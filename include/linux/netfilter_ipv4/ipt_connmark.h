macro_line|#ifndef _IPT_CONNMARK_H
DECL|macro|_IPT_CONNMARK_H
mdefine_line|#define _IPT_CONNMARK_H
multiline_comment|/* Copyright (C) 2002,2004 MARA Systems AB &lt;http://www.marasystems.com&gt;&n; * by Henrik Nordstrom &lt;hno@marasystems.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
DECL|struct|ipt_connmark_info
r_struct
id|ipt_connmark_info
(brace
DECL|member|mark
DECL|member|mask
r_int
r_int
id|mark
comma
id|mask
suffix:semicolon
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_CONNMARK_H*/
eof
