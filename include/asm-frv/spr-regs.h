multiline_comment|/* spr-regs.h: special-purpose registers on the FRV&n; *&n; * Copyright (C) 2003, 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SPR_REGS_H
DECL|macro|_ASM_SPR_REGS_H
mdefine_line|#define _ASM_SPR_REGS_H
multiline_comment|/*&n; * PSR - Processor Status Register&n; */
DECL|macro|PSR_ET
mdefine_line|#define PSR_ET&t;&t;&t;0x00000001&t;/* enable interrupts/exceptions flag */
DECL|macro|PSR_PS
mdefine_line|#define PSR_PS&t;&t;&t;0x00000002&t;/* previous supervisor mode flag */
DECL|macro|PSR_S
mdefine_line|#define PSR_S&t;&t;&t;0x00000004&t;/* supervisor mode flag */
DECL|macro|PSR_PIL
mdefine_line|#define PSR_PIL&t;&t;&t;0x00000078&t;/* processor external interrupt level */
DECL|macro|PSR_PIL_0
mdefine_line|#define PSR_PIL_0&t;&t;0x00000000&t;/* - no interrupt in progress */
DECL|macro|PSR_PIL_13
mdefine_line|#define PSR_PIL_13&t;&t;0x00000068&t;/* - debugging only */
DECL|macro|PSR_PIL_14
mdefine_line|#define PSR_PIL_14&t;&t;0x00000070&t;/* - debugging in progress */
DECL|macro|PSR_PIL_15
mdefine_line|#define PSR_PIL_15&t;&t;0x00000078&t;/* - NMI in progress */
DECL|macro|PSR_EM
mdefine_line|#define PSR_EM&t;&t;&t;0x00000080&t;/* enable media operation */
DECL|macro|PSR_EF
mdefine_line|#define PSR_EF&t;&t;&t;0x00000100&t;/* enable FPU operation */
DECL|macro|PSR_BE
mdefine_line|#define PSR_BE&t;&t;&t;0x00001000&t;/* endianness mode */
DECL|macro|PSR_BE_LE
mdefine_line|#define PSR_BE_LE&t;&t;0x00000000&t;/* - little endian mode */
DECL|macro|PSR_BE_BE
mdefine_line|#define PSR_BE_BE&t;&t;0x00001000&t;/* - big endian mode */
DECL|macro|PSR_CM
mdefine_line|#define PSR_CM&t;&t;&t;0x00002000&t;/* conditional mode */
DECL|macro|PSR_NEM
mdefine_line|#define PSR_NEM&t;&t;&t;0x00004000&t;/* non-excepting mode */
DECL|macro|PSR_ICE
mdefine_line|#define PSR_ICE&t;&t;&t;0x00010000&t;/* in-circuit emulation mode */
DECL|macro|PSR_VERSION_SHIFT
mdefine_line|#define PSR_VERSION_SHIFT&t;24&t;&t;/* CPU silicon ID */
DECL|macro|PSR_IMPLE_SHIFT
mdefine_line|#define PSR_IMPLE_SHIFT&t;&t;28&t;&t;/* CPU core ID */
DECL|macro|PSR_VERSION
mdefine_line|#define PSR_VERSION(psr)&t;(((psr) &gt;&gt; PSR_VERSION_SHIFT) &amp; 0xf)
DECL|macro|PSR_IMPLE
mdefine_line|#define PSR_IMPLE(psr)&t;&t;(((psr) &gt;&gt; PSR_IMPLE_SHIFT) &amp; 0xf)
DECL|macro|PSR_IMPLE_FR401
mdefine_line|#define PSR_IMPLE_FR401&t;&t;0x2
DECL|macro|PSR_VERSION_FR401_MB93401
mdefine_line|#define PSR_VERSION_FR401_MB93401&t;0x0
DECL|macro|PSR_VERSION_FR401_MB93401A
mdefine_line|#define PSR_VERSION_FR401_MB93401A&t;0x1
DECL|macro|PSR_VERSION_FR401_MB93403
mdefine_line|#define PSR_VERSION_FR401_MB93403&t;0x2
DECL|macro|PSR_IMPLE_FR405
mdefine_line|#define PSR_IMPLE_FR405&t;&t;0x4
DECL|macro|PSR_VERSION_FR405_MB93405
mdefine_line|#define PSR_VERSION_FR405_MB93405&t;0x0
DECL|macro|PSR_IMPLE_FR451
mdefine_line|#define PSR_IMPLE_FR451&t;&t;0x5
DECL|macro|PSR_VERSION_FR451_MB93451
mdefine_line|#define PSR_VERSION_FR451_MB93451&t;0x0
DECL|macro|PSR_IMPLE_FR501
mdefine_line|#define PSR_IMPLE_FR501&t;&t;0x1
DECL|macro|PSR_VERSION_FR501_MB93501
mdefine_line|#define PSR_VERSION_FR501_MB93501&t;0x1
DECL|macro|PSR_VERSION_FR501_MB93501A
mdefine_line|#define PSR_VERSION_FR501_MB93501A&t;0x2
DECL|macro|PSR_IMPLE_FR551
mdefine_line|#define PSR_IMPLE_FR551&t;&t;0x3
DECL|macro|PSR_VERSION_FR551_MB93555
mdefine_line|#define PSR_VERSION_FR551_MB93555&t;0x1
DECL|macro|__get_PSR
mdefine_line|#define __get_PSR()&t;({ unsigned long x; asm volatile(&quot;movsg psr,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__set_PSR
mdefine_line|#define __set_PSR(V)&t;do { asm volatile(&quot;movgs %0,psr&quot; : : &quot;r&quot;(V)); } while(0)
multiline_comment|/*&n; * TBR - Trap Base Register&n; */
DECL|macro|TBR_TT
mdefine_line|#define TBR_TT&t;&t;&t;0x00000ff0
DECL|macro|TBR_TT_INSTR_MMU_MISS
mdefine_line|#define TBR_TT_INSTR_MMU_MISS&t;(0x01 &lt;&lt; 4)
DECL|macro|TBR_TT_INSTR_ACC_ERROR
mdefine_line|#define TBR_TT_INSTR_ACC_ERROR&t;(0x02 &lt;&lt; 4)
DECL|macro|TBR_TT_INSTR_ACC_EXCEP
mdefine_line|#define TBR_TT_INSTR_ACC_EXCEP&t;(0x03 &lt;&lt; 4)
DECL|macro|TBR_TT_PRIV_INSTR
mdefine_line|#define TBR_TT_PRIV_INSTR&t;(0x06 &lt;&lt; 4)
DECL|macro|TBR_TT_ILLEGAL_INSTR
mdefine_line|#define TBR_TT_ILLEGAL_INSTR&t;(0x07 &lt;&lt; 4)
DECL|macro|TBR_TT_FP_EXCEPTION
mdefine_line|#define TBR_TT_FP_EXCEPTION&t;(0x0d &lt;&lt; 4)
DECL|macro|TBR_TT_MP_EXCEPTION
mdefine_line|#define TBR_TT_MP_EXCEPTION&t;(0x0e &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_ACC_ERROR
mdefine_line|#define TBR_TT_DATA_ACC_ERROR&t;(0x11 &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_MMU_MISS
mdefine_line|#define TBR_TT_DATA_MMU_MISS&t;(0x12 &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_ACC_EXCEP
mdefine_line|#define TBR_TT_DATA_ACC_EXCEP&t;(0x13 &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_STR_ERROR
mdefine_line|#define TBR_TT_DATA_STR_ERROR&t;(0x14 &lt;&lt; 4)
DECL|macro|TBR_TT_DIVISION_EXCEP
mdefine_line|#define TBR_TT_DIVISION_EXCEP&t;(0x17 &lt;&lt; 4)
DECL|macro|TBR_TT_COMMIT_EXCEP
mdefine_line|#define TBR_TT_COMMIT_EXCEP&t;(0x19 &lt;&lt; 4)
DECL|macro|TBR_TT_INSTR_TLB_MISS
mdefine_line|#define TBR_TT_INSTR_TLB_MISS&t;(0x1a &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_TLB_MISS
mdefine_line|#define TBR_TT_DATA_TLB_MISS&t;(0x1b &lt;&lt; 4)
DECL|macro|TBR_TT_DATA_DAT_EXCEP
mdefine_line|#define TBR_TT_DATA_DAT_EXCEP&t;(0x1d &lt;&lt; 4)
DECL|macro|TBR_TT_DECREMENT_TIMER
mdefine_line|#define TBR_TT_DECREMENT_TIMER&t;(0x1f &lt;&lt; 4)
DECL|macro|TBR_TT_COMPOUND_EXCEP
mdefine_line|#define TBR_TT_COMPOUND_EXCEP&t;(0x20 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_1
mdefine_line|#define TBR_TT_INTERRUPT_1&t;(0x21 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_2
mdefine_line|#define TBR_TT_INTERRUPT_2&t;(0x22 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_3
mdefine_line|#define TBR_TT_INTERRUPT_3&t;(0x23 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_4
mdefine_line|#define TBR_TT_INTERRUPT_4&t;(0x24 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_5
mdefine_line|#define TBR_TT_INTERRUPT_5&t;(0x25 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_6
mdefine_line|#define TBR_TT_INTERRUPT_6&t;(0x26 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_7
mdefine_line|#define TBR_TT_INTERRUPT_7&t;(0x27 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_8
mdefine_line|#define TBR_TT_INTERRUPT_8&t;(0x28 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_9
mdefine_line|#define TBR_TT_INTERRUPT_9&t;(0x29 &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_10
mdefine_line|#define TBR_TT_INTERRUPT_10&t;(0x2a &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_11
mdefine_line|#define TBR_TT_INTERRUPT_11&t;(0x2b &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_12
mdefine_line|#define TBR_TT_INTERRUPT_12&t;(0x2c &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_13
mdefine_line|#define TBR_TT_INTERRUPT_13&t;(0x2d &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_14
mdefine_line|#define TBR_TT_INTERRUPT_14&t;(0x2e &lt;&lt; 4)
DECL|macro|TBR_TT_INTERRUPT_15
mdefine_line|#define TBR_TT_INTERRUPT_15&t;(0x2f &lt;&lt; 4)
DECL|macro|TBR_TT_TRAP0
mdefine_line|#define TBR_TT_TRAP0&t;&t;(0x80 &lt;&lt; 4)
DECL|macro|TBR_TT_TRAP1
mdefine_line|#define TBR_TT_TRAP1&t;&t;(0x81 &lt;&lt; 4)
DECL|macro|TBR_TT_TRAP2
mdefine_line|#define TBR_TT_TRAP2&t;&t;(0x82 &lt;&lt; 4)
DECL|macro|TBR_TT_TRAP126
mdefine_line|#define TBR_TT_TRAP126&t;&t;(0xfe &lt;&lt; 4)
DECL|macro|TBR_TT_BREAK
mdefine_line|#define TBR_TT_BREAK&t;&t;(0xff &lt;&lt; 4)
DECL|macro|__get_TBR
mdefine_line|#define __get_TBR()&t;({ unsigned long x; asm volatile(&quot;movsg tbr,%0&quot; : &quot;=r&quot;(x)); x; })
multiline_comment|/*&n; * HSR0 - Hardware Status Register 0&n; */
DECL|macro|HSR0_PDM
mdefine_line|#define HSR0_PDM&t;&t;0x00000007&t;/* power down mode */
DECL|macro|HSR0_PDM_NORMAL
mdefine_line|#define HSR0_PDM_NORMAL&t;&t;0x00000000&t;/* - normal mode */
DECL|macro|HSR0_PDM_CORE_SLEEP
mdefine_line|#define HSR0_PDM_CORE_SLEEP&t;0x00000001&t;/* - CPU core sleep mode */
DECL|macro|HSR0_PDM_BUS_SLEEP
mdefine_line|#define HSR0_PDM_BUS_SLEEP&t;0x00000003&t;/* - bus sleep mode */
DECL|macro|HSR0_PDM_PLL_RUN
mdefine_line|#define HSR0_PDM_PLL_RUN&t;0x00000005&t;/* - PLL run */
DECL|macro|HSR0_PDM_PLL_STOP
mdefine_line|#define HSR0_PDM_PLL_STOP&t;0x00000007&t;/* - PLL stop */
DECL|macro|HSR0_GRLE
mdefine_line|#define HSR0_GRLE&t;&t;0x00000040&t;/* GR lower register set enable */
DECL|macro|HSR0_GRHE
mdefine_line|#define HSR0_GRHE&t;&t;0x00000080&t;/* GR higher register set enable */
DECL|macro|HSR0_FRLE
mdefine_line|#define HSR0_FRLE&t;&t;0x00000100&t;/* FR lower register set enable */
DECL|macro|HSR0_FRHE
mdefine_line|#define HSR0_FRHE&t;&t;0x00000200&t;/* FR higher register set enable */
DECL|macro|HSR0_GRN
mdefine_line|#define HSR0_GRN&t;&t;0x00000400&t;/* GR quantity */
DECL|macro|HSR0_GRN_64
mdefine_line|#define HSR0_GRN_64&t;&t;0x00000000&t;/* - 64 GR registers */
DECL|macro|HSR0_GRN_32
mdefine_line|#define HSR0_GRN_32&t;&t;0x00000400&t;/* - 32 GR registers */
DECL|macro|HSR0_FRN
mdefine_line|#define HSR0_FRN&t;&t;0x00000800&t;/* FR quantity */
DECL|macro|HSR0_FRN_64
mdefine_line|#define HSR0_FRN_64&t;&t;0x00000000&t;/* - 64 FR registers */
DECL|macro|HSR0_FRN_32
mdefine_line|#define HSR0_FRN_32&t;&t;0x00000800&t;/* - 32 FR registers */
DECL|macro|HSR0_SA
mdefine_line|#define HSR0_SA&t;&t;&t;0x00001000&t;/* start address (RAMBOOT#) */
DECL|macro|HSR0_ETMI
mdefine_line|#define HSR0_ETMI&t;&t;0x00008000&t;/* enable TIMERI (64-bit up timer) */
DECL|macro|HSR0_ETMD
mdefine_line|#define HSR0_ETMD&t;&t;0x00004000&t;/* enable TIMERD (32-bit down timer) */
DECL|macro|HSR0_PEDAT
mdefine_line|#define HSR0_PEDAT&t;&t;0x00010000&t;/* previous DAT mode */
DECL|macro|HSR0_XEDAT
mdefine_line|#define HSR0_XEDAT&t;&t;0x00020000&t;/* exception DAT mode */
DECL|macro|HSR0_EDAT
mdefine_line|#define HSR0_EDAT&t;&t;0x00080000&t;/* enable DAT mode */
DECL|macro|HSR0_RME
mdefine_line|#define HSR0_RME&t;&t;0x00400000&t;/* enable RAM mode */
DECL|macro|HSR0_EMEM
mdefine_line|#define HSR0_EMEM&t;&t;0x00800000&t;/* enable MMU_Miss mask */
DECL|macro|HSR0_EXMMU
mdefine_line|#define HSR0_EXMMU&t;&t;0x01000000&t;/* enable extended MMU mode */
DECL|macro|HSR0_EDMMU
mdefine_line|#define HSR0_EDMMU&t;&t;0x02000000&t;/* enable data MMU */
DECL|macro|HSR0_EIMMU
mdefine_line|#define HSR0_EIMMU&t;&t;0x04000000&t;/* enable instruction MMU */
DECL|macro|HSR0_CBM
mdefine_line|#define HSR0_CBM&t;&t;0x08000000&t;/* copy back mode */
DECL|macro|HSR0_CBM_WRITE_THRU
mdefine_line|#define HSR0_CBM_WRITE_THRU&t;0x00000000&t;/* - write through */
DECL|macro|HSR0_CBM_COPY_BACK
mdefine_line|#define HSR0_CBM_COPY_BACK&t;0x08000000&t;/* - copy back */
DECL|macro|HSR0_NWA
mdefine_line|#define HSR0_NWA&t;&t;0x10000000&t;/* no write allocate */
DECL|macro|HSR0_DCE
mdefine_line|#define HSR0_DCE&t;&t;0x40000000&t;/* data cache enable */
DECL|macro|HSR0_ICE
mdefine_line|#define HSR0_ICE&t;&t;0x80000000&t;/* instruction cache enable */
DECL|macro|__get_HSR
mdefine_line|#define __get_HSR(R)&t;({ unsigned long x; asm volatile(&quot;movsg hsr&quot;#R&quot;,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__set_HSR
mdefine_line|#define __set_HSR(R,V)&t;do { asm volatile(&quot;movgs %0,hsr&quot;#R : : &quot;r&quot;(V)); } while(0)
multiline_comment|/*&n; * CCR - Condition Codes Register&n; */
DECL|macro|CCR_FCC0
mdefine_line|#define CCR_FCC0&t;&t;0x0000000f&t;/* FP/Media condition 0 (fcc0 reg) */
DECL|macro|CCR_FCC1
mdefine_line|#define CCR_FCC1&t;&t;0x000000f0&t;/* FP/Media condition 1 (fcc1 reg) */
DECL|macro|CCR_FCC2
mdefine_line|#define CCR_FCC2&t;&t;0x00000f00&t;/* FP/Media condition 2 (fcc2 reg) */
DECL|macro|CCR_FCC3
mdefine_line|#define CCR_FCC3&t;&t;0x0000f000&t;/* FP/Media condition 3 (fcc3 reg) */
DECL|macro|CCR_ICC0
mdefine_line|#define CCR_ICC0&t;&t;0x000f0000&t;/* Integer condition 0 (icc0 reg) */
DECL|macro|CCR_ICC0_C
mdefine_line|#define CCR_ICC0_C&t;&t;0x00010000&t;/* - Carry flag */
DECL|macro|CCR_ICC0_V
mdefine_line|#define CCR_ICC0_V&t;&t;0x00020000&t;/* - Overflow flag */
DECL|macro|CCR_ICC0_Z
mdefine_line|#define CCR_ICC0_Z&t;&t;0x00040000&t;/* - Zero flag */
DECL|macro|CCR_ICC0_N
mdefine_line|#define CCR_ICC0_N&t;&t;0x00080000&t;/* - Negative flag */
DECL|macro|CCR_ICC1
mdefine_line|#define CCR_ICC1&t;&t;0x00f00000&t;/* Integer condition 1 (icc1 reg) */
DECL|macro|CCR_ICC2
mdefine_line|#define CCR_ICC2&t;&t;0x0f000000&t;/* Integer condition 2 (icc2 reg) */
DECL|macro|CCR_ICC3
mdefine_line|#define CCR_ICC3&t;&t;0xf0000000&t;/* Integer condition 3 (icc3 reg) */
multiline_comment|/*&n; * CCCR - Condition Codes for Conditional Instructions Register&n; */
DECL|macro|CCCR_CC0
mdefine_line|#define CCCR_CC0&t;&t;0x00000003&t;/* condition 0 (cc0 reg) */
DECL|macro|CCCR_CC0_FALSE
mdefine_line|#define CCCR_CC0_FALSE&t;&t;0x00000002&t;/* - condition is false */
DECL|macro|CCCR_CC0_TRUE
mdefine_line|#define CCCR_CC0_TRUE&t;&t;0x00000003&t;/* - condition is true */
DECL|macro|CCCR_CC1
mdefine_line|#define CCCR_CC1&t;&t;0x0000000c&t;/* condition 1 (cc1 reg) */
DECL|macro|CCCR_CC2
mdefine_line|#define CCCR_CC2&t;&t;0x00000030&t;/* condition 2 (cc2 reg) */
DECL|macro|CCCR_CC3
mdefine_line|#define CCCR_CC3&t;&t;0x000000c0&t;/* condition 3 (cc3 reg) */
DECL|macro|CCCR_CC4
mdefine_line|#define CCCR_CC4&t;&t;0x00000300&t;/* condition 4 (cc4 reg) */
DECL|macro|CCCR_CC5
mdefine_line|#define CCCR_CC5&t;&t;0x00000c00&t;/* condition 5 (cc5 reg) */
DECL|macro|CCCR_CC6
mdefine_line|#define CCCR_CC6&t;&t;0x00003000&t;/* condition 6 (cc6 reg) */
DECL|macro|CCCR_CC7
mdefine_line|#define CCCR_CC7&t;&t;0x0000c000&t;/* condition 7 (cc7 reg) */
multiline_comment|/*&n; * ISR - Integer Status Register&n; */
DECL|macro|ISR_EMAM
mdefine_line|#define ISR_EMAM&t;&t;0x00000001&t;/* memory misaligned access handling */
DECL|macro|ISR_EMAM_EXCEPTION
mdefine_line|#define ISR_EMAM_EXCEPTION&t;0x00000000&t;/* - generate exception */
DECL|macro|ISR_EMAM_FUDGE
mdefine_line|#define ISR_EMAM_FUDGE&t;&t;0x00000001&t;/* - mask out invalid address bits */
DECL|macro|ISR_AEXC
mdefine_line|#define ISR_AEXC&t;&t;0x00000004&t;/* accrued [overflow] exception */
DECL|macro|ISR_DTT
mdefine_line|#define ISR_DTT&t;&t;&t;0x00000018&t;/* division type trap */
DECL|macro|ISR_DTT_IGNORE
mdefine_line|#define ISR_DTT_IGNORE&t;&t;0x00000000&t;/* - ignore division error */
DECL|macro|ISR_DTT_DIVBYZERO
mdefine_line|#define ISR_DTT_DIVBYZERO&t;0x00000008&t;/* - generate exception */
DECL|macro|ISR_DTT_OVERFLOW
mdefine_line|#define ISR_DTT_OVERFLOW&t;0x00000010&t;/* - record overflow */
DECL|macro|ISR_EDE
mdefine_line|#define ISR_EDE&t;&t;&t;0x00000020&t;/* enable division exception */
DECL|macro|ISR_PLI
mdefine_line|#define ISR_PLI&t;&t;&t;0x20000000&t;/* pre-load instruction information */
DECL|macro|ISR_QI
mdefine_line|#define ISR_QI&t;&t;&t;0x80000000&t;/* quad data implementation information */
multiline_comment|/*&n; * EPCR0 - Exception PC Register&n; */
DECL|macro|EPCR0_V
mdefine_line|#define EPCR0_V&t;&t;&t;0x00000001&t;/* register content validity indicator */
DECL|macro|EPCR0_PC
mdefine_line|#define EPCR0_PC&t;&t;0xfffffffc&t;/* faulting instruction address */
multiline_comment|/*&n; * ESR0/14/15 - Exception Status Register&n; */
DECL|macro|ESRx_VALID
mdefine_line|#define ESRx_VALID&t;&t;0x00000001&t;/* register content validity indicator */
DECL|macro|ESRx_EC
mdefine_line|#define ESRx_EC&t;&t;&t;0x0000003e&t;/* exception type */
DECL|macro|ESRx_EC_DATA_STORE
mdefine_line|#define ESRx_EC_DATA_STORE&t;0x00000000&t;/* - data_store_error */
DECL|macro|ESRx_EC_INSN_ACCESS
mdefine_line|#define ESRx_EC_INSN_ACCESS&t;0x00000006&t;/* - instruction_access_error */
DECL|macro|ESRx_EC_PRIV_INSN
mdefine_line|#define ESRx_EC_PRIV_INSN&t;0x00000008&t;/* - privileged_instruction */
DECL|macro|ESRx_EC_ILL_INSN
mdefine_line|#define ESRx_EC_ILL_INSN&t;0x0000000a&t;/* - illegal_instruction */
DECL|macro|ESRx_EC_MP_EXCEP
mdefine_line|#define ESRx_EC_MP_EXCEP&t;0x0000001c&t;/* - mp_exception */
DECL|macro|ESRx_EC_DATA_ACCESS
mdefine_line|#define ESRx_EC_DATA_ACCESS&t;0x00000024&t;/* - data_access_error */
DECL|macro|ESRx_EC_DIVISION
mdefine_line|#define ESRx_EC_DIVISION&t;0x00000026&t;/* - division_exception */
DECL|macro|ESRx_EC_ITLB_MISS
mdefine_line|#define ESRx_EC_ITLB_MISS&t;0x00000034&t;/* - instruction_access_TLB_miss */
DECL|macro|ESRx_EC_DTLB_MISS
mdefine_line|#define ESRx_EC_DTLB_MISS&t;0x00000036&t;/* - data_access_TLB_miss */
DECL|macro|ESRx_EC_DATA_ACCESS_DAT
mdefine_line|#define ESRx_EC_DATA_ACCESS_DAT&t;0x0000003a&t;/* - data_access_DAT_exception */
DECL|macro|ESR0_IAEC
mdefine_line|#define ESR0_IAEC&t;&t;0x00000100&t;/* info for instruction-access-exception */
DECL|macro|ESR0_IAEC_RESV
mdefine_line|#define ESR0_IAEC_RESV&t;&t;0x00000000&t;/* - reserved */
DECL|macro|ESR0_IAEC_PROT_VIOL
mdefine_line|#define ESR0_IAEC_PROT_VIOL&t;0x00000100&t;/* - protection violation */
DECL|macro|ESR0_ATXC
mdefine_line|#define ESR0_ATXC&t;&t;0x00f00000&t;/* address translation exception code */
DECL|macro|ESR0_ATXC_MMU_MISS
mdefine_line|#define ESR0_ATXC_MMU_MISS&t;0x00000000&t;/* - MMU miss exception and more (?) */
DECL|macro|ESR0_ATXC_MULTI_DAT
mdefine_line|#define ESR0_ATXC_MULTI_DAT&t;0x00800000&t;/* - multiple DAT entry hit */
DECL|macro|ESR0_ATXC_MULTI_SAT
mdefine_line|#define ESR0_ATXC_MULTI_SAT&t;0x00900000&t;/* - multiple SAT entry hit */
DECL|macro|ESR0_ATXC_AMRTLB_MISS
mdefine_line|#define ESR0_ATXC_AMRTLB_MISS&t;0x00a00000&t;/* - MMU/TLB miss exception */
DECL|macro|ESR0_ATXC_PRIV_EXCEP
mdefine_line|#define ESR0_ATXC_PRIV_EXCEP&t;0x00c00000&t;/* - privilege protection fault */
DECL|macro|ESR0_ATXC_WP_EXCEP
mdefine_line|#define ESR0_ATXC_WP_EXCEP&t;0x00d00000&t;/* - write protection fault */
DECL|macro|ESR0_EAV
mdefine_line|#define ESR0_EAV&t;&t;0x00000800&t;/* true if EAR0 register valid */
DECL|macro|ESR15_EAV
mdefine_line|#define ESR15_EAV&t;&t;0x00000800&t;/* true if EAR15 register valid */
multiline_comment|/*&n; * ESFR1 - Exception Status Valid Flag Register&n; */
DECL|macro|ESFR1_ESR0
mdefine_line|#define ESFR1_ESR0&t;&t;0x00000001&t;/* true if ESR0 is valid */
DECL|macro|ESFR1_ESR14
mdefine_line|#define ESFR1_ESR14&t;&t;0x00004000&t;/* true if ESR14 is valid */
DECL|macro|ESFR1_ESR15
mdefine_line|#define ESFR1_ESR15&t;&t;0x00008000&t;/* true if ESR15 is valid */
multiline_comment|/*&n; * MSR - Media Status Register&n; */
DECL|macro|MSR0_AOVF
mdefine_line|#define MSR0_AOVF&t;&t;0x00000001&t;/* overflow exception accrued */
DECL|macro|MSRx_OVF
mdefine_line|#define MSRx_OVF&t;&t;0x00000002&t;/* overflow exception detected */
DECL|macro|MSRx_SIE
mdefine_line|#define MSRx_SIE&t;&t;0x0000003c&t;/* last SIMD instruction exception detected */
DECL|macro|MSRx_SIE_NONE
mdefine_line|#define MSRx_SIE_NONE&t;&t;0x00000000&t;/* - none detected */
DECL|macro|MSRx_SIE_FRkHI_ACCk
mdefine_line|#define MSRx_SIE_FRkHI_ACCk&t;0x00000020&t;/* - exception at FRkHI or ACCk */
DECL|macro|MSRx_SIE_FRkLO_ACCk1
mdefine_line|#define MSRx_SIE_FRkLO_ACCk1&t;0x00000010&t;/* - exception at FRkLO or ACCk+1 */
DECL|macro|MSRx_SIE_FRk1HI_ACCk2
mdefine_line|#define MSRx_SIE_FRk1HI_ACCk2&t;0x00000008&t;/* - exception at FRk+1HI or ACCk+2 */
DECL|macro|MSRx_SIE_FRk1LO_ACCk3
mdefine_line|#define MSRx_SIE_FRk1LO_ACCk3&t;0x00000004&t;/* - exception at FRk+1LO or ACCk+3 */
DECL|macro|MSR0_MTT
mdefine_line|#define MSR0_MTT&t;&t;0x00007000&t;/* type of last media trap detected */
DECL|macro|MSR0_MTT_NONE
mdefine_line|#define MSR0_MTT_NONE&t;&t;0x00000000&t;/* - none detected */
DECL|macro|MSR0_MTT_OVERFLOW
mdefine_line|#define MSR0_MTT_OVERFLOW&t;0x00001000&t;/* - overflow detected */
DECL|macro|MSR0_HI
mdefine_line|#define MSR0_HI&t;&t;&t;0x00c00000&t;/* hardware implementation */
DECL|macro|MSR0_HI_ROUNDING
mdefine_line|#define MSR0_HI_ROUNDING&t;0x00000000&t;/* - rounding mode */
DECL|macro|MSR0_HI_NONROUNDING
mdefine_line|#define MSR0_HI_NONROUNDING&t;0x00c00000&t;/* - non-rounding mode */
DECL|macro|MSR0_EMCI
mdefine_line|#define MSR0_EMCI&t;&t;0x01000000&t;/* enable media custom instructions */
DECL|macro|MSR0_SRDAV
mdefine_line|#define MSR0_SRDAV&t;&t;0x10000000&t;/* select rounding mode of MAVEH */
DECL|macro|MSR0_SRDAV_RDAV
mdefine_line|#define MSR0_SRDAV_RDAV&t;&t;0x00000000&t;/* - controlled by MSR.RDAV */
DECL|macro|MSR0_SRDAV_RD
mdefine_line|#define MSR0_SRDAV_RD&t;&t;0x10000000&t;/* - controlled by MSR.RD */
DECL|macro|MSR0_RDAV
mdefine_line|#define MSR0_RDAV&t;&t;0x20000000&t;/* rounding mode of MAVEH */
DECL|macro|MSR0_RDAV_NEAREST_MI
mdefine_line|#define MSR0_RDAV_NEAREST_MI&t;0x00000000&t;/* - round to nearest minus */
DECL|macro|MSR0_RDAV_NEAREST_PL
mdefine_line|#define MSR0_RDAV_NEAREST_PL&t;0x20000000&t;/* - round to nearest plus */
DECL|macro|MSR0_RD
mdefine_line|#define MSR0_RD&t;&t;&t;0xc0000000&t;/* rounding mode */
DECL|macro|MSR0_RD_NEAREST
mdefine_line|#define MSR0_RD_NEAREST&t;&t;0x00000000&t;/* - nearest */
DECL|macro|MSR0_RD_ZERO
mdefine_line|#define MSR0_RD_ZERO&t;&t;0x40000000&t;/* - zero */
DECL|macro|MSR0_RD_POS_INF
mdefine_line|#define MSR0_RD_POS_INF&t;&t;0x80000000&t;/* - postive infinity */
DECL|macro|MSR0_RD_NEG_INF
mdefine_line|#define MSR0_RD_NEG_INF&t;&t;0xc0000000&t;/* - negative infinity */
multiline_comment|/*&n; * IAMPR0-7 - Instruction Address Mapping Register&n; * DAMPR0-7 - Data Address Mapping Register&n; */
DECL|macro|xAMPRx_V
mdefine_line|#define xAMPRx_V&t;&t;0x00000001&t;/* register content validity indicator */
DECL|macro|DAMPRx_WP
mdefine_line|#define DAMPRx_WP&t;&t;0x00000002&t;/* write protect */
DECL|macro|DAMPRx_WP_RW
mdefine_line|#define DAMPRx_WP_RW&t;&t;0x00000000&t;/* - read/write */
DECL|macro|DAMPRx_WP_RO
mdefine_line|#define DAMPRx_WP_RO&t;&t;0x00000002&t;/* - read-only */
DECL|macro|xAMPRx_C
mdefine_line|#define xAMPRx_C&t;&t;0x00000004&t;/* cached/uncached */
DECL|macro|xAMPRx_C_CACHED
mdefine_line|#define xAMPRx_C_CACHED&t;&t;0x00000000&t;/* - cached */
DECL|macro|xAMPRx_C_UNCACHED
mdefine_line|#define xAMPRx_C_UNCACHED&t;0x00000004&t;/* - uncached */
DECL|macro|xAMPRx_S
mdefine_line|#define xAMPRx_S&t;&t;0x00000008&t;/* supervisor only */
DECL|macro|xAMPRx_S_USER
mdefine_line|#define xAMPRx_S_USER&t;&t;0x00000000&t;/* - userspace can access */
DECL|macro|xAMPRx_S_KERNEL
mdefine_line|#define xAMPRx_S_KERNEL&t;&t;0x00000008&t;/* - kernel only */
DECL|macro|xAMPRx_SS
mdefine_line|#define xAMPRx_SS&t;&t;0x000000f0&t;/* segment size */
DECL|macro|xAMPRx_SS_16Kb
mdefine_line|#define xAMPRx_SS_16Kb&t;&t;0x00000000&t;/* - 16 kilobytes */
DECL|macro|xAMPRx_SS_64Kb
mdefine_line|#define xAMPRx_SS_64Kb&t;&t;0x00000010&t;/* - 64 kilobytes */
DECL|macro|xAMPRx_SS_256Kb
mdefine_line|#define xAMPRx_SS_256Kb&t;&t;0x00000020&t;/* - 256 kilobytes */
DECL|macro|xAMPRx_SS_1Mb
mdefine_line|#define xAMPRx_SS_1Mb&t;&t;0x00000030&t;/* - 1 megabyte */
DECL|macro|xAMPRx_SS_2Mb
mdefine_line|#define xAMPRx_SS_2Mb&t;&t;0x00000040&t;/* - 2 megabytes */
DECL|macro|xAMPRx_SS_4Mb
mdefine_line|#define xAMPRx_SS_4Mb&t;&t;0x00000050&t;/* - 4 megabytes */
DECL|macro|xAMPRx_SS_8Mb
mdefine_line|#define xAMPRx_SS_8Mb&t;&t;0x00000060&t;/* - 8 megabytes */
DECL|macro|xAMPRx_SS_16Mb
mdefine_line|#define xAMPRx_SS_16Mb&t;&t;0x00000070&t;/* - 16 megabytes */
DECL|macro|xAMPRx_SS_32Mb
mdefine_line|#define xAMPRx_SS_32Mb&t;&t;0x00000080&t;/* - 32 megabytes */
DECL|macro|xAMPRx_SS_64Mb
mdefine_line|#define xAMPRx_SS_64Mb&t;&t;0x00000090&t;/* - 64 megabytes */
DECL|macro|xAMPRx_SS_128Mb
mdefine_line|#define xAMPRx_SS_128Mb&t;&t;0x000000a0&t;/* - 128 megabytes */
DECL|macro|xAMPRx_SS_256Mb
mdefine_line|#define xAMPRx_SS_256Mb&t;&t;0x000000b0&t;/* - 256 megabytes */
DECL|macro|xAMPRx_SS_512Mb
mdefine_line|#define xAMPRx_SS_512Mb&t;&t;0x000000c0&t;/* - 512 megabytes */
DECL|macro|xAMPRx_RESERVED8
mdefine_line|#define xAMPRx_RESERVED8&t;0x00000100&t;/* reserved bit */
DECL|macro|xAMPRx_NG
mdefine_line|#define xAMPRx_NG&t;&t;0x00000200&t;/* non-global */
DECL|macro|xAMPRx_L
mdefine_line|#define xAMPRx_L&t;&t;0x00000400&t;/* locked */
DECL|macro|xAMPRx_M
mdefine_line|#define xAMPRx_M&t;&t;0x00000800&t;/* modified */
DECL|macro|xAMPRx_D
mdefine_line|#define xAMPRx_D&t;&t;0x00001000&t;/* DAT entry */
DECL|macro|xAMPRx_RESERVED13
mdefine_line|#define xAMPRx_RESERVED13&t;0x00002000&t;/* reserved bit */
DECL|macro|xAMPRx_PPFN
mdefine_line|#define xAMPRx_PPFN&t;&t;0xfff00000&t;/* physical page frame number */
DECL|macro|xAMPRx_V_BIT
mdefine_line|#define xAMPRx_V_BIT&t;&t;0
DECL|macro|DAMPRx_WP_BIT
mdefine_line|#define DAMPRx_WP_BIT&t;&t;1
DECL|macro|xAMPRx_C_BIT
mdefine_line|#define xAMPRx_C_BIT&t;&t;2
DECL|macro|xAMPRx_S_BIT
mdefine_line|#define xAMPRx_S_BIT&t;&t;3
DECL|macro|xAMPRx_RESERVED8_BIT
mdefine_line|#define xAMPRx_RESERVED8_BIT&t;8
DECL|macro|xAMPRx_NG_BIT
mdefine_line|#define xAMPRx_NG_BIT&t;&t;9
DECL|macro|xAMPRx_L_BIT
mdefine_line|#define xAMPRx_L_BIT&t;&t;10
DECL|macro|xAMPRx_M_BIT
mdefine_line|#define xAMPRx_M_BIT&t;&t;11
DECL|macro|xAMPRx_D_BIT
mdefine_line|#define xAMPRx_D_BIT&t;&t;12
DECL|macro|xAMPRx_RESERVED13_BIT
mdefine_line|#define xAMPRx_RESERVED13_BIT&t;13
DECL|macro|__get_IAMPR
mdefine_line|#define __get_IAMPR(R) ({ unsigned long x; asm volatile(&quot;movsg iampr&quot;#R&quot;,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__get_DAMPR
mdefine_line|#define __get_DAMPR(R) ({ unsigned long x; asm volatile(&quot;movsg dampr&quot;#R&quot;,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__get_IAMLR
mdefine_line|#define __get_IAMLR(R) ({ unsigned long x; asm volatile(&quot;movsg iamlr&quot;#R&quot;,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__get_DAMLR
mdefine_line|#define __get_DAMLR(R) ({ unsigned long x; asm volatile(&quot;movsg damlr&quot;#R&quot;,%0&quot; : &quot;=r&quot;(x)); x; })
DECL|macro|__set_IAMPR
mdefine_line|#define __set_IAMPR(R,V) &t;do { asm volatile(&quot;movgs %0,iampr&quot;#R : : &quot;r&quot;(V)); } while(0)
DECL|macro|__set_DAMPR
mdefine_line|#define __set_DAMPR(R,V)  &t;do { asm volatile(&quot;movgs %0,dampr&quot;#R : : &quot;r&quot;(V)); } while(0)
DECL|macro|__set_IAMLR
mdefine_line|#define __set_IAMLR(R,V) &t;do { asm volatile(&quot;movgs %0,iamlr&quot;#R : : &quot;r&quot;(V)); } while(0)
DECL|macro|__set_DAMLR
mdefine_line|#define __set_DAMLR(R,V)  &t;do { asm volatile(&quot;movgs %0,damlr&quot;#R : : &quot;r&quot;(V)); } while(0)
DECL|macro|save_dampr
mdefine_line|#define save_dampr(R, _dampr)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;movsg dampr&quot;R&quot;,%0&quot; : &quot;=r&quot;(_dampr));&t;&bslash;&n;} while(0)
DECL|macro|restore_dampr
mdefine_line|#define restore_dampr(R, _dampr)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;movgs %0,dampr&quot;R :: &quot;r&quot;(_dampr));&t;&bslash;&n;} while(0)
multiline_comment|/*&n; * AMCR - Address Mapping Control Register&n; */
DECL|macro|AMCR_IAMRN
mdefine_line|#define AMCR_IAMRN&t;&t;0x000000ff&t;/* quantity of IAMPR registers */
DECL|macro|AMCR_DAMRN
mdefine_line|#define AMCR_DAMRN&t;&t;0x0000ff00&t;/* quantity of DAMPR registers */
multiline_comment|/*&n; * TTBR - Address Translation Table Base Register&n; */
DECL|macro|__get_TTBR
mdefine_line|#define __get_TTBR()&t;&t;({ unsigned long x; asm volatile(&quot;movsg ttbr,%0&quot; : &quot;=r&quot;(x)); x; })
multiline_comment|/*&n; * TPXR - TLB Probe Extend Register&n; */
DECL|macro|TPXR_E
mdefine_line|#define TPXR_E&t;&t;&t;0x00000001
DECL|macro|TPXR_LMAX_SHIFT
mdefine_line|#define TPXR_LMAX_SHIFT&t;&t;20
DECL|macro|TPXR_LMAX_SMASK
mdefine_line|#define TPXR_LMAX_SMASK&t;&t;0xf
DECL|macro|TPXR_WMAX_SHIFT
mdefine_line|#define TPXR_WMAX_SHIFT&t;&t;24
DECL|macro|TPXR_WMAX_SMASK
mdefine_line|#define TPXR_WMAX_SMASK&t;&t;0xf
DECL|macro|TPXR_WAY_SHIFT
mdefine_line|#define TPXR_WAY_SHIFT&t;&t;28
DECL|macro|TPXR_WAY_SMASK
mdefine_line|#define TPXR_WAY_SMASK&t;&t;0xf
multiline_comment|/*&n; * DCR - Debug Control Register&n; */
DECL|macro|DCR_IBCE3
mdefine_line|#define DCR_IBCE3&t;&t;0x00000001&t;/* break on conditional insn pointed to by IBAR3 */
DECL|macro|DCR_IBE3
mdefine_line|#define DCR_IBE3&t;&t;0x00000002&t;/* break on insn pointed to by IBAR3 */
DECL|macro|DCR_IBCE1
mdefine_line|#define DCR_IBCE1&t;&t;0x00000004&t;/* break on conditional insn pointed to by IBAR2 */
DECL|macro|DCR_IBE1
mdefine_line|#define DCR_IBE1&t;&t;0x00000008&t;/* break on insn pointed to by IBAR2 */
DECL|macro|DCR_IBCE2
mdefine_line|#define DCR_IBCE2&t;&t;0x00000010&t;/* break on conditional insn pointed to by IBAR1 */
DECL|macro|DCR_IBE2
mdefine_line|#define DCR_IBE2&t;&t;0x00000020&t;/* break on insn pointed to by IBAR1 */
DECL|macro|DCR_IBCE0
mdefine_line|#define DCR_IBCE0&t;&t;0x00000040&t;/* break on conditional insn pointed to by IBAR0 */
DECL|macro|DCR_IBE0
mdefine_line|#define DCR_IBE0&t;&t;0x00000080&t;/* break on insn pointed to by IBAR0 */
DECL|macro|DCR_DDBE1
mdefine_line|#define DCR_DDBE1&t;&t;0x00004000&t;/* use DBDR1x when checking DBAR1 */
DECL|macro|DCR_DWBE1
mdefine_line|#define DCR_DWBE1&t;&t;0x00008000&t;/* break on store to address in DBAR1/DBMR1x */
DECL|macro|DCR_DRBE1
mdefine_line|#define DCR_DRBE1&t;&t;0x00010000&t;/* break on load from address in DBAR1/DBMR1x */
DECL|macro|DCR_DDBE0
mdefine_line|#define DCR_DDBE0&t;&t;0x00020000&t;/* use DBDR0x when checking DBAR0 */
DECL|macro|DCR_DWBE0
mdefine_line|#define DCR_DWBE0&t;&t;0x00040000&t;/* break on store to address in DBAR0/DBMR0x */
DECL|macro|DCR_DRBE0
mdefine_line|#define DCR_DRBE0&t;&t;0x00080000&t;/* break on load from address in DBAR0/DBMR0x */
DECL|macro|DCR_EIM
mdefine_line|#define DCR_EIM&t;&t;&t;0x0c000000&t;/* external interrupt disable */
DECL|macro|DCR_IBM
mdefine_line|#define DCR_IBM&t;&t;&t;0x10000000&t;/* instruction break disable */
DECL|macro|DCR_SE
mdefine_line|#define DCR_SE&t;&t;&t;0x20000000&t;/* single step enable */
DECL|macro|DCR_EBE
mdefine_line|#define DCR_EBE&t;&t;&t;0x40000000&t;/* exception break enable */
multiline_comment|/*&n; * BRR - Break Interrupt Request Register&n; */
DECL|macro|BRR_ST
mdefine_line|#define BRR_ST&t;&t;&t;0x00000001&t;/* single-step detected */
DECL|macro|BRR_SB
mdefine_line|#define BRR_SB&t;&t;&t;0x00000002&t;/* break instruction detected */
DECL|macro|BRR_BB
mdefine_line|#define BRR_BB&t;&t;&t;0x00000004&t;/* branch with hint detected */
DECL|macro|BRR_CBB
mdefine_line|#define BRR_CBB&t;&t;&t;0x00000008&t;/* branch to LR detected */
DECL|macro|BRR_IBx
mdefine_line|#define BRR_IBx&t;&t;&t;0x000000f0&t;/* hardware breakpoint detected */
DECL|macro|BRR_DBx
mdefine_line|#define BRR_DBx&t;&t;&t;0x00000f00&t;/* hardware watchpoint detected */
DECL|macro|BRR_DBNEx
mdefine_line|#define BRR_DBNEx&t;&t;0x0000f000&t;/* ? */
DECL|macro|BRR_EBTT
mdefine_line|#define BRR_EBTT&t;&t;0x00ff0000&t;/* trap type of exception break */
DECL|macro|BRR_TB
mdefine_line|#define BRR_TB&t;&t;&t;0x10000000&t;/* external break request detected */
DECL|macro|BRR_CB
mdefine_line|#define BRR_CB&t;&t;&t;0x20000000&t;/* ICE break command detected */
DECL|macro|BRR_EB
mdefine_line|#define BRR_EB&t;&t;&t;0x40000000&t;/* exception break detected */
multiline_comment|/*&n; * BPSR - Break PSR Save Register&n; */
DECL|macro|BPSR_BET
mdefine_line|#define BPSR_BET&t;&t;0x00000001&t;/* former PSR.ET */
DECL|macro|BPSR_BS
mdefine_line|#define BPSR_BS&t;&t;&t;0x00001000&t;/* former PSR.S */
macro_line|#endif /* _ASM_SPR_REGS_H */
eof
