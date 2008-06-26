/***************************************************************************
 *     Copyright (c) 1999-2006, Broadcom Corporation
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
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Wed Jul 12 11:56:42 2006
 *                 MD5 Checksum         65dc148f276b8e1325bb5f85be0ccf82
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.006
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/7401/rdb/c0/bchp_pci_bridge.h $
 * 
 * Hydra_Software_Devel/1   7/14/06 12:53p jasonh
 * PR 22628: Initial version
 *
 ***************************************************************************/

#ifndef BCHP_PCI_BRIDGE_H__
#define BCHP_PCI_BRIDGE_H__

/***************************************************************************
 *PCI_BRIDGE - SATA PCI Bridge Registers
 ***************************************************************************/
#define BCHP_PCI_BRIDGE_PCI_CTRL                 0x00500200 /* PCI Bridge Control */
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX           0x00500204 /* Serial ATA Configuration Access Address */
#define BCHP_PCI_BRIDGE_SATA_CFG_DATA            0x00500208 /* Serial ATA Configuration Access Data */
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE     0x0050020c /* PCI SCB Slave Memory Window Base Address */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE 0x00500210 /* CPU to SATA PCI Memory Window Base Address */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE  0x00500214 /* CPU to SATA PCI IO Window Base Address */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_ADDR          0x00500218 /* PCI Memory Slave Retry Address */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS        0x0050021c /* PCI Memory Slave Retry Status */
#define BCHP_PCI_BRIDGE_REVISION                 0x00500220 /* PCI Bridge Revision Register */
#define BCHP_PCI_BRIDGE_SCRATCH                  0x00500224 /* PCI Bridge Scratch register */

/***************************************************************************
 *PCI_CTRL - PCI Bridge Control
 ***************************************************************************/
/* PCI_BRIDGE :: PCI_CTRL :: reserved0 [31:06] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_reserved0_MASK                    0xffffffc0
#define BCHP_PCI_BRIDGE_PCI_CTRL_reserved0_SHIFT                   6

/* PCI_BRIDGE :: PCI_CTRL :: SERR_ENABLE [05:05] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_SERR_ENABLE_MASK                  0x00000020
#define BCHP_PCI_BRIDGE_PCI_CTRL_SERR_ENABLE_SHIFT                 5
#define BCHP_PCI_BRIDGE_PCI_CTRL_SERR_ENABLE_ASSERTED              1
#define BCHP_PCI_BRIDGE_PCI_CTRL_SERR_ENABLE_DEASSERTED            0

/* PCI_BRIDGE :: PCI_CTRL :: PERR_ENABLE [04:04] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_PERR_ENABLE_MASK                  0x00000010
#define BCHP_PCI_BRIDGE_PCI_CTRL_PERR_ENABLE_SHIFT                 4
#define BCHP_PCI_BRIDGE_PCI_CTRL_PERR_ENABLE_ASSERTED              1
#define BCHP_PCI_BRIDGE_PCI_CTRL_PERR_ENABLE_DEASSERTED            0

/* PCI_BRIDGE :: PCI_CTRL :: CFG_BYTE_ALIGN [03:03] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_CFG_BYTE_ALIGN_MASK               0x00000008
#define BCHP_PCI_BRIDGE_PCI_CTRL_CFG_BYTE_ALIGN_SHIFT              3

/* PCI_BRIDGE :: PCI_CTRL :: PARK_LAST [02:02] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_PARK_LAST_MASK                    0x00000004
#define BCHP_PCI_BRIDGE_PCI_CTRL_PARK_LAST_SHIFT                   2

/* PCI_BRIDGE :: PCI_CTRL :: BUS_MASTER [01:01] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_BUS_MASTER_MASK                   0x00000002
#define BCHP_PCI_BRIDGE_PCI_CTRL_BUS_MASTER_SHIFT                  1
#define BCHP_PCI_BRIDGE_PCI_CTRL_BUS_MASTER_ASSERTED               1
#define BCHP_PCI_BRIDGE_PCI_CTRL_BUS_MASTER_DEASSERTED             0

/* PCI_BRIDGE :: PCI_CTRL :: MEMORY_SPACE [00:00] */
#define BCHP_PCI_BRIDGE_PCI_CTRL_MEMORY_SPACE_MASK                 0x00000001
#define BCHP_PCI_BRIDGE_PCI_CTRL_MEMORY_SPACE_SHIFT                0
#define BCHP_PCI_BRIDGE_PCI_CTRL_MEMORY_SPACE_ASSERTED             1
#define BCHP_PCI_BRIDGE_PCI_CTRL_MEMORY_SPACE_DEASSERTED           0

/***************************************************************************
 *SATA_CFG_INDEX - Serial ATA Configuration Access Address
 ***************************************************************************/
/* PCI_BRIDGE :: SATA_CFG_INDEX :: reserved0 [31:11] */
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_reserved0_MASK              0xfffff800
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_reserved0_SHIFT             11

/* PCI_BRIDGE :: SATA_CFG_INDEX :: FUNC_NUM [10:08] */
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_FUNC_NUM_MASK               0x00000700
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_FUNC_NUM_SHIFT              8

/* PCI_BRIDGE :: SATA_CFG_INDEX :: REG_NUM [07:00] */
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_REG_NUM_MASK                0x000000ff
#define BCHP_PCI_BRIDGE_SATA_CFG_INDEX_REG_NUM_SHIFT               0

/***************************************************************************
 *SATA_CFG_DATA - Serial ATA Configuration Access Data
 ***************************************************************************/
