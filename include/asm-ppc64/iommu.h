multiline_comment|/*&n; * iommu.h&n; * Copyright (C) 2001 Mike Corrigan &amp; Dave Engebretsen, IBM Corporation&n; * Rewrite, cleanup:&n; * Copyright (C) 2004 Olof Johansson &lt;olof@austin.ibm.com&gt;, IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _ASM_IOMMU_H
DECL|macro|_ASM_IOMMU_H
mdefine_line|#define _ASM_IOMMU_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
multiline_comment|/*&n; * IOMAP_MAX_ORDER defines the largest contiguous block&n; * of dma (tce) space we can get.  IOMAP_MAX_ORDER = 13&n; * allows up to 2**12 pages (4096 * 4096) = 16 MB&n; */
DECL|macro|IOMAP_MAX_ORDER
mdefine_line|#define IOMAP_MAX_ORDER 13
multiline_comment|/*&n; * Tces come in two formats, one for the virtual bus and a different&n; * format for PCI&n; */
DECL|macro|TCE_VB
mdefine_line|#define TCE_VB  0
DECL|macro|TCE_PCI
mdefine_line|#define TCE_PCI 1
multiline_comment|/* tce_entry&n; * Used by pSeries (SMP) and iSeries/pSeries LPAR, but there it&squot;s&n; * abstracted so layout is irrelevant.&n; */
DECL|union|tce_entry
r_union
id|tce_entry
(brace
DECL|member|te_word
r_int
r_int
id|te_word
suffix:semicolon
r_struct
(brace
DECL|member|tb_cacheBits
r_int
r_int
id|tb_cacheBits
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Cache hash bits - not used */
DECL|member|tb_rsvd
r_int
r_int
id|tb_rsvd
suffix:colon
l_int|6
suffix:semicolon
DECL|member|tb_rpn
r_int
r_int
id|tb_rpn
suffix:colon
l_int|40
suffix:semicolon
multiline_comment|/* Real page number */
DECL|member|tb_valid
r_int
r_int
id|tb_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tce is valid (vb only) */
DECL|member|tb_allio
r_int
r_int
id|tb_allio
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tce is valid for all lps (vb only) */
DECL|member|tb_lpindex
r_int
r_int
id|tb_lpindex
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* LpIndex for user of TCE (vb only) */
DECL|member|tb_pciwr
r_int
r_int
id|tb_pciwr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write allowed (pci only) */
DECL|member|tb_rdwr
r_int
r_int
id|tb_rdwr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read allowed  (pci), Write allowed (vb) */
DECL|member|te_bits
)brace
id|te_bits
suffix:semicolon
DECL|macro|te_cacheBits
mdefine_line|#define te_cacheBits te_bits.tb_cacheBits
DECL|macro|te_rpn
mdefine_line|#define te_rpn       te_bits.tb_rpn
DECL|macro|te_valid
mdefine_line|#define te_valid     te_bits.tb_valid
DECL|macro|te_allio
mdefine_line|#define te_allio     te_bits.tb_allio
DECL|macro|te_lpindex
mdefine_line|#define te_lpindex   te_bits.tb_lpindex
DECL|macro|te_pciwr
mdefine_line|#define te_pciwr     te_bits.tb_pciwr
DECL|macro|te_rdwr
mdefine_line|#define te_rdwr      te_bits.tb_rdwr
)brace
suffix:semicolon
DECL|struct|iommu_table
r_struct
id|iommu_table
(brace
DECL|member|it_busno
r_int
r_int
id|it_busno
suffix:semicolon
multiline_comment|/* Bus number this table belongs to */
DECL|member|it_size
r_int
r_int
id|it_size
suffix:semicolon
multiline_comment|/* Size in pages of iommu table */
DECL|member|it_offset
r_int
r_int
id|it_offset
suffix:semicolon
multiline_comment|/* Offset into global table */
DECL|member|it_base
r_int
r_int
id|it_base
suffix:semicolon
multiline_comment|/* mapped address of tce table */
DECL|member|it_index
r_int
r_int
id|it_index
suffix:semicolon
multiline_comment|/* which iommu table this is */
DECL|member|it_type
r_int
r_int
id|it_type
suffix:semicolon
multiline_comment|/* type: PCI or Virtual Bus */
DECL|member|it_entrysize
r_int
r_int
id|it_entrysize
suffix:semicolon
multiline_comment|/* Size of an entry in bytes */
DECL|member|it_blocksize
r_int
r_int
id|it_blocksize
suffix:semicolon
multiline_comment|/* Entries in each block (cacheline) */
DECL|member|it_hint
r_int
r_int
id|it_hint
suffix:semicolon
multiline_comment|/* Hint for next alloc */
DECL|member|it_largehint
r_int
r_int
id|it_largehint
suffix:semicolon
multiline_comment|/* Hint for large allocs */
DECL|member|it_halfpoint
r_int
r_int
id|it_halfpoint
suffix:semicolon
multiline_comment|/* Breaking point for small/large allocs */
DECL|member|it_lock
id|spinlock_t
id|it_lock
suffix:semicolon
multiline_comment|/* Protects it_map */
DECL|member|it_mapsize
r_int
r_int
id|it_mapsize
suffix:semicolon
multiline_comment|/* Size of map in # of entries (bits) */
DECL|member|it_map
r_int
r_int
op_star
id|it_map
suffix:semicolon
multiline_comment|/* A simple allocation bitmap for now */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|struct|iommu_table_cb
r_struct
id|iommu_table_cb
(brace
DECL|member|itc_busno
r_int
r_int
id|itc_busno
suffix:semicolon
multiline_comment|/* Bus number for this tce table */
DECL|member|itc_start
r_int
r_int
id|itc_start
suffix:semicolon
multiline_comment|/* Will be NULL for secondary */
DECL|member|itc_totalsize
r_int
r_int
id|itc_totalsize
suffix:semicolon
multiline_comment|/* Size (in pages) of whole table */
DECL|member|itc_offset
r_int
r_int
id|itc_offset
suffix:semicolon
multiline_comment|/* Index into real tce table of the&n;&t;&t;&t;&t;&t;   start of our section */
DECL|member|itc_size
r_int
r_int
id|itc_size
suffix:semicolon
multiline_comment|/* Size (in pages) of our section */
DECL|member|itc_index
r_int
r_int
id|itc_index
suffix:semicolon
multiline_comment|/* Index of this tce table */
DECL|member|itc_maxtables
r_int
r_int
id|itc_maxtables
suffix:semicolon
multiline_comment|/* Max num of tables for partition */
DECL|member|itc_virtbus
r_int
r_char
id|itc_virtbus
suffix:semicolon
multiline_comment|/* Flag to indicate virtual bus */
DECL|member|itc_slotno
r_int
r_char
id|itc_slotno
suffix:semicolon
multiline_comment|/* IOA Tce Slot Index */
DECL|member|itc_rsvd
r_int
r_char
id|itc_rsvd
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|iommu_table
id|vio_tce_table
suffix:semicolon
multiline_comment|/* Tce table for virtual bus */
macro_line|#endif /* CONFIG_PPC_ISERIES */
r_struct
id|scatterlist
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_MULTIPLATFORM
multiline_comment|/* Walks all buses and creates iommu tables */
r_extern
r_void
id|iommu_setup_pSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iommu_setup_u3
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Frees table for an individual device node */
r_extern
r_void
id|iommu_free_table
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_MULTIPLATFORM */
macro_line|#ifdef CONFIG_PPC_PSERIES
multiline_comment|/* Creates table for an individual device node */
r_extern
r_void
id|iommu_devnode_init_pSeries
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_PSERIES */
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/* Walks all buses and creates iommu tables */
r_extern
r_void
id|iommu_setup_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initializes tables for bio buses */
r_extern
r_void
id|__init
id|iommu_vio_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|iSeries_Device_Node
suffix:semicolon
multiline_comment|/* Creates table for an individual device node */
r_extern
r_void
id|iommu_devnode_init_iSeries
c_func
(paren
r_struct
id|iSeries_Device_Node
op_star
id|dn
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_ISERIES */
multiline_comment|/* Initializes an iommu_table based in values set in the passed-in&n; * structure&n; */
r_extern
r_struct
id|iommu_table
op_star
id|iommu_init_table
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
)paren
suffix:semicolon
r_extern
r_int
id|iommu_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|iommu_table
op_star
id|tbl
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_extern
r_void
id|iommu_unmap_sg
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nelems
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_extern
r_void
op_star
id|iommu_alloc_consistent
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
suffix:semicolon
r_extern
r_void
id|iommu_free_consistent
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
suffix:semicolon
r_extern
id|dma_addr_t
id|iommu_map_single
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_extern
r_void
id|iommu_unmap_single
c_func
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
suffix:semicolon
r_extern
r_void
id|tce_init_pSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tce_init_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pci_iommu_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pci_dma_init_direct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|alloc_u3_dart_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ppc64_iommu_off
suffix:semicolon
macro_line|#endif /* _ASM_IOMMU_H */
eof
