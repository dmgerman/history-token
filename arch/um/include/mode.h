multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __MODE_H__
DECL|macro|__MODE_H__
mdefine_line|#define __MODE_H__
macro_line|#include &quot;uml-config.h&quot;
macro_line|#ifdef UML_CONFIG_MODE_TT
macro_line|#include &quot;../kernel/tt/include/mode.h&quot;
macro_line|#endif
macro_line|#ifdef UML_CONFIG_MODE_SKAS
macro_line|#include &quot;../kernel/skas/include/mode.h&quot;
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
