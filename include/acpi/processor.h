macro_line|#ifndef __ACPI_PROCESSOR_H
DECL|macro|__ACPI_PROCESSOR_H
mdefine_line|#define __ACPI_PROCESSOR_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|ACPI_PROCESSOR_BUSY_METRIC
mdefine_line|#define ACPI_PROCESSOR_BUSY_METRIC&t;10
DECL|macro|ACPI_PROCESSOR_MAX_POWER
mdefine_line|#define ACPI_PROCESSOR_MAX_POWER&t;8
DECL|macro|ACPI_PROCESSOR_MAX_C2_LATENCY
mdefine_line|#define ACPI_PROCESSOR_MAX_C2_LATENCY&t;100
DECL|macro|ACPI_PROCESSOR_MAX_C3_LATENCY
mdefine_line|#define ACPI_PROCESSOR_MAX_C3_LATENCY&t;1000
DECL|macro|ACPI_PROCESSOR_MAX_THROTTLING
mdefine_line|#define ACPI_PROCESSOR_MAX_THROTTLING&t;16
DECL|macro|ACPI_PROCESSOR_MAX_THROTTLE
mdefine_line|#define ACPI_PROCESSOR_MAX_THROTTLE&t;250&t;/* 25% */
DECL|macro|ACPI_PROCESSOR_MAX_DUTY_WIDTH
mdefine_line|#define ACPI_PROCESSOR_MAX_DUTY_WIDTH&t;4
multiline_comment|/* Power Management */
r_struct
id|acpi_processor_cx
suffix:semicolon
DECL|struct|acpi_power_register
r_struct
id|acpi_power_register
(brace
DECL|member|descriptor
id|u8
id|descriptor
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|bit_width
id|u8
id|bit_width
suffix:semicolon
DECL|member|bit_offset
id|u8
id|bit_offset
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|address
id|u64
id|address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_processor_cx_policy
r_struct
id|acpi_processor_cx_policy
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|state
r_struct
id|acpi_processor_cx
op_star
id|state
suffix:semicolon
r_struct
(brace
DECL|member|time
id|u32
id|time
suffix:semicolon
DECL|member|ticks
id|u32
id|ticks
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|bm
id|u32
id|bm
suffix:semicolon
DECL|member|threshold
)brace
id|threshold
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_processor_cx
r_struct
id|acpi_processor_cx
(brace
DECL|member|valid
id|u8
id|valid
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|latency
id|u32
id|latency
suffix:semicolon
DECL|member|latency_ticks
id|u32
id|latency_ticks
suffix:semicolon
DECL|member|power
id|u32
id|power
suffix:semicolon
DECL|member|usage
id|u32
id|usage
suffix:semicolon
DECL|member|promotion
r_struct
id|acpi_processor_cx_policy
id|promotion
suffix:semicolon
DECL|member|demotion
r_struct
id|acpi_processor_cx_policy
id|demotion
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_processor_power
r_struct
id|acpi_processor_power
(brace
DECL|member|state
r_struct
id|acpi_processor_cx
op_star
id|state
suffix:semicolon
DECL|member|bm_check_timestamp
r_int
r_int
id|bm_check_timestamp
suffix:semicolon
DECL|member|default_state
id|u32
id|default_state
suffix:semicolon
DECL|member|bm_activity
id|u32
id|bm_activity
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|states
r_struct
id|acpi_processor_cx
id|states
(braket
id|ACPI_PROCESSOR_MAX_POWER
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Performance Management */
DECL|struct|acpi_pct_register
r_struct
id|acpi_pct_register
(brace
DECL|member|descriptor
id|u8
id|descriptor
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|bit_width
id|u8
id|bit_width
suffix:semicolon
DECL|member|bit_offset
id|u8
id|bit_offset
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|address
id|u64
id|address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_processor_px
r_struct
id|acpi_processor_px
(brace
DECL|member|core_frequency
id|acpi_integer
id|core_frequency
suffix:semicolon
multiline_comment|/* megahertz */
DECL|member|power
id|acpi_integer
id|power
suffix:semicolon
multiline_comment|/* milliWatts */
DECL|member|transition_latency
id|acpi_integer
id|transition_latency
suffix:semicolon
multiline_comment|/* microseconds */
DECL|member|bus_master_latency
id|acpi_integer
id|bus_master_latency
suffix:semicolon
multiline_comment|/* microseconds */
DECL|member|control
id|acpi_integer
id|control
suffix:semicolon
multiline_comment|/* control value */
DECL|member|status
id|acpi_integer
id|status
suffix:semicolon
multiline_comment|/* success indicator */
)brace
suffix:semicolon
DECL|macro|ACPI_PDC_REVISION_ID
mdefine_line|#define ACPI_PDC_REVISION_ID                   0x1
DECL|struct|acpi_processor_performance
r_struct
id|acpi_processor_performance
(brace
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|platform_limit
r_int
r_int
id|platform_limit
suffix:semicolon
DECL|member|control_register
r_struct
id|acpi_pct_register
id|control_register
suffix:semicolon
DECL|member|status_register
r_struct
id|acpi_pct_register
id|status_register
suffix:semicolon
DECL|member|state_count
r_int
r_int
id|state_count
suffix:semicolon
DECL|member|states
r_struct
id|acpi_processor_px
op_star
id|states
suffix:semicolon
multiline_comment|/* the _PDC objects passed by the driver, if any */
DECL|member|pdc
r_struct
id|acpi_object_list
op_star
id|pdc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Throttling Control */
DECL|struct|acpi_processor_tx
r_struct
id|acpi_processor_tx
(brace
DECL|member|power
id|u16
id|power
suffix:semicolon
DECL|member|performance
id|u16
id|performance
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_processor_throttling
r_struct
id|acpi_processor_throttling
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|duty_offset
id|u8
id|duty_offset
suffix:semicolon
DECL|member|duty_width
id|u8
id|duty_width
suffix:semicolon
DECL|member|state_count
r_int
id|state_count
suffix:semicolon
DECL|member|states
r_struct
id|acpi_processor_tx
id|states
(braket
id|ACPI_PROCESSOR_MAX_THROTTLING
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Limit Interface */
DECL|struct|acpi_processor_lx
r_struct
id|acpi_processor_lx
(brace
DECL|member|px
r_int
id|px
suffix:semicolon
multiline_comment|/* performace state */
DECL|member|tx
r_int
id|tx
suffix:semicolon
multiline_comment|/* throttle level */
)brace
suffix:semicolon
DECL|struct|acpi_processor_limit
r_struct
id|acpi_processor_limit
(brace
DECL|member|state
r_struct
id|acpi_processor_lx
id|state
suffix:semicolon
multiline_comment|/* current limit */
DECL|member|thermal
r_struct
id|acpi_processor_lx
id|thermal
suffix:semicolon
multiline_comment|/* thermal limit */
DECL|member|user
r_struct
id|acpi_processor_lx
id|user
suffix:semicolon
multiline_comment|/* user limit */
)brace
suffix:semicolon
DECL|struct|acpi_processor_flags
r_struct
id|acpi_processor_flags
(brace
DECL|member|power
id|u8
id|power
suffix:colon
l_int|1
suffix:semicolon
DECL|member|performance
id|u8
id|performance
suffix:colon
l_int|1
suffix:semicolon
DECL|member|throttling
id|u8
id|throttling
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit
id|u8
id|limit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bm_control
id|u8
id|bm_control
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bm_check
id|u8
id|bm_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_cst
id|u8
id|has_cst
suffix:colon
l_int|1
suffix:semicolon
DECL|member|power_setup_done
id|u8
id|power_setup_done
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_processor
r_struct
id|acpi_processor
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|acpi_id
id|u32
id|acpi_id
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|pblk
id|u32
id|pblk
suffix:semicolon
DECL|member|performance_platform_limit
r_int
id|performance_platform_limit
suffix:semicolon
DECL|member|flags
r_struct
id|acpi_processor_flags
id|flags
suffix:semicolon
DECL|member|power
r_struct
id|acpi_processor_power
id|power
suffix:semicolon
DECL|member|performance
r_struct
id|acpi_processor_performance
op_star
id|performance
suffix:semicolon
DECL|member|throttling
r_struct
id|acpi_processor_throttling
id|throttling
suffix:semicolon
DECL|member|limit
r_struct
id|acpi_processor_limit
id|limit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_processor_errata
r_struct
id|acpi_processor_errata
(brace
DECL|member|smp
id|u8
id|smp
suffix:semicolon
r_struct
(brace
DECL|member|throttle
id|u8
id|throttle
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fdma
id|u8
id|fdma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|bmisx
id|u32
id|bmisx
suffix:semicolon
DECL|member|piix4
)brace
id|piix4
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|acpi_processor_register_performance
(paren
r_struct
id|acpi_processor_performance
op_star
id|performance
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|acpi_processor_unregister_performance
(paren
r_struct
id|acpi_processor_performance
op_star
id|performance
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* note: this locks both the calling module and the processor module&n;         if a _PPC object exists, rmmod is disallowed then */
r_int
id|acpi_processor_notify_smm
c_func
(paren
r_struct
id|module
op_star
id|calling_module
)paren
suffix:semicolon
multiline_comment|/* for communication between multiple parts of the processor kernel module */
r_extern
r_struct
id|acpi_processor
op_star
id|processors
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_struct
id|acpi_processor_errata
id|errata
suffix:semicolon
multiline_comment|/* in processor_perflib.c */
macro_line|#ifdef CONFIG_CPU_FREQ
r_void
id|acpi_processor_ppc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_processor_ppc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_processor_ppc_has_changed
c_func
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
suffix:semicolon
macro_line|#else
DECL|function|acpi_processor_ppc_init
r_static
r_inline
r_void
id|acpi_processor_ppc_init
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|acpi_processor_ppc_exit
r_static
r_inline
r_void
id|acpi_processor_ppc_exit
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|acpi_processor_ppc_has_changed
r_static
r_inline
r_int
id|acpi_processor_ppc_has_changed
c_func
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
(brace
r_static
r_int
r_int
id|printout
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|printout
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: Processor Platform Limit event detected, but not handled.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Consider compiling CPUfreq support into your kernel.&bslash;n&quot;
)paren
suffix:semicolon
id|printout
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_CPU_FREQ */
multiline_comment|/* in processor_throttling.c */
r_int
id|acpi_processor_get_throttling_info
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
suffix:semicolon
r_int
id|acpi_processor_set_throttling
(paren
r_struct
id|acpi_processor
op_star
id|pr
comma
r_int
id|state
)paren
suffix:semicolon
r_int
id|acpi_processor_throttling_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
id|ssize_t
id|acpi_processor_write_throttling
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|acpi_processor_throttling_fops
suffix:semicolon
multiline_comment|/* in processor_idle.c */
r_int
id|acpi_processor_power_init
c_func
(paren
r_struct
id|acpi_processor
op_star
id|pr
comma
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_processor_cst_has_changed
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
suffix:semicolon
r_int
id|acpi_processor_power_exit
c_func
(paren
r_struct
id|acpi_processor
op_star
id|pr
comma
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
multiline_comment|/* in processor_thermal.c */
r_int
id|acpi_processor_get_limit_info
(paren
r_struct
id|acpi_processor
op_star
id|pr
)paren
suffix:semicolon
r_int
id|acpi_processor_limit_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
id|ssize_t
id|acpi_processor_write_limit
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|acpi_processor_limit_fops
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ
r_void
id|acpi_thermal_cpufreq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_thermal_cpufreq_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|acpi_thermal_cpufreq_init
r_static
r_inline
r_void
id|acpi_thermal_cpufreq_init
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|acpi_thermal_cpufreq_exit
r_static
r_inline
r_void
id|acpi_thermal_cpufreq_exit
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
