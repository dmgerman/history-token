multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;semp.h -- SecureEdge MP3 hardware platform support.&n; *&n; *&t;(C) Copyright 2001-2002, Greg Ungerer (gerg@snapgear.com).&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;semp3_h
DECL|macro|semp3_h
mdefine_line|#define&t;semp3_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/****************************************************************************/
macro_line|#ifdef CONFIG_SECUREEDGEMP3
multiline_comment|/****************************************************************************/
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
multiline_comment|/*&n; *&t;The ColdFire UARTs do not have any support for DTR/DCD lines.&n; *&t;We have wired them onto some of the parallel IO lines.&n; */
DECL|macro|MCFPP_DCD1
mdefine_line|#define&t;MCFPP_DCD1&t;0x0004
DECL|macro|MCFPP_DCD0
mdefine_line|#define&t;MCFPP_DCD0&t;0x0000&t;&t;/* No DCD line on port 0 */
DECL|macro|MCFPP_DTR1
mdefine_line|#define&t;MCFPP_DTR1&t;0x0080
DECL|macro|MCFPP_DTR0
mdefine_line|#define&t;MCFPP_DTR0&t;0x0000&t;&t;/* No DTR line on port 0 */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_volatile
r_int
r_int
id|ppdata
suffix:semicolon
multiline_comment|/*&n; *&t;These functions defined to give quasi generic access to the&n; *&t;PPIO bits used for DTR/DCD.&n; */
DECL|function|mcf_getppdata
r_static
id|__inline__
r_int
r_int
id|mcf_getppdata
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|pp
suffix:semicolon
id|pp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_PADAT
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
op_star
id|pp
suffix:semicolon
)brace
DECL|function|mcf_setppdata
r_static
id|__inline__
r_void
id|mcf_setppdata
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
id|bits
)paren
(brace
r_volatile
r_int
r_int
op_star
id|pp
suffix:semicolon
id|pp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_PADAT
)paren
suffix:semicolon
id|ppdata
op_assign
(paren
id|ppdata
op_amp
op_complement
id|mask
)paren
op_or
id|bits
suffix:semicolon
op_star
id|pp
op_assign
id|ppdata
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/****************************************************************************/
macro_line|#endif /* CONFIG_SECUREEDGEMP3 */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* semp3_h */
eof