/* PCI_BRIDGE :: SATA_CFG_DATA :: DATA [31:00] */
#define BCHP_PCI_BRIDGE_SATA_CFG_DATA_DATA_MASK                    0xffffffff
#define BCHP_PCI_BRIDGE_SATA_CFG_DATA_DATA_SHIFT                   0

/***************************************************************************
 *PCI_SLV_MEM_WIN_BASE - PCI SCB Slave Memory Window Base Address
 ***************************************************************************/
/* PCI_BRIDGE :: PCI_SLV_MEM_WIN_BASE :: BASE_ADRS [31:28] */
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_BASE_ADRS_MASK        0xf0000000
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_BASE_ADRS_SHIFT       28

/* PCI_BRIDGE :: PCI_SLV_MEM_WIN_BASE :: reserved0 [27:02] */
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_reserved0_MASK        0x0ffffffc
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_reserved0_SHIFT       2

/* PCI_BRIDGE :: PCI_SLV_MEM_WIN_BASE :: ENDIAN_MODE [01:00] */
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_ENDIAN_MODE_MASK      0x00000003
#define BCHP_PCI_BRIDGE_PCI_SLV_MEM_WIN_BASE_ENDIAN_MODE_SHIFT     0

/***************************************************************************
 *CPU_TO_SATA_MEM_WIN_BASE - CPU to SATA PCI Memory Window Base Address
 ***************************************************************************/
/* PCI_BRIDGE :: CPU_TO_SATA_MEM_WIN_BASE :: BASE_ADRS [31:16] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_BASE_ADRS_MASK    0xffff0000
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_BASE_ADRS_SHIFT   16

/* PCI_BRIDGE :: CPU_TO_SATA_MEM_WIN_BASE :: reserved0 [15:02] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_reserved0_MASK    0x0000fffc
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_reserved0_SHIFT   2

/* PCI_BRIDGE :: CPU_TO_SATA_MEM_WIN_BASE :: ENDIAN_MODE [01:00] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_ENDIAN_MODE_MASK  0x00000003
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_MEM_WIN_BASE_ENDIAN_MODE_SHIFT 0

/***************************************************************************
 *CPU_TO_SATA_IO_WIN_BASE - CPU to SATA PCI IO Window Base Address
 ***************************************************************************/
/* PCI_BRIDGE :: CPU_TO_SATA_IO_WIN_BASE :: BASE_ADRS [31:16] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_BASE_ADRS_MASK     0xffff0000
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_BASE_ADRS_SHIFT    16

/* PCI_BRIDGE :: CPU_TO_SATA_IO_WIN_BASE :: reserved0 [15:02] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_reserved0_MASK     0x0000fffc
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_reserved0_SHIFT    2

/* PCI_BRIDGE :: CPU_TO_SATA_IO_WIN_BASE :: ENDIAN_MODE [01:00] */
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_ENDIAN_MODE_MASK   0x00000003
#define BCHP_PCI_BRIDGE_CPU_TO_SATA_IO_WIN_BASE_ENDIAN_MODE_SHIFT  0

/***************************************************************************
 *MSLV_RETRY_ADDR - PCI Memory Slave Retry Address
 ***************************************************************************/
/* PCI_BRIDGE :: MSLV_RETRY_ADDR :: ADDR [31:00] */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_ADDR_ADDR_MASK                  0xffffffff
#define BCHP_PCI_BRIDGE_MSLV_RETRY_ADDR_ADDR_SHIFT                 0

/***************************************************************************
 *MSLV_RETRY_STATUS - PCI Memory Slave Retry Status
 ***************************************************************************/
/* PCI_BRIDGE :: MSLV_RETRY_STATUS :: reserved0 [31:08] */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_reserved0_MASK           0xffffff00
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_reserved0_SHIFT          8

/* PCI_BRIDGE :: MSLV_RETRY_STATUS :: BYTE_EN [07:04] */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_BYTE_EN_MASK             0x000000f0
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_BYTE_EN_SHIFT            4

/* PCI_BRIDGE :: MSLV_RETRY_STATUS :: CMD [03:00] */
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_CMD_MASK                 0x0000000f
#define BCHP_PCI_BRIDGE_MSLV_RETRY_STATUS_CMD_SHIFT                0

/***************************************************************************
 *REVISION - PCI Bridge Revision Register
 ***************************************************************************/
/* PCI_BRIDGE :: REVISION :: reserved0 [31:16] */
#define BCHP_PCI_BRIDGE_REVISION_reserved0_MASK                    0xffff0000
#define BCHP_PCI_BRIDGE_REVISION_reserved0_SHIFT                   16

/* PCI_BRIDGE :: REVISION :: MAJOR [15:08] */
#define BCHP_PCI_BRIDGE_REVISION_MAJOR_MASK                        0x0000ff00
#define BCHP_PCI_BRIDGE_REVISION_MAJOR_SHIFT                       8

/* PCI_BRIDGE :: REVISION :: MINOR [07:00] */
#define BCHP_PCI_BRIDGE_REVISION_MINOR_MASK                        0x000000ff
#define BCHP_PCI_BRIDGE_REVISION_MINOR_SHIFT                       0

/***************************************************************************
 *SCRATCH - PCI Bridge Scratch register
 ***************************************************************************/
/* PCI_BRIDGE :: SCRATCH :: DATA [31:00] */
#define BCHP_PCI_BRIDGE_SCRATCH_DATA_MASK                          0xffffffff
#define BCHP_PCI_BRIDGE_SCRATCH_DATA_SHIFT                         0

#endif /* #ifndef BCHP_PCI_BRIDGE_H__ */

/* End of File */
