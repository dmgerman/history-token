macro_line|#ifndef _IPT_CONNMARK_H_target
DECL|macro|_IPT_CONNMARK_H_target
mdefine_line|#define _IPT_CONNMARK_H_target
multiline_comment|/* Copyright (C) 2002,2004 MARA Systems AB &lt;http://www.marasystems.com&gt;&n; * by Henrik Nordstrom &lt;hno@marasystems.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
r_enum
(brace
DECL|enumerator|IPT_CONNMARK_SET
id|IPT_CONNMARK_SET
op_assign
l_int|0
comma
DECL|enumerator|IPT_CONNMARK_SAVE
id|IPT_CONNMARK_SAVE
comma
DECL|enumerator|IPT_CONNMARK_RESTORE
id|IPT_CONNMARK_RESTORE
)brace
suffix:semicolon
DECL|struct|ipt_connmark_target_info
r_struct
id|ipt_connmark_target_info
(brace
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|mode
id|u_int8_t
id|mode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_CONNMARK_H_target*/
eof
