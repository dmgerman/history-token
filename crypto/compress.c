multiline_comment|/*&n; * Cryptographic API.&n; *&n; * Compression operations.&n; *&n; * Copyright (c) 2002 James Morris &lt;jmorris@intercode.com.au&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option) &n; * any later version.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &quot;internal.h&quot;
multiline_comment|/*&n; * This code currently implements blazingly fast and&n; * lossless Quadruple ROT13 compression.&n; */
DECL|function|crypto_compress
r_static
r_void
id|crypto_compress
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|crypto_decompress
r_static
r_void
id|crypto_decompress
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|crypto_init_compress_ops
r_void
id|crypto_init_compress_ops
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_struct
id|compress_tfm
op_star
id|ops
op_assign
op_amp
id|tfm-&gt;crt_compress
suffix:semicolon
id|ops-&gt;cot_compress
op_assign
id|crypto_compress
suffix:semicolon
id|ops-&gt;cot_decompress
op_assign
id|crypto_decompress
suffix:semicolon
)brace
eof
