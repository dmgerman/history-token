multiline_comment|/*&n; * Definitions for PCDP-defined console devices&n; *&n; * v1.0a: http://www.dig64.org/specifications/DIG64_HCDPv10a_01.pdf&n; * v2.0:  http://www.dig64.org/specifications/DIG64_HCDPv20_042804.pdf&n; *&n; * (c) Copyright 2002, 2004 Hewlett-Packard Development Company, L.P.&n; *&t;Khalid Aziz &lt;khalid.aziz@hp.com&gt;&n; *&t;Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|PCDP_CONSOLE
mdefine_line|#define PCDP_CONSOLE&t;&t;&t;0
DECL|macro|PCDP_DEBUG
mdefine_line|#define PCDP_DEBUG&t;&t;&t;1
DECL|macro|PCDP_CONSOLE_OUTPUT
mdefine_line|#define PCDP_CONSOLE_OUTPUT&t;&t;2
DECL|macro|PCDP_CONSOLE_INPUT
mdefine_line|#define PCDP_CONSOLE_INPUT&t;&t;3
DECL|macro|PCDP_UART
mdefine_line|#define PCDP_UART&t;&t;&t;(0 &lt;&lt; 3)
DECL|macro|PCDP_VGA
mdefine_line|#define PCDP_VGA&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|PCDP_USB
mdefine_line|#define PCDP_USB&t;&t;&t;(2 &lt;&lt; 3)
multiline_comment|/* pcdp_uart.type and pcdp_device.type */
DECL|macro|PCDP_CONSOLE_UART
mdefine_line|#define PCDP_CONSOLE_UART&t;&t;(PCDP_UART | PCDP_CONSOLE)
DECL|macro|PCDP_DEBUG_UART
mdefine_line|#define PCDP_DEBUG_UART&t;&t;&t;(PCDP_UART | PCDP_DEBUG)
DECL|macro|PCDP_CONSOLE_VGA
mdefine_line|#define PCDP_CONSOLE_VGA&t;&t;(PCDP_VGA  | PCDP_CONSOLE_OUTPUT)
DECL|macro|PCDP_CONSOLE_USB
mdefine_line|#define PCDP_CONSOLE_USB&t;&t;(PCDP_USB  | PCDP_CONSOLE_INPUT)
multiline_comment|/* pcdp_uart.flags */
DECL|macro|PCDP_UART_EDGE_SENSITIVE
mdefine_line|#define PCDP_UART_EDGE_SENSITIVE&t;(1 &lt;&lt; 0)
DECL|macro|PCDP_UART_ACTIVE_LOW
mdefine_line|#define PCDP_UART_ACTIVE_LOW&t;&t;(1 &lt;&lt; 1)
DECL|macro|PCDP_UART_PRIMARY_CONSOLE
mdefine_line|#define PCDP_UART_PRIMARY_CONSOLE&t;(1 &lt;&lt; 2)
DECL|macro|PCDP_UART_IRQ
mdefine_line|#define PCDP_UART_IRQ&t;&t;&t;(1 &lt;&lt; 6) /* in pci_func for rev &lt; 3 */
DECL|macro|PCDP_UART_PCI
mdefine_line|#define PCDP_UART_PCI&t;&t;&t;(1 &lt;&lt; 7) /* in pci_func for rev &lt; 3 */
DECL|struct|pcdp_uart
r_struct
id|pcdp_uart
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|bits
id|u8
id|bits
suffix:semicolon
DECL|member|parity
id|u8
id|parity
suffix:semicolon
DECL|member|stop_bits
id|u8
id|stop_bits
suffix:semicolon
DECL|member|pci_seg
id|u8
id|pci_seg
suffix:semicolon
DECL|member|pci_bus
id|u8
id|pci_bus
suffix:semicolon
DECL|member|pci_dev
id|u8
id|pci_dev
suffix:semicolon
DECL|member|pci_func
id|u8
id|pci_func
suffix:semicolon
DECL|member|baud
id|u64
id|baud
suffix:semicolon
DECL|member|addr
r_struct
id|acpi_generic_address
id|addr
suffix:semicolon
DECL|member|pci_dev_id
id|u16
id|pci_dev_id
suffix:semicolon
DECL|member|pci_vendor_id
id|u16
id|pci_vendor_id
suffix:semicolon
DECL|member|gsi
id|u32
id|gsi
suffix:semicolon
DECL|member|clock_rate
id|u32
id|clock_rate
suffix:semicolon
DECL|member|pci_prog_intfc
id|u8
id|pci_prog_intfc
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcdp_vga
r_struct
id|pcdp_vga
(brace
DECL|member|count
id|u8
id|count
suffix:semicolon
multiline_comment|/* address space descriptors */
)brace
suffix:semicolon
multiline_comment|/* pcdp_device.flags */
DECL|macro|PCDP_PRIMARY_CONSOLE
mdefine_line|#define PCDP_PRIMARY_CONSOLE&t;1
DECL|struct|pcdp_device
r_struct
id|pcdp_device
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|efi_index
id|u16
id|efi_index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcdp
r_struct
id|pcdp
(brace
DECL|member|signature
id|u8
id|signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|rev
id|u8
id|rev
suffix:semicolon
multiline_comment|/* PCDP v2.0 is rev 3 */
DECL|member|chksum
id|u8
id|chksum
suffix:semicolon
DECL|member|oemid
id|u8
id|oemid
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|oem_tabid
id|u8
id|oem_tabid
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|oem_rev
id|u32
id|oem_rev
suffix:semicolon
DECL|member|creator_id
id|u8
id|creator_id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|creator_rev
id|u32
id|creator_rev
suffix:semicolon
DECL|member|num_uarts
id|u32
id|num_uarts
suffix:semicolon
DECL|member|uart
r_struct
id|pcdp_uart
id|uart
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* actual size is num_uarts */
multiline_comment|/* remainder of table is pcdp_device structures */
)brace
suffix:semicolon
eof
