multiline_comment|/*&n; *  linux/drivers/video/tgafb.h -- DEC 21030 TGA frame buffer device&n; *&n; *  &t;Copyright (C) 1999,2000 Martin Lucina, Tom Zerucha&n; *  &n; *  $Id: tgafb.h,v 1.4.2.3 2000/04/04 06:44:56 mato Exp $&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#ifndef TGAFB_H
DECL|macro|TGAFB_H
mdefine_line|#define TGAFB_H
multiline_comment|/*&n;     * TGA hardware description (minimal)&n;     */
DECL|macro|TGA_TYPE_8PLANE
mdefine_line|#define TGA_TYPE_8PLANE&t;&t;&t;0
DECL|macro|TGA_TYPE_24PLANE
mdefine_line|#define TGA_TYPE_24PLANE&t;&t;1
DECL|macro|TGA_TYPE_24PLUSZ
mdefine_line|#define TGA_TYPE_24PLUSZ&t;&t;3
multiline_comment|/*&n;     * Offsets within Memory Space&n;     */
DECL|macro|TGA_ROM_OFFSET
mdefine_line|#define&t;TGA_ROM_OFFSET&t;&t;&t;0x0000000
DECL|macro|TGA_REGS_OFFSET
mdefine_line|#define&t;TGA_REGS_OFFSET&t;&t;&t;0x0100000
DECL|macro|TGA_8PLANE_FB_OFFSET
mdefine_line|#define&t;TGA_8PLANE_FB_OFFSET&t;&t;0x0200000
DECL|macro|TGA_24PLANE_FB_OFFSET
mdefine_line|#define&t;TGA_24PLANE_FB_OFFSET&t;&t;0x0804000
DECL|macro|TGA_24PLUSZ_FB_OFFSET
mdefine_line|#define&t;TGA_24PLUSZ_FB_OFFSET&t;&t;0x1004000
DECL|macro|TGA_PLANEMASK_REG
mdefine_line|#define&t;TGA_PLANEMASK_REG&t;&t;0x0028
DECL|macro|TGA_MODE_REG
mdefine_line|#define&t;TGA_MODE_REG&t;&t;&t;0x0030
DECL|macro|TGA_RASTEROP_REG
mdefine_line|#define&t;TGA_RASTEROP_REG&t;&t;0x0034
DECL|macro|TGA_PIXELSHIFT_REG
mdefine_line|#define&t;TGA_PIXELSHIFT_REG&t;&t;0x0038
DECL|macro|TGA_DEEP_REG
mdefine_line|#define&t;TGA_DEEP_REG&t;&t;&t;0x0050
DECL|macro|TGA_PIXELMASK_REG
mdefine_line|#define&t;TGA_PIXELMASK_REG&t;&t;0x005c
DECL|macro|TGA_CURSOR_BASE_REG
mdefine_line|#define&t;TGA_CURSOR_BASE_REG&t;&t;0x0060
DECL|macro|TGA_HORIZ_REG
mdefine_line|#define&t;TGA_HORIZ_REG&t;&t;&t;0x0064
DECL|macro|TGA_VERT_REG
mdefine_line|#define&t;TGA_VERT_REG&t;&t;&t;0x0068
DECL|macro|TGA_BASE_ADDR_REG
mdefine_line|#define&t;TGA_BASE_ADDR_REG&t;&t;0x006c
DECL|macro|TGA_VALID_REG
mdefine_line|#define&t;TGA_VALID_REG&t;&t;&t;0x0070
DECL|macro|TGA_CURSOR_XY_REG
mdefine_line|#define&t;TGA_CURSOR_XY_REG&t;&t;0x0074
DECL|macro|TGA_INTR_STAT_REG
mdefine_line|#define&t;TGA_INTR_STAT_REG&t;&t;0x007c
DECL|macro|TGA_RAMDAC_SETUP_REG
mdefine_line|#define&t;TGA_RAMDAC_SETUP_REG&t;&t;0x00c0
DECL|macro|TGA_BLOCK_COLOR0_REG
mdefine_line|#define&t;TGA_BLOCK_COLOR0_REG&t;&t;0x0140
DECL|macro|TGA_BLOCK_COLOR1_REG
mdefine_line|#define&t;TGA_BLOCK_COLOR1_REG&t;&t;0x0144
DECL|macro|TGA_CLOCK_REG
mdefine_line|#define&t;TGA_CLOCK_REG&t;&t;&t;0x01e8
DECL|macro|TGA_RAMDAC_REG
mdefine_line|#define&t;TGA_RAMDAC_REG&t;&t;&t;0x01f0
DECL|macro|TGA_CMD_STAT_REG
mdefine_line|#define&t;TGA_CMD_STAT_REG&t;&t;0x01f8
multiline_comment|/* &n;     * useful defines for managing the registers&n;     */
DECL|macro|TGA_HORIZ_ODD
mdefine_line|#define TGA_HORIZ_ODD&t;&t;&t;0x80000000
DECL|macro|TGA_HORIZ_POLARITY
mdefine_line|#define TGA_HORIZ_POLARITY&t;&t;0x40000000
DECL|macro|TGA_HORIZ_ACT_MSB
mdefine_line|#define TGA_HORIZ_ACT_MSB&t;&t;0x30000000
DECL|macro|TGA_HORIZ_BP
mdefine_line|#define TGA_HORIZ_BP&t;&t;&t;0x0fe00000
DECL|macro|TGA_HORIZ_SYNC
mdefine_line|#define TGA_HORIZ_SYNC&t;&t;&t;0x001fc000
DECL|macro|TGA_HORIZ_FP
mdefine_line|#define TGA_HORIZ_FP&t;&t;&t;0x00007c00
DECL|macro|TGA_HORIZ_ACT_LSB
mdefine_line|#define TGA_HORIZ_ACT_LSB&t;&t;0x000001ff
DECL|macro|TGA_VERT_SE
mdefine_line|#define TGA_VERT_SE&t;&t;&t;0x80000000
DECL|macro|TGA_VERT_POLARITY
mdefine_line|#define TGA_VERT_POLARITY&t;&t;0x40000000
DECL|macro|TGA_VERT_RESERVED
mdefine_line|#define TGA_VERT_RESERVED&t;&t;0x30000000
DECL|macro|TGA_VERT_BP
mdefine_line|#define TGA_VERT_BP&t;&t;&t;0x0fc00000
DECL|macro|TGA_VERT_SYNC
mdefine_line|#define TGA_VERT_SYNC&t;&t;&t;0x003f0000
DECL|macro|TGA_VERT_FP
mdefine_line|#define TGA_VERT_FP&t;&t;&t;0x0000f800
DECL|macro|TGA_VERT_ACTIVE
mdefine_line|#define TGA_VERT_ACTIVE&t;&t;&t;0x000007ff
DECL|macro|TGA_VALID_VIDEO
mdefine_line|#define TGA_VALID_VIDEO&t;&t;&t;0x01
DECL|macro|TGA_VALID_BLANK
mdefine_line|#define TGA_VALID_BLANK&t;&t;&t;0x02
DECL|macro|TGA_VALID_CURSOR
mdefine_line|#define TGA_VALID_CURSOR&t;&t;0x04
multiline_comment|/*&n;     * useful defines for managing the ICS1562 PLL clock&n;     */
DECL|macro|TGA_PLL_BASE_FREQ
mdefine_line|#define TGA_PLL_BASE_FREQ &t;&t;14318&t;&t;/* .18 */
DECL|macro|TGA_PLL_MAX_FREQ
mdefine_line|#define TGA_PLL_MAX_FREQ &t;&t;230000
multiline_comment|/*&n;     * useful defines for managing the BT485 on the 8-plane TGA&n;     */
DECL|macro|BT485_READ_BIT
mdefine_line|#define&t;BT485_READ_BIT&t;&t;&t;0x01
DECL|macro|BT485_WRITE_BIT
mdefine_line|#define&t;BT485_WRITE_BIT&t;&t;&t;0x00
DECL|macro|BT485_ADDR_PAL_WRITE
mdefine_line|#define&t;BT485_ADDR_PAL_WRITE&t;&t;0x00
DECL|macro|BT485_DATA_PAL
mdefine_line|#define&t;BT485_DATA_PAL&t;&t;&t;0x02
DECL|macro|BT485_PIXEL_MASK
mdefine_line|#define&t;BT485_PIXEL_MASK&t;&t;0x04
DECL|macro|BT485_ADDR_PAL_READ
mdefine_line|#define&t;BT485_ADDR_PAL_READ&t;&t;0x06
DECL|macro|BT485_ADDR_CUR_WRITE
mdefine_line|#define&t;BT485_ADDR_CUR_WRITE&t;&t;0x08
DECL|macro|BT485_DATA_CUR
mdefine_line|#define&t;BT485_DATA_CUR&t;&t;&t;0x0a
DECL|macro|BT485_CMD_0
mdefine_line|#define&t;BT485_CMD_0&t;&t;&t;0x0c
DECL|macro|BT485_ADDR_CUR_READ
mdefine_line|#define&t;BT485_ADDR_CUR_READ&t;&t;0x0e
DECL|macro|BT485_CMD_1
mdefine_line|#define&t;BT485_CMD_1&t;&t;&t;0x10
DECL|macro|BT485_CMD_2
mdefine_line|#define&t;BT485_CMD_2&t;&t;&t;0x12
DECL|macro|BT485_STATUS
mdefine_line|#define&t;BT485_STATUS&t;&t;&t;0x14
DECL|macro|BT485_CMD_3
mdefine_line|#define&t;BT485_CMD_3&t;&t;&t;0x14
DECL|macro|BT485_CUR_RAM
mdefine_line|#define&t;BT485_CUR_RAM&t;&t;&t;0x16
DECL|macro|BT485_CUR_LOW_X
mdefine_line|#define&t;BT485_CUR_LOW_X&t;&t;&t;0x18
DECL|macro|BT485_CUR_HIGH_X
mdefine_line|#define&t;BT485_CUR_HIGH_X&t;&t;0x1a
DECL|macro|BT485_CUR_LOW_Y
mdefine_line|#define&t;BT485_CUR_LOW_Y&t;&t;&t;0x1c
DECL|macro|BT485_CUR_HIGH_Y
mdefine_line|#define&t;BT485_CUR_HIGH_Y&t;&t;0x1e
multiline_comment|/*&n;     * useful defines for managing the BT463 on the 24-plane TGAs&n;     */
DECL|macro|BT463_ADDR_LO
mdefine_line|#define&t;BT463_ADDR_LO&t;&t;0x0
DECL|macro|BT463_ADDR_HI
mdefine_line|#define&t;BT463_ADDR_HI&t;&t;0x1
DECL|macro|BT463_REG_ACC
mdefine_line|#define&t;BT463_REG_ACC&t;&t;0x2
DECL|macro|BT463_PALETTE
mdefine_line|#define&t;BT463_PALETTE&t;&t;0x3
DECL|macro|BT463_CUR_CLR_0
mdefine_line|#define&t;BT463_CUR_CLR_0&t;&t;0x0100
DECL|macro|BT463_CUR_CLR_1
mdefine_line|#define&t;BT463_CUR_CLR_1&t;&t;0x0101
DECL|macro|BT463_CMD_REG_0
mdefine_line|#define&t;BT463_CMD_REG_0&t;&t;0x0201
DECL|macro|BT463_CMD_REG_1
mdefine_line|#define&t;BT463_CMD_REG_1&t;&t;0x0202
DECL|macro|BT463_CMD_REG_2
mdefine_line|#define&t;BT463_CMD_REG_2&t;&t;0x0203
DECL|macro|BT463_READ_MASK_0
mdefine_line|#define&t;BT463_READ_MASK_0&t;0x0205
DECL|macro|BT463_READ_MASK_1
mdefine_line|#define&t;BT463_READ_MASK_1&t;0x0206
DECL|macro|BT463_READ_MASK_2
mdefine_line|#define&t;BT463_READ_MASK_2&t;0x0207
DECL|macro|BT463_READ_MASK_3
mdefine_line|#define&t;BT463_READ_MASK_3&t;0x0208
DECL|macro|BT463_BLINK_MASK_0
mdefine_line|#define&t;BT463_BLINK_MASK_0&t;0x0209
DECL|macro|BT463_BLINK_MASK_1
mdefine_line|#define&t;BT463_BLINK_MASK_1&t;0x020a
DECL|macro|BT463_BLINK_MASK_2
mdefine_line|#define&t;BT463_BLINK_MASK_2&t;0x020b
DECL|macro|BT463_BLINK_MASK_3
mdefine_line|#define&t;BT463_BLINK_MASK_3&t;0x020c
DECL|macro|BT463_WINDOW_TYPE_BASE
mdefine_line|#define&t;BT463_WINDOW_TYPE_BASE&t;0x0300
multiline_comment|/*&n;     * Macros for reading/writing TGA and RAMDAC registers&n;     */
DECL|macro|TGA_WRITE_REG
mdefine_line|#define TGA_WRITE_REG(v,r) &bslash;&n;&t;{ writel((v), fb_info.tga_regs_base+(r)); mb(); }
DECL|macro|TGA_READ_REG
mdefine_line|#define TGA_READ_REG(r) readl(fb_info.tga_regs_base+(r))
DECL|macro|BT485_WRITE
mdefine_line|#define BT485_WRITE(v,r) &bslash;&n;&t;  TGA_WRITE_REG((r),TGA_RAMDAC_SETUP_REG);&t;&t;&bslash;&n;&t;  TGA_WRITE_REG(((v)&amp;0xff)|((r)&lt;&lt;8),TGA_RAMDAC_REG);
DECL|macro|BT463_LOAD_ADDR
mdefine_line|#define BT463_LOAD_ADDR(a) &bslash;&n;&t;TGA_WRITE_REG(BT463_ADDR_LO&lt;&lt;2, TGA_RAMDAC_SETUP_REG); &bslash;&n;&t;TGA_WRITE_REG((BT463_ADDR_LO&lt;&lt;10)|((a)&amp;0xff), TGA_RAMDAC_REG); &bslash;&n;&t;TGA_WRITE_REG(BT463_ADDR_HI&lt;&lt;2, TGA_RAMDAC_SETUP_REG); &bslash;&n;&t;TGA_WRITE_REG((BT463_ADDR_HI&lt;&lt;10)|(((a)&gt;&gt;8)&amp;0xff), TGA_RAMDAC_REG);
DECL|macro|BT463_WRITE
mdefine_line|#define BT463_WRITE(m,a,v) &bslash;&n;&t;BT463_LOAD_ADDR((a)); &bslash;&n;&t;TGA_WRITE_REG(((m)&lt;&lt;2),TGA_RAMDAC_SETUP_REG); &bslash;&n;&t;TGA_WRITE_REG(((m)&lt;&lt;10)|((v)&amp;0xff),TGA_RAMDAC_REG);
multiline_comment|/*&n;     *  This structure describes the board.&n;     */
DECL|struct|tgafb_info
r_struct
id|tgafb_info
(brace
multiline_comment|/* Use the generic framebuffer ops */
DECL|member|gen
r_struct
id|fb_info_gen
id|gen
suffix:semicolon
multiline_comment|/* Device dependent information */
DECL|member|tga_type
id|u8
id|tga_type
suffix:semicolon
multiline_comment|/* TGA_TYPE_XXX */
DECL|member|tga_chip_rev
id|u8
id|tga_chip_rev
suffix:semicolon
multiline_comment|/* dc21030 revision */
DECL|member|tga_mem_base
id|u64
id|tga_mem_base
suffix:semicolon
DECL|member|tga_fb_base
id|u64
id|tga_fb_base
suffix:semicolon
DECL|member|tga_regs_base
id|u64
id|tga_regs_base
suffix:semicolon
DECL|member|default_var
r_struct
id|fb_var_screeninfo
id|default_var
suffix:semicolon
multiline_comment|/* default video mode */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  This structure uniquely defines a video mode.&n;     */
DECL|struct|tgafb_par
r_struct
id|tgafb_par
(brace
DECL|member|xres
DECL|member|yres
id|u32
id|xres
comma
id|yres
suffix:semicolon
multiline_comment|/* resolution in pixels */
DECL|member|htimings
id|u32
id|htimings
suffix:semicolon
multiline_comment|/* horizontal timing register */
DECL|member|vtimings
id|u32
id|vtimings
suffix:semicolon
multiline_comment|/* vertical timing register */
DECL|member|pll_freq
id|u32
id|pll_freq
suffix:semicolon
multiline_comment|/* pixclock in mhz */
DECL|member|bits_per_pixel
id|u32
id|bits_per_pixel
suffix:semicolon
multiline_comment|/* bits per pixel */
DECL|member|sync_on_green
id|u32
id|sync_on_green
suffix:semicolon
multiline_comment|/* set if sync is on green */
)brace
suffix:semicolon
macro_line|#endif /* TGAFB_H */
eof
