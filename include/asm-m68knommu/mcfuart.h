multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfuart.h -- ColdFire internal UART support defines.&n; *&n; *&t;(C) Copyright 1999-2003, Greg Ungerer (gerg@snapgear.com)&n; * &t;(C) Copyright 2000, Lineo Inc. (www.lineo.com) &n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcfuart_h
DECL|macro|mcfuart_h
mdefine_line|#define&t;mcfuart_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Define the base address of the UARTS within the MBAR address&n; *&t;space.&n; */
macro_line|#if defined(CONFIG_M5272)
DECL|macro|MCFUART_BASE1
mdefine_line|#define&t;MCFUART_BASE1&t;&t;0x100&t;&t;/* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define&t;MCFUART_BASE2&t;&t;0x140&t;&t;/* Base address of UART2 */
macro_line|#elif defined(CONFIG_M5204) || defined(CONFIG_M5206) || defined(CONFIG_M5206e)
macro_line|#if defined(CONFIG_NETtel)
DECL|macro|MCFUART_BASE1
mdefine_line|#define&t;MCFUART_BASE1&t;&t;0x180&t;&t;/* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define&t;MCFUART_BASE2&t;&t;0x140&t;&t;/* Base address of UART2 */
macro_line|#else
DECL|macro|MCFUART_BASE1
mdefine_line|#define&t;MCFUART_BASE1&t;&t;0x140&t;&t;/* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define&t;MCFUART_BASE2&t;&t;0x180&t;&t;/* Base address of UART2 */
macro_line|#endif
macro_line|#elif defined(CONFIG_M527x) || defined(CONFIG_M528x)
DECL|macro|MCFUART_BASE1
mdefine_line|#define MCFUART_BASE1&t;&t;0x200           /* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define MCFUART_BASE2&t;&t;0x240           /* Base address of UART2 */
DECL|macro|MCFUART_BASE3
mdefine_line|#define MCFUART_BASE3&t;&t;0x280           /* Base address of UART3 */
macro_line|#elif defined(CONFIG_M5249) || defined(CONFIG_M5307) || defined(CONFIG_M5407)
macro_line|#if defined(CONFIG_NETtel) || defined(CONFIG_DISKtel) || defined(CONFIG_SECUREEDGEMP3)
DECL|macro|MCFUART_BASE1
mdefine_line|#define MCFUART_BASE1&t;&t;0x200           /* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define MCFUART_BASE2&t;&t;0x1c0           /* Base address of UART2 */
macro_line|#else
DECL|macro|MCFUART_BASE1
mdefine_line|#define MCFUART_BASE1&t;&t;0x1c0           /* Base address of UART1 */
DECL|macro|MCFUART_BASE2
mdefine_line|#define MCFUART_BASE2&t;&t;0x200           /* Base address of UART2 */
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *&t;Define the ColdFire UART register set addresses.&n; */
DECL|macro|MCFUART_UMR
mdefine_line|#define&t;MCFUART_UMR&t;&t;0x00&t;&t;/* Mode register (r/w) */
DECL|macro|MCFUART_USR
mdefine_line|#define&t;MCFUART_USR&t;&t;0x04&t;&t;/* Status register (r) */
DECL|macro|MCFUART_UCSR
mdefine_line|#define&t;MCFUART_UCSR&t;&t;0x04&t;&t;/* Clock Select (w) */
DECL|macro|MCFUART_UCR
mdefine_line|#define&t;MCFUART_UCR&t;&t;0x08&t;&t;/* Command register (w) */
DECL|macro|MCFUART_URB
mdefine_line|#define&t;MCFUART_URB&t;&t;0x0c&t;&t;/* Receiver Buffer (r) */
DECL|macro|MCFUART_UTB
mdefine_line|#define&t;MCFUART_UTB&t;&t;0x0c&t;&t;/* Transmit Buffer (w) */
DECL|macro|MCFUART_UIPCR
mdefine_line|#define&t;MCFUART_UIPCR&t;&t;0x10&t;&t;/* Input Port Change (r) */
DECL|macro|MCFUART_UACR
mdefine_line|#define&t;MCFUART_UACR&t;&t;0x10&t;&t;/* Auxiliary Control (w) */
DECL|macro|MCFUART_UISR
mdefine_line|#define&t;MCFUART_UISR&t;&t;0x14&t;&t;/* Interrup Status (r) */
DECL|macro|MCFUART_UIMR
mdefine_line|#define&t;MCFUART_UIMR&t;&t;0x14&t;&t;/* Interrupt Mask (w) */
DECL|macro|MCFUART_UBG1
mdefine_line|#define&t;MCFUART_UBG1&t;&t;0x18&t;&t;/* Baud Rate MSB (r/w) */
DECL|macro|MCFUART_UBG2
mdefine_line|#define&t;MCFUART_UBG2&t;&t;0x1c&t;&t;/* Baud Rate LSB (r/w) */
macro_line|#ifdef&t;CONFIG_M5272
DECL|macro|MCFUART_UTF
mdefine_line|#define&t;MCFUART_UTF&t;&t;0x28&t;&t;/* Transmitter FIFO (r/w) */
DECL|macro|MCFUART_URF
mdefine_line|#define&t;MCFUART_URF&t;&t;0x2c&t;&t;/* Receiver FIFO (r/w) */
DECL|macro|MCFUART_UFPD
mdefine_line|#define&t;MCFUART_UFPD&t;&t;0x30&t;&t;/* Frac Prec. Divider (r/w) */
macro_line|#else
DECL|macro|MCFUART_UIVR
mdefine_line|#define&t;MCFUART_UIVR&t;&t;0x30&t;&t;/* Interrupt Vector (r/w) */
macro_line|#endif
DECL|macro|MCFUART_UIPR
mdefine_line|#define&t;MCFUART_UIPR&t;&t;0x34&t;&t;/* Input Port (r) */
DECL|macro|MCFUART_UOP1
mdefine_line|#define&t;MCFUART_UOP1&t;&t;0x38&t;&t;/* Output Port Bit Set (w) */
DECL|macro|MCFUART_UOP0
mdefine_line|#define&t;MCFUART_UOP0&t;&t;0x3c&t;&t;/* Output Port Bit Reset (w) */
multiline_comment|/*&n; *&t;Define bit flags in Mode Register 1 (MR1).&n; */
DECL|macro|MCFUART_MR1_RXRTS
mdefine_line|#define&t;MCFUART_MR1_RXRTS&t;0x80&t;&t;/* Auto RTS flow control */
DECL|macro|MCFUART_MR1_RXIRQFULL
mdefine_line|#define&t;MCFUART_MR1_RXIRQFULL&t;0x40&t;&t;/* RX IRQ type FULL */
DECL|macro|MCFUART_MR1_RXIRQRDY
mdefine_line|#define&t;MCFUART_MR1_RXIRQRDY&t;0x00&t;&t;/* RX IRQ type RDY */
DECL|macro|MCFUART_MR1_RXERRBLOCK
mdefine_line|#define&t;MCFUART_MR1_RXERRBLOCK&t;0x20&t;&t;/* RX block error mode */
DECL|macro|MCFUART_MR1_RXERRCHAR
mdefine_line|#define&t;MCFUART_MR1_RXERRCHAR&t;0x00&t;&t;/* RX char error mode */
DECL|macro|MCFUART_MR1_PARITYNONE
mdefine_line|#define&t;MCFUART_MR1_PARITYNONE&t;0x10&t;&t;/* No parity */
DECL|macro|MCFUART_MR1_PARITYEVEN
mdefine_line|#define&t;MCFUART_MR1_PARITYEVEN&t;0x00&t;&t;/* Even parity */
DECL|macro|MCFUART_MR1_PARITYODD
mdefine_line|#define&t;MCFUART_MR1_PARITYODD&t;0x04&t;&t;/* Odd parity */
DECL|macro|MCFUART_MR1_PARITYSPACE
mdefine_line|#define&t;MCFUART_MR1_PARITYSPACE&t;0x08&t;&t;/* Space parity */
DECL|macro|MCFUART_MR1_PARITYMARK
mdefine_line|#define&t;MCFUART_MR1_PARITYMARK&t;0x0c&t;&t;/* Mark parity */
DECL|macro|MCFUART_MR1_CS5
mdefine_line|#define&t;MCFUART_MR1_CS5&t;&t;0x00&t;&t;/* 5 bits per char */
DECL|macro|MCFUART_MR1_CS6
mdefine_line|#define&t;MCFUART_MR1_CS6&t;&t;0x01&t;&t;/* 6 bits per char */
DECL|macro|MCFUART_MR1_CS7
mdefine_line|#define&t;MCFUART_MR1_CS7&t;&t;0x02&t;&t;/* 7 bits per char */
DECL|macro|MCFUART_MR1_CS8
mdefine_line|#define&t;MCFUART_MR1_CS8&t;&t;0x03&t;&t;/* 8 bits per char */
multiline_comment|/*&n; *&t;Define bit flags in Mode Register 2 (MR2).&n; */
DECL|macro|MCFUART_MR2_LOOPBACK
mdefine_line|#define&t;MCFUART_MR2_LOOPBACK&t;0x80&t;&t;/* Loopback mode */
DECL|macro|MCFUART_MR2_REMOTELOOP
mdefine_line|#define&t;MCFUART_MR2_REMOTELOOP&t;0xc0&t;&t;/* Remote loopback mode */
DECL|macro|MCFUART_MR2_AUTOECHO
mdefine_line|#define&t;MCFUART_MR2_AUTOECHO&t;0x40&t;&t;/* Automatic echo */
DECL|macro|MCFUART_MR2_TXRTS
mdefine_line|#define&t;MCFUART_MR2_TXRTS&t;0x20&t;&t;/* Assert RTS on TX */
DECL|macro|MCFUART_MR2_TXCTS
mdefine_line|#define&t;MCFUART_MR2_TXCTS&t;0x10&t;&t;/* Auto CTS flow control */
DECL|macro|MCFUART_MR2_STOP1
mdefine_line|#define&t;MCFUART_MR2_STOP1&t;0x07&t;&t;/* 1 stop bit */
DECL|macro|MCFUART_MR2_STOP15
mdefine_line|#define&t;MCFUART_MR2_STOP15&t;0x08&t;&t;/* 1.5 stop bits */
DECL|macro|MCFUART_MR2_STOP2
mdefine_line|#define&t;MCFUART_MR2_STOP2&t;0x0f&t;&t;/* 2 stop bits */
multiline_comment|/*&n; *&t;Define bit flags in Status Register (USR).&n; */
DECL|macro|MCFUART_USR_RXBREAK
mdefine_line|#define&t;MCFUART_USR_RXBREAK&t;0x80&t;&t;/* Received BREAK */
DECL|macro|MCFUART_USR_RXFRAMING
mdefine_line|#define&t;MCFUART_USR_RXFRAMING&t;0x40&t;&t;/* Received framing error */
DECL|macro|MCFUART_USR_RXPARITY
mdefine_line|#define&t;MCFUART_USR_RXPARITY&t;0x20&t;&t;/* Received parity error */
DECL|macro|MCFUART_USR_RXOVERRUN
mdefine_line|#define&t;MCFUART_USR_RXOVERRUN&t;0x10&t;&t;/* Received overrun error */
DECL|macro|MCFUART_USR_TXEMPTY
mdefine_line|#define&t;MCFUART_USR_TXEMPTY&t;0x08&t;&t;/* Transmitter empty */
DECL|macro|MCFUART_USR_TXREADY
mdefine_line|#define&t;MCFUART_USR_TXREADY&t;0x04&t;&t;/* Transmitter ready */
DECL|macro|MCFUART_USR_RXFULL
mdefine_line|#define&t;MCFUART_USR_RXFULL&t;0x02&t;&t;/* Receiver full */
DECL|macro|MCFUART_USR_RXREADY
mdefine_line|#define&t;MCFUART_USR_RXREADY&t;0x01&t;&t;/* Receiver ready */
DECL|macro|MCFUART_USR_RXERR
mdefine_line|#define&t;MCFUART_USR_RXERR&t;(MCFUART_USR_RXBREAK | MCFUART_USR_RXFRAMING | &bslash;&n;&t;&t;&t;&t;MCFUART_USR_RXPARITY | MCFUART_USR_RXOVERRUN)
multiline_comment|/*&n; *&t;Define bit flags in Clock Select Register (UCSR).&n; */
DECL|macro|MCFUART_UCSR_RXCLKTIMER
mdefine_line|#define&t;MCFUART_UCSR_RXCLKTIMER&t;0xd0&t;&t;/* RX clock is timer */
DECL|macro|MCFUART_UCSR_RXCLKEXT16
mdefine_line|#define&t;MCFUART_UCSR_RXCLKEXT16&t;0xe0&t;&t;/* RX clock is external x16 */
DECL|macro|MCFUART_UCSR_RXCLKEXT1
mdefine_line|#define&t;MCFUART_UCSR_RXCLKEXT1&t;0xf0&t;&t;/* RX clock is external x1 */
DECL|macro|MCFUART_UCSR_TXCLKTIMER
mdefine_line|#define&t;MCFUART_UCSR_TXCLKTIMER&t;0x0d&t;&t;/* TX clock is timer */
DECL|macro|MCFUART_UCSR_TXCLKEXT16
mdefine_line|#define&t;MCFUART_UCSR_TXCLKEXT16&t;0x0e&t;&t;/* TX clock is external x16 */
DECL|macro|MCFUART_UCSR_TXCLKEXT1
mdefine_line|#define&t;MCFUART_UCSR_TXCLKEXT1&t;0x0f&t;&t;/* TX clock is external x1 */
multiline_comment|/*&n; *&t;Define bit flags in Command Register (UCR).&n; */
DECL|macro|MCFUART_UCR_CMDNULL
mdefine_line|#define&t;MCFUART_UCR_CMDNULL&t;&t;0x00&t;/* No command */
DECL|macro|MCFUART_UCR_CMDRESETMRPTR
mdefine_line|#define&t;MCFUART_UCR_CMDRESETMRPTR&t;0x10&t;/* Reset MR pointer */
DECL|macro|MCFUART_UCR_CMDRESETRX
mdefine_line|#define&t;MCFUART_UCR_CMDRESETRX&t;&t;0x20&t;/* Reset receiver */
DECL|macro|MCFUART_UCR_CMDRESETTX
mdefine_line|#define&t;MCFUART_UCR_CMDRESETTX&t;&t;0x30&t;/* Reset transmitter */
DECL|macro|MCFUART_UCR_CMDRESETERR
mdefine_line|#define&t;MCFUART_UCR_CMDRESETERR&t;&t;0x40&t;/* Reset error status */
DECL|macro|MCFUART_UCR_CMDRESETBREAK
mdefine_line|#define&t;MCFUART_UCR_CMDRESETBREAK&t;0x50&t;/* Reset BREAK change */
DECL|macro|MCFUART_UCR_CMDBREAKSTART
mdefine_line|#define&t;MCFUART_UCR_CMDBREAKSTART&t;0x60&t;/* Start BREAK */
DECL|macro|MCFUART_UCR_CMDBREAKSTOP
mdefine_line|#define&t;MCFUART_UCR_CMDBREAKSTOP&t;0x70&t;/* Stop BREAK */
DECL|macro|MCFUART_UCR_TXNULL
mdefine_line|#define&t;MCFUART_UCR_TXNULL&t;0x00&t;&t;/* No TX command */
DECL|macro|MCFUART_UCR_TXENABLE
mdefine_line|#define&t;MCFUART_UCR_TXENABLE&t;0x04&t;&t;/* Enable TX */
DECL|macro|MCFUART_UCR_TXDISABLE
mdefine_line|#define&t;MCFUART_UCR_TXDISABLE&t;0x08&t;&t;/* Disable TX */
DECL|macro|MCFUART_UCR_RXNULL
mdefine_line|#define&t;MCFUART_UCR_RXNULL&t;0x00&t;&t;/* No RX command */
DECL|macro|MCFUART_UCR_RXENABLE
mdefine_line|#define&t;MCFUART_UCR_RXENABLE&t;0x01&t;&t;/* Enable RX */
DECL|macro|MCFUART_UCR_RXDISABLE
mdefine_line|#define&t;MCFUART_UCR_RXDISABLE&t;0x02&t;&t;/* Disable RX */
multiline_comment|/*&n; *&t;Define bit flags in Input Port Change Register (UIPCR).&n; */
DECL|macro|MCFUART_UIPCR_CTSCOS
mdefine_line|#define&t;MCFUART_UIPCR_CTSCOS&t;0x10&t;&t;/* CTS change of state */
DECL|macro|MCFUART_UIPCR_CTS
mdefine_line|#define&t;MCFUART_UIPCR_CTS&t;0x01&t;&t;/* CTS value */
multiline_comment|/*&n; *&t;Define bit flags in Input Port Register (UIP).&n; */
DECL|macro|MCFUART_UIPR_CTS
mdefine_line|#define&t;MCFUART_UIPR_CTS&t;0x01&t;&t;/* CTS value */
multiline_comment|/*&n; *&t;Define bit flags in Output Port Registers (UOP).&n; *&t;Clear bit by writing to UOP0, set by writing to UOP1.&n; */
DECL|macro|MCFUART_UOP_RTS
mdefine_line|#define&t;MCFUART_UOP_RTS&t;&t;0x01&t;&t;/* RTS set or clear */
multiline_comment|/*&n; *&t;Define bit flags in the Auxiliary Control Register (UACR).&n; */
DECL|macro|MCFUART_UACR_IEC
mdefine_line|#define&t;MCFUART_UACR_IEC&t;0x01&t;&t;/* Input enable control */
multiline_comment|/*&n; *&t;Define bit flags in Interrupt Status Register (UISR).&n; *&t;These same bits are used for the Interrupt Mask Register (UIMR).&n; */
DECL|macro|MCFUART_UIR_COS
mdefine_line|#define&t;MCFUART_UIR_COS&t;&t;0x80&t;&t;/* Change of state (CTS) */
DECL|macro|MCFUART_UIR_DELTABREAK
mdefine_line|#define&t;MCFUART_UIR_DELTABREAK&t;0x04&t;&t;/* Break start or stop */
DECL|macro|MCFUART_UIR_RXREADY
mdefine_line|#define&t;MCFUART_UIR_RXREADY&t;0x02&t;&t;/* Receiver ready */
DECL|macro|MCFUART_UIR_TXREADY
mdefine_line|#define&t;MCFUART_UIR_TXREADY&t;0x01&t;&t;/* Transmitter ready */
macro_line|#ifdef&t;CONFIG_M5272
multiline_comment|/*&n; *&t;Define bit flags in the Transmitter FIFO Register (UTF).&n; */
DECL|macro|MCFUART_UTF_TXB
mdefine_line|#define&t;MCFUART_UTF_TXB&t;&t;0x1f&t;&t;/* Transmitter data level */
DECL|macro|MCFUART_UTF_FULL
mdefine_line|#define&t;MCFUART_UTF_FULL&t;0x20&t;&t;/* Transmitter fifo full */
DECL|macro|MCFUART_UTF_TXS
mdefine_line|#define&t;MCFUART_UTF_TXS&t;&t;0xc0&t;&t;/* Transmitter status */
multiline_comment|/*&n; *&t;Define bit flags in the Receiver FIFO Register (URF).&n; */
DECL|macro|MCFUART_URF_RXB
mdefine_line|#define&t;MCFUART_URF_RXB&t;&t;0x1f&t;&t;/* Receiver data level */
DECL|macro|MCFUART_URF_FULL
mdefine_line|#define&t;MCFUART_URF_FULL&t;0x20&t;&t;/* Receiver fifo full */
DECL|macro|MCFUART_URF_RXS
mdefine_line|#define&t;MCFUART_URF_RXS&t;&t;0xc0&t;&t;/* Receiver status */
macro_line|#endif
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcfuart_h */
eof
