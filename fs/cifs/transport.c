multiline_comment|/*&n; *   fs/cifs/transport.c&n; *&n; *   Copyright (c) International Business Machines  Corp., 2002&n; *   Author(s): Steve French (sfrench@us.ibm.com)&n; *&n; *   This library is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU Lesser General Public License as published&n; *   by the Free Software Foundation; either version 2.1 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This library is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU Lesser General Public License for more details.&n; *&n; *   You should have received a copy of the GNU Lesser General Public License&n; *   along with this library; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA &n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;cifspdu.h&quot;
macro_line|#include &quot;cifsglob.h&quot;
macro_line|#include &quot;cifsproto.h&quot;
macro_line|#include &quot;cifs_debug.h&quot;
r_extern
id|kmem_cache_t
op_star
id|cifs_mid_cachep
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
r_int
id|timeout
op_assign
l_int|10
op_star
id|HZ
suffix:semicolon
multiline_comment|/* BB add spinlock to protect midq for each session BB */
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
id|temp
op_assign
(paren
r_struct
id|mid_q_entry
op_star
)paren
id|kmem_cache_alloc
c_func
(paren
id|cifs_mid_cachep
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
r_while
c_loop
(paren
(paren
id|ses-&gt;server-&gt;tcpStatus
op_ne
id|CifsGood
)paren
op_logical_and
(paren
id|timeout
OG
l_int|0
)paren
)paren
(brace
multiline_comment|/* Give the tcp thread up to 10 seconds to reconnect */
multiline_comment|/* Should we wake up tcp thread first? BB  */
id|timeout
op_assign
id|wait_event_interruptible_timeout
c_func
(paren
id|ses-&gt;server-&gt;response_q
comma
(paren
id|ses-&gt;server-&gt;tcpStatus
op_eq
id|CifsGood
)paren
comma
id|timeout
)paren
suffix:semicolon
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;timeout (after reconnection wait) %d&quot;
comma
id|timeout
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ses-&gt;server-&gt;tcpStatus
op_eq
id|CifsGood
)paren
(brace
id|write_lock
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
id|write_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
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
l_string|&quot;Need to reconnect after session died to server&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
)paren
id|kmem_cache_free
c_func
(paren
id|cifs_mid_cachep
comma
id|temp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
multiline_comment|/* BB add spinlock to protect midq for each session BB */
id|write_lock
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
id|write_unlock
c_func
(paren
op_amp
id|GlobalMid_Lock
)paren
suffix:semicolon
id|buf_release
c_func
(paren
id|midEntry-&gt;resp_buf
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|cifs_mid_cachep
comma
id|midEntry
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
id|file
op_star
id|file
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
id|file
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
id|temp-&gt;file_to_flush
op_assign
id|file
suffix:semicolon
id|temp-&gt;tcon
op_assign
id|tcon
suffix:semicolon
id|write_lock
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
id|write_unlock
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
multiline_comment|/* BB add spinlock to protect midq for each session BB */
id|write_lock
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
id|write_unlock
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
multiline_comment|/*  ssocket-&gt;sk-&gt;allocation = GFP_BUFFER; */
multiline_comment|/* BB is this spurious? */
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
id|rc
op_assign
l_int|0
suffix:semicolon
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
r_return
op_minus
id|EIO
suffix:semicolon
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
id|ses-&gt;server-&gt;sockAddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|long_op
OG
l_int|1
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
l_int|60
op_star
id|HZ
suffix:semicolon
r_else
id|timeout
op_assign
l_int|15
op_star
id|HZ
suffix:semicolon
multiline_comment|/* wait for 15 seconds or until woken up due to response arriving or &n;&t;   due to last connection to this server being unmounted */
id|timeout
op_assign
id|wait_event_interruptible_timeout
c_func
(paren
id|ses-&gt;server-&gt;response_q
comma
id|midQ
op_member_access_from_pointer
id|midState
op_amp
id|MID_RESPONSE_RECEIVED
comma
id|timeout
)paren
suffix:semicolon
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
id|cERROR
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;CIFS: caught signal&quot;
)paren
)paren
suffix:semicolon
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|midQ-&gt;resp_buf
)paren
id|receive_len
op_assign
id|be32_to_cpu
c_func
(paren
id|midQ-&gt;resp_buf-&gt;smb_buf_length
)paren
suffix:semicolon
r_else
(brace
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|timeout
op_eq
l_int|0
)paren
(brace
id|cFYI
c_func
(paren
l_int|1
comma
(paren
l_string|&quot;Timeout on receive. Assume response SMB is invalid.&quot;
)paren
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_else
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
multiline_comment|/* int cifs_verify_signature(out_buf, ses-&gt;mac_signing_key,&n;        __u32 expected_sequence_number); */
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
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
id|DeleteMidQEntry
c_func
(paren
id|midQ
)paren
suffix:semicolon
multiline_comment|/* BB what if process is killed?&n;&t;&t;&t; - BB add background daemon to clean up Mid entries from&n;&t;&t;&t; killed processes &amp; test killing process with active mid */
r_return
id|rc
suffix:semicolon
)brace
eof
