multiline_comment|/* arch/sparc64/kernel/kprobes.c&n; *&n; * Copyright (C) 2004 David S. Miller &lt;davem@davemloft.net&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kprobes.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
multiline_comment|/* We do not have hardware single-stepping on sparc64.&n; * So we implement software single-stepping with breakpoint&n; * traps.  The top-level scheme is similar to that used&n; * in the x86 kprobes implementation.&n; *&n; * In the kprobe-&gt;ainsn.insn[] array we store the original&n; * instruction at index zero and a break instruction at&n; * index one.&n; *&n; * When we hit a kprobe we:&n; * - Run the pre-handler&n; * - Remember &quot;regs-&gt;tnpc&quot; and interrupt level stored in&n; *   &quot;regs-&gt;tstate&quot; so we can restore them later&n; * - Disable PIL interrupts&n; * - Set regs-&gt;tpc to point to kprobe-&gt;ainsn.insn[0]&n; * - Set regs-&gt;tnpc to point to kprobe-&gt;ainsn.insn[1]&n; * - Mark that we are actively in a kprobe&n; *&n; * At this point we wait for the second breakpoint at&n; * kprobe-&gt;ainsn.insn[1] to hit.  When it does we:&n; * - Run the post-handler&n; * - Set regs-&gt;tpc to &quot;remembered&quot; regs-&gt;tnpc stored above,&n; *   restore the PIL interrupt level in &quot;regs-&gt;tstate&quot; as well&n; * - Make any adjustments necessary to regs-&gt;tnpc in order&n; *   to handle relative branches correctly.  See below.&n; * - Mark that we are no longer actively in a kprobe.&n; */
DECL|function|arch_prepare_kprobe
r_int
id|arch_prepare_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|arch_copy_kprobe
r_void
id|arch_copy_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
)paren
(brace
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
op_assign
op_star
id|p-&gt;addr
suffix:semicolon
id|p-&gt;ainsn.insn
(braket
l_int|1
)braket
op_assign
id|BREAKPOINT_INSTRUCTION_2
suffix:semicolon
)brace
DECL|function|arch_remove_kprobe
r_void
id|arch_remove_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
)paren
(brace
)brace
multiline_comment|/* kprobe_status settings */
DECL|macro|KPROBE_HIT_ACTIVE
mdefine_line|#define KPROBE_HIT_ACTIVE&t;0x00000001
DECL|macro|KPROBE_HIT_SS
mdefine_line|#define KPROBE_HIT_SS&t;&t;0x00000002
DECL|variable|current_kprobe
r_static
r_struct
id|kprobe
op_star
id|current_kprobe
suffix:semicolon
DECL|variable|current_kprobe_orig_tnpc
r_static
r_int
r_int
id|current_kprobe_orig_tnpc
suffix:semicolon
DECL|variable|current_kprobe_orig_tstate_pil
r_static
r_int
r_int
id|current_kprobe_orig_tstate_pil
suffix:semicolon
DECL|variable|kprobe_status
r_static
r_int
r_int
id|kprobe_status
suffix:semicolon
DECL|function|prepare_singlestep
r_static
r_inline
r_void
id|prepare_singlestep
c_func
(paren
r_struct
id|kprobe
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|current_kprobe_orig_tnpc
op_assign
id|regs-&gt;tnpc
suffix:semicolon
id|current_kprobe_orig_tstate_pil
op_assign
(paren
id|regs-&gt;tstate
op_amp
id|TSTATE_PIL
)paren
suffix:semicolon
id|regs-&gt;tstate
op_or_assign
id|TSTATE_PIL
suffix:semicolon
multiline_comment|/*single step inline, if it a breakpoint instruction*/
r_if
c_cond
(paren
id|p-&gt;opcode
op_eq
id|BREAKPOINT_INSTRUCTION
)paren
(brace
id|regs-&gt;tpc
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|current_kprobe_orig_tnpc
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;tpc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
suffix:semicolon
id|regs-&gt;tnpc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
DECL|function|disarm_kprobe
r_static
r_inline
r_void
id|disarm_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
op_star
id|p-&gt;addr
op_assign
id|p-&gt;opcode
suffix:semicolon
id|flushi
c_func
(paren
id|p-&gt;addr
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|current_kprobe_orig_tnpc
suffix:semicolon
id|regs-&gt;tstate
op_assign
(paren
(paren
id|regs-&gt;tstate
op_amp
op_complement
id|TSTATE_PIL
)paren
op_or
id|current_kprobe_orig_tstate_pil
)paren
suffix:semicolon
)brace
DECL|function|kprobe_handler
r_static
r_int
id|kprobe_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|kprobe
op_star
id|p
suffix:semicolon
r_void
op_star
id|addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;tpc
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kprobe_running
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* We *are* holding lock here, so this is safe.&n;&t;&t; * Disarm the probe we just hit, and ignore it.&n;&t;&t; */
id|p
op_assign
id|get_kprobe
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|kprobe_status
op_eq
id|KPROBE_HIT_SS
)paren
(brace
id|regs-&gt;tstate
op_assign
(paren
(paren
id|regs-&gt;tstate
op_amp
op_complement
id|TSTATE_PIL
)paren
op_or
id|current_kprobe_orig_tstate_pil
)paren
suffix:semicolon
id|unlock_kprobes
c_func
(paren
)paren
suffix:semicolon
r_goto
id|no_kprobe
suffix:semicolon
)brace
id|disarm_kprobe
c_func
(paren
id|p
comma
id|regs
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|current_kprobe
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;break_handler
op_logical_and
id|p
op_member_access_from_pointer
id|break_handler
c_func
(paren
id|p
comma
id|regs
)paren
)paren
r_goto
id|ss_probe
suffix:semicolon
)brace
multiline_comment|/* If it&squot;s not ours, can&squot;t be delete race, (we hold lock). */
r_goto
id|no_kprobe
suffix:semicolon
)brace
id|lock_kprobes
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|get_kprobe
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|unlock_kprobes
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|u32
op_star
)paren
id|addr
op_ne
id|BREAKPOINT_INSTRUCTION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The breakpoint instruction was removed right&n;&t;&t;&t; * after we hit it.  Another cpu has removed&n;&t;&t;&t; * either a probepoint or a debugger breakpoint&n;&t;&t;&t; * at this address.  In either case, no further&n;&t;&t;&t; * handling of this interrupt is appropriate.&n;&t;&t;&t; */
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Not one of ours: let kernel handle it */
r_goto
id|no_kprobe
suffix:semicolon
)brace
id|kprobe_status
op_assign
id|KPROBE_HIT_ACTIVE
suffix:semicolon
id|current_kprobe
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pre_handler
op_logical_and
id|p
op_member_access_from_pointer
id|pre_handler
c_func
(paren
id|p
comma
id|regs
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|ss_probe
suffix:colon
id|prepare_singlestep
c_func
(paren
id|p
comma
id|regs
)paren
suffix:semicolon
id|kprobe_status
op_assign
id|KPROBE_HIT_SS
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|no_kprobe
suffix:colon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* If INSN is a relative control transfer instruction,&n; * return the corrected branch destination value.&n; *&n; * The original INSN location was REAL_PC, it actually&n; * executed at PC and produced destination address NPC.&n; */
DECL|function|relbranch_fixup
r_static
r_int
r_int
id|relbranch_fixup
c_func
(paren
id|u32
id|insn
comma
r_int
r_int
id|real_pc
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
)paren
(brace
multiline_comment|/* Branch not taken, no mods necessary.  */
r_if
c_cond
(paren
id|npc
op_eq
id|pc
op_plus
l_int|0x4UL
)paren
r_return
id|real_pc
op_plus
l_int|0x4UL
suffix:semicolon
multiline_comment|/* The three cases are call, branch w/prediction,&n;&t; * and traditional branch.&n;&t; */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc0000000
)paren
op_eq
l_int|0x40000000
op_logical_or
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_eq
l_int|0x00400000
op_logical_or
(paren
id|insn
op_amp
l_int|0xc1c00000
)paren
op_eq
l_int|0x00800000
)paren
(brace
multiline_comment|/* The instruction did all the work for us&n;&t;&t; * already, just apply the offset to the correct&n;&t;&t; * instruction location.&n;&t;&t; */
r_return
(paren
id|real_pc
op_plus
(paren
id|npc
op_minus
id|pc
)paren
)paren
suffix:semicolon
)brace
r_return
id|real_pc
op_plus
l_int|0x4UL
suffix:semicolon
)brace
multiline_comment|/* If INSN is an instruction which writes it&squot;s PC location&n; * into a destination register, fix that up.&n; */
DECL|function|retpc_fixup
r_static
r_void
id|retpc_fixup
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|u32
id|insn
comma
r_int
r_int
id|real_pc
)paren
(brace
r_int
r_int
op_star
id|slot
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Simplest cast is call, which always uses %o7 */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc0000000
)paren
op_eq
l_int|0x40000000
)paren
(brace
id|slot
op_assign
op_amp
id|regs-&gt;u_regs
(braket
id|UREG_I7
)braket
suffix:semicolon
)brace
multiline_comment|/* Jmpl encodes the register inside of the opcode */
r_if
c_cond
(paren
(paren
id|insn
op_amp
l_int|0xc1f80000
)paren
op_eq
l_int|0x81c00000
)paren
(brace
r_int
r_int
id|rd
op_assign
(paren
(paren
id|insn
op_rshift
l_int|25
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rd
op_le
l_int|15
)paren
(brace
id|slot
op_assign
op_amp
id|regs-&gt;u_regs
(braket
id|rd
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Hard case, it goes onto the stack. */
id|flushw_all
c_func
(paren
)paren
suffix:semicolon
id|rd
op_sub_assign
l_int|16
suffix:semicolon
id|slot
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_plus
id|STACK_BIAS
)paren
suffix:semicolon
id|slot
op_add_assign
id|rd
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|slot
op_ne
l_int|NULL
)paren
op_star
id|slot
op_assign
id|real_pc
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after single-stepping.  p-&gt;addr is the address of the&n; * instruction whose first byte has been replaced by the breakpoint&n; * instruction.  To avoid the SMP problems that can occur when we&n; * temporarily put back the original opcode to single-step, we&n; * single-stepped a copy of the instruction.  The address of this&n; * copy is p-&gt;ainsn.insn.&n; *&n; * This function prepares to return from the post-single-step&n; * breakpoint trap.&n; */
DECL|function|resume_execution
r_static
r_void
id|resume_execution
c_func
(paren
r_struct
id|kprobe
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|insn
op_assign
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
suffix:semicolon
id|regs-&gt;tpc
op_assign
id|current_kprobe_orig_tnpc
suffix:semicolon
id|regs-&gt;tnpc
op_assign
id|relbranch_fixup
c_func
(paren
id|insn
comma
(paren
r_int
r_int
)paren
id|p-&gt;addr
comma
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
comma
id|regs-&gt;tnpc
)paren
suffix:semicolon
id|retpc_fixup
c_func
(paren
id|regs
comma
id|insn
comma
(paren
r_int
r_int
)paren
id|p-&gt;addr
)paren
suffix:semicolon
id|regs-&gt;tstate
op_assign
(paren
(paren
id|regs-&gt;tstate
op_amp
op_complement
id|TSTATE_PIL
)paren
op_or
id|current_kprobe_orig_tstate_pil
)paren
suffix:semicolon
)brace
DECL|function|post_kprobe_handler
r_static
r_inline
r_int
id|post_kprobe_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kprobe_running
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current_kprobe-&gt;post_handler
)paren
id|current_kprobe
op_member_access_from_pointer
id|post_handler
c_func
(paren
id|current_kprobe
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|resume_execution
c_func
(paren
id|current_kprobe
comma
id|regs
)paren
suffix:semicolon
id|unlock_kprobes
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Interrupts disabled, kprobe_lock held. */
DECL|function|kprobe_fault_handler
r_static
r_inline
r_int
id|kprobe_fault_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|trapnr
)paren
(brace
r_if
c_cond
(paren
id|current_kprobe-&gt;fault_handler
op_logical_and
id|current_kprobe
op_member_access_from_pointer
id|fault_handler
c_func
(paren
id|current_kprobe
comma
id|regs
comma
id|trapnr
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|kprobe_status
op_amp
id|KPROBE_HIT_SS
)paren
(brace
id|resume_execution
c_func
(paren
id|current_kprobe
comma
id|regs
)paren
suffix:semicolon
id|unlock_kprobes
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Wrapper routine to for handling exceptions.&n; */
DECL|function|kprobe_exceptions_notify
r_int
id|kprobe_exceptions_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|die_args
op_star
id|args
op_assign
(paren
r_struct
id|die_args
op_star
)paren
id|data
suffix:semicolon
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
id|DIE_DEBUG
suffix:colon
r_if
c_cond
(paren
id|kprobe_handler
c_func
(paren
id|args-&gt;regs
)paren
)paren
r_return
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIE_DEBUG_2
suffix:colon
r_if
c_cond
(paren
id|post_kprobe_handler
c_func
(paren
id|args-&gt;regs
)paren
)paren
r_return
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIE_GPF
suffix:colon
r_if
c_cond
(paren
id|kprobe_running
c_func
(paren
)paren
op_logical_and
id|kprobe_fault_handler
c_func
(paren
id|args-&gt;regs
comma
id|args-&gt;trapnr
)paren
)paren
r_return
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIE_PAGE_FAULT
suffix:colon
r_if
c_cond
(paren
id|kprobe_running
c_func
(paren
)paren
op_logical_and
id|kprobe_fault_handler
c_func
(paren
id|args-&gt;regs
comma
id|args-&gt;trapnr
)paren
)paren
r_return
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|function|kprobe_trap
id|asmlinkage
r_void
id|kprobe_trap
c_func
(paren
r_int
r_int
id|trap_level
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|BUG_ON
c_func
(paren
id|trap_level
op_ne
l_int|0x170
op_logical_and
id|trap_level
op_ne
l_int|0x171
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|bad_trap
c_func
(paren
id|regs
comma
id|trap_level
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* trap_level == 0x170 --&gt; ta 0x70&n;&t; * trap_level == 0x171 --&gt; ta 0x71&n;&t; */
r_if
c_cond
(paren
id|notify_die
c_func
(paren
(paren
id|trap_level
op_eq
l_int|0x170
)paren
ques
c_cond
id|DIE_DEBUG
suffix:colon
id|DIE_DEBUG_2
comma
(paren
id|trap_level
op_eq
l_int|0x170
)paren
ques
c_cond
l_string|&quot;debug&quot;
suffix:colon
l_string|&quot;debug_2&quot;
comma
id|regs
comma
l_int|0
comma
id|trap_level
comma
id|SIGTRAP
)paren
op_ne
id|NOTIFY_STOP
)paren
id|bad_trap
c_func
(paren
id|regs
comma
id|trap_level
)paren
suffix:semicolon
)brace
multiline_comment|/* Jprobes support.  */
DECL|variable|jprobe_saved_regs
r_static
r_struct
id|pt_regs
id|jprobe_saved_regs
suffix:semicolon
DECL|variable|jprobe_saved_regs_location
r_static
r_struct
id|pt_regs
op_star
id|jprobe_saved_regs_location
suffix:semicolon
DECL|variable|jprobe_saved_stack
r_static
r_struct
id|sparc_stackf
id|jprobe_saved_stack
suffix:semicolon
DECL|function|setjmp_pre_handler
r_int
id|setjmp_pre_handler
c_func
(paren
r_struct
id|kprobe
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
id|jprobe
op_star
id|jp
op_assign
id|container_of
c_func
(paren
id|p
comma
r_struct
id|jprobe
comma
id|kp
)paren
suffix:semicolon
id|jprobe_saved_regs_location
op_assign
id|regs
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|jprobe_saved_regs
comma
id|regs
comma
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
multiline_comment|/* Save a whole stack frame, this gets arguments&n;&t; * pushed onto the stack after using up all the&n;&t; * arg registers.&n;&t; */
id|memcpy
c_func
(paren
op_amp
id|jprobe_saved_stack
comma
(paren
r_char
op_star
)paren
(paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_plus
id|STACK_BIAS
)paren
comma
r_sizeof
(paren
id|jprobe_saved_stack
)paren
)paren
suffix:semicolon
id|regs-&gt;tpc
op_assign
(paren
r_int
r_int
)paren
id|jp-&gt;entry
suffix:semicolon
id|regs-&gt;tnpc
op_assign
(paren
(paren
r_int
r_int
)paren
id|jp-&gt;entry
)paren
op_plus
l_int|0x4UL
suffix:semicolon
id|regs-&gt;tstate
op_or_assign
id|TSTATE_PIL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|jprobe_return
r_void
id|jprobe_return
c_func
(paren
r_void
)paren
(brace
id|preempt_enable_no_resched
c_func
(paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.globl&t;jprobe_return_trap_instruction&bslash;n&quot;
l_string|&quot;jprobe_return_trap_instruction:&bslash;n&bslash;t&quot;
l_string|&quot;ta 0x70&quot;
)paren
suffix:semicolon
)brace
r_extern
r_void
id|jprobe_return_trap_instruction
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|longjmp_break_handler
r_int
id|longjmp_break_handler
c_func
(paren
r_struct
id|kprobe
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
op_star
id|addr
op_assign
(paren
id|u32
op_star
)paren
id|regs-&gt;tpc
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
(paren
id|u32
op_star
)paren
id|jprobe_return_trap_instruction
)paren
(brace
r_if
c_cond
(paren
id|jprobe_saved_regs_location
op_ne
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;JPROBE: Current regs (%p) does not match &quot;
l_string|&quot;saved regs (%p).&bslash;n&quot;
comma
id|regs
comma
id|jprobe_saved_regs_location
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;JPROBE: Saved registers&bslash;n&quot;
)paren
suffix:semicolon
id|__show_regs
c_func
(paren
id|jprobe_saved_regs_location
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;JPROBE: Current registers&bslash;n&quot;
)paren
suffix:semicolon
id|__show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Restore old register state.  Do pt_regs&n;&t;&t; * first so that UREG_FP is the original one for&n;&t;&t; * the stack frame restore.&n;&t;&t; */
id|memcpy
c_func
(paren
id|regs
comma
op_amp
id|jprobe_saved_regs
comma
r_sizeof
(paren
op_star
id|regs
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
op_plus
id|STACK_BIAS
)paren
comma
op_amp
id|jprobe_saved_stack
comma
r_sizeof
(paren
id|jprobe_saved_stack
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
)brace
eof
