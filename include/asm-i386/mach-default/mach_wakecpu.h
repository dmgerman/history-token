macro_line|#ifndef __ASM_MACH_WAKECPU_H
DECL|macro|__ASM_MACH_WAKECPU_H
mdefine_line|#define __ASM_MACH_WAKECPU_H
multiline_comment|/* &n; * This file copes with machines that wakeup secondary CPUs by the&n; * INIT, INIT, STARTUP sequence.&n; */
DECL|macro|WAKE_SECONDARY_VIA_INIT
mdefine_line|#define WAKE_SECONDARY_VIA_INIT
DECL|macro|TRAMPOLINE_LOW
mdefine_line|#define TRAMPOLINE_LOW phys_to_virt(0x467)
DECL|macro|TRAMPOLINE_HIGH
mdefine_line|#define TRAMPOLINE_HIGH phys_to_virt(0x469)
DECL|macro|boot_cpu_apicid
mdefine_line|#define boot_cpu_apicid boot_cpu_physical_apicid
DECL|function|wait_for_init_deassert
r_static
r_inline
r_void
id|wait_for_init_deassert
c_func
(paren
id|atomic_t
op_star
id|deassert
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
id|deassert
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Nothing to do for most platforms, since cleared by the INIT cycle */
DECL|function|smp_callin_clear_local_apic
r_static
r_inline
r_void
id|smp_callin_clear_local_apic
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|store_NMI_vector
r_static
r_inline
r_void
id|store_NMI_vector
c_func
(paren
r_int
r_int
op_star
id|high
comma
r_int
r_int
op_star
id|low
)paren
(brace
)brace
DECL|function|restore_NMI_vector
r_static
r_inline
r_void
id|restore_NMI_vector
c_func
(paren
r_int
r_int
op_star
id|high
comma
r_int
r_int
op_star
id|low
)paren
(brace
)brace
macro_line|#if APIC_DEBUG
DECL|macro|inquire_remote_apic
mdefine_line|#define inquire_remote_apic(apicid) __inquire_remote_apic(apicid)
macro_line|#else
DECL|macro|inquire_remote_apic
mdefine_line|#define inquire_remote_apic(apicid) {}
macro_line|#endif
macro_line|#endif /* __ASM_MACH_WAKECPU_H */
eof
