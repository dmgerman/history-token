multiline_comment|/*&n; * Debug macros for run-time debugging.&n; * Turned on/off with CONFIG_RUNTIME_DEBUG option.&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef _ASM_DEBUG_H
DECL|macro|_ASM_DEBUG_H
mdefine_line|#define _ASM_DEBUG_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * run-time macros for catching spurious errors.  Eable CONFIG_RUNTIME_DEBUG in&n; * kernel hacking config menu to use them.&n; *&n; * Use them as run-time debugging aid.  NEVER USE THEM AS ERROR HANDLING CODE!!!&n; */
macro_line|#ifdef CONFIG_RUNTIME_DEBUG
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|db_assert
mdefine_line|#define db_assert(x)  if (!(x)) { &bslash;&n;&t;panic(&quot;assertion failed at %s:%d: %s&quot;, __FILE__, __LINE__, #x); }
DECL|macro|db_warn
mdefine_line|#define db_warn(x)  if (!(x)) { &bslash;&n;&t;printk(KERN_WARNING &quot;warning at %s:%d: %s&quot;, __FILE__, __LINE__, #x); }
DECL|macro|db_verify
mdefine_line|#define db_verify(x, y) db_assert(x y)
DECL|macro|db_verify_warn
mdefine_line|#define db_verify_warn(x, y) db_warn(x y)
DECL|macro|db_run
mdefine_line|#define db_run(x)  do { x; } while (0)
macro_line|#else
DECL|macro|db_assert
mdefine_line|#define db_assert(x)
DECL|macro|db_warn
mdefine_line|#define db_warn(x)
DECL|macro|db_verify
mdefine_line|#define db_verify(x, y) x
DECL|macro|db_verify_warn
mdefine_line|#define db_verify_warn(x, y) x
DECL|macro|db_run
mdefine_line|#define db_run(x)
macro_line|#endif
macro_line|#endif /* _ASM_DEBUG_H */
eof
