multiline_comment|/*&n; * include/asm-ppc/ipic.h&n; *&n; * IPIC external definitions and structure.&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2005 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IPIC_H__
DECL|macro|__ASM_IPIC_H__
mdefine_line|#define __ASM_IPIC_H__
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/* Flags when we init the IPIC */
DECL|macro|IPIC_SPREADMODE_GRP_A
mdefine_line|#define IPIC_SPREADMODE_GRP_A&t;0x00000001
DECL|macro|IPIC_SPREADMODE_GRP_D
mdefine_line|#define IPIC_SPREADMODE_GRP_D&t;0x00000002
DECL|macro|IPIC_SPREADMODE_MIX_A
mdefine_line|#define IPIC_SPREADMODE_MIX_A&t;0x00000004
DECL|macro|IPIC_SPREADMODE_MIX_B
mdefine_line|#define IPIC_SPREADMODE_MIX_B&t;0x00000008
DECL|macro|IPIC_DISABLE_MCP_OUT
mdefine_line|#define IPIC_DISABLE_MCP_OUT&t;0x00000010
DECL|macro|IPIC_IRQ0_MCP
mdefine_line|#define IPIC_IRQ0_MCP&t;&t;0x00000020
multiline_comment|/* IPIC registers offsets */
DECL|macro|IPIC_SICFR
mdefine_line|#define IPIC_SICFR&t;0x00&t;/* System Global Interrupt Configuration Register */
DECL|macro|IPIC_SIVCR
mdefine_line|#define IPIC_SIVCR&t;0x04&t;/* System Global Interrupt Vector Register */
DECL|macro|IPIC_SIPNR_H
mdefine_line|#define IPIC_SIPNR_H&t;0x08&t;/* System Internal Interrupt Pending Register (HIGH) */
DECL|macro|IPIC_SIPNR_L
mdefine_line|#define IPIC_SIPNR_L&t;0x0C&t;/* System Internal Interrupt Pending Register (LOW) */
DECL|macro|IPIC_SIPRR_A
mdefine_line|#define IPIC_SIPRR_A&t;0x10&t;/* System Internal Interrupt group A Priority Register */
DECL|macro|IPIC_SIPRR_B
mdefine_line|#define IPIC_SIPRR_B&t;0x14&t;/* System Internal Interrupt group B Priority Register */
DECL|macro|IPIC_SIPRR_C
mdefine_line|#define IPIC_SIPRR_C&t;0x18&t;/* System Internal Interrupt group C Priority Register */
DECL|macro|IPIC_SIPRR_D
mdefine_line|#define IPIC_SIPRR_D&t;0x1C&t;/* System Internal Interrupt group D Priority Register */
DECL|macro|IPIC_SIMSR_H
mdefine_line|#define IPIC_SIMSR_H&t;0x20&t;/* System Internal Interrupt Mask Register (HIGH) */
DECL|macro|IPIC_SIMSR_L
mdefine_line|#define IPIC_SIMSR_L&t;0x24&t;/* System Internal Interrupt Mask Register (LOW) */
DECL|macro|IPIC_SICNR
mdefine_line|#define IPIC_SICNR&t;0x28&t;/* System Internal Interrupt Control Register */
DECL|macro|IPIC_SEPNR
mdefine_line|#define IPIC_SEPNR&t;0x2C&t;/* System External Interrupt Pending Register */
DECL|macro|IPIC_SMPRR_A
mdefine_line|#define IPIC_SMPRR_A&t;0x30&t;/* System Mixed Interrupt group A Priority Register */
DECL|macro|IPIC_SMPRR_B
mdefine_line|#define IPIC_SMPRR_B&t;0x34&t;/* System Mixed Interrupt group B Priority Register */
DECL|macro|IPIC_SEMSR
mdefine_line|#define IPIC_SEMSR&t;0x38&t;/* System External Interrupt Mask Register */
DECL|macro|IPIC_SECNR
mdefine_line|#define IPIC_SECNR&t;0x3C&t;/* System External Interrupt Control Register */
DECL|macro|IPIC_SERSR
mdefine_line|#define IPIC_SERSR&t;0x40&t;/* System Error Status Register */
DECL|macro|IPIC_SERMR
mdefine_line|#define IPIC_SERMR&t;0x44&t;/* System Error Mask Register */
DECL|macro|IPIC_SERCR
mdefine_line|#define IPIC_SERCR&t;0x48&t;/* System Error Control Register */
DECL|macro|IPIC_SIFCR_H
mdefine_line|#define IPIC_SIFCR_H&t;0x50&t;/* System Internal Interrupt Force Register (HIGH) */
DECL|macro|IPIC_SIFCR_L
mdefine_line|#define IPIC_SIFCR_L&t;0x54&t;/* System Internal Interrupt Force Register (LOW) */
DECL|macro|IPIC_SEFCR
mdefine_line|#define IPIC_SEFCR&t;0x58&t;/* System External Interrupt Force Register */
DECL|macro|IPIC_SERFR
mdefine_line|#define IPIC_SERFR&t;0x5C&t;/* System Error Force Register */
DECL|macro|IPIC_SCVCR
mdefine_line|#define IPIC_SCVCR&t;0x60&t;/* System Critical Interrupt Vector Register */
DECL|macro|IPIC_SMVCR
mdefine_line|#define IPIC_SMVCR&t;0x64&t;/* System Management Interrupt Vector Register */
DECL|enum|ipic_prio_grp
r_enum
id|ipic_prio_grp
(brace
DECL|enumerator|IPIC_INT_GRP_A
id|IPIC_INT_GRP_A
op_assign
id|IPIC_SIPRR_A
comma
DECL|enumerator|IPIC_INT_GRP_D
id|IPIC_INT_GRP_D
op_assign
id|IPIC_SIPRR_D
comma
DECL|enumerator|IPIC_MIX_GRP_A
id|IPIC_MIX_GRP_A
op_assign
id|IPIC_SMPRR_A
comma
DECL|enumerator|IPIC_MIX_GRP_B
id|IPIC_MIX_GRP_B
op_assign
id|IPIC_SMPRR_B
comma
)brace
suffix:semicolon
DECL|enum|ipic_mcp_irq
r_enum
id|ipic_mcp_irq
(brace
DECL|enumerator|IPIC_MCP_IRQ0
id|IPIC_MCP_IRQ0
op_assign
l_int|0
comma
DECL|enumerator|IPIC_MCP_WDT
id|IPIC_MCP_WDT
op_assign
l_int|1
comma
DECL|enumerator|IPIC_MCP_SBA
id|IPIC_MCP_SBA
op_assign
l_int|2
comma
DECL|enumerator|IPIC_MCP_PCI1
id|IPIC_MCP_PCI1
op_assign
l_int|5
comma
DECL|enumerator|IPIC_MCP_PCI2
id|IPIC_MCP_PCI2
op_assign
l_int|6
comma
DECL|enumerator|IPIC_MCP_MU
id|IPIC_MCP_MU
op_assign
l_int|7
comma
)brace
suffix:semicolon
r_extern
r_void
id|ipic_init
c_func
(paren
id|phys_addr_t
id|phys_addr
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|irq_offset
comma
r_int
r_char
op_star
id|senses
comma
r_int
r_int
id|senses_count
)paren
suffix:semicolon
r_extern
r_int
id|ipic_set_priority
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|ipic_set_highest_priority
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|ipic_set_default_priority
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipic_enable_mcp
c_func
(paren
r_enum
id|ipic_mcp_irq
id|mcp_irq
)paren
suffix:semicolon
r_extern
r_void
id|ipic_disable_mcp
c_func
(paren
r_enum
id|ipic_mcp_irq
id|mcp_irq
)paren
suffix:semicolon
r_extern
id|u32
id|ipic_get_mcp_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ipic_clear_mcp_status
c_func
(paren
id|u32
id|mask
)paren
suffix:semicolon
r_extern
r_int
id|ipic_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* __ASM_IPIC_H__ */
macro_line|#endif /* __KERNEL__ */
eof
