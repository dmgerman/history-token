multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Jack Steiner (steiner@sgi.com)&n; */
macro_line|#ifndef  _ASM_KSYS_CLKSUPPORT_H
DECL|macro|_ASM_KSYS_CLKSUPPORT_H
mdefine_line|#define _ASM_KSYS_CLKSUPPORT_H
multiline_comment|/* #include &lt;sys/mips_addrspace.h&gt; */
macro_line|#if SN
macro_line|#include &lt;asm/sn/agent.h&gt;
macro_line|#include &lt;asm/sn/intr_public.h&gt;
DECL|typedef|clkreg_t
r_typedef
id|hubreg_t
id|clkreg_t
suffix:semicolon
r_extern
id|nasid_t
id|master_nasid
suffix:semicolon
DECL|macro|GET_LOCAL_RTC
mdefine_line|#define GET_LOCAL_RTC&t;&t;(clkreg_t)LOCAL_HUB_L(PI_RT_COUNT)
DECL|macro|DISABLE_TMO_INTR
mdefine_line|#define DISABLE_TMO_INTR()&t;if  (cpuid_to_localslice(cpuid())) &bslash;&n;&t;&t;&t;&t;&t;REMOTE_HUB_PI_S(get_nasid(),&bslash;&n;&t;&t;&t;&t;&t;&t;cputosubnode(cpuid()),&bslash;&n;&t;&t;&t;&t;&t;&t;PI_RT_COMPARE_B, 0); &bslash;&n;&t;&t;&t;&t;else &bslash;&n;&t;&t;&t;&t;&t;REMOTE_HUB_PI_S(get_nasid(),&bslash;&n;&t;&t;&t;&t;&t;&t;cputosubnode(cpuid()),&bslash;&n;&t;&t;&t;&t;&t;&t;PI_RT_COMPARE_A, 0);
multiline_comment|/* This is a hack; we really need to figure these values out dynamically */
multiline_comment|/* &n; * Since 800 ns works very well with various HUB frequencies, such as&n; * 360, 380, 390 and 400 MHZ, we use 800 ns rtc cycle time.&n; */
DECL|macro|NSEC_PER_CYCLE
mdefine_line|#define NSEC_PER_CYCLE&t;&t;800
DECL|macro|CYCLE_PER_SEC
mdefine_line|#define CYCLE_PER_SEC&t;&t;(NSEC_PER_SEC/NSEC_PER_CYCLE)
multiline_comment|/*&n; * Number of cycles per profiling intr &n; */
DECL|macro|CLK_FCLOCK_FAST_FREQ
mdefine_line|#define CLK_FCLOCK_FAST_FREQ&t;1250
DECL|macro|CLK_FCLOCK_SLOW_FREQ
mdefine_line|#define CLK_FCLOCK_SLOW_FREQ&t;0
multiline_comment|/* The is the address that the user will use to mmap the cycle counter */
DECL|macro|CLK_CYCLE_ADDRESS_FOR_USER
mdefine_line|#define CLK_CYCLE_ADDRESS_FOR_USER LOCAL_HUB_ADDR(PI_RT_COUNT)
macro_line|#elif IP30
macro_line|#include &lt;sys/cpu.h&gt;
DECL|typedef|clkreg_t
r_typedef
id|heartreg_t
id|clkreg_t
suffix:semicolon
DECL|macro|NSEC_PER_CYCLE
mdefine_line|#define NSEC_PER_CYCLE&t;&t;80
DECL|macro|CYCLE_PER_SEC
mdefine_line|#define CYCLE_PER_SEC&t;&t;(NSEC_PER_SEC/NSEC_PER_CYCLE)
DECL|macro|GET_LOCAL_RTC
mdefine_line|#define GET_LOCAL_RTC&t;*((volatile clkreg_t *)PHYS_TO_COMPATK1(HEART_COUNT))
DECL|macro|DISABLE_TMO_INTR
mdefine_line|#define DISABLE_TMO_INTR()
DECL|macro|CLK_CYCLE_ADDRESS_FOR_USER
mdefine_line|#define CLK_CYCLE_ADDRESS_FOR_USER PHYS_TO_K1(HEART_COUNT)
DECL|macro|CLK_FCLOCK_SLOW_FREQ
mdefine_line|#define CLK_FCLOCK_SLOW_FREQ (CYCLE_PER_SEC / HZ)
macro_line|#endif
multiline_comment|/* Prototypes */
r_extern
r_void
id|init_timebase
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fastick_maint
c_func
(paren
r_struct
id|eframe_s
op_star
)paren
suffix:semicolon
r_extern
r_int
id|audioclock
suffix:semicolon
r_extern
r_int
id|prfclk_enabled_cnt
suffix:semicolon
macro_line|#endif  /* _ASM_KSYS_CLKSUPPORT_H */
eof
