multiline_comment|/*&n; * arch/ppc/platforms/pq2ads.c&n; *&n; * PQ2ADS platform support&n; *&n; * Author: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; * Derived from: est8260_setup.c by Allen Curtis&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
r_void
id|__init
DECL|function|m82xx_board_setup
id|m82xx_board_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable the 2nd UART port */
op_star
(paren
r_volatile
id|uint
op_star
)paren
(paren
id|BCSR_ADDR
op_plus
l_int|4
)paren
op_and_assign
op_complement
id|BCSR1_RS232_EN2
suffix:semicolon
)brace
eof
