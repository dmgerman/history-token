multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/gp_timers.h&n; *&n; * Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *   07-28-2000&t;SJH&t;Created file&n; *   08-02-2000&t;SJH&t;Used structure for registers&n; */
macro_line|#ifndef _ASM_ARCH_GPTIMERS_H
DECL|macro|_ASM_ARCH_GPTIMERS_H
mdefine_line|#define _ASM_ARCH_GPTIMERS_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
multiline_comment|/*&n; * Layout of L7200 general purpose timer registers&n; */
DECL|struct|GPT_Regs
r_struct
id|GPT_Regs
(brace
DECL|member|TIMERLOAD
r_int
r_int
id|TIMERLOAD
suffix:semicolon
DECL|member|TIMERVALUE
r_int
r_int
id|TIMERVALUE
suffix:semicolon
DECL|member|TIMERCONTROL
r_int
r_int
id|TIMERCONTROL
suffix:semicolon
DECL|member|TIMERCLEAR
r_int
r_int
id|TIMERCLEAR
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GPT_BASE
mdefine_line|#define GPT_BASE&t;&t;(IO_BASE_2 + 0x3000)
DECL|macro|l7200_timer1_regs
mdefine_line|#define l7200_timer1_regs&t;((volatile struct GPT_Regs *) (GPT_BASE))
DECL|macro|l7200_timer2_regs
mdefine_line|#define l7200_timer2_regs&t;((volatile struct GPT_Regs *) (GPT_BASE + 0x20))
multiline_comment|/*&n; * General register values&n; */
DECL|macro|GPT_PRESCALE_1
mdefine_line|#define&t;GPT_PRESCALE_1&t;&t;0x00000000
DECL|macro|GPT_PRESCALE_16
mdefine_line|#define&t;GPT_PRESCALE_16&t;&t;0x00000004
DECL|macro|GPT_PRESCALE_256
mdefine_line|#define&t;GPT_PRESCALE_256&t;0x00000008
DECL|macro|GPT_MODE_FREERUN
mdefine_line|#define GPT_MODE_FREERUN&t;0x00000000
DECL|macro|GPT_MODE_PERIODIC
mdefine_line|#define GPT_MODE_PERIODIC&t;0x00000040
DECL|macro|GPT_ENABLE
mdefine_line|#define GPT_ENABLE&t;&t;0x00000080
DECL|macro|GPT_BZTOG
mdefine_line|#define GPT_BZTOG&t;&t;0x00000100
DECL|macro|GPT_BZMOD
mdefine_line|#define GPT_BZMOD&t;&t;0x00000200
DECL|macro|GPT_LOAD_MASK
mdefine_line|#define GPT_LOAD_MASK &t;&t;0x0000ffff
macro_line|#endif
eof
