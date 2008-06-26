/***************************************************************************
 *     Copyright (c) 1999-2008, Broadcom Corporation
 *     All Rights Reserved
 *     Confidential Property of Broadcom Corporation
 *
 *
 * THIS SOFTWARE MAY ONLY BE USED SUBJECT TO AN EXECUTED SOFTWARE LICENSE
 * AGREEMENT  BETWEEN THE USER AND BROADCOM.  YOU HAVE NO RIGHT TO USE OR
 * EXPLOIT THIS MATERIAL EXCEPT SUBJECT TO THE TERMS OF SUCH AN AGREEMENT.
 *
 * $brcm_Workfile: bchp_usb_ctrl.h $
 * $brcm_Revision: Hydra_Software_Devel/1 $
 * $brcm_Date: 1/15/08 4:23p $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Mon Jan 14 21:34:11 2008
 *                 MD5 Checksum         b0e71c6886be9568c9ec2c69d66ac41e
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008008
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/3548/rdb/a0/bchp_usb_ctrl.h $
 * 
 * Hydra_Software_Devel/1   1/15/08 4:23p maivu
 * PR 38573: Initial CHP files
 *
 ***************************************************************************/

#ifndef BCHP_USB_CTRL_H__
#define BCHP_USB_CTRL_H__

/***************************************************************************
 *USB_CTRL - USB Control Registers
 ***************************************************************************/
#define BCHP_USB_CTRL_BRT_CTL_1                  0x00780200 /* BERT Control 1 Register */
#define BCHP_USB_CTRL_BRT_CTL_2                  0x00780204 /* BERT Control 2 Register */
#define BCHP_USB_CTRL_BRT_STAT_1                 0x00780208 /* BERT Status 1 Register */
#define BCHP_USB_CTRL_BRT_STAT_2                 0x0078020c /* BERT Status 2 Register */
#define BCHP_USB_CTRL_UTMI_CTL_1                 0x00780210 /* UTMI Control Register */
#define BCHP_USB_CTRL_TEST_PORT_CTL              0x00780214 /* Test Port Control Register */
#define BCHP_USB_CTRL_PLL_CTL_1                  0x00780218 /* PLL Control Register */
#define BCHP_USB_CTRL_EBRIDGE                    0x0078021c /* Control Register for EHCI Bridge */
#define BCHP_USB_CTRL_OBRIDGE                    0x00780220 /* Control Register for OHCI Bridge */
#define BCHP_USB_CTRL_FLADJ_VALUE                0x00780224 /* Frame Adjust Value */
#define BCHP_USB_CTRL_SETUP                      0x00780228 /* Setup Register */
#define BCHP_USB_CTRL_MDIO                       0x0078022c /* MDIO Interface Programming Register */
#define BCHP_USB_CTRL_MDIO2                      0x00780230 /* MDIO Interface Read Register */
#define BCHP_USB_CTRL_USB_SIMCTL                 0x00780234 /* Simulation Register */
#define BCHP_USB_CTRL_SPARE1                     0x00780238 /* Spare1 Register for future use */
#define BCHP_USB_CTRL_SPARE2                     0x0078023c /* Spare2 Register for future use */

/***************************************************************************
 *BRT_CTL_1 - BERT Control 1 Register
 ***************************************************************************/
/* USB_CTRL :: BRT_CTL_1 :: BRT_PKT_SIZE [31:16] */
#define BCHP_USB_CTRL_BRT_CTL_1_BRT_PKT_SIZE_MASK                  0xffff0000
#define BCHP_USB_CTRL_BRT_CTL_1_BRT_PKT_SIZE_SHIFT                 16

/* USB_CTRL :: BRT_CTL_1 :: BRT_PKT_CNT [15:08] */
#define BCHP_USB_CTRL_BRT_CTL_1_BRT_PKT_CNT_MASK                   0x0000ff00
#define BCHP_USB_CTRL_BRT_CTL_1_BRT_PKT_CNT_SHIFT                  8

/* USB_CTRL :: BRT_CTL_1 :: PORT_SEL_TX [07:04] */
#define BCHP_USB_CTRL_BRT_CTL_1_PORT_SEL_TX_MASK                   0x000000f0
#define BCHP_USB_CTRL_BRT_CTL_1_PORT_SEL_TX_SHIFT                  4

/* USB_CTRL :: BRT_CTL_1 :: PORT_SEL_RX [03:00] */
#define BCHP_USB_CTRL_BRT_CTL_1_PORT_SEL_RX_MASK                   0x0000000f
#define BCHP_USB_CTRL_BRT_CTL_1_PORT_SEL_RX_SHIFT                  0

/***************************************************************************
 *BRT_CTL_2 - BERT Control 2 Register
 ***************************************************************************/
