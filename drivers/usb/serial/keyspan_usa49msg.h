multiline_comment|/*&n;&t;usa49msg.h&n;&n;&t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&t;This file is available under a BSD-style copyright&n;&n;&t;Keyspan USB Async Firmware to run on Anchor EZ-USB&n;&n;&t;Redistribution and use in source and binary forms, with or without&n;&t;modification, are permitted provided that the following conditions are&n;&t;met:&n;&n;&t;1. Redistributions of source code must retain this licence text&n;   &t;without modification, this list of conditions, and the following&n;   &t;disclaimer.  The following copyright notice must appear immediately at&n;   &t;the beginning of all source files:&n;&n;        &t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&n;        &t;This file is available under a BSD-style copyright&n;&n;&t;2. Redistributions in binary form must reproduce the above copyright&n;   &t;notice, this list of conditions and the following disclaimer in the&n;   &t;documentation and/or other materials provided with the distribution.&n;&n;&t;3. The name of InnoSys Incorprated may not be used to endorse or promote&n;   &t;products derived from this software without specific prior written&n;   &t;permission.&n;&n;&t;THIS SOFTWARE IS PROVIDED BY INNOSYS CORP. ``AS IS&squot;&squot; AND ANY EXPRESS OR&n;&t;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n;&t;OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n;&t;NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,&n;&t;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;&t;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;&t;SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n;&t;CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n;&t;LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n;&t;OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n;&t;SUCH DAMAGE.    &n;&n;&t;4th revision: USA49W version&n;&n;&t;See usa26msg.h for description of message formats&n;&n;&t;Third revision: USA28X version (aka USA26)&n;&n;&t;Buffer formats for RX/TX data messages are not defined by&n;&t;a structure, but are described here:&n;&n;&t;USB OUT (host -&gt; USA26, transmit) messages contain a &n;&t;REQUEST_ACK indicator (set to 0xff to request an ACK at the &n;&t;completion of transmit; 0x00 otherwise), followed by data:&n;&n;&t;&t;RQSTACK DAT DAT DAT ...&n;&n;&t;with a total data length of 63.&n;&n;&t;USB IN (USA26 -&gt; host, receive) messages contain either a zero&n;&t;flag (indicating no error in any data bytes):&n;&n;&t;&t;00 DAT DAT DAT ...&n;&n;&t;for a total of 63 data bytes, or a non-zero status flag (indicating &n;&t;that all data bytes will be preceded by status flag):&n;&n;&t;&t;STAT DAT STAT DAT STAT DAT ...&n;&n;&t;for a total of 32 data bytes.  The valid bits in the STAT bytes are:&n;&n;&t;&t;OVERRUN&t;0x02&n;&t;&t;PARITY&t;0x04&n;&t;&t;FRAMING&t;0x08&n;&t;&t;BREAK&t;0x10&n;&n;&t;Notes:&n;&t;&n;&t;1.&t;a &quot;no status&quot; RX data message (first byte zero) can serve as&n;&t;&t;a &quot;break off&quot; indicator.&n;&t;2.&t;a control message specifying disablePort will be answered&n;&t;&t;with a status message, but no further status will be sent&n;&t;&t;until a control messages with enablePort is sent&n;&n;&t;revision history:&n;&n;&t;1999feb10&t;add reportHskiaChanges to allow us to ignore them&n;&t;1999feb10&t;add txAckThreshold for fast+loose throughput enhancement&n;&t;1999mar30&t;beef up support for RX error reporting&n;&t;1999apr14&t;add resetDataToggle to control message&n;&t;2000jan04&t;merge with usa17msg.h&n;&t;2000mar08&t;clone from usa26msg.h -&gt; usa49msg.h&n;&t;2000mar09&t;change to support 4 ports&n;&t;2000may03&t;change external clocking to match USA-49W hardware&n;&t;2000jun01&t;add extended BSD-style copyright text&n;*/
macro_line|#ifndef&t;__USA49MSG__
DECL|macro|__USA49MSG__
mdefine_line|#define&t;__USA49MSG__
multiline_comment|/*&n;&t;Host-&gt;device messages sent on the global control endpoint:&n;&n;&t;portNumber&t;message&n;&t;----------&t;--------------------&n;&t;0,1,2,3&t;&t;portControlMessage&n;&t;0x80&t;&t;globalControlMessage&n;*/
DECL|struct|keyspan_usa49_portControlMessage
r_typedef
r_struct
id|keyspan_usa49_portControlMessage
(brace
multiline_comment|/*&n;&t;&t;0.&t;0/1/2/3 &t;port control message follows&n;&t;&t;&t;0x80 set&t;non-port control message follows&n;&t;*/
DECL|member|portNumber
id|u8
id|portNumber
comma
multiline_comment|/*&n;&t;&t;there are three types of &quot;commands&quot; sent in the control message:&n;&n;&t;&t;1.&t;configuration changes which must be requested by setting&n;&t;&t;&t;the corresponding &quot;set&quot; flag (and should only be requested&n;&t;&t;&t;when necessary, to reduce overhead on the USA26):&n;&t;*/
DECL|member|setClocking
id|setClocking
comma
singleline_comment|// host requests baud rate be set
DECL|member|baudLo
id|baudLo
comma
singleline_comment|// host does baud divisor calculation
DECL|member|baudHi
id|baudHi
comma
singleline_comment|// baudHi is only used for first port (gives lower rates)
DECL|member|prescaler
id|prescaler
comma
singleline_comment|// specified as N/8; values 8-ff are valid
singleline_comment|// must be set any time internal baud rate is set;
DECL|member|txClocking
id|txClocking
comma
singleline_comment|// 0=internal, 1=external/DSR
DECL|member|rxClocking
id|rxClocking
comma
singleline_comment|// 0=internal, 1=external/DSR
DECL|member|setLcr
id|setLcr
comma
singleline_comment|// host requests lcr be set
DECL|member|lcr
id|lcr
comma
singleline_comment|// use PARITY, STOPBITS, DATABITS below
DECL|member|setFlowControl
id|setFlowControl
comma
singleline_comment|// host requests flow control be set
DECL|member|ctsFlowControl
id|ctsFlowControl
comma
singleline_comment|// 1=use CTS flow control, 0=don&squot;t
DECL|member|xonFlowControl
id|xonFlowControl
comma
singleline_comment|// 1=use XON/XOFF flow control, 0=don&squot;t
DECL|member|xonChar
id|xonChar
comma
singleline_comment|// specified in current character format
DECL|member|xoffChar
id|xoffChar
comma
singleline_comment|// specified in current character format
DECL|member|setRts
id|setRts
comma
singleline_comment|// host requests RTS output be set
DECL|member|rts
id|rts
comma
singleline_comment|// 1=active, 0=inactive
DECL|member|setDtr
id|setDtr
comma
singleline_comment|// host requests DTR output be set
DECL|member|dtr
id|dtr
suffix:semicolon
singleline_comment|// 1=on, 0=off
multiline_comment|/*&n;&t;&t;3.&t;configuration data which is simply used as is (no overhead,&n;&t;&t;&t;but must be specified correctly in every host message).&n;&t;*/
DECL|member|forwardingLength
id|u8
id|forwardingLength
comma
singleline_comment|// forward when this number of chars available
DECL|member|dsrFlowControl
id|dsrFlowControl
comma
singleline_comment|// 1=use DSR flow control, 0=don&squot;t
DECL|member|txAckThreshold
id|txAckThreshold
comma
singleline_comment|// 0=not allowed, 1=normal, 2-255 deliver ACK faster
DECL|member|loopbackMode
id|loopbackMode
suffix:semicolon
singleline_comment|// 0=no loopback, 1=loopback enabled
multiline_comment|/*&n;&t;&t;4.&t;commands which are flags only; these are processed in order&n;&t;&t;&t;(so that, e.g., if both _txOn and _txOff flags are set, the&n;&t;&t;&t;port ends in a TX_OFF state); any non-zero value is respected&n;&t;*/
DECL|member|_txOn
id|u8
id|_txOn
comma
singleline_comment|// enable transmitting (and continue if there&squot;s data)
DECL|member|_txOff
id|_txOff
comma
singleline_comment|// stop transmitting
DECL|member|txFlush
id|txFlush
comma
singleline_comment|// toss outbound data
DECL|member|txBreak
id|txBreak
comma
singleline_comment|// turn on break (cleared by _txOn)
DECL|member|rxOn
id|rxOn
comma
singleline_comment|// turn on receiver
DECL|member|rxOff
id|rxOff
comma
singleline_comment|// turn off receiver
DECL|member|rxFlush
id|rxFlush
comma
singleline_comment|// toss inbound data
DECL|member|rxForward
id|rxForward
comma
singleline_comment|// forward all inbound data, NOW (as if fwdLen==1)
DECL|member|returnStatus
id|returnStatus
comma
singleline_comment|// return current status (even if it hasn&squot;t changed)
DECL|member|resetDataToggle
id|resetDataToggle
comma
singleline_comment|// reset data toggle state to DATA0
DECL|member|enablePort
id|enablePort
comma
singleline_comment|// start servicing port (move data, check status)
DECL|member|disablePort
id|disablePort
suffix:semicolon
singleline_comment|// stop servicing port (does implicit tx/rx flush/off)
DECL|typedef|keyspan_usa49_portControlMessage
)brace
id|keyspan_usa49_portControlMessage
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
mdefine_line|#define&t;STOPBITS_5678_1&t;&t;0x00&t;
singleline_comment|// 1 stop bit for all byte sizes
DECL|macro|STOPBITS_5_1p5
mdefine_line|#define&t;STOPBITS_5_1p5&t;&t;0x04&t;
singleline_comment|// 1.5 stop bits for 5-bit byte
DECL|macro|STOPBITS_678_2
mdefine_line|#define&t;STOPBITS_678_2&t;&t;0x04&t;
singleline_comment|// 2 stop bits for 6/7/8-bit byte
DECL|macro|USA_PARITY_NONE
mdefine_line|#define&t;USA_PARITY_NONE&t;&t;0x00
DECL|macro|USA_PARITY_ODD
mdefine_line|#define&t;USA_PARITY_ODD&t;&t;0x08
DECL|macro|USA_PARITY_EVEN
mdefine_line|#define&t;USA_PARITY_EVEN&t;&t;0x18
DECL|macro|PARITY_1
mdefine_line|#define&t;PARITY_1&t;&t;&t;0x28
DECL|macro|PARITY_0
mdefine_line|#define&t;PARITY_0&t;&t;&t;0x38
multiline_comment|/*&n;&t;during normal operation, status messages are returned &n;&t;to the host whenever the board detects changes.  In some&n;&t;circumstances (e.g. Windows), status messages from the&n;&t;device cause problems; to shut them off, the host issues&n;&t;a control message with the disableStatusMessages flags&n;&t;set (to any non-zero value).  The device will respond to&n;&t;this message, and then suppress further status messages;&n;&t;it will resume sending status messages any time the host&n;&t;sends any control message (either global or port-specific).&n;*/
DECL|struct|keyspan_usa49_globalControlMessage
r_typedef
r_struct
id|keyspan_usa49_globalControlMessage
(brace
DECL|member|portNumber
id|u8
id|portNumber
comma
singleline_comment|// 0x80
DECL|member|sendGlobalStatus
id|sendGlobalStatus
comma
singleline_comment|// 1/2=number of status responses requested
DECL|member|resetStatusToggle
id|resetStatusToggle
comma
singleline_comment|// 1=reset global status toggle
DECL|member|resetStatusCount
id|resetStatusCount
comma
singleline_comment|// a cycling value
DECL|member|remoteWakeupEnable
id|remoteWakeupEnable
comma
singleline_comment|// 0x10=P1, 0x20=P2, 0x40=P3, 0x80=P4
DECL|member|disableStatusMessages
id|disableStatusMessages
suffix:semicolon
singleline_comment|// 1=send no status until host talks
DECL|typedef|keyspan_usa49_globalControlMessage
)brace
id|keyspan_usa49_globalControlMessage
suffix:semicolon
multiline_comment|/*&n;&t;Device-&gt;host messages send on the global status endpoint&n;&n;&t;portNumber&t;&t;&t;message&n;&t;----------&t;&t;&t;--------------------&n;&t;0x00,0x01,0x02,0x03&t;portStatusMessage&n;&t;0x80&t;&t;&t;&t;globalStatusMessage&n;&t;0x81&t;&t;&t;&t;globalDebugMessage&n;*/
DECL|struct|keyspan_usa49_portStatusMessage
r_typedef
r_struct
id|keyspan_usa49_portStatusMessage
singleline_comment|// one for each port
(brace
DECL|member|portNumber
id|u8
id|portNumber
comma
singleline_comment|// 0,1,2,3
DECL|member|cts
id|cts
comma
singleline_comment|// reports CTS pin
DECL|member|dcd
id|dcd
comma
singleline_comment|// reports DCD pin
DECL|member|dsr
id|dsr
comma
singleline_comment|// reports DSR pin
DECL|member|ri
id|ri
comma
singleline_comment|// reports RI pin
DECL|member|_txOff
id|_txOff
comma
singleline_comment|// transmit has been disabled (by host)
DECL|member|_txXoff
id|_txXoff
comma
singleline_comment|// transmit is in XOFF state (either host or RX XOFF)
DECL|member|rxEnabled
id|rxEnabled
comma
singleline_comment|// as configured by rxOn/rxOff 1=on, 0=off
DECL|member|controlResponse
id|controlResponse
comma
singleline_comment|// 1=a control message has been processed
DECL|member|txAck
id|txAck
comma
singleline_comment|// ACK (data TX complete)
DECL|member|rs232valid
id|rs232valid
suffix:semicolon
singleline_comment|// RS-232 signal valid
DECL|typedef|keyspan_usa49_portStatusMessage
)brace
id|keyspan_usa49_portStatusMessage
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
DECL|struct|keyspan_usa49_globalStatusMessage
r_typedef
r_struct
id|keyspan_usa49_globalStatusMessage
(brace
DECL|member|portNumber
id|u8
id|portNumber
comma
singleline_comment|// 0x80=globalStatusMessage
DECL|member|sendGlobalStatus
id|sendGlobalStatus
comma
singleline_comment|// from request, decremented
DECL|member|resetStatusCount
id|resetStatusCount
suffix:semicolon
singleline_comment|// as in request
DECL|typedef|keyspan_usa49_globalStatusMessage
)brace
id|keyspan_usa49_globalStatusMessage
suffix:semicolon
DECL|struct|keyspan_usa49_globalDebugMessage
r_typedef
r_struct
id|keyspan_usa49_globalDebugMessage
(brace
DECL|member|portNumber
id|u8
id|portNumber
comma
singleline_comment|// 0x81=globalDebugMessage
DECL|member|n
id|n
comma
singleline_comment|// typically a count/status byte
DECL|member|b
id|b
suffix:semicolon
singleline_comment|// typically a data byte
DECL|typedef|keyspan_usa49_globalDebugMessage
)brace
id|keyspan_usa49_globalDebugMessage
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
