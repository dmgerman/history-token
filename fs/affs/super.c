multiline_comment|/*&n; *  linux/fs/affs/inode.c&n; *&n; *  (c) 1996  Hans-Joachim Widmaier - Rewritten&n; *&n; *  (C) 1993  Ray Burr - Modified for Amiga FFS filesystem.&n; *&n; *  (C) 1992  Eric Youngdale Modified for ISO 9660 filesystem.&n; *&n; *  (C) 1991  Linus Torvalds - minix filesystem&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/parser.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_static
r_int
id|affs_statfs
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
r_static
r_int
id|affs_remount
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
suffix:semicolon
r_static
r_void
DECL|function|affs_put_super
id|affs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: put_super()&bslash;n&quot;
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
(brace
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|bm_flag
op_assign
id|be32_to_cpu
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|secs_to_datestamp
c_func
(paren
id|get_seconds
c_func
(paren
)paren
comma
op_amp
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|disk_change
)paren
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_root_bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sbi-&gt;s_prefix
)paren
id|kfree
c_func
(paren
id|sbi-&gt;s_prefix
)paren
suffix:semicolon
id|affs_free_bitmap
c_func
(paren
id|sb
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|sbi-&gt;s_root_bh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|affs_write_super
id|affs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_int
id|clean
op_assign
l_int|2
suffix:semicolon
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
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
(brace
singleline_comment|//&t;if (sbi-&gt;s_bitmap[i].bm_bh) {
singleline_comment|//&t;&t;if (buffer_dirty(sbi-&gt;s_bitmap[i].bm_bh)) {
singleline_comment|//&t;&t;&t;clean = 0;
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|bm_flag
op_assign
id|be32_to_cpu
c_func
(paren
id|clean
)paren
suffix:semicolon
id|secs_to_datestamp
c_func
(paren
id|get_seconds
c_func
(paren
)paren
comma
op_amp
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
op_member_access_from_pointer
id|disk_change
)paren
suffix:semicolon
id|affs_fix_checksum
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|sbi-&gt;s_root_bh
)paren
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
op_logical_neg
id|clean
suffix:semicolon
multiline_comment|/* redo until bitmap synced */
)brace
r_else
id|sb-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: write_super() at %lu, clean=%d&bslash;n&quot;
comma
id|get_seconds
c_func
(paren
)paren
comma
id|clean
)paren
suffix:semicolon
)brace
DECL|variable|affs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|affs_inode_cachep
suffix:semicolon
DECL|function|affs_alloc_inode
r_static
r_struct
id|inode
op_star
id|affs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|affs_inode_info
op_star
id|ei
suffix:semicolon
id|ei
op_assign
(paren
r_struct
id|affs_inode_info
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|affs_inode_cachep
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
id|ei-&gt;vfs_inode.i_version
op_assign
l_int|1
suffix:semicolon
r_return
op_amp
id|ei-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|affs_destroy_inode
r_static
r_void
id|affs_destroy_inode
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
id|affs_inode_cachep
comma
id|AFFS_I
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
id|affs_inode_info
op_star
id|ei
op_assign
(paren
r_struct
id|affs_inode_info
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
id|init_MUTEX
c_func
(paren
op_amp
id|ei-&gt;i_link_lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|ei-&gt;i_ext_lock
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
DECL|function|init_inodecache
r_static
r_int
id|init_inodecache
c_func
(paren
r_void
)paren
(brace
id|affs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;affs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|affs_inode_info
)paren
comma
l_int|0
comma
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
id|affs_inode_cachep
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
id|affs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;affs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|affs_sops
r_static
r_struct
id|super_operations
id|affs_sops
op_assign
(brace
dot
id|alloc_inode
op_assign
id|affs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|affs_destroy_inode
comma
dot
id|read_inode
op_assign
id|affs_read_inode
comma
dot
id|write_inode
op_assign
id|affs_write_inode
comma
dot
id|put_inode
op_assign
id|affs_put_inode
comma
dot
id|delete_inode
op_assign
id|affs_delete_inode
comma
dot
id|clear_inode
op_assign
id|affs_clear_inode
comma
dot
id|put_super
op_assign
id|affs_put_super
comma
dot
id|write_super
op_assign
id|affs_write_super
comma
dot
id|statfs
op_assign
id|affs_statfs
comma
dot
id|remount_fs
op_assign
id|affs_remount
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|Opt_bs
DECL|enumerator|Opt_mode
DECL|enumerator|Opt_mufs
DECL|enumerator|Opt_prefix
DECL|enumerator|Opt_protect
id|Opt_bs
comma
id|Opt_mode
comma
id|Opt_mufs
comma
id|Opt_prefix
comma
id|Opt_protect
comma
DECL|enumerator|Opt_reserved
DECL|enumerator|Opt_root
DECL|enumerator|Opt_setgid
DECL|enumerator|Opt_setuid
id|Opt_reserved
comma
id|Opt_root
comma
id|Opt_setgid
comma
id|Opt_setuid
comma
DECL|enumerator|Opt_verbose
DECL|enumerator|Opt_volume
DECL|enumerator|Opt_ignore
DECL|enumerator|Opt_err
id|Opt_verbose
comma
id|Opt_volume
comma
id|Opt_ignore
comma
id|Opt_err
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
id|Opt_bs
comma
l_string|&quot;bs=%u&quot;
)brace
comma
(brace
id|Opt_mode
comma
l_string|&quot;mode=%o&quot;
)brace
comma
(brace
id|Opt_mufs
comma
l_string|&quot;mufs&quot;
)brace
comma
(brace
id|Opt_prefix
comma
l_string|&quot;prefix=%s&quot;
)brace
comma
(brace
id|Opt_protect
comma
l_string|&quot;protect&quot;
)brace
comma
(brace
id|Opt_reserved
comma
l_string|&quot;reserved=%u&quot;
)brace
comma
(brace
id|Opt_root
comma
l_string|&quot;root=%u&quot;
)brace
comma
(brace
id|Opt_setgid
comma
l_string|&quot;setgid=%u&quot;
)brace
comma
(brace
id|Opt_setuid
comma
l_string|&quot;setuid=%u&quot;
)brace
comma
(brace
id|Opt_verbose
comma
l_string|&quot;verbose&quot;
)brace
comma
(brace
id|Opt_volume
comma
l_string|&quot;volume=%s&quot;
)brace
comma
(brace
id|Opt_ignore
comma
l_string|&quot;grpquota&quot;
)brace
comma
(brace
id|Opt_ignore
comma
l_string|&quot;noquota&quot;
)brace
comma
(brace
id|Opt_ignore
comma
l_string|&quot;quota&quot;
)brace
comma
(brace
id|Opt_ignore
comma
l_string|&quot;usrquota&quot;
)brace
comma
(brace
id|Opt_err
comma
l_int|NULL
)brace
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|parse_options
id|parse_options
c_func
(paren
r_char
op_star
id|options
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
r_int
op_star
id|mode
comma
r_int
op_star
id|reserved
comma
id|s32
op_star
id|root
comma
r_int
op_star
id|blocksize
comma
r_char
op_star
op_star
id|prefix
comma
r_char
op_star
id|volume
comma
r_int
r_int
op_star
id|mount_opts
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
id|substring_t
id|args
(braket
id|MAX_OPT_ARGS
)braket
suffix:semicolon
multiline_comment|/* Fill in defaults */
op_star
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
op_star
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
op_star
id|reserved
op_assign
l_int|2
suffix:semicolon
op_star
id|root
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|blocksize
op_assign
op_minus
l_int|1
suffix:semicolon
id|volume
(braket
l_int|0
)braket
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|volume
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|mount_opts
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
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
comma
id|n
comma
id|option
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
r_case
id|Opt_bs
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
id|n
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|512
op_logical_and
id|n
op_ne
l_int|1024
op_logical_and
id|n
op_ne
l_int|2048
op_logical_and
id|n
op_ne
l_int|4096
)paren
(brace
id|printk
(paren
l_string|&quot;AFFS: Invalid blocksize (512, 1024, 2048, 4096 allowed)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|blocksize
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_mode
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
l_int|1
suffix:semicolon
op_star
id|mode
op_assign
id|option
op_amp
l_int|0777
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_SETMODE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_mufs
suffix:colon
op_star
id|mount_opts
op_or_assign
id|SF_MUFS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_prefix
suffix:colon
r_if
c_cond
(paren
op_star
id|prefix
)paren
(brace
multiline_comment|/* Free any previous prefix */
id|kfree
c_func
(paren
op_star
id|prefix
)paren
suffix:semicolon
op_star
id|prefix
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|prefix
op_assign
id|match_strdup
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|prefix
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_PREFIX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_protect
suffix:colon
op_star
id|mount_opts
op_or_assign
id|SF_IMMUTABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_reserved
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
id|reserved
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_root
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
id|root
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_setgid
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
l_int|1
suffix:semicolon
op_star
id|gid
op_assign
id|option
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_SETGID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_setuid
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
op_minus
id|EINVAL
suffix:semicolon
op_star
id|uid
op_assign
id|option
suffix:semicolon
op_star
id|mount_opts
op_or_assign
id|SF_SETUID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_verbose
suffix:colon
op_star
id|mount_opts
op_or_assign
id|SF_VERBOSE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Opt_volume
suffix:colon
(brace
r_char
op_star
id|vol
op_assign
id|match_strdup
c_func
(paren
op_amp
id|args
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|volume
comma
id|vol
comma
l_int|32
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vol
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|Opt_ignore
suffix:colon
multiline_comment|/* Silently ignore the quota options */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;AFFS: Unrecognized mount option &bslash;&quot;%s&bslash;&quot; &quot;
l_string|&quot;or missing value&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This function definitely needs to be split up. Some fine day I&squot;ll&n; * hopefully have the guts to do so. Until then: sorry for the mess.&n; */
DECL|function|affs_fill_super
r_static
r_int
id|affs_fill_super
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
id|affs_sb_info
op_star
id|sbi
suffix:semicolon
r_struct
id|buffer_head
op_star
id|root_bh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|boot_bh
suffix:semicolon
r_struct
id|inode
op_star
id|root_inode
op_assign
l_int|NULL
suffix:semicolon
id|s32
id|root_block
suffix:semicolon
r_int
id|size
comma
id|blocksize
suffix:semicolon
id|u32
id|chksum
suffix:semicolon
r_int
id|num_bm
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|s32
id|key
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
r_int
id|reserved
suffix:semicolon
r_int
r_int
id|mount_flags
suffix:semicolon
r_int
id|tmp_flags
suffix:semicolon
multiline_comment|/* fix remount prototype... */
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: read_super(%s)&bslash;n&quot;
comma
id|data
ques
c_cond
(paren
r_const
r_char
op_star
)paren
id|data
suffix:colon
l_string|&quot;no options&quot;
)paren
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|AFFS_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|affs_sops
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|affs_sb_info
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
id|sb-&gt;s_fs_info
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
op_star
id|sbi
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|sbi-&gt;s_bmlock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|i
comma
op_amp
id|reserved
comma
op_amp
id|root_block
comma
op_amp
id|blocksize
comma
op_amp
id|sbi-&gt;s_prefix
comma
id|sbi-&gt;s_volume
comma
op_amp
id|mount_flags
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Error parsing options&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* N.B. after this point s_prefix must be released */
id|sbi-&gt;s_flags
op_assign
id|mount_flags
suffix:semicolon
id|sbi-&gt;s_mode
op_assign
id|i
suffix:semicolon
id|sbi-&gt;s_uid
op_assign
id|uid
suffix:semicolon
id|sbi-&gt;s_gid
op_assign
id|gid
suffix:semicolon
id|sbi-&gt;s_reserved
op_assign
id|reserved
suffix:semicolon
multiline_comment|/* Get the size of the device in 512-byte blocks.&n;&t; * If we later see that the partition uses bigger&n;&t; * blocks, we will have to change it.&n;&t; */
id|size
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: initial blocksize=%d, #blocks=%d&bslash;n&quot;
comma
l_int|512
comma
id|size
)paren
suffix:semicolon
id|affs_set_blocksize
c_func
(paren
id|sb
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Try to find root block. Its location depends on the block size. */
id|i
op_assign
l_int|512
suffix:semicolon
id|j
op_assign
l_int|4096
suffix:semicolon
r_if
c_cond
(paren
id|blocksize
OG
l_int|0
)paren
(brace
id|i
op_assign
id|j
op_assign
id|blocksize
suffix:semicolon
id|size
op_assign
id|size
op_div
(paren
id|blocksize
op_div
l_int|512
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|blocksize
op_assign
id|i
comma
id|key
op_assign
l_int|0
suffix:semicolon
id|blocksize
op_le
id|j
suffix:semicolon
id|blocksize
op_lshift_assign
l_int|1
comma
id|size
op_rshift_assign
l_int|1
)paren
(brace
id|sbi-&gt;s_root_block
op_assign
id|root_block
suffix:semicolon
r_if
c_cond
(paren
id|root_block
OL
l_int|0
)paren
id|sbi-&gt;s_root_block
op_assign
(paren
id|reserved
op_plus
id|size
op_minus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: setting blocksize to %d&bslash;n&quot;
comma
id|blocksize
)paren
suffix:semicolon
id|affs_set_blocksize
c_func
(paren
id|sb
comma
id|blocksize
)paren
suffix:semicolon
id|sbi-&gt;s_partition_size
op_assign
id|size
suffix:semicolon
multiline_comment|/* The root block location that was calculated above is not&n;&t;&t; * correct if the partition size is an odd number of 512-&n;&t;&t; * byte blocks, which will be rounded down to a number of&n;&t;&t; * 1024-byte blocks, and if there were an even number of&n;&t;&t; * reserved blocks. Ideally, all partition checkers should&n;&t;&t; * report the real number of blocks of the real blocksize,&n;&t;&t; * but since this just cannot be done, we have to try to&n;&t;&t; * find the root block anyways. In the above case, it is one&n;&t;&t; * block behind the calculated one. So we check this one, too.&n;&t;&t; */
r_for
c_loop
(paren
id|num_bm
op_assign
l_int|0
suffix:semicolon
id|num_bm
OL
l_int|2
suffix:semicolon
id|num_bm
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: Dev %s, trying root=%u, bs=%d, &quot;
l_string|&quot;size=%d, reserved=%d&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|sbi-&gt;s_root_block
op_plus
id|num_bm
comma
id|blocksize
comma
id|size
comma
id|reserved
)paren
suffix:semicolon
id|root_bh
op_assign
id|affs_bread
c_func
(paren
id|sb
comma
id|sbi-&gt;s_root_block
op_plus
id|num_bm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_bh
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|affs_checksum_block
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_logical_and
id|be32_to_cpu
c_func
(paren
id|AFFS_ROOT_HEAD
c_func
(paren
id|root_bh
)paren
op_member_access_from_pointer
id|ptype
)paren
op_eq
id|T_SHORT
op_logical_and
id|be32_to_cpu
c_func
(paren
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|stype
)paren
op_eq
id|ST_ROOT
)paren
(brace
id|sbi-&gt;s_hashsize
op_assign
id|blocksize
op_div
l_int|4
op_minus
l_int|56
suffix:semicolon
id|sbi-&gt;s_root_block
op_add_assign
id|num_bm
suffix:semicolon
id|key
op_assign
l_int|1
suffix:semicolon
r_goto
id|got_root
suffix:semicolon
)brace
id|affs_brelse
c_func
(paren
id|root_bh
)paren
suffix:semicolon
id|root_bh
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: No valid root block on device %s&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
multiline_comment|/* N.B. after this point bh must be released */
id|got_root
suffix:colon
id|root_block
op_assign
id|sbi-&gt;s_root_block
suffix:semicolon
multiline_comment|/* Find out which kind of FS we have */
id|boot_bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot_bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Cannot read boot block&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|chksum
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|u32
op_star
)paren
id|boot_bh-&gt;b_data
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|boot_bh
)paren
suffix:semicolon
multiline_comment|/* Dircache filesystems are compatible with non-dircache ones&n;&t; * when reading. As long as they aren&squot;t supported, writing is&n;&t; * not recommended.&n;&t; */
r_if
c_cond
(paren
(paren
id|chksum
op_eq
id|FS_DCFFS
op_logical_or
id|chksum
op_eq
id|MUFS_DCFFS
op_logical_or
id|chksum
op_eq
id|FS_DCOFS
op_logical_or
id|chksum
op_eq
id|MUFS_DCOFS
)paren
op_logical_and
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;AFFS: Dircache FS - mounting %s read only&bslash;n&quot;
comma
id|sb-&gt;s_id
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|chksum
)paren
(brace
r_case
id|MUFS_FS
suffix:colon
r_case
id|MUFS_INTLFFS
suffix:colon
r_case
id|MUFS_DCFFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|FS_INTLFFS
suffix:colon
r_case
id|FS_DCFFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_INTL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MUFS_FFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FS_FFS
suffix:colon
r_break
suffix:semicolon
r_case
id|MUFS_OFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
multiline_comment|/* fall thru */
r_case
id|FS_OFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_OFS
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NOEXEC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MUFS_DCOFS
suffix:colon
r_case
id|MUFS_INTLOFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_MUFS
suffix:semicolon
r_case
id|FS_DCOFS
suffix:colon
r_case
id|FS_INTLOFS
suffix:colon
id|sbi-&gt;s_flags
op_or_assign
id|SF_INTL
op_or
id|SF_OFS
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_NOEXEC
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Unknown filesystem on device %s: %08X&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|chksum
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mount_flags
op_amp
id|SF_VERBOSE
)paren
(brace
id|chksum
op_assign
id|cpu_to_be32
c_func
(paren
id|chksum
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;AFFS: Mounting volume &bslash;&quot;%*s&bslash;&quot;: Type=%.3s&bslash;&bslash;%c, Blocksize=%d&bslash;n&quot;
comma
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|disk_name
(braket
l_int|0
)braket
comma
id|AFFS_ROOT_TAIL
c_func
(paren
id|sb
comma
id|root_bh
)paren
op_member_access_from_pointer
id|disk_name
op_plus
l_int|1
comma
(paren
r_char
op_star
)paren
op_amp
id|chksum
comma
(paren
(paren
r_char
op_star
)paren
op_amp
id|chksum
)paren
(braket
l_int|3
)braket
op_plus
l_char|&squot;0&squot;
comma
id|blocksize
)paren
suffix:semicolon
)brace
id|sb-&gt;s_flags
op_or_assign
id|MS_NODEV
op_or
id|MS_NOSUID
suffix:semicolon
id|sbi-&gt;s_data_blksize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_flags
op_amp
id|SF_OFS
)paren
id|sbi-&gt;s_data_blksize
op_sub_assign
l_int|24
suffix:semicolon
multiline_comment|/* Keep super block in cache */
id|sbi-&gt;s_root_bh
op_assign
id|root_bh
suffix:semicolon
multiline_comment|/* N.B. after this point s_root_bh must be released */
id|tmp_flags
op_assign
id|sb-&gt;s_flags
suffix:semicolon
r_if
c_cond
(paren
id|affs_init_bitmap
c_func
(paren
id|sb
comma
op_amp
id|tmp_flags
)paren
)paren
r_goto
id|out_error
suffix:semicolon
id|sb-&gt;s_flags
op_assign
id|tmp_flags
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|root_inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|root_block
)paren
suffix:semicolon
id|sb-&gt;s_root
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
id|sb-&gt;s_root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AFFS: Get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_error
suffix:semicolon
)brace
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|affs_dentry_operations
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: s_flags=%lX&bslash;n&quot;
comma
id|sb-&gt;s_flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Begin the cascaded cleanup ...&n;&t; */
id|out_error
suffix:colon
r_if
c_cond
(paren
id|root_inode
)paren
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_bitmap
)paren
id|kfree
c_func
(paren
id|sbi-&gt;s_bitmap
)paren
suffix:semicolon
id|affs_brelse
c_func
(paren
id|root_bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_prefix
)paren
id|kfree
c_func
(paren
id|sbi-&gt;s_prefix
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sbi
)paren
suffix:semicolon
id|sb-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_remount
id|affs_remount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
r_struct
id|affs_sb_info
op_star
id|sbi
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|blocksize
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|reserved
suffix:semicolon
r_int
id|root_block
suffix:semicolon
r_int
r_int
id|mount_flags
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: remount(flags=0x%x,opts=&bslash;&quot;%s&bslash;&quot;)&bslash;n&quot;
comma
op_star
id|flags
comma
id|data
)paren
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_NODIRATIME
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parse_options
c_func
(paren
id|data
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|mode
comma
op_amp
id|reserved
comma
op_amp
id|root_block
comma
op_amp
id|blocksize
comma
op_amp
id|sbi-&gt;s_prefix
comma
id|sbi-&gt;s_volume
comma
op_amp
id|mount_flags
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sbi-&gt;s_flags
op_assign
id|mount_flags
suffix:semicolon
id|sbi-&gt;s_mode
op_assign
id|mode
suffix:semicolon
id|sbi-&gt;s_uid
op_assign
id|uid
suffix:semicolon
id|sbi-&gt;s_gid
op_assign
id|gid
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
op_eq
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
(brace
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|sb-&gt;s_dirt
)paren
id|affs_write_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|affs_free_bitmap
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
r_else
id|res
op_assign
id|affs_init_bitmap
c_func
(paren
id|sb
comma
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_static
r_int
DECL|function|affs_statfs
id|affs_statfs
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
id|free
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;AFFS: statfs() partsize=%d, reserved=%d&bslash;n&quot;
comma
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
comma
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
)paren
suffix:semicolon
id|free
op_assign
id|affs_count_free_blocks
c_func
(paren
id|sb
)paren
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|AFFS_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
op_minus
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|free
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|free
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|affs_get_sb
r_static
r_struct
id|super_block
op_star
id|affs_get_sb
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
id|affs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|affs_fs_type
r_static
r_struct
id|file_system_type
id|affs_fs_type
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
l_string|&quot;affs&quot;
comma
dot
id|get_sb
op_assign
id|affs_get_sb
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
DECL|function|init_affs_fs
r_static
r_int
id|__init
id|init_affs_fs
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
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|affs_fs_type
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
DECL|function|exit_affs_fs
r_static
r_void
id|__exit
id|exit_affs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|affs_fs_type
)paren
suffix:semicolon
id|destroy_inodecache
c_func
(paren
)paren
suffix:semicolon
)brace
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Amiga filesystem support for Linux&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|init_affs_fs
)paren
id|module_exit
c_func
(paren
id|exit_affs_fs
)paren
eof
