multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PCIDEV_H
DECL|macro|_ASM_IA64_SN_PCI_PCIDEV_H
mdefine_line|#define _ASM_IA64_SN_PCI_PCIDEV_H
macro_line|#include &lt;linux/pci.h&gt;
r_extern
r_struct
id|sn_irq_info
op_star
op_star
id|sn_irq
suffix:semicolon
DECL|macro|SN_PCIDEV_INFO
mdefine_line|#define SN_PCIDEV_INFO(pci_dev) &bslash;&n;        ((struct pcidev_info *)((pci_dev)-&gt;sysdata))
multiline_comment|/*&n; * Given a pci_bus, return the sn pcibus_bussoft struct.  Note that&n; * this only works for root busses, not for busses represented by PPB&squot;s.&n; */
DECL|macro|SN_PCIBUS_BUSSOFT
mdefine_line|#define SN_PCIBUS_BUSSOFT(pci_bus) &bslash;&n;        ((struct pcibus_bussoft *)(PCI_CONTROLLER((pci_bus))-&gt;platform_data))
multiline_comment|/*&n; * Given a struct pci_dev, return the sn pcibus_bussoft struct.  Note&n; * that this is not equivalent to SN_PCIBUS_BUSSOFT(pci_dev-&gt;bus) due&n; * due to possible PPB&squot;s in the path.&n; */
DECL|macro|SN_PCIDEV_BUSSOFT
mdefine_line|#define SN_PCIDEV_BUSSOFT(pci_dev) &bslash;&n;&t;(SN_PCIDEV_INFO(pci_dev)-&gt;pdi_host_pcidev_info-&gt;pdi_pcibus_info)
DECL|macro|PCIIO_BUS_NONE
mdefine_line|#define PCIIO_BUS_NONE&t;255      /* bus 255 reserved */
DECL|macro|PCIIO_SLOT_NONE
mdefine_line|#define PCIIO_SLOT_NONE 255
DECL|macro|PCIIO_FUNC_NONE
mdefine_line|#define PCIIO_FUNC_NONE 255
DECL|macro|PCIIO_VENDOR_ID_NONE
mdefine_line|#define PCIIO_VENDOR_ID_NONE&t;(-1)
DECL|struct|pcidev_info
r_struct
id|pcidev_info
(brace
DECL|member|pdi_pio_mapped_addr
r_uint64
id|pdi_pio_mapped_addr
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 6 BARs PLUS 1 ROM */
DECL|member|pdi_slot_host_handle
r_uint64
id|pdi_slot_host_handle
suffix:semicolon
multiline_comment|/* Bus and devfn Host pci_dev */
DECL|member|pdi_pcibus_info
r_struct
id|pcibus_bussoft
op_star
id|pdi_pcibus_info
suffix:semicolon
multiline_comment|/* Kernel common bus soft */
DECL|member|pdi_host_pcidev_info
r_struct
id|pcidev_info
op_star
id|pdi_host_pcidev_info
suffix:semicolon
multiline_comment|/* Kernel Host pci_dev */
DECL|member|pdi_linux_pcidev
r_struct
id|pci_dev
op_star
id|pdi_linux_pcidev
suffix:semicolon
multiline_comment|/* Kernel pci_dev */
DECL|member|pdi_sn_irq_info
r_struct
id|sn_irq_info
op_star
id|pdi_sn_irq_info
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_PCI_PCIDEV_H */
eof
