multiline_comment|/******************************************************************************&n; *&n; * Module Name: processor.h&n; *              $Revision: 9 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __PR_H__
DECL|macro|__PR_H__
mdefine_line|#define __PR_H__
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                             Types &amp; Other Defines&n; *****************************************************************************/
DECL|macro|PR_MAX_POWER_STATES
mdefine_line|#define PR_MAX_POWER_STATES&t;4
DECL|macro|PR_MAX_THROTTLE_STATES
mdefine_line|#define PR_MAX_THROTTLE_STATES  8
DECL|macro|PR_MAX_PERF_STATES
mdefine_line|#define PR_MAX_PERF_STATES&t;32
DECL|macro|PR_MAX_C2_LATENCY
mdefine_line|#define PR_MAX_C2_LATENCY&t;100
DECL|macro|PR_MAX_C3_LATENCY
mdefine_line|#define PR_MAX_C3_LATENCY&t;1000
multiline_comment|/*&n; * Commands:&n; * ---------&n; */
DECL|macro|PR_COMMAND_GET_POWER_INFO
mdefine_line|#define PR_COMMAND_GET_POWER_INFO ((BM_COMMAND) 0x80)
DECL|macro|PR_COMMAND_SET_POWER_INFO
mdefine_line|#define PR_COMMAND_SET_POWER_INFO ((BM_COMMAND) 0x81)
DECL|macro|PR_COMMAND_GET_PERF_INFO
mdefine_line|#define PR_COMMAND_GET_PERF_INFO ((BM_COMMAND) 0x82)
DECL|macro|PR_COMMAND_GET_PERF_STATE
mdefine_line|#define PR_COMMAND_GET_PERF_STATE ((BM_COMMAND) 0x83)
DECL|macro|PR_COMMAND_SET_PERF_LIMIT
mdefine_line|#define PR_COMMAND_SET_PERF_LIMIT ((BM_COMMAND) 0x84)
multiline_comment|/*&n; * Notifications:&n; * --------------&n; */
DECL|macro|PR_NOTIFY_PERF_STATES
mdefine_line|#define PR_NOTIFY_PERF_STATES&t;((BM_NOTIFY) 0x80)
DECL|macro|PR_NOTIFY_POWER_STATES
mdefine_line|#define PR_NOTIFY_POWER_STATES&t;((BM_NOTIFY) 0x81)
multiline_comment|/*&n; * Performance Control:&n; * --------------------&n; */
DECL|macro|PR_PERF_DEC
mdefine_line|#define PR_PERF_DEC&t;&t;0x00
DECL|macro|PR_PERF_INC
mdefine_line|#define PR_PERF_INC&t;&t;0x01
DECL|macro|PR_PERF_MAX
mdefine_line|#define PR_PERF_MAX&t;&t;0xFF
multiline_comment|/*&n; * Power States:&n; * -------------&n; */
DECL|macro|PR_C0
mdefine_line|#define PR_C0&t;&t;&t;0x00
DECL|macro|PR_C1
mdefine_line|#define PR_C1&t;&t;&t;0x01
DECL|macro|PR_C2
mdefine_line|#define PR_C2&t;&t;&t;0x02
DECL|macro|PR_C3
mdefine_line|#define PR_C3&t;&t;&t;0x03
DECL|macro|PR_C1_FLAG
mdefine_line|#define PR_C1_FLAG&t;&t;0x01;
DECL|macro|PR_C2_FLAG
mdefine_line|#define PR_C2_FLAG&t;&t;0x02;
DECL|macro|PR_C3_FLAG
mdefine_line|#define PR_C3_FLAG&t;&t;0x04;
multiline_comment|/*&n; * PR_CX_POLICY_VALUES:&n; * --------------------&n; */
r_typedef
r_struct
(brace
DECL|member|time_threshold
id|u32
id|time_threshold
suffix:semicolon
DECL|member|count_threshold
id|u32
id|count_threshold
suffix:semicolon
DECL|member|bm_threshold
id|u32
id|bm_threshold
suffix:semicolon
DECL|member|target_state
id|u32
id|target_state
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|typedef|PR_CX_POLICY_VALUES
)brace
id|PR_CX_POLICY_VALUES
suffix:semicolon
multiline_comment|/*&n; * PR_CX:&n; * ------&n; */
r_typedef
r_struct
(brace
DECL|member|latency
id|u32
id|latency
suffix:semicolon
DECL|member|utilization
id|u32
id|utilization
suffix:semicolon
DECL|member|is_valid
id|u8
id|is_valid
suffix:semicolon
DECL|member|promotion
id|PR_CX_POLICY_VALUES
id|promotion
suffix:semicolon
DECL|member|demotion
id|PR_CX_POLICY_VALUES
id|demotion
suffix:semicolon
DECL|typedef|PR_CX
)brace
id|PR_CX
suffix:semicolon
multiline_comment|/*&n; * PR_POWER:&n; * ---------&n; */
r_typedef
r_struct
(brace
DECL|member|p_lvl2
id|ACPI_PHYSICAL_ADDRESS
id|p_lvl2
suffix:semicolon
DECL|member|p_lvl3
id|ACPI_PHYSICAL_ADDRESS
id|p_lvl3
suffix:semicolon
DECL|member|bm_activity
id|u32
id|bm_activity
suffix:semicolon
DECL|member|active_state
id|u32
id|active_state
suffix:semicolon
DECL|member|default_state
id|u32
id|default_state
suffix:semicolon
DECL|member|busy_metric
id|u32
id|busy_metric
suffix:semicolon
DECL|member|state_count
id|u32
id|state_count
suffix:semicolon
DECL|member|state
id|PR_CX
id|state
(braket
id|PR_MAX_POWER_STATES
)braket
suffix:semicolon
DECL|typedef|PR_POWER
)brace
id|PR_POWER
suffix:semicolon
multiline_comment|/*&n; * PR_PERFORMANCE_STATE:&n; * ---------------------&n; */
r_typedef
r_struct
(brace
DECL|member|performance
id|u32
id|performance
suffix:semicolon
DECL|member|power
id|u32
id|power
suffix:semicolon
DECL|typedef|PR_PERFORMANCE_STATE
)brace
id|PR_PERFORMANCE_STATE
suffix:semicolon
multiline_comment|/*&n; * PR_PERFORMANCE:&n; * ---------------&n; */
r_typedef
r_struct
(brace
DECL|member|active_state
id|u32
id|active_state
suffix:semicolon
DECL|member|thermal_limit
id|u32
id|thermal_limit
suffix:semicolon
DECL|member|power_limit
id|u32
id|power_limit
suffix:semicolon
DECL|member|state_count
id|u32
id|state_count
suffix:semicolon
DECL|member|state
id|PR_PERFORMANCE_STATE
id|state
(braket
id|PR_MAX_PERF_STATES
)braket
suffix:semicolon
DECL|typedef|PR_PERFORMANCE
)brace
id|PR_PERFORMANCE
suffix:semicolon
multiline_comment|/*&n; * PR_PBLOCK:&n; * ----------&n; */
r_typedef
r_struct
(brace
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|ACPI_PHYSICAL_ADDRESS
id|address
suffix:semicolon
DECL|typedef|PR_PBLOCK
)brace
id|PR_PBLOCK
suffix:semicolon
multiline_comment|/*&n; * PR_CONTEXT:&n; * -----------&n; */
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
id|u32
id|uid
suffix:semicolon
DECL|member|pblk
id|PR_PBLOCK
id|pblk
suffix:semicolon
DECL|member|power
id|PR_POWER
id|power
suffix:semicolon
DECL|member|performance
id|PR_PERFORMANCE
id|performance
suffix:semicolon
DECL|typedef|PR_CONTEXT
)brace
id|PR_CONTEXT
suffix:semicolon
multiline_comment|/******************************************************************************&n; *                             Function Prototypes&n; *****************************************************************************/
multiline_comment|/* processor.c */
id|acpi_status
id|pr_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|pr_terminate
c_func
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|pr_notify
(paren
id|BM_NOTIFY
id|notify_type
comma
id|BM_HANDLE
id|device_handle
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|pr_request
c_func
(paren
id|BM_REQUEST
op_star
id|request
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* prpower.c */
r_void
id|pr_power_idle
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|pr_power_add_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
id|acpi_status
id|pr_power_remove_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
id|acpi_status
id|pr_power_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|pr_power_terminate
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* prperf.c */
id|acpi_status
id|pr_perf_get_state
(paren
id|PR_CONTEXT
op_star
id|processor
comma
id|u32
op_star
id|state
)paren
suffix:semicolon
id|acpi_status
id|pr_perf_set_state
(paren
id|PR_CONTEXT
op_star
id|processor
comma
id|u32
id|state
)paren
suffix:semicolon
id|acpi_status
id|pr_perf_set_limit
(paren
id|PR_CONTEXT
op_star
id|processor
comma
id|u32
id|limit
)paren
suffix:semicolon
id|acpi_status
id|pr_perf_add_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
id|acpi_status
id|pr_perf_remove_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
multiline_comment|/* Processor Driver OSL */
id|acpi_status
id|pr_osl_add_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
id|acpi_status
id|pr_osl_remove_device
(paren
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
id|acpi_status
id|pr_osl_generate_event
(paren
id|u32
id|event
comma
id|PR_CONTEXT
op_star
id|processor
)paren
suffix:semicolon
macro_line|#endif  /* __PR_H__ */
eof
