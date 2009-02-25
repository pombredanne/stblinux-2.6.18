/***************************************************************************
 *     Copyright (c) 1999-2009, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: bchp_vcxo_ctl_misc.h $
 * $brcm_Revision: Hydra_Software_Devel/1 $
 * $brcm_Date: 1/23/09 1:47p $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Fri Jan 23 11:26:01 2009
 *                 MD5 Checksum         16788e155ebd540a0f1eb79b01eb33e6
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/7336/rdb/a0/bchp_vcxo_ctl_misc.h $
 * 
 * Hydra_Software_Devel/1   1/23/09 1:47p tdo
 * PR51405: Initial check in
 *
 ***************************************************************************/

#ifndef BCHP_VCXO_CTL_MISC_H__
#define BCHP_VCXO_CTL_MISC_H__

/***************************************************************************
 *VCXO_CTL_MISC - VCXO Core Registers
 ***************************************************************************/
#define BCHP_VCXO_CTL_MISC_VC0_CTRL              0x00041200 /* VCXO 0 reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL              0x00041204 /* AVD PLL reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL              0x00041208 /* Audio PLL 0 reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL              0x0004120c /* Audio PLL 1 reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL             0x00041210 /* EREF PLL  reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL           0x00041218 /* Audio DSP PLL reset, enable and powerdown */
#define BCHP_VCXO_CTL_MISC_LOCK                  0x0004121c /* VCXO core lock status */
#define BCHP_VCXO_CTL_MISC_VC0_DIV               0x00041220 /* VCXO 0 PLL divider settings */
#define BCHP_VCXO_CTL_MISC_AVD_DIV               0x00041228 /* AVD PLL divider settings */
#define BCHP_VCXO_CTL_MISC_EREF_DIV              0x0004122c /* EREF PLL divider settings */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV            0x00041230 /* Audio DSP PLL divider settings */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET       0x00041238 /* VCXO Lock Counter Reset */
#define BCHP_VCXO_CTL_MISC_VC0_LOCK_CNT          0x0004123c /* VCXO 0 Lock Counter */
#define BCHP_VCXO_CTL_MISC_AC0_LOCK_CNT          0x00041244 /* Audio PLL 0 Lock Counter */
#define BCHP_VCXO_CTL_MISC_AC1_LOCK_CNT          0x00041248 /* Audio PLL 1 Lock Counter */
#define BCHP_VCXO_CTL_MISC_EREF_LOCK_CNT         0x0004124c /* EREF PLL Lock Counter */
#define BCHP_VCXO_CTL_MISC_AUDDSP_LOCK_CNT       0x00041254 /* Audio DSP PLL Lock Counter */
#define BCHP_VCXO_CTL_MISC_AVD_LOCK_CNT          0x00041258 /* AVD PLL Lock Counter */
#define BCHP_VCXO_CTL_MISC_TEST_SEL              0x0004127c /* VCXO core test select */

/***************************************************************************
 *VC0_CTRL - VCXO 0 reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: VC0_CTRL :: reserved0 [31:07] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_reserved0_MASK                 0xffffff80
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_reserved0_SHIFT                7

/* VCXO_CTL_MISC :: VC0_CTRL :: NDIV_MODE [06:04] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_NDIV_MODE_MASK                 0x00000070
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_NDIV_MODE_SHIFT                4

/* VCXO_CTL_MISC :: VC0_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_MASK                 0x00000008
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_SHIFT                3
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_Powerdown            1
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_POWERDOWN_Normal               0

/* VCXO_CTL_MISC :: VC0_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_CLOCK_ENA_MASK                 0x00000004
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_CLOCK_ENA_SHIFT                2
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_CLOCK_ENA_Enable               1
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_CLOCK_ENA_Disable              0

/* VCXO_CTL_MISC :: VC0_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_MASK                    0x00000002
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_SHIFT                   1
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_DRESET_Normal                  0

/* VCXO_CTL_MISC :: VC0_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_MASK                    0x00000001
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_SHIFT                   0
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_VC0_CTRL_ARESET_Normal                  0

/***************************************************************************
 *AVD_CTRL - AVD PLL reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: AVD_CTRL :: reserved0 [31:04] */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_reserved0_MASK                 0xfffffff0
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_reserved0_SHIFT                4

