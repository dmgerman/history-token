multiline_comment|/*&n; * AGPGART module version 0.99&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#ifndef _AGP_BACKEND_PRIV_H
DECL|macro|_AGP_BACKEND_PRIV_H
mdefine_line|#define _AGP_BACKEND_PRIV_H 1
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
DECL|struct|_gatt_mask
r_typedef
r_struct
id|_gatt_mask
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
DECL|typedef|gatt_mask
)brace
id|gatt_mask
suffix:semicolon
DECL|struct|_aper_size_info_8
r_typedef
r_struct
id|_aper_size_info_8
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
DECL|typedef|aper_size_info_8
)brace
id|aper_size_info_8
suffix:semicolon
DECL|struct|_aper_size_info_16
r_typedef
r_struct
id|_aper_size_info_16
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
DECL|typedef|aper_size_info_16
)brace
id|aper_size_info_16
suffix:semicolon
DECL|struct|_aper_size_info_32
r_typedef
r_struct
id|_aper_size_info_32
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
DECL|typedef|aper_size_info_32
)brace
id|aper_size_info_32
suffix:semicolon
DECL|struct|_aper_size_info_lvl2
r_typedef
r_struct
id|_aper_size_info_lvl2
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
DECL|typedef|aper_size_info_lvl2
)brace
id|aper_size_info_lvl2
suffix:semicolon
DECL|struct|_aper_size_info_fixed
r_typedef
r_struct
id|_aper_size_info_fixed
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
DECL|typedef|aper_size_info_fixed
)brace
id|aper_size_info_fixed
suffix:semicolon
DECL|struct|agp_bridge_data
r_struct
id|agp_bridge_data
(brace
DECL|member|version
id|agp_version
op_star
id|version
suffix:semicolon
DECL|member|aperture_sizes
r_void
op_star
id|aperture_sizes
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
DECL|member|masks
id|gatt_mask
op_star
id|masks
suffix:semicolon
DECL|member|gatt_table
r_int
r_int
op_star
id|gatt_table
suffix:semicolon
DECL|member|gatt_table_real
r_int
r_int
op_star
id|gatt_table_real
suffix:semicolon
DECL|member|scratch_page
r_int
r_int
id|scratch_page
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
DECL|member|size_type
r_enum
id|aper_size_type
id|size_type
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
DECL|member|needs_scratch_page
r_int
id|needs_scratch_page
suffix:semicolon
DECL|member|aperture_size_idx
r_int
id|aperture_size_idx
suffix:semicolon
DECL|member|num_aperture_sizes
r_int
id|num_aperture_sizes
suffix:semicolon
DECL|member|num_of_masks
r_int
id|num_of_masks
suffix:semicolon
DECL|member|capndx
r_int
id|capndx
suffix:semicolon
DECL|member|cant_use_aperture
r_int
id|cant_use_aperture
suffix:semicolon
multiline_comment|/* Links to driver specific functions */
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
id|agp_memory
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|member|alloc_by_type
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
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|agp_alloc_page
r_int
r_int
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
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OUTREG32
mdefine_line|#define OUTREG32(mmap, addr, val)   __raw_writel((val), (mmap)+(addr))
DECL|macro|OUTREG16
mdefine_line|#define OUTREG16(mmap, addr, val)   __raw_writew((val), (mmap)+(addr))
DECL|macro|OUTREG8
mdefine_line|#define OUTREG8(mmap, addr, val)   __raw_writeb((val), (mmap)+(addr))
DECL|macro|INREG32
mdefine_line|#define INREG32(mmap, addr)         __raw_readl((mmap)+(addr))
DECL|macro|INREG16
mdefine_line|#define INREG16(mmap, addr)         __raw_readw((mmap)+(addr))
DECL|macro|INREG8
mdefine_line|#define INREG8(mmap, addr)         __raw_readb((mmap)+(addr))
DECL|macro|CACHE_FLUSH
mdefine_line|#define CACHE_FLUSH&t;agp_bridge.cache_flush
DECL|macro|A_SIZE_8
mdefine_line|#define A_SIZE_8(x)&t;((aper_size_info_8 *) x)
DECL|macro|A_SIZE_16
mdefine_line|#define A_SIZE_16(x)&t;((aper_size_info_16 *) x)
DECL|macro|A_SIZE_32
mdefine_line|#define A_SIZE_32(x)&t;((aper_size_info_32 *) x)
DECL|macro|A_SIZE_LVL2
mdefine_line|#define A_SIZE_LVL2(x)  ((aper_size_info_lvl2 *) x)
DECL|macro|A_SIZE_FIX
mdefine_line|#define A_SIZE_FIX(x)&t;((aper_size_info_fixed *) x)
DECL|macro|A_IDX8
mdefine_line|#define A_IDX8()&t;(A_SIZE_8(agp_bridge.aperture_sizes) + i)
DECL|macro|A_IDX16
mdefine_line|#define A_IDX16()&t;(A_SIZE_16(agp_bridge.aperture_sizes) + i)
DECL|macro|A_IDX32
mdefine_line|#define A_IDX32()&t;(A_SIZE_32(agp_bridge.aperture_sizes) + i)
DECL|macro|A_IDXLVL2
mdefine_line|#define A_IDXLVL2()&t;(A_SIZE_LVL2(agp_bridge.aperture_sizes) + i)
DECL|macro|A_IDXFIX
mdefine_line|#define A_IDXFIX()&t;(A_SIZE_FIX(agp_bridge.aperture_sizes) + i)
DECL|macro|MAXKEY
mdefine_line|#define MAXKEY&t;&t;(4096 * 32)
DECL|macro|AGPGART_MODULE_NAME
mdefine_line|#define AGPGART_MODULE_NAME&t;&quot;agpgart&quot;
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&t;AGPGART_MODULE_NAME &quot;: &quot;
DECL|macro|PGE_EMPTY
mdefine_line|#define PGE_EMPTY(p) (!(p) || (p) == (unsigned long) agp_bridge.scratch_page)
macro_line|#ifndef PCI_DEVICE_ID_VIA_82C691_0
DECL|macro|PCI_DEVICE_ID_VIA_82C691_0
mdefine_line|#define PCI_DEVICE_ID_VIA_82C691_0      0x0691
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VIA_8371_0
DECL|macro|PCI_DEVICE_ID_VIA_8371_0
mdefine_line|#define PCI_DEVICE_ID_VIA_8371_0      0x0391
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VIA_8363_0
DECL|macro|PCI_DEVICE_ID_VIA_8363_0
mdefine_line|#define PCI_DEVICE_ID_VIA_8363_0      0x0305
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_0
DECL|macro|PCI_DEVICE_ID_INTEL_810_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_0       0x7120
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_840_0
DECL|macro|PCI_DEVICE_ID_INTEL_840_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_840_0&t;&t;0x1a21
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_850_0
DECL|macro|PCI_DEVICE_ID_INTEL_850_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_850_0     0x2530
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_DC100_0
DECL|macro|PCI_DEVICE_ID_INTEL_810_DC100_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_DC100_0 0x7122
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_E_0
DECL|macro|PCI_DEVICE_ID_INTEL_810_E_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_E_0     0x7124
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_82443GX_0
DECL|macro|PCI_DEVICE_ID_INTEL_82443GX_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82443GX_0   0x71a0
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_1
DECL|macro|PCI_DEVICE_ID_INTEL_810_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_1       0x7121
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_DC100_1
DECL|macro|PCI_DEVICE_ID_INTEL_810_DC100_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_DC100_1 0x7123
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_810_E_1
DECL|macro|PCI_DEVICE_ID_INTEL_810_E_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_810_E_1     0x7125
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_815_0
DECL|macro|PCI_DEVICE_ID_INTEL_815_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_815_0       0x1130
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_815_1
DECL|macro|PCI_DEVICE_ID_INTEL_815_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_815_1       0x1132
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_82443GX_1
DECL|macro|PCI_DEVICE_ID_INTEL_82443GX_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_82443GX_1   0x71a1
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AMD_IRONGATE_0
DECL|macro|PCI_DEVICE_ID_AMD_IRONGATE_0
mdefine_line|#define PCI_DEVICE_ID_AMD_IRONGATE_0    0x7006
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_AL
DECL|macro|PCI_VENDOR_ID_AL
mdefine_line|#define PCI_VENDOR_ID_AL&t;&t;0x10b9
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1541_0
DECL|macro|PCI_DEVICE_ID_AL_M1541_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1541_0&t;0x1541
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1621_0
DECL|macro|PCI_DEVICE_ID_AL_M1621_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1621_0&t;0x1621
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1631_0
DECL|macro|PCI_DEVICE_ID_AL_M1631_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1631_0&t;0x1631
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1632_0
DECL|macro|PCI_DEVICE_ID_AL_M1632_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1632_0&t;0x1632
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1641_0
DECL|macro|PCI_DEVICE_ID_AL_M1641_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1641_0&t;0x1641
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1647_0
DECL|macro|PCI_DEVICE_ID_AL_M1647_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1647_0&t;0x1647
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_AL_M1651_0
DECL|macro|PCI_DEVICE_ID_AL_M1651_0
mdefine_line|#define PCI_DEVICE_ID_AL_M1651_0&t;0x1651
macro_line|#endif
multiline_comment|/* intel register */
DECL|macro|INTEL_APBASE
mdefine_line|#define INTEL_APBASE    0x10
DECL|macro|INTEL_APSIZE
mdefine_line|#define INTEL_APSIZE    0xb4
DECL|macro|INTEL_ATTBASE
mdefine_line|#define INTEL_ATTBASE   0xb8
DECL|macro|INTEL_AGPCTRL
mdefine_line|#define INTEL_AGPCTRL   0xb0
DECL|macro|INTEL_NBXCFG
mdefine_line|#define INTEL_NBXCFG    0x50
DECL|macro|INTEL_ERRSTS
mdefine_line|#define INTEL_ERRSTS    0x91
multiline_comment|/* intel i840 registers */
DECL|macro|INTEL_I840_MCHCFG
mdefine_line|#define INTEL_I840_MCHCFG   0x50
DECL|macro|INTEL_I840_ERRSTS
mdefine_line|#define INTEL_I840_ERRSTS&t;0xc8
multiline_comment|/* intel i850 registers */
DECL|macro|INTEL_I850_MCHCFG
mdefine_line|#define INTEL_I850_MCHCFG   0x50
DECL|macro|INTEL_I850_ERRSTS
mdefine_line|#define INTEL_I850_ERRSTS   0xc8
multiline_comment|/* intel i810 registers */
DECL|macro|I810_GMADDR
mdefine_line|#define I810_GMADDR 0x10
DECL|macro|I810_MMADDR
mdefine_line|#define I810_MMADDR 0x14
DECL|macro|I810_PTE_BASE
mdefine_line|#define I810_PTE_BASE          0x10000
DECL|macro|I810_PTE_MAIN_UNCACHED
mdefine_line|#define I810_PTE_MAIN_UNCACHED 0x00000000
DECL|macro|I810_PTE_LOCAL
mdefine_line|#define I810_PTE_LOCAL         0x00000002
DECL|macro|I810_PTE_VALID
mdefine_line|#define I810_PTE_VALID         0x00000001
DECL|macro|I810_SMRAM_MISCC
mdefine_line|#define I810_SMRAM_MISCC       0x70
DECL|macro|I810_GFX_MEM_WIN_SIZE
mdefine_line|#define I810_GFX_MEM_WIN_SIZE  0x00010000
DECL|macro|I810_GFX_MEM_WIN_32M
mdefine_line|#define I810_GFX_MEM_WIN_32M   0x00010000
DECL|macro|I810_GMS
mdefine_line|#define I810_GMS               0x000000c0
DECL|macro|I810_GMS_DISABLE
mdefine_line|#define I810_GMS_DISABLE       0x00000000
DECL|macro|I810_PGETBL_CTL
mdefine_line|#define I810_PGETBL_CTL        0x2020
DECL|macro|I810_PGETBL_ENABLED
mdefine_line|#define I810_PGETBL_ENABLED    0x00000001
DECL|macro|I810_DRAM_CTL
mdefine_line|#define I810_DRAM_CTL          0x3000
DECL|macro|I810_DRAM_ROW_0
mdefine_line|#define I810_DRAM_ROW_0        0x00000001
DECL|macro|I810_DRAM_ROW_0_SDRAM
mdefine_line|#define I810_DRAM_ROW_0_SDRAM  0x00000001
multiline_comment|/* VIA register */
DECL|macro|VIA_APBASE
mdefine_line|#define VIA_APBASE      0x10
DECL|macro|VIA_GARTCTRL
mdefine_line|#define VIA_GARTCTRL    0x80
DECL|macro|VIA_APSIZE
mdefine_line|#define VIA_APSIZE      0x84
DECL|macro|VIA_ATTBASE
mdefine_line|#define VIA_ATTBASE     0x88
multiline_comment|/* SiS registers */
DECL|macro|SIS_APBASE
mdefine_line|#define SIS_APBASE      0x10
DECL|macro|SIS_ATTBASE
mdefine_line|#define SIS_ATTBASE     0x90
DECL|macro|SIS_APSIZE
mdefine_line|#define SIS_APSIZE      0x94
DECL|macro|SIS_TLBCNTRL
mdefine_line|#define SIS_TLBCNTRL    0x97
DECL|macro|SIS_TLBFLUSH
mdefine_line|#define SIS_TLBFLUSH    0x98
multiline_comment|/* AMD registers */
DECL|macro|AMD_APBASE
mdefine_line|#define AMD_APBASE      0x10
DECL|macro|AMD_MMBASE
mdefine_line|#define AMD_MMBASE      0x14
DECL|macro|AMD_APSIZE
mdefine_line|#define AMD_APSIZE      0xac
DECL|macro|AMD_MODECNTL
mdefine_line|#define AMD_MODECNTL    0xb0
DECL|macro|AMD_MODECNTL2
mdefine_line|#define AMD_MODECNTL2   0xb2
DECL|macro|AMD_GARTENABLE
mdefine_line|#define AMD_GARTENABLE  0x02&t;/* In mmio region (16-bit register) */
DECL|macro|AMD_ATTBASE
mdefine_line|#define AMD_ATTBASE     0x04&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_TLBFLUSH
mdefine_line|#define AMD_TLBFLUSH    0x0c&t;/* In mmio region (32-bit register) */
DECL|macro|AMD_CACHEENTRY
mdefine_line|#define AMD_CACHEENTRY  0x10&t;/* In mmio region (32-bit register) */
multiline_comment|/* ALi registers */
DECL|macro|ALI_APBASE
mdefine_line|#define ALI_APBASE&t;0x10
DECL|macro|ALI_AGPCTRL
mdefine_line|#define ALI_AGPCTRL&t;0xb8
DECL|macro|ALI_ATTBASE
mdefine_line|#define ALI_ATTBASE&t;0xbc
DECL|macro|ALI_TLBCTRL
mdefine_line|#define ALI_TLBCTRL&t;0xc0
DECL|macro|ALI_TAGCTRL
mdefine_line|#define ALI_TAGCTRL&t;0xc4
DECL|macro|ALI_CACHE_FLUSH_CTRL
mdefine_line|#define ALI_CACHE_FLUSH_CTRL&t;0xD0
DECL|macro|ALI_CACHE_FLUSH_ADDR_MASK
mdefine_line|#define ALI_CACHE_FLUSH_ADDR_MASK&t;0xFFFFF000
DECL|macro|ALI_CACHE_FLUSH_EN
mdefine_line|#define ALI_CACHE_FLUSH_EN&t;0x100
multiline_comment|/* Serverworks Registers */
DECL|macro|SVWRKS_APSIZE
mdefine_line|#define SVWRKS_APSIZE 0x10
DECL|macro|SVWRKS_SIZE_MASK
mdefine_line|#define SVWRKS_SIZE_MASK 0xfe000000
DECL|macro|SVWRKS_MMBASE
mdefine_line|#define SVWRKS_MMBASE 0x14
DECL|macro|SVWRKS_CACHING
mdefine_line|#define SVWRKS_CACHING 0x4b
DECL|macro|SVWRKS_FEATURE
mdefine_line|#define SVWRKS_FEATURE 0x68
multiline_comment|/* func 1 registers */
DECL|macro|SVWRKS_AGP_ENABLE
mdefine_line|#define SVWRKS_AGP_ENABLE 0x60
DECL|macro|SVWRKS_COMMAND
mdefine_line|#define SVWRKS_COMMAND 0x04
multiline_comment|/* Memory mapped registers */
DECL|macro|SVWRKS_GART_CACHE
mdefine_line|#define SVWRKS_GART_CACHE 0x02
DECL|macro|SVWRKS_GATTBASE
mdefine_line|#define SVWRKS_GATTBASE   0x04
DECL|macro|SVWRKS_TLBFLUSH
mdefine_line|#define SVWRKS_TLBFLUSH   0x10
DECL|macro|SVWRKS_POSTFLUSH
mdefine_line|#define SVWRKS_POSTFLUSH  0x14
DECL|macro|SVWRKS_DIRFLUSH
mdefine_line|#define SVWRKS_DIRFLUSH   0x0c
macro_line|#endif&t;&t;&t;&t;/* _AGP_BACKEND_PRIV_H */
eof
