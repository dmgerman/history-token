multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Algorithm autoloader.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &quot;internal.h&quot;
multiline_comment|/*&n; * A far more intelligent version of this is planned.  For now, just&n; * try an exact match on the name of the algorithm.&n; */
DECL|function|crypto_alg_autoload
r_void
id|crypto_alg_autoload
c_func
(paren
r_char
op_star
id|name
)paren
(brace
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
