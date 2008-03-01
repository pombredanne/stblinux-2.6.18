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
 * Date:           Generated on         Mon Jul 23 11:58:31 2007
 *                 MD5 Checksum         61f9c4d8dcdcd06017506dddbf23f434
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.008004
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/7400/rdb/d0/bchp_sata_mdio.h $
 * 
 * Hydra_Software_Devel/1   7/23/07 4:07p maivu
 * PR 32842: Initial revision
 *
 ***************************************************************************/

#ifndef BCHP_SATA_MDIO_H__
#define BCHP_SATA_MDIO_H__

/***************************************************************************
 *SATA_MDIO - MDIO Address mapping
 ***************************************************************************/
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL          0x520800 /* MDIO PLL Control Register */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW      0x520801 /* MDIO Freq Synth Control Low */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_HIGH     0x520803 /* MDIO Freq Synth Control High */
#define BCHP_SATA_MDIO_MDIO_FRQ_STATUS           0x520805 /* MDIO Freq Synth Status */
#define BCHP_SATA_MDIO_MDIO_CONTROL              0x520807 /* MDIO Misc Control Register */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL         0x520809 /* MDIO Testbus Control Register */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL             0x52080b /* MDIO Read/Write Port Select Register */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW          0x52080d /* MDIO PORTx Rx Control Low Register */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH         0x52080f /* MDIO PORTx Rx Control High Register */
#define BCHP_SATA_MDIO_MDIO_PORT_TX              0x520811 /* MDIO PORTx Tx Control Register */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL    0x520813 /* MDIO PORTx PRBS Control Register */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS     0x520815 /* MDIO PORTx PRBS Status Register */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL     0x520817 /* MDIO PORTx Digital Control Register */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW      0x520819 /* Ram BIST Status Register Low */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL         0x52081b /* Ram BIST Control Register */
#define BCHP_SATA_MDIO_MDIO_DEV_ID               0x52081d /* Device and Revision ID */

/***************************************************************************
 *MDIO_PLL_CONTROL - MDIO PLL Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_TE [07:07] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TE_MASK                0x80
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TE_SHIFT               7

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_TS [06:06] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TS_MASK                0x40
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TS_SHIFT               6

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_DIV [05:05] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_DIV_MASK               0x20
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_DIV_SHIFT              5

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_BYP_EN [04:04] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_BYP_EN_MASK            0x10
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_BYP_EN_SHIFT           4

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_BYP_CLK [03:03] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_BYP_CLK_MASK           0x08
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_BYP_CLK_SHIFT          3

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_TM [02:02] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TM_MASK                0x04
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_TM_SHIFT               2

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_FR [01:01] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_FR_MASK                0x02
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_FR_SHIFT               1

/* SATA_MDIO :: MDIO_PLL_CONTROL :: PLL_PWR [00:00] */
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_PWR_MASK               0x01
#define BCHP_SATA_MDIO_MDIO_PLL_CONTROL_PLL_PWR_SHIFT              0

/***************************************************************************
 *MDIO_FRQ_CONTROL_LOW - MDIO Freq Synth Control Low
 ***************************************************************************/
/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: AMP [15:12] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_AMP_MASK               0xf000
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_AMP_SHIFT              12

/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: MUX [11:11] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_MUX_MASK               0x0800
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_MUX_SHIFT              11

/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: TS [10:09] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_TS_MASK                0x0600
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_TS_SHIFT               9

/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: TP [08:07] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_TP_MASK                0x0180
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_TP_SHIFT               7

/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: reserved0 [06:05] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_reserved0_MASK         0x0060
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_reserved0_SHIFT        5

/* SATA_MDIO :: MDIO_FRQ_CONTROL_LOW :: BIAS [04:00] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_BIAS_MASK              0x001f
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_LOW_BIAS_SHIFT             0

/***************************************************************************
 *MDIO_FRQ_CONTROL_HIGH - MDIO Freq Synth Control High
 ***************************************************************************/
/* SATA_MDIO :: MDIO_FRQ_CONTROL_HIGH :: FREQ [15:06] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_HIGH_FREQ_MASK             0xffc0
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_HIGH_FREQ_SHIFT            6

/* SATA_MDIO :: MDIO_FRQ_CONTROL_HIGH :: AMP [05:00] */
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_HIGH_AMP_MASK              0x003f
#define BCHP_SATA_MDIO_MDIO_FRQ_CONTROL_HIGH_AMP_SHIFT             0

