/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1995 Linus Torvalds
 * Copyright (C) 1995 Waldorf Electronics
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03  Ralf Baechle
 * Copyright (C) 1996 Stoned Elipot
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2000 2001, 2002  Maciej W. Rozycki
 * Copyright (C) 2006 Broadcom Corp.
 */
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/stddef.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/user.h>
#include <linux/utsname.h>
#include <linux/a.out.h>
#include <linux/screen_info.h>
#include <linux/bootmem.h>
#include <linux/initrd.h>
#include <linux/major.h>
#include <linux/kdev_t.h>
#include <linux/root_dev.h>
#include <linux/highmem.h>
#include <linux/console.h>
#include <linux/mmzone.h>
#include <linux/pfn.h>

#include <asm/addrspace.h>
#include <asm/bootinfo.h>
#include <asm/cache.h>
#include <asm/cpu.h>
#include <asm/sections.h>
#include <asm/setup.h>
#include <asm/system.h>

#ifdef CONFIG_MIPS_BRCM97XXX
#include <asm/brcmstb/common/brcmstb.h>
#endif

struct cpuinfo_mips cpu_data[NR_CPUS] __read_mostly;

EXPORT_SYMBOL(cpu_data);

#ifdef CONFIG_VT
struct screen_info screen_info;
#endif

/*
 * Despite it's name this variable is even if we don't have PCI
 */
unsigned int PCI_DMA_BUS_IS_PHYS;

EXPORT_SYMBOL(PCI_DMA_BUS_IS_PHYS);

/*
 * Setup information
 *
 * These are initialized so they are in the .data section
 */
unsigned long mips_machtype __read_mostly = MACH_UNKNOWN;
unsigned long mips_machgroup __read_mostly = MACH_GROUP_UNKNOWN;

EXPORT_SYMBOL(mips_machtype);
EXPORT_SYMBOL(mips_machgroup);

struct boot_mem_map boot_mem_map;
phys_t upper_memory;
EXPORT_SYMBOL(upper_memory);

static char command_line[CL_SIZE];
       char arcs_cmdline[CL_SIZE]=CONFIG_CMDLINE;

/*
 * mips_io_port_base is the begin of the address space to which x86 style
 * I/O ports are mapped.
 */
const unsigned long mips_io_port_base __read_mostly = -1;
EXPORT_SYMBOL(mips_io_port_base);

/*
 * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped
 * for the processor.
 */
unsigned long isa_slot_offset;
EXPORT_SYMBOL(isa_slot_offset);

static struct resource code_resource = { .name = "Kernel code", };
static struct resource data_resource = { .name = "Kernel data", };

void __init add_memory_region(phys_t start, phys_t size, long type)
{
	int x = boot_mem_map.nr_map;

/* Disable merging for BRCM boards */
#ifndef CONFIG_MIPS_BRCM
	{
		struct boot_mem_map_entry *prev = boot_mem_map.map + x - 1;
		/*
		 * Try to merge with previous entry if any.  This is far less than
		 * perfect but is sufficient for most real world cases.
		 */
		if (x && prev->addr + prev->size == start && prev->type == type) {
			prev->size += size;
			return;
		}
	}
#endif

	if (x == BOOT_MEM_MAP_MAX) {
		printk("Ooops! Too many entries in the memory map!\n");
		return;
	}

	boot_mem_map.map[x].addr = start;
	boot_mem_map.map[x].size = size;
	boot_mem_map.map[x].type = type;
	boot_mem_map.nr_map++;
}

static void __init print_memory_map(void)
{
	int i;
	const int field = 2 * sizeof(unsigned long);

	for (i = 0; i < boot_mem_map.nr_map; i++) {
		printk(" memory: %0*Lx @ %0*Lx ",
		       field, (unsigned long long) boot_mem_map.map[i].size,
		       field, (unsigned long long) boot_mem_map.map[i].addr);

		switch (boot_mem_map.map[i].type) {
		case BOOT_MEM_RAM:
			printk("(usable)\n");
			break;
		case BOOT_MEM_ROM_DATA:
			printk("(ROM data)\n");
			break;
		case BOOT_MEM_RESERVED:
			printk("(reserved)\n");
			break;
		default:
			printk("type %lu\n", boot_mem_map.map[i].type);
			break;
		}
	}
}

