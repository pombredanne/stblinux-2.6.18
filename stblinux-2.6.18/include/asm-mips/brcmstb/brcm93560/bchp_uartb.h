/***************************************************************************
 *     Copyright (c) 1999-2005, Broadcom Corporation
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
 * $brcm_Workfile: bchp_uartb.h $
 * $brcm_Revision: Hydra_Software_Devel/1 $
 * $brcm_Date: 2/7/05 5:22p $
 *
 * Module Description:
 *                     DO NOT EDIT THIS FILE DIRECTLY
 *
 * This module was generated magically with RDB from a source description
 * file. You must edit the source file for changes to be made to this file.
 *
 *
 * Date:           Generated on         Wed Feb  2 14:20:19 2005
 *                 MD5 Checksum         79ed7ffd006d38aa0c98f22044a7ee60
 *
 * Compiled with:  RDB Utility          combo_header.pl
 *                 RDB Parser           3.0
 *                 unknown              unknown
 *                 Perl Interpreter     5.006
 *                 Operating System     linux
 *
 * Revision History:
 *
 * $brcm_Log: /magnum/basemodules/chp/3560/rdb/a0/bchp_uartb.h $
 * 
 * Hydra_Software_Devel/1   2/7/05 5:22p pntruong
 * PR13974: Update and fix chip revision detection for 3560.
 *
 ***************************************************************************/

#ifndef BCHP_UARTB_H__
#define BCHP_UARTB_H__

/***************************************************************************
 *UARTB - UART B
 ***************************************************************************/
#define BCHP_UARTB_RCVSTAT                       0x004001a0 /* RECEIVE STATUS REGISTER */
#define BCHP_UARTB_RCVDATA                       0x004001a4 /* RECEIVE DATA REGISTER */
#define BCHP_UARTB_CONTROL                       0x004001ac /* CONTROL REGISTER */
#define BCHP_UARTB_BAUDHI                        0x004001b0 /* BAUD RATE REGISTER HI */
#define BCHP_UARTB_BAUDLO                        0x004001b4 /* BAUD RATE REGISTER LO */
#define BCHP_UARTB_XMTSTAT                       0x004001b8 /* TRANSMIT STATUS REGISTER */
#define BCHP_UARTB_XMTDATA                       0x004001bc /* TRANSMIT DATA REGISTER */

#endif /* #ifndef BCHP_UARTB_H__ */

/* End of File */