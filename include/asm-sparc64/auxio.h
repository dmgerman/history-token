multiline_comment|/* $Id: auxio.h,v 1.3 2001/06/05 08:16:34 davem Exp $&n; * auxio.h:  Definitions and code for the Auxiliary I/O registers.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Refactoring for unified NCR/PCIO support 2002 Eric Brower (ebrower@usa.net)&n; */
macro_line|#ifndef _SPARC64_AUXIO_H
DECL|macro|_SPARC64_AUXIO_H
mdefine_line|#define _SPARC64_AUXIO_H
multiline_comment|/* AUXIO implementations:&n; * sbus-based NCR89C105 &quot;Slavio&quot;&n; *&t;LED/Floppy (AUX1) register&n; *&t;Power (AUX2) register&n; *&n; * ebus-based auxio on PCIO &n; *&t;LED Auxio Register&n; *&t;Power Auxio Register&n; *&n; * Register definitions from NCR _NCR89C105 Chip Specification_&n; * &n; * SLAVIO AUX1 @ 0x1900000&n; * -------------------------------------------------&n; * | (R) | (R) |  D  | (R) |  E  |  M  |  T  |  L  |&n; * -------------------------------------------------&n; * (R) - bit 7:6,4 are reserved and should be masked in s/w&n; *  D  - Floppy Density Sense (1=high density) R/O&n; *  E  - Link Test Enable, directly reflected on AT&amp;T 7213 LTE pin&n; *  M  - Monitor/Mouse Mux, directly reflected on MON_MSE_MUX pin&n; *  T  - Terminal Count: sends TC pulse to 82077 floppy controller&n; *  L  - System LED on front panel (0=off, 1=on) &n; */
DECL|macro|AUXIO_AUX1_MASK
mdefine_line|#define AUXIO_AUX1_MASK&t;&t;0xc0 /* Mask bits &t;&t;*/
DECL|macro|AUXIO_AUX1_FDENS
mdefine_line|#define AUXIO_AUX1_FDENS&t;0x20 /* Floppy Density Sense&t;*/
DECL|macro|AUXIO_AUX1_LTE
mdefine_line|#define AUXIO_AUX1_LTE &t;&t;0x08 /* Link Test Enable &t;*/
DECL|macro|AUXIO_AUX1_MMUX
mdefine_line|#define AUXIO_AUX1_MMUX&t;&t;0x04 /* Monitor/Mouse Mux&t;*/
DECL|macro|AUXIO_AUX1_FTCNT
mdefine_line|#define AUXIO_AUX1_FTCNT&t;0x02 /* Terminal Count, &t;*/
DECL|macro|AUXIO_AUX1_LED
mdefine_line|#define AUXIO_AUX1_LED&t;&t;0x01 /* System LED&t;&t;*/
multiline_comment|/* SLAVIO AUX2 @ 0x1910000&n; * -------------------------------------------------&n; * | (R) | (R) |  D  | (R) | (R) | (R) |  C  |  F  |&n; * -------------------------------------------------&n; * (R) - bits 7:6,4:2 are reserved and should be masked in s/w&n; *  D  - Power Failure Detect (1=power fail)&n; *  C  - Clear Power Failure Detect Int (1=clear)&n; *  F  - Power Off (1=power off)&n; */
DECL|macro|AUXIO_AUX2_MASK
mdefine_line|#define AUXIO_AUX2_MASK&t;&t;0xdc /* Mask Bits&t;&t;*/
DECL|macro|AUXIO_AUX2_PFAILDET
mdefine_line|#define AUXIO_AUX2_PFAILDET&t;0x20 /* Power Fail Detect&t;*/
DECL|macro|AUXIO_AUX2_PFAILCLR
mdefine_line|#define AUXIO_AUX2_PFAILCLR &t;0x02 /* Clear Pwr Fail Det Intr&t;*/
DECL|macro|AUXIO_AUX2_PWR_OFF
mdefine_line|#define AUXIO_AUX2_PWR_OFF&t;0x01 /* Power Off&t;&t;*/
multiline_comment|/* Register definitions from Sun Microsystems _PCIO_ p/n 802-7837&n; *&n; * PCIO LED Auxio @ 0x726000&n; * -------------------------------------------------&n; * |             31:1 Unused                 | LED |&n; * -------------------------------------------------&n; * Bits 31:1 unused&n; * LED - System LED on front panel (0=off, 1=on)&n; */
DECL|macro|AUXIO_PCIO_LED
mdefine_line|#define AUXIO_PCIO_LED&t;&t;0x01 /* System LED &t;&t;*/ 
multiline_comment|/* PCIO Power Auxio @ 0x724000&n; * -------------------------------------------------&n; * |             31:2 Unused           | CPO | SPO |&n; * -------------------------------------------------&n; * Bits 31:2 unused&n; * CPO - Courtesy Power Off (1=off)&n; * SPO - System Power Off   (1=off)&n; */
DECL|macro|AUXIO_PCIO_CPWR_OFF
mdefine_line|#define AUXIO_PCIO_CPWR_OFF&t;0x02 /* Courtesy Power Off&t;*/
DECL|macro|AUXIO_PCIO_SPWR_OFF
mdefine_line|#define AUXIO_PCIO_SPWR_OFF&t;0x01 /* System Power Off&t;*/
macro_line|#ifndef __ASSEMBLY__
DECL|macro|AUXIO_LTE_ON
mdefine_line|#define AUXIO_LTE_ON&t;1
DECL|macro|AUXIO_LTE_OFF
mdefine_line|#define AUXIO_LTE_OFF&t;0
multiline_comment|/* auxio_set_lte - Set Link Test Enable (TPE Link Detect)&n; *&n; * on - AUXIO_LTE_ON or AUXIO_LTE_OFF&n; */
r_extern
r_void
id|auxio_set_lte
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
DECL|macro|AUXIO_LED_ON
mdefine_line|#define AUXIO_LED_ON&t;1
DECL|macro|AUXIO_LED_OFF
mdefine_line|#define AUXIO_LED_OFF&t;0
multiline_comment|/* auxio_set_led - Set system front panel LED &n; *&n; * on - AUXIO_LED_ON or AUXIO_LED_OFF&n; */
r_extern
r_void
id|auxio_set_led
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
macro_line|#endif /* ifndef __ASSEMBLY__ */ 
macro_line|#endif /* !(_SPARC64_AUXIO_H) */
eof