/* USB_CTRL :: BRT_CTL_2 :: BRT2_SPARE [31:24] */
#define BCHP_USB_CTRL_BRT_CTL_2_BRT2_SPARE_MASK                    0xff000000
#define BCHP_USB_CTRL_BRT_CTL_2_BRT2_SPARE_SHIFT                   24

/* USB_CTRL :: BRT_CTL_2 :: BRT_PATTERN [23:16] */
#define BCHP_USB_CTRL_BRT_CTL_2_BRT_PATTERN_MASK                   0x00ff0000
#define BCHP_USB_CTRL_BRT_CTL_2_BRT_PATTERN_SHIFT                  16

/* USB_CTRL :: BRT_CTL_2 :: START [15:15] */
#define BCHP_USB_CTRL_BRT_CTL_2_START_MASK                         0x00008000
#define BCHP_USB_CTRL_BRT_CTL_2_START_SHIFT                        15

/* USB_CTRL :: BRT_CTL_2 :: BERT_SOFT_RESETB [14:14] */
#define BCHP_USB_CTRL_BRT_CTL_2_BERT_SOFT_RESETB_MASK              0x00004000
#define BCHP_USB_CTRL_BRT_CTL_2_BERT_SOFT_RESETB_SHIFT             14

/* USB_CTRL :: BRT_CTL_2 :: CFG_VALID [13:13] */
#define BCHP_USB_CTRL_BRT_CTL_2_CFG_VALID_MASK                     0x00002000
#define BCHP_USB_CTRL_BRT_CTL_2_CFG_VALID_SHIFT                    13

/* USB_CTRL :: BRT_CTL_2 :: XCVER_OWNER [12:12] */
#define BCHP_USB_CTRL_BRT_CTL_2_XCVER_OWNER_MASK                   0x00001000
#define BCHP_USB_CTRL_BRT_CTL_2_XCVER_OWNER_SHIFT                  12

/* USB_CTRL :: BRT_CTL_2 :: LOOP_MODE [11:10] */
#define BCHP_USB_CTRL_BRT_CTL_2_LOOP_MODE_MASK                     0x00000c00
#define BCHP_USB_CTRL_BRT_CTL_2_LOOP_MODE_SHIFT                    10

/* USB_CTRL :: BRT_CTL_2 :: OPMODE [09:08] */
#define BCHP_USB_CTRL_BRT_CTL_2_OPMODE_MASK                        0x00000300
#define BCHP_USB_CTRL_BRT_CTL_2_OPMODE_SHIFT                       8

/* USB_CTRL :: BRT_CTL_2 :: TERM_SEL [07:06] */
#define BCHP_USB_CTRL_BRT_CTL_2_TERM_SEL_MASK                      0x000000c0
#define BCHP_USB_CTRL_BRT_CTL_2_TERM_SEL_SHIFT                     6

/* USB_CTRL :: BRT_CTL_2 :: XCVER_SEL [05:04] */
#define BCHP_USB_CTRL_BRT_CTL_2_XCVER_SEL_MASK                     0x00000030
#define BCHP_USB_CTRL_BRT_CTL_2_XCVER_SEL_SHIFT                    4

/* USB_CTRL :: BRT_CTL_2 :: TEST_SEL [03:00] */
#define BCHP_USB_CTRL_BRT_CTL_2_TEST_SEL_MASK                      0x0000000f
#define BCHP_USB_CTRL_BRT_CTL_2_TEST_SEL_SHIFT                     0

/***************************************************************************
 *BRT_STAT_1 - BERT Status 1 Register
 ***************************************************************************/
/* USB_CTRL :: BRT_STAT_1 :: BRT_TX_STATE [31:28] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_TX_STATE_MASK                 0xf0000000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_TX_STATE_SHIFT                28

/* USB_CTRL :: BRT_STAT_1 :: BRT_RX_STATE [27:24] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_RX_STATE_MASK                 0x0f000000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_RX_STATE_SHIFT                24

/* USB_CTRL :: BRT_STAT_1 :: BRT_TEST_SEL [23:20] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_TEST_SEL_MASK                 0x00f00000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_TEST_SEL_SHIFT                20

/* USB_CTRL :: BRT_STAT_1 :: BRT_RX_COMP [19:19] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_RX_COMP_MASK                  0x00080000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_RX_COMP_SHIFT                 19

/* USB_CTRL :: BRT_STAT_1 :: BRT_START_RCVD [18:18] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_START_RCVD_MASK               0x00040000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_START_RCVD_SHIFT              18

/* USB_CTRL :: BRT_STAT_1 :: BRT_BUSY_TX [17:17] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_BUSY_TX_MASK                  0x00020000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_BUSY_TX_SHIFT                 17

/* USB_CTRL :: BRT_STAT_1 :: BRT_BUSY_RX [16:16] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_BUSY_RX_MASK                  0x00010000
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_BUSY_RX_SHIFT                 16

/* USB_CTRL :: BRT_STAT_1 :: BRT_ERROR_CNT [15:00] */
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_ERROR_CNT_MASK                0x0000ffff
#define BCHP_USB_CTRL_BRT_STAT_1_BRT_ERROR_CNT_SHIFT               0

