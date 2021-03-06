multiline_comment|/*&n; *  linux/arch/arm/mach-sa1100/cpu-sa1110.c&n; *&n; *  Copyright (C) 2001 Russell King&n; *&n; *  $Id: cpu-sa1110.c,v 1.9 2002/07/06 16:53:18 rmk Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Note: there are two erratas that apply to the SA1110 here:&n; *  7 - SDRAM auto-power-up failure (rev A0)&n; * 13 - Corruption of internal register reads/writes following&n; *      SDRAM reads (rev A0, B0, B1)&n; *&n; * We ignore rev. A0 and B0 devices; I don&squot;t think they&squot;re worth supporting.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|variable|sa1110_driver
r_static
r_struct
id|cpufreq_driver
id|sa1110_driver
suffix:semicolon
DECL|struct|sdram_params
r_struct
id|sdram_params
(brace
DECL|member|rows
id|u_char
id|rows
suffix:semicolon
multiline_comment|/* bits&t;&t;&t;&t; */
DECL|member|cas_latency
id|u_char
id|cas_latency
suffix:semicolon
multiline_comment|/* cycles&t;&t;&t; */
DECL|member|tck
id|u_char
id|tck
suffix:semicolon
multiline_comment|/* clock cycle time (ns)&t; */
DECL|member|trcd
id|u_char
id|trcd
suffix:semicolon
multiline_comment|/* activate to r/w (ns)&t;&t; */
DECL|member|trp
id|u_char
id|trp
suffix:semicolon
multiline_comment|/* precharge to activate (ns)&t; */
DECL|member|twr
id|u_char
id|twr
suffix:semicolon
multiline_comment|/* write recovery time (ns)&t; */
DECL|member|refresh
id|u_short
id|refresh
suffix:semicolon
multiline_comment|/* refresh time for array (us)&t; */
)brace
suffix:semicolon
DECL|struct|sdram_info
r_struct
id|sdram_info
(brace
DECL|member|mdcnfg
id|u_int
id|mdcnfg
suffix:semicolon
DECL|member|mdrefr
id|u_int
id|mdrefr
suffix:semicolon
DECL|member|mdcas
id|u_int
id|mdcas
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sdram_params
id|tc59sm716_cl2_params
id|__initdata
op_assign
(brace
dot
id|rows
op_assign
l_int|12
comma
dot
id|tck
op_assign
l_int|10
comma
dot
id|trcd
op_assign
l_int|20
comma
dot
id|trp
op_assign
l_int|20
comma
dot
id|twr
op_assign
l_int|10
comma
dot
id|refresh
op_assign
l_int|64000
comma
dot
id|cas_latency
op_assign
l_int|2
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sdram_params
id|tc59sm716_cl3_params
id|__initdata
op_assign
(brace
dot
id|rows
op_assign
l_int|12
comma
dot
id|tck
op_assign
l_int|8
comma
dot
id|trcd
op_assign
l_int|20
comma
dot
id|trp
op_assign
l_int|20
comma
dot
id|twr
op_assign
l_int|8
comma
dot
id|refresh
op_assign
l_int|64000
comma
dot
id|cas_latency
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sdram_params
id|samsung_k4s641632d_tc75
id|__initdata
op_assign
(brace
dot
id|rows
op_assign
l_int|14
comma
dot
id|tck
op_assign
l_int|9
comma
dot
id|trcd
op_assign
l_int|27
comma
dot
id|trp
op_assign
l_int|20
comma
dot
id|twr
op_assign
l_int|9
comma
dot
id|refresh
op_assign
l_int|64000
comma
dot
id|cas_latency
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sdram_params
id|samsung_km416s4030ct
id|__initdata
op_assign
(brace
dot
id|rows
op_assign
l_int|13
comma
dot
id|tck
op_assign
l_int|8
comma
dot
id|trcd
op_assign
l_int|24
comma
multiline_comment|/* 3 CLKs */
dot
id|trp
op_assign
l_int|24
comma
multiline_comment|/* 3 CLKs */
dot
id|twr
op_assign
l_int|16
comma
multiline_comment|/* Trdl: 2 CLKs */
dot
id|refresh
op_assign
l_int|64000
comma
dot
id|cas_latency
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sdram_params
id|wbond_w982516ah75l_cl3_params
id|__initdata
op_assign
(brace
dot
id|rows
op_assign
l_int|16
comma
dot
id|tck
op_assign
l_int|8
comma
dot
id|trcd
op_assign
l_int|20
comma
dot
id|trp
op_assign
l_int|20
comma
dot
id|twr
op_assign
l_int|8
comma
dot
id|refresh
op_assign
l_int|64000
comma
dot
id|cas_latency
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|variable|sdram_params
r_static
r_struct
id|sdram_params
id|sdram_params
suffix:semicolon
multiline_comment|/*&n; * Given a period in ns and frequency in khz, calculate the number of&n; * cycles of frequency in period.  Note that we round up to the next&n; * cycle, even if we are only slightly over.&n; */
DECL|function|ns_to_cycles
r_static
r_inline
id|u_int
id|ns_to_cycles
c_func
(paren
id|u_int
id|ns
comma
id|u_int
id|khz
)paren
(brace
r_return
(paren
id|ns
op_star
id|khz
op_plus
l_int|999999
)paren
op_div
l_int|1000000
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the MDCAS register bit pattern.&n; */
DECL|function|set_mdcas
r_static
r_inline
r_void
id|set_mdcas
c_func
(paren
id|u_int
op_star
id|mdcas
comma
r_int
id|delayed
comma
id|u_int
id|rcd
)paren
(brace
id|u_int
id|shift
suffix:semicolon
id|rcd
op_assign
l_int|2
op_star
id|rcd
op_minus
l_int|1
suffix:semicolon
id|shift
op_assign
id|delayed
op_plus
l_int|1
op_plus
id|rcd
suffix:semicolon
id|mdcas
(braket
l_int|0
)braket
op_assign
(paren
l_int|1
op_lshift
id|rcd
)paren
op_minus
l_int|1
suffix:semicolon
id|mdcas
(braket
l_int|0
)braket
op_or_assign
l_int|0x55555555
op_lshift
id|shift
suffix:semicolon
id|mdcas
(braket
l_int|1
)braket
op_assign
id|mdcas
(braket
l_int|2
)braket
op_assign
l_int|0x55555555
op_lshift
(paren
id|shift
op_amp
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sdram_calculate_timing
id|sdram_calculate_timing
c_func
(paren
r_struct
id|sdram_info
op_star
id|sd
comma
id|u_int
id|cpu_khz
comma
r_struct
id|sdram_params
op_star
id|sdram
)paren
(brace
id|u_int
id|mem_khz
comma
id|sd_khz
comma
id|trp
comma
id|twr
suffix:semicolon
id|mem_khz
op_assign
id|cpu_khz
op_div
l_int|2
suffix:semicolon
id|sd_khz
op_assign
id|mem_khz
suffix:semicolon
multiline_comment|/*&n;&t; * If SDCLK would invalidate the SDRAM timings,&n;&t; * run SDCLK at half speed.&n;&t; *&n;&t; * CPU steppings prior to B2 must either run the memory at&n;&t; * half speed or use delayed read latching (errata 13).&n;&t; */
r_if
c_cond
(paren
(paren
id|ns_to_cycles
c_func
(paren
id|sdram-&gt;tck
comma
id|sd_khz
)paren
OG
l_int|1
)paren
op_logical_or
(paren
id|CPU_REVISION
OL
id|CPU_SA1110_B2
op_logical_and
id|sd_khz
OL
l_int|62000
)paren
)paren
id|sd_khz
op_div_assign
l_int|2
suffix:semicolon
id|sd-&gt;mdcnfg
op_assign
id|MDCNFG
op_amp
l_int|0x007f007f
suffix:semicolon
id|twr
op_assign
id|ns_to_cycles
c_func
(paren
id|sdram-&gt;twr
comma
id|mem_khz
)paren
suffix:semicolon
multiline_comment|/* trp should always be &gt;1 */
id|trp
op_assign
id|ns_to_cycles
c_func
(paren
id|sdram-&gt;trp
comma
id|mem_khz
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|trp
OL
l_int|1
)paren
id|trp
op_assign
l_int|1
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|trp
op_lshift
l_int|8
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|trp
op_lshift
l_int|24
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|sdram-&gt;cas_latency
op_lshift
l_int|12
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|sdram-&gt;cas_latency
op_lshift
l_int|28
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|twr
op_lshift
l_int|14
suffix:semicolon
id|sd-&gt;mdcnfg
op_or_assign
id|twr
op_lshift
l_int|30
suffix:semicolon
id|sd-&gt;mdrefr
op_assign
id|MDREFR
op_amp
l_int|0xffbffff0
suffix:semicolon
id|sd-&gt;mdrefr
op_or_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|sd_khz
op_ne
id|mem_khz
)paren
id|sd-&gt;mdrefr
op_or_assign
id|MDREFR_K1DB2
suffix:semicolon
multiline_comment|/* initial number of &squot;1&squot;s in MDCAS + 1 */
id|set_mdcas
c_func
(paren
id|sd-&gt;mdcas
comma
id|sd_khz
op_ge
l_int|62000
comma
id|ns_to_cycles
c_func
(paren
id|sdram-&gt;trcd
comma
id|mem_khz
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;MDCNFG: %08x MDREFR: %08x MDCAS0: %08x MDCAS1: %08x MDCAS2: %08x&bslash;n&quot;
comma
id|sd-&gt;mdcnfg
comma
id|sd-&gt;mdrefr
comma
id|sd-&gt;mdcas
(braket
l_int|0
)braket
comma
id|sd-&gt;mdcas
(braket
l_int|1
)braket
comma
id|sd-&gt;mdcas
(braket
l_int|2
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Set the SDRAM refresh rate.&n; */
DECL|function|sdram_set_refresh
r_static
r_inline
r_void
id|sdram_set_refresh
c_func
(paren
id|u_int
id|dri
)paren
(brace
id|MDREFR
op_assign
(paren
id|MDREFR
op_amp
l_int|0xffff000f
)paren
op_or
(paren
id|dri
op_lshift
l_int|4
)paren
suffix:semicolon
(paren
r_void
)paren
id|MDREFR
suffix:semicolon
)brace
multiline_comment|/*&n; * Update the refresh period.  We do this such that we always refresh&n; * the SDRAMs within their permissible period.  The refresh period is&n; * always a multiple of the memory clock (fixed at cpu_clock / 2).&n; *&n; * FIXME: we don&squot;t currently take account of burst accesses here,&n; * but neither do Intels DM nor Angel.&n; */
r_static
r_void
DECL|function|sdram_update_refresh
id|sdram_update_refresh
c_func
(paren
id|u_int
id|cpu_khz
comma
r_struct
id|sdram_params
op_star
id|sdram
)paren
(brace
id|u_int
id|ns_row
op_assign
(paren
id|sdram-&gt;refresh
op_star
l_int|1000
)paren
op_rshift
id|sdram-&gt;rows
suffix:semicolon
id|u_int
id|dri
op_assign
id|ns_to_cycles
c_func
(paren
id|ns_row
comma
id|cpu_khz
op_div
l_int|2
)paren
op_div
l_int|32
suffix:semicolon
macro_line|#ifdef DEBUG
id|mdelay
c_func
(paren
l_int|250
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;new dri value = %d&bslash;n&quot;
comma
id|dri
)paren
suffix:semicolon
macro_line|#endif
id|sdram_set_refresh
c_func
(paren
id|dri
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, set the CPU frequency.  &n; */
DECL|function|sa1110_target
r_static
r_int
id|sa1110_target
c_func
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
r_struct
id|sdram_params
op_star
id|sdram
op_assign
op_amp
id|sdram_params
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_struct
id|sdram_info
id|sd
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|ppcr
comma
id|unused
suffix:semicolon
r_switch
c_cond
(paren
id|relation
)paren
(brace
r_case
id|CPUFREQ_RELATION_L
suffix:colon
id|ppcr
op_assign
id|sa11x0_freq_to_ppcr
c_func
(paren
id|target_freq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sa11x0_ppcr_to_freq
c_func
(paren
id|ppcr
)paren
OG
id|policy-&gt;max
)paren
id|ppcr
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_RELATION_H
suffix:colon
id|ppcr
op_assign
id|sa11x0_freq_to_ppcr
c_func
(paren
id|target_freq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppcr
op_logical_and
(paren
id|sa11x0_ppcr_to_freq
c_func
(paren
id|ppcr
)paren
OG
id|target_freq
)paren
op_logical_and
(paren
id|sa11x0_ppcr_to_freq
c_func
(paren
id|ppcr
op_minus
l_int|1
)paren
op_ge
id|policy-&gt;min
)paren
)paren
id|ppcr
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|freqs.old
op_assign
id|sa11x0_getspeed
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|sa11x0_ppcr_to_freq
c_func
(paren
id|ppcr
)paren
suffix:semicolon
id|freqs.cpu
op_assign
l_int|0
suffix:semicolon
id|sdram_calculate_timing
c_func
(paren
op_amp
id|sd
comma
id|freqs
dot
r_new
comma
id|sdram
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * These values are wrong according to the SA1110 documentation&n;&t; * and errata, but they seem to work.  Need to get a storage&n;&t; * scope on to the SDRAM signals to work out why.&n;&t; */
r_if
c_cond
(paren
id|policy-&gt;max
OL
l_int|147500
)paren
(brace
id|sd.mdrefr
op_or_assign
id|MDREFR_K1DB2
suffix:semicolon
id|sd.mdcas
(braket
l_int|0
)braket
op_assign
l_int|0xaaaaaa7f
suffix:semicolon
)brace
r_else
(brace
id|sd.mdrefr
op_and_assign
op_complement
id|MDREFR_K1DB2
suffix:semicolon
id|sd.mdcas
(braket
l_int|0
)braket
op_assign
l_int|0xaaaaaa9f
suffix:semicolon
)brace
id|sd.mdcas
(braket
l_int|1
)braket
op_assign
l_int|0xaaaaaaaa
suffix:semicolon
id|sd.mdcas
(braket
l_int|2
)braket
op_assign
l_int|0xaaaaaaaa
suffix:semicolon
macro_line|#endif
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The clock could be going away for some time.  Set the SDRAMs&n;&t; * to refresh rapidly (every 64 memory clock cycles).  To get&n;&t; * through the whole array, we need to wait 262144 mclk cycles.&n;&t; * We wait 20ms to be safe.&n;&t; */
id|sdram_set_refresh
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irqs_disabled
c_func
(paren
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|20
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
(brace
id|mdelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reprogram the DRAM timings with interrupts disabled, and&n;&t; * ensure that we are doing this within a complete cache line.&n;&t; * This means that we won&squot;t access SDRAM for the duration of&n;&t; * the programming.&n;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mcr p15, 0, %0, c7, c10, 4&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;&t;&t;b&t;2f&t;&t;&t;&t;&t;&bslash;n&bslash;&n;&t;&t;.align&t;5&t;&t;&t;&t;&t;&bslash;n&bslash;&n;1:&t;&t;str&t;%3, [%1, #0]&t;&t;@ MDCNFG&t;&bslash;n&bslash;&n;&t;&t;str&t;%4, [%1, #28]&t;&t;@ MDREFR&t;&bslash;n&bslash;&n;&t;&t;str&t;%5, [%1, #4]&t;&t;@ MDCAS0&t;&bslash;n&bslash;&n;&t;&t;str&t;%6, [%1, #8]&t;&t;@ MDCAS1&t;&bslash;n&bslash;&n;&t;&t;str&t;%7, [%1, #12]&t;&t;@ MDCAS2&t;&bslash;n&bslash;&n;&t;&t;str&t;%8, [%2, #0]&t;&t;@ PPCR&t;&t;&bslash;n&bslash;&n;&t;&t;ldr&t;%0, [%1, #0]&t;&t;&t;&t;&bslash;n&bslash;&n;&t;&t;b&t;3f&t;&t;&t;&t;&t;&bslash;n&bslash;&n;2:&t;&t;b&t;1b&t;&t;&t;&t;&t;&bslash;n&bslash;&n;3:&t;&t;nop&t;&t;&t;&t;&t;&t;&bslash;n&bslash;&n;&t;&t;nop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|unused
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|MDCNFG
)paren
comma
l_string|&quot;r&quot;
(paren
op_amp
id|PPCR
)paren
comma
l_string|&quot;0&quot;
(paren
id|sd.mdcnfg
)paren
comma
l_string|&quot;r&quot;
(paren
id|sd.mdrefr
)paren
comma
l_string|&quot;r&quot;
(paren
id|sd.mdcas
(braket
l_int|0
)braket
)paren
comma
l_string|&quot;r&quot;
(paren
id|sd.mdcas
(braket
l_int|1
)braket
)paren
comma
l_string|&quot;r&quot;
(paren
id|sd.mdcas
(braket
l_int|2
)braket
)paren
comma
l_string|&quot;r&quot;
(paren
id|ppcr
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now, return the SDRAM refresh back to normal.&n;&t; */
id|sdram_update_refresh
c_func
(paren
id|freqs
dot
r_new
comma
id|sdram
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
DECL|function|sa1110_cpu_init
r_static
r_int
id|__init
id|sa1110_cpu_init
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
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|policy-&gt;cur
op_assign
id|policy-&gt;min
op_assign
id|policy-&gt;max
op_assign
id|sa11x0_getspeed
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.min_freq
op_assign
l_int|59000
suffix:semicolon
id|policy-&gt;cpuinfo.max_freq
op_assign
l_int|287000
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1110_driver
r_static
r_struct
id|cpufreq_driver
id|sa1110_driver
op_assign
(brace
dot
id|flags
op_assign
id|CPUFREQ_STICKY
comma
dot
id|verify
op_assign
id|sa11x0_verify_speed
comma
dot
id|target
op_assign
id|sa1110_target
comma
dot
id|get
op_assign
id|sa11x0_getspeed
comma
dot
id|init
op_assign
id|sa1110_cpu_init
comma
dot
id|name
op_assign
l_string|&quot;sa1110&quot;
comma
)brace
suffix:semicolon
DECL|function|sa1110_clk_init
r_static
r_int
id|__init
id|sa1110_clk_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sdram_params
op_star
id|sdram
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_assabet
c_func
(paren
)paren
)paren
id|sdram
op_assign
op_amp
id|tc59sm716_cl3_params
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_pt_system3
c_func
(paren
)paren
)paren
id|sdram
op_assign
op_amp
id|samsung_k4s641632d_tc75
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_h3100
c_func
(paren
)paren
)paren
id|sdram
op_assign
op_amp
id|samsung_km416s4030ct
suffix:semicolon
r_if
c_cond
(paren
id|sdram
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SDRAM: tck: %d trcd: %d trp: %d&quot;
l_string|&quot; twr: %d refresh: %d cas_latency: %d&bslash;n&quot;
comma
id|sdram-&gt;tck
comma
id|sdram-&gt;trcd
comma
id|sdram-&gt;trp
comma
id|sdram-&gt;twr
comma
id|sdram-&gt;refresh
comma
id|sdram-&gt;cas_latency
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sdram_params
comma
id|sdram
comma
r_sizeof
(paren
id|sdram_params
)paren
)paren
suffix:semicolon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|sa1110_driver
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1110_clk_init
id|arch_initcall
c_func
(paren
id|sa1110_clk_init
)paren
suffix:semicolon
eof
