multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/irqs.h&n; *&n; * Copyright (C) 1998 Russell King&n; * Copyright (C) 1998 Phil Blundell&n; *&n; * Changelog:&n; *  20-Jan-1998&t;RMK&t;Started merge of EBSA286, CATS and NetWinder&n; *  01-Feb-1999&t;PJB&t;ISA IRQs start at 0 not 16&n; */
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;36
DECL|macro|NR_DC21285_IRQS
mdefine_line|#define NR_DC21285_IRQS&t;&t;16
DECL|macro|_ISA_IRQ
mdefine_line|#define _ISA_IRQ(x)&t;&t;(0 + (x))
DECL|macro|_ISA_INR
mdefine_line|#define _ISA_INR(x)&t;&t;((x) - 0)
DECL|macro|_DC21285_IRQ
mdefine_line|#define _DC21285_IRQ(x)&t;&t;(16 + (x))
DECL|macro|_DC21285_INR
mdefine_line|#define _DC21285_INR(x)&t;&t;((x) - 16)
multiline_comment|/*&n; * This is a list of all interrupts that the 21285&n; * can generate and we handle.&n; */
DECL|macro|IRQ_CONRX
mdefine_line|#define IRQ_CONRX&t;&t;_DC21285_IRQ(0)
DECL|macro|IRQ_CONTX
mdefine_line|#define IRQ_CONTX&t;&t;_DC21285_IRQ(1)
DECL|macro|IRQ_TIMER1
mdefine_line|#define IRQ_TIMER1&t;&t;_DC21285_IRQ(2)
DECL|macro|IRQ_TIMER2
mdefine_line|#define IRQ_TIMER2&t;&t;_DC21285_IRQ(3)
DECL|macro|IRQ_TIMER3
mdefine_line|#define IRQ_TIMER3&t;&t;_DC21285_IRQ(4)
DECL|macro|IRQ_IN0
mdefine_line|#define IRQ_IN0&t;&t;&t;_DC21285_IRQ(5)
DECL|macro|IRQ_IN1
mdefine_line|#define IRQ_IN1&t;&t;&t;_DC21285_IRQ(6)
DECL|macro|IRQ_IN2
mdefine_line|#define IRQ_IN2&t;&t;&t;_DC21285_IRQ(7)
DECL|macro|IRQ_IN3
mdefine_line|#define IRQ_IN3&t;&t;&t;_DC21285_IRQ(8)
DECL|macro|IRQ_DOORBELLHOST
mdefine_line|#define IRQ_DOORBELLHOST&t;_DC21285_IRQ(9)
DECL|macro|IRQ_DMA1
mdefine_line|#define IRQ_DMA1&t;&t;_DC21285_IRQ(10)
DECL|macro|IRQ_DMA2
mdefine_line|#define IRQ_DMA2&t;&t;_DC21285_IRQ(11)
DECL|macro|IRQ_PCI
mdefine_line|#define IRQ_PCI&t;&t;&t;_DC21285_IRQ(12)
DECL|macro|IRQ_SDRAMPARITY
mdefine_line|#define IRQ_SDRAMPARITY&t;&t;_DC21285_IRQ(13)
DECL|macro|IRQ_I2OINPOST
mdefine_line|#define IRQ_I2OINPOST&t;&t;_DC21285_IRQ(14)
DECL|macro|IRQ_PCI_ABORT
mdefine_line|#define IRQ_PCI_ABORT&t;&t;_DC21285_IRQ(15)
DECL|macro|IRQ_PCI_SERR
mdefine_line|#define IRQ_PCI_SERR&t;&t;_DC21285_IRQ(16)
DECL|macro|IRQ_DISCARD_TIMER
mdefine_line|#define IRQ_DISCARD_TIMER&t;_DC21285_IRQ(17)
DECL|macro|IRQ_PCI_DPERR
mdefine_line|#define IRQ_PCI_DPERR&t;&t;_DC21285_IRQ(18)
DECL|macro|IRQ_PCI_PERR
mdefine_line|#define IRQ_PCI_PERR&t;&t;_DC21285_IRQ(19)
DECL|macro|IRQ_ISA_TIMER
mdefine_line|#define IRQ_ISA_TIMER&t;&t;_ISA_IRQ(0)
DECL|macro|IRQ_ISA_KEYBOARD
mdefine_line|#define IRQ_ISA_KEYBOARD&t;_ISA_IRQ(1)
DECL|macro|IRQ_ISA_CASCADE
mdefine_line|#define IRQ_ISA_CASCADE&t;&t;_ISA_IRQ(2)
DECL|macro|IRQ_ISA_UART2
mdefine_line|#define IRQ_ISA_UART2&t;&t;_ISA_IRQ(3)
DECL|macro|IRQ_ISA_UART
mdefine_line|#define IRQ_ISA_UART&t;&t;_ISA_IRQ(4)
DECL|macro|IRQ_ISA_FLOPPY
mdefine_line|#define IRQ_ISA_FLOPPY&t;&t;_ISA_IRQ(6)
DECL|macro|IRQ_ISA_PRINTER
mdefine_line|#define IRQ_ISA_PRINTER&t;&t;_ISA_IRQ(7)
DECL|macro|IRQ_ISA_RTC_ALARM
mdefine_line|#define IRQ_ISA_RTC_ALARM&t;_ISA_IRQ(8)
DECL|macro|IRQ_ISA_2
mdefine_line|#define IRQ_ISA_2&t;&t;_ISA_IRQ(9)
DECL|macro|IRQ_ISA_PS2MOUSE
mdefine_line|#define IRQ_ISA_PS2MOUSE&t;_ISA_IRQ(12)
DECL|macro|IRQ_ISA_HARDDISK1
mdefine_line|#define IRQ_ISA_HARDDISK1&t;_ISA_IRQ(14)
DECL|macro|IRQ_ISA_HARDDISK2
mdefine_line|#define IRQ_ISA_HARDDISK2&t;_ISA_IRQ(15)
DECL|macro|IRQ_MASK_UART_RX
mdefine_line|#define IRQ_MASK_UART_RX&t;(1 &lt;&lt; 2)
DECL|macro|IRQ_MASK_UART_TX
mdefine_line|#define IRQ_MASK_UART_TX&t;(1 &lt;&lt; 3)
DECL|macro|IRQ_MASK_TIMER1
mdefine_line|#define IRQ_MASK_TIMER1&t;&t;(1 &lt;&lt; 4)
DECL|macro|IRQ_MASK_TIMER2
mdefine_line|#define IRQ_MASK_TIMER2&t;&t;(1 &lt;&lt; 5)
DECL|macro|IRQ_MASK_TIMER3
mdefine_line|#define IRQ_MASK_TIMER3&t;&t;(1 &lt;&lt; 6)
DECL|macro|IRQ_MASK_IN0
mdefine_line|#define IRQ_MASK_IN0&t;&t;(1 &lt;&lt; 8)
DECL|macro|IRQ_MASK_IN1
mdefine_line|#define IRQ_MASK_IN1&t;&t;(1 &lt;&lt; 9)
DECL|macro|IRQ_MASK_IN2
mdefine_line|#define IRQ_MASK_IN2&t;&t;(1 &lt;&lt; 10)
DECL|macro|IRQ_MASK_IN3
mdefine_line|#define IRQ_MASK_IN3&t;&t;(1 &lt;&lt; 11)
DECL|macro|IRQ_MASK_DOORBELLHOST
mdefine_line|#define IRQ_MASK_DOORBELLHOST&t;(1 &lt;&lt; 15)
DECL|macro|IRQ_MASK_DMA1
mdefine_line|#define IRQ_MASK_DMA1&t;&t;(1 &lt;&lt; 16)
DECL|macro|IRQ_MASK_DMA2
mdefine_line|#define IRQ_MASK_DMA2&t;&t;(1 &lt;&lt; 17)
DECL|macro|IRQ_MASK_PCI
mdefine_line|#define IRQ_MASK_PCI&t;&t;(1 &lt;&lt; 18)
DECL|macro|IRQ_MASK_SDRAMPARITY
mdefine_line|#define IRQ_MASK_SDRAMPARITY&t;(1 &lt;&lt; 24)
DECL|macro|IRQ_MASK_I2OINPOST
mdefine_line|#define IRQ_MASK_I2OINPOST&t;(1 &lt;&lt; 25)
DECL|macro|IRQ_MASK_PCI_ABORT
mdefine_line|#define IRQ_MASK_PCI_ABORT&t;((1 &lt;&lt; 29) | (1 &lt;&lt; 30))
DECL|macro|IRQ_MASK_PCI_SERR
mdefine_line|#define IRQ_MASK_PCI_SERR&t;(1 &lt;&lt; 23)
DECL|macro|IRQ_MASK_DISCARD_TIMER
mdefine_line|#define IRQ_MASK_DISCARD_TIMER&t;(1 &lt;&lt; 27)
DECL|macro|IRQ_MASK_PCI_DPERR
mdefine_line|#define IRQ_MASK_PCI_DPERR&t;(1 &lt;&lt; 28)
DECL|macro|IRQ_MASK_PCI_PERR
mdefine_line|#define IRQ_MASK_PCI_PERR&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; * Netwinder interrupt allocations&n; */
DECL|macro|IRQ_NETWINDER_ETHER10
mdefine_line|#define IRQ_NETWINDER_ETHER10&t;IRQ_IN0
DECL|macro|IRQ_NETWINDER_ETHER100
mdefine_line|#define IRQ_NETWINDER_ETHER100&t;IRQ_IN1
DECL|macro|IRQ_NETWINDER_VIDCOMP
mdefine_line|#define IRQ_NETWINDER_VIDCOMP&t;IRQ_IN2
DECL|macro|IRQ_NETWINDER_PS2MOUSE
mdefine_line|#define IRQ_NETWINDER_PS2MOUSE&t;_ISA_IRQ(5)
DECL|macro|IRQ_NETWINDER_IR
mdefine_line|#define IRQ_NETWINDER_IR&t;_ISA_IRQ(6)
DECL|macro|IRQ_NETWINDER_BUTTON
mdefine_line|#define IRQ_NETWINDER_BUTTON&t;_ISA_IRQ(10)
DECL|macro|IRQ_NETWINDER_VGA
mdefine_line|#define IRQ_NETWINDER_VGA&t;_ISA_IRQ(11)
DECL|macro|IRQ_NETWINDER_SOUND
mdefine_line|#define IRQ_NETWINDER_SOUND&t;_ISA_IRQ(12)
DECL|macro|RTC_IRQ
macro_line|#undef RTC_IRQ
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;IRQ_ISA_RTC_ALARM
DECL|macro|AUX_IRQ
macro_line|#undef AUX_IRQ
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ&t;&t;(machine_is_netwinder() ? IRQ_NETWINDER_PS2MOUSE : IRQ_ISA_PS2MOUSE)
DECL|macro|IRQ_FLOPPYDISK
mdefine_line|#define IRQ_FLOPPYDISK&t;IRQ_ISA_FLOPPY
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(_i)&t;(((_i) == IRQ_ISA_CASCADE) ? IRQ_ISA_2 : _i)
eof
