multiline_comment|/*&n; * AGPGART&n; * Copyright (C) 2002-2003 Dave Jones&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#ifndef _AGP_BACKEND_PRIV_H
DECL|macro|_AGP_BACKEND_PRIV_H
mdefine_line|#define _AGP_BACKEND_PRIV_H 1
macro_line|#include &lt;asm/agp.h&gt;&t;/* for flush_agp_cache() */
DECL|macro|PFX
mdefine_line|#define PFX &quot;agpgart: &quot;
singleline_comment|//#define AGP_DEBUG 1
macro_line|#ifdef AGP_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x,y...) printk (KERN_DEBUG PFX &quot;%s: &quot; x &quot;&bslash;n&quot;, __FUNCTION__ , ## y)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x,y...) do { } while (0)
macro_line|#endif
r_extern
r_struct
id|agp_bridge_data
op_star
id|agp_bridge
suffix:semicolon
DECL|enum|aper_size_type
r_enum
id|aper_size_type
(brace
DECL|enumerator|U8_APER_SIZE
id|U8_APER_SIZE
comma
DECL|enumerator|U16_APER_SIZE
id|U16_APER_SIZE
comma
DECL|enumerator|U32_APER_SIZE
id|U32_APER_SIZE
comma
DECL|enumerator|LVL2_APER_SIZE
id|LVL2_APER_SIZE
comma
DECL|enumerator|FIXED_APER_SIZE
id|FIXED_APER_SIZE
)brace
suffix:semicolon
DECL|struct|gatt_mask
r_struct
id|gatt_mask
(brace
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* totally device specific, for integrated chipsets that &n;&t; * might have different types of memory masks.  For other&n;&t; * devices this will probably be ignored */
)brace
suffix:semicolon
DECL|struct|aper_size_info_8
r_struct
id|aper_size_info_8
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|page_order
r_int
id|page_order
suffix:semicolon
DECL|member|size_value
id|u8
id|size_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aper_size_info_16
r_struct
id|aper_size_info_16
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|page_order
r_int
id|page_order
suffix:semicolon
DECL|member|size_value
id|u16
id|size_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aper_size_info_32
r_struct
id|aper_size_info_32
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|page_order
r_int
id|page_order
suffix:semicolon
DECL|member|size_value
id|u32
id|size_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aper_size_info_lvl2
r_struct
id|aper_size_info_lvl2
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|size_value
id|u32
id|size_value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aper_size_info_fixed
r_struct
id|aper_size_info_fixed
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|page_order
r_int
id|page_order
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|agp_bridge_driver
r_struct
id|agp_bridge_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|aperture_sizes
r_void
op_star
id|aperture_sizes
suffix:semicolon
DECL|member|num_aperture_sizes
r_int
id|num_aperture_sizes
suffix:semicolon
DECL|member|size_type
r_enum
id|aper_size_type
id|size_type
suffix:semicolon
DECL|member|cant_use_aperture
r_int
id|cant_use_aperture
suffix:semicolon
DECL|member|needs_scratch_page
r_int
id|needs_scratch_page
suffix:semicolon
DECL|member|masks
r_struct
id|gatt_mask
op_star
id|masks
suffix:semicolon
DECL|member|fetch_size
r_int
(paren
op_star
id|fetch_size
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|configure
r_int
(paren
op_star
id|configure
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|agp_enable
r_void
(paren
op_star
id|agp_enable
)paren
(paren
id|u32
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|tlb_flush
r_void
(paren
op_star
id|tlb_flush
)paren
(paren
r_struct
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|mask_memory
r_int
r_int
(paren
op_star
id|mask_memory
)paren
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|cache_flush
r_void
(paren
op_star
id|cache_flush
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|create_gatt_table
r_int
(paren
op_star
id|create_gatt_table
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|free_gatt_table
r_int
(paren
op_star
id|free_gatt_table
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|insert_memory
r_int
(paren
op_star
id|insert_memory
)paren
(paren
r_struct
id|agp_memory
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|member|remove_memory
r_int
(paren
op_star
id|remove_memory
)paren
(paren
r_struct
id|agp_memory
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|member|alloc_by_type
r_struct
id|agp_memory
op_star
(paren
op_star
id|alloc_by_type
)paren
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|free_by_type
r_void
(paren
op_star
id|free_by_type
)paren
(paren
r_struct
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|agp_alloc_page
r_void
op_star
(paren
op_star
id|agp_alloc_page
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|agp_destroy_page
r_void
(paren
op_star
id|agp_destroy_page
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|agp_bridge_data
r_struct
id|agp_bridge_data
(brace
DECL|member|version
r_struct
id|agp_version
op_star
id|version
suffix:semicolon
DECL|member|driver
r_struct
id|agp_bridge_driver
op_star
id|driver
suffix:semicolon
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
DECL|member|previous_size
r_void
op_star
id|previous_size
suffix:semicolon
DECL|member|current_size
r_void
op_star
id|current_size
suffix:semicolon
DECL|member|dev_private_data
r_void
op_star
id|dev_private_data
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|gatt_table
id|u32
op_star
id|gatt_table
suffix:semicolon
DECL|member|gatt_table_real
id|u32
op_star
id|gatt_table_real
suffix:semicolon
DECL|member|scratch_page
r_int
r_int
id|scratch_page
suffix:semicolon
DECL|member|scratch_page_real
r_int
r_int
id|scratch_page_real
suffix:semicolon
DECL|member|gart_bus_addr
r_int
r_int
id|gart_bus_addr
suffix:semicolon
DECL|member|gatt_bus_addr
r_int
r_int
id|gatt_bus_addr
suffix:semicolon
DECL|member|mode
id|u32
id|mode
suffix:semicolon
DECL|member|type
r_enum
id|chipset_type
id|type
suffix:semicolon
DECL|member|key_list
r_int
r_int
op_star
id|key_list
suffix:semicolon
DECL|member|current_memory_agp
id|atomic_t
id|current_memory_agp
suffix:semicolon
DECL|member|agp_in_use
id|atomic_t
id|agp_in_use
suffix:semicolon
DECL|member|max_memory_agp
r_int
id|max_memory_agp
suffix:semicolon
multiline_comment|/* in number of pages */
DECL|member|aperture_size_idx
r_int
id|aperture_size_idx
suffix:semicolon
DECL|member|capndx
r_int
id|capndx
suffix:semicolon
DECL|member|major_version
r_char
id|major_version
suffix:semicolon
DECL|member|minor_version
r_char
id|minor_version
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OUTREG64
mdefine_line|#define OUTREG64(mmap, addr, val)&t;__raw_writeq((val), (mmap)+(addr))
DECL|macro|OUTREG32
mdefine_line|#define OUTREG32(mmap, addr, val)&t;__raw_writel((val), (mmap)+(addr))
DECL|macro|OUTREG16
mdefine_line|#define OUTREG16(mmap, addr, val)&t;__raw_writew((val), (mmap)+(addr))
DECL|macro|OUTREG8
mdefine_line|#define OUTREG8(mmap, addr, val)&t;__raw_writeb((val), (mmap)+(addr))
DECL|macro|INREG64
mdefine_line|#define INREG64(mmap, addr)&t;&t;__raw_readq((mmap)+(addr))
DECL|macro|INREG32
mdefine_line|#define INREG32(mmap, addr)&t;&t;__raw_readl((mmap)+(addr))
DECL|macro|INREG16
mdefine_line|#define INREG16(mmap, addr)&t;&t;__raw_readw((mmap)+(addr))
DECL|macro|INREG8
mdefine_line|#define INREG8(mmap, addr)&t;&t;__raw_readb((mmap)+(addr))
DECL|macro|KB
mdefine_line|#define KB(x)&t;((x) * 1024)
DECL|macro|MB
mdefine_line|#define MB(x)&t;(KB (KB (x)))
DECL|macro|GB
mdefine_line|#define GB(x)&t;(MB (KB (x)))
DECL|macro|A_SIZE_8
mdefine_line|#define A_SIZE_8(x)&t;((struct aper_size_info_8 *) x)
DECL|macro|A_SIZE_16
mdefine_line|#define A_SIZE_16(x)&t;((struct aper_size_info_16 *) x)
DECL|macro|A_SIZE_32
mdefine_line|#define A_SIZE_32(x)&t;((struct aper_size_info_32 *) x)
DECL|macro|A_SIZE_LVL2
mdefine_line|#define A_SIZE_LVL2(x)&t;((struct aper_size_info_lvl2 *) x)
DECL|macro|A_SIZE_FIX
mdefine_line|#define A_SIZE_FIX(x)&t;((struct aper_size_info_fixed *) x)
DECL|macro|A_IDX8
mdefine_line|#define A_IDX8(bridge)&t;(A_SIZE_8((bridge)-&gt;driver-&gt;aperture_sizes) + i)
DECL|macro|A_IDX16
mdefine_line|#define A_IDX16(bridge)&t;(A_SIZE_16((bridge)-&gt;driver-&gt;aperture_sizes) + i)
DECL|macro|A_IDX32
mdefine_line|#define A_IDX32(bridge)&t;(A_SIZE_32((bridge)-&gt;driver-&gt;aperture_sizes) + i)
DECL|macro|MAXKEY
mdefine_line|#define MAXKEY&t;&t;(4096 * 32)
DECL|macro|PGE_EMPTY
mdefine_line|#define PGE_EMPTY(b, p)&t;(!(p) || (p) == (unsigned long) (b)-&gt;scratch_page)
multiline_comment|/* Chipset independant registers (from AGP Spec) */
DECL|macro|AGP_APBASE
mdefine_line|#define AGP_APBASE&t;0x10
multiline_comment|/* Intel registers */
DECL|macro|INTEL_APSIZE
mdefine_line|#define INTEL_APSIZE&t;0xb4
DECL|macro|INTEL_ATTBASE
mdefine_line|#define INTEL_ATTBASE&t;0xb8
DECL|macro|INTEL_AGPCTRL
mdefine_line|#define INTEL_AGPCTRL&t;0xb0
DECL|macro|INTEL_NBXCFG
mdefine_line|#define INTEL_NBXCFG&t;0x50
DECL|macro|INTEL_ERRSTS
mdefine_line|#define INTEL_ERRSTS&t;0x91
multiline_comment|/* Intel 460GX Registers */
DECL|macro|INTEL_I460_BAPBASE
mdefine_line|#define INTEL_I460_BAPBASE&t;&t;0x98
DECL|macro|INTEL_I460_GXBCTL
mdefine_line|#define INTEL_I460_GXBCTL&t;&t;0xa0
DECL|macro|INTEL_I460_AGPSIZ
mdefine_line|#define INTEL_I460_AGPSIZ&t;&t;0xa2
DECL|macro|INTEL_I460_ATTBASE
mdefine_line|#define INTEL_I460_ATTBASE&t;&t;0xfe200000
DECL|macro|INTEL_I460_GATT_VALID
mdefine_line|#define INTEL_I460_GATT_VALID&t;&t;(1UL &lt;&lt; 24)
DECL|macro|INTEL_I460_GATT_COHERENT
mdefine_line|#define INTEL_I460_GATT_COHERENT&t;(1UL &lt;&lt; 25)
multiline_comment|/* Intel i830 registers */
DECL|macro|I830_GMCH_CTRL
mdefine_line|#define I830_GMCH_CTRL&t;&t;&t;0x52
DECL|macro|I830_GMCH_ENABLED
mdefine_line|#define I830_GMCH_ENABLED&t;&t;0x4
DECL|macro|I830_GMCH_MEM_MASK
mdefine_line|#define I830_GMCH_MEM_MASK&t;&t;0x1
DECL|macro|I830_GMCH_MEM_64M
mdefine_line|#define I830_GMCH_MEM_64M&t;&t;0x1
DECL|macro|I830_GMCH_MEM_128M
mdefine_line|#define I830_GMCH_MEM_128M&t;&t;0
DECL|macro|I830_GMCH_GMS_MASK
mdefine_line|#define I830_GMCH_GMS_MASK&t;&t;0x70
DECL|macro|I830_GMCH_GMS_DISABLED
mdefine_line|#define I830_GMCH_GMS_DISABLED&t;&t;0x00
DECL|macro|I830_GMCH_GMS_LOCAL
mdefine_line|#define I830_GMCH_GMS_LOCAL&t;&t;0x10
DECL|macro|I830_GMCH_GMS_STOLEN_512
mdefine_line|#define I830_GMCH_GMS_STOLEN_512&t;0x20
DECL|macro|I830_GMCH_GMS_STOLEN_1024
mdefine_line|#define I830_GMCH_GMS_STOLEN_1024&t;0x30
DECL|macro|I830_GMCH_GMS_STOLEN_8192
mdefine_line|#define I830_GMCH_GMS_STOLEN_8192&t;0x40
DECL|macro|I830_RDRAM_CHANNEL_TYPE
mdefine_line|#define I830_RDRAM_CHANNEL_TYPE&t;&t;0x03010
DECL|macro|I830_RDRAM_ND
mdefine_line|#define I830_RDRAM_ND(x)&t;&t;(((x) &amp; 0x20) &gt;&gt; 5)
DECL|macro|I830_RDRAM_DDT
mdefine_line|#define I830_RDRAM_DDT(x)&t;&t;(((x) &amp; 0x18) &gt;&gt; 3)
multiline_comment|/* This one is for I830MP w. an external graphic card */
DECL|macro|INTEL_I830_ERRSTS
mdefine_line|#define INTEL_I830_ERRSTS&t;0x92
multiline_comment|/* Intel 855GM/852GM registers */
DECL|macro|I855_GMCH_GMS_STOLEN_0M
mdefine_line|#define I855_GMCH_GMS_STOLEN_0M&t;&t;0x0
DECL|macro|I855_GMCH_GMS_STOLEN_1M
mdefine_line|#define I855_GMCH_GMS_STOLEN_1M&t;&t;(0x1 &lt;&lt; 4)
DECL|macro|I855_GMCH_GMS_STOLEN_4M
mdefine_line|#define I855_GMCH_GMS_STOLEN_4M&t;&t;(0x2 &lt;&lt; 4)
DECL|macro|I855_GMCH_GMS_STOLEN_8M
mdefine_line|#define I855_GMCH_GMS_STOLEN_8M&t;&t;(0x3 &lt;&lt; 4)
DECL|macro|I855_GMCH_GMS_STOLEN_16M
mdefine_line|#define I855_GMCH_GMS_STOLEN_16M&t;(0x4 &lt;&lt; 4)
DECL|macro|I855_GMCH_GMS_STOLEN_32M
mdefine_line|#define I855_GMCH_GMS_STOLEN_32M&t;(0x5 &lt;&lt; 4)
DECL|macro|I85X_CAPID
mdefine_line|#define I85X_CAPID&t;&t;&t;0x44
DECL|macro|I85X_VARIANT_MASK
mdefine_line|#define I85X_VARIANT_MASK&t;&t;0x7
DECL|macro|I85X_VARIANT_SHIFT
mdefine_line|#define I85X_VARIANT_SHIFT&t;&t;5
DECL|macro|I855_GME
mdefine_line|#define I855_GME&t;&t;&t;0x0
DECL|macro|I855_GM
mdefine_line|#define I855_GM&t;&t;&t;&t;0x4
DECL|macro|I852_GME
mdefine_line|#define I852_GME&t;&t;&t;0x2
DECL|macro|I852_GM
mdefine_line|#define I852_GM&t;&t;&t;&t;0x5
multiline_comment|/* Intel 815 register */
DECL|macro|INTEL_815_APCONT
mdefine_line|#define INTEL_815_APCONT&t;0x51
DECL|macro|INTEL_815_ATTBASE_MASK
mdefine_line|#define INTEL_815_ATTBASE_MASK&t;~0x1FFFFFFF
multiline_comment|/* Intel i820 registers */
DECL|macro|INTEL_I820_RDCR
mdefine_line|#define INTEL_I820_RDCR&t;&t;0x51
DECL|macro|INTEL_I820_ERRSTS
mdefine_line|#define INTEL_I820_ERRSTS&t;0xc8
multiline_comment|/* Intel i840 registers */
DECL|macro|INTEL_I840_MCHCFG
mdefine_line|#define INTEL_I840_MCHCFG&t;0x50
DECL|macro|INTEL_I840_ERRSTS
mdefine_line|#define INTEL_I840_ERRSTS&t;0xc8
multiline_comment|/* Intel i845 registers */
DECL|macro|INTEL_I845_AGPM
mdefine_line|#define INTEL_I845_AGPM&t;&t;0x51
DECL|macro|INTEL_I845_ERRSTS
mdefine_line|#define INTEL_I845_ERRSTS&t;0xc8
multiline_comment|/* Intel i850 registers */
DECL|macro|INTEL_I850_MCHCFG
mdefine_line|#define INTEL_I850_MCHCFG&t;0x50
DECL|macro|INTEL_I850_ERRSTS
mdefine_line|#define INTEL_I850_ERRSTS&t;0xc8
multiline_comment|/* Intel i860 registers */
DECL|macro|INTEL_I860_MCHCFG
mdefine_line|#define INTEL_I860_MCHCFG&t;0x50
DECL|macro|INTEL_I860_ERRSTS
mdefine_line|#define INTEL_I860_ERRSTS&t;0xc8
multiline_comment|/* Intel i810 registers */
DECL|macro|I810_GMADDR
mdefine_line|#define I810_GMADDR&t;&t;0x10
DECL|macro|I810_MMADDR
mdefine_line|#define I810_MMADDR&t;&t;0x14
DECL|macro|I810_PTE_BASE
mdefine_line|#define I810_PTE_BASE&t;&t;0x10000
DECL|macro|I810_PTE_MAIN_UNCACHED
mdefine_line|#define I810_PTE_MAIN_UNCACHED&t;0x00000000
DECL|macro|I810_PTE_LOCAL
mdefine_line|#define I810_PTE_LOCAL&t;&t;0x00000002
DECL|macro|I810_PTE_VALID
mdefine_line|#define I810_PTE_VALID&t;&t;0x00000001
DECL|macro|I810_SMRAM_MISCC
mdefine_line|#define I810_SMRAM_MISCC&t;0x70
DECL|macro|I810_GFX_MEM_WIN_SIZE
mdefine_line|#define I810_GFX_MEM_WIN_SIZE&t;0x00010000
DECL|macro|I810_GFX_MEM_WIN_32M
mdefine_line|#define I810_GFX_MEM_WIN_32M&t;0x00010000
DECL|macro|I810_GMS
mdefine_line|#define I810_GMS&t;&t;0x000000c0
DECL|macro|I810_GMS_DISABLE
mdefine_line|#define I810_GMS_DISABLE&t;0x00000000
DECL|macro|I810_PGETBL_CTL
mdefine_line|#define I810_PGETBL_CTL&t;&t;0x2020
DECL|macro|I810_PGETBL_ENABLED
mdefine_line|#define I810_PGETBL_ENABLED&t;0x00000001
DECL|macro|I810_DRAM_CTL
mdefine_line|#define I810_DRAM_CTL&t;&t;0x3000
DECL|macro|I810_DRAM_ROW_0
mdefine_line|#define I810_DRAM_ROW_0&t;&t;0x00000001
DECL|macro|I810_DRAM_ROW_0_SDRAM
mdefine_line|#define I810_DRAM_ROW_0_SDRAM&t;0x00000001
multiline_comment|/* Intel 7505 registers */
DECL|macro|INTEL_I7505_APSIZE
mdefine_line|#define INTEL_I7505_APSIZE&t;0x74
DECL|macro|INTEL_I7505_NCAPID
mdefine_line|#define INTEL_I7505_NCAPID&t;0x60
DECL|macro|INTEL_I7505_NISTAT
mdefine_line|#define INTEL_I7505_NISTAT&t;0x6c
DECL|macro|INTEL_I7505_ATTBASE
mdefine_line|#define INTEL_I7505_ATTBASE&t;0x78
DECL|macro|INTEL_I7505_ERRSTS
mdefine_line|#define INTEL_I7505_ERRSTS&t;0x42
DECL|macro|INTEL_I7505_AGPCTRL
mdefine_line|#define INTEL_I7505_AGPCTRL&t;0x70
DECL|macro|INTEL_I7505_MCHCFG
mdefine_line|#define INTEL_I7505_MCHCFG&t;0x50
multiline_comment|/* VIA register */
DECL|macro|VIA_GARTCTRL
mdefine_line|#define VIA_GARTCTRL&t;0x80
DECL|macro|VIA_APSIZE
mdefine_line|#define VIA_APSIZE&t;0x84
DECL|macro|VIA_ATTBASE
mdefine_line|#define VIA_ATTBASE&t;0x88
multiline_comment|/* VIA KT400 */
DECL|macro|VIA_AGP3_GARTCTRL
mdefine_line|#define VIA_AGP3_GARTCTRL&t;0x90
DECL|macro|VIA_AGP3_APSIZE
mdefine_line|#define VIA_AGP3_APSIZE&t;&t;0x94
DECL|macro|VIA_AGP3_ATTBASE
mdefine_line|#define VIA_AGP3_ATTBASE&t;0x98
DECL|macro|VIA_AGPSEL
mdefine_line|#define VIA_AGPSEL&t;&t;0xfd
multiline_comment|/* SiS registers */
DECL|macro|SIS_ATTBASE
mdefine_line|#define SIS_ATTBASE&t;0x90
DECL|macro|SIS_APSIZE
mdefine_line|#define SIS_APSIZE&t;0x94
DECL|macro|SIS_TLBCNTRL
mdefine_line|#define SIS_TLBCNTRL&t;0x97
DECL|macro|SIS_TLBFLUSH
mdefine_line|#define SIS_TLBFLUSH&t;0x98
multiline_comment|/* AMD registers */
DECL|macro|AMD_MMBASE
mdefine_line|#define AMD_MMBASE&t;0x14
DECL|macro|AMD_APSIZE
mdefine_line|#define AMD_APSIZE&t;0xac
DECL|macro|AMD_MODECNTL
mdefine_line|#define AMD_MODECNTL&t;0xb0
DECL|macro|AMD_MODECNTL2
mdefine_line|#define AMD_MODECNTL2&t;0xb2
DECL|macro|AMD_GARTENABLE
mdefine_line|#define AMD_GARTENABLE&t;0x02&t;/* In mmio region (16-bit register) */
DECL|macro|AMD_ATTBASE
mdefine_line|#define AMD_ATTBASE&t;0x04&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_TLBFLUSH
mdefine_line|#define AMD_TLBFLUSH&t;0x0c&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_CACHEENTRY
mdefine_line|#define AMD_CACHEENTRY&t;0x10&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_X86_64_GARTAPERTURECTL
mdefine_line|#define AMD_X86_64_GARTAPERTURECTL&t;0x90
DECL|macro|AMD_X86_64_GARTAPERTUREBASE
mdefine_line|#define AMD_X86_64_GARTAPERTUREBASE&t;0x94
DECL|macro|AMD_X86_64_GARTTABLEBASE
mdefine_line|#define AMD_X86_64_GARTTABLEBASE&t;0x98
DECL|macro|AMD_X86_64_GARTCACHECTL
mdefine_line|#define AMD_X86_64_GARTCACHECTL&t;&t;0x9c
DECL|macro|AMD_X86_64_GARTEN
mdefine_line|#define AMD_X86_64_GARTEN&t;&t;1&lt;&lt;0
multiline_comment|/* ALi registers */
DECL|macro|ALI_AGPCTRL
mdefine_line|#define ALI_AGPCTRL&t;&t;&t;0xb8
DECL|macro|ALI_ATTBASE
mdefine_line|#define ALI_ATTBASE&t;&t;&t;0xbc
DECL|macro|ALI_TLBCTRL
mdefine_line|#define ALI_TLBCTRL&t;&t;&t;0xc0
DECL|macro|ALI_TAGCTRL
mdefine_line|#define ALI_TAGCTRL&t;&t;&t;0xc4
DECL|macro|ALI_CACHE_FLUSH_CTRL
mdefine_line|#define ALI_CACHE_FLUSH_CTRL&t;&t;0xD0
DECL|macro|ALI_CACHE_FLUSH_ADDR_MASK
mdefine_line|#define ALI_CACHE_FLUSH_ADDR_MASK&t;0xFFFFF000
DECL|macro|ALI_CACHE_FLUSH_EN
mdefine_line|#define ALI_CACHE_FLUSH_EN&t;&t;0x100
multiline_comment|/* ATI register */
DECL|macro|ATI_GART_MMBASE_ADDR
mdefine_line|#define ATI_GART_MMBASE_ADDR&t;0x14
DECL|macro|ATI_RS100_APSIZE
mdefine_line|#define ATI_RS100_APSIZE&t;0xac
DECL|macro|ATI_RS300_APSIZE
mdefine_line|#define ATI_RS300_APSIZE&t;0xf8
DECL|macro|ATI_RS100_IG_AGPMODE
mdefine_line|#define ATI_RS100_IG_AGPMODE&t;0xb0
DECL|macro|ATI_RS300_IG_AGPMODE
mdefine_line|#define ATI_RS300_IG_AGPMODE&t;0xfc
DECL|macro|ATI_GART_FEATURE_ID
mdefine_line|#define ATI_GART_FEATURE_ID&t;&t;0x00
DECL|macro|ATI_GART_BASE
mdefine_line|#define ATI_GART_BASE&t;&t;&t;0x04
DECL|macro|ATI_GART_CACHE_SZBASE
mdefine_line|#define ATI_GART_CACHE_SZBASE&t;&t;0x08
DECL|macro|ATI_GART_CACHE_CNTRL
mdefine_line|#define ATI_GART_CACHE_CNTRL&t;&t;0x0c
DECL|macro|ATI_GART_CACHE_ENTRY_CNTRL
mdefine_line|#define ATI_GART_CACHE_ENTRY_CNTRL&t;0x10
multiline_comment|/* Serverworks Registers */
DECL|macro|SVWRKS_APSIZE
mdefine_line|#define SVWRKS_APSIZE&t;&t;0x10
DECL|macro|SVWRKS_SIZE_MASK
mdefine_line|#define SVWRKS_SIZE_MASK&t;0xfe000000
DECL|macro|SVWRKS_MMBASE
mdefine_line|#define SVWRKS_MMBASE&t;&t;0x14
DECL|macro|SVWRKS_CACHING
mdefine_line|#define SVWRKS_CACHING&t;&t;0x4b
DECL|macro|SVWRKS_FEATURE
mdefine_line|#define SVWRKS_FEATURE&t;&t;0x68
multiline_comment|/* func 1 registers */
DECL|macro|SVWRKS_AGP_ENABLE
mdefine_line|#define SVWRKS_AGP_ENABLE&t;0x60
DECL|macro|SVWRKS_COMMAND
mdefine_line|#define SVWRKS_COMMAND&t;&t;0x04
multiline_comment|/* Memory mapped registers */
DECL|macro|SVWRKS_GART_CACHE
mdefine_line|#define SVWRKS_GART_CACHE&t;0x02
DECL|macro|SVWRKS_GATTBASE
mdefine_line|#define SVWRKS_GATTBASE&t;&t;0x04
DECL|macro|SVWRKS_TLBFLUSH
mdefine_line|#define SVWRKS_TLBFLUSH&t;&t;0x10
DECL|macro|SVWRKS_POSTFLUSH
mdefine_line|#define SVWRKS_POSTFLUSH&t;0x14
DECL|macro|SVWRKS_DIRFLUSH
mdefine_line|#define SVWRKS_DIRFLUSH&t;&t;0x0c
multiline_comment|/* HP ZX1 SBA registers */
DECL|macro|HP_ZX1_CTRL
mdefine_line|#define HP_ZX1_CTRL&t;&t;0x200
DECL|macro|HP_ZX1_IBASE
mdefine_line|#define HP_ZX1_IBASE&t;&t;0x300
DECL|macro|HP_ZX1_IMASK
mdefine_line|#define HP_ZX1_IMASK&t;&t;0x308
DECL|macro|HP_ZX1_PCOM
mdefine_line|#define HP_ZX1_PCOM&t;&t;0x310
DECL|macro|HP_ZX1_TCNFG
mdefine_line|#define HP_ZX1_TCNFG&t;&t;0x318
DECL|macro|HP_ZX1_PDIR_BASE
mdefine_line|#define HP_ZX1_PDIR_BASE&t;0x320
DECL|macro|HP_ZX1_CACHE_FLUSH
mdefine_line|#define HP_ZX1_CACHE_FLUSH&t;0x428
multiline_comment|/* NVIDIA registers */
DECL|macro|NVIDIA_0_APSIZE
mdefine_line|#define NVIDIA_0_APSIZE&t;&t;0x80
DECL|macro|NVIDIA_1_WBC
mdefine_line|#define NVIDIA_1_WBC&t;&t;0xf0
DECL|macro|NVIDIA_2_GARTCTRL
mdefine_line|#define NVIDIA_2_GARTCTRL&t;0xd0
DECL|macro|NVIDIA_2_APBASE
mdefine_line|#define NVIDIA_2_APBASE&t;&t;0xd8
DECL|macro|NVIDIA_2_APLIMIT
mdefine_line|#define NVIDIA_2_APLIMIT&t;0xdc
DECL|macro|NVIDIA_2_ATTBASE
mdefine_line|#define NVIDIA_2_ATTBASE(i)&t;(0xe0 + (i) * 4)
DECL|macro|NVIDIA_3_APBASE
mdefine_line|#define NVIDIA_3_APBASE&t;&t;0x50
DECL|macro|NVIDIA_3_APLIMIT
mdefine_line|#define NVIDIA_3_APLIMIT&t;0x54
DECL|struct|agp_device_ids
r_struct
id|agp_device_ids
(brace
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
multiline_comment|/* first, to make table easier to read */
DECL|member|chipset
r_enum
id|chipset_type
id|chipset
suffix:semicolon
DECL|member|chipset_name
r_const
r_char
op_star
id|chipset_name
suffix:semicolon
DECL|member|chipset_setup
r_int
(paren
op_star
id|chipset_setup
)paren
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* used to override generic */
)brace
suffix:semicolon
multiline_comment|/* Driver registration */
r_struct
id|agp_bridge_data
op_star
id|agp_alloc_bridge
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|agp_put_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
suffix:semicolon
r_int
id|agp_add_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
suffix:semicolon
r_void
id|agp_remove_bridge
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
suffix:semicolon
multiline_comment|/* Frontend routines. */
r_int
id|agp_frontend_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|agp_frontend_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Generic routines. */
r_void
id|agp_generic_enable
c_func
(paren
id|u32
id|mode
)paren
suffix:semicolon
r_int
id|agp_generic_create_gatt_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|agp_generic_free_gatt_table
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|agp_memory
op_star
id|agp_create_memory
c_func
(paren
r_int
id|scratch_pages
)paren
suffix:semicolon
r_int
id|agp_generic_insert_memory
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
comma
id|off_t
id|pg_start
comma
r_int
id|type
)paren
suffix:semicolon
r_int
id|agp_generic_remove_memory
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
comma
id|off_t
id|pg_start
comma
r_int
id|type
)paren
suffix:semicolon
r_struct
id|agp_memory
op_star
id|agp_generic_alloc_by_type
c_func
(paren
r_int
id|page_count
comma
r_int
id|type
)paren
suffix:semicolon
r_void
id|agp_generic_free_by_type
c_func
(paren
r_struct
id|agp_memory
op_star
id|curr
)paren
suffix:semicolon
r_void
op_star
id|agp_generic_alloc_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|agp_generic_destroy_page
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_void
id|agp_free_key
c_func
(paren
r_int
id|key
)paren
suffix:semicolon
r_int
id|agp_num_entries
c_func
(paren
r_void
)paren
suffix:semicolon
id|u32
id|agp_collect_device_status
c_func
(paren
id|u32
id|mode
comma
id|u32
id|command
)paren
suffix:semicolon
r_void
id|agp_device_command
c_func
(paren
id|u32
id|command
comma
r_int
id|agp_v3
)paren
suffix:semicolon
r_int
id|agp_3_5_enable
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
suffix:semicolon
r_void
id|global_cache_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|get_agp_version
c_func
(paren
r_struct
id|agp_bridge_data
op_star
id|bridge
)paren
suffix:semicolon
r_int
r_int
id|agp_generic_mask_memory
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|agp_off
suffix:semicolon
r_extern
r_int
id|agp_try_unsupported_boot
suffix:semicolon
multiline_comment|/* Standard agp registers */
DECL|macro|AGPSTAT
mdefine_line|#define AGPSTAT&t;&t;&t;0x4
DECL|macro|AGPCMD
mdefine_line|#define AGPCMD&t;&t;&t;0x8
DECL|macro|AGPNISTAT
mdefine_line|#define AGPNISTAT&t;&t;0xc
DECL|macro|AGPCTRL
mdefine_line|#define AGPCTRL                 0x10
DECL|macro|AGPNEPG
mdefine_line|#define AGPNEPG&t;&t;&t;0x16
DECL|macro|AGPNICMD
mdefine_line|#define AGPNICMD&t;&t;0x20
DECL|macro|AGP_MAJOR_VERSION_SHIFT
mdefine_line|#define AGP_MAJOR_VERSION_SHIFT&t;(20)
DECL|macro|AGP_MINOR_VERSION_SHIFT
mdefine_line|#define AGP_MINOR_VERSION_SHIFT&t;(16)
DECL|macro|AGPSTAT_RQ_DEPTH
mdefine_line|#define AGPSTAT_RQ_DEPTH&t;(0xff000000)
DECL|macro|AGPSTAT_CAL_MASK
mdefine_line|#define AGPSTAT_CAL_MASK&t;(1&lt;&lt;12|1&lt;&lt;11|1&lt;&lt;10)
DECL|macro|AGPSTAT_ARQSZ
mdefine_line|#define AGPSTAT_ARQSZ&t;&t;(1&lt;&lt;15|1&lt;&lt;14|1&lt;&lt;13)
DECL|macro|AGPSTAT_ARQSZ_SHIFT
mdefine_line|#define AGPSTAT_ARQSZ_SHIFT&t;13
DECL|macro|AGPSTAT_SBA
mdefine_line|#define AGPSTAT_SBA&t;&t;(1&lt;&lt;9)
DECL|macro|AGPSTAT_AGP_ENABLE
mdefine_line|#define AGPSTAT_AGP_ENABLE&t;(1&lt;&lt;8)
DECL|macro|AGPSTAT_FW
mdefine_line|#define AGPSTAT_FW&t;&t;(1&lt;&lt;4)
DECL|macro|AGPSTAT_MODE_3_0
mdefine_line|#define AGPSTAT_MODE_3_0&t;(1&lt;&lt;3)
DECL|macro|AGPSTAT2_1X
mdefine_line|#define AGPSTAT2_1X&t;&t;(1&lt;&lt;0)
DECL|macro|AGPSTAT2_2X
mdefine_line|#define AGPSTAT2_2X&t;&t;(1&lt;&lt;1)
DECL|macro|AGPSTAT2_4X
mdefine_line|#define AGPSTAT2_4X&t;&t;(1&lt;&lt;2)
DECL|macro|AGPSTAT3_RSVD
mdefine_line|#define AGPSTAT3_RSVD&t;&t;(1&lt;&lt;2)
DECL|macro|AGPSTAT3_8X
mdefine_line|#define AGPSTAT3_8X&t;&t;(1&lt;&lt;1)
DECL|macro|AGPSTAT3_4X
mdefine_line|#define AGPSTAT3_4X&t;&t;(1)
macro_line|#endif&t;&t;&t;&t;/* _AGP_BACKEND_PRIV_H */
eof
