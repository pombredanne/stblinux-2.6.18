/*
 *  drivers/mtd/brcmnand/brcmnand_base.c
 *
    Copyright (c) 2005-2007 Broadcom Corporation                 
    
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2 as
 published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

    File: brcmnand_base.c

    Description: 
    NAND driver with Broadcom NAND controller.
    

when	who what
-----	---	----
051011	tht	codings derived from onenand_base.c implementation.
070528	tht	revised for 2.6.18 derived from nand_base.c implementation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/byteorder/generic.h>
#include <linux/reboot.h>
#include <linux/vmalloc.h>

#include <asm/io.h>
#include <asm/bug.h>
#include <asm/system.h> // For sync on MIPS24K
#include <asm/delay.h>

#ifdef MTD_LARGE
#include <linux/mtd/mtd64.h>
#endif

//#include "bbm.h"

#include "brcmnand_priv.h"

#define PRINTK(...)
//#define PRINTK printk
static char brcmNandMsg[1024];

#define my_be32_to_cpu(x) be32_to_cpu(x)

#ifdef CONFIG_MIPS_BCM7440B0
	#define PLATFORM_IOFLUSH_WAR()	__sync()
#else
	#define PLATFORM_IOFLUSH_WAR()	
#endif

#ifdef CONFIG_MTD_BRCMNAND_EDU

#include "edu.h"

// Prototypes
#include "eduproto.h"
#endif // #ifdef CONFIG_MTD_BRCMNAND_EDU

int gdebug=0;

// Whether we should clear the BBT to fix a previous error.
/* This will eventually be on the command line, to allow a user to 
 * clean the flash
 */
extern int gClearBBT;

/* Number of NAND chips, only applicable to v1.0+ NAND controller */
extern int gNumNand;

/* The Chip Select [0..7] for the NAND chips from gNumNand above, only applicable to v1.0+ NAND controller */
extern int* gNandCS;

#define DRIVER_NAME	"brcmnand"

#define HW_AUTOOOB_LAYOUT_SIZE		32 /* should be enough */

#define BRCMNAND_CORRECTABLE_ECC_ERROR		(1)
#define BRCMNAND_SUCCESS					(0)
#define BRCMNAND_UNCORRECTABLE_ECC_ERROR	(-1)
#define BRCMNAND_FLASH_STATUS_ERROR			(-2)
#define BRCMNAND_TIMED_OUT					(-3)

#ifdef CONFIG_MTD_BRCMNAND_EDU
#define BRCMEDU_CORRECTABLE_ECC_ERROR        (4)
#define BRCMEDU_UNCORRECTABLE_ECC_ERROR      (-4)

uint32_t EDU_ldw;
#endif // #ifdef CONFIG_MTD_BRCMNAND_EDU

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
/* Avoid infinite recursion between brcmnand_refresh_blk() and brcmnand_read_ecc() */
static atomic_t inrefresh = ATOMIC_INIT(0); 
static int brcmnand_refresh_blk(struct mtd_info *, loff_t);
static int brcmnand_erase_nolock(struct mtd_info *, struct erase_info *, int);
#endif


/*
 * MTD structure for Broadcom NAND
 */
//static struct mtd_info *brcmnand_mtd = NULL;


typedef struct brcmnand_chip_Id {
    	uint8 mafId, chipId;
	const char* chipIdStr;
	uint32 options;
	uint32 timing1, timing2; // Specify a non-zero value to override the default timings.
	unsigned int ctrlVersion; // Required controller version if different than 0
} brcmnand_chip_Id;

/*
 * List of supported chip
 */
