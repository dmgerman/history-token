macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_CLUSTER)
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS (0xf)
DECL|macro|NO_BALANCE_IRQ
mdefine_line|#define NO_BALANCE_IRQ (1)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (1)
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE dest_LowestPrio
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE 0     /* physical delivery on LOCAL quad */
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID      0x0F
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid) ((bitmap) &amp; (1 &lt;&lt; (apicid)))
DECL|macro|check_apicid_present
mdefine_line|#define check_apicid_present(bit) (phys_cpu_present_map &amp; (1 &lt;&lt; bit))
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
(paren
l_int|1
)paren
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
(paren
id|apic
op_ne
l_int|0
op_logical_and
id|irq
op_eq
l_int|0
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
multiline_comment|/* We don&squot;t have a good way to do this yet - hack */
r_return
l_int|0xf
suffix:semicolon
)brace
multiline_comment|/* Mapping from cpu number to logical apicid */
r_extern
r_volatile
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
(paren
(paren
(paren
id|mps_cpu
op_div
l_int|4
)paren
op_star
l_int|16
)paren
op_plus
(paren
l_int|1
op_lshift
(paren
id|mps_cpu
op_mod
l_int|4
)paren
)paren
)paren
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
(paren
id|logical_apicid
op_rshift
l_int|4
)paren
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
id|logical_apicid
)paren
(brace
r_return
(paren
(paren
id|logical_apicid
op_amp
l_int|0xf
)paren
op_lshift
(paren
l_int|4
op_star
id|apicid_to_node
c_func
(paren
id|logical_apicid
)paren
)paren
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
DECL|macro|APIC_ID_MASK
mdefine_line|#define APIC_ID_MASK (0xF&lt;&lt;24)
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
l_int|0x0F
)paren
suffix:semicolon
)brace
DECL|macro|GET_APIC_ID
mdefine_line|#define         GET_APIC_ID(x)  get_apic_id(x)
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
id|hweight32
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
l_int|32
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
id|ffs
c_func
(paren
id|cpumask
)paren
op_minus
l_int|1
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
id|cpumask
op_amp
(paren
l_int|1
op_lshift
id|cpu
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
id|TARGET_CPUS
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
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
