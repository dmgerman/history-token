multiline_comment|/* $Id: hysdn_if.h,v 1.1.8.1 2001/03/13 16:17:10 kai Exp $&n;&n; * Linux driver for HYSDN cards, ioctl definitions shared by hynetmgr and driver.&n; * written by Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; *&n; * Copyright 1999  by Werner Cornelius (werner@titro.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: hysdn_if.h,v $&n; * Revision 1.1.8.1  2001/03/13 16:17:10  kai&n; * spelling fixes from 2.4.3-pre&n; *&n; * Revision 1.1  2000/02/10 19:47:50  werner&n; *&n; * Initial release&n; *&n; *&n; */
multiline_comment|/****************/
multiline_comment|/* error values */
multiline_comment|/****************/
DECL|macro|ERR_NONE
mdefine_line|#define ERR_NONE             0 /* no error occurred */
DECL|macro|ERR_ALREADY_BOOT
mdefine_line|#define ERR_ALREADY_BOOT  1000 /* we are already booting */
DECL|macro|EPOF_BAD_MAGIC
mdefine_line|#define EPOF_BAD_MAGIC    1001 /* bad magic in POF header */
DECL|macro|ERR_BOARD_DPRAM
mdefine_line|#define ERR_BOARD_DPRAM   1002 /* board DPRAM failed */
DECL|macro|EPOF_INTERNAL
mdefine_line|#define EPOF_INTERNAL     1003 /* internal POF handler error */
DECL|macro|EPOF_BAD_IMG_SIZE
mdefine_line|#define EPOF_BAD_IMG_SIZE 1004 /* POF boot image size invalid */
DECL|macro|ERR_BOOTIMG_FAIL
mdefine_line|#define ERR_BOOTIMG_FAIL  1005 /* 1. stage boot image did not start */
DECL|macro|ERR_BOOTSEQ_FAIL
mdefine_line|#define ERR_BOOTSEQ_FAIL  1006 /* 2. stage boot seq handshake timeout */
DECL|macro|ERR_POF_TIMEOUT
mdefine_line|#define ERR_POF_TIMEOUT   1007 /* timeout waiting for card pof ready */
DECL|macro|ERR_NOT_BOOTED
mdefine_line|#define ERR_NOT_BOOTED    1008 /* operation only allowed when booted */
DECL|macro|ERR_CONF_LONG
mdefine_line|#define ERR_CONF_LONG     1009 /* conf line is to long */ 
DECL|macro|ERR_INV_CHAN
mdefine_line|#define ERR_INV_CHAN      1010 /* invalid channel number */ 
DECL|macro|ERR_ASYNC_TIME
mdefine_line|#define ERR_ASYNC_TIME    1011 /* timeout sending async data */ 
eof
