multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * Architecture-specific kernel symbols&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN_DEBUG
DECL|variable|__pa_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__pa_debug
)paren
suffix:semicolon
DECL|variable|__va_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__va_debug
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|bte_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_copy
)paren
suffix:semicolon
DECL|variable|bte_unaligned_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_unaligned_copy
)paren
suffix:semicolon
DECL|variable|ia64_sal
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_sal
)paren
suffix:semicolon
DECL|variable|sal_lock
id|EXPORT_SYMBOL
c_func
(paren
id|sal_lock
)paren
suffix:semicolon
DECL|variable|sn_local_partid
id|EXPORT_SYMBOL
c_func
(paren
id|sn_local_partid
)paren
suffix:semicolon
eof
