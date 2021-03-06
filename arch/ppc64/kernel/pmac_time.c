multiline_comment|/*&n; * Support for periodic interrupts (100 per second) and for getting&n; * the current time from the RTC on Power Macintoshes.&n; *&n; * We use the decrementer register for our periodic interrupts.&n; *&n; * Paul Mackerras&t;August 1996.&n; * Copyright (C) 1996 Paul Mackerras.&n; * Copyright (C) 2003-2005 Benjamin Herrenschmidt.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/smu.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
r_extern
r_void
id|setup_default_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ppc_tb_freq
suffix:semicolon
r_extern
r_int
r_int
id|ppc_proc_freq
suffix:semicolon
multiline_comment|/* Apparently the RTC stores seconds since 1 Jan 1904 */
DECL|macro|RTC_OFFSET
mdefine_line|#define RTC_OFFSET&t;2082844800
multiline_comment|/*&n; * Calibrate the decrementer frequency with the VIA timer 1.&n; */
DECL|macro|VIA_TIMER_FREQ_6
mdefine_line|#define VIA_TIMER_FREQ_6&t;4700000&t;/* time 1 frequency * 6 */
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_extern
r_void
id|to_tm
c_func
(paren
r_int
id|tim
comma
r_struct
id|rtc_time
op_star
id|tm
)paren
suffix:semicolon
DECL|function|pmac_get_rtc_time
r_void
id|__pmac
id|pmac_get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_switch
c_cond
(paren
id|sys_ctrler
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_case
id|SYS_CTRLER_PMU
suffix:colon
(brace
multiline_comment|/* TODO: Move that to a function in the PMU driver */
r_struct
id|adb_request
id|req
suffix:semicolon
r_int
r_int
id|now
suffix:semicolon
r_if
c_cond
(paren
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|1
comma
id|PMU_READ_RTC
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|pmu_wait_complete
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req.reply_len
op_ne
l_int|4
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_get_rtc_time: PMU returned a %d&quot;
l_string|&quot; bytes reply&bslash;n&quot;
comma
id|req.reply_len
)paren
suffix:semicolon
id|now
op_assign
(paren
id|req.reply
(braket
l_int|0
)braket
op_lshift
l_int|24
)paren
op_plus
(paren
id|req.reply
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|req.reply
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
op_plus
id|req.reply
(braket
l_int|3
)braket
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;get: %u -&gt; %u&bslash;n&quot;
comma
(paren
r_int
)paren
id|now
comma
(paren
r_int
)paren
(paren
id|now
op_minus
id|RTC_OFFSET
)paren
)paren
suffix:semicolon
id|now
op_sub_assign
id|RTC_OFFSET
suffix:semicolon
id|to_tm
c_func
(paren
id|now
comma
id|tm
)paren
suffix:semicolon
id|tm-&gt;tm_year
op_sub_assign
l_int|1900
suffix:semicolon
id|tm-&gt;tm_mon
op_sub_assign
l_int|1
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;-&gt; tm_mday: %d, tm_mon: %d, tm_year: %d, %d:%02d:%02d&bslash;n&quot;
comma
id|tm-&gt;tm_mday
comma
id|tm-&gt;tm_mon
comma
id|tm-&gt;tm_year
comma
id|tm-&gt;tm_hour
comma
id|tm-&gt;tm_min
comma
id|tm-&gt;tm_sec
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ADB_PMU */
macro_line|#ifdef CONFIG_PMAC_SMU
r_case
id|SYS_CTRLER_SMU
suffix:colon
id|smu_get_rtc_time
c_func
(paren
id|tm
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_SMU */
r_default
suffix:colon
suffix:semicolon
)brace
)brace
DECL|function|pmac_set_rtc_time
r_int
id|__pmac
id|pmac_set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
r_switch
c_cond
(paren
id|sys_ctrler
)paren
(brace
macro_line|#ifdef CONFIG_ADB_PMU
r_case
id|SYS_CTRLER_PMU
suffix:colon
(brace
multiline_comment|/* TODO: Move that to a function in the PMU driver */
r_struct
id|adb_request
id|req
suffix:semicolon
r_int
r_int
id|nowtime
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;set: tm_mday: %d, tm_mon: %d, tm_year: %d,&quot;
l_string|&quot; %d:%02d:%02d&bslash;n&quot;
comma
id|tm-&gt;tm_mday
comma
id|tm-&gt;tm_mon
comma
id|tm-&gt;tm_year
comma
id|tm-&gt;tm_hour
comma
id|tm-&gt;tm_min
comma
id|tm-&gt;tm_sec
)paren
suffix:semicolon
id|nowtime
op_assign
id|mktime
c_func
(paren
id|tm-&gt;tm_year
op_plus
l_int|1900
comma
id|tm-&gt;tm_mon
op_plus
l_int|1
comma
id|tm-&gt;tm_mday
comma
id|tm-&gt;tm_hour
comma
id|tm-&gt;tm_min
comma
id|tm-&gt;tm_sec
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;-&gt; %u -&gt; %u&bslash;n&quot;
comma
(paren
r_int
)paren
id|nowtime
comma
(paren
r_int
)paren
(paren
id|nowtime
op_plus
id|RTC_OFFSET
)paren
)paren
suffix:semicolon
id|nowtime
op_add_assign
id|RTC_OFFSET
suffix:semicolon
r_if
c_cond
(paren
id|pmu_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|5
comma
id|PMU_SET_RTC
comma
id|nowtime
op_rshift
l_int|24
comma
id|nowtime
op_rshift
l_int|16
comma
id|nowtime
op_rshift
l_int|8
comma
id|nowtime
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pmu_wait_complete
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req.reply_len
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_set_rtc_time: PMU returned a %d&quot;
l_string|&quot; bytes reply&bslash;n&quot;
comma
id|req.reply_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ADB_PMU */
macro_line|#ifdef CONFIG_PMAC_SMU
r_case
id|SYS_CTRLER_SMU
suffix:colon
r_return
id|smu_set_rtc_time
c_func
(paren
id|tm
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_SMU */
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|function|pmac_get_boot_time
r_void
id|__init
id|pmac_get_boot_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
id|pmac_get_rtc_time
c_func
(paren
id|tm
)paren
suffix:semicolon
macro_line|#ifdef disabled__CONFIG_NVRAM
id|s32
id|delta
op_assign
l_int|0
suffix:semicolon
r_int
id|dst
suffix:semicolon
id|delta
op_assign
(paren
(paren
id|s32
)paren
id|pmac_xpram_read
c_func
(paren
id|PMAC_XPRAM_MACHINE_LOC
op_plus
l_int|0x9
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|delta
op_or_assign
(paren
(paren
id|s32
)paren
id|pmac_xpram_read
c_func
(paren
id|PMAC_XPRAM_MACHINE_LOC
op_plus
l_int|0xa
)paren
)paren
op_lshift
l_int|8
suffix:semicolon
id|delta
op_or_assign
id|pmac_xpram_read
c_func
(paren
id|PMAC_XPRAM_MACHINE_LOC
op_plus
l_int|0xb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|delta
op_amp
l_int|0x00800000UL
)paren
id|delta
op_or_assign
l_int|0xFF000000UL
suffix:semicolon
id|dst
op_assign
(paren
(paren
id|pmac_xpram_read
c_func
(paren
id|PMAC_XPRAM_MACHINE_LOC
op_plus
l_int|0x8
)paren
op_amp
l_int|0x80
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GMT Delta read from XPRAM: %d minutes, DST: %s&bslash;n&quot;
comma
id|delta
op_div
l_int|60
comma
id|dst
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Query the OF and get the decr frequency.&n; * This was taken from the pmac time_init() when merging the prep/pmac&n; * time functions.&n; */
DECL|function|pmac_calibrate_decr
r_void
id|__init
id|pmac_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|cpu
suffix:semicolon
r_int
r_int
id|freq
comma
op_star
id|fp
suffix:semicolon
r_struct
id|div_result
id|divres
suffix:semicolon
multiline_comment|/*&n;&t; * The cpu node should have a timebase-frequency property&n;&t; * to tell us the rate at which the decrementer counts.&n;&t; */
id|cpu
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
id|cpu
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;can&squot;t find cpu node in time_init&quot;
)paren
suffix:semicolon
id|fp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;timebase-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;can&squot;t get cpu timebase frequency&quot;
)paren
suffix:semicolon
id|freq
op_assign
op_star
id|fp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;time_init: decrementer frequency = %u.%.6u MHz&bslash;n&quot;
comma
id|freq
op_div
l_int|1000000
comma
id|freq
op_mod
l_int|1000000
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
suffix:semicolon
id|tb_ticks_per_sec
op_assign
id|tb_ticks_per_jiffy
op_star
id|HZ
suffix:semicolon
id|tb_ticks_per_usec
op_assign
id|freq
op_div
l_int|1000000
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
comma
l_int|1000000
)paren
suffix:semicolon
id|div128_by_32
c_func
(paren
l_int|1024
op_star
l_int|1024
comma
l_int|0
comma
id|tb_ticks_per_sec
comma
op_amp
id|divres
)paren
suffix:semicolon
id|tb_to_xs
op_assign
id|divres.result_low
suffix:semicolon
id|ppc_tb_freq
op_assign
id|freq
suffix:semicolon
id|fp
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|cpu
comma
l_string|&quot;clock-frequency&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fp
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;can&squot;t get cpu processor frequency&quot;
)paren
suffix:semicolon
id|ppc_proc_freq
op_assign
op_star
id|fp
suffix:semicolon
id|setup_default_decr
c_func
(paren
)paren
suffix:semicolon
)brace
eof
