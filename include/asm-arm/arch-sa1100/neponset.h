multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/assabet.h&n; *&n; * Created 2000/06/05 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware specific definitions for Assabet&n; * Only include this file from SA1100-specific files.&n; *&n; * 2000/05/23 John Dorsey &lt;john+@cs.cmu.edu&gt;&n; *      Definitions for Neponset added.&n; */
macro_line|#ifndef __ASM_ARCH_NEPONSET_H
DECL|macro|__ASM_ARCH_NEPONSET_H
mdefine_line|#define __ASM_ARCH_NEPONSET_H
multiline_comment|/*&n; * Neponset definitions: &n; */
DECL|macro|NEPONSET_CPLD_BASE
mdefine_line|#define NEPONSET_CPLD_BASE      (0x10000000)
DECL|macro|Nep_p2v
mdefine_line|#define Nep_p2v( x )            ((x) - NEPONSET_CPLD_BASE + 0xf3000000)
DECL|macro|Nep_v2p
mdefine_line|#define Nep_v2p( x )            ((x) - 0xf3000000 + NEPONSET_CPLD_BASE)
DECL|macro|_IRR
mdefine_line|#define _IRR                    0x10000024      /* Interrupt Reason Register */
DECL|macro|_AUD_CTL
mdefine_line|#define _AUD_CTL                0x100000c0      /* Audio controls (RW)       */
DECL|macro|_MDM_CTL_0
mdefine_line|#define _MDM_CTL_0              0x100000b0      /* Modem control 0 (RW)      */
DECL|macro|_MDM_CTL_1
mdefine_line|#define _MDM_CTL_1              0x100000b4      /* Modem control 1 (RW)      */
DECL|macro|_NCR_0
mdefine_line|#define _NCR_0&t;                0x100000a0      /* Control Register (RW)     */
DECL|macro|_KP_X_OUT
mdefine_line|#define _KP_X_OUT               0x10000090      /* Keypad row write (RW)     */
DECL|macro|_KP_Y_IN
mdefine_line|#define _KP_Y_IN                0x10000080      /* Keypad column read (RO)   */
DECL|macro|_SWPK
mdefine_line|#define _SWPK                   0x10000020      /* Switch pack (RO)          */
DECL|macro|_WHOAMI
mdefine_line|#define _WHOAMI                 0x10000000      /* System ID Register (RO)   */
DECL|macro|_LEDS
mdefine_line|#define _LEDS                   0x10000010      /* LEDs [31:0] (WO)          */
DECL|macro|IRR
mdefine_line|#define IRR                     (*((volatile u_char *) Nep_p2v(_IRR)))
DECL|macro|AUD_CTL
mdefine_line|#define AUD_CTL                 (*((volatile u_char *) Nep_p2v(_AUD_CTL)))
DECL|macro|MDM_CTL_0
mdefine_line|#define MDM_CTL_0               (*((volatile u_char *) Nep_p2v(_MDM_CTL_0)))
DECL|macro|MDM_CTL_1
mdefine_line|#define MDM_CTL_1               (*((volatile u_char *) Nep_p2v(_MDM_CTL_1)))
DECL|macro|NCR_0
mdefine_line|#define NCR_0&t;&t;&t;(*((volatile u_char *) Nep_p2v(_NCR_0)))
DECL|macro|KP_X_OUT
mdefine_line|#define KP_X_OUT                (*((volatile u_char *) Nep_p2v(_KP_X_OUT)))
DECL|macro|KP_Y_IN
mdefine_line|#define KP_Y_IN                 (*((volatile u_char *) Nep_p2v(_KP_Y_IN)))
DECL|macro|SWPK
mdefine_line|#define SWPK                    (*((volatile u_char *) Nep_p2v(_SWPK)))
DECL|macro|WHOAMI
mdefine_line|#define WHOAMI                  (*((volatile u_char *) Nep_p2v(_WHOAMI)))
DECL|macro|LEDS
mdefine_line|#define LEDS                    (*((volatile Word   *) Nep_p2v(_LEDS)))
DECL|macro|IRR_ETHERNET
mdefine_line|#define IRR_ETHERNET&t;&t;(1&lt;&lt;0)
DECL|macro|IRR_USAR
mdefine_line|#define IRR_USAR&t;&t;(1&lt;&lt;1)
DECL|macro|IRR_SA1111
mdefine_line|#define IRR_SA1111&t;&t;(1&lt;&lt;2)
DECL|macro|AUD_SEL_1341
mdefine_line|#define AUD_SEL_1341            (1&lt;&lt;0)
DECL|macro|AUD_MUTE_1341
mdefine_line|#define AUD_MUTE_1341           (1&lt;&lt;1)
DECL|macro|MDM_CTL0_RTS1
mdefine_line|#define MDM_CTL0_RTS1&t;&t;(1 &lt;&lt; 0)
DECL|macro|MDM_CTL0_DTR1
mdefine_line|#define MDM_CTL0_DTR1&t;&t;(1 &lt;&lt; 1)
DECL|macro|MDM_CTL0_RTS2
mdefine_line|#define MDM_CTL0_RTS2&t;&t;(1 &lt;&lt; 2)
DECL|macro|MDM_CTL0_DTR2
mdefine_line|#define MDM_CTL0_DTR2&t;&t;(1 &lt;&lt; 3)
DECL|macro|MDM_CTL1_CTS1
mdefine_line|#define MDM_CTL1_CTS1&t;&t;(1 &lt;&lt; 0)
DECL|macro|MDM_CTL1_DSR1
mdefine_line|#define MDM_CTL1_DSR1&t;&t;(1 &lt;&lt; 1)
DECL|macro|MDM_CTL1_DCD1
mdefine_line|#define MDM_CTL1_DCD1&t;&t;(1 &lt;&lt; 2)
DECL|macro|MDM_CTL1_CTS2
mdefine_line|#define MDM_CTL1_CTS2&t;&t;(1 &lt;&lt; 3)
DECL|macro|MDM_CTL1_DSR2
mdefine_line|#define MDM_CTL1_DSR2&t;&t;(1 &lt;&lt; 4)
DECL|macro|MDM_CTL1_DCD2
mdefine_line|#define MDM_CTL1_DCD2&t;&t;(1 &lt;&lt; 5)
DECL|macro|NCR_GP01_OFF
mdefine_line|#define NCR_GP01_OFF&t;&t;(1&lt;&lt;0)
DECL|macro|NCR_TP_PWR_EN
mdefine_line|#define NCR_TP_PWR_EN&t;&t;(1&lt;&lt;1)
DECL|macro|NCR_MS_PWR_EN
mdefine_line|#define NCR_MS_PWR_EN&t;&t;(1&lt;&lt;2)
DECL|macro|NCR_ENET_OSC_EN
mdefine_line|#define NCR_ENET_OSC_EN&t;&t;(1&lt;&lt;3)
DECL|macro|NCR_SPI_KB_WK_UP
mdefine_line|#define NCR_SPI_KB_WK_UP&t;(1&lt;&lt;4)
DECL|macro|NCR_A0VPP
mdefine_line|#define NCR_A0VPP&t;&t;(1&lt;&lt;5)
DECL|macro|NCR_A1VPP
mdefine_line|#define NCR_A1VPP&t;&t;(1&lt;&lt;6)
macro_line|#endif
eof
