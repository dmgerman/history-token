macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
DECL|function|calculate_ldr
r_static
r_inline
r_int
r_int
id|calculate_ldr
c_func
(paren
r_int
r_int
id|old
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
id|id
op_assign
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|old
op_amp
op_complement
id|APIC_LDR_MASK
)paren
op_or
id|SET_APIC_LOGICAL_ID
c_func
(paren
id|id
)paren
)paren
suffix:semicolon
)brace
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_FLAT)
macro_line|#ifdef CONFIG_SMP
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS (clustered_apic_mode ? 0xf : cpu_online_map)
macro_line|#else
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS 0x01
macro_line|#endif
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID      0x0F
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid) (bitmap &amp; (1 &lt;&lt; apicid))
DECL|function|summit_check
r_static
r_inline
r_void
id|summit_check
c_func
(paren
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
(brace
)brace
DECL|function|clustered_apic_check
r_static
r_inline
r_void
id|clustered_apic_check
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Enabling APIC mode:  %s.  Using %d I/O APICs&bslash;n&quot;
comma
(paren
id|clustered_apic_mode
ques
c_cond
l_string|&quot;NUMA-Q&quot;
suffix:colon
l_string|&quot;Flat&quot;
)paren
comma
id|nr_ioapics
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
