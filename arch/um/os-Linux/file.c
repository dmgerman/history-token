multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;sys/mount.h&gt;
macro_line|#include &lt;sys/uio.h&gt;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
DECL|function|copy_stat
r_static
r_void
id|copy_stat
c_func
(paren
r_struct
id|uml_stat
op_star
id|dst
comma
r_struct
id|stat64
op_star
id|src
)paren
(brace
op_star
id|dst
op_assign
(paren
(paren
r_struct
id|uml_stat
)paren
(brace
dot
id|ust_dev
op_assign
id|src-&gt;st_dev
comma
multiline_comment|/* device */
dot
id|ust_ino
op_assign
id|src-&gt;st_ino
comma
multiline_comment|/* inode */
dot
id|ust_mode
op_assign
id|src-&gt;st_mode
comma
multiline_comment|/* protection */
dot
id|ust_nlink
op_assign
id|src-&gt;st_nlink
comma
multiline_comment|/* number of hard links */
dot
id|ust_uid
op_assign
id|src-&gt;st_uid
comma
multiline_comment|/* user ID of owner */
dot
id|ust_gid
op_assign
id|src-&gt;st_gid
comma
multiline_comment|/* group ID of owner */
dot
id|ust_size
op_assign
id|src-&gt;st_size
comma
multiline_comment|/* total size, in bytes */
dot
id|ust_blksize
op_assign
id|src-&gt;st_blksize
comma
multiline_comment|/* blocksize for filesys I/O */
dot
id|ust_blocks
op_assign
id|src-&gt;st_blocks
comma
multiline_comment|/* number of blocks allocated */
dot
id|ust_atime
op_assign
id|src-&gt;st_atime
comma
multiline_comment|/* time of last access */
dot
id|ust_mtime
op_assign
id|src-&gt;st_mtime
comma
multiline_comment|/* time of last modification */
dot
id|ust_ctime
op_assign
id|src-&gt;st_ctime
comma
multiline_comment|/* time of last change */
)brace
)paren
suffix:semicolon
)brace
DECL|function|os_stat_fd
r_int
id|os_stat_fd
c_func
(paren
r_const
r_int
id|fd
comma
r_struct
id|uml_stat
op_star
id|ubuf
)paren
(brace
r_struct
id|stat64
id|sbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
r_do
(brace
id|err
op_assign
id|fstat64
c_func
(paren
id|fd
comma
op_amp
id|sbuf
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
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
id|ubuf
op_ne
l_int|NULL
)paren
(brace
id|copy_stat
c_func
(paren
id|ubuf
comma
op_amp
id|sbuf
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|os_stat_file
r_int
id|os_stat_file
c_func
(paren
r_const
r_char
op_star
id|file_name
comma
r_struct
id|uml_stat
op_star
id|ubuf
)paren
(brace
r_struct
id|stat64
id|sbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
r_do
(brace
id|err
op_assign
id|stat64
c_func
(paren
id|file_name
comma
op_amp
id|sbuf
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
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
id|ubuf
op_ne
l_int|NULL
)paren
(brace
id|copy_stat
c_func
(paren
id|ubuf
comma
op_amp
id|sbuf
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|os_access
r_int
id|os_access
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|mode
)paren
(brace
r_int
id|amode
comma
id|err
suffix:semicolon
id|amode
op_assign
(paren
id|mode
op_amp
id|OS_ACC_R_OK
ques
c_cond
id|R_OK
suffix:colon
l_int|0
)paren
op_or
(paren
id|mode
op_amp
id|OS_ACC_W_OK
ques
c_cond
id|W_OK
suffix:colon
l_int|0
)paren
op_or
(paren
id|mode
op_amp
id|OS_ACC_X_OK
ques
c_cond
id|X_OK
suffix:colon
l_int|0
)paren
op_or
(paren
id|mode
op_amp
id|OS_ACC_F_OK
ques
c_cond
id|F_OK
suffix:colon
l_int|0
)paren
suffix:semicolon
id|err
op_assign
id|access
c_func
(paren
id|file
comma
id|amode
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
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_print_error
r_void
id|os_print_error
c_func
(paren
r_int
id|error
comma
r_const
r_char
op_star
id|str
)paren
(brace
id|errno
op_assign
id|error
OL
l_int|0
ques
c_cond
op_minus
id|error
suffix:colon
id|error
suffix:semicolon
id|perror
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME? required only by hostaudio (because it passes ioctls verbatim) */
DECL|function|os_ioctl_generic
r_int
id|os_ioctl_generic
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
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
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|os_window_size
r_int
id|os_window_size
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|rows
comma
r_int
op_star
id|cols
)paren
(brace
r_struct
id|winsize
id|size
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|TIOCGWINSZ
comma
op_amp
id|size
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
op_star
id|rows
op_assign
id|size.ws_row
suffix:semicolon
op_star
id|cols
op_assign
id|size.ws_col
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_new_tty_pgrp
r_int
id|os_new_tty_pgrp
c_func
(paren
r_int
id|fd
comma
r_int
id|pid
)paren
(brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|TIOCSCTTY
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TIOCSCTTY failed, errno = %d&bslash;n&quot;
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
id|tcsetpgrp
c_func
(paren
id|fd
comma
id|pid
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tcsetpgrp failed, errno = %d&bslash;n&quot;
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
multiline_comment|/* FIXME: ensure namebuf in os_get_if_name is big enough */
DECL|function|os_get_ifname
r_int
id|os_get_ifname
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|namebuf
)paren
(brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFNAME
comma
id|namebuf
)paren
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
l_int|0
suffix:semicolon
)brace
DECL|function|os_set_slip
r_int
id|os_set_slip
c_func
(paren
r_int
id|fd
)paren
(brace
r_int
id|disc
comma
id|sencap
suffix:semicolon
id|disc
op_assign
id|N_SLIP
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|TIOCSETD
comma
op_amp
id|disc
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to set slip line discipline - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|sencap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFENCAP
comma
op_amp
id|sencap
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to set slip encapsulation - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
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
DECL|function|os_set_owner
r_int
id|os_set_owner
c_func
(paren
r_int
id|fd
comma
r_int
id|pid
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
id|F_SETOWN
comma
id|pid
)paren
OL
l_int|0
)paren
(brace
r_int
id|save_errno
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fd
comma
id|F_GETOWN
comma
l_int|0
)paren
op_ne
id|pid
)paren
(brace
r_return
op_minus
id|save_errno
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* FIXME? moved wholesale from sigio_user.c to get fcntls out of that file */
DECL|function|os_sigio_async
r_int
id|os_sigio_async
c_func
(paren
r_int
id|master
comma
r_int
id|slave
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
id|master
comma
id|F_GETFL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fcntl F_GETFL failed, errno = %d&bslash;n&quot;
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
(paren
id|fcntl
c_func
(paren
id|master
comma
id|F_SETFL
comma
id|flags
op_or
id|O_NONBLOCK
op_or
id|O_ASYNC
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|fcntl
c_func
(paren
id|master
comma
id|F_SETOWN
comma
id|os_getpid
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fcntl F_SETFL or F_SETOWN failed, errno = %d&bslash;n&quot;
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
(paren
id|fcntl
c_func
(paren
id|slave
comma
id|F_SETFL
comma
id|flags
op_or
id|O_NONBLOCK
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fcntl F_SETFL failed, errno = %d&bslash;n&quot;
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
DECL|function|os_mode_fd
r_int
id|os_mode_fd
c_func
(paren
r_int
id|fd
comma
r_int
id|mode
)paren
(brace
r_int
id|err
suffix:semicolon
r_do
(brace
id|err
op_assign
id|fchmod
c_func
(paren
id|fd
comma
id|mode
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
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
l_int|0
suffix:semicolon
)brace
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
id|uml_stat
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|os_stat_file
c_func
(paren
id|file
comma
op_amp
id|buf
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
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|buf.ust_mode
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
id|buf.ust_mode
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
id|buf.ust_mode
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
id|buf.ust_mode
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
id|buf.ust_mode
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
id|buf.ust_mode
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
r_int
id|err
suffix:semicolon
op_star
id|mode_out
op_assign
id|OPENFLAGS
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|os_access
c_func
(paren
id|file
comma
id|OS_ACC_W_OK
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|err
op_ne
op_minus
id|EACCES
)paren
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
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
id|err
op_assign
id|os_access
c_func
(paren
id|file
comma
id|OS_ACC_R_OK
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|err
op_ne
op_minus
id|EACCES
)paren
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
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
op_logical_and
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
id|os_close_file
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
op_minus
id|errno
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
DECL|function|fault_buffer
r_static
r_int
id|fault_buffer
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|len
comma
r_int
(paren
op_star
id|copy_proc
)paren
(paren
r_void
op_star
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
)paren
(brace
r_int
id|page
op_assign
id|getpagesize
c_func
(paren
)paren
comma
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
id|page
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|copy_proc
)paren
(paren
id|start
op_plus
id|i
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
)brace
r_if
c_cond
(paren
(paren
id|len
op_mod
id|page
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|copy_proc
)paren
(paren
id|start
op_plus
id|len
op_minus
l_int|1
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|file_io
r_static
r_int
id|file_io
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
comma
r_int
(paren
op_star
id|io_proc
)paren
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
comma
r_int
(paren
op_star
id|copy_user_proc
)paren
(paren
r_void
op_star
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
)paren
(brace
r_int
id|n
comma
id|err
suffix:semicolon
r_do
(brace
id|n
op_assign
(paren
op_star
id|io_proc
)paren
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
(paren
id|n
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EFAULT
)paren
)paren
(brace
id|err
op_assign
id|fault_buffer
c_func
(paren
id|buf
comma
id|len
comma
id|copy_user_proc
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
id|n
op_assign
(paren
op_star
id|io_proc
)paren
(paren
id|fd
comma
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|n
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
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
r_return
id|file_io
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
)paren
id|read
comma
id|copy_from_user_proc
)paren
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
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_return
id|file_io
c_func
(paren
id|fd
comma
(paren
r_void
op_star
)paren
id|buf
comma
id|len
comma
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
)paren
id|write
comma
id|copy_to_user_proc
)paren
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
id|uml_stat
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|os_stat_file
c_func
(paren
id|file
comma
op_amp
id|buf
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
l_string|&quot;Couldn&squot;t stat &bslash;&quot;%s&bslash;&quot; : err = %d&bslash;n&quot;
comma
id|file
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|buf.ust_mode
)paren
)paren
(brace
r_int
id|fd
comma
id|blocks
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
id|file
comma
id|of_read
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
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
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t open &bslash;&quot;%s&bslash;&quot;, errno = %d&bslash;n&quot;
comma
id|file
comma
op_minus
id|fd
)paren
suffix:semicolon
r_return
id|fd
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
id|err
op_assign
op_minus
id|errno
suffix:semicolon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|err
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
id|os_close_file
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
id|buf.ust_size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_file_modtime
r_int
id|os_file_modtime
c_func
(paren
r_char
op_star
id|file
comma
r_int
r_int
op_star
id|modtime
)paren
(brace
r_struct
id|uml_stat
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|os_stat_file
c_func
(paren
id|file
comma
op_amp
id|buf
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
l_string|&quot;Couldn&squot;t stat &bslash;&quot;%s&bslash;&quot; : err = %d&bslash;n&quot;
comma
id|file
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
op_star
id|modtime
op_assign
id|buf.ust_mtime
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_get_exec_close
r_int
id|os_get_exec_close
c_func
(paren
r_int
id|fd
comma
r_int
op_star
id|close_on_exec
)paren
(brace
r_int
id|ret
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_GETFD
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|ret
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
op_star
id|close_on_exec
op_assign
(paren
id|ret
op_amp
id|FD_CLOEXEC
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|os_set_exec_close
r_int
id|os_set_exec_close
c_func
(paren
r_int
id|fd
comma
r_int
id|close_on_exec
)paren
(brace
r_int
id|flag
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|close_on_exec
)paren
(brace
id|flag
op_assign
id|FD_CLOEXEC
suffix:semicolon
)brace
r_else
id|flag
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|err
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFD
comma
id|flag
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|err
OL
l_int|0
)paren
op_logical_and
(paren
id|errno
op_eq
id|EINTR
)paren
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
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
id|err
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
op_logical_neg
id|close_on_exec
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|err
op_assign
id|os_set_exec_close
c_func
(paren
id|fds
(braket
l_int|0
)braket
comma
l_int|1
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
r_goto
id|error
suffix:semicolon
)brace
id|err
op_assign
id|os_set_exec_close
c_func
(paren
id|fds
(braket
l_int|1
)braket
comma
l_int|1
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
r_goto
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|printk
c_func
(paren
l_string|&quot;os_pipe : Setting FD_CLOEXEC failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fds
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|err
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
DECL|function|os_create_unix_socket
r_int
id|os_create_unix_socket
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|len
comma
r_int
id|close_on_exec
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
r_if
c_cond
(paren
id|close_on_exec
)paren
(brace
id|err
op_assign
id|os_set_exec_close
c_func
(paren
id|sock
comma
l_int|1
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
l_string|&quot;create_unix_socket : close_on_exec failed, &quot;
l_string|&quot;err = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
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
l_string|&quot;create_listening_socket at &squot;%s&squot; - bind failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
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
r_return
id|sock
suffix:semicolon
)brace
DECL|function|os_flush_stdout
r_void
id|os_flush_stdout
c_func
(paren
r_void
)paren
(brace
id|fflush
c_func
(paren
id|stdout
)paren
suffix:semicolon
)brace
DECL|function|os_lock_file
r_int
id|os_lock_file
c_func
(paren
r_int
id|fd
comma
r_int
id|excl
)paren
(brace
r_int
id|type
op_assign
id|excl
ques
c_cond
id|F_WRLCK
suffix:colon
id|F_RDLCK
suffix:semicolon
r_struct
id|flock
id|lock
op_assign
(paren
(paren
r_struct
id|flock
)paren
(brace
dot
id|l_type
op_assign
id|type
comma
dot
id|l_whence
op_assign
id|SEEK_SET
comma
dot
id|l_start
op_assign
l_int|0
comma
dot
id|l_len
op_assign
l_int|0
)brace
)paren
suffix:semicolon
r_int
id|err
comma
id|save
suffix:semicolon
id|err
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETLK
comma
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|save
op_assign
op_minus
id|errno
suffix:semicolon
id|err
op_assign
id|fcntl
c_func
(paren
id|fd
comma
id|F_GETLK
comma
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|err
op_assign
op_minus
id|errno
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;F_SETLK failed, file already locked by pid %d&bslash;n&quot;
comma
id|lock.l_pid
)paren
suffix:semicolon
id|err
op_assign
id|save
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
