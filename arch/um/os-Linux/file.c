multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;sys/mount.h&gt;
macro_line|#include &lt;sys/uio.h&gt;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
DECL|function|os_file_type
r_int
id|os_file_type
c_func
(paren
r_char
op_star
id|file
)paren
(brace
r_struct
id|stat64
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|stat64
c_func
(paren
id|file
comma
op_amp
id|buf
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_DIR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_SYMLINK
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_CHARDEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_BLOCKDEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISFIFO
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_FIFO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISSOCK
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_return
id|OS_TYPE_SOCK
suffix:semicolon
)brace
r_else
r_return
id|OS_TYPE_FILE
suffix:semicolon
)brace
DECL|function|os_file_mode
r_int
id|os_file_mode
c_func
(paren
r_char
op_star
id|file
comma
r_struct
id|openflags
op_star
id|mode_out
)paren
(brace
op_star
id|mode_out
op_assign
id|OPENFLAGS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|file
comma
id|W_OK
)paren
)paren
(brace
op_star
id|mode_out
op_assign
id|of_write
c_func
(paren
op_star
id|mode_out
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|errno
op_ne
id|EACCES
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|access
c_func
(paren
id|file
comma
id|R_OK
)paren
)paren
(brace
op_star
id|mode_out
op_assign
id|of_read
c_func
(paren
op_star
id|mode_out
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|errno
op_ne
id|EACCES
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_open_file
r_int
id|os_open_file
c_func
(paren
r_char
op_star
id|file
comma
r_struct
id|openflags
id|flags
comma
r_int
id|mode
)paren
(brace
r_int
id|fd
comma
id|f
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags.r
op_logical_and
id|flags.w
)paren
(brace
id|f
op_assign
id|O_RDWR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags.r
)paren
(brace
id|f
op_assign
id|O_RDONLY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flags.w
)paren
(brace
id|f
op_assign
id|O_WRONLY
suffix:semicolon
)brace
r_else
id|f
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags.s
)paren
(brace
id|f
op_or_assign
id|O_SYNC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags.c
)paren
(brace
id|f
op_or_assign
id|O_CREAT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags.t
)paren
(brace
id|f
op_or_assign
id|O_TRUNC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags.e
)paren
(brace
id|f
op_or_assign
id|O_EXCL
suffix:semicolon
)brace
id|fd
op_assign
id|open64
c_func
(paren
id|file
comma
id|f
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags.cl
)paren
(brace
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFD
comma
l_int|1
)paren
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_return
id|fd
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
DECL|function|os_connect_socket
r_int
id|os_connect_socket
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|sockaddr_un
id|sock
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
id|sock.sun_family
op_assign
id|AF_UNIX
suffix:semicolon
id|snprintf
c_func
(paren
id|sock.sun_path
comma
r_sizeof
(paren
id|sock.sun_path
)paren
comma
l_string|&quot;%s&quot;
comma
id|name
)paren
suffix:semicolon
id|fd
op_assign
id|socket
c_func
(paren
id|AF_UNIX
comma
id|SOCK_STREAM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
id|fd
suffix:semicolon
)brace
id|err
op_assign
id|connect
c_func
(paren
id|fd
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|sock
comma
r_sizeof
(paren
id|sock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|os_close_file
r_void
id|os_close_file
c_func
(paren
r_int
id|fd
)paren
(brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|os_seek_file
r_int
id|os_seek_file
c_func
(paren
r_int
id|fd
comma
id|__u64
id|offset
)paren
(brace
id|__u64
id|actual
suffix:semicolon
id|actual
op_assign
id|lseek64
c_func
(paren
id|fd
comma
id|offset
comma
id|SEEK_SET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|actual
op_ne
id|offset
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_read_file
r_int
id|os_read_file
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|n
suffix:semicolon
multiline_comment|/* Force buf into memory if it&squot;s not already. */
multiline_comment|/* XXX This fails if buf is kernel memory */
macro_line|#ifdef notdef
r_if
c_cond
(paren
id|copy_to_user_proc
c_func
(paren
id|buf
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
macro_line|#endif
id|n
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|os_write_file
r_int
id|os_write_file
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|n
suffix:semicolon
multiline_comment|/* Force buf into memory if it&squot;s not already. */
multiline_comment|/* XXX This fails if buf is kernel memory */
macro_line|#ifdef notdef
r_if
c_cond
(paren
id|copy_to_user_proc
c_func
(paren
id|buf
comma
id|buf
comma
id|buf
(braket
l_int|0
)braket
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
macro_line|#endif
id|n
op_assign
id|write
c_func
(paren
id|fd
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|os_file_size
r_int
id|os_file_size
c_func
(paren
r_char
op_star
id|file
comma
r_int
r_int
op_star
id|size_out
)paren
(brace
r_struct
id|stat64
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|stat64
c_func
(paren
id|file
comma
op_amp
id|buf
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t stat &bslash;&quot;%s&bslash;&quot; : errno = %d&bslash;n&quot;
comma
id|file
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|buf.st_mode
)paren
)paren
(brace
r_int
id|fd
comma
id|blocks
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|open64
c_func
(paren
id|file
comma
id|O_RDONLY
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t open &bslash;&quot;%s&bslash;&quot;, errno = %d&bslash;n&quot;
comma
id|file
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|BLKGETSIZE
comma
op_amp
id|blocks
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t get the block size of &bslash;&quot;%s&bslash;&quot;, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|file
comma
id|errno
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
op_star
id|size_out
op_assign
(paren
(paren
r_int
r_int
)paren
id|blocks
)paren
op_star
l_int|512
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|size_out
op_assign
id|buf.st_size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_pipe
r_int
id|os_pipe
c_func
(paren
r_int
op_star
id|fds
comma
r_int
id|stream
comma
r_int
id|close_on_exec
)paren
(brace
r_int
id|err
comma
id|type
op_assign
id|stream
ques
c_cond
id|SOCK_STREAM
suffix:colon
id|SOCK_DGRAM
suffix:semicolon
id|err
op_assign
id|socketpair
c_func
(paren
id|AF_UNIX
comma
id|type
comma
l_int|0
comma
id|fds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|close_on_exec
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fcntl
c_func
(paren
id|fds
(braket
l_int|0
)braket
comma
id|F_SETFD
comma
l_int|1
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|fcntl
c_func
(paren
id|fds
(braket
l_int|1
)braket
comma
id|F_SETFD
comma
l_int|1
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;os_pipe : Setting FD_CLOEXEC failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_set_fd_async
r_int
id|os_set_fd_async
c_func
(paren
r_int
id|fd
comma
r_int
id|owner
)paren
(brace
multiline_comment|/* XXX This should do F_GETFL first */
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFL
comma
id|O_ASYNC
op_or
id|O_NONBLOCK
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;os_set_fd_async : failed to set O_ASYNC and &quot;
l_string|&quot;O_NONBLOCK on fd # %d, errno = %d&bslash;n&quot;
comma
id|fd
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
macro_line|#ifdef notdef
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFD
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;os_set_fd_async : Setting FD_CLOEXEC failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETSIG
comma
id|SIGIO
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETOWN
comma
id|owner
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;os_set_fd_async : Failed to fcntl F_SETOWN &quot;
l_string|&quot;(or F_SETSIG) fd %d to pid %d, errno = %d&bslash;n&quot;
comma
id|fd
comma
id|owner
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_set_fd_block
r_int
id|os_set_fd_block
c_func
(paren
r_int
id|fd
comma
r_int
id|blocking
)paren
(brace
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_GETFL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blocking
)paren
(brace
id|flags
op_and_assign
op_complement
id|O_NONBLOCK
suffix:semicolon
)brace
r_else
id|flags
op_or_assign
id|O_NONBLOCK
suffix:semicolon
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFL
comma
id|flags
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to change blocking on fd # %d, errno = %d&bslash;n&quot;
comma
id|fd
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_accept_connection
r_int
id|os_accept_connection
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
r_new
suffix:semicolon
r_new
op_assign
id|accept
c_func
(paren
id|fd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
r_new
suffix:semicolon
)brace
macro_line|#ifndef SHUT_RD
DECL|macro|SHUT_RD
mdefine_line|#define SHUT_RD 0
macro_line|#endif
macro_line|#ifndef SHUT_WR
DECL|macro|SHUT_WR
mdefine_line|#define SHUT_WR 1
macro_line|#endif
macro_line|#ifndef SHUT_RDWR
DECL|macro|SHUT_RDWR
mdefine_line|#define SHUT_RDWR 2
macro_line|#endif
DECL|function|os_shutdown_socket
r_int
id|os_shutdown_socket
c_func
(paren
r_int
id|fd
comma
r_int
id|r
comma
r_int
id|w
)paren
(brace
r_int
id|what
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|r
op_logical_and
id|w
)paren
(brace
id|what
op_assign
id|SHUT_RDWR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r
)paren
(brace
id|what
op_assign
id|SHUT_RD
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|w
)paren
(brace
id|what
op_assign
id|SHUT_WR
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;os_shutdown_socket : neither r or w was set&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
id|shutdown
c_func
(paren
id|fd
comma
id|what
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_rcv_fd
r_int
id|os_rcv_fd
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|helper_pid_out
)paren
(brace
r_int
r_new
comma
id|n
suffix:semicolon
r_char
id|buf
(braket
id|CMSG_SPACE
c_func
(paren
r_sizeof
(paren
r_new
)paren
)paren
)braket
suffix:semicolon
r_struct
id|msghdr
id|msg
suffix:semicolon
r_struct
id|cmsghdr
op_star
id|cmsg
suffix:semicolon
r_struct
id|iovec
id|iov
suffix:semicolon
id|msg.msg_name
op_assign
l_int|NULL
suffix:semicolon
id|msg.msg_namelen
op_assign
l_int|0
suffix:semicolon
id|iov
op_assign
(paren
(paren
r_struct
id|iovec
)paren
(brace
dot
id|iov_base
op_assign
id|helper_pid_out
comma
dot
id|iov_len
op_assign
r_sizeof
(paren
op_star
id|helper_pid_out
)paren
)brace
)paren
suffix:semicolon
id|msg.msg_iov
op_assign
op_amp
id|iov
suffix:semicolon
id|msg.msg_iovlen
op_assign
l_int|1
suffix:semicolon
id|msg.msg_control
op_assign
id|buf
suffix:semicolon
id|msg.msg_controllen
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
id|msg.msg_flags
op_assign
l_int|0
suffix:semicolon
id|n
op_assign
id|recvmsg
c_func
(paren
id|fd
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ne
r_sizeof
(paren
id|iov.iov_len
)paren
)paren
(brace
op_star
id|helper_pid_out
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|cmsg
op_assign
id|CMSG_FIRSTHDR
c_func
(paren
op_amp
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmsg
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rcv_fd didn&squot;t receive anything, error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cmsg-&gt;cmsg_level
op_ne
id|SOL_SOCKET
)paren
op_logical_or
(paren
id|cmsg-&gt;cmsg_type
op_ne
id|SCM_RIGHTS
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rcv_fd didn&squot;t receive a descriptor&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_new
op_assign
(paren
(paren
r_int
op_star
)paren
id|CMSG_DATA
c_func
(paren
id|cmsg
)paren
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
DECL|function|create_unix_socket
r_int
id|create_unix_socket
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|len
)paren
(brace
r_struct
id|sockaddr_un
id|addr
suffix:semicolon
r_int
id|sock
comma
id|err
suffix:semicolon
id|sock
op_assign
id|socket
c_func
(paren
id|PF_UNIX
comma
id|SOCK_DGRAM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;create_unix_socket - socket failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|addr.sun_family
op_assign
id|AF_UNIX
suffix:semicolon
multiline_comment|/* XXX Be more careful about overflow */
id|snprintf
c_func
(paren
id|addr.sun_path
comma
id|len
comma
l_string|&quot;%s&quot;
comma
id|file
)paren
suffix:semicolon
id|err
op_assign
id|bind
c_func
(paren
id|sock
comma
(paren
r_struct
id|sockaddr
op_star
)paren
op_amp
id|addr
comma
r_sizeof
(paren
id|addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;create_listening_socket - bind failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|sock
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
