multiline_comment|/*&n; * include/asm-sh/saturn/io.h&n; *&n; * I/O functions for use on the Sega Saturn.&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#ifndef __ASM_SH_SATURN_IO_H
DECL|macro|__ASM_SH_SATURN_IO_H
mdefine_line|#define __ASM_SH_SATURN_IO_H
multiline_comment|/* arch/sh/boards/saturn/io.c */
r_extern
r_int
r_int
id|saturn_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
op_star
id|saturn_ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|saturn_iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_SATURN_IO_H */
eof
