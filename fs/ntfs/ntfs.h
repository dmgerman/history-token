multiline_comment|/*&n; * ntfs.h - Defines for NTFS Linux kernel driver. Part of the Linux-NTFS&n; *&t;    project.&n; *&n; * Copyright (c) 2001,2002 Anton Altaparmakov.&n; * Copyright (C) 2002 Richard Russon.&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be &n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty &n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS &n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_H
DECL|macro|_LINUX_NTFS_H
mdefine_line|#define _LINUX_NTFS_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;malloc.h&quot;
macro_line|#include &quot;endian.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;inode.h&quot;
macro_line|#include &quot;layout.h&quot;
macro_line|#include &quot;attrib.h&quot;
macro_line|#include &quot;mft.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|NTFS_BLOCK_SIZE
id|NTFS_BLOCK_SIZE
op_assign
l_int|512
comma
DECL|enumerator|NTFS_BLOCK_SIZE_BITS
id|NTFS_BLOCK_SIZE_BITS
op_assign
l_int|9
comma
DECL|enumerator|NTFS_SB_MAGIC
id|NTFS_SB_MAGIC
op_assign
l_int|0x5346544e
comma
multiline_comment|/* &squot;NTFS&squot; */
DECL|enumerator|NTFS_MAX_NAME_LEN
id|NTFS_MAX_NAME_LEN
op_assign
l_int|255
comma
DECL|typedef|NTFS_CONSTANTS
)brace
id|NTFS_CONSTANTS
suffix:semicolon
multiline_comment|/* Global variables. */
multiline_comment|/* Slab caches (from super.c). */
r_extern
id|kmem_cache_t
op_star
id|ntfs_name_cache
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|ntfs_inode_cache
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|ntfs_big_inode_cache
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|ntfs_attr_ctx_cache
suffix:semicolon
multiline_comment|/* The various operations structs defined throughout the driver files. */
r_extern
r_struct
id|super_operations
id|ntfs_sops
suffix:semicolon
r_extern
r_struct
id|super_operations
id|ntfs_mount_sops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|ntfs_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|ntfs_mft_aops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ntfs_file_ops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ntfs_file_inode_ops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ntfs_dir_ops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ntfs_dir_inode_ops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ntfs_empty_file_ops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ntfs_empty_inode_ops
suffix:semicolon
multiline_comment|/* Generic macro to convert pointers to values for comparison purposes. */
macro_line|#ifndef p2n
DECL|macro|p2n
mdefine_line|#define p2n(p)          ((ptrdiff_t)((ptrdiff_t*)(p)))
macro_line|#endif
multiline_comment|/**&n; * NTFS_SB - return the ntfs volume given a vfs super block&n; * @sb:&t;&t;VFS super block&n; *&n; * NTFS_SB() returns the ntfs volume associated with the VFS super block @sb.&n; */
DECL|function|NTFS_SB
r_static
r_inline
id|ntfs_volume
op_star
id|NTFS_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;u.generic_sbp
suffix:semicolon
)brace
multiline_comment|/**&n; * ntfs_unmap_page - release a page that was mapped using ntfs_map_page()&n; * @page:&t;the page to release&n; *&n; * Unpin, unmap and release a page that was obtained from ntfs_map_page().&n; */
DECL|function|ntfs_unmap_page
r_static
r_inline
r_void
id|ntfs_unmap_page
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
multiline_comment|/**&n; * ntfs_map_page - map a page into accessible memory, reading it if necessary&n; * @mapping:&t;address space for which to obtain the page&n; * @index:&t;index into the page cache for @mapping of the page to map&n; *&n; * Read a page from the page cache of the address space @mapping at position&n; * @index, where @index is in units of PAGE_CACHE_SIZE, and not in bytes.&n; *&n; * If the page is not in memory it is loaded from disk first using the readpage&n; * method defined in the address space operations of @mapping and the page is&n; * added to the page cache of @mapping in the process.&n; *&n; * If the page is in high memory it is mapped into memory directly addressible&n; * by the kernel.&n; *&n; * Finally the page count is incremented, thus pinning the page into place.&n; *&n; * The above means that page_address(page) can be used on all pages obtained&n; * with ntfs_map_page() to get the kernel virtual address of the page.&n; *&n; * When finished with the page, the caller has to call ntfs_unmap_page() to&n; * unpin, unmap and release the page.&n; *&n; * Note this does not grant exclusive access. If such is desired, the caller&n; * must provide it independently of the ntfs_{un}map_page() calls by using&n; * a {rw_}semaphore or other means of serialization. A spin lock cannot be&n; * used as ntfs_map_page() can block.&n; *&n; * The unlocked and uptodate page is returned on success or an encoded error&n; * on failure. Caller has to test for error using the IS_ERR() macro on the&n; * return value. If that evaluates to TRUE, the negative error code can be&n; * obtained using PTR_ERR() on the return value of ntfs_map_page().&n; */
DECL|function|ntfs_map_page
r_static
r_inline
r_struct
id|page
op_star
id|ntfs_map_page
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|index
)paren
(brace
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
id|index
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
id|PageUptodate
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|PageError
c_func
(paren
id|page
)paren
)paren
r_return
id|page
suffix:semicolon
id|ntfs_unmap_page
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
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/* Declarations of functions and global variables. */
multiline_comment|/* From fs/ntfs/compress.c */
r_extern
r_int
id|ntfs_read_compressed_block
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
multiline_comment|/* From fs/ntfs/super.c */
DECL|macro|default_upcase_len
mdefine_line|#define default_upcase_len 0x10000
r_extern
m_wchar_t
op_star
id|default_upcase
suffix:semicolon
r_extern
r_int
r_int
id|ntfs_nr_upcase_users
suffix:semicolon
r_extern
r_int
r_int
id|ntfs_nr_mounts
suffix:semicolon
r_extern
r_struct
id|semaphore
id|ntfs_lock
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|val
r_int
id|val
suffix:semicolon
DECL|member|str
r_char
op_star
id|str
suffix:semicolon
DECL|typedef|option_t
)brace
id|option_t
suffix:semicolon
r_extern
r_const
id|option_t
id|on_errors_arr
(braket
)braket
suffix:semicolon
multiline_comment|/* From fs/ntfs/compress.c */
r_extern
r_int
id|allocate_compression_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_compression_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* From fs/ntfs/mst.c */
r_extern
r_int
id|post_read_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
comma
r_const
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_int
id|pre_write_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
comma
r_const
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_void
id|post_write_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
)paren
suffix:semicolon
multiline_comment|/* From fs/ntfs/time.c */
r_extern
r_inline
id|s64
id|utc2ntfs
c_func
(paren
r_const
id|time_t
id|time
)paren
suffix:semicolon
r_extern
r_inline
id|s64
id|get_current_ntfs_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_inline
id|time_t
id|ntfs2utc
c_func
(paren
r_const
id|s64
id|time
)paren
suffix:semicolon
multiline_comment|/* From fs/ntfs/unistr.c */
r_extern
id|BOOL
id|ntfs_are_names_equal
c_func
(paren
r_const
id|uchar_t
op_star
id|s1
comma
r_int
id|s1_len
comma
r_const
id|uchar_t
op_star
id|s2
comma
r_int
id|s2_len
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_size
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_collate_names
c_func
(paren
r_const
id|uchar_t
op_star
id|name1
comma
r_const
id|u32
id|name1_len
comma
r_const
id|uchar_t
op_star
id|name2
comma
r_const
id|u32
id|name2_len
comma
r_const
r_int
id|err_val
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_ucsncmp
c_func
(paren
r_const
id|uchar_t
op_star
id|s1
comma
r_const
id|uchar_t
op_star
id|s2
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_ucsncasecmp
c_func
(paren
r_const
id|uchar_t
op_star
id|s1
comma
r_const
id|uchar_t
op_star
id|s2
comma
r_int
id|n
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_size
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_upcase_name
c_func
(paren
id|uchar_t
op_star
id|name
comma
id|u32
id|name_len
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
suffix:semicolon
r_extern
r_void
id|ntfs_file_upcase_value
c_func
(paren
id|FILE_NAME_ATTR
op_star
id|file_name_attr
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_file_compare_values
c_func
(paren
id|FILE_NAME_ATTR
op_star
id|file_name_attr1
comma
id|FILE_NAME_ATTR
op_star
id|file_name_attr2
comma
r_const
r_int
id|err_val
comma
r_const
id|IGNORE_CASE_BOOL
id|ic
comma
r_const
id|uchar_t
op_star
id|upcase
comma
r_const
id|u32
id|upcase_len
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_nlstoucs
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
r_char
op_star
id|ins
comma
r_const
r_int
id|ins_len
comma
id|uchar_t
op_star
op_star
id|outs
)paren
suffix:semicolon
r_extern
r_int
id|ntfs_ucstonls
c_func
(paren
r_const
id|ntfs_volume
op_star
id|vol
comma
r_const
id|uchar_t
op_star
id|ins
comma
r_const
r_int
id|ins_len
comma
r_int
r_char
op_star
op_star
id|outs
comma
r_int
id|outs_len
)paren
suffix:semicolon
multiline_comment|/* From fs/ntfs/upcase.c */
r_extern
id|uchar_t
op_star
id|generate_default_upcase
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_NTFS_H */
eof
