multiline_comment|/*&n; * Copyright (C) 2002, 2003, 2004 Hewlett-Packard Co.&n; *&t;Khalid Aziz &lt;khalid_aziz@hp.com&gt;&n; *&t;Alex Williamson &lt;alex.williamson@hp.com&gt;&n; *&t;Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; * Parse the EFI PCDP table to locate the console device.&n; */
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &quot;pcdp.h&quot;
r_static
r_inline
r_int
DECL|function|uart_irq_supported
id|uart_irq_supported
c_func
(paren
r_int
id|rev
comma
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
r_if
c_cond
(paren
id|rev
OL
l_int|3
)paren
r_return
id|uart-&gt;pci_func
op_amp
id|PCDP_UART_IRQ
suffix:semicolon
r_return
id|uart-&gt;flags
op_amp
id|PCDP_UART_IRQ
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|uart_pci
id|uart_pci
c_func
(paren
r_int
id|rev
comma
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
r_if
c_cond
(paren
id|rev
OL
l_int|3
)paren
r_return
id|uart-&gt;pci_func
op_amp
id|PCDP_UART_PCI
suffix:semicolon
r_return
id|uart-&gt;flags
op_amp
id|PCDP_UART_PCI
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|uart_active_high_low
id|uart_active_high_low
c_func
(paren
r_int
id|rev
comma
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
r_if
c_cond
(paren
id|uart_pci
c_func
(paren
id|rev
comma
id|uart
)paren
op_logical_or
id|uart-&gt;flags
op_amp
id|PCDP_UART_ACTIVE_LOW
)paren
r_return
id|ACPI_ACTIVE_LOW
suffix:semicolon
r_return
id|ACPI_ACTIVE_HIGH
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|uart_edge_level
id|uart_edge_level
c_func
(paren
r_int
id|rev
comma
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
r_if
c_cond
(paren
id|uart_pci
c_func
(paren
id|rev
comma
id|uart
)paren
)paren
r_return
id|ACPI_LEVEL_SENSITIVE
suffix:semicolon
r_if
c_cond
(paren
id|rev
OL
l_int|3
op_logical_or
id|uart-&gt;flags
op_amp
id|PCDP_UART_EDGE_SENSITIVE
)paren
r_return
id|ACPI_EDGE_SENSITIVE
suffix:semicolon
r_return
id|ACPI_LEVEL_SENSITIVE
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|setup_serial_console
id|setup_serial_console
c_func
(paren
r_int
id|rev
comma
r_struct
id|pcdp_uart
op_star
id|uart
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
r_struct
id|uart_port
id|port
suffix:semicolon
r_static
r_char
id|options
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|mapsize
op_assign
l_int|64
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.uartclk
op_assign
id|uart-&gt;clock_rate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port.uartclk
)paren
multiline_comment|/* some FW doesn&squot;t supply this */
id|port.uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|uart-&gt;addr.address_space_id
op_eq
id|ACPI_ADR_SPACE_SYSTEM_MEMORY
)paren
(brace
id|port.mapbase
op_assign
id|uart-&gt;addr.address
suffix:semicolon
id|port.membase
op_assign
id|ioremap
c_func
(paren
id|port.mapbase
comma
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port.membase
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
id|port.mapbase
comma
id|port.mapbase
op_plus
id|mapsize
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|port.iotype
op_assign
id|UPIO_MEM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|uart-&gt;addr.address_space_id
op_eq
id|ACPI_ADR_SPACE_SYSTEM_IO
)paren
(brace
id|port.iobase
op_assign
id|uart-&gt;addr.address
suffix:semicolon
id|port.iotype
op_assign
id|UPIO_PORT
suffix:semicolon
)brace
r_else
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|uart-&gt;pci_prog_intfc
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|port.type
op_assign
id|PORT_8250
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|port.type
op_assign
id|PORT_16450
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|port.type
op_assign
id|PORT_16550
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
id|port.type
op_assign
id|PORT_16650
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|port.type
op_assign
id|PORT_16750
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x5
suffix:colon
id|port.type
op_assign
id|PORT_16850
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x6
suffix:colon
id|port.type
op_assign
id|PORT_16C950
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|port.type
op_assign
id|PORT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|port.flags
op_assign
id|UPF_SKIP_TEST
op_or
id|UPF_BOOT_AUTOCONF
suffix:semicolon
r_if
c_cond
(paren
id|uart_irq_supported
c_func
(paren
id|rev
comma
id|uart
)paren
)paren
(brace
id|port.irq
op_assign
id|acpi_register_gsi
c_func
(paren
id|uart-&gt;gsi
comma
id|uart_active_high_low
c_func
(paren
id|rev
comma
id|uart
)paren
comma
id|uart_edge_level
c_func
(paren
id|rev
comma
id|uart
)paren
)paren
suffix:semicolon
id|port.flags
op_or_assign
id|UPF_AUTO_IRQ
suffix:semicolon
multiline_comment|/* some FW reported wrong GSI */
r_if
c_cond
(paren
id|uart_pci
c_func
(paren
id|rev
comma
id|uart
)paren
)paren
id|port.flags
op_or_assign
id|UPF_SHARE_IRQ
suffix:semicolon
)brace
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
)paren
OL
l_int|0
)paren
r_return
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
l_string|&quot;%lun%d&quot;
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
id|add_preferred_console
c_func
(paren
l_string|&quot;ttyS&quot;
comma
id|port.line
comma
id|options
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCDP: serial console at %s 0x%lx (ttyS%d, options %s)&bslash;n&quot;
comma
id|port.iotype
op_eq
id|UPIO_MEM
ques
c_cond
l_string|&quot;MMIO&quot;
suffix:colon
l_string|&quot;I/O&quot;
comma
id|uart-&gt;addr.address
comma
id|port.line
comma
id|options
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
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
macro_line|#ifdef CONFIG_VT
macro_line|#ifdef CONFIG_VGA_CONSOLE
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
macro_line|#endif
macro_line|#endif
)brace
r_void
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
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCDP: v%d at 0x%p&bslash;n&quot;
comma
id|pcdp-&gt;rev
comma
id|pcdp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcdp-&gt;rev
OL
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmdline
comma
l_string|&quot;console=ttyS0&quot;
)paren
op_logical_or
id|efi_uart_console_only
c_func
(paren
)paren
)paren
id|serial
op_assign
l_int|1
suffix:semicolon
)brace
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
id|setup_serial_console
c_func
(paren
id|pcdp-&gt;rev
comma
id|uart
)paren
suffix:semicolon
r_return
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
r_return
suffix:semicolon
)brace
)brace
)brace
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
id|PCDP_TABLE_GUID
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
