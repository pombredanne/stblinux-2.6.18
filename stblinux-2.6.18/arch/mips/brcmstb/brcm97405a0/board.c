/*
 * arch/mips/brcmstb/brcm97405a0/board.c
 *
 * Copyright (C) 2004-2007 Broadcom Corporation
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *
 * Board Specific routines for Broadcom eval boards
 *
 * when         who    what
 * ----         ---    ----
 * 03-31-2004   THT    Created
 * 09-21-2006	TDT	   Added to 2.6.18 kernel
 */

#include <linux/config.h>
// For module exports
#include <linux/module.h>

#include <asm/brcmstb/common/brcmstb.h>
#include <asm/brcmstb/brcm97405a0/bchp_pci_cfg.h>

#ifdef CONFIG_MIPS_BRCM_IKOS

#ifdef DRAM_SIZE
#undef DRAM_SIZE
#endif

// For Ikos
#define DRAM_SIZE	(32 << 20)
#endif

#define NUM_DDR 4


#define SUN_TOP_CTRL_STRAP_VALUE 0xb040401c

#define STRAP_PCI_MEMWIN_SIZE_SHIFT 8
#define STRAP_PCI_MEMWIN_SIZE_MASK 0x00000030

#define STRAP_DDR_CONFIGURATION_SHIFT 	21
#define STRAP_DDR_CONFIGURATION_MASK  	0x00600000


static unsigned long
board_init_once(void)
{
 	unsigned long regval;
	unsigned long memSize = 1<<4;
	unsigned long board_strap;
	unsigned long pci_memwin_size;
	
	regval = *((volatile unsigned long *) SUN_TOP_CTRL_STRAP_VALUE) ;

	/* DDR configuration for DDR0:
	 *                              0 = 16Mx16 bit parts (32MB each)
	 *                              1 = 32Mx16 bit parts (64MB each)
	 *                              2 = 64Mx16 bit parts (128MB each)
	 *                              3 = 128Mx16 bit parts (256MB each)
	 */

	board_strap = (regval & STRAP_DDR_CONFIGURATION_MASK) >> STRAP_DDR_CONFIGURATION_SHIFT;
	pci_memwin_size = (regval & STRAP_PCI_MEMWIN_SIZE_MASK) >> STRAP_PCI_MEMWIN_SIZE_SHIFT;
printk("board_init_once: regval=%08lx, ddr_strap=%lx, %d chips, pci_size=%lx\n", regval, board_strap, NUM_DDR, pci_memwin_size);

	switch (board_strap & 3) {
	case 0:
		memSize = (32 << 20)*NUM_DDR; 
		break;
	case 1:
		memSize = (64 << 20)*NUM_DDR; 
		break;
	case 2:
		memSize = (128 << 20)*NUM_DDR; 
		break;
	case 3:
		memSize = (256 << 20)*NUM_DDR; 
		break;
	}
	
	printk("Detected %ld MB on board\n", (memSize >>20));
	return memSize;
}


unsigned long
get_RAM_size(void)
{
	static int once;
	static unsigned long dramSize = 0;

	if (!once) {
		once++;
		dramSize = board_init_once();
		if (dramSize != DRAM_SIZE) {
			printk("Board strapped at %ld MB, default is %d MB\n", (dramSize>>20), (DRAM_SIZE>>20));
		}
#ifndef CONFIG_DISCONTIGMEM
		/* PR23504: without discontig support, we can only access 256MB */
		if (dramSize > 0x10000000) {
			dramSize = 0x10000000;
			printk("Extra RAM beyond 256MB ignored.  Please "
				"use a kernel that supports DISCONTIG.\n");
		}
#endif
	}
	if (dramSize)
		return dramSize;
	else
		return DRAM_SIZE;
}


EXPORT_SYMBOL(get_RAM_size);

