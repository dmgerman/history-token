multiline_comment|/* $Id: pil.h,v 1.1 2002/01/23 11:27:36 davem Exp $ */
macro_line|#ifndef _SPARC64_PIL_H
DECL|macro|_SPARC64_PIL_H
mdefine_line|#define _SPARC64_PIL_H
multiline_comment|/* To avoid some locking problems, we hard allocate certain PILs&n; * for SMP cross call messages that must do a etrap/rtrap.&n; *&n; * A cli() does not block the cross call delivery, so when SMP&n; * locking is an issue we reschedule the event into a PIL interrupt&n; * which is blocked by cli().&n; *&n; * In fact any XCALL which has to etrap/rtrap has a problem because&n; * it is difficult to prevent rtrap from running BH&squot;s, and that would&n; * need to be done if the XCALL arrived while %pil==15.&n; */
DECL|macro|PIL_SMP_CALL_FUNC
mdefine_line|#define PIL_SMP_CALL_FUNC&t;1
DECL|macro|PIL_SMP_RECEIVE_SIGNAL
mdefine_line|#define PIL_SMP_RECEIVE_SIGNAL&t;2
DECL|macro|PIL_SMP_CAPTURE
mdefine_line|#define PIL_SMP_CAPTURE&t;&t;3
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PIL_RESERVED
mdefine_line|#define PIL_RESERVED(PIL)&t;((PIL) == PIL_SMP_CALL_FUNC || &bslash;&n;&t;&t;&t;&t; (PIL) == PIL_SMP_RECEIVE_SIGNAL || &bslash;&n;&t;&t;&t;&t; (PIL) == PIL_SMP_CAPTURE)
macro_line|#endif
macro_line|#endif /* !(_SPARC64_PIL_H) */
eof
