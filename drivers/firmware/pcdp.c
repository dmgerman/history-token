multiline_comment|/*&n; * Parse the EFI PCDP table to locate the console device.&n; *&n; * (c) Copyright 2002, 2003, 2004 Hewlett-Packard Development Company, L.P.&n; *&t;Khalid Aziz &lt;khalid.aziz@hp.com&gt;&n; *&t;Alex Williamson &lt;alex.williamson@hp.com&gt;&n; *&t;Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &quot;pcdp.h&quot;
r_static
r_int
id|__init
DECL|function|setup_serial_console
id|setup_serial_console
c_func
(paren
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
r_int
id|mmio
suffix:semicolon
r_static
r_char
id|options
(braket
l_int|64
)braket
suffix:semicolon
id|mmio
op_assign
(paren
id|uart-&gt;addr.address_space_id
op_eq
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|options
comma
r_sizeof
(paren
id|options
)paren
comma
l_string|&quot;console=uart,%s,0x%lx,%lun%d&quot;
comma
id|mmio
ques
c_cond
l_string|&quot;mmio&quot;
suffix:colon
l_string|&quot;io&quot;
comma
id|uart-&gt;addr.address
comma
id|uart-&gt;baud
comma
id|uart-&gt;bits
ques
c_cond
id|uart-&gt;bits
suffix:colon
l_int|8
)paren
suffix:semicolon
r_return
id|early_serial_console_init
c_func
(paren
id|options
)paren
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
r_static
r_int
id|__init
DECL|function|setup_vga_console
id|setup_vga_console
c_func
(paren
r_struct
id|pcdp_vga
op_star
id|vga
)paren
(brace
macro_line|#if defined(CONFIG_VT) &amp;&amp; defined(CONFIG_VGA_CONSOLE)
r_if
c_cond
(paren
id|efi_mem_type
c_func
(paren
l_int|0xA0000
)paren
op_eq
id|EFI_CONVENTIONAL_MEMORY
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCDP: VGA selected, but frame buffer is not MMIO!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCDP: VGA console&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
r_int
id|__init
DECL|function|efi_setup_pcdp_console
id|efi_setup_pcdp_console
c_func
(paren
r_char
op_star
id|cmdline
)paren
(brace
r_struct
id|pcdp
op_star
id|pcdp
suffix:semicolon
r_struct
id|pcdp_uart
op_star
id|uart
suffix:semicolon
r_struct
id|pcdp_device
op_star
id|dev
comma
op_star
id|end
suffix:semicolon
r_int
id|i
comma
id|serial
op_assign
l_int|0
suffix:semicolon
id|pcdp
op_assign
id|efi.hcdp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcdp
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCDP: v%d at 0x%lx&bslash;n&quot;
comma
id|pcdp-&gt;rev
comma
id|__pa
c_func
(paren
id|pcdp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmdline
comma
l_string|&quot;console=hcdp&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|pcdp-&gt;rev
OL
l_int|3
)paren
id|serial
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmdline
comma
l_string|&quot;console=&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Explicit &bslash;&quot;console=&bslash;&quot;; ignoring PCDP&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcdp-&gt;rev
OL
l_int|3
op_logical_and
id|efi_uart_console_only
c_func
(paren
)paren
)paren
id|serial
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|uart
op_assign
id|pcdp-&gt;uart
suffix:semicolon
id|i
OL
id|pcdp-&gt;num_uarts
suffix:semicolon
id|i
op_increment
comma
id|uart
op_increment
)paren
(brace
r_if
c_cond
(paren
id|uart-&gt;flags
op_amp
id|PCDP_UART_PRIMARY_CONSOLE
op_logical_or
id|serial
)paren
(brace
r_if
c_cond
(paren
id|uart-&gt;type
op_eq
id|PCDP_CONSOLE_UART
)paren
(brace
r_return
id|setup_serial_console
c_func
(paren
id|uart
)paren
suffix:semicolon
)brace
)brace
)brace
id|end
op_assign
(paren
r_struct
id|pcdp_device
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|pcdp
op_plus
id|pcdp-&gt;length
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
(paren
r_struct
id|pcdp_device
op_star
)paren
(paren
id|pcdp-&gt;uart
op_plus
id|pcdp-&gt;num_uarts
)paren
suffix:semicolon
id|dev
OL
id|end
suffix:semicolon
id|dev
op_assign
(paren
r_struct
id|pcdp_device
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|dev
op_plus
id|dev-&gt;length
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|PCDP_PRIMARY_CONSOLE
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|PCDP_CONSOLE_VGA
)paren
(brace
r_return
id|setup_vga_console
c_func
(paren
(paren
r_struct
id|pcdp_vga
op_star
)paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IA64_EARLY_PRINTK_UART
r_int
r_int
DECL|function|hcdp_early_uart
id|hcdp_early_uart
(paren
r_void
)paren
(brace
id|efi_system_table_t
op_star
id|systab
suffix:semicolon
id|efi_config_table_t
op_star
id|config_tables
suffix:semicolon
r_int
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
r_struct
id|pcdp
op_star
id|pcdp
op_assign
l_int|0
suffix:semicolon
r_struct
id|pcdp_uart
op_star
id|uart
suffix:semicolon
r_int
id|i
suffix:semicolon
id|systab
op_assign
(paren
id|efi_system_table_t
op_star
)paren
id|ia64_boot_param-&gt;efi_systab
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|systab
)paren
r_return
l_int|0
suffix:semicolon
id|systab
op_assign
id|__va
c_func
(paren
id|systab
)paren
suffix:semicolon
id|config_tables
op_assign
(paren
id|efi_config_table_t
op_star
)paren
id|systab-&gt;tables
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|config_tables
)paren
r_return
l_int|0
suffix:semicolon
id|config_tables
op_assign
id|__va
c_func
(paren
id|config_tables
)paren
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
id|systab-&gt;nr_tables
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|efi_guidcmp
c_func
(paren
id|config_tables
(braket
id|i
)braket
dot
id|guid
comma
id|HCDP_TABLE_GUID
)paren
op_eq
l_int|0
)paren
(brace
id|pcdp
op_assign
(paren
r_struct
id|pcdp
op_star
)paren
id|config_tables
(braket
id|i
)braket
dot
id|table
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pcdp
)paren
r_return
l_int|0
suffix:semicolon
id|pcdp
op_assign
id|__va
c_func
(paren
id|pcdp
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|uart
op_assign
id|pcdp-&gt;uart
suffix:semicolon
id|i
OL
id|pcdp-&gt;num_uarts
suffix:semicolon
id|i
op_increment
comma
id|uart
op_increment
)paren
(brace
r_if
c_cond
(paren
id|uart-&gt;type
op_eq
id|PCDP_CONSOLE_UART
)paren
(brace
id|addr
op_assign
id|uart-&gt;addr.address
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|addr
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_IA64_EARLY_PRINTK_UART */
eof
