multiline_comment|/*&n; *  linux/include/linux/console.h&n; *&n; *  Copyright (C) 1993        Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * Changed:&n; * 10-Mar-94: Arno Griffioen: Conversion for vt100 emulator port from PC LINUX&n; */
macro_line|#ifndef _LINUX_CONSOLE_H_
DECL|macro|_LINUX_CONSOLE_H_
mdefine_line|#define _LINUX_CONSOLE_H_ 1
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|vc_data
suffix:semicolon
r_struct
id|console_font_op
suffix:semicolon
r_struct
id|module
suffix:semicolon
multiline_comment|/*&n; * this is what the terminal answers to a ESC-Z or csi0c query.&n; */
DECL|macro|VT100ID
mdefine_line|#define VT100ID &quot;&bslash;033[?1;2c&quot;
DECL|macro|VT102ID
mdefine_line|#define VT102ID &quot;&bslash;033[?6c&quot;
DECL|struct|consw
r_struct
id|consw
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|con_startup
r_const
r_char
op_star
(paren
op_star
id|con_startup
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|con_init
r_void
(paren
op_star
id|con_init
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_deinit
r_void
(paren
op_star
id|con_deinit
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_clear
r_void
(paren
op_star
id|con_clear
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_putc
r_void
(paren
op_star
id|con_putc
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_putcs
r_void
(paren
op_star
id|con_putcs
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_const
r_int
r_int
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_cursor
r_void
(paren
op_star
id|con_cursor
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_scroll
r_int
(paren
op_star
id|con_scroll
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_bmove
r_void
(paren
op_star
id|con_bmove
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_switch
r_int
(paren
op_star
id|con_switch
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_blank
r_int
(paren
op_star
id|con_blank
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|con_font_op
r_int
(paren
op_star
id|con_font_op
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_struct
id|console_font_op
op_star
)paren
suffix:semicolon
DECL|member|con_resize
r_int
(paren
op_star
id|con_resize
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|con_set_palette
r_int
(paren
op_star
id|con_set_palette
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|con_scrolldelta
r_int
(paren
op_star
id|con_scrolldelta
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_set_origin
r_int
(paren
op_star
id|con_set_origin
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_save_screen
r_void
(paren
op_star
id|con_save_screen
)paren
(paren
r_struct
id|vc_data
op_star
)paren
suffix:semicolon
DECL|member|con_build_attr
id|u8
(paren
op_star
id|con_build_attr
)paren
(paren
r_struct
id|vc_data
op_star
comma
id|u8
comma
id|u8
comma
id|u8
comma
id|u8
comma
id|u8
)paren
suffix:semicolon
DECL|member|con_invert_region
r_void
(paren
op_star
id|con_invert_region
)paren
(paren
r_struct
id|vc_data
op_star
comma
id|u16
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_screen_pos
id|u16
op_star
(paren
op_star
id|con_screen_pos
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|con_getxy
r_int
r_int
(paren
op_star
id|con_getxy
)paren
(paren
r_struct
id|vc_data
op_star
comma
r_int
r_int
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|consw
op_star
id|conswitchp
suffix:semicolon
r_extern
r_const
r_struct
id|consw
id|dummy_con
suffix:semicolon
multiline_comment|/* dummy console buffer */
r_extern
r_const
r_struct
id|consw
id|fb_con
suffix:semicolon
multiline_comment|/* frame buffer based console */
r_extern
r_const
r_struct
id|consw
id|vga_con
suffix:semicolon
multiline_comment|/* VGA text console */
r_extern
r_const
r_struct
id|consw
id|newport_con
suffix:semicolon
multiline_comment|/* SGI Newport console  */
r_extern
r_const
r_struct
id|consw
id|prom_con
suffix:semicolon
multiline_comment|/* SPARC PROM console */
r_int
id|take_over_console
c_func
(paren
r_const
r_struct
id|consw
op_star
id|sw
comma
r_int
id|first
comma
r_int
id|last
comma
r_int
id|deflt
)paren
suffix:semicolon
r_void
id|give_up_console
c_func
(paren
r_const
r_struct
id|consw
op_star
id|sw
)paren
suffix:semicolon
multiline_comment|/* scroll */
DECL|macro|SM_UP
mdefine_line|#define SM_UP       (1)
DECL|macro|SM_DOWN
mdefine_line|#define SM_DOWN     (2)
multiline_comment|/* cursor */
DECL|macro|CM_DRAW
mdefine_line|#define CM_DRAW     (1)
DECL|macro|CM_ERASE
mdefine_line|#define CM_ERASE    (2)
DECL|macro|CM_MOVE
mdefine_line|#define CM_MOVE     (3)
multiline_comment|/*&n; *&t;The interface for a console, or any other device that&n; *&t;wants to capture console messages (printer driver?)&n; */
DECL|macro|CON_PRINTBUFFER
mdefine_line|#define CON_PRINTBUFFER&t;(1)
DECL|macro|CON_CONSDEV
mdefine_line|#define CON_CONSDEV&t;(2) /* Last on the command line */
DECL|macro|CON_ENABLED
mdefine_line|#define CON_ENABLED&t;(4)
DECL|struct|console
r_struct
id|console
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
r_struct
id|console
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|console
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|device
r_struct
id|tty_driver
op_star
(paren
op_star
id|device
)paren
(paren
r_struct
id|console
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|member|unblank
r_void
(paren
op_star
id|unblank
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|console
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|cflag
r_int
id|cflag
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|next
r_struct
id|console
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|add_preferred_console
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|idx
comma
r_char
op_star
id|options
)paren
suffix:semicolon
r_extern
r_void
id|register_console
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_console
c_func
(paren
r_struct
id|console
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|console
op_star
id|console_drivers
suffix:semicolon
r_extern
r_void
id|acquire_console_sem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|release_console_sem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_conditional_schedule
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_unblank
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|is_console_locked
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Some debug stub to catch some of the obvious races in the VT code */
macro_line|#if 1
DECL|macro|WARN_CONSOLE_UNLOCKED
mdefine_line|#define WARN_CONSOLE_UNLOCKED()&t;WARN_ON(!is_console_locked() &amp;&amp; !oops_in_progress)
macro_line|#else
DECL|macro|WARN_CONSOLE_UNLOCKED
mdefine_line|#define WARN_CONSOLE_UNLOCKED()
macro_line|#endif
multiline_comment|/* VESA Blanking Levels */
DECL|macro|VESA_NO_BLANKING
mdefine_line|#define VESA_NO_BLANKING        0
DECL|macro|VESA_VSYNC_SUSPEND
mdefine_line|#define VESA_VSYNC_SUSPEND      1
DECL|macro|VESA_HSYNC_SUSPEND
mdefine_line|#define VESA_HSYNC_SUSPEND      2
DECL|macro|VESA_POWERDOWN
mdefine_line|#define VESA_POWERDOWN          3
macro_line|#endif /* _LINUX_CONSOLE_H */
eof
