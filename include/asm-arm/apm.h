multiline_comment|/* -*- linux-c -*-&n; *&n; * (C) 2003 zecke@handhelds.org&n; *&n; * GPL version 2&n; *&n; * based on arch/arm/kernel/apm.c&n; * factor out the information needed by architectures to provide&n; * apm status&n; *&n; *&n; */
macro_line|#ifndef ARM_ASM_SA1100_APM_H
DECL|macro|ARM_ASM_SA1100_APM_H
mdefine_line|#define ARM_ASM_SA1100_APM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_APM
DECL|macro|APM_AC_OFFLINE
mdefine_line|#define APM_AC_OFFLINE 0
DECL|macro|APM_AC_ONLINE
mdefine_line|#define APM_AC_ONLINE 1
DECL|macro|APM_AC_BACKUP
mdefine_line|#define APM_AC_BACKUP 2
DECL|macro|APM_AC_UNKNOWN
mdefine_line|#define APM_AC_UNKNOWN 0xFF
DECL|macro|APM_BATTERY_STATUS_HIGH
mdefine_line|#define APM_BATTERY_STATUS_HIGH 0
DECL|macro|APM_BATTERY_STATUS_LOW
mdefine_line|#define APM_BATTERY_STATUS_LOW  1
DECL|macro|APM_BATTERY_STATUS_CRITICAL
mdefine_line|#define APM_BATTERY_STATUS_CRITICAL 2
DECL|macro|APM_BATTERY_STATUS_CHARGING
mdefine_line|#define APM_BATTERY_STATUS_CHARGING 3
DECL|macro|APM_BATTERY_STATUS_UNKNOWN
mdefine_line|#define APM_BATTERY_STATUS_UNKNOWN 0xFF
DECL|macro|APM_BATTERY_LIFE_UNKNOWN
mdefine_line|#define APM_BATTERY_LIFE_UNKNOWN 0xFFFF
DECL|macro|APM_BATTERY_LIFE_MINUTES
mdefine_line|#define APM_BATTERY_LIFE_MINUTES 0x8000
DECL|macro|APM_BATTERY_LIFE_VALUE_MASK
mdefine_line|#define APM_BATTERY_LIFE_VALUE_MASK 0x7FFF
multiline_comment|/*&n; * This structure gets filled in by the machine specific &squot;get_power_status&squot;&n; * implementation.  Any fields which are not set default to a safe value.&n; */
DECL|struct|apm_power_info
r_struct
id|apm_power_info
(brace
DECL|member|ac_line_status
r_int
r_char
id|ac_line_status
suffix:semicolon
DECL|member|battery_status
r_int
r_char
id|battery_status
suffix:semicolon
DECL|member|battery_flag
r_int
r_char
id|battery_flag
suffix:semicolon
DECL|member|battery_life
r_int
r_char
id|battery_life
suffix:semicolon
DECL|member|time
r_int
id|time
suffix:semicolon
DECL|member|units
r_int
id|units
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This allows machines to provide their own &quot;apm get power status&quot; function.&n; */
r_extern
r_void
(paren
op_star
id|apm_get_power_status
)paren
(paren
r_struct
id|apm_power_info
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
