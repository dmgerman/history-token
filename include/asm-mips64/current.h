multiline_comment|/* $Id: current.h,v 1.3 1999/12/04 03:59:12 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999 Ralf Baechle&n; */
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
macro_line|#endif /* _ASM_CURRENT_H */
eof
