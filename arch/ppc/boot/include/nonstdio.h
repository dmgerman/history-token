multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * This is sort of a catchall for I/O related functions.  Stuff that&n; * wouldn&squot;t be in &squot;stdio.h&squot; normally is here, and it&squot;s &squot;nonstdio.h&squot;&n; * for a reason.  -- Tom&n; */
DECL|typedef|FILE
r_typedef
r_int
id|FILE
suffix:semicolon
r_extern
id|FILE
op_star
id|stdin
comma
op_star
id|stdout
suffix:semicolon
DECL|macro|NULL
mdefine_line|#define NULL ((void *)0)
DECL|macro|EOF
mdefine_line|#define EOF (-1)
DECL|macro|fopen
mdefine_line|#define fopen(n, m) NULL
DECL|macro|fflush
mdefine_line|#define fflush(f) 0
DECL|macro|fclose
mdefine_line|#define fclose(f) 0
DECL|macro|perror
mdefine_line|#define perror(s) printf(&quot;%s: no files!&bslash;n&quot;, (s))
r_extern
r_int
id|getc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|printf
c_func
(paren
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|str
comma
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|tstc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
m_exit
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|outb
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_void
id|putc
c_func
(paren
r_const
r_char
id|c
)paren
suffix:semicolon
r_extern
r_void
id|puthex
c_func
(paren
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udelay
c_func
(paren
r_int
id|delay
)paren
suffix:semicolon
r_extern
r_int
r_char
id|inb
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
eof