/***************************************************************************
 *MDIO_FRQ_STATUS - MDIO Freq Synth Status
 ***************************************************************************/
/* SATA_MDIO :: MDIO_FRQ_STATUS :: BIAS [15:00] */
#define BCHP_SATA_MDIO_MDIO_FRQ_STATUS_BIAS_MASK                   0xffff
#define BCHP_SATA_MDIO_MDIO_FRQ_STATUS_BIAS_SHIFT                  0

/***************************************************************************
 *MDIO_CONTROL - MDIO Misc Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_CONTROL :: BYP_PCI_LL [15:15] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_BYP_PCI_LL_MASK                0x8000
#define BCHP_SATA_MDIO_MDIO_CONTROL_BYP_PCI_LL_SHIFT               15

/* SATA_MDIO :: MDIO_CONTROL :: BYP_PCI_33 [14:14] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_BYP_PCI_33_MASK                0x4000
#define BCHP_SATA_MDIO_MDIO_CONTROL_BYP_PCI_33_SHIFT               14

/* SATA_MDIO :: MDIO_CONTROL :: PWR_PLL [13:13] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_PWR_PLL_MASK                   0x2000
#define BCHP_SATA_MDIO_MDIO_CONTROL_PWR_PLL_SHIFT                  13

/* SATA_MDIO :: MDIO_CONTROL :: PCI_1 [12:12] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_PCI_1_MASK                     0x1000
#define BCHP_SATA_MDIO_MDIO_CONTROL_PCI_1_SHIFT                    12

/* SATA_MDIO :: MDIO_CONTROL :: PCI_33 [11:11] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_PCI_33_MASK                    0x0800
#define BCHP_SATA_MDIO_MDIO_CONTROL_PCI_33_SHIFT                   11

/* SATA_MDIO :: MDIO_CONTROL :: reserved0 [10:07] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_reserved0_MASK                 0x0780
#define BCHP_SATA_MDIO_MDIO_CONTROL_reserved0_SHIFT                7

/* SATA_MDIO :: MDIO_CONTROL :: EN_RX [06:06] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_RX_MASK                     0x0040
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_RX_SHIFT                    6

/* SATA_MDIO :: MDIO_CONTROL :: EN_TX [05:05] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_TX_MASK                     0x0020
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_TX_SHIFT                    5

/* SATA_MDIO :: MDIO_CONTROL :: EN_BERT [04:04] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_BERT_MASK                   0x0010
#define BCHP_SATA_MDIO_MDIO_CONTROL_EN_BERT_SHIFT                  4

/* SATA_MDIO :: MDIO_CONTROL :: ANLOG_RESET [03:03] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANLOG_RESET_MASK               0x0008
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANLOG_RESET_SHIFT              3

/* SATA_MDIO :: MDIO_CONTROL :: SS_CLK_EN [02:02] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_SS_CLK_EN_MASK                 0x0004
#define BCHP_SATA_MDIO_MDIO_CONTROL_SS_CLK_EN_SHIFT                2

/* SATA_MDIO :: MDIO_CONTROL :: ANL_TE [01:01] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANL_TE_MASK                    0x0002
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANL_TE_SHIFT                   1

/* SATA_MDIO :: MDIO_CONTROL :: ANL_PWER [00:00] */
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANL_PWER_MASK                  0x0001
#define BCHP_SATA_MDIO_MDIO_CONTROL_ANL_PWER_SHIFT                 0

/***************************************************************************
 *MDIO_TEST_CONTROL - MDIO Testbus Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_TEST_CONTROL :: reserved0 [15:13] */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_reserved0_MASK            0xe000
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_reserved0_SHIFT           13

/* SATA_MDIO :: MDIO_TEST_CONTROL :: TEST_MUX [12:11] */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TEST_MUX_MASK             0x1800
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TEST_MUX_SHIFT            11

/* SATA_MDIO :: MDIO_TEST_CONTROL :: PORT_SEL [10:08] */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_PORT_SEL_MASK             0x0700
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_PORT_SEL_SHIFT            8

/* SATA_MDIO :: MDIO_TEST_CONTROL :: TESTBUS_B [07:04] */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TESTBUS_B_MASK            0x00f0
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TESTBUS_B_SHIFT           4

/* SATA_MDIO :: MDIO_TEST_CONTROL :: TESTBUS_A [03:00] */
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TESTBUS_A_MASK            0x000f
#define BCHP_SATA_MDIO_MDIO_TEST_CONTROL_TESTBUS_A_SHIFT           0

