multiline_comment|/*&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef __ASM_SPARC_MC146818RTC_H
DECL|macro|__ASM_SPARC_MC146818RTC_H
mdefine_line|#define __ASM_SPARC_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef RTC_PORT
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;1&t;/* RTC operates in binary mode */
macro_line|#endif
multiline_comment|/*&n; * The yet supported machines all access the RTC index register via&n; * an ISA port access but the way to access the date register differs ...&n; */
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) ({ &bslash;&n;outb_p((addr),RTC_PORT(0)); &bslash;&n;inb_p(RTC_PORT(1)); &bslash;&n;})
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val, addr) ({ &bslash;&n;outb_p((addr),RTC_PORT(0)); &bslash;&n;outb_p((val),RTC_PORT(1)); &bslash;&n;})
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ 8
macro_line|#endif /* __ASM_SPARC_MC146818RTC_H */
eof
