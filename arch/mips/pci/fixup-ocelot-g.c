multiline_comment|/*&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * Copyright (C) 2004 Ralf Baechle (ralf@linux-mips.org)&n; */
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
multiline_comment|/* Intel 82543 Gigabit MAC */
r_return
l_int|2
suffix:semicolon
multiline_comment|/* irq_nr is 2 for INT0 */
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|slot
op_eq
l_int|2
)paren
multiline_comment|/* Intel 82543 Gigabit MAC */
r_return
l_int|3
suffix:semicolon
multiline_comment|/* irq_nr is 3 for INT1 */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|3
)paren
multiline_comment|/* Intel 21555 bridge */
r_return
l_int|5
suffix:semicolon
multiline_comment|/* irq_nr is 8 for INT6 */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|4
)paren
multiline_comment|/* PMC Slot */
r_return
l_int|9
suffix:semicolon
multiline_comment|/* irq_nr is 9 for INT7 */
r_return
op_minus
l_int|1
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
