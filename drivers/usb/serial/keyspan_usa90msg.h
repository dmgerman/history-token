multiline_comment|/*&n;&t;usa90msg.h&n;&n;&t;Copyright (c) 1998-2003 InnoSys Incorporated.  All Rights Reserved&n;&t;This file is available under a BSD-style copyright&n;&n;&t;Keyspan USB Async Message Formats for the USA19HS&n;&n;&t;Redistribution and use in source and binary forms, with or without&n;&t;modification, are permitted provided that the following conditions are&n;&t;met:&n;&n;&t;1. Redistributions of source code must retain this licence text&n;   &t;without modification, this list of conditions, and the following&n;   &t;disclaimer.  The following copyright notice must appear immediately at&n;   &t;the beginning of all source files:&n;&n;        &t;Copyright (c) 1998-2003 InnoSys Incorporated.  All Rights Reserved&n;&n;        &t;This file is available under a BSD-style copyright&n;&n;&t;2. The name of InnoSys Incorprated may not be used to endorse or promote&n;   &t;products derived from this software without specific prior written&n;   &t;permission.&n;&n;&t;THIS SOFTWARE IS PROVIDED BY INNOSYS CORP. ``AS IS&squot;&squot; AND ANY EXPRESS OR&n;&t;IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n;&t;OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n;&t;NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,&n;&t;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;&t;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;&t;SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n;&t;CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n;&t;LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n;&t;OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n;&t;SUCH DAMAGE.    &n;&n;&t;Revisions:&n;&n;&t;2003feb14&t;&t;add setTxMode/txMode  and cancelRxXoff to portControl&n;&t;2003mar21&t;&t;change name of PARITY_0/1 to add MARK/SPACE&n;*/
macro_line|#ifndef&t;__USA90MSG__
DECL|macro|__USA90MSG__
mdefine_line|#define&t;__USA90MSG__
DECL|struct|keyspan_usa90_portControlMessage
r_struct
id|keyspan_usa90_portControlMessage
(brace
multiline_comment|/*&n;&t;&t;there are three types of &quot;commands&quot; sent in the control message:&n;&n;&t;&t;1.&t;configuration changes which must be requested by setting&n;&t;&t;&t;the corresponding &quot;set&quot; flag (and should only be requested&n;&t;&t;&t;when necessary, to reduce overhead on the device):&n;&t;*/
DECL|member|setClocking
id|u8
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
singleline_comment|// host does baud divisor calculation 
DECL|member|setLcr
id|setLcr
comma
singleline_comment|// host requests lcr be set
DECL|member|lcr
id|lcr
comma
singleline_comment|// use PARITY, STOPBITS, DATABITS below
DECL|member|setRxMode
id|setRxMode
comma
singleline_comment|// set receive mode
DECL|member|rxMode
id|rxMode
comma
singleline_comment|// RXMODE_DMA or RXMODE_BYHAND
DECL|member|setTxMode
id|setTxMode
comma
singleline_comment|// set transmit mode
DECL|member|txMode
id|txMode
comma
singleline_comment|// TXMODE_DMA or TXMODE_BYHAND
DECL|member|setTxFlowControl
id|setTxFlowControl
comma
singleline_comment|// host requests tx flow control be set
DECL|member|txFlowControl
id|txFlowControl
comma
singleline_comment|// use TX_FLOW... bits below
DECL|member|setRxFlowControl
id|setRxFlowControl
comma
singleline_comment|// host requests rx flow control be set
DECL|member|rxFlowControl
id|rxFlowControl
comma
singleline_comment|// use RX_FLOW... bits below
DECL|member|sendXoff
id|sendXoff
comma
singleline_comment|// host requests XOFF transmitted immediately
DECL|member|sendXon
id|sendXon
comma
singleline_comment|// host requests XON char transmitted
DECL|member|xonChar
id|xonChar
comma
singleline_comment|// specified in current character format
DECL|member|xoffChar
id|xoffChar
comma
singleline_comment|// specified in current character format
DECL|member|sendChar
id|sendChar
comma
singleline_comment|// host requests char transmitted immediately
DECL|member|txChar
id|txChar
comma
singleline_comment|// character to send
DECL|member|setRts
id|setRts
comma
singleline_comment|// host requests RTS output be set
DECL|member|rts
id|rts
comma
singleline_comment|// 1=on, 0=off
DECL|member|setDtr
id|setDtr
comma
singleline_comment|// host requests DTR output be set
DECL|member|dtr
id|dtr
suffix:semicolon
singleline_comment|// 1=on, 0=off
multiline_comment|/*&n;&t;&t;2.&t;configuration data which is simply used as is &n;&t;&t;&t;and must be specified correctly in every host message.&n;&t;*/
DECL|member|rxForwardingLength
id|u8
id|rxForwardingLength
comma
singleline_comment|// forward when this number of chars available
DECL|member|rxForwardingTimeout
id|rxForwardingTimeout
comma
singleline_comment|// (1-31 in ms)
DECL|member|txAckSetting
id|txAckSetting
suffix:semicolon
singleline_comment|// 0=don&squot;t ack, 1=normal, 2-255 TBD...
multiline_comment|/*&n;&t;&t;3.&t;Firmware states which cause actions if they change&t;&t;&t;&t;&t;&n;&t;&t;and must be specified correctly in every host message.&n;&t;*/
DECL|member|portEnabled
id|u8
id|portEnabled
comma
singleline_comment|// 0=disabled, 1=enabled
DECL|member|txFlush
id|txFlush
comma
singleline_comment|// 0=normal, 1=toss outbound data
DECL|member|txBreak
id|txBreak
comma
singleline_comment|// 0=break off, 1=break on
DECL|member|loopbackMode
id|loopbackMode
suffix:semicolon
singleline_comment|// 0=no loopback, 1=loopback enabled
multiline_comment|/*&n;&t;&t;4.&t;commands which are flags only; these are processed in order&n;&t;&t;&t;(so that, e.g., if rxFlush and rxForward flags are set, the&n;&t;&t;&t;port will have no data to forward); any non-zero value &n;&t;&t;&t;is respected&n;&t;*/
DECL|member|rxFlush
id|u8
id|rxFlush
comma
singleline_comment|// toss inbound data
DECL|member|rxForward
id|rxForward
comma
singleline_comment|// forward all inbound data, NOW (as if fwdLen==1)
DECL|member|cancelRxXoff
id|cancelRxXoff
comma
singleline_comment|// cancel any receive XOFF state (_txXoff)
DECL|member|returnStatus
id|returnStatus
suffix:semicolon
singleline_comment|// return current status NOW
)brace
suffix:semicolon
singleline_comment|// defines for bits in lcr
DECL|macro|USA_DATABITS_5
mdefine_line|#define&t;&t;USA_DATABITS_5&t;&t;0x00
DECL|macro|USA_DATABITS_6
mdefine_line|#define&t;&t;USA_DATABITS_6&t;&t;0x01
DECL|macro|USA_DATABITS_7
mdefine_line|#define&t;&t;USA_DATABITS_7&t;&t;0x02
DECL|macro|USA_DATABITS_8
mdefine_line|#define&t;&t;USA_DATABITS_8&t;&t;0x03
DECL|macro|STOPBITS_5678_1
mdefine_line|#define&t;&t;STOPBITS_5678_1&t;&t;0x00&t;
singleline_comment|// 1 stop bit for all byte sizes
DECL|macro|STOPBITS_5_1p5
mdefine_line|#define&t;&t;STOPBITS_5_1p5&t;&t;0x04&t;
singleline_comment|// 1.5 stop bits for 5-bit byte
DECL|macro|STOPBITS_678_2
mdefine_line|#define&t;&t;STOPBITS_678_2&t;&t;0x04&t;
singleline_comment|// 2 stop bits for 6-8 bit byte
DECL|macro|USA_PARITY_NONE
mdefine_line|#define&t;&t;USA_PARITY_NONE&t;&t;0x00
DECL|macro|USA_PARITY_ODD
mdefine_line|#define&t;&t;USA_PARITY_ODD&t;&t;0x08
DECL|macro|USA_PARITY_EVEN
mdefine_line|#define&t;&t;USA_PARITY_EVEN&t;&t;0x18
DECL|macro|PARITY_MARK_1
mdefine_line|#define&t;&t;PARITY_MARK_1  &t;&t;0x28   &t;
singleline_comment|// force parity MARK
DECL|macro|PARITY_SPACE_0
mdefine_line|#define&t;&t;PARITY_SPACE_0 &t;&t;0x38&t;
singleline_comment|// force parity SPACE
DECL|macro|TXFLOW_CTS
mdefine_line|#define&t;&t;TXFLOW_CTS&t;&t;&t;0x04&t;
DECL|macro|TXFLOW_DSR
mdefine_line|#define&t;&t;TXFLOW_DSR&t;&t;&t;0x08
DECL|macro|TXFLOW_XOFF
mdefine_line|#define&t;&t;TXFLOW_XOFF&t;&t;&t;0x01&t;
DECL|macro|TXFLOW_XOFF_ANY
mdefine_line|#define&t;&t;TXFLOW_XOFF_ANY&t;&t;0x02&t;
DECL|macro|TXFLOW_XOFF_BITS
mdefine_line|#define&t;&t;TXFLOW_XOFF_BITS&t;(TXFLOW_XOFF | TXFLOW_XOFF_ANY)
DECL|macro|RXFLOW_XOFF
mdefine_line|#define&t;&t;RXFLOW_XOFF&t;&t;&t;0x10&t;
DECL|macro|RXFLOW_RTS
mdefine_line|#define&t;&t;RXFLOW_RTS&t;&t;&t;0x20&t;
DECL|macro|RXFLOW_DTR
mdefine_line|#define&t;&t;RXFLOW_DTR&t;&t;&t;0x40
DECL|macro|RXFLOW_DSR_SENSITIVITY
mdefine_line|#define&t;&t;RXFLOW_DSR_SENSITIVITY&t;0x80
DECL|macro|RXMODE_BYHAND
mdefine_line|#define&t;&t;RXMODE_BYHAND&t;&t;0x00&t;
DECL|macro|RXMODE_DMA
mdefine_line|#define&t;&t;RXMODE_DMA&t;&t;&t;0x02&t;
DECL|macro|TXMODE_BYHAND
mdefine_line|#define&t;&t;TXMODE_BYHAND&t;&t;0x00&t;
DECL|macro|TXMODE_DMA
mdefine_line|#define&t;&t;TXMODE_DMA&t;&t;&t;0x02&t;
singleline_comment|// all things called &quot;StatusMessage&quot; are sent on the status endpoint
DECL|struct|keyspan_usa90_portStatusMessage
r_struct
id|keyspan_usa90_portStatusMessage
(brace
DECL|member|msr
id|u8
id|msr
comma
singleline_comment|// reports the actual MSR register
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
DECL|member|_txXoff
id|_txXoff
comma
singleline_comment|// port is in XOFF state (we received XOFF)
DECL|member|rxBreak
id|rxBreak
comma
singleline_comment|// reports break state
DECL|member|rxOverrun
id|rxOverrun
comma
singleline_comment|// count of overrun errors (since last reported)
DECL|member|rxParity
id|rxParity
comma
singleline_comment|// count of parity errors (since last reported)
DECL|member|rxFrame
id|rxFrame
comma
singleline_comment|// count of frame errors (since last reported)
DECL|member|portState
id|portState
comma
singleline_comment|// PORTSTATE_xxx bits (useful for debugging)
DECL|member|messageAck
id|messageAck
comma
singleline_comment|// message acknowledgement
DECL|member|charAck
id|charAck
comma
singleline_comment|// character acknowledgement
DECL|member|controlResponse
id|controlResponse
suffix:semicolon
singleline_comment|// (value = returnStatus) a control message has been processed 
)brace
suffix:semicolon
singleline_comment|// bits in RX data message when STAT byte is included
DECL|macro|RXERROR_OVERRUN
mdefine_line|#define&t;RXERROR_OVERRUN&t;&t;0x02
DECL|macro|RXERROR_PARITY
mdefine_line|#define&t;RXERROR_PARITY&t;&t;0x04
DECL|macro|RXERROR_FRAMING
mdefine_line|#define&t;RXERROR_FRAMING&t;&t;0x08
DECL|macro|RXERROR_BREAK
mdefine_line|#define&t;RXERROR_BREAK&t;&t;0x10
DECL|macro|PORTSTATE_ENABLED
mdefine_line|#define&t;PORTSTATE_ENABLED&t;0x80
DECL|macro|PORTSTATE_TXFLUSH
mdefine_line|#define&t;PORTSTATE_TXFLUSH&t;0x01
DECL|macro|PORTSTATE_TXBREAK
mdefine_line|#define&t;PORTSTATE_TXBREAK&t;0x02
DECL|macro|PORTSTATE_LOOPBACK
mdefine_line|#define&t;PORTSTATE_LOOPBACK &t;0x04
singleline_comment|// MSR bits
DECL|macro|USA_MSR_dCTS
mdefine_line|#define USA_MSR_dCTS&t;  &t;&t;0x01&t;&t;
singleline_comment|// CTS has changed since last report&t;
DECL|macro|USA_MSR_dDSR
mdefine_line|#define USA_MSR_dDSR&t;  &t;&t;0x02
DECL|macro|USA_MSR_dRI
mdefine_line|#define USA_MSR_dRI&t;&t;&t;0x04
DECL|macro|USA_MSR_dDCD
mdefine_line|#define USA_MSR_dDCD&t;  &t;&t;0x08
DECL|macro|USA_MSR_CTS
mdefine_line|#define USA_MSR_CTS&t;&t;&t;0x10&t;  &t;
singleline_comment|// current state of CTS
DECL|macro|USA_MSR_DSR
mdefine_line|#define USA_MSR_DSR&t;&t;&t;0x20
DECL|macro|USA_USA_MSR_RI
mdefine_line|#define USA_USA_MSR_RI&t;&t;&t;0x40
DECL|macro|MSR_DCD
mdefine_line|#define MSR_DCD&t;&t;&t;&t;0x80
singleline_comment|// ie: the maximum length of an endpoint buffer
DECL|macro|MAX_DATA_LEN
mdefine_line|#define&t;&t;MAX_DATA_LEN&t;&t;&t;64
macro_line|#endif
eof
