multiline_comment|/*&n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;dirent.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;utime.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/vfs.h&gt;
macro_line|#include &quot;hostfs.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
DECL|function|stat_file
r_int
id|stat_file
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
r_int
op_star
id|inode_out
comma
r_int
op_star
id|mode_out
comma
r_int
op_star
id|nlink_out
comma
r_int
op_star
id|uid_out
comma
r_int
op_star
id|gid_out
comma
r_int
r_int
r_int
op_star
id|size_out
comma
r_struct
id|timespec
op_star
id|atime_out
comma
r_struct
id|timespec
op_star
id|mtime_out
comma
r_struct
id|timespec
op_star
id|ctime_out
comma
r_int
op_star
id|blksize_out
comma
r_int
r_int
r_int
op_star
id|blocks_out
)paren
(brace
r_struct
id|stat64
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|lstat64
c_func
(paren
id|path
comma
op_amp
id|buf
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
multiline_comment|/* See the Makefile for why STAT64_INO_FIELD is passed in&n;&t; * by the build&n;&t; */
r_if
c_cond
(paren
id|inode_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|inode_out
op_assign
id|buf.STAT64_INO_FIELD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mode_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|mode_out
op_assign
id|buf.st_mode
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nlink_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|nlink_out
op_assign
id|buf.st_nlink
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uid_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|uid_out
op_assign
id|buf.st_uid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gid_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|gid_out
op_assign
id|buf.st_gid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|size_out
op_assign
id|buf.st_size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atime_out
op_ne
l_int|NULL
)paren
(brace
id|atime_out-&gt;tv_sec
op_assign
id|buf.st_atime
suffix:semicolon
id|atime_out-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mtime_out
op_ne
l_int|NULL
)paren
(brace
id|mtime_out-&gt;tv_sec
op_assign
id|buf.st_mtime
suffix:semicolon
id|mtime_out-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctime_out
op_ne
l_int|NULL
)paren
(brace
id|ctime_out-&gt;tv_sec
op_assign
id|buf.st_ctime
suffix:semicolon
id|ctime_out-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|blksize_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|blksize_out
op_assign
id|buf.st_blksize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|blocks_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|blocks_out
op_assign
id|buf.st_blocks
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|file_type
r_int
id|file_type
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
op_star
id|maj
comma
r_int
op_star
id|min
)paren
(brace
r_struct
id|stat64
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|lstat64
c_func
(paren
id|path
comma
op_amp
id|buf
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
multiline_comment|/*We cannot pass rdev as is because glibc and the kernel disagree&n;&t; *about its definition.*/
r_if
c_cond
(paren
id|maj
op_ne
l_int|NULL
)paren
(brace
op_star
id|maj
op_assign
id|major
c_func
(paren
id|buf.st_rdev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|min
op_ne
l_int|NULL
)paren
(brace
op_star
id|min
op_assign
id|minor
c_func
(paren
id|buf.st_rdev
)paren
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
DECL|function|access_file
r_int
id|access_file
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
(brace
r_int
id|mode
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
id|mode
op_assign
id|R_OK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|w
)paren
(brace
id|mode
op_or_assign
id|W_OK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
)paren
(brace
id|mode
op_or_assign
id|X_OK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|access
c_func
(paren
id|path
comma
id|mode
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_file
r_int
id|open_file
c_func
(paren
r_char
op_star
id|path
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|append
)paren
(brace
r_int
id|mode
op_assign
l_int|0
comma
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|r
op_logical_and
op_logical_neg
id|w
)paren
(brace
id|mode
op_assign
id|O_RDONLY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|r
op_logical_and
id|w
)paren
(brace
id|mode
op_assign
id|O_WRONLY
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r
op_logical_and
id|w
)paren
(brace
id|mode
op_assign
id|O_RDWR
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;Impossible mode in open_file&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|append
)paren
(brace
id|mode
op_or_assign
id|O_APPEND
suffix:semicolon
)brace
id|fd
op_assign
id|open64
c_func
(paren
id|path
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
r_else
r_return
id|fd
suffix:semicolon
)brace
DECL|function|open_dir
r_void
op_star
id|open_dir
c_func
(paren
r_char
op_star
id|path
comma
r_int
op_star
id|err_out
)paren
(brace
id|DIR
op_star
id|dir
suffix:semicolon
id|dir
op_assign
id|opendir
c_func
(paren
id|path
)paren
suffix:semicolon
op_star
id|err_out
op_assign
id|errno
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|dir
suffix:semicolon
)brace
DECL|function|read_dir
r_char
op_star
id|read_dir
c_func
(paren
r_void
op_star
id|stream
comma
r_int
r_int
r_int
op_star
id|pos
comma
r_int
r_int
r_int
op_star
id|ino_out
comma
r_int
op_star
id|len_out
)paren
(brace
id|DIR
op_star
id|dir
op_assign
id|stream
suffix:semicolon
r_struct
id|dirent
op_star
id|ent
suffix:semicolon
id|seekdir
c_func
(paren
id|dir
comma
op_star
id|pos
)paren
suffix:semicolon
id|ent
op_assign
id|readdir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|len_out
op_assign
id|strlen
c_func
(paren
id|ent-&gt;d_name
)paren
suffix:semicolon
op_star
id|ino_out
op_assign
id|ent-&gt;d_ino
suffix:semicolon
op_star
id|pos
op_assign
id|telldir
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
id|ent-&gt;d_name
suffix:semicolon
)brace
DECL|function|read_file
r_int
id|read_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
r_int
op_star
id|offset
comma
r_char
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
id|n
op_assign
id|pread64
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
op_star
id|offset
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
op_star
id|offset
op_add_assign
id|n
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|write_file
r_int
id|write_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
r_int
op_star
id|offset
comma
r_const
r_char
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
id|n
op_assign
id|pwrite64
c_func
(paren
id|fd
comma
id|buf
comma
id|len
comma
op_star
id|offset
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
op_star
id|offset
op_add_assign
id|n
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|lseek_file
r_int
id|lseek_file
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|offset
comma
r_int
id|whence
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|lseek64
c_func
(paren
id|fd
comma
id|offset
comma
id|whence
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|close_file
r_void
id|close_file
c_func
(paren
r_void
op_star
id|stream
)paren
(brace
id|close
c_func
(paren
op_star
(paren
(paren
r_int
op_star
)paren
id|stream
)paren
)paren
suffix:semicolon
)brace
DECL|function|close_dir
r_void
id|close_dir
c_func
(paren
r_void
op_star
id|stream
)paren
(brace
id|closedir
c_func
(paren
id|stream
)paren
suffix:semicolon
)brace
DECL|function|file_create
r_int
id|file_create
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|ur
comma
r_int
id|uw
comma
r_int
id|ux
comma
r_int
id|gr
comma
r_int
id|gw
comma
r_int
id|gx
comma
r_int
op_logical_or
comma
r_int
id|ow
comma
r_int
id|ox
)paren
(brace
r_int
id|mode
comma
id|fd
suffix:semicolon
id|mode
op_assign
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|ur
ques
c_cond
id|S_IRUSR
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|uw
ques
c_cond
id|S_IWUSR
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|ux
ques
c_cond
id|S_IXUSR
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|gr
ques
c_cond
id|S_IRGRP
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|gw
ques
c_cond
id|S_IWGRP
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|gx
ques
c_cond
id|S_IXGRP
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
op_logical_or
ques
c_cond
id|S_IROTH
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|ow
ques
c_cond
id|S_IWOTH
suffix:colon
l_int|0
suffix:semicolon
id|mode
op_or_assign
id|ox
ques
c_cond
id|S_IXOTH
suffix:colon
l_int|0
suffix:semicolon
id|fd
op_assign
id|open64
c_func
(paren
id|name
comma
id|O_CREAT
op_or
id|O_RDWR
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
r_return
id|fd
suffix:semicolon
)brace
DECL|function|set_attr
r_int
id|set_attr
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_struct
id|hostfs_iattr
op_star
id|attrs
)paren
(brace
r_struct
id|utimbuf
id|buf
suffix:semicolon
r_int
id|err
comma
id|ma
suffix:semicolon
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_MODE
)paren
(brace
r_if
c_cond
(paren
id|chmod
c_func
(paren
id|file
comma
id|attrs-&gt;ia_mode
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_UID
)paren
(brace
r_if
c_cond
(paren
id|chown
c_func
(paren
id|file
comma
id|attrs-&gt;ia_uid
comma
op_minus
l_int|1
)paren
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_GID
)paren
(brace
r_if
c_cond
(paren
id|chown
c_func
(paren
id|file
comma
op_minus
l_int|1
comma
id|attrs-&gt;ia_gid
)paren
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_SIZE
)paren
(brace
r_if
c_cond
(paren
id|truncate
c_func
(paren
id|file
comma
id|attrs-&gt;ia_size
)paren
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
id|ma
op_assign
id|HOSTFS_ATTR_ATIME_SET
op_or
id|HOSTFS_ATTR_MTIME_SET
suffix:semicolon
r_if
c_cond
(paren
(paren
id|attrs-&gt;ia_valid
op_amp
id|ma
)paren
op_eq
id|ma
)paren
(brace
id|buf.actime
op_assign
id|attrs-&gt;ia_atime.tv_sec
suffix:semicolon
id|buf.modtime
op_assign
id|attrs-&gt;ia_mtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|utime
c_func
(paren
id|file
comma
op_amp
id|buf
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|timespec
id|ts
suffix:semicolon
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_ATIME_SET
)paren
(brace
id|err
op_assign
id|stat_file
c_func
(paren
id|file
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|ts
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|buf.actime
op_assign
id|attrs-&gt;ia_atime.tv_sec
suffix:semicolon
id|buf.modtime
op_assign
id|ts.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|utime
c_func
(paren
id|file
comma
op_amp
id|buf
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_MTIME_SET
)paren
(brace
id|err
op_assign
id|stat_file
c_func
(paren
id|file
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|ts
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|buf.actime
op_assign
id|ts.tv_sec
suffix:semicolon
id|buf.modtime
op_assign
id|attrs-&gt;ia_mtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|utime
c_func
(paren
id|file
comma
op_amp
id|buf
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
id|HOSTFS_ATTR_CTIME
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|attrs-&gt;ia_valid
op_amp
(paren
id|HOSTFS_ATTR_ATIME
op_or
id|HOSTFS_ATTR_MTIME
)paren
)paren
(brace
id|err
op_assign
id|stat_file
c_func
(paren
id|file
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|attrs-&gt;ia_atime
comma
op_amp
id|attrs-&gt;ia_mtime
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|make_symlink
r_int
id|make_symlink
c_func
(paren
r_const
r_char
op_star
id|from
comma
r_const
r_char
op_star
id|to
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|symlink
c_func
(paren
id|to
comma
id|from
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
DECL|function|unlink_file
r_int
id|unlink_file
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|unlink
c_func
(paren
id|file
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
DECL|function|do_mkdir
r_int
id|do_mkdir
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
id|err
suffix:semicolon
id|err
op_assign
id|mkdir
c_func
(paren
id|file
comma
id|mode
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
DECL|function|do_rmdir
r_int
id|do_rmdir
c_func
(paren
r_const
r_char
op_star
id|file
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|rmdir
c_func
(paren
id|file
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
DECL|function|do_mknod
r_int
id|do_mknod
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|mode
comma
r_int
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|mknod
c_func
(paren
id|file
comma
id|mode
comma
id|dev
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
DECL|function|link_file
r_int
id|link_file
c_func
(paren
r_const
r_char
op_star
id|to
comma
r_const
r_char
op_star
id|from
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|link
c_func
(paren
id|to
comma
id|from
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
DECL|function|do_readlink
r_int
id|do_readlink
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|readlink
c_func
(paren
id|file
comma
id|buf
comma
id|size
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
r_if
c_cond
(paren
id|n
OL
id|size
)paren
(brace
id|buf
(braket
id|n
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|rename_file
r_int
id|rename_file
c_func
(paren
r_char
op_star
id|from
comma
r_char
op_star
id|to
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|rename
c_func
(paren
id|from
comma
id|to
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
DECL|function|do_statfs
r_int
id|do_statfs
c_func
(paren
r_char
op_star
id|root
comma
r_int
op_star
id|bsize_out
comma
r_int
r_int
op_star
id|blocks_out
comma
r_int
r_int
op_star
id|bfree_out
comma
r_int
r_int
op_star
id|bavail_out
comma
r_int
r_int
op_star
id|files_out
comma
r_int
r_int
op_star
id|ffree_out
comma
r_void
op_star
id|fsid_out
comma
r_int
id|fsid_size
comma
r_int
op_star
id|namelen_out
comma
r_int
op_star
id|spare_out
)paren
(brace
r_struct
id|statfs64
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|statfs64
c_func
(paren
id|root
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
op_minus
id|errno
suffix:semicolon
)brace
op_star
id|bsize_out
op_assign
id|buf.f_bsize
suffix:semicolon
op_star
id|blocks_out
op_assign
id|buf.f_blocks
suffix:semicolon
op_star
id|bfree_out
op_assign
id|buf.f_bfree
suffix:semicolon
op_star
id|bavail_out
op_assign
id|buf.f_bavail
suffix:semicolon
op_star
id|files_out
op_assign
id|buf.f_files
suffix:semicolon
op_star
id|ffree_out
op_assign
id|buf.f_ffree
suffix:semicolon
id|memcpy
c_func
(paren
id|fsid_out
comma
op_amp
id|buf.f_fsid
comma
r_sizeof
(paren
id|buf.f_fsid
)paren
OG
id|fsid_size
ques
c_cond
id|fsid_size
suffix:colon
r_sizeof
(paren
id|buf.f_fsid
)paren
)paren
suffix:semicolon
op_star
id|namelen_out
op_assign
id|buf.f_namelen
suffix:semicolon
id|spare_out
(braket
l_int|0
)braket
op_assign
id|buf.f_spare
(braket
l_int|0
)braket
suffix:semicolon
id|spare_out
(braket
l_int|1
)braket
op_assign
id|buf.f_spare
(braket
l_int|1
)braket
suffix:semicolon
id|spare_out
(braket
l_int|2
)braket
op_assign
id|buf.f_spare
(braket
l_int|2
)braket
suffix:semicolon
id|spare_out
(braket
l_int|3
)braket
op_assign
id|buf.f_spare
(braket
l_int|3
)braket
suffix:semicolon
id|spare_out
(braket
l_int|4
)braket
op_assign
id|buf.f_spare
(braket
l_int|4
)braket
suffix:semicolon
id|spare_out
(braket
l_int|5
)braket
op_assign
id|buf.f_spare
(braket
l_int|5
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
