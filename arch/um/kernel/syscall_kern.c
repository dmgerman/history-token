multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/file.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/utsname.h&quot;
macro_line|#include &quot;linux/msg.h&quot;
macro_line|#include &quot;linux/shm.h&quot;
macro_line|#include &quot;linux/sys.h&quot;
macro_line|#include &quot;linux/unistd.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/utime.h&quot;
macro_line|#include &quot;asm/mman.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/ipc.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;sysdep/syscalls.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
multiline_comment|/*  Unlocked, I don&squot;t care if this is a bit off */
DECL|variable|nsyscalls
r_int
id|nsyscalls
op_assign
l_int|0
suffix:semicolon
DECL|function|um_mount
r_int
id|um_mount
c_func
(paren
r_char
op_star
id|dev_name
comma
r_char
op_star
id|dir_name
comma
r_char
op_star
id|type
comma
r_int
r_int
id|new_flags
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
l_int|NULL
)paren
(brace
id|type
op_assign
l_string|&quot;&quot;
suffix:semicolon
)brace
r_return
id|sys_mount
c_func
(paren
id|dev_name
comma
id|dir_name
comma
id|type
comma
id|new_flags
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|sys_fork
r_int
id|sys_fork
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|1
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|SIGCHLD
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|0
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_clone
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|newsp
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|1
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|0
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_vfork
r_int
id|sys_vfork
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|1
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|0
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
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
DECL|function|sys_mmap2
r_int
id|sys_mmap2
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
r_return
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|pgoff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform the select(nd, in, out, ex, tv) and mmap() system&n; * calls. Linux/i386 didn&squot;t use to be able to handle more than&n; * 4 system call parameters, so these system calls used a memory&n; * block for parameter passing..&n; */
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
DECL|function|old_mmap
r_int
id|old_mmap
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
id|offset
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
DECL|function|sys_pipe
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
DECL|function|sys_sigaction
r_int
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
op_star
id|act
comma
r_struct
id|old_sigaction
op_star
id|oact
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|old_sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_restorer
comma
op_amp
id|act-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask
)paren
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|new_ka.sa.sa_mask
comma
id|mask
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oact
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_restorer
comma
op_amp
id|oact-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
op_amp
id|oact-&gt;sa_mask
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
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
comma
r_int
id|fifth
)paren
(brace
r_int
id|version
comma
id|ret
suffix:semicolon
id|version
op_assign
id|call
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* hack for backward compatibility */
id|call
op_and_assign
l_int|0xffff
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
r_case
id|MSGRCV
suffix:colon
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
l_int|0
suffix:colon
(brace
r_struct
id|ipc_kludge
id|tmp
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
id|copy_from_user
c_func
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
id|tmp
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
)brace
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;msgrcv with version != 0&quot;
)paren
suffix:semicolon
r_return
id|sys_msgrcv
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
id|fifth
comma
id|third
)paren
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|version
)paren
(brace
r_default
suffix:colon
(brace
)brace
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
)brace
r_case
l_int|1
suffix:colon
multiline_comment|/* iBCS2 emulator entry point */
r_if
c_cond
(paren
op_logical_neg
id|segment_eq
c_func
(paren
id|get_fs
c_func
(paren
)paren
comma
id|get_ds
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
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
(paren
id|ulong
op_star
)paren
id|third
)paren
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
)brace
DECL|function|sys_uname
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
DECL|function|sys_sigaltstack
r_int
id|sys_sigaltstack
c_func
(paren
r_const
id|stack_t
op_star
id|uss
comma
id|stack_t
op_star
id|uoss
)paren
(brace
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|PT_REGS_SP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
)paren
suffix:semicolon
)brace
DECL|function|execute_syscall
r_int
id|execute_syscall
c_func
(paren
r_void
op_star
id|r
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|execute_syscall_tt
comma
id|execute_syscall_skas
comma
id|r
)paren
suffix:semicolon
)brace
DECL|variable|syscall_lock
id|spinlock_t
id|syscall_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|syscall_index
r_static
r_int
id|syscall_index
op_assign
l_int|0
suffix:semicolon
DECL|function|next_syscall_index
r_int
id|next_syscall_index
c_func
(paren
r_int
id|limit
)paren
(brace
r_int
id|ret
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|syscall_lock
)paren
suffix:semicolon
id|ret
op_assign
id|syscall_index
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|syscall_index
op_eq
id|limit
)paren
(brace
id|syscall_index
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|syscall_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
