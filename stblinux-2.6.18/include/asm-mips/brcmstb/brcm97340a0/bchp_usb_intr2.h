/***************************************************************************
 *     Copyright (c) 1999-2009, Broadcom Corporation
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
 * Date:           Generated on         Fri Mar 20 13:08:14 2009
 *                 MD5 Checksum         4f0509cfa0b8fc4589050694b4a3e234
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/7340/rdb/a0/bchp_usb_intr2.h $
 * 
 * Hydra_Software_Devel/1   3/22/09 9:20p yuxiaz
 * PR53430: Initial version of header files.
 *
 ***************************************************************************/

#ifndef BCHP_USB_INTR2_H__
#define BCHP_USB_INTR2_H__

/***************************************************************************
 *USB_INTR2 - USB Level 2 Interrupt Registers
 ***************************************************************************/
#define BCHP_USB_INTR2_CPU_STATUS                0x00480000 /* CPU interrupt Status Register */
#define BCHP_USB_INTR2_CPU_SET                   0x00480004 /* CPU interrupt Set Register */
#define BCHP_USB_INTR2_CPU_CLEAR                 0x00480008 /* CPU interrupt Clear Register */
#define BCHP_USB_INTR2_CPU_MASK_STATUS           0x0048000c /* CPU interrupt Mask Status Register */
#define BCHP_USB_INTR2_CPU_MASK_SET              0x00480010 /* CPU interrupt Mask Set Register */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR            0x00480014 /* CPU interrupt Mask Clear Register */
#define BCHP_USB_INTR2_PCI_STATUS                0x00480018 /* PCI interrupt Status Register */
#define BCHP_USB_INTR2_PCI_SET                   0x0048001c /* PCI interrupt Set Register */
#define BCHP_USB_INTR2_PCI_CLEAR                 0x00480020 /* PCI interrupt Clear Register */
#define BCHP_USB_INTR2_PCI_MASK_STATUS           0x00480024 /* PCI interrupt Mask Status Register */
#define BCHP_USB_INTR2_PCI_MASK_SET              0x00480028 /* PCI interrupt Mask Set Register */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR            0x0048002c /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - CPU interrupt Status Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_STATUS :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_STATUS_reserved0_MASK                   0xfffffc00
#define BCHP_USB_INTR2_CPU_STATUS_reserved0_SHIFT                  10

