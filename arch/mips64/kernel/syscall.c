multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 2000, 2001 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/sysmips.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
id|asmlinkage
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|sys_pipe
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
id|abi64_no_regargs
comma
r_struct
id|pt_regs
id|regs
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
comma
id|res
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
id|error
)paren
(brace
id|res
op_assign
id|error
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|regs.regs
(braket
l_int|3
)braket
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
id|res
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
id|out
suffix:colon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|shm_align_mask
r_int
r_int
id|shm_align_mask
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Sane caches */
DECL|macro|COLOUR_ALIGN
mdefine_line|#define COLOUR_ALIGN(addr,pgoff)&t;&t;&t;&t;&bslash;&n;&t;((((addr) + shm_align_mask) &amp; ~shm_align_mask) +&t;&bslash;&n;&t; (((pgoff) &lt;&lt; PAGE_SHIFT) &amp; shm_align_mask))
DECL|function|arch_get_unmapped_area
r_int
r_int
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
id|vmm
suffix:semicolon
r_int
id|do_color_align
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
(brace
multiline_comment|/*&n;&t;&t; * We do not accept a shared mapping if it would violate&n;&t;&t; * cache aliasing constraints.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
op_logical_and
(paren
id|addr
op_amp
id|shm_align_mask
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|do_color_align
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|filp
op_logical_or
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
)paren
id|do_color_align
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
r_if
c_cond
(paren
id|do_color_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
r_else
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
id|vmm
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
op_ge
id|addr
op_logical_and
(paren
op_logical_neg
id|vmm
op_logical_or
id|addr
op_plus
id|len
op_le
id|vmm-&gt;vm_start
)paren
)paren
r_return
id|addr
suffix:semicolon
)brace
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_if
c_cond
(paren
id|do_color_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
r_else
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
id|vmm
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
id|vmm
op_assign
id|vmm-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vmm || addr &lt; vmm-&gt;vm_end). */
r_if
c_cond
(paren
id|TASK_SIZE
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
id|vmm
op_logical_or
id|addr
op_plus
id|len
op_le
id|vmm-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
id|vmm-&gt;vm_end
suffix:semicolon
r_if
c_cond
(paren
id|do_color_align
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
comma
id|pgoff
)paren
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
r_int
DECL|function|sys_mmap
id|sys_mmap
c_func
(paren
r_int
r_int
id|addr
comma
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
id|off_t
id|offset
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|error
suffix:semicolon
id|error
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
)brace
id|flags
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
id|do_mmap
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
id|offset
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
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
id|abi64_no_regargs
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
id|save_static
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|29
)braket
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
id|abi64_no_regargs
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
r_int
id|clone_flags
suffix:semicolon
r_int
r_int
id|newsp
suffix:semicolon
r_int
op_star
id|parent_tidptr
comma
op_star
id|child_tidptr
suffix:semicolon
id|save_static
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
id|clone_flags
op_assign
id|regs.regs
(braket
l_int|4
)braket
suffix:semicolon
id|newsp
op_assign
id|regs.regs
(braket
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
id|parent_tidptr
op_assign
(paren
r_int
op_star
)paren
id|regs.regs
(braket
l_int|6
)braket
suffix:semicolon
id|child_tidptr
op_assign
(paren
r_int
op_star
)paren
id|regs.regs
(braket
l_int|7
)braket
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
comma
id|parent_tidptr
comma
id|child_tidptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
id|abi64_no_regargs
comma
r_struct
id|pt_regs
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
(paren
r_int
)paren
id|regs.regs
(braket
l_int|4
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
(paren
r_int
)paren
id|regs.regs
(braket
l_int|5
)braket
comma
(paren
r_char
op_star
op_star
)paren
(paren
r_int
)paren
id|regs.regs
(braket
l_int|6
)braket
comma
op_amp
id|regs
)paren
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
multiline_comment|/*&n; * Do the indirect syscall syscall.&n; *&n; * XXX This is borken.&n; */
DECL|function|sys_syscall
id|asmlinkage
r_int
id|sys_syscall
c_func
(paren
id|abi64_no_regargs
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_sysmips
id|asmlinkage
r_int
id|sys_sysmips
c_func
(paren
r_int
id|cmd
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
)paren
(brace
r_int
id|tmp
comma
id|len
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SETNAME
suffix:colon
(brace
r_char
id|nodename
(braket
id|__NEW_UTS_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|name
op_assign
(paren
r_char
op_star
)paren
id|arg1
suffix:semicolon
id|len
op_assign
id|strncpy_from_user
c_func
(paren
id|nodename
comma
id|name
comma
id|__NEW_UTS_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|system_utsname.nodename
comma
id|nodename
comma
id|len
)paren
suffix:semicolon
id|nodename
(braket
id|__NEW_UTS_LEN
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|strlcpy
c_func
(paren
id|system_utsname.nodename
comma
id|nodename
comma
r_sizeof
(paren
id|system_utsname.nodename
)paren
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|MIPS_ATOMIC_SET
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;How did I get here?&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|MIPS_FIXADE
suffix:colon
id|tmp
op_assign
id|current-&gt;thread.mflags
op_amp
op_complement
l_int|3
suffix:semicolon
id|current-&gt;thread.mflags
op_assign
id|tmp
op_or
(paren
id|arg1
op_amp
l_int|3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|FLUSH_CACHE
suffix:colon
id|__flush_cache_all
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|MIPS_RDNVRAM
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
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
id|ENOSYS
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * No implemented yet ...&n; */
DECL|function|sys_cachectl
id|asmlinkage
r_int
id|sys_cachectl
c_func
(paren
r_char
op_star
id|addr
comma
r_int
id|nbytes
comma
r_int
id|op
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/*&n; * If we ever come here the user sp is bad.  Zap the process right away.&n; * Due to the bad stack signaling wouldn&squot;t work.&n; */
DECL|function|bad_stack
id|asmlinkage
r_void
id|bad_stack
c_func
(paren
r_void
)paren
(brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
eof
