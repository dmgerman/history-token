multiline_comment|/*&n; * iSeries_dma.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _ISERIES_DMA_H
DECL|macro|_ISERIES_DMA_H
mdefine_line|#define _ISERIES_DMA_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef __LINUX_SPINLOCK_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif
singleline_comment|// NUM_TCE_LEVELS defines the largest contiguous block
singleline_comment|// of dma (tce) space we can get.  NUM_TCE_LEVELS = 10 
singleline_comment|// allows up to 2**9 pages (512 * 4096) = 2 MB
DECL|macro|NUM_TCE_LEVELS
mdefine_line|#define NUM_TCE_LEVELS 10
DECL|macro|NO_TCE
mdefine_line|#define NO_TCE ((dma_addr_t)-1)
singleline_comment|// Tces come in two formats, one for the virtual bus and a different
singleline_comment|// format for PCI
DECL|macro|TCE_VB
mdefine_line|#define TCE_VB  0
DECL|macro|TCE_PCI
mdefine_line|#define TCE_PCI 1
DECL|union|Tce
r_union
id|Tce
(brace
DECL|member|wholeTce
id|u64
id|wholeTce
suffix:semicolon
r_struct
(brace
DECL|member|cacheBits
id|u64
id|cacheBits
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Cache hash bits - not used */
DECL|member|rsvd
id|u64
id|rsvd
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rpn
id|u64
id|rpn
suffix:colon
l_int|40
suffix:semicolon
multiline_comment|/* Absolute page number */
DECL|member|valid
id|u64
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tce is valid (vb only) */
DECL|member|allIo
id|u64
id|allIo
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tce is valid for all lps (vb only) */
DECL|member|lpIndex
id|u64
id|lpIndex
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* LpIndex for user of TCE (vb only) */
DECL|member|pciWrite
id|u64
id|pciWrite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write allowed (pci only) */
DECL|member|readWrite
id|u64
id|readWrite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read allowed (pci), Write allowed&n;&t;&t;&t;&t;&t;&t;   (vb) */
DECL|member|tceBits
)brace
id|tceBits
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Bitmap
r_struct
id|Bitmap
(brace
DECL|member|numBits
r_int
r_int
id|numBits
suffix:semicolon
DECL|member|numBytes
r_int
r_int
id|numBytes
suffix:semicolon
DECL|member|map
r_int
r_char
op_star
id|map
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|MultiLevelBitmap
r_struct
id|MultiLevelBitmap
(brace
DECL|member|maxLevel
r_int
r_int
id|maxLevel
suffix:semicolon
DECL|member|level
r_struct
id|Bitmap
id|level
(braket
id|NUM_TCE_LEVELS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|TceTable
r_struct
id|TceTable
(brace
DECL|member|busNumber
id|u64
id|busNumber
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
DECL|member|startOffset
id|u64
id|startOffset
suffix:semicolon
DECL|member|index
id|u64
id|index
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|mlbm
r_struct
id|MultiLevelBitmap
id|mlbm
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|HvTceTableManagerCB
r_struct
id|HvTceTableManagerCB
(brace
DECL|member|busNumber
id|u64
id|busNumber
suffix:semicolon
multiline_comment|/* Bus number for this tce table */
DECL|member|start
id|u64
id|start
suffix:semicolon
multiline_comment|/* Will be NULL for secondary */
DECL|member|totalSize
id|u64
id|totalSize
suffix:semicolon
multiline_comment|/* Size (in pages) of whole table */
DECL|member|startOffset
id|u64
id|startOffset
suffix:semicolon
multiline_comment|/* Index into real tce table of the&n;&t;&t;&t;&t;&t;   start of our section */
DECL|member|size
id|u64
id|size
suffix:semicolon
multiline_comment|/* Size (in pages) of our section */
DECL|member|index
id|u64
id|index
suffix:semicolon
multiline_comment|/* Index of this tce table (token?) */
DECL|member|maxTceTableIndex
id|u16
id|maxTceTableIndex
suffix:semicolon
multiline_comment|/* Max number of tables for partition */
DECL|member|virtualBusFlag
id|u8
id|virtualBusFlag
suffix:semicolon
multiline_comment|/* Flag to indicate virtual bus */
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|TceTable
id|virtBusTceTable
suffix:semicolon
multiline_comment|/* Tce table for virtual bus */
r_extern
r_struct
id|TceTable
op_star
id|build_tce_table
c_func
(paren
r_struct
id|HvTceTableManagerCB
op_star
comma
r_struct
id|TceTable
op_star
)paren
suffix:semicolon
r_extern
r_void
id|create_virtual_bus_tce_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|create_pci_bus_tce_table
c_func
(paren
r_int
id|busNumber
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// _ISERIES_DMA_H
eof
