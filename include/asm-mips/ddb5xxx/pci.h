macro_line|#ifndef __ASM_DDB5XXXX_PCI_H
DECL|macro|__ASM_DDB5XXXX_PCI_H
mdefine_line|#define __ASM_DDB5XXXX_PCI_H
multiline_comment|/*&n; * This file essentially defines the interface between board&n; * specific PCI code and MIPS common PCI code.  Should potentially put&n; * into include/asm/pci.h file.&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * Each pci channel is a top-level PCI bus seem by CPU.  A machine  with&n; * multiple PCI channels may have multiple PCI host controllers or a&n; * single controller supporting multiple channels.&n; */
DECL|struct|pci_channel
r_struct
id|pci_channel
(brace
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * each board defines an array of pci_channels, that ends with all NULL entry&n; */
r_extern
r_struct
id|pci_channel
id|mips_pci_channels
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * board supplied pci irq fixup routine&n; */
r_extern
r_void
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* __ASM_DDB5XXXX_PCI_H */
eof
