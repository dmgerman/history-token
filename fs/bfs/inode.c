multiline_comment|/*&n; *&t;fs/bfs/inode.c&n; *&t;BFS superblock and inode operations.&n; *&t;Copyright (C) 1999,2000 Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;From fs/minix, Copyright (C) 1991, 1992 Linus Torvalds.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;bfs.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tigran A. Aivazian &lt;tigran@veritas.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SCO UnixWare BFS filesystem for Linux&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)&t;printf(x)
macro_line|#else
DECL|macro|dprintf
mdefine_line|#define dprintf(x...)
macro_line|#endif
r_void
id|dump_imap
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
DECL|function|bfs_read_inode
r_static
r_void
id|bfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_struct
id|bfs_inode
op_star
id|di
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
comma
id|off
suffix:semicolon
r_if
c_cond
(paren
id|ino
template_param
id|BFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|si_lasti
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Bad inode number %s:%08lx&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|block
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_div
id|BFS_INODES_PER_BLOCK
op_plus
l_int|1
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Unable to read inode %s:%08lx&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
id|make_bad_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|off
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_mod
id|BFS_INODES_PER_BLOCK
suffix:semicolon
id|di
op_assign
(paren
r_struct
id|bfs_inode
op_star
)paren
id|bh-&gt;b_data
op_plus
id|off
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0x0000FFFF
op_amp
id|di-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
id|di-&gt;i_vtype
op_eq
id|BFS_VDIR
)paren
(brace
id|inode-&gt;i_mode
op_or_assign
id|S_IFDIR
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|bfs_dir_inops
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bfs_dir_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|di-&gt;i_vtype
op_eq
id|BFS_VREG
)paren
(brace
id|inode-&gt;i_mode
op_or_assign
id|S_IFREG
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|bfs_file_inops
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bfs_file_operations
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|bfs_aops
suffix:semicolon
)brace
id|inode-&gt;i_uid
op_assign
id|di-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|di-&gt;i_gid
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|di-&gt;i_nlink
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|BFS_FILESIZE
c_func
(paren
id|di
)paren
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|BFS_FILEBLOCKS
c_func
(paren
id|di
)paren
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|inode-&gt;i_atime.tv_sec
op_assign
id|di-&gt;i_atime
suffix:semicolon
id|inode-&gt;i_mtime.tv_sec
op_assign
id|di-&gt;i_mtime
suffix:semicolon
id|inode-&gt;i_ctime.tv_sec
op_assign
id|di-&gt;i_ctime
suffix:semicolon
id|inode-&gt;i_atime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_mtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_ctime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_dsk_ino
op_assign
id|di-&gt;i_ino
suffix:semicolon
multiline_comment|/* can be 0 so we store a copy */
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_sblock
op_assign
id|di-&gt;i_sblock
suffix:semicolon
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
op_assign
id|di-&gt;i_eblock
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|bfs_write_inode
r_static
r_void
id|bfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|unused
)paren
(brace
r_int
r_int
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_struct
id|bfs_inode
op_star
id|di
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
comma
id|off
suffix:semicolon
r_if
c_cond
(paren
id|ino
template_param
id|BFS_SB
c_func
(paren
id|inode-&gt;i_sb
)paren
op_member_access_from_pointer
id|si_lasti
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Bad inode number %s:%08lx&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|block
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_div
id|BFS_INODES_PER_BLOCK
op_plus
l_int|1
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Unable to read inode %s:%08lx&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|off
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_mod
id|BFS_INODES_PER_BLOCK
suffix:semicolon
id|di
op_assign
(paren
r_struct
id|bfs_inode
op_star
)paren
id|bh-&gt;b_data
op_plus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|BFS_ROOT_INO
)paren
id|di-&gt;i_vtype
op_assign
id|BFS_VDIR
suffix:semicolon
r_else
id|di-&gt;i_vtype
op_assign
id|BFS_VREG
suffix:semicolon
id|di-&gt;i_ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|di-&gt;i_mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
id|di-&gt;i_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
id|di-&gt;i_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
id|di-&gt;i_nlink
op_assign
id|inode-&gt;i_nlink
suffix:semicolon
id|di-&gt;i_atime
op_assign
id|inode-&gt;i_atime.tv_sec
suffix:semicolon
id|di-&gt;i_mtime
op_assign
id|inode-&gt;i_mtime.tv_sec
suffix:semicolon
id|di-&gt;i_ctime
op_assign
id|inode-&gt;i_ctime.tv_sec
suffix:semicolon
id|di-&gt;i_sblock
op_assign
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_sblock
suffix:semicolon
id|di-&gt;i_eblock
op_assign
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
suffix:semicolon
id|di-&gt;i_eoffset
op_assign
id|di-&gt;i_sblock
op_star
id|BFS_BSIZE
op_plus
id|inode-&gt;i_size
op_minus
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|bfs_delete_inode
r_static
r_void
id|bfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
r_int
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_struct
id|bfs_inode
op_star
id|di
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
comma
id|off
suffix:semicolon
r_struct
id|super_block
op_star
id|s
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_struct
id|bfs_sb_info
op_star
id|info
op_assign
id|BFS_SB
c_func
(paren
id|s
)paren
suffix:semicolon
id|dprintf
c_func
(paren
l_string|&quot;ino=%08lx&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
template_param
id|info-&gt;si_lasti
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;invalid ino=%08lx&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|block
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_div
id|BFS_INODES_PER_BLOCK
op_plus
l_int|1
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Unable to read inode %s:%08lx&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
comma
id|ino
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|off
op_assign
(paren
id|ino
op_minus
id|BFS_ROOT_INO
)paren
op_mod
id|BFS_INODES_PER_BLOCK
suffix:semicolon
id|di
op_assign
(paren
r_struct
id|bfs_inode
op_star
)paren
id|bh-&gt;b_data
op_plus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|di-&gt;i_ino
)paren
(brace
id|info-&gt;si_freeb
op_add_assign
id|BFS_FILEBLOCKS
c_func
(paren
id|di
)paren
suffix:semicolon
id|info-&gt;si_freei
op_increment
suffix:semicolon
id|clear_bit
c_func
(paren
id|di-&gt;i_ino
comma
id|info-&gt;si_imap
)paren
suffix:semicolon
id|dump_imap
c_func
(paren
l_string|&quot;delete_inode&quot;
comma
id|s
)paren
suffix:semicolon
)brace
id|di-&gt;i_ino
op_assign
l_int|0
suffix:semicolon
id|di-&gt;i_sblock
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* if this was the last file, make the previous &n;&t;   block &quot;last files last block&quot; even if there is no real file there,&n;&t;   saves us 1 gap */
r_if
c_cond
(paren
id|info-&gt;si_lf_eblk
op_eq
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
)paren
(brace
id|info-&gt;si_lf_eblk
op_assign
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_sblock
op_minus
l_int|1
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|info-&gt;si_sbh
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
DECL|function|bfs_put_super
r_static
r_void
id|bfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|bfs_sb_info
op_star
id|info
op_assign
id|BFS_SB
c_func
(paren
id|s
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|info-&gt;si_sbh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info-&gt;si_imap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|bfs_statfs
r_static
r_int
id|bfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
r_struct
id|bfs_sb_info
op_star
id|info
op_assign
id|BFS_SB
c_func
(paren
id|s
)paren
suffix:semicolon
id|buf-&gt;f_type
op_assign
id|BFS_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|s-&gt;s_blocksize
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|info-&gt;si_blocks
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|buf-&gt;f_bavail
op_assign
id|info-&gt;si_freeb
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|info-&gt;si_lasti
op_plus
l_int|1
op_minus
id|BFS_ROOT_INO
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|info-&gt;si_freei
suffix:semicolon
id|buf-&gt;f_fsid.val
(braket
l_int|0
)braket
op_assign
id|s-&gt;s_dev
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|BFS_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bfs_write_super
r_static
r_void
id|bfs_write_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
id|mark_buffer_dirty
c_func
(paren
id|BFS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|si_sbh
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|bfs_inode_cachep
r_static
id|kmem_cache_t
op_star
id|bfs_inode_cachep
suffix:semicolon
DECL|function|bfs_alloc_inode
r_static
r_struct
id|inode
op_star
id|bfs_alloc_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|bfs_inode_info
op_star
id|bi
suffix:semicolon
id|bi
op_assign
id|kmem_cache_alloc
c_func
(paren
id|bfs_inode_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bi
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
op_amp
id|bi-&gt;vfs_inode
suffix:semicolon
)brace
DECL|function|bfs_destroy_inode
r_static
r_void
id|bfs_destroy_inode
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
id|bfs_inode_cachep
comma
id|BFS_I
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
id|bfs_inode_info
op_star
id|bi
op_assign
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
id|bi-&gt;vfs_inode
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
id|bfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bfs_inode_cache&quot;
comma
r_sizeof
(paren
r_struct
id|bfs_inode_info
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
id|bfs_inode_cachep
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
id|bfs_inode_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bfs_inode_cache: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|bfs_sops
r_static
r_struct
id|super_operations
id|bfs_sops
op_assign
(brace
dot
id|alloc_inode
op_assign
id|bfs_alloc_inode
comma
dot
id|destroy_inode
op_assign
id|bfs_destroy_inode
comma
dot
id|read_inode
op_assign
id|bfs_read_inode
comma
dot
id|write_inode
op_assign
id|bfs_write_inode
comma
dot
id|delete_inode
op_assign
id|bfs_delete_inode
comma
dot
id|put_super
op_assign
id|bfs_put_super
comma
dot
id|write_super
op_assign
id|bfs_write_super
comma
dot
id|statfs
op_assign
id|bfs_statfs
comma
)brace
suffix:semicolon
DECL|function|dump_imap
r_void
id|dump_imap
c_func
(paren
r_const
r_char
op_star
id|prefix
comma
r_struct
id|super_block
op_star
id|s
)paren
(brace
macro_line|#if 0
r_int
id|i
suffix:semicolon
r_char
op_star
id|tmpbuf
op_assign
(paren
r_char
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmpbuf
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|BFS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|si_lasti
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|i
OG
id|PAGE_SIZE
op_minus
l_int|100
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|BFS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|si_imap
)paren
)paren
id|strcat
c_func
(paren
id|tmpbuf
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_else
id|strcat
c_func
(paren
id|tmpbuf
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BFS-fs: %s: lasti=%08lx &lt;%s&gt;&bslash;n&quot;
comma
id|prefix
comma
id|BFS_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|si_lasti
comma
id|tmpbuf
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmpbuf
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bfs_fill_super
r_static
r_int
id|bfs_fill_super
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
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|bfs_super_block
op_star
id|bfs_sb
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
id|i
comma
id|imap_len
suffix:semicolon
r_struct
id|bfs_sb_info
op_star
id|info
suffix:semicolon
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|s-&gt;s_fs_info
op_assign
id|info
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|sb_set_blocksize
c_func
(paren
id|s
comma
id|BFS_BSIZE
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|s
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|bfs_sb
op_assign
(paren
r_struct
id|bfs_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|bfs_sb-&gt;s_magic
op_ne
id|BFS_MAGIC
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printf
c_func
(paren
l_string|&quot;No BFS filesystem on %s (magic=%08x)&bslash;n&quot;
comma
id|s-&gt;s_id
comma
id|bfs_sb-&gt;s_magic
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|BFS_UNCLEAN
c_func
(paren
id|bfs_sb
comma
id|s
)paren
op_logical_and
op_logical_neg
id|silent
)paren
id|printf
c_func
(paren
l_string|&quot;%s is unclean, continuing&bslash;n&quot;
comma
id|s-&gt;s_id
)paren
suffix:semicolon
id|s-&gt;s_magic
op_assign
id|BFS_MAGIC
suffix:semicolon
id|info-&gt;si_bfs_sb
op_assign
id|bfs_sb
suffix:semicolon
id|info-&gt;si_sbh
op_assign
id|bh
suffix:semicolon
id|info-&gt;si_lasti
op_assign
(paren
id|bfs_sb-&gt;s_start
op_minus
id|BFS_BSIZE
)paren
op_div
r_sizeof
(paren
r_struct
id|bfs_inode
)paren
op_plus
id|BFS_ROOT_INO
op_minus
l_int|1
suffix:semicolon
id|imap_len
op_assign
id|info-&gt;si_lasti
op_div
l_int|8
op_plus
l_int|1
suffix:semicolon
id|info-&gt;si_imap
op_assign
id|kmalloc
c_func
(paren
id|imap_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;si_imap
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|info-&gt;si_imap
comma
l_int|0
comma
id|imap_len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BFS_ROOT_INO
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|i
comma
id|info-&gt;si_imap
)paren
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|bfs_sops
suffix:semicolon
id|inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|BFS_ROOT_INO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|kfree
c_func
(paren
id|info-&gt;si_imap
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|s-&gt;s_root
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
id|s-&gt;s_root
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info-&gt;si_imap
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|info-&gt;si_blocks
op_assign
(paren
id|bfs_sb-&gt;s_end
op_plus
l_int|1
)paren
op_rshift
id|BFS_BSIZE_BITS
suffix:semicolon
multiline_comment|/* for statfs(2) */
id|info-&gt;si_freeb
op_assign
(paren
id|bfs_sb-&gt;s_end
op_plus
l_int|1
op_minus
id|bfs_sb-&gt;s_start
)paren
op_rshift
id|BFS_BSIZE_BITS
suffix:semicolon
id|info-&gt;si_freei
op_assign
l_int|0
suffix:semicolon
id|info-&gt;si_lf_eblk
op_assign
l_int|0
suffix:semicolon
id|info-&gt;si_lf_sblk
op_assign
l_int|0
suffix:semicolon
id|info-&gt;si_lf_ioff
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|BFS_ROOT_INO
suffix:semicolon
id|i
op_le
id|info-&gt;si_lasti
suffix:semicolon
id|i
op_increment
)paren
(brace
id|inode
op_assign
id|iget
c_func
(paren
id|s
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_dsk_ino
op_eq
l_int|0
)paren
id|info-&gt;si_freei
op_increment
suffix:semicolon
r_else
(brace
id|set_bit
c_func
(paren
id|i
comma
id|info-&gt;si_imap
)paren
suffix:semicolon
id|info-&gt;si_freeb
op_sub_assign
id|inode-&gt;i_blocks
suffix:semicolon
r_if
c_cond
(paren
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
OG
id|info-&gt;si_lf_eblk
)paren
(brace
id|info-&gt;si_lf_eblk
op_assign
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_eblock
suffix:semicolon
id|info-&gt;si_lf_sblk
op_assign
id|BFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_sblock
suffix:semicolon
id|info-&gt;si_lf_ioff
op_assign
id|BFS_INO2OFF
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
)brace
id|dump_imap
c_func
(paren
l_string|&quot;read_super&quot;
comma
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
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
DECL|function|bfs_get_sb
r_static
r_struct
id|super_block
op_star
id|bfs_get_sb
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
id|bfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|bfs_fs_type
r_static
r_struct
id|file_system_type
id|bfs_fs_type
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
l_string|&quot;bfs&quot;
comma
dot
id|get_sb
op_assign
id|bfs_get_sb
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
DECL|function|init_bfs_fs
r_static
r_int
id|__init
id|init_bfs_fs
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
id|bfs_fs_type
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
DECL|function|exit_bfs_fs
r_static
r_void
id|__exit
id|exit_bfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|bfs_fs_type
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
id|init_bfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_bfs_fs
)paren
eof