static brcmnand_chip_Id brcmnand_chips[] = {
	{	/* 0 */
		.chipId = SAMSUNG_K9F1G08U0A,
		.mafId = FLASHTYPE_SAMSUNG,
		.chipIdStr = "Samsung K9F1G08U0A",
		.options = NAND_USE_FLASH_BBT, 		/* Use BBT on flash */
				//| NAND_COMPLEX_OOB_WRITE	/* Write data together with OOB for write_oob */
		.timing1 = 0, //00070000,
		.timing2 = 0,
		.ctrlVersion = 0, /* THT Verified on data-sheet 7/10/08: Allows 4 on main and 4 on OOB */
	},

	{	/* 1 */
		.chipId = ST_NAND512W3A,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST ST_NAND512W3A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, //0x6474555f, 
		.timing2 = 0, //0x00000fc7,
		.ctrlVersion = 0,
	},
	{	/* 2 */
		.chipId = ST_NAND256W3A,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST ST_NAND256W3A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, //0x6474555f, 
		.timing2 = 0, //0x00000fc7,
		.ctrlVersion = 0,
	},
#if 0 // EOL
	{	/* 4 */
		.chipId = HYNIX_HY27UF081G2M,
		.mafId = FLASHTYPE_HYNIX,
		.chipIdStr = "HYNIX HY27UF081G2M",
		.options = NAND_USE_FLASH_BBT 
			,
	},
#endif
	/* This is the new version of HYNIX_HY27UF081G2M which is EOL.
	 * Both use the same DevID
	 */
	{	/* 3 */
		.chipId = HYNIX_HY27UF081G2A,
		.mafId = FLASHTYPE_HYNIX,
		.chipIdStr = "Hynix HY27UF081G2A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 4 */
		.chipId = MICRON_MT29F2G08AAB,
		.mafId = FLASHTYPE_MICRON,
		.chipIdStr = "MICRON_MT29F2G08AAB",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},
/* This is just the 16 bit version of the above?
	{
		.chipId = MICRON_MT29F2G16AAB,
		.mafId = FLASHTYPE_MICRON,
		.chipIdStr = "MICRON_MT29F2G16AAB",
		.options = NAND_USE_FLASH_BBT 
			,
	}
*/

	{	/* 5 */
		.chipId = SAMSUNG_K9F2G08U0A,
		.mafId = FLASHTYPE_SAMSUNG,
		.chipIdStr = "Samsung K9F2G08U0A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},

	{	/* 6 */
		.chipId = SAMSUNG_K9K8G08U0A,
		.mafId = FLASHTYPE_SAMSUNG,
		.chipIdStr = "Samsung K9K8G08U0A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},


	{	/* 7 */
		.chipId = HYNIX_HY27UF082G2A,
		.mafId = FLASHTYPE_HYNIX,
		.chipIdStr = "Hynix HY27UF082G2A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},



	{	/* 8 */
		.chipId = HYNIX_HY27UF084G2M,
		.mafId = FLASHTYPE_HYNIX,
		.chipIdStr = "Hynix HY27UF084G2M",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 9 */
		.chipId = SPANSION_S30ML512P_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML512P_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 10 */
		.chipId = SPANSION_S30ML512P_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML512P_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 11 */
		.chipId = SPANSION_S30ML256P_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML256P_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 12 */
		.chipId = SPANSION_S30ML256P_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML256P_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 13 */
		.chipId = SPANSION_S30ML128P_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML128P_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 14 */
		.chipId = SPANSION_S30ML128P_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION S30ML128P_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 15 */
		.chipId = SPANSION_S30ML01GP_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML01GP_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 16 */
		.chipId = SPANSION_S30ML01GP_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML01GP_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 17 */
		.chipId = SPANSION_S30ML02GP_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML02GP_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 18 */
		.chipId = SPANSION_S30ML02GP_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML02GP_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 19 */
		.chipId = SPANSION_S30ML04GP_08,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML04GP_08",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 20 */
		.chipId = SPANSION_S30ML04GP_16,
		.mafId = FLASHTYPE_SPANSION,
		.chipIdStr = "SPANSION_S30ML04GP_16",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	{	/* 21 */
		.chipId = ST_NAND128W3A,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND128W3A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = 0,
	},

	/* The following 6 ST chips only allow 4 writes per page, and requires version2.2 (5) of the controller or later */
	{	/* 22 */
		.chipId = ST_NAND01GW3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND01GW3B2B",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},

	{	/* 23 */ 
		.chipId = ST_NAND01GR3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND01GR3B2B",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},

	{	/* 24 */ 
		.chipId = ST_NAND02GR3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND02GR3B2C",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},
	{	/* 25 */ 
		.chipId = ST_NAND02GW3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND02GW3B2C",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},
	
	{	/* 26 */ 
		.chipId = ST_NAND04GW3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND04GW3B2B",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},
	{	/* 27 */ 
		.chipId = ST_NAND08GW3B,
		.mafId = FLASHTYPE_ST,
		.chipIdStr = "ST NAND08GW3B2A",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
		.ctrlVersion = CONFIG_MTD_BRCMNAND_VERS_2_2,
	},
		
	{	/* 28 */
		.chipId = SAMSUNG_K9LBG08U0M,
		.mafId = FLASHTYPE_SAMSUNG,
		.chipIdStr = "Samsung K9LBG08U0M ",
		.options = NAND_USE_FLASH_BBT, 		/* Use BBT on flash */
				//| NAND_COMPLEX_OOB_WRITE	/* Write data together with OOB for write_oob */
		.timing1 = 0, //00070000,
		.timing2 = 0,
		.ctrlVersion = 0, /* THT Verified on data-sheet 7/10/08: Allows 4 on main and 4 on OOB */
	},
		
	{	/* LAST DUMMY ENTRY */
		.chipId = 0,
		.mafId = 0,
		.chipIdStr = "UNSUPPORTED NAND CHIP",
		.options = NAND_USE_FLASH_BBT,
		.timing1 = 0, .timing2 = 0,
	}
};

// Max chip account for the last dummy entry
#define BRCMNAND_MAX_CHIPS (ARRAY_SIZE(brcmnand_chips) - 1)

#include <mtd/brcmnand_oob.h> /* BRCMNAND controller defined OOB */

static const unsigned char ffchars[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 16 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 32 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 48 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 64 */
};

static unsigned char eccmask[128]; // Will be initialized during probe


static uint32_t brcmnand_ctrl_read(uint32_t nandCtrlReg) 
{
	volatile unsigned long* pReg = (volatile unsigned long*) (BRCMNAND_CTRL_REGS 
		+ nandCtrlReg - BCHP_NAND_REVISION);

	if (nandCtrlReg < BCHP_NAND_REVISION || nandCtrlReg > BCHP_NAND_BLK_WR_PROTECT ||
		(nandCtrlReg & 0x3) != 0) {
		printk(KERN_ERR "brcmnand_ctrl_read: Invalid register value %08x\n", nandCtrlReg);
	}
if (gdebug > 3) printk("%s: CMDREG=%08x val=%08x\n", __FUNCTION__, (unsigned int) nandCtrlReg, (unsigned int)*pReg);
	return (uint32_t) (*pReg);
}


static void brcmnand_ctrl_write(uint32_t nandCtrlReg, uint32_t val) 
{
	volatile unsigned long* pReg = (volatile unsigned long*) (BRCMNAND_CTRL_REGS 
		+ nandCtrlReg - BCHP_NAND_REVISION);

	if (nandCtrlReg < BCHP_NAND_REVISION || nandCtrlReg > BCHP_NAND_BLK_WR_PROTECT ||
		(nandCtrlReg & 0x3) != 0) {
		printk(KERN_ERR "brcmnand_ctrl_read: Invalid register value %08x\n", nandCtrlReg);
	}
	*pReg = (volatile unsigned long) (val);
if (gdebug > 3) printk("%s: CMDREG=%08x val=%08x\n", __FUNCTION__, nandCtrlReg, val);
}


/*
 * chip: BRCM NAND handle
 * offset: offset from start of mtd, not necessarily the same as offset from chip.
 * cmdEndAddr: 1 for CMD_END_ADDRESS, 0 for CMD_ADDRESS
 */
static void brcmnand_ctrl_writeAddr(struct brcmnand_chip* chip, L_OFF_T offset, int cmdEndAddr) 
{
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
	uint32_t pAddr = offset + chip->pbase;

	chip->ctrl_write(cmdEndAddr? BCHP_NAND_CMD_END_ADDRESS: BCHP_NAND_CMD_ADDRESS, pAddr);

#else
	uint32_t udw, ldw, cs;
	DIunion chipOffset;
	
//char msg[24];


	// cs is the index into chip->CS[]
	cs = (uint32_t) __ll_RightShift(offset, chip->chip_shift);
	// chipOffset is offset into the current CS
#ifdef MTD_LARGE
	chipOffset.ll = mtd64_and(offset, mtd64_sub32(chip->chipSize, 1));
#else
	chipOffset.ll = __ll_and32(offset, chip->chipSize - 1);
#endif

	if (cs >= chip->numchips) {
		printk(KERN_ERR "%s: Offset=%s outside of chip range cs=%d, chip->CS[cs]=%d\n", 
			__FUNCTION__, __ll_sprintf(brcmNandMsg, offset), cs, chip->CS[cs]);
		BUG();
		return;
	}

if (gdebug) printk("CS=%d, chip->CS[cs]=%d\n", cs, chip->CS[cs]);

	// ldw is lower 32 bit of chipOffset, need to add pbase when on CS0
	if (chip->CS[cs] == 0) {
		ldw = chipOffset.s.low + chip->pbase;
	}
	else {
		ldw = chipOffset.s.low;
	}
	udw = chipOffset.s.high | (chip->CS[cs] << 16);

if (gdebug > 3) printk("%s: offset=%s  cs=%d ldw = %08x, udw = %08x\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset), cs,  ldw, udw);
	chip->ctrl_write(cmdEndAddr? BCHP_NAND_CMD_END_ADDRESS: BCHP_NAND_CMD_ADDRESS, ldw);
	chip->ctrl_write(BCHP_NAND_CMD_EXT_ADDRESS, udw);


#endif
}

#if 1
/* Dont delete, may be useful for debugging */

static void print_diagnostics(void)
{
	uint32_t nand_acc_control = brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL);
	uint32_t nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
	uint32_t nand_config = brcmnand_ctrl_read(BCHP_NAND_CONFIG);
	uint32_t flash_id = brcmnand_ctrl_read(BCHP_NAND_FLASH_DEVICE_ID);
	uint32_t pageAddr = brcmnand_ctrl_read(BCHP_NAND_PROGRAM_PAGE_ADDR);
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	uint32_t pageAddrExt = brcmnand_ctrl_read(BCHP_NAND_PROGRAM_PAGE_EXT_ADDR);
#endif

	uint32_t ebiCSBase0 = * ((volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_BASE_0));
	//unsigned long nand_timing1 = brcmnand_ctrl_read(BCHP_NAND_TIMING_1);
	//unsigned long nand_timing2 = brcmnand_ctrl_read(BCHP_NAND_TIMING_2);

	printk("NAND_SELECT=%08x ACC_CONTROL=%08x, \tNAND_CONFIG=%08x, FLASH_ID=%08x\n", 
		nand_select, nand_acc_control, nand_config, flash_id);
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	printk("PAGE_EXT_ADDR=%08x\n", pageAddrExt);
#endif
	printk("PAGE_ADDR=%08x, \tCS0_BASE=%08x\n", pageAddr, ebiCSBase0);
}	
#endif

static void print_config_regs(void)
{
	unsigned long nand_acc_control = brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL);
	unsigned long nand_config = brcmnand_ctrl_read(BCHP_NAND_CONFIG);
	unsigned long flash_id = brcmnand_ctrl_read(BCHP_NAND_FLASH_DEVICE_ID);
	unsigned long nand_timing1 = brcmnand_ctrl_read(BCHP_NAND_TIMING_1);
	unsigned long nand_timing2 = brcmnand_ctrl_read(BCHP_NAND_TIMING_2);
	
	
	printk("\nFound NAND: ACC=%08lx, cfg=%08lx, flashId=%08lx, tim1=%08lx, tim2=%08lx\n", 
		nand_acc_control, nand_config, flash_id, nand_timing1, nand_timing2);	
}


#if 1
void print_oobbuf(const unsigned char* buf, int len)
{
int i;


if (!buf) {printk("NULL"); return;}
 for (i=0; i<len; i++) {
  if (i % 16 == 0) printk("\n");
  else if (i % 4 == 0) printk(" ");
  printk("%02x", buf[i]);
 }
 printk("\n");
}

void print_databuf(const unsigned char* buf, int len)
{
int i;


 for (i=0; i<len; i++) {
  if (i % 32 == 0) printk("\n%04x: ", i);
  else if (i % 4 == 0) printk(" ");
  printk("%02x", buf[i]);
 }
 printk("\n");
}

#endif

/*
 * BRCMNAND controller always copies the data in 4 byte chunk, and in Big Endian mode
 * from and to the flash.
 * This routine assumes that dest and src are 4 byte aligned, and that len is a multiple of 4
 (Restriction removed)

 * TBD: 4/28/06: Remove restriction on count=512B, but do restrict the read from within a 512B section.
 * Change brcmnand_memcpy32 to be 2 functions, one to-flash, and one from-flash,
 * enforcing reading from/writing to flash on a 4B boundary, but relaxing on the buffer being on 4 byte boundary.
 */
 typedef union {
 	uint32_t u;
 	char c[4];
} u32_t;

#ifndef CONFIG_MTD_BRCMNAND_EDU
static int brcmnand_from_flash_memcpy32(struct brcmnand_chip* chip, void* dest, L_OFF_T offset, int len)
{
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
	u_char* flash = chip->vbase + offset;
#else
	volatile uint32_t* flash = (volatile uint32_t*) chip->vbase;
#endif
	volatile uint32_t* pucDest = (volatile uint32_t*) dest; 
	volatile uint32_t* pucFlash = (volatile uint32_t*) flash; 
	int i;

#if 1
	if (unlikely(((unsigned int) dest) & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 dest=%p not DW aligned\n", dest);
		return -EINVAL;
	}
	if (unlikely(((unsigned int) flash) & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 src=%p not DW aligned\n", flash);
		return -EINVAL;
	}
	if (unlikely(len & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 len=%d not DW aligned\n", len);
		return -EINVAL;
	}
#endif

#if 0
	/*
	 * Take care of the leading odd bytes.  
	 * Can't use memcpy here, because the flash contents are in BE order
	 */
	odd = (((unsigned long) pucFlash) & 0x3);
	if (odd) {
printk("****** WARNING: leading odd bytes ************\n");
		/* Guaranteed to be valid, since cache is on 512B boundary */
		pSrc = (uint32_t*) (pucFlash - odd);

		/* pSrc is now aligned on a DW boundary, 
		 * no need to call cpu_to_be32 since we write and read from the same endian
		 */
		u32.u = /*cpu_to_be32 */(*pSrc);

		for (i=0; i<odd; i++) {
			pucDest[i] = u32.c[odd+i];
		}
		pucFlash += 4 - odd; 
		len += 4 - odd;
		pucDest += 4 - odd;
	}


	/* Copy the aligned DWs */
	pSrc = (uint32_t*) pucFlash;
	pDest = (uint32_t*) pucDest;
#endif

#if 0
// THT 082808: FOr MLC, this codes still work, but for peace of mind, take it out.
	// THT: Changed to use built-in kernel memcpy() to take advantage of Prefetch
if (gdebug) printk("%s: pucFlash=%p, len=%d\n", __FUNCTION__, pucFlash, len);
	memcpy(pucDest, pucFlash, len);

#else
	for (i=0; i< (len>>2); i++) {
		pucDest[i] = /* THT 8/29/06  cpu_to_be32 */(pucFlash[i]);
	}


#if 0
	/*
	 * Take care of the trailing odd bytes.  
	 * Can't use memcpy here, because the flash contents are in BE order
	 */
	odd = (len & 0x3);
	if (odd) {
		pucDest = (unsigned char*) pDest;

printk("****** WARNING: trailing odd bytes ************\n");	
		/* pSrc is now aligned on a DW boundary */
		u32.u = /*cpu_to_be32 */ (*pSrc);

		for (i=0; i<odd; i++) {
			pucDest[i] = u32.c[odd+i];
		}
	}
#endif // Trailing odd bytes
#endif

	return 0;
}
#endif // ifndef EDU

static int brcmnand_to_flash_memcpy32(struct brcmnand_chip* chip, L_OFF_T offset, const void* src, int len)
{
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
	u_char* flash = chip->vbase + offset;
#else
	u_char* flash = chip->vbase;
#endif
	int i;
	volatile uint32_t* pDest = (volatile uint32_t*) flash;
	volatile uint32_t* pSrc = (volatile uint32_t*) src;
#if 1
	if (unlikely((unsigned int) flash & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 dest=%p not DW aligned\n", flash);
		return -EINVAL;
	}
	if (unlikely((unsigned int) src & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 src=%p not DW aligned\n", src);
		return -EINVAL;
	}
	if (unlikely(len & 0x3)) {
		printk(KERN_ERR "brcmnand_memcpy32 len=%d not DW aligned\n", len);
		return -EINVAL;
	}
#endif

if (gdebug) printk("%s: flash=%p, len=%d, src=%p\n", __FUNCTION__, flash, len, src);
	memcpy(flash, src, len);
#if 0
	// THT Does not work for MLC when {FAST_PGM_RDIN, PARTIAL_PAGE_EN} = {0. 0}
	// Use memcpy to take advantage of Prefetch

#else
	for (i=0; i< (len>>2); i++) {
		pDest[i] = /* THT: 8/29/06 cpu_to_be32  */ (pSrc[i]);
	}
#endif

	return 0;
}

#ifdef CONFIG_MTD_BRCMNAND_EDU
/*
 * Returns     0: No errors
 *             1: Correctable error
 *            -1: Uncorrectable error
 */
static int brcmnand_verify_ecc(struct brcmnand_chip* this, int state)
{
    int err = 1;       //  1 is no error, 2 is ECC correctable, 3 is EDU ECC correctable, -2 is ECC non-corr, -3 is EDU ECC non-corr
    uint32_t intr;
    uint32_t status = 0;

    /* Only make sense on read */
    if (state != FL_READING) 
        return 0;

    intr = EDU_volatileRead(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_STATUS);
    
#ifdef ECC_CORRECTABLE_SIMULATION
    if(bEccCor)
    {
        intr |= BCHP_HIF_INTR2_CPU_STATUS_NAND_CORR_INTR_MASK;
    }
#endif     

#ifdef ECC_UNCORRECTABLE_SIMULATION
    if(bEccUncor)
    {
        intr |= BCHP_HIF_INTR2_CPU_STATUS_NAND_UNC_INTR_MASK;
    }
#endif     
    // Maybe an EDU BUG?
    if ((intr & BCHP_HIF_INTR2_CPU_STATUS_EDU_ERR_INTR_MASK) != 0x00000000)
    { 
        //Check EDU_ERR_STATUS:
        status = EDU_volatileRead(EDU_BASE_ADDRESS + EDU_ERR_STATUS);
        if((status & EDU_ERR_STATUS_NandECCuncor) != 0x00000000)
        {
            // EDU saw and NANDECCUNCORRERROR
            err = BRCMEDU_UNCORRECTABLE_ECC_ERROR;
        }

        if((status & EDU_ERR_STATUS_NandECCcor) != 0x00000000)
        {
            err = BRCMEDU_CORRECTABLE_ECC_ERROR;
        }         
    }
    
    if ((intr & BCHP_HIF_INTR2_CPU_STATUS_NAND_CORR_INTR_MASK) != 0x00000000)
    {

#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
        // Clear it
        this->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
#endif

        // Clear it
        this->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);
        
       
        err = BRCMNAND_CORRECTABLE_ECC_ERROR;

        // Clear the interrupt for next time
        EDU_volatileWrite(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_CLEAR, BCHP_HIF_INTR2_CPU_CLEAR_NAND_CORR_INTR_MASK); 
    }

    if ((intr & BCHP_HIF_INTR2_CPU_STATUS_NAND_UNC_INTR_MASK) != 0x00000000) 
    {
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
        // Clear it
        this->ctrl_write(BCHP_NAND_ECC_UNC_EXT_ADDR, 0);
#endif
        this->ctrl_write(BCHP_NAND_ECC_UNC_ADDR, 0);

        /*
         * If the block was just erased, and have not yet been written to, this will be flagged,
         * so this could be a false alarm
         */

        
        err = BRCMNAND_UNCORRECTABLE_ECC_ERROR;

        // Clear the interrupt for next time
        EDU_volatileWrite(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_CLEAR, BCHP_HIF_INTR2_CPU_CLEAR_NAND_UNC_INTR_MASK); 
    }

    return err;
}

#else

/*
 * Returns	 0: BRCMNAND_SUCCESS:	No errors
 *			 1: Correctable error
 *			-1: Uncorrectable error
 */
static int brcmnand_verify_ecc(struct brcmnand_chip* chip, int state)
{
	int err = 0;
	uint32_t addr;
	uint32_t extAddr = 0;

	/* Only make sense on read */
	if (state != FL_READING) 
		return BRCMNAND_SUCCESS;

	addr = chip->ctrl_read(BCHP_NAND_ECC_CORR_ADDR);
	if (addr) {

#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
		extAddr = chip->ctrl_read(BCHP_NAND_ECC_CORR_EXT_ADDR);
		// Clear it
		chip->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
#endif

		// Clear it
		chip->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);
		printk(KERN_WARNING "%s: Correctable ECC error at %08x:%08x\n", __FUNCTION__, extAddr, addr);
		err = BRCMNAND_CORRECTABLE_ECC_ERROR;
	}

	addr = chip->ctrl_read(BCHP_NAND_ECC_UNC_ADDR);
	if (addr) {
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
		extAddr = chip->ctrl_read(BCHP_NAND_ECC_UNC_EXT_ADDR);
		// Clear it
		chip->ctrl_write(BCHP_NAND_ECC_UNC_EXT_ADDR, 0);
#endif
		chip->ctrl_write(BCHP_NAND_ECC_UNC_ADDR, 0);

		/*
		 * If the block was just erased, and have not yet been written to, this will be flagged,
		 * so this could be a false alarm
		 */

		err = BRCMNAND_UNCORRECTABLE_ECC_ERROR;
	}
	return err;
}

#endif //#ifdef CONFIG_MTD_BRCMNAND_EDU


/**
 * brcmnand_wait - [DEFAULT] wait until the command is done
 * @param mtd		MTD device structure
 * @param state		state to select the max. timeout value
 *
 * Wait for command done. This applies to all BrcmNAND command
 * Read can take up to 53, erase up to ?s and program up to 30 clk cycle ()
 * according to general BrcmNAND specs
 */
static int brcmnand_wait(struct mtd_info *mtd, int state, uint32_t* pStatus)
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned long timeout;
	uint32_t ready;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(3000); // THT: 3secs, for now
	while (time_before(jiffies, timeout)) {
		PLATFORM_IOFLUSH_WAR();
		ready = chip->ctrl_read(BCHP_NAND_INTFC_STATUS);

		if (ready & BCHP_NAND_INTFC_STATUS_CTLR_READY_MASK) {
			*pStatus = ready;
			return 0;
		}

		if (state != FL_READING)
			cond_resched();
		//touch_softlockup_watchdog();
	}

	/*
	 * Get here on timeout
	 */
	return -ETIMEDOUT;
}


/* 
 * Returns 	 1: Success, correctable errors
 * 			 0: Success
 *			-1: Uncorectable error
 *			-2: Block is bad, returned from flash Status.
 *			-3: Timed out
 */
static int brcmnand_cache_is_valid(struct mtd_info* mtd,  int state, L_OFF_T offset) 
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned long timeout;
	uint32_t ready;

	
	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(3000); // 3 sec timeout for now
	while (time_before(jiffies, timeout)) {
		PLATFORM_IOFLUSH_WAR();
		ready = chip->ctrl_read(BCHP_NAND_INTFC_STATUS);

		if (ready & (BCHP_NAND_INTFC_STATUS_CTLR_READY_MASK | 0x1)) {
			int ecc;
			
			if (ready & 0x1) {
				printk(KERN_ERR "%s: Flash chip report error %08x\n", __FUNCTION__, ready);
				return BRCMNAND_FLASH_STATUS_ERROR;
			}

			//if (!raw) {
			ecc = brcmnand_verify_ecc(chip, state);
// Let caller handle it
//printk("%s: Possible Uncorrectable ECC error at offset %08x\n", __FUNCTION__, (unsigned long) offset);
				return ecc;
			//}
			//return BRCMNAND_SUCCESS;
		}
		if (state != FL_READING)
			cond_resched();

	}

	return BRCMNAND_TIMED_OUT; // TimeOut
}

#ifdef CONFIG_MTD_BRCMNAND_EDU

/* 
 * Returns      1: Success, no errors
 *              0: Timeout
 *            -1: Errors
 */
static int brcmnand_EDU_cache_is_valid(struct mtd_info* mtd,  int state, L_OFF_T offset) 
{
        uint32 rd_data = 0;
        int error = 0;

        rd_data = EDU_poll(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_STATUS, HIF_INTR2_EDU_DONE, HIF_INTR2_EDU_DONE);  

        if(rd_data != 0)
        {
            error = brcmnand_cache_is_valid(mtd, state, offset);
        }
        
        EDU_volatileWrite(EDU_BASE_ADDRESS  + EDU_DONE, 0x00000000);
        EDU_volatileWrite(EDU_BASE_ADDRESS  + EDU_ERR_STATUS, 0x00000000);
        EDU_volatileWrite(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_CLEAR, HIF_INTR2_EDU_CLEAR);    
       
        return error;
}

#endif  // CONFIG_MTD_BRCMNAND_EDU


static int brcmnand_select_cache_is_valid(struct mtd_info* mtd,  int state, L_OFF_T offset) 
{
    int ret = 0;
#ifdef CONFIG_MTD_BRCMNAND_EDU
    ret =   brcmnand_EDU_cache_is_valid(mtd,state,offset);  
#else
    ret =   brcmnand_cache_is_valid(mtd,state,offset);  
#endif
    return ret;
}
/* 
 * Returns 	 1: Success, no errors
 * 			 0: Timeout
 *			-1: Errors
 */
static int brcmnand_spare_is_valid(struct mtd_info* mtd,  int state, int raw) 
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned long timeout;
	uint32_t ready;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(3000);  // 3 sec timeout for now
	while (time_before(jiffies, timeout)) {
		PLATFORM_IOFLUSH_WAR();
		ready = chip->ctrl_read(BCHP_NAND_INTFC_STATUS);

		if (ready & BCHP_NAND_INTFC_STATUS_CTLR_READY_MASK) {
			int ecc;

			if (!raw) {
				ecc = brcmnand_verify_ecc(chip, state);
				if (ecc < 0) {
//printk("%s: Uncorrectable ECC error at offset %08x\n", __FUNCTION__, (unsigned long) offset);
					return -1;
				}
			}
			return 1;
		}
		if (state != FL_READING)
			cond_resched();
	}

	return 0; // Timed out
}

#ifdef CONFIG_MTD_BRCMNAND_EDU

static int brcmnand_EDU_write_is_complete(struct mtd_info *mtd, int* outp_needBBT)
{
    uint32 rd_data = 0;

// printk("%s\n", __FUNCTION__);

    *outp_needBBT = 1;
    
    rd_data = EDU_poll(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_STATUS, HIF_INTR2_EDU_DONE, HIF_INTR2_EDU_DONE);
        
    if ((rd_data & HIF_INTR2_EDU_DONE) == HIF_INTR2_EDU_DONE ) 
    {
        //Get status:
        *outp_needBBT = EDU_get_error_status_register();

        //Clear interrupt:
        EDU_volatileWrite(EDU_BASE_ADDRESS  + EDU_DONE, 0x00000000);
        EDU_volatileWrite(EDU_BASE_ADDRESS  + EDU_ERR_STATUS, 0x00000000);
        EDU_volatileWrite(EDU_BASE_ADDRESS  + BCHP_HIF_INTR2_CPU_CLEAR, HIF_INTR2_EDU_CLEAR);

        if (*outp_needBBT != 0)
        {
            printk("EDU_write_is_complete(): error 0x%08X\n", *outp_needBBT);
        }

        return 1;  //Poll success!
    }

    printk("EDU_write_is_complete(): error 2 rd_data: %08x\n", (unsigned int)rd_data);
    
    //Poll did not return HIF_INTR2_EDU_DONE:
    return 0;
}

#endif // CONFIG_MTD_BRCMNAND_EDU


static int brcmnand_write_is_complete(struct mtd_info *mtd, int* outp_needBBT)
{
	int err;
	uint32_t status;
	uint32_t flashStatus = 0;

	*outp_needBBT = 1;
	err = brcmnand_wait(mtd, FL_WRITING, &status);
	if (!err) {
		if (status & BCHP_NAND_INTFC_STATUS_CTLR_READY_MASK) {
			flashStatus = status & 0x01;
			*outp_needBBT = flashStatus; // 0 = write completes with no errors
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

static int brcmnand_select_write_is_complete(struct mtd_info *mtd, int* outp_needBBT)
{
    int ret = 0;
    
#ifdef CONFIG_MTD_BRCMNAND_EDU 
    //Check the state of the current lock of the device: 
    struct brcmnand_chip *this = mtd->priv;
    
    if (this->state == FL_WRITING)
    {
        ret = brcmnand_EDU_write_is_complete(mtd, outp_needBBT);
    }
    else
    {
        ret = brcmnand_write_is_complete(mtd, outp_needBBT);
    }
#else
    ret = brcmnand_write_is_complete(mtd, outp_needBBT);
#endif    

    return ret;
}



/**
 * brcmnand_transfer_oob - [Internal] Transfer oob to client buffer
 * @chip:	nand chip structure
 * @oob:	oob destination address
 * @ops:	oob ops structure
 */
static uint8_t *
brcmnand_transfer_oob(struct brcmnand_chip *chip, uint8_t *oob,
				  struct mtd_oob_ops *ops)
{
	size_t len = ops->ooblen;

	switch(ops->mode) {

	case MTD_OOB_PLACE:
	case MTD_OOB_RAW:
		memcpy(oob, chip->oob_poi + ops->ooboffs, len);
		return oob + len;

	case MTD_OOB_AUTO: {
		struct nand_oobfree *free = chip->ecclayout->oobfree;
		uint32_t boffs = 0, roffs = ops->ooboffs;
		size_t bytes = 0;

		for(; free->length && len; free++, len -= bytes) {
			/* Read request not from offset 0 ? */
			if (unlikely(roffs)) {
				if (roffs >= free->length) {
					roffs -= free->length;
					continue;
				}
				boffs = free->offset + roffs;
				bytes = min_t(size_t, len,
					      (free->length - roffs));
				roffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(oob, chip->oob_poi + boffs, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}

#ifdef CONFIG_MTD_BRCMNAND_EDU

/**
 * brcmnand_posted_read_cache - [BrcmNAND Interface] Read the 512B cache area
 * Assuming brcmnand_get_device() has been called to obtain exclusive lock
 * @param mtd        MTD data structure
 * @param oobarea    Spare area, pass NULL if not interested
 * @param buffer    the databuffer to put/get data, pass NULL if only spare area is wanted.
 * @param offset    offset to read from or write to, must be 512B aligned.
 * @param raw: Ignore BBT bytes when raw = 1
 *
 * Caller is responsible to pass a buffer that is
 * (1) large enough for 512B for data and optionally an oobarea large enough for 16B.
 * (2) 4-byte aligned.
 *
 * Read the cache area into buffer.  The size of the cache is mtd-->eccsize and is always 512B.
 */
static int brcmnand_posted_read_cache(struct mtd_info* mtd, 
        void* buffer, u_char* oobarea, L_OFF_T offset)
{

    int ecc;
#if 0
    L_OFF_T blockOffset;
    static int refresh_recursive = 0;
#endif    
    struct brcmnand_chip* this = mtd->priv;
    L_OFF_T sliceOffset = __ll_and32(offset, ~ (mtd->eccsize - 1));
    int i, ret = 0;
    int retries = 2, done = 0;
    uint32_t* p32 = (uint32_t*) oobarea;
    
    
#ifdef ECC_UNCORRECTABLE_SIMULATION
    uint8_t* my_buffer = NULL;
#endif    
    
if (gdebug > 3) {
printk("%s: offset=%s, oobarea=%p\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset), oobarea);}

    while (retries > 0 && !done) 
    {
        if (unlikely(__ll_isub(offset, sliceOffset))) {
            printk(KERN_ERR "%s: offset %s is not cache aligned, sliceOffset=%s, CacheSize=%d\n", 
                __FUNCTION__, __ll_sprintf(brcmNandMsg, offset), __ll_sprintf(brcmNandMsg, sliceOffset), mtd->eccsize);
            return -EINVAL;
        }

        this->ctrl_writeAddr(this, sliceOffset, 0);
        PLATFORM_IOFLUSH_WAR(); 

        ret = EDU_read(buffer, EDU_ldw);
	 if (ret)
	 	goto out;

        // Wait until cache is filled up
        ecc = brcmnand_select_cache_is_valid(mtd, FL_READING, offset);

        if (oobarea) 
        {
            PLATFORM_IOFLUSH_WAR();
            for (i = 0; i < 4; i++) 
            {
                p32[i] = be32_to_cpu (this->ctrl_read(BCHP_NAND_SPARE_AREA_READ_OFS_0 + i*4));
            }
            if (gdebug) {printk("%s: offset=%s, oob=\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, sliceOffset)); 
                                print_oobbuf(oobarea, 16);}
        }
        
        switch (ecc) 
        {
            case BRCMNAND_SUCCESS: /* Success, no errors */
            {
                ret = 0;            // Success!
                done = 1;
            }
            break;

            case BRCMNAND_CORRECTABLE_ECC_ERROR:
            {
#if 0            
                if (refresh_recursive == 0)
                {
                    printk("%s: ECC correctable error at %s, refreshing block...\n",__FUNCTION__,__ll_sprintf(brcmNandMsg, offset, this->xor_invert_val));

                    refresh_recursive = 1;

                    brcmnand_deduce_blockOffset(mtd, offset, &blockOffset);

                    ret = brcmnand_refresh_block(mtd, blockOffset);
                    
                    refresh_recursive = 0;
                    
                    if (ret == 0)
                    {
                        printk("%s: Block refreshed successfully\n",__FUNCTION__);
                        ret = -EECCCOR;  
                    }
                    else
                    {
                        printk("%s: Block refresh failure!\n",__FUNCTION__);
                    }
                }
#else
                ret = 0; // Success!  
#endif                
                done = 1;
            }
            break;
            
            case BRCMNAND_UNCORRECTABLE_ECC_ERROR:
            {
                /* Flash chip returns errors 

                || There is a bug in the controller, where if one reads from an erased block that has NOT been written to,
                || this error is raised.  
                || (Writing to OOB area does not have any effect on this bug)
                || The workaround is to also look into the OOB area, to see if they are all 0xFF
                
                */
                u_char oobbuf[16];
                int all00, allFF;

               // NAND CTRL BUG... EDU has stopped! Must copy buffer!!!
                memcpy(buffer, this->vbase, mtd->eccsize);

                if (!oobarea) 
                    oobarea = &oobbuf[0];
                p32 = (uint32_t*) oobarea;

                for (i = 0; i < 4; i++) {
                    p32[i] = /* THT 11-30-06 */ be32_to_cpu (this->ctrl_read(BCHP_NAND_SPARE_AREA_READ_OFS_0 + i*4));
                }

                all00 = (oobarea[6] == 0xff && oobarea[7] == 0xff && oobarea[8] == 0xff);
                allFF = (oobarea[6] == 0x00 && oobarea[7] == 0x00 && oobarea[8] == 0x00);
                if ( all00 || allFF) {
                    /* 
                     * For the first case, the slice is an erased block, and the ECC bytes are all 0xFF,
                     * for the 2nd, all bytes are 0xFF, so the Hamming Codes for it are all zeroes.
                     * The current version of the BrcmNAND controller treats these as un-correctable errors.
                     * For either case, fill data buffer with 0x00 or 0xff and return success.  The error has already
                     * been cleared inside brcmnand_verify_ecc.
                     * Both case will be handled correctly by the BrcmNand controller in later releases.
                     */
                    p32 = (uint32_t*) buffer;
                    for (i=0; i < mtd->eccsize/4; i++) {
                        p32[i] = 0xFFFFFFFF;
                    }
                    
              
                    ret = 0; // Success!

                }
                else 
                {
#ifdef ECC_UNCORRECTABLE_SIMULATION
                    if (bEccUncor)
                    {
                        printk("Inserting errors in buffer\n");
                        if (buffer != NULL)
                        {
                            my_buffer = (uint8_t*) buffer;
                            
                            //Invert data in buffer:
                            for (i = 0; i < mtd->eccsize; i++)
                            {
                                my_buffer[i] = ~my_buffer[i];
                            }
                        }
                    }
#endif 
                    /* Real error: Disturb read returns uncorrectable errors */

                    if (gdebug) printk("%s: ECC noncorrectable error at %s\n",__FUNCTION__, __ll_sprintf(brcmNandMsg, offset));

#if 0 
//commented because yaffs2 and jffs2 are taking care of marking the bad blocks whenever we return -EECCUNCOR                    

                    printk("%s: Marking bad block @%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset, this->xor_invert_val));
                    ret = this->block_markbad(mtd, offset);
#endif                    
                    ret = -EBADMSG;

                    
                }
                done = 1;
            }
            break;
            
            case BRCMEDU_CORRECTABLE_ECC_ERROR:
            {
                memcpy(buffer, this->vbase, mtd->eccsize);  
                ret = 0;            // Success!
                done = 1;
                if (gdebug) printk("%s: EDU Correctable ECC error: ret -EBADMSG !!!\n",__FUNCTION__);
            }
            break; 

            case BRCMEDU_UNCORRECTABLE_ECC_ERROR:
            {
                 printk("EDU_read45\n");
                // NAND CTRL BUG... EDU has stopped! BUT NO ERROR!!! Must copy buffer!!!
                memcpy(buffer, this->vbase, mtd->eccsize);  
                ret = 0;            // Success!
                done = 1;
                if (gdebug) printk("%s: EDU ECC noncorrectable error at %s",__FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
            }            
            break;            
            
            case BRCMNAND_TIMED_OUT:
            {
 printk("EDU_read60\n");
                //Read has timed out 
                printk(KERN_ERR "brcmnand_select_cache_is_valid has timed out.\n");
                ret = -ETIMEDOUT;
                done = 1;
            }
            break;

            default:
            {
 printk("EDU_read70\n");
                BUG_ON(1);
                /* Should never get here */
                ret = -EINVAL;
                done = 1;
            }
            break; 
        }//End of switch()
    }//End of while()

out:

    return ret;
}

#else // NO EDU PRESENT OR EDU DISABLED

/**
 * brcmnand_posted_read_cache - [BrcmNAND Interface] Read the 512B cache area
 * Assuming brcmnand_get_device() has been called to obtain exclusive lock
 * @param mtd		MTD data structure
 * @param oobarea	Spare area, pass NULL if not interested
 * @param buffer	the databuffer to put/get data, pass NULL if only spare area is wanted.
 * @param offset	offset to read from or write to, must be 512B aligned.
 *
 * Caller is responsible to pass a buffer that is
 * (1) large enough for 512B for data and optionally an oobarea large enough for 16B.
 * (2) 4-byte aligned.
 *
 * Read the cache area into buffer.  The size of the cache is mtd-->eccsize and is always 512B.
 */
static int brcmnand_posted_read_cache(struct mtd_info* mtd, 
		void* buffer, u_char* oobarea, L_OFF_T offset)
{
	struct brcmnand_chip* chip = mtd->priv;
	L_OFF_T sliceOffset = __ll_and32(offset, ~ (mtd->eccsize - 1));
	int i, ret;
	int retries = 2, done = 0;
	uint32_t* p32 = (uint32_t*) oobarea;

if (gdebug > 3 ) {
printk("%s: offset=%s, oobarea=%p\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset), oobarea);}

	while (retries > 0 && !done) {
		if (unlikely(__ll_isub(offset, sliceOffset))) {
			printk(KERN_ERR "%s: offset %08x is not cache aligned, sliceOffset=%08lx, CacheSize=%d\n", 
				__FUNCTION__, (unsigned int) offset, (unsigned long) sliceOffset, mtd->eccsize);
			return -EINVAL;
		}


		chip->ctrl_writeAddr(chip, sliceOffset, 0);
		PLATFORM_IOFLUSH_WAR();
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_PAGE_READ);

		// Wait until cache is filled up
		ret = brcmnand_select_cache_is_valid(mtd, FL_READING, offset);
		switch (ret) {
		case BRCMNAND_CORRECTABLE_ECC_ERROR: /* Success, no errors */
		case BRCMNAND_SUCCESS:
			if (buffer) {
				brcmnand_from_flash_memcpy32(chip, buffer, offset, mtd->eccsize);
			}

			if (oobarea) {
				PLATFORM_IOFLUSH_WAR();
				for (i = 0; i < 4; i++) {
					p32[i] = /* THT 11-30-06 */ be32_to_cpu (chip->ctrl_read(BCHP_NAND_SPARE_AREA_READ_OFS_0 + i*4));
				}
if (gdebug) {printk("%s: offset=%08x, oob=\n", __FUNCTION__, __ll_low(sliceOffset)); print_oobbuf(oobarea, 16);}
			}

			// ret = BRCMNAND_CORRECTABLE_ECC_ERROR; // Success
			done = 1;
			break;
			
		case BRCMNAND_UNCORRECTABLE_ECC_ERROR:
			{
				/* Flash chip returns errors 

				|| There is a bug in the controller, where if one reads from an erased block that has NOT been written to,
				|| this error is raised.  
				|| (Writing to OOB area does not have any effect on this bug)
				|| The workaround is to also look into the OOB area, to see if they are all 0xFF
				
				*/
				u_char oobbuf[16];
				int erased, allFF;
				int i;

				if (!oobarea) 
					oobarea = &oobbuf[0];
				p32 = (uint32_t*) oobarea;

				for (i = 0; i < 4; i++) {
					p32[i] = /* THT 11-30-06 */ be32_to_cpu (chip->ctrl_read(BCHP_NAND_SPARE_AREA_READ_OFS_0 + i*4));
				}
				if (chip->ecclevel == BRCMNAND_ECC_HAMMING) {
				erased = (oobarea[6] == 0xff && oobarea[7] == 0xff && oobarea[8] == 0xff);
				allFF = (oobarea[6] == 0x00 && oobarea[7] == 0x00 && oobarea[8] == 0x00);
if (gdebug > 3 ) {printk("%s: erased=%d, allFF=%d\n", __FUNCTION__, erased, allFF);}
				}
				else if (chip->ecclevel >= BRCMNAND_ECC_BCH_1 && chip->ecclevel <= BRCMNAND_ECC_BCH_12) {
					erased = allFF = 1;
					// For BCH-n, the ECC bytes are at the end of the OOB area
					for (i=chip->eccOobSize-chip->eccbytes; i<chip->eccOobSize; i++) {
						erased = erased && (oobarea[i] == 0xff);
						allFF = allFF && (oobarea[i] == 0x00);
					}
//if (gdebug > 3 ) 
{printk("%s: eccOobSize=%d, eccbytes=%d, erased=%d, allFF=%d\n", __FUNCTION__, 
chip->eccOobSize, chip->eccbytes, erased, allFF);}
				}
				else {
					printk("BUG: Unsupported ECC level %d\n", chip->ecclevel);
					BUG();
				}
						
				if ( erased || allFF) {
					/* 
					 * For the first case, the slice is an erased block, and the ECC bytes are all 0xFF,
					 * for the 2nd, all bytes are 0xFF, so the Hamming Codes for it are all zeroes.
					 * The current version of the BrcmNAND controller treats these as un-correctable errors.
					 * For either case, fill data buffer with 0xff and return success.  The error has already
					 * been cleared inside brcmnand_verify_ecc.
					 * Both case will be handled correctly by the BrcmNand controller in later releases.
					 */
					p32 = (uint32_t*) buffer;
					for (i=0; i < chip->eccsize/4; i++) {
						p32[i] = 0xFFFFFFFF;
					}
					ret = 0; // Success

				}
				else {
					/* Real error: Disturb read returns uncorrectable errors */
					ret = -EBADMSG; 
if (gdebug > 3 ) {printk("<-- %s: ret -EBADMSG\n", __FUNCTION__);}
				}
				done = 1;
				
				break;
			}
		case BRCMNAND_FLASH_STATUS_ERROR:
			printk(KERN_ERR "brcmnand_cache_is_valid returns 0\n");
			ret = -EBADMSG;
			done = 1;
			break;			
			
		case BRCMNAND_TIMED_OUT:
			//Read has timed out 
			printk(KERN_ERR "brcmnand_cache_is_valid returns 0\n");
			ret = -ETIMEDOUT;
			done = 1;
			break;

		default:
			BUG_ON(1);
			/* Should never gets here */
			ret = -EFAULT;
			done = 1;
			break; 
		}
	}

if (gdebug > 3 ) {
printk("<-- %s: offset=%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
print_databuf(buffer, 32);
}
	return ret;
}

#endif // CONFIG_MTD_BRCMNAND_EDU

/**
 * brcmnand_posted_read_oob - [BrcmNAND Interface] Read the spare area
 * @param mtd		MTD data structure
 * @param oobarea	Spare area, pass NULL if not interested
 * @param offset	offset to read from or write to
 *
 * This is a little bit faster than brcmnand_posted_read, making this command useful for improving
 * the performance of BBT management.
 * The 512B flash cache is invalidated.
 *
 * Read the cache area into buffer.  The size of the cache is mtd->writesize and is always 512B,
 * for this version of the BrcmNAND controller.
 */
static int brcmnand_posted_read_oob(struct mtd_info* mtd, 
		unsigned char* oobarea, L_OFF_T offset, int raw)
{
	struct brcmnand_chip* chip = mtd->priv;
	L_OFF_T sliceOffset = __ll_and32(offset, ~(mtd->eccsize - 1));
	int i, ret, done = 0;
	int retries = 5;
	
//char msg[20];

PRINTK("->%s: offset=%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
PRINTK("->%s: sliceOffset=%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, sliceOffset));
PRINTK("eccsize = %d\n", mtd->eccsize);

if (gdebug > 3 ) {
printk("-->%s: offset=%08x\n", __FUNCTION__, (uint32_t) offset); }
	while (retries > 0 && !done) {
		if (unlikely(__ll_isub(sliceOffset, offset))) {
			printk(KERN_ERR "%s: offset %s is not cache aligned\n", 
				__FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
			return -EINVAL;
		}

		chip->ctrl_writeAddr(chip, sliceOffset, 0);
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_SPARE_AREA_READ);

		// Wait until spare area is filled up
		switch (brcmnand_spare_is_valid(mtd, FL_READING, raw)) {
		case 1:
			if (oobarea) {
				uint32_t* p32 = (uint32_t*) oobarea;
				
				for (i = 0; i < 4; i++) {
					p32[i] = /* THT 11-30-06 */ be32_to_cpu /**/(chip->ctrl_read(BCHP_NAND_SPARE_AREA_READ_OFS_0 + (i<<2)));
				}
if (gdebug > 3) {printk("%s: offset=%08x, oob=\n", __FUNCTION__, __ll_low(sliceOffset)); print_oobbuf(oobarea, 16);}

			}
			
			ret = 0;
			done = 1;
			break;

		case -1:
			ret = -EBADMSG;
if (gdebug > 3 ) {printk("%s: ret = -EBADMSG\n", __FUNCTION__);}
			/* brcmnand_spare_is_valid also clears the error bit, so just retry it */
			retries--;
			break;
			
		case 0:
			//Read has timed out or read found bad block. TBD: Find out which is which
			ret = -ETIMEDOUT;
			done = 1;
			break;
			
		default:
			BUG_ON(1);
			/* NOTREACHED */
			ret = -EINVAL;
			done = 1;
			break; /* Should never gets here */
		}

	}	

if (gdebug > 3 ) {
printk("<--%s: offset=%08x\n", __FUNCTION__, (uint32_t) offset); 
print_oobbuf(oobarea, 16);}
	return ret;
}

#ifdef CONFIG_MTD_BRCMNAND_EDU
/**
 * brcmnand_posted_write - [BrcmNAND Interface] Write a buffer to the flash cache
 * Assuming brcmnand_get_device() has been called to obtain exclusive lock
 *
 * @param mtd        MTD data structure
 * @param buffer    the databuffer to put/get data
 * @param oobarea    Spare area, pass NULL if not interested
 * @param offset    offset to write to, and must be 512B aligned
 *
 * Write to the cache area TBD 4/26/06
 */
static int brcmnand_posted_write_cache(struct mtd_info *mtd,
        const void* buffer, const unsigned char* oobarea, L_OFF_T offset)
{
    uint32_t* p32;
    int i; 
    int ret;

    struct brcmnand_chip* this = mtd->priv;    
    int needBBT=0;
    L_OFF_T sliceOffset = __ll_and32(offset, ~ (mtd->eccsize - 1));


#ifdef WR_BADBLOCK_SIMULATION
    unsigned long tmp = (unsigned long) offset;
    DIunion wrFailLocationOffset;
#endif

// printk("%s\n", __FUNCTION__);
// printk("EDU10\n");
    if (unlikely(__ll_isub(sliceOffset, offset))) {
        printk(KERN_ERR "%s: offset %s is not cache aligned\n", 
            __FUNCTION__, __ll_sprintf(brcmNandMsg, offset));

        ret =  -EINVAL;
        goto out;
    }

    this->ctrl_writeAddr(this, sliceOffset, 0);

// printk("EDU20\n");

    if (oobarea) {
        p32 = (uint32_t*) oobarea;
if (gdebug) {printk("%s: oob=\n", __FUNCTION__); print_oobbuf(oobarea, 16);}
    }
    else {
        // Fill with 0xFF if don't want to change OOB
        p32 = (uint32_t*) &ffchars[0];
    }

// printk("EDU40\n");
    for (i = 0; i < 4; i++) {
        this->ctrl_write(BCHP_NAND_SPARE_AREA_WRITE_OFS_0 + i*4, /* THT 11-30-06 */ cpu_to_be32 /* */(p32[i]));
    }

    PLATFORM_IOFLUSH_WAR(); // Check if this line may be taken-out

#if 0
// printk("EDUWrite\n");
// printk("EDU_write: %08x\n", (uint32) EDU_ldw);
        if(this->options & NAND_COMPLEX_OOB_WRITE)
        {
                EDU_write((uint32)ffchars, (uint32) EDU_ldw);
                // printk("EDU45: NAND_COMPLEX_OOB_WRITE... must investigate!\n"); 
        }
        else
#endif
	{
		ret = EDU_write(buffer, EDU_ldw);
		if (ret) 
			goto out;
	}
// printk("EDU50\n");

    // Wait until flash is ready
    ret = brcmnand_select_write_is_complete(mtd, &needBBT);

#ifdef WR_BADBLOCK_SIMULATION
    if((tmp == wrBadBlockFailLocation) && (bScanBypass_badBlock == 0))
    {
        wrFailLocationOffset.s.high = 0;
        wrFailLocationOffset.s.low = wrBadBlockFailLocation;
        printk("Creating new bad block @ %s\n", __ll_sprintf(brcmNandMsg, wrFailLocationOffset.ll, this->xor_invert_val));
        needBBT = 1;
        ret = 1;
    }
#endif 

    if (ret) 
    {
        if (!needBBT) 
        {
            ret = 0;
            goto out;
        }
        else
        { // Need BBT
#if defined (ECC_CORRECTABLE_SIMULATION) || defined(ECC_UNCORRECTABLE_SIMULATION) || defined(WR_BADBLOCK_SIMULATION)
            printk("%s: Marking bad block @%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset, this->xor_invert_val));
#endif            
            ret = this->block_markbad(mtd, offset);
            ret = -EINVAL;
            //ret = -EINVAL;
            goto out;
        }
    }

    //Write has timed out or read found bad block. TBD: Find out which is which
    printk(KERN_INFO "%s: Timeout\n", __FUNCTION__);
    ret = -ETIMEDOUT;

out:
// printk("EDU99\n");

    return ret;
}

#else // NO EDU PRESENT OR EDU DISABLED

/**
 * brcmnand_posted_write - [BrcmNAND Interface] Write a buffer to the flash cache
 * Assuming brcmnand_get_device() has been called to obtain exclusive lock
 *
 * @param mtd		MTD data structure
 * @param buffer	the databuffer to put/get data
 * @param oobarea	Spare area, pass NULL if not interested
 * @param offset	offset to write to, and must be 512B aligned
 *
 * Write to the cache area TBD 4/26/06
 */
static int brcmnand_posted_write_cache(struct mtd_info *mtd,
		const void* buffer, const unsigned char* oobarea, L_OFF_T offset)
{
	struct brcmnand_chip* chip = mtd->priv;
	L_OFF_T sliceOffset = __ll_and32(offset, ~ (mtd->eccsize - 1));
	uint32_t* p32;
	int i, needBBT=0;
	int ret;

	//char msg[20];


if (gdebug > 3 ) {
printk("--> %s: offset=%sx\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
print_databuf(buffer, 32);}

	if (unlikely(__ll_isub(sliceOffset, offset))) {
		printk(KERN_ERR "%s: offset %s is not cache aligned\n", 
			__FUNCTION__, __ll_sprintf(brcmNandMsg, offset));

		ret =  -EINVAL;
		goto out;
	}
	chip->ctrl_writeAddr(chip, sliceOffset, 0);


	if (buffer) {
if (gdebug > 3 ) {print_databuf(buffer, 32);}
		brcmnand_to_flash_memcpy32(chip, offset, buffer, mtd->eccsize);
	}
#if 0 
	/* Must write data when NAND_COMPLEX_OOB_WRITE */
	else if (chip->options & NAND_COMPLEX_OOB_WRITE) {
		brcmnand_to_flash_memcpy32(chip, offset, ffchars, mtd->eccsize);
	}
#endif


//printk("30\n");
	if (oobarea) {
		p32 = (uint32_t*) oobarea;
if (gdebug > 3) {printk("%s: oob=\n", __FUNCTION__); print_oobbuf(oobarea, 16);}
	}
	else {
		// Fill with 0xFF if don't want to change OOB
		p32 = (uint32_t*) &ffchars[0];
	}

//printk("40\n");
	for (i = 0; i < 4; i++) {
		chip->ctrl_write(BCHP_NAND_SPARE_AREA_WRITE_OFS_0 + i*4, /* THT 11-30-06 */ cpu_to_be32 /* */(p32[i]));
	}

	PLATFORM_IOFLUSH_WAR();
	chip->ctrl_write(BCHP_NAND_CMD_START, OP_PROGRAM_PAGE);
//printk("50\n");

	// Wait until flash is ready
	if (brcmnand_write_is_complete(mtd, &needBBT)) {
		if (!needBBT) {
			ret = 0;
			goto out;
		}
	
		else { // Need BBT
			printk(KERN_WARNING "%s: Marking bad block @%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, offset));
//printk("80 block mark bad\n");
			ret = chip->block_markbad(mtd, offset);
			ret = -EINVAL;
			goto out;
		}
	}
	//Write has timed out or read found bad block. TBD: Find out which is which
	printk(KERN_INFO "%s: Timeout\n", __FUNCTION__);
	ret = -ETIMEDOUT;

out:
//printk("99\n");

	return ret;
}

#endif // CONFIG_EDU SUPPORT

/**
 * brcmnand_posted_write_oob - [BrcmNAND Interface] Write the spare area
 * @param mtd		MTD data structure
 * @param oobarea	Spare area, pass NULL if not interested.  Must be able to 
 *					hold mtd->oobsize (16) bytes.
 * @param offset	offset to write to, and must be 512B aligned
 *
 */
static int brcmnand_posted_write_oob(struct mtd_info *mtd,
		const unsigned char* oobarea, L_OFF_T offset)
{
	struct brcmnand_chip* chip = mtd->priv;
	L_OFF_T sliceOffset = __ll_and32(offset, ~ (mtd->eccsize - 1));
	uint32_t* p32;
	int i, needBBT=0;


if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) offset);
print_oobbuf(oobarea, 16);
}

	if (unlikely(__ll_isub(sliceOffset, offset))) {
		printk(KERN_ERR "%s: offset %08x is not cache aligned\n", 
			__FUNCTION__, (unsigned int) offset);
	}
	
	chip->ctrl_writeAddr(chip, sliceOffset, 0);

#if 0
	/* Must write data when NAND_COMPLEX_OOB_WRITE option is set */
	if (chip->options & NAND_COMPLEX_OOB_WRITE) {
		brcmnand_to_flash_memcpy32(chip, offset, ffchars, mtd->eccsize);
	}
#endif

	// assert oobarea here
	BUG_ON(!oobarea);	
	p32 = (uint32_t*) oobarea;
		
	for (i = 0; i < 4; i++) {
		chip->ctrl_write(BCHP_NAND_SPARE_AREA_WRITE_OFS_0 + i*4, /* THT 11-30-06 */ cpu_to_be32 (p32[i]));
	}

	PLATFORM_IOFLUSH_WAR();
#if 0
	if (chip->options & NAND_COMPLEX_OOB_WRITE) {
printk("****** Workaround, using OP_PROGRAM_PAGE instead of OP_PROGRAM_SPARE_AREA\n");
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_PROGRAM_PAGE);
	}
	else 
#endif
	{
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_PROGRAM_SPARE_AREA);
	}

	// Wait until flash is ready
	if (brcmnand_write_is_complete(mtd, &needBBT)) {
		return 0;
	}
	if (needBBT){
		int ret;
		
		printk(KERN_WARNING "%s: Marking bad block @%08x\n", __FUNCTION__, (unsigned int) offset);
		ret = chip->block_markbad(mtd, offset);
		return -EINVAL;
	}

	return -ETIMEDOUT;
	
}



/**
 * brcmnand_get_device - [GENERIC] Get chip for selected access
 * @param mtd		MTD device structure
 * @param new_state	the state which is requested
 *
 * Get the device and lock it for exclusive access
 */
static int brcmnand_get_device(struct mtd_info *mtd, int new_state)
{
	struct brcmnand_chip * chip = mtd->priv;

	if (chip) {
		DECLARE_WAITQUEUE(wait, current);

		/*
		 * Grab the lock and see if the device is available
		 */
		while (1) {
			spin_lock(&chip->chip_lock);

			if (chip->state == FL_READY) {
				chip->state = new_state;
				spin_unlock(&chip->chip_lock);
				break;
			}
			if (new_state == FL_PM_SUSPENDED) {
				spin_unlock(&chip->chip_lock);
				return (chip->state == FL_PM_SUSPENDED) ? 0 : -EAGAIN;
			}
			set_current_state(TASK_UNINTERRUPTIBLE);
			add_wait_queue(&chip->wq, &wait);
			spin_unlock(&chip->chip_lock);
			schedule();
			remove_wait_queue(&chip->wq, &wait);
		}

		return 0;
	}
	else
		return -EINVAL;
}

static struct brcmnand_chip* 
brcmnand_get_device_exclusive(void)
{
	struct brcmnand_chip * chip = (struct brcmnand_chip*) get_brcmnand_handle();
	struct mtd_info *mtd; 
	int ret;

	mtd = (struct mtd_info*) chip->priv;

	if (mtd) {
		ret = brcmnand_get_device(mtd, BRCMNAND_FL_XIP);
	}
	else 
		ret = -1;
	if (0 == ret)
		return chip;
	else
		return ((struct brcmnand_chip *) 0);
}




/**
 * brcmnand_release_device - [GENERIC] release chip
 * @param mtd		MTD device structure
 *
 * Deselect, release chip lock and wake up anyone waiting on the device
 */
static void brcmnand_release_device(struct mtd_info *mtd)
{
	struct brcmnand_chip * chip = mtd->priv;

	/* Release the chip */
	spin_lock(&chip->chip_lock);
	chip->state = FL_READY;
	wake_up(&chip->wq);
	spin_unlock(&chip->chip_lock);
}






/**
 * brcmnand_read_page - {REPLACABLE] hardware ecc based page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure.  The OOB buf is stored here on return
 * @buf:	buffer to store read data
 *
 * Not for syndrome calculating ecc controllers which need a special oob layout
 */
static int 
brcmnand_read_page(struct mtd_info *mtd,
				uint8_t *outp_buf, uint8_t* outp_oob, uint32_t page)
{
	struct brcmnand_chip *chip = (struct brcmnand_chip*) mtd->priv;
	int winslice;
	int dataRead = 0;
	int oobRead = 0;
	int ret = 0;
	L_OFF_T offset = __ll_LeftShift32(page, chip->page_shift);

//if (1/* (int) offset <= 0x2000 /*gdebug > 3 */) {
//printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) offset);}

	chip->pagebuf = page;

	for (winslice = 0; winslice < chip->eccsteps && ret == 0; winslice++) {
		ret = brcmnand_posted_read_cache(mtd, &outp_buf[dataRead], 
					outp_oob ? &outp_oob[oobRead] : NULL, 
					__ll_add32(offset, dataRead));
		
		if (ret == BRCMNAND_CORRECTABLE_ECC_ERROR) {
			(mtd->ecc_stats.corrected)++;
			ret = 0;
		} 
		else if (ret < 0) {
			printk(KERN_ERR "%s: posted read cache failed at offset=%08lx, ret=%d\n", 
				__FUNCTION__, (unsigned long) __ll_add32(offset, dataRead), ret);
			return ret;
		}
		dataRead += chip->eccsize;
		oobRead += chip->eccOobSize;
	}
	return ret;
}


/**
 * brcmnand_read_page_oob - {REPLACABLE] hardware ecc based page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure.  The OOB buf is stored in the oob_poi ptr on return
 *
 * Not for syndrome calculating ecc controllers which need a special oob layout
 */
static int 
brcmnand_read_page_oob(struct mtd_info *mtd, 
				uint8_t* outp_oob, uint32_t  page)
{
	struct brcmnand_chip *chip = (struct brcmnand_chip*) mtd->priv;
	int winslice;
	int dataRead = 0;
	int oobRead = 0;
	int corrected = 0; // Only update stats once per page
	int ret = 0;
	L_OFF_T offset = __ll_LeftShift32(page, chip->page_shift);


if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) offset);}

	chip->pagebuf = page;

	for (winslice = 0; winslice < chip->eccsteps && ret == 0; winslice++) {
//gdebug=4;
		ret = brcmnand_posted_read_oob(mtd, &outp_oob[oobRead], 
					__ll_add32(offset, dataRead), 1);
//gdebug=0;
		
		if (ret == BRCMNAND_CORRECTABLE_ECC_ERROR && !corrected) {
			(mtd->ecc_stats.corrected)++;
			corrected = 1;
			ret = 0;
		} 
		else if (ret < 0) {
			printk(KERN_ERR "%s: posted read oob failed at offset=%08lx, ret=%d\n", 
				__FUNCTION__, (unsigned long) __ll_add32(offset, dataRead), ret);
			return ret;
		}
		dataRead += chip->eccsize;
		oobRead += chip->eccOobSize;
	}

if (gdebug > 3 ) {
printk("<--%s offset=%08x\n", __FUNCTION__, __ll_low(offset));
print_oobbuf(outp_oob, mtd->oobsize); }
	return ret;
}

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
static int brcmnand_refresh_blk(struct mtd_info *mtd, loff_t from)
{
	struct brcmnand_chip *this = mtd->priv;
	int i, j, k, numpages, ret, count = 0, nonecccount = 0;
	uint8_t *blk_buf;	/* Store one block of data (including OOB) */
	unsigned int realpage, pg_idx, oob_idx;
	struct erase_info *instr;
	//int gdebug = 1; 
	struct nand_ecclayout *oobinfo;
	uint8_t *oobptr;
	uint32_t *oobptr32, blkbegin;
	unsigned int block_size;


#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	this->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
#endif
	this->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);

	DEBUG(MTD_DEBUG_LEVEL3, "Inside %s:\n", __FUNCTION__, __ll_low(from));
	printk(KERN_INFO "%s: Performing block refresh to single bit ECC error\n", __FUNCTION__);
	pg_idx = 0;
	oob_idx = mtd->writesize;
	numpages = mtd->erasesize/mtd->writesize;
	block_size = (1 << this->erase_shift);
	blkbegin = (uint32_t) (from & (~(mtd->erasesize-1)));
	realpage = (unsigned int)(blkbegin >> this->page_shift);

	blk_buf = (uint8_t *) BRCMNAND_malloc(numpages*(mtd->writesize + mtd->oobsize));
	if (unlikely(blk_buf == NULL)) {
		printk(KERN_ERR "%s: buffer allocation failed\n", __FUNCTION__);
		return -1;
	}

	memset(blk_buf, 0xff, numpages*(mtd->writesize + mtd->oobsize));

	if (unlikely(gdebug > 0)) {
		printk("---> %s: from = %08x, numpages = %d, realpage = %x\n",\
				__FUNCTION__, (uint32_t) from, numpages, realpage);
		printk("     Locking flash for read ... \n");
	}

	/* Read an entire block */
	brcmnand_get_device(mtd, FL_READING);
	for (i = 0; i < numpages; i++) {
		ret = brcmnand_read_page(mtd, blk_buf+pg_idx, blk_buf+oob_idx, realpage);
		if (ret < 0) {
			BRCMNAND_free(blk_buf);
			brcmnand_release_device(mtd);
			return -1;
		}
		//printk("DEBUG -> Reading %d realpage = %x %x ret = %d oob = %x\n", i, realpage, *(blk_buf+pg_idx), ret, *(blk_buf + oob_idx));
		//print_oobbuf(blk_buf+oob_idx, mtd->oobsize);
		pg_idx += mtd->writesize + mtd->oobsize;
		oob_idx += mtd->oobsize + mtd->writesize;
		realpage++;
	}
	if (unlikely(gdebug > 0)) {
		printk("---> %s:  Read -> erase\n", __FUNCTION__);
	}
	this->state = FL_ERASING;

	/* Erase the block */
	instr = kmalloc(sizeof(struct erase_info), GFP_KERNEL);
	if (instr == NULL) {
		printk(KERN_WARNING "kmalloc for erase_info failed\n");
		BRCMNAND_free(blk_buf);
		brcmnand_release_device(mtd);
		return -ENOMEM;
	}
	memset(instr, 0, sizeof(struct erase_info));
	instr->mtd = mtd;
	instr->addr = blkbegin;
	instr->len = mtd->erasesize;
	if (unlikely(gdebug > 0)) {
		printk("DEBUG -> erasing %s, %x %d\n", __ll_sprintf(brcmNandMsg, instr->addr), instr->len, this->state);
	}
	ret = brcmnand_erase_nolock(mtd, instr, 0);
	if (ret) {
		BRCMNAND_free(blk_buf);
		kfree(instr);
		brcmnand_release_device(mtd);
		printk(KERN_WARNING " %s Erase failed %d\n", __FUNCTION__, ret);
		return ret;
	}
	kfree(instr);

	/* Write the entire block */
	pg_idx = 0;
	oob_idx = mtd->writesize;
	realpage = (unsigned int)(blkbegin >> this->page_shift);
	if (unlikely(gdebug > 0)) {
		printk("---> %s: Erase -> write ... %d\n", __FUNCTION__, this->state);
	}
	oobinfo = this->ecclayout;
	this->state = FL_WRITING;
	for (i = 0; i < numpages; i++) {
		/* Avoid writing empty pages */
		count = 0;
		nonecccount = 0;
		oobptr = (uint8_t *) (blk_buf + oob_idx);
		oobptr32 = (uint32_t *) (blk_buf + oob_idx);
		for (j = 0; j < oobinfo->eccbytes; j++) {
			if (oobptr[oobinfo->eccpos[j]] == 0xff) { count++; }
		}
		for (k = 0; k < mtd->oobsize/4; k++) {
			if (oobptr32[k] == 0xffffffff) { nonecccount++; }
		}
		/* Skip this page if ECC is 0xff */
		if (count == j && nonecccount == k) {
			pg_idx += mtd->writesize + mtd->oobsize;
			oob_idx += mtd->oobsize + mtd->writesize;
			realpage++;
			continue;
		}
		/* Skip this page, but write the OOB */
		if (count == j && nonecccount != k) {
			ret = this->write_page_oob(mtd, blk_buf + oob_idx, realpage);
			if (ret) {
				BRCMNAND_free(blk_buf);
				brcmnand_release_device(mtd);
				return ret;
			}
			pg_idx += mtd->writesize + mtd->oobsize;
			oob_idx += mtd->oobsize + mtd->writesize;
			realpage++;
			continue;
		}
		for (j = 0; j < oobinfo->eccbytes; j++) {
			oobptr[oobinfo->eccpos[j]] = 0xff;
		}
		ret = this->write_page(mtd, blk_buf+pg_idx, blk_buf+oob_idx, realpage);
		if (ret) {
			BRCMNAND_free(blk_buf);
			brcmnand_release_device(mtd);
			return ret; 
		}
		pg_idx += mtd->writesize + mtd->oobsize;
		oob_idx += mtd->oobsize + mtd->writesize;
		realpage++;
	}
	brcmnand_release_device(mtd);
	BRCMNAND_free(blk_buf);
	printk(KERN_INFO "%s: block refresh succes\n", __FUNCTION__);

	return 0;
}
#endif


/**
 * brcmnand_do_read_ops - [Internal] Read data with ECC
 *
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:		oob ops structure
 * @raw:		read raw data format when TRUE
 *
 * Internal function. Called with chip held.
 */
static int brcmnand_do_read_ops(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	unsigned int /*chipnr, page, */ realpage, col, bytes;
	int aligned;
	struct brcmnand_chip *chip = mtd->priv;
	struct mtd_ecc_stats stats;
	//int blkcheck = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;
	//int sndcmd = 1;
	int ret = 0;
	uint32_t readlen = ops->len;
	uint8_t *bufpoi, *oob, *buf;

	stats = mtd->ecc_stats;

	// THT: BrcmNAND controller treats multiple chip as one logical chip.
	//chipnr = (int)(from >> chip->chip_shift);
	//chip->select_chip(mtd, chipnr);

	realpage = (unsigned int)(from >> chip->page_shift);
	//page = realpage & chip->pagemask;

	col = (int)(from & (mtd->writesize - 1));
	chip->oob_poi = BRCMNAND_OOBBUF(chip->buffers);

	buf = ops->datbuf;
	oob = ops->oobbuf;

	while(1) {
		bytes = min(mtd->writesize - col, readlen);
		aligned = (bytes == mtd->writesize);

		/* Is the current page in the buffer ? */
		if ( 1 /*realpage != chip->pagebuf */ || oob) {
			bufpoi = aligned ? buf : chip->buffers->databuf;

			ret = chip->read_page(mtd, bufpoi, chip->oob_poi, realpage);
			if (ret < 0)
				break;

			/* Transfer not aligned data */
			if (!aligned) {
				chip->pagebuf = realpage;
				memcpy(buf, chip->buffers->databuf + col, bytes);
			}

			buf += bytes;

			if (unlikely(oob)) {
				/* Raw mode does data:oob:data:oob */
				if (ops->mode != MTD_OOB_RAW)
					oob = brcmnand_transfer_oob(chip, oob, ops);
				else {
					buf = brcmnand_transfer_oob(chip, buf, ops);
				}
			}

#if 0
			if (!(chip->options & NAND_NO_READRDY)) {
				/*
				 * Apply delay or wait for ready/busy pin. Do
				 * this before the AUTOINCR check, so no
				 * problems arise if a chip which does auto
				 * increment is marked as NOAUTOINCR by the
				 * board driver.
				 */
				if (!chip->dev_ready)
					udelay(chip->chip_delay);
				else
					nand_wait_ready(mtd);
			}
#endif
		} else {
		
			memcpy(buf, chip->buffers->databuf + col, bytes);
			buf += bytes;
		}

		readlen -= bytes;

		if (!readlen)
			break;

		/* For subsequent reads align to page boundary. */
		col = 0;
		/* Increment page address */
		realpage++;

#if 0
		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}

		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
		 */
		if (!NAND_CANAUTOINCR(chip) || !(page & blkcheck))
			sndcmd = 1;
#endif
	}

	ops->retlen = ops->len - (size_t) readlen;

	if (ret)
		return ret;

	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;

	return  mtd->ecc_stats.corrected - stats.corrected ? -EUCLEAN : 0;
}



/**
 * brcmnand_read - [MTD Interface] MTD compability function for nand_do_read_ecc
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @len:	number of bytes to read
 * @retlen:	pointer to variable to store the number of read bytes
 * @buf:	the databuffer to put data
 *
 * Get hold of the chip and call nand_do_read
 */
static int brcmnand_read(struct mtd_info *mtd, loff_t from, size_t len,
		     size_t *retlen, uint8_t *buf)
{
	struct brcmnand_chip *chip = mtd->priv;
	int ret;
#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
	int status;
#endif

	DEBUG(MTD_DEBUG_LEVEL3, "%s: from=%08x\n", __FUNCTION__, __ll_low(from));

if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) from);}


	/* Do not allow reads past end of device */
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(from, len), MTD_SIZE(mtd)))) 
  #else
	if (unlikely(from + len) > mtd->size) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(from, len), chip->mtdSize)))
#endif
		return -EINVAL;
	if (!len)
		return 0;

	brcmnand_get_device(mtd, FL_READING);

	chip->ops.mode = MTD_OOB_AUTO;
	chip->ops.len = len;
	chip->ops.datbuf = buf;
	chip->ops.oobbuf = NULL;

	ret = brcmnand_do_read_ops(mtd, from, &chip->ops);

	*retlen = chip->ops.retlen;

	brcmnand_release_device(mtd);

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
	if (unlikely(ret == -EUCLEAN && !atomic_read(&inrefresh))) {
		atomic_inc(&inrefresh);
		if(brcmnand_refresh_blk(mtd, from) == 0) { 
			ret = 0; 
		}
		if (likely(chip->cet)) {
			if (likely(chip->cet->flags != BRCMNAND_CET_DISABLED)) {
				if (brcmnand_cet_update(mtd, from, &status) == 0) {
					if (status) {
						ret = -EUCLEAN;
					} else {
						ret = 0;
					}
				}
				if (gdebug > 3) {
					printk(KERN_INFO "DEBUG -> %s ret = %d, status = %d\n", __FUNCTION__, ret, status);
				}
			}
		}
		atomic_dec(&inrefresh);
	}
#endif
	return ret;
}



/**
 * brcmnand_do_read_oob - [Intern] BRCMNAND read out-of-band
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:	oob operations description structure
 *
 * BRCMNAND read out-of-band data from the spare area
 */
static int brcmnand_do_read_oob(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	int realpage = 1;
	struct brcmnand_chip *chip = mtd->priv;
	//int blkcheck = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;
	int readlen = ops->len;
	uint8_t *buf = ops->oobbuf;
	int ret = 0;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: from = 0x%08Lx, len = %i\n",
	      __FUNCTION__, (unsigned long long)from, readlen);

	//chipnr = (int)(from >> chip->chip_shift);
	//chip->select_chip(mtd, chipnr);

	/* Shift to get page */
	realpage = (int)(from >> chip->page_shift);
	//page = realpage & chip->pagemask;

	chip->oob_poi = BRCMNAND_OOBBUF(chip->buffers);

	while(1) {
//		sndcmd = chip->ecc.read_oob(mtd, chip, page, sndcmd);
		ret = chip->read_page_oob(mtd, chip->oob_poi, realpage);

		buf = brcmnand_transfer_oob(chip, buf, ops);

#if 0
		if (!(chip->options & NAND_NO_READRDY)) {
			/*
			 * Apply delay or wait for ready/busy pin. Do this
			 * before the AUTOINCR check, so no problems arise if a
			 * chip which does auto increment is marked as
			 * NOAUTOINCR by the board driver.
			 */
			if (!chip->dev_ready)
				udelay(chip->chip_delay);
			else
				nand_wait_ready(mtd);
		}
#endif
		readlen -= ops->ooblen;
		if (!readlen)
			break;

		/* Increment page address */
		realpage++;

#if 0
		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}


		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
		 */
		if (!NAND_CANAUTOINCR(chip) || !(page & blkcheck))
			sndcmd = 1;
#endif
	}

	ops->retlen = ops->len;
	return 0;
}


/**
 * brcmnand_read_oob - [MTD Interface] NAND read data and/or out-of-band
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:	oob operation description structure
 *
 * NAND read data and/or out-of-band data
 */
static int brcmnand_read_oob(struct mtd_info *mtd, loff_t from,
			 struct mtd_oob_ops *ops)
{
	struct brcmnand_chip *chip = mtd->priv;
	int ret = -ENOTSUPP;
	//int raw;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: from=%08x\n", __FUNCTION__, __ll_low(from));
	
	ops->retlen = 0;

	/* Do not allow reads past end of device */
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(from, ops->len), MTD_SIZE(mtd))))
  #else
	if (unlikely(from + ops->len) > mtd->size) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(from, ops->len), chip->mtdSize)))
#endif
	{
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt read beyond end of device\n", __FUNCTION__);
		return -EINVAL;
	}

	brcmnand_get_device(mtd, FL_READING);

#if 0
	switch(ops->mode) {
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
		raw = 0;
		break;

	case MTD_OOB_RAW:
		raw = 1;
		break;

	default:
		goto out;
	}
#endif

	if (!ops->datbuf)
		ret = brcmnand_do_read_oob(mtd, from, ops);
	else
		ret = brcmnand_do_read_ops(mtd, from, ops);


// out:
	brcmnand_release_device(mtd);
if (gdebug > 3 ) {printk("<-- %s: ret=%d\n", __FUNCTION__, ret);}
	return ret;
}





#if 0 //def CONFIG_MTD_BRCMNAND_VERIFY_WRITE
/*
 * Returns 0 on success, 
 */
static int brcmnand_verify_pageoob_priv(struct mtd_info *mtd, loff_t offset, 
	const u_char* fsbuf, int fslen, u_char* oob_buf, int ooblen, struct nand_oobinfo* oobsel, 
	int autoplace, int raw)
{
	//struct brcmnand_chip * chip = mtd->priv;
	int ret = 0;
	int complen;

	
	if (autoplace) {

		complen = min_t(int, ooblen, fslen);

		/* We may have read more from the OOB area, so just compare the min of the 2 */
		if (complen == fslen) {
			ret = memcmp(fsbuf, oob_buf, complen);
			if (ret) {
{
printk("Autoplace Comparison failed at %08x, ooblen=%d fslen=%d left=\n", 
	__ll_low(offset), ooblen, fslen);
print_oobbuf(fsbuf, fslen);
printk("\nRight=\n"); print_oobbuf(oob_buf, ooblen);
dump_stack();
}
				goto comparison_failed;
			}
		}
		else {
printk("%s: OOB comparison failed, ooblen=%d is less than fslen=%d\n", 
		__FUNCTION__, ooblen, fslen);
			return  -EBADMSG;
		}
	}
	else { // No autoplace.  Skip over non-freebytes

		/* 
		 * THT:
		 * WIth YAFFS1, the FS codes overwrite an already written chunks quite a lot
		 * (without erasing it first, that is!!!!!)
		 * For those write accesses, it does not make sense to check the write ops
		 * because they are going to fail every time
		 */
		

#if 0
		int i, len; 
		
		for (i = 0; oobsel->oobfree[i][1] && i < ARRAY_SIZE(oobsel->oobfree); i++) {
			int from = oobsel->oobfree[i][0];
			int num = oobsel->oobfree[i][1];
			int len1 = num;

			if (num == 0) break; // End of oobsel
			
			if ((from+num) > fslen) len1 = fslen-from;
			ret = memcmp(&fsbuf[from], &oob_buf[from], len1);
			if (ret) {
				printk(KERN_ERR "%s: comparison at offset=%08x, i=%d from=%d failed., num=%d\n", 
					__FUNCTION__, i, __ll_low(offset), from, num); 
if (gdebug > 3) 
{
printk("No autoplace Comparison failed at %08x, ooblen=%d fslen=%d left=\n", 
	__ll_low(offset), ooblen, fslen);
print_oobbuf(&fsbuf[0], fslen);
printk("\nRight=\n"); print_oobbuf(&oob_buf[0], ooblen);
dump_stack();
}
				goto comparison_failed;
			}
			if ((from+num) >= fslen) break;
			len += num;
		}
#endif
	}
	return ret;


comparison_failed:
	{
		//unsigned long nand_timing1 = brcmnand_ctrl_read(BCHP_NAND_TIMING_1);
		//unsigned long nand_timing2 = brcmnand_ctrl_read(BCHP_NAND_TIMING_2);
		//u_char raw_oob[64];
		//int retlen;
		//struct nand_oobinfo noauto_oobsel;

		printk("Comparison Failed\n");
		print_diagnostics();
		
		//noauto_oobsel = *oobsel;
		//noauto_oobsel.useecc = MTD_NANDECC_PLACEONLY;
		//brcmnand_read_pageoob(mtd, offset, raw_oob, &retlen, &noauto_oobsel, 0, raw);
//if (gdebug) { printk("oob="); print_oobbuf(raw_oob, retlen);}
//printk("<-- %s: comparison failed\n", __FUNCTION__);

	
		return -EBADMSG;
	}
}



/**
 * brcmnand_verify_page - [GENERIC] verify the chip contents after a write
 * @param mtd		MTD device structure
 * @param dbuf		the databuffer to verify
 * @param dlen		the length of the data buffer, and should be less than mtd->writesize
 * @param fsbuf		the length of the file system OOB data and should be exactly
 *                             chip->oobavail (for autoplace) or mtd->oobsize otherise
  *					bytes to verify.
 *
 * Assumes that lock on.  Munges the internal data and OOB buffers.
 */
//#define MYDEBUG
static u_char data_buf[2048];

static int brcmnand_verify_page(struct mtd_info *mtd, loff_t addr, const u_char *dbuf, int dlen, 
		u_char* fsbuf, int fslen, struct nand_oobinfo* oobsel, int autoplace
		)
{
	//struct brcmnand_chip * chip = mtd->priv;
	u_char oob_buf [64];
	int ret = 0;
	int ooblen=0, datalen=0;
	//int complen;
	u_char* oobbuf = (fsbuf && fslen > 0) ? oob_buf : NULL;
	uint32_t page;

if (gdebug) printk("%s: oobbuf=%p\n", __FUNCTION__, oobbuf);

	page = __ll_RightShift32(addr, mtd->page_shift);
	// Must read entire page
	ret = brcmnand_read_page(mtd, data_buf, oobbuf, page);
	if (ret) {
		printk(KERN_ERR "%s: brcmnand_read_page at %08x failed ret=%d\n", 
			__FUNCTION__, (unsigned int) addr, ret);
		return ret;
	}
if (gdebug) printk("%s: fsdlen=%d, fslen=%d, datalen=%d, ooblen=%d\n", __FUNCTION__, 
	dlen, fslen, datalen, ooblen);

	/* 
	 * If there are no Input ECC bytes, there is nothing to verify, reading the page and checking the ECC status
	 * flag should be enough
	 */
	if (!fsbuf || fslen <= 0)
		return 0;
	
	// We only verify the ECC bytes.
	ret = brcmnand_verify_pageoob_priv(mtd, addr, fsbuf, fslen, oob_buf, ooblen, oobsel, autoplace, 0);
	if (ret) {
		return ret;
	}

	// but only verify dlen bytes	
	ret = memcmp(data_buf, dbuf, dlen);

	return ret;
}

/**
 * brcmnand_verify_pageoob - [GENERIC] verify the chip contents after a write
 * @param mtd		MTD device structure
 * @param dbuf		the databuffer to verify
 * @param dlen		the length of the data buffer, and should be less than mtd->writesize
 * @param fsbuf		the file system OOB data 
 * @param fslen		the length of the file system buffer
 * @param oobsel		Specify how to write the OOB data
 * @param autoplace	Specify how to write the OOB data
 * @param raw		Ignore the Bad Block Indicator when true
 *
 * Assumes that lock on.  Munges the OOB internal buffer.
 */
static int brcmnand_verify_pageoob(struct mtd_info *mtd, loff_t addr, const u_char* fsbuf, int fslen,
		struct nand_oobinfo *oobsel, int autoplace, int raw)
{
//	struct brcmnand_chip * chip = mtd->priv;
	//u_char* data_buf = chip->data_buf;
	u_char oob_buf[64]; // = chip->oob_buf;
	int ret = 0;
	//int complen;
	//char tmpfsbuf[64]; // Max oob size we support.
	int ooblen = 0;

if(gdebug) printk("-->%s addr=%08x, fslen=%d, autoplace=%d, raw=%d\n", __FUNCTION__, __ll_low(addr),
	fslen, autoplace, raw);

	// Must read entire page
	ret = brcmnand_read_pageoob(mtd, addr, oob_buf, &ooblen, oobsel, autoplace, raw);

	if (ret) {
		printk(KERN_ERR "%s: brcmnand_read_page at %08x failed ret=%d\n", 
			__FUNCTION__, (unsigned int) addr, ret);
		return ret;
	}

if(gdebug) printk("%s: Calling verify_pageoob_priv(addr=%08x, fslen=%d, ooblen=%d\n", 
	__FUNCTION__, __ll_low(addr), fslen, ooblen);
	ret = brcmnand_verify_pageoob_priv(mtd, addr, fsbuf, fslen, oob_buf, ooblen, oobsel, autoplace, raw);

	return ret;
}



#else
#define brcmnand_verify_page(...)	(0)
#define brcmnand_verify_pageoob(...)		(0)
//#define brcmnand_verify_oob(...)		(0)
#endif



/**
 * brcmnand_write_page - [INTERNAL] write one page
 * @mtd:	MTD device structure
 * @chip:	NAND chip descriptor
 * @buf:	the data to write
 * @page:	page number to write
 * @cached:	cached programming
 */
static int brcmnand_write_page(struct mtd_info *mtd,
			   const uint8_t *inp_buf, const uint8_t* inp_oob, uint32_t page)
{
	struct brcmnand_chip *chip = (struct brcmnand_chip*) mtd->priv;
	int winslice;
	int dataWritten = 0;
	int oobWritten = 0;
	int ret = 0;
	L_OFF_T offset = __ll_LeftShift32(page, chip->page_shift);


if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) offset);}

	chip->pagebuf = page;

	for (winslice = 0; winslice < chip->eccsteps && ret == 0; winslice++) {
		ret = brcmnand_posted_write_cache(mtd, &inp_buf[dataWritten], 
					inp_oob ? &inp_oob[oobWritten]  : NULL, 
					__ll_add32(offset, dataWritten));
		
		if (ret < 0) {
			printk(KERN_ERR "%s: brcmnand_posted_write_cache failed at offset=%08lx, ret=%d\n", 
				__FUNCTION__, (unsigned long) __ll_add32(offset, dataWritten), ret);
			return ret;
		}
		dataWritten += chip->eccsize;
		oobWritten += chip->eccOobSize;
	}

	// TBD
	ret = brcmnand_verify_page();

	return ret;
}


