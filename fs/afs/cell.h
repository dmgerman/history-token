multiline_comment|/* cell.h: AFS cell record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_CELL_H
DECL|macro|_LINUX_AFS_CELL_H
mdefine_line|#define _LINUX_AFS_CELL_H
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;cache.h&quot;
DECL|macro|AFS_CELL_MAX_ADDRS
mdefine_line|#define AFS_CELL_MAX_ADDRS 15
r_extern
r_volatile
r_int
id|afs_cells_being_purged
suffix:semicolon
multiline_comment|/* T when cells are being purged by rmmod */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * entry in the cached cell catalogue&n; */
DECL|struct|afs_cache_cell
r_struct
id|afs_cache_cell
(brace
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* cell name (padded with NULs) */
DECL|member|vl_servers
r_struct
id|in_addr
id|vl_servers
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* cached cell VL servers */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS cell record&n; */
DECL|struct|afs_cell
r_struct
id|afs_cell
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* main cell list link */
DECL|member|proc_link
r_struct
id|list_head
id|proc_link
suffix:semicolon
multiline_comment|/* /proc cell list link */
DECL|member|proc_dir
r_struct
id|proc_dir_entry
op_star
id|proc_dir
suffix:semicolon
multiline_comment|/* /proc dir for this cell */
macro_line|#ifdef AFS_CACHING_SUPPORT
DECL|member|cache
r_struct
id|cachefs_cookie
op_star
id|cache
suffix:semicolon
multiline_comment|/* caching cookie */
macro_line|#endif
multiline_comment|/* server record management */
DECL|member|sv_lock
id|rwlock_t
id|sv_lock
suffix:semicolon
multiline_comment|/* active server list lock */
DECL|member|sv_list
r_struct
id|list_head
id|sv_list
suffix:semicolon
multiline_comment|/* active server list */
DECL|member|sv_graveyard
r_struct
id|list_head
id|sv_graveyard
suffix:semicolon
multiline_comment|/* inactive server list */
DECL|member|sv_gylock
id|spinlock_t
id|sv_gylock
suffix:semicolon
multiline_comment|/* inactive server list lock */
multiline_comment|/* volume location record management */
DECL|member|vl_sem
r_struct
id|rw_semaphore
id|vl_sem
suffix:semicolon
multiline_comment|/* volume management serialisation semaphore */
DECL|member|vl_list
r_struct
id|list_head
id|vl_list
suffix:semicolon
multiline_comment|/* cell&squot;s active VL record list */
DECL|member|vl_graveyard
r_struct
id|list_head
id|vl_graveyard
suffix:semicolon
multiline_comment|/* cell&squot;s inactive VL record list */
DECL|member|vl_gylock
id|spinlock_t
id|vl_gylock
suffix:semicolon
multiline_comment|/* graveyard lock */
DECL|member|vl_naddrs
r_int
r_int
id|vl_naddrs
suffix:semicolon
multiline_comment|/* number of VL servers in addr list */
DECL|member|vl_curr_svix
r_int
r_int
id|vl_curr_svix
suffix:semicolon
multiline_comment|/* current server index */
DECL|member|vl_addrs
r_struct
id|in_addr
id|vl_addrs
(braket
id|AFS_CELL_MAX_ADDRS
)braket
suffix:semicolon
multiline_comment|/* cell VL server addresses */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* cell name - must go last */
)brace
suffix:semicolon
r_extern
r_int
id|afs_cell_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|afs_cell_create
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_char
op_star
id|vllist
comma
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
suffix:semicolon
r_extern
r_int
id|afs_cell_lookup
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|nmsize
comma
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
suffix:semicolon
DECL|macro|afs_get_cell
mdefine_line|#define afs_get_cell(C) do { atomic_inc(&amp;(C)-&gt;usage); } while(0)
r_extern
r_struct
id|afs_cell
op_star
id|afs_get_cell_maybe
c_func
(paren
r_struct
id|afs_cell
op_star
op_star
id|_cell
)paren
suffix:semicolon
r_extern
r_void
id|afs_put_cell
c_func
(paren
r_struct
id|afs_cell
op_star
id|cell
)paren
suffix:semicolon
r_extern
r_void
id|afs_cell_purge
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_CELL_H */
eof
