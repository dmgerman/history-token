multiline_comment|/*&n; *&t;$Id: io_dc.c,v 1.1 2001/04/01 15:02:00 yaegashi Exp $&n; *&t;I/O routines for SEGA Dreamcast&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
DECL|function|dreamcast_isa_port2addr
r_int
r_int
id|dreamcast_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_return
id|offset
op_plus
l_int|0xa0000000
suffix:semicolon
)brace
eof
