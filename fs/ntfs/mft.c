multiline_comment|/**&n; * mft.c - NTFS kernel mft record operations. Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; * Copyright (c) 2002 Richard Russon&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/**&n; * __format_mft_record - initialize an empty mft record&n; * @m:&t;&t;mapped, pinned and locked for writing mft record&n; * @size:&t;size of the mft record&n; * @rec_no:&t;mft record number / inode number&n; *&n; * Private function to initialize an empty mft record. Use one of the two&n; * provided format_mft_record() functions instead.&n; */
DECL|function|__format_mft_record
r_static
r_void
id|__format_mft_record
c_func
(paren
id|MFT_RECORD
op_star
id|m
comma
r_const
r_int
id|size
comma
r_const
r_int
r_int
id|rec_no
)paren
(brace
id|ATTR_RECORD
op_star
id|a
suffix:semicolon
id|memset
c_func
(paren
id|m
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|m-&gt;magic
op_assign
id|magic_FILE
suffix:semicolon
multiline_comment|/* Aligned to 2-byte boundary. */
id|m-&gt;usa_ofs
op_assign
id|cpu_to_le16
c_func
(paren
(paren
r_sizeof
(paren
id|MFT_RECORD
)paren
op_plus
l_int|1
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|m-&gt;usa_count
op_assign
id|cpu_to_le16
c_func
(paren
id|size
op_div
id|NTFS_BLOCK_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set the update sequence number to 1. */
op_star
(paren
id|u16
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|m
op_plus
(paren
(paren
r_sizeof
(paren
id|MFT_RECORD
)paren
op_plus
l_int|1
)paren
op_amp
op_complement
l_int|1
)paren
)paren
op_assign
id|cpu_to_le16
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|m-&gt;lsn
op_assign
id|cpu_to_le64
c_func
(paren
l_int|0LL
)paren
suffix:semicolon
id|m-&gt;sequence_number
op_assign
id|cpu_to_le16
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|m-&gt;link_count
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Aligned to 8-byte boundary. */
id|m-&gt;attrs_offset
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|le16_to_cpu
c_func
(paren
id|m-&gt;usa_ofs
)paren
op_plus
(paren
id|le16_to_cpu
c_func
(paren
id|m-&gt;usa_count
)paren
op_lshift
l_int|1
)paren
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|m-&gt;flags
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Using attrs_offset plus eight bytes (for the termination attribute),&n;&t; * aligned to 8-byte boundary.&n;&t; */
id|m-&gt;bytes_in_use
op_assign
id|cpu_to_le32
c_func
(paren
(paren
id|le16_to_cpu
c_func
(paren
id|m-&gt;attrs_offset
)paren
op_plus
l_int|8
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|m-&gt;bytes_allocated
op_assign
id|cpu_to_le32
c_func
(paren
id|size
)paren
suffix:semicolon
id|m-&gt;base_mft_record
op_assign
id|cpu_to_le64
c_func
(paren
(paren
id|MFT_REF
)paren
l_int|0
)paren
suffix:semicolon
id|m-&gt;next_attr_instance
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|a
op_assign
(paren
id|ATTR_RECORD
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|m
op_plus
id|le16_to_cpu
c_func
(paren
id|m-&gt;attrs_offset
)paren
)paren
suffix:semicolon
id|a-&gt;type
op_assign
id|AT_END
suffix:semicolon
id|a-&gt;length
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * format_mft_record - initialize an empty mft record&n; * @ni:&t;&t;ntfs inode of mft record&n; * @mft_rec:&t;mapped, pinned and locked mft record (optional)&n; *&n; * Initialize an empty mft record. This is used when extending the MFT.&n; *&n; * If @mft_rec is NULL, we call map_mft_record() to obtain the&n; * record and we unmap it again when finished.&n; *&n; * We return 0 on success or -errno on error.&n; */
DECL|function|format_mft_record
r_int
id|format_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
comma
id|MFT_RECORD
op_star
id|mft_rec
)paren
(brace
id|MFT_RECORD
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
id|mft_rec
)paren
id|m
op_assign
id|mft_rec
suffix:semicolon
r_else
(brace
id|m
op_assign
id|map_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|m
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
id|__format_mft_record
c_func
(paren
id|m
comma
id|ni-&gt;vol-&gt;mft_record_size
comma
id|ni-&gt;mft_no
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mft_rec
)paren
(brace
singleline_comment|// FIXME: Need to set the mft record dirty!
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_readpage - external declaration, function is in fs/ntfs/aops.c&n; */
r_extern
r_int
id|ntfs_readpage
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
multiline_comment|/**&n; * ntfs_mft_aops - address space operations for access to $MFT&n; *&n; * Address space operations for access to $MFT. This allows us to simply use&n; * ntfs_map_page() in map_mft_record_page().&n; */
DECL|variable|ntfs_mft_aops
r_struct
id|address_space_operations
id|ntfs_mft_aops
op_assign
(brace
dot
id|readpage
op_assign
id|ntfs_readpage
comma
multiline_comment|/* Fill page with data. */
dot
id|sync_page
op_assign
id|block_sync_page
comma
multiline_comment|/* Currently, just unplugs the&n;&t;&t;&t;&t;&t;&t;   disk request queue. */
)brace
suffix:semicolon
multiline_comment|/**&n; * map_mft_record_page - map the page in which a specific mft record resides&n; * @ni:&t;&t;ntfs inode whose mft record page to map&n; *&n; * This maps the page in which the mft record of the ntfs inode @ni is situated&n; * and returns a pointer to the mft record within the mapped page.&n; *&n; * Return value needs to be checked with IS_ERR() and if that is true PTR_ERR()&n; * contains the negative error code returned.&n; */
DECL|function|map_mft_record_page
r_static
r_inline
id|MFT_RECORD
op_star
id|map_mft_record_page
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
id|ntfs_volume
op_star
id|vol
op_assign
id|ni-&gt;vol
suffix:semicolon
r_struct
id|inode
op_star
id|mft_vi
op_assign
id|vol-&gt;mft_ino
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|index
comma
id|ofs
comma
id|end_index
suffix:semicolon
id|BUG_ON
c_func
(paren
id|ni-&gt;page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The index into the page cache and the offset within the page cache&n;&t; * page of the wanted mft record. FIXME: We need to check for&n;&t; * overflowing the unsigned long, but I don&squot;t think we would ever get&n;&t; * here if the volume was that big...&n;&t; */
id|index
op_assign
id|ni-&gt;mft_no
op_lshift
id|vol-&gt;mft_record_size_bits
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|ofs
op_assign
(paren
id|ni-&gt;mft_no
op_lshift
id|vol-&gt;mft_record_size_bits
)paren
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
multiline_comment|/* The maximum valid index into the page cache for $MFT&squot;s data. */
id|end_index
op_assign
id|mft_vi-&gt;i_size
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* If the wanted index is out of bounds the mft record doesn&squot;t exist. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|index
op_ge
id|end_index
)paren
)paren
(brace
r_if
c_cond
(paren
id|index
OG
id|end_index
op_logical_or
(paren
id|mft_vi-&gt;i_size
op_amp
op_complement
id|PAGE_CACHE_MASK
)paren
OL
id|ofs
op_plus
id|vol-&gt;mft_record_size
)paren
(brace
id|page
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOENT
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
)brace
multiline_comment|/* Read, map, and pin the page. */
id|page
op_assign
id|ntfs_map_page
c_func
(paren
id|mft_vi-&gt;i_mapping
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|page
)paren
)paren
)paren
(brace
id|ni-&gt;page
op_assign
id|page
suffix:semicolon
id|ni-&gt;page_ofs
op_assign
id|ofs
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|ofs
suffix:semicolon
)brace
id|err_out
suffix:colon
id|ni-&gt;page
op_assign
l_int|NULL
suffix:semicolon
id|ni-&gt;page_ofs
op_assign
l_int|0
suffix:semicolon
id|ntfs_error
c_func
(paren
id|vol-&gt;sb
comma
l_string|&quot;Failed with error code %lu.&quot;
comma
op_minus
id|PTR_ERR
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|page
suffix:semicolon
)brace
multiline_comment|/**&n; * map_mft_record - map, pin and lock an mft record&n; * @ni:&t;&t;ntfs inode whose MFT record to map&n; *&n; * First, take the mrec_lock semaphore. We might now be sleeping, while waiting&n; * for the semaphore if it was already locked by someone else.&n; *&n; * The page of the record is mapped using map_mft_record_page() before being&n; * returned to the caller.&n; *&n; * This in turn uses ntfs_map_page() to get the page containing the wanted mft&n; * record (it in turn calls read_cache_page() which reads it in from disk if&n; * necessary, increments the use count on the page so that it cannot disappear&n; * under us and returns a reference to the page cache page).&n; *&n; * If read_cache_page() invokes ntfs_readpage() to load the page from disk, it&n; * sets PG_locked and clears PG_uptodate on the page. Once I/O has completed&n; * and the post-read mst fixups on each mft record in the page have been&n; * performed, the page gets PG_uptodate set and PG_locked cleared (this is done&n; * in our asynchronous I/O completion handler end_buffer_read_mft_async()).&n; * ntfs_map_page() waits for PG_locked to become clear and checks if&n; * PG_uptodate is set and returns an error code if not. This provides&n; * sufficient protection against races when reading/using the page.&n; *&n; * However there is the write mapping to think about. Doing the above described&n; * checking here will be fine, because when initiating the write we will set&n; * PG_locked and clear PG_uptodate making sure nobody is touching the page&n; * contents. Doing the locking this way means that the commit to disk code in&n; * the page cache code paths is automatically sufficiently locked with us as&n; * we will not touch a page that has been locked or is not uptodate. The only&n; * locking problem then is them locking the page while we are accessing it.&n; *&n; * So that code will end up having to own the mrec_lock of all mft&n; * records/inodes present in the page before I/O can proceed. In that case we&n; * wouldn&squot;t need to bother with PG_locked and PG_uptodate as nobody will be&n; * accessing anything without owning the mrec_lock semaphore. But we do need&n; * to use them because of the read_cache_page() invocation and the code becomes&n; * so much simpler this way that it is well worth it.&n; *&n; * The mft record is now ours and we return a pointer to it. You need to check&n; * the returned pointer with IS_ERR() and if that is true, PTR_ERR() will return&n; * the error code.&n; *&n; * NOTE: Caller is responsible for setting the mft record dirty before calling&n; * unmap_mft_record(). This is obviously only necessary if the caller really&n; * modified the mft record...&n; * Q: Do we want to recycle one of the VFS inode state bits instead?&n; * A: No, the inode ones mean we want to change the mft record, not we want to&n; * write it out.&n; */
DECL|function|map_mft_record
id|MFT_RECORD
op_star
id|map_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
id|MFT_RECORD
op_star
id|m
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Entering for mft_no 0x%lx.&quot;
comma
id|ni-&gt;mft_no
)paren
suffix:semicolon
multiline_comment|/* Make sure the ntfs inode doesn&squot;t go away. */
id|atomic_inc
c_func
(paren
op_amp
id|ni-&gt;count
)paren
suffix:semicolon
multiline_comment|/* Serialize access to this mft record. */
id|down
c_func
(paren
op_amp
id|ni-&gt;mrec_lock
)paren
suffix:semicolon
id|m
op_assign
id|map_mft_record_page
c_func
(paren
id|ni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|m
)paren
)paren
)paren
r_return
id|m
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ni-&gt;mrec_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ni-&gt;count
)paren
suffix:semicolon
id|ntfs_error
c_func
(paren
id|ni-&gt;vol-&gt;sb
comma
l_string|&quot;Failed with error code %lu.&quot;
comma
op_minus
id|PTR_ERR
c_func
(paren
id|m
)paren
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
multiline_comment|/**&n; * unmap_mft_record_page - unmap the page in which a specific mft record resides&n; * @ni:&t;&t;ntfs inode whose mft record page to unmap&n; *&n; * This unmaps the page in which the mft record of the ntfs inode @ni is&n; * situated and returns. This is a NOOP if highmem is not configured.&n; *&n; * The unmap happens via ntfs_unmap_page() which in turn decrements the use&n; * count on the page thus releasing it from the pinned state.&n; *&n; * We do not actually unmap the page from memory of course, as that will be&n; * done by the page cache code itself when memory pressure increases or&n; * whatever.&n; */
DECL|function|unmap_mft_record_page
r_static
r_inline
r_void
id|unmap_mft_record_page
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|ni-&gt;page
)paren
suffix:semicolon
singleline_comment|// TODO: If dirty, blah...
id|ntfs_unmap_page
c_func
(paren
id|ni-&gt;page
)paren
suffix:semicolon
id|ni-&gt;page
op_assign
l_int|NULL
suffix:semicolon
id|ni-&gt;page_ofs
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * unmap_mft_record - release a mapped mft record&n; * @ni:&t;&t;ntfs inode whose MFT record to unmap&n; *&n; * We release the page mapping and the mrec_lock mutex which unmaps the mft&n; * record and releases it for others to get hold of. We also release the ntfs&n; * inode by decrementing the ntfs inode reference count.&n; *&n; * NOTE: If caller has modified the mft record, it is imperative to set the mft&n; * record dirty BEFORE calling unmap_mft_record().&n; */
DECL|function|unmap_mft_record
r_void
id|unmap_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|ni
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|ni-&gt;page
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|page
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Entering for mft_no 0x%lx.&quot;
comma
id|ni-&gt;mft_no
)paren
suffix:semicolon
id|unmap_mft_record_page
c_func
(paren
id|ni
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ni-&gt;mrec_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|ni-&gt;count
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If pure ntfs_inode, i.e. no vfs inode attached, we leave it to&n;&t; * ntfs_clear_extent_inode() in the extent inode case, and to the&n;&t; * caller in the non-extent, yet pure ntfs inode case, to do the actual&n;&t; * tear down of all structures and freeing of all allocated memory.&n;&t; */
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * map_extent_mft_record - load an extent inode and attach it to its base&n; * @base_ni:&t;base ntfs inode&n; * @mref:&t;mft reference of the extent inode to load (in little endian)&n; * @ntfs_ino:&t;on successful return, pointer to the ntfs_inode structure&n; *&n; * Load the extent mft record @mref and attach it to its base inode @base_ni.&n; * Return the mapped extent mft record if IS_ERR(result) is false. Otherwise&n; * PTR_ERR(result) gives the negative error code.&n; *&n; * On successful return, @ntfs_ino contains a pointer to the ntfs_inode&n; * structure of the mapped extent inode.&n; */
DECL|function|map_extent_mft_record
id|MFT_RECORD
op_star
id|map_extent_mft_record
c_func
(paren
id|ntfs_inode
op_star
id|base_ni
comma
id|MFT_REF
id|mref
comma
id|ntfs_inode
op_star
op_star
id|ntfs_ino
)paren
(brace
id|MFT_RECORD
op_star
id|m
suffix:semicolon
id|ntfs_inode
op_star
id|ni
op_assign
l_int|NULL
suffix:semicolon
id|ntfs_inode
op_star
op_star
id|extent_nis
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|mft_no
op_assign
id|MREF_LE
c_func
(paren
id|mref
)paren
suffix:semicolon
id|u16
id|seq_no
op_assign
id|MSEQNO_LE
c_func
(paren
id|mref
)paren
suffix:semicolon
id|BOOL
id|destroy_ni
op_assign
id|FALSE
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Mapping extent mft record 0x%lx (base mft record 0x%lx).&quot;
comma
id|mft_no
comma
id|base_ni-&gt;mft_no
)paren
suffix:semicolon
multiline_comment|/* Make sure the base ntfs inode doesn&squot;t go away. */
id|atomic_inc
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check if this extent inode has already been added to the base inode,&n;&t; * in which case just return it. If not found, add it to the base&n;&t; * inode before returning it.&n;&t; */
id|down
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_ni-&gt;nr_extents
OG
l_int|0
)paren
(brace
id|extent_nis
op_assign
id|base_ni-&gt;ext.extent_ntfs_inos
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
id|base_ni-&gt;nr_extents
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mft_no
op_ne
id|extent_nis
(braket
id|i
)braket
op_member_access_from_pointer
id|mft_no
)paren
r_continue
suffix:semicolon
id|ni
op_assign
id|extent_nis
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* Make sure the ntfs inode doesn&squot;t go away. */
id|atomic_inc
c_func
(paren
op_amp
id|ni-&gt;count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|ni
op_ne
l_int|NULL
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
multiline_comment|/* We found the record; just have to map and return it. */
id|m
op_assign
id|map_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
multiline_comment|/* map_mft_record() has incremented this on success. */
id|atomic_dec
c_func
(paren
op_amp
id|ni-&gt;count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|m
)paren
)paren
)paren
(brace
multiline_comment|/* Verify the sequence number. */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|m-&gt;sequence_number
)paren
op_eq
id|seq_no
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Done 1.&quot;
)paren
suffix:semicolon
op_star
id|ntfs_ino
op_assign
id|ni
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
id|ntfs_error
c_func
(paren
id|base_ni-&gt;vol-&gt;sb
comma
l_string|&quot;Found stale extent mft &quot;
l_string|&quot;reference! Corrupt file system. &quot;
l_string|&quot;Run chkdsk.&quot;
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
id|map_err_out
suffix:colon
id|ntfs_error
c_func
(paren
id|base_ni-&gt;vol-&gt;sb
comma
l_string|&quot;Failed to map extent &quot;
l_string|&quot;mft record, error code %ld.&quot;
comma
op_minus
id|PTR_ERR
c_func
(paren
id|m
)paren
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
multiline_comment|/* Record wasn&squot;t there. Get a new ntfs inode and initialize it. */
id|ni
op_assign
id|ntfs_new_extent_inode
c_func
(paren
id|base_ni-&gt;vol-&gt;sb
comma
id|mft_no
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|ni
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|ni-&gt;vol
op_assign
id|base_ni-&gt;vol
suffix:semicolon
id|ni-&gt;seq_no
op_assign
id|seq_no
suffix:semicolon
id|ni-&gt;nr_extents
op_assign
op_minus
l_int|1
suffix:semicolon
id|ni-&gt;ext.base_ntfs_ino
op_assign
id|base_ni
suffix:semicolon
multiline_comment|/* Now map the record. */
id|m
op_assign
id|map_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|IS_ERR
c_func
(paren
id|m
)paren
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
id|ntfs_clear_extent_inode
c_func
(paren
id|ni
)paren
suffix:semicolon
r_goto
id|map_err_out
suffix:semicolon
)brace
multiline_comment|/* Verify the sequence number. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|m-&gt;sequence_number
)paren
op_ne
id|seq_no
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|base_ni-&gt;vol-&gt;sb
comma
l_string|&quot;Found stale extent mft &quot;
l_string|&quot;reference! Corrupt file system. Run chkdsk.&quot;
)paren
suffix:semicolon
id|destroy_ni
op_assign
id|TRUE
suffix:semicolon
id|m
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
multiline_comment|/* Attach extent inode to base inode, reallocating memory if needed. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|base_ni-&gt;nr_extents
op_amp
l_int|3
)paren
)paren
(brace
id|ntfs_inode
op_star
op_star
id|tmp
suffix:semicolon
r_int
id|new_size
op_assign
(paren
id|base_ni-&gt;nr_extents
op_plus
l_int|4
)paren
op_star
r_sizeof
(paren
id|ntfs_inode
op_star
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|ntfs_inode
op_star
op_star
)paren
id|kmalloc
c_func
(paren
id|new_size
comma
id|GFP_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|tmp
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|base_ni-&gt;vol-&gt;sb
comma
l_string|&quot;Failed to allocate &quot;
l_string|&quot;internal buffer.&quot;
)paren
suffix:semicolon
id|destroy_ni
op_assign
id|TRUE
suffix:semicolon
id|m
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base_ni-&gt;ext.extent_ntfs_inos
)paren
(brace
id|memcpy
c_func
(paren
id|tmp
comma
id|base_ni-&gt;ext.extent_ntfs_inos
comma
id|new_size
op_minus
l_int|4
op_star
r_sizeof
(paren
id|ntfs_inode
op_star
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|base_ni-&gt;ext.extent_ntfs_inos
)paren
suffix:semicolon
)brace
id|base_ni-&gt;ext.extent_ntfs_inos
op_assign
id|tmp
suffix:semicolon
)brace
id|base_ni-&gt;ext.extent_ntfs_inos
(braket
id|base_ni-&gt;nr_extents
op_increment
)braket
op_assign
id|ni
suffix:semicolon
id|up
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done 2.&quot;
)paren
suffix:semicolon
op_star
id|ntfs_ino
op_assign
id|ni
suffix:semicolon
r_return
id|m
suffix:semicolon
id|unm_err_out
suffix:colon
id|unmap_mft_record
c_func
(paren
id|ni
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|base_ni-&gt;extent_lock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|base_ni-&gt;count
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the extent inode was not attached to the base inode we need to&n;&t; * release it or we will leak memory.&n;&t; */
r_if
c_cond
(paren
id|destroy_ni
)paren
id|ntfs_clear_extent_inode
c_func
(paren
id|ni
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
eof
