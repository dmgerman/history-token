multiline_comment|/*&n; *&t;Low-Level PCI Access for i386 machines.&n; *&n; *&t;(c) 1999 Martin Mares &lt;mj@ucw.cz&gt;&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|macro|PCI_PROBE_BIOS
mdefine_line|#define PCI_PROBE_BIOS&t;&t;0x0001
DECL|macro|PCI_PROBE_CONF1
mdefine_line|#define PCI_PROBE_CONF1&t;&t;0x0002
DECL|macro|PCI_PROBE_CONF2
mdefine_line|#define PCI_PROBE_CONF2&t;&t;0x0004
DECL|macro|PCI_NO_SORT
mdefine_line|#define PCI_NO_SORT&t;&t;0x0100
DECL|macro|PCI_BIOS_SORT
mdefine_line|#define PCI_BIOS_SORT&t;&t;0x0200
DECL|macro|PCI_NO_CHECKS
mdefine_line|#define PCI_NO_CHECKS&t;&t;0x0400
DECL|macro|PCI_USE_PIRQ_MASK
mdefine_line|#define PCI_USE_PIRQ_MASK&t;0x0800
DECL|macro|PCI_ASSIGN_ROMS
mdefine_line|#define PCI_ASSIGN_ROMS&t;&t;0x1000
DECL|macro|PCI_BIOS_IRQ_SCAN
mdefine_line|#define PCI_BIOS_IRQ_SCAN&t;0x2000
DECL|macro|PCI_ASSIGN_ALL_BUSSES
mdefine_line|#define PCI_ASSIGN_ALL_BUSSES&t;0x4000
r_extern
r_int
r_int
id|pci_probe
suffix:semicolon
multiline_comment|/* pci-i386.c */
r_extern
r_int
r_int
id|pcibios_max_latency
suffix:semicolon
r_void
id|pcibios_resource_survey
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|pcibios_enable_resources
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/* pci-pc.c */
r_extern
r_int
id|pcibios_last_bus
suffix:semicolon
r_extern
r_struct
id|pci_bus
op_star
id|pci_root_bus
suffix:semicolon
r_extern
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
multiline_comment|/* pci-irq.c */
DECL|struct|irq_info
r_struct
id|irq_info
(brace
DECL|member|bus
DECL|member|devfn
id|u8
id|bus
comma
id|devfn
suffix:semicolon
multiline_comment|/* Bus, device and function */
r_struct
(brace
DECL|member|link
id|u8
id|link
suffix:semicolon
multiline_comment|/* IRQ line ID, chipset dependent, 0=not routed */
DECL|member|bitmap
id|u16
id|bitmap
suffix:semicolon
multiline_comment|/* Available IRQs */
DECL|member|irq
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|irq
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|slot
id|u8
id|slot
suffix:semicolon
multiline_comment|/* Slot number, 0=onboard */
DECL|member|rfu
id|u8
id|rfu
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|irq_routing_table
r_struct
id|irq_routing_table
(brace
DECL|member|signature
id|u32
id|signature
suffix:semicolon
multiline_comment|/* PIRQ_SIGNATURE should be here */
DECL|member|version
id|u16
id|version
suffix:semicolon
multiline_comment|/* PIRQ_VERSION */
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* Table size in bytes */
DECL|member|rtr_bus
DECL|member|rtr_devfn
id|u8
id|rtr_bus
comma
id|rtr_devfn
suffix:semicolon
multiline_comment|/* Where the interrupt router lies */
DECL|member|exclusive_irqs
id|u16
id|exclusive_irqs
suffix:semicolon
multiline_comment|/* IRQs devoted exclusively to PCI usage */
DECL|member|rtr_vendor
DECL|member|rtr_device
id|u16
id|rtr_vendor
comma
id|rtr_device
suffix:semicolon
multiline_comment|/* Vendor and device ID of interrupt router */
DECL|member|miniport_data
id|u32
id|miniport_data
suffix:semicolon
multiline_comment|/* Crap */
DECL|member|rfu
id|u8
id|rfu
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
multiline_comment|/* Modulo 256 checksum must give zero */
DECL|member|slots
r_struct
id|irq_info
id|slots
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pcibios_irq_mask
suffix:semicolon
r_void
id|pcibios_irq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pcibios_enable_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
eof
