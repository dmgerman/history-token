multiline_comment|/*&n; * arch/ppc/kernel/ipic.h&n; *&n; * IPIC private definitions and structure.&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __IPIC_H__
DECL|macro|__IPIC_H__
mdefine_line|#define __IPIC_H__
macro_line|#include &lt;asm/ipic.h&gt;
DECL|macro|MPC83xx_IPIC_SIZE
mdefine_line|#define MPC83xx_IPIC_SIZE&t;(0x00100)
multiline_comment|/* System Global Interrupt Configuration Register */
DECL|macro|SICFR_IPSA
mdefine_line|#define&t;SICFR_IPSA&t;0x00010000
DECL|macro|SICFR_IPSD
mdefine_line|#define&t;SICFR_IPSD&t;0x00080000
DECL|macro|SICFR_MPSA
mdefine_line|#define&t;SICFR_MPSA&t;0x00200000
DECL|macro|SICFR_MPSB
mdefine_line|#define&t;SICFR_MPSB&t;0x00400000
multiline_comment|/* System External Interrupt Mask Register */
DECL|macro|SEMSR_SIRQ0
mdefine_line|#define&t;SEMSR_SIRQ0&t;0x00008000
multiline_comment|/* System Error Control Register */
DECL|macro|SERCR_MCPR
mdefine_line|#define SERCR_MCPR&t;0x00000001
DECL|struct|ipic
r_struct
id|ipic
(brace
DECL|member|regs
r_volatile
id|u32
id|__iomem
op_star
id|regs
suffix:semicolon
DECL|member|irq_offset
r_int
r_int
id|irq_offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipic_info
r_struct
id|ipic_info
(brace
DECL|member|pend
id|u8
id|pend
suffix:semicolon
multiline_comment|/* pending register offset from base */
DECL|member|mask
id|u8
id|mask
suffix:semicolon
multiline_comment|/* mask register offset from base */
DECL|member|prio
id|u8
id|prio
suffix:semicolon
multiline_comment|/* priority register offset from base */
DECL|member|force
id|u8
id|force
suffix:semicolon
multiline_comment|/* force register offset from base */
DECL|member|bit
id|u8
id|bit
suffix:semicolon
multiline_comment|/* register bit position (as per doc)&n;&t;&t;&t;&t;   bit mask = 1 &lt;&lt; (31 - bit) */
DECL|member|prio_mask
id|u8
id|prio_mask
suffix:semicolon
multiline_comment|/* priority mask value */
)brace
suffix:semicolon
macro_line|#endif /* __IPIC_H__ */
eof
