multiline_comment|/*&n; *  sysctl.c&n; *  System control stuff&n; *&n; *  Copyright (C) 1997 Martin von L&#xfffd;wis&n; *  Copyright (C) 1997 R&#xfffd;gis Duchesne&n; *&n; */
macro_line|#include &quot;sysctl.h&quot;
macro_line|#ifdef DEBUG
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
DECL|variable|ntdebug
r_int
id|ntdebug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Add or remove the debug sysctl&n; * Is this really the only file system with sysctls ?&n; */
DECL|function|ntfs_sysctl
r_void
id|ntfs_sysctl
c_func
(paren
r_int
id|add
)paren
(brace
DECL|macro|FS_NTFS
mdefine_line|#define FS_NTFS             1
multiline_comment|/* Definition of the sysctl */
r_static
id|ctl_table
id|ntfs_sysctls
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* Define the parent file : /proc/sys/fs */
r_static
id|ctl_table
id|sysctls_root
(braket
)braket
op_assign
initialization_block
suffix:semicolon
r_static
r_struct
id|ctl_table_header
op_star
id|sysctls_root_header
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|add
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sysctls_root_header
)paren
(brace
id|sysctls_root_header
op_assign
id|register_sysctl_table
c_func
(paren
id|sysctls_root
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sysctls_root_header
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|sysctls_root_header
)paren
suffix:semicolon
id|sysctls_root_header
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* DEBUG */
multiline_comment|/*&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
