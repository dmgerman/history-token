multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/domain.h&n; *&n; *  Copyright (C) 1999 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_DOMAIN_H
DECL|macro|__ASM_PROC_DOMAIN_H
mdefine_line|#define __ASM_PROC_DOMAIN_H
multiline_comment|/*&n; * Domain numbers&n; *&n; *  DOMAIN_IO     - domain 2 includes all IO only&n; *  DOMAIN_KERNEL - domain 1 includes all kernel memory only&n; *  DOMAIN_USER   - domain 0 includes all user memory only&n; */
DECL|macro|DOMAIN_USER
mdefine_line|#define DOMAIN_USER&t;0
DECL|macro|DOMAIN_KERNEL
mdefine_line|#define DOMAIN_KERNEL&t;1
DECL|macro|DOMAIN_TABLE
mdefine_line|#define DOMAIN_TABLE&t;1
DECL|macro|DOMAIN_IO
mdefine_line|#define DOMAIN_IO&t;2
multiline_comment|/*&n; * Domain types&n; */
DECL|macro|DOMAIN_NOACCESS
mdefine_line|#define DOMAIN_NOACCESS&t;0
DECL|macro|DOMAIN_CLIENT
mdefine_line|#define DOMAIN_CLIENT&t;1
DECL|macro|DOMAIN_MANAGER
mdefine_line|#define DOMAIN_MANAGER&t;3
DECL|macro|domain_val
mdefine_line|#define domain_val(dom,type)&t;((type) &lt;&lt; 2*(dom))
DECL|macro|set_domain
mdefine_line|#define set_domain(x)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;mcr&t;p15, 0, %0, c3, c0&t;@ set domain&quot;&t;&bslash;&n;&t;  : : &quot;r&quot; (x));&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|modify_domain
mdefine_line|#define modify_domain(dom,type)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int domain = current-&gt;thread.domain;&t;&bslash;&n;&t;domain &amp;= ~domain_val(dom, DOMAIN_MANAGER);&t;&bslash;&n;&t;domain |= domain_val(dom, type);&t;&t;&bslash;&n;&t;current-&gt;thread.domain = domain;&t;&t;&bslash;&n;&t;set_domain(current-&gt;thread.domain);&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
eof