#ifdef CONFIG_MIPS_BRCM

/*
 * THT: Unlike the kernel boot_mem_map which is an array, this is a essentially 
 * a linked list for ease of inserting/deleting nodes. (Double linked list may be an overkill)
 * Since we cannot do kmalloc at this time, we just have to use array to handle it.
 * We don't currently need deletion, so this is just a simple sorted linked list implementation 
 * with support for insertion.
 *
 * Note: We try to put all Brcm extensions under #ifdef CONFIG_MIPS_BRCM but never tested the
 * else case. God forbid, one day we may be required to merge these codes into the MIPS tree.
 */
//#define BOOT_MEM_HOLE	4  // Memory hole currently not implemented
#define NILL (-1)
struct brcm_boot_mem_map {
	int nr_map;
	int head, tail;
	int avail;			// Currently we don't support deletion, so this is just the next free node
	struct {
		phys_t addr;	/* start of memory segment */
		phys_t size;	/* size of memory segment */
		long type;		/* type of memory segment */
		int next, prev;
	} map[BOOT_MEM_MAP_MAX];
};
struct brcm_boot_mem_map brcm_mmap;

/*
 * Standard Linked List Insert After op
 */
static int brcm_insert_after(int after, phys_t addr, phys_t size, long type)
{
	int newNode = brcm_mmap.avail;

	if (++brcm_mmap.avail >= BOOT_MEM_MAP_MAX) {
		printk("Max Nodes exceeded: Node at [%08x:%08x] ignored\n", (unsigned int)addr, (unsigned int)size);
		return -1;
	}
	brcm_mmap.nr_map++;
	brcm_mmap.map[newNode].addr = addr;
	brcm_mmap.map[newNode].size = size;
	brcm_mmap.map[newNode].type = type;
	brcm_mmap.map[newNode].next = brcm_mmap.map[newNode].prev = NILL;
	if (after == NILL) {
		brcm_mmap.map[newNode].next = brcm_mmap.head;
		brcm_mmap.head = newNode;
	}
	else {
		brcm_mmap.map[newNode].next = brcm_mmap.map[after].next;
		brcm_mmap.map[newNode].prev = after;
		brcm_mmap.map[after].next = newNode;
	}
	if (brcm_mmap.tail == after ) { /* insert after last node, or to an empty list */
		brcm_mmap.tail = newNode;
	}
	
	return newNode;
}

/*
 * Load the bootmem_map into our brcm_mmap, for ease of sorting.
 */
static void brcm_init_memory_map(void)
{
	int i;
	
	brcm_mmap.nr_map = 0;
	brcm_mmap.head=brcm_mmap.tail = NILL;
	brcm_mmap.avail = 0;

	for (i=0; i<BOOT_MEM_MAP_MAX; i++) {
		brcm_mmap.map[i].next = brcm_mmap.map[i].prev = NILL;
		brcm_mmap.map[i].addr = brcm_mmap.map[i].size = brcm_mmap.map[i].type = 0;
	}
	
	for (i = 0; i < boot_mem_map.nr_map; i++) {
		brcm_insert_after(brcm_mmap.tail, 
			boot_mem_map.map[i].addr, boot_mem_map.map[i].size, boot_mem_map.map[i].type);
	}
}

static long inline flip_type(long old_type)
{
	if (old_type == BOOT_MEM_RAM) return BOOT_MEM_RESERVED;
	else if (old_type == BOOT_MEM_RESERVED) return BOOT_MEM_RAM;
	else return BOOT_MEM_ROM_DATA;
}

