multiline_comment|/*&n; *  Emulation of the &quot;brl&quot; instruction for IA64 processors that&n; *  don&squot;t support it in hardware.&n; *  Author: Stephan Zeisset, Intel Corp. &lt;Stephan.Zeisset@intel.com&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
r_extern
r_char
id|ia64_set_b1
comma
id|ia64_set_b2
comma
id|ia64_set_b3
comma
id|ia64_set_b4
comma
id|ia64_set_b5
suffix:semicolon
DECL|struct|illegal_op_return
r_struct
id|illegal_op_return
(brace
DECL|member|fkt
DECL|member|arg1
DECL|member|arg2
DECL|member|arg3
r_int
r_int
id|fkt
comma
id|arg1
comma
id|arg2
comma
id|arg3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  The unimplemented bits of a virtual address must be set&n; *  to the value of the most significant implemented bit.&n; *  unimpl_va_mask includes all unimplemented bits and&n; *  the most significant implemented bit, so the result&n; *  of an and operation with the mask must be all 0&squot;s&n; *  or all 1&squot;s for the address to be valid.&n; */
DECL|macro|unimplemented_virtual_address
mdefine_line|#define unimplemented_virtual_address(va) (&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((va) &amp; local_cpu_data-&gt;unimpl_va_mask) != 0 &amp;&amp;&t;&t;&t;&t;&t;&bslash;&n;&t;((va) &amp; local_cpu_data-&gt;unimpl_va_mask) != local_cpu_data-&gt;unimpl_va_mask&t;&bslash;&n;)
multiline_comment|/*&n; *  The unimplemented bits of a physical address must be 0.&n; *  unimpl_pa_mask includes all unimplemented bits, so the result&n; *  of an and operation with the mask must be all 0&squot;s for the&n; *  address to be valid.&n; */
DECL|macro|unimplemented_physical_address
mdefine_line|#define unimplemented_physical_address(pa) (&t;&t;&bslash;&n;&t;((pa) &amp; local_cpu_data-&gt;unimpl_pa_mask) != 0&t;&bslash;&n;)
multiline_comment|/*&n; *  Handle an illegal operation fault that was caused by an&n; *  unimplemented &quot;brl&quot; instruction.&n; *  If we are not successful (e.g because the illegal operation&n; *  wasn&squot;t caused by a &quot;brl&quot; after all), we return -1.&n; *  If we are successful, we return either 0 or the address&n; *  of a &quot;fixup&quot; function for manipulating preserved register&n; *  state.&n; */
r_struct
id|illegal_op_return
DECL|function|ia64_emulate_brl
id|ia64_emulate_brl
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|ar_ec
)paren
(brace
r_int
r_int
id|bundle
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|opcode
comma
id|btype
comma
id|qp
comma
id|offset
suffix:semicolon
r_int
r_int
id|next_ip
suffix:semicolon
r_struct
id|siginfo
id|siginfo
suffix:semicolon
r_struct
id|illegal_op_return
id|rv
suffix:semicolon
r_int
id|tmp_taken
comma
id|unimplemented_address
suffix:semicolon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *  Decode the instruction bundle.&n;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|bundle
comma
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;cr_iip
)paren
comma
r_sizeof
(paren
id|bundle
)paren
)paren
)paren
r_return
id|rv
suffix:semicolon
id|next_ip
op_assign
(paren
r_int
r_int
)paren
id|regs-&gt;cr_iip
op_plus
l_int|16
suffix:semicolon
multiline_comment|/* &quot;brl&quot; must be in slot 2. */
r_if
c_cond
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_ne
l_int|1
)paren
r_return
id|rv
suffix:semicolon
multiline_comment|/* Must be &quot;mlx&quot; template */
r_if
c_cond
(paren
(paren
id|bundle
(braket
l_int|0
)braket
op_amp
l_int|0x1e
)paren
op_ne
l_int|0x4
)paren
r_return
id|rv
suffix:semicolon
id|opcode
op_assign
(paren
id|bundle
(braket
l_int|1
)braket
op_rshift
l_int|60
)paren
suffix:semicolon
id|btype
op_assign
(paren
(paren
id|bundle
(braket
l_int|1
)braket
op_rshift
l_int|29
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|qp
op_assign
(paren
(paren
id|bundle
(braket
l_int|1
)braket
op_rshift
l_int|23
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|offset
op_assign
(paren
(paren
id|bundle
(braket
l_int|1
)braket
op_amp
l_int|0x0800000000000000L
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|bundle
(braket
l_int|1
)braket
op_amp
l_int|0x00fffff000000000L
)paren
op_rshift
l_int|32
)paren
op_or
(paren
(paren
id|bundle
(braket
l_int|1
)braket
op_amp
l_int|0x00000000007fffffL
)paren
op_lshift
l_int|40
)paren
op_or
(paren
(paren
id|bundle
(braket
l_int|0
)braket
op_amp
l_int|0xffff000000000000L
)paren
op_rshift
l_int|24
)paren
suffix:semicolon
id|tmp_taken
op_assign
id|regs-&gt;pr
op_amp
(paren
l_int|1L
op_lshift
id|qp
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
l_int|0xC
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  Long Branch.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|btype
op_ne
l_int|0
)paren
r_return
id|rv
suffix:semicolon
id|rv.fkt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp_taken
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; *  Qualifying predicate is 0.&n;&t;&t;&t;&t; *  Skip instruction.&n;&t;&t;&t;&t; */
id|regs-&gt;cr_iip
op_assign
id|next_ip
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0xD
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  Long Call.&n;&t;&t;&t; */
id|rv.fkt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp_taken
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; *  Qualifying predicate is 0.&n;&t;&t;&t;&t; *  Skip instruction.&n;&t;&t;&t;&t; */
id|regs-&gt;cr_iip
op_assign
id|next_ip
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *  BR[btype] = IP+16&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|btype
)paren
(brace
r_case
l_int|0
suffix:colon
id|regs-&gt;b0
op_assign
id|next_ip
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_set_b1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_set_b2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_set_b3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_set_b4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|rv.fkt
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ia64_set_b5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|regs-&gt;b6
op_assign
id|next_ip
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|regs-&gt;b7
op_assign
id|next_ip
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rv.arg1
op_assign
id|next_ip
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  AR[PFS].pfm = CFM&n;&t;&t;&t; *  AR[PFS].pec = AR[EC]&n;&t;&t;&t; *  AR[PFS].ppl = PSR.cpl&n;&t;&t;&t; */
id|regs-&gt;ar_pfs
op_assign
(paren
(paren
id|regs-&gt;cr_ifs
op_amp
l_int|0x3fffffffff
)paren
op_or
(paren
id|ar_ec
op_lshift
l_int|52
)paren
op_or
(paren
(paren
r_int
r_int
)paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|cpl
op_lshift
l_int|62
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  CFM.sof -= CFM.sol&n;&t;&t;&t; *  CFM.sol = 0&n;&t;&t;&t; *  CFM.sor = 0&n;&t;&t;&t; *  CFM.rrb.gr = 0&n;&t;&t;&t; *  CFM.rrb.fr = 0&n;&t;&t;&t; *  CFM.rrb.pr = 0&n;&t;&t;&t; */
id|regs-&gt;cr_ifs
op_assign
(paren
(paren
id|regs-&gt;cr_ifs
op_amp
l_int|0xffffffc00000007f
)paren
op_minus
(paren
(paren
id|regs-&gt;cr_ifs
op_rshift
l_int|7
)paren
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; *  Unknown opcode.&n;&t;&t;&t; */
r_return
id|rv
suffix:semicolon
)brace
id|regs-&gt;cr_iip
op_add_assign
id|offset
suffix:semicolon
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|it
op_eq
l_int|0
)paren
id|unimplemented_address
op_assign
id|unimplemented_physical_address
c_func
(paren
id|regs-&gt;cr_iip
)paren
suffix:semicolon
r_else
id|unimplemented_address
op_assign
id|unimplemented_virtual_address
c_func
(paren
id|regs-&gt;cr_iip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unimplemented_address
)paren
(brace
multiline_comment|/*&n;&t;&t; *  The target address contains unimplemented bits.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;Woah! Unimplemented Instruction Address Trap!&bslash;n&quot;
)paren
suffix:semicolon
id|siginfo.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|ILL_BADIADDR
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|tb
)paren
(brace
multiline_comment|/*&n;&t;&t; *  Branch Tracing is enabled.&n;&t;&t; *  Force a taken branch signal.&n;&t;&t; */
id|siginfo.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|TRAP_BRANCH
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ia64_psr
c_func
(paren
id|regs
)paren
op_member_access_from_pointer
id|ss
)paren
(brace
multiline_comment|/*&n;&t;&t; *  Single Step is enabled.&n;&t;&t; *  Force a trace signal.&n;&t;&t; */
id|siginfo.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|siginfo.si_errno
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|TRAP_TRACE
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
r_return
id|rv
suffix:semicolon
)brace
eof
