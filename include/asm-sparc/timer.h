multiline_comment|/* $Id: timer.h,v 1.21 1999/04/20 13:22:51 anton Exp $&n; * timer.h:  Definitions for the timer chips on the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _SPARC_TIMER_H
DECL|macro|_SPARC_TIMER_H
mdefine_line|#define _SPARC_TIMER_H
macro_line|#include &lt;asm/system.h&gt;  /* For SUN4M_NCPUS */
macro_line|#include &lt;asm/sun4paddr.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
multiline_comment|/* Timer structures. The interrupt timer has two properties which&n; * are the counter (which is handled in do_timer in sched.c) and the limit.&n; * This limit is where the timer&squot;s counter &squot;wraps&squot; around. Oddly enough,&n; * the sun4c timer when it hits the limit wraps back to 1 and not zero&n; * thus when calculating the value at which it will fire a microsecond you&n; * must adjust by one.  Thanks SUN for designing such great hardware ;(&n; */
multiline_comment|/* Note that I am only going to use the timer that interrupts at&n; * Sparc IRQ 10.  There is another one available that can fire at&n; * IRQ 14. Currently it is left untouched, we keep the PROM&squot;s limit&n; * register value and let the prom take these interrupts.  This allows&n; * L1-A to work.&n; */
DECL|struct|sun4c_timer_info
r_struct
id|sun4c_timer_info
(brace
DECL|member|cur_count10
id|__volatile__
r_int
r_int
id|cur_count10
suffix:semicolon
DECL|member|timer_limit10
id|__volatile__
r_int
r_int
id|timer_limit10
suffix:semicolon
DECL|member|cur_count14
id|__volatile__
r_int
r_int
id|cur_count14
suffix:semicolon
DECL|member|timer_limit14
id|__volatile__
r_int
r_int
id|timer_limit14
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUN4C_TIMER_PHYSADDR
mdefine_line|#define SUN4C_TIMER_PHYSADDR   0xf3000000
macro_line|#ifdef CONFIG_SUN4
DECL|macro|SUN_TIMER_PHYSADDR
mdefine_line|#define SUN_TIMER_PHYSADDR SUN4_300_TIMER_PHYSADDR
macro_line|#else
DECL|macro|SUN_TIMER_PHYSADDR
mdefine_line|#define SUN_TIMER_PHYSADDR SUN4C_TIMER_PHYSADDR
macro_line|#endif
multiline_comment|/* A sun4m has two blocks of registers which are probably of the same&n; * structure. LSI Logic&squot;s L64851 is told to _decrement_ from the limit&n; * value. Aurora behaves similarly but its limit value is compacted in&n; * other fashion (it&squot;s wider). Documented fields are defined here.&n; */
multiline_comment|/* As with the interrupt register, we have two classes of timer registers&n; * which are per-cpu and master.  Per-cpu timers only hit that cpu and are&n; * only level 14 ticks, master timer hits all cpus and is level 10.&n; */
DECL|macro|SUN4M_PRM_CNT_L
mdefine_line|#define SUN4M_PRM_CNT_L       0x80000000
DECL|macro|SUN4M_PRM_CNT_LVALUE
mdefine_line|#define SUN4M_PRM_CNT_LVALUE  0x7FFFFC00
DECL|struct|sun4m_timer_percpu_info
r_struct
id|sun4m_timer_percpu_info
(brace
DECL|member|l14_timer_limit
id|__volatile__
r_int
r_int
id|l14_timer_limit
suffix:semicolon
multiline_comment|/* Initial value is 0x009c4000 */
DECL|member|l14_cur_count
id|__volatile__
r_int
r_int
id|l14_cur_count
suffix:semicolon
multiline_comment|/* This register appears to be write only and/or inaccessible&n;   * on Uni-Processor sun4m machines.&n;   */
DECL|member|l14_limit_noclear
id|__volatile__
r_int
r_int
id|l14_limit_noclear
suffix:semicolon
multiline_comment|/* Data access error is here */
DECL|member|cntrl
id|__volatile__
r_int
r_int
id|cntrl
suffix:semicolon
multiline_comment|/* =1 after POST on Aurora */
DECL|member|space
id|__volatile__
r_int
r_char
id|space
(braket
id|PAGE_SIZE
op_minus
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sun4m_timer_regs
r_struct
id|sun4m_timer_regs
(brace
DECL|member|cpu_timers
r_struct
id|sun4m_timer_percpu_info
id|cpu_timers
(braket
id|SUN4M_NCPUS
)braket
suffix:semicolon
DECL|member|l10_timer_limit
r_volatile
r_int
r_int
id|l10_timer_limit
suffix:semicolon
DECL|member|l10_cur_count
r_volatile
r_int
r_int
id|l10_cur_count
suffix:semicolon
multiline_comment|/* Again, this appears to be write only and/or inaccessible&n;&t; * on uni-processor sun4m machines.&n;&t; */
DECL|member|l10_limit_noclear
r_volatile
r_int
r_int
id|l10_limit_noclear
suffix:semicolon
multiline_comment|/* This register too, it must be magic. */
DECL|member|foobar
r_volatile
r_int
r_int
id|foobar
suffix:semicolon
DECL|member|cfg
r_volatile
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/* equals zero at boot time... */
)brace
suffix:semicolon
r_extern
r_struct
id|sun4m_timer_regs
op_star
id|sun4m_timers
suffix:semicolon
DECL|macro|SUN4D_PRM_CNT_L
mdefine_line|#define SUN4D_PRM_CNT_L       0x80000000
DECL|macro|SUN4D_PRM_CNT_LVALUE
mdefine_line|#define SUN4D_PRM_CNT_LVALUE  0x7FFFFC00
DECL|struct|sun4d_timer_regs
r_struct
id|sun4d_timer_regs
(brace
DECL|member|l10_timer_limit
r_volatile
r_int
r_int
id|l10_timer_limit
suffix:semicolon
DECL|member|l10_cur_countx
r_volatile
r_int
r_int
id|l10_cur_countx
suffix:semicolon
DECL|member|l10_limit_noclear
r_volatile
r_int
r_int
id|l10_limit_noclear
suffix:semicolon
DECL|member|ctrl
r_volatile
r_int
r_int
id|ctrl
suffix:semicolon
DECL|member|l10_cur_count
r_volatile
r_int
r_int
id|l10_cur_count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sun4d_timer_regs
op_star
id|sun4d_timers
suffix:semicolon
r_extern
id|__volatile__
r_int
r_int
op_star
id|master_l10_counter
suffix:semicolon
r_extern
id|__volatile__
r_int
r_int
op_star
id|master_l10_limit
suffix:semicolon
multiline_comment|/* FIXME: Make do_[gs]ettimeofday btfixup calls */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|bus_do_settimeofday
comma
r_struct
id|timeval
op_star
id|tv
)paren
DECL|macro|bus_do_settimeofday
mdefine_line|#define bus_do_settimeofday(tv) BTFIXUP_CALL(bus_do_settimeofday)(tv)
macro_line|#endif /* !(_SPARC_TIMER_H) */
eof
