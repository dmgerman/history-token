multiline_comment|/*&n; *  linux/include/asm-arm/arch-clps711x/uncompress.h&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/io.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/hardware/clps7111.h&gt;
DECL|macro|CLPS7111_BASE
macro_line|#undef CLPS7111_BASE
DECL|macro|CLPS7111_BASE
mdefine_line|#define CLPS7111_BASE CLPS7111_PHYS_BASE
DECL|macro|barrier
mdefine_line|#define barrier()&t;&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(p)&t;&t;(*(unsigned long *)(p))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,p)&t;(*(unsigned long *)(p) = (v))
macro_line|#ifdef CONFIG_DEBUG_CLPS711X_UART2
DECL|macro|SYSFLGx
mdefine_line|#define SYSFLGx&t;SYSFLG2
DECL|macro|UARTDRx
mdefine_line|#define UARTDRx&t;UARTDR2
macro_line|#else
DECL|macro|SYSFLGx
mdefine_line|#define SYSFLGx&t;SYSFLG1
DECL|macro|UARTDRx
mdefine_line|#define UARTDRx&t;UARTDR1
macro_line|#endif
multiline_comment|/*&n; * This does not append a newline&n; */
DECL|function|puts
r_static
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_while
c_loop
(paren
id|clps_readl
c_func
(paren
id|SYSFLGx
)paren
op_amp
id|SYSFLG_UTXFF
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
id|c
comma
id|UARTDRx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
id|clps_readl
c_func
(paren
id|SYSFLGx
)paren
op_amp
id|SYSFLG_UTXFF
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|clps_writel
c_func
(paren
l_char|&squot;&bslash;r&squot;
comma
id|UARTDRx
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|clps_readl
c_func
(paren
id|SYSFLGx
)paren
op_amp
id|SYSFLG_UBUSY
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
