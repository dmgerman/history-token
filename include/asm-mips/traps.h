multiline_comment|/*&n; *&t;include/asm-mips/traps.h&n; *&n; *&t;Trap handling definitions.&n; *&n; *&t;Copyright (C) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_TRAPS_H
DECL|macro|__ASM_MIPS_TRAPS_H
mdefine_line|#define __ASM_MIPS_TRAPS_H
multiline_comment|/*&n; * Possible status responses for a board_be_handler backend.&n; */
DECL|macro|MIPS_BE_DISCARD
mdefine_line|#define MIPS_BE_DISCARD&t;0&t;&t;/* return with no action */
DECL|macro|MIPS_BE_FIXUP
mdefine_line|#define MIPS_BE_FIXUP&t;1&t;&t;/* return to the fixup code */
DECL|macro|MIPS_BE_FATAL
mdefine_line|#define MIPS_BE_FATAL&t;2&t;&t;/* treat as an unrecoverable error */
r_extern
r_void
(paren
op_star
id|board_be_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|board_be_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_TRAPS_H */
eof
