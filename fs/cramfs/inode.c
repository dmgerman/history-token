multiline_comment|/*&n; * Compressed rom filesystem for Linux.&n; *&n; * Copyright (C) 1999 Linus Torvalds.&n; *&n; * This file is released under the GPL.&n; */
multiline_comment|/*&n; * These are the VFS interfaces to the compressed rom filesystem.&n; * The actual compression is based on zlib, see the other files.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/cramfs_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cramfs_fs_sb.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|cramfs_ops
r_static
r_struct
id|super_operations
id|cramfs_ops
suffix:semicolon
DECL|variable|cramfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|cramfs_dir_inode_operations
suffix:semicolon
DECL|variable|cramfs_directory_operations
r_static
r_struct
id|file_operations
id|cramfs_directory_operations
suffix:semicolon
DECL|variable|cramfs_aops
r_static
r_struct
id|address_space_operations
id|cramfs_aops
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|read_mutex
)paren
suffix:semicolon
multiline_comment|/* These two macros may change in future, to provide better st_ino&n;   semantics. */
DECL|macro|CRAMINO
mdefine_line|#define CRAMINO(x)&t;((x)-&gt;offset?(x)-&gt;offset&lt;&lt;2:1)
DECL|macro|OFFSET
mdefine_line|#define OFFSET(x)&t;((x)-&gt;i_ino)
DECL|function|get_cramfs_inode
r_static
r_struct
id|inode
op_star
id|get_cramfs_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|cramfs_inode
op_star
id|cramfs_inode
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_static
r_struct
id|timespec
id|zerotime
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|cramfs_inode-&gt;mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|cramfs_inode-&gt;uid
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|cramfs_inode-&gt;size
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
(paren
id|cramfs_inode-&gt;size
op_minus
l_int|1
)paren
op_div
l_int|512
op_plus
l_int|1
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|cramfs_inode-&gt;gid
suffix:semicolon
multiline_comment|/* Struct copy intentional */
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|zerotime
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|CRAMINO
c_func
(paren
id|cramfs_inode
)paren
suffix:semicolon
multiline_comment|/* inode-&gt;i_nlink is left 1 - arguably wrong for directories,&n;&t;&t;   but it&squot;s the best we can do without reading the directory&n;&t;           contents.  1 yields the right result in GNU find, even&n;&t;&t;   without -noleaf option. */
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_fop
op_assign
op_amp
id|generic_ro_fops
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|cramfs_aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|cramfs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|cramfs_directory_operations
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|cramfs_aops
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_size
op_assign
l_int|0
suffix:semicolon
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|old_decode_dev
c_func
(paren
id|cramfs_inode-&gt;size
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|inode
suffix:semicolon
)brace
multiline_comment|/*&n; * We have our own block cache: don&squot;t fill up the buffer cache&n; * with the rom-image, because the way the filesystem is set&n; * up the accesses should be fairly regular and cached in the&n; * page cache and dentry tree anyway..&n; *&n; * This also acts as a way to guarantee contiguous areas of up to&n; * BLKS_PER_BUF*PAGE_CACHE_SIZE, so that the caller doesn&squot;t need to&n; * worry about end-of-buffer issues even when decompressing a full&n; * page cache.&n; */
DECL|macro|READ_BUFFERS
mdefine_line|#define READ_BUFFERS (2)
multiline_comment|/* NEXT_BUFFER(): Loop over [0..(READ_BUFFERS-1)]. */
DECL|macro|NEXT_BUFFER
mdefine_line|#define NEXT_BUFFER(_ix) ((_ix) ^ 1)
multiline_comment|/*&n; * BLKS_PER_BUF_SHIFT should be at least 2 to allow for &quot;compressed&quot;&n; * data that takes up more space than the original and with unlucky&n; * alignment.&n; */
DECL|macro|BLKS_PER_BUF_SHIFT
mdefine_line|#define BLKS_PER_BUF_SHIFT&t;(2)
DECL|macro|BLKS_PER_BUF
mdefine_line|#define BLKS_PER_BUF&t;&t;(1 &lt;&lt; BLKS_PER_BUF_SHIFT)
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;&t;(BLKS_PER_BUF*PAGE_CACHE_SIZE)
DECL|variable|read_buffers
r_static
r_int
r_char
id|read_buffers
(braket
id|READ_BUFFERS
)braket
(braket
id|BUFFER_SIZE
)braket
suffix:semicolon
DECL|variable|buffer_blocknr
r_static
r_int
id|buffer_blocknr
(braket
id|READ_BUFFERS
)braket
suffix:semicolon
DECL|variable|buffer_dev
r_static
r_struct
id|super_block
op_star
id|buffer_dev
(braket
id|READ_BUFFERS
)braket
suffix:semicolon
DECL|variable|next_buffer
r_static
r_int
id|next_buffer
suffix:semicolon
multiline_comment|/*&n; * Returns a pointer to a buffer containing at least LEN bytes of&n; * filesystem starting at byte offset OFFSET into the filesystem.&n; */
DECL|function|cramfs_read
r_static
r_void
op_star
id|cramfs_read
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|pages
(braket
id|BLKS_PER_BUF
)braket
suffix:semicolon
r_int
id|i
comma
id|blocknr
comma
id|buffer
comma
id|unread
suffix:semicolon
r_int
r_int
id|devsize
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
id|blocknr
op_assign
id|offset
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|offset
op_and_assign
id|PAGE_CACHE_SIZE
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Check if an existing buffer already has the data.. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|READ_BUFFERS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|blk_offset
suffix:semicolon
r_if
c_cond
(paren
id|buffer_dev
(braket
id|i
)braket
op_ne
id|sb
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|blocknr
OL
id|buffer_blocknr
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|blk_offset
op_assign
(paren
id|blocknr
op_minus
id|buffer_blocknr
(braket
id|i
)braket
)paren
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|blk_offset
op_add_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|blk_offset
op_plus
id|len
OG
id|BUFFER_SIZE
)paren
r_continue
suffix:semicolon
r_return
id|read_buffers
(braket
id|i
)braket
op_plus
id|blk_offset
suffix:semicolon
)brace
id|devsize
op_assign
id|mapping-&gt;host-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* Ok, read in BLKS_PER_BUF pages completely first. */
id|unread
op_assign
l_int|0
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
id|BLKS_PER_BUF
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|blocknr
op_plus
id|i
OL
id|devsize
)paren
(brace
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|blocknr
op_plus
id|i
comma
(paren
id|filler_t
op_star
)paren
id|mapping-&gt;a_ops-&gt;readpage
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* synchronous error? */
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
id|page
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pages
(braket
id|i
)braket
op_assign
id|page
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BLKS_PER_BUF
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pages
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
multiline_comment|/* asynchronous error */
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|pages
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
id|buffer
op_assign
id|next_buffer
suffix:semicolon
id|next_buffer
op_assign
id|NEXT_BUFFER
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|buffer_blocknr
(braket
id|buffer
)braket
op_assign
id|blocknr
suffix:semicolon
id|buffer_dev
(braket
id|buffer
)braket
op_assign
id|sb
suffix:semicolon
id|data
op_assign
id|read_buffers
(braket
id|buffer
)braket
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
id|BLKS_PER_BUF
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pages
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|memcpy
c_func
(paren
id|data
comma
id|kmap
c_func
(paren
id|page
)paren
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|data
op_add_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_return
id|read_buffers
(braket
id|buffer
)braket
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|cramfs_put_super
r_static
r_void
id|cramfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
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
DECL|function|cramfs_fill_super
r_static
r_int
id|cramfs_fill_super
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
r_int
id|i
suffix:semicolon
r_struct
id|cramfs_super
id|super
suffix:semicolon
r_int
r_int
id|root_offset
suffix:semicolon
r_struct
id|cramfs_sb_info
op_star
id|sbi
suffix:semicolon
id|sbi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cramfs_sb_info
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
r_struct
id|cramfs_sb_info
)paren
)paren
suffix:semicolon
multiline_comment|/* Invalidate the read buffers on mount: think disk change.. */
id|down
c_func
(paren
op_amp
id|read_mutex
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
id|READ_BUFFERS
suffix:semicolon
id|i
op_increment
)paren
id|buffer_blocknr
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Read the first block and get the superblock from it */
id|memcpy
c_func
(paren
op_amp
id|super
comma
id|cramfs_read
c_func
(paren
id|sb
comma
l_int|0
comma
r_sizeof
(paren
id|super
)paren
)paren
comma
r_sizeof
(paren
id|super
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
multiline_comment|/* Do sanity checks on the superblock */
r_if
c_cond
(paren
id|super.magic
op_ne
id|CRAMFS_MAGIC
)paren
(brace
multiline_comment|/* check at 512 byte offset */
id|down
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|super
comma
id|cramfs_read
c_func
(paren
id|sb
comma
l_int|512
comma
r_sizeof
(paren
id|super
)paren
)paren
comma
r_sizeof
(paren
id|super
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|super.magic
op_ne
id|CRAMFS_MAGIC
)paren
(brace
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
l_string|&quot;cramfs: wrong magic&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
multiline_comment|/* get feature flags first */
r_if
c_cond
(paren
id|super.flags
op_amp
op_complement
id|CRAMFS_SUPPORTED_FLAGS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cramfs: unsupported filesystem features&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Check that the root inode is in a sane state */
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|super.root.mode
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cramfs: root is not a directory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|root_offset
op_assign
id|super.root.offset
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|super.flags
op_amp
id|CRAMFS_FLAG_FSID_VERSION_2
)paren
(brace
id|sbi-&gt;size
op_assign
id|super.size
suffix:semicolon
id|sbi-&gt;blocks
op_assign
id|super.fsid.blocks
suffix:semicolon
id|sbi-&gt;files
op_assign
id|super.fsid.files
suffix:semicolon
)brace
r_else
(brace
id|sbi-&gt;size
op_assign
l_int|1
op_lshift
l_int|28
suffix:semicolon
id|sbi-&gt;blocks
op_assign
l_int|0
suffix:semicolon
id|sbi-&gt;files
op_assign
l_int|0
suffix:semicolon
)brace
id|sbi-&gt;magic
op_assign
id|super.magic
suffix:semicolon
id|sbi-&gt;flags
op_assign
id|super.flags
suffix:semicolon
r_if
c_cond
(paren
id|root_offset
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cramfs: empty filesystem&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|super.flags
op_amp
id|CRAMFS_FLAG_SHIFTED_ROOT_OFFSET
)paren
op_logical_and
(paren
(paren
id|root_offset
op_ne
r_sizeof
(paren
r_struct
id|cramfs_super
)paren
)paren
op_logical_and
(paren
id|root_offset
op_ne
l_int|512
op_plus
r_sizeof
(paren
r_struct
id|cramfs_super
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cramfs: bad root offset %lu&bslash;n&quot;
comma
id|root_offset
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Set it all up.. */
id|sb-&gt;s_op
op_assign
op_amp
id|cramfs_ops
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|get_cramfs_inode
c_func
(paren
id|sb
comma
op_amp
id|super.root
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
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
DECL|function|cramfs_statfs
r_static
r_int
id|cramfs_statfs
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
id|buf-&gt;f_type
op_assign
id|CRAMFS_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|CRAMFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|blocks
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|CRAMFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|files
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|CRAMFS_MAXPATHLEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a cramfs directory entry.&n; */
DECL|function|cramfs_readdir
r_static
r_int
id|cramfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|copied
suffix:semicolon
multiline_comment|/* Offset within the thing. */
id|offset
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|inode-&gt;i_size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Directory entries are always 4-byte aligned */
r_if
c_cond
(paren
id|offset
op_amp
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
l_int|256
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|inode-&gt;i_size
)paren
(brace
r_struct
id|cramfs_inode
op_star
id|de
suffix:semicolon
r_int
r_int
id|nextoffset
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
id|mode_t
id|mode
suffix:semicolon
r_int
id|namelen
comma
id|error
suffix:semicolon
id|down
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|de
op_assign
id|cramfs_read
c_func
(paren
id|sb
comma
id|OFFSET
c_func
(paren
id|inode
)paren
op_plus
id|offset
comma
r_sizeof
(paren
op_star
id|de
)paren
op_plus
l_int|256
)paren
suffix:semicolon
id|name
op_assign
(paren
r_char
op_star
)paren
(paren
id|de
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Namelengths on disk are shifted by two&n;&t;&t; * and the name padded out to 4-byte boundaries&n;&t;&t; * with zeroes.&n;&t;&t; */
id|namelen
op_assign
id|de-&gt;namelen
op_lshift
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|ino
op_assign
id|CRAMINO
c_func
(paren
id|de
)paren
suffix:semicolon
id|mode
op_assign
id|de-&gt;mode
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|nextoffset
op_assign
id|offset
op_plus
r_sizeof
(paren
op_star
id|de
)paren
op_plus
id|namelen
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf
(braket
id|namelen
op_minus
l_int|1
)braket
)paren
r_break
suffix:semicolon
id|namelen
op_decrement
suffix:semicolon
)brace
id|error
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|buf
comma
id|namelen
comma
id|offset
comma
id|ino
comma
id|mode
op_rshift
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_break
suffix:semicolon
id|offset
op_assign
id|nextoffset
suffix:semicolon
id|filp-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|copied
op_increment
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Lookup and fill in the inode data..&n; */
DECL|function|cramfs_lookup
r_static
r_struct
id|dentry
op_star
id|cramfs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
id|sorted
suffix:semicolon
id|down
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|sorted
op_assign
id|CRAMFS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|flags
op_amp
id|CRAMFS_FLAG_SORTED_DIRS
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|dir-&gt;i_size
)paren
(brace
r_struct
id|cramfs_inode
op_star
id|de
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|namelen
comma
id|retval
suffix:semicolon
id|de
op_assign
id|cramfs_read
c_func
(paren
id|dir-&gt;i_sb
comma
id|OFFSET
c_func
(paren
id|dir
)paren
op_plus
id|offset
comma
r_sizeof
(paren
op_star
id|de
)paren
op_plus
l_int|256
)paren
suffix:semicolon
id|name
op_assign
(paren
r_char
op_star
)paren
(paren
id|de
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Try to take advantage of sorted directories */
r_if
c_cond
(paren
id|sorted
op_logical_and
(paren
id|dentry-&gt;d_name.name
(braket
l_int|0
)braket
OL
id|name
(braket
l_int|0
)braket
)paren
)paren
r_break
suffix:semicolon
id|namelen
op_assign
id|de-&gt;namelen
op_lshift
l_int|2
suffix:semicolon
id|offset
op_add_assign
r_sizeof
(paren
op_star
id|de
)paren
op_plus
id|namelen
suffix:semicolon
multiline_comment|/* Quick check that the name is roughly the right length */
r_if
c_cond
(paren
(paren
(paren
id|dentry-&gt;d_name.len
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
)paren
op_ne
id|namelen
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|namelen
)paren
(brace
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|name
(braket
id|namelen
op_minus
l_int|1
)braket
)paren
r_break
suffix:semicolon
id|namelen
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|namelen
op_ne
id|dentry-&gt;d_name.len
)paren
r_continue
suffix:semicolon
id|retval
op_assign
id|memcmp
c_func
(paren
id|dentry-&gt;d_name.name
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_struct
id|cramfs_inode
id|entry
op_assign
op_star
id|de
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
id|get_cramfs_inode
c_func
(paren
id|dir-&gt;i_sb
comma
op_amp
id|entry
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* else (retval &lt; 0) */
r_if
c_cond
(paren
id|sorted
)paren
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cramfs_readpage
r_static
r_int
id|cramfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
id|u32
id|maxblock
comma
id|bytes_filled
suffix:semicolon
r_void
op_star
id|pgdata
suffix:semicolon
id|maxblock
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|bytes_filled
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
OL
id|maxblock
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|u32
id|blkptr_offset
op_assign
id|OFFSET
c_func
(paren
id|inode
)paren
op_plus
id|page-&gt;index
op_star
l_int|4
suffix:semicolon
id|u32
id|start_offset
comma
id|compr_len
suffix:semicolon
id|start_offset
op_assign
id|OFFSET
c_func
(paren
id|inode
)paren
op_plus
id|maxblock
op_star
l_int|4
suffix:semicolon
id|down
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;index
)paren
id|start_offset
op_assign
op_star
(paren
id|u32
op_star
)paren
id|cramfs_read
c_func
(paren
id|sb
comma
id|blkptr_offset
op_minus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
id|compr_len
op_assign
(paren
op_star
(paren
id|u32
op_star
)paren
id|cramfs_read
c_func
(paren
id|sb
comma
id|blkptr_offset
comma
l_int|4
)paren
op_minus
id|start_offset
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|pgdata
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compr_len
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* hole */
r_else
(brace
id|down
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
id|bytes_filled
op_assign
id|cramfs_uncompress_block
c_func
(paren
id|pgdata
comma
id|PAGE_CACHE_SIZE
comma
id|cramfs_read
c_func
(paren
id|sb
comma
id|start_offset
comma
id|compr_len
)paren
comma
id|compr_len
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|read_mutex
)paren
suffix:semicolon
)brace
)brace
r_else
id|pgdata
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pgdata
op_plus
id|bytes_filled
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
op_minus
id|bytes_filled
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cramfs_aops
r_static
r_struct
id|address_space_operations
id|cramfs_aops
op_assign
(brace
dot
id|readpage
op_assign
id|cramfs_readpage
)brace
suffix:semicolon
multiline_comment|/*&n; * Our operations:&n; */
multiline_comment|/*&n; * A directory can only readdir&n; */
DECL|variable|cramfs_directory_operations
r_static
r_struct
id|file_operations
id|cramfs_directory_operations
op_assign
(brace
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|cramfs_readdir
comma
)brace
suffix:semicolon
DECL|variable|cramfs_dir_inode_operations
r_static
r_struct
id|inode_operations
id|cramfs_dir_inode_operations
op_assign
(brace
dot
id|lookup
op_assign
id|cramfs_lookup
comma
)brace
suffix:semicolon
DECL|variable|cramfs_ops
r_static
r_struct
id|super_operations
id|cramfs_ops
op_assign
(brace
dot
id|put_super
op_assign
id|cramfs_put_super
comma
dot
id|statfs
op_assign
id|cramfs_statfs
comma
)brace
suffix:semicolon
DECL|function|cramfs_get_sb
r_static
r_struct
id|super_block
op_star
id|cramfs_get_sb
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
id|cramfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|cramfs_fs_type
r_static
r_struct
id|file_system_type
id|cramfs_fs_type
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
l_string|&quot;cramfs&quot;
comma
dot
id|get_sb
op_assign
id|cramfs_get_sb
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
DECL|function|init_cramfs_fs
r_static
r_int
id|__init
id|init_cramfs_fs
c_func
(paren
r_void
)paren
(brace
id|cramfs_uncompress_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|register_filesystem
c_func
(paren
op_amp
id|cramfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_cramfs_fs
r_static
r_void
id|__exit
id|exit_cramfs_fs
c_func
(paren
r_void
)paren
(brace
id|cramfs_uncompress_exit
c_func
(paren
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|cramfs_fs_type
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_cramfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_cramfs_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
