macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &quot;entry.h&quot;
multiline_comment|/*&n; * For ivt.s we want to access the stack virtually so we don&squot;t have to disable translation&n; * on interrupts.&n; *&n; *  On entry:&n; *&t;r1:&t;pointer to current task (ar.k6)&n; */
DECL|macro|MINSTATE_START_SAVE_MIN_VIRT
mdefine_line|#define MINSTATE_START_SAVE_MIN_VIRT&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov ar.rsc=0;&t;&t;/* set enforced lazy mode, pl 0, little-endian, loadrs=0 */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov.m r24=ar.rnat;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;addl r22=IA64_RBS_OFFSET,r1;&t;&t;&t;/* compute base of RBS */&t;&t;&bslash;&n;(pKStk) mov r1=sp;&t;&t;&t;&t;&t;/* get sp  */&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk) lfetch.fault.excl.nt1 [r22];&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;addl r1=IA64_STK_OFFSET-IA64_PT_REGS_SIZE,r1;&t;/* compute base of memory stack */&t;&bslash;&n;(pUStk)&t;mov r23=ar.bspstore;&t;&t;&t;&t;/* save ar.bspstore */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov ar.bspstore=r22;&t;&t;&t;&t;/* switch to kernel RBS */&t;&t;&bslash;&n;(pKStk) addl r1=-IA64_PT_REGS_SIZE,r1;&t;&t;&t;/* if in kernel mode, use sp (r12) */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov r18=ar.bsp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov ar.rsc=0x3;&t;&t;/* set eager mode, pl 0, little-endian, loadrs=0 */&t;&t;&bslash;&n;
DECL|macro|MINSTATE_END_SAVE_MIN_VIRT
mdefine_line|#define MINSTATE_END_SAVE_MIN_VIRT&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;bsw.1;&t;&t;&t;/* switch back to bank 1 (must be last in insn group) */&t;&bslash;&n;&t;;;
multiline_comment|/*&n; * For mca_asm.S we want to access the stack physically since the state is saved before we&n; * go virtual and don&squot;t want to destroy the iip or ipsr.&n; */
DECL|macro|MINSTATE_START_SAVE_MIN_PHYS
mdefine_line|#define MINSTATE_START_SAVE_MIN_PHYS&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) mov r3=IA64_KR(PER_CPU_DATA);;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) addl r3=THIS_CPU(ia64_mca_data),r3;;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) ld8 r3 = [r3];;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) addl r3=IA64_MCA_CPU_INIT_STACK_OFFSET,r3;;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) addl sp=IA64_STK_OFFSET-IA64_PT_REGS_SIZE,r3;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov ar.rsc=0;&t;&t;/* set enforced lazy mode, pl 0, little-endian, loadrs=0 */&t;&bslash;&n;(pUStk)&t;addl r22=IA64_RBS_OFFSET,r1;&t;&t;/* compute base of register backing store */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov r24=ar.rnat;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;addl r1=IA64_STK_OFFSET-IA64_PT_REGS_SIZE,r1;&t;/* compute base of memory stack */&t;&bslash;&n;(pUStk)&t;mov r23=ar.bspstore;&t;&t;&t;&t;/* save ar.bspstore */&t;&t;&t;&bslash;&n;(pUStk)&t;dep r22=-1,r22,61,3;&t;&t;&t;/* compute kernel virtual addr of RBS */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk) addl r1=-IA64_PT_REGS_SIZE,r1;&t;&t;/* if in kernel mode, use sp (r12) */&t;&t;&bslash;&n;(pUStk)&t;mov ar.bspstore=r22;&t;&t;&t;/* switch to kernel RBS */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov r18=ar.bsp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;mov ar.rsc=0x3;&t;&t;/* set eager mode, pl 0, little-endian, loadrs=0 */&t;&t;&bslash;&n;
DECL|macro|MINSTATE_END_SAVE_MIN_PHYS
mdefine_line|#define MINSTATE_END_SAVE_MIN_PHYS&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dep r12=-1,r12,61,3;&t;&t;/* make sp a kernel virtual address */&t;&t;&t;&bslash;&n;&t;;;
macro_line|#ifdef MINSTATE_VIRT
DECL|macro|MINSTATE_GET_CURRENT
macro_line|# define MINSTATE_GET_CURRENT(reg)&t;mov reg=IA64_KR(CURRENT)
DECL|macro|MINSTATE_START_SAVE_MIN
macro_line|# define MINSTATE_START_SAVE_MIN&t;MINSTATE_START_SAVE_MIN_VIRT
DECL|macro|MINSTATE_END_SAVE_MIN
macro_line|# define MINSTATE_END_SAVE_MIN&t;&t;MINSTATE_END_SAVE_MIN_VIRT
macro_line|#endif
macro_line|#ifdef MINSTATE_PHYS
DECL|macro|MINSTATE_GET_CURRENT
macro_line|# define MINSTATE_GET_CURRENT(reg)&t;mov reg=IA64_KR(CURRENT);; tpa reg=reg
DECL|macro|MINSTATE_START_SAVE_MIN
macro_line|# define MINSTATE_START_SAVE_MIN&t;MINSTATE_START_SAVE_MIN_PHYS
DECL|macro|MINSTATE_END_SAVE_MIN
macro_line|# define MINSTATE_END_SAVE_MIN&t;&t;MINSTATE_END_SAVE_MIN_PHYS
macro_line|#endif
multiline_comment|/*&n; * DO_SAVE_MIN switches to the kernel stacks (if necessary) and saves&n; * the minimum state necessary that allows us to turn psr.ic back&n; * on.&n; *&n; * Assumed state upon entry:&n; *&t;psr.ic: off&n; *&t;r31:&t;contains saved predicates (pr)&n; *&n; * Upon exit, the state is as follows:&n; *&t;psr.ic: off&n; *&t; r2 = points to &amp;pt_regs.r16&n; *&t; r8 = contents of ar.ccv&n; *&t; r9 = contents of ar.csd&n; *&t;r10 = contents of ar.ssd&n; *&t;r11 = FPSR_DEFAULT&n; *&t;r12 = kernel sp (kernel virtual address)&n; *&t;r13 = points to current task_struct (kernel virtual address)&n; *&t;p15 = TRUE if psr.i is set in cr.ipsr&n; *&t;predicate registers (other than p2, p3, and p15), b6, r3, r14, r15:&n; *&t;&t;preserved&n; *&n; * Note that psr.ic is NOT turned on by this macro.  This is so that&n; * we can pass interruption state as arguments to a handler.&n; */
DECL|macro|DO_SAVE_MIN
mdefine_line|#define DO_SAVE_MIN(COVER,SAVE_IFS,EXTRA)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MINSTATE_GET_CURRENT(r16);&t;/* M (or M;;I) */&t;&t;&t;&t;&t;&bslash;&n;&t;mov r27=ar.rsc;&t;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r20=r1;&t;&t;&t;/* A */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r25=ar.unat;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r29=cr.ipsr;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r26=ar.pfs;&t;&t;&t;/* I */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r28=cr.iip;&t;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r21=ar.fpsr;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;COVER;&t;&t;&t;&t;/* B;; (or nothing) */&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;adds r16=IA64_TASK_THREAD_ON_USTACK_OFFSET,r16;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ld1 r17=[r16];&t;&t;&t;&t;/* load current-&gt;thread.on_ustack flag */&t;&bslash;&n;&t;st1 [r16]=r0;&t;&t;&t;&t;/* clear current-&gt;thread.on_ustack flag */&t;&bslash;&n;&t;adds r1=-IA64_TASK_THREAD_ON_USTACK_OFFSET,r16&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* switch from user to kernel RBS: */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;invala;&t;&t;&t;&t;/* M */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SAVE_IFS;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cmp.eq pKStk,pUStk=r0,r17;&t;&t;/* are we in kernel mode already? */&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MINSTATE_START_SAVE_MIN&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;adds r17=2*L1_CACHE_BYTES,r1;&t;&t;/* really: biggest cache-line size */&t;&t;&bslash;&n;&t;adds r16=PT(CR_IPSR),r1;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;lfetch.fault.excl.nt1 [r17],L1_CACHE_BYTES;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r16]=r29;&t;&t;/* save cr.ipsr */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;lfetch.fault.excl.nt1 [r17];&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tbit.nz p15,p0=r29,IA64_PSR_I_BIT;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r29=b0&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;adds r16=PT(R8),r1;&t;/* initialize first base pointer */&t;&t;&t;&t;&bslash;&n;&t;adds r17=PT(R9),r1;&t;/* initialize second base pointer */&t;&t;&t;&t;&bslash;&n;(pKStk)&t;mov r18=r0;&t;&t;/* make sure r18 isn&squot;t NaT */&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r8,16;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r9,16;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        ;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r10,24;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r11,24;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        ;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r16]=r28,16;&t;/* save cr.iip */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r17]=r30,16;&t;/* save cr.ifs */&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;sub r18=r18,r22;&t;/* r18=RSE.ndirty*8 */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r8=ar.ccv;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r9=ar.csd;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r10=ar.ssd;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;movl r11=FPSR_DEFAULT;   /* L-unit */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r16]=r25,16;&t;/* save ar.unat */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r17]=r26,16;&t;/* save ar.pfs */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;shl r18=r18,16;&t;&t;/* compute ar.rsc to be used for &quot;loadrs&quot; */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r16]=r27,16;&t;/* save ar.rsc */&t;&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;st8 [r17]=r24,16;&t;/* save ar.rnat */&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk)&t;adds r17=16,r17;&t;/* skip over ar_rnat field */&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;/* avoid RAW on r16 &amp; r17 */&t;&t;&t;&t;&t;&bslash;&n;(pUStk)&t;st8 [r16]=r23,16;&t;/* save ar.bspstore */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r17]=r31,16;&t;/* save predicates */&t;&t;&t;&t;&t;&t;&bslash;&n;(pKStk)&t;adds r16=16,r16;&t;/* skip over ar_bspstore field */&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r16]=r29,16;&t;/* save b0 */&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r17]=r18,16;&t;/* save ar.rsc value for &quot;loadrs&quot; */&t;&t;&t;&t;&bslash;&n;&t;cmp.eq pNonSys,pSys=r0,r0&t;/* initialize pSys=0, pNonSys=1 */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r20,16;&t;/* save original r1 */&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r12,16;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;adds r12=-16,r1;&t;/* switch to kernel memory stack (with 16 bytes of scratch) */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r13,16;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r21,16;&t;/* save ar.fpsr */&t;&t;&t;&t;&bslash;&n;&t;mov r13=IA64_KR(CURRENT);&t;/* establish `current&squot; */&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r15,16;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r14,16;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r16]=r2,16;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r17]=r3,16;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;adds r2=IA64_PT_REGS_R16_OFFSET,r1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;EXTRA;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;movl r1=__gp;&t;&t;/* establish kernel global pointer */&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MINSTATE_END_SAVE_MIN
multiline_comment|/*&n; * SAVE_REST saves the remainder of pt_regs (with psr.ic on).&n; *&n; * Assumed state upon entry:&n; *&t;psr.ic: on&n; *&t;r2:&t;points to &amp;pt_regs.r16&n; *&t;r3:&t;points to &amp;pt_regs.r17&n; *&t;r8:&t;contents of ar.ccv&n; *&t;r9:&t;contents of ar.csd&n; *&t;r10:&t;contents of ar.ssd&n; *&t;r11:&t;FPSR_DEFAULT&n; *&n; * Registers r14 and r15 are guaranteed not to be touched by SAVE_REST.&n; */
DECL|macro|SAVE_REST
mdefine_line|#define SAVE_REST&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r16,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r17,16;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r18,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r19,16;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r20,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r21,16;&t;&t;&bslash;&n;&t;mov r18=b6;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r22,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r23,16;&t;&t;&bslash;&n;&t;mov r19=b7;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r24,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r25,16;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r26,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r27,16;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r28,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r29,16;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0; st8.spill [r2]=r30,16;&t;&t;&bslash;&n;.mem.offset 8,0; st8.spill [r3]=r31,32;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;mov ar.fpsr=r11;&t;/* M-unit */&t;&bslash;&n;&t;st8 [r2]=r8,8;&t;&t;/* ar.ccv */&t;&bslash;&n;&t;adds r24=PT(B6)-PT(F7),r3;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;stf.spill [r2]=f6,32;&t;&t;&t;&bslash;&n;&t;stf.spill [r3]=f7,32;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;stf.spill [r2]=f8,32;&t;&t;&t;&bslash;&n;&t;stf.spill [r3]=f9,32;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;stf.spill [r2]=f10;&t;&t;&t;&bslash;&n;&t;stf.spill [r3]=f11;&t;&t;&t;&bslash;&n;&t;adds r25=PT(B7)-PT(F11),r3;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r24]=r18,16;       /* b6 */&t;&bslash;&n;&t;st8 [r25]=r19,16;       /* b7 */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r24]=r9;        &t;/* ar.csd */&t;&bslash;&n;&t;st8 [r25]=r10;      &t;/* ar.ssd */&t;&bslash;&n;&t;;;
DECL|macro|SAVE_MIN_WITH_COVER
mdefine_line|#define SAVE_MIN_WITH_COVER&t;DO_SAVE_MIN(cover, mov r30=cr.ifs,)
DECL|macro|SAVE_MIN_WITH_COVER_R19
mdefine_line|#define SAVE_MIN_WITH_COVER_R19&t;DO_SAVE_MIN(cover, mov r30=cr.ifs, mov r15=r19)
DECL|macro|SAVE_MIN
mdefine_line|#define SAVE_MIN&t;&t;DO_SAVE_MIN(     , mov r30=r0, )
eof
