multiline_comment|/*&n; *  arch/s390/lib/misaligned.c&n; *    S390 misalignment panic stubs&n; *&n; *  S390 version&n; *    Copyright (C) 2001 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com).&n; *&n; * xchg wants to panic if the pointer is not aligned. To avoid multiplying&n; * the panic message over and over again, the panic is done in the helper&n; * functions __misaligned_u32 and __misaligned_u16.&n; */
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/kernel.h&gt;
DECL|function|__misaligned_u16
r_void
id|__misaligned_u16
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;misaligned (__u16 *) in __xchg&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|__misaligned_u32
r_void
id|__misaligned_u32
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;misaligned (__u32 *) in __xchg&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|__misaligned_u16
id|EXPORT_SYMBOL
c_func
(paren
id|__misaligned_u16
)paren
suffix:semicolon
DECL|variable|__misaligned_u32
id|EXPORT_SYMBOL
c_func
(paren
id|__misaligned_u32
)paren
suffix:semicolon
eof
