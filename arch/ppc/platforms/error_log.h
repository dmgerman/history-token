multiline_comment|/*&n; * BK Id: SCCS/s.error_log.h 1.5 05/17/01 18:14:21 cort&n; */
macro_line|#ifndef __ERROR_LOG_H__
DECL|macro|__ERROR_LOG_H__
mdefine_line|#define __ERROR_LOG_H__
DECL|macro|VERBOSE_ERRORS
mdefine_line|#define VERBOSE_ERRORS&t;&t;1 /* Maybe I enlarge the kernel too much */
DECL|macro|VERBOSE_ERRORS
macro_line|#undef VERBOSE_ERRORS
multiline_comment|/* Event classes */
multiline_comment|/* XXX: Endianess correct? NOW*/
DECL|macro|INTERNAL_ERROR
mdefine_line|#define INTERNAL_ERROR&t;&t;0x80000000 /* set bit 0 */
DECL|macro|EPOW_WARNING
mdefine_line|#define EPOW_WARNING&t;&t;0x40000000 /* set bit 1 */
DECL|macro|POWERMGM_EVENTS
mdefine_line|#define POWERMGM_EVENTS&t;&t;0x20000000 /* set bit 2 */
multiline_comment|/* event-scan returns */
DECL|macro|SEVERITY_FATAL
mdefine_line|#define SEVERITY_FATAL&t;&t;0x5
DECL|macro|SEVERITY_ERROR
mdefine_line|#define SEVERITY_ERROR&t;&t;0x4
DECL|macro|SEVERITY_ERROR_SYNC
mdefine_line|#define SEVERITY_ERROR_SYNC&t;0x3
DECL|macro|SEVERITY_WARNING
mdefine_line|#define SEVERITY_WARNING&t;0x2
DECL|macro|SEVERITY_EVENT
mdefine_line|#define SEVERITY_EVENT&t;&t;0x1
DECL|macro|SEVERITY_NO_ERROR
mdefine_line|#define SEVERITY_NO_ERROR&t;0x0
DECL|macro|DISP_FULLY_RECOVERED
mdefine_line|#define DISP_FULLY_RECOVERED&t;0x0
DECL|macro|DISP_LIMITED_RECOVERY
mdefine_line|#define DISP_LIMITED_RECOVERY&t;0x1
DECL|macro|DISP_NOT_RECOVERED
mdefine_line|#define DISP_NOT_RECOVERED&t;0x2
DECL|macro|PART_PRESENT
mdefine_line|#define PART_PRESENT&t;&t;0x0
DECL|macro|PART_NOT_PRESENT
mdefine_line|#define PART_NOT_PRESENT&t;0x1
DECL|macro|INITIATOR_UNKNOWN
mdefine_line|#define INITIATOR_UNKNOWN&t;0x0
DECL|macro|INITIATOR_CPU
mdefine_line|#define INITIATOR_CPU&t;&t;0x1
DECL|macro|INITIATOR_PCI
mdefine_line|#define INITIATOR_PCI&t;&t;0x2
DECL|macro|INITIATOR_ISA
mdefine_line|#define INITIATOR_ISA&t;&t;0x3
DECL|macro|INITIATOR_MEMORY
mdefine_line|#define INITIATOR_MEMORY&t;0x4
DECL|macro|INITIATOR_POWERMGM
mdefine_line|#define INITIATOR_POWERMGM&t;0x5
DECL|macro|TARGET_UNKNOWN
mdefine_line|#define TARGET_UNKNOWN&t;&t;0x0
DECL|macro|TARGET_CPU
mdefine_line|#define TARGET_CPU&t;&t;0x1
DECL|macro|TARGET_PCI
mdefine_line|#define TARGET_PCI&t;&t;0x2
DECL|macro|TARGET_ISA
mdefine_line|#define TARGET_ISA&t;&t;0x3
DECL|macro|TARGET_MEMORY
mdefine_line|#define TARGET_MEMORY&t;&t;0x4
DECL|macro|TARGET_POWERMGM
mdefine_line|#define TARGET_POWERMGM&t;&t;0x5
DECL|macro|TYPE_RETRY
mdefine_line|#define TYPE_RETRY&t;&t;0x01
DECL|macro|TYPE_TCE_ERR
mdefine_line|#define TYPE_TCE_ERR&t;&t;0x02
DECL|macro|TYPE_INTERN_DEV_FAIL
mdefine_line|#define TYPE_INTERN_DEV_FAIL&t;0x03
DECL|macro|TYPE_TIMEOUT
mdefine_line|#define TYPE_TIMEOUT&t;&t;0x04
DECL|macro|TYPE_DATA_PARITY
mdefine_line|#define TYPE_DATA_PARITY&t;0x05
DECL|macro|TYPE_ADDR_PARITY
mdefine_line|#define TYPE_ADDR_PARITY&t;0x06
DECL|macro|TYPE_CACHE_PARITY
mdefine_line|#define TYPE_CACHE_PARITY&t;0x07
DECL|macro|TYPE_ADDR_INVALID
mdefine_line|#define TYPE_ADDR_INVALID&t;0x08
DECL|macro|TYPE_ECC_UNCORR
mdefine_line|#define TYPE_ECC_UNCORR&t;&t;0x09
DECL|macro|TYPE_ECC_CORR
mdefine_line|#define TYPE_ECC_CORR&t;&t;0x0a
DECL|macro|TYPE_EPOW
mdefine_line|#define TYPE_EPOW&t;&t;0x40
multiline_comment|/* I don&squot;t add PowerMGM events right now, this is a different topic */
DECL|macro|TYPE_PMGM_POWER_SW_ON
mdefine_line|#define TYPE_PMGM_POWER_SW_ON&t;0x60
DECL|macro|TYPE_PMGM_POWER_SW_OFF
mdefine_line|#define TYPE_PMGM_POWER_SW_OFF&t;0x61
DECL|macro|TYPE_PMGM_LID_OPEN
mdefine_line|#define TYPE_PMGM_LID_OPEN&t;0x62
DECL|macro|TYPE_PMGM_LID_CLOSE
mdefine_line|#define TYPE_PMGM_LID_CLOSE&t;0x63
DECL|macro|TYPE_PMGM_SLEEP_BTN
mdefine_line|#define TYPE_PMGM_SLEEP_BTN&t;0x64
DECL|macro|TYPE_PMGM_WAKE_BTN
mdefine_line|#define TYPE_PMGM_WAKE_BTN&t;0x65
DECL|macro|TYPE_PMGM_BATTERY_WARN
mdefine_line|#define TYPE_PMGM_BATTERY_WARN&t;0x66
DECL|macro|TYPE_PMGM_BATTERY_CRIT
mdefine_line|#define TYPE_PMGM_BATTERY_CRIT&t;0x67
DECL|macro|TYPE_PMGM_SWITCH_TO_BAT
mdefine_line|#define TYPE_PMGM_SWITCH_TO_BAT&t;0x68
DECL|macro|TYPE_PMGM_SWITCH_TO_AC
mdefine_line|#define TYPE_PMGM_SWITCH_TO_AC&t;0x69
DECL|macro|TYPE_PMGM_KBD_OR_MOUSE
mdefine_line|#define TYPE_PMGM_KBD_OR_MOUSE&t;0x6a
DECL|macro|TYPE_PMGM_ENCLOS_OPEN
mdefine_line|#define TYPE_PMGM_ENCLOS_OPEN&t;0x6b
DECL|macro|TYPE_PMGM_ENCLOS_CLOSED
mdefine_line|#define TYPE_PMGM_ENCLOS_CLOSED&t;0x6c
DECL|macro|TYPE_PMGM_RING_INDICATE
mdefine_line|#define TYPE_PMGM_RING_INDICATE&t;0x6d
DECL|macro|TYPE_PMGM_LAN_ATTENTION
mdefine_line|#define TYPE_PMGM_LAN_ATTENTION&t;0x6e
DECL|macro|TYPE_PMGM_TIME_ALARM
mdefine_line|#define TYPE_PMGM_TIME_ALARM&t;0x6f
DECL|macro|TYPE_PMGM_CONFIG_CHANGE
mdefine_line|#define TYPE_PMGM_CONFIG_CHANGE&t;0x70
DECL|macro|TYPE_PMGM_SERVICE_PROC
mdefine_line|#define TYPE_PMGM_SERVICE_PROC&t;0x71
DECL|struct|_rtas_error_log
r_typedef
r_struct
id|_rtas_error_log
(brace
DECL|member|version
r_int
r_int
id|version
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Architectural version */
DECL|member|severity
r_int
r_int
id|severity
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Severity level of error */
DECL|member|disposition
r_int
r_int
id|disposition
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Degree of recovery */
DECL|member|extended
r_int
r_int
id|extended
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* extended log present? */
r_int
r_int
multiline_comment|/* reserved */
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|member|initiator
r_int
r_int
id|initiator
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Initiator of event */
DECL|member|target
r_int
r_int
id|target
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Target of failed operation */
DECL|member|type
r_int
r_int
id|type
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* General event or error*/
DECL|member|extended_log_length
r_int
r_int
id|extended_log_length
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* length in bytes */
DECL|typedef|rtas_error_log
)brace
id|rtas_error_log
suffix:semicolon
multiline_comment|/* ****************************************************************** */
DECL|macro|ppc_rtas_errorlog_check_severity
mdefine_line|#define ppc_rtas_errorlog_check_severity(x) &bslash;&n;&t;(_errlog_severity[x.severity])
DECL|macro|ppc_rtas_errorlog_check_target
mdefine_line|#define ppc_rtas_errorlog_check_target(x) &bslash;&n;&t;(_errlog_target[x.target])
DECL|macro|ppc_rtas_errorlog_check_initiator
mdefine_line|#define ppc_rtas_errorlog_check_initiator(x) &bslash;&n;&t;(_errlog_initiator[x.initiator])
DECL|macro|ppc_rtas_errorlog_check_extended
mdefine_line|#define ppc_rtas_errorlog_check_extended(x) &bslash;&n;&t;(_errlog_extended[x.extended])
DECL|macro|ppc_rtas_errorlog_disect_extended
mdefine_line|#define ppc_rtas_errorlog_disect_extended(x) &bslash;&n;&t;do { /* implement me */ } while(0)
r_extern
r_const
r_char
op_star
id|ppc_rtas_errorlog_check_type
(paren
id|rtas_error_log
id|error_log
)paren
suffix:semicolon
r_extern
r_int
id|ppc_rtas_errorlog_scan
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ERROR_LOG_H__ */
eof
