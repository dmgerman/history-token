multiline_comment|/*&n; * linux/drivers/char/selection.c&n; *&n; * This module exports the functions:&n; *&n; *     &squot;int set_selection(const unsigned long arg)&squot;&n; *     &squot;void clear_selection(void)&squot;&n; *     &squot;int paste_selection(struct tty_struct *tty)&squot;&n; *     &squot;int sel_loadlut(const unsigned long arg)&squot;&n; *&n; * Now that /dev/vcs exists, most of this can disappear again.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/consolemap.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/tiocl.h&gt;
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
macro_line|#endif
multiline_comment|/* Don&squot;t take this from &lt;ctype.h&gt;: 011-015 on the screen aren&squot;t spaces */
DECL|macro|isspace
mdefine_line|#define isspace(c)&t;((c) == &squot; &squot;)
r_extern
r_void
id|poke_blanked_console
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Variables for selection control. */
multiline_comment|/* Use a dynamic buffer, instead of static (Dec 1994) */
DECL|variable|sel_cons
r_int
id|sel_cons
suffix:semicolon
multiline_comment|/* must not be disallocated */
DECL|variable|sel_start
r_static
r_volatile
r_int
id|sel_start
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* cleared by clear_selection */
DECL|variable|sel_end
r_static
r_int
id|sel_end
suffix:semicolon
DECL|variable|sel_buffer_lth
r_static
r_int
id|sel_buffer_lth
suffix:semicolon
DECL|variable|sel_buffer
r_static
r_char
op_star
id|sel_buffer
suffix:semicolon
multiline_comment|/* clear_selection, highlight and highlight_pointer can be called&n;   from interrupt (via scrollback/front) */
multiline_comment|/* set reverse video on characters s-e of console with selection. */
r_inline
r_static
r_void
DECL|function|highlight
id|highlight
c_func
(paren
r_const
r_int
id|s
comma
r_const
r_int
id|e
)paren
(brace
id|invert_screen
c_func
(paren
id|sel_cons
comma
id|s
comma
id|e
op_minus
id|s
op_plus
l_int|2
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* use complementary color to show the pointer */
r_inline
r_static
r_void
DECL|function|highlight_pointer
id|highlight_pointer
c_func
(paren
r_const
r_int
id|where
)paren
(brace
id|complement_pos
c_func
(paren
id|sel_cons
comma
id|where
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|sel_pos
id|sel_pos
c_func
(paren
r_int
id|n
)paren
(brace
r_return
id|inverse_translate
c_func
(paren
id|vc_cons
(braket
id|sel_cons
)braket
dot
id|d
comma
id|screen_glyph
c_func
(paren
id|sel_cons
comma
id|n
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* remove the current selection highlight, if any,&n;   from the console holding the selection. */
r_void
DECL|function|clear_selection
id|clear_selection
c_func
(paren
r_void
)paren
(brace
id|highlight_pointer
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* hide the pointer */
r_if
c_cond
(paren
id|sel_start
op_ne
op_minus
l_int|1
)paren
(brace
id|highlight
c_func
(paren
id|sel_start
comma
id|sel_end
)paren
suffix:semicolon
id|sel_start
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * User settable table: what characters are to be considered alphabetic?&n; * 256 bits&n; */
DECL|variable|inwordLut
r_static
id|u32
id|inwordLut
(braket
l_int|8
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|inword
r_static
r_inline
r_int
id|inword
c_func
(paren
r_const
r_int
r_char
id|c
)paren
(brace
r_return
(paren
id|inwordLut
(braket
id|c
op_rshift
l_int|5
)braket
op_rshift
(paren
id|c
op_amp
l_int|0x1F
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
multiline_comment|/* set inwordLut contents. Invoked by ioctl(). */
DECL|function|sel_loadlut
r_int
id|sel_loadlut
c_func
(paren
r_const
r_int
r_int
id|arg
)paren
(brace
r_return
id|copy_from_user
c_func
(paren
id|inwordLut
comma
(paren
id|u32
op_star
)paren
(paren
id|arg
op_plus
l_int|4
)paren
comma
l_int|32
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* does screen address p correspond to character at LH/RH edge of screen? */
DECL|function|atedge
r_static
r_inline
r_int
id|atedge
c_func
(paren
r_const
r_int
id|p
comma
r_int
id|size_row
)paren
(brace
r_return
(paren
op_logical_neg
(paren
id|p
op_mod
id|size_row
)paren
op_logical_or
op_logical_neg
(paren
(paren
id|p
op_plus
l_int|2
)paren
op_mod
id|size_row
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* constrain v such that v &lt;= u */
DECL|function|limit
r_static
r_inline
r_int
r_int
id|limit
c_func
(paren
r_const
r_int
r_int
id|v
comma
r_const
r_int
r_int
id|u
)paren
(brace
r_return
(paren
id|v
OG
id|u
)paren
ques
c_cond
id|u
suffix:colon
id|v
suffix:semicolon
)brace
multiline_comment|/* set the current selection. Invoked by ioctl() or by kernel code. */
DECL|function|set_selection
r_int
id|set_selection
c_func
(paren
r_const
r_struct
id|tiocl_selection
op_star
id|sel
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|user
)paren
(brace
r_int
id|sel_mode
comma
id|new_sel_start
comma
id|new_sel_end
comma
id|spc
suffix:semicolon
r_char
op_star
id|bp
comma
op_star
id|obp
suffix:semicolon
r_int
id|i
comma
id|ps
comma
id|pe
suffix:semicolon
r_int
r_int
id|currcons
op_assign
id|fg_console
suffix:semicolon
id|poke_blanked_console
c_func
(paren
)paren
suffix:semicolon
(brace
r_int
r_int
id|xs
comma
id|ys
comma
id|xe
comma
id|ye
suffix:semicolon
r_if
c_cond
(paren
id|user
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|sel
comma
r_sizeof
(paren
op_star
id|sel
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|xs
comma
op_amp
id|sel-&gt;xs
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|ys
comma
op_amp
id|sel-&gt;ys
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|xe
comma
op_amp
id|sel-&gt;xe
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|ye
comma
op_amp
id|sel-&gt;ye
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|sel_mode
comma
op_amp
id|sel-&gt;sel_mode
)paren
suffix:semicolon
)brace
r_else
(brace
id|xs
op_assign
id|sel-&gt;xs
suffix:semicolon
multiline_comment|/* set selection from kernel */
id|ys
op_assign
id|sel-&gt;ys
suffix:semicolon
id|xe
op_assign
id|sel-&gt;xe
suffix:semicolon
id|ye
op_assign
id|sel-&gt;ye
suffix:semicolon
id|sel_mode
op_assign
id|sel-&gt;sel_mode
suffix:semicolon
)brace
id|xs
op_decrement
suffix:semicolon
id|ys
op_decrement
suffix:semicolon
id|xe
op_decrement
suffix:semicolon
id|ye
op_decrement
suffix:semicolon
id|xs
op_assign
id|limit
c_func
(paren
id|xs
comma
id|video_num_columns
op_minus
l_int|1
)paren
suffix:semicolon
id|ys
op_assign
id|limit
c_func
(paren
id|ys
comma
id|video_num_lines
op_minus
l_int|1
)paren
suffix:semicolon
id|xe
op_assign
id|limit
c_func
(paren
id|xe
comma
id|video_num_columns
op_minus
l_int|1
)paren
suffix:semicolon
id|ye
op_assign
id|limit
c_func
(paren
id|ye
comma
id|video_num_lines
op_minus
l_int|1
)paren
suffix:semicolon
id|ps
op_assign
id|ys
op_star
id|video_size_row
op_plus
(paren
id|xs
op_lshift
l_int|1
)paren
suffix:semicolon
id|pe
op_assign
id|ye
op_star
id|video_size_row
op_plus
(paren
id|xe
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sel_mode
op_eq
id|TIOCL_SELCLEAR
)paren
(brace
multiline_comment|/* useful for screendump without selection highlights */
id|clear_selection
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mouse_reporting
c_func
(paren
)paren
op_logical_and
(paren
id|sel_mode
op_amp
id|TIOCL_SELMOUSEREPORT
)paren
)paren
(brace
id|mouse_report
c_func
(paren
id|tty
comma
id|sel_mode
op_amp
id|TIOCL_SELBUTTONMASK
comma
id|xs
comma
id|ys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ps
OG
id|pe
)paren
multiline_comment|/* make sel_start &lt;= sel_end */
(brace
r_int
id|tmp
op_assign
id|ps
suffix:semicolon
id|ps
op_assign
id|pe
suffix:semicolon
id|pe
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sel_cons
op_ne
id|fg_console
)paren
(brace
id|clear_selection
c_func
(paren
)paren
suffix:semicolon
id|sel_cons
op_assign
id|fg_console
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sel_mode
)paren
(brace
r_case
id|TIOCL_SELCHAR
suffix:colon
multiline_comment|/* character-by-character selection */
id|new_sel_start
op_assign
id|ps
suffix:semicolon
id|new_sel_end
op_assign
id|pe
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCL_SELWORD
suffix:colon
multiline_comment|/* word-by-word selection */
id|spc
op_assign
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|ps
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|new_sel_start
op_assign
id|ps
suffix:semicolon
suffix:semicolon
id|ps
op_sub_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|spc
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|ps
)paren
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|spc
op_logical_and
op_logical_neg
id|inword
c_func
(paren
id|sel_pos
c_func
(paren
id|ps
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
id|new_sel_start
op_assign
id|ps
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ps
op_mod
id|video_size_row
)paren
)paren
r_break
suffix:semicolon
)brace
id|spc
op_assign
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|pe
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|new_sel_end
op_assign
id|pe
suffix:semicolon
suffix:semicolon
id|pe
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|spc
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|pe
)paren
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|spc
op_logical_and
op_logical_neg
id|inword
c_func
(paren
id|sel_pos
c_func
(paren
id|pe
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
id|new_sel_end
op_assign
id|pe
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|pe
op_plus
l_int|2
)paren
op_mod
id|video_size_row
)paren
)paren
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TIOCL_SELLINE
suffix:colon
multiline_comment|/* line-by-line selection */
id|new_sel_start
op_assign
id|ps
op_minus
id|ps
op_mod
id|video_size_row
suffix:semicolon
id|new_sel_end
op_assign
id|pe
op_plus
id|video_size_row
op_minus
id|pe
op_mod
id|video_size_row
op_minus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TIOCL_SELPOINTER
suffix:colon
id|highlight_pointer
c_func
(paren
id|pe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* remove the pointer */
id|highlight_pointer
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* select to end of line if on trailing space */
r_if
c_cond
(paren
id|new_sel_end
OG
id|new_sel_start
op_logical_and
op_logical_neg
id|atedge
c_func
(paren
id|new_sel_end
comma
id|video_size_row
)paren
op_logical_and
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|new_sel_end
)paren
)paren
)paren
(brace
r_for
c_loop
(paren
id|pe
op_assign
id|new_sel_end
op_plus
l_int|2
suffix:semicolon
suffix:semicolon
id|pe
op_add_assign
l_int|2
)paren
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|pe
)paren
)paren
op_logical_or
id|atedge
c_func
(paren
id|pe
comma
id|video_size_row
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|isspace
c_func
(paren
id|sel_pos
c_func
(paren
id|pe
)paren
)paren
)paren
id|new_sel_end
op_assign
id|pe
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sel_start
op_eq
op_minus
l_int|1
)paren
multiline_comment|/* no current selection */
id|highlight
c_func
(paren
id|new_sel_start
comma
id|new_sel_end
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|new_sel_start
op_eq
id|sel_start
)paren
(brace
r_if
c_cond
(paren
id|new_sel_end
op_eq
id|sel_end
)paren
multiline_comment|/* no action required */
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|new_sel_end
OG
id|sel_end
)paren
multiline_comment|/* extend to right */
id|highlight
c_func
(paren
id|sel_end
op_plus
l_int|2
comma
id|new_sel_end
)paren
suffix:semicolon
r_else
multiline_comment|/* contract from right */
id|highlight
c_func
(paren
id|new_sel_end
op_plus
l_int|2
comma
id|sel_end
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|new_sel_end
op_eq
id|sel_end
)paren
(brace
r_if
c_cond
(paren
id|new_sel_start
OL
id|sel_start
)paren
multiline_comment|/* extend to left */
id|highlight
c_func
(paren
id|new_sel_start
comma
id|sel_start
op_minus
l_int|2
)paren
suffix:semicolon
r_else
multiline_comment|/* contract from left */
id|highlight
c_func
(paren
id|sel_start
comma
id|new_sel_start
op_minus
l_int|2
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* some other case; start selection from scratch */
(brace
id|clear_selection
c_func
(paren
)paren
suffix:semicolon
id|highlight
c_func
(paren
id|new_sel_start
comma
id|new_sel_end
)paren
suffix:semicolon
)brace
id|sel_start
op_assign
id|new_sel_start
suffix:semicolon
id|sel_end
op_assign
id|new_sel_end
suffix:semicolon
multiline_comment|/* Allocate a new buffer before freeing the old one ... */
id|bp
op_assign
id|kmalloc
c_func
(paren
(paren
id|sel_end
op_minus
id|sel_start
)paren
op_div
l_int|2
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;selection: kmalloc() failed&bslash;n&quot;
)paren
suffix:semicolon
id|clear_selection
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sel_buffer
)paren
id|kfree
c_func
(paren
id|sel_buffer
)paren
suffix:semicolon
id|sel_buffer
op_assign
id|bp
suffix:semicolon
id|obp
op_assign
id|bp
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sel_start
suffix:semicolon
id|i
op_le
id|sel_end
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
op_star
id|bp
op_assign
id|sel_pos
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
op_star
id|bp
op_increment
)paren
)paren
id|obp
op_assign
id|bp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|i
op_plus
l_int|2
)paren
op_mod
id|video_size_row
)paren
)paren
(brace
multiline_comment|/* strip trailing blanks from line and add newline,&n;&t;&t;&t;   unless non-space at end of line. */
r_if
c_cond
(paren
id|obp
op_ne
id|bp
)paren
(brace
id|bp
op_assign
id|obp
suffix:semicolon
op_star
id|bp
op_increment
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
id|obp
op_assign
id|bp
suffix:semicolon
)brace
)brace
id|sel_buffer_lth
op_assign
id|bp
op_minus
id|sel_buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Insert the contents of the selection buffer into the&n; * queue of the tty associated with the current console.&n; * Invoked by ioctl().&n; */
DECL|function|paste_selection
r_int
id|paste_selection
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|vt_struct
op_star
id|vt
op_assign
(paren
r_struct
id|vt_struct
op_star
)paren
id|tty-&gt;driver_data
suffix:semicolon
r_int
id|pasted
op_assign
l_int|0
comma
id|count
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|poke_blanked_console
c_func
(paren
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|vt-&gt;paste_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sel_buffer
op_logical_and
id|sel_buffer_lth
OG
id|pasted
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|count
op_assign
id|sel_buffer_lth
op_minus
id|pasted
suffix:semicolon
id|count
op_assign
id|MIN
c_func
(paren
id|count
comma
id|tty-&gt;ldisc
dot
id|receive_room
c_func
(paren
id|tty
)paren
)paren
suffix:semicolon
id|tty-&gt;ldisc
dot
id|receive_buf
c_func
(paren
id|tty
comma
id|sel_buffer
op_plus
id|pasted
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|pasted
op_add_assign
id|count
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|vt-&gt;paste_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|set_selection
id|EXPORT_SYMBOL
c_func
(paren
id|set_selection
)paren
suffix:semicolon
DECL|variable|paste_selection
id|EXPORT_SYMBOL
c_func
(paren
id|paste_selection
)paren
suffix:semicolon
eof
