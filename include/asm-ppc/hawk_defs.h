multiline_comment|/*&n; * include/asm-ppc/hawk_defs.h&n; *&n; * Definitions for Motorola MCG Falcon/Raven &amp; HAWK North Bridge &amp; Memory ctlr.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Modified by Randy Vinson (rvinson@mvista.com)&n; *&n; * 2001-2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_HAWK_DEFS_H
DECL|macro|__ASMPPC_HAWK_DEFS_H
mdefine_line|#define __ASMPPC_HAWK_DEFS_H
macro_line|#include &lt;asm/pci-bridge.h&gt;
multiline_comment|/*&n; * The Falcon/Raven and HAWK have 4 sets of registers:&n; *   1) PPC Registers which define the mappings from PPC bus to PCI bus,&n; *      etc.&n; *   2) PCI Registers which define the mappings from PCI bus to PPC bus and the&n; *      MPIC base address.&n; *   3) MPIC registers&n; *   4) System Memory Controller (SMC) registers.&n; */
DECL|macro|HAWK_PCI_CONFIG_ADDR_OFF
mdefine_line|#define HAWK_PCI_CONFIG_ADDR_OFF&t;0x00000cf8
DECL|macro|HAWK_PCI_CONFIG_DATA_OFF
mdefine_line|#define HAWK_PCI_CONFIG_DATA_OFF&t;0x00000cfc
DECL|macro|HAWK_MPIC_SIZE
mdefine_line|#define HAWK_MPIC_SIZE&t;&t;&t;0x00040000U
DECL|macro|HAWK_SMC_SIZE
mdefine_line|#define HAWK_SMC_SIZE&t;&t;&t;0x00001000U
multiline_comment|/*&n; * Define PPC register offsets.&n; */
DECL|macro|HAWK_PPC_XSADD0_OFF
mdefine_line|#define HAWK_PPC_XSADD0_OFF&t;&t;&t;0x40
DECL|macro|HAWK_PPC_XSOFF0_OFF
mdefine_line|#define HAWK_PPC_XSOFF0_OFF&t;&t;&t;0x44
DECL|macro|HAWK_PPC_XSADD1_OFF
mdefine_line|#define HAWK_PPC_XSADD1_OFF&t;&t;&t;0x48
DECL|macro|HAWK_PPC_XSOFF1_OFF
mdefine_line|#define HAWK_PPC_XSOFF1_OFF&t;&t;&t;0x4c
DECL|macro|HAWK_PPC_XSADD2_OFF
mdefine_line|#define HAWK_PPC_XSADD2_OFF&t;&t;&t;0x50
DECL|macro|HAWK_PPC_XSOFF2_OFF
mdefine_line|#define HAWK_PPC_XSOFF2_OFF&t;&t;&t;0x54
DECL|macro|HAWK_PPC_XSADD3_OFF
mdefine_line|#define HAWK_PPC_XSADD3_OFF&t;&t;&t;0x58
DECL|macro|HAWK_PPC_XSOFF3_OFF
mdefine_line|#define HAWK_PPC_XSOFF3_OFF&t;&t;&t;0x5c
multiline_comment|/*&n; * Define PCI register offsets.&n; */
DECL|macro|HAWK_PCI_PSADD0_OFF
mdefine_line|#define HAWK_PCI_PSADD0_OFF&t;&t;&t;0x80
DECL|macro|HAWK_PCI_PSOFF0_OFF
mdefine_line|#define HAWK_PCI_PSOFF0_OFF&t;&t;&t;0x84
DECL|macro|HAWK_PCI_PSADD1_OFF
mdefine_line|#define HAWK_PCI_PSADD1_OFF&t;&t;&t;0x88
DECL|macro|HAWK_PCI_PSOFF1_OFF
mdefine_line|#define HAWK_PCI_PSOFF1_OFF&t;&t;&t;0x8c
DECL|macro|HAWK_PCI_PSADD2_OFF
mdefine_line|#define HAWK_PCI_PSADD2_OFF&t;&t;&t;0x90
DECL|macro|HAWK_PCI_PSOFF2_OFF
mdefine_line|#define HAWK_PCI_PSOFF2_OFF&t;&t;&t;0x94
DECL|macro|HAWK_PCI_PSADD3_OFF
mdefine_line|#define HAWK_PCI_PSADD3_OFF&t;&t;&t;0x98
DECL|macro|HAWK_PCI_PSOFF3_OFF
mdefine_line|#define HAWK_PCI_PSOFF3_OFF&t;&t;&t;0x9c
multiline_comment|/*&n; * Define the System Memory Controller (SMC) register offsets.&n; */
DECL|macro|HAWK_SMC_RAM_A_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_A_SIZE_REG_OFF&t;&t;0x10
DECL|macro|HAWK_SMC_RAM_B_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_B_SIZE_REG_OFF&t;&t;0x11
DECL|macro|HAWK_SMC_RAM_C_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_C_SIZE_REG_OFF&t;&t;0x12
DECL|macro|HAWK_SMC_RAM_D_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_D_SIZE_REG_OFF&t;&t;0x13
DECL|macro|HAWK_SMC_RAM_E_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_E_SIZE_REG_OFF&t;&t;0xc0&t;/* HAWK Only */
DECL|macro|HAWK_SMC_RAM_F_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_F_SIZE_REG_OFF&t;&t;0xc1&t;/* HAWK Only */
DECL|macro|HAWK_SMC_RAM_G_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_G_SIZE_REG_OFF&t;&t;0xc2&t;/* HAWK Only */
DECL|macro|HAWK_SMC_RAM_H_SIZE_REG_OFF
mdefine_line|#define HAWK_SMC_RAM_H_SIZE_REG_OFF&t;&t;0xc3&t;/* HAWK Only */
DECL|macro|FALCON_SMC_REG_COUNT
mdefine_line|#define FALCON_SMC_REG_COUNT&t;&t;&t;4
DECL|macro|HAWK_SMC_REG_COUNT
mdefine_line|#define HAWK_SMC_REG_COUNT&t;&t;&t;8
macro_line|#endif&t;&t;&t;&t;/* __ASMPPC_HAWK_DEFS_H */
eof
