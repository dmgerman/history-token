multiline_comment|/*&n; *&n; *&t;&t;&t;Linux MegaRAID device driver&n; *&n; * Copyright (c) 2003-2004  LSI Logic Corporation.&n; *&n; *&t;   This program is free software; you can redistribute it and/or&n; *&t;   modify it under the terms of the GNU General Public License&n; *&t;   as published by the Free Software Foundation; either version&n; *&t;   2 of the License, or (at your option) any later version.&n; *&n; * FILE&t;&t;: megaraid_mm.h&n; */
macro_line|#ifndef MEGARAID_MM_H
DECL|macro|MEGARAID_MM_H
mdefine_line|#define MEGARAID_MM_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
macro_line|#include &quot;mbox_defs.h&quot;
macro_line|#include &quot;megaraid_ioctl.h&quot;
DECL|macro|LSI_COMMON_MOD_VERSION
mdefine_line|#define LSI_COMMON_MOD_VERSION&t;&quot;2.20.2.3&quot;
DECL|macro|LSI_COMMON_MOD_EXT_VERSION
mdefine_line|#define LSI_COMMON_MOD_EXT_VERSION&t;&bslash;&n;&t;&t;&quot;(Release Date: Thu Dec  9 19:02:14 EST 2004)&quot;
DECL|macro|LSI_DBGLVL
mdefine_line|#define LSI_DBGLVL&t;&t;&t;dbglevel
singleline_comment|// The smallest dma pool
DECL|macro|MRAID_MM_INIT_BUFF_SIZE
mdefine_line|#define MRAID_MM_INIT_BUFF_SIZE&t;&t;4096
multiline_comment|/**&n; * mimd_t&t;: Old style ioctl packet structure (deprecated)&n; *&n; * @inlen&t;:&n; * @outlen&t;:&n; * @fca&t;&t;:&n; * @opcode&t;:&n; * @subopcode&t;:&n; * @adapno&t;:&n; * @buffer&t;:&n; * @pad&t;&t;:&n; * @length&t;:&n; * @mbox&t;:&n; * @pthru&t;:&n; * @data&t;:&n; * @pad&t;&t;:&n; *&n; * Note&t;&t;: This structure is DEPRECATED. New applications must use&n; *&t;&t;: uioc_t structure instead. All new hba drivers use the new&n; *&t;&t;: format. If we get this mimd packet, we will convert it into&n; *&t;&t;: new uioc_t format and send it to the hba drivers.&n; */
DECL|struct|mimd
r_typedef
r_struct
id|mimd
(brace
DECL|member|inlen
r_uint32
id|inlen
suffix:semicolon
DECL|member|outlen
r_uint32
id|outlen
suffix:semicolon
r_union
(brace
DECL|member|fca
r_uint8
id|fca
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|opcode
r_uint8
id|opcode
suffix:semicolon
DECL|member|subopcode
r_uint8
id|subopcode
suffix:semicolon
DECL|member|adapno
r_uint16
id|adapno
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|member|buffer
r_uint8
id|__user
op_star
id|buffer
suffix:semicolon
DECL|member|pad
r_uint8
id|pad
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if BITS_PER_LONG == 64
DECL|member|buffer
r_uint8
id|__user
op_star
id|buffer
suffix:semicolon
macro_line|#endif
DECL|member|length
r_uint32
id|length
suffix:semicolon
DECL|member|fcs
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|fcs
suffix:semicolon
DECL|member|ui
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ui
suffix:semicolon
DECL|member|mbox
r_uint8
id|mbox
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* 16 bytes + 2 status bytes */
DECL|member|pthru
id|mraid_passthru_t
id|pthru
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|member|data
r_char
id|__user
op_star
id|data
suffix:semicolon
multiline_comment|/* buffer &lt;= 4096 for 0x80 commands */
DECL|member|pad
r_char
id|pad
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if BITS_PER_LONG == 64
DECL|member|data
r_char
id|__user
op_star
id|data
suffix:semicolon
macro_line|#endif
DECL|typedef|mimd_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mimd_t
suffix:semicolon
macro_line|#endif 
singleline_comment|// MEGARAID_MM_H
singleline_comment|// vi: set ts=8 sw=8 tw=78:
eof