/**
 * brcmnand_fill_oob - [Internal] Transfer client buffer to oob
 * @chip:	nand chip structure
 * @oob:	oob data buffer
 * @ops:	oob ops structure
 *
 * Returns the pointer to the OOB where next byte should be read
 */
static uint8_t *
brcmnand_fill_oob(struct brcmnand_chip *chip, uint8_t *oob, struct mtd_oob_ops *ops)
{
	size_t len = ops->ooblen;

	switch(ops->mode) {

	case MTD_OOB_PLACE:
	case MTD_OOB_RAW:
		memcpy(chip->oob_poi + ops->ooboffs, oob, len);
		return oob + len;

	case MTD_OOB_AUTO: {
		struct nand_oobfree *free = chip->ecclayout->oobfree;
		uint32_t boffs = 0, woffs = ops->ooboffs;
		size_t bytes = 0;

		for(; free->length && len; free++, len -= bytes) {
			/* Write request not from offset 0 ? */
			if (unlikely(woffs)) {
				if (woffs >= free->length) {
					woffs -= free->length;
					continue;
				}
				boffs = free->offset + woffs;
				bytes = min_t(size_t, len,
					      (free->length - woffs));
				woffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(chip->oob_poi + boffs, oob, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}


#define NOTALIGNED(x) (x & (mtd->writesize-1)) != 0

/**
 * brcmnand_do_write_ops - [Internal] BRCMNAND write with ECC
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operations description structure
 *
 * BRCMNAND write with ECC
 */
static int brcmnand_do_write_ops(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int realpage, blockmask;
	struct brcmnand_chip *chip = mtd->priv;
	uint32_t writelen = ops->len;
	uint8_t *oob = ops->oobbuf;
	uint8_t *buf = ops->datbuf;
	int bytes = mtd->writesize;
	int ret = 0;

DEBUG(MTD_DEBUG_LEVEL3, "-->%s, offset=%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, to));

	ops->retlen = 0;

	/* reject writes, which are not page aligned */
	if (NOTALIGNED(to) || NOTALIGNED(ops->len)) {
		printk(KERN_NOTICE "nand_write: "
		       "Attempt to write not page aligned data\n");
		return -EINVAL;
	}

	if (!writelen)
		return 0;

/* BrcmNAND multi-chips are treated as one logical chip *
	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);
*/

#if 0
/* THT TBD */
	/* Check, if it is write protected */
	if (nand_check_wp(mtd))
		return -EIO;
#endif

	realpage =__ll_RightShift(to, chip->page_shift);
	//page = realpage & chip->pagemask;
	blockmask = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;

	/* Invalidate the page cache, when we write to the cached page */
	if (!__ll_is_greater(to, (chip->pagebuf << chip->page_shift)) &&
	    __ll_is_greater(__ll_add32(to, ops->len), __ll_LeftShift32(chip->pagebuf , chip->page_shift) )) {
		chip->pagebuf = -1;
	}

	/* THT: Provide buffer for brcmnand_fill_oob */
	if (unlikely(oob)) {
		chip->oob_poi = BRCMNAND_OOBBUF(chip->buffers);
	}
	else {
		chip->oob_poi = NULL;
	}

	while(1) {
		if (unlikely(oob)) {
			oob = brcmnand_fill_oob(chip, oob, ops);
			/* THT: oob now points to where to read next, 
			 * chip->oob_poi contains the OOB to be written
			 */
		}

		ret = chip->write_page(mtd, buf, chip->oob_poi, realpage);
		if (ret)
			break;

		writelen -= bytes;
		if (!writelen)
			break;

		buf += bytes;
		realpage++;

#if 0
		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
#endif
	}

	if (unlikely(oob))
		memset(chip->oob_poi, 0xff, mtd->oobsize);

	ops->retlen = ops->len - writelen;
	DEBUG(MTD_DEBUG_LEVEL3, "<-- %s\n", __FUNCTION__);
	return ret;
}


/**
 * BRCMnand_write - [MTD Interface] brcmNAND write with ECC
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @len:	number of bytes to write
 * @retlen:	pointer to variable to store the number of written bytes
 * @buf:	the data to write
 *
 * BRCMNAND write with ECC
 */
static int brcmnand_write(struct mtd_info *mtd, loff_t to, size_t len,
			  size_t *retlen, const uint8_t *buf)
{
	struct brcmnand_chip *chip = mtd->priv;
	int ret;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: to=%08x\n", __FUNCTION__, __ll_low(to));

if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) to);}


	/* Do not allow writes past end of device */
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(to, len), MTD_SIZE(mtd))))
  #else
	if (unlikely((to + len) > (mtd->size))) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(to, len), chip->mtdSize)))
