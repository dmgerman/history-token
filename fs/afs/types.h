multiline_comment|/* types.h: AFS types&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_TYPES_H
DECL|macro|_LINUX_AFS_TYPES_H
mdefine_line|#define _LINUX_AFS_TYPES_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#endif /* __KERNEL__ */
DECL|typedef|afs_volid_t
r_typedef
r_int
id|afs_volid_t
suffix:semicolon
DECL|typedef|afs_vnodeid_t
r_typedef
r_int
id|afs_vnodeid_t
suffix:semicolon
DECL|typedef|afs_dataversion_t
r_typedef
r_int
r_int
r_int
id|afs_dataversion_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AFSVL_RWVOL
id|AFSVL_RWVOL
comma
multiline_comment|/* read/write volume */
DECL|enumerator|AFSVL_ROVOL
id|AFSVL_ROVOL
comma
multiline_comment|/* read-only volume */
DECL|enumerator|AFSVL_BACKVOL
id|AFSVL_BACKVOL
comma
multiline_comment|/* backup volume */
DECL|typedef|afs_voltype_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|afs_voltype_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AFS_FTYPE_INVALID
id|AFS_FTYPE_INVALID
op_assign
l_int|0
comma
DECL|enumerator|AFS_FTYPE_FILE
id|AFS_FTYPE_FILE
op_assign
l_int|1
comma
DECL|enumerator|AFS_FTYPE_DIR
id|AFS_FTYPE_DIR
op_assign
l_int|2
comma
DECL|enumerator|AFS_FTYPE_SYMLINK
id|AFS_FTYPE_SYMLINK
op_assign
l_int|3
comma
DECL|typedef|afs_file_type_t
)brace
id|afs_file_type_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_struct
id|afs_cell
suffix:semicolon
r_struct
id|afs_vnode
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS file identifier&n; */
DECL|struct|afs_fid
r_struct
id|afs_fid
(brace
DECL|member|vid
id|afs_volid_t
id|vid
suffix:semicolon
multiline_comment|/* volume ID */
DECL|member|vnode
id|afs_vnodeid_t
id|vnode
suffix:semicolon
multiline_comment|/* file index within volume */
DECL|member|unique
r_int
id|unique
suffix:semicolon
multiline_comment|/* unique ID number (file index version) */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS callback notification&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AFSCM_CB_UNTYPED
id|AFSCM_CB_UNTYPED
op_assign
l_int|0
comma
multiline_comment|/* no type set on CB break */
DECL|enumerator|AFSCM_CB_EXCLUSIVE
id|AFSCM_CB_EXCLUSIVE
op_assign
l_int|1
comma
multiline_comment|/* CB exclusive to CM [not implemented] */
DECL|enumerator|AFSCM_CB_SHARED
id|AFSCM_CB_SHARED
op_assign
l_int|2
comma
multiline_comment|/* CB shared by other CM&squot;s */
DECL|enumerator|AFSCM_CB_DROPPED
id|AFSCM_CB_DROPPED
op_assign
l_int|3
comma
multiline_comment|/* CB promise cancelled by file server */
DECL|typedef|afs_callback_type_t
)brace
id|afs_callback_type_t
suffix:semicolon
DECL|struct|afs_callback
r_struct
id|afs_callback
(brace
DECL|member|server
r_struct
id|afs_server
op_star
id|server
suffix:semicolon
multiline_comment|/* server that made the promise */
DECL|member|fid
r_struct
id|afs_fid
id|fid
suffix:semicolon
multiline_comment|/* file identifier */
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* callback version */
DECL|member|expiry
r_int
id|expiry
suffix:semicolon
multiline_comment|/* time at which expires */
DECL|member|type
id|afs_callback_type_t
id|type
suffix:semicolon
multiline_comment|/* type of callback */
)brace
suffix:semicolon
DECL|macro|AFSCBMAX
mdefine_line|#define AFSCBMAX 50
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS volume information&n; */
DECL|struct|afs_volume_info
r_struct
id|afs_volume_info
(brace
DECL|member|vid
id|afs_volid_t
id|vid
suffix:semicolon
multiline_comment|/* volume ID */
DECL|member|type
id|afs_voltype_t
id|type
suffix:semicolon
multiline_comment|/* type of this volume */
DECL|member|type_vids
id|afs_volid_t
id|type_vids
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* volume ID&squot;s for possible types for this vol */
multiline_comment|/* list of fileservers serving this volume */
DECL|member|nservers
r_int
id|nservers
suffix:semicolon
multiline_comment|/* number of entries used in servers[] */
r_struct
(brace
DECL|member|addr
r_struct
id|in_addr
id|addr
suffix:semicolon
multiline_comment|/* fileserver address */
DECL|member|servers
)brace
id|servers
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS file status information&n; */
DECL|struct|afs_file_status
r_struct
id|afs_file_status
(brace
DECL|member|if_version
r_int
id|if_version
suffix:semicolon
multiline_comment|/* interface version */
DECL|macro|AFS_FSTATUS_VERSION
mdefine_line|#define AFS_FSTATUS_VERSION&t;1
DECL|member|type
id|afs_file_type_t
id|type
suffix:semicolon
multiline_comment|/* file type */
DECL|member|nlink
r_int
id|nlink
suffix:semicolon
multiline_comment|/* link count */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* file size */
DECL|member|version
id|afs_dataversion_t
id|version
suffix:semicolon
multiline_comment|/* current data version */
DECL|member|author
r_int
id|author
suffix:semicolon
multiline_comment|/* author ID */
DECL|member|owner
r_int
id|owner
suffix:semicolon
multiline_comment|/* owner ID */
DECL|member|caller_access
r_int
id|caller_access
suffix:semicolon
multiline_comment|/* access rights for authenticated caller */
DECL|member|anon_access
r_int
id|anon_access
suffix:semicolon
multiline_comment|/* access rights for unauthenticated caller */
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
multiline_comment|/* UNIX mode */
DECL|member|parent
r_struct
id|afs_fid
id|parent
suffix:semicolon
multiline_comment|/* parent file ID */
DECL|member|mtime_client
id|time_t
id|mtime_client
suffix:semicolon
multiline_comment|/* last time client changed data */
DECL|member|mtime_server
id|time_t
id|mtime_server
suffix:semicolon
multiline_comment|/* last time server changed data */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * AFS volume synchronisation information&n; */
DECL|struct|afs_volsync
r_struct
id|afs_volsync
(brace
DECL|member|creation
id|time_t
id|creation
suffix:semicolon
multiline_comment|/* volume creation time */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AFS_TYPES_H */
eof