/***************************************************************************
 *BRT_STAT_2 - BERT Status 2 Register
 ***************************************************************************/
/* USB_CTRL :: BRT_STAT_2 :: PHY_ID [31:25] */
#define BCHP_USB_CTRL_BRT_STAT_2_PHY_ID_MASK                       0xfe000000
#define BCHP_USB_CTRL_BRT_STAT_2_PHY_ID_SHIFT                      25

/* USB_CTRL :: BRT_STAT_2 :: PLL_LOCK [24:24] */
#define BCHP_USB_CTRL_BRT_STAT_2_PLL_LOCK_MASK                     0x01000000
#define BCHP_USB_CTRL_BRT_STAT_2_PLL_LOCK_SHIFT                    24

/* USB_CTRL :: BRT_STAT_2 :: BRT_RX_PKT_CNT [23:16] */
#define BCHP_USB_CTRL_BRT_STAT_2_BRT_RX_PKT_CNT_MASK               0x00ff0000
#define BCHP_USB_CTRL_BRT_STAT_2_BRT_RX_PKT_CNT_SHIFT              16

/* USB_CTRL :: BRT_STAT_2 :: BRT_RX_BYTE_CNT [15:00] */
#define BCHP_USB_CTRL_BRT_STAT_2_BRT_RX_BYTE_CNT_MASK              0x0000ffff
#define BCHP_USB_CTRL_BRT_STAT_2_BRT_RX_BYTE_CNT_SHIFT             0

/***************************************************************************
 *UTMI_CTL_1 - UTMI Control Register
 ***************************************************************************/
/* USB_CTRL :: UTMI_CTL_1 :: PHY_PWDNB [31:30] */
#define BCHP_USB_CTRL_UTMI_CTL_1_PHY_PWDNB_MASK                    0xc0000000
#define BCHP_USB_CTRL_UTMI_CTL_1_PHY_PWDNB_SHIFT                   30

/* USB_CTRL :: UTMI_CTL_1 :: UTMI_PWDNB [29:28] */
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_PWDNB_MASK                   0x30000000
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_PWDNB_SHIFT                  28

/* USB_CTRL :: UTMI_CTL_1 :: UTMI_SOFT_RESETB [27:26] */
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_SOFT_RESETB_MASK             0x0c000000
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_SOFT_RESETB_SHIFT            26

/* USB_CTRL :: UTMI_CTL_1 :: PHY1_PWDNB [25:25] */
#define BCHP_USB_CTRL_UTMI_CTL_1_PHY1_PWDNB_MASK                   0x02000000
#define BCHP_USB_CTRL_UTMI_CTL_1_PHY1_PWDNB_SHIFT                  25

/* USB_CTRL :: UTMI_CTL_1 :: UTMI1_PWDNB [24:24] */
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI1_PWDNB_MASK                  0x01000000
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI1_PWDNB_SHIFT                 24

/* USB_CTRL :: UTMI_CTL_1 :: UTMI1_SOFT_RESETB [23:23] */
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI1_SOFT_RESETB_MASK            0x00800000
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI1_SOFT_RESETB_SHIFT           23

/* USB_CTRL :: UTMI_CTL_1 :: DISCON_PHY [22:21] */
#define BCHP_USB_CTRL_UTMI_CTL_1_DISCON_PHY_MASK                   0x00600000
#define BCHP_USB_CTRL_UTMI_CTL_1_DISCON_PHY_SHIFT                  21

/* USB_CTRL :: UTMI_CTL_1 :: TX_PHASE [20:20] */
#define BCHP_USB_CTRL_UTMI_CTL_1_TX_PHASE_MASK                     0x00100000
#define BCHP_USB_CTRL_UTMI_CTL_1_TX_PHASE_SHIFT                    20

/* USB_CTRL :: UTMI_CTL_1 :: CHIRP_RX [19:19] */
#define BCHP_USB_CTRL_UTMI_CTL_1_CHIRP_RX_MASK                     0x00080000
#define BCHP_USB_CTRL_UTMI_CTL_1_CHIRP_RX_SHIFT                    19

/* USB_CTRL :: UTMI_CTL_1 :: SYNC_DET_LENG [18:16] */
#define BCHP_USB_CTRL_UTMI_CTL_1_SYNC_DET_LENG_MASK                0x00070000
#define BCHP_USB_CTRL_UTMI_CTL_1_SYNC_DET_LENG_SHIFT               16

/* USB_CTRL :: UTMI_CTL_1 :: AFE_NON_DRIVING [15:12] */
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_NON_DRIVING_MASK              0x0000f000
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_NON_DRIVING_SHIFT             12

