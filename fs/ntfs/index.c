multiline_comment|/*&n; * index.c - NTFS kernel index handling.  Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
macro_line|#include &quot;collate.h&quot;
macro_line|#include &quot;index.h&quot;
multiline_comment|/**&n; * ntfs_index_ctx_get - allocate and initialize a new index context&n; * @idx_ni:&t;ntfs index inode with which to initialize the context&n; *&n; * Allocate a new index context, initialize it with @idx_ni and return it.&n; * Return NULL if allocation failed.&n; *&n; * Locking:  Caller must hold i_sem on the index inode.&n; */
DECL|function|ntfs_index_ctx_get
id|ntfs_index_context
op_star
id|ntfs_index_ctx_get
c_func
(paren
id|ntfs_inode
op_star
id|idx_ni
)paren
(brace
id|ntfs_index_context
op_star
id|ictx
suffix:semicolon
id|ictx
op_assign
id|kmem_cache_alloc
c_func
(paren
id|ntfs_index_ctx_cache
comma
id|SLAB_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ictx
)paren
(brace
id|ictx-&gt;idx_ni
op_assign
id|idx_ni
suffix:semicolon
id|ictx-&gt;entry
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;data_len
op_assign
l_int|0
suffix:semicolon
id|ictx-&gt;is_in_root
op_assign
l_int|0
suffix:semicolon
id|ictx-&gt;ir
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;actx
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;base_ni
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;ia
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;page
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|ictx
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_index_ctx_put - release an index context&n; * @ictx:&t;index context to free&n; *&n; * Release the index context @ictx, releasing all associated resources.&n; *&n; * Locking:  Caller must hold i_sem on the index inode.&n; */
DECL|function|ntfs_index_ctx_put
r_void
id|ntfs_index_ctx_put
c_func
(paren
id|ntfs_index_context
op_star
id|ictx
)paren
(brace
r_if
c_cond
(paren
id|ictx-&gt;entry
)paren
(brace
r_if
c_cond
(paren
id|ictx-&gt;is_in_root
)paren
(brace
r_if
c_cond
(paren
id|ictx-&gt;actx
)paren
id|ntfs_attr_put_search_ctx
c_func
(paren
id|ictx-&gt;actx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ictx-&gt;base_ni
)paren
id|unmap_mft_record
c_func
(paren
id|ictx-&gt;base_ni
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|page
op_star
id|page
op_assign
id|ictx-&gt;page
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ntfs_unmap_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
)brace
id|kmem_cache_free
c_func
(paren
id|ntfs_index_ctx_cache
comma
id|ictx
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_index_lookup - find a key in an index and return its index entry&n; * @key:&t;[IN] key for which to search in the index&n; * @key_len:&t;[IN] length of @key in bytes&n; * @ictx:&t;[IN/OUT] context describing the index and the returned entry&n; *&n; * Before calling ntfs_index_lookup(), @ictx must have been obtained from a&n; * call to ntfs_index_ctx_get().&n; *&n; * Look for the @key in the index specified by the index lookup context @ictx.&n; * ntfs_index_lookup() walks the contents of the index looking for the @key.&n; *&n; * If the @key is found in the index, 0 is returned and @ictx is setup to&n; * describe the index entry containing the matching @key.  @ictx-&gt;entry is the&n; * index entry and @ictx-&gt;data and @ictx-&gt;data_len are the index entry data and&n; * its length in bytes, respectively.&n; *&n; * If the @key is not found in the index, -ENOENT is returned and @ictx is&n; * setup to describe the index entry whose key collates immediately after the&n; * search @key, i.e. this is the position in the index at which an index entry&n; * with a key of @key would need to be inserted.&n; *&n; * If an error occurs return the negative error code and @ictx is left&n; * untouched.&n; *&n; * When finished with the entry and its data, call ntfs_index_ctx_put() to free&n; * the context and other associated resources.&n; *&n; * If the index entry was modified, call flush_dcache_index_entry_page()&n; * immediately after the modification and either ntfs_index_entry_mark_dirty()&n; * or ntfs_index_entry_write() before the call to ntfs_index_ctx_put() to&n; * ensure that the changes are written to disk.&n; *&n; * Locking:  - Caller must hold i_sem on the index inode.&n; *&t;     - Each page cache page in the index allocation mapping must be&n; *&t;       locked whilst being accessed otherwise we may find a corrupt&n; *&t;       page due to it being under -&gt;writepage at the moment which&n; *&t;       applies the mst protection fixups before writing out and then&n; *&t;       removes them again after the write is complete after which it &n; *&t;       unlocks the page.&n; */
DECL|function|ntfs_index_lookup
r_int
id|ntfs_index_lookup
c_func
(paren
r_const
r_void
op_star
id|key
comma
r_const
r_int
id|key_len
comma
id|ntfs_index_context
op_star
id|ictx
)paren
(brace
id|VCN
id|vcn
comma
id|old_vcn
suffix:semicolon
id|ntfs_inode
op_star
id|idx_ni
op_assign
id|ictx-&gt;idx_ni
suffix:semicolon
id|ntfs_volume
op_star
id|vol
op_assign
id|idx_ni-&gt;vol
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|vol-&gt;sb
suffix:semicolon
id|ntfs_inode
op_star
id|base_ni
op_assign
id|idx_ni-&gt;ext.base_ntfs_ino
suffix:semicolon
id|MFT_RECORD
op_star
id|m
suffix:semicolon
id|INDEX_ROOT
op_star
id|ir
suffix:semicolon
id|INDEX_ENTRY
op_star
id|ie
suffix:semicolon
id|INDEX_ALLOCATION
op_star
id|ia
suffix:semicolon
id|u8
op_star
id|index_end
comma
op_star
id|kaddr
suffix:semicolon
id|ntfs_attr_search_ctx
op_star
id|actx
suffix:semicolon
r_struct
id|address_space
op_star
id|ia_mapping
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
id|rc
comma
id|err
op_assign
l_int|0
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Entering.&quot;
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|NInoAttr
c_func
(paren
id|idx_ni
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|idx_ni-&gt;type
op_ne
id|AT_INDEX_ALLOCATION
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|idx_ni-&gt;nr_extents
op_ne
op_minus
l_int|1
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|base_ni
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|key
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|key_len
op_le
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ntfs_is_collation_rule_supported
c_func
(paren
id|idx_ni-&gt;itype.index.collation_rule
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index uses unsupported collation rule 0x%x.  &quot;
l_string|&quot;Aborting lookup.&quot;
comma
id|le32_to_cpu
c_func
(paren
id|idx_ni-&gt;itype.index.collation_rule
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/* Get hold of the mft record for the index inode. */
id|m
op_assign
id|map_mft_record
c_func
(paren
id|base_ni
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
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;map_mft_record() failed with error code %ld.&quot;
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
id|PTR_ERR
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
id|actx
op_assign
id|ntfs_attr_get_search_ctx
c_func
(paren
id|base_ni
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|actx
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* Find the index root attribute in the mft record. */
id|err
op_assign
id|ntfs_attr_lookup
c_func
(paren
id|AT_INDEX_ROOT
comma
id|idx_ni-&gt;name
comma
id|idx_ni-&gt;name_len
comma
id|CASE_SENSITIVE
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|actx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
)paren
)paren
(brace
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ENOENT
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index root attribute missing in inode &quot;
l_string|&quot;0x%lx.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* Get to the index root value (it has been verified in read_inode). */
id|ir
op_assign
(paren
id|INDEX_ROOT
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|actx-&gt;attr
op_plus
id|le16_to_cpu
c_func
(paren
id|actx-&gt;attr-&gt;data.resident.value_offset
)paren
)paren
suffix:semicolon
id|index_end
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|ir-&gt;index
op_plus
id|le32_to_cpu
c_func
(paren
id|ir-&gt;index.index_length
)paren
suffix:semicolon
multiline_comment|/* The first index entry. */
id|ie
op_assign
(paren
id|INDEX_ENTRY
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ir-&gt;index
op_plus
id|le32_to_cpu
c_func
(paren
id|ir-&gt;index.entries_offset
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Loop until we exceed valid memory (corruption case) or until we&n;&t; * reach the last entry.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
id|ie
op_assign
(paren
id|INDEX_ENTRY
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
)paren
)paren
(brace
multiline_comment|/* Bounds checks. */
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
id|ie
template_param
id|index_end
op_logical_or
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
OG
id|index_end
)paren
r_goto
id|idx_err_out
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The last entry cannot contain a key.  It can however contain&n;&t;&t; * a pointer to a child node in the B+tree so we just break out.&n;&t;&t; */
r_if
c_cond
(paren
id|ie-&gt;flags
op_amp
id|INDEX_ENTRY_END
)paren
r_break
suffix:semicolon
multiline_comment|/* Further bounds checks. */
r_if
c_cond
(paren
(paren
id|u32
)paren
r_sizeof
(paren
id|INDEX_ENTRY_HEADER
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
OG
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_offset
)paren
op_logical_or
(paren
id|u32
)paren
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_offset
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_length
)paren
OG
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
)paren
r_goto
id|idx_err_out
suffix:semicolon
multiline_comment|/* If the keys match perfectly, we setup @ictx and return 0. */
r_if
c_cond
(paren
(paren
id|key_len
op_eq
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|key
comma
op_amp
id|ie-&gt;key
comma
id|key_len
)paren
)paren
(brace
id|ir_done
suffix:colon
id|ictx-&gt;is_in_root
op_assign
id|TRUE
suffix:semicolon
id|ictx-&gt;actx
op_assign
id|actx
suffix:semicolon
id|ictx-&gt;base_ni
op_assign
id|base_ni
suffix:semicolon
id|ictx-&gt;ia
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;page
op_assign
l_int|NULL
suffix:semicolon
id|done
suffix:colon
id|ictx-&gt;entry
op_assign
id|ie
suffix:semicolon
id|ictx-&gt;data
op_assign
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_offset
)paren
suffix:semicolon
id|ictx-&gt;data_len
op_assign
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_length
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
l_string|&quot;Done.&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Not a perfect match, need to do full blown collation so we&n;&t;&t; * know which way in the B+tree we have to go.&n;&t;&t; */
id|rc
op_assign
id|ntfs_collate
c_func
(paren
id|vol
comma
id|idx_ni-&gt;itype.index.collation_rule
comma
id|key
comma
id|key_len
comma
op_amp
id|ie-&gt;key
comma
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If @key collates before the key of the current entry, there&n;&t;&t; * is definitely no such key in this index but we might need to&n;&t;&t; * descend into the B+tree so we just break out of the loop.&n;&t;&t; */
r_if
c_cond
(paren
id|rc
op_eq
op_minus
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A match should never happen as the memcmp() call should have&n;&t;&t; * cought it, but we still treat it correctly.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
r_goto
id|ir_done
suffix:semicolon
multiline_comment|/* The keys are not equal, continue the search. */
)brace
multiline_comment|/*&n;&t; * We have finished with this index without success.  Check for the&n;&t; * presence of a child node and if not present setup @ictx and return&n;&t; * -ENOENT.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ie-&gt;flags
op_amp
id|INDEX_ENTRY_NODE
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Entry not found.&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|ir_done
suffix:semicolon
)brace
multiline_comment|/* Child node present, descend into it. */
multiline_comment|/* Consistency check: Verify that an index allocation exists. */
r_if
c_cond
(paren
op_logical_neg
id|NInoIndexAllocPresent
c_func
(paren
id|idx_ni
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;No index allocation attribute but index entry &quot;
l_string|&quot;requires one.  Inode 0x%lx is corrupt or &quot;
l_string|&quot;driver bug.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
multiline_comment|/* Get the starting vcn of the index_block holding the child node. */
id|vcn
op_assign
id|sle64_to_cpup
c_func
(paren
(paren
id|sle64
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|ia_mapping
op_assign
id|VFS_I
c_func
(paren
id|idx_ni
)paren
op_member_access_from_pointer
id|i_mapping
suffix:semicolon
multiline_comment|/*&n;&t; * We are done with the index root and the mft record.  Release them,&n;&t; * otherwise we deadlock with ntfs_map_page().&n;&t; */
id|ntfs_attr_put_search_ctx
c_func
(paren
id|actx
)paren
suffix:semicolon
id|unmap_mft_record
c_func
(paren
id|base_ni
)paren
suffix:semicolon
id|m
op_assign
l_int|NULL
suffix:semicolon
id|actx
op_assign
l_int|NULL
suffix:semicolon
id|descend_into_child_node
suffix:colon
multiline_comment|/*&n;&t; * Convert vcn to index into the index allocation attribute in units&n;&t; * of PAGE_CACHE_SIZE and map the page cache page, reading it from&n;&t; * disk if necessary.&n;&t; */
id|page
op_assign
id|ntfs_map_page
c_func
(paren
id|ia_mapping
comma
id|vcn
op_lshift
id|idx_ni-&gt;itype.index.vcn_size_bits
op_rshift
id|PAGE_CACHE_SHIFT
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
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Failed to map index page, error %ld.&quot;
comma
op_minus
id|PTR_ERR
c_func
(paren
id|page
)paren
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
r_goto
id|err_out
suffix:semicolon
)brace
id|lock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kaddr
op_assign
(paren
id|u8
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|fast_descend_into_child_node
suffix:colon
multiline_comment|/* Get to the index allocation block. */
id|ia
op_assign
(paren
id|INDEX_ALLOCATION
op_star
)paren
(paren
id|kaddr
op_plus
(paren
(paren
id|vcn
op_lshift
id|idx_ni-&gt;itype.index.vcn_size_bits
)paren
op_amp
op_complement
id|PAGE_CACHE_MASK
)paren
)paren
suffix:semicolon
multiline_comment|/* Bounds checks. */
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
id|ia
template_param
id|kaddr
op_plus
id|PAGE_CACHE_SIZE
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Out of bounds check failed.  Corrupt inode &quot;
l_string|&quot;0x%lx or driver bug.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sle64_to_cpu
c_func
(paren
id|ia-&gt;index_block_vcn
)paren
op_ne
id|vcn
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Actual VCN (0x%llx) of index buffer is &quot;
l_string|&quot;different from expected VCN (0x%llx).  Inode &quot;
l_string|&quot;0x%lx is corrupt or driver bug.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|sle64_to_cpu
c_func
(paren
id|ia-&gt;index_block_vcn
)paren
comma
(paren
r_int
r_int
r_int
)paren
id|vcn
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|ia-&gt;index.allocated_size
)paren
op_plus
l_int|0x18
op_ne
id|idx_ni-&gt;itype.index.block_size
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index buffer (VCN 0x%llx) of inode 0x%lx has &quot;
l_string|&quot;a size (%u) differing from the index &quot;
l_string|&quot;specified size (%u).  Inode is corrupt or &quot;
l_string|&quot;driver bug.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|vcn
comma
id|idx_ni-&gt;mft_no
comma
id|le32_to_cpu
c_func
(paren
id|ia-&gt;index.allocated_size
)paren
op_plus
l_int|0x18
comma
id|idx_ni-&gt;itype.index.block_size
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
id|index_end
op_assign
(paren
id|u8
op_star
)paren
id|ia
op_plus
id|idx_ni-&gt;itype.index.block_size
suffix:semicolon
r_if
c_cond
(paren
id|index_end
OG
id|kaddr
op_plus
id|PAGE_CACHE_SIZE
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index buffer (VCN 0x%llx) of inode 0x%lx &quot;
l_string|&quot;crosses page boundary.  Impossible!  Cannot &quot;
l_string|&quot;access!  This is probably a bug in the &quot;
l_string|&quot;driver.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|vcn
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
id|index_end
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|ia-&gt;index
op_plus
id|le32_to_cpu
c_func
(paren
id|ia-&gt;index.index_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index_end
OG
(paren
id|u8
op_star
)paren
id|ia
op_plus
id|idx_ni-&gt;itype.index.block_size
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Size of index buffer (VCN 0x%llx) of inode &quot;
l_string|&quot;0x%lx exceeds maximum size.&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|vcn
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
multiline_comment|/* The first index entry. */
id|ie
op_assign
(paren
id|INDEX_ENTRY
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
op_amp
id|ia-&gt;index
op_plus
id|le32_to_cpu
c_func
(paren
id|ia-&gt;index.entries_offset
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Iterate similar to above big loop but applied to index buffer, thus&n;&t; * loop until we exceed valid memory (corruption case) or until we&n;&t; * reach the last entry.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
id|ie
op_assign
(paren
id|INDEX_ENTRY
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
)paren
)paren
(brace
multiline_comment|/* Bounds checks. */
r_if
c_cond
(paren
(paren
id|u8
op_star
)paren
id|ie
template_param
id|index_end
op_logical_or
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
OG
id|index_end
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index entry out of bounds in inode &quot;
l_string|&quot;0x%lx.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The last entry cannot contain a ket.  It can however contain&n;&t;&t; * a pointer to a child node in the B+tree so we just break out.&n;&t;&t; */
r_if
c_cond
(paren
id|ie-&gt;flags
op_amp
id|INDEX_ENTRY_END
)paren
r_break
suffix:semicolon
multiline_comment|/* Further bounds checks. */
r_if
c_cond
(paren
(paren
id|u32
)paren
r_sizeof
(paren
id|INDEX_ENTRY_HEADER
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
OG
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_offset
)paren
op_logical_or
(paren
id|u32
)paren
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_offset
)paren
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;data.vi.data_length
)paren
OG
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index entry out of bounds in inode &quot;
l_string|&quot;0x%lx.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
multiline_comment|/* If the keys match perfectly, we setup @ictx and return 0. */
r_if
c_cond
(paren
(paren
id|key_len
op_eq
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|key
comma
op_amp
id|ie-&gt;key
comma
id|key_len
)paren
)paren
(brace
id|ia_done
suffix:colon
id|ictx-&gt;is_in_root
op_assign
id|FALSE
suffix:semicolon
id|ictx-&gt;actx
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;base_ni
op_assign
l_int|NULL
suffix:semicolon
id|ictx-&gt;ia
op_assign
id|ia
suffix:semicolon
id|ictx-&gt;page
op_assign
id|page
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Not a perfect match, need to do full blown collation so we&n;&t;&t; * know which way in the B+tree we have to go.&n;&t;&t; */
id|rc
op_assign
id|ntfs_collate
c_func
(paren
id|vol
comma
id|idx_ni-&gt;itype.index.collation_rule
comma
id|key
comma
id|key_len
comma
op_amp
id|ie-&gt;key
comma
id|le16_to_cpu
c_func
(paren
id|ie-&gt;key_length
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If @key collates before the key of the current entry, there&n;&t;&t; * is definitely no such key in this index but we might need to&n;&t;&t; * descend into the B+tree so we just break out of the loop.&n;&t;&t; */
r_if
c_cond
(paren
id|rc
op_eq
op_minus
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * A match should never happen as the memcmp() call should have&n;&t;&t; * cought it, but we still treat it correctly.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
r_goto
id|ia_done
suffix:semicolon
multiline_comment|/* The keys are not equal, continue the search. */
)brace
multiline_comment|/*&n;&t; * We have finished with this index buffer without success.  Check for&n;&t; * the presence of a child node and if not present return -ENOENT.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ie-&gt;flags
op_amp
id|INDEX_ENTRY_NODE
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
l_string|&quot;Entry not found.&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|ia_done
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ia-&gt;index.flags
op_amp
id|NODE_MASK
)paren
op_eq
id|LEAF_NODE
)paren
(brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Index entry with child node found in a leaf &quot;
l_string|&quot;node in inode 0x%lx.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|unm_err_out
suffix:semicolon
)brace
multiline_comment|/* Child node present, descend into it. */
id|old_vcn
op_assign
id|vcn
suffix:semicolon
id|vcn
op_assign
id|sle64_to_cpup
c_func
(paren
(paren
id|sle64
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|ie
op_plus
id|le16_to_cpu
c_func
(paren
id|ie-&gt;length
)paren
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vcn
op_ge
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * If vcn is in the same page cache page as old_vcn we recycle&n;&t;&t; * the mapped page.&n;&t;&t; */
r_if
c_cond
(paren
id|old_vcn
op_lshift
id|vol-&gt;cluster_size_bits
op_rshift
id|PAGE_CACHE_SHIFT
op_eq
id|vcn
op_lshift
id|vol-&gt;cluster_size_bits
op_rshift
id|PAGE_CACHE_SHIFT
)paren
r_goto
id|fast_descend_into_child_node
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ntfs_unmap_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|descend_into_child_node
suffix:semicolon
)brace
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Negative child node vcn in inode 0x%lx.&quot;
comma
id|idx_ni-&gt;mft_no
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
id|unm_err_out
suffix:colon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|ntfs_unmap_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|err_out
suffix:colon
r_if
c_cond
(paren
id|actx
)paren
id|ntfs_attr_put_search_ctx
c_func
(paren
id|actx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
)paren
id|unmap_mft_record
c_func
(paren
id|base_ni
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|idx_err_out
suffix:colon
id|ntfs_error
c_func
(paren
id|sb
comma
l_string|&quot;Corrupt index.  Aborting lookup.&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
eof
