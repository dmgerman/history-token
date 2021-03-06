multiline_comment|/*&n; *   fs/cifs/misc.c&n; *&n; *   Copyright (C) International Business Machines  Corp., 2002,2004&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
macro_line|#include &quot;smberr.h&quot;
macro_line|#include &quot;nterr.h&quot;
r_extern
id|mempool_t
op_star
id|cifs_sm_req_poolp
suffix:semicolon
r_extern
id|mempool_t
op_star
id|cifs_req_poolp
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|oplockThread
suffix:semicolon
DECL|variable|GlobalMid
r_static
id|__u16
id|GlobalMid
suffix:semicolon
multiline_comment|/* multiplex id - rotating counter */
multiline_comment|/* The xid serves as a useful identifier for each incoming vfs request, &n;   in a similar way to the mid which is useful to track each sent smb, &n;   and CurrentXid can also provide a running counter (although it &n;   will eventually wrap past zero) of the total vfs operations handled &n;   since the cifs fs was mounted */
r_int
r_int
DECL|function|_GetXid
id|_GetXid
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|xid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|GlobalTotalActiveXid
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|GlobalTotalActiveXid
OG
id|GlobalMaxActiveXid
)paren
id|GlobalMaxActiveXid
op_assign
id|GlobalTotalActiveXid
suffix:semicolon
multiline_comment|/* keep high water mark for number of simultaneous vfs ops in our filesystem */
id|xid
op_assign
id|GlobalCurrentXid
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_return
id|xid
suffix:semicolon
)brace
r_void
DECL|function|_FreeXid
id|_FreeXid
c_func
(paren
r_int
r_int
id|xid
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
multiline_comment|/* if(GlobalTotalActiveXid == 0)&n;&t;&t;BUG(); */
id|GlobalTotalActiveXid
op_decrement
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
)brace
r_struct
id|cifsSesInfo
op_star
DECL|function|sesInfoAlloc
id|sesInfoAlloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|cifsSesInfo
op_star
id|ret_buf
suffix:semicolon
id|ret_buf
op_assign
(paren
r_struct
id|cifsSesInfo
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cifsSesInfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_buf
)paren
(brace
id|memset
c_func
(paren
id|ret_buf
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cifsSesInfo
)paren
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|sesInfoAllocCount
)paren
suffix:semicolon
id|ret_buf-&gt;status
op_assign
id|CifsNew
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|ret_buf-&gt;cifsSessionList
comma
op_amp
id|GlobalSMBSessionList
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|ret_buf-&gt;sesSem
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
)brace
r_return
id|ret_buf
suffix:semicolon
)brace
r_void
DECL|function|sesInfoFree
id|sesInfoFree
c_func
(paren
r_struct
id|cifsSesInfo
op_star
id|buf_to_free
)paren
(brace
r_if
c_cond
(paren
id|buf_to_free
op_eq
l_int|NULL
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null buffer passed to sesInfoFree&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|sesInfoAllocCount
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|buf_to_free-&gt;cifsSessionList
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_to_free-&gt;serverOS
)paren
id|kfree
c_func
(paren
id|buf_to_free-&gt;serverOS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_to_free-&gt;serverDomain
)paren
id|kfree
c_func
(paren
id|buf_to_free-&gt;serverDomain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_to_free-&gt;serverNOS
)paren
id|kfree
c_func
(paren
id|buf_to_free-&gt;serverNOS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_to_free-&gt;password
)paren
id|kfree
c_func
(paren
id|buf_to_free-&gt;password
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf_to_free
)paren
suffix:semicolon
)brace
r_struct
id|cifsTconInfo
op_star
DECL|function|tconInfoAlloc
id|tconInfoAlloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|cifsTconInfo
op_star
id|ret_buf
suffix:semicolon
id|ret_buf
op_assign
(paren
r_struct
id|cifsTconInfo
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cifsTconInfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_buf
)paren
(brace
id|memset
c_func
(paren
id|ret_buf
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cifsTconInfo
)paren
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|tconInfoAllocCount
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|ret_buf-&gt;cifsConnectionList
comma
op_amp
id|GlobalTreeConnectionList
)paren
suffix:semicolon
id|ret_buf-&gt;tidStatus
op_assign
id|CifsNew
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ret_buf-&gt;openFileList
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|ret_buf-&gt;tconSem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CIFS_STATS
id|spin_lock_init
c_func
(paren
op_amp
id|ret_buf-&gt;stat_lock
)paren
suffix:semicolon
macro_line|#endif
id|write_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
)brace
r_return
id|ret_buf
suffix:semicolon
)brace
r_void
DECL|function|tconInfoFree
id|tconInfoFree
c_func
(paren
r_struct
id|cifsTconInfo
op_star
id|buf_to_free
)paren
(brace
r_if
c_cond
(paren
id|buf_to_free
op_eq
l_int|NULL
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null buffer passed to tconInfoFree&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|tconInfoAllocCount
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|buf_to_free-&gt;cifsConnectionList
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_to_free-&gt;nativeFileSystem
)paren
id|kfree
c_func
(paren
id|buf_to_free-&gt;nativeFileSystem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf_to_free
)paren
suffix:semicolon
)brace
r_struct
id|smb_hdr
op_star
DECL|function|cifs_buf_get
id|cifs_buf_get
c_func
(paren
r_void
)paren
(brace
r_struct
id|smb_hdr
op_star
id|ret_buf
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We could use negotiated size instead of max_msgsize - &n;   but it may be more efficient to always alloc same size &n;   albeit slightly larger than necessary and maxbuffersize &n;   defaults to this and can not be bigger */
id|ret_buf
op_assign
(paren
r_struct
id|smb_hdr
op_star
)paren
id|mempool_alloc
c_func
(paren
id|cifs_req_poolp
comma
id|SLAB_KERNEL
op_or
id|SLAB_NOFS
)paren
suffix:semicolon
multiline_comment|/* clear the first few header bytes */
multiline_comment|/* for most paths, more is cleared in header_assemble */
r_if
c_cond
(paren
id|ret_buf
)paren
(brace
id|memset
c_func
(paren
id|ret_buf
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
op_plus
l_int|3
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bufAllocCount
)paren
suffix:semicolon
)brace
r_return
id|ret_buf
suffix:semicolon
)brace
r_void
DECL|function|cifs_buf_release
id|cifs_buf_release
c_func
(paren
r_void
op_star
id|buf_to_free
)paren
(brace
r_if
c_cond
(paren
id|buf_to_free
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* cFYI(1, (&quot;Null buffer passed to cifs_buf_release&quot;));*/
r_return
suffix:semicolon
)brace
id|mempool_free
c_func
(paren
id|buf_to_free
comma
id|cifs_req_poolp
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bufAllocCount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_struct
id|smb_hdr
op_star
DECL|function|cifs_small_buf_get
id|cifs_small_buf_get
c_func
(paren
r_void
)paren
(brace
r_struct
id|smb_hdr
op_star
id|ret_buf
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We could use negotiated size instead of max_msgsize - &n;   but it may be more efficient to always alloc same size &n;   albeit slightly larger than necessary and maxbuffersize &n;   defaults to this and can not be bigger */
id|ret_buf
op_assign
(paren
r_struct
id|smb_hdr
op_star
)paren
id|mempool_alloc
c_func
(paren
id|cifs_sm_req_poolp
comma
id|SLAB_KERNEL
op_or
id|SLAB_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_buf
)paren
(brace
multiline_comment|/* No need to clear memory here, cleared in header assemble */
multiline_comment|/*&t;memset(ret_buf, 0, sizeof(struct smb_hdr) + 27);*/
id|atomic_inc
c_func
(paren
op_amp
id|smBufAllocCount
)paren
suffix:semicolon
)brace
r_return
id|ret_buf
suffix:semicolon
)brace
r_void
DECL|function|cifs_small_buf_release
id|cifs_small_buf_release
c_func
(paren
r_void
op_star
id|buf_to_free
)paren
(brace
r_if
c_cond
(paren
id|buf_to_free
op_eq
l_int|NULL
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null buffer passed to cifs_small_buf_release&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mempool_free
c_func
(paren
id|buf_to_free
comma
id|cifs_sm_req_poolp
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|smBufAllocCount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_void
DECL|function|header_assemble
id|header_assemble
c_func
(paren
r_struct
id|smb_hdr
op_star
id|buffer
comma
r_char
id|smb_command
multiline_comment|/* command */
comma
r_const
r_struct
id|cifsTconInfo
op_star
id|treeCon
comma
r_int
id|word_count
multiline_comment|/* length of fixed section (word count) in two byte units  */
)paren
(brace
r_struct
id|list_head
op_star
id|temp_item
suffix:semicolon
r_struct
id|cifsSesInfo
op_star
id|ses
suffix:semicolon
r_char
op_star
id|temp
op_assign
(paren
r_char
op_star
)paren
id|buffer
suffix:semicolon
id|memset
c_func
(paren
id|temp
comma
l_int|0
comma
id|MAX_CIFS_HDR_SIZE
)paren
suffix:semicolon
id|buffer-&gt;smb_buf_length
op_assign
(paren
l_int|2
op_star
id|word_count
)paren
op_plus
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
op_minus
l_int|4
multiline_comment|/*  RFC 1001 length field does not count */
op_plus
l_int|2
multiline_comment|/* for bcc field itself */
suffix:semicolon
multiline_comment|/* Note that this is the only network field that has to be converted to big endian and it is done just before we send it */
id|buffer-&gt;Protocol
(braket
l_int|0
)braket
op_assign
l_int|0xFF
suffix:semicolon
id|buffer-&gt;Protocol
(braket
l_int|1
)braket
op_assign
l_char|&squot;S&squot;
suffix:semicolon
id|buffer-&gt;Protocol
(braket
l_int|2
)braket
op_assign
l_char|&squot;M&squot;
suffix:semicolon
id|buffer-&gt;Protocol
(braket
l_int|3
)braket
op_assign
l_char|&squot;B&squot;
suffix:semicolon
id|buffer-&gt;Command
op_assign
id|smb_command
suffix:semicolon
id|buffer-&gt;Flags
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* case sensitive */
id|buffer-&gt;Flags2
op_assign
id|SMBFLG2_KNOWS_LONG_NAMES
suffix:semicolon
id|buffer-&gt;Pid
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|__u16
)paren
id|current-&gt;tgid
)paren
suffix:semicolon
id|buffer-&gt;PidHigh
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|__u16
)paren
(paren
id|current-&gt;tgid
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|GlobalMid
op_increment
suffix:semicolon
id|buffer-&gt;Mid
op_assign
id|GlobalMid
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|treeCon
)paren
(brace
id|buffer-&gt;Tid
op_assign
id|treeCon-&gt;tid
suffix:semicolon
r_if
c_cond
(paren
id|treeCon-&gt;ses
)paren
(brace
r_if
c_cond
(paren
id|treeCon-&gt;ses-&gt;capabilities
op_amp
id|CAP_UNICODE
)paren
id|buffer-&gt;Flags2
op_or_assign
id|SMBFLG2_UNICODE
suffix:semicolon
r_if
c_cond
(paren
id|treeCon-&gt;ses-&gt;capabilities
op_amp
id|CAP_STATUS32
)paren
(brace
id|buffer-&gt;Flags2
op_or_assign
id|SMBFLG2_ERR_STATUS
suffix:semicolon
)brace
id|buffer-&gt;Uid
op_assign
id|treeCon-&gt;ses-&gt;Suid
suffix:semicolon
multiline_comment|/* always in LE format */
r_if
c_cond
(paren
id|multiuser_mount
op_ne
l_int|0
)paren
(brace
multiline_comment|/* For the multiuser case, there are few obvious technically  */
multiline_comment|/* possible mechanisms to match the local linux user (uid)    */
multiline_comment|/* to a valid remote smb user (smb_uid):&t;&t;      */
multiline_comment|/* &t;1) Query Winbind (or other local pam/nss daemon       */
multiline_comment|/* &t;  for userid/password/logon_domain or credential      */
multiline_comment|/*      2) Query Winbind for uid to sid to username mapping   */
multiline_comment|/* &t;   and see if we have a matching password for existing*/
multiline_comment|/*         session for that user perhas getting password by   */
multiline_comment|/*         adding a new pam_cifs module that stores passwords */
multiline_comment|/*         so that the cifs vfs can get at that for all logged*/
multiline_comment|/*&t;   on users&t;&t;&t;&t;&t;      */
multiline_comment|/*&t;3) (Which is the mechanism we have chosen)&t;      */
multiline_comment|/*&t;   Search through sessions to the same server for a   */
multiline_comment|/*&t;   a match on the uid that was passed in on mount     */
multiline_comment|/*         with the current processes uid (or euid?) and use  */
multiline_comment|/* &t;   that smb uid.   If no existing smb session for     */
multiline_comment|/* &t;   that uid found, use the default smb session ie     */
multiline_comment|/*         the smb session for the volume mounted which is    */
multiline_comment|/* &t;   the same as would be used if the multiuser mount   */
multiline_comment|/* &t;   flag were disabled.  */
multiline_comment|/*  BB Add support for establishing new tCon and SMB Session  */
multiline_comment|/*      with userid/password pairs found on the smb session   */
multiline_comment|/*&t;for other target tcp/ip addresses &t;&t;BB    */
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
id|treeCon-&gt;ses-&gt;linux_uid
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Multiuser mode and UID did not match tcon uid &quot;
)paren
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|temp_item
comma
op_amp
id|GlobalSMBSessionList
)paren
(brace
id|ses
op_assign
id|list_entry
c_func
(paren
id|temp_item
comma
r_struct
id|cifsSesInfo
comma
id|cifsSessionList
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ses-&gt;linux_uid
op_eq
id|current-&gt;uid
)paren
(brace
r_if
c_cond
(paren
id|ses-&gt;server
op_eq
id|treeCon-&gt;ses-&gt;server
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;found matching uid substitute right smb_uid&quot;
)paren
)paren
suffix:semicolon
id|buffer-&gt;Uid
op_assign
id|ses-&gt;Suid
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* BB eventually call cifs_setup_session here */
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;local UID found but smb sess with this server does not exist&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|treeCon-&gt;Flags
op_amp
id|SMB_SHARE_IS_IN_DFS
)paren
id|buffer-&gt;Flags2
op_or_assign
id|SMBFLG2_DFS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|treeCon-&gt;ses
)paren
op_logical_and
(paren
id|treeCon-&gt;ses-&gt;server
)paren
)paren
r_if
c_cond
(paren
id|treeCon-&gt;ses-&gt;server-&gt;secMode
op_amp
(paren
id|SECMODE_SIGN_REQUIRED
op_or
id|SECMODE_SIGN_ENABLED
)paren
)paren
(brace
id|buffer-&gt;Flags2
op_or_assign
id|SMBFLG2_SECURITY_SIGNATURE
suffix:semicolon
)brace
)brace
multiline_comment|/*  endian conversion of flags is now done just before sending */
id|buffer-&gt;WordCount
op_assign
(paren
r_char
)paren
id|word_count
suffix:semicolon
r_return
suffix:semicolon
)brace
r_int
DECL|function|checkSMBhdr
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
(brace
multiline_comment|/* Make sure that this really is an SMB, that it is a response, &n;&t;   and that the message ids match */
r_if
c_cond
(paren
(paren
op_star
(paren
id|__le32
op_star
)paren
id|smb-&gt;Protocol
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x424d53ff
)paren
)paren
op_logical_and
(paren
id|mid
op_eq
id|smb-&gt;Mid
)paren
)paren
(brace
r_if
c_cond
(paren
id|smb-&gt;Flags
op_amp
id|SMBFLG_RESPONSE
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* only one valid case where server sends us request */
r_if
c_cond
(paren
id|smb-&gt;Command
op_eq
id|SMB_COM_LOCKING_ANDX
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Rcvd Request not response &quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* bad signature or mid */
r_if
c_cond
(paren
op_star
(paren
id|__le32
op_star
)paren
id|smb-&gt;Protocol
op_ne
id|cpu_to_le32
c_func
(paren
l_int|0x424d53ff
)paren
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Bad protocol string signature header %x &quot;
comma
op_star
(paren
r_int
r_int
op_star
)paren
id|smb-&gt;Protocol
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mid
op_ne
id|smb-&gt;Mid
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Mids do not match&quot;
)paren
)paren
suffix:semicolon
)brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;bad smb detected. The Mid=%d&quot;
comma
id|smb-&gt;Mid
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|checkSMB
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
(brace
id|__u32
id|len
op_assign
id|be32_to_cpu
c_func
(paren
id|smb-&gt;smb_buf_length
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|0
comma
(paren
l_string|&quot;Entering checkSMB with Length: %x, smb_buf_length: %x &quot;
comma
id|length
comma
id|len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|length
OL
l_int|2
op_plus
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
)paren
op_logical_or
(paren
id|len
OG
id|CIFSMaxBufSize
op_plus
id|MAX_CIFS_HDR_SIZE
op_minus
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|length
OL
l_int|2
op_plus
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|length
op_ge
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
op_minus
l_int|1
)paren
op_logical_and
(paren
id|smb-&gt;Status.CifsError
op_ne
l_int|0
)paren
)paren
(brace
id|smb-&gt;WordCount
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* some error cases do not return wct and bcc */
)brace
r_else
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Length less than smb header size&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
OG
id|CIFSMaxBufSize
op_plus
id|MAX_CIFS_HDR_SIZE
op_minus
l_int|4
)paren
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;smb_buf_length greater than MaxBufSize&quot;
)paren
)paren
suffix:semicolon
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;bad smb detected. Illegal length. The mid=%d&quot;
comma
id|smb-&gt;Mid
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checkSMBhdr
c_func
(paren
id|smb
comma
id|mid
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|4
op_plus
id|len
op_ne
id|smbCalcSize
c_func
(paren
id|smb
)paren
)paren
op_logical_or
(paren
l_int|4
op_plus
id|len
op_ne
(paren
r_int
r_int
)paren
id|length
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;smbCalcSize %x &quot;
comma
id|smbCalcSize
c_func
(paren
id|smb
)paren
)paren
)paren
suffix:semicolon
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;bad smb size detected. The Mid=%d&quot;
comma
id|smb-&gt;Mid
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_int
DECL|function|is_valid_oplock_break
id|is_valid_oplock_break
c_func
(paren
r_struct
id|smb_hdr
op_star
id|buf
)paren
(brace
r_struct
id|smb_com_lock_req
op_star
id|pSMB
op_assign
(paren
r_struct
id|smb_com_lock_req
op_star
)paren
id|buf
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp1
suffix:semicolon
r_struct
id|cifsTconInfo
op_star
id|tcon
suffix:semicolon
r_struct
id|cifsFileInfo
op_star
id|netfile
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Checking for oplock break or dnotify response&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pSMB-&gt;hdr.Command
op_eq
id|SMB_COM_NT_TRANSACT
)paren
op_logical_and
(paren
id|pSMB-&gt;hdr.Flags
op_amp
id|SMBFLG_RESPONSE
)paren
)paren
(brace
r_struct
id|smb_com_transaction_change_notify_rsp
op_star
id|pSMBr
op_assign
(paren
r_struct
id|smb_com_transaction_change_notify_rsp
op_star
)paren
id|buf
suffix:semicolon
r_struct
id|file_notify_information
op_star
id|pnotify
suffix:semicolon
id|__u32
id|data_offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pSMBr-&gt;ByteCount
OG
r_sizeof
(paren
r_struct
id|file_notify_information
)paren
)paren
(brace
id|data_offset
op_assign
id|le32_to_cpu
c_func
(paren
id|pSMBr-&gt;DataOffset
)paren
suffix:semicolon
id|pnotify
op_assign
(paren
r_struct
id|file_notify_information
op_star
)paren
(paren
(paren
r_char
op_star
)paren
op_amp
id|pSMBr-&gt;hdr.Protocol
op_plus
id|data_offset
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;dnotify on %s with action: 0x%x&quot;
comma
id|pnotify-&gt;FileName
comma
id|pnotify-&gt;Action
)paren
)paren
suffix:semicolon
multiline_comment|/* BB removeme BB */
multiline_comment|/*   cifs_dump_mem(&quot;Received notify Data is: &quot;,buf,sizeof(struct smb_hdr)+60); */
r_return
id|TRUE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pSMBr-&gt;hdr.Status.CifsError
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;notify err 0x%d&quot;
comma
id|pSMBr-&gt;hdr.Status.CifsError
)paren
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
r_return
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pSMB-&gt;hdr.Command
op_ne
id|SMB_COM_LOCKING_ANDX
)paren
(brace
r_return
id|FALSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pSMB-&gt;hdr.Flags
op_amp
id|SMBFLG_RESPONSE
)paren
(brace
multiline_comment|/* no sense logging error on invalid handle on oplock&n;&t;&t;   break - harmless race between close request and oplock&n;&t;&t;   break response is expected from time to time writing out&n;&t;&t;   large dirty files cached on the client */
r_if
c_cond
(paren
(paren
id|NT_STATUS_INVALID_HANDLE
)paren
op_eq
id|le32_to_cpu
c_func
(paren
id|pSMB-&gt;hdr.Status.CifsError
)paren
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;invalid handle on oplock break&quot;
)paren
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ERRbadfid
op_eq
id|le16_to_cpu
c_func
(paren
id|pSMB-&gt;hdr.Status.DosError.Error
)paren
)paren
(brace
r_return
id|TRUE
suffix:semicolon
)brace
r_else
(brace
r_return
id|FALSE
suffix:semicolon
multiline_comment|/* on valid oplock brk we get &quot;request&quot; */
)brace
)brace
r_if
c_cond
(paren
id|pSMB-&gt;hdr.WordCount
op_ne
l_int|8
)paren
(brace
r_return
id|FALSE
suffix:semicolon
)brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot; oplock type 0x%d level 0x%d&quot;
comma
id|pSMB-&gt;LockType
comma
id|pSMB-&gt;OplockLevel
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pSMB-&gt;LockType
op_amp
id|LOCKING_ANDX_OPLOCK_RELEASE
)paren
)paren
(brace
r_return
id|FALSE
suffix:semicolon
)brace
multiline_comment|/* look up tcon based on tid &amp; uid */
id|read_lock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|GlobalTreeConnectionList
)paren
(brace
id|tcon
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|cifsTconInfo
comma
id|cifsConnectionList
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcon-&gt;tid
op_eq
id|buf-&gt;Tid
)paren
(brace
macro_line|#ifdef CONFIG_CIFS_STATS
id|atomic_inc
c_func
(paren
op_amp
id|tcon-&gt;num_oplock_brks
)paren
suffix:semicolon
macro_line|#endif
(def_block
id|list_for_each
c_func
(paren
id|tmp1
comma
op_amp
id|tcon-&gt;openFileList
)paren
(brace
id|netfile
op_assign
id|list_entry
c_func
(paren
id|tmp1
comma
r_struct
id|cifsFileInfo
comma
id|tlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSMB-&gt;Fid
op_eq
id|netfile-&gt;netfid
)paren
(brace
r_struct
id|cifsInodeInfo
op_star
id|pCifsInode
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Matching file id, processing oplock break&quot;
)paren
)paren
suffix:semicolon
id|pCifsInode
op_assign
id|CIFS_I
c_func
(paren
id|netfile-&gt;pInode
)paren
suffix:semicolon
id|pCifsInode-&gt;clientCanCacheAll
op_assign
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|pSMB-&gt;OplockLevel
op_eq
l_int|0
)paren
(brace
id|pCifsInode-&gt;clientCanCacheRead
op_assign
id|FALSE
suffix:semicolon
)brace
id|pCifsInode-&gt;oplockPending
op_assign
id|TRUE
suffix:semicolon
id|AllocOplockQEntry
c_func
(paren
id|netfile-&gt;pInode
comma
id|netfile-&gt;netfid
comma
id|tcon
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;about to wake up oplock thd&quot;
)paren
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|oplockThread
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
)brace
)def_block
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;No matching file for oplock break on connection&quot;
)paren
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|GlobalSMBSeslock
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Can not process oplock break for non-existent connection&quot;
)paren
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
r_void
DECL|function|dump_smb
id|dump_smb
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb_buf
comma
r_int
id|smb_buf_length
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_char
id|debug_line
(braket
l_int|17
)braket
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|traceSMB
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|smb_buf
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smb_buf_length
suffix:semicolon
id|i
op_increment
comma
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_mod
l_int|8
op_eq
l_int|0
)paren
(brace
multiline_comment|/* we have reached the beginning of line  */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;| &quot;
)paren
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%0#4x &quot;
comma
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
id|debug_line
(braket
l_int|2
op_star
id|j
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|isprint
c_func
(paren
id|buffer
(braket
id|i
)braket
)paren
)paren
id|debug_line
(braket
l_int|1
op_plus
(paren
l_int|2
op_star
id|j
)paren
)braket
op_assign
id|buffer
(braket
id|i
)braket
suffix:semicolon
r_else
id|debug_line
(braket
l_int|1
op_plus
(paren
l_int|2
op_star
id|j
)paren
)braket
op_assign
l_char|&squot;_&squot;
suffix:semicolon
r_if
c_cond
(paren
id|i
op_mod
l_int|8
op_eq
l_int|7
)paren
(brace
multiline_comment|/* we have reached end of line, time to print ascii */
id|debug_line
(braket
l_int|16
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; | %s&bslash;n&quot;
comma
id|debug_line
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;     &quot;
)paren
suffix:semicolon
id|debug_line
(braket
l_int|2
op_star
id|j
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|debug_line
(braket
l_int|1
op_plus
(paren
l_int|2
op_star
id|j
)paren
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; | %s&bslash;n&quot;
comma
id|debug_line
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
