multiline_comment|/*&n; *  linux/fs/filesystems.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  table of configured filesystems&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/nfsd/interface.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#if defined(CONFIG_NFSD_MODULE)
DECL|variable|nfsd_linkage
r_struct
id|nfsd_linkage
op_star
id|nfsd_linkage
op_assign
l_int|NULL
suffix:semicolon
r_int
DECL|function|sys_nfsservctl
id|asmlinkage
id|sys_nfsservctl
c_func
(paren
r_int
id|cmd
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfsd_linkage
op_logical_or
(paren
id|request_module
(paren
l_string|&quot;nfsd&quot;
)paren
op_eq
l_int|0
op_logical_and
id|nfsd_linkage
)paren
)paren
id|ret
op_assign
id|nfsd_linkage
op_member_access_from_pointer
id|do_nfsservctl
c_func
(paren
id|cmd
comma
id|argp
comma
id|resp
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|nfsd_linkage
id|EXPORT_SYMBOL
c_func
(paren
id|nfsd_linkage
)paren
suffix:semicolon
macro_line|#elif ! defined (CONFIG_NFSD)
DECL|function|sys_nfsservctl
id|asmlinkage
r_int
id|sys_nfsservctl
c_func
(paren
r_int
id|cmd
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NFSD */
eof
