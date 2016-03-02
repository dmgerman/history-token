multiline_comment|/*&n; *  setup.c, Setup for the CASIO CASSIOPEIA E-11/15/55/65.&n; *&n; *  Copyright (C) 2002-2005  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/e55.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;CASIO CASSIOPEIA E-11/15/55/65&quot;
suffix:semicolon
)brace
DECL|function|casio_e55_setup
r_static
r_int
id|__init
id|casio_e55_setup
c_func
(paren
r_void
)paren
(brace
id|set_io_port_base
c_func
(paren
id|IO_PORT_BASE
)paren
suffix:semicolon
id|ioport_resource.start
op_assign
id|IO_PORT_RESOURCE_START
suffix:semicolon
id|ioport_resource.end
op_assign
id|IO_PORT_RESOURCE_END
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|casio_e55_setup
id|arch_initcall
c_func
(paren
id|casio_e55_setup
)paren
suffix:semicolon
eof
