multiline_comment|/*&n; * include/asm-sh/machvec_init.h&n; *&n; * Copyright 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * This file has goodies to help simplify instantiation of machine vectors.&n; */
macro_line|#ifndef __SH_MACHVEC_INIT_H
DECL|macro|__SH_MACHVEC_INIT_H
mdefine_line|#define __SH_MACHVEC_INIT_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * In a GENERIC kernel, we have lots of these vectors floating about,&n; * all but one of which we want to go away.  In a non-GENERIC kernel,&n; * we want only one, ever.&n; *&n; * Accomplish this in the GENERIC kernel by puting all of the vectors&n; * in the .init.data section where they&squot;ll go away.  We&squot;ll copy the&n; * one we want to the real alpha_mv vector in setup_arch.&n; *&n; * Accomplish this in a non-GENERIC kernel by ifdef&squot;ing out all but&n; * one of the vectors, which will not reside in .init.data.  We then&n; * alias this one vector to alpha_mv, so no copy is needed.&n; *&n; * Upshot: set __initdata to nothing for non-GENERIC kernels.&n; *&n; * Note we do the same thing for the UNKNOWN kernel, as we need to write&n; * to the machine vector while setting it up.&n; */
macro_line|#if defined(CONFIG_SH_GENERIC) || defined(CONFIG_SH_UNKNOWN)
DECL|macro|__initmv
mdefine_line|#define __initmv __attribute__((unused,__section__ (&quot;.machvec.init&quot;)))
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(x)
macro_line|#else
DECL|macro|__initmv
mdefine_line|#define __initmv
multiline_comment|/* GCC actually has a syntax for defining aliases, but is under some&n;   delusion that you shouldn&squot;t be able to declare it extern somewhere&n;   else beforehand.  Fine.  We&squot;ll do it ourselves.  */
macro_line|#if 0
mdefine_line|#define ALIAS_MV(system) &bslash;&n;  struct sh_machine_vector sh_mv __attribute__((alias(&quot;mv_&quot;#system)));
macro_line|#else
DECL|macro|ALIAS_MV
mdefine_line|#define ALIAS_MV(system) &bslash;&n;  asm(&quot;.global sh_mv&bslash;nsh_mv = mv_&quot;#system );
macro_line|#endif
macro_line|#endif /* GENERIC */
macro_line|#endif /* __SH_MACHVEC_INIT_H */
eof
