multiline_comment|/*&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * Copyright (C) 1997, 01, 05 Ralf Baechle&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * Copyright (C) 2002 Momentum Computer Inc.&n; * Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; *&n; * Louis Hamilton, Red Hat, Inc.&n; * hamilton@redhat.com  [MIPS64 modifications]&n; *&n; * Copyright 2004 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Author: Manish Lachwani, mlachwani@mvista.com&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|function|momenco_ocelot_restart
r_void
id|momenco_ocelot_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
multiline_comment|/* base address of timekeeper portion of part */
r_void
op_star
id|nvram
op_assign
(paren
r_void
op_star
)paren
l_int|0xfc807000L
suffix:semicolon
multiline_comment|/* Ask the NVRAM/RTC/watchdog chip to assert reset in 1/16 second */
id|writeb
c_func
(paren
l_int|0x84
comma
id|nvram
op_plus
l_int|0xff7
)paren
suffix:semicolon
multiline_comment|/* wait for the watchdog to go off */
id|mdelay
c_func
(paren
l_int|100
op_plus
(paren
l_int|1000
op_div
l_int|16
)paren
)paren
suffix:semicolon
multiline_comment|/* if the watchdog fails for some reason, let people know */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Watchdog reset failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|momenco_ocelot_halt
r_void
id|momenco_ocelot_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;&bslash;n** You can safely turn off the power&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
DECL|function|momenco_ocelot_power_off
r_void
id|momenco_ocelot_power_off
c_func
(paren
r_void
)paren
(brace
id|momenco_ocelot_halt
c_func
(paren
)paren
suffix:semicolon
)brace
eof
