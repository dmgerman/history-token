multiline_comment|/* $Id: timer.h,v 1.3 2000/05/09 17:40:15 davem Exp $&n; * timer.h: System timer definitions for sun5.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_TIMER_H
DECL|macro|_SPARC64_TIMER_H
mdefine_line|#define _SPARC64_TIMER_H
multiline_comment|/* How timers work:&n; *&n; * On uniprocessors we just use counter zero for the system wide&n; * ticker, this performs thread scheduling, clock book keeping,&n; * and runs timer based events.  Previously we used the Ultra&n; * %tick interrupt for this purpose.&n; *&n; * On multiprocessors we pick one cpu as the master level 10 tick&n; * processor.  Here this counter zero tick handles clock book&n; * keeping and timer events only.  Each Ultra has it&squot;s level&n; * 14 %tick interrupt set to fire off as well, even the master&n; * tick cpu runs this locally.  This ticker performs thread&n; * scheduling, system/user tick counting for the current thread,&n; * and also profiling if enabled.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Two timers, traditionally steered to PIL&squot;s 10 and 14 respectively.&n; * But since INO packets are used on sun5, we could use any PIL level&n; * we like, however for now we use the normal ones.&n; *&n; * The &squot;reg&squot; and &squot;interrupts&squot; properties for these live in nodes named&n; * &squot;counter-timer&squot;.  The first of three &squot;reg&squot; properties describe where&n; * the sun5_timer registers are.  The other two I have no idea. (XXX)&n; */
DECL|struct|sun5_timer
r_struct
id|sun5_timer
(brace
DECL|member|count0
id|u64
id|count0
suffix:semicolon
DECL|member|limit0
id|u64
id|limit0
suffix:semicolon
DECL|member|count1
id|u64
id|count1
suffix:semicolon
DECL|member|limit1
id|u64
id|limit1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUN5_LIMIT_ENABLE
mdefine_line|#define SUN5_LIMIT_ENABLE&t;0x80000000
DECL|macro|SUN5_LIMIT_TOZERO
mdefine_line|#define SUN5_LIMIT_TOZERO&t;0x40000000
DECL|macro|SUN5_LIMIT_ZRESTART
mdefine_line|#define SUN5_LIMIT_ZRESTART&t;0x20000000
DECL|macro|SUN5_LIMIT_CMASK
mdefine_line|#define SUN5_LIMIT_CMASK&t;0x1fffffff
multiline_comment|/* Given a HZ value, set the limit register to so that the timer IRQ&n; * gets delivered that often.&n; */
DECL|macro|SUN5_HZ_TO_LIMIT
mdefine_line|#define SUN5_HZ_TO_LIMIT(__hz)  (1000000/(__hz))
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
r_int
id|timer_tick_offset
suffix:semicolon
r_extern
r_void
id|timer_tick_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _SPARC64_TIMER_H */
eof
