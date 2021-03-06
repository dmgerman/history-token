multiline_comment|/*&n; * linux/drivers/video/vgastate.c -- VGA state save/restore&n; *&n; * Copyright 2002 James Simmons&n; * &n; * Copyright history from vga16fb.c:&n; *&t;Copyright 1999 Ben Pfaff and Petr Vandrovec&n; *&t;Based on VGA info at http://www.goodnet.com/~tinara/FreeVGA/home.htm&n; *&t;Based on VESA framebuffer (c) 1998 Gerd Knorr&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.  &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;video/vga.h&gt;
DECL|struct|regstate
r_struct
id|regstate
(brace
DECL|member|vga_font0
id|__u8
op_star
id|vga_font0
suffix:semicolon
DECL|member|vga_font1
id|__u8
op_star
id|vga_font1
suffix:semicolon
DECL|member|vga_text
id|__u8
op_star
id|vga_text
suffix:semicolon
DECL|member|vga_cmap
id|__u8
op_star
id|vga_cmap
suffix:semicolon
DECL|member|attr
id|__u8
op_star
id|attr
suffix:semicolon
DECL|member|crtc
id|__u8
op_star
id|crtc
suffix:semicolon
DECL|member|gfx
id|__u8
op_star
id|gfx
suffix:semicolon
DECL|member|seq
id|__u8
op_star
id|seq
suffix:semicolon
DECL|member|misc
id|__u8
id|misc
suffix:semicolon
)brace
suffix:semicolon
DECL|function|vga_rcrtcs
r_static
r_inline
r_int
r_char
id|vga_rcrtcs
c_func
(paren
r_void
id|__iomem
op_star
id|regbase
comma
r_int
r_int
id|iobase
comma
r_int
r_char
id|reg
)paren
(brace
id|vga_w
c_func
(paren
id|regbase
comma
id|iobase
op_plus
l_int|0x4
comma
id|reg
)paren
suffix:semicolon
r_return
id|vga_r
c_func
(paren
id|regbase
comma
id|iobase
op_plus
l_int|0x5
)paren
suffix:semicolon
)brace
DECL|function|vga_wcrtcs
r_static
r_inline
r_void
id|vga_wcrtcs
c_func
(paren
r_void
id|__iomem
op_star
id|regbase
comma
r_int
r_int
id|iobase
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|vga_w
c_func
(paren
id|regbase
comma
id|iobase
op_plus
l_int|0x4
comma
id|reg
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|regbase
comma
id|iobase
op_plus
l_int|0x5
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|save_vga_text
r_static
r_void
id|save_vga_text
c_func
(paren
r_struct
id|vgastate
op_star
id|state
comma
r_void
id|__iomem
op_star
id|fbbase
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|misc
comma
id|attr10
comma
id|gr4
comma
id|gr5
comma
id|gr6
comma
id|seq1
comma
id|seq2
comma
id|seq4
suffix:semicolon
multiline_comment|/* if in graphics mode, no need to save */
id|attr10
op_assign
id|vga_rattr
c_func
(paren
id|state-&gt;vgabase
comma
l_int|0x10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr10
op_amp
l_int|1
)paren
r_return
suffix:semicolon
multiline_comment|/* save regs */
id|misc
op_assign
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_R
)paren
suffix:semicolon
id|gr4
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
)paren
suffix:semicolon
id|gr5
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
)paren
suffix:semicolon
id|gr6
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
)paren
suffix:semicolon
id|seq2
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
)paren
suffix:semicolon
id|seq4
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
)paren
suffix:semicolon
multiline_comment|/* force graphics mode */
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_W
comma
id|misc
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* blank screen */
id|seq1
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
op_or
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x3
)paren
suffix:semicolon
multiline_comment|/* save font at plane 2 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT0
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x4
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x2
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|4
op_star
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;vga_font0
(braket
id|i
)braket
op_assign
id|vga_r
c_func
(paren
id|fbbase
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* save font at plane 3 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT1
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x8
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x3
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
id|state-&gt;memsize
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;vga_font1
(braket
id|i
)braket
op_assign
id|vga_r
c_func
(paren
id|fbbase
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* save font at plane 0/1 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_TEXT
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;vga_text
(braket
id|i
)braket
op_assign
id|vga_r
c_func
(paren
id|fbbase
comma
id|i
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x2
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;vga_text
(braket
l_int|8192
op_plus
id|i
)braket
op_assign
id|vga_r
c_func
(paren
id|fbbase
op_plus
l_int|2
op_star
l_int|8192
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* restore regs */
id|vga_wattr
c_func
(paren
id|state-&gt;vgabase
comma
l_int|0x10
comma
id|attr10
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
id|seq2
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
id|seq4
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
id|gr4
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
id|gr5
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
id|gr6
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_W
comma
id|misc
)paren
suffix:semicolon
multiline_comment|/* unblank screen */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x3
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
)paren
suffix:semicolon
)brace
DECL|function|restore_vga_text
r_static
r_void
id|restore_vga_text
c_func
(paren
r_struct
id|vgastate
op_star
id|state
comma
r_void
id|__iomem
op_star
id|fbbase
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|misc
comma
id|gr1
comma
id|gr3
comma
id|gr4
comma
id|gr5
comma
id|gr6
comma
id|gr8
suffix:semicolon
id|u8
id|seq1
comma
id|seq2
comma
id|seq4
suffix:semicolon
multiline_comment|/* save regs */
id|misc
op_assign
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_R
)paren
suffix:semicolon
id|gr1
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_SR_ENABLE
)paren
suffix:semicolon
id|gr3
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_DATA_ROTATE
)paren
suffix:semicolon
id|gr4
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
)paren
suffix:semicolon
id|gr5
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
)paren
suffix:semicolon
id|gr6
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
)paren
suffix:semicolon
id|gr8
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_BIT_MASK
)paren
suffix:semicolon
id|seq2
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
)paren
suffix:semicolon
id|seq4
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
)paren
suffix:semicolon
multiline_comment|/* force graphics mode */
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_W
comma
id|misc
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* blank screen */
id|seq1
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
op_or
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;depth
op_eq
l_int|4
)paren
(brace
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_DATA_ROTATE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_BIT_MASK
comma
l_int|0xff
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_SR_ENABLE
comma
l_int|0x00
)paren
suffix:semicolon
)brace
multiline_comment|/* restore font at plane 2 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT0
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x4
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x2
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|4
op_star
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|vga_w
c_func
(paren
id|fbbase
comma
id|i
comma
id|saved-&gt;vga_font0
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* restore font at plane 3 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT1
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x8
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x3
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
id|state-&gt;memsize
suffix:semicolon
id|i
op_increment
)paren
id|vga_w
c_func
(paren
id|fbbase
comma
id|i
comma
id|saved-&gt;vga_font1
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* restore font at plane 0/1 */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_TEXT
)paren
(brace
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|vga_w
c_func
(paren
id|fbbase
comma
id|i
comma
id|saved-&gt;vga_text
(braket
id|i
)braket
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
l_int|0x2
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
l_int|0x6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
l_int|0x0
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
l_int|0x5
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
l_int|8192
suffix:semicolon
id|i
op_increment
)paren
id|vga_w
c_func
(paren
id|fbbase
comma
id|i
comma
id|saved-&gt;vga_text
(braket
l_int|8192
op_plus
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* unblank screen */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x3
)paren
suffix:semicolon
multiline_comment|/* restore regs */
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_W
comma
id|misc
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_SR_ENABLE
comma
id|gr1
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_DATA_ROTATE
comma
id|gr3
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_PLANE_READ
comma
id|gr4
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MODE
comma
id|gr5
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_MISC
comma
id|gr6
)paren
suffix:semicolon
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_GFX_BIT_MASK
comma
id|gr8
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|seq1
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_PLANE_WRITE
comma
id|seq2
)paren
suffix:semicolon
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_MEMORY_MODE
comma
id|seq4
)paren
suffix:semicolon
)brace
DECL|function|save_vga_mode
r_static
r_void
id|save_vga_mode
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
r_int
id|iobase
suffix:semicolon
r_int
id|i
suffix:semicolon
id|saved-&gt;misc
op_assign
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_R
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;misc
op_amp
l_int|1
)paren
id|iobase
op_assign
l_int|0x3d0
suffix:semicolon
r_else
id|iobase
op_assign
l_int|0x3b0
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
id|state-&gt;num_crtc
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;crtc
(braket
id|i
)braket
op_assign
id|vga_rcrtcs
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
comma
id|i
)paren
suffix:semicolon
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_ATT_W
comma
l_int|0x00
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
id|state-&gt;num_attr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|saved-&gt;attr
(braket
id|i
)braket
op_assign
id|vga_rattr
c_func
(paren
id|state-&gt;vgabase
comma
id|i
)paren
suffix:semicolon
)brace
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_ATT_W
comma
l_int|0x20
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
id|state-&gt;num_gfx
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;gfx
(braket
id|i
)braket
op_assign
id|vga_rgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|i
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
id|state-&gt;num_seq
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;seq
(braket
id|i
)braket
op_assign
id|vga_rseq
c_func
(paren
id|state-&gt;vgabase
comma
id|i
)paren
suffix:semicolon
)brace
DECL|function|restore_vga_mode
r_static
r_void
id|restore_vga_mode
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
r_int
id|iobase
suffix:semicolon
r_int
id|i
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_MIS_W
comma
id|saved-&gt;misc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;misc
op_amp
l_int|1
)paren
id|iobase
op_assign
l_int|0x3d0
suffix:semicolon
r_else
id|iobase
op_assign
l_int|0x3b0
suffix:semicolon
multiline_comment|/* turn off display */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|saved-&gt;seq
(braket
id|VGA_SEQ_CLOCK_MODE
)braket
op_or
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* disable sequencer */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* enable palette addressing */
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_ATT_W
comma
l_int|0x00
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|state-&gt;num_seq
suffix:semicolon
id|i
op_increment
)paren
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|i
comma
id|saved-&gt;seq
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* unprotect vga regs */
id|vga_wcrtcs
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
comma
l_int|17
comma
id|saved-&gt;crtc
(braket
l_int|17
)braket
op_amp
op_complement
l_int|0x80
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
id|state-&gt;num_crtc
suffix:semicolon
id|i
op_increment
)paren
id|vga_wcrtcs
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
comma
id|i
comma
id|saved-&gt;crtc
(braket
id|i
)braket
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
id|state-&gt;num_gfx
suffix:semicolon
id|i
op_increment
)paren
id|vga_wgfx
c_func
(paren
id|state-&gt;vgabase
comma
id|i
comma
id|saved-&gt;gfx
(braket
id|i
)braket
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
id|state-&gt;num_attr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|vga_wattr
c_func
(paren
id|state-&gt;vgabase
comma
id|i
comma
id|saved-&gt;attr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* reenable sequencer */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_RESET
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* turn display on */
id|vga_wseq
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_SEQ_CLOCK_MODE
comma
id|saved-&gt;seq
(braket
id|VGA_SEQ_CLOCK_MODE
)braket
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
multiline_comment|/* disable video/palette source */
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|iobase
op_plus
l_int|0xa
)paren
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_ATT_W
comma
l_int|0x20
)paren
suffix:semicolon
)brace
DECL|function|save_vga_cmap
r_static
r_void
id|save_vga_cmap
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
id|i
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_MSK
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* assumes DAC is readable and writable */
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_IR
comma
l_int|0x00
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
l_int|768
suffix:semicolon
id|i
op_increment
)paren
id|saved-&gt;vga_cmap
(braket
id|i
)braket
op_assign
id|vga_r
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_D
)paren
suffix:semicolon
)brace
DECL|function|restore_vga_cmap
r_static
r_void
id|restore_vga_cmap
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_int
id|i
suffix:semicolon
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_MSK
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* assumes DAC is readable and writable */
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_IW
comma
l_int|0x00
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
l_int|768
suffix:semicolon
id|i
op_increment
)paren
id|vga_w
c_func
(paren
id|state-&gt;vgabase
comma
id|VGA_PEL_D
comma
id|saved-&gt;vga_cmap
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|vga_cleanup
r_static
r_void
id|vga_cleanup
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;vidstate
op_ne
l_int|NULL
)paren
(brace
r_struct
id|regstate
op_star
id|saved
op_assign
(paren
r_struct
id|regstate
op_star
)paren
id|state-&gt;vidstate
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;vga_font0
)paren
id|vfree
c_func
(paren
id|saved-&gt;vga_font0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;vga_font1
)paren
id|vfree
c_func
(paren
id|saved-&gt;vga_font1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;vga_text
)paren
id|vfree
c_func
(paren
id|saved-&gt;vga_text
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;vga_cmap
)paren
id|vfree
c_func
(paren
id|saved-&gt;vga_cmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved-&gt;attr
)paren
id|vfree
c_func
(paren
id|saved-&gt;attr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|saved
)paren
suffix:semicolon
id|state-&gt;vidstate
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|save_vga
r_int
id|save_vga
c_func
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_struct
id|regstate
op_star
id|saved
suffix:semicolon
id|saved
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|regstate
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saved
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|memset
(paren
id|saved
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|regstate
)paren
)paren
suffix:semicolon
id|state-&gt;vidstate
op_assign
(paren
r_void
op_star
)paren
id|saved
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_CMAP
)paren
(brace
id|saved-&gt;vga_cmap
op_assign
id|vmalloc
c_func
(paren
l_int|768
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saved-&gt;vga_cmap
)paren
(brace
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|save_vga_cmap
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_MODE
)paren
(brace
r_int
id|total
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;num_attr
OL
l_int|21
)paren
id|state-&gt;num_attr
op_assign
l_int|21
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;num_crtc
OL
l_int|25
)paren
id|state-&gt;num_crtc
op_assign
l_int|25
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;num_gfx
OL
l_int|9
)paren
id|state-&gt;num_gfx
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;num_seq
OL
l_int|5
)paren
id|state-&gt;num_seq
op_assign
l_int|5
suffix:semicolon
id|total
op_assign
id|state-&gt;num_attr
op_plus
id|state-&gt;num_crtc
op_plus
id|state-&gt;num_gfx
op_plus
id|state-&gt;num_seq
suffix:semicolon
id|saved-&gt;attr
op_assign
id|vmalloc
c_func
(paren
id|total
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saved-&gt;attr
)paren
(brace
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|saved-&gt;crtc
op_assign
id|saved-&gt;attr
op_plus
id|state-&gt;num_attr
suffix:semicolon
id|saved-&gt;gfx
op_assign
id|saved-&gt;crtc
op_plus
id|state-&gt;num_crtc
suffix:semicolon
id|saved-&gt;seq
op_assign
id|saved-&gt;gfx
op_plus
id|state-&gt;num_gfx
suffix:semicolon
id|save_vga_mode
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONTS
)paren
(brace
r_void
id|__iomem
op_star
id|fbbase
suffix:semicolon
multiline_comment|/* exit if window is less than 32K */
r_if
c_cond
(paren
id|state-&gt;memsize
op_logical_and
id|state-&gt;memsize
OL
l_int|4
op_star
l_int|8192
)paren
(brace
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;memsize
)paren
id|state-&gt;memsize
op_assign
l_int|8
op_star
l_int|8192
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;membase
)paren
id|state-&gt;membase
op_assign
l_int|0xA0000
suffix:semicolon
id|fbbase
op_assign
id|ioremap
c_func
(paren
id|state-&gt;membase
comma
id|state-&gt;memsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fbbase
)paren
(brace
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n;&t;&t; * save only first 32K used by vgacon&n;&t;&t; */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT0
)paren
(brace
id|saved-&gt;vga_font0
op_assign
id|vmalloc
c_func
(paren
l_int|4
op_star
l_int|8192
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saved-&gt;vga_font0
)paren
(brace
id|iounmap
c_func
(paren
id|fbbase
)paren
suffix:semicolon
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* &n;&t;&t; * largely unused, but if required by the caller&n;&t;&t; * we&squot;ll just save everything.&n;&t;&t; */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONT1
)paren
(brace
id|saved-&gt;vga_font1
op_assign
id|vmalloc
c_func
(paren
id|state-&gt;memsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saved-&gt;vga_font1
)paren
(brace
id|iounmap
c_func
(paren
id|fbbase
)paren
suffix:semicolon
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Save 8K at plane0[0], and 8K at plane1[16K]&n;&t;&t; */
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_TEXT
)paren
(brace
id|saved-&gt;vga_text
op_assign
id|vmalloc
c_func
(paren
l_int|8192
op_star
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|saved-&gt;vga_text
)paren
(brace
id|iounmap
c_func
(paren
id|fbbase
)paren
suffix:semicolon
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|save_vga_text
c_func
(paren
id|state
comma
id|fbbase
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|fbbase
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|restore_vga
r_int
id|restore_vga
(paren
r_struct
id|vgastate
op_star
id|state
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;vidstate
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_MODE
)paren
id|restore_vga_mode
c_func
(paren
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_FONTS
)paren
(brace
r_void
id|__iomem
op_star
id|fbbase
op_assign
id|ioremap
c_func
(paren
id|state-&gt;membase
comma
id|state-&gt;memsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fbbase
)paren
(brace
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|restore_vga_text
c_func
(paren
id|state
comma
id|fbbase
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|fbbase
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;flags
op_amp
id|VGA_SAVE_CMAP
)paren
id|restore_vga_cmap
c_func
(paren
id|state
)paren
suffix:semicolon
id|vga_cleanup
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|save_vga
id|EXPORT_SYMBOL
c_func
(paren
id|save_vga
)paren
suffix:semicolon
DECL|variable|restore_vga
id|EXPORT_SYMBOL
c_func
(paren
id|restore_vga
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@users.sf.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VGA State Save/Restore&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
