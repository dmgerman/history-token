multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 2000 by Ralf Baechle and others.&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|current-&gt;nice
op_assign
l_int|20
suffix:semicolon
id|init_idle
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
r_if
c_cond
(paren
id|cpu_wait
)paren
(paren
op_star
id|cpu_wait
)paren
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|last_task_used_math
r_struct
id|task_struct
op_star
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Forget lazy fpu state */
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cfc1&bslash;t$0,$31&quot;
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Forget lazy fpu state */
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cfc1&bslash;t$0,$31&quot;
)paren
suffix:semicolon
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|copy_thread
r_int
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_int
r_int
id|unused
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_int
id|childksp
suffix:semicolon
r_extern
r_void
id|save_fp
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
id|childksp
op_assign
(paren
r_int
r_int
)paren
id|p
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
r_if
c_cond
(paren
id|mips_cpu.options
op_amp
id|MIPS_CPU_FPU
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_CU1
)paren
suffix:semicolon
id|save_fp
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/* set up new TSS. */
id|childregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|childksp
op_minus
l_int|1
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;regs
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear error flag */
r_if
c_cond
(paren
id|current-&gt;personality
op_eq
id|PER_LINUX
)paren
(brace
id|childregs-&gt;regs
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Child gets zero as return value */
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|p-&gt;pid
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Under IRIX things are a little different. */
id|childregs-&gt;regs
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;regs
(braket
l_int|3
)braket
op_assign
l_int|1
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|p-&gt;pid
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|childregs-&gt;cp0_status
op_amp
id|ST0_CU0
)paren
(brace
id|childregs-&gt;regs
(braket
l_int|28
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|childregs-&gt;regs
(braket
l_int|29
)braket
op_assign
id|childksp
suffix:semicolon
id|p-&gt;thread.current_ds
op_assign
id|KERNEL_DS
suffix:semicolon
)brace
r_else
(brace
id|childregs-&gt;regs
(braket
l_int|29
)braket
op_assign
id|usp
suffix:semicolon
id|p-&gt;thread.current_ds
op_assign
id|USER_DS
suffix:semicolon
)brace
id|p-&gt;thread.reg29
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.reg31
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
multiline_comment|/*&n;&t; * New tasks loose permission to use the fpu. This accelerates context&n;&t; * switching for most programs since they don&squot;t use the fpu.&n;&t; */
id|p-&gt;thread.cp0_status
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
)paren
op_amp
op_complement
(paren
id|ST0_CU2
op_or
id|ST0_CU1
op_or
id|KU_MASK
)paren
suffix:semicolon
id|childregs-&gt;cp0_status
op_and_assign
op_complement
(paren
id|ST0_CU2
op_or
id|ST0_CU1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fill in the fpu structure for a core dump.. */
DECL|function|dump_fpu
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|r
)paren
(brace
multiline_comment|/* We actually store the FPU info in the task-&gt;thread&n;&t; * area.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;cp0_status
op_amp
id|ST0_CU1
)paren
(brace
id|memcpy
c_func
(paren
id|r
comma
op_amp
id|current-&gt;thread.fpu
comma
r_sizeof
(paren
id|current-&gt;thread.fpu
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Task didn&squot;t use the fpu at all. */
)brace
multiline_comment|/* Fill in the user structure for a core dump.. */
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
id|current-&gt;mm-&gt;start_code
suffix:semicolon
id|dump-&gt;start_data
op_assign
id|current-&gt;mm-&gt;start_data
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;regs
(braket
l_int|29
)braket
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
id|current-&gt;mm-&gt;end_code
op_minus
id|dump-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
id|dump-&gt;start_data
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
(paren
id|current-&gt;mm-&gt;start_stack
op_minus
id|dump-&gt;start_stack
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs
(braket
l_int|0
)braket
comma
id|regs
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs
(braket
id|EF_SIZE
op_div
l_int|4
)braket
comma
op_amp
id|current-&gt;thread.fpu
comma
r_sizeof
(paren
id|current-&gt;thread.fpu
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
DECL|function|kernel_thread
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder               &bslash;n&quot;
l_string|&quot;    move    $6,$sp           &bslash;n&quot;
l_string|&quot;    move    $4,%5            &bslash;n&quot;
l_string|&quot;    li      $2,%1            &bslash;n&quot;
l_string|&quot;    syscall                  &bslash;n&quot;
l_string|&quot;    beq     $6,$sp,1f        &bslash;n&quot;
l_string|&quot;    subu    $sp,32           &bslash;n&quot;
multiline_comment|/* delay slot */
l_string|&quot;    jalr    %4               &bslash;n&quot;
l_string|&quot;    move    $4,%3            &bslash;n&quot;
multiline_comment|/* delay slot */
l_string|&quot;    move    $4,$2            &bslash;n&quot;
l_string|&quot;    li      $2,%2            &bslash;n&quot;
l_string|&quot;    syscall                  &bslash;n&quot;
l_string|&quot;1:  addiu   $sp,32           &bslash;n&quot;
l_string|&quot;    move    %0,$2            &bslash;n&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|__NR_clone
)paren
comma
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg
)paren
comma
l_string|&quot;r&quot;
(paren
id|fn
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
op_or
id|CLONE_VM
op_or
id|CLONE_UNTRACED
)paren
multiline_comment|/*&n;&t;&t;  * The called subroutine might have destroyed any of the&n;&t;&t;  * at, result, argument or temporary registers ...&n;&t;&t;  */
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$7&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;$10&quot;
comma
l_string|&quot;$11&quot;
comma
l_string|&quot;$12&quot;
comma
l_string|&quot;$13&quot;
comma
l_string|&quot;$14&quot;
comma
l_string|&quot;$15&quot;
comma
l_string|&quot;$24&quot;
comma
l_string|&quot;$25&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long) scheduling_functions_end_here)
multiline_comment|/* get_wchan - a maintenance nightmare ...  */
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|frame
comma
id|pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|pc
op_assign
id|thread_saved_pc
c_func
(paren
op_amp
id|p-&gt;thread
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pc
OL
id|first_sched
op_logical_or
id|pc
op_ge
id|last_sched
)paren
(brace
r_return
id|pc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|sleep_on_timeout
)paren
r_goto
id|schedule_timeout_caller
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|sleep_on
)paren
r_goto
id|schedule_caller
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|interruptible_sleep_on_timeout
)paren
r_goto
id|schedule_timeout_caller
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|interruptible_sleep_on
)paren
r_goto
id|schedule_caller
suffix:semicolon
r_goto
id|schedule_timeout_caller
suffix:semicolon
id|schedule_caller
suffix:colon
id|frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;thread.reg30
)paren
(braket
l_int|9
)braket
suffix:semicolon
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|frame
)paren
(braket
l_int|11
)braket
suffix:semicolon
r_return
id|pc
suffix:semicolon
id|schedule_timeout_caller
suffix:colon
multiline_comment|/* Must be schedule_timeout ...  */
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;thread.reg30
)paren
(braket
l_int|10
)braket
suffix:semicolon
id|frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;thread.reg30
)paren
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* The schedule_timeout frame ...  */
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|frame
)paren
(braket
l_int|14
)braket
suffix:semicolon
id|frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|frame
)paren
(braket
l_int|13
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
id|first_sched
op_logical_and
id|pc
OL
id|last_sched
)paren
(brace
multiline_comment|/* schedule_timeout called by interruptible_sleep_on_timeout */
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|frame
)paren
(braket
l_int|11
)braket
suffix:semicolon
id|frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|frame
)paren
(braket
l_int|10
)braket
suffix:semicolon
)brace
r_return
id|pc
suffix:semicolon
)brace
eof
