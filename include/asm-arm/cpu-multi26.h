multiline_comment|/*&n; *  linux/include/asm-arm/cpu-multi26.h&n; *&n; *  Copyright (C) 2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward-declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t change this structure - ASM code&n; * relies on it.&n; */
DECL|struct|processor
r_extern
r_struct
id|processor
(brace
multiline_comment|/* check for any bugs */
DECL|member|_check_bugs
r_void
(paren
op_star
id|_check_bugs
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Set up any processor specifics */
DECL|member|_proc_init
r_void
(paren
op_star
id|_proc_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Disable any processor specifics */
DECL|member|_proc_fin
r_void
(paren
op_star
id|_proc_fin
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* set the MEMC hardware mappings */
DECL|member|_set_pgd
r_void
(paren
op_star
id|_set_pgd
)paren
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
multiline_comment|/* XCHG */
DECL|member|_xchg_1
r_int
r_int
(paren
op_star
id|_xchg_1
)paren
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|member|_xchg_4
r_int
r_int
(paren
op_star
id|_xchg_4
)paren
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
)brace
id|processor
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm2_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm250_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm3_processor_functions
suffix:semicolon
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs()&t;&t;&t;processor._check_bugs()
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init()&t;&t;&t;&t;processor._proc_init()
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin()&t;&t;&t;&t;processor._proc_fin()
DECL|macro|cpu_do_idle
mdefine_line|#define cpu_do_idle()&t;&t;&t;&t;do { } while (0)
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,tsk)&t;&t;&t;processor._set_pgd(pgd)
DECL|macro|cpu_xchg_1
mdefine_line|#define cpu_xchg_1(x,ptr)&t;&t;&t;processor._xchg_1(x,ptr)
DECL|macro|cpu_xchg_4
mdefine_line|#define cpu_xchg_4(x,ptr)&t;&t;&t;processor._xchg_4(x,ptr)
r_extern
r_void
id|cpu_memc_update_all
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
suffix:semicolon
r_extern
r_void
id|cpu_memc_update_entry
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|phys_pte
comma
r_int
r_int
id|log_addr
)paren
suffix:semicolon
macro_line|#endif
eof
