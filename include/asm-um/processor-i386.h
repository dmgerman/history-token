multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PROCESSOR_I386_H
DECL|macro|__UM_PROCESSOR_I386_H
mdefine_line|#define __UM_PROCESSOR_I386_H
r_extern
r_int
id|cpu_has_xmm
suffix:semicolon
r_extern
r_int
id|cpu_has_cmov
suffix:semicolon
DECL|struct|arch_thread
r_struct
id|arch_thread
(brace
DECL|member|debugregs
r_int
r_int
id|debugregs
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|debugregs_seq
r_int
id|debugregs_seq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_ARCH_THREAD
mdefine_line|#define INIT_ARCH_THREAD { .debugregs  &t;&t;= { [ 0 ... 7 ] = 0 }, &bslash;&n;                           .debugregs_seq&t;= 0 }
macro_line|#include &quot;asm/arch/user.h&quot;
macro_line|#include &quot;asm/processor-generic.h&quot;
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
