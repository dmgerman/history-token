multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_CVLINK_H
DECL|macro|_ASM_IA64_SN_PCI_CVLINK_H
mdefine_line|#define _ASM_IA64_SN_PCI_CVLINK_H
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sn/pio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalkaddrs.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
DECL|macro|MAX_PCI_XWIDGET
mdefine_line|#define MAX_PCI_XWIDGET 256
DECL|macro|MAX_ATE_MAPS
mdefine_line|#define MAX_ATE_MAPS 1024
DECL|macro|SN_DEVICE_SYSDATA
mdefine_line|#define SN_DEVICE_SYSDATA(dev) &bslash;&n;&t;((struct sn_device_sysdata *) &bslash;&n;&t;(((struct pci_controller *) ((dev)-&gt;sysdata))-&gt;platform_data))
DECL|macro|IS_PCI32G
mdefine_line|#define IS_PCI32G(dev)&t;((dev)-&gt;dma_mask &gt;= 0xffffffff)
DECL|macro|IS_PCI32L
mdefine_line|#define IS_PCI32L(dev)&t;((dev)-&gt;dma_mask &lt; 0xffffffff)
DECL|macro|PCIDEV_VERTEX
mdefine_line|#define PCIDEV_VERTEX(pci_dev) &bslash;&n;&t;((SN_DEVICE_SYSDATA(pci_dev))-&gt;vhdl)
DECL|struct|sn_widget_sysdata
r_struct
id|sn_widget_sysdata
(brace
DECL|member|vhdl
id|vertex_hdl_t
id|vhdl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sn_device_sysdata
r_struct
id|sn_device_sysdata
(brace
DECL|member|vhdl
id|vertex_hdl_t
id|vhdl
suffix:semicolon
DECL|member|pci_provider
id|pciio_provider_t
op_star
id|pci_provider
suffix:semicolon
DECL|member|intr_handle
id|pciio_intr_t
id|intr_handle
suffix:semicolon
DECL|member|dma_flush_list
r_struct
id|sn_flush_device_list
op_star
id|dma_flush_list
suffix:semicolon
DECL|member|pio_map
id|pciio_piomap_t
id|pio_map
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ioports_to_tlbs_s
r_struct
id|ioports_to_tlbs_s
(brace
DECL|member|p
r_int
r_int
id|p
suffix:colon
l_int|1
comma
DECL|member|rv_1
id|rv_1
suffix:colon
l_int|1
comma
DECL|member|ma
id|ma
suffix:colon
l_int|3
comma
DECL|member|a
id|a
suffix:colon
l_int|1
comma
DECL|member|d
id|d
suffix:colon
l_int|1
comma
DECL|member|pl
id|pl
suffix:colon
l_int|2
comma
DECL|member|ar
id|ar
suffix:colon
l_int|3
comma
DECL|member|ppn
id|ppn
suffix:colon
l_int|38
comma
DECL|member|rv_2
id|rv_2
suffix:colon
l_int|2
comma
DECL|member|ed
id|ed
suffix:colon
l_int|1
comma
DECL|member|ig
id|ig
suffix:colon
l_int|11
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_PCI_CVLINK_H */
eof
