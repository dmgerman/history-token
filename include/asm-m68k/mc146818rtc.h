multiline_comment|/*&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef _ASM_MC146818RTC_H
DECL|macro|_ASM_MC146818RTC_H
mdefine_line|#define _ASM_MC146818RTC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ATARI
multiline_comment|/* RTC in Atari machines */
macro_line|#include &lt;asm/atarihw.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(TT_RTC_BAS + 2*(x))
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) ({ &bslash;&n;atari_outb_p((addr),RTC_PORT(0)); &bslash;&n;atari_inb_p(RTC_PORT(1)); &bslash;&n;})
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val, addr) ({ &bslash;&n;atari_outb_p((addr),RTC_PORT(0)); &bslash;&n;atari_outb_p((val),RTC_PORT(1)); &bslash;&n;})
macro_line|#endif /* CONFIG_ATARI */
macro_line|#endif /* _ASM_MC146818RTC_H */
eof
