multiline_comment|/*&n; *&t;Low-Level PCI Access for FRV machines.&n; *&n; *&t;(c) 1999 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;asm/sections.h&gt;
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
DECL|macro|PCI_ASSIGN_ROMS
mdefine_line|#define PCI_ASSIGN_ROMS&t;&t;0x1000
DECL|macro|PCI_BIOS_IRQ_SCAN
mdefine_line|#define PCI_BIOS_IRQ_SCAN&t;0x2000
DECL|macro|PCI_ASSIGN_ALL_BUSSES
mdefine_line|#define PCI_ASSIGN_ALL_BUSSES&t;0x4000
r_extern
r_int
r_int
id|__nongpreldata
id|pci_probe
suffix:semicolon
multiline_comment|/* pci-frv.c */
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* pci-vdk.c */
r_extern
r_int
id|__nongpreldata
id|pcibios_last_bus
suffix:semicolon
r_extern
r_struct
id|pci_bus
op_star
id|__nongpreldata
id|pci_root_bus
suffix:semicolon
r_extern
r_struct
id|pci_ops
op_star
id|__nongpreldata
id|pci_root_ops
suffix:semicolon
multiline_comment|/* pci-irq.c */
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