/* USB_CTRL :: UTMI_CTL_1 :: AFE_CHRPTEN1 [11:11] */
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_CHRPTEN1_MASK                 0x00000800
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_CHRPTEN1_SHIFT                11

/* USB_CTRL :: UTMI_CTL_1 :: AFE_LPBACK [10:10] */
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_LPBACK_MASK                   0x00000400
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_LPBACK_SHIFT                  10

/* USB_CTRL :: UTMI_CTL_1 :: AFE_CDRCKEN [09:09] */
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_CDRCKEN_MASK                  0x00000200
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_CDRCKEN_SHIFT                 9

/* USB_CTRL :: UTMI_CTL_1 :: CLK_60_INVERT [08:08] */
#define BCHP_USB_CTRL_UTMI_CTL_1_CLK_60_INVERT_MASK                0x00000100
#define BCHP_USB_CTRL_UTMI_CTL_1_CLK_60_INVERT_SHIFT               8

/* USB_CTRL :: UTMI_CTL_1 :: HS_CURRENT [07:07] */
#define BCHP_USB_CTRL_UTMI_CTL_1_HS_CURRENT_MASK                   0x00000080
#define BCHP_USB_CTRL_UTMI_CTL_1_HS_CURRENT_SHIFT                  7

/* USB_CTRL :: UTMI_CTL_1 :: UTMI_LOOPBACK_EN [06:05] */
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_LOOPBACK_EN_MASK             0x00000060
#define BCHP_USB_CTRL_UTMI_CTL_1_UTMI_LOOPBACK_EN_SHIFT            5

/* USB_CTRL :: UTMI_CTL_1 :: AFE_RXLOGICR [04:04] */
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_RXLOGICR_MASK                 0x00000010
#define BCHP_USB_CTRL_UTMI_CTL_1_AFE_RXLOGICR_SHIFT                4

/* USB_CTRL :: UTMI_CTL_1 :: IOST [03:02] */
#define BCHP_USB_CTRL_UTMI_CTL_1_IOST_MASK                         0x0000000c
#define BCHP_USB_CTRL_UTMI_CTL_1_IOST_SHIFT                        2

/* USB_CTRL :: UTMI_CTL_1 :: HOSTB_DEV [01:00] */
#define BCHP_USB_CTRL_UTMI_CTL_1_HOSTB_DEV_MASK                    0x00000003
#define BCHP_USB_CTRL_UTMI_CTL_1_HOSTB_DEV_SHIFT                   0

/***************************************************************************
 *TEST_PORT_CTL - Test Port Control Register
 ***************************************************************************/
/* USB_CTRL :: TEST_PORT_CTL :: TPCTL_SPARE4 [31:31] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE4_MASK              0x80000000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE4_SHIFT             31

/* USB_CTRL :: TEST_PORT_CTL :: TPOUT_SEL [30:24] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPOUT_SEL_MASK                 0x7f000000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPOUT_SEL_SHIFT                24

/* USB_CTRL :: TEST_PORT_CTL :: TP_EN [23:23] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_EN_MASK                     0x00800000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_EN_SHIFT                    23

/* USB_CTRL :: TEST_PORT_CTL :: TPCTL_SPARE3 [22:20] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE3_MASK              0x00700000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE3_SHIFT             20

/* USB_CTRL :: TEST_PORT_CTL :: TP_PHY_SEL [19:16] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_PHY_SEL_MASK                0x000f0000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_PHY_SEL_SHIFT               16

/* USB_CTRL :: TEST_PORT_CTL :: TPCTL_SPARE2 [15:12] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE2_MASK              0x0000f000
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE2_SHIFT             12

/* USB_CTRL :: TEST_PORT_CTL :: TP_PORT_SEL [11:08] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_PORT_SEL_MASK               0x00000f00
#define BCHP_USB_CTRL_TEST_PORT_CTL_TP_PORT_SEL_SHIFT              8

/* USB_CTRL :: TEST_PORT_CTL :: TPCTL_SPARE1 [07:05] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE1_MASK              0x000000e0
#define BCHP_USB_CTRL_TEST_PORT_CTL_TPCTL_SPARE1_SHIFT             5

/* USB_CTRL :: TEST_PORT_CTL :: TEST_MUX_SEL [04:00] */
#define BCHP_USB_CTRL_TEST_PORT_CTL_TEST_MUX_SEL_MASK              0x0000001f
#define BCHP_USB_CTRL_TEST_PORT_CTL_TEST_MUX_SEL_SHIFT             0

/***************************************************************************
 *PLL_CTL_1 - PLL Control Register
 ***************************************************************************/
/* USB_CTRL :: PLL_CTL_1 :: PLLCTL_SPARE [31:10] */
#define BCHP_USB_CTRL_PLL_CTL_1_PLLCTL_SPARE_MASK                  0xfffffc00
#define BCHP_USB_CTRL_PLL_CTL_1_PLLCTL_SPARE_SHIFT                 10

