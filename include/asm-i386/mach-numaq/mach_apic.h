macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
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
id|cpumask_t
id|tmp
op_assign
id|CPU_MASK_ALL
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS (target_cpus())
DECL|macro|NO_BALANCE_IRQ
mdefine_line|#define NO_BALANCE_IRQ (1)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (1)
DECL|macro|NO_IOAPIC_CHECK
mdefine_line|#define NO_IOAPIC_CHECK (0)
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE dest_LowestPrio
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE 0     /* physical delivery on LOCAL quad */
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid) physid_isset(apicid, bitmap)
DECL|macro|check_apicid_present
mdefine_line|#define check_apicid_present(bit) physid_isset(bit, phys_cpu_present_map)
DECL|macro|apicid_cluster
mdefine_line|#define apicid_cluster(apicid) (apicid &amp; 0xF0)
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
l_int|1
suffix:semicolon
)brace
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
multiline_comment|/* Already done in NUMA-Q firmware */
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
l_string|&quot;NUMA-Q&quot;
comma
id|nr_ioapics
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Skip adding the timer int on secondary nodes, which causes&n; * a small but painful rift in the time-space continuum.&n; */
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
id|apic
op_ne
l_int|0
op_logical_and
id|irq
op_eq
l_int|0
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
multiline_comment|/* We don&squot;t have a good way to do this yet - hack */
r_return
id|physids_promote
c_func
(paren
l_int|0xFUL
)paren
suffix:semicolon
)brace
multiline_comment|/* Mapping from cpu number to logical apicid */
r_extern
id|u8
id|cpu_2_logical_apicid
(braket
)braket
suffix:semicolon
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
multiline_comment|/*&n; * Supporting over 60 cpus on NUMA-Q requires a locality-dependent&n; * cpu to APIC ID relation to properly interact with the intelligent&n; * mode of the cluster controller.&n; */
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
l_int|60
)paren
r_return
(paren
(paren
id|mps_cpu
op_rshift
l_int|2
)paren
op_lshift
l_int|4
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|mps_cpu
op_amp
l_int|0x3
)paren
)paren
suffix:semicolon
r_else
r_return
id|BAD_APICID
suffix:semicolon
)brace
DECL|function|generate_logical_apicid
r_static
r_inline
r_int
id|generate_logical_apicid
c_func
(paren
r_int
id|quad
comma
r_int
id|phys_apicid
)paren
(brace
r_return
(paren
id|quad
op_lshift
l_int|4
)paren
op_plus
(paren
id|phys_apicid
ques
c_cond
id|phys_apicid
op_lshift
l_int|1
suffix:colon
l_int|1
)paren
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
id|logical_apicid
op_rshift
l_int|4
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
id|logical_apicid
)paren
(brace
r_int
id|node
op_assign
id|apicid_to_node
c_func
(paren
id|logical_apicid
)paren
suffix:semicolon
r_int
id|cpu
op_assign
id|__ffs
c_func
(paren
id|logical_apicid
op_amp
l_int|0xf
)paren
suffix:semicolon
r_return
id|physid_mask_of_physid
c_func
(paren
id|cpu
op_plus
l_int|4
op_star
id|node
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
r_int
id|quad
op_assign
id|translation_record-&gt;trans_quad
suffix:semicolon
r_int
id|logical_apicid
op_assign
id|generate_logical_apicid
c_func
(paren
id|quad
comma
id|m-&gt;mpc_apicid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processor #%d %ld:%ld APIC version %d (quad %d, apic %d)&bslash;n&quot;
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
comma
id|quad
comma
id|logical_apicid
)paren
suffix:semicolon
r_return
id|logical_apicid
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
r_if
c_cond
(paren
id|numnodes
op_le
l_int|1
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Remapping cross-quad port I/O for %d quads&bslash;n&quot;
comma
id|numnodes
)paren
suffix:semicolon
id|xquad_portio
op_assign
id|ioremap
(paren
id|XQUAD_PORTIO_BASE
comma
id|numnodes
op_star
id|XQUAD_PORTIO_QUAD
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;xquad_portio vaddr 0x%08lx, len %08lx&bslash;n&quot;
comma
(paren
id|u_long
)paren
id|xquad_portio
comma
(paren
id|u_long
)paren
id|numnodes
op_star
id|XQUAD_PORTIO_QUAD
)paren
suffix:semicolon
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
multiline_comment|/*&n; * We use physical apicids here, not logical, so just return the default&n; * physical broadcast to stop people from breaking us&n; */
DECL|function|cpu_mask_to_apicid
r_static
r_inline
r_int
r_int
id|cpu_mask_to_apicid
c_func
(paren
id|cpumask_t
id|cpumask
)paren
(brace
r_return
(paren
r_int
)paren
l_int|0xF
suffix:semicolon
)brace
multiline_comment|/* No NUMA-Q box has a HT CPU, but it can&squot;t hurt to use the default code. */
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
