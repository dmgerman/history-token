multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PCIBUS_PROVIDER_H
DECL|macro|_ASM_IA64_SN_PCI_PCIBUS_PROVIDER_H
mdefine_line|#define _ASM_IA64_SN_PCI_PCIBUS_PROVIDER_H
multiline_comment|/*&n; * SN pci asic types.  Do not ever renumber these or reuse values.  The&n; * values must agree with what prom thinks they are.&n; */
DECL|macro|PCIIO_ASIC_TYPE_UNKNOWN
mdefine_line|#define PCIIO_ASIC_TYPE_UNKNOWN&t;0
DECL|macro|PCIIO_ASIC_TYPE_PPB
mdefine_line|#define PCIIO_ASIC_TYPE_PPB&t;1
DECL|macro|PCIIO_ASIC_TYPE_PIC
mdefine_line|#define PCIIO_ASIC_TYPE_PIC&t;2
DECL|macro|PCIIO_ASIC_TYPE_TIOCP
mdefine_line|#define PCIIO_ASIC_TYPE_TIOCP&t;3
multiline_comment|/*&n; * Common pciio bus provider data.  There should be one of these as the&n; * first field in any pciio based provider soft structure (e.g. pcibr_soft&n; * tioca_soft, etc).&n; */
DECL|struct|pcibus_bussoft
r_struct
id|pcibus_bussoft
(brace
DECL|member|bs_asic_type
r_uint32
id|bs_asic_type
suffix:semicolon
multiline_comment|/* chipset type */
DECL|member|bs_xid
r_uint32
id|bs_xid
suffix:semicolon
multiline_comment|/* xwidget id */
DECL|member|bs_persist_busnum
r_uint64
id|bs_persist_busnum
suffix:semicolon
multiline_comment|/* Persistent Bus Number */
DECL|member|bs_legacy_io
r_uint64
id|bs_legacy_io
suffix:semicolon
multiline_comment|/* legacy io pio addr */
DECL|member|bs_legacy_mem
r_uint64
id|bs_legacy_mem
suffix:semicolon
multiline_comment|/* legacy mem pio addr */
DECL|member|bs_base
r_uint64
id|bs_base
suffix:semicolon
multiline_comment|/* widget base */
DECL|member|bs_xwidget_info
r_struct
id|xwidget_info
op_star
id|bs_xwidget_info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * DMA mapping flags&n; */
DECL|macro|SN_PCIDMA_CONSISTENT
mdefine_line|#define SN_PCIDMA_CONSISTENT    0x0001
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_PCI_PCIBUS_PROVIDER_H */
eof
