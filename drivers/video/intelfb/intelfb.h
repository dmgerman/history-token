macro_line|#ifndef _INTELFB_H
DECL|macro|_INTELFB_H
mdefine_line|#define _INTELFB_H
multiline_comment|/* $DHD: intelfb/intelfb.h,v 1.40 2003/06/27 15:06:25 dawes Exp $ */
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
multiline_comment|/*** Version/name ***/
DECL|macro|INTELFB_VERSION
mdefine_line|#define INTELFB_VERSION&t;&t;&t;&quot;0.9.2&quot;
DECL|macro|INTELFB_MODULE_NAME
mdefine_line|#define INTELFB_MODULE_NAME&t;&t;&quot;intelfb&quot;
DECL|macro|SUPPORTED_CHIPSETS
mdefine_line|#define SUPPORTED_CHIPSETS&t;&t;&quot;830M/845G/852GM/855GM/865G&quot;
multiline_comment|/*** Debug/feature defines ***/
macro_line|#ifndef DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG&t;&t;&t;&t;0
macro_line|#endif
macro_line|#ifndef VERBOSE
DECL|macro|VERBOSE
mdefine_line|#define VERBOSE&t;&t;&t;&t;0
macro_line|#endif
macro_line|#ifndef REGDUMP
DECL|macro|REGDUMP
mdefine_line|#define REGDUMP&t;&t;&t;&t;0
macro_line|#endif
macro_line|#ifndef DETECT_VGA_CLASS_ONLY
DECL|macro|DETECT_VGA_CLASS_ONLY
mdefine_line|#define DETECT_VGA_CLASS_ONLY&t;&t;1
macro_line|#endif
macro_line|#ifndef ALLOCATE_FOR_PANNING
DECL|macro|ALLOCATE_FOR_PANNING
mdefine_line|#define ALLOCATE_FOR_PANNING&t;&t;1
macro_line|#endif
macro_line|#ifndef PREFERRED_MODE
DECL|macro|PREFERRED_MODE
mdefine_line|#define PREFERRED_MODE&t;&t;&t;&quot;1024x768-16@60&quot;
macro_line|#endif
multiline_comment|/*** hw-related values ***/
multiline_comment|/* PCI ids for supported devices */
DECL|macro|PCI_DEVICE_ID_INTEL_830M
mdefine_line|#define PCI_DEVICE_ID_INTEL_830M&t;0x3577
DECL|macro|PCI_DEVICE_ID_INTEL_845G
mdefine_line|#define PCI_DEVICE_ID_INTEL_845G&t;0x2562
DECL|macro|PCI_DEVICE_ID_INTEL_85XGM
mdefine_line|#define PCI_DEVICE_ID_INTEL_85XGM&t;0x3582
DECL|macro|PCI_DEVICE_ID_INTEL_865G
mdefine_line|#define PCI_DEVICE_ID_INTEL_865G&t;0x2572
multiline_comment|/* Size of MMIO region */
DECL|macro|INTEL_REG_SIZE
mdefine_line|#define INTEL_REG_SIZE&t;&t;&t;0x80000
DECL|macro|STRIDE_ALIGNMENT
mdefine_line|#define STRIDE_ALIGNMENT&t;&t;16
DECL|macro|PALETTE_8_ENTRIES
mdefine_line|#define PALETTE_8_ENTRIES&t;&t;256
multiline_comment|/*** Macros ***/
multiline_comment|/* basic arithmetic */
DECL|macro|KB
mdefine_line|#define KB(x)&t;&t;&t;((x) * 1024)
DECL|macro|MB
mdefine_line|#define MB(x)&t;&t;&t;((x) * 1024 * 1024)
DECL|macro|BtoKB
mdefine_line|#define BtoKB(x)&t;&t;((x) / 1024)
DECL|macro|BtoMB
mdefine_line|#define BtoMB(x)&t;&t;((x) / 1024 / 1024)
DECL|macro|GTT_PAGE_SIZE
mdefine_line|#define GTT_PAGE_SIZE           KB(4)
DECL|macro|ROUND_UP_TO
mdefine_line|#define ROUND_UP_TO(x, y)&t;(((x) + (y) - 1) / (y) * (y))
DECL|macro|ROUND_DOWN_TO
mdefine_line|#define ROUND_DOWN_TO(x, y)&t;((x) / (y) * (y))
DECL|macro|ROUND_UP_TO_PAGE
mdefine_line|#define ROUND_UP_TO_PAGE(x)&t;ROUND_UP_TO((x), GTT_PAGE_SIZE)
DECL|macro|ROUND_DOWN_TO_PAGE
mdefine_line|#define ROUND_DOWN_TO_PAGE(x)&t;ROUND_DOWN_TO((x), GTT_PAGE_SIZE)
multiline_comment|/* messages */
DECL|macro|PFX
mdefine_line|#define PFX&t;&t;&t;INTELFB_MODULE_NAME &quot;: &quot;
DECL|macro|ERR_MSG
mdefine_line|#define ERR_MSG(fmt, args...)&t;printk(KERN_ERR PFX fmt, ## args)
DECL|macro|WRN_MSG
mdefine_line|#define WRN_MSG(fmt, args...)&t;printk(KERN_WARNING PFX fmt, ## args)
DECL|macro|NOT_MSG
mdefine_line|#define NOT_MSG(fmt, args...)&t;printk(KERN_NOTICE PFX fmt, ## args)
DECL|macro|INF_MSG
mdefine_line|#define INF_MSG(fmt, args...)&t;printk(KERN_INFO PFX fmt, ## args)
macro_line|#if DEBUG
DECL|macro|DBG_MSG
mdefine_line|#define DBG_MSG(fmt, args...)&t;printk(KERN_DEBUG PFX fmt, ## args)
macro_line|#else
DECL|macro|DBG_MSG
mdefine_line|#define DBG_MSG(fmt, args...)&t;while (0) printk(fmt, ## args)
macro_line|#endif
multiline_comment|/* get commonly used pointers */
DECL|macro|GET_DINFO
mdefine_line|#define GET_DINFO(info)&t;&t;(info)-&gt;par
multiline_comment|/* misc macros */
DECL|macro|ACCEL
mdefine_line|#define ACCEL(d, i)                                                     &bslash;&n;&t;((d)-&gt;accel &amp;&amp; !(d)-&gt;ring_lockup &amp;&amp;                             &bslash;&n;&t; ((i)-&gt;var.accel_flags &amp; FB_ACCELF_TEXT))
multiline_comment|/*#define NOACCEL_CHIPSET(d)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((d)-&gt;chipset != INTEL_865G)*/
DECL|macro|NOACCEL_CHIPSET
mdefine_line|#define NOACCEL_CHIPSET(d)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(0)
DECL|macro|FIXED_MODE
mdefine_line|#define FIXED_MODE(d) ((d)-&gt;fixed_mode)
multiline_comment|/*** Driver paramters ***/
DECL|macro|RINGBUFFER_SIZE
mdefine_line|#define RINGBUFFER_SIZE&t;&t;KB(64)
DECL|macro|HW_CURSOR_SIZE
mdefine_line|#define HW_CURSOR_SIZE&t;&t;KB(4)
multiline_comment|/* Intel agpgart driver */
DECL|macro|AGP_PHYSICAL_MEMORY
mdefine_line|#define AGP_PHYSICAL_MEMORY     2
multiline_comment|/*** Data Types ***/
multiline_comment|/* supported chipsets */
DECL|enum|intel_chips
r_enum
id|intel_chips
(brace
DECL|enumerator|INTEL_830M
id|INTEL_830M
comma
DECL|enumerator|INTEL_845G
id|INTEL_845G
comma
DECL|enumerator|INTEL_85XGM
id|INTEL_85XGM
comma
DECL|enumerator|INTEL_852GM
id|INTEL_852GM
comma
DECL|enumerator|INTEL_852GME
id|INTEL_852GME
comma
DECL|enumerator|INTEL_855GM
id|INTEL_855GM
comma
DECL|enumerator|INTEL_855GME
id|INTEL_855GME
comma
DECL|enumerator|INTEL_865G
id|INTEL_865G
)brace
suffix:semicolon
DECL|struct|intelfb_hwstate
r_struct
id|intelfb_hwstate
(brace
DECL|member|vga0_divisor
id|u32
id|vga0_divisor
suffix:semicolon
DECL|member|vga1_divisor
id|u32
id|vga1_divisor
suffix:semicolon
DECL|member|vga_pd
id|u32
id|vga_pd
suffix:semicolon
DECL|member|dpll_a
id|u32
id|dpll_a
suffix:semicolon
DECL|member|dpll_b
id|u32
id|dpll_b
suffix:semicolon
DECL|member|fpa0
id|u32
id|fpa0
suffix:semicolon
DECL|member|fpa1
id|u32
id|fpa1
suffix:semicolon
DECL|member|fpb0
id|u32
id|fpb0
suffix:semicolon
DECL|member|fpb1
id|u32
id|fpb1
suffix:semicolon
DECL|member|palette_a
id|u32
id|palette_a
(braket
id|PALETTE_8_ENTRIES
)braket
suffix:semicolon
DECL|member|palette_b
id|u32
id|palette_b
(braket
id|PALETTE_8_ENTRIES
)braket
suffix:semicolon
DECL|member|htotal_a
id|u32
id|htotal_a
suffix:semicolon
DECL|member|hblank_a
id|u32
id|hblank_a
suffix:semicolon
DECL|member|hsync_a
id|u32
id|hsync_a
suffix:semicolon
DECL|member|vtotal_a
id|u32
id|vtotal_a
suffix:semicolon
DECL|member|vblank_a
id|u32
id|vblank_a
suffix:semicolon
DECL|member|vsync_a
id|u32
id|vsync_a
suffix:semicolon
DECL|member|src_size_a
id|u32
id|src_size_a
suffix:semicolon
DECL|member|bclrpat_a
id|u32
id|bclrpat_a
suffix:semicolon
DECL|member|htotal_b
id|u32
id|htotal_b
suffix:semicolon
DECL|member|hblank_b
id|u32
id|hblank_b
suffix:semicolon
DECL|member|hsync_b
id|u32
id|hsync_b
suffix:semicolon
DECL|member|vtotal_b
id|u32
id|vtotal_b
suffix:semicolon
DECL|member|vblank_b
id|u32
id|vblank_b
suffix:semicolon
DECL|member|vsync_b
id|u32
id|vsync_b
suffix:semicolon
DECL|member|src_size_b
id|u32
id|src_size_b
suffix:semicolon
DECL|member|bclrpat_b
id|u32
id|bclrpat_b
suffix:semicolon
DECL|member|adpa
id|u32
id|adpa
suffix:semicolon
DECL|member|dvoa
id|u32
id|dvoa
suffix:semicolon
DECL|member|dvob
id|u32
id|dvob
suffix:semicolon
DECL|member|dvoc
id|u32
id|dvoc
suffix:semicolon
DECL|member|dvoa_srcdim
id|u32
id|dvoa_srcdim
suffix:semicolon
DECL|member|dvob_srcdim
id|u32
id|dvob_srcdim
suffix:semicolon
DECL|member|dvoc_srcdim
id|u32
id|dvoc_srcdim
suffix:semicolon
DECL|member|lvds
id|u32
id|lvds
suffix:semicolon
DECL|member|pipe_a_conf
id|u32
id|pipe_a_conf
suffix:semicolon
DECL|member|pipe_b_conf
id|u32
id|pipe_b_conf
suffix:semicolon
DECL|member|disp_arb
id|u32
id|disp_arb
suffix:semicolon
DECL|member|cursor_a_control
id|u32
id|cursor_a_control
suffix:semicolon
DECL|member|cursor_b_control
id|u32
id|cursor_b_control
suffix:semicolon
DECL|member|cursor_a_base
id|u32
id|cursor_a_base
suffix:semicolon
DECL|member|cursor_b_base
id|u32
id|cursor_b_base
suffix:semicolon
DECL|member|cursor_size
id|u32
id|cursor_size
suffix:semicolon
DECL|member|disp_a_ctrl
id|u32
id|disp_a_ctrl
suffix:semicolon
DECL|member|disp_b_ctrl
id|u32
id|disp_b_ctrl
suffix:semicolon
DECL|member|disp_a_base
id|u32
id|disp_a_base
suffix:semicolon
DECL|member|disp_b_base
id|u32
id|disp_b_base
suffix:semicolon
DECL|member|cursor_a_palette
id|u32
id|cursor_a_palette
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cursor_b_palette
id|u32
id|cursor_b_palette
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|disp_a_stride
id|u32
id|disp_a_stride
suffix:semicolon
DECL|member|disp_b_stride
id|u32
id|disp_b_stride
suffix:semicolon
DECL|member|vgacntrl
id|u32
id|vgacntrl
suffix:semicolon
DECL|member|add_id
id|u32
id|add_id
suffix:semicolon
DECL|member|swf0x
id|u32
id|swf0x
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|swf1x
id|u32
id|swf1x
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|swf3x
id|u32
id|swf3x
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fence
id|u32
id|fence
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|instpm
id|u32
id|instpm
suffix:semicolon
DECL|member|mem_mode
id|u32
id|mem_mode
suffix:semicolon
DECL|member|fw_blc_0
id|u32
id|fw_blc_0
suffix:semicolon
DECL|member|fw_blc_1
id|u32
id|fw_blc_1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|intelfb_heap_data
r_struct
id|intelfb_heap_data
(brace
DECL|member|physical
id|u32
id|physical
suffix:semicolon
DECL|member|virtual
id|u8
id|__iomem
op_star
r_virtual
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
singleline_comment|// in GATT pages
DECL|member|size
id|u32
id|size
suffix:semicolon
singleline_comment|// in bytes
)brace
suffix:semicolon
DECL|struct|intelfb_info
r_struct
id|intelfb_info
(brace
DECL|member|info
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
DECL|member|fbops
r_struct
id|fb_ops
op_star
id|fbops
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|save_state
r_struct
id|intelfb_hwstate
id|save_state
suffix:semicolon
multiline_comment|/* agpgart structs */
DECL|member|gtt_fb_mem
r_struct
id|agp_memory
op_star
id|gtt_fb_mem
suffix:semicolon
singleline_comment|// use all stolen memory or vram
DECL|member|gtt_ring_mem
r_struct
id|agp_memory
op_star
id|gtt_ring_mem
suffix:semicolon
singleline_comment|// ring buffer
DECL|member|gtt_cursor_mem
r_struct
id|agp_memory
op_star
id|gtt_cursor_mem
suffix:semicolon
singleline_comment|// hw cursor
multiline_comment|/* use a gart reserved fb mem */
DECL|member|fbmem_gart
id|u8
id|fbmem_gart
suffix:semicolon
multiline_comment|/* mtrr support */
DECL|member|mtrr_reg
id|u32
id|mtrr_reg
suffix:semicolon
DECL|member|has_mtrr
id|u32
id|has_mtrr
suffix:semicolon
multiline_comment|/* heap data */
DECL|member|aperture
r_struct
id|intelfb_heap_data
id|aperture
suffix:semicolon
DECL|member|fb
r_struct
id|intelfb_heap_data
id|fb
suffix:semicolon
DECL|member|ring
r_struct
id|intelfb_heap_data
id|ring
suffix:semicolon
DECL|member|cursor
r_struct
id|intelfb_heap_data
id|cursor
suffix:semicolon
multiline_comment|/* mmio regs */
DECL|member|mmio_base_phys
id|u32
id|mmio_base_phys
suffix:semicolon
DECL|member|mmio_base
id|u8
id|__iomem
op_star
id|mmio_base
suffix:semicolon
multiline_comment|/* fb start offset (in bytes) */
DECL|member|fb_start
id|u32
id|fb_start
suffix:semicolon
multiline_comment|/* ring buffer */
DECL|member|ring_head
id|u8
id|__iomem
op_star
id|ring_head
suffix:semicolon
DECL|member|ring_tail
id|u32
id|ring_tail
suffix:semicolon
DECL|member|ring_tail_mask
id|u32
id|ring_tail_mask
suffix:semicolon
DECL|member|ring_space
id|u32
id|ring_space
suffix:semicolon
DECL|member|ring_lockup
id|u32
id|ring_lockup
suffix:semicolon
multiline_comment|/* palette */
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|member|palette
r_struct
(brace
id|u8
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* chip info */
DECL|member|pci_chipset
r_int
id|pci_chipset
suffix:semicolon
DECL|member|chipset
r_int
id|chipset
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mobile
r_int
id|mobile
suffix:semicolon
multiline_comment|/* current mode */
DECL|member|bpp
DECL|member|depth
r_int
id|bpp
comma
id|depth
suffix:semicolon
DECL|member|visual
id|u32
id|visual
suffix:semicolon
DECL|member|xres
DECL|member|yres
DECL|member|pitch
r_int
id|xres
comma
id|yres
comma
id|pitch
suffix:semicolon
DECL|member|pixclock
r_int
id|pixclock
suffix:semicolon
multiline_comment|/* current pipe */
DECL|member|pipe
r_int
id|pipe
suffix:semicolon
multiline_comment|/* some flags */
DECL|member|accel
r_int
id|accel
suffix:semicolon
DECL|member|hwcursor
r_int
id|hwcursor
suffix:semicolon
DECL|member|fixed_mode
r_int
id|fixed_mode
suffix:semicolon
DECL|member|ring_active
r_int
id|ring_active
suffix:semicolon
multiline_comment|/* hw cursor */
DECL|member|cursor_on
r_int
id|cursor_on
suffix:semicolon
DECL|member|cursor_blanked
r_int
id|cursor_blanked
suffix:semicolon
DECL|member|cursor_src
id|u8
id|cursor_src
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* initial parameters */
DECL|member|initial_vga
r_int
id|initial_vga
suffix:semicolon
DECL|member|initial_var
r_struct
id|fb_var_screeninfo
id|initial_var
suffix:semicolon
DECL|member|initial_fb_base
id|u32
id|initial_fb_base
suffix:semicolon
DECL|member|initial_video_ram
id|u32
id|initial_video_ram
suffix:semicolon
DECL|member|initial_pitch
id|u32
id|initial_pitch
suffix:semicolon
multiline_comment|/* driver registered */
DECL|member|registered
r_int
id|registered
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*** function prototypes ***/
r_extern
r_int
id|intelfb_var_to_depth
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
macro_line|#endif /* _INTELFB_H */
eof
