macro_line|#ifndef _ASM_RTC_H
DECL|macro|_ASM_RTC_H
mdefine_line|#define _ASM_RTC_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/cpu/rtc.h&gt;
r_extern
r_void
id|sh_rtc_gettimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|ts
)paren
suffix:semicolon
r_extern
r_int
id|sh_rtc_settimeofday
c_func
(paren
r_const
id|time_t
id|secs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|rtc_get_time
)paren
(paren
r_struct
id|timespec
op_star
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|rtc_set_time
)paren
(paren
r_const
id|time_t
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_RTC_H */
eof
