macro_line|#ifndef _ASMPARISC_SIGCONTEXT_H
DECL|macro|_ASMPARISC_SIGCONTEXT_H
mdefine_line|#define _ASMPARISC_SIGCONTEXT_H
DECL|macro|PARISC_SC_FLAG_ONSTACK
mdefine_line|#define PARISC_SC_FLAG_ONSTACK 1&lt;&lt;0
DECL|macro|PARISC_SC_FLAG_IN_SYSCALL
mdefine_line|#define PARISC_SC_FLAG_IN_SYSCALL 1&lt;&lt;1
multiline_comment|/* We will add more stuff here as it becomes necessary, until we know&n;   it works. */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_flags
r_int
r_int
id|sc_flags
suffix:semicolon
DECL|member|sc_gr
r_int
r_int
id|sc_gr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PSW in sc_gr[0] */
DECL|member|sc_fr
r_int
r_int
r_int
id|sc_fr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* FIXME, do we need other state info? */
DECL|member|sc_iasq
r_int
r_int
id|sc_iasq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sc_iaoq
r_int
r_int
id|sc_iaoq
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sc_sar
r_int
r_int
id|sc_sar
suffix:semicolon
multiline_comment|/* cr11 */
)brace
suffix:semicolon
macro_line|#endif
eof
