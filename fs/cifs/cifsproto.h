multiline_comment|/*&n; *   fs/cifs/cifsproto.h&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#ifndef _CIFSPROTO_H
DECL|macro|_CIFSPROTO_H
mdefine_line|#define _CIFSPROTO_H
macro_line|#include &lt;linux/nls.h&gt;
r_struct
id|statfs
suffix:semicolon
multiline_comment|/*&n; *****************************************************************&n; * All Prototypes&n; *****************************************************************&n; */
r_extern
r_struct
id|smb_hdr
op_star
id|cifs_buf_get
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cifs_buf_release
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|smb_send
c_func
(paren
r_struct
id|socket
op_star
comma
r_struct
id|smb_hdr
op_star
comma
r_int
r_int
multiline_comment|/* length */
comma
r_struct
id|sockaddr
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_GetXid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|_FreeXid
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|GetXid
mdefine_line|#define GetXid() (int)_GetXid(); cFYI(1,(&quot;CIFS VFS: in %s as Xid: %d with uid: %d&quot;,__FUNCTION__, xid,current-&gt;fsuid));
DECL|macro|FreeXid
mdefine_line|#define FreeXid(curr_xid) {_FreeXid(curr_xid); cFYI(1,(&quot;CIFS VFS: leaving %s (xid = %d) rc = %d&quot;,__FUNCTION__,curr_xid,(int)rc));}
r_extern
r_char
op_star
id|build_path_from_dentry
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|build_wildcard_path_from_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
)paren
suffix:semicolon
r_extern
r_void
id|renew_parental_timestamps
c_func
(paren
r_struct
id|dentry
op_star
id|direntry
)paren
suffix:semicolon
r_extern
r_int
id|SendReceive
c_func
(paren
r_const
r_int
r_int
multiline_comment|/* xid */
comma
r_struct
id|cifsSesInfo
op_star
comma
r_struct
id|smb_hdr
op_star
multiline_comment|/* input */
comma
r_struct
id|smb_hdr
op_star
multiline_comment|/* out */
comma
r_int
op_star
multiline_comment|/* bytes returned */
comma
r_const
r_int
id|long_op
)paren
suffix:semicolon
r_extern
r_int
id|checkSMBhdr
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb
comma
id|__u16
id|mid
)paren
suffix:semicolon
r_extern
r_int
id|checkSMB
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb
comma
id|__u16
id|mid
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|is_valid_oplock_break
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|smbCalcSize
c_func
(paren
r_struct
id|smb_hdr
op_star
id|ptr
)paren
suffix:semicolon
r_extern
r_int
id|decode_negTokenInit
c_func
(paren
r_int
r_char
op_star
id|security_blob
comma
r_int
id|length
comma
r_enum
id|securityEnum
op_star
id|secType
)paren
suffix:semicolon
r_extern
r_int
id|map_smb_to_linux_error
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb
)paren
suffix:semicolon
r_extern
r_void
id|header_assemble
c_func
(paren
r_struct
id|smb_hdr
op_star
comma
r_char
multiline_comment|/* command */
comma
r_const
r_struct
id|cifsTconInfo
op_star
comma
r_int
multiline_comment|/* length of fixed section (word count) in two byte units  */
)paren
suffix:semicolon
r_struct
id|oplock_q_entry
op_star
id|AllocOplockQEntry
c_func
(paren
r_struct
id|inode
op_star
comma
id|u16
comma
r_struct
id|cifsTconInfo
op_star
)paren
suffix:semicolon
r_void
id|DeleteOplockQEntry
c_func
(paren
r_struct
id|oplock_q_entry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|timespec
id|cifs_NTtimeToUnix
c_func
(paren
id|u64
multiline_comment|/* utc nanoseconds since 1601 */
)paren
suffix:semicolon
r_extern
id|u64
id|cifs_UnixTimeToNT
c_func
(paren
r_struct
id|timespec
)paren
suffix:semicolon
r_extern
r_int
id|cifs_get_inode_info
c_func
(paren
r_struct
id|inode
op_star
op_star
id|pinode
comma
r_const
r_int
r_char
op_star
id|search_path
comma
id|FILE_ALL_INFO
op_star
id|pfile_info
comma
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|xid
)paren
suffix:semicolon
r_extern
r_int
id|cifs_get_inode_info_unix
c_func
(paren
r_struct
id|inode
op_star
op_star
id|pinode
comma
r_const
r_int
r_char
op_star
id|search_path
comma
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|xid
)paren
suffix:semicolon
r_extern
r_int
id|cifs_setup_session
c_func
(paren
r_int
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|pSesInfo
comma
r_struct
id|nls_table
op_star
id|nls_info
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBNegotiate
c_func
(paren
r_int
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|ses
)paren
suffix:semicolon
r_extern
r_int
id|CIFSTCon
c_func
(paren
r_int
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|ses
comma
r_const
r_char
op_star
id|tree
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_struct
id|nls_table
op_star
)paren
suffix:semicolon
r_extern
r_int
id|CIFSFindFirst
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|searchName
comma
id|FILE_DIRECTORY_INFO
op_star
id|findData
comma
id|T2_FFIRST_RSP_PARMS
op_star
id|findParms
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
comma
r_int
op_star
id|pUnicodeFlag
comma
r_int
op_star
id|pUnixFlag
multiline_comment|/* if Unix extensions used */
)paren
suffix:semicolon
r_extern
r_int
id|CIFSFindNext
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
id|FILE_DIRECTORY_INFO
op_star
id|findData
comma
id|T2_FNEXT_RSP_PARMS
op_star
id|findParms
comma
r_const
id|__u16
id|searchHandle
comma
r_char
op_star
id|resume_name
comma
r_int
id|name_length
comma
id|__u32
id|resume_key
comma
r_int
op_star
id|UnicodeFlag
comma
r_int
op_star
id|pUnixFlag
)paren
suffix:semicolon
r_extern
r_int
id|CIFSFindClose
c_func
(paren
r_const
r_int
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
id|__u16
id|search_handle
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQPathInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
id|FILE_ALL_INFO
op_star
id|findData
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBUnixQPathInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
id|FILE_UNIX_BASIC_INFO
op_star
id|pFindData
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSGetDFSRefer
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|ses
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_int
r_char
op_star
op_star
id|targetUNCs
comma
r_int
r_int
op_star
id|number_of_UNC_in_array
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|connect_to_dfs_path
c_func
(paren
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|pSesInfo
comma
r_const
r_char
op_star
id|old_path
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|get_dfs_path
c_func
(paren
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|pSesInfo
comma
r_const
r_char
op_star
id|old_path
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
comma
r_int
r_int
op_star
id|pnum_referrals
comma
r_int
r_char
op_star
op_star
id|preferrals
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQFSInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_struct
id|kstatfs
op_star
id|FSData
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQFSAttributeInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQFSDeviceInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQFSUnixInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBSetTimes
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fileName
comma
r_const
id|FILE_BASIC_INFO
op_star
id|data
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBSetEOF
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fileName
comma
id|__u64
id|size
comma
r_int
id|setAllocationSizeFlag
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBSetFileSize
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
id|__u64
id|size
comma
id|__u16
id|fileHandle
comma
id|__u32
id|opener_pid
comma
r_int
id|AllocSizeFlag
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBUnixSetPerms
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|pTcon
comma
r_char
op_star
id|full_path
comma
id|__u64
id|mode
comma
id|__u64
id|uid
comma
id|__u64
id|gid
comma
id|dev_t
id|dev
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBMkDir
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|newName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBRmDir
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|name
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBDelFile
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|name
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBRename
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fromName
comma
r_const
r_char
op_star
id|toName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBRenameOpenFile
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|pTcon
comma
r_int
id|netfid
comma
r_char
op_star
id|target_name
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSCreateHardLink
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fromName
comma
r_const
r_char
op_star
id|toName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSUnixCreateHardLink
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fromName
comma
r_const
r_char
op_star
id|toName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSUnixCreateSymLink
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fromName
comma
r_const
r_char
op_star
id|toName
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBUnixQuerySymLink
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_char
op_star
id|syminfo
comma
r_const
r_int
id|buflen
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBQueryReparseLinkInfo
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_char
op_star
id|symlinkinfo
comma
r_const
r_int
id|buflen
comma
id|__u16
id|fid
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBOpen
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fileName
comma
r_const
r_int
id|disposition
comma
r_const
r_int
id|access_flags
comma
r_const
r_int
id|omode
comma
id|__u16
op_star
id|netfid
comma
r_int
op_star
id|pOplock
comma
id|FILE_ALL_INFO
op_star
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBClose
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
id|smb_file_id
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBRead
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
id|netfid
comma
r_int
r_int
id|count
comma
r_const
id|__u64
id|lseek
comma
r_int
r_int
op_star
id|nbytes
comma
r_char
op_star
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBWrite
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
id|netfid
comma
r_const
r_int
r_int
id|count
comma
r_const
id|__u64
id|lseek
comma
r_int
r_int
op_star
id|nbytes
comma
r_const
r_char
op_star
id|buf
comma
r_const
r_int
id|long_op
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBLock
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
id|__u16
id|netfid
comma
r_const
id|__u64
id|len
comma
r_const
id|__u64
id|offset
comma
r_const
id|__u32
id|numUnlock
comma
r_const
id|__u32
id|numLock
comma
r_const
id|__u8
id|lockType
comma
r_const
r_int
id|waitFlag
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBTDis
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBLogoff
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|ses
)paren
suffix:semicolon
r_extern
r_struct
id|cifsSesInfo
op_star
id|sesInfoAlloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sesInfoFree
c_func
(paren
r_struct
id|cifsSesInfo
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|cifsTconInfo
op_star
id|tconInfoAlloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tconInfoFree
c_func
(paren
r_struct
id|cifsTconInfo
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_reconnect
c_func
(paren
r_struct
id|TCP_Server_Info
op_star
id|server
)paren
suffix:semicolon
r_extern
r_int
id|cifs_sign_smb
c_func
(paren
r_struct
id|smb_hdr
op_star
comma
r_struct
id|cifsSesInfo
op_star
comma
id|__u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cifs_verify_signature
c_func
(paren
r_const
r_struct
id|smb_hdr
op_star
comma
r_const
r_char
op_star
id|mac_key
comma
id|__u32
id|expected_sequence_number
)paren
suffix:semicolon
r_extern
r_int
id|cifs_calculate_mac_key
c_func
(paren
r_char
op_star
id|key
comma
r_const
r_char
op_star
id|rn
comma
r_const
r_char
op_star
id|pass
)paren
suffix:semicolon
r_extern
r_void
id|CalcNTLMv2_partial_mac_key
c_func
(paren
r_struct
id|cifsSesInfo
op_star
comma
r_struct
id|nls_table
op_star
)paren
suffix:semicolon
r_extern
r_void
id|CalcNTLMv2_response
c_func
(paren
r_const
r_struct
id|cifsSesInfo
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBCopy
c_func
(paren
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|source_tcon
comma
r_const
r_char
op_star
id|fromName
comma
r_const
id|__u16
id|target_tid
comma
r_const
r_char
op_star
id|toName
comma
r_const
r_int
id|flags
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBNotify
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
id|notify_subdirs
comma
r_const
id|__u16
id|netfid
comma
id|__u32
id|filter
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
id|ssize_t
id|CIFSSMBQAllEAs
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_char
op_star
id|EAData
comma
r_int
id|bufsize
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
id|ssize_t
id|CIFSSMBQueryEA
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_const
r_int
r_char
op_star
id|ea_name
comma
r_int
r_char
op_star
id|ea_value
comma
r_int
id|buf_size
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBSetEA
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_char
op_star
id|fileName
comma
r_const
r_char
op_star
id|ea_name
comma
r_const
r_void
op_star
id|ea_value
comma
r_const
id|__u16
id|ea_value_len
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBGetPosixACL
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|searchName
comma
r_char
op_star
id|acl_inf
comma
r_const
r_int
id|buflen
comma
r_const
r_int
id|acl_type
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
r_extern
r_int
id|CIFSSMBSetPosixACL
c_func
(paren
r_const
r_int
id|xid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
comma
r_const
r_int
r_char
op_star
id|fileName
comma
r_const
r_char
op_star
id|local_acl
comma
r_const
r_int
id|buflen
comma
r_const
r_int
id|acl_type
comma
r_const
r_struct
id|nls_table
op_star
id|nls_codepage
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;/* _CIFSPROTO_H */
eof
