multiline_comment|/*&n; * linux/include/asm-sh/irq_microdev.h&n; *&n; * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)&n; *&n; * IRQ functions for the SuperH SH4-202 MicroDev board.&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; */
macro_line|#ifndef _ASM_SH_IRQ_MICRODEV_H
DECL|macro|_ASM_SH_IRQ_MICRODEV_H
mdefine_line|#define _ASM_SH_IRQ_MICRODEV_H
r_extern
r_void
id|init_microdev_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|microdev_print_fpga_intc_status
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The following are useful macros for manipulating the&n;&t; *&t;interrupt controller (INTC) on the CPU-board FPGA.&n;&t; *&t;It should be noted that there is an INTC on the FPGA,&n;&t; *&t;and a seperate INTC on the SH4-202 core - these are&n;&t; *&t;two different things, both of which need to be prorammed&n;&t; *&t;to correctly route - unfortunately, they have the&n;&t; *&t;same name and abbreviations!&n;&t; */
DECL|macro|MICRODEV_FPGA_INTC_BASE
mdefine_line|#define&t;MICRODEV_FPGA_INTC_BASE&t;&t;0xa6110000ul&t;&t;&t;&t;/* INTC base address on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTENB_REG
mdefine_line|#define&t;MICRODEV_FPGA_INTENB_REG&t;(MICRODEV_FPGA_INTC_BASE+0ul)&t;&t;/* Interrupt Enable Register on INTC on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTDSB_REG
mdefine_line|#define&t;MICRODEV_FPGA_INTDSB_REG&t;(MICRODEV_FPGA_INTC_BASE+8ul)&t;&t;/* Interrupt Disable Register on INTC on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTC_MASK
mdefine_line|#define&t;MICRODEV_FPGA_INTC_MASK(n)&t;(1ul&lt;&lt;(n))&t;&t;&t;&t;/* Interupt mask to enable/disable INTC in CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTPRI_REG
mdefine_line|#define&t;MICRODEV_FPGA_INTPRI_REG(n)&t;(MICRODEV_FPGA_INTC_BASE+0x10+((n)/8)*8)/* Interrupt Priority Register on INTC on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTPRI_LEVEL
mdefine_line|#define&t;MICRODEV_FPGA_INTPRI_LEVEL(n,x)&t;((x)&lt;&lt;(((n)%8)*4))&t;&t;&t;/* MICRODEV_FPGA_INTPRI_LEVEL(int_number, int_level) */
DECL|macro|MICRODEV_FPGA_INTPRI_MASK
mdefine_line|#define&t;MICRODEV_FPGA_INTPRI_MASK(n)&t;(MICRODEV_FPGA_INTPRI_LEVEL((n),0xful))&t;/* Interrupt Priority Mask on INTC on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTSRC_REG
mdefine_line|#define&t;MICRODEV_FPGA_INTSRC_REG&t;(MICRODEV_FPGA_INTC_BASE+0x30ul)&t;/* Interrupt Source Register on INTC on CPU-board FPGA */
DECL|macro|MICRODEV_FPGA_INTREQ_REG
mdefine_line|#define&t;MICRODEV_FPGA_INTREQ_REG&t;(MICRODEV_FPGA_INTC_BASE+0x38ul)&t;/* Interrupt Request Register on INTC on CPU-board FPGA */
multiline_comment|/*&n;&t; *&t;The following are the IRQ numbers for the Linux Kernel for external interrupts.&n;&t; *&t;i.e. the numbers seen by &squot;cat /proc/interrupt&squot;.&n;&t; */
DECL|macro|MICRODEV_LINUX_IRQ_KEYBOARD
mdefine_line|#define MICRODEV_LINUX_IRQ_KEYBOARD&t; 1&t;/* SuperIO Keyboard */
DECL|macro|MICRODEV_LINUX_IRQ_SERIAL1
mdefine_line|#define MICRODEV_LINUX_IRQ_SERIAL1&t; 2&t;/* SuperIO Serial #1 */
DECL|macro|MICRODEV_LINUX_IRQ_ETHERNET
mdefine_line|#define MICRODEV_LINUX_IRQ_ETHERNET&t; 3&t;/* on-board Ethnernet */
DECL|macro|MICRODEV_LINUX_IRQ_SERIAL2
mdefine_line|#define MICRODEV_LINUX_IRQ_SERIAL2&t; 4&t;/* SuperIO Serial #2 */
DECL|macro|MICRODEV_LINUX_IRQ_USB_HC
mdefine_line|#define MICRODEV_LINUX_IRQ_USB_HC&t; 7&t;/* on-board USB HC */
DECL|macro|MICRODEV_LINUX_IRQ_MOUSE
mdefine_line|#define MICRODEV_LINUX_IRQ_MOUSE&t;12&t;/* SuperIO PS/2 Mouse */
DECL|macro|MICRODEV_LINUX_IRQ_IDE2
mdefine_line|#define MICRODEV_LINUX_IRQ_IDE2&t;&t;13&t;/* SuperIO IDE #2 */
DECL|macro|MICRODEV_LINUX_IRQ_IDE1
mdefine_line|#define MICRODEV_LINUX_IRQ_IDE1&t;&t;14&t;/* SuperIO IDE #1 */
multiline_comment|/*&n;&t; *&t;The following are the IRQ numbers for the INTC on the FPGA for external interrupts.&n;&t; *&t;i.e. the bits in the INTC registers in the FPGA.&n;&t; */
DECL|macro|MICRODEV_FPGA_IRQ_KEYBOARD
mdefine_line|#define MICRODEV_FPGA_IRQ_KEYBOARD&t; 1&t;/* SuperIO Keyboard */
DECL|macro|MICRODEV_FPGA_IRQ_SERIAL1
mdefine_line|#define MICRODEV_FPGA_IRQ_SERIAL1&t; 3&t;/* SuperIO Serial #1 */
DECL|macro|MICRODEV_FPGA_IRQ_SERIAL2
mdefine_line|#define MICRODEV_FPGA_IRQ_SERIAL2&t; 4&t;/* SuperIO Serial #2 */
DECL|macro|MICRODEV_FPGA_IRQ_MOUSE
mdefine_line|#define MICRODEV_FPGA_IRQ_MOUSE&t;&t;12&t;/* SuperIO PS/2 Mouse */
DECL|macro|MICRODEV_FPGA_IRQ_IDE1
mdefine_line|#define MICRODEV_FPGA_IRQ_IDE1&t;&t;14&t;/* SuperIO IDE #1 */
DECL|macro|MICRODEV_FPGA_IRQ_IDE2
mdefine_line|#define MICRODEV_FPGA_IRQ_IDE2&t;&t;15&t;/* SuperIO IDE #2 */
DECL|macro|MICRODEV_FPGA_IRQ_USB_HC
mdefine_line|#define MICRODEV_FPGA_IRQ_USB_HC&t;16&t;/* on-board USB HC */
DECL|macro|MICRODEV_FPGA_IRQ_ETHERNET
mdefine_line|#define MICRODEV_FPGA_IRQ_ETHERNET&t;18&t;/* on-board Ethnernet */
DECL|macro|MICRODEV_IRQ_PCI_INTA
mdefine_line|#define MICRODEV_IRQ_PCI_INTA&t;&t; 8
DECL|macro|MICRODEV_IRQ_PCI_INTB
mdefine_line|#define MICRODEV_IRQ_PCI_INTB&t;&t; 9
DECL|macro|MICRODEV_IRQ_PCI_INTC
mdefine_line|#define MICRODEV_IRQ_PCI_INTC&t;&t;10
DECL|macro|MICRODEV_IRQ_PCI_INTD
mdefine_line|#define MICRODEV_IRQ_PCI_INTD&t;&t;11
macro_line|#endif /* _ASM_SH_IRQ_MICRODEV_H */
eof
