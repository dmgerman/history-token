multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SN_INTR_H
DECL|macro|__ASM_SN_INTR_H
mdefine_line|#define __ASM_SN_INTR_H
multiline_comment|/* Number of interrupt levels associated with each interrupt register. */
DECL|macro|N_INTPEND_BITS
mdefine_line|#define N_INTPEND_BITS&t;&t;64
DECL|macro|INT_PEND0_BASELVL
mdefine_line|#define INT_PEND0_BASELVL&t;0
DECL|macro|INT_PEND1_BASELVL
mdefine_line|#define INT_PEND1_BASELVL&t;64
DECL|macro|N_INTPENDJUNK_BITS
mdefine_line|#define&t;N_INTPENDJUNK_BITS&t;8
DECL|macro|INTPENDJUNK_CLRBIT
mdefine_line|#define&t;INTPENDJUNK_CLRBIT&t;0x80
macro_line|#include &lt;asm/sn/intr_public.h&gt;
macro_line|#if _LANGUAGE_C
multiline_comment|/*&n; * Macros to manipulate the interrupt register on the calling hub chip.&n; */
DECL|macro|LOCAL_HUB_SEND_INTR
mdefine_line|#define LOCAL_HUB_SEND_INTR(_level)&t;LOCAL_HUB_S(PI_INT_PEND_MOD, &bslash;&n;&t;&t;&t;&t;&t;&t;    (0x100|(_level)))
DECL|macro|REMOTE_HUB_SEND_INTR
mdefine_line|#define REMOTE_HUB_SEND_INTR(_hub, _level) &bslash;&n;&t;&t;REMOTE_HUB_S((_hub), PI_INT_PEND_MOD, (0x100|(_level)))
multiline_comment|/*&n; * When clearing the interrupt, make sure this clear does make it &n; * to the hub. Otherwise we could end up losing interrupts.&n; * We do an uncached load of the int_pend0 register to ensure this.&n; */
DECL|macro|LOCAL_HUB_CLR_INTR
mdefine_line|#define LOCAL_HUB_CLR_INTR(_level)&t;  &bslash;&n;                LOCAL_HUB_S(PI_INT_PEND_MOD, (_level)),&t;&bslash;&n;                LOCAL_HUB_L(PI_INT_PEND0)
DECL|macro|REMOTE_HUB_CLR_INTR
mdefine_line|#define REMOTE_HUB_CLR_INTR(_hub, _level) &bslash;&n;&t;&t;REMOTE_HUB_S((_hub), PI_INT_PEND_MOD, (_level)),&t;&bslash;&n;                REMOTE_HUB_L((_hub), PI_INT_PEND0)
macro_line|#else /* LANGUAGE_ASSEMBLY */
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/*&n; * Hard-coded interrupt levels:&n; */
multiline_comment|/*&n; *&t;L0 = SW1&n; *&t;L1 = SW2&n; *&t;L2 = INT_PEND0&n; *&t;L3 = INT_PEND1&n; *&t;L4 = RTC&n; *&t;L5 = Profiling Timer&n; *&t;L6 = Hub Errors&n; *&t;L7 = Count/Compare (T5 counters)&n; */
multiline_comment|/* INT_PEND0 hard-coded bits. */
macro_line|#ifdef SABLE
DECL|macro|SDISK_INTR
mdefine_line|#define SDISK_INTR&t;63
macro_line|#endif
macro_line|#ifdef DEBUG_INTR_TSTAMP
multiline_comment|/* hard coded interrupt level for interrupt latency test interrupt */
DECL|macro|CPU_INTRLAT_B
mdefine_line|#define&t;CPU_INTRLAT_B&t;62
DECL|macro|CPU_INTRLAT_A
mdefine_line|#define&t;CPU_INTRLAT_A&t;61
macro_line|#endif
multiline_comment|/* Hardcoded bits required by software. */
DECL|macro|MSC_MESG_INTR
mdefine_line|#define MSC_MESG_INTR&t;13
DECL|macro|CPU_ACTION_B
mdefine_line|#define CPU_ACTION_B&t;11
DECL|macro|CPU_ACTION_A
mdefine_line|#define CPU_ACTION_A&t;10
multiline_comment|/* These are determined by hardware: */
DECL|macro|CC_PEND_B
mdefine_line|#define CC_PEND_B&t;6
DECL|macro|CC_PEND_A
mdefine_line|#define CC_PEND_A&t;5
DECL|macro|UART_INTR
mdefine_line|#define UART_INTR&t;4
DECL|macro|PG_MIG_INTR
mdefine_line|#define PG_MIG_INTR&t;3
DECL|macro|GFX_INTR_B
mdefine_line|#define GFX_INTR_B&t;2
DECL|macro|GFX_INTR_A
mdefine_line|#define GFX_INTR_A&t;1
DECL|macro|RESERVED_INTR
mdefine_line|#define RESERVED_INTR&t;0
multiline_comment|/* INT_PEND1 hard-coded bits: */
DECL|macro|MSC_PANIC_INTR
mdefine_line|#define MSC_PANIC_INTR&t;63
DECL|macro|NI_ERROR_INTR
mdefine_line|#define NI_ERROR_INTR&t;62
DECL|macro|MD_COR_ERR_INTR
mdefine_line|#define MD_COR_ERR_INTR&t;61
DECL|macro|COR_ERR_INTR_B
mdefine_line|#define COR_ERR_INTR_B&t;60
DECL|macro|COR_ERR_INTR_A
mdefine_line|#define COR_ERR_INTR_A&t;59
DECL|macro|CLK_ERR_INTR
mdefine_line|#define CLK_ERR_INTR&t;58
DECL|macro|IO_ERROR_INTR
mdefine_line|#define IO_ERROR_INTR&t;57&t;/* set up by prom */
DECL|macro|DEBUG_INTR_B
mdefine_line|#define&t;DEBUG_INTR_B&t;55&t;/* used by symmon to stop all cpus */
DECL|macro|DEBUG_INTR_A
mdefine_line|#define&t;DEBUG_INTR_A&t;54
DECL|macro|BRIDGE_ERROR_INTR
mdefine_line|#define BRIDGE_ERROR_INTR 53&t;/* Setup by PROM to catch Bridge Errors */
DECL|macro|IP27_INTR_0
mdefine_line|#define IP27_INTR_0&t;52&t;/* Reserved for PROM use */
DECL|macro|IP27_INTR_1
mdefine_line|#define IP27_INTR_1&t;51&t;/*   (do not use in Kernel) */
DECL|macro|IP27_INTR_2
mdefine_line|#define IP27_INTR_2&t;50
DECL|macro|IP27_INTR_3
mdefine_line|#define IP27_INTR_3&t;49
DECL|macro|IP27_INTR_4
mdefine_line|#define IP27_INTR_4&t;48
DECL|macro|IP27_INTR_5
mdefine_line|#define IP27_INTR_5&t;47
DECL|macro|IP27_INTR_6
mdefine_line|#define IP27_INTR_6&t;46
DECL|macro|IP27_INTR_7
mdefine_line|#define IP27_INTR_7&t;45
DECL|macro|TLB_INTR_B
mdefine_line|#define&t;TLB_INTR_B&t;44&t;/* used for tlb flush random */
DECL|macro|TLB_INTR_A
mdefine_line|#define&t;TLB_INTR_A&t;43
DECL|macro|LLP_PFAIL_INTR_B
mdefine_line|#define LLP_PFAIL_INTR_B 42&t;/* see ml/SN/SN0/sysctlr.c */
DECL|macro|LLP_PFAIL_INTR_A
mdefine_line|#define LLP_PFAIL_INTR_A 41
DECL|macro|NI_BRDCAST_ERR_B
mdefine_line|#define NI_BRDCAST_ERR_B 40
DECL|macro|NI_BRDCAST_ERR_A
mdefine_line|#define NI_BRDCAST_ERR_A 39
macro_line|#endif /* __ASM_SN_INTR_H */
eof
