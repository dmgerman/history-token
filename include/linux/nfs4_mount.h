macro_line|#ifndef _LINUX_NFS4_MOUNT_H
DECL|macro|_LINUX_NFS4_MOUNT_H
mdefine_line|#define _LINUX_NFS4_MOUNT_H
multiline_comment|/*&n; *  linux/include/linux/nfs4_mount.h&n; *&n; *  Copyright (C) 2002  Trond Myklebust&n; *&n; *  structure passed from user-space to kernel-space during an nfsv4 mount&n; */
multiline_comment|/*&n; * WARNING!  Do not delete or change the order of these fields.  If&n; * a new field is required then add it to the end.  The version field&n; * tracks which fields are present.  This will ensure some measure of&n; * mount-to-kernel version compatibility.  Some of these aren&squot;t used yet&n; * but here they are anyway.&n; */
DECL|macro|NFS4_MOUNT_VERSION
mdefine_line|#define NFS4_MOUNT_VERSION&t;1
DECL|struct|nfs_string
r_struct
id|nfs_string
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|data
r_const
r_char
id|__user
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs4_mount_data
r_struct
id|nfs4_mount_data
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|rsize
r_int
id|rsize
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|wsize
r_int
id|wsize
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|timeo
r_int
id|timeo
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|retrans
r_int
id|retrans
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acregmin
r_int
id|acregmin
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acregmax
r_int
id|acregmax
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acdirmin
r_int
id|acdirmin
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|acdirmax
r_int
id|acdirmax
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* see the definition of &squot;struct clientaddr4&squot; in RFC3010 */
DECL|member|client_addr
r_struct
id|nfs_string
id|client_addr
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* Mount path */
DECL|member|mnt_path
r_struct
id|nfs_string
id|mnt_path
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* Server details */
DECL|member|hostname
r_struct
id|nfs_string
id|hostname
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* Server IP address */
DECL|member|host_addrlen
r_int
r_int
id|host_addrlen
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|host_addr
r_struct
id|sockaddr
id|__user
op_star
id|host_addr
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* Transport protocol to use */
DECL|member|proto
r_int
id|proto
suffix:semicolon
multiline_comment|/* 1 */
multiline_comment|/* Pseudo-flavours to use for authentication. See RFC2623 */
DECL|member|auth_flavourlen
r_int
id|auth_flavourlen
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|auth_flavours
r_int
id|__user
op_star
id|auth_flavours
suffix:semicolon
multiline_comment|/* 1 */
)brace
suffix:semicolon
multiline_comment|/* bits in the flags field */
multiline_comment|/* Note: the fields that correspond to existing NFSv2/v3 mount options&n; * &t; should mirror the values from include/linux/nfs_mount.h&n; */
DECL|macro|NFS4_MOUNT_SOFT
mdefine_line|#define NFS4_MOUNT_SOFT&t;&t;0x0001&t;/* 1 */
DECL|macro|NFS4_MOUNT_INTR
mdefine_line|#define NFS4_MOUNT_INTR&t;&t;0x0002&t;/* 1 */
DECL|macro|NFS4_MOUNT_NOCTO
mdefine_line|#define NFS4_MOUNT_NOCTO&t;0x0010&t;/* 1 */
DECL|macro|NFS4_MOUNT_NOAC
mdefine_line|#define NFS4_MOUNT_NOAC&t;&t;0x0020&t;/* 1 */
DECL|macro|NFS4_MOUNT_STRICTLOCK
mdefine_line|#define NFS4_MOUNT_STRICTLOCK&t;0x1000&t;/* 1 */
DECL|macro|NFS4_MOUNT_FLAGMASK
mdefine_line|#define NFS4_MOUNT_FLAGMASK&t;0xFFFF
macro_line|#endif
eof
