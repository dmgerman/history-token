multiline_comment|/*&n; * aops.c - NTFS kernel address space operations and page cache handling.&n; * &t;    Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/**&n; * ntfs_file_get_block - read/create inode @ino block @blk into buffer head @bh&n; * @ino:&t;inode to read/create block from/onto&n; * @blk:&t;block number to read/create&n; * @bh:&t;&t;buffer in which to return the read/created block&n; * @create:&t;if not zero, create the block if it doesn&squot;t exist already&n; * &n; * ntfs_file_get_block() remaps the block number @blk of the inode @ino from&n; * file offset into disk block position and returns the result in the buffer&n; * head @bh. If the block doesn&squot;t exist and create is not zero,&n; * ntfs_file_get_block() creates the block before returning it. @blk is the&n; * file offset divided by the file system block size, as defined by the field&n; * s_blocksize in the super block reachable by @ino-&gt;i_sb.&n; *&n; * If the block doesn&squot;t exist, create is true, and the inode is marked&n; * for synchronous I/O, then we will wait for creation to complete before&n; * returning the created block (which will be zeroed). Otherwise we only&n; * schedule creation and return. - FIXME: Need to have a think whether this is&n; * really necessary. What would happen if we didn&squot;t actually write the block to&n; * disk at this stage? We would just save writing a block full of zeroes to the&n; * device. - We can always write it synchronously when the user actually writes&n; * some data into it. - But this might result in random data being returned&n; * should the computer crash. - Hmmm. - This requires more thought.&n; *&n; * Obviously the block is only created if the file system super block flag&n; * MS_RDONLY is not set and only if NTFS write support is compiled in.&n; */
DECL|function|ntfs_file_get_block
r_int
id|ntfs_file_get_block
c_func
(paren
r_struct
id|inode
op_star
id|vi
comma
r_const
id|sector_t
id|blk
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_const
r_int
id|create
)paren
(brace
id|ntfs_inode
op_star
id|ni
op_assign
id|NTFS_I
c_func
(paren
id|vi
)paren
suffix:semicolon
id|ntfs_volume
op_star
id|vol
op_assign
id|ni-&gt;vol
suffix:semicolon
id|VCN
id|vcn
suffix:semicolon
id|LCN
id|lcn
suffix:semicolon
r_int
id|ofs
suffix:semicolon
id|BOOL
id|is_retry
op_assign
id|FALSE
suffix:semicolon
singleline_comment|//ntfs_debug(&quot;Entering for blk 0x%lx.&quot;, blk);
singleline_comment|//printk(KERN_DEBUG &quot;NTFS: &quot; __FUNCTION__ &quot;(): Entering for blk &quot;
singleline_comment|//&t;&t;&quot;0x%lx.&bslash;n&quot;, blk);
id|bh-&gt;b_dev
op_assign
id|vi-&gt;i_dev
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
op_minus
l_int|1
suffix:semicolon
id|bh-&gt;b_state
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
multiline_comment|/* Convert @blk into a virtual cluster number (vcn) and offset. */
id|vcn
op_assign
(paren
id|VCN
)paren
id|blk
op_lshift
id|vol-&gt;sb-&gt;s_blocksize_bits
op_rshift
id|vol-&gt;cluster_size_bits
suffix:semicolon
id|ofs
op_assign
(paren
(paren
id|VCN
)paren
id|blk
op_lshift
id|vol-&gt;sb-&gt;s_blocksize_bits
)paren
op_amp
id|vol-&gt;cluster_size_mask
suffix:semicolon
multiline_comment|/* Check for initialized size overflow. */
r_if
c_cond
(paren
(paren
id|vcn
op_lshift
id|vol-&gt;cluster_size_bits
)paren
op_plus
id|ofs
op_ge
id|ni-&gt;initialized_size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Further, we need to be checking i_size and be just doing the&n;&t; * following if it is zero or we are out of bounds:&n;&t; * &t;bh-&gt;b_blocknr = -1UL;&n;&t; * &t;raturn 0;&n;&t; * Also, we need to deal with attr-&gt;initialized_size.&n;&t; * Also, we need to deal with the case where the last block is&n;&t; * requested but it is not initialized fully, i.e. it is a partial&n;&t; * block. We then need to read it synchronously and fill the remainder&n;&t; * with zero. Can&squot;t do it other way round as reading from the block&n;&t; * device would result in our pre-zeroed data to be overwritten as the&n;&t; * whole block is loaded from disk.&n;&t; * Also, need to lock run_list in inode so we don&squot;t have someone&n;&t; * reading it at the same time as someone else writing it.&n;&t; */
id|retry_remap
suffix:colon
multiline_comment|/* Convert the vcn to the corresponding logical cluster number (lcn). */
id|read_lock
c_func
(paren
op_amp
id|ni-&gt;run_list.lock
)paren
suffix:semicolon
id|lcn
op_assign
id|vcn_to_lcn
c_func
(paren
id|ni-&gt;run_list.rl
comma
id|vcn
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|ni-&gt;run_list.lock
)paren
suffix:semicolon
multiline_comment|/* Successful remap. */
r_if
c_cond
(paren
id|lcn
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Setup the buffer head to describe the correct block. */
macro_line|#if 0
multiline_comment|/* Already the case when we are called. */
id|bh-&gt;b_dev
op_assign
id|vfs_ino-&gt;i_dev
suffix:semicolon
macro_line|#endif
id|bh-&gt;b_blocknr
op_assign
(paren
(paren
id|lcn
op_lshift
id|vol-&gt;cluster_size_bits
)paren
op_plus
id|ofs
)paren
op_rshift
id|vol-&gt;sb-&gt;s_blocksize_bits
suffix:semicolon
id|bh-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* It is a hole. */
r_if
c_cond
(paren
id|lcn
op_eq
id|LCN_HOLE
)paren
(brace
r_if
c_cond
(paren
id|create
)paren
multiline_comment|/* FIXME: We should instantiate the hole. */
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Hole. Set the block number to -1 (it is ignored but&n;&t;&t; * just in case and might help with debugging).&n;&t;&t; */
id|bh-&gt;b_blocknr
op_assign
op_minus
l_int|1UL
suffix:semicolon
id|bh-&gt;b_state
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* If on first try and the run list was not mapped, map it and retry. */
r_if
c_cond
(paren
op_logical_neg
id|is_retry
op_logical_and
id|lcn
op_eq
id|LCN_RL_NOT_MAPPED
)paren
(brace
r_int
id|err
op_assign
id|map_run_list
c_func
(paren
id|ni
comma
id|vcn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|is_retry
op_assign
id|TRUE
suffix:semicolon
r_goto
id|retry_remap
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|create
)paren
multiline_comment|/* FIXME: We might need to extend the attribute. */
r_return
op_minus
id|EROFS
suffix:semicolon
multiline_comment|/* Error. */
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_file_readpage - fill a @page of a @file with data from the device&n; * @file:&t;open file to which the page @page belongs or NULL&n; * @page:&t;page cache page to fill with data&n; *&n; * For non-resident attributes, ntfs_file_readpage() fills the @page of the open&n; * file @file by calling the generic block_read_full_page() function provided by&n; * the kernel which in turn invokes our ntfs_file_get_block() callback in order&n; * to create and read in the buffers associated with the page asynchronously.&n; *&n; * For resident attributes, OTOH, ntfs_file_readpage() fills @page by copying&n; * the data from the mft record (which at this stage is most likely in memory)&n; * and fills the remainder with zeroes. Thus, in this case I/O is synchronous,&n; * as even if the mft record is not cached at this point in time, we need to&n; * wait for it to be read in before we can do the copy.&n; *&n; * Return zero on success or -errno on error.&n; */
DECL|function|ntfs_file_readpage
r_static
r_int
id|ntfs_file_readpage
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
id|s64
id|attr_pos
suffix:semicolon
r_struct
id|inode
op_star
id|vi
suffix:semicolon
id|ntfs_inode
op_star
id|ni
suffix:semicolon
r_char
op_star
id|page_addr
suffix:semicolon
id|u32
id|attr_len
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|attr_search_context
op_star
id|ctx
suffix:semicolon
id|MFT_RECORD
op_star
id|mrec
suffix:semicolon
singleline_comment|//ntfs_debug(&quot;Entering for index 0x%lx.&quot;, page-&gt;index);
multiline_comment|/* The page must be locked. */
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the VFS and ntfs inodes associated with the page. This could&n;&t; * be achieved by looking at f-&gt;f_dentry-&gt;d_inode, too, unless the&n;&t; * dentry is negative, but could it really be negative considering we&n;&t; * are reading from the opened file? - NOTE: We can&squot;t get it from file,&n;&t; * because we can use ntfs_file_readpage on inodes not representing&n;&t; * open files!!! So basically we never ever touch file or at least we&n;&t; * must check it is not NULL before doing so.&n;&t; */
id|vi
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
id|ni
op_assign
id|NTFS_I
c_func
(paren
id|vi
)paren
suffix:semicolon
multiline_comment|/* Is the unnamed $DATA attribute resident? */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|NI_NonResident
comma
op_amp
id|ni-&gt;state
)paren
)paren
(brace
multiline_comment|/* Attribute is not resident. */
multiline_comment|/* If the file is encrypted, we deny access, just like NT4. */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|NI_Encrypted
comma
op_amp
id|ni-&gt;state
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_goto
id|unl_err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|NI_Compressed
comma
op_amp
id|ni-&gt;state
)paren
)paren
multiline_comment|/* Normal data stream, use generic functionality. */
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|ntfs_file_get_block
)paren
suffix:semicolon
multiline_comment|/* Compressed data stream. Handled in compress.c. */
r_return
id|ntfs_file_read_compressed_block
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/* Attribute is resident, implying it is not compressed or encrypted. */
multiline_comment|/*&n;&t; * Make sure the inode doesn&squot;t disappear under us. - Shouldn&squot;t be&n;&t; * needed as the page is locked.&n;&t; */
singleline_comment|// atomic_inc(&amp;vfs_ino-&gt;i_count);
multiline_comment|/* Map, pin and lock the mft record for reading. */
id|mrec
op_assign
id|map_mft_record
c_func
(paren
id|READ
comma
id|ni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|mrec
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|mrec
)paren
suffix:semicolon
r_goto
id|dec_unl_err_out
suffix:semicolon
)brace
id|err
op_assign
id|get_attr_search_ctx
c_func
(paren
op_amp
id|ctx
comma
id|ni
comma
id|mrec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|unm_dec_unl_err_out
suffix:semicolon
multiline_comment|/* Find the data attribute in the mft record. */
r_if
c_cond
(paren
op_logical_neg
id|lookup_attr
c_func
(paren
id|AT_DATA
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|ctx
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|put_unm_dec_unl_err_out
suffix:semicolon
)brace
multiline_comment|/* Starting position of the page within the attribute value. */
id|attr_pos
op_assign
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* The total length of the attribute value. */
id|attr_len
op_assign
id|le32_to_cpu
c_func
(paren
id|ctx-&gt;attr
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_length
)paren
)paren
suffix:semicolon
multiline_comment|/* Map the page so we can access it. */
id|page_addr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * TODO: Find out whether we really need to zero the page. If it is&n;&t; * initialized to zero already we could skip this.&n;&t; */
multiline_comment|/* &n;&t; * If we are asking for any in bounds data, copy it over, zeroing the&n;&t; * remainder of the page if necessary. Otherwise just zero the page.&n;&t; */
r_if
c_cond
(paren
id|attr_pos
OL
id|attr_len
)paren
(brace
id|u32
id|bytes
op_assign
id|attr_len
op_minus
id|attr_pos
suffix:semicolon
r_if
c_cond
(paren
id|bytes
OG
id|PAGE_CACHE_SIZE
)paren
id|bytes
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bytes
OL
id|PAGE_CACHE_SIZE
)paren
id|memset
c_func
(paren
id|page_addr
op_plus
id|bytes
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
op_minus
id|bytes
)paren
suffix:semicolon
multiline_comment|/* Copy the data to the page. */
id|memcpy
c_func
(paren
id|page_addr
comma
id|attr_pos
op_plus
(paren
r_char
op_star
)paren
id|ctx-&gt;attr
op_plus
id|le16_to_cpu
c_func
(paren
id|ctx-&gt;attr
op_member_access_from_pointer
id|_ARA
c_func
(paren
id|value_offset
)paren
)paren
comma
id|bytes
)paren
suffix:semicolon
)brace
r_else
id|memset
c_func
(paren
id|page_addr
comma
l_int|0
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
multiline_comment|/* We are done. */
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|put_unm_dec_unl_err_out
suffix:colon
id|put_attr_search_ctx
c_func
(paren
id|ctx
)paren
suffix:semicolon
id|unm_dec_unl_err_out
suffix:colon
multiline_comment|/* Unlock, unpin and release the mft record. */
id|unmap_mft_record
c_func
(paren
id|READ
comma
id|ni
)paren
suffix:semicolon
id|dec_unl_err_out
suffix:colon
multiline_comment|/* Release the inode. - Shouldn&squot;t be needed as the page is locked. */
singleline_comment|// atomic_dec(&amp;vfs_ino-&gt;i_count);
id|unl_err_out
suffix:colon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Specialized get block for reading the mft bitmap. Adapted from&n; * ntfs_file_get_block.&n; */
DECL|function|ntfs_mftbmp_get_block
r_static
r_int
id|ntfs_mftbmp_get_block
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_const
id|sector_t
id|blk
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|VCN
id|vcn
op_assign
(paren
id|VCN
)paren
id|blk
op_lshift
id|vol-&gt;sb-&gt;s_blocksize_bits
op_rshift
id|vol-&gt;cluster_size_bits
suffix:semicolon
r_int
id|ofs
op_assign
(paren
id|blk
op_lshift
id|vol-&gt;sb-&gt;s_blocksize_bits
)paren
op_amp
id|vol-&gt;cluster_size_mask
suffix:semicolon
id|LCN
id|lcn
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Entering for blk = 0x%lx, vcn = 0x%Lx, ofs = 0x%x.&quot;
comma
id|blk
comma
(paren
r_int
r_int
)paren
id|vcn
comma
id|ofs
)paren
suffix:semicolon
id|bh-&gt;b_dev
op_assign
id|vol-&gt;mft_ino-&gt;i_dev
suffix:semicolon
id|bh-&gt;b_state
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Check for initialized size overflow. */
r_if
c_cond
(paren
(paren
id|vcn
op_lshift
id|vol-&gt;cluster_size_bits
)paren
op_plus
id|ofs
op_ge
id|vol-&gt;mftbmp_initialized_size
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Done.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|vol-&gt;mftbmp_rl.lock
)paren
suffix:semicolon
id|lcn
op_assign
id|vcn_to_lcn
c_func
(paren
id|vol-&gt;mftbmp_rl.rl
comma
id|vcn
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|vol-&gt;mftbmp_rl.lock
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;lcn = 0x%Lx.&quot;
comma
(paren
r_int
r_int
)paren
id|lcn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lcn
OL
l_int|0LL
)paren
(brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Returning -EIO, lcn = 0x%Lx.&quot;
comma
(paren
r_int
r_int
)paren
id|lcn
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Setup the buffer head to describe the correct block. */
id|bh-&gt;b_blocknr
op_assign
(paren
(paren
id|lcn
op_lshift
id|vol-&gt;cluster_size_bits
)paren
op_plus
id|ofs
)paren
op_rshift
id|vol-&gt;sb-&gt;s_blocksize_bits
suffix:semicolon
id|bh-&gt;b_state
op_or_assign
(paren
l_int|1UL
op_lshift
id|BH_Mapped
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done, bh-&gt;b_blocknr = 0x%lx.&quot;
comma
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MAX_BUF_PER_PAGE
mdefine_line|#define MAX_BUF_PER_PAGE (PAGE_CACHE_SIZE / 512)
multiline_comment|/*&n; * Specialized readpage for accessing mft bitmap. Adapted from&n; * block_read_full_page().&n; */
DECL|function|ntfs_mftbmp_readpage
r_static
r_int
id|ntfs_mftbmp_readpage
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|sector_t
id|iblock
comma
id|lblock
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|head
comma
op_star
id|arr
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
r_int
r_int
id|blocksize
comma
id|blocks
suffix:semicolon
r_int
id|nr
comma
id|i
suffix:semicolon
r_int
r_char
id|blocksize_bits
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Entering for index 0x%lx.&quot;
comma
id|page-&gt;index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
id|blocksize
op_assign
id|vol-&gt;sb-&gt;s_blocksize
suffix:semicolon
id|blocksize_bits
op_assign
id|vol-&gt;sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;buffers
)paren
id|create_empty_buffers
c_func
(paren
id|page
comma
id|blocksize
)paren
suffix:semicolon
id|head
op_assign
id|page-&gt;buffers
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|head
)paren
(brace
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Creation of empty buffers failed, cannot &quot;
l_string|&quot;read page.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|blocks
op_assign
id|PAGE_CACHE_SIZE
op_rshift
id|blocksize_bits
suffix:semicolon
id|iblock
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|blocksize_bits
)paren
suffix:semicolon
id|lblock
op_assign
(paren
(paren
(paren
id|vol
op_member_access_from_pointer
id|_VMM
c_func
(paren
id|nr_mft_records
)paren
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
op_plus
id|blocksize
op_minus
l_int|1
)paren
op_rshift
id|blocksize_bits
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;blocks = 0x%x, iblock = 0x%lx, lblock = 0x%lx.&quot;
comma
id|blocks
comma
id|iblock
comma
id|lblock
)paren
suffix:semicolon
id|bh
op_assign
id|head
suffix:semicolon
id|nr
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;In do loop, i = 0x%x, iblock = 0x%lx.&quot;
comma
id|i
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Buffer is already uptodate.&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
r_if
c_cond
(paren
id|iblock
OL
id|lblock
)paren
(brace
r_if
c_cond
(paren
id|ntfs_mftbmp_get_block
c_func
(paren
id|vol
comma
id|iblock
comma
id|bh
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Buffer is not mapped, setting &quot;
l_string|&quot;uptodate.&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|i
op_star
id|blocksize
comma
l_int|0
comma
id|blocksize
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BH_Uptodate
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * ntfs_mftbmp_get_block() might have updated the&n;&t;&t;&t; * buffer synchronously.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Buffer is now uptodate.&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|arr
(braket
id|nr
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_increment
comma
id|iblock
op_increment
comma
(paren
id|bh
op_assign
id|bh-&gt;b_this_page
)paren
op_ne
id|head
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;After do loop, i = 0x%x, iblock = 0x%lx, nr = 0x%x.&quot;
comma
id|i
comma
id|iblock
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr
)paren
(brace
multiline_comment|/* All buffers are uptodate - set the page uptodate as well. */
id|ntfs_debug
c_func
(paren
l_string|&quot;All buffers are uptodate, returning 0.&quot;
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Stage two: lock the buffers */
id|ntfs_debug
c_func
(paren
l_string|&quot;Locking buffers.&quot;
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|arr
(braket
id|i
)braket
suffix:semicolon
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_buffer_async_io
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* Stage 3: start the IO */
id|ntfs_debug
c_func
(paren
l_string|&quot;Starting IO on buffers.&quot;
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
id|submit_bh
c_func
(paren
id|READ
comma
id|arr
(braket
id|i
)braket
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * end_buffer_read_index_async - async io completion for reading index records&n; * @bh:&t;&t;buffer head on which io is completed&n; * @uptodate:&t;whether @bh is now uptodate or not&n; *&n; * Asynchronous I/O completion handler for reading pages belogning to the&n; * index allocation attribute address space of directory inodes.&n; *&n; * Perform the post read mst fixups when all IO on the page has been completed&n; * and marks the page uptodate or sets the error bit on the page.&n; *&n; * Adapted from fs/buffer.c.&n; *&n; * NOTE: We use this function as async io completion handler for reading pages&n; * belonging to the mft data attribute address space, too as this saves&n; * duplicating an almost identical function. We do this by cheating a little&n; * bit in setting the index_block_size in the mft ntfs_inode to the mft record&n; * size of the volume (vol-&gt;mft_record_size), and index_block_size_bits to&n; * mft_record_size_bits, respectively.&n; */
DECL|function|end_buffer_read_index_async
r_void
id|end_buffer_read_index_async
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
(brace
r_static
id|spinlock_t
id|page_uptodate_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|buffer_head
op_star
id|tmp
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
multiline_comment|/* This is a temporary buffer used for page I/O. */
id|page
op_assign
id|bh-&gt;b_page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Be _very_ careful from here on. Bad things can happen if&n;&t; * two buffer heads end IO at almost the same time and both&n;&t; * decide that the page is now completely done.&n;&t; *&n;&t; * Async buffer_heads are here only as labels for IO, and get&n;&t; * thrown away once the IO for this page is complete.  IO is&n;&t; * deemed complete once all buffers have been visited&n;&t; * (b_count==0) and are now unlocked. We must make sure that&n;&t; * only the _last_ buffer that decrements its count is the one&n;&t; * that unlock the page..&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|page_uptodate_lock
comma
id|flags
)paren
suffix:semicolon
id|mark_buffer_async
c_func
(paren
id|bh
comma
l_int|0
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|tmp
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_ne
id|bh
)paren
(brace
r_if
c_cond
(paren
id|buffer_async
c_func
(paren
id|tmp
)paren
op_logical_and
id|buffer_locked
c_func
(paren
id|tmp
)paren
)paren
r_goto
id|still_busy
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_this_page
suffix:semicolon
)brace
multiline_comment|/* OK, the async IO on this page is complete. */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|page_uptodate_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If none of the buffers had errors then we can set the page uptodate,&n;&t; * but we first have to perform the post read mst fixups.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|PageError
c_func
(paren
id|page
)paren
)paren
(brace
r_char
op_star
id|addr
suffix:semicolon
r_int
r_int
id|i
comma
id|recs
comma
id|nr_err
op_assign
l_int|0
suffix:semicolon
id|u32
id|rec_size
suffix:semicolon
id|ntfs_inode
op_star
id|ni
op_assign
id|NTFS_I
c_func
(paren
id|page-&gt;mapping-&gt;host
)paren
suffix:semicolon
id|addr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_BIO_IRQ
)paren
suffix:semicolon
id|rec_size
op_assign
id|ni
op_member_access_from_pointer
id|_IDM
c_func
(paren
id|index_block_size
)paren
suffix:semicolon
id|recs
op_assign
id|PAGE_CACHE_SIZE
op_div
id|rec_size
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
id|recs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|post_read_mst_fixup
c_func
(paren
(paren
id|NTFS_RECORD
op_star
)paren
(paren
id|addr
op_plus
id|i
op_star
id|rec_size
)paren
comma
id|rec_size
)paren
)paren
r_continue
suffix:semicolon
id|nr_err
op_increment
suffix:semicolon
id|ntfs_error
c_func
(paren
id|ni-&gt;vol-&gt;sb
comma
l_string|&quot;post_read_mst_fixup() failed, &quot;
l_string|&quot;corrupt %s record 0x%Lx. Run chkdsk.&quot;
comma
id|ni-&gt;mft_no
ques
c_cond
l_string|&quot;index&quot;
suffix:colon
l_string|&quot;mft&quot;
comma
(paren
r_int
r_int
)paren
(paren
(paren
id|page-&gt;index
op_lshift
id|PAGE_CACHE_SHIFT
op_rshift
id|ni
op_member_access_from_pointer
id|_IDM
c_func
(paren
id|index_block_size_bits
)paren
)paren
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
id|kunmap_atomic
c_func
(paren
id|addr
comma
id|KM_BIO_IRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nr_err
op_logical_and
id|recs
)paren
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
(brace
id|ntfs_error
c_func
(paren
id|ni-&gt;vol-&gt;sb
comma
l_string|&quot;Setting page error, index &quot;
l_string|&quot;0x%lx.&quot;
comma
id|page-&gt;index
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
id|still_busy
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|page_uptodate_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_dir_readpage - fill a @page of a directory with data from the device&n; * @dir:&t;open directory to which the page @page belongs&n; * @page:&t;page cache page to fill with data&n; *&n; * Fill the page @page of the open directory @dir. We read each buffer&n; * asynchronously and when all buffers are read in our io completion&n; * handler end_buffer_read_index_block_async() automatically applies the mst&n; * fixups to the page before finally marking it uptodate and unlocking it.&n; *&n; * Contains an adapted version of fs/buffer.c::block_read_full_page(), a&n; * generic &quot;read page&quot; function for block devices that have the normal&n; * get_block functionality. This is most of the block device filesystems.&n; * Reads the page asynchronously --- the unlock_buffer() and&n; * mark_buffer_uptodate() functions propagate buffer state into the&n; * page struct once IO has completed.&n; */
DECL|function|ntfs_dir_readpage
r_static
r_int
id|ntfs_dir_readpage
c_func
(paren
r_struct
id|file
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
id|inode
op_star
id|vi
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|head
comma
op_star
id|arr
(braket
id|MAX_BUF_PER_PAGE
)braket
suffix:semicolon
id|sector_t
id|iblock
comma
id|lblock
suffix:semicolon
r_int
r_int
id|blocksize
comma
id|blocks
comma
id|nr_bu
suffix:semicolon
r_int
id|nr
comma
id|i
suffix:semicolon
r_int
r_char
id|blocksize_bits
suffix:semicolon
multiline_comment|/* The page must be locked. */
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the VFS/ntfs inodes, the super block and ntfs volume associated&n;&t; * with the page.&n;&t; */
id|vi
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
id|sb
op_assign
id|vi-&gt;i_sb
suffix:semicolon
multiline_comment|/* We need to create buffers for the page so we can do low level io. */
id|blocksize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|blocksize_bits
op_assign
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;buffers
)paren
id|create_empty_buffers
c_func
(paren
id|page
comma
id|blocksize
)paren
suffix:semicolon
r_else
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Page (index 0x%lx) already has buffers.&quot;
comma
id|page-&gt;index
)paren
suffix:semicolon
id|nr_bu
op_assign
id|blocks
op_assign
id|PAGE_CACHE_SIZE
op_rshift
id|blocksize_bits
suffix:semicolon
id|iblock
op_assign
id|page-&gt;index
op_lshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
id|blocksize_bits
)paren
suffix:semicolon
id|lblock
op_assign
(paren
id|vi-&gt;i_size
op_plus
id|blocksize
op_minus
l_int|1
)paren
op_rshift
id|blocksize_bits
suffix:semicolon
id|bh
op_assign
id|head
op_assign
id|page-&gt;buffers
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|bh
)paren
suffix:semicolon
multiline_comment|/* Loop through all the buffers in the page. */
id|i
op_assign
id|nr
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|nr_bu
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
multiline_comment|/* Is the block within the allowed limits? */
r_if
c_cond
(paren
id|iblock
OL
id|lblock
)paren
(brace
multiline_comment|/* Remap the inode offset to its disk block. */
r_if
c_cond
(paren
id|ntfs_file_get_block
c_func
(paren
id|vi
comma
id|iblock
comma
id|bh
comma
l_int|0
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bh
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Error. Zero this portion of the page and set&n;&t;&t;&t;&t; * the buffer uptodate.&n;&t;&t;&t;&t; */
id|memset
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|i
op_star
id|blocksize
comma
l_int|0
comma
id|blocksize
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BH_Uptodate
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* The buffer might have been updated synchronousle. */
r_if
c_cond
(paren
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
r_continue
suffix:semicolon
)brace
id|arr
(braket
id|nr
op_increment
)braket
op_assign
id|bh
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_increment
comma
id|iblock
op_increment
comma
(paren
id|bh
op_assign
id|bh-&gt;b_this_page
)paren
op_ne
id|head
)paren
suffix:semicolon
multiline_comment|/* Check we have at least one buffer ready for io. */
r_if
c_cond
(paren
id|nr
)paren
(brace
multiline_comment|/* Lock the buffers. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|buffer_head
op_star
id|tbh
op_assign
id|arr
(braket
id|i
)braket
suffix:semicolon
id|lock_buffer
c_func
(paren
id|tbh
)paren
suffix:semicolon
id|tbh-&gt;b_end_io
op_assign
id|end_buffer_read_index_async
suffix:semicolon
id|mark_buffer_async
c_func
(paren
id|tbh
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Finally, start io on the buffers. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
id|i
op_increment
)paren
id|submit_bh
c_func
(paren
id|READ
comma
id|arr
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* We are done. */
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|nr_bu
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;All buffers in the page were already uptodate, &quot;
l_string|&quot;assuming mst fixups were already applied.&quot;
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;No io was scheduled on any of the buffers in the page, &quot;
l_string|&quot;but buffers were not all uptodate to start with. &quot;
l_string|&quot;Setting page error flag and returning io error.&quot;
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Address space operations for accessing normal file data. */
DECL|variable|ntfs_file_aops
r_struct
id|address_space_operations
id|ntfs_file_aops
op_assign
(brace
id|writepage
suffix:colon
l_int|NULL
comma
multiline_comment|/* Write dirty page to disk. */
id|readpage
suffix:colon
id|ntfs_file_readpage
comma
multiline_comment|/* Fill page with data. */
id|sync_page
suffix:colon
id|block_sync_page
comma
multiline_comment|/* Currently, just unplugs the&n;&t;&t;&t;&t;&t;&t;   disk request queue. */
id|prepare_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
id|commit_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
singleline_comment|//truncatepage:&t;NULL,&t;&t;&t;/* . */
)brace
suffix:semicolon
DECL|typedef|readpage_t
r_typedef
r_int
id|readpage_t
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
multiline_comment|/* FIXME: Kludge: Address space operations for accessing mftbmp. */
DECL|variable|ntfs_mftbmp_aops
r_struct
id|address_space_operations
id|ntfs_mftbmp_aops
op_assign
(brace
id|writepage
suffix:colon
l_int|NULL
comma
multiline_comment|/* Write dirty page to disk. */
id|readpage
suffix:colon
(paren
id|readpage_t
op_star
)paren
id|ntfs_mftbmp_readpage
comma
multiline_comment|/* Fill page with&n;&t;&t;&t;&t;&t;&t;&t;      data. */
id|sync_page
suffix:colon
id|block_sync_page
comma
multiline_comment|/* Currently, just unplugs the&n;&t;&t;&t;&t;&t;&t;   disk request queue. */
id|prepare_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
id|commit_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
singleline_comment|//truncatepage:&t;NULL,&t;&t;&t;/* . */
)brace
suffix:semicolon
multiline_comment|/*&n; * Address space operations for accessing normal directory data (i.e. index&n; * allocation attribute). We can&squot;t just use the same operations as for files&n; * because 1) the attribute is different and even more importantly 2) the index&n; * records have to be multi sector transfer deprotected (i.e. fixed-up).&n; */
DECL|variable|ntfs_dir_aops
r_struct
id|address_space_operations
id|ntfs_dir_aops
op_assign
(brace
id|writepage
suffix:colon
l_int|NULL
comma
multiline_comment|/* Write dirty page to disk. */
id|readpage
suffix:colon
id|ntfs_dir_readpage
comma
multiline_comment|/* Fill page with data. */
id|sync_page
suffix:colon
id|block_sync_page
comma
multiline_comment|/* Currently, just unplugs the&n;&t;&t;&t;&t;&t;&t;   disk request queue. */
id|prepare_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
id|commit_write
suffix:colon
l_int|NULL
comma
multiline_comment|/* . */
singleline_comment|//truncatepage:&t;NULL,&t;&t;&t;/* . */
)brace
suffix:semicolon
eof
