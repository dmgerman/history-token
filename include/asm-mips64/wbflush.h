multiline_comment|/*&n; * Header file for using the wbflush routine&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1998 Harald Koerfgen&n; * Copyright (C) 2002 Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_MIPS64_WBFLUSH_H
DECL|macro|__ASM_MIPS64_WBFLUSH_H
mdefine_line|#define __ASM_MIPS64_WBFLUSH_H
DECL|macro|wbflush_setup
mdefine_line|#define wbflush_setup() do { } while (0)
DECL|macro|wbflush
mdefine_line|#define wbflush() fast_iob()
macro_line|#endif /* __ASM_MIPS64_WBFLUSH_H */
eof
