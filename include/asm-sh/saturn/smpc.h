multiline_comment|/*&n; * include/asm-sh/saturn/smpc.h&n; *&n; * System Manager / Peripheral Control definitions.&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#ifndef __ASM_SH_SATURN_SMPC_H
DECL|macro|__ASM_SH_SATURN_SMPC_H
mdefine_line|#define __ASM_SH_SATURN_SMPC_H
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|SMPC_COMMAND
mdefine_line|#define SMPC_COMMAND&t;0x2010001f&t;/* SMPC command register */
DECL|macro|SMPC_RESULT
mdefine_line|#define SMPC_RESULT&t;0x2010005f&t;/* SMPC result register */
DECL|macro|SMPC_STATUS
mdefine_line|#define SMPC_STATUS&t;0x20100063&t;/* SMPC status register */
DECL|macro|SMPC_CMD_MSHON
mdefine_line|#define SMPC_CMD_MSHON&t;0x0001&t;&t;/* Master SH On */
DECL|macro|SMPC_CMD_SSHON
mdefine_line|#define SMPC_CMD_SSHON&t;0x0002&t;&t;/* Slave SH On */
DECL|macro|SMPC_CMD_SSHOFF
mdefine_line|#define SMPC_CMD_SSHOFF&t;0x0003&t;&t;/* Slave SH Off */
DECL|macro|SMPC_CMD_SNDON
mdefine_line|#define SMPC_CMD_SNDON&t;0x0004&t;&t;/* Sound On */
DECL|macro|SMPC_CMD_SNDOFF
mdefine_line|#define SMPC_CMD_SNDOFF&t;0x0005&t;&t;/* Sound Off */
DECL|macro|SMPC_CMD_CDON
mdefine_line|#define SMPC_CMD_CDON&t;0x0006&t;&t;/* CD On */
DECL|macro|SMPC_CMD_CDOFF
mdefine_line|#define SMPC_CMD_CDOFF&t;0x0007&t;&t;/* CD Off */
DECL|function|smpc_barrier
r_static
r_inline
r_void
id|smpc_barrier
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
(paren
id|ctrl_inb
c_func
(paren
id|SMPC_STATUS
)paren
op_amp
l_int|0x0001
)paren
op_eq
l_int|0x0001
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SH_SATURN_SMPC_H */
eof
