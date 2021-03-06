multiline_comment|/*&n; *  Kernel Probes (KProbes)&n; *  arch/i386/kernel/kprobes.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2002, 2004&n; *&n; * 2002-Oct&t;Created by Vamsi Krishna S &lt;vamsi_krishna@in.ibm.com&gt; Kernel&n; *&t;&t;Probes initial implementation ( includes contributions from&n; *&t;&t;Rusty Russell).&n; * 2004-July&t;Suparna Bhattacharya &lt;suparna@in.ibm.com&gt; added jumper probes&n; *&t;&t;interface to access function arguments.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kprobes.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
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
DECL|variable|kprobe_status
DECL|variable|kprobe_old_eflags
DECL|variable|kprobe_saved_eflags
r_static
r_int
r_int
id|kprobe_status
comma
id|kprobe_old_eflags
comma
id|kprobe_saved_eflags
suffix:semicolon
DECL|variable|jprobe_saved_regs
r_static
r_struct
id|pt_regs
id|jprobe_saved_regs
suffix:semicolon
DECL|variable|jprobe_saved_esp
r_static
r_int
op_star
id|jprobe_saved_esp
suffix:semicolon
multiline_comment|/* copy of the kernel stack at the probe fire time */
DECL|variable|jprobes_stack
r_static
id|kprobe_opcode_t
id|jprobes_stack
(braket
id|MAX_STACK_SIZE
)braket
suffix:semicolon
r_void
id|jprobe_return_end
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * returns non-zero if opcode modifies the interrupt flag.&n; */
DECL|function|is_IF_modifier
r_static
r_inline
r_int
id|is_IF_modifier
c_func
(paren
id|kprobe_opcode_t
id|opcode
)paren
(brace
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
l_int|0xfa
suffix:colon
multiline_comment|/* cli */
r_case
l_int|0xfb
suffix:colon
multiline_comment|/* sti */
r_case
l_int|0xcf
suffix:colon
multiline_comment|/* iret/iretd */
r_case
l_int|0x9d
suffix:colon
multiline_comment|/* popf/popfd */
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|memcpy
c_func
(paren
id|p-&gt;ainsn.insn
comma
id|p-&gt;addr
comma
id|MAX_INSN_SIZE
op_star
r_sizeof
(paren
id|kprobe_opcode_t
)paren
)paren
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
id|regs-&gt;eip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
)brace
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
id|regs-&gt;eflags
op_or_assign
id|TF_MASK
suffix:semicolon
id|regs-&gt;eflags
op_and_assign
op_complement
id|IF_MASK
suffix:semicolon
multiline_comment|/*single step inline if the instruction is an int3*/
r_if
c_cond
(paren
id|p-&gt;opcode
op_eq
id|BREAKPOINT_INSTRUCTION
)paren
id|regs-&gt;eip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
r_else
id|regs-&gt;eip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupts are disabled on entry as trap3 is an interrupt gate and they&n; * remain disabled thorough out this function.&n; */
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|kprobe_opcode_t
op_star
id|addr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
op_star
id|lp
suffix:semicolon
multiline_comment|/* We&squot;re in an interrupt, but this is clear and BUG()-safe. */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Check if the application is using LDT entry for its code segment and&n;&t; * calculate the address by reading the base address from the LDT entry.&n;&t; */
r_if
c_cond
(paren
(paren
id|regs-&gt;xcs
op_amp
l_int|4
)paren
op_logical_and
(paren
id|current-&gt;mm
)paren
)paren
(brace
id|lp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_int
r_int
)paren
(paren
(paren
id|regs-&gt;xcs
op_rshift
l_int|3
)paren
op_star
l_int|8
)paren
op_plus
(paren
r_char
op_star
)paren
id|current-&gt;mm-&gt;context.ldt
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|kprobe_opcode_t
op_star
)paren
(paren
id|get_desc_base
c_func
(paren
id|lp
)paren
op_plus
id|regs-&gt;eip
op_minus
r_sizeof
(paren
id|kprobe_opcode_t
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|addr
op_assign
(paren
id|kprobe_opcode_t
op_star
)paren
(paren
id|regs-&gt;eip
op_minus
r_sizeof
(paren
id|kprobe_opcode_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Check we&squot;re not actually recursing */
r_if
c_cond
(paren
id|kprobe_running
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* We *are* holding lock here, so this is safe.&n;&t;&t;   Disarm the probe we just hit, and ignore it. */
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
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
id|regs-&gt;eflags
op_or_assign
id|kprobe_saved_eflags
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
(brace
r_goto
id|ss_probe
suffix:semicolon
)brace
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
id|regs-&gt;eflags
op_amp
id|VM_MASK
)paren
(brace
multiline_comment|/* We are in virtual-8086 mode. Return 0 */
r_goto
id|no_kprobe
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
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
id|kprobe_saved_eflags
op_assign
id|kprobe_old_eflags
op_assign
(paren
id|regs-&gt;eflags
op_amp
(paren
id|TF_MASK
op_or
id|IF_MASK
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_IF_modifier
c_func
(paren
id|p-&gt;opcode
)paren
)paren
id|kprobe_saved_eflags
op_and_assign
op_complement
id|IF_MASK
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
multiline_comment|/* handler has already set things up, so skip ss setup */
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
multiline_comment|/*&n; * Called after single-stepping.  p-&gt;addr is the address of the&n; * instruction whose first byte has been replaced by the &quot;int 3&quot;&n; * instruction.  To avoid the SMP problems that can occur when we&n; * temporarily put back the original opcode to single-step, we&n; * single-stepped a copy of the instruction.  The address of this&n; * copy is p-&gt;ainsn.insn.&n; *&n; * This function prepares to return from the post-single-step&n; * interrupt.  We have to fix up the stack as follows:&n; *&n; * 0) Except in the case of absolute or indirect jump or call instructions,&n; * the new eip is relative to the copied instruction.  We need to make&n; * it relative to the original instruction.&n; *&n; * 1) If the single-stepped instruction was pushfl, then the TF and IF&n; * flags are set in the just-pushed eflags, and may need to be cleared.&n; *&n; * 2) If the single-stepped instruction was a call, the return address&n; * that is atop the stack is the address following the copied instruction.&n; * We need to make it the address following the original instruction.&n; */
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
r_int
r_int
op_star
id|tos
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|regs-&gt;esp
suffix:semicolon
r_int
r_int
id|next_eip
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|copy_eip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
suffix:semicolon
r_int
r_int
id|orig_eip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
)paren
(brace
r_case
l_int|0x9c
suffix:colon
multiline_comment|/* pushfl */
op_star
id|tos
op_and_assign
op_complement
(paren
id|TF_MASK
op_or
id|IF_MASK
)paren
suffix:semicolon
op_star
id|tos
op_or_assign
id|kprobe_old_eflags
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe8
suffix:colon
multiline_comment|/* call relative - Fix return addr */
op_star
id|tos
op_assign
id|orig_eip
op_plus
(paren
op_star
id|tos
op_minus
id|copy_eip
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xff
suffix:colon
r_if
c_cond
(paren
(paren
id|p-&gt;ainsn.insn
(braket
l_int|1
)braket
op_amp
l_int|0x30
)paren
op_eq
l_int|0x10
)paren
(brace
multiline_comment|/* call absolute, indirect */
multiline_comment|/* Fix return addr; eip is correct. */
id|next_eip
op_assign
id|regs-&gt;eip
suffix:semicolon
op_star
id|tos
op_assign
id|orig_eip
op_plus
(paren
op_star
id|tos
op_minus
id|copy_eip
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
id|p-&gt;ainsn.insn
(braket
l_int|1
)braket
op_amp
l_int|0x31
)paren
op_eq
l_int|0x20
)paren
op_logical_or
multiline_comment|/* jmp near, absolute indirect */
(paren
(paren
id|p-&gt;ainsn.insn
(braket
l_int|1
)braket
op_amp
l_int|0x31
)paren
op_eq
l_int|0x21
)paren
)paren
(brace
multiline_comment|/* jmp far, absolute indirect */
multiline_comment|/* eip is correct. */
id|next_eip
op_assign
id|regs-&gt;eip
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0xea
suffix:colon
multiline_comment|/* jmp absolute -- eip is correct */
id|next_eip
op_assign
id|regs-&gt;eip
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|regs-&gt;eflags
op_and_assign
op_complement
id|TF_MASK
suffix:semicolon
r_if
c_cond
(paren
id|next_eip
)paren
(brace
id|regs-&gt;eip
op_assign
id|next_eip
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;eip
op_assign
id|orig_eip
op_plus
(paren
id|regs-&gt;eip
op_minus
id|copy_eip
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Interrupts are disabled on entry as trap1 is an interrupt gate and they&n; * remain disabled thoroughout this function.  And we hold kprobe lock.&n; */
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
id|regs-&gt;eflags
op_or_assign
id|kprobe_saved_eflags
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
multiline_comment|/*&n;&t; * if somebody else is singlestepping across a probe point, eflags&n;&t; * will have TF set, in which case, continue the remaining processing&n;&t; * of do_debug, as if this is not a probe hit.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|TF_MASK
)paren
r_return
l_int|0
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
id|regs-&gt;eflags
op_or_assign
id|kprobe_old_eflags
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
id|DIE_INT3
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
id|DIE_DEBUG
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
r_int
r_int
id|addr
suffix:semicolon
id|jprobe_saved_regs
op_assign
op_star
id|regs
suffix:semicolon
id|jprobe_saved_esp
op_assign
op_amp
id|regs-&gt;esp
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|jprobe_saved_esp
suffix:semicolon
multiline_comment|/*&n;&t; * TBD: As Linus pointed out, gcc assumes that the callee&n;&t; * owns the argument space and could overwrite it, e.g.&n;&t; * tailcall optimization. So, to be absolutely safe&n;&t; * we also save and restore enough stack bytes to cover&n;&t; * the argument area.&n;&t; */
id|memcpy
c_func
(paren
id|jprobes_stack
comma
(paren
id|kprobe_opcode_t
op_star
)paren
id|addr
comma
id|MIN_STACK_SIZE
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|regs-&gt;eflags
op_and_assign
op_complement
id|IF_MASK
suffix:semicolon
id|regs-&gt;eip
op_assign
(paren
r_int
r_int
)paren
(paren
id|jp-&gt;entry
)paren
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
id|asm
r_volatile
(paren
l_string|&quot;       xchgl   %%ebx,%%esp     &bslash;n&quot;
l_string|&quot;       int3&t;&t;&t;&bslash;n&quot;
l_string|&quot;       .globl jprobe_return_end&t;&bslash;n&quot;
l_string|&quot;       jprobe_return_end:&t;&bslash;n&quot;
l_string|&quot;       nop&t;&t;&t;&bslash;n&quot;
op_scope_resolution
l_string|&quot;b&quot;
(paren
id|jprobe_saved_esp
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
id|u8
op_star
id|addr
op_assign
(paren
id|u8
op_star
)paren
(paren
id|regs-&gt;eip
op_minus
l_int|1
)paren
suffix:semicolon
r_int
r_int
id|stack_addr
op_assign
(paren
r_int
r_int
)paren
id|jprobe_saved_esp
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|addr
OG
(paren
id|u8
op_star
)paren
id|jprobe_return
)paren
op_logical_and
(paren
id|addr
OL
(paren
id|u8
op_star
)paren
id|jprobe_return_end
)paren
)paren
(brace
r_if
c_cond
(paren
op_amp
id|regs-&gt;esp
op_ne
id|jprobe_saved_esp
)paren
(brace
r_struct
id|pt_regs
op_star
id|saved_regs
op_assign
id|container_of
c_func
(paren
id|jprobe_saved_esp
comma
r_struct
id|pt_regs
comma
id|esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;current esp %p does not match saved esp %p&bslash;n&quot;
comma
op_amp
id|regs-&gt;esp
comma
id|jprobe_saved_esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Saved registers for jprobe %p&bslash;n&quot;
comma
id|jp
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|saved_regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Current registers&bslash;n&quot;
)paren
suffix:semicolon
id|show_registers
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
op_star
id|regs
op_assign
id|jprobe_saved_regs
suffix:semicolon
id|memcpy
c_func
(paren
(paren
id|kprobe_opcode_t
op_star
)paren
id|stack_addr
comma
id|jprobes_stack
comma
id|MIN_STACK_SIZE
c_func
(paren
id|stack_addr
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
