multiline_comment|/*&n; * Handle unaligned accesses by emulation.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1998, 1999, 2002 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; *&n; * This file contains exception handler for address error exception with the&n; * special capability to execute faulting instructions in software.  The&n; * handler does not try to handle the case when the program counter points&n; * to an address not aligned to a word boundary.&n; *&n; * Putting data to unaligned addresses is a bad practice even on Intel where&n; * only the performance is affected.  Much worse is that such code is non-&n; * portable.  Due to several programs that die on MIPS due to alignment&n; * problems I decided to implement this handler anyway though I originally&n; * didn&squot;t intend to do this at all for user code.&n; *&n; * For now I enable fixing of address errors by default to make life easier.&n; * I however intend to disable this somewhen in the future when the alignment&n; * problems with user programs have been fixed.  For programmers this is the&n; * right way to go.&n; *&n; * Fixing address errors is a per process option.  The option is inherited&n; * across fork(2) and execve(2) calls.  If you really want to use the&n; * option in your user programs - I discourage the use of the software&n; * emulation strongly - use the following code in your userland stuff:&n; *&n; * #include &lt;sys/sysmips.h&gt;&n; *&n; * ...&n; * sysmips(MIPS_FIXADE, x);&n; * ...&n; *&n; * The argument x is 0 for disabling software emulation, enabled otherwise.&n; *&n; * Below a little program to play around with this feature.&n; *&n; * #include &lt;stdio.h&gt;&n; * #include &lt;sys/sysmips.h&gt;&n; *&n; * struct foo {&n; *         unsigned char bar[8];&n; * };&n; *&n; * main(int argc, char *argv[])&n; * {&n; *         struct foo x = {0, 1, 2, 3, 4, 5, 6, 7};&n; *         unsigned int *p = (unsigned int *) (x.bar + 3);&n; *         int i;&n; *&n; *         if (argc &gt; 1)&n; *                 sysmips(MIPS_FIXADE, atoi(argv[1]));&n; *&n; *         printf(&quot;*p = %08lx&bslash;n&quot;, *p);&n; *&n; *         *p = 0xdeadface;&n; *&n; *         for(i = 0; i &lt;= 7; i++)&n; *         printf(&quot;%02x &quot;, x.bar[i]);&n; *         printf(&quot;&bslash;n&quot;);&n; * }&n; *&n; * Coprocessor loads are not supported; I think this case is unimportant&n; * in the practice.&n; *&n; * TODO: Handle ndc (attempted store to doubleword in uncached memory)&n; *       exception for the R6000.&n; *       A store crossing a page boundary might be executed only partially.&n; *       Undo the partial store in this case.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/inst.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|STR
mdefine_line|#define STR(x)  __STR(x)
DECL|macro|__STR
mdefine_line|#define __STR(x)  #x
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|unaligned_instructions
r_int
r_int
id|unaligned_instructions
suffix:semicolon
macro_line|#endif
DECL|function|emulate_load_store_insn
r_static
r_inline
r_int
id|emulate_load_store_insn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|pc
comma
r_int
r_int
op_star
op_star
id|regptr
comma
r_int
r_int
op_star
id|newvalue
)paren
(brace
r_union
id|mips_instruction
id|insn
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_int
r_int
id|res
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|regptr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * This load never faults.&n;&t; */
id|__get_user
c_func
(paren
id|insn.word
comma
(paren
r_int
r_int
op_star
)paren
id|pc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|insn.i_format.opcode
)paren
(brace
multiline_comment|/*&n;&t; * These are instructions that a compiler doesn&squot;t generate.  We&n;&t; * can assume therefore that the code is MIPS-aware and&n;&t; * really buggy.  Emulating these instructions would break the&n;&t; * semantics anyway.&n;&t; */
r_case
id|ll_op
suffix:colon
r_case
id|lld_op
suffix:colon
r_case
id|sc_op
suffix:colon
r_case
id|scd_op
suffix:colon
multiline_comment|/*&n;&t; * For these instructions the only way to create an address&n;&t; * error is an attempted access to kernel/supervisor address&n;&t; * space.&n;&t; */
r_case
id|ldl_op
suffix:colon
r_case
id|ldr_op
suffix:colon
r_case
id|lwl_op
suffix:colon
r_case
id|lwr_op
suffix:colon
r_case
id|sdl_op
suffix:colon
r_case
id|sdr_op
suffix:colon
r_case
id|swl_op
suffix:colon
r_case
id|swr_op
suffix:colon
r_case
id|lb_op
suffix:colon
r_case
id|lbu_op
suffix:colon
r_case
id|sb_op
suffix:colon
r_goto
id|sigbus
suffix:semicolon
multiline_comment|/*&n;&t; * The remaining opcodes are the ones that are really of interest.&n;&t; */
r_case
id|lh_op
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|addr
comma
l_int|2
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tlb&bslash;t%0, 0(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlbu&bslash;t$1, 1(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tlb&bslash;t%0, 1(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlbu&bslash;t$1, 0(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;sll&bslash;t%0, 0x8&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%1, 0&bslash;n&quot;
l_string|&quot;3:&bslash;t.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
op_star
id|newvalue
op_assign
id|value
suffix:semicolon
op_star
id|regptr
op_assign
op_amp
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|lw_op
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|addr
comma
l_int|4
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tlwl&bslash;t%0, (%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlwr&bslash;t%0, 3(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tlwl&bslash;t%0, 3(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlwr&bslash;t%0, (%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;li&bslash;t%1, 0&bslash;n&quot;
l_string|&quot;3:&bslash;t.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
op_star
id|newvalue
op_assign
id|value
suffix:semicolon
op_star
id|regptr
op_assign
op_amp
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|lhu_op
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|addr
comma
l_int|2
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tlbu&bslash;t%0, 0(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlbu&bslash;t$1, 1(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tlbu&bslash;t%0, 1(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlbu&bslash;t$1, 0(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;sll&bslash;t%0, 0x8&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%1, 0&bslash;n&quot;
l_string|&quot;3:&bslash;t.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
op_star
id|newvalue
op_assign
id|value
suffix:semicolon
op_star
id|regptr
op_assign
op_amp
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|lwu_op
suffix:colon
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n;&t;&t; * A 32-bit kernel might be running on a 64-bit processor.  But&n;&t;&t; * if we&squot;re on a 32-bit processor and an i-cache incoherency&n;&t;&t; * or race makes us see a 64-bit instruction here the sdl/sdr&n;&t;&t; * would blow up, so for now we don&squot;t handle unaligned 64-bit&n;&t;&t; * instructions on 32-bit kernels.&n;&t;&t; */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|addr
comma
l_int|4
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tlwl&bslash;t%0, (%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlwr&bslash;t%0, 3(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tlwl&bslash;t%0, 3(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tlwr&bslash;t%0, (%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;dsll&bslash;t%0, %0, 32&bslash;n&bslash;t&quot;
l_string|&quot;dsrl&bslash;t%0, %0, 32&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t%1, 0&bslash;n&quot;
l_string|&quot;3:&bslash;t.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
op_star
id|newvalue
op_assign
id|value
suffix:semicolon
op_star
id|regptr
op_assign
op_amp
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/* Cannot handle 64-bit instructions in 32-bit kernel */
r_goto
id|sigill
suffix:semicolon
r_case
id|ld_op
suffix:colon
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n;&t;&t; * A 32-bit kernel might be running on a 64-bit processor.  But&n;&t;&t; * if we&squot;re on a 32-bit processor and an i-cache incoherency&n;&t;&t; * or race makes us see a 64-bit instruction here the sdl/sdr&n;&t;&t; * would blow up, so for now we don&squot;t handle unaligned 64-bit&n;&t;&t; * instructions on 32-bit kernels.&n;&t;&t; */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|addr
comma
l_int|8
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tldl&bslash;t%0, (%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tldr&bslash;t%0, 7(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tldl&bslash;t%0, 7(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tldr&bslash;t%0, (%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;li&bslash;t%1, 0&bslash;n&quot;
l_string|&quot;3:&bslash;t.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%1, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
op_star
id|newvalue
op_assign
id|value
suffix:semicolon
op_star
id|regptr
op_assign
op_amp
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/* Cannot handle 64-bit instructions in 32-bit kernel */
r_goto
id|sigill
suffix:semicolon
r_case
id|sh_op
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|addr
comma
l_int|2
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|value
op_assign
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tsb&bslash;t%1, 1(%2)&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t$1, %1, 0x8&bslash;n&quot;
l_string|&quot;2:&bslash;tsb&bslash;t$1, 0(%2)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;.set&bslash;tnoat&bslash;n&quot;
l_string|&quot;1:&bslash;tsb&bslash;t%1, 0(%2)&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t$1,%1, 0x8&bslash;n&quot;
l_string|&quot;2:&bslash;tsb&bslash;t$1, 1(%2)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;li&bslash;t%0, 0&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sw_op
suffix:colon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|addr
comma
l_int|4
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|value
op_assign
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tswl&bslash;t%1,(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tswr&bslash;t%1, 3(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tswl&bslash;t%1, 3(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tswr&bslash;t%1, (%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;li&bslash;t%0, 0&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sd_op
suffix:colon
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n;&t;&t; * A 32-bit kernel might be running on a 64-bit processor.  But&n;&t;&t; * if we&squot;re on a 32-bit processor and an i-cache incoherency&n;&t;&t; * or race makes us see a 64-bit instruction here the sdl/sdr&n;&t;&t; * would blow up, so for now we don&squot;t handle unaligned 64-bit&n;&t;&t; * instructions on 32-bit kernels.&n;&t;&t; */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|addr
comma
l_int|8
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|value
op_assign
id|regs-&gt;regs
(braket
id|insn.i_format.rt
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
macro_line|#ifdef __BIG_ENDIAN
l_string|&quot;1:&bslash;tsdl&bslash;t%1,(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tsdr&bslash;t%1, 7(%2)&bslash;n&bslash;t&quot;
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
l_string|&quot;1:&bslash;tsdl&bslash;t%1, 7(%2)&bslash;n&quot;
l_string|&quot;2:&bslash;tsdr&bslash;t%1, (%2)&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;li&bslash;t%0, 0&bslash;n&quot;
l_string|&quot;3:&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&bslash;t&quot;
l_string|&quot;4:&bslash;tli&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;t3b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b, 4b&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t2b, 4b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EFAULT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
r_goto
id|fault
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/* Cannot handle 64-bit instructions in 32-bit kernel */
r_goto
id|sigill
suffix:semicolon
r_case
id|lwc1_op
suffix:colon
r_case
id|ldc1_op
suffix:colon
r_case
id|swc1_op
suffix:colon
r_case
id|sdc1_op
suffix:colon
multiline_comment|/*&n;&t;&t; * I herewith declare: this does not happen.  So send SIGBUS.&n;&t;&t; */
r_goto
id|sigbus
suffix:semicolon
r_case
id|lwc2_op
suffix:colon
r_case
id|ldc2_op
suffix:colon
r_case
id|swc2_op
suffix:colon
r_case
id|sdc2_op
suffix:colon
multiline_comment|/*&n;&t;&t; * These are the coprocessor 2 load/stores.  The current&n;&t;&t; * implementations don&squot;t use cp2 and cp2 should always be&n;&t;&t; * disabled in c0_status.  So send SIGILL.&n;                 * (No longer true: The Sony Praystation uses cp2 for&n;                 * 3D matrix operations.  Dunno if that thingy has a MMU ...)&n;&t;&t; */
r_default
suffix:colon
multiline_comment|/*&n;&t;&t; * Pheeee...  We encountered an yet unknown instruction or&n;&t;&t; * cache coherence problem.  Die sucker, die ...&n;&t;&t; */
r_goto
id|sigill
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
id|unaligned_instructions
op_increment
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|fault
suffix:colon
multiline_comment|/* Did we have an exception handler installed? */
r_if
c_cond
(paren
id|fixup_exception
c_func
(paren
id|regs
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|die_if_kernel
(paren
l_string|&quot;Unhandled kernel unaligned access&quot;
comma
id|regs
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|sigbus
suffix:colon
id|die_if_kernel
c_func
(paren
l_string|&quot;Unhandled kernel unaligned access&quot;
comma
id|regs
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGBUS
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|sigill
suffix:colon
id|die_if_kernel
c_func
(paren
l_string|&quot;Unhandled kernel unaligned access or invalid instruction&quot;
comma
id|regs
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_ade
id|asmlinkage
r_void
id|do_ade
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
id|regptr
comma
id|newval
suffix:semicolon
r_extern
r_int
id|do_dsemulret
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
id|mm_segment_t
id|seg
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/*&n;&t; * Address errors may be deliberately induced by the FPU emulator to&n;&t; * retake control of the CPU after executing the instruction in the&n;&t; * delay slot of an emulated branch.&n;&t; */
multiline_comment|/* Terminate if exception was recognized as a delay slot return */
r_if
c_cond
(paren
id|do_dsemulret
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Otherwise handle as normal */
multiline_comment|/*&n;&t; * Did we catch a fault trying to load an instruction?&n;&t; * Or are we running in MIPS16 mode?&n;&t; */
r_if
c_cond
(paren
(paren
id|regs-&gt;cp0_badvaddr
op_eq
id|regs-&gt;cp0_epc
)paren
op_logical_or
(paren
id|regs-&gt;cp0_epc
op_amp
l_int|0x1
)paren
)paren
r_goto
id|sigbus
suffix:semicolon
id|pc
op_assign
id|exception_epc
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_FIXADE
)paren
op_eq
l_int|0
)paren
r_goto
id|sigbus
suffix:semicolon
multiline_comment|/*&n;&t; * Do branch emulation only if we didn&squot;t forward the exception.&n;&t; * This is all so but ugly ...&n;&t; */
id|seg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|emulate_load_store_insn
c_func
(paren
id|regs
comma
(paren
r_void
op_star
)paren
id|regs-&gt;cp0_badvaddr
comma
id|pc
comma
op_amp
id|regptr
comma
op_amp
id|newval
)paren
)paren
(brace
id|compute_return_epc
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Now that branch is evaluated, update the dest&n;&t;&t; * register if necessary&n;&t;&t; */
r_if
c_cond
(paren
id|regptr
)paren
op_star
id|regptr
op_assign
id|newval
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|seg
)paren
suffix:semicolon
r_return
suffix:semicolon
id|sigbus
suffix:colon
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel unaligned instruction access&quot;
comma
id|regs
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
multiline_comment|/*&n;&t; * XXX On return from the signal handler we should advance the epc&n;&t; */
)brace
eof
