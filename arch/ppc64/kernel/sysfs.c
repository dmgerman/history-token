macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/hvcall.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
multiline_comment|/* SMT stuff */
macro_line|#ifndef CONFIG_PPC_ISERIES
multiline_comment|/* default to snooze disabled */
id|DEFINE_PER_CPU
c_func
(paren
r_int
r_int
comma
id|smt_snooze_delay
)paren
suffix:semicolon
DECL|function|store_smt_snooze_delay
r_static
id|ssize_t
id|store_smt_snooze_delay
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|cpu
op_star
id|cpu
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|cpu
comma
id|sysdev
)paren
suffix:semicolon
id|ssize_t
id|ret
suffix:semicolon
r_int
r_int
id|snooze
suffix:semicolon
id|ret
op_assign
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%lu&quot;
comma
op_amp
id|snooze
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|per_cpu
c_func
(paren
id|smt_snooze_delay
comma
id|cpu-&gt;sysdev.id
)paren
op_assign
id|snooze
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|show_smt_snooze_delay
r_static
id|ssize_t
id|show_smt_snooze_delay
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|cpu
op_star
id|cpu
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|cpu
comma
id|sysdev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%lu&bslash;n&quot;
comma
id|per_cpu
c_func
(paren
id|smt_snooze_delay
comma
id|cpu-&gt;sysdev.id
)paren
)paren
suffix:semicolon
)brace
r_static
id|SYSDEV_ATTR
c_func
(paren
id|smt_snooze_delay
comma
l_int|0644
comma
id|show_smt_snooze_delay
comma
id|store_smt_snooze_delay
)paren
suffix:semicolon
multiline_comment|/* Only parse OF options if the matching cmdline option was not specified */
DECL|variable|smt_snooze_cmdline
r_static
r_int
id|smt_snooze_cmdline
suffix:semicolon
DECL|function|smt_setup
r_static
r_int
id|__init
id|smt_setup
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|options
suffix:semicolon
r_int
r_int
op_star
id|val
suffix:semicolon
r_int
r_int
id|cpu
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SMT
)paren
r_return
l_int|1
suffix:semicolon
id|options
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/options&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
)paren
r_return
l_int|1
suffix:semicolon
id|val
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|options
comma
l_string|&quot;ibm,smt-snooze-delay&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smt_snooze_cmdline
op_logical_and
id|val
)paren
(brace
id|for_each_cpu
c_func
(paren
id|cpu
)paren
id|per_cpu
c_func
(paren
id|smt_snooze_delay
comma
id|cpu
)paren
op_assign
op_star
id|val
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|smt_setup
id|__initcall
c_func
(paren
id|smt_setup
)paren
suffix:semicolon
DECL|function|setup_smt_snooze_delay
r_static
r_int
id|__init
id|setup_smt_snooze_delay
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
r_int
id|snooze
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SMT
)paren
r_return
l_int|1
suffix:semicolon
id|smt_snooze_cmdline
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|snooze
)paren
)paren
(brace
id|for_each_cpu
c_func
(paren
id|cpu
)paren
id|per_cpu
c_func
(paren
id|smt_snooze_delay
comma
id|cpu
)paren
op_assign
id|snooze
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;smt-snooze-delay=&quot;
comma
id|setup_smt_snooze_delay
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* PMC stuff */
multiline_comment|/*&n; * Enabling PMCs will slow partition context switch times so we only do&n; * it the first time we write to the PMCs.&n; */
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_char
comma
id|pmcs_enabled
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|function|ppc64_enable_pmcs
r_void
id|ppc64_enable_pmcs
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX Implement for iseries */
)brace
macro_line|#else
DECL|function|ppc64_enable_pmcs
r_void
id|ppc64_enable_pmcs
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid0
suffix:semicolon
r_int
r_int
id|set
comma
id|reset
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
r_int
id|ctrl
suffix:semicolon
multiline_comment|/* Only need to enable them once */
r_if
c_cond
(paren
id|__get_cpu_var
c_func
(paren
id|pmcs_enabled
)paren
)paren
r_return
suffix:semicolon
id|__get_cpu_var
c_func
(paren
id|pmcs_enabled
)paren
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|systemcfg-&gt;platform
)paren
(brace
r_case
id|PLATFORM_PSERIES
suffix:colon
id|hid0
op_assign
id|mfspr
c_func
(paren
id|HID0
)paren
suffix:semicolon
id|hid0
op_or_assign
l_int|1UL
op_lshift
(paren
l_int|63
op_minus
l_int|20
)paren
suffix:semicolon
multiline_comment|/* POWER4 requires the following sequence */
id|asm
r_volatile
(paren
l_string|&quot;sync&bslash;n&quot;
l_string|&quot;mtspr&t;%1, %0&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;mfspr&t;%0, %1&bslash;n&quot;
l_string|&quot;isync&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|hid0
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|HID0
)paren
comma
l_string|&quot;0&quot;
(paren
id|hid0
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PLATFORM_PSERIES_LPAR
suffix:colon
id|set
op_assign
l_int|1UL
op_lshift
l_int|63
suffix:semicolon
id|reset
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|plpar_hcall_norets
c_func
(paren
id|H_PERFMON
comma
id|set
comma
id|reset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;H_PERFMON call returned %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* instruct hypervisor to maintain PMCs */
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;firmware_features
op_amp
id|FW_FEATURE_SPLPAR
)paren
(brace
r_char
op_star
id|ptr
op_assign
(paren
r_char
op_star
)paren
op_amp
id|paca
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|lppaca
suffix:semicolon
id|ptr
(braket
l_int|0xBB
)braket
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * On SMT machines we have to set the run latch in the ctrl register&n;&t; * in order to make PMC6 spin.&n;&t; */
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SMT
)paren
(brace
id|ctrl
op_assign
id|mfspr
c_func
(paren
id|CTRLF
)paren
suffix:semicolon
id|ctrl
op_or_assign
id|RUNLATCH
suffix:semicolon
id|mtspr
c_func
(paren
id|CTRLT
comma
id|ctrl
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* XXX convert to rusty&squot;s on_one_cpu */
DECL|function|run_on_cpu
r_static
r_int
r_int
id|run_on_cpu
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|arg
)paren
(brace
id|cpumask_t
id|old_affinity
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
multiline_comment|/* should return -EINVAL to userspace */
r_if
c_cond
(paren
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|ret
op_assign
id|func
c_func
(paren
id|arg
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|old_affinity
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|macro|SYSFS_PMCSETUP
mdefine_line|#define SYSFS_PMCSETUP(NAME, ADDRESS) &bslash;&n;static unsigned long read_##NAME(unsigned long junk) &bslash;&n;{ &bslash;&n;&t;return mfspr(ADDRESS); &bslash;&n;} &bslash;&n;static unsigned long write_##NAME(unsigned long val) &bslash;&n;{ &bslash;&n;&t;ppc64_enable_pmcs(); &bslash;&n;&t;mtspr(ADDRESS, val); &bslash;&n;&t;return 0; &bslash;&n;} &bslash;&n;static ssize_t show_##NAME(struct sys_device *dev, char *buf) &bslash;&n;{ &bslash;&n;&t;struct cpu *cpu = container_of(dev, struct cpu, sysdev); &bslash;&n;&t;unsigned long val = run_on_cpu(cpu-&gt;sysdev.id, read_##NAME, 0); &bslash;&n;&t;return sprintf(buf, &quot;%lx&bslash;n&quot;, val); &bslash;&n;} &bslash;&n;static ssize_t __attribute_used__ &bslash;&n;&t;store_##NAME(struct sys_device *dev, const char *buf, size_t count) &bslash;&n;{ &bslash;&n;&t;struct cpu *cpu = container_of(dev, struct cpu, sysdev); &bslash;&n;&t;unsigned long val; &bslash;&n;&t;int ret = sscanf(buf, &quot;%lx&quot;, &amp;val); &bslash;&n;&t;if (ret != 1) &bslash;&n;&t;&t;return -EINVAL; &bslash;&n;&t;run_on_cpu(cpu-&gt;sysdev.id, write_##NAME, val); &bslash;&n;&t;return count; &bslash;&n;}
id|SYSFS_PMCSETUP
c_func
(paren
id|mmcr0
comma
id|SPRN_MMCR0
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|mmcr1
comma
id|SPRN_MMCR1
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|mmcra
comma
id|SPRN_MMCRA
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc1
comma
id|SPRN_PMC1
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc2
comma
id|SPRN_PMC2
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc3
comma
id|SPRN_PMC3
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc4
comma
id|SPRN_PMC4
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc5
comma
id|SPRN_PMC5
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc6
comma
id|SPRN_PMC6
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc7
comma
id|SPRN_PMC7
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|pmc8
comma
id|SPRN_PMC8
)paren
suffix:semicolon
id|SYSFS_PMCSETUP
c_func
(paren
id|purr
comma
id|SPRN_PURR
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|mmcr0
comma
l_int|0600
comma
id|show_mmcr0
comma
id|store_mmcr0
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|mmcr1
comma
l_int|0600
comma
id|show_mmcr1
comma
id|store_mmcr1
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|mmcra
comma
l_int|0600
comma
id|show_mmcra
comma
id|store_mmcra
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc1
comma
l_int|0600
comma
id|show_pmc1
comma
id|store_pmc1
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc2
comma
l_int|0600
comma
id|show_pmc2
comma
id|store_pmc2
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc3
comma
l_int|0600
comma
id|show_pmc3
comma
id|store_pmc3
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc4
comma
l_int|0600
comma
id|show_pmc4
comma
id|store_pmc4
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc5
comma
l_int|0600
comma
id|show_pmc5
comma
id|store_pmc5
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc6
comma
l_int|0600
comma
id|show_pmc6
comma
id|store_pmc6
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc7
comma
l_int|0600
comma
id|show_pmc7
comma
id|store_pmc7
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|pmc8
comma
l_int|0600
comma
id|show_pmc8
comma
id|store_pmc8
)paren
suffix:semicolon
r_static
id|SYSDEV_ATTR
c_func
(paren
id|purr
comma
l_int|0600
comma
id|show_purr
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|register_cpu_pmc
r_static
r_void
id|__init
id|register_cpu_pmc
c_func
(paren
r_struct
id|sys_device
op_star
id|s
)paren
(brace
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_mmcr0
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_mmcr1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_MMCRA
)paren
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_mmcra
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc1
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc2
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc3
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc4
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc5
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_PMC8
)paren
(brace
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc7
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_pmc8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SMT
)paren
id|sysdev_create_file
c_func
(paren
id|s
comma
op_amp
id|attr_purr
)paren
suffix:semicolon
)brace
multiline_comment|/* NUMA stuff */
macro_line|#ifdef CONFIG_NUMA
DECL|variable|node_devices
r_static
r_struct
id|node
id|node_devices
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|function|register_nodes
r_static
r_void
id|register_nodes
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|MAX_NUMNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|node_online
c_func
(paren
id|i
)paren
)paren
(brace
r_int
id|p_node
op_assign
id|parent_node
c_func
(paren
id|i
)paren
suffix:semicolon
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|p_node
op_ne
id|i
)paren
id|parent
op_assign
op_amp
id|node_devices
(braket
id|p_node
)braket
suffix:semicolon
id|register_node
c_func
(paren
op_amp
id|node_devices
(braket
id|i
)braket
comma
id|i
comma
id|parent
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
DECL|function|register_nodes
r_static
r_void
id|register_nodes
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Only valid if CPU is online. */
DECL|function|show_physical_id
r_static
id|ssize_t
id|show_physical_id
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|cpu
op_star
id|cpu
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|cpu
comma
id|sysdev
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|get_hard_smp_processor_id
c_func
(paren
id|cpu-&gt;sysdev.id
)paren
)paren
suffix:semicolon
)brace
r_static
id|SYSDEV_ATTR
c_func
(paren
id|physical_id
comma
l_int|0444
comma
id|show_physical_id
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|cpu
comma
id|cpu_devices
)paren
suffix:semicolon
DECL|function|topology_init
r_static
r_int
id|__init
id|topology_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
id|register_nodes
c_func
(paren
)paren
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|cpu
op_star
id|c
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_devices
comma
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
id|parent
op_assign
op_amp
id|node_devices
(braket
id|cpu_to_node
c_func
(paren
id|cpu
)paren
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * For now, we just see if the system supports making&n;&t;&t; * the RTAS calls for CPU hotplug.  But, there may be a&n;&t;&t; * more comprehensive way to do this for an individual&n;&t;&t; * CPU.  For instance, the boot cpu might never be valid&n;&t;&t; * for hotplugging.&n;&t;&t; */
r_if
c_cond
(paren
id|systemcfg-&gt;platform
op_ne
id|PLATFORM_PSERIES_LPAR
)paren
id|c-&gt;no_control
op_assign
l_int|1
suffix:semicolon
id|register_cpu
c_func
(paren
id|c
comma
id|cpu
comma
id|parent
)paren
suffix:semicolon
id|register_cpu_pmc
c_func
(paren
op_amp
id|c-&gt;sysdev
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|c-&gt;sysdev
comma
op_amp
id|attr_physical_id
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SMT
)paren
id|sysdev_create_file
c_func
(paren
op_amp
id|c-&gt;sysdev
comma
op_amp
id|attr_smt_snooze_delay
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|topology_init
id|__initcall
c_func
(paren
id|topology_init
)paren
suffix:semicolon
eof
