multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * Architecture-specific kernel symbols&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
r_extern
id|vertex_hdl_t
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
multiline_comment|/* Support IPIs for loaded modules. */
DECL|variable|sn_send_IPI_phys
id|EXPORT_SYMBOL
c_func
(paren
id|sn_send_IPI_phys
)paren
suffix:semicolon
multiline_comment|/* symbols referenced by partitioning modules */
macro_line|#include &lt;asm/sn/bte.h&gt;
DECL|variable|bte_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_copy
)paren
suffix:semicolon
DECL|variable|bte_unaligned_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_unaligned_copy
)paren
suffix:semicolon
macro_line|#include &lt;asm/sal.h&gt;
DECL|variable|ia64_sal
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_sal
)paren
suffix:semicolon
DECL|variable|physical_node_map
id|EXPORT_SYMBOL
c_func
(paren
id|physical_node_map
)paren
suffix:semicolon
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
DECL|variable|sal_lock
id|EXPORT_SYMBOL
c_func
(paren
id|sal_lock
)paren
suffix:semicolon
DECL|variable|sn_partid
id|EXPORT_SYMBOL
c_func
(paren
id|sn_partid
)paren
suffix:semicolon
DECL|variable|sn_local_partid
id|EXPORT_SYMBOL
c_func
(paren
id|sn_local_partid
)paren
suffix:semicolon
DECL|variable|sn_system_serial_number_string
id|EXPORT_SYMBOL
c_func
(paren
id|sn_system_serial_number_string
)paren
suffix:semicolon
DECL|variable|sn_partition_serial_number
id|EXPORT_SYMBOL
c_func
(paren
id|sn_partition_serial_number
)paren
suffix:semicolon
DECL|variable|sn_mmiob
id|EXPORT_SYMBOL
c_func
(paren
id|sn_mmiob
)paren
suffix:semicolon
multiline_comment|/* added by tduffy 04.08.01 to fix depmod issues */
macro_line|#include &lt;linux/mmzone.h&gt;
r_extern
id|nasid_t
id|master_nasid
suffix:semicolon
DECL|variable|master_nasid
id|EXPORT_SYMBOL
c_func
(paren
id|master_nasid
)paren
suffix:semicolon
DECL|variable|sn_flush_all_caches
id|EXPORT_SYMBOL
c_func
(paren
id|sn_flush_all_caches
)paren
suffix:semicolon
eof
