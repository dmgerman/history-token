multiline_comment|/* timer-regs.h: hardware timer register definitions&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_TIMER_REGS_H
DECL|macro|_ASM_TIMER_REGS_H
mdefine_line|#define _ASM_TIMER_REGS_H
macro_line|#include &lt;asm/sections.h&gt;
r_extern
r_int
r_int
id|__nongprelbss
id|__clkin_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__ext_bus_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__res_bus_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__sdram_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__core_bus_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__core_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__dsu_clock_speed_HZ
suffix:semicolon
r_extern
r_int
r_int
id|__nongprelbss
id|__serial_clock_speed_HZ
suffix:semicolon
DECL|macro|__get_CLKC
mdefine_line|#define __get_CLKC()&t;({ *(volatile unsigned long *)(0xfeff9a00); })
DECL|function|__set_CLKC
r_static
r_inline
r_void
id|__set_CLKC
c_func
(paren
r_int
r_int
id|v
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;&t;st%I0.p&t;%2,%M0&t;&t;&bslash;n&quot;
l_string|&quot;&t;setlos&t;%3,%1&t;&t;&bslash;n&quot;
l_string|&quot;&t;membar&t;&t;&t;&bslash;n&quot;
l_string|&quot;0:&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;subicc&t;%1,#1,%1,icc0&t;&bslash;n&quot;
l_string|&quot;&t;bnc&t;icc0,#1,0b&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfeff9a00
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|v
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|256
)paren
suffix:colon
l_string|&quot;icc0&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__get_TCTR
mdefine_line|#define __get_TCTR()&t;({ *(volatile unsigned long *)(0xfeff9418); })
DECL|macro|__get_TPRV
mdefine_line|#define __get_TPRV()&t;({ *(volatile unsigned long *)(0xfeff9420); })
DECL|macro|__get_TPRCKSL
mdefine_line|#define __get_TPRCKSL()&t;({ *(volatile unsigned long *)(0xfeff9428); })
DECL|macro|__get_TCSR
mdefine_line|#define __get_TCSR(T)&t;({ *(volatile unsigned long *)(0xfeff9400 + 8 * (T)); })
DECL|macro|__get_TxCKSL
mdefine_line|#define __get_TxCKSL(T)&t;({ *(volatile unsigned long *)(0xfeff9430 + 8 * (T)); })
DECL|macro|__get_TCSR_DATA
mdefine_line|#define __get_TCSR_DATA(T) ({ __get_TCSR(T) &gt;&gt; 24; })
DECL|macro|__set_TCTR
mdefine_line|#define __set_TCTR(V)&t;do { *(volatile unsigned long *)(0xfeff9418) = (V); mb(); } while(0)
DECL|macro|__set_TPRV
mdefine_line|#define __set_TPRV(V)&t;do { *(volatile unsigned long *)(0xfeff9420) = (V) &lt;&lt; 24; mb(); } while(0)
DECL|macro|__set_TPRCKSL
mdefine_line|#define __set_TPRCKSL(V) do { *(volatile unsigned long *)(0xfeff9428) = (V); mb(); } while(0)
DECL|macro|__set_TCSR
mdefine_line|#define __set_TCSR(T,V)&t;&bslash;&n;do { *(volatile unsigned long *)(0xfeff9400 + 8 * (T)) = (V); mb(); } while(0)
DECL|macro|__set_TxCKSL
mdefine_line|#define __set_TxCKSL(T,V) &bslash;&n;do { *(volatile unsigned long *)(0xfeff9430 + 8 * (T)) = (V); mb(); } while(0)
DECL|macro|__set_TCSR_DATA
mdefine_line|#define __set_TCSR_DATA(T,V) __set_TCSR(T, (V) &lt;&lt; 24)
DECL|macro|__set_TxCKSL_DATA
mdefine_line|#define __set_TxCKSL_DATA(T,V) __set_TxCKSL(T, TxCKSL_EIGHT | __TxCKSL_SELECT((V)))
multiline_comment|/* clock control register */
DECL|macro|CLKC_CMODE
mdefine_line|#define CLKC_CMODE&t;&t;0x0f000000
DECL|macro|CLKC_SLPL
mdefine_line|#define CLKC_SLPL&t;&t;0x000f0000
DECL|macro|CLKC_P0
mdefine_line|#define CLKC_P0&t;&t;&t;0x00000100
DECL|macro|CLKC_CM
mdefine_line|#define CLKC_CM&t;&t;&t;0x00000003
DECL|macro|CLKC_CMODE_s
mdefine_line|#define CLKC_CMODE_s&t;&t;24
multiline_comment|/* timer control register - non-readback mode */
DECL|macro|TCTR_MODE_0
mdefine_line|#define TCTR_MODE_0&t;&t;0x00000000
DECL|macro|TCTR_MODE_2
mdefine_line|#define TCTR_MODE_2&t;&t;0x04000000
DECL|macro|TCTR_MODE_4
mdefine_line|#define TCTR_MODE_4&t;&t;0x08000000
DECL|macro|TCTR_MODE_5
mdefine_line|#define TCTR_MODE_5&t;&t;0x0a000000
DECL|macro|TCTR_RL_LATCH
mdefine_line|#define TCTR_RL_LATCH&t;&t;0x00000000
DECL|macro|TCTR_RL_RW_LOW8
mdefine_line|#define TCTR_RL_RW_LOW8&t;&t;0x10000000
DECL|macro|TCTR_RL_RW_HIGH8
mdefine_line|#define TCTR_RL_RW_HIGH8&t;0x20000000
DECL|macro|TCTR_RL_RW_LH8
mdefine_line|#define TCTR_RL_RW_LH8&t;&t;0x30000000
DECL|macro|TCTR_SC_CTR0
mdefine_line|#define TCTR_SC_CTR0&t;&t;0x00000000
DECL|macro|TCTR_SC_CTR1
mdefine_line|#define TCTR_SC_CTR1&t;&t;0x40000000
DECL|macro|TCTR_SC_CTR2
mdefine_line|#define TCTR_SC_CTR2&t;&t;0x80000000
multiline_comment|/* timer control register - readback mode */
DECL|macro|TCTR_CNT0
mdefine_line|#define TCTR_CNT0&t;&t;0x02000000
DECL|macro|TCTR_CNT1
mdefine_line|#define TCTR_CNT1&t;&t;0x04000000
DECL|macro|TCTR_CNT2
mdefine_line|#define TCTR_CNT2&t;&t;0x08000000
DECL|macro|TCTR_NSTATUS
mdefine_line|#define TCTR_NSTATUS&t;&t;0x10000000
DECL|macro|TCTR_NCOUNT
mdefine_line|#define TCTR_NCOUNT&t;&t;0x20000000
DECL|macro|TCTR_SC_READBACK
mdefine_line|#define TCTR_SC_READBACK&t;0xc0000000
multiline_comment|/* timer control status registers - non-readback mode */
DECL|macro|TCSRx_DATA
mdefine_line|#define TCSRx_DATA&t;&t;0xff000000
multiline_comment|/* timer control status registers - readback mode */
DECL|macro|TCSRx_OUTPUT
mdefine_line|#define TCSRx_OUTPUT&t;&t;0x80000000
DECL|macro|TCSRx_NULLCOUNT
mdefine_line|#define TCSRx_NULLCOUNT&t;&t;0x40000000
DECL|macro|TCSRx_RL
mdefine_line|#define TCSRx_RL&t;&t;0x30000000
DECL|macro|TCSRx_MODE
mdefine_line|#define TCSRx_MODE&t;&t;0x07000000
multiline_comment|/* timer clock select registers */
DECL|macro|TxCKSL_SELECT
mdefine_line|#define TxCKSL_SELECT&t;&t;0x0f000000
DECL|macro|__TxCKSL_SELECT
mdefine_line|#define __TxCKSL_SELECT(X)&t;((X) &lt;&lt; 24)
DECL|macro|TxCKSL_EIGHT
mdefine_line|#define TxCKSL_EIGHT&t;&t;0xf0000000
macro_line|#endif /* _ASM_TIMER_REGS_H */
eof
