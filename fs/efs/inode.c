multiline_comment|/*&n; * inode.c&n; *&n; * Copyright (c) 1999 Al Smith&n; *&n; * Portions derived from work (c) 1995,1996 Christian Vogelgsang,&n; *              and from work (c) 1998 Mike Shaver.&n; */
macro_line|#include &lt;linux/efs_fs.h&gt;
macro_line|#include &lt;linux/efs_fs_sb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
r_extern
r_int
id|efs_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|efs_readpage
r_static
r_int
id|efs_readpage
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
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|efs_get_block
)paren
suffix:semicolon
)brace
DECL|function|_efs_bmap
r_static
r_int
id|_efs_bmap
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
id|block
)paren
(brace
r_return
id|generic_block_bmap
c_func
(paren
id|mapping
comma
id|block
comma
id|efs_get_block
)paren
suffix:semicolon
)brace
DECL|variable|efs_aops
r_struct
id|address_space_operations
id|efs_aops
op_assign
(brace
id|readpage
suffix:colon
id|efs_readpage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|bmap
suffix:colon
id|_efs_bmap
)brace
suffix:semicolon
DECL|function|extent_copy
r_static
r_inline
r_void
id|extent_copy
c_func
(paren
id|efs_extent
op_star
id|src
comma
id|efs_extent
op_star
id|dst
)paren
(brace
multiline_comment|/*&n;&t; * this is slightly evil. it doesn&squot;t just copy&n;&t; * efs_extent from src to dst, it also mangles&n;&t; * the bits so that dst ends up in cpu byte-order.&n;&t; */
id|dst-&gt;cooked.ex_magic
op_assign
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|0
)braket
suffix:semicolon
id|dst-&gt;cooked.ex_bn
op_assign
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|3
)braket
op_lshift
l_int|0
)paren
suffix:semicolon
id|dst-&gt;cooked.ex_length
op_assign
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|4
)braket
suffix:semicolon
id|dst-&gt;cooked.ex_offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|5
)braket
op_lshift
l_int|16
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|6
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|src-&gt;raw
(braket
l_int|7
)braket
op_lshift
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|efs_read_inode
r_void
id|efs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|i
comma
id|inode_index
suffix:semicolon
id|dev_t
id|device
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|efs_sb_info
op_star
id|sb
op_assign
id|SUPER_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|efs_inode_info
op_star
id|in
op_assign
id|INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
id|efs_block_t
id|block
comma
id|offset
suffix:semicolon
r_struct
id|efs_dinode
op_star
id|efs_inode
suffix:semicolon
multiline_comment|/*&n;&t;** EFS layout:&n;&t;**&n;&t;** |   cylinder group    |   cylinder group    |   cylinder group ..etc&n;&t;** |inodes|data          |inodes|data          |inodes|data       ..etc&n;&t;**&n;&t;** work out the inode block index, (considering initially that the&n;&t;** inodes are stored as consecutive blocks). then work out the block&n;&t;** number of that inode given the above layout, and finally the&n;&t;** offset of the inode within that block.&n;&t;*/
id|inode_index
op_assign
id|inode-&gt;i_ino
op_div
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
r_struct
id|efs_dinode
)paren
)paren
suffix:semicolon
id|block
op_assign
id|sb-&gt;fs_start
op_plus
id|sb-&gt;first_block
op_plus
(paren
id|sb-&gt;group_size
op_star
(paren
id|inode_index
op_div
id|sb-&gt;inode_blocks
)paren
)paren
op_plus
(paren
id|inode_index
op_mod
id|sb-&gt;inode_blocks
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|inode-&gt;i_ino
op_mod
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
r_struct
id|efs_dinode
)paren
)paren
)paren
op_star
r_sizeof
(paren
r_struct
id|efs_dinode
)paren
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: bread() failed at block %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|read_inode_error
suffix:semicolon
)brace
id|efs_inode
op_assign
(paren
r_struct
id|efs_dinode
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_mode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_nlink
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_gid
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|be32_to_cpu
c_func
(paren
id|efs_inode-&gt;di_size
)paren
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|be32_to_cpu
c_func
(paren
id|efs_inode-&gt;di_atime
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|be32_to_cpu
c_func
(paren
id|efs_inode-&gt;di_mtime
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|be32_to_cpu
c_func
(paren
id|efs_inode-&gt;di_ctime
)paren
suffix:semicolon
multiline_comment|/* this is the number of blocks in the file */
r_if
c_cond
(paren
id|inode-&gt;i_size
op_eq
l_int|0
)paren
(brace
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_blocks
op_assign
(paren
(paren
id|inode-&gt;i_size
op_minus
l_int|1
)paren
op_rshift
id|EFS_BLOCKSIZE_BITS
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * BUG: irix dev_t is 32-bits. linux dev_t is only 16-bits.&n;&t; *&n;&t; * apparently linux will change to 32-bit dev_t sometime during&n;&t; * linux 2.3.&n;&t; *&n;&t; * as is, this code maps devices that can&squot;t be represented in&n;&t; * 16-bits (ie major &gt; 255 or minor &gt; 255) to major = minor = 255.&n;&t; *&n;&t; * during 2.3 when 32-bit dev_t become available, we should test&n;&t; * to see whether odev contains 65535. if this is the case then we&n;&t; * should then do device = be32_to_cpu(efs_inode-&gt;di_u.di_dev.ndev).&n;&t; */
id|device
op_assign
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_u.di_dev.odev
)paren
suffix:semicolon
multiline_comment|/* get the number of extents for this object */
id|in-&gt;numextents
op_assign
id|be16_to_cpu
c_func
(paren
id|efs_inode-&gt;di_numextents
)paren
suffix:semicolon
id|in-&gt;lastextent
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* copy the extents contained within the inode to memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EFS_DIRECTEXTENTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|extent_copy
c_func
(paren
op_amp
(paren
id|efs_inode-&gt;di_u.di_extents
(braket
id|i
)braket
)paren
comma
op_amp
(paren
id|in-&gt;extents
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|in-&gt;numextents
op_logical_and
id|in-&gt;extents
(braket
id|i
)braket
dot
id|cooked.ex_magic
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: extent %d has bad magic number in inode %lu&bslash;n&quot;
comma
id|i
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_goto
id|read_inode_error
suffix:semicolon
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: read_inode(): inode %lu, extents %d, mode %o&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|in-&gt;numextents
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
(brace
r_case
id|S_IFDIR
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|efs_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|efs_dir_operations
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFREG
suffix:colon
id|inode-&gt;i_fop
op_assign
op_amp
id|generic_ro_fops
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|efs_aops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFLNK
suffix:colon
id|inode-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|efs_symlink_aops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|S_IFCHR
suffix:colon
r_case
id|S_IFBLK
suffix:colon
r_case
id|S_IFIFO
suffix:colon
id|init_special_inode
c_func
(paren
id|inode
comma
id|inode-&gt;i_mode
comma
id|device
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: unsupported inode mode %o&bslash;n&quot;
comma
id|inode-&gt;i_mode
)paren
suffix:semicolon
r_goto
id|read_inode_error
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
id|read_inode_error
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;EFS: failed to read inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
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
r_static
r_inline
id|efs_block_t
DECL|function|efs_extent_check
id|efs_extent_check
c_func
(paren
id|efs_extent
op_star
id|ptr
comma
id|efs_block_t
id|block
comma
r_struct
id|efs_sb_info
op_star
id|sb
)paren
(brace
id|efs_block_t
id|start
suffix:semicolon
id|efs_block_t
id|length
suffix:semicolon
id|efs_block_t
id|offset
suffix:semicolon
multiline_comment|/*&n;&t; * given an extent and a logical block within a file,&n;&t; * can this block be found within this extent ?&n;&t; */
id|start
op_assign
id|ptr-&gt;cooked.ex_bn
suffix:semicolon
id|length
op_assign
id|ptr-&gt;cooked.ex_length
suffix:semicolon
id|offset
op_assign
id|ptr-&gt;cooked.ex_offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_ge
id|offset
)paren
op_logical_and
(paren
id|block
OL
id|offset
op_plus
id|length
)paren
)paren
(brace
r_return
id|sb-&gt;fs_start
op_plus
id|start
op_plus
id|block
op_minus
id|offset
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|efs_map_block
id|efs_block_t
id|efs_map_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|efs_block_t
id|block
)paren
(brace
r_struct
id|efs_sb_info
op_star
id|sb
op_assign
id|SUPER_INFO
c_func
(paren
id|inode-&gt;i_sb
)paren
suffix:semicolon
r_struct
id|efs_inode_info
op_star
id|in
op_assign
id|INODE_INFO
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cur
comma
id|last
comma
id|first
op_assign
l_int|1
suffix:semicolon
r_int
id|ibase
comma
id|ioffset
comma
id|dirext
comma
id|direxts
comma
id|indext
comma
id|indexts
suffix:semicolon
id|efs_block_t
id|iblock
comma
id|result
op_assign
l_int|0
comma
id|lastblock
op_assign
l_int|0
suffix:semicolon
id|efs_extent
id|ext
comma
op_star
id|exts
suffix:semicolon
id|last
op_assign
id|in-&gt;lastextent
suffix:semicolon
r_if
c_cond
(paren
id|in-&gt;numextents
op_le
id|EFS_DIRECTEXTENTS
)paren
(brace
multiline_comment|/* first check the last extent we returned */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|efs_extent_check
c_func
(paren
op_amp
id|in-&gt;extents
(braket
id|last
)braket
comma
id|block
comma
id|sb
)paren
)paren
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* if we only have one extent then nothing can be found */
r_if
c_cond
(paren
id|in-&gt;numextents
op_eq
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: map_block() failed to map (1 extent)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|direxts
op_assign
id|in-&gt;numextents
suffix:semicolon
multiline_comment|/*&n;&t;&t; * check the stored extents in the inode&n;&t;&t; * start with next extent and check forwards&n;&t;&t; */
r_for
c_loop
(paren
id|dirext
op_assign
l_int|1
suffix:semicolon
id|dirext
OL
id|direxts
suffix:semicolon
id|dirext
op_increment
)paren
(brace
id|cur
op_assign
(paren
id|last
op_plus
id|dirext
)paren
op_mod
id|in-&gt;numextents
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|efs_extent_check
c_func
(paren
op_amp
id|in-&gt;extents
(braket
id|cur
)braket
comma
id|block
comma
id|sb
)paren
)paren
)paren
(brace
id|in-&gt;lastextent
op_assign
id|cur
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: map_block() failed to map block %u (dir)&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: map_block(): indirect search for logical block %u&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
macro_line|#endif
id|direxts
op_assign
id|in-&gt;extents
(braket
l_int|0
)braket
dot
id|cooked.ex_offset
suffix:semicolon
id|indexts
op_assign
id|in-&gt;numextents
suffix:semicolon
r_for
c_loop
(paren
id|indext
op_assign
l_int|0
suffix:semicolon
id|indext
OL
id|indexts
suffix:semicolon
id|indext
op_increment
)paren
(brace
id|cur
op_assign
(paren
id|last
op_plus
id|indext
)paren
op_mod
id|indexts
suffix:semicolon
multiline_comment|/*&n;&t;&t; * work out which direct extent contains `cur&squot;.&n;&t;&t; *&n;&t;&t; * also compute ibase: i.e. the number of the first&n;&t;&t; * indirect extent contained within direct extent `cur&squot;.&n;&t;&t; *&n;&t;&t; */
id|ibase
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|dirext
op_assign
l_int|0
suffix:semicolon
id|cur
OL
id|ibase
op_logical_and
id|dirext
OL
id|direxts
suffix:semicolon
id|dirext
op_increment
)paren
(brace
id|ibase
op_add_assign
id|in-&gt;extents
(braket
id|dirext
)braket
dot
id|cooked.ex_length
op_star
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
id|efs_extent
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dirext
op_eq
id|direxts
)paren
(brace
multiline_comment|/* should never happen */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: couldn&squot;t find direct extent for indirect extent %d (block %u)&bslash;n&quot;
comma
id|cur
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* work out block number and offset of this indirect extent */
id|iblock
op_assign
id|sb-&gt;fs_start
op_plus
id|in-&gt;extents
(braket
id|dirext
)braket
dot
id|cooked.ex_bn
op_plus
(paren
id|cur
op_minus
id|ibase
)paren
op_div
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
id|efs_extent
)paren
)paren
suffix:semicolon
id|ioffset
op_assign
(paren
id|cur
op_minus
id|ibase
)paren
op_mod
(paren
id|EFS_BLOCKSIZE
op_div
r_sizeof
(paren
id|efs_extent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
op_logical_or
id|lastblock
op_ne
id|iblock
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: bread() failed at block %d&bslash;n&quot;
comma
id|iblock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;EFS: map_block(): read indirect extent block %d&bslash;n&quot;
comma
id|iblock
)paren
suffix:semicolon
macro_line|#endif
id|first
op_assign
l_int|0
suffix:semicolon
id|lastblock
op_assign
id|iblock
suffix:semicolon
)brace
id|exts
op_assign
(paren
id|efs_extent
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|extent_copy
c_func
(paren
op_amp
(paren
id|exts
(braket
id|ioffset
)braket
)paren
comma
op_amp
id|ext
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext.cooked.ex_magic
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: extent %d has bad magic number in block %d&bslash;n&quot;
comma
id|cur
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|efs_extent_check
c_func
(paren
op_amp
id|ext
comma
id|block
comma
id|sb
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|in-&gt;lastextent
op_assign
id|cur
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EFS: map_block() failed to map block %u (indir)&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
