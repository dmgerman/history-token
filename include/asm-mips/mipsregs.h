multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 2000, 2001 by Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Modified for further R[236]000 support by Paul M. Antoine, 1996.&n; * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_MIPSREGS_H
DECL|macro|_ASM_MIPSREGS_H
mdefine_line|#define _ASM_MIPSREGS_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * The following macros are especially useful for __asm__&n; * inline assembler.&n; */
macro_line|#ifndef __STR
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
macro_line|#endif
macro_line|#ifndef STR
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
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
multiline_comment|/* &n; * Coprocessor 0 Set 1 register names&n; */
DECL|macro|CP0_S1_DERRADDR0
mdefine_line|#define CP0_S1_DERRADDR0  $26
DECL|macro|CP0_S1_DERRADDR1
mdefine_line|#define CP0_S1_DERRADDR1  $27
DECL|macro|CP0_S1_INTCONTROL
mdefine_line|#define CP0_S1_INTCONTROL $20
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
mdefine_line|#define FPU_CSR_ALL_X 0x0003f000
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
DECL|macro|PM_4K
mdefine_line|#define PM_4K   0x00000000
DECL|macro|PM_16K
mdefine_line|#define PM_16K  0x00006000
DECL|macro|PM_64K
mdefine_line|#define PM_64K  0x0001e000
DECL|macro|PM_256K
mdefine_line|#define PM_256K 0x0007e000
DECL|macro|PM_1M
mdefine_line|#define PM_1M   0x001fe000
DECL|macro|PM_4M
mdefine_line|#define PM_4M   0x007fe000
DECL|macro|PM_16M
mdefine_line|#define PM_16M  0x01ffe000
multiline_comment|/*&n; * Values used for computation of new tlb entries&n; */
DECL|macro|PL_4K
mdefine_line|#define PL_4K   12
DECL|macro|PL_16K
mdefine_line|#define PL_16K  14
DECL|macro|PL_64K
mdefine_line|#define PL_64K  16
DECL|macro|PL_256K
mdefine_line|#define PL_256K 18
DECL|macro|PL_1M
mdefine_line|#define PL_1M   20
DECL|macro|PL_4M
mdefine_line|#define PL_4M   22
DECL|macro|PL_16M
mdefine_line|#define PL_16M  24
multiline_comment|/*&n; * Macros to access the system control coprocessor&n; */
DECL|macro|read_32bit_cp0_register
mdefine_line|#define read_32bit_cp0_register(source)                         &bslash;&n;({ int __res;                                                   &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;        &quot;mfc0&bslash;t%0,&quot;STR(source)&quot;&bslash;n&bslash;t&quot;                            &bslash;&n;&t;&quot;.set&bslash;tpop&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res));                                        &bslash;&n;        __res;})
DECL|macro|read_32bit_cp0_set1_register
mdefine_line|#define read_32bit_cp0_set1_register(source)                    &bslash;&n;({ int __res;                                                   &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;        &quot;cfc0&bslash;t%0,&quot;STR(source)&quot;&bslash;n&bslash;t&quot;                            &bslash;&n;&t;&quot;.set&bslash;tpop&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=r&quot; (__res));                                        &bslash;&n;        __res;})
multiline_comment|/*&n; * For now use this only with interrupts disabled!&n; */
DECL|macro|read_64bit_cp0_register
mdefine_line|#define read_64bit_cp0_register(source)                         &bslash;&n;({ int __res;                                                   &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;                                       &bslash;&n;        &quot;dmfc0&bslash;t%0,&quot;STR(source)&quot;&bslash;n&bslash;t&quot;                           &bslash;&n;        &quot;.set&bslash;tmips0&quot;                                           &bslash;&n;        : &quot;=r&quot; (__res));                                        &bslash;&n;        __res;})
DECL|macro|write_32bit_cp0_register
mdefine_line|#define write_32bit_cp0_register(register,value)                &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;mtc0&bslash;t%0,&quot;STR(register)&quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : : &quot;r&quot; (value));
DECL|macro|write_32bit_cp0_set1_register
mdefine_line|#define write_32bit_cp0_set1_register(register,value)           &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;ctc0&bslash;t%0,&quot;STR(register)&quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : : &quot;r&quot; (value));
DECL|macro|write_64bit_cp0_register
mdefine_line|#define write_64bit_cp0_register(register,value)                &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;                                       &bslash;&n;        &quot;dmtc0&bslash;t%0,&quot;STR(register)&quot;&bslash;n&bslash;t&quot;                         &bslash;&n;        &quot;.set&bslash;tmips0&quot;                                           &bslash;&n;        : : &quot;r&quot; (value))
macro_line|#ifdef CONFIG_CPU_MIPS32
multiline_comment|/* &n; * This should be changed when we get a compiler that support the MIPS32 ISA. &n; */
DECL|macro|read_mips32_cp0_config1
mdefine_line|#define read_mips32_cp0_config1()                               &bslash;&n;({ int __res;                                                   &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;                                   &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;                                        &bslash;&n;     &t;&quot;.word&bslash;t0x40018001&bslash;n&bslash;t&quot;                                 &bslash;&n;&t;&quot;move&bslash;t%0,$1&bslash;n&bslash;t&quot;                                       &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot;                                          &bslash;&n;&t;&quot;.set&bslash;treorder&quot;                                         &bslash;&n;&t;:&quot;=r&quot; (__res));                                         &bslash;&n;        __res;})
macro_line|#endif
multiline_comment|/*&n; * R4x00 interrupt enable / cause bits&n; */
DECL|macro|IE_SW0
mdefine_line|#define IE_SW0          (1&lt;&lt; 8)
DECL|macro|IE_SW1
mdefine_line|#define IE_SW1          (1&lt;&lt; 9)
DECL|macro|IE_IRQ0
mdefine_line|#define IE_IRQ0         (1&lt;&lt;10)
DECL|macro|IE_IRQ1
mdefine_line|#define IE_IRQ1         (1&lt;&lt;11)
DECL|macro|IE_IRQ2
mdefine_line|#define IE_IRQ2         (1&lt;&lt;12)
DECL|macro|IE_IRQ3
mdefine_line|#define IE_IRQ3         (1&lt;&lt;13)
DECL|macro|IE_IRQ4
mdefine_line|#define IE_IRQ4         (1&lt;&lt;14)
DECL|macro|IE_IRQ5
mdefine_line|#define IE_IRQ5         (1&lt;&lt;15)
multiline_comment|/*&n; * R4x00 interrupt cause bits&n; */
DECL|macro|C_SW0
mdefine_line|#define C_SW0           (1&lt;&lt; 8)
DECL|macro|C_SW1
mdefine_line|#define C_SW1           (1&lt;&lt; 9)
DECL|macro|C_IRQ0
mdefine_line|#define C_IRQ0          (1&lt;&lt;10)
DECL|macro|C_IRQ1
mdefine_line|#define C_IRQ1          (1&lt;&lt;11)
DECL|macro|C_IRQ2
mdefine_line|#define C_IRQ2          (1&lt;&lt;12)
DECL|macro|C_IRQ3
mdefine_line|#define C_IRQ3          (1&lt;&lt;13)
DECL|macro|C_IRQ4
mdefine_line|#define C_IRQ4          (1&lt;&lt;14)
DECL|macro|C_IRQ5
mdefine_line|#define C_IRQ5          (1&lt;&lt;15)
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Manipulate the status register.&n; * Mostly used to access the interrupt bits.&n; */
DECL|macro|__BUILD_SET_CP0
mdefine_line|#define __BUILD_SET_CP0(name,register)                          &bslash;&n;extern __inline__ unsigned int                                  &bslash;&n;set_cp0_##name(unsigned int set)&t;&t;&t;&t;&bslash;&n;{                                                               &bslash;&n;&t;unsigned int res;                                       &bslash;&n;                                                                &bslash;&n;&t;res = read_32bit_cp0_register(register);                &bslash;&n;&t;res |= set;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write_32bit_cp0_register(register, res);        &t;&bslash;&n;                                                                &bslash;&n;&t;return res;                                             &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned int                                  &bslash;&n;clear_cp0_##name(unsigned int clear)&t;&t;&t;&t;&bslash;&n;{                                                               &bslash;&n;&t;unsigned int res;                                       &bslash;&n;                                                                &bslash;&n;&t;res = read_32bit_cp0_register(register);                &bslash;&n;&t;res &amp;= ~clear;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;write_32bit_cp0_register(register, res);&t;&t;&bslash;&n;                                                                &bslash;&n;&t;return res;                                             &bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned int                                  &bslash;&n;change_cp0_##name(unsigned int change, unsigned int new)&t;&bslash;&n;{                                                               &bslash;&n;&t;unsigned int res;                                       &bslash;&n;                                                                &bslash;&n;&t;res = read_32bit_cp0_register(register);                &bslash;&n;&t;res &amp;= ~change;                                         &bslash;&n;&t;res |= (new &amp; change);                                  &bslash;&n;&t;if(change)                                              &bslash;&n;&t;&t;write_32bit_cp0_register(register, res);        &bslash;&n;                                                                &bslash;&n;&t;return res;                                             &bslash;&n;}
id|__BUILD_SET_CP0
c_func
(paren
id|status
comma
id|CP0_STATUS
)paren
id|__BUILD_SET_CP0
c_func
(paren
id|cause
comma
id|CP0_CAUSE
)paren
id|__BUILD_SET_CP0
c_func
(paren
id|config
comma
id|CP0_CONFIG
)paren
macro_line|#endif /* defined (_LANGUAGE_ASSEMBLY) */
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
multiline_comment|/*&n; * Bits specific to the R4640/R4650&n; */
DECL|macro|ST0_UM
mdefine_line|#define ST0_UM                 (1   &lt;&lt;  4)
DECL|macro|ST0_IL
mdefine_line|#define ST0_IL                 (1   &lt;&lt; 23)
DECL|macro|ST0_DL
mdefine_line|#define ST0_DL                 (1   &lt;&lt; 24)
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
mdefine_line|#define  STATUSF_IP0&t;&t;(1   &lt;&lt;  8)
DECL|macro|STATUSB_IP1
mdefine_line|#define  STATUSB_IP1&t;&t;9
DECL|macro|STATUSF_IP1
mdefine_line|#define  STATUSF_IP1&t;&t;(1   &lt;&lt;  9)
DECL|macro|STATUSB_IP2
mdefine_line|#define  STATUSB_IP2&t;&t;10
DECL|macro|STATUSF_IP2
mdefine_line|#define  STATUSF_IP2&t;&t;(1   &lt;&lt; 10)
DECL|macro|STATUSB_IP3
mdefine_line|#define  STATUSB_IP3&t;&t;11
DECL|macro|STATUSF_IP3
mdefine_line|#define  STATUSF_IP3&t;&t;(1   &lt;&lt; 11)
DECL|macro|STATUSB_IP4
mdefine_line|#define  STATUSB_IP4&t;&t;12
DECL|macro|STATUSF_IP4
mdefine_line|#define  STATUSF_IP4&t;&t;(1   &lt;&lt; 12)
DECL|macro|STATUSB_IP5
mdefine_line|#define  STATUSB_IP5&t;&t;13
DECL|macro|STATUSF_IP5
mdefine_line|#define  STATUSF_IP5&t;&t;(1   &lt;&lt; 13)
DECL|macro|STATUSB_IP6
mdefine_line|#define  STATUSB_IP6&t;&t;14
DECL|macro|STATUSF_IP6
mdefine_line|#define  STATUSF_IP6&t;&t;(1   &lt;&lt; 14)
DECL|macro|STATUSB_IP7
mdefine_line|#define  STATUSB_IP7&t;&t;15
DECL|macro|STATUSF_IP7
mdefine_line|#define  STATUSF_IP7&t;&t;(1   &lt;&lt; 15)
DECL|macro|STATUSB_IP8
mdefine_line|#define  STATUSB_IP8&t;&t;0
DECL|macro|STATUSF_IP8
mdefine_line|#define  STATUSF_IP8&t;&t;(1   &lt;&lt; 0)
DECL|macro|STATUSB_IP9
mdefine_line|#define  STATUSB_IP9&t;&t;1
DECL|macro|STATUSF_IP9
mdefine_line|#define  STATUSF_IP9&t;&t;(1   &lt;&lt; 1)
DECL|macro|STATUSB_IP10
mdefine_line|#define  STATUSB_IP10&t;&t;2
DECL|macro|STATUSF_IP10
mdefine_line|#define  STATUSF_IP10&t;&t;(1   &lt;&lt; 2)
DECL|macro|STATUSB_IP11
mdefine_line|#define  STATUSB_IP11&t;&t;3
DECL|macro|STATUSF_IP11
mdefine_line|#define  STATUSF_IP11&t;&t;(1   &lt;&lt; 3)
DECL|macro|STATUSB_IP12
mdefine_line|#define  STATUSB_IP12&t;&t;4
DECL|macro|STATUSF_IP12
mdefine_line|#define  STATUSF_IP12&t;&t;(1   &lt;&lt; 4)
DECL|macro|STATUSB_IP13
mdefine_line|#define  STATUSB_IP13&t;&t;5
DECL|macro|STATUSF_IP13
mdefine_line|#define  STATUSF_IP13&t;&t;(1   &lt;&lt; 5)
DECL|macro|STATUSB_IP14
mdefine_line|#define  STATUSB_IP14&t;&t;6
DECL|macro|STATUSF_IP14
mdefine_line|#define  STATUSF_IP14&t;&t;(1   &lt;&lt; 6)
DECL|macro|STATUSB_IP15
mdefine_line|#define  STATUSB_IP15&t;&t;7
DECL|macro|STATUSF_IP15
mdefine_line|#define  STATUSF_IP15&t;&t;(1   &lt;&lt; 7)
DECL|macro|ST0_CH
mdefine_line|#define ST0_CH&t;&t;&t;0x00040000
DECL|macro|ST0_SR
mdefine_line|#define ST0_SR&t;&t;&t;0x00100000
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
mdefine_line|#define  CAUSEF_EXCCODE&t;&t;(31  &lt;&lt;  2)
DECL|macro|CAUSEB_IP
mdefine_line|#define  CAUSEB_IP&t;&t;8
DECL|macro|CAUSEF_IP
mdefine_line|#define  CAUSEF_IP&t;&t;(255 &lt;&lt;  8)
DECL|macro|CAUSEB_IP0
mdefine_line|#define  CAUSEB_IP0&t;&t;8
DECL|macro|CAUSEF_IP0
mdefine_line|#define  CAUSEF_IP0&t;&t;(1   &lt;&lt;  8)
DECL|macro|CAUSEB_IP1
mdefine_line|#define  CAUSEB_IP1&t;&t;9
DECL|macro|CAUSEF_IP1
mdefine_line|#define  CAUSEF_IP1&t;&t;(1   &lt;&lt;  9)
DECL|macro|CAUSEB_IP2
mdefine_line|#define  CAUSEB_IP2&t;&t;10
DECL|macro|CAUSEF_IP2
mdefine_line|#define  CAUSEF_IP2&t;&t;(1   &lt;&lt; 10)
DECL|macro|CAUSEB_IP3
mdefine_line|#define  CAUSEB_IP3&t;&t;11
DECL|macro|CAUSEF_IP3
mdefine_line|#define  CAUSEF_IP3&t;&t;(1   &lt;&lt; 11)
DECL|macro|CAUSEB_IP4
mdefine_line|#define  CAUSEB_IP4&t;&t;12
DECL|macro|CAUSEF_IP4
mdefine_line|#define  CAUSEF_IP4&t;&t;(1   &lt;&lt; 12)
DECL|macro|CAUSEB_IP5
mdefine_line|#define  CAUSEB_IP5&t;&t;13
DECL|macro|CAUSEF_IP5
mdefine_line|#define  CAUSEF_IP5&t;&t;(1   &lt;&lt; 13)
DECL|macro|CAUSEB_IP6
mdefine_line|#define  CAUSEB_IP6&t;&t;14
DECL|macro|CAUSEF_IP6
mdefine_line|#define  CAUSEF_IP6&t;&t;(1   &lt;&lt; 14)
DECL|macro|CAUSEB_IP7
mdefine_line|#define  CAUSEB_IP7&t;&t;15
DECL|macro|CAUSEF_IP7
mdefine_line|#define  CAUSEF_IP7&t;&t;(1   &lt;&lt; 15)
DECL|macro|CAUSEB_IV
mdefine_line|#define  CAUSEB_IV&t;&t;23
DECL|macro|CAUSEF_IV
mdefine_line|#define  CAUSEF_IV&t;&t;(1   &lt;&lt; 23)
DECL|macro|CAUSEB_CE
mdefine_line|#define  CAUSEB_CE&t;&t;28
DECL|macro|CAUSEF_CE
mdefine_line|#define  CAUSEF_CE&t;&t;(3   &lt;&lt; 28)
DECL|macro|CAUSEB_BD
mdefine_line|#define  CAUSEB_BD&t;&t;31
DECL|macro|CAUSEF_BD
mdefine_line|#define  CAUSEF_BD&t;&t;(1   &lt;&lt; 31)
multiline_comment|/*&n; * Bits in the coprozessor 0 config register.&n; */
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
DECL|macro|CONF_DB
mdefine_line|#define CONF_DB&t;&t;&t;&t;(1 &lt;&lt;  4)
DECL|macro|CONF_IB
mdefine_line|#define CONF_IB&t;&t;&t;&t;(1 &lt;&lt;  5)
DECL|macro|CONF_SC
mdefine_line|#define CONF_SC&t;&t;&t;&t;(1 &lt;&lt; 17)
DECL|macro|CONF_AC
mdefine_line|#define CONF_AC                         (1 &lt;&lt; 23)
DECL|macro|CONF_HALT
mdefine_line|#define CONF_HALT                       (1 &lt;&lt; 25)
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
multiline_comment|/*&n; * These flags define in which priviledge mode the counters count events&n; */
DECL|macro|CEB_USER
mdefine_line|#define CEB_USER&t;8&t;/* Count events in user mode, EXL = ERL = 0 */
DECL|macro|CEB_SUPERVISOR
mdefine_line|#define CEB_SUPERVISOR&t;4&t;/* Count events in supvervisor mode EXL = ERL = 0 */
DECL|macro|CEB_KERNEL
mdefine_line|#define CEB_KERNEL&t;2&t;/* Count events in kernel mode EXL = ERL = 0 */
DECL|macro|CEB_EXL
mdefine_line|#define CEB_EXL&t;&t;1&t;/* Count events with EXL = 1, ERL = 0 */
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Functions to access the performance counter and control registers&n; */
r_extern
id|asmlinkage
r_int
r_int
id|read_perf_cntr
c_func
(paren
r_int
r_int
id|counter
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|write_perf_cntr
c_func
(paren
r_int
r_int
id|counter
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
r_int
id|read_perf_cntl
c_func
(paren
r_int
r_int
id|counter
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|write_perf_cntl
c_func
(paren
r_int
r_int
id|counter
comma
r_int
r_int
id|val
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_MIPSREGS_H */
eof
