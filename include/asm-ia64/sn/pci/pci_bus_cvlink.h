multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_CVLINK_H
DECL|macro|_ASM_SN_PCI_CVLINK_H
mdefine_line|#define _ASM_SN_PCI_CVLINK_H
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/hack.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sn/pio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
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
DECL|macro|SET_PCIA64
mdefine_line|#define SET_PCIA64(dev) &bslash;&n;&t;(((struct sn1_device_sysdata *)((dev)-&gt;sysdata))-&gt;isa64) = 1
DECL|macro|IS_PCIA64
mdefine_line|#define IS_PCIA64(dev)&t;(((dev)-&gt;dma_mask == 0xffffffffffffffffUL) || &bslash;&n;&t;&t;(((struct sn1_device_sysdata *)((dev)-&gt;sysdata))-&gt;isa64))
DECL|macro|IS_PCI32G
mdefine_line|#define IS_PCI32G(dev)&t;((dev)-&gt;dma_mask &gt;= 0xffffffff)
DECL|macro|IS_PCI32L
mdefine_line|#define IS_PCI32L(dev)&t;((dev)-&gt;dma_mask &lt; 0xffffffff)
DECL|macro|PCIDEV_VERTEX
mdefine_line|#define PCIDEV_VERTEX(pci_dev) &bslash;&n;&t;(((struct sn1_device_sysdata *)((pci_dev)-&gt;sysdata))-&gt;vhdl)
DECL|macro|PCIBUS_VERTEX
mdefine_line|#define PCIBUS_VERTEX(pci_bus) &bslash;&n;&t;(((struct sn1_widget_sysdata *)((pci_bus)-&gt;sysdata))-&gt;vhdl)
DECL|struct|sn1_widget_sysdata
r_struct
id|sn1_widget_sysdata
(brace
DECL|member|vhdl
id|devfs_handle_t
id|vhdl
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sn1_device_sysdata
r_struct
id|sn1_device_sysdata
(brace
DECL|member|vhdl
id|devfs_handle_t
id|vhdl
suffix:semicolon
DECL|member|isa64
r_int
id|isa64
suffix:semicolon
DECL|member|dma_buf_sync
r_volatile
r_int
r_int
op_star
id|dma_buf_sync
suffix:semicolon
DECL|member|xbow_buf_sync
r_volatile
r_int
r_int
op_star
id|xbow_buf_sync
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sn1_dma_maps_s
r_struct
id|sn1_dma_maps_s
(brace
DECL|member|dma_map
r_struct
id|pcibr_dmamap_s
id|dma_map
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
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
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_PCI_CVLINK_H */
eof
