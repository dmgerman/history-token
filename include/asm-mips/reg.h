multiline_comment|/*&n; * Various register offset definitions for debuggers, core file&n; * examiners and whatnot.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1999 Ralf Baechle&n; * Copyright (C) 1995, 1999 Silicon Graphics&n; */
macro_line|#ifndef __ASM_MIPS_REG_H
DECL|macro|__ASM_MIPS_REG_H
mdefine_line|#define __ASM_MIPS_REG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_MIPS32) || defined(WANT_COMPAT_REG_H)
DECL|macro|EF_R0
mdefine_line|#define EF_R0&t;&t;&t;6
DECL|macro|EF_R1
mdefine_line|#define EF_R1&t;&t;&t;7
DECL|macro|EF_R2
mdefine_line|#define EF_R2&t;&t;&t;8
DECL|macro|EF_R3
mdefine_line|#define EF_R3&t;&t;&t;9
DECL|macro|EF_R4
mdefine_line|#define EF_R4&t;&t;&t;10
DECL|macro|EF_R5
mdefine_line|#define EF_R5&t;&t;&t;11
DECL|macro|EF_R6
mdefine_line|#define EF_R6&t;&t;&t;12
DECL|macro|EF_R7
mdefine_line|#define EF_R7&t;&t;&t;13
DECL|macro|EF_R8
mdefine_line|#define EF_R8&t;&t;&t;14
DECL|macro|EF_R9
mdefine_line|#define EF_R9&t;&t;&t;15
DECL|macro|EF_R10
mdefine_line|#define EF_R10&t;&t;&t;16
DECL|macro|EF_R11
mdefine_line|#define EF_R11&t;&t;&t;17
DECL|macro|EF_R12
mdefine_line|#define EF_R12&t;&t;&t;18
DECL|macro|EF_R13
mdefine_line|#define EF_R13&t;&t;&t;19
DECL|macro|EF_R14
mdefine_line|#define EF_R14&t;&t;&t;20
DECL|macro|EF_R15
mdefine_line|#define EF_R15&t;&t;&t;21
DECL|macro|EF_R16
mdefine_line|#define EF_R16&t;&t;&t;22
DECL|macro|EF_R17
mdefine_line|#define EF_R17&t;&t;&t;23
DECL|macro|EF_R18
mdefine_line|#define EF_R18&t;&t;&t;24
DECL|macro|EF_R19
mdefine_line|#define EF_R19&t;&t;&t;25
DECL|macro|EF_R20
mdefine_line|#define EF_R20&t;&t;&t;26
DECL|macro|EF_R21
mdefine_line|#define EF_R21&t;&t;&t;27
DECL|macro|EF_R22
mdefine_line|#define EF_R22&t;&t;&t;28
DECL|macro|EF_R23
mdefine_line|#define EF_R23&t;&t;&t;29
DECL|macro|EF_R24
mdefine_line|#define EF_R24&t;&t;&t;30
DECL|macro|EF_R25
mdefine_line|#define EF_R25&t;&t;&t;31
multiline_comment|/*&n; * k0/k1 unsaved&n; */
DECL|macro|EF_R26
mdefine_line|#define EF_R26&t;&t;&t;32
DECL|macro|EF_R27
mdefine_line|#define EF_R27&t;&t;&t;33
DECL|macro|EF_R28
mdefine_line|#define EF_R28&t;&t;&t;34
DECL|macro|EF_R29
mdefine_line|#define EF_R29&t;&t;&t;35
DECL|macro|EF_R30
mdefine_line|#define EF_R30&t;&t;&t;36
DECL|macro|EF_R31
mdefine_line|#define EF_R31&t;&t;&t;37
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
mdefine_line|#define EF_CP0_CAUSE&t;&t;43
DECL|macro|EF_UNUSED0
mdefine_line|#define EF_UNUSED0&t;&t;44
DECL|macro|EF_SIZE
mdefine_line|#define EF_SIZE&t;&t;&t;180
macro_line|#endif
macro_line|#if CONFIG_MIPS64
DECL|macro|EF_R0
mdefine_line|#define EF_R0&t;&t;&t; 0
DECL|macro|EF_R1
mdefine_line|#define EF_R1&t;&t;&t; 1
DECL|macro|EF_R2
mdefine_line|#define EF_R2&t;&t;&t; 2
DECL|macro|EF_R3
mdefine_line|#define EF_R3&t;&t;&t; 3
DECL|macro|EF_R4
mdefine_line|#define EF_R4&t;&t;&t; 4
DECL|macro|EF_R5
mdefine_line|#define EF_R5&t;&t;&t; 5
DECL|macro|EF_R6
mdefine_line|#define EF_R6&t;&t;&t; 6
DECL|macro|EF_R7
mdefine_line|#define EF_R7&t;&t;&t; 7
DECL|macro|EF_R8
mdefine_line|#define EF_R8&t;&t;&t; 8
DECL|macro|EF_R9
mdefine_line|#define EF_R9&t;&t;&t; 9
DECL|macro|EF_R10
mdefine_line|#define EF_R10&t;&t;&t;10
DECL|macro|EF_R11
mdefine_line|#define EF_R11&t;&t;&t;11
DECL|macro|EF_R12
mdefine_line|#define EF_R12&t;&t;&t;12
DECL|macro|EF_R13
mdefine_line|#define EF_R13&t;&t;&t;13
DECL|macro|EF_R14
mdefine_line|#define EF_R14&t;&t;&t;14
DECL|macro|EF_R15
mdefine_line|#define EF_R15&t;&t;&t;15
DECL|macro|EF_R16
mdefine_line|#define EF_R16&t;&t;&t;16
DECL|macro|EF_R17
mdefine_line|#define EF_R17&t;&t;&t;17
DECL|macro|EF_R18
mdefine_line|#define EF_R18&t;&t;&t;18
DECL|macro|EF_R19
mdefine_line|#define EF_R19&t;&t;&t;19
DECL|macro|EF_R20
mdefine_line|#define EF_R20&t;&t;&t;20
DECL|macro|EF_R21
mdefine_line|#define EF_R21&t;&t;&t;21
DECL|macro|EF_R22
mdefine_line|#define EF_R22&t;&t;&t;22
DECL|macro|EF_R23
mdefine_line|#define EF_R23&t;&t;&t;23
DECL|macro|EF_R24
mdefine_line|#define EF_R24&t;&t;&t;24
DECL|macro|EF_R25
mdefine_line|#define EF_R25&t;&t;&t;25
multiline_comment|/*&n; * k0/k1 unsaved&n; */
DECL|macro|EF_R26
mdefine_line|#define EF_R26&t;&t;&t;26
DECL|macro|EF_R27
mdefine_line|#define EF_R27&t;&t;&t;27
DECL|macro|EF_R28
mdefine_line|#define EF_R28&t;&t;&t;28
DECL|macro|EF_R29
mdefine_line|#define EF_R29&t;&t;&t;29
DECL|macro|EF_R30
mdefine_line|#define EF_R30&t;&t;&t;30
DECL|macro|EF_R31
mdefine_line|#define EF_R31&t;&t;&t;31
multiline_comment|/*&n; * Saved special registers&n; */
DECL|macro|EF_LO
mdefine_line|#define EF_LO&t;&t;&t;32
DECL|macro|EF_HI
mdefine_line|#define EF_HI&t;&t;&t;33
DECL|macro|EF_CP0_EPC
mdefine_line|#define EF_CP0_EPC&t;&t;34
DECL|macro|EF_CP0_BADVADDR
mdefine_line|#define EF_CP0_BADVADDR&t;&t;35
DECL|macro|EF_CP0_STATUS
mdefine_line|#define EF_CP0_STATUS&t;&t;36
DECL|macro|EF_CP0_CAUSE
mdefine_line|#define EF_CP0_CAUSE&t;&t;37
DECL|macro|EF_SIZE
mdefine_line|#define EF_SIZE&t;&t;&t;304&t;/* size in bytes */
macro_line|#endif /* CONFIG_MIPS64 */
macro_line|#endif /* __ASM_MIPS_REG_H */
eof
