multiline_comment|/*&n; * IA32 Architecture-specific ioctl shim code&n; *&n; * Copyright (C) 2000 VA Linux Co&n; * Copyright (C) 2000 Don Dugger &lt;n0ano@valinux.com&gt;&n; * Copyright (C) 2001-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/signal.h&gt;&t;/* argh, msdos_fs.h isn&squot;t self-contained... */
macro_line|#include &quot;ia32priv.h&quot;
DECL|macro|INCLUDES
mdefine_line|#define&t;INCLUDES
macro_line|#include &quot;compat_ioctl.c&quot;
macro_line|#include &lt;asm/ioctl32.h&gt;
DECL|macro|IOCTL_NR
mdefine_line|#define IOCTL_NR(a)&t;((a) &amp; ~(_IOC_SIZEMASK &lt;&lt; _IOC_SIZESHIFT))
DECL|macro|DO_IOCTL
mdefine_line|#define DO_IOCTL(fd, cmd, arg) ({&t;&t;&t;&bslash;&n;&t;int _ret;&t;&t;&t;&t;&t;&bslash;&n;&t;mm_segment_t _old_fs = get_fs();&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(KERNEL_DS);&t;&t;&t;&t;&bslash;&n;&t;_ret = sys_ioctl(fd, cmd, (unsigned long)arg);&t;&bslash;&n;&t;set_fs(_old_fs);&t;&t;&t;&t;&bslash;&n;&t;_ret;&t;&t;&t;&t;&t;&t;&bslash;&n;})
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|macro|CODE
mdefine_line|#define CODE
macro_line|#include &quot;compat_ioctl.c&quot;
DECL|typedef|ioctl32_handler_t
r_typedef
r_int
(paren
op_star
id|ioctl32_handler_t
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|macro|COMPATIBLE_IOCTL
mdefine_line|#define COMPATIBLE_IOCTL(cmd)&t;&t;HANDLE_IOCTL((cmd),sys_ioctl)
DECL|macro|HANDLE_IOCTL
mdefine_line|#define HANDLE_IOCTL(cmd,handler)&t;{ (cmd), (ioctl32_handler_t)(handler), NULL },
DECL|macro|IOCTL_TABLE_START
mdefine_line|#define IOCTL_TABLE_START &bslash;&n;&t;struct ioctl_trans ioctl_start[] = {
DECL|macro|IOCTL_TABLE_END
mdefine_line|#define IOCTL_TABLE_END &bslash;&n;&t;};
id|IOCTL_TABLE_START
DECL|macro|DECLARES
mdefine_line|#define DECLARES
macro_line|#include &quot;compat_ioctl.c&quot;
macro_line|#include &lt;linux/compat_ioctl.h&gt;
id|IOCTL_TABLE_END
DECL|variable|ioctl_table_size
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
