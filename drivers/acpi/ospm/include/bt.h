multiline_comment|/******************************************************************************&n; *&n; * Module Name: bt.h&n; *   $Revision: 18 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __BT_H__
DECL|macro|__BT_H__
mdefine_line|#define __BT_H__
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                Types &amp; Other Defines&n; *****************************************************************************/
multiline_comment|/*! [Begin] no source code translation */
DECL|macro|BT_UNKNOWN
mdefine_line|#define BT_UNKNOWN&t;&t;0xFFFFFFFF
DECL|macro|BT_POWER_UNITS_DEFAULT
mdefine_line|#define BT_POWER_UNITS_DEFAULT  &quot;?&quot;
DECL|macro|BT_POWER_UNITS_WATTS
mdefine_line|#define BT_POWER_UNITS_WATTS    &quot;mW&quot;
DECL|macro|BT_POWER_UNITS_AMPS
mdefine_line|#define BT_POWER_UNITS_AMPS&t;&quot;mA&quot;
multiline_comment|/*! [End] no source code translation !*/
multiline_comment|/*&n; * Battery Notifications:&n; * ----------------------&n; */
DECL|macro|BT_NOTIFY_STATUS_CHANGE
mdefine_line|#define BT_NOTIFY_STATUS_CHANGE ((BM_NOTIFY) 0x80)
DECL|macro|BT_NOTIFY_INFORMATION_CHANGE
mdefine_line|#define BT_NOTIFY_INFORMATION_CHANGE ((BM_NOTIFY) 0x81)
multiline_comment|/*&n; * Hardware IDs:&n; * -------------&n; */
DECL|macro|BT_HID_CM_BATTERY
mdefine_line|#define BT_HID_CM_BATTERY   &quot;PNP0C0A&quot;
multiline_comment|/*&n; * BT_CM_BATTERY_INFO:&n; * -------------------&n; */
r_typedef
r_struct
(brace
DECL|member|power_unit
id|acpi_integer
id|power_unit
suffix:semicolon
DECL|member|design_capacity
id|acpi_integer
id|design_capacity
suffix:semicolon
DECL|member|last_full_capacity
id|acpi_integer
id|last_full_capacity
suffix:semicolon
DECL|member|battery_technology
id|acpi_integer
id|battery_technology
suffix:semicolon
DECL|member|design_voltage
id|acpi_integer
id|design_voltage
suffix:semicolon
DECL|member|design_capacity_warning
id|acpi_integer
id|design_capacity_warning
suffix:semicolon
DECL|member|design_capacity_low
id|acpi_integer
id|design_capacity_low
suffix:semicolon
DECL|member|battery_capacity_granularity_1
id|acpi_integer
id|battery_capacity_granularity_1
suffix:semicolon
DECL|member|battery_capacity_granularity_2
id|acpi_integer
id|battery_capacity_granularity_2
suffix:semicolon
DECL|member|model_number
id|acpi_string
id|model_number
suffix:semicolon
DECL|member|serial_number
id|acpi_string
id|serial_number
suffix:semicolon
DECL|member|battery_type
id|acpi_string
id|battery_type
suffix:semicolon
DECL|member|oem_info
id|acpi_string
id|oem_info
suffix:semicolon
DECL|typedef|BT_BATTERY_INFO
)brace
id|BT_BATTERY_INFO
suffix:semicolon
multiline_comment|/*&n; * BT_CM_BATTERY_STATUS:&n; * ---------------------&n; */
r_typedef
r_struct
(brace
DECL|member|state
id|acpi_integer
id|state
suffix:semicolon
DECL|member|present_rate
id|acpi_integer
id|present_rate
suffix:semicolon
DECL|member|remaining_capacity
id|acpi_integer
id|remaining_capacity
suffix:semicolon
DECL|member|present_voltage
id|acpi_integer
id|present_voltage
suffix:semicolon
DECL|typedef|BT_BATTERY_STATUS
)brace
id|BT_BATTERY_STATUS
suffix:semicolon
multiline_comment|/*&n; * BT_CONTEXT:&n; * -----------&n; */
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
DECL|member|power_units
id|acpi_string
id|power_units
suffix:semicolon
DECL|member|is_present
id|u8
id|is_present
suffix:semicolon
DECL|typedef|BT_CONTEXT
)brace
id|BT_CONTEXT
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *              Function Prototypes&n; *****************************************************************************/
multiline_comment|/* bt.c */
id|acpi_status
id|bt_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bt_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bt_notify
(paren
id|u32
id|notify_type
comma
id|u32
id|device
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|bt_request
c_func
(paren
id|BM_REQUEST
op_star
id|request_info
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|bt_get_status
(paren
id|BT_CONTEXT
op_star
id|battery
comma
id|BT_BATTERY_STATUS
op_star
op_star
id|battery_status
)paren
suffix:semicolon
id|acpi_status
id|bt_get_info
(paren
id|BT_CONTEXT
op_star
id|battery
comma
id|BT_BATTERY_INFO
op_star
op_star
id|battery_info
)paren
suffix:semicolon
multiline_comment|/* Battery OSL */
id|acpi_status
id|bt_osl_add_device
(paren
id|BT_CONTEXT
op_star
id|battery
)paren
suffix:semicolon
id|acpi_status
id|bt_osl_remove_device
(paren
id|BT_CONTEXT
op_star
id|battery
)paren
suffix:semicolon
id|acpi_status
id|bt_osl_generate_event
(paren
id|u32
id|event
comma
id|BT_CONTEXT
op_star
id|battery
)paren
suffix:semicolon
macro_line|#endif  /* __BT_H__ */
eof
