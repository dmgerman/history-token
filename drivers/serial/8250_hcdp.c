multiline_comment|/*&n; * linux/drivers/char/hcdp_serial.c&n; *&n; * Copyright (C) 2002 Hewlett-Packard Co.&n; *&t;Khalid Aziz &lt;khalid_aziz@hp.com&gt;&n; *&n; * Parse the EFI HCDP table to locate serial console and debug ports and&n; * initialize them.&n; *&n; * 2002/08/29 davidm&t;Adjust it to new 2.5 serial driver infrastructure.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &quot;8250_hcdp.h&quot;
DECL|macro|SERIAL_DEBUG_HCDP
macro_line|#undef SERIAL_DEBUG_HCDP
multiline_comment|/*&n; * Parse the HCDP table to find descriptions for headless console and debug&n; * serial ports and add them to rs_table[]. A pointer to HCDP table is&n; * passed as parameter. This function should be called before&n; * serial_console_init() is called to make sure the HCDP serial console will&n; * be available for use. IA-64 kernel calls this function from setup_arch()&n; * after the EFI and ACPI tables have been parsed.&n; */
r_void
id|__init
DECL|function|setup_serial_hcdp
id|setup_serial_hcdp
c_func
(paren
r_void
op_star
id|tablep
)paren
(brace
id|hcdp_dev_t
op_star
id|hcdp_dev
suffix:semicolon
r_struct
id|uart_port
id|port
suffix:semicolon
r_int
r_int
id|iobase
suffix:semicolon
id|hcdp_t
id|hcdp
suffix:semicolon
r_int
id|gsi
comma
id|nr
suffix:semicolon
r_static
r_char
id|options
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#if 0
r_static
r_int
id|shift_once
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SERIAL_DEBUG_HCDP
id|printk
c_func
(paren
l_string|&quot;Entering setup_serial_hcdp()&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Verify we have a valid table pointer */
r_if
c_cond
(paren
op_logical_neg
id|tablep
)paren
r_return
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
multiline_comment|/*&n;&t; * Don&squot;t trust firmware to give us a table starting at an aligned&n;&t; * address. Make a local copy of the HCDP table with aligned&n;&t; * structures.&n;&t; */
id|memcpy
c_func
(paren
op_amp
id|hcdp
comma
id|tablep
comma
r_sizeof
(paren
id|hcdp
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Perform a sanity check on the table. Table should have a signature&n;&t; * of &quot;HCDP&quot; and it should be atleast 82 bytes long to have any&n;&t; * useful information.&n;&t; */
r_if
c_cond
(paren
(paren
id|strncmp
c_func
(paren
id|hcdp.signature
comma
id|HCDP_SIGNATURE
comma
id|HCDP_SIG_LEN
)paren
op_ne
l_int|0
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|hcdp.len
OL
l_int|82
)paren
r_return
suffix:semicolon
macro_line|#ifdef SERIAL_DEBUG_HCDP
id|printk
c_func
(paren
l_string|&quot;setup_serial_hcdp(): table pointer = 0x%p, sig = &squot;%.4s&squot;&bslash;n&quot;
comma
id|tablep
comma
id|hcdp.signature
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; length = %d, rev = %d, &quot;
comma
id|hcdp.len
comma
id|hcdp.rev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OEM ID = %.6s, # of entries = %d&bslash;n&quot;
comma
id|hcdp.oemid
comma
id|hcdp.num_entries
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Parse each device entry&n;&t; */
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
id|hcdp.num_entries
suffix:semicolon
id|nr
op_increment
)paren
(brace
id|hcdp_dev
op_assign
id|hcdp.hcdp_dev
op_plus
id|nr
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We will parse only the primary console device which is&n;&t;&t; * the first entry for these devices. We will ignore rest&n;&t;&t; * of the entries for the same type device that has already&n;&t;&t; * been parsed and initialized&n;&t;&t; */
r_if
c_cond
(paren
id|hcdp_dev-&gt;type
op_ne
id|HCDP_DEV_CONSOLE
)paren
r_continue
suffix:semicolon
id|iobase
op_assign
(paren
(paren
id|u64
)paren
id|hcdp_dev-&gt;base_addr.addrhi
op_lshift
l_int|32
)paren
op_or
id|hcdp_dev-&gt;base_addr.addrlo
suffix:semicolon
id|gsi
op_assign
id|hcdp_dev-&gt;global_int
suffix:semicolon
multiline_comment|/* See PCI spec v2.2, Appendix D (Class Codes): */
r_switch
c_cond
(paren
id|hcdp_dev-&gt;pci_prog_intfc
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|port.type
op_assign
id|PORT_8250
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|port.type
op_assign
id|PORT_16450
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|port.type
op_assign
id|PORT_16550
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x03
suffix:colon
id|port.type
op_assign
id|PORT_16650
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
id|port.type
op_assign
id|PORT_16750
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x05
suffix:colon
id|port.type
op_assign
id|PORT_16850
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x06
suffix:colon
id|port.type
op_assign
id|PORT_16C950
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;warning: EFI HCDP table reports &quot;
l_string|&quot;unknown serial programming interface 0x%02x; &quot;
l_string|&quot;will autoprobe.&bslash;n&quot;
comma
id|hcdp_dev-&gt;pci_prog_intfc
)paren
suffix:semicolon
id|port.type
op_assign
id|PORT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef SERIAL_DEBUG_HCDP
id|printk
c_func
(paren
l_string|&quot;  type = %s, uart = %d&bslash;n&quot;
comma
(paren
(paren
id|hcdp_dev-&gt;type
op_eq
id|HCDP_DEV_CONSOLE
)paren
ques
c_cond
l_string|&quot;Headless Console&quot;
suffix:colon
(paren
(paren
id|hcdp_dev-&gt;type
op_eq
id|HCDP_DEV_DEBUG
)paren
ques
c_cond
l_string|&quot;Debug port&quot;
suffix:colon
l_string|&quot;Huh????&quot;
)paren
)paren
comma
id|port.type
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  base address space = %s, base address = 0x%lx&bslash;n&quot;
comma
(paren
(paren
id|hcdp_dev-&gt;base_addr.space_id
op_eq
id|ACPI_MEM_SPACE
)paren
ques
c_cond
l_string|&quot;Memory Space&quot;
suffix:colon
(paren
(paren
id|hcdp_dev-&gt;base_addr.space_id
op_eq
id|ACPI_IO_SPACE
)paren
ques
c_cond
l_string|&quot;I/O space&quot;
suffix:colon
l_string|&quot;PCI space&quot;
)paren
)paren
comma
id|iobase
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  gsi = %d, baud rate = %lu, bits = %d, clock = %d&bslash;n&quot;
comma
id|gsi
comma
(paren
r_int
r_int
)paren
id|hcdp_dev-&gt;baud
comma
id|hcdp_dev-&gt;bits
comma
id|hcdp_dev-&gt;clock_rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HCDP_PCI_UART
c_func
(paren
id|hcdp_dev
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; PCI id: %02x:%02x:%02x, vendor ID=0x%x, &quot;
l_string|&quot;dev ID=0x%x&bslash;n&quot;
comma
id|hcdp_dev-&gt;pci_seg
comma
id|hcdp_dev-&gt;pci_bus
comma
id|hcdp_dev-&gt;pci_dev
comma
id|hcdp_dev-&gt;pci_vendor_id
comma
id|hcdp_dev-&gt;pci_dev_id
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Now fill in a port structure to update the 8250 port table..&n;&t;&t; */
r_if
c_cond
(paren
id|hcdp_dev-&gt;clock_rate
)paren
id|port.uartclk
op_assign
id|hcdp_dev-&gt;clock_rate
suffix:semicolon
r_else
id|port.uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check if this is an I/O mapped address or a memory mapped&n;&t;&t; * address&n;&t;&t; */
r_if
c_cond
(paren
id|hcdp_dev-&gt;base_addr.space_id
op_eq
id|ACPI_MEM_SPACE
)paren
(brace
id|port.iobase
op_assign
l_int|0
suffix:semicolon
id|port.mapbase
op_assign
id|iobase
suffix:semicolon
id|port.membase
op_assign
id|ioremap
c_func
(paren
id|iobase
comma
l_int|64
)paren
suffix:semicolon
id|port.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hcdp_dev-&gt;base_addr.space_id
op_eq
id|ACPI_IO_SPACE
)paren
(brace
id|port.iobase
op_assign
id|iobase
suffix:semicolon
id|port.mapbase
op_assign
l_int|0
suffix:semicolon
id|port.membase
op_assign
l_int|NULL
suffix:semicolon
id|port.iotype
op_assign
id|SERIAL_IO_PORT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hcdp_dev-&gt;base_addr.space_id
op_eq
id|ACPI_PCICONF_SPACE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;warning: No support for PCI serial console&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|HCDP_IRQ_SUPPORTED
c_func
(paren
id|hcdp_dev
)paren
)paren
(brace
macro_line|#ifdef CONFIG_IA64
r_if
c_cond
(paren
id|HCDP_PCI_UART
c_func
(paren
id|hcdp_dev
)paren
)paren
id|port.irq
op_assign
id|acpi_register_irq
c_func
(paren
id|gsi
comma
id|ACPI_ACTIVE_LOW
comma
id|ACPI_LEVEL_SENSITIVE
)paren
suffix:semicolon
r_else
id|port.irq
op_assign
id|acpi_register_irq
c_func
(paren
id|gsi
comma
id|ACPI_ACTIVE_HIGH
comma
id|ACPI_EDGE_SENSITIVE
)paren
suffix:semicolon
macro_line|#else
id|port.irq
op_assign
id|gsi
suffix:semicolon
macro_line|#endif
id|port.flags
op_or_assign
id|UPF_AUTO_IRQ
suffix:semicolon
r_if
c_cond
(paren
id|HCDP_PCI_UART
c_func
(paren
id|hcdp_dev
)paren
)paren
id|port.flags
op_or_assign
id|UPF_SHARE_IRQ
suffix:semicolon
)brace
id|port.flags
op_or_assign
id|UPF_SKIP_TEST
op_or
id|UPF_BOOT_AUTOCONF
op_or
id|UPF_RESOURCES
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note: the above memset() initializes port.line to 0,&n;&t;&t; * so we register this port as ttyS0.&n;&t;&t; */
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
(brace
id|printk
c_func
(paren
l_string|&quot;setup_serial_hcdp(): early_serial_setup() &quot;
l_string|&quot;for HCDP serial console port failed. &quot;
l_string|&quot;Will try any additional consoles in HCDP.&bslash;n&quot;
)paren
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
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|efi_uart_console_only
c_func
(paren
)paren
)paren
(brace
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
id|hcdp_dev-&gt;baud
comma
id|hcdp_dev-&gt;bits
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
)brace
r_break
suffix:semicolon
)brace
macro_line|#ifdef SERIAL_DEBUG_HCDP
id|printk
c_func
(paren
l_string|&quot;Leaving setup_serial_hcdp()&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
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
id|hcdp_t
op_star
id|hcdp
op_assign
l_int|0
suffix:semicolon
id|hcdp_dev_t
op_star
id|dev
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
id|hcdp
op_assign
(paren
id|hcdp_t
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
id|hcdp
)paren
r_return
l_int|0
suffix:semicolon
id|hcdp
op_assign
id|__va
c_func
(paren
id|hcdp
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|dev
op_assign
id|hcdp-&gt;hcdp_dev
suffix:semicolon
id|i
OL
id|hcdp-&gt;num_entries
suffix:semicolon
id|i
op_increment
comma
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;type
op_eq
id|HCDP_DEV_CONSOLE
)paren
(brace
id|addr
op_assign
(paren
id|u64
)paren
id|dev-&gt;base_addr.addrhi
op_lshift
l_int|32
op_or
id|dev-&gt;base_addr.addrlo
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
