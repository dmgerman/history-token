multiline_comment|/*&n; *   fs/cifs/cifspdu.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#ifndef _CIFSPDU_H
DECL|macro|_CIFSPDU_H
mdefine_line|#define _CIFSPDU_H
macro_line|#include &lt;net/sock.h&gt;
DECL|macro|CIFS_PROT
mdefine_line|#define CIFS_PROT   0
DECL|macro|BAD_PROT
mdefine_line|#define BAD_PROT    CIFS_PROT+1
multiline_comment|/* SMB command codes */
multiline_comment|/* Some commands have minimal (wct=0,bcc=0), or uninteresting, responses&n; (ie which include no useful data other than the SMB error code itself).&n; Knowing this helps avoid response buffer allocations and copy in some cases */
DECL|macro|SMB_COM_CREATE_DIRECTORY
mdefine_line|#define SMB_COM_CREATE_DIRECTORY      0x00 /* trivial response */
DECL|macro|SMB_COM_DELETE_DIRECTORY
mdefine_line|#define SMB_COM_DELETE_DIRECTORY      0x01 /* trivial response */
DECL|macro|SMB_COM_CLOSE
mdefine_line|#define SMB_COM_CLOSE                 0x04 /* triv req/rsp, timestamp ignored */
DECL|macro|SMB_COM_DELETE
mdefine_line|#define SMB_COM_DELETE                0x06 /* trivial response */
DECL|macro|SMB_COM_RENAME
mdefine_line|#define SMB_COM_RENAME                0x07 /* trivial response */
DECL|macro|SMB_COM_LOCKING_ANDX
mdefine_line|#define SMB_COM_LOCKING_ANDX          0x24 /* trivial response */
DECL|macro|SMB_COM_COPY
mdefine_line|#define SMB_COM_COPY                  0x29 /* trivial rsp, fail filename ignrd*/
DECL|macro|SMB_COM_READ_ANDX
mdefine_line|#define SMB_COM_READ_ANDX             0x2E
DECL|macro|SMB_COM_WRITE_ANDX
mdefine_line|#define SMB_COM_WRITE_ANDX            0x2F
DECL|macro|SMB_COM_TRANSACTION2
mdefine_line|#define SMB_COM_TRANSACTION2          0x32
DECL|macro|SMB_COM_TRANSACTION2_SECONDARY
mdefine_line|#define SMB_COM_TRANSACTION2_SECONDARY 0x33
DECL|macro|SMB_COM_FIND_CLOSE2
mdefine_line|#define SMB_COM_FIND_CLOSE2           0x34 /* trivial response */
DECL|macro|SMB_COM_TREE_DISCONNECT
mdefine_line|#define SMB_COM_TREE_DISCONNECT       0x71 /* trivial response */
DECL|macro|SMB_COM_NEGOTIATE
mdefine_line|#define SMB_COM_NEGOTIATE             0x72
DECL|macro|SMB_COM_SESSION_SETUP_ANDX
mdefine_line|#define SMB_COM_SESSION_SETUP_ANDX    0x73
DECL|macro|SMB_COM_LOGOFF_ANDX
mdefine_line|#define SMB_COM_LOGOFF_ANDX           0x74 /* trivial response */
DECL|macro|SMB_COM_TREE_CONNECT_ANDX
mdefine_line|#define SMB_COM_TREE_CONNECT_ANDX     0x75
DECL|macro|SMB_COM_NT_TRANSACT
mdefine_line|#define SMB_COM_NT_TRANSACT           0xA0
DECL|macro|SMB_COM_NT_TRANSACT_SECONDARY
mdefine_line|#define SMB_COM_NT_TRANSACT_SECONDARY 0xA1
DECL|macro|SMB_COM_NT_CREATE_ANDX
mdefine_line|#define SMB_COM_NT_CREATE_ANDX        0xA2
DECL|macro|SMB_COM_NT_RENAME
mdefine_line|#define SMB_COM_NT_RENAME             0xA5 /* trivial response */
multiline_comment|/* Transact2 subcommand codes */
DECL|macro|TRANS2_OPEN
mdefine_line|#define TRANS2_OPEN                   0x00
DECL|macro|TRANS2_FIND_FIRST
mdefine_line|#define TRANS2_FIND_FIRST             0x01
DECL|macro|TRANS2_FIND_NEXT
mdefine_line|#define TRANS2_FIND_NEXT              0x02
DECL|macro|TRANS2_QUERY_FS_INFORMATION
mdefine_line|#define TRANS2_QUERY_FS_INFORMATION   0x03
DECL|macro|TRANS2_QUERY_PATH_INFORMATION
mdefine_line|#define TRANS2_QUERY_PATH_INFORMATION 0x05
DECL|macro|TRANS2_SET_PATH_INFORMATION
mdefine_line|#define TRANS2_SET_PATH_INFORMATION   0x06
DECL|macro|TRANS2_QUERY_FILE_INFORMATION
mdefine_line|#define TRANS2_QUERY_FILE_INFORMATION 0x07
DECL|macro|TRANS2_SET_FILE_INFORMATION
mdefine_line|#define TRANS2_SET_FILE_INFORMATION   0x08
DECL|macro|TRANS2_GET_DFS_REFERRAL
mdefine_line|#define TRANS2_GET_DFS_REFERRAL       0x10
DECL|macro|TRANS2_REPORT_DFS_INCOSISTENCY
mdefine_line|#define TRANS2_REPORT_DFS_INCOSISTENCY 0x11
multiline_comment|/* NT Transact subcommand codes */
DECL|macro|NT_TRANSACT_CREATE
mdefine_line|#define NT_TRANSACT_CREATE            0x01
DECL|macro|NT_TRANSACT_IOCTL
mdefine_line|#define NT_TRANSACT_IOCTL             0x02
DECL|macro|NT_TRANSACT_SET_SECURITY_DESC
mdefine_line|#define NT_TRANSACT_SET_SECURITY_DESC 0x03
DECL|macro|NT_TRANSACT_NOTIFY_CHANGE
mdefine_line|#define NT_TRANSACT_NOTIFY_CHANGE     0x04
DECL|macro|NT_TRANSACT_RENAME
mdefine_line|#define NT_TRANSACT_RENAME            0x05
DECL|macro|NT_TRANSACT_QUERY_SECURITY_DESC
mdefine_line|#define NT_TRANSACT_QUERY_SECURITY_DESC 0x06
DECL|macro|NT_TRANSACT_GET_USER_QUOTA
mdefine_line|#define NT_TRANSACT_GET_USER_QUOTA    0x07
DECL|macro|NT_TRANSACT_SET_USER_QUOTA
mdefine_line|#define NT_TRANSACT_SET_USER_QUOTA    0x08
DECL|macro|MAX_CIFS_HDR_SIZE
mdefine_line|#define MAX_CIFS_HDR_SIZE 256&t;/* chained NTCreateXReadX will probably be biggest */
multiline_comment|/* internal cifs vfs structures */
multiline_comment|/*****************************************************************&n; * All constants go here&n; *****************************************************************&n; */
multiline_comment|/*&n; * Starting value for maximum SMB size negotiation&n; */
DECL|macro|CIFS_MAX_MSGSIZE
mdefine_line|#define CIFS_MAX_MSGSIZE (4*4096)
multiline_comment|/*&n; * Size of encrypted user password in bytes&n; */
DECL|macro|CIFS_ENCPWD_SIZE
mdefine_line|#define CIFS_ENCPWD_SIZE (16)
multiline_comment|/*&n; * Size of the crypto key returned on the negotiate SMB in bytes&n; */
DECL|macro|CIFS_CRYPTO_KEY_SIZE
mdefine_line|#define CIFS_CRYPTO_KEY_SIZE (8)
multiline_comment|/*&n; * Size of the session key (crypto key encrypted with the password&n; */
DECL|macro|CIFS_SESSION_KEY_SIZE
mdefine_line|#define CIFS_SESSION_KEY_SIZE (24)
multiline_comment|/*&n; * Maximum user name length&n; */
DECL|macro|CIFS_UNLEN
mdefine_line|#define CIFS_UNLEN (20)
multiline_comment|/*&n; * Flags on SMB open&n; */
DECL|macro|SMBOPEN_WRITE_THROUGH
mdefine_line|#define SMBOPEN_WRITE_THROUGH 0x4000
DECL|macro|SMBOPEN_DENY_ALL
mdefine_line|#define SMBOPEN_DENY_ALL      0x0010
DECL|macro|SMBOPEN_DENY_WRITE
mdefine_line|#define SMBOPEN_DENY_WRITE    0x0020
DECL|macro|SMBOPEN_DENY_READ
mdefine_line|#define SMBOPEN_DENY_READ     0x0030
DECL|macro|SMBOPEN_DENY_NONE
mdefine_line|#define SMBOPEN_DENY_NONE     0x0040
DECL|macro|SMBOPEN_READ
mdefine_line|#define SMBOPEN_READ          0x0000
DECL|macro|SMBOPEN_WRITE
mdefine_line|#define SMBOPEN_WRITE         0x0001
DECL|macro|SMBOPEN_READWRITE
mdefine_line|#define SMBOPEN_READWRITE     0x0002
DECL|macro|SMBOPEN_EXECUTE
mdefine_line|#define SMBOPEN_EXECUTE       0x0003
DECL|macro|SMBOPEN_OCREATE
mdefine_line|#define SMBOPEN_OCREATE       0x0010
DECL|macro|SMBOPEN_OTRUNC
mdefine_line|#define SMBOPEN_OTRUNC        0x0002
DECL|macro|SMBOPEN_OAPPEND
mdefine_line|#define SMBOPEN_OAPPEND       0x0001
multiline_comment|/*&n; * SMB flag definitions &n; */
DECL|macro|SMBFLG_EXTD_LOCK
mdefine_line|#define SMBFLG_EXTD_LOCK 0x01&t;/* server supports lock-read write-unlock primitives */
DECL|macro|SMBFLG_RCV_POSTED
mdefine_line|#define SMBFLG_RCV_POSTED 0x02&t;/* obsolete */
DECL|macro|SMBFLG_RSVD
mdefine_line|#define SMBFLG_RSVD 0x04
DECL|macro|SMBFLG_CASELESS
mdefine_line|#define SMBFLG_CASELESS 0x08&t;/* all pathnames treated as caseless (off implies case sensitive file handling requested) */
DECL|macro|SMBFLG_CANONICAL_PATH_FORMAT
mdefine_line|#define SMBFLG_CANONICAL_PATH_FORMAT 0x10&t;/* obsolete */
DECL|macro|SMBFLG_OLD_OPLOCK
mdefine_line|#define SMBFLG_OLD_OPLOCK 0x20&t;/* obsolete */
DECL|macro|SMBFLG_OLD_OPLOCK_NOTIFY
mdefine_line|#define SMBFLG_OLD_OPLOCK_NOTIFY 0x40&t;/* obsolete */
DECL|macro|SMBFLG_RESPONSE
mdefine_line|#define SMBFLG_RESPONSE 0x80&t;/* this PDU is a response from server */
multiline_comment|/*&n; * SMB flag2 definitions &n; */
DECL|macro|SMBFLG2_KNOWS_LONG_NAMES
mdefine_line|#define SMBFLG2_KNOWS_LONG_NAMES cpu_to_le16(1)&t;/* can send long (non-8.3) path names in response */
DECL|macro|SMBFLG2_KNOWS_EAS
mdefine_line|#define SMBFLG2_KNOWS_EAS cpu_to_le16(2)
DECL|macro|SMBFLG2_SECURITY_SIGNATURE
mdefine_line|#define SMBFLG2_SECURITY_SIGNATURE cpu_to_le16(4)
DECL|macro|SMBFLG2_IS_LONG_NAME
mdefine_line|#define SMBFLG2_IS_LONG_NAME cpu_to_le16(0x40)
DECL|macro|SMBFLG2_EXT_SEC
mdefine_line|#define SMBFLG2_EXT_SEC cpu_to_le16(0x80)
DECL|macro|SMBFLG2_DFS
mdefine_line|#define SMBFLG2_DFS cpu_to_le16(0x1000)
DECL|macro|SMBFLG2_PAGING_IO
mdefine_line|#define SMBFLG2_PAGING_IO cpu_to_le16(0x2000)
DECL|macro|SMBFLG2_ERR_STATUS
mdefine_line|#define SMBFLG2_ERR_STATUS cpu_to_le16(0x4000)
DECL|macro|SMBFLG2_UNICODE
mdefine_line|#define SMBFLG2_UNICODE cpu_to_le16(0x8000)
multiline_comment|/*&n; * These are the file access permission bits defined in CIFS for the&n; * NTCreateAndX as well as the level 0x107&n; * TRANS2_QUERY_PATH_INFORMATION API.  The level 0x107, SMB_QUERY_FILE_ALL_INFO&n; * responds with the AccessFlags.&n; * The AccessFlags specifies the access permissions a caller has to the&n; * file and can have any suitable combination of the following values:&n; */
DECL|macro|FILE_READ_DATA
mdefine_line|#define FILE_READ_DATA        0x00000001&t;/* Data can be read from the file   */
DECL|macro|FILE_WRITE_DATA
mdefine_line|#define FILE_WRITE_DATA       0x00000002&t;/* Data can be written to the file  */
DECL|macro|FILE_APPEND_DATA
mdefine_line|#define FILE_APPEND_DATA      0x00000004&t;/* Data can be appended to the file */
DECL|macro|FILE_READ_EA
mdefine_line|#define FILE_READ_EA          0x00000008&t;/* Extended attributes associated   */
multiline_comment|/* with the file can be read        */
DECL|macro|FILE_WRITE_EA
mdefine_line|#define FILE_WRITE_EA         0x00000010&t;/* Extended attributes associated   */
multiline_comment|/* with the file can be written     */
DECL|macro|FILE_EXECUTE
mdefine_line|#define FILE_EXECUTE          0x00000020&t;/*Data can be read into memory from */
multiline_comment|/* the file using system paging I/O */
DECL|macro|FILE_DELETE_CHILD
mdefine_line|#define FILE_DELETE_CHILD     0x00000040
DECL|macro|FILE_READ_ATTRIBUTES
mdefine_line|#define FILE_READ_ATTRIBUTES  0x00000080&t;/* Attributes associated with the   */
multiline_comment|/* file can be read                 */
DECL|macro|FILE_WRITE_ATTRIBUTES
mdefine_line|#define FILE_WRITE_ATTRIBUTES 0x00000100&t;/* Attributes associated with the   */
multiline_comment|/* file can be written              */
DECL|macro|DELETE
mdefine_line|#define DELETE                0x00010000&t;/* The file can be deleted          */
DECL|macro|READ_CONTROL
mdefine_line|#define READ_CONTROL          0x00020000&t;/* The access control list and      */
multiline_comment|/* ownership associated with the    */
multiline_comment|/* file can be read                 */
DECL|macro|WRITE_DAC
mdefine_line|#define WRITE_DAC             0x00040000&t;/* The access control list and      */
multiline_comment|/* ownership associated with the    */
multiline_comment|/* file can be written.             */
DECL|macro|WRITE_OWNER
mdefine_line|#define WRITE_OWNER           0x00080000&t;/* Ownership information associated */
multiline_comment|/* with the file can be written     */
DECL|macro|SYNCHRONIZE
mdefine_line|#define SYNCHRONIZE           0x00100000&t;/* The file handle can waited on to */
multiline_comment|/* synchronize with the completion  */
multiline_comment|/* of an input/output request       */
DECL|macro|GENERIC_ALL
mdefine_line|#define GENERIC_ALL           0x10000000
DECL|macro|GENERIC_EXECUTE
mdefine_line|#define GENERIC_EXECUTE       0x20000000
DECL|macro|GENERIC_WRITE
mdefine_line|#define GENERIC_WRITE         0x40000000
DECL|macro|GENERIC_READ
mdefine_line|#define GENERIC_READ          0x80000000
multiline_comment|/* In summary - Relevant file       */
multiline_comment|/* access flags from CIFS are       */
multiline_comment|/* file_read_data, file_write_data  */
multiline_comment|/* file_execute, file_read_attributes */
multiline_comment|/* write_dac, and delete.           */
multiline_comment|/*&n; * Invalid readdir handle&n; */
DECL|macro|CIFS_NO_HANDLE
mdefine_line|#define CIFS_NO_HANDLE        0xFFFF
multiline_comment|/* IPC$ in ASCII */
DECL|macro|CIFS_IPC_RESOURCE
mdefine_line|#define CIFS_IPC_RESOURCE &quot;&bslash;x49&bslash;x50&bslash;x43&bslash;x24&quot;
multiline_comment|/* IPC$ in Unicode */
DECL|macro|CIFS_IPC_UNICODE_RESOURCE
mdefine_line|#define CIFS_IPC_UNICODE_RESOURCE &quot;&bslash;x00&bslash;x49&bslash;x00&bslash;x50&bslash;x00&bslash;x43&bslash;x00&bslash;x24&bslash;x00&bslash;x00&quot;
multiline_comment|/* Unicode Null terminate 2 bytes of 0 */
DECL|macro|UNICODE_NULL
mdefine_line|#define UNICODE_NULL &quot;&bslash;x00&bslash;x00&quot;
DECL|macro|ASCII_NULL
mdefine_line|#define ASCII_NULL 0x00
multiline_comment|/*&n; * Server type values (returned on EnumServer API&n; */
DECL|macro|CIFS_SV_TYPE_DC
mdefine_line|#define CIFS_SV_TYPE_DC     0x00000008
DECL|macro|CIFS_SV_TYPE_BACKDC
mdefine_line|#define CIFS_SV_TYPE_BACKDC 0x00000010
multiline_comment|/*&n; * Alias type flags (From EnumAlias API call&n; */
DECL|macro|CIFS_ALIAS_TYPE_FILE
mdefine_line|#define CIFS_ALIAS_TYPE_FILE 0x0001
DECL|macro|CIFS_SHARE_TYPE_FILE
mdefine_line|#define CIFS_SHARE_TYPE_FILE 0x0000
multiline_comment|/*&n; * File Attribute flags&n; */
DECL|macro|ATTR_READONLY
mdefine_line|#define ATTR_READONLY  0x0001
DECL|macro|ATTR_HIDDEN
mdefine_line|#define ATTR_HIDDEN    0x0002
DECL|macro|ATTR_SYSTEM
mdefine_line|#define ATTR_SYSTEM    0x0004
DECL|macro|ATTR_VOLUME
mdefine_line|#define ATTR_VOLUME    0x0008
DECL|macro|ATTR_DIRECTORY
mdefine_line|#define ATTR_DIRECTORY 0x0010
DECL|macro|ATTR_ARCHIVE
mdefine_line|#define ATTR_ARCHIVE   0x0020
DECL|macro|ATTR_DEVICE
mdefine_line|#define ATTR_DEVICE    0x0040
DECL|macro|ATTR_NORMAL
mdefine_line|#define ATTR_NORMAL    0x0080
DECL|macro|ATTR_TEMPORARY
mdefine_line|#define ATTR_TEMPORARY 0x0100
DECL|macro|ATTR_SPARSE
mdefine_line|#define ATTR_SPARSE    0x0200
DECL|macro|ATTR_REPARSE
mdefine_line|#define ATTR_REPARSE   0x0400
DECL|macro|ATTR_COMPRESSED
mdefine_line|#define ATTR_COMPRESSED 0x0800
DECL|macro|ATTR_OFFLINE
mdefine_line|#define ATTR_OFFLINE    0x1000&t;/* ie file not immediately available - offline storage */
DECL|macro|ATTR_NOT_CONTENT_INDEXED
mdefine_line|#define ATTR_NOT_CONTENT_INDEXED 0x2000
DECL|macro|ATTR_ENCRYPTED
mdefine_line|#define ATTR_ENCRYPTED  0x4000
DECL|macro|ATTR_POSIX_SEMANTICS
mdefine_line|#define ATTR_POSIX_SEMANTICS 0x01000000
DECL|macro|ATTR_BACKUP_SEMANTICS
mdefine_line|#define ATTR_BACKUP_SEMANTICS 0x02000000
DECL|macro|ATTR_DELETE_ON_CLOSE
mdefine_line|#define ATTR_DELETE_ON_CLOSE 0x04000000
DECL|macro|ATTR_SEQUENTIAL_SCAN
mdefine_line|#define ATTR_SEQUENTIAL_SCAN 0x08000000
DECL|macro|ATTR_RANDOM_ACCESS
mdefine_line|#define ATTR_RANDOM_ACCESS   0x10000000
DECL|macro|ATTR_NO_BUFFERING
mdefine_line|#define ATTR_NO_BUFFERING    0x20000000
DECL|macro|ATTR_WRITE_THROUGH
mdefine_line|#define ATTR_WRITE_THROUGH   0x80000000
multiline_comment|/* ShareAccess flags */
DECL|macro|FILE_NO_SHARE
mdefine_line|#define FILE_NO_SHARE     0x00000000
DECL|macro|FILE_SHARE_READ
mdefine_line|#define FILE_SHARE_READ   0x00000001
DECL|macro|FILE_SHARE_WRITE
mdefine_line|#define FILE_SHARE_WRITE  0x00000002
DECL|macro|FILE_SHARE_DELETE
mdefine_line|#define FILE_SHARE_DELETE 0x00000004
DECL|macro|FILE_SHARE_ALL
mdefine_line|#define FILE_SHARE_ALL    0x00000007
multiline_comment|/* CreateDisposition flags */
DECL|macro|FILE_SUPERSEDE
mdefine_line|#define FILE_SUPERSEDE    0x00000000
DECL|macro|FILE_OPEN
mdefine_line|#define FILE_OPEN         0x00000001
DECL|macro|FILE_CREATE
mdefine_line|#define FILE_CREATE       0x00000002
DECL|macro|FILE_OPEN_IF
mdefine_line|#define FILE_OPEN_IF      0x00000003
DECL|macro|FILE_OVERWRITE
mdefine_line|#define FILE_OVERWRITE    0x00000004
DECL|macro|FILE_OVERWRITE_IF
mdefine_line|#define FILE_OVERWRITE_IF 0x00000005
multiline_comment|/* CreateOptions */
DECL|macro|CREATE_NOT_FILE
mdefine_line|#define CREATE_NOT_FILE&t;&t;0x00000001&t;/* if set must not be file */
DECL|macro|CREATE_WRITE_THROUGH
mdefine_line|#define CREATE_WRITE_THROUGH&t;0x00000002
DECL|macro|CREATE_NOT_DIR
mdefine_line|#define CREATE_NOT_DIR&t;&t;0x00000040&t;/* if set must not be directory */
DECL|macro|CREATE_RANDOM_ACCESS
mdefine_line|#define CREATE_RANDOM_ACCESS&t;0x00000800
DECL|macro|CREATE_DELETE_ON_CLOSE
mdefine_line|#define CREATE_DELETE_ON_CLOSE&t;0x00001000
DECL|macro|OPEN_REPARSE_POINT
mdefine_line|#define OPEN_REPARSE_POINT&t;0x00200000
multiline_comment|/* ImpersonationLevel flags */
DECL|macro|SECURITY_ANONYMOUS
mdefine_line|#define SECURITY_ANONYMOUS      0
DECL|macro|SECURITY_IDENTIFICATION
mdefine_line|#define SECURITY_IDENTIFICATION 1
DECL|macro|SECURITY_IMPERSONATION
mdefine_line|#define SECURITY_IMPERSONATION  2
DECL|macro|SECURITY_DELEGATION
mdefine_line|#define SECURITY_DELEGATION     3
multiline_comment|/* SecurityFlags */
DECL|macro|SECURITY_CONTEXT_TRACKING
mdefine_line|#define SECURITY_CONTEXT_TRACKING 0x01
DECL|macro|SECURITY_EFFECTIVE_ONLY
mdefine_line|#define SECURITY_EFFECTIVE_ONLY   0x02
multiline_comment|/*&n; * Default PID value, used in all SMBs where the PID is not important&n; */
DECL|macro|CIFS_DFT_PID
mdefine_line|#define CIFS_DFT_PID  0x1234
multiline_comment|/*&n; * We use the same routine for Copy and Move SMBs.  This flag is used to&n; * distinguish&n; */
DECL|macro|CIFS_COPY_OP
mdefine_line|#define CIFS_COPY_OP 1
DECL|macro|CIFS_RENAME_OP
mdefine_line|#define CIFS_RENAME_OP 2
DECL|macro|GETU16
mdefine_line|#define GETU16(var)  (*((__u16 *)var))&t;/* BB check for endian issues */
DECL|macro|GETU32
mdefine_line|#define GETU32(var)  (*((__u32 *)var))&t;/* BB check for endian issues */
macro_line|#pragma pack(1)
DECL|struct|smb_hdr
r_struct
id|smb_hdr
(brace
DECL|member|smb_buf_length
id|__u32
id|smb_buf_length
suffix:semicolon
multiline_comment|/* big endian on wire */
multiline_comment|/* BB length is only two or three bytes - with one or two byte type preceding it but that is always zero - we could mask the type byte off just in case BB */
DECL|member|Protocol
id|__u8
id|Protocol
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|Command
id|__u8
id|Command
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|ErrorClass
id|__u8
id|ErrorClass
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Error
id|__le16
id|Error
suffix:semicolon
DECL|member|DosError
)brace
id|DosError
suffix:semicolon
DECL|member|CifsError
id|__le32
id|CifsError
suffix:semicolon
DECL|member|Status
)brace
id|Status
suffix:semicolon
DECL|member|Flags
id|__u8
id|Flags
suffix:semicolon
DECL|member|Flags2
id|__le16
id|Flags2
suffix:semicolon
multiline_comment|/* note: le */
DECL|member|PidHigh
id|__le16
id|PidHigh
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|SequenceNumber
id|__le32
id|SequenceNumber
suffix:semicolon
multiline_comment|/* le */
DECL|member|Reserved
id|__u32
id|Reserved
suffix:semicolon
multiline_comment|/* zero */
DECL|member|Sequence
)brace
id|Sequence
suffix:semicolon
DECL|member|SecuritySignature
id|__u8
id|SecuritySignature
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* le */
DECL|member|Signature
)brace
id|Signature
suffix:semicolon
DECL|member|pad
id|__u8
id|pad
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|Tid
id|__u16
id|Tid
suffix:semicolon
DECL|member|Pid
id|__le16
id|Pid
suffix:semicolon
DECL|member|Uid
id|__u16
id|Uid
suffix:semicolon
DECL|member|Mid
id|__u16
id|Mid
suffix:semicolon
DECL|member|WordCount
id|__u8
id|WordCount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* given a pointer to an smb_hdr retrieve the value of byte count */
DECL|macro|BCC
mdefine_line|#define BCC(smb_var) ( *(__u16 *)((char *)smb_var + sizeof(struct smb_hdr) + (2* smb_var-&gt;WordCount) ) )
multiline_comment|/* given a pointer to an smb_hdr retrieve the pointer to the byte area */
DECL|macro|pByteArea
mdefine_line|#define pByteArea(smb_var) ((unsigned char *)smb_var + sizeof(struct smb_hdr) + (2* smb_var-&gt;WordCount) + 2 )
multiline_comment|/*&n; * Computer Name Length&n; */
DECL|macro|CNLEN
mdefine_line|#define CNLEN 15
multiline_comment|/*&n; * Share Name Length&t;&t;&t;&t;&t;  @S8A&n; * Note:  This length is limited by the SMB used to get   @S8A&n; *        the Share info.   NetShareEnum only returns 13  @S8A&n; *        chars, including the null termination.          @S8A &n; */
DECL|macro|SNLEN
mdefine_line|#define SNLEN 12&t;&t;/*@S8A */
multiline_comment|/*&n; * Comment Length&n; */
DECL|macro|MAXCOMMENTLEN
mdefine_line|#define MAXCOMMENTLEN 40
multiline_comment|/*&n; * The OS/2 maximum path name&n; */
DECL|macro|MAX_PATHCONF
mdefine_line|#define MAX_PATHCONF 256
multiline_comment|/*&n; *  SMB frame definitions  (following must be packed structs)&n; *  See the SNIA CIFS Specification for details.&n; *&n; *  The Naming convention is the lower case version of the&n; *  smb command code name for the struct and this is typedef to the&n; *  uppercase version of the same name with the prefix SMB_ removed &n; *  for brevity.  Although typedefs are not commonly used for &n; *  structure definitions in the Linux kernel, their use in the&n; *  CIFS standards document, which this code is based on, may&n; *  make this one of the cases where typedefs for structures make&n; *  sense to improve readability for readers of the standards doc.&n; *  Typedefs can always be removed later if they are too distracting&n; *  and they are only used for the CIFSs PDUs themselves, not&n; *  internal cifs vfs structures&n; *  &n; */
DECL|struct|negotiate_req
r_typedef
r_struct
id|negotiate_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|DialectsArray
r_int
r_char
id|DialectsArray
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|NEGOTIATE_REQ
)brace
id|NEGOTIATE_REQ
suffix:semicolon
DECL|struct|negotiate_rsp
r_typedef
r_struct
id|negotiate_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 17 */
DECL|member|DialectIndex
id|__le16
id|DialectIndex
suffix:semicolon
DECL|member|SecurityMode
id|__u8
id|SecurityMode
suffix:semicolon
DECL|member|MaxMpxCount
id|__le16
id|MaxMpxCount
suffix:semicolon
DECL|member|MaxNumberVcs
id|__le16
id|MaxNumberVcs
suffix:semicolon
DECL|member|MaxBufferSize
id|__le32
id|MaxBufferSize
suffix:semicolon
DECL|member|MaxRawSize
id|__le32
id|MaxRawSize
suffix:semicolon
DECL|member|SessionKey
id|__le32
id|SessionKey
suffix:semicolon
DECL|member|Capabilities
id|__le32
id|Capabilities
suffix:semicolon
multiline_comment|/* see below */
DECL|member|SystemTimeLow
id|__le32
id|SystemTimeLow
suffix:semicolon
DECL|member|SystemTimeHigh
id|__le32
id|SystemTimeHigh
suffix:semicolon
DECL|member|ServerTimeZone
id|__le16
id|ServerTimeZone
suffix:semicolon
DECL|member|EncryptionKeyLength
id|__u8
id|EncryptionKeyLength
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
r_union
(brace
DECL|member|EncryptionKey
r_int
r_char
id|EncryptionKey
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* if cap extended security is off */
multiline_comment|/* followed by Domain name - if extended security is off */
multiline_comment|/* followed by 16 bytes of server GUID */
multiline_comment|/* followed by security blob if cap_extended_security negotiated */
r_struct
(brace
DECL|member|GUID
r_int
r_char
id|GUID
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|SecurityBlob
r_int
r_char
id|SecurityBlob
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|extended_response
)brace
id|extended_response
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|NEGOTIATE_RSP
)brace
id|NEGOTIATE_RSP
suffix:semicolon
multiline_comment|/* SecurityMode bits */
DECL|macro|SECMODE_USER
mdefine_line|#define SECMODE_USER          0x01&t;/* off indicates share level security */
DECL|macro|SECMODE_PW_ENCRYPT
mdefine_line|#define SECMODE_PW_ENCRYPT    0x02
DECL|macro|SECMODE_SIGN_ENABLED
mdefine_line|#define SECMODE_SIGN_ENABLED  0x04&t;/* SMB security signatures enabled */
DECL|macro|SECMODE_SIGN_REQUIRED
mdefine_line|#define SECMODE_SIGN_REQUIRED 0x08&t;/* SMB security signatures required */
multiline_comment|/* Negotiate response Capabilities */
DECL|macro|CAP_RAW_MODE
mdefine_line|#define CAP_RAW_MODE           0x00000001
DECL|macro|CAP_MPX_MODE
mdefine_line|#define CAP_MPX_MODE           0x00000002
DECL|macro|CAP_UNICODE
mdefine_line|#define CAP_UNICODE            0x00000004
DECL|macro|CAP_LARGE_FILES
mdefine_line|#define CAP_LARGE_FILES        0x00000008
DECL|macro|CAP_NT_SMBS
mdefine_line|#define CAP_NT_SMBS            0x00000010&t;/* implies CAP_NT_FIND */
DECL|macro|CAP_RPC_REMOTE_APIS
mdefine_line|#define CAP_RPC_REMOTE_APIS    0x00000020
DECL|macro|CAP_STATUS32
mdefine_line|#define CAP_STATUS32           0x00000040
DECL|macro|CAP_LEVEL_II_OPLOCKS
mdefine_line|#define CAP_LEVEL_II_OPLOCKS   0x00000080
DECL|macro|CAP_LOCK_AND_READ
mdefine_line|#define CAP_LOCK_AND_READ      0x00000100
DECL|macro|CAP_NT_FIND
mdefine_line|#define CAP_NT_FIND            0x00000200
DECL|macro|CAP_DFS
mdefine_line|#define CAP_DFS                0x00001000
DECL|macro|CAP_INFOLEVEL_PASSTHRU
mdefine_line|#define CAP_INFOLEVEL_PASSTHRU 0x00002000
DECL|macro|CAP_LARGE_READ_X
mdefine_line|#define CAP_LARGE_READ_X       0x00004000
DECL|macro|CAP_LARGE_WRITE_X
mdefine_line|#define CAP_LARGE_WRITE_X      0x00008000
DECL|macro|CAP_UNIX
mdefine_line|#define CAP_UNIX               0x00800000
DECL|macro|CAP_RESERVED
mdefine_line|#define CAP_RESERVED           0x02000000
DECL|macro|CAP_BULK_TRANSFER
mdefine_line|#define CAP_BULK_TRANSFER      0x20000000
DECL|macro|CAP_COMPRESSED_DATA
mdefine_line|#define CAP_COMPRESSED_DATA    0x40000000
DECL|macro|CAP_EXTENDED_SECURITY
mdefine_line|#define CAP_EXTENDED_SECURITY  0x80000000
DECL|union|smb_com_session_setup_andx
r_typedef
r_union
id|smb_com_session_setup_andx
(brace
r_struct
(brace
multiline_comment|/* request format */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 12 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|MaxBufferSize
id|__le16
id|MaxBufferSize
suffix:semicolon
DECL|member|MaxMpxCount
id|__le16
id|MaxMpxCount
suffix:semicolon
DECL|member|VcNumber
id|__le16
id|VcNumber
suffix:semicolon
DECL|member|SessionKey
id|__u32
id|SessionKey
suffix:semicolon
DECL|member|SecurityBlobLength
id|__le16
id|SecurityBlobLength
suffix:semicolon
DECL|member|Reserved
id|__u32
id|Reserved
suffix:semicolon
DECL|member|Capabilities
id|__le32
id|Capabilities
suffix:semicolon
multiline_comment|/* see below */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|SecurityBlob
r_int
r_char
id|SecurityBlob
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by */
multiline_comment|/* STRING NativeOS */
multiline_comment|/* STRING NativeLanMan */
DECL|member|req
)brace
id|req
suffix:semicolon
multiline_comment|/* NTLM request format (with extended security */
r_struct
(brace
multiline_comment|/* request format */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 13 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|MaxBufferSize
id|__le16
id|MaxBufferSize
suffix:semicolon
DECL|member|MaxMpxCount
id|__le16
id|MaxMpxCount
suffix:semicolon
DECL|member|VcNumber
id|__le16
id|VcNumber
suffix:semicolon
DECL|member|SessionKey
id|__u32
id|SessionKey
suffix:semicolon
DECL|member|CaseInsensitivePasswordLength
id|__le16
id|CaseInsensitivePasswordLength
suffix:semicolon
multiline_comment|/* ASCII password length */
DECL|member|CaseSensitivePasswordLength
id|__le16
id|CaseSensitivePasswordLength
suffix:semicolon
multiline_comment|/* Unicode password length */
DECL|member|Reserved
id|__u32
id|Reserved
suffix:semicolon
multiline_comment|/* see below */
DECL|member|Capabilities
id|__le32
id|Capabilities
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|CaseInsensitivePassword
r_int
r_char
id|CaseInsensitivePassword
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by: */
multiline_comment|/* unsigned char * CaseSensitivePassword; */
multiline_comment|/* STRING AccountName */
multiline_comment|/* STRING PrimaryDomain */
multiline_comment|/* STRING NativeOS */
multiline_comment|/* STRING NativeLanMan */
DECL|member|req_no_secext
)brace
id|req_no_secext
suffix:semicolon
multiline_comment|/* NTLM request format (without extended security */
r_struct
(brace
multiline_comment|/* default (NTLM) response format */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 4 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Action
id|__le16
id|Action
suffix:semicolon
multiline_comment|/* see below */
DECL|member|SecurityBlobLength
id|__le16
id|SecurityBlobLength
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|SecurityBlob
r_int
r_char
id|SecurityBlob
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by */
multiline_comment|/*      unsigned char  * NativeOS;      */
multiline_comment|/*&t;unsigned char  * NativeLanMan;  */
multiline_comment|/*      unsigned char  * PrimaryDomain; */
DECL|member|resp
)brace
id|resp
suffix:semicolon
multiline_comment|/* NTLM response format (with or without extended security */
r_struct
(brace
multiline_comment|/* request format */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|MaxBufferSize
id|__le16
id|MaxBufferSize
suffix:semicolon
DECL|member|MaxMpxCount
id|__le16
id|MaxMpxCount
suffix:semicolon
DECL|member|VcNumber
id|__le16
id|VcNumber
suffix:semicolon
DECL|member|SessionKey
id|__u32
id|SessionKey
suffix:semicolon
DECL|member|PassswordLength
id|__le16
id|PassswordLength
suffix:semicolon
DECL|member|Reserved
id|__u32
id|Reserved
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|AccountPassword
r_int
r_char
id|AccountPassword
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by */
multiline_comment|/* STRING AccountName */
multiline_comment|/* STRING PrimaryDomain */
multiline_comment|/* STRING NativeOS */
multiline_comment|/* STRING NativeLanMan */
DECL|member|old_req
)brace
id|old_req
suffix:semicolon
multiline_comment|/* pre-NTLM (LANMAN2.1) request format */
r_struct
(brace
multiline_comment|/* default (NTLM) response format */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 3 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Action
id|__le16
id|Action
suffix:semicolon
multiline_comment|/* see below */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|NativeOS
r_int
r_char
id|NativeOS
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by */
multiline_comment|/*&t;unsigned char * NativeLanMan; */
multiline_comment|/*      unsigned char * PrimaryDomain; */
DECL|member|old_resp
)brace
id|old_resp
suffix:semicolon
multiline_comment|/* pre-NTLM (LANMAN2.1) response format */
DECL|typedef|SESSION_SETUP_ANDX
)brace
id|SESSION_SETUP_ANDX
suffix:semicolon
DECL|macro|CIFS_NETWORK_OPSYS
mdefine_line|#define CIFS_NETWORK_OPSYS &quot;CIFS VFS Client for Linux&quot;
multiline_comment|/* Capabilities bits (for NTLM SessSetup request) */
DECL|macro|CAP_UNICODE
mdefine_line|#define CAP_UNICODE            0x00000004
DECL|macro|CAP_LARGE_FILES
mdefine_line|#define CAP_LARGE_FILES        0x00000008
DECL|macro|CAP_NT_SMBS
mdefine_line|#define CAP_NT_SMBS            0x00000010
DECL|macro|CAP_STATUS32
mdefine_line|#define CAP_STATUS32           0x00000040
DECL|macro|CAP_LEVEL_II_OPLOCKS
mdefine_line|#define CAP_LEVEL_II_OPLOCKS   0x00000080
DECL|macro|CAP_NT_FIND
mdefine_line|#define CAP_NT_FIND            0x00000200&t;/* reserved should be zero (presumably because NT_SMBs implies the same thing) */
DECL|macro|CAP_BULK_TRANSFER
mdefine_line|#define CAP_BULK_TRANSFER      0x20000000
DECL|macro|CAP_EXTENDED_SECURITY
mdefine_line|#define CAP_EXTENDED_SECURITY  0x80000000
multiline_comment|/* Action bits */
DECL|macro|GUEST_LOGIN
mdefine_line|#define GUEST_LOGIN 1
DECL|struct|smb_com_tconx_req
r_typedef
r_struct
id|smb_com_tconx_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 4 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
multiline_comment|/* see below */
DECL|member|PasswordLength
id|__le16
id|PasswordLength
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Password
r_int
r_char
id|Password
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by */
multiline_comment|/* STRING Path    */
multiline_comment|/* &bslash;&bslash;server&bslash;share name */
multiline_comment|/* STRING Service */
DECL|typedef|TCONX_REQ
)brace
id|TCONX_REQ
suffix:semicolon
DECL|struct|smb_com_tconx_rsp
r_typedef
r_struct
id|smb_com_tconx_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 3 */
multiline_comment|/* note that Win2000 has sent wct=7 in some cases on responses. Four unspecified words followed OptionalSupport */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|OptionalSupport
id|__le16
id|OptionalSupport
suffix:semicolon
multiline_comment|/* see below */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Service
r_int
r_char
id|Service
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* always ASCII, not Unicode */
multiline_comment|/* STRING NativeFileSystem */
DECL|typedef|TCONX_RSP
)brace
id|TCONX_RSP
suffix:semicolon
multiline_comment|/* tree connect Flags */
DECL|macro|DISCONNECT_TID
mdefine_line|#define DISCONNECT_TID          0x0001
DECL|macro|TCON_EXTENDED_SECINFO
mdefine_line|#define TCON_EXTENDED_SECINFO   0x0008
multiline_comment|/* OptionalSupport bits */
DECL|macro|SMB_SUPPORT_SEARCH_BITS
mdefine_line|#define SMB_SUPPORT_SEARCH_BITS 0x0001&t;/* must have bits (exclusive searches suppt. */
DECL|macro|SMB_SHARE_IS_IN_DFS
mdefine_line|#define SMB_SHARE_IS_IN_DFS     0x0002
DECL|struct|smb_com_logoff_andx_req
r_typedef
r_struct
id|smb_com_logoff_andx_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 2 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__u16
id|AndXOffset
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|LOGOFF_ANDX_REQ
)brace
id|LOGOFF_ANDX_REQ
suffix:semicolon
DECL|struct|smb_com_logoff_andx_rsp
r_typedef
r_struct
id|smb_com_logoff_andx_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 2 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__u16
id|AndXOffset
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|LOGOFF_ANDX_RSP
)brace
id|LOGOFF_ANDX_RSP
suffix:semicolon
DECL|union|smb_com_tree_disconnect
r_typedef
r_union
id|smb_com_tree_disconnect
(brace
multiline_comment|/* as an altetnative can use flag on tree_connect PDU to effect disconnect */
multiline_comment|/* probably the simplest SMB PDU */
r_struct
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bcc = 0 */
DECL|member|req
)brace
id|req
suffix:semicolon
r_struct
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bcc = 0 */
DECL|member|resp
)brace
id|resp
suffix:semicolon
DECL|typedef|TREE_DISCONNECT
)brace
id|TREE_DISCONNECT
suffix:semicolon
DECL|struct|smb_com_close_req
r_typedef
r_struct
id|smb_com_close_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 3 */
DECL|member|FileID
id|__u16
id|FileID
suffix:semicolon
DECL|member|LastWriteTime
id|__u32
id|LastWriteTime
suffix:semicolon
multiline_comment|/* should be zero */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* 0 */
DECL|typedef|CLOSE_REQ
)brace
id|CLOSE_REQ
suffix:semicolon
DECL|struct|smb_com_close_rsp
r_typedef
r_struct
id|smb_com_close_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|CLOSE_RSP
)brace
id|CLOSE_RSP
suffix:semicolon
DECL|struct|smb_com_findclose_req
r_typedef
r_struct
id|smb_com_findclose_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 1 */
DECL|member|FileID
id|__u16
id|FileID
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* 0 */
DECL|typedef|FINDCLOSE_REQ
)brace
id|FINDCLOSE_REQ
suffix:semicolon
multiline_comment|/* OpenFlags */
DECL|macro|REQ_OPLOCK
mdefine_line|#define REQ_OPLOCK         0x00000002
DECL|macro|REQ_BATCHOPLOCK
mdefine_line|#define REQ_BATCHOPLOCK    0x00000004
DECL|macro|REQ_OPENDIRONLY
mdefine_line|#define REQ_OPENDIRONLY    0x00000008
DECL|struct|smb_com_open_req
r_typedef
r_struct
id|smb_com_open_req
(brace
multiline_comment|/* also handles create */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 24 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
multiline_comment|/* Must Be Zero */
DECL|member|NameLength
id|__le16
id|NameLength
suffix:semicolon
DECL|member|OpenFlags
id|__le32
id|OpenFlags
suffix:semicolon
DECL|member|RootDirectoryFid
id|__le32
id|RootDirectoryFid
suffix:semicolon
DECL|member|DesiredAccess
id|__le32
id|DesiredAccess
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|FileAttributes
id|__le32
id|FileAttributes
suffix:semicolon
DECL|member|ShareAccess
id|__le32
id|ShareAccess
suffix:semicolon
DECL|member|CreateDisposition
id|__le32
id|CreateDisposition
suffix:semicolon
DECL|member|CreateOptions
id|__le32
id|CreateOptions
suffix:semicolon
DECL|member|ImpersonationLevel
id|__le32
id|ImpersonationLevel
suffix:semicolon
DECL|member|SecurityFlags
id|__u8
id|SecurityFlags
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|fileName
r_char
id|fileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|OPEN_REQ
)brace
id|OPEN_REQ
suffix:semicolon
multiline_comment|/* open response: oplock levels */
DECL|macro|OPLOCK_NONE
mdefine_line|#define OPLOCK_NONE  &t; 0
DECL|macro|OPLOCK_EXCLUSIVE
mdefine_line|#define OPLOCK_EXCLUSIVE 1
DECL|macro|OPLOCK_BATCH
mdefine_line|#define OPLOCK_BATCH&t; 2
DECL|macro|OPLOCK_READ
mdefine_line|#define OPLOCK_READ&t; 3  /* level 2 oplock */
multiline_comment|/* open response for CreateAction shifted left */
DECL|macro|CIFS_CREATE_ACTION
mdefine_line|#define CIFS_CREATE_ACTION 0x20000 /* file created */
DECL|struct|smb_com_open_rsp
r_typedef
r_struct
id|smb_com_open_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 34 BB */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|OplockLevel
id|__u8
id|OplockLevel
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|CreateAction
id|__le32
id|CreateAction
suffix:semicolon
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|FileAttributes
id|__le32
id|FileAttributes
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|FileType
id|__le16
id|FileType
suffix:semicolon
DECL|member|DeviceState
id|__le16
id|DeviceState
suffix:semicolon
DECL|member|DirectoryFlag
id|__u8
id|DirectoryFlag
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|OPEN_RSP
)brace
id|OPEN_RSP
suffix:semicolon
DECL|struct|smb_com_write_req
r_typedef
r_struct
id|smb_com_write_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 14 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|OffsetLow
id|__le32
id|OffsetLow
suffix:semicolon
DECL|member|Reserved
id|__u32
id|Reserved
suffix:semicolon
DECL|member|WriteMode
id|__le16
id|WriteMode
suffix:semicolon
DECL|member|Remaining
id|__le16
id|Remaining
suffix:semicolon
DECL|member|DataLengthHigh
id|__le16
id|DataLengthHigh
suffix:semicolon
DECL|member|DataLengthLow
id|__le16
id|DataLengthLow
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|OffsetHigh
id|__le32
id|OffsetHigh
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
multiline_comment|/* BB check for whether padded to DWORD boundary and optimum performance here */
DECL|member|Data
r_char
id|Data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|WRITE_REQ
)brace
id|WRITE_REQ
suffix:semicolon
DECL|struct|smb_com_write_rsp
r_typedef
r_struct
id|smb_com_write_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 6 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Count
id|__le16
id|Count
suffix:semicolon
DECL|member|Remaining
id|__le16
id|Remaining
suffix:semicolon
DECL|member|Reserved
id|__le32
id|Reserved
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|WRITE_RSP
)brace
id|WRITE_RSP
suffix:semicolon
DECL|struct|smb_com_read_req
r_typedef
r_struct
id|smb_com_read_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 12 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|OffsetLow
id|__le32
id|OffsetLow
suffix:semicolon
DECL|member|MaxCount
id|__le16
id|MaxCount
suffix:semicolon
DECL|member|MinCount
id|__le16
id|MinCount
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|MaxCountHigh
id|__le32
id|MaxCountHigh
suffix:semicolon
DECL|member|Remaining
id|__le16
id|Remaining
suffix:semicolon
DECL|member|OffsetHigh
id|__le32
id|OffsetHigh
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|typedef|READ_REQ
)brace
id|READ_REQ
suffix:semicolon
DECL|struct|smb_com_read_rsp
r_typedef
r_struct
id|smb_com_read_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 12 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Remaining
id|__le16
id|Remaining
suffix:semicolon
DECL|member|DataCompactionMode
id|__le16
id|DataCompactionMode
suffix:semicolon
DECL|member|Reserved
id|__le16
id|Reserved
suffix:semicolon
DECL|member|DataLength
id|__le16
id|DataLength
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|DataLengthHigh
id|__le16
id|DataLengthHigh
suffix:semicolon
DECL|member|Reserved2
id|__u64
id|Reserved2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
multiline_comment|/* BB check for whether padded to DWORD boundary and optimum performance here */
DECL|member|Data
r_char
id|Data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|READ_RSP
)brace
id|READ_RSP
suffix:semicolon
DECL|struct|locking_andx_range
r_typedef
r_struct
id|locking_andx_range
(brace
DECL|member|Pid
id|__le16
id|Pid
suffix:semicolon
DECL|member|Pad
id|__le16
id|Pad
suffix:semicolon
DECL|member|OffsetHigh
id|__le32
id|OffsetHigh
suffix:semicolon
DECL|member|OffsetLow
id|__le32
id|OffsetLow
suffix:semicolon
DECL|member|LengthHigh
id|__le32
id|LengthHigh
suffix:semicolon
DECL|member|LengthLow
id|__le32
id|LengthLow
suffix:semicolon
DECL|typedef|LOCKING_ANDX_RANGE
)brace
id|LOCKING_ANDX_RANGE
suffix:semicolon
DECL|macro|LOCKING_ANDX_SHARED_LOCK
mdefine_line|#define LOCKING_ANDX_SHARED_LOCK     0x01
DECL|macro|LOCKING_ANDX_OPLOCK_RELEASE
mdefine_line|#define LOCKING_ANDX_OPLOCK_RELEASE  0x02
DECL|macro|LOCKING_ANDX_CHANGE_LOCKTYPE
mdefine_line|#define LOCKING_ANDX_CHANGE_LOCKTYPE 0x04
DECL|macro|LOCKING_ANDX_CANCEL_LOCK
mdefine_line|#define LOCKING_ANDX_CANCEL_LOCK     0x08
DECL|macro|LOCKING_ANDX_LARGE_FILES
mdefine_line|#define LOCKING_ANDX_LARGE_FILES     0x10&t;/* always on for us */
DECL|struct|smb_com_lock_req
r_typedef
r_struct
id|smb_com_lock_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 8 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|LockType
id|__u8
id|LockType
suffix:semicolon
DECL|member|OplockLevel
id|__u8
id|OplockLevel
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|NumberOfUnlocks
id|__le16
id|NumberOfUnlocks
suffix:semicolon
DECL|member|NumberOfLocks
id|__le16
id|NumberOfLocks
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Locks
id|LOCKING_ANDX_RANGE
id|Locks
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|LOCK_REQ
)brace
id|LOCK_REQ
suffix:semicolon
DECL|struct|smb_com_lock_rsp
r_typedef
r_struct
id|smb_com_lock_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 2 */
DECL|member|AndXCommand
id|__u8
id|AndXCommand
suffix:semicolon
DECL|member|AndXReserved
id|__u8
id|AndXReserved
suffix:semicolon
DECL|member|AndXOffset
id|__le16
id|AndXOffset
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|LOCK_RSP
)brace
id|LOCK_RSP
suffix:semicolon
DECL|struct|smb_com_rename_req
r_typedef
r_struct
id|smb_com_rename_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 1 */
DECL|member|SearchAttributes
id|__le16
id|SearchAttributes
suffix:semicolon
multiline_comment|/* target file attributes */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII or Unicode */
DECL|member|OldFileName
r_int
r_char
id|OldFileName
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by __u8 BufferFormat2 */
multiline_comment|/* followed by NewFileName */
DECL|typedef|RENAME_REQ
)brace
id|RENAME_REQ
suffix:semicolon
multiline_comment|/* copy request flags */
DECL|macro|COPY_MUST_BE_FILE
mdefine_line|#define COPY_MUST_BE_FILE      0x0001
DECL|macro|COPY_MUST_BE_DIR
mdefine_line|#define COPY_MUST_BE_DIR       0x0002
DECL|macro|COPY_TARGET_MODE_ASCII
mdefine_line|#define COPY_TARGET_MODE_ASCII 0x0004 /* if not set, binary */
DECL|macro|COPY_SOURCE_MODE_ASCII
mdefine_line|#define COPY_SOURCE_MODE_ASCII 0x0008 /* if not set, binary */
DECL|macro|COPY_VERIFY_WRITES
mdefine_line|#define COPY_VERIFY_WRITES     0x0010
DECL|macro|COPY_TREE
mdefine_line|#define COPY_TREE              0x0020 
DECL|struct|smb_com_copy_req
r_typedef
r_struct
id|smb_com_copy_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 3 */
DECL|member|Tid2
id|__u16
id|Tid2
suffix:semicolon
DECL|member|OpenFunction
id|__le16
id|OpenFunction
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII or Unicode */
DECL|member|OldFileName
r_int
r_char
id|OldFileName
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by __u8 BufferFormat2 */
multiline_comment|/* followed by NewFileName string */
DECL|typedef|COPY_REQ
)brace
id|COPY_REQ
suffix:semicolon
DECL|struct|smb_com_copy_rsp
r_typedef
r_struct
id|smb_com_copy_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 1 */
DECL|member|CopyCount
id|__le16
id|CopyCount
suffix:semicolon
multiline_comment|/* number of files copied */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* may be zero */
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 0x04 - only present if errored file follows */
DECL|member|ErrorFileName
r_int
r_char
id|ErrorFileName
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* only present if error in copy */
DECL|typedef|COPY_RSP
)brace
id|COPY_RSP
suffix:semicolon
DECL|macro|CREATE_HARD_LINK
mdefine_line|#define CREATE_HARD_LINK&t;&t;0x103
DECL|macro|MOVEFILE_COPY_ALLOWED
mdefine_line|#define MOVEFILE_COPY_ALLOWED&t;&t;0x0002
DECL|macro|MOVEFILE_REPLACE_EXISTING
mdefine_line|#define MOVEFILE_REPLACE_EXISTING&t;0x0001
DECL|struct|smb_com_nt_rename_req
r_typedef
r_struct
id|smb_com_nt_rename_req
(brace
multiline_comment|/* A5 - also used for create hardlink */
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 4 */
DECL|member|SearchAttributes
id|__le16
id|SearchAttributes
suffix:semicolon
multiline_comment|/* target file attributes */
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
multiline_comment|/* spec says Information Level */
DECL|member|ClusterCount
id|__le32
id|ClusterCount
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII or Unicode */
DECL|member|OldFileName
r_int
r_char
id|OldFileName
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* followed by __u8 BufferFormat2 */
multiline_comment|/* followed by NewFileName */
DECL|typedef|NT_RENAME_REQ
)brace
id|NT_RENAME_REQ
suffix:semicolon
DECL|struct|smb_com_rename_rsp
r_typedef
r_struct
id|smb_com_rename_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|RENAME_RSP
)brace
id|RENAME_RSP
suffix:semicolon
DECL|struct|smb_com_delete_file_req
r_typedef
r_struct
id|smb_com_delete_file_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 1 */
DECL|member|SearchAttributes
id|__le16
id|SearchAttributes
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII */
DECL|member|fileName
r_int
r_char
id|fileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|DELETE_FILE_REQ
)brace
id|DELETE_FILE_REQ
suffix:semicolon
DECL|struct|smb_com_delete_file_rsp
r_typedef
r_struct
id|smb_com_delete_file_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|DELETE_FILE_RSP
)brace
id|DELETE_FILE_RSP
suffix:semicolon
DECL|struct|smb_com_delete_directory_req
r_typedef
r_struct
id|smb_com_delete_directory_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII */
DECL|member|DirName
r_int
r_char
id|DirName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|DELETE_DIRECTORY_REQ
)brace
id|DELETE_DIRECTORY_REQ
suffix:semicolon
DECL|struct|smb_com_delete_directory_rsp
r_typedef
r_struct
id|smb_com_delete_directory_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|DELETE_DIRECTORY_RSP
)brace
id|DELETE_DIRECTORY_RSP
suffix:semicolon
DECL|struct|smb_com_create_directory_req
r_typedef
r_struct
id|smb_com_create_directory_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|BufferFormat
id|__u8
id|BufferFormat
suffix:semicolon
multiline_comment|/* 4 = ASCII */
DECL|member|DirName
r_int
r_char
id|DirName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|CREATE_DIRECTORY_REQ
)brace
id|CREATE_DIRECTORY_REQ
suffix:semicolon
DECL|struct|smb_com_create_directory_rsp
r_typedef
r_struct
id|smb_com_create_directory_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* bct = 0 */
DECL|typedef|CREATE_DIRECTORY_RSP
)brace
id|CREATE_DIRECTORY_RSP
suffix:semicolon
multiline_comment|/***************************************************/
multiline_comment|/* NT Transact structure defintions follow         */
multiline_comment|/* Currently only ioctl and notify are implemented */
multiline_comment|/***************************************************/
DECL|struct|smb_com_transaction_ioctl_req
r_typedef
r_struct
id|smb_com_transaction_ioctl_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 23 */
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u16
id|Reserved
suffix:semicolon
DECL|member|TotalParameterCount
id|__le32
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le32
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le32
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le32
id|MaxDataCount
suffix:semicolon
DECL|member|ParameterCount
id|__le32
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le32
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le32
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le32
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* four setup words follow subcommand */
multiline_comment|/* SNIA spec incorrectly included spurious pad here */
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* 2 = IOCTL/FSCTL */
DECL|member|FunctionCode
id|__le32
id|FunctionCode
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|IsFsctl
id|__u8
id|IsFsctl
suffix:semicolon
multiline_comment|/* 1 = File System Control, 0 = device control (IOCTL)*/
DECL|member|IsRootFlag
id|__u8
id|IsRootFlag
suffix:semicolon
multiline_comment|/* 1 = apply command to root of share (must be DFS share)*/
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Data
id|__u8
id|Data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACT_IOCTL_REQ
)brace
id|TRANSACT_IOCTL_REQ
suffix:semicolon
DECL|struct|smb_com_transaction_ioctl_rsp
r_typedef
r_struct
id|smb_com_transaction_ioctl_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 19 */
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|TotalParameterCount
id|__le32
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le32
id|TotalDataCount
suffix:semicolon
DECL|member|ParameterCount
id|__le32
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le32
id|ParameterOffset
suffix:semicolon
DECL|member|ParameterDisplacement
id|__le32
id|ParameterDisplacement
suffix:semicolon
DECL|member|DataCount
id|__le32
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le32
id|DataOffset
suffix:semicolon
DECL|member|DataDisplacement
id|__le32
id|DataDisplacement
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|ReturnedDataLen
id|__le16
id|ReturnedDataLen
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|TRANSACT_IOCTL_RSP
)brace
id|TRANSACT_IOCTL_RSP
suffix:semicolon
DECL|struct|smb_com_transaction_change_notify_req
r_typedef
r_struct
id|smb_com_transaction_change_notify_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 23 */
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u16
id|Reserved
suffix:semicolon
DECL|member|TotalParameterCount
id|__le32
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le32
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le32
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le32
id|MaxDataCount
suffix:semicolon
DECL|member|ParameterCount
id|__le32
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le32
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le32
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le32
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* four setup words follow subcommand */
multiline_comment|/* SNIA spec incorrectly included spurious pad here */
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* 4 = Change Notify */
DECL|member|CompletionFilter
id|__le32
id|CompletionFilter
suffix:semicolon
multiline_comment|/* operation to monitor */
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|WatchTree
id|__u8
id|WatchTree
suffix:semicolon
multiline_comment|/* 1 = Monitor subdirectories */
DECL|member|Reserved2
id|__u8
id|Reserved2
suffix:semicolon
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
multiline_comment|/* __u8 Pad[3];*/
multiline_comment|/*&t;__u8 Data[1];*/
DECL|typedef|TRANSACT_CHANGE_NOTIFY_REQ
)brace
id|TRANSACT_CHANGE_NOTIFY_REQ
suffix:semicolon
DECL|struct|smb_com_transaction_change_notify_rsp
r_typedef
r_struct
id|smb_com_transaction_change_notify_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 18 */
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|TotalParameterCount
id|__le32
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le32
id|TotalDataCount
suffix:semicolon
DECL|member|ParameterCount
id|__le32
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le32
id|ParameterOffset
suffix:semicolon
DECL|member|ParameterDisplacement
id|__le32
id|ParameterDisplacement
suffix:semicolon
DECL|member|DataCount
id|__le32
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le32
id|DataOffset
suffix:semicolon
DECL|member|DataDisplacement
id|__le32
id|DataDisplacement
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
multiline_comment|/* __u8 Pad[3]; */
DECL|typedef|TRANSACT_CHANGE_NOTIFY_RSP
)brace
id|TRANSACT_CHANGE_NOTIFY_RSP
suffix:semicolon
multiline_comment|/* Completion Filter flags for Notify */
DECL|macro|FILE_NOTIFY_CHANGE_FILE_NAME
mdefine_line|#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
DECL|macro|FILE_NOTIFY_CHANGE_DIR_NAME
mdefine_line|#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
DECL|macro|FILE_NOTIFY_CHANGE_NAME
mdefine_line|#define FILE_NOTIFY_CHANGE_NAME         0x00000003
DECL|macro|FILE_NOTIFY_CHANGE_ATTRIBUTES
mdefine_line|#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
DECL|macro|FILE_NOTIFY_CHANGE_SIZE
mdefine_line|#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
DECL|macro|FILE_NOTIFY_CHANGE_LAST_WRITE
mdefine_line|#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
DECL|macro|FILE_NOTIFY_CHANGE_LAST_ACCESS
mdefine_line|#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
DECL|macro|FILE_NOTIFY_CHANGE_CREATION
mdefine_line|#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
DECL|macro|FILE_NOTIFY_CHANGE_EA
mdefine_line|#define FILE_NOTIFY_CHANGE_EA           0x00000080
DECL|macro|FILE_NOTIFY_CHANGE_SECURITY
mdefine_line|#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
DECL|macro|FILE_NOTIFY_CHANGE_STREAM_NAME
mdefine_line|#define FILE_NOTIFY_CHANGE_STREAM_NAME  0x00000200
DECL|macro|FILE_NOTIFY_CHANGE_STREAM_SIZE
mdefine_line|#define FILE_NOTIFY_CHANGE_STREAM_SIZE  0x00000400
DECL|macro|FILE_NOTIFY_CHANGE_STREAM_WRITE
mdefine_line|#define FILE_NOTIFY_CHANGE_STREAM_WRITE 0x00000800
DECL|macro|FILE_ACTION_ADDED
mdefine_line|#define FILE_ACTION_ADDED&t;&t;0x00000001
DECL|macro|FILE_ACTION_REMOVED
mdefine_line|#define FILE_ACTION_REMOVED&t;&t;0x00000002
DECL|macro|FILE_ACTION_MODIFIED
mdefine_line|#define FILE_ACTION_MODIFIED&t;&t;0x00000003
DECL|macro|FILE_ACTION_RENAMED_OLD_NAME
mdefine_line|#define FILE_ACTION_RENAMED_OLD_NAME&t;0x00000004
DECL|macro|FILE_ACTION_RENAMED_NEW_NAME
mdefine_line|#define FILE_ACTION_RENAMED_NEW_NAME&t;0x00000005
DECL|macro|FILE_ACTION_ADDED_STREAM
mdefine_line|#define FILE_ACTION_ADDED_STREAM&t;0x00000006
DECL|macro|FILE_ACTION_REMOVED_STREAM
mdefine_line|#define FILE_ACTION_REMOVED_STREAM&t;0x00000007
DECL|macro|FILE_ACTION_MODIFIED_STREAM
mdefine_line|#define FILE_ACTION_MODIFIED_STREAM&t;0x00000008
multiline_comment|/* response contains array of the following structures */
DECL|struct|file_notify_information
r_struct
id|file_notify_information
(brace
DECL|member|NextEntryOffset
id|__u32
id|NextEntryOffset
suffix:semicolon
DECL|member|Action
id|__u32
id|Action
suffix:semicolon
DECL|member|FileNameLength
id|__u32
id|FileNameLength
suffix:semicolon
DECL|member|FileName
id|__u8
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|reparse_data
r_struct
id|reparse_data
(brace
DECL|member|ReparseTag
id|__u32
id|ReparseTag
suffix:semicolon
DECL|member|ReparseDataLength
id|__u16
id|ReparseDataLength
suffix:semicolon
DECL|member|Reserved
id|__u16
id|Reserved
suffix:semicolon
DECL|member|AltNameOffset
id|__u16
id|AltNameOffset
suffix:semicolon
DECL|member|AltNameLen
id|__u16
id|AltNameLen
suffix:semicolon
DECL|member|TargetNameOffset
id|__u16
id|TargetNameOffset
suffix:semicolon
DECL|member|TargetNameLen
id|__u16
id|TargetNameLen
suffix:semicolon
DECL|member|LinkNamesBuf
r_char
id|LinkNamesBuf
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cifs_quota_data
r_struct
id|cifs_quota_data
(brace
DECL|member|rsrvd1
id|__u32
id|rsrvd1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|sid_size
id|__u32
id|sid_size
suffix:semicolon
DECL|member|rsrvd2
id|__u64
id|rsrvd2
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|space_used
id|__u64
id|space_used
suffix:semicolon
DECL|member|soft_limit
id|__u64
id|soft_limit
suffix:semicolon
DECL|member|hard_limit
id|__u64
id|hard_limit
suffix:semicolon
DECL|member|sid
r_char
id|sid
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* variable size? */
)brace
suffix:semicolon
multiline_comment|/* quota sub commands */
DECL|macro|QUOTA_LIST_CONTINUE
mdefine_line|#define QUOTA_LIST_CONTINUE&t;    0
DECL|macro|QUOTA_LIST_START
mdefine_line|#define QUOTA_LIST_START&t;0x100
DECL|macro|QUOTA_FOR_SID
mdefine_line|#define QUOTA_FOR_SID&t;&t;0x101
DECL|struct|trans2_req
r_struct
id|trans2_req
(brace
multiline_comment|/* struct smb_hdr hdr precedes. Set wct = 14+ */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* 1st setup word - SetupCount words follow */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|smb_t2_req
r_struct
id|smb_t2_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
DECL|member|t2_req
r_struct
id|trans2_req
id|t2_req
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|trans2_resp
r_struct
id|trans2_resp
(brace
multiline_comment|/* struct smb_hdr hdr precedes. Note wct = 10 + setup count */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|Reserved
id|__u16
id|Reserved
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|ParameterDisplacement
id|__le16
id|ParameterDisplacement
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|DataDisplacement
id|__le16
id|DataDisplacement
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved1
id|__u8
id|Reserved1
suffix:semicolon
multiline_comment|/* SetupWords[SetupCount];&n;&t;__u16 ByteCount;&n;&t;__u16 Reserved2;*/
multiline_comment|/* data area follows */
)brace
suffix:semicolon
DECL|struct|smb_t2_rsp
r_struct
id|smb_t2_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
DECL|member|t2_rsp
r_struct
id|trans2_resp
id|t2_rsp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PathInfo/FileInfo infolevels */
DECL|macro|SMB_INFO_STANDARD
mdefine_line|#define SMB_INFO_STANDARD                   1
DECL|macro|SMB_SET_FILE_EA
mdefine_line|#define SMB_SET_FILE_EA                     2
DECL|macro|SMB_QUERY_FILE_EA_SIZE
mdefine_line|#define SMB_QUERY_FILE_EA_SIZE              2
DECL|macro|SMB_INFO_QUERY_EAS_FROM_LIST
mdefine_line|#define SMB_INFO_QUERY_EAS_FROM_LIST        3
DECL|macro|SMB_INFO_QUERY_ALL_EAS
mdefine_line|#define SMB_INFO_QUERY_ALL_EAS              4
DECL|macro|SMB_INFO_IS_NAME_VALID
mdefine_line|#define SMB_INFO_IS_NAME_VALID              6
DECL|macro|SMB_QUERY_FILE_BASIC_INFO
mdefine_line|#define SMB_QUERY_FILE_BASIC_INFO       0x101
DECL|macro|SMB_QUERY_FILE_STANDARD_INFO
mdefine_line|#define SMB_QUERY_FILE_STANDARD_INFO    0x102
DECL|macro|SMB_QUERY_FILE_EA_INFO
mdefine_line|#define SMB_QUERY_FILE_EA_INFO          0x103
DECL|macro|SMB_QUERY_FILE_NAME_INFO
mdefine_line|#define SMB_QUERY_FILE_NAME_INFO        0x104
DECL|macro|SMB_QUERY_FILE_ALLOCATION_INFO
mdefine_line|#define SMB_QUERY_FILE_ALLOCATION_INFO  0x105
DECL|macro|SMB_QUERY_FILE_END_OF_FILEINFO
mdefine_line|#define SMB_QUERY_FILE_END_OF_FILEINFO  0x106
DECL|macro|SMB_QUERY_FILE_ALL_INFO
mdefine_line|#define SMB_QUERY_FILE_ALL_INFO         0x107
DECL|macro|SMB_QUERY_ALT_NAME_INFO
mdefine_line|#define SMB_QUERY_ALT_NAME_INFO         0x108
DECL|macro|SMB_QUERY_FILE_STREAM_INFO
mdefine_line|#define SMB_QUERY_FILE_STREAM_INFO      0x109
DECL|macro|SMB_QUERY_FILE_COMPRESSION_INFO
mdefine_line|#define SMB_QUERY_FILE_COMPRESSION_INFO 0x10B
DECL|macro|SMB_QUERY_FILE_UNIX_BASIC
mdefine_line|#define SMB_QUERY_FILE_UNIX_BASIC       0x200
DECL|macro|SMB_QUERY_FILE_UNIX_LINK
mdefine_line|#define SMB_QUERY_FILE_UNIX_LINK        0x201
DECL|macro|SMB_QUERY_POSIX_ACL
mdefine_line|#define SMB_QUERY_POSIX_ACL             0x204
DECL|macro|SMB_QUERY_FILE_INTERNAL_INFO
mdefine_line|#define SMB_QUERY_FILE_INTERNAL_INFO    0x3ee
DECL|macro|SMB_QUERY_FILE_ACCESS_INFO
mdefine_line|#define SMB_QUERY_FILE_ACCESS_INFO      0x3f0
DECL|macro|SMB_QUERY_FILE_NAME_INFO2
mdefine_line|#define SMB_QUERY_FILE_NAME_INFO2       0x3f1 /* 0x30 bytes */
DECL|macro|SMB_QUERY_FILE_POSITION_INFO
mdefine_line|#define SMB_QUERY_FILE_POSITION_INFO    0x3f6 
DECL|macro|SMB_QUERY_FILE_MODE_INFO
mdefine_line|#define SMB_QUERY_FILE_MODE_INFO        0x3f8
DECL|macro|SMB_QUERY_FILE_ALGN_INFO
mdefine_line|#define SMB_QUERY_FILE_ALGN_INFO        0x3f9 
DECL|macro|SMB_SET_FILE_BASIC_INFO
mdefine_line|#define SMB_SET_FILE_BASIC_INFO&t;        0x101
DECL|macro|SMB_SET_FILE_DISPOSITION_INFO
mdefine_line|#define SMB_SET_FILE_DISPOSITION_INFO   0x102
DECL|macro|SMB_SET_FILE_ALLOCATION_INFO
mdefine_line|#define SMB_SET_FILE_ALLOCATION_INFO    0x103
DECL|macro|SMB_SET_FILE_END_OF_FILE_INFO
mdefine_line|#define SMB_SET_FILE_END_OF_FILE_INFO   0x104
DECL|macro|SMB_SET_FILE_UNIX_BASIC
mdefine_line|#define SMB_SET_FILE_UNIX_BASIC         0x200
DECL|macro|SMB_SET_FILE_UNIX_LINK
mdefine_line|#define SMB_SET_FILE_UNIX_LINK          0x201
DECL|macro|SMB_SET_POSIX_ACL
mdefine_line|#define SMB_SET_POSIX_ACL               0x204
DECL|macro|SMB_SET_FILE_UNIX_HLINK
mdefine_line|#define SMB_SET_FILE_UNIX_HLINK         0x203
DECL|macro|SMB_SET_FILE_BASIC_INFO2
mdefine_line|#define SMB_SET_FILE_BASIC_INFO2        0x3ec
DECL|macro|SMB_SET_FILE_RENAME_INFORMATION
mdefine_line|#define SMB_SET_FILE_RENAME_INFORMATION 0x3f2 /* BB check if qpathinfo level too */
DECL|macro|SMB_FILE_ALL_INFO2
mdefine_line|#define SMB_FILE_ALL_INFO2              0x3fa
DECL|macro|SMB_SET_FILE_ALLOCATION_INFO2
mdefine_line|#define SMB_SET_FILE_ALLOCATION_INFO2   0x3fb
DECL|macro|SMB_SET_FILE_END_OF_FILE_INFO2
mdefine_line|#define SMB_SET_FILE_END_OF_FILE_INFO2  0x3fc
DECL|macro|SMB_FILE_MOVE_CLUSTER_INFO
mdefine_line|#define SMB_FILE_MOVE_CLUSTER_INFO      0x407
DECL|macro|SMB_FILE_QUOTA_INFO
mdefine_line|#define SMB_FILE_QUOTA_INFO             0x408
DECL|macro|SMB_FILE_REPARSEPOINT_INFO
mdefine_line|#define SMB_FILE_REPARSEPOINT_INFO      0x409
DECL|macro|SMB_FILE_MAXIMUM_INFO
mdefine_line|#define SMB_FILE_MAXIMUM_INFO           0x40d
multiline_comment|/* Find File infolevels */
DECL|macro|SMB_FIND_FILE_DIRECTORY_INFO
mdefine_line|#define SMB_FIND_FILE_DIRECTORY_INFO      0x101
DECL|macro|SMB_FIND_FILE_FULL_DIRECTORY_INFO
mdefine_line|#define SMB_FIND_FILE_FULL_DIRECTORY_INFO 0x102
DECL|macro|SMB_FIND_FILE_NAMES_INFO
mdefine_line|#define SMB_FIND_FILE_NAMES_INFO          0x103
DECL|macro|SMB_FIND_FILE_BOTH_DIRECTORY_INFO
mdefine_line|#define SMB_FIND_FILE_BOTH_DIRECTORY_INFO 0x104
DECL|macro|SMB_FIND_FILE_ID_FULL_DIR_INFO
mdefine_line|#define SMB_FIND_FILE_ID_FULL_DIR_INFO    0x105
DECL|macro|SMB_FIND_FILE_ID_BOTH_DIR_INFO
mdefine_line|#define SMB_FIND_FILE_ID_BOTH_DIR_INFO    0x106
DECL|macro|SMB_FIND_FILE_UNIX
mdefine_line|#define SMB_FIND_FILE_UNIX                0x202
DECL|struct|smb_com_transaction2_qpi_req
r_typedef
r_struct
id|smb_com_transaction2_qpi_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 14+ */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* one setup word */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|member|Reserved4
id|__u32
id|Reserved4
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACTION2_QPI_REQ
)brace
id|TRANSACTION2_QPI_REQ
suffix:semicolon
DECL|struct|smb_com_transaction2_qpi_rsp
r_typedef
r_struct
id|smb_com_transaction2_qpi_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 + SetupCount */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
multiline_comment|/* parameter word reserved - present for infolevels &gt; 100 */
DECL|typedef|TRANSACTION2_QPI_RSP
)brace
id|TRANSACTION2_QPI_RSP
suffix:semicolon
DECL|struct|smb_com_transaction2_spi_req
r_typedef
r_struct
id|smb_com_transaction2_spi_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 15 */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* one setup word */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|Pad1
id|__u16
id|Pad1
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|member|Reserved4
id|__u32
id|Reserved4
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACTION2_SPI_REQ
)brace
id|TRANSACTION2_SPI_REQ
suffix:semicolon
DECL|struct|smb_com_transaction2_spi_rsp
r_typedef
r_struct
id|smb_com_transaction2_spi_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 + SetupCount */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
multiline_comment|/* parameter word reserved - present for infolevels &gt; 100 */
DECL|typedef|TRANSACTION2_SPI_RSP
)brace
id|TRANSACTION2_SPI_RSP
suffix:semicolon
DECL|struct|set_file_rename
r_struct
id|set_file_rename
(brace
DECL|member|overwrite
id|__le32
id|overwrite
suffix:semicolon
multiline_comment|/* 1 = overwrite dest */
DECL|member|root_fid
id|__u32
id|root_fid
suffix:semicolon
multiline_comment|/* zero */
DECL|member|target_name_len
id|__le32
id|target_name_len
suffix:semicolon
DECL|member|target_name
r_char
id|target_name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Must be unicode */
)brace
suffix:semicolon
DECL|struct|smb_com_transaction2_sfi_req
r_struct
id|smb_com_transaction2_sfi_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 15 */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* one setup word */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|Pad1
id|__u16
id|Pad1
suffix:semicolon
DECL|member|Fid
id|__u16
id|Fid
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|member|Reserved4
id|__u16
id|Reserved4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|smb_com_transaction2_sfi_rsp
r_struct
id|smb_com_transaction2_sfi_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 + SetupCount */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
multiline_comment|/* parameter word reserved - present for infolevels &gt; 100 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Flags on T2 FINDFIRST and FINDNEXT &n; */
DECL|macro|CIFS_SEARCH_CLOSE_ALWAYS
mdefine_line|#define CIFS_SEARCH_CLOSE_ALWAYS  0x0001
DECL|macro|CIFS_SEARCH_CLOSE_AT_END
mdefine_line|#define CIFS_SEARCH_CLOSE_AT_END  0x0002
DECL|macro|CIFS_SEARCH_RETURN_RESUME
mdefine_line|#define CIFS_SEARCH_RETURN_RESUME 0x0004
DECL|macro|CIFS_SEARCH_CONTINUE_FROM_LAST
mdefine_line|#define CIFS_SEARCH_CONTINUE_FROM_LAST 0x0008
DECL|macro|CIFS_SEARCH_BACKUP_SEARCH
mdefine_line|#define CIFS_SEARCH_BACKUP_SEARCH 0x0010
multiline_comment|/*&n; * Size of the resume key on FINDFIRST and FINDNEXT calls&n; */
DECL|macro|CIFS_SMB_RESUME_KEY_SIZE
mdefine_line|#define CIFS_SMB_RESUME_KEY_SIZE 4
DECL|struct|smb_com_transaction2_ffirst_req
r_typedef
r_struct
id|smb_com_transaction2_ffirst_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 15 */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* one */
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* TRANS2_FIND_FIRST */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|SearchAttributes
id|__le16
id|SearchAttributes
suffix:semicolon
DECL|member|SearchCount
id|__le16
id|SearchCount
suffix:semicolon
DECL|member|SearchFlags
id|__le16
id|SearchFlags
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|member|SearchStorageType
id|__le32
id|SearchStorageType
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACTION2_FFIRST_REQ
)brace
id|TRANSACTION2_FFIRST_REQ
suffix:semicolon
DECL|struct|smb_com_transaction2_ffirst_rsp
r_typedef
r_struct
id|smb_com_transaction2_ffirst_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|TRANSACTION2_FFIRST_RSP
)brace
id|TRANSACTION2_FFIRST_RSP
suffix:semicolon
DECL|struct|smb_com_transaction2_ffirst_rsp_parms
r_typedef
r_struct
id|smb_com_transaction2_ffirst_rsp_parms
(brace
DECL|member|SearchHandle
id|__u16
id|SearchHandle
suffix:semicolon
DECL|member|SearchCount
id|__le16
id|SearchCount
suffix:semicolon
DECL|member|EndofSearch
id|__le16
id|EndofSearch
suffix:semicolon
DECL|member|EAErrorOffset
id|__le16
id|EAErrorOffset
suffix:semicolon
DECL|member|LastNameOffset
id|__le16
id|LastNameOffset
suffix:semicolon
DECL|typedef|T2_FFIRST_RSP_PARMS
)brace
id|T2_FFIRST_RSP_PARMS
suffix:semicolon
DECL|struct|smb_com_transaction2_fnext_req
r_typedef
r_struct
id|smb_com_transaction2_fnext_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 15 */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
multiline_comment|/* one */
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* TRANS2_FIND_NEXT */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|SearchHandle
id|__u16
id|SearchHandle
suffix:semicolon
DECL|member|SearchCount
id|__le16
id|SearchCount
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|member|ResumeKey
id|__u32
id|ResumeKey
suffix:semicolon
DECL|member|SearchFlags
id|__le16
id|SearchFlags
suffix:semicolon
DECL|member|ResumeFileName
r_char
id|ResumeFileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACTION2_FNEXT_REQ
)brace
id|TRANSACTION2_FNEXT_REQ
suffix:semicolon
DECL|struct|smb_com_transaction2_fnext_rsp
r_typedef
r_struct
id|smb_com_transaction2_fnext_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|typedef|TRANSACTION2_FNEXT_RSP
)brace
id|TRANSACTION2_FNEXT_RSP
suffix:semicolon
DECL|struct|smb_com_transaction2_fnext_rsp_parms
r_typedef
r_struct
id|smb_com_transaction2_fnext_rsp_parms
(brace
DECL|member|SearchCount
id|__le16
id|SearchCount
suffix:semicolon
DECL|member|EndofSearch
id|__le16
id|EndofSearch
suffix:semicolon
DECL|member|EAErrorOffset
id|__le16
id|EAErrorOffset
suffix:semicolon
DECL|member|LastNameOffset
id|__le16
id|LastNameOffset
suffix:semicolon
DECL|typedef|T2_FNEXT_RSP_PARMS
)brace
id|T2_FNEXT_RSP_PARMS
suffix:semicolon
multiline_comment|/* QFSInfo Levels */
DECL|macro|SMB_INFO_ALLOCATION
mdefine_line|#define SMB_INFO_ALLOCATION         1
DECL|macro|SMB_INFO_VOLUME
mdefine_line|#define SMB_INFO_VOLUME             2
DECL|macro|SMB_QUERY_FS_VOLUME_INFO
mdefine_line|#define SMB_QUERY_FS_VOLUME_INFO    0x102
DECL|macro|SMB_QUERY_FS_SIZE_INFO
mdefine_line|#define SMB_QUERY_FS_SIZE_INFO      0x103
DECL|macro|SMB_QUERY_FS_DEVICE_INFO
mdefine_line|#define SMB_QUERY_FS_DEVICE_INFO    0x104
DECL|macro|SMB_QUERY_FS_ATTRIBUTE_INFO
mdefine_line|#define SMB_QUERY_FS_ATTRIBUTE_INFO 0x105
DECL|macro|SMB_QUERY_CIFS_UNIX_INFO
mdefine_line|#define SMB_QUERY_CIFS_UNIX_INFO    0x200
DECL|macro|SMB_QUERY_LABEL_INFO
mdefine_line|#define SMB_QUERY_LABEL_INFO        0x3ea
DECL|macro|SMB_QUERY_FS_QUOTA_INFO
mdefine_line|#define SMB_QUERY_FS_QUOTA_INFO     0x3ee
DECL|macro|SMB_QUERY_FS_FULL_SIZE_INFO
mdefine_line|#define SMB_QUERY_FS_FULL_SIZE_INFO 0x3ef
DECL|macro|SMB_QUERY_OBJECTID_INFO
mdefine_line|#define SMB_QUERY_OBJECTID_INFO     0x3f0
DECL|struct|smb_com_transaction2_qfsi_req
r_typedef
r_struct
id|smb_com_transaction2_qfsi_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 14+ */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* one setup word */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|InformationLevel
id|__le16
id|InformationLevel
suffix:semicolon
DECL|typedef|TRANSACTION2_QFSI_REQ
)brace
id|TRANSACTION2_QFSI_REQ
suffix:semicolon
DECL|struct|smb_com_transaction_qfsi_rsp
r_typedef
r_struct
id|smb_com_transaction_qfsi_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 + SetupCount */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
multiline_comment|/* may be three bytes */
multiline_comment|/* followed by data area */
DECL|typedef|TRANSACTION2_QFSI_RSP
)brace
id|TRANSACTION2_QFSI_RSP
suffix:semicolon
DECL|struct|smb_com_transaction2_get_dfs_refer_req
r_typedef
r_struct
id|smb_com_transaction2_get_dfs_refer_req
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 15 */
DECL|member|TotalParameterCount
id|__le16
id|TotalParameterCount
suffix:semicolon
DECL|member|TotalDataCount
id|__le16
id|TotalDataCount
suffix:semicolon
DECL|member|MaxParameterCount
id|__le16
id|MaxParameterCount
suffix:semicolon
DECL|member|MaxDataCount
id|__le16
id|MaxDataCount
suffix:semicolon
DECL|member|MaxSetupCount
id|__u8
id|MaxSetupCount
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|Flags
id|__le16
id|Flags
suffix:semicolon
DECL|member|Timeout
id|__le32
id|Timeout
suffix:semicolon
DECL|member|Reserved2
id|__u16
id|Reserved2
suffix:semicolon
DECL|member|ParameterCount
id|__le16
id|ParameterCount
suffix:semicolon
DECL|member|ParameterOffset
id|__le16
id|ParameterOffset
suffix:semicolon
DECL|member|DataCount
id|__le16
id|DataCount
suffix:semicolon
DECL|member|DataOffset
id|__le16
id|DataOffset
suffix:semicolon
DECL|member|SetupCount
id|__u8
id|SetupCount
suffix:semicolon
DECL|member|Reserved3
id|__u8
id|Reserved3
suffix:semicolon
DECL|member|SubCommand
id|__le16
id|SubCommand
suffix:semicolon
multiline_comment|/* one setup word */
DECL|member|ByteCount
id|__le16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Win2K has sent 0x0F01 (max resp length perhaps?) followed by one byte pad - doesn&squot;t seem to matter though */
DECL|member|MaxReferralLevel
id|__le16
id|MaxReferralLevel
suffix:semicolon
DECL|member|RequestFileName
r_char
id|RequestFileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TRANSACTION2_GET_DFS_REFER_REQ
)brace
id|TRANSACTION2_GET_DFS_REFER_REQ
suffix:semicolon
DECL|struct|dfs_referral_level_3
r_typedef
r_struct
id|dfs_referral_level_3
(brace
DECL|member|VersionNumber
id|__le16
id|VersionNumber
suffix:semicolon
DECL|member|ReferralSize
id|__le16
id|ReferralSize
suffix:semicolon
DECL|member|ServerType
id|__le16
id|ServerType
suffix:semicolon
multiline_comment|/* 0x0001 = CIFS server */
DECL|member|ReferralFlags
id|__le16
id|ReferralFlags
suffix:semicolon
multiline_comment|/* or proximity - not clear which since always set to zero - SNIA spec says 0x01 means strip off PathConsumed chars before submitting RequestFileName to remote node */
DECL|member|TimeToLive
id|__le16
id|TimeToLive
suffix:semicolon
DECL|member|Proximity
id|__le16
id|Proximity
suffix:semicolon
DECL|member|DfsPathOffset
id|__le16
id|DfsPathOffset
suffix:semicolon
DECL|member|DfsAlternatePathOffset
id|__le16
id|DfsAlternatePathOffset
suffix:semicolon
DECL|member|NetworkAddressOffset
id|__le16
id|NetworkAddressOffset
suffix:semicolon
DECL|typedef|REFERRAL3
)brace
id|REFERRAL3
suffix:semicolon
DECL|struct|smb_com_transaction_get_dfs_refer_rsp
r_typedef
r_struct
id|smb_com_transaction_get_dfs_refer_rsp
(brace
DECL|member|hdr
r_struct
id|smb_hdr
id|hdr
suffix:semicolon
multiline_comment|/* wct = 10 */
DECL|member|t2
r_struct
id|trans2_resp
id|t2
suffix:semicolon
DECL|member|ByteCount
id|__u16
id|ByteCount
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|PathConsumed
id|__le16
id|PathConsumed
suffix:semicolon
DECL|member|NumberOfReferrals
id|__le16
id|NumberOfReferrals
suffix:semicolon
DECL|member|DFSFlags
id|__le16
id|DFSFlags
suffix:semicolon
DECL|member|Pad2
id|__u16
id|Pad2
suffix:semicolon
DECL|member|referrals
id|REFERRAL3
id|referrals
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* array of level 3 dfs_referral structures */
multiline_comment|/* followed by the strings pointed to by the referral structures */
DECL|typedef|TRANSACTION2_GET_DFS_REFER_RSP
)brace
id|TRANSACTION2_GET_DFS_REFER_RSP
suffix:semicolon
multiline_comment|/* DFS Flags */
DECL|macro|DFSREF_REFERRAL_SERVER
mdefine_line|#define DFSREF_REFERRAL_SERVER  0x0001
DECL|macro|DFSREF_STORAGE_SERVER
mdefine_line|#define DFSREF_STORAGE_SERVER   0x0002
multiline_comment|/* IOCTL information */
multiline_comment|/* List of ioctl function codes that look to be of interest to remote clients like this. */
multiline_comment|/* Need to do some experimentation to make sure they all work remotely.                  */
multiline_comment|/* Some of the following such as the encryption/compression ones would be                */
multiline_comment|/* invoked from tools via a specialized hook into the VFS rather than via the            */
multiline_comment|/* standard vfs entry points */
DECL|macro|FSCTL_REQUEST_OPLOCK_LEVEL_1
mdefine_line|#define FSCTL_REQUEST_OPLOCK_LEVEL_1 0x00090000
DECL|macro|FSCTL_REQUEST_OPLOCK_LEVEL_2
mdefine_line|#define FSCTL_REQUEST_OPLOCK_LEVEL_2 0x00090004
DECL|macro|FSCTL_REQUEST_BATCH_OPLOCK
mdefine_line|#define FSCTL_REQUEST_BATCH_OPLOCK   0x00090008
DECL|macro|FSCTL_LOCK_VOLUME
mdefine_line|#define FSCTL_LOCK_VOLUME            0x00090018
DECL|macro|FSCTL_UNLOCK_VOLUME
mdefine_line|#define FSCTL_UNLOCK_VOLUME          0x0009001C
DECL|macro|FSCTL_GET_COMPRESSION
mdefine_line|#define FSCTL_GET_COMPRESSION        0x0009003C
DECL|macro|FSCTL_SET_COMPRESSION
mdefine_line|#define FSCTL_SET_COMPRESSION        0x0009C040
DECL|macro|FSCTL_REQUEST_FILTER_OPLOCK
mdefine_line|#define FSCTL_REQUEST_FILTER_OPLOCK  0x0009008C
DECL|macro|FSCTL_FILESYS_GET_STATISTICS
mdefine_line|#define FSCTL_FILESYS_GET_STATISTICS 0x00090090
DECL|macro|FSCTL_SET_REPARSE_POINT
mdefine_line|#define FSCTL_SET_REPARSE_POINT      0x000900A4
DECL|macro|FSCTL_GET_REPARSE_POINT
mdefine_line|#define FSCTL_GET_REPARSE_POINT      0x000900A8
DECL|macro|FSCTL_DELETE_REPARSE_POINT
mdefine_line|#define FSCTL_DELETE_REPARSE_POINT   0x000900AC
DECL|macro|FSCTL_SET_SPARSE
mdefine_line|#define FSCTL_SET_SPARSE             0x000900C4
DECL|macro|FSCTL_SET_ZERO_DATA
mdefine_line|#define FSCTL_SET_ZERO_DATA          0x000900C8
DECL|macro|FSCTL_SET_ENCRYPTION
mdefine_line|#define FSCTL_SET_ENCRYPTION         0x000900D7
DECL|macro|FSCTL_ENCRYPTION_FSCTL_IO
mdefine_line|#define FSCTL_ENCRYPTION_FSCTL_IO    0x000900DB
DECL|macro|FSCTL_WRITE_RAW_ENCRYPTED
mdefine_line|#define FSCTL_WRITE_RAW_ENCRYPTED    0x000900DF
DECL|macro|FSCTL_READ_RAW_ENCRYPTED
mdefine_line|#define FSCTL_READ_RAW_ENCRYPTED     0x000900E3
DECL|macro|FSCTL_SIS_COPYFILE
mdefine_line|#define FSCTL_SIS_COPYFILE           0x00090100
DECL|macro|FSCTL_SIS_LINK_FILES
mdefine_line|#define FSCTL_SIS_LINK_FILES         0x0009C104
DECL|macro|IO_REPARSE_TAG_MOUNT_POINT
mdefine_line|#define IO_REPARSE_TAG_MOUNT_POINT   0xA0000003
DECL|macro|IO_REPARSE_TAG_HSM
mdefine_line|#define IO_REPARSE_TAG_HSM           0xC0000004
DECL|macro|IO_REPARSE_TAG_SIS
mdefine_line|#define IO_REPARSE_TAG_SIS           0x80000007
multiline_comment|/*&n; ************************************************************************&n; * All structs for everything above the SMB PDUs themselves&n; * (such as the T2 level specific data) go here                  &n; ************************************************************************&n; */
multiline_comment|/*&n; * Information on a server&n; */
DECL|struct|serverInfo
r_struct
id|serverInfo
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|versionMajor
r_int
r_char
id|versionMajor
suffix:semicolon
DECL|member|versionMinor
r_int
r_char
id|versionMinor
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|commentOffset
r_int
r_int
id|commentOffset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following structure is the format of the data returned on a NetShareEnum&n; * with level &quot;90&quot; (x5A)&n; */
DECL|struct|shareInfo
r_struct
id|shareInfo
(brace
DECL|member|shareName
r_char
id|shareName
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|pad
r_char
id|pad
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|commentOffset
r_int
r_int
id|commentOffset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aliasInfo
r_struct
id|aliasInfo
(brace
DECL|member|aliasName
r_char
id|aliasName
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|pad
r_char
id|pad
suffix:semicolon
DECL|member|commentOffset
r_int
r_int
id|commentOffset
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aliasInfo92
r_struct
id|aliasInfo92
(brace
DECL|member|aliasNameOffset
r_int
id|aliasNameOffset
suffix:semicolon
DECL|member|serverNameOffset
r_int
id|serverNameOffset
suffix:semicolon
DECL|member|shareNameOffset
r_int
id|shareNameOffset
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|TotalAllocationUnits
id|__le64
id|TotalAllocationUnits
suffix:semicolon
DECL|member|FreeAllocationUnits
id|__le64
id|FreeAllocationUnits
suffix:semicolon
DECL|member|SectorsPerAllocationUnit
id|__le32
id|SectorsPerAllocationUnit
suffix:semicolon
DECL|member|BytesPerSector
id|__le32
id|BytesPerSector
suffix:semicolon
DECL|typedef|FILE_SYSTEM_INFO
)brace
id|FILE_SYSTEM_INFO
suffix:semicolon
multiline_comment|/* size info, level 0x103 */
r_typedef
r_struct
(brace
DECL|member|MajorVersionNumber
id|__le16
id|MajorVersionNumber
suffix:semicolon
DECL|member|MinorVersionNumber
id|__le16
id|MinorVersionNumber
suffix:semicolon
DECL|member|Capability
id|__le64
id|Capability
suffix:semicolon
DECL|typedef|FILE_SYSTEM_UNIX_INFO
)brace
id|FILE_SYSTEM_UNIX_INFO
suffix:semicolon
multiline_comment|/* Unix extensions info, level 0x200 */
multiline_comment|/* Linux/Unix extensions capability flags */
DECL|macro|CIFS_UNIX_FCNTL_CAP
mdefine_line|#define CIFS_UNIX_FCNTL_CAP             0x00000001 /* support for fcntl locks */
DECL|macro|CIFS_UNIX_POSIX_ACL_CAP
mdefine_line|#define CIFS_UNIX_POSIX_ACL_CAP         0x00000002
multiline_comment|/* DeviceType Flags */
DECL|macro|FILE_DEVICE_CD_ROM
mdefine_line|#define FILE_DEVICE_CD_ROM              0x00000002
DECL|macro|FILE_DEVICE_CD_ROM_FILE_SYSTEM
mdefine_line|#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
DECL|macro|FILE_DEVICE_DFS
mdefine_line|#define FILE_DEVICE_DFS                 0x00000006
DECL|macro|FILE_DEVICE_DISK
mdefine_line|#define FILE_DEVICE_DISK                0x00000007
DECL|macro|FILE_DEVICE_DISK_FILE_SYSTEM
mdefine_line|#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
DECL|macro|FILE_DEVICE_FILE_SYSTEM
mdefine_line|#define FILE_DEVICE_FILE_SYSTEM         0x00000009
DECL|macro|FILE_DEVICE_NAMED_PIPE
mdefine_line|#define FILE_DEVICE_NAMED_PIPE          0x00000011
DECL|macro|FILE_DEVICE_NETWORK
mdefine_line|#define FILE_DEVICE_NETWORK             0x00000012
DECL|macro|FILE_DEVICE_NETWORK_FILE_SYSTEM
mdefine_line|#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
DECL|macro|FILE_DEVICE_NULL
mdefine_line|#define FILE_DEVICE_NULL                0x00000015
DECL|macro|FILE_DEVICE_PARALLEL_PORT
mdefine_line|#define FILE_DEVICE_PARALLEL_PORT       0x00000016
DECL|macro|FILE_DEVICE_PRINTER
mdefine_line|#define FILE_DEVICE_PRINTER             0x00000018
DECL|macro|FILE_DEVICE_SERIAL_PORT
mdefine_line|#define FILE_DEVICE_SERIAL_PORT         0x0000001b
DECL|macro|FILE_DEVICE_STREAMS
mdefine_line|#define FILE_DEVICE_STREAMS             0x0000001e
DECL|macro|FILE_DEVICE_TAPE
mdefine_line|#define FILE_DEVICE_TAPE                0x0000001f
DECL|macro|FILE_DEVICE_TAPE_FILE_SYSTEM
mdefine_line|#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
DECL|macro|FILE_DEVICE_VIRTUAL_DISK
mdefine_line|#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
DECL|macro|FILE_DEVICE_NETWORK_REDIRECTOR
mdefine_line|#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
r_typedef
r_struct
(brace
DECL|member|DeviceType
id|__le32
id|DeviceType
suffix:semicolon
DECL|member|DeviceCharacteristics
id|__le32
id|DeviceCharacteristics
suffix:semicolon
DECL|typedef|FILE_SYSTEM_DEVICE_INFO
)brace
id|FILE_SYSTEM_DEVICE_INFO
suffix:semicolon
multiline_comment|/* device info, level 0x104 */
r_typedef
r_struct
(brace
DECL|member|Attributes
id|__le32
id|Attributes
suffix:semicolon
DECL|member|MaxPathNameComponentLength
id|__le32
id|MaxPathNameComponentLength
suffix:semicolon
DECL|member|FileSystemNameLen
id|__le32
id|FileSystemNameLen
suffix:semicolon
DECL|member|FileSystemName
r_char
id|FileSystemName
(braket
l_int|52
)braket
suffix:semicolon
multiline_comment|/* do not really need to save this - so potentially get only subset of name */
DECL|typedef|FILE_SYSTEM_ATTRIBUTE_INFO
)brace
id|FILE_SYSTEM_ATTRIBUTE_INFO
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/* QueryFileInfo/QueryPathinfo (also for SetPath/SetFile) data buffer formats */
multiline_comment|/******************************************************************************/
r_typedef
r_struct
(brace
multiline_comment|/* data block encoding of response to level 263 QPathInfo */
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|Attributes
id|__le32
id|Attributes
suffix:semicolon
DECL|member|Pad1
id|__u32
id|Pad1
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
multiline_comment|/* size ie offset to first free byte in file */
DECL|member|NumberOfLinks
id|__le32
id|NumberOfLinks
suffix:semicolon
multiline_comment|/* hard links */
DECL|member|DeletePending
id|__u8
id|DeletePending
suffix:semicolon
DECL|member|Directory
id|__u8
id|Directory
suffix:semicolon
DECL|member|Pad2
id|__u16
id|Pad2
suffix:semicolon
DECL|member|IndexNumber
id|__u64
id|IndexNumber
suffix:semicolon
DECL|member|EASize
id|__le32
id|EASize
suffix:semicolon
DECL|member|AccessFlags
id|__le32
id|AccessFlags
suffix:semicolon
DECL|member|IndexNumber1
id|__u64
id|IndexNumber1
suffix:semicolon
DECL|member|CurrentByteOffset
id|__le64
id|CurrentByteOffset
suffix:semicolon
DECL|member|Mode
id|__le32
id|Mode
suffix:semicolon
DECL|member|AlignmentRequirement
id|__le32
id|AlignmentRequirement
suffix:semicolon
DECL|member|FileNameLength
id|__le32
id|FileNameLength
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_ALL_INFO
)brace
id|FILE_ALL_INFO
suffix:semicolon
multiline_comment|/* level 0x107 QPathInfo */
multiline_comment|/* defines for enumerating possible values of the Unix type field below */
DECL|macro|UNIX_FILE
mdefine_line|#define UNIX_FILE      0
DECL|macro|UNIX_DIR
mdefine_line|#define UNIX_DIR       1
DECL|macro|UNIX_SYMLINK
mdefine_line|#define UNIX_SYMLINK   2
DECL|macro|UNIX_CHARDEV
mdefine_line|#define UNIX_CHARDEV   3
DECL|macro|UNIX_BLOCKDEV
mdefine_line|#define UNIX_BLOCKDEV  4
DECL|macro|UNIX_FIFO
mdefine_line|#define UNIX_FIFO      5
DECL|macro|UNIX_SOCKET
mdefine_line|#define UNIX_SOCKET    6
r_typedef
r_struct
(brace
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|NumOfBytes
id|__le64
id|NumOfBytes
suffix:semicolon
DECL|member|LastStatusChange
id|__le64
id|LastStatusChange
suffix:semicolon
multiline_comment|/*SNIA specs DCE time for the 3 time fields */
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastModificationTime
id|__le64
id|LastModificationTime
suffix:semicolon
DECL|member|Uid
id|__le64
id|Uid
suffix:semicolon
DECL|member|Gid
id|__le64
id|Gid
suffix:semicolon
DECL|member|Type
id|__le32
id|Type
suffix:semicolon
DECL|member|DevMajor
id|__le64
id|DevMajor
suffix:semicolon
DECL|member|DevMinor
id|__le64
id|DevMinor
suffix:semicolon
DECL|member|UniqueId
id|__u64
id|UniqueId
suffix:semicolon
DECL|member|Permissions
id|__le64
id|Permissions
suffix:semicolon
DECL|member|Nlinks
id|__le64
id|Nlinks
suffix:semicolon
DECL|typedef|FILE_UNIX_BASIC_INFO
)brace
id|FILE_UNIX_BASIC_INFO
suffix:semicolon
multiline_comment|/* level 0x200 QPathInfo */
r_typedef
r_struct
(brace
DECL|member|LinkDest
r_char
id|LinkDest
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_UNIX_LINK_INFO
)brace
id|FILE_UNIX_LINK_INFO
suffix:semicolon
multiline_comment|/* level 0x201 QPathInfo */
r_typedef
r_struct
(brace
DECL|member|CreationDate
id|__u16
id|CreationDate
suffix:semicolon
DECL|member|CreationTime
id|__u16
id|CreationTime
suffix:semicolon
DECL|member|LastAccessDate
id|__u16
id|LastAccessDate
suffix:semicolon
DECL|member|LastAccessTime
id|__u16
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteDate
id|__u16
id|LastWriteDate
suffix:semicolon
DECL|member|LastWriteTime
id|__u16
id|LastWriteTime
suffix:semicolon
DECL|member|DataSize
id|__u32
id|DataSize
suffix:semicolon
multiline_comment|/* File Size (EOF) */
DECL|member|AllocationSize
id|__u32
id|AllocationSize
suffix:semicolon
DECL|member|Attributes
id|__u16
id|Attributes
suffix:semicolon
multiline_comment|/* verify not u32 */
DECL|member|EASize
id|__u32
id|EASize
suffix:semicolon
DECL|typedef|FILE_INFO_STANDARD
)brace
id|FILE_INFO_STANDARD
suffix:semicolon
multiline_comment|/* level 1 SetPath/FileInfo */
r_typedef
r_struct
(brace
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|Attributes
id|__le32
id|Attributes
suffix:semicolon
DECL|member|Pad
id|__u32
id|Pad
suffix:semicolon
DECL|typedef|FILE_BASIC_INFO
)brace
id|FILE_BASIC_INFO
suffix:semicolon
multiline_comment|/* size info, level 0x101 */
DECL|struct|file_allocation_info
r_struct
id|file_allocation_info
(brace
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
multiline_comment|/* Note old Samba srvr rounds this up too much */
)brace
suffix:semicolon
multiline_comment|/* size used on disk, level 0x103 for set, 0x105 for query */
DECL|struct|file_end_of_file_info
r_struct
id|file_end_of_file_info
(brace
DECL|member|FileSize
id|__le64
id|FileSize
suffix:semicolon
multiline_comment|/* offset to end of file */
)brace
suffix:semicolon
multiline_comment|/* size info, level 0x104 for set, 0x106 for query */
DECL|struct|file_alt_name_info
r_struct
id|file_alt_name_info
(brace
DECL|member|alt_name
id|__u8
id|alt_name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* level 0x0108 */
DECL|struct|file_stream_info
r_struct
id|file_stream_info
(brace
DECL|member|number_of_streams
id|__le32
id|number_of_streams
suffix:semicolon
multiline_comment|/* BB check sizes and verify location */
multiline_comment|/* followed by info on streams themselves &n;&t;&t;u64 size;&n;&t;&t;u64 allocation_size &n;&t;&t;stream info */
)brace
suffix:semicolon
multiline_comment|/* level 0x109 */
DECL|struct|file_compression_info
r_struct
id|file_compression_info
(brace
DECL|member|compressed_size
id|__le64
id|compressed_size
suffix:semicolon
DECL|member|format
id|__le16
id|format
suffix:semicolon
DECL|member|unit_shift
id|__u8
id|unit_shift
suffix:semicolon
DECL|member|ch_shift
id|__u8
id|ch_shift
suffix:semicolon
DECL|member|cl_shift
id|__u8
id|cl_shift
suffix:semicolon
DECL|member|pad
id|__u8
id|pad
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* level 0x10b */
multiline_comment|/* POSIX ACL set/query path info structures */
DECL|macro|CIFS_ACL_VERSION
mdefine_line|#define CIFS_ACL_VERSION 1
DECL|struct|cifs_posix_ace
r_struct
id|cifs_posix_ace
(brace
multiline_comment|/* access control entry (ACE) */
DECL|member|cifs_e_tag
id|__u8
id|cifs_e_tag
suffix:semicolon
DECL|member|cifs_e_perm
id|__u8
id|cifs_e_perm
suffix:semicolon
DECL|member|cifs_uid
id|__le64
id|cifs_uid
suffix:semicolon
multiline_comment|/* or gid */
)brace
suffix:semicolon
DECL|struct|cifs_posix_acl
r_struct
id|cifs_posix_acl
(brace
multiline_comment|/* access conrol list  (ACL) */
DECL|member|version
id|__le16
id|version
suffix:semicolon
DECL|member|access_entry_count
id|__le16
id|access_entry_count
suffix:semicolon
multiline_comment|/* access ACL - count of entries */
DECL|member|default_entry_count
id|__le16
id|default_entry_count
suffix:semicolon
multiline_comment|/* default ACL - count of entries */
DECL|member|ace_array
r_struct
id|cifs_posix_ace
id|ace_array
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* followed by&n;&t;struct cifs_posix_ace default_ace_arraay[] */
)brace
suffix:semicolon
multiline_comment|/* level 0x204 */
multiline_comment|/* types of access control entries already defined in posix_acl.h */
multiline_comment|/* #define CIFS_POSIX_ACL_USER_OBJ&t; 0x01&n;#define CIFS_POSIX_ACL_USER      0x02&n;#define CIFS_POSIX_ACL_GROUP_OBJ 0x04&n;#define CIFS_POSIX_ACL_GROUP     0x08&n;#define CIFS_POSIX_ACL_MASK      0x10&n;#define CIFS_POSIX_ACL_OTHER     0x20 */
multiline_comment|/* types of perms */
multiline_comment|/* #define CIFS_POSIX_ACL_EXECUTE   0x01&n;#define CIFS_POSIX_ACL_WRITE     0x02&n;#define CIFS_POSIX_ACL_READ&t;     0x04 */
multiline_comment|/* end of POSIX ACL definitions */
DECL|struct|file_internal_info
r_struct
id|file_internal_info
(brace
DECL|member|UniqueId
id|__u64
id|UniqueId
suffix:semicolon
multiline_comment|/* inode number */
)brace
suffix:semicolon
multiline_comment|/* level 0x3ee */
DECL|struct|file_mode_info
r_struct
id|file_mode_info
(brace
DECL|member|Mode
id|__le32
id|Mode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* level 0x3f8 */
DECL|struct|file_attrib_tag
r_struct
id|file_attrib_tag
(brace
DECL|member|Attribute
id|__le32
id|Attribute
suffix:semicolon
DECL|member|ReparseTag
id|__le32
id|ReparseTag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* level 0x40b */
multiline_comment|/********************************************************/
multiline_comment|/*  FindFirst/FindNext transact2 data buffer formats    */
multiline_comment|/********************************************************/
r_typedef
r_struct
(brace
DECL|member|NextEntryOffset
id|__le32
id|NextEntryOffset
suffix:semicolon
DECL|member|ResumeKey
id|__u32
id|ResumeKey
suffix:semicolon
multiline_comment|/* as with FileIndex - no need to convert */
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|NumOfBytes
id|__le64
id|NumOfBytes
suffix:semicolon
DECL|member|LastStatusChange
id|__le64
id|LastStatusChange
suffix:semicolon
multiline_comment|/*SNIA specs DCE time for the 3 time fields */
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastModificationTime
id|__le64
id|LastModificationTime
suffix:semicolon
DECL|member|Uid
id|__le64
id|Uid
suffix:semicolon
DECL|member|Gid
id|__le64
id|Gid
suffix:semicolon
DECL|member|Type
id|__le32
id|Type
suffix:semicolon
DECL|member|DevMajor
id|__le64
id|DevMajor
suffix:semicolon
DECL|member|DevMinor
id|__le64
id|DevMinor
suffix:semicolon
DECL|member|UniqueId
id|__u64
id|UniqueId
suffix:semicolon
DECL|member|Permissions
id|__le64
id|Permissions
suffix:semicolon
DECL|member|Nlinks
id|__le64
id|Nlinks
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_UNIX_INFO
)brace
id|FILE_UNIX_INFO
suffix:semicolon
multiline_comment|/* level 0x202 */
r_typedef
r_struct
(brace
DECL|member|NextEntryOffset
id|__le32
id|NextEntryOffset
suffix:semicolon
DECL|member|FileIndex
id|__u32
id|FileIndex
suffix:semicolon
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|ExtFileAttributes
id|__le32
id|ExtFileAttributes
suffix:semicolon
DECL|member|FileNameLength
id|__le32
id|FileNameLength
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_DIRECTORY_INFO
)brace
id|FILE_DIRECTORY_INFO
suffix:semicolon
multiline_comment|/* level 0x101 FF response data area */
r_typedef
r_struct
(brace
DECL|member|NextEntryOffset
id|__le32
id|NextEntryOffset
suffix:semicolon
DECL|member|FileIndex
id|__u32
id|FileIndex
suffix:semicolon
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|ExtFileAttributes
id|__le32
id|ExtFileAttributes
suffix:semicolon
DECL|member|FileNameLength
id|__le32
id|FileNameLength
suffix:semicolon
DECL|member|EaSize
id|__le32
id|EaSize
suffix:semicolon
multiline_comment|/* length of the xattrs */
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_FULL_DIRECTORY_INFO
)brace
id|FILE_FULL_DIRECTORY_INFO
suffix:semicolon
multiline_comment|/* level 0x102 FF response data area */
r_typedef
r_struct
(brace
DECL|member|NextEntryOffset
id|__le32
id|NextEntryOffset
suffix:semicolon
DECL|member|FileIndex
id|__u32
id|FileIndex
suffix:semicolon
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|ExtFileAttributes
id|__le32
id|ExtFileAttributes
suffix:semicolon
DECL|member|FileNameLength
id|__le32
id|FileNameLength
suffix:semicolon
DECL|member|EaSize
id|__le32
id|EaSize
suffix:semicolon
multiline_comment|/* EA size */
DECL|member|Reserved
id|__le32
id|Reserved
suffix:semicolon
DECL|member|UniqueId
id|__u64
id|UniqueId
suffix:semicolon
multiline_comment|/* inode num - le since Samba puts ino in low 32 bit*/
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SEARCH_ID_FULL_DIR_INFO
)brace
id|SEARCH_ID_FULL_DIR_INFO
suffix:semicolon
multiline_comment|/* level 0x105 FF response data area */
r_typedef
r_struct
(brace
DECL|member|NextEntryOffset
id|__le32
id|NextEntryOffset
suffix:semicolon
DECL|member|FileIndex
id|__u32
id|FileIndex
suffix:semicolon
DECL|member|CreationTime
id|__le64
id|CreationTime
suffix:semicolon
DECL|member|LastAccessTime
id|__le64
id|LastAccessTime
suffix:semicolon
DECL|member|LastWriteTime
id|__le64
id|LastWriteTime
suffix:semicolon
DECL|member|ChangeTime
id|__le64
id|ChangeTime
suffix:semicolon
DECL|member|EndOfFile
id|__le64
id|EndOfFile
suffix:semicolon
DECL|member|AllocationSize
id|__le64
id|AllocationSize
suffix:semicolon
DECL|member|ExtFileAttributes
id|__le32
id|ExtFileAttributes
suffix:semicolon
DECL|member|FileNameLength
id|__le32
id|FileNameLength
suffix:semicolon
DECL|member|EaSize
id|__le32
id|EaSize
suffix:semicolon
multiline_comment|/* length of the xattrs */
DECL|member|ShortNameLength
id|__u8
id|ShortNameLength
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
suffix:semicolon
DECL|member|ShortName
id|__u8
id|ShortName
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|FileName
r_char
id|FileName
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|FILE_BOTH_DIRECTORY_INFO
)brace
id|FILE_BOTH_DIRECTORY_INFO
suffix:semicolon
multiline_comment|/* level 0x104 FF response data area */
DECL|struct|gea
r_struct
id|gea
(brace
DECL|member|name_len
r_int
r_char
id|name_len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gealist
r_struct
id|gealist
(brace
DECL|member|list_len
r_int
r_int
id|list_len
suffix:semicolon
DECL|member|list
r_struct
id|gea
id|list
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fea
r_struct
id|fea
(brace
DECL|member|EA_flags
r_int
r_char
id|EA_flags
suffix:semicolon
DECL|member|name_len
id|__u8
id|name_len
suffix:semicolon
DECL|member|value_len
id|__le16
id|value_len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* optionally followed by value */
)brace
suffix:semicolon
multiline_comment|/* flags for _FEA.fEA */
DECL|macro|FEA_NEEDEA
mdefine_line|#define FEA_NEEDEA         0x80&t;/* need EA bit */
DECL|struct|fealist
r_struct
id|fealist
(brace
DECL|member|list_len
id|__le32
id|list_len
suffix:semicolon
DECL|member|list
r_struct
id|fea
id|list
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used to hold an arbitrary blob of data */
DECL|struct|data_blob
r_struct
id|data_blob
(brace
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|data_blob
op_star
id|data_blob
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_CIFS_POSIX
multiline_comment|/* &n;&t;For better POSIX semantics from Linux client, (even better&n;&t;than the existing CIFS Unix Extensions) we need updated PDUs for:&n;&t;&n;&t;1) PosixCreateX - to set and return the mode, inode#, device info and&n;&t;perhaps add a CreateDevice - to create Pipes and other special .inodes&n;&t;Also note POSIX open flags&n;&t;2) Close - to return the last write time to do cache across close more safely&n;&t;3) PosixQFSInfo - to return statfs info&n;&t;4) FindFirst return unique inode number - what about resume key, two forms short (matches readdir) and full (enough info to cache inodes)&n;&t;5) Mkdir - set mode&n;&t;&n;&t;And under consideration: &n;&t;6) FindClose2 (return nanosecond timestamp ??)&n;&t;7) Use nanosecond timestamps throughout all time fields if &n;&t;   corresponding attribute flag is set&n;&t;8) sendfile - handle based copy&n;&t;9) Direct i/o&n;&t;10) &quot;POSIX ACL&quot; support&n;&t;11) Misc fcntls?&n;&t;&n;&t;what about fixing 64 bit alignment&n;&t;&n;&t;There are also various legacy SMB/CIFS requests used as is&n;&t;&n;&t;From existing Lanman and NTLM dialects:&n;&t;--------------------------------------&n;&t;NEGOTIATE&n;&t;SESSION_SETUP_ANDX (BB which?)&n;&t;TREE_CONNECT_ANDX (BB which wct?)&n;&t;TREE_DISCONNECT (BB add volume timestamp on response)&n;&t;LOGOFF_ANDX&n;&t;DELETE (note delete open file behavior)&n;&t;DELETE_DIRECTORY&n;&t;READ_AND_X&n;&t;WRITE_AND_X&n;&t;LOCKING_AND_X (note posix lock semantics)&n;&t;RENAME (note rename across dirs and open file rename posix behaviors)&n;&t;NT_RENAME (for hardlinks) Is this good enough for all features?&n;&t;FIND_CLOSE2&n;&t;TRANSACTION2 (18 cases)&n;&t;&t;SMB_SET_FILE_END_OF_FILE_INFO2 SMB_SET_PATH_END_OF_FILE_INFO2&n;&t;&t;(BB verify that never need to set allocation size)&n;&t;&t;SMB_SET_FILE_BASIC_INFO2 (setting times - BB can it be done via Unix ext?)&n;&t;&n;&t;COPY (note support for copy across directories) - FUTURE, OPTIONAL&n;&t;setting/getting OS/2 EAs - FUTURE (BB can this handle&n;&t;setting Linux xattrs perfectly)         - OPTIONAL&n;&t;dnotify                                 - FUTURE, OPTIONAL&n;&t;quota                                   - FUTURE, OPTIONAL&n;&t;&t;&t;&n;&t;Note that various requests implemented for NT interop such as &n;&t;&t;NT_TRANSACT (IOCTL) QueryReparseInfo&n;&t;are unneeded to servers compliant with the CIFS POSIX extensions&n;&t;&n;&t;From CIFS Unix Extensions:&n;&t;-------------------------&n;&t;T2 SET_PATH_INFO (SMB_SET_FILE_UNIX_LINK) for symlinks&n;&t;T2 SET_PATH_INFO (SMB_SET_FILE_BASIC_INFO2)&n;&t;T2 QUERY_PATH_INFO (SMB_QUERY_FILE_UNIX_LINK)&n;&t;T2 QUERY_PATH_INFO (SMB_QUERY_FILE_UNIX_BASIC) - BB check for missing inode fields&n;&t;&t;&t;&t;&t;Actually need QUERY_FILE_UNIX_INFO since has inode num&n;&t;&t;&t;&t;&t;BB what about a) blksize/blkbits/blocks&n;&t;&t;&t;&t;&t;&t;&t;&t;  b) i_version&n;&t;&t;&t;&t;&t;&t;&t;&t;  c) i_rdev&n;&t;&t;&t;&t;&t;&t;&t;&t;  d) notify mask?&n;&t;&t;&t;&t;&t;&t;&t;&t;  e) generation&n;&t;&t;&t;&t;&t;&t;&t;&t;  f) size_seqcount&n;&t;T2 FIND_FIRST/FIND_NEXT FIND_FILE_UNIX&n;&t;TRANS2_GET_DFS_REFERRAL&t;&t;&t;&t;  - OPTIONAL but recommended&n;&t;T2_QFS_INFO QueryDevice/AttributeInfo - OPTIONAL&n;&t;&n;&t;&n; */
multiline_comment|/* xsymlink is a symlink format that can be used&n;   to save symlink info in a regular file when &n;   mounted to operating systems that do not&n;   support the cifs Unix extensions or EAs (for xattr&n;   based symlinks).  For such a file to be recognized&n;   as containing symlink data: &n;&n;   1) file size must be 1067, &n;   2) signature must begin file data,&n;   3) length field must be set to ASCII representation&n;&t;of a number which is less than or equal to 1024, &n;   4) md5 must match that of the path data */
DECL|struct|xsymlink
r_struct
id|xsymlink
(brace
multiline_comment|/* 1067 bytes */
DECL|member|signature
r_char
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* XSym */
multiline_comment|/* not null terminated */
DECL|member|cr0
r_char
id|cr0
suffix:semicolon
multiline_comment|/* &bslash;n */
multiline_comment|/* ASCII representation of length (4 bytes decimal) terminated by &bslash;n not null */
DECL|member|length
r_char
id|length
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cr1
r_char
id|cr1
suffix:semicolon
multiline_comment|/* &bslash;n */
multiline_comment|/* md5 of valid subset of path ie path[0] through path[length-1] */
DECL|member|md5
id|__u8
id|md5
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|cr2
r_char
id|cr2
suffix:semicolon
multiline_comment|/* &bslash;n */
multiline_comment|/* if room left, then end with &bslash;n then 0x20s by convention but not required */
DECL|member|path
r_char
id|path
(braket
l_int|1024
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif 
macro_line|#pragma pack()&t;&t;&t;/* resume default structure packing */
macro_line|#endif&t;&t;&t;&t;/* _CIFSPDU_H */
eof
