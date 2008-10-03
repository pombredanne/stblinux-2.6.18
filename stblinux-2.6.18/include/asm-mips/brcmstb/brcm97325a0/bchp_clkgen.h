/***************************************************************************
 *     Copyright (c) 1999-2007, Broadcom Corporation
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
 * Date:           Generated on         Tue Sep 25 17:06:01 2007
 *                 MD5 Checksum         060a528ae9e5f522671d33a2e2948f87
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008004
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/7325/rdb/a0/bchp_clkgen.h $
 * 
 * Hydra_Software_Devel/2   9/26/07 2:44p yuxiaz
 * PR32498: Updated RDB for 7325
 *
 ***************************************************************************/

#ifndef BCHP_CLKGEN_H__
#define BCHP_CLKGEN_H__

/***************************************************************************
 *CLKGEN - Clkgen registers
 ***************************************************************************/
#define BCHP_CLKGEN_PWRDN_CTRL_0                 0x00040000 /* Power Down Control Register #0 */
#define BCHP_CLKGEN_PWRDN_CTRL_1                 0x00040004 /* Power Down Control Register #1 */
#define BCHP_CLKGEN_PWRDN_CTRL_2                 0x00040008 /* Power Down Control Register #2 */
#define BCHP_CLKGEN_PWRDN_CTRL_3                 0x0004000c /* Power Down Control Register #3 */
#define BCHP_CLKGEN_PAD_CLOCK                    0x00040010 /* PAD Clock Control Register */
#define BCHP_CLKGEN_MISC                         0x00040014 /* clock_gen block output clock selection */
#define BCHP_CLKGEN_PAD_CLOCK_WITH_STRAP_CTRL    0x00040018 /* PAD Clock With Strap Control Register */
#define BCHP_CLKGEN_PLL_TEST_CTRL                0x00040020 /* PLL_TEST_CTRL Control Register */
#define BCHP_CLKGEN_AVD_CTRL                     0x00040024 /* AVD PLL reset, enable and powerdown */
#define BCHP_CLKGEN_AVD_DIV                      0x00040028 /* AVD PLL divider settings */
#define BCHP_CLKGEN_LOCK                         0x0004034c /* PLL lock status */
#define BCHP_CLKGEN_LOCK_CNTR_RESET              0x00040038 /* VCXO Lock Counter Reset */
#define BCHP_CLKGEN_AVD_LOCK_CNT                 0x00040058 /* AVD PLL Lock Counter */
#define BCHP_CLKGEN_CPU_LOCK_CNT                 0x0004005c /* CPU PLL Lock Counter */
#define BCHP_CLKGEN_MAIN_LOCK_CNT                0x00040060 /* MAIN PLL Lock Counter */

/***************************************************************************
 *PWRDN_CTRL_0 - Power Down Control Register #0
 ***************************************************************************/
/* CLKGEN :: PWRDN_CTRL_0 :: reserved_for_eco0 [31:13] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_reserved_for_eco0_MASK            0xffffe000
#define BCHP_CLKGEN_PWRDN_CTRL_0_reserved_for_eco0_SHIFT           13

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_XPT [12:12] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_XPT_MASK       0x00001000
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_XPT_SHIFT      12

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_VEC [11:11] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_VEC_MASK       0x00000800
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_VEC_SHIFT      11

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_USB [10:10] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_USB_MASK       0x00000400
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_USB_SHIFT      10

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_RPTD [09:09] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_RPTD_MASK      0x00000200
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_RPTD_SHIFT     9

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_HIF [08:08] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_HIF_MASK       0x00000100
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_HIF_SHIFT      8

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_GFX [07:07] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_GFX_MASK       0x00000080
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_GFX_SHIFT      7

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_ENET [06:06] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_ENET_MASK      0x00000040
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_ENET_SHIFT     6

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_BVNM [05:05] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVNM_MASK      0x00000020
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVNM_SHIFT     5

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_BVNE [04:04] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVNE_MASK      0x00000010
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVNE_SHIFT     4

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_BVND [03:03] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVND_MASK      0x00000008
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_BVND_SHIFT     3

/* CLKGEN :: PWRDN_CTRL_0 :: reserved_for_eco1 [02:02] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_reserved_for_eco1_MASK            0x00000004
#define BCHP_CLKGEN_PWRDN_CTRL_0_reserved_for_eco1_SHIFT           2

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_AVD [01:01] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_AVD_MASK       0x00000002
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_AVD_SHIFT      1

/* CLKGEN :: PWRDN_CTRL_0 :: PWRDN_CLOCK_216_CG_AIO [00:00] */
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_AIO_MASK       0x00000001
#define BCHP_CLKGEN_PWRDN_CTRL_0_PWRDN_CLOCK_216_CG_AIO_SHIFT      0

