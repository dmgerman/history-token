multiline_comment|/* &n; *    Copyright (C) 2001 Matthew Wilcox &lt;willy at parisc-linux.org&gt;&n; *    Copyright (C) 2003 Carlos O&squot;Donell &lt;carlos at parisc-linux.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _PARISC64_KERNEL_SIGNAL32_H
DECL|macro|_PARISC64_KERNEL_SIGNAL32_H
mdefine_line|#define _PARISC64_KERNEL_SIGNAL32_H
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;asm/compat_signal.h&gt;
macro_line|#include &lt;asm/compat_rt_sigframe.h&gt;
multiline_comment|/* ELF32 signal handling */
DECL|struct|k_sigaction32
r_struct
id|k_sigaction32
(brace
DECL|member|sa
r_struct
id|compat_sigaction
id|sa
suffix:semicolon
)brace
suffix:semicolon
r_void
id|sigset_32to64
c_func
(paren
id|sigset_t
op_star
id|s64
comma
id|compat_sigset_t
op_star
id|s32
)paren
suffix:semicolon
r_void
id|sigset_64to32
c_func
(paren
id|compat_sigset_t
op_star
id|s32
comma
id|sigset_t
op_star
id|s64
)paren
suffix:semicolon
r_int
id|do_sigaltstack32
(paren
r_const
id|compat_stack_t
id|__user
op_star
id|uss32
comma
id|compat_stack_t
id|__user
op_star
id|uoss32
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_int
id|restore_sigcontext32
c_func
(paren
r_struct
id|compat_sigcontext
id|__user
op_star
id|sc
comma
r_struct
id|compat_regfile
id|__user
op_star
id|rf
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|setup_sigcontext32
c_func
(paren
r_struct
id|compat_sigcontext
id|__user
op_star
id|sc
comma
r_struct
id|compat_regfile
id|__user
op_star
id|rf
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|in_syscall
)paren
suffix:semicolon
macro_line|#endif
eof
