multiline_comment|/* &n; * ioctl32.c: Conversion between 32bit and 64bit native ioctls.&n; * &n; * Based on sparc64 ioctl32.c by:&n; *&n; * Copyright (C) 1997-2000  Jakub Jelinek  (jakub@redhat.com)&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; *&n; * ppc64 changes:&n; *&n; * Copyright (C) 2000  Ken Aaker (kdaaker@rchland.vnet.ibm.com)&n; * Copyright (C) 2001  Anton Blanchard (antonb@au.ibm.com)&n; *&n; * These routines maintain argument size conversion between 32bit and 64bit&n; * ioctls.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|INCLUDES
mdefine_line|#define INCLUDES
macro_line|#include &quot;compat_ioctl.c&quot;
macro_line|#include &lt;linux/syscalls.h&gt;
DECL|macro|CODE
mdefine_line|#define CODE
macro_line|#include &quot;compat_ioctl.c&quot;
DECL|macro|HANDLE_IOCTL
mdefine_line|#define HANDLE_IOCTL(cmd,handler) { cmd, (ioctl_trans_handler_t)handler, NULL },
DECL|macro|COMPATIBLE_IOCTL
mdefine_line|#define COMPATIBLE_IOCTL(cmd) HANDLE_IOCTL(cmd,sys_ioctl)
DECL|macro|IOCTL_TABLE_START
mdefine_line|#define IOCTL_TABLE_START &bslash;&n;&t;struct ioctl_trans ioctl_start[] = {
DECL|macro|IOCTL_TABLE_END
mdefine_line|#define IOCTL_TABLE_END &bslash;&n;&t;};
id|IOCTL_TABLE_START
macro_line|#include &lt;linux/compat_ioctl.h&gt;
DECL|macro|DECLARES
mdefine_line|#define DECLARES
macro_line|#include &quot;compat_ioctl.c&quot;
id|COMPATIBLE_IOCTL
c_func
(paren
id|TCSBRKP
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|TIOCSTART
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|TIOCSTOP
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|TIOCSLTC
)paren
multiline_comment|/* Little p (/dev/rtc, /dev/envctrl, etc.) */
id|COMPATIBLE_IOCTL
c_func
(paren
id|_IOR
c_func
(paren
l_char|&squot;p&squot;
comma
l_int|20
comma
r_int
(braket
l_int|7
)braket
)paren
)paren
multiline_comment|/* RTCGET */
id|COMPATIBLE_IOCTL
c_func
(paren
id|_IOW
c_func
(paren
l_char|&squot;p&squot;
comma
l_int|21
comma
r_int
(braket
l_int|7
)braket
)paren
)paren
multiline_comment|/* RTCSET */
id|IOCTL_TABLE_END
r_int
id|ioctl_table_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|ioctl_start
)paren
suffix:semicolon
eof
