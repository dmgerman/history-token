multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;nap.h -- Marconi/NAP support.&n; *&n; * &t;(C) Copyright 2001, SnapGear (www.snapgear.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;nap_h
DECL|macro|nap_h
mdefine_line|#define&t;nap_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/****************************************************************************/
macro_line|#ifdef CONFIG_MARCONINAP
multiline_comment|/****************************************************************************/
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
macro_line|#endif
multiline_comment|/*&n; *&t;Command to support selecting RS232 or RS422 mode on the&n; *&t;second COM port.&n; */
DECL|macro|TIOCSET422
mdefine_line|#define&t;TIOCSET422&t;0x4d01&t;&t;/* Set port mode 232 or 422 */
DECL|macro|TIOCGET422
mdefine_line|#define&t;TIOCGET422&t;0x4d02&t;&t;/* Get current port mode */
multiline_comment|/*&n; *&t;Low level control of the RS232/422 enable.&n; */
DECL|macro|MCFPP_PA11
mdefine_line|#define&t;MCFPP_PA11&t;0x0800
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; *&t;RS232/422 control is via the single PA11 line. Low is the RS422&n; *&t;enable, high is RS232 mode.&n; */
DECL|function|mcf_getpa
r_static
id|__inline__
r_int
r_int
id|mcf_getpa
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
DECL|function|mcf_setpa
r_static
id|__inline__
r_void
id|mcf_setpa
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
r_int
r_int
id|flags
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
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|pp
op_assign
(paren
op_star
id|pp
op_amp
op_complement
id|mask
)paren
op_or
id|bits
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/****************************************************************************/
macro_line|#if defined(CONFIG_M5272)
multiline_comment|/*&n; *&t;Marconi/NAP based hardware. DTR/DCD lines are wired to GPB lines.&n; */
DECL|macro|MCFPP_DCD0
mdefine_line|#define&t;MCFPP_DCD0&t;0x0080
DECL|macro|MCFPP_DCD1
mdefine_line|#define&t;MCFPP_DCD1&t;0x0020
DECL|macro|MCFPP_DTR0
mdefine_line|#define&t;MCFPP_DTR0&t;0x0040
DECL|macro|MCFPP_DTR1
mdefine_line|#define&t;MCFPP_DTR1&t;0x0010
macro_line|#ifndef __ASSEMBLY__
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
id|MCFSIM_PBDAT
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
id|MCFSIM_PBDAT
)paren
suffix:semicolon
op_star
id|pp
op_assign
(paren
op_star
id|pp
op_amp
op_complement
id|mask
)paren
op_or
id|bits
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* CONFIG_M5272 */
multiline_comment|/****************************************************************************/
macro_line|#endif /* CONFIG_MARCONINAP */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* nap_h */
eof
