macro_line|#ifndef __ASM_SH64_SHMPARAM_H
DECL|macro|__ASM_SH64_SHMPARAM_H
mdefine_line|#define __ASM_SH64_SHMPARAM_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/shmparam.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/* attach addr a multiple of this */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA&t;(cpu_data-&gt;dcache.sets * L1_CACHE_BYTES)
macro_line|#endif /* __ASM_SH64_SHMPARAM_H */
eof
