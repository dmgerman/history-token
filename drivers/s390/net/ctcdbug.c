multiline_comment|/*&n; *&n; * linux/drivers/s390/net/ctcdbug.c ($Revision: 1.4 $)&n; *&n; * CTC / ESCON network driver - s390 dbf exploit.&n; *&n; * Copyright 2000,2003 IBM Corporation&n; *&n; *    Author(s): Original Code written by&n; *&t;&t;&t;  Peter Tiedemann (ptiedem@de.ibm.com)&n; *&n; *    $Revision: 1.4 $&t; $Date: 2004/08/04 10:11:59 $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &quot;ctcdbug.h&quot;
multiline_comment|/**&n; * Debug Facility Stuff&n; */
DECL|variable|ctc_dbf_setup
id|debug_info_t
op_star
id|ctc_dbf_setup
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|ctc_dbf_data
id|debug_info_t
op_star
id|ctc_dbf_data
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|ctc_dbf_trace
id|debug_info_t
op_star
id|ctc_dbf_trace
op_assign
l_int|NULL
suffix:semicolon
id|DEFINE_PER_CPU
c_func
(paren
r_char
(braket
l_int|256
)braket
comma
id|ctc_dbf_txt_buf
)paren
suffix:semicolon
r_void
DECL|function|ctc_unregister_dbf_views
id|ctc_unregister_dbf_views
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ctc_dbf_setup
)paren
id|debug_unregister
c_func
(paren
id|ctc_dbf_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctc_dbf_data
)paren
id|debug_unregister
c_func
(paren
id|ctc_dbf_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctc_dbf_trace
)paren
id|debug_unregister
c_func
(paren
id|ctc_dbf_trace
)paren
suffix:semicolon
)brace
r_int
DECL|function|ctc_register_dbf_views
id|ctc_register_dbf_views
c_func
(paren
r_void
)paren
(brace
id|ctc_dbf_setup
op_assign
id|debug_register
c_func
(paren
id|CTC_DBF_SETUP_NAME
comma
id|CTC_DBF_SETUP_INDEX
comma
id|CTC_DBF_SETUP_NR_AREAS
comma
id|CTC_DBF_SETUP_LEN
)paren
suffix:semicolon
id|ctc_dbf_data
op_assign
id|debug_register
c_func
(paren
id|CTC_DBF_DATA_NAME
comma
id|CTC_DBF_DATA_INDEX
comma
id|CTC_DBF_DATA_NR_AREAS
comma
id|CTC_DBF_DATA_LEN
)paren
suffix:semicolon
id|ctc_dbf_trace
op_assign
id|debug_register
c_func
(paren
id|CTC_DBF_TRACE_NAME
comma
id|CTC_DBF_TRACE_INDEX
comma
id|CTC_DBF_TRACE_NR_AREAS
comma
id|CTC_DBF_TRACE_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ctc_dbf_setup
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|ctc_dbf_data
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|ctc_dbf_trace
op_eq
l_int|NULL
)paren
)paren
(brace
id|ctc_unregister_dbf_views
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|debug_register_view
c_func
(paren
id|ctc_dbf_setup
comma
op_amp
id|debug_hex_ascii_view
)paren
suffix:semicolon
id|debug_set_level
c_func
(paren
id|ctc_dbf_setup
comma
id|CTC_DBF_SETUP_LEVEL
)paren
suffix:semicolon
id|debug_register_view
c_func
(paren
id|ctc_dbf_data
comma
op_amp
id|debug_hex_ascii_view
)paren
suffix:semicolon
id|debug_set_level
c_func
(paren
id|ctc_dbf_data
comma
id|CTC_DBF_DATA_LEVEL
)paren
suffix:semicolon
id|debug_register_view
c_func
(paren
id|ctc_dbf_trace
comma
op_amp
id|debug_hex_ascii_view
)paren
suffix:semicolon
id|debug_set_level
c_func
(paren
id|ctc_dbf_trace
comma
id|CTC_DBF_TRACE_LEVEL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
