multiline_comment|/*&n; *  linux/include/asm-arm/hardware/icst307.h&n; *&n; *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Support functions for calculating clocks/divisors for the ICS307&n; *  clock generators.  See http://www.icst.com/ for more information&n; *  on these devices.&n; *&n; *  This file is similar to the icst525.h file&n; */
macro_line|#ifndef ASMARM_HARDWARE_ICST307_H
DECL|macro|ASMARM_HARDWARE_ICST307_H
mdefine_line|#define ASMARM_HARDWARE_ICST307_H
DECL|struct|icst307_params
r_struct
id|icst307_params
(brace
DECL|member|ref
r_int
r_int
id|ref
suffix:semicolon
DECL|member|vco_max
r_int
r_int
id|vco_max
suffix:semicolon
multiline_comment|/* inclusive */
DECL|member|vd_min
r_int
r_int
id|vd_min
suffix:semicolon
multiline_comment|/* inclusive */
DECL|member|vd_max
r_int
r_int
id|vd_max
suffix:semicolon
multiline_comment|/* inclusive */
DECL|member|rd_min
r_int
r_char
id|rd_min
suffix:semicolon
multiline_comment|/* inclusive */
DECL|member|rd_max
r_int
r_char
id|rd_max
suffix:semicolon
multiline_comment|/* inclusive */
)brace
suffix:semicolon
DECL|struct|icst307_vco
r_struct
id|icst307_vco
(brace
DECL|member|v
r_int
r_int
id|v
suffix:semicolon
DECL|member|r
r_int
r_char
id|r
suffix:semicolon
DECL|member|s
r_int
r_char
id|s
suffix:semicolon
)brace
suffix:semicolon
r_int
r_int
id|icst307_khz
c_func
(paren
r_const
r_struct
id|icst307_params
op_star
id|p
comma
r_struct
id|icst307_vco
id|vco
)paren
suffix:semicolon
r_struct
id|icst307_vco
id|icst307_khz_to_vco
c_func
(paren
r_const
r_struct
id|icst307_params
op_star
id|p
comma
r_int
r_int
id|freq
)paren
suffix:semicolon
r_struct
id|icst307_vco
id|icst307_ps_to_vco
c_func
(paren
r_const
r_struct
id|icst307_params
op_star
id|p
comma
r_int
r_int
id|period
)paren
suffix:semicolon
macro_line|#endif
eof