#endif
	if (!len)
		return 0;
	
	brcmnand_get_device(mtd, FL_WRITING);

	chip->ops.len = len;
	chip->ops.datbuf = (uint8_t *)buf;
	chip->ops.oobbuf = NULL;

	ret = brcmnand_do_write_ops(mtd, to, &chip->ops);

	*retlen = chip->ops.retlen;

	brcmnand_release_device(mtd);
	return ret;
}


/**
 * brcmnand_write_page_oob - [INTERNAL] write one page
 * @mtd:	MTD device structure
 * @chip:	NAND chip descriptor.  The oob_poi pointer points to the OOB buffer.
 * @page:	page number to write
 */
static int brcmnand_write_page_oob(struct mtd_info *mtd, 
			   const uint8_t* inp_oob, uint32_t page)
{
	struct brcmnand_chip *chip = (struct brcmnand_chip*) mtd->priv;
	int winslice;
	int oobWritten = 0;
	int ret = 0;
	L_OFF_T offset = __ll_LeftShift32(page, chip->page_shift);

	chip->pagebuf = page;

	for (winslice = 0; winslice < chip->eccsteps && ret == 0; winslice++) {
		ret = brcmnand_posted_write_oob(mtd,  &inp_oob[oobWritten] , 
					offset);
//gdebug=0;		
		if (ret < 0) {
			printk(KERN_ERR "%s: brcmnand_posted_write_oob failed at offset=%s, ret=%d\n", 
				__FUNCTION__, __ll_sprintf(brcmNandMsg, offset), ret);
			return ret;
		}
		offset = __ll_add32(offset, chip->eccsize);
		oobWritten += chip->eccOobSize;
	}

	// TBD
	ret = brcmnand_verify_pageoob();

if (gdebug > 3 ) {
printk("<--%s offset=%08x\n", __FUNCTION__, __ll_low(__ll_LeftShift32(page, chip->page_shift)));
print_oobbuf(inp_oob, mtd->oobsize);}
	return ret;
}


