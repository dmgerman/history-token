multiline_comment|/*&n; *  arch/ppc/platforms/pmac_cpufreq.c&n; *&n; *  Copyright (C) 2002 - 2004 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n; *  Copyright (C) 2004        John Steele Scott &lt;toojays@toojays.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
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
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/hardirq.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/time.h&gt;
multiline_comment|/* WARNING !!! This will cause calibrate_delay() to be called,&n; * but this is an __init function ! So you MUST go edit&n; * init/main.c to make it non-init before enabling DEBUG_FREQ&n; */
DECL|macro|DEBUG_FREQ
macro_line|#undef DEBUG_FREQ
multiline_comment|/*&n; * There is a problem with the core cpufreq code on SMP kernels,&n; * it won&squot;t recalculate the Bogomips properly&n; */
macro_line|#ifdef CONFIG_SMP
macro_line|#warning &quot;WARNING, CPUFREQ not recommended on SMP kernels&quot;
macro_line|#endif
r_extern
r_void
id|low_choose_7447a_dfs
c_func
(paren
r_int
id|dfs
)paren
suffix:semicolon
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
id|openpic_suspend
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
comma
id|u32
id|state
)paren
suffix:semicolon
r_extern
r_void
id|openpic_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
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
multiline_comment|/*&n; * Currently, PowerMac cpufreq supports only high &amp; low frequencies&n; * that are set by the firmware&n; */
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
multiline_comment|/*&n; * Different models uses different mecanisms to switch the frequency&n; */
DECL|variable|set_speed_proc
r_static
r_int
(paren
op_star
id|set_speed_proc
)paren
(paren
r_int
id|low_speed
)paren
suffix:semicolon
multiline_comment|/*&n; * Some definitions used by the various speedprocs&n; */
DECL|variable|voltage_gpio
r_static
id|u32
id|voltage_gpio
suffix:semicolon
DECL|variable|frequency_gpio
r_static
id|u32
id|frequency_gpio
suffix:semicolon
DECL|variable|slew_done_gpio
r_static
id|u32
id|slew_done_gpio
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
DECL|function|wakeup_decrementer
r_static
r_inline
r_void
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
DECL|function|debug_calc_bogomips
r_static
r_inline
r_void
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
macro_line|#endif /* DEBUG_FREQ */
multiline_comment|/* Switch CPU speed under 750FX CPU control&n; */
DECL|function|cpu_750fx_cpu_speed
r_static
r_int
id|__pmac
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
macro_line|#ifdef CONFIG_6xx
id|low_choose_750fx_pll
c_func
(paren
id|low_speed
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Switch CPU speed using DFS */
DECL|function|dfs_set_cpu_speed
r_static
r_int
id|__pmac
id|dfs_set_cpu_speed
c_func
(paren
r_int
id|low_speed
)paren
(brace
r_if
c_cond
(paren
id|low_speed
op_eq
l_int|0
)paren
(brace
multiline_comment|/* ramping up, set voltage first */
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_WRITE_GPIO
comma
l_int|NULL
comma
id|voltage_gpio
comma
l_int|0x05
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ramping down, enable aack delay first */
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_AACK_DELAY_ENABLE
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* set frequency */
id|low_choose_7447a_dfs
c_func
(paren
id|low_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|low_speed
op_eq
l_int|1
)paren
(brace
multiline_comment|/* ramping down, set voltage last */
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_WRITE_GPIO
comma
l_int|NULL
comma
id|voltage_gpio
comma
l_int|0x04
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ramping up, disable aack delay last */
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_AACK_DELAY_ENABLE
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Switch CPU speed using slewing GPIOs&n; */
DECL|function|gpios_set_cpu_speed
r_static
r_int
id|__pmac
id|gpios_set_cpu_speed
c_func
(paren
r_int
id|low_speed
)paren
(brace
r_int
id|gpio
suffix:semicolon
multiline_comment|/* If ramping up, set voltage first */
r_if
c_cond
(paren
id|low_speed
op_eq
l_int|0
)paren
(brace
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_WRITE_GPIO
comma
l_int|NULL
comma
id|voltage_gpio
comma
l_int|0x05
)paren
suffix:semicolon
multiline_comment|/* Delay is way too big but it&squot;s ok, we schedule */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|100
)paren
suffix:semicolon
)brace
multiline_comment|/* Set frequency */
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_WRITE_GPIO
comma
l_int|NULL
comma
id|frequency_gpio
comma
id|low_speed
ques
c_cond
l_int|0x04
suffix:colon
l_int|0x05
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
r_do
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
l_int|1
)paren
suffix:semicolon
id|gpio
op_assign
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_READ_GPIO
comma
l_int|NULL
comma
id|slew_done_gpio
comma
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|gpio
op_amp
l_int|0x02
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* If ramping down, set voltage last */
r_if
c_cond
(paren
id|low_speed
op_eq
l_int|1
)paren
(brace
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_WRITE_GPIO
comma
l_int|NULL
comma
id|voltage_gpio
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* Delay is way too big but it&squot;s ok, we schedule */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|100
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Switch CPU speed under PMU control&n; */
DECL|function|pmu_set_cpu_speed
r_static
r_int
id|__pmac
id|pmu_set_cpu_speed
c_func
(paren
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
id|preempt_disable
c_func
(paren
)paren
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
id|openpic_suspend
c_func
(paren
l_int|NULL
comma
l_int|1
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
multiline_comment|/* Prepare the northbridge for the speed transition */
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
multiline_comment|/* Call low level code to backup CPU state and recover from&n;&t; * hardware reset&n;&t; */
id|low_sleep_handler
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Restore the northbridge */
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
multiline_comment|/* Restore low level PMU operations */
id|pmu_unlock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Restore decrementer */
id|wakeup_decrementer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Restore interrupts */
id|openpic_resume
c_func
(paren
l_int|NULL
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
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_set_cpu_speed
r_static
r_int
id|__pmac
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
r_if
c_cond
(paren
id|freqs.old
op_eq
id|freqs
dot
r_new
)paren
r_return
l_int|0
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
id|set_speed_proc
c_func
(paren
id|speed_mode
op_eq
id|PMAC_CPU_LOW_SPEED
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
l_int|0
suffix:semicolon
)brace
DECL|function|pmac_cpufreq_verify
r_static
r_int
id|__pmac
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
DECL|function|pmac_cpufreq_target
r_static
r_int
id|__pmac
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
DECL|function|pmac_get_one_cpufreq
r_int
r_int
id|__pmac
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
DECL|function|pmac_cpufreq_cpu_init
r_static
r_int
id|__pmac
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
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
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
DECL|function|read_gpio
r_static
id|u32
id|__pmac
id|read_gpio
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
(brace
id|u32
op_star
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* That works for all keylargos but shall be fixed properly&n;&t; * some day...&n;&t; */
r_return
l_int|0x50
op_plus
(paren
op_star
id|reg
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
DECL|function|pmac_cpufreq_init_MacRISC3
r_static
r_int
id|__pmac
id|pmac_cpufreq_init_MacRISC3
c_func
(paren
r_struct
id|device_node
op_star
id|cpunode
)paren
(brace
r_struct
id|device_node
op_star
id|volt_gpio_np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;voltage-gpio&quot;
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|freq_gpio_np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;frequency-gpio&quot;
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|slew_done_gpio_np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;slewing-done&quot;
)paren
suffix:semicolon
id|u32
op_star
id|value
suffix:semicolon
multiline_comment|/*&n;&t; * Check to see if it&squot;s GPIO driven or PMU only&n;&t; *&n;&t; * The way we extract the GPIO address is slightly hackish, but it&n;&t; * works well enough for now. We need to abstract the whole GPIO&n;&t; * stuff sooner or later anyway&n;&t; */
r_if
c_cond
(paren
id|volt_gpio_np
)paren
id|voltage_gpio
op_assign
id|read_gpio
c_func
(paren
id|volt_gpio_np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq_gpio_np
)paren
id|frequency_gpio
op_assign
id|read_gpio
c_func
(paren
id|freq_gpio_np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slew_done_gpio_np
)paren
id|slew_done_gpio
op_assign
id|read_gpio
c_func
(paren
id|slew_done_gpio_np
)paren
suffix:semicolon
multiline_comment|/* If we use the frequency GPIOs, calculate the min/max speeds based&n;&t; * on the bus frequencies&n;&t; */
r_if
c_cond
(paren
id|frequency_gpio
op_logical_and
id|slew_done_gpio
)paren
(brace
r_int
id|lenp
comma
id|rc
suffix:semicolon
id|u32
op_star
id|freqs
comma
op_star
id|ratio
suffix:semicolon
id|freqs
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
l_string|&quot;bus-frequencies&quot;
comma
op_amp
id|lenp
)paren
suffix:semicolon
id|lenp
op_div_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freqs
op_eq
l_int|NULL
op_logical_or
id|lenp
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: bus-frequencies incorrect or missing&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|ratio
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
l_string|&quot;processor-to-bus-ratio*2&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ratio
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: processor-to-bus-ratio*2 missing&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Get the min/max bus frequencies */
id|low_freq
op_assign
id|min
c_func
(paren
id|freqs
(braket
l_int|0
)braket
comma
id|freqs
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|hi_freq
op_assign
id|max
c_func
(paren
id|freqs
(braket
l_int|0
)braket
comma
id|freqs
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Grrrr.. It _seems_ that the device-tree is lying on the low bus&n;&t;&t; * frequency, it claims it to be around 84Mhz on some models while&n;&t;&t; * it appears to be approx. 101Mhz on all. Let&squot;s hack around here...&n;&t;&t; * fortunately, we don&squot;t need to be too precise&n;&t;&t; */
r_if
c_cond
(paren
id|low_freq
OL
l_int|98000000
)paren
id|low_freq
op_assign
l_int|101000000
suffix:semicolon
multiline_comment|/* Convert those to CPU core clocks */
id|low_freq
op_assign
(paren
id|low_freq
op_star
(paren
op_star
id|ratio
)paren
)paren
op_div
l_int|2000
suffix:semicolon
id|hi_freq
op_assign
(paren
id|hi_freq
op_star
(paren
op_star
id|ratio
)paren
)paren
op_div
l_int|2000
suffix:semicolon
multiline_comment|/* Now we get the frequencies, we read the GPIO to see what is out current&n;&t;&t; * speed&n;&t;&t; */
id|rc
op_assign
id|pmac_call_feature
c_func
(paren
id|PMAC_FTR_READ_GPIO
comma
l_int|NULL
comma
id|frequency_gpio
comma
l_int|0
)paren
suffix:semicolon
id|cur_freq
op_assign
(paren
id|rc
op_amp
l_int|0x01
)paren
ques
c_cond
id|hi_freq
suffix:colon
id|low_freq
suffix:semicolon
id|set_speed_proc
op_assign
id|gpios_set_cpu_speed
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* If we use the PMU, look for the min &amp; max frequencies in the&n;&t; * device-tree&n;&t; */
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
r_return
l_int|1
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
multiline_comment|/* The PowerBook G4 12&quot; (PowerBook6,1) has an error in the device-tree&n;&t; * here */
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
r_return
l_int|1
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
id|set_speed_proc
op_assign
id|pmu_set_cpu_speed
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pmac_cpufreq_init_7447A
r_static
r_int
id|__pmac
id|pmac_cpufreq_init_7447A
c_func
(paren
r_struct
id|device_node
op_star
id|cpunode
)paren
(brace
r_struct
id|device_node
op_star
id|volt_gpio_np
suffix:semicolon
id|u32
op_star
id|reg
suffix:semicolon
multiline_comment|/* OF only reports the high frequency */
id|hi_freq
op_assign
id|cur_freq
suffix:semicolon
id|low_freq
op_assign
id|cur_freq
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|mfspr
c_func
(paren
id|HID1
)paren
op_amp
id|HID1_DFS
)paren
id|cur_freq
op_assign
id|low_freq
suffix:semicolon
r_else
id|cur_freq
op_assign
id|hi_freq
suffix:semicolon
id|volt_gpio_np
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu-vcore-select&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|volt_gpio_np
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: missing cpu-vcore-select gpio&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|reg
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|volt_gpio_np
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|voltage_gpio
op_assign
op_star
id|reg
suffix:semicolon
id|set_speed_proc
op_assign
id|dfs_set_cpu_speed
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Currently, we support the following machines:&n; *&n; *  - Titanium PowerBook 1Ghz (PMU based, 667Mhz &amp; 1Ghz)&n; *  - Titanium PowerBook 800 (PMU based, 667Mhz &amp; 800Mhz)&n; *  - Titanium PowerBook 400 (PMU based, 300Mhz &amp; 400Mhz)&n; *  - Titanium PowerBook 500 (PMU based, 300Mhz &amp; 500Mhz)&n; *  - iBook2 500/600 (PMU based, 400Mhz &amp; 500/600Mhz)&n; *  - iBook2 700 (CPU based, 400Mhz &amp; 700Mhz, support low voltage)&n; *  - Recent MacRISC3 laptops&n; *  - iBook G4s and PowerBook G4s with 7447A CPUs&n; */
DECL|function|pmac_cpufreq_setup
r_static
r_int
id|__init
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
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;nocpufreq&quot;
)paren
)paren
r_return
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
multiline_comment|/*  Check for 7447A based iBook G4 or PowerBook */
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook6,5&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook6,4&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook5,5&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;PowerBook5,4&quot;
)paren
)paren
(brace
id|pmac_cpufreq_init_7447A
c_func
(paren
id|cpunode
)paren
suffix:semicolon
multiline_comment|/* Check for other MacRISC3 machines */
)brace
r_else
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
id|pmac_cpufreq_init_MacRISC3
c_func
(paren
id|cpunode
)paren
suffix:semicolon
multiline_comment|/* Else check for iBook2 500/600 */
)brace
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
id|hi_freq
op_assign
id|cur_freq
suffix:semicolon
id|low_freq
op_assign
l_int|400000
suffix:semicolon
id|set_speed_proc
op_assign
id|pmu_set_cpu_speed
suffix:semicolon
)brace
multiline_comment|/* Else check for TiPb 400 &amp; 500 */
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
multiline_comment|/* We only know about the 400 MHz and the 500Mhz model&n;&t;&t; * they both have 300 MHz as low frequency&n;&t;&t; */
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
id|set_speed_proc
op_assign
id|pmu_set_cpu_speed
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
id|set_speed_proc
op_assign
id|cpu_750fx_cpu_speed
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|set_speed_proc
op_eq
l_int|NULL
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Registering PowerMac CPU frequency driver&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Low: %d Mhz, High: %d Mhz, Boot: %d Mhz&bslash;n&quot;
comma
id|low_freq
op_div
l_int|1000
comma
id|hi_freq
op_div
l_int|1000
comma
id|cur_freq
op_div
l_int|1000
)paren
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
