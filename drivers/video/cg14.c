multiline_comment|/* cg14.c: CGFOURTEEN frame buffer driver&n; *&n; * Copyright (C) 2003 David S. Miller (davem@redhat.com)&n; * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *&n; * Driver layout based loosely on tgafb.c, see that file for credits.&n; */
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
id|cg14_setcolreg
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
id|cg14_mmap
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
id|cg14_ioctl
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
r_static
r_int
id|cg14_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *  Frame buffer operations&n; */
DECL|variable|cg14_ops
r_static
r_struct
id|fb_ops
id|cg14_ops
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
id|cg14_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|cg14_pan_display
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
id|cg14_mmap
comma
dot
id|fb_ioctl
op_assign
id|cg14_ioctl
comma
dot
id|fb_cursor
op_assign
id|soft_cursor
comma
)brace
suffix:semicolon
DECL|macro|CG14_MCR_INTENABLE_SHIFT
mdefine_line|#define CG14_MCR_INTENABLE_SHIFT&t;7
DECL|macro|CG14_MCR_INTENABLE_MASK
mdefine_line|#define CG14_MCR_INTENABLE_MASK&t;&t;0x80
DECL|macro|CG14_MCR_VIDENABLE_SHIFT
mdefine_line|#define CG14_MCR_VIDENABLE_SHIFT&t;6
DECL|macro|CG14_MCR_VIDENABLE_MASK
mdefine_line|#define CG14_MCR_VIDENABLE_MASK&t;&t;0x40
DECL|macro|CG14_MCR_PIXMODE_SHIFT
mdefine_line|#define CG14_MCR_PIXMODE_SHIFT&t;&t;4
DECL|macro|CG14_MCR_PIXMODE_MASK
mdefine_line|#define CG14_MCR_PIXMODE_MASK&t;&t;0x30
DECL|macro|CG14_MCR_TMR_SHIFT
mdefine_line|#define CG14_MCR_TMR_SHIFT&t;&t;2
DECL|macro|CG14_MCR_TMR_MASK
mdefine_line|#define CG14_MCR_TMR_MASK&t;&t;0x0c
DECL|macro|CG14_MCR_TMENABLE_SHIFT
mdefine_line|#define CG14_MCR_TMENABLE_SHIFT&t;&t;1
DECL|macro|CG14_MCR_TMENABLE_MASK
mdefine_line|#define CG14_MCR_TMENABLE_MASK&t;&t;0x02
DECL|macro|CG14_MCR_RESET_SHIFT
mdefine_line|#define CG14_MCR_RESET_SHIFT&t;&t;0
DECL|macro|CG14_MCR_RESET_MASK
mdefine_line|#define CG14_MCR_RESET_MASK&t;&t;0x01
DECL|macro|CG14_REV_REVISION_SHIFT
mdefine_line|#define CG14_REV_REVISION_SHIFT&t;&t;4
DECL|macro|CG14_REV_REVISION_MASK
mdefine_line|#define CG14_REV_REVISION_MASK&t;&t;0xf0
DECL|macro|CG14_REV_IMPL_SHIFT
mdefine_line|#define CG14_REV_IMPL_SHIFT&t;&t;0
DECL|macro|CG14_REV_IMPL_MASK
mdefine_line|#define CG14_REV_IMPL_MASK&t;&t;0x0f
DECL|macro|CG14_VBR_FRAMEBASE_SHIFT
mdefine_line|#define CG14_VBR_FRAMEBASE_SHIFT&t;12
DECL|macro|CG14_VBR_FRAMEBASE_MASK
mdefine_line|#define CG14_VBR_FRAMEBASE_MASK&t;&t;0x00fff000
DECL|macro|CG14_VMCR1_SETUP_SHIFT
mdefine_line|#define CG14_VMCR1_SETUP_SHIFT&t;&t;0
DECL|macro|CG14_VMCR1_SETUP_MASK
mdefine_line|#define CG14_VMCR1_SETUP_MASK&t;&t;0x000001ff
DECL|macro|CG14_VMCR1_VCONFIG_SHIFT
mdefine_line|#define CG14_VMCR1_VCONFIG_SHIFT&t;9
DECL|macro|CG14_VMCR1_VCONFIG_MASK
mdefine_line|#define CG14_VMCR1_VCONFIG_MASK&t;&t;0x00000e00
DECL|macro|CG14_VMCR2_REFRESH_SHIFT
mdefine_line|#define CG14_VMCR2_REFRESH_SHIFT&t;0
DECL|macro|CG14_VMCR2_REFRESH_MASK
mdefine_line|#define CG14_VMCR2_REFRESH_MASK&t;&t;0x00000001
DECL|macro|CG14_VMCR2_TESTROWCNT_SHIFT
mdefine_line|#define CG14_VMCR2_TESTROWCNT_SHIFT&t;1
DECL|macro|CG14_VMCR2_TESTROWCNT_MASK
mdefine_line|#define CG14_VMCR2_TESTROWCNT_MASK&t;0x00000002
DECL|macro|CG14_VMCR2_FBCONFIG_SHIFT
mdefine_line|#define CG14_VMCR2_FBCONFIG_SHIFT&t;2
DECL|macro|CG14_VMCR2_FBCONFIG_MASK
mdefine_line|#define CG14_VMCR2_FBCONFIG_MASK&t;0x0000000c
DECL|macro|CG14_VCR_REFRESHREQ_SHIFT
mdefine_line|#define CG14_VCR_REFRESHREQ_SHIFT&t;0
DECL|macro|CG14_VCR_REFRESHREQ_MASK
mdefine_line|#define CG14_VCR_REFRESHREQ_MASK&t;0x000003ff
DECL|macro|CG14_VCR1_REFRESHENA_SHIFT
mdefine_line|#define CG14_VCR1_REFRESHENA_SHIFT&t;10
DECL|macro|CG14_VCR1_REFRESHENA_MASK
mdefine_line|#define CG14_VCR1_REFRESHENA_MASK&t;0x00000400
DECL|macro|CG14_VCA_CAD_SHIFT
mdefine_line|#define CG14_VCA_CAD_SHIFT&t;&t;0
DECL|macro|CG14_VCA_CAD_MASK
mdefine_line|#define CG14_VCA_CAD_MASK&t;&t;0x000003ff
DECL|macro|CG14_VCA_VERS_SHIFT
mdefine_line|#define CG14_VCA_VERS_SHIFT&t;&t;10
DECL|macro|CG14_VCA_VERS_MASK
mdefine_line|#define CG14_VCA_VERS_MASK&t;&t;0x00000c00
DECL|macro|CG14_VCA_RAMSPEED_SHIFT
mdefine_line|#define CG14_VCA_RAMSPEED_SHIFT&t;&t;12
DECL|macro|CG14_VCA_RAMSPEED_MASK
mdefine_line|#define CG14_VCA_RAMSPEED_MASK&t;&t;0x00001000
DECL|macro|CG14_VCA_8MB_SHIFT
mdefine_line|#define CG14_VCA_8MB_SHIFT&t;&t;13
DECL|macro|CG14_VCA_8MB_MASK
mdefine_line|#define CG14_VCA_8MB_MASK&t;&t;0x00002000
DECL|macro|CG14_MCR_PIXMODE_8
mdefine_line|#define CG14_MCR_PIXMODE_8&t;&t;0
DECL|macro|CG14_MCR_PIXMODE_16
mdefine_line|#define CG14_MCR_PIXMODE_16&t;&t;2
DECL|macro|CG14_MCR_PIXMODE_32
mdefine_line|#define CG14_MCR_PIXMODE_32&t;&t;3
DECL|struct|cg14_regs
r_struct
id|cg14_regs
(brace
DECL|member|mcr
r_volatile
id|u8
id|mcr
suffix:semicolon
multiline_comment|/* Master Control Reg */
DECL|member|ppr
r_volatile
id|u8
id|ppr
suffix:semicolon
multiline_comment|/* Packed Pixel Reg */
DECL|member|tms
r_volatile
id|u8
id|tms
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Test Mode Status Regs */
DECL|member|msr
r_volatile
id|u8
id|msr
suffix:semicolon
multiline_comment|/* Master Status Reg */
DECL|member|fsr
r_volatile
id|u8
id|fsr
suffix:semicolon
multiline_comment|/* Fault Status Reg */
DECL|member|rev
r_volatile
id|u8
id|rev
suffix:semicolon
multiline_comment|/* Revision &amp; Impl */
DECL|member|ccr
r_volatile
id|u8
id|ccr
suffix:semicolon
multiline_comment|/* Clock Control Reg */
DECL|member|tmr
r_volatile
id|u32
id|tmr
suffix:semicolon
multiline_comment|/* Test Mode Read Back */
DECL|member|mod
r_volatile
id|u8
id|mod
suffix:semicolon
multiline_comment|/* Monitor Operation Data Reg */
DECL|member|acr
r_volatile
id|u8
id|acr
suffix:semicolon
multiline_comment|/* Aux Control */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|hct
r_volatile
id|u16
id|hct
suffix:semicolon
multiline_comment|/* Hor Counter */
DECL|member|vct
r_volatile
id|u16
id|vct
suffix:semicolon
multiline_comment|/* Vert Counter */
DECL|member|hbs
r_volatile
id|u16
id|hbs
suffix:semicolon
multiline_comment|/* Hor Blank Start */
DECL|member|hbc
r_volatile
id|u16
id|hbc
suffix:semicolon
multiline_comment|/* Hor Blank Clear */
DECL|member|hss
r_volatile
id|u16
id|hss
suffix:semicolon
multiline_comment|/* Hor Sync Start */
DECL|member|hsc
r_volatile
id|u16
id|hsc
suffix:semicolon
multiline_comment|/* Hor Sync Clear */
DECL|member|csc
r_volatile
id|u16
id|csc
suffix:semicolon
multiline_comment|/* Composite Sync Clear */
DECL|member|vbs
r_volatile
id|u16
id|vbs
suffix:semicolon
multiline_comment|/* Vert Blank Start */
DECL|member|vbc
r_volatile
id|u16
id|vbc
suffix:semicolon
multiline_comment|/* Vert Blank Clear */
DECL|member|vss
r_volatile
id|u16
id|vss
suffix:semicolon
multiline_comment|/* Vert Sync Start */
DECL|member|vsc
r_volatile
id|u16
id|vsc
suffix:semicolon
multiline_comment|/* Vert Sync Clear */
DECL|member|xcs
r_volatile
id|u16
id|xcs
suffix:semicolon
DECL|member|xcc
r_volatile
id|u16
id|xcc
suffix:semicolon
DECL|member|fsa
r_volatile
id|u16
id|fsa
suffix:semicolon
multiline_comment|/* Fault Status Address */
DECL|member|adr
r_volatile
id|u16
id|adr
suffix:semicolon
multiline_comment|/* Address Registers */
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|0xce
)braket
suffix:semicolon
DECL|member|pcg
r_volatile
id|u8
id|pcg
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Pixel Clock Generator */
DECL|member|vbr
r_volatile
id|u32
id|vbr
suffix:semicolon
multiline_comment|/* Frame Base Row */
DECL|member|vmcr
r_volatile
id|u32
id|vmcr
suffix:semicolon
multiline_comment|/* VBC Master Control */
DECL|member|vcr
r_volatile
id|u32
id|vcr
suffix:semicolon
multiline_comment|/* VBC refresh */
DECL|member|vca
r_volatile
id|u32
id|vca
suffix:semicolon
multiline_comment|/* VBC Config */
)brace
suffix:semicolon
DECL|macro|CG14_CCR_ENABLE
mdefine_line|#define CG14_CCR_ENABLE&t;0x04
DECL|macro|CG14_CCR_SELECT
mdefine_line|#define CG14_CCR_SELECT 0x02&t;/* HW/Full screen */
DECL|struct|cg14_cursor
r_struct
id|cg14_cursor
(brace
DECL|member|cpl0
r_volatile
id|u32
id|cpl0
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Enable plane 0 */
DECL|member|cpl1
r_volatile
id|u32
id|cpl1
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Color selection plane */
DECL|member|ccr
r_volatile
id|u8
id|ccr
suffix:semicolon
multiline_comment|/* Cursor Control Reg */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cursx
r_volatile
id|u16
id|cursx
suffix:semicolon
multiline_comment|/* Cursor x,y position */
DECL|member|cursy
r_volatile
id|u16
id|cursy
suffix:semicolon
multiline_comment|/* Cursor x,y position */
DECL|member|color0
r_volatile
id|u32
id|color0
suffix:semicolon
DECL|member|color1
r_volatile
id|u32
id|color1
suffix:semicolon
DECL|member|xxx1
id|u32
id|xxx1
(braket
l_int|0x1bc
)braket
suffix:semicolon
DECL|member|cpl0i
r_volatile
id|u32
id|cpl0i
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Enable plane 0 autoinc */
DECL|member|cpl1i
r_volatile
id|u32
id|cpl1i
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Color selection autoinc */
)brace
suffix:semicolon
DECL|struct|cg14_dac
r_struct
id|cg14_dac
(brace
DECL|member|addr
r_volatile
id|u8
id|addr
suffix:semicolon
multiline_comment|/* Address Register */
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|glut
r_volatile
id|u8
id|glut
suffix:semicolon
multiline_comment|/* Gamma table */
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|select
r_volatile
id|u8
id|select
suffix:semicolon
multiline_comment|/* Register Select */
DECL|member|xxx2
id|u8
id|xxx2
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|mode
r_volatile
id|u8
id|mode
suffix:semicolon
multiline_comment|/* Mode Register */
)brace
suffix:semicolon
DECL|struct|cg14_xlut
r_struct
id|cg14_xlut
(brace
DECL|member|x_xlut
r_volatile
id|u8
id|x_xlut
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|x_xlutd
r_volatile
id|u8
id|x_xlutd
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|xxx0
id|u8
id|xxx0
(braket
l_int|0x600
)braket
suffix:semicolon
DECL|member|x_xlut_inc
r_volatile
id|u8
id|x_xlut_inc
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|x_xlutd_inc
r_volatile
id|u8
id|x_xlutd_inc
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Color look up table (clut) */
multiline_comment|/* Each one of these arrays hold the color lookup table (for 256&n; * colors) for each MDI page (I assume then there should be 4 MDI&n; * pages, I still wonder what they are.  I have seen NeXTStep split&n; * the screen in four parts, while operating in 24 bits mode.  Each&n; * integer holds 4 values: alpha value (transparency channel, thanks&n; * go to John Stone (johns@umr.edu) from OpenBSD), red, green and blue&n; *&n; * I currently use the clut instead of the Xlut&n; */
DECL|struct|cg14_clut
r_struct
id|cg14_clut
(brace
DECL|member|c_clut
id|u32
id|c_clut
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|c_clutd
id|u32
id|c_clutd
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* i wonder what the &squot;d&squot; is for */
DECL|member|c_clut_inc
id|u32
id|c_clut_inc
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|c_clutd_inc
id|u32
id|c_clutd_inc
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CG14_MMAP_ENTRIES
mdefine_line|#define CG14_MMAP_ENTRIES&t;16
DECL|struct|cg14_par
r_struct
id|cg14_par
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|regs
r_struct
id|cg14_regs
op_star
id|regs
suffix:semicolon
DECL|member|clut
r_struct
id|cg14_clut
op_star
id|clut
suffix:semicolon
DECL|member|cursor
r_struct
id|cg14_cursor
op_star
id|cursor
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|macro|CG14_FLAG_BLANKED
mdefine_line|#define CG14_FLAG_BLANKED&t;0x00000001
DECL|member|physbase
r_int
r_int
id|physbase
suffix:semicolon
DECL|member|iospace
r_int
r_int
id|iospace
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
id|CG14_MMAP_ENTRIES
)braket
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|ramsize
r_int
id|ramsize
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
DECL|function|__cg14_reset
r_static
r_void
id|__cg14_reset
c_func
(paren
r_struct
id|cg14_par
op_star
id|par
)paren
(brace
r_struct
id|cg14_regs
op_star
id|regs
op_assign
id|par-&gt;regs
suffix:semicolon
id|u8
id|val
suffix:semicolon
id|val
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;mcr
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|CG14_MCR_PIXMODE_MASK
)paren
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|val
comma
op_amp
id|regs-&gt;mcr
)paren
suffix:semicolon
)brace
DECL|function|cg14_pan_display
r_static
r_int
id|cg14_pan_display
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
(brace
r_struct
id|cg14_par
op_star
id|par
op_assign
(paren
r_struct
id|cg14_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* We just use this to catch switches out of&n;&t; * graphics mode.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__cg14_reset
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
r_if
c_cond
(paren
id|var-&gt;xoffset
op_logical_or
id|var-&gt;yoffset
op_logical_or
id|var-&gt;vmode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *      cg14_setcolreg - Optional function. Sets a color register.&n; *      @regno: boolean, 0 copy local, 1 get_user() function&n; *      @red: frame buffer colormap structure&n; *      @green: The green value which can be up to 16 bits wide&n; *      @blue:  The blue value which can be up to 16 bits wide.&n; *      @transp: If supported the alpha value which can be up to 16 bits wide.&n; *      @info: frame buffer info structure&n; */
DECL|function|cg14_setcolreg
r_static
r_int
id|cg14_setcolreg
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
id|cg14_par
op_star
id|par
op_assign
(paren
r_struct
id|cg14_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|cg14_clut
op_star
id|clut
op_assign
id|par-&gt;clut
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
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
id|val
op_assign
(paren
id|red
op_or
(paren
id|green
op_lshift
l_int|8
)paren
op_or
(paren
id|blue
op_lshift
l_int|16
)paren
)paren
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
id|val
comma
op_amp
id|clut-&gt;c_clut
(braket
id|regno
)braket
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
DECL|function|cg14_mmap
r_static
r_int
id|cg14_mmap
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
id|cg14_par
op_star
id|par
op_assign
(paren
r_struct
id|cg14_par
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
id|par-&gt;iospace
comma
id|vma
)paren
suffix:semicolon
)brace
DECL|function|cg14_ioctl
r_static
r_int
id|cg14_ioctl
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
id|cg14_par
op_star
id|par
op_assign
(paren
r_struct
id|cg14_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_struct
id|cg14_regs
op_star
id|regs
op_assign
id|par-&gt;regs
suffix:semicolon
r_struct
id|mdi_cfginfo
id|kmdi
comma
id|__user
op_star
id|mdii
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cur_mode
comma
id|mode
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MDI_RESET
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|__cg14_reset
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
r_break
suffix:semicolon
r_case
id|MDI_GET_CFGINFO
suffix:colon
id|memset
c_func
(paren
op_amp
id|kmdi
comma
l_int|0
comma
r_sizeof
(paren
id|kmdi
)paren
)paren
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
id|kmdi.mdi_type
op_assign
id|FBTYPE_MDICOLOR
suffix:semicolon
id|kmdi.mdi_height
op_assign
id|info-&gt;var.yres
suffix:semicolon
id|kmdi.mdi_width
op_assign
id|info-&gt;var.xres
suffix:semicolon
id|kmdi.mdi_mode
op_assign
id|par-&gt;mode
suffix:semicolon
id|kmdi.mdi_pixfreq
op_assign
l_int|72
suffix:semicolon
multiline_comment|/* FIXME */
id|kmdi.mdi_size
op_assign
id|par-&gt;ramsize
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
id|mdii
op_assign
(paren
r_struct
id|mdi_cfginfo
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|mdii
comma
op_amp
id|kmdi
comma
r_sizeof
(paren
id|kmdi
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_SET_PIXELMODE
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|mode
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|par-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|cur_mode
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;mcr
)paren
suffix:semicolon
id|cur_mode
op_and_assign
op_complement
id|CG14_MCR_PIXMODE_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|MDI_32_PIX
suffix:colon
id|cur_mode
op_or_assign
(paren
id|CG14_MCR_PIXMODE_32
op_lshift
id|CG14_MCR_PIXMODE_SHIFT
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_16_PIX
suffix:colon
id|cur_mode
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDI_8_PIX
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|sbus_writeb
c_func
(paren
id|cur_mode
comma
op_amp
id|regs-&gt;mcr
)paren
suffix:semicolon
id|par-&gt;mode
op_assign
id|mode
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
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|sbusfb_ioctl_helper
c_func
(paren
id|cmd
comma
id|arg
comma
id|info
comma
id|FBTYPE_MDICOLOR
comma
l_int|24
comma
id|par-&gt;fbsize
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialisation&n; */
DECL|function|cg14_init_fix
r_static
r_void
id|cg14_init_fix
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
id|cg14_par
op_star
id|par
op_assign
(paren
r_struct
id|cg14_par
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
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|info-&gt;fix.line_length
op_assign
id|linebytes
suffix:semicolon
id|info-&gt;fix.accel
op_assign
id|FB_ACCEL_SUN_CG14
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|sbus_mmap_map
id|__cg14_mmap_map
(braket
id|CG14_MMAP_ENTRIES
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|voff
op_assign
id|CG14_REGS
comma
dot
id|poff
op_assign
l_int|0x80000000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG14_XLUT
comma
dot
id|poff
op_assign
l_int|0x80003000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG14_CLUT1
comma
dot
id|poff
op_assign
l_int|0x80004000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG14_CLUT2
comma
dot
id|poff
op_assign
l_int|0x80005000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG14_CLUT3
comma
dot
id|poff
op_assign
l_int|0x80006000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG3_MMAP_OFFSET
op_minus
l_int|0x7000
comma
dot
id|poff
op_assign
l_int|0x80000000
comma
dot
id|size
op_assign
l_int|0x7000
)brace
comma
(brace
dot
id|voff
op_assign
id|CG3_MMAP_OFFSET
comma
dot
id|poff
op_assign
l_int|0x00000000
comma
dot
id|size
op_assign
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_CURSOR_MAP
comma
dot
id|poff
op_assign
l_int|0x80001000
comma
dot
id|size
op_assign
l_int|0x1000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_CHUNKY_BGR_MAP
comma
dot
id|poff
op_assign
l_int|0x01000000
comma
dot
id|size
op_assign
l_int|0x400000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_X16_MAP
comma
dot
id|poff
op_assign
l_int|0x02000000
comma
dot
id|size
op_assign
l_int|0x200000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_C16_MAP
comma
dot
id|poff
op_assign
l_int|0x02800000
comma
dot
id|size
op_assign
l_int|0x200000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_X32_MAP
comma
dot
id|poff
op_assign
l_int|0x03000000
comma
dot
id|size
op_assign
l_int|0x100000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_B32_MAP
comma
dot
id|poff
op_assign
l_int|0x03400000
comma
dot
id|size
op_assign
l_int|0x100000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_G32_MAP
comma
dot
id|poff
op_assign
l_int|0x03800000
comma
dot
id|size
op_assign
l_int|0x100000
)brace
comma
(brace
dot
id|voff
op_assign
id|MDI_PLANAR_R32_MAP
comma
dot
id|poff
op_assign
l_int|0x03c00000
comma
dot
id|size
op_assign
l_int|0x100000
)brace
comma
(brace
dot
id|size
op_assign
l_int|0
)brace
)brace
suffix:semicolon
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
id|cg14_par
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
id|cg14_list
)paren
suffix:semicolon
DECL|function|cg14_init_one
r_static
r_void
id|cg14_init_one
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|node
comma
r_int
id|parent_node
)paren
(brace
r_struct
id|all_info
op_star
id|all
suffix:semicolon
r_int
r_int
id|phys
comma
id|rphys
suffix:semicolon
id|u32
id|bases
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|is_8mb
comma
id|linebytes
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
(brace
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;address&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|bases
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|bases
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bases
(braket
l_int|0
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cg14: Device is not mapped.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__get_iospace
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
op_ne
id|__get_iospace
c_func
(paren
id|bases
(braket
l_int|1
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cg14: I/O spaces don&squot;t match.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
l_string|&quot;cg14: Cannot allocate memory.&bslash;n&quot;
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
id|sbusfb_fill_var
c_func
(paren
op_amp
id|all-&gt;info.var
comma
id|node
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
id|all-&gt;par.sdev
op_assign
id|sdev
suffix:semicolon
r_if
c_cond
(paren
id|sdev
)paren
(brace
id|rphys
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|all-&gt;par.physbase
op_assign
id|phys
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|1
)braket
dot
id|phys_addr
suffix:semicolon
id|all-&gt;par.iospace
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|all-&gt;par.regs
op_assign
(paren
r_struct
id|cg14_regs
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
id|cg14_regs
)paren
comma
l_string|&quot;cg14 regs&quot;
)paren
suffix:semicolon
id|all-&gt;par.clut
op_assign
(paren
r_struct
id|cg14_clut
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
id|CG14_CLUT1
comma
r_sizeof
(paren
r_struct
id|cg14_clut
)paren
comma
l_string|&quot;cg14 clut&quot;
)paren
suffix:semicolon
id|all-&gt;par.cursor
op_assign
(paren
r_struct
id|cg14_cursor
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
id|CG14_CURSORREGS
comma
r_sizeof
(paren
r_struct
id|cg14_cursor
)paren
comma
l_string|&quot;cg14 cursor&quot;
)paren
suffix:semicolon
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
l_int|1
)braket
comma
l_int|0
comma
id|all-&gt;par.fbsize
comma
l_string|&quot;cg14 ram&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|rphys
op_assign
id|__get_phys
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|all-&gt;par.physbase
op_assign
id|phys
op_assign
id|__get_phys
c_func
(paren
id|bases
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|all-&gt;par.iospace
op_assign
id|__get_iospace
c_func
(paren
id|bases
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|all-&gt;par.regs
op_assign
(paren
r_struct
id|cg14_regs
op_star
)paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
suffix:semicolon
id|all-&gt;par.clut
op_assign
(paren
r_struct
id|cg14_clut
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
op_plus
id|CG14_CLUT1
)paren
suffix:semicolon
id|all-&gt;par.cursor
op_assign
(paren
r_struct
id|cg14_cursor
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|0
)braket
op_plus
id|CG14_CURSORREGS
)paren
suffix:semicolon
id|all-&gt;info.screen_base
op_assign
(paren
r_char
op_star
)paren
(paren
r_int
r_int
)paren
id|bases
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|bases
(braket
l_int|0
)braket
comma
r_sizeof
(paren
id|bases
)paren
)paren
suffix:semicolon
id|is_8mb
op_assign
(paren
id|bases
(braket
l_int|5
)braket
op_eq
l_int|0x800000
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|all-&gt;par.mmap_map
)paren
op_ne
r_sizeof
(paren
id|__cg14_mmap_map
)paren
)paren
(brace
r_extern
r_void
id|__cg14_mmap_sized_wrongly
c_func
(paren
r_void
)paren
suffix:semicolon
id|__cg14_mmap_sized_wrongly
c_func
(paren
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|all-&gt;par.mmap_map
comma
op_amp
id|__cg14_mmap_map
comma
r_sizeof
(paren
id|all-&gt;par.mmap_map
)paren
)paren
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
id|CG14_MMAP_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|sbus_mmap_map
op_star
id|map
op_assign
op_amp
id|all-&gt;par.mmap_map
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map-&gt;size
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;poff
op_amp
l_int|0x80000000
)paren
id|map-&gt;poff
op_assign
(paren
id|map-&gt;poff
op_amp
l_int|0x7fffffff
)paren
op_plus
id|rphys
op_minus
id|phys
suffix:semicolon
r_if
c_cond
(paren
id|is_8mb
op_logical_and
id|map-&gt;size
op_ge
l_int|0x100000
op_logical_and
id|map-&gt;size
op_le
l_int|0x400000
)paren
id|map-&gt;size
op_mul_assign
l_int|2
suffix:semicolon
)brace
id|all-&gt;par.mode
op_assign
id|MDI_8_PIX
suffix:semicolon
id|all-&gt;par.ramsize
op_assign
(paren
id|is_8mb
ques
c_cond
l_int|0x800000
suffix:colon
l_int|0x400000
)paren
suffix:semicolon
id|all-&gt;info.flags
op_assign
id|FBINFO_DEFAULT
op_or
id|FBINFO_HWACCEL_YPAN
suffix:semicolon
id|all-&gt;info.fbops
op_assign
op_amp
id|cg14_ops
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
id|__cg14_reset
c_func
(paren
op_amp
id|all-&gt;par
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
l_string|&quot;cg14: Could not allocate color map.&bslash;n&quot;
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
id|cg14_init_fix
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
l_string|&quot;cg14: Could not register framebuffer.&bslash;n&quot;
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
id|cg14_list
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;cg14: cgfourteen at %lx:%lx&bslash;n&quot;
comma
id|all-&gt;par.physbase
comma
id|all-&gt;par.iospace
)paren
suffix:semicolon
)brace
DECL|function|cg14_init
r_int
id|__init
id|cg14_init
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
macro_line|#ifdef CONFIG_SPARC32
(brace
r_int
id|root
comma
id|node
suffix:semicolon
id|root
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|root
op_assign
id|prom_searchsiblings
c_func
(paren
id|root
comma
l_string|&quot;obio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
(brace
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|root
)paren
comma
l_string|&quot;cgfourteen&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
id|cg14_init_one
c_func
(paren
l_int|NULL
comma
id|node
comma
id|root
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
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
l_string|&quot;cgfourteen&quot;
)paren
)paren
id|cg14_init_one
c_func
(paren
id|sdev
comma
id|sdev-&gt;prom_node
comma
id|sbus-&gt;prom_node
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cg14_exit
r_void
id|__exit
id|cg14_exit
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
id|cg14_list
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
DECL|function|cg14_setup
id|cg14_setup
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
DECL|variable|cg14_init
id|module_init
c_func
(paren
id|cg14_init
)paren
suffix:semicolon
DECL|variable|cg14_exit
id|module_exit
c_func
(paren
id|cg14_exit
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;framebuffer driver for CGfourteen chipsets&quot;
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
