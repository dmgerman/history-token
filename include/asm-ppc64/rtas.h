macro_line|#ifndef _PPC64_RTAS_H
DECL|macro|_PPC64_RTAS_H
mdefine_line|#define _PPC64_RTAS_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Definitions for talking to the RTAS on CHRP machines.&n; *&n; * Copyright (C) 2001 Peter Bergner&n; * Copyright (C) 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|RTAS_UNKNOWN_SERVICE
mdefine_line|#define RTAS_UNKNOWN_SERVICE (-1)
DECL|macro|RTAS_INSTANTIATE_MAX
mdefine_line|#define RTAS_INSTANTIATE_MAX (1UL&lt;&lt;30) /* Don&squot;t instantiate rtas at/above this value */
multiline_comment|/* Buffer size for ppc_rtas system call. */
DECL|macro|RTAS_RMOBUF_MAX
mdefine_line|#define RTAS_RMOBUF_MAX (64 * 1024)
multiline_comment|/* RTAS return status codes */
DECL|macro|RTAS_BUSY
mdefine_line|#define RTAS_BUSY&t;&t;-2    /* RTAS Busy */
DECL|macro|RTAS_NO_SUCH_INDICATOR
mdefine_line|#define RTAS_NO_SUCH_INDICATOR&t;-3    /* No such indicator implemented */
DECL|macro|RTAS_EXTENDED_DELAY_MIN
mdefine_line|#define RTAS_EXTENDED_DELAY_MIN&t;9900
DECL|macro|RTAS_EXTENDED_DELAY_MAX
mdefine_line|#define RTAS_EXTENDED_DELAY_MAX&t;9905
DECL|macro|RTAS_UNKNOWN_OP
mdefine_line|#define RTAS_UNKNOWN_OP&t;&t;-1099 /* Unknown RTAS Token */
multiline_comment|/*&n; * In general to call RTAS use rtas_token(&quot;string&quot;) to lookup&n; * an RTAS token for the given string (e.g. &quot;event-scan&quot;).&n; * To actually perform the call use&n; *    ret = rtas_call(token, n_in, n_out, ...)&n; * Where n_in is the number of input parameters and&n; *       n_out is the number of output parameters&n; *&n; * If the &quot;string&quot; is invalid on this system, RTAS_UNKNOWN_SERVICE&n; * will be returned as a token.  rtas_call() does look for this&n; * token and error out gracefully so rtas_call(rtas_token(&quot;str&quot;), ...)&n; * may be safely used for one-shot calls to RTAS.&n; *&n; */
DECL|typedef|rtas_arg_t
r_typedef
id|u32
id|rtas_arg_t
suffix:semicolon
DECL|struct|rtas_args
r_struct
id|rtas_args
(brace
DECL|member|token
id|u32
id|token
suffix:semicolon
DECL|member|nargs
id|u32
id|nargs
suffix:semicolon
DECL|member|nret
id|u32
id|nret
suffix:semicolon
DECL|member|args
id|rtas_arg_t
id|args
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rets
id|rtas_arg_t
op_star
id|rets
suffix:semicolon
multiline_comment|/* Pointer to return values in args[]. */
)brace
suffix:semicolon
r_extern
r_struct
id|rtas_args
id|rtas_stop_self_args
suffix:semicolon
DECL|struct|rtas_t
r_struct
id|rtas_t
(brace
DECL|member|entry
r_int
r_int
id|entry
suffix:semicolon
multiline_comment|/* physical address pointer */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* physical address pointer */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|args
r_struct
id|rtas_args
id|args
suffix:semicolon
DECL|member|dev
r_struct
id|device_node
op_star
id|dev
suffix:semicolon
multiline_comment|/* virtual address pointer */
)brace
suffix:semicolon
multiline_comment|/* RTAS event classes */
DECL|macro|RTAS_INTERNAL_ERROR
mdefine_line|#define RTAS_INTERNAL_ERROR&t;&t;0x80000000 /* set bit 0 */
DECL|macro|RTAS_EPOW_WARNING
mdefine_line|#define RTAS_EPOW_WARNING&t;&t;0x40000000 /* set bit 1 */
DECL|macro|RTAS_POWERMGM_EVENTS
mdefine_line|#define RTAS_POWERMGM_EVENTS&t;&t;0x20000000 /* set bit 2 */
DECL|macro|RTAS_HOTPLUG_EVENTS
mdefine_line|#define RTAS_HOTPLUG_EVENTS&t;&t;0x10000000 /* set bit 3 */
DECL|macro|RTAS_EVENT_SCAN_ALL_EVENTS
mdefine_line|#define RTAS_EVENT_SCAN_ALL_EVENTS&t;0xf0000000
multiline_comment|/* RTAS event severity */
DECL|macro|RTAS_SEVERITY_FATAL
mdefine_line|#define RTAS_SEVERITY_FATAL&t;&t;0x5
DECL|macro|RTAS_SEVERITY_ERROR
mdefine_line|#define RTAS_SEVERITY_ERROR&t;&t;0x4
DECL|macro|RTAS_SEVERITY_ERROR_SYNC
mdefine_line|#define RTAS_SEVERITY_ERROR_SYNC&t;0x3
DECL|macro|RTAS_SEVERITY_WARNING
mdefine_line|#define RTAS_SEVERITY_WARNING&t;&t;0x2
DECL|macro|RTAS_SEVERITY_EVENT
mdefine_line|#define RTAS_SEVERITY_EVENT&t;&t;0x1
DECL|macro|RTAS_SEVERITY_NO_ERROR
mdefine_line|#define RTAS_SEVERITY_NO_ERROR&t;&t;0x0
multiline_comment|/* RTAS event disposition */
DECL|macro|RTAS_DISP_FULLY_RECOVERED
mdefine_line|#define RTAS_DISP_FULLY_RECOVERED&t;0x0
DECL|macro|RTAS_DISP_LIMITED_RECOVERY
mdefine_line|#define RTAS_DISP_LIMITED_RECOVERY&t;0x1
DECL|macro|RTAS_DISP_NOT_RECOVERED
mdefine_line|#define RTAS_DISP_NOT_RECOVERED&t;&t;0x2
multiline_comment|/* RTAS event initiator */
DECL|macro|RTAS_INITIATOR_UNKNOWN
mdefine_line|#define RTAS_INITIATOR_UNKNOWN&t;&t;0x0
DECL|macro|RTAS_INITIATOR_CPU
mdefine_line|#define RTAS_INITIATOR_CPU&t;&t;0x1
DECL|macro|RTAS_INITIATOR_PCI
mdefine_line|#define RTAS_INITIATOR_PCI&t;&t;0x2
DECL|macro|RTAS_INITIATOR_ISA
mdefine_line|#define RTAS_INITIATOR_ISA&t;&t;0x3
DECL|macro|RTAS_INITIATOR_MEMORY
mdefine_line|#define RTAS_INITIATOR_MEMORY&t;&t;0x4
DECL|macro|RTAS_INITIATOR_POWERMGM
mdefine_line|#define RTAS_INITIATOR_POWERMGM&t;&t;0x5
multiline_comment|/* RTAS event target */
DECL|macro|RTAS_TARGET_UNKNOWN
mdefine_line|#define RTAS_TARGET_UNKNOWN&t;&t;0x0
DECL|macro|RTAS_TARGET_CPU
mdefine_line|#define RTAS_TARGET_CPU&t;&t;&t;0x1
DECL|macro|RTAS_TARGET_PCI
mdefine_line|#define RTAS_TARGET_PCI&t;&t;&t;0x2
DECL|macro|RTAS_TARGET_ISA
mdefine_line|#define RTAS_TARGET_ISA&t;&t;&t;0x3
DECL|macro|RTAS_TARGET_MEMORY
mdefine_line|#define RTAS_TARGET_MEMORY&t;&t;0x4
DECL|macro|RTAS_TARGET_POWERMGM
mdefine_line|#define RTAS_TARGET_POWERMGM&t;&t;0x5
multiline_comment|/* RTAS event type */
DECL|macro|RTAS_TYPE_RETRY
mdefine_line|#define RTAS_TYPE_RETRY&t;&t;&t;0x01
DECL|macro|RTAS_TYPE_TCE_ERR
mdefine_line|#define RTAS_TYPE_TCE_ERR&t;&t;0x02
DECL|macro|RTAS_TYPE_INTERN_DEV_FAIL
mdefine_line|#define RTAS_TYPE_INTERN_DEV_FAIL&t;0x03
DECL|macro|RTAS_TYPE_TIMEOUT
mdefine_line|#define RTAS_TYPE_TIMEOUT&t;&t;0x04
DECL|macro|RTAS_TYPE_DATA_PARITY
mdefine_line|#define RTAS_TYPE_DATA_PARITY&t;&t;0x05
DECL|macro|RTAS_TYPE_ADDR_PARITY
mdefine_line|#define RTAS_TYPE_ADDR_PARITY&t;&t;0x06
DECL|macro|RTAS_TYPE_CACHE_PARITY
mdefine_line|#define RTAS_TYPE_CACHE_PARITY&t;&t;0x07
DECL|macro|RTAS_TYPE_ADDR_INVALID
mdefine_line|#define RTAS_TYPE_ADDR_INVALID&t;&t;0x08
DECL|macro|RTAS_TYPE_ECC_UNCORR
mdefine_line|#define RTAS_TYPE_ECC_UNCORR&t;&t;0x09
DECL|macro|RTAS_TYPE_ECC_CORR
mdefine_line|#define RTAS_TYPE_ECC_CORR&t;&t;0x0a
DECL|macro|RTAS_TYPE_EPOW
mdefine_line|#define RTAS_TYPE_EPOW&t;&t;&t;0x40
DECL|macro|RTAS_TYPE_PLATFORM
mdefine_line|#define RTAS_TYPE_PLATFORM&t;&t;0xE0
DECL|macro|RTAS_TYPE_IO
mdefine_line|#define RTAS_TYPE_IO&t;&t;&t;0xE1
DECL|macro|RTAS_TYPE_INFO
mdefine_line|#define RTAS_TYPE_INFO&t;&t;&t;0xE2
DECL|macro|RTAS_TYPE_DEALLOC
mdefine_line|#define RTAS_TYPE_DEALLOC&t;&t;0xE3
DECL|macro|RTAS_TYPE_DUMP
mdefine_line|#define RTAS_TYPE_DUMP&t;&t;&t;0xE4
multiline_comment|/* I don&squot;t add PowerMGM events right now, this is a different topic */
DECL|macro|RTAS_TYPE_PMGM_POWER_SW_ON
mdefine_line|#define RTAS_TYPE_PMGM_POWER_SW_ON&t;0x60
DECL|macro|RTAS_TYPE_PMGM_POWER_SW_OFF
mdefine_line|#define RTAS_TYPE_PMGM_POWER_SW_OFF&t;0x61
DECL|macro|RTAS_TYPE_PMGM_LID_OPEN
mdefine_line|#define RTAS_TYPE_PMGM_LID_OPEN&t;&t;0x62
DECL|macro|RTAS_TYPE_PMGM_LID_CLOSE
mdefine_line|#define RTAS_TYPE_PMGM_LID_CLOSE&t;0x63
DECL|macro|RTAS_TYPE_PMGM_SLEEP_BTN
mdefine_line|#define RTAS_TYPE_PMGM_SLEEP_BTN&t;0x64
DECL|macro|RTAS_TYPE_PMGM_WAKE_BTN
mdefine_line|#define RTAS_TYPE_PMGM_WAKE_BTN&t;&t;0x65
DECL|macro|RTAS_TYPE_PMGM_BATTERY_WARN
mdefine_line|#define RTAS_TYPE_PMGM_BATTERY_WARN&t;0x66
DECL|macro|RTAS_TYPE_PMGM_BATTERY_CRIT
mdefine_line|#define RTAS_TYPE_PMGM_BATTERY_CRIT&t;0x67
DECL|macro|RTAS_TYPE_PMGM_SWITCH_TO_BAT
mdefine_line|#define RTAS_TYPE_PMGM_SWITCH_TO_BAT&t;0x68
DECL|macro|RTAS_TYPE_PMGM_SWITCH_TO_AC
mdefine_line|#define RTAS_TYPE_PMGM_SWITCH_TO_AC&t;0x69
DECL|macro|RTAS_TYPE_PMGM_KBD_OR_MOUSE
mdefine_line|#define RTAS_TYPE_PMGM_KBD_OR_MOUSE&t;0x6a
DECL|macro|RTAS_TYPE_PMGM_ENCLOS_OPEN
mdefine_line|#define RTAS_TYPE_PMGM_ENCLOS_OPEN&t;0x6b
DECL|macro|RTAS_TYPE_PMGM_ENCLOS_CLOSED
mdefine_line|#define RTAS_TYPE_PMGM_ENCLOS_CLOSED&t;0x6c
DECL|macro|RTAS_TYPE_PMGM_RING_INDICATE
mdefine_line|#define RTAS_TYPE_PMGM_RING_INDICATE&t;0x6d
DECL|macro|RTAS_TYPE_PMGM_LAN_ATTENTION
mdefine_line|#define RTAS_TYPE_PMGM_LAN_ATTENTION&t;0x6e
DECL|macro|RTAS_TYPE_PMGM_TIME_ALARM
mdefine_line|#define RTAS_TYPE_PMGM_TIME_ALARM&t;0x6f
DECL|macro|RTAS_TYPE_PMGM_CONFIG_CHANGE
mdefine_line|#define RTAS_TYPE_PMGM_CONFIG_CHANGE&t;0x70
DECL|macro|RTAS_TYPE_PMGM_SERVICE_PROC
mdefine_line|#define RTAS_TYPE_PMGM_SERVICE_PROC&t;0x71
DECL|struct|rtas_error_log
r_struct
id|rtas_error_log
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
DECL|member|buffer
r_int
r_char
id|buffer
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|flash_block
r_struct
id|flash_block
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is very similar but not identical to&n; * that needed by the rtas flash update.&n; * All we need to do for rtas is rewrite num_blocks&n; * into a version/length and translate the pointers&n; * to absolute.&n; */
DECL|macro|FLASH_BLOCKS_PER_NODE
mdefine_line|#define FLASH_BLOCKS_PER_NODE ((PAGE_SIZE - 16) / sizeof(struct flash_block))
DECL|struct|flash_block_list
r_struct
id|flash_block_list
(brace
DECL|member|num_blocks
r_int
r_int
id|num_blocks
suffix:semicolon
DECL|member|next
r_struct
id|flash_block_list
op_star
id|next
suffix:semicolon
DECL|member|blocks
r_struct
id|flash_block
id|blocks
(braket
id|FLASH_BLOCKS_PER_NODE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|flash_block_list_header
r_struct
id|flash_block_list_header
(brace
multiline_comment|/* just the header of flash_block_list */
DECL|member|num_blocks
r_int
r_int
id|num_blocks
suffix:semicolon
DECL|member|next
r_struct
id|flash_block_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|flash_block_list_header
id|rtas_firmware_flash_list
suffix:semicolon
r_extern
r_struct
id|rtas_t
id|rtas
suffix:semicolon
r_extern
r_void
id|enter_rtas
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|rtas_token
c_func
(paren
r_const
r_char
op_star
id|service
)paren
suffix:semicolon
r_extern
r_int
id|rtas_call
c_func
(paren
r_int
id|token
comma
r_int
comma
r_int
comma
r_int
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|call_rtas_display_status
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|rtas_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|rtas_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtas_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rtas_os_term
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_int
id|rtas_get_sensor
c_func
(paren
r_int
id|sensor
comma
r_int
id|index
comma
r_int
op_star
id|state
)paren
suffix:semicolon
r_extern
r_int
id|rtas_get_power_level
c_func
(paren
r_int
id|powerdomain
comma
r_int
op_star
id|level
)paren
suffix:semicolon
r_extern
r_int
id|rtas_set_power_level
c_func
(paren
r_int
id|powerdomain
comma
r_int
id|level
comma
r_int
op_star
id|setlevel
)paren
suffix:semicolon
r_extern
r_int
id|rtas_set_indicator
c_func
(paren
r_int
id|indicator
comma
r_int
id|index
comma
r_int
id|new_value
)paren
suffix:semicolon
r_extern
r_void
id|rtas_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Given an RTAS status code of 9900..9905 compute the hinted delay */
r_int
r_int
id|rtas_extended_busy_delay_time
c_func
(paren
r_int
id|status
)paren
suffix:semicolon
DECL|function|rtas_is_extended_busy
r_static
r_inline
r_int
id|rtas_is_extended_busy
c_func
(paren
r_int
id|status
)paren
(brace
r_return
id|status
op_ge
l_int|9900
op_logical_and
id|status
op_le
l_int|9909
suffix:semicolon
)brace
r_extern
r_void
id|pSeries_log_error
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|err_type
comma
r_int
id|fatal
)paren
suffix:semicolon
multiline_comment|/* Error types logged.  */
DECL|macro|ERR_FLAG_ALREADY_LOGGED
mdefine_line|#define ERR_FLAG_ALREADY_LOGGED&t;0x0
DECL|macro|ERR_FLAG_BOOT
mdefine_line|#define ERR_FLAG_BOOT&t;&t;0x1 &t;/* log was pulled from NVRAM on boot */
DECL|macro|ERR_TYPE_RTAS_LOG
mdefine_line|#define ERR_TYPE_RTAS_LOG&t;0x2&t;/* from rtas event-scan */
DECL|macro|ERR_TYPE_KERNEL_PANIC
mdefine_line|#define ERR_TYPE_KERNEL_PANIC&t;0x4&t;/* from panic() */
multiline_comment|/* All the types and not flags */
DECL|macro|ERR_TYPE_MASK
mdefine_line|#define ERR_TYPE_MASK&t;(ERR_TYPE_RTAS_LOG | ERR_TYPE_KERNEL_PANIC)
DECL|macro|RTAS_DEBUG
mdefine_line|#define RTAS_DEBUG KERN_DEBUG &quot;RTAS: &quot;
DECL|macro|RTAS_ERROR_LOG_MAX
mdefine_line|#define RTAS_ERROR_LOG_MAX 2048
multiline_comment|/*&n; * Return the firmware-specified size of the error log buffer&n; *  for all rtas calls that require an error buffer argument.&n; *  This includes &squot;check-exception&squot; and &squot;rtas-last-error&squot;.&n; */
r_extern
r_int
id|rtas_get_error_log_max
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Event Scan Parameters */
DECL|macro|EVENT_SCAN_ALL_EVENTS
mdefine_line|#define EVENT_SCAN_ALL_EVENTS&t;0xf0000000
DECL|macro|SURVEILLANCE_TOKEN
mdefine_line|#define SURVEILLANCE_TOKEN&t;9000
DECL|macro|LOG_NUMBER
mdefine_line|#define LOG_NUMBER&t;&t;64&t;&t;/* must be a power of two */
DECL|macro|LOG_NUMBER_MASK
mdefine_line|#define LOG_NUMBER_MASK&t;&t;(LOG_NUMBER-1)
multiline_comment|/* Some RTAS ops require a data buffer and that buffer must be &lt; 4G.&n; * Rather than having a memory allocator, just use this buffer&n; * (get the lock first), make the RTAS call.  Copy the data instead&n; * of holding the buffer for long.&n; */
DECL|macro|RTAS_DATA_BUF_SIZE
mdefine_line|#define RTAS_DATA_BUF_SIZE 4096
r_extern
id|spinlock_t
id|rtas_data_buf_lock
suffix:semicolon
r_extern
r_char
id|rtas_data_buf
(braket
id|RTAS_DATA_BUF_SIZE
)braket
suffix:semicolon
r_extern
r_void
id|rtas_stop_self
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* RMO buffer reserved for user-space RTAS use */
r_extern
r_int
r_int
id|rtas_rmo_buf
suffix:semicolon
macro_line|#endif /* _PPC64_RTAS_H */
eof
