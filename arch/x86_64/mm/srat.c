multiline_comment|/*&n; * ACPI 3.0 based NUMA setup&n; * Copyright 2004 Andi Kleen, SuSE Labs.&n; *&n; * Reads the ACPI SRAT table to figure out what memory belongs to which CPUs.&n; *&n; * Called from acpi_numa_init while reading the SRAT and SLIT tables.&n; * Assumes all memory regions belonging to a single proximity domain&n; * are in one chunk. Holes between them will be included in the node.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/bitmap.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
DECL|variable|acpi_slit
r_static
r_struct
id|acpi_table_slit
op_star
id|acpi_slit
suffix:semicolon
DECL|variable|__initdata
r_static
id|nodemask_t
id|nodes_parsed
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
id|nodemask_t
id|nodes_found
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|node
id|nodes
(braket
id|MAX_NUMNODES
)braket
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
id|__u8
id|pxm2node
(braket
l_int|256
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|255
)braket
op_assign
l_int|0xff
)brace
suffix:semicolon
DECL|function|setup_node
r_static
id|__init
r_int
id|setup_node
c_func
(paren
r_int
id|pxm
)paren
(brace
r_int
id|node
op_assign
id|pxm2node
(braket
id|pxm
)braket
suffix:semicolon
r_if
c_cond
(paren
id|node
op_eq
l_int|0xff
)paren
(brace
r_if
c_cond
(paren
id|nodes_weight
c_func
(paren
id|nodes_found
)paren
op_ge
id|MAX_NUMNODES
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|node
op_assign
id|first_unset_node
c_func
(paren
id|nodes_found
)paren
suffix:semicolon
id|node_set
c_func
(paren
id|node
comma
id|nodes_found
)paren
suffix:semicolon
id|pxm2node
(braket
id|pxm
)braket
op_assign
id|node
suffix:semicolon
)brace
r_return
id|pxm2node
(braket
id|pxm
)braket
suffix:semicolon
)brace
DECL|function|conflicting_nodes
r_static
id|__init
r_int
id|conflicting_nodes
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
id|i
suffix:semicolon
id|for_each_online_node
c_func
(paren
id|i
)paren
(brace
r_struct
id|node
op_star
id|nd
op_assign
op_amp
id|nodes
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;start
op_eq
id|nd-&gt;end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;end
OG
id|start
op_logical_and
id|nd-&gt;start
OL
id|end
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;end
op_eq
id|end
op_logical_and
id|nd-&gt;start
op_eq
id|start
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cutoff_node
r_static
id|__init
r_void
id|cutoff_node
c_func
(paren
r_int
id|i
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|node
op_star
id|nd
op_assign
op_amp
id|nodes
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;start
OL
id|start
)paren
(brace
id|nd-&gt;start
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;end
OL
id|nd-&gt;start
)paren
id|nd-&gt;start
op_assign
id|nd-&gt;end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nd-&gt;end
OG
id|end
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|end
op_amp
l_int|0xfff
)paren
)paren
id|end
op_decrement
suffix:semicolon
id|nd-&gt;end
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;start
OG
id|nd-&gt;end
)paren
id|nd-&gt;start
op_assign
id|nd-&gt;end
suffix:semicolon
)brace
)brace
DECL|function|bad_srat
r_static
id|__init
r_void
id|bad_srat
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: SRAT not used.&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_numa
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|srat_disabled
r_static
id|__init
r_inline
r_int
id|srat_disabled
c_func
(paren
r_void
)paren
(brace
r_return
id|numa_off
op_logical_or
id|acpi_numa
OL
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Callback for SLIT parsing */
DECL|function|acpi_numa_slit_init
r_void
id|__init
id|acpi_numa_slit_init
c_func
(paren
r_struct
id|acpi_table_slit
op_star
id|slit
)paren
(brace
id|acpi_slit
op_assign
id|slit
suffix:semicolon
)brace
multiline_comment|/* Callback for Proximity Domain -&gt; LAPIC mapping */
r_void
id|__init
DECL|function|acpi_numa_processor_affinity_init
id|acpi_numa_processor_affinity_init
c_func
(paren
r_struct
id|acpi_table_processor_affinity
op_star
id|pa
)paren
(brace
r_int
id|pxm
comma
id|node
suffix:semicolon
r_if
c_cond
(paren
id|srat_disabled
c_func
(paren
)paren
op_logical_or
id|pa-&gt;flags.enabled
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|pxm
op_assign
id|pa-&gt;proximity_domain
suffix:semicolon
id|node
op_assign
id|setup_node
c_func
(paren
id|pxm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: Too many proximity domains %x&bslash;n&quot;
comma
id|pxm
)paren
suffix:semicolon
id|bad_srat
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pa-&gt;apic_id
op_ge
id|NR_CPUS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: lapic %u too large.&bslash;n&quot;
comma
id|pa-&gt;apic_id
)paren
suffix:semicolon
id|bad_srat
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cpu_to_node
(braket
id|pa-&gt;apic_id
)braket
op_assign
id|node
suffix:semicolon
id|acpi_numa
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SRAT: PXM %u -&gt; APIC %u -&gt; Node %u&bslash;n&quot;
comma
id|pxm
comma
id|pa-&gt;apic_id
comma
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/* Callback for parsing of the Proximity Domain &lt;-&gt; Memory Area mappings */
r_void
id|__init
DECL|function|acpi_numa_memory_affinity_init
id|acpi_numa_memory_affinity_init
c_func
(paren
r_struct
id|acpi_table_memory_affinity
op_star
id|ma
)paren
(brace
r_struct
id|node
op_star
id|nd
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
id|node
comma
id|pxm
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|srat_disabled
c_func
(paren
)paren
op_logical_or
id|ma-&gt;flags.enabled
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* hotplug bit is ignored for now */
id|pxm
op_assign
id|ma-&gt;proximity_domain
suffix:semicolon
id|node
op_assign
id|setup_node
c_func
(paren
id|pxm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: Too many proximity domains.&bslash;n&quot;
)paren
suffix:semicolon
id|bad_srat
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|start
op_assign
id|ma-&gt;base_addr_lo
op_or
(paren
(paren
id|u64
)paren
id|ma-&gt;base_addr_hi
op_lshift
l_int|32
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
(paren
id|ma-&gt;length_lo
op_or
(paren
(paren
id|u64
)paren
id|ma-&gt;length_hi
op_lshift
l_int|32
)paren
)paren
suffix:semicolon
id|i
op_assign
id|conflicting_nodes
c_func
(paren
id|start
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: pxm %d overlap %lx-%lx with node %d(%Lx-%Lx)&bslash;n&quot;
comma
id|pxm
comma
id|start
comma
id|end
comma
id|i
comma
id|nodes
(braket
id|i
)braket
dot
id|start
comma
id|nodes
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
id|bad_srat
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nd
op_assign
op_amp
id|nodes
(braket
id|node
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node_test_and_set
c_func
(paren
id|node
comma
id|nodes_parsed
)paren
)paren
(brace
id|nd-&gt;start
op_assign
id|start
suffix:semicolon
id|nd-&gt;end
op_assign
id|end
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|start
OL
id|nd-&gt;start
)paren
id|nd-&gt;start
op_assign
id|start
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;end
OL
id|end
)paren
id|nd-&gt;end
op_assign
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|nd-&gt;end
op_amp
l_int|0xfff
)paren
)paren
id|nd-&gt;end
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SRAT: Node %u PXM %u %Lx-%Lx&bslash;n&quot;
comma
id|node
comma
id|pxm
comma
id|nd-&gt;start
comma
id|nd-&gt;end
)paren
suffix:semicolon
)brace
DECL|function|acpi_numa_arch_fixup
r_void
id|__init
id|acpi_numa_arch_fixup
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Use the information discovered above to actually set up the nodes. */
DECL|function|acpi_scan_nodes
r_int
id|__init
id|acpi_scan_nodes
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|acpi_numa
op_le
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|memnode_shift
op_assign
id|compute_hash_shift
c_func
(paren
id|nodes
comma
id|nodes_weight
c_func
(paren
id|nodes_parsed
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memnode_shift
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SRAT: No NUMA node hash function found. Contact maintainer&bslash;n&quot;
)paren
suffix:semicolon
id|bad_srat
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|node_isset
c_func
(paren
id|i
comma
id|nodes_parsed
)paren
)paren
r_continue
suffix:semicolon
id|cutoff_node
c_func
(paren
id|i
comma
id|start
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nodes
(braket
id|i
)braket
dot
id|start
op_eq
id|nodes
(braket
id|i
)braket
dot
id|end
)paren
r_continue
suffix:semicolon
id|setup_node_bootmem
c_func
(paren
id|i
comma
id|nodes
(braket
id|i
)braket
dot
id|start
comma
id|nodes
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
)brace
id|numa_init_array
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|node_to_pxm
r_int
id|node_to_pxm
c_func
(paren
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|pxm2node
(braket
id|n
)braket
op_eq
id|n
)paren
r_return
id|n
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|pxm2node
(braket
id|i
)braket
op_eq
id|n
)paren
r_return
id|i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__node_distance
r_int
id|__node_distance
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_slit
)paren
r_return
id|a
op_eq
id|b
ques
c_cond
l_int|10
suffix:colon
l_int|20
suffix:semicolon
id|index
op_assign
id|acpi_slit-&gt;localities
op_star
id|node_to_pxm
c_func
(paren
id|a
)paren
suffix:semicolon
r_return
id|acpi_slit-&gt;entry
(braket
id|index
op_plus
id|node_to_pxm
c_func
(paren
id|b
)paren
)braket
suffix:semicolon
)brace
DECL|variable|__node_distance
id|EXPORT_SYMBOL
c_func
(paren
id|__node_distance
)paren
suffix:semicolon
eof
