multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_PCI_CVLINK_H
DECL|macro|_ASM_SN_PCI_CVLINK_H
mdefine_line|#define _ASM_SN_PCI_CVLINK_H
DECL|macro|SET_PCIA64
mdefine_line|#define SET_PCIA64(dev) &bslash;&n;&t;(((struct sn1_device_sysdata *)((dev)-&gt;sysdata))-&gt;isa64) = 1
DECL|macro|IS_PCIA64
mdefine_line|#define IS_PCIA64(dev)&t;(((dev)-&gt;dma_mask == 0xffffffffffffffffUL) || &bslash;&n;&t;&t;(((struct sn1_device_sysdata *)((dev)-&gt;sysdata))-&gt;isa64))
DECL|macro|IS_PCI32G
mdefine_line|#define IS_PCI32G(dev)&t;((dev)-&gt;dma_mask &gt;= 0xffffffff)
DECL|macro|IS_PCI32L
mdefine_line|#define IS_PCI32L(dev)&t;((dev)-&gt;dma_mask &lt; 0xffffffff)
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
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_PCI_CVLINK_H */
eof
