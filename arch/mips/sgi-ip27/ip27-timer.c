multiline_comment|/*&n; * Copytight (C) 1999, 2000 Ralf Baechle (ralf@gnu.org)&n; * Copytight (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sn/ioc3.h&gt;
macro_line|#include &lt;asm/m48t35.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
macro_line|#include &lt;asm/sn/sn0/hub.h&gt;
multiline_comment|/*&n; * This is a hack; we really need to figure these values out dynamically&n; *&n; * Since 800 ns works very well with various HUB frequencies, such as&n; * 360, 380, 390 and 400 MHZ, we use 800 ns rtc cycle time.&n; *&n; * Ralf: which clock rate is used to feed the counter?&n; */
DECL|macro|NSEC_PER_CYCLE
mdefine_line|#define NSEC_PER_CYCLE&t;&t;800
DECL|macro|CYCLES_PER_SEC
mdefine_line|#define CYCLES_PER_SEC&t;&t;(NSEC_PER_SEC/NSEC_PER_CYCLE)
DECL|macro|CYCLES_PER_JIFFY
mdefine_line|#define CYCLES_PER_JIFFY&t;(CYCLES_PER_SEC/HZ)
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE (tick_nsec / 1000)
DECL|variable|ct_cur
r_static
r_int
r_int
id|ct_cur
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* What counter should be at next timer irq */
DECL|variable|last_rtc_update
r_static
r_int
id|last_rtc_update
suffix:semicolon
multiline_comment|/* Last time the rtc clock got updated */
r_extern
r_volatile
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|function|set_rtc_mmss
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
r_struct
id|m48t35_rtc
op_star
id|rtc
suffix:semicolon
id|nasid_t
id|nid
suffix:semicolon
id|nid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
id|rtc
op_assign
(paren
r_struct
id|m48t35_rtc
op_star
)paren
(paren
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|memory_base
op_plus
id|IOC3_BYTEBUS_DEV0
)paren
suffix:semicolon
id|rtc-&gt;control
op_or_assign
id|M48T35_RTC_READ
suffix:semicolon
id|cmos_minutes
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;min
)paren
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_READ
suffix:semicolon
multiline_comment|/*&n;&t; * Since we&squot;re only adjusting minutes and seconds, don&squot;t interfere with&n;&t; * hour overflow. This avoids messing with unknown time zones but&n;&t; * requires your RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
id|real_seconds
op_assign
id|BIN2BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|real_minutes
op_assign
id|BIN2BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|rtc-&gt;control
op_or_assign
id|M48T35_RTC_SET
suffix:semicolon
id|rtc-&gt;sec
op_assign
id|real_seconds
suffix:semicolon
id|rtc-&gt;min
op_assign
id|real_minutes
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_SET
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_mmss: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|rt_timer_interrupt
r_void
id|rt_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|cpuA
op_assign
(paren
(paren
id|cputoslice
c_func
(paren
id|cpu
)paren
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_int
id|irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* XXX Assign number */
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|again
suffix:colon
id|LOCAL_HUB_S
c_func
(paren
id|cpuA
ques
c_cond
id|PI_RT_PEND_A
suffix:colon
id|PI_RT_PEND_B
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Ack  */
id|ct_cur
(braket
id|cpu
)braket
op_add_assign
id|CYCLES_PER_JIFFY
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|cpuA
ques
c_cond
id|PI_RT_COMPARE_A
suffix:colon
id|PI_RT_COMPARE_B
comma
id|ct_cur
(braket
id|cpu
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LOCAL_HUB_L
c_func
(paren
id|PI_RT_COUNT
)paren
op_ge
id|ct_cur
(braket
id|cpu
)braket
)paren
r_goto
id|again
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
multiline_comment|/* kstat only for bootcpu? */
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|update_process_times
c_func
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n;&t; * If we have an externally synchronized Linux clock, then update&n;&t; * RTC clock accordingly every ~11 minutes. Set_rtc_mmss() has to be&n;&t; * called as close as possible to when a second starts.&n;&t; */
r_if
c_cond
(paren
(paren
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_eq
l_int|0
op_logical_and
id|xtime.tv_sec
OG
id|last_rtc_update
op_plus
l_int|660
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_ge
l_int|500000
op_minus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_le
l_int|500000
op_plus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|rtc_set_time
c_func
(paren
id|xtime.tv_sec
)paren
op_eq
l_int|0
)paren
(brace
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
)brace
r_else
(brace
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
)brace
)brace
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ip27_do_gettimeoffset
r_int
r_int
id|ip27_do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ct_cur1
suffix:semicolon
id|ct_cur1
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|cputonasid
c_func
(paren
l_int|0
)paren
comma
id|PI_RT_COUNT
)paren
op_plus
id|CYCLES_PER_JIFFY
suffix:semicolon
r_return
(paren
id|ct_cur1
op_minus
id|ct_cur
(braket
l_int|0
)braket
)paren
op_star
id|NSEC_PER_CYCLE
op_div
l_int|1000
suffix:semicolon
)brace
multiline_comment|/* Includes for ioc3_init().  */
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubni.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubio.h&gt;
macro_line|#include &lt;asm/pci/bridge.h&gt;
DECL|function|get_m48t35_time
r_static
id|__init
r_int
r_int
id|get_m48t35_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|month
comma
id|date
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_struct
id|m48t35_rtc
op_star
id|rtc
suffix:semicolon
id|nasid_t
id|nid
suffix:semicolon
id|nid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
id|rtc
op_assign
(paren
r_struct
id|m48t35_rtc
op_star
)paren
(paren
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|nid
)paren
op_member_access_from_pointer
id|memory_base
op_plus
id|IOC3_BYTEBUS_DEV0
)paren
suffix:semicolon
id|rtc-&gt;control
op_or_assign
id|M48T35_RTC_READ
suffix:semicolon
id|sec
op_assign
id|rtc-&gt;sec
suffix:semicolon
id|min
op_assign
id|rtc-&gt;min
suffix:semicolon
id|hour
op_assign
id|rtc-&gt;hour
suffix:semicolon
id|date
op_assign
id|rtc-&gt;date
suffix:semicolon
id|month
op_assign
id|rtc-&gt;month
suffix:semicolon
id|year
op_assign
id|rtc-&gt;year
suffix:semicolon
id|rtc-&gt;control
op_and_assign
op_complement
id|M48T35_RTC_READ
suffix:semicolon
id|sec
op_assign
id|BCD2BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|min
op_assign
id|BCD2BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|hour
op_assign
id|BCD2BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|date
op_assign
id|BCD2BIN
c_func
(paren
id|date
)paren
suffix:semicolon
id|month
op_assign
id|BCD2BIN
c_func
(paren
id|month
)paren
suffix:semicolon
id|year
op_assign
id|BCD2BIN
c_func
(paren
id|year
)paren
suffix:semicolon
id|year
op_add_assign
l_int|1970
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|year
comma
id|month
comma
id|date
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
DECL|function|ip27_time_init
r_void
id|__init
id|ip27_time_init
c_func
(paren
r_void
)paren
(brace
id|xtime.tv_sec
op_assign
id|get_m48t35_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|do_gettimeoffset
op_assign
id|ip27_do_gettimeoffset
suffix:semicolon
)brace
DECL|function|cpu_time_init
r_void
id|__init
id|cpu_time_init
c_func
(paren
r_void
)paren
(brace
id|lboard_t
op_star
id|board
suffix:semicolon
id|klcpu_t
op_star
id|cpu
suffix:semicolon
r_int
id|cpuid
suffix:semicolon
multiline_comment|/* Don&squot;t use ARCS.  ARCS is fragile.  Klconfig is simple and sane.  */
id|board
op_assign
id|find_lboard
c_func
(paren
id|KL_CONFIG_INFO
c_func
(paren
id|get_nasid
c_func
(paren
)paren
)paren
comma
id|KLTYPE_IP27
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|board
)paren
id|panic
c_func
(paren
l_string|&quot;Can&squot;t find board info for myself.&quot;
)paren
suffix:semicolon
id|cpuid
op_assign
id|LOCAL_HUB_L
c_func
(paren
id|PI_CPU_NUM
)paren
ques
c_cond
id|IP27_CPU0_INDEX
suffix:colon
id|IP27_CPU1_INDEX
suffix:semicolon
id|cpu
op_assign
(paren
id|klcpu_t
op_star
)paren
id|KLCF_COMP
c_func
(paren
id|board
comma
id|cpuid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu
)paren
id|panic
c_func
(paren
l_string|&quot;No information about myself?&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU %d clock is %dMHz.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu-&gt;cpu_speed
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
id|SRB_TIMOCLK
)paren
suffix:semicolon
)brace
DECL|function|hub_rtc_init
r_void
id|__init
id|hub_rtc_init
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
multiline_comment|/*&n;&t; * We only need to initialize the current node.&n;&t; * If this is not the current node then it is a cpuless&n;&t; * node and timeouts will not happen there.&n;&t; */
r_if
c_cond
(paren
id|get_compact_nodeid
c_func
(paren
)paren
op_eq
id|cnode
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_EN_A
comma
l_int|1
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_EN_B
comma
l_int|1
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_PROF_EN_A
comma
l_int|0
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_PROF_EN_B
comma
l_int|0
)paren
suffix:semicolon
id|ct_cur
(braket
id|cpu
)braket
op_assign
id|CYCLES_PER_JIFFY
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_COMPARE_A
comma
id|ct_cur
(braket
id|cpu
)braket
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_COUNT
comma
l_int|0
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_PEND_A
comma
l_int|0
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_COMPARE_B
comma
id|ct_cur
(braket
id|cpu
)braket
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_COUNT
comma
l_int|0
)paren
suffix:semicolon
id|LOCAL_HUB_S
c_func
(paren
id|PI_RT_PEND_B
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
eof
