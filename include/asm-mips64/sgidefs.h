multiline_comment|/* $Id: sgidefs.h,v 1.1 1999/08/18 23:37:52 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; *&n; * Definitions commonly used in SGI style code.&n; */
macro_line|#ifndef _ASM_SGIDEFS_H
DECL|macro|_ASM_SGIDEFS_H
mdefine_line|#define _ASM_SGIDEFS_H
multiline_comment|/*&n; * Definitions for the ISA level&n; */
DECL|macro|_MIPS_ISA_MIPS1
mdefine_line|#define _MIPS_ISA_MIPS1 1
DECL|macro|_MIPS_ISA_MIPS2
mdefine_line|#define _MIPS_ISA_MIPS2 2
DECL|macro|_MIPS_ISA_MIPS3
mdefine_line|#define _MIPS_ISA_MIPS3 3
DECL|macro|_MIPS_ISA_MIPS4
mdefine_line|#define _MIPS_ISA_MIPS4 4
DECL|macro|_MIPS_ISA_MIPS5
mdefine_line|#define _MIPS_ISA_MIPS5 5
multiline_comment|/*&n; * Subprogram calling convention&n; */
DECL|macro|_MIPS_SIM_ABI32
mdefine_line|#define _MIPS_SIM_ABI32&t;&t;1
DECL|macro|_MIPS_SIM_NABI32
mdefine_line|#define _MIPS_SIM_NABI32&t;2
DECL|macro|_MIPS_SIM_ABI64
mdefine_line|#define _MIPS_SIM_ABI64&t;&t;3
macro_line|#endif /* _ASM_SGIDEFS_H */
eof
