macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_FLAT)
DECL|function|target_cpus
r_static
r_inline
r_int
r_int
id|target_cpus
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_return
id|cpu_online_map
suffix:semicolon
macro_line|#else
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS (target_cpus())
DECL|macro|NO_BALANCE_IRQ
mdefine_line|#define NO_BALANCE_IRQ (0)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (0)
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE dest_LowestPrio
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE 1     /* logical delivery broadcast to all procs */
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID      0x0F
DECL|function|check_apicid_used
r_static
r_inline
r_int
r_int
id|check_apicid_used
c_func
(paren
r_int
r_int
id|bitmap
comma
r_int
id|apicid
)paren
(brace
r_return
(paren
id|bitmap
op_amp
(paren
l_int|1UL
op_lshift
id|apicid
)paren
)paren
suffix:semicolon
)brace
DECL|function|check_apicid_present
r_static
r_inline
r_int
r_int
id|check_apicid_present
c_func
(paren
r_int
id|bit
)paren
(brace
r_return
(paren
id|phys_cpu_present_map
op_amp
(paren
l_int|1UL
op_lshift
id|bit
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
r_int
r_int
id|ioapic_phys_id_map
c_func
(paren
r_int
r_int
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
multiline_comment|/* Mapping from cpu number to logical apicid */
DECL|function|cpu_to_logical_apicid
r_static
r_inline
r_int
id|cpu_to_logical_apicid
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
l_int|1
op_lshift
id|cpu
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
r_struct
id|mpc_config_translation
op_star
id|translation_record
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
DECL|function|check_phys_apicid_present
r_static
r_inline
r_int
id|check_phys_apicid_present
c_func
(paren
r_int
id|boot_cpu_physical_apicid
)paren
(brace
r_return
id|test_bit
c_func
(paren
id|boot_cpu_physical_apicid
comma
op_amp
id|phys_cpu_present_map
)paren
suffix:semicolon
)brace
DECL|macro|APIC_ID_MASK
mdefine_line|#define&t;&t;APIC_ID_MASK&t;&t;(0xF&lt;&lt;24)
DECL|function|get_apic_id
r_static
r_inline
r_int
id|get_apic_id
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
(paren
(paren
(paren
id|x
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xF
)paren
suffix:semicolon
)brace
DECL|macro|GET_APIC_ID
mdefine_line|#define&t;&t;GET_APIC_ID(x)&t;get_apic_id(x)
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
DECL|function|cpu_mask_to_apicid
r_static
r_inline
r_int
r_int
id|cpu_mask_to_apicid
(paren
r_int
r_int
id|cpumask
)paren
(brace
r_return
id|cpumask
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
