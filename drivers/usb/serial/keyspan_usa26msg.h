multiline_comment|/*&n;&t;usa26msg.h&n;&n;&t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&t;This file is available under a BSD-style copyright&n;&n;&t;Keyspan USB Async Firmware to run on Anchor EZ-USB&n;&n;&t;Redistribution and use in source and binary forms, with or without&n;&t;modification, are permitted provided that the following conditions are&n;&t;met:&n;&n;&t;1. Redistributions of source code must retain this licence text&n;   &t;without modification, this list of conditions, and the following&n;   &t;disclaimer.  The following copyright notice must appear immediately at&n;   &t;the beginning of all source files:&n;&n;        &t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&n;        &t;This file is available under a BSD-style copyright&n;&n;&t;2. Redistributions in binary form must reproduce the above copyright&n;   &t;notice, this list of conditions and the following disclaimer in the&n;   &t;documentation and/or other materials provided with the distribution.&n;&n;&t;3. The name of InnoSys Incorprated may not be used to endorse or promote&n;   &t;products derived from this software without specific prior written&n;   &t;permission.&n;&n;&t;THIS SOFTWARE IS PROVIDED BY INNOSYS CORP. ``AS IS&squot;&squot; AND ANY EXPRESS OR&n;&t;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n;&t;OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n;&t;NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,&n;&t;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;&t;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;&t;SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n;&t;CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n;&t;LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n;&t;OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n;&t;SUCH DAMAGE.    &n;&n;&t;Third revision: USA28X version (aka USA26)&n;&n;&t;Buffer formats for RX/TX data messages are not defined by&n;&t;a structure, but are described here:&n;&n;&t;USB OUT (host -&gt; USA26, transmit) messages contain a &n;&t;REQUEST_ACK indicator (set to 0xff to request an ACK at the &n;&t;completion of transmit; 0x00 otherwise), followed by data:&n;&n;&t;&t;RQSTACK DAT DAT DAT ...&n;&n;&t;with a total data length of 63.&n;&n;&t;USB IN (USA26 -&gt; host, receive) messages contain either a zero&n;&t;flag (indicating no error in any data bytes):&n;&n;&t;&t;00 DAT DAT DAT ...&n;&n;&t;for a total of 63 data bytes, or a non-zero status flag (indicating &n;&t;that all data bytes will be preceded by status flag):&n;&n;&t;&t;STAT DAT STAT DAT STAT DAT ...&n;&n;&t;for a total of 32 data bytes.  The valid bits in the STAT bytes are:&n;&n;&t;&t;OVERRUN&t;0x02&n;&t;&t;PARITY&t;0x04&n;&t;&t;FRAMING&t;0x08&n;&t;&t;BREAK&t;0x10&n;&n;&t;Note: a &quot;no status&quot; RX data message (first byte zero) can serve as&n;&t;a &quot;break off&quot; indicator.&n;&n;&t;revision history:&n;&n;&t;1999feb10&t;add reportHskiaChanges to allow us to ignore them&n;&t;1999feb10&t;add txAckThreshold for fast+loose throughput enhancement&n;&t;1999mar30&t;beef up support for RX error reporting&n;&t;1999apr14&t;add resetDataToggle to control message&n;&t;2000jan04&t;merge with usa17msg.h&n;&t;2000jun01&t;add extended BSD-style copyright text&n;&n;&t;Note on shared names:&n;&n;&t;In the case of fields which have been merged between the USA17&n;&t;and USA26 definitions, the USA26 definition is the first part&n;&t;of the name and the USA17 definition is the second part of the&n;&t;name; both meanings are described below.&n;*/
macro_line|#ifndef&t;__USA26MSG__
DECL|macro|__USA26MSG__
mdefine_line|#define&t;__USA26MSG__
DECL|struct|keyspan_usa26_portControlMessage
r_typedef
r_struct
id|keyspan_usa26_portControlMessage
(brace
multiline_comment|/*&n;&t;&t;there are three types of &quot;commands&quot; sent in the control message:&n;&n;&t;&t;1.&t;configuration changes which must be requested by setting&n;&t;&t;&t;the corresponding &quot;set&quot; flag (and should only be requested&n;&t;&t;&t;when necessary, to reduce overhead on the USA26):&n;&t;*/
DECL|member|setClocking
id|u8
id|setClocking
comma
singleline_comment|// BOTH: host requests baud rate be set
DECL|member|baudLo
id|baudLo
comma
singleline_comment|// BOTH: host does baud divisor calculation
DECL|member|baudHi
id|baudHi
comma
singleline_comment|// BOTH: baudHi is only used for first port (gives lower rates)
DECL|member|externalClock_txClocking
id|externalClock_txClocking
comma
singleline_comment|// USA26: 0=internal, other=external
singleline_comment|// USA17: 0=internal, other=external/RI
DECL|member|rxClocking
id|rxClocking
comma
singleline_comment|// USA17: 0=internal, 1=external/RI, other=external/DSR
DECL|member|setLcr
id|setLcr
comma
singleline_comment|// BOTH: host requests lcr be set
DECL|member|lcr
id|lcr
comma
singleline_comment|// BOTH: use PARITY, STOPBITS, DATABITS below
DECL|member|setFlowControl
id|setFlowControl
comma
singleline_comment|// BOTH: host requests flow control be set
DECL|member|ctsFlowControl
id|ctsFlowControl
comma
singleline_comment|// BOTH: 1=use CTS flow control, 0=don&squot;t
DECL|member|xonFlowControl
id|xonFlowControl
comma
singleline_comment|// BOTH: 1=use XON/XOFF flow control, 0=don&squot;t
DECL|member|xonChar
id|xonChar
comma
singleline_comment|// BOTH: specified in current character format
DECL|member|xoffChar
id|xoffChar
comma
singleline_comment|// BOTH: specified in current character format
DECL|member|setTxTriState_setRts
id|setTxTriState_setRts
comma
singleline_comment|// USA26: host requests TX tri-state be set
singleline_comment|// USA17: host requests RTS output be set
DECL|member|txTriState_rts
id|txTriState_rts
comma
singleline_comment|// BOTH: 1=active (normal), 0=tristate (off)
DECL|member|setHskoa_setDtr
id|setHskoa_setDtr
comma
singleline_comment|// USA26: host requests HSKOA output be set
singleline_comment|// USA17: host requests DTR output be set
DECL|member|hskoa_dtr
id|hskoa_dtr
comma
singleline_comment|// BOTH: 1=on, 0=off
DECL|member|setPrescaler
id|setPrescaler
comma
singleline_comment|// USA26: host requests prescalar be set (default: 13)
DECL|member|prescaler
id|prescaler
suffix:semicolon
singleline_comment|// BOTH: specified as N/8; values 8-ff are valid
singleline_comment|// must be set any time internal baud rate is set;
singleline_comment|// must not be set when external clocking is used
singleline_comment|// note: in USA17, prescaler is applied whenever
singleline_comment|// setClocking is requested
multiline_comment|/*&n;&t;&t;3.&t;configuration data which is simply used as is (no overhead,&n;&t;&t;&t;but must be specified correctly in every host message).&n;&t;*/
DECL|member|forwardingLength
id|u8
id|forwardingLength
comma
singleline_comment|// BOTH: forward when this number of chars available
DECL|member|reportHskiaChanges_dsrFlowControl
id|reportHskiaChanges_dsrFlowControl
comma
singleline_comment|// USA26: 1=normal; 0=ignore external clock
singleline_comment|// USA17: 1=use DSR flow control, 0=don&squot;t
DECL|member|txAckThreshold
id|txAckThreshold
comma
singleline_comment|// BOTH: 0=not allowed, 1=normal, 2-255 deliver ACK faster
DECL|member|loopbackMode
id|loopbackMode
suffix:semicolon
singleline_comment|// BOTH: 0=no loopback, 1=loopback enabled
multiline_comment|/*&n;&t;&t;4.&t;commands which are flags only; these are processed in order&n;&t;&t;&t;(so that, e.g., if both _txOn and _txOff flags are set, the&n;&t;&t;&t;port ends in a TX_OFF state); any non-zero value is respected&n;&t;*/
DECL|member|_txOn
id|u8
id|_txOn
comma
singleline_comment|// BOTH: enable transmitting (and continue if there&squot;s data)
DECL|member|_txOff
id|_txOff
comma
singleline_comment|// BOTH: stop transmitting
DECL|member|txFlush
id|txFlush
comma
singleline_comment|// BOTH: toss outbound data
DECL|member|txBreak
id|txBreak
comma
singleline_comment|// BOTH: turn on break (cleared by _txOn)
DECL|member|rxOn
id|rxOn
comma
singleline_comment|// BOTH: turn on receiver
DECL|member|rxOff
id|rxOff
comma
singleline_comment|// BOTH: turn off receiver
DECL|member|rxFlush
id|rxFlush
comma
singleline_comment|// BOTH: toss inbound data
DECL|member|rxForward
id|rxForward
comma
singleline_comment|// BOTH: forward all inbound data, NOW (as if fwdLen==1)
DECL|member|returnStatus
id|returnStatus
comma
singleline_comment|// BOTH: return current status (even if it hasn&squot;t changed)
DECL|member|resetDataToggle
id|resetDataToggle
suffix:semicolon
singleline_comment|// BOTH: reset data toggle state to DATA0
DECL|typedef|keyspan_usa26_portControlMessage
)brace
id|keyspan_usa26_portControlMessage
suffix:semicolon
singleline_comment|// defines for bits in lcr
DECL|macro|USA_DATABITS_5
mdefine_line|#define&t;USA_DATABITS_5&t;&t;0x00
DECL|macro|USA_DATABITS_6
mdefine_line|#define&t;USA_DATABITS_6&t;&t;0x01
DECL|macro|USA_DATABITS_7
mdefine_line|#define&t;USA_DATABITS_7&t;&t;0x02
DECL|macro|USA_DATABITS_8
mdefine_line|#define&t;USA_DATABITS_8&t;&t;0x03
DECL|macro|STOPBITS_5678_1
mdefine_line|#define&t;STOPBITS_5678_1&t;0x00&t;
singleline_comment|// 1 stop bit for all byte sizes
DECL|macro|STOPBITS_5_1p5
mdefine_line|#define&t;STOPBITS_5_1p5&t;0x04&t;
singleline_comment|// 1.5 stop bits for 5-bit byte
DECL|macro|STOPBITS_678_2
mdefine_line|#define&t;STOPBITS_678_2&t;0x04&t;
singleline_comment|// 2 stop bits for 6/7/8-bit byte
DECL|macro|USA_PARITY_NONE
mdefine_line|#define&t;USA_PARITY_NONE&t;&t;0x00
DECL|macro|USA_PARITY_ODD
mdefine_line|#define&t;USA_PARITY_ODD&t;&t;0x08
DECL|macro|USA_PARITY_EVEN
mdefine_line|#define&t;USA_PARITY_EVEN&t;&t;0x18
DECL|macro|PARITY_1
mdefine_line|#define&t;PARITY_1&t;&t;0x28
DECL|macro|PARITY_0
mdefine_line|#define&t;PARITY_0&t;&t;0x38
singleline_comment|// all things called &quot;StatusMessage&quot; are sent on the status endpoint
DECL|struct|keyspan_usa26_portStatusMessage
r_typedef
r_struct
id|keyspan_usa26_portStatusMessage
singleline_comment|// one for each port
(brace
DECL|member|port
id|u8
id|port
comma
singleline_comment|// BOTH: 0=first, 1=second, other=see below
DECL|member|hskia_cts
id|hskia_cts
comma
singleline_comment|// USA26: reports HSKIA pin
singleline_comment|// USA17: reports CTS pin
DECL|member|gpia_dcd
id|gpia_dcd
comma
singleline_comment|// USA26: reports GPIA pin
singleline_comment|// USA17: reports DCD pin
DECL|member|dsr
id|dsr
comma
singleline_comment|// USA17: reports DSR pin
DECL|member|ri
id|ri
comma
singleline_comment|// USA17: reports RI pin
DECL|member|_txOff
id|_txOff
comma
singleline_comment|// port has been disabled (by host)
DECL|member|_txXoff
id|_txXoff
comma
singleline_comment|// port is in XOFF state (either host or RX XOFF)
DECL|member|rxEnabled
id|rxEnabled
comma
singleline_comment|// as configured by rxOn/rxOff 1=on, 0=off
DECL|member|controlResponse
id|controlResponse
suffix:semicolon
singleline_comment|// 1=a control message has been processed
DECL|typedef|keyspan_usa26_portStatusMessage
)brace
id|keyspan_usa26_portStatusMessage
suffix:semicolon
singleline_comment|// bits in RX data message when STAT byte is included
DECL|macro|RXERROR_OVERRUN
mdefine_line|#define&t;RXERROR_OVERRUN&t;0x02
DECL|macro|RXERROR_PARITY
mdefine_line|#define&t;RXERROR_PARITY&t;0x04
DECL|macro|RXERROR_FRAMING
mdefine_line|#define&t;RXERROR_FRAMING&t;0x08
DECL|macro|RXERROR_BREAK
mdefine_line|#define&t;RXERROR_BREAK&t;0x10
DECL|struct|keyspan_usa26_globalControlMessage
r_typedef
r_struct
id|keyspan_usa26_globalControlMessage
(brace
DECL|member|sendGlobalStatus
id|u8
id|sendGlobalStatus
comma
singleline_comment|// 2=request for two status responses
DECL|member|resetStatusToggle
id|resetStatusToggle
comma
singleline_comment|// 1=reset global status toggle
DECL|member|resetStatusCount
id|resetStatusCount
suffix:semicolon
singleline_comment|// a cycling value
DECL|typedef|keyspan_usa26_globalControlMessage
)brace
id|keyspan_usa26_globalControlMessage
suffix:semicolon
DECL|struct|keyspan_usa26_globalStatusMessage
r_typedef
r_struct
id|keyspan_usa26_globalStatusMessage
(brace
DECL|member|port
id|u8
id|port
comma
singleline_comment|// 3
DECL|member|sendGlobalStatus
id|sendGlobalStatus
comma
singleline_comment|// from request, decremented
DECL|member|resetStatusCount
id|resetStatusCount
suffix:semicolon
singleline_comment|// as in request
DECL|typedef|keyspan_usa26_globalStatusMessage
)brace
id|keyspan_usa26_globalStatusMessage
suffix:semicolon
DECL|struct|keyspan_usa26_globalDebugMessage
r_typedef
r_struct
id|keyspan_usa26_globalDebugMessage
(brace
DECL|member|port
id|u8
id|port
comma
singleline_comment|// 2
DECL|member|a
id|a
comma
DECL|member|b
id|b
comma
DECL|member|c
id|c
comma
DECL|member|d
id|d
suffix:semicolon
DECL|typedef|keyspan_usa26_globalDebugMessage
)brace
id|keyspan_usa26_globalDebugMessage
suffix:semicolon
singleline_comment|// ie: the maximum length of an EZUSB endpoint buffer
DECL|macro|MAX_DATA_LEN
mdefine_line|#define&t;MAX_DATA_LEN&t;&t;&t;64
singleline_comment|// update status approx. 60 times a second (16.6666 ms)
DECL|macro|STATUS_UPDATE_INTERVAL
mdefine_line|#define&t;STATUS_UPDATE_INTERVAL&t;16
singleline_comment|// status rationing tuning value (each port gets checked each n ms)
DECL|macro|STATUS_RATION
mdefine_line|#define&t;STATUS_RATION&t;10
macro_line|#endif
eof
