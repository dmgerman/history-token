multiline_comment|/*  Generic MTRR (Memory Type Range Register) ioctls.&n;&n;    Copyright (C) 1997-1999  Richard Gooch&n;&n;    This library is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU Library General Public&n;    License as published by the Free Software Foundation; either&n;    version 2 of the License, or (at your option) any later version.&n;&n;    This library is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    Library General Public License for more details.&n;&n;    You should have received a copy of the GNU Library General Public&n;    License along with this library; if not, write to the Free&n;    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Richard Gooch may be reached by email at  rgooch@atnf.csiro.au&n;    The postal address is:&n;      Richard Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.&n;*/
macro_line|#ifndef _LINUX_MTRR_H
DECL|macro|_LINUX_MTRR_H
mdefine_line|#define _LINUX_MTRR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|MTRR_IOCTL_BASE
mdefine_line|#define&t;MTRR_IOCTL_BASE&t;&squot;M&squot;
DECL|struct|mtrr_sentry
r_struct
id|mtrr_sentry
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/*  Base address     */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/*  Size of region   */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*  Type of region   */
)brace
suffix:semicolon
DECL|struct|mtrr_gentry
r_struct
id|mtrr_gentry
(brace
DECL|member|regnum
r_int
r_int
id|regnum
suffix:semicolon
multiline_comment|/*  Register number  */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/*  Base address     */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/*  Size of region   */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*  Type of region   */
)brace
suffix:semicolon
multiline_comment|/*  These are the various ioctls  */
DECL|macro|MTRRIOC_ADD_ENTRY
mdefine_line|#define MTRRIOC_ADD_ENTRY        _IOW(MTRR_IOCTL_BASE,  0, struct mtrr_sentry)
DECL|macro|MTRRIOC_SET_ENTRY
mdefine_line|#define MTRRIOC_SET_ENTRY        _IOW(MTRR_IOCTL_BASE,  1, struct mtrr_sentry)
DECL|macro|MTRRIOC_DEL_ENTRY
mdefine_line|#define MTRRIOC_DEL_ENTRY        _IOW(MTRR_IOCTL_BASE,  2, struct mtrr_sentry)
DECL|macro|MTRRIOC_GET_ENTRY
mdefine_line|#define MTRRIOC_GET_ENTRY        _IOWR(MTRR_IOCTL_BASE, 3, struct mtrr_gentry)
DECL|macro|MTRRIOC_KILL_ENTRY
mdefine_line|#define MTRRIOC_KILL_ENTRY       _IOW(MTRR_IOCTL_BASE,  4, struct mtrr_sentry)
DECL|macro|MTRRIOC_ADD_PAGE_ENTRY
mdefine_line|#define MTRRIOC_ADD_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  5, struct mtrr_sentry)
DECL|macro|MTRRIOC_SET_PAGE_ENTRY
mdefine_line|#define MTRRIOC_SET_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  6, struct mtrr_sentry)
DECL|macro|MTRRIOC_DEL_PAGE_ENTRY
mdefine_line|#define MTRRIOC_DEL_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  7, struct mtrr_sentry)
DECL|macro|MTRRIOC_GET_PAGE_ENTRY
mdefine_line|#define MTRRIOC_GET_PAGE_ENTRY   _IOWR(MTRR_IOCTL_BASE, 8, struct mtrr_gentry)
DECL|macro|MTRRIOC_KILL_PAGE_ENTRY
mdefine_line|#define MTRRIOC_KILL_PAGE_ENTRY  _IOW(MTRR_IOCTL_BASE,  9, struct mtrr_sentry)
multiline_comment|/*  These are the region types  */
DECL|macro|MTRR_TYPE_UNCACHABLE
mdefine_line|#define MTRR_TYPE_UNCACHABLE 0
DECL|macro|MTRR_TYPE_WRCOMB
mdefine_line|#define MTRR_TYPE_WRCOMB     1
multiline_comment|/*#define MTRR_TYPE_         2*/
multiline_comment|/*#define MTRR_TYPE_         3*/
DECL|macro|MTRR_TYPE_WRTHROUGH
mdefine_line|#define MTRR_TYPE_WRTHROUGH  4
DECL|macro|MTRR_TYPE_WRPROT
mdefine_line|#define MTRR_TYPE_WRPROT     5
DECL|macro|MTRR_TYPE_WRBACK
mdefine_line|#define MTRR_TYPE_WRBACK     6
DECL|macro|MTRR_NUM_TYPES
mdefine_line|#define MTRR_NUM_TYPES       7
macro_line|#ifdef MTRR_NEED_STRINGS
DECL|variable|mtrr_strings
r_static
r_char
op_star
id|mtrr_strings
(braket
id|MTRR_NUM_TYPES
)braket
op_assign
(brace
l_string|&quot;uncachable&quot;
comma
multiline_comment|/* 0 */
l_string|&quot;write-combining&quot;
comma
multiline_comment|/* 1 */
l_string|&quot;?&quot;
comma
multiline_comment|/* 2 */
l_string|&quot;?&quot;
comma
multiline_comment|/* 3 */
l_string|&quot;write-through&quot;
comma
multiline_comment|/* 4 */
l_string|&quot;write-protect&quot;
comma
multiline_comment|/* 5 */
l_string|&quot;write-back&quot;
comma
multiline_comment|/* 6 */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*  The following functions are for use by other drivers  */
macro_line|# ifdef CONFIG_MTRR
r_extern
r_int
id|mtrr_add
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
suffix:semicolon
r_extern
r_int
id|mtrr_add_page
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
suffix:semicolon
r_extern
r_int
id|mtrr_del
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|mtrr_del_page
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
suffix:semicolon
macro_line|#  else
DECL|function|mtrr_add
r_static
id|__inline__
r_int
id|mtrr_add
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|mtrr_add_page
r_static
id|__inline__
r_int
id|mtrr_add_page
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|mtrr_del
r_static
id|__inline__
r_int
id|mtrr_del
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|mtrr_del_page
r_static
id|__inline__
r_int
id|mtrr_del_page
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#  endif
multiline_comment|/*  The following functions are for initialisation: don&squot;t use them!  */
r_extern
r_int
id|mtrr_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#  if defined(CONFIG_SMP) &amp;&amp; defined(CONFIG_MTRR)
r_extern
r_void
id|mtrr_init_boot_cpu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mtrr_init_secondary_cpu
(paren
r_void
)paren
suffix:semicolon
macro_line|#  endif
macro_line|#endif
macro_line|#endif  /*  _LINUX_MTRR_H  */
eof
