macro_line|#ifndef _ASM_IA64_DELAY_H
DECL|macro|_ASM_IA64_DELAY_H
mdefine_line|#define _ASM_IA64_DELAY_H
multiline_comment|/*&n; * Delay routines using a pre-computed &quot;cycles/usec&quot; value.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
r_static
id|__inline__
r_void
DECL|function|ia64_set_itm
id|ia64_set_itm
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.itm=%0;; srlz.d;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_int
r_int
DECL|function|ia64_get_itm
id|ia64_get_itm
(paren
r_void
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=cr.itm;; srlz.d;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
op_scope_resolution
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|ia64_set_itv
id|ia64_set_itv
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.itv=%0;; srlz.d;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|ia64_set_itc
id|ia64_set_itc
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov ar.itc=%0;; srlz.d;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_int
r_int
DECL|function|ia64_get_itc
id|ia64_get_itc
(paren
r_void
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=ar.itc&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
op_scope_resolution
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ITANIUM
r_while
c_loop
(paren
id|unlikely
c_func
(paren
(paren
id|__s32
)paren
id|result
op_eq
op_minus
l_int|1
)paren
)paren
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=ar.itc&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
op_scope_resolution
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|result
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|__delay
id|__delay
(paren
r_int
r_int
id|loops
)paren
(brace
r_int
r_int
id|saved_ar_lc
suffix:semicolon
r_if
c_cond
(paren
id|loops
OL
l_int|1
)paren
r_return
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=ar.lc;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|saved_ar_lc
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov ar.lc=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|loops
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&bslash;tbr.cloop.sptk.few 1b;;&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov ar.lc=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|saved_ar_lc
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|udelay
id|udelay
(paren
r_int
r_int
id|usecs
)paren
(brace
r_int
r_int
id|start
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|cycles
op_assign
id|usecs
op_star
id|local_cpu_data-&gt;cyc_per_usec
suffix:semicolon
r_while
c_loop
(paren
id|ia64_get_itc
c_func
(paren
)paren
op_minus
id|start
OL
id|cycles
)paren
multiline_comment|/* skip */
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_DELAY_H */
eof
