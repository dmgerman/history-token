multiline_comment|/* $Id: pcimt_scache.c,v 1.4 1999/01/04 16:03:59 ralf Exp $&n; *&n; * arch/mips/sni/pcimt_scache.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1997, 1998 by Ralf Baechle&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
DECL|macro|cacheconf
mdefine_line|#define cacheconf (*(volatile unsigned int *)PCIMT_CACHECONF)
DECL|macro|invspace
mdefine_line|#define invspace (*(volatile unsigned int *)PCIMT_INVSPACE)
DECL|function|sni_pcimt_sc_init
r_void
id|__init
id|sni_pcimt_sc_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|scsiz
comma
id|sc_size
suffix:semicolon
id|scsiz
op_assign
id|cacheconf
op_amp
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|scsiz
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Second level cache is deactived.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scsiz
op_ge
l_int|6
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid second level cache size configured, &quot;
l_string|&quot;deactivating second level cache.&bslash;n&quot;
)paren
suffix:semicolon
id|cacheconf
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sc_size
op_assign
l_int|128
op_lshift
id|scsiz
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%dkb second level cache detected, deactivating.&bslash;n&quot;
comma
id|sc_size
)paren
suffix:semicolon
id|cacheconf
op_assign
l_int|0
suffix:semicolon
)brace
eof
