multiline_comment|/*&n; * arch/ppc/syslib/ibm440gp_common.h&n; *&n; * PPC440GP system library&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2003 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_SYSLIB_IBM440GP_COMMON_H
DECL|macro|__PPC_SYSLIB_IBM440GP_COMMON_H
mdefine_line|#define __PPC_SYSLIB_IBM440GP_COMMON_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * All clocks are in Hz&n; */
DECL|struct|ibm440gp_clocks
r_struct
id|ibm440gp_clocks
(brace
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* CPUCoreClk */
DECL|member|plb
r_int
r_int
id|plb
suffix:semicolon
multiline_comment|/* PLBClk */
DECL|member|opb
r_int
r_int
id|opb
suffix:semicolon
multiline_comment|/* OPBClk */
DECL|member|ebc
r_int
r_int
id|ebc
suffix:semicolon
multiline_comment|/* PerClk */
DECL|member|uart
r_int
r_int
id|uart
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Please, refer to the Figure 13.1 in 440GP user manual&n; * &n; * if internal UART clock is used, ser_clk is ignored&n; */
r_void
id|ibm440gp_get_clocks
c_func
(paren
r_struct
id|ibm440gp_clocks
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
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __PPC_SYSLIB_IBM440GP_COMMON_H */
macro_line|#endif /* __KERNEL__ */
eof
