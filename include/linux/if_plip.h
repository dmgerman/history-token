multiline_comment|/*&n; *&t;NET3&t;PLIP tuning facilities for the new Niibe PLIP.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#ifndef _LINUX_IF_PLIP_H
DECL|macro|_LINUX_IF_PLIP_H
mdefine_line|#define _LINUX_IF_PLIP_H
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|SIOCDEVPLIP
mdefine_line|#define&t;SIOCDEVPLIP&t;SIOCDEVPRIVATE
DECL|struct|plipconf
r_struct
id|plipconf
(brace
DECL|member|pcmd
r_int
r_int
id|pcmd
suffix:semicolon
DECL|member|nibble
r_int
r_int
id|nibble
suffix:semicolon
DECL|member|trigger
r_int
r_int
id|trigger
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PLIP_GET_TIMEOUT
mdefine_line|#define PLIP_GET_TIMEOUT&t;0x1
DECL|macro|PLIP_SET_TIMEOUT
mdefine_line|#define PLIP_SET_TIMEOUT&t;0x2
macro_line|#endif
eof
