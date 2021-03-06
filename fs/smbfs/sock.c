multiline_comment|/*&n; *  sock.c&n; *&n; *  Copyright (C) 1995, 1996 by Paal-Kr. Engstad and Volker Lendecke&n; *  Copyright (C) 1997 by Volker Lendecke&n; *&n; *  Please add a note about your changes to smbfs in the ChangeLog file.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;net/scm.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/smb.h&gt;
macro_line|#include &lt;linux/smbno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &quot;smb_debug.h&quot;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;request.h&quot;
r_static
r_int
DECL|function|_recvfrom
id|_recvfrom
c_func
(paren
r_struct
id|socket
op_star
id|socket
comma
r_int
r_char
op_star
id|ubuf
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_struct
id|kvec
id|iov
op_assign
(brace
id|ubuf
comma
id|size
)brace
suffix:semicolon
r_struct
id|msghdr
id|msg
op_assign
(brace
dot
id|msg_flags
op_assign
id|flags
)brace
suffix:semicolon
id|msg.msg_flags
op_or_assign
id|MSG_DONTWAIT
op_or
id|MSG_NOSIGNAL
suffix:semicolon
r_return
id|kernel_recvmsg
c_func
(paren
id|socket
comma
op_amp
id|msg
comma
op_amp
id|iov
comma
l_int|1
comma
id|size
comma
id|msg.msg_flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the server this socket belongs to&n; */
r_static
r_struct
id|smb_sb_info
op_star
DECL|function|server_from_socket
id|server_from_socket
c_func
(paren
r_struct
id|socket
op_star
id|socket
)paren
(brace
r_return
id|socket-&gt;sk-&gt;sk_user_data
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when there is data on the socket.&n; */
r_void
DECL|function|smb_data_ready
id|smb_data_ready
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|server_from_socket
c_func
(paren
id|sk-&gt;sk_socket
)paren
suffix:semicolon
r_void
(paren
op_star
id|data_ready
)paren
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
op_assign
id|server-&gt;data_ready
suffix:semicolon
id|data_ready
c_func
(paren
id|sk
comma
id|len
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;(%p, %d)&bslash;n&quot;
comma
id|sk
comma
id|len
)paren
suffix:semicolon
id|smbiod_wake_up
c_func
(paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|smb_valid_socket
id|smb_valid_socket
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
id|inode
op_logical_and
id|S_ISSOCK
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|SOCKET_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|type
op_eq
id|SOCK_STREAM
)paren
suffix:semicolon
)brace
r_static
r_struct
id|socket
op_star
DECL|function|server_sock
id|server_sock
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_if
c_cond
(paren
id|server
op_logical_and
(paren
id|file
op_assign
id|server-&gt;sock_file
)paren
)paren
(brace
macro_line|#ifdef SMBFS_PARANOIA
r_if
c_cond
(paren
op_logical_neg
id|smb_valid_socket
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
)paren
id|PARANOIA
c_func
(paren
l_string|&quot;bad socket!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|SOCKET_I
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|smb_close_socket
id|smb_close_socket
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|server-&gt;sock_file
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
r_struct
id|socket
op_star
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;closing socket %p&bslash;n&quot;
comma
id|sock
)paren
suffix:semicolon
id|sock-&gt;sk-&gt;sk_data_ready
op_assign
id|server-&gt;data_ready
suffix:semicolon
id|server-&gt;sock_file
op_assign
l_int|NULL
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|smb_get_length
id|smb_get_length
c_func
(paren
r_struct
id|socket
op_star
id|socket
comma
r_int
r_char
op_star
id|header
)paren
(brace
r_int
id|result
suffix:semicolon
id|result
op_assign
id|_recvfrom
c_func
(paren
id|socket
comma
id|header
comma
l_int|4
comma
id|MSG_PEEK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EAGAIN
)paren
r_return
op_minus
id|ENODATA
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;recv error = %d&bslash;n&quot;
comma
op_minus
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|4
)paren
r_return
op_minus
id|ENODATA
suffix:semicolon
r_switch
c_cond
(paren
id|header
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x00
suffix:colon
r_case
l_int|0x82
suffix:colon
r_break
suffix:semicolon
r_case
l_int|0x85
suffix:colon
id|DEBUG1
c_func
(paren
l_string|&quot;Got SESSION KEEP ALIVE&bslash;n&quot;
)paren
suffix:semicolon
id|_recvfrom
c_func
(paren
id|socket
comma
id|header
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* read away */
r_return
op_minus
id|ENODATA
suffix:semicolon
r_default
suffix:colon
id|PARANOIA
c_func
(paren
l_string|&quot;Invalid NBT packet, code=%x&bslash;n&quot;
comma
id|header
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* The length in the RFC NB header is the raw data length */
r_return
id|smb_len
c_func
(paren
id|header
)paren
suffix:semicolon
)brace
r_int
DECL|function|smb_recv_available
id|smb_recv_available
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
id|mm_segment_t
id|oldfs
suffix:semicolon
r_int
id|avail
comma
id|err
suffix:semicolon
r_struct
id|socket
op_star
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|err
op_assign
id|sock-&gt;ops
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|sock
comma
id|SIOCINQ
comma
(paren
r_int
r_int
)paren
op_amp
id|avail
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
(paren
id|err
op_ge
l_int|0
)paren
ques
c_cond
id|avail
suffix:colon
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust the kvec to move on &squot;n&squot; bytes (from nfs/sunrpc)&n; */
r_static
r_int
DECL|function|smb_move_iov
id|smb_move_iov
c_func
(paren
r_struct
id|kvec
op_star
op_star
id|data
comma
r_int
op_star
id|num
comma
r_struct
id|kvec
op_star
id|vec
comma
r_int
id|amount
)paren
(brace
r_struct
id|kvec
op_star
id|iv
op_assign
op_star
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Eat any sent kvecs&n;&t; */
r_while
c_loop
(paren
id|iv-&gt;iov_len
op_le
id|amount
)paren
(brace
id|amount
op_sub_assign
id|iv-&gt;iov_len
suffix:semicolon
id|iv
op_increment
suffix:semicolon
(paren
op_star
id|num
)paren
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;And chew down the partial one&n;&t; */
id|vec
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|iv-&gt;iov_len
op_minus
id|amount
suffix:semicolon
id|vec
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|iv-&gt;iov_base
)paren
op_plus
id|amount
suffix:semicolon
id|iv
op_increment
suffix:semicolon
id|len
op_assign
id|vec
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
multiline_comment|/*&n;&t; *&t;And copy any others&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
op_star
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vec
(braket
id|i
)braket
op_assign
op_star
id|iv
op_increment
suffix:semicolon
id|len
op_add_assign
id|vec
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
op_star
id|data
op_assign
id|vec
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * smb_receive_header&n; * Only called by the smbiod thread.&n; */
r_int
DECL|function|smb_receive_header
id|smb_receive_header
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|peek_buf
(braket
l_int|4
)braket
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|server-&gt;smb_read
)paren
(brace
id|result
op_assign
id|smb_get_length
c_func
(paren
id|sock
comma
id|peek_buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENODATA
)paren
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|server-&gt;smb_len
op_assign
id|result
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;smb_len
OL
id|SMB_HEADER_LEN
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;short packet: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|server-&gt;rstate
op_assign
id|SMB_RECV_DROP
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|server-&gt;smb_len
OG
id|SMB_MAX_PACKET_SIZE
)paren
(brace
id|PARANOIA
c_func
(paren
l_string|&quot;long packet: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|server-&gt;rstate
op_assign
id|SMB_RECV_DROP
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|result
op_assign
id|_recvfrom
c_func
(paren
id|sock
comma
id|server-&gt;header
op_plus
id|server-&gt;smb_read
comma
id|SMB_HEADER_LEN
op_minus
id|server-&gt;smb_read
comma
l_int|0
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;_recvfrom: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;receive error: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|server-&gt;smb_read
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;smb_read
op_eq
id|SMB_HEADER_LEN
)paren
id|server-&gt;rstate
op_assign
id|SMB_RECV_HCOMPLETE
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|drop_buffer
r_static
r_char
id|drop_buffer
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * smb_receive_drop - read and throw away the data&n; * Only called by the smbiod thread.&n; *&n; * FIXME: we are in the kernel, could we just tell the socket that we want&n; * to drop stuff from the buffer?&n; */
r_int
DECL|function|smb_receive_drop
id|smb_receive_drop
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
)paren
(brace
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|kvec
id|iov
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_int
id|rlen
op_assign
id|smb_len
c_func
(paren
id|server-&gt;header
)paren
op_minus
id|server-&gt;smb_read
op_plus
l_int|4
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|rlen
OG
id|PAGE_SIZE
)paren
id|rlen
op_assign
id|PAGE_SIZE
suffix:semicolon
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
r_goto
id|out
suffix:semicolon
id|flags
op_assign
id|MSG_DONTWAIT
op_or
id|MSG_NOSIGNAL
suffix:semicolon
id|iov.iov_base
op_assign
id|drop_buffer
suffix:semicolon
id|iov.iov_len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|msg.msg_flags
op_assign
id|flags
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
id|result
op_assign
id|kernel_recvmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
op_amp
id|iov
comma
l_int|1
comma
id|rlen
comma
id|flags
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;read: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;receive error: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|server-&gt;smb_read
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;smb_read
op_ge
id|server-&gt;smb_len
)paren
id|server-&gt;rstate
op_assign
id|SMB_RECV_END
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * smb_receive&n; * Only called by the smbiod thread.&n; */
r_int
DECL|function|smb_receive
id|smb_receive
c_func
(paren
r_struct
id|smb_sb_info
op_star
id|server
comma
r_struct
id|smb_request
op_star
id|req
)paren
(brace
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|kvec
id|iov
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|p
op_assign
id|req-&gt;rq_iov
suffix:semicolon
r_int
id|num
op_assign
id|req-&gt;rq_iovlen
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_int
id|rlen
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
r_goto
id|out
suffix:semicolon
id|flags
op_assign
id|MSG_DONTWAIT
op_or
id|MSG_NOSIGNAL
suffix:semicolon
id|msg.msg_flags
op_assign
id|flags
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|msg.msg_control
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Dont repeat bytes and count available bufferspace */
id|rlen
op_assign
id|smb_move_iov
c_func
(paren
op_amp
id|p
comma
op_amp
id|num
comma
id|iov
comma
id|req-&gt;rq_bytes_recvd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;rq_rlen
OL
id|rlen
)paren
id|rlen
op_assign
id|req-&gt;rq_rlen
suffix:semicolon
id|result
op_assign
id|kernel_recvmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|p
comma
id|num
comma
id|rlen
comma
id|flags
)paren
suffix:semicolon
id|VERBOSE
c_func
(paren
l_string|&quot;read: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|VERBOSE
c_func
(paren
l_string|&quot;receive error: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|req-&gt;rq_bytes_recvd
op_add_assign
id|result
suffix:semicolon
id|server-&gt;smb_read
op_add_assign
id|result
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to send a SMB request. This may return after sending only parts of the&n; * request. SMB_REQ_TRANSMITTED will be set if a request was fully sent.&n; *&n; * Parts of this was taken from xprt_sendmsg from net/sunrpc/xprt.c&n; */
r_int
DECL|function|smb_send_request
id|smb_send_request
c_func
(paren
r_struct
id|smb_request
op_star
id|req
)paren
(brace
r_struct
id|smb_sb_info
op_star
id|server
op_assign
id|req-&gt;rq_server
suffix:semicolon
r_struct
id|socket
op_star
id|sock
suffix:semicolon
r_struct
id|msghdr
id|msg
op_assign
(brace
dot
id|msg_flags
op_assign
id|MSG_NOSIGNAL
op_or
id|MSG_DONTWAIT
)brace
suffix:semicolon
r_int
id|slen
op_assign
id|req-&gt;rq_slen
op_minus
id|req-&gt;rq_bytes_sent
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_struct
id|kvec
id|iov
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|kvec
op_star
id|p
op_assign
id|req-&gt;rq_iov
suffix:semicolon
r_int
id|num
op_assign
id|req-&gt;rq_iovlen
suffix:semicolon
id|sock
op_assign
id|server_sock
c_func
(paren
id|server
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;sk-&gt;sk_state
op_ne
id|TCP_ESTABLISHED
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Dont repeat bytes */
r_if
c_cond
(paren
id|req-&gt;rq_bytes_sent
)paren
id|smb_move_iov
c_func
(paren
op_amp
id|p
comma
op_amp
id|num
comma
id|iov
comma
id|req-&gt;rq_bytes_sent
)paren
suffix:semicolon
id|result
op_assign
id|kernel_sendmsg
c_func
(paren
id|sock
comma
op_amp
id|msg
comma
id|p
comma
id|num
comma
id|slen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|req-&gt;rq_bytes_sent
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;rq_bytes_sent
op_ge
id|req-&gt;rq_slen
)paren
id|req-&gt;rq_flags
op_or_assign
id|SMB_REQ_TRANSMITTED
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
eof
