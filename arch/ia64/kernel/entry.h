macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* XXX fixme */
macro_line|#if defined(CONFIG_ITANIUM_B1_SPECIFIC)
DECL|macro|MOVBR
macro_line|# define MOVBR(type,br,gr,lbl)&t;mov br=gr
macro_line|#else
DECL|macro|MOVBR
macro_line|# define MOVBR(type,br,gr,lbl)&t;mov##type br=gr,lbl
macro_line|#endif
multiline_comment|/*&n; * Preserved registers that are shared between code in ivt.S and entry.S.  Be&n; * careful not to step on these!&n; */
DECL|macro|pKern
mdefine_line|#define pKern&t;&t;p2&t;/* will leave_kernel return to kernel-mode? */
DECL|macro|pUser
mdefine_line|#define pUser&t;&t;p3&t;/* will leave_kernel return to user-mode? */
DECL|macro|pSys
mdefine_line|#define pSys&t;&t;p4&t;/* are we processing a (synchronous) system call? */
DECL|macro|pNonSys
mdefine_line|#define pNonSys&t;&t;p5&t;/* complement of pSys */
DECL|macro|PT
mdefine_line|#define PT(f)&t;&t;(IA64_PT_REGS_##f##_OFFSET)
DECL|macro|SW
mdefine_line|#define SW(f)&t;&t;(IA64_SWITCH_STACK_##f##_OFFSET)
DECL|macro|PT_REGS_SAVES
mdefine_line|#define PT_REGS_SAVES(off)&t;&t;&t;&bslash;&n;&t;.unwabi @svr4, &squot;i&squot;;&t;&t;&t;&bslash;&n;&t;.fframe IA64_PT_REGS_SIZE+16+(off);&t;&bslash;&n;&t;.spillsp rp, PT(CR_IIP)+16+(off);&t;&bslash;&n;&t;.spillsp ar.pfs, PT(CR_IFS)+16+(off);&t;&bslash;&n;&t;.spillsp ar.unat, PT(AR_UNAT)+16+(off);&t;&bslash;&n;&t;.spillsp ar.fpsr, PT(AR_FPSR)+16+(off);&t;&bslash;&n;&t;.spillsp pr, PT(PR)+16+(off);
DECL|macro|PT_REGS_UNWIND_INFO
mdefine_line|#define PT_REGS_UNWIND_INFO(off)&t;&t;&bslash;&n;&t;.prologue;&t;&t;&t;&t;&bslash;&n;&t;PT_REGS_SAVES(off);&t;&t;&t;&bslash;&n;&t;.body
DECL|macro|SWITCH_STACK_SAVES
mdefine_line|#define SWITCH_STACK_SAVES(off)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.savesp ar.unat,SW(CALLER_UNAT)+16+(off);&t;&t;&t;&t;&bslash;&n;&t;.savesp ar.fpsr,SW(AR_FPSR)+16+(off);&t;&t;&t;&t;&t;&bslash;&n;&t;.spillsp f2,SW(F2)+16+(off); .spillsp f3,SW(F3)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f4,SW(F4)+16+(off); .spillsp f5,SW(F5)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f16,SW(F16)+16+(off); .spillsp f17,SW(F17)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f18,SW(F18)+16+(off); .spillsp f19,SW(F19)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f20,SW(F20)+16+(off); .spillsp f21,SW(F21)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f22,SW(F22)+16+(off); .spillsp f23,SW(F23)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f24,SW(F24)+16+(off); .spillsp f25,SW(F25)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f26,SW(F26)+16+(off); .spillsp f27,SW(F27)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f28,SW(F28)+16+(off); .spillsp f29,SW(F29)+16+(off);&t;&t;&bslash;&n;&t;.spillsp f30,SW(F30)+16+(off); .spillsp f31,SW(F31)+16+(off);&t;&t;&bslash;&n;&t;.spillsp r4,SW(R4)+16+(off); .spillsp r5,SW(R5)+16+(off);&t;&t;&bslash;&n;&t;.spillsp r6,SW(R6)+16+(off); .spillsp r7,SW(R7)+16+(off);&t;&t;&bslash;&n;&t;.spillsp b0,SW(B0)+16+(off); .spillsp b1,SW(B1)+16+(off);&t;&t;&bslash;&n;&t;.spillsp b2,SW(B2)+16+(off); .spillsp b3,SW(B3)+16+(off);&t;&t;&bslash;&n;&t;.spillsp b4,SW(B4)+16+(off); .spillsp b5,SW(B5)+16+(off);&t;&t;&bslash;&n;&t;.spillsp ar.pfs,SW(AR_PFS)+16+(off); .spillsp ar.lc,SW(AR_LC)+16+(off);&t;&bslash;&n;&t;.spillsp @priunat,SW(AR_UNAT)+16+(off);&t;&t;&t;&t;&t;&bslash;&n;&t;.spillsp ar.rnat,SW(AR_RNAT)+16+(off);&t;&t;&t;&t;&t;&bslash;&n;&t;.spillsp ar.bspstore,SW(AR_BSPSTORE)+16+(off);&t;&t;&t;&t;&bslash;&n;&t;.spillsp pr,SW(PR)+16+(off))
DECL|macro|DO_SAVE_SWITCH_STACK
mdefine_line|#define DO_SAVE_SWITCH_STACK&t;&t;&t;&bslash;&n;&t;movl r28=1f;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;.fframe IA64_SWITCH_STACK_SIZE;&t;&t;&bslash;&n;&t;adds sp=-IA64_SWITCH_STACK_SIZE,sp;&t;&bslash;&n;&t;MOVBR(.ret.sptk,b7,r28,1f);&t;&t;&bslash;&n;&t;SWITCH_STACK_SAVES(0);&t;&t;&t;&bslash;&n;&t;br.cond.sptk.many save_switch_stack;&t;&bslash;&n;1:
DECL|macro|DO_LOAD_SWITCH_STACK
mdefine_line|#define DO_LOAD_SWITCH_STACK&t;&t;&t;&bslash;&n;&t;movl r28=1f;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;invala;&t;&t;&t;&t;&t;&bslash;&n;&t;MOVBR(.ret.sptk,b7,r28,1f);&t;&t;&bslash;&n;&t;br.cond.sptk.many load_switch_stack;&t;&bslash;&n;1:&t;.restore sp;&t;&t;&t;&t;&bslash;&n;&t;adds sp=IA64_SWITCH_STACK_SIZE,sp
eof