/***************************************************************************
 *PWRDN_CTRL_1 - Power Down Control Register #1
 ***************************************************************************/
/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_23P04_27_CG_PLLAUD0 [31:31] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_23P04_27_CG_PLLAUD0_MASK 0x80000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_23P04_27_CG_PLLAUD0_SHIFT 31

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_20P25_CG_XPT [30:30] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_20P25_CG_XPT_MASK     0x40000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_20P25_CG_XPT_SHIFT    30

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_27_CG_XPT [29:29] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_CG_XPT_MASK        0x20000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_CG_XPT_SHIFT       29

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_27_CG_SUN [28:28] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_CG_SUN_MASK        0x10000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_CG_SUN_SHIFT       28

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_27_656_VCXO_CG_VEC [27:27] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_656_VCXO_CG_VEC_MASK 0x08000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_27_656_VCXO_CG_VEC_SHIFT 27

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_40P5_CG_XPT [26:26] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_40P5_CG_XPT_MASK      0x04000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_40P5_CG_XPT_SHIFT     26

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_40_27_SC_CG_SUN [25:25] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_40_27_SC_CG_SUN_MASK  0x02000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_40_27_SC_CG_SUN_SHIFT 25

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_54_CG_XPT [24:24] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_54_CG_XPT_MASK        0x01000000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_54_CG_XPT_SHIFT       24

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_81_CG_XPT [23:23] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_81_CG_XPT_MASK        0x00800000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_81_CG_XPT_SHIFT       23

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_UART_CG_SUN [22:22] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_UART_CG_SUN_MASK  0x00400000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_UART_CG_SUN_SHIFT 22

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_DAC_CG_VEC [21:21] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_DAC_CG_VEC_MASK   0x00200000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_DAC_CG_VEC_SHIFT  21

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_XPT [20:20] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_XPT_MASK       0x00100000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_XPT_SHIFT      20

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_VEC [19:19] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_VEC_MASK       0x00080000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_VEC_SHIFT      19

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_VCXOCTL [18:18] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_VCXOCTL_MASK   0x00040000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_VCXOCTL_SHIFT  18

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_USB [17:17] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_USB_MASK       0x00020000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_USB_SHIFT      17

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_TDAC1 [16:16] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_TDAC1_MASK     0x00010000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_TDAC1_SHIFT    16

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_TDAC0 [15:15] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_TDAC0_MASK     0x00008000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_TDAC0_SHIFT    15

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_RPTD [14:14] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_RPTD_MASK      0x00004000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_RPTD_SHIFT     14

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_RFM [13:13] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_RFM_MASK       0x00002000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_RFM_SHIFT      13

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_MEMC [12:12] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_MEMC_MASK      0x00001000
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_MEMC_SHIFT     12

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_HIF [11:11] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_HIF_MASK       0x00000800
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_HIF_SHIFT      11

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_HDMI [10:10] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_HDMI_MASK      0x00000400
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_HDMI_SHIFT     10

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_GFX [09:09] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_GFX_MASK       0x00000200
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_GFX_SHIFT      9

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_ENET [08:08] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_ENET_MASK      0x00000100
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_ENET_SHIFT     8

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_CGM [07:07] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_CGM_MASK       0x00000080
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_CGM_SHIFT      7

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_CG [06:06] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_CG_MASK        0x00000040
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_CG_SHIFT       6

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_BVNM [05:05] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVNM_MASK      0x00000020
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVNM_SHIFT     5

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_BVNE [04:04] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVNE_MASK      0x00000010
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVNE_SHIFT     4

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_BVND [03:03] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVND_MASK      0x00000008
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_BVND_SHIFT     3