/* VCXO_CTL_MISC :: AVD_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_POWERDOWN_MASK                 0x00000008
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_POWERDOWN_SHIFT                3
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_POWERDOWN_Powerdown            1
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_POWERDOWN_Normal               0

/* VCXO_CTL_MISC :: AVD_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_CLOCK_ENA_MASK                 0x00000004
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_CLOCK_ENA_SHIFT                2
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_CLOCK_ENA_Enable               1
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_CLOCK_ENA_Disable              0

/* VCXO_CTL_MISC :: AVD_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_DRESET_MASK                    0x00000002
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_DRESET_SHIFT                   1
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_DRESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_DRESET_Normal                  0

/* VCXO_CTL_MISC :: AVD_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_ARESET_MASK                    0x00000001
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_ARESET_SHIFT                   0
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_ARESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AVD_CTRL_ARESET_Normal                  0

/***************************************************************************
 *AC0_CTRL - Audio PLL 0 reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: AC0_CTRL :: reserved0 [31:04] */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_reserved0_MASK                 0xfffffff0
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_reserved0_SHIFT                4

/* VCXO_CTL_MISC :: AC0_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_MASK                 0x00000008
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_SHIFT                3
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_Powerdown            1
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_POWERDOWN_Normal               0

/* VCXO_CTL_MISC :: AC0_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_CLOCK_ENA_MASK                 0x00000004
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_CLOCK_ENA_SHIFT                2
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_CLOCK_ENA_Enable               1
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_CLOCK_ENA_Disable              0

/* VCXO_CTL_MISC :: AC0_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_MASK                    0x00000002
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_SHIFT                   1
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_DRESET_Normal                  0

/* VCXO_CTL_MISC :: AC0_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_MASK                    0x00000001
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_SHIFT                   0
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AC0_CTRL_ARESET_Normal                  0

/***************************************************************************
 *AC1_CTRL - Audio PLL 1 reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: AC1_CTRL :: reserved0 [31:04] */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_reserved0_MASK                 0xfffffff0
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_reserved0_SHIFT                4

/* VCXO_CTL_MISC :: AC1_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_POWERDOWN_MASK                 0x00000008
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_POWERDOWN_SHIFT                3
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_POWERDOWN_Powerdown            1
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_POWERDOWN_Normal               0

/* VCXO_CTL_MISC :: AC1_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_CLOCK_ENA_MASK                 0x00000004
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_CLOCK_ENA_SHIFT                2
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_CLOCK_ENA_Enable               1
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_CLOCK_ENA_Disable              0

/* VCXO_CTL_MISC :: AC1_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_DRESET_MASK                    0x00000002
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_DRESET_SHIFT                   1
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_DRESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_DRESET_Normal                  0

/* VCXO_CTL_MISC :: AC1_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_ARESET_MASK                    0x00000001
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_ARESET_SHIFT                   0
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_ARESET_Reset                   1
#define BCHP_VCXO_CTL_MISC_AC1_CTRL_ARESET_Normal                  0

/***************************************************************************
 *EREF_CTRL - EREF PLL  reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: EREF_CTRL :: reserved0 [31:04] */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_reserved0_MASK                0xfffffff0
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_reserved0_SHIFT               4

/* VCXO_CTL_MISC :: EREF_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_POWERDOWN_MASK                0x00000008
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_POWERDOWN_SHIFT               3
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_POWERDOWN_Powerdown           1
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_POWERDOWN_Normal              0

/* VCXO_CTL_MISC :: EREF_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_CLOCK_ENA_MASK                0x00000004
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_CLOCK_ENA_SHIFT               2
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_CLOCK_ENA_Enable              1
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_CLOCK_ENA_Disable             0

/* VCXO_CTL_MISC :: EREF_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_DRESET_MASK                   0x00000002
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_DRESET_SHIFT                  1
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_DRESET_Reset                  1
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_DRESET_Normal                 0

/* VCXO_CTL_MISC :: EREF_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_ARESET_MASK                   0x00000001
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_ARESET_SHIFT                  0
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_ARESET_Reset                  1
#define BCHP_VCXO_CTL_MISC_EREF_CTRL_ARESET_Normal                 0

/***************************************************************************
 *AUDDSP_CTRL - Audio DSP PLL reset, enable and powerdown
 ***************************************************************************/
