multiline_comment|/*&n; * Copyright (c) 2002-2003 Matthew Wilcox for Hewlett-Packard&n; * Copyright (C) 2004 Hewlett-Packard Co&n; *&t;Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|struct|serial_private
r_struct
id|serial_private
(brace
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|iomem_base
r_void
op_star
id|iomem_base
suffix:semicolon
)brace
suffix:semicolon
DECL|function|acpi_serial_mmio
r_static
id|acpi_status
id|acpi_serial_mmio
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
comma
r_struct
id|acpi_resource_address64
op_star
id|addr
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
id|size
op_assign
id|addr-&gt;max_address_range
op_minus
id|addr-&gt;min_address_range
op_plus
l_int|1
suffix:semicolon
id|req-&gt;iomap_base
op_assign
id|addr-&gt;min_address_range
suffix:semicolon
id|req-&gt;iomem_base
op_assign
id|ioremap
c_func
(paren
id|req-&gt;iomap_base
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req-&gt;iomem_base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: couldn&squot;t ioremap 0x%lx-0x%lx&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|req-&gt;iomap_base
comma
id|req-&gt;iomap_base
op_plus
id|size
)paren
suffix:semicolon
r_return
id|AE_ERROR
suffix:semicolon
)brace
id|req-&gt;io_type
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|acpi_serial_port
r_static
id|acpi_status
id|acpi_serial_port
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
comma
r_struct
id|acpi_resource_io
op_star
id|io
)paren
(brace
r_if
c_cond
(paren
id|io-&gt;range_length
)paren
(brace
id|req-&gt;port
op_assign
id|io-&gt;min_base_address
suffix:semicolon
id|req-&gt;io_type
op_assign
id|SERIAL_IO_PORT
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: zero-length IO port range?&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|acpi_serial_ext_irq
r_static
id|acpi_status
id|acpi_serial_ext_irq
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
comma
r_struct
id|acpi_resource_ext_irq
op_star
id|ext_irq
)paren
(brace
r_if
c_cond
(paren
id|ext_irq-&gt;number_of_interrupts
OG
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_IA64
id|req-&gt;irq
op_assign
id|acpi_register_irq
c_func
(paren
id|ext_irq-&gt;interrupts
(braket
l_int|0
)braket
comma
id|ext_irq-&gt;active_high_low
comma
id|ext_irq-&gt;edge_level
)paren
suffix:semicolon
macro_line|#else
id|req-&gt;irq
op_assign
id|ext_irq-&gt;interrupts
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|acpi_serial_irq
r_static
id|acpi_status
id|acpi_serial_irq
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
comma
r_struct
id|acpi_resource_irq
op_star
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq-&gt;number_of_interrupts
OG
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_IA64
id|req-&gt;irq
op_assign
id|acpi_register_irq
c_func
(paren
id|irq-&gt;interrupts
(braket
l_int|0
)braket
comma
id|irq-&gt;active_high_low
comma
id|irq-&gt;edge_level
)paren
suffix:semicolon
macro_line|#else
id|req-&gt;irq
op_assign
id|irq-&gt;interrupts
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|acpi_serial_resource
r_static
id|acpi_status
id|acpi_serial_resource
c_func
(paren
r_struct
id|acpi_resource
op_star
id|res
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|serial_struct
op_star
id|serial_req
op_assign
(paren
r_struct
id|serial_struct
op_star
)paren
id|data
suffix:semicolon
r_struct
id|acpi_resource_address64
id|addr
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|status
op_assign
id|acpi_resource_to_address64
c_func
(paren
id|res
comma
op_amp
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
r_return
id|acpi_serial_mmio
c_func
(paren
id|serial_req
comma
op_amp
id|addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res-&gt;id
op_eq
id|ACPI_RSTYPE_IO
)paren
r_return
id|acpi_serial_port
c_func
(paren
id|serial_req
comma
op_amp
id|res-&gt;data.io
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res-&gt;id
op_eq
id|ACPI_RSTYPE_EXT_IRQ
)paren
r_return
id|acpi_serial_ext_irq
c_func
(paren
id|serial_req
comma
op_amp
id|res-&gt;data.extended_irq
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res-&gt;id
op_eq
id|ACPI_RSTYPE_IRQ
)paren
r_return
id|acpi_serial_irq
c_func
(paren
id|serial_req
comma
op_amp
id|res-&gt;data.irq
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|acpi_serial_add
r_static
r_int
id|acpi_serial_add
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|serial_private
op_star
id|priv
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|serial_struct
id|serial_req
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|serial_req
comma
l_int|0
comma
r_sizeof
(paren
id|serial_req
)paren
)paren
suffix:semicolon
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serial_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
(brace
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|priv
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_walk_resources
c_func
(paren
id|device-&gt;handle
comma
id|METHOD_NAME__CRS
comma
id|acpi_serial_resource
comma
op_amp
id|serial_req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial_req.iomem_base
)paren
id|priv-&gt;iomem_base
op_assign
id|serial_req.iomem_base
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|serial_req.port
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no iomem or port address in %s _CRS&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|device-&gt;pnp.bus_id
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|serial_req.baud_base
op_assign
id|BASE_BAUD
suffix:semicolon
id|serial_req.flags
op_assign
id|UPF_SKIP_TEST
op_or
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_AUTO_IRQ
op_or
id|UPF_RESOURCES
suffix:semicolon
id|priv-&gt;line
op_assign
id|register_serial
c_func
(paren
op_amp
id|serial_req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;line
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Couldn&squot;t register serial port %s: %d&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
id|priv-&gt;line
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|priv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|serial_req.iomem_base
)paren
id|iounmap
c_func
(paren
id|serial_req.iomem_base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|acpi_serial_remove
r_static
r_int
id|acpi_serial_remove
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
(brace
r_struct
id|serial_private
op_star
id|priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
op_logical_neg
id|acpi_driver_data
c_func
(paren
id|device
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|priv
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|unregister_serial
c_func
(paren
id|priv-&gt;line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;iomem_base
)paren
id|iounmap
c_func
(paren
id|priv-&gt;iomem_base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|acpi_serial_driver
r_static
r_struct
id|acpi_driver
id|acpi_serial_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial&quot;
comma
dot
r_class
op_assign
l_string|&quot;&quot;
comma
dot
id|ids
op_assign
l_string|&quot;PNP0501&quot;
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|acpi_serial_add
comma
dot
id|remove
op_assign
id|acpi_serial_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|acpi_serial_init
r_static
r_int
id|__init
id|acpi_serial_init
c_func
(paren
r_void
)paren
(brace
r_return
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_serial_driver
)paren
suffix:semicolon
)brace
DECL|function|acpi_serial_exit
r_static
r_void
id|__exit
id|acpi_serial_exit
c_func
(paren
r_void
)paren
(brace
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|acpi_serial_driver
)paren
suffix:semicolon
)brace
DECL|variable|acpi_serial_init
id|module_init
c_func
(paren
id|acpi_serial_init
)paren
suffix:semicolon
DECL|variable|acpi_serial_exit
id|module_exit
c_func
(paren
id|acpi_serial_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic 8250/16x50 ACPI serial driver&quot;
)paren
suffix:semicolon
eof
