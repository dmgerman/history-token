multiline_comment|/*&n; * arch/ppc/platforms/cpci405.c&n; *&n; * Board setup routines for the esd CPCI-405 cPCI Board.&n; *&n; * Author: Stefan Roese&n; *         stefan.roese@esd-electronics.com&n; *&n; * Copyright 2001 esd electronic system design - hannover germany&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; *&t;History: 11/09/2001 - armin&n; *       added board_init to add in additional instuctions needed during platfrom_init&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
multiline_comment|/*&n; * Some IRQs unique to CPCI-405.&n; */
r_int
id|__init
DECL|function|ppc405_map_irq
id|ppc405_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; *      A       B       C       D&n;&t; */
(brace
(brace
l_int|28
comma
l_int|28
comma
l_int|28
comma
l_int|28
)brace
comma
multiline_comment|/* IDSEL 15 - cPCI slot 8 */
(brace
l_int|29
comma
l_int|29
comma
l_int|29
comma
l_int|29
)brace
comma
multiline_comment|/* IDSEL 16 - cPCI slot 7 */
(brace
l_int|30
comma
l_int|30
comma
l_int|30
comma
l_int|30
)brace
comma
multiline_comment|/* IDSEL 17 - cPCI slot 6 */
(brace
l_int|27
comma
l_int|27
comma
l_int|27
comma
l_int|27
)brace
comma
multiline_comment|/* IDSEL 18 - cPCI slot 5 */
(brace
l_int|28
comma
l_int|28
comma
l_int|28
comma
l_int|28
)brace
comma
multiline_comment|/* IDSEL 19 - cPCI slot 4 */
(brace
l_int|29
comma
l_int|29
comma
l_int|29
comma
l_int|29
)brace
comma
multiline_comment|/* IDSEL 20 - cPCI slot 3 */
(brace
l_int|30
comma
l_int|30
comma
l_int|30
comma
l_int|30
)brace
comma
multiline_comment|/* IDSEL 21 - cPCI slot 2 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|15
comma
id|max_idsel
op_assign
l_int|21
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
DECL|function|board_setup_arch
id|board_setup_arch
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|board_io_mapping
id|board_io_mapping
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|board_setup_irq
id|board_setup_irq
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|board_init
id|board_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PPC_RTC
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
macro_line|#endif
)brace
eof
