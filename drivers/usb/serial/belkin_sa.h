multiline_comment|/*&n; * Definitions for Belkin USB Serial Adapter Driver&n; *&n; *  Copyright (C) 2000&n; *      William Greathouse (wgreathouse@smva.com)&n; *&n; *  This program is largely derived from work by the linux-usb group&n; *  and associated source files.  Please see the usb/serial files for&n; *  individual credits and copyrights.&n; *  &n; * &t;This program is free software; you can redistribute it and/or modify&n; * &t;it under the terms of the GNU General Public License as published by&n; * &t;the Free Software Foundation; either version 2 of the License, or&n; * &t;(at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; * 12-Mar-2001 gkh&n; *&t;Added GoHubs GO-COM232 device id.&n; *&n; * 06-Nov-2000 gkh&n; *&t;Added old Belkin and Peracom device ids, which this driver supports&n; *&n; * 12-Oct-2000 William Greathouse&n; *    First cut at supporting Belkin USB Serial Adapter F5U103&n; *    I did not have a copy of the original work to support this&n; *    adapter, so pardon any stupid mistakes.  All of the information&n; *    I am using to write this driver was acquired by using a modified&n; *    UsbSnoop on Windows2000.&n; *    &n; */
macro_line|#ifndef __LINUX_USB_SERIAL_BSA_H
DECL|macro|__LINUX_USB_SERIAL_BSA_H
mdefine_line|#define __LINUX_USB_SERIAL_BSA_H
DECL|macro|BELKIN_DOCKSTATION_VID
mdefine_line|#define BELKIN_DOCKSTATION_VID&t;0x050d&t;/* Vendor Id */
DECL|macro|BELKIN_DOCKSTATION_PID
mdefine_line|#define BELKIN_DOCKSTATION_PID&t;0x1203&t;/* Product Id */
DECL|macro|BELKIN_SA_VID
mdefine_line|#define BELKIN_SA_VID&t;0x050d&t;/* Vendor Id */
DECL|macro|BELKIN_SA_PID
mdefine_line|#define BELKIN_SA_PID&t;0x0103&t;/* Product Id */
DECL|macro|BELKIN_OLD_VID
mdefine_line|#define BELKIN_OLD_VID&t;0x056c&t;/* Belkin&squot;s &quot;old&quot; vendor id */
DECL|macro|BELKIN_OLD_PID
mdefine_line|#define BELKIN_OLD_PID&t;0x8007&t;/* Belkin&squot;s &quot;old&quot; single port serial converter&squot;s id */
DECL|macro|PERACOM_VID
mdefine_line|#define PERACOM_VID&t;0x0565&t;/* Peracom&squot;s vendor id */
DECL|macro|PERACOM_PID
mdefine_line|#define PERACOM_PID&t;0x0001&t;/* Peracom&squot;s single port serial converter&squot;s id */
DECL|macro|GOHUBS_VID
mdefine_line|#define GOHUBS_VID&t;0x0921&t;/* GoHubs vendor id */
DECL|macro|GOHUBS_PID
mdefine_line|#define GOHUBS_PID&t;0x1000&t;/* GoHubs single port serial converter&squot;s id (identical to the Peracom device) */
multiline_comment|/* Vendor Request Interface */
DECL|macro|BELKIN_SA_SET_BAUDRATE_REQUEST
mdefine_line|#define BELKIN_SA_SET_BAUDRATE_REQUEST&t;0  /* Set baud rate */
DECL|macro|BELKIN_SA_SET_STOP_BITS_REQUEST
mdefine_line|#define BELKIN_SA_SET_STOP_BITS_REQUEST&t;1  /* Set stop bits (1,2) */
DECL|macro|BELKIN_SA_SET_DATA_BITS_REQUEST
mdefine_line|#define BELKIN_SA_SET_DATA_BITS_REQUEST&t;2  /* Set data bits (5,6,7,8) */
DECL|macro|BELKIN_SA_SET_PARITY_REQUEST
mdefine_line|#define BELKIN_SA_SET_PARITY_REQUEST&t;3  /* Set parity (None, Even, Odd) */
DECL|macro|BELKIN_SA_SET_DTR_REQUEST
mdefine_line|#define BELKIN_SA_SET_DTR_REQUEST&t;10 /* Set DTR state */
DECL|macro|BELKIN_SA_SET_RTS_REQUEST
mdefine_line|#define BELKIN_SA_SET_RTS_REQUEST&t;11 /* Set RTS state */
DECL|macro|BELKIN_SA_SET_BREAK_REQUEST
mdefine_line|#define BELKIN_SA_SET_BREAK_REQUEST&t;12 /* Set BREAK state */
DECL|macro|BELKIN_SA_SET_FLOW_CTRL_REQUEST
mdefine_line|#define BELKIN_SA_SET_FLOW_CTRL_REQUEST&t;16 /* Set flow control mode */
macro_line|#ifdef WHEN_I_LEARN_THIS
DECL|macro|BELKIN_SA_SET_MAGIC_REQUEST
mdefine_line|#define BELKIN_SA_SET_MAGIC_REQUEST&t;17 /* I don&squot;t know, possibly flush */
multiline_comment|/* (always in Wininit sequence before flow control) */
DECL|macro|BELKIN_SA_RESET
mdefine_line|#define BELKIN_SA_RESET &t;&t;xx /* Reset the port */
DECL|macro|BELKIN_SA_GET_MODEM_STATUS
mdefine_line|#define BELKIN_SA_GET_MODEM_STATUS&t;xx /* Force return of modem status register */
macro_line|#endif
DECL|macro|BELKIN_SA_SET_REQUEST_TYPE
mdefine_line|#define BELKIN_SA_SET_REQUEST_TYPE&t;0x40
DECL|macro|BELKIN_SA_BAUD
mdefine_line|#define BELKIN_SA_BAUD(b)&t;&t;(230400/b)
DECL|macro|BELKIN_SA_STOP_BITS
mdefine_line|#define BELKIN_SA_STOP_BITS(b)&t;&t;(b-1)
DECL|macro|BELKIN_SA_DATA_BITS
mdefine_line|#define BELKIN_SA_DATA_BITS(b)&t;&t;(b-5)
DECL|macro|BELKIN_SA_PARITY_NONE
mdefine_line|#define BELKIN_SA_PARITY_NONE&t;&t;0
DECL|macro|BELKIN_SA_PARITY_EVEN
mdefine_line|#define BELKIN_SA_PARITY_EVEN&t;&t;1
DECL|macro|BELKIN_SA_PARITY_ODD
mdefine_line|#define BELKIN_SA_PARITY_ODD&t;&t;2
DECL|macro|BELKIN_SA_PARITY_MARK
mdefine_line|#define BELKIN_SA_PARITY_MARK&t;&t;3
DECL|macro|BELKIN_SA_PARITY_SPACE
mdefine_line|#define BELKIN_SA_PARITY_SPACE&t;&t;4
DECL|macro|BELKIN_SA_FLOW_NONE
mdefine_line|#define BELKIN_SA_FLOW_NONE&t;&t;0x0000&t;/* No flow control */
DECL|macro|BELKIN_SA_FLOW_OCTS
mdefine_line|#define BELKIN_SA_FLOW_OCTS&t;&t;0x0001&t;/* use CTS input to throttle output */
DECL|macro|BELKIN_SA_FLOW_ODSR
mdefine_line|#define BELKIN_SA_FLOW_ODSR&t;&t;0x0002&t;/* use DSR input to throttle output */
DECL|macro|BELKIN_SA_FLOW_IDSR
mdefine_line|#define BELKIN_SA_FLOW_IDSR&t;&t;0x0004&t;/* use DSR input to enable receive */
DECL|macro|BELKIN_SA_FLOW_IDTR
mdefine_line|#define BELKIN_SA_FLOW_IDTR&t;&t;0x0008&t;/* use DTR output for input flow control */
DECL|macro|BELKIN_SA_FLOW_IRTS
mdefine_line|#define BELKIN_SA_FLOW_IRTS&t;&t;0x0010&t;/* use RTS output for input flow control */
DECL|macro|BELKIN_SA_FLOW_ORTS
mdefine_line|#define BELKIN_SA_FLOW_ORTS&t;&t;0x0020&t;/* use RTS to indicate data available to send */
DECL|macro|BELKIN_SA_FLOW_ERRSUB
mdefine_line|#define BELKIN_SA_FLOW_ERRSUB&t;&t;0x0040&t;/* ???? guess ???? substitute inline errors */
DECL|macro|BELKIN_SA_FLOW_OXON
mdefine_line|#define BELKIN_SA_FLOW_OXON&t;&t;0x0080&t;/* use XON/XOFF for output flow control */
DECL|macro|BELKIN_SA_FLOW_IXON
mdefine_line|#define BELKIN_SA_FLOW_IXON&t;&t;0x0100&t;/* use XON/XOFF for input flow control */
multiline_comment|/*&n; * It seems that the interrupt pipe is closely modelled after the&n; * 16550 register layout.  This is probably because the adapter can &n; * be used in a &quot;DOS&quot; environment to simulate a standard hardware port.&n; */
DECL|macro|BELKIN_SA_LSR_INDEX
mdefine_line|#define BELKIN_SA_LSR_INDEX&t;&t;2&t;&t;/* Line Status Register */
DECL|macro|BELKIN_SA_LSR_RDR
mdefine_line|#define BELKIN_SA_LSR_RDR&t;&t;0x01&t;/* receive data ready */
DECL|macro|BELKIN_SA_LSR_OE
mdefine_line|#define BELKIN_SA_LSR_OE&t;&t;0x02&t;/* overrun error */
DECL|macro|BELKIN_SA_LSR_PE
mdefine_line|#define BELKIN_SA_LSR_PE&t;&t;0x04&t;/* parity error */
DECL|macro|BELKIN_SA_LSR_FE
mdefine_line|#define BELKIN_SA_LSR_FE&t;&t;0x08&t;/* framing error */
DECL|macro|BELKIN_SA_LSR_BI
mdefine_line|#define BELKIN_SA_LSR_BI&t;&t;0x10&t;/* break indicator */
DECL|macro|BELKIN_SA_LSR_THE
mdefine_line|#define BELKIN_SA_LSR_THE&t;&t;0x20&t;/* transmit holding register empty */
DECL|macro|BELKIN_SA_LSR_TE
mdefine_line|#define BELKIN_SA_LSR_TE&t;&t;0x40&t;/* transmit register empty */
DECL|macro|BELKIN_SA_LSR_ERR
mdefine_line|#define BELKIN_SA_LSR_ERR&t;&t;0x80&t;/* OE | PE | FE | BI */
DECL|macro|BELKIN_SA_MSR_INDEX
mdefine_line|#define BELKIN_SA_MSR_INDEX&t;&t;3&t;&t;/* Modem Status Register */
DECL|macro|BELKIN_SA_MSR_DCTS
mdefine_line|#define BELKIN_SA_MSR_DCTS&t;&t;0x01&t;/* Delta CTS */
DECL|macro|BELKIN_SA_MSR_DDSR
mdefine_line|#define BELKIN_SA_MSR_DDSR&t;&t;0x02&t;/* Delta DSR */
DECL|macro|BELKIN_SA_MSR_DRI
mdefine_line|#define BELKIN_SA_MSR_DRI&t;&t;0x04&t;/* Delta RI */
DECL|macro|BELKIN_SA_MSR_DCD
mdefine_line|#define BELKIN_SA_MSR_DCD&t;&t;0x08&t;/* Delta CD */
DECL|macro|BELKIN_SA_MSR_CTS
mdefine_line|#define BELKIN_SA_MSR_CTS&t;&t;0x10&t;/* Current CTS */
DECL|macro|BELKIN_SA_MSR_DSR
mdefine_line|#define BELKIN_SA_MSR_DSR&t;&t;0x20&t;/* Current DSR */
DECL|macro|BELKIN_SA_MSR_RI
mdefine_line|#define BELKIN_SA_MSR_RI&t;&t;0x40&t;/* Current RI */
DECL|macro|BELKIN_SA_MSR_CD
mdefine_line|#define BELKIN_SA_MSR_CD&t;&t;0x80&t;/* Current CD */
macro_line|#endif /* __LINUX_USB_SERIAL_BSA_H */
eof
