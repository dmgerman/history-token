multiline_comment|/*&n; *  asm-ppc/gg2.h -- VLSI VAS96011/12 `Golden Gate 2&squot; register definitions&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is based on the following documentation:&n; *&n; *&t;The VAS96011/12 Chipset, Data Book, Edition 1.0&n; *&t;VLSI Technology, Inc.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _ASMPPC_GG2_H
DECL|macro|_ASMPPC_GG2_H
mdefine_line|#define _ASMPPC_GG2_H
multiline_comment|/*&n;     *  Memory Map (CHRP mode)&n;     */
DECL|macro|GG2_PCI_MEM_BASE
mdefine_line|#define GG2_PCI_MEM_BASE&t;0xc0000000&t;/* Peripheral memory space */
DECL|macro|GG2_ISA_MEM_BASE
mdefine_line|#define GG2_ISA_MEM_BASE&t;0xf7000000&t;/* Peripheral memory alias */
DECL|macro|GG2_ISA_IO_BASE
mdefine_line|#define GG2_ISA_IO_BASE&t;&t;0xf8000000&t;/* Peripheral I/O space */
DECL|macro|GG2_PCI_CONFIG_BASE
mdefine_line|#define GG2_PCI_CONFIG_BASE&t;0xfec00000&t;/* PCI configuration space */
DECL|macro|GG2_INT_ACK_SPECIAL
mdefine_line|#define GG2_INT_ACK_SPECIAL&t;0xfec80000&t;/* Interrupt acknowledge and */
multiline_comment|/* special PCI cycles */
DECL|macro|GG2_ROM_BASE0
mdefine_line|#define GG2_ROM_BASE0&t;&t;0xff000000&t;/* ROM bank 0 */
DECL|macro|GG2_ROM_BASE1
mdefine_line|#define GG2_ROM_BASE1&t;&t;0xff800000&t;/* ROM bank 1 */
multiline_comment|/*&n;     *  GG2 specific PCI Registers&n;     */
DECL|macro|GG2_PCI_BUSNO
mdefine_line|#define GG2_PCI_BUSNO&t;&t;0x40&t;/* Bus number */
DECL|macro|GG2_PCI_SUBBUSNO
mdefine_line|#define GG2_PCI_SUBBUSNO&t;0x41&t;/* Subordinate bus number */
DECL|macro|GG2_PCI_DISCCTR
mdefine_line|#define GG2_PCI_DISCCTR&t;&t;0x42&t;/* Disconnect counter */
DECL|macro|GG2_PCI_PPC_CTRL
mdefine_line|#define GG2_PCI_PPC_CTRL&t;0x50&t;/* PowerPC interface control register */
DECL|macro|GG2_PCI_ADDR_MAP
mdefine_line|#define GG2_PCI_ADDR_MAP&t;0x5c&t;/* Address map */
DECL|macro|GG2_PCI_PCI_CTRL
mdefine_line|#define GG2_PCI_PCI_CTRL&t;0x60&t;/* PCI interface control register */
DECL|macro|GG2_PCI_ROM_CTRL
mdefine_line|#define GG2_PCI_ROM_CTRL&t;0x70&t;/* ROM interface control register */
DECL|macro|GG2_PCI_ROM_TIME
mdefine_line|#define GG2_PCI_ROM_TIME&t;0x74&t;/* ROM timing */
DECL|macro|GG2_PCI_CC_CTRL
mdefine_line|#define GG2_PCI_CC_CTRL&t;&t;0x80&t;/* Cache controller control register */
DECL|macro|GG2_PCI_DRAM_BANK0
mdefine_line|#define GG2_PCI_DRAM_BANK0&t;0x90&t;/* Control register for DRAM bank #0 */
DECL|macro|GG2_PCI_DRAM_BANK1
mdefine_line|#define GG2_PCI_DRAM_BANK1&t;0x94&t;/* Control register for DRAM bank #1 */
DECL|macro|GG2_PCI_DRAM_BANK2
mdefine_line|#define GG2_PCI_DRAM_BANK2&t;0x98&t;/* Control register for DRAM bank #2 */
DECL|macro|GG2_PCI_DRAM_BANK3
mdefine_line|#define GG2_PCI_DRAM_BANK3&t;0x9c&t;/* Control register for DRAM bank #3 */
DECL|macro|GG2_PCI_DRAM_BANK4
mdefine_line|#define GG2_PCI_DRAM_BANK4&t;0xa0&t;/* Control register for DRAM bank #4 */
DECL|macro|GG2_PCI_DRAM_BANK5
mdefine_line|#define GG2_PCI_DRAM_BANK5&t;0xa4&t;/* Control register for DRAM bank #5 */
DECL|macro|GG2_PCI_DRAM_TIME0
mdefine_line|#define GG2_PCI_DRAM_TIME0&t;0xb0&t;/* Timing parameters set #0 */
DECL|macro|GG2_PCI_DRAM_TIME1
mdefine_line|#define GG2_PCI_DRAM_TIME1&t;0xb4&t;/* Timing parameters set #1 */
DECL|macro|GG2_PCI_DRAM_CTRL
mdefine_line|#define GG2_PCI_DRAM_CTRL&t;0xc0&t;/* DRAM control */
DECL|macro|GG2_PCI_ERR_CTRL
mdefine_line|#define GG2_PCI_ERR_CTRL&t;0xd0&t;/* Error control register */
DECL|macro|GG2_PCI_ERR_STATUS
mdefine_line|#define GG2_PCI_ERR_STATUS&t;0xd4&t;/* Error status register */
multiline_comment|/* Cleared when read */
macro_line|#endif /* _ASMPPC_GG2_H */
eof
