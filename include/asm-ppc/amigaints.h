multiline_comment|/*&n; * BK Id: SCCS/s.amigaints.h 1.5 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n;** amigaints.h -- Amiga Linux interrupt handling structs and prototypes&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created 10/2/92 by Greg Harp&n;*/
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASMm68k_AMIGAINTS_H_
DECL|macro|_ASMm68k_AMIGAINTS_H_
mdefine_line|#define _ASMm68k_AMIGAINTS_H_
multiline_comment|/*&n;** Amiga Interrupt sources.&n;**&n;*/
DECL|macro|AUTO_IRQS
mdefine_line|#define AUTO_IRQS           (8)
DECL|macro|AMI_STD_IRQS
mdefine_line|#define AMI_STD_IRQS        (14)
DECL|macro|CIA_IRQS
mdefine_line|#define CIA_IRQS            (5)
DECL|macro|AMI_IRQS
mdefine_line|#define AMI_IRQS            (32) /* AUTO_IRQS+AMI_STD_IRQS+2*CIA_IRQS */
multiline_comment|/* vertical blanking interrupt */
DECL|macro|IRQ_AMIGA_VERTB
mdefine_line|#define IRQ_AMIGA_VERTB     0
multiline_comment|/* copper interrupt */
DECL|macro|IRQ_AMIGA_COPPER
mdefine_line|#define IRQ_AMIGA_COPPER    1
multiline_comment|/* Audio interrupts */
DECL|macro|IRQ_AMIGA_AUD0
mdefine_line|#define IRQ_AMIGA_AUD0&t;    2
DECL|macro|IRQ_AMIGA_AUD1
mdefine_line|#define IRQ_AMIGA_AUD1&t;    3
DECL|macro|IRQ_AMIGA_AUD2
mdefine_line|#define IRQ_AMIGA_AUD2&t;    4
DECL|macro|IRQ_AMIGA_AUD3
mdefine_line|#define IRQ_AMIGA_AUD3&t;    5
multiline_comment|/* Blitter done interrupt */
DECL|macro|IRQ_AMIGA_BLIT
mdefine_line|#define IRQ_AMIGA_BLIT&t;    6
multiline_comment|/* floppy disk interrupts */
DECL|macro|IRQ_AMIGA_DSKSYN
mdefine_line|#define IRQ_AMIGA_DSKSYN    7
DECL|macro|IRQ_AMIGA_DSKBLK
mdefine_line|#define IRQ_AMIGA_DSKBLK    8
multiline_comment|/* builtin serial port interrupts */
DECL|macro|IRQ_AMIGA_RBF
mdefine_line|#define IRQ_AMIGA_RBF&t;    9
DECL|macro|IRQ_AMIGA_TBE
mdefine_line|#define IRQ_AMIGA_TBE&t;    10
multiline_comment|/* software interrupts */
DECL|macro|IRQ_AMIGA_SOFT
mdefine_line|#define IRQ_AMIGA_SOFT      11
multiline_comment|/* interrupts from external hardware */
DECL|macro|IRQ_AMIGA_PORTS
mdefine_line|#define IRQ_AMIGA_PORTS&t;    12
DECL|macro|IRQ_AMIGA_EXTER
mdefine_line|#define IRQ_AMIGA_EXTER&t;    13
multiline_comment|/* CIA interrupt sources */
DECL|macro|IRQ_AMIGA_CIAA
mdefine_line|#define IRQ_AMIGA_CIAA      14
DECL|macro|IRQ_AMIGA_CIAA_TA
mdefine_line|#define IRQ_AMIGA_CIAA_TA   14
DECL|macro|IRQ_AMIGA_CIAA_TB
mdefine_line|#define IRQ_AMIGA_CIAA_TB   15
DECL|macro|IRQ_AMIGA_CIAA_ALRM
mdefine_line|#define IRQ_AMIGA_CIAA_ALRM 16
DECL|macro|IRQ_AMIGA_CIAA_SP
mdefine_line|#define IRQ_AMIGA_CIAA_SP   17
DECL|macro|IRQ_AMIGA_CIAA_FLG
mdefine_line|#define IRQ_AMIGA_CIAA_FLG  18
DECL|macro|IRQ_AMIGA_CIAB
mdefine_line|#define IRQ_AMIGA_CIAB      19
DECL|macro|IRQ_AMIGA_CIAB_TA
mdefine_line|#define IRQ_AMIGA_CIAB_TA   19
DECL|macro|IRQ_AMIGA_CIAB_TB
mdefine_line|#define IRQ_AMIGA_CIAB_TB   20
DECL|macro|IRQ_AMIGA_CIAB_ALRM
mdefine_line|#define IRQ_AMIGA_CIAB_ALRM 21
DECL|macro|IRQ_AMIGA_CIAB_SP
mdefine_line|#define IRQ_AMIGA_CIAB_SP   22
DECL|macro|IRQ_AMIGA_CIAB_FLG
mdefine_line|#define IRQ_AMIGA_CIAB_FLG  23
multiline_comment|/* auto-vector interrupts */
DECL|macro|IRQ_AMIGA_AUTO
mdefine_line|#define IRQ_AMIGA_AUTO      24
DECL|macro|IRQ_AMIGA_AUTO_0
mdefine_line|#define IRQ_AMIGA_AUTO_0    24 /* This is just a dummy */
DECL|macro|IRQ_AMIGA_AUTO_1
mdefine_line|#define IRQ_AMIGA_AUTO_1    25
DECL|macro|IRQ_AMIGA_AUTO_2
mdefine_line|#define IRQ_AMIGA_AUTO_2    26
DECL|macro|IRQ_AMIGA_AUTO_3
mdefine_line|#define IRQ_AMIGA_AUTO_3    27
DECL|macro|IRQ_AMIGA_AUTO_4
mdefine_line|#define IRQ_AMIGA_AUTO_4    28
DECL|macro|IRQ_AMIGA_AUTO_5
mdefine_line|#define IRQ_AMIGA_AUTO_5    29
DECL|macro|IRQ_AMIGA_AUTO_6
mdefine_line|#define IRQ_AMIGA_AUTO_6    30
DECL|macro|IRQ_AMIGA_AUTO_7
mdefine_line|#define IRQ_AMIGA_AUTO_7    31
DECL|macro|IRQ_FLOPPY
mdefine_line|#define IRQ_FLOPPY&t;    IRQ_AMIGA_DSKBLK
multiline_comment|/* INTREQR masks */
DECL|macro|IRQ1_MASK
mdefine_line|#define IRQ1_MASK   0x0007&t;/* INTREQR mask for IRQ 1 */
DECL|macro|IRQ2_MASK
mdefine_line|#define IRQ2_MASK   0x0008&t;/* INTREQR mask for IRQ 2 */
DECL|macro|IRQ3_MASK
mdefine_line|#define IRQ3_MASK   0x0070&t;/* INTREQR mask for IRQ 3 */
DECL|macro|IRQ4_MASK
mdefine_line|#define IRQ4_MASK   0x0780&t;/* INTREQR mask for IRQ 4 */
DECL|macro|IRQ5_MASK
mdefine_line|#define IRQ5_MASK   0x1800&t;/* INTREQR mask for IRQ 5 */
DECL|macro|IRQ6_MASK
mdefine_line|#define IRQ6_MASK   0x2000&t;/* INTREQR mask for IRQ 6 */
DECL|macro|IRQ7_MASK
mdefine_line|#define IRQ7_MASK   0x4000&t;/* INTREQR mask for IRQ 7 */
DECL|macro|IF_SETCLR
mdefine_line|#define IF_SETCLR   0x8000      /* set/clr bit */
DECL|macro|IF_INTEN
mdefine_line|#define IF_INTEN    0x4000&t;/* master interrupt bit in INT* registers */
DECL|macro|IF_EXTER
mdefine_line|#define IF_EXTER    0x2000&t;/* external level 6 and CIA B interrupt */
DECL|macro|IF_DSKSYN
mdefine_line|#define IF_DSKSYN   0x1000&t;/* disk sync interrupt */
DECL|macro|IF_RBF
mdefine_line|#define IF_RBF&t;    0x0800&t;/* serial receive buffer full interrupt */
DECL|macro|IF_AUD3
mdefine_line|#define IF_AUD3     0x0400&t;/* audio channel 3 done interrupt */
DECL|macro|IF_AUD2
mdefine_line|#define IF_AUD2     0x0200&t;/* audio channel 2 done interrupt */
DECL|macro|IF_AUD1
mdefine_line|#define IF_AUD1     0x0100&t;/* audio channel 1 done interrupt */
DECL|macro|IF_AUD0
mdefine_line|#define IF_AUD0     0x0080&t;/* audio channel 0 done interrupt */
DECL|macro|IF_BLIT
mdefine_line|#define IF_BLIT     0x0040&t;/* blitter done interrupt */
DECL|macro|IF_VERTB
mdefine_line|#define IF_VERTB    0x0020&t;/* vertical blanking interrupt */
DECL|macro|IF_COPER
mdefine_line|#define IF_COPER    0x0010&t;/* copper interrupt */
DECL|macro|IF_PORTS
mdefine_line|#define IF_PORTS    0x0008&t;/* external level 2 and CIA A interrupt */
DECL|macro|IF_SOFT
mdefine_line|#define IF_SOFT     0x0004&t;/* software initiated interrupt */
DECL|macro|IF_DSKBLK
mdefine_line|#define IF_DSKBLK   0x0002&t;/* diskblock DMA finished */
DECL|macro|IF_TBE
mdefine_line|#define IF_TBE&t;    0x0001&t;/* serial transmit buffer empty interrupt */
DECL|struct|irq_server
r_struct
id|irq_server
(brace
DECL|member|count
DECL|member|reentrance
r_int
r_int
id|count
comma
id|reentrance
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|amiga_do_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_extern
r_void
id|amiga_do_irq_list
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
comma
r_struct
id|irq_server
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* CIA interrupt control register bits */
DECL|macro|CIA_ICR_TA
mdefine_line|#define CIA_ICR_TA&t;0x01
DECL|macro|CIA_ICR_TB
mdefine_line|#define CIA_ICR_TB&t;0x02
DECL|macro|CIA_ICR_ALRM
mdefine_line|#define CIA_ICR_ALRM&t;0x04
DECL|macro|CIA_ICR_SP
mdefine_line|#define CIA_ICR_SP&t;0x08
DECL|macro|CIA_ICR_FLG
mdefine_line|#define CIA_ICR_FLG&t;0x10
DECL|macro|CIA_ICR_ALL
mdefine_line|#define CIA_ICR_ALL&t;0x1f
DECL|macro|CIA_ICR_SETCLR
mdefine_line|#define CIA_ICR_SETCLR&t;0x80
multiline_comment|/* to access the interrupt control registers of CIA&squot;s use only&n;** these functions, they behave exactly like the amiga os routines&n;*/
r_extern
r_struct
id|ciabase
id|ciaa_base
comma
id|ciab_base
suffix:semicolon
r_extern
r_int
r_char
id|cia_set_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
id|set
)paren
suffix:semicolon
r_extern
r_int
r_char
id|cia_able_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
id|enable
)paren
suffix:semicolon
macro_line|#endif /* asm-m68k/amigaints.h */
macro_line|#endif /* __KERNEL__ */
eof
