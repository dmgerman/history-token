multiline_comment|/*****************************************************************************&n; *&n; * Module name: bmpower.h&n; *   $Revision: 9 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __BMPOWER_H__
DECL|macro|__BMPOWER_H__
mdefine_line|#define __BMPOWER_H__
macro_line|#include &quot;bm.h&quot;
multiline_comment|/*****************************************************************************&n; *                               Types &amp; Defines&n; *****************************************************************************/
multiline_comment|/*&n; * BM_POWER_RESOURCE:&n; * ------------------&n; */
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
DECL|member|system_level
id|BM_POWER_STATE
id|system_level
suffix:semicolon
DECL|member|resource_order
id|u32
id|resource_order
suffix:semicolon
DECL|member|state
id|BM_POWER_STATE
id|state
suffix:semicolon
DECL|member|reference_count
id|u32
id|reference_count
suffix:semicolon
DECL|typedef|BM_POWER_RESOURCE
)brace
id|BM_POWER_RESOURCE
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                             Function Prototypes&n; *****************************************************************************/
multiline_comment|/* bmpower.c */
id|acpi_status
id|bm_pr_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bm_pr_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|bm_pr_list_get_state
(paren
id|BM_HANDLE_LIST
op_star
id|resource_list
comma
id|BM_POWER_STATE
op_star
id|power_state
)paren
suffix:semicolon
id|acpi_status
id|bm_pr_list_transition
(paren
id|BM_HANDLE_LIST
op_star
id|current_list
comma
id|BM_HANDLE_LIST
op_star
id|target_list
)paren
suffix:semicolon
macro_line|#endif  /* __BMPOWER_H__ */
eof