/* USB_CTRL :: PLL_CTL_1 :: PLL_RESET [09:09] */
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_RESET_MASK                     0x00000200
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_RESET_SHIFT                    9

/* USB_CTRL :: PLL_CTL_1 :: PHYPLLBYP [08:08] */
#define BCHP_USB_CTRL_PLL_CTL_1_PHYPLLBYP_MASK                     0x00000100
#define BCHP_USB_CTRL_PLL_CTL_1_PHYPLLBYP_SHIFT                    8

/* USB_CTRL :: PLL_CTL_1 :: CLKSEL [07:06] */
#define BCHP_USB_CTRL_PLL_CTL_1_CLKSEL_MASK                        0x000000c0
#define BCHP_USB_CTRL_PLL_CTL_1_CLKSEL_SHIFT                       6

/* USB_CTRL :: PLL_CTL_1 :: PLL_SUSPEND_EN [05:05] */
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_SUSPEND_EN_MASK                0x00000020
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_SUSPEND_EN_SHIFT               5

/* USB_CTRL :: PLL_CTL_1 :: PLL_CALEN [04:04] */
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_CALEN_MASK                     0x00000010
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_CALEN_SHIFT                    4

/* USB_CTRL :: PLL_CTL_1 :: PLL_PWRDWNB [03:03] */
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_PWRDWNB_MASK                   0x00000008
#define BCHP_USB_CTRL_PLL_CTL_1_PLL_PWRDWNB_SHIFT                  3

/* USB_CTRL :: PLL_CTL_1 :: XTAL_PWRDWNB [02:02] */
#define BCHP_USB_CTRL_PLL_CTL_1_XTAL_PWRDWNB_MASK                  0x00000004
#define BCHP_USB_CTRL_PLL_CTL_1_XTAL_PWRDWNB_SHIFT                 2

/* USB_CTRL :: PLL_CTL_1 :: REFCLKSEL [01:00] */
#define BCHP_USB_CTRL_PLL_CTL_1_REFCLKSEL_MASK                     0x00000003
#define BCHP_USB_CTRL_PLL_CTL_1_REFCLKSEL_SHIFT                    0

/***************************************************************************
 *EBRIDGE - Control Register for EHCI Bridge
 ***************************************************************************/
/* USB_CTRL :: EBRIDGE :: EBRIDGE_SPARE [31:17] */
#define BCHP_USB_CTRL_EBRIDGE_EBRIDGE_SPARE_MASK                   0xfffe0000
#define BCHP_USB_CTRL_EBRIDGE_EBRIDGE_SPARE_SHIFT                  17

/* USB_CTRL :: EBRIDGE :: EBR_RD_THRESH [16:12] */
#define BCHP_USB_CTRL_EBRIDGE_EBR_RD_THRESH_MASK                   0x0001f000
#define BCHP_USB_CTRL_EBRIDGE_EBR_RD_THRESH_SHIFT                  12

/* USB_CTRL :: EBRIDGE :: EBR_SCB_SIZE [11:07] */
#define BCHP_USB_CTRL_EBRIDGE_EBR_SCB_SIZE_MASK                    0x00000f80
#define BCHP_USB_CTRL_EBRIDGE_EBR_SCB_SIZE_SHIFT                   7

/* USB_CTRL :: EBRIDGE :: EBR_MISC [06:01] */
#define BCHP_USB_CTRL_EBRIDGE_EBR_MISC_MASK                        0x0000007e
#define BCHP_USB_CTRL_EBRIDGE_EBR_MISC_SHIFT                       1

/* USB_CTRL :: EBRIDGE :: EBR_SEQ_EN [00:00] */
#define BCHP_USB_CTRL_EBRIDGE_EBR_SEQ_EN_MASK                      0x00000001
#define BCHP_USB_CTRL_EBRIDGE_EBR_SEQ_EN_SHIFT                     0

/***************************************************************************
 *OBRIDGE - Control Register for OHCI Bridge
 ***************************************************************************/
/* USB_CTRL :: OBRIDGE :: OBRIDGE_SPARE [31:17] */
#define BCHP_USB_CTRL_OBRIDGE_OBRIDGE_SPARE_MASK                   0xfffe0000
#define BCHP_USB_CTRL_OBRIDGE_OBRIDGE_SPARE_SHIFT                  17

/* USB_CTRL :: OBRIDGE :: OBR_RD_THRESH [16:12] */
#define BCHP_USB_CTRL_OBRIDGE_OBR_RD_THRESH_MASK                   0x0001f000
#define BCHP_USB_CTRL_OBRIDGE_OBR_RD_THRESH_SHIFT                  12

