macro_line|#ifndef _ASM_IA64_GCC_INTRIN_H
DECL|macro|_ASM_IA64_GCC_INTRIN_H
mdefine_line|#define _ASM_IA64_GCC_INTRIN_H
multiline_comment|/*&n; *&n; * Copyright (C) 2002,2003 Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; * Copyright (C) 2002,2003 Suresh Siddha &lt;suresh.b.siddha@intel.com&gt;&n; *&n; */
multiline_comment|/* define this macro to get some asm stmts included in &squot;c&squot; files */
DECL|macro|ASM_SUPPORTED
mdefine_line|#define ASM_SUPPORTED
multiline_comment|/* Optimization barrier */
multiline_comment|/* The &quot;volatile&quot; is due to gcc bugs */
DECL|macro|ia64_barrier
mdefine_line|#define ia64_barrier()&t;asm volatile (&quot;&quot;:::&quot;memory&quot;)
DECL|macro|ia64_stop
mdefine_line|#define ia64_stop()&t;asm volatile (&quot;;;&quot;::)
DECL|macro|ia64_invala_gr
mdefine_line|#define ia64_invala_gr(regnum)&t;asm volatile (&quot;invala.e r%0&quot; :: &quot;i&quot;(regnum))
DECL|macro|ia64_invala_fr
mdefine_line|#define ia64_invala_fr(regnum)&t;asm volatile (&quot;invala.e f%0&quot; :: &quot;i&quot;(regnum))
r_extern
r_void
id|ia64_bad_param_for_setreg
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ia64_bad_param_for_getreg
(paren
r_void
)paren
suffix:semicolon
DECL|macro|ia64_setreg
mdefine_line|#define ia64_setreg(regnum, val)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (regnum) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case _IA64_REG_PSR_L:&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    asm volatile (&quot;mov psr.l=%0&quot; :: &quot;r&quot;(val) : &quot;memory&quot;);&t;&bslash;&n;&t;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case _IA64_REG_AR_KR0 ... _IA64_REG_AR_EC:&t;&t;&t;&t;&bslash;&n;&t;&t;    asm volatile (&quot;mov ar%0=%1&quot; ::&t;&t;&t;&t;&bslash;&n;&t;&t;    &t;&t;&t;  &quot;i&quot; (regnum - _IA64_REG_AR_KR0),&t;&bslash;&n;&t;&t;&t;&t;&t;  &quot;r&quot;(val): &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case _IA64_REG_CR_DCR ... _IA64_REG_CR_LRR1:&t;&t;&t;&bslash;&n;&t;&t;    asm volatile (&quot;mov cr%0=%1&quot; ::&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;          &quot;i&quot; (regnum - _IA64_REG_CR_DCR),&t;&bslash;&n;&t;&t;&t;&t;&t;  &quot;r&quot;(val): &quot;memory&quot; );&t;&t;&t;&bslash;&n;&t;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case _IA64_REG_SP:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    asm volatile (&quot;mov r12=%0&quot; ::&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    &t;&t;  &quot;r&quot;(val): &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case _IA64_REG_GP:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    asm volatile (&quot;mov gp=%0&quot; :: &quot;r&quot;(val) : &quot;memory&quot;);&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    ia64_bad_param_for_setreg();&t;&t;&t;&t;&bslash;&n;&t;&t;    break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_getreg
mdefine_line|#define ia64_getreg(regnum)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (regnum) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_GP:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=gp&quot; : &quot;=r&quot;(ia64_intri_res));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_IP:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=ip&quot; : &quot;=r&quot;(ia64_intri_res));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_PSR:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=psr&quot; : &quot;=r&quot;(ia64_intri_res));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_TP:&t;/* for current() */&t;&t;&t;&t;&bslash;&n;&t;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;register __u64 ia64_r13 asm (&quot;r13&quot;);&t;&t;&t;&bslash;&n;&t;&t;&t;ia64_intri_res = ia64_r13;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_AR_KR0 ... _IA64_REG_AR_EC:&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=ar%1&quot; : &quot;=r&quot; (ia64_intri_res)&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;i&quot;(regnum - _IA64_REG_AR_KR0));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_CR_DCR ... _IA64_REG_CR_LRR1:&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=cr%1&quot; : &quot;=r&quot; (ia64_intri_res)&t;&t;&bslash;&n;&t;&t;&t;&t;      : &quot;i&quot; (regnum - _IA64_REG_CR_DCR));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case _IA64_REG_SP:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;mov %0=sp&quot; : &quot;=r&quot; (ia64_intri_res));&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;default:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_bad_param_for_getreg();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_hint_pause
mdefine_line|#define ia64_hint_pause 0
DECL|macro|ia64_hint
mdefine_line|#define ia64_hint(mode)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (mode) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_hint_pause:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm volatile (&quot;hint @pause&quot; ::: &quot;memory&quot;);&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Integer values for mux1 instruction */
DECL|macro|ia64_mux1_brcst
mdefine_line|#define ia64_mux1_brcst 0
DECL|macro|ia64_mux1_mix
mdefine_line|#define ia64_mux1_mix   8
DECL|macro|ia64_mux1_shuf
mdefine_line|#define ia64_mux1_shuf  9
DECL|macro|ia64_mux1_alt
mdefine_line|#define ia64_mux1_alt  10
DECL|macro|ia64_mux1_rev
mdefine_line|#define ia64_mux1_rev  11
DECL|macro|ia64_mux1
mdefine_line|#define ia64_mux1(x, mode)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (mode) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_mux1_brcst:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mux1 %0=%1,@brcst&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_mux1_mix:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mux1 %0=%1,@mix&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_mux1_shuf:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mux1 %0=%1,@shuf&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_mux1_alt:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mux1 %0=%1,@alt&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case ia64_mux1_rev:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm (&quot;mux1 %0=%1,@rev&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_popcnt
mdefine_line|#define ia64_popcnt(x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;popcnt %0=%1&quot; : &quot;=r&quot; (ia64_intri_res) : &quot;r&quot; (x));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_getf_exp
mdefine_line|#define ia64_getf_exp(x)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long ia64_intri_res;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;getf.exp %0=%1&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;f&quot;(x));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_shrp
mdefine_line|#define ia64_shrp(a, b, count)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;shrp %0=%1,%2,%3&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(a), &quot;r&quot;(b), &quot;i&quot;(count));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_ldfs
mdefine_line|#define ia64_ldfs(regnum, x)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ldfs %0=[%1]&quot; :&quot;=f&quot;(__f__): &quot;r&quot;(x));&t;&bslash;&n;})
DECL|macro|ia64_ldfd
mdefine_line|#define ia64_ldfd(regnum, x)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ldfd %0=[%1]&quot; :&quot;=f&quot;(__f__): &quot;r&quot;(x));&t;&bslash;&n;})
DECL|macro|ia64_ldfe
mdefine_line|#define ia64_ldfe(regnum, x)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ldfe %0=[%1]&quot; :&quot;=f&quot;(__f__): &quot;r&quot;(x));&t;&bslash;&n;})
DECL|macro|ia64_ldf8
mdefine_line|#define ia64_ldf8(regnum, x)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ldf8 %0=[%1]&quot; :&quot;=f&quot;(__f__): &quot;r&quot;(x));&t;&bslash;&n;})
DECL|macro|ia64_ldf_fill
mdefine_line|#define ia64_ldf_fill(regnum, x)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ldf.fill %0=[%1]&quot; :&quot;=f&quot;(__f__): &quot;r&quot;(x));&t;&bslash;&n;})
DECL|macro|ia64_stfs
mdefine_line|#define ia64_stfs(x, regnum)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;stfs [%0]=%1&quot; :: &quot;r&quot;(x), &quot;f&quot;(__f__) : &quot;memory&quot;);&t;&bslash;&n;})
DECL|macro|ia64_stfd
mdefine_line|#define ia64_stfd(x, regnum)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;stfd [%0]=%1&quot; :: &quot;r&quot;(x), &quot;f&quot;(__f__) : &quot;memory&quot;);&t;&bslash;&n;})
DECL|macro|ia64_stfe
mdefine_line|#define ia64_stfe(x, regnum)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;stfe [%0]=%1&quot; :: &quot;r&quot;(x), &quot;f&quot;(__f__) : &quot;memory&quot;);&t;&bslash;&n;})
DECL|macro|ia64_stf8
mdefine_line|#define ia64_stf8(x, regnum)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;stf8 [%0]=%1&quot; :: &quot;r&quot;(x), &quot;f&quot;(__f__) : &quot;memory&quot;);&t;&bslash;&n;})
DECL|macro|ia64_stf_spill
mdefine_line|#define ia64_stf_spill(x, regnum)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register double __f__ asm (&quot;f&quot;#regnum);&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;stf.spill [%0]=%1&quot; :: &quot;r&quot;(x), &quot;f&quot;(__f__) : &quot;memory&quot;);&t;&bslash;&n;})
DECL|macro|ia64_fetchadd4_acq
mdefine_line|#define ia64_fetchadd4_acq(p, inc)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;fetchadd4.acq %0=[%1],%2&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;: &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(p), &quot;i&quot; (inc)&t;&bslash;&n;&t;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetchadd4_rel
mdefine_line|#define ia64_fetchadd4_rel(p, inc)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;fetchadd4.rel %0=[%1],%2&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;: &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(p), &quot;i&quot; (inc)&t;&bslash;&n;&t;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetchadd8_acq
mdefine_line|#define ia64_fetchadd8_acq(p, inc)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;fetchadd8.acq %0=[%1],%2&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;: &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(p), &quot;i&quot; (inc)&t;&bslash;&n;&t;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fetchadd8_rel
mdefine_line|#define ia64_fetchadd8_rel(p, inc)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;fetchadd8.rel %0=[%1],%2&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;: &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(p), &quot;i&quot; (inc)&t;&bslash;&n;&t;&t;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_xchg1
mdefine_line|#define ia64_xchg1(ptr,x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm __volatile (&quot;xchg1 %0=[%1],%2&quot; : &quot;=r&quot; (ia64_intri_res)&t;&bslash;&n;&t;&t;&t;    : &quot;r&quot; (ptr), &quot;r&quot; (x) : &quot;memory&quot;);&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_xchg2
mdefine_line|#define ia64_xchg2(ptr,x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm __volatile (&quot;xchg2 %0=[%1],%2&quot; : &quot;=r&quot; (ia64_intri_res)&t;&bslash;&n;&t;&t;&t;    : &quot;r&quot; (ptr), &quot;r&quot; (x) : &quot;memory&quot;);&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_xchg4
mdefine_line|#define ia64_xchg4(ptr,x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm __volatile (&quot;xchg4 %0=[%1],%2&quot; : &quot;=r&quot; (ia64_intri_res)&t;&bslash;&n;&t;&t;&t;    : &quot;r&quot; (ptr), &quot;r&quot; (x) : &quot;memory&quot;);&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_xchg8
mdefine_line|#define ia64_xchg8(ptr,x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm __volatile (&quot;xchg8 %0=[%1],%2&quot; : &quot;=r&quot; (ia64_intri_res)&t;&bslash;&n;&t;&t;&t;    : &quot;r&quot; (ptr), &quot;r&quot; (x) : &quot;memory&quot;);&t;&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg1_acq
mdefine_line|#define ia64_cmpxchg1_acq(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg1.acq %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg1_rel
mdefine_line|#define ia64_cmpxchg1_rel(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg1.rel %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg2_acq
mdefine_line|#define ia64_cmpxchg2_acq(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg2.acq %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg2_rel
mdefine_line|#define ia64_cmpxchg2_rel(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg2.rel %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg4_acq
mdefine_line|#define ia64_cmpxchg4_acq(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg4.acq %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg4_rel
mdefine_line|#define ia64_cmpxchg4_rel(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg4.rel %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg8_acq
mdefine_line|#define ia64_cmpxchg8_acq(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg8.acq %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_cmpxchg8_rel
mdefine_line|#define ia64_cmpxchg8_rel(ptr, new, old)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ar.ccv=%0;;&quot; :: &quot;rO&quot;(old));&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;cmpxchg8.rel %0=[%1],%2,ar.ccv&quot;:&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(ptr), &quot;r&quot;(new) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_mf
mdefine_line|#define ia64_mf()&t;asm volatile (&quot;mf&quot; ::: &quot;memory&quot;)
DECL|macro|ia64_mfa
mdefine_line|#define ia64_mfa()&t;asm volatile (&quot;mf.a&quot; ::: &quot;memory&quot;)
DECL|macro|ia64_invala
mdefine_line|#define ia64_invala() asm volatile (&quot;invala&quot; ::: &quot;memory&quot;)
DECL|macro|ia64_thash
mdefine_line|#define ia64_thash(addr)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;thash %0=%1&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot; (addr));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_srlz_i
mdefine_line|#define ia64_srlz_i()&t;asm volatile (&quot;;; srlz.i ;;&quot; ::: &quot;memory&quot;)
DECL|macro|ia64_srlz_d
mdefine_line|#define ia64_srlz_d()&t;asm volatile (&quot;;; srlz.d&quot; ::: &quot;memory&quot;);
DECL|macro|ia64_nop
mdefine_line|#define ia64_nop(x)&t;asm volatile (&quot;nop %0&quot;::&quot;i&quot;(x));
DECL|macro|ia64_itci
mdefine_line|#define ia64_itci(addr)&t;asm volatile (&quot;itc.i %0;;&quot; :: &quot;r&quot;(addr) : &quot;memory&quot;)
DECL|macro|ia64_itcd
mdefine_line|#define ia64_itcd(addr)&t;asm volatile (&quot;itc.d %0;;&quot; :: &quot;r&quot;(addr) : &quot;memory&quot;)
DECL|macro|ia64_itri
mdefine_line|#define ia64_itri(trnum, addr) asm volatile (&quot;itr.i itr[%0]=%1&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;     :: &quot;r&quot;(trnum), &quot;r&quot;(addr) : &quot;memory&quot;)
DECL|macro|ia64_itrd
mdefine_line|#define ia64_itrd(trnum, addr) asm volatile (&quot;itr.d dtr[%0]=%1&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;     :: &quot;r&quot;(trnum), &quot;r&quot;(addr) : &quot;memory&quot;)
DECL|macro|ia64_tpa
mdefine_line|#define ia64_tpa(addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_pa;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;tpa %0 = %1&quot; : &quot;=r&quot;(ia64_pa) : &quot;r&quot;(addr) : &quot;memory&quot;);&t;&bslash;&n;&t;ia64_pa;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ia64_set_dbr
mdefine_line|#define __ia64_set_dbr(index, val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov dbr[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;)
DECL|macro|ia64_set_ibr
mdefine_line|#define ia64_set_ibr(index, val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov ibr[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;)
DECL|macro|ia64_set_pkr
mdefine_line|#define ia64_set_pkr(index, val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov pkr[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;)
DECL|macro|ia64_set_pmc
mdefine_line|#define ia64_set_pmc(index, val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov pmc[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;)
DECL|macro|ia64_set_pmd
mdefine_line|#define ia64_set_pmd(index, val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov pmd[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;)
DECL|macro|ia64_set_rr
mdefine_line|#define ia64_set_rr(index, val)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov rr[%0]=%1&quot; :: &quot;r&quot;(index), &quot;r&quot;(val) : &quot;memory&quot;);
DECL|macro|ia64_get_cpuid
mdefine_line|#define ia64_get_cpuid(index)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=cpuid[%r1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;rO&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ia64_get_dbr
mdefine_line|#define __ia64_get_dbr(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=dbr[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_get_ibr
mdefine_line|#define ia64_get_ibr(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=ibr[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_get_pkr
mdefine_line|#define ia64_get_pkr(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=pkr[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_get_pmc
mdefine_line|#define ia64_get_pmc(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=pmc[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_get_pmd
mdefine_line|#define ia64_get_pmd(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=pmd[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot;(index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_get_rr
mdefine_line|#define ia64_get_rr(index)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;mov %0=rr[%1]&quot; : &quot;=r&quot;(ia64_intri_res) : &quot;r&quot; (index));&t;&bslash;&n;&t;ia64_intri_res;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_fc
mdefine_line|#define ia64_fc(addr)&t;asm volatile (&quot;fc %0&quot; :: &quot;r&quot;(addr) : &quot;memory&quot;)
DECL|macro|ia64_sync_i
mdefine_line|#define ia64_sync_i()&t;asm volatile (&quot;;; sync.i&quot; ::: &quot;memory&quot;)
DECL|macro|ia64_ssm
mdefine_line|#define ia64_ssm(mask)&t;asm volatile (&quot;ssm %0&quot;:: &quot;i&quot;((mask)) : &quot;memory&quot;)
DECL|macro|ia64_rsm
mdefine_line|#define ia64_rsm(mask)&t;asm volatile (&quot;rsm %0&quot;:: &quot;i&quot;((mask)) : &quot;memory&quot;)
DECL|macro|ia64_sum
mdefine_line|#define ia64_sum(mask)&t;asm volatile (&quot;sum %0&quot;:: &quot;i&quot;((mask)) : &quot;memory&quot;)
DECL|macro|ia64_rum
mdefine_line|#define ia64_rum(mask)&t;asm volatile (&quot;rum %0&quot;:: &quot;i&quot;((mask)) : &quot;memory&quot;)
DECL|macro|ia64_ptce
mdefine_line|#define ia64_ptce(addr)&t;asm volatile (&quot;ptc.e %0&quot; :: &quot;r&quot;(addr))
DECL|macro|ia64_ptcga
mdefine_line|#define ia64_ptcga(addr, size)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ptc.ga %0,%1&quot; :: &quot;r&quot;(addr), &quot;r&quot;(size) : &quot;memory&quot;)
DECL|macro|ia64_ptcl
mdefine_line|#define ia64_ptcl(addr, size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ptc.l %0,%1&quot; :: &quot;r&quot;(addr), &quot;r&quot;(size) : &quot;memory&quot;)
DECL|macro|ia64_ptri
mdefine_line|#define ia64_ptri(addr, size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ptr.i %0,%1&quot; :: &quot;r&quot;(addr), &quot;r&quot;(size) : &quot;memory&quot;)
DECL|macro|ia64_ptrd
mdefine_line|#define ia64_ptrd(addr, size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;ptr.d %0,%1&quot; :: &quot;r&quot;(addr), &quot;r&quot;(size) : &quot;memory&quot;)
multiline_comment|/* Values for lfhint in ia64_lfetch and ia64_lfetch_fault */
DECL|macro|ia64_lfhint_none
mdefine_line|#define ia64_lfhint_none   0
DECL|macro|ia64_lfhint_nt1
mdefine_line|#define ia64_lfhint_nt1    1
DECL|macro|ia64_lfhint_nt2
mdefine_line|#define ia64_lfhint_nt2    2
DECL|macro|ia64_lfhint_nta
mdefine_line|#define ia64_lfhint_nta    3
DECL|macro|ia64_lfetch
mdefine_line|#define ia64_lfetch(lfhint, y)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        switch (lfhint) {&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_none:&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt1:&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.nt1 [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt2:&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.nt2 [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nta:&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.nta [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_lfetch_excl
mdefine_line|#define ia64_lfetch_excl(lfhint, y)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        switch (lfhint) {&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_none:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.excl [%0]&quot; :: &quot;r&quot;(y));&t;&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt1:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.excl.nt1 [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt2:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.excl.nt2 [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nta:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.excl.nta [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_lfetch_fault
mdefine_line|#define ia64_lfetch_fault(lfhint, y)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        switch (lfhint) {&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_none:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault [%0]&quot; : : &quot;r&quot;(y));&t;&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt1:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.nt1 [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt2:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.nt2 [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nta:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.nta [%0]&quot; : : &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_lfetch_fault_excl
mdefine_line|#define ia64_lfetch_fault_excl(lfhint, y)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        switch (lfhint) {&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_none:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.excl [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt1:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.excl.nt1 [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nt2:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.excl.nt2 [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        case ia64_lfhint_nta:&t;&t;&t;&t;&t;&t;&bslash;&n;                asm volatile (&quot;lfetch.fault.excl.nta [%0]&quot; :: &quot;r&quot;(y));&t;&bslash;&n;                break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|ia64_intrin_local_irq_restore
mdefine_line|#define ia64_intrin_local_irq_restore(x)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile (&quot;     cmp.ne p6,p7=%0,r0;;&quot;&t;&t;&bslash;&n;&t;&t;      &quot;(p6) ssm psr.i;&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;      &quot;(p7) rsm psr.i;;&quot;&t;&t;&t;&bslash;&n;&t;&t;      &quot;(p6) srlz.d&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;      :: &quot;r&quot;((x)) : &quot;p6&quot;, &quot;p7&quot;, &quot;memory&quot;);&t;&bslash;&n;} while (0)
macro_line|#endif /* _ASM_IA64_GCC_INTRIN_H */
eof
