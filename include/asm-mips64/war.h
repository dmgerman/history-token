multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2002 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_WAR_H
DECL|macro|_ASM_WAR_H
mdefine_line|#define _ASM_WAR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Pleassures of the R4600 V1.x.  Cite from the IDT R4600 V1.7 errata:&n; *&n; *  18. The CACHE instructions Hit_Writeback_Invalidate_D, Hit_Writeback_D,&n; *      Hit_Invalidate_D and Create_Dirty_Excl_D should only be&n; *      executed if there is no other dcache activity. If the dcache is&n; *      accessed for another instruction immeidately preceding when these&n; *      cache instructions are executing, it is possible that the dcache&n; *      tag match outputs used by these cache instructions will be&n; *      incorrect. These cache instructions should be preceded by at least&n; *      four instructions that are not any kind of load or store&n; *      instruction.&n; *&n; *      This is not allowed:    lw&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              cache       Hit_Writeback_Invalidate_D&n; *&n; *      This is allowed:        lw&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              cache       Hit_Writeback_Invalidate_D&n; *&n; * #define R4600_V1_HIT_CACHEOP_WAR 1&n; */
multiline_comment|/*&n; * Writeback and invalidate the primary cache dcache before DMA.&n; *&n; * R4600 v2.0 bug: &quot;The CACHE instructions Hit_Writeback_Inv_D,&n; * Hit_Writeback_D, Hit_Invalidate_D and Create_Dirty_Exclusive_D will only&n; * operate correctly if the internal data cache refill buffer is empty.  These&n; * CACHE instructions should be separated from any potential data cache miss&n; * by a load instruction to an uncached address to empty the response buffer.&quot;&n; * (Revision 2.0 device errata from IDT available on http://www.idt.com/&n; * in .pdf format.)&n; *&n; * #define R4600_V2_HIT_CACHEOP_WAR 1&n; */
multiline_comment|/*&n; * R4600 CPU modules for the Indy come with both V1.7 and V2.0 processors.&n; */
macro_line|#ifdef CONFIG_SGI_IP22
DECL|macro|R4600_V1_HIT_CACHEOP_WAR
mdefine_line|#define R4600_V1_HIT_CACHEOP_WAR&t;1
DECL|macro|R4600_V2_HIT_CACHEOP_WAR
mdefine_line|#define R4600_V2_HIT_CACHEOP_WAR&t;1
macro_line|#endif
multiline_comment|/*&n; * But the RM200C seems to have been shipped only with V2.0 R4600s&n; */
macro_line|#ifdef CONFIG_SNI_RM200_PCI
DECL|macro|R4600_V2_HIT_CACHEOP_WAR
mdefine_line|#define R4600_V2_HIT_CACHEOP_WAR&t;1
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_R5432
multiline_comment|/*&n; * When an interrupt happens on a CP0 register read instruction, CPU may&n; * lock up or read corrupted values of CP0 registers after it enters&n; * the exception handler.&n; *&n; * This workaround makes sure that we read a &quot;safe&quot; CP0 register as the&n; * first thing in the exception handler, which breaks one of the&n; * pre-conditions for this problem.&n; */
DECL|macro|R5432_CP0_INTERRUPT_WAR
mdefine_line|#define&t;R5432_CP0_INTERRUPT_WAR 1
macro_line|#endif
macro_line|#if defined(CONFIG_SB1_PASS_1_WORKAROUNDS) || &bslash;&n;    defined(CONFIG_SB1_PASS_2_WORKAROUNDS)
multiline_comment|/*&n; * Workaround for the Sibyte M3 errata the text of which can be found at&n; *&n; *   http://sibyte.broadcom.com/hw/bcm1250/docs/pass2errata.txt&n; *&n; * This will enable the use of a special TLB refill handler which does a&n; * consistency check on the information in c0_badvaddr and c0_entryhi and&n; * will just return and take the exception again if the information was&n; * found to be inconsistent.&n; */
DECL|macro|BCM1250_M3_WAR
mdefine_line|#define BCM1250_M3_WAR 1
multiline_comment|/* &n; * This is a DUART workaround related to glitches around register accesses&n; */
DECL|macro|SIBYTE_1956_WAR
mdefine_line|#define SIBYTE_1956_WAR 1
macro_line|#endif
multiline_comment|/*&n; * Workarounds default to off&n; */
macro_line|#ifndef R4600_V1_HIT_CACHEOP_WAR
DECL|macro|R4600_V1_HIT_CACHEOP_WAR
mdefine_line|#define R4600_V1_HIT_CACHEOP_WAR&t;0
macro_line|#endif
macro_line|#ifndef R4600_V2_HIT_CACHEOP_WAR
DECL|macro|R4600_V2_HIT_CACHEOP_WAR
mdefine_line|#define R4600_V2_HIT_CACHEOP_WAR&t;0
macro_line|#endif
macro_line|#ifndef R5432_CP0_INTERRUPT_WAR
DECL|macro|R5432_CP0_INTERRUPT_WAR
mdefine_line|#define R5432_CP0_INTERRUPT_WAR&t;&t;0
macro_line|#endif
macro_line|#ifndef BCM1250_M3_WAR
DECL|macro|BCM1250_M3_WAR
mdefine_line|#define BCM1250_M3_WAR&t;&t;&t;0
macro_line|#endif
macro_line|#ifndef SIBYTE_1956_WAR
DECL|macro|SIBYTE_1956_WAR
mdefine_line|#define SIBYTE_1956_WAR&t;&t;&t;0
macro_line|#endif
macro_line|#endif /* _ASM_WAR_H */
eof
