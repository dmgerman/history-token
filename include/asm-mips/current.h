multiline_comment|/* $Id: current.h,v 1.5 1999/07/26 19:42:43 harald Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CURRENT_H
DECL|macro|_ASM_CURRENT_H
mdefine_line|#define _ASM_CURRENT_H
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/* MIPS rules... */
r_register
r_struct
id|task_struct
op_star
id|current
id|asm
c_func
(paren
l_string|&quot;$28&quot;
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
macro_line|#ifdef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Special variant for use by exception handlers when the stack pointer&n; * is not loaded.&n; */
DECL|macro|_GET_CURRENT
mdefine_line|#define _GET_CURRENT(reg)&t;&t;&t;&bslash;&n;&t;lui&t;reg, %hi(kernelsp);&t;&t;&bslash;&n;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;.set&t;reorder;&t;&t;&t;&bslash;&n;&t;lw&t;reg, %lo(kernelsp)(reg);&t;&bslash;&n;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;&t;ori&t;reg, 8191;&t;&t;&t;&bslash;&n;&t;xori&t;reg, 8191
macro_line|#endif
macro_line|#endif /* _ASM_CURRENT_H */
eof
