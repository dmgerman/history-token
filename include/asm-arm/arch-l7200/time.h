multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/time.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.net)&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *   01-02-2000&t;RS&t;Created l7200 version, derived from rpc code&n; *   05-03-2000&t;SJH&t;Complete rewrite&n; */
macro_line|#ifndef _ASM_ARCH_TIME_H
DECL|macro|_ASM_ARCH_TIME_H
mdefine_line|#define _ASM_ARCH_TIME_H
macro_line|#include &lt;asm/arch/irqs.h&gt;
multiline_comment|/*&n; * RTC base register address&n; */
DECL|macro|RTC_BASE
mdefine_line|#define RTC_BASE&t;(IO_BASE_2 + 0x2000)
multiline_comment|/*&n; * RTC registers&n; */
DECL|macro|RTC_RTCDR
mdefine_line|#define RTC_RTCDR&t;(*(volatile unsigned char *) (RTC_BASE + 0x000))
DECL|macro|RTC_RTCMR
mdefine_line|#define RTC_RTCMR&t;(*(volatile unsigned char *) (RTC_BASE + 0x004))
DECL|macro|RTC_RTCS
mdefine_line|#define RTC_RTCS&t;(*(volatile unsigned char *) (RTC_BASE + 0x008))
DECL|macro|RTC_RTCC
mdefine_line|#define RTC_RTCC&t;(*(volatile unsigned char *) (RTC_BASE + 0x008))
DECL|macro|RTC_RTCDV
mdefine_line|#define RTC_RTCDV&t;(*(volatile unsigned char *) (RTC_BASE + 0x00c))
DECL|macro|RTC_RTCCR
mdefine_line|#define RTC_RTCCR&t;(*(volatile unsigned char *) (RTC_BASE + 0x010))
multiline_comment|/*&n; * RTCCR register values&n; */
DECL|macro|RTC_RATE_32
mdefine_line|#define RTC_RATE_32&t;0x00      /* 32 Hz tick */
DECL|macro|RTC_RATE_64
mdefine_line|#define RTC_RATE_64&t;0x10      /* 64 Hz tick */
DECL|macro|RTC_RATE_128
mdefine_line|#define RTC_RATE_128&t;0x20      /* 128 Hz tick */
DECL|macro|RTC_RATE_256
mdefine_line|#define RTC_RATE_256&t;0x30      /* 256 Hz tick */
DECL|macro|RTC_EN_ALARM
mdefine_line|#define RTC_EN_ALARM&t;0x01      /* Enable alarm */
DECL|macro|RTC_EN_TIC
mdefine_line|#define RTC_EN_TIC&t;0x04      /* Enable counter */
DECL|macro|RTC_EN_STWDOG
mdefine_line|#define RTC_EN_STWDOG&t;0x08      /* Enable watchdog */
multiline_comment|/*&n; * Handler for RTC timer interrupt&n; */
DECL|function|timer_interrupt
r_static
r_void
id|timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
id|RTC_RTCC
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear interrupt */
)brace
multiline_comment|/*&n; * Set up RTC timer interrupt, and return the current time in seconds.&n; */
DECL|function|setup_timer
r_static
r_inline
r_void
id|setup_timer
c_func
(paren
r_void
)paren
(brace
id|RTC_RTCC
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear interrupt */
id|timer_irq.handler
op_assign
id|timer_interrupt
suffix:semicolon
id|setup_arm_irq
c_func
(paren
id|IRQ_RTC_TICK
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
id|RTC_RTCCR
op_assign
id|RTC_RATE_128
op_or
id|RTC_EN_TIC
suffix:semicolon
multiline_comment|/* Set rate and enable timer */
)brace
macro_line|#endif
eof
