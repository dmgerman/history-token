multiline_comment|/* $Id: loadmmu.c,v 1.56 2000/02/08 20:24:21 davem Exp $&n; * loadmmu.c:  This code loads up all the mm function pointers once the&n; *             machine type has been determined.  It also sets the static&n; *             mmu values such as PAGE_NONE, etc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/a.out.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|variable|ctx_list_pool
r_struct
id|ctx_list
op_star
id|ctx_list_pool
suffix:semicolon
DECL|variable|ctx_free
r_struct
id|ctx_list
id|ctx_free
suffix:semicolon
DECL|variable|ctx_used
r_struct
id|ctx_list
id|ctx_used
suffix:semicolon
DECL|variable|pg_iobits
r_int
r_int
id|pg_iobits
suffix:semicolon
r_extern
r_void
id|ld_mmu_sun4c
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ld_mmu_srmmu
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|load_mmu
r_void
id|__init
id|load_mmu
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_case
id|sun4
suffix:colon
id|ld_mmu_sun4c
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
r_case
id|sun4d
suffix:colon
id|ld_mmu_srmmu
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;load_mmu: %d unsupported&bslash;n&quot;
comma
(paren
r_int
)paren
id|sparc_cpu_model
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|btfixup
c_func
(paren
)paren
suffix:semicolon
)brace
eof
