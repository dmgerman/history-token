DECL|macro|NULL
mdefine_line|#define NULL 0
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
suffix:semicolon
DECL|struct|screen_info
r_struct
id|screen_info
(brace
DECL|member|orig_x
r_int
r_char
id|orig_x
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|orig_y
r_int
r_char
id|orig_y
suffix:semicolon
multiline_comment|/* 0x01 */
DECL|member|dontuse1
r_int
r_int
id|dontuse1
suffix:semicolon
multiline_comment|/* 0x02 -- EXT_MEM_K sits here */
DECL|member|orig_video_page
r_int
r_int
id|orig_video_page
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|orig_video_mode
r_int
r_char
id|orig_video_mode
suffix:semicolon
multiline_comment|/* 0x06 */
DECL|member|orig_video_cols
r_int
r_char
id|orig_video_cols
suffix:semicolon
multiline_comment|/* 0x07 */
DECL|member|unused2
r_int
r_int
id|unused2
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|orig_video_ega_bx
r_int
r_int
id|orig_video_ega_bx
suffix:semicolon
multiline_comment|/* 0x0a */
DECL|member|unused3
r_int
r_int
id|unused3
suffix:semicolon
multiline_comment|/* 0x0c */
DECL|member|orig_video_lines
r_int
r_char
id|orig_video_lines
suffix:semicolon
multiline_comment|/* 0x0e */
DECL|member|orig_video_isVGA
r_int
r_char
id|orig_video_isVGA
suffix:semicolon
multiline_comment|/* 0x0f */
DECL|member|orig_video_points
r_int
r_int
id|orig_video_points
suffix:semicolon
multiline_comment|/* 0x10 */
multiline_comment|/* VESA graphic mode -- linear frame buffer */
DECL|member|lfb_width
r_int
r_int
id|lfb_width
suffix:semicolon
multiline_comment|/* 0x12 */
DECL|member|lfb_height
r_int
r_int
id|lfb_height
suffix:semicolon
multiline_comment|/* 0x14 */
DECL|member|lfb_depth
r_int
r_int
id|lfb_depth
suffix:semicolon
multiline_comment|/* 0x16 */
DECL|member|lfb_base
r_int
r_int
id|lfb_base
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|lfb_size
r_int
r_int
id|lfb_size
suffix:semicolon
multiline_comment|/* 0x1c */
DECL|member|dontuse2
DECL|member|dontuse3
r_int
r_int
id|dontuse2
comma
id|dontuse3
suffix:semicolon
multiline_comment|/* 0x20 -- CL_MAGIC and CL_OFFSET here */
DECL|member|lfb_linelength
r_int
r_int
id|lfb_linelength
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|red_size
r_int
r_char
id|red_size
suffix:semicolon
multiline_comment|/* 0x26 */
DECL|member|red_pos
r_int
r_char
id|red_pos
suffix:semicolon
multiline_comment|/* 0x27 */
DECL|member|green_size
r_int
r_char
id|green_size
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|green_pos
r_int
r_char
id|green_pos
suffix:semicolon
multiline_comment|/* 0x29 */
DECL|member|blue_size
r_int
r_char
id|blue_size
suffix:semicolon
multiline_comment|/* 0x2a */
DECL|member|blue_pos
r_int
r_char
id|blue_pos
suffix:semicolon
multiline_comment|/* 0x2b */
DECL|member|rsvd_size
r_int
r_char
id|rsvd_size
suffix:semicolon
multiline_comment|/* 0x2c */
DECL|member|rsvd_pos
r_int
r_char
id|rsvd_pos
suffix:semicolon
multiline_comment|/* 0x2d */
DECL|member|vesapm_seg
r_int
r_int
id|vesapm_seg
suffix:semicolon
multiline_comment|/* 0x2e */
DECL|member|vesapm_off
r_int
r_int
id|vesapm_off
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|pages
r_int
r_int
id|pages
suffix:semicolon
multiline_comment|/* 0x32 */
multiline_comment|/* 0x34 -- 0x3f reserved for future expansion */
)brace
suffix:semicolon
eof