/* VCXO_CTL_MISC :: AUDDSP_CTRL :: reserved0 [31:04] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_reserved0_MASK              0xfffffff0
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_reserved0_SHIFT             4

/* VCXO_CTL_MISC :: AUDDSP_CTRL :: POWERDOWN [03:03] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_POWERDOWN_MASK              0x00000008
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_POWERDOWN_SHIFT             3
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_POWERDOWN_Powerdown         1
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_POWERDOWN_Normal            0

/* VCXO_CTL_MISC :: AUDDSP_CTRL :: CLOCK_ENA [02:02] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_CLOCK_ENA_MASK              0x00000004
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_CLOCK_ENA_SHIFT             2
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_CLOCK_ENA_Enable            1
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_CLOCK_ENA_Disable           0

/* VCXO_CTL_MISC :: AUDDSP_CTRL :: DRESET [01:01] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_DRESET_MASK                 0x00000002
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_DRESET_SHIFT                1
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_DRESET_Reset                1
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_DRESET_Normal               0

/* VCXO_CTL_MISC :: AUDDSP_CTRL :: ARESET [00:00] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_ARESET_MASK                 0x00000001
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_ARESET_SHIFT                0
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_ARESET_Reset                1
#define BCHP_VCXO_CTL_MISC_AUDDSP_CTRL_ARESET_Normal               0

/***************************************************************************
 *LOCK - VCXO core lock status
 ***************************************************************************/
/* VCXO_CTL_MISC :: LOCK :: reserved0 [31:07] */
#define BCHP_VCXO_CTL_MISC_LOCK_reserved0_MASK                     0xffffff80
#define BCHP_VCXO_CTL_MISC_LOCK_reserved0_SHIFT                    7

/* VCXO_CTL_MISC :: LOCK :: AUDDSP [06:06] */
#define BCHP_VCXO_CTL_MISC_LOCK_AUDDSP_MASK                        0x00000040
#define BCHP_VCXO_CTL_MISC_LOCK_AUDDSP_SHIFT                       6

/* VCXO_CTL_MISC :: LOCK :: reserved1 [05:05] */
#define BCHP_VCXO_CTL_MISC_LOCK_reserved1_MASK                     0x00000020
#define BCHP_VCXO_CTL_MISC_LOCK_reserved1_SHIFT                    5

/* VCXO_CTL_MISC :: LOCK :: EREF [04:04] */
#define BCHP_VCXO_CTL_MISC_LOCK_EREF_MASK                          0x00000010
#define BCHP_VCXO_CTL_MISC_LOCK_EREF_SHIFT                         4

/* VCXO_CTL_MISC :: LOCK :: AC1 [03:03] */
#define BCHP_VCXO_CTL_MISC_LOCK_AC1_MASK                           0x00000008
#define BCHP_VCXO_CTL_MISC_LOCK_AC1_SHIFT                          3

/* VCXO_CTL_MISC :: LOCK :: AC0 [02:02] */
#define BCHP_VCXO_CTL_MISC_LOCK_AC0_MASK                           0x00000004
#define BCHP_VCXO_CTL_MISC_LOCK_AC0_SHIFT                          2

/* VCXO_CTL_MISC :: LOCK :: AVD [01:01] */
#define BCHP_VCXO_CTL_MISC_LOCK_AVD_MASK                           0x00000002
#define BCHP_VCXO_CTL_MISC_LOCK_AVD_SHIFT                          1

/* VCXO_CTL_MISC :: LOCK :: VC0 [00:00] */
#define BCHP_VCXO_CTL_MISC_LOCK_VC0_MASK                           0x00000001
#define BCHP_VCXO_CTL_MISC_LOCK_VC0_SHIFT                          0

