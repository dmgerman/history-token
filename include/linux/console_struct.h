multiline_comment|/*&n; * console_struct.h&n; *&n; * Data structure describing single virtual console except for data&n; * used by vt.c.&n; *&n; * Fields marked with [#] must be set by the low-level driver.&n; * Fields marked with [!] can be changed by the low-level driver&n; * to achieve effects such as fast scrolling by changing the origin.&n; */
DECL|macro|NPAR
mdefine_line|#define NPAR 16
DECL|struct|vc_data
r_struct
id|vc_data
(brace
DECL|member|vc_num
r_int
r_int
id|vc_num
suffix:semicolon
multiline_comment|/* Console number */
DECL|member|vc_cols
r_int
r_int
id|vc_cols
suffix:semicolon
multiline_comment|/* [#] Console size */
DECL|member|vc_rows
r_int
r_int
id|vc_rows
suffix:semicolon
DECL|member|vc_size_row
r_int
r_int
id|vc_size_row
suffix:semicolon
multiline_comment|/* Bytes per row */
DECL|member|vc_sw
r_const
r_struct
id|consw
op_star
id|vc_sw
suffix:semicolon
DECL|member|vc_screenbuf
r_int
r_int
op_star
id|vc_screenbuf
suffix:semicolon
multiline_comment|/* In-memory character/attribute buffer */
DECL|member|vc_screenbuf_size
r_int
r_int
id|vc_screenbuf_size
suffix:semicolon
DECL|member|vc_attr
r_int
r_char
id|vc_attr
suffix:semicolon
multiline_comment|/* Current attributes */
DECL|member|vc_def_color
r_int
r_char
id|vc_def_color
suffix:semicolon
multiline_comment|/* Default colors */
DECL|member|vc_color
r_int
r_char
id|vc_color
suffix:semicolon
multiline_comment|/* Foreground &amp; background */
DECL|member|vc_s_color
r_int
r_char
id|vc_s_color
suffix:semicolon
multiline_comment|/* Saved foreground &amp; background */
DECL|member|vc_ulcolor
r_int
r_char
id|vc_ulcolor
suffix:semicolon
multiline_comment|/* Color for underline mode */
DECL|member|vc_halfcolor
r_int
r_char
id|vc_halfcolor
suffix:semicolon
multiline_comment|/* Color for half intensity mode */
DECL|member|vc_complement_mask
r_int
r_int
id|vc_complement_mask
suffix:semicolon
multiline_comment|/* [#] Xor mask for mouse pointer */
DECL|member|vc_hi_font_mask
r_int
r_int
id|vc_hi_font_mask
suffix:semicolon
multiline_comment|/* [#] Attribute set for upper 256 chars of font or 0 if not supported */
DECL|member|vc_video_erase_char
r_int
r_int
id|vc_video_erase_char
suffix:semicolon
multiline_comment|/* Background erase character */
DECL|member|vc_s_complement_mask
r_int
r_int
id|vc_s_complement_mask
suffix:semicolon
multiline_comment|/* Saved mouse pointer mask */
DECL|member|vc_x
DECL|member|vc_y
r_int
r_int
id|vc_x
comma
id|vc_y
suffix:semicolon
multiline_comment|/* Cursor position */
DECL|member|vc_top
DECL|member|vc_bottom
r_int
r_int
id|vc_top
comma
id|vc_bottom
suffix:semicolon
multiline_comment|/* Scrolling region */
DECL|member|vc_state
r_int
r_int
id|vc_state
suffix:semicolon
multiline_comment|/* Escape sequence parser state */
DECL|member|vc_npar
DECL|member|vc_par
r_int
r_int
id|vc_npar
comma
id|vc_par
(braket
id|NPAR
)braket
suffix:semicolon
multiline_comment|/* Parameters of current escape sequence */
DECL|member|vc_origin
r_int
r_int
id|vc_origin
suffix:semicolon
multiline_comment|/* [!] Start of real screen */
DECL|member|vc_scr_end
r_int
r_int
id|vc_scr_end
suffix:semicolon
multiline_comment|/* [!] End of real screen */
DECL|member|vc_visible_origin
r_int
r_int
id|vc_visible_origin
suffix:semicolon
multiline_comment|/* [!] Top of visible window */
DECL|member|vc_pos
r_int
r_int
id|vc_pos
suffix:semicolon
multiline_comment|/* Cursor address */
DECL|member|vc_saved_x
r_int
r_int
id|vc_saved_x
suffix:semicolon
DECL|member|vc_saved_y
r_int
r_int
id|vc_saved_y
suffix:semicolon
multiline_comment|/* mode flags */
DECL|member|vc_charset
r_int
r_int
id|vc_charset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Character set G0 / G1 */
DECL|member|vc_s_charset
r_int
r_int
id|vc_s_charset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Saved character set */
DECL|member|vc_disp_ctrl
r_int
r_int
id|vc_disp_ctrl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Display chars &lt; 32? */
DECL|member|vc_toggle_meta
r_int
r_int
id|vc_toggle_meta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Toggle high bit? */
DECL|member|vc_decscnm
r_int
r_int
id|vc_decscnm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Screen Mode */
DECL|member|vc_decom
r_int
r_int
id|vc_decom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Origin Mode */
DECL|member|vc_decawm
r_int
r_int
id|vc_decawm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Autowrap Mode */
DECL|member|vc_deccm
r_int
r_int
id|vc_deccm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cursor Visible */
DECL|member|vc_decim
r_int
r_int
id|vc_decim
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Insert Mode */
DECL|member|vc_deccolm
r_int
r_int
id|vc_deccolm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 80/132 Column Mode */
multiline_comment|/* attribute flags */
DECL|member|vc_intensity
r_int
r_int
id|vc_intensity
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 0=half-bright, 1=normal, 2=bold */
DECL|member|vc_underline
r_int
r_int
id|vc_underline
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_blink
r_int
r_int
id|vc_blink
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_reverse
r_int
r_int
id|vc_reverse
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_intensity
r_int
r_int
id|vc_s_intensity
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* saved rendition */
DECL|member|vc_s_underline
r_int
r_int
id|vc_s_underline
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_blink
r_int
r_int
id|vc_s_blink
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_reverse
r_int
r_int
id|vc_s_reverse
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* misc */
DECL|member|vc_ques
r_int
r_int
id|vc_ques
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_need_wrap
r_int
r_int
id|vc_need_wrap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_can_do_color
r_int
r_int
id|vc_can_do_color
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_report_mouse
r_int
r_int
id|vc_report_mouse
suffix:colon
l_int|2
suffix:semicolon
DECL|member|vc_kmalloced
r_int
r_int
id|vc_kmalloced
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_utf
r_int
r_char
id|vc_utf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unicode UTF-8 encoding */
DECL|member|vc_utf_count
r_int
r_char
id|vc_utf_count
suffix:semicolon
DECL|member|vc_utf_char
r_int
id|vc_utf_char
suffix:semicolon
DECL|member|vc_tab_stop
r_int
r_int
id|vc_tab_stop
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Tab stops. 256 columns. */
DECL|member|vc_palette
r_int
r_char
id|vc_palette
(braket
l_int|16
op_star
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Colour palette for VGA+ */
DECL|member|vc_translate
r_int
r_int
op_star
id|vc_translate
suffix:semicolon
DECL|member|vc_G0_charset
r_int
r_char
id|vc_G0_charset
suffix:semicolon
DECL|member|vc_G1_charset
r_int
r_char
id|vc_G1_charset
suffix:semicolon
DECL|member|vc_saved_G0
r_int
r_char
id|vc_saved_G0
suffix:semicolon
DECL|member|vc_saved_G1
r_int
r_char
id|vc_saved_G1
suffix:semicolon
DECL|member|vc_bell_pitch
r_int
r_int
id|vc_bell_pitch
suffix:semicolon
multiline_comment|/* Console bell pitch */
DECL|member|vc_bell_duration
r_int
r_int
id|vc_bell_duration
suffix:semicolon
multiline_comment|/* Console bell duration */
DECL|member|vc_cursor_type
r_int
r_int
id|vc_cursor_type
suffix:semicolon
DECL|member|vc_display_fg
r_struct
id|vc_data
op_star
op_star
id|vc_display_fg
suffix:semicolon
multiline_comment|/* [!] Ptr to var holding fg console for this display */
DECL|member|vc_uni_pagedir
r_int
r_int
id|vc_uni_pagedir
suffix:semicolon
DECL|member|vc_uni_pagedir_loc
r_int
r_int
op_star
id|vc_uni_pagedir_loc
suffix:semicolon
multiline_comment|/* [!] Location of uni_pagedir variable for this console */
multiline_comment|/* additional information is in vt_kern.h */
)brace
suffix:semicolon
DECL|struct|vc
r_struct
id|vc
(brace
DECL|member|d
r_struct
id|vc_data
op_star
id|d
suffix:semicolon
multiline_comment|/* might add  scrmem, vt_struct, kbd  at some time,&n;&t;   to have everything in one place - the disadvantage&n;&t;   would be that vc_cons etc can no longer be static */
)brace
suffix:semicolon
r_extern
r_struct
id|vc
id|vc_cons
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
DECL|macro|CUR_DEF
mdefine_line|#define CUR_DEF&t;&t;0
DECL|macro|CUR_NONE
mdefine_line|#define CUR_NONE&t;1
DECL|macro|CUR_UNDERLINE
mdefine_line|#define CUR_UNDERLINE&t;2
DECL|macro|CUR_LOWER_THIRD
mdefine_line|#define CUR_LOWER_THIRD&t;3
DECL|macro|CUR_LOWER_HALF
mdefine_line|#define CUR_LOWER_HALF&t;4
DECL|macro|CUR_TWO_THIRDS
mdefine_line|#define CUR_TWO_THIRDS&t;5
DECL|macro|CUR_BLOCK
mdefine_line|#define CUR_BLOCK&t;6
DECL|macro|CUR_HWMASK
mdefine_line|#define CUR_HWMASK&t;0x0f
DECL|macro|CUR_SWMASK
mdefine_line|#define CUR_SWMASK&t;0xfff0
DECL|macro|CUR_DEFAULT
mdefine_line|#define CUR_DEFAULT CUR_UNDERLINE
DECL|macro|CON_IS_VISIBLE
mdefine_line|#define CON_IS_VISIBLE(conp) (*conp-&gt;vc_display_fg == conp)
eof
