multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_METAPAGE
DECL|macro|_H_JFS_METAPAGE
mdefine_line|#define _H_JFS_METAPAGE
macro_line|#include &lt;linux/pagemap.h&gt;
DECL|struct|metapage
r_typedef
r_struct
id|metapage
(brace
multiline_comment|/* Common logsyncblk prefix (see jfs_logmgr.h) */
DECL|member|xflag
id|u16
id|xflag
suffix:semicolon
DECL|member|unused
id|u16
id|unused
suffix:semicolon
DECL|member|lid
id|lid_t
id|lid
suffix:semicolon
DECL|member|lsn
r_int
id|lsn
suffix:semicolon
DECL|member|synclist
r_struct
id|list_head
id|synclist
suffix:semicolon
multiline_comment|/* End of logsyncblk prefix */
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
multiline_comment|/* See Below */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* Reference count */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* Data pointer */
multiline_comment|/* list management stuff */
DECL|member|hash_prev
r_struct
id|metapage
op_star
id|hash_prev
suffix:semicolon
DECL|member|hash_next
r_struct
id|metapage
op_star
id|hash_next
suffix:semicolon
multiline_comment|/* Also used for free list */
DECL|member|inode_list
r_struct
id|list_head
id|inode_list
suffix:semicolon
multiline_comment|/* per-inode metapage list */
multiline_comment|/*&n;&t; * mapping &amp; index become redundant, but we need these here to&n;&t; * add the metapage to the hash before we have the real page&n;&t; */
DECL|member|mapping
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* implementation */
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|logical_size
r_int
r_int
id|logical_size
suffix:semicolon
multiline_comment|/* Journal management */
DECL|member|clsn
r_int
id|clsn
suffix:semicolon
DECL|member|nohomeok
id|atomic_t
id|nohomeok
suffix:semicolon
DECL|member|log
r_struct
id|jfs_log
op_star
id|log
suffix:semicolon
DECL|typedef|metapage_t
)brace
id|metapage_t
suffix:semicolon
multiline_comment|/*&n; * Direct-access address space operations&n; */
r_extern
r_struct
id|address_space_operations
id|direct_aops
suffix:semicolon
multiline_comment|/* metapage flag */
DECL|macro|META_locked
mdefine_line|#define META_locked&t;0
DECL|macro|META_absolute
mdefine_line|#define META_absolute&t;1
DECL|macro|META_free
mdefine_line|#define META_free&t;2
DECL|macro|META_dirty
mdefine_line|#define META_dirty&t;3
DECL|macro|META_sync
mdefine_line|#define META_sync&t;4
DECL|macro|META_discard
mdefine_line|#define META_discard&t;5
DECL|macro|META_forced
mdefine_line|#define META_forced&t;6
DECL|macro|mark_metapage_dirty
mdefine_line|#define mark_metapage_dirty(mp) set_bit(META_dirty, &amp;(mp)-&gt;flag)
multiline_comment|/* function prototypes */
r_extern
id|metapage_t
op_star
id|__get_metapage
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|lblock
comma
r_int
r_int
id|size
comma
r_int
id|absolute
comma
r_int
r_int
r_new
)paren
suffix:semicolon
DECL|macro|read_metapage
mdefine_line|#define read_metapage(inode, lblock, size, absolute)&bslash;&n;&t; __get_metapage(inode, lblock, size, absolute, FALSE)
DECL|macro|get_metapage
mdefine_line|#define get_metapage(inode, lblock, size, absolute)&bslash;&n;&t; __get_metapage(inode, lblock, size, absolute, TRUE)
r_extern
r_void
id|release_metapage
c_func
(paren
id|metapage_t
op_star
)paren
suffix:semicolon
DECL|macro|flush_metapage
mdefine_line|#define flush_metapage(mp) &bslash;&n;{&bslash;&n;&t;set_bit(META_dirty, &amp;(mp)-&gt;flag);&bslash;&n;&t;set_bit(META_sync, &amp;(mp)-&gt;flag);&bslash;&n;&t;release_metapage(mp);&bslash;&n;}
DECL|macro|sync_metapage
mdefine_line|#define sync_metapage(mp) &bslash;&n;&t;generic_buffer_fdatasync((struct inode *)mp-&gt;mapping-&gt;host,&bslash;&n;&t;&t;&t;&t; mp-&gt;page-&gt;index, mp-&gt;page-&gt;index + 1)
DECL|macro|write_metapage
mdefine_line|#define write_metapage(mp) &bslash;&n;{&bslash;&n;&t;set_bit(META_dirty, &amp;(mp)-&gt;flag);&bslash;&n;&t;release_metapage(mp);&bslash;&n;}
DECL|macro|discard_metapage
mdefine_line|#define discard_metapage(mp) &bslash;&n;{&bslash;&n;&t;clear_bit(META_dirty, &amp;(mp)-&gt;flag);&bslash;&n;&t;set_bit(META_discard, &amp;(mp)-&gt;flag);&bslash;&n;&t;release_metapage(mp);&bslash;&n;}
r_extern
r_void
id|hold_metapage
c_func
(paren
id|metapage_t
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine uses hash to explicitly find small number of pages&n; */
r_extern
r_void
id|invalidate_metapages
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This one uses mp_list to invalidate all pages for an inode&n; */
r_extern
r_void
id|invalidate_inode_metapages
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_METAPAGE */
eof
