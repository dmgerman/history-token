multiline_comment|/* vnode.h: AFS vnode record&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_VNODE_H
DECL|macro|_LINUX_AFS_VNODE_H
mdefine_line|#define _LINUX_AFS_VNODE_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#ifdef __KERNEL__
r_struct
id|afs_rxfs_fetch_descriptor
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS inode private data&n; */
DECL|struct|afs_vnode
r_struct
id|afs_vnode
(brace
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
multiline_comment|/* the VFS&squot;s inode record */
DECL|member|volume
id|afs_volume_t
op_star
id|volume
suffix:semicolon
multiline_comment|/* volume on which vnode resides */
DECL|member|fid
id|afs_fid_t
id|fid
suffix:semicolon
multiline_comment|/* the file identifier for this inode */
DECL|member|status
id|afs_file_status_t
id|status
suffix:semicolon
multiline_comment|/* AFS status info for this file */
DECL|member|nix
r_int
id|nix
suffix:semicolon
multiline_comment|/* vnode index in cache */
DECL|member|update_waitq
id|wait_queue_head_t
id|update_waitq
suffix:semicolon
multiline_comment|/* status fetch waitqueue */
DECL|member|update_cnt
r_int
id|update_cnt
suffix:semicolon
multiline_comment|/* number of outstanding ops that will update the&n;&t;&t;&t;&t;&t;&t; * status */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* waitqueue/flags lock */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|AFS_VNODE_CHANGED
mdefine_line|#define AFS_VNODE_CHANGED&t;0x00000001&t;/* set if vnode reported changed by callback */
DECL|macro|AFS_VNODE_DELETED
mdefine_line|#define AFS_VNODE_DELETED&t;0x00000002&t;/* set if vnode deleted on server */
DECL|macro|AFS_VNODE_MOUNTPOINT
mdefine_line|#define AFS_VNODE_MOUNTPOINT&t;0x00000004&t;/* set if vnode is a mountpoint symlink */
multiline_comment|/* outstanding callback notification on this file */
DECL|member|cb_server
id|afs_server_t
op_star
id|cb_server
suffix:semicolon
multiline_comment|/* server that made the current promise */
DECL|member|cb_link
r_struct
id|list_head
id|cb_link
suffix:semicolon
multiline_comment|/* link in server&squot;s promises list */
DECL|member|cb_hash_link
r_struct
id|list_head
id|cb_hash_link
suffix:semicolon
multiline_comment|/* link in master callback hash */
DECL|member|cb_timeout
id|afs_timer_t
id|cb_timeout
suffix:semicolon
multiline_comment|/* timeout on promise */
DECL|member|cb_version
r_int
id|cb_version
suffix:semicolon
multiline_comment|/* callback version */
DECL|member|cb_expiry
r_int
id|cb_expiry
suffix:semicolon
multiline_comment|/* callback expiry time */
DECL|member|cb_type
id|afs_callback_type_t
id|cb_type
suffix:semicolon
multiline_comment|/* type of callback */
)brace
suffix:semicolon
DECL|function|AFS_FS_I
r_static
r_inline
id|afs_vnode_t
op_star
id|AFS_FS_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
id|afs_vnode_t
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|function|AFS_VNODE_TO_I
r_static
r_inline
r_struct
id|inode
op_star
id|AFS_VNODE_TO_I
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
(brace
r_return
op_amp
id|vnode-&gt;vfs_inode
suffix:semicolon
)brace
r_extern
r_int
id|afs_vnode_fetch_status
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
suffix:semicolon
r_extern
r_int
id|afs_vnode_fetch_data
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
comma
r_struct
id|afs_rxfs_fetch_descriptor
op_star
id|desc
)paren
suffix:semicolon
r_extern
r_int
id|afs_vnode_give_up_callback
c_func
(paren
id|afs_vnode_t
op_star
id|vnode
)paren
suffix:semicolon
r_extern
r_struct
id|afs_timer_ops
id|afs_vnode_cb_timed_out_ops
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AFS_VNODE_H */
eof
