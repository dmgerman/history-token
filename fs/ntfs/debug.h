multiline_comment|/*&n; * debug.h - NTFS kernel debug support. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_DEBUG_H
DECL|macro|_LINUX_NTFS_DEBUG_H
mdefine_line|#define _LINUX_NTFS_DEBUG_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;inode.h&quot;
macro_line|#include &quot;attrib.h&quot;
macro_line|#ifdef DEBUG
r_extern
r_int
id|debug_msgs
suffix:semicolon
macro_line|#if 0 /* Fool kernel-doc since it doesn&squot;t do macros yet */
multiline_comment|/**&n; * ntfs_debug - write a debug level message to syslog&n; * @f:&t;&t;a printf format string containing the message&n; * @...:&t;the variables to substitute into @f&n; *&n; * ntfs_debug() writes a DEBUG level message to the syslog but only if the&n; * driver was compiled with -DDEBUG. Otherwise, the call turns into a NOP.&n; */
r_static
r_void
id|ntfs_debug
c_func
(paren
r_const
r_char
op_star
id|f
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|__ntfs_debug
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|4
comma
l_int|5
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ntfs_debug
mdefine_line|#define ntfs_debug(f, a...)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__ntfs_debug(__FILE__, __LINE__, __FUNCTION__, f, ##a)
r_extern
r_void
id|ntfs_debug_dump_runlist
c_func
(paren
r_const
id|run_list_element
op_star
id|rl
)paren
suffix:semicolon
macro_line|#else&t;/* !DEBUG */
DECL|macro|ntfs_debug
mdefine_line|#define ntfs_debug(f, a...)&t;&t;do {} while (0)
DECL|macro|ntfs_debug_dump_runlist
mdefine_line|#define ntfs_debug_dump_runlist(rl)&t;do {} while (0)
macro_line|#endif&t;/* !DEBUG */
r_extern
r_void
id|__ntfs_warning
c_func
(paren
r_const
r_char
op_star
id|function
comma
r_const
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ntfs_warning
mdefine_line|#define ntfs_warning(sb, f, a...)&t;__ntfs_warning(__FUNCTION__, sb, f, ##a)
r_extern
r_void
id|__ntfs_error
c_func
(paren
r_const
r_char
op_star
id|function
comma
r_const
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ntfs_error
mdefine_line|#define ntfs_error(sb, f, a...)&t;&t;__ntfs_error(__FUNCTION__, sb, f, ##a)
macro_line|#endif /* _LINUX_NTFS_DEBUG_H */
eof
