macro_line|#ifndef _LINUX_TTY_FLIP_H
DECL|macro|_LINUX_TTY_FLIP_H
mdefine_line|#define _LINUX_TTY_FLIP_H
macro_line|#ifdef INCLUDE_INLINE_FUNCS
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_ extern
macro_line|#else
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_ static __inline__
macro_line|#endif
DECL|function|tty_insert_flip_char
id|_INLINE_
r_void
id|tty_insert_flip_char
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
id|ch
comma
r_char
id|flag
)paren
(brace
r_if
c_cond
(paren
id|tty-&gt;flip.count
OL
id|TTY_FLIPBUF_SIZE
)paren
(brace
id|tty-&gt;flip.count
op_increment
suffix:semicolon
op_star
id|tty-&gt;flip.flag_buf_ptr
op_increment
op_assign
id|flag
suffix:semicolon
op_star
id|tty-&gt;flip.char_buf_ptr
op_increment
op_assign
id|ch
suffix:semicolon
)brace
)brace
DECL|function|tty_schedule_flip
id|_INLINE_
r_void
id|tty_schedule_flip
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
id|schedule_task
c_func
(paren
op_amp
id|tty-&gt;flip.tqueue
)paren
suffix:semicolon
)brace
DECL|macro|_INLINE_
macro_line|#undef _INLINE_
macro_line|#endif /* _LINUX_TTY_FLIP_H */
eof
