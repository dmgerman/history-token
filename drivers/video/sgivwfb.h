multiline_comment|/*&n; *  linux/drivers/video/sgivwfb.h -- SGI DBE frame buffer device header&n; *&n; *      Copyright (C) 1999 Silicon Graphics, Inc.&n; *      Jeffrey Newquist, newquist@engr.sgi.som&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#ifndef __SGIVWFB_H__
DECL|macro|__SGIVWFB_H__
mdefine_line|#define __SGIVWFB_H__
DECL|macro|DBE_GETREG
mdefine_line|#define DBE_GETREG(reg, dest)       ((dest) = DBE_REG_BASE-&gt;##reg)
DECL|macro|DBE_SETREG
mdefine_line|#define DBE_SETREG(reg, src)        DBE_REG_BASE-&gt;##reg = (src)
DECL|macro|DBE_IGETREG
mdefine_line|#define DBE_IGETREG(reg, idx, dest) ((dest) = DBE_REG_BASE-&gt;##reg##[idx])
DECL|macro|DBE_ISETREG
mdefine_line|#define DBE_ISETREG(reg, idx, src)  (DBE_REG_BASE-&gt;##reg##[idx] = (src))
DECL|macro|MASK
mdefine_line|#define MASK(msb, lsb)          ( (((u32)1&lt;&lt;((msb)-(lsb)+1))-1) &lt;&lt; (lsb) )
DECL|macro|GET
mdefine_line|#define GET(v, msb, lsb)        ( ((u32)(v) &amp; MASK(msb,lsb)) &gt;&gt; (lsb) )
DECL|macro|SET
mdefine_line|#define SET(v, f, msb, lsb)     ( (v) = ((v)&amp;~MASK(msb,lsb)) | (( (u32)(f)&lt;&lt;(lsb) ) &amp; MASK(msb,lsb)) )
DECL|macro|GET_DBE_FIELD
mdefine_line|#define GET_DBE_FIELD(reg, field, v)        GET((v), DBE_##reg##_##field##_MSB, DBE_##reg##_##field##_LSB)
DECL|macro|SET_DBE_FIELD
mdefine_line|#define SET_DBE_FIELD(reg, field, v, f)     SET((v), (f), DBE_##reg##_##field##_MSB, DBE_##reg##_##field##_LSB)
multiline_comment|/* NOTE: All loads/stores must be 32 bits and uncached */
DECL|macro|DBE_REG_PHYS
mdefine_line|#define DBE_REG_PHYS&t;0xd0000000
DECL|macro|DBE_REG_SIZE
mdefine_line|#define DBE_REG_SIZE        0x01000000
r_typedef
r_struct
(brace
DECL|member|ctrlstat
r_volatile
id|u32
id|ctrlstat
suffix:semicolon
multiline_comment|/* 0x000000 general control */
DECL|member|dotclock
r_volatile
id|u32
id|dotclock
suffix:semicolon
multiline_comment|/* 0x000004 dot clock PLL control */
DECL|member|i2c
r_volatile
id|u32
id|i2c
suffix:semicolon
multiline_comment|/* 0x000008 crt I2C control */
DECL|member|sysclk
r_volatile
id|u32
id|sysclk
suffix:semicolon
multiline_comment|/* 0x00000c system clock PLL control */
DECL|member|i2cfp
r_volatile
id|u32
id|i2cfp
suffix:semicolon
multiline_comment|/* 0x000010 flat panel I2C control */
DECL|member|id
r_volatile
id|u32
id|id
suffix:semicolon
multiline_comment|/* 0x000014 device id/chip revision */
DECL|member|config
r_volatile
id|u32
id|config
suffix:semicolon
multiline_comment|/* 0x000018 power on configuration */
DECL|member|bist
r_volatile
id|u32
id|bist
suffix:semicolon
multiline_comment|/* 0x00001c internal bist status */
DECL|member|_pad0
r_char
id|_pad0
(braket
l_int|0x010000
op_minus
l_int|0x000020
)braket
suffix:semicolon
DECL|member|vt_xy
r_volatile
id|u32
id|vt_xy
suffix:semicolon
multiline_comment|/* 0x010000 current dot coords */
DECL|member|vt_xymax
r_volatile
id|u32
id|vt_xymax
suffix:semicolon
multiline_comment|/* 0x010004 maximum dot coords */
DECL|member|vt_vsync
r_volatile
id|u32
id|vt_vsync
suffix:semicolon
multiline_comment|/* 0x010008 vsync on/off */
DECL|member|vt_hsync
r_volatile
id|u32
id|vt_hsync
suffix:semicolon
multiline_comment|/* 0x01000c hsync on/off */
DECL|member|vt_vblank
r_volatile
id|u32
id|vt_vblank
suffix:semicolon
multiline_comment|/* 0x010010 vblank on/off */
DECL|member|vt_hblank
r_volatile
id|u32
id|vt_hblank
suffix:semicolon
multiline_comment|/* 0x010014 hblank on/off */
DECL|member|vt_flags
r_volatile
id|u32
id|vt_flags
suffix:semicolon
multiline_comment|/* 0x010018 polarity of vt signals */
DECL|member|vt_f2rf_lock
r_volatile
id|u32
id|vt_f2rf_lock
suffix:semicolon
multiline_comment|/* 0x01001c f2rf &amp; framelck y coord */
DECL|member|vt_intr01
r_volatile
id|u32
id|vt_intr01
suffix:semicolon
multiline_comment|/* 0x010020 intr 0,1 y coords */
DECL|member|vt_intr23
r_volatile
id|u32
id|vt_intr23
suffix:semicolon
multiline_comment|/* 0x010024 intr 2,3 y coords */
DECL|member|fp_hdrv
r_volatile
id|u32
id|fp_hdrv
suffix:semicolon
multiline_comment|/* 0x010028 flat panel hdrv on/off */
DECL|member|fp_vdrv
r_volatile
id|u32
id|fp_vdrv
suffix:semicolon
multiline_comment|/* 0x01002c flat panel vdrv on/off */
DECL|member|fp_de
r_volatile
id|u32
id|fp_de
suffix:semicolon
multiline_comment|/* 0x010030 flat panel de on/off */
DECL|member|vt_hpixen
r_volatile
id|u32
id|vt_hpixen
suffix:semicolon
multiline_comment|/* 0x010034 intrnl horiz pixel on/off*/
DECL|member|vt_vpixen
r_volatile
id|u32
id|vt_vpixen
suffix:semicolon
multiline_comment|/* 0x010038 intrnl vert pixel on/off */
DECL|member|vt_hcmap
r_volatile
id|u32
id|vt_hcmap
suffix:semicolon
multiline_comment|/* 0x01003c cmap write (horiz) */
DECL|member|vt_vcmap
r_volatile
id|u32
id|vt_vcmap
suffix:semicolon
multiline_comment|/* 0x010040 cmap write (vert) */
DECL|member|did_start_xy
r_volatile
id|u32
id|did_start_xy
suffix:semicolon
multiline_comment|/* 0x010044 eol/f did/xy reset val */
DECL|member|crs_start_xy
r_volatile
id|u32
id|crs_start_xy
suffix:semicolon
multiline_comment|/* 0x010048 eol/f crs/xy reset val */
DECL|member|vc_start_xy
r_volatile
id|u32
id|vc_start_xy
suffix:semicolon
multiline_comment|/* 0x01004c eol/f vc/xy reset val */
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x020000
op_minus
l_int|0x010050
)braket
suffix:semicolon
DECL|member|ovr_width_tile
r_volatile
id|u32
id|ovr_width_tile
suffix:semicolon
multiline_comment|/* 0x020000 overlay plane ctrl 0 */
DECL|member|ovr_inhwctrl
r_volatile
id|u32
id|ovr_inhwctrl
suffix:semicolon
multiline_comment|/* 0x020004 overlay plane ctrl 1 */
DECL|member|ovr_control
r_volatile
id|u32
id|ovr_control
suffix:semicolon
multiline_comment|/* 0x020008 overlay plane ctrl 1 */
DECL|member|_pad2
r_char
id|_pad2
(braket
l_int|0x030000
op_minus
l_int|0x02000C
)braket
suffix:semicolon
DECL|member|frm_size_tile
r_volatile
id|u32
id|frm_size_tile
suffix:semicolon
multiline_comment|/* 0x030000 normal plane ctrl 0 */
DECL|member|frm_size_pixel
r_volatile
id|u32
id|frm_size_pixel
suffix:semicolon
multiline_comment|/* 0x030004 normal plane ctrl 1 */
DECL|member|frm_inhwctrl
r_volatile
id|u32
id|frm_inhwctrl
suffix:semicolon
multiline_comment|/* 0x030008 normal plane ctrl 2 */
DECL|member|frm_control
r_volatile
id|u32
id|frm_control
suffix:semicolon
multiline_comment|/* 0x03000C normal plane ctrl 3 */
DECL|member|_pad3
r_char
id|_pad3
(braket
l_int|0x040000
op_minus
l_int|0x030010
)braket
suffix:semicolon
DECL|member|did_inhwctrl
r_volatile
id|u32
id|did_inhwctrl
suffix:semicolon
multiline_comment|/* 0x040000 DID control */
DECL|member|did_control
r_volatile
id|u32
id|did_control
suffix:semicolon
multiline_comment|/* 0x040004 DID shadow */
DECL|member|_pad4
r_char
id|_pad4
(braket
l_int|0x048000
op_minus
l_int|0x040008
)braket
suffix:semicolon
DECL|member|mode_regs
r_volatile
id|u32
id|mode_regs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 0x048000 - 0x04807c WID table */
DECL|member|_pad5
r_char
id|_pad5
(braket
l_int|0x050000
op_minus
l_int|0x048080
)braket
suffix:semicolon
DECL|member|cmap
r_volatile
id|u32
id|cmap
(braket
l_int|6144
)braket
suffix:semicolon
multiline_comment|/* 0x050000 - 0x055ffc color map */
DECL|member|_pad6
r_char
id|_pad6
(braket
l_int|0x058000
op_minus
l_int|0x056000
)braket
suffix:semicolon
DECL|member|cm_fifo
r_volatile
id|u32
id|cm_fifo
suffix:semicolon
multiline_comment|/* 0x058000 color map fifo status */
DECL|member|_pad7
r_char
id|_pad7
(braket
l_int|0x060000
op_minus
l_int|0x058004
)braket
suffix:semicolon
DECL|member|gmap
r_volatile
id|u32
id|gmap
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x060000 - 0x0603fc gamma map */
DECL|member|_pad8
r_char
id|_pad8
(braket
l_int|0x068000
op_minus
l_int|0x060400
)braket
suffix:semicolon
DECL|member|gmap10
r_volatile
id|u32
id|gmap10
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x068000 - 0x068ffc gamma map */
DECL|member|_pad9
r_char
id|_pad9
(braket
l_int|0x070000
op_minus
l_int|0x069000
)braket
suffix:semicolon
DECL|member|crs_pos
r_volatile
id|u32
id|crs_pos
suffix:semicolon
multiline_comment|/* 0x070000 cusror control 0 */
DECL|member|crs_ctl
r_volatile
id|u32
id|crs_ctl
suffix:semicolon
multiline_comment|/* 0x070004 cusror control 1 */
DECL|member|crs_cmap
r_volatile
id|u32
id|crs_cmap
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x070008 - 0x070010 crs cmap */
DECL|member|_pad10
r_char
id|_pad10
(braket
l_int|0x078000
op_minus
l_int|0x070014
)braket
suffix:semicolon
DECL|member|crs_glyph
r_volatile
id|u32
id|crs_glyph
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 0x078000 - 0x0780fc crs glyph */
DECL|member|_pad11
r_char
id|_pad11
(braket
l_int|0x080000
op_minus
l_int|0x078100
)braket
suffix:semicolon
DECL|member|vc_0
r_volatile
id|u32
id|vc_0
suffix:semicolon
multiline_comment|/* 0x080000 video capture crtl 0 */
DECL|member|vc_1
r_volatile
id|u32
id|vc_1
suffix:semicolon
multiline_comment|/* 0x080004 video capture crtl 1 */
DECL|member|vc_2
r_volatile
id|u32
id|vc_2
suffix:semicolon
multiline_comment|/* 0x080008 video capture crtl 2 */
DECL|member|vc_3
r_volatile
id|u32
id|vc_3
suffix:semicolon
multiline_comment|/* 0x08000c video capture crtl 3 */
DECL|member|vc_4
r_volatile
id|u32
id|vc_4
suffix:semicolon
multiline_comment|/* 0x080010 video capture crtl 3 */
DECL|member|vc_5
r_volatile
id|u32
id|vc_5
suffix:semicolon
multiline_comment|/* 0x080014 video capture crtl 3 */
DECL|member|vc_6
r_volatile
id|u32
id|vc_6
suffix:semicolon
multiline_comment|/* 0x080018 video capture crtl 3 */
DECL|member|vc_7
r_volatile
id|u32
id|vc_7
suffix:semicolon
multiline_comment|/* 0x08001c video capture crtl 3 */
DECL|member|vc_8
r_volatile
id|u32
id|vc_8
suffix:semicolon
multiline_comment|/* 0x08000c video capture crtl 3 */
DECL|typedef|asregs
)brace
id|asregs
suffix:semicolon
multiline_comment|/* Bit mask information */
DECL|macro|DBE_CTRLSTAT_CHIPID_MSB
mdefine_line|#define DBE_CTRLSTAT_CHIPID_MSB     3
DECL|macro|DBE_CTRLSTAT_CHIPID_LSB
mdefine_line|#define DBE_CTRLSTAT_CHIPID_LSB     0
DECL|macro|DBE_CTRLSTAT_SENSE_N_MSB
mdefine_line|#define DBE_CTRLSTAT_SENSE_N_MSB    4
DECL|macro|DBE_CTRLSTAT_SENSE_N_LSB
mdefine_line|#define DBE_CTRLSTAT_SENSE_N_LSB    4
DECL|macro|DBE_CTRLSTAT_PCLKSEL_MSB
mdefine_line|#define DBE_CTRLSTAT_PCLKSEL_MSB    29
DECL|macro|DBE_CTRLSTAT_PCLKSEL_LSB
mdefine_line|#define DBE_CTRLSTAT_PCLKSEL_LSB    28
DECL|macro|DBE_DOTCLK_M_MSB
mdefine_line|#define DBE_DOTCLK_M_MSB            7
DECL|macro|DBE_DOTCLK_M_LSB
mdefine_line|#define DBE_DOTCLK_M_LSB            0
DECL|macro|DBE_DOTCLK_N_MSB
mdefine_line|#define DBE_DOTCLK_N_MSB            13
DECL|macro|DBE_DOTCLK_N_LSB
mdefine_line|#define DBE_DOTCLK_N_LSB            8
DECL|macro|DBE_DOTCLK_P_MSB
mdefine_line|#define DBE_DOTCLK_P_MSB            15
DECL|macro|DBE_DOTCLK_P_LSB
mdefine_line|#define DBE_DOTCLK_P_LSB            14
DECL|macro|DBE_DOTCLK_RUN_MSB
mdefine_line|#define DBE_DOTCLK_RUN_MSB          20
DECL|macro|DBE_DOTCLK_RUN_LSB
mdefine_line|#define DBE_DOTCLK_RUN_LSB          20
DECL|macro|DBE_VT_XY_VT_FREEZE_MSB
mdefine_line|#define DBE_VT_XY_VT_FREEZE_MSB     31
DECL|macro|DBE_VT_XY_VT_FREEZE_LSB
mdefine_line|#define DBE_VT_XY_VT_FREEZE_LSB     31
DECL|macro|DBE_VT_VSYNC_VT_VSYNC_ON_MSB
mdefine_line|#define DBE_VT_VSYNC_VT_VSYNC_ON_MSB        23
DECL|macro|DBE_VT_VSYNC_VT_VSYNC_ON_LSB
mdefine_line|#define DBE_VT_VSYNC_VT_VSYNC_ON_LSB        12
DECL|macro|DBE_VT_VSYNC_VT_VSYNC_OFF_MSB
mdefine_line|#define DBE_VT_VSYNC_VT_VSYNC_OFF_MSB       11
DECL|macro|DBE_VT_VSYNC_VT_VSYNC_OFF_LSB
mdefine_line|#define DBE_VT_VSYNC_VT_VSYNC_OFF_LSB       0
DECL|macro|DBE_VT_HSYNC_VT_HSYNC_ON_MSB
mdefine_line|#define DBE_VT_HSYNC_VT_HSYNC_ON_MSB        23
DECL|macro|DBE_VT_HSYNC_VT_HSYNC_ON_LSB
mdefine_line|#define DBE_VT_HSYNC_VT_HSYNC_ON_LSB        12
DECL|macro|DBE_VT_HSYNC_VT_HSYNC_OFF_MSB
mdefine_line|#define DBE_VT_HSYNC_VT_HSYNC_OFF_MSB       11
DECL|macro|DBE_VT_HSYNC_VT_HSYNC_OFF_LSB
mdefine_line|#define DBE_VT_HSYNC_VT_HSYNC_OFF_LSB       0
DECL|macro|DBE_VT_VBLANK_VT_VBLANK_ON_MSB
mdefine_line|#define DBE_VT_VBLANK_VT_VBLANK_ON_MSB        23
DECL|macro|DBE_VT_VBLANK_VT_VBLANK_ON_LSB
mdefine_line|#define DBE_VT_VBLANK_VT_VBLANK_ON_LSB        12
DECL|macro|DBE_VT_VBLANK_VT_VBLANK_OFF_MSB
mdefine_line|#define DBE_VT_VBLANK_VT_VBLANK_OFF_MSB       11
DECL|macro|DBE_VT_VBLANK_VT_VBLANK_OFF_LSB
mdefine_line|#define DBE_VT_VBLANK_VT_VBLANK_OFF_LSB       0
DECL|macro|DBE_VT_HBLANK_VT_HBLANK_ON_MSB
mdefine_line|#define DBE_VT_HBLANK_VT_HBLANK_ON_MSB        23
DECL|macro|DBE_VT_HBLANK_VT_HBLANK_ON_LSB
mdefine_line|#define DBE_VT_HBLANK_VT_HBLANK_ON_LSB        12
DECL|macro|DBE_VT_HBLANK_VT_HBLANK_OFF_MSB
mdefine_line|#define DBE_VT_HBLANK_VT_HBLANK_OFF_MSB       11
DECL|macro|DBE_VT_HBLANK_VT_HBLANK_OFF_LSB
mdefine_line|#define DBE_VT_HBLANK_VT_HBLANK_OFF_LSB       0
DECL|macro|DBE_VT_VCMAP_VT_VCMAP_ON_MSB
mdefine_line|#define DBE_VT_VCMAP_VT_VCMAP_ON_MSB        23
DECL|macro|DBE_VT_VCMAP_VT_VCMAP_ON_LSB
mdefine_line|#define DBE_VT_VCMAP_VT_VCMAP_ON_LSB        12
DECL|macro|DBE_VT_VCMAP_VT_VCMAP_OFF_MSB
mdefine_line|#define DBE_VT_VCMAP_VT_VCMAP_OFF_MSB       11
DECL|macro|DBE_VT_VCMAP_VT_VCMAP_OFF_LSB
mdefine_line|#define DBE_VT_VCMAP_VT_VCMAP_OFF_LSB       0
DECL|macro|DBE_VT_HCMAP_VT_HCMAP_ON_MSB
mdefine_line|#define DBE_VT_HCMAP_VT_HCMAP_ON_MSB        23
DECL|macro|DBE_VT_HCMAP_VT_HCMAP_ON_LSB
mdefine_line|#define DBE_VT_HCMAP_VT_HCMAP_ON_LSB        12
DECL|macro|DBE_VT_HCMAP_VT_HCMAP_OFF_MSB
mdefine_line|#define DBE_VT_HCMAP_VT_HCMAP_OFF_MSB       11
DECL|macro|DBE_VT_HCMAP_VT_HCMAP_OFF_LSB
mdefine_line|#define DBE_VT_HCMAP_VT_HCMAP_OFF_LSB       0
DECL|macro|DBE_VT_XYMAX_VT_MAXX_MSB
mdefine_line|#define DBE_VT_XYMAX_VT_MAXX_MSB    11
DECL|macro|DBE_VT_XYMAX_VT_MAXX_LSB
mdefine_line|#define DBE_VT_XYMAX_VT_MAXX_LSB    0
DECL|macro|DBE_VT_XYMAX_VT_MAXY_MSB
mdefine_line|#define DBE_VT_XYMAX_VT_MAXY_MSB    23
DECL|macro|DBE_VT_XYMAX_VT_MAXY_LSB
mdefine_line|#define DBE_VT_XYMAX_VT_MAXY_LSB    12
DECL|macro|DBE_VT_HPIXEN_VT_HPIXEN_ON_MSB
mdefine_line|#define DBE_VT_HPIXEN_VT_HPIXEN_ON_MSB      23
DECL|macro|DBE_VT_HPIXEN_VT_HPIXEN_ON_LSB
mdefine_line|#define DBE_VT_HPIXEN_VT_HPIXEN_ON_LSB      12
DECL|macro|DBE_VT_HPIXEN_VT_HPIXEN_OFF_MSB
mdefine_line|#define DBE_VT_HPIXEN_VT_HPIXEN_OFF_MSB     11
DECL|macro|DBE_VT_HPIXEN_VT_HPIXEN_OFF_LSB
mdefine_line|#define DBE_VT_HPIXEN_VT_HPIXEN_OFF_LSB     0
DECL|macro|DBE_VT_VPIXEN_VT_VPIXEN_ON_MSB
mdefine_line|#define DBE_VT_VPIXEN_VT_VPIXEN_ON_MSB      23
DECL|macro|DBE_VT_VPIXEN_VT_VPIXEN_ON_LSB
mdefine_line|#define DBE_VT_VPIXEN_VT_VPIXEN_ON_LSB      12
DECL|macro|DBE_VT_VPIXEN_VT_VPIXEN_OFF_MSB
mdefine_line|#define DBE_VT_VPIXEN_VT_VPIXEN_OFF_MSB     11
DECL|macro|DBE_VT_VPIXEN_VT_VPIXEN_OFF_LSB
mdefine_line|#define DBE_VT_VPIXEN_VT_VPIXEN_OFF_LSB     0
DECL|macro|DBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB
mdefine_line|#define DBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB  0
DECL|macro|DBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB
mdefine_line|#define DBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB  0
DECL|macro|DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB
mdefine_line|#define DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB 0
DECL|macro|DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB
mdefine_line|#define DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB 0
DECL|macro|DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB
mdefine_line|#define DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB       13
DECL|macro|DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB
mdefine_line|#define DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB       13
DECL|macro|DBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB  0
DECL|macro|DBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB  0
DECL|macro|DBE_FRM_CONTROL_FRM_TILE_PTR_MSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_TILE_PTR_MSB    31
DECL|macro|DBE_FRM_CONTROL_FRM_TILE_PTR_LSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_TILE_PTR_LSB    9
DECL|macro|DBE_FRM_CONTROL_FRM_LINEAR_MSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_LINEAR_MSB      1
DECL|macro|DBE_FRM_CONTROL_FRM_LINEAR_LSB
mdefine_line|#define DBE_FRM_CONTROL_FRM_LINEAR_LSB      1
DECL|macro|DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB
mdefine_line|#define DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB 0
DECL|macro|DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB
mdefine_line|#define DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB 0
DECL|macro|DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB        12
DECL|macro|DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB        5
DECL|macro|DBE_FRM_SIZE_TILE_FRM_RHS_MSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_RHS_MSB       4
DECL|macro|DBE_FRM_SIZE_TILE_FRM_RHS_LSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_RHS_LSB       0
DECL|macro|DBE_FRM_SIZE_TILE_FRM_DEPTH_MSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_DEPTH_MSB     14
DECL|macro|DBE_FRM_SIZE_TILE_FRM_DEPTH_LSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_DEPTH_LSB     13
DECL|macro|DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB        15
DECL|macro|DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB
mdefine_line|#define DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB        15
DECL|macro|DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB
mdefine_line|#define DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB        31
DECL|macro|DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB
mdefine_line|#define DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB        16
DECL|macro|DBE_DID_CONTROL_DID_DMA_ENABLE_MSB
mdefine_line|#define DBE_DID_CONTROL_DID_DMA_ENABLE_MSB  0
DECL|macro|DBE_DID_CONTROL_DID_DMA_ENABLE_LSB
mdefine_line|#define DBE_DID_CONTROL_DID_DMA_ENABLE_LSB  0
DECL|macro|DBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB
mdefine_line|#define DBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB 0
DECL|macro|DBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB
mdefine_line|#define DBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB 0
DECL|macro|DBE_DID_START_XY_DID_STARTY_MSB
mdefine_line|#define DBE_DID_START_XY_DID_STARTY_MSB     23
DECL|macro|DBE_DID_START_XY_DID_STARTY_LSB
mdefine_line|#define DBE_DID_START_XY_DID_STARTY_LSB     12
DECL|macro|DBE_DID_START_XY_DID_STARTX_MSB
mdefine_line|#define DBE_DID_START_XY_DID_STARTX_MSB     11
DECL|macro|DBE_DID_START_XY_DID_STARTX_LSB
mdefine_line|#define DBE_DID_START_XY_DID_STARTX_LSB     0
DECL|macro|DBE_CRS_START_XY_CRS_STARTY_MSB
mdefine_line|#define DBE_CRS_START_XY_CRS_STARTY_MSB     23
DECL|macro|DBE_CRS_START_XY_CRS_STARTY_LSB
mdefine_line|#define DBE_CRS_START_XY_CRS_STARTY_LSB     12
DECL|macro|DBE_CRS_START_XY_CRS_STARTX_MSB
mdefine_line|#define DBE_CRS_START_XY_CRS_STARTX_MSB     11
DECL|macro|DBE_CRS_START_XY_CRS_STARTX_LSB
mdefine_line|#define DBE_CRS_START_XY_CRS_STARTX_LSB     0
DECL|macro|DBE_WID_TYP_MSB
mdefine_line|#define DBE_WID_TYP_MSB     4
DECL|macro|DBE_WID_TYP_LSB
mdefine_line|#define DBE_WID_TYP_LSB     2
DECL|macro|DBE_WID_BUF_MSB
mdefine_line|#define DBE_WID_BUF_MSB     1
DECL|macro|DBE_WID_BUF_LSB
mdefine_line|#define DBE_WID_BUF_LSB     0
DECL|macro|DBE_VC_START_XY_VC_STARTY_MSB
mdefine_line|#define DBE_VC_START_XY_VC_STARTY_MSB       23
DECL|macro|DBE_VC_START_XY_VC_STARTY_LSB
mdefine_line|#define DBE_VC_START_XY_VC_STARTY_LSB       12
DECL|macro|DBE_VC_START_XY_VC_STARTX_MSB
mdefine_line|#define DBE_VC_START_XY_VC_STARTX_MSB       11
DECL|macro|DBE_VC_START_XY_VC_STARTX_LSB
mdefine_line|#define DBE_VC_START_XY_VC_STARTX_LSB       0
multiline_comment|/* Constants */
DECL|macro|DBE_FRM_DEPTH_8
mdefine_line|#define DBE_FRM_DEPTH_8     0
DECL|macro|DBE_FRM_DEPTH_16
mdefine_line|#define DBE_FRM_DEPTH_16    1
DECL|macro|DBE_FRM_DEPTH_32
mdefine_line|#define DBE_FRM_DEPTH_32    2
DECL|macro|DBE_CMODE_I8
mdefine_line|#define DBE_CMODE_I8        0
DECL|macro|DBE_CMODE_I12
mdefine_line|#define DBE_CMODE_I12       1
DECL|macro|DBE_CMODE_RG3B2
mdefine_line|#define DBE_CMODE_RG3B2     2
DECL|macro|DBE_CMODE_RGB4
mdefine_line|#define DBE_CMODE_RGB4      3
DECL|macro|DBE_CMODE_ARGB5
mdefine_line|#define DBE_CMODE_ARGB5     4
DECL|macro|DBE_CMODE_RGB8
mdefine_line|#define DBE_CMODE_RGB8      5
DECL|macro|DBE_CMODE_RGBA5
mdefine_line|#define DBE_CMODE_RGBA5     6
DECL|macro|DBE_CMODE_RGB10
mdefine_line|#define DBE_CMODE_RGB10     7
DECL|macro|DBE_BMODE_BOTH
mdefine_line|#define DBE_BMODE_BOTH      3
DECL|macro|DBE_CRS_MAGIC
mdefine_line|#define DBE_CRS_MAGIC       54
multiline_comment|/* Config Register (DBE Only) Definitions */
DECL|macro|DBE_CONFIG_VDAC_ENABLE
mdefine_line|#define DBE_CONFIG_VDAC_ENABLE       0x00000001
DECL|macro|DBE_CONFIG_VDAC_GSYNC
mdefine_line|#define DBE_CONFIG_VDAC_GSYNC        0x00000002
DECL|macro|DBE_CONFIG_VDAC_PBLANK
mdefine_line|#define DBE_CONFIG_VDAC_PBLANK       0x00000004
DECL|macro|DBE_CONFIG_FPENABLE
mdefine_line|#define DBE_CONFIG_FPENABLE          0x00000008
DECL|macro|DBE_CONFIG_LENDIAN
mdefine_line|#define DBE_CONFIG_LENDIAN           0x00000020
DECL|macro|DBE_CONFIG_TILEHIST
mdefine_line|#define DBE_CONFIG_TILEHIST          0x00000040
DECL|macro|DBE_CONFIG_EXT_ADDR
mdefine_line|#define DBE_CONFIG_EXT_ADDR          0x00000080
DECL|macro|DBE_CONFIG_FBDEV
mdefine_line|#define DBE_CONFIG_FBDEV        ( DBE_CONFIG_VDAC_ENABLE | &bslash;&n;                                      DBE_CONFIG_VDAC_GSYNC  | &bslash;&n;                                      DBE_CONFIG_VDAC_PBLANK | &bslash;&n;                                      DBE_CONFIG_LENDIAN     | &bslash;&n;                                      DBE_CONFIG_EXT_ADDR )
multiline_comment|/*&n; * Available Video Timings and Corresponding Indices&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DBE_VT_640_480_60
id|DBE_VT_640_480_60
comma
DECL|enumerator|DBE_VT_800_600_60
id|DBE_VT_800_600_60
comma
DECL|enumerator|DBE_VT_800_600_75
id|DBE_VT_800_600_75
comma
DECL|enumerator|DBE_VT_800_600_120
id|DBE_VT_800_600_120
comma
DECL|enumerator|DBE_VT_1024_768_50
id|DBE_VT_1024_768_50
comma
DECL|enumerator|DBE_VT_1024_768_60
id|DBE_VT_1024_768_60
comma
DECL|enumerator|DBE_VT_1024_768_75
id|DBE_VT_1024_768_75
comma
DECL|enumerator|DBE_VT_1024_768_85
id|DBE_VT_1024_768_85
comma
DECL|enumerator|DBE_VT_1024_768_120
id|DBE_VT_1024_768_120
comma
DECL|enumerator|DBE_VT_1280_1024_50
id|DBE_VT_1280_1024_50
comma
DECL|enumerator|DBE_VT_1280_1024_60
id|DBE_VT_1280_1024_60
comma
DECL|enumerator|DBE_VT_1280_1024_75
id|DBE_VT_1280_1024_75
comma
DECL|enumerator|DBE_VT_1280_1024_85
id|DBE_VT_1280_1024_85
comma
DECL|enumerator|DBE_VT_1600_1024_53
id|DBE_VT_1600_1024_53
comma
DECL|enumerator|DBE_VT_1600_1024_60
id|DBE_VT_1600_1024_60
comma
DECL|enumerator|DBE_VT_1600_1200_50
id|DBE_VT_1600_1200_50
comma
DECL|enumerator|DBE_VT_1600_1200_60
id|DBE_VT_1600_1200_60
comma
DECL|enumerator|DBE_VT_1600_1200_75
id|DBE_VT_1600_1200_75
comma
DECL|enumerator|DBE_VT_1920_1080_50
id|DBE_VT_1920_1080_50
comma
DECL|enumerator|DBE_VT_1920_1080_60
id|DBE_VT_1920_1080_60
comma
DECL|enumerator|DBE_VT_1920_1080_72
id|DBE_VT_1920_1080_72
comma
DECL|enumerator|DBE_VT_1920_1200_50
id|DBE_VT_1920_1200_50
comma
DECL|enumerator|DBE_VT_1920_1200_60
id|DBE_VT_1920_1200_60
comma
DECL|enumerator|DBE_VT_1920_1200_66
id|DBE_VT_1920_1200_66
comma
DECL|enumerator|DBE_VT_UNKNOWN
id|DBE_VT_UNKNOWN
DECL|typedef|dbe_timing_t
)brace
id|dbe_timing_t
suffix:semicolon
multiline_comment|/*&n; * Crime Video Timing Data Structure&n; */
DECL|struct|dbe_timing_info
r_typedef
r_struct
id|dbe_timing_info
(brace
DECL|member|type
id|dbe_timing_t
id|type
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Monitor resolution&t;&t;*/
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
multiline_comment|/* Horizontal total pixels&t;*/
DECL|member|hblank_start
r_int
id|hblank_start
suffix:semicolon
multiline_comment|/* Horizontal blank start&t;*/
DECL|member|hblank_end
r_int
id|hblank_end
suffix:semicolon
multiline_comment|/* Horizontal blank end&t;&t;*/
DECL|member|hsync_start
r_int
id|hsync_start
suffix:semicolon
multiline_comment|/* Horizontal sync start&t;*/
DECL|member|hsync_end
r_int
id|hsync_end
suffix:semicolon
multiline_comment|/* Horizontal sync end&t;&t;*/
DECL|member|vtotal
r_int
id|vtotal
suffix:semicolon
multiline_comment|/* Vertical total lines&t;&t;*/
DECL|member|vblank_start
r_int
id|vblank_start
suffix:semicolon
multiline_comment|/* Vertical blank start&t;&t;*/
DECL|member|vblank_end
r_int
id|vblank_end
suffix:semicolon
multiline_comment|/* Vertical blank end&t;&t;*/
DECL|member|vsync_start
r_int
id|vsync_start
suffix:semicolon
multiline_comment|/* Vertical sync start&t;&t;*/
DECL|member|vsync_end
r_int
id|vsync_end
suffix:semicolon
multiline_comment|/* Vertical sync end&t;&t;*/
DECL|member|pll_m
r_int
id|pll_m
suffix:semicolon
multiline_comment|/* PLL M parameter&t;&t;*/
DECL|member|pll_n
r_int
id|pll_n
suffix:semicolon
multiline_comment|/* PLL P parameter&t;&t;*/
DECL|member|pll_p
r_int
id|pll_p
suffix:semicolon
multiline_comment|/* PLL N parameter&t;&t;*/
DECL|typedef|dbe_timing_info_t
)brace
id|dbe_timing_info_t
suffix:semicolon
multiline_comment|/* Defines for dbe_vof_info_t flags */
DECL|macro|DBE_VOF_UNKNOWNMON
mdefine_line|#define DBE_VOF_UNKNOWNMON    1
DECL|macro|DBE_VOF_STEREO
mdefine_line|#define DBE_VOF_STEREO        2
DECL|macro|DBE_VOF_DO_GENSYNC
mdefine_line|#define DBE_VOF_DO_GENSYNC    4          /* enable incoming sync */
DECL|macro|DBE_VOF_SYNC_ON_GREEN
mdefine_line|#define DBE_VOF_SYNC_ON_GREEN 8          /* sync on green */
DECL|macro|DBE_VOF_FLATPANEL
mdefine_line|#define DBE_VOF_FLATPANEL     0x1000     /* FLATPANEL Timing */
DECL|macro|DBE_VOF_MAGICKEY
mdefine_line|#define DBE_VOF_MAGICKEY      0x2000     /* Backdoor key */
multiline_comment|/*&n; * DBE Timing Tables&n; */
macro_line|#ifdef INCLUDE_TIMING_TABLE_DATA
DECL|variable|dbeVTimings
r_struct
id|dbe_timing_info
id|dbeVTimings
(braket
)braket
op_assign
(brace
(brace
id|DBE_VT_640_480_60
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|640
comma
l_int|480
comma
l_int|59940
comma
l_int|25175
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|800
comma
l_int|640
comma
l_int|800
comma
l_int|656
comma
l_int|752
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|525
comma
l_int|480
comma
l_int|525
comma
l_int|490
comma
l_int|492
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|15
comma
l_int|2
comma
l_int|3
)brace
comma
(brace
id|DBE_VT_800_600_60
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|800
comma
l_int|600
comma
l_int|60317
comma
l_int|40000
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1056
comma
l_int|800
comma
l_int|1056
comma
l_int|840
comma
l_int|968
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|628
comma
l_int|600
comma
l_int|628
comma
l_int|601
comma
l_int|605
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|3
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
id|DBE_VT_800_600_75
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;    height,&t;&t;fields_sec,&t;    cfreq */
l_int|0
comma
l_int|800
comma
l_int|600
comma
l_int|75000
comma
l_int|49500
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1056
comma
l_int|800
comma
l_int|1056
comma
l_int|816
comma
l_int|896
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|625
comma
l_int|600
comma
l_int|625
comma
l_int|601
comma
l_int|604
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;    pll_p */
l_int|11
comma
l_int|3
comma
l_int|1
)brace
comma
(brace
id|DBE_VT_800_600_120
comma
multiline_comment|/*&t;flags,&t;&t;&t;&t;&t;width,&t;&t;height,&t;&t;&t;fields_sec,&t;    cfreq */
id|DBE_VOF_STEREO
comma
l_int|800
comma
l_int|600
comma
l_int|119800
comma
l_int|82978
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1040
comma
l_int|800
comma
l_int|1040
comma
l_int|856
comma
l_int|976
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|666
comma
l_int|600
comma
l_int|666
comma
l_int|637
comma
l_int|643
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;    pll_p */
l_int|31
comma
l_int|5
comma
l_int|1
)brace
comma
(brace
id|DBE_VT_1024_768_50
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;    height,&t;&t;fields_sec,&t;    cfreq */
l_int|0
comma
l_int|1024
comma
l_int|768
comma
l_int|50000
comma
l_int|54163
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1344
comma
l_int|1024
comma
l_int|1344
comma
l_int|1048
comma
l_int|1184
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|806
comma
l_int|768
comma
l_int|806
comma
l_int|771
comma
l_int|777
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;    pll_p */
l_int|4
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
id|DBE_VT_1024_768_60
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1024
comma
l_int|768
comma
l_int|60004
comma
l_int|65000
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1344
comma
l_int|1024
comma
l_int|1344
comma
l_int|1048
comma
l_int|1184
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|806
comma
l_int|768
comma
l_int|806
comma
l_int|771
comma
l_int|777
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|12
comma
l_int|5
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1024_768_75
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1024
comma
l_int|768
comma
l_int|75029
comma
l_int|78750
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1312
comma
l_int|1024
comma
l_int|1312
comma
l_int|1040
comma
l_int|1136
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|800
comma
l_int|768
comma
l_int|800
comma
l_int|769
comma
l_int|772
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|29
comma
l_int|5
comma
l_int|1
)brace
comma
(brace
id|DBE_VT_1024_768_85
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1024
comma
l_int|768
comma
l_int|84997
comma
l_int|94500
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1376
comma
l_int|1024
comma
l_int|1376
comma
l_int|1072
comma
l_int|1168
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|808
comma
l_int|768
comma
l_int|808
comma
l_int|769
comma
l_int|772
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|7
comma
l_int|2
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1024_768_120
comma
multiline_comment|/*&t;flags,&t;&t;&t;&t;&t;width,&t;&t;height,&t;&t;&t;fields_sec,&t;&t;cfreq */
id|DBE_VOF_STEREO
comma
l_int|1024
comma
l_int|768
comma
l_int|119800
comma
l_int|133195
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1376
comma
l_int|1024
comma
l_int|1376
comma
l_int|1072
comma
l_int|1168
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|808
comma
l_int|768
comma
l_int|808
comma
l_int|769
comma
l_int|772
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|5
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1280_1024_50
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1280
comma
l_int|1024
comma
l_int|50000
comma
l_int|89460
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1680
comma
l_int|1280
comma
l_int|1680
comma
l_int|1360
comma
l_int|1480
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|1065
comma
l_int|1024
comma
l_int|1065
comma
l_int|1027
comma
l_int|1030
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|10
comma
l_int|3
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1280_1024_60
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1280
comma
l_int|1024
comma
l_int|60020
comma
l_int|108000
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1688
comma
l_int|1280
comma
l_int|1688
comma
l_int|1328
comma
l_int|1440
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|1066
comma
l_int|1024
comma
l_int|1066
comma
l_int|1025
comma
l_int|1028
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|4
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1280_1024_75
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,&t;&t;cfreq */
l_int|0
comma
l_int|1280
comma
l_int|1024
comma
l_int|75025
comma
l_int|135000
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1688
comma
l_int|1280
comma
l_int|1688
comma
l_int|1296
comma
l_int|1440
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|1066
comma
l_int|1024
comma
l_int|1066
comma
l_int|1025
comma
l_int|1028
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;&t;pll_p */
l_int|5
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1280_1024_85
comma
multiline_comment|/*&t;flags,&t;width,&t;&t;    height,&t;&t;fields_sec,&t;    cfreq */
l_int|0
comma
l_int|1280
comma
l_int|1024
comma
l_int|85024
comma
l_int|157500
comma
multiline_comment|/*&t;htotal,&t;hblank_start,&t;hblank_end,&t;hsync_start,&t;hsync_end */
l_int|1728
comma
l_int|1280
comma
l_int|1728
comma
l_int|1344
comma
l_int|1504
comma
multiline_comment|/*&t;vtotal,&t;vblank_start,&t;vblank_end,&t;vsync_start,&t;vsync_end */
l_int|1072
comma
l_int|1024
comma
l_int|1072
comma
l_int|1025
comma
l_int|1028
comma
multiline_comment|/*&t;pll_m,&t;pll_n,&t;&t;    pll_p */
l_int|29
comma
l_int|5
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1600_1024_53
comma
multiline_comment|/* flags,&t;width,&t;&t;&t;height,&t;&t;fields_sec,     cfreq */
id|DBE_VOF_FLATPANEL
op_or
id|DBE_VOF_MAGICKEY
comma
l_int|1600
comma
l_int|1024
comma
l_int|53000
comma
l_int|107447
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|1900
comma
l_int|1600
comma
l_int|1900
comma
l_int|1630
comma
l_int|1730
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1067
comma
l_int|1024
comma
l_int|1067
comma
l_int|1027
comma
l_int|1030
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|4
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1600_1024_60
comma
multiline_comment|/* flags,&t;&t;&t;&t;&t;width,          height,&t;&t;&t;fields_sec,     cfreq */
id|DBE_VOF_FLATPANEL
comma
l_int|1600
comma
l_int|1024
comma
l_int|60000
comma
l_int|106913
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|1670
comma
l_int|1600
comma
l_int|1670
comma
l_int|1630
comma
l_int|1650
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1067
comma
l_int|1024
comma
l_int|1067
comma
l_int|1027
comma
l_int|1030
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|4
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1600_1200_50
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1600
comma
l_int|1200
comma
l_int|50000
comma
l_int|130500
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2088
comma
l_int|1600
comma
l_int|2088
comma
l_int|1644
comma
l_int|1764
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1205
comma
l_int|1211
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|24
comma
l_int|5
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1600_1200_60
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1600
comma
l_int|1200
comma
l_int|59940
comma
l_int|162000
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2160
comma
l_int|1600
comma
l_int|2160
comma
l_int|1644
comma
l_int|1856
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1201
comma
l_int|1204
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|6
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1600_1200_75
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1600
comma
l_int|1200
comma
l_int|75000
comma
l_int|202500
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2160
comma
l_int|1600
comma
l_int|2160
comma
l_int|1644
comma
l_int|1856
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1201
comma
l_int|1204
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|15
comma
l_int|2
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1080_50
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1080
comma
l_int|50000
comma
l_int|133200
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2368
comma
l_int|1920
comma
l_int|2368
comma
l_int|1952
comma
l_int|2096
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1125
comma
l_int|1080
comma
l_int|1125
comma
l_int|1083
comma
l_int|1086
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|5
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1080_60
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1080
comma
l_int|59940
comma
l_int|159840
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2368
comma
l_int|1920
comma
l_int|2368
comma
l_int|1952
comma
l_int|2096
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1125
comma
l_int|1080
comma
l_int|1125
comma
l_int|1083
comma
l_int|1086
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|6
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1080_72
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1080
comma
l_int|72000
comma
l_int|216023
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2560
comma
l_int|1920
comma
l_int|2560
comma
l_int|1968
comma
l_int|2184
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1172
comma
l_int|1080
comma
l_int|1172
comma
l_int|1083
comma
l_int|1086
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|8
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1200_50
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1200
comma
l_int|50000
comma
l_int|161500
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2584
comma
l_int|1920
comma
l_int|2584
comma
l_int|1984
comma
l_int|2240
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1203
comma
l_int|1206
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|6
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1200_60
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1200
comma
l_int|59940
comma
l_int|193800
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2584
comma
l_int|1920
comma
l_int|2584
comma
l_int|1984
comma
l_int|2240
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1203
comma
l_int|1206
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|29
comma
l_int|4
comma
l_int|0
)brace
comma
(brace
id|DBE_VT_1920_1200_66
comma
multiline_comment|/* flags,  width,          height,         fields_sec,     cfreq */
l_int|0
comma
l_int|1920
comma
l_int|1200
comma
l_int|66000
comma
l_int|213180
comma
multiline_comment|/* htotal, hblank_start,   hblank_end,     hsync_start,    hsync_end */
l_int|2584
comma
l_int|1920
comma
l_int|2584
comma
l_int|1984
comma
l_int|2240
comma
multiline_comment|/* vtotal, vblank_start,   vblank_end,     vsync_start,    vsync_end */
l_int|1250
comma
l_int|1200
comma
l_int|1250
comma
l_int|1203
comma
l_int|1206
comma
multiline_comment|/* pll_m,  pll_n,          pll_p */
l_int|8
comma
l_int|1
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|DBE_VT_SIZE
mdefine_line|#define DBE_VT_SIZE  (sizeof(dbeVTimings)/sizeof(dbeVTimings[0]))
macro_line|#endif 
singleline_comment|// INCLUDE_TIMING_TABLE_DATA
macro_line|#endif 
singleline_comment|// ! __SGIVWFB_H__
eof
