multiline_comment|/*&n; * linux/include/asm/arch/SA-1111.h&n; *&n; * Copyright (C) 2000 John G Dorsey &lt;john+@cs.cmu.edu&gt;&n; *&n; * This file contains definitions for the SA-1111 Companion Chip.&n; * (Structure and naming borrowed from SA-1101.h, by Peter Danielsson.)&n; *&n; */
macro_line|#ifndef _ASM_ARCH_SA1111
DECL|macro|_ASM_ARCH_SA1111
mdefine_line|#define _ASM_ARCH_SA1111
multiline_comment|/*&n; * Macro that calculates real address for registers in the SA-1111&n; */
DECL|macro|_SA1111
mdefine_line|#define _SA1111( x )    ((x) + SA1111_BASE)
multiline_comment|/*&n; * System Bus Interface (SBI)&n; *&n; * Registers&n; *    SKCR&t;Control Register&n; *    SMCR&t;Shared Memory Controller Register&n; *    SKID&t;ID Register&n; */
DECL|macro|_SKCR
mdefine_line|#define _SKCR&t;&t;_SA1111( 0x0000 )
DECL|macro|_SMCR
mdefine_line|#define _SMCR&t;&t;_SA1111( 0x0004 )
DECL|macro|_SKID
mdefine_line|#define _SKID&t;&t;_SA1111( 0x0008 )
macro_line|#if LANGUAGE == C
DECL|macro|SKCR
mdefine_line|#define SKCR&t;&t;(*((volatile Word *) SA1111_p2v (_SKCR)))
DECL|macro|SMCR
mdefine_line|#define SMCR&t;&t;(*((volatile Word *) SA1111_p2v (_SMCR)))
DECL|macro|SKID
mdefine_line|#define SKID&t;&t;(*((volatile Word *) SA1111_p2v (_SKID)))
macro_line|#endif  /* LANGUAGE == C */
DECL|macro|SKCR_PLL_BYPASS
mdefine_line|#define SKCR_PLL_BYPASS&t;(1&lt;&lt;0)
DECL|macro|SKCR_RCLKEN
mdefine_line|#define SKCR_RCLKEN&t;(1&lt;&lt;1)
DECL|macro|SKCR_SLEEP
mdefine_line|#define SKCR_SLEEP&t;(1&lt;&lt;2)
DECL|macro|SKCR_DOZE
mdefine_line|#define SKCR_DOZE&t;(1&lt;&lt;3)
DECL|macro|SKCR_VCO_OFF
mdefine_line|#define SKCR_VCO_OFF&t;(1&lt;&lt;4)
DECL|macro|SKCR_SCANTSTEN
mdefine_line|#define SKCR_SCANTSTEN&t;(1&lt;&lt;5)
DECL|macro|SKCR_CLKTSTEN
mdefine_line|#define SKCR_CLKTSTEN&t;(1&lt;&lt;6)
DECL|macro|SKCR_RDYEN
mdefine_line|#define SKCR_RDYEN&t;(1&lt;&lt;7)
DECL|macro|SKCR_SELAC
mdefine_line|#define SKCR_SELAC&t;(1&lt;&lt;8)
DECL|macro|SKCR_OPPC
mdefine_line|#define SKCR_OPPC&t;(1&lt;&lt;9)
DECL|macro|SKCR_PLLTSTEN
mdefine_line|#define SKCR_PLLTSTEN&t;(1&lt;&lt;10)
DECL|macro|SKCR_USBIOTSTEN
mdefine_line|#define SKCR_USBIOTSTEN&t;(1&lt;&lt;11)
DECL|macro|SKCR_OE_EN
mdefine_line|#define SKCR_OE_EN&t;(1&lt;&lt;13)
DECL|macro|SMCR_DTIM
mdefine_line|#define SMCR_DTIM&t;(1&lt;&lt;0)
DECL|macro|SMCR_MBGE
mdefine_line|#define SMCR_MBGE&t;(1&lt;&lt;1)
DECL|macro|SMCR_DRAC_0
mdefine_line|#define SMCR_DRAC_0&t;(1&lt;&lt;2)
DECL|macro|SMCR_DRAC_1
mdefine_line|#define SMCR_DRAC_1&t;(1&lt;&lt;3)
DECL|macro|SMCR_DRAC_2
mdefine_line|#define SMCR_DRAC_2&t;(1&lt;&lt;4)
DECL|macro|SMCR_CLAT
mdefine_line|#define SMCR_CLAT&t;(1&lt;&lt;5)
DECL|macro|SKID_SIREV_MASK
mdefine_line|#define SKID_SIREV_MASK&t;(0x000000f0)
DECL|macro|SKID_MTREV_MASK
mdefine_line|#define SKID_MTREV_MASK (0x0000000f)
DECL|macro|SKID_ID_MASK
mdefine_line|#define SKID_ID_MASK&t;(0xffffff00)
DECL|macro|SKID_SA1111_ID
mdefine_line|#define SKID_SA1111_ID&t;(0x690cc200)
multiline_comment|/*&n; * System Controller&n; *&n; * Registers&n; *    SKPCR&t;Power Control Register&n; *    SKCDR&t;Clock Divider Register&n; *    SKAUD&t;Audio Clock Divider Register&n; *    SKPMC&t;PS/2 Mouse Clock Divider Register&n; *    SKPTC&t;PS/2 Track Pad Clock Divider Register&n; *    SKPEN0&t;PWM0 Enable Register&n; *    SKPWM0&t;PWM0 Clock Register&n; *    SKPEN1&t;PWM1 Enable Register&n; *    SKPWM1&t;PWM1 Clock Register&n; */
DECL|macro|_SKPCR
mdefine_line|#define _SKPCR&t;&t;_SA1111(0x0200)
DECL|macro|_SKCDR
mdefine_line|#define _SKCDR&t;&t;_SA1111(0x0204)
DECL|macro|_SKAUD
mdefine_line|#define _SKAUD&t;&t;_SA1111(0x0208)
DECL|macro|_SKPMC
mdefine_line|#define _SKPMC&t;&t;_SA1111(0x020c)
DECL|macro|_SKPTC
mdefine_line|#define _SKPTC&t;&t;_SA1111(0x0210)
DECL|macro|_SKPEN0
mdefine_line|#define _SKPEN0&t;&t;_SA1111(0x0214)
DECL|macro|_SKPWM0
mdefine_line|#define _SKPWM0&t;&t;_SA1111(0x0218)
DECL|macro|_SKPEN1
mdefine_line|#define _SKPEN1&t;&t;_SA1111(0x021c)
DECL|macro|_SKPWM1
mdefine_line|#define _SKPWM1&t;&t;_SA1111(0x0220)
macro_line|#if LANGUAGE == C
DECL|macro|SKPCR
mdefine_line|#define SKPCR&t;&t;(*((volatile Word *) SA1111_p2v (_SKPCR)))
DECL|macro|SKCDR
mdefine_line|#define SKCDR&t;&t;(*((volatile Word *) SA1111_p2v (_SKCDR)))
DECL|macro|SKAUD
mdefine_line|#define SKAUD&t;&t;(*((volatile Word *) SA1111_p2v (_SKAUD)))
DECL|macro|SKPMC
mdefine_line|#define SKPMC&t;&t;(*((volatile Word *) SA1111_p2v (_SKPMC)))
DECL|macro|SKPTC
mdefine_line|#define SKPTC&t;&t;(*((volatile Word *) SA1111_p2v (_SKPTC)))
DECL|macro|SKPEN0
mdefine_line|#define SKPEN0&t;&t;(*((volatile Word *) SA1111_p2v (_SKPEN0)))
DECL|macro|SKPWM0
mdefine_line|#define SKPWM0&t;&t;(*((volatile Word *) SA1111_p2v (_SKPWM0)))
DECL|macro|SKPEN1
mdefine_line|#define SKPEN1&t;&t;(*((volatile Word *) SA1111_p2v (_SKPEN1)))
DECL|macro|SKPWM1
mdefine_line|#define SKPWM1&t;&t;(*((volatile Word *) SA1111_p2v (_SKPWM1)))
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * General-Purpose I/O Interface&n; *&n; * Registers&n; *    PA_DDR&t;&t;GPIO Block A Data Direction&n; *    PA_DRR/PA_DWR&t;GPIO Block A Data Value Register (read/write)&n; *    PA_SDR&t;&t;GPIO Block A Sleep Direction&n; *    PA_SSR&t;&t;GPIO Block A Sleep State&n; *    PB_DDR&t;&t;GPIO Block B Data Direction&n; *    PB_DRR/PB_DWR&t;GPIO Block B Data Value Register (read/write)&n; *    PB_SDR&t;&t;GPIO Block B Sleep Direction&n; *    PB_SSR&t;&t;GPIO Block B Sleep State&n; *    PC_DDR&t;&t;GPIO Block C Data Direction&n; *    PC_DRR/PC_DWR&t;GPIO Block C Data Value Register (read/write)&n; *    PC_SDR&t;&t;GPIO Block C Sleep Direction&n; *    PC_SSR&t;&t;GPIO Block C Sleep State&n; */
DECL|macro|_PA_DDR
mdefine_line|#define _PA_DDR&t;&t;_SA1111( 0x1000 )
DECL|macro|_PA_DRR
mdefine_line|#define _PA_DRR&t;&t;_SA1111( 0x1004 )
DECL|macro|_PA_DWR
mdefine_line|#define _PA_DWR&t;&t;_SA1111( 0x1004 )
DECL|macro|_PA_SDR
mdefine_line|#define _PA_SDR&t;&t;_SA1111( 0x1008 )
DECL|macro|_PA_SSR
mdefine_line|#define _PA_SSR&t;&t;_SA1111( 0x100c )
DECL|macro|_PB_DDR
mdefine_line|#define _PB_DDR&t;&t;_SA1111( 0x1010 )
DECL|macro|_PB_DRR
mdefine_line|#define _PB_DRR&t;&t;_SA1111( 0x1014 )
DECL|macro|_PB_DWR
mdefine_line|#define _PB_DWR&t;&t;_SA1111( 0x1014 )
DECL|macro|_PB_SDR
mdefine_line|#define _PB_SDR&t;&t;_SA1111( 0x1018 )
DECL|macro|_PB_SSR
mdefine_line|#define _PB_SSR&t;&t;_SA1111( 0x101c )
DECL|macro|_PC_DDR
mdefine_line|#define _PC_DDR&t;&t;_SA1111( 0x1020 )
DECL|macro|_PC_DRR
mdefine_line|#define _PC_DRR&t;&t;_SA1111( 0x1024 )
DECL|macro|_PC_DWR
mdefine_line|#define _PC_DWR&t;&t;_SA1111( 0x1024 )
DECL|macro|_PC_SDR
mdefine_line|#define _PC_SDR&t;&t;_SA1111( 0x1028 )
DECL|macro|_PC_SSR
mdefine_line|#define _PC_SSR&t;&t;_SA1111( 0x102c )
macro_line|#if LANGUAGE == C
DECL|macro|PA_DDR
mdefine_line|#define PA_DDR&t;&t;(*((volatile Word *) SA1111_p2v (_PA_DDR)))
DECL|macro|PA_DRR
mdefine_line|#define PA_DRR&t;&t;(*((volatile Word *) SA1111_p2v (_PA_DRR)))
DECL|macro|PA_DWR
mdefine_line|#define PA_DWR&t;&t;(*((volatile Word *) SA1111_p2v (_PA_DWR)))
DECL|macro|PA_SDR
mdefine_line|#define PA_SDR&t;&t;(*((volatile Word *) SA1111_p2v (_PA_SDR)))
DECL|macro|PA_SSR
mdefine_line|#define PA_SSR&t;&t;(*((volatile Word *) SA1111_p2v (_PA_SSR)))
DECL|macro|PB_DDR
mdefine_line|#define PB_DDR&t;&t;(*((volatile Word *) SA1111_p2v (_PB_DDR)))
DECL|macro|PB_DRR
mdefine_line|#define PB_DRR&t;&t;(*((volatile Word *) SA1111_p2v (_PB_DRR)))
DECL|macro|PB_DWR
mdefine_line|#define PB_DWR&t;&t;(*((volatile Word *) SA1111_p2v (_PB_DWR)))
DECL|macro|PB_SDR
mdefine_line|#define PB_SDR&t;&t;(*((volatile Word *) SA1111_p2v (_PB_SDR)))
DECL|macro|PB_SSR
mdefine_line|#define PB_SSR&t;&t;(*((volatile Word *) SA1111_p2v (_PB_SSR)))
DECL|macro|PC_DDR
mdefine_line|#define PC_DDR&t;&t;(*((volatile Word *) SA1111_p2v (_PC_DDR)))
DECL|macro|PC_DRR
mdefine_line|#define PC_DRR&t;&t;(*((volatile Word *) SA1111_p2v (_PC_DRR)))
DECL|macro|PC_DWR
mdefine_line|#define PC_DWR&t;&t;(*((volatile Word *) SA1111_p2v (_PC_DWR)))
DECL|macro|PC_SDR
mdefine_line|#define PC_SDR&t;&t;(*((volatile Word *) SA1111_p2v (_PC_SDR)))
DECL|macro|PC_SSR
mdefine_line|#define PC_SSR&t;&t;(*((volatile Word *) SA1111_p2v (_PC_SSR)))
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * Interrupt Controller&n; *&n; * Registers&n; *    INTTEST0&t;&t;Test register 0&n; *    INTTEST1&t;&t;Test register 1&n; *    INTEN0&t;&t;Interrupt Enable register 0&n; *    INTEN1&t;&t;Interrupt Enable register 1&n; *    INTPOL0&t;&t;Interrupt Polarity selection 0&n; *    INTPOL1&t;&t;Interrupt Polarity selection 1&n; *    INTTSTSEL&t;&t;Interrupt source selection&n; *    INTSTATCLR0&t;Interrupt Status/Clear 0&n; *    INTSTATCLR1&t;Interrupt Status/Clear 1&n; *    INTSET0&t;&t;Interrupt source set 0&n; *    INTSET1&t;&t;Interrupt source set 1&n; *    WAKE_EN0&t;&t;Wake-up source enable 0&n; *    WAKE_EN1&t;&t;Wake-up source enable 1&n; *    WAKE_POL0&t;&t;Wake-up polarity selection 0&n; *    WAKE_POL1&t;&t;Wake-up polarity selection 1&n; */
DECL|macro|_INTTEST0
mdefine_line|#define _INTTEST0&t;_SA1111( 0x1600 )
DECL|macro|_INTTEST1
mdefine_line|#define _INTTEST1&t;_SA1111( 0x1604 )
DECL|macro|_INTEN0
mdefine_line|#define _INTEN0&t;&t;_SA1111( 0x1608 )
DECL|macro|_INTEN1
mdefine_line|#define _INTEN1&t;&t;_SA1111( 0x160c )
DECL|macro|_INTPOL0
mdefine_line|#define _INTPOL0&t;_SA1111( 0x1610 )
DECL|macro|_INTPOL1
mdefine_line|#define _INTPOL1&t;_SA1111( 0x1614 )
DECL|macro|_INTTSTSEL
mdefine_line|#define _INTTSTSEL&t;_SA1111( 0x1618 )
DECL|macro|_INTSTATCLR0
mdefine_line|#define _INTSTATCLR0&t;_SA1111( 0x161c )
DECL|macro|_INTSTATCLR1
mdefine_line|#define _INTSTATCLR1&t;_SA1111( 0x1620 )
DECL|macro|_INTSET0
mdefine_line|#define _INTSET0&t;_SA1111( 0x1624 )
DECL|macro|_INTSET1
mdefine_line|#define _INTSET1&t;_SA1111( 0x1628 )
DECL|macro|_WAKE_EN0
mdefine_line|#define _WAKE_EN0&t;_SA1111( 0x162c )
DECL|macro|_WAKE_EN1
mdefine_line|#define _WAKE_EN1&t;_SA1111( 0x1630 )
DECL|macro|_WAKE_POL0
mdefine_line|#define _WAKE_POL0&t;_SA1111( 0x1634 )
DECL|macro|_WAKE_POL1
mdefine_line|#define _WAKE_POL1&t;_SA1111( 0x1638 )
macro_line|#if LANGUAGE == C
DECL|macro|INTTEST0
mdefine_line|#define INTTEST0&t;(*((volatile Word *) SA1111_p2v (_INTTEST0)))
DECL|macro|INTTEST1
mdefine_line|#define INTTEST1&t;(*((volatile Word *) SA1111_p2v (_INTTEST1)))
DECL|macro|INTEN0
mdefine_line|#define INTEN0&t;&t;(*((volatile Word *) SA1111_p2v (_INTEN0)))
DECL|macro|INTEN1
mdefine_line|#define INTEN1&t;&t;(*((volatile Word *) SA1111_p2v (_INTEN1)))
DECL|macro|INTPOL0
mdefine_line|#define INTPOL0&t;&t;(*((volatile Word *) SA1111_p2v (_INTPOL0)))
DECL|macro|INTPOL1
mdefine_line|#define INTPOL1&t;&t;(*((volatile Word *) SA1111_p2v (_INTPOL1)))
DECL|macro|INTTSTSEL
mdefine_line|#define INTTSTSEL&t;(*((volatile Word *) SA1111_p2v (_INTTSTSEL)))
DECL|macro|INTSTATCLR0
mdefine_line|#define INTSTATCLR0&t;(*((volatile Word *) SA1111_p2v (_INTSTATCLR0)))
DECL|macro|INTSTATCLR1
mdefine_line|#define INTSTATCLR1&t;(*((volatile Word *) SA1111_p2v (_INTSTATCLR1)))
DECL|macro|INTSET0
mdefine_line|#define INTSET0&t;&t;(*((volatile Word *) SA1111_p2v (_INTSET0)))
DECL|macro|INTSET1
mdefine_line|#define INTSET1&t;&t;(*((volatile Word *) SA1111_p2v (_INTSET1)))
DECL|macro|WAKE_EN0
mdefine_line|#define WAKE_EN0&t;(*((volatile Word *) SA1111_p2v (_WAKE_EN0)))
DECL|macro|WAKE_EN1
mdefine_line|#define WAKE_EN1&t;(*((volatile Word *) SA1111_p2v (_WAKE_EN1)))
DECL|macro|WAKE_POL0
mdefine_line|#define WAKE_POL0&t;(*((volatile Word *) SA1111_p2v (_WAKE_POL0)))
DECL|macro|WAKE_POL1
mdefine_line|#define WAKE_POL1&t;(*((volatile Word *) SA1111_p2v (_WAKE_POL1)))
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * PCMCIA Interface&n; *&n; * Registers&n; *    PCSR&t;Status Register&n; *    PCCR&t;Control Register&n; *    PCSSR&t;Sleep State Register&n; */
DECL|macro|_PCCR
mdefine_line|#define _PCCR&t;&t;_SA1111( 0x1800 )
DECL|macro|_PCSSR
mdefine_line|#define _PCSSR&t;&t;_SA1111( 0x1804 )
DECL|macro|_PCSR
mdefine_line|#define _PCSR&t;&t;_SA1111( 0x1808 )
macro_line|#if LANGUAGE == C
DECL|macro|PCCR
mdefine_line|#define PCCR&t;&t;(*((volatile Word *) SA1111_p2v (_PCCR)))
DECL|macro|PCSSR
mdefine_line|#define PCSSR&t;&t;(*((volatile Word *) SA1111_p2v (_PCSSR)))
DECL|macro|PCSR
mdefine_line|#define PCSR&t;&t;(*((volatile Word *) SA1111_p2v (_PCSR)))
macro_line|#endif  /* LANGUAGE == C */
DECL|macro|PCSR_S0_READY
mdefine_line|#define PCSR_S0_READY&t;(1&lt;&lt;0)
DECL|macro|PCSR_S1_READY
mdefine_line|#define PCSR_S1_READY&t;(1&lt;&lt;1)
DECL|macro|PCSR_S0_DETECT
mdefine_line|#define PCSR_S0_DETECT&t;(1&lt;&lt;2)
DECL|macro|PCSR_S1_DETECT
mdefine_line|#define PCSR_S1_DETECT&t;(1&lt;&lt;3)
DECL|macro|PCSR_S0_VS1
mdefine_line|#define PCSR_S0_VS1&t;(1&lt;&lt;4)
DECL|macro|PCSR_S0_VS2
mdefine_line|#define PCSR_S0_VS2&t;(1&lt;&lt;5)
DECL|macro|PCSR_S1_VS1
mdefine_line|#define PCSR_S1_VS1&t;(1&lt;&lt;6)
DECL|macro|PCSR_S1_VS2
mdefine_line|#define PCSR_S1_VS2&t;(1&lt;&lt;7)
DECL|macro|PCSR_S0_WP
mdefine_line|#define PCSR_S0_WP&t;(1&lt;&lt;8)
DECL|macro|PCSR_S1_WP
mdefine_line|#define PCSR_S1_WP&t;(1&lt;&lt;9)
DECL|macro|PCSR_S0_BVD1
mdefine_line|#define PCSR_S0_BVD1&t;(1&lt;&lt;10)
DECL|macro|PCSR_S0_BVD2
mdefine_line|#define PCSR_S0_BVD2&t;(1&lt;&lt;11)
DECL|macro|PCSR_S1_BVD1
mdefine_line|#define PCSR_S1_BVD1&t;(1&lt;&lt;12)
DECL|macro|PCSR_S1_BVD2
mdefine_line|#define PCSR_S1_BVD2&t;(1&lt;&lt;13)
DECL|macro|PCCR_S0_RST
mdefine_line|#define PCCR_S0_RST&t;(1&lt;&lt;0)
DECL|macro|PCCR_S1_RST
mdefine_line|#define PCCR_S1_RST&t;(1&lt;&lt;1)
DECL|macro|PCCR_S0_FLT
mdefine_line|#define PCCR_S0_FLT&t;(1&lt;&lt;2)
DECL|macro|PCCR_S1_FLT
mdefine_line|#define PCCR_S1_FLT&t;(1&lt;&lt;3)
DECL|macro|PCCR_S0_PWAITEN
mdefine_line|#define PCCR_S0_PWAITEN&t;(1&lt;&lt;4)
DECL|macro|PCCR_S1_PWAITEN
mdefine_line|#define PCCR_S1_PWAITEN&t;(1&lt;&lt;5)
DECL|macro|PCCR_S0_PSE
mdefine_line|#define PCCR_S0_PSE&t;(1&lt;&lt;6)
DECL|macro|PCCR_S1_PSE
mdefine_line|#define PCCR_S1_PSE&t;(1&lt;&lt;7)
DECL|macro|PCSSR_S0_SLEEP
mdefine_line|#define PCSSR_S0_SLEEP&t;(1&lt;&lt;0)
DECL|macro|PCSSR_S1_SLEEP
mdefine_line|#define PCSSR_S1_SLEEP&t;(1&lt;&lt;1)
macro_line|#endif  /* _ASM_ARCH_SA1111 */
eof
