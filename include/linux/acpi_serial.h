multiline_comment|/*&n; *  linux/include/linux/acpi_serial.h&n; *&n; *  Copyright (C) 2000  Hewlett-Packard Co.&n; *  Copyright (C) 2000  Khalid Aziz &lt;khalid_aziz@hp.com&gt;&n; *&n; *  Definitions for ACPI defined serial ports (headless console and &n; *  debug ports)&n; *&n; */
r_extern
r_void
id|setup_serial_acpi
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* ACPI table signatures */
DECL|macro|ACPI_SPCRT_SIGNATURE
mdefine_line|#define ACPI_SPCRT_SIGNATURE&t;&quot;SPCR&quot;
DECL|macro|ACPI_DBGPT_SIGNATURE
mdefine_line|#define ACPI_DBGPT_SIGNATURE&t;&quot;DBGP&quot;
multiline_comment|/* Interface type as defined in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_INTFC_16550
mdefine_line|#define ACPI_SERIAL_INTFC_16550&t;0
DECL|macro|ACPI_SERIAL_INTFC_16450
mdefine_line|#define ACPI_SERIAL_INTFC_16450&t;1
multiline_comment|/* Interrupt types for ACPI serial port tables */
DECL|macro|ACPI_SERIAL_INT_PCAT
mdefine_line|#define ACPI_SERIAL_INT_PCAT&t;0x01
DECL|macro|ACPI_SERIAL_INT_APIC
mdefine_line|#define ACPI_SERIAL_INT_APIC&t;0x02
DECL|macro|ACPI_SERIAL_INT_SAPIC
mdefine_line|#define ACPI_SERIAL_INT_SAPIC&t;0x04
multiline_comment|/* Baud rates as defined in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_BAUD_9600
mdefine_line|#define ACPI_SERIAL_BAUD_9600&t;&t;3
DECL|macro|ACPI_SERIAL_BAUD_19200
mdefine_line|#define ACPI_SERIAL_BAUD_19200&t;&t;4
DECL|macro|ACPI_SERIAL_BAUD_57600
mdefine_line|#define ACPI_SERIAL_BAUD_57600&t;&t;6
DECL|macro|ACPI_SERIAL_BAUD_115200
mdefine_line|#define ACPI_SERIAL_BAUD_115200&t;&t;7
multiline_comment|/* Parity as defined in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_PARITY_NONE
mdefine_line|#define ACPI_SERIAL_PARITY_NONE&t;&t;0
multiline_comment|/* Flow control methods as defined in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_FLOW_DCD
mdefine_line|#define ACPI_SERIAL_FLOW_DCD&t;0x01
DECL|macro|ACPI_SERIAL_FLOW_RTS
mdefine_line|#define ACPI_SERIAL_FLOW_RTS&t;0x02
DECL|macro|ACPI_SERIAL_FLOW_XON
mdefine_line|#define ACPI_SERIAL_FLOW_XON&t;0x04
multiline_comment|/* Terminal types as defined in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_TERM_VT100
mdefine_line|#define ACPI_SERIAL_TERM_VT100&t;&t;0
DECL|macro|ACPI_SERIAL_TERM_VT100X
mdefine_line|#define ACPI_SERIAL_TERM_VT100X&t;1
multiline_comment|/* PCI Flags as defined by SPCR table */
DECL|macro|ACPI_SERIAL_PCIFLAG_PNP
mdefine_line|#define ACPI_SERIAL_PCIFLAG_PNP&t;0x00000001
multiline_comment|/* Space ID as defined in base address structure in ACPI serial port tables */
DECL|macro|ACPI_SERIAL_MEM_SPACE
mdefine_line|#define ACPI_SERIAL_MEM_SPACE&t;&t;0
DECL|macro|ACPI_SERIAL_IO_SPACE
mdefine_line|#define ACPI_SERIAL_IO_SPACE&t;&t;1
DECL|macro|ACPI_SERIAL_PCICONF_SPACE
mdefine_line|#define ACPI_SERIAL_PCICONF_SPACE&t;2
multiline_comment|/* &n; * Generic Register Address Structure - as defined by Microsoft &n; * in http://www.microsoft.com/hwdev/onnow/download/LFreeACPI.doc&n; *&n;*/
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
DECL|member|addrl
id|u32
id|addrl
suffix:semicolon
DECL|member|addrh
id|u32
id|addrh
suffix:semicolon
DECL|typedef|gen_regaddr
)brace
id|gen_regaddr
suffix:semicolon
multiline_comment|/* Space ID for generic register address structure */
DECL|macro|REGADDR_SPACE_SYSMEM
mdefine_line|#define REGADDR_SPACE_SYSMEM&t;0
DECL|macro|REGADDR_SPACE_SYSIO
mdefine_line|#define REGADDR_SPACE_SYSIO&t;1
DECL|macro|REGADDR_SPACE_PCICONFIG
mdefine_line|#define REGADDR_SPACE_PCICONFIG&t;2
multiline_comment|/* Serial Port Console Redirection and Debug Port Table formats */
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
DECL|member|length
id|u32
id|length
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
DECL|member|intfc_type
id|u8
id|intfc_type
suffix:semicolon
DECL|member|resv1
id|u8
id|resv1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|base_addr
id|gen_regaddr
id|base_addr
suffix:semicolon
DECL|member|int_type
id|u8
id|int_type
suffix:semicolon
DECL|member|irq
id|u8
id|irq
suffix:semicolon
DECL|member|global_int
id|u8
id|global_int
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|baud
id|u8
id|baud
suffix:semicolon
DECL|member|parity
id|u8
id|parity
suffix:semicolon
DECL|member|stop_bits
id|u8
id|stop_bits
suffix:semicolon
DECL|member|flow_ctrl
id|u8
id|flow_ctrl
suffix:semicolon
DECL|member|termtype
id|u8
id|termtype
suffix:semicolon
DECL|member|language
id|u8
id|language
suffix:semicolon
DECL|member|pci_dev_id
id|u16
id|pci_dev_id
suffix:semicolon
DECL|member|pci_vendor_id
id|u16
id|pci_vendor_id
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
DECL|member|pci_flags
id|u8
id|pci_flags
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pci_seg
id|u8
id|pci_seg
suffix:semicolon
DECL|member|resv2
id|u32
id|resv2
suffix:semicolon
DECL|typedef|acpi_ser_t
)brace
id|acpi_ser_t
suffix:semicolon
eof
