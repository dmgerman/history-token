macro_line|#ifndef _ASM_PPC64_MEMORY_H_ 
DECL|macro|_ASM_PPC64_MEMORY_H_
mdefine_line|#define _ASM_PPC64_MEMORY_H_ 
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Arguably the bitops and *xchg operations don&squot;t imply any memory barrier&n; * or SMP ordering, but in fact a lot of drivers expect them to imply&n; * both, since they do on x86 cpus.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|EIEIO_ON_SMP
mdefine_line|#define EIEIO_ON_SMP&t;&quot;eieio&bslash;n&quot;
DECL|macro|ISYNC_ON_SMP
mdefine_line|#define ISYNC_ON_SMP&t;&quot;&bslash;n&bslash;tisync&quot;
macro_line|#else
DECL|macro|EIEIO_ON_SMP
mdefine_line|#define EIEIO_ON_SMP
DECL|macro|ISYNC_ON_SMP
mdefine_line|#define ISYNC_ON_SMP
macro_line|#endif
DECL|function|eieio
r_static
r_inline
r_void
id|eieio
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|isync
r_static
r_inline
r_void
id|isync
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;isync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|eieio_on_smp
mdefine_line|#define eieio_on_smp()&t;eieio()
DECL|macro|isync_on_smp
mdefine_line|#define isync_on_smp()&t;isync()
macro_line|#else
DECL|macro|eieio_on_smp
mdefine_line|#define eieio_on_smp()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|isync_on_smp
mdefine_line|#define isync_on_smp()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
macro_line|#endif
macro_line|#endif
eof
