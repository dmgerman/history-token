multiline_comment|/*&n; * include/asm-ppc/ibm44x.h&n; *&n; * PPC44x definitions&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2002-2003 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM44x_H__
DECL|macro|__ASM_IBM44x_H__
mdefine_line|#define __ASM_IBM44x_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef NR_BOARD_IRQS
DECL|macro|NR_BOARD_IRQS
mdefine_line|#define NR_BOARD_IRQS 0
macro_line|#endif
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;isa_io_base
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;isa_mem_base
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;pci_dram_offset
multiline_comment|/* TLB entry offset/size used for pinning kernel lowmem */
DECL|macro|PPC44x_PIN_SHIFT
mdefine_line|#define PPC44x_PIN_SHIFT&t;28
DECL|macro|PPC44x_PIN_SIZE
mdefine_line|#define PPC44x_PIN_SIZE&t;&t;(1 &lt;&lt; PPC44x_PIN_SHIFT)
multiline_comment|/* Lowest TLB slot consumed by the default pinned TLBs */
DECL|macro|PPC44x_LOW_SLOT
mdefine_line|#define PPC44x_LOW_SLOT&t;&t;63
multiline_comment|/*&n; * Standard 4GB &quot;page&quot; definitions&n; */
DECL|macro|PPC44x_IO_PAGE
mdefine_line|#define&t;PPC44x_IO_PAGE&t;&t;0x0000000100000000ULL
DECL|macro|PPC44x_PCICFG_PAGE
mdefine_line|#define&t;PPC44x_PCICFG_PAGE&t;0x0000000200000000ULL
DECL|macro|PPC44x_PCIIO_PAGE
mdefine_line|#define&t;PPC44x_PCIIO_PAGE&t;PPC44x_PCICFG_PAGE
DECL|macro|PPC44x_PCIMEM_PAGE
mdefine_line|#define&t;PPC44x_PCIMEM_PAGE&t;0x0000000300000000ULL
multiline_comment|/*&n; * 36-bit trap ranges&n; */
DECL|macro|PPC44x_IO_LO
mdefine_line|#define PPC44x_IO_LO&t;&t;0x40000000
DECL|macro|PPC44x_IO_HI
mdefine_line|#define PPC44x_IO_HI&t;&t;0x40001000
DECL|macro|PPC44x_PCICFG_LO
mdefine_line|#define PPC44x_PCICFG_LO&t;0x0ec00000
DECL|macro|PPC44x_PCICFG_HI
mdefine_line|#define PPC44x_PCICFG_HI&t;0x0ec7ffff
DECL|macro|PPC44x_PCIMEM_LO
mdefine_line|#define PPC44x_PCIMEM_LO&t;0x80002000
DECL|macro|PPC44x_PCIMEM_HI
mdefine_line|#define PPC44x_PCIMEM_HI&t;0xffffffff
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * DCRN definitions&n; */
macro_line|#ifdef CONFIG_440GX
multiline_comment|/* CPRs */
DECL|macro|DCRN_CPR_CONFIG_ADDR
mdefine_line|#define DCRN_CPR_CONFIG_ADDR&t;0xc
DECL|macro|DCRN_CPR_CONFIG_DATA
mdefine_line|#define DCRN_CPR_CONFIG_DATA&t;0xd
DECL|macro|DCRN_CPR_CLKUPD
mdefine_line|#define DCRN_CPR_CLKUPD&t;&t;0x0020
DECL|macro|DCRN_CPR_PLLC
mdefine_line|#define DCRN_CPR_PLLC&t;&t;0x0040
DECL|macro|DCRN_CPR_PLLD
mdefine_line|#define DCRN_CPR_PLLD&t;&t;0x0060
DECL|macro|DCRN_CPR_PRIMAD
mdefine_line|#define DCRN_CPR_PRIMAD&t;&t;0x0080
DECL|macro|DCRN_CPR_PRIMBD
mdefine_line|#define DCRN_CPR_PRIMBD&t;&t;0x00a0
DECL|macro|DCRN_CPR_OPBD
mdefine_line|#define DCRN_CPR_OPBD&t;&t;0x00c0
DECL|macro|DCRN_CPR_PERD
mdefine_line|#define DCRN_CPR_PERD&t;&t;0x00e0
DECL|macro|DCRN_CPR_MALD
mdefine_line|#define DCRN_CPR_MALD&t;&t;0x0100
multiline_comment|/* CPRs read/write helper macros */
DECL|macro|CPR_READ
mdefine_line|#define CPR_READ(offset) ({&bslash;&n;&t;mtdcr(DCRN_CPR_CONFIG_ADDR, offset); &bslash;&n;&t;mfdcr(DCRN_CPR_CONFIG_DATA);})
DECL|macro|CPR_WRITE
mdefine_line|#define CPR_WRITE(offset, data) ({&bslash;&n;&t;mtdcr(DCRN_CPR_CONFIG_ADDR, offset); &bslash;&n;&t;mtdcr(DCRN_CPR_CONFIG_DATA, data);})
multiline_comment|/* SDRs */
DECL|macro|DCRN_SDR_CONFIG_ADDR
mdefine_line|#define DCRN_SDR_CONFIG_ADDR &t;0xe
DECL|macro|DCRN_SDR_CONFIG_DATA
mdefine_line|#define DCRN_SDR_CONFIG_DATA&t;0xf
DECL|macro|DCRN_SDR_PFC0
mdefine_line|#define DCRN_SDR_PFC0&t;&t;0x4100
DECL|macro|DCRN_SDR_PFC1
mdefine_line|#define DCRN_SDR_PFC1&t;&t;0x4101
DECL|macro|DCRN_SDR_PFC1_EPS
mdefine_line|#define DCRN_SDR_PFC1_EPS&t;0x1c00000
DECL|macro|DCRN_SDR_PFC1_EPS_SHIFT
mdefine_line|#define DCRN_SDR_PFC1_EPS_SHIFT&t;22
DECL|macro|DCRN_SDR_PFC1_RMII
mdefine_line|#define DCRN_SDR_PFC1_RMII&t;0x02000000
DECL|macro|DCRN_SDR_MFR
mdefine_line|#define DCRN_SDR_MFR&t;&t;0x4300
DECL|macro|DCRN_SDR_MFR_TAH0
mdefine_line|#define DCRN_SDR_MFR_TAH0 &t;0x80000000  &t;/* TAHOE0 Enable */
DECL|macro|DCRN_SDR_MFR_TAH1
mdefine_line|#define DCRN_SDR_MFR_TAH1 &t;0x40000000  &t;/* TAHOE1 Enable */
DECL|macro|DCRN_SDR_MFR_PCM
mdefine_line|#define DCRN_SDR_MFR_PCM  &t;0x10000000  &t;/* PPC440GP irq compat mode */
DECL|macro|DCRN_SDR_MFR_ECS
mdefine_line|#define DCRN_SDR_MFR_ECS  &t;0x08000000  &t;/* EMAC int clk */
DECL|macro|DCRN_SDR_MFR_T0TXFL
mdefine_line|#define DCRN_SDR_MFR_T0TXFL&t;0x00080000
DECL|macro|DCRN_SDR_MFR_T0TXFH
mdefine_line|#define DCRN_SDR_MFR_T0TXFH&t;0x00040000
DECL|macro|DCRN_SDR_MFR_T1TXFL
mdefine_line|#define DCRN_SDR_MFR_T1TXFL&t;0x00020000
DECL|macro|DCRN_SDR_MFR_T1TXFH
mdefine_line|#define DCRN_SDR_MFR_T1TXFH&t;0x00010000
DECL|macro|DCRN_SDR_MFR_E0TXFL
mdefine_line|#define DCRN_SDR_MFR_E0TXFL&t;0x00008000
DECL|macro|DCRN_SDR_MFR_E0TXFH
mdefine_line|#define DCRN_SDR_MFR_E0TXFH&t;0x00004000
DECL|macro|DCRN_SDR_MFR_E0RXFL
mdefine_line|#define DCRN_SDR_MFR_E0RXFL&t;0x00002000
DECL|macro|DCRN_SDR_MFR_E0RXFH
mdefine_line|#define DCRN_SDR_MFR_E0RXFH&t;0x00001000
DECL|macro|DCRN_SDR_MFR_E1TXFL
mdefine_line|#define DCRN_SDR_MFR_E1TXFL&t;0x00000800
DECL|macro|DCRN_SDR_MFR_E1TXFH
mdefine_line|#define DCRN_SDR_MFR_E1TXFH&t;0x00000400
DECL|macro|DCRN_SDR_MFR_E1RXFL
mdefine_line|#define DCRN_SDR_MFR_E1RXFL&t;0x00000200
DECL|macro|DCRN_SDR_MFR_E1RXFH
mdefine_line|#define DCRN_SDR_MFR_E1RXFH&t;0x00000100
DECL|macro|DCRN_SDR_MFR_E2TXFL
mdefine_line|#define DCRN_SDR_MFR_E2TXFL&t;0x00000080
DECL|macro|DCRN_SDR_MFR_E2TXFH
mdefine_line|#define DCRN_SDR_MFR_E2TXFH&t;0x00000040
DECL|macro|DCRN_SDR_MFR_E2RXFL
mdefine_line|#define DCRN_SDR_MFR_E2RXFL&t;0x00000020
DECL|macro|DCRN_SDR_MFR_E2RXFH
mdefine_line|#define DCRN_SDR_MFR_E2RXFH&t;0x00000010
DECL|macro|DCRN_SDR_MFR_E3TXFL
mdefine_line|#define DCRN_SDR_MFR_E3TXFL&t;0x00000008
DECL|macro|DCRN_SDR_MFR_E3TXFH
mdefine_line|#define DCRN_SDR_MFR_E3TXFH&t;0x00000004
DECL|macro|DCRN_SDR_MFR_E3RXFL
mdefine_line|#define DCRN_SDR_MFR_E3RXFL&t;0x00000002
DECL|macro|DCRN_SDR_MFR_E3RXFH
mdefine_line|#define DCRN_SDR_MFR_E3RXFH&t;0x00000001
DECL|macro|DCRN_SDR_UART0
mdefine_line|#define DCRN_SDR_UART0&t;&t;0x0120
DECL|macro|DCRN_SDR_UART1
mdefine_line|#define DCRN_SDR_UART1&t;&t;0x0121
multiline_comment|/* SDR read/write helper macros */
DECL|macro|SDR_READ
mdefine_line|#define SDR_READ(offset) ({&bslash;&n;&t;mtdcr(DCRN_SDR_CONFIG_ADDR, offset); &bslash;&n;&t;mfdcr(DCRN_SDR_CONFIG_DATA);})
DECL|macro|SDR_WRITE
mdefine_line|#define SDR_WRITE(offset, data) ({&bslash;&n;&t;mtdcr(DCRN_SDR_CONFIG_ADDR, offset); &bslash;&n;&t;mtdcr(DCRN_SDR_CONFIG_DATA,data);})
macro_line|#endif /* CONFIG_440GX */
multiline_comment|/* Base DCRNs */
DECL|macro|DCRN_DMA0_BASE
mdefine_line|#define DCRN_DMA0_BASE&t;&t;0x100
DECL|macro|DCRN_DMA1_BASE
mdefine_line|#define DCRN_DMA1_BASE&t;&t;0x108
DECL|macro|DCRN_DMA2_BASE
mdefine_line|#define DCRN_DMA2_BASE&t;&t;0x110
DECL|macro|DCRN_DMA3_BASE
mdefine_line|#define DCRN_DMA3_BASE&t;&t;0x118
DECL|macro|DCRN_DMASR_BASE
mdefine_line|#define DCRN_DMASR_BASE&t;&t;0x120
DECL|macro|DCRNCAP_DMA_SG
mdefine_line|#define DCRNCAP_DMA_SG&t;&t;1&t;/* have DMA scatter/gather capability */
DECL|macro|DCRN_MAL_BASE
mdefine_line|#define DCRN_MAL_BASE&t;&t;0x180
multiline_comment|/* UIC */
DECL|macro|DCRN_UIC0_BASE
mdefine_line|#define DCRN_UIC0_BASE&t;0xc0
DECL|macro|DCRN_UIC1_BASE
mdefine_line|#define DCRN_UIC1_BASE&t;0xd0
DECL|macro|DCRN_UIC2_BASE
mdefine_line|#define DCRN_UIC2_BASE&t;0x210
DECL|macro|DCRN_UICB_BASE
mdefine_line|#define DCRN_UICB_BASE&t;0x200
DECL|macro|UIC0
mdefine_line|#define UIC0&t;&t;DCRN_UIC0_BASE
DECL|macro|UIC1
mdefine_line|#define UIC1&t;&t;DCRN_UIC1_BASE
DECL|macro|UIC2
mdefine_line|#define UIC2&t;&t;DCRN_UIC2_BASE
DECL|macro|UICB
mdefine_line|#define UICB&t;&t;DCRN_UICB_BASE
DECL|macro|DCRN_UIC_SR
mdefine_line|#define DCRN_UIC_SR(base)       (base + 0x0)
DECL|macro|DCRN_UIC_ER
mdefine_line|#define DCRN_UIC_ER(base)       (base + 0x2)
DECL|macro|DCRN_UIC_CR
mdefine_line|#define DCRN_UIC_CR(base)       (base + 0x3)
DECL|macro|DCRN_UIC_PR
mdefine_line|#define DCRN_UIC_PR(base)       (base + 0x4)
DECL|macro|DCRN_UIC_TR
mdefine_line|#define DCRN_UIC_TR(base)       (base + 0x5)
DECL|macro|DCRN_UIC_MSR
mdefine_line|#define DCRN_UIC_MSR(base)      (base + 0x6)
DECL|macro|DCRN_UIC_VR
mdefine_line|#define DCRN_UIC_VR(base)       (base + 0x7)
DECL|macro|DCRN_UIC_VCR
mdefine_line|#define DCRN_UIC_VCR(base)      (base + 0x8)
DECL|macro|UIC0_UIC1NC
mdefine_line|#define UIC0_UIC1NC      &t;0x00000002
DECL|macro|UICB_UIC0NC
mdefine_line|#define UICB_UIC0NC&t;&t;0x40000000
DECL|macro|UICB_UIC1NC
mdefine_line|#define UICB_UIC1NC&t;&t;0x10000000
DECL|macro|UICB_UIC2NC
mdefine_line|#define UICB_UIC2NC&t;&t;0x04000000
multiline_comment|/* 440GP MAL DCRs */
DECL|macro|DCRN_MALCR
mdefine_line|#define DCRN_MALCR(base)&t;&t;(base + 0x0)&t;/* Configuration */
DECL|macro|DCRN_MALESR
mdefine_line|#define DCRN_MALESR(base)&t;&t;(base + 0x1)&t;/* Error Status */
DECL|macro|DCRN_MALIER
mdefine_line|#define DCRN_MALIER(base)&t;&t;(base + 0x2)&t;/* Interrupt Enable */
DECL|macro|DCRN_MALTXCASR
mdefine_line|#define DCRN_MALTXCASR(base)&t;&t;(base + 0x4)&t;/* Tx Channel Active Set */
DECL|macro|DCRN_MALTXCARR
mdefine_line|#define DCRN_MALTXCARR(base)&t;&t;(base + 0x5)&t;/* Tx Channel Active Reset */
DECL|macro|DCRN_MALTXEOBISR
mdefine_line|#define DCRN_MALTXEOBISR(base)&t;&t;(base + 0x6)&t;/* Tx End of Buffer Interrupt Status */
DECL|macro|DCRN_MALTXDEIR
mdefine_line|#define DCRN_MALTXDEIR(base)&t;&t;(base + 0x7)&t;/* Tx Descriptor Error Interrupt */
DECL|macro|DCRN_MALRXCASR
mdefine_line|#define DCRN_MALRXCASR(base)&t;&t;(base + 0x10)&t;/* Rx Channel Active Set */
DECL|macro|DCRN_MALRXCARR
mdefine_line|#define DCRN_MALRXCARR(base)&t;&t;(base + 0x11)&t;/* Rx Channel Active Reset */
DECL|macro|DCRN_MALRXEOBISR
mdefine_line|#define DCRN_MALRXEOBISR(base)&t;&t;(base + 0x12)&t;/* Rx End of Buffer Interrupt Status */
DECL|macro|DCRN_MALRXDEIR
mdefine_line|#define DCRN_MALRXDEIR(base)&t;&t;(base + 0x13)&t;/* Rx Descriptor Error Interrupt */
DECL|macro|DCRN_MALTXCTP0R
mdefine_line|#define DCRN_MALTXCTP0R(base)&t;&t;(base + 0x20)&t;/* Channel Tx 0 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP1R
mdefine_line|#define DCRN_MALTXCTP1R(base)&t;&t;(base + 0x21)&t;/* Channel Tx 1 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP2R
mdefine_line|#define DCRN_MALTXCTP2R(base)&t;&t;(base + 0x22)&t;/* Channel Tx 2 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP3R
mdefine_line|#define DCRN_MALTXCTP3R(base)&t;&t;(base + 0x23)&t;/* Channel Tx 3 Channel Table Pointer */
DECL|macro|DCRN_MALRXCTP0R
mdefine_line|#define DCRN_MALRXCTP0R(base)&t;&t;(base + 0x40)&t;/* Channel Rx 0 Channel Table Pointer */
DECL|macro|DCRN_MALRXCTP1R
mdefine_line|#define DCRN_MALRXCTP1R(base)&t;&t;(base + 0x41)&t;/* Channel Rx 1 Channel Table Pointer */
DECL|macro|DCRN_MALRCBS0
mdefine_line|#define DCRN_MALRCBS0(base)&t;&t;(base + 0x60)&t;/* Channel Rx 0 Channel Buffer Size */
DECL|macro|DCRN_MALRCBS1
mdefine_line|#define DCRN_MALRCBS1(base)&t;&t;(base + 0x61)&t;/* Channel Rx 1 Channel Buffer Size */
multiline_comment|/* Compatibility DCRN&squot;s */
DECL|macro|DCRN_MALRXCTP2R
mdefine_line|#define DCRN_MALRXCTP2R(base)&t;((base) + 0x42)&t;/* Channel Rx 2 Channel Table Pointer */
DECL|macro|DCRN_MALRXCTP3R
mdefine_line|#define DCRN_MALRXCTP3R(base)&t;((base) + 0x43)&t;/* Channel Rx 3 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP4R
mdefine_line|#define DCRN_MALTXCTP4R(base)&t;((base) + 0x24)&t;/* Channel Tx 4 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP5R
mdefine_line|#define DCRN_MALTXCTP5R(base)&t;((base) + 0x25)&t;/* Channel Tx 5 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP6R
mdefine_line|#define DCRN_MALTXCTP6R(base)&t;((base) + 0x26)&t;/* Channel Tx 6 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP7R
mdefine_line|#define DCRN_MALTXCTP7R(base)&t;((base) + 0x27)&t;/* Channel Tx 7 Channel Table Pointer */
DECL|macro|DCRN_MALRCBS2
mdefine_line|#define DCRN_MALRCBS2(base)&t;((base) + 0x62)&t;/* Channel Rx 2 Channel Buffer Size */
DECL|macro|DCRN_MALRCBS3
mdefine_line|#define DCRN_MALRCBS3(base)&t;((base) + 0x63)&t;/* Channel Rx 3 Channel Buffer Size */
DECL|macro|MALCR_MMSR
mdefine_line|#define MALCR_MMSR&t;&t;0x80000000&t;/* MAL Software reset */
DECL|macro|MALCR_PLBP_1
mdefine_line|#define MALCR_PLBP_1&t;&t;0x00400000&t;/* MAL reqest priority: */
DECL|macro|MALCR_PLBP_2
mdefine_line|#define MALCR_PLBP_2&t;&t;0x00800000&t;/* lowsest is 00 */
DECL|macro|MALCR_PLBP_3
mdefine_line|#define MALCR_PLBP_3&t;&t;0x00C00000&t;/* highest */
DECL|macro|MALCR_GA
mdefine_line|#define MALCR_GA&t;&t;0x00200000&t;/* Guarded Active Bit */
DECL|macro|MALCR_OA
mdefine_line|#define MALCR_OA&t;&t;0x00100000&t;/* Ordered Active Bit */
DECL|macro|MALCR_PLBLE
mdefine_line|#define MALCR_PLBLE&t;&t;0x00080000&t;/* PLB Lock Error Bit */
DECL|macro|MALCR_PLBLT_1
mdefine_line|#define MALCR_PLBLT_1&t;&t;0x00040000&t;/* PLB Latency Timer */
DECL|macro|MALCR_PLBLT_2
mdefine_line|#define MALCR_PLBLT_2 &t;&t;0x00020000
DECL|macro|MALCR_PLBLT_3
mdefine_line|#define MALCR_PLBLT_3&t;&t;0x00010000
DECL|macro|MALCR_PLBLT_4
mdefine_line|#define MALCR_PLBLT_4&t;&t;0x00008000
macro_line|#ifdef CONFIG_440GP
DECL|macro|MALCR_PLBLT_DEFAULT
mdefine_line|#define MALCR_PLBLT_DEFAULT&t;0x00330000&t;/* PLB Latency Timer default */
macro_line|#else
DECL|macro|MALCR_PLBLT_DEFAULT
mdefine_line|#define MALCR_PLBLT_DEFAULT&t;0x00ff0000&t;/* PLB Latency Timer default */
macro_line|#endif
DECL|macro|MALCR_PLBB
mdefine_line|#define MALCR_PLBB&t;&t;0x00004000&t;/* PLB Burst Deactivation Bit */
DECL|macro|MALCR_OPBBL
mdefine_line|#define MALCR_OPBBL&t;&t;0x00000080&t;/* OPB Lock Bit */
DECL|macro|MALCR_EOPIE
mdefine_line|#define MALCR_EOPIE&t;&t;0x00000004&t;/* End Of Packet Interrupt Enable */
DECL|macro|MALCR_LEA
mdefine_line|#define MALCR_LEA&t;&t;0x00000002&t;/* Locked Error Active */
DECL|macro|MALCR_MSD
mdefine_line|#define MALCR_MSD&t;&t;0x00000001&t;/* MAL Scroll Descriptor Bit */
multiline_comment|/* DCRN_MALESR */
DECL|macro|MALESR_EVB
mdefine_line|#define MALESR_EVB&t;&t;0x80000000&t;/* Error Valid Bit */
DECL|macro|MALESR_CIDRX
mdefine_line|#define MALESR_CIDRX&t;&t;0x40000000&t;/* Channel ID Receive */
DECL|macro|MALESR_DE
mdefine_line|#define MALESR_DE&t;&t;0x00100000&t;/* Descriptor Error */
DECL|macro|MALESR_OEN
mdefine_line|#define MALESR_OEN&t;&t;0x00080000&t;/* OPB Non-Fullword Error */
DECL|macro|MALESR_OTE
mdefine_line|#define MALESR_OTE&t;&t;0x00040000&t;/* OPB Timeout Error */
DECL|macro|MALESR_OSE
mdefine_line|#define MALESR_OSE&t;&t;0x00020000&t;/* OPB Slave Error */
DECL|macro|MALESR_PEIN
mdefine_line|#define MALESR_PEIN&t;&t;0x00010000&t;/* PLB Bus Error Indication */
DECL|macro|MALESR_DEI
mdefine_line|#define MALESR_DEI&t;&t;0x00000010&t;/* Descriptor Error Interrupt */
DECL|macro|MALESR_ONEI
mdefine_line|#define MALESR_ONEI&t;&t;0x00000008&t;/* OPB Non-Fullword Error Interrupt */
DECL|macro|MALESR_OTEI
mdefine_line|#define MALESR_OTEI&t;&t;0x00000004&t;/* OPB Timeout Error Interrupt */
DECL|macro|MALESR_OSEI
mdefine_line|#define MALESR_OSEI&t;&t;0x00000002&t;/* OPB Slace Error Interrupt */
DECL|macro|MALESR_PBEI
mdefine_line|#define MALESR_PBEI&t;&t;0x00000001&t;/* PLB Bus Error Interrupt */
multiline_comment|/* DCRN_MALIER */
DECL|macro|MALIER_DE
mdefine_line|#define MALIER_DE&t;&t;0x00000010&t;/* Descriptor Error Interrupt Enable */
DECL|macro|MALIER_NE
mdefine_line|#define MALIER_NE&t;&t;0x00000008&t;/* OPB Non-word Transfer Int Enable */
DECL|macro|MALIER_TE
mdefine_line|#define MALIER_TE&t;&t;0x00000004&t;/* OPB Time Out Error Interrupt Enable */
DECL|macro|MALIER_OPBE
mdefine_line|#define MALIER_OPBE&t;&t;0x00000002&t;/* OPB Slave Error Interrupt Enable */
DECL|macro|MALIER_PLBE
mdefine_line|#define MALIER_PLBE&t;&t;0x00000001&t;/* PLB Error Interrupt Enable */
multiline_comment|/* DCRN_MALTXEOBISR */
DECL|macro|MALOBISR_CH0
mdefine_line|#define MALOBISR_CH0&t;&t;0x80000000&t;/* EOB channel 1 bit */
DECL|macro|MALOBISR_CH2
mdefine_line|#define MALOBISR_CH2&t;&t;0x40000000&t;/* EOB channel 2 bit */
multiline_comment|/* 440GP PLB Arbiter DCRs */
DECL|macro|DCRN_PLB0_REVID
mdefine_line|#define DCRN_PLB0_REVID&t;&t;0x082&t;&t;/* PLB Arbiter Revision ID */
DECL|macro|DCRN_PLB0_ACR
mdefine_line|#define DCRN_PLB0_ACR&t;&t;0x083&t;&t;/* PLB Arbiter Control */
DECL|macro|DCRN_PLB0_BESR
mdefine_line|#define DCRN_PLB0_BESR&t;&t;0x084&t;&t;/* PLB Error Status */
DECL|macro|DCRN_PLB0_BEARL
mdefine_line|#define DCRN_PLB0_BEARL&t;&t;0x086&t;&t;/* PLB Error Address Low */
DECL|macro|DCRN_PLB0_BEAR
mdefine_line|#define DCRN_PLB0_BEAR&t;&t;DCRN_PLB0_BEARL&t;/* 40x compatibility */
DECL|macro|DCRN_PLB0_BEARH
mdefine_line|#define DCRN_PLB0_BEARH&t;&t;0x087&t;&t;/* PLB Error Address High */
multiline_comment|/* 440GP Clock, PM, chip control */
DECL|macro|DCRN_CPC0_SR
mdefine_line|#define DCRN_CPC0_SR&t;&t;0x0b0
DECL|macro|DCRN_CPC0_ER
mdefine_line|#define DCRN_CPC0_ER&t;&t;0x0b1
DECL|macro|DCRN_CPC0_FR
mdefine_line|#define DCRN_CPC0_FR&t;&t;0x0b2
DECL|macro|DCRN_CPC0_SYS0
mdefine_line|#define DCRN_CPC0_SYS0&t;&t;0x0e0
DECL|macro|DCRN_CPC0_SYS1
mdefine_line|#define DCRN_CPC0_SYS1&t;&t;0x0e1
DECL|macro|DCRN_CPC0_CUST0
mdefine_line|#define DCRN_CPC0_CUST0&t;&t;0x0e2
DECL|macro|DCRN_CPC0_CUST1
mdefine_line|#define DCRN_CPC0_CUST1&t;&t;0x0e3
DECL|macro|DCRN_CPC0_STRP0
mdefine_line|#define DCRN_CPC0_STRP0&t;&t;0x0e4
DECL|macro|DCRN_CPC0_STRP1
mdefine_line|#define DCRN_CPC0_STRP1&t;&t;0x0e5
DECL|macro|DCRN_CPC0_STRP2
mdefine_line|#define DCRN_CPC0_STRP2&t;&t;0x0e6
DECL|macro|DCRN_CPC0_STRP3
mdefine_line|#define DCRN_CPC0_STRP3&t;&t;0x0e7
DECL|macro|DCRN_CPC0_GPIO
mdefine_line|#define DCRN_CPC0_GPIO&t;&t;0x0e8
DECL|macro|DCRN_CPC0_PLB
mdefine_line|#define DCRN_CPC0_PLB&t;&t;0x0e9
DECL|macro|DCRN_CPC0_CR1
mdefine_line|#define DCRN_CPC0_CR1&t;&t;0x0ea
DECL|macro|DCRN_CPC0_CR0
mdefine_line|#define DCRN_CPC0_CR0&t;&t;0x0eb
DECL|macro|DCRN_CPC0_MIRQ0
mdefine_line|#define DCRN_CPC0_MIRQ0&t;&t;0x0ec
DECL|macro|DCRN_CPC0_MIRQ1
mdefine_line|#define DCRN_CPC0_MIRQ1&t;&t;0x0ed
DECL|macro|DCRN_CPC0_JTAGID
mdefine_line|#define DCRN_CPC0_JTAGID&t;0x0ef
multiline_comment|/* 440GP DMA controller DCRs */
DECL|macro|DCRN_DMACR0
mdefine_line|#define DCRN_DMACR0&t;(DCRN_DMA0_BASE + 0x0)&t;/* DMA Channel Control 0 */
DECL|macro|DCRN_DMACT0
mdefine_line|#define DCRN_DMACT0&t;(DCRN_DMA0_BASE + 0x1)  /* DMA Count 0 */
DECL|macro|DCRN_DMASAH0
mdefine_line|#define DCRN_DMASAH0&t;(DCRN_DMA0_BASE + 0x2)&t;/* DMA Src Addr High 0 */
DECL|macro|DCRN_DMASA0
mdefine_line|#define DCRN_DMASA0&t;(DCRN_DMA0_BASE + 0x3)&t;/* DMA Src Addr Low 0 */
DECL|macro|DCRN_DMADAH0
mdefine_line|#define DCRN_DMADAH0&t;(DCRN_DMA0_BASE + 0x4)&t;/* DMA Dest Addr High 0 */
DECL|macro|DCRN_DMADA0
mdefine_line|#define DCRN_DMADA0&t;(DCRN_DMA0_BASE + 0x5)&t;/* DMA Dest Addr Low 0 */
DECL|macro|DCRN_ASGH0
mdefine_line|#define DCRN_ASGH0&t;(DCRN_DMA0_BASE + 0x6)&t;/* DMA SG Desc Addr High 0 */
DECL|macro|DCRN_ASG0
mdefine_line|#define DCRN_ASG0&t;(DCRN_DMA0_BASE + 0x7)&t;/* DMA SG Desc Addr Low 0 */
DECL|macro|DCRN_DMACR1
mdefine_line|#define DCRN_DMACR1&t;(DCRN_DMA1_BASE + 0x0)&t;/* DMA Channel Control 1 */
DECL|macro|DCRN_DMACT1
mdefine_line|#define DCRN_DMACT1&t;(DCRN_DMA1_BASE + 0x1)  /* DMA Count 1 */
DECL|macro|DCRN_DMASAH1
mdefine_line|#define DCRN_DMASAH1&t;(DCRN_DMA1_BASE + 0x2)&t;/* DMA Src Addr High 1 */
DECL|macro|DCRN_DMASA1
mdefine_line|#define DCRN_DMASA1&t;(DCRN_DMA1_BASE + 0x3)&t;/* DMA Src Addr Low 1 */
DECL|macro|DCRN_DMADAH1
mdefine_line|#define DCRN_DMADAH1&t;(DCRN_DMA1_BASE + 0x4)&t;/* DMA Dest Addr High 1 */
DECL|macro|DCRN_DMADA1
mdefine_line|#define DCRN_DMADA1&t;(DCRN_DMA1_BASE + 0x5)&t;/* DMA Dest Addr Low 1 */
DECL|macro|DCRN_ASGH1
mdefine_line|#define DCRN_ASGH1&t;(DCRN_DMA1_BASE + 0x6)&t;/* DMA SG Desc Addr High 1 */
DECL|macro|DCRN_ASG1
mdefine_line|#define DCRN_ASG1&t;(DCRN_DMA1_BASE + 0x7)&t;/* DMA SG Desc Addr Low 1 */
DECL|macro|DCRN_DMACR2
mdefine_line|#define DCRN_DMACR2&t;(DCRN_DMA2_BASE + 0x0)&t;/* DMA Channel Control 2 */
DECL|macro|DCRN_DMACT2
mdefine_line|#define DCRN_DMACT2&t;(DCRN_DMA2_BASE + 0x1)  /* DMA Count 2 */
DECL|macro|DCRN_DMASAH2
mdefine_line|#define DCRN_DMASAH2&t;(DCRN_DMA2_BASE + 0x2)&t;/* DMA Src Addr High 2 */
DECL|macro|DCRN_DMASA2
mdefine_line|#define DCRN_DMASA2&t;(DCRN_DMA2_BASE + 0x3)&t;/* DMA Src Addr Low 2 */
DECL|macro|DCRN_DMADAH2
mdefine_line|#define DCRN_DMADAH2&t;(DCRN_DMA2_BASE + 0x4)&t;/* DMA Dest Addr High 2 */
DECL|macro|DCRN_DMADA2
mdefine_line|#define DCRN_DMADA2&t;(DCRN_DMA2_BASE + 0x5)&t;/* DMA Dest Addr Low 2 */
DECL|macro|DCRN_ASGH2
mdefine_line|#define DCRN_ASGH2&t;(DCRN_DMA2_BASE + 0x6)&t;/* DMA SG Desc Addr High 2 */
DECL|macro|DCRN_ASG2
mdefine_line|#define DCRN_ASG2&t;(DCRN_DMA2_BASE + 0x7)&t;/* DMA SG Desc Addr Low 2 */
DECL|macro|DCRN_DMACR3
mdefine_line|#define DCRN_DMACR3&t;(DCRN_DMA3_BASE + 0x0)&t;/* DMA Channel Control 3 */
DECL|macro|DCRN_DMACT3
mdefine_line|#define DCRN_DMACT3&t;(DCRN_DMA3_BASE + 0x1)  /* DMA Count 3 */
DECL|macro|DCRN_DMASAH3
mdefine_line|#define DCRN_DMASAH3&t;(DCRN_DMA3_BASE + 0x2)&t;/* DMA Src Addr High 3 */
DECL|macro|DCRN_DMASA3
mdefine_line|#define DCRN_DMASA3&t;(DCRN_DMA3_BASE + 0x3)&t;/* DMA Src Addr Low 3 */
DECL|macro|DCRN_DMADAH3
mdefine_line|#define DCRN_DMADAH3&t;(DCRN_DMA3_BASE + 0x4)&t;/* DMA Dest Addr High 3 */
DECL|macro|DCRN_DMADA3
mdefine_line|#define DCRN_DMADA3&t;(DCRN_DMA3_BASE + 0x5)&t;/* DMA Dest Addr Low 3 */
DECL|macro|DCRN_ASGH3
mdefine_line|#define DCRN_ASGH3&t;(DCRN_DMA3_BASE + 0x6)&t;/* DMA SG Desc Addr High 3 */
DECL|macro|DCRN_ASG3
mdefine_line|#define DCRN_ASG3&t;(DCRN_DMA3_BASE + 0x7)&t;/* DMA SG Desc Addr Low 3 */
DECL|macro|DCRN_DMASR
mdefine_line|#define DCRN_DMASR&t;(DCRN_DMASR_BASE + 0x0)&t;/* DMA Status Register */
DECL|macro|DCRN_ASGC
mdefine_line|#define DCRN_ASGC&t;(DCRN_DMASR_BASE + 0x3)&t;/* DMA Scatter/Gather Command */
DECL|macro|DCRN_SLP
mdefine_line|#define DCRN_SLP&t;(DCRN_DMASR_BASE + 0x5)&t;/* DMA Sleep Register */
DECL|macro|DCRN_POL
mdefine_line|#define DCRN_POL&t;(DCRN_DMASR_BASE + 0x6)&t;/* DMA Polarity Register */
multiline_comment|/* 440GP DRAM controller DCRs */
DECL|macro|DCRN_SDRAM0_CFGADDR
mdefine_line|#define DCRN_SDRAM0_CFGADDR&t;&t;0x010
DECL|macro|DCRN_SDRAM0_CFGDATA
mdefine_line|#define DCRN_SDRAM0_CFGDATA&t;&t;0x011
DECL|macro|SDRAM0_B0CR
mdefine_line|#define SDRAM0_B0CR&t;0x40
DECL|macro|SDRAM0_B1CR
mdefine_line|#define SDRAM0_B1CR&t;0x44
DECL|macro|SDRAM0_B2CR
mdefine_line|#define SDRAM0_B2CR&t;0x48
DECL|macro|SDRAM0_B3CR
mdefine_line|#define SDRAM0_B3CR&t;0x4c
DECL|macro|SDRAM_CONFIG_BANK_ENABLE
mdefine_line|#define SDRAM_CONFIG_BANK_ENABLE&t;0x00000001
DECL|macro|SDRAM_CONFIG_SIZE_MASK
mdefine_line|#define SDRAM_CONFIG_SIZE_MASK&t;&t;0x000e0000
DECL|macro|SDRAM_CONFIG_BANK_SIZE
mdefine_line|#define SDRAM_CONFIG_BANK_SIZE(reg)&t;((reg &amp; SDRAM_CONFIG_SIZE_MASK) &gt;&gt; 17)
DECL|macro|SDRAM_CONFIG_SIZE_8M
mdefine_line|#define SDRAM_CONFIG_SIZE_8M&t;&t;0x00000001
DECL|macro|SDRAM_CONFIG_SIZE_16M
mdefine_line|#define SDRAM_CONFIG_SIZE_16M&t;&t;0x00000002
DECL|macro|SDRAM_CONFIG_SIZE_32M
mdefine_line|#define SDRAM_CONFIG_SIZE_32M&t;&t;0x00000003
DECL|macro|SDRAM_CONFIG_SIZE_64M
mdefine_line|#define SDRAM_CONFIG_SIZE_64M&t;&t;0x00000004
DECL|macro|SDRAM_CONFIG_SIZE_128M
mdefine_line|#define SDRAM_CONFIG_SIZE_128M&t;&t;0x00000005
DECL|macro|SDRAM_CONFIG_SIZE_256M
mdefine_line|#define SDRAM_CONFIG_SIZE_256M&t;&t;0x00000006
DECL|macro|SDRAM_CONFIG_SIZE_512M
mdefine_line|#define SDRAM_CONFIG_SIZE_512M&t;&t;0x00000007
DECL|macro|PPC44x_MEM_SIZE_8M
mdefine_line|#define PPC44x_MEM_SIZE_8M&t;&t;0x00800000
DECL|macro|PPC44x_MEM_SIZE_16M
mdefine_line|#define PPC44x_MEM_SIZE_16M&t;&t;0x01000000
DECL|macro|PPC44x_MEM_SIZE_32M
mdefine_line|#define PPC44x_MEM_SIZE_32M&t;&t;0x02000000
DECL|macro|PPC44x_MEM_SIZE_64M
mdefine_line|#define PPC44x_MEM_SIZE_64M&t;&t;0x04000000
DECL|macro|PPC44x_MEM_SIZE_128M
mdefine_line|#define PPC44x_MEM_SIZE_128M&t;&t;0x08000000
DECL|macro|PPC44x_MEM_SIZE_256M
mdefine_line|#define PPC44x_MEM_SIZE_256M&t;&t;0x10000000
DECL|macro|PPC44x_MEM_SIZE_512M
mdefine_line|#define PPC44x_MEM_SIZE_512M&t;&t;0x20000000
macro_line|#ifdef CONFIG_440GX
multiline_comment|/* Internal SRAM Controller */
DECL|macro|DCRN_SRAM0_SB0CR
mdefine_line|#define DCRN_SRAM0_SB0CR&t;0x020
DECL|macro|DCRN_SRAM0_SB1CR
mdefine_line|#define DCRN_SRAM0_SB1CR&t;0x021
DECL|macro|DCRN_SRAM0_SB2CR
mdefine_line|#define DCRN_SRAM0_SB2CR&t;0x022
DECL|macro|DCRN_SRAM0_SB3CR
mdefine_line|#define DCRN_SRAM0_SB3CR&t;0x023
DECL|macro|SRAM_SBCR_BAS0
mdefine_line|#define  SRAM_SBCR_BAS0&t;&t;0x80000000
DECL|macro|SRAM_SBCR_BAS1
mdefine_line|#define  SRAM_SBCR_BAS1&t;&t;0x80010000
DECL|macro|SRAM_SBCR_BAS2
mdefine_line|#define  SRAM_SBCR_BAS2&t;&t;0x80020000
DECL|macro|SRAM_SBCR_BAS3
mdefine_line|#define  SRAM_SBCR_BAS3&t;&t;0x80030000
DECL|macro|SRAM_SBCR_BU_MASK
mdefine_line|#define  SRAM_SBCR_BU_MASK&t;0x00000180
DECL|macro|SRAM_SBCR_BS_64KB
mdefine_line|#define  SRAM_SBCR_BS_64KB&t;0x00000800
DECL|macro|SRAM_SBCR_BU_RO
mdefine_line|#define  SRAM_SBCR_BU_RO&t;0x00000080
DECL|macro|SRAM_SBCR_BU_RW
mdefine_line|#define  SRAM_SBCR_BU_RW&t;0x00000180
DECL|macro|DCRN_SRAM0_BEAR
mdefine_line|#define DCRN_SRAM0_BEAR&t;&t;0x024
DECL|macro|DCRN_SRAM0_BESR0
mdefine_line|#define DCRN_SRAM0_BESR0&t;0x025
DECL|macro|DCRN_SRAM0_BESR1
mdefine_line|#define DCRN_SRAM0_BESR1&t;0x026
DECL|macro|DCRN_SRAM0_PMEG
mdefine_line|#define DCRN_SRAM0_PMEG&t;&t;0x027
DECL|macro|DCRN_SRAM0_CID
mdefine_line|#define DCRN_SRAM0_CID&t;&t;0x028
DECL|macro|DCRN_SRAM0_REVID
mdefine_line|#define DCRN_SRAM0_REVID&t;0x029
DECL|macro|DCRN_SRAM0_DPC
mdefine_line|#define DCRN_SRAM0_DPC&t;&t;0x02a
DECL|macro|SRAM_DPC_ENABLE
mdefine_line|#define  SRAM_DPC_ENABLE&t;0x80000000
multiline_comment|/* L2 Cache Controller */
DECL|macro|DCRN_L2C0_CFG
mdefine_line|#define DCRN_L2C0_CFG&t;&t;0x030
DECL|macro|L2C_CFG_L2M
mdefine_line|#define  L2C_CFG_L2M&t;&t;0x80000000
DECL|macro|L2C_CFG_ICU
mdefine_line|#define  L2C_CFG_ICU&t;&t;0x40000000
DECL|macro|L2C_CFG_DCU
mdefine_line|#define  L2C_CFG_DCU&t;&t;0x20000000
DECL|macro|L2C_CFG_DCW_MASK
mdefine_line|#define  L2C_CFG_DCW_MASK&t;0x1e000000
DECL|macro|L2C_CFG_TPC
mdefine_line|#define  L2C_CFG_TPC&t;&t;0x01000000
DECL|macro|L2C_CFG_CPC
mdefine_line|#define  L2C_CFG_CPC&t;&t;0x00800000
DECL|macro|L2C_CFG_FRAN
mdefine_line|#define  L2C_CFG_FRAN&t;&t;0x00200000
DECL|macro|L2C_CFG_SS_MASK
mdefine_line|#define  L2C_CFG_SS_MASK&t;0x00180000
DECL|macro|L2C_CFG_SS_256
mdefine_line|#define  L2C_CFG_SS_256&t;&t;0x00000000
DECL|macro|L2C_CFG_CPIM
mdefine_line|#define  L2C_CFG_CPIM&t;&t;0x00040000
DECL|macro|L2C_CFG_TPIM
mdefine_line|#define  L2C_CFG_TPIM&t;&t;0x00020000
DECL|macro|L2C_CFG_LIM
mdefine_line|#define  L2C_CFG_LIM&t;&t;0x00010000
DECL|macro|L2C_CFG_PMUX_MASK
mdefine_line|#define  L2C_CFG_PMUX_MASK&t;0x00007000
DECL|macro|L2C_CFG_PMUX_SNP
mdefine_line|#define  L2C_CFG_PMUX_SNP&t;0x00000000
DECL|macro|L2C_CFG_PMUX_IF
mdefine_line|#define  L2C_CFG_PMUX_IF&t;0x00001000
DECL|macro|L2C_CFG_PMUX_DF
mdefine_line|#define  L2C_CFG_PMUX_DF&t;0x00002000
DECL|macro|L2C_CFG_PMUX_DS
mdefine_line|#define  L2C_CFG_PMUX_DS&t;0x00003000
DECL|macro|L2C_CFG_PMIM
mdefine_line|#define  L2C_CFG_PMIM&t;&t;0x00000800
DECL|macro|L2C_CFG_TPEI
mdefine_line|#define  L2C_CFG_TPEI&t;&t;0x00000400
DECL|macro|L2C_CFG_CPEI
mdefine_line|#define  L2C_CFG_CPEI&t;&t;0x00000200
DECL|macro|L2C_CFG_NAM
mdefine_line|#define  L2C_CFG_NAM&t;&t;0x00000100
DECL|macro|L2C_CFG_SMCM
mdefine_line|#define  L2C_CFG_SMCM&t;&t;0x00000080
DECL|macro|L2C_CFG_NBRM
mdefine_line|#define  L2C_CFG_NBRM&t;&t;0x00000040
DECL|macro|DCRN_L2C0_CMD
mdefine_line|#define DCRN_L2C0_CMD&t;&t;0x031
DECL|macro|L2C_CMD_CLR
mdefine_line|#define  L2C_CMD_CLR&t;&t;0x80000000
DECL|macro|L2C_CMD_DIAG
mdefine_line|#define  L2C_CMD_DIAG&t;&t;0x40000000
DECL|macro|L2C_CMD_INV
mdefine_line|#define  L2C_CMD_INV&t;&t;0x20000000
DECL|macro|L2C_CMD_CCP
mdefine_line|#define  L2C_CMD_CCP&t;&t;0x10000000
DECL|macro|L2C_CMD_CTE
mdefine_line|#define  L2C_CMD_CTE&t;&t;0x08000000
DECL|macro|L2C_CMD_STRC
mdefine_line|#define  L2C_CMD_STRC&t;&t;0x04000000
DECL|macro|L2C_CMD_STPC
mdefine_line|#define  L2C_CMD_STPC&t;&t;0x02000000
DECL|macro|L2C_CMD_RPMC
mdefine_line|#define  L2C_CMD_RPMC&t;&t;0x01000000
DECL|macro|L2C_CMD_HCC
mdefine_line|#define  L2C_CMD_HCC&t;&t;0x00800000
DECL|macro|DCRN_L2C0_ADDR
mdefine_line|#define DCRN_L2C0_ADDR&t;&t;0x032
DECL|macro|DCRN_L2C0_DATA
mdefine_line|#define DCRN_L2C0_DATA&t;&t;0x033
DECL|macro|DCRN_L2C0_SR
mdefine_line|#define DCRN_L2C0_SR&t;&t;0x034
DECL|macro|L2C_SR_CC
mdefine_line|#define  L2C_SR_CC&t;&t;0x80000000
DECL|macro|L2C_SR_CPE
mdefine_line|#define  L2C_SR_CPE&t;&t;0x40000000
DECL|macro|L2C_SR_TPE
mdefine_line|#define  L2C_SR_TPE&t;&t;0x20000000
DECL|macro|L2C_SR_LRU
mdefine_line|#define  L2C_SR_LRU&t;&t;0x10000000
DECL|macro|L2C_SR_PCS
mdefine_line|#define  L2C_SR_PCS&t;&t;0x08000000
DECL|macro|DCRN_L2C0_REVID
mdefine_line|#define DCRN_L2C0_REVID&t;&t;0x035
DECL|macro|DCRN_L2C0_SNP0
mdefine_line|#define DCRN_L2C0_SNP0&t;&t;0x036
DECL|macro|DCRN_L2C0_SNP1
mdefine_line|#define DCRN_L2C0_SNP1&t;&t;0x037
DECL|macro|L2C_SNP_BA_MASK
mdefine_line|#define  L2C_SNP_BA_MASK&t;0xffff0000
DECL|macro|L2C_SNP_SSR_MASK
mdefine_line|#define  L2C_SNP_SSR_MASK&t;0x0000f000
DECL|macro|L2C_SNP_SSR_32G
mdefine_line|#define  L2C_SNP_SSR_32G&t;0x0000f000
DECL|macro|L2C_SNP_ESR
mdefine_line|#define  L2C_SNP_ESR&t;&t;0x00000800
macro_line|#endif /* CONFIG_440GX */
multiline_comment|/*&n; * PCI-X definitions&n; */
DECL|macro|PCIX0_REG_BASE
mdefine_line|#define PCIX0_REG_BASE&t;&t;0x20ec80000ULL
DECL|macro|PCIX0_REG_SIZE
mdefine_line|#define PCIX0_REG_SIZE&t;&t;0x200
DECL|macro|PCIX0_VENDID
mdefine_line|#define PCIX0_VENDID&t;&t;0x000
DECL|macro|PCIX0_DEVID
mdefine_line|#define PCIX0_DEVID&t;&t;0x002
DECL|macro|PCIX0_COMMAND
mdefine_line|#define PCIX0_COMMAND&t;&t;0x004
DECL|macro|PCIX0_STATUS
mdefine_line|#define PCIX0_STATUS&t;&t;0x006
DECL|macro|PCIX0_REVID
mdefine_line|#define PCIX0_REVID&t;&t;0x008
DECL|macro|PCIX0_CLS
mdefine_line|#define PCIX0_CLS&t;&t;0x009
DECL|macro|PCIX0_CACHELS
mdefine_line|#define PCIX0_CACHELS&t;&t;0x00c
DECL|macro|PCIX0_LATTIM
mdefine_line|#define PCIX0_LATTIM&t;&t;0x00d
DECL|macro|PCIX0_HDTYPE
mdefine_line|#define PCIX0_HDTYPE&t;&t;0x00e
DECL|macro|PCIX0_BIST
mdefine_line|#define PCIX0_BIST&t;&t;0x00f
DECL|macro|PCIX0_BAR0L
mdefine_line|#define PCIX0_BAR0L&t;&t;0x010
DECL|macro|PCIX0_BAR0H
mdefine_line|#define PCIX0_BAR0H&t;&t;0x014
DECL|macro|PCIX0_BAR1
mdefine_line|#define PCIX0_BAR1&t;&t;0x018
DECL|macro|PCIX0_BAR2L
mdefine_line|#define PCIX0_BAR2L&t;&t;0x01c
DECL|macro|PCIX0_BAR2H
mdefine_line|#define PCIX0_BAR2H&t;&t;0x020
DECL|macro|PCIX0_BAR3
mdefine_line|#define PCIX0_BAR3&t;&t;0x024
DECL|macro|PCIX0_CISPTR
mdefine_line|#define PCIX0_CISPTR&t;&t;0x028
DECL|macro|PCIX0_SBSYSVID
mdefine_line|#define PCIX0_SBSYSVID&t;&t;0x02c
DECL|macro|PCIX0_SBSYSID
mdefine_line|#define PCIX0_SBSYSID&t;&t;0x02e
DECL|macro|PCIX0_EROMBA
mdefine_line|#define PCIX0_EROMBA&t;&t;0x030
DECL|macro|PCIX0_CAP
mdefine_line|#define PCIX0_CAP&t;&t;0x034
DECL|macro|PCIX0_RES0
mdefine_line|#define PCIX0_RES0&t;&t;0x035
DECL|macro|PCIX0_RES1
mdefine_line|#define PCIX0_RES1&t;&t;0x036
DECL|macro|PCIX0_RES2
mdefine_line|#define PCIX0_RES2&t;&t;0x038
DECL|macro|PCIX0_INTLN
mdefine_line|#define PCIX0_INTLN&t;&t;0x03c
DECL|macro|PCIX0_INTPN
mdefine_line|#define PCIX0_INTPN&t;&t;0x03d
DECL|macro|PCIX0_MINGNT
mdefine_line|#define PCIX0_MINGNT&t;&t;0x03e
DECL|macro|PCIX0_MAXLTNCY
mdefine_line|#define PCIX0_MAXLTNCY&t;&t;0x03f
DECL|macro|PCIX0_BRDGOPT1
mdefine_line|#define PCIX0_BRDGOPT1&t;&t;0x040
DECL|macro|PCIX0_BRDGOPT2
mdefine_line|#define PCIX0_BRDGOPT2&t;&t;0x044
DECL|macro|PCIX0_ERREN
mdefine_line|#define PCIX0_ERREN&t;&t;0x050
DECL|macro|PCIX0_ERRSTS
mdefine_line|#define PCIX0_ERRSTS&t;&t;0x054
DECL|macro|PCIX0_PLBBESR
mdefine_line|#define PCIX0_PLBBESR&t;&t;0x058
DECL|macro|PCIX0_PLBBEARL
mdefine_line|#define PCIX0_PLBBEARL&t;&t;0x05c
DECL|macro|PCIX0_PLBBEARH
mdefine_line|#define PCIX0_PLBBEARH&t;&t;0x060
DECL|macro|PCIX0_POM0LAL
mdefine_line|#define PCIX0_POM0LAL&t;&t;0x068
DECL|macro|PCIX0_POM0LAH
mdefine_line|#define PCIX0_POM0LAH&t;&t;0x06c
DECL|macro|PCIX0_POM0SA
mdefine_line|#define PCIX0_POM0SA&t;&t;0x070
DECL|macro|PCIX0_POM0PCIAL
mdefine_line|#define PCIX0_POM0PCIAL&t;&t;0x074
DECL|macro|PCIX0_POM0PCIAH
mdefine_line|#define PCIX0_POM0PCIAH&t;&t;0x078
DECL|macro|PCIX0_POM1LAL
mdefine_line|#define PCIX0_POM1LAL&t;&t;0x07c
DECL|macro|PCIX0_POM1LAH
mdefine_line|#define PCIX0_POM1LAH&t;&t;0x080
DECL|macro|PCIX0_POM1SA
mdefine_line|#define PCIX0_POM1SA&t;&t;0x084
DECL|macro|PCIX0_POM1PCIAL
mdefine_line|#define PCIX0_POM1PCIAL&t;&t;0x088
DECL|macro|PCIX0_POM1PCIAH
mdefine_line|#define PCIX0_POM1PCIAH&t;&t;0x08c
DECL|macro|PCIX0_POM2SA
mdefine_line|#define PCIX0_POM2SA&t;&t;0x090
DECL|macro|PCIX0_PIM0SAL
mdefine_line|#define PCIX0_PIM0SAL&t;&t;0x098
DECL|macro|PCIX0_PIM0SA
mdefine_line|#define PCIX0_PIM0SA&t;&t;PCIX0_PIM0SAL
DECL|macro|PCIX0_PIM0LAL
mdefine_line|#define PCIX0_PIM0LAL&t;&t;0x09c
DECL|macro|PCIX0_PIM0LAH
mdefine_line|#define PCIX0_PIM0LAH&t;&t;0x0a0
DECL|macro|PCIX0_PIM1SA
mdefine_line|#define PCIX0_PIM1SA&t;&t;0x0a4
DECL|macro|PCIX0_PIM1LAL
mdefine_line|#define PCIX0_PIM1LAL&t;&t;0x0a8
DECL|macro|PCIX0_PIM1LAH
mdefine_line|#define PCIX0_PIM1LAH&t;&t;0x0ac
DECL|macro|PCIX0_PIM2SAL
mdefine_line|#define PCIX0_PIM2SAL&t;&t;0x0b0
DECL|macro|PCIX0_PIM2SA
mdefine_line|#define PCIX0_PIM2SA&t;&t;PCIX0_PIM2SAL
DECL|macro|PCIX0_PIM2LAL
mdefine_line|#define PCIX0_PIM2LAL&t;&t;0x0b4
DECL|macro|PCIX0_PIM2LAH
mdefine_line|#define PCIX0_PIM2LAH&t;&t;0x0b8
DECL|macro|PCIX0_OMCAPID
mdefine_line|#define PCIX0_OMCAPID&t;&t;0x0c0
DECL|macro|PCIX0_OMNIPTR
mdefine_line|#define PCIX0_OMNIPTR&t;&t;0x0c1
DECL|macro|PCIX0_OMMC
mdefine_line|#define PCIX0_OMMC&t;&t;0x0c2
DECL|macro|PCIX0_OMMA
mdefine_line|#define PCIX0_OMMA&t;&t;0x0c4
DECL|macro|PCIX0_OMMUA
mdefine_line|#define PCIX0_OMMUA&t;&t;0x0c8
DECL|macro|PCIX0_OMMDATA
mdefine_line|#define PCIX0_OMMDATA&t;&t;0x0cc
DECL|macro|PCIX0_OMMEOI
mdefine_line|#define PCIX0_OMMEOI&t;&t;0x0ce
DECL|macro|PCIX0_PMCAPID
mdefine_line|#define PCIX0_PMCAPID&t;&t;0x0d0
DECL|macro|PCIX0_PMNIPTR
mdefine_line|#define PCIX0_PMNIPTR&t;&t;0x0d1
DECL|macro|PCIX0_PMC
mdefine_line|#define PCIX0_PMC&t;&t;0x0d2
DECL|macro|PCIX0_PMCSR
mdefine_line|#define PCIX0_PMCSR&t;&t;0x0d4
DECL|macro|PCIX0_PMCSRBSE
mdefine_line|#define PCIX0_PMCSRBSE&t;&t;0x0d6
DECL|macro|PCIX0_PMDATA
mdefine_line|#define PCIX0_PMDATA&t;&t;0x0d7
DECL|macro|PCIX0_PMSCRR
mdefine_line|#define PCIX0_PMSCRR&t;&t;0x0d8
DECL|macro|PCIX0_CAPID
mdefine_line|#define PCIX0_CAPID&t;&t;0x0dc
DECL|macro|PCIX0_NIPTR
mdefine_line|#define PCIX0_NIPTR&t;&t;0x0dd
DECL|macro|PCIX0_CMD
mdefine_line|#define PCIX0_CMD&t;&t;0x0de
DECL|macro|PCIX0_STS
mdefine_line|#define PCIX0_STS&t;&t;0x0e0
DECL|macro|PCIX0_IDR
mdefine_line|#define PCIX0_IDR&t;&t;0x0e4
DECL|macro|PCIX0_CID
mdefine_line|#define PCIX0_CID&t;&t;0x0e8
DECL|macro|PCIX0_RID
mdefine_line|#define PCIX0_RID&t;&t;0x0ec
DECL|macro|PCIX0_PIM0SAH
mdefine_line|#define PCIX0_PIM0SAH&t;&t;0x0f8
DECL|macro|PCIX0_PIM2SAH
mdefine_line|#define PCIX0_PIM2SAH&t;&t;0x0fc
DECL|macro|PCIX0_MSGIL
mdefine_line|#define PCIX0_MSGIL&t;&t;0x100
DECL|macro|PCIX0_MSGIH
mdefine_line|#define PCIX0_MSGIH&t;&t;0x104
DECL|macro|PCIX0_MSGOL
mdefine_line|#define PCIX0_MSGOL&t;&t;0x108
DECL|macro|PCIX0_MSGOH
mdefine_line|#define PCIX0_MSGOH&t;&t;0x10c
DECL|macro|PCIX0_IM
mdefine_line|#define PCIX0_IM&t;&t;0x1f8
DECL|macro|IIC_OWN
mdefine_line|#define IIC_OWN&t;&t;&t;0x55
DECL|macro|IIC_CLOCK
mdefine_line|#define IIC_CLOCK&t;&t;50
DECL|macro|NR_UICS
macro_line|#undef NR_UICS
macro_line|#ifdef CONFIG_440GX
DECL|macro|NR_UICS
mdefine_line|#define NR_UICS 3
macro_line|#else
DECL|macro|NR_UICS
mdefine_line|#define NR_UICS 2
macro_line|#endif
DECL|macro|BD_EMAC_ADDR
mdefine_line|#define BD_EMAC_ADDR(e,i) bi_enetaddr[e][i]
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_IBM44x_H__ */
macro_line|#endif /* __KERNEL__ */
eof
