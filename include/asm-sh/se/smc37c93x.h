macro_line|#ifndef __ASM_SH_SMC37C93X_H
DECL|macro|__ASM_SH_SMC37C93X_H
mdefine_line|#define __ASM_SH_SMC37C93X_H
multiline_comment|/*&n; * linux/include/asm-sh/smc37c93x.h&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * SMSC 37C93x Super IO Chip support&n; */
multiline_comment|/* Default base I/O address */
DECL|macro|FDC_PRIMARY_BASE
mdefine_line|#define FDC_PRIMARY_BASE&t;0x3f0
DECL|macro|IDE1_PRIMARY_BASE
mdefine_line|#define IDE1_PRIMARY_BASE&t;0x1f0
DECL|macro|IDE1_SECONDARY_BASE
mdefine_line|#define IDE1_SECONDARY_BASE&t;0x170
DECL|macro|PARPORT_PRIMARY_BASE
mdefine_line|#define PARPORT_PRIMARY_BASE&t;0x378
DECL|macro|COM1_PRIMARY_BASE
mdefine_line|#define COM1_PRIMARY_BASE&t;0x2f8
DECL|macro|COM2_PRIMARY_BASE
mdefine_line|#define COM2_PRIMARY_BASE&t;0x3f8
DECL|macro|RTC_PRIMARY_BASE
mdefine_line|#define RTC_PRIMARY_BASE&t;0x070
DECL|macro|KBC_PRIMARY_BASE
mdefine_line|#define KBC_PRIMARY_BASE&t;0x060
DECL|macro|AUXIO_PRIMARY_BASE
mdefine_line|#define AUXIO_PRIMARY_BASE&t;0x000&t;/* XXX */
multiline_comment|/* Logical device number */
DECL|macro|LDN_FDC
mdefine_line|#define LDN_FDC&t;&t;&t;0
DECL|macro|LDN_IDE1
mdefine_line|#define LDN_IDE1&t;&t;1
DECL|macro|LDN_IDE2
mdefine_line|#define LDN_IDE2&t;&t;2
DECL|macro|LDN_PARPORT
mdefine_line|#define LDN_PARPORT&t;&t;3
DECL|macro|LDN_COM1
mdefine_line|#define LDN_COM1&t;&t;4
DECL|macro|LDN_COM2
mdefine_line|#define LDN_COM2&t;&t;5
DECL|macro|LDN_RTC
mdefine_line|#define LDN_RTC&t;&t;&t;6
DECL|macro|LDN_KBC
mdefine_line|#define LDN_KBC&t;&t;&t;7
DECL|macro|LDN_AUXIO
mdefine_line|#define LDN_AUXIO&t;&t;8
multiline_comment|/* Configuration port and key */
DECL|macro|CONFIG_PORT
mdefine_line|#define CONFIG_PORT&t;&t;0x3f0
DECL|macro|INDEX_PORT
mdefine_line|#define INDEX_PORT&t;&t;CONFIG_PORT
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;&t;0x3f1
DECL|macro|CONFIG_ENTER
mdefine_line|#define CONFIG_ENTER&t;&t;0x55
DECL|macro|CONFIG_EXIT
mdefine_line|#define CONFIG_EXIT&t;&t;0xaa
multiline_comment|/* Configuration index */
DECL|macro|CURRENT_LDN_INDEX
mdefine_line|#define CURRENT_LDN_INDEX&t;0x07
DECL|macro|POWER_CONTROL_INDEX
mdefine_line|#define POWER_CONTROL_INDEX&t;0x22
DECL|macro|ACTIVATE_INDEX
mdefine_line|#define ACTIVATE_INDEX&t;&t;0x30
DECL|macro|IO_BASE_HI_INDEX
mdefine_line|#define IO_BASE_HI_INDEX&t;0x60
DECL|macro|IO_BASE_LO_INDEX
mdefine_line|#define IO_BASE_LO_INDEX&t;0x61
DECL|macro|IRQ_SELECT_INDEX
mdefine_line|#define IRQ_SELECT_INDEX&t;0x70
DECL|macro|DMA_SELECT_INDEX
mdefine_line|#define DMA_SELECT_INDEX&t;0x74
DECL|macro|GPIO46_INDEX
mdefine_line|#define GPIO46_INDEX&t;&t;0xc6
DECL|macro|GPIO47_INDEX
mdefine_line|#define GPIO47_INDEX&t;&t;0xc7
multiline_comment|/* UART stuff. Only for debugging.  */
multiline_comment|/* UART Register */
DECL|macro|UART_RBR
mdefine_line|#define UART_RBR&t;0x0&t;/* Receiver Buffer Register (Read Only) */
DECL|macro|UART_THR
mdefine_line|#define UART_THR&t;0x0&t;/* Transmitter Holding Register (Write Only) */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;0x2&t;/* Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0x4&t;/* Interrupt Ident Register (Read Only) */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0x4&t;/* FIFO Control Register (Write Only) */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0x6&t;/* Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0x8&t;/* MODEM Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;0xa&t;/* Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0xc&t;/* MODEM Status Register */
DECL|macro|UART_SCR
mdefine_line|#define UART_SCR&t;0xe&t;/* Scratch Register */
DECL|macro|UART_DLL
mdefine_line|#define UART_DLL&t;0x0&t;/* Divisor Latch (LS) */
DECL|macro|UART_DLM
mdefine_line|#define UART_DLM&t;0x2&t;/* Divisor Latch (MS) */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|uart_reg
r_typedef
r_struct
id|uart_reg
(brace
DECL|member|rbr
r_volatile
id|__u16
id|rbr
suffix:semicolon
DECL|member|ier
r_volatile
id|__u16
id|ier
suffix:semicolon
DECL|member|iir
r_volatile
id|__u16
id|iir
suffix:semicolon
DECL|member|lcr
r_volatile
id|__u16
id|lcr
suffix:semicolon
DECL|member|mcr
r_volatile
id|__u16
id|mcr
suffix:semicolon
DECL|member|lsr
r_volatile
id|__u16
id|lsr
suffix:semicolon
DECL|member|msr
r_volatile
id|__u16
id|msr
suffix:semicolon
DECL|member|scr
r_volatile
id|__u16
id|scr
suffix:semicolon
DECL|typedef|uart_reg
)brace
id|uart_reg
suffix:semicolon
macro_line|#endif /* ! __ASSEMBLY__ */
multiline_comment|/* Alias for Write Only Register */
DECL|macro|thr
mdefine_line|#define thr&t;rbr
DECL|macro|tcr
mdefine_line|#define tcr&t;iir
multiline_comment|/* Alias for Divisor Latch Register */
DECL|macro|dll
mdefine_line|#define dll&t;rbr
DECL|macro|dlm
mdefine_line|#define dlm&t;ier
DECL|macro|fcr
mdefine_line|#define fcr&t;iir
multiline_comment|/* Interrupt Enable Register */
DECL|macro|IER_ERDAI
mdefine_line|#define IER_ERDAI&t;0x0100&t;/* Enable Received Data Available Interrupt */
DECL|macro|IER_ETHREI
mdefine_line|#define IER_ETHREI&t;0x0200&t;/* Enable Transmitter Holding Register Empty Interrupt */
DECL|macro|IER_ELSI
mdefine_line|#define IER_ELSI&t;0x0400&t;/* Enable Receiver Line Status Interrupt */
DECL|macro|IER_EMSI
mdefine_line|#define IER_EMSI&t;0x0800&t;/* Enable MODEM Status Interrupt */
multiline_comment|/* Interrupt Ident Register */
DECL|macro|IIR_IP
mdefine_line|#define IIR_IP&t;&t;0x0100&t;/* &quot;0&quot; if Interrupt Pending */
DECL|macro|IIR_IIB0
mdefine_line|#define IIR_IIB0&t;0x0200&t;/* Interrupt ID Bit 0 */
DECL|macro|IIR_IIB1
mdefine_line|#define IIR_IIB1&t;0x0400&t;/* Interrupt ID Bit 1 */
DECL|macro|IIR_IIB2
mdefine_line|#define IIR_IIB2&t;0x0800&t;/* Interrupt ID Bit 2 */
DECL|macro|IIR_FIFO
mdefine_line|#define IIR_FIFO&t;0xc000&t;/* FIFOs enabled */
multiline_comment|/* FIFO Control Register */
DECL|macro|FCR_FEN
mdefine_line|#define FCR_FEN&t;&t;0x0100&t;/* FIFO enable */
DECL|macro|FCR_RFRES
mdefine_line|#define FCR_RFRES&t;0x0200&t;/* Receiver FIFO reset */
DECL|macro|FCR_TFRES
mdefine_line|#define FCR_TFRES&t;0x0400&t;/* Transmitter FIFO reset */
DECL|macro|FCR_DMA
mdefine_line|#define FCR_DMA&t;&t;0x0800&t;/* DMA mode select */
DECL|macro|FCR_RTL
mdefine_line|#define FCR_RTL&t;&t;0x4000&t;/* Receiver triger (LSB) */
DECL|macro|FCR_RTM
mdefine_line|#define FCR_RTM&t;&t;0x8000&t;/* Receiver triger (MSB) */
multiline_comment|/* Line Control Register */
DECL|macro|LCR_WLS0
mdefine_line|#define LCR_WLS0&t;0x0100&t;/* Word Length Select Bit 0 */
DECL|macro|LCR_WLS1
mdefine_line|#define LCR_WLS1&t;0x0200&t;/* Word Length Select Bit 1 */
DECL|macro|LCR_STB
mdefine_line|#define LCR_STB&t;&t;0x0400&t;/* Number of Stop Bits */
DECL|macro|LCR_PEN
mdefine_line|#define LCR_PEN&t;&t;0x0800&t;/* Parity Enable */
DECL|macro|LCR_EPS
mdefine_line|#define LCR_EPS&t;&t;0x1000&t;/* Even Parity Select */
DECL|macro|LCR_SP
mdefine_line|#define LCR_SP&t;&t;0x2000&t;/* Stick Parity */
DECL|macro|LCR_SB
mdefine_line|#define LCR_SB&t;&t;0x4000&t;/* Set Break */
DECL|macro|LCR_DLAB
mdefine_line|#define LCR_DLAB&t;0x8000&t;/* Divisor Latch Access Bit */
multiline_comment|/* MODEM Control Register */
DECL|macro|MCR_DTR
mdefine_line|#define MCR_DTR&t;&t;0x0100&t;/* Data Terminal Ready */
DECL|macro|MCR_RTS
mdefine_line|#define MCR_RTS&t;&t;0x0200&t;/* Request to Send */
DECL|macro|MCR_OUT1
mdefine_line|#define MCR_OUT1&t;0x0400&t;/* Out 1 */
DECL|macro|MCR_IRQEN
mdefine_line|#define MCR_IRQEN&t;0x0800&t;/* IRQ Enable */
DECL|macro|MCR_LOOP
mdefine_line|#define MCR_LOOP&t;0x1000&t;/* Loop */
multiline_comment|/* Line Status Register */
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR&t;&t;0x0100&t;/* Data Ready */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE&t;&t;0x0200&t;/* Overrun Error */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE&t;&t;0x0400&t;/* Parity Error */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE&t;&t;0x0800&t;/* Framing Error */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI&t;&t;0x1000&t;/* Break Interrupt */
DECL|macro|LSR_THRE
mdefine_line|#define LSR_THRE&t;0x2000&t;/* Transmitter Holding Register Empty */
DECL|macro|LSR_TEMT
mdefine_line|#define LSR_TEMT&t;0x4000&t;/* Transmitter Empty */
DECL|macro|LSR_FIFOE
mdefine_line|#define LSR_FIFOE&t;0x8000&t;/* Receiver FIFO error */
multiline_comment|/* MODEM Status Register */
DECL|macro|MSR_DCTS
mdefine_line|#define MSR_DCTS&t;0x0100&t;/* Delta Clear to Send */
DECL|macro|MSR_DDSR
mdefine_line|#define MSR_DDSR&t;0x0200&t;/* Delta Data Set Ready */
DECL|macro|MSR_TERI
mdefine_line|#define MSR_TERI&t;0x0400&t;/* Trailing Edge Ring Indicator */
DECL|macro|MSR_DDCD
mdefine_line|#define MSR_DDCD&t;0x0800&t;/* Delta Data Carrier Detect */
DECL|macro|MSR_CTS
mdefine_line|#define MSR_CTS&t;&t;0x1000&t;/* Clear to Send */
DECL|macro|MSR_DSR
mdefine_line|#define MSR_DSR&t;&t;0x2000&t;/* Data Set Ready */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;0x4000&t;/* Ring Indicator */
DECL|macro|MSR_DCD
mdefine_line|#define MSR_DCD&t;&t;0x8000&t;/* Data Carrier Detect */
multiline_comment|/* Baud Rate Divisor */
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;(1843200)&t;/* 1.8432 MHz */
DECL|macro|UART_BAUD
mdefine_line|#define UART_BAUD(x)&t;(UART_CLK / (16 * (x)))
multiline_comment|/* RTC register definition */
DECL|macro|RTC_SECONDS
mdefine_line|#define RTC_SECONDS             0
DECL|macro|RTC_SECONDS_ALARM
mdefine_line|#define RTC_SECONDS_ALARM       1
DECL|macro|RTC_MINUTES
mdefine_line|#define RTC_MINUTES             2
DECL|macro|RTC_MINUTES_ALARM
mdefine_line|#define RTC_MINUTES_ALARM       3
DECL|macro|RTC_HOURS
mdefine_line|#define RTC_HOURS               4
DECL|macro|RTC_HOURS_ALARM
mdefine_line|#define RTC_HOURS_ALARM         5
DECL|macro|RTC_DAY_OF_WEEK
mdefine_line|#define RTC_DAY_OF_WEEK         6
DECL|macro|RTC_DAY_OF_MONTH
mdefine_line|#define RTC_DAY_OF_MONTH        7
DECL|macro|RTC_MONTH
mdefine_line|#define RTC_MONTH               8
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR                9
DECL|macro|RTC_FREQ_SELECT
mdefine_line|#define RTC_FREQ_SELECT&t;&t;10
DECL|macro|RTC_UIP
macro_line|# define RTC_UIP 0x80
DECL|macro|RTC_DIV_CTL
macro_line|# define RTC_DIV_CTL 0x70
multiline_comment|/* This RTC can work under 32.768KHz clock only.  */
DECL|macro|RTC_OSC_ENABLE
macro_line|# define RTC_OSC_ENABLE 0x20
DECL|macro|RTC_OSC_DISABLE
macro_line|# define RTC_OSC_DISABLE 0x00
DECL|macro|RTC_CONTROL
mdefine_line|#define RTC_CONTROL     &t;11
DECL|macro|RTC_SET
macro_line|# define RTC_SET 0x80
DECL|macro|RTC_PIE
macro_line|# define RTC_PIE 0x40
DECL|macro|RTC_AIE
macro_line|# define RTC_AIE 0x20
DECL|macro|RTC_UIE
macro_line|# define RTC_UIE 0x10
DECL|macro|RTC_SQWE
macro_line|# define RTC_SQWE 0x08
DECL|macro|RTC_DM_BINARY
macro_line|# define RTC_DM_BINARY 0x04
DECL|macro|RTC_24H
macro_line|# define RTC_24H 0x02
DECL|macro|RTC_DST_EN
macro_line|# define RTC_DST_EN 0x01
macro_line|#endif  /* __ASM_SH_SMC37C93X_H */
eof
