DECL|macro|cons_num
mdefine_line|#define cons_num&t;(vc_cons[currcons].d-&gt;vc_num)
DECL|macro|sw
mdefine_line|#define sw&t;&t;(vc_cons[currcons].d-&gt;vc_sw)
DECL|macro|screenbuf
mdefine_line|#define screenbuf&t;(vc_cons[currcons].d-&gt;vc_screenbuf)
DECL|macro|screenbuf_size
mdefine_line|#define screenbuf_size&t;(vc_cons[currcons].d-&gt;vc_screenbuf_size)
DECL|macro|origin
mdefine_line|#define origin&t;&t;(vc_cons[currcons].d-&gt;vc_origin)
DECL|macro|scr_top
mdefine_line|#define scr_top&t;&t;(vc_cons[currcons].d-&gt;vc_scr_top)
DECL|macro|visible_origin
mdefine_line|#define visible_origin  (vc_cons[currcons].d-&gt;vc_visible_origin)
DECL|macro|scr_end
mdefine_line|#define scr_end&t;&t;(vc_cons[currcons].d-&gt;vc_scr_end)
DECL|macro|pos
mdefine_line|#define pos&t;&t;(vc_cons[currcons].d-&gt;vc_pos)
DECL|macro|top
mdefine_line|#define top&t;&t;(vc_cons[currcons].d-&gt;vc_top)
DECL|macro|bottom
mdefine_line|#define bottom&t;&t;(vc_cons[currcons].d-&gt;vc_bottom)
DECL|macro|x
mdefine_line|#define x&t;&t;(vc_cons[currcons].d-&gt;vc_x)
DECL|macro|y
mdefine_line|#define y&t;&t;(vc_cons[currcons].d-&gt;vc_y)
DECL|macro|vc_state
mdefine_line|#define vc_state&t;(vc_cons[currcons].d-&gt;vc_state)
DECL|macro|npar
mdefine_line|#define npar&t;&t;(vc_cons[currcons].d-&gt;vc_npar)
DECL|macro|par
mdefine_line|#define par&t;&t;(vc_cons[currcons].d-&gt;vc_par)
DECL|macro|ques
mdefine_line|#define ques&t;&t;(vc_cons[currcons].d-&gt;vc_ques)
DECL|macro|attr
mdefine_line|#define attr&t;&t;(vc_cons[currcons].d-&gt;vc_attr)
DECL|macro|saved_x
mdefine_line|#define saved_x&t;&t;(vc_cons[currcons].d-&gt;vc_saved_x)
DECL|macro|saved_y
mdefine_line|#define saved_y&t;&t;(vc_cons[currcons].d-&gt;vc_saved_y)
DECL|macro|translate
mdefine_line|#define translate&t;(vc_cons[currcons].d-&gt;vc_translate)
DECL|macro|G0_charset
mdefine_line|#define G0_charset&t;(vc_cons[currcons].d-&gt;vc_G0_charset)
DECL|macro|G1_charset
mdefine_line|#define G1_charset&t;(vc_cons[currcons].d-&gt;vc_G1_charset)
DECL|macro|saved_G0
mdefine_line|#define saved_G0&t;(vc_cons[currcons].d-&gt;vc_saved_G0)
DECL|macro|saved_G1
mdefine_line|#define saved_G1&t;(vc_cons[currcons].d-&gt;vc_saved_G1)
DECL|macro|utf
mdefine_line|#define utf&t;&t;(vc_cons[currcons].d-&gt;vc_utf)
DECL|macro|utf_count
mdefine_line|#define utf_count&t;(vc_cons[currcons].d-&gt;vc_utf_count)
DECL|macro|utf_char
mdefine_line|#define utf_char&t;(vc_cons[currcons].d-&gt;vc_utf_char)
DECL|macro|video_erase_char
mdefine_line|#define video_erase_char (vc_cons[currcons].d-&gt;vc_video_erase_char)
DECL|macro|disp_ctrl
mdefine_line|#define disp_ctrl&t;(vc_cons[currcons].d-&gt;vc_disp_ctrl)
DECL|macro|toggle_meta
mdefine_line|#define toggle_meta&t;(vc_cons[currcons].d-&gt;vc_toggle_meta)
DECL|macro|decscnm
mdefine_line|#define decscnm&t;&t;(vc_cons[currcons].d-&gt;vc_decscnm)
DECL|macro|decom
mdefine_line|#define decom&t;&t;(vc_cons[currcons].d-&gt;vc_decom)
DECL|macro|decawm
mdefine_line|#define decawm&t;&t;(vc_cons[currcons].d-&gt;vc_decawm)
DECL|macro|deccm
mdefine_line|#define deccm&t;&t;(vc_cons[currcons].d-&gt;vc_deccm)
DECL|macro|decim
mdefine_line|#define decim&t;&t;(vc_cons[currcons].d-&gt;vc_decim)
DECL|macro|deccolm
mdefine_line|#define deccolm&t;&t;(vc_cons[currcons].d-&gt;vc_deccolm)
DECL|macro|need_wrap
mdefine_line|#define need_wrap&t;(vc_cons[currcons].d-&gt;vc_need_wrap)
DECL|macro|kmalloced
mdefine_line|#define kmalloced&t;(vc_cons[currcons].d-&gt;vc_kmalloced)
DECL|macro|report_mouse
mdefine_line|#define report_mouse&t;(vc_cons[currcons].d-&gt;vc_report_mouse)
DECL|macro|color
mdefine_line|#define color&t;&t;(vc_cons[currcons].d-&gt;vc_color)
DECL|macro|s_color
mdefine_line|#define s_color&t;&t;(vc_cons[currcons].d-&gt;vc_s_color)
DECL|macro|def_color
mdefine_line|#define def_color&t;(vc_cons[currcons].d-&gt;vc_def_color)
DECL|macro|foreground
mdefine_line|#define foreground&t;(color &amp; 0x0f)
DECL|macro|background
mdefine_line|#define background&t;(color &amp; 0xf0)
DECL|macro|charset
mdefine_line|#define charset&t;&t;(vc_cons[currcons].d-&gt;vc_charset)
DECL|macro|s_charset
mdefine_line|#define s_charset&t;(vc_cons[currcons].d-&gt;vc_s_charset)
DECL|macro|intensity
mdefine_line|#define&t;intensity&t;(vc_cons[currcons].d-&gt;vc_intensity)
DECL|macro|underline
mdefine_line|#define&t;underline&t;(vc_cons[currcons].d-&gt;vc_underline)
DECL|macro|blink
mdefine_line|#define&t;blink&t;&t;(vc_cons[currcons].d-&gt;vc_blink)
DECL|macro|reverse
mdefine_line|#define&t;reverse&t;&t;(vc_cons[currcons].d-&gt;vc_reverse)
DECL|macro|s_intensity
mdefine_line|#define&t;s_intensity&t;(vc_cons[currcons].d-&gt;vc_s_intensity)
DECL|macro|s_underline
mdefine_line|#define&t;s_underline&t;(vc_cons[currcons].d-&gt;vc_s_underline)
DECL|macro|s_blink
mdefine_line|#define&t;s_blink&t;&t;(vc_cons[currcons].d-&gt;vc_s_blink)
DECL|macro|s_reverse
mdefine_line|#define&t;s_reverse&t;(vc_cons[currcons].d-&gt;vc_s_reverse)
DECL|macro|ulcolor
mdefine_line|#define&t;ulcolor&t;&t;(vc_cons[currcons].d-&gt;vc_ulcolor)
DECL|macro|halfcolor
mdefine_line|#define&t;halfcolor&t;(vc_cons[currcons].d-&gt;vc_halfcolor)
DECL|macro|tab_stop
mdefine_line|#define tab_stop&t;(vc_cons[currcons].d-&gt;vc_tab_stop)
DECL|macro|palette
mdefine_line|#define palette&t;&t;(vc_cons[currcons].d-&gt;vc_palette)
DECL|macro|bell_pitch
mdefine_line|#define bell_pitch&t;(vc_cons[currcons].d-&gt;vc_bell_pitch)
DECL|macro|bell_duration
mdefine_line|#define bell_duration&t;(vc_cons[currcons].d-&gt;vc_bell_duration)
DECL|macro|cursor_type
mdefine_line|#define cursor_type&t;(vc_cons[currcons].d-&gt;vc_cursor_type)
DECL|macro|display_fg
mdefine_line|#define display_fg&t;(vc_cons[currcons].d-&gt;vc_display_fg)
DECL|macro|complement_mask
mdefine_line|#define complement_mask (vc_cons[currcons].d-&gt;vc_complement_mask)
DECL|macro|s_complement_mask
mdefine_line|#define s_complement_mask (vc_cons[currcons].d-&gt;vc_s_complement_mask)
DECL|macro|hi_font_mask
mdefine_line|#define hi_font_mask&t;(vc_cons[currcons].d-&gt;vc_hi_font_mask)
DECL|macro|vcmode
mdefine_line|#define vcmode&t;&t;(vt_cons[currcons]-&gt;vc_mode)
DECL|macro|structsize
mdefine_line|#define structsize&t;(sizeof(struct vc_data) + sizeof(struct vt_struct))
eof
