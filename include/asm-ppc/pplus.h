multiline_comment|/*&n; * arch/ppc/kernel/pplus.h&n; * &n; * Definitions for Motorola MCG Falcon/Raven &amp; HAWK North Bridge &amp; Memory ctlr.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_PPLUS_H
DECL|macro|__ASMPPC_PPLUS_H
mdefine_line|#define __ASMPPC_PPLUS_H
macro_line|#include &lt;asm/pci-bridge.h&gt;
multiline_comment|/*&n; * The Falcon/Raven and HAWK have 4 sets of registers:&n; *   1) PPC Registers which define the mappings from PPC bus to PCI bus,&n; *      etc.&n; *   2) PCI Registers which define the mappings from PCI bus to PPC bus and the&n; *      MPIC base address.&n; *   3) MPIC registers&n; *   4) System Memory Controller (SMC) registers.&n; */
DECL|macro|PPLUS_RAVEN_VEND_DEV_ID
mdefine_line|#define&t;PPLUS_RAVEN_VEND_DEV_ID&t;&t;0x48011057
DECL|macro|PPLUS_HAWK_VEND_DEV_ID
mdefine_line|#define&t;PPLUS_HAWK_VEND_DEV_ID&t;&t;0x48031057
DECL|macro|PPLUS_PCI_CONFIG_ADDR_OFF
mdefine_line|#define&t;PPLUS_PCI_CONFIG_ADDR_OFF&t;0x00000cf8
DECL|macro|PPLUS_PCI_CONFIG_DATA_OFF
mdefine_line|#define&t;PPLUS_PCI_CONFIG_DATA_OFF&t;0x00000cfc
DECL|macro|PPLUS_MPIC_SIZE
mdefine_line|#define PPLUS_MPIC_SIZE&t;&t;&t;0x00040000U
DECL|macro|PPLUS_SMC_SIZE
mdefine_line|#define PPLUS_SMC_SIZE&t;&t;&t;0x00001000U
multiline_comment|/*&n; * Define PPC register offsets.&n; */
DECL|macro|PPLUS_PPC_XSADD0_OFF
mdefine_line|#define PPLUS_PPC_XSADD0_OFF&t;&t;&t;0x40
DECL|macro|PPLUS_PPC_XSOFF0_OFF
mdefine_line|#define PPLUS_PPC_XSOFF0_OFF&t;&t;&t;0x44
DECL|macro|PPLUS_PPC_XSADD1_OFF
mdefine_line|#define PPLUS_PPC_XSADD1_OFF&t;&t;&t;0x48
DECL|macro|PPLUS_PPC_XSOFF1_OFF
mdefine_line|#define PPLUS_PPC_XSOFF1_OFF&t;&t;&t;0x4c
DECL|macro|PPLUS_PPC_XSADD2_OFF
mdefine_line|#define PPLUS_PPC_XSADD2_OFF&t;&t;&t;0x50
DECL|macro|PPLUS_PPC_XSOFF2_OFF
mdefine_line|#define PPLUS_PPC_XSOFF2_OFF&t;&t;&t;0x54
DECL|macro|PPLUS_PPC_XSADD3_OFF
mdefine_line|#define PPLUS_PPC_XSADD3_OFF&t;&t;&t;0x58
DECL|macro|PPLUS_PPC_XSOFF3_OFF
mdefine_line|#define PPLUS_PPC_XSOFF3_OFF&t;&t;&t;0x5c
multiline_comment|/*&n; * Define PCI register offsets.&n; */
DECL|macro|PPLUS_PCI_PSADD0_OFF
mdefine_line|#define PPLUS_PCI_PSADD0_OFF&t;&t;&t;0x80
DECL|macro|PPLUS_PCI_PSOFF0_OFF
mdefine_line|#define PPLUS_PCI_PSOFF0_OFF&t;&t;&t;0x84
DECL|macro|PPLUS_PCI_PSADD1_OFF
mdefine_line|#define PPLUS_PCI_PSADD1_OFF&t;&t;&t;0x88
DECL|macro|PPLUS_PCI_PSOFF1_OFF
mdefine_line|#define PPLUS_PCI_PSOFF1_OFF&t;&t;&t;0x8c
DECL|macro|PPLUS_PCI_PSADD2_OFF
mdefine_line|#define PPLUS_PCI_PSADD2_OFF&t;&t;&t;0x90
DECL|macro|PPLUS_PCI_PSOFF2_OFF
mdefine_line|#define PPLUS_PCI_PSOFF2_OFF&t;&t;&t;0x94
DECL|macro|PPLUS_PCI_PSADD3_OFF
mdefine_line|#define PPLUS_PCI_PSADD3_OFF&t;&t;&t;0x98
DECL|macro|PPLUS_PCI_PSOFF3_OFF
mdefine_line|#define PPLUS_PCI_PSOFF3_OFF&t;&t;&t;0x9c
multiline_comment|/*&n; * Define the System Memory Controller (SMC) register offsets.&n; */
DECL|macro|PPLUS_SMC_RAM_A_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_A_SIZE_REG_OFF&t;&t;0x10
DECL|macro|PPLUS_SMC_RAM_B_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_B_SIZE_REG_OFF&t;&t;0x11
DECL|macro|PPLUS_SMC_RAM_C_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_C_SIZE_REG_OFF&t;&t;0x12
DECL|macro|PPLUS_SMC_RAM_D_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_D_SIZE_REG_OFF&t;&t;0x13
DECL|macro|PPLUS_SMC_RAM_E_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_E_SIZE_REG_OFF&t;&t;0xc0&t;/* HAWK Only */
DECL|macro|PPLUS_SMC_RAM_F_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_F_SIZE_REG_OFF&t;&t;0xc1&t;/* HAWK Only */
DECL|macro|PPLUS_SMC_RAM_G_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_G_SIZE_REG_OFF&t;&t;0xc2&t;/* HAWK Only */
DECL|macro|PPLUS_SMC_RAM_H_SIZE_REG_OFF
mdefine_line|#define PPLUS_SMC_RAM_H_SIZE_REG_OFF&t;&t;0xc3&t;/* HAWK Only */
DECL|macro|PPLUS_FALCON_SMC_REG_COUNT
mdefine_line|#define&t;PPLUS_FALCON_SMC_REG_COUNT&t;&t;4
DECL|macro|PPLUS_HAWK_SMC_REG_COUNT
mdefine_line|#define&t;PPLUS_HAWK_SMC_REG_COUNT&t;&t;8
r_int
id|pplus_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|ppc_reg_base
comma
id|ulong
id|processor_pci_mem_start
comma
id|ulong
id|processor_pci_mem_end
comma
id|ulong
id|processor_pci_io_start
comma
id|ulong
id|processor_pci_io_end
comma
id|ulong
id|processor_mpic_base
)paren
suffix:semicolon
r_int
r_int
id|pplus_get_mem_size
c_func
(paren
id|uint
id|smc_base
)paren
suffix:semicolon
r_int
id|pplus_mpic_init
c_func
(paren
r_int
r_int
id|pci_mem_offset
)paren
suffix:semicolon
macro_line|#endif /* __ASMPPC_PPLUS_H */
eof
