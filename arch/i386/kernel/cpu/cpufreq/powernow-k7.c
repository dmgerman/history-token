multiline_comment|/*&n; *  AMD K7 Powernow driver.&n; *  (C) 2003 Dave Jones &lt;davej@codemonkey.org.uk&gt; on behalf of SuSE Labs.&n; *  (C) 2003-2004 Dave Jones &lt;davej@redhat.com&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon datasheets &amp; sample CPUs kindly provided by AMD.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; *&n; * Errata 5: Processor may fail to execute a FID/VID change in presence of interrupt.&n; * - We cli/sti on stepping A0 CPUs around the FID/VID transition.&n; * Errata 15: Processors with half frequency multipliers may hang upon wakeup from disconnect.&n; * - We disable half multipliers if ACPI is used on A0 stepping CPUs.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_ACPI_PROCESSOR
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/processor.h&gt;
macro_line|#endif
macro_line|#include &quot;powernow-k7.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
DECL|macro|PFX
mdefine_line|#define PFX &quot;powernow: &quot;
DECL|struct|psb_s
r_struct
id|psb_s
(brace
DECL|member|signature
id|u8
id|signature
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|tableversion
id|u8
id|tableversion
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|settlingtime
id|u16
id|settlingtime
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|numpst
id|u8
id|numpst
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pst_s
r_struct
id|pst_s
(brace
DECL|member|cpuid
id|u32
id|cpuid
suffix:semicolon
DECL|member|fsbspeed
id|u8
id|fsbspeed
suffix:semicolon
DECL|member|maxfid
id|u8
id|maxfid
suffix:semicolon
DECL|member|startvid
id|u8
id|startvid
suffix:semicolon
DECL|member|numpstates
id|u8
id|numpstates
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_PROCESSOR
DECL|union|powernow_acpi_control_t
r_union
id|powernow_acpi_control_t
(brace
r_struct
(brace
DECL|member|fid
r_int
r_int
id|fid
suffix:colon
l_int|5
comma
DECL|member|vid
id|vid
suffix:colon
l_int|5
comma
DECL|member|sgtc
id|sgtc
suffix:colon
l_int|20
comma
DECL|member|res1
id|res1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* divide by 1000 to get VID. */
DECL|variable|mobile_vid_table
r_static
r_int
id|mobile_vid_table
(braket
l_int|32
)braket
op_assign
(brace
l_int|2000
comma
l_int|1950
comma
l_int|1900
comma
l_int|1850
comma
l_int|1800
comma
l_int|1750
comma
l_int|1700
comma
l_int|1650
comma
l_int|1600
comma
l_int|1550
comma
l_int|1500
comma
l_int|1450
comma
l_int|1400
comma
l_int|1350
comma
l_int|1300
comma
l_int|0
comma
l_int|1275
comma
l_int|1250
comma
l_int|1225
comma
l_int|1200
comma
l_int|1175
comma
l_int|1150
comma
l_int|1125
comma
l_int|1100
comma
l_int|1075
comma
l_int|1050
comma
l_int|1024
comma
l_int|1000
comma
l_int|975
comma
l_int|950
comma
l_int|925
comma
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* divide by 10 to get FID. */
DECL|variable|fid_codes
r_static
r_int
id|fid_codes
(braket
l_int|32
)braket
op_assign
(brace
l_int|110
comma
l_int|115
comma
l_int|120
comma
l_int|125
comma
l_int|50
comma
l_int|55
comma
l_int|60
comma
l_int|65
comma
l_int|70
comma
l_int|75
comma
l_int|80
comma
l_int|85
comma
l_int|90
comma
l_int|95
comma
l_int|100
comma
l_int|105
comma
l_int|30
comma
l_int|190
comma
l_int|40
comma
l_int|200
comma
l_int|130
comma
l_int|135
comma
l_int|140
comma
l_int|210
comma
l_int|150
comma
l_int|225
comma
l_int|160
comma
l_int|165
comma
l_int|170
comma
l_int|180
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* This parameter is used in order to force ACPI instead of legacy method for&n; * configuration purpose.&n; */
DECL|variable|powernow_acpi_force
r_static
r_int
id|powernow_acpi_force
suffix:semicolon
DECL|variable|powernow_table
r_static
r_struct
id|cpufreq_frequency_table
op_star
id|powernow_table
suffix:semicolon
DECL|variable|can_scale_bus
r_static
r_int
r_int
id|can_scale_bus
suffix:semicolon
DECL|variable|can_scale_vid
r_static
r_int
r_int
id|can_scale_vid
suffix:semicolon
DECL|variable|minimum_speed
r_static
r_int
r_int
id|minimum_speed
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|maximum_speed
r_static
r_int
r_int
id|maximum_speed
suffix:semicolon
DECL|variable|number_scales
r_static
r_int
r_int
id|number_scales
suffix:semicolon
DECL|variable|fsb
r_static
r_int
r_int
id|fsb
suffix:semicolon
DECL|variable|latency
r_static
r_int
r_int
id|latency
suffix:semicolon
DECL|variable|have_a0
r_static
r_char
id|have_a0
suffix:semicolon
DECL|function|check_fsb
r_static
r_int
id|check_fsb
c_func
(paren
r_int
r_int
id|fsbspeed
)paren
(brace
r_int
id|delta
suffix:semicolon
r_int
r_int
id|f
op_assign
id|fsb
op_div
l_int|1000
suffix:semicolon
id|delta
op_assign
(paren
id|fsbspeed
OG
id|f
)paren
ques
c_cond
id|fsbspeed
op_minus
id|f
suffix:colon
id|f
op_minus
id|fsbspeed
suffix:semicolon
r_return
(paren
id|delta
OL
l_int|5
)paren
suffix:semicolon
)brace
DECL|function|check_powernow
r_static
r_int
id|check_powernow
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
r_int
r_int
id|maxei
comma
id|eax
comma
id|ebx
comma
id|ecx
comma
id|edx
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_AMD
)paren
op_logical_or
(paren
id|c-&gt;x86
op_ne
l_int|6
)paren
)paren
(brace
macro_line|#ifdef MODULE
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;This module only works with AMD K7 CPUs&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get maximum capabilities */
id|maxei
op_assign
id|cpuid_eax
(paren
l_int|0x80000000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxei
OL
l_int|0x80000007
)paren
(brace
multiline_comment|/* Any powernow info ? */
macro_line|#ifdef MODULE
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;No powernow capabilities detected&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c-&gt;x86_model
op_eq
l_int|6
)paren
op_logical_and
(paren
id|c-&gt;x86_mask
op_eq
l_int|0
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;K7 660[A0] core detected, enabling errata workarounds&bslash;n&quot;
)paren
suffix:semicolon
id|have_a0
op_assign
l_int|1
suffix:semicolon
)brace
id|cpuid
c_func
(paren
l_int|0x80000007
comma
op_amp
id|eax
comma
op_amp
id|ebx
comma
op_amp
id|ecx
comma
op_amp
id|edx
)paren
suffix:semicolon
multiline_comment|/* Check we can actually do something before we say anything.*/
r_if
c_cond
(paren
op_logical_neg
(paren
id|edx
op_amp
(paren
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|2
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;PowerNOW! Technology present. Can scale: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|edx
op_amp
l_int|1
op_lshift
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;frequency&quot;
)paren
suffix:semicolon
id|can_scale_bus
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|edx
op_amp
(paren
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|2
)paren
)paren
op_eq
l_int|0x6
)paren
id|printk
(paren
l_string|&quot; and &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|edx
op_amp
l_int|1
op_lshift
l_int|2
)paren
(brace
id|printk
(paren
l_string|&quot;voltage&quot;
)paren
suffix:semicolon
id|can_scale_vid
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|get_ranges
r_static
r_int
id|get_ranges
(paren
r_int
r_char
op_star
id|pst
)paren
(brace
r_int
r_int
id|j
suffix:semicolon
r_int
r_int
id|speed
suffix:semicolon
id|u8
id|fid
comma
id|vid
suffix:semicolon
id|powernow_table
op_assign
id|kmalloc
c_func
(paren
(paren
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
op_star
(paren
id|number_scales
op_plus
l_int|1
)paren
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|powernow_table
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|powernow_table
comma
l_int|0
comma
(paren
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
op_star
(paren
id|number_scales
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|number_scales
suffix:semicolon
id|j
op_increment
)paren
(brace
id|fid
op_assign
op_star
id|pst
op_increment
suffix:semicolon
id|powernow_table
(braket
id|j
)braket
dot
id|frequency
op_assign
(paren
id|fsb
op_star
id|fid_codes
(braket
id|fid
)braket
)paren
op_div
l_int|10
suffix:semicolon
id|powernow_table
(braket
id|j
)braket
dot
id|index
op_assign
id|fid
suffix:semicolon
multiline_comment|/* lower 8 bits */
id|speed
op_assign
id|powernow_table
(braket
id|j
)braket
dot
id|frequency
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fid_codes
(braket
id|fid
)braket
op_mod
l_int|10
)paren
op_eq
l_int|5
)paren
(brace
macro_line|#if defined(CONFIG_ACPI_PROCESSOR) || defined(CONFIG_ACPI_PROCESSOR_MODULE)
r_if
c_cond
(paren
id|have_a0
op_eq
l_int|1
)paren
id|powernow_table
(braket
id|j
)braket
dot
id|frequency
op_assign
id|CPUFREQ_ENTRY_INVALID
suffix:semicolon
macro_line|#endif
)brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;   FID: 0x%x (%d.%dx [%dMHz])&bslash;t&quot;
comma
id|fid
comma
id|fid_codes
(braket
id|fid
)braket
op_div
l_int|10
comma
id|fid_codes
(braket
id|fid
)braket
op_mod
l_int|10
comma
id|speed
op_div
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speed
OL
id|minimum_speed
)paren
id|minimum_speed
op_assign
id|speed
suffix:semicolon
r_if
c_cond
(paren
id|speed
OG
id|maximum_speed
)paren
id|maximum_speed
op_assign
id|speed
suffix:semicolon
id|vid
op_assign
op_star
id|pst
op_increment
suffix:semicolon
id|powernow_table
(braket
id|j
)braket
dot
id|index
op_or_assign
(paren
id|vid
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* upper 8 bits */
id|dprintk
(paren
l_string|&quot;VID: 0x%x (%d.%03dV)&bslash;n&quot;
comma
id|vid
comma
id|mobile_vid_table
(braket
id|vid
)braket
op_div
l_int|1000
comma
id|mobile_vid_table
(braket
id|vid
)braket
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
id|powernow_table
(braket
id|number_scales
)braket
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
suffix:semicolon
id|powernow_table
(braket
id|number_scales
)braket
dot
id|index
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|change_FID
r_static
r_void
id|change_FID
c_func
(paren
r_int
id|fid
)paren
(brace
r_union
id|msr_fidvidctl
id|fidvidctl
suffix:semicolon
id|rdmsrl
(paren
id|MSR_K7_FID_VID_CTL
comma
id|fidvidctl.val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fidvidctl.bits.FID
op_ne
id|fid
)paren
(brace
id|fidvidctl.bits.SGTC
op_assign
id|latency
suffix:semicolon
id|fidvidctl.bits.FID
op_assign
id|fid
suffix:semicolon
id|fidvidctl.bits.VIDC
op_assign
l_int|0
suffix:semicolon
id|fidvidctl.bits.FIDC
op_assign
l_int|1
suffix:semicolon
id|wrmsrl
(paren
id|MSR_K7_FID_VID_CTL
comma
id|fidvidctl.val
)paren
suffix:semicolon
)brace
)brace
DECL|function|change_VID
r_static
r_void
id|change_VID
c_func
(paren
r_int
id|vid
)paren
(brace
r_union
id|msr_fidvidctl
id|fidvidctl
suffix:semicolon
id|rdmsrl
(paren
id|MSR_K7_FID_VID_CTL
comma
id|fidvidctl.val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fidvidctl.bits.VID
op_ne
id|vid
)paren
(brace
id|fidvidctl.bits.SGTC
op_assign
id|latency
suffix:semicolon
id|fidvidctl.bits.VID
op_assign
id|vid
suffix:semicolon
id|fidvidctl.bits.FIDC
op_assign
l_int|0
suffix:semicolon
id|fidvidctl.bits.VIDC
op_assign
l_int|1
suffix:semicolon
id|wrmsrl
(paren
id|MSR_K7_FID_VID_CTL
comma
id|fidvidctl.val
)paren
suffix:semicolon
)brace
)brace
DECL|function|change_speed
r_static
r_void
id|change_speed
(paren
r_int
r_int
id|index
)paren
(brace
id|u8
id|fid
comma
id|vid
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_union
id|msr_fidvidstatus
id|fidvidstatus
suffix:semicolon
r_int
id|cfid
suffix:semicolon
multiline_comment|/* fid are the lower 8 bits of the index we stored into&n;&t; * the cpufreq frequency table in powernow_decode_bios,&n;&t; * vid are the upper 8 bits.&n;&t; */
id|fid
op_assign
id|powernow_table
(braket
id|index
)braket
dot
id|index
op_amp
l_int|0xFF
suffix:semicolon
id|vid
op_assign
(paren
id|powernow_table
(braket
id|index
)braket
dot
id|index
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
suffix:semicolon
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
id|rdmsrl
(paren
id|MSR_K7_FID_VID_STATUS
comma
id|fidvidstatus.val
)paren
suffix:semicolon
id|cfid
op_assign
id|fidvidstatus.bits.CFID
suffix:semicolon
id|freqs.old
op_assign
id|fsb
op_star
id|fid_codes
(braket
id|cfid
)braket
op_div
l_int|10
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|powernow_table
(braket
id|index
)braket
dot
id|frequency
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
multiline_comment|/* Now do the magic poking into the MSRs.  */
r_if
c_cond
(paren
id|have_a0
op_eq
l_int|1
)paren
multiline_comment|/* A0 errata 5 */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freqs.old
OG
id|freqs
dot
r_new
)paren
(brace
multiline_comment|/* Going down, so change FID first */
id|change_FID
c_func
(paren
id|fid
)paren
suffix:semicolon
id|change_VID
c_func
(paren
id|vid
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Going up, so change VID first */
id|change_VID
c_func
(paren
id|vid
)paren
suffix:semicolon
id|change_FID
c_func
(paren
id|fid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|have_a0
op_eq
l_int|1
)paren
id|local_irq_enable
c_func
(paren
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
)brace
macro_line|#ifdef CONFIG_ACPI_PROCESSOR
DECL|variable|acpi_processor_perf
r_struct
id|acpi_processor_performance
op_star
id|acpi_processor_perf
suffix:semicolon
DECL|function|powernow_acpi_init
r_static
r_int
id|powernow_acpi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_union
id|powernow_acpi_control_t
id|pc
suffix:semicolon
r_if
c_cond
(paren
id|acpi_processor_perf
op_ne
l_int|NULL
op_logical_and
id|powernow_table
op_ne
l_int|NULL
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err0
suffix:semicolon
)brace
id|acpi_processor_perf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_processor_performance
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_processor_perf
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|acpi_processor_perf
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_processor_performance
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_processor_register_performance
c_func
(paren
id|acpi_processor_perf
comma
l_int|0
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_processor_perf-&gt;control_register.space_id
op_ne
id|ACPI_ADR_SPACE_FIXED_HARDWARE
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_processor_perf-&gt;status_register.space_id
op_ne
id|ACPI_ADR_SPACE_FIXED_HARDWARE
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
id|number_scales
op_assign
id|acpi_processor_perf-&gt;state_count
suffix:semicolon
r_if
c_cond
(paren
id|number_scales
OL
l_int|2
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
id|powernow_table
op_assign
id|kmalloc
c_func
(paren
(paren
id|number_scales
op_plus
l_int|1
)paren
op_star
(paren
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|powernow_table
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err2
suffix:semicolon
)brace
id|memset
c_func
(paren
id|powernow_table
comma
l_int|0
comma
(paren
(paren
id|number_scales
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|cpufreq_frequency_table
)paren
)paren
)paren
suffix:semicolon
id|pc.val
op_assign
(paren
r_int
r_int
)paren
id|acpi_processor_perf-&gt;states
(braket
l_int|0
)braket
dot
id|control
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
id|number_scales
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u8
id|fid
comma
id|vid
suffix:semicolon
r_int
r_int
id|speed
suffix:semicolon
id|pc.val
op_assign
(paren
r_int
r_int
)paren
id|acpi_processor_perf-&gt;states
(braket
id|i
)braket
dot
id|control
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;acpi:  P%d: %d MHz %d mW %d uS control %08x SGTC %d&bslash;n&quot;
comma
id|i
comma
(paren
id|u32
)paren
id|acpi_processor_perf-&gt;states
(braket
id|i
)braket
dot
id|core_frequency
comma
(paren
id|u32
)paren
id|acpi_processor_perf-&gt;states
(braket
id|i
)braket
dot
id|power
comma
(paren
id|u32
)paren
id|acpi_processor_perf-&gt;states
(braket
id|i
)braket
dot
id|transition_latency
comma
(paren
id|u32
)paren
id|acpi_processor_perf-&gt;states
(braket
id|i
)braket
dot
id|control
comma
id|pc.bits.sgtc
)paren
suffix:semicolon
id|vid
op_assign
id|pc.bits.vid
suffix:semicolon
id|fid
op_assign
id|pc.bits.fid
suffix:semicolon
id|powernow_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|fsb
op_star
id|fid_codes
(braket
id|fid
)braket
op_div
l_int|10
suffix:semicolon
id|powernow_table
(braket
id|i
)braket
dot
id|index
op_assign
id|fid
suffix:semicolon
multiline_comment|/* lower 8 bits */
id|powernow_table
(braket
id|i
)braket
dot
id|index
op_or_assign
(paren
id|vid
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* upper 8 bits */
id|speed
op_assign
id|powernow_table
(braket
id|i
)braket
dot
id|frequency
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fid_codes
(braket
id|fid
)braket
op_mod
l_int|10
)paren
op_eq
l_int|5
)paren
(brace
r_if
c_cond
(paren
id|have_a0
op_eq
l_int|1
)paren
id|powernow_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|CPUFREQ_ENTRY_INVALID
suffix:semicolon
)brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;   FID: 0x%x (%d.%dx [%dMHz])&bslash;t&quot;
comma
id|fid
comma
id|fid_codes
(braket
id|fid
)braket
op_div
l_int|10
comma
id|fid_codes
(braket
id|fid
)braket
op_mod
l_int|10
comma
id|speed
op_div
l_int|1000
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;VID: 0x%x (%d.%03dV)&bslash;n&quot;
comma
id|vid
comma
id|mobile_vid_table
(braket
id|vid
)braket
op_div
l_int|1000
comma
id|mobile_vid_table
(braket
id|vid
)braket
op_mod
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latency
OL
id|pc.bits.sgtc
)paren
id|latency
op_assign
id|pc.bits.sgtc
suffix:semicolon
r_if
c_cond
(paren
id|speed
OL
id|minimum_speed
)paren
id|minimum_speed
op_assign
id|speed
suffix:semicolon
r_if
c_cond
(paren
id|speed
OG
id|maximum_speed
)paren
id|maximum_speed
op_assign
id|speed
suffix:semicolon
)brace
id|powernow_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|CPUFREQ_TABLE_END
suffix:semicolon
id|powernow_table
(braket
id|i
)braket
dot
id|index
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err2
suffix:colon
id|acpi_processor_unregister_performance
c_func
(paren
id|acpi_processor_perf
comma
l_int|0
)paren
suffix:semicolon
id|err1
suffix:colon
id|kfree
c_func
(paren
id|acpi_processor_perf
)paren
suffix:semicolon
id|err0
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;ACPI perflib can not be used in this platform&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_processor_perf
op_assign
l_int|NULL
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else
DECL|function|powernow_acpi_init
r_static
r_int
id|powernow_acpi_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;no support for ACPI processor found.&quot;
l_string|&quot;  Please recompile your kernel with ACPI processor&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
DECL|function|powernow_decode_bios
r_static
r_int
id|powernow_decode_bios
(paren
r_int
id|maxfid
comma
r_int
id|startvid
)paren
(brace
r_struct
id|psb_s
op_star
id|psb
suffix:semicolon
r_struct
id|pst_s
op_star
id|pst
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|etuple
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|etuple
op_assign
id|cpuid_eax
c_func
(paren
l_int|0x80000001
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0xC0000
suffix:semicolon
id|i
OL
l_int|0xffff0
suffix:semicolon
id|i
op_add_assign
l_int|16
)paren
(brace
id|p
op_assign
id|phys_to_virt
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;AMDK7PNOW!&quot;
comma
l_int|10
)paren
op_eq
l_int|0
)paren
(brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Found PSB header at %p&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
id|psb
op_assign
(paren
r_struct
id|psb_s
op_star
)paren
id|p
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Table version: 0x%x&bslash;n&quot;
comma
id|psb-&gt;tableversion
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psb-&gt;tableversion
op_ne
l_int|0x12
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Sorry, only v1.2 tables supported right now&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Flags: 0x%x (&quot;
comma
id|psb-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|psb-&gt;flags
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|dprintk
(paren
l_string|&quot;Mobile&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
(paren
l_string|&quot;Desktop&quot;
)paren
suffix:semicolon
)brace
id|dprintk
(paren
l_string|&quot; voltage regulator)&bslash;n&quot;
)paren
suffix:semicolon
id|latency
op_assign
id|psb-&gt;settlingtime
suffix:semicolon
r_if
c_cond
(paren
id|latency
OL
l_int|100
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;BIOS set settling time to %d microseconds.&quot;
l_string|&quot;Should be at least 100. Correcting.&bslash;n&quot;
comma
id|latency
)paren
suffix:semicolon
id|latency
op_assign
l_int|100
suffix:semicolon
)brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Settling Time: %d microseconds.&bslash;n&quot;
comma
id|psb-&gt;settlingtime
)paren
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Has %d PST tables. (Only dumping ones relevant to this CPU).&bslash;n&quot;
comma
id|psb-&gt;numpst
)paren
suffix:semicolon
id|p
op_add_assign
r_sizeof
(paren
r_struct
id|psb_s
)paren
suffix:semicolon
id|pst
op_assign
(paren
r_struct
id|pst_s
op_star
)paren
id|p
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
id|psb-&gt;numpst
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pst
op_assign
(paren
r_struct
id|pst_s
op_star
)paren
id|p
suffix:semicolon
id|number_scales
op_assign
id|pst-&gt;numpstates
suffix:semicolon
r_if
c_cond
(paren
(paren
id|etuple
op_eq
id|pst-&gt;cpuid
)paren
op_logical_and
id|check_fsb
c_func
(paren
id|pst-&gt;fsbspeed
)paren
op_logical_and
(paren
id|maxfid
op_eq
id|pst-&gt;maxfid
)paren
op_logical_and
(paren
id|startvid
op_eq
id|pst-&gt;startvid
)paren
)paren
(brace
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;PST:%d (@%p)&bslash;n&quot;
comma
id|i
comma
id|pst
)paren
suffix:semicolon
id|dprintk
(paren
id|KERN_INFO
id|PFX
l_string|&quot; cpuid: 0x%x&bslash;t&quot;
comma
id|pst-&gt;cpuid
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;fsb: %d&bslash;t&quot;
comma
id|pst-&gt;fsbspeed
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;maxFID: 0x%x&bslash;t&quot;
comma
id|pst-&gt;maxfid
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;startvid: 0x%x&bslash;n&quot;
comma
id|pst-&gt;startvid
)paren
suffix:semicolon
id|ret
op_assign
id|get_ranges
(paren
(paren
r_char
op_star
)paren
id|pst
op_plus
r_sizeof
(paren
r_struct
id|pst_s
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|pst
op_plus
r_sizeof
(paren
r_struct
id|pst_s
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|number_scales
suffix:semicolon
id|j
op_increment
)paren
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;No PST tables match this cpuid (0x%x)&bslash;n&quot;
comma
id|etuple
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;This is indicative of a broken BIOS.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|powernow_target
r_static
r_int
id|powernow_target
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
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
id|powernow_table
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
id|change_speed
c_func
(paren
id|newstate
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|powernow_verify
r_static
r_int
id|powernow_verify
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
id|powernow_table
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We use the fact that the bus frequency is somehow&n; * a multiple of 100000/3 khz, then we compute sgtc according&n; * to this multiple.&n; * That way, we match more how AMD thinks all of that work.&n; * We will then get the same kind of behaviour already tested under&n; * the &quot;well-known&quot; other OS.&n; */
DECL|function|fixup_sgtc
r_static
r_int
id|__init
id|fixup_sgtc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sgtc
suffix:semicolon
r_int
r_int
id|m
suffix:semicolon
id|m
op_assign
id|fsb
op_div
l_int|3333
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m
op_mod
l_int|10
)paren
op_ge
l_int|5
)paren
id|m
op_add_assign
l_int|5
suffix:semicolon
id|m
op_div_assign
l_int|10
suffix:semicolon
id|sgtc
op_assign
l_int|100
op_star
id|m
op_star
id|latency
suffix:semicolon
id|sgtc
op_assign
id|sgtc
op_div
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|sgtc
OG
l_int|0xfffff
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;SGTC too large %d&bslash;n&quot;
comma
id|sgtc
)paren
suffix:semicolon
id|sgtc
op_assign
l_int|0xfffff
suffix:semicolon
)brace
r_return
id|sgtc
suffix:semicolon
)brace
DECL|function|powernow_get
r_static
r_int
r_int
id|powernow_get
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_union
id|msr_fidvidstatus
id|fidvidstatus
suffix:semicolon
r_int
r_int
id|cfid
suffix:semicolon
r_if
c_cond
(paren
id|cpu
)paren
r_return
l_int|0
suffix:semicolon
id|rdmsrl
(paren
id|MSR_K7_FID_VID_STATUS
comma
id|fidvidstatus.val
)paren
suffix:semicolon
id|cfid
op_assign
id|fidvidstatus.bits.CFID
suffix:semicolon
r_return
(paren
id|fsb
op_star
id|fid_codes
(braket
id|cfid
)braket
op_div
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|powernow_cpu_init
r_static
r_int
id|__init
id|powernow_cpu_init
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_union
id|msr_fidvidstatus
id|fidvidstatus
suffix:semicolon
r_int
id|result
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
id|rdmsrl
(paren
id|MSR_K7_FID_VID_STATUS
comma
id|fidvidstatus.val
)paren
suffix:semicolon
multiline_comment|/* A K7 with powernow technology is set to max frequency by BIOS */
id|fsb
op_assign
(paren
l_int|10
op_star
id|cpu_khz
)paren
op_div
id|fid_codes
(braket
id|fidvidstatus.bits.CFID
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fsb
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;can not determine bus frequency&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dprintk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;FSB: %3d.%03d MHz&bslash;n&quot;
comma
id|fsb
op_div
l_int|1000
comma
id|fsb
op_mod
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dmi_broken
op_amp
id|BROKEN_CPUFREQ
)paren
op_logical_or
id|powernow_acpi_force
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;PSB/PST known to be broken.  Trying ACPI instead&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
id|powernow_acpi_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|powernow_decode_bios
c_func
(paren
id|fidvidstatus.bits.MFID
comma
id|fidvidstatus.bits.SVID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Trying ACPI perflib&bslash;n&quot;
)paren
suffix:semicolon
id|maximum_speed
op_assign
l_int|0
suffix:semicolon
id|minimum_speed
op_assign
op_minus
l_int|1
suffix:semicolon
id|latency
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|powernow_acpi_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;ACPI and legacy methods failed&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;See http://www.codemonkey.org.uk/projects/cpufreq/powernow-k7.shtml&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* SGTC use the bus clock as timer */
id|latency
op_assign
id|fixup_sgtc
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;SGTC: %d&bslash;n&quot;
comma
id|latency
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Minimum speed %d MHz. Maximum speed %d MHz.&bslash;n&quot;
comma
id|minimum_speed
op_div
l_int|1000
comma
id|maximum_speed
op_div
l_int|1000
)paren
suffix:semicolon
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
l_int|20
op_star
id|latency
op_div
id|fsb
suffix:semicolon
id|policy-&gt;cur
op_assign
id|powernow_get
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|cpufreq_frequency_table_get_attr
c_func
(paren
id|powernow_table
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
id|powernow_table
)paren
suffix:semicolon
)brace
DECL|function|powernow_cpu_exit
r_static
r_int
id|powernow_cpu_exit
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|cpufreq_frequency_table_put_attr
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|powernow_table_attr
r_static
r_struct
id|freq_attr
op_star
id|powernow_table_attr
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
DECL|variable|powernow_driver
r_static
r_struct
id|cpufreq_driver
id|powernow_driver
op_assign
(brace
dot
id|verify
op_assign
id|powernow_verify
comma
dot
id|target
op_assign
id|powernow_target
comma
dot
id|get
op_assign
id|powernow_get
comma
dot
id|init
op_assign
id|powernow_cpu_init
comma
dot
m_exit
op_assign
id|powernow_cpu_exit
comma
dot
id|name
op_assign
l_string|&quot;powernow-k7&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|attr
op_assign
id|powernow_table_attr
comma
)brace
suffix:semicolon
DECL|function|powernow_init
r_static
r_int
id|__init
id|powernow_init
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|check_powernow
c_func
(paren
)paren
op_eq
l_int|0
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
id|powernow_driver
)paren
suffix:semicolon
)brace
DECL|function|powernow_exit
r_static
r_void
id|__exit
id|powernow_exit
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ACPI_PROCESSOR
r_if
c_cond
(paren
id|acpi_processor_perf
)paren
(brace
id|acpi_processor_unregister_performance
c_func
(paren
id|acpi_processor_perf
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|acpi_processor_perf
)paren
suffix:semicolon
)brace
macro_line|#endif
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|powernow_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|powernow_table
)paren
id|kfree
c_func
(paren
id|powernow_table
)paren
suffix:semicolon
)brace
id|module_param
c_func
(paren
id|powernow_acpi_force
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|acpi_force
comma
l_string|&quot;Force ACPI to be used&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Powernow driver for AMD K7 processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|powernow_init
id|late_initcall
c_func
(paren
id|powernow_init
)paren
suffix:semicolon
DECL|variable|powernow_exit
id|module_exit
c_func
(paren
id|powernow_exit
)paren
suffix:semicolon
eof
