multiline_comment|/*&n; * arch/ppc/platforms/mpc5200.c&n; *&n; * OCP Definitions for the boards based on MPC5200 processor. Contains&n; * definitions for every common peripherals. (Mostly all but PSCs)&n; * &n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Copyright 2004 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/mpc52xx.h&gt;
multiline_comment|/* Here is the core_ocp struct.&n; * With all the devices common to all board. Even if port multiplexing is&n; * not setup for them (if the user don&squot;t want them, just don&squot;t select the&n; * config option). The potentially conflicting devices (like PSCs) goes in&n; * board specific file.&n; */
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* Terminating entry */
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
eof
