multiline_comment|/* -*- linux-c -*-&n; *&n; * (C) 2003 zecke@handhelds.org&n; *&n; * GPL version 2&n; *&n; * based on arch/arm/kernel/apm.c&n; * factor out the information needed by architectures to provide&n; * apm status&n; *&n; *&n; */
macro_line|#ifndef ARM_ASM_SA1100_APM_H
DECL|macro|ARM_ASM_SA1100_APM_H
mdefine_line|#define ARM_ASM_SA1100_APM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
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
DECL|macro|APM_AC_OFFLINE
mdefine_line|#define APM_AC_OFFLINE&t;&t;&t;0
DECL|macro|APM_AC_ONLINE
mdefine_line|#define APM_AC_ONLINE&t;&t;&t;1
DECL|macro|APM_AC_BACKUP
mdefine_line|#define APM_AC_BACKUP&t;&t;&t;2
DECL|macro|APM_AC_UNKNOWN
mdefine_line|#define APM_AC_UNKNOWN&t;&t;&t;0xff
DECL|member|battery_status
r_int
r_char
id|battery_status
suffix:semicolon
DECL|macro|APM_BATTERY_STATUS_HIGH
mdefine_line|#define APM_BATTERY_STATUS_HIGH&t;&t;0
DECL|macro|APM_BATTERY_STATUS_LOW
mdefine_line|#define APM_BATTERY_STATUS_LOW&t;&t;1
DECL|macro|APM_BATTERY_STATUS_CRITICAL
mdefine_line|#define APM_BATTERY_STATUS_CRITICAL&t;2
DECL|macro|APM_BATTERY_STATUS_CHARGING
mdefine_line|#define APM_BATTERY_STATUS_CHARGING&t;3
DECL|macro|APM_BATTERY_STATUS_NOT_PRESENT
mdefine_line|#define APM_BATTERY_STATUS_NOT_PRESENT&t;4
DECL|macro|APM_BATTERY_STATUS_UNKNOWN
mdefine_line|#define APM_BATTERY_STATUS_UNKNOWN&t;0xff
DECL|member|battery_flag
r_int
r_char
id|battery_flag
suffix:semicolon
DECL|macro|APM_BATTERY_FLAG_HIGH
mdefine_line|#define APM_BATTERY_FLAG_HIGH&t;&t;(1 &lt;&lt; 0)
DECL|macro|APM_BATTERY_FLAG_LOW
mdefine_line|#define APM_BATTERY_FLAG_LOW&t;&t;(1 &lt;&lt; 1)
DECL|macro|APM_BATTERY_FLAG_CRITICAL
mdefine_line|#define APM_BATTERY_FLAG_CRITICAL&t;(1 &lt;&lt; 2)
DECL|macro|APM_BATTERY_FLAG_CHARGING
mdefine_line|#define APM_BATTERY_FLAG_CHARGING&t;(1 &lt;&lt; 3)
DECL|macro|APM_BATTERY_FLAG_NOT_PRESENT
mdefine_line|#define APM_BATTERY_FLAG_NOT_PRESENT&t;(1 &lt;&lt; 7)
DECL|macro|APM_BATTERY_FLAG_UNKNOWN
mdefine_line|#define APM_BATTERY_FLAG_UNKNOWN&t;0xff
DECL|member|battery_life
r_int
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
DECL|macro|APM_UNITS_MINS
mdefine_line|#define APM_UNITS_MINS&t;&t;&t;0
DECL|macro|APM_UNITS_SECS
mdefine_line|#define APM_UNITS_SECS&t;&t;&t;1
DECL|macro|APM_UNITS_UNKNOWN
mdefine_line|#define APM_UNITS_UNKNOWN&t;&t;-1
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
multiline_comment|/*&n; * Queue an event (APM_SYS_SUSPEND or APM_CRITICAL_SUSPEND)&n; */
r_void
id|apm_queue_event
c_func
(paren
id|apm_event_t
id|event
)paren
suffix:semicolon
macro_line|#endif
eof