/* USB_CTRL :: OBRIDGE :: OBR_SCB_SIZE [11:07] */
#define BCHP_USB_CTRL_OBRIDGE_OBR_SCB_SIZE_MASK                    0x00000f80
#define BCHP_USB_CTRL_OBRIDGE_OBR_SCB_SIZE_SHIFT                   7

/* USB_CTRL :: OBRIDGE :: OBR_MISC [06:01] */
#define BCHP_USB_CTRL_OBRIDGE_OBR_MISC_MASK                        0x0000007e
#define BCHP_USB_CTRL_OBRIDGE_OBR_MISC_SHIFT                       1

/* USB_CTRL :: OBRIDGE :: OBR_SEQ_EN [00:00] */
#define BCHP_USB_CTRL_OBRIDGE_OBR_SEQ_EN_MASK                      0x00000001
#define BCHP_USB_CTRL_OBRIDGE_OBR_SEQ_EN_SHIFT                     0

/***************************************************************************
 *FLADJ_VALUE - Frame Adjust Value
 ***************************************************************************/
/* USB_CTRL :: FLADJ_VALUE :: FLADJ_VAL [31:00] */
#define BCHP_USB_CTRL_FLADJ_VALUE_FLADJ_VAL_MASK                   0xffffffff
#define BCHP_USB_CTRL_FLADJ_VALUE_FLADJ_VAL_SHIFT                  0

/***************************************************************************
 *SETUP - Setup Register
 ***************************************************************************/
/* USB_CTRL :: SETUP :: async_expire_dis [31:31] */
#define BCHP_USB_CTRL_SETUP_async_expire_dis_MASK                  0x80000000
#define BCHP_USB_CTRL_SETUP_async_expire_dis_SHIFT                 31

/* USB_CTRL :: SETUP :: SETUP_SPARE4 [30:28] */
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE4_MASK                      0x70000000
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE4_SHIFT                     28

/* USB_CTRL :: SETUP :: OC_DISABLE [27:25] */
#define BCHP_USB_CTRL_SETUP_OC_DISABLE_MASK                        0x0e000000
#define BCHP_USB_CTRL_SETUP_OC_DISABLE_SHIFT                       25

/* USB_CTRL :: SETUP :: mdio_sm_sel [24:24] */
#define BCHP_USB_CTRL_SETUP_mdio_sm_sel_MASK                       0x01000000
#define BCHP_USB_CTRL_SETUP_mdio_sm_sel_SHIFT                      24

/* USB_CTRL :: SETUP :: SETUP_SPARE2 [23:23] */
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE2_MASK                      0x00800000
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE2_SHIFT                     23

/* USB_CTRL :: SETUP :: mdio_test_en [22:22] */
#define BCHP_USB_CTRL_SETUP_mdio_test_en_MASK                      0x00400000
#define BCHP_USB_CTRL_SETUP_mdio_test_en_SHIFT                     22

/* USB_CTRL :: SETUP :: byte_read_en [21:21] */
#define BCHP_USB_CTRL_SETUP_byte_read_en_MASK                      0x00200000
#define BCHP_USB_CTRL_SETUP_byte_read_en_SHIFT                     21

/* USB_CTRL :: SETUP :: SETUP_SPARE1 [20:12] */
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE1_MASK                      0x001ff000
#define BCHP_USB_CTRL_SETUP_SETUP_SPARE1_SHIFT                     12

/* USB_CTRL :: SETUP :: wrgwordcnt_sel [11:11] */
#define BCHP_USB_CTRL_SETUP_wrgwordcnt_sel_MASK                    0x00000800
#define BCHP_USB_CTRL_SETUP_wrgwordcnt_sel_SHIFT                   11

/* USB_CTRL :: SETUP :: rdgwordcnt_sel [10:10] */
#define BCHP_USB_CTRL_SETUP_rdgwordcnt_sel_MASK                    0x00000400
#define BCHP_USB_CTRL_SETUP_rdgwordcnt_sel_SHIFT                   10

/* USB_CTRL :: SETUP :: soft_reset [09:09] */
#define BCHP_USB_CTRL_SETUP_soft_reset_MASK                        0x00000200
#define BCHP_USB_CTRL_SETUP_soft_reset_SHIFT                       9

/* USB_CTRL :: SETUP :: scbff_reset [08:08] */
#define BCHP_USB_CTRL_SETUP_scbff_reset_MASK                       0x00000100
#define BCHP_USB_CTRL_SETUP_scbff_reset_SHIFT                      8

/* USB_CTRL :: SETUP :: PDT2 [07:07] */
#define BCHP_USB_CTRL_SETUP_PDT2_MASK                              0x00000080
#define BCHP_USB_CTRL_SETUP_PDT2_SHIFT                             7

/* USB_CTRL :: SETUP :: PDT1 [06:06] */
#define BCHP_USB_CTRL_SETUP_PDT1_MASK                              0x00000040
#define BCHP_USB_CTRL_SETUP_PDT1_SHIFT                             6

