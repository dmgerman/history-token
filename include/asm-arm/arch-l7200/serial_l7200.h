multiline_comment|/*&n; * linux/include/asm-arm/arch-l7200/serial_l7200.h&n; *&n; * Copyright (c) 2000 Steven Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *  05-09-2000&t;SJH&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_L7200_H
DECL|macro|__ASM_ARCH_SERIAL_L7200_H
mdefine_line|#define __ASM_ARCH_SERIAL_L7200_H
macro_line|#include &lt;asm/arch/memory.h&gt;
multiline_comment|/*&n; * This assumes you have a 3.6864 MHz clock for your UART.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 3686400
multiline_comment|/*&n; * UART base register addresses&n; */
DECL|macro|UART1_BASE
mdefine_line|#define UART1_BASE&t;(IO_BASE + 0x00044000)
DECL|macro|UART2_BASE
mdefine_line|#define UART2_BASE&t;(IO_BASE + 0x00045000)
multiline_comment|/*&n; * UART register offsets&n; */
DECL|macro|UARTDR
mdefine_line|#define UARTDR&t;&t;&t;0x00&t;/* Tx/Rx data */
DECL|macro|RXSTAT
mdefine_line|#define RXSTAT&t;&t;&t;0x04&t;/* Rx status */
DECL|macro|H_UBRLCR
mdefine_line|#define H_UBRLCR&t;&t;0x08&t;/* mode register high */
DECL|macro|M_UBRLCR
mdefine_line|#define M_UBRLCR&t;&t;0x0C&t;/* mode reg mid (MSB of buad)*/
DECL|macro|L_UBRLCR
mdefine_line|#define L_UBRLCR&t;&t;0x10&t;/* mode reg low (LSB of baud)*/
DECL|macro|UARTCON
mdefine_line|#define UARTCON&t;&t;&t;0x14&t;/* control register */
DECL|macro|UARTFLG
mdefine_line|#define UARTFLG&t;&t;&t;0x18&t;/* flag register */
DECL|macro|UARTINTSTAT
mdefine_line|#define UARTINTSTAT&t;&t;0x1C&t;/* FIFO IRQ status register */
DECL|macro|UARTINTMASK
mdefine_line|#define UARTINTMASK&t;&t;0x20&t;/* FIFO IRQ mask register */
multiline_comment|/*&n; * UART baud rate register values&n; */
DECL|macro|BR_110
mdefine_line|#define BR_110&t;&t;&t;0x827
DECL|macro|BR_1200
mdefine_line|#define BR_1200&t;&t;&t;0x06e
DECL|macro|BR_2400
mdefine_line|#define BR_2400&t;&t;&t;0x05f
DECL|macro|BR_4800
mdefine_line|#define BR_4800&t;&t;&t;0x02f
DECL|macro|BR_9600
mdefine_line|#define BR_9600&t;&t;&t;0x017
DECL|macro|BR_14400
mdefine_line|#define BR_14400&t;&t;0x00f
DECL|macro|BR_19200
mdefine_line|#define BR_19200&t;&t;0x00b
DECL|macro|BR_38400
mdefine_line|#define BR_38400&t;&t;0x005
DECL|macro|BR_57600
mdefine_line|#define BR_57600&t;&t;0x003
DECL|macro|BR_76800
mdefine_line|#define BR_76800 &t;&t;0x002
DECL|macro|BR_115200
mdefine_line|#define BR_115200&t;&t;0x001
multiline_comment|/*&n; * Receiver status register (RXSTAT) mask values&n; */
DECL|macro|RXSTAT_NO_ERR
mdefine_line|#define RXSTAT_NO_ERR&t;&t;0x00&t;/* No error */
DECL|macro|RXSTAT_FRM_ERR
mdefine_line|#define RXSTAT_FRM_ERR&t;&t;0x01&t;/* Framing error */
DECL|macro|RXSTAT_PAR_ERR
mdefine_line|#define RXSTAT_PAR_ERR&t;&t;0x02&t;/* Parity error */
DECL|macro|RXSTAT_OVR_ERR
mdefine_line|#define RXSTAT_OVR_ERR&t;&t;0x04&t;/* Overrun error */
multiline_comment|/*&n; * High byte of UART bit rate and line control register (H_UBRLCR) values&n; */
DECL|macro|UBRLCR_BRK
mdefine_line|#define UBRLCR_BRK&t;&t;0x01&t;/* generate break on tx */
DECL|macro|UBRLCR_PEN
mdefine_line|#define UBRLCR_PEN&t;&t;0x02&t;/* enable parity */
DECL|macro|UBRLCR_PDIS
mdefine_line|#define UBRLCR_PDIS&t;&t;0x00&t;/* disable parity */
DECL|macro|UBRLCR_EVEN
mdefine_line|#define UBRLCR_EVEN&t;&t;0x04&t;/* 1= even parity,0 = odd parity */
DECL|macro|UBRLCR_STP2
mdefine_line|#define UBRLCR_STP2&t;&t;0x08&t;/* transmit 2 stop bits */
DECL|macro|UBRLCR_FIFO
mdefine_line|#define UBRLCR_FIFO&t;&t;0x10&t;/* enable FIFO */
DECL|macro|UBRLCR_LEN5
mdefine_line|#define UBRLCR_LEN5&t;&t;0x60&t;/* word length5 */
DECL|macro|UBRLCR_LEN6
mdefine_line|#define UBRLCR_LEN6&t;&t;0x40&t;/* word length6 */
DECL|macro|UBRLCR_LEN7
mdefine_line|#define UBRLCR_LEN7&t;&t;0x20&t;/* word length7 */
DECL|macro|UBRLCR_LEN8
mdefine_line|#define UBRLCR_LEN8&t;&t;0x00&t;/* word length8 */
multiline_comment|/*&n; * UART control register (UARTCON) values&n; */
DECL|macro|UARTCON_UARTEN
mdefine_line|#define UARTCON_UARTEN&t;&t;0x01&t;/* Enable UART */
DECL|macro|UARTCON_DMAONERR
mdefine_line|#define UARTCON_DMAONERR&t;0x08&t;/* Mask RxDmaRq when errors occur */
multiline_comment|/*&n; * UART flag register (UARTFLG) mask values&n; */
DECL|macro|UARTFLG_UTXFF
mdefine_line|#define UARTFLG_UTXFF&t;&t;0x20&t;/* Transmit FIFO full */
DECL|macro|UARTFLG_URXFE
mdefine_line|#define UARTFLG_URXFE&t;&t;0x10&t;/* Receiver FIFO empty */
DECL|macro|UARTFLG_UBUSY
mdefine_line|#define UARTFLG_UBUSY&t;&t;0x08&t;/* Transmitter busy */
DECL|macro|UARTFLG_DCD
mdefine_line|#define UARTFLG_DCD&t;&t;0x04&t;/* Data carrier detect */
DECL|macro|UARTFLG_DSR
mdefine_line|#define UARTFLG_DSR&t;&t;0x02&t;/* Data set ready */
DECL|macro|UARTFLG_CTS
mdefine_line|#define UARTFLG_CTS&t;&t;0x01&t;/* Clear to send */
multiline_comment|/*&n; * UART interrupt status/clear registers (UARTINTSTAT/CLR) values&n; */
DECL|macro|UART_TXINT
mdefine_line|#define UART_TXINT&t;&t;0x01&t;/* TX interrupt */
DECL|macro|UART_RXINT
mdefine_line|#define UART_RXINT&t;&t;0x02&t;/* RX interrupt */
DECL|macro|UART_RXERRINT
mdefine_line|#define UART_RXERRINT&t;&t;0x04&t;/* RX error interrupt */
DECL|macro|UART_MSINT
mdefine_line|#define UART_MSINT&t;&t;0x08&t;/* Modem Status interrupt */
DECL|macro|UART_UDINT
mdefine_line|#define UART_UDINT&t;&t;0x10&t;/* UART Disabled interrupt */
DECL|macro|UART_ALLIRQS
mdefine_line|#define UART_ALLIRQS&t;&t;0x1f&t;/* All interrupts */
macro_line|#endif
eof