/***************************************************************************
 *VC0_DIV - VCXO 0 PLL divider settings
 ***************************************************************************/
/* VCXO_CTL_MISC :: VC0_DIV :: reserved0 [31:26] */
#define BCHP_VCXO_CTL_MISC_VC0_DIV_reserved0_MASK                  0xfc000000
#define BCHP_VCXO_CTL_MISC_VC0_DIV_reserved0_SHIFT                 26

/* VCXO_CTL_MISC :: VC0_DIV :: VCORNG [25:24] */
#define BCHP_VCXO_CTL_MISC_VC0_DIV_VCORNG_MASK                     0x03000000
#define BCHP_VCXO_CTL_MISC_VC0_DIV_VCORNG_SHIFT                    24

/* VCXO_CTL_MISC :: VC0_DIV :: M3DIV [23:16] */
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M3DIV_MASK                      0x00ff0000
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M3DIV_SHIFT                     16

/* VCXO_CTL_MISC :: VC0_DIV :: M2DIV [15:08] */
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M2DIV_MASK                      0x0000ff00
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M2DIV_SHIFT                     8

/* VCXO_CTL_MISC :: VC0_DIV :: M1DIV [07:00] */
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M1DIV_MASK                      0x000000ff
#define BCHP_VCXO_CTL_MISC_VC0_DIV_M1DIV_SHIFT                     0

/***************************************************************************
 *AVD_DIV - AVD PLL divider settings
 ***************************************************************************/
/* VCXO_CTL_MISC :: AVD_DIV :: reserved0 [31:26] */
#define BCHP_VCXO_CTL_MISC_AVD_DIV_reserved0_MASK                  0xfc000000
#define BCHP_VCXO_CTL_MISC_AVD_DIV_reserved0_SHIFT                 26

/* VCXO_CTL_MISC :: AVD_DIV :: VCORNG [25:24] */
#define BCHP_VCXO_CTL_MISC_AVD_DIV_VCORNG_MASK                     0x03000000
#define BCHP_VCXO_CTL_MISC_AVD_DIV_VCORNG_SHIFT                    24

/* VCXO_CTL_MISC :: AVD_DIV :: reserved1 [23:17] */
#define BCHP_VCXO_CTL_MISC_AVD_DIV_reserved1_MASK                  0x00fe0000
#define BCHP_VCXO_CTL_MISC_AVD_DIV_reserved1_SHIFT                 17

/* VCXO_CTL_MISC :: AVD_DIV :: NDIV_INT [16:08] */
#define BCHP_VCXO_CTL_MISC_AVD_DIV_NDIV_INT_MASK                   0x0001ff00
#define BCHP_VCXO_CTL_MISC_AVD_DIV_NDIV_INT_SHIFT                  8

/* VCXO_CTL_MISC :: AVD_DIV :: M1DIV [07:00] */
#define BCHP_VCXO_CTL_MISC_AVD_DIV_M1DIV_MASK                      0x000000ff
#define BCHP_VCXO_CTL_MISC_AVD_DIV_M1DIV_SHIFT                     0

/***************************************************************************
 *EREF_DIV - EREF PLL divider settings
 ***************************************************************************/
/* VCXO_CTL_MISC :: EREF_DIV :: reserved0 [31:24] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved0_MASK                 0xff000000
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved0_SHIFT                24

/* VCXO_CTL_MISC :: EREF_DIV :: M5DIV [23:16] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M5DIV_MASK                     0x00ff0000
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M5DIV_SHIFT                    16

/* VCXO_CTL_MISC :: EREF_DIV :: reserved1 [15:12] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved1_MASK                 0x0000f000
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved1_SHIFT                12

/* VCXO_CTL_MISC :: EREF_DIV :: M3DIV [11:08] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M3DIV_MASK                     0x00000f00
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M3DIV_SHIFT                    8

/* VCXO_CTL_MISC :: EREF_DIV :: reserved2 [07:04] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved2_MASK                 0x000000f0
#define BCHP_VCXO_CTL_MISC_EREF_DIV_reserved2_SHIFT                4

/* VCXO_CTL_MISC :: EREF_DIV :: M2DIV [03:00] */
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M2DIV_MASK                     0x0000000f
#define BCHP_VCXO_CTL_MISC_EREF_DIV_M2DIV_SHIFT                    0