/* CLKGEN :: PWRDN_CTRL_1 :: reserved_for_eco0 [02:02] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_reserved_for_eco0_MASK            0x00000004
#define BCHP_CLKGEN_PWRDN_CTRL_1_reserved_for_eco0_SHIFT           2

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_AVD [01:01] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_AVD_MASK       0x00000002
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_AVD_SHIFT      1

/* CLKGEN :: PWRDN_CTRL_1 :: PWRDN_CLOCK_108_CG_AIO [00:00] */
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_AIO_MASK       0x00000001
#define BCHP_CLKGEN_PWRDN_CTRL_1_PWRDN_CLOCK_108_CG_AIO_SHIFT      0

/***************************************************************************
 *PWRDN_CTRL_2 - Power Down Control Register #2
 ***************************************************************************/
/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_500_CG_CPU [31:31] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_500_CG_CPU_MASK       0x80000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_500_CG_CPU_SHIFT      31

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_216_CG_TFEC [30:30] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_TFEC_MASK      0x40000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_TFEC_SHIFT     30

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_216_CG_AFEC [29:29] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_AFEC_MASK      0x20000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_AFEC_SHIFT     29

/* CLKGEN :: PWRDN_CTRL_2 :: reserved_for_eco0 [28:28] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco0_MASK            0x10000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco0_SHIFT           28

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_216_CG_CPU [27:27] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_CPU_MASK       0x08000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_216_CG_CPU_SHIFT      27

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_27_UHFR_CG_SUN [26:26] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_UHFR_CG_SUN_MASK   0x04000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_UHFR_CG_SUN_SHIFT  26

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_27_SM_CG_SUN [25:25] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_SM_CG_SUN_MASK     0x02000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_SM_CG_SUN_SHIFT    25

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_32P4_DAA_CG_SUN [24:24] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_32P4_DAA_CG_SUN_MASK  0x01000000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_32P4_DAA_CG_SUN_SHIFT 24

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_81_27_CG_UHF [23:23] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_27_CG_UHF_MASK     0x00800000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_27_CG_UHF_SHIFT    23

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_USB [22:22] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_USB_MASK 0x00400000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_USB_SHIFT 22

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_TFEC [21:21] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_TFEC_MASK 0x00200000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_TFEC_SHIFT 21

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_XPT [20:20] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_XPT_MASK 0x00100000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_XPT_SHIFT 20

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_BVND [19:19] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_BVND_MASK 0x00080000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_BVND_SHIFT 19

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_HIF [18:18] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_HIF_MASK 0x00040000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_HIF_SHIFT 18

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_QPSK [17:17] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_QPSK_MASK 0x00020000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_QPSK_SHIFT 17

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_PINMUX_CG_SDS0 [16:16] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_SDS0_MASK 0x00010000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_PINMUX_CG_SDS0_SHIFT 16

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_27_CODEC_MCLK_CG_PAD [15:15] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_CODEC_MCLK_CG_PAD_MASK 0x00008000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_CODEC_MCLK_CG_PAD_SHIFT 15

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_25_CG_ENET [14:14] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_25_CG_ENET_MASK       0x00004000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_25_CG_ENET_SHIFT      14

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_CG_FTM [13:13] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_FTM_MASK       0x00002000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_FTM_SHIFT      13

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_33_PLL [12:12] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_33_PLL_MASK           0x00001000
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_33_PLL_SHIFT          12

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_81_CG_SUN [11:11] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_CG_SUN_MASK        0x00000800
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_CG_SUN_SHIFT       11

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_81_27_UHFR_CG_SUN [10:10] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_27_UHFR_CG_SUN_MASK 0x00000400
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_81_27_UHFR_CG_SUN_SHIFT 10

/* CLKGEN :: PWRDN_CTRL_2 :: reserved_for_eco1 [09:09] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco1_MASK            0x00000200
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco1_SHIFT           9

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_CG_QPSK [08:08] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_QPSK_MASK      0x00000100
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_QPSK_SHIFT     8

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_CG_SDS0 [07:07] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_SDS0_MASK      0x00000080
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_SDS0_SHIFT     7

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_108_CG_AFEC [06:06] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_AFEC_MASK      0x00000040
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_108_CG_AFEC_SHIFT     6

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_27_VCXO_CG_PAD [05:05] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_VCXO_CG_PAD_MASK   0x00000020
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_27_VCXO_CG_PAD_SHIFT  5

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_33_27_PCI_CG_PAD [04:04] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_33_27_PCI_CG_PAD_MASK 0x00000010
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_33_27_PCI_CG_PAD_SHIFT 4

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_54_40P5_ACC_CG_PAD [03:03] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_54_40P5_ACC_CG_PAD_MASK 0x00000008
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_54_40P5_ACC_CG_PAD_SHIFT 3

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_9_CG_JTAG [02:02] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_9_CG_JTAG_MASK        0x00000004
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_9_CG_JTAG_SHIFT       2

/* CLKGEN :: PWRDN_CTRL_2 :: reserved_for_eco2 [01:01] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco2_MASK            0x00000002
#define BCHP_CLKGEN_PWRDN_CTRL_2_reserved_for_eco2_SHIFT           1

/* CLKGEN :: PWRDN_CTRL_2 :: PWRDN_CLOCK_23P04_27_CG_PLLAUD1 [00:00] */
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_23P04_27_CG_PLLAUD1_MASK 0x00000001
#define BCHP_CLKGEN_PWRDN_CTRL_2_PWRDN_CLOCK_23P04_27_CG_PLLAUD1_SHIFT 0

