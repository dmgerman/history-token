multiline_comment|/* ptrace.c */
multiline_comment|/* By Ross Biro 1/23/92 */
multiline_comment|/* edited by Linus Torvalds */
multiline_comment|/* mangled further by Bob Manson (manson@santafe.edu) */
multiline_comment|/* more mutilation by David Mosberger (davidm@azstarnet.com) */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &quot;proto.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;DBG_MEM
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
r_enum
(brace
DECL|enumerator|DBG_MEM
id|DBG_MEM
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
DECL|enumerator|DBG_BPT
id|DBG_BPT
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
DECL|enumerator|DBG_MEM_ALL
id|DBG_MEM_ALL
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
)brace
suffix:semicolon
DECL|macro|DBG
mdefine_line|#define DBG(fac,args)&t;{if ((fac) &amp; DEBUG) printk args;}
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fac,args)
macro_line|#endif
DECL|macro|BREAKINST
mdefine_line|#define BREAKINST&t;0x00000080&t;/* call_pal bpt */
multiline_comment|/*&n; * does not yet catch signals sent when the child dies.&n; * in exit.c or in signal.c.&n; */
multiline_comment|/*&n; * Processes always block with the following stack-layout:&n; *&n; *  +================================+ &lt;---- task + 2*PAGE_SIZE&n; *  | PALcode saved frame (ps, pc,   | ^&n; *  | gp, a0, a1, a2)&t;&t;     | |&n; *  +================================+ | struct pt_regs&n; *  |&t;        &t;&t;     | |&n; *  | frame generated by SAVE_ALL    | |&n; *  |&t;        &t;&t;     | v&n; *  +================================+&n; *  |&t;        &t;&t;     | ^&n; *  | frame saved by do_switch_stack | | struct switch_stack&n; *  |&t;        &t;&t;     | v&n; *  +================================+&n; */
multiline_comment|/* &n; * The following table maps a register index into the stack offset at&n; * which the register is saved.  Register indices are 0-31 for integer&n; * regs, 32-63 for fp regs, and 64 for the pc.  Notice that sp and&n; * zero have no stack-slot and need to be treated specially (see&n; * get_reg/put_reg below).&n; */
r_enum
(brace
DECL|enumerator|REG_R0
DECL|enumerator|REG_F0
DECL|enumerator|REG_FPCR
DECL|enumerator|REG_PC
id|REG_R0
op_assign
l_int|0
comma
id|REG_F0
op_assign
l_int|32
comma
id|REG_FPCR
op_assign
l_int|63
comma
id|REG_PC
op_assign
l_int|64
)brace
suffix:semicolon
DECL|variable|regoff
r_static
r_int
id|regoff
(braket
)braket
op_assign
(brace
id|PT_REG
c_func
(paren
id|r0
)paren
comma
id|PT_REG
c_func
(paren
id|r1
)paren
comma
id|PT_REG
c_func
(paren
id|r2
)paren
comma
id|PT_REG
c_func
(paren
id|r3
)paren
comma
id|PT_REG
c_func
(paren
id|r4
)paren
comma
id|PT_REG
c_func
(paren
id|r5
)paren
comma
id|PT_REG
c_func
(paren
id|r6
)paren
comma
id|PT_REG
c_func
(paren
id|r7
)paren
comma
id|PT_REG
c_func
(paren
id|r8
)paren
comma
id|SW_REG
c_func
(paren
id|r9
)paren
comma
id|SW_REG
c_func
(paren
id|r10
)paren
comma
id|SW_REG
c_func
(paren
id|r11
)paren
comma
id|SW_REG
c_func
(paren
id|r12
)paren
comma
id|SW_REG
c_func
(paren
id|r13
)paren
comma
id|SW_REG
c_func
(paren
id|r14
)paren
comma
id|SW_REG
c_func
(paren
id|r15
)paren
comma
id|PT_REG
c_func
(paren
id|r16
)paren
comma
id|PT_REG
c_func
(paren
id|r17
)paren
comma
id|PT_REG
c_func
(paren
id|r18
)paren
comma
id|PT_REG
c_func
(paren
id|r19
)paren
comma
id|PT_REG
c_func
(paren
id|r20
)paren
comma
id|PT_REG
c_func
(paren
id|r21
)paren
comma
id|PT_REG
c_func
(paren
id|r22
)paren
comma
id|PT_REG
c_func
(paren
id|r23
)paren
comma
id|PT_REG
c_func
(paren
id|r24
)paren
comma
id|PT_REG
c_func
(paren
id|r25
)paren
comma
id|PT_REG
c_func
(paren
id|r26
)paren
comma
id|PT_REG
c_func
(paren
id|r27
)paren
comma
id|PT_REG
c_func
(paren
id|r28
)paren
comma
id|PT_REG
c_func
(paren
id|gp
)paren
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|0
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|1
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|2
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|3
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|4
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|5
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|6
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|7
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|8
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|9
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|10
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|11
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|12
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|13
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|14
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|15
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|16
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|17
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|18
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|19
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|20
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|21
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|22
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|23
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|24
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|25
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|26
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|27
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|28
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|29
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|30
)braket
)paren
comma
id|SW_REG
c_func
(paren
id|fp
(braket
l_int|31
)braket
)paren
comma
id|PT_REG
c_func
(paren
id|pc
)paren
)brace
suffix:semicolon
DECL|variable|zero
r_static
r_int
id|zero
suffix:semicolon
multiline_comment|/*&n; * Get address of register REGNO in task TASK.&n; */
r_static
r_int
op_star
DECL|function|get_reg_addr
id|get_reg_addr
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
r_int
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_eq
l_int|30
)paren
(brace
id|addr
op_assign
op_amp
id|task-&gt;thread_info-&gt;pcb.usp
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|regno
op_eq
l_int|65
)paren
(brace
id|addr
op_assign
op_amp
id|task-&gt;thread_info-&gt;pcb.unique
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|regno
op_eq
l_int|31
op_logical_or
id|regno
OG
l_int|65
)paren
(brace
id|zero
op_assign
l_int|0
suffix:semicolon
id|addr
op_assign
op_amp
id|zero
suffix:semicolon
)brace
r_else
(brace
id|addr
op_assign
(paren
r_int
op_star
)paren
(paren
(paren
r_int
)paren
id|task-&gt;thread_info
op_plus
id|regoff
(braket
id|regno
)braket
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Get contents of register REGNO in task TASK.&n; */
r_static
r_int
DECL|function|get_reg
id|get_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
)paren
(brace
multiline_comment|/* Special hack for fpcr -- combine hardware and software bits.  */
r_if
c_cond
(paren
id|regno
op_eq
l_int|63
)paren
(brace
r_int
r_int
id|fpcr
op_assign
op_star
id|get_reg_addr
c_func
(paren
id|task
comma
id|regno
)paren
suffix:semicolon
r_int
r_int
id|swcr
op_assign
id|task-&gt;thread_info-&gt;ieee_state
op_amp
id|IEEE_SW_MASK
suffix:semicolon
id|swcr
op_assign
id|swcr_update_status
c_func
(paren
id|swcr
comma
id|fpcr
)paren
suffix:semicolon
r_return
id|fpcr
op_or
id|swcr
suffix:semicolon
)brace
r_return
op_star
id|get_reg_addr
c_func
(paren
id|task
comma
id|regno
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write contents of register REGNO in task TASK.&n; */
r_static
r_int
DECL|function|put_reg
id|put_reg
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|regno
comma
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|regno
op_eq
l_int|63
)paren
(brace
id|task-&gt;thread_info-&gt;ieee_state
op_assign
(paren
(paren
id|task-&gt;thread_info-&gt;ieee_state
op_amp
op_complement
id|IEEE_SW_MASK
)paren
op_or
(paren
id|data
op_amp
id|IEEE_SW_MASK
)paren
)paren
suffix:semicolon
id|data
op_assign
(paren
id|data
op_amp
id|FPCR_DYN_MASK
)paren
op_or
id|ieee_swcr_to_fpcr
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
op_star
id|get_reg_addr
c_func
(paren
id|task
comma
id|regno
)paren
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|read_int
id|read_int
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
comma
r_int
op_star
id|data
)paren
(brace
r_int
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
comma
id|data
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|copied
op_eq
r_sizeof
(paren
r_int
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|write_int
id|write_int
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|task
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|copied
op_eq
r_sizeof
(paren
r_int
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * Set breakpoint.&n; */
r_int
DECL|function|ptrace_set_bpt
id|ptrace_set_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|displ
comma
id|i
comma
id|res
comma
id|reg_b
comma
id|nsaved
op_assign
l_int|0
suffix:semicolon
id|u32
id|insn
comma
id|op_code
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
id|pc
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|REG_PC
)paren
suffix:semicolon
id|res
op_assign
id|read_int
c_func
(paren
id|child
comma
id|pc
comma
op_amp
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
id|op_code
op_assign
id|insn
op_rshift
l_int|26
suffix:semicolon
r_if
c_cond
(paren
id|op_code
op_ge
l_int|0x30
)paren
(brace
multiline_comment|/*&n;&t;&t; * It&squot;s a branch: instead of trying to figure out&n;&t;&t; * whether the branch will be taken or not, we&squot;ll put&n;&t;&t; * a breakpoint at either location.  This is simpler,&n;&t;&t; * more reliable, and probably not a whole lot slower&n;&t;&t; * than the alternative approach of emulating the&n;&t;&t; * branch (emulation can be tricky for fp branches).&n;&t;&t; */
id|displ
op_assign
(paren
(paren
id|s32
)paren
(paren
id|insn
op_lshift
l_int|11
)paren
)paren
op_rshift
l_int|9
suffix:semicolon
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|displ
)paren
multiline_comment|/* guard against unoptimized code */
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
op_plus
id|displ
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing branch&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|op_code
op_eq
l_int|0x1a
)paren
(brace
id|reg_b
op_assign
(paren
id|insn
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|reg_b
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing jump&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|nsaved
op_increment
)braket
op_assign
id|pc
op_plus
l_int|4
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;execing normal insn&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* install breakpoints: */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nsaved
suffix:semicolon
op_increment
id|i
)paren
(brace
id|res
op_assign
id|read_int
c_func
(paren
id|child
comma
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|i
)braket
comma
op_amp
id|insn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
id|child-&gt;thread_info-&gt;bpt_insn
(braket
id|i
)braket
op_assign
id|insn
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_BPT
comma
(paren
l_string|&quot;    -&gt; next_pc=%lx&bslash;n&quot;
comma
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|res
op_assign
id|write_int
c_func
(paren
id|child
comma
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|i
)braket
comma
id|BREAKINST
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
r_return
id|res
suffix:semicolon
)brace
id|child-&gt;thread_info-&gt;bpt_nsaved
op_assign
id|nsaved
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Ensure no single-step breakpoint is pending.  Returns non-zero&n; * value if child was being single-stepped.&n; */
r_int
DECL|function|ptrace_cancel_bpt
id|ptrace_cancel_bpt
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
r_int
id|i
comma
id|nsaved
op_assign
id|child-&gt;thread_info-&gt;bpt_nsaved
suffix:semicolon
id|child-&gt;thread_info-&gt;bpt_nsaved
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nsaved
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptrace_cancel_bpt: bogus nsaved: %d!&bslash;n&quot;
comma
id|nsaved
)paren
suffix:semicolon
id|nsaved
op_assign
l_int|2
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nsaved
suffix:semicolon
op_increment
id|i
)paren
(brace
id|write_int
c_func
(paren
id|child
comma
id|child-&gt;thread_info-&gt;bpt_addr
(braket
id|i
)braket
comma
id|child-&gt;thread_info-&gt;bpt_insn
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
(paren
id|nsaved
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure the single step bit is not set.&n; */
DECL|function|ptrace_disable
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|do_sys_ptrace
id|do_sys_ptrace
c_func
(paren
r_int
id|request
comma
r_int
id|pid
comma
r_int
id|addr
comma
r_int
id|data
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|copied
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;request=%ld pid=%ld addr=0x%lx data=0x%lx&bslash;n&quot;
comma
id|request
comma
id|pid
comma
id|addr
comma
id|data
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out_notsk
suffix:semicolon
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_notsk
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process ptrace flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_notsk
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* you may not mess with init */
r_goto
id|out_notsk
suffix:semicolon
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
r_goto
id|out_notsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
id|ptrace_attach
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|ptrace_check_attach
c_func
(paren
id|child
comma
id|request
op_eq
id|PTRACE_KILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
multiline_comment|/* When I and D space are separate, these will need to be fixed.  */
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
id|regs-&gt;r0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* special return: no errors */
id|ret
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Read register number ADDR. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
id|regs-&gt;r0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* special return: no errors */
id|ret
op_assign
id|get_reg
c_func
(paren
id|child
comma
id|addr
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;peek $%ld-&gt;%#lx&bslash;n&quot;
comma
id|addr
comma
id|ret
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* When I and D space are separate, this will have to be fixed.  */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|tmp
op_assign
id|data
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|copied
op_eq
r_sizeof
(paren
id|tmp
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_POKEUSR
suffix:colon
multiline_comment|/* write the specified register */
id|DBG
c_func
(paren
id|DBG_MEM
comma
(paren
l_string|&quot;poke $%ld&lt;-%#lx&bslash;n&quot;
comma
id|addr
comma
id|data
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|put_reg
c_func
(paren
id|child
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
multiline_comment|/* restart after signal. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
r_else
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* make sure single-step breakpoint is gone. */
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * Make the child exit.  Best I can do is send it a sigkill.&n;&t; * perhaps it should be put in the status that it wants to&n;&t; * exit.&n;&t; */
r_case
id|PTRACE_KILL
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
r_break
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
multiline_comment|/* make sure single-step breakpoint is gone. */
id|ptrace_cancel_bpt
c_func
(paren
id|child
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_SINGLESTEP
suffix:colon
multiline_comment|/* execute single instruction. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_break
suffix:semicolon
multiline_comment|/* Mark single stepping.  */
id|child-&gt;thread_info-&gt;bpt_nsaved
op_assign
op_minus
l_int|1
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* give it a chance to run. */
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|PTRACE_DETACH
suffix:colon
multiline_comment|/* detach a process that was attached. */
id|ret
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|ptrace_request
c_func
(paren
id|child
comma
id|request
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
id|put_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|out_notsk
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
r_void
DECL|function|syscall_trace
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* The 0x80 provides a way for the tracing parent to distinguish&n;&t;   between a syscall stop and SIGTRAP delivery */
id|ptrace_notify
c_func
(paren
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
