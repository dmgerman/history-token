macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;cobalt.h&quot;
macro_line|#include &quot;mach_apic.h&quot;
multiline_comment|/* Have we found an MP table */
DECL|variable|smp_found_config
r_int
id|smp_found_config
suffix:semicolon
multiline_comment|/*&n; * Various Linux-internal data structures created from the&n; * MP-table.&n; */
DECL|variable|apic_version
r_int
id|apic_version
(braket
id|MAX_APICS
)braket
suffix:semicolon
DECL|variable|pic_mode
r_int
id|pic_mode
suffix:semicolon
DECL|variable|mp_lapic_addr
r_int
r_int
id|mp_lapic_addr
suffix:semicolon
multiline_comment|/* Processor that is doing the boot up */
DECL|variable|boot_cpu_physical_apicid
r_int
r_int
id|boot_cpu_physical_apicid
op_assign
op_minus
l_int|1U
suffix:semicolon
DECL|variable|boot_cpu_logical_apicid
r_int
r_int
id|boot_cpu_logical_apicid
op_assign
op_minus
l_int|1U
suffix:semicolon
multiline_comment|/* Bitmask of physically existing CPUs */
DECL|variable|phys_cpu_present_map
id|physid_mask_t
id|phys_cpu_present_map
suffix:semicolon
DECL|variable|maxcpus
r_int
r_int
id|__initdata
id|maxcpus
op_assign
id|NR_CPUS
suffix:semicolon
multiline_comment|/*&n; * The Visual Workstation is Intel MP compliant in the hardware&n; * sense, but it doesn&squot;t have a BIOS(-configuration table).&n; * No problem for Linux.&n; */
DECL|function|MP_processor_info
r_void
id|__init
id|MP_processor_info
(paren
r_struct
id|mpc_config_processor
op_star
id|m
)paren
(brace
r_int
id|ver
comma
id|logical_apicid
suffix:semicolon
id|physid_mask_t
id|apic_cpus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|m-&gt;mpc_cpuflag
op_amp
id|CPU_ENABLED
)paren
)paren
r_return
suffix:semicolon
id|logical_apicid
op_assign
id|m-&gt;mpc_apicid
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%sCPU #%d %ld:%ld APIC version %d&bslash;n&quot;
comma
id|m-&gt;mpc_cpuflag
op_amp
id|CPU_BOOTPROCESSOR
ques
c_cond
l_string|&quot;Bootup &quot;
suffix:colon
l_string|&quot;&quot;
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
r_if
c_cond
(paren
id|m-&gt;mpc_cpuflag
op_amp
id|CPU_BOOTPROCESSOR
)paren
(brace
id|boot_cpu_physical_apicid
op_assign
id|m-&gt;mpc_apicid
suffix:semicolon
id|boot_cpu_logical_apicid
op_assign
id|logical_apicid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m-&gt;mpc_apicid
OG
id|MAX_APICS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Processor #%d INVALID. (Max ID: %d).&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
comma
id|MAX_APICS
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ver
op_assign
id|m-&gt;mpc_apicver
suffix:semicolon
id|apic_cpus
op_assign
id|apicid_to_cpu_present
c_func
(paren
id|m-&gt;mpc_apicid
)paren
suffix:semicolon
id|physids_or
c_func
(paren
id|phys_cpu_present_map
comma
id|phys_cpu_present_map
comma
id|apic_cpus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Validate version&n;&t; */
r_if
c_cond
(paren
id|ver
op_eq
l_int|0x0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BIOS bug, APIC version is 0 for CPU#%d! &quot;
l_string|&quot;fixing up to 0x10. (tell your hw vendor)&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
)paren
suffix:semicolon
id|ver
op_assign
l_int|0x10
suffix:semicolon
)brace
id|apic_version
(braket
id|m-&gt;mpc_apicid
)braket
op_assign
id|ver
suffix:semicolon
)brace
DECL|function|find_smp_config
r_void
id|__init
id|find_smp_config
c_func
(paren
r_void
)paren
(brace
r_struct
id|mpc_config_processor
op_star
id|mp
op_assign
id|phys_to_virt
c_func
(paren
id|CO_CPU_TAB_PHYS
)paren
suffix:semicolon
r_int
r_int
id|ncpus
op_assign
id|readw
c_func
(paren
id|phys_to_virt
c_func
(paren
id|CO_CPU_NUM_PHYS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncpus
OG
id|CO_CPU_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;find_visws_smp: got cpu count of %d at %p&bslash;n&quot;
comma
id|ncpus
comma
id|mp
)paren
suffix:semicolon
id|ncpus
op_assign
id|CO_CPU_MAX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncpus
OG
id|maxcpus
)paren
id|ncpus
op_assign
id|maxcpus
suffix:semicolon
id|smp_found_config
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|ncpus
op_decrement
)paren
id|MP_processor_info
c_func
(paren
id|mp
op_increment
)paren
suffix:semicolon
id|mp_lapic_addr
op_assign
id|APIC_DEFAULT_PHYS_BASE
suffix:semicolon
)brace
DECL|function|get_smp_config
r_void
id|__init
id|get_smp_config
(paren
r_void
)paren
(brace
)brace
eof
