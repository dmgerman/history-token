multiline_comment|/******************************************************************************&n; *&n; * Module Name: bn.h&n; *   $Revision: 10 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __BN_H__
DECL|macro|__BN_H__
mdefine_line|#define __BN_H__
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                            Types &amp; Other Defines&n; *****************************************************************************/
multiline_comment|/*&n; * Notifications:&n; * ---------------------&n; */
DECL|macro|BN_NOTIFY_STATUS_CHANGE
mdefine_line|#define BN_NOTIFY_STATUS_CHANGE&t;((BM_NOTIFY) 0x80)
multiline_comment|/*&n; * Types:&n; * ------&n; */
DECL|macro|BN_TYPE_POWER_BUTTON
mdefine_line|#define BN_TYPE_POWER_BUTTON&t;0x01
DECL|macro|BN_TYPE_POWER_BUTTON_FIXED
mdefine_line|#define BN_TYPE_POWER_BUTTON_FIXED 0x02
DECL|macro|BN_TYPE_SLEEP_BUTTON
mdefine_line|#define BN_TYPE_SLEEP_BUTTON&t;0x03
DECL|macro|BN_TYPE_SLEEP_BUTTON_FIXED
mdefine_line|#define BN_TYPE_SLEEP_BUTTON_FIXED 0x04
DECL|macro|BN_TYPE_LID_SWITCH
mdefine_line|#define BN_TYPE_LID_SWITCH&t;0x05
multiline_comment|/*&n; * Hardware IDs:&n; * -------------&n; * TBD: Power and Sleep button HIDs also exist in &lt;bm.h&gt;.  Should all&n; *      HIDs (ACPI well-known devices) exist in one place (e.g.&n; *      acpi_hid.h)?&n; */
DECL|macro|BN_HID_POWER_BUTTON
mdefine_line|#define BN_HID_POWER_BUTTON&t;&quot;PNP0C0C&quot;
DECL|macro|BN_HID_SLEEP_BUTTON
mdefine_line|#define BN_HID_SLEEP_BUTTON&t;&quot;PNP0C0E&quot;
DECL|macro|BN_HID_LID_SWITCH
mdefine_line|#define BN_HID_LID_SWITCH&t;&quot;PNP0C0D&quot;
multiline_comment|/*&n; * Device Context:&n; * ---------------&n; */
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
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|typedef|BN_CONTEXT
)brace
id|BN_CONTEXT
suffix:semicolon
multiline_comment|/******************************************************************************&n; *                              Function Prototypes&n; *****************************************************************************/
id|acpi_status
id|bn_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bn_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bn_notify_fixed
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|bn_notify
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
id|bn_request
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
multiline_comment|/* Button OSL */
id|acpi_status
id|bn_osl_add_device
(paren
id|BN_CONTEXT
op_star
id|button
)paren
suffix:semicolon
id|acpi_status
id|bn_osl_remove_device
(paren
id|BN_CONTEXT
op_star
id|button
)paren
suffix:semicolon
id|acpi_status
id|bn_osl_generate_event
(paren
id|u32
id|event
comma
id|BN_CONTEXT
op_star
id|button
)paren
suffix:semicolon
macro_line|#endif&t;/* __BN_H__ */
eof
