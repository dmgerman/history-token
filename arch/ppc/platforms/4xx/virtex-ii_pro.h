multiline_comment|/*&n; * arch/ppc/platforms/4xx/virtex-ii_pro.h&n; *&n; * Include file that defines the Xilinx Virtex-II Pro processor&n; *&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * 2002-2004 (c) MontaVista Software, Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2.  This program is licensed&n; * &quot;as is&quot; without any warranty of any kind, whether express or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_VIRTEXIIPRO_H__
DECL|macro|__ASM_VIRTEXIIPRO_H__
mdefine_line|#define __ASM_VIRTEXIIPRO_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/xparameters.h&gt;
multiline_comment|/* serial defines */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4&t;/* change this and add more devices below&n;&t;&t;&t;&t;   if you have more then 4 16x50 UARTs */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;(XPAR_UARTNS550_0_CLOCK_FREQ_HZ/16)
multiline_comment|/* The serial ports in the Virtex-II Pro have each I/O byte in the&n; * LSByte of a word.  This means that iomem_reg_shift needs to be 2 to&n; * change the byte offsets into word offsets.  In addition the base&n; * addresses need to have 3 added to them to get to the LSByte.&n; */
DECL|macro|STD_UART_OP
mdefine_line|#define STD_UART_OP(num)&t;&t;&t;&t;&t;&t; &bslash;&n;&t;{ 0, BASE_BAUD, 0, XPAR_INTC_0_UARTNS550_##num##_VEC_ID,&t; &bslash;&n;&t;&t;ASYNC_BOOT_AUTOCONF,&t;&t; &t;&t;&t; &bslash;&n;&t;&t;.iomem_base = (u8 *)XPAR_UARTNS550_##num##_BASEADDR + 3, &bslash;&n;&t;&t;.iomem_reg_shift = 2,&t;&t;&t;&t;&t; &bslash;&n;&t;&t;.io_type = SERIAL_IO_MEM},
macro_line|#if defined(XPAR_INTC_0_UARTNS550_0_VEC_ID)
DECL|macro|ML300_UART0
mdefine_line|#define ML300_UART0 STD_UART_OP(0)
macro_line|#else
DECL|macro|ML300_UART0
mdefine_line|#define ML300_UART0
macro_line|#endif
macro_line|#if defined(XPAR_INTC_0_UARTNS550_1_VEC_ID)
DECL|macro|ML300_UART1
mdefine_line|#define ML300_UART1 STD_UART_OP(1)
macro_line|#else
DECL|macro|ML300_UART1
mdefine_line|#define ML300_UART1
macro_line|#endif
macro_line|#if defined(XPAR_INTC_0_UARTNS550_2_VEC_ID)
DECL|macro|ML300_UART2
mdefine_line|#define ML300_UART2 STD_UART_OP(2)
macro_line|#else
DECL|macro|ML300_UART2
mdefine_line|#define ML300_UART2
macro_line|#endif
macro_line|#if defined(XPAR_INTC_0_UARTNS550_3_VEC_ID)
DECL|macro|ML300_UART3
mdefine_line|#define ML300_UART3 STD_UART_OP(3)
macro_line|#else
DECL|macro|ML300_UART3
mdefine_line|#define ML300_UART3
macro_line|#endif
macro_line|#if defined(XPAR_INTC_0_UARTNS550_4_VEC_ID)
macro_line|#error Edit this file to add more devices.
macro_line|#elif defined(XPAR_INTC_0_UARTNS550_3_VEC_ID)
DECL|macro|NR_SER_PORTS
mdefine_line|#define NR_SER_PORTS&t;4
macro_line|#elif defined(XPAR_INTC_0_UARTNS550_2_VEC_ID)
DECL|macro|NR_SER_PORTS
mdefine_line|#define NR_SER_PORTS&t;3
macro_line|#elif defined(XPAR_INTC_0_UARTNS550_1_VEC_ID)
DECL|macro|NR_SER_PORTS
mdefine_line|#define NR_SER_PORTS&t;2
macro_line|#elif defined(XPAR_INTC_0_UARTNS550_0_VEC_ID)
DECL|macro|NR_SER_PORTS
mdefine_line|#define NR_SER_PORTS&t;1
macro_line|#else
DECL|macro|NR_SER_PORTS
mdefine_line|#define NR_SER_PORTS&t;0
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS0)
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;ML300_UART0&t;&t;&bslash;&n;&t;ML300_UART1&t;&t;&bslash;&n;&t;ML300_UART2&t;&t;&bslash;&n;&t;ML300_UART3
macro_line|#endif
macro_line|#if defined(CONFIG_UART0_TTYS1)
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&bslash;&n;&t;ML300_UART1&t;&t;&bslash;&n;&t;ML300_UART0&t;&t;&bslash;&n;&t;ML300_UART2&t;&t;&bslash;&n;&t;ML300_UART3
macro_line|#endif
DECL|macro|DCRN_CPMFR_BASE
mdefine_line|#define DCRN_CPMFR_BASE&t;0
macro_line|#include &lt;asm/ibm405.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __ASM_VIRTEXIIPRO_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
