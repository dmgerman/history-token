multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999, 2001 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#ifndef __ASM_SGIDEFS_H
DECL|macro|__ASM_SGIDEFS_H
mdefine_line|#define __ASM_SGIDEFS_H
multiline_comment|/*&n; * Using a Linux compiler for building Linux seems logic but not to&n; * everybody.&n; */
macro_line|#ifndef __linux__
macro_line|#error Use a Linux compiler or give up.
macro_line|#endif
multiline_comment|/*&n; * Definitions for the ISA levels&n; *&n; * With the introduction of MIPS32 / MIPS64 instruction sets definitions&n; * MIPS ISAs are no longer subsets of each other.  Therefore comparisons&n; * on these symbols except with == may result in unexpected results and&n; * are forbidden!&n; */
DECL|macro|_MIPS_ISA_MIPS1
mdefine_line|#define _MIPS_ISA_MIPS1&t;&t;1
DECL|macro|_MIPS_ISA_MIPS2
mdefine_line|#define _MIPS_ISA_MIPS2&t;&t;2
DECL|macro|_MIPS_ISA_MIPS3
mdefine_line|#define _MIPS_ISA_MIPS3&t;&t;3
DECL|macro|_MIPS_ISA_MIPS4
mdefine_line|#define _MIPS_ISA_MIPS4&t;&t;4
DECL|macro|_MIPS_ISA_MIPS5
mdefine_line|#define _MIPS_ISA_MIPS5&t;&t;5
DECL|macro|_MIPS_ISA_MIPS32
mdefine_line|#define _MIPS_ISA_MIPS32&t;6
DECL|macro|_MIPS_ISA_MIPS64
mdefine_line|#define _MIPS_ISA_MIPS64&t;7
multiline_comment|/*&n; * Subprogram calling convention&n; */
DECL|macro|_MIPS_SIM_ABI32
mdefine_line|#define _MIPS_SIM_ABI32&t;&t;1
DECL|macro|_MIPS_SIM_NABI32
mdefine_line|#define _MIPS_SIM_NABI32&t;2
DECL|macro|_MIPS_SIM_ABI64
mdefine_line|#define _MIPS_SIM_ABI64&t;&t;3
macro_line|#endif /* __ASM_SGIDEFS_H */
eof