/***************************************************************************
 *AUDDSP_DIV - Audio DSP PLL divider settings
 ***************************************************************************/
/* VCXO_CTL_MISC :: AUDDSP_DIV :: reserved0 [31:26] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_reserved0_MASK               0xfc000000
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_reserved0_SHIFT              26

/* VCXO_CTL_MISC :: AUDDSP_DIV :: VCORNG [25:24] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_VCORNG_MASK                  0x03000000
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_VCORNG_SHIFT                 24

/* VCXO_CTL_MISC :: AUDDSP_DIV :: reserved1 [23:17] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_reserved1_MASK               0x00fe0000
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_reserved1_SHIFT              17

/* VCXO_CTL_MISC :: AUDDSP_DIV :: NDIV_INT [16:08] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_NDIV_INT_MASK                0x0001ff00
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_NDIV_INT_SHIFT               8

/* VCXO_CTL_MISC :: AUDDSP_DIV :: M1DIV [07:00] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_M1DIV_MASK                   0x000000ff
#define BCHP_VCXO_CTL_MISC_AUDDSP_DIV_M1DIV_SHIFT                  0

/***************************************************************************
 *LOCK_CNTR_RESET - VCXO Lock Counter Reset
 ***************************************************************************/
/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: reserved0 [31:07] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_reserved0_MASK          0xffffff80
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_reserved0_SHIFT         7

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: AUDDSP [06:06] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AUDDSP_MASK             0x00000040
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AUDDSP_SHIFT            6

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: reserved1 [05:05] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_reserved1_MASK          0x00000020
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_reserved1_SHIFT         5

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: EREF [04:04] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_EREF_MASK               0x00000010
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_EREF_SHIFT              4

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: AC1 [03:03] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AC1_MASK                0x00000008
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AC1_SHIFT               3

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: AC0 [02:02] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AC0_MASK                0x00000004
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AC0_SHIFT               2

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: AVD [01:01] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AVD_MASK                0x00000002
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_AVD_SHIFT               1

/* VCXO_CTL_MISC :: LOCK_CNTR_RESET :: VC0 [00:00] */
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_VC0_MASK                0x00000001
#define BCHP_VCXO_CTL_MISC_LOCK_CNTR_RESET_VC0_SHIFT               0

/***************************************************************************
 *VC0_LOCK_CNT - VCXO 0 Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: VC0_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_VC0_LOCK_CNT_reserved0_MASK             0xfffff000
#define BCHP_VCXO_CTL_MISC_VC0_LOCK_CNT_reserved0_SHIFT            12

/* VCXO_CTL_MISC :: VC0_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_VC0_LOCK_CNT_COUNT_MASK                 0x00000fff
#define BCHP_VCXO_CTL_MISC_VC0_LOCK_CNT_COUNT_SHIFT                0

/***************************************************************************
 *AC0_LOCK_CNT - Audio PLL 0 Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: AC0_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_AC0_LOCK_CNT_reserved0_MASK             0xfffff000
#define BCHP_VCXO_CTL_MISC_AC0_LOCK_CNT_reserved0_SHIFT            12

/* VCXO_CTL_MISC :: AC0_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_AC0_LOCK_CNT_COUNT_MASK                 0x00000fff
#define BCHP_VCXO_CTL_MISC_AC0_LOCK_CNT_COUNT_SHIFT                0

/***************************************************************************
 *AC1_LOCK_CNT - Audio PLL 1 Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: AC1_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_AC1_LOCK_CNT_reserved0_MASK             0xfffff000
#define BCHP_VCXO_CTL_MISC_AC1_LOCK_CNT_reserved0_SHIFT            12

/* VCXO_CTL_MISC :: AC1_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_AC1_LOCK_CNT_COUNT_MASK                 0x00000fff
#define BCHP_VCXO_CTL_MISC_AC1_LOCK_CNT_COUNT_SHIFT                0

/***************************************************************************
 *EREF_LOCK_CNT - EREF PLL Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: EREF_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_EREF_LOCK_CNT_reserved0_MASK            0xfffff000
#define BCHP_VCXO_CTL_MISC_EREF_LOCK_CNT_reserved0_SHIFT           12

/* VCXO_CTL_MISC :: EREF_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_EREF_LOCK_CNT_COUNT_MASK                0x00000fff
#define BCHP_VCXO_CTL_MISC_EREF_LOCK_CNT_COUNT_SHIFT               0

/***************************************************************************
 *AUDDSP_LOCK_CNT - Audio DSP PLL Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: AUDDSP_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_LOCK_CNT_reserved0_MASK          0xfffff000
#define BCHP_VCXO_CTL_MISC_AUDDSP_LOCK_CNT_reserved0_SHIFT         12

/* VCXO_CTL_MISC :: AUDDSP_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_AUDDSP_LOCK_CNT_COUNT_MASK              0x00000fff
#define BCHP_VCXO_CTL_MISC_AUDDSP_LOCK_CNT_COUNT_SHIFT             0

/***************************************************************************
 *AVD_LOCK_CNT - AVD PLL Lock Counter
 ***************************************************************************/
