multiline_comment|/*&n; * This file is designed to contain the BUILD_INTERRUPT specifications for&n; * all of the extra named interrupt vectors used by the architecture.&n; * Usually this is the Inter Process Interrupts (IPIs)&n; */
multiline_comment|/*&n; * The following vectors are part of the Linux architecture, there&n; * is no hardware IRQ pin equivalent for them, they are triggered&n; * through the ICC by us (IPIs)&n; */
macro_line|#ifdef CONFIG_X86_SMP
id|BUILD_INTERRUPT
c_func
(paren
id|reschedule_interrupt
comma
id|RESCHEDULE_VECTOR
)paren
id|BUILD_INTERRUPT
c_func
(paren
id|invalidate_interrupt
comma
id|INVALIDATE_TLB_VECTOR
)paren
id|BUILD_INTERRUPT
c_func
(paren
id|call_function_interrupt
comma
id|CALL_FUNCTION_VECTOR
)paren
macro_line|#endif
multiline_comment|/*&n; * every pentium local APIC has two &squot;local interrupts&squot;, with a&n; * soft-definable vector attached to both interrupts, one of&n; * which is a timer interrupt, the other one is error counter&n; * overflow. Linux uses the local APIC timer interrupt to get&n; * a much simpler SMP time architecture:&n; */
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|BUILD_INTERRUPT
c_func
(paren
id|apic_timer_interrupt
comma
id|LOCAL_TIMER_VECTOR
)paren
id|BUILD_INTERRUPT
c_func
(paren
id|error_interrupt
comma
id|ERROR_APIC_VECTOR
)paren
id|BUILD_INTERRUPT
c_func
(paren
id|spurious_interrupt
comma
id|SPURIOUS_APIC_VECTOR
)paren
macro_line|#ifdef CONFIG_X86_MCE_P4THERMAL
id|BUILD_INTERRUPT
c_func
(paren
id|thermal_interrupt
comma
id|THERMAL_APIC_VECTOR
)paren
macro_line|#endif
macro_line|#endif
eof
