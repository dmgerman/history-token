multiline_comment|/*&n; * include/asm-mips/vr41xx/cmbvr4133.h&n; *&n; * Include file for NEC CMB-VR4133.&n; *&n; * Author: Yoichi Yuasa &lt;yyuasa@mvista.com, or source@mvista.com&gt; and&n; *         Jun Sun &lt;jsun@mvista.com, or source@mvista.com&gt; and&n; *         Alex Sapkov &lt;asapkov@ru.mvista.com&gt;&n; *&n; * 2002-2004 (c) MontaVista, Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef __NEC_CMBVR4133_H
DECL|macro|__NEC_CMBVR4133_H
mdefine_line|#define __NEC_CMBVR4133_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
multiline_comment|/*&n; * General-Purpose I/O Pin Number&n; */
DECL|macro|CMBVR41XX_INTA_PIN
mdefine_line|#define CMBVR41XX_INTA_PIN&t;&t;1
DECL|macro|CMBVR41XX_INTB_PIN
mdefine_line|#define CMBVR41XX_INTB_PIN&t;&t;1
DECL|macro|CMBVR41XX_INTC_PIN
mdefine_line|#define CMBVR41XX_INTC_PIN&t;&t;3
DECL|macro|CMBVR41XX_INTD_PIN
mdefine_line|#define CMBVR41XX_INTD_PIN&t;&t;1
DECL|macro|CMBVR41XX_INTE_PIN
mdefine_line|#define CMBVR41XX_INTE_PIN&t;&t;1
multiline_comment|/*&n; * Interrupt Number&n; */
DECL|macro|CMBVR41XX_INTA_IRQ
mdefine_line|#define CMBVR41XX_INTA_IRQ&t;&t;GIU_IRQ(CMBVR41XX_INTA_PIN)
DECL|macro|CMBVR41XX_INTB_IRQ
mdefine_line|#define CMBVR41XX_INTB_IRQ&t;&t;GIU_IRQ(CMBVR41XX_INTB_PIN)
DECL|macro|CMBVR41XX_INTC_IRQ
mdefine_line|#define CMBVR41XX_INTC_IRQ&t;&t;GIU_IRQ(CMBVR41XX_INTC_PIN)
DECL|macro|CMBVR41XX_INTD_IRQ
mdefine_line|#define CMBVR41XX_INTD_IRQ&t;&t;GIU_IRQ(CMBVR41XX_INTD_PIN)
DECL|macro|CMBVR41XX_INTE_IRQ
mdefine_line|#define CMBVR41XX_INTE_IRQ&t;&t;GIU_IRQ(CMBVR41XX_INTE_PIN)
DECL|macro|I8259_IRQ_BASE
mdefine_line|#define I8259_IRQ_BASE&t;&t;&t;72
DECL|macro|I8259_IRQ
mdefine_line|#define I8259_IRQ(x)&t;&t;&t;(I8259_IRQ_BASE + (x))
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;&t;&t;I8259_IRQ(0)
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ&t;&t;&t;I8259_IRQ(1)
DECL|macro|I8259_SLAVE_IRQ
mdefine_line|#define I8259_SLAVE_IRQ&t;&t;&t;I8259_IRQ(2)
DECL|macro|UART3_IRQ
mdefine_line|#define UART3_IRQ&t;&t;&t;I8259_IRQ(3)
DECL|macro|UART1_IRQ
mdefine_line|#define UART1_IRQ&t;&t;&t;I8259_IRQ(4)
DECL|macro|UART2_IRQ
mdefine_line|#define UART2_IRQ&t;&t;&t;I8259_IRQ(5)
DECL|macro|FDC_IRQ
mdefine_line|#define FDC_IRQ&t;&t;&t;&t;I8259_IRQ(6)
DECL|macro|PARPORT_IRQ
mdefine_line|#define PARPORT_IRQ&t;&t;&t;I8259_IRQ(7)
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;&t;&t;I8259_IRQ(8)
DECL|macro|USB_IRQ
mdefine_line|#define USB_IRQ&t;&t;&t;&t;I8259_IRQ(9)
DECL|macro|I8259_INTA_IRQ
mdefine_line|#define I8259_INTA_IRQ&t;&t;&t;I8259_IRQ(10)
DECL|macro|AUDIO_IRQ
mdefine_line|#define AUDIO_IRQ&t;&t;&t;I8259_IRQ(11)
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ&t;&t;&t;&t;I8259_IRQ(12)
DECL|macro|IDE_PRIMARY_IRQ
mdefine_line|#define IDE_PRIMARY_IRQ&t;&t;&t;I8259_IRQ(14)
DECL|macro|IDE_SECONDARY_IRQ
mdefine_line|#define IDE_SECONDARY_IRQ&t;&t;I8259_IRQ(15)
DECL|macro|I8259_IRQ_LAST
mdefine_line|#define I8259_IRQ_LAST&t;&t;&t;IDE_SECONDARY_IRQ
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0xaf000100 + (x))
DECL|macro|RTC_IO_EXTENT
mdefine_line|#define RTC_IO_EXTENT&t;0x140
macro_line|#endif /* __NEC_CMBVR4133_H */
eof
