multiline_comment|/*&n; * system.c - a driver for reserving pnp system resources&n; *&n; * Some code is based on pnpbios_core.c&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
DECL|variable|pnp_dev_table
r_static
r_const
r_struct
id|pnp_device_id
id|pnp_dev_table
(braket
)braket
op_assign
(brace
multiline_comment|/* General ID for reserving resources */
(brace
l_string|&quot;PNP0c02&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* memory controller */
(brace
l_string|&quot;PNP0c01&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;&quot;
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|reserve_ioport_range
r_static
r_void
id|__init
id|reserve_ioport_range
c_func
(paren
r_char
op_star
id|pnpid
comma
r_int
id|start
comma
r_int
id|end
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_char
op_star
id|regionid
suffix:semicolon
id|regionid
op_assign
id|kmalloc
c_func
(paren
l_int|16
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regionid
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|snprintf
c_func
(paren
id|regionid
comma
l_int|16
comma
l_string|&quot;pnp %s&quot;
comma
id|pnpid
)paren
suffix:semicolon
id|res
op_assign
id|request_region
c_func
(paren
id|start
comma
id|end
op_minus
id|start
op_plus
l_int|1
comma
id|regionid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
id|kfree
c_func
(paren
id|regionid
)paren
suffix:semicolon
r_else
id|res-&gt;flags
op_and_assign
op_complement
id|IORESOURCE_BUSY
suffix:semicolon
multiline_comment|/*&n;&t; * Failures at this point are usually harmless. pci quirks for&n;&t; * example do reserve stuff they know about too, so we may well&n;&t; * have double reservations.&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pnp: %s: ioport range 0x%x-0x%x %s reserved&bslash;n&quot;
comma
id|pnpid
comma
id|start
comma
id|end
comma
l_int|NULL
op_ne
id|res
ques
c_cond
l_string|&quot;has been&quot;
suffix:colon
l_string|&quot;could not be&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|reserve_resources_of_dev
r_static
r_void
id|__init
id|reserve_resources_of_dev
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_PORT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_port_valid
c_func
(paren
id|dev
comma
id|i
)paren
)paren
multiline_comment|/* end of resources */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pnp_port_start
c_func
(paren
id|dev
comma
id|i
)paren
op_eq
l_int|0
)paren
multiline_comment|/* disabled */
multiline_comment|/* Do nothing */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pnp_port_start
c_func
(paren
id|dev
comma
id|i
)paren
OL
l_int|0x100
)paren
multiline_comment|/*&n;&t;&t;&t; * Below 0x100 is only standard PC hardware&n;&t;&t;&t; * (pics, kbd, timer, dma, ...)&n;&t;&t;&t; * We should not get resource conflicts there,&n;&t;&t;&t; * and the kernel reserves these anyway&n;&t;&t;&t; * (see arch/i386/kernel/setup.c).&n;&t;&t;&t; * So, do nothing&n;&t;&t;&t; */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pnp_port_end
c_func
(paren
id|dev
comma
id|i
)paren
OL
id|pnp_port_start
c_func
(paren
id|dev
comma
id|i
)paren
)paren
multiline_comment|/* invalid endpoint */
multiline_comment|/* Do nothing */
r_continue
suffix:semicolon
id|reserve_ioport_range
c_func
(paren
id|dev-&gt;dev.bus_id
comma
id|pnp_port_start
c_func
(paren
id|dev
comma
id|i
)paren
comma
id|pnp_port_end
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|system_pnp_probe
r_static
r_int
id|system_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
(brace
id|reserve_resources_of_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|system_pnp_driver
r_static
r_struct
id|pnp_driver
id|system_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;system&quot;
comma
dot
id|flags
op_assign
id|PNP_DRIVER_RES_DO_NOT_CHANGE
comma
dot
id|id_table
op_assign
id|pnp_dev_table
comma
dot
id|probe
op_assign
id|system_pnp_probe
comma
dot
id|remove
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|pnp_system_init
r_static
r_int
id|__init
id|pnp_system_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pnp_register_driver
c_func
(paren
op_amp
id|system_pnp_driver
)paren
suffix:semicolon
)brace
DECL|variable|pnp_system_init
id|subsys_initcall
c_func
(paren
id|pnp_system_init
)paren
suffix:semicolon
eof
