multiline_comment|/*&n; *  ATI Mach64 Hardware Acceleration&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#include &lt;video/mach64.h&gt;
macro_line|#include &quot;atyfb.h&quot;
multiline_comment|/*&n;     *  Text console acceleration&n;     */
r_static
r_void
id|fbcon_aty_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
r_static
r_void
id|fbcon_aty_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Generic Mach64 routines&n;     */
DECL|function|aty_reset_engine
r_void
id|aty_reset_engine
c_func
(paren
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* reset engine */
id|aty_st_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|par
)paren
op_amp
op_complement
id|GUI_ENGINE_ENABLE
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* enable engine */
id|aty_st_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|GEN_TEST_CNTL
comma
id|par
)paren
op_or
id|GUI_ENGINE_ENABLE
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* ensure engine is not locked up by clearing any FIFO or */
multiline_comment|/* HOST errors */
id|aty_st_le32
c_func
(paren
id|BUS_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|BUS_CNTL
comma
id|par
)paren
op_or
id|BUS_HOST_ERR_ACK
op_or
id|BUS_FIFO_ERR_ACK
comma
id|par
)paren
suffix:semicolon
)brace
DECL|function|reset_GTC_3D_engine
r_static
r_void
id|reset_GTC_3D_engine
c_func
(paren
r_const
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
id|aty_st_le32
c_func
(paren
id|SCALE_3D_CNTL
comma
l_int|0xc0
comma
id|par
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|GTC_3D_RESET_DELAY
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SETUP_CNTL
comma
l_int|0x00
comma
id|par
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|GTC_3D_RESET_DELAY
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SCALE_3D_CNTL
comma
l_int|0x00
comma
id|par
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|GTC_3D_RESET_DELAY
)paren
suffix:semicolon
)brace
DECL|function|aty_init_engine
r_void
id|aty_init_engine
c_func
(paren
r_struct
id|atyfb_par
op_star
id|par
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|u32
id|pitch_value
suffix:semicolon
multiline_comment|/* determine modal information from global mode structure */
id|pitch_value
op_assign
id|par-&gt;crtc.vxres
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;crtc.bpp
op_eq
l_int|24
)paren
(brace
multiline_comment|/* In 24 bpp, the engine is in 8 bpp - this requires that all */
multiline_comment|/* horizontal coordinates and widths must be adjusted */
id|pitch_value
op_assign
id|pitch_value
op_star
l_int|3
suffix:semicolon
)brace
multiline_comment|/* On GTC (RagePro), we need to reset the 3D engine before */
r_if
c_cond
(paren
id|M64_HAS
c_func
(paren
id|RESET_3D
)paren
)paren
id|reset_GTC_3D_engine
c_func
(paren
id|par
)paren
suffix:semicolon
multiline_comment|/* Reset engine, enable, and clear any engine errors */
id|aty_reset_engine
c_func
(paren
id|par
)paren
suffix:semicolon
multiline_comment|/* Ensure that vga page pointers are set to zero - the upper */
multiline_comment|/* page pointers are set to 1 to handle overflows in the */
multiline_comment|/* lower page */
id|aty_st_le32
c_func
(paren
id|MEM_VGA_WP_SEL
comma
l_int|0x00010000
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|MEM_VGA_RP_SEL
comma
l_int|0x00010000
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* ---- Setup standard engine context ---- */
multiline_comment|/* All GUI registers here are FIFOed - therefore, wait for */
multiline_comment|/* the appropriate number of empty FIFO entries */
id|wait_for_fifo
c_func
(paren
l_int|14
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* enable all registers to be loaded for context loads */
id|aty_st_le32
c_func
(paren
id|CONTEXT_MASK
comma
l_int|0xFFFFFFFF
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set destination pitch to modal pitch, set offset to zero */
id|aty_st_le32
c_func
(paren
id|DST_OFF_PITCH
comma
(paren
id|pitch_value
op_div
l_int|8
)paren
op_lshift
l_int|22
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* zero these registers (set them to a known state) */
id|aty_st_le32
c_func
(paren
id|DST_Y_X
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_HEIGHT
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_BRES_ERR
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_BRES_INC
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_BRES_DEC
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set destination drawing attributes */
id|aty_st_le32
c_func
(paren
id|DST_CNTL
comma
id|DST_LAST_PEL
op_or
id|DST_Y_TOP_TO_BOTTOM
op_or
id|DST_X_LEFT_TO_RIGHT
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set source pitch to modal pitch, set offset to zero */
id|aty_st_le32
c_func
(paren
id|SRC_OFF_PITCH
comma
(paren
id|pitch_value
op_div
l_int|8
)paren
op_lshift
l_int|22
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set these registers to a known state */
id|aty_st_le32
c_func
(paren
id|SRC_Y_X
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SRC_HEIGHT1_WIDTH1
comma
l_int|1
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SRC_Y_X_START
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SRC_HEIGHT2_WIDTH2
comma
l_int|1
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set source pixel retrieving attributes */
id|aty_st_le32
c_func
(paren
id|SRC_CNTL
comma
id|SRC_LINE_X_LEFT_TO_RIGHT
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set host attributes */
id|wait_for_fifo
c_func
(paren
l_int|13
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|HOST_CNTL
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set pattern attributes */
id|aty_st_le32
c_func
(paren
id|PAT_REG0
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|PAT_REG1
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|PAT_CNTL
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set scissors to modal size */
id|aty_st_le32
c_func
(paren
id|SC_LEFT
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SC_TOP
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SC_BOTTOM
comma
id|par-&gt;crtc.vyres
op_minus
l_int|1
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SC_RIGHT
comma
id|pitch_value
op_minus
l_int|1
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set background color to minimum value (usually BLACK) */
id|aty_st_le32
c_func
(paren
id|DP_BKGD_CLR
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set foreground color to maximum value (usually WHITE) */
id|aty_st_le32
c_func
(paren
id|DP_FRGD_CLR
comma
l_int|0xFFFFFFFF
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set write mask to effect all pixel bits */
id|aty_st_le32
c_func
(paren
id|DP_WRITE_MASK
comma
l_int|0xFFFFFFFF
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set foreground mix to overpaint and background mix to */
multiline_comment|/* no-effect */
id|aty_st_le32
c_func
(paren
id|DP_MIX
comma
id|FRGD_MIX_S
op_or
id|BKGD_MIX_D
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set primary source pixel channel to foreground color */
multiline_comment|/* register */
id|aty_st_le32
c_func
(paren
id|DP_SRC
comma
id|FRGD_SRC_FRGD_CLR
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set compare functionality to false (no-effect on */
multiline_comment|/* destination) */
id|wait_for_fifo
c_func
(paren
l_int|3
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CLR_CMP_CLR
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CLR_CMP_MASK
comma
l_int|0xFFFFFFFF
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CLR_CMP_CNTL
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* set pixel depth */
id|wait_for_fifo
c_func
(paren
l_int|2
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DP_PIX_WIDTH
comma
id|par-&gt;crtc.dp_pix_width
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DP_CHAIN_MASK
comma
id|par-&gt;crtc.dp_chain_mask
comma
id|par
)paren
suffix:semicolon
id|wait_for_fifo
c_func
(paren
l_int|5
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SCALE_3D_CNTL
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|Z_CNTL
comma
l_int|0
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|CRTC_INT_CNTL
comma
id|aty_ld_le32
c_func
(paren
id|CRTC_INT_CNTL
comma
id|par
)paren
op_amp
op_complement
l_int|0x20
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|GUI_TRAJ_CNTL
comma
l_int|0x100023
comma
id|par
)paren
suffix:semicolon
multiline_comment|/* insure engine is idle before leaving */
id|wait_for_idle
c_func
(paren
id|par
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Accelerated functions&n;     */
DECL|function|draw_rect
r_static
r_inline
r_void
id|draw_rect
c_func
(paren
id|s16
id|x
comma
id|s16
id|y
comma
id|u16
id|width
comma
id|u16
id|height
comma
r_struct
id|atyfb_par
op_star
id|par
)paren
(brace
multiline_comment|/* perform rectangle fill */
id|wait_for_fifo
c_func
(paren
l_int|2
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_Y_X
comma
(paren
id|x
op_lshift
l_int|16
)paren
op_or
id|y
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_HEIGHT_WIDTH
comma
(paren
id|width
op_lshift
l_int|16
)paren
op_or
id|height
comma
id|par
)paren
suffix:semicolon
id|par-&gt;blitter_may_be_busy
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|atyfb_copyarea
r_static
r_void
id|atyfb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_copyarea
op_star
id|area
)paren
(brace
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
id|u32
id|direction
op_assign
id|DST_LAST_PEL
suffix:semicolon
id|u32
id|pitch_value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area-&gt;width
op_logical_or
op_logical_neg
id|area-&gt;height
)paren
r_return
suffix:semicolon
id|pitch_value
op_assign
id|par-&gt;crtc.vxres
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;crtc.bpp
op_eq
l_int|24
)paren
(brace
multiline_comment|/* In 24 bpp, the engine is in 8 bpp - this requires that all */
multiline_comment|/* horizontal coordinates and widths must be adjusted */
id|pitch_value
op_mul_assign
l_int|3
suffix:semicolon
id|area-&gt;sx
op_mul_assign
l_int|3
suffix:semicolon
id|area-&gt;dx
op_mul_assign
l_int|3
suffix:semicolon
id|area-&gt;width
op_mul_assign
l_int|3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|area-&gt;sy
OL
id|area-&gt;dy
)paren
(brace
id|area-&gt;dy
op_add_assign
id|area-&gt;height
op_minus
l_int|1
suffix:semicolon
id|area-&gt;sy
op_add_assign
id|area-&gt;height
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|direction
op_or_assign
id|DST_Y_TOP_TO_BOTTOM
suffix:semicolon
r_if
c_cond
(paren
id|area-&gt;sx
OL
id|area-&gt;dx
)paren
(brace
id|area-&gt;dx
op_add_assign
id|area-&gt;width
op_minus
l_int|1
suffix:semicolon
id|area-&gt;sx
op_add_assign
id|area-&gt;width
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|direction
op_or_assign
id|DST_X_LEFT_TO_RIGHT
suffix:semicolon
id|wait_for_fifo
c_func
(paren
l_int|4
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DP_SRC
comma
id|FRGD_SRC_BLIT
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SRC_Y_X
comma
(paren
id|area-&gt;sx
op_lshift
l_int|16
)paren
op_or
id|area-&gt;sy
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|SRC_HEIGHT1_WIDTH1
comma
(paren
id|area-&gt;width
op_lshift
l_int|16
)paren
op_or
id|area-&gt;height
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_CNTL
comma
id|direction
comma
id|par
)paren
suffix:semicolon
id|draw_rect
c_func
(paren
id|area-&gt;dx
comma
id|area-&gt;dy
comma
id|area-&gt;width
comma
id|area-&gt;height
comma
id|par
)paren
suffix:semicolon
)brace
DECL|function|atyfb_fillrect
r_void
id|atyfb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_struct
id|fb_fillrect
op_star
id|rect
)paren
(brace
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rect-&gt;width
op_logical_or
op_logical_neg
id|rect-&gt;height
)paren
r_return
suffix:semicolon
id|rect-&gt;color
op_or_assign
(paren
id|rect-&gt;color
op_lshift
l_int|8
)paren
suffix:semicolon
id|rect-&gt;color
op_or_assign
(paren
id|rect-&gt;color
op_lshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;crtc.bpp
op_eq
l_int|24
)paren
(brace
multiline_comment|/* In 24 bpp, the engine is in 8 bpp - this requires that all */
multiline_comment|/* horizontal coordinates and widths must be adjusted */
id|rect-&gt;dx
op_mul_assign
l_int|3
suffix:semicolon
id|rect-&gt;width
op_mul_assign
l_int|3
suffix:semicolon
)brace
id|wait_for_fifo
c_func
(paren
l_int|3
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DP_FRGD_CLR
comma
id|rect-&gt;color
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DP_SRC
comma
id|BKGD_SRC_BKGD_CLR
op_or
id|FRGD_SRC_FRGD_CLR
op_or
id|MONO_SRC_ONE
comma
id|par
)paren
suffix:semicolon
id|aty_st_le32
c_func
(paren
id|DST_CNTL
comma
id|DST_LAST_PEL
op_or
id|DST_Y_TOP_TO_BOTTOM
op_or
id|DST_X_LEFT_TO_RIGHT
comma
id|par
)paren
suffix:semicolon
id|draw_rect
c_func
(paren
id|rect-&gt;dx
comma
id|rect-&gt;dy
comma
id|rect-&gt;width
comma
id|rect-&gt;height
comma
id|par
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Text console acceleration&n;     */
DECL|function|fbcon_aty_bmove
r_static
r_void
id|fbcon_aty_bmove
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
id|p-&gt;fb_info
suffix:semicolon
r_struct
id|fb_copyarea
id|area
suffix:semicolon
macro_line|#ifdef __sparc__
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
(paren
id|info-&gt;par
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|area.sx
op_assign
id|sx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|area.sy
op_assign
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|area.dx
op_assign
id|dx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|area.dy
op_assign
id|dy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|area.width
op_assign
id|width
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|area.height
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|atyfb_copyarea
c_func
(paren
id|info
comma
op_amp
id|area
)paren
suffix:semicolon
)brace
DECL|function|fbcon_aty_clear
r_static
r_void
id|fbcon_aty_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_struct
id|fb_info
op_star
id|info
op_assign
id|p-&gt;fb_info
suffix:semicolon
r_struct
id|fb_fillrect
id|region
suffix:semicolon
macro_line|#ifdef __sparc__
r_struct
id|atyfb_par
op_star
id|par
op_assign
(paren
r_struct
id|atyfb_par
op_star
)paren
(paren
id|info-&gt;par
)paren
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;mmaped
op_logical_and
(paren
op_logical_neg
id|info-&gt;display_fg
op_logical_or
id|info-&gt;display_fg-&gt;vc_num
op_eq
id|par-&gt;vtconsole
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|region.color
op_assign
id|attr_bgcol_ec
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|region.color
op_or_assign
(paren
id|region.color
op_lshift
l_int|8
)paren
suffix:semicolon
id|region.color
op_or_assign
(paren
id|region.color
op_lshift
l_int|16
)paren
suffix:semicolon
id|region.dx
op_assign
id|sx
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|region.dy
op_assign
id|sy
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|region.width
op_assign
id|width
op_star
id|fontwidth
c_func
(paren
id|p
)paren
suffix:semicolon
id|region.height
op_assign
id|height
op_star
id|fontheight
c_func
(paren
id|p
)paren
suffix:semicolon
id|region.rop
op_assign
id|ROP_COPY
suffix:semicolon
id|atyfb_fillrect
c_func
(paren
id|info
comma
op_amp
id|region
)paren
suffix:semicolon
)brace
macro_line|#ifdef __sparc__
DECL|macro|check_access
mdefine_line|#define check_access &bslash;&n;    if (par-&gt;mmaped &amp;&amp; (!info-&gt;display_fg &bslash;&n;&t;|| info-&gt;display_fg-&gt;vc_num == par-&gt;vtconsole)) &bslash;&n;&t;return;
macro_line|#else
DECL|macro|check_access
mdefine_line|#define check_access do { } while (0)
macro_line|#endif
DECL|macro|DEF_FBCON_ATY_OP
mdefine_line|#define DEF_FBCON_ATY_OP(name, call, args...) &bslash;&n;static void name(struct vc_data *conp, struct display *p, args) &bslash;&n;{ &bslash;&n;    struct fb_info *info = p-&gt;fb_info; &bslash;&n;    struct atyfb_par *par = (struct atyfb_par *) info-&gt;par; &bslash;&n;    check_access; &bslash;&n;    if (par-&gt;blitter_may_be_busy) &bslash;&n;&t;wait_for_idle(par); &bslash;&n;    call; &bslash;&n;}
DECL|macro|DEF_FBCON_ATY
mdefine_line|#define DEF_FBCON_ATY(width) &bslash;&n;    DEF_FBCON_ATY_OP(fbcon_aty##width##_putc, &bslash;&n;&t;&t;     fbcon_cfb##width##_putc(conp, p, c, yy, xx), &bslash;&n;&t;&t;     int c, int yy, int xx) &bslash;&n;    DEF_FBCON_ATY_OP(fbcon_aty##width##_putcs, &bslash;&n;&t;&t;     fbcon_cfb##width##_putcs(conp, p, s, count, yy, xx), &bslash;&n;&t;&t;     const unsigned short *s, int count, int yy, int xx) &bslash;&n;    DEF_FBCON_ATY_OP(fbcon_aty##width##_clear_margins, &bslash;&n;&t;&t;     fbcon_cfb##width##_clear_margins(conp, p, bottom_only), &bslash;&n;&t;&t;     int bottom_only) &bslash;&n; &bslash;&n;const struct display_switch fbcon_aty##width = { &bslash;&n;    setup:&t;&t;fbcon_cfb##width##_setup, &bslash;&n;    bmove:&t;&t;fbcon_aty_bmove, &bslash;&n;    clear:&t;&t;fbcon_aty_clear, &bslash;&n;    putc:&t;&t;fbcon_aty##width##_putc, &bslash;&n;    putcs:&t;&t;fbcon_aty##width##_putcs, &bslash;&n;    revc:&t;&t;fbcon_cfb##width##_revc, &bslash;&n;    clear_margins:&t;fbcon_aty##width##_clear_margins, &bslash;&n;    fontwidthmask:&t;FONTWIDTH(4)|FONTWIDTH(8)|FONTWIDTH(12)|FONTWIDTH(16) &bslash;&n;};
macro_line|#ifdef FBCON_HAS_CFB8
id|DEF_FBCON_ATY
c_func
(paren
l_int|8
)paren
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
id|DEF_FBCON_ATY
c_func
(paren
l_int|16
)paren
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
id|DEF_FBCON_ATY
c_func
(paren
l_int|24
)paren
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
id|DEF_FBCON_ATY
c_func
(paren
l_int|32
)paren
macro_line|#endif
eof
