multiline_comment|/*&n; * Interrupt handling assembler for Linux/CRIS&n; *&n; * Copyright (c) 2000 Axis Communications AB&n; *&n; * Authors:   Bjorn Wesen (bjornw@axis.com)&n; *&n; */
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm-cris/irq.h&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/sv_addr_ag.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 26     /* TODO: what is this for Etrax100/LX ? */
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync      disable_irq
DECL|macro|enable_irq_nosync
mdefine_line|#define enable_irq_nosync       enable_irq
multiline_comment|/* our fine, global, etrax irq vector! the pointer lives in the head.S file. */
DECL|typedef|irqvectptr
r_typedef
r_void
(paren
op_star
id|irqvectptr
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|struct|etrax_interrupt_vector
r_struct
id|etrax_interrupt_vector
(brace
DECL|member|v
id|irqvectptr
id|v
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|etrax_interrupt_vector
op_star
id|etrax_irv
suffix:semicolon
r_void
id|set_int_vector
c_func
(paren
r_int
id|n
comma
id|irqvectptr
id|addr
comma
id|irqvectptr
id|saddr
)paren
suffix:semicolon
r_void
id|set_break_vector
c_func
(paren
r_int
id|n
comma
id|irqvectptr
id|addr
)paren
suffix:semicolon
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
multiline_comment|/* SAVE_ALL saves registers so they match pt_regs */
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;  &quot;push irp&bslash;n&bslash;t&quot;       /* push instruction pointer */ &bslash;&n;  &quot;push srp&bslash;n&bslash;t&quot;       /* push subroutine return pointer */ &bslash;&n;  &quot;push dccr&bslash;n&bslash;t&quot;      /* push condition codes */ &bslash;&n;  &quot;push mof&bslash;n&bslash;t&quot;       /* push multiply overflow reg */ &bslash;&n;  &quot;di&bslash;n&bslash;t&quot;             /* need to disable irq&squot;s at this point */&bslash;&n;  &quot;subq 14*4,sp&bslash;n&bslash;t&quot;   /* make room for r0-r13 */ &bslash;&n;  &quot;movem r13,[sp]&bslash;n&bslash;t&quot; /* push the r0-r13 registers */ &bslash;&n;  &quot;push r10&bslash;n&bslash;t&quot;       /* push orig_r10 */ &bslash;&n;  &quot;clear.d [sp=sp-4]&bslash;n&bslash;t&quot;  /* frametype - this is a normal stackframe */
multiline_comment|/* BLOCK_IRQ and UNBLOCK_IRQ do the same as mask_irq and unmask_irq in irq.c */
DECL|macro|BLOCK_IRQ
mdefine_line|#define BLOCK_IRQ(mask,nr) &bslash;&n;  &quot;move.d &quot; #mask &quot;,r0&bslash;n&bslash;t&quot; &bslash;&n;  &quot;move.d r0,[0xb00000d8]&bslash;n&bslash;t&quot; 
DECL|macro|UNBLOCK_IRQ
mdefine_line|#define UNBLOCK_IRQ(mask) &bslash;&n;  &quot;move.d &quot; #mask &quot;,r0&bslash;n&bslash;t&quot; &bslash;&n;  &quot;move.d r0,[0xb00000dc]&bslash;n&bslash;t&quot; 
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|sIRQ_NAME
mdefine_line|#define sIRQ_NAME(nr) IRQ_NAME2(sIRQ##nr)
DECL|macro|BAD_IRQ_NAME
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
multiline_comment|/* the asm IRQ handler makes sure the causing IRQ is blocked, then it calls&n;   * do_IRQ (with irq disabled still). after that it unblocks and jumps to&n;   * ret_from_intr (entry.S)&n;   */
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(nr,mask) &bslash;&n;void IRQ_NAME(nr); &bslash;&n;void sIRQ_NAME(nr); &bslash;&n;void BAD_IRQ_NAME(nr); &bslash;&n;__asm__ ( &bslash;&n;          &quot;.text&bslash;n&bslash;t&quot; &bslash;&n;          &quot;_IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  SAVE_ALL &bslash;&n;&t;  &quot;_sIRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; /* shortcut for the multiple irq handler */ &bslash;&n;&t;  BLOCK_IRQ(mask,nr) /* this must be done to prevent irq loops when we ei later */ &bslash;&n;&t;  &quot;moveq &quot;#nr&quot;,r10&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;move.d sp,r11&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;jsr _do_IRQ&bslash;n&bslash;t&quot; /* irq.c, r10 and r11 are arguments */ &bslash;&n;&t;  UNBLOCK_IRQ(mask) &bslash;&n;&t;  &quot;moveq 0,r9&bslash;n&bslash;t&quot; /* make ret_from_intr realise we came from an irq */ &bslash;&n;&t;  &quot;jump _ret_from_intr&bslash;n&bslash;t&quot; &bslash;&n;          &quot;_bad_IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;push r0&bslash;n&bslash;t&quot; &bslash;&n;&t;  BLOCK_IRQ(mask,nr) &bslash;&n;&t;  &quot;pop r0&bslash;n&bslash;t&quot;);
macro_line|#endif  /* _ASM_IRQ_H */
eof
