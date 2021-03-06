multiline_comment|/*&n; * Copyright (C) 2004 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * Based on alpha version.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef OP_IMPL_H
DECL|macro|OP_IMPL_H
mdefine_line|#define OP_IMPL_H 1
DECL|macro|OP_MAX_COUNTER
mdefine_line|#define OP_MAX_COUNTER 8
multiline_comment|/* Per-counter configuration as set via oprofilefs.  */
DECL|struct|op_counter_config
r_struct
id|op_counter_config
(brace
DECL|member|enabled
r_int
r_int
id|enabled
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|kernel
r_int
r_int
id|kernel
suffix:semicolon
DECL|member|user
r_int
r_int
id|user
suffix:semicolon
DECL|member|unit_mask
r_int
r_int
id|unit_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* System-wide configuration as set via oprofilefs.  */
DECL|struct|op_system_config
r_struct
id|op_system_config
(brace
DECL|member|enable_kernel
r_int
r_int
id|enable_kernel
suffix:semicolon
DECL|member|enable_user
r_int
r_int
id|enable_user
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Per-arch configuration */
DECL|struct|op_ppc32_model
r_struct
id|op_ppc32_model
(brace
DECL|member|reg_setup
r_void
(paren
op_star
id|reg_setup
)paren
(paren
r_struct
id|op_counter_config
op_star
comma
r_struct
id|op_system_config
op_star
comma
r_int
id|num_counters
)paren
suffix:semicolon
DECL|member|start
r_void
(paren
op_star
id|start
)paren
(paren
r_struct
id|op_counter_config
op_star
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|handle_interrupt
r_void
(paren
op_star
id|handle_interrupt
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|op_counter_config
op_star
)paren
suffix:semicolon
DECL|member|num_counters
r_int
id|num_counters
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* OP_IMPL_H */
eof
