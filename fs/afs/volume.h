multiline_comment|/* volume.h: AFS volume management&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_VOLUME_H
DECL|macro|_LINUX_AFS_VOLUME_H
mdefine_line|#define _LINUX_AFS_VOLUME_H
macro_line|#include &quot;types.h&quot;
macro_line|#include &quot;fsclient.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &quot;kafsasyncd.h&quot;
macro_line|#include &quot;cache-layout.h&quot;
DECL|macro|__packed
mdefine_line|#define __packed __attribute__((packed))
r_typedef
r_enum
(brace
DECL|enumerator|AFS_VLUPD_SLEEP
id|AFS_VLUPD_SLEEP
comma
multiline_comment|/* sleeping waiting for update timer to fire */
DECL|enumerator|AFS_VLUPD_PENDING
id|AFS_VLUPD_PENDING
comma
multiline_comment|/* on pending queue */
DECL|enumerator|AFS_VLUPD_INPROGRESS
id|AFS_VLUPD_INPROGRESS
comma
multiline_comment|/* op in progress */
DECL|enumerator|AFS_VLUPD_BUSYSLEEP
id|AFS_VLUPD_BUSYSLEEP
comma
multiline_comment|/* sleeping because server returned EBUSY */
DECL|typedef|afs_vlocation_upd_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|afs_vlocation_upd_t
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS volume location record&n; */
DECL|struct|afs_vlocation
r_struct
id|afs_vlocation
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
multiline_comment|/* link in cell volume location list */
DECL|member|timeout
id|afs_timer_t
id|timeout
suffix:semicolon
multiline_comment|/* decaching timer */
DECL|member|cell
id|afs_cell_t
op_star
id|cell
suffix:semicolon
multiline_comment|/* cell to which volume belongs */
DECL|member|caches
r_struct
id|list_head
id|caches
suffix:semicolon
multiline_comment|/* backing caches */
DECL|member|vldb
id|afsc_vldb_record_t
id|vldb
suffix:semicolon
multiline_comment|/* volume information DB record */
DECL|member|vols
r_struct
id|afs_volume
op_star
id|vols
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* volume access record pointer (index by type) */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* access lock */
DECL|member|read_jif
r_int
r_int
id|read_jif
suffix:semicolon
multiline_comment|/* time at which last read from vlserver */
DECL|member|upd_timer
id|afs_timer_t
id|upd_timer
suffix:semicolon
multiline_comment|/* update timer */
DECL|member|upd_op
id|afs_async_op_t
id|upd_op
suffix:semicolon
multiline_comment|/* update operation */
DECL|member|upd_state
id|afs_vlocation_upd_t
id|upd_state
suffix:semicolon
multiline_comment|/* update state */
DECL|member|upd_first_svix
r_int
r_int
id|upd_first_svix
suffix:semicolon
multiline_comment|/* first server index during update */
DECL|member|upd_curr_svix
r_int
r_int
id|upd_curr_svix
suffix:semicolon
multiline_comment|/* current server index during update */
DECL|member|upd_rej_cnt
r_int
r_int
id|upd_rej_cnt
suffix:semicolon
multiline_comment|/* ENOMEDIUM count during update */
DECL|member|upd_busy_cnt
r_int
r_int
id|upd_busy_cnt
suffix:semicolon
multiline_comment|/* EBUSY count during update */
DECL|member|valid
r_int
r_int
id|valid
suffix:semicolon
multiline_comment|/* T if valid */
)brace
suffix:semicolon
r_extern
r_int
id|afs_vlocation_lookup
c_func
(paren
id|afs_cell_t
op_star
id|cell
comma
r_const
r_char
op_star
id|name
comma
id|afs_vlocation_t
op_star
op_star
id|_vlocation
)paren
suffix:semicolon
DECL|macro|afs_get_vlocation
mdefine_line|#define afs_get_vlocation(V) do { atomic_inc(&amp;(V)-&gt;usage); } while(0)
r_extern
r_void
id|__afs_put_vlocation
c_func
(paren
id|afs_vlocation_t
op_star
id|vlocation
)paren
suffix:semicolon
r_extern
r_void
id|afs_put_vlocation
c_func
(paren
id|afs_vlocation_t
op_star
id|vlocation
)paren
suffix:semicolon
r_extern
r_void
id|afs_vlocation_do_timeout
c_func
(paren
id|afs_vlocation_t
op_star
id|vlocation
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS volume access record&n; */
DECL|struct|afs_volume
r_struct
id|afs_volume
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
DECL|member|cell
id|afs_cell_t
op_star
id|cell
suffix:semicolon
multiline_comment|/* cell to which belongs (unrefd ptr) */
DECL|member|vlocation
id|afs_vlocation_t
op_star
id|vlocation
suffix:semicolon
multiline_comment|/* volume location */
DECL|member|vid
id|afs_volid_t
id|vid
suffix:semicolon
multiline_comment|/* volume ID */
DECL|member|type
id|afs_voltype_t
id|__packed
id|type
suffix:semicolon
multiline_comment|/* type of volume */
DECL|member|type_force
r_char
id|type_force
suffix:semicolon
multiline_comment|/* force volume type (suppress R/O -&gt; R/W) */
DECL|member|nservers
r_int
r_int
id|nservers
suffix:semicolon
multiline_comment|/* number of server slots filled */
DECL|member|rjservers
r_int
r_int
id|rjservers
suffix:semicolon
multiline_comment|/* number of servers discarded due to -ENOMEDIUM */
DECL|member|servers
id|afs_server_t
op_star
id|servers
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* servers on which volume resides (ordered) */
DECL|member|server_sem
r_struct
id|rw_semaphore
id|server_sem
suffix:semicolon
multiline_comment|/* lock for accessing current server */
)brace
suffix:semicolon
r_extern
r_int
id|afs_volume_lookup
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|ro
comma
id|afs_volume_t
op_star
op_star
id|_volume
)paren
suffix:semicolon
DECL|macro|afs_get_volume
mdefine_line|#define afs_get_volume(V) do { atomic_inc(&amp;(V)-&gt;usage); } while(0)
r_extern
r_void
id|afs_put_volume
c_func
(paren
id|afs_volume_t
op_star
id|volume
)paren
suffix:semicolon
r_extern
r_int
id|afs_volume_pick_fileserver
c_func
(paren
id|afs_volume_t
op_star
id|volume
comma
id|afs_server_t
op_star
op_star
id|_server
)paren
suffix:semicolon
r_extern
r_int
id|afs_volume_release_fileserver
c_func
(paren
id|afs_volume_t
op_star
id|volume
comma
id|afs_server_t
op_star
id|server
comma
r_int
id|result
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_VOLUME_H */
eof
