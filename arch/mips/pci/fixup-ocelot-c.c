multiline_comment|/*&n; * Copyright 2002 Momentum Computer Inc.&n; * Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; *&n; * Based on work for the Linux port to the Ocelot board, which is&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * arch/mips/momentum/ocelot_g/pci.c&n; *     Board-specific PCI routines for mv64340 controller.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_int
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|slot
op_eq
l_int|1
)paren
r_return
l_int|2
suffix:semicolon
multiline_comment|/* PCI-X A */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|1
)paren
r_return
l_int|12
suffix:semicolon
multiline_comment|/* PCI-X B */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|2
)paren
r_return
l_int|4
suffix:semicolon
multiline_comment|/* PCI B */
r_return
l_int|0
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Whooops in pcibios_map_irq&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
