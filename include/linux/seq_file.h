macro_line|#ifndef _LINUX_SEQ_FILE_H
DECL|macro|_LINUX_SEQ_FILE_H
mdefine_line|#define _LINUX_SEQ_FILE_H
macro_line|#ifdef __KERNEL__
r_struct
id|seq_operations
suffix:semicolon
DECL|struct|seq_file
r_struct
id|seq_file
(brace
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|from
r_int
id|from
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|index
id|loff_t
id|index
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|op
r_struct
id|seq_operations
op_star
id|op
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|seq_operations
r_struct
id|seq_operations
(brace
DECL|member|start
r_void
op_star
(paren
op_star
id|start
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
DECL|member|next
r_void
op_star
(paren
op_star
id|next
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
DECL|member|show
r_int
(paren
op_star
id|show
)paren
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|seq_open
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|seq_operations
op_star
)paren
suffix:semicolon
id|ssize_t
id|seq_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
id|loff_t
id|seq_lseek
c_func
(paren
r_struct
id|file
op_star
comma
id|loff_t
comma
r_int
)paren
suffix:semicolon
r_int
id|seq_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|seq_escape
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|function|seq_putc
r_static
r_inline
r_int
id|seq_putc
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;count
OL
id|m-&gt;size
)paren
(brace
id|m-&gt;buf
(braket
id|m-&gt;count
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|seq_puts
r_static
r_inline
r_int
id|seq_puts
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;count
op_plus
id|len
OL
id|m-&gt;size
)paren
(brace
id|memcpy
c_func
(paren
id|m-&gt;buf
op_plus
id|m-&gt;count
comma
id|s
comma
id|len
)paren
suffix:semicolon
id|m-&gt;count
op_add_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|m-&gt;count
op_assign
id|m-&gt;size
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
id|seq_printf
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof