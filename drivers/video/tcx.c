multiline_comment|/* tcx.c: TCX frame buffer driver&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; *&n; * Driver layout based loosely on tgafb.c, see that file for credits.&n; */
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
id|tcx_setcolreg
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
id|tcx_blank
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
id|tcx_mmap
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
id|tcx_ioctl
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
DECL|variable|tcx_ops
r_static
r_struct
id|fb_ops
id|tcx_ops
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
id|tcx_setcolreg
comma
dot
id|fb_blank
op_assign
id|tcx_blank
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
id|tcx_mmap
comma
dot
id|fb_ioctl
op_assign
id|tcx_ioctl
comma
dot
id|fb_cursor
op_assign
id|soft_cursor
comma
)brace
suffix:semicolon
multiline_comment|/* THC definitions */
DECL|macro|TCX_THC_MISC_REV_SHIFT
mdefine_line|#define TCX_THC_MISC_REV_SHIFT       16
DECL|macro|TCX_THC_MISC_REV_MASK
mdefine_line|#define TCX_THC_MISC_REV_MASK        15
DECL|macro|TCX_THC_MISC_VSYNC_DIS
mdefine_line|#define TCX_THC_MISC_VSYNC_DIS       (1 &lt;&lt; 25)
DECL|macro|TCX_THC_MISC_HSYNC_DIS
mdefine_line|#define TCX_THC_MISC_HSYNC_DIS       (1 &lt;&lt; 24)
DECL|macro|TCX_THC_MISC_RESET
mdefine_line|#define TCX_THC_MISC_RESET           (1 &lt;&lt; 12)
DECL|macro|TCX_THC_MISC_VIDEO
mdefine_line|#define TCX_THC_MISC_VIDEO           (1 &lt;&lt; 10)
DECL|macro|TCX_THC_MISC_SYNC
mdefine_line|#define TCX_THC_MISC_SYNC            (1 &lt;&lt; 9)
DECL|macro|TCX_THC_MISC_VSYNC
mdefine_line|#define TCX_THC_MISC_VSYNC           (1 &lt;&lt; 8)
DECL|macro|TCX_THC_MISC_SYNC_ENAB
mdefine_line|#define TCX_THC_MISC_SYNC_ENAB       (1 &lt;&lt; 7)
DECL|macro|TCX_THC_MISC_CURS_RES
mdefine_line|#define TCX_THC_MISC_CURS_RES        (1 &lt;&lt; 6)
DECL|macro|TCX_THC_MISC_INT_ENAB
mdefine_line|#define TCX_THC_MISC_INT_ENAB        (1 &lt;&lt; 5)
DECL|macro|TCX_THC_MISC_INT
mdefine_line|#define TCX_THC_MISC_INT             (1 &lt;&lt; 4)
DECL|macro|TCX_THC_MISC_INIT
mdefine_line|#define TCX_THC_MISC_INIT            0x9f
DECL|macro|TCX_THC_REV_REV_SHIFT
mdefine_line|#define TCX_THC_REV_REV_SHIFT        20
DECL|macro|TCX_THC_REV_REV_MASK
mdefine_line|#define TCX_THC_REV_REV_MASK         15
DECL|macro|TCX_THC_REV_MINREV_SHIFT
mdefine_line|#define TCX_THC_REV_MINREV_SHIFT     28
DECL|macro|TCX_THC_REV_MINREV_MASK
mdefine_line|#define TCX_THC_REV_MINREV_MASK      15
multiline_comment|/* The contents are unknown */
DECL|struct|tcx_tec
r_struct
id|tcx_tec
(brace
DECL|member|tec_matrix
r_volatile
id|u32
id|tec_matrix
suffix:semicolon
DECL|member|tec_clip
r_volatile
id|u32
id|tec_clip
suffix:semicolon
DECL|member|tec_vdc
r_volatile
id|u32
id|tec_vdc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcx_thc
r_struct
id|tcx_thc
(brace
DECL|member|thc_rev
r_volatile
id|u32
id|thc_rev
suffix:semicolon
DECL|member|thc_pad0
id|u32
id|thc_pad0
(braket
l_int|511
)braket
suffix:semicolon
DECL|member|thc_hs
r_volatile
id|u32
id|thc_hs
suffix:semicolon
multiline_comment|/* hsync timing */
DECL|member|thc_hsdvs
r_volatile
id|u32
id|thc_hsdvs
suffix:semicolon
DECL|member|thc_hd
r_volatile
id|u32
id|thc_hd
suffix:semicolon
DECL|member|thc_vs
r_volatile
id|u32
id|thc_vs
suffix:semicolon
multiline_comment|/* vsync timing */
DECL|member|thc_vd
r_volatile
id|u32
id|thc_vd
suffix:semicolon
DECL|member|thc_refresh
r_volatile
id|u32
id|thc_refresh
suffix:semicolon
DECL|member|thc_misc
r_volatile
id|u32
id|thc_misc
suffix:semicolon
DECL|member|thc_pad1
id|u32
id|thc_pad1
(braket
l_int|56
)braket
suffix:semicolon
DECL|member|thc_cursxy
r_volatile
id|u32
id|thc_cursxy
suffix:semicolon
multiline_comment|/* cursor x,y position (16 bits each) */
DECL|member|thc_cursmask
r_volatile
id|u32
id|thc_cursmask
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* cursor mask bits */
DECL|member|thc_cursbits
r_volatile
id|u32
id|thc_cursbits
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* what to show where mask enabled */
)brace
suffix:semicolon
DECL|struct|bt_regs
r_struct
id|bt_regs
(brace
DECL|member|addr
r_volatile
id|u32
id|addr
suffix:semicolon
DECL|member|color_map
r_volatile
id|u32
id|color_map
suffix:semicolon
DECL|member|control
r_volatile
id|u32
id|control
suffix:semicolon
DECL|member|cursor
r_volatile
id|u32
id|cursor
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TCX_MMAP_ENTRIES
mdefine_line|#define TCX_MMAP_ENTRIES 14
DECL|struct|tcx_par
r_struct
id|tcx_par
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|bt
r_struct
id|bt_regs
op_star
id|bt
suffix:semicolon
DECL|member|thc
r_struct
id|tcx_thc
op_star
id|thc
suffix:semicolon
DECL|member|tec
r_struct
id|tcx_tec
op_star
id|tec
suffix:semicolon
DECL|member|cplane
r_volatile
id|u32
op_star
id|cplane
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|macro|TCX_FLAG_BLANKED
mdefine_line|#define TCX_FLAG_BLANKED&t;0x00000001
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
DECL|member|mmap_map
r_struct
id|sbus_mmap_map
id|mmap_map
(braket
id|TCX_MMAP_ENTRIES
)braket
suffix:semicolon
DECL|member|lowdepth
r_int
id|lowdepth
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
multiline_comment|/* Reset control plane so that WID is 8-bit plane. */
DECL|function|__tcx_set_control_plane
r_static
r_void
id|__tcx_set_control_plane
(paren
r_struct
id|tcx_par
op_star
id|par
)paren
(brace
r_volatile
id|u32
op_star
id|p
comma
op_star
id|pend
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;lowdepth
)paren
r_return
suffix:semicolon
id|p
op_assign
id|par-&gt;cplane
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|pend
op_assign
id|p
op_plus
id|par-&gt;fbsize
suffix:semicolon
id|p
OL
id|pend
suffix:semicolon
id|p
op_increment
)paren
(brace
id|u32
id|tmp
op_assign
id|sbus_readl
c_func
(paren
id|p
)paren
suffix:semicolon
id|tmp
op_and_assign
l_int|0xffffff
suffix:semicolon
id|sbus_writel
c_func
(paren
id|tmp
comma
id|p
)paren
suffix:semicolon
)brace
)brace
DECL|function|tcx_reset
r_static
r_void
id|tcx_reset
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_int
r_int
id|flags
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
id|__tcx_set_control_plane
c_func
(paren
id|par
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
)brace
multiline_comment|/**&n; *      tcx_setcolreg - Optional function. Sets a color register.&n; *      @regno: boolean, 0 copy local, 1 get_user() function&n; *      @red: frame buffer colormap structure&n; *      @green: The green value which can be up to 16 bits wide&n; *      @blue:  The blue value which can be up to 16 bits wide.&n; *      @transp: If supported the alpha value which can be up to 16 bits wide.&n; *      @info: frame buffer info structure&n; */
DECL|function|tcx_setcolreg
r_static
r_int
id|tcx_setcolreg
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
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|bt_regs
op_star
id|bt
op_assign
id|par-&gt;bt
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
id|regno
op_lshift
l_int|24
comma
op_amp
id|bt-&gt;addr
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|red
op_lshift
l_int|24
comma
op_amp
id|bt-&gt;color_map
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|green
op_lshift
l_int|24
comma
op_amp
id|bt-&gt;color_map
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
id|blue
op_lshift
l_int|24
comma
op_amp
id|bt-&gt;color_map
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
multiline_comment|/**&n; *      tcx_blank - Optional function.  Blanks the display.&n; *      @blank_mode: the blank mode we want.&n; *      @info: frame buffer structure that represents a single frame buffer&n; */
r_static
r_int
DECL|function|tcx_blank
id|tcx_blank
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
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|tcx_thc
op_star
id|thc
op_assign
id|par-&gt;thc
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
id|val
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|thc-&gt;thc_misc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|blank
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Unblanking */
id|val
op_and_assign
op_complement
(paren
id|TCX_THC_MISC_VSYNC_DIS
op_or
id|TCX_THC_MISC_HSYNC_DIS
)paren
suffix:semicolon
id|val
op_or_assign
id|TCX_THC_MISC_VIDEO
suffix:semicolon
id|par-&gt;flags
op_and_assign
op_complement
id|TCX_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Normal blanking */
id|val
op_and_assign
op_complement
id|TCX_THC_MISC_VIDEO
suffix:semicolon
id|par-&gt;flags
op_or_assign
id|TCX_FLAG_BLANKED
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* VESA blank (vsync off) */
id|val
op_or_assign
id|TCX_THC_MISC_VSYNC_DIS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* VESA blank (hsync off) */
id|val
op_or_assign
id|TCX_THC_MISC_HSYNC_DIS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Poweroff */
r_break
suffix:semicolon
)brace
suffix:semicolon
id|sbus_writel
c_func
(paren
id|val
comma
op_amp
id|thc-&gt;thc_misc
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
DECL|variable|__tcx_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|__tcx_mmap_map
(braket
id|TCX_MMAP_ENTRIES
)braket
op_assign
(brace
(brace
id|TCX_RAM8BIT
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
id|TCX_RAM24BIT
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|4
)paren
)brace
comma
(brace
id|TCX_UNK3
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_UNK4
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_CONTROLPLANE
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|4
)paren
)brace
comma
(brace
id|TCX_UNK6
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_UNK7
comma
l_int|0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|8
)paren
)brace
comma
(brace
id|TCX_TEC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_BTREGS
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_THC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_DHC
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_ALT
comma
l_int|0
comma
id|PAGE_SIZE
)brace
comma
(brace
id|TCX_UNK2
comma
l_int|0
comma
l_int|0x20000
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
DECL|function|tcx_mmap
r_static
r_int
id|tcx_mmap
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
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_return
id|sbusfb_mmap_helper
c_func
(paren
id|par-&gt;mmap_map
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
DECL|function|tcx_ioctl
r_static
r_int
id|tcx_ioctl
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
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_return
id|sbusfb_ioctl_helper
c_func
(paren
id|cmd
comma
id|info
comma
id|FBTYPE_TCXCOLOR
comma
(paren
id|par-&gt;lowdepth
ques
c_cond
l_int|8
suffix:colon
l_int|24
)paren
comma
id|par-&gt;fbsize
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialisation&n; */
r_static
r_void
DECL|function|tcx_init_fix
id|tcx_init_fix
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
id|tcx_par
op_star
id|par
op_assign
(paren
r_struct
id|tcx_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_const
r_char
op_star
id|tcx_name
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;lowdepth
)paren
id|tcx_name
op_assign
l_string|&quot;TCX8&quot;
suffix:semicolon
r_else
id|tcx_name
op_assign
l_string|&quot;TCX24&quot;
suffix:semicolon
id|strncpy
c_func
(paren
id|info-&gt;fix.id
comma
id|tcx_name
comma
r_sizeof
(paren
id|info-&gt;fix.id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|info-&gt;fix.id
(braket
r_sizeof
(paren
id|info-&gt;fix.id
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
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
id|FB_ACCEL_SUN_TCX
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
id|tcx_par
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
id|tcx_list
)paren
suffix:semicolon
DECL|function|tcx_init_one
r_static
r_void
id|tcx_init_one
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
comma
id|i
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
l_string|&quot;tcx: Cannot allocate memory.&bslash;n&quot;
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
id|all-&gt;par.lowdepth
op_assign
id|prom_getbool
c_func
(paren
id|sdev-&gt;prom_node
comma
l_string|&quot;tcx-8-bit&quot;
)paren
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
id|all-&gt;par.tec
op_assign
(paren
r_struct
id|tcx_tec
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|7
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tcx_tec
)paren
comma
l_string|&quot;tcx tec&quot;
)paren
suffix:semicolon
id|all-&gt;par.thc
op_assign
(paren
r_struct
id|tcx_thc
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|9
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tcx_thc
)paren
comma
l_string|&quot;tcx thc&quot;
)paren
suffix:semicolon
id|all-&gt;par.bt
op_assign
(paren
r_struct
id|bt_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|8
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bt_regs
)paren
comma
l_string|&quot;tcx dac&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|all-&gt;par.mmap_map
comma
op_amp
id|__tcx_mmap_map
comma
r_sizeof
(paren
id|all-&gt;par.mmap_map
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|all-&gt;par.lowdepth
)paren
(brace
id|all-&gt;par.cplane
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|4
)braket
comma
l_int|0
comma
id|all-&gt;par.fbsize
op_star
r_sizeof
(paren
id|u32
)paren
comma
l_string|&quot;tcx cplane&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|all-&gt;par.mmap_map
(braket
l_int|1
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|all-&gt;par.mmap_map
(braket
l_int|4
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|all-&gt;par.mmap_map
(braket
l_int|5
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
id|all-&gt;par.mmap_map
(braket
l_int|6
)braket
dot
id|size
op_assign
id|SBUS_MMAP_EMPTY
suffix:semicolon
)brace
id|all-&gt;par.physbase
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
id|i
OL
id|TCX_MMAP_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|10
suffix:colon
id|j
op_assign
l_int|12
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
r_case
l_int|12
suffix:colon
id|j
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|j
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|all-&gt;par.mmap_map
(braket
id|i
)braket
dot
id|poff
op_assign
id|sdev-&gt;reg_addrs
(braket
id|j
)braket
dot
id|phys_addr
suffix:semicolon
)brace
id|all-&gt;info.node
op_assign
id|NODEV
suffix:semicolon
id|all-&gt;info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|all-&gt;info.fbops
op_assign
op_amp
id|tcx_ops
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
l_int|0
)braket
comma
l_int|0
comma
id|all-&gt;par.fbsize
comma
l_string|&quot;tcx ram&quot;
)paren
suffix:semicolon
id|all-&gt;info.currcon
op_assign
op_minus
l_int|1
suffix:semicolon
id|all-&gt;info.par
op_assign
op_amp
id|all-&gt;par
suffix:semicolon
multiline_comment|/* Initialize brooktree DAC. */
id|sbus_writel
c_func
(paren
l_int|0x04
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;addr
)paren
suffix:semicolon
multiline_comment|/* color planes */
id|sbus_writel
c_func
(paren
l_int|0xff
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;control
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x05
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;addr
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x00
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;control
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x06
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;addr
)paren
suffix:semicolon
multiline_comment|/* overlay plane */
id|sbus_writel
c_func
(paren
l_int|0x73
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;control
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x07
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;addr
)paren
suffix:semicolon
id|sbus_writel
c_func
(paren
l_int|0x00
op_lshift
l_int|24
comma
op_amp
id|all-&gt;par.bt-&gt;control
)paren
suffix:semicolon
id|tcx_reset
c_func
(paren
op_amp
id|all-&gt;info
)paren
suffix:semicolon
id|tcx_blank
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
l_string|&quot;tcx: Could not allocate color map.&bslash;n&quot;
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
id|tcx_init_fix
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
l_string|&quot;tcx: Could not register framebuffer.&bslash;n&quot;
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
id|tcx_list
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tcx: %s at %lx:%lx, %s&bslash;n&quot;
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
comma
id|all-&gt;par.lowdepth
ques
c_cond
l_string|&quot;8-bit only&quot;
suffix:colon
l_string|&quot;24-bit depth&quot;
)paren
suffix:semicolon
)brace
DECL|function|tcx_init
r_int
id|__init
id|tcx_init
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
l_string|&quot;tcx&quot;
)paren
)paren
id|tcx_init_one
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
DECL|function|tcx_exit
r_void
id|__exit
id|tcx_exit
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
id|tcx_list
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
DECL|function|tcx_setup
id|tcx_setup
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
macro_line|#ifdef MODULE
DECL|variable|tcx_init
id|module_init
c_func
(paren
id|tcx_init
)paren
suffix:semicolon
DECL|variable|tcx_exit
id|module_exit
c_func
(paren
id|tcx_exit
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;framebuffer driver for TCX chipsets&quot;
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
