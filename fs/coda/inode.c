multiline_comment|/*&n; * Super block/filesystem wide operations&n; *&n; * Copyright (C) 1996 Peter J. Braam &lt;braam@maths.ox.ac.uk&gt; and &n; * Michael Callahan &lt;callahan@maths.ox.ac.uk&gt; &n; * &n; * Rewritten for Linux 2.1.  Peter Braam &lt;braam@cs.cmu.edu&gt;&n; * Copyright (C) Carnegie Mellon University&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
multiline_comment|/* VFS super_block ops */
r_static
r_void
id|coda_clear_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|coda_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|coda_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|buf
)paren
suffix:semicolon
DECL|variable|coda_inode_cachep
r_static
id|kmem_cache_t
op_star
id|coda_inode_cachep
suffix:semicolon
DECL|function|coda_alloc_inode
r_static
r_struct
id|inode
op_star
id|coda_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|coda_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|coda_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ei
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ei-&gt;c_fid
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|CodaFid
)paren
)paren
suffix:semicolon
id|ei-&gt;c_flags
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;c_uid
op_assign
l_int|0
suffix:semicolon
id|ei-&gt;c_cached_perm
op_assign
l_int|0
suffix:semicolon
r_return
op_amp
id|ei-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|coda_destroy_inode
r_static
r_void
id|coda_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|coda_inode_cachep
comma
id|ITOC
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|coda_inode_info
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
id|inode_init_once
c_func
(paren
op_amp
id|ei-&gt;vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|coda_init_inodecache
r_int
id|coda_init_inodecache
c_func
(paren
r_void
)paren
(brace
id|coda_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;coda_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|coda_inode_info
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_RECLAIM_ACCOUNT
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|coda_inode_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_destroy_inodecache
r_void
id|coda_destroy_inodecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|coda_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;coda_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* exported operations */
DECL|variable|coda_super_operations
r_struct
id|super_operations
id|coda_super_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|coda_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|coda_destroy_inode
comma
dot
id|clear_inode
op_assign
id|coda_clear_inode
comma
dot
id|put_super
op_assign
id|coda_put_super
comma
dot
id|statfs
op_assign
id|coda_statfs
comma
)brace
suffix:semicolon
DECL|function|get_device_index
r_static
r_int
id|get_device_index
c_func
(paren
r_struct
id|coda_mount_data
op_star
id|data
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: Bad mount data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;version
op_ne
id|CODA_MOUNT_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: Bad mount version&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|file
op_assign
id|fget
c_func
(paren
id|data-&gt;fd
)paren
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_or
id|imajor
c_func
(paren
id|inode
)paren
op_ne
id|CODA_PSDEV_MAJOR
)paren
(brace
r_if
c_cond
(paren
id|file
)paren
(brace
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: Bad file&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|idx
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
op_logical_or
id|idx
op_ge
id|MAX_CODADEVS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: Bad minor number&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|idx
suffix:semicolon
)brace
DECL|function|coda_fill_super
r_static
r_int
id|coda_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|root
op_assign
l_int|0
suffix:semicolon
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|venus_comm
op_star
id|vc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|CodaFid
id|fid
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|idx
op_assign
id|get_device_index
c_func
(paren
(paren
r_struct
id|coda_mount_data
op_star
)paren
id|data
)paren
suffix:semicolon
multiline_comment|/* Ignore errors in data, for backward compatibility */
r_if
c_cond
(paren
id|idx
op_eq
op_minus
l_int|1
)paren
(brace
id|idx
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;coda_read_super: device index: %i&bslash;n&quot;
comma
id|idx
)paren
suffix:semicolon
id|vc
op_assign
op_amp
id|coda_comms
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vc-&gt;vc_inuse
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: No pseudo device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vc-&gt;vc_sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: Device already mounted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|coda_sb_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbi
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|vc-&gt;vc_sb
op_assign
id|sb
suffix:semicolon
id|sbi-&gt;sbi_vcomm
op_assign
id|vc
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|sbi
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
multiline_comment|/* probably even noatime */
id|sb-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
multiline_comment|/* XXXXX  what do we put here?? */
id|sb-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|CODA_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|coda_super_operations
suffix:semicolon
multiline_comment|/* get root fid from Venus: this needs the root inode */
id|error
op_assign
id|venus_rootfid
c_func
(paren
id|sb
comma
op_amp
id|fid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: coda_get_rootfid failed with %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: rootfid is %s&bslash;n&quot;
comma
id|coda_f2s
c_func
(paren
op_amp
id|fid
)paren
)paren
suffix:semicolon
multiline_comment|/* make root inode */
id|error
op_assign
id|coda_cnode_make
c_func
(paren
op_amp
id|root
comma
op_amp
id|fid
comma
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|root
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failure of coda_cnode_make for root: error %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: rootinode is %ld dev %s&bslash;n&quot;
comma
id|root-&gt;i_ino
comma
id|root-&gt;i_sb-&gt;s_id
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
r_goto
id|error
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|sbi
)paren
(brace
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vc
)paren
(brace
id|vc-&gt;vc_sb
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|root
)paren
id|iput
c_func
(paren
id|root
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|coda_put_super
r_static
r_void
id|coda_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coda_sb_info
op_star
id|sbi
suffix:semicolon
id|sbi
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sbi-&gt;sbi_vcomm-&gt;vc_sb
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Coda: Bye bye.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
)brace
DECL|function|coda_clear_inode
r_static
r_void
id|coda_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|coda_cache_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|coda_getattr
r_int
id|coda_getattr
c_func
(paren
r_struct
id|vfsmount
op_star
id|mnt
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|kstat
op_star
id|stat
)paren
(brace
r_int
id|err
op_assign
id|coda_revalidate_inode
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|generic_fillattr
c_func
(paren
id|dentry-&gt;d_inode
comma
id|stat
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|coda_setattr
r_int
id|coda_setattr
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
r_struct
id|coda_vattr
id|vattr
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|vattr
comma
l_int|0
comma
r_sizeof
(paren
id|vattr
)paren
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|coda_iattr_to_vattr
c_func
(paren
id|iattr
comma
op_amp
id|vattr
)paren
suffix:semicolon
id|vattr.va_type
op_assign
id|C_VNON
suffix:semicolon
multiline_comment|/* cannot set type */
multiline_comment|/* Venus is responsible for truncating the container-file!!! */
id|error
op_assign
id|venus_setattr
c_func
(paren
id|inode-&gt;i_sb
comma
id|coda_i2f
c_func
(paren
id|inode
)paren
comma
op_amp
id|vattr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|coda_vattr_to_iattr
c_func
(paren
id|inode
comma
op_amp
id|vattr
)paren
suffix:semicolon
id|coda_cache_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|coda_file_inode_operations
r_struct
id|inode_operations
id|coda_file_inode_operations
op_assign
(brace
dot
id|permission
op_assign
id|coda_permission
comma
dot
id|getattr
op_assign
id|coda_getattr
comma
dot
id|setattr
op_assign
id|coda_setattr
comma
)brace
suffix:semicolon
DECL|function|coda_statfs
r_static
r_int
id|coda_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|buf
)paren
(brace
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|venus_statfs
c_func
(paren
id|sb
comma
id|buf
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
multiline_comment|/* fake something like AFS does */
id|buf-&gt;f_blocks
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_files
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|9000000
suffix:semicolon
)brace
multiline_comment|/* and fill in the rest */
id|buf-&gt;f_type
op_assign
id|CODA_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|1024
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|CODA_MAXNAMLEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init_coda: used by filesystems.c to register coda */
DECL|function|coda_get_sb
r_static
r_struct
id|super_block
op_star
id|coda_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_nodev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|coda_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|coda_fs_type
r_struct
id|file_system_type
id|coda_fs_type
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;coda&quot;
comma
dot
id|get_sb
op_assign
id|coda_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
dot
id|fs_flags
op_assign
id|FS_BINARY_MOUNTDATA
comma
)brace
suffix:semicolon
eof