/**
 * brcmnand_do_write_oob - [Internal] BrcmNAND write out-of-band
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operation description structure
 *
 * BrcmNAND write out-of-band, no data.
 */
static int 
brcmnand_do_write_oob(struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)
{
	int page, status;
	struct brcmnand_chip *chip = mtd->priv;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: to = 0x%08x, len = %i\n", __FUNCTION__,
	      (unsigned int)to, (int)ops->len);
if (gdebug > 3 ) {
printk("-->%s, to=%08x, len=%d\n", __FUNCTION__, (uint32_t) to, (int)ops->len);}

	/* Do not allow write past end of page */
	if ((ops->ooboffs + ops->len) > mtd->oobsize) {
		DEBUG(MTD_DEBUG_LEVEL0, "nand_write_oob: "
		      "Attempt to write past end of page\n");
		return -EINVAL;
	}

/* BrcmNAND treats multiple chips as a single logical chip
	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);
*/

	/* Shift to get page */
	page = __ll_RightShift(to, chip->page_shift);

#if 0
	/*
	 * Reset the chip. Some chips (like the Toshiba TC5832DC found in one
	 * of my DiskOnChip 2000 test units) will clear the whole data page too
	 * if we don't do this. I have no clue why, but I seem to have 'fixed'
	 * it in the doc2000 driver in August 1999.  dwmw2.
	 */
	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);
#endif

#if 0
	/* Check, if it is write protected */
	if (nand_check_wp(mtd))
		return -EROFS;
#endif

	/* Invalidate the page cache, if we write to the cached page */
	if (page == chip->pagebuf)
		chip->pagebuf = -1;

	chip->oob_poi = BRCMNAND_OOBBUF(chip->buffers);
	memset(chip->oob_poi, 0xff, mtd->oobsize);
	brcmnand_fill_oob(chip, ops->oobbuf, ops);
	
	status = chip->write_page_oob(mtd, chip->oob_poi, page);
	// memset(chip->oob_poi, 0xff, mtd->oobsize);

	if (status)
		return status;

	ops->retlen = ops->len;

	return 0;
}

/**
 * brcmnand_write_oob - [MTD Interface] BrcmNAND write data and/or out-of-band
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operation description structure
 */
static int 
brcmnand_write_oob(struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)
{
	struct brcmnand_chip *chip = mtd->priv;
	int ret = -ENOTSUPP;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: to=%08x\n", __FUNCTION__, __ll_low(to));

if (gdebug > 3 ) {
printk("-->%s, offset=%08x, len=%08x\n", __FUNCTION__, (uint32_t) to, (int) ops->len);}

	ops->retlen = 0;

	/* Do not allow writes past end of device */
#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(to, ops->len), MTD_SIZE(mtd))))
  #else
	if (unlikely(to + ops->len) > mtd->size) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(to, ops->len), chip->mtdSize)))
#endif
	{
		DEBUG(MTD_DEBUG_LEVEL0, "%s: ", __FUNCTION__,
		      "Attempt to write beyond end of device\n");
printk("Attempt to write beyond end of device\n");		
		return -EINVAL;
	}

	brcmnand_get_device(mtd, FL_WRITING);


	if (!ops->datbuf)
		ret = brcmnand_do_write_oob(mtd, to, ops);
	else
		ret = brcmnand_do_write_ops(mtd, to, ops);

#if 0
	if (unlikely(ops->mode == MTD_OOB_RAW))
		chip->ecc.write_page = write_page;
#endif

 //out:
	brcmnand_release_device(mtd);
	return ret;
}

/**
 * brcmnand_writev - [MTD Interface] compabilty function for brcmnand_writev_ecc
 * @param mtd		MTD device structure
 * @param vecs		the iovectors to write
 * @param count		number of vectors
 * @param to		offset to write to
 * @param retlen	pointer to variable to store the number of written bytes
 *
 * BrcmNAND write with kvec. 
 */
static int brcmnand_writev(struct mtd_info *mtd, const struct kvec *vecs,
	unsigned long count, loff_t to, size_t *retlen)
{
	int i, len, total_len, ret = -EIO, written = 0,  buflen;
	uint32_t page;
	int numpages = 0;
	struct brcmnand_chip * chip = mtd->priv;
	//int	ppblock = (1 << (chip->phys_erase_shift - chip->page_shift));
	u_char *bufstart = NULL;
	//u_char tmp_oob[64];
	u_char *data_buf;


if (gdebug > 3 ) {
printk("-->%s, offset=%08x\n", __FUNCTION__, (uint32_t) to);}

	/* Preset written len for early exit */
	*retlen = 0;

	/* Calculate total length of data */
	total_len = 0;
	for (i = 0; i < count; i++)
		total_len += vecs[i].iov_len;

	DEBUG(MTD_DEBUG_LEVEL3, "%s: to = 0x%08x, len = %i, count = %ld, eccbuf=%p, total_len=%d\n", 
		__FUNCTION__, (unsigned int) to, (unsigned int) total_len, count, NULL, total_len);

	/* Do not allow write past end of the device */

#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(to, total_len), MTD_SIZE(mtd))))
  #else
	if (unlikely(to + total_len) > mtd->size) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(to, total_len), chip->mtdSize)))
#endif
	{
		DEBUG(MTD_DEBUG_LEVEL0, "brcmnand_writev_ecc: Attempted write past end of device\n");
		return -EINVAL;
	}

	/* Reject writes, which are not page aligned */
        if (unlikely(NOTALIGNED(to)) || unlikely(NOTALIGNED(total_len))) {
                DEBUG(MTD_DEBUG_LEVEL0, "brcmnand_writev_ecc: Attempt to write not page aligned data\n");
                return -EINVAL;
        }

	/* Grab the lock and see if the device is available */
	brcmnand_get_device(mtd, FL_WRITING);

	/* Setup start page, we know that to is aligned on page boundary */
	page = __ll_RightShift(to, chip->page_shift);;

	data_buf = BRCMNAND_malloc(sizeof(u_char)*2048);
	if (unlikely(data_buf == NULL)) {
		printk(KERN_ERR "%s: vmalloc failed\n", __FUNCTION__);
		return -ENOMEM;
	}
	/* Loop until all keve's data has been written */
	len = 0; 		// How many data from current iovec has been written
	written = 0;	// How many bytes have been written so far in all
	buflen = 0;	// How many bytes from the buffer has been copied to.
	while (count) {
		/* If the given tuple is >= pagesize then
		 * write it out from the iov
		 */
		// THT: We must also account for the partial buffer left over from previous iovec
		if ((buflen + vecs->iov_len - len) >= mtd->writesize) {
			/* Calc number of pages we can write
			 * out of this iov in one go */
			numpages = (buflen + vecs->iov_len - len) >> chip->page_shift;


			//oob = 0;
			for (i = 0; i < numpages; i++) {
				if (0 == buflen) { // If we start a new page
					bufstart = &((u_char *)vecs->iov_base)[len];
				}
				else { // Reuse existing partial buffer, partial refill to end of page
					memcpy(&bufstart[buflen], &((u_char *)vecs->iov_base)[len], mtd->writesize - buflen);
				}

				ret = chip->write_page (mtd, bufstart, NULL, page);
				bufstart = NULL;

				if (ret) {
					printk("%s: brcmnand_write_page failed, ret=%d\n", __FUNCTION__, ret);
					goto out;
				}
				len += mtd->writesize - buflen;
				buflen = 0;
				//oob += oobretlen;
				page++;
				written += mtd->writesize;
			}
			/* Check, if we have to switch to the next tuple */
			if (len >= (int) vecs->iov_len) {
				vecs++;
				len = 0;
				count--;
			}
		} else { // (vecs->iov_len - len) <  mtd->writesize)
			/*
			 * We must use the internal buffer, read data out of each
			 * tuple until we have a full page to write
			 */
			

			/*
			 * THT: Changed to use memcpy which is more efficient than byte copying, does not work yet
			 *  Here we know that 0 < vecs->iov_len - len < mtd->writesize, and len is not necessarily 0
			 */
			// While we have iovec to write and a partial buffer to fill
			while (count && (buflen < mtd->writesize)) {
				
				// Start new buffer?
				if (0 == buflen) {
					bufstart = data_buf;
				}
				if (vecs->iov_base != NULL && (vecs->iov_len - len) > 0) {
					// We fill up to the page
					int fillLen = min_t(int, vecs->iov_len - len, mtd->writesize - buflen);
					
					memcpy(&data_buf[buflen], &((u_char*) vecs->iov_base)[len], fillLen);
					buflen += fillLen;
					len += fillLen;
				}
				/* Check, if we have to switch to the next tuple */
				if (len >= (int) vecs->iov_len) {
					vecs++;
					len = 0;
					count--;
				}

			}
			// Write out a full page if we have enough, otherwise loop back to the top
			if (buflen == mtd->writesize) {
				
				numpages = 1;
				
				ret = chip->write_page (mtd, bufstart, NULL, page);
				if (ret) {
					printk("%s: brcmnand_write_page failed, ret=%d\n", __FUNCTION__, ret);
					goto out;
				}
				page++;
				written += mtd->writesize;
				
				bufstart = NULL;
				buflen = 0;
			}
		}

		/* All done ? */
		if (!count) {
			if (buflen) { // Partial page left un-written.  Imposible, as we check for totalLen being multiple of pageSize above.
				printk("%s: %d bytes left unwritten with writev_ecc at offset %s\n", 
					__FUNCTION__, buflen, __ll_sprintf(brcmNandMsg,__ll_LeftShift32(page, chip->page_shift)));
				BUG();
			}
			break;
		}

	}
	ret = 0;
out:
	/* Deselect and wake up anyone waiting on the device */
	brcmnand_release_device(mtd);

	BRCMNAND_free(data_buf);
	*retlen = written;
//if (*retlen <= 0) printk("%s returns retlen=%d, ret=%d, startAddr=%08x\n", __FUNCTION__, *retlen, ret, startAddr);
//printk("<-- %s: retlen=%d\n", __FUNCTION__, *retlen);
	return ret;
}

#if 0
/**
 * brcmnand_block_bad - [DEFAULT] Read bad block marker from the chip
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 * @getchip:	0, if the chip is already selected
 *
 * Check, if the block is bad.
 */
static int brcmnand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
	int res = 0, ret = 0;
	uint32_t page;
	struct brcmnand_chip *chip = mtd->priv;
	u16 bad;
	uint8_t oob[64];
	//uint8_t* saved_poi;

	if (getchip) {
		page = __ll_RightShift(ofs, chip->page_shift);

#if 0
		chipnr = (int)(ofs >> chip->chip_shift);
#endif

		brcmnand_get_device(mtd, FL_READING);

#if 0
		/* Select the NAND device */
		chip->select_chip(mtd, chipnr);
#endif
	} 
	page = __ll_RightShift(ofs, chip->page_shift);

	ret = chip->read_page_oob(mtd, oob, page);
	if (ret) {
		return 1;
	}

	if (chip->options & NAND_BUSWIDTH_16) {
		bad = (u16) cpu_to_le16(*(uint16*) (oob[chip->badblockpos]));
		if (chip->badblockpos & 0x1)
			bad >>= 8;
		if ((bad & 0xFF) != 0xff)
			res = 1;
	} else {
		if (oob[chip->badblockpos] != 0xff)
			res = 1;
	}

	if (getchip)
		brcmnand_release_device(mtd);

	return res;
}
#endif


/**
 * brcmnand_block_checkbad - [GENERIC] Check if a block is marked bad
 * @param mtd		MTD device structure
 * @param ofs		offset from device start
 * @param getchip	0, if the chip is already selected
 * @param allowbbt	1, if its allowed to access the bbt area
 *
 * Check, if the block is bad. Either by reading the bad block table or
 * calling of the scan function.
 */
static int brcmnand_block_checkbad(struct mtd_info *mtd, loff_t ofs, int getchip, int allowbbt)
{
	struct brcmnand_chip * chip = mtd->priv;
	int res;

	if (getchip) {
		brcmnand_get_device(mtd, FL_READING);
	}
	
	/* Return info from the table */
	res = chip->isbad_bbt(mtd, ofs, allowbbt);

	if (getchip) {
		brcmnand_release_device(mtd);
	}

	return res;
}

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
/**
 * brcmnand_erase_nolock - [Private] erase block(s)
 * @param mtd		MTD device structure
 * @param instr		erase instruction
 * @allowBBT			allow erase of BBT
 *
 * Erase one ore more blocks
 * ** FIXME ** This code does not work for multiple chips that span an address space > 4GB
 * Similar to BBT, except does not use locks and no alignment checks
 * Assumes lock held by caller
 */
static int brcmnand_erase_nolock(struct mtd_info *mtd, struct erase_info *instr, int allowbbt)
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned int block_size;
	loff_t addr;
	int len;
	int ret = 0;
	int needBBT;
	
	block_size = (1 << chip->erase_shift);
	instr->fail_addr = 0xffffffff;

	/* Clear ECC registers */
	chip->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);
	chip->ctrl_write(BCHP_NAND_ECC_UNC_ADDR, 0);
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	chip->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
	chip->ctrl_write(BCHP_NAND_ECC_UNC_EXT_ADDR, 0);
#endif

	/* Loop throught the pages */
	len = instr->len;
	addr = instr->addr;
	instr->state = MTD_ERASING;

	while (len) {
		/* Check if we have a bad block, we do not erase bad blocks */
		if (brcmnand_block_checkbad(mtd, addr, 0, allowbbt)) {
			printk (KERN_ERR "%s: attempt to erase a bad block at addr 0x%08x\n", __FUNCTION__, (unsigned int) addr);
			instr->state = MTD_ERASE_FAILED;
			goto erase_one_block;
		}
		chip->ctrl_writeAddr(chip, addr, 0);
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_BLOCK_ERASE);

		/* Wait until flash is ready */
		ret = brcmnand_write_is_complete(mtd, &needBBT);

		/* Check, if it is write protected: TBD */
		if (needBBT ) {
			if ( !allowbbt) {
				printk(KERN_ERR "brcmnand_erase: Failed erase, block %d, flash status=%08x\n", 
						__ll_low(__ll_RightShift(addr, chip->erase_shift)), needBBT);
				instr->state = MTD_ERASE_FAILED;
				instr->fail_addr = addr;
				printk(KERN_WARNING "%s: Marking bad block @%08x\n", __FUNCTION__, (unsigned int) addr);
				(void) chip->block_markbad(mtd, addr);
				goto erase_one_block;
			}
		}
erase_one_block:
		len -= block_size;
		addr = __ll_add32(addr, block_size);
	}

	instr->state = MTD_ERASE_DONE;
	ret = instr->state == MTD_ERASE_DONE ? 0 : -EIO;
	/* Do call back function */
	if (!ret) {
		mtd_erase_callback(instr);
	}

	return ret;
}
#endif



/**
 * brcmnand_erase_bbt - [Private] erase block(s)
 * @param mtd		MTD device structure
 * @param instr		erase instruction
 * @allowBBT			allow erase of BBT
 * @doNotUseBBT		Do not look up in BBT
 *
 * Erase one ore more blocks
 * ** FIXME ** This code does not work for multiple chips that span an address space > 4GB
 */
static int 
brcmnand_erase_bbt(struct mtd_info *mtd, struct erase_info *instr, int allowbbt, int doNotUseBBT)
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned int block_size;
	loff_t addr;
	int len;
	int ret = 0;
	int needBBT;
	
#if 0// CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	// For now ignore the high DW.
	L_OFF_T instr_addr = __ll_constructor(0, instr->addr);
	//instr->addr_hi = 0;
#endif
	

	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = %s, len = %08x\n", __FUNCTION__, 
	__ll_sprintf(brcmNandMsg, instr->addr), (unsigned int) instr->len);
//printk( "%s: start = 0x%08x, len = %08x\n", __FUNCTION__, (unsigned int) instr->addr, (unsigned int) instr->len);

	block_size = (1 << chip->erase_shift);


	/* Start address must align on block boundary */
#if 1 //CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
	if (unlikely(instr->addr & (block_size - 1))) 
#else
	if (unlikely(!__ll_is_zero(__ll_and32(instr_addr, (block_size - 1)))))
#endif
	{
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Unaligned address\n", __FUNCTION__);
if (gdebug > 3 ) {printk( "%s: Unaligned address\n", __FUNCTION__);}
		return -EINVAL;
	}

	/* Length must align on block boundary */
	if (unlikely(instr->len & (block_size - 1))) 
	{
		DEBUG(MTD_DEBUG_LEVEL0, 
"%s: Length not block aligned, len=%08x, blocksize=%08x, chip->blkSize=%08x, chip->erase=%d\n",
__FUNCTION__, instr->len, block_size, chip->blockSize, chip->erase_shift);
printk(  
"%s: Length not block aligned, len=%08x, blocksize=%08x, chip->blkSize=%08x, chip->erase=%d\n",
__FUNCTION__, instr->len, block_size, chip->blockSize, chip->erase_shift);
		return -EINVAL;
	}

	/* Do not allow erase past end of device */
#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
  #ifdef MTD_LARGE
	if (unlikely(mtd64_is_greater(mtd64_add32(instr->addr, instr->len), MTD_SIZE(mtd))))
  #else
	if (unlikely((instr->len + instr->addr) > mtd->size)) 
  #endif
#else
	if (unlikely(__ll_is_greater(__ll_add32(instr->addr, instr->len), chip->mtdSize)))
#endif
	{
#ifdef MTD_LARGE
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Erase past end of device\n", __FUNCTION__);
if (gdebug > 3 ) {printk(  "%s: Erase past end of device, instr_addr=%016llx, instr->len=%08x, mtd->size=%16llx\n", 
	__FUNCTION__, instr->addr, instr->len, MTD_SIZE(mtd));}
#else
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Erase past end of device\n", __FUNCTION__);
if (gdebug > 3 ) {printk(  "%s: Erase past end of device, instr_addr=%08x, instr->len=%08x, mtd->size=%08x\n", 
	__FUNCTION__, __ll_low( instr->addr), instr->len, mtd->size);}
#endif
		return -EINVAL;
	}

#if 1 //CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
#ifdef MTD_LARGE
	instr->fail_addr = 0xffffffffffffffffULL;
#else
	instr->fail_addr = 0xffffffff;
#endif
#else
	instr->fail_addr = instr->fail_addr_hi = 0xffffffff;
#endif


	/*
	 * Clear ECC registers 
	 */
	chip->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);
	chip->ctrl_write(BCHP_NAND_ECC_UNC_ADDR, 0);
	
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	chip->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
	chip->ctrl_write(BCHP_NAND_ECC_UNC_EXT_ADDR, 0);
#endif

	/* Loop throught the pages */
	len = instr->len;

#if 1 //CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
	addr = instr->addr;
#else
	addr = instr_addr;
#endif

	instr->state = MTD_ERASING;

	while (len) {


/* THT: We cannot call brcmnand_block_checkbad which just look at the BBT,
// since this code is also called when we create the BBT.
// We must look at the actual bits, or have a flag to tell the driver
// to read the BI directly from the OOB, bypassing the BBT
 */
		/* Check if we have a bad block, we do not erase bad blocks */
		if (brcmnand_block_checkbad(mtd, addr, 0, allowbbt)) {
			printk (KERN_ERR "%s: attempt to erase a bad block at addr 0x%08x\n", __FUNCTION__, (unsigned int) addr);
			instr->state = MTD_ERASE_FAILED;
			goto erase_one_block;
		}

		//chip->command(mtd, ONENAND_CMD_ERASE, addr, block_size);

		chip->ctrl_writeAddr(chip, addr, 0);
	
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_BLOCK_ERASE);

		// Wait until flash is ready
		ret = brcmnand_write_is_complete(mtd, &needBBT);
		
		/* Check, if it is write protected: TBD */
		if (needBBT ) {
			if ( !allowbbt) {
				printk(KERN_ERR "brcmnand_erase: Failed erase, block %d, flash status=%08x\n", 
					__ll_low(__ll_RightShift(addr, chip->erase_shift)), needBBT);
				instr->state = MTD_ERASE_FAILED;

#if 1 //CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
				instr->fail_addr = addr;
#else
				instr->fail_addr = __ll_low(addr);
				instr->fail_addr_hi = __ll_high(addr);
#endif

				printk(KERN_WARNING "%s: Marking bad block @%08x\n", __FUNCTION__, (unsigned int) addr);
				(void) chip->block_markbad(mtd, addr);
				goto erase_one_block;
			}
		}
erase_one_block:

		len -= block_size;
		addr = __ll_add32(addr, block_size);
	}

	instr->state = MTD_ERASE_DONE;

//erase_exit:

	ret = instr->state == MTD_ERASE_DONE ? 0 : -EIO;
	/* Do call back function */
	if (!ret) {
		mtd_erase_callback(instr);
	}

	DEBUG(MTD_DEBUG_LEVEL0, "<--%s\n", __FUNCTION__);
	return ret;
}


/**
 * brcmnand_erase - [MTD Interface] erase block(s)
 * @param mtd		MTD device structure
 * @param instr		erase instruction
 *
 * Erase one ore more blocks
 */
static int brcmnand_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct brcmnand_chip * chip = mtd->priv;
	int ret;
	unsigned int block_size;
	loff_t addr;
	int len;
	int allowbbt = 0;
	
	DEBUG(MTD_DEBUG_LEVEL3, "-->%s addr=%08x, len=%d\n", __FUNCTION__,
 		(unsigned long) instr->addr, instr->len);

	/* Grab the lock and see if the device is available */
	brcmnand_get_device(mtd, FL_ERASING);

	block_size = (1 << chip->erase_shift);
	
	ret = brcmnand_erase_bbt(mtd, instr, allowbbt, 0); // Do not allow erase of BBT, and use BBT

		/* Deselect and wake up anyone waiting on the device */
	brcmnand_release_device(mtd);

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
		if (chip->cet) {
			if (chip->cet->flags != BRCMNAND_CET_DISABLED && 
					chip->cet->flags != BRCMNAND_CET_LAZY && allowbbt != 1) {
				len = instr->len;
				addr = instr->addr;
				while (len) {
					/* Skip if bad block */
					if (brcmnand_block_checkbad(mtd, addr, 0, allowbbt)) {
						printk (KERN_ERR "%s: attempt to erase a bad block at addr 0x%08x\n", __FUNCTION__, (unsigned int) addr);
						len -= block_size;
						addr = __ll_add32(addr, block_size);
						continue;
					}
					if(brcmnand_cet_erasecallback(mtd, instr->addr) < 0) {
						printk(KERN_INFO "Error in CET erase callback, disabling CET\n");
						chip->cet->flags = BRCMNAND_CET_DISABLED;
					}
					len -= block_size;
					addr = __ll_add32(addr, block_size);
				}
			}
		}
#endif
	return ret;
}

/**
 * brcmnand_sync - [MTD Interface] sync
 * @param mtd		MTD device structure
 *
 * Sync is actually a wait for chip ready function
 */
static void brcmnand_sync(struct mtd_info *mtd)
{
	DEBUG(MTD_DEBUG_LEVEL3, "brcmnand_sync: called\n");

	/* Grab the lock and see if the device is available */
	brcmnand_get_device(mtd, FL_SYNCING);

	PLATFORM_IOFLUSH_WAR();

	/* Release it and go back */
	brcmnand_release_device(mtd);
}


/**
 * brcmnand_block_isbad - [MTD Interface] Check whether the block at the given offset is bad
 * @param mtd		MTD device structure
 * @param ofs		offset relative to mtd start
 *
 * Check whether the block is bad
 */
