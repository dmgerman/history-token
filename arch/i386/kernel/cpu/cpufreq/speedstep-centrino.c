multiline_comment|/*&n; * cpufreq driver for Enhanced SpeedStep, as found in Intel&squot;s Pentium&n; * M (part of the Centrino chipset).&n; *&n; * Despite the &quot;SpeedStep&quot; in the name, this is almost entirely unlike&n; * traditional SpeedStep.&n; *&n; * Modelled on speedstep.c&n; *&n; * Copyright (C) 2003 Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&n; *&n; * WARNING WARNING WARNING&n; * &n; * This driver manipulates the PERF_CTL MSR, which is only somewhat&n; * documented.  While it seems to work on my laptop, it has not been&n; * tested anywhere else, and it may not work for you, do strange&n; * things or simply crash.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cpufeature.h&gt;
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&quot;speedstep-centrino: &quot;
DECL|macro|MAINTAINER
mdefine_line|#define MAINTAINER&t;&quot;Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&quot;
multiline_comment|/*#define CENTRINO_DEBUG*/
macro_line|#ifdef CENTRINO_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
DECL|struct|cpu_model
r_struct
id|cpu_model
(brace
DECL|member|model_name
r_const
r_char
op_star
id|model_name
suffix:semicolon
DECL|member|max_freq
r_int
id|max_freq
suffix:semicolon
multiline_comment|/* max clock in kHz */
DECL|member|op_points
r_struct
id|cpufreq_frequency_table
op_star
id|op_points
suffix:semicolon
multiline_comment|/* clock/voltage pairs */
)brace
suffix:semicolon
multiline_comment|/* Operating points for current CPU */
DECL|variable|centrino_model
r_static
r_struct
id|cpu_model
op_star
id|centrino_model
suffix:semicolon
macro_line|#ifdef CONFIG_X86_SPEEDSTEP_CENTRINO_TABLE
multiline_comment|/* Computes the correct form for IA32_PERF_CTL MSR for a particular&n;   frequency/voltage operating point; frequency in MHz, volts in mV.&n;   This is stored as &quot;index&quot; in the structure. */
DECL|macro|OP
mdefine_line|#define OP(mhz, mv)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.frequency = (mhz) * 1000,&t;&t;&t;&t;&bslash;&n;&t;&t;.index = (((mhz)/100) &lt;&lt; 8) | ((mv - 700) / 16)&t;&t;&bslash;&n;&t;}
multiline_comment|/* &n; * These voltage tables were derived from the Intel Pentium M&n; * datasheet, document 25261202.pdf, Table 5.  I have verified they&n; * are consistent with my IBM ThinkPad X31, which has a 1.3GHz Pentium&n; * M.&n; */
multiline_comment|/* Ultra Low Voltage Intel Pentium M processor 900MHz */
DECL|variable|op_900
r_static
r_struct
id|cpufreq_frequency_table
id|op_900
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|844
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|988
)paren
comma
id|OP
c_func
(paren
l_int|900
comma
l_int|1004
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Ultra Low Voltage Intel Pentium M processor 1000MHz */
DECL|variable|op_1000
r_static
r_struct
id|cpufreq_frequency_table
id|op_1000
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|844
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|972
)paren
comma
id|OP
c_func
(paren
l_int|900
comma
l_int|988
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1004
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Low Voltage Intel Pentium M processor 1.10GHz */
DECL|variable|op_1100
r_static
r_struct
id|cpufreq_frequency_table
id|op_1100
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1020
)paren
comma
id|OP
c_func
(paren
l_int|900
comma
l_int|1100
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1164
)paren
comma
id|OP
c_func
(paren
l_int|1100
comma
l_int|1180
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Low Voltage Intel Pentium M processor 1.20GHz */
DECL|variable|op_1200
r_static
r_struct
id|cpufreq_frequency_table
id|op_1200
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1004
)paren
comma
id|OP
c_func
(paren
l_int|900
comma
l_int|1020
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1100
)paren
comma
id|OP
c_func
(paren
l_int|1100
comma
l_int|1164
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1180
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Intel Pentium M processor 1.30GHz */
DECL|variable|op_1300
r_static
r_struct
id|cpufreq_frequency_table
id|op_1300
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1260
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1292
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1356
)paren
comma
id|OP
c_func
(paren
l_int|1300
comma
l_int|1388
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Intel Pentium M processor 1.40GHz */
DECL|variable|op_1400
r_static
r_struct
id|cpufreq_frequency_table
id|op_1400
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1180
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1308
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1436
)paren
comma
id|OP
c_func
(paren
l_int|1400
comma
l_int|1484
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Intel Pentium M processor 1.50GHz */
DECL|variable|op_1500
r_static
r_struct
id|cpufreq_frequency_table
id|op_1500
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1116
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1228
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1356
)paren
comma
id|OP
c_func
(paren
l_int|1400
comma
l_int|1452
)paren
comma
id|OP
c_func
(paren
l_int|1500
comma
l_int|1484
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Intel Pentium M processor 1.60GHz */
DECL|variable|op_1600
r_static
r_struct
id|cpufreq_frequency_table
id|op_1600
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1036
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1164
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1276
)paren
comma
id|OP
c_func
(paren
l_int|1400
comma
l_int|1420
)paren
comma
id|OP
c_func
(paren
l_int|1600
comma
l_int|1484
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
multiline_comment|/* Intel Pentium M processor 1.70GHz */
DECL|variable|op_1700
r_static
r_struct
id|cpufreq_frequency_table
id|op_1700
(braket
)braket
op_assign
(brace
id|OP
c_func
(paren
l_int|600
comma
l_int|956
)paren
comma
id|OP
c_func
(paren
l_int|800
comma
l_int|1004
)paren
comma
id|OP
c_func
(paren
l_int|1000
comma
l_int|1116
)paren
comma
id|OP
c_func
(paren
l_int|1200
comma
l_int|1228
)paren
comma
id|OP
c_func
(paren
l_int|1400
comma
l_int|1308
)paren
comma
id|OP
c_func
(paren
l_int|1700
comma
l_int|1484
)paren
comma
(brace
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
)brace
)brace
suffix:semicolon
DECL|macro|OP
macro_line|#undef OP
DECL|macro|_CPU
mdefine_line|#define _CPU(max, name)&t;&bslash;&n;&t;{ &quot;Intel(R) Pentium(R) M processor &quot; name &quot;MHz&quot;, (max)*1000, op_##max }
DECL|macro|CPU
mdefine_line|#define CPU(max)&t;_CPU(max, #max)
multiline_comment|/* CPU models, their operating frequency range, and freq/voltage&n;   operating points */
DECL|variable|models
r_static
r_struct
id|cpu_model
id|models
(braket
)braket
op_assign
(brace
id|_CPU
c_func
(paren
l_int|900
comma
l_string|&quot; 900&quot;
)paren
comma
id|CPU
c_func
(paren
l_int|1000
)paren
comma
id|CPU
c_func
(paren
l_int|1100
)paren
comma
id|CPU
c_func
(paren
l_int|1200
)paren
comma
id|CPU
c_func
(paren
l_int|1300
)paren
comma
id|CPU
c_func
(paren
l_int|1400
)paren
comma
id|CPU
c_func
(paren
l_int|1500
)paren
comma
id|CPU
c_func
(paren
l_int|1600
)paren
comma
id|CPU
c_func
(paren
l_int|1700
)paren
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|macro|CPU
macro_line|#undef CPU
DECL|function|centrino_cpu_init_table
r_static
r_int
id|centrino_cpu_init_table
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|cpu
op_assign
op_amp
id|cpu_data
(braket
id|policy-&gt;cpu
)braket
suffix:semicolon
r_struct
id|cpu_model
op_star
id|model
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|cpu
comma
id|X86_FEATURE_EST
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Only Intel Pentium M stepping 5 for now - add new CPUs as&n;&t;   they appear after making sure they use PERF_CTL in the same&n;&t;   way. */
r_if
c_cond
(paren
id|cpu-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
op_logical_or
id|cpu-&gt;x86
op_ne
l_int|6
op_logical_or
id|cpu-&gt;x86_model
op_ne
l_int|9
op_logical_or
id|cpu-&gt;x86_mask
op_ne
l_int|5
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;found unsupported CPU with Enhanced SpeedStep: &quot;
l_string|&quot;send /proc/cpuinfo to &quot;
id|MAINTAINER
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_for
c_loop
(paren
id|model
op_assign
id|models
suffix:semicolon
id|model-&gt;model_name
op_ne
l_int|NULL
suffix:semicolon
id|model
op_increment
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cpu-&gt;x86_model_id
comma
id|model-&gt;model_name
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|model-&gt;model_name
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;no support for CPU model &bslash;&quot;%s&bslash;&quot;: &quot;
l_string|&quot;send /proc/cpuinfo to &quot;
id|MAINTAINER
l_string|&quot;&bslash;n&quot;
comma
id|cpu-&gt;x86_model_id
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|centrino_model
op_assign
id|model
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;found &bslash;&quot;%s&bslash;&quot;: max frequency: %dkHz&bslash;n&quot;
comma
id|model-&gt;model_name
comma
id|model-&gt;max_freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|centrino_cpu_init_table
r_static
r_inline
r_int
id|centrino_cpu_init_table
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_X86_SPEEDSTEP_CENTRINO_TABLE */
multiline_comment|/* Extract clock in kHz from PERF_CTL value */
DECL|function|extract_clock
r_static
r_int
id|extract_clock
c_func
(paren
r_int
id|msr
)paren
(brace
id|msr
op_assign
(paren
id|msr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_return
id|msr
op_star
l_int|100000
suffix:semicolon
)brace
multiline_comment|/* Return the current CPU frequency in kHz */
DECL|function|get_cur_freq
r_static
r_int
id|get_cur_freq
c_func
(paren
r_void
)paren
(brace
r_int
id|l
comma
id|h
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_PERF_STATUS
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_return
id|extract_clock
c_func
(paren
id|l
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_SPEEDSTEP_CENTRINO_ACPI
DECL|variable|p
r_static
r_struct
id|acpi_processor_performance
id|p
suffix:semicolon
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/processor.h&gt;
DECL|macro|ACPI_PDC_CAPABILITY_ENHANCED_SPEEDSTEP
mdefine_line|#define ACPI_PDC_CAPABILITY_ENHANCED_SPEEDSTEP 0x1
multiline_comment|/*&n; * centrino_cpu_init_acpi - register with ACPI P-States library &n; *&n; * Register with the ACPI P-States library (part of drivers/acpi/processor.c)&n; * in order to determine correct frequency and voltage pairings by reading&n; * the _PSS of the ACPI DSDT or SSDT tables.&n; */
DECL|function|centrino_cpu_init_acpi
r_static
r_int
id|centrino_cpu_init_acpi
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_union
id|acpi_object
id|arg0
op_assign
(brace
id|ACPI_TYPE_BUFFER
)brace
suffix:semicolon
id|u32
id|arg0_buf
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|acpi_object_list
id|arg_list
op_assign
(brace
l_int|1
comma
op_amp
id|arg0
)brace
suffix:semicolon
r_int
r_int
id|cur_freq
suffix:semicolon
r_int
id|result
op_assign
l_int|0
comma
id|i
suffix:semicolon
multiline_comment|/* _PDC settings */
id|arg0.buffer.length
op_assign
l_int|12
suffix:semicolon
id|arg0.buffer.pointer
op_assign
(paren
id|u8
op_star
)paren
id|arg0_buf
suffix:semicolon
id|arg0_buf
(braket
l_int|0
)braket
op_assign
id|ACPI_PDC_REVISION_ID
suffix:semicolon
id|arg0_buf
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|arg0_buf
(braket
l_int|2
)braket
op_assign
id|ACPI_PDC_CAPABILITY_ENHANCED_SPEEDSTEP
suffix:semicolon
id|p.pdc
op_assign
op_amp
id|arg_list
suffix:semicolon
multiline_comment|/* register with ACPI core */
r_if
c_cond
(paren
id|acpi_processor_register_performance
c_func
(paren
op_amp
id|p
comma
l_int|0
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* verify the acpi_data */
r_if
c_cond
(paren
id|p.state_count
op_le
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;No P-States&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_unreg
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|p.control_register.space_id
op_ne
id|ACPI_ADR_SPACE_FIXED_HARDWARE
)paren
op_logical_or
(paren
id|p.status_register.space_id
op_ne
id|ACPI_ADR_SPACE_FIXED_HARDWARE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Invalid control/status registers&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err_unreg
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
id|p.state_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p.states
(braket
id|i
)braket
dot
id|control
op_ne
id|p.states
(braket
id|i
)braket
dot
id|status
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Different control and status values&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_unreg
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|p.states
(braket
id|i
)braket
dot
id|core_frequency
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Zero core frequency&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_unreg
suffix:semicolon
)brace
r_if
c_cond
(paren
id|extract_clock
c_func
(paren
id|p.states
(braket
id|i
)braket
dot
id|control
)paren
op_ne
(paren
id|p.states
(braket
id|i
)braket
dot
id|core_frequency
op_star
l_int|1000
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Invalid encoded frequency&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err_unreg
suffix:semicolon
)brace
)brace
id|centrino_model
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cpu_model
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|centrino_model
)paren
(brace
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_unreg
suffix:semicolon
)brace
id|memset
c_func
(paren
id|centrino_model
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpu_model
)paren
)paren
suffix:semicolon
id|centrino_model-&gt;model_name
op_assign
l_int|NULL
suffix:semicolon
id|centrino_model-&gt;max_freq
op_assign
id|p.states
(braket
l_int|0
)braket
dot
id|core_frequency
op_star
l_int|1000
suffix:semicolon
id|centrino_model-&gt;op_points
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
op_star
(paren
id|p.state_count
op_plus
l_int|1
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|centrino_model-&gt;op_points
)paren
(brace
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_kfree
suffix:semicolon
)brace
id|cur_freq
op_assign
id|get_cur_freq
c_func
(paren
)paren
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
id|p.state_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|centrino_model-&gt;op_points
(braket
id|i
)braket
dot
id|index
op_assign
id|p.states
(braket
id|i
)braket
dot
id|control
suffix:semicolon
id|centrino_model-&gt;op_points
(braket
id|i
)braket
dot
id|frequency
op_assign
id|p.states
(braket
id|i
)braket
dot
id|core_frequency
op_star
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|cur_freq
op_eq
id|centrino_model-&gt;op_points
(braket
id|i
)braket
dot
id|frequency
)paren
id|p.state
op_assign
id|i
suffix:semicolon
)brace
id|centrino_model-&gt;op_points
(braket
id|p.state_count
)braket
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_kfree
suffix:colon
id|kfree
c_func
(paren
id|centrino_model
)paren
suffix:semicolon
id|err_unreg
suffix:colon
id|acpi_processor_unregister_performance
c_func
(paren
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|result
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|centrino_cpu_init_acpi
r_static
r_inline
r_int
id|centrino_cpu_init_acpi
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif
DECL|function|centrino_cpu_init
r_static
r_int
id|centrino_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
id|freq
suffix:semicolon
r_int
id|l
comma
id|h
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|centrino_cpu_init_acpi
c_func
(paren
id|policy
)paren
)paren
(brace
r_if
c_cond
(paren
id|centrino_cpu_init_table
c_func
(paren
id|policy
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
multiline_comment|/* Check to see if Enhanced SpeedStep is enabled, and try to&n;&t;   enable it if not. */
id|rdmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|l
op_amp
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
)paren
(brace
id|l
op_or_assign
(paren
l_int|1
op_lshift
l_int|16
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
multiline_comment|/* check to see if it stuck */
id|rdmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|l
op_amp
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;couldn&squot;t enable Enhanced SpeedStep&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|freq
op_assign
id|get_cur_freq
c_func
(paren
)paren
suffix:semicolon
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* 10uS transition latency */
id|policy-&gt;cur
op_assign
id|freq
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;centrino_cpu_init: policy=%d cur=%dkHz&bslash;n&quot;
comma
id|policy-&gt;policy
comma
id|policy-&gt;cur
)paren
suffix:semicolon
id|ret
op_assign
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
id|centrino_model-&gt;op_points
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
(paren
id|ret
)paren
suffix:semicolon
id|cpufreq_frequency_table_get_attr
c_func
(paren
id|centrino_model-&gt;op_points
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|centrino_cpu_exit
r_static
r_int
id|centrino_cpu_exit
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|centrino_model
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cpufreq_frequency_table_put_attr
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_SPEEDSTEP_CENTRINO_ACPI
r_if
c_cond
(paren
op_logical_neg
id|centrino_model-&gt;model_name
)paren
(brace
id|acpi_processor_unregister_performance
c_func
(paren
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|centrino_model-&gt;op_points
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|centrino_model
)paren
suffix:semicolon
)brace
macro_line|#endif
id|centrino_model
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * centrino_verify - verifies a new CPUFreq policy&n; * @freq: new policy&n; *&n; * Limit must be within this model&squot;s frequency range at least one&n; * border included.&n; */
DECL|function|centrino_verify
r_static
r_int
id|centrino_verify
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
id|cpufreq_frequency_table_verify
c_func
(paren
id|policy
comma
id|centrino_model-&gt;op_points
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * centrino_setpolicy - set a new CPUFreq policy&n; * @policy: new policy&n; *&n; * Sets a new CPUFreq policy.&n; */
DECL|function|centrino_target
r_static
r_int
id|centrino_target
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|target_freq
comma
r_int
r_int
id|relation
)paren
(brace
r_int
r_int
id|newstate
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|msr
comma
id|oldmsr
comma
id|h
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_if
c_cond
(paren
id|centrino_model
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
id|centrino_model-&gt;op_points
comma
id|target_freq
comma
id|relation
comma
op_amp
id|newstate
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|msr
op_assign
id|centrino_model-&gt;op_points
(braket
id|newstate
)braket
dot
id|index
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_PERF_CTL
comma
id|oldmsr
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msr
op_eq
(paren
id|oldmsr
op_amp
l_int|0xffff
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Hm, old frequency can either be the last value we put in&n;&t;   PERF_CTL, or whatever it is now. The trouble is that TM2&n;&t;   can change it behind our back, which means we never get to&n;&t;   see the speed change.  Reading back the current speed would&n;&t;   tell us something happened, but it may leave the things on&n;&t;   the notifier chain confused; we therefore stick to using&n;&t;   the last programmed speed rather than the current speed for&n;&t;   &quot;old&quot;. &n;&n;&t;   TODO: work out how the TCC interrupts work, and try to&n;&t;   catch the CPU changing things under us.&n;&t;*/
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
id|freqs.old
op_assign
id|extract_clock
c_func
(paren
id|oldmsr
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|extract_clock
c_func
(paren
id|msr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;target=%dkHz old=%d new=%d msr=%04x&bslash;n&quot;
comma
id|target_freq
comma
id|freqs.old
comma
id|freqs
dot
r_new
comma
id|msr
)paren
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
multiline_comment|/* all but 16 LSB are &quot;reserved&quot;, so treat them with&n;&t;   care */
id|oldmsr
op_and_assign
op_complement
l_int|0xffff
suffix:semicolon
id|msr
op_and_assign
l_int|0xffff
suffix:semicolon
id|oldmsr
op_or_assign
id|msr
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_PERF_CTL
comma
id|oldmsr
comma
id|h
)paren
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|centrino_attr
r_static
r_struct
id|freq_attr
op_star
id|centrino_attr
(braket
)braket
op_assign
(brace
op_amp
id|cpufreq_freq_attr_scaling_available_freqs
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|centrino_driver
r_static
r_struct
id|cpufreq_driver
id|centrino_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;centrino&quot;
comma
multiline_comment|/* should be speedstep-centrino, &n;&t;&t;&t;&t;&t; but there&squot;s a 16 char limit */
dot
id|init
op_assign
id|centrino_cpu_init
comma
dot
m_exit
op_assign
id|centrino_cpu_exit
comma
dot
id|verify
op_assign
id|centrino_verify
comma
dot
id|target
op_assign
id|centrino_target
comma
dot
id|attr
op_assign
id|centrino_attr
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * centrino_init - initializes the Enhanced SpeedStep CPUFreq driver&n; *&n; * Initializes the Enhanced SpeedStep support. Returns -ENODEV on&n; * unsupported devices, -ENOENT if there&squot;s no voltage table for this&n; * particular CPU model, -EINVAL on problems during initiatization,&n; * and zero on success.&n; *&n; * This is quite picky.  Not only does the CPU have to advertise the&n; * &quot;est&quot; flag in the cpuid capability flags, we look for a specific&n; * CPU model and stepping, and we need to have the exact model name in&n; * our voltage tables.  That is, be paranoid about not releasing&n; * someone&squot;s valuable magic smoke.&n; */
DECL|function|centrino_init
r_static
r_int
id|__init
id|centrino_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|cpu
op_assign
id|cpu_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|cpu
comma
id|X86_FEATURE_EST
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|centrino_driver
)paren
suffix:semicolon
)brace
DECL|function|centrino_exit
r_static
r_void
id|__exit
id|centrino_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|centrino_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Jeremy Fitzhardinge &lt;jeremy@goop.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Enhanced SpeedStep driver for Intel Pentium M processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|centrino_init
id|late_initcall
c_func
(paren
id|centrino_init
)paren
suffix:semicolon
DECL|variable|centrino_exit
id|module_exit
c_func
(paren
id|centrino_exit
)paren
suffix:semicolon
eof
