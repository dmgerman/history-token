multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 97, 2000, 2001 by Ralf Baechle&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/cpu-features.h&gt;
macro_line|#include &lt;asm/inst.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Compute the return address and do emulate branch simulation, if required.&n; */
DECL|function|__compute_return_epc
r_int
id|__compute_return_epc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
op_star
id|addr
comma
id|bit
comma
id|fcr31
suffix:semicolon
r_int
id|epc
suffix:semicolon
r_union
id|mips_instruction
id|insn
suffix:semicolon
id|epc
op_assign
id|regs-&gt;cp0_epc
suffix:semicolon
r_if
c_cond
(paren
id|epc
op_amp
l_int|3
)paren
r_goto
id|unaligned
suffix:semicolon
multiline_comment|/*&n;&t; * Read the instruction&n;&t; */
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|epc
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|insn.word
comma
id|addr
)paren
)paren
(brace
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
id|EFAULT
suffix:semicolon
)brace
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|insn.i_format.opcode
)paren
(brace
multiline_comment|/*&n;&t; * jr and jalr are in r_format format.&n;&t; */
r_case
id|spec_op
suffix:colon
r_switch
c_cond
(paren
id|insn.r_format.func
)paren
(brace
r_case
id|jalr_op
suffix:colon
id|regs-&gt;regs
(braket
id|insn.r_format.rd
)braket
op_assign
id|epc
op_plus
l_int|8
suffix:semicolon
multiline_comment|/* Fall through */
r_case
id|jr_op
suffix:colon
id|regs-&gt;cp0_epc
op_assign
id|regs-&gt;regs
(braket
id|insn.r_format.rs
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * This group contains:&n;&t; * bltz_op, bgez_op, bltzl_op, bgezl_op,&n;&t; * bltzal_op, bgezal_op, bltzall_op, bgezall_op.&n;&t; */
r_case
id|bcond_op
suffix:colon
r_switch
c_cond
(paren
id|insn.i_format.rt
)paren
(brace
r_case
id|bltz_op
suffix:colon
r_case
id|bltzl_op
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
OL
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|bgez_op
suffix:colon
r_case
id|bgezl_op
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
op_ge
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|bltzal_op
suffix:colon
r_case
id|bltzall_op
suffix:colon
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
id|epc
op_plus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
OL
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|bgezal_op
suffix:colon
r_case
id|bgezall_op
suffix:colon
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
id|epc
op_plus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
op_ge
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * These are unconditional and in j_format.&n;&t; */
r_case
id|jal_op
suffix:colon
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
id|regs-&gt;cp0_epc
op_plus
l_int|8
suffix:semicolon
r_case
id|j_op
suffix:colon
id|epc
op_add_assign
l_int|4
suffix:semicolon
id|epc
op_rshift_assign
l_int|28
suffix:semicolon
id|epc
op_lshift_assign
l_int|28
suffix:semicolon
id|epc
op_or_assign
(paren
id|insn.j_format.target
op_lshift
l_int|2
)paren
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * These are conditional and in i_format.&n;&t; */
r_case
id|beq_op
suffix:colon
r_case
id|beql_op
suffix:colon
r_if
c_cond
(paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
op_eq
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|bne_op
suffix:colon
r_case
id|bnel_op
suffix:colon
r_if
c_cond
(paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
op_ne
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|blez_op
suffix:colon
multiline_comment|/* not really i_format */
r_case
id|blezl_op
suffix:colon
multiline_comment|/* rt field assumed to be zero */
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
op_le
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
id|bgtz_op
suffix:colon
r_case
id|bgtzl_op
suffix:colon
multiline_comment|/* rt field assumed to be zero */
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;regs
(braket
id|insn.i_format.rs
)braket
OG
l_int|0
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * And now the FPA/cp1 branch instructions.&n;&t; */
r_case
id|cop1_op
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_fpu
)paren
id|fcr31
op_assign
id|current-&gt;thread.fpu.soft.fcr31
suffix:semicolon
r_else
id|asm
r_volatile
(paren
l_string|&quot;cfc1&bslash;t%0,$31&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fcr31
)paren
)paren
suffix:semicolon
id|bit
op_assign
(paren
id|insn.i_format.rt
op_rshift
l_int|2
)paren
suffix:semicolon
id|bit
op_add_assign
(paren
id|bit
op_ne
l_int|0
)paren
suffix:semicolon
id|bit
op_add_assign
l_int|23
suffix:semicolon
r_switch
c_cond
(paren
id|insn.i_format.rt
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* bc1f */
r_case
l_int|2
suffix:colon
multiline_comment|/* bc1fl */
r_if
c_cond
(paren
op_complement
id|fcr31
op_amp
(paren
l_int|1
op_lshift
id|bit
)paren
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* bc1t */
r_case
l_int|3
suffix:colon
multiline_comment|/* bc1tl */
r_if
c_cond
(paren
id|fcr31
op_amp
(paren
l_int|1
op_lshift
id|bit
)paren
)paren
id|epc
op_assign
id|epc
op_plus
l_int|4
op_plus
(paren
id|insn.i_format.simmediate
op_lshift
l_int|2
)paren
suffix:semicolon
r_else
id|epc
op_add_assign
l_int|8
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|unaligned
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: unaligned epc - sending SIGBUS.&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGBUS
comma
id|current
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
eof
