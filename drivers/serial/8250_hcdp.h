multiline_comment|/*&n; * drivers/serial/8250_hcdp.h&n; *&n; * Copyright (C) 2002 Hewlett-Packard Co.&n; *&t;Khalid Aziz &lt;khalid_aziz@hp.com&gt;&n; *&n; * Definitions for HCDP defined serial ports (Serial console and debug&n; * ports)&n; */
multiline_comment|/* ACPI table signatures */
DECL|macro|HCDP_SIG_LEN
mdefine_line|#define HCDP_SIG_LEN&t;&t;4
DECL|macro|HCDP_SIGNATURE
mdefine_line|#define HCDP_SIGNATURE&t;&t;&quot;HCDP&quot;
multiline_comment|/* Space ID as defined in ACPI generic address structure */
DECL|macro|ACPI_MEM_SPACE
mdefine_line|#define ACPI_MEM_SPACE&t;&t;0
DECL|macro|ACPI_IO_SPACE
mdefine_line|#define ACPI_IO_SPACE&t;&t;1
DECL|macro|ACPI_PCICONF_SPACE
mdefine_line|#define ACPI_PCICONF_SPACE&t;2
multiline_comment|/*&n; * Maximum number of HCDP devices we want to read in&n; */
DECL|macro|MAX_HCDP_DEVICES
mdefine_line|#define MAX_HCDP_DEVICES&t;6
multiline_comment|/*&n; * Default UART clock rate if clock rate is 0 in HCDP table.&n; */
DECL|macro|DEFAULT_UARTCLK
mdefine_line|#define DEFAULT_UARTCLK&t;&t;115200
multiline_comment|/*&n; * ACPI Generic Address Structure&n; */
r_typedef
r_struct
(brace
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|bit_width
id|u8
id|bit_width
suffix:semicolon
DECL|member|bit_offset
id|u8
id|bit_offset
suffix:semicolon
DECL|member|resv
id|u8
id|resv
suffix:semicolon
DECL|member|addrlo
id|u32
id|addrlo
suffix:semicolon
DECL|member|addrhi
id|u32
id|addrhi
suffix:semicolon
DECL|typedef|acpi_gen_addr
)brace
id|acpi_gen_addr
suffix:semicolon
multiline_comment|/* HCDP Device descriptor entry types */
DECL|macro|HCDP_DEV_CONSOLE
mdefine_line|#define HCDP_DEV_CONSOLE&t;0
DECL|macro|HCDP_DEV_DEBUG
mdefine_line|#define HCDP_DEV_DEBUG&t;&t;1
multiline_comment|/* HCDP Device descriptor type */
r_typedef
r_struct
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
DECL|member|base_addr
id|acpi_gen_addr
id|base_addr
suffix:semicolon
DECL|member|pci_dev_id
id|u16
id|pci_dev_id
suffix:semicolon
DECL|member|pci_vendor_id
id|u16
id|pci_vendor_id
suffix:semicolon
DECL|member|global_int
id|u32
id|global_int
suffix:semicolon
DECL|member|clock_rate
id|u32
id|clock_rate
suffix:semicolon
DECL|member|pci_prog_intfc
id|u8
id|pci_prog_intfc
suffix:semicolon
DECL|member|resv
id|u8
id|resv
suffix:semicolon
DECL|typedef|hcdp_dev_t
)brace
id|hcdp_dev_t
suffix:semicolon
multiline_comment|/* HCDP Table format */
r_typedef
r_struct
(brace
DECL|member|signature
id|u8
id|signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|rev
id|u8
id|rev
suffix:semicolon
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
DECL|member|num_entries
id|u32
id|num_entries
suffix:semicolon
DECL|member|hcdp_dev
id|hcdp_dev_t
id|hcdp_dev
(braket
id|MAX_HCDP_DEVICES
)braket
suffix:semicolon
DECL|typedef|hcdp_t
)brace
id|hcdp_t
suffix:semicolon
DECL|macro|HCDP_PCI_UART
mdefine_line|#define HCDP_PCI_UART(x) (x-&gt;pci_func &amp; 1UL&lt;&lt;7)
DECL|macro|HCDP_IRQ_SUPPORTED
mdefine_line|#define HCDP_IRQ_SUPPORTED(x) (x-&gt;pci_func &amp; 1UL&lt;&lt;6)
eof
