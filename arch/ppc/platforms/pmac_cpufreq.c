multiline_comment|/*&n; *  arch/ppc/platforms/pmac_cpufreq.c&n; *&n; *  Copyright (C) 2002 - 2003 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|macro|DEBUG_FREQ
macro_line|#undef DEBUG_FREQ
r_extern
r_void
id|low_choose_750fx_pll
c_func
(paren
r_int
id|pll
)paren
suffix:semicolon
r_extern
r_void
id|low_sleep_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|openpic_sleep_save_intrs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|openpic_sleep_restore_intrs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_kernel_altivec
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_kernel_fp
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|low_freq
r_static
r_int
r_int
id|low_freq
suffix:semicolon
DECL|variable|hi_freq
r_static
r_int
r_int
id|hi_freq
suffix:semicolon
DECL|variable|cur_freq
r_static
r_int
r_int
id|cur_freq
suffix:semicolon
DECL|variable|cpufreq_uses_pmu
r_static
r_int
id|cpufreq_uses_pmu
suffix:semicolon
DECL|macro|PMAC_CPU_LOW_SPEED
mdefine_line|#define PMAC_CPU_LOW_SPEED&t;1
DECL|macro|PMAC_CPU_HIGH_SPEED
mdefine_line|#define PMAC_CPU_HIGH_SPEED&t;0
multiline_comment|/* There are only two frequency states for each processor. Values&n; * are in kHz for the time being.&n; */
DECL|macro|CPUFREQ_HIGH
mdefine_line|#define CPUFREQ_HIGH                  PMAC_CPU_HIGH_SPEED
DECL|macro|CPUFREQ_LOW
mdefine_line|#define CPUFREQ_LOW                   PMAC_CPU_LOW_SPEED
DECL|variable|pmac_cpu_freqs
r_static
r_struct
id|cpufreq_frequency_table
id|pmac_cpu_freqs
(braket
)braket
op_assign
(brace
(brace
id|CPUFREQ_HIGH
comma
l_int|0
)brace
comma
(brace
id|CPUFREQ_LOW
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
id|CPUFREQ_TABLE_END
)brace
comma
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|wakeup_decrementer
id|wakeup_decrementer
c_func
(paren
r_void
)paren
(brace
id|set_dec
c_func
(paren
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
multiline_comment|/* No currently-supported powerbook has a 601,&n;&t; * so use get_tbl, not native&n;&t; */
id|last_jiffy_stamp
c_func
(paren
l_int|0
)paren
op_assign
id|tb_last_stamp
op_assign
id|get_tbl
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_FREQ
r_static
r_inline
r_void
DECL|function|debug_calc_bogomips
id|debug_calc_bogomips
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This will cause a recalc of bogomips and display the&n;&t; * result. We backup/restore the value to avoid affecting the&n;&t; * core cpufreq framework&squot;s own calculation.&n;&t; */
r_extern
r_void
id|calibrate_delay
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|save_lpj
op_assign
id|loops_per_jiffy
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|loops_per_jiffy
op_assign
id|save_lpj
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Switch CPU speed under 750FX CPU control&n; */
r_static
r_int
id|__pmac
DECL|function|cpu_750fx_cpu_speed
id|cpu_750fx_cpu_speed
c_func
(paren
r_int
id|low_speed
)paren
(brace
macro_line|#ifdef DEBUG_FREQ
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;HID1, before: %x&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
)paren
suffix:semicolon
macro_line|#endif
id|low_choose_750fx_pll
c_func
(paren
id|low_speed
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_FREQ
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;HID1, after: %x&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
)paren
suffix:semicolon
id|debug_calc_bogomips
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Switch CPU speed under PMU control&n; */
r_static
r_int
id|__pmac
DECL|function|pmu_set_cpu_speed
id|pmu_set_cpu_speed
c_func
(paren
r_int
r_int
id|low_speed
)paren
(brace
r_struct
id|adb_request
id|req
suffix:semicolon
r_int
r_int
id|save_l2cr
suffix:semicolon
r_int
r_int
id|save_l3cr
suffix:semicolon
macro_line|#ifdef DEBUG_FREQ
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;HID1, before: %x&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Disable all interrupt sources on openpic */
id|openpic_sleep_save_intrs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Make sure the PMU is idle */
id|pmu_suspend
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Make sure the decrementer won&squot;t interrupt us */
id|asm
r_volatile
(paren
l_string|&quot;mtdec %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x7fffffff
)paren
)paren
suffix:semicolon
multiline_comment|/* Make sure any pending DEC interrupt occuring while we did&n;&t; * the above didn&squot;t re-enable the DEC */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mtdec %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x7fffffff
)paren
)paren
suffix:semicolon
multiline_comment|/* We can now disable MSR_EE */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Giveup the FPU &amp; vec */
id|enable_kernel_fp
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
r_if
c_cond
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_ALTIVEC
)paren
id|enable_kernel_altivec
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
multiline_comment|/* Save &amp; disable L2 and L3 caches */
id|save_l3cr
op_assign
id|_get_L3CR
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* (returns -1 if not available) */
id|save_l2cr
op_assign
id|_get_L2CR
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* (returns -1 if not available) */
r_if
c_cond
(paren
id|save_l3cr
op_ne
l_int|0xffffffff
op_logical_and
(paren
id|save_l3cr
op_amp
id|L3CR_L3E
)paren
op_ne
l_int|0
)paren
id|_set_L3CR
c_func
(paren
id|save_l3cr
op_amp
l_int|0x7fffffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|save_l2cr
op_ne
l_int|0xffffffff
op_logical_and
(paren
id|save_l2cr
op_amp
id|L2CR_L2E
)paren
op_ne
l_int|0
)paren
id|_set_L2CR
c_func
(paren
id|save_l2cr
op_amp
l_int|0x7fffffff
)paren
suffix:semicolon
multiline_comment|/* Send the new speed command. My assumption is that this command&n;&t; * will cause PLL_CFG[0..3] to be changed next time CPU goes to sleep&n;&t; */
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|6
comma
id|PMU_CPU_SPEED
comma
l_char|&squot;W&squot;
comma
l_char|&squot;O&squot;
comma
l_char|&squot;O&squot;
comma
l_char|&squot;F&squot;
comma
id|low_speed
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.complete
)paren
id|pmu_poll
c_func
(paren
)paren
suffix:semicolon
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_SLEEP_STATE
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|low_sleep_handler
c_func
(paren
)paren
suffix:semicolon
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_SLEEP_STATE
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Restore L2 cache */
r_if
c_cond
(paren
id|save_l2cr
op_ne
l_int|0xffffffff
op_logical_and
(paren
id|save_l2cr
op_amp
id|L2CR_L2E
)paren
op_ne
l_int|0
)paren
id|_set_L2CR
c_func
(paren
id|save_l2cr
)paren
suffix:semicolon
multiline_comment|/* Restore L3 cache */
r_if
c_cond
(paren
id|save_l3cr
op_ne
l_int|0xffffffff
op_logical_and
(paren
id|save_l3cr
op_amp
id|L3CR_L3E
)paren
op_ne
l_int|0
)paren
id|_set_L3CR
c_func
(paren
id|save_l3cr
)paren
suffix:semicolon
multiline_comment|/* Restore userland MMU context */
id|set_context
c_func
(paren
id|current-&gt;active_mm-&gt;context
comma
id|current-&gt;active_mm-&gt;pgd
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_FREQ
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;HID1, after: %x&bslash;n&quot;
comma
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Restore decrementer */
id|wakeup_decrementer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Restore interrupts */
id|openpic_sleep_restore_intrs
c_func
(paren
)paren
suffix:semicolon
id|pmu_resume
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Let interrupts flow again ... */
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_FREQ
id|debug_calc_bogomips
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__pmac
DECL|function|do_set_cpu_speed
id|do_set_cpu_speed
c_func
(paren
r_int
id|speed_mode
)paren
(brace
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|freqs.old
op_assign
id|cur_freq
suffix:semicolon
id|freqs
dot
r_new
op_assign
(paren
id|speed_mode
op_eq
id|PMAC_CPU_HIGH_SPEED
)paren
ques
c_cond
id|hi_freq
suffix:colon
id|low_freq
suffix:semicolon
id|freqs.cpu
op_assign
id|smp_processor_id
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
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_uses_pmu
)paren
id|rc
op_assign
id|pmu_set_cpu_speed
c_func
(paren
id|speed_mode
)paren
suffix:semicolon
r_else
id|rc
op_assign
id|cpu_750fx_cpu_speed
c_func
(paren
id|speed_mode
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
id|cur_freq
op_assign
(paren
id|speed_mode
op_eq
id|PMAC_CPU_HIGH_SPEED
)paren
ques
c_cond
id|hi_freq
suffix:colon
id|low_freq
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
id|__pmac
DECL|function|pmac_cpufreq_verify
id|pmac_cpufreq_verify
c_func
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
id|pmac_cpu_freqs
)paren
suffix:semicolon
)brace
r_static
r_int
id|__pmac
DECL|function|pmac_cpufreq_target
id|pmac_cpufreq_target
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
r_int
r_int
id|newstate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
id|pmac_cpu_freqs
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
r_return
id|do_set_cpu_speed
c_func
(paren
id|newstate
)paren
suffix:semicolon
)brace
r_int
r_int
id|__pmac
DECL|function|pmac_get_one_cpufreq
id|pmac_get_one_cpufreq
c_func
(paren
r_int
id|i
)paren
(brace
multiline_comment|/* Supports only one CPU for now */
r_return
(paren
id|i
op_eq
l_int|0
)paren
ques
c_cond
id|cur_freq
suffix:colon
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__pmac
DECL|function|pmac_cpufreq_cpu_init
id|pmac_cpufreq_cpu_init
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
id|ENODEV
suffix:semicolon
id|policy-&gt;policy
op_assign
(paren
id|cur_freq
op_eq
id|low_freq
)paren
ques
c_cond
id|CPUFREQ_POLICY_POWERSAVE
suffix:colon
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
id|policy-&gt;cur
op_assign
id|cur_freq
suffix:semicolon
r_return
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
op_amp
id|pmac_cpu_freqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|variable|pmac_cpufreq_driver
r_static
r_struct
id|cpufreq_driver
id|pmac_cpufreq_driver
op_assign
(brace
dot
id|verify
op_assign
id|pmac_cpufreq_verify
comma
dot
id|target
op_assign
id|pmac_cpufreq_target
comma
dot
id|init
op_assign
id|pmac_cpufreq_cpu_init
comma
dot
id|name
op_assign
l_string|&quot;powermac&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/* Currently, we support the following machines:&n; * &n; *  - Titanium PowerBook 800 (PMU based, 667Mhz &amp; 800Mhz)&n; *  - Titanium PowerBook 500 (PMU based, 300Mhz &amp; 500Mhz)&n; *  - iBook2 500 (PMU based, 400Mhz &amp; 500Mhz)&n; *  - iBook2 700 (CPU based, 400Mhz &amp; 700Mhz, support low voltage)&n; */
r_static
r_int
id|__init
DECL|function|pmac_cpufreq_setup
id|pmac_cpufreq_setup
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpunode
suffix:semicolon
id|u32
op_star
id|value
suffix:semicolon
r_int
id|has_freq_ctl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Assume only one CPU */
id|cpunode
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;cpu&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpunode
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Get current cpu clock freq */
id|value
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|cpunode
comma
l_string|&quot;clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_goto
id|out
suffix:semicolon
id|cur_freq
op_assign
(paren
op_star
id|value
)paren
op_div
l_int|1000
suffix:semicolon
multiline_comment|/* Check for newer machines */
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook3,4&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook3,5&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;MacRISC3&quot;
)paren
)paren
(brace
id|value
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|cpunode
comma
l_string|&quot;min-clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_goto
id|out
suffix:semicolon
id|low_freq
op_assign
(paren
op_star
id|value
)paren
op_div
l_int|1000
suffix:semicolon
multiline_comment|/* The PowerBook G4 12&quot; (PowerBook6,1) has an error in the device-tree&n;&t;&t; * here */
r_if
c_cond
(paren
id|low_freq
OL
l_int|100000
)paren
id|low_freq
op_mul_assign
l_int|10
suffix:semicolon
id|value
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|cpunode
comma
l_string|&quot;max-clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_goto
id|out
suffix:semicolon
id|hi_freq
op_assign
(paren
op_star
id|value
)paren
op_div
l_int|1000
suffix:semicolon
id|has_freq_ctl
op_assign
l_int|1
suffix:semicolon
id|cpufreq_uses_pmu
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Else check for iBook2 500 */
r_else
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook4,1&quot;
)paren
)paren
(brace
multiline_comment|/* We only know about 500Mhz model */
r_if
c_cond
(paren
id|cur_freq
template_param
l_int|550000
)paren
r_goto
id|out
suffix:semicolon
id|hi_freq
op_assign
id|cur_freq
suffix:semicolon
id|low_freq
op_assign
l_int|400000
suffix:semicolon
id|has_freq_ctl
op_assign
l_int|1
suffix:semicolon
id|cpufreq_uses_pmu
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Else check for TiPb 500 */
r_else
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook3,2&quot;
)paren
)paren
(brace
multiline_comment|/* We only know about 500Mhz model */
r_if
c_cond
(paren
id|cur_freq
template_param
l_int|550000
)paren
r_goto
id|out
suffix:semicolon
id|hi_freq
op_assign
id|cur_freq
suffix:semicolon
id|low_freq
op_assign
l_int|300000
suffix:semicolon
id|has_freq_ctl
op_assign
l_int|1
suffix:semicolon
id|cpufreq_uses_pmu
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Else check for 750FX */
r_else
r_if
c_cond
(paren
id|PVR_VER
c_func
(paren
id|mfspr
c_func
(paren
id|PVR
)paren
)paren
op_eq
l_int|0x7000
)paren
(brace
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|cpunode
comma
l_string|&quot;dynamic-power-step&quot;
comma
l_int|NULL
)paren
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|hi_freq
op_assign
id|cur_freq
suffix:semicolon
id|value
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|cpunode
comma
l_string|&quot;reduced-clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
r_goto
id|out
suffix:semicolon
id|low_freq
op_assign
(paren
op_star
id|value
)paren
op_div
l_int|1000
suffix:semicolon
id|cpufreq_uses_pmu
op_assign
l_int|0
suffix:semicolon
id|has_freq_ctl
op_assign
l_int|1
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|has_freq_ctl
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pmac_cpu_freqs
(braket
id|CPUFREQ_LOW
)braket
dot
id|frequency
op_assign
id|low_freq
suffix:semicolon
id|pmac_cpu_freqs
(braket
id|CPUFREQ_HIGH
)braket
dot
id|frequency
op_assign
id|hi_freq
suffix:semicolon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|pmac_cpufreq_driver
)paren
suffix:semicolon
)brace
DECL|variable|pmac_cpufreq_setup
id|module_init
c_func
(paren
id|pmac_cpufreq_setup
)paren
suffix:semicolon
eof
