multiline_comment|/*&n; * linux/drivers/video/hgafb.c -- Hercules graphics adaptor frame buffer device&n; * &n; *      Created 25 Nov 1999 by Ferenc Bakonyi (fero@drama.obuda.kando.hu)&n; *      Based on skeletonfb.c by Geert Uytterhoeven and&n; *               mdacon.c by Andrew Apted&n; *&n; * History:&n; *&n; * - Revision 0.1.8 (23 Oct 2002): Ported to new framebuffer api.&n; * &n; * - Revision 0.1.7 (23 Jan 2001): fix crash resulting from MDA only cards &n; *&t;&t;&t;&t;   being detected as Hercules.&t; (Paul G.)&n; * - Revision 0.1.6 (17 Aug 2000): new style structs&n; *                                 documentation&n; * - Revision 0.1.5 (13 Mar 2000): spinlocks instead of saveflags();cli();etc&n; *                                 minor fixes&n; * - Revision 0.1.4 (24 Jan 2000): fixed a bug in hga_card_detect() for &n; *                                  HGA-only systems&n; * - Revision 0.1.3 (22 Jan 2000): modified for the new fb_info structure&n; *                                 screen is cleared after rmmod&n; *                                 virtual resolutions&n; *                                 module parameter &squot;nologo={0|1}&squot;&n; *                                 the most important: boot logo :)&n; * - Revision 0.1.0  (6 Dec 1999): faster scrolling and minor fixes&n; * - First release  (25 Nov 1999)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vga.h&gt;
macro_line|#if 0
mdefine_line|#define DPRINTK(args...) printk(KERN_DEBUG __FILE__&quot;: &quot; ##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(args...)
macro_line|#endif
macro_line|#if 0
mdefine_line|#define CHKINFO(ret) if (info != &amp;fb_info) { printk(KERN_DEBUG __FILE__&quot;: This should never happen, line:%d &bslash;n&quot;, __LINE__); return ret; }
macro_line|#else
DECL|macro|CHKINFO
mdefine_line|#define CHKINFO(ret)
macro_line|#endif
multiline_comment|/* Description of the hardware layout */
DECL|variable|hga_vram_base
r_static
r_int
r_int
id|hga_vram_base
suffix:semicolon
multiline_comment|/* Base of video memory */
DECL|variable|hga_vram_len
r_static
r_int
r_int
id|hga_vram_len
suffix:semicolon
multiline_comment|/* Size of video memory */
DECL|macro|HGA_ROWADDR
mdefine_line|#define HGA_ROWADDR(row) ((row%4)*8192 + (row&gt;&gt;2)*90)
DECL|macro|HGA_TXT
mdefine_line|#define HGA_TXT&t;&t;&t;0
DECL|macro|HGA_GFX
mdefine_line|#define HGA_GFX&t;&t;&t;1
DECL|function|rowaddr
r_static
r_inline
id|u8
op_star
id|rowaddr
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
id|u_int
id|row
)paren
(brace
r_return
id|info-&gt;screen_base
op_plus
id|HGA_ROWADDR
c_func
(paren
id|row
)paren
suffix:semicolon
)brace
DECL|variable|hga_mode
r_static
r_int
id|hga_mode
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* 0 = txt, 1 = gfx mode */
DECL|enumerator|TYPE_HERC
DECL|enumerator|TYPE_HERCPLUS
DECL|enumerator|TYPE_HERCCOLOR
DECL|variable|hga_type
r_static
r_enum
(brace
id|TYPE_HERC
comma
id|TYPE_HERCPLUS
comma
id|TYPE_HERCCOLOR
)brace
id|hga_type
suffix:semicolon
DECL|variable|hga_type_name
r_static
r_char
op_star
id|hga_type_name
suffix:semicolon
DECL|macro|HGA_INDEX_PORT
mdefine_line|#define HGA_INDEX_PORT&t;&t;0x3b4&t;&t;/* Register select port */
DECL|macro|HGA_VALUE_PORT
mdefine_line|#define HGA_VALUE_PORT&t;&t;0x3b5&t;&t;/* Register value port */
DECL|macro|HGA_MODE_PORT
mdefine_line|#define HGA_MODE_PORT&t;&t;0x3b8&t;&t;/* Mode control port */
DECL|macro|HGA_STATUS_PORT
mdefine_line|#define HGA_STATUS_PORT&t;&t;0x3ba&t;&t;/* Status and Config port */
DECL|macro|HGA_GFX_PORT
mdefine_line|#define HGA_GFX_PORT&t;&t;0x3bf&t;&t;/* Graphics control port */
multiline_comment|/* HGA register values */
DECL|macro|HGA_CURSOR_BLINKING
mdefine_line|#define HGA_CURSOR_BLINKING&t;0x00
DECL|macro|HGA_CURSOR_OFF
mdefine_line|#define HGA_CURSOR_OFF&t;&t;0x20
DECL|macro|HGA_CURSOR_SLOWBLINK
mdefine_line|#define HGA_CURSOR_SLOWBLINK&t;0x60
DECL|macro|HGA_MODE_GRAPHICS
mdefine_line|#define HGA_MODE_GRAPHICS&t;0x02
DECL|macro|HGA_MODE_VIDEO_EN
mdefine_line|#define HGA_MODE_VIDEO_EN&t;0x08
DECL|macro|HGA_MODE_BLINK_EN
mdefine_line|#define HGA_MODE_BLINK_EN&t;0x20
DECL|macro|HGA_MODE_GFX_PAGE1
mdefine_line|#define HGA_MODE_GFX_PAGE1&t;0x80
DECL|macro|HGA_STATUS_HSYNC
mdefine_line|#define HGA_STATUS_HSYNC&t;0x01
DECL|macro|HGA_STATUS_VSYNC
mdefine_line|#define HGA_STATUS_VSYNC&t;0x80
DECL|macro|HGA_STATUS_VIDEO
mdefine_line|#define HGA_STATUS_VIDEO&t;0x08
DECL|macro|HGA_CONFIG_COL132
mdefine_line|#define HGA_CONFIG_COL132&t;0x08
DECL|macro|HGA_GFX_MODE_EN
mdefine_line|#define HGA_GFX_MODE_EN&t;&t;0x01
DECL|macro|HGA_GFX_PAGE_EN
mdefine_line|#define HGA_GFX_PAGE_EN&t;&t;0x02
multiline_comment|/* Global locks */
DECL|variable|hga_reg_lock
r_static
id|spinlock_t
id|hga_reg_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Framebuffer driver structures */
DECL|variable|hga_default_var
r_static
r_struct
id|fb_var_screeninfo
id|hga_default_var
op_assign
(brace
dot
id|xres
op_assign
l_int|720
comma
dot
id|yres
op_assign
l_int|348
comma
dot
id|xres_virtual
op_assign
l_int|720
comma
dot
id|yres_virtual
op_assign
l_int|348
comma
dot
id|bits_per_pixel
op_assign
l_int|1
comma
dot
id|red
op_assign
(brace
l_int|0
comma
l_int|1
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
l_int|1
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
l_int|1
comma
l_int|0
)brace
comma
dot
id|transp
op_assign
(brace
l_int|0
comma
l_int|0
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
)brace
suffix:semicolon
DECL|variable|hga_fix
r_static
r_struct
id|fb_fix_screeninfo
id|hga_fix
op_assign
(brace
dot
id|id
op_assign
l_string|&quot;HGA&quot;
comma
dot
id|type
op_assign
id|FB_TYPE_PACKED_PIXELS
comma
multiline_comment|/* (not sure) */
dot
id|visual
op_assign
id|FB_VISUAL_MONO10
comma
dot
id|xpanstep
op_assign
l_int|8
comma
dot
id|ypanstep
op_assign
l_int|8
comma
dot
id|line_length
op_assign
l_int|90
comma
dot
id|accel
op_assign
id|FB_ACCEL_NONE
)brace
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
multiline_comment|/* Don&squot;t assume that tty1 will be the initial current console. */
DECL|variable|release_io_port
r_static
r_int
id|release_io_port
op_assign
l_int|0
suffix:semicolon
DECL|variable|release_io_ports
r_static
r_int
id|release_io_ports
op_assign
l_int|0
suffix:semicolon
DECL|variable|nologo
r_static
r_int
id|nologo
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------&n; *&n; * Low level hardware functions&n; *&n; * ------------------------------------------------------------------------- */
DECL|function|write_hga_b
r_static
r_void
id|write_hga_b
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_char
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|HGA_INDEX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|HGA_VALUE_PORT
)paren
suffix:semicolon
)brace
DECL|function|write_hga_w
r_static
r_void
id|write_hga_w
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_char
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|HGA_INDEX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|HGA_VALUE_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg
op_plus
l_int|1
comma
id|HGA_INDEX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xff
comma
id|HGA_VALUE_PORT
)paren
suffix:semicolon
)brace
DECL|function|test_hga_b
r_static
r_int
id|test_hga_b
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_char
id|reg
)paren
(brace
id|outb_p
c_func
(paren
id|reg
comma
id|HGA_INDEX_PORT
)paren
suffix:semicolon
id|outb
(paren
id|val
comma
id|HGA_VALUE_PORT
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|val
op_assign
(paren
id|inb_p
c_func
(paren
id|HGA_VALUE_PORT
)paren
op_eq
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|hga_clear_screen
r_static
r_void
id|hga_clear_screen
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|fillchar
op_assign
l_int|0xbf
suffix:semicolon
multiline_comment|/* magic */
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hga_mode
op_eq
id|HGA_TXT
)paren
id|fillchar
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|hga_mode
op_eq
id|HGA_GFX
)paren
id|fillchar
op_assign
l_int|0x00
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fillchar
op_ne
l_int|0xbf
)paren
id|isa_memset_io
c_func
(paren
id|hga_vram_base
comma
id|fillchar
comma
id|hga_vram_len
)paren
suffix:semicolon
)brace
DECL|function|hga_txt_mode
r_static
r_void
id|hga_txt_mode
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|HGA_MODE_VIDEO_EN
op_or
id|HGA_MODE_BLINK_EN
comma
id|HGA_MODE_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|HGA_GFX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|HGA_STATUS_PORT
)paren
suffix:semicolon
id|write_hga_b
c_func
(paren
l_int|0x61
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* horizontal total */
id|write_hga_b
c_func
(paren
l_int|0x50
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* horizontal displayed */
id|write_hga_b
c_func
(paren
l_int|0x52
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* horizontal sync pos */
id|write_hga_b
c_func
(paren
l_int|0x0f
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* horizontal sync width */
id|write_hga_b
c_func
(paren
l_int|0x19
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* vertical total */
id|write_hga_b
c_func
(paren
l_int|0x06
comma
l_int|0x05
)paren
suffix:semicolon
multiline_comment|/* vertical total adjust */
id|write_hga_b
c_func
(paren
l_int|0x19
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* vertical displayed */
id|write_hga_b
c_func
(paren
l_int|0x19
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* vertical sync pos */
id|write_hga_b
c_func
(paren
l_int|0x02
comma
l_int|0x08
)paren
suffix:semicolon
multiline_comment|/* interlace mode */
id|write_hga_b
c_func
(paren
l_int|0x0d
comma
l_int|0x09
)paren
suffix:semicolon
multiline_comment|/* maximum scanline */
id|write_hga_b
c_func
(paren
l_int|0x0c
comma
l_int|0x0a
)paren
suffix:semicolon
multiline_comment|/* cursor start */
id|write_hga_b
c_func
(paren
l_int|0x0d
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* cursor end */
id|write_hga_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* start address */
id|write_hga_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0e
)paren
suffix:semicolon
multiline_comment|/* cursor location */
id|hga_mode
op_assign
id|HGA_TXT
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hga_gfx_mode
r_static
r_void
id|hga_gfx_mode
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|HGA_STATUS_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|HGA_GFX_MODE_EN
comma
id|HGA_GFX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|HGA_MODE_VIDEO_EN
op_or
id|HGA_MODE_GRAPHICS
comma
id|HGA_MODE_PORT
)paren
suffix:semicolon
id|write_hga_b
c_func
(paren
l_int|0x35
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* horizontal total */
id|write_hga_b
c_func
(paren
l_int|0x2d
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* horizontal displayed */
id|write_hga_b
c_func
(paren
l_int|0x2e
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* horizontal sync pos */
id|write_hga_b
c_func
(paren
l_int|0x07
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* horizontal sync width */
id|write_hga_b
c_func
(paren
l_int|0x5b
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* vertical total */
id|write_hga_b
c_func
(paren
l_int|0x02
comma
l_int|0x05
)paren
suffix:semicolon
multiline_comment|/* vertical total adjust */
id|write_hga_b
c_func
(paren
l_int|0x57
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* vertical displayed */
id|write_hga_b
c_func
(paren
l_int|0x57
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* vertical sync pos */
id|write_hga_b
c_func
(paren
l_int|0x02
comma
l_int|0x08
)paren
suffix:semicolon
multiline_comment|/* interlace mode */
id|write_hga_b
c_func
(paren
l_int|0x03
comma
l_int|0x09
)paren
suffix:semicolon
multiline_comment|/* maximum scanline */
id|write_hga_b
c_func
(paren
l_int|0x00
comma
l_int|0x0a
)paren
suffix:semicolon
multiline_comment|/* cursor start */
id|write_hga_b
c_func
(paren
l_int|0x00
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* cursor end */
id|write_hga_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* start address */
id|write_hga_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0e
)paren
suffix:semicolon
multiline_comment|/* cursor location */
id|hga_mode
op_assign
id|HGA_GFX
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hga_show_logo
r_static
r_void
id|hga_show_logo
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;&t;unsigned long dest = hga_vram_base;&n;&t;char *logo = linux_logo_bw;&n;&t;int x, y;&n;&t;&n;&t;for (y = 134; y &lt; 134 + 80 ; y++) * this needs some cleanup *&n;&t;&t;for (x = 0; x &lt; 10 ; x++)&n;&t;&t;&t;isa_writeb(~*(logo++),(dest + HGA_ROWADDR(y) + x + 40));&n;*/
)brace
DECL|function|hga_pan
r_static
r_void
id|hga_pan
c_func
(paren
r_int
r_int
id|xoffset
comma
r_int
r_int
id|yoffset
)paren
(brace
r_int
r_int
id|base
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|base
op_assign
(paren
id|yoffset
op_div
l_int|8
)paren
op_star
l_int|90
op_plus
id|xoffset
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
id|write_hga_w
c_func
(paren
id|base
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* start address */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;hga_pan: base:%d&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|hga_blank
r_static
r_void
id|hga_blank
c_func
(paren
r_int
id|blank_mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blank_mode
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x00
comma
id|HGA_MODE_PORT
)paren
suffix:semicolon
multiline_comment|/* disable video */
)brace
r_else
(brace
id|outb_p
c_func
(paren
id|HGA_MODE_VIDEO_EN
op_or
id|HGA_MODE_GRAPHICS
comma
id|HGA_MODE_PORT
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hga_reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hga_card_detect
r_static
r_int
id|__init
id|hga_card_detect
c_func
(paren
r_void
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|p
comma
id|q
suffix:semicolon
r_int
r_int
id|p_save
comma
id|q_save
suffix:semicolon
id|hga_vram_base
op_assign
l_int|0xb0000
suffix:semicolon
id|hga_vram_len
op_assign
l_int|0x08000
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
l_int|0x3b0
comma
l_int|12
comma
l_string|&quot;hgafb&quot;
)paren
)paren
id|release_io_ports
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
l_int|0x3bf
comma
l_int|1
comma
l_string|&quot;hgafb&quot;
)paren
)paren
id|release_io_port
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* do a memory check */
id|p
op_assign
id|hga_vram_base
suffix:semicolon
id|q
op_assign
id|hga_vram_base
op_plus
l_int|0x01000
suffix:semicolon
id|p_save
op_assign
id|isa_readw
c_func
(paren
id|p
)paren
suffix:semicolon
id|q_save
op_assign
id|isa_readw
c_func
(paren
id|q
)paren
suffix:semicolon
id|isa_writew
c_func
(paren
l_int|0xaa55
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isa_readw
c_func
(paren
id|p
)paren
op_eq
l_int|0xaa55
)paren
id|count
op_increment
suffix:semicolon
id|isa_writew
c_func
(paren
l_int|0x55aa
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isa_readw
c_func
(paren
id|p
)paren
op_eq
l_int|0x55aa
)paren
id|count
op_increment
suffix:semicolon
id|isa_writew
c_func
(paren
id|p_save
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
l_int|2
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Ok, there is definitely a card registering at the correct&n;&t; * memory location, so now we do an I/O port test.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_hga_b
c_func
(paren
l_int|0x66
comma
l_int|0x0f
)paren
)paren
(brace
multiline_comment|/* cursor low register */
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_hga_b
c_func
(paren
l_int|0x99
comma
l_int|0x0f
)paren
)paren
(brace
multiline_comment|/* cursor low register */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* See if the card is a Hercules, by checking whether the vsync&n;&t; * bit of the status register is changing.  This test lasts for&n;&t; * approximately 1/10th of a second.&n;&t; */
id|p_save
op_assign
id|q_save
op_assign
id|inb_p
c_func
(paren
id|HGA_STATUS_PORT
)paren
op_amp
id|HGA_STATUS_VSYNC
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|50000
op_logical_and
id|p_save
op_eq
id|q_save
suffix:semicolon
id|count
op_increment
)paren
(brace
id|q_save
op_assign
id|inb
c_func
(paren
id|HGA_STATUS_PORT
)paren
op_amp
id|HGA_STATUS_VSYNC
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p_save
op_eq
id|q_save
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|inb_p
c_func
(paren
id|HGA_STATUS_PORT
)paren
op_amp
l_int|0x70
)paren
(brace
r_case
l_int|0x10
suffix:colon
id|hga_type
op_assign
id|TYPE_HERCPLUS
suffix:semicolon
id|hga_type_name
op_assign
l_string|&quot;HerculesPlus&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x50
suffix:colon
id|hga_type
op_assign
id|TYPE_HERCCOLOR
suffix:semicolon
id|hga_type_name
op_assign
l_string|&quot;HerculesColor&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|hga_type
op_assign
id|TYPE_HERC
suffix:semicolon
id|hga_type_name
op_assign
l_string|&quot;Hercules&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;hgafb_open - open the framebuffer device&n; *&t;@info:pointer to fb_info object containing info for current hga board&n; *&t;@int:open by console system or userland.&n; */
DECL|function|hgafb_open
r_static
r_int
id|hgafb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|init
)paren
(brace
id|hga_gfx_mode
c_func
(paren
)paren
suffix:semicolon
id|hga_clear_screen
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nologo
)paren
id|hga_show_logo
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;hgafb_open - open the framebuffer device&n; *&t;@info:pointer to fb_info object containing info for current hga board&n; *&t;@int:open by console system or userland.&n; */
DECL|function|hgafb_release
r_static
r_int
id|hgafb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|init
)paren
(brace
id|hga_txt_mode
c_func
(paren
)paren
suffix:semicolon
id|hga_clear_screen
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;hgafb_setcolreg - set color registers&n; *&t;@regno:register index to set&n; *&t;@red:red value, unused&n; *&t;@green:green value, unused&n; *&t;@blue:blue value, unused&n; *&t;@transp:transparency value, unused&n; *&t;@info:unused&n; *&n; *&t;This callback function is used to set the color registers of a HGA&n; *&t;board. Since we have only two fixed colors only @regno is checked.&n; *&t;A zero is returned on success and 1 for failure.&n; */
DECL|function|hgafb_setcolreg
r_static
r_int
id|hgafb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|regno
OG
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;hga_pan_display - pan or wrap the display&n; *&t;@var:contains new xoffset, yoffset and vmode values&n; *&t;@info:pointer to fb_info object containing info for current hga board&n; *&n; *&t;This function looks only at xoffset, yoffset and the %FB_VMODE_YWRAP&n; *&t;flag in @var. If input parameters are correct it calls hga_pan() to &n; *&t;program the hardware. @info-&gt;var is updated to the new values.&n; *&t;A zero is returned on success and %-EINVAL for failure.&n; */
DECL|function|hgafb_pan_display
r_int
id|hgafb_pan_display
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
r_if
c_cond
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;yoffset
OL
l_int|0
op_logical_or
id|var-&gt;yoffset
op_ge
id|info-&gt;var.yres_virtual
op_logical_or
id|var-&gt;xoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_plus
id|var-&gt;xres
OG
id|info-&gt;var.xres_virtual
op_logical_or
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
OG
id|info-&gt;var.yres_virtual
op_logical_or
id|var-&gt;yoffset
op_mod
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|hga_pan
c_func
(paren
id|var-&gt;xoffset
comma
id|var-&gt;yoffset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;hgafb_blank - (un)blank the screen&n; *&t;@blank_mode:blanking method to use&n; *&t;@info:unused&n; *&t;&n; *&t;Blank the screen if blank_mode != 0, else unblank. &n; *&t;Implements VESA suspend and powerdown modes on hardware that supports &n; *&t;disabling hsync/vsync:&n; *&t;&t;@blank_mode == 2 means suspend vsync,&n; *&t;&t;@blank_mode == 3 means suspend hsync,&n; *&t;&t;@blank_mode == 4 means powerdown.&n; */
DECL|function|hgafb_blank
r_static
r_int
id|hgafb_blank
c_func
(paren
r_int
id|blank_mode
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|hga_blank
c_func
(paren
id|blank_mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hgafb_fillrect
r_static
r_void
id|hgafb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
(brace
id|u_int
id|rows
comma
id|y
suffix:semicolon
id|u8
op_star
id|dest
suffix:semicolon
id|y
op_assign
id|rect-&gt;dy
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|rect-&gt;height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|y
op_increment
)paren
(brace
id|dest
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y
)paren
op_plus
(paren
id|rect-&gt;dx
op_rshift
l_int|3
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rect-&gt;rop
)paren
(brace
r_case
id|ROP_COPY
suffix:colon
singleline_comment|//fb_memset(dest, rect-&gt;color, (rect-&gt;width &gt;&gt; 3));
r_break
suffix:semicolon
r_case
id|ROP_XOR
suffix:colon
op_star
id|dest
op_assign
op_complement
op_star
id|dest
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|hgafb_copyarea
r_static
r_void
id|hgafb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
id|u_int
id|rows
comma
id|y1
comma
id|y2
suffix:semicolon
id|u8
op_star
id|src
comma
op_star
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;dy
op_le
id|area-&gt;sy
)paren
(brace
id|y1
op_assign
id|area-&gt;sy
suffix:semicolon
id|y2
op_assign
id|area-&gt;dy
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|area-&gt;height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|src
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y1
)paren
op_plus
(paren
id|area-&gt;sx
op_rshift
l_int|3
)paren
suffix:semicolon
id|dest
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y2
)paren
op_plus
(paren
id|area-&gt;dx
op_rshift
l_int|3
)paren
suffix:semicolon
singleline_comment|//fb_memmove(dest, src, (area-&gt;width &gt;&gt; 3));
id|y1
op_increment
suffix:semicolon
id|y2
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|y1
op_assign
id|area-&gt;sy
op_plus
id|area-&gt;height
op_minus
l_int|1
suffix:semicolon
id|y2
op_assign
id|area-&gt;dy
op_plus
id|area-&gt;height
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|area-&gt;height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|src
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y1
)paren
op_plus
(paren
id|area-&gt;sx
op_rshift
l_int|3
)paren
suffix:semicolon
id|dest
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y2
)paren
op_plus
(paren
id|area-&gt;dx
op_rshift
l_int|3
)paren
suffix:semicolon
singleline_comment|//fb_memmove(dest, src, (area-&gt;width &gt;&gt; 3));
id|y1
op_decrement
suffix:semicolon
id|y2
op_decrement
suffix:semicolon
)brace
)brace
)brace
DECL|function|hgafb_imageblit
r_static
r_void
id|hgafb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_image
op_star
id|image
)paren
(brace
id|u8
op_star
id|dest
comma
op_star
id|cdat
op_assign
(paren
id|u8
op_star
)paren
id|image-&gt;data
suffix:semicolon
id|u_int
id|rows
comma
id|y
op_assign
id|image-&gt;dy
suffix:semicolon
id|u8
id|d
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|image-&gt;height
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|y
op_increment
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
id|dest
op_assign
id|rowaddr
c_func
(paren
id|info
comma
id|y
)paren
op_plus
(paren
id|image-&gt;dx
op_rshift
l_int|3
)paren
suffix:semicolon
op_star
id|dest
op_assign
id|d
suffix:semicolon
)brace
)brace
DECL|variable|hgafb_ops
r_static
r_struct
id|fb_ops
id|hgafb_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|fb_open
op_assign
id|hgafb_open
comma
dot
id|fb_release
op_assign
id|hgafb_release
comma
dot
id|fb_setcolreg
op_assign
id|hgafb_setcolreg
comma
dot
id|fb_pan_display
op_assign
id|hgafb_pan_display
comma
dot
id|fb_blank
op_assign
id|hgafb_blank
comma
dot
id|fb_fillrect
op_assign
id|cfb_fillrect
comma
singleline_comment|//hgafb_fillrect,
dot
id|fb_copyarea
op_assign
id|cfb_copyarea
comma
singleline_comment|//hgafb_copyarea,
dot
id|fb_imageblit
op_assign
id|cfb_imageblit
comma
singleline_comment|//hgafb_imageblit,
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------- *&n; *&n; * Functions in fb_info&n; * &n; * ------------------------------------------------------------------------- */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*&n;&t; *  Initialization&n;&t; */
DECL|function|hgafb_init
r_int
id|__init
id|hgafb_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hga_card_detect
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hgafb: HGA card not detected.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hgafb: %s with %ldK of memory detected.&bslash;n&quot;
comma
id|hga_type_name
comma
id|hga_vram_len
op_div
l_int|1024
)paren
suffix:semicolon
id|hga_fix.smem_start
op_assign
id|VGA_MAP_MEM
c_func
(paren
id|hga_vram_base
)paren
suffix:semicolon
id|hga_fix.smem_len
op_assign
id|hga_vram_len
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_info.var
op_assign
id|hga_default_var
suffix:semicolon
id|fb_info.fix
op_assign
id|hga_fix
suffix:semicolon
id|fb_info.monspecs.hfmin
op_assign
l_int|0
suffix:semicolon
id|fb_info.monspecs.hfmax
op_assign
l_int|0
suffix:semicolon
id|fb_info.monspecs.vfmin
op_assign
l_int|10000
suffix:semicolon
id|fb_info.monspecs.vfmax
op_assign
l_int|10000
suffix:semicolon
id|fb_info.monspecs.dpms
op_assign
l_int|0
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|hgafb_ops
suffix:semicolon
id|fb_info.screen_base
op_assign
(paren
r_char
op_star
)paren
id|hga_fix.smem_start
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|fb_info.node
comma
id|fb_info.fix.id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Setup&n;&t; */
DECL|function|hgafb_setup
r_int
id|__init
id|hgafb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|hgafb_exit
r_static
r_void
id|__exit
id|hgafb_exit
c_func
(paren
r_void
)paren
(brace
id|hga_txt_mode
c_func
(paren
)paren
suffix:semicolon
id|hga_clear_screen
c_func
(paren
)paren
suffix:semicolon
id|unregister_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|release_io_ports
)paren
id|release_region
c_func
(paren
l_int|0x3b0
comma
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|release_io_port
)paren
id|release_region
c_func
(paren
l_int|0x3bf
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* -------------------------------------------------------------------------&n; *&n; *  Modularization&n; *&n; * ------------------------------------------------------------------------- */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ferenc Bakonyi (fero@drama.obuda.kando.hu)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;FBDev driver for Hercules Graphics Adaptor&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|nologo
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nologo
comma
l_string|&quot;Disables startup logo if != 0 (default=0)&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|hgafb_init
id|module_init
c_func
(paren
id|hgafb_init
)paren
suffix:semicolon
DECL|variable|hgafb_exit
id|module_exit
c_func
(paren
id|hgafb_exit
)paren
suffix:semicolon
macro_line|#endif
eof
