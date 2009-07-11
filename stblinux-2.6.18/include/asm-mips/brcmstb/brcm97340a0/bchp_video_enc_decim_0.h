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
 * Date:           Generated on         Fri Mar 20 12:54:14 2009
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
 * $brcm_Log: /magnum/basemodules/chp/7340/rdb/a0/bchp_video_enc_decim_0.h $
 * 
 * Hydra_Software_Devel/1   3/22/09 9:25p yuxiaz
 * PR53430: Initial version of header files.
 *
 ***************************************************************************/

#ifndef BCHP_VIDEO_ENC_DECIM_0_H__
#define BCHP_VIDEO_ENC_DECIM_0_H__

/***************************************************************************
 *VIDEO_ENC_DECIM_0 - VEC Decimator  Controls
 ***************************************************************************/
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_REV_ID      0x00185200 /* Decimator Revision ID register */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL     0x00185208 /* Control Register for decimator */

/***************************************************************************
 *DECIM_REV_ID - Decimator Revision ID register
 ***************************************************************************/
/* VIDEO_ENC_DECIM_0 :: DECIM_REV_ID :: reserved0 [31:16] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_REV_ID_reserved0_MASK         0xffff0000
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_REV_ID_reserved0_SHIFT        16

/* VIDEO_ENC_DECIM_0 :: DECIM_REV_ID :: REVISION_ID [15:00] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_REV_ID_REVISION_ID_MASK       0x0000ffff
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_REV_ID_REVISION_ID_SHIFT      0

/***************************************************************************
 *DECIM_CONTROL - Control Register for decimator
 ***************************************************************************/
/* VIDEO_ENC_DECIM_0 :: DECIM_CONTROL :: reserved0 [31:13] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_reserved0_MASK        0xffffe000
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_reserved0_SHIFT       13

/* VIDEO_ENC_DECIM_0 :: DECIM_CONTROL :: PASSTHROUGH_COUNT [12:03] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_PASSTHROUGH_COUNT_MASK 0x00001ff8
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_PASSTHROUGH_COUNT_SHIFT 3

/* VIDEO_ENC_DECIM_0 :: DECIM_CONTROL :: DECIMATE_RATIO [02:02] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_RATIO_MASK   0x00000004
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_RATIO_SHIFT  2
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_RATIO_BY2    1
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_RATIO_BY4    0

/* VIDEO_ENC_DECIM_0 :: DECIM_CONTROL :: DECIMATE_SAMPLING_EN [01:01] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_SAMPLING_EN_MASK 0x00000002
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_SAMPLING_EN_SHIFT 1
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_SAMPLING_EN_ON 1
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_SAMPLING_EN_OFF 0

/* VIDEO_ENC_DECIM_0 :: DECIM_CONTROL :: DECIMATE_FILTER_EN [00:00] */
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_FILTER_EN_MASK 0x00000001
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_FILTER_EN_SHIFT 0
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_FILTER_EN_ON 1
#define BCHP_VIDEO_ENC_DECIM_0_DECIM_CONTROL_DECIMATE_FILTER_EN_OFF 0

#endif /* #ifndef BCHP_VIDEO_ENC_DECIM_0_H__ */

/* End of File */