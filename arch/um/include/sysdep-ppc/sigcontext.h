multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __SYS_SIGCONTEXT_PPC_H
DECL|macro|__SYS_SIGCONTEXT_PPC_H
mdefine_line|#define __SYS_SIGCONTEXT_PPC_H
DECL|macro|DSISR_WRITE
mdefine_line|#define DSISR_WRITE 0x02000000
DECL|macro|SC_FAULT_ADDR
mdefine_line|#define SC_FAULT_ADDR(sc) ({ &bslash;&n;&t;&t;struct sigcontext_struct *_sc = (sc); &bslash;&n;&t;&t;long retval = -1; &bslash;&n;&t;&t;switch (_sc-&gt;regs-&gt;trap) { &bslash;&n;&t;&t;case 0x300: &bslash;&n;&t;&t;&t;/* data exception */ &bslash;&n;&t;&t;&t;retval = _sc-&gt;regs-&gt;dar; &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;case 0x400: &bslash;&n;&t;&t;&t;/* instruction exception */ &bslash;&n;&t;&t;&t;retval = _sc-&gt;regs-&gt;nip; &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;default: &bslash;&n;&t;&t;&t;panic(&quot;SC_FAULT_ADDR: unhandled trap type&bslash;n&quot;); &bslash;&n;&t;&t;} &bslash;&n;&t;&t;retval; &bslash;&n;&t;})
DECL|macro|SC_FAULT_WRITE
mdefine_line|#define SC_FAULT_WRITE(sc) ({ &bslash;&n;&t;&t;struct sigcontext_struct *_sc = (sc); &bslash;&n;&t;&t;long retval = -1; &bslash;&n;&t;&t;switch (_sc-&gt;regs-&gt;trap) { &bslash;&n;&t;&t;case 0x300: &bslash;&n;&t;&t;&t;/* data exception */ &bslash;&n;&t;&t;&t;retval = !!(_sc-&gt;regs-&gt;dsisr &amp; DSISR_WRITE); &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;case 0x400: &bslash;&n;&t;&t;&t;/* instruction exception: not a write */ &bslash;&n;&t;&t;&t;retval = 0; &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;default: &bslash;&n;&t;&t;&t;panic(&quot;SC_FAULT_ADDR: unhandled trap type&bslash;n&quot;); &bslash;&n;&t;&t;} &bslash;&n;&t;&t;retval; &bslash;&n;&t;})
DECL|macro|SC_IP
mdefine_line|#define SC_IP(sc) ((sc)-&gt;regs-&gt;nip)
DECL|macro|SC_SP
mdefine_line|#define SC_SP(sc) ((sc)-&gt;regs-&gt;gpr[1])
DECL|macro|SEGV_IS_FIXABLE
mdefine_line|#define SEGV_IS_FIXABLE(sc) (1)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
