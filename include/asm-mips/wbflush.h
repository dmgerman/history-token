multiline_comment|/*&n; * Header file for using the wbflush routine&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1998 Harald Koerfgen&n; * Copyright (C) 2002 Maciej W. Rozycki&n; */
macro_line|#ifndef _ASM_WBFLUSH_H
DECL|macro|_ASM_WBFLUSH_H
mdefine_line|#define _ASM_WBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_CPU_HAS_WB
r_extern
r_void
(paren
op_star
id|__wbflush
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wbflush_setup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|wbflush
mdefine_line|#define wbflush()&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;__sync();&t;&t;&bslash;&n;&t;&t;__wbflush();&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else /* !CONFIG_CPU_HAS_WB */
DECL|macro|wbflush_setup
mdefine_line|#define wbflush_setup() do { } while (0)
DECL|macro|wbflush
mdefine_line|#define wbflush() fast_iob()
macro_line|#endif /* !CONFIG_CPU_HAS_WB */
macro_line|#endif /* _ASM_WBFLUSH_H */
eof
