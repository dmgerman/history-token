multiline_comment|/*&n; *   fs/cifs/cifsglob.h&n; *&n; *   Copyright (C) International Business Machines  Corp., 2002,2003&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; * &n; */
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &quot;cifs_fs_sb.h&quot;
multiline_comment|/*&n; * The sizes of various internal tables and strings&n; */
DECL|macro|MAX_UID_INFO
mdefine_line|#define MAX_UID_INFO 16
DECL|macro|MAX_SES_INFO
mdefine_line|#define MAX_SES_INFO 2
DECL|macro|MAX_TCON_INFO
mdefine_line|#define MAX_TCON_INFO 4
DECL|macro|MAX_TREE_SIZE
mdefine_line|#define MAX_TREE_SIZE 2 + MAX_SERVER_SIZE + 1 + MAX_SHARE_SIZE + 1
DECL|macro|MAX_SERVER_SIZE
mdefine_line|#define MAX_SERVER_SIZE 15
DECL|macro|MAX_SHARE_SIZE
mdefine_line|#define MAX_SHARE_SIZE  64&t;/* used to be 20 - this should still be enough */
DECL|macro|MAX_USERNAME_SIZE
mdefine_line|#define MAX_USERNAME_SIZE 32&t;/* 32 is to allow for 15 char names + null&n;&t;&t;&t;&t;   termination then *2 for unicode versions */
DECL|macro|MAX_PASSWORD_SIZE
mdefine_line|#define MAX_PASSWORD_SIZE 16
DECL|macro|CIFS_MIN_RCV_POOL
mdefine_line|#define CIFS_MIN_RCV_POOL 4
multiline_comment|/*&n; * MAX_REQ is the maximum number of requests that WE will send&n; * on one socket concurently. It also matches the most common&n; * value of max multiplex returned by servers.  We may &n; * eventually want to use the negotiated value (in case&n; * future servers can handle more) when we are more confident that&n; * we will not have problems oveloading the socket with pending&n; * write data.&n; */
DECL|macro|CIFS_MAX_REQ
mdefine_line|#define CIFS_MAX_REQ 50 
DECL|macro|SERVER_NAME_LENGTH
mdefine_line|#define SERVER_NAME_LENGTH 15
DECL|macro|SERVER_NAME_LEN_WITH_NULL
mdefine_line|#define SERVER_NAME_LEN_WITH_NULL     (SERVER_NAME_LENGTH + 1)
multiline_comment|/* used to define string lengths for reversing unicode strings */
multiline_comment|/*         (256+1)*2 = 514                                     */
multiline_comment|/*           (max path length + 1 for null) * 2 for unicode    */
DECL|macro|MAX_NAME
mdefine_line|#define MAX_NAME 514
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef XATTR_DOS_ATTRIB
DECL|macro|XATTR_DOS_ATTRIB
mdefine_line|#define XATTR_DOS_ATTRIB &quot;user.DOSATTRIB&quot;
macro_line|#endif
multiline_comment|/*&n; * This information is kept on every Server we know about.&n; *&n; * Some things to note:&n; *&n; */
DECL|macro|SERVER_NAME_LEN_WITH_NULL
mdefine_line|#define SERVER_NAME_LEN_WITH_NULL&t;(SERVER_NAME_LENGTH + 1)
multiline_comment|/*&n; * CIFS vfs client Status information (based on what we know.)&n; */
multiline_comment|/* associated with each tcp and smb session */
DECL|enum|statusEnum
r_enum
id|statusEnum
(brace
DECL|enumerator|CifsNew
id|CifsNew
op_assign
l_int|0
comma
DECL|enumerator|CifsGood
id|CifsGood
comma
DECL|enumerator|CifsExiting
id|CifsExiting
comma
DECL|enumerator|CifsNeedReconnect
id|CifsNeedReconnect
)brace
suffix:semicolon
DECL|enum|securityEnum
r_enum
id|securityEnum
(brace
DECL|enumerator|NTLM
id|NTLM
op_assign
l_int|0
comma
multiline_comment|/* Legacy NTLM012 auth with NTLM hash */
DECL|enumerator|NTLMv2
id|NTLMv2
comma
multiline_comment|/* Legacy NTLM auth with NTLMv2 hash */
DECL|enumerator|RawNTLMSSP
id|RawNTLMSSP
comma
multiline_comment|/* NTLMSSP without SPNEGO */
DECL|enumerator|NTLMSSP
id|NTLMSSP
comma
multiline_comment|/* NTLMSSP via SPNEGO */
DECL|enumerator|Kerberos
id|Kerberos
multiline_comment|/* Kerberos via SPNEGO */
)brace
suffix:semicolon
DECL|enum|protocolEnum
r_enum
id|protocolEnum
(brace
DECL|enumerator|IPV4
id|IPV4
op_assign
l_int|0
comma
DECL|enumerator|IPV6
id|IPV6
comma
DECL|enumerator|SCTP
id|SCTP
multiline_comment|/* Netbios frames protocol not supported at this time */
)brace
suffix:semicolon
multiline_comment|/*&n; *****************************************************************&n; * Except the CIFS PDUs themselves all the&n; * globally interesting structs should go here&n; *****************************************************************&n; */
DECL|struct|TCP_Server_Info
r_struct
id|TCP_Server_Info
(brace
DECL|member|server_Name
r_char
id|server_Name
(braket
id|SERVER_NAME_LEN_WITH_NULL
)braket
suffix:semicolon
multiline_comment|/* 15 chars + X&squot;20&squot;in 16th */
DECL|member|unicode_server_Name
r_char
id|unicode_server_Name
(braket
id|SERVER_NAME_LEN_WITH_NULL
op_star
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Unicode version of server_Name */
DECL|member|ssocket
r_struct
id|socket
op_star
id|ssocket
suffix:semicolon
r_union
(brace
DECL|member|sockAddr
r_struct
id|sockaddr_in
id|sockAddr
suffix:semicolon
DECL|member|sockAddr6
r_struct
id|sockaddr_in6
id|sockAddr6
suffix:semicolon
DECL|member|addr
)brace
id|addr
suffix:semicolon
DECL|member|response_q
id|wait_queue_head_t
id|response_q
suffix:semicolon
DECL|member|request_q
id|wait_queue_head_t
id|request_q
suffix:semicolon
multiline_comment|/* if more than maxmpx to srvr must block*/
DECL|member|pending_mid_q
r_struct
id|list_head
id|pending_mid_q
suffix:semicolon
DECL|member|Server_NlsInfo
r_void
op_star
id|Server_NlsInfo
suffix:semicolon
multiline_comment|/* BB - placeholder for future NLS info  */
DECL|member|server_codepage
r_int
r_int
id|server_codepage
suffix:semicolon
multiline_comment|/* codepage for the server    */
DECL|member|ip_address
r_int
r_int
id|ip_address
suffix:semicolon
multiline_comment|/* IP addr for the server if known     */
DECL|member|protocolType
r_enum
id|protocolEnum
id|protocolType
suffix:semicolon
DECL|member|versionMajor
r_char
id|versionMajor
suffix:semicolon
DECL|member|versionMinor
r_char
id|versionMinor
suffix:semicolon
DECL|member|svlocal
r_int
id|svlocal
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* local server or remote */
DECL|member|socketUseCount
id|atomic_t
id|socketUseCount
suffix:semicolon
multiline_comment|/* number of open cifs sessions on socket */
DECL|member|inFlight
id|atomic_t
id|inFlight
suffix:semicolon
multiline_comment|/* number of requests on the wire to server */
DECL|member|tcpStatus
r_enum
id|statusEnum
id|tcpStatus
suffix:semicolon
multiline_comment|/* what we think the status is */
DECL|member|tcpSem
r_struct
id|semaphore
id|tcpSem
suffix:semicolon
DECL|member|tsk
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
DECL|member|server_GUID
r_char
id|server_GUID
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|secMode
r_char
id|secMode
suffix:semicolon
DECL|member|secType
r_enum
id|securityEnum
id|secType
suffix:semicolon
DECL|member|maxReq
r_int
r_int
id|maxReq
suffix:semicolon
multiline_comment|/* Clients should submit no more */
multiline_comment|/* than maxReq distinct unanswered SMBs to the server when using  */
multiline_comment|/* multiplexed reads or writes */
DECL|member|maxBuf
r_int
r_int
id|maxBuf
suffix:semicolon
multiline_comment|/* maxBuf specifies the maximum */
multiline_comment|/* message size the server can send or receive for non-raw SMBs */
DECL|member|maxRw
r_int
r_int
id|maxRw
suffix:semicolon
multiline_comment|/* maxRw specifies the maximum */
multiline_comment|/* message size the server can send or receive for */
multiline_comment|/* SMB_COM_WRITE_RAW or SMB_COM_READ_RAW. */
DECL|member|sessid
r_char
id|sessid
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* unique token id for this session */
multiline_comment|/* (returned on Negotiate */
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* allow selective disabling of caps by smb sess */
DECL|member|timeZone
id|__u16
id|timeZone
suffix:semicolon
DECL|member|cryptKey
r_char
id|cryptKey
(braket
id|CIFS_CRYPTO_KEY_SIZE
)braket
suffix:semicolon
DECL|member|workstation_RFC1001_name
r_char
id|workstation_RFC1001_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16th byte is always zero */
)brace
suffix:semicolon
multiline_comment|/*&n; * The following is our shortcut to user information.  We surface the uid,&n; * and name. We always get the password on the fly in case it&n; * has changed. We also hang a list of sessions owned by this user off here. &n; */
DECL|struct|cifsUidInfo
r_struct
id|cifsUidInfo
(brace
DECL|member|userList
r_struct
id|list_head
id|userList
suffix:semicolon
DECL|member|sessionList
r_struct
id|list_head
id|sessionList
suffix:semicolon
multiline_comment|/* SMB sessions for this user */
DECL|member|linux_uid
id|uid_t
id|linux_uid
suffix:semicolon
DECL|member|user
r_char
id|user
(braket
id|MAX_USERNAME_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* ascii name of user */
multiline_comment|/* BB may need ptr or callback for PAM or WinBind info */
)brace
suffix:semicolon
multiline_comment|/*&n; * Session structure.  One of these for each uid session with a particular host&n; */
DECL|struct|cifsSesInfo
r_struct
id|cifsSesInfo
(brace
DECL|member|cifsSessionList
r_struct
id|list_head
id|cifsSessionList
suffix:semicolon
DECL|member|sesSem
r_struct
id|semaphore
id|sesSem
suffix:semicolon
DECL|member|uidInfo
r_struct
id|cifsUidInfo
op_star
id|uidInfo
suffix:semicolon
multiline_comment|/* pointer to user info */
DECL|member|server
r_struct
id|TCP_Server_Info
op_star
id|server
suffix:semicolon
multiline_comment|/* pointer to server info */
DECL|member|inUse
id|atomic_t
id|inUse
suffix:semicolon
multiline_comment|/* # of mounts (tree connections) on this ses */
DECL|member|status
r_enum
id|statusEnum
id|status
suffix:semicolon
DECL|member|sequence_number
id|__u32
id|sequence_number
suffix:semicolon
multiline_comment|/* needed for CIFS PDU signature */
DECL|member|ipc_tid
id|__u16
id|ipc_tid
suffix:semicolon
multiline_comment|/* special tid for connection to IPC share */
DECL|member|mac_signing_key
r_char
id|mac_signing_key
(braket
id|CIFS_SESSION_KEY_SIZE
op_plus
l_int|16
)braket
suffix:semicolon
DECL|member|serverOS
r_char
op_star
id|serverOS
suffix:semicolon
multiline_comment|/* name of operating system underlying the server */
DECL|member|serverNOS
r_char
op_star
id|serverNOS
suffix:semicolon
multiline_comment|/* name of network operating system that the server is running */
DECL|member|serverDomain
r_char
op_star
id|serverDomain
suffix:semicolon
multiline_comment|/* security realm of server */
DECL|member|Suid
r_int
id|Suid
suffix:semicolon
multiline_comment|/* remote smb uid  */
DECL|member|linux_uid
id|uid_t
id|linux_uid
suffix:semicolon
multiline_comment|/* local Linux uid */
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
DECL|member|serverName
r_char
id|serverName
(braket
id|SERVER_NAME_LEN_WITH_NULL
op_star
l_int|2
)braket
suffix:semicolon
multiline_comment|/* BB make bigger for tcp names - will ipv6 and sctp addresses fit here?? */
DECL|member|userName
r_char
id|userName
(braket
id|MAX_USERNAME_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|domainName
r_char
id|domainName
(braket
id|MAX_USERNAME_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|password
r_char
op_star
id|password
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * there is one of these for each connection to a resource on a particular&n; * session &n; */
DECL|struct|cifsTconInfo
r_struct
id|cifsTconInfo
(brace
DECL|member|cifsConnectionList
r_struct
id|list_head
id|cifsConnectionList
suffix:semicolon
DECL|member|openFileList
r_struct
id|list_head
id|openFileList
suffix:semicolon
DECL|member|tconSem
r_struct
id|semaphore
id|tconSem
suffix:semicolon
DECL|member|ses
r_struct
id|cifsSesInfo
op_star
id|ses
suffix:semicolon
multiline_comment|/* pointer to session associated with */
DECL|member|treeName
r_char
id|treeName
(braket
id|MAX_TREE_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* UNC name of resource (in ASCII not UTF) */
DECL|member|nativeFileSystem
r_char
op_star
id|nativeFileSystem
suffix:semicolon
DECL|member|tid
id|__u16
id|tid
suffix:semicolon
multiline_comment|/* The 2 byte tree id */
DECL|member|Flags
id|__u16
id|Flags
suffix:semicolon
multiline_comment|/* optional support bits */
DECL|member|tidStatus
r_enum
id|statusEnum
id|tidStatus
suffix:semicolon
DECL|member|useCount
id|atomic_t
id|useCount
suffix:semicolon
multiline_comment|/* how many mounts (explicit or implicit) to this share */
macro_line|#ifdef CONFIG_CIFS_STATS
DECL|member|num_smbs_sent
id|atomic_t
id|num_smbs_sent
suffix:semicolon
DECL|member|num_writes
id|atomic_t
id|num_writes
suffix:semicolon
DECL|member|num_reads
id|atomic_t
id|num_reads
suffix:semicolon
DECL|member|num_oplock_brks
id|atomic_t
id|num_oplock_brks
suffix:semicolon
DECL|member|num_opens
id|atomic_t
id|num_opens
suffix:semicolon
DECL|member|num_deletes
id|atomic_t
id|num_deletes
suffix:semicolon
DECL|member|num_mkdirs
id|atomic_t
id|num_mkdirs
suffix:semicolon
DECL|member|num_rmdirs
id|atomic_t
id|num_rmdirs
suffix:semicolon
DECL|member|num_renames
id|atomic_t
id|num_renames
suffix:semicolon
DECL|member|num_t2renames
id|atomic_t
id|num_t2renames
suffix:semicolon
DECL|member|bytes_read
id|__u64
id|bytes_read
suffix:semicolon
DECL|member|bytes_written
id|__u64
id|bytes_written
suffix:semicolon
DECL|member|stat_lock
id|spinlock_t
id|stat_lock
suffix:semicolon
macro_line|#endif
DECL|member|fsDevInfo
id|FILE_SYSTEM_DEVICE_INFO
id|fsDevInfo
suffix:semicolon
DECL|member|fsAttrInfo
id|FILE_SYSTEM_ATTRIBUTE_INFO
id|fsAttrInfo
suffix:semicolon
multiline_comment|/* ok if file system name truncated */
DECL|member|fsUnixInfo
id|FILE_SYSTEM_UNIX_INFO
id|fsUnixInfo
suffix:semicolon
DECL|member|retry
r_int
id|retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* BB add field for back pointer to sb struct? */
)brace
suffix:semicolon
multiline_comment|/*&n; * This info hangs off the cifsFileInfo structure.  This is used to track&n; * byte stream locks on the file&n; */
DECL|struct|cifsLockInfo
r_struct
id|cifsLockInfo
(brace
DECL|member|next
r_struct
id|cifsLockInfo
op_star
id|next
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * One of these for each open instance of a file&n; */
DECL|struct|cifs_search_info
r_struct
id|cifs_search_info
(brace
DECL|member|index_of_last_entry
id|loff_t
id|index_of_last_entry
suffix:semicolon
DECL|member|entries_in_buffer
id|__u16
id|entries_in_buffer
suffix:semicolon
DECL|member|info_level
id|__u16
id|info_level
suffix:semicolon
DECL|member|resume_key
id|__u32
id|resume_key
suffix:semicolon
DECL|member|ntwrk_buf_start
r_char
op_star
id|ntwrk_buf_start
suffix:semicolon
DECL|member|srch_entries_start
r_char
op_star
id|srch_entries_start
suffix:semicolon
DECL|member|presume_name
r_char
op_star
id|presume_name
suffix:semicolon
DECL|member|resume_name_len
r_int
r_int
id|resume_name_len
suffix:semicolon
DECL|member|endOfSearch
r_int
id|endOfSearch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|emptyDir
r_int
id|emptyDir
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unicode
r_int
id|unicode
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cifsFileInfo
r_struct
id|cifsFileInfo
(brace
DECL|member|tlist
r_struct
id|list_head
id|tlist
suffix:semicolon
multiline_comment|/* pointer to next fid owned by tcon */
DECL|member|flist
r_struct
id|list_head
id|flist
suffix:semicolon
multiline_comment|/* next fid (file instance) for this inode */
DECL|member|uid
r_int
r_int
id|uid
suffix:semicolon
multiline_comment|/* allows finding which FileInfo structure */
DECL|member|pid
id|__u32
id|pid
suffix:semicolon
multiline_comment|/* process id who opened file */
DECL|member|netfid
id|__u16
id|netfid
suffix:semicolon
multiline_comment|/* file id from remote */
multiline_comment|/* BB add lock scope info here if needed */
suffix:semicolon
multiline_comment|/* lock scope id (0 if none) */
DECL|member|pfile
r_struct
id|file
op_star
id|pfile
suffix:semicolon
multiline_comment|/* needed for writepage */
DECL|member|pInode
r_struct
id|inode
op_star
id|pInode
suffix:semicolon
multiline_comment|/* needed for oplock break */
DECL|member|closePend
r_int
id|closePend
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* file is marked to close */
DECL|member|invalidHandle
r_int
id|invalidHandle
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* file closed via session abend */
DECL|member|fh_sem
r_struct
id|semaphore
id|fh_sem
suffix:semicolon
multiline_comment|/* prevents reopen race after dead ses*/
DECL|member|search_resume_name
r_char
op_star
id|search_resume_name
suffix:semicolon
multiline_comment|/* BB removeme BB */
DECL|member|resume_name_length
r_int
r_int
id|resume_name_length
suffix:semicolon
multiline_comment|/* BB removeme - field renamed and moved BB */
DECL|member|srch_inf
r_struct
id|cifs_search_info
id|srch_inf
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * One of these for each file inode&n; */
DECL|struct|cifsInodeInfo
r_struct
id|cifsInodeInfo
(brace
DECL|member|lockList
r_struct
id|list_head
id|lockList
suffix:semicolon
multiline_comment|/* BB add in lists for dirty pages - i.e. write caching info for oplock */
DECL|member|openFileList
r_struct
id|list_head
id|openFileList
suffix:semicolon
DECL|member|write_behind_rc
r_int
id|write_behind_rc
suffix:semicolon
DECL|member|cifsAttrs
id|__u32
id|cifsAttrs
suffix:semicolon
multiline_comment|/* e.g. DOS archive bit, sparse, compressed, system */
DECL|member|inUse
id|atomic_t
id|inUse
suffix:semicolon
multiline_comment|/* num concurrent users (local openers cifs) of file*/
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/* jiffies of last update/check of inode */
DECL|member|clientCanCacheRead
r_int
id|clientCanCacheRead
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* read oplock */
DECL|member|clientCanCacheAll
r_int
id|clientCanCacheAll
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* read and writebehind oplock */
DECL|member|oplockPending
r_int
id|oplockPending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_struct
id|cifsInodeInfo
op_star
DECL|function|CIFS_I
id|CIFS_I
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
r_struct
id|cifsInodeInfo
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|cifs_sb_info
op_star
DECL|function|CIFS_SB
id|CIFS_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
multiline_comment|/* one of these for every pending CIFS request to the server */
DECL|struct|mid_q_entry
r_struct
id|mid_q_entry
(brace
DECL|member|qhead
r_struct
id|list_head
id|qhead
suffix:semicolon
multiline_comment|/* mids waiting on reply from this server */
DECL|member|mid
id|__u16
id|mid
suffix:semicolon
multiline_comment|/* multiplex id */
DECL|member|pid
id|__u16
id|pid
suffix:semicolon
multiline_comment|/* process id */
DECL|member|sequence_number
id|__u32
id|sequence_number
suffix:semicolon
multiline_comment|/* for CIFS signing */
DECL|member|command
id|__u16
id|command
suffix:semicolon
multiline_comment|/* smb command code */
DECL|member|when_sent
r_struct
id|timeval
id|when_sent
suffix:semicolon
multiline_comment|/* time when smb sent */
DECL|member|ses
r_struct
id|cifsSesInfo
op_star
id|ses
suffix:semicolon
multiline_comment|/* smb was sent to this server */
DECL|member|tsk
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
multiline_comment|/* task waiting for response */
DECL|member|resp_buf
r_struct
id|smb_hdr
op_star
id|resp_buf
suffix:semicolon
multiline_comment|/* response buffer */
DECL|member|midState
r_int
id|midState
suffix:semicolon
multiline_comment|/* wish this were enum but can not pass to wait_event */
)brace
suffix:semicolon
DECL|struct|oplock_q_entry
r_struct
id|oplock_q_entry
(brace
DECL|member|qhead
r_struct
id|list_head
id|qhead
suffix:semicolon
DECL|member|pinode
r_struct
id|inode
op_star
id|pinode
suffix:semicolon
DECL|member|tcon
r_struct
id|cifsTconInfo
op_star
id|tcon
suffix:semicolon
DECL|member|netfid
id|__u16
id|netfid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MID_FREE
mdefine_line|#define   MID_FREE 0
DECL|macro|MID_REQUEST_ALLOCATED
mdefine_line|#define   MID_REQUEST_ALLOCATED 1
DECL|macro|MID_REQUEST_SUBMITTED
mdefine_line|#define   MID_REQUEST_SUBMITTED 2
DECL|macro|MID_RESPONSE_RECEIVED
mdefine_line|#define   MID_RESPONSE_RECEIVED 4
DECL|macro|MID_RETRY_NEEDED
mdefine_line|#define   MID_RETRY_NEEDED      8 /* session closed while this request out */
DECL|macro|MID_NO_RESP_NEEDED
mdefine_line|#define   MID_NO_RESP_NEEDED 0x10
DECL|macro|MID_SMALL_BUFFER
mdefine_line|#define   MID_SMALL_BUFFER   0x20 /* 112 byte response buffer instead of 4K */
multiline_comment|/*&n; *****************************************************************&n; * All constants go here&n; *****************************************************************&n; */
DECL|macro|UID_HASH
mdefine_line|#define UID_HASH (16)
multiline_comment|/*&n; * Note that ONE module should define _DECLARE_GLOBALS_HERE to cause the&n; * following to be declared.&n; */
multiline_comment|/****************************************************************************&n; *  Locking notes.  All updates to global variables and lists should be&n; *                  protected by spinlocks or semaphores.&n; *&n; *  Spinlocks&n; *  ---------&n; *  GlobalMid_Lock protects:&n; *&t;list operations on pending_mid_q and oplockQ&n; *      updates to XID counters, multiplex id  and SMB sequence numbers&n; *  GlobalSMBSesLock protects:&n; *&t;list operations on tcp and SMB session lists and tCon lists&n; *  f_owner.lock protects certain per file struct operations&n; *  mapping-&gt;page_lock protects certain per page operations&n; *&n; *  Semaphores&n; *  ----------&n; *  sesSem     operations on smb session&n; *  tconSem    operations on tree connection&n; *  fh_sem      file handle reconnection operations &n; *&n; ****************************************************************************/
macro_line|#ifdef DECLARE_GLOBALS_HERE
DECL|macro|GLOBAL_EXTERN
mdefine_line|#define GLOBAL_EXTERN
macro_line|#else
DECL|macro|GLOBAL_EXTERN
mdefine_line|#define GLOBAL_EXTERN extern
macro_line|#endif
multiline_comment|/*&n; * The list of servers that did not respond with NT LM 0.12.&n; * This list helps improve performance and eliminate the messages indicating&n; * that we had a communications error talking to the server in this list. &n; */
DECL|variable|NotSuppList
id|GLOBAL_EXTERN
r_struct
id|servers_not_supported
op_star
id|NotSuppList
suffix:semicolon
multiline_comment|/*@z4a */
multiline_comment|/*&n; * The following is a hash table of all the users we know about.&n; */
DECL|variable|GlobalUidList
id|GLOBAL_EXTERN
r_struct
id|smbUidInfo
op_star
id|GlobalUidList
(braket
id|UID_HASH
)braket
suffix:semicolon
DECL|variable|GlobalServerList
id|GLOBAL_EXTERN
r_struct
id|list_head
id|GlobalServerList
suffix:semicolon
multiline_comment|/* BB not implemented yet */
DECL|variable|GlobalSMBSessionList
id|GLOBAL_EXTERN
r_struct
id|list_head
id|GlobalSMBSessionList
suffix:semicolon
DECL|variable|GlobalTreeConnectionList
id|GLOBAL_EXTERN
r_struct
id|list_head
id|GlobalTreeConnectionList
suffix:semicolon
DECL|variable|GlobalSMBSeslock
id|GLOBAL_EXTERN
id|rwlock_t
id|GlobalSMBSeslock
suffix:semicolon
multiline_comment|/* protects list inserts on 3 above */
DECL|variable|GlobalOplock_Q
id|GLOBAL_EXTERN
r_struct
id|list_head
id|GlobalOplock_Q
suffix:semicolon
multiline_comment|/*&n; * Global transaction id (XID) information&n; */
DECL|variable|GlobalCurrentXid
id|GLOBAL_EXTERN
r_int
r_int
id|GlobalCurrentXid
suffix:semicolon
multiline_comment|/* protected by GlobalMid_Sem */
DECL|variable|GlobalTotalActiveXid
id|GLOBAL_EXTERN
r_int
r_int
id|GlobalTotalActiveXid
suffix:semicolon
multiline_comment|/* prot by GlobalMid_Sem */
DECL|variable|GlobalMaxActiveXid
id|GLOBAL_EXTERN
r_int
r_int
id|GlobalMaxActiveXid
suffix:semicolon
multiline_comment|/* prot by GlobalMid_Sem */
DECL|variable|GlobalMid_Lock
id|GLOBAL_EXTERN
id|spinlock_t
id|GlobalMid_Lock
suffix:semicolon
multiline_comment|/* protects above and list operations */
multiline_comment|/* on midQ entries */
DECL|variable|Local_System_Name
id|GLOBAL_EXTERN
r_char
id|Local_System_Name
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/*&n; *  Global counters, updated atomically&n; */
DECL|variable|sesInfoAllocCount
id|GLOBAL_EXTERN
id|atomic_t
id|sesInfoAllocCount
suffix:semicolon
DECL|variable|tconInfoAllocCount
id|GLOBAL_EXTERN
id|atomic_t
id|tconInfoAllocCount
suffix:semicolon
DECL|variable|tcpSesAllocCount
id|GLOBAL_EXTERN
id|atomic_t
id|tcpSesAllocCount
suffix:semicolon
DECL|variable|tcpSesReconnectCount
id|GLOBAL_EXTERN
id|atomic_t
id|tcpSesReconnectCount
suffix:semicolon
DECL|variable|tconInfoReconnectCount
id|GLOBAL_EXTERN
id|atomic_t
id|tconInfoReconnectCount
suffix:semicolon
multiline_comment|/* Various Debug counters to remove someday (BB) */
DECL|variable|bufAllocCount
id|GLOBAL_EXTERN
id|atomic_t
id|bufAllocCount
suffix:semicolon
macro_line|#ifdef CONFIG_CIFS_EXPERIMENTAL
DECL|variable|smBufAllocCount
id|GLOBAL_EXTERN
id|atomic_t
id|smBufAllocCount
suffix:semicolon
macro_line|#endif /* CIFS_EXPERIMENTAL */
DECL|variable|midCount
id|GLOBAL_EXTERN
id|atomic_t
id|midCount
suffix:semicolon
multiline_comment|/* Misc globals */
DECL|variable|multiuser_mount
id|GLOBAL_EXTERN
r_int
r_int
id|multiuser_mount
suffix:semicolon
multiline_comment|/* if enabled allows new sessions&n;&t;&t;&t;&t;to be established on existing mount if we&n;&t;&t;&t;&t;have the uid/password or Kerberos credential &n;&t;&t;&t;&t;or equivalent for current user */
DECL|variable|oplockEnabled
id|GLOBAL_EXTERN
r_int
r_int
id|oplockEnabled
suffix:semicolon
DECL|variable|experimEnabled
id|GLOBAL_EXTERN
r_int
r_int
id|experimEnabled
suffix:semicolon
DECL|variable|lookupCacheEnabled
id|GLOBAL_EXTERN
r_int
r_int
id|lookupCacheEnabled
suffix:semicolon
DECL|variable|extended_security
id|GLOBAL_EXTERN
r_int
r_int
id|extended_security
suffix:semicolon
multiline_comment|/* if on, session setup sent &n;&t;&t;&t;&t;with more secure ntlmssp2 challenge/resp */
DECL|variable|ntlmv2_support
id|GLOBAL_EXTERN
r_int
r_int
id|ntlmv2_support
suffix:semicolon
multiline_comment|/* better optional password hash */
DECL|variable|sign_CIFS_PDUs
id|GLOBAL_EXTERN
r_int
r_int
id|sign_CIFS_PDUs
suffix:semicolon
multiline_comment|/* enable smb packet signing */
DECL|variable|linuxExtEnabled
id|GLOBAL_EXTERN
r_int
r_int
id|linuxExtEnabled
suffix:semicolon
multiline_comment|/* enable Linux/Unix CIFS extensions */
eof
