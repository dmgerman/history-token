multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_HUBSPC_H
DECL|macro|_ASM_IA64_SN_SN1_HUBSPC_H
mdefine_line|#define _ASM_IA64_SN_SN1_HUBSPC_H
r_typedef
r_enum
(brace
DECL|enumerator|HUBSPC_REFCOUNTERS
id|HUBSPC_REFCOUNTERS
comma
DECL|enumerator|HUBSPC_PROM
id|HUBSPC_PROM
DECL|typedef|hubspc_subdevice_t
)brace
id|hubspc_subdevice_t
suffix:semicolon
multiline_comment|/*&n; * Reference Counters&n; */
r_extern
r_int
id|refcounters_attach
c_func
(paren
id|devfs_handle_t
id|hub
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_SN1_HUBSPC_H */        
eof
