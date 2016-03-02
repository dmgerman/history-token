multiline_comment|/*&n; *  linux/include/asm-arm/cpu-single.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
multiline_comment|/*&n; * Single CPU&n; */
macro_line|#ifdef __STDC__
DECL|macro|__catify_fn
mdefine_line|#define __catify_fn(name,x)&t;name##x
macro_line|#else
DECL|macro|__catify_fn
mdefine_line|#define __catify_fn(name,x)&t;name/**/x
macro_line|#endif
DECL|macro|__cpu_fn
mdefine_line|#define __cpu_fn(name,x)&t;__catify_fn(name,x)
multiline_comment|/*&n; * If we are supporting multiple CPUs, then we must use a table of&n; * function pointers for this lot.  Otherwise, we can optimise the&n; * table away.&n; */
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init&t;&t;&t;__cpu_fn(CPU_NAME,_proc_init)
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin&t;&t;&t;__cpu_fn(CPU_NAME,_proc_fin)
DECL|macro|cpu_reset
mdefine_line|#define cpu_reset&t;&t;&t;__cpu_fn(CPU_NAME,_reset)
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle&t;&t;&t;__cpu_fn(CPU_NAME,_do_idle)
DECL|macro|cpu_dcache_clean_area
mdefine_line|#define cpu_dcache_clean_area&t;&t;__cpu_fn(CPU_NAME,_dcache_clean_area)
DECL|macro|cpu_do_switch_mm
mdefine_line|#define cpu_do_switch_mm&t;&t;__cpu_fn(CPU_NAME,_switch_mm)
DECL|macro|cpu_set_pte
mdefine_line|#define cpu_set_pte&t;&t;&t;__cpu_fn(CPU_NAME,_set_pte)
macro_line|#include &lt;asm/page.h&gt;
r_struct
id|mm_struct
suffix:semicolon
multiline_comment|/* declare all the functions as extern */
r_extern
r_void
id|cpu_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_proc_fin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpu_do_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_dcache_clean_area
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|cpu_do_switch_mm
c_func
(paren
r_int
r_int
id|pgd_phys
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|cpu_set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pte
)paren
suffix:semicolon
r_extern
r_volatile
r_void
id|cpu_reset
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
eof
