multiline_comment|/*&n; *  Registers for the SGS-Thomson M48T35 Timekeeper RAM chip&n; */
macro_line|#ifndef _ASM_M48T35_H
DECL|macro|_ASM_M48T35_H
mdefine_line|#define _ASM_M48T35_H
macro_line|#include &lt;linux/spinlock.h&gt;
r_extern
id|spinlock_t
id|rtc_lock
suffix:semicolon
DECL|struct|m48t35_rtc
r_struct
id|m48t35_rtc
(brace
DECL|member|pad
r_volatile
id|u8
id|pad
(braket
l_int|0x7ff8
)braket
suffix:semicolon
multiline_comment|/* starts at 0x7ff8 */
DECL|member|control
r_volatile
id|u8
id|control
suffix:semicolon
DECL|member|sec
r_volatile
id|u8
id|sec
suffix:semicolon
DECL|member|min
r_volatile
id|u8
id|min
suffix:semicolon
DECL|member|hour
r_volatile
id|u8
id|hour
suffix:semicolon
DECL|member|day
r_volatile
id|u8
id|day
suffix:semicolon
DECL|member|date
r_volatile
id|u8
id|date
suffix:semicolon
DECL|member|month
r_volatile
id|u8
id|month
suffix:semicolon
DECL|member|year
r_volatile
id|u8
id|year
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|M48T35_RTC_SET
mdefine_line|#define M48T35_RTC_SET&t;&t;0x80
DECL|macro|M48T35_RTC_STOPPED
mdefine_line|#define M48T35_RTC_STOPPED&t;0x80
DECL|macro|M48T35_RTC_READ
mdefine_line|#define M48T35_RTC_READ&t;&t;0x40
macro_line|#endif /* _ASM_M48T35_H */
eof
