multiline_comment|/*&n; * Various register offset definitions for debuggers, core file&n; * examiners and whatnot.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1999 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_REG_H
DECL|macro|__ASM_MIPS_REG_H
mdefine_line|#define __ASM_MIPS_REG_H
multiline_comment|/*&n; * This defines/structures correspond to the register layout on stack -&n; * if the order here is changed, it needs to be updated in&n; * include/asm-mips/stackframe.h&n; */
DECL|macro|EF_REG0
mdefine_line|#define EF_REG0&t;&t;&t;6
DECL|macro|EF_REG1
mdefine_line|#define EF_REG1&t;&t;&t;7
DECL|macro|EF_REG2
mdefine_line|#define EF_REG2&t;&t;&t;8
DECL|macro|EF_REG3
mdefine_line|#define EF_REG3&t;&t;&t;9
DECL|macro|EF_REG4
mdefine_line|#define EF_REG4&t;&t;&t;10
DECL|macro|EF_REG5
mdefine_line|#define EF_REG5&t;&t;&t;11
DECL|macro|EF_REG6
mdefine_line|#define EF_REG6&t;&t;&t;12
DECL|macro|EF_REG7
mdefine_line|#define EF_REG7&t;&t;&t;13
DECL|macro|EF_REG8
mdefine_line|#define EF_REG8&t;&t;&t;14
DECL|macro|EF_REG9
mdefine_line|#define EF_REG9&t;&t;&t;15
DECL|macro|EF_REG10
mdefine_line|#define EF_REG10&t;&t;16
DECL|macro|EF_REG11
mdefine_line|#define EF_REG11&t;&t;17
DECL|macro|EF_REG12
mdefine_line|#define EF_REG12&t;&t;18
DECL|macro|EF_REG13
mdefine_line|#define EF_REG13&t;&t;19
DECL|macro|EF_REG14
mdefine_line|#define EF_REG14&t;&t;20
DECL|macro|EF_REG15
mdefine_line|#define EF_REG15&t;&t;21
DECL|macro|EF_REG16
mdefine_line|#define EF_REG16&t;&t;22
DECL|macro|EF_REG17
mdefine_line|#define EF_REG17&t;&t;23
DECL|macro|EF_REG18
mdefine_line|#define EF_REG18&t;&t;24
DECL|macro|EF_REG19
mdefine_line|#define EF_REG19&t;&t;25
DECL|macro|EF_REG20
mdefine_line|#define EF_REG20&t;&t;26
DECL|macro|EF_REG21
mdefine_line|#define EF_REG21&t;&t;27
DECL|macro|EF_REG22
mdefine_line|#define EF_REG22&t;&t;28
DECL|macro|EF_REG23
mdefine_line|#define EF_REG23&t;&t;29
DECL|macro|EF_REG24
mdefine_line|#define EF_REG24&t;&t;30
DECL|macro|EF_REG25
mdefine_line|#define EF_REG25&t;&t;31
multiline_comment|/*&n; * k0/k1 unsaved&n; */
DECL|macro|EF_REG28
mdefine_line|#define EF_REG28&t;&t;34
DECL|macro|EF_REG29
mdefine_line|#define EF_REG29&t;&t;35
DECL|macro|EF_REG30
mdefine_line|#define EF_REG30&t;&t;36
DECL|macro|EF_REG31
mdefine_line|#define EF_REG31&t;&t;37
multiline_comment|/*&n; * Saved special registers&n; */
DECL|macro|EF_LO
mdefine_line|#define EF_LO&t;&t;&t;38
DECL|macro|EF_HI
mdefine_line|#define EF_HI&t;&t;&t;39
DECL|macro|EF_CP0_EPC
mdefine_line|#define EF_CP0_EPC&t;&t;40
DECL|macro|EF_CP0_BADVADDR
mdefine_line|#define EF_CP0_BADVADDR&t;&t;41
DECL|macro|EF_CP0_STATUS
mdefine_line|#define EF_CP0_STATUS&t;&t;42
DECL|macro|EF_CP0_CAUSE
mdefine_line|#define EF_CP0_CAUSE&t;&t;44
DECL|macro|EF_SIZE
mdefine_line|#define EF_SIZE&t;&t;&t;180&t;/* size in bytes */
macro_line|#endif /* __ASM_MIPS_REG_H */
eof
