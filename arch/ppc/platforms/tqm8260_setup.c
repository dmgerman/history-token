multiline_comment|/*&n; * arch/ppc/platforms/tqm8260_setup.c&n; *&n; * TQM8260 platform support&n; *&n; * Author: Allen Curtis &lt;acurtis@onz.com&gt;&n; * Derived from: m8260_setup.c by Dan Malek, MVista&n; *&n; * Copyright 2002 Ones and Zeros, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/immap_cpm2.h&gt;
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
r_static
r_int
DECL|function|tqm8260_set_rtc_time
id|tqm8260_set_rtc_time
c_func
(paren
r_int
r_int
id|time
)paren
(brace
(paren
(paren
id|cpm2_map_t
op_star
)paren
id|CPM_MAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_tmcnt
op_assign
id|time
suffix:semicolon
(paren
(paren
id|cpm2_map_t
op_star
)paren
id|CPM_MAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_tmcntsc
op_assign
l_int|0x3
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|tqm8260_get_rtc_time
id|tqm8260_get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
id|cpm2_map_t
op_star
)paren
id|CPM_MAP_ADDR
)paren
op_member_access_from_pointer
id|im_sit.sit_tmcnt
suffix:semicolon
)brace
r_void
id|__init
DECL|function|m82xx_board_init
id|m82xx_board_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Anything special for this platform */
id|ppc_md.set_rtc_time
op_assign
id|tqm8260_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|tqm8260_get_rtc_time
suffix:semicolon
)brace
eof
