multiline_comment|/*&n; * Permedia2 framebuffer driver definitions.&n; * Copyright (c) 1998-1999 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)&n; * --------------------------------------------------------------------------&n; * $Id: pm2fb.h,v 1.21 1999/01/28 13:18:07 illo Exp $&n; * --------------------------------------------------------------------------&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef PM2FB_H
DECL|macro|PM2FB_H
mdefine_line|#define PM2FB_H
DECL|macro|PM2_REFERENCE_CLOCK
mdefine_line|#define PM2_REFERENCE_CLOCK&t;14318&t;&t;&t;/* in KHz */
DECL|macro|PM2_MAX_PIXCLOCK
mdefine_line|#define PM2_MAX_PIXCLOCK&t;230000&t;&t;&t;/* in KHz */
DECL|macro|PM2_REGS_SIZE
mdefine_line|#define PM2_REGS_SIZE&t;&t;0x10000
DECL|macro|PM2TAG
mdefine_line|#define PM2TAG(r) (u32 )(((r)-0x8000)&gt;&gt;3)
multiline_comment|/*****************************************************************************&n; * Permedia2 registers used in the framebuffer&n; *****************************************************************************/
DECL|macro|PM2R_RESET_STATUS
mdefine_line|#define PM2R_RESET_STATUS&t;&t;&t;&t;0x0000
DECL|macro|PM2R_IN_FIFO_SPACE
mdefine_line|#define PM2R_IN_FIFO_SPACE&t;&t;&t;&t;0x0018
DECL|macro|PM2R_OUT_FIFO_WORDS
mdefine_line|#define PM2R_OUT_FIFO_WORDS&t;&t;&t;&t;0x0020
DECL|macro|PM2R_APERTURE_ONE
mdefine_line|#define PM2R_APERTURE_ONE&t;&t;&t;&t;0x0050
DECL|macro|PM2R_APERTURE_TWO
mdefine_line|#define PM2R_APERTURE_TWO&t;&t;&t;&t;0x0058
DECL|macro|PM2R_FIFO_DISCON
mdefine_line|#define PM2R_FIFO_DISCON&t;&t;&t;&t;0x0068
DECL|macro|PM2R_CHIP_CONFIG
mdefine_line|#define PM2R_CHIP_CONFIG&t;&t;&t;&t;0x0070
DECL|macro|PM2R_REBOOT
mdefine_line|#define PM2R_REBOOT&t;&t;&t;&t;&t;0x1000
DECL|macro|PM2R_MEM_CONTROL
mdefine_line|#define PM2R_MEM_CONTROL&t;&t;&t;&t;0x1040
DECL|macro|PM2R_BOOT_ADDRESS
mdefine_line|#define PM2R_BOOT_ADDRESS&t;&t;&t;&t;0x1080
DECL|macro|PM2R_MEM_CONFIG
mdefine_line|#define PM2R_MEM_CONFIG&t;&t;&t;&t;&t;0x10c0
DECL|macro|PM2R_BYPASS_WRITE_MASK
mdefine_line|#define PM2R_BYPASS_WRITE_MASK&t;&t;&t;&t;0x1100
DECL|macro|PM2R_FRAMEBUFFER_WRITE_MASK
mdefine_line|#define PM2R_FRAMEBUFFER_WRITE_MASK&t;&t;&t;0x1140
DECL|macro|PM2R_OUT_FIFO
mdefine_line|#define PM2R_OUT_FIFO&t;&t;&t;&t;&t;0x2000
DECL|macro|PM2R_SCREEN_BASE
mdefine_line|#define PM2R_SCREEN_BASE&t;&t;&t;&t;0x3000
DECL|macro|PM2R_SCREEN_STRIDE
mdefine_line|#define PM2R_SCREEN_STRIDE&t;&t;&t;&t;0x3008
DECL|macro|PM2R_H_TOTAL
mdefine_line|#define PM2R_H_TOTAL&t;&t;&t;&t;&t;0x3010
DECL|macro|PM2R_HG_END
mdefine_line|#define PM2R_HG_END&t;&t;&t;&t;&t;0x3018
DECL|macro|PM2R_HB_END
mdefine_line|#define PM2R_HB_END&t;&t;&t;&t;&t;0x3020
DECL|macro|PM2R_HS_START
mdefine_line|#define PM2R_HS_START&t;&t;&t;&t;&t;0x3028
DECL|macro|PM2R_HS_END
mdefine_line|#define PM2R_HS_END&t;&t;&t;&t;&t;0x3030
DECL|macro|PM2R_V_TOTAL
mdefine_line|#define PM2R_V_TOTAL&t;&t;&t;&t;&t;0x3038
DECL|macro|PM2R_VB_END
mdefine_line|#define PM2R_VB_END&t;&t;&t;&t;&t;0x3040
DECL|macro|PM2R_VS_START
mdefine_line|#define PM2R_VS_START&t;&t;&t;&t;&t;0x3048
DECL|macro|PM2R_VS_END
mdefine_line|#define PM2R_VS_END&t;&t;&t;&t;&t;0x3050
DECL|macro|PM2R_VIDEO_CONTROL
mdefine_line|#define PM2R_VIDEO_CONTROL&t;&t;&t;&t;0x3058
DECL|macro|PM2R_LINE_COUNT
mdefine_line|#define PM2R_LINE_COUNT&t;&t;&t;&t;&t;0x3070
DECL|macro|PM2R_FIFO_CONTROL
mdefine_line|#define PM2R_FIFO_CONTROL&t;&t;&t;&t;0x3078
DECL|macro|PM2R_RD_PALETTE_WRITE_ADDRESS
mdefine_line|#define PM2R_RD_PALETTE_WRITE_ADDRESS&t;&t;&t;0x4000
DECL|macro|PM2R_RD_PALETTE_DATA
mdefine_line|#define PM2R_RD_PALETTE_DATA&t;&t;&t;&t;0x4008
DECL|macro|PM2R_RD_PALETTE_READ_ADDRESS
mdefine_line|#define PM2R_RD_PALETTE_READ_ADDRESS&t;&t;&t;0x4018
DECL|macro|PM2R_RD_INDEXED_DATA
mdefine_line|#define PM2R_RD_INDEXED_DATA&t;&t;&t;&t;0x4050
DECL|macro|PM2R_START_X_DOM
mdefine_line|#define PM2R_START_X_DOM&t;&t;&t;&t;0x8000
DECL|macro|PM2R_D_X_DOM
mdefine_line|#define PM2R_D_X_DOM&t;&t;&t;&t;&t;0x8008
DECL|macro|PM2R_START_X_SUB
mdefine_line|#define PM2R_START_X_SUB&t;&t;&t;&t;0x8010
DECL|macro|PM2R_D_X_SUB
mdefine_line|#define PM2R_D_X_SUB&t;&t;&t;&t;&t;0x8018
DECL|macro|PM2R_START_Y
mdefine_line|#define PM2R_START_Y&t;&t;&t;&t;&t;0x8020
DECL|macro|PM2R_D_Y
mdefine_line|#define PM2R_D_Y&t;&t;&t;&t;&t;0x8028
DECL|macro|PM2R_COUNT
mdefine_line|#define PM2R_COUNT&t;&t;&t;&t;&t;0x8030
DECL|macro|PM2R_RENDER
mdefine_line|#define PM2R_RENDER&t;&t;&t;&t;&t;0x8038
DECL|macro|PM2R_RECTANGLE_ORIGIN
mdefine_line|#define PM2R_RECTANGLE_ORIGIN&t;&t;&t;&t;0x80d0
DECL|macro|PM2R_RECTANGLE_SIZE
mdefine_line|#define PM2R_RECTANGLE_SIZE&t;&t;&t;&t;0x80d8
DECL|macro|PM2R_PACKED_DATA_LIMITS
mdefine_line|#define PM2R_PACKED_DATA_LIMITS&t;&t;&t;&t;0x8150
DECL|macro|PM2R_SCISSOR_MODE
mdefine_line|#define PM2R_SCISSOR_MODE&t;&t;&t;&t;0x8180
DECL|macro|PM2R_SCREEN_SIZE
mdefine_line|#define PM2R_SCREEN_SIZE&t;&t;&t;&t;0x8198
DECL|macro|PM2R_AREA_STIPPLE_MODE
mdefine_line|#define PM2R_AREA_STIPPLE_MODE&t;&t;&t;&t;0x81a0
DECL|macro|PM2R_WINDOW_ORIGIN
mdefine_line|#define PM2R_WINDOW_ORIGIN&t;&t;&t;&t;0x81c8
DECL|macro|PM2R_TEXTURE_ADDRESS_MODE
mdefine_line|#define PM2R_TEXTURE_ADDRESS_MODE&t;&t;&t;0x8380
DECL|macro|PM2R_TEXTURE_MAP_FORMAT
mdefine_line|#define PM2R_TEXTURE_MAP_FORMAT&t;&t;&t;&t;0x8588
DECL|macro|PM2R_TEXTURE_DATA_FORMAT
mdefine_line|#define PM2R_TEXTURE_DATA_FORMAT&t;&t;&t;0x8590
DECL|macro|PM2R_TEXTURE_READ_MODE
mdefine_line|#define PM2R_TEXTURE_READ_MODE&t;&t;&t;&t;0x8670
DECL|macro|PM2R_TEXEL_LUT_MODE
mdefine_line|#define PM2R_TEXEL_LUT_MODE&t;&t;&t;&t;0x8678
DECL|macro|PM2R_TEXTURE_COLOR_MODE
mdefine_line|#define PM2R_TEXTURE_COLOR_MODE&t;&t;&t;&t;0x8680
DECL|macro|PM2R_FOG_MODE
mdefine_line|#define PM2R_FOG_MODE&t;&t;&t;&t;&t;0x8690
DECL|macro|PM2R_COLOR_DDA_MODE
mdefine_line|#define PM2R_COLOR_DDA_MODE&t;&t;&t;&t;0x87e0
DECL|macro|PM2R_ALPHA_BLEND_MODE
mdefine_line|#define PM2R_ALPHA_BLEND_MODE&t;&t;&t;&t;0x8810
DECL|macro|PM2R_DITHER_MODE
mdefine_line|#define PM2R_DITHER_MODE&t;&t;&t;&t;0x8818
DECL|macro|PM2R_FB_SOFT_WRITE_MASK
mdefine_line|#define PM2R_FB_SOFT_WRITE_MASK&t;&t;&t;&t;0x8820
DECL|macro|PM2R_LOGICAL_OP_MODE
mdefine_line|#define PM2R_LOGICAL_OP_MODE&t;&t;&t;&t;0x8828
DECL|macro|PM2R_LB_READ_MODE
mdefine_line|#define PM2R_LB_READ_MODE&t;&t;&t;&t;0x8880
DECL|macro|PM2R_LB_READ_FORMAT
mdefine_line|#define PM2R_LB_READ_FORMAT&t;&t;&t;&t;0x8888
DECL|macro|PM2R_LB_SOURCE_OFFSET
mdefine_line|#define PM2R_LB_SOURCE_OFFSET&t;&t;&t;&t;0x8890
DECL|macro|PM2R_LB_WINDOW_BASE
mdefine_line|#define PM2R_LB_WINDOW_BASE&t;&t;&t;&t;0x88b8
DECL|macro|PM2R_LB_WRITE_FORMAT
mdefine_line|#define PM2R_LB_WRITE_FORMAT&t;&t;&t;&t;0x88c8
DECL|macro|PM2R_STENCIL_MODE
mdefine_line|#define PM2R_STENCIL_MODE&t;&t;&t;&t;0x8988
DECL|macro|PM2R_DEPTH_MODE
mdefine_line|#define PM2R_DEPTH_MODE&t;&t;&t;&t;&t;0x89a0
DECL|macro|PM2R_FB_READ_MODE
mdefine_line|#define PM2R_FB_READ_MODE&t;&t;&t;&t;0x8a80
DECL|macro|PM2R_FB_SOURCE_OFFSET
mdefine_line|#define PM2R_FB_SOURCE_OFFSET&t;&t;&t;&t;0x8a88
DECL|macro|PM2R_FB_PIXEL_OFFSET
mdefine_line|#define PM2R_FB_PIXEL_OFFSET&t;&t;&t;&t;0x8a90
DECL|macro|PM2R_FB_WINDOW_BASE
mdefine_line|#define PM2R_FB_WINDOW_BASE&t;&t;&t;&t;0x8ab0
DECL|macro|PM2R_FB_WRITE_MODE
mdefine_line|#define PM2R_FB_WRITE_MODE&t;&t;&t;&t;0x8ab8
DECL|macro|PM2R_FB_HARD_WRITE_MASK
mdefine_line|#define PM2R_FB_HARD_WRITE_MASK&t;&t;&t;&t;0x8ac0
DECL|macro|PM2R_FB_BLOCK_COLOR
mdefine_line|#define PM2R_FB_BLOCK_COLOR&t;&t;&t;&t;0x8ac8
DECL|macro|PM2R_FB_READ_PIXEL
mdefine_line|#define PM2R_FB_READ_PIXEL&t;&t;&t;&t;0x8ad0
DECL|macro|PM2R_FILTER_MODE
mdefine_line|#define PM2R_FILTER_MODE&t;&t;&t;&t;0x8c00
DECL|macro|PM2R_SYNC
mdefine_line|#define PM2R_SYNC&t;&t;&t;&t;&t;0x8c40
DECL|macro|PM2R_YUV_MODE
mdefine_line|#define PM2R_YUV_MODE&t;&t;&t;&t;&t;0x8f00
DECL|macro|PM2R_STATISTICS_MODE
mdefine_line|#define PM2R_STATISTICS_MODE&t;&t;&t;&t;0x8c08
DECL|macro|PM2R_FB_SOURCE_DELTA
mdefine_line|#define PM2R_FB_SOURCE_DELTA&t;&t;&t;&t;0x8d88
DECL|macro|PM2R_CONFIG
mdefine_line|#define PM2R_CONFIG&t;&t;&t;&t;&t;0x8d90
multiline_comment|/* Permedia2v */
DECL|macro|PM2VR_RD_INDEX_LOW
mdefine_line|#define PM2VR_RD_INDEX_LOW&t;&t;&t;&t;0x4020
DECL|macro|PM2VR_RD_INDEX_HIGH
mdefine_line|#define PM2VR_RD_INDEX_HIGH&t;&t;&t;&t;0x4028
DECL|macro|PM2VR_RD_INDEXED_DATA
mdefine_line|#define PM2VR_RD_INDEXED_DATA&t;&t;&t;&t;0x4030
multiline_comment|/* Permedia2 RAMDAC indexed registers */
DECL|macro|PM2I_RD_CURSOR_CONTROL
mdefine_line|#define PM2I_RD_CURSOR_CONTROL&t;&t;&t;&t;0x06
DECL|macro|PM2I_RD_COLOR_MODE
mdefine_line|#define PM2I_RD_COLOR_MODE&t;&t;&t;&t;0x18
DECL|macro|PM2I_RD_MODE_CONTROL
mdefine_line|#define PM2I_RD_MODE_CONTROL&t;&t;&t;&t;0x19
DECL|macro|PM2I_RD_MISC_CONTROL
mdefine_line|#define PM2I_RD_MISC_CONTROL&t;&t;&t;&t;0x1e
DECL|macro|PM2I_RD_PIXEL_CLOCK_A1
mdefine_line|#define PM2I_RD_PIXEL_CLOCK_A1&t;&t;&t;&t;0x20
DECL|macro|PM2I_RD_PIXEL_CLOCK_A2
mdefine_line|#define PM2I_RD_PIXEL_CLOCK_A2&t;&t;&t;&t;0x21
DECL|macro|PM2I_RD_PIXEL_CLOCK_A3
mdefine_line|#define PM2I_RD_PIXEL_CLOCK_A3&t;&t;&t;&t;0x22
DECL|macro|PM2I_RD_PIXEL_CLOCK_STATUS
mdefine_line|#define PM2I_RD_PIXEL_CLOCK_STATUS&t;&t;&t;0x29
DECL|macro|PM2I_RD_MEMORY_CLOCK_1
mdefine_line|#define PM2I_RD_MEMORY_CLOCK_1&t;&t;&t;&t;0x30
DECL|macro|PM2I_RD_MEMORY_CLOCK_2
mdefine_line|#define PM2I_RD_MEMORY_CLOCK_2&t;&t;&t;&t;0x31
DECL|macro|PM2I_RD_MEMORY_CLOCK_3
mdefine_line|#define PM2I_RD_MEMORY_CLOCK_3&t;&t;&t;&t;0x32
DECL|macro|PM2I_RD_MEMORY_CLOCK_STATUS
mdefine_line|#define PM2I_RD_MEMORY_CLOCK_STATUS&t;&t;&t;0x33
DECL|macro|PM2I_RD_COLOR_KEY_CONTROL
mdefine_line|#define PM2I_RD_COLOR_KEY_CONTROL&t;&t;&t;0x40
DECL|macro|PM2I_RD_OVERLAY_KEY
mdefine_line|#define PM2I_RD_OVERLAY_KEY&t;&t;&t;&t;0x41
DECL|macro|PM2I_RD_RED_KEY
mdefine_line|#define PM2I_RD_RED_KEY&t;&t;&t;&t;&t;0x42
DECL|macro|PM2I_RD_GREEN_KEY
mdefine_line|#define PM2I_RD_GREEN_KEY&t;&t;&t;&t;0x43
DECL|macro|PM2I_RD_BLUE_KEY
mdefine_line|#define PM2I_RD_BLUE_KEY&t;&t;&t;&t;0x44
multiline_comment|/* Permedia2v extensions */
DECL|macro|PM2VI_RD_MISC_CONTROL
mdefine_line|#define PM2VI_RD_MISC_CONTROL&t;&t;&t;&t;0x000
DECL|macro|PM2VI_RD_SYNC_CONTROL
mdefine_line|#define PM2VI_RD_SYNC_CONTROL&t;&t;&t;&t;0x001
DECL|macro|PM2VI_RD_DAC_CONTROL
mdefine_line|#define PM2VI_RD_DAC_CONTROL&t;&t;&t;&t;0x002
DECL|macro|PM2VI_RD_PIXEL_SIZE
mdefine_line|#define PM2VI_RD_PIXEL_SIZE&t;&t;&t;&t;0x003
DECL|macro|PM2VI_RD_COLOR_FORMAT
mdefine_line|#define PM2VI_RD_COLOR_FORMAT&t;&t;&t;&t;0x004
DECL|macro|PM2VI_RD_CURSOR_MODE
mdefine_line|#define PM2VI_RD_CURSOR_MODE&t;&t;&t;&t;0x005
DECL|macro|PM2VI_RD_CURSOR_X_LOW
mdefine_line|#define PM2VI_RD_CURSOR_X_LOW&t;&t;&t;&t;0x007
DECL|macro|PM2VI_RD_CURSOR_X_HIGH
mdefine_line|#define PM2VI_RD_CURSOR_X_HIGH&t;&t;&t;&t;0x008
DECL|macro|PM2VI_RD_CURSOR_Y_LOW
mdefine_line|#define PM2VI_RD_CURSOR_Y_LOW&t;&t;&t;&t;0x009
DECL|macro|PM2VI_RD_CURSOR_Y_HIGH
mdefine_line|#define PM2VI_RD_CURSOR_Y_HIGH&t;&t;&t;&t;0x00A
DECL|macro|PM2VI_RD_CURSOR_X_HOT
mdefine_line|#define PM2VI_RD_CURSOR_X_HOT&t;&t;&t;&t;0x00B
DECL|macro|PM2VI_RD_CURSOR_Y_HOT
mdefine_line|#define PM2VI_RD_CURSOR_Y_HOT&t;&t;&t;&t;0x00C
DECL|macro|PM2VI_RD_CLK0_PRESCALE
mdefine_line|#define PM2VI_RD_CLK0_PRESCALE&t;&t;&t;&t;0x201
DECL|macro|PM2VI_RD_CLK0_FEEDBACK
mdefine_line|#define PM2VI_RD_CLK0_FEEDBACK&t;&t;&t;&t;0x202
DECL|macro|PM2VI_RD_CLK0_POSTSCALE
mdefine_line|#define PM2VI_RD_CLK0_POSTSCALE&t;&t;&t;&t;0x203
DECL|macro|PM2VI_RD_CLK1_PRESCALE
mdefine_line|#define PM2VI_RD_CLK1_PRESCALE&t;&t;&t;&t;0x204
DECL|macro|PM2VI_RD_CLK1_FEEDBACK
mdefine_line|#define PM2VI_RD_CLK1_FEEDBACK&t;&t;&t;&t;0x205
DECL|macro|PM2VI_RD_CLK1_POSTSCALE
mdefine_line|#define PM2VI_RD_CLK1_POSTSCALE&t;&t;&t;&t;0x206
DECL|macro|PM2VI_RD_CURSOR_PALETTE
mdefine_line|#define PM2VI_RD_CURSOR_PALETTE&t;&t;&t;&t;0x303
DECL|macro|PM2VI_RD_CURSOR_PATTERN
mdefine_line|#define PM2VI_RD_CURSOR_PATTERN&t;&t;&t;&t;0x400
multiline_comment|/* Fields and flags */
DECL|macro|PM2F_RENDER_AREASTIPPLE
mdefine_line|#define PM2F_RENDER_AREASTIPPLE&t;&t;&t;&t;(1L&lt;&lt;0)
DECL|macro|PM2F_RENDER_FASTFILL
mdefine_line|#define PM2F_RENDER_FASTFILL&t;&t;&t;&t;(1L&lt;&lt;3)
DECL|macro|PM2F_RENDER_PRIMITIVE_MASK
mdefine_line|#define PM2F_RENDER_PRIMITIVE_MASK&t;&t;&t;(3L&lt;&lt;6)
DECL|macro|PM2F_RENDER_LINE
mdefine_line|#define PM2F_RENDER_LINE&t;&t;&t;&t;0
DECL|macro|PM2F_RENDER_TRAPEZOID
mdefine_line|#define PM2F_RENDER_TRAPEZOID&t;&t;&t;&t;(1L&lt;&lt;6)
DECL|macro|PM2F_RENDER_POINT
mdefine_line|#define PM2F_RENDER_POINT&t;&t;&t;&t;(2L&lt;&lt;6)
DECL|macro|PM2F_RENDER_RECTANGLE
mdefine_line|#define PM2F_RENDER_RECTANGLE&t;&t;&t;&t;(3L&lt;&lt;6)
DECL|macro|PM2F_SYNCHRONIZATION
mdefine_line|#define PM2F_SYNCHRONIZATION&t;&t;&t;&t;(1L&lt;&lt;10)
DECL|macro|PM2F_PLL_LOCKED
mdefine_line|#define PM2F_PLL_LOCKED&t;&t;&t;&t;&t;0x10
DECL|macro|PM2F_BEING_RESET
mdefine_line|#define PM2F_BEING_RESET&t;&t;&t;&t;(1L&lt;&lt;31)
DECL|macro|PM2F_DATATYPE_COLOR
mdefine_line|#define PM2F_DATATYPE_COLOR&t;&t;&t;&t;0x8000
DECL|macro|PM2F_VGA_ENABLE
mdefine_line|#define PM2F_VGA_ENABLE&t;&t;&t;&t;&t;0x02
DECL|macro|PM2F_VGA_FIXED
mdefine_line|#define PM2F_VGA_FIXED&t;&t;&t;&t;&t;0x04
DECL|macro|PM2F_FB_WRITE_ENABLE
mdefine_line|#define PM2F_FB_WRITE_ENABLE&t;&t;&t;&t;0x01
DECL|macro|PM2F_FB_READ_SOURCE_ENABLE
mdefine_line|#define PM2F_FB_READ_SOURCE_ENABLE&t;&t;&t;0x0200
DECL|macro|PM2F_RD_PALETTE_WIDTH_8
mdefine_line|#define PM2F_RD_PALETTE_WIDTH_8&t;&t;&t;&t;0x02
DECL|macro|PM2F_PART_PROD_MASK
mdefine_line|#define PM2F_PART_PROD_MASK&t;&t;&t;&t;0x01ff
DECL|macro|PM2F_SCREEN_SCISSOR_ENABLE
mdefine_line|#define PM2F_SCREEN_SCISSOR_ENABLE&t;&t;&t;0x02
DECL|macro|PM2F_DATA_64_ENABLE
mdefine_line|#define PM2F_DATA_64_ENABLE&t;&t;&t;&t;0x00010000
DECL|macro|PM2F_BLANK_LOW
mdefine_line|#define PM2F_BLANK_LOW&t;&t;&t;&t;&t;0x02
DECL|macro|PM2F_HSYNC_MASK
mdefine_line|#define PM2F_HSYNC_MASK&t;&t;&t;&t;&t;0x18
DECL|macro|PM2F_VSYNC_MASK
mdefine_line|#define PM2F_VSYNC_MASK&t;&t;&t;&t;&t;0x60
DECL|macro|PM2F_HSYNC_ACT_HIGH
mdefine_line|#define PM2F_HSYNC_ACT_HIGH&t;&t;&t;&t;0x08
DECL|macro|PM2F_HSYNC_FORCED_LOW
mdefine_line|#define PM2F_HSYNC_FORCED_LOW&t;&t;&t;&t;0x10
DECL|macro|PM2F_HSYNC_ACT_LOW
mdefine_line|#define PM2F_HSYNC_ACT_LOW&t;&t;&t;&t;0x18
DECL|macro|PM2F_VSYNC_ACT_HIGH
mdefine_line|#define PM2F_VSYNC_ACT_HIGH&t;&t;&t;&t;0x20
DECL|macro|PM2F_VSYNC_FORCED_LOW
mdefine_line|#define PM2F_VSYNC_FORCED_LOW&t;&t;&t;&t;0x40
DECL|macro|PM2F_VSYNC_ACT_LOW
mdefine_line|#define PM2F_VSYNC_ACT_LOW&t;&t;&t;&t;0x60
DECL|macro|PM2F_LINE_DOUBLE
mdefine_line|#define PM2F_LINE_DOUBLE&t;&t;&t;&t;0x04
DECL|macro|PM2F_VIDEO_ENABLE
mdefine_line|#define PM2F_VIDEO_ENABLE&t;&t;&t;&t;0x01
DECL|macro|PM2F_RD_GUI_ACTIVE
mdefine_line|#define PM2F_RD_GUI_ACTIVE&t;&t;&t;&t;0x10
DECL|macro|PM2F_RD_COLOR_MODE_RGB
mdefine_line|#define PM2F_RD_COLOR_MODE_RGB&t;&t;&t;&t;0x20
DECL|macro|PM2F_RD_TRUECOLOR
mdefine_line|#define PM2F_RD_TRUECOLOR&t;&t;&t;&t;0x80
DECL|macro|PM2F_NO_ALPHA_BUFFER
mdefine_line|#define PM2F_NO_ALPHA_BUFFER&t;&t;&t;&t;0x10
DECL|macro|PM2F_TEXTEL_SIZE_16
mdefine_line|#define PM2F_TEXTEL_SIZE_16&t;&t;&t;&t;0x00080000
DECL|macro|PM2F_TEXTEL_SIZE_32
mdefine_line|#define PM2F_TEXTEL_SIZE_32&t;&t;&t;&t;0x00100000
DECL|macro|PM2F_TEXTEL_SIZE_4
mdefine_line|#define PM2F_TEXTEL_SIZE_4&t;&t;&t;&t;0x00180000
DECL|macro|PM2F_TEXTEL_SIZE_24
mdefine_line|#define PM2F_TEXTEL_SIZE_24&t;&t;&t;&t;0x00200000
DECL|macro|PM2F_INCREASE_X
mdefine_line|#define PM2F_INCREASE_X&t;&t;&t;&t;&t;(1L&lt;&lt;21)
DECL|macro|PM2F_INCREASE_Y
mdefine_line|#define PM2F_INCREASE_Y&t;&t;&t;&t;&t;(1L&lt;&lt;22)
DECL|macro|PM2F_CONFIG_FB_WRITE_ENABLE
mdefine_line|#define PM2F_CONFIG_FB_WRITE_ENABLE&t;&t;&t;(1L&lt;&lt;3)
DECL|macro|PM2F_CONFIG_FB_PACKED_DATA
mdefine_line|#define PM2F_CONFIG_FB_PACKED_DATA&t;&t;&t;(1L&lt;&lt;2)
DECL|macro|PM2F_CONFIG_FB_READ_DEST_ENABLE
mdefine_line|#define PM2F_CONFIG_FB_READ_DEST_ENABLE&t;&t;&t;(1L&lt;&lt;1)
DECL|macro|PM2F_CONFIG_FB_READ_SOURCE_ENABLE
mdefine_line|#define PM2F_CONFIG_FB_READ_SOURCE_ENABLE&t;&t;(1L&lt;&lt;0)
DECL|macro|PM2F_COLOR_KEY_TEST_OFF
mdefine_line|#define PM2F_COLOR_KEY_TEST_OFF&t;&t;&t;&t;(1L&lt;&lt;4)
DECL|macro|PM2F_MEM_CONFIG_RAM_MASK
mdefine_line|#define PM2F_MEM_CONFIG_RAM_MASK&t;&t;&t;(3L&lt;&lt;29)
DECL|macro|PM2F_MEM_BANKS_1
mdefine_line|#define PM2F_MEM_BANKS_1&t;&t;&t;&t;0L
DECL|macro|PM2F_MEM_BANKS_2
mdefine_line|#define PM2F_MEM_BANKS_2&t;&t;&t;&t;(1L&lt;&lt;29)
DECL|macro|PM2F_MEM_BANKS_3
mdefine_line|#define PM2F_MEM_BANKS_3&t;&t;&t;&t;(2L&lt;&lt;29)
DECL|macro|PM2F_MEM_BANKS_4
mdefine_line|#define PM2F_MEM_BANKS_4&t;&t;&t;&t;(3L&lt;&lt;29)
r_typedef
r_enum
(brace
DECL|enumerator|PM2_TYPE_PERMEDIA2
id|PM2_TYPE_PERMEDIA2
comma
DECL|enumerator|PM2_TYPE_PERMEDIA2V
id|PM2_TYPE_PERMEDIA2V
DECL|typedef|pm2type_t
)brace
id|pm2type_t
suffix:semicolon
macro_line|#endif /* PM2FB_H */
multiline_comment|/*****************************************************************************&n; * That&squot;s all folks!&n; *****************************************************************************/
eof
