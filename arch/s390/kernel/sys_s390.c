multiline_comment|/*&n; *  arch/s390/kernel/sys_s390.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *&n; *  Derived from &quot;arch/i386/kernel/sys_i386.c&quot;&n; *&n; *  This file contains various random system calls that&n; *  have a non-standard calling sequence on the Linux/s390&n; *  platform.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way Unix traditionally does this, though.&n; */
DECL|function|sys_pipe
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_int
r_int
op_star
id|fildes
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_pipe
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|fildes
comma
id|fd
comma
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* common code for old and new mmaps */
DECL|function|do_mmap2
r_static
r_inline
r_int
id|do_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
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
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap_pgoff
c_func
(paren
id|file
comma
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|pgoff
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
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
multiline_comment|/*&n; * Perform the select(nd, in, out, ex, tv) and mmap() system&n; * calls. Linux for S/390 isn&squot;t able to handle more than 5&n; * system call parameters, so these system calls used a memory&n; * block for parameter passing..&n; */
DECL|struct|mmap_arg_struct
r_struct
id|mmap_arg_struct
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|prot
r_int
r_int
id|prot
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|fd
r_int
r_int
id|fd
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sys_mmap2
id|asmlinkage
r_int
id|sys_mmap2
c_func
(paren
r_struct
id|mmap_arg_struct
op_star
id|arg
)paren
(brace
r_struct
id|mmap_arg_struct
id|a
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
id|a
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_mmap2
c_func
(paren
id|a.addr
comma
id|a.len
comma
id|a.prot
comma
id|a.flags
comma
id|a.fd
comma
id|a.offset
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|old_mmap
id|asmlinkage
r_int
id|old_mmap
c_func
(paren
r_struct
id|mmap_arg_struct
op_star
id|arg
)paren
(brace
r_struct
id|mmap_arg_struct
id|a
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
id|a
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|a.offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_mmap2
c_func
(paren
id|a.addr
comma
id|a.len
comma
id|a.prot
comma
id|a.flags
comma
id|a.fd
comma
id|a.offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_extern
id|asmlinkage
r_int
id|sys_select
c_func
(paren
r_int
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
id|fd_set
op_star
comma
r_struct
id|timeval
op_star
)paren
suffix:semicolon
DECL|struct|sel_arg_struct
r_struct
id|sel_arg_struct
(brace
DECL|member|n
r_int
r_int
id|n
suffix:semicolon
DECL|member|inp
DECL|member|outp
DECL|member|exp
id|fd_set
op_star
id|inp
comma
op_star
id|outp
comma
op_star
id|exp
suffix:semicolon
DECL|member|tvp
r_struct
id|timeval
op_star
id|tvp
suffix:semicolon
)brace
suffix:semicolon
DECL|function|old_select
id|asmlinkage
r_int
id|old_select
c_func
(paren
r_struct
id|sel_arg_struct
op_star
id|arg
)paren
(brace
r_struct
id|sel_arg_struct
id|a
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|a
comma
id|arg
comma
r_sizeof
(paren
id|a
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* sys_select() does the appropriate kernel locking */
r_return
id|sys_select
c_func
(paren
id|a.n
comma
id|a.inp
comma
id|a.outp
comma
id|a.exp
comma
id|a.tvp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
r_int
id|sys_ipc
(paren
id|uint
id|call
comma
r_int
id|first
comma
r_int
id|second
comma
r_int
id|third
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|ipc_kludge
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
r_return
id|sys_semop
(paren
id|first
comma
(paren
r_struct
id|sembuf
op_star
)paren
id|ptr
comma
id|second
)paren
suffix:semicolon
r_case
id|SEMGET
suffix:colon
r_return
id|sys_semget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
(brace
r_union
id|semun
id|fourth
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|fourth.__pad
comma
(paren
r_void
op_star
op_star
)paren
id|ptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_semctl
(paren
id|first
comma
id|second
comma
id|third
comma
id|fourth
)paren
suffix:semicolon
)brace
r_case
id|MSGSND
suffix:colon
r_return
id|sys_msgsnd
(paren
id|first
comma
(paren
r_struct
id|msgbuf
op_star
)paren
id|ptr
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MSGRCV
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|tmp
comma
(paren
r_struct
id|ipc_kludge
op_star
)paren
id|ptr
comma
r_sizeof
(paren
r_struct
id|ipc_kludge
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sys_msgrcv
(paren
id|first
comma
id|tmp.msgp
comma
id|second
comma
id|tmp.msgtyp
comma
id|third
)paren
suffix:semicolon
r_case
id|MSGGET
suffix:colon
r_return
id|sys_msgget
(paren
(paren
id|key_t
)paren
id|first
comma
id|second
)paren
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
r_return
id|sys_msgctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|msqid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_case
id|SHMAT
suffix:colon
(brace
id|ulong
id|raddr
suffix:semicolon
id|ret
op_assign
id|sys_shmat
(paren
id|first
comma
(paren
r_char
op_star
)paren
id|ptr
comma
id|second
comma
op_amp
id|raddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
id|put_user
(paren
id|raddr
comma
(paren
id|ulong
op_star
)paren
id|third
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|SHMDT
suffix:colon
r_return
id|sys_shmdt
(paren
(paren
r_char
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_case
id|SHMGET
suffix:colon
r_return
id|sys_shmget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
r_return
id|sys_shmctl
(paren
id|first
comma
id|second
comma
(paren
r_struct
id|shmid_ds
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Old cruft&n; */
DECL|function|sys_uname
id|asmlinkage
r_int
id|sys_uname
c_func
(paren
r_struct
id|old_utsname
op_star
id|name
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|name
comma
op_amp
id|system_utsname
comma
r_sizeof
(paren
op_star
id|name
)paren
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|err
ques
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|sys_olduname
id|asmlinkage
r_int
id|sys_olduname
c_func
(paren
r_struct
id|oldold_utsname
op_star
id|name
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|name
comma
r_sizeof
(paren
r_struct
id|oldold_utsname
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;sysname
comma
op_amp
id|system_utsname.sysname
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;sysname
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;nodename
comma
op_amp
id|system_utsname.nodename
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;nodename
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;release
comma
op_amp
id|system_utsname.release
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;release
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;version
comma
op_amp
id|system_utsname.version
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;version
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|name-&gt;machine
comma
op_amp
id|system_utsname.machine
comma
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|error
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
id|name-&gt;machine
op_plus
id|__OLD_UTS_LEN
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|error
op_assign
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
eof
