macro_line|#ifndef _ASM_IST_H
DECL|macro|_ASM_IST_H
mdefine_line|#define _ASM_IST_H
multiline_comment|/*&n; * Include file for the interface to IST BIOS&n; * Copyright 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
macro_line|#ifdef __KERNEL__
DECL|struct|ist_info
r_struct
id|ist_info
(brace
DECL|member|signature
r_int
r_int
id|signature
suffix:semicolon
DECL|member|command
r_int
r_int
id|command
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|perf_level
r_int
r_int
id|perf_level
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ist_info
id|ist_info
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _ASM_IST_H */
eof
