multiline_comment|/*&n; * cistpl.h 1.34 2000/06/19 23:18:12&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_CISTPL_H
DECL|macro|_LINUX_CISTPL_H
mdefine_line|#define _LINUX_CISTPL_H
DECL|macro|CISTPL_NULL
mdefine_line|#define CISTPL_NULL&t;&t;0x00
DECL|macro|CISTPL_DEVICE
mdefine_line|#define CISTPL_DEVICE&t;&t;0x01
DECL|macro|CISTPL_LONGLINK_CB
mdefine_line|#define CISTPL_LONGLINK_CB&t;0x02
DECL|macro|CISTPL_INDIRECT
mdefine_line|#define CISTPL_INDIRECT&t;&t;0x03
DECL|macro|CISTPL_CONFIG_CB
mdefine_line|#define CISTPL_CONFIG_CB&t;0x04
DECL|macro|CISTPL_CFTABLE_ENTRY_CB
mdefine_line|#define CISTPL_CFTABLE_ENTRY_CB&t;0x05
DECL|macro|CISTPL_LONGLINK_MFC
mdefine_line|#define CISTPL_LONGLINK_MFC&t;0x06
DECL|macro|CISTPL_BAR
mdefine_line|#define CISTPL_BAR&t;&t;0x07
DECL|macro|CISTPL_PWR_MGMNT
mdefine_line|#define CISTPL_PWR_MGMNT&t;0x08
DECL|macro|CISTPL_EXTDEVICE
mdefine_line|#define CISTPL_EXTDEVICE&t;0x09
DECL|macro|CISTPL_CHECKSUM
mdefine_line|#define CISTPL_CHECKSUM&t;&t;0x10
DECL|macro|CISTPL_LONGLINK_A
mdefine_line|#define CISTPL_LONGLINK_A&t;0x11
DECL|macro|CISTPL_LONGLINK_C
mdefine_line|#define CISTPL_LONGLINK_C&t;0x12
DECL|macro|CISTPL_LINKTARGET
mdefine_line|#define CISTPL_LINKTARGET&t;0x13
DECL|macro|CISTPL_NO_LINK
mdefine_line|#define CISTPL_NO_LINK&t;&t;0x14
DECL|macro|CISTPL_VERS_1
mdefine_line|#define CISTPL_VERS_1&t;&t;0x15
DECL|macro|CISTPL_ALTSTR
mdefine_line|#define CISTPL_ALTSTR&t;&t;0x16
DECL|macro|CISTPL_DEVICE_A
mdefine_line|#define CISTPL_DEVICE_A&t;&t;0x17
DECL|macro|CISTPL_JEDEC_C
mdefine_line|#define CISTPL_JEDEC_C&t;&t;0x18
DECL|macro|CISTPL_JEDEC_A
mdefine_line|#define CISTPL_JEDEC_A&t;&t;0x19
DECL|macro|CISTPL_CONFIG
mdefine_line|#define CISTPL_CONFIG&t;&t;0x1a
DECL|macro|CISTPL_CFTABLE_ENTRY
mdefine_line|#define CISTPL_CFTABLE_ENTRY&t;0x1b
DECL|macro|CISTPL_DEVICE_OC
mdefine_line|#define CISTPL_DEVICE_OC&t;0x1c
DECL|macro|CISTPL_DEVICE_OA
mdefine_line|#define CISTPL_DEVICE_OA&t;0x1d
DECL|macro|CISTPL_DEVICE_GEO
mdefine_line|#define CISTPL_DEVICE_GEO&t;0x1e
DECL|macro|CISTPL_DEVICE_GEO_A
mdefine_line|#define CISTPL_DEVICE_GEO_A&t;0x1f
DECL|macro|CISTPL_MANFID
mdefine_line|#define CISTPL_MANFID&t;&t;0x20
DECL|macro|CISTPL_FUNCID
mdefine_line|#define CISTPL_FUNCID&t;&t;0x21
DECL|macro|CISTPL_FUNCE
mdefine_line|#define CISTPL_FUNCE&t;&t;0x22
DECL|macro|CISTPL_SWIL
mdefine_line|#define CISTPL_SWIL&t;&t;0x23
DECL|macro|CISTPL_END
mdefine_line|#define CISTPL_END&t;&t;0xff
multiline_comment|/* Layer 2 tuples */
DECL|macro|CISTPL_VERS_2
mdefine_line|#define CISTPL_VERS_2&t;&t;0x40
DECL|macro|CISTPL_FORMAT
mdefine_line|#define CISTPL_FORMAT&t;&t;0x41
DECL|macro|CISTPL_GEOMETRY
mdefine_line|#define CISTPL_GEOMETRY&t;&t;0x42
DECL|macro|CISTPL_BYTEORDER
mdefine_line|#define CISTPL_BYTEORDER&t;0x43
DECL|macro|CISTPL_DATE
mdefine_line|#define CISTPL_DATE&t;&t;0x44
DECL|macro|CISTPL_BATTERY
mdefine_line|#define CISTPL_BATTERY&t;&t;0x45
DECL|macro|CISTPL_FORMAT_A
mdefine_line|#define CISTPL_FORMAT_A&t;&t;0x47
multiline_comment|/* Layer 3 tuples */
DECL|macro|CISTPL_ORG
mdefine_line|#define CISTPL_ORG&t;&t;0x46
DECL|macro|CISTPL_SPCL
mdefine_line|#define CISTPL_SPCL&t;&t;0x90
DECL|struct|cistpl_longlink_t
r_typedef
r_struct
id|cistpl_longlink_t
(brace
DECL|member|addr
id|u_int
id|addr
suffix:semicolon
DECL|typedef|cistpl_longlink_t
)brace
id|cistpl_longlink_t
suffix:semicolon
DECL|struct|cistpl_checksum_t
r_typedef
r_struct
id|cistpl_checksum_t
(brace
DECL|member|addr
id|u_short
id|addr
suffix:semicolon
DECL|member|len
id|u_short
id|len
suffix:semicolon
DECL|member|sum
id|u_char
id|sum
suffix:semicolon
DECL|typedef|cistpl_checksum_t
)brace
id|cistpl_checksum_t
suffix:semicolon
DECL|macro|CISTPL_MAX_FUNCTIONS
mdefine_line|#define CISTPL_MAX_FUNCTIONS&t;8
DECL|macro|CISTPL_MFC_ATTR
mdefine_line|#define CISTPL_MFC_ATTR&t;&t;0x00
DECL|macro|CISTPL_MFC_COMMON
mdefine_line|#define CISTPL_MFC_COMMON&t;0x01
DECL|struct|cistpl_longlink_mfc_t
r_typedef
r_struct
id|cistpl_longlink_mfc_t
(brace
DECL|member|nfn
id|u_char
id|nfn
suffix:semicolon
r_struct
(brace
DECL|member|space
id|u_char
id|space
suffix:semicolon
DECL|member|addr
id|u_int
id|addr
suffix:semicolon
DECL|member|fn
)brace
id|fn
(braket
id|CISTPL_MAX_FUNCTIONS
)braket
suffix:semicolon
DECL|typedef|cistpl_longlink_mfc_t
)brace
id|cistpl_longlink_mfc_t
suffix:semicolon
DECL|macro|CISTPL_MAX_ALTSTR_STRINGS
mdefine_line|#define CISTPL_MAX_ALTSTR_STRINGS&t;4
DECL|struct|cistpl_altstr_t
r_typedef
r_struct
id|cistpl_altstr_t
(brace
DECL|member|ns
id|u_char
id|ns
suffix:semicolon
DECL|member|ofs
id|u_char
id|ofs
(braket
id|CISTPL_MAX_ALTSTR_STRINGS
)braket
suffix:semicolon
DECL|member|str
r_char
id|str
(braket
l_int|254
)braket
suffix:semicolon
DECL|typedef|cistpl_altstr_t
)brace
id|cistpl_altstr_t
suffix:semicolon
DECL|macro|CISTPL_DTYPE_NULL
mdefine_line|#define CISTPL_DTYPE_NULL&t;0x00
DECL|macro|CISTPL_DTYPE_ROM
mdefine_line|#define CISTPL_DTYPE_ROM&t;0x01
DECL|macro|CISTPL_DTYPE_OTPROM
mdefine_line|#define CISTPL_DTYPE_OTPROM&t;0x02
DECL|macro|CISTPL_DTYPE_EPROM
mdefine_line|#define CISTPL_DTYPE_EPROM&t;0x03
DECL|macro|CISTPL_DTYPE_EEPROM
mdefine_line|#define CISTPL_DTYPE_EEPROM&t;0x04
DECL|macro|CISTPL_DTYPE_FLASH
mdefine_line|#define CISTPL_DTYPE_FLASH&t;0x05
DECL|macro|CISTPL_DTYPE_SRAM
mdefine_line|#define CISTPL_DTYPE_SRAM&t;0x06
DECL|macro|CISTPL_DTYPE_DRAM
mdefine_line|#define CISTPL_DTYPE_DRAM&t;0x07
DECL|macro|CISTPL_DTYPE_FUNCSPEC
mdefine_line|#define CISTPL_DTYPE_FUNCSPEC&t;0x0d
DECL|macro|CISTPL_DTYPE_EXTEND
mdefine_line|#define CISTPL_DTYPE_EXTEND&t;0x0e
DECL|macro|CISTPL_MAX_DEVICES
mdefine_line|#define CISTPL_MAX_DEVICES&t;4
DECL|struct|cistpl_device_t
r_typedef
r_struct
id|cistpl_device_t
(brace
DECL|member|ndev
id|u_char
id|ndev
suffix:semicolon
r_struct
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|wp
id|u_char
id|wp
suffix:semicolon
DECL|member|speed
id|u_int
id|speed
suffix:semicolon
DECL|member|size
id|u_int
id|size
suffix:semicolon
DECL|member|dev
)brace
id|dev
(braket
id|CISTPL_MAX_DEVICES
)braket
suffix:semicolon
DECL|typedef|cistpl_device_t
)brace
id|cistpl_device_t
suffix:semicolon
DECL|macro|CISTPL_DEVICE_MWAIT
mdefine_line|#define CISTPL_DEVICE_MWAIT&t;0x01
DECL|macro|CISTPL_DEVICE_3VCC
mdefine_line|#define CISTPL_DEVICE_3VCC&t;0x02
DECL|struct|cistpl_device_o_t
r_typedef
r_struct
id|cistpl_device_o_t
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|device
id|cistpl_device_t
id|device
suffix:semicolon
DECL|typedef|cistpl_device_o_t
)brace
id|cistpl_device_o_t
suffix:semicolon
DECL|macro|CISTPL_VERS_1_MAX_PROD_STRINGS
mdefine_line|#define CISTPL_VERS_1_MAX_PROD_STRINGS&t;4
DECL|struct|cistpl_vers_1_t
r_typedef
r_struct
id|cistpl_vers_1_t
(brace
DECL|member|major
id|u_char
id|major
suffix:semicolon
DECL|member|minor
id|u_char
id|minor
suffix:semicolon
DECL|member|ns
id|u_char
id|ns
suffix:semicolon
DECL|member|ofs
id|u_char
id|ofs
(braket
id|CISTPL_VERS_1_MAX_PROD_STRINGS
)braket
suffix:semicolon
DECL|member|str
r_char
id|str
(braket
l_int|254
)braket
suffix:semicolon
DECL|typedef|cistpl_vers_1_t
)brace
id|cistpl_vers_1_t
suffix:semicolon
DECL|struct|cistpl_jedec_t
r_typedef
r_struct
id|cistpl_jedec_t
(brace
DECL|member|nid
id|u_char
id|nid
suffix:semicolon
r_struct
(brace
DECL|member|mfr
id|u_char
id|mfr
suffix:semicolon
DECL|member|info
id|u_char
id|info
suffix:semicolon
DECL|member|id
)brace
id|id
(braket
id|CISTPL_MAX_DEVICES
)braket
suffix:semicolon
DECL|typedef|cistpl_jedec_t
)brace
id|cistpl_jedec_t
suffix:semicolon
DECL|struct|cistpl_manfid_t
r_typedef
r_struct
id|cistpl_manfid_t
(brace
DECL|member|manf
id|u_short
id|manf
suffix:semicolon
DECL|member|card
id|u_short
id|card
suffix:semicolon
DECL|typedef|cistpl_manfid_t
)brace
id|cistpl_manfid_t
suffix:semicolon
DECL|macro|CISTPL_FUNCID_MULTI
mdefine_line|#define CISTPL_FUNCID_MULTI&t;0x00
DECL|macro|CISTPL_FUNCID_MEMORY
mdefine_line|#define CISTPL_FUNCID_MEMORY&t;0x01
DECL|macro|CISTPL_FUNCID_SERIAL
mdefine_line|#define CISTPL_FUNCID_SERIAL&t;0x02
DECL|macro|CISTPL_FUNCID_PARALLEL
mdefine_line|#define CISTPL_FUNCID_PARALLEL&t;0x03
DECL|macro|CISTPL_FUNCID_FIXED
mdefine_line|#define CISTPL_FUNCID_FIXED&t;0x04
DECL|macro|CISTPL_FUNCID_VIDEO
mdefine_line|#define CISTPL_FUNCID_VIDEO&t;0x05
DECL|macro|CISTPL_FUNCID_NETWORK
mdefine_line|#define CISTPL_FUNCID_NETWORK&t;0x06
DECL|macro|CISTPL_FUNCID_AIMS
mdefine_line|#define CISTPL_FUNCID_AIMS&t;0x07
DECL|macro|CISTPL_FUNCID_SCSI
mdefine_line|#define CISTPL_FUNCID_SCSI&t;0x08
DECL|macro|CISTPL_SYSINIT_POST
mdefine_line|#define CISTPL_SYSINIT_POST&t;0x01
DECL|macro|CISTPL_SYSINIT_ROM
mdefine_line|#define CISTPL_SYSINIT_ROM&t;0x02
DECL|struct|cistpl_funcid_t
r_typedef
r_struct
id|cistpl_funcid_t
(brace
DECL|member|func
id|u_char
id|func
suffix:semicolon
DECL|member|sysinit
id|u_char
id|sysinit
suffix:semicolon
DECL|typedef|cistpl_funcid_t
)brace
id|cistpl_funcid_t
suffix:semicolon
DECL|struct|cistpl_funce_t
r_typedef
r_struct
id|cistpl_funce_t
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|data
id|u_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|cistpl_funce_t
)brace
id|cistpl_funce_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    Modem Function Extension Tuples&n;&n;======================================================================*/
DECL|macro|CISTPL_FUNCE_SERIAL_IF
mdefine_line|#define CISTPL_FUNCE_SERIAL_IF&t;&t;0x00
DECL|macro|CISTPL_FUNCE_SERIAL_CAP
mdefine_line|#define CISTPL_FUNCE_SERIAL_CAP&t;&t;0x01
DECL|macro|CISTPL_FUNCE_SERIAL_SERV_DATA
mdefine_line|#define CISTPL_FUNCE_SERIAL_SERV_DATA&t;0x02
DECL|macro|CISTPL_FUNCE_SERIAL_SERV_FAX
mdefine_line|#define CISTPL_FUNCE_SERIAL_SERV_FAX&t;0x03
DECL|macro|CISTPL_FUNCE_SERIAL_SERV_VOICE
mdefine_line|#define CISTPL_FUNCE_SERIAL_SERV_VOICE&t;0x04
DECL|macro|CISTPL_FUNCE_SERIAL_CAP_DATA
mdefine_line|#define CISTPL_FUNCE_SERIAL_CAP_DATA&t;0x05
DECL|macro|CISTPL_FUNCE_SERIAL_CAP_FAX
mdefine_line|#define CISTPL_FUNCE_SERIAL_CAP_FAX&t;0x06
DECL|macro|CISTPL_FUNCE_SERIAL_CAP_VOICE
mdefine_line|#define CISTPL_FUNCE_SERIAL_CAP_VOICE&t;0x07
DECL|macro|CISTPL_FUNCE_SERIAL_IF_DATA
mdefine_line|#define CISTPL_FUNCE_SERIAL_IF_DATA&t;0x08
DECL|macro|CISTPL_FUNCE_SERIAL_IF_FAX
mdefine_line|#define CISTPL_FUNCE_SERIAL_IF_FAX&t;0x09
DECL|macro|CISTPL_FUNCE_SERIAL_IF_VOICE
mdefine_line|#define CISTPL_FUNCE_SERIAL_IF_VOICE&t;0x0a
multiline_comment|/* UART identification */
DECL|macro|CISTPL_SERIAL_UART_8250
mdefine_line|#define CISTPL_SERIAL_UART_8250&t;&t;0x00
DECL|macro|CISTPL_SERIAL_UART_16450
mdefine_line|#define CISTPL_SERIAL_UART_16450&t;0x01
DECL|macro|CISTPL_SERIAL_UART_16550
mdefine_line|#define CISTPL_SERIAL_UART_16550&t;0x02
DECL|macro|CISTPL_SERIAL_UART_8251
mdefine_line|#define CISTPL_SERIAL_UART_8251&t;&t;0x03
DECL|macro|CISTPL_SERIAL_UART_8530
mdefine_line|#define CISTPL_SERIAL_UART_8530&t;&t;0x04
DECL|macro|CISTPL_SERIAL_UART_85230
mdefine_line|#define CISTPL_SERIAL_UART_85230&t;0x05
multiline_comment|/* UART capabilities */
DECL|macro|CISTPL_SERIAL_UART_SPACE
mdefine_line|#define CISTPL_SERIAL_UART_SPACE&t;0x01
DECL|macro|CISTPL_SERIAL_UART_MARK
mdefine_line|#define CISTPL_SERIAL_UART_MARK&t;&t;0x02
DECL|macro|CISTPL_SERIAL_UART_ODD
mdefine_line|#define CISTPL_SERIAL_UART_ODD&t;&t;0x04
DECL|macro|CISTPL_SERIAL_UART_EVEN
mdefine_line|#define CISTPL_SERIAL_UART_EVEN&t;&t;0x08
DECL|macro|CISTPL_SERIAL_UART_5BIT
mdefine_line|#define CISTPL_SERIAL_UART_5BIT&t;&t;0x01
DECL|macro|CISTPL_SERIAL_UART_6BIT
mdefine_line|#define CISTPL_SERIAL_UART_6BIT&t;&t;0x02
DECL|macro|CISTPL_SERIAL_UART_7BIT
mdefine_line|#define CISTPL_SERIAL_UART_7BIT&t;&t;0x04
DECL|macro|CISTPL_SERIAL_UART_8BIT
mdefine_line|#define CISTPL_SERIAL_UART_8BIT&t;&t;0x08
DECL|macro|CISTPL_SERIAL_UART_1STOP
mdefine_line|#define CISTPL_SERIAL_UART_1STOP&t;0x10
DECL|macro|CISTPL_SERIAL_UART_MSTOP
mdefine_line|#define CISTPL_SERIAL_UART_MSTOP&t;0x20
DECL|macro|CISTPL_SERIAL_UART_2STOP
mdefine_line|#define CISTPL_SERIAL_UART_2STOP&t;0x40
DECL|struct|cistpl_serial_t
r_typedef
r_struct
id|cistpl_serial_t
(brace
DECL|member|uart_type
id|u_char
id|uart_type
suffix:semicolon
DECL|member|uart_cap_0
id|u_char
id|uart_cap_0
suffix:semicolon
DECL|member|uart_cap_1
id|u_char
id|uart_cap_1
suffix:semicolon
DECL|typedef|cistpl_serial_t
)brace
id|cistpl_serial_t
suffix:semicolon
DECL|struct|cistpl_modem_cap_t
r_typedef
r_struct
id|cistpl_modem_cap_t
(brace
DECL|member|flow
id|u_char
id|flow
suffix:semicolon
DECL|member|cmd_buf
id|u_char
id|cmd_buf
suffix:semicolon
DECL|member|rcv_buf_0
DECL|member|rcv_buf_1
DECL|member|rcv_buf_2
id|u_char
id|rcv_buf_0
comma
id|rcv_buf_1
comma
id|rcv_buf_2
suffix:semicolon
DECL|member|xmit_buf_0
DECL|member|xmit_buf_1
DECL|member|xmit_buf_2
id|u_char
id|xmit_buf_0
comma
id|xmit_buf_1
comma
id|xmit_buf_2
suffix:semicolon
DECL|typedef|cistpl_modem_cap_t
)brace
id|cistpl_modem_cap_t
suffix:semicolon
DECL|macro|CISTPL_SERIAL_MOD_103
mdefine_line|#define CISTPL_SERIAL_MOD_103&t;&t;0x01
DECL|macro|CISTPL_SERIAL_MOD_V21
mdefine_line|#define CISTPL_SERIAL_MOD_V21&t;&t;0x02
DECL|macro|CISTPL_SERIAL_MOD_V23
mdefine_line|#define CISTPL_SERIAL_MOD_V23&t;&t;0x04
DECL|macro|CISTPL_SERIAL_MOD_V22
mdefine_line|#define CISTPL_SERIAL_MOD_V22&t;&t;0x08
DECL|macro|CISTPL_SERIAL_MOD_212A
mdefine_line|#define CISTPL_SERIAL_MOD_212A&t;&t;0x10
DECL|macro|CISTPL_SERIAL_MOD_V22BIS
mdefine_line|#define CISTPL_SERIAL_MOD_V22BIS&t;0x20
DECL|macro|CISTPL_SERIAL_MOD_V26
mdefine_line|#define CISTPL_SERIAL_MOD_V26&t;&t;0x40
DECL|macro|CISTPL_SERIAL_MOD_V26BIS
mdefine_line|#define CISTPL_SERIAL_MOD_V26BIS&t;0x80
DECL|macro|CISTPL_SERIAL_MOD_V27BIS
mdefine_line|#define CISTPL_SERIAL_MOD_V27BIS&t;0x01
DECL|macro|CISTPL_SERIAL_MOD_V29
mdefine_line|#define CISTPL_SERIAL_MOD_V29&t;&t;0x02
DECL|macro|CISTPL_SERIAL_MOD_V32
mdefine_line|#define CISTPL_SERIAL_MOD_V32&t;&t;0x04
DECL|macro|CISTPL_SERIAL_MOD_V32BIS
mdefine_line|#define CISTPL_SERIAL_MOD_V32BIS&t;0x08
DECL|macro|CISTPL_SERIAL_MOD_V34
mdefine_line|#define CISTPL_SERIAL_MOD_V34&t;&t;0x10
DECL|macro|CISTPL_SERIAL_ERR_MNP2_4
mdefine_line|#define CISTPL_SERIAL_ERR_MNP2_4&t;0x01
DECL|macro|CISTPL_SERIAL_ERR_V42_LAPM
mdefine_line|#define CISTPL_SERIAL_ERR_V42_LAPM&t;0x02
DECL|macro|CISTPL_SERIAL_CMPR_V42BIS
mdefine_line|#define CISTPL_SERIAL_CMPR_V42BIS&t;0x01
DECL|macro|CISTPL_SERIAL_CMPR_MNP5
mdefine_line|#define CISTPL_SERIAL_CMPR_MNP5&t;&t;0x02
DECL|macro|CISTPL_SERIAL_CMD_AT1
mdefine_line|#define CISTPL_SERIAL_CMD_AT1&t;&t;0x01
DECL|macro|CISTPL_SERIAL_CMD_AT2
mdefine_line|#define CISTPL_SERIAL_CMD_AT2&t;&t;0x02
DECL|macro|CISTPL_SERIAL_CMD_AT3
mdefine_line|#define CISTPL_SERIAL_CMD_AT3&t;&t;0x04
DECL|macro|CISTPL_SERIAL_CMD_MNP_AT
mdefine_line|#define CISTPL_SERIAL_CMD_MNP_AT&t;0x08
DECL|macro|CISTPL_SERIAL_CMD_V25BIS
mdefine_line|#define CISTPL_SERIAL_CMD_V25BIS&t;0x10
DECL|macro|CISTPL_SERIAL_CMD_V25A
mdefine_line|#define CISTPL_SERIAL_CMD_V25A&t;&t;0x20
DECL|macro|CISTPL_SERIAL_CMD_DMCL
mdefine_line|#define CISTPL_SERIAL_CMD_DMCL&t;&t;0x40
DECL|struct|cistpl_data_serv_t
r_typedef
r_struct
id|cistpl_data_serv_t
(brace
DECL|member|max_data_0
id|u_char
id|max_data_0
suffix:semicolon
DECL|member|max_data_1
id|u_char
id|max_data_1
suffix:semicolon
DECL|member|modulation_0
id|u_char
id|modulation_0
suffix:semicolon
DECL|member|modulation_1
id|u_char
id|modulation_1
suffix:semicolon
DECL|member|error_control
id|u_char
id|error_control
suffix:semicolon
DECL|member|compression
id|u_char
id|compression
suffix:semicolon
DECL|member|cmd_protocol
id|u_char
id|cmd_protocol
suffix:semicolon
DECL|member|escape
id|u_char
id|escape
suffix:semicolon
DECL|member|encrypt
id|u_char
id|encrypt
suffix:semicolon
DECL|member|misc_features
id|u_char
id|misc_features
suffix:semicolon
DECL|member|ccitt_code
id|u_char
id|ccitt_code
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|cistpl_data_serv_t
)brace
id|cistpl_data_serv_t
suffix:semicolon
DECL|struct|cistpl_fax_serv_t
r_typedef
r_struct
id|cistpl_fax_serv_t
(brace
DECL|member|max_data_0
id|u_char
id|max_data_0
suffix:semicolon
DECL|member|max_data_1
id|u_char
id|max_data_1
suffix:semicolon
DECL|member|modulation
id|u_char
id|modulation
suffix:semicolon
DECL|member|encrypt
id|u_char
id|encrypt
suffix:semicolon
DECL|member|features_0
id|u_char
id|features_0
suffix:semicolon
DECL|member|features_1
id|u_char
id|features_1
suffix:semicolon
DECL|member|ccitt_code
id|u_char
id|ccitt_code
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|cistpl_fax_serv_t
)brace
id|cistpl_fax_serv_t
suffix:semicolon
DECL|struct|cistpl_voice_serv_t
r_typedef
r_struct
id|cistpl_voice_serv_t
(brace
DECL|member|max_data_0
id|u_char
id|max_data_0
suffix:semicolon
DECL|member|max_data_1
id|u_char
id|max_data_1
suffix:semicolon
DECL|typedef|cistpl_voice_serv_t
)brace
id|cistpl_voice_serv_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    LAN Function Extension Tuples&n;&n;======================================================================*/
DECL|macro|CISTPL_FUNCE_LAN_TECH
mdefine_line|#define CISTPL_FUNCE_LAN_TECH&t;&t;0x01
DECL|macro|CISTPL_FUNCE_LAN_SPEED
mdefine_line|#define CISTPL_FUNCE_LAN_SPEED&t;&t;0x02
DECL|macro|CISTPL_FUNCE_LAN_MEDIA
mdefine_line|#define CISTPL_FUNCE_LAN_MEDIA&t;&t;0x03
DECL|macro|CISTPL_FUNCE_LAN_NODE_ID
mdefine_line|#define CISTPL_FUNCE_LAN_NODE_ID&t;0x04
DECL|macro|CISTPL_FUNCE_LAN_CONNECTOR
mdefine_line|#define CISTPL_FUNCE_LAN_CONNECTOR&t;0x05
multiline_comment|/* LAN technologies */
DECL|macro|CISTPL_LAN_TECH_ARCNET
mdefine_line|#define CISTPL_LAN_TECH_ARCNET&t;&t;0x01
DECL|macro|CISTPL_LAN_TECH_ETHERNET
mdefine_line|#define CISTPL_LAN_TECH_ETHERNET&t;0x02
DECL|macro|CISTPL_LAN_TECH_TOKENRING
mdefine_line|#define CISTPL_LAN_TECH_TOKENRING&t;0x03
DECL|macro|CISTPL_LAN_TECH_LOCALTALK
mdefine_line|#define CISTPL_LAN_TECH_LOCALTALK&t;0x04
DECL|macro|CISTPL_LAN_TECH_FDDI
mdefine_line|#define CISTPL_LAN_TECH_FDDI&t;&t;0x05
DECL|macro|CISTPL_LAN_TECH_ATM
mdefine_line|#define CISTPL_LAN_TECH_ATM&t;&t;0x06
DECL|macro|CISTPL_LAN_TECH_WIRELESS
mdefine_line|#define CISTPL_LAN_TECH_WIRELESS&t;0x07
DECL|struct|cistpl_lan_tech_t
r_typedef
r_struct
id|cistpl_lan_tech_t
(brace
DECL|member|tech
id|u_char
id|tech
suffix:semicolon
DECL|typedef|cistpl_lan_tech_t
)brace
id|cistpl_lan_tech_t
suffix:semicolon
DECL|struct|cistpl_lan_speed_t
r_typedef
r_struct
id|cistpl_lan_speed_t
(brace
DECL|member|speed
id|u_int
id|speed
suffix:semicolon
DECL|typedef|cistpl_lan_speed_t
)brace
id|cistpl_lan_speed_t
suffix:semicolon
multiline_comment|/* LAN media definitions */
DECL|macro|CISTPL_LAN_MEDIA_UTP
mdefine_line|#define CISTPL_LAN_MEDIA_UTP&t;&t;0x01
DECL|macro|CISTPL_LAN_MEDIA_STP
mdefine_line|#define CISTPL_LAN_MEDIA_STP&t;&t;0x02
DECL|macro|CISTPL_LAN_MEDIA_THIN_COAX
mdefine_line|#define CISTPL_LAN_MEDIA_THIN_COAX&t;0x03
DECL|macro|CISTPL_LAN_MEDIA_THICK_COAX
mdefine_line|#define CISTPL_LAN_MEDIA_THICK_COAX&t;0x04
DECL|macro|CISTPL_LAN_MEDIA_FIBER
mdefine_line|#define CISTPL_LAN_MEDIA_FIBER&t;&t;0x05
DECL|macro|CISTPL_LAN_MEDIA_900MHZ
mdefine_line|#define CISTPL_LAN_MEDIA_900MHZ&t;&t;0x06
DECL|macro|CISTPL_LAN_MEDIA_2GHZ
mdefine_line|#define CISTPL_LAN_MEDIA_2GHZ&t;&t;0x07
DECL|macro|CISTPL_LAN_MEDIA_5GHZ
mdefine_line|#define CISTPL_LAN_MEDIA_5GHZ&t;&t;0x08
DECL|macro|CISTPL_LAN_MEDIA_DIFF_IR
mdefine_line|#define CISTPL_LAN_MEDIA_DIFF_IR&t;0x09
DECL|macro|CISTPL_LAN_MEDIA_PTP_IR
mdefine_line|#define CISTPL_LAN_MEDIA_PTP_IR&t;&t;0x0a
DECL|struct|cistpl_lan_media_t
r_typedef
r_struct
id|cistpl_lan_media_t
(brace
DECL|member|media
id|u_char
id|media
suffix:semicolon
DECL|typedef|cistpl_lan_media_t
)brace
id|cistpl_lan_media_t
suffix:semicolon
DECL|struct|cistpl_lan_node_id_t
r_typedef
r_struct
id|cistpl_lan_node_id_t
(brace
DECL|member|nb
id|u_char
id|nb
suffix:semicolon
DECL|member|id
id|u_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|cistpl_lan_node_id_t
)brace
id|cistpl_lan_node_id_t
suffix:semicolon
DECL|struct|cistpl_lan_connector_t
r_typedef
r_struct
id|cistpl_lan_connector_t
(brace
DECL|member|code
id|u_char
id|code
suffix:semicolon
DECL|typedef|cistpl_lan_connector_t
)brace
id|cistpl_lan_connector_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    IDE Function Extension Tuples&n;&n;======================================================================*/
DECL|macro|CISTPL_IDE_INTERFACE
mdefine_line|#define CISTPL_IDE_INTERFACE&t;&t;0x01
DECL|struct|cistpl_ide_interface_t
r_typedef
r_struct
id|cistpl_ide_interface_t
(brace
DECL|member|interface
id|u_char
id|interface
suffix:semicolon
DECL|typedef|cistpl_ide_interface_t
)brace
id|cistpl_ide_interface_t
suffix:semicolon
multiline_comment|/* First feature byte */
DECL|macro|CISTPL_IDE_SILICON
mdefine_line|#define CISTPL_IDE_SILICON&t;&t;0x04
DECL|macro|CISTPL_IDE_UNIQUE
mdefine_line|#define CISTPL_IDE_UNIQUE&t;&t;0x08
DECL|macro|CISTPL_IDE_DUAL
mdefine_line|#define CISTPL_IDE_DUAL&t;&t;&t;0x10
multiline_comment|/* Second feature byte */
DECL|macro|CISTPL_IDE_HAS_SLEEP
mdefine_line|#define CISTPL_IDE_HAS_SLEEP&t;&t;0x01
DECL|macro|CISTPL_IDE_HAS_STANDBY
mdefine_line|#define CISTPL_IDE_HAS_STANDBY&t;&t;0x02
DECL|macro|CISTPL_IDE_HAS_IDLE
mdefine_line|#define CISTPL_IDE_HAS_IDLE&t;&t;0x04
DECL|macro|CISTPL_IDE_LOW_POWER
mdefine_line|#define CISTPL_IDE_LOW_POWER&t;&t;0x08
DECL|macro|CISTPL_IDE_REG_INHIBIT
mdefine_line|#define CISTPL_IDE_REG_INHIBIT&t;&t;0x10
DECL|macro|CISTPL_IDE_HAS_INDEX
mdefine_line|#define CISTPL_IDE_HAS_INDEX&t;&t;0x20
DECL|macro|CISTPL_IDE_IOIS16
mdefine_line|#define CISTPL_IDE_IOIS16&t;&t;0x40
DECL|struct|cistpl_ide_feature_t
r_typedef
r_struct
id|cistpl_ide_feature_t
(brace
DECL|member|feature1
id|u_char
id|feature1
suffix:semicolon
DECL|member|feature2
id|u_char
id|feature2
suffix:semicolon
DECL|typedef|cistpl_ide_feature_t
)brace
id|cistpl_ide_feature_t
suffix:semicolon
DECL|macro|CISTPL_FUNCE_IDE_IFACE
mdefine_line|#define CISTPL_FUNCE_IDE_IFACE&t;&t;0x01
DECL|macro|CISTPL_FUNCE_IDE_MASTER
mdefine_line|#define CISTPL_FUNCE_IDE_MASTER&t;&t;0x02
DECL|macro|CISTPL_FUNCE_IDE_SLAVE
mdefine_line|#define CISTPL_FUNCE_IDE_SLAVE&t;&t;0x03
multiline_comment|/*======================================================================&n;&n;    Configuration Table Entries&n;&n;======================================================================*/
DECL|macro|CISTPL_BAR_SPACE
mdefine_line|#define CISTPL_BAR_SPACE&t;0x07
DECL|macro|CISTPL_BAR_SPACE_IO
mdefine_line|#define CISTPL_BAR_SPACE_IO&t;0x10
DECL|macro|CISTPL_BAR_PREFETCH
mdefine_line|#define CISTPL_BAR_PREFETCH&t;0x20
DECL|macro|CISTPL_BAR_CACHEABLE
mdefine_line|#define CISTPL_BAR_CACHEABLE&t;0x40
DECL|macro|CISTPL_BAR_1MEG_MAP
mdefine_line|#define CISTPL_BAR_1MEG_MAP&t;0x80
DECL|struct|cistpl_bar_t
r_typedef
r_struct
id|cistpl_bar_t
(brace
DECL|member|attr
id|u_char
id|attr
suffix:semicolon
DECL|member|size
id|u_int
id|size
suffix:semicolon
DECL|typedef|cistpl_bar_t
)brace
id|cistpl_bar_t
suffix:semicolon
DECL|struct|cistpl_config_t
r_typedef
r_struct
id|cistpl_config_t
(brace
DECL|member|last_idx
id|u_char
id|last_idx
suffix:semicolon
DECL|member|base
id|u_int
id|base
suffix:semicolon
DECL|member|rmask
id|u_int
id|rmask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|subtuples
id|u_char
id|subtuples
suffix:semicolon
DECL|typedef|cistpl_config_t
)brace
id|cistpl_config_t
suffix:semicolon
multiline_comment|/* These are bits in the &squot;present&squot; field, and indices in &squot;param&squot; */
DECL|macro|CISTPL_POWER_VNOM
mdefine_line|#define CISTPL_POWER_VNOM&t;0
DECL|macro|CISTPL_POWER_VMIN
mdefine_line|#define CISTPL_POWER_VMIN&t;1
DECL|macro|CISTPL_POWER_VMAX
mdefine_line|#define CISTPL_POWER_VMAX&t;2
DECL|macro|CISTPL_POWER_ISTATIC
mdefine_line|#define CISTPL_POWER_ISTATIC&t;3
DECL|macro|CISTPL_POWER_IAVG
mdefine_line|#define CISTPL_POWER_IAVG&t;4
DECL|macro|CISTPL_POWER_IPEAK
mdefine_line|#define CISTPL_POWER_IPEAK&t;5
DECL|macro|CISTPL_POWER_IDOWN
mdefine_line|#define CISTPL_POWER_IDOWN&t;6
DECL|macro|CISTPL_POWER_HIGHZ_OK
mdefine_line|#define CISTPL_POWER_HIGHZ_OK&t;0x01
DECL|macro|CISTPL_POWER_HIGHZ_REQ
mdefine_line|#define CISTPL_POWER_HIGHZ_REQ&t;0x02
DECL|struct|cistpl_power_t
r_typedef
r_struct
id|cistpl_power_t
(brace
DECL|member|present
id|u_char
id|present
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|param
id|u_int
id|param
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|cistpl_power_t
)brace
id|cistpl_power_t
suffix:semicolon
DECL|struct|cistpl_timing_t
r_typedef
r_struct
id|cistpl_timing_t
(brace
DECL|member|wait
DECL|member|waitscale
id|u_int
id|wait
comma
id|waitscale
suffix:semicolon
DECL|member|ready
DECL|member|rdyscale
id|u_int
id|ready
comma
id|rdyscale
suffix:semicolon
DECL|member|reserved
DECL|member|rsvscale
id|u_int
id|reserved
comma
id|rsvscale
suffix:semicolon
DECL|typedef|cistpl_timing_t
)brace
id|cistpl_timing_t
suffix:semicolon
DECL|macro|CISTPL_IO_LINES_MASK
mdefine_line|#define CISTPL_IO_LINES_MASK&t;0x1f
DECL|macro|CISTPL_IO_8BIT
mdefine_line|#define CISTPL_IO_8BIT&t;&t;0x20
DECL|macro|CISTPL_IO_16BIT
mdefine_line|#define CISTPL_IO_16BIT&t;&t;0x40
DECL|macro|CISTPL_IO_RANGE
mdefine_line|#define CISTPL_IO_RANGE&t;&t;0x80
DECL|macro|CISTPL_IO_MAX_WIN
mdefine_line|#define CISTPL_IO_MAX_WIN&t;16
DECL|struct|cistpl_io_t
r_typedef
r_struct
id|cistpl_io_t
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|nwin
id|u_char
id|nwin
suffix:semicolon
r_struct
(brace
DECL|member|base
id|u_int
id|base
suffix:semicolon
DECL|member|len
id|u_int
id|len
suffix:semicolon
DECL|member|win
)brace
id|win
(braket
id|CISTPL_IO_MAX_WIN
)braket
suffix:semicolon
DECL|typedef|cistpl_io_t
)brace
id|cistpl_io_t
suffix:semicolon
DECL|struct|cistpl_irq_t
r_typedef
r_struct
id|cistpl_irq_t
(brace
DECL|member|IRQInfo1
id|u_int
id|IRQInfo1
suffix:semicolon
DECL|member|IRQInfo2
id|u_int
id|IRQInfo2
suffix:semicolon
DECL|typedef|cistpl_irq_t
)brace
id|cistpl_irq_t
suffix:semicolon
DECL|macro|CISTPL_MEM_MAX_WIN
mdefine_line|#define CISTPL_MEM_MAX_WIN&t;8
DECL|struct|cistpl_mem_t
r_typedef
r_struct
id|cistpl_mem_t
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|nwin
id|u_char
id|nwin
suffix:semicolon
r_struct
(brace
DECL|member|len
id|u_int
id|len
suffix:semicolon
DECL|member|card_addr
id|u_int
id|card_addr
suffix:semicolon
DECL|member|host_addr
id|u_int
id|host_addr
suffix:semicolon
DECL|member|win
)brace
id|win
(braket
id|CISTPL_MEM_MAX_WIN
)braket
suffix:semicolon
DECL|typedef|cistpl_mem_t
)brace
id|cistpl_mem_t
suffix:semicolon
DECL|macro|CISTPL_CFTABLE_DEFAULT
mdefine_line|#define CISTPL_CFTABLE_DEFAULT&t;&t;0x0001
DECL|macro|CISTPL_CFTABLE_BVDS
mdefine_line|#define CISTPL_CFTABLE_BVDS&t;&t;0x0002
DECL|macro|CISTPL_CFTABLE_WP
mdefine_line|#define CISTPL_CFTABLE_WP&t;&t;0x0004
DECL|macro|CISTPL_CFTABLE_RDYBSY
mdefine_line|#define CISTPL_CFTABLE_RDYBSY&t;&t;0x0008
DECL|macro|CISTPL_CFTABLE_MWAIT
mdefine_line|#define CISTPL_CFTABLE_MWAIT&t;&t;0x0010
DECL|macro|CISTPL_CFTABLE_AUDIO
mdefine_line|#define CISTPL_CFTABLE_AUDIO&t;&t;0x0800
DECL|macro|CISTPL_CFTABLE_READONLY
mdefine_line|#define CISTPL_CFTABLE_READONLY&t;&t;0x1000
DECL|macro|CISTPL_CFTABLE_PWRDOWN
mdefine_line|#define CISTPL_CFTABLE_PWRDOWN&t;&t;0x2000
DECL|struct|cistpl_cftable_entry_t
r_typedef
r_struct
id|cistpl_cftable_entry_t
(brace
DECL|member|index
id|u_char
id|index
suffix:semicolon
DECL|member|flags
id|u_short
id|flags
suffix:semicolon
DECL|member|interface
id|u_char
id|interface
suffix:semicolon
DECL|member|vcc
DECL|member|vpp1
DECL|member|vpp2
id|cistpl_power_t
id|vcc
comma
id|vpp1
comma
id|vpp2
suffix:semicolon
DECL|member|timing
id|cistpl_timing_t
id|timing
suffix:semicolon
DECL|member|io
id|cistpl_io_t
id|io
suffix:semicolon
DECL|member|irq
id|cistpl_irq_t
id|irq
suffix:semicolon
DECL|member|mem
id|cistpl_mem_t
id|mem
suffix:semicolon
DECL|member|subtuples
id|u_char
id|subtuples
suffix:semicolon
DECL|typedef|cistpl_cftable_entry_t
)brace
id|cistpl_cftable_entry_t
suffix:semicolon
DECL|macro|CISTPL_CFTABLE_MASTER
mdefine_line|#define CISTPL_CFTABLE_MASTER&t;&t;0x000100
DECL|macro|CISTPL_CFTABLE_INVALIDATE
mdefine_line|#define CISTPL_CFTABLE_INVALIDATE&t;0x000200
DECL|macro|CISTPL_CFTABLE_VGA_PALETTE
mdefine_line|#define CISTPL_CFTABLE_VGA_PALETTE&t;0x000400
DECL|macro|CISTPL_CFTABLE_PARITY
mdefine_line|#define CISTPL_CFTABLE_PARITY&t;&t;0x000800
DECL|macro|CISTPL_CFTABLE_WAIT
mdefine_line|#define CISTPL_CFTABLE_WAIT&t;&t;0x001000
DECL|macro|CISTPL_CFTABLE_SERR
mdefine_line|#define CISTPL_CFTABLE_SERR&t;&t;0x002000
DECL|macro|CISTPL_CFTABLE_FAST_BACK
mdefine_line|#define CISTPL_CFTABLE_FAST_BACK&t;0x004000
DECL|macro|CISTPL_CFTABLE_BINARY_AUDIO
mdefine_line|#define CISTPL_CFTABLE_BINARY_AUDIO&t;0x010000
DECL|macro|CISTPL_CFTABLE_PWM_AUDIO
mdefine_line|#define CISTPL_CFTABLE_PWM_AUDIO&t;0x020000
DECL|struct|cistpl_cftable_entry_cb_t
r_typedef
r_struct
id|cistpl_cftable_entry_cb_t
(brace
DECL|member|index
id|u_char
id|index
suffix:semicolon
DECL|member|flags
id|u_int
id|flags
suffix:semicolon
DECL|member|vcc
DECL|member|vpp1
DECL|member|vpp2
id|cistpl_power_t
id|vcc
comma
id|vpp1
comma
id|vpp2
suffix:semicolon
DECL|member|io
id|u_char
id|io
suffix:semicolon
DECL|member|irq
id|cistpl_irq_t
id|irq
suffix:semicolon
DECL|member|mem
id|u_char
id|mem
suffix:semicolon
DECL|member|subtuples
id|u_char
id|subtuples
suffix:semicolon
DECL|typedef|cistpl_cftable_entry_cb_t
)brace
id|cistpl_cftable_entry_cb_t
suffix:semicolon
DECL|struct|cistpl_device_geo_t
r_typedef
r_struct
id|cistpl_device_geo_t
(brace
DECL|member|ngeo
id|u_char
id|ngeo
suffix:semicolon
r_struct
(brace
DECL|member|buswidth
id|u_char
id|buswidth
suffix:semicolon
DECL|member|erase_block
id|u_int
id|erase_block
suffix:semicolon
DECL|member|read_block
id|u_int
id|read_block
suffix:semicolon
DECL|member|write_block
id|u_int
id|write_block
suffix:semicolon
DECL|member|partition
id|u_int
id|partition
suffix:semicolon
DECL|member|interleave
id|u_int
id|interleave
suffix:semicolon
DECL|member|geo
)brace
id|geo
(braket
id|CISTPL_MAX_DEVICES
)braket
suffix:semicolon
DECL|typedef|cistpl_device_geo_t
)brace
id|cistpl_device_geo_t
suffix:semicolon
DECL|struct|cistpl_vers_2_t
r_typedef
r_struct
id|cistpl_vers_2_t
(brace
DECL|member|vers
id|u_char
id|vers
suffix:semicolon
DECL|member|comply
id|u_char
id|comply
suffix:semicolon
DECL|member|dindex
id|u_short
id|dindex
suffix:semicolon
DECL|member|vspec8
DECL|member|vspec9
id|u_char
id|vspec8
comma
id|vspec9
suffix:semicolon
DECL|member|nhdr
id|u_char
id|nhdr
suffix:semicolon
DECL|member|vendor
DECL|member|info
id|u_char
id|vendor
comma
id|info
suffix:semicolon
DECL|member|str
r_char
id|str
(braket
l_int|244
)braket
suffix:semicolon
DECL|typedef|cistpl_vers_2_t
)brace
id|cistpl_vers_2_t
suffix:semicolon
DECL|struct|cistpl_org_t
r_typedef
r_struct
id|cistpl_org_t
(brace
DECL|member|data_org
id|u_char
id|data_org
suffix:semicolon
DECL|member|desc
r_char
id|desc
(braket
l_int|30
)braket
suffix:semicolon
DECL|typedef|cistpl_org_t
)brace
id|cistpl_org_t
suffix:semicolon
DECL|macro|CISTPL_ORG_FS
mdefine_line|#define CISTPL_ORG_FS&t;&t;0x00
DECL|macro|CISTPL_ORG_APPSPEC
mdefine_line|#define CISTPL_ORG_APPSPEC&t;0x01
DECL|macro|CISTPL_ORG_XIP
mdefine_line|#define CISTPL_ORG_XIP&t;&t;0x02
DECL|struct|cistpl_format_t
r_typedef
r_struct
id|cistpl_format_t
(brace
DECL|member|type
id|u_char
id|type
suffix:semicolon
DECL|member|edc
id|u_char
id|edc
suffix:semicolon
DECL|member|offset
id|u_int
id|offset
suffix:semicolon
DECL|member|length
id|u_int
id|length
suffix:semicolon
DECL|typedef|cistpl_format_t
)brace
id|cistpl_format_t
suffix:semicolon
DECL|macro|CISTPL_FORMAT_DISK
mdefine_line|#define CISTPL_FORMAT_DISK&t;0x00
DECL|macro|CISTPL_FORMAT_MEM
mdefine_line|#define CISTPL_FORMAT_MEM&t;0x01
DECL|macro|CISTPL_EDC_NONE
mdefine_line|#define CISTPL_EDC_NONE&t;&t;0x00
DECL|macro|CISTPL_EDC_CKSUM
mdefine_line|#define CISTPL_EDC_CKSUM&t;0x01
DECL|macro|CISTPL_EDC_CRC
mdefine_line|#define CISTPL_EDC_CRC&t;&t;0x02
DECL|macro|CISTPL_EDC_PCC
mdefine_line|#define CISTPL_EDC_PCC&t;&t;0x03
DECL|union|cisparse_t
r_typedef
r_union
id|cisparse_t
(brace
DECL|member|device
id|cistpl_device_t
id|device
suffix:semicolon
DECL|member|checksum
id|cistpl_checksum_t
id|checksum
suffix:semicolon
DECL|member|longlink
id|cistpl_longlink_t
id|longlink
suffix:semicolon
DECL|member|longlink_mfc
id|cistpl_longlink_mfc_t
id|longlink_mfc
suffix:semicolon
DECL|member|version_1
id|cistpl_vers_1_t
id|version_1
suffix:semicolon
DECL|member|altstr
id|cistpl_altstr_t
id|altstr
suffix:semicolon
DECL|member|jedec
id|cistpl_jedec_t
id|jedec
suffix:semicolon
DECL|member|manfid
id|cistpl_manfid_t
id|manfid
suffix:semicolon
DECL|member|funcid
id|cistpl_funcid_t
id|funcid
suffix:semicolon
DECL|member|funce
id|cistpl_funce_t
id|funce
suffix:semicolon
DECL|member|bar
id|cistpl_bar_t
id|bar
suffix:semicolon
DECL|member|config
id|cistpl_config_t
id|config
suffix:semicolon
DECL|member|cftable_entry
id|cistpl_cftable_entry_t
id|cftable_entry
suffix:semicolon
DECL|member|cftable_entry_cb
id|cistpl_cftable_entry_cb_t
id|cftable_entry_cb
suffix:semicolon
DECL|member|device_geo
id|cistpl_device_geo_t
id|device_geo
suffix:semicolon
DECL|member|vers_2
id|cistpl_vers_2_t
id|vers_2
suffix:semicolon
DECL|member|org
id|cistpl_org_t
id|org
suffix:semicolon
DECL|member|format
id|cistpl_format_t
id|format
suffix:semicolon
DECL|typedef|cisparse_t
)brace
id|cisparse_t
suffix:semicolon
DECL|struct|tuple_t
r_typedef
r_struct
id|tuple_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|DesiredTuple
id|cisdata_t
id|DesiredTuple
suffix:semicolon
DECL|member|Flags
id|u_int
id|Flags
suffix:semicolon
multiline_comment|/* internal use */
DECL|member|LinkOffset
id|u_int
id|LinkOffset
suffix:semicolon
multiline_comment|/* internal use */
DECL|member|CISOffset
id|u_int
id|CISOffset
suffix:semicolon
multiline_comment|/* internal use */
DECL|member|TupleCode
id|cisdata_t
id|TupleCode
suffix:semicolon
DECL|member|TupleLink
id|cisdata_t
id|TupleLink
suffix:semicolon
DECL|member|TupleOffset
id|cisdata_t
id|TupleOffset
suffix:semicolon
DECL|member|TupleDataMax
id|cisdata_t
id|TupleDataMax
suffix:semicolon
DECL|member|TupleDataLen
id|cisdata_t
id|TupleDataLen
suffix:semicolon
DECL|member|TupleData
id|cisdata_t
op_star
id|TupleData
suffix:semicolon
DECL|typedef|tuple_t
)brace
id|tuple_t
suffix:semicolon
multiline_comment|/* Special cisdata_t value */
DECL|macro|RETURN_FIRST_TUPLE
mdefine_line|#define RETURN_FIRST_TUPLE&t;0xff
multiline_comment|/* Attributes for tuple calls */
DECL|macro|TUPLE_RETURN_LINK
mdefine_line|#define TUPLE_RETURN_LINK&t;0x01
DECL|macro|TUPLE_RETURN_COMMON
mdefine_line|#define TUPLE_RETURN_COMMON&t;0x02
multiline_comment|/* For ValidateCIS */
DECL|struct|cisinfo_t
r_typedef
r_struct
id|cisinfo_t
(brace
DECL|member|Chains
id|u_int
id|Chains
suffix:semicolon
DECL|typedef|cisinfo_t
)brace
id|cisinfo_t
suffix:semicolon
DECL|macro|CISTPL_MAX_CIS_SIZE
mdefine_line|#define CISTPL_MAX_CIS_SIZE&t;0x200
multiline_comment|/* For ReplaceCIS */
DECL|struct|cisdump_t
r_typedef
r_struct
id|cisdump_t
(brace
DECL|member|Length
id|u_int
id|Length
suffix:semicolon
DECL|member|Data
id|cisdata_t
id|Data
(braket
id|CISTPL_MAX_CIS_SIZE
)braket
suffix:semicolon
DECL|typedef|cisdump_t
)brace
id|cisdump_t
suffix:semicolon
r_int
id|pcmcia_get_first_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
suffix:semicolon
r_int
id|pcmcia_get_next_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
suffix:semicolon
r_int
id|pcmcia_get_tuple_data
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
suffix:semicolon
r_int
id|pcmcia_parse_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
suffix:semicolon
r_int
id|pcmcia_validate_cis
c_func
(paren
id|client_handle_t
id|handle
comma
id|cisinfo_t
op_star
id|info
)paren
suffix:semicolon
r_int
id|pcmcia_replace_cis
c_func
(paren
id|client_handle_t
id|handle
comma
id|cisdump_t
op_star
id|cis
)paren
suffix:semicolon
macro_line|#endif /* LINUX_CISTPL_H */
eof
