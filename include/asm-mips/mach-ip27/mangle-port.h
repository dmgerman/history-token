multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003, 2004 Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_IP27_MANGLE_PORT_H
DECL|macro|__ASM_MACH_IP27_MANGLE_PORT_H
mdefine_line|#define __ASM_MACH_IP27_MANGLE_PORT_H
DECL|macro|__swizzle_addr_b
mdefine_line|#define __swizzle_addr_b(port)&t;(port)
DECL|macro|__swizzle_addr_w
mdefine_line|#define __swizzle_addr_w(port)&t;((port) ^ 2)
DECL|macro|__swizzle_addr_l
mdefine_line|#define __swizzle_addr_l(port)&t;(port)
DECL|macro|__swizzle_addr_q
mdefine_line|#define __swizzle_addr_q(port)&t;(port)
macro_line|#endif /* __ASM_MACH_IP27_MANGLE_PORT_H */
eof
