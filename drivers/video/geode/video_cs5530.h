multiline_comment|/*&n; * drivers/video/geode/video_cs5530.h&n; *   -- CS5530 video device&n; *&n; * Copyright (C) 2005 Arcom Control Systems Ltd.&n; *&n; * Based on AMD&squot;s original 2.4 driver:&n; *   Copyright (C) 2004 Advanced Micro Devices, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#ifndef __VIDEO_CS5530_H__
DECL|macro|__VIDEO_CS5530_H__
mdefine_line|#define __VIDEO_CS5530_H__
r_extern
r_struct
id|geode_vid_ops
id|cs5530_vid_ops
suffix:semicolon
multiline_comment|/* CS5530 Video device registers */
DECL|macro|CS5530_VIDEO_CONFIG
mdefine_line|#define CS5530_VIDEO_CONFIG&t;0x0000
DECL|macro|CS5530_VCFG_VID_EN
macro_line|#  define CS5530_VCFG_VID_EN&t;&t;&t;0x00000001
DECL|macro|CS5530_VCFG_VID_REG_UPDATE
macro_line|#  define CS5530_VCFG_VID_REG_UPDATE&t;&t;0x00000002
DECL|macro|CS5530_VCFG_VID_INP_FORMAT
macro_line|#  define CS5530_VCFG_VID_INP_FORMAT&t;&t;0x0000000C
DECL|macro|CS5530_VCFG_8_BIT_4_2_0
macro_line|#  define CS5530_VCFG_8_BIT_4_2_0&t;&t;0x00000004
DECL|macro|CS5530_VCFG_16_BIT_4_2_0
macro_line|#  define CS5530_VCFG_16_BIT_4_2_0&t;&t;0x00000008
DECL|macro|CS5530_VCFG_GV_SEL
macro_line|#  define CS5530_VCFG_GV_SEL&t;&t;&t;0x00000010
DECL|macro|CS5530_VCFG_CSC_BYPASS
macro_line|#  define CS5530_VCFG_CSC_BYPASS&t;&t;0x00000020
DECL|macro|CS5530_VCFG_X_FILTER_EN
macro_line|#  define CS5530_VCFG_X_FILTER_EN&t;&t;0x00000040
DECL|macro|CS5530_VCFG_Y_FILTER_EN
macro_line|#  define CS5530_VCFG_Y_FILTER_EN&t;&t;0x00000080
DECL|macro|CS5530_VCFG_LINE_SIZE_LOWER_MASK
macro_line|#  define CS5530_VCFG_LINE_SIZE_LOWER_MASK&t;0x0000FF00
DECL|macro|CS5530_VCFG_INIT_READ_MASK
macro_line|#  define CS5530_VCFG_INIT_READ_MASK&t;&t;0x01FF0000
DECL|macro|CS5530_VCFG_EARLY_VID_RDY
macro_line|#  define CS5530_VCFG_EARLY_VID_RDY&t;&t;0x02000000
DECL|macro|CS5530_VCFG_LINE_SIZE_UPPER
macro_line|#  define CS5530_VCFG_LINE_SIZE_UPPER&t;&t;0x08000000
DECL|macro|CS5530_VCFG_4_2_0_MODE
macro_line|#  define CS5530_VCFG_4_2_0_MODE&t;&t;0x10000000
DECL|macro|CS5530_VCFG_16_BIT_EN
macro_line|#  define CS5530_VCFG_16_BIT_EN&t;&t;&t;0x20000000
DECL|macro|CS5530_VCFG_HIGH_SPD_INT
macro_line|#  define CS5530_VCFG_HIGH_SPD_INT&t;&t;0x40000000
DECL|macro|CS5530_DISPLAY_CONFIG
mdefine_line|#define CS5530_DISPLAY_CONFIG&t;0x0004
DECL|macro|CS5530_DCFG_DIS_EN
macro_line|#  define CS5530_DCFG_DIS_EN&t;&t;&t;0x00000001
DECL|macro|CS5530_DCFG_HSYNC_EN
macro_line|#  define CS5530_DCFG_HSYNC_EN&t;&t;&t;0x00000002
DECL|macro|CS5530_DCFG_VSYNC_EN
macro_line|#  define CS5530_DCFG_VSYNC_EN&t;&t;&t;0x00000004
DECL|macro|CS5530_DCFG_DAC_BL_EN
macro_line|#  define CS5530_DCFG_DAC_BL_EN&t;&t;&t;0x00000008
DECL|macro|CS5530_DCFG_DAC_PWR_EN
macro_line|#  define CS5530_DCFG_DAC_PWR_EN&t;&t;0x00000020
DECL|macro|CS5530_DCFG_FP_PWR_EN
macro_line|#  define CS5530_DCFG_FP_PWR_EN&t;&t;&t;0x00000040
DECL|macro|CS5530_DCFG_FP_DATA_EN
macro_line|#  define CS5530_DCFG_FP_DATA_EN&t;&t;0x00000080
DECL|macro|CS5530_DCFG_CRT_HSYNC_POL
macro_line|#  define CS5530_DCFG_CRT_HSYNC_POL&t;&t;0x00000100
DECL|macro|CS5530_DCFG_CRT_VSYNC_POL
macro_line|#  define CS5530_DCFG_CRT_VSYNC_POL&t;&t;0x00000200
DECL|macro|CS5530_DCFG_FP_HSYNC_POL
macro_line|#  define CS5530_DCFG_FP_HSYNC_POL&t;&t;0x00000400
DECL|macro|CS5530_DCFG_FP_VSYNC_POL
macro_line|#  define CS5530_DCFG_FP_VSYNC_POL&t;&t;0x00000800
DECL|macro|CS5530_DCFG_XGA_FP
macro_line|#  define CS5530_DCFG_XGA_FP&t;&t;&t;0x00001000
DECL|macro|CS5530_DCFG_FP_DITH_EN
macro_line|#  define CS5530_DCFG_FP_DITH_EN&t;&t;0x00002000
DECL|macro|CS5530_DCFG_CRT_SYNC_SKW_MASK
macro_line|#  define CS5530_DCFG_CRT_SYNC_SKW_MASK&t;&t;0x0001C000
DECL|macro|CS5530_DCFG_CRT_SYNC_SKW_INIT
macro_line|#  define CS5530_DCFG_CRT_SYNC_SKW_INIT&t;&t;0x00010000
DECL|macro|CS5530_DCFG_PWR_SEQ_DLY_MASK
macro_line|#  define CS5530_DCFG_PWR_SEQ_DLY_MASK&t;&t;0x000E0000
DECL|macro|CS5530_DCFG_PWR_SEQ_DLY_INIT
macro_line|#  define CS5530_DCFG_PWR_SEQ_DLY_INIT&t;&t;0x00080000
DECL|macro|CS5530_DCFG_VG_CK
macro_line|#  define CS5530_DCFG_VG_CK&t;&t;&t;0x00100000
DECL|macro|CS5530_DCFG_GV_PAL_BYP
macro_line|#  define CS5530_DCFG_GV_PAL_BYP&t;&t;0x00200000
DECL|macro|CS5530_DCFG_DDC_SCL
macro_line|#  define CS5530_DCFG_DDC_SCL&t;&t;&t;0x00400000
DECL|macro|CS5530_DCFG_DDC_SDA
macro_line|#  define CS5530_DCFG_DDC_SDA&t;&t;&t;0x00800000
DECL|macro|CS5530_DCFG_DDC_OE
macro_line|#  define CS5530_DCFG_DDC_OE&t;&t;&t;0x01000000
DECL|macro|CS5530_DCFG_16_BIT_EN
macro_line|#  define CS5530_DCFG_16_BIT_EN&t;&t;&t;0x02000000
DECL|macro|CS5530_VIDEO_X_POS
mdefine_line|#define CS5530_VIDEO_X_POS&t;0x0008
DECL|macro|CS5530_VIDEO_Y_POS
mdefine_line|#define CS5530_VIDEO_Y_POS&t;0x000C
DECL|macro|CS5530_VIDEO_SCALE
mdefine_line|#define CS5530_VIDEO_SCALE&t;0x0010
DECL|macro|CS5530_VIDEO_COLOR_KEY
mdefine_line|#define CS5530_VIDEO_COLOR_KEY&t;0x0014
DECL|macro|CS5530_VIDEO_COLOR_MASK
mdefine_line|#define CS5530_VIDEO_COLOR_MASK 0x0018
DECL|macro|CS5530_PALETTE_ADDRESS
mdefine_line|#define CS5530_PALETTE_ADDRESS&t;0x001C
DECL|macro|CS5530_PALETTE_DATA
mdefine_line|#define CS5530_PALETTE_DATA&t;0x0020
DECL|macro|CS5530_DOT_CLK_CONFIG
mdefine_line|#define CS5530_DOT_CLK_CONFIG&t;0x0024
DECL|macro|CS5530_CRCSIG_TFT_TV
mdefine_line|#define CS5530_CRCSIG_TFT_TV&t;0x0028
macro_line|#endif /* !__VIDEO_CS5530_H__ */
eof
