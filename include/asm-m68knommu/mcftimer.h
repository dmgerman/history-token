multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcftimer.h -- ColdFire internal TIMER support defines.&n; *&n; *&t;(C) Copyright 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; * &t;(C) Copyright 2000, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcftimer_h
DECL|macro|mcftimer_h
mdefine_line|#define&t;mcftimer_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Get address specific defines for this ColdFire member.&n; */
macro_line|#if defined(CONFIG_M5204) || defined(CONFIG_M5206) || defined(CONFIG_M5206e)
DECL|macro|MCFTIMER_BASE1
mdefine_line|#define&t;MCFTIMER_BASE1&t;&t;0x100&t;&t;/* Base address of TIMER1 */
DECL|macro|MCFTIMER_BASE2
mdefine_line|#define&t;MCFTIMER_BASE2&t;&t;0x120&t;&t;/* Base address of TIMER2 */
macro_line|#elif defined(CONFIG_M5272)
DECL|macro|MCFTIMER_BASE1
mdefine_line|#define MCFTIMER_BASE1&t;&t;0x200           /* Base address of TIMER1 */
DECL|macro|MCFTIMER_BASE2
mdefine_line|#define MCFTIMER_BASE2&t;&t;0x220           /* Base address of TIMER2 */
DECL|macro|MCFTIMER_BASE3
mdefine_line|#define MCFTIMER_BASE3&t;&t;0x240           /* Base address of TIMER4 */
DECL|macro|MCFTIMER_BASE4
mdefine_line|#define MCFTIMER_BASE4&t;&t;0x260           /* Base address of TIMER3 */
macro_line|#elif defined(CONFIG_M5249) || defined(CONFIG_M5307) || defined(CONFIG_M5407)
DECL|macro|MCFTIMER_BASE1
mdefine_line|#define MCFTIMER_BASE1&t;&t;0x140           /* Base address of TIMER1 */
DECL|macro|MCFTIMER_BASE2
mdefine_line|#define MCFTIMER_BASE2&t;&t;0x180           /* Base address of TIMER2 */
macro_line|#endif
multiline_comment|/*&n; *&t;Define the TIMER register set addresses.&n; */
DECL|macro|MCFTIMER_TMR
mdefine_line|#define&t;MCFTIMER_TMR&t;&t;0x00&t;&t;/* Timer Mode reg (r/w) */
DECL|macro|MCFTIMER_TRR
mdefine_line|#define&t;MCFTIMER_TRR&t;&t;0x02&t;&t;/* Timer Reference (r/w) */
DECL|macro|MCFTIMER_TCR
mdefine_line|#define&t;MCFTIMER_TCR&t;&t;0x04&t;&t;/* Timer Capture reg (r/w) */
DECL|macro|MCFTIMER_TCN
mdefine_line|#define&t;MCFTIMER_TCN&t;&t;0x06&t;&t;/* Timer Counter reg (r/w) */
DECL|macro|MCFTIMER_TER
mdefine_line|#define&t;MCFTIMER_TER&t;&t;0x11&t;&t;/* Timer Event reg (r/w) */
DECL|struct|mcftimer
r_struct
id|mcftimer
(brace
DECL|member|tmr
r_int
r_int
id|tmr
suffix:semicolon
multiline_comment|/* Timer Mode reg (r/w) */
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:semicolon
DECL|member|trr
r_int
r_int
id|trr
suffix:semicolon
multiline_comment|/* Timer Reference (r/w) */
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:semicolon
DECL|member|tcr
r_int
r_int
id|tcr
suffix:semicolon
multiline_comment|/* Timer Capture reg (r/w) */
DECL|member|reserved3
r_int
r_int
id|reserved3
suffix:semicolon
DECL|member|tcn
r_int
r_int
id|tcn
suffix:semicolon
multiline_comment|/* Timer Counter reg (r/w) */
DECL|member|reserved4
r_int
r_int
id|reserved4
suffix:semicolon
DECL|member|reserved5
r_int
r_char
id|reserved5
suffix:semicolon
DECL|member|ter
r_int
r_char
id|ter
suffix:semicolon
multiline_comment|/* Timer Event reg (r/w) */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Bit definitions for the Timer Mode Register (TMR).&n; *&t;Register bit flags are common accross ColdFires.&n; */
DECL|macro|MCFTIMER_TMR_PREMASK
mdefine_line|#define&t;MCFTIMER_TMR_PREMASK&t;0xff00&t;&t;/* Prescalar mask */
DECL|macro|MCFTIMER_TMR_DISCE
mdefine_line|#define&t;MCFTIMER_TMR_DISCE&t;0x0000&t;&t;/* Disable capture */
DECL|macro|MCFTIMER_TMR_ANYCE
mdefine_line|#define&t;MCFTIMER_TMR_ANYCE&t;0x00c0&t;&t;/* Capture any edge */
DECL|macro|MCFTIMER_TMR_FALLCE
mdefine_line|#define&t;MCFTIMER_TMR_FALLCE&t;0x0080&t;&t;/* Capture fallingedge */
DECL|macro|MCFTIMER_TMR_RISECE
mdefine_line|#define&t;MCFTIMER_TMR_RISECE&t;0x0040&t;&t;/* Capture rising edge */
DECL|macro|MCFTIMER_TMR_ENOM
mdefine_line|#define&t;MCFTIMER_TMR_ENOM&t;0x0020&t;&t;/* Enable output toggle */
DECL|macro|MCFTIMER_TMR_DISOM
mdefine_line|#define&t;MCFTIMER_TMR_DISOM&t;0x0000&t;&t;/* Do single output pulse  */
DECL|macro|MCFTIMER_TMR_ENORI
mdefine_line|#define&t;MCFTIMER_TMR_ENORI&t;0x0010&t;&t;/* Enable ref interrupt */
DECL|macro|MCFTIMER_TMR_DISORI
mdefine_line|#define&t;MCFTIMER_TMR_DISORI&t;0x0000&t;&t;/* Disable ref interrupt */
DECL|macro|MCFTIMER_TMR_RESTART
mdefine_line|#define&t;MCFTIMER_TMR_RESTART&t;0x0008&t;&t;/* Restart counter */
DECL|macro|MCFTIMER_TMR_FREERUN
mdefine_line|#define&t;MCFTIMER_TMR_FREERUN&t;0x0000&t;&t;/* Free running counter */
DECL|macro|MCFTIMER_TMR_CLKTIN
mdefine_line|#define&t;MCFTIMER_TMR_CLKTIN&t;0x0006&t;&t;/* Input clock is TIN */
DECL|macro|MCFTIMER_TMR_CLK16
mdefine_line|#define&t;MCFTIMER_TMR_CLK16&t;0x0004&t;&t;/* Input clock is /16 */
DECL|macro|MCFTIMER_TMR_CLK1
mdefine_line|#define&t;MCFTIMER_TMR_CLK1&t;0x0002&t;&t;/* Input clock is /1 */
DECL|macro|MCFTIMER_TMR_CLKSTOP
mdefine_line|#define&t;MCFTIMER_TMR_CLKSTOP&t;0x0000&t;&t;/* Stop counter */
DECL|macro|MCFTIMER_TMR_ENABLE
mdefine_line|#define&t;MCFTIMER_TMR_ENABLE&t;0x0001&t;&t;/* Enable timer */
DECL|macro|MCFTIMER_TMR_DISABLE
mdefine_line|#define&t;MCFTIMER_TMR_DISABLE&t;0x0000&t;&t;/* Disable timer */
multiline_comment|/*&n; *&t;Bit definitions for the Timer Event Registers (TER).&n; */
DECL|macro|MCFTIMER_TER_CAP
mdefine_line|#define&t;MCFTIMER_TER_CAP&t;0x01&t;&t;/* Capture event */
DECL|macro|MCFTIMER_TER_REF
mdefine_line|#define&t;MCFTIMER_TER_REF&t;0x02&t;&t;/* Refernece event */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcftimer_h */
eof