static int brcm_insert_ram_node(phys_t start, phys_t size, long type)
{
	int n;
	int found = 0;
	phys_t oldstart, oldsize;
	long oldtype;

	for (n = brcm_mmap.head; n != NILL && !found; n = brcm_mmap.map[n].next) {
		unsigned long end_node = brcm_mmap.map[n].addr + brcm_mmap.map[n].size;

		if (start >= brcm_mmap.map[n].addr && start <= end_node ) {
			if ((start+size) <= end_node) {
				found = 1;
				break;
			}
			/* Some validation */
			else { /* ((start+size) > (brcm_mmap.map[n].addr + brcm_mmap.map[n].size)) */
				printk("Entry start=%dm: size=%dm overlaps with existing node(%dm:%dm), and is ignored\n", 
					(unsigned int)start>>20, (unsigned int)size>>20, 
					(unsigned int)brcm_mmap.map[n].addr>>20, (unsigned int)brcm_mmap.map[n].size>>20);
				return -1;
			}
		}
		if (start < brcm_mmap.map[n].addr) {
			printk("Entry start=%dm: size=%dm not found in memory map and is ignored\n", 
				(unsigned int)start>>20, (unsigned int)size>>20);
			return -2;
		}
		/* else start > node_start and start >= node_end, visit next node */
	}
	if (!found) {
		printk("No node found in memory map\n");
		return -2;
	}
	
	
	/* Save the old info */
	oldstart = brcm_mmap.map[n].addr;
	oldtype = brcm_mmap.map[n].type;
	oldsize = brcm_mmap.map[n].size;
	
	if (start >= brcm_mmap.map[n].addr) {
		/* We know that start+size <= (brcm_mmap.map[n].addr + brcm_mmap.map[n].size) from above
		 * This split the old node into 3 new nodes.
		 * The middle node will bear the type of the new node (to be inserted)
		 * The other 2 nodes bear the opposite type.
		 */
		/*
		 * Handle the first node: old_start, (new_start - old_start), type = opposite of new node type
		 */
		if (start > brcm_mmap.map[n].addr) {
			//pstart = brcm_mmap.map[n].addr; Unchanged
			brcm_mmap.map[n].size = start - brcm_mmap.map[n].addr;
			brcm_mmap.map[n].type = flip_type(type);
		
			//Insert new node with new type.
			n = brcm_insert_after(n, start, size, type);
		}
		else { // start == old_start, just set the type and size
			brcm_mmap.map[n].size = size;
			brcm_mmap.map[n].type = type;			
		}

		// Now insert the last node with the flip type
		if ((start+size) < (oldstart+oldsize)) {
			n = brcm_insert_after(n, start+size, oldstart+oldsize-start-size, flip_type(type));
			return n;
		}
	}

	return n;
}

#if 0
/*
 * Copy the our private bootmem map back to the kernel bootmem, marking all reserved type as RAM.
 */
static void brcm_copy_bootmem_map(void)
{
	int node;
	
	boot_mem_map.nr_map = 0;
	for (node = brcm_mmap.head; node != NILL; node = brcm_mmap.map[node].next) {
		add_memory_region(brcm_mmap.map[node].addr, brcm_mmap.map[node].size, BOOT_MEM_RAM);
	}
}
#endif

int brcm_walk_boot_mem_map(void* cbdata, walk_cb_t walk_cb)
{
	int n, done = 0;
	
	for (n=brcm_mmap.head; n!=NILL; n=brcm_mmap.map[n].next) {
		if ((done = (*walk_cb)(brcm_mmap.map[n].addr, brcm_mmap.map[n].size, brcm_mmap.map[n].type, cbdata))) {
			return done;
		}
	}
	return 0;
}	
EXPORT_SYMBOL(brcm_walk_boot_mem_map);

/*
 * We want to print the memory map NOW so we use uart_puts.  printk's won't be shown 
 * until the kernel has started
 */
static int  brcm_walk_print(unsigned long addr, unsigned long size, long type, void* data)
{
	char* msg = (char*) data;
	
	sprintf(msg, "node [%08lx, %08lx: %s]\n", addr, size, type==BOOT_MEM_RAM ? "RAM" : "RSVD");
	uart_puts(msg);
	return 0;  // Next node please
}

static void brcm_print_memory_map(void)
{
	char msg[80];

	brcm_walk_boot_mem_map(msg, brcm_walk_print);
}

