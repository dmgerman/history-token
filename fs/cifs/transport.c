multiline_comment|/*&n; *   fs/cifs/transport.c&n; *&n; *   Copyright (C) International Business Machines  Corp., 2002,2004&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
r_extern
id|mempool_t
op_star
id|cifs_mid_poolp
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|cifs_oplock_cachep
suffix:semicolon
r_struct
id|mid_q_entry
op_star
DECL|function|AllocMidQEntry
id|AllocMidQEntry
c_func
(paren
r_struct
id|smb_hdr
op_star
id|smb_buffer
comma
r_struct
id|cifsSesInfo
op_star
id|ses
)paren
(brace
r_struct
id|mid_q_entry
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|ses
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null session passed in to AllocMidQEntry &quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ses-&gt;server
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null TCP session in AllocMidQEntry&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|temp
op_assign
(paren
r_struct
id|mid_q_entry
op_star
)paren
id|mempool_alloc
c_func
(paren
id|cifs_mid_poolp
comma
id|SLAB_KERNEL
op_or
id|SLAB_NOFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_eq
l_int|NULL
)paren
r_return
id|temp
suffix:semicolon
r_else
(brace
id|memset
c_func
(paren
id|temp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mid_q_entry
)paren
)paren
suffix:semicolon
id|temp-&gt;mid
op_assign
id|smb_buffer-&gt;Mid
suffix:semicolon
multiline_comment|/* always LE */
id|temp-&gt;pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|temp-&gt;command
op_assign
id|smb_buffer-&gt;Command
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;For smb_command %d&quot;
comma
id|temp-&gt;command
)paren
)paren
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|temp-&gt;when_sent
)paren
suffix:semicolon
id|temp-&gt;ses
op_assign
id|ses
suffix:semicolon
id|temp-&gt;tsk
op_assign
id|current
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|temp-&gt;qhead
comma
op_amp
id|ses-&gt;server-&gt;pending_mid_q
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|midCount
)paren
suffix:semicolon
id|temp-&gt;midState
op_assign
id|MID_REQUEST_ALLOCATED
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
r_void
DECL|function|DeleteMidQEntry
id|DeleteMidQEntry
c_func
(paren
r_struct
id|mid_q_entry
op_star
id|midEntry
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|midEntry-&gt;midState
op_assign
id|MID_FREE
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|midEntry-&gt;qhead
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|midCount
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|cifs_buf_release
c_func
(paren
id|midEntry-&gt;resp_buf
)paren
suffix:semicolon
id|mempool_free
c_func
(paren
id|midEntry
comma
id|cifs_mid_poolp
)paren
suffix:semicolon
)brace
r_struct
id|oplock_q_entry
op_star
DECL|function|AllocOplockQEntry
id|AllocOplockQEntry
c_func
(paren
r_struct
id|inode
op_star
id|pinode
comma
id|__u16
id|fid
comma
r_struct
id|cifsTconInfo
op_star
id|tcon
)paren
(brace
r_struct
id|oplock_q_entry
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pinode
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|tcon
op_eq
l_int|NULL
)paren
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null parms passed to AllocOplockQEntry&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|temp
op_assign
(paren
r_struct
id|oplock_q_entry
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|cifs_oplock_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_eq
l_int|NULL
)paren
r_return
id|temp
suffix:semicolon
r_else
(brace
id|temp-&gt;pinode
op_assign
id|pinode
suffix:semicolon
id|temp-&gt;tcon
op_assign
id|tcon
suffix:semicolon
id|temp-&gt;netfid
op_assign
id|fid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|temp-&gt;qhead
comma
op_amp
id|GlobalOplock_Q
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
)brace
r_return
id|temp
suffix:semicolon
)brace
DECL|function|DeleteOplockQEntry
r_void
id|DeleteOplockQEntry
c_func
(paren
r_struct
id|oplock_q_entry
op_star
id|oplockEntry
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
multiline_comment|/* should we check if list empty first? */
id|list_del
c_func
(paren
op_amp
id|oplockEntry-&gt;qhead
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|cifs_oplock_cachep
comma
id|oplockEntry
)paren
suffix:semicolon
)brace
r_int
DECL|function|smb_send
id|smb_send
c_func
(paren
r_struct
id|socket
op_star
id|ssocket
comma
r_struct
id|smb_hdr
op_star
id|smb_buffer
comma
r_int
r_int
id|smb_buf_length
comma
r_struct
id|sockaddr
op_star
id|sin
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|msghdr
id|smb_msg
suffix:semicolon
r_struct
id|iovec
id|iov
suffix:semicolon
id|mm_segment_t
id|temp_fs
suffix:semicolon
r_if
c_cond
(paren
id|ssocket
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOTSOCK
suffix:semicolon
)brace
multiline_comment|/* BB eventually add reconnect code here */
id|iov.iov_base
op_assign
id|smb_buffer
suffix:semicolon
id|iov.iov_len
op_assign
id|smb_buf_length
op_plus
l_int|4
suffix:semicolon
id|smb_msg.msg_name
op_assign
id|sin
suffix:semicolon
id|smb_msg.msg_namelen
op_assign
r_sizeof
(paren
r_struct
id|sockaddr
)paren
suffix:semicolon
id|smb_msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|smb_msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|smb_msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
id|smb_msg.msg_controllen
op_assign
l_int|0
suffix:semicolon
id|smb_msg.msg_flags
op_assign
id|MSG_DONTWAIT
op_plus
id|MSG_NOSIGNAL
suffix:semicolon
multiline_comment|/* BB add more flags?*/
multiline_comment|/* smb header is converted in header_assemble. bcc and rest of SMB word&n;&t;   area, and byte area if necessary, is converted to littleendian in &n;&t;   cifssmb.c and RFC1001 len is converted to bigendian in smb_send &n;&t;   Flags2 is converted in SendReceive */
id|smb_buffer-&gt;smb_buf_length
op_assign
id|cpu_to_be32
c_func
(paren
id|smb_buffer-&gt;smb_buf_length
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Sending smb of length %d &quot;
comma
id|smb_buf_length
)paren
)paren
suffix:semicolon
id|dump_smb
c_func
(paren
id|smb_buffer
comma
id|smb_buf_length
op_plus
l_int|4
)paren
suffix:semicolon
id|temp_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we must turn off socket api parm checking */
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|iov.iov_len
OG
l_int|0
)paren
(brace
id|rc
op_assign
id|sock_sendmsg
c_func
(paren
id|ssocket
comma
op_amp
id|smb_msg
comma
id|smb_buf_length
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_eq
op_minus
id|ENOSPC
)paren
op_logical_or
(paren
id|rc
op_eq
op_minus
id|EAGAIN
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|60
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;sends on sock %p stuck for 30 seconds&quot;
comma
id|ssocket
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|2
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_break
suffix:semicolon
id|iov.iov_base
op_add_assign
id|rc
suffix:semicolon
id|iov.iov_len
op_sub_assign
id|rc
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|temp_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Error %d sending data on socket to server.&quot;
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_int
DECL|function|SendReceive
id|SendReceive
c_func
(paren
r_const
r_int
r_int
id|xid
comma
r_struct
id|cifsSesInfo
op_star
id|ses
comma
r_struct
id|smb_hdr
op_star
id|in_buf
comma
r_struct
id|smb_hdr
op_star
id|out_buf
comma
r_int
op_star
id|pbytes_returned
comma
r_const
r_int
id|long_op
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|receive_len
suffix:semicolon
r_int
id|timeout
suffix:semicolon
r_struct
id|mid_q_entry
op_star
id|midQ
suffix:semicolon
r_if
c_cond
(paren
id|ses
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null smb session&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ses-&gt;server
op_eq
l_int|NULL
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Null tcp session&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Ensure that we do not send more than 50 overlapping requests &n;&t;   to the same server. We may make this configurable later or&n;&t;   use ses-&gt;maxReq */
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
op_ge
id|CIFS_MAX_REQ
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|wait_event
c_func
(paren
id|ses-&gt;server-&gt;request_q
comma
id|atomic_read
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
OL
id|CIFS_MAX_REQ
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* can not count locking commands against the total since&n;&t;&t;&t;   they are allowed to block on server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
multiline_comment|/* update # of requests on the wire to this server */
id|atomic_inc
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* make sure that we sign in the same order that we send on this socket &n;&t;   and avoid races inside tcp sendmsg code that could cause corruption&n;&t;   of smb data */
id|down
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ses-&gt;server-&gt;tcpStatus
op_eq
id|CifsExiting
)paren
(brace
id|rc
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ses-&gt;server-&gt;tcpStatus
op_eq
id|CifsNeedReconnect
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;tcp session dead - return to caller to retry&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ses-&gt;status
op_ne
id|CifsGood
)paren
(brace
multiline_comment|/* check if SMB session is bad because we are setting it up */
r_if
c_cond
(paren
(paren
id|in_buf-&gt;Command
op_ne
id|SMB_COM_SESSION_SETUP_ANDX
)paren
op_logical_and
(paren
id|in_buf-&gt;Command
op_ne
id|SMB_COM_NEGOTIATE
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/* else ok - we are setting up session */
)brace
id|midQ
op_assign
id|AllocMidQEntry
c_func
(paren
id|in_buf
comma
id|ses
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midQ
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
multiline_comment|/* If not lock req, update # of requests on wire to server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|in_buf-&gt;smb_buf_length
OG
id|CIFS_MAX_MSGSIZE
op_plus
id|MAX_CIFS_HDR_SIZE
op_minus
l_int|4
)paren
(brace
id|up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Illegal length, greater than maximum frame, %d &quot;
comma
id|in_buf-&gt;smb_buf_length
)paren
)paren
suffix:semicolon
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
multiline_comment|/* If not lock req, update # of requests on wire to server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|in_buf-&gt;smb_buf_length
OG
l_int|12
)paren
id|in_buf-&gt;Flags2
op_assign
id|cpu_to_le16
c_func
(paren
id|in_buf-&gt;Flags2
)paren
suffix:semicolon
id|rc
op_assign
id|cifs_sign_smb
c_func
(paren
id|in_buf
comma
id|ses
comma
op_amp
id|midQ-&gt;sequence_number
)paren
suffix:semicolon
id|midQ-&gt;midState
op_assign
id|MID_REQUEST_SUBMITTED
suffix:semicolon
id|rc
op_assign
id|smb_send
c_func
(paren
id|ses-&gt;server-&gt;ssocket
comma
id|in_buf
comma
id|in_buf-&gt;smb_buf_length
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
(paren
id|ses-&gt;server-&gt;addr.sockAddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
multiline_comment|/* If not lock req, update # of requests on wire to server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_else
id|up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|long_op
op_eq
op_minus
l_int|1
)paren
r_goto
id|cifs_no_response_exit
suffix:semicolon
r_else
r_if
c_cond
(paren
id|long_op
op_eq
l_int|2
)paren
multiline_comment|/* writes past end of file can take looooong time */
id|timeout
op_assign
l_int|300
op_star
id|HZ
suffix:semicolon
r_else
r_if
c_cond
(paren
id|long_op
op_eq
l_int|1
)paren
id|timeout
op_assign
l_int|45
op_star
id|HZ
suffix:semicolon
multiline_comment|/* should be greater than &n;&t;&t;&t;servers oplock break timeout (about 43 seconds) */
r_else
r_if
c_cond
(paren
id|long_op
OG
l_int|2
)paren
(brace
id|timeout
op_assign
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
)brace
r_else
id|timeout
op_assign
l_int|15
op_star
id|HZ
suffix:semicolon
multiline_comment|/* wait for 15 seconds or until woken up due to response arriving or &n;&t;   due to last connection to this server being unmounted */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
multiline_comment|/* if signal pending do not hold up user for full smb timeout&n;&t;&t;but we still give response a change to complete */
r_if
c_cond
(paren
id|midQ-&gt;midState
op_amp
id|MID_REQUEST_SUBMITTED
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|timeout
op_assign
id|sleep_on_timeout
c_func
(paren
op_amp
id|ses-&gt;server-&gt;response_q
comma
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* using normal timeout */
multiline_comment|/* timeout = wait_event_interruptible_timeout(ses-&gt;server-&gt;response_q,&n;&t;&t;&t;(midQ-&gt;midState &amp; MID_RESPONSE_RECEIVED) || &n;&t;&t;&t;((ses-&gt;server-&gt;tcpStatus != CifsGood) &amp;&amp;&n;&t;&t;&t; (ses-&gt;server-&gt;tcpStatus != CifsNew)),&n;&t;&t;&t;timeout); */
multiline_comment|/* Can not allow user interrupts- wreaks havoc with performance */
r_if
c_cond
(paren
id|midQ-&gt;midState
op_amp
id|MID_REQUEST_SUBMITTED
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|timeout
op_assign
id|sleep_on_timeout
c_func
(paren
op_amp
id|ses-&gt;server-&gt;response_q
comma
id|timeout
)paren
suffix:semicolon
)brace
)brace
id|spin_lock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midQ-&gt;resp_buf
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|receive_len
op_assign
id|be32_to_cpu
c_func
(paren
id|midQ-&gt;resp_buf-&gt;smb_buf_length
)paren
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
l_string|&quot;No response buffer&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|midQ-&gt;midState
op_eq
id|MID_REQUEST_SUBMITTED
)paren
(brace
r_if
c_cond
(paren
id|ses-&gt;server-&gt;tcpStatus
op_eq
id|CifsExiting
)paren
(brace
id|rc
op_assign
op_minus
id|EHOSTDOWN
suffix:semicolon
)brace
r_else
(brace
id|ses-&gt;server-&gt;tcpStatus
op_assign
id|CifsNeedReconnect
suffix:semicolon
id|midQ-&gt;midState
op_assign
id|MID_RETRY_NEEDED
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|rc
op_ne
op_minus
id|EHOSTDOWN
)paren
(brace
r_if
c_cond
(paren
id|midQ-&gt;midState
op_eq
id|MID_RETRY_NEEDED
)paren
(brace
id|rc
op_assign
op_minus
id|EAGAIN
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;marking request for retry&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
multiline_comment|/* If not lock req, update # of requests on wire to server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|receive_len
OG
id|CIFS_MAX_MSGSIZE
op_plus
id|MAX_CIFS_HDR_SIZE
)paren
(brace
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Frame too large received.  Length: %d  Xid: %d&quot;
comma
id|receive_len
comma
id|xid
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* rcvd frame is ok */
r_if
c_cond
(paren
id|midQ-&gt;resp_buf
op_logical_and
id|out_buf
op_logical_and
(paren
id|midQ-&gt;midState
op_eq
id|MID_RESPONSE_RECEIVED
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|out_buf
comma
id|midQ-&gt;resp_buf
comma
id|receive_len
op_plus
l_int|4
multiline_comment|/* include 4 byte RFC1001 header */
)paren
suffix:semicolon
id|dump_smb
c_func
(paren
id|out_buf
comma
l_int|92
)paren
suffix:semicolon
multiline_comment|/* convert the length into a more usable form */
id|out_buf-&gt;smb_buf_length
op_assign
id|be32_to_cpu
c_func
(paren
id|out_buf-&gt;smb_buf_length
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|out_buf-&gt;smb_buf_length
OG
l_int|24
)paren
op_logical_and
(paren
id|ses-&gt;server-&gt;secMode
op_amp
(paren
id|SECMODE_SIGN_REQUIRED
op_or
id|SECMODE_SIGN_ENABLED
)paren
)paren
)paren
(brace
id|rc
op_assign
id|cifs_verify_signature
c_func
(paren
id|out_buf
comma
id|ses-&gt;mac_signing_key
comma
id|midQ-&gt;sequence_number
)paren
suffix:semicolon
multiline_comment|/* BB fix BB */
r_if
c_cond
(paren
id|rc
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Unexpected signature received from server&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|out_buf-&gt;smb_buf_length
OG
l_int|12
)paren
id|out_buf-&gt;Flags2
op_assign
id|le16_to_cpu
c_func
(paren
id|out_buf-&gt;Flags2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_buf-&gt;smb_buf_length
OG
l_int|28
)paren
id|out_buf-&gt;Pid
op_assign
id|le16_to_cpu
c_func
(paren
id|out_buf-&gt;Pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_buf-&gt;smb_buf_length
OG
l_int|28
)paren
id|out_buf-&gt;PidHigh
op_assign
id|le16_to_cpu
c_func
(paren
id|out_buf-&gt;PidHigh
)paren
suffix:semicolon
op_star
id|pbytes_returned
op_assign
id|out_buf-&gt;smb_buf_length
suffix:semicolon
multiline_comment|/* BB special case reconnect tid and reconnect uid here? */
id|rc
op_assign
id|map_smb_to_linux_error
c_func
(paren
id|out_buf
)paren
suffix:semicolon
multiline_comment|/* convert ByteCount if necessary */
r_if
c_cond
(paren
id|receive_len
op_ge
r_sizeof
(paren
r_struct
id|smb_hdr
)paren
op_minus
l_int|4
multiline_comment|/* do not count RFC1001 header */
op_plus
(paren
l_int|2
op_star
id|out_buf-&gt;WordCount
)paren
op_plus
l_int|2
multiline_comment|/* bcc */
)paren
id|BCC
c_func
(paren
id|out_buf
)paren
op_assign
id|le16_to_cpu
c_func
(paren
id|BCC
c_func
(paren
id|out_buf
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Bad MID state? &quot;
)paren
)paren
suffix:semicolon
)brace
)brace
id|cifs_no_response_exit
suffix:colon
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
id|out_unlock
suffix:colon
id|up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;tcpSem
)paren
suffix:semicolon
multiline_comment|/* If not lock req, update # of requests on wire to server */
r_if
c_cond
(paren
id|long_op
OL
l_int|3
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|ses-&gt;server-&gt;inFlight
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|ses-&gt;server-&gt;request_q
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
eof
