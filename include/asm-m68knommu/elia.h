multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;elia.h -- Lineo (formerly Moreton Bay) eLIA platform support.&n; *&n; *&t;(C) Copyright 1999-2000, Moreton Bay (www.moreton.com.au)&n; *&t;(C) Copyright 1999-2000, Lineo (www.lineo.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;elia_h
DECL|macro|elia_h
mdefine_line|#define&t;elia_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#ifdef CONFIG_eLIA
multiline_comment|/*&n; *&t;The serial port DTR and DCD lines are also on the Parallel I/O&n; *&t;as well, so define those too.&n; */
DECL|macro|eLIA_DCD1
mdefine_line|#define&t;eLIA_DCD1&t;&t;0x0001
DECL|macro|eLIA_DCD0
mdefine_line|#define&t;eLIA_DCD0&t;&t;0x0002
DECL|macro|eLIA_DTR1
mdefine_line|#define&t;eLIA_DTR1&t;&t;0x0004
DECL|macro|eLIA_DTR0
mdefine_line|#define&t;eLIA_DTR0&t;&t;0x0008
DECL|macro|eLIA_PCIRESET
mdefine_line|#define&t;eLIA_PCIRESET&t;&t;0x0020
multiline_comment|/*&n; *&t;Kernel macros to set and unset the LEDs.&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|ppdata
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif&t;/* CONFIG_eLIA */
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* elia_h */
eof
