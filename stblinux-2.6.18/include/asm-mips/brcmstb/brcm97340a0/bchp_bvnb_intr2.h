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
 * Date:           Generated on         Fri Mar 20 12:58:52 2009
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
 * $brcm_Log: /magnum/basemodules/chp/7340/rdb/a0/bchp_bvnb_intr2.h $
 * 
 * Hydra_Software_Devel/1   3/22/09 7:55p yuxiaz
 * PR53430: Initial version of header files.
 *
 ***************************************************************************/

#ifndef BCHP_BVNB_INTR2_H__
#define BCHP_BVNB_INTR2_H__

/***************************************************************************
 *BVNB_INTR2 - BVN Back Interrupt Controller (BVN Error INTRs to CPU) Registers
 ***************************************************************************/
#define BCHP_BVNB_INTR2_CPU_STATUS               0x00146000 /* R5f interrupt Status Register */
#define BCHP_BVNB_INTR2_CPU_SET                  0x00146004 /* R5f interrupt Set Register */
#define BCHP_BVNB_INTR2_CPU_CLEAR                0x00146008 /* R5f interrupt Clear Register */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS          0x0014600c /* R5f interrupt Mask Status Register */
#define BCHP_BVNB_INTR2_CPU_MASK_SET             0x00146010 /* R5f interrupt Mask Set Register */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR           0x00146014 /* R5f interrupt Mask Clear Register */
#define BCHP_BVNB_INTR2_PCI_STATUS               0x00146018 /* PCI interrupt Status Register */
#define BCHP_BVNB_INTR2_PCI_SET                  0x0014601c /* PCI interrupt Set Register */
#define BCHP_BVNB_INTR2_PCI_CLEAR                0x00146020 /* PCI interrupt Clear Register */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS          0x00146024 /* PCI interrupt Mask Status Register */
#define BCHP_BVNB_INTR2_PCI_MASK_SET             0x00146028 /* PCI interrupt Mask Set Register */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR           0x0014602c /* PCI interrupt Mask Clear Register */

