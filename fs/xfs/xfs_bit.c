multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * XFS bit manipulation routines, used in non-realtime code.&n; */
macro_line|#include &lt;xfs.h&gt;
macro_line|#ifndef HAVE_ARCH_HIGHBIT
multiline_comment|/*&n; * Index of high bit number in byte, -1 for none set, 0..7 otherwise.&n; */
DECL|variable|xfs_highbit
r_const
r_char
id|xfs_highbit
(braket
l_int|256
)braket
op_assign
(brace
op_minus
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
multiline_comment|/* 00 .. 07 */
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
multiline_comment|/* 08 .. 0f */
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
multiline_comment|/* 10 .. 17 */
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
l_int|4
comma
multiline_comment|/* 18 .. 1f */
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
multiline_comment|/* 20 .. 27 */
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
multiline_comment|/* 28 .. 2f */
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
multiline_comment|/* 30 .. 37 */
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
l_int|5
comma
multiline_comment|/* 38 .. 3f */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 40 .. 47 */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 48 .. 4f */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 50 .. 57 */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 58 .. 5f */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 60 .. 67 */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 68 .. 6f */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 70 .. 77 */
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
l_int|6
comma
multiline_comment|/* 78 .. 7f */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* 80 .. 87 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* 88 .. 8f */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* 90 .. 97 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* 98 .. 9f */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* a0 .. a7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* a8 .. af */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* b0 .. b7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* b8 .. bf */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* c0 .. c7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* c8 .. cf */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* d0 .. d7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* d8 .. df */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* e0 .. e7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* e8 .. ef */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* f0 .. f7 */
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
l_int|7
comma
multiline_comment|/* f8 .. ff */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Count of bits set in byte, 0..8.&n; */
DECL|variable|xfs_countbit
r_static
r_const
r_char
id|xfs_countbit
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
multiline_comment|/* 00 .. 07 */
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 08 .. 0f */
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 10 .. 17 */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 18 .. 1f */
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 20 .. 27 */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 28 .. 2f */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 30 .. 37 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* 38 .. 3f */
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 40 .. 47 */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 48 .. 4f */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 50 .. 57 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* 58 .. 5f */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 60 .. 67 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* 68 .. 6f */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* 70 .. 77 */
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
multiline_comment|/* 78 .. 7f */
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
multiline_comment|/* 80 .. 87 */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 88 .. 8f */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* 90 .. 97 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* 98 .. 9f */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* a0 .. a7 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* a8 .. af */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* b0 .. b7 */
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
multiline_comment|/* b8 .. bf */
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
multiline_comment|/* c0 .. c7 */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* c8 .. cf */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* d0 .. d7 */
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
multiline_comment|/* d8 .. df */
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|5
comma
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
multiline_comment|/* e0 .. e7 */
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
multiline_comment|/* e8 .. ef */
l_int|4
comma
l_int|5
comma
l_int|5
comma
l_int|6
comma
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
multiline_comment|/* f0 .. f7 */
l_int|5
comma
l_int|6
comma
l_int|6
comma
l_int|7
comma
l_int|6
comma
l_int|7
comma
l_int|7
comma
l_int|8
comma
multiline_comment|/* f8 .. ff */
)brace
suffix:semicolon
multiline_comment|/*&n; * xfs_highbit32: get high bit set out of 32-bit argument, -1 if none set.&n; */
r_inline
r_int
DECL|function|xfs_highbit32
id|xfs_highbit32
c_func
(paren
id|__uint32_t
id|v
)paren
(brace
macro_line|#ifdef HAVE_ARCH_HIGHBIT
r_return
id|highbit32
c_func
(paren
id|v
)paren
suffix:semicolon
macro_line|#else
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|v
op_amp
l_int|0xffff0000
)paren
r_if
c_cond
(paren
id|v
op_amp
l_int|0xff000000
)paren
id|i
op_assign
l_int|24
suffix:semicolon
r_else
id|i
op_assign
l_int|16
suffix:semicolon
r_else
r_if
c_cond
(paren
id|v
op_amp
l_int|0x0000ffff
)paren
r_if
c_cond
(paren
id|v
op_amp
l_int|0x0000ff00
)paren
id|i
op_assign
l_int|8
suffix:semicolon
r_else
id|i
op_assign
l_int|0
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|i
op_plus
id|xfs_highbit
(braket
(paren
id|v
op_rshift
id|i
)paren
op_amp
l_int|0xff
)braket
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * xfs_lowbit64: get low bit set out of 64-bit argument, -1 if none set.&n; */
r_int
DECL|function|xfs_lowbit64
id|xfs_lowbit64
c_func
(paren
id|__uint64_t
id|v
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|ffs
c_func
(paren
(paren
r_int
)paren
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
id|n
op_assign
id|ffs
c_func
(paren
id|v
op_rshift
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
l_int|0
)paren
id|n
op_add_assign
l_int|32
suffix:semicolon
)brace
r_return
id|n
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * xfs_highbit64: get high bit set out of 64-bit argument, -1 if none set.&n; */
r_int
DECL|function|xfs_highbit64
id|xfs_highbit64
c_func
(paren
id|__uint64_t
id|v
)paren
(brace
id|__uint32_t
id|h
op_assign
id|v
op_rshift
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|h
)paren
r_return
id|xfs_highbit32
c_func
(paren
id|h
)paren
op_plus
l_int|32
suffix:semicolon
r_return
id|xfs_highbit32
c_func
(paren
(paren
id|__u32
)paren
id|v
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Count the number of bits set in the bitmap starting with bit&n; * start_bit.  Size is the size of the bitmap in words.&n; *&n; * Do the counting by mapping a byte value to the number of set&n; * bits for that value using the xfs_countbit array, i.e.&n; * xfs_countbit[0] == 0, xfs_countbit[1] == 1, xfs_countbit[2] == 1,&n; * xfs_countbit[3] == 2, etc.&n; */
r_int
DECL|function|xfs_count_bits
id|xfs_count_bits
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
(brace
r_register
r_int
id|bits
suffix:semicolon
r_register
r_int
r_char
op_star
id|bytep
suffix:semicolon
r_register
r_int
r_char
op_star
id|end_map
suffix:semicolon
r_int
id|byte_bit
suffix:semicolon
id|bits
op_assign
l_int|0
suffix:semicolon
id|end_map
op_assign
(paren
r_char
op_star
)paren
(paren
id|map
op_plus
id|size
)paren
suffix:semicolon
id|bytep
op_assign
(paren
r_char
op_star
)paren
(paren
id|map
op_plus
(paren
id|start_bit
op_amp
op_complement
l_int|0x7
)paren
)paren
suffix:semicolon
id|byte_bit
op_assign
id|start_bit
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/*&n;&t; * If the caller fell off the end of the map, return 0.&n;&t; */
r_if
c_cond
(paren
id|bytep
op_ge
id|end_map
)paren
(brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If start_bit is not byte aligned, then process the&n;&t; * first byte separately.&n;&t; */
r_if
c_cond
(paren
id|byte_bit
op_ne
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Shift off the bits we don&squot;t want to look at,&n;&t;&t; * before indexing into xfs_countbit.&n;&t;&t; */
id|bits
op_add_assign
id|xfs_countbit
(braket
(paren
op_star
id|bytep
op_rshift
id|byte_bit
)paren
)braket
suffix:semicolon
id|bytep
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Count the bits in each byte until the end of the bitmap.&n;&t; */
r_while
c_loop
(paren
id|bytep
OL
id|end_map
)paren
(brace
id|bits
op_add_assign
id|xfs_countbit
(braket
op_star
id|bytep
)braket
suffix:semicolon
id|bytep
op_increment
suffix:semicolon
)brace
r_return
(paren
id|bits
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Count the number of contiguous bits set in the bitmap starting with bit&n; * start_bit.  Size is the size of the bitmap in words.&n; */
r_int
DECL|function|xfs_contig_bits
id|xfs_contig_bits
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
(brace
macro_line|#if BITS_PER_LONG == 32
r_return
id|find_next_zero_bit
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|map
comma
id|size
op_star
r_sizeof
(paren
id|uint
)paren
op_star
l_int|8
comma
id|start_bit
)paren
op_minus
id|start_bit
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * The first argument to find_next_zero_bit needs to be aligned,&n;&t; * but this is coming from the xfs_buf_log_format_t on-disk&n;&t; * struct, which can&squot;t be padded or otherwise modified w/o breaking&n;&t; * on-disk compatibility... so create a temporary, aligned&n;&t; * variable, copy over the bitmap, and send that to find_next_zero_bit&n;&t; * This only happens in recovery, so it&squot;s ugly but not too bad.&n;&t; */
r_void
op_star
id|addr
suffix:semicolon
r_int
id|bit
suffix:semicolon
r_int
id|bitmap_size
op_assign
id|size
op_star
r_sizeof
(paren
id|uint
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|kmem_alloc
c_func
(paren
id|bitmap_size
comma
id|KM_SLEEP
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|addr
comma
id|map
comma
id|size
op_star
r_sizeof
(paren
id|uint
)paren
)paren
suffix:semicolon
id|bit
op_assign
id|find_next_zero_bit
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
comma
id|size
op_star
r_sizeof
(paren
id|uint
)paren
op_star
l_int|8
comma
id|start_bit
)paren
op_minus
id|start_bit
suffix:semicolon
id|kmem_free
c_func
(paren
id|addr
comma
id|bitmap_size
)paren
suffix:semicolon
r_return
id|bit
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * This takes the bit number to start looking from and&n; * returns the next set bit from there.&t; It returns -1&n; * if there are no more bits set or the start bit is&n; * beyond the end of the bitmap.&n; *&n; * Size is the number of words, not bytes, in the bitmap.&n; */
DECL|function|xfs_next_bit
r_int
id|xfs_next_bit
c_func
(paren
id|uint
op_star
id|map
comma
id|uint
id|size
comma
id|uint
id|start_bit
)paren
(brace
id|uint
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|map
)paren
op_plus
(paren
id|start_bit
op_rshift
id|BIT_TO_WORD_SHIFT
)paren
suffix:semicolon
id|uint
id|result
op_assign
id|start_bit
op_amp
op_complement
(paren
id|NBWORD
op_minus
l_int|1
)paren
suffix:semicolon
id|uint
id|tmp
suffix:semicolon
id|size
op_lshift_assign
id|BIT_TO_WORD_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|start_bit
op_ge
id|size
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|size
op_sub_assign
id|result
suffix:semicolon
id|start_bit
op_and_assign
(paren
id|NBWORD
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_bit
)paren
(brace
id|tmp
op_assign
op_star
id|p
op_increment
suffix:semicolon
multiline_comment|/* set to zero first offset bits */
id|tmp
op_and_assign
(paren
op_complement
l_int|0U
op_lshift
id|start_bit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|NBWORD
)paren
r_goto
id|found_first
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|0U
)paren
r_goto
id|found_middle
suffix:semicolon
id|size
op_sub_assign
id|NBWORD
suffix:semicolon
id|result
op_add_assign
id|NBWORD
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|NBWORD
)paren
(brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|0U
)paren
r_goto
id|found_middle
suffix:semicolon
id|result
op_add_assign
id|NBWORD
suffix:semicolon
id|size
op_sub_assign
id|NBWORD
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|tmp
op_assign
op_star
id|p
suffix:semicolon
id|found_first
suffix:colon
id|found_middle
suffix:colon
r_return
id|result
op_plus
id|ffs
c_func
(paren
id|tmp
)paren
op_minus
l_int|1
suffix:semicolon
)brace
eof
