multiline_comment|/*****************************************************************************&n; *&n; * Module Name: tz.h&n; *   $Revision: 24 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __TZ_H__
DECL|macro|__TZ_H__
mdefine_line|#define __TZ_H__
multiline_comment|/* TBD: Linux-specific */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;bm.h&gt;
macro_line|#include &lt;pr.h&gt;
multiline_comment|/*****************************************************************************&n; *                             Types &amp; Other Defines&n; *****************************************************************************/
DECL|macro|TZ_MAX_THRESHOLDS
mdefine_line|#define TZ_MAX_THRESHOLDS&t;12&t;/* _AC0 through _AC9 + _CRT + _PSV */
DECL|macro|TZ_MAX_ACTIVE_THRESHOLDS
mdefine_line|#define TZ_MAX_ACTIVE_THRESHOLDS 10&t;/* _AC0 through _AC9 */
DECL|macro|TZ_MAX_COOLING_DEVICES
mdefine_line|#define TZ_MAX_COOLING_DEVICES&t;10&t;/* TBD: Make size dynamic */
multiline_comment|/*&n; * Notifications:&n; * --------------&n; */
DECL|macro|TZ_NOTIFY_TEMPERATURE_CHANGE
mdefine_line|#define TZ_NOTIFY_TEMPERATURE_CHANGE ((BM_NOTIFY) 0x80)
DECL|macro|TZ_NOTIFY_THRESHOLD_CHANGE
mdefine_line|#define TZ_NOTIFY_THRESHOLD_CHANGE ((BM_NOTIFY) 0x81)
DECL|macro|TZ_NOTIFY_DEVICE_LISTS_CHANGE
mdefine_line|#define TZ_NOTIFY_DEVICE_LISTS_CHANGE ((BM_NOTIFY) 0x82)
multiline_comment|/*&n; * TZ_THRESHOLD_TYPE:&n; * ------------------&n; */
DECL|typedef|TZ_THRESHOLD_TYPE
r_typedef
id|u32
id|TZ_THRESHOLD_TYPE
suffix:semicolon
DECL|macro|TZ_THRESHOLD_UNKNOWN
mdefine_line|#define TZ_THRESHOLD_UNKNOWN&t;((TZ_THRESHOLD_TYPE) 0x00)
DECL|macro|TZ_THRESHOLD_CRITICAL
mdefine_line|#define TZ_THRESHOLD_CRITICAL&t;((TZ_THRESHOLD_TYPE) 0x01)
DECL|macro|TZ_THRESHOLD_PASSIVE
mdefine_line|#define TZ_THRESHOLD_PASSIVE&t;((TZ_THRESHOLD_TYPE) 0x02)
DECL|macro|TZ_THRESHOLD_ACTIVE
mdefine_line|#define TZ_THRESHOLD_ACTIVE&t;((TZ_THRESHOLD_TYPE) 0x03)
multiline_comment|/*&n; * TZ_COOLING_STATE:&n; * -----------------&n; */
DECL|typedef|TZ_COOLING_STATE
r_typedef
id|u32
id|TZ_COOLING_STATE
suffix:semicolon
DECL|macro|TZ_COOLING_UNKNOWN
mdefine_line|#define TZ_COOLING_UNKNOWN&t;((TZ_COOLING_STATE) 0x00)
DECL|macro|TZ_COOLING_ENABLED
mdefine_line|#define TZ_COOLING_ENABLED&t;((TZ_COOLING_STATE) 0x01)
DECL|macro|TZ_COOLING_DISABLED
mdefine_line|#define TZ_COOLING_DISABLED&t;((TZ_COOLING_STATE) 0x02)
multiline_comment|/*&n; * TZ_COOLING_MODE:&n; * ----------------&n; */
DECL|typedef|TZ_COOLING_MODE
r_typedef
id|u32
id|TZ_COOLING_MODE
suffix:semicolon
DECL|macro|TZ_COOLING_MODE_ACTIVE
mdefine_line|#define TZ_COOLING_MODE_ACTIVE&t;((TZ_COOLING_MODE) 0x00)
DECL|macro|TZ_COOLING_MODE_PASSIVE
mdefine_line|#define TZ_COOLING_MODE_PASSIVE&t;((TZ_COOLING_MODE) 0x01)
multiline_comment|/*&n; * Thermal State:&n; * --------------&n; * The encoding of TZ_STATE is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the device has dynamic status).&n; * No bits set indicates an OK cooling state.&n; * +--+--+--+-----------+----------+&n; * |31|30|29| Bits 27:4 | Bits 3:0 |&n; * +--+--+--+-----------+----------+&n; *  |  |  |       |          |&n; *  |  |  |       |          +------ Active Index&n; *  |  |  |       +----------------- &lt;reserved&gt;&n; *  |  |  +------------------------- Active&n; *  |  +---------------------------- Passive&n; *  +------------------------------- Critical&n; *&n; * Active Index:    Value representing the level of active cooling&n; *                  presently applied (e.g. 0=_AL0, 9=_AL9).  Only&n; *                  valid when &squot;Active&squot; is set.&n; * Active:          If set, indicates that the system temperature&n; *                  has crossed at least one active threshold (_ALx).&n; * Passive:         If set, indicates that the system temperature&n; *                  has crossed the passive threshold (_PSL).&n; * Passive:         If set, indicates that the system temperature&n; *                  has crossed the critical threshold (_CRT).&n; */
DECL|typedef|TZ_STATE
r_typedef
id|u32
id|TZ_STATE
suffix:semicolon
DECL|macro|TZ_STATE_OK
mdefine_line|#define TZ_STATE_OK&t;&t;((TZ_STATE) 0x00000000)
DECL|macro|TZ_STATE_HOT
mdefine_line|#define TZ_STATE_HOT&t;&t;((TZ_STATE) 0x10000000)
DECL|macro|TZ_STATE_ACTIVE
mdefine_line|#define TZ_STATE_ACTIVE&t;&t;((TZ_STATE) 0x20000000)
DECL|macro|TZ_STATE_PASSIVE
mdefine_line|#define TZ_STATE_PASSIVE&t;((TZ_STATE) 0x40000000)
DECL|macro|TZ_STATE_CRITICAL
mdefine_line|#define TZ_STATE_CRITICAL&t;((TZ_STATE) 0x80000000)
r_typedef
r_struct
(brace
DECL|member|temperature
id|u32
id|temperature
suffix:semicolon
DECL|typedef|TZ_CRITICAL_THRESHOLD
)brace
id|TZ_CRITICAL_THRESHOLD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|is_valid
id|u8
id|is_valid
suffix:semicolon
DECL|member|temperature
id|u32
id|temperature
suffix:semicolon
DECL|typedef|TZ_HOT_THRESHOLD
)brace
id|TZ_HOT_THRESHOLD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|is_valid
id|u8
id|is_valid
suffix:semicolon
DECL|member|temperature
id|u32
id|temperature
suffix:semicolon
DECL|member|tc1
id|u32
id|tc1
suffix:semicolon
DECL|member|tc2
id|u32
id|tc2
suffix:semicolon
DECL|member|tsp
id|u32
id|tsp
suffix:semicolon
DECL|member|devices
id|BM_HANDLE_LIST
id|devices
suffix:semicolon
DECL|typedef|TZ_PASSIVE_THRESHOLD
)brace
id|TZ_PASSIVE_THRESHOLD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|is_valid
id|u8
id|is_valid
suffix:semicolon
DECL|member|temperature
id|u32
id|temperature
suffix:semicolon
DECL|member|cooling_state
id|TZ_COOLING_STATE
id|cooling_state
suffix:semicolon
DECL|member|devices
id|BM_HANDLE_LIST
id|devices
suffix:semicolon
DECL|typedef|TZ_ACTIVE_THRESHOLD
)brace
id|TZ_ACTIVE_THRESHOLD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|critical
id|TZ_CRITICAL_THRESHOLD
id|critical
suffix:semicolon
DECL|member|hot
id|TZ_HOT_THRESHOLD
id|hot
suffix:semicolon
DECL|member|passive
id|TZ_PASSIVE_THRESHOLD
id|passive
suffix:semicolon
DECL|member|active
id|TZ_ACTIVE_THRESHOLD
id|active
(braket
id|TZ_MAX_ACTIVE_THRESHOLDS
)braket
suffix:semicolon
DECL|typedef|TZ_THRESHOLDS
)brace
id|TZ_THRESHOLDS
suffix:semicolon
multiline_comment|/*&n; * TZ_POLICY:&n; * ---------&n; */
r_typedef
r_struct
(brace
DECL|member|temperature
id|u32
id|temperature
suffix:semicolon
DECL|member|state
id|TZ_STATE
id|state
suffix:semicolon
DECL|member|cooling_mode
id|TZ_COOLING_MODE
id|cooling_mode
suffix:semicolon
DECL|member|polling_freq
id|u32
id|polling_freq
suffix:semicolon
DECL|member|thresholds
id|TZ_THRESHOLDS
id|thresholds
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|typedef|TZ_POLICY
)brace
id|TZ_POLICY
suffix:semicolon
multiline_comment|/*&n; * TZ_CONTEXT:&n; * -----------&n; */
r_typedef
r_struct
(brace
DECL|member|device_handle
id|BM_HANDLE
id|device_handle
suffix:semicolon
DECL|member|acpi_handle
id|acpi_handle
id|acpi_handle
suffix:semicolon
DECL|member|uid
r_char
id|uid
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|policy
id|TZ_POLICY
id|policy
suffix:semicolon
DECL|typedef|TZ_CONTEXT
)brace
id|TZ_CONTEXT
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                             Function Prototypes&n; *****************************************************************************/
multiline_comment|/* tz.c */
id|acpi_status
id|tz_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|tz_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|tz_notify
(paren
id|BM_NOTIFY
id|notify_type
comma
id|BM_HANDLE
id|device_handle
comma
id|BM_DRIVER_CONTEXT
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|tz_request
(paren
id|BM_REQUEST
op_star
id|request
comma
id|BM_DRIVER_CONTEXT
id|context
)paren
suffix:semicolon
id|acpi_status
id|tz_get_temperature
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
id|acpi_status
id|tz_get_thresholds
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
id|acpi_status
id|tz_set_cooling_preference
(paren
id|TZ_CONTEXT
op_star
id|tz
comma
id|TZ_COOLING_MODE
id|cooling_mode
)paren
suffix:semicolon
r_void
id|tz_print
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
multiline_comment|/* tzpolicy.c */
id|acpi_status
id|tz_policy_add_device
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
id|acpi_status
id|tz_policy_remove_device
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
r_void
id|tz_policy_check
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* tz_osl.c */
id|acpi_status
id|tz_osl_add_device
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
id|acpi_status
id|tz_osl_remove_device
(paren
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
id|acpi_status
id|tz_osl_generate_event
(paren
id|u32
id|event
comma
id|TZ_CONTEXT
op_star
id|tz
)paren
suffix:semicolon
macro_line|#endif  /* __TZ_H__ */
eof
