multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2000 by Ralf Baechle and others.&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
macro_line|#include &lt;asm/inst.h&gt;
multiline_comment|/*&n; * We use this if we don&squot;t have any better idle routine..&n; * (This to kill: kernel/platform.c.&n; */
DECL|function|default_idle
r_void
id|default_idle
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be done, so just try to conserve&n; * power and have a low exit latency (ie sit in a loop waiting for somebody to&n; * say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
id|ATTRIB_NORET
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
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
)brace
)brace
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|start_thread
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* New thread loses kernel privileges. */
id|status
op_assign
id|regs-&gt;cp0_status
op_amp
op_complement
(paren
id|ST0_CU0
op_or
id|ST0_CU1
op_or
id|KU_MASK
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS64
id|status
op_and_assign
op_complement
id|ST0_FR
suffix:semicolon
id|status
op_or_assign
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_32BIT_REGS
)paren
ques
c_cond
l_int|0
suffix:colon
id|ST0_FR
suffix:semicolon
macro_line|#endif
id|status
op_or_assign
id|KU_USER
suffix:semicolon
id|regs-&gt;cp0_status
op_assign
id|status
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|lose_fpu
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|29
)braket
op_assign
id|sp
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|addr_limit
op_assign
id|USER_DS
suffix:semicolon
)brace
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
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
id|thread_info
op_star
id|ti
op_assign
id|p-&gt;thread_info
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_int
id|childksp
suffix:semicolon
id|childksp
op_assign
(paren
r_int
r_int
)paren
id|ti
op_plus
id|THREAD_SIZE
op_minus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|is_fpu_owner
c_func
(paren
)paren
)paren
(brace
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
macro_line|#ifdef CONFIG_BINFMT_IRIX
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_LINUX
)paren
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
r_else
macro_line|#endif
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
id|ti
suffix:semicolon
id|childregs-&gt;regs
(braket
l_int|29
)braket
op_assign
id|childksp
suffix:semicolon
id|ti-&gt;addr_limit
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
id|ti-&gt;addr_limit
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
multiline_comment|/*&n;&t; * New tasks lose permission to use the fpu. This accelerates context&n;&t; * switching for most programs since they don&squot;t use the fpu.&n;&t; */
id|p-&gt;thread.cp0_status
op_assign
id|read_c0_status
c_func
(paren
)paren
op_amp
op_complement
(paren
id|ST0_CU2
op_or
id|ST0_CU1
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
id|clear_tsk_thread_flag
c_func
(paren
id|p
comma
id|TIF_USEDFPU
)paren
suffix:semicolon
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
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
l_string|&quot;&t;move&t;$6, $sp&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$4, %5&t;&t;&bslash;n&quot;
l_string|&quot;&t;li&t;$2, %1&t;&t;&bslash;n&quot;
l_string|&quot;&t;syscall&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beq&t;$6, $sp, 1f&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_MIPS32&t;/* On o32 the caller has to create the stackframe */
l_string|&quot;&t;subu&t;$sp, 32&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;&t;move&t;$4, %3&t;&t;&bslash;n&quot;
l_string|&quot;&t;jalr&t;%4&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$4, $2&t;&t;&bslash;n&quot;
l_string|&quot;&t;li&t;$2, %2&t;&t;&bslash;n&quot;
l_string|&quot;&t;syscall&t;&t;&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_MIPS32&t;/* On o32 the caller has to deallocate the stackframe */
l_string|&quot;&t;addiu&t;$sp, 32&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;1:&t;move&t;%0, $2&quot;
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
comma
l_string|&quot;$31&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|struct|mips_frame_info
r_struct
id|mips_frame_info
(brace
DECL|member|frame_offset
r_int
id|frame_offset
suffix:semicolon
DECL|member|pc_offset
r_int
id|pc_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|schedule_frame
r_static
r_struct
id|mips_frame_info
id|schedule_frame
suffix:semicolon
DECL|variable|schedule_timeout_frame
r_static
r_struct
id|mips_frame_info
id|schedule_timeout_frame
suffix:semicolon
DECL|variable|sleep_on_frame
r_static
r_struct
id|mips_frame_info
id|sleep_on_frame
suffix:semicolon
DECL|variable|sleep_on_timeout_frame
r_static
r_struct
id|mips_frame_info
id|sleep_on_timeout_frame
suffix:semicolon
DECL|variable|wait_for_completion_frame
r_static
r_struct
id|mips_frame_info
id|wait_for_completion_frame
suffix:semicolon
DECL|variable|mips_frame_info_initialized
r_static
r_int
id|mips_frame_info_initialized
suffix:semicolon
DECL|function|get_frame_info
r_static
r_int
id|__init
id|get_frame_info
c_func
(paren
r_struct
id|mips_frame_info
op_star
id|info
comma
r_void
op_star
id|func
)paren
(brace
r_int
id|i
suffix:semicolon
r_union
id|mips_instruction
op_star
id|ip
op_assign
(paren
r_union
id|mips_instruction
op_star
)paren
id|func
suffix:semicolon
id|info-&gt;pc_offset
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;frame_offset
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
comma
id|ip
op_increment
)paren
(brace
multiline_comment|/* if jal, jalr, jr, stop. */
r_if
c_cond
(paren
id|ip-&gt;j_format.opcode
op_eq
id|jal_op
op_logical_or
(paren
id|ip-&gt;r_format.opcode
op_eq
id|spec_op
op_logical_and
(paren
id|ip-&gt;r_format.func
op_eq
id|jalr_op
op_logical_or
id|ip-&gt;r_format.func
op_eq
id|jr_op
)paren
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
macro_line|#ifdef CONFIG_MIPS32
id|ip-&gt;i_format.opcode
op_eq
id|sw_op
op_logical_and
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
id|ip-&gt;i_format.opcode
op_eq
id|sd_op
op_logical_and
macro_line|#endif
id|ip-&gt;i_format.rs
op_eq
l_int|29
)paren
(brace
multiline_comment|/* sw / sd $ra, offset($sp) */
r_if
c_cond
(paren
id|ip-&gt;i_format.rt
op_eq
l_int|31
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;pc_offset
op_ne
op_minus
l_int|1
)paren
r_break
suffix:semicolon
id|info-&gt;pc_offset
op_assign
id|ip-&gt;i_format.simmediate
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
multiline_comment|/* sw / sd $s8, offset($sp) */
r_if
c_cond
(paren
id|ip-&gt;i_format.rt
op_eq
l_int|30
)paren
(brace
r_if
c_cond
(paren
id|info-&gt;frame_offset
op_ne
op_minus
l_int|1
)paren
r_break
suffix:semicolon
id|info-&gt;frame_offset
op_assign
id|ip-&gt;i_format.simmediate
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|info-&gt;pc_offset
op_eq
op_minus
l_int|1
op_logical_or
id|info-&gt;frame_offset
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Can&squot;t analyze prologue code at %p&bslash;n&quot;
comma
id|func
)paren
suffix:semicolon
id|info-&gt;pc_offset
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;frame_offset
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|frame_info_init
r_void
id|__init
id|frame_info_init
c_func
(paren
r_void
)paren
(brace
id|mips_frame_info_initialized
op_assign
op_logical_neg
id|get_frame_info
c_func
(paren
op_amp
id|schedule_frame
comma
id|schedule
)paren
op_logical_and
op_logical_neg
id|get_frame_info
c_func
(paren
op_amp
id|schedule_timeout_frame
comma
id|schedule_timeout
)paren
op_logical_and
op_logical_neg
id|get_frame_info
c_func
(paren
op_amp
id|sleep_on_frame
comma
id|sleep_on
)paren
op_logical_and
op_logical_neg
id|get_frame_info
c_func
(paren
op_amp
id|sleep_on_timeout_frame
comma
id|sleep_on_timeout
)paren
op_logical_and
op_logical_neg
id|get_frame_info
c_func
(paren
op_amp
id|wait_for_completion_frame
comma
id|wait_for_completion
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|thread_struct
op_star
id|t
op_assign
op_amp
id|tsk-&gt;thread
suffix:semicolon
multiline_comment|/* New born processes are a special case */
r_if
c_cond
(paren
id|t-&gt;reg31
op_eq
(paren
r_int
r_int
)paren
id|ret_from_fork
)paren
r_return
id|t-&gt;reg31
suffix:semicolon
r_if
c_cond
(paren
id|schedule_frame.pc_offset
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;reg29
)paren
(braket
id|schedule_frame.pc_offset
)braket
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
multiline_comment|/* get_wchan - a maintenance nightmare^W^Wpain in the ass ...  */
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
r_if
c_cond
(paren
op_logical_neg
id|mips_frame_info_initialized
)paren
r_return
l_int|0
suffix:semicolon
id|pc
op_assign
id|thread_saved_pc
c_func
(paren
id|p
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
r_goto
id|out
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
r_if
c_cond
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|wait_for_completion
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
id|schedule_frame.frame_offset
)braket
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
id|sleep_on_frame.pc_offset
)braket
suffix:semicolon
r_else
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
id|wait_for_completion_frame.pc_offset
)braket
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|schedule_timeout_caller
suffix:colon
multiline_comment|/*&n;&t; * The schedule_timeout frame&n;&t; */
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
id|schedule_frame.frame_offset
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * frame now points to sleep_on_timeout&squot;s frame&n;&t; */
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
id|schedule_timeout_frame.pc_offset
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
multiline_comment|/* schedule_timeout called by [interruptible_]sleep_on_timeout */
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
id|schedule_timeout_frame.frame_offset
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
id|sleep_on_timeout_frame.pc_offset
)braket
suffix:semicolon
)brace
id|out
suffix:colon
macro_line|#ifdef CONFIG_MIPS64
r_if
c_cond
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_32BIT_REGS
)paren
multiline_comment|/* Kludge for 32-bit ps  */
id|pc
op_and_assign
l_int|0xffffffffUL
suffix:semicolon
macro_line|#endif
r_return
id|pc
suffix:semicolon
)brace
eof
