multiline_comment|/*&n; * USB ConnectTech WhiteHEAT driver&n; *&n; *      Copyright (C) 2002&n; *          Connect Tech Inc.&t;&n; *&n; *      Copyright (C) 1999, 2000&n; *          Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; */
macro_line|#ifndef __LINUX_USB_SERIAL_WHITEHEAT_H
DECL|macro|__LINUX_USB_SERIAL_WHITEHEAT_H
mdefine_line|#define __LINUX_USB_SERIAL_WHITEHEAT_H
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
multiline_comment|/* WhiteHEAT commands */
DECL|macro|WHITEHEAT_OPEN
mdefine_line|#define WHITEHEAT_OPEN&t;&t;&t;1&t;/* open the port */
DECL|macro|WHITEHEAT_CLOSE
mdefine_line|#define WHITEHEAT_CLOSE&t;&t;&t;2&t;/* close the port */
DECL|macro|WHITEHEAT_SETUP_PORT
mdefine_line|#define WHITEHEAT_SETUP_PORT&t;&t;3&t;/* change port settings */
DECL|macro|WHITEHEAT_SET_RTS
mdefine_line|#define WHITEHEAT_SET_RTS&t;&t;4&t;/* turn RTS on or off */
DECL|macro|WHITEHEAT_SET_DTR
mdefine_line|#define WHITEHEAT_SET_DTR&t;&t;5&t;/* turn DTR on or off */
DECL|macro|WHITEHEAT_SET_BREAK
mdefine_line|#define WHITEHEAT_SET_BREAK&t;&t;6&t;/* turn BREAK on or off */
DECL|macro|WHITEHEAT_DUMP
mdefine_line|#define WHITEHEAT_DUMP&t;&t;&t;7&t;/* dump memory */
DECL|macro|WHITEHEAT_STATUS
mdefine_line|#define WHITEHEAT_STATUS&t;&t;8&t;/* get status */
DECL|macro|WHITEHEAT_PURGE
mdefine_line|#define WHITEHEAT_PURGE&t;&t;&t;9&t;/* clear the UART fifos */
DECL|macro|WHITEHEAT_GET_DTR_RTS
mdefine_line|#define WHITEHEAT_GET_DTR_RTS&t;&t;10&t;/* get the state of DTR and RTS for a port */
DECL|macro|WHITEHEAT_GET_HW_INFO
mdefine_line|#define WHITEHEAT_GET_HW_INFO&t;&t;11&t;/* get EEPROM info and hardware ID */
DECL|macro|WHITEHEAT_REPORT_TX_DONE
mdefine_line|#define WHITEHEAT_REPORT_TX_DONE&t;12&t;/* get the next TX done */
DECL|macro|WHITEHEAT_EVENT
mdefine_line|#define WHITEHEAT_EVENT&t;&t;&t;13&t;/* unsolicited status events */
DECL|macro|WHITEHEAT_ECHO
mdefine_line|#define WHITEHEAT_ECHO&t;&t;&t;14&t;/* send data to the indicated IN endpoint */
DECL|macro|WHITEHEAT_DO_TEST
mdefine_line|#define WHITEHEAT_DO_TEST&t;&t;15&t;/* perform the specified test */
DECL|macro|WHITEHEAT_CMD_COMPLETE
mdefine_line|#define WHITEHEAT_CMD_COMPLETE&t;&t;16&t;/* reply for certain commands */
DECL|macro|WHITEHEAT_CMD_FAILURE
mdefine_line|#define WHITEHEAT_CMD_FAILURE&t;&t;17&t;/* reply for failed commands */
multiline_comment|/*&n; * Commands to the firmware&n; */
multiline_comment|/*&n; * WHITEHEAT_OPEN&n; * WHITEHEAT_CLOSE&n; * WHITEHEAT_STATUS&n; * WHITEHEAT_GET_DTR_RTS&n; * WHITEHEAT_REPORT_TX_DONE&n;*/
DECL|struct|whiteheat_simple
r_struct
id|whiteheat_simple
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_SETUP_PORT&n; */
DECL|macro|WHITEHEAT_PAR_NONE
mdefine_line|#define WHITEHEAT_PAR_NONE&t;&squot;n&squot;&t;/* no parity */
DECL|macro|WHITEHEAT_PAR_EVEN
mdefine_line|#define WHITEHEAT_PAR_EVEN&t;&squot;e&squot;&t;/* even parity */
DECL|macro|WHITEHEAT_PAR_ODD
mdefine_line|#define WHITEHEAT_PAR_ODD&t;&squot;o&squot;&t;/* odd parity */
DECL|macro|WHITEHEAT_PAR_SPACE
mdefine_line|#define WHITEHEAT_PAR_SPACE&t;&squot;0&squot;&t;/* space (force 0) parity */
DECL|macro|WHITEHEAT_PAR_MARK
mdefine_line|#define WHITEHEAT_PAR_MARK&t;&squot;1&squot;&t;/* mark (force 1) parity */
DECL|macro|WHITEHEAT_SFLOW_NONE
mdefine_line|#define WHITEHEAT_SFLOW_NONE&t;&squot;n&squot;&t;/* no software flow control */
DECL|macro|WHITEHEAT_SFLOW_RX
mdefine_line|#define WHITEHEAT_SFLOW_RX&t;&squot;r&squot;&t;/* XOFF/ON is sent when RX fills/empties */
DECL|macro|WHITEHEAT_SFLOW_TX
mdefine_line|#define WHITEHEAT_SFLOW_TX&t;&squot;t&squot;&t;/* when received XOFF/ON will stop/start TX */
DECL|macro|WHITEHEAT_SFLOW_RXTX
mdefine_line|#define WHITEHEAT_SFLOW_RXTX&t;&squot;b&squot;&t;/* both SFLOW_RX and SFLOW_TX */
DECL|macro|WHITEHEAT_HFLOW_NONE
mdefine_line|#define WHITEHEAT_HFLOW_NONE&t;&t;0x00&t;/* no hardware flow control */
DECL|macro|WHITEHEAT_HFLOW_RTS_TOGGLE
mdefine_line|#define WHITEHEAT_HFLOW_RTS_TOGGLE&t;0x01&t;/* RTS is on during transmit, off otherwise */
DECL|macro|WHITEHEAT_HFLOW_DTR
mdefine_line|#define WHITEHEAT_HFLOW_DTR&t;&t;0x02&t;/* DTR is off/on when RX fills/empties */
DECL|macro|WHITEHEAT_HFLOW_CTS
mdefine_line|#define WHITEHEAT_HFLOW_CTS&t;&t;0x08&t;/* when received CTS off/on will stop/start TX */
DECL|macro|WHITEHEAT_HFLOW_DSR
mdefine_line|#define WHITEHEAT_HFLOW_DSR&t;&t;0x10&t;/* when received DSR off/on will stop/start TX */
DECL|macro|WHITEHEAT_HFLOW_RTS
mdefine_line|#define WHITEHEAT_HFLOW_RTS&t;&t;0x80&t;/* RTS is off/on when RX fills/empties */
DECL|struct|whiteheat_port_settings
r_struct
id|whiteheat_port_settings
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|baud
id|__u32
id|baud
suffix:semicolon
multiline_comment|/* any value 7 - 460800, firmware calculates best fit; arrives little endian */
DECL|member|bits
id|__u8
id|bits
suffix:semicolon
multiline_comment|/* 5, 6, 7, or 8 */
DECL|member|stop
id|__u8
id|stop
suffix:semicolon
multiline_comment|/* 1 or 2, default 1 (2 = 1.5 if bits = 5) */
DECL|member|parity
id|__u8
id|parity
suffix:semicolon
multiline_comment|/* see WHITEHEAT_PAR_* above */
DECL|member|sflow
id|__u8
id|sflow
suffix:semicolon
multiline_comment|/* see WHITEHEAT_SFLOW_* above */
DECL|member|xoff
id|__u8
id|xoff
suffix:semicolon
multiline_comment|/* XOFF byte value */
DECL|member|xon
id|__u8
id|xon
suffix:semicolon
multiline_comment|/* XON byte value */
DECL|member|hflow
id|__u8
id|hflow
suffix:semicolon
multiline_comment|/* see WHITEHEAT_HFLOW_* above */
DECL|member|lloop
id|__u8
id|lloop
suffix:semicolon
multiline_comment|/* 0/1 turns local loopback mode off/on */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_SET_RTS&n; * WHITEHEAT_SET_DTR&n; * WHITEHEAT_SET_BREAK&n; */
DECL|macro|WHITEHEAT_RTS_OFF
mdefine_line|#define WHITEHEAT_RTS_OFF&t;0x00
DECL|macro|WHITEHEAT_RTS_ON
mdefine_line|#define WHITEHEAT_RTS_ON&t;0x01
DECL|macro|WHITEHEAT_DTR_OFF
mdefine_line|#define WHITEHEAT_DTR_OFF&t;0x00
DECL|macro|WHITEHEAT_DTR_ON
mdefine_line|#define WHITEHEAT_DTR_ON&t;0x01
DECL|macro|WHITEHEAT_BREAK_OFF
mdefine_line|#define WHITEHEAT_BREAK_OFF&t;0x00
DECL|macro|WHITEHEAT_BREAK_ON
mdefine_line|#define WHITEHEAT_BREAK_ON&t;0x01
DECL|struct|whiteheat_set_rdb
r_struct
id|whiteheat_set_rdb
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|state
id|__u8
id|state
suffix:semicolon
multiline_comment|/* 0/1 turns signal off/on */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_DUMP&n; */
DECL|macro|WHITEHEAT_DUMP_MEM_DATA
mdefine_line|#define WHITEHEAT_DUMP_MEM_DATA&t;&t;&squot;d&squot;  /* data */
DECL|macro|WHITEHEAT_DUMP_MEM_IDATA
mdefine_line|#define WHITEHEAT_DUMP_MEM_IDATA&t;&squot;i&squot;  /* idata */
DECL|macro|WHITEHEAT_DUMP_MEM_BDATA
mdefine_line|#define WHITEHEAT_DUMP_MEM_BDATA&t;&squot;b&squot;  /* bdata */
DECL|macro|WHITEHEAT_DUMP_MEM_XDATA
mdefine_line|#define WHITEHEAT_DUMP_MEM_XDATA&t;&squot;x&squot;  /* xdata */
multiline_comment|/*&n; * Allowable address ranges (firmware checks address):&n; * Type DATA:  0x00 - 0xff&n; * Type IDATA: 0x80 - 0xff&n; * Type BDATA: 0x20 - 0x2f&n; * Type XDATA: 0x0000 - 0xffff&n; *&n; * B/I/DATA all read the local memory space&n; * XDATA reads the external memory space&n; * BDATA returns bits as bytes&n; *&n; * NOTE: 0x80 - 0xff (local space) are the Special Function Registers&n; *       of the 8051, and some have on-read side-effects.&n; */
DECL|struct|whiteheat_dump
r_struct
id|whiteheat_dump
(brace
DECL|member|mem_type
id|__u8
id|mem_type
suffix:semicolon
multiline_comment|/* see WHITEHEAT_DUMP_* above */
DECL|member|addr
id|__u16
id|addr
suffix:semicolon
multiline_comment|/* address, see restrictions above */
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* number of bytes to dump, max 63 bytes */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_PURGE&n; */
DECL|macro|WHITEHEAT_PURGE_RX
mdefine_line|#define WHITEHEAT_PURGE_RX&t;0x01&t;/* purge rx fifos */
DECL|macro|WHITEHEAT_PURGE_TX
mdefine_line|#define WHITEHEAT_PURGE_TX&t;0x02&t;/* purge tx fifos */
DECL|struct|whiteheat_purge
r_struct
id|whiteheat_purge
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|what
id|__u8
id|what
suffix:semicolon
multiline_comment|/* bit pattern of what to purge */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_ECHO&n; */
DECL|struct|whiteheat_echo
r_struct
id|whiteheat_echo
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|length
id|__u8
id|length
suffix:semicolon
multiline_comment|/* length of message to echo, max 61 bytes */
DECL|member|echo_data
id|__u8
id|echo_data
(braket
l_int|61
)braket
suffix:semicolon
multiline_comment|/* data to echo */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_DO_TEST&n; */
DECL|macro|WHITEHEAT_TEST_UART_RW
mdefine_line|#define WHITEHEAT_TEST_UART_RW&t;&t;0x01  /* read/write uart registers */
DECL|macro|WHITEHEAT_TEST_UART_INTR
mdefine_line|#define WHITEHEAT_TEST_UART_INTR&t;0x02  /* uart interrupt */
DECL|macro|WHITEHEAT_TEST_SETUP_CONT
mdefine_line|#define WHITEHEAT_TEST_SETUP_CONT&t;0x03  /* setup for PORT_CONT/PORT_DISCONT */
DECL|macro|WHITEHEAT_TEST_PORT_CONT
mdefine_line|#define WHITEHEAT_TEST_PORT_CONT&t;0x04  /* port connect */
DECL|macro|WHITEHEAT_TEST_PORT_DISCONT
mdefine_line|#define WHITEHEAT_TEST_PORT_DISCONT&t;0x05  /* port disconnect */
DECL|macro|WHITEHEAT_TEST_UART_CLK_START
mdefine_line|#define WHITEHEAT_TEST_UART_CLK_START&t;0x06  /* uart clock test start */
DECL|macro|WHITEHEAT_TEST_UART_CLK_STOP
mdefine_line|#define WHITEHEAT_TEST_UART_CLK_STOP&t;0x07  /* uart clock test stop */
DECL|macro|WHITEHEAT_TEST_MODEM_FT
mdefine_line|#define WHITEHEAT_TEST_MODEM_FT&t;&t;0x08  /* modem signals, requires a loopback cable/connector */
DECL|macro|WHITEHEAT_TEST_ERASE_EEPROM
mdefine_line|#define WHITEHEAT_TEST_ERASE_EEPROM&t;0x09  /* erase eeprom */
DECL|macro|WHITEHEAT_TEST_READ_EEPROM
mdefine_line|#define WHITEHEAT_TEST_READ_EEPROM&t;0x0a  /* read eeprom */
DECL|macro|WHITEHEAT_TEST_PROGRAM_EEPROM
mdefine_line|#define WHITEHEAT_TEST_PROGRAM_EEPROM&t;0x0b  /* program eeprom */
DECL|struct|whiteheat_test
r_struct
id|whiteheat_test
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to n) */
DECL|member|test
id|__u8
id|test
suffix:semicolon
multiline_comment|/* see WHITEHEAT_TEST_* above*/
DECL|member|info
id|__u8
id|info
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* additional info */
)brace
suffix:semicolon
multiline_comment|/*&n; * Replies from the firmware&n; */
multiline_comment|/*&n; * WHITEHEAT_STATUS&n; */
DECL|macro|WHITEHEAT_EVENT_MODEM
mdefine_line|#define WHITEHEAT_EVENT_MODEM&t;&t;0x01&t;/* modem field is valid */
DECL|macro|WHITEHEAT_EVENT_ERROR
mdefine_line|#define WHITEHEAT_EVENT_ERROR&t;&t;0x02&t;/* error field is valid */
DECL|macro|WHITEHEAT_EVENT_FLOW
mdefine_line|#define WHITEHEAT_EVENT_FLOW&t;&t;0x04&t;/* flow field is valid */
DECL|macro|WHITEHEAT_EVENT_CONNECT
mdefine_line|#define WHITEHEAT_EVENT_CONNECT&t;&t;0x08&t;/* connect field is valid */
DECL|macro|WHITEHEAT_FLOW_NONE
mdefine_line|#define WHITEHEAT_FLOW_NONE&t;&t;0x00&t;/* no flow control active */
DECL|macro|WHITEHEAT_FLOW_HARD_OUT
mdefine_line|#define WHITEHEAT_FLOW_HARD_OUT&t;&t;0x01&t;/* TX is stopped by CTS (waiting for CTS to go on) */
DECL|macro|WHITEHEAT_FLOW_HARD_IN
mdefine_line|#define WHITEHEAT_FLOW_HARD_IN&t;&t;0x02&t;/* remote TX is stopped by RTS */
DECL|macro|WHITEHEAT_FLOW_SOFT_OUT
mdefine_line|#define WHITEHEAT_FLOW_SOFT_OUT&t;&t;0x04&t;/* TX is stopped by XOFF received (waiting for XON) */
DECL|macro|WHITEHEAT_FLOW_SOFT_IN
mdefine_line|#define WHITEHEAT_FLOW_SOFT_IN&t;&t;0x08&t;/* remote TX is stopped by XOFF transmitted */
DECL|macro|WHITEHEAT_FLOW_TX_DONE
mdefine_line|#define WHITEHEAT_FLOW_TX_DONE&t;&t;0x80&t;/* TX has completed */
DECL|struct|whiteheat_status_info
r_struct
id|whiteheat_status_info
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|event
id|__u8
id|event
suffix:semicolon
multiline_comment|/* indicates what the current event is, see WHITEHEAT_EVENT_* above */
DECL|member|modem
id|__u8
id|modem
suffix:semicolon
multiline_comment|/* modem signal status (copy of uart&squot;s MSR register) */
DECL|member|error
id|__u8
id|error
suffix:semicolon
multiline_comment|/* line status (copy of uart&squot;s LSR register) */
DECL|member|flow
id|__u8
id|flow
suffix:semicolon
multiline_comment|/* flow control state, see WHITEHEAT_FLOW_* above */
DECL|member|connect
id|__u8
id|connect
suffix:semicolon
multiline_comment|/* 0 means not connected, non-zero means connected */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_GET_DTR_RTS&n; */
DECL|struct|whiteheat_dr_info
r_struct
id|whiteheat_dr_info
(brace
DECL|member|mcr
id|__u8
id|mcr
suffix:semicolon
multiline_comment|/* copy of uart&squot;s MCR register */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_GET_HW_INFO&n; */
DECL|struct|whiteheat_hw_info
r_struct
id|whiteheat_hw_info
(brace
DECL|member|hw_id
id|__u8
id|hw_id
suffix:semicolon
multiline_comment|/* hardware id number, WhiteHEAT = 0 */
DECL|member|sw_major_rev
id|__u8
id|sw_major_rev
suffix:semicolon
multiline_comment|/* major version number */
DECL|member|sw_minor_rev
id|__u8
id|sw_minor_rev
suffix:semicolon
multiline_comment|/* minor version number */
DECL|struct|whiteheat_hw_eeprom_info
r_struct
id|whiteheat_hw_eeprom_info
(brace
DECL|member|b0
id|__u8
id|b0
suffix:semicolon
multiline_comment|/* B0 */
DECL|member|vendor_id_low
id|__u8
id|vendor_id_low
suffix:semicolon
multiline_comment|/* vendor id (low byte) */
DECL|member|vendor_id_high
id|__u8
id|vendor_id_high
suffix:semicolon
multiline_comment|/* vendor id (high byte) */
DECL|member|product_id_low
id|__u8
id|product_id_low
suffix:semicolon
multiline_comment|/* product id (low byte) */
DECL|member|product_id_high
id|__u8
id|product_id_high
suffix:semicolon
multiline_comment|/* product id (high byte) */
DECL|member|device_id_low
id|__u8
id|device_id_low
suffix:semicolon
multiline_comment|/* device id (low byte) */
DECL|member|device_id_high
id|__u8
id|device_id_high
suffix:semicolon
multiline_comment|/* device id (high byte) */
DECL|member|not_used_1
id|__u8
id|not_used_1
suffix:semicolon
DECL|member|serial_number_0
id|__u8
id|serial_number_0
suffix:semicolon
multiline_comment|/* serial number (low byte) */
DECL|member|serial_number_1
id|__u8
id|serial_number_1
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|serial_number_2
id|__u8
id|serial_number_2
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|serial_number_3
id|__u8
id|serial_number_3
suffix:semicolon
multiline_comment|/* serial number (high byte) */
DECL|member|not_used_2
id|__u8
id|not_used_2
suffix:semicolon
DECL|member|not_used_3
id|__u8
id|not_used_3
suffix:semicolon
DECL|member|checksum_low
id|__u8
id|checksum_low
suffix:semicolon
multiline_comment|/* checksum (low byte) */
DECL|member|checksum_high
id|__u8
id|checksum_high
suffix:semicolon
multiline_comment|/* checksum (high byte */
DECL|member|hw_eeprom_info
)brace
id|hw_eeprom_info
suffix:semicolon
multiline_comment|/* EEPROM contents */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_EVENT&n; */
DECL|struct|whiteheat_event_info
r_struct
id|whiteheat_event_info
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|event
id|__u8
id|event
suffix:semicolon
multiline_comment|/* see whiteheat_status_info.event */
DECL|member|info
id|__u8
id|info
suffix:semicolon
multiline_comment|/* see whiteheat_status_info.modem, .error, .flow, .connect */
)brace
suffix:semicolon
multiline_comment|/*&n; * WHITEHEAT_DO_TEST&n; */
DECL|macro|WHITEHEAT_TEST_FAIL
mdefine_line|#define WHITEHEAT_TEST_FAIL&t;0x00  /* test failed */
DECL|macro|WHITEHEAT_TEST_UNKNOWN
mdefine_line|#define WHITEHEAT_TEST_UNKNOWN&t;0x01  /* unknown test requested */
DECL|macro|WHITEHEAT_TEST_PASS
mdefine_line|#define WHITEHEAT_TEST_PASS&t;0xff  /* test passed */
DECL|struct|whiteheat_test_info
r_struct
id|whiteheat_test_info
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
DECL|member|test
id|__u8
id|test
suffix:semicolon
multiline_comment|/* indicates which test this is a response for, see WHITEHEAT_DO_TEST above */
DECL|member|status
id|__u8
id|status
suffix:semicolon
multiline_comment|/* see WHITEHEAT_TEST_* above */
DECL|member|results
id|__u8
id|results
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* test-dependent results */
)brace
suffix:semicolon
macro_line|#endif
eof
