multiline_comment|/*****************************************************************************&n; *&n; * Module Name: sm.h&n; *   $Revision: 3 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __SM_H__
DECL|macro|__SM_H__
mdefine_line|#define __SM_H__
macro_line|#include &lt;actypes.h&gt;
macro_line|#include &lt;acexcep.h&gt;
macro_line|#include &lt;bm.h&gt;
multiline_comment|/*****************************************************************************&n; *                            Types &amp; Other Defines&n; *****************************************************************************/
DECL|macro|SM_MAX_SYSTEM_STATES
mdefine_line|#define SM_MAX_SYSTEM_STATES&t;6&t;/* S0-S5 */
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
DECL|member|states
id|u8
id|states
(braket
id|SM_MAX_SYSTEM_STATES
)braket
suffix:semicolon
DECL|typedef|SM_CONTEXT
)brace
id|SM_CONTEXT
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                              Function Prototypes&n; *****************************************************************************/
id|acpi_status
id|sm_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|sm_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|sm_notify
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
id|sm_request
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
multiline_comment|/* System Driver OSL */
id|acpi_status
id|sm_osl_add_device
(paren
id|SM_CONTEXT
op_star
id|system
)paren
suffix:semicolon
id|acpi_status
id|sm_osl_remove_device
(paren
id|SM_CONTEXT
op_star
id|system
)paren
suffix:semicolon
id|acpi_status
id|sm_osl_generate_event
(paren
id|u32
id|event
comma
id|SM_CONTEXT
op_star
id|system
)paren
suffix:semicolon
macro_line|#endif&t;/* __SM_H__ */
eof
