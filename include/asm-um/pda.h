multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PDA_X86_64_H
DECL|macro|__UM_PDA_X86_64_H
mdefine_line|#define __UM_PDA_X86_64_H
multiline_comment|/* XXX */
DECL|struct|foo
r_struct
id|foo
(brace
DECL|member|__softirq_pending
r_int
r_int
id|__softirq_pending
suffix:semicolon
DECL|member|__nmi_count
r_int
r_int
id|__nmi_count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|foo
id|me
suffix:semicolon
DECL|macro|read_pda
mdefine_line|#define read_pda(me) (&amp;me)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
