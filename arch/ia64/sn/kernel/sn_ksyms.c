multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * Architecture-specific kernel symbols&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
multiline_comment|/*&n; * other stuff (more to be added later, cleanup then)&n; */
DECL|variable|sn1_pci_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_map_sg
)paren
suffix:semicolon
DECL|variable|sn1_pci_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_unmap_sg
)paren
suffix:semicolon
DECL|variable|sn1_pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|sn1_pci_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_free_consistent
)paren
suffix:semicolon
DECL|variable|sn1_dma_address
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_dma_address
)paren
suffix:semicolon
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
r_extern
id|devfs_handle_t
id|base_io_scsi_ctlr_vhdl
(braket
)braket
suffix:semicolon
macro_line|#include &lt;asm/sn/types.h&gt;
r_extern
id|cnodeid_t
id|master_node_get
c_func
(paren
id|devfs_handle_t
id|vhdl
)paren
suffix:semicolon
macro_line|#include &lt;asm/sn/arch.h&gt;
DECL|variable|base_io_scsi_ctlr_vhdl
id|EXPORT_SYMBOL
c_func
(paren
id|base_io_scsi_ctlr_vhdl
)paren
suffix:semicolon
DECL|variable|master_node_get
id|EXPORT_SYMBOL
c_func
(paren
id|master_node_get
)paren
suffix:semicolon
multiline_comment|/*&n; * symbols referenced by the PCIBA module&n; */
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hack.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
id|devfs_handle_t
id|devfn_to_vertex
c_func
(paren
r_int
r_char
id|busnum
comma
r_int
r_int
id|devfn
)paren
suffix:semicolon
DECL|variable|devfn_to_vertex
id|EXPORT_SYMBOL
c_func
(paren
id|devfn_to_vertex
)paren
suffix:semicolon
DECL|variable|hwgraph_vertex_unref
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_vertex_unref
)paren
suffix:semicolon
DECL|variable|pciio_config_get
id|EXPORT_SYMBOL
c_func
(paren
id|pciio_config_get
)paren
suffix:semicolon
DECL|variable|pciio_info_slot_get
id|EXPORT_SYMBOL
c_func
(paren
id|pciio_info_slot_get
)paren
suffix:semicolon
DECL|variable|hwgraph_edge_add
id|EXPORT_SYMBOL
c_func
(paren
id|hwgraph_edge_add
)paren
suffix:semicolon
DECL|variable|pciio_info_master_get
id|EXPORT_SYMBOL
c_func
(paren
id|pciio_info_master_get
)paren
suffix:semicolon
DECL|variable|pciio_info_get
id|EXPORT_SYMBOL
c_func
(paren
id|pciio_info_get
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_SGI_SN_DEBUG
DECL|variable|__pa_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__pa_debug
)paren
suffix:semicolon
DECL|variable|__va_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__va_debug
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* added by tduffy 04.08.01 to fix depmod issues */
macro_line|#include &lt;linux/mmzone.h&gt;
DECL|variable|sn1_pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_unmap_single
)paren
suffix:semicolon
DECL|variable|sn1_pci_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_map_single
)paren
suffix:semicolon
DECL|variable|sn1_pci_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|sn1_pci_dma_sync_single
)paren
suffix:semicolon
eof