/***************************************************************************
 *MDIO_PORT_SEL - MDIO Read/Write Port Select Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_SEL :: LOCK [15:15] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_LOCK_MASK                     0x8000
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_LOCK_SHIFT                    15

/* SATA_MDIO :: MDIO_PORT_SEL :: reserved0 [14:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_reserved0_MASK                0x7ff0
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_reserved0_SHIFT               4

/* SATA_MDIO :: MDIO_PORT_SEL :: PORT3 [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT3_MASK                    0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT3_SHIFT                   3

/* SATA_MDIO :: MDIO_PORT_SEL :: PORT2 [02:02] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT2_MASK                    0x0004
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT2_SHIFT                   2

/* SATA_MDIO :: MDIO_PORT_SEL :: PORT1 [01:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT1_MASK                    0x0002
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT1_SHIFT                   1

/* SATA_MDIO :: MDIO_PORT_SEL :: PORT0 [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT0_MASK                    0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_SEL_PORT0_SHIFT                   0

/***************************************************************************
 *MDIO_PORT_RX_LOW - MDIO PORTx Rx Control Low Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_RX_LOW :: TS_MSB [15:15] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_MSB_MASK                0x8000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_MSB_SHIFT               15

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: TS [14:14] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_MASK                    0x4000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_SHIFT                   14

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: TS_LSB [13:13] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_LSB_MASK                0x2000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_TS_LSB_SHIFT               13

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: SDT_MSB [12:12] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDT_MSB_MASK               0x1000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDT_MSB_SHIFT              12

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: SDT_LSB [11:11] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDT_LSB_MASK               0x0800
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDT_LSB_SHIFT              11

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: SDE [10:10] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDE_MASK                   0x0400
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_SDE_SHIFT                  10

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: LPE [09:09] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_LPE_MASK                   0x0200
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_LPE_SHIFT                  9

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: ES_RWCLK [08:08] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_ES_RWCLK_MASK              0x0100
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_ES_RWCLK_SHIFT             8

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: I_BIAS_MSB [07:07] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_MSB_MASK            0x0080
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_MSB_SHIFT           7

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: I_BIAS [06:06] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_MASK                0x0040
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_SHIFT               6

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: I_BIAS_LSB [05:05] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_LSB_MASK            0x0020
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_I_BIAS_LSB_SHIFT           5

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: R_BIAS_MSB [04:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_MSB_MASK            0x0010
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_MSB_SHIFT           4

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: R_BIAS [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_MASK                0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_SHIFT               3

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: R_BIAS_LSB [02:02] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_LSB_MASK            0x0004
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_BIAS_LSB_SHIFT           2

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: R_RESET [01:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_RESET_MASK               0x0002
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_RESET_SHIFT              1

/* SATA_MDIO :: MDIO_PORT_RX_LOW :: R_PWR [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_PWR_MASK                 0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_RX_LOW_R_PWR_SHIFT                0

/***************************************************************************
 *MDIO_PORT_RX_HIGH - MDIO PORTx Rx Control High Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: PDIE [15:15] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_PDIE_MASK                 0x8000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_PDIE_SHIFT                15

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MIV_MSB [14:14] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIV_MSB_MASK              0x4000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIV_MSB_SHIFT             14

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MIVF [13:13] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIVF_MASK                 0x2000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIVF_SHIFT                13

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MIVS [12:12] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIVS_MASK                 0x1000
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIVS_SHIFT                12

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MIV_LSB [11:11] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIV_LSB_MASK              0x0800
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MIV_LSB_SHIFT             11

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MMIV_MSB [10:10] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV_MSB_MASK             0x0400
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV_MSB_SHIFT            10

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MMIV1 [09:09] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV1_MASK                0x0200
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV1_SHIFT               9

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MMIV2 [08:08] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV2_MASK                0x0100
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV2_SHIFT               8

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: MMIV_LSB [07:07] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV_LSB_MASK             0x0080
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_MMIV_LSB_SHIFT            7

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFPB_MSB [06:06] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_MSB_MASK             0x0040
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_MSB_SHIFT            6

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFPB [05:05] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_MASK                 0x0020
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_SHIFT                5

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFPB_LSB [04:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_LSB_MASK             0x0010
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFPB_LSB_SHIFT            4

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFIN_MSB [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_MSB_MASK             0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_MSB_SHIFT            3

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFIN [02:02] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_MASK                 0x0004
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_SHIFT                2

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFIN_LSB [01:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_LSB_MASK             0x0002
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIN_LSB_SHIFT            1

/* SATA_MDIO :: MDIO_PORT_RX_HIGH :: LFIB [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIB_MASK                 0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_RX_HIGH_LFIB_SHIFT                0

/***************************************************************************
 *MDIO_PORT_TX - MDIO PORTx Tx Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_TX :: TDC_MSB [15:15] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDC_MSB_MASK                   0x8000
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDC_MSB_SHIFT                  15

/* SATA_MDIO :: MDIO_PORT_TX :: TDCF [14:14] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDCF_MASK                      0x4000
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDCF_SHIFT                     14

/* SATA_MDIO :: MDIO_PORT_TX :: TDCS [13:13] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDCS_MASK                      0x2000
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDCS_SHIFT                     13

/* SATA_MDIO :: MDIO_PORT_TX :: TDC_LSB [12:12] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDC_LSB_MASK                   0x1000
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDC_LSB_SHIFT                  12

/* SATA_MDIO :: MDIO_PORT_TX :: TPC_MSB [11:11] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_MSB_MASK                   0x0800
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_MSB_SHIFT                  11

/* SATA_MDIO :: MDIO_PORT_TX :: TPC [10:10] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_MASK                       0x0400
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_SHIFT                      10

/* SATA_MDIO :: MDIO_PORT_TX :: TPC_LSB [09:09] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_LSB_MASK                   0x0200
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TPC_LSB_SHIFT                  9

/* SATA_MDIO :: MDIO_PORT_TX :: PEC_MSB [08:08] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_MSB_MASK                   0x0100
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_MSB_SHIFT                  8

/* SATA_MDIO :: MDIO_PORT_TX :: PEC [07:07] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_MASK                       0x0080
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_SHIFT                      7

/* SATA_MDIO :: MDIO_PORT_TX :: PEC_LSB [06:06] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_LSB_MASK                   0x0040
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PEC_LSB_SHIFT                  6

/* SATA_MDIO :: MDIO_PORT_TX :: TR_TXWCLK [05:05] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TR_TXWCLK_MASK                 0x0020
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TR_TXWCLK_SHIFT                5

/* SATA_MDIO :: MDIO_PORT_TX :: PPEM [04:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PPEM_MASK                      0x0010
#define BCHP_SATA_MDIO_MDIO_PORT_TX_PPEM_SHIFT                     4

/* SATA_MDIO :: MDIO_PORT_TX :: TDIE [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDIE_MASK                      0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDIE_SHIFT                     3

/* SATA_MDIO :: MDIO_PORT_TX :: RLE [02:02] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_RLE_MASK                       0x0004
#define BCHP_SATA_MDIO_MDIO_PORT_TX_RLE_SHIFT                      2

/* SATA_MDIO :: MDIO_PORT_TX :: TDR [01:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDR_MASK                       0x0002
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDR_SHIFT                      1

/* SATA_MDIO :: MDIO_PORT_TX :: TDPWR [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDPWR_MASK                     0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_TX_TDPWR_SHIFT                    0

/***************************************************************************
 *MDIO_PORT_PRBS_CONTROL - MDIO PORTx PRBS Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_PRBS_CONTROL :: reserved0 [15:05] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_reserved0_MASK       0xffe0
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_reserved0_SHIFT      5

/* SATA_MDIO :: MDIO_PORT_PRBS_CONTROL :: EN [04:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_EN_MASK              0x0010
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_EN_SHIFT             4

/* SATA_MDIO :: MDIO_PORT_PRBS_CONTROL :: INV [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_INV_MASK             0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_INV_SHIFT            3

/* SATA_MDIO :: MDIO_PORT_PRBS_CONTROL :: ORDER [02:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_ORDER_MASK           0x0006
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_ORDER_SHIFT          1

/* SATA_MDIO :: MDIO_PORT_PRBS_CONTROL :: EC [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_EC_MASK              0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_CONTROL_EC_SHIFT             0

/***************************************************************************
 *MDIO_PORT_PRBS_STATUS - MDIO PORTx PRBS Status Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_PRBS_STATUS :: LOCK [15:15] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_LOCK_MASK             0x8000
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_LOCK_SHIFT            15

/* SATA_MDIO :: MDIO_PORT_PRBS_STATUS :: LOST [14:14] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_LOST_MASK             0x4000
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_LOST_SHIFT            14

/* SATA_MDIO :: MDIO_PORT_PRBS_STATUS :: ERR [13:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_ERR_MASK              0x3fff
#define BCHP_SATA_MDIO_MDIO_PORT_PRBS_STATUS_ERR_SHIFT             0

/***************************************************************************
 *MDIO_PORT_DIG_CONTROL - MDIO PORTx Digital Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_PORT_DIG_CONTROL :: reserved0 [15:05] */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_reserved0_MASK        0xffe0
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_reserved0_SHIFT       5

