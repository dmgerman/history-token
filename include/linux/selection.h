multiline_comment|/*&n; * selection.h&n; *&n; * Interface between console.c, tty_io.c, vt.c, vc_screen.c and selection.c&n; */
macro_line|#ifndef _LINUX_SELECTION_H_
DECL|macro|_LINUX_SELECTION_H_
mdefine_line|#define _LINUX_SELECTION_H_
macro_line|#include &lt;linux/tiocl.h&gt;
macro_line|#include &lt;linux/vt_buffer.h&gt;
r_extern
r_struct
id|vc_data
op_star
id|sel_cons
suffix:semicolon
r_extern
r_void
id|clear_selection
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|set_selection
c_func
(paren
r_const
r_struct
id|tiocl_selection
id|__user
op_star
id|sel
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|paste_selection
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|sel_loadlut
c_func
(paren
r_char
id|__user
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|mouse_reporting
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mouse_report
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|butt
comma
r_int
id|mrx
comma
r_int
id|mry
)paren
suffix:semicolon
r_extern
r_int
id|console_blanked
suffix:semicolon
r_extern
r_int
r_char
id|color_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_red
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_grn
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_blu
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
op_star
id|screen_pos
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|w_offset
comma
r_int
id|viewed
)paren
suffix:semicolon
r_extern
id|u16
id|screen_glyph
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
id|complement_pos
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
id|invert_screen
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
id|offset
comma
r_int
id|count
comma
r_int
id|shift
)paren
suffix:semicolon
r_extern
r_void
id|getconsxy
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
r_char
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|putconsxy
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_int
r_char
op_star
id|p
)paren
suffix:semicolon
r_extern
id|u16
id|vcs_scr_readw
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
r_const
id|u16
op_star
id|org
)paren
suffix:semicolon
r_extern
r_void
id|vcs_scr_writew
c_func
(paren
r_struct
id|vc_data
op_star
id|vc
comma
id|u16
id|val
comma
id|u16
op_star
id|org
)paren
suffix:semicolon
macro_line|#endif
eof
