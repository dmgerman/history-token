multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/sn0_fru.h&gt;&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SN_SN0_SN0_FRU_H
DECL|macro|_ASM_SN_SN0_SN0_FRU_H
mdefine_line|#define _ASM_SN_SN0_SN0_FRU_H
DECL|macro|MAX_DIMMS
mdefine_line|#define MAX_DIMMS&t;&t;&t;8&t; /* max # of dimm banks */
DECL|macro|MAX_PCIDEV
mdefine_line|#define MAX_PCIDEV&t;&t;&t;8&t; /* max # of pci devices on a pci bus */
DECL|typedef|confidence_t
r_typedef
r_int
r_char
id|confidence_t
suffix:semicolon
DECL|struct|kf_mem_s
r_typedef
r_struct
id|kf_mem_s
(brace
DECL|member|km_confidence
id|confidence_t
id|km_confidence
suffix:semicolon
multiline_comment|/* confidence level that the memory is bad &n;&t;&t;&t;&t;     * is this necessary ? &n;&t;&t;&t;&t;     */
DECL|member|km_dimm
id|confidence_t
id|km_dimm
(braket
id|MAX_DIMMS
)braket
suffix:semicolon
multiline_comment|/* confidence level that dimm[i] is bad &n;&t;&t;&t;&t;     *I think this is the right number&n;&t;&t;&t;&t;     */
DECL|typedef|kf_mem_t
)brace
id|kf_mem_t
suffix:semicolon
DECL|struct|kf_cpu_s
r_typedef
r_struct
id|kf_cpu_s
(brace
DECL|member|kc_confidence
id|confidence_t
id|kc_confidence
suffix:semicolon
multiline_comment|/* confidence level that cpu is bad */
DECL|member|kc_icache
id|confidence_t
id|kc_icache
suffix:semicolon
multiline_comment|/* confidence level that instr. cache is bad */
DECL|member|kc_dcache
id|confidence_t
id|kc_dcache
suffix:semicolon
multiline_comment|/* confidence level that data   cache is bad */
DECL|member|kc_scache
id|confidence_t
id|kc_scache
suffix:semicolon
multiline_comment|/* confidence level that sec.   cache is bad */
DECL|member|kc_sysbus
id|confidence_t
id|kc_sysbus
suffix:semicolon
multiline_comment|/* confidence level that sysad/cmd/state bus is bad */
DECL|typedef|kf_cpu_t
)brace
id|kf_cpu_t
suffix:semicolon
DECL|struct|kf_pci_bus_s
r_typedef
r_struct
id|kf_pci_bus_s
(brace
DECL|member|kpb_belief
id|confidence_t
id|kpb_belief
suffix:semicolon
multiline_comment|/* confidence level  that the  pci bus is bad */
DECL|member|kpb_pcidev_belief
id|confidence_t
id|kpb_pcidev_belief
(braket
id|MAX_PCIDEV
)braket
suffix:semicolon
multiline_comment|/* confidence level that the pci dev is bad */
DECL|typedef|kf_pci_bus_t
)brace
id|kf_pci_bus_t
suffix:semicolon
macro_line|#endif /* _ASM_SN_SN0_SN0_FRU_H */
eof