/* SATA_MDIO :: MDIO_PORT_DIG_CONTROL :: TBI [04:04] */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_TBI_MASK              0x0010
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_TBI_SHIFT             4

/* SATA_MDIO :: MDIO_PORT_DIG_CONTROL :: LOOP [03:03] */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_LOOP_MASK             0x0008
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_LOOP_SHIFT            3

/* SATA_MDIO :: MDIO_PORT_DIG_CONTROL :: reserved1 [02:01] */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_reserved1_MASK        0x0006
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_reserved1_SHIFT       1

/* SATA_MDIO :: MDIO_PORT_DIG_CONTROL :: COMMA [00:00] */
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_COMMA_MASK            0x0001
#define BCHP_SATA_MDIO_MDIO_PORT_DIG_CONTROL_COMMA_SHIFT           0

/***************************************************************************
 *MDIO_BIST_STATUS_LOW - Ram BIST Status Register Low
 ***************************************************************************/
/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST3_F [15:14] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST3_F_MASK           0xc000
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST3_F_SHIFT          14

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST3_C [13:12] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST3_C_MASK           0x3000
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST3_C_SHIFT          12

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST2_F [11:10] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST2_F_MASK           0x0c00
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST2_F_SHIFT          10

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST2_C [09:08] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST2_C_MASK           0x0300
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST2_C_SHIFT          8

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST1_F [07:06] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST1_F_MASK           0x00c0
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST1_F_SHIFT          6

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST1_C [05:04] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST1_C_MASK           0x0030
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST1_C_SHIFT          4

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST0_F [03:02] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST0_F_MASK           0x000c
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST0_F_SHIFT          2

