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
multiline_comment|/*&n; * Macros to manipulate the interrupt register on the calling hub chip.&n; */
DECL|macro|LOCAL_HUB_SEND_INTR
mdefine_line|#define LOCAL_HUB_SEND_INTR(level)&t;&t;&t;&t;&bslash;&n;&t;LOCAL_HUB_S(PI_INT_PEND_MOD, (0x100 | (level)))
DECL|macro|REMOTE_HUB_SEND_INTR
mdefine_line|#define REMOTE_HUB_SEND_INTR(hub, level)&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((hub), PI_INT_PEND_MOD, (0x100 | (level)))
multiline_comment|/*&n; * When clearing the interrupt, make sure this clear does make it&n; * to the hub. Otherwise we could end up losing interrupts.&n; * We do an uncached load of the int_pend0 register to ensure this.&n; */
DECL|macro|LOCAL_HUB_CLR_INTR
mdefine_line|#define LOCAL_HUB_CLR_INTR(level)&t;  &t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;LOCAL_HUB_S(PI_INT_PEND_MOD, (level));&t;&t;&t;&bslash;&n;&t;LOCAL_HUB_L(PI_INT_PEND0);&t;&t;&t;&t;&bslash;&n;} while (0);
DECL|macro|REMOTE_HUB_CLR_INTR
mdefine_line|#define REMOTE_HUB_CLR_INTR(hub, level)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nasid_t  __hub = (hub);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S(__hub, PI_INT_PEND_MOD, (level));&t;&t;&bslash;&n;&t;REMOTE_HUB_L(__hub, PI_INT_PEND0);&t;&t;&t;&bslash;&n;} while (0);
multiline_comment|/*&n; * Hard-coded interrupt levels:&n; */
multiline_comment|/*&n; *&t;L0 = SW1&n; *&t;L1 = SW2&n; *&t;L2 = INT_PEND0&n; *&t;L3 = INT_PEND1&n; *&t;L4 = RTC&n; *&t;L5 = Profiling Timer&n; *&t;L6 = Hub Errors&n; *&t;L7 = Count/Compare (T5 counters)&n; */
multiline_comment|/*&n; * INT_PEND0 hard-coded bits.&n; */
multiline_comment|/*&n; * INT_PEND0 bits determined by hardware:&n; */
DECL|macro|RESERVED_INTR
mdefine_line|#define RESERVED_INTR&t;&t; 0&t;/* What is this bit? */
DECL|macro|GFX_INTR_A
mdefine_line|#define GFX_INTR_A&t;&t; 1
DECL|macro|GFX_INTR_B
mdefine_line|#define GFX_INTR_B&t;&t; 2
DECL|macro|PG_MIG_INTR
mdefine_line|#define PG_MIG_INTR&t;&t; 3
DECL|macro|UART_INTR
mdefine_line|#define UART_INTR&t;&t; 4
DECL|macro|CC_PEND_A
mdefine_line|#define CC_PEND_A&t;&t; 5
DECL|macro|CC_PEND_B
mdefine_line|#define CC_PEND_B&t;&t; 6
multiline_comment|/*&n; * INT_PEND0 used by the kernel for itself ...&n; */
DECL|macro|CPU_RESCHED_A_IRQ
mdefine_line|#define CPU_RESCHED_A_IRQ&t; 7
DECL|macro|CPU_RESCHED_B_IRQ
mdefine_line|#define CPU_RESCHED_B_IRQ&t; 8
DECL|macro|CPU_CALL_A_IRQ
mdefine_line|#define CPU_CALL_A_IRQ&t;&t; 9
DECL|macro|CPU_CALL_B_IRQ
mdefine_line|#define CPU_CALL_B_IRQ&t;&t;10
DECL|macro|MSC_MESG_INTR
mdefine_line|#define MSC_MESG_INTR&t;&t;11
DECL|macro|BASE_PCI_IRQ
mdefine_line|#define BASE_PCI_IRQ&t;&t;12
multiline_comment|/*&n; * INT_PEND0 again, bits determined by hardware / hardcoded:&n; */
DECL|macro|SDISK_INTR
mdefine_line|#define SDISK_INTR&t;&t;63&t;/* SABLE name */
DECL|macro|IP_PEND0_6_63
mdefine_line|#define IP_PEND0_6_63&t;&t;63&t;/* What is this bit? */
multiline_comment|/*&n; * INT_PEND1 hard-coded bits:&n; */
DECL|macro|NI_BRDCAST_ERR_A
mdefine_line|#define NI_BRDCAST_ERR_A&t;39
DECL|macro|NI_BRDCAST_ERR_B
mdefine_line|#define NI_BRDCAST_ERR_B&t;40
DECL|macro|LLP_PFAIL_INTR_A
mdefine_line|#define LLP_PFAIL_INTR_A&t;41&t;/* see ml/SN/SN0/sysctlr.c */
DECL|macro|LLP_PFAIL_INTR_B
mdefine_line|#define LLP_PFAIL_INTR_B&t;42
DECL|macro|TLB_INTR_A
mdefine_line|#define&t;TLB_INTR_A&t;&t;43&t;/* used for tlb flush random */
DECL|macro|TLB_INTR_B
mdefine_line|#define&t;TLB_INTR_B&t;&t;44
DECL|macro|IP27_INTR_0
mdefine_line|#define IP27_INTR_0&t;&t;45&t;/* Reserved for PROM use */
DECL|macro|IP27_INTR_1
mdefine_line|#define IP27_INTR_1&t;&t;46&t;/* do not use in Kernel */
DECL|macro|IP27_INTR_2
mdefine_line|#define IP27_INTR_2&t;&t;47
DECL|macro|IP27_INTR_3
mdefine_line|#define IP27_INTR_3&t;&t;48
DECL|macro|IP27_INTR_4
mdefine_line|#define IP27_INTR_4&t;&t;49
DECL|macro|IP27_INTR_5
mdefine_line|#define IP27_INTR_5&t;&t;50
DECL|macro|IP27_INTR_6
mdefine_line|#define IP27_INTR_6&t;&t;51
DECL|macro|IP27_INTR_7
mdefine_line|#define IP27_INTR_7&t;&t;52
DECL|macro|BRIDGE_ERROR_INTR
mdefine_line|#define BRIDGE_ERROR_INTR&t;53&t;/* Setup by PROM to catch&t;*/
multiline_comment|/* Bridge Errors */
DECL|macro|DEBUG_INTR_A
mdefine_line|#define&t;DEBUG_INTR_A&t;&t;54
DECL|macro|DEBUG_INTR_B
mdefine_line|#define&t;DEBUG_INTR_B&t;&t;55&t;/* Used by symmon to stop all cpus */
DECL|macro|IO_ERROR_INTR
mdefine_line|#define IO_ERROR_INTR&t;&t;57&t;/* Setup by PROM */
DECL|macro|CLK_ERR_INTR
mdefine_line|#define CLK_ERR_INTR&t;&t;58
DECL|macro|COR_ERR_INTR_A
mdefine_line|#define COR_ERR_INTR_A&t;&t;59
DECL|macro|COR_ERR_INTR_B
mdefine_line|#define COR_ERR_INTR_B&t;&t;60
DECL|macro|MD_COR_ERR_INTR
mdefine_line|#define MD_COR_ERR_INTR&t;&t;61
DECL|macro|NI_ERROR_INTR
mdefine_line|#define NI_ERROR_INTR&t;&t;62
DECL|macro|MSC_PANIC_INTR
mdefine_line|#define MSC_PANIC_INTR&t;&t;63
macro_line|#endif /* __ASM_SN_INTR_H */
eof
