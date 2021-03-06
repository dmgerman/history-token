multiline_comment|/*&n; * linux/arch/x86_64/kernel/sys_x86_64.c&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
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
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
multiline_comment|/*&n; * sys_pipe() is the normal C calling standard for creating&n; * a pipe. It&squot;s not the way Unix traditionally does this, though.&n; */
DECL|function|sys_pipe
id|asmlinkage
r_int
id|sys_pipe
c_func
(paren
r_int
id|__user
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
DECL|function|sys_mmap
id|asmlinkage
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
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|off
op_amp
op_complement
id|PAGE_MASK
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
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
id|off
op_rshift
id|PAGE_SHIFT
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
DECL|function|find_start_end
r_static
r_void
id|find_start_end
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
op_star
id|begin
comma
r_int
r_int
op_star
id|end
)paren
(brace
macro_line|#ifdef CONFIG_IA32_EMULATION
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
)paren
(brace
op_star
id|begin
op_assign
id|TASK_UNMAPPED_32
suffix:semicolon
op_star
id|end
op_assign
id|IA32_PAGE_OFFSET
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_32BIT
)paren
(brace
multiline_comment|/* This is usually used needed to map code in small&n;&t;&t;   model, so it needs to be in the first 31bit. Limit&n;&t;&t;   it to that.  This means we need to move the&n;&t;&t;   unmapped base down for this case. This can give&n;&t;&t;   conflicts with the heap, but we assume that glibc&n;&t;&t;   malloc knows how to fall back to mmap. Give it 1GB&n;&t;&t;   of playground for now. -AK */
op_star
id|begin
op_assign
l_int|0x40000000
suffix:semicolon
op_star
id|end
op_assign
l_int|0x80000000
suffix:semicolon
)brace
r_else
(brace
op_star
id|begin
op_assign
id|TASK_UNMAPPED_64
suffix:semicolon
op_star
id|end
op_assign
id|TASK_SIZE
suffix:semicolon
)brace
)brace
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
id|start_addr
suffix:semicolon
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
id|find_start_end
c_func
(paren
id|flags
comma
op_amp
id|begin
comma
op_amp
id|end
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|addr
)paren
(brace
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
id|end
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
id|addr
op_assign
id|mm-&gt;free_area_cache
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|begin
)paren
id|addr
op_assign
id|begin
suffix:semicolon
id|start_addr
op_assign
id|addr
suffix:semicolon
id|full_search
suffix:colon
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
id|end
op_minus
id|len
OL
id|addr
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Start a new search - just in case we missed&n;&t;&t;&t; * some holes.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|start_addr
op_ne
id|begin
)paren
(brace
id|start_addr
op_assign
id|addr
op_assign
id|begin
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
)brace
)brace
DECL|function|sys_uname
id|asmlinkage
r_int
id|sys_uname
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
id|err
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
r_if
c_cond
(paren
id|personality
c_func
(paren
id|current-&gt;personality
)paren
op_eq
id|PER_LINUX32
)paren
id|err
op_or_assign
id|copy_to_user
c_func
(paren
op_amp
id|name-&gt;machine
comma
l_string|&quot;i686&quot;
comma
l_int|5
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|wrap_sys_shmat
id|asmlinkage
r_int
id|wrap_sys_shmat
c_func
(paren
r_int
id|shmid
comma
r_char
id|__user
op_star
id|shmaddr
comma
r_int
id|shmflg
)paren
(brace
r_int
r_int
id|raddr
suffix:semicolon
r_return
id|do_shmat
c_func
(paren
id|shmid
comma
id|shmaddr
comma
id|shmflg
comma
op_amp
id|raddr
)paren
ques
c_cond
suffix:colon
(paren
r_int
)paren
id|raddr
suffix:semicolon
)brace
DECL|function|sys_time64
id|asmlinkage
r_int
id|sys_time64
c_func
(paren
r_int
id|__user
op_star
id|tloc
)paren
(brace
r_struct
id|timeval
id|now
suffix:semicolon
r_int
id|i
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
id|i
op_assign
id|now.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|tloc
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|i
comma
id|tloc
)paren
)paren
id|i
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
eof
