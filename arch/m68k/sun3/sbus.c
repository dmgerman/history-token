multiline_comment|/*&n; * SBus helper functions&n; *&n; * Sun3 don&squot;t have a sbus, but many of the used devices are also&n; * used on Sparc machines with sbus. To avoid having a lot of&n; * duplicate code, we provide necessary glue stuff to make using&n; * of the sbus driver code possible.&n; *&n; * (C) 1999 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|sbus_init
r_int
id|__init
id|sbus_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sparc_alloc_io
r_void
op_star
id|sparc_alloc_io
(paren
id|u32
id|address
comma
r_void
op_star
r_virtual
comma
r_int
id|len
comma
r_char
op_star
id|name
comma
id|u32
id|bus_type
comma
r_int
id|rdonly
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|address
suffix:semicolon
)brace
DECL|variable|sbus_init
id|subsys_initcall
c_func
(paren
id|sbus_init
)paren
suffix:semicolon
eof
