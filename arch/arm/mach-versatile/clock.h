multiline_comment|/*&n; *  linux/arch/arm/mach-versatile/clock.h&n; *&n; *  Copyright (C) 2004 ARM Limited.&n; *  Written by Deep Blue Solutions Limited.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
r_struct
id|module
suffix:semicolon
r_struct
id|icst307_params
suffix:semicolon
DECL|struct|clk
r_struct
id|clk
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|params
r_const
r_struct
id|icst307_params
op_star
id|params
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|setvco
r_void
(paren
op_star
id|setvco
)paren
(paren
r_struct
id|clk
op_star
comma
r_struct
id|icst307_vco
id|vco
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|clk_register
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
r_void
id|clk_unregister
c_func
(paren
r_struct
id|clk
op_star
id|clk
)paren
suffix:semicolon
eof