/* USB_INTR2 :: CPU_STATUS :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_09_INTR_MASK                 0x00000200
#define BCHP_USB_INTR2_CPU_STATUS_USB_09_INTR_SHIFT                9

/* USB_INTR2 :: CPU_STATUS :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_08_INTR_MASK                 0x00000100
#define BCHP_USB_INTR2_CPU_STATUS_USB_08_INTR_SHIFT                8

/* USB_INTR2 :: CPU_STATUS :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_07_INTR_MASK                 0x00000080
#define BCHP_USB_INTR2_CPU_STATUS_USB_07_INTR_SHIFT                7

/* USB_INTR2 :: CPU_STATUS :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_06_INTR_MASK                 0x00000040
#define BCHP_USB_INTR2_CPU_STATUS_USB_06_INTR_SHIFT                6

/* USB_INTR2 :: CPU_STATUS :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_05_INTR_MASK                 0x00000020
#define BCHP_USB_INTR2_CPU_STATUS_USB_05_INTR_SHIFT                5

/* USB_INTR2 :: CPU_STATUS :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_04_INTR_MASK                 0x00000010
#define BCHP_USB_INTR2_CPU_STATUS_USB_04_INTR_SHIFT                4

/* USB_INTR2 :: CPU_STATUS :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_03_INTR_MASK                 0x00000008
#define BCHP_USB_INTR2_CPU_STATUS_USB_03_INTR_SHIFT                3

/* USB_INTR2 :: CPU_STATUS :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_02_INTR_MASK                 0x00000004
#define BCHP_USB_INTR2_CPU_STATUS_USB_02_INTR_SHIFT                2

/* USB_INTR2 :: CPU_STATUS :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_01_INTR_MASK                 0x00000002
#define BCHP_USB_INTR2_CPU_STATUS_USB_01_INTR_SHIFT                1

/* USB_INTR2 :: CPU_STATUS :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_STATUS_USB_00_INTR_MASK                 0x00000001
#define BCHP_USB_INTR2_CPU_STATUS_USB_00_INTR_SHIFT                0

/***************************************************************************
 *CPU_SET - CPU interrupt Set Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_SET :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_SET_reserved0_MASK                      0xfffffc00
#define BCHP_USB_INTR2_CPU_SET_reserved0_SHIFT                     10

/* USB_INTR2 :: CPU_SET :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_SET_USB_09_INTR_MASK                    0x00000200
#define BCHP_USB_INTR2_CPU_SET_USB_09_INTR_SHIFT                   9

/* USB_INTR2 :: CPU_SET :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_SET_USB_08_INTR_MASK                    0x00000100
#define BCHP_USB_INTR2_CPU_SET_USB_08_INTR_SHIFT                   8

/* USB_INTR2 :: CPU_SET :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_SET_USB_07_INTR_MASK                    0x00000080
#define BCHP_USB_INTR2_CPU_SET_USB_07_INTR_SHIFT                   7

/* USB_INTR2 :: CPU_SET :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_SET_USB_06_INTR_MASK                    0x00000040
#define BCHP_USB_INTR2_CPU_SET_USB_06_INTR_SHIFT                   6

/* USB_INTR2 :: CPU_SET :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_SET_USB_05_INTR_MASK                    0x00000020
#define BCHP_USB_INTR2_CPU_SET_USB_05_INTR_SHIFT                   5

/* USB_INTR2 :: CPU_SET :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_SET_USB_04_INTR_MASK                    0x00000010
#define BCHP_USB_INTR2_CPU_SET_USB_04_INTR_SHIFT                   4

/* USB_INTR2 :: CPU_SET :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_SET_USB_03_INTR_MASK                    0x00000008
#define BCHP_USB_INTR2_CPU_SET_USB_03_INTR_SHIFT                   3

/* USB_INTR2 :: CPU_SET :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_SET_USB_02_INTR_MASK                    0x00000004
#define BCHP_USB_INTR2_CPU_SET_USB_02_INTR_SHIFT                   2

/* USB_INTR2 :: CPU_SET :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_SET_USB_01_INTR_MASK                    0x00000002
#define BCHP_USB_INTR2_CPU_SET_USB_01_INTR_SHIFT                   1

/* USB_INTR2 :: CPU_SET :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_SET_USB_00_INTR_MASK                    0x00000001
#define BCHP_USB_INTR2_CPU_SET_USB_00_INTR_SHIFT                   0

/***************************************************************************
 *CPU_CLEAR - CPU interrupt Clear Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_CLEAR :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_CLEAR_reserved0_MASK                    0xfffffc00
#define BCHP_USB_INTR2_CPU_CLEAR_reserved0_SHIFT                   10

/* USB_INTR2 :: CPU_CLEAR :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_09_INTR_MASK                  0x00000200
#define BCHP_USB_INTR2_CPU_CLEAR_USB_09_INTR_SHIFT                 9

/* USB_INTR2 :: CPU_CLEAR :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_08_INTR_MASK                  0x00000100
#define BCHP_USB_INTR2_CPU_CLEAR_USB_08_INTR_SHIFT                 8

/* USB_INTR2 :: CPU_CLEAR :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_07_INTR_MASK                  0x00000080
#define BCHP_USB_INTR2_CPU_CLEAR_USB_07_INTR_SHIFT                 7

/* USB_INTR2 :: CPU_CLEAR :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_06_INTR_MASK                  0x00000040
#define BCHP_USB_INTR2_CPU_CLEAR_USB_06_INTR_SHIFT                 6

/* USB_INTR2 :: CPU_CLEAR :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_05_INTR_MASK                  0x00000020
#define BCHP_USB_INTR2_CPU_CLEAR_USB_05_INTR_SHIFT                 5

/* USB_INTR2 :: CPU_CLEAR :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_04_INTR_MASK                  0x00000010
#define BCHP_USB_INTR2_CPU_CLEAR_USB_04_INTR_SHIFT                 4

/* USB_INTR2 :: CPU_CLEAR :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_03_INTR_MASK                  0x00000008
#define BCHP_USB_INTR2_CPU_CLEAR_USB_03_INTR_SHIFT                 3

/* USB_INTR2 :: CPU_CLEAR :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_02_INTR_MASK                  0x00000004
#define BCHP_USB_INTR2_CPU_CLEAR_USB_02_INTR_SHIFT                 2

/* USB_INTR2 :: CPU_CLEAR :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_01_INTR_MASK                  0x00000002
#define BCHP_USB_INTR2_CPU_CLEAR_USB_01_INTR_SHIFT                 1

/* USB_INTR2 :: CPU_CLEAR :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_CLEAR_USB_00_INTR_MASK                  0x00000001
#define BCHP_USB_INTR2_CPU_CLEAR_USB_00_INTR_SHIFT                 0

/***************************************************************************
 *CPU_MASK_STATUS - CPU interrupt Mask Status Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_MASK_STATUS :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_reserved0_MASK              0xfffffc00
#define BCHP_USB_INTR2_CPU_MASK_STATUS_reserved0_SHIFT             10

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_09_INTR_MASK            0x00000200
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_09_INTR_SHIFT           9

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_08_INTR_MASK            0x00000100
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_08_INTR_SHIFT           8

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_07_INTR_MASK            0x00000080
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_07_INTR_SHIFT           7

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_06_INTR_MASK            0x00000040
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_06_INTR_SHIFT           6

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_05_INTR_MASK            0x00000020
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_05_INTR_SHIFT           5

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_04_INTR_MASK            0x00000010
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_04_INTR_SHIFT           4

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_03_INTR_MASK            0x00000008
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_03_INTR_SHIFT           3

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_02_INTR_MASK            0x00000004
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_02_INTR_SHIFT           2

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_01_INTR_MASK            0x00000002
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_01_INTR_SHIFT           1

/* USB_INTR2 :: CPU_MASK_STATUS :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_00_INTR_MASK            0x00000001
#define BCHP_USB_INTR2_CPU_MASK_STATUS_USB_00_INTR_SHIFT           0

/***************************************************************************
 *CPU_MASK_SET - CPU interrupt Mask Set Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_MASK_SET :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_MASK_SET_reserved0_MASK                 0xfffffc00
#define BCHP_USB_INTR2_CPU_MASK_SET_reserved0_SHIFT                10

/* USB_INTR2 :: CPU_MASK_SET :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_09_INTR_MASK               0x00000200
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_09_INTR_SHIFT              9

/* USB_INTR2 :: CPU_MASK_SET :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_08_INTR_MASK               0x00000100
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_08_INTR_SHIFT              8

/* USB_INTR2 :: CPU_MASK_SET :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_07_INTR_MASK               0x00000080
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_07_INTR_SHIFT              7

/* USB_INTR2 :: CPU_MASK_SET :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_06_INTR_MASK               0x00000040
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_06_INTR_SHIFT              6

/* USB_INTR2 :: CPU_MASK_SET :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_05_INTR_MASK               0x00000020
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_05_INTR_SHIFT              5

/* USB_INTR2 :: CPU_MASK_SET :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_04_INTR_MASK               0x00000010
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_04_INTR_SHIFT              4

/* USB_INTR2 :: CPU_MASK_SET :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_03_INTR_MASK               0x00000008
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_03_INTR_SHIFT              3

/* USB_INTR2 :: CPU_MASK_SET :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_02_INTR_MASK               0x00000004
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_02_INTR_SHIFT              2

/* USB_INTR2 :: CPU_MASK_SET :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_01_INTR_MASK               0x00000002
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_01_INTR_SHIFT              1

/* USB_INTR2 :: CPU_MASK_SET :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_00_INTR_MASK               0x00000001
#define BCHP_USB_INTR2_CPU_MASK_SET_USB_00_INTR_SHIFT              0

/***************************************************************************
 *CPU_MASK_CLEAR - CPU interrupt Mask Clear Register
 ***************************************************************************/
