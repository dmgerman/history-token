multiline_comment|/* $Id: sys_sparc.c,v 1.57 2002/02/09 19:49:30 davem Exp $&n; * linux/arch/sparc64/kernel/sys_sparc.c&n; *&n; * This file contains various random system calls that&n; * have a non-standard calling sequence on the Linux/sparc&n; * platform.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ipc.h&gt;
macro_line|#include &lt;asm/utrap.h&gt;
macro_line|#include &lt;asm/perfctr.h&gt;
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
)brace
DECL|macro|COLOUR_ALIGN
mdefine_line|#define COLOUR_ALIGN(addr,pgoff)&t;&t;&bslash;&n;&t;((((addr)+SHMLBA-1)&amp;~(SHMLBA-1)) +&t;&bslash;&n;&t; (((pgoff)&lt;&lt;PAGE_SHIFT) &amp; (SHMLBA-1)))
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
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|task_size
op_assign
id|TASK_SIZE
suffix:semicolon
r_int
r_int
id|start_addr
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
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
id|task_size
op_assign
l_int|0xf0000000UL
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|task_size
op_logical_or
id|len
OG
op_minus
id|PAGE_OFFSET
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
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task_size
op_minus
id|len
op_ge
id|addr
op_logical_and
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
)paren
r_return
id|addr
suffix:semicolon
)brace
id|start_addr
op_assign
id|addr
op_assign
id|mm-&gt;free_area_cache
suffix:semicolon
id|task_size
op_sub_assign
id|len
suffix:semicolon
id|full_search
suffix:colon
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
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
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
id|addr
OL
id|PAGE_OFFSET
op_logical_and
op_minus
id|PAGE_OFFSET
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
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task_size
OL
id|addr
)paren
(brace
r_if
c_cond
(paren
id|start_addr
op_ne
id|TASK_UNMAPPED_BASE
)paren
(brace
id|start_addr
op_assign
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_goto
id|full_search
suffix:semicolon
)brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
(brace
multiline_comment|/*&n;&t;&t;&t; * Remember the place where we stopped the search:&n;&t;&t;&t; */
id|mm-&gt;free_area_cache
op_assign
id|addr
op_plus
id|len
suffix:semicolon
r_return
id|addr
suffix:semicolon
)brace
id|addr
op_assign
id|vma-&gt;vm_end
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
multiline_comment|/* Try to align mapping such that we align it as much as possible. */
DECL|function|get_fb_unmapped_area
r_int
r_int
id|get_fb_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|orig_addr
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
r_int
r_int
id|align_goal
comma
id|addr
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
(brace
multiline_comment|/* Ok, don&squot;t mess with it. */
r_return
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|addr
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
)brace
id|flags
op_and_assign
op_complement
id|MAP_SHARED
suffix:semicolon
id|align_goal
op_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
(paren
l_int|4UL
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
id|align_goal
op_assign
(paren
l_int|4UL
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
op_ge
(paren
l_int|512UL
op_star
l_int|1024
)paren
)paren
id|align_goal
op_assign
(paren
l_int|512UL
op_star
l_int|1024
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|len
op_ge
(paren
l_int|64UL
op_star
l_int|1024
)paren
)paren
id|align_goal
op_assign
(paren
l_int|64UL
op_star
l_int|1024
)paren
suffix:semicolon
r_do
(brace
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|orig_addr
comma
id|len
op_plus
(paren
id|align_goal
op_minus
id|PAGE_SIZE
)paren
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
(brace
id|addr
op_assign
(paren
id|addr
op_plus
(paren
id|align_goal
op_minus
l_int|1UL
)paren
)paren
op_amp
op_complement
(paren
id|align_goal
op_minus
l_int|1UL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|align_goal
op_eq
(paren
l_int|4UL
op_star
l_int|1024
op_star
l_int|1024
)paren
)paren
id|align_goal
op_assign
(paren
l_int|512UL
op_star
l_int|1024
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|align_goal
op_eq
(paren
l_int|512UL
op_star
l_int|1024
)paren
)paren
id|align_goal
op_assign
(paren
l_int|64UL
op_star
l_int|1024
)paren
suffix:semicolon
r_else
id|align_goal
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
op_logical_and
id|align_goal
OG
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Mapping is smaller than 64K or larger areas could not&n;&t; * be obtained.&n;&t; */
r_if
c_cond
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
id|addr
op_assign
id|get_unmapped_area
c_func
(paren
l_int|NULL
comma
id|orig_addr
comma
id|len
comma
id|pgoff
comma
id|flags
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
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
multiline_comment|/* People could try to be nasty and use ta 0x6d in 32bit programs */
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
op_logical_and
id|brk
op_ge
l_int|0xf0000000UL
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;mm-&gt;brk
op_amp
id|PAGE_OFFSET
)paren
op_ne
(paren
id|brk
op_amp
id|PAGE_OFFSET
)paren
)paren
r_return
id|current-&gt;mm-&gt;brk
suffix:semicolon
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
r_int
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
id|err
suffix:semicolon
multiline_comment|/* No need for backward compatibility. We can start fresh... */
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
(paren
r_int
)paren
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
op_star
op_star
)paren
id|ptr
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|sys_semctl
(paren
id|first
comma
id|second
op_or
id|IPC_64
comma
(paren
r_int
)paren
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
op_star
)paren
id|ptr
comma
id|second
comma
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|MSGRCV
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
op_star
)paren
id|ptr
comma
id|second
comma
id|fifth
comma
(paren
r_int
)paren
id|third
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
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
op_or
id|IPC_64
comma
(paren
r_struct
id|msqid_ds
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
op_logical_neg
id|err
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
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
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
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
(paren
r_int
)paren
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
op_or
id|IPC_64
comma
(paren
r_struct
id|shmid_ds
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
DECL|function|sparc64_newuname
id|asmlinkage
r_int
id|sparc64_newuname
c_func
(paren
r_struct
id|new_utsname
id|__user
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
l_string|&quot;sparc&bslash;0&bslash;0&quot;
comma
l_int|8
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sparc64_personality
id|asmlinkage
r_int
id|sparc64_personality
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
multiline_comment|/* Linux version of mmap */
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
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
OG
l_int|0xf0000000UL
op_logical_or
(paren
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
op_logical_and
id|addr
OG
l_int|0xf0000000UL
op_minus
id|len
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|len
OG
op_minus
id|PAGE_OFFSET
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
op_minus
id|PAGE_OFFSET
)paren
)paren
r_goto
id|out_putf
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
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
id|off
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
DECL|function|sys64_munmap
id|asmlinkage
r_int
id|sys64_munmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
op_minus
id|PAGE_OFFSET
op_logical_or
(paren
id|addr
template_param
op_minus
id|PAGE_OFFSET
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|ret
op_assign
id|do_munmap
c_func
(paren
id|current-&gt;mm
comma
id|addr
comma
id|len
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|ret
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
DECL|function|sys64_mremap
id|asmlinkage
r_int
r_int
id|sys64_mremap
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
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|old_len
OG
op_minus
id|PAGE_OFFSET
op_logical_or
id|new_len
OG
op_minus
id|PAGE_OFFSET
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|addr
template_param
op_minus
id|PAGE_OFFSET
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
id|new_addr
template_param
op_minus
id|PAGE_OFFSET
)paren
r_goto
id|out_sem
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|addr
template_param
op_minus
id|PAGE_OFFSET
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
multiline_comment|/* MREMAP_FIXED checked above. */
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
suffix:semicolon
multiline_comment|/* Don&squot;t make the system unusable, if someone goes stuck */
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
l_string|&quot;Unimplemented SPARC system call %ld&bslash;n&quot;
comma
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
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|regs-&gt;tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|regs-&gt;tnpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_SPARC_BREAKPOINT
id|printk
(paren
l_string|&quot;TRAP: Entering kernel PC=%lx, nPC=%lx&bslash;n&quot;
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
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
op_star
)paren
id|regs-&gt;tpc
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
l_string|&quot;TRAP: Returning to space: PC=%lx nPC=%lx&bslash;n&quot;
comma
id|regs-&gt;tpc
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_void
id|check_pending
c_func
(paren
r_int
id|signum
)paren
suffix:semicolon
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
DECL|function|solaris_syscall
id|asmlinkage
r_int
id|solaris_syscall
c_func
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
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|regs-&gt;tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|regs-&gt;tnpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|count
op_le
l_int|5
)paren
(brace
id|printk
(paren
l_string|&quot;For Solaris binary emulation you need solaris module loaded&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
)brace
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SUNOS_EMUL
DECL|function|sunos_syscall
id|asmlinkage
r_int
id|sunos_syscall
c_func
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
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|regs-&gt;tpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|regs-&gt;tnpc
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|count
op_le
l_int|20
)paren
id|printk
(paren
l_string|&quot;SunOS binary emulation not compiled in&bslash;n&quot;
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_utrap_install
id|asmlinkage
r_int
id|sys_utrap_install
c_func
(paren
id|utrap_entry_t
id|type
comma
id|utrap_handler_t
id|new_p
comma
id|utrap_handler_t
id|new_d
comma
id|utrap_handler_t
id|__user
op_star
id|old_p
comma
id|utrap_handler_t
id|__user
op_star
id|old_d
)paren
(brace
r_if
c_cond
(paren
id|type
template_param
id|UT_TRAP_INSTRUCTION_31
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|new_p
op_eq
(paren
id|utrap_handler_t
)paren
(paren
r_int
)paren
id|UTH_NOCHANGE
)paren
(brace
r_if
c_cond
(paren
id|old_p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_int|NULL
comma
id|old_p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
id|utrap_handler_t
)paren
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
id|type
)braket
)paren
comma
id|old_p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|old_d
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_int|NULL
comma
id|old_d
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
)paren
(brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
op_assign
id|kmalloc
c_func
(paren
(paren
id|UT_TRAP_INSTRUCTION_31
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
op_plus
l_int|1
comma
l_int|0
comma
id|UT_TRAP_INSTRUCTION_31
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|utrap_handler_t
)paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
id|type
)braket
op_ne
id|new_p
op_logical_and
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
r_int
op_star
id|p
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
op_assign
id|kmalloc
c_func
(paren
(paren
id|UT_TRAP_INSTRUCTION_31
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
)paren
(brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
op_assign
id|p
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|p
(braket
l_int|0
)braket
op_decrement
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
op_plus
l_int|1
comma
id|p
op_plus
l_int|1
comma
id|UT_TRAP_INSTRUCTION_31
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|old_p
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
id|utrap_handler_t
)paren
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
id|type
)braket
)paren
comma
id|old_p
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|old_d
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_int|NULL
comma
id|old_d
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|utraps
(braket
id|type
)braket
op_assign
(paren
r_int
)paren
id|new_p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sparc_memory_ordering
r_int
id|sparc_memory_ordering
c_func
(paren
r_int
r_int
id|model
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|model
op_ge
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|regs-&gt;tstate
op_assign
(paren
id|regs-&gt;tstate
op_amp
op_complement
id|TSTATE_MM
)paren
op_or
(paren
id|model
op_lshift
l_int|14
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/* Invoked by rtrap code to update performance counters in&n; * user space.&n; */
id|asmlinkage
r_void
DECL|function|update_perfctrs
id|update_perfctrs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pic
comma
id|tmp
suffix:semicolon
id|read_pic
c_func
(paren
id|pic
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd0
op_add_assign
(paren
r_int
r_int
)paren
id|pic
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|tmp
comma
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd0
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd1
op_add_assign
(paren
id|pic
op_rshift
l_int|32
)paren
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|tmp
comma
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd1
)paren
suffix:semicolon
id|reset_pic
c_func
(paren
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_perfctr
id|sys_perfctr
c_func
(paren
r_int
id|opcode
comma
r_int
r_int
id|arg0
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|PERFCTR_ON
suffix:colon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcr_reg
op_assign
id|arg2
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd0
op_assign
(paren
id|u64
op_star
)paren
id|arg0
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd1
op_assign
(paren
id|u64
op_star
)paren
id|arg1
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd0
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd1
op_assign
l_int|0
suffix:semicolon
id|write_pcr
c_func
(paren
id|arg2
)paren
suffix:semicolon
id|reset_pic
c_func
(paren
)paren
suffix:semicolon
id|set_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PERFCTR_OFF
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
)paren
(brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd0
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd1
op_assign
l_int|NULL
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcr_reg
op_assign
l_int|0
suffix:semicolon
id|write_pcr
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PERFCTR_READ
suffix:colon
(brace
r_int
r_int
id|pic
comma
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|read_pic
c_func
(paren
id|pic
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd0
op_add_assign
(paren
r_int
r_int
)paren
id|pic
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tmp
comma
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd0
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd1
op_add_assign
(paren
id|pic
op_rshift
l_int|32
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|tmp
comma
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|user_cntd1
)paren
suffix:semicolon
id|reset_pic
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PERFCTR_CLRPIC
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd0
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd1
op_assign
l_int|0
suffix:semicolon
id|reset_pic
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PERFCTR_SETPCR
suffix:colon
(brace
id|u64
op_star
id|user_pcr
op_assign
(paren
id|u64
op_star
)paren
id|arg0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcr_reg
comma
id|user_pcr
)paren
suffix:semicolon
id|write_pcr
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcr_reg
)paren
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd0
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|kernel_cntd1
op_assign
l_int|0
suffix:semicolon
id|reset_pic
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PERFCTR_GETPCR
suffix:colon
(brace
id|u64
op_star
id|user_pcr
op_assign
(paren
id|u64
op_star
)paren
id|arg0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_PERFCTR
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|pcr_reg
comma
id|user_pcr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
