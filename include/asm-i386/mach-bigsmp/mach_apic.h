macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|SEQUENTIAL_APICID
mdefine_line|#define SEQUENTIAL_APICID
macro_line|#ifdef SEQUENTIAL_APICID
DECL|macro|xapic_phys_to_log_apicid
mdefine_line|#define xapic_phys_to_log_apicid(phys_apic) ( (1ul &lt;&lt; ((phys_apic) &amp; 0x3)) |&bslash;&n;&t;&t;((phys_apic&lt;&lt;2) &amp; (~0xf)) )
macro_line|#elif CLUSTERED_APICID
DECL|macro|xapic_phys_to_log_apicid
mdefine_line|#define xapic_phys_to_log_apicid(phys_apic) ( (1ul &lt;&lt; ((phys_apic) &amp; 0x3)) |&bslash;&n;&t;&t;((phys_apic) &amp; (~0xf)) )
macro_line|#endif
DECL|macro|NO_BALANCE_IRQ
mdefine_line|#define NO_BALANCE_IRQ (1)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (1)
DECL|macro|NO_IOAPIC_CHECK
mdefine_line|#define NO_IOAPIC_CHECK (0)
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
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_CLUSTER)
DECL|function|target_cpus
r_static
r_inline
id|cpumask_t
id|target_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|cpu_online_map
suffix:semicolon
)brace
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS&t;(target_cpus())
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE dest_LowestPrio
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE 1     /* logical delivery broadcast to all procs */
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID     (0xff)
DECL|function|check_apicid_used
r_static
r_inline
r_int
r_int
id|check_apicid_used
c_func
(paren
id|physid_mask_t
id|bitmap
comma
r_int
id|apicid
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* we don&squot;t use the phys_cpu_present_map to indicate apicid presence */
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
l_int|1
suffix:semicolon
)brace
DECL|macro|apicid_cluster
mdefine_line|#define apicid_cluster(apicid) (apicid &amp; 0xF0)
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
id|xapic_phys_to_log_apicid
c_func
(paren
id|hard_smp_processor_id
c_func
(paren
)paren
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
op_assign
id|calculate_ldr
c_func
(paren
id|val
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
l_string|&quot;Cluster&quot;
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
r_extern
id|u8
id|bios_cpu_apicid
(braket
)braket
suffix:semicolon
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
r_if
c_cond
(paren
id|mps_cpu
OL
id|NR_CPUS
)paren
r_return
(paren
r_int
)paren
id|bios_cpu_apicid
(braket
id|mps_cpu
)braket
suffix:semicolon
r_else
r_return
id|BAD_APICID
suffix:semicolon
)brace
DECL|function|apicid_to_cpu_present
r_static
r_inline
id|physid_mask_t
id|apicid_to_cpu_present
c_func
(paren
r_int
id|phys_apicid
)paren
(brace
r_return
id|physid_mask_of_physid
c_func
(paren
id|phys_apicid
)paren
suffix:semicolon
)brace
r_extern
id|u8
id|cpu_2_logical_apicid
(braket
)braket
suffix:semicolon
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
r_if
c_cond
(paren
id|cpu
op_ge
id|NR_CPUS
)paren
r_return
id|BAD_APICID
suffix:semicolon
r_return
(paren
r_int
)paren
id|cpu_2_logical_apicid
(braket
id|cpu
)braket
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
id|m-&gt;mpc_apicid
suffix:semicolon
)brace
DECL|function|ioapic_phys_id_map
r_static
r_inline
id|physid_mask_t
id|ioapic_phys_id_map
c_func
(paren
id|physid_mask_t
id|phys_map
)paren
(brace
multiline_comment|/* For clustered we don&squot;t have a good way to do this yet - hack */
r_return
id|physids_promote
c_func
(paren
l_int|0xFUL
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
DECL|function|enable_apic_mode
r_static
r_inline
r_void
id|enable_apic_mode
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
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cpu_mask_to_apicid
r_static
r_inline
r_int
r_int
id|cpu_mask_to_apicid
c_func
(paren
id|cpumask_const_t
id|cpumask
)paren
(brace
r_int
id|num_bits_set
suffix:semicolon
r_int
id|cpus_found
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_int
id|apicid
suffix:semicolon
id|num_bits_set
op_assign
id|cpus_weight_const
c_func
(paren
id|cpumask
)paren
suffix:semicolon
multiline_comment|/* Return id to all */
r_if
c_cond
(paren
id|num_bits_set
op_eq
id|NR_CPUS
)paren
r_return
(paren
r_int
)paren
l_int|0xFF
suffix:semicolon
multiline_comment|/* &n;&t; * The cpus in the mask must all be on the apic cluster.  If are not &n;&t; * on the same apicid cluster return default value of TARGET_CPUS. &n;&t; */
id|cpu
op_assign
id|first_cpu_const
c_func
(paren
id|cpumask
)paren
suffix:semicolon
id|apicid
op_assign
id|cpu_to_logical_apicid
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cpus_found
OL
id|num_bits_set
)paren
(brace
r_if
c_cond
(paren
id|cpu_isset_const
c_func
(paren
id|cpu
comma
id|cpumask
)paren
)paren
(brace
r_int
id|new_apicid
op_assign
id|cpu_to_logical_apicid
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apicid_cluster
c_func
(paren
id|apicid
)paren
op_ne
id|apicid_cluster
c_func
(paren
id|new_apicid
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Not a valid mask!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0xFF
suffix:semicolon
)brace
id|apicid
op_assign
id|apicid
op_or
id|new_apicid
suffix:semicolon
id|cpus_found
op_increment
suffix:semicolon
)brace
id|cpu
op_increment
suffix:semicolon
)brace
r_return
id|apicid
suffix:semicolon
)brace
DECL|function|phys_pkg_id
r_static
r_inline
id|u32
id|phys_pkg_id
c_func
(paren
id|u32
id|cpuid_apic
comma
r_int
id|index_msb
)paren
(brace
r_return
id|cpuid_apic
op_rshift
id|index_msb
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