/*
 * By default, set the kernel to use 32MB if the user does not specify mem=nnM on the command line
 */
static inline void brcm_default_boot_mem()
{
	int ramSizeMB = get_RAM_size() >> 20;
	int size;
	char msg[40];
	
	if (ramSizeMB <= 32) {
#ifdef CONFIG_BLK_DEV_INITRD
		uart_puts("Using all RAM for STBs\n");
		size = ramSizeMB;

#else
		size = 20;

#endif
	}
	else {
		/* 
		  * Kernels on STBs with larger than 32MB, we only use 32MB RAM for the kernel
		  */

#ifdef CONFIG_MTD_BRCMNAND
		size = 48; // FOr BBT tables
#else
		size = 32;
#endif
	}
	sprintf(msg, "Using %dMB for memory, overwrite by passing mem=xx\n", size);
	uart_puts(msg);
	brcm_insert_ram_node(0, size<<20, BOOT_MEM_RAM);
}

/*
 * Here we only check for the kernel starting memory.
 */
static void inline brcm_reserve_bootmem_node(unsigned long firstUsableAddr)
{
	int i;
	
	/*
	 * The kernel boot_mem_map does not contain the reserved info, but ours does
	 */
	for (i = brcm_mmap.head; i != NILL; i = brcm_mmap.map[i].next) {
		if (brcm_mmap.map[i].type != BOOT_MEM_RESERVED)
			continue;

		/* Kernel must use the first 1MB for exception handlers, so request to reserve
		 * memory starting at 0 will be ignored
		 */
		if (brcm_mmap.map[i].addr < firstUsableAddr) {
			printk("Error: Cannot reserve memory currently used by the kernel, requested=%08x, firstUsable=%08lx\n",
				(unsigned int) brcm_mmap.map[i].addr, firstUsableAddr);
			continue;
		}
		if (brcm_mmap.map[i].addr < (256<<20)) {
#ifndef CONFIG_DISCONTIGMEM
			reserve_bootmem(brcm_mmap.map[i].addr, 
				brcm_mmap.map[i].size);
#else
			reserve_bootmem_node(NODE_DATA(0), brcm_mmap.map[i].addr, 
				brcm_mmap.map[i].size);		
#endif
			if (upper_memory < brcm_mmap.map[i].addr) {
				upper_memory = brcm_mmap.map[i].addr;
			}
			printk(KERN_NOTICE "Reserving %ld MB upper memory starting at %08x\n", 
				brcm_mmap.map[i].size >> 20,
				(unsigned int)brcm_mmap.map[i].addr);
		}
		else {
#ifndef CONFIG_DISCONTIGMEM
			uart_puts("Error: Cannot reserve memory above 256MB.  for UMA platforms\n");
#else
			reserve_bootmem_node(NODE_DATA(1), brcm_mmap.map[i].addr, 
				brcm_mmap.map[i].size);	
			printk(KERN_NOTICE "Reserving %ld MB upper memory starting at %08x\n", 
				brcm_mmap.map[i].size >> 20,
				brcm_mmap.map[i].addr);
#endif
		}

	}
}

unsigned long
get_RSVD_size(void)
{
	int node;
	unsigned long res = 0;

	for (node = brcm_mmap.head; node != NILL; node = brcm_mmap.map[node].next) {
		if(brcm_mmap.map[node].type == BOOT_MEM_RESERVED)
			res += brcm_mmap.map[node].size;
	}
	return(res);
}
EXPORT_SYMBOL(get_RSVD_size);

#else
#define brcm_init_memory_map
#define brcm_insert_ram_node(start,size,type)
#define brcm_default_boot_mem
#define brcm_print_memory_map
#define brcm_reserve_bootmem_node(firstUsableAddr)
#endif // #define CONFIG_MIPS_BRCM97XXX