static int brcmnand_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	struct brcmnand_chip * chip = mtd->priv;
	
	DEBUG(MTD_DEBUG_LEVEL3, "-->%s ofs=%08x\n", __FUNCTION__, __ll_low(ofs));
	/* Check for invalid offset */
#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
  #ifdef MTD_LARGE
	if (mtd64_is_greater(ofs, MTD_SIZE(mtd)))
  #else
	if (ofs > mtd->size)
  #endif
#else
	if (__ll_is_greater(ofs, chip->mtdSize))
#endif
	{
		return -EINVAL;
	}

	return brcmnand_block_checkbad(mtd, ofs, 1, 0);
}

/**
 * brcmnand_default_block_markbad - [DEFAULT] mark a block bad
 * @param mtd		MTD device structure
 * @param ofs		offset from device start
 *
 * This is the default implementation, which can be overridden by
 * a hardware specific driver.
 */
static int brcmnand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct brcmnand_chip * chip = mtd->priv;
	//struct bbm_info *bbm = chip->bbm;
	// THT: 3/20/07: We restrict ourselves to only support x8.  
	// Revisit this for x16.
	u_char bbmarker[1] = {0};  // CFE and BBS uses 0x0F, Linux by default uses 0
								//so we can use this to mark the difference
	u_char buf[64];
	//size_t retlen;
	uint32_t block, page;
	int dir;
	UL_OFF_T ulofs;
	int ret;

	DEBUG(MTD_DEBUG_LEVEL3, "-->%s ofs=%s\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, ofs));

	// Page align offset
	ulofs = (UL_OFF_T)__ll_and32(ofs, ~ chip->page_mask);
	

	/* Get block number.  Block is guaranteed to be < 2*32 */
	block = (uint32_t) __ll_RightShift(ulofs, chip->erase_shift);

	// Block align offset
	ulofs = __ll_LeftShift32(block, chip->erase_shift);

	if (!NAND_IS_MLC(chip)) { // SLC chip, mark first and 2nd page as bad.
		page = block << (chip->erase_shift - chip->page_shift);
		dir = 1;
	}
	else { // MLC chip, mark last and previous page as bad.
		page = ((block+1) << (chip->erase_shift - chip->page_shift)) - 1;
		dir = -1;
	}
      if (chip->bbt) {
                chip->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1); 
      	}

	memcpy(buf, ffchars, sizeof(buf));
	memcpy(&buf[chip->badblockpos], bbmarker, sizeof(bbmarker));

	// Lock already held by caller, so cant call mtd->write_oob directly
	ret = chip->write_page_oob(mtd, buf, page);
	if (ret) {
		printk(KERN_INFO "Mark bad page %d failed with retval=%d\n", page, ret);
	}

	// Mark 2nd page as bad, ignoring last write
	page += dir;
	// Lock already held by caller, so cant call mtd->write_oob directly
DEBUG(MTD_DEBUG_LEVEL3, "%s Calling chip->write_page(page=%08x)\n", __FUNCTION__, page);
	ret = chip->write_page_oob(mtd, buf, page);
	if (ret) {
		printk(KERN_INFO "Mark bad page %d failed with retval=%d\n", page, ret);
	}

	/*
	 * According to the HW guy, even if the write fails, the controller have written 
	 * a 0 pattern that certainly would have written a non 0xFF value into the BI marker.
	 *
	 * Ignoring ret.  Even if we fail to write the BI bytes, just ignore it, 
	 * and mark the block as bad in the BBT
	 */
DEBUG(MTD_DEBUG_LEVEL3, "%s Calling brcmnand_update_bbt(ulofs=%s))\n", __FUNCTION__, __ll_sprintf(brcmNandMsg, ulofs));
	(void) brcmnand_update_bbt(mtd, ulofs);
	//if (!ret)
	mtd->ecc_stats.badblocks++;
	return ret;
}

/**
 * brcmnand_block_markbad - [MTD Interface] Mark the block at the given offset as bad
 * @param mtd		MTD device structure
 * @param ofs		offset relative to mtd start
 *
 * Mark the block as bad
 */
static int brcmnand_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct brcmnand_chip * chip = mtd->priv;
	int ret;

	DEBUG(MTD_DEBUG_LEVEL3, "-->%s ofs=%08x\n", __FUNCTION__, (unsigned int) ofs);
	
	ret = brcmnand_block_isbad(mtd, ofs);
	if (ret) {
		/* If it was bad already, return success and do nothing */
		if (ret > 0)
			return 0;
		return ret;
	}

	return chip->block_markbad(mtd, ofs);
}

/**
 * brcmnand_unlock - [MTD Interface] Unlock block(s)
 * @param mtd		MTD device structure
 * @param ofs		offset relative to mtd start
 * @param len		number of bytes to unlock
 *
 * Unlock one or more blocks
 */
static int brcmnand_unlock(struct mtd_info *mtd, loff_t llofs, size_t len)
{
	struct brcmnand_chip * chip = mtd->priv;
	int status;
	UL_OFF_T blkAddr, ofs = (UL_OFF_T) llofs;

	DEBUG(MTD_DEBUG_LEVEL3, "-->%s llofs=%08x, len=%d\n", __FUNCTION__,
 		(unsigned long) llofs, (int) len);



	/* Block lock scheme */
	for (blkAddr = ofs; __ll_is_less(blkAddr, __ll_add32(ofs, len)); blkAddr = __ll_add32(blkAddr, chip->blockSize)) {

		/* The following 2 commands share the same CMD_EXT_ADDR, as the block never cross a CS boundary */
		chip->ctrl_writeAddr(chip, blkAddr, 0); 
		/* Set end block address */
		chip->ctrl_writeAddr(chip, __ll_add32(blkAddr, chip->blockSize - 1), 1);
		/* Write unlock command */
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_BLOCKS_UNLOCK);


		/* There's no return value */
		chip->wait(mtd, FL_UNLOCKING, &status);

		if (status & 0x0f)  
			printk(KERN_ERR "block = %08x, wp status = 0x%x\n", __ll_low(blkAddr), status);

		/* Sanity check */
#if 0
		while (chip->read_word(chip->base + ONENAND_REG_CTRL_STATUS)
		    & ONENAND_CTRL_ONGO)
			continue;
#endif

		/* Check lock status */
		chip->ctrl_writeAddr(chip, blkAddr, 0); 
		chip->ctrl_write(BCHP_NAND_CMD_START, OP_READ_BLOCKS_LOCK_STATUS);
		status = chip->ctrl_read(BCHP_NAND_BLOCK_LOCK_STATUS);
		//status = chip->read_word(chip->base + ONENAND_REG_WP_STATUS);

	}

	return 0;
}


/**
 * brcmnand_print_device_info - Print device ID
 * @param device        device ID
 *
 * Print device ID
 */
static void brcmnand_print_device_info(brcmnand_chip_Id* chipId, struct brcmnand_chip *chip)
{
#ifdef MTD_LARGE
	printk(KERN_INFO "BrcmNAND mfg %x %x %s %dMB\n",
                chipId->mafId, chipId->chipId, chipId->chipIdStr,\
	       	mtd64_ll_low(mtd64_rshft32(chip->chipSize, 20)));
#else
	printk(KERN_INFO "BrcmNAND mfg %x %x %s %dMB\n",
                chipId->mafId, chipId->chipId, chipId->chipIdStr, (int) (chip->chipSize >>20));
#endif
	print_config_regs();

}



/*
 * bit 31: 	1 = OTP read-only
 * 	v2.1 and earlier: 30: 		Page Size: 0 = PG_SIZE_512, 1 = PG_SIZE_2KB version 
 * 28-29: 	Block size: 3=512K, 1 = 128K, 0 = 16K, 2 = 8K
 * 24-27:	Device_Size
 *			0:	4MB
 *			1:	8MB
 *			2: 	16MB
 *			3:	32MB
 *			4:	64MB
 *			5:	128MB
 *			6: 	256MB
 *			7:	512MB
 *			8:	1GB
 *			9:	2GB
 *			10:	4GB  << Hit limit of MTD struct here.
 *			11:	8GB
 *			12:	16GB
 *			13:	32GB
 *			14:	64GB
 *			15:	128GB
 * 23:		Dev_Width 0 = Byte8, 1 = Word16
 *   v2.1 and earlier:22-19: 	Reserved
 *   v2.2 and later:  21:20	page Size
 * 18:16:	Full Address Bytes
 * 15		Reserved
 * 14:12	Col_Adr_Bytes
 * 11:		Reserved
 * 10-08	Blk_Adr_Bytes
 * 07-00	Reserved
 */
 
void
brcmnand_decode_config(struct brcmnand_chip* chip, uint32_t nand_config)
{
	unsigned int chipSizeShift;
	
	//chip->chipSize = (nand_config & 0x07000000) >> (24 - 20);

#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_2_2
	// Version 2.1 or earlier: 2 bit field 28:29
	switch ((nand_config & 0x30000000) >> 28) {
		case 3:
			chip->blockSize = 512 << 10;
			break;
		case 2:
			chip->blockSize = 8 << 10;
			break;
		case 1:	
			chip->blockSize = 128 << 10;
			break;
		case 0:
			chip->blockSize = 16 << 10;
			break;
	}
#else
	// Version 2.2 or later: 3 bits 28:30
	switch ((nand_config & 0x70000000) >> 28) {
		case 4:
			chip->blockSize = 256 << 10;
			break;
		case 3:
			chip->blockSize = 512 << 10;
			break;
		case 2:
			chip->blockSize = 8 << 10;
			break;
		case 1:	
			chip->blockSize = 128 << 10;
			break;
		case 0:
			chip->blockSize = 16 << 10;
			break;
	}
#endif
	chip->erase_shift = ffs(chip->blockSize) - 1;

#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_2_2
	// Version 2.1 or earlier: Bit 30
	switch((nand_config & 0x40000000) >> 30) {
		case 0:
			chip->pageSize= 512;
			break;
		case 1:
			chip->pageSize = 2048;
			break;
	}
	
#else
	// Version 2.2 or later, bits 20:21
	switch((nand_config & 0x300000) >> 20) {
		case 0:
			chip->pageSize= 512;
			break;
		case 1:
			chip->pageSize = 2048;
			break;
		case 2:
			chip->pageSize = 4096;
			break;
		case 3:
			printk(KERN_ERR "Un-supported page size\n");
			chip->pageSize = 0; // Let it crash
			break;
	}
#endif

	chip->page_shift = ffs(chip->pageSize) - 1;
	chip->page_mask = (1 << chip->page_shift) - 1;

	chipSizeShift = (nand_config & 0x0F000000) >> 24;

#ifndef MTD_LARGE
	if (chipSizeShift <= 0xa)
		chip->chipSize = (4 << 20) << chipSizeShift;
	else {
		unsigned int chipSizeMB = 4 << chipSizeShift;
		printk(KERN_ERR "Size of chip %dMB exceeded MTD layer limit\n", chipSizeMB);
		chip->chipSize = (4 << 20) << 10;
	}
#else
	chip->chipSize = __ll_LeftShift32(4 << 20, chipSizeShift);
#endif

	chip->busWidth = 1 + ((nand_config & 0x00400000) >> 23);

#ifdef MTD_LARGE
	printk(KERN_INFO "NAND Config: Reg=%08x, chipSize=%lld MB, blockSize=%dK, erase_shift=%x\n",
		nand_config, mtd64_rshft32(chip->chipSize, 20), chip->blockSize >> 10, chip->erase_shift);
#else
	printk(KERN_INFO "NAND Config: Reg=%08x, chipSize=%dMB, blockSize=%dK, erase_shift=%x\n",
		nand_config, chip->chipSize >> 20, chip->blockSize >> 10, chip->erase_shift);
#endif
	printk(KERN_INFO "busWidth=%d, pageSize=%dB, page_shift=%d, page_mask=%08x\n", 
		chip->busWidth, chip->pageSize, chip->page_shift , chip->page_mask);

}

/*
 * Adjust timing pattern if specified in chip ID list
 * Also take dummy entries, but no adjustments will be made.
 */
static void brcmnand_adjust_timings(struct brcmnand_chip *this, brcmnand_chip_Id* chip)
{
		unsigned long nand_timing1 = this->ctrl_read(BCHP_NAND_TIMING_1);
		unsigned long nand_timing1_b4;
		unsigned long nand_timing2 = this->ctrl_read(BCHP_NAND_TIMING_2);
		unsigned long nand_timing2_b4;
		
	// Adjust NAND timings:
	if (chip->timing1) {
		nand_timing1_b4 = nand_timing1;

		if (chip->timing1 & BCHP_NAND_TIMING_1_tWP_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tWP_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tWP_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tWH_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tWH_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tWH_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tRP_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tRP_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tRP_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tREH_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tREH_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tREH_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tCS_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tCS_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tCS_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tCLH_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tCLH_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tCLH_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tALH_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tALH_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tALH_MASK);  
		}
		if (chip->timing1 & BCHP_NAND_TIMING_1_tADL_MASK) {
			nand_timing1 &= ~BCHP_NAND_TIMING_1_tADL_MASK;
			nand_timing1 |= (chip->timing1 & BCHP_NAND_TIMING_1_tADL_MASK);  
		}

		this->ctrl_write(BCHP_NAND_TIMING_1, nand_timing1);
if (gdebug > 3 ) {printk("Adjust timing1: Was %08lx, changed to %08lx\n", nand_timing1_b4, nand_timing1);}
	}
	else {
printk("timing1 not adjusted: %08lx\n", nand_timing1);
	}

	// Adjust NAND timings:
	if (chip->timing2) {
		nand_timing2_b4 = nand_timing2;

		if (chip->timing2 & BCHP_NAND_TIMING_2_tWB_MASK) {
			nand_timing2 &= ~BCHP_NAND_TIMING_2_tWB_MASK;
			nand_timing2 |= (chip->timing2 & BCHP_NAND_TIMING_2_tWB_MASK);  
		}
		if (chip->timing2 & BCHP_NAND_TIMING_2_tWHR_MASK) {
			nand_timing2 &= ~BCHP_NAND_TIMING_2_tWHR_MASK;
			nand_timing2 |= (chip->timing2 & BCHP_NAND_TIMING_2_tWHR_MASK);  
		}
		if (chip->timing2 & BCHP_NAND_TIMING_2_tREAD_MASK) {
			nand_timing2 &= ~BCHP_NAND_TIMING_2_tREAD_MASK;
			nand_timing2 |= (chip->timing2 & BCHP_NAND_TIMING_2_tREAD_MASK);  
		}

		this->ctrl_write(BCHP_NAND_TIMING_2, nand_timing2);
if (gdebug > 3 ) {printk("Adjust timing2: Was %08lx, changed to %08lx\n", nand_timing2_b4, nand_timing2);}
	}
	else {
printk("timing2 not adjusted: %08lx\n", nand_timing2);
	}
}

static void 
brcmnand_read_id(struct mtd_info *mtd, unsigned int chipSelect, unsigned long* dev_id)
{
	struct brcmnand_chip * chip = mtd->priv;
	
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	/* Set correct chip Select */
	chip->ctrl_write(BCHP_NAND_CMD_ADDRESS, BCHP_NAND_CMD_START_OPCODE_DEVICE_ID_READ);
	chip->ctrl_write(BCHP_NAND_CMD_EXT_ADDRESS, chipSelect << 16);
#endif

PRINTK("-->%s: this=%p, chip->ctrl_read=%p\n", __FUNCTION__, chip, chip->ctrl_read);

	/* Send the command for reading device ID from controller */
	*dev_id = chip->ctrl_read(BCHP_NAND_FLASH_DEVICE_ID);

	printk(KERN_INFO "brcmnand_probe: CS%1d: dev_id=%08x\n", chipSelect, (unsigned int) *dev_id);

}


/**
 * brcmnand_probe - [BrcmNAND Interface] Probe the BrcmNAND device
 * @param mtd		MTD device structure
 *
 * BrcmNAND detection method:
 *   Compare the the values from command with ones from register
 *
 * 8/13/08:
 * V3.0+: Add celltype probe for MLC
 */
static int brcmnand_probe(struct mtd_info *mtd, unsigned int chipSelect)
{
	struct brcmnand_chip * chip = mtd->priv;
	unsigned char brcmnand_maf_id, brcmnand_dev_id;
	uint32_t nand_config;
	int version_id;
	//int density;
	int i;
#ifdef MTD_LARGE
	int rs, hi, lo, rem;
#endif

	/* Read manufacturer and device IDs from Controller */
	brcmnand_read_id(mtd, chipSelect, &chip->device_id);

	brcmnand_maf_id = (chip->device_id >> 24) & 0xff;
	brcmnand_dev_id = (chip->device_id >> 16) & 0xff;

	/* Look up in our table for infos on device */
	for (i=0; i < BRCMNAND_MAX_CHIPS; i++) {
		if (brcmnand_dev_id == brcmnand_chips[i].chipId 
			&& brcmnand_maf_id == brcmnand_chips[i].mafId)
			break;
	}

	if (i >= BRCMNAND_MAX_CHIPS) {
#if CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_0_0
		printk(KERN_ERR "DevId %08x may not be supported\n", (unsigned int) chip->device_id);
		/* Because of the bug in the controller in the first version,
		 * if we can't identify the chip, we punt
		 */
		return (-EINVAL);
#else
		printk(KERN_WARNING"DevId %08x may not be supported.  Will use config info\n", (unsigned int) chip->device_id);
#endif
	}

	/*
	 * Check to see if the NAND chip requires any special controller version
	 */
	if (brcmnand_chips[i].ctrlVersion > CONFIG_MTD_BRCMNAND_VERSION) {
		printk(KERN_ERR "#########################################################\n");
		printk(KERN_ERR "DevId %s requires controller version %d or later, but STB is version %d\n",
			brcmnand_chips[i].chipIdStr, brcmnand_chips[i].ctrlVersion, CONFIG_MTD_BRCMNAND_VERSION);
		printk(KERN_ERR "#########################################################\n");
	}



	/*
	 * Special treatment for Spansion OrNand chips which do not conform to standard ID
	 */

	chip->disableECC = 0;
	chip->cellinfo = 0; // default to SLC, will read 3rd byte ID later for v3.0+ controller
	
	nand_config = chip->ctrl_read(BCHP_NAND_CONFIG);
	
	if (FLASHTYPE_SPANSION == brcmnand_maf_id) {
		unsigned char devId3rdByte =  (chip->device_id >> 8) & 0xff;

		switch (devId3rdByte) {
			case 0x04:
			case 0x00:
				/* ECC Needed, device with up to 2% bad blocks */
				break;

			case 0x01:
			case 0x03:
				/* ECC NOT Needed, device is 100% valid blocks */
				chip->disableECC = 1;
				break;
		}

		/* Correct erase Block Size to read 512K for all Spansion OrNand chips */
		nand_config &= ~(0x3 << 28);
		nand_config |= (0x3 << 28); // bit 29:28 = 3 ===> 512K erase block
		chip->ctrl_write(BCHP_NAND_CONFIG, nand_config);
	} else {

#if CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_0_0
		// Workaround for bug in 7400A0 returning invalid config
		switch(i) { 
			case 0: /* SamSung NAND 1Gbit */
			case 1: /* ST NAND 1Gbit */
			case 4:
			case 5:
				/* Large page, 128K erase block
				   PAGE_SIZE = 0x1 = 1b = PG_SIZE_2KB
				   BLOCK_SIZE = 0x1 = 01b = BK_SIZE_128KB
				   DEVICE_SIZE = 0x5 = 101b = DVC_SIZE_128MB
				   DEVICE_WIDTH = 0x0 = 0b = DVC_WIDTH_8
				   FUL_ADR_BYTES = 5 = 101b
				   COL_ADR_BYTES = 2 = 010b
				   BLK_ADR_BYTES = 3 = 011b
				 */
				nand_config &= ~0x30000000;
				nand_config |= 0x10000000; // bit 29:28 = 1 ===> 128K erase block
				//nand_config = 0x55042200; //128MB, 0x55052300  for 256MB
				chip->ctrl_write(BCHP_NAND_CONFIG, nand_config);

				break;

			case 2:
			case 3:
				/* Small page, 16K erase block
				   PAGE_SIZE = 0x0 = 0b = PG_SIZE_512B
				   BLOCK_SIZE = 0x0 = 0b = BK_SIZE_16KB
				   DEVICE_SIZE = 0x5 = 101b = DVC_SIZE_128MB
				   DEVICE_WIDTH = 0x0 = 0b = DVC_WIDTH_8
				   FUL_ADR_BYTES = 5 = 101b
				   COL_ADR_BYTES = 2 = 010b
				   BLK_ADR_BYTES = 3 = 011b
				 */
				nand_config &= ~0x70000000;
				chip->ctrl_write(BCHP_NAND_CONFIG, nand_config);

				break;

			default:
				printk(KERN_ERR "%s: DevId %08x not supported\n", __FUNCTION__, (unsigned int) chip->device_id);
				BUG();
				break;
		}
#elif CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_3_0
		{
			unsigned char devId3rdByte =  (chip->device_id >> 8) & 0xff;

			chip->cellinfo = devId3rdByte & NAND_CI_CELLTYPE_MSK;

			if (FLASHTYPE_SAMSUNG == brcmnand_maf_id && \
				(brcmnand_dev_id == SAMSUNG_K9LBG08U0M)) 
			{
				unsigned long devIdExt = chip->ctrl_read(BCHP_NAND_FLASH_DEVICE_ID_EXT);
				unsigned char devId5thByte = (devIdExt & 0xff000000) >> 24;
				unsigned int nbrPlanes;
				unsigned int planeSizeMB, chipSizeMB, nandConfigChipSize;

printk("5th ID byte = %02x, extID = %08lx\n", devId5thByte, devIdExt);

				switch(devId5thByte & SAMSUNG_5THID_NRPLANE_MASK) {
				case SAMSUNG_5THID_NRPLANE_1:
					nbrPlanes = 1;
					break;
				case SAMSUNG_5THID_NRPLANE_2:
					nbrPlanes = 2;
					break;
				case SAMSUNG_5THID_NRPLANE_4:
					nbrPlanes = 4;
					break;
				case SAMSUNG_5THID_NRPLANE_8:
					nbrPlanes = 8;
					break;
				}
printk("nbrPlanes = %d\n", nbrPlanes);

				/*
				#define SAMSUNG_5THID_PLANESZ_64Mb	0x00
				#define SAMSUNG_5THID_PLANESZ_128Mb	0x10
				#define SAMSUNG_5THID_PLANESZ_256Mb	0x20
				#define SAMSUNG_5THID_PLANESZ_512Mb	0x30
				#define SAMSUNG_5THID_PLANESZ_1Gb	0x40
				#define SAMSUNG_5THID_PLANESZ_2Gb	0x50
				#define SAMSUNG_5THID_PLANESZ_4Gb	0x60
				#define SAMSUNG_5THID_PLANESZ_8Gb	0x70
				*/
				// planeSize starts at (64Mb/8) = 8MB;
				planeSizeMB = 8 << ((devId5thByte & SAMSUNG_5THID_PLANESZ_MASK) >> 4);
				chipSizeMB = planeSizeMB*nbrPlanes;
printk("planeSizeMB = %d, chipSizeMB=%d,0x%04x, planeSizeMask=%08x\n", planeSizeMB, chipSizeMB, chipSizeMB, devId5thByte & SAMSUNG_5THID_PLANESZ_MASK);
				/* NAND Config register starts at 4MB for chip size */
				nandConfigChipSize = ffs(chipSizeMB >> 2) - 1;

printk("nandConfigChipSize = %04x\n", nandConfigChipSize);
				/* Correct chip Size accordingly, bit 24-27 */
				nand_config &= ~(0x7 << 24);
				nand_config |= (nandConfigChipSize << 24); 
				chip->ctrl_write(BCHP_NAND_CONFIG, nand_config);				
			}
		}
#endif
	}
	
	brcmnand_decode_config(chip, nand_config);

	// Also works for dummy entries, but no adjustments possible
	brcmnand_adjust_timings(chip, &brcmnand_chips[i]);

	/* Flash device information */
	brcmnand_print_device_info(&brcmnand_chips[i], chip);
	chip->options = brcmnand_chips[i].options;
		
	/* BrcmNAND page size & block size */	
	mtd->writesize = chip->pageSize; 		
	mtd->oobsize = mtd->writesize >> 5; // tht - 16 byte OOB for 512B page, 64B for 2K page
	mtd->erasesize = chip->blockSize;

	/* Fix me: When we have both a NOR and NAND flash on board */
	/* For now, we will adjust the mtd->size for version 0.0 and 0.1 later in scan routine */

	if (chip->numchips == 0) 
		chip->numchips = 1;
#ifdef MTD_LARGE
	chip->mtdSize = mtd64_mul32(chip->chipSize, chip->numchips);
#else
	chip->mtdSize = __ll_mult32(chip->chipSize, chip->numchips);
#endif
#ifdef MTD_LARGE
	hi = mtd64_ll_high(chip->mtdSize);
	lo = mtd64_ll_low(chip->mtdSize);
	do_mtd_div64_32(rs, hi, lo, chip->blockSize, rem);
	mtd->numblks = (uint64_t) rs;
#else
	mtd->size = __ll_low(chip->mtdSize); // Nothing we can do really
#endif
	//mtd->size_hi = __ll_high(chip->mtdSize);

	/* Version ID */
	version_id = chip->ctrl_read(BCHP_NAND_REVISION);
#ifdef MTD_LARGE
	printk(KERN_INFO "BrcmNAND version = 0x%04x %dMB @%p\n", 
		version_id, mtd64_ll_low(mtd64_rshft32(chip->chipSize, 20)), chip->vbase);
#else
	printk(KERN_INFO "BrcmNAND version = 0x%04x %dMB @%p\n", 
		version_id, chip->chipSize>>20, chip->vbase);
#endif

	return 0;
}

