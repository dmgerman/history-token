multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_CDL_H
DECL|macro|_ASM_IA64_SN_CDL_H
mdefine_line|#define _ASM_IA64_SN_CDL_H
macro_line|#include &lt;asm/sn/sgi.h&gt;
DECL|struct|cdl
r_struct
id|cdl
(brace
DECL|member|part_num
r_int
id|part_num
suffix:semicolon
multiline_comment|/* Part part number */
DECL|member|mfg_num
r_int
id|mfg_num
suffix:semicolon
multiline_comment|/* Part MFG number */
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
multiline_comment|/* Attach routine */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;cdl: connection/driver list&n; *&n; *&t;support code for bus infrastructure for busses&n; *&t;that have self-identifying devices; initially&n; *&t;constructed for xtalk, pciio and gioio modules.&n; */
DECL|typedef|cdl_p
r_typedef
r_struct
id|cdl
op_star
id|cdl_p
suffix:semicolon
multiline_comment|/*&n; *&t;cdl_add_connpt: add a connection point&n; *&n; *&t;Calls the attach routines of all the drivers on&n; *&t;the list that match this connection point, in&n; *&t;the order that they were added to the list.&n; */
r_extern
r_int
id|cdl_add_connpt
c_func
(paren
r_int
id|key1
comma
r_int
id|key2
comma
id|vertex_hdl_t
id|conn
comma
r_int
id|drv_flags
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_CDL_H */
eof