/* SATA_MDIO :: MDIO_BIST_STATUS_LOW :: BIST0_C [01:00] */
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST0_C_MASK           0x0003
#define BCHP_SATA_MDIO_MDIO_BIST_STATUS_LOW_BIST0_C_SHIFT          0

/***************************************************************************
 *MDIO_BIST_CONTROL - Ram BIST Control Register
 ***************************************************************************/
/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST3_E [15:14] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST3_E_MASK              0xc000
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST3_E_SHIFT             14

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST3_F [13:12] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST3_F_MASK              0x3000
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST3_F_SHIFT             12

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST2_E [11:10] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST2_E_MASK              0x0c00
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST2_E_SHIFT             10

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST2_F [09:08] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST2_F_MASK              0x0300
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST2_F_SHIFT             8

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST1_E [07:06] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST1_E_MASK              0x00c0
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST1_E_SHIFT             6

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST1_F [05:04] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST1_F_MASK              0x0030
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST1_F_SHIFT             4

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST0_E [03:02] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST0_E_MASK              0x000c
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST0_E_SHIFT             2

/* SATA_MDIO :: MDIO_BIST_CONTROL :: BIST0_F [01:00] */
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST0_F_MASK              0x0003
#define BCHP_SATA_MDIO_MDIO_BIST_CONTROL_BIST0_F_SHIFT             0

/***************************************************************************
 *MDIO_DEV_ID - Device and Revision ID
 ***************************************************************************/
/* SATA_MDIO :: MDIO_DEV_ID :: PN [15:08] */
#define BCHP_SATA_MDIO_MDIO_DEV_ID_PN_MASK                         0xff00
#define BCHP_SATA_MDIO_MDIO_DEV_ID_PN_SHIFT                        8

/* SATA_MDIO :: MDIO_DEV_ID :: ID [07:04] */
#define BCHP_SATA_MDIO_MDIO_DEV_ID_ID_MASK                         0x00f0
#define BCHP_SATA_MDIO_MDIO_DEV_ID_ID_SHIFT                        4

/* SATA_MDIO :: MDIO_DEV_ID :: MASK [03:00] */
#define BCHP_SATA_MDIO_MDIO_DEV_ID_MASK_MASK                       0x000f
#define BCHP_SATA_MDIO_MDIO_DEV_ID_MASK_SHIFT                      0

#endif /* #ifndef BCHP_SATA_MDIO_H__ */

/* End of File */
