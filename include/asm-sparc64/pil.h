multiline_comment|/* $Id: pil.h,v 1.1 2002/01/23 11:27:36 davem Exp $ */
macro_line|#ifndef _SPARC64_PIL_H
DECL|macro|_SPARC64_PIL_H
mdefine_line|#define _SPARC64_PIL_H
multiline_comment|/* To avoid some locking problems, we hard allocate certain PILs&n; * for SMP cross call messages.  cli() does not block the cross&n; * call delivery, so when SMP locking is an issue we reschedule&n; * the event into a PIL interrupt which is blocked by cli().&n; *&n; * XXX In fact the whole set of PILs used for hardware interrupts&n; * XXX may be allocated in this manner.  All of the devices can&n; * XXX happily sit at the same PIL.  We would then need only two&n; * XXX PILs, one for devices and one for the CPU local timer tick.&n; */
multiline_comment|/* None currently allocated, &squot;1&squot; is available for use. */
DECL|macro|PIL_SMP_1
mdefine_line|#define PIL_SMP_1&t;1
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PIL_RESERVED
mdefine_line|#define PIL_RESERVED(PIL)&t;((PIL) == PIL_SMP_1)
macro_line|#endif
macro_line|#endif /* !(_SPARC64_PIL_H) */
eof