/* USB_CTRL :: SETUP :: IPP [05:05] */
#define BCHP_USB_CTRL_SETUP_IPP_MASK                               0x00000020
#define BCHP_USB_CTRL_SETUP_IPP_SHIFT                              5

/* USB_CTRL :: SETUP :: IOC [04:04] */
#define BCHP_USB_CTRL_SETUP_IOC_MASK                               0x00000010
#define BCHP_USB_CTRL_SETUP_IOC_SHIFT                              4

/* USB_CTRL :: SETUP :: WABO [03:03] */
#define BCHP_USB_CTRL_SETUP_WABO_MASK                              0x00000008
#define BCHP_USB_CTRL_SETUP_WABO_SHIFT                             3

/* USB_CTRL :: SETUP :: FNBO [02:02] */
#define BCHP_USB_CTRL_SETUP_FNBO_MASK                              0x00000004
#define BCHP_USB_CTRL_SETUP_FNBO_SHIFT                             2

/* USB_CTRL :: SETUP :: FNHW [01:01] */
#define BCHP_USB_CTRL_SETUP_FNHW_MASK                              0x00000002
#define BCHP_USB_CTRL_SETUP_FNHW_SHIFT                             1

/* USB_CTRL :: SETUP :: BABO [00:00] */
#define BCHP_USB_CTRL_SETUP_BABO_MASK                              0x00000001
#define BCHP_USB_CTRL_SETUP_BABO_SHIFT                             0

/***************************************************************************
 *MDIO - MDIO Interface Programming Register
 ***************************************************************************/
/* USB_CTRL :: MDIO :: MDIO_SPARE [31:26] */
#define BCHP_USB_CTRL_MDIO_MDIO_SPARE_MASK                         0xfc000000
#define BCHP_USB_CTRL_MDIO_MDIO_SPARE_SHIFT                        26

/* USB_CTRL :: MDIO :: WR_START [25:25] */
#define BCHP_USB_CTRL_MDIO_WR_START_MASK                           0x02000000
#define BCHP_USB_CTRL_MDIO_WR_START_SHIFT                          25

/* USB_CTRL :: MDIO :: RD_START [24:24] */
#define BCHP_USB_CTRL_MDIO_RD_START_MASK                           0x01000000
#define BCHP_USB_CTRL_MDIO_RD_START_SHIFT                          24

/* USB_CTRL :: MDIO :: MDIO_ADDR [23:16] */
#define BCHP_USB_CTRL_MDIO_MDIO_ADDR_MASK                          0x00ff0000
#define BCHP_USB_CTRL_MDIO_MDIO_ADDR_SHIFT                         16

/* USB_CTRL :: MDIO :: MDIO_DATA [15:00] */
#define BCHP_USB_CTRL_MDIO_MDIO_DATA_MASK                          0x0000ffff
#define BCHP_USB_CTRL_MDIO_MDIO_DATA_SHIFT                         0

/***************************************************************************
 *MDIO2 - MDIO Interface Read Register
 ***************************************************************************/
/* USB_CTRL :: MDIO2 :: SYNOPSIS_CORE_ID [31:16] */
#define BCHP_USB_CTRL_MDIO2_SYNOPSIS_CORE_ID_MASK                  0xffff0000
#define BCHP_USB_CTRL_MDIO2_SYNOPSIS_CORE_ID_SHIFT                 16

/* USB_CTRL :: MDIO2 :: MDIO_RD_DATA [15:00] */
#define BCHP_USB_CTRL_MDIO2_MDIO_RD_DATA_MASK                      0x0000ffff
#define BCHP_USB_CTRL_MDIO2_MDIO_RD_DATA_SHIFT                     0

/***************************************************************************
 *USB_SIMCTL - Simulation Register
 ***************************************************************************/
/* USB_CTRL :: USB_SIMCTL :: sim_mode_en [31:31] */
#define BCHP_USB_CTRL_USB_SIMCTL_sim_mode_en_MASK                  0x80000000
#define BCHP_USB_CTRL_USB_SIMCTL_sim_mode_en_SHIFT                 31

/* USB_CTRL :: USB_SIMCTL :: scale_down_en [30:30] */
#define BCHP_USB_CTRL_USB_SIMCTL_scale_down_en_MASK                0x40000000
#define BCHP_USB_CTRL_USB_SIMCTL_scale_down_en_SHIFT               30

/* USB_CTRL :: USB_SIMCTL :: utmi_bkward_en [29:29] */
#define BCHP_USB_CTRL_USB_SIMCTL_utmi_bkward_en_MASK               0x20000000
#define BCHP_USB_CTRL_USB_SIMCTL_utmi_bkward_en_SHIFT              29

/* USB_CTRL :: USB_SIMCTL :: utmi_pls_dis [28:28] */
#define BCHP_USB_CTRL_USB_SIMCTL_utmi_pls_dis_MASK                 0x10000000
#define BCHP_USB_CTRL_USB_SIMCTL_utmi_pls_dis_SHIFT                28

