multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * include/asm-mips/ddb5xxx/debug.h&n; *     Some debug macros used by ddb code.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; ***********************************************************************&n; */
macro_line|#ifndef __ASM_DDB5XXX_DEBUG_H
DECL|macro|__ASM_DDB5XXX_DEBUG_H
mdefine_line|#define __ASM_DDB5XXX_DEBUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * macro for catching spurious errors.  Eable to LL_DEBUG in kernel hacking&n; * config menu.&n; */
macro_line|#ifdef CONFIG_LL_DEBUG
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|MIPS_ASSERT
mdefine_line|#define MIPS_ASSERT(x)  if (!(x)) { panic(&quot;MIPS_ASSERT failed at %s:%d&bslash;n&quot;, __FILE__, __LINE__); }
DECL|macro|MIPS_VERIFY
mdefine_line|#define MIPS_VERIFY(x, y) MIPS_ASSERT(x y)
DECL|macro|MIPS_DEBUG
mdefine_line|#define MIPS_DEBUG(x)  do { x; } while (0)
macro_line|#else
DECL|macro|MIPS_ASSERT
mdefine_line|#define MIPS_ASSERT(x)
DECL|macro|MIPS_VERIFY
mdefine_line|#define MIPS_VERIFY(x, y) x
DECL|macro|MIPS_DEBUG
mdefine_line|#define MIPS_DEBUG(x)
macro_line|#endif
macro_line|#endif /* __ASM_DDB5XXX_DEBUG_H */
eof