/***************************************************************************
 *PWRDN_CTRL_3 - Power Down Control Register #3
 ***************************************************************************/
/* CLKGEN :: PWRDN_CTRL_3 :: reserved_for_eco0 [31:31] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_reserved_for_eco0_MASK            0x80000000
#define BCHP_CLKGEN_PWRDN_CTRL_3_reserved_for_eco0_SHIFT           31

/* CLKGEN :: PWRDN_CTRL_3 :: PWRDN_CLOCK_216_CG_SUN [30:30] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_216_CG_SUN_MASK       0x40000000
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_216_CG_SUN_SHIFT      30

/* CLKGEN :: PWRDN_CTRL_3 :: PWRDN_CLOCK_RPT_AUD_DSP [29:29] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_RPT_AUD_DSP_MASK      0x20000000
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_RPT_AUD_DSP_SHIFT     29

/* CLKGEN :: PWRDN_CTRL_3 :: PWRDN_CLOCK_AVD0_PROG [28:28] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_AVD0_PROG_MASK        0x10000000
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_CLOCK_AVD0_PROG_SHIFT       28

/* CLKGEN :: PWRDN_CTRL_3 :: PWRDN_PIPE_CLOCK_216_CG [27:27] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_PIPE_CLOCK_216_CG_MASK      0x08000000
#define BCHP_CLKGEN_PWRDN_CTRL_3_PWRDN_PIPE_CLOCK_216_CG_SHIFT     27

/* CLKGEN :: PWRDN_CTRL_3 :: reserved_for_eco1 [26:00] */
#define BCHP_CLKGEN_PWRDN_CTRL_3_reserved_for_eco1_MASK            0x07ffffff
#define BCHP_CLKGEN_PWRDN_CTRL_3_reserved_for_eco1_SHIFT           0

/***************************************************************************
 *PAD_CLOCK - PAD Clock Control Register
 ***************************************************************************/
/* CLKGEN :: PAD_CLOCK :: reserved0 [31:07] */
#define BCHP_CLKGEN_PAD_CLOCK_reserved0_MASK                       0xffffff80
#define BCHP_CLKGEN_PAD_CLOCK_reserved0_SHIFT                      7

/* CLKGEN :: PAD_CLOCK :: CLOCK_ACC_TEST_MODE [06:06] */
#define BCHP_CLKGEN_PAD_CLOCK_CLOCK_ACC_TEST_MODE_MASK             0x00000040
#define BCHP_CLKGEN_PAD_CLOCK_CLOCK_ACC_TEST_MODE_SHIFT            6

/* CLKGEN :: PAD_CLOCK :: CLOCK_ACC_TEST_SEL [05:01] */
#define BCHP_CLKGEN_PAD_CLOCK_CLOCK_ACC_TEST_SEL_MASK              0x0000003e
#define BCHP_CLKGEN_PAD_CLOCK_CLOCK_ACC_TEST_SEL_SHIFT             1

