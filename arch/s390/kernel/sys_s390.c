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
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#ifdef CONFIG_ARCH_S390X
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#endif /* CONFIG_ARCH_S390X */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|macro|__SYS_RETTYPE
mdefine_line|#define __SYS_RETTYPE int
macro_line|#else
DECL|macro|__SYS_RETTYPE
mdefine_line|#define __SYS_RETTYPE long
macro_line|#endif /* CONFIG_ARCH_S390X */
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way Unix traditionally does this, though.&n; */
DECL|function|sys_pipe
id|asmlinkage
id|__SYS_RETTYPE
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
id|__SYS_RETTYPE
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
id|__SYS_RETTYPE
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
id|__SYS_RETTYPE
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
macro_line|#ifndef CONFIG_ARCH_S390X
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
macro_line|#else /* CONFIG_ARCH_S390X */
r_int
r_int
DECL|function|arch_get_unmapped_area
id|arch_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
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
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_31BIT
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
id|addr
op_assign
l_int|0x40000000
suffix:semicolon
id|end
op_assign
l_int|0x80000000
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
id|addr
op_assign
id|TASK_SIZE
op_div
l_int|2
suffix:semicolon
id|end
op_assign
id|TASK_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|end
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vma || addr &lt; vma-&gt;vm_end). */
r_if
c_cond
(paren
id|end
op_minus
id|len
OL
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
id|vma-&gt;vm_end
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
id|__SYS_RETTYPE
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
id|sys_semtimedop
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
comma
l_int|NULL
)paren
suffix:semicolon
r_case
id|SEMTIMEDOP
suffix:colon
r_return
id|sys_semtimedop
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
comma
(paren
r_const
r_struct
id|timespec
op_star
)paren
id|third
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
id|do_shmat
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
id|ENOSYS
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
macro_line|#ifndef CONFIG_ARCH_S390X
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
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|function|s390x_newuname
id|asmlinkage
r_int
id|s390x_newuname
c_func
(paren
r_struct
id|new_utsname
op_star
id|name
)paren
(brace
r_int
id|ret
op_assign
id|sys_newuname
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;personality
op_eq
id|PER_LINUX32
op_logical_and
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|copy_to_user
c_func
(paren
id|name-&gt;machine
comma
l_string|&quot;s390&bslash;0&bslash;0&bslash;0&bslash;0&quot;
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|s390x_personality
id|asmlinkage
r_int
id|s390x_personality
c_func
(paren
r_int
r_int
id|personality
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;personality
op_eq
id|PER_LINUX32
op_logical_and
id|personality
op_eq
id|PER_LINUX
)paren
id|personality
op_assign
id|PER_LINUX32
suffix:semicolon
id|ret
op_assign
id|sys_personality
c_func
(paren
id|personality
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|PER_LINUX32
)paren
id|ret
op_assign
id|PER_LINUX
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ARCH_S390X */
multiline_comment|/*&n; * Wrapper function for sys_fadvise64/fadvise64_64&n; */
macro_line|#ifndef CONFIG_ARCH_S390X
id|asmlinkage
r_int
DECL|function|s390_fadvise64
id|s390_fadvise64
c_func
(paren
r_int
id|fd
comma
id|u32
id|offset_high
comma
id|u32
id|offset_low
comma
r_int
id|len
comma
r_int
id|advice
)paren
(brace
r_return
id|sys_fadvise64
c_func
(paren
id|fd
comma
(paren
id|u64
)paren
id|offset_high
op_lshift
l_int|32
op_or
id|offset_low
comma
id|len
comma
id|advice
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|struct|fadvise64_64_args
r_struct
id|fadvise64_64_args
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|advice
r_int
id|advice
suffix:semicolon
)brace
suffix:semicolon
id|asmlinkage
r_int
DECL|function|s390_fadvise64_64
id|s390_fadvise64_64
c_func
(paren
r_struct
id|fadvise64_64_args
op_star
id|args
)paren
(brace
r_struct
id|fadvise64_64_args
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
id|args
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
r_return
id|sys_fadvise64_64
c_func
(paren
id|a.fd
comma
id|a.offset
comma
id|a.len
comma
id|a.advice
)paren
suffix:semicolon
)brace
eof