static inline void parse_cmdline_early(void)
{
	char c = ' ', *to = command_line, *from = saved_command_line;
	unsigned long start_at, mem_size;
	int len = 0;
	int usermem = 0;

	printk("Determined physical RAM map:\n");
	print_memory_map();

    brcm_init_memory_map();

	for (;;) {
		/*
		 * "mem=XXX[kKmM]" defines a memory region from
		 * 0 to <XXX>, overriding the determined size.
		 * "mem=XXX[KkmM]@YYY[KkmM]" defines a memory region from
		 * <YYY> to <YYY>+<XXX>, overriding the determined size.
		 *
		 * The followings are BRCM extension to/deviation from the documentation:
		 * "mem=XXX[KkmM]$YYY[KkmM]" defines a memory region from
		 * <YYY> to <YYY>+<XXX> to be excluded from kernel usable RAM
		 * # is used to mark an ACPI region, but since we don't support it,
		 * we have a non-conformant behavior, by using # and $ interchangeably.
		 * This is done to allow the user to specify # in lieu of $ because
		 * the CFE would interprete the $, and thus requires an escape sequence.
		 */
		if (c == ' ' && !memcmp(from, "mem=", 4)) {
			if (to != command_line)
				to--;
			/*
			 * If a user specifies memory size, we
			 * blow away any automatically generated
			 * size.
			 */
			if (usermem == 0) {
#ifndef CONFIG_MIPS_BRCM
				boot_mem_map.nr_map = 0;
#endif
				usermem = 1;
			}
			mem_size = memparse(from + 4, &from);
			switch (*from) {
			case '@':
				start_at = memparse(from + 1, &from);
				brcm_insert_ram_node(start_at, mem_size, BOOT_MEM_RAM);
				break;
			case '$':
			case '#': /* CFE will interprete $, so non-conformant alternate syntax is supported */
				start_at = memparse(from + 1, &from);
				brcm_insert_ram_node(start_at, mem_size, BOOT_MEM_RESERVED);
				break;
			default:
				start_at = 0;
				brcm_insert_ram_node(start_at, mem_size, BOOT_MEM_RAM);
		}
			
		}
		c = *(from++);
		if (!c)
			break;
		if (CL_SIZE <= ++len)
			break;
		*(to++) = c;
	}
	*to = '\0';

	if (!usermem) {
		/* Default memory map */
		brcm_default_boot_mem();
	}

		printk("User-defined physical RAM map:\n");
	brcm_print_memory_map();

}

static inline int parse_rd_cmdline(unsigned long* rd_start, unsigned long* rd_end)
{
	/*
	 * "rd_start=0xNNNNNNNN" defines the memory address of an initrd
	 * "rd_size=0xNN" it's size
	 */
	unsigned long start = 0;
	unsigned long size = 0;
	unsigned long end;
	char cmd_line[CL_SIZE];
	char *start_str;
	char *size_str;
	char *tmp;

	strcpy(cmd_line, command_line);
	*command_line = 0;
	tmp = cmd_line;
	/* Ignore "rd_start=" strings in other parameters. */
	start_str = strstr(cmd_line, "rd_start=");
	if (start_str && start_str != cmd_line && *(start_str - 1) != ' ')
		start_str = strstr(start_str, " rd_start=");
	while (start_str) {
		if (start_str != cmd_line)
			strncat(command_line, tmp, start_str - tmp);
		start = memparse(start_str + 9, &start_str);
		tmp = start_str + 1;
		start_str = strstr(start_str, " rd_start=");
	}
	if (*tmp)
		strcat(command_line, tmp);

	strcpy(cmd_line, command_line);
	*command_line = 0;
	tmp = cmd_line;
	/* Ignore "rd_size" strings in other parameters. */
	size_str = strstr(cmd_line, "rd_size=");
	if (size_str && size_str != cmd_line && *(size_str - 1) != ' ')
		size_str = strstr(size_str, " rd_size=");
	while (size_str) {
		if (size_str != cmd_line)
			strncat(command_line, tmp, size_str - tmp);
		size = memparse(size_str + 8, &size_str);
		tmp = size_str + 1;
		size_str = strstr(size_str, " rd_size=");
	}
	if (*tmp)
		strcat(command_line, tmp);

#ifdef CONFIG_64BIT
	/* HACK: Guess if the sign extension was forgotten */
	if (start > 0x0000000080000000 && start < 0x00000000ffffffff)
		start |= 0xffffffff00000000UL;
#endif

	end = start + size;
	if (start && end) {
		*rd_start = start;
		*rd_end = end;
		return 1;
	}
	return 0;
}

