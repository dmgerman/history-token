multiline_comment|/* defines for inline arch setup functions */
DECL|function|do_timer_interrupt_hook
r_static
r_inline
r_void
id|do_timer_interrupt_hook
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * In the SMP case we use the local APIC timer interrupt to do the&n; * profiling, except when we simulate SMP mode on a uniprocessor&n; * system, in that case we have to call the local interrupt handler.&n; */
macro_line|#ifndef CONFIG_X86_LOCAL_APIC
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
id|x86_do_profile
c_func
(paren
id|regs-&gt;eip
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|using_apic_timer
)paren
id|smp_local_timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* you can safely undefine this if you don&squot;t have the Neptune chipset */
DECL|macro|BUGGY_NEPTUN_TIMER
mdefine_line|#define BUGGY_NEPTUN_TIMER
DECL|function|do_timer_overflow
r_static
r_inline
r_int
id|do_timer_overflow
c_func
(paren
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is tricky when I/O APICs are used;&n;&t; * see do_timer_interrupt().&n;&t; */
id|i
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i8259A_lock
)paren
suffix:semicolon
multiline_comment|/* assumption about timer being IRQ0 */
r_if
c_cond
(paren
id|i
op_amp
l_int|0x01
)paren
(brace
multiline_comment|/*&n;&t;&t; * We cannot detect lost timer interrupts ... &n;&t;&t; * well, that&squot;s why we call them lost, don&squot;t we? :)&n;&t;&t; * [hmm, on the Pentium and Alpha we can ... sort of]&n;&t;&t; */
id|count
op_sub_assign
id|LATCH
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef BUGGY_NEPTUN_TIMER
multiline_comment|/*&n;&t;&t; * for the Neptun bug we know that the &squot;latch&squot;&n;&t;&t; * command doesnt latch the high and low value&n;&t;&t; * of the counter atomically. Thus we have to &n;&t;&t; * substract 256 from the counter &n;&t;&t; * ... funny, isnt it? :)&n;&t;&t; */
id|count
op_sub_assign
l_int|256
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;do_slow_gettimeoffset(): hardware timer problem?&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|count
suffix:semicolon
)brace
eof
