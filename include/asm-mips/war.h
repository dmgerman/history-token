multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2002, 2004 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_WAR_H
DECL|macro|_ASM_WAR_H
mdefine_line|#define _ASM_WAR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Another R4600 erratum.  Due to the lack of errata information the exact&n; * technical details aren&squot;t known.  I&squot;ve experimentally found that disabling&n; * interrupts during indexed I-cache flushes seems to be sufficient to deal&n; * with the issue.&n; *&n; * #define R4600_V1_INDEX_ICACHEOP_WAR 1&n; */
multiline_comment|/*&n; * Pleasures of the R4600 V1.x.  Cite from the IDT R4600 V1.7 errata:&n; *&n; *  18. The CACHE instructions Hit_Writeback_Invalidate_D, Hit_Writeback_D,&n; *      Hit_Invalidate_D and Create_Dirty_Excl_D should only be&n; *      executed if there is no other dcache activity. If the dcache is&n; *      accessed for another instruction immeidately preceding when these&n; *      cache instructions are executing, it is possible that the dcache&n; *      tag match outputs used by these cache instructions will be&n; *      incorrect. These cache instructions should be preceded by at least&n; *      four instructions that are not any kind of load or store&n; *      instruction.&n; *&n; *      This is not allowed:    lw&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              cache       Hit_Writeback_Invalidate_D&n; *&n; *      This is allowed:        lw&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              nop&n; *                              cache       Hit_Writeback_Invalidate_D&n; *&n; * #define R4600_V1_HIT_CACHEOP_WAR 1&n; */
multiline_comment|/*&n; * Writeback and invalidate the primary cache dcache before DMA.&n; *&n; * R4600 v2.0 bug: &quot;The CACHE instructions Hit_Writeback_Inv_D,&n; * Hit_Writeback_D, Hit_Invalidate_D and Create_Dirty_Exclusive_D will only&n; * operate correctly if the internal data cache refill buffer is empty.  These&n; * CACHE instructions should be separated from any potential data cache miss&n; * by a load instruction to an uncached address to empty the response buffer.&quot;&n; * (Revision 2.0 device errata from IDT available on http://www.idt.com/&n; * in .pdf format.)&n; *&n; * #define R4600_V2_HIT_CACHEOP_WAR 1&n; */
multiline_comment|/*&n; * R4600 CPU modules for the Indy come with both V1.7 and V2.0 processors.&n; */
macro_line|#ifdef CONFIG_SGI_IP22
DECL|macro|R4600_V1_INDEX_ICACHEOP_WAR
mdefine_line|#define R4600_V1_INDEX_ICACHEOP_WAR&t;1
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
multiline_comment|/*&n; * Fill buffers not flushed on CACHE instructions&n; * &n; * Hit_Invalidate_I cacheops invalidate an icache line but the refill&n; * for that line can get stale data from the fill buffer instead of&n; * accessing memory if the previous icache miss was also to that line.&n; *&n; * Workaround: generate an icache refill from a different line&n; *&n; * Affects:&n; *  MIPS 4K&t;&t;RTL revision &lt;3.0, PRID revision &lt;4&n; */
macro_line|#if defined(CONFIG_MIPS_MALTA) || defined(CONFIG_MIPS_ATLAS) || &bslash;&n;    defined(CONFIG_MIPS_SEAD)
DECL|macro|MIPS4K_ICACHE_REFILL_WAR
mdefine_line|#define MIPS4K_ICACHE_REFILL_WAR 1
macro_line|#endif
multiline_comment|/*&n; * Missing implicit forced flush of evictions caused by CACHE&n; * instruction&n; *&n; * Evictions caused by a CACHE instructions are not forced on to the&n; * bus. The BIU gives higher priority to fetches than to the data from&n; * the eviction buffer and no collision detection is performed between&n; * fetches and pending data from the eviction buffer.&n; *&n; * Workaround: Execute a SYNC instruction after the cache instruction&n; *&n; * Affects:&n; *   MIPS 5Kc,5Kf&t;RTL revision &lt;2.3, PRID revision &lt;8&n; *   MIPS 20Kc&t;&t;RTL revision &lt;4.0, PRID revision &lt;?&n; */
macro_line|#if defined(CONFIG_MIPS_MALTA) || defined(CONFIG_MIPS_ATLAS) || &bslash;&n;    defined(CONFIG_MIPS_SEAD)
DECL|macro|MIPS_CACHE_SYNC_WAR
mdefine_line|#define MIPS_CACHE_SYNC_WAR 1
macro_line|#endif
multiline_comment|/*&n; * From TX49/H2 manual: &quot;If the instruction (i.e. CACHE) is issued for&n; * the line which this instruction itself exists, the following&n; * operation is not guaranteed.&quot;&n; *&n; * Workaround: do two phase flushing for Index_Invalidate_I&n; */
macro_line|#ifdef CONFIG_CPU_TX49XX
DECL|macro|TX49XX_ICACHE_INDEX_INV_WAR
mdefine_line|#define TX49XX_ICACHE_INDEX_INV_WAR 1
macro_line|#endif
multiline_comment|/*&n; * On the RM9000 there is a problem which makes the CreateDirtyExclusive&n; * cache operation unusable on SMP systems.&n; */
macro_line|#if defined(CONFIG_MOMENCO_JAGUAR_ATX) || defined(CONFIG_PMC_YOSEMITE)
DECL|macro|RM9000_CDEX_SMP_WAR
mdefine_line|#define  RM9000_CDEX_SMP_WAR&t;&t;1
macro_line|#endif
multiline_comment|/*&n; * ON the R10000 upto version 2.6 (not sure about 2.7) there is a bug that&n; * may cause ll / sc and lld / scd sequences to execute non-atomically.&n; */
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|R10000_LLSC_WAR
mdefine_line|#define R10000_LLSC_WAR 1
macro_line|#endif
multiline_comment|/*&n; * Workarounds default to off&n; */
macro_line|#ifndef R4600_V1_INDEX_ICACHEOP_WAR
DECL|macro|R4600_V1_INDEX_ICACHEOP_WAR
mdefine_line|#define R4600_V1_INDEX_ICACHEOP_WAR&t;0
macro_line|#endif
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
macro_line|#ifndef MIPS4K_ICACHE_REFILL_WAR
DECL|macro|MIPS4K_ICACHE_REFILL_WAR
mdefine_line|#define MIPS4K_ICACHE_REFILL_WAR&t;0
macro_line|#endif
macro_line|#ifndef MIPS_CACHE_SYNC_WAR
DECL|macro|MIPS_CACHE_SYNC_WAR
mdefine_line|#define MIPS_CACHE_SYNC_WAR&t;&t;0
macro_line|#endif
macro_line|#ifndef TX49XX_ICACHE_INDEX_INV_WAR
DECL|macro|TX49XX_ICACHE_INDEX_INV_WAR
mdefine_line|#define TX49XX_ICACHE_INDEX_INV_WAR&t;0
macro_line|#endif
macro_line|#ifndef RM9000_CDEX_SMP_WAR
DECL|macro|RM9000_CDEX_SMP_WAR
mdefine_line|#define RM9000_CDEX_SMP_WAR&t;&t;0
macro_line|#endif
macro_line|#ifndef R10000_LLSC_WAR
DECL|macro|R10000_LLSC_WAR
mdefine_line|#define R10000_LLSC_WAR&t;&t;&t;0
macro_line|#endif
macro_line|#endif /* _ASM_WAR_H */
eof