/* VCXO_CTL_MISC :: AVD_LOCK_CNT :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_AVD_LOCK_CNT_reserved0_MASK             0xfffff000
#define BCHP_VCXO_CTL_MISC_AVD_LOCK_CNT_reserved0_SHIFT            12

/* VCXO_CTL_MISC :: AVD_LOCK_CNT :: COUNT [11:00] */
#define BCHP_VCXO_CTL_MISC_AVD_LOCK_CNT_COUNT_MASK                 0x00000fff
#define BCHP_VCXO_CTL_MISC_AVD_LOCK_CNT_COUNT_SHIFT                0

/***************************************************************************
 *TEST_SEL - VCXO core test select
 ***************************************************************************/
/* VCXO_CTL_MISC :: TEST_SEL :: reserved0 [31:12] */
#define BCHP_VCXO_CTL_MISC_TEST_SEL_reserved0_MASK                 0xfffff000
#define BCHP_VCXO_CTL_MISC_TEST_SEL_reserved0_SHIFT                12

/* VCXO_CTL_MISC :: TEST_SEL :: reserved_for_eco1 [11:08] */
#define BCHP_VCXO_CTL_MISC_TEST_SEL_reserved_for_eco1_MASK         0x00000f00
#define BCHP_VCXO_CTL_MISC_TEST_SEL_reserved_for_eco1_SHIFT        8

/* VCXO_CTL_MISC :: TEST_SEL :: PLL_SEL [07:04] */
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_MASK                   0x000000f0
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_SHIFT                  4
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_Reserved_3             15
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_Reserved_2             14
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_Reserved_1             13
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_Reserved_0             12
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_SDS1_PLL               11
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_SDS0_PLL               10
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_EREF_PLL               9
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_AC1_PLL                8
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_AC0_PLL                7
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_RAPDSP_PLL             6
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_AVD_PLL                5
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_VC0_PLL                4
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_MIPS_PLL               3
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_SYSTEM_PLL1            2
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_SYSTEM_PLL0            1
#define BCHP_VCXO_CTL_MISC_TEST_SEL_PLL_SEL_None                   0

/* VCXO_CTL_MISC :: TEST_SEL :: SUB_SEL [03:00] */
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_MASK                   0x0000000f
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_SHIFT                  0
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_VCO_Vcontrol           0
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_VCO_divid_BY_8_clock   1
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_frefi                  2
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_fdbki                  3
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_watchdog_timer_reset_output 4
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout1                5
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout2                6
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout3                7
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout4                8
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout5                9
#define BCHP_VCXO_CTL_MISC_TEST_SEL_SUB_SEL_clkout6                10

#endif /* #ifndef BCHP_VCXO_CTL_MISC_H__ */

/* End of File */