multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: super.c,v 1.79 2003/05/27 22:35:42 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &quot;nodelist.h&quot;
r_void
id|jffs2_put_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|variable|jffs2_inode_cachep
r_static
id|kmem_cache_t
op_star
id|jffs2_inode_cachep
suffix:semicolon
DECL|function|jffs2_alloc_inode
r_static
r_struct
id|inode
op_star
id|jffs2_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|jffs2_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|jffs2_inode_cachep
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
r_return
op_amp
id|ei-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|jffs2_destroy_inode
r_static
r_void
id|jffs2_destroy_inode
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
id|jffs2_inode_cachep
comma
id|JFFS2_INODE_INFO
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_i_init_once
r_static
r_void
id|jffs2_i_init_once
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
id|jffs2_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|jffs2_inode_info
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
(brace
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|ei-&gt;sem
)paren
suffix:semicolon
id|inode_init_once
c_func
(paren
op_amp
id|ei-&gt;vfs_inode
)paren
suffix:semicolon
)brace
)brace
DECL|variable|jffs2_super_operations
r_static
r_struct
id|super_operations
id|jffs2_super_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|jffs2_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|jffs2_destroy_inode
comma
dot
id|read_inode
op_assign
id|jffs2_read_inode
comma
dot
id|put_super
op_assign
id|jffs2_put_super
comma
dot
id|write_super
op_assign
id|jffs2_write_super
comma
dot
id|statfs
op_assign
id|jffs2_statfs
comma
dot
id|remount_fs
op_assign
id|jffs2_remount_fs
comma
dot
id|clear_inode
op_assign
id|jffs2_clear_inode
)brace
suffix:semicolon
DECL|function|jffs2_sb_compare
r_static
r_int
id|jffs2_sb_compare
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
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|p
op_assign
id|data
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* The superblocks are considered to be equivalent if the underlying MTD&n;&t;   device is the same one */
r_if
c_cond
(paren
id|c-&gt;mtd
op_eq
id|p-&gt;mtd
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_sb_compare: match on device %d (&bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|p-&gt;mtd-&gt;index
comma
id|p-&gt;mtd-&gt;name
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_sb_compare: No match, device %d (&bslash;&quot;%s&bslash;&quot;), device %d (&bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|c-&gt;mtd-&gt;index
comma
id|c-&gt;mtd-&gt;name
comma
id|p-&gt;mtd-&gt;index
comma
id|p-&gt;mtd-&gt;name
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|jffs2_sb_set
r_static
r_int
id|jffs2_sb_set
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
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|p
op_assign
id|data
suffix:semicolon
multiline_comment|/* For persistence of NFS exports etc. we use the same s_dev&n;&t;   each time we mount the device, don&squot;t just use an anonymous&n;&t;   device */
id|sb-&gt;s_fs_info
op_assign
id|p
suffix:semicolon
id|p-&gt;os_priv
op_assign
id|sb
suffix:semicolon
id|sb-&gt;s_dev
op_assign
id|MKDEV
c_func
(paren
id|MTD_BLOCK_MAJOR
comma
id|p-&gt;mtd-&gt;index
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|jffs2_get_sb_mtd
r_static
r_struct
id|super_block
op_star
id|jffs2_get_sb_mtd
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
comma
r_struct
id|mtd_info
op_star
id|mtd
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|jffs2_sb_info
op_star
id|c
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|c
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|c
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|c
)paren
)paren
suffix:semicolon
id|c-&gt;mtd
op_assign
id|mtd
suffix:semicolon
id|sb
op_assign
id|sget
c_func
(paren
id|fs_type
comma
id|jffs2_sb_compare
comma
id|jffs2_sb_set
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sb
)paren
)paren
r_goto
id|out_put
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_root
)paren
(brace
multiline_comment|/* New mountpoint for JFFS2 which is already mounted */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb_mtd(): Device %d (&bslash;&quot;%s&bslash;&quot;) is already mounted&bslash;n&quot;
comma
id|mtd-&gt;index
comma
id|mtd-&gt;name
)paren
)paren
suffix:semicolon
r_goto
id|out_put
suffix:semicolon
)brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb_mtd(): New superblock for device %d (&bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
id|mtd-&gt;index
comma
id|mtd-&gt;name
)paren
)paren
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|jffs2_super_operations
suffix:semicolon
id|ret
op_assign
id|jffs2_do_fill_super
c_func
(paren
id|sb
comma
id|data
comma
(paren
id|flags
op_amp
id|MS_VERBOSE
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* Failure case... */
id|up_write
c_func
(paren
op_amp
id|sb-&gt;s_umount
)paren
suffix:semicolon
id|deactivate_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb
op_assign
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
r_goto
id|out_put1
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|out_put
suffix:colon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
id|out_put1
suffix:colon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
)brace
DECL|function|jffs2_get_sb_mtdnr
r_static
r_struct
id|super_block
op_star
id|jffs2_get_sb_mtdnr
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
comma
r_int
id|mtdnr
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
id|mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
id|mtdnr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtd
)paren
(brace
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: MTD device #%u doesn&squot;t appear to exist&bslash;n&quot;
comma
id|mtdnr
)paren
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_return
id|jffs2_get_sb_mtd
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|mtd
)paren
suffix:semicolon
)brace
DECL|function|jffs2_get_sb
r_static
r_struct
id|super_block
op_star
id|jffs2_get_sb
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
r_int
id|err
suffix:semicolon
r_struct
id|nameidata
id|nd
suffix:semicolon
r_int
id|mtdnr
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_name
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb(): dev_name &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|dev_name
)paren
)paren
suffix:semicolon
multiline_comment|/* The preferred way of mounting in future; especially when&n;&t;   CONFIG_BLK_DEV is implemented - we specify the underlying&n;&t;   MTD device by number or by name, so that we don&squot;t require &n;&t;   block device support to be present in the kernel. */
multiline_comment|/* FIXME: How to do the root fs this way? */
r_if
c_cond
(paren
id|dev_name
(braket
l_int|0
)braket
op_eq
l_char|&squot;m&squot;
op_logical_and
id|dev_name
(braket
l_int|1
)braket
op_eq
l_char|&squot;t&squot;
op_logical_and
id|dev_name
(braket
l_int|2
)braket
op_eq
l_char|&squot;d&squot;
)paren
(brace
multiline_comment|/* Probably mounting without the blkdev crap */
r_if
c_cond
(paren
id|dev_name
(braket
l_int|3
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
multiline_comment|/* Mount by MTD device name */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb(): mtd:%%s, name &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|dev_name
op_plus
l_int|4
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|mtdnr
op_assign
l_int|0
suffix:semicolon
id|mtdnr
OL
id|MAX_MTD_DEVICES
suffix:semicolon
id|mtdnr
op_increment
)paren
(brace
id|mtd
op_assign
id|get_mtd_device
c_func
(paren
l_int|NULL
comma
id|mtdnr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|mtd-&gt;name
comma
id|dev_name
op_plus
l_int|4
)paren
)paren
r_return
id|jffs2_get_sb_mtd
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|mtd
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|mtd
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;jffs2_get_sb(): MTD device with name &bslash;&quot;%s&bslash;&quot; not found.&bslash;n&quot;
comma
id|dev_name
op_plus
l_int|4
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|isdigit
c_func
(paren
id|dev_name
(braket
l_int|3
)braket
)paren
)paren
(brace
multiline_comment|/* Mount by MTD device number name */
r_char
op_star
id|endptr
suffix:semicolon
id|mtdnr
op_assign
id|simple_strtoul
c_func
(paren
id|dev_name
op_plus
l_int|3
comma
op_amp
id|endptr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|endptr
)paren
(brace
multiline_comment|/* It was a valid number */
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb(): mtd%%d, mtdnr %d&bslash;n&quot;
comma
id|mtdnr
)paren
)paren
suffix:semicolon
r_return
id|jffs2_get_sb_mtdnr
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|mtdnr
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Try the old way - the hack where we allowed users to mount &n;&t;   /dev/mtdblock$(n) but didn&squot;t actually _use_ the blkdev */
id|err
op_assign
id|path_lookup
c_func
(paren
id|dev_name
comma
id|LOOKUP_FOLLOW
comma
op_amp
id|nd
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_get_sb(): path_lookup() returned %d, inode %p&bslash;n&quot;
comma
id|err
comma
id|nd.dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISBLK
c_func
(paren
id|nd.dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nd.mnt-&gt;mnt_flags
op_amp
id|MNT_NODEV
)paren
(brace
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
)brace
id|dev
op_assign
id|nd.dentry-&gt;d_inode-&gt;i_rdev
suffix:semicolon
id|path_release
c_func
(paren
op_amp
id|nd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|major
c_func
(paren
id|dev
)paren
op_ne
id|MTD_BLOCK_MAJOR
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MS_VERBOSE
)paren
)paren
multiline_comment|/* Yes I mean this. Strangely */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Attempt to mount non-MTD device &bslash;&quot;%s&bslash;&quot; as JFFS2&bslash;n&quot;
comma
id|dev_name
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_return
id|jffs2_get_sb_mtdnr
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_put_super
r_void
id|jffs2_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|D2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2: jffs2_put_super()&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|jffs2_stop_garbage_collect_thread
c_func
(paren
id|c
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|jffs2_flush_wbuf
c_func
(paren
id|c
comma
l_int|1
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|c-&gt;alloc_sem
)paren
suffix:semicolon
id|jffs2_free_ino_caches
c_func
(paren
id|c
)paren
suffix:semicolon
id|jffs2_free_raw_node_refs
c_func
(paren
id|c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c-&gt;blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;wbuf
)paren
id|kfree
c_func
(paren
id|c-&gt;wbuf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c-&gt;inocache_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;sync
)paren
id|c-&gt;mtd
op_member_access_from_pointer
id|sync
c_func
(paren
id|c-&gt;mtd
)paren
suffix:semicolon
id|D1
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;jffs2_put_super returning&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|jffs2_kill_sb
r_static
r_void
id|jffs2_kill_sb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|jffs2_sb_info
op_star
id|c
op_assign
id|JFFS2_SB_INFO
c_func
(paren
id|sb
)paren
suffix:semicolon
id|generic_shutdown_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|put_mtd_device
c_func
(paren
id|c-&gt;mtd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|variable|jffs2_fs_type
r_static
r_struct
id|file_system_type
id|jffs2_fs_type
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
l_string|&quot;jffs2&quot;
comma
dot
id|get_sb
op_assign
id|jffs2_get_sb
comma
dot
id|kill_sb
op_assign
id|jffs2_kill_sb
comma
)brace
suffix:semicolon
DECL|function|init_jffs2_fs
r_static
r_int
id|__init
id|init_jffs2_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;JFFS2 version 2.1. (C) 2001, 2002 Red Hat, Inc.&bslash;n&quot;
)paren
suffix:semicolon
id|jffs2_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;jffs2_i&quot;
comma
r_sizeof
(paren
r_struct
id|jffs2_inode_info
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
op_or
id|SLAB_RECLAIM_ACCOUNT
comma
id|jffs2_i_init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jffs2_inode_cachep
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to initialise inode cache&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_zlib_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to initialise zlib workspaces&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|jffs2_create_slab_caches
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to initialise slab caches&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_zlib
suffix:semicolon
)brace
id|ret
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|jffs2_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;JFFS2 error: Failed to register filesystem&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_slab
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_slab
suffix:colon
id|jffs2_destroy_slab_caches
c_func
(paren
)paren
suffix:semicolon
id|out_zlib
suffix:colon
id|jffs2_zlib_exit
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|exit_jffs2_fs
r_static
r_void
id|__exit
id|exit_jffs2_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|jffs2_fs_type
)paren
suffix:semicolon
id|jffs2_destroy_slab_caches
c_func
(paren
)paren
suffix:semicolon
id|jffs2_zlib_exit
c_func
(paren
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|jffs2_inode_cachep
)paren
suffix:semicolon
)brace
DECL|variable|init_jffs2_fs
id|module_init
c_func
(paren
id|init_jffs2_fs
)paren
suffix:semicolon
DECL|variable|exit_jffs2_fs
id|module_exit
c_func
(paren
id|exit_jffs2_fs
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;The Journalling Flash File System, v2&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
singleline_comment|// Actually dual-licensed, but it doesn&squot;t matter for 
singleline_comment|// the sake of this tag. It&squot;s Free Software.
eof
