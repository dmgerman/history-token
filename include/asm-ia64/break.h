macro_line|#ifndef _ASM_IA64_BREAK_H
DECL|macro|_ASM_IA64_BREAK_H
mdefine_line|#define _ASM_IA64_BREAK_H
multiline_comment|/*&n; * IA-64 Linux break numbers.&n; *&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * OS-specific debug break numbers:&n; */
DECL|macro|__IA64_BREAK_KDB
mdefine_line|#define __IA64_BREAK_KDB&t;&t;0x80100
multiline_comment|/*&n; * OS-specific break numbers:&n; */
DECL|macro|__IA64_BREAK_SYSCALL
mdefine_line|#define __IA64_BREAK_SYSCALL&t;&t;0x100000
macro_line|#endif /* _ASM_IA64_BREAK_H */
eof
