multiline_comment|/*&n; * linux/arch/parisc/kernel/sys_hpux.c&n; *&n; * implements HPUX syscalls.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|hpux_execve
r_int
id|hpux_execve
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|regs-&gt;gr
(braket
l_int|26
)braket
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;gr
(braket
l_int|25
)braket
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;gr
(braket
l_int|24
)braket
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|struct|hpux_dirent
r_struct
id|hpux_dirent
(brace
DECL|member|d_off
id|loff_t
id|d_off
suffix:semicolon
DECL|member|d_ino
id|ino_t
id|d_ino
suffix:semicolon
DECL|member|d_reclen
r_int
id|d_reclen
suffix:semicolon
DECL|member|d_namlen
r_int
id|d_namlen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|getdents_callback
r_struct
id|getdents_callback
(brace
DECL|member|current_dir
r_struct
id|hpux_dirent
op_star
id|current_dir
suffix:semicolon
DECL|member|previous
r_struct
id|hpux_dirent
op_star
id|previous
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NAME_OFFSET
mdefine_line|#define NAME_OFFSET(de) ((int) ((de)-&gt;d_name - (char *) (de)))
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x) (((x)+sizeof(long)-1) &amp; ~(sizeof(long)-1))
DECL|function|filldir
r_static
r_int
id|filldir
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|loff_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
id|d_type
)paren
(brace
r_struct
id|hpux_dirent
op_star
id|dirent
suffix:semicolon
r_struct
id|getdents_callback
op_star
id|buf
op_assign
(paren
r_struct
id|getdents_callback
op_star
)paren
id|__buf
suffix:semicolon
r_int
id|reclen
op_assign
id|ROUND_UP
c_func
(paren
id|NAME_OFFSET
c_func
(paren
id|dirent
)paren
op_plus
id|namlen
op_plus
l_int|1
)paren
suffix:semicolon
id|buf-&gt;error
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* only used if we fail.. */
r_if
c_cond
(paren
id|reclen
OG
id|buf-&gt;count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;previous
suffix:semicolon
r_if
c_cond
(paren
id|dirent
)paren
id|put_user
c_func
(paren
id|offset
comma
op_amp
id|dirent-&gt;d_off
)paren
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;current_dir
suffix:semicolon
id|buf-&gt;previous
op_assign
id|dirent
suffix:semicolon
id|put_user
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|reclen
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|namlen
comma
op_amp
id|dirent-&gt;d_namlen
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|dirent-&gt;d_name
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
id|dirent-&gt;d_name
op_plus
id|namlen
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|dirent
)paren
op_add_assign
id|reclen
suffix:semicolon
id|buf-&gt;current_dir
op_assign
id|dirent
suffix:semicolon
id|buf-&gt;count
op_sub_assign
id|reclen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|NAME_OFFSET
macro_line|#undef NAME_OFFSET
DECL|macro|ROUND_UP
macro_line|#undef ROUND_UP
DECL|function|hpux_getdents
r_int
id|hpux_getdents
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|hpux_dirent
op_star
id|dirent
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|hpux_dirent
op_star
id|lastdirent
suffix:semicolon
r_struct
id|getdents_callback
id|buf
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
id|buf.current_dir
op_assign
id|dirent
suffix:semicolon
id|buf.previous
op_assign
l_int|NULL
suffix:semicolon
id|buf.count
op_assign
id|count
suffix:semicolon
id|buf.error
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|vfs_readdir
c_func
(paren
id|file
comma
id|filldir
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out_putf
suffix:semicolon
id|error
op_assign
id|buf.error
suffix:semicolon
id|lastdirent
op_assign
id|buf.previous
suffix:semicolon
r_if
c_cond
(paren
id|lastdirent
)paren
(brace
id|put_user
c_func
(paren
id|file-&gt;f_pos
comma
op_amp
id|lastdirent-&gt;d_off
)paren
suffix:semicolon
id|error
op_assign
id|count
op_minus
id|buf.count
suffix:semicolon
)brace
id|out_putf
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|hpux_mount
r_int
id|hpux_mount
c_func
(paren
r_const
r_char
op_star
id|fs
comma
r_const
r_char
op_star
id|path
comma
r_int
id|mflag
comma
r_const
r_char
op_star
id|fstype
comma
r_const
r_char
op_star
id|dataptr
comma
r_int
id|datalen
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|cp_hpux_stat
r_static
r_int
id|cp_hpux_stat
c_func
(paren
r_struct
id|kstat
op_star
id|stat
comma
r_struct
id|hpux_stat64
op_star
id|statbuf
)paren
(brace
r_struct
id|hpux_stat64
id|tmp
suffix:semicolon
multiline_comment|/* we probably want a different split here - is hpux 12:20? */
r_if
c_cond
(paren
op_logical_neg
id|new_valid_dev
c_func
(paren
id|stat-&gt;dev
)paren
op_logical_or
op_logical_neg
id|new_valid_dev
c_func
(paren
id|stat-&gt;rdev
)paren
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|tmp.st_dev
op_assign
id|new_encode_dev
c_func
(paren
id|stat-&gt;dev
)paren
suffix:semicolon
id|tmp.st_ino
op_assign
id|stat-&gt;ino
suffix:semicolon
id|tmp.st_mode
op_assign
id|stat-&gt;mode
suffix:semicolon
id|tmp.st_nlink
op_assign
id|stat-&gt;nlink
suffix:semicolon
id|tmp.st_uid
op_assign
id|stat-&gt;uid
suffix:semicolon
id|tmp.st_gid
op_assign
id|stat-&gt;gid
suffix:semicolon
id|tmp.st_rdev
op_assign
id|new_encode_dev
c_func
(paren
id|stat-&gt;rdev
)paren
suffix:semicolon
id|tmp.st_size
op_assign
id|stat-&gt;size
suffix:semicolon
id|tmp.st_atime
op_assign
id|stat-&gt;atime.tv_sec
suffix:semicolon
id|tmp.st_mtime
op_assign
id|stat-&gt;mtime.tv_sec
suffix:semicolon
id|tmp.st_ctime
op_assign
id|stat-&gt;ctime.tv_sec
suffix:semicolon
id|tmp.st_blocks
op_assign
id|stat-&gt;blocks
suffix:semicolon
id|tmp.st_blksize
op_assign
id|stat-&gt;blksize
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|statbuf
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|hpux_stat64
r_int
id|hpux_stat64
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|hpux_stat64
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_stat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_hpux_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|hpux_fstat64
r_int
id|hpux_fstat64
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|hpux_stat64
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_fstat
c_func
(paren
id|fd
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_hpux_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|hpux_lstat64
r_int
id|hpux_lstat64
c_func
(paren
r_char
op_star
id|filename
comma
r_struct
id|hpux_stat64
op_star
id|statbuf
)paren
(brace
r_struct
id|kstat
id|stat
suffix:semicolon
r_int
id|error
op_assign
id|vfs_lstat
c_func
(paren
id|filename
comma
op_amp
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|cp_hpux_stat
c_func
(paren
op_amp
id|stat
comma
id|statbuf
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
