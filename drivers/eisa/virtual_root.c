multiline_comment|/*&n; * Virtual EISA root driver.&n; * Acts as a placeholder if we don&squot;t have a proper EISA bridge.&n; *&n; * (C) 2003 Marc Zyngier &lt;maz@wild-wind.fr.eu.org&gt;&n; *&n; * This code is released under the GPL version 2.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* The default EISA device parent (virtual root device). */
DECL|variable|eisa_root_dev
r_static
r_struct
id|device
id|eisa_root_dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Virtual EISA Bridge&quot;
comma
dot
id|bus_id
op_assign
l_string|&quot;eisa&quot;
comma
)brace
suffix:semicolon
DECL|variable|eisa_bus_root
r_static
r_struct
id|eisa_root_device
id|eisa_bus_root
op_assign
(brace
dot
id|dev
op_assign
op_amp
id|eisa_root_dev
comma
dot
id|bus_base_addr
op_assign
l_int|0
comma
dot
id|res
op_assign
op_amp
id|ioport_resource
comma
dot
id|slots
op_assign
id|EISA_MAX_SLOTS
comma
)brace
suffix:semicolon
DECL|function|virtual_eisa_root_init
r_static
r_int
id|virtual_eisa_root_init
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|device_register
(paren
op_amp
id|eisa_root_dev
)paren
)paren
)paren
(brace
r_return
id|r
suffix:semicolon
)brace
id|eisa_root_dev.driver_data
op_assign
op_amp
id|eisa_bus_root
suffix:semicolon
r_if
c_cond
(paren
id|eisa_root_register
(paren
op_amp
id|eisa_bus_root
)paren
)paren
(brace
multiline_comment|/* A real bridge may have been registered before&n;&t;&t; * us. So quietly unregister. */
id|device_unregister
(paren
op_amp
id|eisa_root_dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|virtual_eisa_root_init
id|device_initcall
(paren
id|virtual_eisa_root_init
)paren
suffix:semicolon
eof
