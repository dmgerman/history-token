multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 2003 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_BREAK_H
DECL|macro|__ASM_BREAK_H
mdefine_line|#define __ASM_BREAK_H
multiline_comment|/*&n; * The following break codes are or were in use for specific purposes in&n; * other MIPS operating systems.  Linux/MIPS doesn&squot;t use all of them.  The&n; * unused ones are here as placeholders; we might encounter them in&n; * non-Linux/MIPS object files or make use of them in the future.&n; */
DECL|macro|BRK_USERBP
mdefine_line|#define BRK_USERBP&t;0&t;/* User bp (used by debuggers) */
DECL|macro|BRK_KERNELBP
mdefine_line|#define BRK_KERNELBP&t;1&t;/* Break in the kernel */
DECL|macro|BRK_ABORT
mdefine_line|#define BRK_ABORT&t;2&t;/* Sometimes used by abort(3) to SIGIOT */
DECL|macro|BRK_BD_TAKEN
mdefine_line|#define BRK_BD_TAKEN&t;3&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_BD_NOTTAKEN
mdefine_line|#define BRK_BD_NOTTAKEN&t;4&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_SSTEPBP
mdefine_line|#define BRK_SSTEPBP&t;5&t;/* User bp (used by debuggers) */
DECL|macro|BRK_OVERFLOW
mdefine_line|#define BRK_OVERFLOW&t;6&t;/* Overflow check */
DECL|macro|BRK_DIVZERO
mdefine_line|#define BRK_DIVZERO&t;7&t;/* Divide by zero check */
DECL|macro|BRK_RANGE
mdefine_line|#define BRK_RANGE&t;8&t;/* Range error check */
DECL|macro|BRK_STACKOVERFLOW
mdefine_line|#define BRK_STACKOVERFLOW 9&t;/* For Ada stackchecking */
DECL|macro|BRK_NORLD
mdefine_line|#define BRK_NORLD&t;10&t;/* No rld found - not used by Linux/MIPS */
DECL|macro|_BRK_THREADBP
mdefine_line|#define _BRK_THREADBP&t;11&t;/* For threads, user bp (used by debuggers) */
DECL|macro|BRK_BUG
mdefine_line|#define BRK_BUG&t;&t;512&t;/* Used by BUG() */
DECL|macro|BRK_MULOVF
mdefine_line|#define BRK_MULOVF&t;1023&t;/* Multiply overflow */
macro_line|#endif /* __ASM_BREAK_H */
eof
