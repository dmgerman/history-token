multiline_comment|/*&n; *  Kernel Probes (KProbes)&n; *  arch/ppc64/kernel/kprobes.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2002, 2004&n; *&n; * 2002-Oct&t;Created by Vamsi Krishna S &lt;vamsi_krishna@in.ibm.com&gt; Kernel&n; *&t;&t;Probes initial implementation ( includes contributions from&n; *&t;&t;Rusty Russell).&n; * 2004-July&t;Suparna Bhattacharya &lt;suparna@in.ibm.com&gt; added jumper probes&n; *&t;&t;interface to access function arguments.&n; * 2004-Nov&t;Ananth N Mavinakayanahalli &lt;ananth@in.ibm.com&gt; kprobes port&n; *&t;&t;for PPC64&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kprobes.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/sstep.h&gt;
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
DECL|variable|kprobe_saved_msr
r_static
r_int
r_int
id|kprobe_status
comma
id|kprobe_saved_msr
suffix:semicolon
DECL|variable|jprobe_saved_regs
r_static
r_struct
id|pt_regs
id|jprobe_saved_regs
suffix:semicolon
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
id|kprobe_opcode_t
id|insn
op_assign
op_star
id|p-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|IS_MTMSRD
c_func
(paren
id|insn
)paren
op_logical_or
id|IS_RFID
c_func
(paren
id|insn
)paren
)paren
multiline_comment|/* cannot put bp on RFID/MTMSRD */
r_return
l_int|1
suffix:semicolon
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
id|regs-&gt;nip
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
id|regs-&gt;msr
op_or_assign
id|MSR_SE
suffix:semicolon
multiline_comment|/*single step inline if it a breakpoint instruction*/
r_if
c_cond
(paren
id|p-&gt;opcode
op_eq
id|BREAKPOINT_INSTRUCTION
)paren
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
r_else
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|p-&gt;ainsn.insn
suffix:semicolon
)brace
DECL|function|kprobe_handler
r_static
r_inline
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
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;nip
suffix:semicolon
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
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SE
suffix:semicolon
id|regs-&gt;msr
op_or_assign
id|kprobe_saved_msr
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
op_star
id|addr
op_ne
id|BREAKPOINT_INSTRUCTION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * PowerPC has multiple variants of the &quot;trap&quot;&n;&t;&t;&t; * instruction. If the current instruction is a&n;&t;&t;&t; * trap variant, it could belong to someone else&n;&t;&t;&t; */
id|kprobe_opcode_t
id|cur_insn
op_assign
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|IS_TW
c_func
(paren
id|cur_insn
)paren
op_logical_or
id|IS_TD
c_func
(paren
id|cur_insn
)paren
op_logical_or
id|IS_TWI
c_func
(paren
id|cur_insn
)paren
op_logical_or
id|IS_TDI
c_func
(paren
id|cur_insn
)paren
)paren
r_goto
id|no_kprobe
suffix:semicolon
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
id|kprobe_saved_msr
op_assign
id|regs-&gt;msr
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
multiline_comment|/*&n;&t; * This preempt_disable() matches the preempt_enable_no_resched()&n;&t; * in post_kprobe_handler().&n;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|no_kprobe
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Called after single-stepping.  p-&gt;addr is the address of the&n; * instruction whose first byte has been replaced by the &quot;breakpoint&quot;&n; * instruction.  To avoid the SMP problems that can occur when we&n; * temporarily put back the original opcode to single-step, we&n; * single-stepped a copy of the instruction.  The address of this&n; * copy is p-&gt;ainsn.insn.&n; */
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
id|ret
suffix:semicolon
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
suffix:semicolon
id|ret
op_assign
id|emulate_step
c_func
(paren
id|regs
comma
id|p-&gt;ainsn.insn
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;addr
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SE
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
id|regs-&gt;msr
op_or_assign
id|kprobe_saved_msr
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
multiline_comment|/*&n;&t; * if somebody else is singlestepping across a probe point, msr&n;&t; * will have SE set, in which case, continue the remaining processing&n;&t; * of do_debug, as if this is not a probe hit.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_SE
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
id|regs-&gt;msr
op_or_assign
id|kprobe_saved_msr
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
r_int
id|ret
op_assign
id|NOTIFY_DONE
suffix:semicolon
multiline_comment|/*&n;&t; * Interrupts are not disabled here.  We need to disable&n;&t; * preemption, because kprobe_running() uses smp_processor_id().&n;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
)paren
(brace
r_case
id|DIE_IABR_MATCH
suffix:colon
r_case
id|DIE_DABR_MATCH
suffix:colon
r_case
id|DIE_BPT
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
id|ret
op_assign
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIE_SSTEP
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
id|ret
op_assign
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIE_GPF
suffix:colon
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
id|ret
op_assign
id|NOTIFY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
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
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
multiline_comment|/* setup return addr to the jprobe handler routine */
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
(paren
id|func_descr_t
op_star
)paren
id|jp-&gt;entry
)paren
op_member_access_from_pointer
id|entry
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
(paren
id|func_descr_t
op_star
)paren
id|jp-&gt;entry
)paren
op_member_access_from_pointer
id|toc
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
id|asm
r_volatile
(paren
l_string|&quot;trap&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|jprobe_return_end
r_void
id|jprobe_return_end
c_func
(paren
r_void
)paren
(brace
)brace
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
multiline_comment|/*&n;&t; * FIXME - we should ideally be validating that we got here &squot;cos&n;&t; * of the &quot;trap&quot; in jprobe_return() above, before restoring the&n;&t; * saved regs...&n;&t; */
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
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
