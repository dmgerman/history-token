multiline_comment|/* sys_frv.c: FRV arch-specific syscall wrappers&n; *&n; * Copyright (C) 2003-5 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; * - Derived from arch/m68k/kernel/sys_m68k.c&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
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
DECL|function|sys_mmap2
id|asmlinkage
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
multiline_comment|/* As with sparc32, make sure the shift for mmap2 is constant&n;&t;   (12), no matter what PAGE_SIZE we have.... */
multiline_comment|/* But unlike sparc32, don&squot;t just silently break if we&squot;re&n;&t;   trying to map something we can&squot;t */
r_if
c_cond
(paren
id|pgoff
op_amp
(paren
(paren
l_int|1
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pgoff
op_rshift_assign
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
suffix:semicolon
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
macro_line|#if 0 /* DAVIDM - do we want this */
r_struct
id|mmap_arg_struct64
(brace
id|__u32
id|addr
suffix:semicolon
id|__u32
id|len
suffix:semicolon
id|__u32
id|prot
suffix:semicolon
id|__u32
id|flags
suffix:semicolon
id|__u64
id|offset
suffix:semicolon
multiline_comment|/* 64 bits */
id|__u32
id|fd
suffix:semicolon
)brace
suffix:semicolon
id|asmlinkage
r_int
id|sys_mmap64
c_func
(paren
r_struct
id|mmap_arg_struct64
op_star
id|arg
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|mmap_arg_struct64
id|a
suffix:semicolon
r_int
r_int
id|pgoff
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
r_if
c_cond
(paren
(paren
r_int
)paren
id|a.offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pgoff
op_assign
id|a.offset
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a.offset
op_rshift
id|PAGE_SHIFT
)paren
op_ne
id|pgoff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a.flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
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
id|a.fd
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
id|a.flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
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
id|a.addr
comma
id|a.len
comma
id|a.prot
comma
id|a.flags
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
macro_line|#endif
multiline_comment|/*&n; * sys_ipc() is the de-multiplexer for the SysV IPC calls..&n; *&n; * This is really horribly ugly.&n; */
DECL|function|sys_ipc
id|asmlinkage
r_int
id|sys_ipc
c_func
(paren
r_int
r_int
id|call
comma
r_int
r_int
id|first
comma
r_int
r_int
id|second
comma
r_int
r_int
id|third
comma
r_void
id|__user
op_star
id|ptr
comma
r_int
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
id|sys_semtimedop
c_func
(paren
id|first
comma
(paren
r_struct
id|sembuf
id|__user
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
c_func
(paren
id|first
comma
(paren
r_struct
id|sembuf
id|__user
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
id|__user
op_star
)paren
id|fifth
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
id|__user
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
id|__user
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
id|__user
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
r_return
id|sys_msgrcv
(paren
id|first
comma
(paren
r_struct
id|msgbuf
id|__user
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
id|__user
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
id|do_shmat
(paren
id|first
comma
(paren
r_char
id|__user
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
id|__user
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
multiline_comment|/* The &quot;(ulong *) third&quot; is valid _only_ because of the kernel segment thing */
r_return
id|do_shmat
(paren
id|first
comma
(paren
r_char
id|__user
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
id|__user
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
id|__user
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
)brace
eof
