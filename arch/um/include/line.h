multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __LINE_H__
DECL|macro|__LINE_H__
mdefine_line|#define __LINE_H__
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/tqueue.h&quot;
macro_line|#include &quot;linux/tty.h&quot;
macro_line|#include &quot;asm/semaphore.h&quot;
macro_line|#include &quot;chan_user.h&quot;
DECL|struct|line_driver
r_struct
id|line_driver
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|devfs_name
r_char
op_star
id|devfs_name
suffix:semicolon
DECL|member|major
r_int
id|major
suffix:semicolon
DECL|member|minor_start
r_int
id|minor_start
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|subtype
r_int
id|subtype
suffix:semicolon
DECL|member|read_irq
r_int
id|read_irq
suffix:semicolon
DECL|member|read_irq_name
r_char
op_star
id|read_irq_name
suffix:semicolon
DECL|member|write_irq
r_int
id|write_irq
suffix:semicolon
DECL|member|write_irq_name
r_char
op_star
id|write_irq_name
suffix:semicolon
DECL|member|symlink_from
r_char
op_star
id|symlink_from
suffix:semicolon
DECL|member|symlink_to
r_char
op_star
id|symlink_to
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|line
r_struct
id|line
(brace
DECL|member|init_str
r_char
op_star
id|init_str
suffix:semicolon
DECL|member|init_pri
r_int
id|init_pri
suffix:semicolon
DECL|member|chan_list
r_struct
id|list_head
id|chan_list
suffix:semicolon
DECL|member|valid
r_int
id|valid
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|head
r_char
op_star
id|head
suffix:semicolon
DECL|member|tail
r_char
op_star
id|tail
suffix:semicolon
DECL|member|sigio
r_int
id|sigio
suffix:semicolon
DECL|member|task
r_struct
id|tq_struct
id|task
suffix:semicolon
DECL|member|driver
r_struct
id|line_driver
op_star
id|driver
suffix:semicolon
DECL|member|have_irq
r_int
id|have_irq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LINE_INIT
mdefine_line|#define LINE_INIT(str, d) &bslash;&n;&t;{ init_str :&t;str, &bslash;&n;&t;  init_pri :&t;INIT_STATIC, &bslash;&n;&t;  chan_list : &t;{ }, &bslash;&n;&t;  valid :&t;1, &bslash;&n;&t;  count :&t;0, &bslash;&n;&t;  tty :&t;&t;NULL, &bslash;&n;&t;  sem : &t;{ }, &bslash;&n;&t;  buffer :&t;NULL, &bslash;&n;&t;  head :&t;NULL, &bslash;&n;&t;  tail :&t;NULL, &bslash;&n;&t;  sigio :&t;0, &bslash;&n; &t;  driver :&t;d, &bslash;&n;          have_irq :&t;0 }
DECL|struct|lines
r_struct
id|lines
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LINES_INIT
mdefine_line|#define LINES_INIT(n) &bslash;&n;&t;{  num :&t;&t;n, &bslash;&n;&t;   refcount :&t;&t;0 }
r_extern
r_void
id|line_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
suffix:semicolon
r_extern
r_void
id|line_write_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
suffix:semicolon
r_extern
r_void
id|line_close
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|line_open
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
suffix:semicolon
r_extern
r_void
id|line_setup
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|num
comma
r_char
op_star
id|init
)paren
suffix:semicolon
r_extern
r_int
id|line_write
c_func
(paren
r_struct
id|line
op_star
id|line
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|line_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_char
op_star
id|add_xterm_umid
c_func
(paren
r_char
op_star
id|base
)paren
suffix:semicolon
r_extern
r_int
id|line_setup_irq
c_func
(paren
r_int
id|fd
comma
r_int
id|input
comma
r_int
id|output
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|line_close_chan
c_func
(paren
r_struct
id|line
op_star
id|line
)paren
suffix:semicolon
r_extern
r_void
id|line_disable
c_func
(paren
r_struct
id|line
op_star
id|line
comma
r_int
id|current_irq
)paren
suffix:semicolon
r_extern
r_void
id|line_register_devfs
c_func
(paren
r_struct
id|lines
op_star
id|set
comma
r_struct
id|line_driver
op_star
id|line_driver
comma
r_struct
id|tty_driver
op_star
id|driver
comma
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
)paren
suffix:semicolon
r_extern
r_void
id|lines_init
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
)paren
suffix:semicolon
r_extern
r_void
id|close_lines
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof