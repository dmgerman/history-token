multiline_comment|/*&n; *  linux/drivers/video/dummycon.c -- A dummy console driver&n; *&n; *  To be used if there&squot;s no other console driver (e.g. for plain VGA text)&n; *  available, usually until fbcon takes console over.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; *  Dummy console driver&n; */
macro_line|#if defined(__arm__)
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;ORIG_VIDEO_COLS
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;ORIG_VIDEO_LINES
macro_line|#elif defined(__hppa__)
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;80&t;/* fixme ! (mine uses 160x64 at 1280x1024) */
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;25
macro_line|#else
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;80
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;25
macro_line|#endif
DECL|function|dummycon_startup
r_static
r_const
r_char
op_star
id|dummycon_startup
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;dummy device&quot;
suffix:semicolon
)brace
DECL|function|dummycon_init
r_static
r_void
id|dummycon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|init
)paren
(brace
id|conp-&gt;vc_can_do_color
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|init
)paren
(brace
id|conp-&gt;vc_cols
op_assign
id|DUMMY_COLUMNS
suffix:semicolon
id|conp-&gt;vc_rows
op_assign
id|DUMMY_ROWS
suffix:semicolon
)brace
r_else
id|vc_resize_con
c_func
(paren
id|DUMMY_ROWS
comma
id|DUMMY_COLUMNS
comma
id|conp-&gt;vc_num
)paren
suffix:semicolon
)brace
DECL|function|dummycon_dummy
r_static
r_int
id|dummycon_dummy
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DUMMY
mdefine_line|#define DUMMY&t;(void *)dummycon_dummy
multiline_comment|/*&n; *  The console `switch&squot; structure for the dummy console&n; *&n; *  Most of the operations are dummies.&n; */
DECL|variable|dummy_con
r_const
r_struct
id|consw
id|dummy_con
op_assign
(brace
id|con_startup
suffix:colon
id|dummycon_startup
comma
id|con_init
suffix:colon
id|dummycon_init
comma
id|con_deinit
suffix:colon
id|DUMMY
comma
id|con_clear
suffix:colon
id|DUMMY
comma
id|con_putc
suffix:colon
id|DUMMY
comma
id|con_putcs
suffix:colon
id|DUMMY
comma
id|con_cursor
suffix:colon
id|DUMMY
comma
id|con_scroll
suffix:colon
id|DUMMY
comma
id|con_bmove
suffix:colon
id|DUMMY
comma
id|con_switch
suffix:colon
id|DUMMY
comma
id|con_blank
suffix:colon
id|DUMMY
comma
id|con_font_op
suffix:colon
id|DUMMY
comma
id|con_set_palette
suffix:colon
id|DUMMY
comma
id|con_scrolldelta
suffix:colon
id|DUMMY
comma
)brace
suffix:semicolon
eof
