multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999 by Ralf Baechle&n; * Copyright (C) 1995, 1996 Paul M. Antoine&n; * Copyright (C) 1998 Ulf Carlsson&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/watch.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
r_extern
id|asmlinkage
r_void
id|__xtlb_mod
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__xtlb_tlbl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__xtlb_tlbs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_adel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ades
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ibe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_dbe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_sys
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_bp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ri
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ov
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_tr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_fpe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_watch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_reserved
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cpu_names
r_static
r_char
op_star
id|cpu_names
(braket
)braket
op_assign
id|CPU_NAMES
suffix:semicolon
DECL|variable|watch_available
r_char
id|watch_available
op_assign
l_int|0
suffix:semicolon
DECL|variable|dedicated_iv_available
r_char
id|dedicated_iv_available
op_assign
l_int|0
suffix:semicolon
DECL|variable|vce_available
r_char
id|vce_available
op_assign
l_int|0
suffix:semicolon
DECL|variable|mips4_available
r_char
id|mips4_available
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * These constant is for searching for possible module text segments.&n; * MODULE_RANGE is a guess of how much space is likely to be vmalloced.&n; */
DECL|macro|MODULE_RANGE
mdefine_line|#define MODULE_RANGE (8*1024*1024)
multiline_comment|/*&n; * This routine abuses get_user()/put_user() to reference pointers&n; * with at least a bit of error checking ...&n; */
DECL|function|show_stack
r_void
id|show_stack
c_func
(paren
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|stack
suffix:semicolon
id|stack
op_assign
id|sp
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Stack:&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
id|stack
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
(brace
r_int
r_int
id|stackdata
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|stackdata
comma
id|stack
op_increment
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; (Bad stack address)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %016lx&quot;
comma
id|stackdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|i
OG
l_int|40
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; ...&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_mod
l_int|4
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n      &quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|show_trace
r_void
id|show_trace
c_func
(paren
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|stack
suffix:semicolon
r_int
r_int
id|kernel_start
comma
id|kernel_end
suffix:semicolon
r_int
r_int
id|module_start
comma
id|module_end
suffix:semicolon
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
id|stack
op_assign
id|sp
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|kernel_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|kernel_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|module_start
op_assign
id|VMALLOC_START
suffix:semicolon
id|module_end
op_assign
id|module_start
op_plus
id|MODULE_RANGE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nCall Trace:&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
id|stack
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|addr
comma
id|stack
op_increment
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; (Bad stack address)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If the address is either in the text segment of the&n;&t;&t; * kernel, or in the region which contains vmalloc&squot;ed&n;&t;&t; * memory, it *may* be the address of a calling&n;&t;&t; * routine; if so, print it so that someone tracing&n;&t;&t; * down the cause of the crash will be able to figure&n;&t;&t; * out the call path that was taken.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|kernel_start
op_logical_and
id|addr
OL
id|kernel_end
)paren
op_logical_or
(paren
id|addr
op_ge
id|module_start
op_logical_and
id|addr
OL
id|module_end
)paren
)paren
(brace
multiline_comment|/* Since our kernel is still at KSEG0,&n;&t;&t;&t; * truncate the address so that ksymoops&n;&t;&t;&t; * understands it.&n;&t;&t;&t; */
id|printk
c_func
(paren
l_string|&quot; [&lt;%08x&gt;]&quot;
comma
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|i
OG
l_int|40
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; ...&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|show_code
r_void
id|show_code
c_func
(paren
r_int
r_int
op_star
id|pc
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nCode:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|3
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|insn
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|insn
comma
id|pc
op_plus
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; (Bad address in epc)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%c%08x%c&quot;
comma
(paren
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&lt;&squot;
)paren
comma
id|insn
comma
(paren
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&gt;&squot;
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|die_lock
id|spinlock_t
id|die_lock
suffix:semicolon
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|err
)paren
(brace
r_static
r_int
id|die_counter
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
multiline_comment|/* Just return if in user mode.  */
r_return
suffix:semicolon
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %04lx [#%d]&bslash;n&quot;
comma
id|str
comma
id|err
op_amp
l_int|0xffff
comma
op_increment
id|die_counter
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stackpage=%08lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
r_int
r_int
)paren
id|current
)paren
suffix:semicolon
id|show_stack
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
)paren
suffix:semicolon
id|show_trace
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
)paren
suffix:semicolon
id|show_code
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;cp0_epc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|err
)paren
(brace
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
id|die
c_func
(paren
id|str
comma
id|regs
comma
id|err
)paren
suffix:semicolon
)brace
DECL|function|do_ov
r_void
id|do_ov
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
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGFPE
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MIPS_FPE_MODULE
DECL|variable|fpe_handler
r_static
r_void
(paren
op_star
id|fpe_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fcr31
)paren
suffix:semicolon
multiline_comment|/*&n; * Register_fpe/unregister_fpe are for debugging purposes only.  To make&n; * this hack work a bit better there is no error checking.&n; */
DECL|function|register_fpe
r_int
id|register_fpe
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fcr31
)paren
)paren
(brace
id|fpe_handler
op_assign
id|handler
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_fpe
r_int
id|unregister_fpe
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fcr31
)paren
)paren
(brace
id|fpe_handler
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * XXX Delayed fp exceptions when doing a lazy ctx switch XXX&n; */
DECL|function|do_fpe
r_void
id|do_fpe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fcr31
)paren
(brace
r_int
r_int
id|pc
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
r_extern
r_void
id|simfp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS_FPE_MODULE
r_if
c_cond
(paren
id|fpe_handler
op_ne
l_int|NULL
)paren
(brace
id|fpe_handler
c_func
(paren
id|regs
comma
id|fcr31
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|fcr31
op_amp
l_int|0x20000
)paren
(brace
multiline_comment|/* Retry instruction with flush to zero ...  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|fcr31
op_amp
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Setting flush to zero for %s.&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|fcr31
op_and_assign
op_complement
l_int|0x20000
suffix:semicolon
id|fcr31
op_or_assign
(paren
l_int|1
op_lshift
l_int|24
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ctc1&bslash;t%0,$31&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|fcr31
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pc
op_assign
id|regs-&gt;cp0_epc
op_plus
(paren
(paren
id|regs-&gt;cp0_cause
op_amp
id|CAUSEF_BD
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|insn
comma
(paren
r_int
r_int
op_star
)paren
id|pc
)paren
)paren
(brace
multiline_comment|/* XXX Can this happen?  */
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Unimplemented exception for insn %08x at 0x%08lx in %s.&bslash;n&quot;
comma
id|insn
comma
id|regs-&gt;cp0_epc
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|simfp
c_func
(paren
id|insn
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
singleline_comment|//force_sig(SIGFPE, current);
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Should send SIGFPE to %s&bslash;n&quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
)brace
DECL|function|do_bp
r_void
id|do_bp
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
id|opcode
comma
id|bcode
suffix:semicolon
r_int
r_int
op_star
id|epc
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|epc
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;cp0_epc
op_plus
(paren
(paren
id|regs-&gt;cp0_cause
op_amp
id|CAUSEF_BD
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opcode
comma
id|epc
)paren
)paren
r_goto
id|sigsegv
suffix:semicolon
multiline_comment|/*&n;&t; * There is the ancient bug in the MIPS assemblers that the break&n;&t; * code starts left to bit 16 instead to bit 6 in the opcode.&n;&t; * Gas is bug-compatible ...&n;&t; */
id|bcode
op_assign
(paren
(paren
id|opcode
op_rshift
l_int|16
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * (A short test says that IRIX 5.3 sends SIGTRAP for all break&n;&t; * insns, even for break codes that indicate arithmetic failures.&n;&t; * Weird ...)&n;&t; * But should we continue the brokenness???  --macro&n;&t; */
r_switch
c_cond
(paren
id|bcode
)paren
(brace
r_case
l_int|6
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|bcode
op_eq
l_int|7
)paren
id|info.si_code
op_assign
id|FPE_INTDIV
suffix:semicolon
r_else
id|info.si_code
op_assign
id|FPE_INTOVF
suffix:semicolon
id|info.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
id|sigsegv
suffix:colon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_tr
r_void
id|do_tr
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
id|opcode
comma
id|bcode
suffix:semicolon
r_int
r_int
op_star
id|epc
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
id|epc
op_assign
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;cp0_epc
op_plus
(paren
(paren
id|regs-&gt;cp0_cause
op_amp
id|CAUSEF_BD
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|opcode
comma
id|epc
)paren
)paren
r_goto
id|sigsegv
suffix:semicolon
id|bcode
op_assign
(paren
(paren
id|opcode
op_rshift
l_int|6
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * (A short test says that IRIX 5.3 sends SIGTRAP for all break&n;&t; * insns, even for break codes that indicate arithmetic failures.&n;&t; * Wiered ...)&n;&t; * But should we continue the brokenness???  --macro&n;&t; */
r_switch
c_cond
(paren
id|bcode
)paren
(brace
r_case
l_int|6
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|bcode
op_eq
l_int|7
)paren
id|info.si_code
op_assign
id|FPE_INTDIV
suffix:semicolon
r_else
id|info.si_code
op_assign
id|FPE_INTOVF
suffix:semicolon
id|info.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|sigsegv
suffix:colon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_ri
r_void
id|do_ri
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Cpu%d[%s:%d] Illegal instruction at %08lx ra=%08lx&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_cpu
r_void
id|do_cpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|cpid
suffix:semicolon
id|cpid
op_assign
(paren
id|regs-&gt;cp0_cause
op_rshift
id|CAUSEB_CE
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|cpid
op_ne
l_int|1
)paren
r_goto
id|bad_cid
suffix:semicolon
id|regs-&gt;cp0_status
op_or_assign
id|ST0_CU1
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
multiline_comment|/* Using the FPU again.  */
id|lazy_fpu_switch
c_func
(paren
id|last_task_used_math
comma
id|current
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* First time FPU user.  */
id|lazy_fpu_switch
c_func
(paren
id|last_task_used_math
comma
l_int|0
)paren
suffix:semicolon
id|init_fpu
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|last_task_used_math
op_assign
id|current
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
id|lazy_fpu_switch
c_func
(paren
l_int|0
comma
id|current
)paren
suffix:semicolon
)brace
r_else
(brace
id|init_fpu
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
id|current-&gt;flags
op_or_assign
id|PF_USEDFPU
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
id|bad_cid
suffix:colon
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_watch
r_void
id|do_watch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * We use the watch exception where available to detect stack&n;&t; * overflows.&n;&t; */
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Caught WATCH exception - probably caused by stack overflow.&quot;
)paren
suffix:semicolon
)brace
DECL|function|do_reserved
r_void
id|do_reserved
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Game over - no way to handle this if it ever occurs.  Most probably&n;&t; * caused by a new unknown cpu type or after another deadly&n;&t; * hard/software error.&n;&t; */
id|panic
c_func
(paren
l_string|&quot;Caught reserved exception %ld - should not happen.&quot;
comma
(paren
id|regs-&gt;cp0_cause
op_amp
l_int|0x1f
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|watch_init
r_static
r_inline
r_void
id|watch_init
c_func
(paren
r_int
r_int
id|cputype
)paren
(brace
r_switch
c_cond
(paren
id|cputype
)paren
(brace
r_case
id|CPU_R10000
suffix:colon
r_case
id|CPU_R4000MC
suffix:colon
r_case
id|CPU_R4400MC
suffix:colon
r_case
id|CPU_R4000SC
suffix:colon
r_case
id|CPU_R4400SC
suffix:colon
r_case
id|CPU_R4000PC
suffix:colon
r_case
id|CPU_R4400PC
suffix:colon
r_case
id|CPU_R4200
suffix:colon
r_case
id|CPU_R4300
suffix:colon
id|set_except_vector
c_func
(paren
l_int|23
comma
id|handle_watch
)paren
suffix:semicolon
id|watch_available
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Some MIPS CPUs have a dedicated interrupt vector which reduces the&n; * interrupt processing overhead.  Use it where available.&n; * FIXME: more CPUs than just the Nevada have this feature.&n; */
DECL|function|setup_dedicated_int
r_static
r_inline
r_void
id|setup_dedicated_int
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|except_vec4
c_func
(paren
r_void
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mips_cputype
)paren
(brace
r_case
id|CPU_NEVADA
suffix:colon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x200
)paren
comma
id|except_vec4
comma
l_int|8
)paren
suffix:semicolon
id|set_cp0_cause
c_func
(paren
id|CAUSEF_IV
comma
id|CAUSEF_IV
)paren
suffix:semicolon
id|dedicated_iv_available
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|variable|exception_handlers
r_int
r_int
id|exception_handlers
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*&n; * As a side effect of the way this is implemented we&squot;re limited&n; * to interrupt handlers in the address range from&n; * KSEG0 &lt;= x &lt; KSEG0 + 256mb on the Nevada.  Oh well ...&n; */
DECL|function|set_except_vector
r_void
id|set_except_vector
c_func
(paren
r_int
id|n
comma
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|handler
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|exception_handlers
(braket
id|n
)braket
op_assign
id|handler
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
op_logical_and
id|dedicated_iv_available
)paren
(brace
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x200
)paren
op_assign
l_int|0x08000000
op_or
(paren
l_int|0x03ffffff
op_amp
(paren
id|handler
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|KSEG0
op_plus
l_int|0x200
comma
id|KSEG0
op_plus
l_int|0x204
)paren
suffix:semicolon
)brace
)brace
DECL|function|mips4_setup
r_static
r_inline
r_void
id|mips4_setup
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|mips_cputype
)paren
(brace
r_case
id|CPU_R5000
suffix:colon
r_case
id|CPU_R5000A
suffix:colon
r_case
id|CPU_NEVADA
suffix:colon
r_case
id|CPU_R8000
suffix:colon
r_case
id|CPU_R10000
suffix:colon
id|mips4_available
op_assign
l_int|1
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_XX
comma
id|ST0_XX
)paren
suffix:semicolon
)brace
)brace
DECL|function|go_64
r_static
r_inline
r_void
id|go_64
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|bits
suffix:semicolon
id|bits
op_assign
id|ST0_KX
op_or
id|ST0_SX
op_or
id|ST0_UX
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|bits
comma
id|bits
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Entering 64-bit mode.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|trap_init
r_void
id|__init
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|except_vec0
suffix:semicolon
r_extern
r_char
id|except_vec1_r10k
suffix:semicolon
r_extern
r_char
id|except_vec2_generic
suffix:semicolon
r_extern
r_char
id|except_vec3_generic
comma
id|except_vec3_r4000
suffix:semicolon
r_extern
r_void
id|bus_error_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Some firmware leaves the BEV flag set, clear it.  */
id|set_cp0_status
c_func
(paren
id|ST0_BEV
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Copy the generic exception handler code to its final destination. */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x100
)paren
comma
op_amp
id|except_vec2_generic
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x180
)paren
comma
op_amp
id|except_vec3_generic
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup default vectors&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|31
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_except_vector
c_func
(paren
id|i
comma
id|handle_reserved
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Only some CPUs have the watch exceptions or a dedicated&n;&t; * interrupt vector.&n;&t; */
id|watch_init
c_func
(paren
id|mips_cputype
)paren
suffix:semicolon
id|setup_dedicated_int
c_func
(paren
)paren
suffix:semicolon
id|mips4_setup
c_func
(paren
)paren
suffix:semicolon
id|go_64
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* In memoriam C128 ;-)  */
multiline_comment|/*&n;&t; * Handling the following exceptions depends mostly of the cpu type&n;&t; */
r_switch
c_cond
(paren
id|mips_cputype
)paren
(brace
r_case
id|CPU_R10000
suffix:colon
multiline_comment|/*&n;&t;&t; * The R10000 is in most aspects similar to the R4400.  It&n;&t;&t; * should get some special optimizations.&n;&t;&t; */
id|write_32bit_cp0_register
c_func
(paren
id|CP0_FRAMEMASK
comma
l_int|0
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_XX
comma
id|ST0_XX
)paren
suffix:semicolon
r_goto
id|r4k
suffix:semicolon
r_case
id|CPU_R4000MC
suffix:colon
r_case
id|CPU_R4400MC
suffix:colon
r_case
id|CPU_R4000SC
suffix:colon
r_case
id|CPU_R4400SC
suffix:colon
id|vce_available
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Fall through ...  */
r_case
id|CPU_R4000PC
suffix:colon
r_case
id|CPU_R4400PC
suffix:colon
r_case
id|CPU_R4200
suffix:colon
r_case
id|CPU_R4300
suffix:colon
r_case
id|CPU_R4600
suffix:colon
r_case
id|CPU_R5000
suffix:colon
r_case
id|CPU_NEVADA
suffix:colon
id|r4k
suffix:colon
multiline_comment|/* Debug TLB refill handler.  */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
op_plus
l_int|0x080
comma
op_amp
id|except_vec1_r10k
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Cache error vector  */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x100
)paren
comma
(paren
r_void
op_star
)paren
id|KSEG0
comma
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vce_available
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x180
)paren
comma
op_amp
id|except_vec3_r4000
comma
l_int|0x180
)paren
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x180
)paren
comma
op_amp
id|except_vec3_generic
comma
l_int|0x100
)paren
suffix:semicolon
)brace
id|set_except_vector
c_func
(paren
l_int|1
comma
id|__xtlb_mod
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|2
comma
id|__xtlb_tlbl
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|3
comma
id|__xtlb_tlbs
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|4
comma
id|handle_adel
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|5
comma
id|handle_ades
)paren
suffix:semicolon
multiline_comment|/* DBE / IBE exception handler are system specific.  */
id|bus_error_init
c_func
(paren
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|8
comma
id|handle_sys
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|9
comma
id|handle_bp
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|10
comma
id|handle_ri
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|11
comma
id|handle_cpu
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|12
comma
id|handle_ov
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|13
comma
id|handle_tr
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|15
comma
id|handle_fpe
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_R8000
suffix:colon
id|panic
c_func
(paren
l_string|&quot;unsupported CPU type %s.&bslash;n&quot;
comma
id|cpu_names
(braket
id|mips_cputype
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_UNKNOWN
suffix:colon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown CPU type&quot;
)paren
suffix:semicolon
)brace
id|flush_icache_range
c_func
(paren
id|KSEG0
comma
id|KSEG0
op_plus
l_int|0x200
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
multiline_comment|/* XXX UP?  */
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
)brace
eof
