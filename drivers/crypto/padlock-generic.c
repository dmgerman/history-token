multiline_comment|/* &n; * Cryptographic API.&n; *&n; * Support for VIA PadLock hardware crypto engine.&n; *&n; * Copyright (c) 2004  Michal Ludvig &lt;michal@logix.cz&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;padlock.h&quot;
r_static
r_int
id|__init
DECL|function|padlock_init
id|padlock_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_xcrypt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;VIA PadLock not detected.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_xcrypt_enabled
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;VIA PadLock detected, but not enabled. Hmm, strange...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CRYPTO_DEV_PADLOCK_AES
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|padlock_init_aes
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;VIA PadLock AES initialization failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOSYS
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Hmm, VIA PadLock was compiled without any algorithm.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|padlock_fini
id|padlock_fini
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CRYPTO_DEV_PADLOCK_AES
id|padlock_fini_aes
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|padlock_init
id|module_init
c_func
(paren
id|padlock_init
)paren
suffix:semicolon
DECL|variable|padlock_fini
id|module_exit
c_func
(paren
id|padlock_fini
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VIA PadLock crypto engine support.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michal Ludvig&quot;
)paren
suffix:semicolon
eof