/***************************************************************************
 *CPU_STATUS - R5f interrupt Status Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_STATUS :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved0_MASK                  0xffff8000
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved0_SHIFT                 15

/* BVNB_INTR2 :: CPU_STATUS :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_STATUS_LAB_MIN_MAX_DONE_INTR_MASK      0x00004000
#define BCHP_BVNB_INTR2_CPU_STATUS_LAB_MIN_MAX_DONE_INTR_SHIFT     14

/* BVNB_INTR2 :: CPU_STATUS :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_STATUS_LAB_HISTO_DONE_INTR_MASK        0x00002000
#define BCHP_BVNB_INTR2_CPU_STATUS_LAB_HISTO_DONE_INTR_SHIFT       13

/* BVNB_INTR2 :: CPU_STATUS :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_STATUS_GFD1_INTR_MASK                  0x00001000
#define BCHP_BVNB_INTR2_CPU_STATUS_GFD1_INTR_SHIFT                 12

/* BVNB_INTR2 :: CPU_STATUS :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_STATUS_GFD0_INTR_MASK                  0x00000800
#define BCHP_BVNB_INTR2_CPU_STATUS_GFD0_INTR_SHIFT                 11

/* BVNB_INTR2 :: CPU_STATUS :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved1_MASK                  0x00000700
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved1_SHIFT                 8

/* BVNB_INTR2 :: CPU_STATUS :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CAP1_INTR_MASK                  0x00000080
#define BCHP_BVNB_INTR2_CPU_STATUS_CAP1_INTR_SHIFT                 7

/* BVNB_INTR2 :: CPU_STATUS :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CAP0_INTR_MASK                  0x00000040
#define BCHP_BVNB_INTR2_CPU_STATUS_CAP0_INTR_SHIFT                 6

/* BVNB_INTR2 :: CPU_STATUS :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved2_MASK                  0x00000020
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved2_SHIFT                 5

/* BVNB_INTR2 :: CPU_STATUS :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP1_V0_INTR_MASK               0x00000010
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP1_V0_INTR_SHIFT              4

/* BVNB_INTR2 :: CPU_STATUS :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP1_G0_INTR_MASK               0x00000008
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP1_G0_INTR_SHIFT              3

/* BVNB_INTR2 :: CPU_STATUS :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved3_MASK                  0x00000004
#define BCHP_BVNB_INTR2_CPU_STATUS_reserved3_SHIFT                 2

/* BVNB_INTR2 :: CPU_STATUS :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP0_V0_INTR_MASK               0x00000002
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP0_V0_INTR_SHIFT              1

/* BVNB_INTR2 :: CPU_STATUS :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP0_G0_INTR_MASK               0x00000001
#define BCHP_BVNB_INTR2_CPU_STATUS_CMP0_G0_INTR_SHIFT              0

/***************************************************************************
 *CPU_SET - R5f interrupt Set Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_SET :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_SET_reserved0_MASK                     0xffff8000
#define BCHP_BVNB_INTR2_CPU_SET_reserved0_SHIFT                    15

/* BVNB_INTR2 :: CPU_SET :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_SET_LAB_MIN_MAX_DONE_INTR_MASK         0x00004000
#define BCHP_BVNB_INTR2_CPU_SET_LAB_MIN_MAX_DONE_INTR_SHIFT        14

/* BVNB_INTR2 :: CPU_SET :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_SET_LAB_HISTO_DONE_INTR_MASK           0x00002000
#define BCHP_BVNB_INTR2_CPU_SET_LAB_HISTO_DONE_INTR_SHIFT          13

/* BVNB_INTR2 :: CPU_SET :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_SET_GFD1_INTR_MASK                     0x00001000
#define BCHP_BVNB_INTR2_CPU_SET_GFD1_INTR_SHIFT                    12

/* BVNB_INTR2 :: CPU_SET :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_SET_GFD0_INTR_MASK                     0x00000800
#define BCHP_BVNB_INTR2_CPU_SET_GFD0_INTR_SHIFT                    11

/* BVNB_INTR2 :: CPU_SET :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_SET_reserved1_MASK                     0x00000700
#define BCHP_BVNB_INTR2_CPU_SET_reserved1_SHIFT                    8

/* BVNB_INTR2 :: CPU_SET :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_SET_CAP1_INTR_MASK                     0x00000080
#define BCHP_BVNB_INTR2_CPU_SET_CAP1_INTR_SHIFT                    7

/* BVNB_INTR2 :: CPU_SET :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_SET_CAP0_INTR_MASK                     0x00000040
#define BCHP_BVNB_INTR2_CPU_SET_CAP0_INTR_SHIFT                    6

/* BVNB_INTR2 :: CPU_SET :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_SET_reserved2_MASK                     0x00000020
#define BCHP_BVNB_INTR2_CPU_SET_reserved2_SHIFT                    5

/* BVNB_INTR2 :: CPU_SET :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_SET_CMP1_V0_INTR_MASK                  0x00000010
#define BCHP_BVNB_INTR2_CPU_SET_CMP1_V0_INTR_SHIFT                 4

/* BVNB_INTR2 :: CPU_SET :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_SET_CMP1_G0_INTR_MASK                  0x00000008
#define BCHP_BVNB_INTR2_CPU_SET_CMP1_G0_INTR_SHIFT                 3

/* BVNB_INTR2 :: CPU_SET :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_SET_reserved3_MASK                     0x00000004
#define BCHP_BVNB_INTR2_CPU_SET_reserved3_SHIFT                    2

/* BVNB_INTR2 :: CPU_SET :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_SET_CMP0_V0_INTR_MASK                  0x00000002
#define BCHP_BVNB_INTR2_CPU_SET_CMP0_V0_INTR_SHIFT                 1

/* BVNB_INTR2 :: CPU_SET :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_SET_CMP0_G0_INTR_MASK                  0x00000001
#define BCHP_BVNB_INTR2_CPU_SET_CMP0_G0_INTR_SHIFT                 0

/***************************************************************************
 *CPU_CLEAR - R5f interrupt Clear Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_CLEAR :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved0_MASK                   0xffff8000
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved0_SHIFT                  15

/* BVNB_INTR2 :: CPU_CLEAR :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_LAB_MIN_MAX_DONE_INTR_MASK       0x00004000
#define BCHP_BVNB_INTR2_CPU_CLEAR_LAB_MIN_MAX_DONE_INTR_SHIFT      14

/* BVNB_INTR2 :: CPU_CLEAR :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_LAB_HISTO_DONE_INTR_MASK         0x00002000
#define BCHP_BVNB_INTR2_CPU_CLEAR_LAB_HISTO_DONE_INTR_SHIFT        13

/* BVNB_INTR2 :: CPU_CLEAR :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_GFD1_INTR_MASK                   0x00001000
#define BCHP_BVNB_INTR2_CPU_CLEAR_GFD1_INTR_SHIFT                  12

/* BVNB_INTR2 :: CPU_CLEAR :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_GFD0_INTR_MASK                   0x00000800
#define BCHP_BVNB_INTR2_CPU_CLEAR_GFD0_INTR_SHIFT                  11

/* BVNB_INTR2 :: CPU_CLEAR :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved1_MASK                   0x00000700
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved1_SHIFT                  8

/* BVNB_INTR2 :: CPU_CLEAR :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CAP1_INTR_MASK                   0x00000080
#define BCHP_BVNB_INTR2_CPU_CLEAR_CAP1_INTR_SHIFT                  7

/* BVNB_INTR2 :: CPU_CLEAR :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CAP0_INTR_MASK                   0x00000040
#define BCHP_BVNB_INTR2_CPU_CLEAR_CAP0_INTR_SHIFT                  6

/* BVNB_INTR2 :: CPU_CLEAR :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved2_MASK                   0x00000020
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved2_SHIFT                  5

/* BVNB_INTR2 :: CPU_CLEAR :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP1_V0_INTR_MASK                0x00000010
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP1_V0_INTR_SHIFT               4

/* BVNB_INTR2 :: CPU_CLEAR :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP1_G0_INTR_MASK                0x00000008
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP1_G0_INTR_SHIFT               3

/* BVNB_INTR2 :: CPU_CLEAR :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved3_MASK                   0x00000004
#define BCHP_BVNB_INTR2_CPU_CLEAR_reserved3_SHIFT                  2

/* BVNB_INTR2 :: CPU_CLEAR :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP0_V0_INTR_MASK                0x00000002
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP0_V0_INTR_SHIFT               1

/* BVNB_INTR2 :: CPU_CLEAR :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP0_G0_INTR_MASK                0x00000001
#define BCHP_BVNB_INTR2_CPU_CLEAR_CMP0_G0_INTR_SHIFT               0

/***************************************************************************
 *CPU_MASK_STATUS - R5f interrupt Mask Status Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_MASK_STATUS :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved0_MASK             0xffff8000
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved0_SHIFT            15

/* BVNB_INTR2 :: CPU_MASK_STATUS :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_LAB_MIN_MAX_DONE_INTR_MASK 0x00004000
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_LAB_MIN_MAX_DONE_INTR_SHIFT 14

/* BVNB_INTR2 :: CPU_MASK_STATUS :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_LAB_HISTO_DONE_INTR_MASK   0x00002000
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_LAB_HISTO_DONE_INTR_SHIFT  13

/* BVNB_INTR2 :: CPU_MASK_STATUS :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_GFD1_INTR_MASK             0x00001000
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_GFD1_INTR_SHIFT            12

/* BVNB_INTR2 :: CPU_MASK_STATUS :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_GFD0_INTR_MASK             0x00000800
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_GFD0_INTR_SHIFT            11

/* BVNB_INTR2 :: CPU_MASK_STATUS :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved1_MASK             0x00000700
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved1_SHIFT            8

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CAP1_INTR_MASK             0x00000080
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CAP1_INTR_SHIFT            7

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CAP0_INTR_MASK             0x00000040
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CAP0_INTR_SHIFT            6

/* BVNB_INTR2 :: CPU_MASK_STATUS :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved2_MASK             0x00000020
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved2_SHIFT            5

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP1_V0_INTR_MASK          0x00000010
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP1_V0_INTR_SHIFT         4

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP1_G0_INTR_MASK          0x00000008
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP1_G0_INTR_SHIFT         3

/* BVNB_INTR2 :: CPU_MASK_STATUS :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved3_MASK             0x00000004
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_reserved3_SHIFT            2

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP0_V0_INTR_MASK          0x00000002
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP0_V0_INTR_SHIFT         1

/* BVNB_INTR2 :: CPU_MASK_STATUS :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP0_G0_INTR_MASK          0x00000001
#define BCHP_BVNB_INTR2_CPU_MASK_STATUS_CMP0_G0_INTR_SHIFT         0

/***************************************************************************
 *CPU_MASK_SET - R5f interrupt Mask Set Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_MASK_SET :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved0_MASK                0xffff8000
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved0_SHIFT               15

/* BVNB_INTR2 :: CPU_MASK_SET :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_LAB_MIN_MAX_DONE_INTR_MASK    0x00004000
#define BCHP_BVNB_INTR2_CPU_MASK_SET_LAB_MIN_MAX_DONE_INTR_SHIFT   14

/* BVNB_INTR2 :: CPU_MASK_SET :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_LAB_HISTO_DONE_INTR_MASK      0x00002000
#define BCHP_BVNB_INTR2_CPU_MASK_SET_LAB_HISTO_DONE_INTR_SHIFT     13

/* BVNB_INTR2 :: CPU_MASK_SET :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_GFD1_INTR_MASK                0x00001000
#define BCHP_BVNB_INTR2_CPU_MASK_SET_GFD1_INTR_SHIFT               12

/* BVNB_INTR2 :: CPU_MASK_SET :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_GFD0_INTR_MASK                0x00000800
#define BCHP_BVNB_INTR2_CPU_MASK_SET_GFD0_INTR_SHIFT               11

/* BVNB_INTR2 :: CPU_MASK_SET :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved1_MASK                0x00000700
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved1_SHIFT               8

/* BVNB_INTR2 :: CPU_MASK_SET :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CAP1_INTR_MASK                0x00000080
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CAP1_INTR_SHIFT               7

/* BVNB_INTR2 :: CPU_MASK_SET :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CAP0_INTR_MASK                0x00000040
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CAP0_INTR_SHIFT               6

/* BVNB_INTR2 :: CPU_MASK_SET :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved2_MASK                0x00000020
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved2_SHIFT               5

/* BVNB_INTR2 :: CPU_MASK_SET :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP1_V0_INTR_MASK             0x00000010
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP1_V0_INTR_SHIFT            4

/* BVNB_INTR2 :: CPU_MASK_SET :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP1_G0_INTR_MASK             0x00000008
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP1_G0_INTR_SHIFT            3

/* BVNB_INTR2 :: CPU_MASK_SET :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved3_MASK                0x00000004
#define BCHP_BVNB_INTR2_CPU_MASK_SET_reserved3_SHIFT               2

/* BVNB_INTR2 :: CPU_MASK_SET :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP0_V0_INTR_MASK             0x00000002
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP0_V0_INTR_SHIFT            1

/* BVNB_INTR2 :: CPU_MASK_SET :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP0_G0_INTR_MASK             0x00000001
#define BCHP_BVNB_INTR2_CPU_MASK_SET_CMP0_G0_INTR_SHIFT            0

/***************************************************************************
 *CPU_MASK_CLEAR - R5f interrupt Mask Clear Register
 ***************************************************************************/