/* USB_INTR2 :: CPU_MASK_CLEAR :: reserved0 [31:10] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_reserved0_MASK               0xfffffc00
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_reserved0_SHIFT              10

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_09_INTR_MASK             0x00000200
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_09_INTR_SHIFT            9

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_08_INTR_MASK             0x00000100
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_08_INTR_SHIFT            8

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_07_INTR_MASK             0x00000080
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_07_INTR_SHIFT            7

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_06_INTR_MASK             0x00000040
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_06_INTR_SHIFT            6

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_05_INTR_MASK             0x00000020
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_05_INTR_SHIFT            5

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_04_INTR_MASK             0x00000010
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_04_INTR_SHIFT            4

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_03_INTR_MASK             0x00000008
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_03_INTR_SHIFT            3

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_02_INTR_MASK             0x00000004
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_02_INTR_SHIFT            2

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_01_INTR_MASK             0x00000002
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_01_INTR_SHIFT            1

/* USB_INTR2 :: CPU_MASK_CLEAR :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_00_INTR_MASK             0x00000001
#define BCHP_USB_INTR2_CPU_MASK_CLEAR_USB_00_INTR_SHIFT            0

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_STATUS :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_STATUS_reserved0_MASK                   0xfffffc00
#define BCHP_USB_INTR2_PCI_STATUS_reserved0_SHIFT                  10

/* USB_INTR2 :: PCI_STATUS :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_09_INTR_MASK                 0x00000200
#define BCHP_USB_INTR2_PCI_STATUS_USB_09_INTR_SHIFT                9

/* USB_INTR2 :: PCI_STATUS :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_08_INTR_MASK                 0x00000100
#define BCHP_USB_INTR2_PCI_STATUS_USB_08_INTR_SHIFT                8

/* USB_INTR2 :: PCI_STATUS :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_07_INTR_MASK                 0x00000080
#define BCHP_USB_INTR2_PCI_STATUS_USB_07_INTR_SHIFT                7

/* USB_INTR2 :: PCI_STATUS :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_06_INTR_MASK                 0x00000040
#define BCHP_USB_INTR2_PCI_STATUS_USB_06_INTR_SHIFT                6

/* USB_INTR2 :: PCI_STATUS :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_05_INTR_MASK                 0x00000020
#define BCHP_USB_INTR2_PCI_STATUS_USB_05_INTR_SHIFT                5

/* USB_INTR2 :: PCI_STATUS :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_04_INTR_MASK                 0x00000010
#define BCHP_USB_INTR2_PCI_STATUS_USB_04_INTR_SHIFT                4

/* USB_INTR2 :: PCI_STATUS :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_03_INTR_MASK                 0x00000008
#define BCHP_USB_INTR2_PCI_STATUS_USB_03_INTR_SHIFT                3

/* USB_INTR2 :: PCI_STATUS :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_02_INTR_MASK                 0x00000004
#define BCHP_USB_INTR2_PCI_STATUS_USB_02_INTR_SHIFT                2

/* USB_INTR2 :: PCI_STATUS :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_01_INTR_MASK                 0x00000002
#define BCHP_USB_INTR2_PCI_STATUS_USB_01_INTR_SHIFT                1

/* USB_INTR2 :: PCI_STATUS :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_STATUS_USB_00_INTR_MASK                 0x00000001
#define BCHP_USB_INTR2_PCI_STATUS_USB_00_INTR_SHIFT                0

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_SET :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_SET_reserved0_MASK                      0xfffffc00
#define BCHP_USB_INTR2_PCI_SET_reserved0_SHIFT                     10

/* USB_INTR2 :: PCI_SET :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_SET_USB_09_INTR_MASK                    0x00000200
#define BCHP_USB_INTR2_PCI_SET_USB_09_INTR_SHIFT                   9

/* USB_INTR2 :: PCI_SET :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_SET_USB_08_INTR_MASK                    0x00000100
#define BCHP_USB_INTR2_PCI_SET_USB_08_INTR_SHIFT                   8

/* USB_INTR2 :: PCI_SET :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_SET_USB_07_INTR_MASK                    0x00000080
#define BCHP_USB_INTR2_PCI_SET_USB_07_INTR_SHIFT                   7

/* USB_INTR2 :: PCI_SET :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_SET_USB_06_INTR_MASK                    0x00000040
#define BCHP_USB_INTR2_PCI_SET_USB_06_INTR_SHIFT                   6

/* USB_INTR2 :: PCI_SET :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_SET_USB_05_INTR_MASK                    0x00000020
#define BCHP_USB_INTR2_PCI_SET_USB_05_INTR_SHIFT                   5

/* USB_INTR2 :: PCI_SET :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_SET_USB_04_INTR_MASK                    0x00000010
#define BCHP_USB_INTR2_PCI_SET_USB_04_INTR_SHIFT                   4

/* USB_INTR2 :: PCI_SET :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_SET_USB_03_INTR_MASK                    0x00000008
#define BCHP_USB_INTR2_PCI_SET_USB_03_INTR_SHIFT                   3

/* USB_INTR2 :: PCI_SET :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_SET_USB_02_INTR_MASK                    0x00000004
#define BCHP_USB_INTR2_PCI_SET_USB_02_INTR_SHIFT                   2

/* USB_INTR2 :: PCI_SET :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_SET_USB_01_INTR_MASK                    0x00000002
#define BCHP_USB_INTR2_PCI_SET_USB_01_INTR_SHIFT                   1

/* USB_INTR2 :: PCI_SET :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_SET_USB_00_INTR_MASK                    0x00000001
#define BCHP_USB_INTR2_PCI_SET_USB_00_INTR_SHIFT                   0

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_CLEAR :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_CLEAR_reserved0_MASK                    0xfffffc00
#define BCHP_USB_INTR2_PCI_CLEAR_reserved0_SHIFT                   10

/* USB_INTR2 :: PCI_CLEAR :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_09_INTR_MASK                  0x00000200
#define BCHP_USB_INTR2_PCI_CLEAR_USB_09_INTR_SHIFT                 9

/* USB_INTR2 :: PCI_CLEAR :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_08_INTR_MASK                  0x00000100
#define BCHP_USB_INTR2_PCI_CLEAR_USB_08_INTR_SHIFT                 8

/* USB_INTR2 :: PCI_CLEAR :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_07_INTR_MASK                  0x00000080
#define BCHP_USB_INTR2_PCI_CLEAR_USB_07_INTR_SHIFT                 7

/* USB_INTR2 :: PCI_CLEAR :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_06_INTR_MASK                  0x00000040
#define BCHP_USB_INTR2_PCI_CLEAR_USB_06_INTR_SHIFT                 6

/* USB_INTR2 :: PCI_CLEAR :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_05_INTR_MASK                  0x00000020
#define BCHP_USB_INTR2_PCI_CLEAR_USB_05_INTR_SHIFT                 5

/* USB_INTR2 :: PCI_CLEAR :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_04_INTR_MASK                  0x00000010
#define BCHP_USB_INTR2_PCI_CLEAR_USB_04_INTR_SHIFT                 4

/* USB_INTR2 :: PCI_CLEAR :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_03_INTR_MASK                  0x00000008
#define BCHP_USB_INTR2_PCI_CLEAR_USB_03_INTR_SHIFT                 3

/* USB_INTR2 :: PCI_CLEAR :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_02_INTR_MASK                  0x00000004
#define BCHP_USB_INTR2_PCI_CLEAR_USB_02_INTR_SHIFT                 2

/* USB_INTR2 :: PCI_CLEAR :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_01_INTR_MASK                  0x00000002
#define BCHP_USB_INTR2_PCI_CLEAR_USB_01_INTR_SHIFT                 1

/* USB_INTR2 :: PCI_CLEAR :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_CLEAR_USB_00_INTR_MASK                  0x00000001
#define BCHP_USB_INTR2_PCI_CLEAR_USB_00_INTR_SHIFT                 0

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_MASK_STATUS :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_reserved0_MASK              0xfffffc00
#define BCHP_USB_INTR2_PCI_MASK_STATUS_reserved0_SHIFT             10

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_09_INTR_MASK            0x00000200
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_09_INTR_SHIFT           9

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_08_INTR_MASK            0x00000100
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_08_INTR_SHIFT           8

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_07_INTR_MASK            0x00000080
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_07_INTR_SHIFT           7

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_06_INTR_MASK            0x00000040
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_06_INTR_SHIFT           6

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_05_INTR_MASK            0x00000020
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_05_INTR_SHIFT           5

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_04_INTR_MASK            0x00000010
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_04_INTR_SHIFT           4

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_03_INTR_MASK            0x00000008
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_03_INTR_SHIFT           3

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_02_INTR_MASK            0x00000004
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_02_INTR_SHIFT           2

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_01_INTR_MASK            0x00000002
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_01_INTR_SHIFT           1

/* USB_INTR2 :: PCI_MASK_STATUS :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_00_INTR_MASK            0x00000001
#define BCHP_USB_INTR2_PCI_MASK_STATUS_USB_00_INTR_SHIFT           0

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_MASK_SET :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_MASK_SET_reserved0_MASK                 0xfffffc00
#define BCHP_USB_INTR2_PCI_MASK_SET_reserved0_SHIFT                10

/* USB_INTR2 :: PCI_MASK_SET :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_09_INTR_MASK               0x00000200
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_09_INTR_SHIFT              9

/* USB_INTR2 :: PCI_MASK_SET :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_08_INTR_MASK               0x00000100
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_08_INTR_SHIFT              8

/* USB_INTR2 :: PCI_MASK_SET :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_07_INTR_MASK               0x00000080
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_07_INTR_SHIFT              7

/* USB_INTR2 :: PCI_MASK_SET :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_06_INTR_MASK               0x00000040
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_06_INTR_SHIFT              6

/* USB_INTR2 :: PCI_MASK_SET :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_05_INTR_MASK               0x00000020
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_05_INTR_SHIFT              5

/* USB_INTR2 :: PCI_MASK_SET :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_04_INTR_MASK               0x00000010
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_04_INTR_SHIFT              4

/* USB_INTR2 :: PCI_MASK_SET :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_03_INTR_MASK               0x00000008
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_03_INTR_SHIFT              3

/* USB_INTR2 :: PCI_MASK_SET :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_02_INTR_MASK               0x00000004
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_02_INTR_SHIFT              2

/* USB_INTR2 :: PCI_MASK_SET :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_01_INTR_MASK               0x00000002
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_01_INTR_SHIFT              1

/* USB_INTR2 :: PCI_MASK_SET :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_00_INTR_MASK               0x00000001
#define BCHP_USB_INTR2_PCI_MASK_SET_USB_00_INTR_SHIFT              0

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* USB_INTR2 :: PCI_MASK_CLEAR :: reserved0 [31:10] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_reserved0_MASK               0xfffffc00
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_reserved0_SHIFT              10

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_09_INTR [09:09] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_09_INTR_MASK             0x00000200
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_09_INTR_SHIFT            9

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_08_INTR [08:08] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_08_INTR_MASK             0x00000100
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_08_INTR_SHIFT            8

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_07_INTR [07:07] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_07_INTR_MASK             0x00000080
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_07_INTR_SHIFT            7

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_06_INTR [06:06] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_06_INTR_MASK             0x00000040
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_06_INTR_SHIFT            6

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_05_INTR [05:05] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_05_INTR_MASK             0x00000020
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_05_INTR_SHIFT            5

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_04_INTR [04:04] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_04_INTR_MASK             0x00000010
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_04_INTR_SHIFT            4

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_03_INTR [03:03] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_03_INTR_MASK             0x00000008
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_03_INTR_SHIFT            3

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_02_INTR [02:02] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_02_INTR_MASK             0x00000004
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_02_INTR_SHIFT            2

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_01_INTR [01:01] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_01_INTR_MASK             0x00000002
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_01_INTR_SHIFT            1

/* USB_INTR2 :: PCI_MASK_CLEAR :: USB_00_INTR [00:00] */
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_00_INTR_MASK             0x00000001
#define BCHP_USB_INTR2_PCI_MASK_CLEAR_USB_00_INTR_SHIFT            0

#endif /* #ifndef BCHP_USB_INTR2_H__ */

/* End of File */