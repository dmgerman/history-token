multiline_comment|/*&n; * Header file for using the wbflush routine&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1998 Harald Koerfgen&n; *&n; * $Id: wbflush.h,v 1.2 1999/08/13 17:07:28 harald Exp $&n; */
macro_line|#ifndef __ASM_MIPS_WBFLUSH_H
DECL|macro|__ASM_MIPS_WBFLUSH_H
mdefine_line|#define __ASM_MIPS_WBFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_CPU_HAS_WB)
multiline_comment|/*&n; * R2000 or R3000&n; */
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
DECL|macro|wbflush
mdefine_line|#define wbflush() __wbflush()
macro_line|#else
multiline_comment|/*&n; * we don&squot;t need no stinkin&squot; wbflush&n; */
DECL|macro|wbflush
mdefine_line|#define wbflush()  do { } while(0)
macro_line|#endif
r_extern
r_void
id|wbflush_setup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_WBFLUSH_H */
eof