#define PFN_UP(x)	(((x) + PAGE_SIZE - 1) >> PAGE_SHIFT)
#define PFN_DOWN(x)	((x) >> PAGE_SHIFT)
#define PFN_PHYS(x)	((x) << PAGE_SHIFT)

#define MAXMEM		HIGHMEM_START
#define MAXMEM_PFN	PFN_DOWN(MAXMEM)

static inline void bootmem_init(void)
{
	unsigned long start_pfn;
	unsigned long reserved_end = (unsigned long)&_end;
#ifndef CONFIG_SGI_IP27
	unsigned long first_usable_pfn;
	unsigned long bootmap_size;
	int i;
#endif
	unsigned long firstUsableAddr;
#ifdef CONFIG_BLK_DEV_INITRD
	int initrd_reserve_bootmem = 0;

	/* Board specific code should have set up initrd_start and initrd_end */
 	ROOT_DEV = Root_RAM0;
	if (parse_rd_cmdline(&initrd_start, &initrd_end)) {
		reserved_end = max(reserved_end, initrd_end);
		initrd_reserve_bootmem = 1;
	} else {
		unsigned long tmp;
		u32 *initrd_header;

#if 1 //def CONFIG_MIPS_BRCM
	extern void* __initramfs_start;
	extern void* __initramfs_end;
	
	//ROOT_DEV = Root_RAM0;
	initrd_start = (unsigned long) &__initramfs_start;
	initrd_end = (unsigned long) &__initramfs_end;
#endif

		tmp = ((reserved_end + PAGE_SIZE-1) & PAGE_MASK) - sizeof(u32) * 2;
		if (tmp < reserved_end)
			tmp += PAGE_SIZE;
		initrd_header = (u32 *)tmp;
		if (initrd_header[0] == 0x494E5244) {
			initrd_start = (unsigned long)&initrd_header[2];
			initrd_end = initrd_start + initrd_header[1];
			reserved_end = max(reserved_end, initrd_end);
			initrd_reserve_bootmem = 1;
		}
	}
#endif	/* CONFIG_BLK_DEV_INITRD */

	/*
	 * Partially used pages are not usable - thus
	 * we are rounding upwards.
	 */
	start_pfn = PFN_UP(CPHYSADDR(reserved_end));

#ifndef CONFIG_SGI_IP27
	/* Find the highest page frame number we have available.  */
	max_pfn = 0;
	first_usable_pfn = -1UL;
	for (i = 0; i < boot_mem_map.nr_map; i++) {
		unsigned long start, end;

		if (boot_mem_map.map[i].type != BOOT_MEM_RAM)
			continue;

		start = PFN_UP(boot_mem_map.map[i].addr);
		end = PFN_DOWN(boot_mem_map.map[i].addr
		      + boot_mem_map.map[i].size);

		if (start >= end)
			continue;
		if (end > max_pfn)
			max_pfn = end;
		if (start < first_usable_pfn) {
			if (start > start_pfn) {
				first_usable_pfn = start;
			} else if (end > start_pfn) {
				first_usable_pfn = start_pfn;
			}
		}
	}

	/*
	 * Determine low and high memory ranges
	 */
	max_low_pfn = max_pfn;
	if (max_low_pfn > MAXMEM_PFN) {
		max_low_pfn = MAXMEM_PFN;
#ifndef CONFIG_HIGHMEM
		/* Maximum memory usable is what is directly addressable */
		printk(KERN_WARNING "Warning only %ldMB will be used.\n",
		       MAXMEM >> 20);
		printk(KERN_WARNING "Use a HIGHMEM enabled kernel.\n");
#endif
	}

#ifdef CONFIG_HIGHMEM
	/*
	 * Crude, we really should make a better attempt at detecting
	 * highstart_pfn
	 */
	highstart_pfn = highend_pfn = max_pfn;
	if (max_pfn > MAXMEM_PFN) {
		highstart_pfn = MAXMEM_PFN;
		printk(KERN_NOTICE "%ldMB HIGHMEM available.\n",
		       (highend_pfn - highstart_pfn) >> (20 - PAGE_SHIFT));
	}
#endif

	/* Initialize the boot-time allocator with low memory only.  */
	bootmap_size = init_bootmem(first_usable_pfn, max_low_pfn);

	/*
	 * Register fully available low RAM pages with the bootmem allocator.
	 */
	for (i = 0; i < boot_mem_map.nr_map; i++) {
		unsigned long curr_pfn, last_pfn, size;

		/*
		 * Reserve usable memory.
		 */
		if (boot_mem_map.map[i].type != BOOT_MEM_RAM)
			continue;

		/*
		 * We are rounding up the start address of usable memory:
		 */
		curr_pfn = PFN_UP(boot_mem_map.map[i].addr);
		if (curr_pfn >= max_low_pfn)
			continue;
		if (curr_pfn < start_pfn)
			curr_pfn = start_pfn;

		/*
		 * ... and at the end of the usable range downwards:
		 */
		last_pfn = PFN_DOWN(boot_mem_map.map[i].addr
				    + boot_mem_map.map[i].size);

		if (last_pfn > max_low_pfn)
			last_pfn = max_low_pfn;

		/*
		 * Only register lowmem part of lowmem segment with bootmem.
		 */
		size = last_pfn - curr_pfn;
		if (curr_pfn > PFN_DOWN(HIGHMEM_START))
			continue;
		if (curr_pfn + size - 1 > PFN_DOWN(HIGHMEM_START))
			size = PFN_DOWN(HIGHMEM_START) - curr_pfn;
		if (!size)
			continue;

		/*
		 * ... finally, did all the rounding and playing
		 * around just make the area go away?
		 */
		if (last_pfn <= curr_pfn)
			continue;

		/* Register lowmem ranges */
		free_bootmem(PFN_PHYS(curr_pfn), PFN_PHYS(size));
		//memory_present(0, curr_pfn, curr_pfn + size - 1);
	}

	/* Reserve the bootmap memory.  */

#ifndef CONFIG_DISCONTIGMEM
	reserve_bootmem(PFN_PHYS(first_usable_pfn), bootmap_size);
	firstUsableAddr = PFN_PHYS(first_usable_pfn) + bootmap_size;
#else
	
	reserve_bootmem_node(NODE_DATA(0), PFN_PHYS(first_usable_pfn), bootmap_size[0]);
	reserve_bootmem_node(NODE_DATA(1), 0x20000000, bootmap_size[1]);
	firstUsableAddr = PFN_PHYS(first_usable_pfn) + bootmap_size[0];

#endif
#ifdef CONFIG_MIPS_BRCM
	brcm_reserve_bootmem_node(firstUsableAddr);

#endif

#endif /* !CONFIG_SGI_IP27 */

#ifdef CONFIG_BLK_DEV_INITRD
	initrd_below_start_ok = 1;
	if (initrd_start) {
		unsigned long initrd_size = ((unsigned char *)initrd_end) -
			((unsigned char *)initrd_start);
		const int width = sizeof(long) * 2;

		printk("Initial ramdisk at: 0x%p (%lu bytes)\n",
		       (void *)initrd_start, initrd_size);

		if (CPHYSADDR(initrd_end) > PFN_PHYS(max_low_pfn)) {
			printk("initrd extends beyond end of memory "
			       "(0x%0*Lx > 0x%0*Lx)\ndisabling initrd\n",
			       width,
			       (unsigned long long) CPHYSADDR(initrd_end),
			       width,
			       (unsigned long long) PFN_PHYS(max_low_pfn));
			initrd_start = initrd_end = 0;
			initrd_reserve_bootmem = 0;
		}

		if (initrd_reserve_bootmem)
			reserve_bootmem(CPHYSADDR(initrd_start), initrd_size);
	}
#endif /* CONFIG_BLK_DEV_INITRD  */
}

