multiline_comment|/*&n; * arch/ppc/kernel/mpc10x.h&n; * &n; * Common routines for the Motorola SPS MPC106/8240/107 Host bridge/Mem&n; * ctlr/EPIC/etc.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_KERNEL_MPC10X_H
DECL|macro|__PPC_KERNEL_MPC10X_H
mdefine_line|#define __PPC_KERNEL_MPC10X_H
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
multiline_comment|/*&n; * The values here don&squot;t completely map everything but should work in most&n; * cases.&n; *&n; * MAP A (PReP Map)&n; *   Processor: 0x80000000 - 0x807fffff -&gt; PCI I/O: 0x00000000 - 0x007fffff&n; *   Processor: 0xc0000000 - 0xdfffffff -&gt; PCI MEM: 0x00000000 - 0x1fffffff&n; *   PCI MEM:   0x80000000 -&gt; Processor System Memory: 0x00000000&n; *   EUMB mapped to: ioremap_base - 0x00100000 (ioremap_base - 1 MB)&n; *&n; * MAP B (CHRP Map)&n; *   Processor: 0xfe000000 - 0xfebfffff -&gt; PCI I/O: 0x00000000 - 0x00bfffff&n; *   Processor: 0x80000000 - 0xbfffffff -&gt; PCI MEM: 0x80000000 - 0xbfffffff&n; *   PCI MEM:   0x00000000 -&gt; Processor System Memory: 0x00000000&n; *   EUMB mapped to: ioremap_base - 0x00100000 (ioremap_base - 1 MB)&n; */
multiline_comment|/*&n; * Define the vendor/device IDs for the various bridges--should be added to&n; * &lt;linux/pci_ids.h&gt;&n; */
DECL|macro|MPC10X_BRIDGE_106
mdefine_line|#define&t;MPC10X_BRIDGE_106&t;((PCI_DEVICE_ID_MOTOROLA_MPC106 &lt;&lt; 16) |  &bslash;&n;&t;&t;&t;&t;  PCI_VENDOR_ID_MOTOROLA)
DECL|macro|MPC10X_BRIDGE_8240
mdefine_line|#define&t;MPC10X_BRIDGE_8240&t;((0x0003 &lt;&lt; 16) | PCI_VENDOR_ID_MOTOROLA)
DECL|macro|MPC10X_BRIDGE_107
mdefine_line|#define&t;MPC10X_BRIDGE_107&t;((0x0004 &lt;&lt; 16) | PCI_VENDOR_ID_MOTOROLA)
DECL|macro|MPC10X_BRIDGE_8245
mdefine_line|#define&t;MPC10X_BRIDGE_8245&t;((0x0006 &lt;&lt; 16) | PCI_VENDOR_ID_MOTOROLA)
multiline_comment|/* Define the type of map to use */
DECL|macro|MPC10X_MEM_MAP_A
mdefine_line|#define&t;MPC10X_MEM_MAP_A&t;&t;1
DECL|macro|MPC10X_MEM_MAP_B
mdefine_line|#define&t;MPC10X_MEM_MAP_B&t;&t;2
multiline_comment|/* Map A (PReP Map) Defines */
DECL|macro|MPC10X_MAPA_CNFG_ADDR
mdefine_line|#define&t;MPC10X_MAPA_CNFG_ADDR&t;&t;0x80000cf8
DECL|macro|MPC10X_MAPA_CNFG_DATA
mdefine_line|#define&t;MPC10X_MAPA_CNFG_DATA&t;&t;0x80000cfc
DECL|macro|MPC10X_MAPA_ISA_IO_BASE
mdefine_line|#define MPC10X_MAPA_ISA_IO_BASE&t;&t;0x80000000
DECL|macro|MPC10X_MAPA_ISA_MEM_BASE
mdefine_line|#define MPC10X_MAPA_ISA_MEM_BASE&t;0xc0000000
DECL|macro|MPC10X_MAPA_DRAM_OFFSET
mdefine_line|#define&t;MPC10X_MAPA_DRAM_OFFSET&t;&t;0x80000000
DECL|macro|MPC10X_MAPA_PCI_INTACK_ADDR
mdefine_line|#define&t;MPC10X_MAPA_PCI_INTACK_ADDR&t;0xbffffff0
DECL|macro|MPC10X_MAPA_PCI_IO_START
mdefine_line|#define&t;MPC10X_MAPA_PCI_IO_START&t;0x00000000
DECL|macro|MPC10X_MAPA_PCI_IO_END
mdefine_line|#define&t;MPC10X_MAPA_PCI_IO_END&t;       (0x00800000 - 1)
DECL|macro|MPC10X_MAPA_PCI_MEM_START
mdefine_line|#define&t;MPC10X_MAPA_PCI_MEM_START&t;0x00000000
DECL|macro|MPC10X_MAPA_PCI_MEM_END
mdefine_line|#define&t;MPC10X_MAPA_PCI_MEM_END&t;       (0x20000000 - 1)
DECL|macro|MPC10X_MAPA_PCI_MEM_OFFSET
mdefine_line|#define&t;MPC10X_MAPA_PCI_MEM_OFFSET&t;(MPC10X_MAPA_ISA_MEM_BASE -&t;&bslash;&n;&t;&t;&t;&t;&t; MPC10X_MAPA_PCI_MEM_START)
multiline_comment|/* Map B (CHRP Map) Defines */
DECL|macro|MPC10X_MAPB_CNFG_ADDR
mdefine_line|#define&t;MPC10X_MAPB_CNFG_ADDR&t;&t;0xfec00000
DECL|macro|MPC10X_MAPB_CNFG_DATA
mdefine_line|#define&t;MPC10X_MAPB_CNFG_DATA&t;&t;0xfee00000
DECL|macro|MPC10X_MAPB_ISA_IO_BASE
mdefine_line|#define MPC10X_MAPB_ISA_IO_BASE&t;&t;0xfe000000
DECL|macro|MPC10X_MAPB_ISA_MEM_BASE
mdefine_line|#define MPC10X_MAPB_ISA_MEM_BASE&t;0x80000000
DECL|macro|MPC10X_MAPB_DRAM_OFFSET
mdefine_line|#define&t;MPC10X_MAPB_DRAM_OFFSET&t;&t;0x00000000
DECL|macro|MPC10X_MAPB_PCI_INTACK_ADDR
mdefine_line|#define&t;MPC10X_MAPB_PCI_INTACK_ADDR&t;0xfef00000
DECL|macro|MPC10X_MAPB_PCI_IO_START
mdefine_line|#define&t;MPC10X_MAPB_PCI_IO_START&t;0x00000000
DECL|macro|MPC10X_MAPB_PCI_IO_END
mdefine_line|#define&t;MPC10X_MAPB_PCI_IO_END&t;       (0x00c00000 - 1)
DECL|macro|MPC10X_MAPB_PCI_MEM_START
mdefine_line|#define&t;MPC10X_MAPB_PCI_MEM_START&t;0x80000000
DECL|macro|MPC10X_MAPB_PCI_MEM_END
mdefine_line|#define&t;MPC10X_MAPB_PCI_MEM_END&t;       (0xc0000000 - 1)
DECL|macro|MPC10X_MAPB_PCI_MEM_OFFSET
mdefine_line|#define&t;MPC10X_MAPB_PCI_MEM_OFFSET&t;(MPC10X_MAPB_ISA_MEM_BASE -&t;&bslash;&n;&t;&t;&t;&t;&t; MPC10X_MAPB_PCI_MEM_START)
multiline_comment|/* Set hose members to values appropriate for the mem map used */
DECL|macro|MPC10X_SETUP_HOSE
mdefine_line|#define&t;MPC10X_SETUP_HOSE(hose, map) {&t;&t;&t;&t;&t;&bslash;&n;&t;(hose)-&gt;pci_mem_offset = MPC10X_MAP##map##_PCI_MEM_OFFSET;&t;&bslash;&n;&t;(hose)-&gt;io_space.start = MPC10X_MAP##map##_PCI_IO_START;&t;&bslash;&n;&t;(hose)-&gt;io_space.end = MPC10X_MAP##map##_PCI_IO_END;&t;&t;&bslash;&n;&t;(hose)-&gt;mem_space.start = MPC10X_MAP##map##_PCI_MEM_START;&t;&bslash;&n;&t;(hose)-&gt;mem_space.end = MPC10X_MAP##map##_PCI_MEM_END;&t;&t;&bslash;&n;&t;(hose)-&gt;io_base_virt = (void *)MPC10X_MAP##map##_ISA_IO_BASE;&t;&bslash;&n;}
multiline_comment|/* Miscellaneous Configuration register offsets */
DECL|macro|MPC10X_CFG_PIR_REG
mdefine_line|#define&t;MPC10X_CFG_PIR_REG&t;&t;0x09
DECL|macro|MPC10X_CFG_PIR_HOST_BRIDGE
mdefine_line|#define&t;MPC10X_CFG_PIR_HOST_BRIDGE&t;0x00
DECL|macro|MPC10X_CFG_PIR_AGENT
mdefine_line|#define&t;MPC10X_CFG_PIR_AGENT&t;&t;0x01
DECL|macro|MPC10X_CFG_EUMBBAR
mdefine_line|#define&t;MPC10X_CFG_EUMBBAR&t;&t;0x78
DECL|macro|MPC10X_CFG_PICR1_REG
mdefine_line|#define&t;MPC10X_CFG_PICR1_REG&t;&t;0xa8
DECL|macro|MPC10X_CFG_PICR1_ADDR_MAP_MASK
mdefine_line|#define&t;MPC10X_CFG_PICR1_ADDR_MAP_MASK&t;0x00010000
DECL|macro|MPC10X_CFG_PICR1_ADDR_MAP_A
mdefine_line|#define&t;MPC10X_CFG_PICR1_ADDR_MAP_A&t;0x00010000
DECL|macro|MPC10X_CFG_PICR1_ADDR_MAP_B
mdefine_line|#define&t;MPC10X_CFG_PICR1_ADDR_MAP_B&t;0x00000000
DECL|macro|MPC10X_CFG_PICR1_ST_GATH_EN
mdefine_line|#define&t;MPC10X_CFG_PICR1_ST_GATH_EN&t;0x00000040
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_REG
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_REG&t;0xe0
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_CFAE
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_CFAE&t;0x80&t;/* CPU_FD_ALIAS_EN */
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_PFAE
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_PFAE&t;0x40&t;/* PCI_FD_ALIAS_EN */
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_DR
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_DR&t;0x20&t;/* DLL_RESET */
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_PCICH
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_PCICH&t;0x80&t;/* PCI_COMPATIBILITY_HOLE */
DECL|macro|MPC10X_CFG_MAPB_OPTIONS_PROCCH
mdefine_line|#define&t;MPC10X_CFG_MAPB_OPTIONS_PROCCH&t;0x40&t;/* PROC_COMPATIBILITY_HOLE */
multiline_comment|/* Define offsets for the memory controller registers in the config space */
DECL|macro|MPC10X_MCTLR_MEM_START_1
mdefine_line|#define MPC10X_MCTLR_MEM_START_1&t;0x80&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_MEM_START_2
mdefine_line|#define MPC10X_MCTLR_MEM_START_2&t;0x84&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_START_1
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_START_1&t;0x88&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_START_2
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_START_2&t;0x8c&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_MEM_END_1
mdefine_line|#define MPC10X_MCTLR_MEM_END_1&t;&t;0x90&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_MEM_END_2i
mdefine_line|#define MPC10X_MCTLR_MEM_END_2i&t;&t;0x94&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_END_1
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_END_1&t;0x98&t;/* Banks 0-3 */
DECL|macro|MPC10X_MCTLR_EXT_MEM_END_2
mdefine_line|#define MPC10X_MCTLR_EXT_MEM_END_2&t;0x9c&t;/* Banks 4-7 */
DECL|macro|MPC10X_MCTLR_MEM_BANK_ENABLES
mdefine_line|#define MPC10X_MCTLR_MEM_BANK_ENABLES&t;0xa0
multiline_comment|/* Define some offset in the EUMB */
DECL|macro|MPC10X_EUMB_SIZE
mdefine_line|#define&t;MPC10X_EUMB_SIZE&t;&t;0x00100000 /* Total EUMB size (1MB) */
DECL|macro|MPC10X_EUMB_MU_OFFSET
mdefine_line|#define MPC10X_EUMB_MU_OFFSET&t;&t;0x00000000 /* Msg Unit reg offset */
DECL|macro|MPC10X_EUMB_MU_SIZE
mdefine_line|#define MPC10X_EUMB_MU_SIZE&t;&t;0x00001000 /* Msg Unit reg size */
DECL|macro|MPC10X_EUMB_DMA_OFFSET
mdefine_line|#define MPC10X_EUMB_DMA_OFFSET&t;&t;0x00001000 /* DMA Unit reg offset */
DECL|macro|MPC10X_EUMB_DMA_SIZE
mdefine_line|#define MPC10X_EUMB_DMA_SIZE&t;&t;0x00001000 /* DMA Unit reg size  */
DECL|macro|MPC10X_EUMB_ATU_OFFSET
mdefine_line|#define MPC10X_EUMB_ATU_OFFSET&t;&t;0x00002000 /* Addr xlate reg offset */
DECL|macro|MPC10X_EUMB_ATU_SIZE
mdefine_line|#define MPC10X_EUMB_ATU_SIZE&t;&t;0x00001000 /* Addr xlate reg size  */
DECL|macro|MPC10X_EUMB_I2C_OFFSET
mdefine_line|#define MPC10X_EUMB_I2C_OFFSET&t;&t;0x00003000 /* I2C Unit reg offset */
DECL|macro|MPC10X_EUMB_I2C_SIZE
mdefine_line|#define MPC10X_EUMB_I2C_SIZE&t;&t;0x00001000 /* I2C Unit reg size  */
DECL|macro|MPC10X_EUMB_DUART_OFFSET
mdefine_line|#define MPC10X_EUMB_DUART_OFFSET&t;0x00004000 /* DUART Unit reg offset (8245) */
DECL|macro|MPC10X_EUMB_DUART_SIZE
mdefine_line|#define MPC10X_EUMB_DUART_SIZE&t;&t;0x00001000 /* DUART Unit reg size (8245) */
DECL|macro|MPC10X_EUMB_EPIC_OFFSET
mdefine_line|#define&t;MPC10X_EUMB_EPIC_OFFSET&t;&t;0x00040000 /* EPIC offset in EUMB */
DECL|macro|MPC10X_EUMB_EPIC_SIZE
mdefine_line|#define&t;MPC10X_EUMB_EPIC_SIZE&t;&t;0x00030000 /* EPIC size */
DECL|macro|MPC10X_EUMB_PM_OFFSET
mdefine_line|#define MPC10X_EUMB_PM_OFFSET&t;&t;0x000fe000 /* Performance Monitor reg offset (8245) */
DECL|macro|MPC10X_EUMB_PM_SIZE
mdefine_line|#define MPC10X_EUMB_PM_SIZE&t;&t;0x00001000 /* Performance Monitor reg size (8245) */
DECL|macro|MPC10X_EUMB_WP_OFFSET
mdefine_line|#define MPC10X_EUMB_WP_OFFSET&t;&t;0x000ff000 /* Data path diagnostic, watchpoint reg offset */
DECL|macro|MPC10X_EUMB_WP_SIZE
mdefine_line|#define MPC10X_EUMB_WP_SIZE&t;&t;0x00001000 /* Data path diagnostic, watchpoint reg size */
multiline_comment|/*&n; * Define some recommended places to put the EUMB regs.&n; * For both maps, recommend putting the EUMB from 0xeff00000 to 0xefffffff.&n; */
r_extern
r_int
r_int
id|ioremap_base
suffix:semicolon
DECL|macro|MPC10X_MAPA_EUMB_BASE
mdefine_line|#define&t;MPC10X_MAPA_EUMB_BASE&t;&t;(ioremap_base - MPC10X_EUMB_SIZE)
DECL|macro|MPC10X_MAPB_EUMB_BASE
mdefine_line|#define&t;MPC10X_MAPB_EUMB_BASE&t;&t;MPC10X_MAPA_EUMB_BASE
r_int
id|mpc10x_bridge_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|current_map
comma
id|uint
id|new_map
comma
id|uint
id|phys_eumb_base
)paren
suffix:semicolon
r_int
r_int
id|mpc10x_get_mem_size
c_func
(paren
id|uint
id|mem_map
)paren
suffix:semicolon
r_int
id|mpc10x_enable_store_gathering
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
suffix:semicolon
macro_line|#endif&t;/* __PPC_KERNEL_MPC10X_H */
eof
