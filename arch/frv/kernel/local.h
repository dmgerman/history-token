multiline_comment|/* local.h: local definitions&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _FRV_LOCAL_H
DECL|macro|_FRV_LOCAL_H
mdefine_line|#define _FRV_LOCAL_H
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* dma.c */
r_extern
r_int
r_int
id|frv_dma_inprogress
suffix:semicolon
r_extern
r_void
id|frv_dma_pause_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|frv_dma_resume_all
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* sleep.S */
r_extern
id|asmlinkage
r_void
id|frv_cpu_suspend
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|frv_cpu_core_sleep
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* setup.c */
r_extern
r_int
r_int
id|__nongprelbss
id|pdm_suspend_mode
suffix:semicolon
r_extern
r_void
id|determine_clocks
c_func
(paren
r_int
id|verbose
)paren
suffix:semicolon
r_extern
r_int
id|__nongprelbss
id|clock_p0_current
suffix:semicolon
r_extern
r_int
id|__nongprelbss
id|clock_cm_current
suffix:semicolon
r_extern
r_int
id|__nongprelbss
id|clock_cmode_current
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_extern
r_int
id|__nongprelbss
id|clock_cmodes_permitted
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|clock_bits_settable
suffix:semicolon
DECL|macro|CLOCK_BIT_CM
mdefine_line|#define CLOCK_BIT_CM&t;&t;0x0000000f
DECL|macro|CLOCK_BIT_CM_H
mdefine_line|#define CLOCK_BIT_CM_H&t;&t;0x00000001&t;/* CLKC.CM can be set to 0 */
DECL|macro|CLOCK_BIT_CM_M
mdefine_line|#define CLOCK_BIT_CM_M&t;&t;0x00000002&t;/* CLKC.CM can be set to 1 */
DECL|macro|CLOCK_BIT_CM_L
mdefine_line|#define CLOCK_BIT_CM_L&t;&t;0x00000004&t;/* CLKC.CM can be set to 2 */
DECL|macro|CLOCK_BIT_P0
mdefine_line|#define CLOCK_BIT_P0&t;&t;0x00000010&t;/* CLKC.P0 can be changed */
DECL|macro|CLOCK_BIT_CMODE
mdefine_line|#define CLOCK_BIT_CMODE&t;&t;0x00000020&t;/* CLKC.CMODE can be changed */
r_extern
r_void
(paren
op_star
id|__power_switch_wake_setup
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__power_switch_wake_check
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|__power_switch_wake_cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* time.c */
r_extern
r_void
id|time_divisor_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _FRV_LOCAL_H */
eof
