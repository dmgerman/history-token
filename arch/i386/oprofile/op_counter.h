multiline_comment|/**&n; * @file op_counter.h&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; */
macro_line|#ifndef OP_COUNTER_H
DECL|macro|OP_COUNTER_H
mdefine_line|#define OP_COUNTER_H
DECL|macro|OP_MAX_COUNTER
mdefine_line|#define OP_MAX_COUNTER 8
multiline_comment|/* Per-perfctr configuration as set via&n; * oprofilefs.&n; */
DECL|struct|op_counter_config
r_struct
id|op_counter_config
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
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
r_extern
r_struct
id|op_counter_config
id|counter_config
(braket
)braket
suffix:semicolon
macro_line|#endif /* OP_COUNTER_H */
eof
