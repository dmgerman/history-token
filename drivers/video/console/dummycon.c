multiline_comment|/*&n; *  linux/drivers/video/dummycon.c -- A dummy console driver&n; *&n; *  To be used if there&squot;s no other console driver (e.g. for plain VGA text)&n; *  available, usually until fbcon takes console over.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; *  Dummy console driver&n; */
macro_line|#if defined(__arm__)
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;ORIG_VIDEO_COLS
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;ORIG_VIDEO_LINES
macro_line|#elif defined(__hppa__)
multiline_comment|/* set by Kconfig. Use 80x25 for 640x480 and 160x64 for 1280x1024 */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DUMMY_COLUMNS
mdefine_line|#define DUMMY_COLUMNS&t;CONFIG_DUMMY_CONSOLE_COLUMNS
DECL|macro|DUMMY_ROWS
mdefine_line|#define DUMMY_ROWS&t;CONFIG_DUMMY_CONSOLE_ROWS
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
id|vc
comma
r_int
id|init
)paren
(brace
id|vc-&gt;vc_can_do_color
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|init
)paren
(brace
id|vc-&gt;vc_cols
op_assign
id|DUMMY_COLUMNS
suffix:semicolon
id|vc-&gt;vc_rows
op_assign
id|DUMMY_ROWS
suffix:semicolon
)brace
r_else
id|vc_resize
c_func
(paren
id|vc-&gt;vc_num
comma
id|DUMMY_COLUMNS
comma
id|DUMMY_ROWS
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
dot
id|con_startup
op_assign
id|dummycon_startup
comma
dot
id|con_init
op_assign
id|dummycon_init
comma
dot
id|con_deinit
op_assign
id|DUMMY
comma
dot
id|con_clear
op_assign
id|DUMMY
comma
dot
id|con_putc
op_assign
id|DUMMY
comma
dot
id|con_putcs
op_assign
id|DUMMY
comma
dot
id|con_cursor
op_assign
id|DUMMY
comma
dot
id|con_scroll
op_assign
id|DUMMY
comma
dot
id|con_bmove
op_assign
id|DUMMY
comma
dot
id|con_switch
op_assign
id|DUMMY
comma
dot
id|con_blank
op_assign
id|DUMMY
comma
dot
id|con_font_op
op_assign
id|DUMMY
comma
dot
id|con_set_palette
op_assign
id|DUMMY
comma
dot
id|con_scrolldelta
op_assign
id|DUMMY
comma
)brace
suffix:semicolon
eof
