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
 * Date:           Generated on         Mon Jul 23 12:04:11 2007
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
 * $brcm_Log: /magnum/basemodules/chp/7400/rdb/d0/bchp_uartb.h $
 * 
 * Hydra_Software_Devel/1   7/23/07 4:38p maivu
 * PR 32842: Initial revision
 *
 ***************************************************************************/

#ifndef BCHP_UARTB_H__
#define BCHP_UARTB_H__

/***************************************************************************
 *UARTB - UART B
 ***************************************************************************/
#define BCHP_UARTB_RBR                           0x00400b40 /* Receive Buffer Register */
#define BCHP_UARTB_THR                           0x00400b40 /* Transmit Holding Register */
#define BCHP_UARTB_DLH                           0x00400b44 /* Divisor Latch High */
#define BCHP_UARTB_DLL                           0x00400b40 /* Divisor Latch Low */
#define BCHP_UARTB_IER                           0x00400b44 /* Interrupt Enable Register */
#define BCHP_UARTB_IIR                           0x00400b48 /* Interrupt Identity Register */
#define BCHP_UARTB_FCR                           0x00400b48 /* FIFO Control Register */
#define BCHP_UARTB_LCR                           0x00400b4c /* Line Control Register */
#define BCHP_UARTB_MCR                           0x00400b50 /* Modem Control Register */
#define BCHP_UARTB_LSR                           0x00400b54 /* Line Status Register */
#define BCHP_UARTB_MSR                           0x00400b58 /* Modem Status Register */
#define BCHP_UARTB_SCR                           0x00400b5c /* Scratchpad Register */

#endif /* #ifndef BCHP_UARTB_H__ */

/* End of File */
