multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 2000, 2001 by Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Modified for further R[236]000 support by Paul M. Antoine, 1996.&n; * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; * Copyright (C) 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef _ASM_MIPSREGS_H
DECL|macro|_ASM_MIPSREGS_H
mdefine_line|#define _ASM_MIPSREGS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/hazards.h&gt;
multiline_comment|/*&n; * The following macros are especially useful for __asm__&n; * inline assembler.&n; */
macro_line|#ifndef __STR
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#endif
macro_line|#ifndef STR
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#endif
multiline_comment|/*&n; *  Configure language&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_ULCAST_
mdefine_line|#define _ULCAST_
macro_line|#else
DECL|macro|_ULCAST_
mdefine_line|#define _ULCAST_ (unsigned long)
macro_line|#endif
multiline_comment|/*&n; * Coprocessor 0 register names&n; */
DECL|macro|CP0_INDEX
mdefine_line|#define CP0_INDEX $0
DECL|macro|CP0_RANDOM
mdefine_line|#define CP0_RANDOM $1
DECL|macro|CP0_ENTRYLO0
mdefine_line|#define CP0_ENTRYLO0 $2
DECL|macro|CP0_ENTRYLO1
mdefine_line|#define CP0_ENTRYLO1 $3
DECL|macro|CP0_CONF
mdefine_line|#define CP0_CONF $3
DECL|macro|CP0_CONTEXT
mdefine_line|#define CP0_CONTEXT $4
DECL|macro|CP0_PAGEMASK
mdefine_line|#define CP0_PAGEMASK $5
DECL|macro|CP0_WIRED
mdefine_line|#define CP0_WIRED $6
DECL|macro|CP0_INFO
mdefine_line|#define CP0_INFO $7
DECL|macro|CP0_BADVADDR
mdefine_line|#define CP0_BADVADDR $8
DECL|macro|CP0_COUNT
mdefine_line|#define CP0_COUNT $9
DECL|macro|CP0_ENTRYHI
mdefine_line|#define CP0_ENTRYHI $10
DECL|macro|CP0_COMPARE
mdefine_line|#define CP0_COMPARE $11
DECL|macro|CP0_STATUS
mdefine_line|#define CP0_STATUS $12
DECL|macro|CP0_CAUSE
mdefine_line|#define CP0_CAUSE $13
DECL|macro|CP0_EPC
mdefine_line|#define CP0_EPC $14
DECL|macro|CP0_PRID
mdefine_line|#define CP0_PRID $15
DECL|macro|CP0_CONFIG
mdefine_line|#define CP0_CONFIG $16
DECL|macro|CP0_LLADDR
mdefine_line|#define CP0_LLADDR $17
DECL|macro|CP0_WATCHLO
mdefine_line|#define CP0_WATCHLO $18
DECL|macro|CP0_WATCHHI
mdefine_line|#define CP0_WATCHHI $19
DECL|macro|CP0_XCONTEXT
mdefine_line|#define CP0_XCONTEXT $20
DECL|macro|CP0_FRAMEMASK
mdefine_line|#define CP0_FRAMEMASK $21
DECL|macro|CP0_DIAGNOSTIC
mdefine_line|#define CP0_DIAGNOSTIC $22
DECL|macro|CP0_DEBUG
mdefine_line|#define CP0_DEBUG $23
DECL|macro|CP0_DEPC
mdefine_line|#define CP0_DEPC $24
DECL|macro|CP0_PERFORMANCE
mdefine_line|#define CP0_PERFORMANCE $25
DECL|macro|CP0_ECC
mdefine_line|#define CP0_ECC $26
DECL|macro|CP0_CACHEERR
mdefine_line|#define CP0_CACHEERR $27
DECL|macro|CP0_TAGLO
mdefine_line|#define CP0_TAGLO $28
DECL|macro|CP0_TAGHI
mdefine_line|#define CP0_TAGHI $29
DECL|macro|CP0_ERROREPC
mdefine_line|#define CP0_ERROREPC $30
DECL|macro|CP0_DESAVE
mdefine_line|#define CP0_DESAVE $31
multiline_comment|/*&n; * R4640/R4650 cp0 register names.  These registers are listed&n; * here only for completeness; without MMU these CPUs are not useable&n; * by Linux.  A future ELKS port might take make Linux run on them&n; * though ...&n; */
DECL|macro|CP0_IBASE
mdefine_line|#define CP0_IBASE $0
DECL|macro|CP0_IBOUND
mdefine_line|#define CP0_IBOUND $1
DECL|macro|CP0_DBASE
mdefine_line|#define CP0_DBASE $2
DECL|macro|CP0_DBOUND
mdefine_line|#define CP0_DBOUND $3
DECL|macro|CP0_CALG
mdefine_line|#define CP0_CALG $17
DECL|macro|CP0_IWATCH
mdefine_line|#define CP0_IWATCH $18
DECL|macro|CP0_DWATCH
mdefine_line|#define CP0_DWATCH $19
multiline_comment|/*&n; * Coprocessor 0 Set 1 register names&n; */
DECL|macro|CP0_S1_DERRADDR0
mdefine_line|#define CP0_S1_DERRADDR0  $26
DECL|macro|CP0_S1_DERRADDR1
mdefine_line|#define CP0_S1_DERRADDR1  $27
DECL|macro|CP0_S1_INTCONTROL
mdefine_line|#define CP0_S1_INTCONTROL $20
multiline_comment|/*&n; *  TX39 Series&n; */
DECL|macro|CP0_TX39_CACHE
mdefine_line|#define CP0_TX39_CACHE&t;$7
multiline_comment|/*&n; * Coprocessor 1 (FPU) register names&n; */
DECL|macro|CP1_REVISION
mdefine_line|#define CP1_REVISION   $0
DECL|macro|CP1_STATUS
mdefine_line|#define CP1_STATUS     $31
multiline_comment|/*&n; * FPU Status Register Values&n; */
multiline_comment|/*&n; * Status Register Values&n; */
DECL|macro|FPU_CSR_FLUSH
mdefine_line|#define FPU_CSR_FLUSH   0x01000000      /* flush denormalised results to 0 */
DECL|macro|FPU_CSR_COND
mdefine_line|#define FPU_CSR_COND    0x00800000      /* $fcc0 */
DECL|macro|FPU_CSR_COND0
mdefine_line|#define FPU_CSR_COND0   0x00800000      /* $fcc0 */
DECL|macro|FPU_CSR_COND1
mdefine_line|#define FPU_CSR_COND1   0x02000000      /* $fcc1 */
DECL|macro|FPU_CSR_COND2
mdefine_line|#define FPU_CSR_COND2   0x04000000      /* $fcc2 */
DECL|macro|FPU_CSR_COND3
mdefine_line|#define FPU_CSR_COND3   0x08000000      /* $fcc3 */
DECL|macro|FPU_CSR_COND4
mdefine_line|#define FPU_CSR_COND4   0x10000000      /* $fcc4 */
DECL|macro|FPU_CSR_COND5
mdefine_line|#define FPU_CSR_COND5   0x20000000      /* $fcc5 */
DECL|macro|FPU_CSR_COND6
mdefine_line|#define FPU_CSR_COND6   0x40000000      /* $fcc6 */
DECL|macro|FPU_CSR_COND7
mdefine_line|#define FPU_CSR_COND7   0x80000000      /* $fcc7 */
multiline_comment|/*&n; * X the exception cause indicator&n; * E the exception enable&n; * S the sticky/flag bit&n;*/
DECL|macro|FPU_CSR_ALL_X
mdefine_line|#define FPU_CSR_ALL_X   0x0003f000
DECL|macro|FPU_CSR_UNI_X
mdefine_line|#define FPU_CSR_UNI_X   0x00020000
DECL|macro|FPU_CSR_INV_X
mdefine_line|#define FPU_CSR_INV_X   0x00010000
DECL|macro|FPU_CSR_DIV_X
mdefine_line|#define FPU_CSR_DIV_X   0x00008000
DECL|macro|FPU_CSR_OVF_X
mdefine_line|#define FPU_CSR_OVF_X   0x00004000
DECL|macro|FPU_CSR_UDF_X
mdefine_line|#define FPU_CSR_UDF_X   0x00002000
DECL|macro|FPU_CSR_INE_X
mdefine_line|#define FPU_CSR_INE_X   0x00001000
DECL|macro|FPU_CSR_ALL_E
mdefine_line|#define FPU_CSR_ALL_E   0x00000f80
DECL|macro|FPU_CSR_INV_E
mdefine_line|#define FPU_CSR_INV_E   0x00000800
DECL|macro|FPU_CSR_DIV_E
mdefine_line|#define FPU_CSR_DIV_E   0x00000400
DECL|macro|FPU_CSR_OVF_E
mdefine_line|#define FPU_CSR_OVF_E   0x00000200
DECL|macro|FPU_CSR_UDF_E
mdefine_line|#define FPU_CSR_UDF_E   0x00000100
DECL|macro|FPU_CSR_INE_E
mdefine_line|#define FPU_CSR_INE_E   0x00000080
DECL|macro|FPU_CSR_ALL_S
mdefine_line|#define FPU_CSR_ALL_S   0x0000007c
DECL|macro|FPU_CSR_INV_S
mdefine_line|#define FPU_CSR_INV_S   0x00000040
DECL|macro|FPU_CSR_DIV_S
mdefine_line|#define FPU_CSR_DIV_S   0x00000020
DECL|macro|FPU_CSR_OVF_S
mdefine_line|#define FPU_CSR_OVF_S   0x00000010
DECL|macro|FPU_CSR_UDF_S
mdefine_line|#define FPU_CSR_UDF_S   0x00000008
DECL|macro|FPU_CSR_INE_S
mdefine_line|#define FPU_CSR_INE_S   0x00000004
multiline_comment|/* rounding mode */
DECL|macro|FPU_CSR_RN
mdefine_line|#define FPU_CSR_RN      0x0     /* nearest */
DECL|macro|FPU_CSR_RZ
mdefine_line|#define FPU_CSR_RZ      0x1     /* towards zero */
DECL|macro|FPU_CSR_RU
mdefine_line|#define FPU_CSR_RU      0x2     /* towards +Infinity */
DECL|macro|FPU_CSR_RD
mdefine_line|#define FPU_CSR_RD      0x3     /* towards -Infinity */
multiline_comment|/*&n; * Values for PageMask register&n; */
macro_line|#ifdef CONFIG_CPU_VR41XX
multiline_comment|/* Why doesn&squot;t stupidity hurt ... */
DECL|macro|PM_1K
mdefine_line|#define PM_1K&t;&t;0x00000000
DECL|macro|PM_4K
mdefine_line|#define PM_4K&t;&t;0x00001800
DECL|macro|PM_16K
mdefine_line|#define PM_16K&t;&t;0x00007800
DECL|macro|PM_64K
mdefine_line|#define PM_64K&t;&t;0x0001f800
DECL|macro|PM_256K
mdefine_line|#define PM_256K&t;&t;0x0007f800
macro_line|#else
DECL|macro|PM_4K
mdefine_line|#define PM_4K&t;&t;0x00000000
DECL|macro|PM_16K
mdefine_line|#define PM_16K&t;&t;0x00006000
DECL|macro|PM_64K
mdefine_line|#define PM_64K&t;&t;0x0001e000
DECL|macro|PM_256K
mdefine_line|#define PM_256K&t;&t;0x0007e000
DECL|macro|PM_1M
mdefine_line|#define PM_1M&t;&t;0x001fe000
DECL|macro|PM_4M
mdefine_line|#define PM_4M&t;&t;0x007fe000
DECL|macro|PM_16M
mdefine_line|#define PM_16M&t;&t;0x01ffe000
DECL|macro|PM_64M
mdefine_line|#define PM_64M&t;&t;0x07ffe000
DECL|macro|PM_256M
mdefine_line|#define PM_256M&t;&t;0x1fffe000
macro_line|#endif
multiline_comment|/*&n; * Default page size for a given kernel configuration&n; */
macro_line|#ifdef CONFIG_PAGE_SIZE_4KB
DECL|macro|PM_DEFAULT_MASK
mdefine_line|#define PM_DEFAULT_MASK&t;PM_4K
macro_line|#elif defined(CONFIG_PAGE_SIZE_16KB)
DECL|macro|PM_DEFAULT_MASK
mdefine_line|#define PM_DEFAULT_MASK&t;PM_16K
macro_line|#elif defined(CONFIG_PAGE_SIZE_64KB)
DECL|macro|PM_DEFAULT_MASK
mdefine_line|#define PM_DEFAULT_MASK&t;PM_64K
macro_line|#else
macro_line|#error Bad page size configuration!
macro_line|#endif
multiline_comment|/*&n; * Values used for computation of new tlb entries&n; */
DECL|macro|PL_4K
mdefine_line|#define PL_4K&t;&t;12
DECL|macro|PL_16K
mdefine_line|#define PL_16K&t;&t;14
DECL|macro|PL_64K
mdefine_line|#define PL_64K&t;&t;16
DECL|macro|PL_256K
mdefine_line|#define PL_256K&t;&t;18
DECL|macro|PL_1M
mdefine_line|#define PL_1M&t;&t;20
DECL|macro|PL_4M
mdefine_line|#define PL_4M&t;&t;22
DECL|macro|PL_16M
mdefine_line|#define PL_16M&t;&t;24
DECL|macro|PL_64M
mdefine_line|#define PL_64M&t;&t;26
DECL|macro|PL_256M
mdefine_line|#define PL_256M&t;&t;28
multiline_comment|/*&n; * R4x00 interrupt enable / cause bits&n; */
DECL|macro|IE_SW0
mdefine_line|#define IE_SW0          (_ULCAST_(1) &lt;&lt;  8)
DECL|macro|IE_SW1
mdefine_line|#define IE_SW1          (_ULCAST_(1) &lt;&lt;  9)
DECL|macro|IE_IRQ0
mdefine_line|#define IE_IRQ0         (_ULCAST_(1) &lt;&lt; 10)
DECL|macro|IE_IRQ1
mdefine_line|#define IE_IRQ1         (_ULCAST_(1) &lt;&lt; 11)
DECL|macro|IE_IRQ2
mdefine_line|#define IE_IRQ2         (_ULCAST_(1) &lt;&lt; 12)
DECL|macro|IE_IRQ3
mdefine_line|#define IE_IRQ3         (_ULCAST_(1) &lt;&lt; 13)
DECL|macro|IE_IRQ4
mdefine_line|#define IE_IRQ4         (_ULCAST_(1) &lt;&lt; 14)
DECL|macro|IE_IRQ5
mdefine_line|#define IE_IRQ5         (_ULCAST_(1) &lt;&lt; 15)
multiline_comment|/*&n; * R4x00 interrupt cause bits&n; */
DECL|macro|C_SW0
mdefine_line|#define C_SW0           (_ULCAST_(1) &lt;&lt;  8)
DECL|macro|C_SW1
mdefine_line|#define C_SW1           (_ULCAST_(1) &lt;&lt;  9)
DECL|macro|C_IRQ0
mdefine_line|#define C_IRQ0          (_ULCAST_(1) &lt;&lt; 10)
DECL|macro|C_IRQ1
mdefine_line|#define C_IRQ1          (_ULCAST_(1) &lt;&lt; 11)
DECL|macro|C_IRQ2
mdefine_line|#define C_IRQ2          (_ULCAST_(1) &lt;&lt; 12)
DECL|macro|C_IRQ3
mdefine_line|#define C_IRQ3          (_ULCAST_(1) &lt;&lt; 13)
DECL|macro|C_IRQ4
mdefine_line|#define C_IRQ4          (_ULCAST_(1) &lt;&lt; 14)
DECL|macro|C_IRQ5
mdefine_line|#define C_IRQ5          (_ULCAST_(1) &lt;&lt; 15)
multiline_comment|/*&n; * Bitfields in the R4xx0 cp0 status register&n; */
DECL|macro|ST0_IE
mdefine_line|#define ST0_IE&t;&t;&t;0x00000001
DECL|macro|ST0_EXL
mdefine_line|#define ST0_EXL&t;&t;&t;0x00000002
DECL|macro|ST0_ERL
mdefine_line|#define ST0_ERL&t;&t;&t;0x00000004
DECL|macro|ST0_KSU
mdefine_line|#define ST0_KSU&t;&t;&t;0x00000018
DECL|macro|KSU_USER
macro_line|#  define KSU_USER&t;&t;0x00000010
DECL|macro|KSU_SUPERVISOR
macro_line|#  define KSU_SUPERVISOR&t;0x00000008
DECL|macro|KSU_KERNEL
macro_line|#  define KSU_KERNEL&t;&t;0x00000000
DECL|macro|ST0_UX
mdefine_line|#define ST0_UX&t;&t;&t;0x00000020
DECL|macro|ST0_SX
mdefine_line|#define ST0_SX&t;&t;&t;0x00000040
DECL|macro|ST0_KX
mdefine_line|#define ST0_KX &t;&t;&t;0x00000080
DECL|macro|ST0_DE
mdefine_line|#define ST0_DE&t;&t;&t;0x00010000
DECL|macro|ST0_CE
mdefine_line|#define ST0_CE&t;&t;&t;0x00020000
multiline_comment|/*&n; * Setting c0_status.co enables Hit_Writeback and Hit_Writeback_Invalidate&n; * cacheops in userspace.  This bit exists only on RM7000 and RM9000&n; * processors.&n; */
DECL|macro|ST0_CO
mdefine_line|#define ST0_CO&t;&t;&t;0x08000000
multiline_comment|/*&n; * Bitfields in the R[23]000 cp0 status register.&n; */
DECL|macro|ST0_IEC
mdefine_line|#define ST0_IEC                 0x00000001
DECL|macro|ST0_KUC
mdefine_line|#define ST0_KUC&t;&t;&t;0x00000002
DECL|macro|ST0_IEP
mdefine_line|#define ST0_IEP&t;&t;&t;0x00000004
DECL|macro|ST0_KUP
mdefine_line|#define ST0_KUP&t;&t;&t;0x00000008
DECL|macro|ST0_IEO
mdefine_line|#define ST0_IEO&t;&t;&t;0x00000010
DECL|macro|ST0_KUO
mdefine_line|#define ST0_KUO&t;&t;&t;0x00000020
multiline_comment|/* bits 6 &amp; 7 are reserved on R[23]000 */
DECL|macro|ST0_ISC
mdefine_line|#define ST0_ISC&t;&t;&t;0x00010000
DECL|macro|ST0_SWC
mdefine_line|#define ST0_SWC&t;&t;&t;0x00020000
DECL|macro|ST0_CM
mdefine_line|#define ST0_CM&t;&t;&t;0x00080000
multiline_comment|/*&n; * Bits specific to the R4640/R4650&n; */
DECL|macro|ST0_UM
mdefine_line|#define ST0_UM&t;&t;&t;(_ULCAST_(1) &lt;&lt;  4)
DECL|macro|ST0_IL
mdefine_line|#define ST0_IL&t;&t;&t;(_ULCAST_(1) &lt;&lt; 23)
DECL|macro|ST0_DL
mdefine_line|#define ST0_DL&t;&t;&t;(_ULCAST_(1) &lt;&lt; 24)
multiline_comment|/*&n; * Bitfields in the TX39 family CP0 Configuration Register 3&n; */
DECL|macro|TX39_CONF_ICS_SHIFT
mdefine_line|#define TX39_CONF_ICS_SHIFT&t;19
DECL|macro|TX39_CONF_ICS_MASK
mdefine_line|#define TX39_CONF_ICS_MASK&t;0x00380000
DECL|macro|TX39_CONF_ICS_1KB
mdefine_line|#define TX39_CONF_ICS_1KB &t;0x00000000
DECL|macro|TX39_CONF_ICS_2KB
mdefine_line|#define TX39_CONF_ICS_2KB &t;0x00080000
DECL|macro|TX39_CONF_ICS_4KB
mdefine_line|#define TX39_CONF_ICS_4KB &t;0x00100000
DECL|macro|TX39_CONF_ICS_8KB
mdefine_line|#define TX39_CONF_ICS_8KB &t;0x00180000
DECL|macro|TX39_CONF_ICS_16KB
mdefine_line|#define TX39_CONF_ICS_16KB &t;0x00200000
DECL|macro|TX39_CONF_DCS_SHIFT
mdefine_line|#define TX39_CONF_DCS_SHIFT&t;16
DECL|macro|TX39_CONF_DCS_MASK
mdefine_line|#define TX39_CONF_DCS_MASK&t;0x00070000
DECL|macro|TX39_CONF_DCS_1KB
mdefine_line|#define TX39_CONF_DCS_1KB &t;0x00000000
DECL|macro|TX39_CONF_DCS_2KB
mdefine_line|#define TX39_CONF_DCS_2KB &t;0x00010000
DECL|macro|TX39_CONF_DCS_4KB
mdefine_line|#define TX39_CONF_DCS_4KB &t;0x00020000
DECL|macro|TX39_CONF_DCS_8KB
mdefine_line|#define TX39_CONF_DCS_8KB &t;0x00030000
DECL|macro|TX39_CONF_DCS_16KB
mdefine_line|#define TX39_CONF_DCS_16KB &t;0x00040000
DECL|macro|TX39_CONF_CWFON
mdefine_line|#define TX39_CONF_CWFON &t;0x00004000
DECL|macro|TX39_CONF_WBON
mdefine_line|#define TX39_CONF_WBON  &t;0x00002000
DECL|macro|TX39_CONF_RF_SHIFT
mdefine_line|#define TX39_CONF_RF_SHIFT&t;10
DECL|macro|TX39_CONF_RF_MASK
mdefine_line|#define TX39_CONF_RF_MASK&t;0x00000c00
DECL|macro|TX39_CONF_DOZE
mdefine_line|#define TX39_CONF_DOZE&t;&t;0x00000200
DECL|macro|TX39_CONF_HALT
mdefine_line|#define TX39_CONF_HALT&t;&t;0x00000100
DECL|macro|TX39_CONF_LOCK
mdefine_line|#define TX39_CONF_LOCK&t;&t;0x00000080
DECL|macro|TX39_CONF_ICE
mdefine_line|#define TX39_CONF_ICE&t;&t;0x00000020
DECL|macro|TX39_CONF_DCE
mdefine_line|#define TX39_CONF_DCE&t;&t;0x00000010
DECL|macro|TX39_CONF_IRSIZE_SHIFT
mdefine_line|#define TX39_CONF_IRSIZE_SHIFT&t;2
DECL|macro|TX39_CONF_IRSIZE_MASK
mdefine_line|#define TX39_CONF_IRSIZE_MASK&t;0x0000000c
DECL|macro|TX39_CONF_DRSIZE_SHIFT
mdefine_line|#define TX39_CONF_DRSIZE_SHIFT&t;0
DECL|macro|TX39_CONF_DRSIZE_MASK
mdefine_line|#define TX39_CONF_DRSIZE_MASK&t;0x00000003
multiline_comment|/*&n; * Status register bits available in all MIPS CPUs.&n; */
DECL|macro|ST0_IM
mdefine_line|#define ST0_IM&t;&t;&t;0x0000ff00
DECL|macro|STATUSB_IP0
mdefine_line|#define  STATUSB_IP0&t;&t;8
DECL|macro|STATUSF_IP0
mdefine_line|#define  STATUSF_IP0&t;&t;(_ULCAST_(1) &lt;&lt;  8)
DECL|macro|STATUSB_IP1
mdefine_line|#define  STATUSB_IP1&t;&t;9
DECL|macro|STATUSF_IP1
mdefine_line|#define  STATUSF_IP1&t;&t;(_ULCAST_(1) &lt;&lt;  9)
DECL|macro|STATUSB_IP2
mdefine_line|#define  STATUSB_IP2&t;&t;10
DECL|macro|STATUSF_IP2
mdefine_line|#define  STATUSF_IP2&t;&t;(_ULCAST_(1) &lt;&lt; 10)
DECL|macro|STATUSB_IP3
mdefine_line|#define  STATUSB_IP3&t;&t;11
DECL|macro|STATUSF_IP3
mdefine_line|#define  STATUSF_IP3&t;&t;(_ULCAST_(1) &lt;&lt; 11)
DECL|macro|STATUSB_IP4
mdefine_line|#define  STATUSB_IP4&t;&t;12
DECL|macro|STATUSF_IP4
mdefine_line|#define  STATUSF_IP4&t;&t;(_ULCAST_(1) &lt;&lt; 12)
DECL|macro|STATUSB_IP5
mdefine_line|#define  STATUSB_IP5&t;&t;13
DECL|macro|STATUSF_IP5
mdefine_line|#define  STATUSF_IP5&t;&t;(_ULCAST_(1) &lt;&lt; 13)
DECL|macro|STATUSB_IP6
mdefine_line|#define  STATUSB_IP6&t;&t;14
DECL|macro|STATUSF_IP6
mdefine_line|#define  STATUSF_IP6&t;&t;(_ULCAST_(1) &lt;&lt; 14)
DECL|macro|STATUSB_IP7
mdefine_line|#define  STATUSB_IP7&t;&t;15
DECL|macro|STATUSF_IP7
mdefine_line|#define  STATUSF_IP7&t;&t;(_ULCAST_(1) &lt;&lt; 15)
DECL|macro|STATUSB_IP8
mdefine_line|#define  STATUSB_IP8&t;&t;0
DECL|macro|STATUSF_IP8
mdefine_line|#define  STATUSF_IP8&t;&t;(_ULCAST_(1) &lt;&lt;  0)
DECL|macro|STATUSB_IP9
mdefine_line|#define  STATUSB_IP9&t;&t;1
DECL|macro|STATUSF_IP9
mdefine_line|#define  STATUSF_IP9&t;&t;(_ULCAST_(1) &lt;&lt;  1)
DECL|macro|STATUSB_IP10
mdefine_line|#define  STATUSB_IP10&t;&t;2
DECL|macro|STATUSF_IP10
mdefine_line|#define  STATUSF_IP10&t;&t;(_ULCAST_(1) &lt;&lt;  2)
DECL|macro|STATUSB_IP11
mdefine_line|#define  STATUSB_IP11&t;&t;3
DECL|macro|STATUSF_IP11
mdefine_line|#define  STATUSF_IP11&t;&t;(_ULCAST_(1) &lt;&lt;  3)
DECL|macro|STATUSB_IP12
mdefine_line|#define  STATUSB_IP12&t;&t;4
DECL|macro|STATUSF_IP12
mdefine_line|#define  STATUSF_IP12&t;&t;(_ULCAST_(1) &lt;&lt;  4)
DECL|macro|STATUSB_IP13
mdefine_line|#define  STATUSB_IP13&t;&t;5
DECL|macro|STATUSF_IP13
mdefine_line|#define  STATUSF_IP13&t;&t;(_ULCAST_(1) &lt;&lt;  5)
DECL|macro|STATUSB_IP14
mdefine_line|#define  STATUSB_IP14&t;&t;6
DECL|macro|STATUSF_IP14
mdefine_line|#define  STATUSF_IP14&t;&t;(_ULCAST_(1) &lt;&lt;  6)
DECL|macro|STATUSB_IP15
mdefine_line|#define  STATUSB_IP15&t;&t;7
DECL|macro|STATUSF_IP15
mdefine_line|#define  STATUSF_IP15&t;&t;(_ULCAST_(1) &lt;&lt;  7)
DECL|macro|ST0_CH
mdefine_line|#define ST0_CH&t;&t;&t;0x00040000
DECL|macro|ST0_SR
mdefine_line|#define ST0_SR&t;&t;&t;0x00100000
DECL|macro|ST0_TS
mdefine_line|#define ST0_TS&t;&t;&t;0x00200000
DECL|macro|ST0_BEV
mdefine_line|#define ST0_BEV&t;&t;&t;0x00400000
DECL|macro|ST0_RE
mdefine_line|#define ST0_RE&t;&t;&t;0x02000000
DECL|macro|ST0_FR
mdefine_line|#define ST0_FR&t;&t;&t;0x04000000
DECL|macro|ST0_CU
mdefine_line|#define ST0_CU&t;&t;&t;0xf0000000
DECL|macro|ST0_CU0
mdefine_line|#define ST0_CU0&t;&t;&t;0x10000000
DECL|macro|ST0_CU1
mdefine_line|#define ST0_CU1&t;&t;&t;0x20000000
DECL|macro|ST0_CU2
mdefine_line|#define ST0_CU2&t;&t;&t;0x40000000
DECL|macro|ST0_CU3
mdefine_line|#define ST0_CU3&t;&t;&t;0x80000000
DECL|macro|ST0_XX
mdefine_line|#define ST0_XX&t;&t;&t;0x80000000&t;/* MIPS IV naming */
multiline_comment|/*&n; * Bitfields and bit numbers in the coprocessor 0 cause register.&n; *&n; * Refer to your MIPS R4xx0 manual, chapter 5 for explanation.&n; */
DECL|macro|CAUSEB_EXCCODE
mdefine_line|#define  CAUSEB_EXCCODE&t;&t;2
DECL|macro|CAUSEF_EXCCODE
mdefine_line|#define  CAUSEF_EXCCODE&t;&t;(_ULCAST_(31)  &lt;&lt;  2)
DECL|macro|CAUSEB_IP
mdefine_line|#define  CAUSEB_IP&t;&t;8
DECL|macro|CAUSEF_IP
mdefine_line|#define  CAUSEF_IP&t;&t;(_ULCAST_(255) &lt;&lt;  8)
DECL|macro|CAUSEB_IP0
mdefine_line|#define  CAUSEB_IP0&t;&t;8
DECL|macro|CAUSEF_IP0
mdefine_line|#define  CAUSEF_IP0&t;&t;(_ULCAST_(1)   &lt;&lt;  8)
DECL|macro|CAUSEB_IP1
mdefine_line|#define  CAUSEB_IP1&t;&t;9
DECL|macro|CAUSEF_IP1
mdefine_line|#define  CAUSEF_IP1&t;&t;(_ULCAST_(1)   &lt;&lt;  9)
DECL|macro|CAUSEB_IP2
mdefine_line|#define  CAUSEB_IP2&t;&t;10
DECL|macro|CAUSEF_IP2
mdefine_line|#define  CAUSEF_IP2&t;&t;(_ULCAST_(1)   &lt;&lt; 10)
DECL|macro|CAUSEB_IP3
mdefine_line|#define  CAUSEB_IP3&t;&t;11
DECL|macro|CAUSEF_IP3
mdefine_line|#define  CAUSEF_IP3&t;&t;(_ULCAST_(1)   &lt;&lt; 11)
DECL|macro|CAUSEB_IP4
mdefine_line|#define  CAUSEB_IP4&t;&t;12
DECL|macro|CAUSEF_IP4
mdefine_line|#define  CAUSEF_IP4&t;&t;(_ULCAST_(1)   &lt;&lt; 12)
DECL|macro|CAUSEB_IP5
mdefine_line|#define  CAUSEB_IP5&t;&t;13
DECL|macro|CAUSEF_IP5
mdefine_line|#define  CAUSEF_IP5&t;&t;(_ULCAST_(1)   &lt;&lt; 13)
DECL|macro|CAUSEB_IP6
mdefine_line|#define  CAUSEB_IP6&t;&t;14
DECL|macro|CAUSEF_IP6
mdefine_line|#define  CAUSEF_IP6&t;&t;(_ULCAST_(1)   &lt;&lt; 14)
DECL|macro|CAUSEB_IP7
mdefine_line|#define  CAUSEB_IP7&t;&t;15
DECL|macro|CAUSEF_IP7
mdefine_line|#define  CAUSEF_IP7&t;&t;(_ULCAST_(1)   &lt;&lt; 15)
DECL|macro|CAUSEB_IV
mdefine_line|#define  CAUSEB_IV&t;&t;23
DECL|macro|CAUSEF_IV
mdefine_line|#define  CAUSEF_IV&t;&t;(_ULCAST_(1)   &lt;&lt; 23)
DECL|macro|CAUSEB_CE
mdefine_line|#define  CAUSEB_CE&t;&t;28
DECL|macro|CAUSEF_CE
mdefine_line|#define  CAUSEF_CE&t;&t;(_ULCAST_(3)   &lt;&lt; 28)
DECL|macro|CAUSEB_BD
mdefine_line|#define  CAUSEB_BD&t;&t;31
DECL|macro|CAUSEF_BD
mdefine_line|#define  CAUSEF_BD&t;&t;(_ULCAST_(1)   &lt;&lt; 31)
multiline_comment|/*&n; * Bits in the coprocessor 0 config register.&n; */
multiline_comment|/* Generic bits.  */
DECL|macro|CONF_CM_CACHABLE_NO_WA
mdefine_line|#define CONF_CM_CACHABLE_NO_WA&t;&t;0
DECL|macro|CONF_CM_CACHABLE_WA
mdefine_line|#define CONF_CM_CACHABLE_WA&t;&t;1
DECL|macro|CONF_CM_UNCACHED
mdefine_line|#define CONF_CM_UNCACHED&t;&t;2
DECL|macro|CONF_CM_CACHABLE_NONCOHERENT
mdefine_line|#define CONF_CM_CACHABLE_NONCOHERENT&t;3
DECL|macro|CONF_CM_CACHABLE_CE
mdefine_line|#define CONF_CM_CACHABLE_CE&t;&t;4
DECL|macro|CONF_CM_CACHABLE_COW
mdefine_line|#define CONF_CM_CACHABLE_COW&t;&t;5
DECL|macro|CONF_CM_CACHABLE_CUW
mdefine_line|#define CONF_CM_CACHABLE_CUW&t;&t;6
DECL|macro|CONF_CM_CACHABLE_ACCELERATED
mdefine_line|#define CONF_CM_CACHABLE_ACCELERATED&t;7
DECL|macro|CONF_CM_CMASK
mdefine_line|#define CONF_CM_CMASK&t;&t;&t;7
DECL|macro|CONF_BE
mdefine_line|#define CONF_BE&t;&t;&t;(_ULCAST_(1) &lt;&lt; 15)
multiline_comment|/* Bits common to various processors.  */
DECL|macro|CONF_CU
mdefine_line|#define CONF_CU&t;&t;&t;(_ULCAST_(1) &lt;&lt;  3)
DECL|macro|CONF_DB
mdefine_line|#define CONF_DB&t;&t;&t;(_ULCAST_(1) &lt;&lt;  4)
DECL|macro|CONF_IB
mdefine_line|#define CONF_IB&t;&t;&t;(_ULCAST_(1) &lt;&lt;  5)
DECL|macro|CONF_DC
mdefine_line|#define CONF_DC&t;&t;&t;(_ULCAST_(7) &lt;&lt;  6)
DECL|macro|CONF_IC
mdefine_line|#define CONF_IC&t;&t;&t;(_ULCAST_(7) &lt;&lt;  9)
DECL|macro|CONF_EB
mdefine_line|#define CONF_EB&t;&t;&t;(_ULCAST_(1) &lt;&lt; 13)
DECL|macro|CONF_EM
mdefine_line|#define CONF_EM&t;&t;&t;(_ULCAST_(1) &lt;&lt; 14)
DECL|macro|CONF_SM
mdefine_line|#define CONF_SM&t;&t;&t;(_ULCAST_(1) &lt;&lt; 16)
DECL|macro|CONF_SC
mdefine_line|#define CONF_SC&t;&t;&t;(_ULCAST_(1) &lt;&lt; 17)
DECL|macro|CONF_EW
mdefine_line|#define CONF_EW&t;&t;&t;(_ULCAST_(3) &lt;&lt; 18)
DECL|macro|CONF_EP
mdefine_line|#define CONF_EP&t;&t;&t;(_ULCAST_(15)&lt;&lt; 24)
DECL|macro|CONF_EC
mdefine_line|#define CONF_EC&t;&t;&t;(_ULCAST_(7) &lt;&lt; 28)
DECL|macro|CONF_CM
mdefine_line|#define CONF_CM&t;&t;&t;(_ULCAST_(1) &lt;&lt; 31)
multiline_comment|/* Bits specific to the R4xx0.  */
DECL|macro|R4K_CONF_SW
mdefine_line|#define R4K_CONF_SW&t;&t;(_ULCAST_(1) &lt;&lt; 20)
DECL|macro|R4K_CONF_SS
mdefine_line|#define R4K_CONF_SS&t;&t;(_ULCAST_(1) &lt;&lt; 21)
DECL|macro|R4K_CONF_SB
mdefine_line|#define R4K_CONF_SB&t;&t;(_ULCAST_(3) &lt;&lt; 22)
multiline_comment|/* Bits specific to the R5000.  */
DECL|macro|R5K_CONF_SE
mdefine_line|#define R5K_CONF_SE&t;&t;(_ULCAST_(1) &lt;&lt; 12)
DECL|macro|R5K_CONF_SS
mdefine_line|#define R5K_CONF_SS&t;&t;(_ULCAST_(3) &lt;&lt; 20)
multiline_comment|/* Bits specific to the R10000.  */
DECL|macro|R10K_CONF_DN
mdefine_line|#define R10K_CONF_DN&t;&t;(_ULCAST_(3) &lt;&lt;  3)
DECL|macro|R10K_CONF_CT
mdefine_line|#define R10K_CONF_CT&t;&t;(_ULCAST_(1) &lt;&lt;  5)
DECL|macro|R10K_CONF_PE
mdefine_line|#define R10K_CONF_PE&t;&t;(_ULCAST_(1) &lt;&lt;  6)
DECL|macro|R10K_CONF_PM
mdefine_line|#define R10K_CONF_PM&t;&t;(_ULCAST_(3) &lt;&lt;  7)
DECL|macro|R10K_CONF_EC
mdefine_line|#define R10K_CONF_EC&t;&t;(_ULCAST_(15)&lt;&lt;  9)
DECL|macro|R10K_CONF_SB
mdefine_line|#define R10K_CONF_SB&t;&t;(_ULCAST_(1) &lt;&lt; 13)
DECL|macro|R10K_CONF_SK
mdefine_line|#define R10K_CONF_SK&t;&t;(_ULCAST_(1) &lt;&lt; 14)
DECL|macro|R10K_CONF_SS
mdefine_line|#define R10K_CONF_SS&t;&t;(_ULCAST_(7) &lt;&lt; 16)
DECL|macro|R10K_CONF_SC
mdefine_line|#define R10K_CONF_SC&t;&t;(_ULCAST_(7) &lt;&lt; 19)
DECL|macro|R10K_CONF_DC
mdefine_line|#define R10K_CONF_DC&t;&t;(_ULCAST_(7) &lt;&lt; 26)
DECL|macro|R10K_CONF_IC
mdefine_line|#define R10K_CONF_IC&t;&t;(_ULCAST_(7) &lt;&lt; 29)
multiline_comment|/* Bits specific to the VR41xx.  */
DECL|macro|VR41_CONF_CS
mdefine_line|#define VR41_CONF_CS&t;&t;(_ULCAST_(1) &lt;&lt; 12)
DECL|macro|VR41_CONF_M16
mdefine_line|#define VR41_CONF_M16&t;&t;(_ULCAST_(1) &lt;&lt; 20)
DECL|macro|VR41_CONF_AD
mdefine_line|#define VR41_CONF_AD&t;&t;(_ULCAST_(1) &lt;&lt; 23)
multiline_comment|/* Bits specific to the R30xx.  */
DECL|macro|R30XX_CONF_FDM
mdefine_line|#define R30XX_CONF_FDM&t;&t;(_ULCAST_(1) &lt;&lt; 19)
DECL|macro|R30XX_CONF_REV
mdefine_line|#define R30XX_CONF_REV&t;&t;(_ULCAST_(1) &lt;&lt; 22)
DECL|macro|R30XX_CONF_AC
mdefine_line|#define R30XX_CONF_AC&t;&t;(_ULCAST_(1) &lt;&lt; 23)
DECL|macro|R30XX_CONF_RF
mdefine_line|#define R30XX_CONF_RF&t;&t;(_ULCAST_(1) &lt;&lt; 24)
DECL|macro|R30XX_CONF_HALT
mdefine_line|#define R30XX_CONF_HALT&t;&t;(_ULCAST_(1) &lt;&lt; 25)
DECL|macro|R30XX_CONF_FPINT
mdefine_line|#define R30XX_CONF_FPINT&t;(_ULCAST_(7) &lt;&lt; 26)
DECL|macro|R30XX_CONF_DBR
mdefine_line|#define R30XX_CONF_DBR&t;&t;(_ULCAST_(1) &lt;&lt; 29)
DECL|macro|R30XX_CONF_SB
mdefine_line|#define R30XX_CONF_SB&t;&t;(_ULCAST_(1) &lt;&lt; 30)
DECL|macro|R30XX_CONF_LOCK
mdefine_line|#define R30XX_CONF_LOCK&t;&t;(_ULCAST_(1) &lt;&lt; 31)
multiline_comment|/* Bits specific to the TX49.  */
DECL|macro|TX49_CONF_DC
mdefine_line|#define TX49_CONF_DC&t;&t;(_ULCAST_(1) &lt;&lt; 16)
DECL|macro|TX49_CONF_IC
mdefine_line|#define TX49_CONF_IC&t;&t;(_ULCAST_(1) &lt;&lt; 17)  /* conflict with CONF_SC */
DECL|macro|TX49_CONF_HALT
mdefine_line|#define TX49_CONF_HALT&t;&t;(_ULCAST_(1) &lt;&lt; 18)
DECL|macro|TX49_CONF_CWFON
mdefine_line|#define TX49_CONF_CWFON&t;&t;(_ULCAST_(1) &lt;&lt; 27)
multiline_comment|/* Bits specific to the MIPS32/64 PRA.  */
DECL|macro|MIPS_CONF_MT
mdefine_line|#define MIPS_CONF_MT&t;&t;(_ULCAST_(7) &lt;&lt;  7)
DECL|macro|MIPS_CONF_AR
mdefine_line|#define MIPS_CONF_AR&t;&t;(_ULCAST_(7) &lt;&lt; 10)
DECL|macro|MIPS_CONF_AT
mdefine_line|#define MIPS_CONF_AT&t;&t;(_ULCAST_(3) &lt;&lt; 13)
DECL|macro|MIPS_CONF_M
mdefine_line|#define MIPS_CONF_M&t;&t;(_ULCAST_(1) &lt;&lt; 31)
multiline_comment|/*&n; * R10000 performance counter definitions.&n; *&n; * FIXME: The R10000 performance counter opens a nice way to implement CPU&n; *        time accounting with a precission of one cycle.  I don&squot;t have&n; *        R10000 silicon but just a manual, so ...&n; */
multiline_comment|/*&n; * Events counted by counter #0&n; */
DECL|macro|CE0_CYCLES
mdefine_line|#define CE0_CYCLES&t;&t;&t;0
DECL|macro|CE0_INSN_ISSUED
mdefine_line|#define CE0_INSN_ISSUED&t;&t;&t;1
DECL|macro|CE0_LPSC_ISSUED
mdefine_line|#define CE0_LPSC_ISSUED&t;&t;&t;2
DECL|macro|CE0_S_ISSUED
mdefine_line|#define CE0_S_ISSUED&t;&t;&t;3
DECL|macro|CE0_SC_ISSUED
mdefine_line|#define CE0_SC_ISSUED&t;&t;&t;4
DECL|macro|CE0_SC_FAILED
mdefine_line|#define CE0_SC_FAILED&t;&t;&t;5
DECL|macro|CE0_BRANCH_DECODED
mdefine_line|#define CE0_BRANCH_DECODED&t;&t;6
DECL|macro|CE0_QW_WB_SECONDARY
mdefine_line|#define CE0_QW_WB_SECONDARY&t;&t;7
DECL|macro|CE0_CORRECTED_ECC_ERRORS
mdefine_line|#define CE0_CORRECTED_ECC_ERRORS&t;8
DECL|macro|CE0_ICACHE_MISSES
mdefine_line|#define CE0_ICACHE_MISSES&t;&t;9
DECL|macro|CE0_SCACHE_I_MISSES
mdefine_line|#define CE0_SCACHE_I_MISSES&t;&t;10
DECL|macro|CE0_SCACHE_I_WAY_MISSPREDICTED
mdefine_line|#define CE0_SCACHE_I_WAY_MISSPREDICTED&t;11
DECL|macro|CE0_EXT_INTERVENTIONS_REQ
mdefine_line|#define CE0_EXT_INTERVENTIONS_REQ&t;12
DECL|macro|CE0_EXT_INVALIDATE_REQ
mdefine_line|#define CE0_EXT_INVALIDATE_REQ&t;&t;13
DECL|macro|CE0_VIRTUAL_COHERENCY_COND
mdefine_line|#define CE0_VIRTUAL_COHERENCY_COND&t;14
DECL|macro|CE0_INSN_GRADUATED
mdefine_line|#define CE0_INSN_GRADUATED&t;&t;15
multiline_comment|/*&n; * Events counted by counter #1&n; */
DECL|macro|CE1_CYCLES
mdefine_line|#define CE1_CYCLES&t;&t;&t;0
DECL|macro|CE1_INSN_GRADUATED
mdefine_line|#define CE1_INSN_GRADUATED&t;&t;1
DECL|macro|CE1_LPSC_GRADUATED
mdefine_line|#define CE1_LPSC_GRADUATED&t;&t;2
DECL|macro|CE1_S_GRADUATED
mdefine_line|#define CE1_S_GRADUATED&t;&t;&t;3
DECL|macro|CE1_SC_GRADUATED
mdefine_line|#define CE1_SC_GRADUATED&t;&t;4
DECL|macro|CE1_FP_INSN_GRADUATED
mdefine_line|#define CE1_FP_INSN_GRADUATED&t;&t;5
DECL|macro|CE1_QW_WB_PRIMARY
mdefine_line|#define CE1_QW_WB_PRIMARY&t;&t;6
DECL|macro|CE1_TLB_REFILL
mdefine_line|#define CE1_TLB_REFILL&t;&t;&t;7
DECL|macro|CE1_BRANCH_MISSPREDICTED
mdefine_line|#define CE1_BRANCH_MISSPREDICTED&t;8
DECL|macro|CE1_DCACHE_MISS
mdefine_line|#define CE1_DCACHE_MISS&t;&t;&t;9
DECL|macro|CE1_SCACHE_D_MISSES
mdefine_line|#define CE1_SCACHE_D_MISSES&t;&t;10
DECL|macro|CE1_SCACHE_D_WAY_MISSPREDICTED
mdefine_line|#define CE1_SCACHE_D_WAY_MISSPREDICTED&t;11
DECL|macro|CE1_EXT_INTERVENTION_HITS
mdefine_line|#define CE1_EXT_INTERVENTION_HITS&t;12
DECL|macro|CE1_EXT_INVALIDATE_REQ
mdefine_line|#define CE1_EXT_INVALIDATE_REQ&t;&t;13
DECL|macro|CE1_SP_HINT_TO_CEXCL_SC_BLOCKS
mdefine_line|#define CE1_SP_HINT_TO_CEXCL_SC_BLOCKS&t;14
DECL|macro|CE1_SP_HINT_TO_SHARED_SC_BLOCKS
mdefine_line|#define CE1_SP_HINT_TO_SHARED_SC_BLOCKS&t;15
multiline_comment|/*&n; * These flags define in which privilege mode the counters count events&n; */
DECL|macro|CEB_USER
mdefine_line|#define CEB_USER&t;8&t;/* Count events in user mode, EXL = ERL = 0 */
DECL|macro|CEB_SUPERVISOR
mdefine_line|#define CEB_SUPERVISOR&t;4&t;/* Count events in supvervisor mode EXL = ERL = 0 */
DECL|macro|CEB_KERNEL
mdefine_line|#define CEB_KERNEL&t;2&t;/* Count events in kernel mode EXL = ERL = 0 */
DECL|macro|CEB_EXL
mdefine_line|#define CEB_EXL&t;&t;1&t;/* Count events with EXL = 1, ERL = 0 */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Functions to access the R10000 performance counters.  These are basically&n; * mfc0 and mtc0 instructions from and to coprocessor register with a 5-bit&n; * performance counter number encoded into bits 1 ... 5 of the instruction.&n; * Only performance counters 0 to 1 actually exist, so for a non-R10000 aware&n; * disassembler these will look like an access to sel 0 or 1.&n; */
DECL|macro|read_r10k_perf_cntr
mdefine_line|#define read_r10k_perf_cntr(counter)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __res;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mfpc&bslash;t%0, %1&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;i&quot; (counter));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|write_r10k_perf_cntr
mdefine_line|#define write_r10k_perf_cntr(counter,val)                       &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mtpc&bslash;t%0, %1&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (val), &quot;i&quot; (counter));&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|read_r10k_perf_event
mdefine_line|#define read_r10k_perf_event(counter)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __res;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mfps&bslash;t%0, %1&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;i&quot; (counter));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        __res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|write_r10k_perf_cntl
mdefine_line|#define write_r10k_perf_cntl(counter,val)                       &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mtps&bslash;t%0, %1&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (val), &quot;i&quot; (counter));&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Macros to access the system control coprocessor&n; */
DECL|macro|__read_32bit_c0_register
mdefine_line|#define __read_32bit_c0_register(source, sel)&t;&t;&t;&t;&bslash;&n;({ int __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sel == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;mfc0&bslash;t%0, &quot; #source &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__res));&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;mfc0&bslash;t%0, &quot; #source &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__res));&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__read_64bit_c0_register
mdefine_line|#define __read_64bit_c0_register(source, sel)&t;&t;&t;&t;&bslash;&n;({ unsigned long long __res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(unsigned long) == 4)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__res = __read_64bit_c0_split(source, sel);&t;&t;&bslash;&n;&t;else if (sel == 0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmfc0&bslash;t%0, &quot; #source &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__res));&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmfc0&bslash;t%0, &quot; #source &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (__res));&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__write_32bit_c0_register
mdefine_line|#define __write_32bit_c0_register(register, sel, value)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sel == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;mtc0&bslash;t%z0, &quot; #register &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;Jr&quot; ((unsigned int)value));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;mtc0&bslash;t%z0, &quot; #register &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;Jr&quot; ((unsigned int)value));&t;&t;&bslash;&n;} while (0)
DECL|macro|__write_64bit_c0_register
mdefine_line|#define __write_64bit_c0_register(register, sel, value)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(unsigned long) == 4)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__write_64bit_c0_split(register, sel, value);&t;&t;&bslash;&n;&t;else if (sel == 0)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmtc0&bslash;t%z0, &quot; #register &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;Jr&quot; (value));&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmtc0&bslash;t%z0, &quot; #register &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;Jr&quot; (value));&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|__read_ulong_c0_register
mdefine_line|#define __read_ulong_c0_register(reg, sel)&t;&t;&t;&t;&bslash;&n;&t;((sizeof(unsigned long) == 4) ?&t;&t;&t;&t;&t;&bslash;&n;&t;(unsigned long) __read_32bit_c0_register(reg, sel) :&t;&t;&bslash;&n;&t;(unsigned long) __read_64bit_c0_register(reg, sel))
DECL|macro|__write_ulong_c0_register
mdefine_line|#define __write_ulong_c0_register(reg, sel, val)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sizeof(unsigned long) == 4)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__write_32bit_c0_register(reg, sel, val);&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__write_64bit_c0_register(reg, sel, val);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * On RM7000/RM9000 these are uses to access cop0 set 1 registers&n; */
DECL|macro|__read_32bit_c0_ctrl_register
mdefine_line|#define __read_32bit_c0_ctrl_register(source)&t;&t;&t;&t;&bslash;&n;({ int __res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cfc0&bslash;t%0, &quot; #source &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__res));&t;&t;&t;&t;&t;&bslash;&n;&t;__res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__write_32bit_c0_ctrl_register
mdefine_line|#define __write_32bit_c0_ctrl_register(register, value)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ctc0&bslash;t%z0, &quot; #register &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;Jr&quot; ((unsigned int)value));&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * These versions are only needed for systems with more than 38 bits of&n; * physical address space running the 32-bit kernel.  That&squot;s none atm :-)&n; */
DECL|macro|__read_64bit_c0_split
mdefine_line|#define __read_64bit_c0_split(source, sel)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long long val;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sel == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmfc0&bslash;t%M0, &quot; #source &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%L0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%M0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (val));&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmfc0&bslash;t%M0, &quot; #source &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%L0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%M0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (val));&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_restore(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;val;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__write_64bit_c0_split
mdefine_line|#define __write_64bit_c0_split(source, sel, val)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (sel == 0)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%M0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;or&bslash;t%L0, %L0, %M0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmtc0&bslash;t%L0, &quot; #source &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;r&quot; (val));&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips64&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsrl&bslash;t%L0, %L0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dsll&bslash;t%M0, %M0, 32&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;or&bslash;t%L0, %L0, %M0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&quot;dmtc0&bslash;t%L0, &quot; #source &quot;, &quot; #sel &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&bslash;tmips0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;: : &quot;r&quot; (val));&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_restore(flags);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|read_c0_index
mdefine_line|#define read_c0_index()&t;&t;__read_32bit_c0_register($0, 0)
DECL|macro|write_c0_index
mdefine_line|#define write_c0_index(val)&t;__write_32bit_c0_register($0, 0, val)
DECL|macro|read_c0_entrylo0
mdefine_line|#define read_c0_entrylo0()&t;__read_ulong_c0_register($2, 0)
DECL|macro|write_c0_entrylo0
mdefine_line|#define write_c0_entrylo0(val)&t;__write_ulong_c0_register($2, 0, val)
DECL|macro|read_c0_entrylo1
mdefine_line|#define read_c0_entrylo1()&t;__read_ulong_c0_register($3, 0)
DECL|macro|write_c0_entrylo1
mdefine_line|#define write_c0_entrylo1(val)&t;__write_ulong_c0_register($3, 0, val)
DECL|macro|read_c0_conf
mdefine_line|#define read_c0_conf()&t;&t;__read_32bit_c0_register($3, 0)
DECL|macro|write_c0_conf
mdefine_line|#define write_c0_conf(val)&t;__write_32bit_c0_register($3, 0, val)
DECL|macro|read_c0_context
mdefine_line|#define read_c0_context()&t;__read_ulong_c0_register($4, 0)
DECL|macro|write_c0_context
mdefine_line|#define write_c0_context(val)&t;__write_ulong_c0_register($4, 0, val)
DECL|macro|read_c0_pagemask
mdefine_line|#define read_c0_pagemask()&t;__read_32bit_c0_register($5, 0)
DECL|macro|write_c0_pagemask
mdefine_line|#define write_c0_pagemask(val)&t;__write_32bit_c0_register($5, 0, val)
DECL|macro|read_c0_wired
mdefine_line|#define read_c0_wired()&t;&t;__read_32bit_c0_register($6, 0)
DECL|macro|write_c0_wired
mdefine_line|#define write_c0_wired(val)&t;__write_32bit_c0_register($6, 0, val)
DECL|macro|read_c0_info
mdefine_line|#define read_c0_info()&t;&t;__read_32bit_c0_register($7, 0)
DECL|macro|read_c0_cache
mdefine_line|#define read_c0_cache()&t;&t;__read_32bit_c0_register($7, 0)&t;/* TX39xx */
DECL|macro|write_c0_cache
mdefine_line|#define write_c0_cache(val)&t;__write_32bit_c0_register($7, 0, val)
DECL|macro|read_c0_count
mdefine_line|#define read_c0_count()&t;&t;__read_32bit_c0_register($9, 0)
DECL|macro|write_c0_count
mdefine_line|#define write_c0_count(val)&t;__write_32bit_c0_register($9, 0, val)
DECL|macro|read_c0_entryhi
mdefine_line|#define read_c0_entryhi()&t;__read_ulong_c0_register($10, 0)
DECL|macro|write_c0_entryhi
mdefine_line|#define write_c0_entryhi(val)&t;__write_ulong_c0_register($10, 0, val)
DECL|macro|read_c0_compare
mdefine_line|#define read_c0_compare()&t;__read_32bit_c0_register($11, 0)
DECL|macro|write_c0_compare
mdefine_line|#define write_c0_compare(val)&t;__write_32bit_c0_register($11, 0, val)
DECL|macro|read_c0_status
mdefine_line|#define read_c0_status()&t;__read_32bit_c0_register($12, 0)
DECL|macro|write_c0_status
mdefine_line|#define write_c0_status(val)&t;__write_32bit_c0_register($12, 0, val)
DECL|macro|read_c0_cause
mdefine_line|#define read_c0_cause()&t;&t;__read_32bit_c0_register($13, 0)
DECL|macro|write_c0_cause
mdefine_line|#define write_c0_cause(val)&t;__write_32bit_c0_register($13, 0, val)
DECL|macro|read_c0_epc
mdefine_line|#define read_c0_epc()&t;&t;__read_ulong_c0_register($14, 0)
DECL|macro|write_c0_epc
mdefine_line|#define write_c0_epc(val)&t;__write_ulong_c0_register($14, 0, val)
DECL|macro|read_c0_prid
mdefine_line|#define read_c0_prid()&t;&t;__read_32bit_c0_register($15, 0)
DECL|macro|read_c0_config
mdefine_line|#define read_c0_config()&t;__read_32bit_c0_register($16, 0)
DECL|macro|read_c0_config1
mdefine_line|#define read_c0_config1()&t;__read_32bit_c0_register($16, 1)
DECL|macro|read_c0_config2
mdefine_line|#define read_c0_config2()&t;__read_32bit_c0_register($16, 2)
DECL|macro|read_c0_config3
mdefine_line|#define read_c0_config3()&t;__read_32bit_c0_register($16, 3)
DECL|macro|write_c0_config
mdefine_line|#define write_c0_config(val)&t;__write_32bit_c0_register($16, 0, val)
DECL|macro|write_c0_config1
mdefine_line|#define write_c0_config1(val)&t;__write_32bit_c0_register($16, 1, val)
DECL|macro|write_c0_config2
mdefine_line|#define write_c0_config2(val)&t;__write_32bit_c0_register($16, 2, val)
DECL|macro|write_c0_config3
mdefine_line|#define write_c0_config3(val)&t;__write_32bit_c0_register($16, 3, val)
multiline_comment|/*&n; * The WatchLo register.  There may be upto 8 of them.&n; */
DECL|macro|read_c0_watchlo0
mdefine_line|#define read_c0_watchlo0()&t;__read_ulong_c0_register($18, 0)
DECL|macro|read_c0_watchlo1
mdefine_line|#define read_c0_watchlo1()&t;__read_ulong_c0_register($18, 1)
DECL|macro|read_c0_watchlo2
mdefine_line|#define read_c0_watchlo2()&t;__read_ulong_c0_register($18, 2)
DECL|macro|read_c0_watchlo3
mdefine_line|#define read_c0_watchlo3()&t;__read_ulong_c0_register($18, 3)
DECL|macro|read_c0_watchlo4
mdefine_line|#define read_c0_watchlo4()&t;__read_ulong_c0_register($18, 4)
DECL|macro|read_c0_watchlo5
mdefine_line|#define read_c0_watchlo5()&t;__read_ulong_c0_register($18, 5)
DECL|macro|read_c0_watchlo6
mdefine_line|#define read_c0_watchlo6()&t;__read_ulong_c0_register($18, 6)
DECL|macro|read_c0_watchlo7
mdefine_line|#define read_c0_watchlo7()&t;__read_ulong_c0_register($18, 7)
DECL|macro|write_c0_watchlo0
mdefine_line|#define write_c0_watchlo0(val)&t;__write_ulong_c0_register($18, 0, val)
DECL|macro|write_c0_watchlo1
mdefine_line|#define write_c0_watchlo1(val)&t;__write_ulong_c0_register($18, 1, val)
DECL|macro|write_c0_watchlo2
mdefine_line|#define write_c0_watchlo2(val)&t;__write_ulong_c0_register($18, 2, val)
DECL|macro|write_c0_watchlo3
mdefine_line|#define write_c0_watchlo3(val)&t;__write_ulong_c0_register($18, 3, val)
DECL|macro|write_c0_watchlo4
mdefine_line|#define write_c0_watchlo4(val)&t;__write_ulong_c0_register($18, 4, val)
DECL|macro|write_c0_watchlo5
mdefine_line|#define write_c0_watchlo5(val)&t;__write_ulong_c0_register($18, 5, val)
DECL|macro|write_c0_watchlo6
mdefine_line|#define write_c0_watchlo6(val)&t;__write_ulong_c0_register($18, 6, val)
DECL|macro|write_c0_watchlo7
mdefine_line|#define write_c0_watchlo7(val)&t;__write_ulong_c0_register($18, 7, val)
multiline_comment|/*&n; * The WatchHi register.  There may be upto 8 of them.&n; */
DECL|macro|read_c0_watchhi0
mdefine_line|#define read_c0_watchhi0()&t;__read_32bit_c0_register($19, 0)
DECL|macro|read_c0_watchhi1
mdefine_line|#define read_c0_watchhi1()&t;__read_32bit_c0_register($19, 1)
DECL|macro|read_c0_watchhi2
mdefine_line|#define read_c0_watchhi2()&t;__read_32bit_c0_register($19, 2)
DECL|macro|read_c0_watchhi3
mdefine_line|#define read_c0_watchhi3()&t;__read_32bit_c0_register($19, 3)
DECL|macro|read_c0_watchhi4
mdefine_line|#define read_c0_watchhi4()&t;__read_32bit_c0_register($19, 4)
DECL|macro|read_c0_watchhi5
mdefine_line|#define read_c0_watchhi5()&t;__read_32bit_c0_register($19, 5)
DECL|macro|read_c0_watchhi6
mdefine_line|#define read_c0_watchhi6()&t;__read_32bit_c0_register($19, 6)
DECL|macro|read_c0_watchhi7
mdefine_line|#define read_c0_watchhi7()&t;__read_32bit_c0_register($19, 7)
DECL|macro|write_c0_watchhi0
mdefine_line|#define write_c0_watchhi0(val)&t;__write_32bit_c0_register($19, 0, val)
DECL|macro|write_c0_watchhi1
mdefine_line|#define write_c0_watchhi1(val)&t;__write_32bit_c0_register($19, 1, val)
DECL|macro|write_c0_watchhi2
mdefine_line|#define write_c0_watchhi2(val)&t;__write_32bit_c0_register($19, 2, val)
DECL|macro|write_c0_watchhi3
mdefine_line|#define write_c0_watchhi3(val)&t;__write_32bit_c0_register($19, 3, val)
DECL|macro|write_c0_watchhi4
mdefine_line|#define write_c0_watchhi4(val)&t;__write_32bit_c0_register($19, 4, val)
DECL|macro|write_c0_watchhi5
mdefine_line|#define write_c0_watchhi5(val)&t;__write_32bit_c0_register($19, 5, val)
DECL|macro|write_c0_watchhi6
mdefine_line|#define write_c0_watchhi6(val)&t;__write_32bit_c0_register($19, 6, val)
DECL|macro|write_c0_watchhi7
mdefine_line|#define write_c0_watchhi7(val)&t;__write_32bit_c0_register($19, 7, val)
DECL|macro|read_c0_xcontext
mdefine_line|#define read_c0_xcontext()&t;__read_ulong_c0_register($20, 0)
DECL|macro|write_c0_xcontext
mdefine_line|#define write_c0_xcontext(val)&t;__write_ulong_c0_register($20, 0, val)
DECL|macro|read_c0_intcontrol
mdefine_line|#define read_c0_intcontrol()&t;__read_32bit_c0_ctrl_register($20)
DECL|macro|write_c0_intcontrol
mdefine_line|#define write_c0_intcontrol(val) __write_32bit_c0_ctrl_register($20, val)
DECL|macro|read_c0_framemask
mdefine_line|#define read_c0_framemask()&t;__read_32bit_c0_register($21, 0)
DECL|macro|write_c0_framemask
mdefine_line|#define write_c0_framemask(val)&t;__write_32bit_c0_register($21, 0, val)
multiline_comment|/* RM9000 PerfControl performance counter control register */
DECL|macro|read_c0_perfcontrol
mdefine_line|#define read_c0_perfcontrol()&t;__read_32bit_c0_register($22, 0)
DECL|macro|write_c0_perfcontrol
mdefine_line|#define write_c0_perfcontrol(val) __write_32bit_c0_register($22, 0, val)
DECL|macro|read_c0_diag
mdefine_line|#define read_c0_diag()&t;&t;__read_32bit_c0_register($22, 0)
DECL|macro|write_c0_diag
mdefine_line|#define write_c0_diag(val)&t;__write_32bit_c0_register($22, 0, val)
DECL|macro|read_c0_diag1
mdefine_line|#define read_c0_diag1()&t;&t;__read_32bit_c0_register($22, 1)
DECL|macro|write_c0_diag1
mdefine_line|#define write_c0_diag1(val)&t;__write_32bit_c0_register($22, 1, val)
DECL|macro|read_c0_diag2
mdefine_line|#define read_c0_diag2()&t;&t;__read_32bit_c0_register($22, 2)
DECL|macro|write_c0_diag2
mdefine_line|#define write_c0_diag2(val)&t;__write_32bit_c0_register($22, 2, val)
DECL|macro|read_c0_diag3
mdefine_line|#define read_c0_diag3()&t;&t;__read_32bit_c0_register($22, 3)
DECL|macro|write_c0_diag3
mdefine_line|#define write_c0_diag3(val)&t;__write_32bit_c0_register($22, 3, val)
DECL|macro|read_c0_diag4
mdefine_line|#define read_c0_diag4()&t;&t;__read_32bit_c0_register($22, 4)
DECL|macro|write_c0_diag4
mdefine_line|#define write_c0_diag4(val)&t;__write_32bit_c0_register($22, 4, val)
DECL|macro|read_c0_diag5
mdefine_line|#define read_c0_diag5()&t;&t;__read_32bit_c0_register($22, 5)
DECL|macro|write_c0_diag5
mdefine_line|#define write_c0_diag5(val)&t;__write_32bit_c0_register($22, 5, val)
DECL|macro|read_c0_debug
mdefine_line|#define read_c0_debug()&t;&t;__read_32bit_c0_register($23, 0)
DECL|macro|write_c0_debug
mdefine_line|#define write_c0_debug(val)&t;__write_32bit_c0_register($23, 0, val)
DECL|macro|read_c0_depc
mdefine_line|#define read_c0_depc()&t;&t;__read_ulong_c0_register($24, 0)
DECL|macro|write_c0_depc
mdefine_line|#define write_c0_depc(val)&t;__write_ulong_c0_register($24, 0, val)
multiline_comment|/*&n; * MIPS32 / MIPS64 performance counters&n; */
DECL|macro|read_c0_perfctrl0
mdefine_line|#define read_c0_perfctrl0()&t;__read_32bit_c0_register($25, 0)
DECL|macro|write_c0_perfctrl0
mdefine_line|#define write_c0_perfctrl0(val)&t;__write_32bit_c0_register($25, 0, val)
DECL|macro|read_c0_perfcntr0
mdefine_line|#define read_c0_perfcntr0()&t;__read_32bit_c0_register($25, 1)
DECL|macro|write_c0_perfcntr0
mdefine_line|#define write_c0_perfcntr0(val)&t;__write_32bit_c0_register($25, 1, val)
DECL|macro|read_c0_perfctrl1
mdefine_line|#define read_c0_perfctrl1()&t;__read_32bit_c0_register($25, 2)
DECL|macro|write_c0_perfctrl1
mdefine_line|#define write_c0_perfctrl1(val)&t;__write_32bit_c0_register($25, 2, val)
DECL|macro|read_c0_perfcntr1
mdefine_line|#define read_c0_perfcntr1()&t;__read_32bit_c0_register($25, 3)
DECL|macro|write_c0_perfcntr1
mdefine_line|#define write_c0_perfcntr1(val)&t;__write_32bit_c0_register($25, 3, val)
DECL|macro|read_c0_perfctrl2
mdefine_line|#define read_c0_perfctrl2()&t;__read_32bit_c0_register($25, 4)
DECL|macro|write_c0_perfctrl2
mdefine_line|#define write_c0_perfctrl2(val)&t;__write_32bit_c0_register($25, 4, val)
DECL|macro|read_c0_perfcntr2
mdefine_line|#define read_c0_perfcntr2()&t;__read_32bit_c0_register($25, 5)
DECL|macro|write_c0_perfcntr2
mdefine_line|#define write_c0_perfcntr2(val)&t;__write_32bit_c0_register($25, 5, val)
DECL|macro|read_c0_perfctrl3
mdefine_line|#define read_c0_perfctrl3()&t;__read_32bit_c0_register($25, 6)
DECL|macro|write_c0_perfctrl3
mdefine_line|#define write_c0_perfctrl3(val)&t;__write_32bit_c0_register($25, 6, val)
DECL|macro|read_c0_perfcntr3
mdefine_line|#define read_c0_perfcntr3()&t;__read_32bit_c0_register($25, 7)
DECL|macro|write_c0_perfcntr3
mdefine_line|#define write_c0_perfcntr3(val)&t;__write_32bit_c0_register($25, 7, val)
multiline_comment|/* RM9000 PerfCount performance counter register */
DECL|macro|read_c0_perfcount
mdefine_line|#define read_c0_perfcount()&t;__read_64bit_c0_register($25, 0)
DECL|macro|write_c0_perfcount
mdefine_line|#define write_c0_perfcount(val)&t;__write_64bit_c0_register($25, 0, val)
DECL|macro|read_c0_ecc
mdefine_line|#define read_c0_ecc()&t;&t;__read_32bit_c0_register($26, 0)
DECL|macro|write_c0_ecc
mdefine_line|#define write_c0_ecc(val)&t;__write_32bit_c0_register($26, 0, val)
DECL|macro|read_c0_derraddr0
mdefine_line|#define read_c0_derraddr0()&t;__read_ulong_c0_register($26, 1)
DECL|macro|write_c0_derraddr0
mdefine_line|#define write_c0_derraddr0(val)&t;__write_ulong_c0_register($26, 1, val)
DECL|macro|read_c0_cacheerr
mdefine_line|#define read_c0_cacheerr()&t;__read_32bit_c0_register($27, 0)
DECL|macro|read_c0_derraddr1
mdefine_line|#define read_c0_derraddr1()&t;__read_ulong_c0_register($27, 1)
DECL|macro|write_c0_derraddr1
mdefine_line|#define write_c0_derraddr1(val)&t;__write_ulong_c0_register($27, 1, val)
DECL|macro|read_c0_taglo
mdefine_line|#define read_c0_taglo()&t;&t;__read_32bit_c0_register($28, 0)
DECL|macro|write_c0_taglo
mdefine_line|#define write_c0_taglo(val)&t;__write_32bit_c0_register($28, 0, val)
DECL|macro|read_c0_taghi
mdefine_line|#define read_c0_taghi()&t;&t;__read_32bit_c0_register($29, 0)
DECL|macro|write_c0_taghi
mdefine_line|#define write_c0_taghi(val)&t;__write_32bit_c0_register($29, 0, val)
DECL|macro|read_c0_errorepc
mdefine_line|#define read_c0_errorepc()&t;__read_ulong_c0_register($30, 0)
DECL|macro|write_c0_errorepc
mdefine_line|#define write_c0_errorepc(val)&t;__write_ulong_c0_register($30, 0, val)
multiline_comment|/*&n; * Macros to access the floating point coprocessor control registers&n; */
DECL|macro|read_32bit_cp1_register
mdefine_line|#define read_32bit_cp1_register(source)                         &bslash;&n;({ int __res;                                                   &bslash;&n;&t;__asm__ __volatile__(                                   &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;        &quot;cfc1&bslash;t%0,&quot;STR(source)&quot;&bslash;n&bslash;t&quot;                            &bslash;&n;&t;&quot;.set&bslash;tpop&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res));                                        &bslash;&n;        __res;})
multiline_comment|/*&n; * TLB operations.&n; *&n; * It is responsibility of the caller to take care of any TLB hazards.&n; */
DECL|function|tlb_probe
r_static
r_inline
r_void
id|tlb_probe
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbp&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_read
r_static
r_inline
r_void
id|tlb_read
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbr&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_write_indexed
r_static
r_inline
r_void
id|tlb_write_indexed
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbwi&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_write_random
r_static
r_inline
r_void
id|tlb_write_random
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbwr&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Manipulate bits in a c0 register.&n; */
DECL|macro|__BUILD_SET_C0
mdefine_line|#define __BUILD_SET_C0(name)&t;&t;&t;&t;&t;&bslash;&n;static inline unsigned int&t;&t;&t;&t;&t;&bslash;&n;set_c0_##name(unsigned int set)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int res;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;res = read_c0_##name();&t;&t;&t;&t;&t;&bslash;&n;&t;res |= set;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write_c0_##name(res);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return res;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline unsigned int&t;&t;&t;&t;&t;&bslash;&n;clear_c0_##name(unsigned int clear)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int res;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;res = read_c0_##name();&t;&t;&t;&t;&t;&bslash;&n;&t;res &amp;= ~clear;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write_c0_##name(res);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return res;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline unsigned int&t;&t;&t;&t;&t;&bslash;&n;change_c0_##name(unsigned int change, unsigned int new)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int res;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;res = read_c0_##name();&t;&t;&t;&t;&t;&bslash;&n;&t;res &amp;= ~change;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;res |= (new &amp; change);&t;&t;&t;&t;&t;&bslash;&n;&t;write_c0_##name(res);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return res;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|__BUILD_SET_C0
c_func
(paren
id|status
)paren
id|__BUILD_SET_C0
c_func
(paren
id|cause
)paren
id|__BUILD_SET_C0
c_func
(paren
id|config
)paren
id|__BUILD_SET_C0
c_func
(paren
id|intcontrol
)paren
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_MIPSREGS_H */
eof
