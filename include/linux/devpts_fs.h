multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/include/linux/devpts_fs.h&n; *&n; *  Copyright 1998-2004 H. Peter Anvin -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#ifndef _LINUX_DEVPTS_FS_H
DECL|macro|_LINUX_DEVPTS_FS_H
mdefine_line|#define _LINUX_DEVPTS_FS_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifdef CONFIG_UNIX98_PTYS
r_int
id|devpts_pty_new
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
multiline_comment|/* mknod in devpts */
r_struct
id|tty_struct
op_star
id|devpts_get_tty
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
multiline_comment|/* get tty structure */
r_void
id|devpts_pty_kill
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
multiline_comment|/* unlink */
macro_line|#else
multiline_comment|/* Dummy stubs in the no-pty case */
DECL|function|devpts_pty_new
r_static
r_inline
r_int
id|devpts_pty_new
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|devpts_get_tty
r_static
r_inline
r_struct
id|tty_struct
op_star
id|devpts_get_tty
c_func
(paren
r_int
id|number
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devpts_pty_kill
r_static
r_inline
r_void
id|devpts_pty_kill
c_func
(paren
r_int
id|number
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_DEVPTS_FS_H */
eof
