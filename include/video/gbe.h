multiline_comment|/*&n; * include/video/gbe.h -- SGI GBE (Graphics Back End)&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc. (Jeffrey Newquist)&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License version 2 as published by the Free Software Foundation.&n; */
macro_line|#ifndef __GBE_H__
DECL|macro|__GBE_H__
mdefine_line|#define __GBE_H__
DECL|struct|sgi_gbe
r_struct
id|sgi_gbe
(brace
DECL|member|ctrlstat
r_volatile
r_uint32
id|ctrlstat
suffix:semicolon
multiline_comment|/* general control */
DECL|member|dotclock
r_volatile
r_uint32
id|dotclock
suffix:semicolon
multiline_comment|/* dot clock PLL control */
DECL|member|i2c
r_volatile
r_uint32
id|i2c
suffix:semicolon
multiline_comment|/* crt I2C control */
DECL|member|sysclk
r_volatile
r_uint32
id|sysclk
suffix:semicolon
multiline_comment|/* system clock PLL control */
DECL|member|i2cfp
r_volatile
r_uint32
id|i2cfp
suffix:semicolon
multiline_comment|/* flat panel I2C control */
DECL|member|id
r_volatile
r_uint32
id|id
suffix:semicolon
multiline_comment|/* device id/chip revision */
DECL|member|config
r_volatile
r_uint32
id|config
suffix:semicolon
multiline_comment|/* power on configuration [1] */
DECL|member|bist
r_volatile
r_uint32
id|bist
suffix:semicolon
multiline_comment|/* internal bist status [1] */
DECL|member|_pad0
r_uint32
id|_pad0
(braket
l_int|0x010000
op_div
l_int|4
op_minus
l_int|8
)braket
suffix:semicolon
DECL|member|vt_xy
r_volatile
r_uint32
id|vt_xy
suffix:semicolon
multiline_comment|/* current dot coords */
DECL|member|vt_xymax
r_volatile
r_uint32
id|vt_xymax
suffix:semicolon
multiline_comment|/* maximum dot coords */
DECL|member|vt_vsync
r_volatile
r_uint32
id|vt_vsync
suffix:semicolon
multiline_comment|/* vsync on/off */
DECL|member|vt_hsync
r_volatile
r_uint32
id|vt_hsync
suffix:semicolon
multiline_comment|/* hsync on/off */
DECL|member|vt_vblank
r_volatile
r_uint32
id|vt_vblank
suffix:semicolon
multiline_comment|/* vblank on/off */
DECL|member|vt_hblank
r_volatile
r_uint32
id|vt_hblank
suffix:semicolon
multiline_comment|/* hblank on/off */
DECL|member|vt_flags
r_volatile
r_uint32
id|vt_flags
suffix:semicolon
multiline_comment|/* polarity of vt signals */
DECL|member|vt_f2rf_lock
r_volatile
r_uint32
id|vt_f2rf_lock
suffix:semicolon
multiline_comment|/* f2rf &amp; framelck y coord */
DECL|member|vt_intr01
r_volatile
r_uint32
id|vt_intr01
suffix:semicolon
multiline_comment|/* intr 0,1 y coords */
DECL|member|vt_intr23
r_volatile
r_uint32
id|vt_intr23
suffix:semicolon
multiline_comment|/* intr 2,3 y coords */
DECL|member|fp_hdrv
r_volatile
r_uint32
id|fp_hdrv
suffix:semicolon
multiline_comment|/* flat panel hdrv on/off */
DECL|member|fp_vdrv
r_volatile
r_uint32
id|fp_vdrv
suffix:semicolon
multiline_comment|/* flat panel vdrv on/off */
DECL|member|fp_de
r_volatile
r_uint32
id|fp_de
suffix:semicolon
multiline_comment|/* flat panel de on/off */
DECL|member|vt_hpixen
r_volatile
r_uint32
id|vt_hpixen
suffix:semicolon
multiline_comment|/* intrnl horiz pixel on/off */
DECL|member|vt_vpixen
r_volatile
r_uint32
id|vt_vpixen
suffix:semicolon
multiline_comment|/* intrnl vert pixel on/off */
DECL|member|vt_hcmap
r_volatile
r_uint32
id|vt_hcmap
suffix:semicolon
multiline_comment|/* cmap write (horiz) */
DECL|member|vt_vcmap
r_volatile
r_uint32
id|vt_vcmap
suffix:semicolon
multiline_comment|/* cmap write (vert) */
DECL|member|did_start_xy
r_volatile
r_uint32
id|did_start_xy
suffix:semicolon
multiline_comment|/* eol/f did/xy reset val */
DECL|member|crs_start_xy
r_volatile
r_uint32
id|crs_start_xy
suffix:semicolon
multiline_comment|/* eol/f crs/xy reset val */
DECL|member|vc_start_xy
r_volatile
r_uint32
id|vc_start_xy
suffix:semicolon
multiline_comment|/* eol/f vc/xy reset val */
DECL|member|_pad1
r_uint32
id|_pad1
(braket
l_int|0xffb0
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|ovr_width_tile
r_volatile
r_uint32
id|ovr_width_tile
suffix:semicolon
multiline_comment|/*overlay plane ctrl 0 */
DECL|member|ovr_inhwctrl
r_volatile
r_uint32
id|ovr_inhwctrl
suffix:semicolon
multiline_comment|/* overlay plane ctrl 1 */
DECL|member|ovr_control
r_volatile
r_uint32
id|ovr_control
suffix:semicolon
multiline_comment|/* overlay plane ctrl 1 */
DECL|member|_pad2
r_uint32
id|_pad2
(braket
l_int|0xfff4
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|frm_size_tile
r_volatile
r_uint32
id|frm_size_tile
suffix:semicolon
multiline_comment|/* normal plane ctrl 0 */
DECL|member|frm_size_pixel
r_volatile
r_uint32
id|frm_size_pixel
suffix:semicolon
multiline_comment|/*normal plane ctrl 1 */
DECL|member|frm_inhwctrl
r_volatile
r_uint32
id|frm_inhwctrl
suffix:semicolon
multiline_comment|/* normal plane ctrl 2 */
DECL|member|frm_control
r_volatile
r_uint32
id|frm_control
suffix:semicolon
multiline_comment|/* normal plane ctrl 3 */
DECL|member|_pad3
r_uint32
id|_pad3
(braket
l_int|0xfff0
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|did_inhwctrl
r_volatile
r_uint32
id|did_inhwctrl
suffix:semicolon
multiline_comment|/* DID control */
DECL|member|did_control
r_volatile
r_uint32
id|did_control
suffix:semicolon
multiline_comment|/* DID shadow */
DECL|member|_pad4
r_uint32
id|_pad4
(braket
l_int|0x7ff8
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|mode_regs
r_volatile
r_uint32
id|mode_regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* WID table */
DECL|member|_pad5
r_uint32
id|_pad5
(braket
l_int|0x7f80
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|cmap
r_volatile
r_uint32
id|cmap
(braket
l_int|6144
)braket
suffix:semicolon
multiline_comment|/* color map */
DECL|member|_pad6
r_uint32
id|_pad6
(braket
l_int|0x2000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|cm_fifo
r_volatile
r_uint32
id|cm_fifo
suffix:semicolon
multiline_comment|/* color map fifo status */
DECL|member|_pad7
r_uint32
id|_pad7
(braket
l_int|0x7ffc
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|gmap
r_volatile
r_uint32
id|gmap
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* gamma map */
DECL|member|_pad8
r_uint32
id|_pad8
(braket
l_int|0x7c00
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|gmap10
r_volatile
r_uint32
id|gmap10
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* gamma map */
DECL|member|_pad9
r_uint32
id|_pad9
(braket
l_int|0x7000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|crs_pos
r_volatile
r_uint32
id|crs_pos
suffix:semicolon
multiline_comment|/* cusror control 0 */
DECL|member|crs_ctl
r_volatile
r_uint32
id|crs_ctl
suffix:semicolon
multiline_comment|/* cusror control 1 */
DECL|member|crs_cmap
r_volatile
r_uint32
id|crs_cmap
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* crs cmap */
DECL|member|_pad10
r_uint32
id|_pad10
(braket
l_int|0x7fec
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|crs_glyph
r_volatile
r_uint32
id|crs_glyph
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* crs glyph */
DECL|member|_pad11
r_uint32
id|_pad11
(braket
l_int|0x7f00
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|vc_0
r_volatile
r_uint32
id|vc_0
suffix:semicolon
multiline_comment|/* video capture crtl 0 */
DECL|member|vc_1
r_volatile
r_uint32
id|vc_1
suffix:semicolon
multiline_comment|/* video capture crtl 1 */
DECL|member|vc_2
r_volatile
r_uint32
id|vc_2
suffix:semicolon
multiline_comment|/* video capture crtl 2 */
DECL|member|vc_3
r_volatile
r_uint32
id|vc_3
suffix:semicolon
multiline_comment|/* video capture crtl 3 */
DECL|member|vc_4
r_volatile
r_uint32
id|vc_4
suffix:semicolon
multiline_comment|/* video capture crtl 4 */
DECL|member|vc_5
r_volatile
r_uint32
id|vc_5
suffix:semicolon
multiline_comment|/* video capture crtl 5 */
DECL|member|vc_6
r_volatile
r_uint32
id|vc_6
suffix:semicolon
multiline_comment|/* video capture crtl 6 */
DECL|member|vc_7
r_volatile
r_uint32
id|vc_7
suffix:semicolon
multiline_comment|/* video capture crtl 7 */
DECL|member|vc_8
r_volatile
r_uint32
id|vc_8
suffix:semicolon
multiline_comment|/* video capture crtl 8 */
)brace
suffix:semicolon
DECL|macro|MASK
mdefine_line|#define MASK(msb, lsb)&t;&t;&bslash;&n;&t;( (((u32)1&lt;&lt;((msb)-(lsb)+1))-1) &lt;&lt; (lsb) )
DECL|macro|GET
mdefine_line|#define GET(v, msb, lsb)&t;&bslash;&n;&t;( ((u32)(v) &amp; MASK(msb,lsb)) &gt;&gt; (lsb) )
DECL|macro|SET
mdefine_line|#define SET(v, f, msb, lsb)&t;&bslash;&n;&t;( (v) = ((v)&amp;~MASK(msb,lsb)) | (( (u32)(f)&lt;&lt;(lsb) ) &amp; MASK(msb,lsb)) )
DECL|macro|GET_GBE_FIELD
mdefine_line|#define GET_GBE_FIELD(reg, field, v)&t;&t;&bslash;&n;&t;GET((v), GBE_##reg##_##field##_MSB, GBE_##reg##_##field##_LSB)
DECL|macro|SET_GBE_FIELD
mdefine_line|#define SET_GBE_FIELD(reg, field, v, f)&t;&t;&bslash;&n;&t;SET((v), (f), GBE_##reg##_##field##_MSB, GBE_##reg##_##field##_LSB)
multiline_comment|/*&n; * Bit mask information&n; */
DECL|macro|GBE_CTRLSTAT_CHIPID_MSB
mdefine_line|#define GBE_CTRLSTAT_CHIPID_MSB&t;&t; 3
DECL|macro|GBE_CTRLSTAT_CHIPID_LSB
mdefine_line|#define GBE_CTRLSTAT_CHIPID_LSB&t;&t; 0
DECL|macro|GBE_CTRLSTAT_SENSE_N_MSB
mdefine_line|#define GBE_CTRLSTAT_SENSE_N_MSB&t; 4
DECL|macro|GBE_CTRLSTAT_SENSE_N_LSB
mdefine_line|#define GBE_CTRLSTAT_SENSE_N_LSB&t; 4
DECL|macro|GBE_CTRLSTAT_PCLKSEL_MSB
mdefine_line|#define GBE_CTRLSTAT_PCLKSEL_MSB&t;29
DECL|macro|GBE_CTRLSTAT_PCLKSEL_LSB
mdefine_line|#define GBE_CTRLSTAT_PCLKSEL_LSB&t;28
DECL|macro|GBE_DOTCLK_M_MSB
mdefine_line|#define GBE_DOTCLK_M_MSB&t;&t; 7
DECL|macro|GBE_DOTCLK_M_LSB
mdefine_line|#define GBE_DOTCLK_M_LSB&t;&t; 0
DECL|macro|GBE_DOTCLK_N_MSB
mdefine_line|#define GBE_DOTCLK_N_MSB&t;&t;13
DECL|macro|GBE_DOTCLK_N_LSB
mdefine_line|#define GBE_DOTCLK_N_LSB&t;&t; 8
DECL|macro|GBE_DOTCLK_P_MSB
mdefine_line|#define GBE_DOTCLK_P_MSB&t;&t;15
DECL|macro|GBE_DOTCLK_P_LSB
mdefine_line|#define GBE_DOTCLK_P_LSB&t;&t;14
DECL|macro|GBE_DOTCLK_RUN_MSB
mdefine_line|#define GBE_DOTCLK_RUN_MSB&t;&t;20
DECL|macro|GBE_DOTCLK_RUN_LSB
mdefine_line|#define GBE_DOTCLK_RUN_LSB&t;&t;20
DECL|macro|GBE_VT_XY_Y_MSB
mdefine_line|#define GBE_VT_XY_Y_MSB&t;&t;23
DECL|macro|GBE_VT_XY_Y_LSB
mdefine_line|#define GBE_VT_XY_Y_LSB&t;&t;12
DECL|macro|GBE_VT_XY_X_MSB
mdefine_line|#define GBE_VT_XY_X_MSB&t;&t;11
DECL|macro|GBE_VT_XY_X_LSB
mdefine_line|#define GBE_VT_XY_X_LSB&t;&t; 0
DECL|macro|GBE_VT_XY_FREEZE_MSB
mdefine_line|#define GBE_VT_XY_FREEZE_MSB&t;&t;31
DECL|macro|GBE_VT_XY_FREEZE_LSB
mdefine_line|#define GBE_VT_XY_FREEZE_LSB&t;&t;31
DECL|macro|GBE_FP_VDRV_ON_MSB
mdefine_line|#define GBE_FP_VDRV_ON_MSB&t;23
DECL|macro|GBE_FP_VDRV_ON_LSB
mdefine_line|#define GBE_FP_VDRV_ON_LSB&t;12
DECL|macro|GBE_FP_VDRV_OFF_MSB
mdefine_line|#define GBE_FP_VDRV_OFF_MSB&t;11
DECL|macro|GBE_FP_VDRV_OFF_LSB
mdefine_line|#define GBE_FP_VDRV_OFF_LSB&t;0
DECL|macro|GBE_FP_HDRV_ON_MSB
mdefine_line|#define GBE_FP_HDRV_ON_MSB&t;23
DECL|macro|GBE_FP_HDRV_ON_LSB
mdefine_line|#define GBE_FP_HDRV_ON_LSB&t;12
DECL|macro|GBE_FP_HDRV_OFF_MSB
mdefine_line|#define GBE_FP_HDRV_OFF_MSB&t;11
DECL|macro|GBE_FP_HDRV_OFF_LSB
mdefine_line|#define GBE_FP_HDRV_OFF_LSB&t;0
DECL|macro|GBE_FP_DE_ON_MSB
mdefine_line|#define GBE_FP_DE_ON_MSB&t;&t;23
DECL|macro|GBE_FP_DE_ON_LSB
mdefine_line|#define GBE_FP_DE_ON_LSB&t;&t;12
DECL|macro|GBE_FP_DE_OFF_MSB
mdefine_line|#define GBE_FP_DE_OFF_MSB&t;&t;11
DECL|macro|GBE_FP_DE_OFF_LSB
mdefine_line|#define GBE_FP_DE_OFF_LSB&t;&t;0
DECL|macro|GBE_VT_VSYNC_VSYNC_ON_MSB
mdefine_line|#define GBE_VT_VSYNC_VSYNC_ON_MSB&t;23
DECL|macro|GBE_VT_VSYNC_VSYNC_ON_LSB
mdefine_line|#define GBE_VT_VSYNC_VSYNC_ON_LSB&t;12
DECL|macro|GBE_VT_VSYNC_VSYNC_OFF_MSB
mdefine_line|#define GBE_VT_VSYNC_VSYNC_OFF_MSB&t;11
DECL|macro|GBE_VT_VSYNC_VSYNC_OFF_LSB
mdefine_line|#define GBE_VT_VSYNC_VSYNC_OFF_LSB&t; 0
DECL|macro|GBE_VT_HSYNC_HSYNC_ON_MSB
mdefine_line|#define GBE_VT_HSYNC_HSYNC_ON_MSB&t;23
DECL|macro|GBE_VT_HSYNC_HSYNC_ON_LSB
mdefine_line|#define GBE_VT_HSYNC_HSYNC_ON_LSB&t;12
DECL|macro|GBE_VT_HSYNC_HSYNC_OFF_MSB
mdefine_line|#define GBE_VT_HSYNC_HSYNC_OFF_MSB&t;11
DECL|macro|GBE_VT_HSYNC_HSYNC_OFF_LSB
mdefine_line|#define GBE_VT_HSYNC_HSYNC_OFF_LSB&t; 0
DECL|macro|GBE_VT_VBLANK_VBLANK_ON_MSB
mdefine_line|#define GBE_VT_VBLANK_VBLANK_ON_MSB&t;23
DECL|macro|GBE_VT_VBLANK_VBLANK_ON_LSB
mdefine_line|#define GBE_VT_VBLANK_VBLANK_ON_LSB&t;12
DECL|macro|GBE_VT_VBLANK_VBLANK_OFF_MSB
mdefine_line|#define GBE_VT_VBLANK_VBLANK_OFF_MSB&t;11
DECL|macro|GBE_VT_VBLANK_VBLANK_OFF_LSB
mdefine_line|#define GBE_VT_VBLANK_VBLANK_OFF_LSB&t; 0
DECL|macro|GBE_VT_HBLANK_HBLANK_ON_MSB
mdefine_line|#define GBE_VT_HBLANK_HBLANK_ON_MSB&t;23
DECL|macro|GBE_VT_HBLANK_HBLANK_ON_LSB
mdefine_line|#define GBE_VT_HBLANK_HBLANK_ON_LSB&t;12
DECL|macro|GBE_VT_HBLANK_HBLANK_OFF_MSB
mdefine_line|#define GBE_VT_HBLANK_HBLANK_OFF_MSB&t;11
DECL|macro|GBE_VT_HBLANK_HBLANK_OFF_LSB
mdefine_line|#define GBE_VT_HBLANK_HBLANK_OFF_LSB&t; 0
DECL|macro|GBE_VT_FLAGS_F2RF_HIGH_MSB
mdefine_line|#define GBE_VT_FLAGS_F2RF_HIGH_MSB&t; 6
DECL|macro|GBE_VT_FLAGS_F2RF_HIGH_LSB
mdefine_line|#define GBE_VT_FLAGS_F2RF_HIGH_LSB&t; 6
DECL|macro|GBE_VT_FLAGS_SYNC_LOW_MSB
mdefine_line|#define GBE_VT_FLAGS_SYNC_LOW_MSB&t; 5
DECL|macro|GBE_VT_FLAGS_SYNC_LOW_LSB
mdefine_line|#define GBE_VT_FLAGS_SYNC_LOW_LSB&t; 5
DECL|macro|GBE_VT_FLAGS_SYNC_HIGH_MSB
mdefine_line|#define GBE_VT_FLAGS_SYNC_HIGH_MSB&t; 4
DECL|macro|GBE_VT_FLAGS_SYNC_HIGH_LSB
mdefine_line|#define GBE_VT_FLAGS_SYNC_HIGH_LSB&t; 4
DECL|macro|GBE_VT_FLAGS_HDRV_LOW_MSB
mdefine_line|#define GBE_VT_FLAGS_HDRV_LOW_MSB&t; 3
DECL|macro|GBE_VT_FLAGS_HDRV_LOW_LSB
mdefine_line|#define GBE_VT_FLAGS_HDRV_LOW_LSB&t; 3
DECL|macro|GBE_VT_FLAGS_HDRV_INVERT_MSB
mdefine_line|#define GBE_VT_FLAGS_HDRV_INVERT_MSB&t; 2
DECL|macro|GBE_VT_FLAGS_HDRV_INVERT_LSB
mdefine_line|#define GBE_VT_FLAGS_HDRV_INVERT_LSB&t; 2
DECL|macro|GBE_VT_FLAGS_VDRV_LOW_MSB
mdefine_line|#define GBE_VT_FLAGS_VDRV_LOW_MSB&t; 1
DECL|macro|GBE_VT_FLAGS_VDRV_LOW_LSB
mdefine_line|#define GBE_VT_FLAGS_VDRV_LOW_LSB&t; 1
DECL|macro|GBE_VT_FLAGS_VDRV_INVERT_MSB
mdefine_line|#define GBE_VT_FLAGS_VDRV_INVERT_MSB&t; 0
DECL|macro|GBE_VT_FLAGS_VDRV_INVERT_LSB
mdefine_line|#define GBE_VT_FLAGS_VDRV_INVERT_LSB&t; 0
DECL|macro|GBE_VT_VCMAP_VCMAP_ON_MSB
mdefine_line|#define GBE_VT_VCMAP_VCMAP_ON_MSB&t;23
DECL|macro|GBE_VT_VCMAP_VCMAP_ON_LSB
mdefine_line|#define GBE_VT_VCMAP_VCMAP_ON_LSB&t;12
DECL|macro|GBE_VT_VCMAP_VCMAP_OFF_MSB
mdefine_line|#define GBE_VT_VCMAP_VCMAP_OFF_MSB&t;11
DECL|macro|GBE_VT_VCMAP_VCMAP_OFF_LSB
mdefine_line|#define GBE_VT_VCMAP_VCMAP_OFF_LSB&t; 0
DECL|macro|GBE_VT_HCMAP_HCMAP_ON_MSB
mdefine_line|#define GBE_VT_HCMAP_HCMAP_ON_MSB&t;23
DECL|macro|GBE_VT_HCMAP_HCMAP_ON_LSB
mdefine_line|#define GBE_VT_HCMAP_HCMAP_ON_LSB&t;12
DECL|macro|GBE_VT_HCMAP_HCMAP_OFF_MSB
mdefine_line|#define GBE_VT_HCMAP_HCMAP_OFF_MSB&t;11
DECL|macro|GBE_VT_HCMAP_HCMAP_OFF_LSB
mdefine_line|#define GBE_VT_HCMAP_HCMAP_OFF_LSB&t; 0
DECL|macro|GBE_VT_XYMAX_MAXX_MSB
mdefine_line|#define GBE_VT_XYMAX_MAXX_MSB&t;11
DECL|macro|GBE_VT_XYMAX_MAXX_LSB
mdefine_line|#define GBE_VT_XYMAX_MAXX_LSB&t; 0
DECL|macro|GBE_VT_XYMAX_MAXY_MSB
mdefine_line|#define GBE_VT_XYMAX_MAXY_MSB&t;23
DECL|macro|GBE_VT_XYMAX_MAXY_LSB
mdefine_line|#define GBE_VT_XYMAX_MAXY_LSB&t;12
DECL|macro|GBE_VT_HPIXEN_HPIXEN_ON_MSB
mdefine_line|#define GBE_VT_HPIXEN_HPIXEN_ON_MSB&t;23
DECL|macro|GBE_VT_HPIXEN_HPIXEN_ON_LSB
mdefine_line|#define GBE_VT_HPIXEN_HPIXEN_ON_LSB&t;12
DECL|macro|GBE_VT_HPIXEN_HPIXEN_OFF_MSB
mdefine_line|#define GBE_VT_HPIXEN_HPIXEN_OFF_MSB&t;11
DECL|macro|GBE_VT_HPIXEN_HPIXEN_OFF_LSB
mdefine_line|#define GBE_VT_HPIXEN_HPIXEN_OFF_LSB&t; 0
DECL|macro|GBE_VT_VPIXEN_VPIXEN_ON_MSB
mdefine_line|#define GBE_VT_VPIXEN_VPIXEN_ON_MSB&t;23
DECL|macro|GBE_VT_VPIXEN_VPIXEN_ON_LSB
mdefine_line|#define GBE_VT_VPIXEN_VPIXEN_ON_LSB&t;12
DECL|macro|GBE_VT_VPIXEN_VPIXEN_OFF_MSB
mdefine_line|#define GBE_VT_VPIXEN_VPIXEN_OFF_MSB&t;11
DECL|macro|GBE_VT_VPIXEN_VPIXEN_OFF_LSB
mdefine_line|#define GBE_VT_VPIXEN_VPIXEN_OFF_LSB&t; 0
DECL|macro|GBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB
mdefine_line|#define GBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB
mdefine_line|#define GBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB
mdefine_line|#define GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB
mdefine_line|#define GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB
mdefine_line|#define GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB&t;13
DECL|macro|GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB
mdefine_line|#define GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB&t;13
DECL|macro|GBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_FRM_CONTROL_FRM_TILE_PTR_MSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_TILE_PTR_MSB&t;31
DECL|macro|GBE_FRM_CONTROL_FRM_TILE_PTR_LSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_TILE_PTR_LSB&t; 9
DECL|macro|GBE_FRM_CONTROL_FRM_LINEAR_MSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_LINEAR_MSB&t;&t; 1
DECL|macro|GBE_FRM_CONTROL_FRM_LINEAR_LSB
mdefine_line|#define GBE_FRM_CONTROL_FRM_LINEAR_LSB&t;&t; 1
DECL|macro|GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB
mdefine_line|#define GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB
mdefine_line|#define GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB&t;12
DECL|macro|GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB&t; 5
DECL|macro|GBE_FRM_SIZE_TILE_FRM_RHS_MSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_RHS_MSB&t;&t; 4
DECL|macro|GBE_FRM_SIZE_TILE_FRM_RHS_LSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_RHS_LSB&t;&t; 0
DECL|macro|GBE_FRM_SIZE_TILE_FRM_DEPTH_MSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_DEPTH_MSB&t;&t;14
DECL|macro|GBE_FRM_SIZE_TILE_FRM_DEPTH_LSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_DEPTH_LSB&t;&t;13
DECL|macro|GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB&t;15
DECL|macro|GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB
mdefine_line|#define GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB&t;15
DECL|macro|GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB
mdefine_line|#define GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB&t;31
DECL|macro|GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB
mdefine_line|#define GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB&t;16
DECL|macro|GBE_DID_CONTROL_DID_DMA_ENABLE_MSB
mdefine_line|#define GBE_DID_CONTROL_DID_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_DID_CONTROL_DID_DMA_ENABLE_LSB
mdefine_line|#define GBE_DID_CONTROL_DID_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB
mdefine_line|#define GBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB&t; 0
DECL|macro|GBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB
mdefine_line|#define GBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB&t; 0
DECL|macro|GBE_DID_START_XY_DID_STARTY_MSB
mdefine_line|#define GBE_DID_START_XY_DID_STARTY_MSB&t;&t;23
DECL|macro|GBE_DID_START_XY_DID_STARTY_LSB
mdefine_line|#define GBE_DID_START_XY_DID_STARTY_LSB&t;&t;12
DECL|macro|GBE_DID_START_XY_DID_STARTX_MSB
mdefine_line|#define GBE_DID_START_XY_DID_STARTX_MSB&t;&t;11
DECL|macro|GBE_DID_START_XY_DID_STARTX_LSB
mdefine_line|#define GBE_DID_START_XY_DID_STARTX_LSB&t;&t; 0
DECL|macro|GBE_CRS_START_XY_CRS_STARTY_MSB
mdefine_line|#define GBE_CRS_START_XY_CRS_STARTY_MSB&t;&t;23
DECL|macro|GBE_CRS_START_XY_CRS_STARTY_LSB
mdefine_line|#define GBE_CRS_START_XY_CRS_STARTY_LSB&t;&t;12
DECL|macro|GBE_CRS_START_XY_CRS_STARTX_MSB
mdefine_line|#define GBE_CRS_START_XY_CRS_STARTX_MSB&t;&t;11
DECL|macro|GBE_CRS_START_XY_CRS_STARTX_LSB
mdefine_line|#define GBE_CRS_START_XY_CRS_STARTX_LSB&t;&t; 0
DECL|macro|GBE_WID_AUX_MSB
mdefine_line|#define GBE_WID_AUX_MSB&t;&t;12
DECL|macro|GBE_WID_AUX_LSB
mdefine_line|#define GBE_WID_AUX_LSB&t;&t;11
DECL|macro|GBE_WID_GAMMA_MSB
mdefine_line|#define GBE_WID_GAMMA_MSB&t;10
DECL|macro|GBE_WID_GAMMA_LSB
mdefine_line|#define GBE_WID_GAMMA_LSB&t;10
DECL|macro|GBE_WID_CM_MSB
mdefine_line|#define GBE_WID_CM_MSB&t;&t; 9
DECL|macro|GBE_WID_CM_LSB
mdefine_line|#define GBE_WID_CM_LSB&t;&t; 5
DECL|macro|GBE_WID_TYP_MSB
mdefine_line|#define GBE_WID_TYP_MSB&t;&t; 4
DECL|macro|GBE_WID_TYP_LSB
mdefine_line|#define GBE_WID_TYP_LSB&t;&t; 2
DECL|macro|GBE_WID_BUF_MSB
mdefine_line|#define GBE_WID_BUF_MSB&t;&t; 1
DECL|macro|GBE_WID_BUF_LSB
mdefine_line|#define GBE_WID_BUF_LSB&t;&t; 0
DECL|macro|GBE_VC_START_XY_VC_STARTY_MSB
mdefine_line|#define GBE_VC_START_XY_VC_STARTY_MSB&t;23
DECL|macro|GBE_VC_START_XY_VC_STARTY_LSB
mdefine_line|#define GBE_VC_START_XY_VC_STARTY_LSB&t;12
DECL|macro|GBE_VC_START_XY_VC_STARTX_MSB
mdefine_line|#define GBE_VC_START_XY_VC_STARTX_MSB&t;11
DECL|macro|GBE_VC_START_XY_VC_STARTX_LSB
mdefine_line|#define GBE_VC_START_XY_VC_STARTX_LSB&t; 0
multiline_comment|/* Constants */
DECL|macro|GBE_FRM_DEPTH_8
mdefine_line|#define GBE_FRM_DEPTH_8&t;&t;0
DECL|macro|GBE_FRM_DEPTH_16
mdefine_line|#define GBE_FRM_DEPTH_16&t;1
DECL|macro|GBE_FRM_DEPTH_32
mdefine_line|#define GBE_FRM_DEPTH_32&t;2
DECL|macro|GBE_CMODE_I8
mdefine_line|#define GBE_CMODE_I8&t;&t;0
DECL|macro|GBE_CMODE_I12
mdefine_line|#define GBE_CMODE_I12&t;&t;1
DECL|macro|GBE_CMODE_RG3B2
mdefine_line|#define GBE_CMODE_RG3B2&t;&t;2
DECL|macro|GBE_CMODE_RGB4
mdefine_line|#define GBE_CMODE_RGB4&t;&t;3
DECL|macro|GBE_CMODE_ARGB5
mdefine_line|#define GBE_CMODE_ARGB5&t;&t;4
DECL|macro|GBE_CMODE_RGB8
mdefine_line|#define GBE_CMODE_RGB8&t;&t;5
DECL|macro|GBE_CMODE_RGBA5
mdefine_line|#define GBE_CMODE_RGBA5&t;&t;6
DECL|macro|GBE_CMODE_RGB10
mdefine_line|#define GBE_CMODE_RGB10&t;&t;7
DECL|macro|GBE_BMODE_BOTH
mdefine_line|#define GBE_BMODE_BOTH&t;&t;3
DECL|macro|GBE_CRS_MAGIC
mdefine_line|#define GBE_CRS_MAGIC&t;&t;54
DECL|macro|GBE_PIXEN_MAGIC_ON
mdefine_line|#define GBE_PIXEN_MAGIC_ON&t;19
DECL|macro|GBE_PIXEN_MAGIC_OFF
mdefine_line|#define GBE_PIXEN_MAGIC_OFF&t; 2
DECL|macro|GBE_TLB_SIZE
mdefine_line|#define GBE_TLB_SIZE&t;&t;128
multiline_comment|/* [1] - only GBE revision 2 and later */
multiline_comment|/*&n; * Video Timing Data Structure&n; */
DECL|struct|gbe_timing_info
r_struct
id|gbe_timing_info
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Monitor resolution */
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|fields_sec
r_int
id|fields_sec
suffix:semicolon
multiline_comment|/* fields/sec  (Hz -3 dec. places */
DECL|member|cfreq
r_int
id|cfreq
suffix:semicolon
multiline_comment|/* pixel clock frequency (MHz -3 dec. places) */
DECL|member|htotal
r_int
id|htotal
suffix:semicolon
multiline_comment|/* Horizontal total pixels */
DECL|member|hblank_start
r_int
id|hblank_start
suffix:semicolon
multiline_comment|/* Horizontal blank start */
DECL|member|hblank_end
r_int
id|hblank_end
suffix:semicolon
multiline_comment|/* Horizontal blank end */
DECL|member|hsync_start
r_int
id|hsync_start
suffix:semicolon
multiline_comment|/* Horizontal sync start */
DECL|member|hsync_end
r_int
id|hsync_end
suffix:semicolon
multiline_comment|/* Horizontal sync end */
DECL|member|vtotal
r_int
id|vtotal
suffix:semicolon
multiline_comment|/* Vertical total lines */
DECL|member|vblank_start
r_int
id|vblank_start
suffix:semicolon
multiline_comment|/* Vertical blank start */
DECL|member|vblank_end
r_int
id|vblank_end
suffix:semicolon
multiline_comment|/* Vertical blank end */
DECL|member|vsync_start
r_int
id|vsync_start
suffix:semicolon
multiline_comment|/* Vertical sync start */
DECL|member|vsync_end
r_int
id|vsync_end
suffix:semicolon
multiline_comment|/* Vertical sync end */
DECL|member|pll_m
r_int
id|pll_m
suffix:semicolon
multiline_comment|/* PLL M parameter */
DECL|member|pll_n
r_int
id|pll_n
suffix:semicolon
multiline_comment|/* PLL P parameter */
DECL|member|pll_p
r_int
id|pll_p
suffix:semicolon
multiline_comment|/* PLL N parameter */
)brace
suffix:semicolon
multiline_comment|/* Defines for gbe_vof_info_t flags */
DECL|macro|GBE_VOF_UNKNOWNMON
mdefine_line|#define GBE_VOF_UNKNOWNMON&t;1
DECL|macro|GBE_VOF_STEREO
mdefine_line|#define GBE_VOF_STEREO&t;&t;2
DECL|macro|GBE_VOF_DO_GENSYNC
mdefine_line|#define GBE_VOF_DO_GENSYNC&t;4&t;/* enable incoming sync */
DECL|macro|GBE_VOF_SYNC_ON_GREEN
mdefine_line|#define GBE_VOF_SYNC_ON_GREEN&t;8&t;/* sync on green */
DECL|macro|GBE_VOF_FLATPANEL
mdefine_line|#define GBE_VOF_FLATPANEL&t;0x1000&t;/* FLATPANEL Timing */
DECL|macro|GBE_VOF_MAGICKEY
mdefine_line|#define GBE_VOF_MAGICKEY&t;0x2000&t;/* Backdoor key */
macro_line|#endif&t;&t;/* ! __GBE_H__ */
eof
