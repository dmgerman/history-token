multiline_comment|/**&n; * aops.h - Defines for NTFS kernel address space operations and page cache&n; *&t;    handling.  Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; * Copyright (c) 2002 Richard Russon&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _LINUX_NTFS_AOPS_H
DECL|macro|_LINUX_NTFS_AOPS_H
mdefine_line|#define _LINUX_NTFS_AOPS_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;inode.h&quot;
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
multiline_comment|/**&n; * ntfs_map_page - map a page into accessible memory, reading it if necessary&n; * @mapping:&t;address space for which to obtain the page&n; * @index:&t;index into the page cache for @mapping of the page to map&n; *&n; * Read a page from the page cache of the address space @mapping at position&n; * @index, where @index is in units of PAGE_CACHE_SIZE, and not in bytes.&n; *&n; * If the page is not in memory it is loaded from disk first using the readpage&n; * method defined in the address space operations of @mapping and the page is&n; * added to the page cache of @mapping in the process.&n; *&n; * If the page belongs to an mst protected attribute and it is marked as such&n; * in its ntfs inode (NInoMstProtected()) the mst fixups are applied but no&n; * error checking is performed.  This means the caller has to verify whether&n; * the ntfs record(s) contained in the page are valid or not using one of the&n; * ntfs_is_XXXX_record{,p}() macros, where XXXX is the record type you are&n; * expecting to see.  (For details of the macros, see fs/ntfs/layout.h.)&n; *&n; * If the page is in high memory it is mapped into memory directly addressible&n; * by the kernel.&n; *&n; * Finally the page count is incremented, thus pinning the page into place.&n; *&n; * The above means that page_address(page) can be used on all pages obtained&n; * with ntfs_map_page() to get the kernel virtual address of the page.&n; *&n; * When finished with the page, the caller has to call ntfs_unmap_page() to&n; * unpin, unmap and release the page.&n; *&n; * Note this does not grant exclusive access. If such is desired, the caller&n; * must provide it independently of the ntfs_{un}map_page() calls by using&n; * a {rw_}semaphore or other means of serialization. A spin lock cannot be&n; * used as ntfs_map_page() can block.&n; *&n; * The unlocked and uptodate page is returned on success or an encoded error&n; * on failure. Caller has to test for error using the IS_ERR() macro on the&n; * return value. If that evaluates to TRUE, the negative error code can be&n; * obtained using PTR_ERR() on the return value of ntfs_map_page().&n; */
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
macro_line|#ifdef NTFS_RW
r_extern
r_void
id|mark_ntfs_record_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_const
r_int
r_int
id|ofs
)paren
suffix:semicolon
macro_line|#endif /* NTFS_RW */
macro_line|#endif /* _LINUX_NTFS_AOPS_H */
eof
