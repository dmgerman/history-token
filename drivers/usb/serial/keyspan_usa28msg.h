multiline_comment|/*&n;&t;usa28msg.h&n;&n;&t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&t;This file is available under a BSD-style copyright&n;&n;&t;Keyspan USB Async Firmware to run on Anchor EZ-USB&n;&n;&t;Redistribution and use in source and binary forms, with or without&n;&t;modification, are permitted provided that the following conditions are&n;&t;met:&n;&n;&t;1. Redistributions of source code must retain this licence text&n;   &t;without modification, this list of conditions, and the following&n;   &t;disclaimer.  The following copyright notice must appear immediately at&n;   &t;the beginning of all source files:&n;&n;        &t;Copyright (c) 1998-2000 InnoSys Incorporated.  All Rights Reserved&n;&n;        &t;This file is available under a BSD-style copyright&n;&n;&t;2. Redistributions in binary form must reproduce the above copyright&n;   &t;notice, this list of conditions and the following disclaimer in the&n;   &t;documentation and/or other materials provided with the distribution.&n;&n;&t;3. The name of InnoSys Incorprated may not be used to endorse or promote&n;   &t;products derived from this software without specific prior written&n;   &t;permission.&n;&n;&t;THIS SOFTWARE IS PROVIDED BY INNOSYS CORP. ``AS IS&squot;&squot; AND ANY EXPRESS OR&n;&t;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n;&t;OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n;&t;NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,&n;&t;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;&t;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;&t;SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n;&t;CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n;&t;LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n;&t;OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n;&t;SUCH DAMAGE.    &n;&n;&t;Note: these message formats are common to USA18, USA19, and USA28;&n;&t;(for USA28X, see usa26msg.h)&n;&n;&t;Buffer formats for RX/TX data messages are not defined by&n;&t;a structure, but are described here:&n;&n;&t;USB OUT (host -&gt; USA28, transmit) messages contain a &n;&t;REQUEST_ACK indicator (set to 0xff to request an ACK at the &n;&t;completion of transmit; 0x00 otherwise), followed by data.&n;&t;If the port is configured for parity, the data will be an &n;&t;alternating string of parity and data bytes, so the message&n;&t;format will be:&n;&n;&t;&t;RQSTACK PAR DAT PAR DAT ...&n;&n;&t;so the maximum length is 63 bytes (1 + 62, or 31 data bytes);&n;&t;always an odd number for the total message length.&n;&n;&t;If there is no parity, the format is simply:&n;&n;&t;&t;RQSTACK DAT DAT DAT ...&n;&n;&t;with a total data length of 63.&n;&n;&t;USB IN (USA28 -&gt; host, receive) messages contain data and parity&n;&t;if parity is configred, thusly:&n;&t;&n;&t;&t;DAT PAR DAT PAR DAT PAR ...&n;&n;&t;for a total of 32 data bytes;&n;&t;&n;&t;If parity is not configured, the format is:&n;&n;&t;&t;DAT DAT DAT ...&n;&n;&t;for a total of 64 data bytes.&n;&n;&t;In the TX messages (USB OUT), the 0x01 bit of the PARity byte is &n;&t;the parity bit.  In the RX messages (USB IN), the PARity byte is &n;&t;the content of the 8051&squot;s status register; the parity bit &n;&t;(RX_PARITY_BIT) is the 0x04 bit.&n;&n;&t;revision history:&n;&n;&t;1999may06&t;add resetDataToggle to control message&n;&t;2000mar21&t;add rs232invalid to status response message&n;&t;2000apr04&t;add 230.4Kb definition to setBaudRate&n;&t;2000apr13&t;add/remove loopbackMode switch&n;&t;2000apr13&t;change definition of setBaudRate to cover 115.2Kb, too&n;&t;2000jun01&t;add extended BSD-style copyright text&n;*/
macro_line|#ifndef&t;__USA28MSG__
DECL|macro|__USA28MSG__
mdefine_line|#define&t;__USA28MSG__
DECL|struct|keyspan_usa28_portControlMessage
r_struct
id|keyspan_usa28_portControlMessage
(brace
multiline_comment|/*&n;&t;&t;there are four types of &quot;commands&quot; sent in the control message:&n;&n;&t;&t;1.&t;configuration changes which must be requested by setting&n;&t;&t;&t;the corresponding &quot;set&quot; flag (and should only be requested&n;&t;&t;&t;when necessary, to reduce overhead on the USA28):&n;&t;*/
DECL|member|setBaudRate
id|u8
id|setBaudRate
comma
singleline_comment|// 0=don&squot;t set, 1=baudLo/Hi, 2=115.2K, 3=230.4K
DECL|member|baudLo
id|baudLo
comma
singleline_comment|// host does baud divisor calculation
DECL|member|baudHi
id|baudHi
suffix:semicolon
singleline_comment|// baudHi is only used for first port (gives lower rates)
multiline_comment|/*&n;&t;&t;2.&t;configuration changes which are done every time (because it&squot;s&n;&t;&t;&t;hardly more trouble to do them than to check whether to do them):&n;&t;*/
DECL|member|parity
id|u8
id|parity
comma
singleline_comment|// 1=use parity, 0=don&squot;t
DECL|member|ctsFlowControl
id|ctsFlowControl
comma
singleline_comment|// all except 19Q: 1=use CTS flow control, 0=don&squot;t
singleline_comment|// 19Q: 0x08:CTSflowControl 0x10:DSRflowControl
DECL|member|xonFlowControl
id|xonFlowControl
comma
singleline_comment|// 1=use XON/XOFF flow control, 0=don&squot;t
DECL|member|rts
id|rts
comma
singleline_comment|// 1=on, 0=off
DECL|member|dtr
id|dtr
suffix:semicolon
singleline_comment|// 1=on, 0=off
multiline_comment|/*&n;&t;&t;3.&t;configuration data which is simply used as is (no overhead,&n;&t;&t;&t;but must be correct in every host message).&n;&t;*/
DECL|member|forwardingLength
id|u8
id|forwardingLength
comma
singleline_comment|// forward when this number of chars available
DECL|member|forwardMs
id|forwardMs
comma
singleline_comment|// forward this many ms after last rx data
DECL|member|breakThreshold
id|breakThreshold
comma
singleline_comment|// specified in ms, 1-255 (see note below)
DECL|member|xonChar
id|xonChar
comma
singleline_comment|// specified in current character format
DECL|member|xoffChar
id|xoffChar
suffix:semicolon
singleline_comment|// specified in current character format
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
DECL|member|txForceXoff
id|txForceXoff
comma
singleline_comment|// pretend we&squot;ve received XOFF
DECL|member|txBreak
id|txBreak
comma
singleline_comment|// turn on break (leave on until txOn clears it)
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
singleline_comment|// forward all inbound data, NOW
DECL|member|returnStatus
id|returnStatus
comma
singleline_comment|// return current status n times (1 or 2)
DECL|member|resetDataToggle
id|resetDataToggle
suffix:semicolon
singleline_comment|// reset data toggle state to DATA0
)brace
suffix:semicolon
DECL|struct|keyspan_usa28_portStatusMessage
r_struct
id|keyspan_usa28_portStatusMessage
(brace
DECL|member|port
id|u8
id|port
comma
singleline_comment|// 0=first, 1=second, 2=global (see below)
DECL|member|cts
id|cts
comma
DECL|member|dsr
id|dsr
comma
singleline_comment|// (not used in all products)
DECL|member|dcd
id|dcd
comma
DECL|member|ri
id|ri
comma
singleline_comment|// (not used in all products)
DECL|member|_txOff
id|_txOff
comma
singleline_comment|// port has been disabled (by host)
DECL|member|_txXoff
id|_txXoff
comma
singleline_comment|// port is in XOFF state (either host or RX XOFF)
DECL|member|dataLost
id|dataLost
comma
singleline_comment|// count of lost chars; wraps; not guaranteed exact
DECL|member|rxEnabled
id|rxEnabled
comma
singleline_comment|// as configured by rxOn/rxOff 1=on, 0=off
DECL|member|rxBreak
id|rxBreak
comma
singleline_comment|// 1=we&squot;re in break state
DECL|member|rs232invalid
id|rs232invalid
comma
singleline_comment|// 1=no valid signals on rs-232 inputs
DECL|member|controlResponse
id|controlResponse
suffix:semicolon
singleline_comment|// 1=a control messages has been processed
)brace
suffix:semicolon
singleline_comment|// bit defines in txState
DECL|macro|TX_OFF
mdefine_line|#define&t;TX_OFF&t;&t;&t;0x01&t;
singleline_comment|// requested by host txOff command
DECL|macro|TX_XOFF
mdefine_line|#define&t;TX_XOFF&t;&t;&t;0x02&t;
singleline_comment|// either real, or simulated by host
DECL|struct|keyspan_usa28_globalControlMessage
r_struct
id|keyspan_usa28_globalControlMessage
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
)brace
suffix:semicolon
DECL|struct|keyspan_usa28_globalStatusMessage
r_struct
id|keyspan_usa28_globalStatusMessage
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
)brace
suffix:semicolon
DECL|struct|keyspan_usa28_globalDebugMessage
r_struct
id|keyspan_usa28_globalDebugMessage
(brace
DECL|member|port
id|u8
id|port
comma
singleline_comment|// 2
DECL|member|n
id|n
comma
singleline_comment|// typically a count/status byte
DECL|member|b
id|b
suffix:semicolon
singleline_comment|// typically a data byte
)brace
suffix:semicolon
singleline_comment|// ie: the maximum length of an EZUSB endpoint buffer
DECL|macro|MAX_DATA_LEN
mdefine_line|#define&t;MAX_DATA_LEN&t;&t;&t;64
singleline_comment|// the parity bytes have only one significant bit
DECL|macro|RX_PARITY_BIT
mdefine_line|#define&t;RX_PARITY_BIT&t;&t;&t;0x04
DECL|macro|TX_PARITY_BIT
mdefine_line|#define&t;TX_PARITY_BIT&t;&t;&t;0x01
singleline_comment|// update status approx. 60 times a second (16.6666 ms)
DECL|macro|STATUS_UPDATE_INTERVAL
mdefine_line|#define&t;STATUS_UPDATE_INTERVAL&t;16
macro_line|#endif
eof
