multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_PCI_DEFS_H
DECL|macro|_ASM_SN_PCI_PCI_DEFS_H
mdefine_line|#define _ASM_SN_PCI_PCI_DEFS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* defines for the PCI bus architecture */
multiline_comment|/* Bit layout of address fields for Type-1&n; * Configuration Space cycles.&n; */
DECL|macro|PCI_TYPE0_SLOT_MASK
mdefine_line|#define&t;PCI_TYPE0_SLOT_MASK&t;0xFFFFF800
DECL|macro|PCI_TYPE0_FUNC_MASK
mdefine_line|#define&t;PCI_TYPE0_FUNC_MASK&t;0x00000700
DECL|macro|PCI_TYPE0_REG_MASK
mdefine_line|#define&t;PCI_TYPE0_REG_MASK&t;0x000000FF
DECL|macro|PCI_TYPE0_SLOT_SHFT
mdefine_line|#define&t;PCI_TYPE0_SLOT_SHFT&t;11
DECL|macro|PCI_TYPE0_FUNC_SHFT
mdefine_line|#define&t;PCI_TYPE0_FUNC_SHFT&t;8
DECL|macro|PCI_TYPE0_REG_SHFT
mdefine_line|#define&t;PCI_TYPE0_REG_SHFT&t;0
DECL|macro|PCI_TYPE0_FUNC
mdefine_line|#define&t;PCI_TYPE0_FUNC(a)&t;(((a) &amp; PCI_TYPE0_FUNC_MASK) &gt;&gt; PCI_TYPE0_FUNC_SHFT)
DECL|macro|PCI_TYPE0_REG
mdefine_line|#define&t;PCI_TYPE0_REG(a)&t;(((a) &amp; PCI_TYPE0_REG_MASK) &gt;&gt; PCI_TYPE0_REG_SHFT)
DECL|macro|PCI_TYPE0
mdefine_line|#define&t;PCI_TYPE0(s,f,r)&t;((((1&lt;&lt;(s)) &lt;&lt; PCI_TYPE0_SLOT_SHFT) &amp; PCI_TYPE0_SLOT_MASK) |&bslash;&n;&t;&t;&t;&t; (((f) &lt;&lt; PCI_TYPE0_FUNC_SHFT) &amp; PCI_TYPE0_FUNC_MASK) |&bslash;&n;&t;&t;&t;&t; (((r) &lt;&lt; PCI_TYPE0_REG_SHFT) &amp; PCI_TYPE0_REG_MASK))
multiline_comment|/* Bit layout of address fields for Type-1&n; * Configuration Space cycles.&n; * NOTE: I&squot;m including the byte offset within&n; * the 32-bit word as part of the register&n; * number as an extension of the layout in&n; * the PCI spec.&n; */
DECL|macro|PCI_TYPE1_BUS_MASK
mdefine_line|#define&t;PCI_TYPE1_BUS_MASK&t;0x00FF0000
DECL|macro|PCI_TYPE1_SLOT_MASK
mdefine_line|#define&t;PCI_TYPE1_SLOT_MASK&t;0x0000F800
DECL|macro|PCI_TYPE1_FUNC_MASK
mdefine_line|#define&t;PCI_TYPE1_FUNC_MASK&t;0x00000700
DECL|macro|PCI_TYPE1_REG_MASK
mdefine_line|#define&t;PCI_TYPE1_REG_MASK&t;0x000000FF
DECL|macro|PCI_TYPE1_BUS_SHFT
mdefine_line|#define&t;PCI_TYPE1_BUS_SHFT&t;16
DECL|macro|PCI_TYPE1_SLOT_SHFT
mdefine_line|#define&t;PCI_TYPE1_SLOT_SHFT&t;11
DECL|macro|PCI_TYPE1_FUNC_SHFT
mdefine_line|#define&t;PCI_TYPE1_FUNC_SHFT&t;8
DECL|macro|PCI_TYPE1_REG_SHFT
mdefine_line|#define&t;PCI_TYPE1_REG_SHFT&t;0
DECL|macro|PCI_TYPE1_BUS
mdefine_line|#define&t;PCI_TYPE1_BUS(a)&t;(((a) &amp; PCI_TYPE1_BUS_MASK) &gt;&gt; PCI_TYPE1_BUS_SHFT)
DECL|macro|PCI_TYPE1_SLOT
mdefine_line|#define&t;PCI_TYPE1_SLOT(a)&t;(((a) &amp; PCI_TYPE1_SLOT_MASK) &gt;&gt; PCI_TYPE1_SLOT_SHFT)
DECL|macro|PCI_TYPE1_FUNC
mdefine_line|#define&t;PCI_TYPE1_FUNC(a)&t;(((a) &amp; PCI_TYPE1_FUNC_MASK) &gt;&gt; PCI_TYPE1_FUNC_SHFT)
DECL|macro|PCI_TYPE1_REG
mdefine_line|#define&t;PCI_TYPE1_REG(a)&t;(((a) &amp; PCI_TYPE1_REG_MASK) &gt;&gt; PCI_TYPE1_REG_SHFT)
DECL|macro|PCI_TYPE1
mdefine_line|#define&t;PCI_TYPE1(b,s,f,r)&t;((((b) &lt;&lt; PCI_TYPE1_BUS_SHFT) &amp; PCI_TYPE1_BUS_MASK) |&bslash;&n;&t;&t;&t;&t; (((s) &lt;&lt; PCI_TYPE1_SLOT_SHFT) &amp; PCI_TYPE1_SLOT_MASK) |&bslash;&n;&t;&t;&t;&t; (((f) &lt;&lt; PCI_TYPE1_FUNC_SHFT) &amp; PCI_TYPE1_FUNC_MASK) |&bslash;&n;&t;&t;&t;&t; (((r) &lt;&lt; PCI_TYPE1_REG_SHFT) &amp; PCI_TYPE1_REG_MASK))
multiline_comment|/* Byte offsets of registers in CFG space&n; */
DECL|macro|PCI_CFG_VENDOR_ID
mdefine_line|#define&t;PCI_CFG_VENDOR_ID&t;0x00&t;&t;/* Vendor ID (2 bytes) */
DECL|macro|PCI_CFG_DEVICE_ID
mdefine_line|#define&t;PCI_CFG_DEVICE_ID&t;0x02&t;&t;/* Device ID (2 bytes) */
DECL|macro|PCI_CFG_COMMAND
mdefine_line|#define&t;PCI_CFG_COMMAND&t;&t;0x04&t;&t;/* Command (2 bytes) */
DECL|macro|PCI_CFG_STATUS
mdefine_line|#define&t;PCI_CFG_STATUS&t;&t;0x06&t;&t;/* Status (2 bytes) */
multiline_comment|/* NOTE: if you are using a C &quot;switch&quot; statement to&n; * differentiate between the Config space registers, be&n; * aware that PCI_CFG_CLASS_CODE and PCI_CFG_PROG_IF&n; * are the same offset.&n; */
DECL|macro|PCI_CFG_REV_ID
mdefine_line|#define&t;PCI_CFG_REV_ID&t;&t;0x08&t;&t;/* Revision Id (1 byte) */
DECL|macro|PCI_CFG_CLASS_CODE
mdefine_line|#define&t;PCI_CFG_CLASS_CODE&t;0x09&t;&t;/* Class Code (3 bytes) */
DECL|macro|PCI_CFG_PROG_IF
mdefine_line|#define&t;PCI_CFG_PROG_IF&t;&t;0x09&t;&t;/* Prog Interface (1 byte) */
DECL|macro|PCI_CFG_SUB_CLASS
mdefine_line|#define&t;PCI_CFG_SUB_CLASS&t;0x0A&t;&t;/* Sub Class (1 byte) */
DECL|macro|PCI_CFG_BASE_CLASS
mdefine_line|#define&t;PCI_CFG_BASE_CLASS&t;0x0B&t;&t;/* Base Class (1 byte) */
DECL|macro|PCI_CFG_CACHE_LINE
mdefine_line|#define&t;PCI_CFG_CACHE_LINE&t;0x0C&t;&t;/* Cache line size (1 byte) */
DECL|macro|PCI_CFG_LATENCY_TIMER
mdefine_line|#define&t;PCI_CFG_LATENCY_TIMER&t;0x0D&t;&t;/* Latency Timer (1 byte) */
DECL|macro|PCI_CFG_HEADER_TYPE
mdefine_line|#define&t;PCI_CFG_HEADER_TYPE&t;0x0E&t;&t;/* Header Type (1 byte) */
DECL|macro|PCI_CFG_BIST
mdefine_line|#define&t;PCI_CFG_BIST&t;&t;0x0F&t;&t;/* Built In Self Test */
DECL|macro|PCI_CFG_BASE_ADDR_0
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_0&t;0x10&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_1
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_1&t;0x14&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_2
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_2&t;0x18&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_3
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_3&t;0x1C&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_4
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_4&t;0x20&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_5
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_5&t;0x24&t;&t;/* Base Address (4 bytes) */
DECL|macro|PCI_CFG_BASE_ADDR_OFF
mdefine_line|#define&t;PCI_CFG_BASE_ADDR_OFF&t;0x04&t;&t;/* Base Address Offset (1..5)*/
DECL|macro|PCI_CFG_BASE_ADDR
mdefine_line|#define&t;PCI_CFG_BASE_ADDR(n)&t;(PCI_CFG_BASE_ADDR_0 + (n)*PCI_CFG_BASE_ADDR_OFF)
DECL|macro|PCI_CFG_BASE_ADDRS
mdefine_line|#define&t;PCI_CFG_BASE_ADDRS&t;6&t;&t;/* up to this many BASE regs */
DECL|macro|PCI_CFG_CARDBUS_CIS
mdefine_line|#define&t;PCI_CFG_CARDBUS_CIS&t;0x28&t;&t;/* Cardbus CIS Pointer (4B) */
DECL|macro|PCI_CFG_SUBSYS_VEND_ID
mdefine_line|#define&t;PCI_CFG_SUBSYS_VEND_ID&t;0x2C&t;&t;/* Subsystem Vendor ID (2B) */
DECL|macro|PCI_CFG_SUBSYS_ID
mdefine_line|#define&t;PCI_CFG_SUBSYS_ID&t;0x2E&t;&t;/* Subsystem ID */
DECL|macro|PCI_EXPANSION_ROM
mdefine_line|#define&t;PCI_EXPANSION_ROM&t;0x30&t;&t;/* Expansion Rom Base (4B) */
DECL|macro|PCI_CAPABILITIES_PTR
mdefine_line|#define&t;PCI_CAPABILITIES_PTR&t;0x34&t;&t;/* Capabilities Pointer */
DECL|macro|PCI_INTR_LINE
mdefine_line|#define&t;PCI_INTR_LINE&t;&t;0x3C&t;&t;/* Interrupt Line (1B) */
DECL|macro|PCI_INTR_PIN
mdefine_line|#define&t;PCI_INTR_PIN&t;&t;0x3D&t;&t;/* Interrupt Pin (1B) */
DECL|macro|PCI_CFG_VEND_SPECIFIC
mdefine_line|#define PCI_CFG_VEND_SPECIFIC&t;0x40&t;&t;/* first vendor specific reg */
multiline_comment|/* layout for Type 0x01 headers */
DECL|macro|PCI_CFG_PPB_BUS_PRI
mdefine_line|#define&t;PCI_CFG_PPB_BUS_PRI&t;&t;0x18&t;/* immediate upstream bus # */
DECL|macro|PCI_CFG_PPB_BUS_SEC
mdefine_line|#define&t;PCI_CFG_PPB_BUS_SEC&t;&t;0x19&t;/* immediate downstream bus # */
DECL|macro|PCI_CFG_PPB_BUS_SUB
mdefine_line|#define&t;PCI_CFG_PPB_BUS_SUB&t;&t;0x1A&t;/* last downstream bus # */
DECL|macro|PCI_CFG_PPB_SEC_LAT
mdefine_line|#define&t;PCI_CFG_PPB_SEC_LAT&t;&t;0x1B&t;/* latency timer for SEC bus */
DECL|macro|PCI_CFG_PPB_IOBASE
mdefine_line|#define PCI_CFG_PPB_IOBASE&t;&t;0x1C&t;/* IO Base Addr bits 12..15 */
DECL|macro|PCI_CFG_PPB_IOLIM
mdefine_line|#define PCI_CFG_PPB_IOLIM&t;&t;0x1D&t;/* IO Limit Addr bits 12..15 */
DECL|macro|PCI_CFG_PPB_SEC_STAT
mdefine_line|#define&t;PCI_CFG_PPB_SEC_STAT&t;&t;0x1E&t;/* Secondary Status */
DECL|macro|PCI_CFG_PPB_MEMBASE
mdefine_line|#define PCI_CFG_PPB_MEMBASE&t;&t;0x20&t;/* MEM Base Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_MEMLIM
mdefine_line|#define PCI_CFG_PPB_MEMLIM&t;&t;0x22&t;/* MEM Limit Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_MEMPFBASE
mdefine_line|#define PCI_CFG_PPB_MEMPFBASE&t;&t;0x24&t;/* PfMEM Base Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_MEMPFLIM
mdefine_line|#define PCI_CFG_PPB_MEMPFLIM&t;&t;0x26&t;/* PfMEM Limit Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_MEMPFBASEHI
mdefine_line|#define PCI_CFG_PPB_MEMPFBASEHI&t;&t;0x28&t;/* PfMEM Base Addr bits 32..63 */
DECL|macro|PCI_CFG_PPB_MEMPFLIMHI
mdefine_line|#define PCI_CFG_PPB_MEMPFLIMHI&t;&t;0x2C&t;/* PfMEM Limit Addr bits 32..63 */
DECL|macro|PCI_CFG_PPB_IOBASEHI
mdefine_line|#define PCI_CFG_PPB_IOBASEHI&t;&t;0x30&t;/* IO Base Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_IOLIMHI
mdefine_line|#define PCI_CFG_PPB_IOLIMHI&t;&t;0x32&t;/* IO Limit Addr bits 16..31 */
DECL|macro|PCI_CFG_PPB_SUB_VENDOR
mdefine_line|#define&t;PCI_CFG_PPB_SUB_VENDOR&t;&t;0x34&t;/* Subsystem Vendor ID */
DECL|macro|PCI_CFG_PPB_SUB_DEVICE
mdefine_line|#define&t;PCI_CFG_PPB_SUB_DEVICE&t;&t;0x36&t;/* Subsystem Device ID */
DECL|macro|PCI_CFG_PPB_ROM_BASE
mdefine_line|#define&t;PCI_CFG_PPB_ROM_BASE&t;&t;0x38&t;/* ROM base address */
DECL|macro|PCI_CFG_PPB_INT_LINE
mdefine_line|#define&t;PCI_CFG_PPB_INT_LINE&t;&t;0x3C&t;/* Interrupt Line */
DECL|macro|PCI_CFG_PPB_INT_PIN
mdefine_line|#define&t;PCI_CFG_PPB_INT_PIN&t;&t;0x3D&t;/* Interrupt Pin */
DECL|macro|PCI_CFG_PPB_BRIDGE_CTRL
mdefine_line|#define&t;PCI_CFG_PPB_BRIDGE_CTRL&t;&t;0x3E&t;/* Bridge Control */
multiline_comment|/* XXX- these might be DEC 21152 specific */
DECL|macro|PCI_CFG_PPB_CHIP_CTRL
mdefine_line|#define&t;PCI_CFG_PPB_CHIP_CTRL&t;&t;0x40
DECL|macro|PCI_CFG_PPB_DIAG_CTRL
mdefine_line|#define&t;PCI_CFG_PPB_DIAG_CTRL&t;&t;0x41
DECL|macro|PCI_CFG_PPB_ARB_CTRL
mdefine_line|#define&t;PCI_CFG_PPB_ARB_CTRL&t;&t;0x42
DECL|macro|PCI_CFG_PPB_SERR_DISABLE
mdefine_line|#define&t;PCI_CFG_PPB_SERR_DISABLE&t;0x64
DECL|macro|PCI_CFG_PPB_CLK2_CTRL
mdefine_line|#define&t;PCI_CFG_PPB_CLK2_CTRL&t;&t;0x68
DECL|macro|PCI_CFG_PPB_SERR_STATUS
mdefine_line|#define&t;PCI_CFG_PPB_SERR_STATUS&t;&t;0x6A
multiline_comment|/* Command Register layout (0x04) */
DECL|macro|PCI_CMD_IO_SPACE
mdefine_line|#define&t;PCI_CMD_IO_SPACE&t;0x001&t;&t;/* I/O Space device */
DECL|macro|PCI_CMD_MEM_SPACE
mdefine_line|#define&t;PCI_CMD_MEM_SPACE&t;0x002&t;&t;/* Memory Space */
DECL|macro|PCI_CMD_BUS_MASTER
mdefine_line|#define&t;PCI_CMD_BUS_MASTER&t;0x004&t;&t;/* Bus Master */
DECL|macro|PCI_CMD_SPEC_CYCLES
mdefine_line|#define&t;PCI_CMD_SPEC_CYCLES&t;0x008&t;&t;/* Special Cycles */
DECL|macro|PCI_CMD_MEMW_INV_ENAB
mdefine_line|#define&t;PCI_CMD_MEMW_INV_ENAB&t;0x010&t;&t;/* Memory Write Inv Enable */
DECL|macro|PCI_CMD_VGA_PALETTE_SNP
mdefine_line|#define&t;PCI_CMD_VGA_PALETTE_SNP&t;0x020&t;&t;/* VGA Palette Snoop */
DECL|macro|PCI_CMD_PAR_ERR_RESP
mdefine_line|#define&t;PCI_CMD_PAR_ERR_RESP&t;0x040&t;&t;/* Parity Error Response */
DECL|macro|PCI_CMD_WAIT_CYCLE_CTL
mdefine_line|#define&t;PCI_CMD_WAIT_CYCLE_CTL&t;0x080&t;&t;/* Wait Cycle Control */
DECL|macro|PCI_CMD_SERR_ENABLE
mdefine_line|#define&t;PCI_CMD_SERR_ENABLE&t;0x100&t;&t;/* SERR# Enable */
DECL|macro|PCI_CMD_F_BK_BK_ENABLE
mdefine_line|#define&t;PCI_CMD_F_BK_BK_ENABLE&t;0x200&t;&t;/* Fast Back-to-Back Enable */
multiline_comment|/* Status Register Layout (0x06) */
DECL|macro|PCI_STAT_PAR_ERR_DET
mdefine_line|#define&t;PCI_STAT_PAR_ERR_DET&t;0x8000&t;&t;/* Detected Parity Error */
DECL|macro|PCI_STAT_SYS_ERR
mdefine_line|#define&t;PCI_STAT_SYS_ERR&t;0x4000&t;&t;/* Signaled System Error */
DECL|macro|PCI_STAT_RCVD_MSTR_ABT
mdefine_line|#define&t;PCI_STAT_RCVD_MSTR_ABT&t;0x2000&t;&t;/* Received Master Abort */
DECL|macro|PCI_STAT_RCVD_TGT_ABT
mdefine_line|#define&t;PCI_STAT_RCVD_TGT_ABT&t;0x1000&t;&t;/* Received Target Abort */
DECL|macro|PCI_STAT_SGNL_TGT_ABT
mdefine_line|#define&t;PCI_STAT_SGNL_TGT_ABT&t;0x0800&t;&t;/* Signaled Target Abort */
DECL|macro|PCI_STAT_DEVSEL_TIMING
mdefine_line|#define&t;PCI_STAT_DEVSEL_TIMING&t;0x0600&t;&t;/* DEVSEL Timing Mask */
DECL|macro|DEVSEL_TIMING
mdefine_line|#define&t;DEVSEL_TIMING(_x)&t;(((_x) &gt;&gt; 9) &amp; 3)&t;/* devsel tim macro */
DECL|macro|DEVSEL_FAST
mdefine_line|#define&t;DEVSEL_FAST&t;&t;0&t;&t;/* Fast timing */
DECL|macro|DEVSEL_MEDIUM
mdefine_line|#define&t;DEVSEL_MEDIUM&t;&t;1&t;&t;/* Medium timing */
DECL|macro|DEVSEL_SLOW
mdefine_line|#define&t;DEVSEL_SLOW&t;&t;2&t;&t;/* Slow timing */
DECL|macro|PCI_STAT_DATA_PAR_ERR
mdefine_line|#define&t;PCI_STAT_DATA_PAR_ERR&t;0x0100&t;&t;/* Data Parity Err Detected */
DECL|macro|PCI_STAT_F_BK_BK_CAP
mdefine_line|#define&t;PCI_STAT_F_BK_BK_CAP&t;0x0080&t;&t;/* Fast Back-to-Back Capable */
DECL|macro|PCI_STAT_UDF_SUPP
mdefine_line|#define&t;PCI_STAT_UDF_SUPP&t;0x0040&t;&t;/* UDF Supported */
DECL|macro|PCI_STAT_66MHZ_CAP
mdefine_line|#define&t;PCI_STAT_66MHZ_CAP&t;0x0020&t;&t;/* 66 MHz Capable */
DECL|macro|PCI_STAT_CAP_LIST
mdefine_line|#define&t;PCI_STAT_CAP_LIST&t;0x0010&t;&t;/* Capabilities List */
multiline_comment|/* BIST Register Layout (0x0F) */
DECL|macro|PCI_BIST_BIST_CAP
mdefine_line|#define&t;PCI_BIST_BIST_CAP&t;0x80&t;&t;/* BIST Capable */
DECL|macro|PCI_BIST_START_BIST
mdefine_line|#define&t;PCI_BIST_START_BIST&t;0x40&t;&t;/* Start BIST */
DECL|macro|PCI_BIST_CMPLTION_MASK
mdefine_line|#define&t;PCI_BIST_CMPLTION_MASK&t;0x0F&t;&t;/* COMPLETION MASK */
DECL|macro|PCI_BIST_CMPL_OK
mdefine_line|#define&t;PCI_BIST_CMPL_OK&t;0x00&t;&t;/* 0 value is completion OK */
multiline_comment|/* Base Address Register 0x10 */
DECL|macro|PCI_BA_IO_CODEMASK
mdefine_line|#define PCI_BA_IO_CODEMASK&t;0x3&t;&t;/* bottom 2 bits encode I/O BAR type */
DECL|macro|PCI_BA_IO_SPACE
mdefine_line|#define&t;PCI_BA_IO_SPACE&t;&t;0x1&t;&t;/* I/O Space Marker */
DECL|macro|PCI_BA_MEM_CODEMASK
mdefine_line|#define PCI_BA_MEM_CODEMASK&t;0xf&t;&t;/* bottom 4 bits encode MEM BAR type */
DECL|macro|PCI_BA_MEM_LOCATION
mdefine_line|#define&t;PCI_BA_MEM_LOCATION&t;0x6&t;&t;/* 2 bits for location avail */
DECL|macro|PCI_BA_MEM_32BIT
mdefine_line|#define&t;PCI_BA_MEM_32BIT&t;0x0&t;&t;/* Anywhere in 32bit space */
DECL|macro|PCI_BA_MEM_1MEG
mdefine_line|#define&t;PCI_BA_MEM_1MEG&t;&t;0x2&t;&t;/* Locate below 1 Meg */
DECL|macro|PCI_BA_MEM_64BIT
mdefine_line|#define&t;PCI_BA_MEM_64BIT&t;0x4&t;&t;/* Anywhere in 64bit space */
DECL|macro|PCI_BA_PREFETCH
mdefine_line|#define&t;PCI_BA_PREFETCH&t;&t;0x8&t;&t;/* Prefetchable, no side effect */
DECL|macro|PCI_BA_ROM_CODEMASK
mdefine_line|#define PCI_BA_ROM_CODEMASK&t;0x1&t;&t;/* bottom bit control expansion ROM enable */
DECL|macro|PCI_BA_ROM_ENABLE
mdefine_line|#define PCI_BA_ROM_ENABLE&t;0x1&t;&t;/* enable expansion ROM */
multiline_comment|/* Bridge Control Register 0x3e */
DECL|macro|PCI_BCTRL_DTO_SERR
mdefine_line|#define PCI_BCTRL_DTO_SERR&t;0x0800&t;&t;/* Discard Timer timeout generates SERR on primary bus */
DECL|macro|PCI_BCTRL_DTO
mdefine_line|#define PCI_BCTRL_DTO&t;&t;0x0400&t;&t;/* Discard Timer timeout status */
DECL|macro|PCI_BCTRL_DTO_SEC
mdefine_line|#define PCI_BCTRL_DTO_SEC&t;0x0200&t;&t;/* Secondary Discard Timer: 0 =&gt; 2^15 PCI clock cycles, 1 =&gt; 2^10 */
DECL|macro|PCI_BCTRL_DTO_PRI
mdefine_line|#define PCI_BCTRL_DTO_PRI&t;0x0100&t;&t;/* Primary Discard Timer: 0 =&gt; 2^15 PCI clock cycles, 1 =&gt; 2^10 */
DECL|macro|PCI_BCTRL_F_BK_BK_ENABLE
mdefine_line|#define PCI_BCTRL_F_BK_BK_ENABLE 0x0080&t;&t;/* Enable Fast Back-to-Back on secondary bus */
DECL|macro|PCI_BCTRL_RESET_SEC
mdefine_line|#define PCI_BCTRL_RESET_SEC&t;0x0040&t;&t;/* Reset Secondary bus */
DECL|macro|PCI_BCTRL_MSTR_ABT_MODE
mdefine_line|#define PCI_BCTRL_MSTR_ABT_MODE&t;0x0020&t;&t;/* Master Abort Mode: 0 =&gt; do not report Master-Aborts */
DECL|macro|PCI_BCTRL_VGA_AF_ENABLE
mdefine_line|#define PCI_BCTRL_VGA_AF_ENABLE&t;0x0008&t;&t;/* Enable VGA Address Forwarding */
DECL|macro|PCI_BCTRL_ISA_AF_ENABLE
mdefine_line|#define PCI_BCTRL_ISA_AF_ENABLE&t;0x0004&t;&t;/* Enable ISA Address Forwarding */
DECL|macro|PCI_BCTRL_SERR_ENABLE
mdefine_line|#define PCI_BCTRL_SERR_ENABLE&t;0x0002&t;&t;/* Enable forwarding of SERR from secondary bus to primary bus */
DECL|macro|PCI_BCTRL_PAR_ERR_RESP
mdefine_line|#define PCI_BCTRL_PAR_ERR_RESP&t;0x0001&t;&t;/* Enable Parity Error Response reporting on secondary interface */
multiline_comment|/*&n; * PCI 2.2 introduces the concept of ``capability lists.&squot;&squot;  Capability lists&n; * provide a flexible mechanism for a device or bridge to advertise one or&n; * more standardized capabilities such as the presense of a power management&n; * interface, etc.  The presense of a capability list is indicated by&n; * PCI_STAT_CAP_LIST being non-zero in the PCI_CFG_STATUS register.  If&n; * PCI_STAT_CAP_LIST is set, then PCI_CFG_CAP_PTR is a ``pointer&squot;&squot; into the&n; * device-specific portion of the configuration header where the first&n; * capability block is stored.  This ``pointer&squot;&squot; is a single byte which&n; * contains an offset from the beginning of the configuration header.  The&n; * bottom two bits of the pointer are reserved and should be masked off to&n; * determine the offset.  Each capability block contains a capability ID, a&n; * ``pointer&squot;&squot; to the next capability (another offset where a zero terminates&n; * the list) and capability-specific data.  Each capability block starts with&n; * the capability ID and the ``next capability pointer.&squot;&squot;  All data following&n; * this are capability-dependent.&n; */
DECL|macro|PCI_CAP_ID
mdefine_line|#define PCI_CAP_ID&t;&t;0x00&t;&t;/* Capability ID (1B) */
DECL|macro|PCI_CAP_PTR
mdefine_line|#define PCI_CAP_PTR&t;&t;0x01&t;&t;/* Capability ``pointer&squot;&squot; (1B) */
multiline_comment|/* PCI Capability IDs */
DECL|macro|PCI_CAP_PM
mdefine_line|#define&t;PCI_CAP_PM&t;&t;0x01&t;&t;/* PCI Power Management */
DECL|macro|PCI_CAP_AGP
mdefine_line|#define&t;PCI_CAP_AGP&t;&t;0x02&t;&t;/* Accelerated Graphics Port */
DECL|macro|PCI_CAP_VPD
mdefine_line|#define&t;PCI_CAP_VPD&t;&t;0x03&t;&t;/* Vital Product Data (VPD) */
DECL|macro|PCI_CAP_SID
mdefine_line|#define&t;PCI_CAP_SID&t;&t;0x04&t;&t;/* Slot Identification */
DECL|macro|PCI_CAP_MSI
mdefine_line|#define PCI_CAP_MSI&t;&t;0x05&t;&t;/* Message Signaled Intr */
DECL|macro|PCI_CAP_HS
mdefine_line|#define&t;PCI_CAP_HS&t;&t;0x06&t;&t;/* CompactPCI Hot Swap */
DECL|macro|PCI_CAP_PCIX
mdefine_line|#define&t;PCI_CAP_PCIX&t;&t;0x07&t;&t;/* PCI-X */
DECL|macro|PCI_CAP_ID_HT
mdefine_line|#define PCI_CAP_ID_HT&t;&t;0x08&t;&t;/* HyperTransport */
multiline_comment|/* PIO interface macros */
macro_line|#ifndef IOC3_EMULATION
DECL|macro|PCI_INB
mdefine_line|#define PCI_INB(x)          (*((volatile char*)x))
DECL|macro|PCI_INH
mdefine_line|#define PCI_INH(x)          (*((volatile short*)x))
DECL|macro|PCI_INW
mdefine_line|#define PCI_INW(x)          (*((volatile int*)x))
DECL|macro|PCI_OUTB
mdefine_line|#define PCI_OUTB(x,y)       (*((volatile char*)x) = y)
DECL|macro|PCI_OUTH
mdefine_line|#define PCI_OUTH(x,y)       (*((volatile short*)x) = y)
DECL|macro|PCI_OUTW
mdefine_line|#define PCI_OUTW(x,y)       (*((volatile int*)x) = y)
macro_line|#else
r_extern
id|uint
id|pci_read
c_func
(paren
r_void
op_star
id|address
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|pci_write
c_func
(paren
r_void
op_star
id|address
comma
r_int
id|data
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|BYTE
mdefine_line|#define BYTE   1
DECL|macro|HALF
mdefine_line|#define HALF   2
DECL|macro|WORD
mdefine_line|#define WORD   4
DECL|macro|PCI_INB
mdefine_line|#define PCI_INB(x)          pci_read((void *)(x),BYTE)
DECL|macro|PCI_INH
mdefine_line|#define PCI_INH(x)          pci_read((void *)(x),HALF)
DECL|macro|PCI_INW
mdefine_line|#define PCI_INW(x)          pci_read((void *)(x),WORD)
DECL|macro|PCI_OUTB
mdefine_line|#define PCI_OUTB(x,y)       pci_write((void *)(x),(y),BYTE)
DECL|macro|PCI_OUTH
mdefine_line|#define PCI_OUTH(x,y)       pci_write((void *)(x),(y),HALF)
DECL|macro|PCI_OUTW
mdefine_line|#define PCI_OUTW(x,y)       pci_write((void *)(x),(y),WORD)
macro_line|#endif /* !IOC3_EMULATION */
multiline_comment|/* effects on reads, merges */
multiline_comment|/*&n; * Definition of address layouts for PCI Config mechanism #1&n; * XXX- These largely duplicate PCI_TYPE1 constants at the top&n; * of the file; the two groups should probably be combined.&n; */
DECL|macro|CFG1_ADDR_REGISTER_MASK
mdefine_line|#define CFG1_ADDR_REGISTER_MASK&t;&t;0x000000fc
DECL|macro|CFG1_ADDR_FUNCTION_MASK
mdefine_line|#define CFG1_ADDR_FUNCTION_MASK&t;&t;0x00000700
DECL|macro|CFG1_ADDR_DEVICE_MASK
mdefine_line|#define CFG1_ADDR_DEVICE_MASK&t;&t;0x0000f800
DECL|macro|CFG1_ADDR_BUS_MASK
mdefine_line|#define CFG1_ADDR_BUS_MASK&t;&t;0x00ff0000
DECL|macro|CFG1_REGISTER_SHIFT
mdefine_line|#define CFG1_REGISTER_SHIFT&t;&t;2
DECL|macro|CFG1_FUNCTION_SHIFT
mdefine_line|#define CFG1_FUNCTION_SHIFT&t;&t;8
DECL|macro|CFG1_DEVICE_SHIFT
mdefine_line|#define CFG1_DEVICE_SHIFT&t;&t;11
DECL|macro|CFG1_BUS_SHIFT
mdefine_line|#define CFG1_BUS_SHIFT&t;&t;&t;16
macro_line|#ifdef CONFIG_SGI_IP32
multiline_comment|/* Definitions related to IP32 PCI Bridge policy&n;  * XXX- should probaly be moved to a mace-specific header&n;  */
DECL|macro|PCI_CONFIG_BITS
mdefine_line|#define PCI_CONFIG_BITS&t;&t;&t;0xfe0085ff
DECL|macro|PCI_CONTROL_MRMRA_ENABLE
mdefine_line|#define&t;PCI_CONTROL_MRMRA_ENABLE&t;0x00000800
DECL|macro|PCI_FIRST_IO_ADDR
mdefine_line|#define PCI_FIRST_IO_ADDR&t;&t;0x1000
DECL|macro|PCI_IO_MAP_INCR
mdefine_line|#define PCI_IO_MAP_INCR&t;&t;&t;0x1000
macro_line|#endif /* CONFIG_SGI_IP32 */
multiline_comment|/*&n; * Class codes&n; */
DECL|macro|PCI_CFG_CLASS_PRE20
mdefine_line|#define PCI_CFG_CLASS_PRE20&t;0x00
DECL|macro|PCI_CFG_CLASS_STORAGE
mdefine_line|#define PCI_CFG_CLASS_STORAGE&t;0x01
DECL|macro|PCI_CFG_CLASS_NETWORK
mdefine_line|#define PCI_CFG_CLASS_NETWORK&t;0x02
DECL|macro|PCI_CFG_CLASS_DISPLAY
mdefine_line|#define PCI_CFG_CLASS_DISPLAY&t;0x03
DECL|macro|PCI_CFG_CLASS_MMEDIA
mdefine_line|#define PCI_CFG_CLASS_MMEDIA&t;0x04
DECL|macro|PCI_CFG_CLASS_MEMORY
mdefine_line|#define PCI_CFG_CLASS_MEMORY&t;0x05
DECL|macro|PCI_CFG_CLASS_BRIDGE
mdefine_line|#define PCI_CFG_CLASS_BRIDGE&t;0x06
DECL|macro|PCI_CFG_CLASS_COMM
mdefine_line|#define PCI_CFG_CLASS_COMM&t;0x07
DECL|macro|PCI_CFG_CLASS_BASE
mdefine_line|#define PCI_CFG_CLASS_BASE&t;0x08
DECL|macro|PCI_CFG_CLASS_INPUT
mdefine_line|#define PCI_CFG_CLASS_INPUT&t;0x09
DECL|macro|PCI_CFG_CLASS_DOCK
mdefine_line|#define PCI_CFG_CLASS_DOCK&t;0x0A
DECL|macro|PCI_CFG_CLASS_PROC
mdefine_line|#define PCI_CFG_CLASS_PROC&t;0x0B
DECL|macro|PCI_CFG_CLASS_SERIALBUS
mdefine_line|#define PCI_CFG_CLASS_SERIALBUS&t;0x0C
DECL|macro|PCI_CFG_CLASS_OTHER
mdefine_line|#define PCI_CFG_CLASS_OTHER&t;0xFF
multiline_comment|/*&n; * Important Subclasses&n; */
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_HOST
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_HOST&t;0x00
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_ISA
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_ISA&t;0x01
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_EISA
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_EISA&t;0x02
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_MC
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_MC&t;0x03
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_PCI
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_PCI&t;0x04
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_PCMCIA
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_PCMCIA&t;0x05
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_NUBUS
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_NUBUS&t;0x06
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_CARDBUS
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_CARDBUS&t;0x07
DECL|macro|PCI_CFG_SUBCLASS_BRIDGE_OTHER
mdefine_line|#define PCI_CFG_SUBCLASS_BRIDGE_OTHER&t;0x80
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef LITTLE_ENDIAN
multiline_comment|/*&n; * PCI config space definition&n; */
DECL|struct|pci_cfg_s
r_typedef
r_volatile
r_struct
id|pci_cfg_s
(brace
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|dev_id
r_uint16
id|dev_id
suffix:semicolon
DECL|member|cmd
r_uint16
id|cmd
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|rev
id|uchar_t
id|rev
suffix:semicolon
DECL|member|prog_if
id|uchar_t
id|prog_if
suffix:semicolon
DECL|member|sub_class
id|uchar_t
id|sub_class
suffix:semicolon
DECL|member|class
id|uchar_t
r_class
suffix:semicolon
DECL|member|line_size
id|uchar_t
id|line_size
suffix:semicolon
DECL|member|lt
id|uchar_t
id|lt
suffix:semicolon
DECL|member|hdr_type
id|uchar_t
id|hdr_type
suffix:semicolon
DECL|member|bist
id|uchar_t
id|bist
suffix:semicolon
DECL|member|bar
r_uint32
id|bar
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|cardbus
r_uint32
id|cardbus
suffix:semicolon
DECL|member|subsys_vendor_id
r_uint16
id|subsys_vendor_id
suffix:semicolon
DECL|member|subsys_dev_id
r_uint16
id|subsys_dev_id
suffix:semicolon
DECL|member|exp_rom
r_uint32
id|exp_rom
suffix:semicolon
DECL|member|res
r_uint32
id|res
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|int_line
id|uchar_t
id|int_line
suffix:semicolon
DECL|member|int_pin
id|uchar_t
id|int_pin
suffix:semicolon
DECL|member|min_gnt
id|uchar_t
id|min_gnt
suffix:semicolon
DECL|member|max_lat
id|uchar_t
id|max_lat
suffix:semicolon
DECL|typedef|pci_cfg_t
)brace
id|pci_cfg_t
suffix:semicolon
multiline_comment|/*&n; * PCI Type 1 config space definition for PCI to PCI Bridges (PPBs)&n; */
DECL|struct|pci_cfg1_s
r_typedef
r_volatile
r_struct
id|pci_cfg1_s
(brace
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|dev_id
r_uint16
id|dev_id
suffix:semicolon
DECL|member|cmd
r_uint16
id|cmd
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|rev
id|uchar_t
id|rev
suffix:semicolon
DECL|member|prog_if
id|uchar_t
id|prog_if
suffix:semicolon
DECL|member|sub_class
id|uchar_t
id|sub_class
suffix:semicolon
DECL|member|class
id|uchar_t
r_class
suffix:semicolon
DECL|member|line_size
id|uchar_t
id|line_size
suffix:semicolon
DECL|member|lt
id|uchar_t
id|lt
suffix:semicolon
DECL|member|hdr_type
id|uchar_t
id|hdr_type
suffix:semicolon
DECL|member|bist
id|uchar_t
id|bist
suffix:semicolon
DECL|member|bar
r_uint32
id|bar
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pri_bus_num
id|uchar_t
id|pri_bus_num
suffix:semicolon
DECL|member|snd_bus_num
id|uchar_t
id|snd_bus_num
suffix:semicolon
DECL|member|sub_bus_num
id|uchar_t
id|sub_bus_num
suffix:semicolon
DECL|member|slt
id|uchar_t
id|slt
suffix:semicolon
DECL|member|io_base
id|uchar_t
id|io_base
suffix:semicolon
DECL|member|io_limit
id|uchar_t
id|io_limit
suffix:semicolon
DECL|member|snd_status
r_uint16
id|snd_status
suffix:semicolon
DECL|member|mem_base
r_uint16
id|mem_base
suffix:semicolon
DECL|member|mem_limit
r_uint16
id|mem_limit
suffix:semicolon
DECL|member|pmem_base
r_uint16
id|pmem_base
suffix:semicolon
DECL|member|pmem_limit
r_uint16
id|pmem_limit
suffix:semicolon
DECL|member|pmem_base_upper
r_uint32
id|pmem_base_upper
suffix:semicolon
DECL|member|pmem_limit_upper
r_uint32
id|pmem_limit_upper
suffix:semicolon
DECL|member|io_base_upper
r_uint16
id|io_base_upper
suffix:semicolon
DECL|member|io_limit_upper
r_uint16
id|io_limit_upper
suffix:semicolon
DECL|member|res
r_uint32
id|res
suffix:semicolon
DECL|member|exp_rom
r_uint32
id|exp_rom
suffix:semicolon
DECL|member|int_line
id|uchar_t
id|int_line
suffix:semicolon
DECL|member|int_pin
id|uchar_t
id|int_pin
suffix:semicolon
DECL|member|ppb_control
r_uint16
id|ppb_control
suffix:semicolon
DECL|typedef|pci_cfg1_t
)brace
id|pci_cfg1_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Capability&n; */
DECL|struct|cap_pcix_cmd_reg_s
r_typedef
r_volatile
r_struct
id|cap_pcix_cmd_reg_s
(brace
DECL|member|data_parity_enable
r_uint16
id|data_parity_enable
suffix:colon
l_int|1
comma
DECL|member|enable_relaxed_order
id|enable_relaxed_order
suffix:colon
l_int|1
comma
DECL|member|max_mem_read_cnt
id|max_mem_read_cnt
suffix:colon
l_int|2
comma
DECL|member|max_split
id|max_split
suffix:colon
l_int|3
comma
DECL|member|reserved1
id|reserved1
suffix:colon
l_int|9
suffix:semicolon
DECL|typedef|cap_pcix_cmd_reg_t
)brace
id|cap_pcix_cmd_reg_t
suffix:semicolon
DECL|struct|cap_pcix_stat_reg_s
r_typedef
r_volatile
r_struct
id|cap_pcix_stat_reg_s
(brace
DECL|member|func_num
r_uint32
id|func_num
suffix:colon
l_int|3
comma
DECL|member|dev_num
id|dev_num
suffix:colon
l_int|5
comma
DECL|member|bus_num
id|bus_num
suffix:colon
l_int|8
comma
DECL|member|bit64_device
id|bit64_device
suffix:colon
l_int|1
comma
DECL|member|mhz133_capable
id|mhz133_capable
suffix:colon
l_int|1
comma
DECL|member|split_complt_discard
id|split_complt_discard
suffix:colon
l_int|1
comma
DECL|member|unexpect_split_complt
id|unexpect_split_complt
suffix:colon
l_int|1
comma
DECL|member|device_complex
id|device_complex
suffix:colon
l_int|1
comma
DECL|member|max_mem_read_cnt
id|max_mem_read_cnt
suffix:colon
l_int|2
comma
DECL|member|max_out_split
id|max_out_split
suffix:colon
l_int|3
comma
DECL|member|max_cum_read
id|max_cum_read
suffix:colon
l_int|3
comma
DECL|member|split_complt_err
id|split_complt_err
suffix:colon
l_int|1
comma
DECL|member|reserved1
id|reserved1
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|cap_pcix_stat_reg_t
)brace
id|cap_pcix_stat_reg_t
suffix:semicolon
DECL|struct|cap_pcix_type0_s
r_typedef
r_volatile
r_struct
id|cap_pcix_type0_s
(brace
DECL|member|pcix_cap_id
id|uchar_t
id|pcix_cap_id
suffix:semicolon
DECL|member|pcix_cap_nxt
id|uchar_t
id|pcix_cap_nxt
suffix:semicolon
DECL|member|pcix_type0_command
id|cap_pcix_cmd_reg_t
id|pcix_type0_command
suffix:semicolon
DECL|member|pcix_type0_status
id|cap_pcix_stat_reg_t
id|pcix_type0_status
suffix:semicolon
DECL|typedef|cap_pcix_type0_t
)brace
id|cap_pcix_type0_t
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; * PCI config space definition&n; */
DECL|struct|pci_cfg_s
r_typedef
r_volatile
r_struct
id|pci_cfg_s
(brace
DECL|member|dev_id
r_uint16
id|dev_id
suffix:semicolon
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|cmd
r_uint16
id|cmd
suffix:semicolon
DECL|member|class
id|uchar_t
r_class
suffix:semicolon
DECL|member|sub_class
id|uchar_t
id|sub_class
suffix:semicolon
DECL|member|prog_if
id|uchar_t
id|prog_if
suffix:semicolon
DECL|member|rev
id|uchar_t
id|rev
suffix:semicolon
DECL|member|bist
id|uchar_t
id|bist
suffix:semicolon
DECL|member|hdr_type
id|uchar_t
id|hdr_type
suffix:semicolon
DECL|member|lt
id|uchar_t
id|lt
suffix:semicolon
DECL|member|line_size
id|uchar_t
id|line_size
suffix:semicolon
DECL|member|bar
r_uint32
id|bar
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|cardbus
r_uint32
id|cardbus
suffix:semicolon
DECL|member|subsys_dev_id
r_uint16
id|subsys_dev_id
suffix:semicolon
DECL|member|subsys_vendor_id
r_uint16
id|subsys_vendor_id
suffix:semicolon
DECL|member|exp_rom
r_uint32
id|exp_rom
suffix:semicolon
DECL|member|res
r_uint32
id|res
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|max_lat
id|uchar_t
id|max_lat
suffix:semicolon
DECL|member|min_gnt
id|uchar_t
id|min_gnt
suffix:semicolon
DECL|member|int_pin
id|uchar_t
id|int_pin
suffix:semicolon
DECL|member|int_line
id|uchar_t
id|int_line
suffix:semicolon
DECL|typedef|pci_cfg_t
)brace
id|pci_cfg_t
suffix:semicolon
multiline_comment|/*&n; * PCI Type 1 config space definition for PCI to PCI Bridges (PPBs)&n; */
DECL|struct|pci_cfg1_s
r_typedef
r_volatile
r_struct
id|pci_cfg1_s
(brace
DECL|member|dev_id
r_uint16
id|dev_id
suffix:semicolon
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|cmd
r_uint16
id|cmd
suffix:semicolon
DECL|member|class
id|uchar_t
r_class
suffix:semicolon
DECL|member|sub_class
id|uchar_t
id|sub_class
suffix:semicolon
DECL|member|prog_if
id|uchar_t
id|prog_if
suffix:semicolon
DECL|member|rev
id|uchar_t
id|rev
suffix:semicolon
DECL|member|bist
id|uchar_t
id|bist
suffix:semicolon
DECL|member|hdr_type
id|uchar_t
id|hdr_type
suffix:semicolon
DECL|member|lt
id|uchar_t
id|lt
suffix:semicolon
DECL|member|line_size
id|uchar_t
id|line_size
suffix:semicolon
DECL|member|bar
r_uint32
id|bar
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|slt
id|uchar_t
id|slt
suffix:semicolon
DECL|member|sub_bus_num
id|uchar_t
id|sub_bus_num
suffix:semicolon
DECL|member|snd_bus_num
id|uchar_t
id|snd_bus_num
suffix:semicolon
DECL|member|pri_bus_num
id|uchar_t
id|pri_bus_num
suffix:semicolon
DECL|member|snd_status
r_uint16
id|snd_status
suffix:semicolon
DECL|member|io_limit
id|uchar_t
id|io_limit
suffix:semicolon
DECL|member|io_base
id|uchar_t
id|io_base
suffix:semicolon
DECL|member|mem_limit
r_uint16
id|mem_limit
suffix:semicolon
DECL|member|mem_base
r_uint16
id|mem_base
suffix:semicolon
DECL|member|pmem_limit
r_uint16
id|pmem_limit
suffix:semicolon
DECL|member|pmem_base
r_uint16
id|pmem_base
suffix:semicolon
DECL|member|pmem_limit_upper
r_uint32
id|pmem_limit_upper
suffix:semicolon
DECL|member|pmem_base_upper
r_uint32
id|pmem_base_upper
suffix:semicolon
DECL|member|io_limit_upper
r_uint16
id|io_limit_upper
suffix:semicolon
DECL|member|io_base_upper
r_uint16
id|io_base_upper
suffix:semicolon
DECL|member|res
r_uint32
id|res
suffix:semicolon
DECL|member|exp_rom
r_uint32
id|exp_rom
suffix:semicolon
DECL|member|ppb_control
r_uint16
id|ppb_control
suffix:semicolon
DECL|member|int_pin
id|uchar_t
id|int_pin
suffix:semicolon
DECL|member|int_line
id|uchar_t
id|int_line
suffix:semicolon
DECL|typedef|pci_cfg1_t
)brace
id|pci_cfg1_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Capability&n; */
DECL|struct|cap_pcix_cmd_reg_s
r_typedef
r_volatile
r_struct
id|cap_pcix_cmd_reg_s
(brace
DECL|member|reserved1
r_uint16
id|reserved1
suffix:colon
l_int|9
comma
DECL|member|max_split
id|max_split
suffix:colon
l_int|3
comma
DECL|member|max_mem_read_cnt
id|max_mem_read_cnt
suffix:colon
l_int|2
comma
DECL|member|enable_relaxed_order
id|enable_relaxed_order
suffix:colon
l_int|1
comma
DECL|member|data_parity_enable
id|data_parity_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|cap_pcix_cmd_reg_t
)brace
id|cap_pcix_cmd_reg_t
suffix:semicolon
DECL|struct|cap_pcix_stat_reg_s
r_typedef
r_volatile
r_struct
id|cap_pcix_stat_reg_s
(brace
DECL|member|reserved1
r_uint32
id|reserved1
suffix:colon
l_int|2
comma
DECL|member|split_complt_err
id|split_complt_err
suffix:colon
l_int|1
comma
DECL|member|max_cum_read
id|max_cum_read
suffix:colon
l_int|3
comma
DECL|member|max_out_split
id|max_out_split
suffix:colon
l_int|3
comma
DECL|member|max_mem_read_cnt
id|max_mem_read_cnt
suffix:colon
l_int|2
comma
DECL|member|device_complex
id|device_complex
suffix:colon
l_int|1
comma
DECL|member|unexpect_split_complt
id|unexpect_split_complt
suffix:colon
l_int|1
comma
DECL|member|split_complt_discard
id|split_complt_discard
suffix:colon
l_int|1
comma
DECL|member|mhz133_capable
id|mhz133_capable
suffix:colon
l_int|1
comma
DECL|member|bit64_device
id|bit64_device
suffix:colon
l_int|1
comma
DECL|member|bus_num
id|bus_num
suffix:colon
l_int|8
comma
DECL|member|dev_num
id|dev_num
suffix:colon
l_int|5
comma
DECL|member|func_num
id|func_num
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|cap_pcix_stat_reg_t
)brace
id|cap_pcix_stat_reg_t
suffix:semicolon
DECL|struct|cap_pcix_type0_s
r_typedef
r_volatile
r_struct
id|cap_pcix_type0_s
(brace
DECL|member|pcix_type0_command
id|cap_pcix_cmd_reg_t
id|pcix_type0_command
suffix:semicolon
DECL|member|pcix_cap_nxt
id|uchar_t
id|pcix_cap_nxt
suffix:semicolon
DECL|member|pcix_cap_id
id|uchar_t
id|pcix_cap_id
suffix:semicolon
DECL|member|pcix_type0_status
id|cap_pcix_stat_reg_t
id|pcix_type0_status
suffix:semicolon
DECL|typedef|cap_pcix_type0_t
)brace
id|cap_pcix_type0_t
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif /* _ASM_SN_PCI_PCI_DEFS_H */
eof
