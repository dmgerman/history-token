multiline_comment|/*&n; * ipmi_smi.h&n; *&n; * MontaVista IPMI system management interface&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __LINUX_IPMI_MSGDEFS_H
DECL|macro|__LINUX_IPMI_MSGDEFS_H
mdefine_line|#define __LINUX_IPMI_MSGDEFS_H
multiline_comment|/* Various definitions for IPMI messages used by almost everything in&n;   the IPMI stack. */
multiline_comment|/* NetFNs and commands used inside the IPMI stack. */
DECL|macro|IPMI_NETFN_SENSOR_EVENT_REQUEST
mdefine_line|#define IPMI_NETFN_SENSOR_EVENT_REQUEST&t;&t;0x04
DECL|macro|IPMI_NETFN_SENSOR_EVENT_RESPONSE
mdefine_line|#define IPMI_NETFN_SENSOR_EVENT_RESPONSE&t;0x05
DECL|macro|IPMI_GET_EVENT_RECEIVER_CMD
mdefine_line|#define IPMI_GET_EVENT_RECEIVER_CMD&t;0x01
DECL|macro|IPMI_NETFN_APP_REQUEST
mdefine_line|#define IPMI_NETFN_APP_REQUEST&t;&t;&t;0x06
DECL|macro|IPMI_NETFN_APP_RESPONSE
mdefine_line|#define IPMI_NETFN_APP_RESPONSE&t;&t;&t;0x07
DECL|macro|IPMI_GET_DEVICE_ID_CMD
mdefine_line|#define IPMI_GET_DEVICE_ID_CMD&t;&t;0x01
DECL|macro|IPMI_CLEAR_MSG_FLAGS_CMD
mdefine_line|#define IPMI_CLEAR_MSG_FLAGS_CMD&t;0x30
DECL|macro|IPMI_GET_MSG_FLAGS_CMD
mdefine_line|#define IPMI_GET_MSG_FLAGS_CMD&t;&t;0x31
DECL|macro|IPMI_SEND_MSG_CMD
mdefine_line|#define IPMI_SEND_MSG_CMD&t;&t;0x34
DECL|macro|IPMI_GET_MSG_CMD
mdefine_line|#define IPMI_GET_MSG_CMD&t;&t;0x33
DECL|macro|IPMI_SET_BMC_GLOBAL_ENABLES_CMD
mdefine_line|#define IPMI_SET_BMC_GLOBAL_ENABLES_CMD&t;0x2e
DECL|macro|IPMI_GET_BMC_GLOBAL_ENABLES_CMD
mdefine_line|#define IPMI_GET_BMC_GLOBAL_ENABLES_CMD&t;0x2f
DECL|macro|IPMI_READ_EVENT_MSG_BUFFER_CMD
mdefine_line|#define IPMI_READ_EVENT_MSG_BUFFER_CMD&t;0x35
DECL|macro|IPMI_GET_CHANNEL_INFO_CMD
mdefine_line|#define IPMI_GET_CHANNEL_INFO_CMD&t;0x42
DECL|macro|IPMI_NETFN_STORAGE_REQUEST
mdefine_line|#define IPMI_NETFN_STORAGE_REQUEST&t;&t;0x0a
DECL|macro|IPMI_NETFN_STORAGE_RESPONSE
mdefine_line|#define IPMI_NETFN_STORAGE_RESPONSE&t;&t;0x0b
DECL|macro|IPMI_ADD_SEL_ENTRY_CMD
mdefine_line|#define IPMI_ADD_SEL_ENTRY_CMD&t;&t;0x44
multiline_comment|/* The default slave address */
DECL|macro|IPMI_BMC_SLAVE_ADDR
mdefine_line|#define IPMI_BMC_SLAVE_ADDR&t;0x20
multiline_comment|/* The BT interface on high-end HP systems supports up to 255 bytes in&n; * one transfer.  Its &quot;virtual&quot; BMC supports some commands that are longer&n; * than 128 bytes.  Use the full 256, plus NetFn/LUN, Cmd, cCode, plus&n; * some overhead.  It would be nice to base this on the &quot;BT Capabilities&quot;&n; * but that&squot;s too hard to propagate to the rest of the driver. */
DECL|macro|IPMI_MAX_MSG_LENGTH
mdefine_line|#define IPMI_MAX_MSG_LENGTH&t;272&t;/* multiple of 16 */
DECL|macro|IPMI_CC_NO_ERROR
mdefine_line|#define IPMI_CC_NO_ERROR&t;&t;0x00
DECL|macro|IPMI_NODE_BUSY_ERR
mdefine_line|#define IPMI_NODE_BUSY_ERR&t;&t;0xc0
DECL|macro|IPMI_INVALID_COMMAND_ERR
mdefine_line|#define IPMI_INVALID_COMMAND_ERR&t;0xc1
DECL|macro|IPMI_ERR_MSG_TRUNCATED
mdefine_line|#define IPMI_ERR_MSG_TRUNCATED&t;&t;0xc6
DECL|macro|IPMI_LOST_ARBITRATION_ERR
mdefine_line|#define IPMI_LOST_ARBITRATION_ERR&t;0x81
DECL|macro|IPMI_ERR_UNSPECIFIED
mdefine_line|#define IPMI_ERR_UNSPECIFIED&t;&t;0xff
DECL|macro|IPMI_CHANNEL_PROTOCOL_IPMB
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_IPMB&t;1
DECL|macro|IPMI_CHANNEL_PROTOCOL_ICMB
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_ICMB&t;2
DECL|macro|IPMI_CHANNEL_PROTOCOL_SMBUS
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_SMBUS&t;4
DECL|macro|IPMI_CHANNEL_PROTOCOL_KCS
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_KCS&t;5
DECL|macro|IPMI_CHANNEL_PROTOCOL_SMIC
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_SMIC&t;6
DECL|macro|IPMI_CHANNEL_PROTOCOL_BT10
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_BT10&t;7
DECL|macro|IPMI_CHANNEL_PROTOCOL_BT15
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_BT15&t;8
DECL|macro|IPMI_CHANNEL_PROTOCOL_TMODE
mdefine_line|#define IPMI_CHANNEL_PROTOCOL_TMODE&t;9
DECL|macro|IPMI_CHANNEL_MEDIUM_IPMB
mdefine_line|#define IPMI_CHANNEL_MEDIUM_IPMB&t;1
DECL|macro|IPMI_CHANNEL_MEDIUM_ICMB10
mdefine_line|#define IPMI_CHANNEL_MEDIUM_ICMB10&t;2
DECL|macro|IPMI_CHANNEL_MEDIUM_ICMB09
mdefine_line|#define IPMI_CHANNEL_MEDIUM_ICMB09&t;3
DECL|macro|IPMI_CHANNEL_MEDIUM_8023LAN
mdefine_line|#define IPMI_CHANNEL_MEDIUM_8023LAN&t;4
DECL|macro|IPMI_CHANNEL_MEDIUM_ASYNC
mdefine_line|#define IPMI_CHANNEL_MEDIUM_ASYNC&t;5
DECL|macro|IPMI_CHANNEL_MEDIUM_OTHER_LAN
mdefine_line|#define IPMI_CHANNEL_MEDIUM_OTHER_LAN&t;6
DECL|macro|IPMI_CHANNEL_MEDIUM_PCI_SMBUS
mdefine_line|#define IPMI_CHANNEL_MEDIUM_PCI_SMBUS&t;7
DECL|macro|IPMI_CHANNEL_MEDIUM_SMBUS1
mdefine_line|#define IPMI_CHANNEL_MEDIUM_SMBUS1&t;8
DECL|macro|IPMI_CHANNEL_MEDIUM_SMBUS2
mdefine_line|#define IPMI_CHANNEL_MEDIUM_SMBUS2&t;9
DECL|macro|IPMI_CHANNEL_MEDIUM_USB1
mdefine_line|#define IPMI_CHANNEL_MEDIUM_USB1&t;10
DECL|macro|IPMI_CHANNEL_MEDIUM_USB2
mdefine_line|#define IPMI_CHANNEL_MEDIUM_USB2&t;11
DECL|macro|IPMI_CHANNEL_MEDIUM_SYSINTF
mdefine_line|#define IPMI_CHANNEL_MEDIUM_SYSINTF&t;12
macro_line|#endif /* __LINUX_IPMI_MSGDEFS_H */
eof
