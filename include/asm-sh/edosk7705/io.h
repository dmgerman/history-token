multiline_comment|/*&n; * include/asm-sh/edosk7705/io.h&n; *&n; * Modified version of io_se.h for the EDOSK7705 specific functions.&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * IO functions for an Hitachi EDOSK7705 development board&n; */
macro_line|#ifndef __ASM_SH_EDOSK7705_IO_H
DECL|macro|__ASM_SH_EDOSK7705_IO_H
mdefine_line|#define __ASM_SH_EDOSK7705_IO_H
macro_line|#include &lt;asm/io_generic.h&gt;
r_extern
r_int
r_char
id|sh_edosk7705_inb
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sh_edosk7705_inl
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_outl
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|sh_edosk7705_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sh_edosk7705_isa_port2addr
c_func
(paren
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_EDOSK7705_IO_H */
eof
