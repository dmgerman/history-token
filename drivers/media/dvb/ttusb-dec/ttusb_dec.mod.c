macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/vermagic.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
id|MODULE_INFO
c_func
(paren
id|vermagic
comma
id|VERMAGIC_STRING
)paren
suffix:semicolon
r_static
r_const
r_char
id|__module_depends
(braket
)braket
DECL|variable|__attribute_used__
id|__attribute_used__
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.modinfo&quot;
)paren
)paren
)paren
op_assign
l_string|&quot;depends=dvb-core&quot;
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;usb:v0B48p1006dl*dh*dc*dsc*dp*ic*isc*ip*&quot;
)paren
suffix:semicolon
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;usb:v0B48p1008dl*dh*dc*dsc*dp*ic*isc*ip*&quot;
)paren
suffix:semicolon
eof
