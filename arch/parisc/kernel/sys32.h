multiline_comment|/* &n; *    Copyright (C) 2002 Richard Hirst &lt;rhirst at parisc-linux.org&gt;&n; *    Copyright (C) 2003 James Bottomley &lt;jejb at parisc-linux.org&gt;&n; *    Copyright (C) 2003 Randolph Chung &lt;tausq with parisc-linux.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _PARISC64_KERNEL_SYS32_H
DECL|macro|_PARISC64_KERNEL_SYS32_H
mdefine_line|#define _PARISC64_KERNEL_SYS32_H
macro_line|#include &lt;linux/compat.h&gt;
multiline_comment|/* Call a kernel syscall which will use kernel space instead of user&n; * space for its copy_to/from_user.&n; */
DECL|macro|KERNEL_SYSCALL
mdefine_line|#define KERNEL_SYSCALL(ret, syscall, args...) &bslash;&n;{ &bslash;&n;    mm_segment_t old_fs = get_fs(); &bslash;&n;    set_fs(KERNEL_DS); &bslash;&n;    ret = syscall(args); &bslash;&n;    set_fs (old_fs); &bslash;&n;}
macro_line|#ifdef CONFIG_COMPAT
DECL|typedef|__sighandler_t32
r_typedef
id|__u32
id|__sighandler_t32
suffix:semicolon
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
id|__sighandler_t32
id|sa_handler
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
