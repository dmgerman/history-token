multiline_comment|/*&n; * Flash Memory Driver for M32700UT-CPU&n; *&n; * Copyright 2003 (C)   Takeo Takahashi&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * 2003-02-01: &t;Takeo Takahashi, support M5M29GT320VP.&n; */
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|DEBUG
macro_line|#undef DEBUG
multiline_comment|/* debug routine:&n; *   0x00000001: print debug information&n; */
DECL|macro|DEBUG
macro_line|#  define DEBUG(n, args...) if ((n) &amp; debug) &bslash;&n;&t;printk(KERN_DEBUG args)
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/*&n; * data type to access flash memory&n; */
DECL|typedef|m5_t
r_typedef
r_volatile
r_int
r_int
id|m5_t
suffix:semicolon
multiline_comment|/*&n; * - Page program buffer size in byte&n; * - block size in byte&n; * - number of block&n; */
DECL|macro|M5_PAGE_SIZE
mdefine_line|#define M5_PAGE_SIZE&t;&t;(256)
DECL|macro|M5_BLOCK_SIZE8
mdefine_line|#define M5_BLOCK_SIZE8&t;&t;(8*1024)
DECL|macro|M5_BLOCK_SIZE64
mdefine_line|#define M5_BLOCK_SIZE64&t;&t;(64*1024)
DECL|macro|MAX_BLOCK_NUM
mdefine_line|#define MAX_BLOCK_NUM&t;&t;70
multiline_comment|/*&n; * Software commands&n; */
DECL|macro|M5_CMD_READ_ARRAY
mdefine_line|#define M5_CMD_READ_ARRAY            0xff
DECL|macro|M5_CMD_DEVICE_IDENT
mdefine_line|#define M5_CMD_DEVICE_IDENT          0x90
DECL|macro|M5_CMD_READ_STATUS
mdefine_line|#define M5_CMD_READ_STATUS           0x70
DECL|macro|M5_CMD_CLEAR_STATUS
mdefine_line|#define M5_CMD_CLEAR_STATUS          0x50
DECL|macro|M5_CMD_BLOCK_ERASE
mdefine_line|#define M5_CMD_BLOCK_ERASE           0x20
DECL|macro|M5_CMD_CONFIRM
mdefine_line|#define M5_CMD_CONFIRM               0xd0
DECL|macro|M5_CMD_PROGRAM_BYTE
mdefine_line|#define M5_CMD_PROGRAM_BYTE          0x40
DECL|macro|M5_CMD_PROGRAM_WORD
mdefine_line|#define M5_CMD_PROGRAM_WORD          M5_CMD_PROGRAM_BYTE
DECL|macro|M5_CMD_PROGRAM_PAGE
mdefine_line|#define M5_CMD_PROGRAM_PAGE          0x41
DECL|macro|M5_CMD_SINGLE_LOAD_DATA
mdefine_line|#define M5_CMD_SINGLE_LOAD_DATA      0x74
DECL|macro|M5_CMD_BUFF2FLASH
mdefine_line|#define M5_CMD_BUFF2FLASH            0x0e
DECL|macro|M5_CMD_FLASH2BUFF
mdefine_line|#define M5_CMD_FLASH2BUFF            0xf1
DECL|macro|M5_CMD_CLEAR_BUFF
mdefine_line|#define M5_CMD_CLEAR_BUFF            0x55
DECL|macro|M5_CMD_SUSPEND
mdefine_line|#define M5_CMD_SUSPEND               0xb0
DECL|macro|M5_CMD_RESUME
mdefine_line|#define M5_CMD_RESUME                0xd0
multiline_comment|/*&n; * Status&n; */
DECL|macro|M5_STATUS_READY
mdefine_line|#define M5_STATUS_READY              0x80 /* 0:busy 1:ready */
DECL|macro|M5_STATUS_SUSPEND
mdefine_line|#define M5_STATUS_SUSPEND            0x40 /* 0:progress/complete 1:suspend */
DECL|macro|M5_STATUS_ERASE
mdefine_line|#define M5_STATUS_ERASE              0x20 /* 0:pass 1:error */
DECL|macro|M5_STATUS_PROGRAM
mdefine_line|#define M5_STATUS_PROGRAM            0x10 /* 0:pass 1:error */
DECL|macro|M5_STATUS_BLOCK
mdefine_line|#define M5_STATUS_BLOCK              0x08 /* 0:pass 1:error */
multiline_comment|/*&n; * Device Code&n; */
DECL|macro|M5_MAKER
mdefine_line|#define M5_MAKER&t;&t;(0x1c)
DECL|macro|M5_M5M29GT320VP
mdefine_line|#define M5_M5M29GT320VP&t;&t;(0x20)
DECL|macro|M5_M5M29GB320VP
mdefine_line|#define M5_M5M29GB320VP&t;&t;(0x21)
eof
