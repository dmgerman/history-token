multiline_comment|/* -*- mode: c; c-basic-offset: 8; indent-tabs-mode: nil; -*-&n; * vim:expandtab:shiftwidth=8:tabstop=8:&n; *&n; *  Copyright (C) 2001, 2002 Cluster File Systems, Inc.&n; *  Copyright (C) 2001 Tacit Networks, Inc.&n; *&n; *   This file is part of InterMezzo, http://www.inter-mezzo.org.&n; *&n; *   InterMezzo is free software; you can redistribute it and/or&n; *   modify it under the terms of version 2 of the GNU General Public&n; *   License as published by the Free Software Foundation.&n; *&n; *   InterMezzo is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with InterMezzo; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __INTERMEZZO_IDL_H__
DECL|macro|__INTERMEZZO_IDL_H__
mdefine_line|#define __INTERMEZZO_IDL_H__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* this file contains all data structures used in InterMezzo&squot;s interfaces:&n; * - upcalls&n; * - ioctl&squot;s&n; * - KML records&n; * - RCVD records&n; * - rpc&squot;s&n; */
multiline_comment|/* UPCALL */
DECL|macro|INTERMEZZO_MINOR
mdefine_line|#define INTERMEZZO_MINOR 248   
DECL|macro|IZO_UPC_VERSION
mdefine_line|#define IZO_UPC_VERSION 0x00010002
DECL|macro|IZO_UPC_PERMIT
mdefine_line|#define IZO_UPC_PERMIT        1
DECL|macro|IZO_UPC_CONNECT
mdefine_line|#define IZO_UPC_CONNECT       2
DECL|macro|IZO_UPC_GO_FETCH_KML
mdefine_line|#define IZO_UPC_GO_FETCH_KML  3
DECL|macro|IZO_UPC_OPEN
mdefine_line|#define IZO_UPC_OPEN          4
DECL|macro|IZO_UPC_REVOKE_PERMIT
mdefine_line|#define IZO_UPC_REVOKE_PERMIT 5
DECL|macro|IZO_UPC_KML
mdefine_line|#define IZO_UPC_KML           6
DECL|macro|IZO_UPC_BACKFETCH
mdefine_line|#define IZO_UPC_BACKFETCH     7
DECL|macro|IZO_UPC_KML_TRUNC
mdefine_line|#define IZO_UPC_KML_TRUNC     8
DECL|macro|IZO_UPC_SET_KMLSIZE
mdefine_line|#define IZO_UPC_SET_KMLSIZE   9
DECL|macro|IZO_UPC_BRANCH_UNDO
mdefine_line|#define IZO_UPC_BRANCH_UNDO   10
DECL|macro|IZO_UPC_BRANCH_REDO
mdefine_line|#define IZO_UPC_BRANCH_REDO   11
DECL|macro|IZO_UPC_GET_FILEID
mdefine_line|#define IZO_UPC_GET_FILEID    12
DECL|macro|IZO_UPC_CLIENT_MAKE_BRANCH
mdefine_line|#define IZO_UPC_CLIENT_MAKE_BRANCH    13
DECL|macro|IZO_UPC_SERVER_MAKE_BRANCH
mdefine_line|#define IZO_UPC_SERVER_MAKE_BRANCH    14
DECL|macro|IZO_UPC_REPSTATUS
mdefine_line|#define IZO_UPC_REPSTATUS    15
DECL|macro|IZO_UPC_LARGEST_OPCODE
mdefine_line|#define IZO_UPC_LARGEST_OPCODE 15
DECL|struct|izo_upcall_hdr
r_struct
id|izo_upcall_hdr
(brace
DECL|member|u_len
id|__u32
id|u_len
suffix:semicolon
DECL|member|u_version
id|__u32
id|u_version
suffix:semicolon
DECL|member|u_opc
id|__u32
id|u_opc
suffix:semicolon
DECL|member|u_uniq
id|__u32
id|u_uniq
suffix:semicolon
DECL|member|u_pid
id|__u32
id|u_pid
suffix:semicolon
DECL|member|u_uid
id|__u32
id|u_uid
suffix:semicolon
DECL|member|u_pathlen
id|__u32
id|u_pathlen
suffix:semicolon
DECL|member|u_fsetlen
id|__u32
id|u_fsetlen
suffix:semicolon
DECL|member|u_offset
id|__u64
id|u_offset
suffix:semicolon
DECL|member|u_length
id|__u64
id|u_length
suffix:semicolon
DECL|member|u_first_recno
id|__u32
id|u_first_recno
suffix:semicolon
DECL|member|u_last_recno
id|__u32
id|u_last_recno
suffix:semicolon
DECL|member|u_async
id|__u32
id|u_async
suffix:semicolon
DECL|member|u_reclen
id|__u32
id|u_reclen
suffix:semicolon
DECL|member|u_uuid
id|__u8
id|u_uuid
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This structure _must_ sit at the beginning of the buffer */
DECL|struct|izo_upcall_resp
r_struct
id|izo_upcall_resp
(brace
DECL|member|opcode
id|__u32
id|opcode
suffix:semicolon
DECL|member|unique
id|__u32
id|unique
suffix:semicolon
DECL|member|result
id|__u32
id|result
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* IOCTL */
DECL|macro|IZO_IOCTL_VERSION
mdefine_line|#define IZO_IOCTL_VERSION 0x00010003
multiline_comment|/* maximum size supported for ioc_pbuf1 */
DECL|macro|KML_MAX_BUF
mdefine_line|#define KML_MAX_BUF (64*1024)
DECL|struct|izo_ioctl_hdr
r_struct
id|izo_ioctl_hdr
(brace
DECL|member|ioc_len
id|__u32
id|ioc_len
suffix:semicolon
DECL|member|ioc_version
id|__u32
id|ioc_version
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|izo_ioctl_data
r_struct
id|izo_ioctl_data
(brace
DECL|member|ioc_len
id|__u32
id|ioc_len
suffix:semicolon
DECL|member|ioc_version
id|__u32
id|ioc_version
suffix:semicolon
DECL|member|ioc_izodev
id|__u32
id|ioc_izodev
suffix:semicolon
DECL|member|ioc_kmlrecno
id|__u32
id|ioc_kmlrecno
suffix:semicolon
DECL|member|ioc_kmlsize
id|__u64
id|ioc_kmlsize
suffix:semicolon
DECL|member|ioc_flags
id|__u32
id|ioc_flags
suffix:semicolon
DECL|member|ioc_inofd
id|__s32
id|ioc_inofd
suffix:semicolon
DECL|member|ioc_ino
id|__u64
id|ioc_ino
suffix:semicolon
DECL|member|ioc_generation
id|__u64
id|ioc_generation
suffix:semicolon
DECL|member|ioc_mark_what
id|__u32
id|ioc_mark_what
suffix:semicolon
DECL|member|ioc_and_flag
id|__u32
id|ioc_and_flag
suffix:semicolon
DECL|member|ioc_or_flag
id|__u32
id|ioc_or_flag
suffix:semicolon
DECL|member|ioc_dev
id|__u32
id|ioc_dev
suffix:semicolon
DECL|member|ioc_offset
id|__u32
id|ioc_offset
suffix:semicolon
DECL|member|ioc_slot
id|__u32
id|ioc_slot
suffix:semicolon
DECL|member|ioc_uid
id|__u64
id|ioc_uid
suffix:semicolon
DECL|member|ioc_uuid
id|__u8
id|ioc_uuid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ioc_inllen1
id|__u32
id|ioc_inllen1
suffix:semicolon
multiline_comment|/* path */
DECL|member|ioc_inlbuf1
r_char
op_star
id|ioc_inlbuf1
suffix:semicolon
DECL|member|ioc_inllen2
id|__u32
id|ioc_inllen2
suffix:semicolon
multiline_comment|/* fileset */
DECL|member|ioc_inlbuf2
r_char
op_star
id|ioc_inlbuf2
suffix:semicolon
DECL|member|ioc_plen1
id|__u32
id|ioc_plen1
suffix:semicolon
multiline_comment|/* buffers in user space (KML) */
DECL|member|ioc_pbuf1
r_char
op_star
id|ioc_pbuf1
suffix:semicolon
DECL|member|ioc_plen2
id|__u32
id|ioc_plen2
suffix:semicolon
multiline_comment|/* buffers in user space (KML) */
DECL|member|ioc_pbuf2
r_char
op_star
id|ioc_pbuf2
suffix:semicolon
DECL|member|ioc_bulk
r_char
id|ioc_bulk
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IZO_IOC_DEVICE
mdefine_line|#define IZO_IOC_DEVICE          _IOW (&squot;p&squot;,0x50, void *)
DECL|macro|IZO_IOC_REINTKML
mdefine_line|#define IZO_IOC_REINTKML        _IOW (&squot;p&squot;,0x51, void *)
DECL|macro|IZO_IOC_GET_RCVD
mdefine_line|#define IZO_IOC_GET_RCVD        _IOW (&squot;p&squot;,0x52, void *)
DECL|macro|IZO_IOC_SET_IOCTL_UID
mdefine_line|#define IZO_IOC_SET_IOCTL_UID   _IOW (&squot;p&squot;,0x53, void *)
DECL|macro|IZO_IOC_GET_KML_SIZE
mdefine_line|#define IZO_IOC_GET_KML_SIZE    _IOW (&squot;p&squot;,0x54, void *)
DECL|macro|IZO_IOC_PURGE_FILE_DATA
mdefine_line|#define IZO_IOC_PURGE_FILE_DATA _IOW (&squot;p&squot;,0x55, void *)
DECL|macro|IZO_IOC_CONNECT
mdefine_line|#define IZO_IOC_CONNECT         _IOW (&squot;p&squot;,0x56, void *)
DECL|macro|IZO_IOC_GO_FETCH_KML
mdefine_line|#define IZO_IOC_GO_FETCH_KML    _IOW (&squot;p&squot;,0x57, void *)
DECL|macro|IZO_IOC_MARK
mdefine_line|#define IZO_IOC_MARK            _IOW (&squot;p&squot;,0x58, void *)
DECL|macro|IZO_IOC_CLEAR_FSET
mdefine_line|#define IZO_IOC_CLEAR_FSET      _IOW (&squot;p&squot;,0x59, void *)
DECL|macro|IZO_IOC_CLEAR_ALL_FSETS
mdefine_line|#define IZO_IOC_CLEAR_ALL_FSETS _IOW (&squot;p&squot;,0x60, void *)
DECL|macro|IZO_IOC_SET_FSET
mdefine_line|#define IZO_IOC_SET_FSET        _IOW (&squot;p&squot;,0x61, void *)
DECL|macro|IZO_IOC_REVOKE_PERMIT
mdefine_line|#define IZO_IOC_REVOKE_PERMIT   _IOW (&squot;p&squot;,0x62, void *)
DECL|macro|IZO_IOC_SET_KMLSIZE
mdefine_line|#define IZO_IOC_SET_KMLSIZE     _IOW (&squot;p&squot;,0x63, void *)
DECL|macro|IZO_IOC_CLIENT_MAKE_BRANCH
mdefine_line|#define IZO_IOC_CLIENT_MAKE_BRANCH _IOW (&squot;p&squot;,0x64, void *)
DECL|macro|IZO_IOC_SERVER_MAKE_BRANCH
mdefine_line|#define IZO_IOC_SERVER_MAKE_BRANCH _IOW (&squot;p&squot;,0x65, void *)
DECL|macro|IZO_IOC_BRANCH_UNDO
mdefine_line|#define IZO_IOC_BRANCH_UNDO    _IOW (&squot;p&squot;,0x66, void *)
DECL|macro|IZO_IOC_BRANCH_REDO
mdefine_line|#define IZO_IOC_BRANCH_REDO    _IOW (&squot;p&squot;,0x67, void *)
DECL|macro|IZO_IOC_SET_PID
mdefine_line|#define IZO_IOC_SET_PID        _IOW (&squot;p&squot;,0x68, void *)
DECL|macro|IZO_IOC_SET_CHANNEL
mdefine_line|#define IZO_IOC_SET_CHANNEL    _IOW (&squot;p&squot;,0x69, void *)
DECL|macro|IZO_IOC_GET_CHANNEL
mdefine_line|#define IZO_IOC_GET_CHANNEL    _IOW (&squot;p&squot;,0x70, void *)
DECL|macro|IZO_IOC_GET_FILEID
mdefine_line|#define IZO_IOC_GET_FILEID    _IOW (&squot;p&squot;,0x71, void *)
DECL|macro|IZO_IOC_ADJUST_LML
mdefine_line|#define IZO_IOC_ADJUST_LML    _IOW (&squot;p&squot;,0x72, void *)
DECL|macro|IZO_IOC_SET_FILEID
mdefine_line|#define IZO_IOC_SET_FILEID    _IOW (&squot;p&squot;,0x73, void *)
DECL|macro|IZO_IOC_REPSTATUS
mdefine_line|#define IZO_IOC_REPSTATUS    _IOW (&squot;p&squot;,0x74, void *)
multiline_comment|/* marking flags for fsets */
DECL|macro|FSET_CLIENT_RO
mdefine_line|#define FSET_CLIENT_RO        0x00000001
DECL|macro|FSET_LENTO_RO
mdefine_line|#define FSET_LENTO_RO         0x00000002
DECL|macro|FSET_HASPERMIT
mdefine_line|#define FSET_HASPERMIT        0x00000004 /* we have a permit to WB */
DECL|macro|FSET_INSYNC
mdefine_line|#define FSET_INSYNC           0x00000008 /* this fileset is in sync */
DECL|macro|FSET_PERMIT_WAITING
mdefine_line|#define FSET_PERMIT_WAITING   0x00000010 /* Lento is waiting for permit */
DECL|macro|FSET_STEAL_PERMIT
mdefine_line|#define FSET_STEAL_PERMIT     0x00000020 /* take permit if Lento is dead */
DECL|macro|FSET_JCLOSE_ON_WRITE
mdefine_line|#define FSET_JCLOSE_ON_WRITE  0x00000040 /* Journal closes on writes */
DECL|macro|FSET_DATA_ON_DEMAND
mdefine_line|#define FSET_DATA_ON_DEMAND   0x00000080 /* update data on file_open() */
DECL|macro|FSET_PERMIT_EXCLUSIVE
mdefine_line|#define FSET_PERMIT_EXCLUSIVE 0x00000100 /* only one permitholder allowed */
DECL|macro|FSET_HAS_BRANCHES
mdefine_line|#define FSET_HAS_BRANCHES     0x00000200 /* this fileset contains branches */
DECL|macro|FSET_IS_BRANCH
mdefine_line|#define FSET_IS_BRANCH        0x00000400 /* this fileset is a branch */
DECL|macro|FSET_FLAT_BRANCH
mdefine_line|#define FSET_FLAT_BRANCH      0x00000800 /* this fileset is ROOT with branches */
multiline_comment|/* what to mark indicator (ioctl parameter) */
DECL|macro|MARK_DENTRY
mdefine_line|#define MARK_DENTRY   101
DECL|macro|MARK_FSET
mdefine_line|#define MARK_FSET     102
DECL|macro|MARK_CACHE
mdefine_line|#define MARK_CACHE    103
DECL|macro|MARK_GETFL
mdefine_line|#define MARK_GETFL    104
multiline_comment|/* KML */
DECL|macro|KML_MAJOR_VERSION
mdefine_line|#define KML_MAJOR_VERSION 0x00010000
DECL|macro|KML_MINOR_VERSION
mdefine_line|#define KML_MINOR_VERSION 0x00000002
DECL|macro|KML_OPCODE_NOOP
mdefine_line|#define KML_OPCODE_NOOP          0
DECL|macro|KML_OPCODE_CREATE
mdefine_line|#define KML_OPCODE_CREATE        1
DECL|macro|KML_OPCODE_MKDIR
mdefine_line|#define KML_OPCODE_MKDIR         2
DECL|macro|KML_OPCODE_UNLINK
mdefine_line|#define KML_OPCODE_UNLINK        3
DECL|macro|KML_OPCODE_RMDIR
mdefine_line|#define KML_OPCODE_RMDIR         4
DECL|macro|KML_OPCODE_CLOSE
mdefine_line|#define KML_OPCODE_CLOSE         5
DECL|macro|KML_OPCODE_SYMLINK
mdefine_line|#define KML_OPCODE_SYMLINK       6
DECL|macro|KML_OPCODE_RENAME
mdefine_line|#define KML_OPCODE_RENAME        7
DECL|macro|KML_OPCODE_SETATTR
mdefine_line|#define KML_OPCODE_SETATTR       8
DECL|macro|KML_OPCODE_LINK
mdefine_line|#define KML_OPCODE_LINK          9
DECL|macro|KML_OPCODE_OPEN
mdefine_line|#define KML_OPCODE_OPEN          10
DECL|macro|KML_OPCODE_MKNOD
mdefine_line|#define KML_OPCODE_MKNOD         11
DECL|macro|KML_OPCODE_WRITE
mdefine_line|#define KML_OPCODE_WRITE         12
DECL|macro|KML_OPCODE_RELEASE
mdefine_line|#define KML_OPCODE_RELEASE       13
DECL|macro|KML_OPCODE_TRUNC
mdefine_line|#define KML_OPCODE_TRUNC         14
DECL|macro|KML_OPCODE_SETEXTATTR
mdefine_line|#define KML_OPCODE_SETEXTATTR    15
DECL|macro|KML_OPCODE_DELEXTATTR
mdefine_line|#define KML_OPCODE_DELEXTATTR    16
DECL|macro|KML_OPCODE_KML_TRUNC
mdefine_line|#define KML_OPCODE_KML_TRUNC     17
DECL|macro|KML_OPCODE_GET_FILEID
mdefine_line|#define KML_OPCODE_GET_FILEID    18
DECL|macro|KML_OPCODE_NUM
mdefine_line|#define KML_OPCODE_NUM           19
multiline_comment|/* new stuff */
DECL|struct|presto_version
r_struct
id|presto_version
(brace
DECL|member|pv_mtime_sec
id|__u32
id|pv_mtime_sec
suffix:semicolon
DECL|member|pv_mtime_nsec
id|__u32
id|pv_mtime_nsec
suffix:semicolon
DECL|member|pv_ctime_sec
id|__u32
id|pv_ctime_sec
suffix:semicolon
DECL|member|pv_ctime_nsec
id|__u32
id|pv_ctime_nsec
suffix:semicolon
DECL|member|pv_size
id|__u64
id|pv_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_prefix_hdr
r_struct
id|kml_prefix_hdr
(brace
DECL|member|len
id|__u32
id|len
suffix:semicolon
DECL|member|version
id|__u32
id|version
suffix:semicolon
DECL|member|pid
id|__u32
id|pid
suffix:semicolon
DECL|member|auid
id|__u32
id|auid
suffix:semicolon
DECL|member|fsuid
id|__u32
id|fsuid
suffix:semicolon
DECL|member|fsgid
id|__u32
id|fsgid
suffix:semicolon
DECL|member|opcode
id|__u32
id|opcode
suffix:semicolon
DECL|member|ngroups
id|__u32
id|ngroups
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_prefix
r_struct
id|kml_prefix
(brace
DECL|member|hdr
r_struct
id|kml_prefix_hdr
op_star
id|hdr
suffix:semicolon
DECL|member|groups
id|__u32
op_star
id|groups
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_suffix
r_struct
id|kml_suffix
(brace
DECL|member|prevrec
id|__u32
id|prevrec
suffix:semicolon
DECL|member|recno
id|__u32
id|recno
suffix:semicolon
DECL|member|time
id|__u32
id|time
suffix:semicolon
DECL|member|len
id|__u32
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|kml_rec
r_struct
id|kml_rec
(brace
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|prefix
r_struct
id|kml_prefix
id|prefix
suffix:semicolon
DECL|member|offset
id|__u64
id|offset
suffix:semicolon
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|pathlen
r_int
id|pathlen
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
DECL|member|target
r_char
op_star
id|target
suffix:semicolon
DECL|member|targetlen
r_int
id|targetlen
suffix:semicolon
DECL|member|old_objectv
r_struct
id|presto_version
op_star
id|old_objectv
suffix:semicolon
DECL|member|new_objectv
r_struct
id|presto_version
op_star
id|new_objectv
suffix:semicolon
DECL|member|old_parentv
r_struct
id|presto_version
op_star
id|old_parentv
suffix:semicolon
DECL|member|new_parentv
r_struct
id|presto_version
op_star
id|new_parentv
suffix:semicolon
DECL|member|old_targetv
r_struct
id|presto_version
op_star
id|old_targetv
suffix:semicolon
DECL|member|new_targetv
r_struct
id|presto_version
op_star
id|new_targetv
suffix:semicolon
DECL|member|valid
id|__u32
id|valid
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|uid
id|__u32
id|uid
suffix:semicolon
DECL|member|gid
id|__u32
id|gid
suffix:semicolon
DECL|member|size
id|__u64
id|size
suffix:semicolon
DECL|member|mtime_sec
id|__u32
id|mtime_sec
suffix:semicolon
DECL|member|mtime_nsec
id|__u32
id|mtime_nsec
suffix:semicolon
DECL|member|ctime_sec
id|__u32
id|ctime_sec
suffix:semicolon
DECL|member|ctime_nsec
id|__u32
id|ctime_nsec
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|ino
id|__u32
id|ino
suffix:semicolon
DECL|member|rdev
id|__u32
id|rdev
suffix:semicolon
DECL|member|major
id|__u32
id|major
suffix:semicolon
DECL|member|minor
id|__u32
id|minor
suffix:semicolon
DECL|member|generation
id|__u32
id|generation
suffix:semicolon
DECL|member|old_mode
id|__u32
id|old_mode
suffix:semicolon
DECL|member|old_rdev
id|__u32
id|old_rdev
suffix:semicolon
DECL|member|old_uid
id|__u64
id|old_uid
suffix:semicolon
DECL|member|old_gid
id|__u64
id|old_gid
suffix:semicolon
DECL|member|old_target
r_char
op_star
id|old_target
suffix:semicolon
DECL|member|old_targetlen
r_int
id|old_targetlen
suffix:semicolon
DECL|member|suffix
r_struct
id|kml_suffix
op_star
id|suffix
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* RCVD */
multiline_comment|/* izo_rcvd_rec fills the .intermezzo/fset/last_rcvd file and provides data about&n; * our view of reintegration offsets for a given peer.&n; *&n; * The only exception is the last_rcvd record which has a UUID consisting of all&n; * zeroes; this record&squot;s lr_local_offset field is the logical byte offset of our&n; * KML, which is updated when KML truncation takes place.  All other fields are&n; * reserved. */
multiline_comment|/* XXX - document how clean shutdowns are recorded */
DECL|struct|izo_rcvd_rec
r_struct
id|izo_rcvd_rec
(brace
DECL|member|lr_uuid
id|__u8
id|lr_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* which peer? */
DECL|member|lr_remote_recno
id|__u64
id|lr_remote_recno
suffix:semicolon
multiline_comment|/* last confirmed remote recno  */
DECL|member|lr_remote_offset
id|__u64
id|lr_remote_offset
suffix:semicolon
multiline_comment|/* last confirmed remote offset */
DECL|member|lr_local_recno
id|__u64
id|lr_local_recno
suffix:semicolon
multiline_comment|/* last locally reinted recno   */
DECL|member|lr_local_offset
id|__u64
id|lr_local_offset
suffix:semicolon
multiline_comment|/* last locally reinted offset  */
DECL|member|lr_last_ctime
id|__u64
id|lr_last_ctime
suffix:semicolon
multiline_comment|/* the largest ctime that has reintegrated */
)brace
suffix:semicolon
multiline_comment|/* Cache purge database&n; *&n; * Each DB entry is this structure followed by the path name, no trailing NUL. */
DECL|struct|izo_purge_entry
r_struct
id|izo_purge_entry
(brace
DECL|member|p_atime
id|__u64
id|p_atime
suffix:semicolon
DECL|member|p_pathlen
id|__u32
id|p_pathlen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* RPC */
macro_line|#endif
eof
