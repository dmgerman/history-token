multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __CHOOSE_MODE_H__
DECL|macro|__CHOOSE_MODE_H__
mdefine_line|#define __CHOOSE_MODE_H__
macro_line|#include &quot;uml-config.h&quot;
macro_line|#if defined(UML_CONFIG_MODE_TT) &amp;&amp; defined(UML_CONFIG_MODE_SKAS)
DECL|macro|CHOOSE_MODE
mdefine_line|#define CHOOSE_MODE(tt, skas) (mode_tt ? (tt) : (skas))
macro_line|#elif defined(UML_CONFIG_MODE_SKAS)
DECL|macro|CHOOSE_MODE
mdefine_line|#define CHOOSE_MODE(tt, skas) (skas)
macro_line|#elif defined(UML_CONFIG_MODE_TT)
DECL|macro|CHOOSE_MODE
mdefine_line|#define CHOOSE_MODE(tt, skas) (tt)
macro_line|#endif
DECL|macro|CHOOSE_MODE_PROC
mdefine_line|#define CHOOSE_MODE_PROC(tt, skas, args...) &bslash;&n;&t;CHOOSE_MODE(tt(args), skas(args))
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
