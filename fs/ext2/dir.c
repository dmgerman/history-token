multiline_comment|/*&n; *  linux/fs/ext2/dir.c&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/fs/minix/dir.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext2 directory handling functions&n; *&n; *  Big-endian to little-endian byte-swapping/bitmaps by&n; *        David S. Miller (davem@caip.rutgers.edu), 1995&n; *&n; * All code that works with directory layout had been switched to pagecache&n; * and moved here. AV&n; */
macro_line|#include &quot;ext2.h&quot;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|typedef|ext2_dirent
r_typedef
r_struct
id|ext2_dir_entry_2
id|ext2_dirent
suffix:semicolon
multiline_comment|/*&n; * ext2 uses block-sized chunks. Arguably, sector-sized ones would be&n; * more robust, but we have what we have&n; */
DECL|function|ext2_chunk_size
r_static
r_inline
r_int
id|ext2_chunk_size
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|inode-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
)brace
DECL|function|ext2_put_page
r_static
r_inline
r_void
id|ext2_put_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
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
DECL|function|dir_pages
r_static
r_inline
r_int
r_int
id|dir_pages
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
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
)brace
multiline_comment|/*&n; * Return the offset into page `page_nr&squot; of the last valid&n; * byte in that page, plus one.&n; */
r_static
r_int
DECL|function|ext2_last_byte
id|ext2_last_byte
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|page_nr
)paren
(brace
r_int
id|last_byte
op_assign
id|inode-&gt;i_size
suffix:semicolon
id|last_byte
op_sub_assign
id|page_nr
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|last_byte
OG
id|PAGE_CACHE_SIZE
)paren
id|last_byte
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_return
id|last_byte
suffix:semicolon
)brace
DECL|function|ext2_commit_chunk
r_static
r_int
id|ext2_commit_chunk
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|dir-&gt;i_version
op_increment
suffix:semicolon
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|commit_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_DIRSYNC
c_func
(paren
id|dir
)paren
)paren
id|err
op_assign
id|write_one_page
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
r_else
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ext2_check_page
r_static
r_void
id|ext2_check_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_int
id|chunk_size
op_assign
id|ext2_chunk_size
c_func
(paren
id|dir
)paren
suffix:semicolon
r_char
op_star
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|u32
id|max_inumber
op_assign
id|le32_to_cpu
c_func
(paren
id|EXT2_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_es-&gt;s_inodes_count
)paren
suffix:semicolon
r_int
id|offs
comma
id|rec_len
suffix:semicolon
r_int
id|limit
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|ext2_dirent
op_star
id|p
suffix:semicolon
r_char
op_star
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
)paren
op_eq
id|page-&gt;index
)paren
(brace
id|limit
op_assign
id|dir-&gt;i_size
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|limit
op_amp
(paren
id|chunk_size
op_minus
l_int|1
)paren
)paren
r_goto
id|Ebadsize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|limit
)paren
r_goto
id|out
suffix:semicolon
)brace
r_for
c_loop
(paren
id|offs
op_assign
l_int|0
suffix:semicolon
id|offs
op_le
id|limit
op_minus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|offs
op_add_assign
id|rec_len
)paren
(brace
id|p
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|kaddr
op_plus
id|offs
)paren
suffix:semicolon
id|rec_len
op_assign
id|le16_to_cpu
c_func
(paren
id|p-&gt;rec_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec_len
OL
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
r_goto
id|Eshort
suffix:semicolon
r_if
c_cond
(paren
id|rec_len
op_amp
l_int|3
)paren
r_goto
id|Ealign
suffix:semicolon
r_if
c_cond
(paren
id|rec_len
OL
id|EXT2_DIR_REC_LEN
c_func
(paren
id|p-&gt;name_len
)paren
)paren
r_goto
id|Enamelen
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|offs
op_plus
id|rec_len
op_minus
l_int|1
)paren
op_xor
id|offs
)paren
op_amp
op_complement
(paren
id|chunk_size
op_minus
l_int|1
)paren
)paren
r_goto
id|Espan
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|p-&gt;inode
)paren
OG
id|max_inumber
)paren
r_goto
id|Einumber
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offs
op_ne
id|limit
)paren
r_goto
id|Eend
suffix:semicolon
id|out
suffix:colon
id|SetPageChecked
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Too bad, we had an error */
id|Ebadsize
suffix:colon
id|ext2_error
c_func
(paren
id|sb
comma
l_string|&quot;ext2_check_page&quot;
comma
l_string|&quot;size of directory #%lu is not a multiple of chunk size&quot;
comma
id|dir-&gt;i_ino
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
id|Eshort
suffix:colon
id|error
op_assign
l_string|&quot;rec_len is smaller than minimal&quot;
suffix:semicolon
r_goto
id|bad_entry
suffix:semicolon
id|Ealign
suffix:colon
id|error
op_assign
l_string|&quot;unaligned directory entry&quot;
suffix:semicolon
r_goto
id|bad_entry
suffix:semicolon
id|Enamelen
suffix:colon
id|error
op_assign
l_string|&quot;rec_len is too small for name_len&quot;
suffix:semicolon
r_goto
id|bad_entry
suffix:semicolon
id|Espan
suffix:colon
id|error
op_assign
l_string|&quot;directory entry across blocks&quot;
suffix:semicolon
r_goto
id|bad_entry
suffix:semicolon
id|Einumber
suffix:colon
id|error
op_assign
l_string|&quot;inode out of bounds&quot;
suffix:semicolon
id|bad_entry
suffix:colon
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_page&quot;
comma
l_string|&quot;bad entry in directory #%lu: %s - &quot;
l_string|&quot;offset=%lu, inode=%lu, rec_len=%d, name_len=%d&quot;
comma
id|dir-&gt;i_ino
comma
id|error
comma
(paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|offs
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|p-&gt;inode
)paren
comma
id|rec_len
comma
id|p-&gt;name_len
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
id|Eend
suffix:colon
id|p
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|kaddr
op_plus
id|offs
)paren
suffix:semicolon
id|ext2_error
(paren
id|sb
comma
l_string|&quot;ext2_check_page&quot;
comma
l_string|&quot;entry in directory #%lu spans the page boundary&quot;
l_string|&quot;offset=%lu, inode=%lu&quot;
comma
id|dir-&gt;i_ino
comma
(paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|offs
comma
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|p-&gt;inode
)paren
)paren
suffix:semicolon
id|fail
suffix:colon
id|SetPageChecked
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|ext2_get_page
r_static
r_struct
id|page
op_star
id|ext2_get_page
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|dir-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|read_cache_page
c_func
(paren
id|mapping
comma
id|n
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
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|wait_on_page_locked
c_func
(paren
id|page
)paren
suffix:semicolon
id|kmap
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
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageChecked
c_func
(paren
id|page
)paren
)paren
id|ext2_check_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
id|fail
suffix:colon
id|ext2_put_page
c_func
(paren
id|page
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
multiline_comment|/*&n; * NOTE! unlike strncmp, ext2_match returns 1 for success, 0 for failure.&n; *&n; * len &lt;= EXT2_NAME_LEN and de != NULL are guaranteed by caller.&n; */
DECL|function|ext2_match
r_static
r_inline
r_int
id|ext2_match
(paren
r_int
id|len
comma
r_const
r_char
op_star
r_const
id|name
comma
r_struct
id|ext2_dir_entry_2
op_star
id|de
)paren
(brace
r_if
c_cond
(paren
id|len
op_ne
id|de-&gt;name_len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
id|de-&gt;name
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * p is at least 6 bytes before the end of page&n; */
DECL|function|ext2_next_entry
r_static
r_inline
id|ext2_dirent
op_star
id|ext2_next_entry
c_func
(paren
id|ext2_dirent
op_star
id|p
)paren
(brace
r_return
(paren
id|ext2_dirent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|p
op_plus
id|le16_to_cpu
c_func
(paren
id|p-&gt;rec_len
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|ext2_validate_entry
id|ext2_validate_entry
c_func
(paren
r_char
op_star
id|base
comma
r_int
id|offset
comma
r_int
id|mask
)paren
(brace
id|ext2_dirent
op_star
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|base
op_plus
id|offset
)paren
suffix:semicolon
id|ext2_dirent
op_star
id|p
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|base
op_plus
(paren
id|offset
op_amp
id|mask
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|p
OL
(paren
r_char
op_star
)paren
id|de
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;rec_len
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|p
op_assign
id|ext2_next_entry
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_return
(paren
r_char
op_star
)paren
id|p
op_minus
id|base
suffix:semicolon
)brace
DECL|variable|ext2_filetype_table
r_static
r_int
r_char
id|ext2_filetype_table
(braket
id|EXT2_FT_MAX
)braket
op_assign
(brace
(braket
id|EXT2_FT_UNKNOWN
)braket
op_assign
id|DT_UNKNOWN
comma
(braket
id|EXT2_FT_REG_FILE
)braket
op_assign
id|DT_REG
comma
(braket
id|EXT2_FT_DIR
)braket
op_assign
id|DT_DIR
comma
(braket
id|EXT2_FT_CHRDEV
)braket
op_assign
id|DT_CHR
comma
(braket
id|EXT2_FT_BLKDEV
)braket
op_assign
id|DT_BLK
comma
(braket
id|EXT2_FT_FIFO
)braket
op_assign
id|DT_FIFO
comma
(braket
id|EXT2_FT_SOCK
)braket
op_assign
id|DT_SOCK
comma
(braket
id|EXT2_FT_SYMLINK
)braket
op_assign
id|DT_LNK
comma
)brace
suffix:semicolon
DECL|macro|S_SHIFT
mdefine_line|#define S_SHIFT 12
DECL|variable|ext2_type_by_mode
r_static
r_int
r_char
id|ext2_type_by_mode
(braket
id|S_IFMT
op_rshift
id|S_SHIFT
)braket
op_assign
(brace
(braket
id|S_IFREG
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_REG_FILE
comma
(braket
id|S_IFDIR
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_DIR
comma
(braket
id|S_IFCHR
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_CHRDEV
comma
(braket
id|S_IFBLK
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_BLKDEV
comma
(braket
id|S_IFIFO
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_FIFO
comma
(braket
id|S_IFSOCK
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_SOCK
comma
(braket
id|S_IFLNK
op_rshift
id|S_SHIFT
)braket
op_assign
id|EXT2_FT_SYMLINK
comma
)brace
suffix:semicolon
DECL|function|ext2_set_de_type
r_static
r_inline
r_void
id|ext2_set_de_type
c_func
(paren
id|ext2_dirent
op_star
id|de
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|mode_t
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
id|EXT2_HAS_INCOMPAT_FEATURE
c_func
(paren
id|inode-&gt;i_sb
comma
id|EXT2_FEATURE_INCOMPAT_FILETYPE
)paren
)paren
id|de-&gt;file_type
op_assign
id|ext2_type_by_mode
(braket
(paren
id|mode
op_amp
id|S_IFMT
)paren
op_rshift
id|S_SHIFT
)braket
suffix:semicolon
r_else
id|de-&gt;file_type
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ext2_readdir
id|ext2_readdir
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
id|loff_t
id|pos
op_assign
id|filp-&gt;f_pos
suffix:semicolon
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
r_int
id|offset
op_assign
id|pos
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_int
r_int
id|n
op_assign
id|pos
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|chunk_mask
op_assign
op_complement
(paren
id|ext2_chunk_size
c_func
(paren
id|inode
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_int
r_char
op_star
id|types
op_assign
l_int|NULL
suffix:semicolon
r_int
id|need_revalidate
op_assign
(paren
id|filp-&gt;f_version
op_ne
id|inode-&gt;i_version
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|inode-&gt;i_size
op_minus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|EXT2_HAS_INCOMPAT_FEATURE
c_func
(paren
id|sb
comma
id|EXT2_FEATURE_INCOMPAT_FILETYPE
)paren
)paren
id|types
op_assign
id|ext2_filetype_table
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OL
id|npages
suffix:semicolon
id|n
op_increment
comma
id|offset
op_assign
l_int|0
)paren
(brace
r_char
op_star
id|kaddr
comma
op_star
id|limit
suffix:semicolon
id|ext2_dirent
op_star
id|de
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|ext2_get_page
c_func
(paren
id|inode
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_revalidate
)paren
(brace
id|offset
op_assign
id|ext2_validate_entry
c_func
(paren
id|kaddr
comma
id|offset
comma
id|chunk_mask
)paren
suffix:semicolon
id|need_revalidate
op_assign
l_int|0
suffix:semicolon
)brace
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|kaddr
op_plus
id|offset
)paren
suffix:semicolon
id|limit
op_assign
id|kaddr
op_plus
id|ext2_last_byte
c_func
(paren
id|inode
comma
id|n
)paren
op_minus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
r_char
op_star
)paren
id|de
op_le
id|limit
suffix:semicolon
id|de
op_assign
id|ext2_next_entry
c_func
(paren
id|de
)paren
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;rec_len
op_eq
l_int|0
)paren
(brace
id|ext2_error
c_func
(paren
id|sb
comma
id|__FUNCTION__
comma
l_string|&quot;zero-length directory entry&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
r_int
id|over
suffix:semicolon
r_int
r_char
id|d_type
op_assign
id|DT_UNKNOWN
suffix:semicolon
r_if
c_cond
(paren
id|types
op_logical_and
id|de-&gt;file_type
OL
id|EXT2_FT_MAX
)paren
id|d_type
op_assign
id|types
(braket
id|de-&gt;file_type
)braket
suffix:semicolon
id|offset
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
id|kaddr
suffix:semicolon
id|over
op_assign
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;name
comma
id|de-&gt;name_len
comma
(paren
id|n
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_or
id|offset
comma
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
)paren
comma
id|d_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|over
)paren
(brace
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|done
suffix:colon
id|filp-&gt;f_pos
op_assign
(paren
id|n
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_or
id|offset
suffix:semicolon
id|filp-&gt;f_version
op_assign
id|inode-&gt;i_version
suffix:semicolon
id|UPDATE_ATIME
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;ext2_find_entry()&n; *&n; * finds an entry in the specified directory with the wanted name. It&n; * returns the page in which the entry was found, and the entry itself&n; * (as a parameter - res_dir). Page is returned mapped and unlocked.&n; * Entry is guaranteed to be valid.&n; */
DECL|function|ext2_find_entry
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_find_entry
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
id|page
op_star
op_star
id|res_page
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_int
id|reclen
op_assign
id|EXT2_DIR_REC_LEN
c_func
(paren
id|namelen
)paren
suffix:semicolon
r_int
r_int
id|start
comma
id|n
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|dir
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|ext2_inode_info
op_star
id|ei
op_assign
id|EXT2_I
c_func
(paren
id|dir
)paren
suffix:semicolon
id|ext2_dirent
op_star
id|de
suffix:semicolon
r_if
c_cond
(paren
id|npages
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* OFFSET_CACHE */
op_star
id|res_page
op_assign
l_int|NULL
suffix:semicolon
id|start
op_assign
id|ei-&gt;i_dir_start_lookup
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|npages
)paren
id|start
op_assign
l_int|0
suffix:semicolon
id|n
op_assign
id|start
suffix:semicolon
r_do
(brace
r_char
op_star
id|kaddr
suffix:semicolon
id|page
op_assign
id|ext2_get_page
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|ext2_last_byte
c_func
(paren
id|dir
comma
id|n
)paren
op_minus
id|reclen
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;rec_len
op_eq
l_int|0
)paren
(brace
id|ext2_error
c_func
(paren
id|dir-&gt;i_sb
comma
id|__FUNCTION__
comma
l_string|&quot;zero-length directory entry&quot;
)paren
suffix:semicolon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ext2_match
(paren
id|namelen
comma
id|name
comma
id|de
)paren
)paren
r_goto
id|found
suffix:semicolon
id|de
op_assign
id|ext2_next_entry
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|n
op_ge
id|npages
)paren
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_ne
id|start
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|NULL
suffix:semicolon
id|found
suffix:colon
op_star
id|res_page
op_assign
id|page
suffix:semicolon
id|ei-&gt;i_dir_start_lookup
op_assign
id|n
suffix:semicolon
r_return
id|de
suffix:semicolon
)brace
DECL|function|ext2_dotdot
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_dotdot
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|page
op_star
op_star
id|p
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|ext2_get_page
c_func
(paren
id|dir
comma
l_int|0
)paren
suffix:semicolon
id|ext2_dirent
op_star
id|de
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
(brace
id|de
op_assign
id|ext2_next_entry
c_func
(paren
(paren
id|ext2_dirent
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|page
suffix:semicolon
)brace
r_return
id|de
suffix:semicolon
)brace
DECL|function|ext2_inode_by_name
id|ino_t
id|ext2_inode_by_name
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
)paren
(brace
id|ino_t
id|res
op_assign
l_int|0
suffix:semicolon
r_struct
id|ext2_dir_entry_2
op_star
id|de
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|de
op_assign
id|ext2_find_entry
(paren
id|dir
comma
id|dentry
comma
op_amp
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
id|res
op_assign
id|le32_to_cpu
c_func
(paren
id|de-&gt;inode
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
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Releases the page */
DECL|function|ext2_set_link
r_void
id|ext2_set_link
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|ext2_dir_entry_2
op_star
id|de
comma
r_struct
id|page
op_star
id|page
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|from
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|to
op_assign
id|from
op_plus
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ext2_set_de_type
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|EXT2_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_flags
op_and_assign
op_complement
id|EXT2_BTREE_FL
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Parent is locked.&n; */
DECL|function|ext2_add_link
r_int
id|ext2_add_link
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|dentry-&gt;d_parent-&gt;d_inode
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|dentry-&gt;d_name.name
suffix:semicolon
r_int
id|namelen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
r_int
id|chunk_size
op_assign
id|ext2_chunk_size
c_func
(paren
id|dir
)paren
suffix:semicolon
r_int
id|reclen
op_assign
id|EXT2_DIR_REC_LEN
c_func
(paren
id|namelen
)paren
suffix:semicolon
r_int
r_int
id|rec_len
comma
id|name_len
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
id|ext2_dirent
op_star
id|de
suffix:semicolon
r_int
r_int
id|npages
op_assign
id|dir_pages
c_func
(paren
id|dir
)paren
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_int
id|from
comma
id|to
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * We take care of directory expansion in the same loop.&n;&t; * This code plays outside i_size, so it locks the page&n;&t; * to protect that region.&n;&t; */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
op_le
id|npages
suffix:semicolon
id|n
op_increment
)paren
(brace
r_char
op_star
id|dir_end
suffix:semicolon
id|page
op_assign
id|ext2_get_page
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_goto
id|out
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|dir_end
op_assign
id|kaddr
op_plus
id|ext2_last_byte
c_func
(paren
id|dir
comma
id|n
)paren
suffix:semicolon
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|PAGE_CACHE_SIZE
op_minus
id|reclen
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|de
op_eq
id|dir_end
)paren
(brace
multiline_comment|/* We hit i_size */
id|name_len
op_assign
l_int|0
suffix:semicolon
id|rec_len
op_assign
id|chunk_size
suffix:semicolon
id|de-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|chunk_size
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
l_int|0
suffix:semicolon
r_goto
id|got_it
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;rec_len
op_eq
l_int|0
)paren
(brace
id|ext2_error
c_func
(paren
id|dir-&gt;i_sb
comma
id|__FUNCTION__
comma
l_string|&quot;zero-length directory entry&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|ext2_match
(paren
id|namelen
comma
id|name
comma
id|de
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|name_len
op_assign
id|EXT2_DIR_REC_LEN
c_func
(paren
id|de-&gt;name_len
)paren
suffix:semicolon
id|rec_len
op_assign
id|le16_to_cpu
c_func
(paren
id|de-&gt;rec_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;inode
op_logical_and
id|rec_len
op_ge
id|reclen
)paren
r_goto
id|got_it
suffix:semicolon
r_if
c_cond
(paren
id|rec_len
op_ge
id|name_len
op_plus
id|reclen
)paren
r_goto
id|got_it
suffix:semicolon
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|rec_len
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|got_it
suffix:colon
id|from
op_assign
(paren
r_char
op_star
)paren
id|de
op_minus
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|to
op_assign
id|from
op_plus
id|rec_len
suffix:semicolon
id|err
op_assign
id|page-&gt;mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_unlock
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;inode
)paren
(brace
id|ext2_dirent
op_star
id|de1
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|de
op_plus
id|name_len
)paren
suffix:semicolon
id|de1-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|rec_len
op_minus
id|name_len
)paren
suffix:semicolon
id|de-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|name_len
)paren
suffix:semicolon
id|de
op_assign
id|de1
suffix:semicolon
)brace
id|de-&gt;name_len
op_assign
id|namelen
suffix:semicolon
id|memcpy
(paren
id|de-&gt;name
comma
id|name
comma
id|namelen
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ext2_set_de_type
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
id|err
op_assign
id|ext2_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|dir-&gt;i_mtime
op_assign
id|dir-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|EXT2_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_flags
op_and_assign
op_complement
id|EXT2_BTREE_FL
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|dir
)paren
suffix:semicolon
multiline_comment|/* OFFSET_CACHE */
id|out_put
suffix:colon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_unlock
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out_put
suffix:semicolon
)brace
multiline_comment|/*&n; * ext2_delete_entry deletes a directory entry by merging it with the&n; * previous entry. Page is up-to-date. Releases the page.&n; */
DECL|function|ext2_delete_entry
r_int
id|ext2_delete_entry
(paren
r_struct
id|ext2_dir_entry_2
op_star
id|dir
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|mapping-&gt;host
suffix:semicolon
r_char
op_star
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|from
op_assign
(paren
(paren
r_char
op_star
)paren
id|dir
op_minus
id|kaddr
)paren
op_amp
op_complement
(paren
id|ext2_chunk_size
c_func
(paren
id|inode
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_int
id|to
op_assign
(paren
(paren
r_char
op_star
)paren
id|dir
op_minus
id|kaddr
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|dir-&gt;rec_len
)paren
suffix:semicolon
id|ext2_dirent
op_star
id|pde
op_assign
l_int|NULL
suffix:semicolon
id|ext2_dirent
op_star
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
(paren
id|kaddr
op_plus
id|from
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
OL
(paren
r_char
op_star
)paren
id|dir
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;rec_len
op_eq
l_int|0
)paren
(brace
id|ext2_error
c_func
(paren
id|inode-&gt;i_sb
comma
id|__FUNCTION__
comma
l_string|&quot;zero-length directory entry&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|pde
op_assign
id|de
suffix:semicolon
id|de
op_assign
id|ext2_next_entry
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pde
)paren
id|from
op_assign
(paren
r_char
op_star
)paren
id|pde
op_minus
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pde
)paren
id|pde-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|to
op_minus
id|from
)paren
suffix:semicolon
id|dir-&gt;inode
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|ext2_commit_chunk
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|EXT2_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_flags
op_and_assign
op_complement
id|EXT2_BTREE_FL
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|out
suffix:colon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the first fragment of directory.&n; */
DECL|function|ext2_make_empty
r_int
id|ext2_make_empty
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|inode
op_star
id|parent
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
l_int|0
)paren
suffix:semicolon
r_int
id|chunk_size
op_assign
id|ext2_chunk_size
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|ext2_dir_entry_2
op_star
id|de
suffix:semicolon
r_int
id|err
suffix:semicolon
r_void
op_star
id|kaddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
id|mapping-&gt;a_ops
op_member_access_from_pointer
id|prepare_write
c_func
(paren
l_int|NULL
comma
id|page
comma
l_int|0
comma
id|chunk_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ext2_dir_entry_2
op_star
)paren
id|kaddr
suffix:semicolon
id|de-&gt;name_len
op_assign
l_int|1
suffix:semicolon
id|de-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|memcpy
(paren
id|de-&gt;name
comma
l_string|&quot;.&bslash;0&bslash;0&quot;
comma
l_int|4
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|ext2_set_de_type
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
id|de
op_assign
(paren
r_struct
id|ext2_dir_entry_2
op_star
)paren
(paren
id|kaddr
op_plus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|de-&gt;name_len
op_assign
l_int|2
suffix:semicolon
id|de-&gt;rec_len
op_assign
id|cpu_to_le16
c_func
(paren
id|chunk_size
op_minus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
)paren
suffix:semicolon
id|de-&gt;inode
op_assign
id|cpu_to_le32
c_func
(paren
id|parent-&gt;i_ino
)paren
suffix:semicolon
id|memcpy
(paren
id|de-&gt;name
comma
l_string|&quot;..&bslash;0&quot;
comma
l_int|4
)paren
suffix:semicolon
id|ext2_set_de_type
(paren
id|de
comma
id|inode
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|err
op_assign
id|ext2_commit_chunk
c_func
(paren
id|page
comma
l_int|0
comma
id|chunk_size
)paren
suffix:semicolon
id|fail
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * routine to check that the specified directory is empty (for rmdir)&n; */
DECL|function|ext2_empty_dir
r_int
id|ext2_empty_dir
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|i
comma
id|npages
op_assign
id|dir_pages
c_func
(paren
id|inode
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
id|npages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
id|kaddr
suffix:semicolon
id|ext2_dirent
op_star
id|de
suffix:semicolon
id|page
op_assign
id|ext2_get_page
c_func
(paren
id|inode
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|de
op_assign
(paren
id|ext2_dirent
op_star
)paren
id|kaddr
suffix:semicolon
id|kaddr
op_add_assign
id|ext2_last_byte
c_func
(paren
id|inode
comma
id|i
)paren
op_minus
id|EXT2_DIR_REC_LEN
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_char
op_star
)paren
id|de
op_le
id|kaddr
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;rec_len
op_eq
l_int|0
)paren
(brace
id|ext2_error
c_func
(paren
id|inode-&gt;i_sb
comma
id|__FUNCTION__
comma
l_string|&quot;zero-length directory entry&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kaddr=%p, de=%p&bslash;n&quot;
comma
id|kaddr
comma
id|de
)paren
suffix:semicolon
r_goto
id|not_empty
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de-&gt;inode
op_ne
l_int|0
)paren
(brace
multiline_comment|/* check for . and .. */
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_goto
id|not_empty
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;name_len
OG
l_int|2
)paren
r_goto
id|not_empty
suffix:semicolon
r_if
c_cond
(paren
id|de-&gt;name_len
OL
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|de-&gt;inode
op_ne
id|cpu_to_le32
c_func
(paren
id|inode-&gt;i_ino
)paren
)paren
r_goto
id|not_empty
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|1
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_goto
id|not_empty
suffix:semicolon
)brace
id|de
op_assign
id|ext2_next_entry
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|not_empty
suffix:colon
id|ext2_put_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ext2_dir_operations
r_struct
id|file_operations
id|ext2_dir_operations
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
id|ext2_readdir
comma
dot
id|ioctl
op_assign
id|ext2_ioctl
comma
dot
id|fsync
op_assign
id|ext2_sync_file
comma
)brace
suffix:semicolon
eof