/*
 * arch_mem_init - initialize memory managment subsystem
 *
 *  o plat_mem_setup() detects the memory configuration and will record detected
 *    memory areas using add_memory_region.
 *  o parse_cmdline_early() parses the command line for mem= options which,
 *    iff detected, will override the results of the automatic detection.
 *
 * At this stage the memory configuration of the system is known to the
 * kernel but generic memory managment system is still entirely uninitialized.
 *
 *  o bootmem_init()
 *  o sparse_init()
 *  o paging_init()
 *
 * At this stage the bootmem allocator is ready to use.
 *
 * NOTE: historically plat_mem_setup did the entire platform initialization.
 *       This was rather impractical because it meant plat_mem_setup had to
 * get away without any kind of memory allocator.  To keep old code from
 * breaking plat_setup was just renamed to plat_setup and a second platform
 * initialization hook for anything else was introduced.
 */

extern void plat_mem_setup(void);

static void __init arch_mem_init(char **cmdline_p)
{
	/* call board setup routine */
	plat_mem_setup();

	strlcpy(command_line, arcs_cmdline, sizeof(command_line));
	strlcpy(saved_command_line, command_line, COMMAND_LINE_SIZE);

	*cmdline_p = command_line;

	parse_cmdline_early();
	bootmem_init();
	sparse_init();
	paging_init();
}