/* BVNB_INTR2 :: CPU_MASK_CLEAR :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved0_MASK              0xffff8000
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved0_SHIFT             15

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_LAB_MIN_MAX_DONE_INTR_MASK  0x00004000
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_LAB_MIN_MAX_DONE_INTR_SHIFT 14

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_LAB_HISTO_DONE_INTR_MASK    0x00002000
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_LAB_HISTO_DONE_INTR_SHIFT   13

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_GFD1_INTR_MASK              0x00001000
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_GFD1_INTR_SHIFT             12

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_GFD0_INTR_MASK              0x00000800
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_GFD0_INTR_SHIFT             11

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved1_MASK              0x00000700
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved1_SHIFT             8

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CAP1_INTR_MASK              0x00000080
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CAP1_INTR_SHIFT             7

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CAP0_INTR_MASK              0x00000040
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CAP0_INTR_SHIFT             6

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved2_MASK              0x00000020
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved2_SHIFT             5

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP1_V0_INTR_MASK           0x00000010
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP1_V0_INTR_SHIFT          4

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP1_G0_INTR_MASK           0x00000008
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP1_G0_INTR_SHIFT          3

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved3_MASK              0x00000004
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_reserved3_SHIFT             2

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP0_V0_INTR_MASK           0x00000002
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP0_V0_INTR_SHIFT          1

/* BVNB_INTR2 :: CPU_MASK_CLEAR :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP0_G0_INTR_MASK           0x00000001
#define BCHP_BVNB_INTR2_CPU_MASK_CLEAR_CMP0_G0_INTR_SHIFT          0

/***************************************************************************
 *PCI_STATUS - PCI interrupt Status Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_STATUS :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved0_MASK                  0xffff8000
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved0_SHIFT                 15

/* BVNB_INTR2 :: PCI_STATUS :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_STATUS_LAB_MIN_MAX_DONE_INTR_MASK      0x00004000
#define BCHP_BVNB_INTR2_PCI_STATUS_LAB_MIN_MAX_DONE_INTR_SHIFT     14

/* BVNB_INTR2 :: PCI_STATUS :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_STATUS_LAB_HISTO_DONE_INTR_MASK        0x00002000
#define BCHP_BVNB_INTR2_PCI_STATUS_LAB_HISTO_DONE_INTR_SHIFT       13

/* BVNB_INTR2 :: PCI_STATUS :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_STATUS_GFD1_INTR_MASK                  0x00001000
#define BCHP_BVNB_INTR2_PCI_STATUS_GFD1_INTR_SHIFT                 12

/* BVNB_INTR2 :: PCI_STATUS :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_STATUS_GFD0_INTR_MASK                  0x00000800
#define BCHP_BVNB_INTR2_PCI_STATUS_GFD0_INTR_SHIFT                 11

/* BVNB_INTR2 :: PCI_STATUS :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved1_MASK                  0x00000700
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved1_SHIFT                 8

/* BVNB_INTR2 :: PCI_STATUS :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CAP1_INTR_MASK                  0x00000080
#define BCHP_BVNB_INTR2_PCI_STATUS_CAP1_INTR_SHIFT                 7

/* BVNB_INTR2 :: PCI_STATUS :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CAP0_INTR_MASK                  0x00000040
#define BCHP_BVNB_INTR2_PCI_STATUS_CAP0_INTR_SHIFT                 6

/* BVNB_INTR2 :: PCI_STATUS :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved2_MASK                  0x00000020
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved2_SHIFT                 5

/* BVNB_INTR2 :: PCI_STATUS :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP1_V0_INTR_MASK               0x00000010
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP1_V0_INTR_SHIFT              4

/* BVNB_INTR2 :: PCI_STATUS :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP1_G0_INTR_MASK               0x00000008
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP1_G0_INTR_SHIFT              3

/* BVNB_INTR2 :: PCI_STATUS :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved3_MASK                  0x00000004
#define BCHP_BVNB_INTR2_PCI_STATUS_reserved3_SHIFT                 2

/* BVNB_INTR2 :: PCI_STATUS :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP0_V0_INTR_MASK               0x00000002
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP0_V0_INTR_SHIFT              1

/* BVNB_INTR2 :: PCI_STATUS :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP0_G0_INTR_MASK               0x00000001
#define BCHP_BVNB_INTR2_PCI_STATUS_CMP0_G0_INTR_SHIFT              0

/***************************************************************************
 *PCI_SET - PCI interrupt Set Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_SET :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_SET_reserved0_MASK                     0xffff8000
#define BCHP_BVNB_INTR2_PCI_SET_reserved0_SHIFT                    15

/* BVNB_INTR2 :: PCI_SET :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_SET_LAB_MIN_MAX_DONE_INTR_MASK         0x00004000
#define BCHP_BVNB_INTR2_PCI_SET_LAB_MIN_MAX_DONE_INTR_SHIFT        14

/* BVNB_INTR2 :: PCI_SET :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_SET_LAB_HISTO_DONE_INTR_MASK           0x00002000
#define BCHP_BVNB_INTR2_PCI_SET_LAB_HISTO_DONE_INTR_SHIFT          13

/* BVNB_INTR2 :: PCI_SET :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_SET_GFD1_INTR_MASK                     0x00001000
#define BCHP_BVNB_INTR2_PCI_SET_GFD1_INTR_SHIFT                    12

/* BVNB_INTR2 :: PCI_SET :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_SET_GFD0_INTR_MASK                     0x00000800
#define BCHP_BVNB_INTR2_PCI_SET_GFD0_INTR_SHIFT                    11

/* BVNB_INTR2 :: PCI_SET :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_SET_reserved1_MASK                     0x00000700
#define BCHP_BVNB_INTR2_PCI_SET_reserved1_SHIFT                    8

/* BVNB_INTR2 :: PCI_SET :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_SET_CAP1_INTR_MASK                     0x00000080
#define BCHP_BVNB_INTR2_PCI_SET_CAP1_INTR_SHIFT                    7

/* BVNB_INTR2 :: PCI_SET :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_SET_CAP0_INTR_MASK                     0x00000040
#define BCHP_BVNB_INTR2_PCI_SET_CAP0_INTR_SHIFT                    6

/* BVNB_INTR2 :: PCI_SET :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_SET_reserved2_MASK                     0x00000020
#define BCHP_BVNB_INTR2_PCI_SET_reserved2_SHIFT                    5

/* BVNB_INTR2 :: PCI_SET :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_SET_CMP1_V0_INTR_MASK                  0x00000010
#define BCHP_BVNB_INTR2_PCI_SET_CMP1_V0_INTR_SHIFT                 4

/* BVNB_INTR2 :: PCI_SET :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_SET_CMP1_G0_INTR_MASK                  0x00000008
#define BCHP_BVNB_INTR2_PCI_SET_CMP1_G0_INTR_SHIFT                 3

/* BVNB_INTR2 :: PCI_SET :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_SET_reserved3_MASK                     0x00000004
#define BCHP_BVNB_INTR2_PCI_SET_reserved3_SHIFT                    2

/* BVNB_INTR2 :: PCI_SET :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_SET_CMP0_V0_INTR_MASK                  0x00000002
#define BCHP_BVNB_INTR2_PCI_SET_CMP0_V0_INTR_SHIFT                 1

/* BVNB_INTR2 :: PCI_SET :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_SET_CMP0_G0_INTR_MASK                  0x00000001
#define BCHP_BVNB_INTR2_PCI_SET_CMP0_G0_INTR_SHIFT                 0

/***************************************************************************
 *PCI_CLEAR - PCI interrupt Clear Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_CLEAR :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved0_MASK                   0xffff8000
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved0_SHIFT                  15

/* BVNB_INTR2 :: PCI_CLEAR :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_LAB_MIN_MAX_DONE_INTR_MASK       0x00004000
#define BCHP_BVNB_INTR2_PCI_CLEAR_LAB_MIN_MAX_DONE_INTR_SHIFT      14

/* BVNB_INTR2 :: PCI_CLEAR :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_LAB_HISTO_DONE_INTR_MASK         0x00002000
#define BCHP_BVNB_INTR2_PCI_CLEAR_LAB_HISTO_DONE_INTR_SHIFT        13

/* BVNB_INTR2 :: PCI_CLEAR :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_GFD1_INTR_MASK                   0x00001000
#define BCHP_BVNB_INTR2_PCI_CLEAR_GFD1_INTR_SHIFT                  12

/* BVNB_INTR2 :: PCI_CLEAR :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_GFD0_INTR_MASK                   0x00000800
#define BCHP_BVNB_INTR2_PCI_CLEAR_GFD0_INTR_SHIFT                  11

/* BVNB_INTR2 :: PCI_CLEAR :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved1_MASK                   0x00000700
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved1_SHIFT                  8

/* BVNB_INTR2 :: PCI_CLEAR :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CAP1_INTR_MASK                   0x00000080
#define BCHP_BVNB_INTR2_PCI_CLEAR_CAP1_INTR_SHIFT                  7

/* BVNB_INTR2 :: PCI_CLEAR :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CAP0_INTR_MASK                   0x00000040
#define BCHP_BVNB_INTR2_PCI_CLEAR_CAP0_INTR_SHIFT                  6

/* BVNB_INTR2 :: PCI_CLEAR :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved2_MASK                   0x00000020
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved2_SHIFT                  5

/* BVNB_INTR2 :: PCI_CLEAR :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP1_V0_INTR_MASK                0x00000010
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP1_V0_INTR_SHIFT               4

/* BVNB_INTR2 :: PCI_CLEAR :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP1_G0_INTR_MASK                0x00000008
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP1_G0_INTR_SHIFT               3

/* BVNB_INTR2 :: PCI_CLEAR :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved3_MASK                   0x00000004
#define BCHP_BVNB_INTR2_PCI_CLEAR_reserved3_SHIFT                  2

/* BVNB_INTR2 :: PCI_CLEAR :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP0_V0_INTR_MASK                0x00000002
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP0_V0_INTR_SHIFT               1

/* BVNB_INTR2 :: PCI_CLEAR :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP0_G0_INTR_MASK                0x00000001
#define BCHP_BVNB_INTR2_PCI_CLEAR_CMP0_G0_INTR_SHIFT               0

/***************************************************************************
 *PCI_MASK_STATUS - PCI interrupt Mask Status Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_MASK_STATUS :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved0_MASK             0xffff8000
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved0_SHIFT            15

/* BVNB_INTR2 :: PCI_MASK_STATUS :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_LAB_MIN_MAX_DONE_INTR_MASK 0x00004000
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_LAB_MIN_MAX_DONE_INTR_SHIFT 14

/* BVNB_INTR2 :: PCI_MASK_STATUS :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_LAB_HISTO_DONE_INTR_MASK   0x00002000
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_LAB_HISTO_DONE_INTR_SHIFT  13

/* BVNB_INTR2 :: PCI_MASK_STATUS :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_GFD1_INTR_MASK             0x00001000
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_GFD1_INTR_SHIFT            12

/* BVNB_INTR2 :: PCI_MASK_STATUS :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_GFD0_INTR_MASK             0x00000800
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_GFD0_INTR_SHIFT            11

/* BVNB_INTR2 :: PCI_MASK_STATUS :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved1_MASK             0x00000700
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved1_SHIFT            8

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CAP1_INTR_MASK             0x00000080
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CAP1_INTR_SHIFT            7

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CAP0_INTR_MASK             0x00000040
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CAP0_INTR_SHIFT            6

/* BVNB_INTR2 :: PCI_MASK_STATUS :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved2_MASK             0x00000020
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved2_SHIFT            5

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP1_V0_INTR_MASK          0x00000010
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP1_V0_INTR_SHIFT         4

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP1_G0_INTR_MASK          0x00000008
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP1_G0_INTR_SHIFT         3

/* BVNB_INTR2 :: PCI_MASK_STATUS :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved3_MASK             0x00000004
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_reserved3_SHIFT            2

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP0_V0_INTR_MASK          0x00000002
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP0_V0_INTR_SHIFT         1

/* BVNB_INTR2 :: PCI_MASK_STATUS :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP0_G0_INTR_MASK          0x00000001
#define BCHP_BVNB_INTR2_PCI_MASK_STATUS_CMP0_G0_INTR_SHIFT         0

/***************************************************************************
 *PCI_MASK_SET - PCI interrupt Mask Set Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_MASK_SET :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved0_MASK                0xffff8000
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved0_SHIFT               15

/* BVNB_INTR2 :: PCI_MASK_SET :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_LAB_MIN_MAX_DONE_INTR_MASK    0x00004000
#define BCHP_BVNB_INTR2_PCI_MASK_SET_LAB_MIN_MAX_DONE_INTR_SHIFT   14

/* BVNB_INTR2 :: PCI_MASK_SET :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_LAB_HISTO_DONE_INTR_MASK      0x00002000
#define BCHP_BVNB_INTR2_PCI_MASK_SET_LAB_HISTO_DONE_INTR_SHIFT     13

/* BVNB_INTR2 :: PCI_MASK_SET :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_GFD1_INTR_MASK                0x00001000
#define BCHP_BVNB_INTR2_PCI_MASK_SET_GFD1_INTR_SHIFT               12

/* BVNB_INTR2 :: PCI_MASK_SET :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_GFD0_INTR_MASK                0x00000800
#define BCHP_BVNB_INTR2_PCI_MASK_SET_GFD0_INTR_SHIFT               11

/* BVNB_INTR2 :: PCI_MASK_SET :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved1_MASK                0x00000700
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved1_SHIFT               8

/* BVNB_INTR2 :: PCI_MASK_SET :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CAP1_INTR_MASK                0x00000080
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CAP1_INTR_SHIFT               7

/* BVNB_INTR2 :: PCI_MASK_SET :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CAP0_INTR_MASK                0x00000040
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CAP0_INTR_SHIFT               6

/* BVNB_INTR2 :: PCI_MASK_SET :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved2_MASK                0x00000020
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved2_SHIFT               5

/* BVNB_INTR2 :: PCI_MASK_SET :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP1_V0_INTR_MASK             0x00000010
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP1_V0_INTR_SHIFT            4

/* BVNB_INTR2 :: PCI_MASK_SET :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP1_G0_INTR_MASK             0x00000008
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP1_G0_INTR_SHIFT            3

/* BVNB_INTR2 :: PCI_MASK_SET :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved3_MASK                0x00000004
#define BCHP_BVNB_INTR2_PCI_MASK_SET_reserved3_SHIFT               2

/* BVNB_INTR2 :: PCI_MASK_SET :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP0_V0_INTR_MASK             0x00000002
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP0_V0_INTR_SHIFT            1

/* BVNB_INTR2 :: PCI_MASK_SET :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP0_G0_INTR_MASK             0x00000001
#define BCHP_BVNB_INTR2_PCI_MASK_SET_CMP0_G0_INTR_SHIFT            0

/***************************************************************************
 *PCI_MASK_CLEAR - PCI interrupt Mask Clear Register
 ***************************************************************************/
