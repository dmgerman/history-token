multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *  Copyright (C) 2003 Luis R. Rodriguez &lt;mcgrof@ruslug.rutgers.edu&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef _ISLPCI_MGT_H
DECL|macro|_ISLPCI_MGT_H
mdefine_line|#define _ISLPCI_MGT_H
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/*&n; *  Function definitions&n; */
DECL|macro|K_DEBUG
mdefine_line|#define K_DEBUG(f, m, args...) do { if(f &amp; m) printk(KERN_DEBUG args); } while(0)
DECL|macro|DEBUG
mdefine_line|#define DEBUG(f, args...) K_DEBUG(f, pc_debug, args)
r_extern
r_int
id|pc_debug
suffix:semicolon
DECL|macro|init_wds
mdefine_line|#define init_wds 0&t;/* help compiler optimize away dead code */
multiline_comment|/* General driver definitions */
DECL|macro|PCIDEVICE_LATENCY_TIMER_MIN
mdefine_line|#define PCIDEVICE_LATENCY_TIMER_MIN &t;&t;0x40
DECL|macro|PCIDEVICE_LATENCY_TIMER_VAL
mdefine_line|#define PCIDEVICE_LATENCY_TIMER_VAL &t;&t;0x50
multiline_comment|/* Debugging verbose definitions */
DECL|macro|SHOW_NOTHING
mdefine_line|#define SHOW_NOTHING                            0x00&t;/* overrules everything */
DECL|macro|SHOW_ANYTHING
mdefine_line|#define SHOW_ANYTHING                           0xFF
DECL|macro|SHOW_ERROR_MESSAGES
mdefine_line|#define SHOW_ERROR_MESSAGES                     0x01
DECL|macro|SHOW_TRAPS
mdefine_line|#define SHOW_TRAPS                              0x02
DECL|macro|SHOW_FUNCTION_CALLS
mdefine_line|#define SHOW_FUNCTION_CALLS                     0x04
DECL|macro|SHOW_TRACING
mdefine_line|#define SHOW_TRACING                            0x08
DECL|macro|SHOW_QUEUE_INDEXES
mdefine_line|#define SHOW_QUEUE_INDEXES                      0x10
DECL|macro|SHOW_PIMFOR_FRAMES
mdefine_line|#define SHOW_PIMFOR_FRAMES                      0x20
DECL|macro|SHOW_BUFFER_CONTENTS
mdefine_line|#define SHOW_BUFFER_CONTENTS                    0x40
DECL|macro|VERBOSE
mdefine_line|#define VERBOSE                                 0x01
multiline_comment|/* Default card definitions */
DECL|macro|CARD_DEFAULT_CHANNEL
mdefine_line|#define CARD_DEFAULT_CHANNEL                    6
DECL|macro|CARD_DEFAULT_MODE
mdefine_line|#define CARD_DEFAULT_MODE                       INL_MODE_CLIENT
DECL|macro|CARD_DEFAULT_IW_MODE
mdefine_line|#define CARD_DEFAULT_IW_MODE&t;&t;&t;IW_MODE_INFRA
DECL|macro|CARD_DEFAULT_BSSTYPE
mdefine_line|#define CARD_DEFAULT_BSSTYPE                    DOT11_BSSTYPE_INFRA
DECL|macro|CARD_DEFAULT_CLIENT_SSID
mdefine_line|#define CARD_DEFAULT_CLIENT_SSID&t;&t;&quot;&quot;
DECL|macro|CARD_DEFAULT_AP_SSID
mdefine_line|#define CARD_DEFAULT_AP_SSID&t;&t;&t;&quot;default&quot;
DECL|macro|CARD_DEFAULT_KEY1
mdefine_line|#define CARD_DEFAULT_KEY1                       &quot;default_key_1&quot;
DECL|macro|CARD_DEFAULT_KEY2
mdefine_line|#define CARD_DEFAULT_KEY2                       &quot;default_key_2&quot;
DECL|macro|CARD_DEFAULT_KEY3
mdefine_line|#define CARD_DEFAULT_KEY3                       &quot;default_key_3&quot;
DECL|macro|CARD_DEFAULT_KEY4
mdefine_line|#define CARD_DEFAULT_KEY4                       &quot;default_key_4&quot;
DECL|macro|CARD_DEFAULT_WEP
mdefine_line|#define CARD_DEFAULT_WEP                        0
DECL|macro|CARD_DEFAULT_FILTER
mdefine_line|#define CARD_DEFAULT_FILTER                     0
DECL|macro|CARD_DEFAULT_WDS
mdefine_line|#define CARD_DEFAULT_WDS                        0
DECL|macro|CARD_DEFAULT_AUTHEN
mdefine_line|#define&t;CARD_DEFAULT_AUTHEN                     DOT11_AUTH_OS
DECL|macro|CARD_DEFAULT_DOT1X
mdefine_line|#define&t;CARD_DEFAULT_DOT1X&t;&t;&t;0
DECL|macro|CARD_DEFAULT_MLME_MODE
mdefine_line|#define CARD_DEFAULT_MLME_MODE&t;&t;&t;DOT11_MLME_AUTO
DECL|macro|CARD_DEFAULT_CONFORMANCE
mdefine_line|#define CARD_DEFAULT_CONFORMANCE                OID_INL_CONFORMANCE_NONE
DECL|macro|CARD_DEFAULT_PROFILE
mdefine_line|#define CARD_DEFAULT_PROFILE&t;&t;&t;DOT11_PROFILE_MIXED_G_WIFI
DECL|macro|CARD_DEFAULT_MAXFRAMEBURST
mdefine_line|#define CARD_DEFAULT_MAXFRAMEBURST&t;&t;DOT11_MAXFRAMEBURST_MIXED_SAFE
multiline_comment|/* PIMFOR package definitions */
DECL|macro|PIMFOR_ETHERTYPE
mdefine_line|#define PIMFOR_ETHERTYPE                        0x8828
DECL|macro|PIMFOR_HEADER_SIZE
mdefine_line|#define PIMFOR_HEADER_SIZE                      12
DECL|macro|PIMFOR_VERSION
mdefine_line|#define PIMFOR_VERSION                          1
DECL|macro|PIMFOR_OP_GET
mdefine_line|#define PIMFOR_OP_GET                           0
DECL|macro|PIMFOR_OP_SET
mdefine_line|#define PIMFOR_OP_SET                           1
DECL|macro|PIMFOR_OP_RESPONSE
mdefine_line|#define PIMFOR_OP_RESPONSE                      2
DECL|macro|PIMFOR_OP_ERROR
mdefine_line|#define PIMFOR_OP_ERROR                         3
DECL|macro|PIMFOR_OP_TRAP
mdefine_line|#define PIMFOR_OP_TRAP                          4
DECL|macro|PIMFOR_OP_RESERVED
mdefine_line|#define PIMFOR_OP_RESERVED                      5&t;/* till 255 */
DECL|macro|PIMFOR_DEV_ID_MHLI_MIB
mdefine_line|#define PIMFOR_DEV_ID_MHLI_MIB                  0
DECL|macro|PIMFOR_FLAG_APPLIC_ORIGIN
mdefine_line|#define PIMFOR_FLAG_APPLIC_ORIGIN               0x01
DECL|macro|PIMFOR_FLAG_LITTLE_ENDIAN
mdefine_line|#define PIMFOR_FLAG_LITTLE_ENDIAN               0x02
r_static
r_inline
r_void
DECL|function|add_le32p
id|add_le32p
c_func
(paren
id|u32
op_star
id|le_number
comma
id|u32
id|add
)paren
(brace
op_star
id|le_number
op_assign
id|cpu_to_le32
c_func
(paren
id|le32_to_cpup
c_func
(paren
id|le_number
)paren
op_plus
id|add
)paren
suffix:semicolon
)brace
r_void
id|display_buffer
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *  Type definition section&n; *&n; *  the structure defines only the header allowing copyless&n; *  frame handling&n; */
r_typedef
r_struct
(brace
DECL|member|version
id|u8
id|version
suffix:semicolon
DECL|member|operation
id|u8
id|operation
suffix:semicolon
DECL|member|oid
id|u32
id|oid
suffix:semicolon
DECL|member|device_id
id|u8
id|device_id
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|pimfor_header_t
id|pimfor_header_t
suffix:semicolon
multiline_comment|/* A received and interrupt-processed management frame, either for&n; * schedule_work(prism54_process_trap) or for priv-&gt;mgmt_received,&n; * processed by islpci_mgt_transaction(). */
DECL|struct|islpci_mgmtframe
r_struct
id|islpci_mgmtframe
(brace
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
multiline_comment|/* pointer to network device */
DECL|member|header
id|pimfor_header_t
op_star
id|header
suffix:semicolon
multiline_comment|/* payload header, points into buf */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* payload ex header, points into buf */
DECL|member|ws
r_struct
id|work_struct
id|ws
suffix:semicolon
multiline_comment|/* argument for schedule_work() */
DECL|member|buf
r_char
id|buf
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* fragment buffer */
)brace
suffix:semicolon
r_int
id|islpci_mgt_receive
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
suffix:semicolon
r_int
id|islpci_mgmt_rx_fill
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
suffix:semicolon
r_void
id|islpci_mgt_cleanup_transmit
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
suffix:semicolon
r_int
id|islpci_mgt_transaction
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
comma
r_int
id|operation
comma
r_int
r_int
id|oid
comma
r_void
op_star
id|senddata
comma
r_int
id|sendlen
comma
r_struct
id|islpci_mgmtframe
op_star
op_star
id|recvframe
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|islpci_mgt_release
id|islpci_mgt_release
c_func
(paren
r_struct
id|islpci_mgmtframe
op_star
id|frame
)paren
(brace
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* _ISLPCI_MGT_H */
eof