/* USB_CTRL :: USB_SIMCTL :: intr_test [27:27] */
#define BCHP_USB_CTRL_USB_SIMCTL_intr_test_MASK                    0x08000000
#define BCHP_USB_CTRL_USB_SIMCTL_intr_test_SHIFT                   27

/* USB_CTRL :: USB_SIMCTL :: pwrflt1_oe [26:26] */
#define BCHP_USB_CTRL_USB_SIMCTL_pwrflt1_oe_MASK                   0x04000000
#define BCHP_USB_CTRL_USB_SIMCTL_pwrflt1_oe_SHIFT                  26

/* USB_CTRL :: USB_SIMCTL :: pwrflt2_oe [25:25] */
#define BCHP_USB_CTRL_USB_SIMCTL_pwrflt2_oe_MASK                   0x02000000
#define BCHP_USB_CTRL_USB_SIMCTL_pwrflt2_oe_SHIFT                  25

/* USB_CTRL :: USB_SIMCTL :: pwron1_tstsel [24:24] */
#define BCHP_USB_CTRL_USB_SIMCTL_pwron1_tstsel_MASK                0x01000000
#define BCHP_USB_CTRL_USB_SIMCTL_pwron1_tstsel_SHIFT               24

/* USB_CTRL :: USB_SIMCTL :: pwron2_tstsel [23:23] */
#define BCHP_USB_CTRL_USB_SIMCTL_pwron2_tstsel_MASK                0x00800000
#define BCHP_USB_CTRL_USB_SIMCTL_pwron2_tstsel_SHIFT               23

/* USB_CTRL :: USB_SIMCTL :: test_clksel [22:21] */
#define BCHP_USB_CTRL_USB_SIMCTL_test_clksel_MASK                  0x00600000
#define BCHP_USB_CTRL_USB_SIMCTL_test_clksel_SHIFT                 21

/* USB_CTRL :: USB_SIMCTL :: SIMCTL_SPARE [20:17] */
#define BCHP_USB_CTRL_USB_SIMCTL_SIMCTL_SPARE_MASK                 0x001e0000
#define BCHP_USB_CTRL_USB_SIMCTL_SIMCTL_SPARE_SHIFT                17

/* USB_CTRL :: USB_SIMCTL :: AUTOPPD_ON_OVERCUR_EN [16:16] */
#define BCHP_USB_CTRL_USB_SIMCTL_AUTOPPD_ON_OVERCUR_EN_MASK        0x00010000
#define BCHP_USB_CTRL_USB_SIMCTL_AUTOPPD_ON_OVERCUR_EN_SHIFT       16

/* USB_CTRL :: USB_SIMCTL :: TMB_u2 [15:12] */
#define BCHP_USB_CTRL_USB_SIMCTL_TMB_u2_MASK                       0x0000f000
#define BCHP_USB_CTRL_USB_SIMCTL_TMB_u2_SHIFT                      12

/* USB_CTRL :: USB_SIMCTL :: TMB_u1 [11:08] */
#define BCHP_USB_CTRL_USB_SIMCTL_TMB_u1_MASK                       0x00000f00
#define BCHP_USB_CTRL_USB_SIMCTL_TMB_u1_SHIFT                      8

/* USB_CTRL :: USB_SIMCTL :: TMA_u2 [07:04] */
#define BCHP_USB_CTRL_USB_SIMCTL_TMA_u2_MASK                       0x000000f0
#define BCHP_USB_CTRL_USB_SIMCTL_TMA_u2_SHIFT                      4

/* USB_CTRL :: USB_SIMCTL :: TMA_u1 [03:00] */
#define BCHP_USB_CTRL_USB_SIMCTL_TMA_u1_MASK                       0x0000000f
#define BCHP_USB_CTRL_USB_SIMCTL_TMA_u1_SHIFT                      0

/***************************************************************************
 *SPARE1 - Spare1 Register for future use
 ***************************************************************************/
/* USB_CTRL :: SPARE1 :: SPARE1_BITS [31:00] */
#define BCHP_USB_CTRL_SPARE1_SPARE1_BITS_MASK                      0xffffffff
#define BCHP_USB_CTRL_SPARE1_SPARE1_BITS_SHIFT                     0

/***************************************************************************
 *SPARE2 - Spare2 Register for future use
 ***************************************************************************/
/* USB_CTRL :: SPARE2 :: SPARE2_BITS [31:00] */
#define BCHP_USB_CTRL_SPARE2_SPARE2_BITS_MASK                      0xffffffff
#define BCHP_USB_CTRL_SPARE2_SPARE2_BITS_SHIFT                     0

#endif /* #ifndef BCHP_USB_CTRL_H__ */

/* End of File */
