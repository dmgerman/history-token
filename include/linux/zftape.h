macro_line|#ifndef _ZFTAPE_H
DECL|macro|_ZFTAPE_H
mdefine_line|#define _ZFTAPE_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/include/linux/zftape.h,v $&n; * $Revision: 1.12 $&n; * $Date: 1997/10/21 11:02:37 $&n; *&n; *      Special ioctl and other global info for the zftape VFS&n; *      interface for the QIC-40/80/3010/3020 floppy-tape driver for&n; *      Linux.&n; */
DECL|macro|ZFTAPE_VERSION
mdefine_line|#define ZFTAPE_VERSION  &quot;zftape for &quot; FTAPE_VERSION
macro_line|#include &lt;linux/ftape.h&gt;
DECL|macro|ZFTAPE_LABEL
mdefine_line|#define ZFTAPE_LABEL       &quot;Ftape - The Linux Floppy Tape Project!&quot;
multiline_comment|/* Bits of the minor device number that control the operation mode */
DECL|macro|ZFT_Q80_MODE
mdefine_line|#define ZFT_Q80_MODE&t;&t;(1 &lt;&lt; 3)
DECL|macro|ZFT_ZIP_MODE
mdefine_line|#define ZFT_ZIP_MODE&t;&t;(1 &lt;&lt; 4)
DECL|macro|ZFT_RAW_MODE
mdefine_line|#define ZFT_RAW_MODE&t;&t;(1 &lt;&lt; 5)
DECL|macro|ZFT_MINOR_OP_MASK
mdefine_line|#define ZFT_MINOR_OP_MASK&t;(ZFT_Q80_MODE&t;| &t;&bslash;&n;&t;&t;&t;&t; ZFT_ZIP_MODE&t;| &t;&bslash;&n;&t;&t;&t;&t; ZFT_RAW_MODE)
DECL|macro|ZFT_MINOR_MASK
mdefine_line|#define ZFT_MINOR_MASK&t;&t;(FTAPE_SEL_MASK&t;&t;|&t;&bslash;&n;&t;&t;&t;&t; ZFT_MINOR_OP_MASK&t;|&t;&bslash;&n;&t;&t;&t;&t; FTAPE_NO_REWIND)
macro_line|#ifdef ZFT_OBSOLETE
DECL|struct|mtblksz
r_struct
id|mtblksz
(brace
DECL|member|mt_blksz
r_int
r_int
id|mt_blksz
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MTIOC_ZFTAPE_GETBLKSZ
mdefine_line|#define MTIOC_ZFTAPE_GETBLKSZ _IOR(&squot;m&squot;, 104, struct mtblksz)
macro_line|#endif
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|zft_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|zft_div_blksz
r_static
r_inline
id|__s64
id|zft_div_blksz
c_func
(paren
id|__s64
id|value
comma
id|__u32
id|blk_sz
)paren
(brace
r_if
c_cond
(paren
id|blk_sz
op_eq
l_int|1
)paren
(brace
r_return
id|value
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|__s64
)paren
(paren
(paren
(paren
id|__u32
)paren
(paren
id|value
op_rshift
l_int|10
)paren
op_plus
(paren
id|blk_sz
op_rshift
l_int|10
)paren
op_minus
l_int|1
)paren
op_div
(paren
id|blk_sz
op_rshift
l_int|10
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|zft_mul_blksz
r_static
r_inline
id|__s64
id|zft_mul_blksz
c_func
(paren
id|__s64
id|value
comma
id|__u32
id|blk_sz
)paren
(brace
r_if
c_cond
(paren
id|blk_sz
op_eq
l_int|1
)paren
(brace
r_return
id|value
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*  if blk_sz != 1, then it is a multiple of 1024. In&n;&t;&t; *  this case, `value&squot; will also fit into 32 bits.&n;&t;&t; * &n;&t;&t; *  Actually, this limits the capacity to 42&n;&t;&t; *  bits. This is (2^32)*1024, roughly a thousand&n;&t;&t; *  times 2GB, or 3 Terabytes. Hopefully this is enough&n;&t;&t; */
r_return
(paren
id|__s64
)paren
(paren
(paren
(paren
id|__u32
)paren
(paren
id|value
)paren
op_star
(paren
id|blk_sz
op_rshift
l_int|10
)paren
)paren
op_lshift
l_int|10
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#endif
eof