/* BVNB_INTR2 :: PCI_MASK_CLEAR :: reserved0 [31:15] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved0_MASK              0xffff8000
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved0_SHIFT             15

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: LAB_MIN_MAX_DONE_INTR [14:14] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_LAB_MIN_MAX_DONE_INTR_MASK  0x00004000
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_LAB_MIN_MAX_DONE_INTR_SHIFT 14

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: LAB_HISTO_DONE_INTR [13:13] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_LAB_HISTO_DONE_INTR_MASK    0x00002000
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_LAB_HISTO_DONE_INTR_SHIFT   13

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: GFD1_INTR [12:12] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_GFD1_INTR_MASK              0x00001000
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_GFD1_INTR_SHIFT             12

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: GFD0_INTR [11:11] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_GFD0_INTR_MASK              0x00000800
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_GFD0_INTR_SHIFT             11

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: reserved1 [10:08] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved1_MASK              0x00000700
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved1_SHIFT             8

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CAP1_INTR [07:07] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CAP1_INTR_MASK              0x00000080
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CAP1_INTR_SHIFT             7

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CAP0_INTR [06:06] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CAP0_INTR_MASK              0x00000040
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CAP0_INTR_SHIFT             6

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: reserved2 [05:05] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved2_MASK              0x00000020
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved2_SHIFT             5

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CMP1_V0_INTR [04:04] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP1_V0_INTR_MASK           0x00000010
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP1_V0_INTR_SHIFT          4

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CMP1_G0_INTR [03:03] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP1_G0_INTR_MASK           0x00000008
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP1_G0_INTR_SHIFT          3

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: reserved3 [02:02] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved3_MASK              0x00000004
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_reserved3_SHIFT             2

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CMP0_V0_INTR [01:01] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP0_V0_INTR_MASK           0x00000002
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP0_V0_INTR_SHIFT          1

/* BVNB_INTR2 :: PCI_MASK_CLEAR :: CMP0_G0_INTR [00:00] */
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP0_G0_INTR_MASK           0x00000001
#define BCHP_BVNB_INTR2_PCI_MASK_CLEAR_CMP0_G0_INTR_SHIFT          0

#endif /* #ifndef BCHP_BVNB_INTR2_H__ */

/* End of File */