macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/inst.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/fpu_emulator.h&gt;
macro_line|#include &quot;ieee754.h&quot;
macro_line|#include &quot;dsemul.h&quot;
multiline_comment|/* Strap kernel emulator for full MIPS IV emulation */
macro_line|#ifdef __mips
DECL|macro|__mips
macro_line|#undef __mips
macro_line|#endif
DECL|macro|__mips
mdefine_line|#define __mips 4
r_extern
r_struct
id|mips_fpu_emulator_private
id|fpuemuprivate
suffix:semicolon
multiline_comment|/*&n; * Emulate the arbritrary instruction ir at xcp-&gt;cp0_epc.  Required when&n; * we have to emulate the instruction in a COP1 branch delay slot.  Do&n; * not change cp0_epc due to the instruction&n; *&n; * According to the spec:&n; * 1) it shouldnt be a branch :-)&n; * 2) it can be a COP instruction :-(&n; * 3) if we are tring to run a protected memory space we must take&n; *    special care on memory access instructions :-(&n; */
multiline_comment|/*&n; * &quot;Trampoline&quot; return routine to catch exception following&n; *  execution of delay-slot instruction execution.&n; */
DECL|struct|emuframe
r_struct
id|emuframe
(brace
DECL|member|emul
id|mips_instruction
id|emul
suffix:semicolon
DECL|member|badinst
id|mips_instruction
id|badinst
suffix:semicolon
DECL|member|cookie
id|mips_instruction
id|cookie
suffix:semicolon
DECL|member|epc
id|gpreg_t
id|epc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mips_dsemul
r_int
id|mips_dsemul
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|mips_instruction
id|ir
comma
id|gpreg_t
id|cpc
)paren
(brace
r_extern
id|asmlinkage
r_void
id|handle_dsemulret
c_func
(paren
r_void
)paren
suffix:semicolon
id|mips_instruction
op_star
id|dsemul_insns
suffix:semicolon
r_struct
id|emuframe
op_star
id|fr
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|ir
op_eq
l_int|0
)paren
(brace
multiline_comment|/* a nop is easy */
id|regs-&gt;cp0_epc
op_assign
id|cpc
suffix:semicolon
id|regs-&gt;cp0_cause
op_and_assign
op_complement
id|CAUSEF_BD
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DSEMUL_TRACE
id|printk
c_func
(paren
l_string|&quot;dsemul %lx %lx&bslash;n&quot;
comma
id|regs-&gt;cp0_epc
comma
id|cpc
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * The strategy is to push the instruction onto the user stack&n;&t; * and put a trap after it which we can catch and jump to&n;&t; * the required address any alternative apart from full&n;&t; * instruction emulation!!.&n;&t; *&n;&t; * Algorithmics used a system call instruction, and&n;&t; * borrowed that vector.  MIPS/Linux version is a bit&n;&t; * more heavyweight in the interests of portability and&n;&t; * multiprocessor support.  For Linux we generate a&n;&t; * an unaligned access and force an address error exception.&n;&t; *&n;&t; * For embedded systems (stand-alone) we prefer to use a&n;&t; * non-existing CP1 instruction. This prevents us from emulating&n;&t; * branches, but gives us a cleaner interface to the exception&n;&t; * handler (single entry point).&n;&t; */
multiline_comment|/* Ensure that the two instructions are in the same cache line */
id|dsemul_insns
op_assign
(paren
id|mips_instruction
op_star
)paren
id|REG_TO_VA
(paren
(paren
id|regs-&gt;regs
(braket
l_int|29
)braket
op_minus
r_sizeof
(paren
r_struct
id|emuframe
)paren
)paren
op_amp
op_complement
l_int|0x7
)paren
suffix:semicolon
id|fr
op_assign
(paren
r_struct
id|emuframe
op_star
)paren
id|dsemul_insns
suffix:semicolon
multiline_comment|/* Verify that the stack pointer is not competely insane */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|fr
comma
r_sizeof
(paren
r_struct
id|emuframe
)paren
)paren
)paren
)paren
r_return
id|SIGBUS
suffix:semicolon
id|err
op_assign
id|__put_user
c_func
(paren
id|ir
comma
op_amp
id|fr-&gt;emul
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|mips_instruction
)paren
id|BADINST
comma
op_amp
id|fr-&gt;badinst
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
id|mips_instruction
)paren
id|BD_COOKIE
comma
op_amp
id|fr-&gt;cookie
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|cpc
comma
op_amp
id|fr-&gt;epc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
)paren
)paren
(brace
id|fpuemuprivate.stats.errors
op_increment
suffix:semicolon
r_return
id|SIGBUS
suffix:semicolon
)brace
id|regs-&gt;cp0_epc
op_assign
id|VA_TO_REG
op_amp
id|fr-&gt;emul
suffix:semicolon
id|flush_cache_sigtramp
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|fr-&gt;badinst
)paren
suffix:semicolon
r_return
id|SIGILL
suffix:semicolon
multiline_comment|/* force out of emulation loop */
)brace
DECL|function|do_dsemulret
r_int
id|do_dsemulret
c_func
(paren
r_struct
id|pt_regs
op_star
id|xcp
)paren
(brace
r_struct
id|emuframe
op_star
id|fr
suffix:semicolon
id|gpreg_t
id|epc
suffix:semicolon
id|u32
id|insn
comma
id|cookie
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|fr
op_assign
(paren
r_struct
id|emuframe
op_star
)paren
(paren
id|xcp-&gt;cp0_epc
op_minus
r_sizeof
(paren
id|mips_instruction
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we can&squot;t even access the area, something is very wrong, but we&squot;ll&n;&t; * leave that to the default handling&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|fr
comma
r_sizeof
(paren
r_struct
id|emuframe
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Do some sanity checking on the stackframe:&n;&t; *&n;&t; *  - Is the instruction pointed to by the EPC an BADINST?&n;&t; *  - Is the following memory word the BD_COOKIE?&n;&t; */
id|err
op_assign
id|__get_user
c_func
(paren
id|insn
comma
op_amp
id|fr-&gt;badinst
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|cookie
comma
op_amp
id|fr-&gt;cookie
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
op_logical_or
(paren
id|insn
op_ne
id|BADINST
)paren
op_logical_or
(paren
id|cookie
op_ne
id|BD_COOKIE
)paren
)paren
)paren
(brace
id|fpuemuprivate.stats.errors
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * At this point, we are satisfied that it&squot;s a BD emulation trap.  Yes,&n;&t; * a user might have deliberately put two malformed and useless&n;&t; * instructions in a row in his program, in which case he&squot;s in for a&n;&t; * nasty surprise - the next instruction will be treated as a&n;&t; * continuation address!  Alas, this seems to be the only way that we&n;&t; * can handle signals, recursion, and longjmps() in the context of&n;&t; * emulating the branch delay instruction.&n;&t; */
macro_line|#ifdef DSEMUL_TRACE
id|printk
c_func
(paren
l_string|&quot;dsemulret&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|epc
comma
op_amp
id|fr-&gt;epc
)paren
)paren
(brace
multiline_comment|/* Saved EPC */
multiline_comment|/* This is not a good situation to be in */
id|force_sig
c_func
(paren
id|SIGBUS
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set EPC to return to post-branch instruction */
id|xcp-&gt;cp0_epc
op_assign
id|epc
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
