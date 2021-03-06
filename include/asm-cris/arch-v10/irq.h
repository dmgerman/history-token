multiline_comment|/*&n; * Interrupt handling assembler and defines for Linux/CRISv10&n; */
macro_line|#ifndef _ASM_ARCH_IRQ_H
DECL|macro|_ASM_ARCH_IRQ_H
mdefine_line|#define _ASM_ARCH_IRQ_H
macro_line|#include &lt;asm/arch/sv_addr_ag.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 32
multiline_comment|/* The first vector number used for IRQs in v10 is really 0x20 */
multiline_comment|/* but all the code and constants are offseted to make 0 the first */
DECL|macro|FIRST_IRQ
mdefine_line|#define FIRST_IRQ 0
DECL|macro|SOME_IRQ_NBR
mdefine_line|#define SOME_IRQ_NBR        IO_BITNR(R_VECT_MASK_RD, some)   /* 0 ? */
DECL|macro|NMI_IRQ_NBR
mdefine_line|#define NMI_IRQ_NBR         IO_BITNR(R_VECT_MASK_RD, nmi)    /* 1 */
DECL|macro|TIMER0_IRQ_NBR
mdefine_line|#define TIMER0_IRQ_NBR      IO_BITNR(R_VECT_MASK_RD, timer0) /* 2 */
DECL|macro|TIMER1_IRQ_NBR
mdefine_line|#define TIMER1_IRQ_NBR      IO_BITNR(R_VECT_MASK_RD, timer1) /* 3 */
multiline_comment|/* mio, ata, par0, scsi0 on 4 */
multiline_comment|/* par1, scsi1 on 5 */
DECL|macro|NETWORK_STATUS_IRQ_NBR
mdefine_line|#define NETWORK_STATUS_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, network) /* 6 */
DECL|macro|SERIAL_IRQ_NBR
mdefine_line|#define SERIAL_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, serial) /* 8 */
DECL|macro|PA_IRQ_NBR
mdefine_line|#define PA_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, pa) /* 11 */
multiline_comment|/* extdma0 and extdma1 is at irq 12 and 13 and/or same as dma5 and dma6 ? */
DECL|macro|EXTDMA0_IRQ_NBR
mdefine_line|#define EXTDMA0_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, ext_dma0)
DECL|macro|EXTDMA1_IRQ_NBR
mdefine_line|#define EXTDMA1_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, ext_dma1)
multiline_comment|/* dma0-9 is irq 16..25 */
multiline_comment|/* 16,17: network */
DECL|macro|DMA0_TX_IRQ_NBR
mdefine_line|#define DMA0_TX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma0)
DECL|macro|DMA1_RX_IRQ_NBR
mdefine_line|#define DMA1_RX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma1)
DECL|macro|NETWORK_DMA_TX_IRQ_NBR
mdefine_line|#define NETWORK_DMA_TX_IRQ_NBR DMA0_TX_IRQ_NBR
DECL|macro|NETWORK_DMA_RX_IRQ_NBR
mdefine_line|#define NETWORK_DMA_RX_IRQ_NBR DMA1_RX_IRQ_NBR
multiline_comment|/* 18,19: dma2 and dma3 shared by par0, scsi0, ser2 and ata */
DECL|macro|DMA2_TX_IRQ_NBR
mdefine_line|#define DMA2_TX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma2)
DECL|macro|DMA3_RX_IRQ_NBR
mdefine_line|#define DMA3_RX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma3)
DECL|macro|SER2_DMA_TX_IRQ_NBR
mdefine_line|#define SER2_DMA_TX_IRQ_NBR DMA2_TX_IRQ_NBR
DECL|macro|SER2_DMA_RX_IRQ_NBR
mdefine_line|#define SER2_DMA_RX_IRQ_NBR DMA3_RX_IRQ_NBR
multiline_comment|/* 20,21: dma4 and dma5 shared by par1, scsi1, ser3 and extdma0 */
DECL|macro|DMA4_TX_IRQ_NBR
mdefine_line|#define DMA4_TX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma4)
DECL|macro|DMA5_RX_IRQ_NBR
mdefine_line|#define DMA5_RX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma5)
DECL|macro|SER3_DMA_TX_IRQ_NBR
mdefine_line|#define SER3_DMA_TX_IRQ_NBR DMA4_TX_IRQ_NBR
DECL|macro|SER3_DMA_RX_IRQ_NBR
mdefine_line|#define SER3_DMA_RX_IRQ_NBR DMA5_RX_IRQ_NBR
multiline_comment|/* 22,23: dma6 and dma7 shared by ser0, extdma1 and mem2mem */
DECL|macro|DMA6_TX_IRQ_NBR
mdefine_line|#define DMA6_TX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma6)
DECL|macro|DMA7_RX_IRQ_NBR
mdefine_line|#define DMA7_RX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma7)
DECL|macro|SER0_DMA_TX_IRQ_NBR
mdefine_line|#define SER0_DMA_TX_IRQ_NBR DMA6_TX_IRQ_NBR
DECL|macro|SER0_DMA_RX_IRQ_NBR
mdefine_line|#define SER0_DMA_RX_IRQ_NBR DMA7_RX_IRQ_NBR
DECL|macro|MEM2MEM_DMA_TX_IRQ_NBR
mdefine_line|#define MEM2MEM_DMA_TX_IRQ_NBR DMA6_TX_IRQ_NBR
DECL|macro|MEM2MEM_DMA_RX_IRQ_NBR
mdefine_line|#define MEM2MEM_DMA_RX_IRQ_NBR DMA7_RX_IRQ_NBR
multiline_comment|/* 24,25: dma8 and dma9 shared by ser1 and usb */
DECL|macro|DMA8_TX_IRQ_NBR
mdefine_line|#define DMA8_TX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma8)
DECL|macro|DMA9_RX_IRQ_NBR
mdefine_line|#define DMA9_RX_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, dma9)
DECL|macro|SER1_DMA_TX_IRQ_NBR
mdefine_line|#define SER1_DMA_TX_IRQ_NBR DMA8_TX_IRQ_NBR
DECL|macro|SER1_DMA_RX_IRQ_NBR
mdefine_line|#define SER1_DMA_RX_IRQ_NBR DMA9_RX_IRQ_NBR
DECL|macro|USB_DMA_TX_IRQ_NBR
mdefine_line|#define USB_DMA_TX_IRQ_NBR DMA8_TX_IRQ_NBR
DECL|macro|USB_DMA_RX_IRQ_NBR
mdefine_line|#define USB_DMA_RX_IRQ_NBR DMA9_RX_IRQ_NBR
multiline_comment|/* usb: controller at irq 31 + uses DMA8 and DMA9 */
DECL|macro|USB_HC_IRQ_NBR
mdefine_line|#define USB_HC_IRQ_NBR IO_BITNR(R_VECT_MASK_RD, usb)
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
DECL|macro|mask_irq
mdefine_line|#define mask_irq(irq_nr) (*R_VECT_MASK_CLR = 1 &lt;&lt; (irq_nr));
DECL|macro|unmask_irq
mdefine_line|#define unmask_irq(irq_nr) (*R_VECT_MASK_SET = 1 &lt;&lt; (irq_nr));
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
multiline_comment|/* SAVE_ALL saves registers so they match pt_regs */
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;  &quot;move $irp,[$sp=$sp-16]&bslash;n&bslash;t&quot; /* push instruction pointer and fake SBFS struct */ &bslash;&n;  &quot;push $srp&bslash;n&bslash;t&quot;       /* push subroutine return pointer */ &bslash;&n;  &quot;push $dccr&bslash;n&bslash;t&quot;      /* push condition codes */ &bslash;&n;  &quot;push $mof&bslash;n&bslash;t&quot;       /* push multiply overflow reg */ &bslash;&n;  &quot;di&bslash;n&bslash;t&quot;             /* need to disable irq&squot;s at this point */&bslash;&n;  &quot;subq 14*4,$sp&bslash;n&bslash;t&quot;   /* make room for r0-r13 */ &bslash;&n;  &quot;movem $r13,[$sp]&bslash;n&bslash;t&quot; /* push the r0-r13 registers */ &bslash;&n;  &quot;push $r10&bslash;n&bslash;t&quot;       /* push orig_r10 */ &bslash;&n;  &quot;clear.d [$sp=$sp-4]&bslash;n&bslash;t&quot;  /* frametype - this is a normal stackframe */
multiline_comment|/* BLOCK_IRQ and UNBLOCK_IRQ do the same as mask_irq and unmask_irq */
DECL|macro|BLOCK_IRQ
mdefine_line|#define BLOCK_IRQ(mask,nr) &bslash;&n;  &quot;move.d &quot; #mask &quot;,$r0&bslash;n&bslash;t&quot; &bslash;&n;  &quot;move.d $r0,[0xb00000d8]&bslash;n&bslash;t&quot; 
DECL|macro|UNBLOCK_IRQ
mdefine_line|#define UNBLOCK_IRQ(mask) &bslash;&n;  &quot;move.d &quot; #mask &quot;,$r0&bslash;n&bslash;t&quot; &bslash;&n;  &quot;move.d $r0,[0xb00000dc]&bslash;n&bslash;t&quot; 
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|sIRQ_NAME
mdefine_line|#define sIRQ_NAME(nr) IRQ_NAME2(sIRQ##nr)
DECL|macro|BAD_IRQ_NAME
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
multiline_comment|/* the asm IRQ handler makes sure the causing IRQ is blocked, then it calls&n;   * do_IRQ (with irq disabled still). after that it unblocks and jumps to&n;   * ret_from_intr (entry.S)&n;   *&n;   * The reason the IRQ is blocked is to allow an sti() before the handler which&n;   * will acknowledge the interrupt is run.&n;   */
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(nr,mask) &bslash;&n;void IRQ_NAME(nr); &bslash;&n;void sIRQ_NAME(nr); &bslash;&n;void BAD_IRQ_NAME(nr); &bslash;&n;__asm__ ( &bslash;&n;          &quot;.text&bslash;n&bslash;t&quot; &bslash;&n;          &quot;IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  SAVE_ALL &bslash;&n;&t;  &quot;sIRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; /* shortcut for the multiple irq handler */ &bslash;&n;&t;  BLOCK_IRQ(mask,nr) /* this must be done to prevent irq loops when we ei later */ &bslash;&n;&t;  &quot;moveq &quot;#nr&quot;,$r10&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;move.d $sp,$r11&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;jsr do_IRQ&bslash;n&bslash;t&quot; /* irq.c, r10 and r11 are arguments */ &bslash;&n;&t;  UNBLOCK_IRQ(mask) &bslash;&n;&t;  &quot;moveq 0,$r9&bslash;n&bslash;t&quot; /* make ret_from_intr realise we came from an irq */ &bslash;&n;&t;  &quot;jump ret_from_intr&bslash;n&bslash;t&quot; &bslash;&n;          &quot;bad_IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;push $r0&bslash;n&bslash;t&quot; &bslash;&n;&t;  BLOCK_IRQ(mask,nr) &bslash;&n;&t;  &quot;pop $r0&bslash;n&bslash;t&quot; &bslash;&n;          &quot;reti&bslash;n&bslash;t&quot; &bslash;&n;          &quot;nop&bslash;n&quot;);
multiline_comment|/* This is subtle. The timer interrupt is crucial and it should not be disabled for &n; * too long. However, if it had been a normal interrupt as per BUILD_IRQ, it would&n; * have been BLOCK&squot;ed, and then softirq&squot;s are run before we return here to UNBLOCK.&n; * If the softirq&squot;s take too much time to run, the timer irq won&squot;t run and the &n; * watchdog will kill us.&n; *&n; * Furthermore, if a lot of other irq&squot;s occur before we return here, the multiple_irq&n; * handler is run and it prioritizes the timer interrupt. However if we had BLOCK&squot;ed&n; * it here, we would not get the multiple_irq at all.&n; *&n; * The non-blocking here is based on the knowledge that the timer interrupt is &n; * registred as a fast interrupt (SA_INTERRUPT) so that we _know_ there will not&n; * be an sti() before the timer irq handler is run to acknowledge the interrupt.&n; */
DECL|macro|BUILD_TIMER_IRQ
mdefine_line|#define BUILD_TIMER_IRQ(nr,mask) &bslash;&n;void IRQ_NAME(nr); &bslash;&n;void sIRQ_NAME(nr); &bslash;&n;void BAD_IRQ_NAME(nr); &bslash;&n;__asm__ ( &bslash;&n;          &quot;.text&bslash;n&bslash;t&quot; &bslash;&n;          &quot;IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  SAVE_ALL &bslash;&n;&t;  &quot;sIRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; /* shortcut for the multiple irq handler */ &bslash;&n;&t;  &quot;moveq &quot;#nr&quot;,$r10&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;move.d $sp,$r11&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;jsr do_IRQ&bslash;n&bslash;t&quot; /* irq.c, r10 and r11 are arguments */ &bslash;&n;&t;  &quot;moveq 0,$r9&bslash;n&bslash;t&quot; /* make ret_from_intr realise we came from an irq */ &bslash;&n;&t;  &quot;jump ret_from_intr&bslash;n&bslash;t&quot; &bslash;&n;          &quot;bad_IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;  &quot;push $r0&bslash;n&bslash;t&quot; &bslash;&n;&t;  BLOCK_IRQ(mask,nr) &bslash;&n;&t;  &quot;pop $r0&bslash;n&bslash;t&quot; &bslash;&n;          &quot;reti&bslash;n&bslash;t&quot; &bslash;&n;          &quot;nop&bslash;n&quot;);
macro_line|#endif
eof
