multiline_comment|/* p9100.c: P9100 frame buffer driver&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; * Copyright 1999 Derrick J Brashear (shadow@dementia.org)&n; *&n; * Driver layout based loosely on tgafb.c, see that file for credits.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &quot;sbuslib.h&quot;
multiline_comment|/*&n; * Local functions.&n; */
r_static
r_int
id|p9100_setcolreg
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|p9100_blank
c_func
(paren
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
r_static
r_int
id|p9100_mmap
c_func
(paren
r_struct
id|fb_info
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_static
r_int
id|p9100_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *  Frame buffer operations&n; */
DECL|variable|p9100_ops
r_static
r_struct
id|fb_ops
id|p9100_ops
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
id|p9100_setcolreg
comma
dot
id|fb_blank
op_assign
id|p9100_blank
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
dot
id|fb_mmap
op_assign
id|p9100_mmap
comma
dot
id|fb_ioctl
op_assign
id|p9100_ioctl
comma
dot
id|fb_cursor
op_assign
id|soft_cursor
comma
)brace
suffix:semicolon
multiline_comment|/* P9100 control registers */
DECL|macro|P9100_SYSCTL_OFF
mdefine_line|#define P9100_SYSCTL_OFF&t;0x0UL
DECL|macro|P9100_VIDEOCTL_OFF
mdefine_line|#define P9100_VIDEOCTL_OFF&t;0x100UL
DECL|macro|P9100_VRAMCTL_OFF
mdefine_line|#define P9100_VRAMCTL_OFF &t;0x180UL
DECL|macro|P9100_RAMDAC_OFF
mdefine_line|#define P9100_RAMDAC_OFF &t;0x200UL
DECL|macro|P9100_VIDEOCOPROC_OFF
mdefine_line|#define P9100_VIDEOCOPROC_OFF &t;0x400UL
multiline_comment|/* P9100 command registers */
DECL|macro|P9100_CMD_OFF
mdefine_line|#define P9100_CMD_OFF 0x0UL
multiline_comment|/* P9100 framebuffer memory */
DECL|macro|P9100_FB_OFF
mdefine_line|#define P9100_FB_OFF 0x0UL
multiline_comment|/* 3 bits: 2=8bpp 3=16bpp 5=32bpp 7=24bpp */
DECL|macro|SYS_CONFIG_PIXELSIZE_SHIFT
mdefine_line|#define SYS_CONFIG_PIXELSIZE_SHIFT 26 
DECL|macro|SCREENPAINT_TIMECTL1_ENABLE_VIDEO
mdefine_line|#define SCREENPAINT_TIMECTL1_ENABLE_VIDEO 0x20 /* 0 = off, 1 = on */
DECL|struct|p9100_regs
r_struct
id|p9100_regs
(brace
multiline_comment|/* Registers for the system control */
DECL|member|sys_base
r_volatile
id|u32
id|sys_base
suffix:semicolon
DECL|member|sys_config
r_volatile
id|u32
id|sys_config
suffix:semicolon
DECL|member|sys_intr
r_volatile
id|u32
id|sys_intr
suffix:semicolon
DECL|member|sys_int_ena
r_volatile
id|u32
id|sys_int_ena
suffix:semicolon
DECL|member|sys_alt_rd
r_volatile
id|u32
id|sys_alt_rd
suffix:semicolon
DECL|member|sys_alt_wr
r_volatile
id|u32
id|sys_alt_wr
suffix:semicolon
DECL|member|sys_xxx
r_volatile
id|u32
id|sys_xxx
(braket
l_int|58
)braket
suffix:semicolon
multiline_comment|/* Registers for the video control */
DECL|member|vid_base
r_volatile
id|u32
id|vid_base
suffix:semicolon
DECL|member|vid_hcnt
r_volatile
id|u32
id|vid_hcnt
suffix:semicolon
DECL|member|vid_htotal
r_volatile
id|u32
id|vid_htotal
suffix:semicolon
DECL|member|vid_hsync_rise
r_volatile
id|u32
id|vid_hsync_rise
suffix:semicolon
DECL|member|vid_hblank_rise
r_volatile
id|u32
id|vid_hblank_rise
suffix:semicolon
DECL|member|vid_hblank_fall
r_volatile
id|u32
id|vid_hblank_fall
suffix:semicolon
DECL|member|vid_hcnt_preload
r_volatile
id|u32
id|vid_hcnt_preload
suffix:semicolon
DECL|member|vid_vcnt
r_volatile
id|u32
id|vid_vcnt
suffix:semicolon
DECL|member|vid_vlen
r_volatile
id|u32
id|vid_vlen
suffix:semicolon
DECL|member|vid_vsync_rise
r_volatile
id|u32
id|vid_vsync_rise
suffix:semicolon
DECL|member|vid_vblank_rise
r_volatile
id|u32
id|vid_vblank_rise
suffix:semicolon
DECL|member|vid_vblank_fall
r_volatile
id|u32
id|vid_vblank_fall
suffix:semicolon
DECL|member|vid_vcnt_preload
r_volatile
id|u32
id|vid_vcnt_preload
suffix:semicolon
DECL|member|vid_screenpaint_addr
r_volatile
id|u32
id|vid_screenpaint_addr
suffix:semicolon
DECL|member|vid_screenpaint_timectl1
r_volatile
id|u32
id|vid_screenpaint_timectl1
suffix:semicolon
DECL|member|vid_screenpaint_qsfcnt
r_volatile
id|u32
id|vid_screenpaint_qsfcnt
suffix:semicolon
DECL|member|vid_screenpaint_timectl2
r_volatile
id|u32
id|vid_screenpaint_timectl2
suffix:semicolon
DECL|member|vid_xxx
r_volatile
id|u32
id|vid_xxx
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* Registers for the video control */
DECL|member|vram_base
r_volatile
id|u32
id|vram_base
suffix:semicolon
DECL|member|vram_memcfg
r_volatile
id|u32
id|vram_memcfg
suffix:semicolon
DECL|member|vram_refresh_pd
r_volatile
id|u32
id|vram_refresh_pd
suffix:semicolon
DECL|member|vram_refresh_cnt
r_volatile
id|u32
id|vram_refresh_cnt
suffix:semicolon
DECL|member|vram_raslo_max
r_volatile
id|u32
id|vram_raslo_max
suffix:semicolon
DECL|member|vram_raslo_cur
r_volatile
id|u32
id|vram_raslo_cur
suffix:semicolon
DECL|member|pwrup_cfg
r_volatile
id|u32
id|pwrup_cfg
suffix:semicolon
DECL|member|vram_xxx
r_volatile
id|u32
id|vram_xxx
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* Registers for IBM RGB528 Palette */
DECL|member|ramdac_cmap_wridx
r_volatile
id|u32
id|ramdac_cmap_wridx
suffix:semicolon
DECL|member|ramdac_palette_data
r_volatile
id|u32
id|ramdac_palette_data
suffix:semicolon
DECL|member|ramdac_pixel_mask
r_volatile
id|u32
id|ramdac_pixel_mask
suffix:semicolon
DECL|member|ramdac_palette_rdaddr
r_volatile
id|u32
id|ramdac_palette_rdaddr
suffix:semicolon
DECL|member|ramdac_idx_lo
r_volatile
id|u32
id|ramdac_idx_lo
suffix:semicolon
DECL|member|ramdac_idx_hi
r_volatile
id|u32
id|ramdac_idx_hi
suffix:semicolon
DECL|member|ramdac_idx_data
r_volatile
id|u32
id|ramdac_idx_data
suffix:semicolon
DECL|member|ramdac_idx_ctl
r_volatile
id|u32
id|ramdac_idx_ctl
suffix:semicolon
DECL|member|ramdac_xxx
r_volatile
id|u32
id|ramdac_xxx
(braket
l_int|1784
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|p9100_cmd_parameng
r_struct
id|p9100_cmd_parameng
(brace
DECL|member|parameng_status
r_volatile
id|u32
id|parameng_status
suffix:semicolon
DECL|member|parameng_bltcmd
r_volatile
id|u32
id|parameng_bltcmd
suffix:semicolon
DECL|member|parameng_quadcmd
r_volatile
id|u32
id|parameng_quadcmd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|p9100_par
r_struct
id|p9100_par
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|regs
r_struct
id|p9100_regs
op_star
id|regs
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|macro|P9100_FLAG_BLANKED
mdefine_line|#define P9100_FLAG_BLANKED&t;0x00000001
DECL|member|physbase
r_int
r_int
id|physbase
suffix:semicolon
DECL|member|fbsize
r_int
r_int
id|fbsize
suffix:semicolon
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *      p9100_setcolreg - Optional function. Sets a color register.&n; *      @regno: boolean, 0 copy local, 1 get_user() function&n; *      @red: frame buffer colormap structure&n; *      @green: The green value which can be up to 16 bits wide&n; *      @blue:  The blue value which can be up to 16 bits wide.&n; *      @transp: If supported the alpha value which can be up to 16 bits wide.&n; *      @info: frame buffer info structure&n; */
DECL|function|p9100_setcolreg
r_static
r_int
id|p9100_setcolreg
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
r_struct
id|p9100_par
op_star
id|par
op_assign
(paren
r_struct
id|p9100_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|p9100_regs
op_star
id|regs
op_assign
id|par-&gt;regs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|regno
op_ge
l_int|256
)paren
r_return
l_int|1
suffix:semicolon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
(paren
id|regno
op_lshift
l_int|16
)paren
comma
op_amp
id|regs-&gt;ramdac_cmap_wridx
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
(paren
id|red
op_lshift
l_int|16
)paren
comma
op_amp
id|regs-&gt;ramdac_palette_data
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
(paren
id|green
op_lshift
l_int|16
)paren
comma
op_amp
id|regs-&gt;ramdac_palette_data
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
(paren
id|blue
op_lshift
l_int|16
)paren
comma
op_amp
id|regs-&gt;ramdac_palette_data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      p9100_blank - Optional function.  Blanks the display.&n; *      @blank_mode: the blank mode we want.&n; *      @info: frame buffer structure that represents a single frame buffer&n; */
r_static
r_int
DECL|function|p9100_blank
id|p9100_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|p9100_par
op_star
id|par
op_assign
(paren
r_struct
id|p9100_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|p9100_regs
op_star
id|regs
op_assign
id|par-&gt;regs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|blank
)paren
(brace
r_case
id|FB_BLANK_UNBLANK
suffix:colon
multiline_comment|/* Unblanking */
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|regs-&gt;vid_screenpaint_timectl1
)paren
suffix:semicolon
id|val
op_or_assign
id|SCREENPAINT_TIMECTL1_ENABLE_VIDEO
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|regs-&gt;vid_screenpaint_timectl1
)paren
suffix:semicolon
id|par-&gt;flags
op_and_assign
op_complement
id|P9100_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FB_BLANK_NORMAL
suffix:colon
multiline_comment|/* Normal blanking */
r_case
id|FB_BLANK_VSYNC_SUSPEND
suffix:colon
multiline_comment|/* VESA blank (vsync off) */
r_case
id|FB_BLANK_HSYNC_SUSPEND
suffix:colon
multiline_comment|/* VESA blank (hsync off) */
r_case
id|FB_BLANK_POWERDOWN
suffix:colon
multiline_comment|/* Poweroff */
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|regs-&gt;vid_screenpaint_timectl1
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|SCREENPAINT_TIMECTL1_ENABLE_VIDEO
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|regs-&gt;vid_screenpaint_timectl1
)paren
suffix:semicolon
id|par-&gt;flags
op_or_assign
id|P9100_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|p9100_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|p9100_mmap_map
(braket
)braket
op_assign
(brace
(brace
id|CG3_MMAP_OFFSET
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|p9100_mmap
r_static
r_int
id|p9100_mmap
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
id|p9100_par
op_star
id|par
op_assign
(paren
r_struct
id|p9100_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_return
id|sbusfb_mmap_helper
c_func
(paren
id|p9100_mmap_map
comma
id|par-&gt;physbase
comma
id|par-&gt;fbsize
comma
id|par-&gt;sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|p9100_ioctl
r_static
r_int
id|p9100_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|p9100_par
op_star
id|par
op_assign
(paren
r_struct
id|p9100_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
multiline_comment|/* Make it look like a cg3. */
r_return
id|sbusfb_ioctl_helper
c_func
(paren
id|cmd
comma
id|arg
comma
id|info
comma
id|FBTYPE_SUN3COLOR
comma
l_int|8
comma
id|par-&gt;fbsize
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialisation&n; */
r_static
r_void
DECL|function|p9100_init_fix
id|p9100_init_fix
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|linebytes
)paren
(brace
r_struct
id|p9100_par
op_star
id|par
op_assign
(paren
r_struct
id|p9100_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
id|strlcpy
c_func
(paren
id|info-&gt;fix.id
comma
id|par-&gt;sdev-&gt;prom_name
comma
r_sizeof
(paren
id|info-&gt;fix.id
)paren
)paren
suffix:semicolon
id|info-&gt;fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|info-&gt;fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|info-&gt;fix.line_length
op_assign
id|linebytes
suffix:semicolon
id|info-&gt;fix.accel
op_assign
id|FB_ACCEL_SUN_CGTHREE
suffix:semicolon
)brace
DECL|struct|all_info
r_struct
id|all_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|par
r_struct
id|p9100_par
id|par
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|p9100_list
)paren
suffix:semicolon
DECL|function|p9100_init_one
r_static
r_void
id|p9100_init_one
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
)paren
(brace
r_struct
id|all_info
op_star
id|all
suffix:semicolon
r_int
id|linebytes
suffix:semicolon
id|all
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|all
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;p9100: Cannot allocate memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
c_func
(paren
id|all
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|all
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|all-&gt;list
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|all-&gt;par.lock
)paren
suffix:semicolon
id|all-&gt;par.sdev
op_assign
id|sdev
suffix:semicolon
multiline_comment|/* This is the framebuffer and the only resource apps can mmap.  */
id|all-&gt;par.physbase
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|2
)braket
dot
id|phys_addr
suffix:semicolon
id|sbusfb_fill_var
c_func
(paren
op_amp
id|all-&gt;info.var
comma
id|sdev-&gt;prom_node
comma
l_int|8
)paren
suffix:semicolon
id|linebytes
op_assign
id|prom_getintdefault
c_func
(paren
id|sdev-&gt;prom_node
comma
l_string|&quot;linebytes&quot;
comma
id|all-&gt;info.var.xres
)paren
suffix:semicolon
id|all-&gt;par.fbsize
op_assign
id|PAGE_ALIGN
c_func
(paren
id|linebytes
op_star
id|all-&gt;info.var.yres
)paren
suffix:semicolon
id|all-&gt;par.regs
op_assign
(paren
r_struct
id|p9100_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|p9100_regs
)paren
comma
l_string|&quot;p9100 regs&quot;
)paren
suffix:semicolon
id|all-&gt;info.flags
op_assign
id|FBINFO_DEFAULT
suffix:semicolon
id|all-&gt;info.fbops
op_assign
op_amp
id|p9100_ops
suffix:semicolon
macro_line|#ifdef CONFIG_SPARC32
id|all-&gt;info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|prom_getintdefault
c_func
(paren
id|sdev-&gt;prom_node
comma
l_string|&quot;address&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|all-&gt;info.screen_base
)paren
id|all-&gt;info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|2
)braket
comma
l_int|0
comma
id|all-&gt;par.fbsize
comma
l_string|&quot;p9100 ram&quot;
)paren
suffix:semicolon
id|all-&gt;info.par
op_assign
op_amp
id|all-&gt;par
suffix:semicolon
id|p9100_blank
c_func
(paren
l_int|0
comma
op_amp
id|all-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fb_alloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
comma
l_int|256
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;p9100: Could not allocate color map.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p9100_init_fix
c_func
(paren
op_amp
id|all-&gt;info
comma
id|linebytes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|all-&gt;info
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;p9100: Could not register framebuffer.&bslash;n&quot;
)paren
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|all-&gt;list
comma
op_amp
id|p9100_list
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;p9100: %s at %lx:%lx&bslash;n&quot;
comma
id|sdev-&gt;prom_name
comma
(paren
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
comma
(paren
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
suffix:semicolon
)brace
DECL|function|p9100_init
r_int
id|__init
id|p9100_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
r_if
c_cond
(paren
id|fb_get_options
c_func
(paren
l_string|&quot;p9100fb&quot;
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;p9100&quot;
)paren
)paren
id|p9100_init_one
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|p9100_exit
r_void
id|__exit
id|p9100_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|p9100_list
)paren
(brace
r_struct
id|all_info
op_star
id|all
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|all
)paren
comma
id|list
)paren
suffix:semicolon
id|unregister_framebuffer
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
id|fb_dealloc_cmap
c_func
(paren
op_amp
id|all-&gt;info.cmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|all
)paren
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|p9100_setup
id|p9100_setup
c_func
(paren
r_char
op_star
id|arg
)paren
(brace
multiline_comment|/* No cmdline options yet... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|p9100_init
id|module_init
c_func
(paren
id|p9100_init
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|p9100_exit
id|module_exit
c_func
(paren
id|p9100_exit
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;framebuffer driver for P9100 chipsets&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David S. Miller &lt;davem@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
