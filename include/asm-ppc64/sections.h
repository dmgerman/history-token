macro_line|#ifndef _PPC64_SECTIONS_H
DECL|macro|_PPC64_SECTIONS_H
mdefine_line|#define _PPC64_SECTIONS_H
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
macro_line|#include &lt;asm-generic/sections.h&gt;
DECL|macro|__pmac
mdefine_line|#define __pmac
DECL|macro|__pmacdata
mdefine_line|#define __pmacdata
DECL|macro|__prep
mdefine_line|#define __prep
DECL|macro|__prepdata
mdefine_line|#define __prepdata
DECL|macro|__chrp
mdefine_line|#define __chrp
DECL|macro|__chrpdata
mdefine_line|#define __chrpdata
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata
DECL|function|in_kernel_text
r_static
r_inline
r_int
id|in_kernel_text
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|_stext
op_logical_and
id|addr
OL
(paren
r_int
r_int
)paren
id|__init_end
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
