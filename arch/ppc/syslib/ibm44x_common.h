multiline_comment|/*&n; * arch/ppc/kernel/ibm44x_common.h&n; *&n; * PPC44x system library&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2003, 2004 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_SYSLIB_IBM44x_COMMON_H
DECL|macro|__PPC_SYSLIB_IBM44x_COMMON_H
mdefine_line|#define __PPC_SYSLIB_IBM44x_COMMON_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * All clocks are in Hz&n; */
DECL|struct|ibm44x_clocks
r_struct
id|ibm44x_clocks
(brace
DECL|member|vco
r_int
r_int
id|vco
suffix:semicolon
multiline_comment|/* VCO, 0 if system PLL is bypassed */
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
DECL|member|uart0
r_int
r_int
id|uart0
suffix:semicolon
DECL|member|uart1
r_int
r_int
id|uart1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* common 44x platform init */
r_void
id|ibm44x_platform_init
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* initialize decrementer and tick-related variables */
r_void
id|ibm44x_calibrate_decr
c_func
(paren
r_int
r_int
id|freq
)paren
id|__init
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __PPC_SYSLIB_IBM44x_COMMON_H */
macro_line|#endif /* __KERNEL__ */
eof
