multiline_comment|/*&n; *  Copyright (C) 2003 Aurelien Alleaume &lt;slts@free.fr&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#if !defined(_OID_MGT_H)
DECL|macro|_OID_MGT_H
mdefine_line|#define _OID_MGT_H
macro_line|#include &quot;isl_oid.h&quot;
macro_line|#include &quot;islpci_dev.h&quot;
r_extern
r_struct
id|oid_t
id|isl_oid
(braket
)braket
suffix:semicolon
r_int
id|mgt_init
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_void
id|mgt_clean
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_extern
r_const
r_int
id|frequency_list_bg
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|frequency_list_a
(braket
)braket
suffix:semicolon
r_void
id|mgt_le_to_cpu
c_func
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|mgt_set_request
c_func
(paren
id|islpci_private
op_star
comma
r_enum
id|oid_num_t
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|mgt_get_request
c_func
(paren
id|islpci_private
op_star
comma
r_enum
id|oid_num_t
comma
r_int
comma
r_void
op_star
comma
r_union
id|oid_res_t
op_star
)paren
suffix:semicolon
r_int
id|mgt_commit_list
c_func
(paren
id|islpci_private
op_star
comma
r_enum
id|oid_num_t
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|mgt_set
c_func
(paren
id|islpci_private
op_star
comma
r_enum
id|oid_num_t
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|mgt_get
c_func
(paren
id|islpci_private
op_star
comma
r_enum
id|oid_num_t
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|mgt_commit
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_int
id|mgt_mlme_answer
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_enum
id|oid_num_t
id|mgt_oidtonum
c_func
(paren
id|u32
id|oid
)paren
suffix:semicolon
r_int
id|mgt_response_to_str
c_func
(paren
r_enum
id|oid_num_t
comma
r_union
id|oid_res_t
op_star
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* !defined(_OID_MGT_H) */
multiline_comment|/* EOF */
eof
