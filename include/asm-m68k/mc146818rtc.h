multiline_comment|/*&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef _ASM_MC146818RTC_H
DECL|macro|_ASM_MC146818RTC_H
mdefine_line|#define _ASM_MC146818RTC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ATARI
multiline_comment|/* RTC in Atari machines */
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|RTC_HAS_IRQ
mdefine_line|#define RTC_HAS_IRQ&t;(ATARIHW_PRESENT(TT_MFP))
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ &t;IRQ_TT_MFP_RTC
DECL|macro|RTC_IRQ_FLAGS
mdefine_line|#define RTC_IRQ_FLAGS&t;IRQ_TYPE_FAST
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(TT_RTC_BAS + 2*(x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0&t;/* TOS uses binary mode, Linux should be able&n;&t;&t;&t;&t; * to deal with both modes */
DECL|macro|RTC_CHECK_DRIVER_INIT
mdefine_line|#define RTC_CHECK_DRIVER_INIT() (MACH_IS_ATARI &amp;&amp; ATARIHW_PRESENT(TT_CLK))
DECL|macro|RTC_MACH_INIT
mdefine_line|#define RTC_MACH_INIT()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;epoch = atari_rtc_year_offset + 1900;&t;&t;&t;&t;&bslash;&n;&t;if (RTC_HAS_IRQ)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    /* select RTC int on H-&gt;L edge */&t;&t;&t;&t;&bslash;&n;&t;    tt_mfp.active_edge &amp;= ~0x40;&t;&t;&t;&t;&bslash;&n;    } while(0)
DECL|macro|RTC_MACH_EXIT
mdefine_line|#define RTC_MACH_EXIT()
multiline_comment|/* On Atari, the year was stored with base 1970 in old TOS versions (before&n; * 3.06). Later, Atari recognized that this broke leap year recognition, and&n; * changed the base to 1968. Medusa and Hades always use the new version. */
DECL|macro|RTC_CENTURY_SWITCH
mdefine_line|#define RTC_CENTURY_SWITCH&t;-1&t;/* no century switch */
DECL|macro|RTC_MINYEAR
mdefine_line|#define RTC_MINYEAR&t;&t;epoch
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) ({ &bslash;&n;outb_p((addr),RTC_PORT(0)); &bslash;&n;inb_p(RTC_PORT(1)); &bslash;&n;})
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val, addr) ({ &bslash;&n;outb_p((addr),RTC_PORT(0)); &bslash;&n;outb_p((val),RTC_PORT(1)); &bslash;&n;})
macro_line|#endif /* CONFIG_ATARI */
macro_line|#endif /* _ASM_MC146818RTC_H */
eof
