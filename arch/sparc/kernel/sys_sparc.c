multiline_comment|/* $Id: sys_sparc.c,v 1.70 2001/04/14 01:12:02 davem Exp $&n; * linux/arch/sparc/kernel/sys_sparc.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/sparc&n; * platform.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
multiline_comment|/* #define DEBUG_UNIMP_SYSCALL */
multiline_comment|/* XXX Make this per-binary type, this way we can detect the type of&n; * XXX a binary.  Every Sparc executable calls this very early on.&n; */
DECL|function|sys_getpagesize
id|asmlinkage
r_int
r_int
id|sys_getpagesize
c_func
(paren
r_void
)paren
(brace
r_return
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Possibly older binaries want 8192 on sun4&squot;s? */
)brace
DECL|macro|COLOUR_ALIGN
mdefine_line|#define COLOUR_ALIGN(addr)      (((addr)+SHMLBA-1)&amp;~(SHMLBA-1))
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
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
(brace
multiline_comment|/* We do not accept a shared mapping if it would violate&n;&t;&t; * cache aliasing constraints.&n;&t;&t; */
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
(paren
id|SHMLBA
op_minus
l_int|1
)paren
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
multiline_comment|/* See asm-sparc/uaccess.h */
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
op_logical_and
id|len
OG
l_int|0x20000000
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
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
id|ARCH_SUN4C_SUN4
op_logical_and
id|addr
OL
l_int|0xe0000000
op_logical_and
l_int|0x20000000
op_minus
id|len
OL
id|addr
)paren
(brace
id|addr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|vmm
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|PAGE_SIZE
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
id|flags
op_amp
id|MAP_SHARED
)paren
id|addr
op_assign
id|COLOUR_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
)brace
DECL|function|sparc_brk
id|asmlinkage
r_int
r_int
id|sparc_brk
c_func
(paren
r_int
r_int
id|brk
)paren
(brace
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
)paren
(brace
r_if
c_cond
(paren
(paren
id|brk
op_amp
l_int|0xe0000000
)paren
op_ne
(paren
id|current-&gt;mm-&gt;brk
op_amp
l_int|0xe0000000
)paren
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
)brace
r_return
id|sys_brk
c_func
(paren
id|brk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way unix traditionally does this, though.&n; */
DECL|function|sparc_pipe
id|asmlinkage
r_int
id|sparc_pipe
c_func
(paren
r_struct
id|pt_regs
op_star
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
r_goto
id|out
suffix:semicolon
id|regs-&gt;u_regs
(braket
id|UREG_I1
)braket
op_assign
id|fd
(braket
l_int|1
)braket
suffix:semicolon
id|error
op_assign
id|fd
(braket
l_int|0
)braket
suffix:semicolon
id|out
suffix:colon
r_return
id|error
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
id|__user
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
id|err
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
r_if
c_cond
(paren
id|call
op_le
id|SEMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SEMOP
suffix:colon
id|err
op_assign
id|sys_semtimedop
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
r_goto
id|out
suffix:semicolon
r_case
id|SEMTIMEDOP
suffix:colon
id|err
op_assign
id|sys_semtimedop
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
r_goto
id|out
suffix:semicolon
r_case
id|SEMGET
suffix:colon
id|err
op_assign
id|sys_semget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SEMCTL
suffix:colon
(brace
r_union
id|semun
id|fourth
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
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
id|__user
op_star
id|__user
op_star
)paren
id|ptr
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
)brace
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|MSGCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|MSGSND
suffix:colon
id|err
op_assign
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
r_goto
id|out
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
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_goto
id|out
suffix:semicolon
id|err
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
r_goto
id|out
suffix:semicolon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
r_default
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
)brace
r_case
id|MSGGET
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_case
id|MSGCTL
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|call
op_le
id|SHMCTL
)paren
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|SHMAT
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
r_default
suffix:colon
(brace
)brace
(brace
id|ulong
id|raddr
suffix:semicolon
id|err
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
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
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
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
multiline_comment|/* iBCS2 emulator entry point */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_case
id|SHMDT
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_case
id|SHMGET
suffix:colon
id|err
op_assign
id|sys_shmget
(paren
id|first
comma
id|second
comma
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SHMCTL
suffix:colon
id|err
op_assign
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
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
id|err
op_assign
op_minus
id|ENOSYS
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* Linux version of mmap */
DECL|function|do_mmap2
r_static
r_int
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
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|retval
op_assign
op_minus
id|EBADF
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
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
op_logical_and
(paren
id|len
OG
l_int|0x20000000
op_logical_or
(paren
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
op_logical_and
id|addr
template_param
l_int|0x20000000
)paren
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
multiline_comment|/* See asm-sparc/uaccess.h */
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
op_logical_or
id|addr
op_plus
id|len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
r_goto
id|out_putf
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
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
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
id|out_putf
suffix:colon
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
id|retval
suffix:semicolon
)brace
DECL|function|sys_mmap2
id|asmlinkage
r_int
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
multiline_comment|/* Make sure the shift for mmap2 is constant (12), no matter what PAGE_SIZE&n;&t;   we have. */
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
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
)paren
suffix:semicolon
)brace
DECL|function|sys_mmap
id|asmlinkage
r_int
r_int
id|sys_mmap
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
id|off
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
id|off
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|sparc_remap_file_pages
r_int
id|sparc_remap_file_pages
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
comma
r_int
r_int
id|prot
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
multiline_comment|/* This works on an existing mmap so we don&squot;t need to validate&n;&t; * the range as that was done at the original mmap call.&n;&t; */
r_return
id|sys_remap_file_pages
c_func
(paren
id|start
comma
id|size
comma
id|prot
comma
(paren
id|pgoff
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|do_mremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
suffix:semicolon
DECL|function|sparc_mremap
id|asmlinkage
r_int
r_int
id|sparc_mremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|old_len
comma
r_int
r_int
id|new_len
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|new_addr
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
)paren
(brace
r_if
c_cond
(paren
id|old_len
OG
l_int|0x20000000
op_logical_or
id|new_len
OG
l_int|0x20000000
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr
template_param
l_int|0x20000000
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
op_logical_or
id|new_len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
r_goto
id|out
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MREMAP_FIXED
)paren
(brace
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
op_logical_and
id|new_addr
template_param
l_int|0x20000000
)paren
r_goto
id|out_sem
suffix:semicolon
r_if
c_cond
(paren
id|new_addr
op_plus
id|new_len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
r_goto
id|out_sem
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|ARCH_SUN4C_SUN4
op_logical_and
id|addr
template_param
l_int|0x20000000
)paren
op_logical_or
id|addr
op_plus
id|new_len
OG
id|TASK_SIZE
op_minus
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|map_flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MREMAP_MAYMOVE
)paren
)paren
r_goto
id|out_sem
suffix:semicolon
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
r_if
c_cond
(paren
id|vma
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
id|map_flags
op_or_assign
id|MAP_SHARED
suffix:semicolon
id|file
op_assign
id|vma-&gt;vm_file
suffix:semicolon
)brace
id|new_addr
op_assign
id|get_unmapped_area
c_func
(paren
id|file
comma
id|addr
comma
id|new_len
comma
id|vma
ques
c_cond
id|vma-&gt;vm_pgoff
suffix:colon
l_int|0
comma
id|map_flags
)paren
suffix:semicolon
id|ret
op_assign
id|new_addr
suffix:semicolon
r_if
c_cond
(paren
id|new_addr
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out_sem
suffix:semicolon
id|flags
op_or_assign
id|MREMAP_FIXED
suffix:semicolon
)brace
id|ret
op_assign
id|do_mremap
c_func
(paren
id|addr
comma
id|old_len
comma
id|new_len
comma
id|flags
comma
id|new_addr
)paren
suffix:semicolon
id|out_sem
suffix:colon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* we come to here via sys_nis_syscall so it can setup the regs argument */
id|asmlinkage
r_int
r_int
DECL|function|c_sys_nis_syscall
id|c_sys_nis_syscall
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_increment
OG
l_int|5
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|printk
(paren
l_string|&quot;%s[%d]: Unimplemented SPARC system call %d&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_UNIMP_SYSCALL&t;
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
multiline_comment|/* #define DEBUG_SPARC_BREAKPOINT */
id|asmlinkage
r_void
DECL|function|sparc_breakpoint
id|sparc_breakpoint
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Entering kernel PC=%x, nPC=%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|regs-&gt;pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Returning to space: PC=%x nPC=%x&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;npc
)paren
suffix:semicolon
macro_line|#endif
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sparc_sigaction
id|sparc_sigaction
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
id|__user
op_star
id|act
comma
r_struct
id|old_sigaction
id|__user
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
id|sig
OL
l_int|0
)paren
(brace
id|current-&gt;thread.new_signal
op_assign
l_int|1
suffix:semicolon
id|sig
op_assign
op_minus
id|sig
suffix:semicolon
)brace
r_if
c_cond
(paren
id|act
)paren
(brace
r_int
r_int
id|mask
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
id|new_ka.ka_restorer
op_assign
l_int|NULL
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
multiline_comment|/* In the clone() case we could copy half consistent&n;&t;&t; * state to the user, however this could sleep and&n;&t;&t; * deadlock us if we held the signal lock on SMP.  So for&n;&t;&t; * now I take the easy way out and do no locking.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
id|asmlinkage
r_int
DECL|function|sys_rt_sigaction
id|sys_rt_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|sigaction
id|__user
op_star
id|act
comma
r_struct
id|sigaction
id|__user
op_star
id|oact
comma
r_void
id|__user
op_star
id|restorer
comma
r_int
id|sigsetsize
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
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s.  */
r_if
c_cond
(paren
id|sigsetsize
op_ne
r_sizeof
(paren
id|sigset_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* All tasks which use RT signals (effectively) use&n;&t; * new style signals.&n;&t; */
id|current-&gt;thread.new_signal
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|new_ka.ka_restorer
op_assign
id|restorer
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|new_ka.sa
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
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
id|copy_to_user
c_func
(paren
id|oact
comma
op_amp
id|old_ka.sa
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_getdomainname
id|asmlinkage
r_int
id|sys_getdomainname
c_func
(paren
r_char
id|__user
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|nlen
suffix:semicolon
r_int
id|err
op_assign
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
id|nlen
op_assign
id|strlen
c_func
(paren
id|system_utsname.domainname
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nlen
OL
id|len
)paren
id|len
op_assign
id|nlen
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|__NEW_UTS_LEN
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|name
comma
id|system_utsname.domainname
comma
id|len
)paren
)paren
r_goto
id|done
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|done
suffix:colon
id|up_read
c_func
(paren
op_amp
id|uts_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
