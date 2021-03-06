multiline_comment|/*&n; * Linux/PA-RISC Project (http://www.parisc-linux.org/)&n; *&n; * Floating-point emulation code&n; *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) &lt;bame@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * BEGIN_DESC&n; *&n; *  File:&n; *&t;@(#)&t;pa/fp/decode_exc.c&t;&t;$ Revision: $&n; *&n; *  Purpose:&n; *&t;&lt;&lt;please update with a synopsis of the functionality provided by this file&gt;&gt;&n; *&n; *  External Interfaces:&n; *&t;&lt;&lt;the following list was autogenerated, please review&gt;&gt;&n; *&t;decode_fpu(Fpu_register, trap_counts)&n; *&n; *  Internal Interfaces:&n; *&t;&lt;&lt;please update&gt;&gt;&n; *&n; *  Theory:&n; *&t;&lt;&lt;please update with a overview of the operation of this file&gt;&gt;&n; *&n; * END_DESC&n;*/
macro_line|#include &quot;float.h&quot;
macro_line|#include &quot;sgl_float.h&quot;
macro_line|#include &quot;dbl_float.h&quot;
macro_line|#include &quot;cnv_float.h&quot;
multiline_comment|/* #include &quot;types.h&quot; */
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/siginfo.h&gt;
multiline_comment|/* #include &lt;machine/sys/mdep_private.h&gt; */
DECL|macro|Fpustatus_register
macro_line|#undef Fpustatus_register
DECL|macro|Fpustatus_register
mdefine_line|#define Fpustatus_register Fpu_register[0]
multiline_comment|/* General definitions */
DECL|macro|DOESTRAP
mdefine_line|#define DOESTRAP 1
DECL|macro|NOTRAP
mdefine_line|#define NOTRAP 0
DECL|macro|SIGNALCODE
mdefine_line|#define SIGNALCODE(signal, code) ((signal) &lt;&lt; 24 | (code));
DECL|macro|copropbit
mdefine_line|#define copropbit&t;1&lt;&lt;31-2&t;/* bit position 2 */
DECL|macro|opclass
mdefine_line|#define opclass&t;&t;9&t;/* bits 21 &amp; 22 */
DECL|macro|fmt
mdefine_line|#define fmt&t;&t;11&t;/* bits 19 &amp; 20 */
DECL|macro|df
mdefine_line|#define df&t;&t;13&t;/* bits 17 &amp; 18 */
DECL|macro|twobits
mdefine_line|#define twobits&t;&t;3&t;/* mask low-order 2 bits */
DECL|macro|fivebits
mdefine_line|#define fivebits&t;31&t;/* mask low-order 5 bits */
DECL|macro|MAX_EXCP_REG
mdefine_line|#define MAX_EXCP_REG&t;7&t;/* number of excpeption registers to check */
multiline_comment|/* Exception register definitions */
DECL|macro|Excp_type
mdefine_line|#define Excp_type(index) Exceptiontype(Fpu_register[index])
DECL|macro|Excp_instr
mdefine_line|#define Excp_instr(index) Instructionfield(Fpu_register[index])
DECL|macro|Clear_excp_register
mdefine_line|#define Clear_excp_register(index) Allexception(Fpu_register[index]) = 0
DECL|macro|Excp_format
mdefine_line|#define Excp_format() &bslash;&n;    (current_ir &gt;&gt; ((current_ir&gt;&gt;opclass &amp; twobits)==1 ? df : fmt) &amp; twobits)
multiline_comment|/* Miscellaneous definitions */
DECL|macro|Fpu_sgl
mdefine_line|#define Fpu_sgl(index) Fpu_register[index*2]
DECL|macro|Fpu_dblp1
mdefine_line|#define Fpu_dblp1(index) Fpu_register[index*2]
DECL|macro|Fpu_dblp2
mdefine_line|#define Fpu_dblp2(index) Fpu_register[(index*2)+1]
DECL|macro|Fpu_quadp1
mdefine_line|#define Fpu_quadp1(index) Fpu_register[index*2]
DECL|macro|Fpu_quadp2
mdefine_line|#define Fpu_quadp2(index) Fpu_register[(index*2)+1]
DECL|macro|Fpu_quadp3
mdefine_line|#define Fpu_quadp3(index) Fpu_register[(index*2)+2]
DECL|macro|Fpu_quadp4
mdefine_line|#define Fpu_quadp4(index) Fpu_register[(index*2)+3]
multiline_comment|/* Single precision floating-point definitions */
macro_line|#ifndef Sgl_decrement
DECL|macro|Sgl_decrement
macro_line|# define Sgl_decrement(sgl_value) Sall(sgl_value)--
macro_line|#endif
multiline_comment|/* Double precision floating-point definitions */
macro_line|#ifndef Dbl_decrement
DECL|macro|Dbl_decrement
macro_line|# define Dbl_decrement(dbl_valuep1,dbl_valuep2) &bslash;&n;    if ((Dallp2(dbl_valuep2)--) == 0) Dallp1(dbl_valuep1)-- 
macro_line|#endif
DECL|macro|update_trap_counts
mdefine_line|#define update_trap_counts(Fpu_register, aflags, bflags, trap_counts) {&t;&bslash;&n;&t;aflags=(Fpu_register[0])&gt;&gt;27;&t;/* assumes zero fill. 32 bit */&t;&bslash;&n;&t;Fpu_register[0] |= bflags;&t;&t;&t;&t;&t;&bslash;&n;}
id|u_int
DECL|function|decode_fpu
id|decode_fpu
c_func
(paren
r_int
r_int
id|Fpu_register
(braket
)braket
comma
r_int
r_int
id|trap_counts
(braket
)braket
)paren
(brace
r_int
r_int
id|current_ir
comma
id|excp
suffix:semicolon
r_int
id|target
comma
id|exception_index
op_assign
l_int|1
suffix:semicolon
id|boolean
id|inexact
suffix:semicolon
r_int
r_int
id|aflags
suffix:semicolon
r_int
r_int
id|bflags
suffix:semicolon
r_int
r_int
id|excptype
suffix:semicolon
multiline_comment|/* Keep stats on how many floating point exceptions (based on type)&n;     * that happen.  Want to keep this overhead low, but still provide&n;     * some information to the customer.  All exits from this routine&n;     * need to restore Fpu_register[0]&n;    */
id|bflags
op_assign
(paren
id|Fpu_register
(braket
l_int|0
)braket
op_amp
l_int|0xf8000000
)paren
suffix:semicolon
id|Fpu_register
(braket
l_int|0
)braket
op_and_assign
l_int|0x07ffffff
suffix:semicolon
multiline_comment|/* exception_index is used to index the exception register queue.  It&n;     *   always points at the last register that contains a valid exception.  A&n;     *   zero value implies no exceptions (also the initialized value).  Setting&n;     *   the T-bit resets the exception_index to zero.&n;     */
multiline_comment|/*&n;     * Check for reserved-op exception.  A reserved-op exception does not &n;     * set any exception registers nor does it set the T-bit.  If the T-bit&n;     * is not set then a reserved-op exception occurred.&n;     *&n;     * At some point, we may want to report reserved op exceptions as&n;     * illegal instructions.&n;     */
r_if
c_cond
(paren
op_logical_neg
id|Is_tbit_set
c_func
(paren
)paren
)paren
(brace
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGILL
comma
id|ILL_COPROC
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;     * Is a coprocessor op. &n;     *&n;     * Now we need to determine what type of exception occurred.&n;     */
r_for
c_loop
(paren
id|exception_index
op_assign
l_int|1
suffix:semicolon
id|exception_index
op_le
id|MAX_EXCP_REG
suffix:semicolon
id|exception_index
op_increment
)paren
(brace
id|current_ir
op_assign
id|Excp_instr
c_func
(paren
id|exception_index
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   * On PA89: there are 5 different unimplemented exception&n;&t;   * codes: 0x1, 0x9, 0xb, 0x3, and 0x23.  PA-RISC 2.0 adds&n;&t;   * another, 0x2b.  Only these have the low order bit set.&n;&t;   */
id|excptype
op_assign
id|Excp_type
c_func
(paren
id|exception_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|excptype
op_amp
id|UNIMPLEMENTEDEXCEPTION
)paren
(brace
multiline_comment|/*&n;&t;&t; * Clear T-bit and exception register so that&n;&t;&t; * we can tell if a trap really occurs while &n;&t;&t; * emulating the instruction.&n;&t;&t; */
id|Clear_tbit
c_func
(paren
)paren
suffix:semicolon
id|Clear_excp_register
c_func
(paren
id|exception_index
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now emulate this instruction.  If a trap occurs,&n;&t;&t; * fpudispatch will return a non-zero number &n;&t;&t; */
id|excp
op_assign
id|fpudispatch
c_func
(paren
id|current_ir
comma
id|excptype
comma
l_int|0
comma
id|Fpu_register
)paren
suffix:semicolon
multiline_comment|/* accumulate the status flags, don&squot;t lose them as in hpux */
r_if
c_cond
(paren
id|excp
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We now need to make sure that the T-bit and the&n;&t;&t;&t; * exception register contain the correct values&n;&t;&t;&t; * before continuing.&n;&t;&t;&t; */
multiline_comment|/*&n;&t;&t;&t; * Set t-bit since it might still be needed for a&n;&t;&t;&t; * subsequent real trap (I don&squot;t understand fully -PB)&n;&t;&t;&t; */
id|Set_tbit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* some of the following code uses&n;&t;&t;&t; * Excp_type(exception_index) so fix that up */
id|Set_exceptiontype_and_instr_field
c_func
(paren
id|excp
comma
id|current_ir
comma
id|Fpu_register
(braket
id|exception_index
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|excp
op_eq
id|UNIMPLEMENTEDEXCEPTION
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; &t; * it is really unimplemented, so restore the&n;&t;&t;&t; &t; * TIMEX extended unimplemented exception code&n;&t;&t;&t; &t; */
id|excp
op_assign
id|excptype
suffix:semicolon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGILL
comma
id|ILL_COPROC
)paren
suffix:semicolon
)brace
multiline_comment|/* some of the following code uses excptype, so&n;&t;&t;&t; * fix that up too */
id|excptype
op_assign
id|excp
suffix:semicolon
)brace
multiline_comment|/* handle exceptions other than the real UNIMPLIMENTED the&n;&t;&t; * same way as if the hardware had caused them */
r_if
c_cond
(paren
id|excp
op_eq
id|NOEXCEPTION
)paren
multiline_comment|/* For now use &squot;break&squot;, should technically be &squot;continue&squot; */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   * In PA89, the underflow exception has been extended to encode&n;&t;   * additional information.  The exception looks like pp01x0,&n;&t;   * where x is 1 if inexact and pp represent the inexact bit (I)&n;&t;   * and the round away bit (RA)&n;&t;   */
r_if
c_cond
(paren
id|excptype
op_amp
id|UNDERFLOWEXCEPTION
)paren
(brace
multiline_comment|/* check for underflow trap enabled */
r_if
c_cond
(paren
id|Is_underflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTUND
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;     * Isn&squot;t a real trap; we need to &n;&t;&t;     * return the default value.&n;&t;&t;     */
id|target
op_assign
id|current_ir
op_amp
id|fivebits
suffix:semicolon
macro_line|#ifndef lint
r_if
c_cond
(paren
id|Ibit
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
)paren
)paren
id|inexact
op_assign
id|TRUE
suffix:semicolon
r_else
id|inexact
op_assign
id|FALSE
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|Excp_format
c_func
(paren
)paren
)paren
(brace
r_case
id|SGL
suffix:colon
multiline_comment|/*&n;&t;&t;         * If ra (round-away) is set, will &n;&t;&t;         * want to undo the rounding done&n;&t;&t;         * by the hardware.&n;&t;&t;         */
r_if
c_cond
(paren
id|Rabit
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
)paren
)paren
id|Sgl_decrement
c_func
(paren
id|Fpu_sgl
c_func
(paren
id|target
)paren
)paren
suffix:semicolon
multiline_comment|/* now denormalize */
id|sgl_denormalize
c_func
(paren
op_amp
id|Fpu_sgl
c_func
(paren
id|target
)paren
comma
op_amp
id|inexact
comma
id|Rounding_mode
c_func
(paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DBL
suffix:colon
multiline_comment|/*&n;&t;&t;    &t; * If ra (round-away) is set, will &n;&t;&t;    &t; * want to undo the rounding done&n;&t;&t;    &t; * by the hardware.&n;&t;&t;    &t; */
r_if
c_cond
(paren
id|Rabit
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
)paren
)paren
id|Dbl_decrement
c_func
(paren
id|Fpu_dblp1
c_func
(paren
id|target
)paren
comma
id|Fpu_dblp2
c_func
(paren
id|target
)paren
)paren
suffix:semicolon
multiline_comment|/* now denormalize */
id|dbl_denormalize
c_func
(paren
op_amp
id|Fpu_dblp1
c_func
(paren
id|target
)paren
comma
op_amp
id|Fpu_dblp2
c_func
(paren
id|target
)paren
comma
op_amp
id|inexact
comma
id|Rounding_mode
c_func
(paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inexact
)paren
id|Set_underflowflag
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t;     * Underflow can generate an inexact&n;&t;&t;     * exception.  If inexact trap is enabled,&n;&t;&t;     * want to do an inexact trap, otherwise &n;&t;&t;     * set inexact flag.&n;&t;&t;     */
r_if
c_cond
(paren
id|inexact
op_logical_and
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;    &t; * Set exception field of exception register&n;&t;&t;    &t; * to inexact, parm field to zero.&n;&t;&t;&t; * Underflow bit should be cleared.&n;&t;&t;    &t; */
id|Set_exceptiontype
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
comma
id|INEXACTEXCEPTION
)paren
suffix:semicolon
id|Set_parmfield
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
comma
l_int|0
)paren
suffix:semicolon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTRES
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;    &t; * Exception register needs to be cleared.  &n;&t;&t;&t; * Inexact flag needs to be set if inexact.&n;&t;&t;    &t; */
id|Clear_excp_register
c_func
(paren
id|exception_index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inexact
)paren
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|Excp_type
c_func
(paren
id|exception_index
)paren
)paren
(brace
r_case
id|OVERFLOWEXCEPTION
suffix:colon
r_case
id|OVERFLOWEXCEPTION
op_or
id|INEXACTEXCEPTION
suffix:colon
multiline_comment|/* check for overflow trap enabled */
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Is_overflowtrap_enabled
c_func
(paren
)paren
)paren
(brace
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTOVF
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Isn&squot;t a real trap; we need to &n;&t;&t;&t; * return the default value.&n;&t;&t;&t; */
id|target
op_assign
id|current_ir
op_amp
id|fivebits
suffix:semicolon
r_switch
c_cond
(paren
id|Excp_format
c_func
(paren
)paren
)paren
(brace
r_case
id|SGL
suffix:colon
id|Sgl_setoverflow
c_func
(paren
id|Fpu_sgl
c_func
(paren
id|target
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DBL
suffix:colon
id|Dbl_setoverflow
c_func
(paren
id|Fpu_dblp1
c_func
(paren
id|target
)paren
comma
id|Fpu_dblp2
c_func
(paren
id|target
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|Set_overflowflag
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * Overflow always generates an inexact&n;&t;&t;&t; * exception.  If inexact trap is enabled,&n;&t;&t;&t; * want to do an inexact trap, otherwise &n;&t;&t;&t; * set inexact flag.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|Is_inexacttrap_enabled
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Set exception field of exception&n;&t;&t;&t;&t; * register to inexact.  Overflow&n;&t;&t;&t;&t; * bit should be cleared.&n;&t;&t;&t;&t; */
id|Set_exceptiontype
c_func
(paren
id|Fpu_register
(braket
id|exception_index
)braket
comma
id|INEXACTEXCEPTION
)paren
suffix:semicolon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTRES
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Exception register needs to be cleared.  &n;&t;&t;&t;&t; * Inexact flag needs to be set.&n;&t;&t;&t;&t; */
id|Clear_excp_register
c_func
(paren
id|exception_index
)paren
suffix:semicolon
id|Set_inexactflag
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|INVALIDEXCEPTION
suffix:colon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTINV
)paren
suffix:semicolon
r_case
id|DIVISIONBYZEROEXCEPTION
suffix:colon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTDIV
)paren
suffix:semicolon
r_case
id|INEXACTEXCEPTION
suffix:colon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGFPE
comma
id|FPE_FLTRES
)paren
suffix:semicolon
r_default
suffix:colon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(%d) Unknown FPU exception 0x%x&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|Excp_type
c_func
(paren
id|exception_index
)paren
)paren
suffix:semicolon
r_return
id|SIGNALCODE
c_func
(paren
id|SIGILL
comma
id|ILL_COPROC
)paren
suffix:semicolon
r_case
id|NOEXCEPTION
suffix:colon
multiline_comment|/* no exception */
multiline_comment|/*&n;&t;&t; * Clear exception register in case &n;&t;&t; * other fields are non-zero.&n;&t;&t; */
id|Clear_excp_register
c_func
(paren
id|exception_index
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     * No real exceptions occurred.&n;     */
id|Clear_tbit
c_func
(paren
)paren
suffix:semicolon
id|update_trap_counts
c_func
(paren
id|Fpu_register
comma
id|aflags
comma
id|bflags
comma
id|trap_counts
)paren
suffix:semicolon
r_return
id|NOTRAP
suffix:semicolon
)brace
eof