/**
 * brcmnand_suspend - [MTD Interface] Suspend the BrcmNAND flash
 * @param mtd		MTD device structure
 */
static int brcmnand_suspend(struct mtd_info *mtd)
{
	DEBUG(MTD_DEBUG_LEVEL3, "-->%s  \n", __FUNCTION__);
	return brcmnand_get_device(mtd, FL_PM_SUSPENDED);
}

/**
 * brcmnand_resume - [MTD Interface] Resume the BrcmNAND flash
 * @param mtd		MTD device structure
 */
static void brcmnand_resume(struct mtd_info *mtd)
{
	struct brcmnand_chip * chip = mtd->priv;

	DEBUG(MTD_DEBUG_LEVEL3, "-->%s  \n", __FUNCTION__);
	if (chip->state == FL_PM_SUSPENDED)
		brcmnand_release_device(mtd);
	else
		printk(KERN_ERR "resume() called for the chip which is not"
				"in suspended state\n");
}



static void fill_ecccmp_mask(struct mtd_info *mtd)
{
	struct brcmnand_chip * chip = mtd->priv;
	int i, len;
	
	struct nand_oobfree *free = chip->ecclayout->oobfree;
	unsigned char* myEccMask = (unsigned char*) eccmask; // Defeat const

	/* 
	 * Should we rely on eccmask being zeroed out
	 */
	for (i=0; i < ARRAY_SIZE(eccmask); i++) {
		myEccMask[i] = 0;
	}
	/* Write 0xFF where there is a free byte */
	for (i = 0, len = 0; 
		len < chip->oobavail && len < mtd->oobsize && i < MTD_MAX_OOBFREE_ENTRIES; 
		i++) 
	{
		int to = free[i].offset;
		int num = free[i].length;

		if (num == 0) break; // End marker reached
		memcpy (&myEccMask[to], ffchars, num);
		len += num;
	}
}

/*
 * Sort Chip Select array into ascending sequence, and validate chip ID
 * We have to sort the CS in order not to use a wrong order when the user specify
 * a wrong order in the command line.
 */
static int
brcmnand_sort_chipSelects(struct mtd_info *mtd , int maxchips, int* argNandCS, int* chipSelect)
{
	int i;
	int cs[MAX_NAND_CS];
	struct brcmnand_chip* chip = (struct brcmnand_chip*) mtd->priv;
	

	chip->numchips = 0;
	for (i=0; i<MAX_NAND_CS; i++) {
		chip->CS[i] = cs[i] = -1;
	}
	for (i=0; i<maxchips; i++) {
		cs[argNandCS[i]] = argNandCS[i];
	}
	for (i=0; i<MAX_NAND_CS;i++) {
		if (cs[i] != -1) {
			chip->CS[chip->numchips++] = cs[i];
			printk("i=%d, CS[%d] = %d\n", i, chip->numchips-1, cs[i]);
		}
	}

	return 0;
}

/*
 * Make sure that all NAND chips have same ID
 */
static int
brcmnand_validate_cs(struct mtd_info *mtd )
{
	struct brcmnand_chip* chip = (struct brcmnand_chip*) mtd->priv;
	int i;
	unsigned long dev_id;
	
	// Now verify that a NAND chip is at the CS
	for (i=0; i<chip->numchips; i++) {
		brcmnand_read_id(mtd, chip->CS[i], &dev_id);

		if (dev_id != chip->device_id) {
			printk(KERN_ERR "Device ID for CS[%1d] = %08lx, Device ID for CS[%1d] = %08lx\n",
				chip->CS[0], chip->device_id, chip->CS[i], dev_id);
			return 1;
		}
#ifdef MTD_LARGE
		printk("Found NAND chip on Chip Select %d, chipSize=%dMB, usable size=%lldMB, base=%lux\n", 
				chip->CS[i], mtd64_ll_low(mtd64_rshft32(chip->chipSize, 20)), mtd64_rshft32(MTD_SIZE(mtd), 20), chip->pbase);
#else
		printk("Found NAND chip on Chip Select %d, chipSize=%dMB, usable size=%dMB, base=%08x\n", 
				chip->CS[i], chip->chipSize>>20, mtd->size>>20, chip->pbase);
#endif
	}
	return 0;
}

/*
 * CS0 reset values are gone by now, since the bootloader disabled CS0 before booting Linux
 * in order to give the EBI address space to NAND.
 * We will need to read strap_ebi_rom_size in order to reconstruct the CS0 values
 * This will not be a problem, since in order to boot with NAND on CSn (n != 0), the board
 * must be strapped for NOR.
 */
static unsigned int 
get_rom_size(unsigned long* outp_cs0Base)
{
	volatile unsigned long strap_ebi_rom_size, sun_top_ctrl_strap_value;
	uint32_t romSize = 0;

#if defined(BCHP_SUN_TOP_CTRL_STRAP_VALUE_0_strap_ebi_rom_size_MASK)
	sun_top_ctrl_strap_value = *(volatile unsigned long*) (0xb0000000|BCHP_SUN_TOP_CTRL_STRAP_VALUE_0);
	strap_ebi_rom_size = sun_top_ctrl_strap_value & BCHP_SUN_TOP_CTRL_STRAP_VALUE_0_strap_ebi_rom_size_MASK;
	strap_ebi_rom_size >>= BCHP_SUN_TOP_CTRL_STRAP_VALUE_0_strap_ebi_rom_size_SHIFT;
#elif defined(BCHP_SUN_TOP_CTRL_STRAP_VALUE_strap_ebi_rom_size_MASK)
	sun_top_ctrl_strap_value = *(volatile unsigned long*) (0xb0000000|BCHP_SUN_TOP_CTRL_STRAP_VALUE);
	strap_ebi_rom_size = sun_top_ctrl_strap_value & BCHP_SUN_TOP_CTRL_STRAP_VALUE_strap_ebi_rom_size_MASK;
	strap_ebi_rom_size >>= BCHP_SUN_TOP_CTRL_STRAP_VALUE_strap_ebi_rom_size_SHIFT;
#elif defined(CONFIG_MIPS_BCM3548)
	printk("FIXME: no strap option for rom size on 3548\n");
	BUG();
#else
#error "Don't know how to find the ROM size"
#endif

	// Here we expect these values to remain the same across platforms.
	// Some customers want to have a 2MB NOR flash, but I don't see how that is possible.
	switch(strap_ebi_rom_size) {
	case 0:
		romSize = 64<<20;
		*outp_cs0Base = (0x20000000 - romSize) | BCHP_EBI_CS_BASE_0_size_SIZE_64MB;
		break;
	case 1:
		romSize = 16<<20;
		*outp_cs0Base = (0x20000000 - romSize) | BCHP_EBI_CS_BASE_0_size_SIZE_16MB;
		break;
	case 2:
		romSize = 8<<20;
		*outp_cs0Base = (0x20000000 - romSize) | BCHP_EBI_CS_BASE_0_size_SIZE_8MB;
		break;
	case 3:
		romSize = 4<<20;
		*outp_cs0Base = (0x20000000 - romSize) | BCHP_EBI_CS_BASE_0_size_SIZE_4MB;
		break;
	default:
		printk("%s: Impossible Strap Value %08lx for BCHP_SUN_TOP_CTRL_STRAP_VALUE\n", 
			__FUNCTION__, sun_top_ctrl_strap_value);
		BUG();
	}
	return romSize;
}


static void brcmnand_prepare_reboot_priv(struct mtd_info *mtd)
{
	/* 
	 * Must set NAND back to Direct Access mode for reboot, but only if NAND is on CS0
	 */

	struct brcmnand_chip* this;

	if (mtd) {
		this = (struct brcmnand_chip*) mtd->priv;
		brcmnand_get_device(mtd, BRCMNAND_FL_XIP);
	}
	else {
		/*
		 * Prevent further access to the NAND flash, we are rebooting 
		 */
		this = brcmnand_get_device_exclusive();
	}

	// PR41560: Handle boot from NOR but open NAND flash for access in Linux
	if (!is_bootrom_nand()) {
		// Restore CS0 in order to allow boot from NOR.

		//int ret = -EFAULT;
		int i; 
		int csNand; // Which CS is NAND
		volatile unsigned long cs0Base, cs0Cnfg, cs0BaseAddr, csNandSelect;
		volatile unsigned long csNandBase[MAX_NAND_CS], csNandCnfg[MAX_NAND_CS];
		unsigned int romSize;
		
		romSize = get_rom_size((unsigned long*) &cs0Base);
//printk("ROM size is %dMB\n", romSize >>20);
		
		cs0BaseAddr = cs0Base & BCHP_EBI_CS_BASE_0_base_addr_MASK;

		cs0Cnfg = *(volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_CONFIG_0);

		// Turn off NAND CS
		for (i=0; i < this->numchips; i++) {
			csNand = this->CS[i];

			if (csNand == 0) {
				printk("%s: Call this routine only if NAND is not on CS0\n", __FUNCTION__);
			}

#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
			BUG_ON(csNand > 5);
#else
			BUG_ON(csNand > 8);
#endif
			csNandBase[i] = *(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_BASE_0 + 8*csNand);
			csNandCnfg[i] = *(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_CONFIG_0 + 8*csNand);

			// Turn off NAND, must turn off both NAND_CS_NAND_SELECT and CONFIG.
			// We turn off the CS_CONFIG here, and will turn off NAND_CS_NAND_SELECT for all CS at once,
			// outside the loop.
			*(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_CONFIG_0 + 8*csNand) = 
				csNandCnfg[i] & (~BCHP_EBI_CS_CONFIG_0_enable_MASK);

		}
		
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_0_1
		csNandSelect = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);

		brcmnand_ctrl_write(BCHP_NAND_CS_NAND_SELECT, csNandSelect & 
			~(
#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
				BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_SEL_MASK
				| BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_SEL_MASK
				| BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_SEL_MASK
				| BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_SEL_MASK
				| BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_SEL_MASK
				| BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK
#else
				0x0000003E	/* Not documented on V1.0+ */
#endif // Version < 1.0
			));
#endif // version >= 0.1
		
//printk("Turn on NOR\n");
		// Turn on NOR on CS0
		*(volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_CONFIG_0) = 
			cs0Cnfg | BCHP_EBI_CS_CONFIG_0_enable_MASK;

//printk("returning from reboot\n");
		// We have turned on NOR, just return, leaving NAND locked
		// The CFE will straighten out everything.
		return;
	}
		
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	// Otherwise if NAND is on CS0, turn off direct access before rebooting
	if (this->CS[0] == 0) { // Only if on CS0
		volatile unsigned long nand_select;

		nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
		//printk("%s: B4 nand_select = %08x\n", __FUNCTION__, (uint32_t) nand_select);
		
		// THT: Set Direct Access bit 
		nand_select |= BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK;
		brcmnand_ctrl_write(BCHP_NAND_CS_NAND_SELECT, nand_select);

		//nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
		//printk("%s: After nand_select = %08x\n", __FUNCTION__, (uint32_t)  nand_select);
	}
	
#endif  //#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0


	return;
}

// In case someone reboot w/o going thru the MTD notifier mechanism.
void brcmnand_prepare_reboot(void)
{
	brcmnand_prepare_reboot_priv(NULL);
}
EXPORT_SYMBOL(brcmnand_prepare_reboot);



static int brcmnand_reboot_cb(struct notifier_block *nb, unsigned long val, void *v)
{
	struct mtd_info *mtd;

	mtd = container_of(nb, struct mtd_info, reboot_notifier);
	brcmnand_prepare_reboot_priv(mtd);
	return NOTIFY_DONE;
}

/**
 * brcmnand_scan - [BrcmNAND Interface] Scan for the BrcmNAND device
 * @param mtd		MTD device structure
 * @param maxchips	Number of chips to scan for
 *
 * This fills out all the not initialized function pointers
 * with the defaults.
 * The flash ID is read and the mtd/chip structures are
 * filled with the appropriate values.
 *
 * THT: For now, maxchips should always be 1.
 */
int brcmnand_scan(struct mtd_info *mtd , int maxchips )
{
	struct brcmnand_chip* chip = (struct brcmnand_chip*) mtd->priv;
	//unsigned char brcmnand_maf_id;
	int err, i;
	volatile unsigned long nand_select, cs;
	unsigned int version_id;
	unsigned int version_major;
	unsigned int version_minor;

	if (!chip->ctrl_read)
		chip->ctrl_read = brcmnand_ctrl_read;
	if (!chip->ctrl_write)
		chip->ctrl_write = brcmnand_ctrl_write;
	if (!chip->ctrl_writeAddr)
		chip->ctrl_writeAddr = brcmnand_ctrl_writeAddr;

#if 0
	if (!chip->read_raw)
		chip->read_raw = brcmnand_read_raw;
	if (!chip->read_pageoob)
		chip->read_pageoob = brcmnand_read_pageoob;
#endif

	if (!chip->write_is_complete)
		chip->write_is_complete = brcmnand_select_write_is_complete;
	
	if (!chip->wait)
		chip->wait = brcmnand_wait;

	if (!chip->block_markbad)
		chip->block_markbad = brcmnand_default_block_markbad;
	if (!chip->scan_bbt)
		chip->scan_bbt = brcmnand_default_bbt;
	if (!chip->erase_bbt)
		chip->erase_bbt = brcmnand_erase_bbt;

#if CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_0_0
	cs = 0;
	chip->CS[0] = 0;
	chip->numchips = 1;

#elif CONFIG_MTD_BRCMNAND_VERSION == CONFIG_MTD_BRCMNAND_VERS_0_1
	/*
	 * Read NAND strap option to see if this is on CS0 or CSn 
	 */
	{
		int i;
		
		nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
		cs = 0;
		for (i=0; i<6; i++) {
			if (nand_select & (BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK<<i)) {
				chip->CS[0] = cs = i;
				break;  // Only 1 chip select is allowed
			}
		}
	}
	chip->numchips = 1;

#elif CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	/*
	  * For now, we can only support up to 1 chip using BCHP_NAND_CS_NAND_SELECT.  
	  * We have to use kernel command line parameter 
	  * to support more than one chip selects.  
	  * May be future HW will allow us to read BCHP_NAND_CS_NAND_SELECT again.
	  */
	/*
	 * Read NAND strap option to see if this is on CS0 or CSn 
	 */
	if (gNumNand == 0) {
		int i;
		
		nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
		cs = 0;
		// We start at 1 since 0 is used for Direct Addressing.
		// These bits are functional in v1.0 for backward compatibility, but we can only select 1 at a time.
		for (i=1; i<6; i++) {
			if (nand_select & (BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK<<i)) {
				chip->CS[0] = cs = i;
				break;  // Only 1 chip select is allowed
			}
		}
		chip->numchips = 1;
	}
	else { // Chip Select via Kernel parameters, currently the only way to allow more than one CS to be set
		//cs = chip->numchips = gNumNand;
		if (brcmnand_sort_chipSelects(mtd, maxchips, gNandCS, chip->CS))
			return (-EINVAL);
		cs = chip->CS[chip->numchips - 1];
PRINTK("gNumNand=%d, cs=%d\n", gNumNand, cs);
	}
	
#elif CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_2_0
  	/* 
  	 * Starting with version 2.0 (bcm7118C0 and later, 
  	 * We can use EBI_CS_USES_NAND  Registers to find out where the NAND
  	 * chips are (which CS) 
  	 */
  	if (gNumNand > 0) { /* Kernel argument nandcs=<comma-sep-list> override CFE settings */
		if (brcmnand_sort_chipSelects(mtd, maxchips, gNandCS, this->CS))
			return (-EINVAL);
		cs = this->CS[this->numchips - 1];
PRINTK("gNumNand=%d, cs=%d\n", gNumNand, cs);
  	}
	else {
		
		/* Load the gNandCS_priv[] array from EBI_CS_USES_NAND values,
		 * same way that get_options() does, i.e. first entry is gNumNand
		 */
		int nandCsShift, i;
		int numNand = 0;
		int nandCS[MAX_NAND_CS];

		for (i = 0; i< MAX_NAND_CS; i++) {
			nandCS[i] = -1;
		}
		
		nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
		for (i=0, nandCsShift = BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_USES_NAND_SHIFT;
			nandCsShift <= BCHP_NAND_CS_NAND_SELECT_EBI_CS_7_USES_NAND_SHIFT;
			nandCsShift ++)
		{
			if (nand_select & (1 << nandCsShift)) {
				nandCS[i] = nandCsShift - BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_USES_NAND_SHIFT;
				PRINTK("Found NAND on CS%1d\n", nandCS[i]);
				i++;
			}
		}
		numNand = i;
		if (brcmnand_sort_chipSelects(mtd, maxchips, nandCS, this->CS))
			return (-EINVAL);
		cs = this->CS[this->numchips - 1];
PRINTK("gNumNand=%d, cs=%d\n", gNumNand, cs);
	}

  
#else
	#error "Unknown Broadcom NAND controller version"
#endif /* Versions >= 1.0 */


PRINTK("brcmnand_scan: Calling brcmnand_probe\n");
	if (brcmnand_probe(mtd, cs))
		return -ENXIO;

#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
	if (chip->numchips > 0) {
		if (brcmnand_validate_cs(mtd))
			return (-EINVAL);
	}
#endif

PRINTK("brcmnand_scan: Done brcmnand_probe\n");

	/* Will correct it for MLC later */
	chip->ecclevel = BRCMNAND_ECC_HAMMING;

#if CONFIG_MTD_BRCMNAND_VERSION <= CONFIG_MTD_BRCMNAND_VERS_0_1	
	if (cs) {
		volatile unsigned long wr_protect;
		volatile unsigned long acc_control;

		chip->numchips = 1;
		if (chip->chipSize >= (128 << 20)) {
			chip->pbase = 0x11000000; /* Skip 16MB EBI Registers */
#ifdef MTD_LARGE
			mtd->numblks = (chip->chipSize - (16<<20)) >> chip->erase_shift; // Maximum size on a 128MB/256MB flash
			chip->mtdSize = MTD_SIZE(mtd);
#else
			mtd->size = chip->chipSize - (16<<20); // Maximum size on a 128MB/256MB flash
			//mtd->size_hi = 0;
			chip->mtdSize = mtd->size;
#endif
		}
/*
		else if (chip->chipSize == (256 << 20)) {
			chip->pbase = 0x11000000; // Skip 16MB EBI Registers 
			mtd->size = 240<<20; // Maximum size on a 256MB flash, provided CS0/NOR is disabled
		}
 */
		else {
#ifdef MTD_LARGE
			chip->pbase = (unsigned long) mtd64_sub(0x18000000LL, chip->chipSize);
			mtd->numblks = mtd64_rshft32(chip->chipSize, chip->erase_shift);
			chip->mtdSize = MTD_SIZE(mtd);
#else
			chip->pbase = 0x18000000 - chip->chipSize;
			mtd->size = chip->chipSize;
			chip->mtdSize = mtd->size;
#endif
			//mtd->size_hi = 0;
		}
#ifdef MTD_LARGE
		printk("Found NAND chip on Chip Select %d, chipSize=%dMB, usable size=%dMB, base=%08x\n", 
			(int) cs, mtd64_ll_low(mtd64_rshft32(chip->chipSize, 20)), mtd64_ll_low(mtd64_rshft32(MTD_SIZE(mtd), 20)), (unsigned int) chip->pbase);
#else
		printk("Found NAND chip on Chip Select %d, chipSize=%dMB, usable size=%dMB, base=%08x\n", 
			cs, chip->chipSize>>20, mtd->size>>20, chip->pbase);
#endif


		/*
		 * When NAND is on CS0, it reads the strap values and set up accordingly.
		 * WHen on CS1, some configurations must be done by SW
		 */

		// Set Write-Unprotect.  This register is sticky, so if someone already set it, we are out of luck
		wr_protect = brcmnand_ctrl_read(BCHP_NAND_BLK_WR_PROTECT);
		if (wr_protect) {
			printk("Unprotect Register B4: %08x.  Please do a hard power recycle to reset\n", wr_protect);
			// THT: Actually we should punt here, as we cannot zero the register.
		} 
		brcmnand_ctrl_write(BCHP_NAND_BLK_WR_PROTECT, 0); // This will not work.
		if (wr_protect) {
			printk("Unprotect Register after: %08x\n", brcmnand_ctrl_read(BCHP_NAND_BLK_WR_PROTECT));
		}

		// Enable HW ECC.  This is another sticky register.
		acc_control = brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL);
		printk("ACC_CONTROL B4: %08x\n", acc_control);
		 
		brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control | BCHP_NAND_ACC_CONTROL_RD_ECC_BLK0_EN_MASK);
		if (!(acc_control & BCHP_NAND_ACC_CONTROL_RD_ECC_BLK0_EN_MASK)) {
			printk("ACC_CONTROL after: %08x\n", brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL));
		}
	}
	else {
		/* NAND chip on Chip Select 0 */
		chip->CS[0] = 0;
	
		chip->numchips = 1;
		
#ifdef MTD_LARGE
		/* Set up base, based on flash size */
		if (mtd64_is_gteq(chip->chipSize, (uint64_t) ((uint64_t)256LL << 20))) {
			chip->pbase = 0x12000000;
			mtd->numblks = mtd64_rshft32((uint64_t)(0x20000000 - chip->pbase), chip->erase_shift);
		} else {
			//TODO sidc - is this true for large flash ? 
			/* We know that flash endAddr is 0x2000_0000 */
			chip->pbase = mtd64_sub((uint64_t) 0x20000000, chip->chipSize);
			mtd->numblks = mtd64_rshft32(chip->chipSize, chip->erase_shift);
		}
		chip->mtdSize = MTD_SIZE(mtd);

		printk("Found NAND chip on Chip Select 0, size=%dMB, base=%08x\n", MTD_SIZE(mtd)>>20, chip->pbase);
#else
		/* Set up base, based on flash size */
		if (chip->chipSize >= (256 << 20)) {
			chip->pbase = 0x12000000;
			mtd->size = 0x20000000 - chip->pbase; // THT: This is different than chip->chipSize
		} else {
			/* We know that flash endAddr is 0x2000_0000 */
			chip->pbase = 0x20000000 - chip->chipSize;
			mtd->size = chip->chipSize;
		}
		//mtd->size_hi = 0;
		chip->mtdSize = mtd->size;

		printk("Found NAND chip on Chip Select 0, size=%dMB, base=%08x\n", mtd->size>>20, chip->pbase);
#endif
	}
	chip->vbase = (void*) KSEG1ADDR(chip->pbase);
	
#else
	/*
	 * v1.0 controller and after
	 */
	// This table is in the Architecture Doc
	// pbase is the physical address of the "logical" start of flash.  Logical means how Linux sees it,
	// and is given by the partition table defined in bcm7xxx-nand.c
	// The "physical" start of the flash is always at 1FC0_0000
