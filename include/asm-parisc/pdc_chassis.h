multiline_comment|/*&n; *&t;&t;include/asm-parisc/pdc_chassis.h&n; *&n; *&t;&t;Copyright (C) 2002 Laurent Canet &lt;canetl@esiee.fr&gt;&n; *&t;&t;Copyright (C) 2002 Thibaut Varene &lt;varenet@esiee.fr&gt;&n; *&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2, or (at your option)&n; *      any later version.&n; *      &n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *      &n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *      TODO:&t;- handle processor number on SMP systems (Reporting Entity ID)&n; *      &t;- handle message ID&n; *      &t;- handle timestamps&n; */
macro_line|#ifndef _PARISC_PDC_CHASSIS_H
DECL|macro|_PARISC_PDC_CHASSIS_H
mdefine_line|#define _PARISC_PDC_CHASSIS_H
multiline_comment|/*&n; * ----------&n; * Prototypes&n; * ----------&n; */
r_int
id|pdc_chassis_send_status
c_func
(paren
r_int
id|message
)paren
suffix:semicolon
r_void
id|parisc_pdc_chassis_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * -----------------&n; * Direct call names&n; * -----------------&n; * They setup everything for you, the Log message and the corresponding LED state&n; */
DECL|macro|PDC_CHASSIS_DIRECT_BSTART
mdefine_line|#define PDC_CHASSIS_DIRECT_BSTART&t;0
DECL|macro|PDC_CHASSIS_DIRECT_BCOMPLETE
mdefine_line|#define PDC_CHASSIS_DIRECT_BCOMPLETE&t;1
DECL|macro|PDC_CHASSIS_DIRECT_SHUTDOWN
mdefine_line|#define PDC_CHASSIS_DIRECT_SHUTDOWN&t;2
DECL|macro|PDC_CHASSIS_DIRECT_PANIC
mdefine_line|#define PDC_CHASSIS_DIRECT_PANIC&t;3
DECL|macro|PDC_CHASSIS_DIRECT_HPMC
mdefine_line|#define PDC_CHASSIS_DIRECT_HPMC&t;&t;4
DECL|macro|PDC_CHASSIS_DIRECT_LPMC
mdefine_line|#define PDC_CHASSIS_DIRECT_LPMC&t;&t;5
DECL|macro|PDC_CHASSIS_DIRECT_DUMP
mdefine_line|#define PDC_CHASSIS_DIRECT_DUMP&t;&t;6&t;/* not yet implemented */
DECL|macro|PDC_CHASSIS_DIRECT_OOPS
mdefine_line|#define PDC_CHASSIS_DIRECT_OOPS&t;&t;7&t;/* not yet implemented */
multiline_comment|/*&n; * ------------&n; * LEDs control&n; * ------------&n; * Set the three LEDs -- Run, Attn, and Fault.&n; */
multiline_comment|/* Old PDC LED control */
DECL|macro|PDC_CHASSIS_DISP_DATA
mdefine_line|#define PDC_CHASSIS_DISP_DATA(v)&t;((unsigned long)(v) &lt;&lt; 17)
multiline_comment|/* &n; * Available PDC PAT LED states&n; */
DECL|macro|PDC_CHASSIS_LED_RUN_OFF
mdefine_line|#define PDC_CHASSIS_LED_RUN_OFF&t;&t;(0ULL &lt;&lt; 4)
DECL|macro|PDC_CHASSIS_LED_RUN_FLASH
mdefine_line|#define PDC_CHASSIS_LED_RUN_FLASH&t;(1ULL &lt;&lt; 4)
DECL|macro|PDC_CHASSIS_LED_RUN_ON
mdefine_line|#define PDC_CHASSIS_LED_RUN_ON&t;&t;(2ULL &lt;&lt; 4)
DECL|macro|PDC_CHASSIS_LED_RUN_NC
mdefine_line|#define PDC_CHASSIS_LED_RUN_NC&t;&t;(3ULL &lt;&lt; 4)
DECL|macro|PDC_CHASSIS_LED_ATTN_OFF
mdefine_line|#define PDC_CHASSIS_LED_ATTN_OFF&t;(0ULL &lt;&lt; 6)
DECL|macro|PDC_CHASSIS_LED_ATTN_FLASH
mdefine_line|#define PDC_CHASSIS_LED_ATTN_FLASH&t;(1ULL &lt;&lt; 6)
DECL|macro|PDC_CHASSIS_LED_ATTN_NC
mdefine_line|#define PDC_CHASSIS_LED_ATTN_NC&t;&t;(3ULL &lt;&lt; 6)&t;/* ATTN ON is invalid */
DECL|macro|PDC_CHASSIS_LED_FAULT_OFF
mdefine_line|#define PDC_CHASSIS_LED_FAULT_OFF&t;(0ULL &lt;&lt; 8)
DECL|macro|PDC_CHASSIS_LED_FAULT_FLASH
mdefine_line|#define PDC_CHASSIS_LED_FAULT_FLASH&t;(1ULL &lt;&lt; 8)
DECL|macro|PDC_CHASSIS_LED_FAULT_ON
mdefine_line|#define PDC_CHASSIS_LED_FAULT_ON&t;(2ULL &lt;&lt; 8)
DECL|macro|PDC_CHASSIS_LED_FAULT_NC
mdefine_line|#define PDC_CHASSIS_LED_FAULT_NC&t;(3ULL &lt;&lt; 8)
DECL|macro|PDC_CHASSIS_LED_VALID
mdefine_line|#define PDC_CHASSIS_LED_VALID&t;&t;(1ULL &lt;&lt; 10)
multiline_comment|/* &n; * Valid PDC PAT LED states combinations&n; */
multiline_comment|/* System running normally */
DECL|macro|PDC_CHASSIS_LSTATE_RUN_NORMAL
mdefine_line|#define PDC_CHASSIS_LSTATE_RUN_NORMAL&t;(PDC_CHASSIS_LED_RUN_ON&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* System crashed and rebooted itself successfully */
DECL|macro|PDC_CHASSIS_LSTATE_RUN_CRASHREC
mdefine_line|#define PDC_CHASSIS_LSTATE_RUN_CRASHREC&t;(PDC_CHASSIS_LED_RUN_ON&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* There was a system interruption that did not take the system down */
DECL|macro|PDC_CHASSIS_LSTATE_RUN_SYSINT
mdefine_line|#define PDC_CHASSIS_LSTATE_RUN_SYSINT&t;(PDC_CHASSIS_LED_RUN_ON&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* System running and unexpected reboot or non-critical error detected */
DECL|macro|PDC_CHASSIS_LSTATE_RUN_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_RUN_NCRIT&t;(PDC_CHASSIS_LED_RUN_ON&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Executing non-OS code */
DECL|macro|PDC_CHASSIS_LSTATE_NONOS
mdefine_line|#define PDC_CHASSIS_LSTATE_NONOS&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Boot failed - Executing non-OS code */
DECL|macro|PDC_CHASSIS_LSTATE_NONOS_BFAIL
mdefine_line|#define PDC_CHASSIS_LSTATE_NONOS_BFAIL&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_ON&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Unexpected reboot occurred - Executing non-OS code */
DECL|macro|PDC_CHASSIS_LSTATE_NONOS_UNEXP
mdefine_line|#define PDC_CHASSIS_LSTATE_NONOS_UNEXP&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Executing non-OS code - Non-critical error detected */
DECL|macro|PDC_CHASSIS_LSTATE_NONOS_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_NONOS_NCRIT&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Boot failed - Executing non-OS code - Non-critical error detected */
DECL|macro|PDC_CHASSIS_LSTATE_BFAIL_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_BFAIL_NCRIT&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_ON&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Unexpected reboot/recovering - Executing non-OS code - Non-critical error detected */
DECL|macro|PDC_CHASSIS_LSTATE_UNEXP_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_UNEXP_NCRIT&t;(PDC_CHASSIS_LED_RUN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Cannot execute PDC */
DECL|macro|PDC_CHASSIS_LSTATE_CANNOT_PDC
mdefine_line|#define PDC_CHASSIS_LSTATE_CANNOT_PDC&t;(PDC_CHASSIS_LED_RUN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Boot failed - OS not up - PDC has detected a failure that prevents boot */
DECL|macro|PDC_CHASSIS_LSTATE_FATAL_BFAIL
mdefine_line|#define PDC_CHASSIS_LSTATE_FATAL_BFAIL&t;(PDC_CHASSIS_LED_RUN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_ON&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* No code running - Non-critical error detected (double fault situation) */
DECL|macro|PDC_CHASSIS_LSTATE_NOCODE_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_NOCODE_NCRIT&t;(PDC_CHASSIS_LED_RUN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* Boot failed - OS not up - Fatal failure detected - Non-critical error detected */
DECL|macro|PDC_CHASSIS_LSTATE_FATAL_NCRIT
mdefine_line|#define PDC_CHASSIS_LSTATE_FATAL_NCRIT&t;(PDC_CHASSIS_LED_RUN_OFF&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_ATTN_FLASH&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_FAULT_ON&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_LED_VALID&t;&t;)
multiline_comment|/* All other states are invalid */
multiline_comment|/*&n; * --------------&n; * PDC Log events&n; * --------------&n; * Here follows bits needed to fill up the log event sent to PDC_CHASSIS&n; * The log message contains: Alert level, Source, Source detail,&n; * Source ID, Problem detail, Caller activity, Activity status, &n; * Caller subactivity, Reporting entity type, Reporting entity ID,&n; * Data type, Unique message ID and EOM. &n; */
multiline_comment|/* Alert level */
DECL|macro|PDC_CHASSIS_ALERT_FORWARD
mdefine_line|#define PDC_CHASSIS_ALERT_FORWARD&t;(0ULL &lt;&lt; 36)&t;/* no failure detected */
DECL|macro|PDC_CHASSIS_ALERT_SERPROC
mdefine_line|#define PDC_CHASSIS_ALERT_SERPROC&t;(1ULL &lt;&lt; 36)&t;/* service proc - no failure */
DECL|macro|PDC_CHASSIS_ALERT_NURGENT
mdefine_line|#define PDC_CHASSIS_ALERT_NURGENT&t;(2ULL &lt;&lt; 36)&t;/* non-urgent operator attn */
DECL|macro|PDC_CHASSIS_ALERT_BLOCKED
mdefine_line|#define PDC_CHASSIS_ALERT_BLOCKED&t;(3ULL &lt;&lt; 36)&t;/* system blocked */
DECL|macro|PDC_CHASSIS_ALERT_CONF_CHG
mdefine_line|#define PDC_CHASSIS_ALERT_CONF_CHG&t;(4ULL &lt;&lt; 36)&t;/* unexpected configuration change */
DECL|macro|PDC_CHASSIS_ALERT_ENV_PB
mdefine_line|#define PDC_CHASSIS_ALERT_ENV_PB&t;(5ULL &lt;&lt; 36)&t;/* boot possible, environmental pb */
DECL|macro|PDC_CHASSIS_ALERT_PENDING
mdefine_line|#define PDC_CHASSIS_ALERT_PENDING&t;(6ULL &lt;&lt; 36)&t;/* boot possible, pending failure */
DECL|macro|PDC_CHASSIS_ALERT_PERF_IMP
mdefine_line|#define PDC_CHASSIS_ALERT_PERF_IMP&t;(8ULL &lt;&lt; 36)&t;/* boot possible, performance impaired */
DECL|macro|PDC_CHASSIS_ALERT_FUNC_IMP
mdefine_line|#define PDC_CHASSIS_ALERT_FUNC_IMP&t;(10ULL &lt;&lt; 36)&t;/* boot possible, functionality impaired */
DECL|macro|PDC_CHASSIS_ALERT_SOFT_FAIL
mdefine_line|#define PDC_CHASSIS_ALERT_SOFT_FAIL&t;(12ULL &lt;&lt; 36)&t;/* software failure */
DECL|macro|PDC_CHASSIS_ALERT_HANG
mdefine_line|#define PDC_CHASSIS_ALERT_HANG&t;&t;(13ULL &lt;&lt; 36)&t;/* system hang */
DECL|macro|PDC_CHASSIS_ALERT_ENV_FATAL
mdefine_line|#define PDC_CHASSIS_ALERT_ENV_FATAL&t;(14ULL &lt;&lt; 36)&t;/* fatal power or environmental pb */
DECL|macro|PDC_CHASSIS_ALERT_HW_FATAL
mdefine_line|#define PDC_CHASSIS_ALERT_HW_FATAL&t;(15ULL &lt;&lt; 36)&t;/* fatal hardware problem */
multiline_comment|/* Source */
DECL|macro|PDC_CHASSIS_SRC_NONE
mdefine_line|#define PDC_CHASSIS_SRC_NONE&t;&t;(0ULL &lt;&lt; 28)&t;/* unknown, no source stated */
DECL|macro|PDC_CHASSIS_SRC_PROC
mdefine_line|#define PDC_CHASSIS_SRC_PROC&t;&t;(1ULL &lt;&lt; 28)&t;/* processor */
multiline_comment|/* For later use ? */
DECL|macro|PDC_CHASSIS_SRC_PROC_CACHE
mdefine_line|#define PDC_CHASSIS_SRC_PROC_CACHE&t;(2ULL &lt;&lt; 28)&t;/* processor cache*/
DECL|macro|PDC_CHASSIS_SRC_PDH
mdefine_line|#define PDC_CHASSIS_SRC_PDH&t;&t;(3ULL &lt;&lt; 28)&t;/* processor dependent hardware */
DECL|macro|PDC_CHASSIS_SRC_PWR
mdefine_line|#define PDC_CHASSIS_SRC_PWR&t;&t;(4ULL &lt;&lt; 28)&t;/* power */
DECL|macro|PDC_CHASSIS_SRC_FAB
mdefine_line|#define PDC_CHASSIS_SRC_FAB&t;&t;(5ULL &lt;&lt; 28)&t;/* fabric connector */
DECL|macro|PDC_CHASSIS_SRC_PLATi
mdefine_line|#define PDC_CHASSIS_SRC_PLATi&t;&t;(6ULL &lt;&lt; 28)&t;/* platform */
DECL|macro|PDC_CHASSIS_SRC_MEM
mdefine_line|#define PDC_CHASSIS_SRC_MEM&t;&t;(7ULL &lt;&lt; 28)&t;/* memory */
DECL|macro|PDC_CHASSIS_SRC_IO
mdefine_line|#define PDC_CHASSIS_SRC_IO&t;&t;(8ULL &lt;&lt; 28)&t;/* I/O */
DECL|macro|PDC_CHASSIS_SRC_CELL
mdefine_line|#define PDC_CHASSIS_SRC_CELL&t;&t;(9ULL &lt;&lt; 28)&t;/* cell */
DECL|macro|PDC_CHASSIS_SRC_PD
mdefine_line|#define PDC_CHASSIS_SRC_PD&t;&t;(10ULL &lt;&lt; 28)&t;/* protected domain */
multiline_comment|/* Source detail field */
DECL|macro|PDC_CHASSIS_SRC_D_PROC
mdefine_line|#define PDC_CHASSIS_SRC_D_PROC&t;&t;(1ULL &lt;&lt; 24)&t;/* processor general */
multiline_comment|/* Source ID - platform dependent */
DECL|macro|PDC_CHASSIS_SRC_ID_UNSPEC
mdefine_line|#define PDC_CHASSIS_SRC_ID_UNSPEC&t;(0ULL &lt;&lt; 16)
multiline_comment|/* Problem detail - problem source dependent */
DECL|macro|PDC_CHASSIS_PB_D_PROC_NONE
mdefine_line|#define PDC_CHASSIS_PB_D_PROC_NONE&t;(0ULL &lt;&lt; 32)&t;/* no problem detail */
DECL|macro|PDC_CHASSIS_PB_D_PROC_TIMEOUT
mdefine_line|#define PDC_CHASSIS_PB_D_PROC_TIMEOUT&t;(4ULL &lt;&lt; 32)&t;/* timeout */
multiline_comment|/* Caller activity */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_BL
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_BL&t;(7ULL &lt;&lt; 12)&t;/* Boot Loader */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_PD
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_PD&t;(8ULL &lt;&lt; 12)&t;/* SAL_PD activities */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_EVENT
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_EVENT&t;(9ULL &lt;&lt; 12)&t;/* SAL_EVENTS activities */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_IO
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_IO&t;(10ULL &lt;&lt; 12)&t;/* SAL_IO activities */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_PANIC
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_PANIC&t;(11ULL &lt;&lt; 12)&t;/* System panic */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_INIT
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_INIT&t;(12ULL &lt;&lt; 12)&t;/* System initialization */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_SHUT
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_SHUT&t;(13ULL &lt;&lt; 12)&t;/* System shutdown */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_WARN
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_WARN&t;(14ULL &lt;&lt; 12)&t;/* System warning */
DECL|macro|PDC_CHASSIS_CALL_ACT_HPUX_DU
mdefine_line|#define PDC_CHASSIS_CALL_ACT_HPUX_DU&t;(15ULL &lt;&lt; 12)&t;/* Display_Activity() update */
multiline_comment|/* Activity status - implementation dependent */
DECL|macro|PDC_CHASSIS_ACT_STATUS_UNSPEC
mdefine_line|#define PDC_CHASSIS_ACT_STATUS_UNSPEC&t;(0ULL &lt;&lt; 0)
multiline_comment|/* Caller subactivity - implementation dependent */
multiline_comment|/* FIXME: other subactivities ? */
DECL|macro|PDC_CHASSIS_CALL_SACT_UNSPEC
mdefine_line|#define PDC_CHASSIS_CALL_SACT_UNSPEC&t;(0ULL &lt;&lt; 4)&t;/* implementation dependent */
multiline_comment|/* Reporting entity type */
DECL|macro|PDC_CHASSIS_RET_GENERICOS
mdefine_line|#define PDC_CHASSIS_RET_GENERICOS&t;(12ULL &lt;&lt; 52)&t;/* generic OSes */
DECL|macro|PDC_CHASSIS_RET_IA64_NT
mdefine_line|#define PDC_CHASSIS_RET_IA64_NT&t;&t;(13ULL &lt;&lt; 52)&t;/* IA-64 NT */
DECL|macro|PDC_CHASSIS_RET_HPUX
mdefine_line|#define PDC_CHASSIS_RET_HPUX&t;&t;(14ULL &lt;&lt; 52)&t;/* HP-UX */
DECL|macro|PDC_CHASSIS_RET_DIAG
mdefine_line|#define PDC_CHASSIS_RET_DIAG&t;&t;(15ULL &lt;&lt; 52)&t;/* offline diagnostics &amp; utilities */
multiline_comment|/* Reporting entity ID */
DECL|macro|PDC_CHASSIS_REID_UNSPEC
mdefine_line|#define PDC_CHASSIS_REID_UNSPEC&t;&t;(0ULL &lt;&lt; 44)
multiline_comment|/* Data type */
DECL|macro|PDC_CHASSIS_DT_NONE
mdefine_line|#define PDC_CHASSIS_DT_NONE&t;&t;(0ULL &lt;&lt; 59)&t;/* data field unused */
multiline_comment|/* For later use ? Do we need these ? */
DECL|macro|PDC_CHASSIS_DT_PHYS_ADDR
mdefine_line|#define PDC_CHASSIS_DT_PHYS_ADDR&t;(1ULL &lt;&lt; 59)&t;/* physical address */
DECL|macro|PDC_CHASSIS_DT_DATA_EXPECT
mdefine_line|#define PDC_CHASSIS_DT_DATA_EXPECT&t;(2ULL &lt;&lt; 59)&t;/* expected data */
DECL|macro|PDC_CHASSIS_DT_ACTUAL
mdefine_line|#define PDC_CHASSIS_DT_ACTUAL&t;&t;(3ULL &lt;&lt; 59)&t;/* actual data */
DECL|macro|PDC_CHASSIS_DT_PHYS_LOC
mdefine_line|#define PDC_CHASSIS_DT_PHYS_LOC&t;&t;(4ULL &lt;&lt; 59)&t;/* physical location */
DECL|macro|PDC_CHASSIS_DT_PHYS_LOC_EXT
mdefine_line|#define PDC_CHASSIS_DT_PHYS_LOC_EXT&t;(5ULL &lt;&lt; 59)&t;/* physical location extension */
DECL|macro|PDC_CHASSIS_DT_TAG
mdefine_line|#define PDC_CHASSIS_DT_TAG&t;&t;(6ULL &lt;&lt; 59)&t;/* tag */
DECL|macro|PDC_CHASSIS_DT_SYNDROME
mdefine_line|#define PDC_CHASSIS_DT_SYNDROME&t;&t;(7ULL &lt;&lt; 59)&t;/* syndrome */
DECL|macro|PDC_CHASSIS_DT_CODE_ADDR
mdefine_line|#define PDC_CHASSIS_DT_CODE_ADDR&t;(8ULL &lt;&lt; 59)&t;/* code address */
DECL|macro|PDC_CHASSIS_DT_ASCII_MSG
mdefine_line|#define PDC_CHASSIS_DT_ASCII_MSG&t;(9ULL &lt;&lt; 59)&t;/* ascii message */
DECL|macro|PDC_CHASSIS_DT_POST
mdefine_line|#define PDC_CHASSIS_DT_POST&t;&t;(10ULL &lt;&lt; 59)&t;/* POST code */
DECL|macro|PDC_CHASSIS_DT_TIMESTAMP
mdefine_line|#define PDC_CHASSIS_DT_TIMESTAMP&t;(11ULL &lt;&lt; 59)&t;/* timestamp */
DECL|macro|PDC_CHASSIS_DT_DEV_STAT
mdefine_line|#define PDC_CHASSIS_DT_DEV_STAT&t;&t;(12ULL &lt;&lt; 59)&t;/* device status */
DECL|macro|PDC_CHASSIS_DT_DEV_TYPE
mdefine_line|#define PDC_CHASSIS_DT_DEV_TYPE&t;&t;(13ULL &lt;&lt; 59)&t;/* device type */
DECL|macro|PDC_CHASSIS_DT_PB_DET
mdefine_line|#define PDC_CHASSIS_DT_PB_DET&t;&t;(14ULL &lt;&lt; 59)&t;/* problem detail */
DECL|macro|PDC_CHASSIS_DT_ACT_LEV
mdefine_line|#define PDC_CHASSIS_DT_ACT_LEV&t;&t;(15ULL &lt;&lt; 59)&t;/* activity level/timeout */
DECL|macro|PDC_CHASSIS_DT_SER_NUM
mdefine_line|#define PDC_CHASSIS_DT_SER_NUM&t;&t;(16ULL &lt;&lt; 59)&t;/* serial number */
DECL|macro|PDC_CHASSIS_DT_REV_NUM
mdefine_line|#define PDC_CHASSIS_DT_REV_NUM&t;&t;(17ULL &lt;&lt; 59)&t;/* revision number */
DECL|macro|PDC_CHASSIS_DT_INTERRUPT
mdefine_line|#define PDC_CHASSIS_DT_INTERRUPT&t;(18ULL &lt;&lt; 59)&t;/* interruption information */
DECL|macro|PDC_CHASSIS_DT_TEST_NUM
mdefine_line|#define PDC_CHASSIS_DT_TEST_NUM&t;&t;(19ULL &lt;&lt; 59)&t;/* test number */
DECL|macro|PDC_CHASSIS_DT_STATE_CHG
mdefine_line|#define PDC_CHASSIS_DT_STATE_CHG&t;(20ULL &lt;&lt; 59)&t;/* major changes in system state */
DECL|macro|PDC_CHASSIS_DT_PROC_DEALLOC
mdefine_line|#define PDC_CHASSIS_DT_PROC_DEALLOC&t;(21ULL &lt;&lt; 59)&t;/* processor deallocate */
DECL|macro|PDC_CHASSIS_DT_RESET
mdefine_line|#define PDC_CHASSIS_DT_RESET&t;&t;(30ULL &lt;&lt; 59)&t;/* reset type and cause */
DECL|macro|PDC_CHASSIS_DT_PA_LEGACY
mdefine_line|#define PDC_CHASSIS_DT_PA_LEGACY&t;(31ULL &lt;&lt; 59)&t;/* legacy PA hex chassis code */
multiline_comment|/* System states - part of major changes in system state data field */
DECL|macro|PDC_CHASSIS_SYSTATE_BSTART
mdefine_line|#define PDC_CHASSIS_SYSTATE_BSTART&t;(0ULL &lt;&lt; 0)&t;/* boot start */
DECL|macro|PDC_CHASSIS_SYSTATE_BCOMP
mdefine_line|#define PDC_CHASSIS_SYSTATE_BCOMP&t;(1ULL &lt;&lt; 0)&t;/* boot complete */
DECL|macro|PDC_CHASSIS_SYSTATE_CHANGE
mdefine_line|#define PDC_CHASSIS_SYSTATE_CHANGE&t;(2ULL &lt;&lt; 0)&t;/* major change */
DECL|macro|PDC_CHASSIS_SYSTATE_LED
mdefine_line|#define PDC_CHASSIS_SYSTATE_LED&t;&t;(3ULL &lt;&lt; 0)&t;/* LED change */
DECL|macro|PDC_CHASSIS_SYSTATE_PANIC
mdefine_line|#define PDC_CHASSIS_SYSTATE_PANIC&t;(9ULL &lt;&lt; 0)&t;/* OS Panic */
DECL|macro|PDC_CHASSIS_SYSTATE_DUMP
mdefine_line|#define PDC_CHASSIS_SYSTATE_DUMP&t;(10ULL &lt;&lt; 0)&t;/* memory dump */
DECL|macro|PDC_CHASSIS_SYSTATE_HPMC
mdefine_line|#define PDC_CHASSIS_SYSTATE_HPMC&t;(11ULL &lt;&lt; 0)&t;/* processing HPMC */
DECL|macro|PDC_CHASSIS_SYSTATE_HALT
mdefine_line|#define PDC_CHASSIS_SYSTATE_HALT&t;(15ULL &lt;&lt; 0)&t;/* system halted */
multiline_comment|/* Message ID */
DECL|macro|PDC_CHASSIS_MSG_ID
mdefine_line|#define PDC_CHASSIS_MSG_ID&t;&t;(0ULL &lt;&lt; 40)&t;/* we do not handle msg IDs atm */
multiline_comment|/* EOM - separates log entries */
DECL|macro|PDC_CHASSIS_EOM_CLEAR
mdefine_line|#define PDC_CHASSIS_EOM_CLEAR&t;&t;(0ULL &lt;&lt; 43)
DECL|macro|PDC_CHASSIS_EOM_SET
mdefine_line|#define PDC_CHASSIS_EOM_SET&t;&t;(1ULL &lt;&lt; 43)
multiline_comment|/*&n; * Preformated well known messages&n; */
multiline_comment|/* Boot started */
DECL|macro|PDC_CHASSIS_PMSG_BSTART
mdefine_line|#define PDC_CHASSIS_PMSG_BSTART&t;&t;(PDC_CHASSIS_ALERT_SERPROC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_INIT&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_ACT_STATUS_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_SACT_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_REID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_BSTART&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
multiline_comment|/* Boot complete */
DECL|macro|PDC_CHASSIS_PMSG_BCOMPLETE
mdefine_line|#define PDC_CHASSIS_PMSG_BCOMPLETE&t;(PDC_CHASSIS_ALERT_SERPROC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_INIT&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_ACT_STATUS_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_SACT_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_REID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_BCOMP&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
multiline_comment|/* Shutdown */
DECL|macro|PDC_CHASSIS_PMSG_SHUTDOWN
mdefine_line|#define PDC_CHASSIS_PMSG_SHUTDOWN&t;(PDC_CHASSIS_ALERT_SERPROC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_SHUT&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_ACT_STATUS_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_SACT_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_REID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_HALT&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
multiline_comment|/* Panic */
DECL|macro|PDC_CHASSIS_PMSG_PANIC
mdefine_line|#define PDC_CHASSIS_PMSG_PANIC&t;&t;(PDC_CHASSIS_ALERT_SOFT_FAIL&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_PANIC| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_ACT_STATUS_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_SACT_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_REID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_PANIC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
singleline_comment|// FIXME: extrapolated data
multiline_comment|/* HPMC */
DECL|macro|PDC_CHASSIS_PMSG_HPMC
mdefine_line|#define PDC_CHASSIS_PMSG_HPMC&t;&t;(PDC_CHASSIS_ALERT_CONF_CHG /*?*/&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_WARN&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_HPMC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
multiline_comment|/* LPMC */
DECL|macro|PDC_CHASSIS_PMSG_LPMC
mdefine_line|#define PDC_CHASSIS_PMSG_LPMC&t;&t;(PDC_CHASSIS_ALERT_BLOCKED /*?*/| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_D_PROC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SRC_ID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_PB_D_PROC_NONE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_ACT_HPUX_WARN&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_ACT_STATUS_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_CALL_SACT_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_RET_HPUX&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_REID_UNSPEC&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_DT_STATE_CHG&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_SYSTATE_CHANGE&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_MSG_ID&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; PDC_CHASSIS_EOM_SET&t;&t;)
macro_line|#endif /* _PARISC_PDC_CHASSIS_H */
multiline_comment|/* vim: set ts=8 */
eof
