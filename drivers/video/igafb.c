multiline_comment|/*&n; *  linux/drivers/video/igafb.c -- Frame buffer device for IGA 1682&n; *&n; *      Copyright (C) 1998  Vladimir Roganov and Gleb Raiko&n; *&n; *  This driver is partly based on the Frame buffer device for ATI Mach64&n; *  and partially on VESA-related code.&n; *&n; *      Copyright (C) 1997-1998  Geert Uytterhoeven&n; *      Copyright (C) 1998  Bernd Harries&n; *      Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/******************************************************************************&n;&n;  TODO:&n;       Despite of IGA Card has advanced graphic acceleration, &n;       initial version is almost dummy and does not support it.&n;       Support for video modes and acceleration must be added&n;       together with accelerated X-Windows driver implementation.&n;&n;       Most important thing at this moment is that we have working&n;       JavaEngine1  console &amp; X  with new console interface.&n;&n;******************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef __sparc__
macro_line|#include &lt;asm/pbm.h&gt;
macro_line|#include &lt;asm/pcic.h&gt;
macro_line|#endif
macro_line|#include &lt;video/iga.h&gt;
DECL|struct|pci_mmap_map
r_struct
id|pci_mmap_map
(brace
DECL|member|voff
r_int
r_int
id|voff
suffix:semicolon
DECL|member|poff
r_int
r_int
id|poff
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|prot_flag
r_int
r_int
id|prot_flag
suffix:semicolon
DECL|member|prot_mask
r_int
r_int
id|prot_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iga_par
r_struct
id|iga_par
(brace
DECL|member|mmap_map
r_struct
id|pci_mmap_map
op_star
id|mmap_map
suffix:semicolon
DECL|member|frame_buffer_phys
r_int
r_int
id|frame_buffer_phys
suffix:semicolon
DECL|member|io_base
r_int
r_int
id|io_base
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|fb_info
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|__initdata
r_struct
id|fb_fix_screeninfo
id|igafb_fix
id|__initdata
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;IGA 1682&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
dot
id|mmio_len
op_assign
l_int|1000
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|default_var
r_struct
id|fb_var_screeninfo
id|default_var
op_assign
(brace
multiline_comment|/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz dotclock) */
dot
id|xres
op_assign
l_int|640
comma
dot
id|yres
op_assign
l_int|480
comma
dot
id|xres_virtual
op_assign
l_int|640
comma
dot
id|yres_virtual
op_assign
l_int|480
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|green
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|accel_flags
op_assign
id|FB_ACCEL_NONE
comma
dot
id|pixclock
op_assign
l_int|39722
comma
dot
id|left_margin
op_assign
l_int|48
comma
dot
id|right_margin
op_assign
l_int|16
comma
dot
id|upper_margin
op_assign
l_int|33
comma
dot
id|lower_margin
op_assign
l_int|10
comma
dot
id|hsync_len
op_assign
l_int|96
comma
dot
id|vsync_len
op_assign
l_int|2
comma
dot
id|vmode
op_assign
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
macro_line|#ifdef __sparc__
DECL|variable|__initdata
r_struct
id|fb_var_screeninfo
id|default_var_1024x768
id|__initdata
op_assign
(brace
multiline_comment|/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz dotclock) */
dot
id|xres
op_assign
l_int|1024
comma
dot
id|yres
op_assign
l_int|768
comma
dot
id|xres_virtual
op_assign
l_int|1024
comma
dot
id|yres_virtual
op_assign
l_int|768
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|green
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|accel_flags
op_assign
id|FB_ACCEL_NONE
comma
dot
id|pixclock
op_assign
l_int|12699
comma
dot
id|left_margin
op_assign
l_int|176
comma
dot
id|right_margin
op_assign
l_int|16
comma
dot
id|upper_margin
op_assign
l_int|28
comma
dot
id|lower_margin
op_assign
l_int|1
comma
dot
id|hsync_len
op_assign
l_int|96
comma
dot
id|vsync_len
op_assign
l_int|3
comma
dot
id|vmode
op_assign
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
DECL|variable|__initdata
r_struct
id|fb_var_screeninfo
id|default_var_1152x900
id|__initdata
op_assign
(brace
multiline_comment|/* 1152x900, 76 Hz, Non-Interlaced (110.0 MHz dotclock) */
dot
id|xres
op_assign
l_int|1152
comma
dot
id|yres
op_assign
l_int|900
comma
dot
id|xres_virtual
op_assign
l_int|1152
comma
dot
id|yres_virtual
op_assign
l_int|900
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|green
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|accel_flags
op_assign
id|FB_ACCEL_NONE
comma
dot
id|pixclock
op_assign
l_int|9091
comma
dot
id|left_margin
op_assign
l_int|234
comma
dot
id|right_margin
op_assign
l_int|24
comma
dot
id|upper_margin
op_assign
l_int|34
comma
dot
id|lower_margin
op_assign
l_int|3
comma
dot
id|hsync_len
op_assign
l_int|100
comma
dot
id|vsync_len
op_assign
l_int|3
comma
dot
id|vmode
op_assign
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
DECL|variable|__initdata
r_struct
id|fb_var_screeninfo
id|default_var_1280x1024
id|__initdata
op_assign
(brace
multiline_comment|/* 1280x1024, 75 Hz, Non-Interlaced (135.00 MHz dotclock) */
dot
id|xres
op_assign
l_int|1280
comma
dot
id|yres
op_assign
l_int|1024
comma
dot
id|xres_virtual
op_assign
l_int|1280
comma
dot
id|yres_virtaul
op_assign
l_int|1024
comma
dot
id|bits_per_pixel
op_assign
l_int|8
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|green
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|blue
op_assign
(brace
l_int|0
comma
l_int|8
comma
l_int|0
)brace
comma
dot
id|height
op_assign
op_minus
l_int|1
comma
dot
id|width
op_assign
op_minus
l_int|1
comma
dot
id|accel_flags
op_assign
l_int|0
comma
dot
id|pixclock
op_assign
l_int|7408
comma
dot
id|left_margin
op_assign
l_int|248
comma
dot
id|right_margin
op_assign
l_int|16
comma
dot
id|upper_margin
op_assign
l_int|38
comma
dot
id|lower_margin
op_assign
l_int|1
comma
dot
id|hsync_len
op_assign
l_int|144
comma
dot
id|vsync_len
op_assign
l_int|3
comma
dot
id|vmode
op_assign
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/*&n; *   Memory-mapped I/O functions for Sparc PCI&n; *&n; * On sparc we happen to access I/O with memory mapped functions too.&n; */
DECL|macro|pci_inb
mdefine_line|#define pci_inb(par, reg)        readb(par-&gt;io_base+(reg))
DECL|macro|pci_outb
mdefine_line|#define pci_outb(par, val, reg)  writeb(val, par-&gt;io_base+(reg))
DECL|function|iga_inb
r_static
r_inline
r_int
r_int
id|iga_inb
c_func
(paren
r_struct
id|iga_par
op_star
id|par
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|idx
)paren
(brace
id|pci_outb
c_func
(paren
id|par
comma
id|idx
comma
id|reg
)paren
suffix:semicolon
r_return
id|pci_inb
c_func
(paren
id|par
comma
id|reg
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|iga_outb
r_static
r_inline
r_void
id|iga_outb
c_func
(paren
r_struct
id|iga_par
op_star
id|par
comma
r_int
r_char
id|val
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|idx
)paren
(brace
id|pci_outb
c_func
(paren
id|par
comma
id|idx
comma
id|reg
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
id|val
comma
id|reg
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif /* __sparc__ */
multiline_comment|/*&n; *  Very important functionality for the JavaEngine1 computer:&n; *  make screen border black (usign special IGA registers) &n; */
DECL|function|iga_blank_border
r_static
r_void
id|iga_blank_border
c_func
(paren
r_struct
id|iga_par
op_star
id|par
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t; * PROM does this for us, so keep this code as a reminder&n;&t; * about required read from 0x3DA and writing of 0x20 in the end.&n;&t; */
(paren
r_void
)paren
id|pci_inb
c_func
(paren
id|par
comma
l_int|0x3DA
)paren
suffix:semicolon
multiline_comment|/* required for every access */
id|pci_outb
c_func
(paren
id|par
comma
id|IGA_IDX_VGA_OVERSCAN
comma
id|IGA_ATTR_CTL
)paren
suffix:semicolon
(paren
r_void
)paren
id|pci_inb
c_func
(paren
id|par
comma
id|IGA_ATTR_CTL
op_plus
l_int|1
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
l_int|0x38
comma
id|IGA_ATTR_CTL
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
l_int|0x20
comma
id|IGA_ATTR_CTL
)paren
suffix:semicolon
multiline_comment|/* re-enable visual */
macro_line|#endif
multiline_comment|/*&n;&t; * This does not work as it was designed because the overscan&n;&t; * color is looked up in the palette. Therefore, under X11&n;&t; * overscan changes color.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|iga_outb
c_func
(paren
id|par
comma
l_int|0
comma
id|IGA_EXT_CNTRL
comma
id|IGA_IDX_OVERSCAN_COLOR
op_plus
id|i
)paren
suffix:semicolon
)brace
macro_line|#ifdef __sparc__
DECL|function|igafb_mmap
r_static
r_int
id|igafb_mmap
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|iga_par
op_star
id|par
op_assign
(paren
r_struct
id|iga_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_int
r_int
id|size
comma
id|page
comma
id|map_size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|map_offset
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;mmap_map
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
multiline_comment|/* To stop the swapper from even considering these pages. */
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
)paren
suffix:semicolon
multiline_comment|/* Each page, see which map applies */
r_for
c_loop
(paren
id|page
op_assign
l_int|0
suffix:semicolon
id|page
OL
id|size
suffix:semicolon
)paren
(brace
id|map_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
op_assign
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|voff
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_int
r_int
id|offset
op_assign
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|page
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|offset
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|end
)paren
r_continue
suffix:semicolon
id|map_size
op_assign
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|size
op_minus
(paren
id|offset
op_minus
id|start
)paren
suffix:semicolon
id|map_offset
op_assign
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|poff
op_plus
(paren
id|offset
op_minus
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map_size
)paren
(brace
id|page
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
op_plus
id|map_size
OG
id|size
)paren
id|map_size
op_assign
id|size
op_minus
id|page
suffix:semicolon
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_and_assign
op_complement
(paren
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|prot_mask
)paren
suffix:semicolon
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_or_assign
id|par-&gt;mmap_map
(braket
id|i
)braket
dot
id|prot_flag
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
op_plus
id|page
comma
id|map_offset
comma
id|map_size
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|page
op_add_assign
id|map_size
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map_size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __sparc__ */
DECL|function|igafb_setcolreg
r_static
r_int
id|igafb_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;         *  Set a single color register. The values supplied are&n;         *  already rounded down to the hardware&squot;s capabilities&n;         *  (according to the entries in the `var&squot; structure). Return&n;         *  != 0 for invalid regno.&n;         */
r_struct
id|iga_par
op_star
id|par
op_assign
(paren
r_struct
id|iga_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
id|info-&gt;cmap.len
)paren
r_return
l_int|1
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
id|regno
comma
id|DAC_W_INDEX
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
id|red
comma
id|DAC_DATA
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
id|green
comma
id|DAC_DATA
)paren
suffix:semicolon
id|pci_outb
c_func
(paren
id|par
comma
id|blue
comma
id|DAC_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
r_switch
c_cond
(paren
id|info-&gt;var.bits_per_pixel
)paren
(brace
r_case
l_int|16
suffix:colon
id|info-&gt;pseudo_palette
(braket
id|regno
)braket
op_assign
(paren
id|regno
op_lshift
l_int|10
)paren
op_or
(paren
id|regno
op_lshift
l_int|5
)paren
op_or
id|regno
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|info-&gt;pseudo_palette
(braket
id|regno
)braket
op_assign
(paren
id|regno
op_lshift
l_int|16
)paren
op_or
(paren
id|regno
op_lshift
l_int|8
)paren
op_or
id|regno
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
(paren
id|regno
op_lshift
l_int|8
)paren
op_or
id|regno
suffix:semicolon
id|info-&gt;pseudo_palette
(braket
id|regno
)braket
op_assign
(paren
id|i
op_lshift
l_int|16
)paren
op_or
id|i
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Framebuffer option structure&n; */
DECL|variable|igafb_ops
r_static
r_struct
id|fb_ops
id|igafb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_setcolreg
op_assign
id|igafb_setcolreg
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
macro_line|#ifdef __sparc__
dot
id|fb_mmap
op_assign
id|igafb_mmap
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|iga_init
r_static
r_int
id|__init
id|iga_init
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|iga_par
op_star
id|par
)paren
(brace
r_char
id|vramsz
op_assign
id|iga_inb
c_func
(paren
id|par
comma
id|IGA_EXT_CNTRL
comma
id|IGA_IDX_EXT_BUS_CNTL
)paren
op_amp
id|MEM_SIZE_ALIAS
suffix:semicolon
r_int
id|video_cmap_len
suffix:semicolon
r_switch
c_cond
(paren
id|vramsz
)paren
(brace
r_case
id|MEM_SIZE_1M
suffix:colon
id|info-&gt;fix.smem_len
op_assign
l_int|0x100000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEM_SIZE_2M
suffix:colon
id|info-&gt;fix.smem_len
op_assign
l_int|0x200000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEM_SIZE_4M
suffix:colon
r_case
id|MEM_SIZE_RESERVED
suffix:colon
id|info-&gt;fix.smem_len
op_assign
l_int|0x400000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;var.bits_per_pixel
OG
l_int|8
)paren
id|video_cmap_len
op_assign
l_int|16
suffix:semicolon
r_else
id|video_cmap_len
op_assign
l_int|256
suffix:semicolon
id|info-&gt;fbops
op_assign
op_amp
id|igafb_ops
suffix:semicolon
id|info-&gt;flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_alloc_cmap
c_func
(paren
id|info-&gt;cmap
comma
id|video_cmap_len
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
id|info
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fb%d: %s frame buffer device at 0x%08lx [%dMB VRAM]&bslash;n&quot;
comma
id|info-&gt;node
comma
id|info-&gt;fix.id
comma
id|par-&gt;frame_buffer_phys
comma
id|info-&gt;fix.smem_len
op_rshift
l_int|20
)paren
suffix:semicolon
id|iga_blank_border
c_func
(paren
id|par
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|igafb_init
r_int
id|__init
id|igafb_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|con_is_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|fb_info
op_star
id|info
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|iga_par
op_star
id|par
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|size
comma
id|iga2000
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Do not attach when we have a serial console. */
r_if
c_cond
(paren
op_logical_neg
id|con_is_present
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTERG
comma
id|PCI_DEVICE_ID_INTERG_1682
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * XXX We tried to use cyber2000fb.c for IGS 2000.&n;&t;&t; * But it does not initialize the chip in JavaStation-E, alas.&n;&t;&t; */
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_INTERG
comma
l_int|0x2000
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|iga2000
op_assign
l_int|1
suffix:semicolon
)brace
id|size
op_assign
r_sizeof
(paren
r_struct
id|fb_info
)paren
op_plus
r_sizeof
(paren
r_struct
id|iga_par
)paren
op_plus
r_sizeof
(paren
id|u32
)paren
op_star
l_int|16
suffix:semicolon
id|info
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;igafb_init: can&squot;t alloc fb_info&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|par
op_assign
(paren
r_struct
id|iga_par
op_star
)paren
(paren
id|info
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;igafb_init: no memory start&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|info-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|addr
comma
l_int|1024
op_star
l_int|1024
op_star
l_int|2
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;igafb_init: can&squot;t remap %lx[2M]&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|par-&gt;frame_buffer_phys
op_assign
id|addr
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
macro_line|#ifdef __sparc__
multiline_comment|/*&n;&t; * The following is sparc specific and this is why:&n;&t; *&n;&t; * IGS2000 has its I/O memory mapped and we want&n;&t; * to generate memory cycles on PCI, e.g. do ioremap(),&n;&t; * then readb/writeb() as in Documentation/IO-mapping.txt.&n;&t; *&n;&t; * IGS1682 is more traditional, it responds to PCI I/O&n;&t; * cycles, so we want to access it with inb()/outb().&n;&t; *&n;&t; * On sparc, PCIC converts CPU memory access within&n;&t; * phys window 0x3000xxxx into PCI I/O cycles. Therefore&n;&t; * we may use readb/writeb to access them with IGS1682.&n;&t; *&n;&t; * We do not take io_base_phys from resource[n].start&n;&t; * on IGS1682 because that chip is BROKEN. It does not&n;&t; * have a base register for I/O. We just &quot;know&quot; what its&n;&t; * I/O addresses are.&n;&t; */
r_if
c_cond
(paren
id|iga2000
)paren
(brace
id|igafb_fix.mmio_start
op_assign
id|par-&gt;frame_buffer_phys
op_or
l_int|0x00800000
suffix:semicolon
)brace
r_else
(brace
id|igafb_fix.mmio_start
op_assign
l_int|0x30000000
suffix:semicolon
multiline_comment|/* XXX */
)brace
r_if
c_cond
(paren
(paren
id|par-&gt;io_base
op_assign
(paren
r_int
)paren
id|ioremap
c_func
(paren
id|igafb_fix.mmio_start
comma
id|igafb_fix.smem_len
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;igafb_init: can&squot;t remap %lx[4K]&bslash;n&quot;
comma
id|igafb_fix.mmio_start
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|info-&gt;screen_base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Figure mmap addresses from PCI config space.&n;&t; * We need two regions: for video memory and for I/O ports.&n;&t; * Later one can add region for video coprocessor registers.&n;&t; * However, mmap routine loops until size != 0, so we put&n;&t; * one additional region with size == 0. &n;&t; */
id|par-&gt;mmap_map
op_assign
id|kmalloc
c_func
(paren
l_int|4
op_star
r_sizeof
(paren
op_star
id|par-&gt;mmap_map
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|par-&gt;mmap_map
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;igafb_init: can&squot;t alloc mmap_map&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|par-&gt;io_base
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|info-&gt;screen_base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|par-&gt;mmap_map
comma
l_int|0
comma
l_int|4
op_star
r_sizeof
(paren
op_star
id|par-&gt;mmap_map
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set default vmode and cmode from PROM properties.&n;&t; */
(brace
r_struct
id|pcidev_cookie
op_star
id|cookie
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_int
id|node
op_assign
id|cookie-&gt;prom_node
suffix:semicolon
r_int
id|width
op_assign
id|prom_getintdefault
c_func
(paren
id|node
comma
l_string|&quot;width&quot;
comma
l_int|1024
)paren
suffix:semicolon
r_int
id|height
op_assign
id|prom_getintdefault
c_func
(paren
id|node
comma
l_string|&quot;height&quot;
comma
l_int|768
)paren
suffix:semicolon
r_int
id|depth
op_assign
id|prom_getintdefault
c_func
(paren
id|node
comma
l_string|&quot;depth&quot;
comma
l_int|8
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|width
)paren
(brace
r_case
l_int|1024
suffix:colon
r_if
c_cond
(paren
id|height
op_eq
l_int|768
)paren
id|default_var
op_assign
id|default_var_1024x768
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1152
suffix:colon
r_if
c_cond
(paren
id|height
op_eq
l_int|900
)paren
id|default_var
op_assign
id|default_var_1152x900
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1280
suffix:colon
r_if
c_cond
(paren
id|height
op_eq
l_int|1024
)paren
id|default_var
op_assign
id|default_var_1280x1024
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|depth
)paren
(brace
r_case
l_int|8
suffix:colon
id|default_var.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|default_var.bits_per_pixel
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
id|default_var.bits_per_pixel
op_assign
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|32
suffix:colon
id|default_var.bits_per_pixel
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif
id|igafb_fix.smem_start
op_assign
(paren
r_int
r_int
)paren
id|info-&gt;screen_base
suffix:semicolon
id|igafb_fix.line_length
op_assign
id|default_var.xres
op_star
(paren
id|default_var.bits_per_pixel
op_div
l_int|8
)paren
suffix:semicolon
id|igafb_fix.visual
op_assign
id|default_var.bits_per_pixel
op_le
l_int|8
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_DIRECTCOLOR
suffix:semicolon
id|info-&gt;var
op_assign
id|default_var
suffix:semicolon
id|info-&gt;fix
op_assign
id|igafb_fix
suffix:semicolon
id|info-&gt;pseudo_palette
op_assign
(paren
r_void
op_star
)paren
(paren
id|par
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iga_init
c_func
(paren
id|info
comma
id|par
)paren
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|par-&gt;io_base
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|info-&gt;screen_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;mmap_map
)paren
id|kfree
c_func
(paren
id|par-&gt;mmap_map
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
macro_line|#ifdef __sparc__
multiline_comment|/*&n;&t;     * Add /dev/fb mmap values.&n;&t;     */
multiline_comment|/* First region is for video memory */
id|par-&gt;mmap_map
(braket
l_int|0
)braket
dot
id|voff
op_assign
l_int|0x0
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|0
)braket
dot
id|poff
op_assign
id|par-&gt;frame_buffer_phys
op_amp
id|PAGE_MASK
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|0
)braket
dot
id|size
op_assign
id|info-&gt;fix.smem_len
op_amp
id|PAGE_MASK
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|0
)braket
dot
id|prot_mask
op_assign
id|SRMMU_CACHE
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|0
)braket
dot
id|prot_flag
op_assign
id|SRMMU_WRITE
suffix:semicolon
multiline_comment|/* Second region is for I/O ports */
id|par-&gt;mmap_map
(braket
l_int|1
)braket
dot
id|voff
op_assign
id|par-&gt;frame_buffer_phys
op_amp
id|PAGE_MASK
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|1
)braket
dot
id|poff
op_assign
id|info-&gt;fix.smem_start
op_amp
id|PAGE_MASK
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|1
)braket
dot
id|size
op_assign
id|PAGE_SIZE
op_star
l_int|2
suffix:semicolon
multiline_comment|/* X wants 2 pages */
id|par-&gt;mmap_map
(braket
l_int|1
)braket
dot
id|prot_mask
op_assign
id|SRMMU_CACHE
suffix:semicolon
id|par-&gt;mmap_map
(braket
l_int|1
)braket
dot
id|prot_flag
op_assign
id|SRMMU_WRITE
suffix:semicolon
macro_line|#endif /* __sparc__ */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|igafb_setup
r_int
id|__init
id|igafb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|this_opt
op_assign
id|strsep
c_func
(paren
op_amp
id|options
comma
l_string|&quot;,&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
