macro_line|#ifndef _SUN3_INTERSIL_H
DECL|macro|_SUN3_INTERSIL_H
mdefine_line|#define _SUN3_INTERSIL_H
multiline_comment|/* bits 0 and 1 */
DECL|macro|INTERSIL_FREQ_32K
mdefine_line|#define INTERSIL_FREQ_32K        0x00
DECL|macro|INTERSIL_FREQ_1M
mdefine_line|#define INTERSIL_FREQ_1M         0x01
DECL|macro|INTERSIL_FREQ_2M
mdefine_line|#define INTERSIL_FREQ_2M         0x02
DECL|macro|INTERSIL_FREQ_4M
mdefine_line|#define INTERSIL_FREQ_4M         0x03
multiline_comment|/* bit 2 */
DECL|macro|INTERSIL_12H_MODE
mdefine_line|#define INTERSIL_12H_MODE   0x00
DECL|macro|INTERSIL_24H_MODE
mdefine_line|#define INTERSIL_24H_MODE   0x04
multiline_comment|/* bit 3 */
DECL|macro|INTERSIL_STOP
mdefine_line|#define INTERSIL_STOP            0x00
DECL|macro|INTERSIL_RUN
mdefine_line|#define INTERSIL_RUN             0x08
multiline_comment|/* bit 4 */
DECL|macro|INTERSIL_INT_ENABLE
mdefine_line|#define INTERSIL_INT_ENABLE     0x10
DECL|macro|INTERSIL_INT_DISABLE
mdefine_line|#define INTERSIL_INT_DISABLE    0x00
multiline_comment|/* bit 5 */
DECL|macro|INTERSIL_MODE_NORMAL
mdefine_line|#define INTERSIL_MODE_NORMAL     0x00
DECL|macro|INTERSIL_MODE_TEST
mdefine_line|#define INTERSIL_MODE_TEST       0x20
DECL|macro|INTERSIL_HZ_100_MASK
mdefine_line|#define INTERSIL_HZ_100_MASK&t; 0x02
DECL|struct|intersil_dt
r_struct
id|intersil_dt
(brace
DECL|member|csec
id|u_char
id|csec
suffix:semicolon
DECL|member|hour
id|u_char
id|hour
suffix:semicolon
DECL|member|minute
id|u_char
id|minute
suffix:semicolon
DECL|member|second
id|u_char
id|second
suffix:semicolon
DECL|member|month
id|u_char
id|month
suffix:semicolon
DECL|member|day
id|u_char
id|day
suffix:semicolon
DECL|member|year
id|u_char
id|year
suffix:semicolon
DECL|member|weekday
id|u_char
id|weekday
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|intersil_7170
r_struct
id|intersil_7170
(brace
DECL|member|counter
r_struct
id|intersil_dt
id|counter
suffix:semicolon
DECL|member|alarm
r_struct
id|intersil_dt
id|alarm
suffix:semicolon
DECL|member|int_reg
id|u_char
id|int_reg
suffix:semicolon
DECL|member|cmd_reg
id|u_char
id|cmd_reg
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_volatile
r_char
op_star
id|clock_va
suffix:semicolon
DECL|macro|intersil_clock
mdefine_line|#define intersil_clock ((volatile struct intersil_7170 *) clock_va)
DECL|macro|intersil_clear
mdefine_line|#define intersil_clear() (void)intersil_clock-&gt;int_reg
macro_line|#endif
eof
