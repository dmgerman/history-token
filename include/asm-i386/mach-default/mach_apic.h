macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_FLAT)
macro_line|#ifdef CONFIG_SMP
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS (cpu_online_map)
macro_line|#else
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS 0x01
macro_line|#endif
DECL|macro|no_balance_irq
mdefine_line|#define no_balance_irq (0)
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID      0x0F
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid) (bitmap &amp; (1 &lt;&lt; apicid))
DECL|function|apic_id_registered
r_static
r_inline
r_int
id|apic_id_registered
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|test_bit
c_func
(paren
id|GET_APIC_ID
c_func
(paren
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
comma
op_amp
id|phys_cpu_present_map
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the logical destination ID.&n; *&n; * Intel recommends to set DFR, LDR and TPR before enabling&n; * an APIC.  See e.g. &quot;AP-388 82489DX User&squot;s Manual&quot; (Intel&n; * document number 292116).  So here it goes...&n; */
DECL|function|init_apic_ldr
r_static
r_inline
r_void
id|init_apic_ldr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_DFR
comma
id|APIC_DFR_VALUE
)paren
suffix:semicolon
id|val
op_assign
id|apic_read
c_func
(paren
id|APIC_LDR
)paren
op_amp
op_complement
id|APIC_LDR_MASK
suffix:semicolon
id|val
op_or_assign
id|SET_APIC_LOGICAL_ID
c_func
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_LDR
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|ioapic_phys_id_map
r_static
r_inline
id|ulong
id|ioapic_phys_id_map
c_func
(paren
id|ulong
id|phys_map
)paren
(brace
r_return
id|phys_map
suffix:semicolon
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
l_string|&quot;Flat&quot;
comma
id|nr_ioapics
)paren
suffix:semicolon
)brace
DECL|function|multi_timer_check
r_static
r_inline
r_int
id|multi_timer_check
c_func
(paren
r_int
id|apic
comma
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|apicid_to_node
r_static
r_inline
r_int
id|apicid_to_node
c_func
(paren
r_int
id|logical_apicid
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpu_present_to_apicid
r_static
r_inline
r_int
id|cpu_present_to_apicid
c_func
(paren
r_int
id|mps_cpu
)paren
(brace
r_return
id|mps_cpu
suffix:semicolon
)brace
DECL|function|apicid_to_cpu_present
r_static
r_inline
r_int
r_int
id|apicid_to_cpu_present
c_func
(paren
r_int
id|phys_apicid
)paren
(brace
r_return
(paren
l_int|1ul
op_lshift
id|phys_apicid
)paren
suffix:semicolon
)brace
DECL|function|mpc_apic_id
r_static
r_inline
r_int
id|mpc_apic_id
c_func
(paren
r_struct
id|mpc_config_processor
op_star
id|m
comma
r_int
id|quad
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Processor #%d %ld:%ld APIC version %d&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
comma
(paren
id|m-&gt;mpc_cpufeature
op_amp
id|CPU_FAMILY_MASK
)paren
op_rshift
l_int|8
comma
(paren
id|m-&gt;mpc_cpufeature
op_amp
id|CPU_MODEL_MASK
)paren
op_rshift
l_int|4
comma
id|m-&gt;mpc_apicver
)paren
suffix:semicolon
r_return
(paren
id|m-&gt;mpc_apicid
)paren
suffix:semicolon
)brace
DECL|macro|WAKE_SECONDARY_VIA_INIT
mdefine_line|#define WAKE_SECONDARY_VIA_INIT
DECL|function|setup_portio_remap
r_static
r_inline
r_void
id|setup_portio_remap
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