/* CLKGEN :: PAD_CLOCK :: ACC_PAD_CLOCK_SEL [00:00] */
#define BCHP_CLKGEN_PAD_CLOCK_ACC_PAD_CLOCK_SEL_MASK               0x00000001
#define BCHP_CLKGEN_PAD_CLOCK_ACC_PAD_CLOCK_SEL_SHIFT              0

/***************************************************************************
 *MISC - clock_gen block output clock selection
 ***************************************************************************/
/* CLKGEN :: MISC :: reserved0 [31:05] */
#define BCHP_CLKGEN_MISC_reserved0_MASK                            0xffffffe0
#define BCHP_CLKGEN_MISC_reserved0_SHIFT                           5

/* CLKGEN :: MISC :: UHFR_CLK_INV_SEL [04:04] */
#define BCHP_CLKGEN_MISC_UHFR_CLK_INV_SEL_MASK                     0x00000010
#define BCHP_CLKGEN_MISC_UHFR_CLK_INV_SEL_SHIFT                    4

/* CLKGEN :: MISC :: UHFR_CLK_SEL [03:03] */
#define BCHP_CLKGEN_MISC_UHFR_CLK_SEL_MASK                         0x00000008
#define BCHP_CLKGEN_MISC_UHFR_CLK_SEL_SHIFT                        3

/* CLKGEN :: MISC :: reserved_for_eco1 [02:02] */
#define BCHP_CLKGEN_MISC_reserved_for_eco1_MASK                    0x00000004
#define BCHP_CLKGEN_MISC_reserved_for_eco1_SHIFT                   2

/* CLKGEN :: MISC :: DIS_VEC_VCXO_656_CLK [01:01] */
#define BCHP_CLKGEN_MISC_DIS_VEC_VCXO_656_CLK_MASK                 0x00000002
#define BCHP_CLKGEN_MISC_DIS_VEC_VCXO_656_CLK_SHIFT                1

/* CLKGEN :: MISC :: reserved_for_eco2 [00:00] */
#define BCHP_CLKGEN_MISC_reserved_for_eco2_MASK                    0x00000001
#define BCHP_CLKGEN_MISC_reserved_for_eco2_SHIFT                   0

/***************************************************************************
 *PAD_CLOCK_WITH_STRAP_CTRL - PAD Clock With Strap Control Register
 ***************************************************************************/
/* CLKGEN :: PAD_CLOCK_WITH_STRAP_CTRL :: reserved0 [31:01] */
#define BCHP_CLKGEN_PAD_CLOCK_WITH_STRAP_CTRL_reserved0_MASK       0xfffffffe
#define BCHP_CLKGEN_PAD_CLOCK_WITH_STRAP_CTRL_reserved0_SHIFT      1

/* CLKGEN :: PAD_CLOCK_WITH_STRAP_CTRL :: PCI_PAD_CLOCK_SEL [00:00] */
#define BCHP_CLKGEN_PAD_CLOCK_WITH_STRAP_CTRL_PCI_PAD_CLOCK_SEL_MASK 0x00000001
#define BCHP_CLKGEN_PAD_CLOCK_WITH_STRAP_CTRL_PCI_PAD_CLOCK_SEL_SHIFT 0

/***************************************************************************
 *PLL_TEST_CTRL - PLL_TEST_CTRL Control Register
 ***************************************************************************/
/* CLKGEN :: PLL_TEST_CTRL :: reserved0 [31:09] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_reserved0_MASK                   0xfffffe00
#define BCHP_CLKGEN_PLL_TEST_CTRL_reserved0_SHIFT                  9

/* CLKGEN :: PLL_TEST_CTRL :: TEST_EN_AMP_LIMITER [08:08] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_AMP_LIMITER_MASK         0x00000100
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_AMP_LIMITER_SHIFT        8

/* CLKGEN :: PLL_TEST_CTRL :: TEST_EN_DIFFOSC [07:07] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_DIFFOSC_MASK             0x00000080
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_DIFFOSC_SHIFT            7

/* CLKGEN :: PLL_TEST_CTRL :: TEST_EN_PLL_AVD [06:06] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_AVD_MASK             0x00000040
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_AVD_SHIFT            6

/* CLKGEN :: PLL_TEST_CTRL :: TEST_EN_PLL_CPU [05:05] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_CPU_MASK             0x00000020
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_CPU_SHIFT            5

/* CLKGEN :: PLL_TEST_CTRL :: TEST_EN_PLL_MAIN [04:04] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_MAIN_MASK            0x00000010
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_EN_PLL_MAIN_SHIFT           4

/* CLKGEN :: PLL_TEST_CTRL :: TEST_SEL_PLL [03:00] */
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_SEL_PLL_MASK                0x0000000f
#define BCHP_CLKGEN_PLL_TEST_CTRL_TEST_SEL_PLL_SHIFT               0