#ifdef MTD_LARGE
	if (mtd64_is_lteq(chip->chipSize, (uint64_t) ((uint64_t) 256LL <<20))) 
		//TODO sidc check this 
		chip->pbase = (unsigned long) mtd64_sub((uint64_t) 0x20000000LL, chip->chipSize);
	else // 512MB and up
		chip->pbase = 0; 
#else
	if (chip->chipSize <= (256<<20)) 
		chip->pbase = 0x20000000 - chip->chipSize;
	else // 512MB and up
		chip->pbase = 0; 
#endif
	// vbase is the address of the flash cache array
	chip->vbase = (void*) (0xb0000000+BCHP_NAND_FLASH_CACHEi_ARRAY_BASE);  // Start of Buffer Cache
	// Already set in probe mtd->size = chip->chipSize * chip->numchips;
	// Make sure we use Buffer Array access, not direct access, Clear CS0
	nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
	printk("%s: B4 nand_select = %08x\n", __FUNCTION__, (uint32_t) nand_select);
	
#if 0// THT 8/27/08: RDB now says that we should leave this bit on, as Register Array Addressing can be
// used regardless of its value

	//chip->directAccess = !(nand_select & BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK);
	// THT: Clear Direct Access bit 
	nand_select &= ~(BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK);
	brcmnand_ctrl_write(BCHP_NAND_CS_NAND_SELECT, nand_select);
#endif

	nand_select = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);
	printk("%s: After nand_select = %08x\n", __FUNCTION__, (uint32_t)  nand_select);
	chip->directAccess = !(nand_select & BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK);


	/* Handle Partial Write Enable configuration for MLC
	 * {FAST_PGM_RDIN, PARTIAL_PAGE_EN}
	 * {0, 0} = 1 write per page, no partial page writes (required for MLC flash, suitable for SLC flash)
	 * {1, 1} = 4 partial page writes per 2k page (SLC flash only)
	 * {0, 1} = 8 partial page writes per 2k page (not recommended)
	 * {1, 0} = RESERVED, DO NOT USE
 	 */
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_3_0
// CS0
#define BCHP_NAND_ACC_CONTROL_0_BCH_4		(BRCMNAND_ECC_BCH_4 << BCHP_NAND_ACC_CONTROL_ECC_LEVEL_0_SHIFT)

// CSn n > 0
#define BCHP_NAND_ACC_CONTROL_N_BCH_4		(BRCMNAND_ECC_BCH_4 << BCHP_NAND_ACC_CONTROL_ECC_LEVEL_SHIFT)

	if (NAND_IS_MLC(chip)) {
		volatile unsigned long acc_control, org_acc_control;
		int csi = 0; // Index into chip->CS array
		
		org_acc_control = acc_control = brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL);
		printk("ACC_CONTROL for MLC NAND: %08lx\n", acc_control);

		/*
		 * For now, we only support same ECC level for both block0 and other blocks
		 */
		// Verify BCH-4 ECC: Handle CS0 block0
//		if (chip->CS[csi] == 0) 
		{
			if (((acc_control & BCHP_NAND_ACC_CONTROL_ECC_LEVEL_0_MASK) != 
				BCHP_NAND_ACC_CONTROL_0_BCH_4) ||
				((acc_control & BCHP_NAND_ACC_CONTROL_ECC_LEVEL_MASK) != 
				BCHP_NAND_ACC_CONTROL_N_BCH_4))
			{
				acc_control &= ~(BCHP_NAND_ACC_CONTROL_ECC_LEVEL_0_MASK|
					BCHP_NAND_ACC_CONTROL_ECC_LEVEL_MASK);
				acc_control |= BCHP_NAND_ACC_CONTROL_0_BCH_4 | BCHP_NAND_ACC_CONTROL_N_BCH_4;
				brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control );
				printk("Corrected ECC to BCH-4: ACC_CONTROL = %08lx from %08lx\n", acc_control, org_acc_control);
			}
			csi++; // Look at next CS
		}
#if 0
		// Handle CS > 0, if any
		if (csi < chip->numchips) {
			if ((acc_control & BCHP_NAND_ACC_CONTROL_ECC_LEVEL_MASK) != 
				BCHP_NAND_ACC_CONTROL_N_BCH_4) 
			{
				acc_control &= ~(BCHP_NAND_ACC_CONTROL_ECC_LEVEL_MASK);
				acc_control |= BCHP_NAND_ACC_CONTROL_N_BCH_4;
				brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control );
				printk("Corrected ECC to BCH-4: ACC_CONTROL = %08x\n", acc_control);
			}	
		}
#endif
		chip->ecclevel = BRCMNAND_ECC_BCH_4;

		/* Set FAST_PGM_RDIN, PARTIAL_PAGE_EN  to {0, 0} for NOP=1 */
		if (acc_control & BCHP_NAND_ACC_CONTROL_FAST_PGM_RDIN_MASK) 
		{
			acc_control &= ~(BCHP_NAND_ACC_CONTROL_FAST_PGM_RDIN_MASK);
			brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control );
			printk("Corrected PARTIAL_PAGE_EN: ACC_CONTROL = %08lx\n", acc_control);
		}
		if (acc_control & BCHP_NAND_ACC_CONTROL_PARTIAL_PAGE_EN_MASK) 
		{
			acc_control &= ~(BCHP_NAND_ACC_CONTROL_PARTIAL_PAGE_EN_MASK);
			brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control );
			printk("Corrected PARTIAL_PAGE_EN: ACC_CONTROL = %08lx\n", acc_control);
		}			
#if 1
		/* THT Disable Optimization for 2K page */
		acc_control &= ~(BCHP_NAND_ACC_CONTROL_WR_PREEMPT_EN_MASK|BCHP_NAND_ACC_CONTROL_PAGE_HIT_EN_MASK);
		brcmnand_ctrl_write(BCHP_NAND_ACC_CONTROL, acc_control );
		printk("Disable WR_PREEMPT and PAGE_HIT_EN: ACC_CONTROL = %08lx\n", acc_control);
#endif
	}else {   
	 	/* SLC will use Hamming for now, so nothing need to be done here,
	 	 * Just print out ACC_CONTROL to catch any erronous straps
	 	 */
		volatile unsigned long acc_control;
		
		acc_control = brcmnand_ctrl_read(BCHP_NAND_ACC_CONTROL);
		printk("ACC_CONTROL for SLC NAND: %08lx\n", acc_control);
	}
#endif // Version 3.0+
#endif // Version 1.0+

PRINTK("%s 10\n", __FUNCTION__);

	chip->bbt_erase_shift =  ffs(mtd->erasesize) - 1;

	/* Calculate the address shift from the page size */	
	chip->page_shift = ffs(mtd->writesize) - 1;
	chip->bbt_erase_shift = chip->phys_erase_shift = ffs(mtd->erasesize) - 1;
	chip->chip_shift = __ll_ffs(chip->chipSize) - 1;

	printk(KERN_INFO "page_shift=%d, bbt_erase_shift=%d, chip_shift=%d, phys_erase_shift=%d\n",
		chip->page_shift, chip->bbt_erase_shift , chip->chip_shift, chip->phys_erase_shift);

	/* Set the bad block position */
	/* NAND_LARGE_BADBLOCK_POS also holds for MLC NAND */
	chip->badblockpos = mtd->writesize > 512 ? 
		NAND_LARGE_BADBLOCK_POS : NAND_SMALL_BADBLOCK_POS;




PRINTK("%s 20\n", __FUNCTION__);
	
	chip->state = FL_READY;
	init_waitqueue_head(&chip->wq);
	spin_lock_init(&chip->chip_lock);

	/* The number of bytes available for the filesystem to place fs dependend
	 * oob data */
//PRINTK( "Deterimining chip->oobavail, chip->autooob=%p \n", chip->autooob);

	/* Version ID */
	version_id = chip->ctrl_read(BCHP_NAND_REVISION);
	version_major = (version_id & 0xff00) >> 8;
	version_minor = (version_id & 0xff);
#ifdef MTD_LARGE
	printk(KERN_INFO "Brcm NAND controller version = %x.%x NAND flash size %dMB @%08x\n", 
		version_major, version_minor, mtd64_ll_low(mtd64_rshft32(chip->chipSize, 20)), (uint32_t) chip->pbase);
#else
	printk(KERN_INFO "Brcm NAND controller version = %x.%x NAND flash size %dMB @%08x\n", 
		version_major, version_minor, chip->chipSize>>20, (uint32_t) chip->pbase);
#endif


PRINTK("%s 30\n", __FUNCTION__);
	/*
	 * Initialize the eccmask array for ease of verifying OOB area.
	 */
	fill_ecccmp_mask(mtd);
	

	/* Store the number of chips and calc total size for mtd */
	//chip->numchips = i;
	//mtd->size = i * chip->chipSize;

	/* Preset the internal oob write buffer */
	memset(BRCMNAND_OOBBUF(chip->buffers), 0xff, mtd->oobsize);

	/*
	 * If no default placement scheme is given, select an appropriate one
	 */
PRINTK("%s 40, mtd->oobsize=%d\n", __FUNCTION__, mtd->oobsize);
	if (!chip->ecclayout) {
PRINTK("%s 42, mtd->oobsize=%d\n", __FUNCTION__, mtd->oobsize);
		switch (mtd->oobsize) {
#if 0
		case 8:
			chip->ecc.layout = &nand_oob_8;
			break;
#endif
		case 16:
			chip->ecclayout = &brcmnand_oob_16;
			break;
			
		case 64:
			if (NAND_IS_MLC(chip)) {
				switch (mtd->writesize) {
				case 4096:
					chip->ecclayout = &brcmnand_oob_bch4_4k;
					break;
				case 2048:
					chip->ecclayout = &brcmnand_oob_bch4_2k;
					break;
				default:
					printk(KERN_ERR "Unsupported page size of %d\n", mtd->writesize);
					BUG();
					break;
				}
			}
			else {
				chip->ecclayout = &brcmnand_oob_64;
			}
			break;
			
		case 128:
			if (NAND_IS_MLC(chip)) {
				switch (mtd->writesize) {
				case 4096:
					chip->ecclayout = &brcmnand_oob_bch4_4k;
					break;

				default:
					printk(KERN_ERR "Unsupported page size of %d\n", mtd->writesize);
					BUG();
					break;
				}
			}
			else {
				printk(KERN_ERR "Unsupported SLC NAND with page size of %d\n", mtd->writesize);
				BUG();
			}
			break;
			
		default:
			printk(KERN_WARNING "No oob scheme defined for oobsize %d\n", mtd->oobsize);
			BUG();
			break;
		}
	}
	
	chip->eccsize = 512;  // Fixed for Broadcom controller
	// THT: For V.3+ controller, this is no longer true.  It is governed by ACC_CONTROL bits SPARE_AREA_SIZE
	chip->eccOobSize = 16; // Fixed for Broadcom controller

PRINTK("%s 45, mtd->oobsize=%d\n", __FUNCTION__, mtd->oobsize);
	if (!chip->read_page)
		chip->read_page = brcmnand_read_page;
	if (!chip->write_page)
		chip->write_page = brcmnand_write_page;
	if (!chip->read_page_oob)
		chip->read_page_oob = brcmnand_read_page_oob;
	if (!chip->write_page_oob)
		chip->write_page_oob = brcmnand_write_page_oob;
	if (!chip->read_oob)
		chip->read_oob = brcmnand_do_read_ops;
	if (!chip->write_oob)
		chip->write_oob = brcmnand_do_write_ops;

	/*
	 * The number of bytes available for a client to place data into
	 * the out of band area
	 */
printk(KERN_INFO "%s:  mtd->oobsize=%d\n", __FUNCTION__, mtd->oobsize);
	chip->ecclayout->oobavail = 0;
	for (i = 0; chip->ecclayout->oobfree[i].length; i++)
		chip->ecclayout->oobavail +=
			chip->ecclayout->oobfree[i].length;

printk(KERN_INFO "%s: oobavail=%d, eccsize=%d, writesize=%d\n", __FUNCTION__, 
	chip->ecclayout->oobavail, chip->eccsize, mtd->writesize);

	/*
	 * Set the number of read / write steps for one page depending on ECC
	 * mode
	 */

	chip->eccsteps = mtd->writesize / chip->eccsize;
	chip->eccbytes = brcmnand_eccbytes[chip->ecclevel];
printk(KERN_INFO "%s, eccsize=%d, writesize=%d, eccsteps=%d, ecclevel=%d, eccbytes=%d\n", __FUNCTION__, 
	chip->eccsize, mtd->writesize, chip->eccsteps, chip->ecclevel, chip->eccbytes);
//udelay(2000000);
	if(chip->eccsteps * chip->eccsize != mtd->writesize) {
		printk(KERN_WARNING "Invalid ecc parameters\n");

//udelay(2000000);
		BUG();
	}
	chip->ecctotal = chip->eccsteps * chip->eccbytes;
	mtd->eccsize = chip->eccsize;

	/* Initialize state */
	chip->state = FL_READY;

#if 0
	/* De-select the device */
	chip->select_chip(mtd, -1);
#endif

	/* Invalidate the pagebuffer reference */
	chip->pagebuf = -1;

	/* Fill in remaining MTD driver data */
	mtd->type = MTD_NANDFLASH;
	/*
	 * Now that we know what kind of NAND it is (SLC vs MLC),
	 * tell the MTD layer how to test it
	 */
	mtd->flags = NAND_IS_MLC(chip) ? MTD_CAP_MLC_NANDFLASH : MTD_CAP_NANDFLASH;
	mtd->ecctype = MTD_ECC_SW;
	
	mtd->erase = brcmnand_erase;
	mtd->point = NULL;
	mtd->unpoint = NULL;
	mtd->read = brcmnand_read;
	mtd->write = brcmnand_write;
	mtd->read_oob = brcmnand_read_oob;
	mtd->write_oob = brcmnand_write_oob;

	// Not needed?
	mtd->writev = brcmnand_writev;
	
	mtd->sync = brcmnand_sync;
	mtd->lock = NULL;
	mtd->unlock = brcmnand_unlock;
	mtd->suspend = brcmnand_suspend;
	mtd->resume = brcmnand_resume;
	mtd->block_isbad = brcmnand_block_isbad;
	mtd->block_markbad = brcmnand_block_markbad;

	/* propagate ecc.layout to mtd_info */
	mtd->ecclayout = chip->ecclayout;

	mtd->reboot_notifier.notifier_call = brcmnand_reboot_cb;
	register_reboot_notifier(&mtd->reboot_notifier);
	
	mtd->owner = THIS_MODULE;

    /*
     * Clear ECC registers 
     */
    chip->ctrl_write(BCHP_NAND_ECC_CORR_ADDR, 0);
    chip->ctrl_write(BCHP_NAND_ECC_UNC_ADDR, 0);
  
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_1_0
    chip->ctrl_write(BCHP_NAND_ECC_CORR_EXT_ADDR, 0);
    chip->ctrl_write(BCHP_NAND_ECC_UNC_EXT_ADDR, 0);
#endif
    

#ifdef CONFIG_MTD_BRCMNAND_EDU
	EDU_init();
	/* THT: External dev physAddr is the 512B Register Array EBI address */
	EDU_ldw = BCHP_PHYSICAL_OFFSET + BCHP_NAND_FLASH_CACHEi_ARRAY_BASE;
#endif

	/* Unlock whole block */
	if (mtd->unlock) {
#ifdef MTD_LARGE
		PRINTK("Calling mtd->unlock(ofs=0, MTD Size=%016x\n", MTD_SIZE(mtd));
		mtd->unlock(mtd, 0x0, MTD_SIZE(mtd));
#else
		PRINTK("Calling mtd->unlock(ofs=0, MTD Size=%08x\n", mtd->size);
		mtd->unlock(mtd, 0x0, mtd->size);
#endif
	}


PRINTK("%s 60 Calling scan_bbt\n", __FUNCTION__);
	err =  chip->scan_bbt(mtd);

#ifdef CONFIG_MTD_BRCMNAND_CORRECTABLE_ERR_HANDLING
	if(brcmnand_create_cet(mtd) < 0) {
		printk(KERN_INFO "%s: CET not created\n", __FUNCTION__);
	}
#endif

PRINTK("%s 99\n", __FUNCTION__);

print_diagnostics();
	return err;

}



#if defined( CONFIG_MIPS_BCM7401C0 ) || defined( CONFIG_MIPS_BCM7118A0 )  || defined( CONFIG_MIPS_BCM7403A0 ) 
static DEFINE_SPINLOCK(bcm9XXXX_lock);
static unsigned long misb_war_flags;

static inline void
HANDLE_MISB_WAR_BEGIN(void)
{
	/* if it is 7401C0, then we need this workaround */
	if(brcm_ebi_war)
	{	
		spin_lock_irqsave(&bcm9XXXX_lock, misb_war_flags);
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
		*(volatile unsigned long*)0xb0400b1c = 0xFFFF;
	}
}

static inline void
HANDLE_MISB_WAR_END(void)
{
	if(brcm_ebi_war)
	{	
		spin_unlock_irqrestore(&bcm9XXXX_lock, misb_war_flags);
	}
}

#else
#define HANDLE_MISB_WAR_BEGIN()
#define HANDLE_MISB_WAR_END()
#endif


/*
 * @ buff		Kernel buffer to hold the data read from the NOR flash, must be able to hold len bytes, 
 *			and aligned on word boundary.
 * @ offset	Offset of the data from CS0 (on NOR flash), must be on word boundary.
 * @ len		Number of bytes to be read, must be even number.
 *
 * returns 0 on success, negative error codes on failure.
 *
 * The caller thread may block until access to the NOR flash can be granted.
 * Further accesses to the NAND flash (from other threads) will be blocked until this routine returns.
 * The routine performs the required swapping of CS0/CS1 under the hood.
 */
int brcmnand_readNorFlash(struct mtd_info *mtd, void* buff, unsigned int offset, int len)
{
	struct brcmnand_chip* chip = (struct brcmnand_chip*) mtd->priv;
	int ret = -EFAULT;
	int i; 
	int csNand; // Which CS is NAND
	volatile unsigned long cs0Base, cs0Cnfg, cs0BaseAddr, csNandSelect;
	volatile unsigned long csNandBase[MAX_NAND_CS], csNandCnfg[MAX_NAND_CS];
	unsigned int romSize;
	volatile uint16_t* pui16 = (volatile uint16_t*) buff;
	volatile uint16_t* fp;

	if (!chip) { // When booting from CRAMFS/SQUASHFS using /dev/romblock
		chip = brcmnand_get_device_exclusive();
		mtd = (struct mtd_info*) chip->priv;
	}
	else if (brcmnand_get_device(mtd, BRCMNAND_FL_EXCLUSIVE))
		return ret;

	romSize = get_rom_size((unsigned long*) &cs0Base);
	
	cs0BaseAddr = cs0Base & BCHP_EBI_CS_BASE_0_base_addr_MASK;

	if ((len + offset) > romSize) {
		printk("%s; Attempt to read past end of CS0, (len+offset)=%08x, romSize=%dMB\n",
			__FUNCTION__, len + offset, romSize>>20);
		ret = (-EINVAL);
		goto release_device_and_out;
	}

	cs0Cnfg = *(volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_CONFIG_0);

	// Turn off NAND CS
	for (i=0; i < chip->numchips; i++) {
		csNand = chip->CS[i];

		if (csNand == 0) {
			printk("%s: Call this routine only if NAND is not on CS0\n", __FUNCTION__);
			ret = (-EINVAL);
			goto release_device_and_out;
		}

#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
		BUG_ON(csNand > 5);
#else
		BUG_ON(csNand > 7);
#endif
		csNandBase[i] = *(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_BASE_0 + 8*csNand);
		csNandCnfg[i] = *(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_CONFIG_0 + 8*csNand);

		// Turn off NAND, must turn off both NAND_CS_NAND_SELECT and CONFIG.
		// We turn off the CS_CONFIG here, and will turn off NAND_CS_NAND_SELECT for all CS at once,
		// outside the loop.
		*(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_CONFIG_0 + 8*csNand) = 
			csNandCnfg[i] & (~BCHP_EBI_CS_CONFIG_0_enable_MASK);

	}
	
#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_0_1
	csNandSelect = brcmnand_ctrl_read(BCHP_NAND_CS_NAND_SELECT);

	brcmnand_ctrl_write(BCHP_NAND_CS_NAND_SELECT, csNandSelect & 
		~(
#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
			BCHP_NAND_CS_NAND_SELECT_EBI_CS_5_SEL_MASK
			| BCHP_NAND_CS_NAND_SELECT_EBI_CS_4_SEL_MASK
			| BCHP_NAND_CS_NAND_SELECT_EBI_CS_3_SEL_MASK
			| BCHP_NAND_CS_NAND_SELECT_EBI_CS_2_SEL_MASK
			| BCHP_NAND_CS_NAND_SELECT_EBI_CS_1_SEL_MASK
			| BCHP_NAND_CS_NAND_SELECT_EBI_CS_0_SEL_MASK
#else
			0x0000003E	/* Not documented on V1.0+ */
#endif
		));
#endif

	// Turn on NOR on CS0
	*(volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_CONFIG_0) = 
		cs0Cnfg | BCHP_EBI_CS_CONFIG_0_enable_MASK;

	// Take care of MISB Bridge bug on 7401c0/7403a0/7118a0
	HANDLE_MISB_WAR_BEGIN();

	// Read NOR, 16 bits at a time, we have already checked the out-of-bound condition above.
	fp = (volatile uint16_t*) (KSEG1ADDR(cs0BaseAddr + offset));
	for (i=0; i < (len>>1); i++) {
		pui16[i] = fp[i];
	}

	HANDLE_MISB_WAR_END();

	// Turn Off NOR
	*(volatile unsigned long*) (0xb0000000|BCHP_EBI_CS_CONFIG_0) = 
		cs0Cnfg & (~BCHP_EBI_CS_CONFIG_0_enable_MASK);

	// Turn NAND back on
	for (i=0; i < chip->numchips; i++) {
		csNand = chip->CS[i];
		if (csNand == 0) {
			printk("%s: Call this routine only if NAND is not on CS0\n", __FUNCTION__);
			ret = (-EINVAL);
			goto release_device_and_out;
		}
#if CONFIG_MTD_BRCMNAND_VERSION < CONFIG_MTD_BRCMNAND_VERS_1_0
		BUG_ON(csNand > 5);
#else
		BUG_ON(csNand > 7);
#endif
		*(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_BASE_0 + 8*csNand) = csNandBase[i] ;
		*(volatile unsigned long*) (0xb0000000 + BCHP_EBI_CS_CONFIG_0 + 8*csNand) = csNandCnfg[i];
	}

#if CONFIG_MTD_BRCMNAND_VERSION >= CONFIG_MTD_BRCMNAND_VERS_0_1
	// Restore NAND_CS_SELECT
	brcmnand_ctrl_write(BCHP_NAND_CS_NAND_SELECT, csNandSelect);
#endif
	udelay(10000); // Wait for ID Configuration to stabilize
	
release_device_and_out:
	brcmnand_release_device(mtd);
//printk("<-- %s\n", __FUNCTION__);

	return ret;
}
EXPORT_SYMBOL(brcmnand_readNorFlash);

/**
 * brcmnand_release - [BrcmNAND Interface] Free resources held by the BrcmNAND device
 * @param mtd		MTD device structure
 */
void brcmnand_release(struct mtd_info *mtd)
{
	//struct brcmnand_chip * chip = mtd->priv;

#ifdef CONFIG_MTD_PARTITIONS
	/* Deregister partitions */
	del_mtd_partitions (mtd);
#endif

	/* Unregister reboot notifier */
	brcmnand_prepare_reboot_priv(mtd);
	unregister_reboot_notifier(&mtd->reboot_notifier);
	mtd->reboot_notifier.notifier_call = NULL;
	
	/* Deregister the device */
	del_mtd_device (mtd);

#if 0
	/* Buffer allocated by brcmnand_scan */
	if (chip->options & NAND_DATABUF_ALLOC)
		kfree(chip->data_buf);

	/* Buffer allocated by brcmnand_scan */
	if (chip->options & NAND_OOBBUF_ALLOC)
		kfree(chip->oob_buf);
#endif

}



