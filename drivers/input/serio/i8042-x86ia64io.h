macro_line|#ifndef _I8042_X86IA64IO_H
DECL|macro|_I8042_X86IA64IO_H
mdefine_line|#define _I8042_X86IA64IO_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
multiline_comment|/*&n; * Names.&n; */
DECL|macro|I8042_KBD_PHYS_DESC
mdefine_line|#define I8042_KBD_PHYS_DESC &quot;isa0060/serio0&quot;
DECL|macro|I8042_AUX_PHYS_DESC
mdefine_line|#define I8042_AUX_PHYS_DESC &quot;isa0060/serio1&quot;
DECL|macro|I8042_MUX_PHYS_DESC
mdefine_line|#define I8042_MUX_PHYS_DESC &quot;isa0060/serio%d&quot;
multiline_comment|/*&n; * IRQs.&n; */
macro_line|#if defined(__ia64__)
DECL|macro|I8042_MAP_IRQ
macro_line|# define I8042_MAP_IRQ(x)&t;isa_irq_to_vector((x))
macro_line|#else
DECL|macro|I8042_MAP_IRQ
macro_line|# define I8042_MAP_IRQ(x)&t;(x)
macro_line|#endif
DECL|macro|I8042_KBD_IRQ
mdefine_line|#define I8042_KBD_IRQ&t;i8042_kbd_irq
DECL|macro|I8042_AUX_IRQ
mdefine_line|#define I8042_AUX_IRQ&t;i8042_aux_irq
DECL|variable|i8042_kbd_irq
r_static
r_int
id|i8042_kbd_irq
suffix:semicolon
DECL|variable|i8042_aux_irq
r_static
r_int
id|i8042_aux_irq
suffix:semicolon
multiline_comment|/*&n; * Register numbers.&n; */
DECL|macro|I8042_COMMAND_REG
mdefine_line|#define I8042_COMMAND_REG&t;i8042_command_reg
DECL|macro|I8042_STATUS_REG
mdefine_line|#define I8042_STATUS_REG&t;i8042_command_reg
DECL|macro|I8042_DATA_REG
mdefine_line|#define I8042_DATA_REG&t;&t;i8042_data_reg
DECL|variable|i8042_command_reg
r_static
r_int
id|i8042_command_reg
op_assign
l_int|0x64
suffix:semicolon
DECL|variable|i8042_data_reg
r_static
r_int
id|i8042_data_reg
op_assign
l_int|0x60
suffix:semicolon
DECL|function|i8042_read_data
r_static
r_inline
r_int
id|i8042_read_data
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|I8042_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|i8042_read_status
r_static
r_inline
r_int
id|i8042_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|I8042_STATUS_REG
)paren
suffix:semicolon
)brace
DECL|function|i8042_write_data
r_static
r_inline
r_void
id|i8042_write_data
c_func
(paren
r_int
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|I8042_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|i8042_write_command
r_static
r_inline
r_void
id|i8042_write_command
c_func
(paren
r_int
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|I8042_COMMAND_REG
)paren
suffix:semicolon
)brace
macro_line|#if defined(__i386__)
macro_line|#include &lt;linux/dmi.h&gt;
DECL|variable|i8042_dmi_table
r_static
r_struct
id|dmi_system_id
id|__initdata
id|i8042_dmi_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ident
op_assign
l_string|&quot;Compaq Proliant 8500&quot;
comma
dot
id|matches
op_assign
(brace
id|DMI_MATCH
c_func
(paren
id|DMI_SYS_VENDOR
comma
l_string|&quot;Compaq&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_PRODUCT_NAME
comma
l_string|&quot;ProLiant&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_PRODUCT_VERSION
comma
l_string|&quot;8500&quot;
)paren
comma
)brace
comma
)brace
comma
(brace
dot
id|ident
op_assign
l_string|&quot;Compaq Proliant DL760&quot;
comma
dot
id|matches
op_assign
(brace
id|DMI_MATCH
c_func
(paren
id|DMI_SYS_VENDOR
comma
l_string|&quot;Compaq&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_PRODUCT_NAME
comma
l_string|&quot;ProLiant&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_PRODUCT_VERSION
comma
l_string|&quot;DL760&quot;
)paren
comma
)brace
comma
)brace
comma
(brace
)brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
DECL|struct|i8042_acpi_resources
r_struct
id|i8042_acpi_resources
(brace
DECL|member|port1
r_int
r_int
id|port1
suffix:semicolon
DECL|member|port2
r_int
r_int
id|port2
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|i8042_acpi_kbd_registered
r_static
r_int
id|i8042_acpi_kbd_registered
suffix:semicolon
DECL|variable|i8042_acpi_aux_registered
r_static
r_int
id|i8042_acpi_aux_registered
suffix:semicolon
DECL|function|i8042_acpi_parse_resource
r_static
id|acpi_status
id|i8042_acpi_parse_resource
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
id|i8042_acpi_resources
op_star
id|i8042_res
op_assign
id|data
suffix:semicolon
r_struct
id|acpi_resource_io
op_star
id|io
suffix:semicolon
r_struct
id|acpi_resource_fixed_io
op_star
id|fixed_io
suffix:semicolon
r_struct
id|acpi_resource_irq
op_star
id|irq
suffix:semicolon
r_struct
id|acpi_resource_ext_irq
op_star
id|ext_irq
suffix:semicolon
r_switch
c_cond
(paren
id|res-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_IO
suffix:colon
id|io
op_assign
op_amp
id|res-&gt;data.io
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;range_length
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i8042_res-&gt;port1
)paren
id|i8042_res-&gt;port1
op_assign
id|io-&gt;min_base_address
suffix:semicolon
r_else
id|i8042_res-&gt;port2
op_assign
id|io-&gt;min_base_address
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_FIXED_IO
suffix:colon
id|fixed_io
op_assign
op_amp
id|res-&gt;data.fixed_io
suffix:semicolon
r_if
c_cond
(paren
id|fixed_io-&gt;range_length
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i8042_res-&gt;port1
)paren
id|i8042_res-&gt;port1
op_assign
id|fixed_io-&gt;base_address
suffix:semicolon
r_else
id|i8042_res-&gt;port2
op_assign
id|fixed_io-&gt;base_address
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_IRQ
suffix:colon
id|irq
op_assign
op_amp
id|res-&gt;data.irq
suffix:semicolon
r_if
c_cond
(paren
id|irq-&gt;number_of_interrupts
OG
l_int|0
)paren
id|i8042_res-&gt;irq
op_assign
id|acpi_register_gsi
c_func
(paren
id|irq-&gt;interrupts
(braket
l_int|0
)braket
comma
id|irq-&gt;edge_level
comma
id|irq-&gt;active_high_low
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_EXT_IRQ
suffix:colon
id|ext_irq
op_assign
op_amp
id|res-&gt;data.extended_irq
suffix:semicolon
r_if
c_cond
(paren
id|ext_irq-&gt;number_of_interrupts
OG
l_int|0
)paren
id|i8042_res-&gt;irq
op_assign
id|acpi_register_gsi
c_func
(paren
id|ext_irq-&gt;interrupts
(braket
l_int|0
)braket
comma
id|ext_irq-&gt;edge_level
comma
id|ext_irq-&gt;active_high_low
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
DECL|function|i8042_acpi_kbd_add
r_static
r_int
id|i8042_acpi_kbd_add
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|i8042_acpi_resources
id|kbd_res
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|kbd_res
comma
l_int|0
comma
r_sizeof
(paren
id|kbd_res
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
id|i8042_acpi_parse_resource
comma
op_amp
id|kbd_res
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
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|kbd_res.port1
)paren
id|i8042_data_reg
op_assign
id|kbd_res.port1
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: [%s] has no data port; default is 0x%x&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_data_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbd_res.port2
)paren
id|i8042_command_reg
op_assign
id|kbd_res.port2
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: [%s] has no command port; default is 0x%x&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_command_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbd_res.irq
)paren
id|i8042_kbd_irq
op_assign
id|kbd_res.irq
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: [%s] has no IRQ; default is %d&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_kbd_irq
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
l_string|&quot;PS/2 Keyboard Controller&quot;
comma
r_sizeof
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ACPI: %s [%s] at I/O 0x%x, 0x%x, irq %d&bslash;n&quot;
comma
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_data_reg
comma
id|i8042_command_reg
comma
id|i8042_kbd_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_acpi_aux_add
r_static
r_int
id|i8042_acpi_aux_add
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|i8042_acpi_resources
id|aux_res
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|aux_res
comma
l_int|0
comma
r_sizeof
(paren
id|aux_res
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
id|i8042_acpi_parse_resource
comma
op_amp
id|aux_res
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
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|aux_res.irq
)paren
id|i8042_aux_irq
op_assign
id|aux_res.irq
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ACPI: [%s] has no IRQ; default is %d&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_aux_irq
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
l_string|&quot;PS/2 Mouse Controller&quot;
comma
r_sizeof
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ACPI: %s [%s] at irq %d&bslash;n&quot;
comma
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|i8042_aux_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|i8042_acpi_kbd_driver
r_static
r_struct
id|acpi_driver
id|i8042_acpi_kbd_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i8042&quot;
comma
dot
id|ids
op_assign
l_string|&quot;PNP0303&quot;
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|i8042_acpi_kbd_add
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|i8042_acpi_aux_driver
r_static
r_struct
id|acpi_driver
id|i8042_acpi_aux_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i8042&quot;
comma
dot
id|ids
op_assign
l_string|&quot;PNP0F13&quot;
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|i8042_acpi_aux_add
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|i8042_acpi_init
r_static
r_int
id|i8042_acpi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
op_logical_or
id|i8042_noacpi
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i8042: ACPI detection disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|result
op_assign
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|i8042_acpi_kbd_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
(brace
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|i8042_acpi_kbd_driver
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|i8042_acpi_kbd_registered
op_assign
l_int|1
suffix:semicolon
id|result
op_assign
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|i8042_acpi_aux_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
id|i8042_acpi_aux_registered
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
l_int|0
)paren
id|i8042_noaux
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_acpi_exit
r_static
r_void
id|i8042_acpi_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|i8042_acpi_kbd_registered
)paren
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|i8042_acpi_kbd_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i8042_acpi_aux_registered
)paren
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|i8042_acpi_aux_driver
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|i8042_platform_init
r_static
r_inline
r_int
id|i8042_platform_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * On ix86 platforms touching the i8042 data register region can do really&n; * bad things. Because of this the region is always reserved on ix86 boxes.&n; *&n; *&t;if (!request_region(I8042_DATA_REG, 16, &quot;i8042&quot;))&n; *&t;&t;return -1;&n; */
id|i8042_kbd_irq
op_assign
id|I8042_MAP_IRQ
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i8042_aux_irq
op_assign
id|I8042_MAP_IRQ
c_func
(paren
l_int|12
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI
r_if
c_cond
(paren
id|i8042_acpi_init
c_func
(paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#if defined(__ia64__)
id|i8042_reset
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#if defined(__i386__)
r_if
c_cond
(paren
id|dmi_check_system
c_func
(paren
id|i8042_dmi_table
)paren
)paren
id|i8042_noloop
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8042_platform_exit
r_static
r_inline
r_void
id|i8042_platform_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ACPI
id|i8042_acpi_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* _I8042_X86IA64IO_H */
eof
