multiline_comment|/*&n; *  include/linux/nfs4.h&n; *&n; *  NFSv4 protocol definitions.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
macro_line|#ifndef _LINUX_NFS4_H
DECL|macro|_LINUX_NFS4_H
mdefine_line|#define _LINUX_NFS4_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|NFS4_VERIFIER_SIZE
mdefine_line|#define NFS4_VERIFIER_SIZE&t;8
DECL|macro|NFS4_FHSIZE
mdefine_line|#define NFS4_FHSIZE&t;&t;128
DECL|macro|NFS4_MAXPATHLEN
mdefine_line|#define NFS4_MAXPATHLEN&t;&t;PATH_MAX
DECL|macro|NFS4_MAXNAMLEN
mdefine_line|#define NFS4_MAXNAMLEN&t;&t;NAME_MAX
DECL|macro|NFS4_ACCESS_READ
mdefine_line|#define NFS4_ACCESS_READ        0x0001
DECL|macro|NFS4_ACCESS_LOOKUP
mdefine_line|#define NFS4_ACCESS_LOOKUP      0x0002
DECL|macro|NFS4_ACCESS_MODIFY
mdefine_line|#define NFS4_ACCESS_MODIFY      0x0004
DECL|macro|NFS4_ACCESS_EXTEND
mdefine_line|#define NFS4_ACCESS_EXTEND      0x0008
DECL|macro|NFS4_ACCESS_DELETE
mdefine_line|#define NFS4_ACCESS_DELETE      0x0010
DECL|macro|NFS4_ACCESS_EXECUTE
mdefine_line|#define NFS4_ACCESS_EXECUTE     0x0020
DECL|macro|NFS4_FH_PERISTENT
mdefine_line|#define NFS4_FH_PERISTENT&t;&t;0x0000
DECL|macro|NFS4_FH_NOEXPIRE_WITH_OPEN
mdefine_line|#define NFS4_FH_NOEXPIRE_WITH_OPEN&t;0x0001
DECL|macro|NFS4_FH_VOLATILE_ANY
mdefine_line|#define NFS4_FH_VOLATILE_ANY&t;&t;0x0002
DECL|macro|NFS4_FH_VOL_MIGRATION
mdefine_line|#define NFS4_FH_VOL_MIGRATION&t;&t;0x0004
DECL|macro|NFS4_FH_VOL_RENAME
mdefine_line|#define NFS4_FH_VOL_RENAME&t;&t;0x0008
DECL|macro|NFS4_OPEN_RESULT_CONFIRM
mdefine_line|#define NFS4_OPEN_RESULT_CONFIRM 0x0002
DECL|macro|NFS4_OPEN_RESULT_LOCKTYPE_POSIX
mdefine_line|#define NFS4_OPEN_RESULT_LOCKTYPE_POSIX 0x0004
DECL|macro|NFS4_SHARE_ACCESS_READ
mdefine_line|#define NFS4_SHARE_ACCESS_READ&t;0x0001
DECL|macro|NFS4_SHARE_ACCESS_WRITE
mdefine_line|#define NFS4_SHARE_ACCESS_WRITE&t;0x0002
DECL|macro|NFS4_SHARE_ACCESS_BOTH
mdefine_line|#define NFS4_SHARE_ACCESS_BOTH&t;0x0003
DECL|macro|NFS4_SHARE_DENY_READ
mdefine_line|#define NFS4_SHARE_DENY_READ&t;0x0001
DECL|macro|NFS4_SHARE_DENY_WRITE
mdefine_line|#define NFS4_SHARE_DENY_WRITE&t;0x0002
DECL|macro|NFS4_SHARE_DENY_BOTH
mdefine_line|#define NFS4_SHARE_DENY_BOTH&t;0x0003
DECL|macro|NFS4_SET_TO_SERVER_TIME
mdefine_line|#define NFS4_SET_TO_SERVER_TIME&t;0
DECL|macro|NFS4_SET_TO_CLIENT_TIME
mdefine_line|#define NFS4_SET_TO_CLIENT_TIME&t;1
DECL|macro|NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE
mdefine_line|#define NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE 0
DECL|macro|NFS4_ACE_ACCESS_DENIED_ACE_TYPE
mdefine_line|#define NFS4_ACE_ACCESS_DENIED_ACE_TYPE  1
DECL|macro|NFS4_ACE_SYSTEM_AUDIT_ACE_TYPE
mdefine_line|#define NFS4_ACE_SYSTEM_AUDIT_ACE_TYPE   2
DECL|macro|NFS4_ACE_SYSTEM_ALARM_ACE_TYPE
mdefine_line|#define NFS4_ACE_SYSTEM_ALARM_ACE_TYPE   3
DECL|macro|ACL4_SUPPORT_ALLOW_ACL
mdefine_line|#define ACL4_SUPPORT_ALLOW_ACL 0x01
DECL|macro|ACL4_SUPPORT_DENY_ACL
mdefine_line|#define ACL4_SUPPORT_DENY_ACL  0x02
DECL|macro|ACL4_SUPPORT_AUDIT_ACL
mdefine_line|#define ACL4_SUPPORT_AUDIT_ACL 0x04
DECL|macro|ACL4_SUPPORT_ALARM_ACL
mdefine_line|#define ACL4_SUPPORT_ALARM_ACL 0x08
DECL|macro|NFS4_ACE_FILE_INHERIT_ACE
mdefine_line|#define NFS4_ACE_FILE_INHERIT_ACE             0x00000001
DECL|macro|NFS4_ACE_DIRECTORY_INHERIT_ACE
mdefine_line|#define NFS4_ACE_DIRECTORY_INHERIT_ACE        0x00000002
DECL|macro|NFS4_ACE_NO_PROPAGATE_INHERIT_ACE
mdefine_line|#define NFS4_ACE_NO_PROPAGATE_INHERIT_ACE     0x00000004
DECL|macro|NFS4_ACE_INHERIT_ONLY_ACE
mdefine_line|#define NFS4_ACE_INHERIT_ONLY_ACE             0x00000008
DECL|macro|NFS4_ACE_SUCCESSFUL_ACCESS_ACE_FLAG
mdefine_line|#define NFS4_ACE_SUCCESSFUL_ACCESS_ACE_FLAG   0x00000010
DECL|macro|NFS4_ACE_FAILED_ACCESS_ACE_FLAG
mdefine_line|#define NFS4_ACE_FAILED_ACCESS_ACE_FLAG       0x00000020
DECL|macro|NFS4_ACE_IDENTIFIER_GROUP
mdefine_line|#define NFS4_ACE_IDENTIFIER_GROUP             0x00000040
DECL|macro|NFS4_ACE_OWNER
mdefine_line|#define NFS4_ACE_OWNER                        0x00000080
DECL|macro|NFS4_ACE_GROUP
mdefine_line|#define NFS4_ACE_GROUP                        0x00000100
DECL|macro|NFS4_ACE_EVERYONE
mdefine_line|#define NFS4_ACE_EVERYONE                     0x00000200
DECL|macro|NFS4_ACE_READ_DATA
mdefine_line|#define NFS4_ACE_READ_DATA                    0x00000001
DECL|macro|NFS4_ACE_LIST_DIRECTORY
mdefine_line|#define NFS4_ACE_LIST_DIRECTORY               0x00000001
DECL|macro|NFS4_ACE_WRITE_DATA
mdefine_line|#define NFS4_ACE_WRITE_DATA                   0x00000002
DECL|macro|NFS4_ACE_ADD_FILE
mdefine_line|#define NFS4_ACE_ADD_FILE                     0x00000002
DECL|macro|NFS4_ACE_APPEND_DATA
mdefine_line|#define NFS4_ACE_APPEND_DATA                  0x00000004
DECL|macro|NFS4_ACE_ADD_SUBDIRECTORY
mdefine_line|#define NFS4_ACE_ADD_SUBDIRECTORY             0x00000004
DECL|macro|NFS4_ACE_READ_NAMED_ATTRS
mdefine_line|#define NFS4_ACE_READ_NAMED_ATTRS             0x00000008
DECL|macro|NFS4_ACE_WRITE_NAMED_ATTRS
mdefine_line|#define NFS4_ACE_WRITE_NAMED_ATTRS            0x00000010
DECL|macro|NFS4_ACE_EXECUTE
mdefine_line|#define NFS4_ACE_EXECUTE                      0x00000020
DECL|macro|NFS4_ACE_DELETE_CHILD
mdefine_line|#define NFS4_ACE_DELETE_CHILD                 0x00000040
DECL|macro|NFS4_ACE_READ_ATTRIBUTES
mdefine_line|#define NFS4_ACE_READ_ATTRIBUTES              0x00000080
DECL|macro|NFS4_ACE_WRITE_ATTRIBUTES
mdefine_line|#define NFS4_ACE_WRITE_ATTRIBUTES             0x00000100
DECL|macro|NFS4_ACE_DELETE
mdefine_line|#define NFS4_ACE_DELETE                       0x00010000
DECL|macro|NFS4_ACE_READ_ACL
mdefine_line|#define NFS4_ACE_READ_ACL                     0x00020000
DECL|macro|NFS4_ACE_WRITE_ACL
mdefine_line|#define NFS4_ACE_WRITE_ACL                    0x00040000
DECL|macro|NFS4_ACE_WRITE_OWNER
mdefine_line|#define NFS4_ACE_WRITE_OWNER                  0x00080000
DECL|macro|NFS4_ACE_SYNCHRONIZE
mdefine_line|#define NFS4_ACE_SYNCHRONIZE                  0x00100000
DECL|macro|NFS4_ACE_GENERIC_READ
mdefine_line|#define NFS4_ACE_GENERIC_READ                 0x00120081
DECL|macro|NFS4_ACE_GENERIC_WRITE
mdefine_line|#define NFS4_ACE_GENERIC_WRITE                0x00160106
DECL|macro|NFS4_ACE_GENERIC_EXECUTE
mdefine_line|#define NFS4_ACE_GENERIC_EXECUTE              0x001200A0
DECL|macro|NFS4_ACE_MASK_ALL
mdefine_line|#define NFS4_ACE_MASK_ALL                     0x001F01FF
DECL|enum|nfs4_acl_whotype
r_enum
id|nfs4_acl_whotype
(brace
DECL|enumerator|NFS4_ACL_WHO_NAMED
id|NFS4_ACL_WHO_NAMED
op_assign
l_int|0
comma
DECL|enumerator|NFS4_ACL_WHO_OWNER
id|NFS4_ACL_WHO_OWNER
comma
DECL|enumerator|NFS4_ACL_WHO_GROUP
id|NFS4_ACL_WHO_GROUP
comma
DECL|enumerator|NFS4_ACL_WHO_EVERYONE
id|NFS4_ACL_WHO_EVERYONE
comma
)brace
suffix:semicolon
DECL|struct|nfs4_ace
r_struct
id|nfs4_ace
(brace
DECL|member|type
r_uint32
id|type
suffix:semicolon
DECL|member|flag
r_uint32
id|flag
suffix:semicolon
DECL|member|access_mask
r_uint32
id|access_mask
suffix:semicolon
DECL|member|whotype
r_int
id|whotype
suffix:semicolon
DECL|member|who
id|uid_t
id|who
suffix:semicolon
DECL|member|l_ace
r_struct
id|list_head
id|l_ace
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs4_acl
r_struct
id|nfs4_acl
(brace
DECL|member|naces
r_uint32
id|naces
suffix:semicolon
DECL|member|ace_head
r_struct
id|list_head
id|ace_head
suffix:semicolon
)brace
suffix:semicolon
DECL|member|data
DECL|typedef|nfs4_verifier
r_typedef
r_struct
(brace
r_char
id|data
(braket
id|NFS4_VERIFIER_SIZE
)braket
suffix:semicolon
)brace
id|nfs4_verifier
suffix:semicolon
DECL|member|data
DECL|typedef|nfs4_stateid
r_typedef
r_struct
(brace
r_char
id|data
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|nfs4_stateid
suffix:semicolon
DECL|enum|nfs_opnum4
r_enum
id|nfs_opnum4
(brace
DECL|enumerator|OP_ACCESS
id|OP_ACCESS
op_assign
l_int|3
comma
DECL|enumerator|OP_CLOSE
id|OP_CLOSE
op_assign
l_int|4
comma
DECL|enumerator|OP_COMMIT
id|OP_COMMIT
op_assign
l_int|5
comma
DECL|enumerator|OP_CREATE
id|OP_CREATE
op_assign
l_int|6
comma
DECL|enumerator|OP_DELEGPURGE
id|OP_DELEGPURGE
op_assign
l_int|7
comma
DECL|enumerator|OP_DELEGRETURN
id|OP_DELEGRETURN
op_assign
l_int|8
comma
DECL|enumerator|OP_GETATTR
id|OP_GETATTR
op_assign
l_int|9
comma
DECL|enumerator|OP_GETFH
id|OP_GETFH
op_assign
l_int|10
comma
DECL|enumerator|OP_LINK
id|OP_LINK
op_assign
l_int|11
comma
DECL|enumerator|OP_LOCK
id|OP_LOCK
op_assign
l_int|12
comma
DECL|enumerator|OP_LOCKT
id|OP_LOCKT
op_assign
l_int|13
comma
DECL|enumerator|OP_LOCKU
id|OP_LOCKU
op_assign
l_int|14
comma
DECL|enumerator|OP_LOOKUP
id|OP_LOOKUP
op_assign
l_int|15
comma
DECL|enumerator|OP_LOOKUPP
id|OP_LOOKUPP
op_assign
l_int|16
comma
DECL|enumerator|OP_NVERIFY
id|OP_NVERIFY
op_assign
l_int|17
comma
DECL|enumerator|OP_OPEN
id|OP_OPEN
op_assign
l_int|18
comma
DECL|enumerator|OP_OPENATTR
id|OP_OPENATTR
op_assign
l_int|19
comma
DECL|enumerator|OP_OPEN_CONFIRM
id|OP_OPEN_CONFIRM
op_assign
l_int|20
comma
DECL|enumerator|OP_OPEN_DOWNGRADE
id|OP_OPEN_DOWNGRADE
op_assign
l_int|21
comma
DECL|enumerator|OP_PUTFH
id|OP_PUTFH
op_assign
l_int|22
comma
DECL|enumerator|OP_PUTPUBFH
id|OP_PUTPUBFH
op_assign
l_int|23
comma
DECL|enumerator|OP_PUTROOTFH
id|OP_PUTROOTFH
op_assign
l_int|24
comma
DECL|enumerator|OP_READ
id|OP_READ
op_assign
l_int|25
comma
DECL|enumerator|OP_READDIR
id|OP_READDIR
op_assign
l_int|26
comma
DECL|enumerator|OP_READLINK
id|OP_READLINK
op_assign
l_int|27
comma
DECL|enumerator|OP_REMOVE
id|OP_REMOVE
op_assign
l_int|28
comma
DECL|enumerator|OP_RENAME
id|OP_RENAME
op_assign
l_int|29
comma
DECL|enumerator|OP_RENEW
id|OP_RENEW
op_assign
l_int|30
comma
DECL|enumerator|OP_RESTOREFH
id|OP_RESTOREFH
op_assign
l_int|31
comma
DECL|enumerator|OP_SAVEFH
id|OP_SAVEFH
op_assign
l_int|32
comma
DECL|enumerator|OP_SECINFO
id|OP_SECINFO
op_assign
l_int|33
comma
DECL|enumerator|OP_SETATTR
id|OP_SETATTR
op_assign
l_int|34
comma
DECL|enumerator|OP_SETCLIENTID
id|OP_SETCLIENTID
op_assign
l_int|35
comma
DECL|enumerator|OP_SETCLIENTID_CONFIRM
id|OP_SETCLIENTID_CONFIRM
op_assign
l_int|36
comma
DECL|enumerator|OP_VERIFY
id|OP_VERIFY
op_assign
l_int|37
comma
DECL|enumerator|OP_WRITE
id|OP_WRITE
op_assign
l_int|38
comma
DECL|enumerator|OP_RELEASE_LOCKOWNER
id|OP_RELEASE_LOCKOWNER
op_assign
l_int|39
comma
DECL|enumerator|OP_ILLEGAL
id|OP_ILLEGAL
op_assign
l_int|10044
comma
)brace
suffix:semicolon
DECL|enum|nfsstat4
r_enum
id|nfsstat4
(brace
DECL|enumerator|NFS4_OK
id|NFS4_OK
op_assign
l_int|0
comma
DECL|enumerator|NFS4ERR_PERM
id|NFS4ERR_PERM
op_assign
l_int|1
comma
DECL|enumerator|NFS4ERR_NOENT
id|NFS4ERR_NOENT
op_assign
l_int|2
comma
DECL|enumerator|NFS4ERR_IO
id|NFS4ERR_IO
op_assign
l_int|5
comma
DECL|enumerator|NFS4ERR_NXIO
id|NFS4ERR_NXIO
op_assign
l_int|6
comma
DECL|enumerator|NFS4ERR_ACCESS
id|NFS4ERR_ACCESS
op_assign
l_int|13
comma
DECL|enumerator|NFS4ERR_EXIST
id|NFS4ERR_EXIST
op_assign
l_int|17
comma
DECL|enumerator|NFS4ERR_XDEV
id|NFS4ERR_XDEV
op_assign
l_int|18
comma
multiline_comment|/* Unused/reserved 19 */
DECL|enumerator|NFS4ERR_NOTDIR
id|NFS4ERR_NOTDIR
op_assign
l_int|20
comma
DECL|enumerator|NFS4ERR_ISDIR
id|NFS4ERR_ISDIR
op_assign
l_int|21
comma
DECL|enumerator|NFS4ERR_INVAL
id|NFS4ERR_INVAL
op_assign
l_int|22
comma
DECL|enumerator|NFS4ERR_FBIG
id|NFS4ERR_FBIG
op_assign
l_int|27
comma
DECL|enumerator|NFS4ERR_NOSPC
id|NFS4ERR_NOSPC
op_assign
l_int|28
comma
DECL|enumerator|NFS4ERR_ROFS
id|NFS4ERR_ROFS
op_assign
l_int|30
comma
DECL|enumerator|NFS4ERR_MLINK
id|NFS4ERR_MLINK
op_assign
l_int|31
comma
DECL|enumerator|NFS4ERR_NAMETOOLONG
id|NFS4ERR_NAMETOOLONG
op_assign
l_int|63
comma
DECL|enumerator|NFS4ERR_NOTEMPTY
id|NFS4ERR_NOTEMPTY
op_assign
l_int|66
comma
DECL|enumerator|NFS4ERR_DQUOT
id|NFS4ERR_DQUOT
op_assign
l_int|69
comma
DECL|enumerator|NFS4ERR_STALE
id|NFS4ERR_STALE
op_assign
l_int|70
comma
DECL|enumerator|NFS4ERR_BADHANDLE
id|NFS4ERR_BADHANDLE
op_assign
l_int|10001
comma
DECL|enumerator|NFS4ERR_BAD_COOKIE
id|NFS4ERR_BAD_COOKIE
op_assign
l_int|10003
comma
DECL|enumerator|NFS4ERR_NOTSUPP
id|NFS4ERR_NOTSUPP
op_assign
l_int|10004
comma
DECL|enumerator|NFS4ERR_TOOSMALL
id|NFS4ERR_TOOSMALL
op_assign
l_int|10005
comma
DECL|enumerator|NFS4ERR_SERVERFAULT
id|NFS4ERR_SERVERFAULT
op_assign
l_int|10006
comma
DECL|enumerator|NFS4ERR_BADTYPE
id|NFS4ERR_BADTYPE
op_assign
l_int|10007
comma
DECL|enumerator|NFS4ERR_DELAY
id|NFS4ERR_DELAY
op_assign
l_int|10008
comma
DECL|enumerator|NFS4ERR_SAME
id|NFS4ERR_SAME
op_assign
l_int|10009
comma
DECL|enumerator|NFS4ERR_DENIED
id|NFS4ERR_DENIED
op_assign
l_int|10010
comma
DECL|enumerator|NFS4ERR_EXPIRED
id|NFS4ERR_EXPIRED
op_assign
l_int|10011
comma
DECL|enumerator|NFS4ERR_LOCKED
id|NFS4ERR_LOCKED
op_assign
l_int|10012
comma
DECL|enumerator|NFS4ERR_GRACE
id|NFS4ERR_GRACE
op_assign
l_int|10013
comma
DECL|enumerator|NFS4ERR_FHEXPIRED
id|NFS4ERR_FHEXPIRED
op_assign
l_int|10014
comma
DECL|enumerator|NFS4ERR_SHARE_DENIED
id|NFS4ERR_SHARE_DENIED
op_assign
l_int|10015
comma
DECL|enumerator|NFS4ERR_WRONGSEC
id|NFS4ERR_WRONGSEC
op_assign
l_int|10016
comma
DECL|enumerator|NFS4ERR_CLID_INUSE
id|NFS4ERR_CLID_INUSE
op_assign
l_int|10017
comma
DECL|enumerator|NFS4ERR_RESOURCE
id|NFS4ERR_RESOURCE
op_assign
l_int|10018
comma
DECL|enumerator|NFS4ERR_MOVED
id|NFS4ERR_MOVED
op_assign
l_int|10019
comma
DECL|enumerator|NFS4ERR_NOFILEHANDLE
id|NFS4ERR_NOFILEHANDLE
op_assign
l_int|10020
comma
DECL|enumerator|NFS4ERR_MINOR_VERS_MISMATCH
id|NFS4ERR_MINOR_VERS_MISMATCH
op_assign
l_int|10021
comma
DECL|enumerator|NFS4ERR_STALE_CLIENTID
id|NFS4ERR_STALE_CLIENTID
op_assign
l_int|10022
comma
DECL|enumerator|NFS4ERR_STALE_STATEID
id|NFS4ERR_STALE_STATEID
op_assign
l_int|10023
comma
DECL|enumerator|NFS4ERR_OLD_STATEID
id|NFS4ERR_OLD_STATEID
op_assign
l_int|10024
comma
DECL|enumerator|NFS4ERR_BAD_STATEID
id|NFS4ERR_BAD_STATEID
op_assign
l_int|10025
comma
DECL|enumerator|NFS4ERR_BAD_SEQID
id|NFS4ERR_BAD_SEQID
op_assign
l_int|10026
comma
DECL|enumerator|NFS4ERR_NOT_SAME
id|NFS4ERR_NOT_SAME
op_assign
l_int|10027
comma
DECL|enumerator|NFS4ERR_LOCK_RANGE
id|NFS4ERR_LOCK_RANGE
op_assign
l_int|10028
comma
DECL|enumerator|NFS4ERR_SYMLINK
id|NFS4ERR_SYMLINK
op_assign
l_int|10029
comma
DECL|enumerator|NFS4ERR_RESTOREFH
id|NFS4ERR_RESTOREFH
op_assign
l_int|10030
comma
DECL|enumerator|NFS4ERR_LEASE_MOVED
id|NFS4ERR_LEASE_MOVED
op_assign
l_int|10031
comma
DECL|enumerator|NFS4ERR_ATTRNOTSUPP
id|NFS4ERR_ATTRNOTSUPP
op_assign
l_int|10032
comma
DECL|enumerator|NFS4ERR_NO_GRACE
id|NFS4ERR_NO_GRACE
op_assign
l_int|10033
comma
DECL|enumerator|NFS4ERR_RECLAIM_BAD
id|NFS4ERR_RECLAIM_BAD
op_assign
l_int|10034
comma
DECL|enumerator|NFS4ERR_RECLAIM_CONFLICT
id|NFS4ERR_RECLAIM_CONFLICT
op_assign
l_int|10035
comma
DECL|enumerator|NFS4ERR_BADXDR
id|NFS4ERR_BADXDR
op_assign
l_int|10036
comma
DECL|enumerator|NFS4ERR_LOCKS_HELD
id|NFS4ERR_LOCKS_HELD
op_assign
l_int|10037
comma
DECL|enumerator|NFS4ERR_OPENMODE
id|NFS4ERR_OPENMODE
op_assign
l_int|10038
comma
DECL|enumerator|NFS4ERR_BADOWNER
id|NFS4ERR_BADOWNER
op_assign
l_int|10039
comma
DECL|enumerator|NFS4ERR_BADCHAR
id|NFS4ERR_BADCHAR
op_assign
l_int|10040
comma
DECL|enumerator|NFS4ERR_BADNAME
id|NFS4ERR_BADNAME
op_assign
l_int|10041
comma
DECL|enumerator|NFS4ERR_BAD_RANGE
id|NFS4ERR_BAD_RANGE
op_assign
l_int|10042
comma
DECL|enumerator|NFS4ERR_LOCK_NOTSUPP
id|NFS4ERR_LOCK_NOTSUPP
op_assign
l_int|10043
comma
DECL|enumerator|NFS4ERR_OP_ILLEGAL
id|NFS4ERR_OP_ILLEGAL
op_assign
l_int|10044
comma
DECL|enumerator|NFS4ERR_DEADLOCK
id|NFS4ERR_DEADLOCK
op_assign
l_int|10045
comma
DECL|enumerator|NFS4ERR_FILE_OPEN
id|NFS4ERR_FILE_OPEN
op_assign
l_int|10046
comma
DECL|enumerator|NFS4ERR_ADMIN_REVOKED
id|NFS4ERR_ADMIN_REVOKED
op_assign
l_int|10047
comma
DECL|enumerator|NFS4ERR_CB_PATH_DOWN
id|NFS4ERR_CB_PATH_DOWN
op_assign
l_int|10048
)brace
suffix:semicolon
multiline_comment|/*&n; * Note: NF4BAD is not actually part of the protocol; it is just used&n; * internally by nfsd.&n; */
DECL|enum|nfs_ftype4
r_enum
id|nfs_ftype4
(brace
DECL|enumerator|NF4BAD
id|NF4BAD
op_assign
l_int|0
comma
DECL|enumerator|NF4REG
id|NF4REG
op_assign
l_int|1
comma
multiline_comment|/* Regular File */
DECL|enumerator|NF4DIR
id|NF4DIR
op_assign
l_int|2
comma
multiline_comment|/* Directory */
DECL|enumerator|NF4BLK
id|NF4BLK
op_assign
l_int|3
comma
multiline_comment|/* Special File - block device */
DECL|enumerator|NF4CHR
id|NF4CHR
op_assign
l_int|4
comma
multiline_comment|/* Special File - character device */
DECL|enumerator|NF4LNK
id|NF4LNK
op_assign
l_int|5
comma
multiline_comment|/* Symbolic Link */
DECL|enumerator|NF4SOCK
id|NF4SOCK
op_assign
l_int|6
comma
multiline_comment|/* Special File - socket */
DECL|enumerator|NF4FIFO
id|NF4FIFO
op_assign
l_int|7
comma
multiline_comment|/* Special File - fifo */
DECL|enumerator|NF4ATTRDIR
id|NF4ATTRDIR
op_assign
l_int|8
comma
multiline_comment|/* Attribute Directory */
DECL|enumerator|NF4NAMEDATTR
id|NF4NAMEDATTR
op_assign
l_int|9
multiline_comment|/* Named Attribute */
)brace
suffix:semicolon
DECL|enum|open_claim_type4
r_enum
id|open_claim_type4
(brace
DECL|enumerator|NFS4_OPEN_CLAIM_NULL
id|NFS4_OPEN_CLAIM_NULL
op_assign
l_int|0
comma
DECL|enumerator|NFS4_OPEN_CLAIM_PREVIOUS
id|NFS4_OPEN_CLAIM_PREVIOUS
op_assign
l_int|1
comma
DECL|enumerator|NFS4_OPEN_CLAIM_DELEGATE_CUR
id|NFS4_OPEN_CLAIM_DELEGATE_CUR
op_assign
l_int|2
comma
DECL|enumerator|NFS4_OPEN_CLAIM_DELEGATE_PREV
id|NFS4_OPEN_CLAIM_DELEGATE_PREV
op_assign
l_int|3
)brace
suffix:semicolon
DECL|enum|opentype4
r_enum
id|opentype4
(brace
DECL|enumerator|NFS4_OPEN_NOCREATE
id|NFS4_OPEN_NOCREATE
op_assign
l_int|0
comma
DECL|enumerator|NFS4_OPEN_CREATE
id|NFS4_OPEN_CREATE
op_assign
l_int|1
)brace
suffix:semicolon
DECL|enum|createmode4
r_enum
id|createmode4
(brace
DECL|enumerator|NFS4_CREATE_UNCHECKED
id|NFS4_CREATE_UNCHECKED
op_assign
l_int|0
comma
DECL|enumerator|NFS4_CREATE_GUARDED
id|NFS4_CREATE_GUARDED
op_assign
l_int|1
comma
DECL|enumerator|NFS4_CREATE_EXCLUSIVE
id|NFS4_CREATE_EXCLUSIVE
op_assign
l_int|2
)brace
suffix:semicolon
DECL|enum|limit_by4
r_enum
id|limit_by4
(brace
DECL|enumerator|NFS4_LIMIT_SIZE
id|NFS4_LIMIT_SIZE
op_assign
l_int|1
comma
DECL|enumerator|NFS4_LIMIT_BLOCKS
id|NFS4_LIMIT_BLOCKS
op_assign
l_int|2
)brace
suffix:semicolon
DECL|enum|open_delegation_type4
r_enum
id|open_delegation_type4
(brace
DECL|enumerator|NFS4_OPEN_DELEGATE_NONE
id|NFS4_OPEN_DELEGATE_NONE
op_assign
l_int|0
comma
DECL|enumerator|NFS4_OPEN_DELEGATE_READ
id|NFS4_OPEN_DELEGATE_READ
op_assign
l_int|1
comma
DECL|enumerator|NFS4_OPEN_DELEGATE_WRITE
id|NFS4_OPEN_DELEGATE_WRITE
op_assign
l_int|2
)brace
suffix:semicolon
DECL|enum|lock_type4
r_enum
id|lock_type4
(brace
DECL|enumerator|NFS4_UNLOCK_LT
id|NFS4_UNLOCK_LT
op_assign
l_int|0
comma
DECL|enumerator|NFS4_READ_LT
id|NFS4_READ_LT
op_assign
l_int|1
comma
DECL|enumerator|NFS4_WRITE_LT
id|NFS4_WRITE_LT
op_assign
l_int|2
comma
DECL|enumerator|NFS4_READW_LT
id|NFS4_READW_LT
op_assign
l_int|3
comma
DECL|enumerator|NFS4_WRITEW_LT
id|NFS4_WRITEW_LT
op_assign
l_int|4
)brace
suffix:semicolon
multiline_comment|/* Mandatory Attributes */
DECL|macro|FATTR4_WORD0_SUPPORTED_ATTRS
mdefine_line|#define FATTR4_WORD0_SUPPORTED_ATTRS    (1UL &lt;&lt; 0)
DECL|macro|FATTR4_WORD0_TYPE
mdefine_line|#define FATTR4_WORD0_TYPE               (1UL &lt;&lt; 1)
DECL|macro|FATTR4_WORD0_FH_EXPIRE_TYPE
mdefine_line|#define FATTR4_WORD0_FH_EXPIRE_TYPE     (1UL &lt;&lt; 2)
DECL|macro|FATTR4_WORD0_CHANGE
mdefine_line|#define FATTR4_WORD0_CHANGE             (1UL &lt;&lt; 3)
DECL|macro|FATTR4_WORD0_SIZE
mdefine_line|#define FATTR4_WORD0_SIZE               (1UL &lt;&lt; 4)
DECL|macro|FATTR4_WORD0_LINK_SUPPORT
mdefine_line|#define FATTR4_WORD0_LINK_SUPPORT       (1UL &lt;&lt; 5)
DECL|macro|FATTR4_WORD0_SYMLINK_SUPPORT
mdefine_line|#define FATTR4_WORD0_SYMLINK_SUPPORT    (1UL &lt;&lt; 6)
DECL|macro|FATTR4_WORD0_NAMED_ATTR
mdefine_line|#define FATTR4_WORD0_NAMED_ATTR         (1UL &lt;&lt; 7)
DECL|macro|FATTR4_WORD0_FSID
mdefine_line|#define FATTR4_WORD0_FSID               (1UL &lt;&lt; 8)
DECL|macro|FATTR4_WORD0_UNIQUE_HANDLES
mdefine_line|#define FATTR4_WORD0_UNIQUE_HANDLES     (1UL &lt;&lt; 9)
DECL|macro|FATTR4_WORD0_LEASE_TIME
mdefine_line|#define FATTR4_WORD0_LEASE_TIME         (1UL &lt;&lt; 10)
DECL|macro|FATTR4_WORD0_RDATTR_ERROR
mdefine_line|#define FATTR4_WORD0_RDATTR_ERROR       (1UL &lt;&lt; 11)
multiline_comment|/* Recommended Attributes */
DECL|macro|FATTR4_WORD0_ACL
mdefine_line|#define FATTR4_WORD0_ACL                (1UL &lt;&lt; 12)
DECL|macro|FATTR4_WORD0_ACLSUPPORT
mdefine_line|#define FATTR4_WORD0_ACLSUPPORT         (1UL &lt;&lt; 13)
DECL|macro|FATTR4_WORD0_ARCHIVE
mdefine_line|#define FATTR4_WORD0_ARCHIVE            (1UL &lt;&lt; 14)
DECL|macro|FATTR4_WORD0_CANSETTIME
mdefine_line|#define FATTR4_WORD0_CANSETTIME         (1UL &lt;&lt; 15)
DECL|macro|FATTR4_WORD0_CASE_INSENSITIVE
mdefine_line|#define FATTR4_WORD0_CASE_INSENSITIVE   (1UL &lt;&lt; 16)
DECL|macro|FATTR4_WORD0_CASE_PRESERVING
mdefine_line|#define FATTR4_WORD0_CASE_PRESERVING    (1UL &lt;&lt; 17)
DECL|macro|FATTR4_WORD0_CHOWN_RESTRICTED
mdefine_line|#define FATTR4_WORD0_CHOWN_RESTRICTED   (1UL &lt;&lt; 18)
DECL|macro|FATTR4_WORD0_FILEHANDLE
mdefine_line|#define FATTR4_WORD0_FILEHANDLE         (1UL &lt;&lt; 19)
DECL|macro|FATTR4_WORD0_FILEID
mdefine_line|#define FATTR4_WORD0_FILEID             (1UL &lt;&lt; 20)
DECL|macro|FATTR4_WORD0_FILES_AVAIL
mdefine_line|#define FATTR4_WORD0_FILES_AVAIL        (1UL &lt;&lt; 21)
DECL|macro|FATTR4_WORD0_FILES_FREE
mdefine_line|#define FATTR4_WORD0_FILES_FREE         (1UL &lt;&lt; 22)
DECL|macro|FATTR4_WORD0_FILES_TOTAL
mdefine_line|#define FATTR4_WORD0_FILES_TOTAL        (1UL &lt;&lt; 23)
DECL|macro|FATTR4_WORD0_FS_LOCATIONS
mdefine_line|#define FATTR4_WORD0_FS_LOCATIONS       (1UL &lt;&lt; 24)
DECL|macro|FATTR4_WORD0_HIDDEN
mdefine_line|#define FATTR4_WORD0_HIDDEN             (1UL &lt;&lt; 25)
DECL|macro|FATTR4_WORD0_HOMOGENEOUS
mdefine_line|#define FATTR4_WORD0_HOMOGENEOUS        (1UL &lt;&lt; 26)
DECL|macro|FATTR4_WORD0_MAXFILESIZE
mdefine_line|#define FATTR4_WORD0_MAXFILESIZE        (1UL &lt;&lt; 27)
DECL|macro|FATTR4_WORD0_MAXLINK
mdefine_line|#define FATTR4_WORD0_MAXLINK            (1UL &lt;&lt; 28)
DECL|macro|FATTR4_WORD0_MAXNAME
mdefine_line|#define FATTR4_WORD0_MAXNAME            (1UL &lt;&lt; 29)
DECL|macro|FATTR4_WORD0_MAXREAD
mdefine_line|#define FATTR4_WORD0_MAXREAD            (1UL &lt;&lt; 30)
DECL|macro|FATTR4_WORD0_MAXWRITE
mdefine_line|#define FATTR4_WORD0_MAXWRITE           (1UL &lt;&lt; 31)
DECL|macro|FATTR4_WORD1_MIMETYPE
mdefine_line|#define FATTR4_WORD1_MIMETYPE           (1UL &lt;&lt; 0)
DECL|macro|FATTR4_WORD1_MODE
mdefine_line|#define FATTR4_WORD1_MODE               (1UL &lt;&lt; 1)
DECL|macro|FATTR4_WORD1_NO_TRUNC
mdefine_line|#define FATTR4_WORD1_NO_TRUNC           (1UL &lt;&lt; 2)
DECL|macro|FATTR4_WORD1_NUMLINKS
mdefine_line|#define FATTR4_WORD1_NUMLINKS           (1UL &lt;&lt; 3)
DECL|macro|FATTR4_WORD1_OWNER
mdefine_line|#define FATTR4_WORD1_OWNER              (1UL &lt;&lt; 4)
DECL|macro|FATTR4_WORD1_OWNER_GROUP
mdefine_line|#define FATTR4_WORD1_OWNER_GROUP        (1UL &lt;&lt; 5)
DECL|macro|FATTR4_WORD1_QUOTA_HARD
mdefine_line|#define FATTR4_WORD1_QUOTA_HARD         (1UL &lt;&lt; 6)
DECL|macro|FATTR4_WORD1_QUOTA_SOFT
mdefine_line|#define FATTR4_WORD1_QUOTA_SOFT         (1UL &lt;&lt; 7)
DECL|macro|FATTR4_WORD1_QUOTA_USED
mdefine_line|#define FATTR4_WORD1_QUOTA_USED         (1UL &lt;&lt; 8)
DECL|macro|FATTR4_WORD1_RAWDEV
mdefine_line|#define FATTR4_WORD1_RAWDEV             (1UL &lt;&lt; 9)
DECL|macro|FATTR4_WORD1_SPACE_AVAIL
mdefine_line|#define FATTR4_WORD1_SPACE_AVAIL        (1UL &lt;&lt; 10)
DECL|macro|FATTR4_WORD1_SPACE_FREE
mdefine_line|#define FATTR4_WORD1_SPACE_FREE         (1UL &lt;&lt; 11)
DECL|macro|FATTR4_WORD1_SPACE_TOTAL
mdefine_line|#define FATTR4_WORD1_SPACE_TOTAL        (1UL &lt;&lt; 12)
DECL|macro|FATTR4_WORD1_SPACE_USED
mdefine_line|#define FATTR4_WORD1_SPACE_USED         (1UL &lt;&lt; 13)
DECL|macro|FATTR4_WORD1_SYSTEM
mdefine_line|#define FATTR4_WORD1_SYSTEM             (1UL &lt;&lt; 14)
DECL|macro|FATTR4_WORD1_TIME_ACCESS
mdefine_line|#define FATTR4_WORD1_TIME_ACCESS        (1UL &lt;&lt; 15)
DECL|macro|FATTR4_WORD1_TIME_ACCESS_SET
mdefine_line|#define FATTR4_WORD1_TIME_ACCESS_SET    (1UL &lt;&lt; 16)
DECL|macro|FATTR4_WORD1_TIME_BACKUP
mdefine_line|#define FATTR4_WORD1_TIME_BACKUP        (1UL &lt;&lt; 17)
DECL|macro|FATTR4_WORD1_TIME_CREATE
mdefine_line|#define FATTR4_WORD1_TIME_CREATE        (1UL &lt;&lt; 18)
DECL|macro|FATTR4_WORD1_TIME_DELTA
mdefine_line|#define FATTR4_WORD1_TIME_DELTA         (1UL &lt;&lt; 19)
DECL|macro|FATTR4_WORD1_TIME_METADATA
mdefine_line|#define FATTR4_WORD1_TIME_METADATA      (1UL &lt;&lt; 20)
DECL|macro|FATTR4_WORD1_TIME_MODIFY
mdefine_line|#define FATTR4_WORD1_TIME_MODIFY        (1UL &lt;&lt; 21)
DECL|macro|FATTR4_WORD1_TIME_MODIFY_SET
mdefine_line|#define FATTR4_WORD1_TIME_MODIFY_SET    (1UL &lt;&lt; 22)
DECL|macro|FATTR4_WORD1_MOUNTED_ON_FILEID
mdefine_line|#define FATTR4_WORD1_MOUNTED_ON_FILEID  (1UL &lt;&lt; 23)
DECL|macro|NFSPROC4_NULL
mdefine_line|#define NFSPROC4_NULL 0
DECL|macro|NFSPROC4_COMPOUND
mdefine_line|#define NFSPROC4_COMPOUND 1
DECL|macro|NFS4_MINOR_VERSION
mdefine_line|#define NFS4_MINOR_VERSION 0
DECL|macro|NFS4_DEBUG
mdefine_line|#define NFS4_DEBUG 1
macro_line|#ifdef __KERNEL__
multiline_comment|/* Index of predefined Linux client operations */
r_enum
(brace
DECL|enumerator|NFSPROC4_CLNT_NULL
id|NFSPROC4_CLNT_NULL
op_assign
l_int|0
comma
multiline_comment|/* Unused */
DECL|enumerator|NFSPROC4_CLNT_READ
id|NFSPROC4_CLNT_READ
comma
DECL|enumerator|NFSPROC4_CLNT_WRITE
id|NFSPROC4_CLNT_WRITE
comma
DECL|enumerator|NFSPROC4_CLNT_COMMIT
id|NFSPROC4_CLNT_COMMIT
comma
DECL|enumerator|NFSPROC4_CLNT_OPEN
id|NFSPROC4_CLNT_OPEN
comma
DECL|enumerator|NFSPROC4_CLNT_OPEN_CONFIRM
id|NFSPROC4_CLNT_OPEN_CONFIRM
comma
DECL|enumerator|NFSPROC4_CLNT_OPEN_NOATTR
id|NFSPROC4_CLNT_OPEN_NOATTR
comma
DECL|enumerator|NFSPROC4_CLNT_OPEN_DOWNGRADE
id|NFSPROC4_CLNT_OPEN_DOWNGRADE
comma
DECL|enumerator|NFSPROC4_CLNT_CLOSE
id|NFSPROC4_CLNT_CLOSE
comma
DECL|enumerator|NFSPROC4_CLNT_SETATTR
id|NFSPROC4_CLNT_SETATTR
comma
DECL|enumerator|NFSPROC4_CLNT_FSINFO
id|NFSPROC4_CLNT_FSINFO
comma
DECL|enumerator|NFSPROC4_CLNT_RENEW
id|NFSPROC4_CLNT_RENEW
comma
DECL|enumerator|NFSPROC4_CLNT_SETCLIENTID
id|NFSPROC4_CLNT_SETCLIENTID
comma
DECL|enumerator|NFSPROC4_CLNT_SETCLIENTID_CONFIRM
id|NFSPROC4_CLNT_SETCLIENTID_CONFIRM
comma
DECL|enumerator|NFSPROC4_CLNT_LOCK
id|NFSPROC4_CLNT_LOCK
comma
DECL|enumerator|NFSPROC4_CLNT_LOCKT
id|NFSPROC4_CLNT_LOCKT
comma
DECL|enumerator|NFSPROC4_CLNT_LOCKU
id|NFSPROC4_CLNT_LOCKU
comma
DECL|enumerator|NFSPROC4_CLNT_ACCESS
id|NFSPROC4_CLNT_ACCESS
comma
DECL|enumerator|NFSPROC4_CLNT_GETATTR
id|NFSPROC4_CLNT_GETATTR
comma
DECL|enumerator|NFSPROC4_CLNT_LOOKUP
id|NFSPROC4_CLNT_LOOKUP
comma
DECL|enumerator|NFSPROC4_CLNT_LOOKUP_ROOT
id|NFSPROC4_CLNT_LOOKUP_ROOT
comma
DECL|enumerator|NFSPROC4_CLNT_REMOVE
id|NFSPROC4_CLNT_REMOVE
comma
DECL|enumerator|NFSPROC4_CLNT_RENAME
id|NFSPROC4_CLNT_RENAME
comma
DECL|enumerator|NFSPROC4_CLNT_LINK
id|NFSPROC4_CLNT_LINK
comma
DECL|enumerator|NFSPROC4_CLNT_SYMLINK
id|NFSPROC4_CLNT_SYMLINK
comma
DECL|enumerator|NFSPROC4_CLNT_CREATE
id|NFSPROC4_CLNT_CREATE
comma
DECL|enumerator|NFSPROC4_CLNT_PATHCONF
id|NFSPROC4_CLNT_PATHCONF
comma
DECL|enumerator|NFSPROC4_CLNT_STATFS
id|NFSPROC4_CLNT_STATFS
comma
DECL|enumerator|NFSPROC4_CLNT_READLINK
id|NFSPROC4_CLNT_READLINK
comma
DECL|enumerator|NFSPROC4_CLNT_READDIR
id|NFSPROC4_CLNT_READDIR
comma
DECL|enumerator|NFSPROC4_CLNT_SERVER_CAPS
id|NFSPROC4_CLNT_SERVER_CAPS
comma
DECL|enumerator|NFSPROC4_CLNT_DELEGRETURN
id|NFSPROC4_CLNT_DELEGRETURN
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 8&n; * End:&n; */
eof
