multiline_comment|/*&n; *  include/linux/nfs4.h&n; *&n; *  NFSv4 protocol definitions.&n; *&n; *  Copyright (c) 2002 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Kendrick Smith &lt;kmsmith@umich.edu&gt;&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
macro_line|#ifndef _LINUX_NFS4_H
DECL|macro|_LINUX_NFS4_H
mdefine_line|#define _LINUX_NFS4_H
DECL|macro|NFS4_VERIFIER_SIZE
mdefine_line|#define NFS4_VERIFIER_SIZE&t;8
DECL|macro|NFS4_FHSIZE
mdefine_line|#define NFS4_FHSIZE&t;&t;128
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
DECL|macro|NFS4_SHARE_ACCESS_READ
mdefine_line|#define NFS4_SHARE_ACCESS_READ&t;0x0001
DECL|macro|NFS4_SHARE_ACCESS_WRITE
mdefine_line|#define NFS4_SHARE_ACCESS_WRITE&t;0x0002
DECL|macro|NFS4_SHARE_ACCESS_BOTH
mdefine_line|#define NFS4_SHARE_ACCESS_BOTH&t;0x0003
DECL|macro|NFS4_SHARE_DENY_READ
mdefine_line|#define NFS4_SHARE_DENY_READ&t;0x0001
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
DECL|typedef|nfs4_verifier
r_typedef
r_char
id|nfs4_verifier
(braket
id|NFS4_VERIFIER_SIZE
)braket
suffix:semicolon
DECL|typedef|nfs4_stateid
r_typedef
r_char
id|nfs4_stateid
(braket
l_int|16
)braket
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
multiline_comment|/* Mandatory Attributes */
DECL|macro|FATTR4_WORD0_SUPPORTED_ATTRS
mdefine_line|#define FATTR4_WORD0_SUPPORTED_ATTRS    (1)
DECL|macro|FATTR4_WORD0_TYPE
mdefine_line|#define FATTR4_WORD0_TYPE               (1 &lt;&lt; 1)
DECL|macro|FATTR4_WORD0_FH_EXPIRE_TYPE
mdefine_line|#define FATTR4_WORD0_FH_EXPIRE_TYPE     (1 &lt;&lt; 2)
DECL|macro|FATTR4_WORD0_CHANGE
mdefine_line|#define FATTR4_WORD0_CHANGE             (1 &lt;&lt; 3)
DECL|macro|FATTR4_WORD0_SIZE
mdefine_line|#define FATTR4_WORD0_SIZE               (1 &lt;&lt; 4)
DECL|macro|FATTR4_WORD0_LINK_SUPPORT
mdefine_line|#define FATTR4_WORD0_LINK_SUPPORT       (1 &lt;&lt; 5)
DECL|macro|FATTR4_WORD0_SYMLINK_SUPPORT
mdefine_line|#define FATTR4_WORD0_SYMLINK_SUPPORT    (1 &lt;&lt; 6)
DECL|macro|FATTR4_WORD0_NAMED_ATTR
mdefine_line|#define FATTR4_WORD0_NAMED_ATTR         (1 &lt;&lt; 7)
DECL|macro|FATTR4_WORD0_FSID
mdefine_line|#define FATTR4_WORD0_FSID               (1 &lt;&lt; 8)
DECL|macro|FATTR4_WORD0_UNIQUE_HANDLES
mdefine_line|#define FATTR4_WORD0_UNIQUE_HANDLES     (1 &lt;&lt; 9)
DECL|macro|FATTR4_WORD0_LEASE_TIME
mdefine_line|#define FATTR4_WORD0_LEASE_TIME         (1 &lt;&lt; 10)
DECL|macro|FATTR4_WORD0_RDATTR_ERROR
mdefine_line|#define FATTR4_WORD0_RDATTR_ERROR       (1 &lt;&lt; 11)
multiline_comment|/* Recommended Attributes */
DECL|macro|FATTR4_WORD0_ACL
mdefine_line|#define FATTR4_WORD0_ACL                (1 &lt;&lt; 12)
DECL|macro|FATTR4_WORD0_ACLSUPPORT
mdefine_line|#define FATTR4_WORD0_ACLSUPPORT         (1 &lt;&lt; 13)
DECL|macro|FATTR4_WORD0_ARCHIVE
mdefine_line|#define FATTR4_WORD0_ARCHIVE            (1 &lt;&lt; 14)
DECL|macro|FATTR4_WORD0_CANSETTIME
mdefine_line|#define FATTR4_WORD0_CANSETTIME         (1 &lt;&lt; 15)
DECL|macro|FATTR4_WORD0_CASE_INSENSITIVE
mdefine_line|#define FATTR4_WORD0_CASE_INSENSITIVE   (1 &lt;&lt; 16)
DECL|macro|FATTR4_WORD0_CASE_PRESERVING
mdefine_line|#define FATTR4_WORD0_CASE_PRESERVING    (1 &lt;&lt; 17)
DECL|macro|FATTR4_WORD0_CHOWN_RESTRICTED
mdefine_line|#define FATTR4_WORD0_CHOWN_RESTRICTED   (1 &lt;&lt; 18)
DECL|macro|FATTR4_WORD0_FILEHANDLE
mdefine_line|#define FATTR4_WORD0_FILEHANDLE         (1 &lt;&lt; 19)
DECL|macro|FATTR4_WORD0_FILEID
mdefine_line|#define FATTR4_WORD0_FILEID             (1 &lt;&lt; 20)
DECL|macro|FATTR4_WORD0_FILES_AVAIL
mdefine_line|#define FATTR4_WORD0_FILES_AVAIL        (1 &lt;&lt; 21)
DECL|macro|FATTR4_WORD0_FILES_FREE
mdefine_line|#define FATTR4_WORD0_FILES_FREE         (1 &lt;&lt; 22)
DECL|macro|FATTR4_WORD0_FILES_TOTAL
mdefine_line|#define FATTR4_WORD0_FILES_TOTAL        (1 &lt;&lt; 23)
DECL|macro|FATTR4_WORD0_FS_LOCATIONS
mdefine_line|#define FATTR4_WORD0_FS_LOCATIONS       (1 &lt;&lt; 24)
DECL|macro|FATTR4_WORD0_HIDDEN
mdefine_line|#define FATTR4_WORD0_HIDDEN             (1 &lt;&lt; 25)
DECL|macro|FATTR4_WORD0_HOMOGENEOUS
mdefine_line|#define FATTR4_WORD0_HOMOGENEOUS        (1 &lt;&lt; 26)
DECL|macro|FATTR4_WORD0_MAXFILESIZE
mdefine_line|#define FATTR4_WORD0_MAXFILESIZE        (1 &lt;&lt; 27)
DECL|macro|FATTR4_WORD0_MAXLINK
mdefine_line|#define FATTR4_WORD0_MAXLINK            (1 &lt;&lt; 28)
DECL|macro|FATTR4_WORD0_MAXNAME
mdefine_line|#define FATTR4_WORD0_MAXNAME            (1 &lt;&lt; 29)
DECL|macro|FATTR4_WORD0_MAXREAD
mdefine_line|#define FATTR4_WORD0_MAXREAD            (1 &lt;&lt; 30)
DECL|macro|FATTR4_WORD0_MAXWRITE
mdefine_line|#define FATTR4_WORD0_MAXWRITE           (1 &lt;&lt; 31)
DECL|macro|FATTR4_WORD1_MIMETYPE
mdefine_line|#define FATTR4_WORD1_MIMETYPE           (1)
DECL|macro|FATTR4_WORD1_MODE
mdefine_line|#define FATTR4_WORD1_MODE               (1 &lt;&lt; 1)
DECL|macro|FATTR4_WORD1_NO_TRUNC
mdefine_line|#define FATTR4_WORD1_NO_TRUNC           (1 &lt;&lt; 2)
DECL|macro|FATTR4_WORD1_NUMLINKS
mdefine_line|#define FATTR4_WORD1_NUMLINKS           (1 &lt;&lt; 3)
DECL|macro|FATTR4_WORD1_OWNER
mdefine_line|#define FATTR4_WORD1_OWNER              (1 &lt;&lt; 4)
DECL|macro|FATTR4_WORD1_OWNER_GROUP
mdefine_line|#define FATTR4_WORD1_OWNER_GROUP        (1 &lt;&lt; 5)
DECL|macro|FATTR4_WORD1_QUOTA_HARD
mdefine_line|#define FATTR4_WORD1_QUOTA_HARD         (1 &lt;&lt; 6)
DECL|macro|FATTR4_WORD1_QUOTA_SOFT
mdefine_line|#define FATTR4_WORD1_QUOTA_SOFT         (1 &lt;&lt; 7)
DECL|macro|FATTR4_WORD1_QUOTA_USED
mdefine_line|#define FATTR4_WORD1_QUOTA_USED         (1 &lt;&lt; 8)
DECL|macro|FATTR4_WORD1_RAWDEV
mdefine_line|#define FATTR4_WORD1_RAWDEV             (1 &lt;&lt; 9)
DECL|macro|FATTR4_WORD1_SPACE_AVAIL
mdefine_line|#define FATTR4_WORD1_SPACE_AVAIL        (1 &lt;&lt; 10)
DECL|macro|FATTR4_WORD1_SPACE_FREE
mdefine_line|#define FATTR4_WORD1_SPACE_FREE         (1 &lt;&lt; 11)
DECL|macro|FATTR4_WORD1_SPACE_TOTAL
mdefine_line|#define FATTR4_WORD1_SPACE_TOTAL        (1 &lt;&lt; 12)
DECL|macro|FATTR4_WORD1_SPACE_USED
mdefine_line|#define FATTR4_WORD1_SPACE_USED         (1 &lt;&lt; 13)
DECL|macro|FATTR4_WORD1_SYSTEM
mdefine_line|#define FATTR4_WORD1_SYSTEM             (1 &lt;&lt; 14)
DECL|macro|FATTR4_WORD1_TIME_ACCESS
mdefine_line|#define FATTR4_WORD1_TIME_ACCESS        (1 &lt;&lt; 15)
DECL|macro|FATTR4_WORD1_TIME_ACCESS_SET
mdefine_line|#define FATTR4_WORD1_TIME_ACCESS_SET    (1 &lt;&lt; 16)
DECL|macro|FATTR4_WORD1_TIME_BACKUP
mdefine_line|#define FATTR4_WORD1_TIME_BACKUP        (1 &lt;&lt; 17)
DECL|macro|FATTR4_WORD1_TIME_CREATE
mdefine_line|#define FATTR4_WORD1_TIME_CREATE        (1 &lt;&lt; 18)
DECL|macro|FATTR4_WORD1_TIME_DELTA
mdefine_line|#define FATTR4_WORD1_TIME_DELTA         (1 &lt;&lt; 19)
DECL|macro|FATTR4_WORD1_TIME_METADATA
mdefine_line|#define FATTR4_WORD1_TIME_METADATA      (1 &lt;&lt; 20)
DECL|macro|FATTR4_WORD1_TIME_MODIFY
mdefine_line|#define FATTR4_WORD1_TIME_MODIFY        (1 &lt;&lt; 21)
DECL|macro|FATTR4_WORD1_TIME_MODIFY_SET
mdefine_line|#define FATTR4_WORD1_TIME_MODIFY_SET    (1 &lt;&lt; 22)
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
DECL|enumerator|NFSPROC4_CLNT_COMPOUND
id|NFSPROC4_CLNT_COMPOUND
comma
multiline_comment|/* Soon to be unused */
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
DECL|enumerator|NFSPROC4_CLNT_CLOSE
id|NFSPROC4_CLNT_CLOSE
comma
DECL|enumerator|NFSPROC4_CLNT_SETATTR
id|NFSPROC4_CLNT_SETATTR
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 8&n; * End:&n; */
eof
