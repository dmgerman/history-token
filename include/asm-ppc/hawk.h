multiline_comment|/*&n; * include/asm-ppc/hawk.h&n; *&n; * Support functions for MCG Falcon/Raven &amp; HAWK North Bridge &amp; Memory ctlr.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * Modified by Randy Vinson (rvinson@mvista.com)&n; *&n; * 2001,2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __ASMPPC_HAWK_H
DECL|macro|__ASMPPC_HAWK_H
mdefine_line|#define __ASMPPC_HAWK_H
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/hawk_defs.h&gt;
r_extern
r_int
id|hawk_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
r_int
id|ppc_reg_base
comma
r_int
r_int
id|processor_pci_mem_start
comma
r_int
r_int
id|processor_pci_mem_end
comma
r_int
r_int
id|processor_pci_io_start
comma
r_int
r_int
id|processor_pci_io_end
comma
r_int
r_int
id|processor_mpic_base
)paren
suffix:semicolon
r_extern
r_int
r_int
id|hawk_get_mem_size
c_func
(paren
r_int
r_int
id|smc_base
)paren
suffix:semicolon
r_extern
r_int
id|hawk_mpic_init
c_func
(paren
r_int
r_int
id|pci_mem_offset
)paren
suffix:semicolon
macro_line|#endif&t;/* __ASMPPC_HAWK_H */
eof
