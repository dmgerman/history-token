multiline_comment|/*&n; * arch/ppc/kernel/harrier.h&n; *&n; * Definitions for Motorola MCG Harrier North Bridge &amp; Memory controller&n; *&n; * Author: Dale Farnsworth&n; *         dale.farnsworth@mvista.com&n; *&n; * Modified by: Randy Vinson&n; * &t;   rvinson@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_HARRIER_H
DECL|macro|__ASMPPC_HARRIER_H
mdefine_line|#define __ASMPPC_HARRIER_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
r_struct
id|pci_controller
suffix:semicolon
r_int
id|harrier_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|ppc_reg_base
comma
id|ulong
id|processor_pci_mem_start
comma
id|ulong
id|processor_pci_mem_end
comma
id|ulong
id|processor_pci_io_start
comma
id|ulong
id|processor_pci_io_end
comma
id|ulong
id|processor_mpic_base
)paren
suffix:semicolon
r_int
r_int
id|harrier_get_mem_size
c_func
(paren
id|uint
id|smc_base
)paren
suffix:semicolon
r_int
id|harrier_mpic_init
c_func
(paren
r_int
r_int
id|pci_mem_offset
)paren
suffix:semicolon
r_void
id|harrier_setup_nonmonarch
c_func
(paren
id|uint
id|ppc_reg_base
comma
id|uint
id|in0_size
)paren
suffix:semicolon
r_void
id|harrier_release_eready
c_func
(paren
id|uint
id|ppc_reg_base
)paren
suffix:semicolon
r_void
id|harrier_wait_eready
c_func
(paren
id|uint
id|ppc_reg_base
)paren
suffix:semicolon
macro_line|#endif /* __ASMPPC_HARRIER_H */
eof
