multiline_comment|/*&n; * linux/fs/hfs/super.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * This file contains hfs_read_super(), some of the super_ops and&n; * init_module() and cleanup_module().&t;The remaining super_ops are in&n; * inode.c since they deal with inodes.&n; *&n; * Based on the minix file system code, (C) 1991, 1992 by Linus Torvalds&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; * The code in this file initializes some structures which contain&n; * pointers by calling memset(&amp;foo, 0, sizeof(foo)).&n; * This produces the desired behavior only due to the non-ANSI&n; * assumption that the machine representation of NULL is all zeros.&n; */
macro_line|#include &quot;hfs.h&quot;
macro_line|#include &lt;linux/hfs_fs_sb.h&gt;
macro_line|#include &lt;linux/hfs_fs_i.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_MAC_PARTITION */
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parser.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*================ Forward declarations ================*/
r_static
r_void
id|hfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|hfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|hfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|kstatfs
op_star
)paren
suffix:semicolon
r_static
r_void
id|hfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
DECL|variable|hfs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|hfs_inode_cachep
suffix:semicolon
DECL|function|hfs_alloc_inode
r_static
r_struct
id|inode
op_star
id|hfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|hfs_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|hfs_inode_cachep
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
DECL|function|hfs_destroy_inode
r_static
r_void
id|hfs_destroy_inode
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
id|hfs_inode_cachep
comma
id|HFS_I
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
id|hfs_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|hfs_inode_info
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
DECL|function|init_inodecache
r_static
r_int
id|init_inodecache
c_func
(paren
r_void
)paren
(brace
id|hfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;hfs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|hfs_inode_info
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
id|hfs_inode_cachep
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
DECL|function|destroy_inodecache
r_static
r_void
id|destroy_inodecache
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
id|hfs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hfs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*================ Global variables ================*/
DECL|variable|hfs_super_operations
r_static
r_struct
id|super_operations
id|hfs_super_operations
op_assign
(brace
dot
id|alloc_inode
op_assign
id|hfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|hfs_destroy_inode
comma
dot
id|read_inode
op_assign
id|hfs_read_inode
comma
dot
id|put_inode
op_assign
id|hfs_put_inode
comma
dot
id|put_super
op_assign
id|hfs_put_super
comma
dot
id|write_super
op_assign
id|hfs_write_super
comma
dot
id|statfs
op_assign
id|hfs_statfs
comma
)brace
suffix:semicolon
multiline_comment|/*================ File-local variables ================*/
DECL|function|hfs_get_sb
r_static
r_struct
id|super_block
op_star
id|hfs_get_sb
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
id|get_sb_bdev
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
id|hfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|hfs_fs
r_static
r_struct
id|file_system_type
id|hfs_fs
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
l_string|&quot;hfs&quot;
comma
dot
id|get_sb
op_assign
id|hfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_block_super
comma
dot
id|fs_flags
op_assign
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/* &n; * hfs_read_inode()&n; *&n; * this doesn&squot;t actually do much. hfs_iget actually fills in the &n; * necessary inode information.&n; */
DECL|function|hfs_read_inode
r_static
r_void
id|hfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_write_super()&n; *&n; * Description:&n; *   This function is called by the VFS only. When the filesystem&n; *   is mounted r/w it updates the MDB on disk.&n; * Input Variable(s):&n; *   struct super_block *sb: Pointer to the hfs superblock&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;sb&squot; points to a &quot;valid&quot; (struct super_block).&n; * Postconditions:&n; *   The MDB is marked &squot;unsuccessfully unmounted&squot; by clearing bit 8 of drAtrb&n; *   (hfs_put_super() must set this flag!). Some MDB fields are updated&n; *   and the MDB buffer is written to disk by calling hfs_mdb_commit().&n; */
DECL|function|hfs_write_super
r_static
r_void
id|hfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* is this a valid hfs superblock? */
r_if
c_cond
(paren
op_logical_neg
id|sb
op_logical_or
id|sb-&gt;s_magic
op_ne
id|HFS_SUPER_MAGIC
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
(brace
multiline_comment|/* sync everything to the buffers */
id|hfs_mdb_commit
c_func
(paren
id|mdb
comma
l_int|0
)paren
suffix:semicolon
)brace
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_put_super()&n; *&n; * This is the put_super() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to release the resources&n; * associated with the superblock sb.&n; */
DECL|function|hfs_put_super
r_static
r_void
id|hfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
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
(brace
id|hfs_mdb_commit
c_func
(paren
id|mdb
comma
l_int|0
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* release the MDB&squot;s resources */
id|hfs_mdb_put
c_func
(paren
id|mdb
comma
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sb-&gt;s_fs_info
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_statfs()&n; *&n; * This is the statfs() entry in the super_operations structure for&n; * HFS filesystems.  The purpose is to return various data about the&n; * filesystem.&n; *&n; * changed f_files/f_ffree to reflect the fs_ablock/free_ablocks.&n; */
DECL|function|hfs_statfs
r_static
r_int
id|hfs_statfs
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
r_struct
id|hfs_mdb
op_star
id|mdb
op_assign
id|HFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_mdb
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|HFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|HFS_SECTOR_SIZE
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|mdb-&gt;alloc_blksz
op_star
id|mdb-&gt;fs_ablocks
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|mdb-&gt;alloc_blksz
op_star
id|mdb-&gt;free_ablocks
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|buf-&gt;f_bfree
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|mdb-&gt;fs_ablocks
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|mdb-&gt;free_ablocks
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|HFS_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_enum
(brace
DECL|enumerator|Opt_version
DECL|enumerator|Opt_uid
DECL|enumerator|Opt_gid
DECL|enumerator|Opt_umask
DECL|enumerator|Opt_part
id|Opt_version
comma
id|Opt_uid
comma
id|Opt_gid
comma
id|Opt_umask
comma
id|Opt_part
comma
DECL|enumerator|Opt_type
DECL|enumerator|Opt_creator
DECL|enumerator|Opt_quiet
DECL|enumerator|Opt_afpd
id|Opt_type
comma
id|Opt_creator
comma
id|Opt_quiet
comma
id|Opt_afpd
comma
DECL|enumerator|Opt_names_netatalk
DECL|enumerator|Opt_names_trivial
DECL|enumerator|Opt_names_alpha
DECL|enumerator|Opt_names_latin
id|Opt_names_netatalk
comma
id|Opt_names_trivial
comma
id|Opt_names_alpha
comma
id|Opt_names_latin
comma
DECL|enumerator|Opt_names_7bit
DECL|enumerator|Opt_names_8bit
DECL|enumerator|Opt_names_cap
id|Opt_names_7bit
comma
id|Opt_names_8bit
comma
id|Opt_names_cap
comma
DECL|enumerator|Opt_fork_netatalk
DECL|enumerator|Opt_fork_single
DECL|enumerator|Opt_fork_double
DECL|enumerator|Opt_fork_cap
id|Opt_fork_netatalk
comma
id|Opt_fork_single
comma
id|Opt_fork_double
comma
id|Opt_fork_cap
comma
DECL|enumerator|Opt_case_lower
DECL|enumerator|Opt_case_asis
id|Opt_case_lower
comma
id|Opt_case_asis
comma
DECL|enumerator|Opt_conv_binary
DECL|enumerator|Opt_conv_text
DECL|enumerator|Opt_conv_auto
id|Opt_conv_binary
comma
id|Opt_conv_text
comma
id|Opt_conv_auto
comma
)brace
suffix:semicolon
DECL|variable|tokens
r_static
id|match_table_t
id|tokens
op_assign
(brace
(brace
id|Opt_version
comma
l_string|&quot;version=%u&quot;
)brace
comma
(brace
id|Opt_uid
comma
l_string|&quot;uid=%u&quot;
)brace
comma
(brace
id|Opt_gid
comma
l_string|&quot;gid=%u&quot;
)brace
comma
(brace
id|Opt_umask
comma
l_string|&quot;umask=%o&quot;
)brace
comma
(brace
id|Opt_part
comma
l_string|&quot;part=%u&quot;
)brace
comma
(brace
id|Opt_type
comma
l_string|&quot;type=%s&quot;
)brace
comma
(brace
id|Opt_creator
comma
l_string|&quot;creator=%s&quot;
)brace
comma
(brace
id|Opt_quiet
comma
l_string|&quot;quiet&quot;
)brace
comma
(brace
id|Opt_afpd
comma
l_string|&quot;afpd&quot;
)brace
comma
(brace
id|Opt_names_netatalk
comma
l_string|&quot;names=netatalk&quot;
)brace
comma
(brace
id|Opt_names_trivial
comma
l_string|&quot;names=trivial&quot;
)brace
comma
(brace
id|Opt_names_alpha
comma
l_string|&quot;names=alpha&quot;
)brace
comma
(brace
id|Opt_names_latin
comma
l_string|&quot;names=latin&quot;
)brace
comma
(brace
id|Opt_names_7bit
comma
l_string|&quot;names=7bit&quot;
)brace
comma
(brace
id|Opt_names_8bit
comma
l_string|&quot;names=8bit&quot;
)brace
comma
(brace
id|Opt_names_cap
comma
l_string|&quot;names=cap&quot;
)brace
comma
(brace
id|Opt_names_netatalk
comma
l_string|&quot;names=n&quot;
)brace
comma
(brace
id|Opt_names_trivial
comma
l_string|&quot;names=t&quot;
)brace
comma
(brace
id|Opt_names_alpha
comma
l_string|&quot;names=a&quot;
)brace
comma
(brace
id|Opt_names_latin
comma
l_string|&quot;names=l&quot;
)brace
comma
(brace
id|Opt_names_7bit
comma
l_string|&quot;names=7&quot;
)brace
comma
(brace
id|Opt_names_8bit
comma
l_string|&quot;names=8&quot;
)brace
comma
(brace
id|Opt_names_cap
comma
l_string|&quot;names=c&quot;
)brace
comma
(brace
id|Opt_fork_netatalk
comma
l_string|&quot;fork=netatalk&quot;
)brace
comma
(brace
id|Opt_fork_single
comma
l_string|&quot;fork=single&quot;
)brace
comma
(brace
id|Opt_fork_double
comma
l_string|&quot;fork=double&quot;
)brace
comma
(brace
id|Opt_fork_cap
comma
l_string|&quot;fork=cap&quot;
)brace
comma
(brace
id|Opt_fork_netatalk
comma
l_string|&quot;fork=n&quot;
)brace
comma
(brace
id|Opt_fork_single
comma
l_string|&quot;fork=s&quot;
)brace
comma
(brace
id|Opt_fork_double
comma
l_string|&quot;fork=d&quot;
)brace
comma
(brace
id|Opt_fork_cap
comma
l_string|&quot;fork=c&quot;
)brace
comma
(brace
id|Opt_case_lower
comma
l_string|&quot;case=lower&quot;
)brace
comma
(brace
id|Opt_case_asis
comma
l_string|&quot;case=asis&quot;
)brace
comma
(brace
id|Opt_case_lower
comma
l_string|&quot;case=l&quot;
)brace
comma
(brace
id|Opt_case_asis
comma
l_string|&quot;case=a&quot;
)brace
comma
(brace
id|Opt_conv_binary
comma
l_string|&quot;conv=binary&quot;
)brace
comma
(brace
id|Opt_conv_text
comma
l_string|&quot;conv=text&quot;
)brace
comma
(brace
id|Opt_conv_auto
comma
l_string|&quot;conv=auto&quot;
)brace
comma
(brace
id|Opt_conv_binary
comma
l_string|&quot;conv=b&quot;
)brace
comma
(brace
id|Opt_conv_text
comma
l_string|&quot;conv=t&quot;
)brace
comma
(brace
id|Opt_conv_auto
comma
l_string|&quot;conv=a&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * parse_options()&n; * &n; * adapted from linux/fs/msdos/inode.c written 1992,93 by Werner Almesberger&n; * This function is called by hfs_read_super() to parse the mount options.&n; */
DECL|function|parse_options
r_static
r_int
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
r_struct
id|hfs_sb_info
op_star
id|hsb
comma
r_int
op_star
id|part
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_char
id|names
comma
id|fork
suffix:semicolon
id|substring_t
id|args
(braket
id|MAX_OPT_ARGS
)braket
suffix:semicolon
r_int
id|option
suffix:semicolon
multiline_comment|/* initialize the sb with defaults */
id|memset
c_func
(paren
id|hsb
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|hsb
)paren
)paren
suffix:semicolon
id|hsb-&gt;magic
op_assign
id|HFS_SB_MAGIC
suffix:semicolon
id|hsb-&gt;s_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|hsb-&gt;s_gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|hsb-&gt;s_umask
op_assign
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|hsb-&gt;s_type
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_creator
op_assign
l_int|0x3f3f3f3f
suffix:semicolon
multiline_comment|/* == &squot;????&squot; */
id|hsb-&gt;s_lowercase
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_quiet
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_afpd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default version. 0 just selects the defaults */
id|hsb-&gt;s_version
op_assign
l_int|0
suffix:semicolon
id|hsb-&gt;s_conv
op_assign
l_char|&squot;b&squot;
suffix:semicolon
id|names
op_assign
l_char|&squot;?&squot;
suffix:semicolon
id|fork
op_assign
l_char|&squot;?&squot;
suffix:semicolon
op_star
id|part
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|p
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
op_ne
l_int|NULL
)paren
(brace
r_int
id|token
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
r_continue
suffix:semicolon
id|token
op_assign
id|match_token
c_func
(paren
id|p
comma
id|tokens
comma
id|args
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|token
)paren
(brace
multiline_comment|/* Numeric-valued options */
r_case
id|Opt_version
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_version
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_uid
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_uid
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_gid
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_gid
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_umask
suffix:colon
r_if
c_cond
(paren
id|match_octal
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hsb-&gt;s_umask
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_part
suffix:colon
r_if
c_cond
(paren
id|match_int
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
comma
op_amp
id|option
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|part
op_assign
id|option
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* String-valued options */
r_case
id|Opt_type
suffix:colon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|args
(braket
l_int|0
)braket
dot
id|from
)paren
op_ne
l_int|4
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_type
op_assign
id|hfs_get_nl
c_func
(paren
id|args
(braket
l_int|0
)braket
dot
id|from
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_creator
suffix:colon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|args
(braket
l_int|0
)braket
dot
id|from
)paren
op_ne
l_int|4
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|hsb-&gt;s_creator
op_assign
id|hfs_get_nl
c_func
(paren
id|args
(braket
l_int|0
)braket
dot
id|from
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Boolean-valued options */
r_case
id|Opt_quiet
suffix:colon
id|hsb-&gt;s_quiet
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_afpd
suffix:colon
id|hsb-&gt;s_afpd
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Multiple choice options */
r_case
id|Opt_names_netatalk
suffix:colon
id|names
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_trivial
suffix:colon
id|names
op_assign
l_char|&squot;t&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_alpha
suffix:colon
id|names
op_assign
l_char|&squot;a&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_latin
suffix:colon
id|names
op_assign
l_char|&squot;l&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_7bit
suffix:colon
id|names
op_assign
l_char|&squot;7&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_8bit
suffix:colon
id|names
op_assign
l_char|&squot;8&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_names_cap
suffix:colon
id|names
op_assign
l_char|&squot;c&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_fork_netatalk
suffix:colon
id|fork
op_assign
l_char|&squot;n&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_fork_single
suffix:colon
id|fork
op_assign
l_char|&squot;s&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_fork_double
suffix:colon
id|fork
op_assign
l_char|&squot;d&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_fork_cap
suffix:colon
id|fork
op_assign
l_char|&squot;c&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_case_lower
suffix:colon
id|hsb-&gt;s_lowercase
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_case_asis
suffix:colon
id|hsb-&gt;s_lowercase
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_conv_binary
suffix:colon
id|hsb-&gt;s_conv
op_assign
l_char|&squot;b&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_conv_text
suffix:colon
id|hsb-&gt;s_conv
op_assign
l_char|&squot;t&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_conv_auto
suffix:colon
id|hsb-&gt;s_conv
op_assign
l_char|&squot;a&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|done
suffix:colon
multiline_comment|/* Parse the &quot;fork&quot; and &quot;names&quot; options */
r_if
c_cond
(paren
id|fork
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|fork
op_assign
id|hsb-&gt;s_afpd
ques
c_cond
l_char|&squot;n&squot;
suffix:colon
l_char|&squot;c&squot;
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|fork
)paren
(brace
r_default
suffix:colon
r_case
l_char|&squot;c&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_cap_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_cap_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_cap_reserved2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: AppleSingle not yet implemented.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* break; */
r_case
l_char|&squot;d&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_dbl_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_dbl_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_dbl_reserved2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;n&squot;
suffix:colon
id|hsb-&gt;s_ifill
op_assign
id|hfs_nat_ifill
suffix:semicolon
id|hsb-&gt;s_reserved1
op_assign
id|hfs_nat_reserved1
suffix:semicolon
id|hsb-&gt;s_reserved2
op_assign
id|hfs_nat_reserved2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|names
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|names
op_assign
id|fork
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|names
)paren
(brace
r_default
suffix:colon
r_case
l_char|&squot;n&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_colon2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2nat
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_colon2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2cap
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_triv2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2triv
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;7&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2seven
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;8&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2eight
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
id|hsb-&gt;s_nameout
op_assign
id|hfs_latin2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2latin
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
suffix:colon
multiline_comment|/* &squot;s&squot; and &squot;d&squot; are unadvertised aliases for &squot;alpha&squot;, */
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* since &squot;alpha&squot; is the default if fork=s or fork=d. */
r_case
l_char|&squot;d&squot;
suffix:colon
multiline_comment|/* (It is also helpful for poor typists!)           */
id|hsb-&gt;s_nameout
op_assign
id|hfs_prcnt2mac
suffix:semicolon
id|hsb-&gt;s_namein
op_assign
id|hfs_mac2alpha
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_read_super()&n; *&n; * This is the function that is responsible for mounting an HFS&n; * filesystem.&t;It performs all the tasks necessary to get enough data&n; * from the disk to read the root inode.  This includes parsing the&n; * mount options, dealing with Macintosh partitions, reading the&n; * superblock and the allocation bitmap blocks, calling&n; * hfs_btree_init() to get the necessary data about the extents and&n; * catalog B-trees and, finally, reading the root inode into memory.&n; */
DECL|function|hfs_fill_super
r_int
id|hfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
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
id|hfs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|hfs_mdb
op_star
id|mdb
suffix:semicolon
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
id|hfs_s32
id|part_size
comma
id|part_start
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_int
id|part
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hfs_sb_info
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
id|sbi
suffix:semicolon
id|memset
c_func
(paren
id|sbi
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hfs_sb_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
(paren
r_char
op_star
)paren
id|data
comma
id|sbi
comma
op_amp
id|part
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to parse mount options.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail2
suffix:semicolon
)brace
multiline_comment|/* set the device driver to 512-byte blocks */
id|sb_set_blocksize
c_func
(paren
id|s
comma
id|HFS_SECTOR_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAC_PARTITION
multiline_comment|/* check to see if we&squot;re in a partition */
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* erk. try parsing the partition table ourselves */
r_if
c_cond
(paren
op_logical_neg
id|mdb
)paren
(brace
r_if
c_cond
(paren
id|hfs_part_find
c_func
(paren
id|s
comma
id|part
comma
id|silent
comma
op_amp
id|part_size
comma
op_amp
id|part_start
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
id|part_start
)paren
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|hfs_part_find
c_func
(paren
id|s
comma
id|part
comma
id|silent
comma
op_amp
id|part_size
comma
op_amp
id|part_start
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|mdb
op_assign
id|hfs_mdb_get
c_func
(paren
id|s
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
comma
id|part_start
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|mdb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;VFS: Can&squot;t find a HFS filesystem on dev %s.&bslash;n&quot;
comma
id|s-&gt;s_id
)paren
suffix:semicolon
)brace
r_goto
id|bail2
suffix:semicolon
)brace
id|sbi-&gt;s_mdb
op_assign
id|mdb
suffix:semicolon
r_if
c_cond
(paren
id|HFS_ITYPE
c_func
(paren
id|mdb-&gt;next_id
)paren
op_ne
l_int|0
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: too many files.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail1
suffix:semicolon
)brace
id|s-&gt;s_magic
op_assign
id|HFS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|hfs_super_operations
suffix:semicolon
multiline_comment|/* try to get the root inode */
id|hfs_cat_build_key
c_func
(paren
id|htonl
c_func
(paren
id|HFS_POR_CNID
)paren
comma
(paren
r_struct
id|hfs_name
op_star
)paren
(paren
id|mdb-&gt;vname
)paren
comma
op_amp
id|key
)paren
suffix:semicolon
id|root_inode
op_assign
id|hfs_iget
c_func
(paren
id|hfs_cat_get
c_func
(paren
id|mdb
comma
op_amp
id|key
)paren
comma
id|HFS_ITYPE_NORM
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
r_goto
id|bail_no_root
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
)paren
r_goto
id|bail_no_root
suffix:semicolon
multiline_comment|/* fix up pointers. */
id|HFS_I
c_func
(paren
id|root_inode
)paren
op_member_access_from_pointer
id|entry-&gt;sys_entry
(braket
id|HFS_ITYPE_TO_INT
c_func
(paren
id|HFS_ITYPE_NORM
)paren
)braket
op_assign
id|s-&gt;s_root
suffix:semicolon
id|s-&gt;s_root-&gt;d_op
op_assign
op_amp
id|hfs_dentry_operations
suffix:semicolon
multiline_comment|/* everything&squot;s okay */
r_return
l_int|0
suffix:semicolon
id|bail_no_root
suffix:colon
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: get root inode failed.&bslash;n&quot;
)paren
suffix:semicolon
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|bail1
suffix:colon
id|hfs_mdb_put
c_func
(paren
id|mdb
comma
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
id|bail2
suffix:colon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|init_hfs_fs
r_static
r_int
id|__init
id|init_hfs_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|init_inodecache
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out1
suffix:semicolon
id|hfs_cat_init
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|hfs_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|hfs_cat_free
c_func
(paren
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
id|out1
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_hfs_fs
r_static
r_void
id|__exit
id|exit_hfs_fs
c_func
(paren
r_void
)paren
(brace
id|hfs_cat_free
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|hfs_fs
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_hfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_hfs_fs
)paren
macro_line|#if defined(DEBUG_ALL) || defined(DEBUG_MEM)
r_int
r_int
id|hfs_alloc
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
eof
