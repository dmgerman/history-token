multiline_comment|/*&n; * Copyright (c) 2002 Red Hat, Inc. All rights reserved.&n; *&n; * This software may be freely redistributed under the terms of the&n; * GNU General Public License.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Authors: David Howells &lt;dhowells@redhat.com&gt;&n; *          David Woodhouse &lt;dwmw2@cambridge.redhat.com&gt;&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;vnode.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;cell.h&quot;
macro_line|#include &quot;cmservice.h&quot;
macro_line|#include &quot;fsclient.h&quot;
macro_line|#include &quot;super.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|macro|AFS_FS_MAGIC
mdefine_line|#define AFS_FS_MAGIC 0x6B414653 /* &squot;kAFS&squot; */
DECL|struct|afs_mount_params
r_struct
id|afs_mount_params
(brace
DECL|member|rwpath
r_int
id|rwpath
suffix:semicolon
DECL|member|default_cell
r_struct
id|afs_cell
op_star
id|default_cell
suffix:semicolon
DECL|member|volume
r_struct
id|afs_volume
op_star
id|volume
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|afs_i_init_once
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
suffix:semicolon
r_static
r_struct
id|super_block
op_star
id|afs_get_sb
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
suffix:semicolon
r_static
r_struct
id|inode
op_star
id|afs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_void
id|afs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_static
r_void
id|afs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
DECL|variable|afs_fs_type
r_static
r_struct
id|file_system_type
id|afs_fs_type
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
l_string|&quot;afs&quot;
comma
dot
id|get_sb
op_assign
id|afs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_anon_super
comma
)brace
suffix:semicolon
DECL|variable|afs_super_ops
r_static
r_struct
id|super_operations
id|afs_super_ops
op_assign
(brace
dot
id|statfs
op_assign
id|simple_statfs
comma
dot
id|alloc_inode
op_assign
id|afs_alloc_inode
comma
dot
id|drop_inode
op_assign
id|generic_delete_inode
comma
dot
id|destroy_inode
op_assign
id|afs_destroy_inode
comma
dot
id|clear_inode
op_assign
id|afs_clear_inode
comma
dot
id|put_super
op_assign
id|afs_put_super
comma
)brace
suffix:semicolon
DECL|variable|afs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|afs_inode_cachep
suffix:semicolon
DECL|variable|afs_count_active_inodes
r_static
id|atomic_t
id|afs_count_active_inodes
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the filesystem&n; */
DECL|function|afs_fs_init
r_int
id|__init
id|afs_fs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
macro_line|#ifdef AFS_AUTOMOUNT_SUPPORT
id|afs_timer_init
c_func
(paren
op_amp
id|afs_mntpt_expiry_timer
comma
op_amp
id|afs_mntpt_expiry_timer_ops
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* create ourselves an inode cache */
id|atomic_set
c_func
(paren
op_amp
id|afs_count_active_inodes
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|afs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;afs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|afs_vnode
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|afs_i_init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|afs_inode_cachep
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;kAFS: Failed to allocate inode cache&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* now export our filesystem to lesser mortals */
id|ret
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|afs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|kmem_cache_destroy
c_func
(paren
id|afs_inode_cachep
)paren
suffix:semicolon
id|kleave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|kleave
c_func
(paren
l_string|&quot; = 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end afs_fs_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up the filesystem&n; */
DECL|function|afs_fs_exit
r_void
id|__exit
id|afs_fs_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|afs_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|afs_count_active_inodes
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: %d active inode objects still present&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|afs_count_active_inodes
)paren
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|kmem_cache_destroy
c_func
(paren
id|afs_inode_cachep
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_fs_exit() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * check that an argument has a value&n; */
DECL|function|want_arg
r_static
r_int
id|want_arg
c_func
(paren
r_char
op_star
op_star
id|_value
comma
r_const
r_char
op_star
id|option
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|_value
op_logical_or
op_logical_neg
op_star
id|_value
op_logical_or
op_logical_neg
op_star
op_star
id|_value
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;kAFS: %s: argument missing&bslash;n&quot;
comma
id|option
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end want_arg() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * check that there&squot;s no subsequent value&n; */
DECL|function|want_no_value
r_static
r_int
id|want_no_value
c_func
(paren
r_char
op_star
r_const
op_star
id|_value
comma
r_const
r_char
op_star
id|option
)paren
(brace
r_if
c_cond
(paren
op_star
id|_value
op_logical_and
op_star
op_star
id|_value
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;kAFS: %s: Invalid argument: %s&bslash;n&quot;
comma
id|option
comma
op_star
id|_value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end want_no_value() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * parse the mount options&n; * - this function has been shamelessly adapted from the ext3 fs which&n; *   shamelessly adapted it from the msdos fs&n; */
DECL|function|afs_super_parse_options
r_static
r_int
id|afs_super_parse_options
c_func
(paren
r_struct
id|afs_mount_params
op_star
id|params
comma
r_char
op_star
id|options
comma
r_const
r_char
op_star
op_star
id|devname
)paren
(brace
r_char
op_star
id|key
comma
op_star
id|value
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;%s&quot;
comma
id|options
)paren
suffix:semicolon
id|options
(braket
id|PAGE_SIZE
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|key
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
)paren
(brace
id|value
op_assign
id|strchr
c_func
(paren
id|key
comma
l_char|&squot;=&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kAFS: KEY: %s, VAL:%s&bslash;n&quot;
comma
id|key
comma
id|value
ques
c_cond
suffix:colon
l_string|&quot;-&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;rwpath&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|want_no_value
c_func
(paren
op_amp
id|value
comma
l_string|&quot;rwpath&quot;
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|params-&gt;rwpath
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;vol&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|want_arg
c_func
(paren
op_amp
id|value
comma
l_string|&quot;vol&quot;
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|devname
op_assign
id|value
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|key
comma
l_string|&quot;cell&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|want_arg
c_func
(paren
op_amp
id|value
comma
l_string|&quot;cell&quot;
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|afs_put_cell
c_func
(paren
id|params-&gt;default_cell
)paren
suffix:semicolon
id|ret
op_assign
id|afs_cell_lookup
c_func
(paren
id|value
comma
id|strlen
c_func
(paren
id|value
)paren
comma
op_amp
id|params-&gt;default_cell
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;kAFS: Unknown mount option: &squot;%s&squot;&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|error
suffix:colon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_super_parse_options() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * check a superblock to see if it&squot;s the one we&squot;re looking for&n; */
DECL|function|afs_test_super
r_static
r_int
id|afs_test_super
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
id|afs_mount_params
op_star
id|params
op_assign
id|data
suffix:semicolon
r_struct
id|afs_super_info
op_star
id|as
op_assign
id|sb-&gt;s_fs_info
suffix:semicolon
r_return
id|as-&gt;volume
op_eq
id|params-&gt;volume
suffix:semicolon
)brace
multiline_comment|/* end afs_test_super() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * fill in the superblock&n; */
DECL|function|afs_fill_super
r_static
r_int
id|afs_fill_super
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
id|afs_mount_params
op_star
id|params
op_assign
id|data
suffix:semicolon
r_struct
id|afs_super_info
op_star
id|as
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|afs_fid
id|fid
suffix:semicolon
r_struct
id|dentry
op_star
id|root
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|kenter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* allocate a superblock info record */
id|as
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|afs_super_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|as
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = -ENOMEM&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|as
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|afs_super_info
)paren
)paren
suffix:semicolon
id|afs_get_volume
c_func
(paren
id|params-&gt;volume
)paren
suffix:semicolon
id|as-&gt;volume
op_assign
id|params-&gt;volume
suffix:semicolon
multiline_comment|/* fill in the superblock */
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|AFS_FS_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|afs_super_ops
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
id|as
suffix:semicolon
multiline_comment|/* allocate the root inode and dentry */
id|fid.vid
op_assign
id|as-&gt;volume-&gt;vid
suffix:semicolon
id|fid.vnode
op_assign
l_int|1
suffix:semicolon
id|fid.unique
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|afs_iget
c_func
(paren
id|sb
comma
op_amp
id|fid
comma
op_amp
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|root
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
)paren
r_goto
id|error
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|root
suffix:semicolon
id|kleave
c_func
(paren
l_string|&quot; = 0&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|afs_put_volume
c_func
(paren
id|as-&gt;volume
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
id|kleave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_fill_super() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * get an AFS superblock&n; * - TODO: don&squot;t use get_sb_nodev(), but rather call sget() directly&n; */
DECL|function|afs_get_sb
r_static
r_struct
id|super_block
op_star
id|afs_get_sb
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
id|options
)paren
(brace
r_struct
id|afs_mount_params
id|params
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;,,%s,%p&quot;
comma
id|dev_name
comma
id|options
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|params
comma
l_int|0
comma
r_sizeof
(paren
id|params
)paren
)paren
suffix:semicolon
multiline_comment|/* start the cache manager */
id|ret
op_assign
id|afscm_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* parse the options */
r_if
c_cond
(paren
id|options
)paren
(brace
id|ret
op_assign
id|afs_super_parse_options
c_func
(paren
op_amp
id|params
comma
id|options
comma
op_amp
id|dev_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_name
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: no volume name specified&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
)brace
multiline_comment|/* parse the device name */
id|ret
op_assign
id|afs_volume_lookup
c_func
(paren
id|dev_name
comma
id|params.default_cell
comma
id|params.rwpath
comma
op_amp
id|params.volume
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* allocate a deviceless superblock */
id|sb
op_assign
id|sget
c_func
(paren
id|fs_type
comma
id|afs_test_super
comma
id|set_anon_super
comma
op_amp
id|params
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
id|error
suffix:semicolon
id|sb-&gt;s_flags
op_assign
id|flags
suffix:semicolon
id|ret
op_assign
id|afs_fill_super
c_func
(paren
id|sb
comma
op_amp
id|params
comma
id|flags
op_amp
id|MS_VERBOSE
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
OL
l_int|0
)paren
(brace
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
r_goto
id|error
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_ACTIVE
suffix:semicolon
id|afs_put_volume
c_func
(paren
id|params.volume
)paren
suffix:semicolon
id|afs_put_cell
c_func
(paren
id|params.default_cell
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %p&quot;
comma
id|sb
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|error
suffix:colon
id|afs_put_volume
c_func
(paren
id|params.volume
)paren
suffix:semicolon
id|afs_put_cell
c_func
(paren
id|params.default_cell
)paren
suffix:semicolon
id|afscm_stop
c_func
(paren
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_get_sb() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * finish the unmounting process on the superblock&n; */
DECL|function|afs_put_super
r_static
r_void
id|afs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|afs_super_info
op_star
id|as
op_assign
id|sb-&gt;s_fs_info
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|afs_put_volume
c_func
(paren
id|as-&gt;volume
)paren
suffix:semicolon
id|afscm_stop
c_func
(paren
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_put_super() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise an inode cache slab element prior to any use&n; */
DECL|function|afs_i_init_once
r_static
r_void
id|afs_i_init_once
c_func
(paren
r_void
op_star
id|_vnode
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
id|afs_vnode
op_star
id|vnode
op_assign
(paren
r_struct
id|afs_vnode
op_star
)paren
id|_vnode
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
id|memset
c_func
(paren
id|vnode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|vnode
)paren
)paren
suffix:semicolon
id|inode_init_once
c_func
(paren
op_amp
id|vnode-&gt;vfs_inode
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|vnode-&gt;update_waitq
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|vnode-&gt;lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vnode-&gt;cb_link
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vnode-&gt;cb_hash_link
)paren
suffix:semicolon
id|afs_timer_init
c_func
(paren
op_amp
id|vnode-&gt;cb_timeout
comma
op_amp
id|afs_vnode_cb_timed_out_ops
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* end afs_i_init_once() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * allocate an AFS inode struct from our slab cache&n; */
DECL|function|afs_alloc_inode
r_static
r_struct
id|inode
op_star
id|afs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|afs_vnode
op_star
id|vnode
suffix:semicolon
id|vnode
op_assign
(paren
r_struct
id|afs_vnode
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|afs_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vnode
)paren
r_return
l_int|NULL
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|afs_count_active_inodes
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|vnode-&gt;fid
comma
l_int|0
comma
r_sizeof
(paren
id|vnode-&gt;fid
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|vnode-&gt;status
comma
l_int|0
comma
r_sizeof
(paren
id|vnode-&gt;status
)paren
)paren
suffix:semicolon
id|vnode-&gt;volume
op_assign
l_int|NULL
suffix:semicolon
id|vnode-&gt;update_cnt
op_assign
l_int|0
suffix:semicolon
id|vnode-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
op_amp
id|vnode-&gt;vfs_inode
suffix:semicolon
)brace
multiline_comment|/* end afs_alloc_inode() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * destroy an AFS inode struct&n; */
DECL|function|afs_destroy_inode
r_static
r_void
id|afs_destroy_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|_enter
c_func
(paren
l_string|&quot;{%lu}&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|afs_inode_cachep
comma
id|AFS_FS_I
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|afs_count_active_inodes
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_destroy_inode() */
eof
