macro_line|#ifndef _ASM_RTC_H
DECL|macro|_ASM_RTC_H
mdefine_line|#define _ASM_RTC_H
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|rtc_gettimeofday
mdefine_line|#define rtc_gettimeofday sh_mv.mv_rtc_gettimeofday
DECL|macro|rtc_settimeofday
mdefine_line|#define rtc_settimeofday sh_mv.mv_rtc_settimeofday
r_extern
r_void
id|sh_rtc_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
r_extern
r_int
id|sh_rtc_settimeofday
c_func
(paren
r_const
r_struct
id|timeval
op_star
id|tv
)paren
suffix:semicolon
multiline_comment|/* RCR1 Bits */
DECL|macro|RCR1_CF
mdefine_line|#define RCR1_CF&t;&t;0x80&t;/* Carry Flag             */
DECL|macro|RCR1_CIE
mdefine_line|#define RCR1_CIE&t;0x10&t;/* Carry Interrupt Enable */
DECL|macro|RCR1_AIE
mdefine_line|#define RCR1_AIE&t;0x08&t;/* Alarm Interrupt Enable */
DECL|macro|RCR1_AF
mdefine_line|#define RCR1_AF&t;&t;0x01&t;/* Alarm Flag             */
multiline_comment|/* RCR2 Bits */
DECL|macro|RCR2_PEF
mdefine_line|#define RCR2_PEF&t;0x80&t;/* PEriodic interrupt Flag */
DECL|macro|RCR2_PESMASK
mdefine_line|#define RCR2_PESMASK&t;0x70&t;/* Periodic interrupt Set  */
DECL|macro|RCR2_RTCEN
mdefine_line|#define RCR2_RTCEN&t;0x08&t;/* ENable RTC              */
DECL|macro|RCR2_ADJ
mdefine_line|#define RCR2_ADJ&t;0x04&t;/* ADJustment (30-second)  */
DECL|macro|RCR2_RESET
mdefine_line|#define RCR2_RESET&t;0x02&t;/* Reset bit               */
DECL|macro|RCR2_START
mdefine_line|#define RCR2_START&t;0x01&t;/* Start bit               */
macro_line|#if defined(__sh3__)
multiline_comment|/* SH-3 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xfffffec0
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xfffffec2
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xfffffec4
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xfffffec6
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xfffffec8
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xfffffeca
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xfffffecc
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xfffffece
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xfffffed0
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xfffffed2
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xfffffed4
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xfffffed6
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xfffffed8
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xfffffeda
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xfffffedc
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xfffffede
DECL|macro|RTC_BIT_INVERTED
mdefine_line|#define RTC_BIT_INVERTED&t;0&t;/* No bug on SH7708, SH7709A */
macro_line|#elif defined(__SH4__)
multiline_comment|/* SH-4 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xffc80000
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xffc80004
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xffc80008
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xffc8000c
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xffc80010
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xffc80014
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xffc80018
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xffc8001c  /* 16bit */
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xffc80020
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xffc80024
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xffc80028
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xffc8002c
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xffc80030
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xffc80034
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xffc80038
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xffc8003c
DECL|macro|RTC_BIT_INVERTED
mdefine_line|#define RTC_BIT_INVERTED&t;0x40&t;/* bug on SH7750, SH7750S */
macro_line|#endif
macro_line|#endif /* _ASM_RTC_H */
eof
