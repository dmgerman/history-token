multiline_comment|/*&n; * Definitions for MCT (Magic Control Technology) USB-RS232 Converter Driver&n; *&n; *   Copyright (C) 2000 Wolfgang Grandegger (wolfgang@ces.ch)&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; * This driver is for the device MCT USB-RS232 Converter (25 pin, Model No.&n; * U232-P25) from Magic Control Technology Corp. (there is also a 9 pin&n; * Model No. U232-P9). See http://www.mct.com.tw/p_u232.html for further&n; * information. The properties of this device are listed at the end of this&n; * file. This device is available from various distributors. I know Hana,&n; * http://www.hana.de and D-Link, http://www.dlink.com/products/usb/dsbs25.&n; *&n; * All of the information about the device was acquired by using SniffUSB&n; * on Windows98. The technical details of the reverse engineering are&n; * summarized at the end of this file.&n; */
macro_line|#ifndef __LINUX_USB_SERIAL_MCT_U232_H
DECL|macro|__LINUX_USB_SERIAL_MCT_U232_H
mdefine_line|#define __LINUX_USB_SERIAL_MCT_U232_H
DECL|macro|MCT_U232_VID
mdefine_line|#define MCT_U232_VID&t;                0x0711&t;/* Vendor Id */
DECL|macro|MCT_U232_PID
mdefine_line|#define MCT_U232_PID&t;                0x0210&t;/* Original MCT Product Id */
multiline_comment|/* U232-P25, Sitecom */
DECL|macro|MCT_U232_SITECOM_PID
mdefine_line|#define MCT_U232_SITECOM_PID&t;&t;0x0230&t;/* Sitecom Product Id */
multiline_comment|/* DU-H3SP USB BAY hub */
DECL|macro|MCT_U232_DU_H3SP_PID
mdefine_line|#define MCT_U232_DU_H3SP_PID&t;&t;0x0200&t;/* D-Link DU-H3SP USB BAY */
multiline_comment|/*&n; * Vendor Request Interface&n; */
DECL|macro|MCT_U232_SET_REQUEST_TYPE
mdefine_line|#define MCT_U232_SET_REQUEST_TYPE&t;0x40
DECL|macro|MCT_U232_GET_REQUEST_TYPE
mdefine_line|#define MCT_U232_GET_REQUEST_TYPE&t;0xc0
DECL|macro|MCT_U232_GET_MODEM_STAT_REQUEST
mdefine_line|#define MCT_U232_GET_MODEM_STAT_REQUEST 2  /* Get Modem Status Register (MSR) */
DECL|macro|MCT_U232_GET_MODEM_STAT_SIZE
mdefine_line|#define MCT_U232_GET_MODEM_STAT_SIZE    1
DECL|macro|MCT_U232_GET_LINE_CTRL_REQUEST
mdefine_line|#define MCT_U232_GET_LINE_CTRL_REQUEST  6  /* Get Line Control Register (LCR) */
DECL|macro|MCT_U232_GET_LINE_CTRL_SIZE
mdefine_line|#define MCT_U232_GET_LINE_CTRL_SIZE     1  /* ... not used by this driver */
DECL|macro|MCT_U232_SET_BAUD_RATE_REQUEST
mdefine_line|#define MCT_U232_SET_BAUD_RATE_REQUEST&t;5  /* Set Baud Rate Divisor */
DECL|macro|MCT_U232_SET_BAUD_RATE_SIZE
mdefine_line|#define MCT_U232_SET_BAUD_RATE_SIZE     4
DECL|macro|MCT_U232_SET_LINE_CTRL_REQUEST
mdefine_line|#define MCT_U232_SET_LINE_CTRL_REQUEST&t;7  /* Set Line Control Register (LCR) */
DECL|macro|MCT_U232_SET_LINE_CTRL_SIZE
mdefine_line|#define MCT_U232_SET_LINE_CTRL_SIZE     1
DECL|macro|MCT_U232_SET_MODEM_CTRL_REQUEST
mdefine_line|#define MCT_U232_SET_MODEM_CTRL_REQUEST&t;10 /* Set Modem Control Register (MCR) */
DECL|macro|MCT_U232_SET_MODEM_CTRL_SIZE
mdefine_line|#define MCT_U232_SET_MODEM_CTRL_SIZE    1
multiline_comment|/*&n; * Baud rate (divisor)&n; */
DECL|macro|MCT_U232_BAUD_RATE
mdefine_line|#define MCT_U232_BAUD_RATE(b)&t;&t;(115200/b)
multiline_comment|/*&n; * Line Control Register (LCR)&n; */
DECL|macro|MCT_U232_SET_BREAK
mdefine_line|#define MCT_U232_SET_BREAK              0x40
DECL|macro|MCT_U232_PARITY_SPACE
mdefine_line|#define MCT_U232_PARITY_SPACE&t;&t;0x38
DECL|macro|MCT_U232_PARITY_MARK
mdefine_line|#define MCT_U232_PARITY_MARK&t;&t;0x28
DECL|macro|MCT_U232_PARITY_EVEN
mdefine_line|#define MCT_U232_PARITY_EVEN&t;&t;0x18
DECL|macro|MCT_U232_PARITY_ODD
mdefine_line|#define MCT_U232_PARITY_ODD&t;&t;0x08
DECL|macro|MCT_U232_PARITY_NONE
mdefine_line|#define MCT_U232_PARITY_NONE&t;&t;0x00
DECL|macro|MCT_U232_DATA_BITS_5
mdefine_line|#define MCT_U232_DATA_BITS_5            0x00
DECL|macro|MCT_U232_DATA_BITS_6
mdefine_line|#define MCT_U232_DATA_BITS_6            0x01
DECL|macro|MCT_U232_DATA_BITS_7
mdefine_line|#define MCT_U232_DATA_BITS_7            0x02
DECL|macro|MCT_U232_DATA_BITS_8
mdefine_line|#define MCT_U232_DATA_BITS_8            0x03
DECL|macro|MCT_U232_STOP_BITS_2
mdefine_line|#define MCT_U232_STOP_BITS_2            0x04
DECL|macro|MCT_U232_STOP_BITS_1
mdefine_line|#define MCT_U232_STOP_BITS_1            0x00
multiline_comment|/*&n; * Modem Control Register (MCR)&n; */
DECL|macro|MCT_U232_MCR_NONE
mdefine_line|#define MCT_U232_MCR_NONE               0x8     /* Deactivate DTR and RTS */
DECL|macro|MCT_U232_MCR_RTS
mdefine_line|#define MCT_U232_MCR_RTS                0xa     /* Activate RTS */
DECL|macro|MCT_U232_MCR_DTR
mdefine_line|#define MCT_U232_MCR_DTR                0x9     /* Activate DTR */
multiline_comment|/*&n; * Modem Status Register (MSR)&n; */
DECL|macro|MCT_U232_MSR_INDEX
mdefine_line|#define MCT_U232_MSR_INDEX              0x0     /* data[index] */
DECL|macro|MCT_U232_MSR_CD
mdefine_line|#define MCT_U232_MSR_CD                 0x80    /* Current CD */
DECL|macro|MCT_U232_MSR_RI
mdefine_line|#define MCT_U232_MSR_RI                 0x40    /* Current RI */
DECL|macro|MCT_U232_MSR_DSR
mdefine_line|#define MCT_U232_MSR_DSR                0x20    /* Current DSR */
DECL|macro|MCT_U232_MSR_CTS
mdefine_line|#define MCT_U232_MSR_CTS                0x10    /* Current CTS */
DECL|macro|MCT_U232_MSR_DCD
mdefine_line|#define MCT_U232_MSR_DCD                0x08    /* Delta CD */
DECL|macro|MCT_U232_MSR_DRI
mdefine_line|#define MCT_U232_MSR_DRI                0x04    /* Delta RI */
DECL|macro|MCT_U232_MSR_DDSR
mdefine_line|#define MCT_U232_MSR_DDSR               0x02    /* Delta DSR */
DECL|macro|MCT_U232_MSR_DCTS
mdefine_line|#define MCT_U232_MSR_DCTS               0x01    /* Delta CTS */
multiline_comment|/*&n; * Line Status Register (LSR)&n; */
DECL|macro|MCT_U232_LSR_INDEX
mdefine_line|#define MCT_U232_LSR_INDEX              1       /* data[index] */
DECL|macro|MCT_U232_LSR_ERR
mdefine_line|#define MCT_U232_LSR_ERR                0x80    /* OE | PE | FE | BI */
DECL|macro|MCT_U232_LSR_TEMT
mdefine_line|#define MCT_U232_LSR_TEMT               0x40    /* transmit register empty */
DECL|macro|MCT_U232_LSR_THRE
mdefine_line|#define MCT_U232_LSR_THRE               0x20    /* transmit holding register empty */
DECL|macro|MCT_U232_LSR_BI
mdefine_line|#define MCT_U232_LSR_BI                 0x10    /* break indicator */
DECL|macro|MCT_U232_LSR_FE
mdefine_line|#define MCT_U232_LSR_FE                 0x08    /* framing error */
DECL|macro|MCT_U232_LSR_OE
mdefine_line|#define MCT_U232_LSR_OE                 0x02    /* overrun error */
DECL|macro|MCT_U232_LSR_PE
mdefine_line|#define MCT_U232_LSR_PE                 0x04    /* parity error */
DECL|macro|MCT_U232_LSR_OE
mdefine_line|#define MCT_U232_LSR_OE                 0x02    /* overrun error */
DECL|macro|MCT_U232_LSR_DR
mdefine_line|#define MCT_U232_LSR_DR                 0x01    /* receive data ready */
multiline_comment|/* -----------------------------------------------------------------------------&n; * Technical Specification reverse engineered with SniffUSB on Windows98&n; * =====================================================================&n; *&n; *  The technical details of the device have been acquired be using &quot;SniffUSB&quot;&n; *  and the vendor-supplied device driver (version 2.3A) under Windows98. To&n; *  identify the USB vendor-specific requests and to assign them to terminal &n; *  settings (flow control, baud rate, etc.) the program &quot;SerialSettings&quot; from&n; *  William G. Greathouse has been proven to be very useful. I also used the&n; *  Win98 &quot;HyperTerminal&quot; and &quot;usb-robot&quot; on Linux for testing. The results and &n; *  observations are summarized below:&n; *&n; *  The USB requests seem to be directly mapped to the registers of a 8250,&n; *  16450 or 16550 UART. The FreeBSD handbook (appendix F.4 &quot;Input/Output&n; *  devices&quot;) contains a comprehensive description of UARTs and its registers.&n; *  The bit descriptions are actually taken from there.&n; *&n; *&n; * Baud rate (divisor)&n; * -------------------&n; *&n; *   BmRequestType:  0x4 (0100 0000B)&n; *   bRequest:       0x5&n; *   wValue:         0x0&n; *   wIndex:         0x0&n; *   wLength:        0x4&n; *   Data:           divisor = 115200 / baud_rate&n; *&n; *&n; * Line Control Register (LCR)&n; * ---------------------------&n; *&n; *  BmRequestType:  0x4 (0100 0000B)    0xc (1100 0000B)&n; *  bRequest:       0x7                 0x6&n; *  wValue:         0x0&n; *  wIndex:         0x0&n; *  wLength:        0x1&n; *  Data:           LCR (see below)&n; *&n; *  Bit 7: Divisor Latch Access Bit (DLAB). When set, access to the data&n; *  &t;   transmit/receive register (THR/RBR) and the Interrupt Enable Register&n; *  &t;   (IER) is disabled. Any access to these ports is now redirected to the&n; *  &t;   Divisor Latch Registers. Setting this bit, loading the Divisor&n; *  &t;   Registers, and clearing DLAB should be done with interrupts disabled.&n; *  Bit 6: Set Break. When set to &quot;1&quot;, the transmitter begins to transmit&n; *  &t;   continuous Spacing until this bit is set to &quot;0&quot;. This overrides any&n; *  &t;   bits of characters that are being transmitted.&n; *  Bit 5: Stick Parity. When parity is enabled, setting this bit causes parity&n; *  &t;   to always be &quot;1&quot; or &quot;0&quot;, based on the value of Bit 4.&n; *  Bit 4: Even Parity Select (EPS). When parity is enabled and Bit 5 is &quot;0&quot;,&n; *  &t;   setting this bit causes even parity to be transmitted and expected.&n; *  &t;   Otherwise, odd parity is used.&n; *  Bit 3: Parity Enable (PEN). When set to &quot;1&quot;, a parity bit is inserted&n; *  &t;   between the last bit of the data and the Stop Bit. The UART will also&n; *  &t;   expect parity to be present in the received data.&n; *  Bit 2: Number of Stop Bits (STB). If set to &quot;1&quot; and using 5-bit data words,&n; *  &t;   1.5 Stop Bits are transmitted and expected in each data word. For&n; *  &t;   6, 7 and 8-bit data words, 2 Stop Bits are transmitted and expected.&n; *  &t;   When this bit is set to &quot;0&quot;, one Stop Bit is used on each data word.&n; *  Bit 1: Word Length Select Bit #1 (WLSB1)&n; *  Bit 0: Word Length Select Bit #0 (WLSB0)&n; *  &t;   Together these bits specify the number of bits in each data word.&n; *  &t;     1 0  Word Length&n; *  &t;     0 0  5 Data Bits&n; *  &t;     0 1  6 Data Bits&n; *  &t;     1 0  7 Data Bits&n; *  &t;     1 1  8 Data Bits&n; *&n; *  SniffUSB observations: Bit 7 seems not to be used. There seem to be two bugs&n; *  in the Win98 driver: the break does not work (bit 6 is not asserted) and the&n; *  sticky parity bit is not cleared when set once. The LCR can also be read&n; *  back with USB request 6 but this has never been observed with SniffUSB.&n; *&n; *&n; * Modem Control Register (MCR)&n; * ----------------------------&n; *&n; *  BmRequestType:  0x4  (0100 0000B)&n; *  bRequest:       0xa&n; *  wValue:         0x0&n; *  wIndex:         0x0&n; *  wLength:        0x1&n; *  Data:           MCR (Bit 4..7, see below)&n; *&n; *  Bit 7: Reserved, always 0.&n; *  Bit 6: Reserved, always 0.&n; *  Bit 5: Reserved, always 0.&n; *  Bit 4: Loop-Back Enable. When set to &quot;1&quot;, the UART transmitter and receiver&n; *  &t;   are internally connected together to allow diagnostic operations. In&n; *  &t;   addition, the UART modem control outputs are connected to the UART&n; *  &t;   modem control inputs. CTS is connected to RTS, DTR is connected to&n; *  &t;   DSR, OUT1 is connected to RI, and OUT 2 is connected to DCD.&n; *  Bit 3: OUT 2. An auxiliary output that the host processor may set high or&n; *  &t;   low. In the IBM PC serial adapter (and most clones), OUT 2 is used&n; *  &t;   to tri-state (disable) the interrupt signal from the&n; *  &t;   8250/16450/16550 UART.&n; *  Bit 2: OUT 1. An auxiliary output that the host processor may set high or&n; *  &t;   low. This output is not used on the IBM PC serial adapter.&n; *  Bit 1: Request to Send (RTS). When set to &quot;1&quot;, the output of the UART -RTS&n; *  &t;   line is Low (Active).&n; *  Bit 0: Data Terminal Ready (DTR). When set to &quot;1&quot;, the output of the UART&n; *  &t;   -DTR line is Low (Active).&n; *&n; *  SniffUSB observations: Bit 2 and 4 seem not to be used but bit 3 has been&n; *  seen _always_ set.&n; *&n; *&n; * Modem Status Register (MSR)&n; * ---------------------------&n; *&n; *  BmRequestType:  0xc  (1100 0000B)&n; *  bRequest:       0x2&n; *  wValue:         0x0&n; *  wIndex:         0x0&n; *  wLength:        0x1&n; *  Data:           MSR (see below)&n; *&n; *  Bit 7: Data Carrier Detect (CD). Reflects the state of the DCD line on the&n; *  &t;   UART.&n; *  Bit 6: Ring Indicator (RI). Reflects the state of the RI line on the UART.&n; *  Bit 5: Data Set Ready (DSR). Reflects the state of the DSR line on the UART.&n; *  Bit 4: Clear To Send (CTS). Reflects the state of the CTS line on the UART.&n; *  Bit 3: Delta Data Carrier Detect (DDCD). Set to &quot;1&quot; if the -DCD line has&n; *  &t;   changed state one more more times since the last time the MSR was&n; *  &t;   read by the host.&n; *  Bit 2: Trailing Edge Ring Indicator (TERI). Set to &quot;1&quot; if the -RI line has&n; *  &t;   had a low to high transition since the last time the MSR was read by&n; *  &t;   the host.&n; *  Bit 1: Delta Data Set Ready (DDSR). Set to &quot;1&quot; if the -DSR line has changed&n; *  &t;   state one more more times since the last time the MSR was read by the&n; *  &t;   host.&n; *  Bit 0: Delta Clear To Send (DCTS). Set to &quot;1&quot; if the -CTS line has changed&n; *  &t;   state one more times since the last time the MSR was read by the&n; *  &t;   host.&n; *&n; *  SniffUSB observations: the MSR is also returned as first byte on the&n; *  interrupt-in endpoint 0x83 to signal changes of modem status lines. The USB&n; *  request to read MSR cannot be applied during normal device operation.&n; *&n; *&n; * Line Status Register (LSR)&n; * --------------------------&n; *&n; *  Bit 7   Error in Receiver FIFO. On the 8250/16450 UART, this bit is zero.&n; *  &t;    This bit is set to &quot;1&quot; when any of the bytes in the FIFO have one or&n; *  &t;    more of the following error conditions: PE, FE, or BI.&n; *  Bit 6   Transmitter Empty (TEMT). When set to &quot;1&quot;, there are no words&n; *  &t;    remaining in the transmit FIFO or the transmit shift register. The&n; *  &t;    transmitter is completely idle.&n; *  Bit 5   Transmitter Holding Register Empty (THRE). When set to &quot;1&quot;, the FIFO&n; *  &t;    (or holding register) now has room for at least one additional word&n; *  &t;    to transmit. The transmitter may still be transmitting when this bit&n; *  &t;    is set to &quot;1&quot;.&n; *  Bit 4   Break Interrupt (BI). The receiver has detected a Break signal.&n; *  Bit 3   Framing Error (FE). A Start Bit was detected but the Stop Bit did not&n; *  &t;    appear at the expected time. The received word is probably garbled.&n; *  Bit 2   Parity Error (PE). The parity bit was incorrect for the word received.&n; *  Bit 1   Overrun Error (OE). A new word was received and there was no room in&n; *  &t;    the receive buffer. The newly-arrived word in the shift register is&n; *  &t;    discarded. On 8250/16450 UARTs, the word in the holding register is&n; *  &t;    discarded and the newly- arrived word is put in the holding register.&n; *  Bit 0   Data Ready (DR). One or more words are in the receive FIFO that the&n; *  &t;    host may read. A word must be completely received and moved from the&n; *  &t;    shift register into the FIFO (or holding register for 8250/16450&n; *  &t;    designs) before this bit is set.&n; *&n; *  SniffUSB observations: the LSR is returned as second byte on the interrupt-in&n; *  endpoint 0x83 to signal error conditions. Such errors have been seen with&n; *  minicom/zmodem transfers (CRC errors).&n; *&n; *&n; * Flow control&n; * ------------&n; *&n; *  SniffUSB observations: no flow control specific requests have been realized&n; *  apart from DTR/RTS settings. Both signals are dropped for no flow control&n; *  but asserted for hardware or software flow control.&n; *&n; *&n; * Endpoint usage&n; * --------------&n; *&n; *  SniffUSB observations: the bulk-out endpoint 0x1 and interrupt-in endpoint&n; *  0x81 is used to transmit and receive characters. The second interrupt-in &n; *  endpoint 0x83 signals exceptional conditions like modem line changes and &n; *  errors. The first byte returned is the MSR and the second byte the LSR.&n; *&n; *&n; * Other observations&n; * ------------------&n; *&n; *  Queued bulk transfers like used in visor.c did not work. &n; *  &n; *&n; * Properties of the USB device used (as found in /var/log/messages)&n; * -----------------------------------------------------------------&n; *&n; *  Manufacturer: MCT Corporation.&n; *  Product: USB-232 Interfact Controller&n; *  SerialNumber: U2S22050&n; *&n; *    Length              = 18&n; *    DescriptorType      = 01&n; *    USB version         = 1.00&n; *    Vendor:Product      = 0711:0210&n; *    MaxPacketSize0      = 8&n; *    NumConfigurations   = 1&n; *    Device version      = 1.02&n; *    Device Class:SubClass:Protocol = 00:00:00&n; *      Per-interface classes&n; *  Configuration:&n; *    bLength             =    9&n; *    bDescriptorType     =   02&n; *    wTotalLength        = 0027&n; *    bNumInterfaces      =   01&n; *    bConfigurationValue =   01&n; *    iConfiguration      =   00&n; *    bmAttributes        =   c0&n; *    MaxPower            =  100mA&n; *&n; *    Interface: 0&n; *    Alternate Setting:  0&n; *      bLength             =    9&n; *      bDescriptorType     =   04&n; *      bInterfaceNumber    =   00&n; *      bAlternateSetting   =   00&n; *      bNumEndpoints       =   03&n; *      bInterface Class:SubClass:Protocol =   00:00:00&n; *      iInterface          =   00&n; *      Endpoint:&n; * &t;  bLength             =    7&n; * &t;  bDescriptorType     =   05&n; * &t;  bEndpointAddress    =   81 (in)&n; * &t;  bmAttributes        =   03 (Interrupt)&n; * &t;  wMaxPacketSize      = 0040&n; * &t;  bInterval           =   02&n; *      Endpoint:&n; * &t;  bLength             =    7&n; * &t;  bDescriptorType     =   05&n; * &t;  bEndpointAddress    =   01 (out)&n; * &t;  bmAttributes        =   02 (Bulk)&n; * &t;  wMaxPacketSize      = 0040&n; * &t;  bInterval           =   00&n; *      Endpoint:&n; * &t;  bLength             =    7&n; * &t;  bDescriptorType     =   05&n; * &t;  bEndpointAddress    =   83 (in)&n; * &t;  bmAttributes        =   03 (Interrupt)&n; * &t;  wMaxPacketSize      = 0002&n; * &t;  bInterval           =   02&n; */
macro_line|#endif /* __LINUX_USB_SERIAL_MCT_U232_H */
eof
