macro_line|#ifndef _PPC64_SIGINFO_H
DECL|macro|_PPC64_SIGINFO_H
mdefine_line|#define _PPC64_SIGINFO_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|__ARCH_SI_PREAMBLE_SIZE
mdefine_line|#define __ARCH_SI_PREAMBLE_SIZE&t;(4 * sizeof(int))
DECL|macro|SI_PAD_SIZE32
mdefine_line|#define SI_PAD_SIZE32&t;&t;((SI_MAX_SIZE/sizeof(int)) - 3)
macro_line|#include &lt;asm-generic/siginfo.h&gt;
macro_line|#endif /* _PPC64_SIGINFO_H */
eof
