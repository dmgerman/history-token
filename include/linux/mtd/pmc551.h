multiline_comment|/*&n; * $Id: pmc551.h,v 1.3 2000/10/30 20:03:23 major Exp $&n; *&n; * PMC551 PCI Mezzanine Ram Device&n; *&n; * Author:&n; *       Mark Ferrell&n; *       Copyright 1999,2000 Nortel Networks&n; *&n; * License: &n; *&t; As part of this driver was derrived from the slram.c driver it falls&n; *&t; under the same license, which is GNU General Public License v2&n; */
macro_line|#ifndef __MTD_PMC551_H__
DECL|macro|__MTD_PMC551_H__
mdefine_line|#define __MTD_PMC551_H__
macro_line|#include &lt;linux/mtd/mtd.h&gt;
DECL|macro|PMC551_VERSION
mdefine_line|#define PMC551_VERSION &quot;$Id: pmc551.h,v 1.3 2000/10/30 20:03:23 major Exp $&bslash;n&quot;&bslash;&n;       &quot;Ramix PMC551 PCI Mezzanine Ram Driver. (C) 1999,2000 Nortel Networks.&bslash;n&quot;
multiline_comment|/*&n; * Our personal and private information&n; */
DECL|struct|mypriv
r_struct
id|mypriv
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|start
id|u_char
op_star
id|start
suffix:semicolon
DECL|member|mem_map0_base_val
id|u32
id|mem_map0_base_val
suffix:semicolon
DECL|member|curr_mem_map0_val
id|u32
id|curr_mem_map0_val
suffix:semicolon
DECL|member|aperture_size
id|u32
id|aperture_size
suffix:semicolon
DECL|member|nextpmc551
r_struct
id|mtd_info
op_star
id|nextpmc551
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Function Prototypes&n; */
r_static
r_int
id|pmc551_erase
c_func
(paren
r_struct
id|mtd_info
op_star
comma
r_struct
id|erase_info
op_star
)paren
suffix:semicolon
r_static
r_void
id|pmc551_unpoint
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|u_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|pmc551_read
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|loff_t
comma
r_int
comma
r_int
op_star
comma
id|u_char
op_star
)paren
suffix:semicolon
r_static
r_int
id|pmc551_write
c_func
(paren
r_struct
id|mtd_info
op_star
comma
id|loff_t
comma
r_int
comma
r_int
op_star
comma
r_const
id|u_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Define the PCI ID&squot;s if the kernel doesn&squot;t define them for us&n; */
macro_line|#ifndef PCI_VENDOR_ID_V3_SEMI
DECL|macro|PCI_VENDOR_ID_V3_SEMI
mdefine_line|#define PCI_VENDOR_ID_V3_SEMI             0x11b0
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_V3_SEMI_V370PDC
DECL|macro|PCI_DEVICE_ID_V3_SEMI_V370PDC
mdefine_line|#define PCI_DEVICE_ID_V3_SEMI_V370PDC     0x0200  
macro_line|#endif
DECL|macro|PMC551_PCI_MEM_MAP0
mdefine_line|#define PMC551_PCI_MEM_MAP0&t;0x50
DECL|macro|PMC551_PCI_MEM_MAP1
mdefine_line|#define PMC551_PCI_MEM_MAP1&t;0x54
DECL|macro|PMC551_PCI_MEM_MAP_MAP_ADDR_MASK
mdefine_line|#define PMC551_PCI_MEM_MAP_MAP_ADDR_MASK&t;0x3ff00000
DECL|macro|PMC551_PCI_MEM_MAP_APERTURE_MASK
mdefine_line|#define PMC551_PCI_MEM_MAP_APERTURE_MASK&t;0x000000f0
DECL|macro|PMC551_PCI_MEM_MAP_REG_EN
mdefine_line|#define PMC551_PCI_MEM_MAP_REG_EN&t;&t;0x00000002
DECL|macro|PMC551_PCI_MEM_MAP_ENABLE
mdefine_line|#define PMC551_PCI_MEM_MAP_ENABLE&t;&t;0x00000001
DECL|macro|PMC551_SDRAM_MA
mdefine_line|#define PMC551_SDRAM_MA&t;&t;0x60
DECL|macro|PMC551_SDRAM_CMD
mdefine_line|#define PMC551_SDRAM_CMD&t;0x62
DECL|macro|PMC551_DRAM_CFG
mdefine_line|#define PMC551_DRAM_CFG&t;&t;0x64
DECL|macro|PMC551_SYS_CTRL_REG
mdefine_line|#define PMC551_SYS_CTRL_REG&t;0x78
DECL|macro|PMC551_DRAM_BLK0
mdefine_line|#define PMC551_DRAM_BLK0&t;0x68
DECL|macro|PMC551_DRAM_BLK1
mdefine_line|#define PMC551_DRAM_BLK1&t;0x6c
DECL|macro|PMC551_DRAM_BLK2
mdefine_line|#define PMC551_DRAM_BLK2&t;0x70
DECL|macro|PMC551_DRAM_BLK3
mdefine_line|#define PMC551_DRAM_BLK3&t;0x74
DECL|macro|PMC551_DRAM_BLK_GET_SIZE
mdefine_line|#define PMC551_DRAM_BLK_GET_SIZE(x) (524288&lt;&lt;((x&gt;&gt;4)&amp;0x0f))
DECL|macro|PMC551_DRAM_BLK_SET_COL_MUX
mdefine_line|#define PMC551_DRAM_BLK_SET_COL_MUX(x,v) (((x) &amp; ~0x00007000) | (((v) &amp; 0x7) &lt;&lt; 12))
DECL|macro|PMC551_DRAM_BLK_SET_ROW_MUX
mdefine_line|#define PMC551_DRAM_BLK_SET_ROW_MUX(x,v) (((x) &amp; ~0x00000f00) | (((v) &amp; 0xf) &lt;&lt; 8))
DECL|macro|PMC551_ADDR_HIGH_MASK
mdefine_line|#define PMC551_ADDR_HIGH_MASK&t;0x3ff00000
DECL|macro|PMC551_ADDR_LOW_MASK
mdefine_line|#define PMC551_ADDR_LOW_MASK&t;0x000fffff
macro_line|#endif /* __MTD_PMC551_H__ */
eof
