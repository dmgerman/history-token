multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * This file contains definitions for accessing a platform supported high resolution&n; * clock. The clock is monitonically increasing and can be accessed from any node&n; * in the system. The clock is synchronized across nodes - all nodes see the&n; * same value.&n; * &n; *&t;RTC_COUNTER_ADDR - contains the address of the counter &n; *&n; *&t;GET_RTC_COUNTER() - macro to read the value of the clock&n; *&n; *&t;RTC_CYCLES_PER_SEC - clock frequency in ticks per second&t;&n; *&n; */
macro_line|#ifndef _ASM_IA64_SN_CLKSUPPORT_H
DECL|macro|_ASM_IA64_SN_CLKSUPPORT_H
mdefine_line|#define _ASM_IA64_SN_CLKSUPPORT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
DECL|typedef|clkreg_t
r_typedef
r_int
id|clkreg_t
suffix:semicolon
r_extern
r_int
id|sn_rtc_cycles_per_second
suffix:semicolon
macro_line|#if defined(CONFIG_IA64_SGI_SN1)
macro_line|#include &lt;asm/sn/sn1/bedrock.h&gt;
macro_line|#include &lt;asm/sn/sn1/hubpi_next.h&gt;
multiline_comment|/* clocks are not synchronized yet on SN1  - used node 0 (problem if no NASID 0) */
DECL|macro|RTC_COUNTER_ADDR
mdefine_line|#define RTC_COUNTER_ADDR&t;((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_COUNTER))
DECL|macro|RTC_COMPARE_A_ADDR
mdefine_line|#define RTC_COMPARE_A_ADDR      ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_COMPARE_A))
DECL|macro|RTC_COMPARE_B_ADDR
mdefine_line|#define RTC_COMPARE_B_ADDR      ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_COMPARE_B))
DECL|macro|RTC_INT_PENDING_A_ADDR
mdefine_line|#define RTC_INT_PENDING_A_ADDR  ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_INT_PEND_A))
DECL|macro|RTC_INT_PENDING_B_ADDR
mdefine_line|#define RTC_INT_PENDING_B_ADDR  ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_INT_PEND_B))
DECL|macro|RTC_INT_ENABLED_A_ADDR
mdefine_line|#define RTC_INT_ENABLED_A_ADDR  ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_INT_EN_A))
DECL|macro|RTC_INT_ENABLED_B_ADDR
mdefine_line|#define RTC_INT_ENABLED_B_ADDR  ((clkreg_t*)REMOTE_HUB_ADDR(0, PI_RT_INT_EN_B))
macro_line|#else
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
DECL|macro|RTC_COUNTER_ADDR
mdefine_line|#define RTC_COUNTER_ADDR&t;((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_COMPARE_A_ADDR
mdefine_line|#define RTC_COMPARE_A_ADDR      ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_COMPARE_B_ADDR
mdefine_line|#define RTC_COMPARE_B_ADDR      ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_INT_PENDING_A_ADDR
mdefine_line|#define RTC_INT_PENDING_A_ADDR  ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_INT_PENDING_B_ADDR
mdefine_line|#define RTC_INT_PENDING_B_ADDR  ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_INT_ENABLED_A_ADDR
mdefine_line|#define RTC_INT_ENABLED_A_ADDR  ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|RTC_INT_ENABLED_B_ADDR
mdefine_line|#define RTC_INT_ENABLED_B_ADDR  ((clkreg_t*)LOCAL_MMR_ADDR(SH_RTC))
macro_line|#endif
DECL|macro|GET_RTC_COUNTER
mdefine_line|#define GET_RTC_COUNTER()&t;(*RTC_COUNTER_ADDR)
DECL|macro|rtc_time
mdefine_line|#define rtc_time()&t;&t;GET_RTC_COUNTER()
DECL|macro|RTC_CYCLES_PER_SEC
mdefine_line|#define RTC_CYCLES_PER_SEC&t;sn_rtc_cycles_per_second
macro_line|#endif /* _ASM_IA64_SN_CLKSUPPORT_H */
eof