/***************************************************************************
 *AVD_CTRL - AVD PLL reset, enable and powerdown
 ***************************************************************************/
/* CLKGEN :: AVD_CTRL :: reserved0 [31:03] */
#define BCHP_CLKGEN_AVD_CTRL_reserved0_MASK                        0xfffffff8
#define BCHP_CLKGEN_AVD_CTRL_reserved0_SHIFT                       3

/* CLKGEN :: AVD_CTRL :: POWERDOWN [02:02] */
#define BCHP_CLKGEN_AVD_CTRL_POWERDOWN_MASK                        0x00000004
#define BCHP_CLKGEN_AVD_CTRL_POWERDOWN_SHIFT                       2
#define BCHP_CLKGEN_AVD_CTRL_POWERDOWN_Powerdown                   1
#define BCHP_CLKGEN_AVD_CTRL_POWERDOWN_Normal                      0

/* CLKGEN :: AVD_CTRL :: CLOCK_ENA [01:01] */
#define BCHP_CLKGEN_AVD_CTRL_CLOCK_ENA_MASK                        0x00000002
#define BCHP_CLKGEN_AVD_CTRL_CLOCK_ENA_SHIFT                       1
#define BCHP_CLKGEN_AVD_CTRL_CLOCK_ENA_Enable                      1
#define BCHP_CLKGEN_AVD_CTRL_CLOCK_ENA_Disable                     0

/* CLKGEN :: AVD_CTRL :: RESET [00:00] */
#define BCHP_CLKGEN_AVD_CTRL_RESET_MASK                            0x00000001
#define BCHP_CLKGEN_AVD_CTRL_RESET_SHIFT                           0
#define BCHP_CLKGEN_AVD_CTRL_RESET_Reset                           1
#define BCHP_CLKGEN_AVD_CTRL_RESET_Normal                          0

/***************************************************************************
 *AVD_DIV - AVD PLL divider settings
 ***************************************************************************/
/* CLKGEN :: AVD_DIV :: reserved0 [31:26] */
#define BCHP_CLKGEN_AVD_DIV_reserved0_MASK                         0xfc000000
#define BCHP_CLKGEN_AVD_DIV_reserved0_SHIFT                        26

/* CLKGEN :: AVD_DIV :: VCORNG [25:24] */
#define BCHP_CLKGEN_AVD_DIV_VCORNG_MASK                            0x03000000
#define BCHP_CLKGEN_AVD_DIV_VCORNG_SHIFT                           24

/* CLKGEN :: AVD_DIV :: reserved_for_eco1 [23:17] */
#define BCHP_CLKGEN_AVD_DIV_reserved_for_eco1_MASK                 0x00fe0000
#define BCHP_CLKGEN_AVD_DIV_reserved_for_eco1_SHIFT                17

/* CLKGEN :: AVD_DIV :: NDIV_INT [16:08] */
#define BCHP_CLKGEN_AVD_DIV_NDIV_INT_MASK                          0x0001ff00
#define BCHP_CLKGEN_AVD_DIV_NDIV_INT_SHIFT                         8

/* CLKGEN :: AVD_DIV :: M1DIV [07:00] */
#define BCHP_CLKGEN_AVD_DIV_M1DIV_MASK                             0x000000ff
#define BCHP_CLKGEN_AVD_DIV_M1DIV_SHIFT                            0

/***************************************************************************
 *LOCK - PLL lock status
 ***************************************************************************/
/* CLKGEN :: LOCK :: reserved0 [31:03] */
#define BCHP_CLKGEN_LOCK_reserved0_MASK                            0xfffffff8
#define BCHP_CLKGEN_LOCK_reserved0_SHIFT                           3

