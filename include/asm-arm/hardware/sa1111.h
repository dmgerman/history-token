multiline_comment|/*&n; * linux/include/asm-arm/hardware/SA-1111.h&n; *&n; * Copyright (C) 2000 John G Dorsey &lt;john+@cs.cmu.edu&gt;&n; *&n; * This file contains definitions for the SA-1111 Companion Chip.&n; * (Structure and naming borrowed from SA-1101.h, by Peter Danielsson.)&n; *&n; * Macro that calculates real address for registers in the SA-1111&n; */
macro_line|#ifndef _ASM_ARCH_SA1111
DECL|macro|_ASM_ARCH_SA1111
mdefine_line|#define _ASM_ARCH_SA1111
macro_line|#include &lt;asm/arch/bitfield.h&gt;
multiline_comment|/*&n; * The SA1111 is always located at virtual 0xf4000000, and is always&n; * &quot;native&quot; endian.&n; */
DECL|macro|SA1111_VBASE
mdefine_line|#define SA1111_VBASE&t;&t;0xf4000000
multiline_comment|/* Don&squot;t use these! */
DECL|macro|SA1111_p2v
mdefine_line|#define SA1111_p2v( x )         ((x) - SA1111_BASE + SA1111_VBASE)
DECL|macro|SA1111_v2p
mdefine_line|#define SA1111_v2p( x )         ((x) - SA1111_VBASE + SA1111_BASE)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|_SA1111
mdefine_line|#define _SA1111(x)&t;((x) + sa1111-&gt;resource.start)
macro_line|#endif
multiline_comment|/*&n; * 26 bits of the SA-1110 address bus are available to the SA-1111.&n; * Use these when feeding target addresses to the DMA engines.&n; */
DECL|macro|SA1111_ADDR_WIDTH
mdefine_line|#define SA1111_ADDR_WIDTH&t;(26)
DECL|macro|SA1111_ADDR_MASK
mdefine_line|#define SA1111_ADDR_MASK&t;((1&lt;&lt;SA1111_ADDR_WIDTH)-1)
DECL|macro|SA1111_DMA_ADDR
mdefine_line|#define SA1111_DMA_ADDR(x)&t;((x)&amp;SA1111_ADDR_MASK)
multiline_comment|/*&n; * Don&squot;t ask the (SAC) DMA engines to move less than this amount.&n; */
DECL|macro|SA1111_SAC_DMA_MIN_XFER
mdefine_line|#define SA1111_SAC_DMA_MIN_XFER&t;(0x800)
multiline_comment|/*&n; * SA1111 register definitions.&n; */
DECL|macro|__CCREG
mdefine_line|#define __CCREG(x)&t;__REGP(SA1111_VBASE + (x))
multiline_comment|/*&n; * System Bus Interface (SBI)&n; *&n; * Registers&n; *    SKCR&t;Control Register&n; *    SMCR&t;Shared Memory Controller Register&n; *    SKID&t;ID Register&n; */
DECL|macro|SA1111_SKCR
mdefine_line|#define SA1111_SKCR&t;0x0000
DECL|macro|SA1111_SMCR
mdefine_line|#define SA1111_SMCR&t;0x0004
DECL|macro|SA1111_SKID
mdefine_line|#define SA1111_SKID&t;0x0008
DECL|macro|_SBI_SKCR
mdefine_line|#define _SBI_SKCR&t;_SA1111(SA1111_SKCR)
DECL|macro|_SBI_SMCR
mdefine_line|#define _SBI_SMCR&t;_SA1111(SA1111_SMCR)
DECL|macro|_SBI_SKID
mdefine_line|#define _SBI_SKID&t;_SA1111(SA1111_SKID)
macro_line|#if LANGUAGE == C
DECL|macro|SBI_SKCR
mdefine_line|#define SBI_SKCR&t;__CCREG(SA1111_SKCR)
DECL|macro|SBI_SMCR
mdefine_line|#define SBI_SMCR&t;__CCREG(SA1111_SMCR)
DECL|macro|SBI_SKID
mdefine_line|#define SBI_SKID&t;__CCREG(SA1111_SKID)
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
multiline_comment|/*&n; * Don&squot;t believe the specs!  Take them, throw them outside.  Leave them&n; * there for a week.  Spit on them.  Walk on them.  Stamp on them.&n; * Pour gasoline over them and finally burn them.  Now think about coding.&n; *  - The October 1999 errata (278260-007) says its bit 13, 1 to enable.&n; *  - The Feb 2001 errata (278260-010) says that the previous errata&n; *    (278260-009) is wrong, and its bit actually 12, fixed in spec&n; *    278242-003.&n; *  - The SA1111 manual (278242) says bit 12, but 0 to enable.&n; *  - Reality is bit 13, 1 to enable.&n; *      -- rmk&n; */
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
DECL|macro|SMCR_DRAC
mdefine_line|#define SMCR_DRAC&t;Fld(3, 2)
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
DECL|macro|SA1111_SKPCR
mdefine_line|#define SA1111_SKPCR&t;0x0200
DECL|macro|SA1111_SKCDR
mdefine_line|#define SA1111_SKCDR&t;0x0204
DECL|macro|SA1111_SKAUD
mdefine_line|#define SA1111_SKAUD&t;0x0208
DECL|macro|SA1111_SKPMC
mdefine_line|#define SA1111_SKPMC&t;0x020c
DECL|macro|SA1111_SKPTC
mdefine_line|#define SA1111_SKPTC&t;0x0210
DECL|macro|SA1111_SKPEN0
mdefine_line|#define SA1111_SKPEN0&t;0x0214
DECL|macro|SA1111_SKPWN0
mdefine_line|#define SA1111_SKPWN0&t;0x0218
DECL|macro|SA1111_SKPEN1
mdefine_line|#define SA1111_SKPEN1&t;0x021c
DECL|macro|SA1111_SKPWM1
mdefine_line|#define SA1111_SKPWM1&t;0x0220
DECL|macro|_SKPCR
mdefine_line|#define _SKPCR&t;&t;_SA1111(SA1111_SKPCR)
DECL|macro|_SKCDR
mdefine_line|#define _SKCDR&t;&t;_SA1111(SA1111_SKCDR)
DECL|macro|_SKAUD
mdefine_line|#define _SKAUD&t;&t;_SA1111(SA1111_SKAUD)
DECL|macro|_SKPMC
mdefine_line|#define _SKPMC&t;&t;_SA1111(SA1111_SKPMC)
DECL|macro|_SKPTC
mdefine_line|#define _SKPTC&t;&t;_SA1111(SA1111_SKPTC)
DECL|macro|_SKPEN0
mdefine_line|#define _SKPEN0&t;&t;_SA1111(SA1111_SKPEN0)
DECL|macro|_SKPWM0
mdefine_line|#define _SKPWM0&t;&t;_SA1111(SA1111_SKPWM0)
DECL|macro|_SKPEN1
mdefine_line|#define _SKPEN1&t;&t;_SA1111(SA1111_SKPEN1)
DECL|macro|_SKPWM1
mdefine_line|#define _SKPWM1&t;&t;_SA1111(SA1111_SKPWM1)
macro_line|#if LANGUAGE == C
DECL|macro|SKPCR
mdefine_line|#define SKPCR&t;&t;__CCREG(SA1111_SKPCR)
DECL|macro|SKCDR
mdefine_line|#define SKCDR&t;&t;__CCREG(SA1111_SKCDR)
DECL|macro|SKAUD
mdefine_line|#define SKAUD&t;&t;__CCREG(SA1111_SKAUD)
DECL|macro|SKPMC
mdefine_line|#define SKPMC&t;&t;__CCREG(SA1111_SKPMC)
DECL|macro|SKPTC
mdefine_line|#define SKPTC&t;&t;__CCREG(SA1111_SKPTC)
DECL|macro|SKPEN0
mdefine_line|#define SKPEN0&t;&t;__CCREG(SA1111_SKPEN0)
DECL|macro|SKPWM0
mdefine_line|#define SKPWM0&t;&t;__CCREG(SA1111_SKPWM0)
DECL|macro|SKPEN1
mdefine_line|#define SKPEN1&t;&t;__CCREG(SA1111_SKPEN1)
DECL|macro|SKPWM1
mdefine_line|#define SKPWM1&t;&t;__CCREG(SA1111_SKPWM1)
macro_line|#endif  /* LANGUAGE == C */
DECL|macro|SKPCR_UCLKEN
mdefine_line|#define SKPCR_UCLKEN&t;(1&lt;&lt;0)
DECL|macro|SKPCR_ACCLKEN
mdefine_line|#define SKPCR_ACCLKEN&t;(1&lt;&lt;1)
DECL|macro|SKPCR_I2SCLKEN
mdefine_line|#define SKPCR_I2SCLKEN&t;(1&lt;&lt;2)
DECL|macro|SKPCR_L3CLKEN
mdefine_line|#define SKPCR_L3CLKEN&t;(1&lt;&lt;3)
DECL|macro|SKPCR_SCLKEN
mdefine_line|#define SKPCR_SCLKEN&t;(1&lt;&lt;4)
DECL|macro|SKPCR_PMCLKEN
mdefine_line|#define SKPCR_PMCLKEN&t;(1&lt;&lt;5)
DECL|macro|SKPCR_PTCLKEN
mdefine_line|#define SKPCR_PTCLKEN&t;(1&lt;&lt;6)
DECL|macro|SKPCR_DCLKEN
mdefine_line|#define SKPCR_DCLKEN&t;(1&lt;&lt;7)
DECL|macro|SKPCR_PWMCLKEN
mdefine_line|#define SKPCR_PWMCLKEN&t;(1&lt;&lt;8)
multiline_comment|/*&n; * USB Host controller&n; */
DECL|macro|_USB_OHCI_OP_BASE
mdefine_line|#define _USB_OHCI_OP_BASE&t;_SA1111( 0x400 )
DECL|macro|_USB_STATUS
mdefine_line|#define _USB_STATUS&t;&t;_SA1111( 0x518 )
DECL|macro|_USB_RESET
mdefine_line|#define _USB_RESET&t;&t;_SA1111( 0x51c )
DECL|macro|_USB_INTERRUPTEST
mdefine_line|#define _USB_INTERRUPTEST&t;_SA1111( 0x520 )
DECL|macro|_USB_EXTENT
mdefine_line|#define _USB_EXTENT&t;&t;(_USB_INTERRUPTEST - _USB_OHCI_OP_BASE + 4)
macro_line|#if LANGUAGE == C
DECL|macro|USB_OHCI_OP_BASE
mdefine_line|#define USB_OHCI_OP_BASE&t;__CCREG(0x0400)
DECL|macro|USB_STATUS
mdefine_line|#define USB_STATUS&t;&t;__CCREG(0x0518)
DECL|macro|USB_RESET
mdefine_line|#define USB_RESET&t;&t;__CCREG(0x051c)
DECL|macro|USB_INTERRUPTEST
mdefine_line|#define USB_INTERRUPTEST&t;__CCReG(0x0520)
macro_line|#endif  /* LANGUAGE == C */
DECL|macro|USB_RESET_FORCEIFRESET
mdefine_line|#define USB_RESET_FORCEIFRESET&t;(1 &lt;&lt; 0)
DECL|macro|USB_RESET_FORCEHCRESET
mdefine_line|#define USB_RESET_FORCEHCRESET&t;(1 &lt;&lt; 1)
DECL|macro|USB_RESET_CLKGENRESET
mdefine_line|#define USB_RESET_CLKGENRESET&t;(1 &lt;&lt; 2)
DECL|macro|USB_RESET_SIMSCALEDOWN
mdefine_line|#define USB_RESET_SIMSCALEDOWN&t;(1 &lt;&lt; 3)
DECL|macro|USB_RESET_USBINTTEST
mdefine_line|#define USB_RESET_USBINTTEST&t;(1 &lt;&lt; 4)
DECL|macro|USB_RESET_SLEEPSTBYEN
mdefine_line|#define USB_RESET_SLEEPSTBYEN&t;(1 &lt;&lt; 5)
DECL|macro|USB_RESET_PWRSENSELOW
mdefine_line|#define USB_RESET_PWRSENSELOW&t;(1 &lt;&lt; 6)
DECL|macro|USB_RESET_PWRCTRLLOW
mdefine_line|#define USB_RESET_PWRCTRLLOW&t;(1 &lt;&lt; 7)
DECL|macro|USB_STATUS_IRQHCIRMTWKUP
mdefine_line|#define USB_STATUS_IRQHCIRMTWKUP  (1 &lt;&lt;  7)
DECL|macro|USB_STATUS_IRQHCIBUFFACC
mdefine_line|#define USB_STATUS_IRQHCIBUFFACC  (1 &lt;&lt;  8)
DECL|macro|USB_STATUS_NIRQHCIM
mdefine_line|#define USB_STATUS_NIRQHCIM       (1 &lt;&lt;  9)
DECL|macro|USB_STATUS_NHCIMFCLR
mdefine_line|#define USB_STATUS_NHCIMFCLR      (1 &lt;&lt; 10)
DECL|macro|USB_STATUS_USBPWRSENSE
mdefine_line|#define USB_STATUS_USBPWRSENSE    (1 &lt;&lt; 11)
multiline_comment|/*&n; * Serial Audio Controller&n; *&n; * Registers&n; *    SACR0             Serial Audio Common Control Register&n; *    SACR1             Serial Audio Alternate Mode (I2C/MSB) Control Register&n; *    SACR2             Serial Audio AC-link Control Register&n; *    SASR0             Serial Audio I2S/MSB Interface &amp; FIFO Status Register&n; *    SASR1             Serial Audio AC-link Interface &amp; FIFO Status Register&n; *    SASCR             Serial Audio Status Clear Register&n; *    L3_CAR            L3 Control Bus Address Register&n; *    L3_CDR            L3 Control Bus Data Register&n; *    ACCAR             AC-link Command Address Register&n; *    ACCDR             AC-link Command Data Register&n; *    ACSAR             AC-link Status Address Register&n; *    ACSDR             AC-link Status Data Register&n; *    SADTCS            Serial Audio DMA Transmit Control/Status Register&n; *    SADTSA            Serial Audio DMA Transmit Buffer Start Address A&n; *    SADTCA            Serial Audio DMA Transmit Buffer Count Register A&n; *    SADTSB            Serial Audio DMA Transmit Buffer Start Address B&n; *    SADTCB            Serial Audio DMA Transmit Buffer Count Register B&n; *    SADRCS            Serial Audio DMA Receive Control/Status Register&n; *    SADRSA            Serial Audio DMA Receive Buffer Start Address A&n; *    SADRCA            Serial Audio DMA Receive Buffer Count Register A&n; *    SADRSB            Serial Audio DMA Receive Buffer Start Address B&n; *    SADRCB            Serial Audio DMA Receive Buffer Count Register B&n; *    SAITR             Serial Audio Interrupt Test Register&n; *    SADR              Serial Audio Data Register (16 x 32-bit)&n; */
DECL|macro|_SACR0
mdefine_line|#define _SACR0          _SA1111( 0x0600 )
DECL|macro|_SACR1
mdefine_line|#define _SACR1          _SA1111( 0x0604 )
DECL|macro|_SACR2
mdefine_line|#define _SACR2          _SA1111( 0x0608 )
DECL|macro|_SASR0
mdefine_line|#define _SASR0          _SA1111( 0x060c )
DECL|macro|_SASR1
mdefine_line|#define _SASR1          _SA1111( 0x0610 )
DECL|macro|_SASCR
mdefine_line|#define _SASCR          _SA1111( 0x0618 )
DECL|macro|_L3_CAR
mdefine_line|#define _L3_CAR         _SA1111( 0x061c )
DECL|macro|_L3_CDR
mdefine_line|#define _L3_CDR         _SA1111( 0x0620 )
DECL|macro|_ACCAR
mdefine_line|#define _ACCAR          _SA1111( 0x0624 )
DECL|macro|_ACCDR
mdefine_line|#define _ACCDR          _SA1111( 0x0628 )
DECL|macro|_ACSAR
mdefine_line|#define _ACSAR          _SA1111( 0x062c )
DECL|macro|_ACSDR
mdefine_line|#define _ACSDR          _SA1111( 0x0630 )
DECL|macro|_SADTCS
mdefine_line|#define _SADTCS         _SA1111( 0x0634 )
DECL|macro|_SADTSA
mdefine_line|#define _SADTSA         _SA1111( 0x0638 )
DECL|macro|_SADTCA
mdefine_line|#define _SADTCA         _SA1111( 0x063c )
DECL|macro|_SADTSB
mdefine_line|#define _SADTSB         _SA1111( 0x0640 )
DECL|macro|_SADTCB
mdefine_line|#define _SADTCB         _SA1111( 0x0644 )
DECL|macro|_SADRCS
mdefine_line|#define _SADRCS         _SA1111( 0x0648 )
DECL|macro|_SADRSA
mdefine_line|#define _SADRSA         _SA1111( 0x064c )
DECL|macro|_SADRCA
mdefine_line|#define _SADRCA         _SA1111( 0x0650 )
DECL|macro|_SADRSB
mdefine_line|#define _SADRSB         _SA1111( 0x0654 )
DECL|macro|_SADRCB
mdefine_line|#define _SADRCB         _SA1111( 0x0658 )
DECL|macro|_SAITR
mdefine_line|#define _SAITR          _SA1111( 0x065c )
DECL|macro|_SADR
mdefine_line|#define _SADR           _SA1111( 0x0680 )
macro_line|#if LANGUAGE == C
DECL|macro|SACR0
mdefine_line|#define SACR0&t;&t;__CCREG(0x0600)
DECL|macro|SACR1
mdefine_line|#define SACR1&t;&t;__CCREG(0x0604)
DECL|macro|SACR2
mdefine_line|#define SACR2&t;&t;__CCREG(0x0608)
DECL|macro|SASR0
mdefine_line|#define SASR0&t;&t;__CCREG(0x060c)
DECL|macro|SASR1
mdefine_line|#define SASR1&t;&t;__CCREG(0x0610)
DECL|macro|SASCR
mdefine_line|#define SASCR&t;&t;__CCREG(0x0618)
DECL|macro|L3_CAR
mdefine_line|#define L3_CAR&t;&t;__CCREG(0x061c)
DECL|macro|L3_CDR
mdefine_line|#define L3_CDR&t;&t;__CCREG(0x0620)
DECL|macro|ACCAR
mdefine_line|#define ACCAR&t;&t;__CCREG(0x0624)
DECL|macro|ACCDR
mdefine_line|#define ACCDR&t;&t;__CCREG(0x0628)
DECL|macro|ACSAR
mdefine_line|#define ACSAR&t;&t;__CCREG(0x062c)
DECL|macro|ACSDR
mdefine_line|#define ACSDR&t;&t;__CCREG(0x0630)
DECL|macro|SADTCS
mdefine_line|#define SADTCS&t;&t;__CCREG(0x0634)
DECL|macro|SADTSA
mdefine_line|#define SADTSA&t;&t;__CCREG(0x0638)
DECL|macro|SADTCA
mdefine_line|#define SADTCA&t;&t;__CCREG(0x063c)
DECL|macro|SADTSB
mdefine_line|#define SADTSB&t;&t;__CCREG(0x0640)
DECL|macro|SADTCB
mdefine_line|#define SADTCB&t;&t;__CCREG(0x0644)
DECL|macro|SADRCS
mdefine_line|#define SADRCS&t;&t;__CCREG(0x0648)
DECL|macro|SADRSA
mdefine_line|#define SADRSA&t;&t;__CCREG(0x064c)
DECL|macro|SADRCA
mdefine_line|#define SADRCA&t;&t;__CCREG(0x0650)
DECL|macro|SADRSB
mdefine_line|#define SADRSB&t;&t;__CCREG(0x0654)
DECL|macro|SADRCB
mdefine_line|#define SADRCB&t;&t;__CCREG(0x0658)
DECL|macro|SAITR
mdefine_line|#define SAITR&t;&t;__CCREG(0x065c)
DECL|macro|SADR
mdefine_line|#define SADR&t;&t;__CCREG(0x0680)
macro_line|#endif  /* LANGUAGE == C */
DECL|macro|SACR0_ENB
mdefine_line|#define SACR0_ENB&t;(1&lt;&lt;0)
DECL|macro|SACR0_BCKD
mdefine_line|#define SACR0_BCKD&t;(1&lt;&lt;2)
DECL|macro|SACR0_RST
mdefine_line|#define SACR0_RST&t;(1&lt;&lt;3)
DECL|macro|SACR1_AMSL
mdefine_line|#define SACR1_AMSL&t;(1&lt;&lt;0)
DECL|macro|SACR1_L3EN
mdefine_line|#define SACR1_L3EN&t;(1&lt;&lt;1)
DECL|macro|SACR1_L3MB
mdefine_line|#define SACR1_L3MB&t;(1&lt;&lt;2)
DECL|macro|SACR1_DREC
mdefine_line|#define SACR1_DREC&t;(1&lt;&lt;3)
DECL|macro|SACR1_DRPL
mdefine_line|#define SACR1_DRPL&t;(1&lt;&lt;4)
DECL|macro|SACR1_ENLBF
mdefine_line|#define SACR1_ENLBF&t;(1&lt;&lt;5)
DECL|macro|SACR2_TS3V
mdefine_line|#define SACR2_TS3V&t;(1&lt;&lt;0)
DECL|macro|SACR2_TS4V
mdefine_line|#define SACR2_TS4V&t;(1&lt;&lt;1)
DECL|macro|SACR2_WKUP
mdefine_line|#define SACR2_WKUP&t;(1&lt;&lt;2)
DECL|macro|SACR2_DREC
mdefine_line|#define SACR2_DREC&t;(1&lt;&lt;3)
DECL|macro|SACR2_DRPL
mdefine_line|#define SACR2_DRPL&t;(1&lt;&lt;4)
DECL|macro|SACR2_ENLBF
mdefine_line|#define SACR2_ENLBF&t;(1&lt;&lt;5)
DECL|macro|SACR2_RESET
mdefine_line|#define SACR2_RESET&t;(1&lt;&lt;6)
DECL|macro|SASR0_TNF
mdefine_line|#define SASR0_TNF&t;(1&lt;&lt;0)
DECL|macro|SASR0_RNE
mdefine_line|#define SASR0_RNE&t;(1&lt;&lt;1)
DECL|macro|SASR0_BSY
mdefine_line|#define SASR0_BSY&t;(1&lt;&lt;2)
DECL|macro|SASR0_TFS
mdefine_line|#define SASR0_TFS&t;(1&lt;&lt;3)
DECL|macro|SASR0_RFS
mdefine_line|#define SASR0_RFS&t;(1&lt;&lt;4)
DECL|macro|SASR0_TUR
mdefine_line|#define SASR0_TUR&t;(1&lt;&lt;5)
DECL|macro|SASR0_ROR
mdefine_line|#define SASR0_ROR&t;(1&lt;&lt;6)
DECL|macro|SASR0_L3WD
mdefine_line|#define SASR0_L3WD&t;(1&lt;&lt;16)
DECL|macro|SASR0_L3RD
mdefine_line|#define SASR0_L3RD&t;(1&lt;&lt;17)
DECL|macro|SASR1_TNF
mdefine_line|#define SASR1_TNF&t;(1&lt;&lt;0)
DECL|macro|SASR1_RNE
mdefine_line|#define SASR1_RNE&t;(1&lt;&lt;1)
DECL|macro|SASR1_BSY
mdefine_line|#define SASR1_BSY&t;(1&lt;&lt;2)
DECL|macro|SASR1_TFS
mdefine_line|#define SASR1_TFS&t;(1&lt;&lt;3)
DECL|macro|SASR1_RFS
mdefine_line|#define SASR1_RFS&t;(1&lt;&lt;4)
DECL|macro|SASR1_TUR
mdefine_line|#define SASR1_TUR&t;(1&lt;&lt;5)
DECL|macro|SASR1_ROR
mdefine_line|#define SASR1_ROR&t;(1&lt;&lt;6)
DECL|macro|SASR1_CADT
mdefine_line|#define SASR1_CADT&t;(1&lt;&lt;16)
DECL|macro|SASR1_SADR
mdefine_line|#define SASR1_SADR&t;(1&lt;&lt;17)
DECL|macro|SASR1_RSTO
mdefine_line|#define SASR1_RSTO&t;(1&lt;&lt;18)
DECL|macro|SASR1_CLPM
mdefine_line|#define SASR1_CLPM&t;(1&lt;&lt;19)
DECL|macro|SASR1_CRDY
mdefine_line|#define SASR1_CRDY&t;(1&lt;&lt;20)
DECL|macro|SASR1_RS3V
mdefine_line|#define SASR1_RS3V&t;(1&lt;&lt;21)
DECL|macro|SASR1_RS4V
mdefine_line|#define SASR1_RS4V&t;(1&lt;&lt;22)
DECL|macro|SASCR_TUR
mdefine_line|#define SASCR_TUR&t;(1&lt;&lt;5)
DECL|macro|SASCR_ROR
mdefine_line|#define SASCR_ROR&t;(1&lt;&lt;6)
DECL|macro|SASCR_DTS
mdefine_line|#define SASCR_DTS&t;(1&lt;&lt;16)
DECL|macro|SASCR_RDD
mdefine_line|#define SASCR_RDD&t;(1&lt;&lt;17)
DECL|macro|SASCR_STO
mdefine_line|#define SASCR_STO&t;(1&lt;&lt;18)
DECL|macro|SADTCS_TDEN
mdefine_line|#define SADTCS_TDEN&t;(1&lt;&lt;0)
DECL|macro|SADTCS_TDIE
mdefine_line|#define SADTCS_TDIE&t;(1&lt;&lt;1)
DECL|macro|SADTCS_TDBDA
mdefine_line|#define SADTCS_TDBDA&t;(1&lt;&lt;3)
DECL|macro|SADTCS_TDSTA
mdefine_line|#define SADTCS_TDSTA&t;(1&lt;&lt;4)
DECL|macro|SADTCS_TDBDB
mdefine_line|#define SADTCS_TDBDB&t;(1&lt;&lt;5)
DECL|macro|SADTCS_TDSTB
mdefine_line|#define SADTCS_TDSTB&t;(1&lt;&lt;6)
DECL|macro|SADTCS_TBIU
mdefine_line|#define SADTCS_TBIU&t;(1&lt;&lt;7)
DECL|macro|SADRCS_RDEN
mdefine_line|#define SADRCS_RDEN&t;(1&lt;&lt;0)
DECL|macro|SADRCS_RDIE
mdefine_line|#define SADRCS_RDIE&t;(1&lt;&lt;1)
DECL|macro|SADRCS_RDBDA
mdefine_line|#define SADRCS_RDBDA&t;(1&lt;&lt;3)
DECL|macro|SADRCS_RDSTA
mdefine_line|#define SADRCS_RDSTA&t;(1&lt;&lt;4)
DECL|macro|SADRCS_RDBDB
mdefine_line|#define SADRCS_RDBDB&t;(1&lt;&lt;5)
DECL|macro|SADRCS_RDSTB
mdefine_line|#define SADRCS_RDSTB&t;(1&lt;&lt;6)
DECL|macro|SADRCS_RBIU
mdefine_line|#define SADRCS_RBIU&t;(1&lt;&lt;7)
DECL|macro|SAD_CS_DEN
mdefine_line|#define SAD_CS_DEN&t;(1&lt;&lt;0)
DECL|macro|SAD_CS_DIE
mdefine_line|#define SAD_CS_DIE&t;(1&lt;&lt;1)&t;/* Not functional on metal 1 */
DECL|macro|SAD_CS_DBDA
mdefine_line|#define SAD_CS_DBDA&t;(1&lt;&lt;3)&t;/* Not functional on metal 1 */
DECL|macro|SAD_CS_DSTA
mdefine_line|#define SAD_CS_DSTA&t;(1&lt;&lt;4)
DECL|macro|SAD_CS_DBDB
mdefine_line|#define SAD_CS_DBDB&t;(1&lt;&lt;5)&t;/* Not functional on metal 1 */
DECL|macro|SAD_CS_DSTB
mdefine_line|#define SAD_CS_DSTB&t;(1&lt;&lt;6)
DECL|macro|SAD_CS_BIU
mdefine_line|#define SAD_CS_BIU&t;(1&lt;&lt;7)&t;/* Not functional on metal 1 */
DECL|macro|SAITR_TFS
mdefine_line|#define SAITR_TFS&t;(1&lt;&lt;0)
DECL|macro|SAITR_RFS
mdefine_line|#define SAITR_RFS&t;(1&lt;&lt;1)
DECL|macro|SAITR_TUR
mdefine_line|#define SAITR_TUR&t;(1&lt;&lt;2)
DECL|macro|SAITR_ROR
mdefine_line|#define SAITR_ROR&t;(1&lt;&lt;3)
DECL|macro|SAITR_CADT
mdefine_line|#define SAITR_CADT&t;(1&lt;&lt;4)
DECL|macro|SAITR_SADR
mdefine_line|#define SAITR_SADR&t;(1&lt;&lt;5)
DECL|macro|SAITR_RSTO
mdefine_line|#define SAITR_RSTO&t;(1&lt;&lt;6)
DECL|macro|SAITR_TDBDA
mdefine_line|#define SAITR_TDBDA&t;(1&lt;&lt;8)
DECL|macro|SAITR_TDBDB
mdefine_line|#define SAITR_TDBDB&t;(1&lt;&lt;9)
DECL|macro|SAITR_RDBDA
mdefine_line|#define SAITR_RDBDA&t;(1&lt;&lt;10)
DECL|macro|SAITR_RDBDB
mdefine_line|#define SAITR_RDBDB&t;(1&lt;&lt;11)
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
mdefine_line|#define PA_DDR&t;&t;__CCREG(0x1000)
DECL|macro|PA_DRR
mdefine_line|#define PA_DRR&t;&t;__CCREG(0x1004)
DECL|macro|PA_DWR
mdefine_line|#define PA_DWR&t;&t;__CCREG(0x1004)
DECL|macro|PA_SDR
mdefine_line|#define PA_SDR&t;&t;__CCREG(0x1008)
DECL|macro|PA_SSR
mdefine_line|#define PA_SSR&t;&t;__CCREG(0x100c)
DECL|macro|PB_DDR
mdefine_line|#define PB_DDR&t;&t;__CCREG(0x1010)
DECL|macro|PB_DRR
mdefine_line|#define PB_DRR&t;&t;__CCREG(0x1014)
DECL|macro|PB_DWR
mdefine_line|#define PB_DWR&t;&t;__CCREG(0x1014)
DECL|macro|PB_SDR
mdefine_line|#define PB_SDR&t;&t;__CCREG(0x1018)
DECL|macro|PB_SSR
mdefine_line|#define PB_SSR&t;&t;__CCREG(0x101c)
DECL|macro|PC_DDR
mdefine_line|#define PC_DDR&t;&t;__CCREG(0x1020)
DECL|macro|PC_DRR
mdefine_line|#define PC_DRR&t;&t;__CCREG(0x1024)
DECL|macro|PC_DWR
mdefine_line|#define PC_DWR&t;&t;__CCREG(0x1024)
DECL|macro|PC_SDR
mdefine_line|#define PC_SDR&t;&t;__CCREG(0x1028)
DECL|macro|PC_SSR
mdefine_line|#define PC_SSR&t;&t;__CCREG(0x102c)
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * Interrupt Controller&n; *&n; * Registers&n; *    INTTEST0&t;&t;Test register 0&n; *    INTTEST1&t;&t;Test register 1&n; *    INTEN0&t;&t;Interrupt Enable register 0&n; *    INTEN1&t;&t;Interrupt Enable register 1&n; *    INTPOL0&t;&t;Interrupt Polarity selection 0&n; *    INTPOL1&t;&t;Interrupt Polarity selection 1&n; *    INTTSTSEL&t;&t;Interrupt source selection&n; *    INTSTATCLR0&t;Interrupt Status/Clear 0&n; *    INTSTATCLR1&t;Interrupt Status/Clear 1&n; *    INTSET0&t;&t;Interrupt source set 0&n; *    INTSET1&t;&t;Interrupt source set 1&n; *    WAKE_EN0&t;&t;Wake-up source enable 0&n; *    WAKE_EN1&t;&t;Wake-up source enable 1&n; *    WAKE_POL0&t;&t;Wake-up polarity selection 0&n; *    WAKE_POL1&t;&t;Wake-up polarity selection 1&n; */
DECL|macro|SA1111_INTTEST0
mdefine_line|#define SA1111_INTTEST0&t;&t;0x1600
DECL|macro|SA1111_INTTEST1
mdefine_line|#define SA1111_INTTEST1&t;&t;0x1604
DECL|macro|SA1111_INTEN0
mdefine_line|#define SA1111_INTEN0&t;&t;0x1608
DECL|macro|SA1111_INTEN1
mdefine_line|#define SA1111_INTEN1&t;&t;0x160c
DECL|macro|SA1111_INTPOL0
mdefine_line|#define SA1111_INTPOL0&t;&t;0x1610
DECL|macro|SA1111_INTPOL1
mdefine_line|#define SA1111_INTPOL1&t;&t;0x1614
DECL|macro|SA1111_INTTSTSEL
mdefine_line|#define SA1111_INTTSTSEL&t;0x1618
DECL|macro|SA1111_INTSTATCLR0
mdefine_line|#define SA1111_INTSTATCLR0&t;0x161c
DECL|macro|SA1111_INTSTATCLR1
mdefine_line|#define SA1111_INTSTATCLR1&t;0x1620
DECL|macro|SA1111_INTSET0
mdefine_line|#define SA1111_INTSET0&t;&t;0x1624
DECL|macro|SA1111_INTSET1
mdefine_line|#define SA1111_INTSET1&t;&t;0x1628
DECL|macro|SA1111_WAKE_EN0
mdefine_line|#define SA1111_WAKE_EN0&t;&t;0x162c
DECL|macro|SA1111_WAKE_EN1
mdefine_line|#define SA1111_WAKE_EN1&t;&t;0x1630
DECL|macro|SA1111_WAKE_POL0
mdefine_line|#define SA1111_WAKE_POL0&t;0x1634
DECL|macro|SA1111_WAKE_POL1
mdefine_line|#define SA1111_WAKE_POL1&t;0x1638
DECL|macro|_INTTEST0
mdefine_line|#define _INTTEST0&t;_SA1111(SA1111_INTTEST0)
DECL|macro|_INTTEST1
mdefine_line|#define _INTTEST1&t;_SA1111(SA1111_INTTEST1)
DECL|macro|_INTEN0
mdefine_line|#define _INTEN0&t;&t;_SA1111(SA1111_INTEN0)
DECL|macro|_INTEN1
mdefine_line|#define _INTEN1&t;&t;_SA1111(SA1111_INTEN1)
DECL|macro|_INTPOL0
mdefine_line|#define _INTPOL0&t;_SA1111(SA1111_INTPOL0)
DECL|macro|_INTPOL1
mdefine_line|#define _INTPOL1&t;_SA1111(SA1111_INTPOL1)
DECL|macro|_INTTSTSEL
mdefine_line|#define _INTTSTSEL&t;_SA1111(SA1111_INTTSTSEL)
DECL|macro|_INTSTATCLR0
mdefine_line|#define _INTSTATCLR0&t;_SA1111(SA1111_INTSTATCLR0)
DECL|macro|_INTSTATCLR1
mdefine_line|#define _INTSTATCLR1&t;_SA1111(SA1111_INTSTATCLR1)
DECL|macro|_INTSET0
mdefine_line|#define _INTSET0&t;_SA1111(SA1111_INTSET0)
DECL|macro|_INTSET1
mdefine_line|#define _INTSET1&t;_SA1111(SA1111_INTSET1)
DECL|macro|_WAKE_EN0
mdefine_line|#define _WAKE_EN0&t;_SA1111(SA1111_WAKE_EN0)
DECL|macro|_WAKE_EN1
mdefine_line|#define _WAKE_EN1&t;_SA1111(SA1111_WAKE_EN1)
DECL|macro|_WAKE_POL0
mdefine_line|#define _WAKE_POL0&t;_SA1111(SA1111_WAKE_POL0)
DECL|macro|_WAKE_POL1
mdefine_line|#define _WAKE_POL1&t;_SA1111(SA1111_WAKE_POL1)
macro_line|#if LANGUAGE == C
DECL|macro|INTTEST0
mdefine_line|#define INTTEST0&t;__CCREG(SA1111_INTTEST0)
DECL|macro|INTTEST1
mdefine_line|#define INTTEST1&t;__CCREG(SA1111_INTTEST1)
DECL|macro|INTEN0
mdefine_line|#define INTEN0&t;&t;__CCREG(SA1111_INTEN0)
DECL|macro|INTEN1
mdefine_line|#define INTEN1&t;&t;__CCREG(SA1111_INTEN1)
DECL|macro|INTPOL0
mdefine_line|#define INTPOL0&t;&t;__CCREG(SA1111_INTPOL0)
DECL|macro|INTPOL1
mdefine_line|#define INTPOL1&t;&t;__CCREG(SA1111_INTPOL1)
DECL|macro|INTTSTSEL
mdefine_line|#define INTTSTSEL&t;__CCREG(SA1111_INTTSTSEL)
DECL|macro|INTSTATCLR0
mdefine_line|#define INTSTATCLR0&t;__CCREG(SA1111_INTSTATCLR0)
DECL|macro|INTSTATCLR1
mdefine_line|#define INTSTATCLR1&t;__CCREG(SA1111_INTSTATCLR1)
DECL|macro|INTSET0
mdefine_line|#define INTSET0&t;&t;__CCREG(SA1111_INTSET0)
DECL|macro|INTSET1
mdefine_line|#define INTSET1&t;&t;__CCREG(SA1111_INTSET1)
DECL|macro|WAKE_EN0
mdefine_line|#define WAKE_EN0&t;__CCREG(SA1111_WAKE_EN0)
DECL|macro|WAKE_EN1
mdefine_line|#define WAKE_EN1&t;__CCREG(SA1111_WAKE_EN1)
DECL|macro|WAKE_POL0
mdefine_line|#define WAKE_POL0&t;__CCREG(SA1111_WAKE_POL0)
DECL|macro|WAKE_POL1
mdefine_line|#define WAKE_POL1&t;__CCREG(SA1111_WAKE_POL1)
macro_line|#endif  /* LANGUAGE == C */
multiline_comment|/*&n; * PS/2 Trackpad and Mouse Interfaces&n; *&n; * Registers   (prefix kbd applies to trackpad interface, mse to mouse)&n; *    KBDCR     Control Register&n; *    KBDSTAT       Status Register&n; *    KBDDATA       Transmit/Receive Data register&n; *    KBDCLKDIV     Clock Division Register&n; *    KBDPRECNT     Clock Precount Register&n; *    KBDTEST1      Test register 1&n; *    KBDTEST2      Test register 2&n; *    KBDTEST3      Test register 3&n; *    KBDTEST4      Test register 4&n; *    MSECR&n; *    MSESTAT&n; *    MSEDATA&n; *    MSECLKDIV&n; *    MSEPRECNT&n; *    MSETEST1&n; *    MSETEST2&n; *    MSETEST3&n; *    MSETEST4&n; *&n; */
DECL|macro|_KBD
mdefine_line|#define _KBD( x )   _SA1111( 0x0A00 )
DECL|macro|_MSE
mdefine_line|#define _MSE( x )   _SA1111( 0x0C00 )
DECL|macro|_KBDCR
mdefine_line|#define _KBDCR&t;    _SA1111( 0x0A00 )
DECL|macro|_KBDSTAT
mdefine_line|#define _KBDSTAT    _SA1111( 0x0A04 )
DECL|macro|_KBDDATA
mdefine_line|#define _KBDDATA    _SA1111( 0x0A08 )
DECL|macro|_KBDCLKDIV
mdefine_line|#define _KBDCLKDIV  _SA1111( 0x0A0C )
DECL|macro|_KBDPRECNT
mdefine_line|#define _KBDPRECNT  _SA1111( 0x0A10 )
DECL|macro|_MSECR
mdefine_line|#define _MSECR&t;    _SA1111( 0x0C00 )
DECL|macro|_MSESTAT
mdefine_line|#define _MSESTAT    _SA1111( 0x0C04 )
DECL|macro|_MSEDATA
mdefine_line|#define _MSEDATA    _SA1111( 0x0C08 )
DECL|macro|_MSECLKDIV
mdefine_line|#define _MSECLKDIV  _SA1111( 0x0C0C )
DECL|macro|_MSEPRECNT
mdefine_line|#define _MSEPRECNT  _SA1111( 0x0C10 )
macro_line|#if ( LANGUAGE == C )
DECL|macro|KBDCR
mdefine_line|#define KBDCR&t;&t;__CCREG(0x0a00)
DECL|macro|KBDSTAT
mdefine_line|#define KBDSTAT&t;&t;__CCREG(0x0a04)
DECL|macro|KBDDATA
mdefine_line|#define KBDDATA&t;&t;__CCREG(0x0a08)
DECL|macro|KBDCLKDIV
mdefine_line|#define KBDCLKDIV&t;__CCREG(0x0a0c)
DECL|macro|KBDPRECNT
mdefine_line|#define KBDPRECNT&t;__CCREG(0x0a10)
DECL|macro|MSECR
mdefine_line|#define MSECR&t;&t;__CCREG(0x0c00)
DECL|macro|MSESTAT
mdefine_line|#define MSESTAT&t;&t;__CCREG(0x0c04)
DECL|macro|MSEDATA
mdefine_line|#define MSEDATA&t;&t;__CCREG(0x0c08)
DECL|macro|MSECLKDIV
mdefine_line|#define MSECLKDIV&t;__CCREG(0x0c0c)
DECL|macro|MSEPRECNT
mdefine_line|#define MSEPRECNT&t;__CCREG(0x0c10)
DECL|macro|KBDCR_ENA
mdefine_line|#define KBDCR_ENA        0x08
DECL|macro|KBDCR_FKD
mdefine_line|#define KBDCR_FKD        0x02
DECL|macro|KBDCR_FKC
mdefine_line|#define KBDCR_FKC        0x01
DECL|macro|KBDSTAT_TXE
mdefine_line|#define KBDSTAT_TXE      0x80
DECL|macro|KBDSTAT_TXB
mdefine_line|#define KBDSTAT_TXB      0x40
DECL|macro|KBDSTAT_RXF
mdefine_line|#define KBDSTAT_RXF      0x20
DECL|macro|KBDSTAT_RXB
mdefine_line|#define KBDSTAT_RXB      0x10
DECL|macro|KBDSTAT_ENA
mdefine_line|#define KBDSTAT_ENA      0x08
DECL|macro|KBDSTAT_RXP
mdefine_line|#define KBDSTAT_RXP      0x04
DECL|macro|KBDSTAT_KBD
mdefine_line|#define KBDSTAT_KBD      0x02
DECL|macro|KBDSTAT_KBC
mdefine_line|#define KBDSTAT_KBC      0x01
DECL|macro|KBDCLKDIV_DivVal
mdefine_line|#define KBDCLKDIV_DivVal     Fld(4,0)
DECL|macro|MSECR_ENA
mdefine_line|#define MSECR_ENA        0x08
DECL|macro|MSECR_FKD
mdefine_line|#define MSECR_FKD        0x02
DECL|macro|MSECR_FKC
mdefine_line|#define MSECR_FKC        0x01
DECL|macro|MSESTAT_TXE
mdefine_line|#define MSESTAT_TXE      0x80
DECL|macro|MSESTAT_TXB
mdefine_line|#define MSESTAT_TXB      0x40
DECL|macro|MSESTAT_RXF
mdefine_line|#define MSESTAT_RXF      0x20
DECL|macro|MSESTAT_RXB
mdefine_line|#define MSESTAT_RXB      0x10
DECL|macro|MSESTAT_ENA
mdefine_line|#define MSESTAT_ENA      0x08
DECL|macro|MSESTAT_RXP
mdefine_line|#define MSESTAT_RXP      0x04
DECL|macro|MSESTAT_MSD
mdefine_line|#define MSESTAT_MSD      0x02
DECL|macro|MSESTAT_MSC
mdefine_line|#define MSESTAT_MSC      0x01
DECL|macro|MSECLKDIV_DivVal
mdefine_line|#define MSECLKDIV_DivVal     Fld(4,0)
DECL|macro|KBDTEST1_CD
mdefine_line|#define KBDTEST1_CD      0x80
DECL|macro|KBDTEST1_RC1
mdefine_line|#define KBDTEST1_RC1         0x40
DECL|macro|KBDTEST1_MC
mdefine_line|#define KBDTEST1_MC      0x20
DECL|macro|KBDTEST1_C
mdefine_line|#define KBDTEST1_C       Fld(2,3)
DECL|macro|KBDTEST1_T2
mdefine_line|#define KBDTEST1_T2      0x40
DECL|macro|KBDTEST1_T1
mdefine_line|#define KBDTEST1_T1      0x20
DECL|macro|KBDTEST1_T0
mdefine_line|#define KBDTEST1_T0      0x10
DECL|macro|KBDTEST2_TICBnRES
mdefine_line|#define KBDTEST2_TICBnRES    0x08
DECL|macro|KBDTEST2_RKC
mdefine_line|#define KBDTEST2_RKC         0x04
DECL|macro|KBDTEST2_RKD
mdefine_line|#define KBDTEST2_RKD         0x02
DECL|macro|KBDTEST2_SEL
mdefine_line|#define KBDTEST2_SEL         0x01
DECL|macro|KBDTEST3_ms_16
mdefine_line|#define KBDTEST3_ms_16       0x80
DECL|macro|KBDTEST3_us_64
mdefine_line|#define KBDTEST3_us_64       0x40
DECL|macro|KBDTEST3_us_16
mdefine_line|#define KBDTEST3_us_16       0x20
DECL|macro|KBDTEST3_DIV8
mdefine_line|#define KBDTEST3_DIV8        0x10
DECL|macro|KBDTEST3_DIn
mdefine_line|#define KBDTEST3_DIn         0x08
DECL|macro|KBDTEST3_CIn
mdefine_line|#define KBDTEST3_CIn         0x04
DECL|macro|KBDTEST3_KD
mdefine_line|#define KBDTEST3_KD      0x02
DECL|macro|KBDTEST3_KC
mdefine_line|#define KBDTEST3_KC      0x01
DECL|macro|KBDTEST4_BC12
mdefine_line|#define KBDTEST4_BC12        0x80
DECL|macro|KBDTEST4_BC11
mdefine_line|#define KBDTEST4_BC11        0x40
DECL|macro|KBDTEST4_TRES
mdefine_line|#define KBDTEST4_TRES        0x20
DECL|macro|KBDTEST4_CLKOE
mdefine_line|#define KBDTEST4_CLKOE       0x10
DECL|macro|KBDTEST4_CRES
mdefine_line|#define KBDTEST4_CRES        0x08
DECL|macro|KBDTEST4_RXB
mdefine_line|#define KBDTEST4_RXB         0x04
DECL|macro|KBDTEST4_TXB
mdefine_line|#define KBDTEST4_TXB         0x02
DECL|macro|KBDTEST4_SRX
mdefine_line|#define KBDTEST4_SRX         0x01
DECL|macro|MSETEST1_CD
mdefine_line|#define MSETEST1_CD      0x80
DECL|macro|MSETEST1_RC1
mdefine_line|#define MSETEST1_RC1         0x40
DECL|macro|MSETEST1_MC
mdefine_line|#define MSETEST1_MC      0x20
DECL|macro|MSETEST1_C
mdefine_line|#define MSETEST1_C       Fld(2,3)
DECL|macro|MSETEST1_T2
mdefine_line|#define MSETEST1_T2      0x40
DECL|macro|MSETEST1_T1
mdefine_line|#define MSETEST1_T1      0x20
DECL|macro|MSETEST1_T0
mdefine_line|#define MSETEST1_T0      0x10
DECL|macro|MSETEST2_TICBnRES
mdefine_line|#define MSETEST2_TICBnRES    0x08
DECL|macro|MSETEST2_RKC
mdefine_line|#define MSETEST2_RKC         0x04
DECL|macro|MSETEST2_RKD
mdefine_line|#define MSETEST2_RKD         0x02
DECL|macro|MSETEST2_SEL
mdefine_line|#define MSETEST2_SEL         0x01
DECL|macro|MSETEST3_ms_16
mdefine_line|#define MSETEST3_ms_16       0x80
DECL|macro|MSETEST3_us_64
mdefine_line|#define MSETEST3_us_64       0x40
DECL|macro|MSETEST3_us_16
mdefine_line|#define MSETEST3_us_16       0x20
DECL|macro|MSETEST3_DIV8
mdefine_line|#define MSETEST3_DIV8        0x10
DECL|macro|MSETEST3_DIn
mdefine_line|#define MSETEST3_DIn         0x08
DECL|macro|MSETEST3_CIn
mdefine_line|#define MSETEST3_CIn         0x04
DECL|macro|MSETEST3_KD
mdefine_line|#define MSETEST3_KD      0x02
DECL|macro|MSETEST3_KC
mdefine_line|#define MSETEST3_KC      0x01
DECL|macro|MSETEST4_BC12
mdefine_line|#define MSETEST4_BC12        0x80
DECL|macro|MSETEST4_BC11
mdefine_line|#define MSETEST4_BC11        0x40
DECL|macro|MSETEST4_TRES
mdefine_line|#define MSETEST4_TRES        0x20
DECL|macro|MSETEST4_CLKOE
mdefine_line|#define MSETEST4_CLKOE       0x10
DECL|macro|MSETEST4_CRES
mdefine_line|#define MSETEST4_CRES        0x08
DECL|macro|MSETEST4_RXB
mdefine_line|#define MSETEST4_RXB         0x04
DECL|macro|MSETEST4_TXB
mdefine_line|#define MSETEST4_TXB         0x02
DECL|macro|MSETEST4_SRX
mdefine_line|#define MSETEST4_SRX         0x01
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
mdefine_line|#define PCCR&t;&t;__CCREG(0x1800)
DECL|macro|PCSSR
mdefine_line|#define PCSSR&t;&t;__CCREG(0x1804)
DECL|macro|PCSR
mdefine_line|#define PCSR&t;&t;__CCREG(0x1808)
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
DECL|struct|sa1111_device
r_struct
id|sa1111_device
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|resource
r_struct
id|resource
id|resource
suffix:semicolon
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sa1111_device
op_star
id|sa1111
suffix:semicolon
macro_line|#endif  /* _ASM_ARCH_SA1111 */
eof
