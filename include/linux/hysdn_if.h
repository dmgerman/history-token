multiline_comment|/* $Id: hysdn_if.h,v 1.1.8.3 2001/09/23 22:25:05 kai Exp $&n; *&n; * Linux driver for HYSDN cards&n; * ioctl definitions shared by hynetmgr and driver.&n; *&n; * Author    Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; * Copyright 1999 by Werner Cornelius (werner@titro.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
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
