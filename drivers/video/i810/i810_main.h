multiline_comment|/*-*- linux-c -*-&n; *  linux/drivers/video/i810fb_main.h -- Intel 810 frame buffer device &n; *                                       main header file&n; *&n; *      Copyright (C) 2001 Antonino Daplas&lt;adaplas@pol.net&gt;&n; *      All Rights Reserved      &n; *&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#ifndef __I810_MAIN_H__
DECL|macro|__I810_MAIN_H__
mdefine_line|#define __I810_MAIN_H__
multiline_comment|/* PCI */
DECL|variable|__initdata
r_static
r_const
r_char
op_star
id|i810_pci_list
(braket
)braket
id|__initdata
op_assign
(brace
l_string|&quot;Intel(R) 810 Framebuffer Device&quot;
comma
l_string|&quot;Intel(R) 810-DC100 Framebuffer Device&quot;
comma
l_string|&quot;Intel(R) 810E Framebuffer Device&quot;
comma
l_string|&quot;Intel(R) 815 (Internal Graphics 100Mhz FSB) Framebuffer Device&quot;
comma
l_string|&quot;Intel(R) 815 (Internal Graphics only) Framebuffer Device&quot;
comma
l_string|&quot;Intel(R) 815 (Internal Graphics with AGP) Framebuffer Device&quot;
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|i810fb_pci_tbl
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810_IG1
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810_IG3
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810E_IG
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
multiline_comment|/* mvo: added i815 PCI-ID */
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82815_100
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82815_NOAGP
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82815_CGC
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|5
)brace
)brace
suffix:semicolon
r_static
r_int
id|__init
id|i810fb_init_pci
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|entry
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|i810fb_remove_pci
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|i810fb_resume
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|i810fb_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
DECL|variable|i810fb_driver
r_static
r_struct
id|pci_driver
id|i810fb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i810fb&quot;
comma
dot
id|id_table
op_assign
id|i810fb_pci_tbl
comma
dot
id|probe
op_assign
id|i810fb_init_pci
comma
dot
id|remove
op_assign
id|__exit_p
c_func
(paren
id|i810fb_remove_pci
)paren
comma
dot
id|suspend
op_assign
id|i810fb_suspend
comma
dot
id|resume
op_assign
id|i810fb_resume
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|vram
id|__initdata
op_assign
l_int|4
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|bpp
id|__initdata
op_assign
l_int|8
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|mtrr
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|accel
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|hsync1
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|hsync2
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|vsync1
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|vsync2
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|xres
id|__initdata
op_assign
l_int|640
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|yres
id|__initdata
op_assign
l_int|480
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|vyres
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|sync
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|ext_vga
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|dcolor
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * voffset - framebuffer offset in MiB from aperture start address.  In order for&n; * the driver to work with X, we must try to use memory holes left untouched by X. The &n; * following table lists where X&squot;s different surfaces start at.  &n; * &n; * ---------------------------------------------&n; * :                :  64 MiB     : 32 MiB      :&n; * ----------------------------------------------&n; * : FrontBuffer    :   0         :  0          :&n; * : DepthBuffer    :   48        :  16         :&n; * : BackBuffer     :   56        :  24         :&n; * ----------------------------------------------&n; *&n; * So for chipsets with 64 MiB Aperture sizes, 32 MiB for v_offset is okay, allowing up to&n; * 15 + 1 MiB of Framebuffer memory.  For 32 MiB Aperture sizes, a v_offset of 8 MiB should&n; * work, allowing 7 + 1 MiB of Framebuffer memory.&n; * Note, the size of the hole may change depending on how much memory you allocate to X,&n; * and how the memory is split up between these surfaces.  &n; *&n; * Note: Anytime the DepthBuffer or FrontBuffer is overlapped, X would still run but with&n; * DRI disabled.  But if the Frontbuffer is overlapped, X will fail to load.&n; * &n; * Experiment with v_offset to find out which works best for you.&n; */
DECL|variable|__initdata
r_static
id|u32
id|v_offset_default
id|__initdata
suffix:semicolon
multiline_comment|/* For 32 MiB Aper size, 8 should be the default */
DECL|variable|__initdata
r_static
id|u32
id|voffset
id|__initdata
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|i810fb_cursor
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_cursor
op_star
id|cursor
)paren
suffix:semicolon
multiline_comment|/* Chipset Specific Functions */
r_static
r_int
id|i810fb_set_par
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|i810fb_getcolreg
(paren
id|u8
id|regno
comma
id|u8
op_star
id|red
comma
id|u8
op_star
id|green
comma
id|u8
op_star
id|blue
comma
id|u8
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|i810fb_setcolreg
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
suffix:semicolon
r_static
r_int
id|i810fb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|i810fb_blank
(paren
r_int
id|blank_mode
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* Initialization */
r_static
r_void
id|i810fb_release_resource
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|i810fb_par
op_star
id|par
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|agp_intel_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Video Timings */
r_extern
r_void
id|round_off_xres
(paren
id|u32
op_star
id|xres
)paren
suffix:semicolon
r_extern
r_void
id|round_off_yres
(paren
id|u32
op_star
id|xres
comma
id|u32
op_star
id|yres
)paren
suffix:semicolon
r_extern
id|u32
id|i810_get_watermark
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|i810fb_par
op_star
id|par
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_encode_registers
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|i810fb_par
op_star
id|par
comma
id|u32
id|xres
comma
id|u32
id|yres
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_fill_var_timings
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
multiline_comment|/* Accelerated Functions */
r_extern
r_void
id|i810fb_fillrect
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_copyarea
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_const
r_struct
id|fb_copyarea
op_star
id|region
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|p
comma
r_const
r_struct
id|fb_image
op_star
id|image
)paren
suffix:semicolon
r_extern
r_int
id|i810fb_sync
(paren
r_struct
id|fb_info
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_init_ringbuffer
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|i810fb_load_front
(paren
id|u32
id|offset
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* Conditionals */
macro_line|#if defined(__i386__)
DECL|function|flush_cache
r_inline
r_void
id|flush_cache
c_func
(paren
r_void
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;wbinvd&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|flush_cache
mdefine_line|#define flush_cache() do { } while(0)
macro_line|#endif 
macro_line|#ifdef CONFIG_MTRR
DECL|macro|KERNEL_HAS_MTRR
mdefine_line|#define KERNEL_HAS_MTRR 1
DECL|function|set_mtrr
r_static
r_inline
r_void
id|__init
id|set_mtrr
c_func
(paren
r_struct
id|i810fb_par
op_star
id|par
)paren
(brace
id|par-&gt;mtrr_reg
op_assign
id|mtrr_add
c_func
(paren
(paren
id|u32
)paren
id|par-&gt;aperture.physical
comma
id|par-&gt;aperture.size
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;mtrr_reg
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;set_mtrr: unable to set MTRR/n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|par-&gt;dev_flags
op_or_assign
id|HAS_MTRR
suffix:semicolon
)brace
DECL|function|unset_mtrr
r_static
r_inline
r_void
id|unset_mtrr
c_func
(paren
r_struct
id|i810fb_par
op_star
id|par
)paren
(brace
r_if
c_cond
(paren
id|par-&gt;dev_flags
op_amp
id|HAS_MTRR
)paren
id|mtrr_del
c_func
(paren
id|par-&gt;mtrr_reg
comma
(paren
id|u32
)paren
id|par-&gt;aperture.physical
comma
id|par-&gt;aperture.size
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|KERNEL_HAS_MTRR
mdefine_line|#define KERNEL_HAS_MTRR 0
DECL|macro|set_mtrr
mdefine_line|#define set_mtrr(x) printk(&quot;set_mtrr: MTRR is disabled in the kernel&bslash;n&quot;)
DECL|macro|unset_mtrr
mdefine_line|#define unset_mtrr(x) do { } while (0)
macro_line|#endif /* CONFIG_MTRR */
macro_line|#ifdef CONFIG_FB_I810_GTF
DECL|macro|IS_DVT
mdefine_line|#define IS_DVT (0)
macro_line|#else
DECL|macro|IS_DVT
mdefine_line|#define IS_DVT (1)
macro_line|#endif
macro_line|#endif /* __I810_MAIN_H__ */
eof
