macro_line|#ifndef __ASM_PCI_CHANNEL_H
DECL|macro|__ASM_PCI_CHANNEL_H
mdefine_line|#define __ASM_PCI_CHANNEL_H
multiline_comment|/*&n; * This file essentially defines the interface between board&n; * specific PCI code and MIPS common PCI code.  Should potentially put&n; * into include/asm/pci.h file.&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * Each pci channel is a top-level PCI bus seem by CPU.  A machine  with&n; * multiple PCI channels may have multiple PCI host controllers or a&n; * single controller supporting multiple channels.&n; */
DECL|struct|pci_controller
r_struct
id|pci_controller
(brace
DECL|member|next
r_struct
id|pci_controller
op_star
id|next
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
DECL|member|mem_offset
r_int
r_int
id|mem_offset
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
DECL|member|io_offset
r_int
r_int
id|io_offset
suffix:semicolon
multiline_comment|/* For compatibility with current (as of July 2003) pciutils&n;&t;   and XFree86. Eventually will be removed. */
DECL|member|need_domain_info
r_int
r_int
id|need_domain_info
suffix:semicolon
DECL|member|iommu
r_int
id|iommu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used by boards to register their PCI interfaces before the actual scanning.&n; */
r_extern
r_struct
id|pci_controller
op_star
id|alloc_pci_controller
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|register_pci_controller
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
suffix:semicolon
multiline_comment|/*&n; * board supplied pci irq fixup routine&n; */
r_extern
r_int
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
suffix:semicolon
macro_line|#endif  /* __ASM_PCI_CHANNEL_H */
eof
