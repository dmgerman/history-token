multiline_comment|/* drivers/char/s3c2410_rtc.c&n; *&n; * Copyright (c) 2004 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 Internal RTC Driver&n; *&n; *  Changelog:&n; *&t;08-Nov-2004&t;BJD&t;Initial creation&n; *&t;12-Nov-2004&t;BJD&t;Added periodic IRQ and PM code&n; *&t;22-Nov-2004&t;BJD&t;Sign-test on alarm code to check for &lt;0&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
macro_line|#include &lt;asm/arch/regs-rtc.h&gt;
multiline_comment|/* need this for the RTC_AF definitions */
macro_line|#include &lt;linux/mc146818rtc.h&gt;
DECL|macro|S3C2410_VA_RTC
macro_line|#undef S3C2410_VA_RTC
DECL|macro|S3C2410_VA_RTC
mdefine_line|#define S3C2410_VA_RTC s3c2410_rtc_base
DECL|variable|s3c2410_rtc_mem
r_static
r_struct
id|resource
op_star
id|s3c2410_rtc_mem
suffix:semicolon
DECL|variable|s3c2410_rtc_base
r_static
r_void
id|__iomem
op_star
id|s3c2410_rtc_base
suffix:semicolon
DECL|variable|s3c2410_rtc_alarmno
r_static
r_int
id|s3c2410_rtc_alarmno
op_assign
id|NO_IRQ
suffix:semicolon
DECL|variable|s3c2410_rtc_tickno
r_static
r_int
id|s3c2410_rtc_tickno
op_assign
id|NO_IRQ
suffix:semicolon
DECL|variable|s3c2410_rtc_freq
r_static
r_int
id|s3c2410_rtc_freq
op_assign
l_int|1
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|s3c2410_rtc_pie_lock
)paren
suffix:semicolon
multiline_comment|/* IRQ Handlers */
DECL|function|s3c2410_rtc_alarmirq
r_static
id|irqreturn_t
id|s3c2410_rtc_alarmirq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|id
comma
r_struct
id|pt_regs
op_star
id|r
)paren
(brace
id|rtc_update
c_func
(paren
l_int|1
comma
id|RTC_AF
op_or
id|RTC_IRQF
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_tickirq
r_static
id|irqreturn_t
id|s3c2410_rtc_tickirq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|id
comma
r_struct
id|pt_regs
op_star
id|r
)paren
(brace
id|rtc_update
c_func
(paren
l_int|1
comma
id|RTC_PF
op_or
id|RTC_IRQF
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* Update control registers */
DECL|function|s3c2410_rtc_setaie
r_static
r_void
id|s3c2410_rtc_setaie
c_func
(paren
r_int
id|to
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: aie=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|to
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCALM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|to
)paren
id|tmp
op_or_assign
id|S3C2410_RTCALM_ALMEN
suffix:semicolon
r_else
id|tmp
op_and_assign
op_complement
id|S3C2410_RTCALM_ALMEN
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
comma
id|S3C2410_RTCALM
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_setpie
r_static
r_void
id|s3c2410_rtc_setpie
c_func
(paren
r_int
id|to
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: pie=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|to
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|s3c2410_rtc_pie_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_TICNT
)paren
op_amp
op_complement
id|S3C2410_TICNT_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|to
)paren
id|tmp
op_or_assign
id|S3C2410_TICNT_ENABLE
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
comma
id|S3C2410_TICNT
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|s3c2410_rtc_pie_lock
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_setfreq
r_static
r_void
id|s3c2410_rtc_setfreq
c_func
(paren
r_int
id|freq
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|s3c2410_rtc_pie_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_TICNT
)paren
op_amp
id|S3C2410_TICNT_ENABLE
suffix:semicolon
id|s3c2410_rtc_freq
op_assign
id|freq
suffix:semicolon
id|tmp
op_or_assign
(paren
l_int|128
op_div
id|freq
)paren
op_minus
l_int|1
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
comma
id|S3C2410_TICNT
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|s3c2410_rtc_pie_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Time read/write */
DECL|function|s3c2410_rtc_gettime
r_static
r_void
id|s3c2410_rtc_gettime
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_tm
)paren
(brace
r_int
r_int
id|have_retried
op_assign
l_int|0
suffix:semicolon
id|retry_get_time
suffix:colon
id|rtc_tm-&gt;tm_min
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCMIN
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_hour
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCHOUR
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_mday
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCDATE
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCMON
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_year
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCYEAR
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_sec
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCSEC
)paren
suffix:semicolon
multiline_comment|/* the only way to work out wether the system was mid-update&n;&t; * when we read it is to check the second counter, and if it&n;&t; * is zero, then we re-try the entire read&n;&t; */
r_if
c_cond
(paren
id|rtc_tm-&gt;tm_sec
op_eq
l_int|0
op_logical_and
op_logical_neg
id|have_retried
)paren
(brace
id|have_retried
op_assign
l_int|1
suffix:semicolon
r_goto
id|retry_get_time
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;read time %02x.%02x.%02x %02x/%02x/%02x&bslash;n&quot;
comma
id|rtc_tm-&gt;tm_year
comma
id|rtc_tm-&gt;tm_mon
comma
id|rtc_tm-&gt;tm_mday
comma
id|rtc_tm-&gt;tm_hour
comma
id|rtc_tm-&gt;tm_min
comma
id|rtc_tm-&gt;tm_sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mday
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_year
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_year
op_add_assign
l_int|100
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_sub_assign
l_int|1
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_settime
r_static
r_int
id|s3c2410_rtc_settime
c_func
(paren
r_struct
id|rtc_time
op_star
id|tm
)paren
(brace
multiline_comment|/* the rtc gets round the y2k problem by just not supporting it */
r_if
c_cond
(paren
id|tm-&gt;tm_year
OL
l_int|100
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_sec
)paren
comma
id|S3C2410_RTCSEC
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_min
)paren
comma
id|S3C2410_RTCMIN
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_hour
)paren
comma
id|S3C2410_RTCHOUR
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_mday
)paren
comma
id|S3C2410_RTCDATE
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_mon
op_plus
l_int|1
)paren
comma
id|S3C2410_RTCMON
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_year
op_minus
l_int|100
)paren
comma
id|S3C2410_RTCYEAR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_getalarm
r_static
r_void
id|s3c2410_rtc_getalarm
c_func
(paren
r_struct
id|rtc_wkalrm
op_star
id|alrm
)paren
(brace
r_struct
id|rtc_time
op_star
id|alm_tm
op_assign
op_amp
id|alrm-&gt;time
suffix:semicolon
r_int
r_int
id|alm_en
suffix:semicolon
id|alm_tm-&gt;tm_sec
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMSEC
)paren
suffix:semicolon
id|alm_tm-&gt;tm_min
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMMIN
)paren
suffix:semicolon
id|alm_tm-&gt;tm_hour
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMHOUR
)paren
suffix:semicolon
id|alm_tm-&gt;tm_mon
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMMON
)paren
suffix:semicolon
id|alm_tm-&gt;tm_mday
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMDATE
)paren
suffix:semicolon
id|alm_tm-&gt;tm_year
op_assign
id|readb
c_func
(paren
id|S3C2410_ALMYEAR
)paren
suffix:semicolon
id|alm_en
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCALM
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;read alarm %02x %02x.%02x.%02x %02x/%02x/%02x&bslash;n&quot;
comma
id|alm_en
comma
id|alm_tm-&gt;tm_year
comma
id|alm_tm-&gt;tm_mon
comma
id|alm_tm-&gt;tm_mday
comma
id|alm_tm-&gt;tm_hour
comma
id|alm_tm-&gt;tm_min
comma
id|alm_tm-&gt;tm_sec
)paren
suffix:semicolon
multiline_comment|/* decode the alarm enable field */
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_SECEN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_sec
)paren
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_sec
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_MINEN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_min
)paren
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_min
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_HOUREN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_hour
)paren
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_hour
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_DAYEN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_mday
)paren
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_mday
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_MONEN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_mon
)paren
suffix:semicolon
id|alm_tm-&gt;tm_mon
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_mon
op_assign
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alm_en
op_amp
id|S3C2410_RTCALM_YEAREN
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|alm_tm-&gt;tm_year
)paren
suffix:semicolon
)brace
r_else
(brace
id|alm_tm-&gt;tm_year
op_assign
l_int|0xffff
suffix:semicolon
)brace
multiline_comment|/* todo - set alrm-&gt;enabled ? */
)brace
DECL|function|s3c2410_rtc_setalarm
r_static
r_int
id|s3c2410_rtc_setalarm
c_func
(paren
r_struct
id|rtc_wkalrm
op_star
id|alrm
)paren
(brace
r_struct
id|rtc_time
op_star
id|tm
op_assign
op_amp
id|alrm-&gt;time
suffix:semicolon
r_int
r_int
id|alrm_en
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc_setalarm: %d, %02x/%02x/%02x %02x.%02x.%02x&bslash;n&quot;
comma
id|alrm-&gt;enabled
comma
id|tm-&gt;tm_mday
op_amp
l_int|0xff
comma
id|tm-&gt;tm_mon
op_amp
l_int|0xff
comma
id|tm-&gt;tm_year
op_amp
l_int|0xff
comma
id|tm-&gt;tm_hour
op_amp
l_int|0xff
comma
id|tm-&gt;tm_min
op_amp
l_int|0xff
comma
id|tm-&gt;tm_sec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alrm-&gt;enabled
op_logical_or
l_int|1
)paren
(brace
id|alrm_en
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCALM
)paren
op_amp
id|S3C2410_RTCALM_ALMEN
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x00
comma
id|S3C2410_RTCALM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tm-&gt;tm_sec
OL
l_int|60
op_logical_and
id|tm-&gt;tm_sec
op_ge
l_int|0
)paren
(brace
id|alrm_en
op_or_assign
id|S3C2410_RTCALM_SECEN
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_sec
)paren
comma
id|S3C2410_ALMSEC
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tm-&gt;tm_min
OL
l_int|60
op_logical_and
id|tm-&gt;tm_min
op_ge
l_int|0
)paren
(brace
id|alrm_en
op_or_assign
id|S3C2410_RTCALM_MINEN
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_min
)paren
comma
id|S3C2410_ALMMIN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tm-&gt;tm_hour
OL
l_int|24
op_logical_and
id|tm-&gt;tm_hour
op_ge
l_int|0
)paren
(brace
id|alrm_en
op_or_assign
id|S3C2410_RTCALM_HOUREN
suffix:semicolon
id|writeb
c_func
(paren
id|BIN2BCD
c_func
(paren
id|tm-&gt;tm_hour
)paren
comma
id|S3C2410_ALMHOUR
)paren
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;setting S3C2410_RTCALM to %08x&bslash;n&quot;
comma
id|alrm_en
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|alrm_en
comma
id|S3C2410_RTCALM
)paren
suffix:semicolon
id|enable_irq_wake
c_func
(paren
id|s3c2410_rtc_alarmno
)paren
suffix:semicolon
)brace
r_else
(brace
id|alrm_en
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCALM
)paren
suffix:semicolon
id|alrm_en
op_and_assign
op_complement
id|S3C2410_RTCALM_ALMEN
suffix:semicolon
id|writeb
c_func
(paren
id|alrm_en
comma
id|S3C2410_RTCALM
)paren
suffix:semicolon
id|disable_irq_wake
c_func
(paren
id|s3c2410_rtc_alarmno
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_ioctl
r_static
r_int
id|s3c2410_rtc_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_AIE_OFF
suffix:colon
r_case
id|RTC_AIE_ON
suffix:colon
id|s3c2410_rtc_setaie
c_func
(paren
(paren
id|cmd
op_eq
id|RTC_AIE_ON
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|RTC_PIE_OFF
suffix:colon
r_case
id|RTC_PIE_ON
suffix:colon
id|s3c2410_rtc_setpie
c_func
(paren
(paren
id|cmd
op_eq
id|RTC_PIE_ON
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|RTC_IRQP_READ
suffix:colon
r_return
id|put_user
c_func
(paren
id|s3c2410_rtc_freq
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|RTC_IRQP_SET
suffix:colon
r_if
c_cond
(paren
id|arg
template_param
l_int|64
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_RESOURCE
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* check for power of 2 */
r_if
c_cond
(paren
(paren
id|arg
op_amp
(paren
id|arg
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc: setting frequency %ld&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
id|s3c2410_rtc_setfreq
c_func
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|RTC_UIE_ON
suffix:colon
r_case
id|RTC_UIE_OFF
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_proc
r_static
r_int
id|s3c2410_rtc_proc
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
r_int
id|rtcalm
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCALM
)paren
suffix:semicolon
r_int
r_int
id|ticnt
op_assign
id|readb
(paren
id|S3C2410_TICNT
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;alarm_IRQ&bslash;t: %s&bslash;n&quot;
comma
(paren
id|rtcalm
op_amp
id|S3C2410_RTCALM_ALMEN
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;periodic_IRQ&bslash;t: %s&bslash;n&quot;
comma
(paren
id|ticnt
op_amp
id|S3C2410_TICNT_ENABLE
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;periodic_freq&bslash;t: %d&bslash;n&quot;
comma
id|s3c2410_rtc_freq
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_open
r_static
r_int
id|s3c2410_rtc_open
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|s3c2410_rtc_alarmno
comma
id|s3c2410_rtc_alarmirq
comma
id|SA_INTERRUPT
comma
l_string|&quot;s3c2410-rtc alarm&quot;
comma
l_int|NULL
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
l_string|&quot;IRQ%d already in use&bslash;n&quot;
comma
id|s3c2410_rtc_alarmno
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|s3c2410_rtc_tickno
comma
id|s3c2410_rtc_tickirq
comma
id|SA_INTERRUPT
comma
l_string|&quot;s3c2410-rtc tick&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IRQ%d already in use&bslash;n&quot;
comma
id|s3c2410_rtc_tickno
)paren
suffix:semicolon
r_goto
id|tick_err
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
id|tick_err
suffix:colon
id|free_irq
c_func
(paren
id|s3c2410_rtc_alarmno
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_release
r_static
r_void
id|s3c2410_rtc_release
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* do not clear AIE here, it may be needed for wake */
id|s3c2410_rtc_setpie
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|s3c2410_rtc_alarmno
comma
l_int|NULL
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|s3c2410_rtc_tickno
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|s3c2410_rtcops
r_static
r_struct
id|rtc_ops
id|s3c2410_rtcops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|s3c2410_rtc_open
comma
dot
id|release
op_assign
id|s3c2410_rtc_release
comma
dot
id|ioctl
op_assign
id|s3c2410_rtc_ioctl
comma
dot
id|read_time
op_assign
id|s3c2410_rtc_gettime
comma
dot
id|set_time
op_assign
id|s3c2410_rtc_settime
comma
dot
id|read_alarm
op_assign
id|s3c2410_rtc_getalarm
comma
dot
id|set_alarm
op_assign
id|s3c2410_rtc_setalarm
comma
dot
id|proc
op_assign
id|s3c2410_rtc_proc
comma
)brace
suffix:semicolon
DECL|function|s3c2410_rtc_enable
r_static
r_void
id|s3c2410_rtc_enable
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|en
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_base
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|en
)paren
(brace
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
op_amp
op_complement
id|S3C2410_RTCCON_RTCEN
comma
id|S3C2410_RTCCON
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_TICNT
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
op_amp
op_complement
id|S3C2410_TICNT_ENABLE
comma
id|S3C2410_TICNT
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* re-enable the device, and check it is ok */
r_if
c_cond
(paren
(paren
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
op_amp
id|S3C2410_RTCCON_RTCEN
)paren
op_eq
l_int|0
)paren
(brace
id|dev_info
c_func
(paren
id|dev
comma
l_string|&quot;rtc disabled, re-enabling&bslash;n&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
op_or
id|S3C2410_RTCCON_RTCEN
comma
id|S3C2410_RTCCON
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
op_amp
id|S3C2410_RTCCON_CNTSEL
)paren
)paren
(brace
id|dev_info
c_func
(paren
id|dev
comma
l_string|&quot;removing S3C2410_RTCCON_CNTSEL&bslash;n&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
op_amp
op_complement
id|S3C2410_RTCCON_CNTSEL
comma
id|S3C2410_RTCCON
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
op_amp
id|S3C2410_RTCCON_CLKRST
)paren
)paren
(brace
id|dev_info
c_func
(paren
id|dev
comma
l_string|&quot;removing S3C2410_RTCCON_CLKRST&bslash;n&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
op_amp
op_complement
id|S3C2410_RTCCON_CLKRST
comma
id|S3C2410_RTCCON
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|s3c2410_rtc_remove
r_static
r_int
id|s3c2410_rtc_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|unregister_rtc
c_func
(paren
op_amp
id|s3c2410_rtcops
)paren
suffix:semicolon
id|s3c2410_rtc_setpie
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|s3c2410_rtc_setaie
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_mem
op_ne
l_int|NULL
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc: releasing s3c2410_rtc_mem&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|s3c2410_rtc_base
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|s3c2410_rtc_mem
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s3c2410_rtc_mem
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_probe
r_static
r_int
id|s3c2410_rtc_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: probe=%p, device=%p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pdev
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* find the IRQs */
id|s3c2410_rtc_tickno
op_assign
id|platform_get_irq
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_tickno
op_le
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;no irq for rtc tick&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|s3c2410_rtc_alarmno
op_assign
id|platform_get_irq
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_alarmno
op_le
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;no irq for alarm&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc: tick irq %d, alarm irq %d&bslash;n&quot;
comma
id|s3c2410_rtc_tickno
comma
id|s3c2410_rtc_alarmno
)paren
suffix:semicolon
multiline_comment|/* get the memory region */
id|res
op_assign
id|platform_get_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_MEM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;failed to get memory region resource&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|s3c2410_rtc_mem
op_assign
id|request_mem_region
c_func
(paren
id|res-&gt;start
comma
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
comma
id|pdev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_mem
op_eq
l_int|NULL
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;failed to reserve memory region&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|exit_err
suffix:semicolon
)brace
id|s3c2410_rtc_base
op_assign
id|ioremap
c_func
(paren
id|res-&gt;start
comma
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s3c2410_rtc_base
op_eq
l_int|NULL
)paren
(brace
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;failed ioremap()&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|exit_err
suffix:semicolon
)brace
id|s3c2410_rtc_mem
op_assign
id|res
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc_base=%p&bslash;n&quot;
comma
id|s3c2410_rtc_base
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc: RTCCON=%02x&bslash;n&quot;
comma
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
)paren
suffix:semicolon
multiline_comment|/* check to see if everything is setup correctly */
id|s3c2410_rtc_enable
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;s3c2410_rtc: RTCCON=%02x&bslash;n&quot;
comma
id|readb
c_func
(paren
id|S3C2410_RTCCON
)paren
)paren
suffix:semicolon
id|s3c2410_rtc_setfreq
c_func
(paren
id|s3c2410_rtc_freq
)paren
suffix:semicolon
multiline_comment|/* register RTC and exit */
id|register_rtc
c_func
(paren
op_amp
id|s3c2410_rtcops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_err
suffix:colon
id|dev_err
c_func
(paren
id|dev
comma
l_string|&quot;error %d during initialisation&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/* S3C2410 RTC Power management control */
DECL|variable|s3c2410_rtc_delta
r_static
r_struct
id|timespec
id|s3c2410_rtc_delta
suffix:semicolon
DECL|variable|ticnt_save
r_static
r_int
id|ticnt_save
suffix:semicolon
DECL|function|s3c2410_rtc_suspend
r_static
r_int
id|s3c2410_rtc_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
r_struct
id|timespec
id|time
suffix:semicolon
id|time.tv_nsec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_POWER_DOWN
)paren
(brace
multiline_comment|/* save TICNT for anyone using periodic interrupts */
id|ticnt_save
op_assign
id|readb
c_func
(paren
id|S3C2410_TICNT
)paren
suffix:semicolon
multiline_comment|/* calculate time delta for suspend */
id|s3c2410_rtc_gettime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
id|rtc_tm_to_time
c_func
(paren
op_amp
id|tm
comma
op_amp
id|time.tv_sec
)paren
suffix:semicolon
id|save_time_delta
c_func
(paren
op_amp
id|s3c2410_rtc_delta
comma
op_amp
id|time
)paren
suffix:semicolon
id|s3c2410_rtc_enable
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_resume
r_static
r_int
id|s3c2410_rtc_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
r_struct
id|timespec
id|time
suffix:semicolon
id|time.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|s3c2410_rtc_enable
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|s3c2410_rtc_gettime
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
id|rtc_tm_to_time
c_func
(paren
op_amp
id|tm
comma
op_amp
id|time.tv_sec
)paren
suffix:semicolon
id|restore_time_delta
c_func
(paren
op_amp
id|s3c2410_rtc_delta
comma
op_amp
id|time
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|ticnt_save
comma
id|S3C2410_TICNT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|s3c2410_rtc_suspend
mdefine_line|#define s3c2410_rtc_suspend NULL
DECL|macro|s3c2410_rtc_resume
mdefine_line|#define s3c2410_rtc_resume  NULL
macro_line|#endif
DECL|variable|s3c2410_rtcdrv
r_static
r_struct
id|device_driver
id|s3c2410_rtcdrv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;s3c2410-rtc&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|s3c2410_rtc_probe
comma
dot
id|remove
op_assign
id|s3c2410_rtc_remove
comma
dot
id|suspend
op_assign
id|s3c2410_rtc_suspend
comma
dot
id|resume
op_assign
id|s3c2410_rtc_resume
comma
)brace
suffix:semicolon
DECL|variable|banner
r_static
r_char
id|__initdata
id|banner
(braket
)braket
op_assign
l_string|&quot;S3C2410 RTC, (c) 2004 Simtec Electronics&bslash;n&quot;
suffix:semicolon
DECL|function|s3c2410_rtc_init
r_static
r_int
id|__init
id|s3c2410_rtc_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|banner
)paren
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|s3c2410_rtcdrv
)paren
suffix:semicolon
)brace
DECL|function|s3c2410_rtc_exit
r_static
r_void
id|__exit
id|s3c2410_rtc_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|s3c2410_rtcdrv
)paren
suffix:semicolon
)brace
DECL|variable|s3c2410_rtc_init
id|module_init
c_func
(paren
id|s3c2410_rtc_init
)paren
suffix:semicolon
DECL|variable|s3c2410_rtc_exit
id|module_exit
c_func
(paren
id|s3c2410_rtc_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;S3C24XX RTC Driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ben Dooks, &lt;ben@simtec.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
