macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;&t;/* ppc_md */
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * These constants are used for passing information about interrupt&n; * signal polarity and level/edge sensing to the low-level PIC chip&n; * drivers.&n; */
DECL|macro|IRQ_SENSE_MASK
mdefine_line|#define IRQ_SENSE_MASK&t;&t;0x1
DECL|macro|IRQ_SENSE_LEVEL
mdefine_line|#define IRQ_SENSE_LEVEL&t;&t;0x1&t;/* interrupt on active level */
DECL|macro|IRQ_SENSE_EDGE
mdefine_line|#define IRQ_SENSE_EDGE&t;&t;0x0&t;/* interrupt triggered by edge */
DECL|macro|IRQ_POLARITY_MASK
mdefine_line|#define IRQ_POLARITY_MASK&t;0x2
DECL|macro|IRQ_POLARITY_POSITIVE
mdefine_line|#define IRQ_POLARITY_POSITIVE&t;0x2&t;/* high level or low-&gt;high edge */
DECL|macro|IRQ_POLARITY_NEGATIVE
mdefine_line|#define IRQ_POLARITY_NEGATIVE&t;0x0&t;/* low level or high-&gt;low edge */
macro_line|#if defined(CONFIG_40x)
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#ifndef NR_BOARD_IRQS
DECL|macro|NR_BOARD_IRQS
mdefine_line|#define NR_BOARD_IRQS 0
macro_line|#endif
macro_line|#ifndef UIC_WIDTH /* Number of interrupts per device */
DECL|macro|UIC_WIDTH
mdefine_line|#define UIC_WIDTH 32
macro_line|#endif
macro_line|#ifndef NR_UICS /* number  of UIC devices */
DECL|macro|NR_UICS
mdefine_line|#define NR_UICS 1
macro_line|#endif
macro_line|#if defined (CONFIG_403)
multiline_comment|/*&n; * The PowerPC 403 cores&squot; Asynchronous Interrupt Controller (AIC) has&n; * 32 possible interrupts, a majority of which are not implemented on&n; * all cores. There are six configurable, external interrupt pins and&n; * there are eight internal interrupts for the on-chip serial port&n; * (SPU), DMA controller, and JTAG controller.&n; *&n; */
DECL|macro|NR_AIC_IRQS
mdefine_line|#define&t;NR_AIC_IRQS 32
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t; (NR_AIC_IRQS + NR_BOARD_IRQS)
macro_line|#elif !defined (CONFIG_403)
multiline_comment|/*&n; *  The PowerPC 405 cores&squot; Universal Interrupt Controller (UIC) has 32&n; * possible interrupts as well. There are seven, configurable external&n; * interrupt pins and there are 17 internal interrupts for the on-chip&n; * serial port, DMA controller, on-chip Ethernet controller, PCI, etc.&n; *&n; */
DECL|macro|NR_UIC_IRQS
mdefine_line|#define NR_UIC_IRQS UIC_WIDTH
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;((NR_UIC_IRQS * NR_UICS) + NR_BOARD_IRQS)
macro_line|#endif
r_static
id|__inline__
r_int
DECL|function|irq_canonicalize
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_44x)
macro_line|#include &lt;asm/ibm44x.h&gt;
DECL|macro|NR_UIC_IRQS
mdefine_line|#define&t;NR_UIC_IRQS&t;32
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;&t;((NR_UIC_IRQS * NR_UICS) + NR_BOARD_IRQS)
r_static
id|__inline__
r_int
DECL|function|irq_canonicalize
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
id|irq
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_8xx)
multiline_comment|/* Now include the board configuration specific associations.&n;*/
macro_line|#include &lt;asm/mpc8xx.h&gt;
multiline_comment|/* The MPC8xx cores have 16 possible interrupts.  There are eight&n; * possible level sensitive interrupts assigned and generated internally&n; * from such devices as CPM, PCMCIA, RTC, PIT, TimeBase and Decrementer.&n; * There are eight external interrupts (IRQs) that can be configured&n; * as either level or edge sensitive.&n; *&n; * On some implementations, there is also the possibility of an 8259&n; * through the PCI and PCI-ISA bridges.&n; *&n; * We are &quot;flattening&quot; the interrupt vectors of the cascaded CPM&n; * and 8259 interrupt controllers so that we can uniquely identify&n; * any interrupt source with a single integer.&n; */
DECL|macro|NR_SIU_INTS
mdefine_line|#define NR_SIU_INTS&t;16
DECL|macro|NR_CPM_INTS
mdefine_line|#define NR_CPM_INTS&t;32
macro_line|#ifndef NR_8259_INTS
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS 0
macro_line|#endif
DECL|macro|SIU_IRQ_OFFSET
mdefine_line|#define SIU_IRQ_OFFSET&t;&t;0
DECL|macro|CPM_IRQ_OFFSET
mdefine_line|#define CPM_IRQ_OFFSET&t;&t;(SIU_IRQ_OFFSET + NR_SIU_INTS)
DECL|macro|I8259_IRQ_OFFSET
mdefine_line|#define I8259_IRQ_OFFSET&t;(CPM_IRQ_OFFSET + NR_CPM_INTS)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;(NR_SIU_INTS + NR_CPM_INTS + NR_8259_INTS)
multiline_comment|/* These values must be zero-based and map 1:1 with the SIU configuration.&n; * They are used throughout the 8xx I/O subsystem to generate&n; * interrupt masks, flags, and other control patterns.  This is why the&n; * current kernel assumption of the 8259 as the base controller is such&n; * a pain in the butt.&n; */
DECL|macro|SIU_IRQ0
mdefine_line|#define&t;SIU_IRQ0&t;(0)&t;/* Highest priority */
DECL|macro|SIU_LEVEL0
mdefine_line|#define&t;SIU_LEVEL0&t;(1)
DECL|macro|SIU_IRQ1
mdefine_line|#define&t;SIU_IRQ1&t;(2)
DECL|macro|SIU_LEVEL1
mdefine_line|#define&t;SIU_LEVEL1&t;(3)
DECL|macro|SIU_IRQ2
mdefine_line|#define&t;SIU_IRQ2&t;(4)
DECL|macro|SIU_LEVEL2
mdefine_line|#define&t;SIU_LEVEL2&t;(5)
DECL|macro|SIU_IRQ3
mdefine_line|#define&t;SIU_IRQ3&t;(6)
DECL|macro|SIU_LEVEL3
mdefine_line|#define&t;SIU_LEVEL3&t;(7)
DECL|macro|SIU_IRQ4
mdefine_line|#define&t;SIU_IRQ4&t;(8)
DECL|macro|SIU_LEVEL4
mdefine_line|#define&t;SIU_LEVEL4&t;(9)
DECL|macro|SIU_IRQ5
mdefine_line|#define&t;SIU_IRQ5&t;(10)
DECL|macro|SIU_LEVEL5
mdefine_line|#define&t;SIU_LEVEL5&t;(11)
DECL|macro|SIU_IRQ6
mdefine_line|#define&t;SIU_IRQ6&t;(12)
DECL|macro|SIU_LEVEL6
mdefine_line|#define&t;SIU_LEVEL6&t;(13)
DECL|macro|SIU_IRQ7
mdefine_line|#define&t;SIU_IRQ7&t;(14)
DECL|macro|SIU_LEVEL7
mdefine_line|#define&t;SIU_LEVEL7&t;(15)
multiline_comment|/* The internal interrupts we can configure as we see fit.&n; * My personal preference is CPM at level 2, which puts it above the&n; * MBX PCI/ISA/IDE interrupts.&n; */
macro_line|#ifndef PIT_INTERRUPT
DECL|macro|PIT_INTERRUPT
mdefine_line|#define PIT_INTERRUPT&t;&t;SIU_LEVEL0
macro_line|#endif
macro_line|#ifndef&t;CPM_INTERRUPT
DECL|macro|CPM_INTERRUPT
mdefine_line|#define CPM_INTERRUPT&t;&t;SIU_LEVEL2
macro_line|#endif
macro_line|#ifndef&t;PCMCIA_INTERRUPT
DECL|macro|PCMCIA_INTERRUPT
mdefine_line|#define PCMCIA_INTERRUPT&t;SIU_LEVEL6
macro_line|#endif
macro_line|#ifndef&t;DEC_INTERRUPT
DECL|macro|DEC_INTERRUPT
mdefine_line|#define DEC_INTERRUPT&t;&t;SIU_LEVEL7
macro_line|#endif
multiline_comment|/* Some internal interrupt registers use an 8-bit mask for the interrupt&n; * level instead of a number.&n; */
DECL|macro|mk_int_int_mask
mdefine_line|#define&t;mk_int_int_mask(IL) (1 &lt;&lt; (7 - (IL/2)))
multiline_comment|/* always the same on 8xx -- Cort */
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_83xx)
macro_line|#include &lt;asm/mpc83xx.h&gt;
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
DECL|macro|NR_IRQS
mdefine_line|#define&t;NR_IRQS&t;(NR_IPIC_INTS)
macro_line|#elif defined(CONFIG_85xx)
multiline_comment|/* Now include the board configuration specific associations.&n;*/
macro_line|#include &lt;asm/mpc85xx.h&gt;
multiline_comment|/* The MPC8560 openpic has  32 internal interrupts and 12 external&n; * interrupts.&n; *&n; * We are &quot;flattening&quot; the interrupt vectors of the cascaded CPM&n; * so that we can uniquely identify any interrupt source with a&n; * single integer.&n; */
DECL|macro|NR_CPM_INTS
mdefine_line|#define NR_CPM_INTS&t;64
DECL|macro|NR_EPIC_INTS
mdefine_line|#define NR_EPIC_INTS&t;44
macro_line|#ifndef NR_8259_INTS
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
macro_line|#endif
DECL|macro|NUM_8259_INTERRUPTS
mdefine_line|#define NUM_8259_INTERRUPTS NR_8259_INTS
macro_line|#ifndef CPM_IRQ_OFFSET
DECL|macro|CPM_IRQ_OFFSET
mdefine_line|#define CPM_IRQ_OFFSET&t;0
macro_line|#endif
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;(NR_EPIC_INTS + NR_CPM_INTS + NR_8259_INTS)
multiline_comment|/* Internal IRQs on MPC85xx OpenPIC */
macro_line|#ifndef MPC85xx_OPENPIC_IRQ_OFFSET
macro_line|#ifdef CONFIG_CPM2
DECL|macro|MPC85xx_OPENPIC_IRQ_OFFSET
mdefine_line|#define MPC85xx_OPENPIC_IRQ_OFFSET&t;(CPM_IRQ_OFFSET + NR_CPM_INTS)
macro_line|#else
DECL|macro|MPC85xx_OPENPIC_IRQ_OFFSET
mdefine_line|#define MPC85xx_OPENPIC_IRQ_OFFSET&t;0
macro_line|#endif
macro_line|#endif
multiline_comment|/* Not all of these exist on all MPC85xx implementations */
DECL|macro|MPC85xx_IRQ_L2CACHE
mdefine_line|#define MPC85xx_IRQ_L2CACHE&t;( 0 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_ECM
mdefine_line|#define MPC85xx_IRQ_ECM&t;&t;( 1 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DDR
mdefine_line|#define MPC85xx_IRQ_DDR&t;&t;( 2 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_LBIU
mdefine_line|#define MPC85xx_IRQ_LBIU&t;( 3 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DMA0
mdefine_line|#define MPC85xx_IRQ_DMA0&t;( 4 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DMA1
mdefine_line|#define MPC85xx_IRQ_DMA1&t;( 5 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DMA2
mdefine_line|#define MPC85xx_IRQ_DMA2&t;( 6 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DMA3
mdefine_line|#define MPC85xx_IRQ_DMA3&t;( 7 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_PCI1
mdefine_line|#define MPC85xx_IRQ_PCI1&t;( 8 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_PCI2
mdefine_line|#define MPC85xx_IRQ_PCI2&t;( 9 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_RIO_ERROR
mdefine_line|#define MPC85xx_IRQ_RIO_ERROR&t;( 9 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_RIO_BELL
mdefine_line|#define MPC85xx_IRQ_RIO_BELL&t;(10 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_RIO_TX
mdefine_line|#define MPC85xx_IRQ_RIO_TX&t;(11 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_RIO_RX
mdefine_line|#define MPC85xx_IRQ_RIO_RX&t;(12 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC1_TX
mdefine_line|#define MPC85xx_IRQ_TSEC1_TX&t;(13 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC1_RX
mdefine_line|#define MPC85xx_IRQ_TSEC1_RX&t;(14 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC1_ERROR
mdefine_line|#define MPC85xx_IRQ_TSEC1_ERROR&t;(18 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC2_TX
mdefine_line|#define MPC85xx_IRQ_TSEC2_TX&t;(19 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC2_RX
mdefine_line|#define MPC85xx_IRQ_TSEC2_RX&t;(20 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_TSEC2_ERROR
mdefine_line|#define MPC85xx_IRQ_TSEC2_ERROR&t;(24 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_FEC
mdefine_line|#define MPC85xx_IRQ_FEC&t;&t;(25 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_DUART
mdefine_line|#define MPC85xx_IRQ_DUART&t;(26 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_IIC1
mdefine_line|#define MPC85xx_IRQ_IIC1&t;(27 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_PERFMON
mdefine_line|#define MPC85xx_IRQ_PERFMON&t;(28 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_SEC2
mdefine_line|#define MPC85xx_IRQ_SEC2&t;(29 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_CPM
mdefine_line|#define MPC85xx_IRQ_CPM&t;&t;(30 + MPC85xx_OPENPIC_IRQ_OFFSET)
multiline_comment|/* The 12 external interrupt lines */
DECL|macro|MPC85xx_IRQ_EXT0
mdefine_line|#define MPC85xx_IRQ_EXT0        (32 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT1
mdefine_line|#define MPC85xx_IRQ_EXT1        (33 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT2
mdefine_line|#define MPC85xx_IRQ_EXT2        (34 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT3
mdefine_line|#define MPC85xx_IRQ_EXT3        (35 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT4
mdefine_line|#define MPC85xx_IRQ_EXT4        (36 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT5
mdefine_line|#define MPC85xx_IRQ_EXT5        (37 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT6
mdefine_line|#define MPC85xx_IRQ_EXT6        (38 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT7
mdefine_line|#define MPC85xx_IRQ_EXT7        (39 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT8
mdefine_line|#define MPC85xx_IRQ_EXT8        (40 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT9
mdefine_line|#define MPC85xx_IRQ_EXT9        (41 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT10
mdefine_line|#define MPC85xx_IRQ_EXT10       (42 + MPC85xx_OPENPIC_IRQ_OFFSET)
DECL|macro|MPC85xx_IRQ_EXT11
mdefine_line|#define MPC85xx_IRQ_EXT11       (43 + MPC85xx_OPENPIC_IRQ_OFFSET)
multiline_comment|/* CPM related interrupts */
DECL|macro|SIU_INT_ERROR
mdefine_line|#define&t;SIU_INT_ERROR&t;&t;((uint)0x00+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_I2C
mdefine_line|#define&t;SIU_INT_I2C&t;&t;((uint)0x01+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SPI
mdefine_line|#define&t;SIU_INT_SPI&t;&t;((uint)0x02+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_RISC
mdefine_line|#define&t;SIU_INT_RISC&t;&t;((uint)0x03+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SMC1
mdefine_line|#define&t;SIU_INT_SMC1&t;&t;((uint)0x04+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SMC2
mdefine_line|#define&t;SIU_INT_SMC2&t;&t;((uint)0x05+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_USB
mdefine_line|#define&t;SIU_INT_USB&t;&t;((uint)0x0b+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER1
mdefine_line|#define&t;SIU_INT_TIMER1&t;&t;((uint)0x0c+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER2
mdefine_line|#define&t;SIU_INT_TIMER2&t;&t;((uint)0x0d+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER3
mdefine_line|#define&t;SIU_INT_TIMER3&t;&t;((uint)0x0e+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER4
mdefine_line|#define&t;SIU_INT_TIMER4&t;&t;((uint)0x0f+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC1
mdefine_line|#define&t;SIU_INT_FCC1&t;&t;((uint)0x20+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC2
mdefine_line|#define&t;SIU_INT_FCC2&t;&t;((uint)0x21+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC3
mdefine_line|#define&t;SIU_INT_FCC3&t;&t;((uint)0x22+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_MCC1
mdefine_line|#define&t;SIU_INT_MCC1&t;&t;((uint)0x24+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_MCC2
mdefine_line|#define&t;SIU_INT_MCC2&t;&t;((uint)0x25+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC1
mdefine_line|#define&t;SIU_INT_SCC1&t;&t;((uint)0x28+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC2
mdefine_line|#define&t;SIU_INT_SCC2&t;&t;((uint)0x29+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC3
mdefine_line|#define&t;SIU_INT_SCC3&t;&t;((uint)0x2a+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC4
mdefine_line|#define&t;SIU_INT_SCC4&t;&t;((uint)0x2b+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC15
mdefine_line|#define&t;SIU_INT_PC15&t;&t;((uint)0x30+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC14
mdefine_line|#define&t;SIU_INT_PC14&t;&t;((uint)0x31+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC13
mdefine_line|#define&t;SIU_INT_PC13&t;&t;((uint)0x32+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC12
mdefine_line|#define&t;SIU_INT_PC12&t;&t;((uint)0x33+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC11
mdefine_line|#define&t;SIU_INT_PC11&t;&t;((uint)0x34+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC10
mdefine_line|#define&t;SIU_INT_PC10&t;&t;((uint)0x35+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC9
mdefine_line|#define&t;SIU_INT_PC9&t;&t;((uint)0x36+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC8
mdefine_line|#define&t;SIU_INT_PC8&t;&t;((uint)0x37+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC7
mdefine_line|#define&t;SIU_INT_PC7&t;&t;((uint)0x38+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC6
mdefine_line|#define&t;SIU_INT_PC6&t;&t;((uint)0x39+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC5
mdefine_line|#define&t;SIU_INT_PC5&t;&t;((uint)0x3a+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC4
mdefine_line|#define&t;SIU_INT_PC4&t;&t;((uint)0x3b+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC3
mdefine_line|#define&t;SIU_INT_PC3&t;&t;((uint)0x3c+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC2
mdefine_line|#define&t;SIU_INT_PC2&t;&t;((uint)0x3d+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC1
mdefine_line|#define&t;SIU_INT_PC1&t;&t;((uint)0x3e+CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC0
mdefine_line|#define&t;SIU_INT_PC0&t;&t;((uint)0x3f+CPM_IRQ_OFFSET)
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
macro_line|#else /* CONFIG_40x + CONFIG_8xx */
multiline_comment|/*&n; * this is the # irq&squot;s for all ppc arch&squot;s (pmac/chrp/prep)&n; * so it is the max of them all&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;256
macro_line|#ifndef CONFIG_8260
DECL|macro|NUM_8259_INTERRUPTS
mdefine_line|#define NUM_8259_INTERRUPTS&t;16
macro_line|#else /* CONFIG_8260 */
multiline_comment|/* The 8260 has an internal interrupt controller with a maximum of&n; * 64 IRQs.  We will use NR_IRQs from above since it is large enough.&n; * Don&squot;t be confused by the 8260 documentation where they list an&n; * &quot;interrupt number&quot; and &quot;interrupt vector&quot;.  We are only interested&n; * in the interrupt vector.  There are &quot;reserved&quot; holes where the&n; * vector number increases, but the interrupt number in the table does not.&n; * (Document errata updates have fixed this...make sure you have up to&n; * date processor documentation -- Dan).&n; */
macro_line|#ifndef CPM_IRQ_OFFSET
DECL|macro|CPM_IRQ_OFFSET
mdefine_line|#define CPM_IRQ_OFFSET&t;0
macro_line|#endif
DECL|macro|NR_CPM_INTS
mdefine_line|#define NR_CPM_INTS&t;64
DECL|macro|SIU_INT_ERROR
mdefine_line|#define&t;SIU_INT_ERROR&t;&t;((uint)0x00 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_I2C
mdefine_line|#define&t;SIU_INT_I2C&t;&t;((uint)0x01 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SPI
mdefine_line|#define&t;SIU_INT_SPI&t;&t;((uint)0x02 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_RISC
mdefine_line|#define&t;SIU_INT_RISC&t;&t;((uint)0x03 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SMC1
mdefine_line|#define&t;SIU_INT_SMC1&t;&t;((uint)0x04 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SMC2
mdefine_line|#define&t;SIU_INT_SMC2&t;&t;((uint)0x05 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IDMA1
mdefine_line|#define&t;SIU_INT_IDMA1&t;&t;((uint)0x06 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IDMA2
mdefine_line|#define&t;SIU_INT_IDMA2&t;&t;((uint)0x07 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IDMA3
mdefine_line|#define&t;SIU_INT_IDMA3&t;&t;((uint)0x08 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IDMA4
mdefine_line|#define&t;SIU_INT_IDMA4&t;&t;((uint)0x09 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SDMA
mdefine_line|#define&t;SIU_INT_SDMA&t;&t;((uint)0x0a + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER1
mdefine_line|#define&t;SIU_INT_TIMER1&t;&t;((uint)0x0c + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER2
mdefine_line|#define&t;SIU_INT_TIMER2&t;&t;((uint)0x0d + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER3
mdefine_line|#define&t;SIU_INT_TIMER3&t;&t;((uint)0x0e + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TIMER4
mdefine_line|#define&t;SIU_INT_TIMER4&t;&t;((uint)0x0f + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_TMCNT
mdefine_line|#define&t;SIU_INT_TMCNT&t;&t;((uint)0x10 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PIT
mdefine_line|#define&t;SIU_INT_PIT&t;&t;((uint)0x11 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ1
mdefine_line|#define&t;SIU_INT_IRQ1&t;&t;((uint)0x13 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ2
mdefine_line|#define&t;SIU_INT_IRQ2&t;&t;((uint)0x14 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ3
mdefine_line|#define&t;SIU_INT_IRQ3&t;&t;((uint)0x15 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ4
mdefine_line|#define&t;SIU_INT_IRQ4&t;&t;((uint)0x16 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ5
mdefine_line|#define&t;SIU_INT_IRQ5&t;&t;((uint)0x17 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ6
mdefine_line|#define&t;SIU_INT_IRQ6&t;&t;((uint)0x18 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_IRQ7
mdefine_line|#define&t;SIU_INT_IRQ7&t;&t;((uint)0x19 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC1
mdefine_line|#define&t;SIU_INT_FCC1&t;&t;((uint)0x20 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC2
mdefine_line|#define&t;SIU_INT_FCC2&t;&t;((uint)0x21 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_FCC3
mdefine_line|#define&t;SIU_INT_FCC3&t;&t;((uint)0x22 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_MCC1
mdefine_line|#define&t;SIU_INT_MCC1&t;&t;((uint)0x24 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_MCC2
mdefine_line|#define&t;SIU_INT_MCC2&t;&t;((uint)0x25 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC1
mdefine_line|#define&t;SIU_INT_SCC1&t;&t;((uint)0x28 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC2
mdefine_line|#define&t;SIU_INT_SCC2&t;&t;((uint)0x29 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC3
mdefine_line|#define&t;SIU_INT_SCC3&t;&t;((uint)0x2a + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_SCC4
mdefine_line|#define&t;SIU_INT_SCC4&t;&t;((uint)0x2b + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC15
mdefine_line|#define&t;SIU_INT_PC15&t;&t;((uint)0x30 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC14
mdefine_line|#define&t;SIU_INT_PC14&t;&t;((uint)0x31 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC13
mdefine_line|#define&t;SIU_INT_PC13&t;&t;((uint)0x32 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC12
mdefine_line|#define&t;SIU_INT_PC12&t;&t;((uint)0x33 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC11
mdefine_line|#define&t;SIU_INT_PC11&t;&t;((uint)0x34 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC10
mdefine_line|#define&t;SIU_INT_PC10&t;&t;((uint)0x35 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC9
mdefine_line|#define&t;SIU_INT_PC9&t;&t;((uint)0x36 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC8
mdefine_line|#define&t;SIU_INT_PC8&t;&t;((uint)0x37 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC7
mdefine_line|#define&t;SIU_INT_PC7&t;&t;((uint)0x38 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC6
mdefine_line|#define&t;SIU_INT_PC6&t;&t;((uint)0x39 + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC5
mdefine_line|#define&t;SIU_INT_PC5&t;&t;((uint)0x3a + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC4
mdefine_line|#define&t;SIU_INT_PC4&t;&t;((uint)0x3b + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC3
mdefine_line|#define&t;SIU_INT_PC3&t;&t;((uint)0x3c + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC2
mdefine_line|#define&t;SIU_INT_PC2&t;&t;((uint)0x3d + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC1
mdefine_line|#define&t;SIU_INT_PC1&t;&t;((uint)0x3e + CPM_IRQ_OFFSET)
DECL|macro|SIU_INT_PC0
mdefine_line|#define&t;SIU_INT_PC0&t;&t;((uint)0x3f + CPM_IRQ_OFFSET)
macro_line|#endif /* CONFIG_8260 */
multiline_comment|/*&n; * This gets called from serial.c, which is now used on&n; * powermacs as well as prep/chrp boxes.&n; * Prep and chrp both have cascaded 8259 PICs.&n; */
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.irq_canonicalize
)paren
r_return
id|ppc_md
dot
id|irq_canonicalize
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|NR_MASK_WORDS
mdefine_line|#define NR_MASK_WORDS&t;((NR_IRQS + 31) / 32)
multiline_comment|/* pedantic: these are long because they are used with set_bit --RR */
r_extern
r_int
r_int
id|ppc_cached_irq_mask
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|ppc_lost_interrupts
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
r_extern
id|atomic_t
id|ppc_n_lost_interrupts
suffix:semicolon
r_struct
id|irqaction
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
