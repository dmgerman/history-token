multiline_comment|/*&n; * Preserved registers that are shared between code in ivt.S and entry.S.  Be&n; * careful not to step on these!&n; */
DECL|macro|pKern
mdefine_line|#define pKern&t;&t;p2&t;/* will leave_kernel return to kernel-mode? */
DECL|macro|pSys
mdefine_line|#define pSys&t;&t;p4&t;/* are we processing a (synchronous) system call? */
DECL|macro|pNonSys
mdefine_line|#define pNonSys&t;&t;p5&t;/* complement of pSys */
DECL|macro|PT
mdefine_line|#define PT(f)&t;&t;(IA64_PT_REGS_##f##_OFFSET + 16)
DECL|macro|SW
mdefine_line|#define SW(f)&t;&t;(IA64_SWITCH_STACK_##f##_OFFSET + 16)
DECL|macro|PT_REGS_SAVES
mdefine_line|#define PT_REGS_SAVES(off)&t;&t;&t;&t;&bslash;&n;&t;UNW(.unwabi @svr4, &squot;i&squot;);&t;&t;&t;&bslash;&n;&t;UNW(.fframe IA64_PT_REGS_SIZE+16+(off));&t;&bslash;&n;&t;UNW(.spillsp rp, PT(CR_IIP)+(off));&t;&t;&bslash;&n;&t;UNW(.spillsp ar.pfs, PT(CR_IFS)+(off));&t;&t;&bslash;&n;&t;UNW(.spillsp ar.unat, PT(AR_UNAT)+(off));&t;&bslash;&n;&t;UNW(.spillsp ar.fpsr, PT(AR_FPSR)+(off));&t;&bslash;&n;&t;UNW(.spillsp pr, PT(PR)+(off));
DECL|macro|PT_REGS_UNWIND_INFO
mdefine_line|#define PT_REGS_UNWIND_INFO(off)&t;&t;&bslash;&n;&t;UNW(.prologue);&t;&t;&t;&t;&bslash;&n;&t;PT_REGS_SAVES(off);&t;&t;&t;&bslash;&n;&t;UNW(.body)
DECL|macro|SWITCH_STACK_SAVES
mdefine_line|#define SWITCH_STACK_SAVES(off)&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;UNW(.savesp ar.unat,SW(CALLER_UNAT)+(off)); UNW(.savesp ar.fpsr,SW(AR_FPSR)+(off));&t;  &bslash;&n;&t;UNW(.spillsp f2,SW(F2)+(off)); UNW(.spillsp f3,SW(F3)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f4,SW(F4)+(off)); UNW(.spillsp f5,SW(F5)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f16,SW(F16)+(off)); UNW(.spillsp f17,SW(F17)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f18,SW(F18)+(off)); UNW(.spillsp f19,SW(F19)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f20,SW(F20)+(off)); UNW(.spillsp f21,SW(F21)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f22,SW(F22)+(off)); UNW(.spillsp f23,SW(F23)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f24,SW(F24)+(off)); UNW(.spillsp f25,SW(F25)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f26,SW(F26)+(off)); UNW(.spillsp f27,SW(F27)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f28,SW(F28)+(off)); UNW(.spillsp f29,SW(F29)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp f30,SW(F30)+(off)); UNW(.spillsp f31,SW(F31)+(off));&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp r4,SW(R4)+(off)); UNW(.spillsp r5,SW(R5)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp r6,SW(R6)+(off)); UNW(.spillsp r7,SW(R7)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp b0,SW(B0)+(off)); UNW(.spillsp b1,SW(B1)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp b2,SW(B2)+(off)); UNW(.spillsp b3,SW(B3)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp b4,SW(B4)+(off)); UNW(.spillsp b5,SW(B5)+(off));&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp ar.pfs,SW(AR_PFS)+(off)); UNW(.spillsp ar.lc,SW(AR_LC)+(off));&t;&t;  &bslash;&n;&t;UNW(.spillsp @priunat,SW(AR_UNAT)+(off));&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;UNW(.spillsp ar.rnat,SW(AR_RNAT)+(off)); UNW(.spillsp ar.bspstore,SW(AR_BSPSTORE)+(off)); &bslash;&n;&t;UNW(.spillsp pr,SW(PR)+(off))
DECL|macro|DO_SAVE_SWITCH_STACK
mdefine_line|#define DO_SAVE_SWITCH_STACK&t;&t;&t;&bslash;&n;&t;movl r28=1f;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;.fframe IA64_SWITCH_STACK_SIZE;&t;&t;&bslash;&n;&t;adds sp=-IA64_SWITCH_STACK_SIZE,sp;&t;&bslash;&n;&t;mov b7=r28;&t;&t;&t;&t;&bslash;&n;&t;SWITCH_STACK_SAVES(0);&t;&t;&t;&bslash;&n;&t;br.cond.sptk.many save_switch_stack;&t;&bslash;&n;1:
DECL|macro|DO_LOAD_SWITCH_STACK
mdefine_line|#define DO_LOAD_SWITCH_STACK(extra)&t;&t;&bslash;&n;&t;movl r28=1f;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;mov b7=r28;&t;&t;&t;&t;&bslash;&n;&t;br.cond.sptk.many load_switch_stack;&t;&bslash;&n;1:&t;UNW(.restore sp);&t;&t;&t;&bslash;&n;&t;extra;&t;&t;&t;&t;&t;&bslash;&n;&t;adds sp=IA64_SWITCH_STACK_SIZE,sp
eof
