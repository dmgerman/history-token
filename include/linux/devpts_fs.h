multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/include/linux/devpts_fs.h&n; *&n; *  Copyright 1998 H. Peter Anvin -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#ifndef _LINUX_DEVPTS_FS_H
DECL|macro|_LINUX_DEVPTS_FS_H
mdefine_line|#define _LINUX_DEVPTS_FS_H 1
macro_line|#ifdef CONFIG_DEVPTS_FS
r_void
id|devpts_pty_new
c_func
(paren
r_int
comma
id|dev_t
)paren
suffix:semicolon
multiline_comment|/* mknod in devpts */
r_void
id|devpts_pty_kill
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* unlink */
macro_line|#else
DECL|function|devpts_pty_new
r_static
r_inline
r_void
id|devpts_pty_new
c_func
(paren
r_int
id|line
comma
id|dev_t
id|device
)paren
(brace
)brace
DECL|function|devpts_pty_kill
r_static
r_inline
r_void
id|devpts_pty_kill
c_func
(paren
r_int
id|line
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_DEVPTS_FS_H */
eof
