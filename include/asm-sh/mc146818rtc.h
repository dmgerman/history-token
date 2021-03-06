multiline_comment|/*&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef _ASM_MC146818RTC_H
DECL|macro|_ASM_MC146818RTC_H
mdefine_line|#define _ASM_MC146818RTC_H
macro_line|#ifdef CONFIG_SH_MPC1211
DECL|macro|_ASM_MC146818RTC_H
macro_line|#undef  _ASM_MC146818RTC_H
DECL|macro|RTC_IRQ
macro_line|#undef  RTC_IRQ
macro_line|#include &lt;asm/mpc1211/mc146818rtc.h&gt;
macro_line|#else
macro_line|#include &lt;asm/rtc.h&gt;
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;1
multiline_comment|/* FIXME:RTC Interrupt feature is not implemented yet. */
DECL|macro|RTC_IRQ
macro_line|#undef  RTC_IRQ
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;0
macro_line|#if defined(CONFIG_CPU_SH3)
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(n)&t;&t;(R64CNT+(n)*2)
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr)&t;&t;__CMOS_READ(addr,b)
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val,addr)&t;__CMOS_WRITE(val,addr,b)
macro_line|#elif defined(CONFIG_SH_SECUREEDGE5410)
macro_line|#include &lt;asm/snapgear/io.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(n)             SECUREEDGE_IOPORT_ADDR
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr)         secureedge5410_cmos_read(addr)
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val,addr)    secureedge5410_cmos_write(val,addr)
r_extern
r_int
r_char
id|secureedge5410_cmos_read
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|secureedge5410_cmos_write
c_func
(paren
r_int
r_char
id|val
comma
r_int
id|addr
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_SH4)
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(n)&t;&t;(R64CNT+(n)*4)
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr)&t;&t;__CMOS_READ(addr,w)
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val,addr)&t;__CMOS_WRITE(val,addr,w)
macro_line|#endif
DECL|macro|__CMOS_READ
mdefine_line|#define __CMOS_READ(addr, s) ({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char val=0, rcr1, rcr2, r64cnt, retry;&t;&t;&t;&bslash;&n;&t;switch(addr) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_SECONDS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RSECCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_SECONDS_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RSECAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MINUTES:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RMINCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MINUTES_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RMINAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_HOURS:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RHRCNT);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_HOURS_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RHRAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_DAY_OF_WEEK:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RWKCNT);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_DAY_OF_MONTH:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RDAYCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MONTH:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_inb(RMONCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_YEAR:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = ctrl_in##s(RYRCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_A: /* RTC_FREQ_SELECT */&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 = ctrl_inb(RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = (rcr2 &amp; RCR2_PESMASK) &gt;&gt; 4;&t;&t;&bslash;&n;&t;&t;&t;rcr1 = ctrl_inb(RCR1);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr1 = (rcr1 &amp; (RCR1_CIE | RCR1_AIE)) | RCR1_AF;&bslash;&n;&t;&t;&t;retry = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ctrl_outb(rcr1, RCR1); /* clear CF */&t;&bslash;&n;&t;&t;&t;&t;r64cnt = ctrl_inb(R64CNT);&t;&t;&bslash;&n;&t;&t;&t;} while((ctrl_inb(RCR1) &amp; RCR1_CF) &amp;&amp; retry++ &lt; 1000);&bslash;&n;&t;&t;&t;r64cnt ^= RTC_BIT_INVERTED;&t;&t;&t;&bslash;&n;&t;&t;&t;if(r64cnt == 0x7f || r64cnt == 0)&t;&t;&bslash;&n;&t;&t;&t;&t;val |= RTC_UIP;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_B:&t;/* RTC_CONTROL */&t;&t;&t;&bslash;&n;&t;&t;&t;rcr1 = ctrl_inb(RCR1);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 = ctrl_inb(RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if(rcr1 &amp; RCR1_CIE)&t;val |= RTC_UIE;&t;&t;&bslash;&n;&t;&t;&t;if(rcr1 &amp; RCR1_AIE)&t;val |= RTC_AIE;&t;&t;&bslash;&n;&t;&t;&t;if(rcr2 &amp; RCR2_PESMASK)&t;val |= RTC_PIE;&t;&t;&bslash;&n;&t;&t;&t;if(!(rcr2 &amp; RCR2_START))val |= RTC_SET;&t;&t;&bslash;&n;&t;&t;&t;val |= RTC_24H;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_C:&t;/* RTC_INTR_FLAGS */&t;&t;&t;&bslash;&n;&t;&t;&t;rcr1 = ctrl_inb(RCR1);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr1 &amp;= ~(RCR1_CF | RCR1_AF);&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(rcr1, RCR1);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 = ctrl_inb(RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 &amp;= ~RCR2_PEF;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(rcr2, RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_D:&t;/* RTC_VALID */&t;&t;&t;&t;&bslash;&n;&t;&t;&t;/* Always valid ... */&t;&t;&t;&t;&bslash;&n;&t;&t;&t;val = RTC_VRT;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;val;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__CMOS_WRITE
mdefine_line|#define __CMOS_WRITE(val, addr, s) ({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char rcr1,rcr2;&t;&t;&t;&t;&t;&bslash;&n;&t;switch(addr) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_SECONDS:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RSECCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_SECONDS_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RSECAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MINUTES:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RMINCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MINUTES_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RMINAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_HOURS:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RHRCNT);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_HOURS_ALARM:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RHRAR);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_DAY_OF_WEEK:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RWKCNT);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_DAY_OF_MONTH:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RDAYCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_MONTH:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(val, RMONCNT);&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_YEAR:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_out##s((ctrl_in##s(RYRCNT) &amp; 0xff00) | (val &amp; 0xff), RYRCNT);&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_A: /* RTC_FREQ_SELECT */&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 = ctrl_inb(RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if((val &amp; RTC_DIV_CTL) == RTC_DIV_RESET2)&t;&bslash;&n;&t;&t;&t;&t;rcr2 |= RCR2_RESET;&t;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(rcr2, RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_B:&t;/* RTC_CONTROL */&t;&t;&t;&bslash;&n;&t;&t;&t;rcr1 = (ctrl_inb(RCR1) &amp; 0x99) | RCR1_AF;&t;&bslash;&n;&t;&t;&t;if(val &amp; RTC_AIE) rcr1 |= RCR1_AIE;&t;&t;&bslash;&n;&t;&t;&t;else              rcr1 &amp;= ~RCR1_AIE;&t;&t;&bslash;&n;&t;&t;&t;if(val &amp; RTC_UIE) rcr1 |= RCR1_CIE;&t;&t;&bslash;&n;&t;&t;&t;else              rcr1 &amp;= ~RCR1_CIE;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(rcr1, RCR1);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;rcr2 = ctrl_inb(RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if(val &amp; RTC_SET) rcr2 &amp;= ~RCR2_START;&t;&t;&bslash;&n;&t;&t;&t;else              rcr2 |= RCR2_START;&t;&t;&bslash;&n;&t;&t;&t;ctrl_outb(rcr2, RCR2);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_C:&t;/* RTC_INTR_FLAGS */&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;case RTC_REG_D:&t;/* RTC_VALID */&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;default:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* CONFIG_SH_MPC1211 */
macro_line|#endif /* _ASM_MC146818RTC_H */
eof
