multiline_comment|/* &n; * Coda File System, Linux Kernel module&n; * &n; * Original version, adapted from cfs_mach.c, (C) Carnegie Mellon University&n; * Linux modifications (C) 1996, Peter J. Braam&n; * Rewritten for Linux 2.1 (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon University encourages users of this software to&n; * contribute improvements to the Coda project.&n; */
macro_line|#ifndef _LINUX_CODA_FS
DECL|macro|_LINUX_CODA_FS
mdefine_line|#define _LINUX_CODA_FS
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt; 
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/wait.h&gt;&t;&t;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
multiline_comment|/* operations */
r_extern
r_struct
id|inode_operations
id|coda_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|coda_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|coda_ioctl_inode_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|coda_file_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|coda_symlink_aops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_ioctl_operations
suffix:semicolon
multiline_comment|/* operations shared over more than one file */
r_int
id|coda_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_flush
c_func
(paren
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_release
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
r_int
id|coda_revalidate_inode
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|coda_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|kstat
op_star
)paren
suffix:semicolon
r_int
id|coda_setattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_int
id|coda_isnullfid
c_func
(paren
id|ViceFid
op_star
id|fid
)paren
suffix:semicolon
multiline_comment|/* global variables */
r_extern
r_int
id|coda_fake_statfs
suffix:semicolon
multiline_comment|/* this file:  heloers */
r_static
id|__inline__
r_struct
id|ViceFid
op_star
id|coda_i2f
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
id|__inline__
r_char
op_star
id|coda_i2s
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
id|__inline__
r_void
id|coda_flag_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
id|flag
)paren
suffix:semicolon
r_char
op_star
id|coda_f2s
c_func
(paren
id|ViceFid
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_isroot
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
suffix:semicolon
r_int
id|coda_iscontrol
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|length
)paren
suffix:semicolon
r_void
id|coda_load_creds
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred
)paren
suffix:semicolon
r_void
id|coda_vattr_to_iattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|coda_vattr
op_star
)paren
suffix:semicolon
r_void
id|coda_iattr_to_vattr
c_func
(paren
r_struct
id|iattr
op_star
comma
r_struct
id|coda_vattr
op_star
)paren
suffix:semicolon
r_int
r_int
id|coda_flags_to_cflags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|print_vattr
c_func
(paren
r_struct
id|coda_vattr
op_star
id|attr
)paren
suffix:semicolon
r_int
id|coda_cred_ok
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred
)paren
suffix:semicolon
r_int
id|coda_cred_eq
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred1
comma
r_struct
id|coda_cred
op_star
id|cred2
)paren
suffix:semicolon
multiline_comment|/* sysctl.h */
r_void
id|coda_sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coda_sysctl_clean
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|CODA_ALLOC
mdefine_line|#define CODA_ALLOC(ptr, cast, size) do { &bslash;&n;    if (size &lt; PAGE_SIZE) &bslash;&n;        ptr = (cast)kmalloc((unsigned long) size, GFP_KERNEL); &bslash;&n;    else &bslash;&n;        ptr = (cast)vmalloc((unsigned long) size); &bslash;&n;    if (!ptr) &bslash;&n;        printk(&quot;kernel malloc returns 0 at %s:%d&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;    else memset( ptr, 0, size ); &bslash;&n;} while (0)
DECL|macro|CODA_FREE
mdefine_line|#define CODA_FREE(ptr,size) &bslash;&n;    do { if (size &lt; PAGE_SIZE) kfree((ptr)); else vfree((ptr)); } while (0)
multiline_comment|/* inode to cnode access functions */
DECL|function|ITOC
r_static
r_inline
r_struct
id|coda_inode_info
op_star
id|ITOC
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|coda_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|coda_i2f
r_static
id|__inline__
r_struct
id|ViceFid
op_star
id|coda_i2f
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
op_amp
(paren
id|ITOC
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|c_fid
)paren
suffix:semicolon
)brace
DECL|function|coda_i2s
r_static
id|__inline__
r_char
op_star
id|coda_i2s
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|coda_f2s
c_func
(paren
op_amp
(paren
id|ITOC
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|c_fid
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* this will not zap the inode away */
DECL|function|coda_flag_inode
r_static
id|__inline__
r_void
id|coda_flag_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
(brace
id|ITOC
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|c_flags
op_or_assign
id|flag
suffix:semicolon
)brace
macro_line|#endif
eof
