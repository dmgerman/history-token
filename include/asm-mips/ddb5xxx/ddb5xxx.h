multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                    Sony Software Development Center Europe (SDCE), Brussels&n; *&n; * include/asm-mips/ddb5xxx/ddb5xxx.h&n; *     Common header for all NEC DDB 5xxx boards, including 5074, 5476, 5477.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; ***********************************************************************&n; */
macro_line|#ifndef __ASM_DDB5XXX_DDB5XXX_H
DECL|macro|__ASM_DDB5XXX_DDB5XXX_H
mdefine_line|#define __ASM_DDB5XXX_DDB5XXX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ddb5xxx/debug.h&gt;
multiline_comment|/*&n; *  This file is based on the following documentation:&n; *&n; *&t;NEC Vrc 5074 System Controller Data Sheet, June 1998&n; *&n; * [jsun] It is modified so that this file only contains the macros&n; * that are true for all DDB 5xxx boards.  The modification is based on&n; *&n; *&t;uPD31577(VRC5477) VR5432-SDRAM/PCI Bridge (Luke)&n; *&t;Preliminary Specification Decoment, Rev 1.1, 27 Dec, 2000&n; *  &n; */
DECL|macro|DDB_BASE
mdefine_line|#define DDB_BASE&t;&t;0xbfa00000
DECL|macro|DDB_SIZE
mdefine_line|#define DDB_SIZE&t;&t;0x00200000&t;&t;/* 2 MB */
multiline_comment|/*&n; *  Physical Device Address Registers (PDARs)&n; */
DECL|macro|DDB_SDRAM0
mdefine_line|#define DDB_SDRAM0&t;0x0000&t;/* SDRAM Bank 0 [R/W] */
DECL|macro|DDB_SDRAM1
mdefine_line|#define DDB_SDRAM1&t;0x0008&t;/* SDRAM Bank 1 [R/W] */
DECL|macro|DDB_LDCS0
mdefine_line|#define DDB_LDCS0&t;0x0010&t;/* Device Chip-Select 0 [R/W] */
DECL|macro|DDB_LDCS1
mdefine_line|#define DDB_LDCS1&t;0x0018&t;/* Device Chip-Select 1 [R/W] */
DECL|macro|DDB_LDCS2
mdefine_line|#define DDB_LDCS2&t;0x0020&t;/* Device Chip-Select 2 [R/W] */
DECL|macro|DDB_LDCS3
mdefine_line|#define DDB_LDCS3&t;0x0028&t;/* Device Chip-Select 3 [R/W] */
DECL|macro|DDB_LDCS4
mdefine_line|#define DDB_LDCS4&t;0x0030&t;/* Device Chip-Select 4 [R/W] */
DECL|macro|DDB_LDCS5
mdefine_line|#define DDB_LDCS5&t;0x0038&t;/* Device Chip-Select 5 [R/W] */
DECL|macro|DDB_PCIW0
mdefine_line|#define DDB_PCIW0&t;0x0060&t;/* PCI Address Window 0 [R/W] */
DECL|macro|DDB_PCIW1
mdefine_line|#define DDB_PCIW1&t;0x0068&t;/* PCI Address Window 1 [R/W] */
DECL|macro|DDB_INTCS
mdefine_line|#define DDB_INTCS&t;0x0070&t;/* Controller Internal Registers and Devices */
multiline_comment|/* [R/W] */
DECL|macro|DDB_BOOTCS
mdefine_line|#define DDB_BOOTCS&t;0x0078&t;/* Boot ROM Chip-Select [R/W] */
multiline_comment|/* Vrc5477 has two more, IOPCIW0, IOPCIW1 */
multiline_comment|/*&n; *  CPU Interface Registers&n; */
DECL|macro|DDB_CPUSTAT
mdefine_line|#define DDB_CPUSTAT&t;0x0080&t;/* CPU Status [R/W] */
DECL|macro|DDB_INTCTRL
mdefine_line|#define DDB_INTCTRL&t;0x0088&t;/* Interrupt Control [R/W] */
DECL|macro|DDB_INTSTAT0
mdefine_line|#define DDB_INTSTAT0&t;0x0090&t;/* Interrupt Status 0 [R] */
DECL|macro|DDB_INTSTAT1
mdefine_line|#define DDB_INTSTAT1&t;0x0098&t;/* Interrupt Status 1 and CPU Interrupt */
multiline_comment|/* Enable [R/W] */
DECL|macro|DDB_INTCLR
mdefine_line|#define DDB_INTCLR&t;0x00A0&t;/* Interrupt Clear [R/W] */
DECL|macro|DDB_INTPPES
mdefine_line|#define DDB_INTPPES&t;0x00A8&t;/* PCI Interrupt Control [R/W] */
multiline_comment|/*&n; *  Memory-Interface Registers&n; */
DECL|macro|DDB_MEMCTRL
mdefine_line|#define DDB_MEMCTRL&t;0x00C0&t;/* Memory Control */
DECL|macro|DDB_ACSTIME
mdefine_line|#define DDB_ACSTIME&t;0x00C8&t;/* Memory Access Timing [R/W] */
DECL|macro|DDB_CHKERR
mdefine_line|#define DDB_CHKERR&t;0x00D0&t;/* Memory Check Error Status [R] */
multiline_comment|/*&n; *  PCI-Bus Registers&n; */
DECL|macro|DDB_PCICTRL
mdefine_line|#define DDB_PCICTRL&t;0x00E0&t;/* PCI Control [R/W] */
DECL|macro|DDB_PCIARB
mdefine_line|#define DDB_PCIARB&t;0x00E8&t;/* PCI Arbiter [R/W] */
DECL|macro|DDB_PCIINIT0
mdefine_line|#define DDB_PCIINIT0&t;0x00F0&t;/* PCI Master (Initiator) 0 [R/W] */
DECL|macro|DDB_PCIINIT1
mdefine_line|#define DDB_PCIINIT1&t;0x00F8&t;/* PCI Master (Initiator) 1 [R/W] */
DECL|macro|DDB_PCIERR
mdefine_line|#define DDB_PCIERR&t;0x00B8&t;/* PCI Error [R/W] */
multiline_comment|/*&n; *  Local-Bus Registers&n; */
DECL|macro|DDB_LCNFG
mdefine_line|#define DDB_LCNFG&t;0x0100&t;/* Local Bus Configuration [R/W] */
DECL|macro|DDB_LCST2
mdefine_line|#define DDB_LCST2&t;0x0110&t;/* Local Bus Chip-Select Timing 2 [R/W] */
DECL|macro|DDB_LCST3
mdefine_line|#define DDB_LCST3&t;0x0118&t;/* Local Bus Chip-Select Timing 3 [R/W] */
DECL|macro|DDB_LCST4
mdefine_line|#define DDB_LCST4&t;0x0120&t;/* Local Bus Chip-Select Timing 4 [R/W] */
DECL|macro|DDB_LCST5
mdefine_line|#define DDB_LCST5&t;0x0128&t;/* Local Bus Chip-Select Timing 5 [R/W] */
DECL|macro|DDB_LCST6
mdefine_line|#define DDB_LCST6&t;0x0130&t;/* Local Bus Chip-Select Timing 6 [R/W] */
DECL|macro|DDB_LCST7
mdefine_line|#define DDB_LCST7&t;0x0138&t;/* Local Bus Chip-Select Timing 7 [R/W] */
DECL|macro|DDB_LCST8
mdefine_line|#define DDB_LCST8&t;0x0140&t;/* Local Bus Chip-Select Timing 8 [R/W] */
DECL|macro|DDB_DCSFN
mdefine_line|#define DDB_DCSFN&t;0x0150&t;/* Device Chip-Select Muxing and Output */
multiline_comment|/* Enables [R/W] */
DECL|macro|DDB_DCSIO
mdefine_line|#define DDB_DCSIO&t;0x0158&t;/* Device Chip-Selects As I/O Bits [R/W] */
DECL|macro|DDB_BCST
mdefine_line|#define DDB_BCST&t;0x0178&t;/* Local Boot Chip-Select Timing [R/W] */
multiline_comment|/*&n; *  DMA Registers&n; */
DECL|macro|DDB_DMACTRL0
mdefine_line|#define DDB_DMACTRL0&t;0x0180&t;/* DMA Control 0 [R/W] */
DECL|macro|DDB_DMASRCA0
mdefine_line|#define DDB_DMASRCA0&t;0x0188&t;/* DMA Source Address 0 [R/W] */
DECL|macro|DDB_DMADESA0
mdefine_line|#define DDB_DMADESA0&t;0x0190&t;/* DMA Destination Address 0 [R/W] */
DECL|macro|DDB_DMACTRL1
mdefine_line|#define DDB_DMACTRL1&t;0x0198&t;/* DMA Control 1 [R/W] */
DECL|macro|DDB_DMASRCA1
mdefine_line|#define DDB_DMASRCA1&t;0x01A0&t;/* DMA Source Address 1 [R/W] */
DECL|macro|DDB_DMADESA1
mdefine_line|#define DDB_DMADESA1&t;0x01A8&t;/* DMA Destination Address 1 [R/W] */
multiline_comment|/*&n; *  Timer Registers&n; */
DECL|macro|DDB_T0CTRL
mdefine_line|#define DDB_T0CTRL&t;0x01C0&t;/* SDRAM Refresh Control [R/W] */
DECL|macro|DDB_T0CNTR
mdefine_line|#define DDB_T0CNTR&t;0x01C8&t;/* SDRAM Refresh Counter [R/W] */
DECL|macro|DDB_T1CTRL
mdefine_line|#define DDB_T1CTRL&t;0x01D0&t;/* CPU-Bus Read Time-Out Control [R/W] */
DECL|macro|DDB_T1CNTR
mdefine_line|#define DDB_T1CNTR&t;0x01D8&t;/* CPU-Bus Read Time-Out Counter [R/W] */
DECL|macro|DDB_T2CTRL
mdefine_line|#define DDB_T2CTRL&t;0x01E0&t;/* General-Purpose Timer Control [R/W] */
DECL|macro|DDB_T2CNTR
mdefine_line|#define DDB_T2CNTR&t;0x01E8&t;/* General-Purpose Timer Counter [R/W] */
DECL|macro|DDB_T3CTRL
mdefine_line|#define DDB_T3CTRL&t;0x01F0&t;/* Watchdog Timer Control [R/W] */
DECL|macro|DDB_T3CNTR
mdefine_line|#define DDB_T3CNTR&t;0x01F8&t;/* Watchdog Timer Counter [R/W] */
multiline_comment|/*&n; *  PCI Configuration Space Registers&n; */
DECL|macro|DDB_PCI_BASE
mdefine_line|#define DDB_PCI_BASE&t;0x0200
DECL|macro|DDB_VID
mdefine_line|#define DDB_VID&t;&t;0x0200&t;/* PCI Vendor ID [R] */
DECL|macro|DDB_DID
mdefine_line|#define DDB_DID&t;&t;0x0202&t;/* PCI Device ID [R] */
DECL|macro|DDB_PCICMD
mdefine_line|#define DDB_PCICMD&t;0x0204&t;/* PCI Command [R/W] */
DECL|macro|DDB_PCISTS
mdefine_line|#define DDB_PCISTS&t;0x0206&t;/* PCI Status [R/W] */
DECL|macro|DDB_REVID
mdefine_line|#define DDB_REVID&t;0x0208&t;/* PCI Revision ID [R] */
DECL|macro|DDB_CLASS
mdefine_line|#define DDB_CLASS&t;0x0209&t;/* PCI Class Code [R] */
DECL|macro|DDB_CLSIZ
mdefine_line|#define DDB_CLSIZ&t;0x020C&t;/* PCI Cache Line Size [R/W] */
DECL|macro|DDB_MLTIM
mdefine_line|#define DDB_MLTIM&t;0x020D&t;/* PCI Latency Timer [R/W] */
DECL|macro|DDB_HTYPE
mdefine_line|#define DDB_HTYPE&t;0x020E&t;/* PCI Header Type [R] */
DECL|macro|DDB_BIST
mdefine_line|#define DDB_BIST&t;0x020F&t;/* BIST [R] (unimplemented) */
DECL|macro|DDB_BARC
mdefine_line|#define DDB_BARC&t;0x0210&t;/* PCI Base Address Register Control [R/W] */
DECL|macro|DDB_BAR0
mdefine_line|#define DDB_BAR0&t;0x0218&t;/* PCI Base Address Register 0 [R/W] */
DECL|macro|DDB_BAR1
mdefine_line|#define DDB_BAR1&t;0x0220&t;/* PCI Base Address Register 1 [R/W] */
DECL|macro|DDB_CIS
mdefine_line|#define DDB_CIS&t;&t;0x0228&t;/* PCI Cardbus CIS Pointer [R] */
multiline_comment|/* (unimplemented) */
DECL|macro|DDB_SSVID
mdefine_line|#define DDB_SSVID&t;0x022C&t;/* PCI Sub-System Vendor ID [R/W] */
DECL|macro|DDB_SSID
mdefine_line|#define DDB_SSID&t;0x022E&t;/* PCI Sub-System ID [R/W] */
DECL|macro|DDB_ROM
mdefine_line|#define DDB_ROM&t;&t;0x0230&t;/* Expansion ROM Base Address [R] */
multiline_comment|/* (unimplemented) */
DECL|macro|DDB_INTLIN
mdefine_line|#define DDB_INTLIN&t;0x023C&t;/* PCI Interrupt Line [R/W] */
DECL|macro|DDB_INTPIN
mdefine_line|#define DDB_INTPIN&t;0x023D&t;/* PCI Interrupt Pin [R] */
DECL|macro|DDB_MINGNT
mdefine_line|#define DDB_MINGNT&t;0x023E&t;/* PCI Min_Gnt [R] (unimplemented) */
DECL|macro|DDB_MAXLAT
mdefine_line|#define DDB_MAXLAT&t;0x023F&t;/* PCI Max_Lat [R] (unimplemented) */
DECL|macro|DDB_BAR2
mdefine_line|#define DDB_BAR2&t;0x0240&t;/* PCI Base Address Register 2 [R/W] */
DECL|macro|DDB_BAR3
mdefine_line|#define DDB_BAR3&t;0x0248&t;/* PCI Base Address Register 3 [R/W] */
DECL|macro|DDB_BAR4
mdefine_line|#define DDB_BAR4&t;0x0250&t;/* PCI Base Address Register 4 [R/W] */
DECL|macro|DDB_BAR5
mdefine_line|#define DDB_BAR5&t;0x0258&t;/* PCI Base Address Register 5 [R/W] */
DECL|macro|DDB_BAR6
mdefine_line|#define DDB_BAR6&t;0x0260&t;/* PCI Base Address Register 6 [R/W] */
DECL|macro|DDB_BAR7
mdefine_line|#define DDB_BAR7&t;0x0268&t;/* PCI Base Address Register 7 [R/W] */
DECL|macro|DDB_BAR8
mdefine_line|#define DDB_BAR8&t;0x0270&t;/* PCI Base Address Register 8 [R/W] */
DECL|macro|DDB_BARB
mdefine_line|#define DDB_BARB&t;0x0278&t;/* PCI Base Address Register BOOT [R/W] */
multiline_comment|/*&n; *  Nile 4 Register Access&n; */
DECL|function|ddb_sync
r_static
r_inline
r_void
id|ddb_sync
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u32
op_star
id|p
op_assign
(paren
r_volatile
id|u32
op_star
)paren
l_int|0xbfc00000
suffix:semicolon
(paren
r_void
)paren
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
DECL|function|ddb_out32
r_static
r_inline
r_void
id|ddb_out32
c_func
(paren
id|u32
id|offset
comma
id|u32
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_in32
r_static
r_inline
id|u32
id|ddb_in32
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u32
id|val
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|ddb_out16
r_static
r_inline
r_void
id|ddb_out16
c_func
(paren
id|u32
id|offset
comma
id|u16
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_in16
r_static
r_inline
id|u16
id|ddb_in16
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u16
id|val
op_assign
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|ddb_out8
r_static
r_inline
r_void
id|ddb_out8
c_func
(paren
id|u32
id|offset
comma
id|u8
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ddb_in8
r_static
r_inline
id|u8
id|ddb_in8
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u8
id|val
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|DDB_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|ddb_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; *  Physical Device Address Registers&n; */
r_extern
id|u32
id|ddb_calc_pdar
c_func
(paren
id|u32
id|phys
comma
id|u32
id|size
comma
r_int
id|width
comma
r_int
id|on_memory_bus
comma
r_int
id|pci_visible
)paren
suffix:semicolon
r_extern
r_void
id|ddb_set_pdar
c_func
(paren
id|u32
id|pdar
comma
id|u32
id|phys
comma
id|u32
id|size
comma
r_int
id|width
comma
r_int
id|on_memory_bus
comma
r_int
id|pci_visible
)paren
suffix:semicolon
multiline_comment|/*&n; *  PCI Master Registers&n; */
DECL|macro|DDB_PCICMD_IACK
mdefine_line|#define DDB_PCICMD_IACK&t;&t;0&t;/* PCI Interrupt Acknowledge */
DECL|macro|DDB_PCICMD_IO
mdefine_line|#define DDB_PCICMD_IO&t;&t;1&t;/* PCI I/O Space */
DECL|macro|DDB_PCICMD_MEM
mdefine_line|#define DDB_PCICMD_MEM&t;&t;3&t;/* PCI Memory Space */
DECL|macro|DDB_PCICMD_CFG
mdefine_line|#define DDB_PCICMD_CFG&t;&t;5&t;/* PCI Configuration Space */
multiline_comment|/*&n; * additional options for pci init reg (no shifting needed)&n; */
DECL|macro|DDB_PCI_CFGTYPE1
mdefine_line|#define DDB_PCI_CFGTYPE1     0x200   /* for pci init0/1 regs */
DECL|macro|DDB_PCI_ACCESS_32
mdefine_line|#define DDB_PCI_ACCESS_32    0x10    /* for pci init0/1 regs */
r_extern
r_void
id|ddb_set_pmr
c_func
(paren
id|u32
id|pmr
comma
id|u32
id|type
comma
id|u32
id|addr
comma
id|u32
id|options
)paren
suffix:semicolon
multiline_comment|/*&n; * we need to reset pci bus when we start up and shutdown&n; */
r_extern
r_void
id|ddb_pci_reset_bus
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * include the board dependent part&n; */
macro_line|#if defined(CONFIG_DDB5074)
macro_line|#include &lt;asm/ddb5xxx/ddb5074.h&gt;
macro_line|#elif defined(CONFIG_DDB5476)
macro_line|#include &lt;asm/ddb5xxx/ddb5476.h&gt;
macro_line|#elif defined(CONFIG_DDB5477)
macro_line|#include &lt;asm/ddb5xxx/ddb5477.h&gt;
macro_line|#else
macro_line|#error &quot;Unknown DDB board!&quot;
macro_line|#endif
macro_line|#endif /* __ASM_DDB5XXX_DDB5XXX_H */
eof
