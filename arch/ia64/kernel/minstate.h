macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;entry.h&quot;
multiline_comment|/*&n; * A couple of convenience macros that make writing and reading&n; * SAVE_MIN and SAVE_REST easier.&n; */
DECL|macro|rARPR
mdefine_line|#define rARPR&t;&t;r31
DECL|macro|rCRIFS
mdefine_line|#define rCRIFS&t;&t;r30
DECL|macro|rCRIPSR
mdefine_line|#define rCRIPSR&t;&t;r29
DECL|macro|rCRIIP
mdefine_line|#define rCRIIP&t;&t;r28
DECL|macro|rARRSC
mdefine_line|#define rARRSC&t;&t;r27
DECL|macro|rARPFS
mdefine_line|#define rARPFS&t;&t;r26
DECL|macro|rARUNAT
mdefine_line|#define rARUNAT&t;&t;r25
DECL|macro|rARRNAT
mdefine_line|#define rARRNAT&t;&t;r24
DECL|macro|rARBSPSTORE
mdefine_line|#define rARBSPSTORE&t;r23
DECL|macro|rKRBS
mdefine_line|#define rKRBS&t;&t;r22
DECL|macro|rB6
mdefine_line|#define rB6&t;&t;r21
DECL|macro|rR1
mdefine_line|#define rR1&t;&t;r20
multiline_comment|/*&n; * Here start the source dependent macros.&n; */
multiline_comment|/*&n; * For ivt.s we want to access the stack virtually so we dont have to disable translation&n; * on interrupts.&n; */
DECL|macro|MINSTATE_START_SAVE_MIN_VIRT
mdefine_line|#define MINSTATE_START_SAVE_MIN_VIRT&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;dep r1=-1,r1,61,3;&t;&t;&t;&t;/* r1 = current (virtual) */&t;&t;&bslash;&n;(p7)&t;mov ar.rsc=r0;&t;&t;/* set enforced lazy mode, pl 0, little-endian, loadrs=0 */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;addl rKRBS=IA64_RBS_OFFSET,r1;&t;&t;&t;/* compute base of RBS */&t;&t;&bslash;&n;(p7)&t;mov rARRNAT=ar.rnat;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKern) mov r1=sp;&t;&t;&t;&t;&t;/* get sp  */&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;addl r1=IA64_STK_OFFSET-IA64_PT_REGS_SIZE,r1;&t;/* compute base of memory stack */&t;&bslash;&n;(p7)&t;mov rARBSPSTORE=ar.bspstore;&t;&t;&t;/* save ar.bspstore */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKern) addl r1=-IA64_PT_REGS_SIZE,r1;&t;&t;&t;/* if in kernel mode, use sp (r12) */&t;&bslash;&n;(p7)&t;mov ar.bspstore=rKRBS;&t;&t;&t;&t;/* switch to kernel RBS */&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov r18=ar.bsp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov ar.rsc=0x3;&t;&t;/* set eager mode, pl 0, little-endian, loadrs=0 */&t;&t;&bslash;&n;
DECL|macro|MINSTATE_END_SAVE_MIN_VIRT
mdefine_line|#define MINSTATE_END_SAVE_MIN_VIRT&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;or r13=r13,r14;&t;&t;/* make `current&squot; a kernel virtual address */&t;&t;&t;&bslash;&n;&t;bsw.1;&t;&t;&t;/* switch back to bank 1 (must be last in insn group) */&t;&bslash;&n;&t;;;
multiline_comment|/*&n; * For mca_asm.S we want to access the stack physically since the state is saved before we&n; * go virtual and dont want to destroy the iip or ipsr.&n; */
DECL|macro|MINSTATE_START_SAVE_MIN_PHYS
mdefine_line|#define MINSTATE_START_SAVE_MIN_PHYS&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKern) movl sp=ia64_init_stack+IA64_STK_OFFSET-IA64_PT_REGS_SIZE;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov ar.rsc=r0;&t;&t;/* set enforced lazy mode, pl 0, little-endian, loadrs=0 */&t;&bslash;&n;(p7)&t;addl rKRBS=IA64_RBS_OFFSET,r1;&t;&t;/* compute base of register backing store */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov rARRNAT=ar.rnat;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKern) dep r1=0,sp,61,3;&t;&t;&t;&t;/* compute physical addr of sp&t;*/&t;&bslash;&n;(p7)&t;addl r1=IA64_STK_OFFSET-IA64_PT_REGS_SIZE,r1;&t;/* compute base of memory stack */&t;&bslash;&n;(p7)&t;mov rARBSPSTORE=ar.bspstore;&t;&t;&t;/* save ar.bspstore */&t;&t;&t;&bslash;&n;(p7)&t;dep rKRBS=-1,rKRBS,61,3;&t;&t;&t;/* compute kernel virtual addr of RBS */&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(pKern) addl r1=-IA64_PT_REGS_SIZE,r1;&t;&t;/* if in kernel mode, use sp (r12) */&t;&t;&bslash;&n;(p7)&t;mov ar.bspstore=rKRBS;&t;&t;&t;/* switch to kernel RBS */&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov r18=ar.bsp;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;(p7)&t;mov ar.rsc=0x3;&t;&t;/* set eager mode, pl 0, little-endian, loadrs=0 */&t;&t;&bslash;&n;
DECL|macro|MINSTATE_END_SAVE_MIN_PHYS
mdefine_line|#define MINSTATE_END_SAVE_MIN_PHYS&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;or r12=r12,r14;&t;&t;/* make sp a kernel virtual address */&t;&t;&t;&t;&bslash;&n;&t;or r13=r13,r14;&t;&t;/* make `current&squot; a kernel virtual address */&t;&t;&t;&bslash;&n;&t;;;
macro_line|#ifdef MINSTATE_VIRT
DECL|macro|MINSTATE_START_SAVE_MIN
macro_line|# define MINSTATE_START_SAVE_MIN&t;MINSTATE_START_SAVE_MIN_VIRT
DECL|macro|MINSTATE_END_SAVE_MIN
macro_line|# define MINSTATE_END_SAVE_MIN&t;&t;MINSTATE_END_SAVE_MIN_VIRT
macro_line|#endif
macro_line|#ifdef MINSTATE_PHYS
DECL|macro|MINSTATE_START_SAVE_MIN
macro_line|# define MINSTATE_START_SAVE_MIN&t;MINSTATE_START_SAVE_MIN_PHYS
DECL|macro|MINSTATE_END_SAVE_MIN
macro_line|# define MINSTATE_END_SAVE_MIN&t;&t;MINSTATE_END_SAVE_MIN_PHYS
macro_line|#endif
multiline_comment|/*&n; * DO_SAVE_MIN switches to the kernel stacks (if necessary) and saves&n; * the minimum state necessary that allows us to turn psr.ic back&n; * on.&n; *&n; * Assumed state upon entry:&n; *&t;psr.ic: off&n; *&t;psr.dt: off&n; *&t;r31:&t;contains saved predicates (pr)&n; *&n; * Upon exit, the state is as follows:&n; *&t;psr.ic: off&n; *&t;r2 = points to &amp;pt_regs.r16&n; *&t;r12 = kernel sp (kernel virtual address)&n; *&t;r13 = points to current task_struct (kernel virtual address)&n; *&t;p15 = TRUE if psr.i is set in cr.ipsr&n; *&t;predicate registers (other than p6, p7, and p15), b6, r3, r8, r9, r10, r11, r14, r15:&n; *&t;&t;preserved&n; *&n; * Note that psr.ic is NOT turned on by this macro.  This is so that&n; * we can pass interruption state as arguments to a handler.&n; */
DECL|macro|DO_SAVE_MIN
mdefine_line|#define DO_SAVE_MIN(COVER,EXTRA)&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rARRSC=ar.rsc;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rARPFS=ar.pfs;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rR1=r1;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rARUNAT=ar.unat;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rCRIPSR=cr.ipsr;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rB6=b6;&t;&t;/* rB6 = branch reg 6 */&t;&t;&t;&t;&t;  &bslash;&n;&t;mov rCRIIP=cr.iip;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov r1=ar.k6;&t;&t;/* r1 = current (physical) */&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;invala;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;extr.u r16=rCRIPSR,32,2;&t;&t;/* extract psr.cpl */&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;cmp.eq pKern,p7=r0,r16;&t;&t;&t;/* are we in kernel mode already? (psr.cpl==0) */ &bslash;&n;&t;/* switch from user to kernel RBS: */&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;COVER;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;MINSTATE_START_SAVE_MIN&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov r16=r1;&t;&t;&t;&t;&t;/* initialize first base pointer */&t;  &bslash;&n;&t;adds r17=8,r1;&t;&t;&t;&t;&t;/* initialize second base pointer */&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r16]=rCRIPSR,16;&t;/* save cr.ipsr */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r17]=rCRIIP,16;&t;/* save cr.iip */&t;&t;&t;&t;&t;&t;  &bslash;&n;(pKern)&t;mov r18=r0;&t;&t;/* make sure r18 isn&squot;t NaT */&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r16]=rCRIFS,16;&t;/* save cr.ifs */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r17]=rARUNAT,16;&t;/* save ar.unat */&t;&t;&t;&t;&t;&t;  &bslash;&n;(p7)&t;sub r18=r18,rKRBS;&t;/* r18=RSE.ndirty*8 */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r16]=rARPFS,16;&t;/* save ar.pfs */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r17]=rARRSC,16;&t;/* save ar.rsc */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;tbit.nz p15,p0=rCRIPSR,IA64_PSR_I_BIT&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;/* avoid RAW on r16 &amp; r17 */&t;&t;&t;&t;&t;  &bslash;&n;(pKern)&t;adds r16=16,r16;&t;/* skip over ar_rnat field */&t;&t;&t;&t;&t;  &bslash;&n;(pKern)&t;adds r17=16,r17;&t;/* skip over ar_bspstore field */&t;&t;&t;&t;  &bslash;&n;(p7)&t;st8 [r16]=rARRNAT,16;&t;/* save ar.rnat */&t;&t;&t;&t;&t;&t;  &bslash;&n;(p7)&t;st8 [r17]=rARBSPSTORE,16;&t;/* save ar.bspstore */&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r16]=rARPR,16;&t;/* save predicates */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r17]=rB6,16;&t;/* save b6 */&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;shl r18=r18,16;&t;&t;/* compute ar.rsc to be used for &quot;loadrs&quot; */&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;st8 [r16]=r18,16;&t;/* save ar.rsc value for &quot;loadrs&quot; */&t;&t;&t;&t;  &bslash;&n;&t;st8.spill [r17]=rR1,16;&t;/* save original r1 */&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 0,0;&t;st8.spill [r16]=r2,16;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 8,0;&t;st8.spill [r17]=r3,16;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;adds r2=IA64_PT_REGS_R16_OFFSET,r1;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 0,0;&t;&t;st8.spill [r16]=r12,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 8,0;&t;&t;st8.spill [r17]=r13,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;cmp.eq pNonSys,pSys=r0,r0&t;/* initialize pSys=0, pNonSys=1 */&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 0,0;&t;&t;st8.spill [r16]=r14,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 8,0;&t;&t;st8.spill [r17]=r15,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;dep r14=-1,r0,61,3;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 0,0;&t;&t;st8.spill [r16]=r8,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 8,0;&t;&t;st8.spill [r17]=r9,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;adds r12=-16,r1;&t;/* switch to kernel memory stack (with 16 bytes of scratch) */&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 0,0;&t;&t;st8.spill [r16]=r10,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;.mem.offset 8,0;&t;&t;st8.spill [r17]=r11,16;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;mov r13=ar.k6;&t;&t;/* establish `current&squot; */&t;&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;EXTRA;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;movl r1=__gp;&t;&t;/* establish kernel global pointer */&t;&t;&t;&t;  &bslash;&n;&t;;;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;MINSTATE_END_SAVE_MIN
multiline_comment|/*&n; * SAVE_REST saves the remainder of pt_regs (with psr.ic on).  This&n; * macro guarantees to preserve all predicate registers, r8, r9, r10,&n; * r11, r14, and r15.&n; *&n; * Assumed state upon entry:&n; *&t;psr.ic: on&n; *&t;psr.dt: on&n; *&t;r2:&t;points to &amp;pt_regs.r16&n; *&t;r3:&t;points to &amp;pt_regs.r17&n; */
DECL|macro|SAVE_REST
mdefine_line|#define SAVE_REST&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r16,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r17,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r18,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r19,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r16=ar.ccv;&t;&t;/* M-unit */&t;&bslash;&n;&t;movl r18=FPSR_DEFAULT&t;/* L-unit */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;mov r17=ar.fpsr;&t;/* M-unit */&t;&bslash;&n;&t;mov ar.fpsr=r18;&t;/* M-unit */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r20,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r21,16;&t;&bslash;&n;&t;mov r18=b0;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r22,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r23,16;&t;&bslash;&n;&t;mov r19=b7;&t;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r24,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r25,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r26,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r27,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r28,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r29,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;.mem.offset 0,0;&t;st8.spill [r2]=r30,16;&t;&bslash;&n;.mem.offset 8,0;&t;st8.spill [r3]=r31,16;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r2]=r16,16;&t;/* ar.ccv */&t;&bslash;&n;&t;st8 [r3]=r17,16;&t;/* ar.fpsr */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;st8 [r2]=r18,16;&t;/* b0 */&t;&bslash;&n;&t;st8 [r3]=r19,16+8;&t;/* b7 */&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;stf.spill [r2]=f6,32;&t;&t;&t;&bslash;&n;&t;stf.spill [r3]=f7,32;&t;&t;&t;&bslash;&n;&t;;;&t;&t;&t;&t;&t;&bslash;&n;&t;stf.spill [r2]=f8,32;&t;&t;&t;&bslash;&n;&t;stf.spill [r3]=f9,32
macro_line|#ifdef CONFIG_ITANIUM_ASTEP_SPECIFIC
DECL|macro|STOPS
macro_line|# define STOPS&t;nop.i 0x0;; nop.i 0x0;; nop.i 0x0;;
macro_line|#else
DECL|macro|STOPS
macro_line|# define STOPS
macro_line|#endif
DECL|macro|SAVE_MIN_WITH_COVER
mdefine_line|#define SAVE_MIN_WITH_COVER&t;DO_SAVE_MIN(cover;; mov rCRIFS=cr.ifs,) STOPS
DECL|macro|SAVE_MIN_WITH_COVER_R19
mdefine_line|#define SAVE_MIN_WITH_COVER_R19&t;DO_SAVE_MIN(cover;; mov rCRIFS=cr.ifs, mov r15=r19) STOPS
DECL|macro|SAVE_MIN
mdefine_line|#define SAVE_MIN&t;&t;DO_SAVE_MIN(mov rCRIFS=r0,) STOPS
eof
