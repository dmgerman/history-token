multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/IP27.h&gt;.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_SN0_IP27_H
DECL|macro|_ASM_SN_SN0_IP27_H
mdefine_line|#define _ASM_SN_SN0_IP27_H
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * Simple definitions for the masks which remove SW bits from pte.&n; */
DECL|macro|TLBLO_HWBITSHIFT
mdefine_line|#define TLBLO_HWBITSHIFT&t;0&t;&t;/* Shift value, for masking */
macro_line|#if !_LANGUAGE_ASSEMBLY
DECL|macro|CAUSE_BERRINTR
mdefine_line|#define CAUSE_BERRINTR &t;&t;IE_IRQ5
DECL|macro|ECCF_CACHE_ERR
mdefine_line|#define ECCF_CACHE_ERR  0
DECL|macro|ECCF_TAGLO
mdefine_line|#define ECCF_TAGLO      1
DECL|macro|ECCF_ECC
mdefine_line|#define ECCF_ECC        2
DECL|macro|ECCF_ERROREPC
mdefine_line|#define ECCF_ERROREPC   3
DECL|macro|ECCF_PADDR
mdefine_line|#define ECCF_PADDR      4
DECL|macro|ECCF_SIZE
mdefine_line|#define ECCF_SIZE       (5 * sizeof(long))
macro_line|#endif /* !_LANGUAGE_ASSEMBLY */
macro_line|#if _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * KL_GET_CPUNUM (similar to EV_GET_SPNUM for EVEREST platform) reads&n; * the processor number of the calling processor.  The proc parameters&n; * must be a register.&n; */
DECL|macro|KL_GET_CPUNUM
mdefine_line|#define KL_GET_CPUNUM(proc) &t;&t;&t;&t;&bslash;&n;&t;dli&t;proc, LOCAL_HUB(0); &t;&t;&t;&bslash;&n;&t;ld&t;proc, PI_CPU_NUM(proc)
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
multiline_comment|/*&n; * R10000 status register interrupt bit mask usage for IP27.&n; */
DECL|macro|SRB_SWTIMO
mdefine_line|#define SRB_SWTIMO&t;IE_SW0&t;&t;/* 0x0100 */
DECL|macro|SRB_NET
mdefine_line|#define SRB_NET&t;&t;IE_SW1&t;&t;/* 0x0200 */
DECL|macro|SRB_DEV0
mdefine_line|#define SRB_DEV0&t;IE_IRQ0&t;&t;/* 0x0400 */
DECL|macro|SRB_DEV1
mdefine_line|#define SRB_DEV1&t;IE_IRQ1&t;&t;/* 0x0800 */
DECL|macro|SRB_TIMOCLK
mdefine_line|#define SRB_TIMOCLK&t;IE_IRQ2&t;&t;/* 0x1000 */
DECL|macro|SRB_PROFCLK
mdefine_line|#define SRB_PROFCLK&t;IE_IRQ3&t;&t;/* 0x2000 */
DECL|macro|SRB_ERR
mdefine_line|#define SRB_ERR&t;&t;IE_IRQ4&t;&t;/* 0x4000 */
DECL|macro|SRB_SCHEDCLK
mdefine_line|#define SRB_SCHEDCLK&t;IE_IRQ5&t;&t;/* 0x8000 */
DECL|macro|SR_IBIT_HI
mdefine_line|#define SR_IBIT_HI&t;SRB_DEV0
DECL|macro|SR_IBIT_PROF
mdefine_line|#define SR_IBIT_PROF&t;SRB_PROFCLK
DECL|macro|SRB_SWTIMO_IDX
mdefine_line|#define SRB_SWTIMO_IDX&t;&t;0
DECL|macro|SRB_NET_IDX
mdefine_line|#define SRB_NET_IDX&t;&t;1
DECL|macro|SRB_DEV0_IDX
mdefine_line|#define SRB_DEV0_IDX&t;&t;2
DECL|macro|SRB_DEV1_IDX
mdefine_line|#define SRB_DEV1_IDX&t;&t;3
DECL|macro|SRB_TIMOCLK_IDX
mdefine_line|#define SRB_TIMOCLK_IDX&t;&t;4
DECL|macro|SRB_PROFCLK_IDX
mdefine_line|#define SRB_PROFCLK_IDX&t;&t;5
DECL|macro|SRB_ERR_IDX
mdefine_line|#define SRB_ERR_IDX&t;&t;6
DECL|macro|SRB_SCHEDCLK_IDX
mdefine_line|#define SRB_SCHEDCLK_IDX&t;7
DECL|macro|NUM_CAUSE_INTRS
mdefine_line|#define NUM_CAUSE_INTRS&t;&t;8
DECL|macro|SCACHE_LINESIZE
mdefine_line|#define SCACHE_LINESIZE&t;128
DECL|macro|SCACHE_LINEMASK
mdefine_line|#define SCACHE_LINEMASK&t;(SCACHE_LINESIZE - 1)
macro_line|#include &lt;asm/sn/addrs.h&gt;
DECL|macro|LED_CYCLE_MASK
mdefine_line|#define LED_CYCLE_MASK  0x0f
DECL|macro|LED_CYCLE_SHFT
mdefine_line|#define LED_CYCLE_SHFT  4
DECL|macro|SEND_NMI
mdefine_line|#define SEND_NMI(_nasid, _slice)&t;&bslash;&n;          REMOTE_HUB_S((_nasid),  (PI_NMI_A + ((_slice) * PI_NMI_OFFSET)), 1)
multiline_comment|/* Sanity hazzard ...  Below all the Origin hacks are following.  */
DECL|macro|CPU_RESCHED_A_IRQ
mdefine_line|#define CPU_RESCHED_A_IRQ&t;0
DECL|macro|CPU_RESCHED_B_IRQ
mdefine_line|#define CPU_RESCHED_B_IRQ&t;1
DECL|macro|CPU_CALL_A_IRQ
mdefine_line|#define CPU_CALL_A_IRQ&t;&t;2
DECL|macro|CPU_CALL_B_IRQ
mdefine_line|#define CPU_CALL_B_IRQ&t;&t;3
DECL|macro|BASE_PCI_IRQ
mdefine_line|#define BASE_PCI_IRQ&t;&t;4
DECL|macro|SN00_BRIDGE
mdefine_line|#define SN00_BRIDGE&t;&t;0x9200000008000000
DECL|macro|SN00I_BRIDGE0
mdefine_line|#define SN00I_BRIDGE0&t;&t;0x920000000b000000
DECL|macro|SN00I_BRIDGE1
mdefine_line|#define SN00I_BRIDGE1&t;&t;0x920000000e000000
DECL|macro|SN00I_BRIDGE2
mdefine_line|#define SN00I_BRIDGE2&t;&t;0x920000000f000000
macro_line|#endif /* _ASM_SN_SN0_IP27_H */
eof
