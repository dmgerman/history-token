multiline_comment|/* $Id: ttable.h,v 1.16 2001/03/28 10:56:34 davem Exp $ */
macro_line|#ifndef _SPARC64_TTABLE_H
DECL|macro|_SPARC64_TTABLE_H
mdefine_line|#define _SPARC64_TTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/asm_offsets.h&gt;
macro_line|#include &lt;asm/utrap.h&gt;
DECL|macro|BOOT_KERNEL
mdefine_line|#define BOOT_KERNEL b sparc64_boot; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* We need a &quot;cleaned&quot; instruction... */
DECL|macro|CLEAN_WINDOW
mdefine_line|#define CLEAN_WINDOW&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rdpr&t;%cleanwin, %l0;&t;&t;add&t;%l0, 1, %l0;&t;&t;&bslash;&n;&t;wrpr&t;%l0, 0x0, %cleanwin;&t;&t;&t;&t;&t;&bslash;&n;&t;clr&t;%o0;&t;clr&t;%o1;&t;clr&t;%o2;&t;clr&t;%o3;&t;&bslash;&n;&t;clr&t;%o4;&t;clr&t;%o5;&t;clr&t;%o6;&t;clr&t;%o7;&t;&bslash;&n;&t;clr&t;%l0;&t;clr&t;%l1;&t;clr&t;%l2;&t;clr&t;%l3;&t;&bslash;&n;&t;clr&t;%l4;&t;clr&t;%l5;&t;clr&t;%l6;&t;clr&t;%l7;&t;&bslash;&n;&t;retry;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;
DECL|macro|TRAP
mdefine_line|#define TRAP(routine)&t;&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_SAVEFPU
mdefine_line|#define TRAP_SAVEFPU(routine)&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, do_fptrap;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_NOSAVE
mdefine_line|#define TRAP_NOSAVE(routine)&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, routine;&t;&t;&t;&t;&bslash;&n;&t; nop;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop;
DECL|macro|TRAPTL1
mdefine_line|#define TRAPTL1(routine)&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etraptl1;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_ARG
mdefine_line|#define TRAP_ARG(routine, arg)&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; mov&t;arg, %o1;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|TRAPTL1_ARG
mdefine_line|#define TRAPTL1_ARG(routine, arg)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etraptl1;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; mov&t;arg, %o1;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|SYSCALL_TRAP
mdefine_line|#define SYSCALL_TRAP(routine, systbl)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, scetrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, routine;&t;&t;&t;&t;&bslash;&n;&t; sethi&t;%hi(systbl), %l7;&t;&t;&t;&bslash;&n;&t;nop; nop; nop;
DECL|macro|INDIRECT_SOLARIS_SYSCALL
mdefine_line|#define INDIRECT_SOLARIS_SYSCALL(num)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, tl0_solaris + 0xc;&t;&t;&bslash;&n;&t; mov&t;num, %g1;&t;&t;&t;&t;&bslash;&n;&t;nop;nop;nop;
DECL|macro|TRAP_UTRAP
mdefine_line|#define TRAP_UTRAP(handler,lvl)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%g6 + AOFF_task_thread + AOFF_thread_utraps], %g1;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;brz,pn&t;%g1, utrap;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; or&t;%g7, %lo(109f), %g7;&t;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, utrap;&t;&t;&t;&t;&t;&t;&bslash;&n;109:&t; ldx&t;[%g1 + handler*8], %g1;&t;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, utrap_ill;&t;&t;&t;&t;&t;&bslash;&n;&t; mov&t;lvl, %o1;
macro_line|#ifdef CONFIG_SUNOS_EMUL
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall32, sunos_sys_table)
macro_line|#else
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP TRAP(sunos_syscall)
macro_line|#endif
DECL|macro|LINUX_32BIT_SYSCALL_TRAP
mdefine_line|#define&t;LINUX_32BIT_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall32, sys_call_table32)
DECL|macro|LINUX_64BIT_SYSCALL_TRAP
mdefine_line|#define LINUX_64BIT_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall, sys_call_table64)
DECL|macro|GETCC_TRAP
mdefine_line|#define GETCC_TRAP TRAP(getcc)
DECL|macro|SETCC_TRAP
mdefine_line|#define SETCC_TRAP TRAP(setcc)
macro_line|#ifdef CONFIG_SOLARIS_EMUL
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP TRAP(solaris_sparc_syscall)
macro_line|#else
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP TRAP(solaris_syscall)
macro_line|#endif
multiline_comment|/* FIXME: Write these actually */
DECL|macro|NETBSD_SYSCALL_TRAP
mdefine_line|#define NETBSD_SYSCALL_TRAP TRAP(netbsd_syscall)
DECL|macro|BREAKPOINT_TRAP
mdefine_line|#define BREAKPOINT_TRAP TRAP(breakpoint_trap)
DECL|macro|TRAP_IRQ
mdefine_line|#define TRAP_IRQ(routine, level)&t;&t;&t;&bslash;&n;&t;rdpr&t;%pil, %g2;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g0, 15, %pil;&t;&t;&t;&t;&bslash;&n;&t;b,pt&t;%xcc, etrap_irq;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;mov&t;level, %o0;&t;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o1;&t;&bslash;&n;&t;ba,a,pt&t;%xcc, rtrap_clr_l6;
DECL|macro|TICK_SMP_IRQ
mdefine_line|#define TICK_SMP_IRQ&t;&t;&t;&t;&t;&bslash;&n;&t;rdpr&t;%pil, %g2;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g0, 15, %pil;&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;b,pt&t;%xcc, etrap_irq;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;smp_percpu_timer_interrupt;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,a,pt&t;%xcc, rtrap_clr_l6;
DECL|macro|TRAP_IVEC
mdefine_line|#define TRAP_IVEC TRAP_NOSAVE(do_ivec)
DECL|macro|BTRAP
mdefine_line|#define BTRAP(lvl) TRAP_ARG(bad_trap, lvl)
DECL|macro|BTRAPTL1
mdefine_line|#define BTRAPTL1(lvl) TRAPTL1_ARG(bad_trap_tl1, lvl)
DECL|macro|FLUSH_WINDOW_TRAP
mdefine_line|#define FLUSH_WINDOW_TRAP&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flushw;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TNPC], %l1;&t;&bslash;&n;&t;add&t;%l1, 4, %l2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;stx&t;%l1, [%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TPC];&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap_clr_l6;&t;&t;&t;&t;&t;&bslash;&n;&t; stx&t;%l2, [%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TNPC];
multiline_comment|/* Before touching these macros, you owe it to yourself to go and&n; * see how arch/sparc64/kernel/winfixup.S works... -DaveM&n; *&n; * For the user cases we used to use the %asi register, but&n; * it turns out that the &quot;wr xxx, %asi&quot; costs ~5 cycles, so&n; * now we use immediate ASI loads and stores instead.  Kudos&n; * to Greg Onufer for pointing out this performance anomaly.&n; *&n; * Further note that we cannot use the g2, g4, g5, and g7 alternate&n; * globals in the spill routines, check out the save instruction in&n; * arch/sparc64/kernel/etrap.S to see what I mean about g2, and&n; * g4/g5 are the globals which are preserved by etrap processing&n; * for the caller of it.  The g7 register is the return pc for&n; * etrap.  Finally, g6 is the current thread register so we cannot&n; * us it in the spill handlers either.  Most of these rules do not&n; * apply to fill processing, only g6 is not usable.&n; */
multiline_comment|/* Normal kernel spill */
DECL|macro|SPILL_0_NORMAL
mdefine_line|#define SPILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;stx&t;%l0, [%sp + STACK_BIAS + 0x00];&t;&t;&bslash;&n;&t;stx&t;%l1, [%sp + STACK_BIAS + 0x08];&t;&t;&bslash;&n;&t;stx&t;%l2, [%sp + STACK_BIAS + 0x10];&t;&t;&bslash;&n;&t;stx&t;%l3, [%sp + STACK_BIAS + 0x18];&t;&t;&bslash;&n;&t;stx&t;%l4, [%sp + STACK_BIAS + 0x20];&t;&t;&bslash;&n;&t;stx&t;%l5, [%sp + STACK_BIAS + 0x28];&t;&t;&bslash;&n;&t;stx&t;%l6, [%sp + STACK_BIAS + 0x30];&t;&t;&bslash;&n;&t;stx&t;%l7, [%sp + STACK_BIAS + 0x38];&t;&t;&bslash;&n;&t;stx&t;%i0, [%sp + STACK_BIAS + 0x40];&t;&t;&bslash;&n;&t;stx&t;%i1, [%sp + STACK_BIAS + 0x48];&t;&t;&bslash;&n;&t;stx&t;%i2, [%sp + STACK_BIAS + 0x50];&t;&t;&bslash;&n;&t;stx&t;%i3, [%sp + STACK_BIAS + 0x58];&t;&t;&bslash;&n;&t;stx&t;%i4, [%sp + STACK_BIAS + 0x60];&t;&t;&bslash;&n;&t;stx&t;%i5, [%sp + STACK_BIAS + 0x68];&t;&t;&bslash;&n;&t;stx&t;%i6, [%sp + STACK_BIAS + 0x70];&t;&t;&bslash;&n;&t;stx&t;%i7, [%sp + STACK_BIAS + 0x78];&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit spill */
DECL|macro|SPILL_1_GENERIC
mdefine_line|#define SPILL_1_GENERIC(ASI)&t;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + 0x00, %g1;&t;&t;&bslash;&n;&t;stxa&t;%l0, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;mov&t;0x08, %g3;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%l1, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%l2, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%l3, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%l4, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%l5, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%l6, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%l7, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%i0, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%i1, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%i2, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%i3, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%i4, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%i5, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%i6, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stxa&t;%i7, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;saved;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;retry; nop; nop;&t;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_dax;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup;
multiline_comment|/* Normal 32bit spill */
DECL|macro|SPILL_2_GENERIC
mdefine_line|#define SPILL_2_GENERIC(ASI)&t;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l0, [%sp + %g0] ASI;&t;&t;&t;&bslash;&n;&t;mov&t;0x04, %g3;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l1, [%sp + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%sp, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l2, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%l3, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l4, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%l5, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l6, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%l7, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%i0, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%i1, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%i2, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%i3, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%i4, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%i5, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x08, %g1;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%i6, [%g1 + %g0] ASI;&t;&t;&t;&bslash;&n;&t;stwa&t;%i7, [%g1 + %g3] ASI;&t;&t;&t;&bslash;&n;&t;saved;&t;&t;&t;&t;&t;&t;&bslash;&n;        retry; nop; nop;&t;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_dax;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup;
DECL|macro|SPILL_1_NORMAL
mdefine_line|#define SPILL_1_NORMAL SPILL_1_GENERIC(ASI_AIUP)
DECL|macro|SPILL_2_NORMAL
mdefine_line|#define SPILL_2_NORMAL SPILL_2_GENERIC(ASI_AIUP)
DECL|macro|SPILL_3_NORMAL
mdefine_line|#define SPILL_3_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_4_NORMAL
mdefine_line|#define SPILL_4_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_5_NORMAL
mdefine_line|#define SPILL_5_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_6_NORMAL
mdefine_line|#define SPILL_6_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_7_NORMAL
mdefine_line|#define SPILL_7_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_0_OTHER
mdefine_line|#define SPILL_0_OTHER SPILL_0_NORMAL
DECL|macro|SPILL_1_OTHER
mdefine_line|#define SPILL_1_OTHER SPILL_1_GENERIC(ASI_AIUS)
DECL|macro|SPILL_2_OTHER
mdefine_line|#define SPILL_2_OTHER SPILL_2_GENERIC(ASI_AIUS)
DECL|macro|SPILL_3_OTHER
mdefine_line|#define SPILL_3_OTHER SPILL_3_NORMAL
DECL|macro|SPILL_4_OTHER
mdefine_line|#define SPILL_4_OTHER SPILL_4_NORMAL
DECL|macro|SPILL_5_OTHER
mdefine_line|#define SPILL_5_OTHER SPILL_5_NORMAL
DECL|macro|SPILL_6_OTHER
mdefine_line|#define SPILL_6_OTHER SPILL_6_NORMAL
DECL|macro|SPILL_7_OTHER
mdefine_line|#define SPILL_7_OTHER SPILL_7_NORMAL
multiline_comment|/* Normal kernel fill */
DECL|macro|FILL_0_NORMAL
mdefine_line|#define FILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x00], %l0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x08], %l1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x10], %l2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x18], %l3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x20], %l4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x28], %l5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x30], %l6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x38], %l7;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x40], %i0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x48], %i1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x50], %i2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x58], %i3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x60], %i4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x68], %i5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x70], %i6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x78], %i7;&t;&t;&bslash;&n;&t;restored; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit fill */
DECL|macro|FILL_1_GENERIC
mdefine_line|#define FILL_1_GENERIC(ASI)&t;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + 0x00, %g1;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g0] ASI, %l0;&t;&t;&t;&bslash;&n;&t;mov&t;0x08, %g2;&t;&t;&t;&t;&bslash;&n;&t;mov&t;0x10, %g3;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g2] ASI, %l1;&t;&t;&t;&bslash;&n;&t;mov&t;0x18, %g5;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g3] ASI, %l2;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g5] ASI, %l3;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x20, %g1;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g0] ASI, %l4;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g2] ASI, %l5;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g3] ASI, %l6;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g5] ASI, %l7;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x20, %g1;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g0] ASI, %i0;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g2] ASI, %i1;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g3] ASI, %i2;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g5] ASI, %i3;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x20, %g1;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g0] ASI, %i4;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g2] ASI, %i5;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g3] ASI, %i6;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%g1 + %g5] ASI, %i7;&t;&t;&t;&bslash;&n;&t;restored;&t;&t;&t;&t;&t;&bslash;&n;&t;retry; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_dax;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup;
multiline_comment|/* Normal 32bit fill */
DECL|macro|FILL_2_GENERIC
mdefine_line|#define FILL_2_GENERIC(ASI)&t;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + %g0] ASI, %l0;&t;&t;&t;&bslash;&n;&t;mov&t;0x04, %g2;&t;&t;&t;&t;&bslash;&n;&t;mov&t;0x08, %g3;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + %g2] ASI, %l1;&t;&t;&t;&bslash;&n;&t;mov&t;0x0c, %g5;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + %g3] ASI, %l2;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + %g5] ASI, %l3;&t;&t;&t;&bslash;&n;&t;add&t;%sp, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g0] ASI, %l4;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g2] ASI, %l5;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g3] ASI, %l6;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g5] ASI, %l7;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g0] ASI, %i0;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g2] ASI, %i1;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g3] ASI, %i2;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g5] ASI, %i3;&t;&t;&t;&bslash;&n;&t;add&t;%g1, 0x10, %g1;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g0] ASI, %i4;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g2] ASI, %i5;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g3] ASI, %i6;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%g1 + %g5] ASI, %i7;&t;&t;&t;&bslash;&n;&t;restored;&t;&t;&t;&t;&t;&bslash;&n;&t;retry; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_dax;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup;
DECL|macro|FILL_1_NORMAL
mdefine_line|#define FILL_1_NORMAL FILL_1_GENERIC(ASI_AIUP)
DECL|macro|FILL_2_NORMAL
mdefine_line|#define FILL_2_NORMAL FILL_2_GENERIC(ASI_AIUP)
DECL|macro|FILL_3_NORMAL
mdefine_line|#define FILL_3_NORMAL FILL_0_NORMAL
DECL|macro|FILL_4_NORMAL
mdefine_line|#define FILL_4_NORMAL FILL_0_NORMAL
DECL|macro|FILL_5_NORMAL
mdefine_line|#define FILL_5_NORMAL FILL_0_NORMAL
DECL|macro|FILL_6_NORMAL
mdefine_line|#define FILL_6_NORMAL FILL_0_NORMAL
DECL|macro|FILL_7_NORMAL
mdefine_line|#define FILL_7_NORMAL FILL_0_NORMAL
DECL|macro|FILL_0_OTHER
mdefine_line|#define FILL_0_OTHER FILL_0_NORMAL
DECL|macro|FILL_1_OTHER
mdefine_line|#define FILL_1_OTHER FILL_1_GENERIC(ASI_AIUS)
DECL|macro|FILL_2_OTHER
mdefine_line|#define FILL_2_OTHER FILL_2_GENERIC(ASI_AIUS)
DECL|macro|FILL_3_OTHER
mdefine_line|#define FILL_3_OTHER FILL_3_NORMAL
DECL|macro|FILL_4_OTHER
mdefine_line|#define FILL_4_OTHER FILL_4_NORMAL
DECL|macro|FILL_5_OTHER
mdefine_line|#define FILL_5_OTHER FILL_5_NORMAL
DECL|macro|FILL_6_OTHER
mdefine_line|#define FILL_6_OTHER FILL_6_NORMAL
DECL|macro|FILL_7_OTHER
mdefine_line|#define FILL_7_OTHER FILL_7_NORMAL
macro_line|#endif /* !(_SPARC64_TTABLE_H) */
eof
