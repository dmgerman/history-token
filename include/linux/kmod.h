macro_line|#ifndef __LINUX_KMOD_H__
DECL|macro|__LINUX_KMOD_H__
mdefine_line|#define __LINUX_KMOD_H__
multiline_comment|/*&n; *&t;include/linux/kmod.h&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
DECL|macro|KMOD_PATH_LEN
mdefine_line|#define KMOD_PATH_LEN 256
macro_line|#ifdef CONFIG_KMOD
multiline_comment|/* modprobe exit status on success, -ve on error.  Return value&n; * usually useless though. */
r_extern
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|name
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
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
macro_line|#else
DECL|function|request_module
r_static
r_inline
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|name
comma
dot
dot
dot
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|try_then_request_module
mdefine_line|#define try_then_request_module(x, mod...) ((x) ?: (request_module(mod), (x)))
r_extern
r_int
id|call_usermodehelper
c_func
(paren
r_char
op_star
id|path
comma
r_char
op_star
id|argv
(braket
)braket
comma
r_char
op_star
id|envp
(braket
)braket
comma
r_int
id|wait
)paren
suffix:semicolon
r_extern
r_void
id|usermodehelper_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_KMOD_H__ */
eof
