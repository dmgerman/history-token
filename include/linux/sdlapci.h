multiline_comment|/*****************************************************************************&n;* sdlapci.h&t;WANPIPE(tm) Multiprotocol WAN Link Driver.&n;*&t;&t;Definitions for the SDLA PCI adapter.&n;*&n;* Author:&t;Gideon Hack&t;&lt;ghack@sangoma.com&gt;&n;*&n;* Copyright:&t;(c) 1999-2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jun 02, 1999&t;Gideon Hack&t;Initial version.&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLAPCI_H
DECL|macro|_SDLAPCI_H
mdefine_line|#define&t;_SDLAPCI_H
multiline_comment|/****** Defines *************************************************************/
multiline_comment|/* Definitions for identifying and finding S514 PCI adapters */
DECL|macro|V3_VENDOR_ID
mdefine_line|#define V3_VENDOR_ID&t;&t;0x11B0&t;&t;/* V3 vendor ID number */
DECL|macro|V3_DEVICE_ID
mdefine_line|#define V3_DEVICE_ID  &t;&t;0x0002&t;&t;/* V3 device ID number */
DECL|macro|SANGOMA_SUBSYS_VENDOR
mdefine_line|#define SANGOMA_SUBSYS_VENDOR &t;0x4753&t;&t;/* ID for Sangoma */
DECL|macro|PCI_DEV_SLOT_MASK
mdefine_line|#define PCI_DEV_SLOT_MASK&t;0x1F&t;&t;/* mask for slot numbering */
DECL|macro|PCI_IRQ_NOT_ALLOCATED
mdefine_line|#define PCI_IRQ_NOT_ALLOCATED&t;0xFF&t;&t;/* interrupt line for no IRQ */
multiline_comment|/* Local PCI register offsets */
DECL|macro|PCI_VENDOR_ID_WORD
mdefine_line|#define PCI_VENDOR_ID_WORD&t;0x00&t;&t;/* vendor ID */
DECL|macro|PCI_IO_BASE_DWORD
mdefine_line|#define PCI_IO_BASE_DWORD&t;0x10&t;&t;/* IO base */&t;
DECL|macro|PCI_MEM_BASE0_DWORD
mdefine_line|#define PCI_MEM_BASE0_DWORD&t;0x14&t;&t;/* memory base - apperture 0 */
DECL|macro|PCI_MEM_BASE1_DWORD
mdefine_line|#define PCI_MEM_BASE1_DWORD     0x18&t;&t;/* memory base - apperture 1 */
DECL|macro|PCI_SUBSYS_VENDOR_WORD
mdefine_line|#define PCI_SUBSYS_VENDOR_WORD &t;0x2C&t;&t;/* subsystem vendor ID */
DECL|macro|PCI_INT_LINE_BYTE
mdefine_line|#define PCI_INT_LINE_BYTE&t;0x3C&t;&t;/* interrupt line */
DECL|macro|PCI_INT_PIN_BYTE
mdefine_line|#define PCI_INT_PIN_BYTE&t;0x3D&t;&t;/* interrupt pin */
DECL|macro|PCI_MAP0_DWORD
mdefine_line|#define PCI_MAP0_DWORD&t;&t;0x40&t;&t;/* PCI to local bus address 0 */
DECL|macro|PCI_MAP1_DWORD
mdefine_line|#define PCI_MAP1_DWORD          0x44&t;&t;/* PCI to local bus address 1 */
DECL|macro|PCI_INT_STATUS
mdefine_line|#define PCI_INT_STATUS          0x48&t;&t;/* interrupt status */
DECL|macro|PCI_INT_CONFIG
mdefine_line|#define PCI_INT_CONFIG&t;&t;0x4C&t;&t;/* interrupt configuration */
multiline_comment|/* Local PCI register usage */
DECL|macro|PCI_MEMORY_ENABLE
mdefine_line|#define PCI_MEMORY_ENABLE&t;0x00000003&t;/* enable PCI memory */
DECL|macro|PCI_CPU_A_MEM_DISABLE
mdefine_line|#define PCI_CPU_A_MEM_DISABLE&t;0x00000002&t;/* disable CPU A memory */
DECL|macro|PCI_CPU_B_MEM_DISABLE
mdefine_line|#define PCI_CPU_B_MEM_DISABLE  &t;0x00100002&t;/* disable CPU B memory */
DECL|macro|PCI_ENABLE_IRQ_CPU_A
mdefine_line|#define PCI_ENABLE_IRQ_CPU_A&t;0x005A0004&t;/* enable IRQ for CPU A */
DECL|macro|PCI_ENABLE_IRQ_CPU_B
mdefine_line|#define PCI_ENABLE_IRQ_CPU_B    0x005A0008&t;/* enable IRQ for CPU B */
DECL|macro|PCI_DISABLE_IRQ_CPU_A
mdefine_line|#define PCI_DISABLE_IRQ_CPU_A   0x00000004&t;/* disable IRQ for CPU A */
DECL|macro|PCI_DISABLE_IRQ_CPU_B
mdefine_line|#define PCI_DISABLE_IRQ_CPU_B   0x00000008&t;/* disable IRQ for CPU B */
multiline_comment|/* Setting for the Interrupt Status register */
DECL|macro|IRQ_CPU_A
mdefine_line|#define IRQ_CPU_A               0x04            /* IRQ for CPU A */
DECL|macro|IRQ_CPU_B
mdefine_line|#define IRQ_CPU_B               0x08&t;&t;/* IRQ for CPU B */
multiline_comment|/* The maximum size of the S514 memory */
DECL|macro|MAX_SIZEOF_S514_MEMORY
mdefine_line|#define MAX_SIZEOF_S514_MEMORY&t;(256 * 1024)
multiline_comment|/* S514 control register offsets within the memory address space */
DECL|macro|S514_CTRL_REG_BYTE
mdefine_line|#define S514_CTRL_REG_BYTE&t;0x80000
multiline_comment|/* S514 adapter control bytes */
DECL|macro|S514_CPU_HALT
mdefine_line|#define S514_CPU_HALT &t;&t;0x00
DECL|macro|S514_CPU_START
mdefine_line|#define S514_CPU_START&t;&t;0x01
multiline_comment|/* The maximum number of S514 adapters supported */
DECL|macro|MAX_S514_CARDS
mdefine_line|#define MAX_S514_CARDS&t;&t;20&t;
DECL|macro|PCI_CARD_TYPE
mdefine_line|#define PCI_CARD_TYPE&t;&t;0x2E
DECL|macro|S514_DUAL_CPU
mdefine_line|#define S514_DUAL_CPU&t;&t;0x12
DECL|macro|S514_SINGLE_CPU
mdefine_line|#define S514_SINGLE_CPU&t;&t;0x11
macro_line|#endif&t;/* _SDLAPCI_H */
eof
