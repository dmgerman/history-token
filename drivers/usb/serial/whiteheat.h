multiline_comment|/*&n; * USB ConnectTech WhiteHEAT driver&n; *&n; *      Copyright (C) 1999, 2000&n; *          Greg Kroah-Hartman (greg@kroah.com)&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; * See Documentation/usb/usb-serial.txt for more information on using this driver&n; *&n; */
macro_line|#ifndef __LINUX_USB_SERIAL_WHITEHEAT_H
DECL|macro|__LINUX_USB_SERIAL_WHITEHEAT_H
mdefine_line|#define __LINUX_USB_SERIAL_WHITEHEAT_H
DECL|macro|FALSE
mdefine_line|#define FALSE&t;&t;&t;&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;&t;&t;&t;1
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
multiline_comment|/* Data for the WHITEHEAT_SETUP_PORT command */
DECL|macro|WHITEHEAT_CTS_FLOW
mdefine_line|#define WHITEHEAT_CTS_FLOW&t;&t;0x08
DECL|macro|WHITEHEAT_RTS_FLOW
mdefine_line|#define WHITEHEAT_RTS_FLOW&t;&t;0x80
DECL|macro|WHITEHEAT_DSR_FLOW
mdefine_line|#define WHITEHEAT_DSR_FLOW&t;&t;0x10
DECL|macro|WHITEHEAT_DTR_FLOW
mdefine_line|#define WHITEHEAT_DTR_FLOW&t;&t;0x02
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
multiline_comment|/* any value allowed, default 9600, arrives little endian, range is 7 - 460800 */
DECL|member|bits
id|__u8
id|bits
suffix:semicolon
multiline_comment|/* 5, 6, 7, or 8, default 8 */
DECL|member|stop
id|__u8
id|stop
suffix:semicolon
multiline_comment|/* 1 or 2, default 1 (2 = 1.5 if bits = 5) */
DECL|member|parity
id|__u8
id|parity
suffix:semicolon
multiline_comment|/* &squot;n, e, o, 0, or 1&squot; (ascii), default &squot;n&squot;&n;&t;&t;&t;&t; *&t;n = none&t;e = even&t;o = odd&n;&t;&t;&t;&t; *&t;0 = force 0&t;1 = force 1&t;*/
DECL|member|sflow
id|__u8
id|sflow
suffix:semicolon
multiline_comment|/* &squot;n, r, t, or b&squot; (ascii), default &squot;n&squot;&n;&t;&t;&t;&t; *&t;n = none&n;&t;&t;&t;&t; *&t;r = receive (XOFF/XON transmitted when receiver fills / empties)&n;&t;&t;&t;&t; *&t;t = transmit (XOFF/XON received will stop/start TX)&n;&t;&t;&t;&t; *&t;b = both &t;*/
DECL|member|xoff
id|__u8
id|xoff
suffix:semicolon
multiline_comment|/* XOFF byte value, default 0x13 */
DECL|member|xon
id|__u8
id|xon
suffix:semicolon
multiline_comment|/* XON byte value, default 0x11 */
DECL|member|hflow
id|__u8
id|hflow
suffix:semicolon
multiline_comment|/* bits indicate mode as follows:&n;&t;&t;&t;&t; *&t;CTS (0x08) (CTS off/on will control/cause TX off/on)&n;&t;&t;&t;&t; *&t;DSR (0x10) (DSR off/on will control/cause TX off/on)&n;&t;&t;&t;&t; *&t;RTS (0x80) (RTS off/on when receiver fills/empties)&n;&t;&t;&t;&t; *&t;DTR (0x02) (DTR off/on when receiver fills/empties) */
DECL|member|lloop
id|__u8
id|lloop
suffix:semicolon
multiline_comment|/* local loopback 0 or 1, default 0 */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* data for WHITEHEAT_SET_RTS, WHITEHEAT_SET_DTR, and WHITEHEAT_SET_BREAK commands */
DECL|struct|whiteheat_rdb_set
r_struct
id|whiteheat_rdb_set
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
multiline_comment|/* 0 = off, non-zero = on */
)brace
suffix:semicolon
multiline_comment|/* data for:&n;&t;WHITEHEAT_OPEN&n;&t;WHITEHEAT_CLOSE&n;&t;WHITEHEAT_STATUS&n;&t;WHITEHEAT_GET_DTR_RTS&n;&t;WHITEHEAT_REPORT_TX_DONE */
DECL|struct|whiteheat_min_set
r_struct
id|whiteheat_min_set
(brace
DECL|member|port
id|__u8
id|port
suffix:semicolon
multiline_comment|/* port number (1 to N) */
)brace
suffix:semicolon
multiline_comment|/* data for WHITEHEAT_PURGE command */
DECL|macro|WHITEHEAT_PURGE_INPUT
mdefine_line|#define WHITEHEAT_PURGE_INPUT&t;&t;0x01
DECL|macro|WHITEHEAT_PURGE_OUTPUT
mdefine_line|#define WHITEHEAT_PURGE_OUTPUT&t;&t;0x02
DECL|struct|whiteheat_purge_set
r_struct
id|whiteheat_purge_set
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
multiline_comment|/* data for WHITEHEAT_DUMP command */
DECL|struct|whiteheat_dump_info
r_struct
id|whiteheat_dump_info
(brace
DECL|member|mem_type
id|__u8
id|mem_type
suffix:semicolon
multiline_comment|/* memory type: &squot;d&squot; = data, &squot;i&squot; = idata, &squot;b&squot; = bdata, &squot;x&squot; = xdata */
DECL|member|addr
id|__u16
id|addr
suffix:semicolon
multiline_comment|/* memory address to dump, address range depends on the above mem_type:&n;&t;&t;&t;&t; *&t;&squot;d&squot; = 0 to ff (80 to FF is SFR&squot;s)&n;&t;&t;&t;&t; *&t;&squot;i&squot; = 80 to ff&n;&t;&t;&t;&t; *&t;&squot;b&squot; = 20 to 2f (bits returned as bytes)&n;&t;&t;&t;&t; *&t;&squot;x&squot; = 0000 to ffff (also code space)&t;*/
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* number of bytes to dump, max 64 */
)brace
suffix:semicolon
multiline_comment|/* data for WHITEHEAT_ECHO command */
DECL|struct|whiteheat_echo_set
r_struct
id|whiteheat_echo_set
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
multiline_comment|/* length of message to echo */
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
multiline_comment|/* data returned from WHITEHEAT_STATUS command */
DECL|macro|WHITEHEAT_OVERRUN_ERROR
mdefine_line|#define WHITEHEAT_OVERRUN_ERROR&t;&t;0x02
DECL|macro|WHITEHEAT_PARITY_ERROR
mdefine_line|#define WHITEHEAT_PARITY_ERROR&t;&t;0x04
DECL|macro|WHITEHEAT_FRAMING_ERROR
mdefine_line|#define WHITEHEAT_FRAMING_ERROR&t;&t;0x08
DECL|macro|WHITEHEAT_BREAK_ERROR
mdefine_line|#define WHITEHEAT_BREAK_ERROR&t;&t;0x10
DECL|macro|WHITEHEAT_OHFLOW
mdefine_line|#define WHITEHEAT_OHFLOW&t;&t;0x01&t;/* TX is stopped by CTS (waiting for CTS to go ON) */
DECL|macro|WHITEHEAT_IHFLOW
mdefine_line|#define WHITEHEAT_IHFLOW&t;&t;0x02&t;/* remote TX is stopped by RTS */
DECL|macro|WHITEHEAT_OSFLOW
mdefine_line|#define WHITEHEAT_OSFLOW&t;&t;0x04&t;/* TX is stopped by XOFF received (waiting for XON to occur) */
DECL|macro|WHITEHEAT_ISFLOW
mdefine_line|#define WHITEHEAT_ISFLOW&t;&t;0x08&t;/* remote TX is stopped by XOFF transmitted */
DECL|macro|WHITEHEAT_TX_DONE
mdefine_line|#define WHITEHEAT_TX_DONE&t;&t;0x80&t;/* TX has completed */
DECL|macro|WHITEHEAT_MODEM_EVENT
mdefine_line|#define WHITEHEAT_MODEM_EVENT&t;&t;0x01
DECL|macro|WHITEHEAT_ERROR_EVENT
mdefine_line|#define WHITEHEAT_ERROR_EVENT&t;&t;0x02
DECL|macro|WHITEHEAT_FLOW_EVENT
mdefine_line|#define WHITEHEAT_FLOW_EVENT&t;&t;0x04
DECL|macro|WHITEHEAT_CONNECT_EVENT
mdefine_line|#define WHITEHEAT_CONNECT_EVENT&t;&t;0x08
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
multiline_comment|/* indicates which of the following bytes are the current event */
DECL|member|modem
id|__u8
id|modem
suffix:semicolon
multiline_comment|/* modem signal status (copy of UART MSR register) */
DECL|member|error
id|__u8
id|error
suffix:semicolon
multiline_comment|/* PFO and RX break (copy of UART LSR register) */
DECL|member|flow
id|__u8
id|flow
suffix:semicolon
multiline_comment|/* flow control state */
DECL|member|connect
id|__u8
id|connect
suffix:semicolon
multiline_comment|/* connect state, non-zero value indicates connected */
)brace
suffix:semicolon
multiline_comment|/* data returned from WHITEHEAT_EVENT command */
DECL|struct|whiteheat_event
r_struct
id|whiteheat_event
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
multiline_comment|/* indicates which of the following bytes are the current event */
DECL|member|info
id|__u8
id|info
suffix:semicolon
multiline_comment|/* either modem, error, flow, or connect information */
)brace
suffix:semicolon
multiline_comment|/* data retured by the WHITEHEAT_GET_HW_INFO command */
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
macro_line|#endif
eof
