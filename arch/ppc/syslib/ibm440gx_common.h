multiline_comment|/*&n; * arch/ppc/kernel/ibm440gx_common.h&n; *&n; * PPC440GX system library&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2003, 2004 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_SYSLIB_IBM440GX_COMMON_H
DECL|macro|__PPC_SYSLIB_IBM440GX_COMMON_H
mdefine_line|#define __PPC_SYSLIB_IBM440GX_COMMON_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;syslib/ibm44x_common.h&gt;
multiline_comment|/*&n; * Please, refer to the Figure 14.1 in 440GX user manual&n; *&n; * if internal UART clock is used, ser_clk is ignored&n; */
r_void
id|ibm440gx_get_clocks
c_func
(paren
r_struct
id|ibm44x_clocks
op_star
comma
r_int
r_int
id|sys_clk
comma
r_int
r_int
id|ser_clk
)paren
id|__init
suffix:semicolon
multiline_comment|/* Enable L2 cache */
r_void
id|ibm440gx_l2c_enable
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* Disable L2 cache */
r_void
id|ibm440gx_l2c_disable
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* Enable/disable L2 cache for a particular chip revision */
r_void
id|ibm440gx_l2c_setup
c_func
(paren
r_struct
id|ibm44x_clocks
op_star
)paren
id|__init
suffix:semicolon
multiline_comment|/* Get Ethernet Group */
r_int
id|ibm440gx_get_eth_grp
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* Set Ethernet Group */
r_void
id|ibm440gx_set_eth_grp
c_func
(paren
r_int
id|group
)paren
id|__init
suffix:semicolon
multiline_comment|/* Enable TAH devices */
r_void
id|ibm440gx_tah_enable
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* Add L2C info to /proc/cpuinfo */
r_int
id|ibm440gx_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __PPC_SYSLIB_IBM440GX_COMMON_H */
macro_line|#endif /* __KERNEL__ */
eof