/* CLKGEN :: LOCK :: AVD [02:02] */
#define BCHP_CLKGEN_LOCK_AVD_MASK                                  0x00000004
#define BCHP_CLKGEN_LOCK_AVD_SHIFT                                 2

/* CLKGEN :: LOCK :: CPU [01:01] */
#define BCHP_CLKGEN_LOCK_CPU_MASK                                  0x00000002
#define BCHP_CLKGEN_LOCK_CPU_SHIFT                                 1

/* CLKGEN :: LOCK :: MAIN [00:00] */
#define BCHP_CLKGEN_LOCK_MAIN_MASK                                 0x00000001
#define BCHP_CLKGEN_LOCK_MAIN_SHIFT                                0

/***************************************************************************
 *LOCK_CNTR_RESET - VCXO Lock Counter Reset
 ***************************************************************************/
/* CLKGEN :: LOCK_CNTR_RESET :: reserved0 [31:03] */
#define BCHP_CLKGEN_LOCK_CNTR_RESET_reserved0_MASK                 0xfffffff8
#define BCHP_CLKGEN_LOCK_CNTR_RESET_reserved0_SHIFT                3

/* CLKGEN :: LOCK_CNTR_RESET :: AVD [02:02] */
#define BCHP_CLKGEN_LOCK_CNTR_RESET_AVD_MASK                       0x00000004
#define BCHP_CLKGEN_LOCK_CNTR_RESET_AVD_SHIFT                      2

/* CLKGEN :: LOCK_CNTR_RESET :: CPU [01:01] */
#define BCHP_CLKGEN_LOCK_CNTR_RESET_CPU_MASK                       0x00000002
#define BCHP_CLKGEN_LOCK_CNTR_RESET_CPU_SHIFT                      1

/* CLKGEN :: LOCK_CNTR_RESET :: MAIN [00:00] */
#define BCHP_CLKGEN_LOCK_CNTR_RESET_MAIN_MASK                      0x00000001
#define BCHP_CLKGEN_LOCK_CNTR_RESET_MAIN_SHIFT                     0

/***************************************************************************
 *AVD_LOCK_CNT - AVD PLL Lock Counter
 ***************************************************************************/
/* CLKGEN :: AVD_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_CLKGEN_AVD_LOCK_CNT_reserved0_MASK                    0xfffff000
#define BCHP_CLKGEN_AVD_LOCK_CNT_reserved0_SHIFT                   12

/* CLKGEN :: AVD_LOCK_CNT :: COUNT [11:00] */
#define BCHP_CLKGEN_AVD_LOCK_CNT_COUNT_MASK                        0x00000fff
#define BCHP_CLKGEN_AVD_LOCK_CNT_COUNT_SHIFT                       0

/***************************************************************************
 *CPU_LOCK_CNT - CPU PLL Lock Counter
 ***************************************************************************/
/* CLKGEN :: CPU_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_CLKGEN_CPU_LOCK_CNT_reserved0_MASK                    0xfffff000
#define BCHP_CLKGEN_CPU_LOCK_CNT_reserved0_SHIFT                   12

/* CLKGEN :: CPU_LOCK_CNT :: COUNT [11:00] */
#define BCHP_CLKGEN_CPU_LOCK_CNT_COUNT_MASK                        0x00000fff
#define BCHP_CLKGEN_CPU_LOCK_CNT_COUNT_SHIFT                       0

/***************************************************************************
 *MAIN_LOCK_CNT - MAIN PLL Lock Counter
 ***************************************************************************/
/* CLKGEN :: MAIN_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_CLKGEN_MAIN_LOCK_CNT_reserved0_MASK                   0xfffff000
#define BCHP_CLKGEN_MAIN_LOCK_CNT_reserved0_SHIFT                  12

/* CLKGEN :: MAIN_LOCK_CNT :: COUNT [11:00] */
#define BCHP_CLKGEN_MAIN_LOCK_CNT_COUNT_MASK                       0x00000fff
#define BCHP_CLKGEN_MAIN_LOCK_CNT_COUNT_SHIFT                      0

#endif /* #ifndef BCHP_CLKGEN_H__ */

/* End of File */
