multiline_comment|/*****************************************************************************&n; *&n; * Module Name: ac.h&n; *   $Revision: 6 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __AC_H__
DECL|macro|__AC_H__
mdefine_line|#define __AC_H__
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                            Types &amp; Other Defines&n; *****************************************************************************/
multiline_comment|/*&n; * Notifications:&n; * --------------&n; */
DECL|macro|AC_NOTIFY_STATUS_CHANGE
mdefine_line|#define AC_NOTIFY_STATUS_CHANGE&t;((BM_NOTIFY) 0x80)
multiline_comment|/*&n; * Hardware IDs:&n; * -------------&n; */
DECL|macro|AC_HID_AC_ADAPTER
mdefine_line|#define AC_HID_AC_ADAPTER&t;&quot;ACPI0003&quot;
multiline_comment|/*&n; * Device Context:&n; * ---------------&n; */
r_typedef
r_struct
(brace
DECL|member|device_handle
id|BM_HANDLE
id|device_handle
suffix:semicolon
DECL|member|acpi_handle
id|ACPI_HANDLE
id|acpi_handle
suffix:semicolon
DECL|member|uid
r_char
id|uid
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|is_online
id|u32
id|is_online
suffix:semicolon
DECL|typedef|AC_CONTEXT
)brace
id|AC_CONTEXT
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                              Function Prototypes&n; *****************************************************************************/
id|ACPI_STATUS
id|ac_initialize
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|ac_terminate
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|ac_notify
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
id|ACPI_STATUS
id|ac_request
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
multiline_comment|/* AC Adapter Driver OSL */
id|ACPI_STATUS
id|ac_osl_add_device
(paren
id|AC_CONTEXT
op_star
id|ac_adapter
)paren
suffix:semicolon
id|ACPI_STATUS
id|ac_osl_remove_device
(paren
id|AC_CONTEXT
op_star
id|ac_adapter
)paren
suffix:semicolon
id|ACPI_STATUS
id|ac_osl_generate_event
(paren
id|u32
id|event
comma
id|AC_CONTEXT
op_star
id|ac_adapter
)paren
suffix:semicolon
macro_line|#endif&t;/* __AC_H__ */
eof