static inline void resource_init(void)
{
	int i;

	if (UNCAC_BASE != IO_BASE)
		return;

	code_resource.start = virt_to_phys(&_text);
	code_resource.end = virt_to_phys(&_etext) - 1;
	data_resource.start = virt_to_phys(&_etext);
	data_resource.end = virt_to_phys(&_edata) - 1;

	/*
	 * Request address space for all standard RAM.
	 */
	for (i = 0; i < boot_mem_map.nr_map; i++) {
		struct resource *res;
		unsigned long start, end;

		start = boot_mem_map.map[i].addr;
		end = boot_mem_map.map[i].addr + boot_mem_map.map[i].size - 1;
		if (start >= MAXMEM)
			continue;
		if (end >= MAXMEM)
			end = MAXMEM - 1;

		res = alloc_bootmem(sizeof(struct resource));
		switch (boot_mem_map.map[i].type) {
		case BOOT_MEM_RAM:
		case BOOT_MEM_ROM_DATA:
			res->name = "System RAM";
			break;
		case BOOT_MEM_RESERVED:
		default:
			res->name = "reserved";
		}

		res->start = start;
		res->end = end;

		res->flags = IORESOURCE_MEM | IORESOURCE_BUSY;
		request_resource(&iomem_resource, res);

		/*
		 *  We don't know which RAM region contains kernel data,
		 *  so we try it repeatedly and let the resource manager
		 *  test it.
		 */
		request_resource(res, &code_resource);
		request_resource(res, &data_resource);
	}
}

#undef PFN_UP
#undef PFN_DOWN
#undef PFN_PHYS

#undef MAXMEM
#undef MAXMEM_PFN

void __init setup_arch(char **cmdline_p)
{
	cpu_probe();
	prom_init();
	cpu_report();

#if defined(CONFIG_VT)
#if defined(CONFIG_VGA_CONSOLE)
        conswitchp = &vga_con;
#elif defined(CONFIG_DUMMY_CONSOLE)
        conswitchp = &dummy_con;
#endif
#endif

	arch_mem_init(cmdline_p);

	resource_init();
#ifdef CONFIG_SMP
	plat_smp_setup();
#endif
}

int __init fpu_disable(char *s)
{
	int i;

	for (i = 0; i < NR_CPUS; i++)
		cpu_data[i].options &= ~MIPS_CPU_FPU;

	return 1;
}

__setup("nofpu", fpu_disable);

int __init dsp_disable(char *s)
{
	cpu_data[0].ases &= ~MIPS_ASE_DSP;

	return 1;
}

__setup("nodsp", dsp_disable);