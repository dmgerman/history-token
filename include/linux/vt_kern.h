macro_line|#ifndef _VT_KERN_H
DECL|macro|_VT_KERN_H
mdefine_line|#define _VT_KERN_H
multiline_comment|/*&n; * this really is an extension of the vc_cons structure in console.c, but&n; * with information needed by the vt package&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/vt.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
multiline_comment|/*&n; * Presently, a lot of graphics programs do not restore the contents of&n; * the higher font pages.  Defining this flag will avoid use of them, but&n; * will lose support for PIO_FONTRESET.  Note that many font operations are&n; * not likely to work with these programs anyway; they need to be&n; * fixed.  The linux/Documentation directory includes a code snippet&n; * to save and restore the text font.&n; */
macro_line|#ifdef CONFIG_VGA_CONSOLE
DECL|macro|BROKEN_GRAPHICS_PROGRAMS
mdefine_line|#define BROKEN_GRAPHICS_PROGRAMS 1
macro_line|#endif
DECL|struct|vt_struct
r_extern
r_struct
id|vt_struct
(brace
DECL|member|vc_num
r_int
id|vc_num
suffix:semicolon
multiline_comment|/* The console number */
DECL|member|vc_mode
r_int
r_char
id|vc_mode
suffix:semicolon
multiline_comment|/* KD_TEXT, ... */
DECL|member|vt_mode
r_struct
id|vt_mode
id|vt_mode
suffix:semicolon
DECL|member|vt_pid
r_int
id|vt_pid
suffix:semicolon
DECL|member|vt_newvt
r_int
id|vt_newvt
suffix:semicolon
DECL|member|paste_wait
id|wait_queue_head_t
id|paste_wait
suffix:semicolon
)brace
op_star
id|vt_cons
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
r_extern
r_void
id|kd_mksound
c_func
(paren
r_int
r_int
id|hz
comma
r_int
r_int
id|ticks
)paren
suffix:semicolon
r_extern
r_int
id|kbd_rate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|rep
)paren
suffix:semicolon
multiline_comment|/* console.c */
r_int
id|vc_allocate
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
r_int
id|vc_cons_allocated
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
r_int
id|vc_resize
c_func
(paren
r_int
id|currcons
comma
r_int
r_int
id|cols
comma
r_int
r_int
id|lines
)paren
suffix:semicolon
r_void
id|vc_disallocate
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
r_void
id|reset_palette
c_func
(paren
r_int
id|currcons
)paren
suffix:semicolon
r_void
id|set_palette
c_func
(paren
r_int
id|currcons
)paren
suffix:semicolon
r_void
id|do_blank_screen
c_func
(paren
r_int
id|entering_gfx
)paren
suffix:semicolon
r_void
id|do_unblank_screen
c_func
(paren
r_int
id|leaving_gfx
)paren
suffix:semicolon
r_void
id|unblank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|poke_blanked_console
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|con_font_op
c_func
(paren
r_int
id|currcons
comma
r_struct
id|console_font_op
op_star
id|op
)paren
suffix:semicolon
r_int
id|con_set_cmap
c_func
(paren
r_int
r_char
op_star
id|cmap
)paren
suffix:semicolon
r_int
id|con_get_cmap
c_func
(paren
r_int
r_char
op_star
id|cmap
)paren
suffix:semicolon
r_void
id|scrollback
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|scrollfront
c_func
(paren
r_int
)paren
suffix:semicolon
r_void
id|update_region
c_func
(paren
r_int
id|currcons
comma
r_int
r_int
id|start
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|redraw_screen
c_func
(paren
r_int
id|new_console
comma
r_int
id|is_switch
)paren
suffix:semicolon
DECL|macro|update_screen
mdefine_line|#define update_screen(x) redraw_screen(x, 0)
DECL|macro|switch_screen
mdefine_line|#define switch_screen(x) redraw_screen(x, 1)
r_struct
id|tty_struct
suffix:semicolon
r_int
id|tioclinux
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* consolemap.c */
r_struct
id|unimapinit
suffix:semicolon
r_struct
id|unipair
suffix:semicolon
r_int
id|con_set_trans_old
c_func
(paren
r_int
r_char
op_star
id|table
)paren
suffix:semicolon
r_int
id|con_get_trans_old
c_func
(paren
r_int
r_char
op_star
id|table
)paren
suffix:semicolon
r_int
id|con_set_trans_new
c_func
(paren
r_int
r_int
op_star
id|table
)paren
suffix:semicolon
r_int
id|con_get_trans_new
c_func
(paren
r_int
r_int
op_star
id|table
)paren
suffix:semicolon
r_int
id|con_clear_unimap
c_func
(paren
r_int
id|currcons
comma
r_struct
id|unimapinit
op_star
id|ui
)paren
suffix:semicolon
r_int
id|con_set_unimap
c_func
(paren
r_int
id|currcons
comma
id|ushort
id|ct
comma
r_struct
id|unipair
op_star
id|list
)paren
suffix:semicolon
r_int
id|con_get_unimap
c_func
(paren
r_int
id|currcons
comma
id|ushort
id|ct
comma
id|ushort
op_star
id|uct
comma
r_struct
id|unipair
op_star
id|list
)paren
suffix:semicolon
r_int
id|con_set_default_unimap
c_func
(paren
r_int
id|currcons
)paren
suffix:semicolon
r_void
id|con_free_unimap
c_func
(paren
r_int
id|currcons
)paren
suffix:semicolon
r_void
id|con_protect_unimap
c_func
(paren
r_int
id|currcons
comma
r_int
id|rdonly
)paren
suffix:semicolon
r_int
id|con_copy_unimap
c_func
(paren
r_int
id|dstcons
comma
r_int
id|srccons
)paren
suffix:semicolon
multiline_comment|/* vt.c */
r_void
id|complete_change_console
c_func
(paren
r_int
r_int
id|new_console
)paren
suffix:semicolon
r_int
id|vt_waitactive
c_func
(paren
r_int
id|vt
)paren
suffix:semicolon
r_void
id|change_console
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|reset_vc
c_func
(paren
r_int
r_int
id|new_console
)paren
suffix:semicolon
macro_line|#endif /* _VT_KERN_H */
eof
