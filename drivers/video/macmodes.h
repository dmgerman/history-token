multiline_comment|/*&n; *  linux/drivers/video/macmodes.h -- Standard MacOS video modes&n; *&n; *&t;Copyright (C) 1998 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#ifndef _VIDEO_MACMODES_H
DECL|macro|_VIDEO_MACMODES_H
mdefine_line|#define _VIDEO_MACMODES_H
multiline_comment|/*&n;     *  Video mode values.&n;     *  These are supposed to be the same as the values that Apple uses in&n;     *  MacOS.&n;     */
DECL|macro|VMODE_NVRAM
mdefine_line|#define VMODE_NVRAM&t;&t;0
DECL|macro|VMODE_512_384_60I
mdefine_line|#define VMODE_512_384_60I&t;1&t;/* 512x384, 60Hz interlaced (NTSC) */
DECL|macro|VMODE_512_384_60
mdefine_line|#define VMODE_512_384_60&t;2&t;/* 512x384, 60Hz */
DECL|macro|VMODE_640_480_50I
mdefine_line|#define VMODE_640_480_50I&t;3&t;/* 640x480, 50Hz interlaced (PAL) */
DECL|macro|VMODE_640_480_60I
mdefine_line|#define VMODE_640_480_60I&t;4&t;/* 640x480, 60Hz interlaced (NTSC) */
DECL|macro|VMODE_640_480_60
mdefine_line|#define VMODE_640_480_60&t;5&t;/* 640x480, 60Hz (VGA) */
DECL|macro|VMODE_640_480_67
mdefine_line|#define VMODE_640_480_67&t;6&t;/* 640x480, 67Hz */
DECL|macro|VMODE_640_870_75P
mdefine_line|#define VMODE_640_870_75P&t;7&t;/* 640x870, 75Hz (portrait) */
DECL|macro|VMODE_768_576_50I
mdefine_line|#define VMODE_768_576_50I&t;8&t;/* 768x576, 50Hz (PAL full frame) */
DECL|macro|VMODE_800_600_56
mdefine_line|#define VMODE_800_600_56&t;9&t;/* 800x600, 56Hz */
DECL|macro|VMODE_800_600_60
mdefine_line|#define VMODE_800_600_60&t;10&t;/* 800x600, 60Hz */
DECL|macro|VMODE_800_600_72
mdefine_line|#define VMODE_800_600_72&t;11&t;/* 800x600, 72Hz */
DECL|macro|VMODE_800_600_75
mdefine_line|#define VMODE_800_600_75&t;12&t;/* 800x600, 75Hz */
DECL|macro|VMODE_832_624_75
mdefine_line|#define VMODE_832_624_75&t;13&t;/* 832x624, 75Hz */
DECL|macro|VMODE_1024_768_60
mdefine_line|#define VMODE_1024_768_60&t;14&t;/* 1024x768, 60Hz */
DECL|macro|VMODE_1024_768_70
mdefine_line|#define VMODE_1024_768_70&t;15&t;/* 1024x768, 70Hz (or 72Hz?) */
DECL|macro|VMODE_1024_768_75V
mdefine_line|#define VMODE_1024_768_75V&t;16&t;/* 1024x768, 75Hz (VESA) */
DECL|macro|VMODE_1024_768_75
mdefine_line|#define VMODE_1024_768_75&t;17&t;/* 1024x768, 75Hz */
DECL|macro|VMODE_1152_870_75
mdefine_line|#define VMODE_1152_870_75&t;18&t;/* 1152x870, 75Hz */
DECL|macro|VMODE_1280_960_75
mdefine_line|#define VMODE_1280_960_75&t;19&t;/* 1280x960, 75Hz */
DECL|macro|VMODE_1280_1024_75
mdefine_line|#define VMODE_1280_1024_75&t;20&t;/* 1280x1024, 75Hz */
DECL|macro|VMODE_1152_768_60
mdefine_line|#define VMODE_1152_768_60&t;21&t;/* 1152x768, 60Hz     Titanium PowerBook */
DECL|macro|VMODE_1600_1024_60
mdefine_line|#define VMODE_1600_1024_60&t;22&t;/* 1600x1024, 60Hz 22&quot; Cinema Display */
DECL|macro|VMODE_MAX
mdefine_line|#define VMODE_MAX&t;&t;22
DECL|macro|VMODE_CHOOSE
mdefine_line|#define VMODE_CHOOSE&t;&t;99
DECL|macro|CMODE_NVRAM
mdefine_line|#define CMODE_NVRAM&t;&t;-1
DECL|macro|CMODE_CHOOSE
mdefine_line|#define CMODE_CHOOSE&t;&t;-2
DECL|macro|CMODE_8
mdefine_line|#define CMODE_8&t;&t;&t;0&t;/* 8 bits/pixel */
DECL|macro|CMODE_16
mdefine_line|#define CMODE_16&t;&t;1&t;/* 16 (actually 15) bits/pixel */
DECL|macro|CMODE_32
mdefine_line|#define CMODE_32&t;&t;2&t;/* 32 (actually 24) bits/pixel */
r_extern
r_int
id|mac_vmode_to_var
c_func
(paren
r_int
id|vmode
comma
r_int
id|cmode
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
suffix:semicolon
r_extern
r_int
id|mac_var_to_vmode
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
op_star
id|vmode
comma
r_int
op_star
id|cmode
)paren
suffix:semicolon
r_extern
r_int
id|mac_map_monitor_sense
c_func
(paren
r_int
id|sense
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|mac_find_mode
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
comma
r_const
r_char
op_star
id|mode_option
comma
r_int
r_int
id|default_bpp
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Addresses in NVRAM where video mode and pixel size are stored.&n;     */
DECL|macro|NV_VMODE
mdefine_line|#define NV_VMODE&t;&t;0x140f
DECL|macro|NV_CMODE
mdefine_line|#define NV_CMODE&t;&t;0x1410
macro_line|#endif /* _VIDEO_MACMODES_H */
eof
