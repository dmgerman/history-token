multiline_comment|/************************************************************************&n; *&n; *&t;IONSP.H&t;&t;Definitions for I/O Networks Serial Protocol&n; *&n; *&t;Copyright (c) 1997-1998 Inside Out Networks, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;These definitions are used by both kernel-mode driver and the&n; *&t;peripheral firmware and MUST be kept in sync.&n; *&n; ************************************************************************/
multiline_comment|/************************************************************************&n;&n;The data to and from all ports on the peripheral is multiplexed&n;through a single endpoint pair (EP1 since it supports 64-byte&n;MaxPacketSize). Therefore, the data, commands, and status for&n;each port must be preceeded by a short header identifying the&n;destination port. The header also identifies the bytes that follow&n;as data or as command/status info.&n;&n;Header format, first byte:&n;&n;    CLLLLPPP&n;    --------&n;    | |&t; |------ Port Number:&t;0-7&n;    | |--------- Length:&t;MSB bits of length&n;    |----------- Data/Command:&t;0 = Data header&n;&t;&t;&t;&t;1 = Cmd / Status (Cmd if OUT, Status if IN)&n;&n;This gives 2 possible formats:&n;&n;&n;    Data header:&t;&t;0LLLLPPP&t;LLLLLLLL&n;    ============&n;&n;    Where (LLLL,LLLLLLL) is 12-bit length of data that follows for&n;    port number (PPP). The length is 0-based (0-FFF means 0-4095&n;    bytes). The ~4K limit allows the host driver (which deals in&n;    transfer requests instead of individual packets) to write a&n;    large chunk of data in a single request. Note, however, that&n;    the length must always be &lt;= the current TxCredits for a given&n;    port due to buffering limitations on the peripheral.&n;&n;&n;    Cmd/Status header:&t;&t;1ccccPPP&t;[ CCCCCCCC,&t; Params ]...&n;    ==================&n;&n;    Where (cccc) or (cccc,CCCCCCCC) is the cmd or status identifier.&n;    Frequently-used values are encoded as (cccc), longer ones using&n;    (cccc,CCCCCCCC). Subsequent bytes are optional parameters and are&n;    specific to the cmd or status code. This may include a length&n;    for command and status codes that need variable-length parameters.&n;&n;&n;In addition, we use another interrupt pipe (endpoint) which the host polls&n;periodically for flow control information. The peripheral, when there has&n;been a change, sends the following 10-byte packet:&n;&n;&t;RRRRRRRRRRRRRRRR&n;&t;T0T0T0T0T0T0T0T0&n;&t;T1T1T1T1T1T1T1T1&n;&t;T2T2T2T2T2T2T2T2&n;&t;T3T3T3T3T3T3T3T3&n;&n;The first field is the 16-bit RxBytesAvail field, which indicates the&n;number of bytes which may be read by the host from EP1. This is necessary:&n;(a) because OSR2.1 has a bug which causes data loss if the peripheral returns&n;fewer bytes than the host expects to read, and (b) because, on Microsoft&n;platforms at least, an outstanding read posted on EP1 consumes about 35% of&n;the CPU just polling the device for data.&n;&n;The next 4 fields are the 16-bit TxCredits for each port, which indicate how&n;many bytes the host is allowed to send on EP1 for transmit to a given port.&n;After an OPEN_PORT command, the Edgeport sends the initial TxCredits for that&n;port.&n;&n;All 16-bit fields are sent in little-endian (Intel) format.&n;&n;************************************************************************/
singleline_comment|//
singleline_comment|// Define format of InterruptStatus packet returned from the
singleline_comment|// Interrupt pipe
singleline_comment|//
DECL|struct|_INT_STATUS_PKT
r_typedef
r_struct
id|_INT_STATUS_PKT
(brace
DECL|member|RxBytesAvail
id|__u16
id|RxBytesAvail
suffix:semicolon
singleline_comment|// Additional bytes available to
singleline_comment|// be read from Bulk IN pipe
DECL|member|TxCredits
id|__u16
id|TxCredits
(braket
id|MAX_RS232_PORTS
)braket
suffix:semicolon
singleline_comment|// Additional space available in
singleline_comment|// given port&squot;s TxBuffer
DECL|typedef|INT_STATUS_PKT
DECL|typedef|PINT_STATUS_PKT
)brace
id|INT_STATUS_PKT
comma
op_star
id|PINT_STATUS_PKT
suffix:semicolon
DECL|macro|GET_INT_STATUS_SIZE
mdefine_line|#define GET_INT_STATUS_SIZE(NumPorts) (sizeof(__u16) + (sizeof(__u16) * (NumPorts)))
singleline_comment|//
singleline_comment|// Define cmd/status header values and macros to extract them.
singleline_comment|//
singleline_comment|//&t;Data:&t;&t;0LLLLPPP LLLLLLLL
singleline_comment|//&t;Cmd/Stat:&t;1ccccPPP CCCCCCCC
DECL|macro|IOSP_DATA_HDR_SIZE
mdefine_line|#define&t;IOSP_DATA_HDR_SIZE&t;&t;2
DECL|macro|IOSP_CMD_HDR_SIZE
mdefine_line|#define&t;IOSP_CMD_HDR_SIZE&t;&t;2
DECL|macro|IOSP_MAX_DATA_LENGTH
mdefine_line|#define&t;IOSP_MAX_DATA_LENGTH&t;&t;0x0FFF&t;&t;
singleline_comment|// 12 bits -&gt; 4K
DECL|macro|IOSP_PORT_MASK
mdefine_line|#define&t;IOSP_PORT_MASK&t;&t;&t;0x07&t;&t;
singleline_comment|// Mask to isolate port number
DECL|macro|IOSP_CMD_STAT_BIT
mdefine_line|#define&t;IOSP_CMD_STAT_BIT&t;&t;0x80&t;&t;
singleline_comment|// If set, this is command/status header
DECL|macro|IS_CMD_STAT_HDR
mdefine_line|#define IS_CMD_STAT_HDR(Byte1)&t;&t;((Byte1) &amp; IOSP_CMD_STAT_BIT)
DECL|macro|IS_DATA_HDR
mdefine_line|#define IS_DATA_HDR(Byte1)&t;&t;(! IS_CMD_STAT_HDR(Byte1))
DECL|macro|IOSP_GET_HDR_PORT
mdefine_line|#define&t;IOSP_GET_HDR_PORT(Byte1)&t;&t;((__u8) ((Byte1) &amp; IOSP_PORT_MASK))
DECL|macro|IOSP_GET_HDR_DATA_LEN
mdefine_line|#define&t;IOSP_GET_HDR_DATA_LEN(Byte1, Byte2)&t;((__u16) ( ((__u16)((Byte1) &amp; 0x78)) &lt;&lt; 5) | (Byte2))
DECL|macro|IOSP_GET_STATUS_CODE
mdefine_line|#define&t;IOSP_GET_STATUS_CODE(Byte1)&t;&t;((__u8) (((Byte1) &amp;  0x78) &gt;&gt; 3))
singleline_comment|//
singleline_comment|// These macros build the 1st and 2nd bytes for a data header
singleline_comment|//
DECL|macro|IOSP_BUILD_DATA_HDR1
mdefine_line|#define&t;IOSP_BUILD_DATA_HDR1(Port, Len)&t;&t;((__u8) (((Port) | ((__u8) (((__u16) (Len)) &gt;&gt; 5) &amp; 0x78 ))))
DECL|macro|IOSP_BUILD_DATA_HDR2
mdefine_line|#define&t;IOSP_BUILD_DATA_HDR2(Port, Len)&t;&t;((__u8) (Len))
singleline_comment|//
singleline_comment|// These macros build the 1st and 2nd bytes for a command header
singleline_comment|//
DECL|macro|IOSP_BUILD_CMD_HDR1
mdefine_line|#define&t;IOSP_BUILD_CMD_HDR1(Port, Cmd)&t;&t;((__u8) ( IOSP_CMD_STAT_BIT | (Port) |&t;((__u8) ((Cmd) &lt;&lt; 3)) ))
singleline_comment|//--------------------------------------------------------------
singleline_comment|//
singleline_comment|//&t;Define values for commands and command parameters
singleline_comment|//&t;(sent from Host to Edgeport)
singleline_comment|//
singleline_comment|//&t;1ccccPPP P1P1P1P1 [ P2P2P2P2P2 ]...
singleline_comment|//
singleline_comment|//&t;cccc:&t;00-07&t;2-byte commands. Write UART register 0-7 with
singleline_comment|//&t;&t;&t;&t;&t;value in P1. See 16650.H for definitions of
singleline_comment|//&t;&t;&t;&t;&t;UART register numbers and contents.
singleline_comment|//
singleline_comment|//&t;&t;08-0B&t;3-byte commands:&t;&t;&t;&t;&t;==== P1 ====&t;==== P2 ====
singleline_comment|//&t;&t;&t;&t;&t;08&t;available for expansion
singleline_comment|//&t;&t;&t;&t;&t;09&t;1-param commands&t;&t;Command Code&t;Param
singleline_comment|//&t;&t;&t;&t;&t;0A&t;available for expansion
singleline_comment|//&t;&t;&t;&t;&t;0B&t;available for expansion
singleline_comment|//
singleline_comment|//&t;&t;0C-0D&t;4-byte commands.&t;P1 = extended cmd and P2,P3 = params
singleline_comment|//&t;&t;&t;&t;&t;&t;Currently unimplemented.
singleline_comment|//
singleline_comment|//&t;&t;0E-0F&t;N-byte commands:&t;P1 = num bytes after P1 (ie, TotalLen - 2)
singleline_comment|//&t;&t;&t;&t;&t;&t;P2 = extended cmd, P3..Pn = parameters.
singleline_comment|//&t;&t;&t;&t;&t;&t;Currently unimplemented.
singleline_comment|//
DECL|macro|IOSP_WRITE_UART_REG
mdefine_line|#define&t;IOSP_WRITE_UART_REG(n)&t;((n) &amp; 0x07)&t;
singleline_comment|// UartReg[ n ] := P1
singleline_comment|// Register numbers and contents
singleline_comment|// defined in 16554.H.
singleline_comment|//&t;&t;&t;&t;&t;0x08&t;&t;// Available for expansion.
DECL|macro|IOSP_EXT_CMD
mdefine_line|#define&t;IOSP_EXT_CMD&t;&t;&t;0x09&t;&t;
singleline_comment|// P1 = Command code (defined below)
singleline_comment|// P2 = Parameter
singleline_comment|//
singleline_comment|// Extended Command values, used with IOSP_EXT_CMD, may
singleline_comment|// or may not use parameter P2.
singleline_comment|//
DECL|macro|IOSP_CMD_OPEN_PORT
mdefine_line|#define&t;IOSP_CMD_OPEN_PORT&t;&t;0x00&t;&t;
singleline_comment|// Enable ints, init UART. (NO PARAM)
DECL|macro|IOSP_CMD_CLOSE_PORT
mdefine_line|#define&t;IOSP_CMD_CLOSE_PORT&t;&t;0x01&t;&t;
singleline_comment|// Disable ints, flush buffers. (NO PARAM)
DECL|macro|IOSP_CMD_CHASE_PORT
mdefine_line|#define&t;IOSP_CMD_CHASE_PORT&t;&t;0x02&t;&t;
singleline_comment|// Wait for Edgeport TX buffers to empty. (NO PARAM)
DECL|macro|IOSP_CMD_SET_RX_FLOW
mdefine_line|#define IOSP_CMD_SET_RX_FLOW&t;&t;0x03&t;&t;
singleline_comment|// Set Rx Flow Control in Edgeport
DECL|macro|IOSP_CMD_SET_TX_FLOW
mdefine_line|#define IOSP_CMD_SET_TX_FLOW&t;&t;0x04&t;&t;
singleline_comment|// Set Tx Flow Control in Edgeport
DECL|macro|IOSP_CMD_SET_XON_CHAR
mdefine_line|#define IOSP_CMD_SET_XON_CHAR&t;&t;0x05&t;&t;
singleline_comment|// Set XON Character in Edgeport
DECL|macro|IOSP_CMD_SET_XOFF_CHAR
mdefine_line|#define IOSP_CMD_SET_XOFF_CHAR&t;&t;0x06&t;&t;
singleline_comment|// Set XOFF Character in Edgeport
DECL|macro|IOSP_CMD_RX_CHECK_REQ
mdefine_line|#define IOSP_CMD_RX_CHECK_REQ&t;&t;0x07&t;&t;
singleline_comment|// Request Edgeport to insert a Checkpoint into
singleline_comment|// the receive data stream (Parameter = 1 byte sequence number)
DECL|macro|IOSP_CMD_SET_BREAK
mdefine_line|#define IOSP_CMD_SET_BREAK&t;&t;0x08&t;&t;
singleline_comment|// Turn on the BREAK (LCR bit 6)
DECL|macro|IOSP_CMD_CLEAR_BREAK
mdefine_line|#define IOSP_CMD_CLEAR_BREAK&t;&t;0x09&t;&t;
singleline_comment|// Turn off the BREAK (LCR bit 6)
singleline_comment|//
singleline_comment|// Define macros to simplify building of IOSP cmds
singleline_comment|//
DECL|macro|MAKE_CMD_WRITE_REG
mdefine_line|#define&t;MAKE_CMD_WRITE_REG(ppBuf, pLen, Port, Reg, Val)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(*(ppBuf))[0] = IOSP_BUILD_CMD_HDR1( (Port), IOSP_WRITE_UART_REG(Reg) );&t;&bslash;&n;&t;&t;(*(ppBuf))[1] = (Val);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*ppBuf += 2;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*pLen  += 2;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|MAKE_CMD_EXT_CMD
mdefine_line|#define&t;MAKE_CMD_EXT_CMD(ppBuf, pLen, Port, ExtCmd, Param)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(*(ppBuf))[0] = IOSP_BUILD_CMD_HDR1( (Port), IOSP_EXT_CMD );&t;&t;&t;&bslash;&n;&t;&t;(*(ppBuf))[1] = (ExtCmd);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(*(ppBuf))[2] = (Param);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*ppBuf += 3;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*pLen  += 3;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
singleline_comment|//--------------------------------------------------------------
singleline_comment|//
singleline_comment|//&t;Define format of flow control commands
singleline_comment|//&t;(sent from Host to Edgeport)
singleline_comment|//
singleline_comment|//&t;11001PPP FlowCmd FlowTypes
singleline_comment|//
singleline_comment|//&t;Note that the &squot;FlowTypes&squot; parameter is a bit mask; that is,
singleline_comment|//&t;more than one flow control type can be active at the same time.
singleline_comment|//&t;FlowTypes = 0 means &squot;no flow control&squot;.
singleline_comment|//
singleline_comment|//
singleline_comment|//&t;IOSP_CMD_SET_RX_FLOW
singleline_comment|//
singleline_comment|//&t;Tells Edgeport how it can stop incoming UART data
singleline_comment|//
singleline_comment|//  Example for Port 0
singleline_comment|//&t;P0 = 11001000
singleline_comment|//  P1 = IOSP_CMD_SET_RX_FLOW
singleline_comment|//  P2 = Bit mask as follows:
DECL|macro|IOSP_RX_FLOW_RTS
mdefine_line|#define IOSP_RX_FLOW_RTS&t;&t;0x01&t;
singleline_comment|// Edgeport drops RTS to stop incoming data
DECL|macro|IOSP_RX_FLOW_DTR
mdefine_line|#define IOSP_RX_FLOW_DTR&t;&t;0x02&t;
singleline_comment|// Edgeport drops DTR to stop incoming data
DECL|macro|IOSP_RX_FLOW_DSR_SENSITIVITY
mdefine_line|#define IOSP_RX_FLOW_DSR_SENSITIVITY&t;0x04&t;
singleline_comment|// Ignores Rx data unless DSR high
singleline_comment|// Not currently implemented by firmware.
DECL|macro|IOSP_RX_FLOW_XON_XOFF
mdefine_line|#define IOSP_RX_FLOW_XON_XOFF&t;&t;0x08&t;
singleline_comment|// Edgeport sends XOFF char to stop incoming data.
singleline_comment|// Host must have previously programmed the
singleline_comment|// XON/XOFF values with SET_XON/SET_XOFF
singleline_comment|// before enabling this bit.
singleline_comment|//
singleline_comment|//&t;IOSP_CMD_SET_TX_FLOW
singleline_comment|//
singleline_comment|//&t;Tells Edgeport what signal(s) will stop it from transmitting UART data
singleline_comment|//
singleline_comment|//  Example for Port 0
singleline_comment|//&t;P0 = 11001000
singleline_comment|//  P1 = IOSP_CMD_SET_TX_FLOW
singleline_comment|//  P2 = Bit mask as follows:
DECL|macro|IOSP_TX_FLOW_CTS
mdefine_line|#define IOSP_TX_FLOW_CTS&t;&t;0x01&t;
singleline_comment|// Edgeport stops Tx if CTS low
DECL|macro|IOSP_TX_FLOW_DSR
mdefine_line|#define IOSP_TX_FLOW_DSR&t;&t;0x02&t;
singleline_comment|// Edgeport stops Tx if DSR low
DECL|macro|IOSP_TX_FLOW_DCD
mdefine_line|#define IOSP_TX_FLOW_DCD&t;&t;0x04&t;
singleline_comment|// Edgeport stops Tx if DCD low
DECL|macro|IOSP_TX_FLOW_XON_XOFF
mdefine_line|#define IOSP_TX_FLOW_XON_XOFF&t;&t;0x08&t;
singleline_comment|// Edgeport stops Tx upon receiving XOFF char.
singleline_comment|// Host must have previously programmed the
singleline_comment|// XON/XOFF values with SET_XON/SET_XOFF
singleline_comment|// before enabling this bit.
DECL|macro|IOSP_TX_FLOW_XOFF_CONTINUE
mdefine_line|#define IOSP_TX_FLOW_XOFF_CONTINUE&t;0x10&t;
singleline_comment|// If not set, Edgeport stops Tx when
singleline_comment|// sending XOFF in order to fix broken
singleline_comment|// systems that interpret the next
singleline_comment|// received char as XON.
singleline_comment|// If set, Edgeport continues Tx
singleline_comment|// normally after transmitting XOFF.
singleline_comment|// Not currently implemented by firmware.
DECL|macro|IOSP_TX_TOGGLE_RTS
mdefine_line|#define IOSP_TX_TOGGLE_RTS&t;&t;0x20&t;
singleline_comment|// Edgeport drives RTS as a true half-duplex
singleline_comment|// Request-to-Send signal: it is raised before
singleline_comment|// beginning transmission and lowered after
singleline_comment|// the last Tx char leaves the UART.
singleline_comment|// Not currently implemented by firmware.
singleline_comment|//
singleline_comment|//&t;IOSP_CMD_SET_XON_CHAR
singleline_comment|//
singleline_comment|//&t;Sets the character which Edgeport transmits/interprets as XON.
singleline_comment|//&t;Note: This command MUST be sent before sending a SET_RX_FLOW or
singleline_comment|//&t;SET_TX_FLOW with the XON_XOFF bit set.
singleline_comment|//
singleline_comment|//  Example for Port 0
singleline_comment|//&t;P0 = 11001000
singleline_comment|//  P1 = IOSP_CMD_SET_XON_CHAR
singleline_comment|//  P2 = 0x11
singleline_comment|//
singleline_comment|//&t;IOSP_CMD_SET_XOFF_CHAR
singleline_comment|//
singleline_comment|//&t;Sets the character which Edgeport transmits/interprets as XOFF.
singleline_comment|//&t;Note: This command must be sent before sending a SET_RX_FLOW or
singleline_comment|//&t;SET_TX_FLOW with the XON_XOFF bit set.
singleline_comment|//
singleline_comment|//  Example for Port 0
singleline_comment|//&t;P0 = 11001000
singleline_comment|//  P1 = IOSP_CMD_SET_XOFF_CHAR
singleline_comment|//  P2 = 0x13
singleline_comment|//
singleline_comment|//&t;IOSP_CMD_RX_CHECK_REQ
singleline_comment|//
singleline_comment|//  This command is used to assist in the implementation of the 
singleline_comment|//  IOCTL_SERIAL_PURGE Windows IOCTL.  
singleline_comment|//  This IOSP command tries to place a marker at the end of the RX 
singleline_comment|//  queue in the Edgeport. If the Edgeport RX queue is full then 
singleline_comment|//  the Check will be discarded.  
singleline_comment|//  It is up to the device driver to timeout waiting for the 
singleline_comment|//  RX_CHECK_RSP.  If a RX_CHECK_RSP is received, the driver is 
singleline_comment|//&t;sure that all data has been received from the edgeport and 
singleline_comment|//&t;may now purge any internal RX buffers.
singleline_comment|//  Note tat the sequence numbers may be used to detect lost 
singleline_comment|//  CHECK_REQs.
singleline_comment|//  Example for Port 0
singleline_comment|//&t;P0 = 11001000
singleline_comment|//  P1 = IOSP_CMD_RX_CHECK_REQ
singleline_comment|//  P2 = Sequence number
singleline_comment|//  Response will be:
singleline_comment|//  P1 = IOSP_EXT_RX_CHECK_RSP
singleline_comment|//  P2 = Request Sequence number
singleline_comment|//--------------------------------------------------------------
singleline_comment|//
singleline_comment|//&t;Define values for status and status parameters
singleline_comment|//&t;(received by Host from Edgeport)
singleline_comment|//
singleline_comment|//&t;1ssssPPP P1P1P1P1 [ P2P2P2P2P2 ]...
singleline_comment|//
singleline_comment|// &t;ssss:&t;00-07&t;2-byte status.&t;ssss identifies which UART register
singleline_comment|//&t;&t;&t;&t;&t;has changed value, and the new value is in P1.
singleline_comment|//&t;&t;&t;&t;&t;Note that the ssss values do not correspond to the
singleline_comment|//&t;&t;&t;&t;&t;16554 register numbers given in 16554.H. Instead,
singleline_comment|//&t;&t;&t;&t;&t;see below for definitions of the ssss numbers
singleline_comment|//&t;&t;&t;&t;&t;used in this status message.
singleline_comment|//
singleline_comment|//&t;&t;08-0B&t;3-byte status:&t;&t;&t;&t;&t;==== P1 ====&t;==== P2 ====
singleline_comment|//&t;&t;&t;&t;&t;08&t;LSR_DATA:&t;&t;New LSR&t;&t;Errored byte
singleline_comment|//&t;&t;&t;&t;&t;09&t;1-param responses&t;Response Code&t;Param
singleline_comment|//&t;&t;&t;&t;&t;0A&t;OPEN_RSP:&t;&t;InitialMsr&t;TxBufferSize
singleline_comment|//&t;&t;&t;&t;&t;0B&t;available for expansion
singleline_comment|//
singleline_comment|//&t;&t;0C-0D&t;4-byte status.&t;P1 = extended status code and P2,P3 = params
singleline_comment|//&t;&t;&t;&t;&t;Not currently implemented.
singleline_comment|//
singleline_comment|//&t;&t;0E-0F&t;N-byte status:&t;P1 = num bytes after P1 (ie, TotalLen - 2)
singleline_comment|//&t;&t;&t;&t;&t;P2 = extended status, P3..Pn = parameters.
singleline_comment|//&t;&t;&t;&t;&t;Not currently implemented.
singleline_comment|//
multiline_comment|/****************************************************&n; *&t;SSSS values for 2-byte status messages (0-8)&n; ****************************************************/
DECL|macro|IOSP_STATUS_LSR
mdefine_line|#define&t;IOSP_STATUS_LSR&t;&t;&t;0x00&t;
singleline_comment|// P1 is new value of LSR register.
singleline_comment|// Bits defined in 16554.H. Edgeport
singleline_comment|// returns this in order to report
singleline_comment|// line status errors (overrun,
singleline_comment|// parity, framing, break). This form
singleline_comment|// is used when a errored receive data
singleline_comment|// character was NOT present in the
singleline_comment|// UART when the LSR error occurred
singleline_comment|// (ie, when LSR bit 0 = 0).
DECL|macro|IOSP_STATUS_MSR
mdefine_line|#define&t;IOSP_STATUS_MSR&t;&t;&t;0x01&t;
singleline_comment|// P1 is new value of MSR register.
singleline_comment|// Bits defined in 16554.H. Edgeport
singleline_comment|// returns this in order to report
singleline_comment|// changes in modem status lines
singleline_comment|// (CTS, DSR, RI, CD)
singleline_comment|// 
singleline_comment|//&t;&t;&t;&t;&t;0x02&t;// Available for future expansion
singleline_comment|//&t;&t;&t;&t;&t;0x03&t;// 
singleline_comment|//&t;&t;&t;&t;&t;0x04&t;// 
singleline_comment|//&t;&t;&t;&t;&t;0x05&t;// 
singleline_comment|//&t;&t;&t;&t;&t;0x06&t;// 
singleline_comment|//&t;&t;&t;&t;&t;0x07&t;// 
multiline_comment|/****************************************************&n; *&t;SSSS values for 3-byte status messages (8-A)&n; ****************************************************/
DECL|macro|IOSP_STATUS_LSR_DATA
mdefine_line|#define&t;IOSP_STATUS_LSR_DATA&t;&t;0x08&t;
singleline_comment|// P1 is new value of LSR register (same as STATUS_LSR)
singleline_comment|// P2 is errored character read from
singleline_comment|//    RxFIFO after LSR reported an error.&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;
DECL|macro|IOSP_EXT_STATUS
mdefine_line|#define&t;IOSP_EXT_STATUS&t;&t;&t;0x09&t;
singleline_comment|// P1 is status/response code, param in P2.
singleline_comment|// Response Codes (P1 values) for 3-byte status messages
DECL|macro|IOSP_EXT_STATUS_CHASE_RSP
mdefine_line|#define&t;IOSP_EXT_STATUS_CHASE_RSP&t;0&t;
singleline_comment|// Reply to CHASE_PORT cmd. P2 is outcome:
DECL|macro|IOSP_EXT_STATUS_CHASE_PASS
mdefine_line|#define&t;IOSP_EXT_STATUS_CHASE_PASS&t;0&t;
singleline_comment|// &t;P2 = 0: All Tx data drained successfully
DECL|macro|IOSP_EXT_STATUS_CHASE_FAIL
mdefine_line|#define&t;IOSP_EXT_STATUS_CHASE_FAIL&t;1&t;
singleline_comment|//&t;P2 = 1: Timed out (stuck due to flow
singleline_comment|//&t;&t;&t;control from remote device).
DECL|macro|IOSP_EXT_STATUS_RX_CHECK_RSP
mdefine_line|#define&t;IOSP_EXT_STATUS_RX_CHECK_RSP&t;1&t;
singleline_comment|// Reply to RX_CHECK cmd. P2 is sequence number
DECL|macro|IOSP_STATUS_OPEN_RSP
mdefine_line|#define IOSP_STATUS_OPEN_RSP&t;&t;0x0A&t;
singleline_comment|// Reply to OPEN_PORT cmd.
singleline_comment|// P1 is Initial MSR value
singleline_comment|// P2 is encoded TxBuffer Size:
singleline_comment|//&t;TxBufferSize = (P2 + 1) * 64
singleline_comment|//&t;&t;&t;&t;&t;0x0B&t;// Available for future expansion
DECL|macro|GET_TX_BUFFER_SIZE
mdefine_line|#define GET_TX_BUFFER_SIZE(P2) (((P2) + 1) * 64)
multiline_comment|/****************************************************&n; *&t;SSSS values for 4-byte status messages&n; ****************************************************/
DECL|macro|IOSP_EXT4_STATUS
mdefine_line|#define IOSP_EXT4_STATUS&t;&t;0x0C&t;
singleline_comment|// Extended status code in P1,
singleline_comment|// Params in P2, P3
singleline_comment|// Currently unimplemented.
singleline_comment|//&t;&t;&t;&t;&t;0x0D&t;// Currently unused, available.
singleline_comment|//
singleline_comment|// Macros to parse status messages
singleline_comment|//
DECL|macro|IOSP_GET_STATUS_LEN
mdefine_line|#define&t;IOSP_GET_STATUS_LEN(code)&t;( (code) &lt; 8 ? 2 : ((code) &lt; 0x0A ? 3 : 4) )
DECL|macro|IOSP_STATUS_IS_2BYTE
mdefine_line|#define&t;IOSP_STATUS_IS_2BYTE(code)&t;( (code) &lt; 0x08 )
DECL|macro|IOSP_STATUS_IS_3BYTE
mdefine_line|#define&t;IOSP_STATUS_IS_3BYTE(code)&t;( ((code) &gt;= 0x08) &amp;&amp; ((code) &lt;= 0x0B) )
DECL|macro|IOSP_STATUS_IS_4BYTE
mdefine_line|#define&t;IOSP_STATUS_IS_4BYTE(code)&t;( ((code) &gt;= 0x0C) &amp;&amp; ((code) &lt;= 0x0D) )
eof
