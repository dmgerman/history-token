multiline_comment|/* $Id: pbm.h,v 1.3 1999/12/20 17:06:35 zaitcev Exp $&n; *&n; * pbm.h: PCI bus module pseudo driver software state&n; *        Adopted from sparc64 by V. Roganov and G. Raiko&n; *&n; * Original header:&n; * pbm.h: U2P PCI bus module pseudo driver software state.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * To put things into perspective, consider sparc64 with a few PCI controllers.&n; * Each type would have an own structure, with instances related one to one.&n; * We have only pcic on sparc, but we want to be compatible with sparc64 pbm.h.&n; * All three represent different abstractions.&n; *   pci_bus  - Linux PCI subsystem view of a PCI bus (including bridged buses)&n; *   pbm      - Arch-specific view of a PCI bus (sparc or sparc64)&n; *   pcic     - Chip-specific information for PCIC.&n; */
macro_line|#ifndef __SPARC_PBM_H
DECL|macro|__SPARC_PBM_H
mdefine_line|#define __SPARC_PBM_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|struct|linux_pbm_info
r_struct
id|linux_pbm_info
(brace
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* struct linux_prom_pci_ranges&t;pbm_ranges[PROMREG_MAX]; */
multiline_comment|/* int&t;&t;num_pbm_ranges; */
multiline_comment|/* Now things for the actual PCI bus probes. */
DECL|member|pci_first_busno
r_int
r_int
id|pci_first_busno
suffix:semicolon
multiline_comment|/* Can it be nonzero? */
DECL|member|pci_bus
r_struct
id|pci_bus
op_star
id|pci_bus
suffix:semicolon
multiline_comment|/* Was inline, MJ allocs now */
)brace
suffix:semicolon
multiline_comment|/* PCI devices which are not bridges have this placed in their pci_dev&n; * sysdata member.  This makes OBP aware PCI device drivers easier to&n; * code.&n; */
DECL|struct|pcidev_cookie
r_struct
id|pcidev_cookie
(brace
DECL|member|pbm
r_struct
id|linux_pbm_info
op_star
id|pbm
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__SPARC_PBM_H) */
eof
