multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
macro_line|#include &quot;ixgb.h&quot;
multiline_comment|/* This is the only thing that needs to be changed to adjust the&n; * maximum number of ports that the driver can manage.&n; */
DECL|macro|IXGB_MAX_NIC
mdefine_line|#define IXGB_MAX_NIC 8
DECL|macro|OPTION_UNSET
mdefine_line|#define OPTION_UNSET    -1
DECL|macro|OPTION_DISABLED
mdefine_line|#define OPTION_DISABLED 0
DECL|macro|OPTION_ENABLED
mdefine_line|#define OPTION_ENABLED  1
multiline_comment|/* Module Parameters are always initialized to -1, so that the driver&n; * can tell the difference between no user specified value or the&n; * user asking for the default value.&n; * The true default values are loaded in when ixgb_check_options is called.&n; *&n; * This is a GCC extension to ANSI C.&n; * See the item &quot;Labeled Elements in Initializers&quot; in the section&n; * &quot;Extensions to the C Language Family&quot; of the GCC documentation.&n; */
DECL|macro|IXGB_PARAM_INIT
mdefine_line|#define IXGB_PARAM_INIT { [0 ... IXGB_MAX_NIC] = OPTION_UNSET }
multiline_comment|/* All parameters are treated the same, as an integer array of values.&n; * This macro just reduces the need to repeat the same declaration code&n; * over and over (plus this helps to avoid typo bugs).&n; */
DECL|macro|IXGB_PARAM
mdefine_line|#define IXGB_PARAM(X, S) &bslash;&n;static const int __devinitdata X[IXGB_MAX_NIC + 1] = IXGB_PARAM_INIT; &bslash;&n;MODULE_PARM(X, &quot;1-&quot; __MODULE_STRING(IXGB_MAX_NIC) &quot;i&quot;); &bslash;&n;MODULE_PARM_DESC(X, S);
multiline_comment|/* Transmit Descriptor Count&n; *&n; * Valid Range: 64-4096&n; *&n; * Default Value: 256&n; */
id|IXGB_PARAM
c_func
(paren
id|TxDescriptors
comma
l_string|&quot;Number of transmit descriptors&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Descriptor Count&n; *&n; * Valid Range: 64-4096&n; *&n; * Default Value: 1024&n; */
id|IXGB_PARAM
c_func
(paren
id|RxDescriptors
comma
l_string|&quot;Number of receive descriptors&quot;
)paren
suffix:semicolon
multiline_comment|/* User Specified Flow Control Override&n; *&n; * Valid Range: 0-3&n; *  - 0 - No Flow Control&n; *  - 1 - Rx only, respond to PAUSE frames but do not generate them&n; *  - 2 - Tx only, generate PAUSE frames but ignore them on receive&n; *  - 3 - Full Flow Control Support&n; *&n; * Default Value: Read flow control settings from the EEPROM&n; */
id|IXGB_PARAM
c_func
(paren
id|FlowControl
comma
l_string|&quot;Flow Control setting&quot;
)paren
suffix:semicolon
multiline_comment|/* XsumRX - Receive Checksum Offload Enable/Disable&n; *&n; * Valid Range: 0, 1&n; *  - 0 - disables all checksum offload&n; *  - 1 - enables receive IP/TCP/UDP checksum offload&n; *        on 82597 based NICs&n; *&n; * Default Value: 1&n; */
id|IXGB_PARAM
c_func
(paren
id|XsumRX
comma
l_string|&quot;Disable or enable Receive Checksum offload&quot;
)paren
suffix:semicolon
multiline_comment|/* Transmit Interrupt Delay in units of 0.8192 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 32&n; */
id|IXGB_PARAM
c_func
(paren
id|TxIntDelay
comma
l_string|&quot;Transmit Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Interrupt Delay in units of 0.8192 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 72&n; */
id|IXGB_PARAM
c_func
(paren
id|RxIntDelay
comma
l_string|&quot;Receive Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Interrupt Moderation enable (uses RxIntDelay too)&n; *&n; * Valid Range: 0,1&n; *&n; * Default Value: 1&n; */
id|IXGB_PARAM
c_func
(paren
id|RAIDC
comma
l_string|&quot;Disable or enable Receive Interrupt Moderation&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Flow control high threshold (when we send a pause frame)&n; * (FCRTH)&n; *&n; * Valid Range: 1,536 - 262,136 (0x600 - 0x3FFF8, 8 byte granularity)&n; *&n; * Default Value: 196,608 (0x30000)&n; */
id|IXGB_PARAM
c_func
(paren
id|RxFCHighThresh
comma
l_string|&quot;Receive Flow Control High Threshold&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Flow control low threshold (when we send a resume frame)&n; * (FCRTL)&n; *&n; * Valid Range: 64 - 262,136 (0x40 - 0x3FFF8, 8 byte granularity)&n; *              must be less than high threshold by at least 8 bytes&n; *&n; * Default Value:  163,840 (0x28000)&n; */
id|IXGB_PARAM
c_func
(paren
id|RxFCLowThresh
comma
l_string|&quot;Receive Flow Control Low Threshold&quot;
)paren
suffix:semicolon
multiline_comment|/* Flow control request timeout (how long to pause the link partner&squot;s tx)&n; * (PAP 15:0)&n; *&n; * Valid Range: 1 - 65535 &n; *&n; * Default Value:  256 (0x100)&n; */
id|IXGB_PARAM
c_func
(paren
id|FCReqTimeout
comma
l_string|&quot;Flow Control Request Timeout&quot;
)paren
suffix:semicolon
multiline_comment|/* Interrupt Delay Enable&n; *&n; * Valid Range: 0, 1&n; *&n; *  - 0 - disables transmit interrupt delay&n; *  - 1 - enables transmmit interrupt delay&n; *&n; * Default Value: 1&n; */
id|IXGB_PARAM
c_func
(paren
id|IntDelayEnable
comma
l_string|&quot;Transmit Interrupt Delay Enable&quot;
)paren
suffix:semicolon
DECL|macro|DEFAULT_TXD
mdefine_line|#define DEFAULT_TXD&t;&t;&t;    256
DECL|macro|MAX_TXD
mdefine_line|#define MAX_TXD&t;&t;&t;&t;   4096
DECL|macro|MIN_TXD
mdefine_line|#define MIN_TXD&t;&t;&t;&t;     64
DECL|macro|DEFAULT_TIDV
mdefine_line|#define DEFAULT_TIDV&t;   &t;&t;     32
DECL|macro|MAX_TIDV
mdefine_line|#define MAX_TIDV&t;&t;&t; 0xFFFF
DECL|macro|MIN_TIDV
mdefine_line|#define MIN_TIDV&t;&t;&t;      0
DECL|macro|DEFAULT_RDTR
mdefine_line|#define DEFAULT_RDTR&t;&t;   &t;     72
DECL|macro|MAX_RDTR
mdefine_line|#define MAX_RDTR&t;&t;&t; 0xFFFF
DECL|macro|MIN_RDTR
mdefine_line|#define MIN_RDTR&t;&t;&t;      0
DECL|macro|XSUMRX_DEFAULT
mdefine_line|#define XSUMRX_DEFAULT&t;&t; OPTION_ENABLED
DECL|macro|FLOW_CONTROL_FULL
mdefine_line|#define FLOW_CONTROL_FULL&t;   ixgb_fc_full
DECL|macro|FLOW_CONTROL_DEFAULT
mdefine_line|#define FLOW_CONTROL_DEFAULT  FLOW_CONTROL_FULL
DECL|macro|DEFAULT_FCRTL
mdefine_line|#define DEFAULT_FCRTL&t;  &t;&t;0x28000
DECL|macro|DEFAULT_FCRTH
mdefine_line|#define DEFAULT_FCRTH&t;&t;&t;0x30000
DECL|macro|MIN_FCRTL
mdefine_line|#define MIN_FCRTL&t;&t;&t;      0
DECL|macro|MAX_FCRTL
mdefine_line|#define MAX_FCRTL&t;&t;&t;0x3FFE8
DECL|macro|MIN_FCRTH
mdefine_line|#define MIN_FCRTH&t;&t;&t;      8
DECL|macro|MAX_FCRTH
mdefine_line|#define MAX_FCRTH&t;&t;&t;0x3FFF0
DECL|macro|DEFAULT_FCPAUSE
mdefine_line|#define DEFAULT_FCPAUSE&t;&t;  &t;0x100&t;/* this may be too long */
DECL|macro|MIN_FCPAUSE
mdefine_line|#define MIN_FCPAUSE&t;&t;&t;      1
DECL|macro|MAX_FCPAUSE
mdefine_line|#define MAX_FCPAUSE&t;&t;&t; 0xffff
DECL|struct|ixgb_option
r_struct
id|ixgb_option
(brace
DECL|enumerator|enable_option
DECL|enumerator|range_option
DECL|enumerator|list_option
DECL|member|type
r_enum
(brace
id|enable_option
comma
id|range_option
comma
id|list_option
)brace
id|type
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|err
r_char
op_star
id|err
suffix:semicolon
DECL|member|def
r_int
id|def
suffix:semicolon
r_union
(brace
r_struct
(brace
multiline_comment|/* range_option info */
DECL|member|min
r_int
id|min
suffix:semicolon
DECL|member|max
r_int
id|max
suffix:semicolon
DECL|member|r
)brace
id|r
suffix:semicolon
r_struct
(brace
multiline_comment|/* list_option info */
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|struct|ixgb_opt_list
r_struct
id|ixgb_opt_list
(brace
DECL|member|i
r_int
id|i
suffix:semicolon
DECL|member|str
r_char
op_star
id|str
suffix:semicolon
DECL|member|p
)brace
op_star
id|p
suffix:semicolon
DECL|member|l
)brace
id|l
suffix:semicolon
DECL|member|arg
)brace
id|arg
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ixgb_validate_option
r_static
r_int
id|__devinit
id|ixgb_validate_option
c_func
(paren
r_int
op_star
id|value
comma
r_struct
id|ixgb_option
op_star
id|opt
)paren
(brace
r_if
c_cond
(paren
op_star
id|value
op_eq
id|OPTION_UNSET
)paren
(brace
op_star
id|value
op_assign
id|opt-&gt;def
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|opt-&gt;type
)paren
(brace
r_case
id|enable_option
suffix:colon
r_switch
c_cond
(paren
op_star
id|value
)paren
(brace
r_case
id|OPTION_ENABLED
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s Enabled&bslash;n&quot;
comma
id|opt-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|OPTION_DISABLED
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s Disabled&bslash;n&quot;
comma
id|opt-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|range_option
suffix:colon
r_if
c_cond
(paren
op_star
id|value
op_ge
id|opt-&gt;arg.r.min
op_logical_and
op_star
id|value
op_le
id|opt-&gt;arg.r.max
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s set to %i&bslash;n&quot;
comma
id|opt-&gt;name
comma
op_star
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|list_option
suffix:colon
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ixgb_opt_list
op_star
id|ent
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|opt-&gt;arg.l.nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ent
op_assign
op_amp
id|opt-&gt;arg.l.p
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_star
id|value
op_eq
id|ent-&gt;i
)paren
(brace
r_if
c_cond
(paren
id|ent-&gt;str
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&bslash;n&quot;
comma
id|ent-&gt;str
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Invalid %s specified (%i) %s&bslash;n&quot;
comma
id|opt-&gt;name
comma
op_star
id|value
comma
id|opt-&gt;err
)paren
suffix:semicolon
op_star
id|value
op_assign
id|opt-&gt;def
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|macro|LIST_LEN
mdefine_line|#define LIST_LEN(l) (sizeof(l) / sizeof(l[0]))
multiline_comment|/**&n; * ixgb_check_options - Range Checking for Command Line Parameters&n; * @adapter: board private structure&n; *&n; * This routine checks all command line parameters for valid user&n; * input.  If an invalid value is given, or if no user specified&n; * value exists, a default value is used.  The final value is stored&n; * in a variable in the adapter structure.&n; **/
DECL|function|ixgb_check_options
r_void
id|__devinit
id|ixgb_check_options
c_func
(paren
r_struct
id|ixgb_adapter
op_star
id|adapter
)paren
(brace
r_int
id|bd
op_assign
id|adapter-&gt;bd_number
suffix:semicolon
r_if
c_cond
(paren
id|bd
op_ge
id|IXGB_MAX_NIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Warning: no configuration for board #%i&bslash;n&quot;
comma
id|bd
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Using defaults for all values&bslash;n&quot;
)paren
suffix:semicolon
id|bd
op_assign
id|IXGB_MAX_NIC
suffix:semicolon
)brace
(brace
multiline_comment|/* Transmit Descriptor Count */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Transmit Descriptors&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_TXD
)paren
comma
dot
id|def
op_assign
id|DEFAULT_TXD
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_TXD
comma
dot
id|max
op_assign
id|MAX_TXD
)brace
)brace
)brace
suffix:semicolon
r_struct
id|ixgb_desc_ring
op_star
id|tx_ring
op_assign
op_amp
id|adapter-&gt;tx_ring
suffix:semicolon
id|tx_ring-&gt;count
op_assign
id|TxDescriptors
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|tx_ring-&gt;count
comma
op_amp
id|opt
)paren
suffix:semicolon
id|IXGB_ROUNDUP
c_func
(paren
id|tx_ring-&gt;count
comma
id|IXGB_REQ_TX_DESCRIPTOR_MULTIPLE
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Receive Descriptor Count */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Receive Descriptors&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_RXD
)paren
comma
dot
id|def
op_assign
id|DEFAULT_RXD
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_RXD
comma
dot
id|max
op_assign
id|MAX_RXD
)brace
)brace
)brace
suffix:semicolon
r_struct
id|ixgb_desc_ring
op_star
id|rx_ring
op_assign
op_amp
id|adapter-&gt;rx_ring
suffix:semicolon
id|rx_ring-&gt;count
op_assign
id|RxDescriptors
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|rx_ring-&gt;count
comma
op_amp
id|opt
)paren
suffix:semicolon
id|IXGB_ROUNDUP
c_func
(paren
id|rx_ring-&gt;count
comma
id|IXGB_REQ_RX_DESCRIPTOR_MULTIPLE
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Receive Checksum Offload Enable */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|enable_option
comma
dot
id|name
op_assign
l_string|&quot;Receive Checksum Offload&quot;
comma
dot
id|err
op_assign
l_string|&quot;defaulting to Enabled&quot;
comma
dot
id|def
op_assign
id|OPTION_ENABLED
)brace
suffix:semicolon
r_int
id|rx_csum
op_assign
id|XsumRX
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|rx_csum
comma
op_amp
id|opt
)paren
suffix:semicolon
id|adapter-&gt;rx_csum
op_assign
id|rx_csum
suffix:semicolon
)brace
(brace
multiline_comment|/* Flow Control */
r_struct
id|ixgb_opt_list
id|fc_list
(braket
)braket
op_assign
(brace
(brace
id|ixgb_fc_none
comma
l_string|&quot;Flow Control Disabled&quot;
)brace
comma
(brace
id|ixgb_fc_rx_pause
comma
l_string|&quot;Flow Control Receive Only&quot;
)brace
comma
(brace
id|ixgb_fc_tx_pause
comma
l_string|&quot;Flow Control Transmit Only&quot;
)brace
comma
(brace
id|ixgb_fc_full
comma
l_string|&quot;Flow Control Enabled&quot;
)brace
comma
(brace
id|ixgb_fc_default
comma
l_string|&quot;Flow Control Hardware Default&quot;
)brace
)brace
suffix:semicolon
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|list_option
comma
dot
id|name
op_assign
l_string|&quot;Flow Control&quot;
comma
dot
id|err
op_assign
l_string|&quot;reading default settings from EEPROM&quot;
comma
dot
id|def
op_assign
id|ixgb_fc_full
comma
dot
id|arg
op_assign
(brace
dot
id|l
op_assign
(brace
dot
id|nr
op_assign
id|LIST_LEN
c_func
(paren
id|fc_list
)paren
comma
dot
id|p
op_assign
id|fc_list
)brace
)brace
)brace
suffix:semicolon
r_int
id|fc
op_assign
id|FlowControl
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|fc
comma
op_amp
id|opt
)paren
suffix:semicolon
id|adapter-&gt;hw.fc.type
op_assign
id|fc
suffix:semicolon
)brace
(brace
multiline_comment|/* Receive Flow Control High Threshold */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Rx Flow Control High Threshold&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_FCRTH
)paren
comma
dot
id|def
op_assign
id|DEFAULT_FCRTH
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_FCRTH
comma
dot
id|max
op_assign
id|MAX_FCRTH
)brace
)brace
)brace
suffix:semicolon
id|adapter-&gt;hw.fc.high_water
op_assign
id|RxFCHighThresh
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|adapter-&gt;hw.fc.high_water
comma
op_amp
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|adapter-&gt;hw.fc.type
op_amp
id|ixgb_fc_rx_pause
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Ignoring RxFCHighThresh when no RxFC&bslash;n&quot;
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Receive Flow Control Low Threshold */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Rx Flow Control Low Threshold&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_FCRTL
)paren
comma
dot
id|def
op_assign
id|DEFAULT_FCRTL
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_FCRTL
comma
dot
id|max
op_assign
id|MAX_FCRTL
)brace
)brace
)brace
suffix:semicolon
id|adapter-&gt;hw.fc.low_water
op_assign
id|RxFCLowThresh
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|adapter-&gt;hw.fc.low_water
comma
op_amp
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|adapter-&gt;hw.fc.type
op_amp
id|ixgb_fc_rx_pause
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Ignoring RxFCLowThresh when no RxFC&bslash;n&quot;
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Flow Control Pause Time Request */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Flow Control Pause Time Request&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_FCPAUSE
)paren
comma
dot
id|def
op_assign
id|DEFAULT_FCPAUSE
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_FCPAUSE
comma
dot
id|max
op_assign
id|MAX_FCPAUSE
)brace
)brace
)brace
suffix:semicolon
r_int
id|pause_time
op_assign
id|FCReqTimeout
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|pause_time
comma
op_amp
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|adapter-&gt;hw.fc.type
op_amp
id|ixgb_fc_rx_pause
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Ignoring FCReqTimeout when no RxFC&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.fc.pause_time
op_assign
id|pause_time
suffix:semicolon
)brace
multiline_comment|/* high low and spacing check for rx flow control thresholds */
r_if
c_cond
(paren
id|adapter-&gt;hw.fc.type
op_amp
id|ixgb_fc_rx_pause
)paren
(brace
multiline_comment|/* high must be greater than low */
r_if
c_cond
(paren
id|adapter-&gt;hw.fc.high_water
OL
(paren
id|adapter-&gt;hw.fc.low_water
op_plus
l_int|8
)paren
)paren
(brace
multiline_comment|/* set defaults */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;RxFCHighThresh must be &gt;= (RxFCLowThresh + 8), &quot;
l_string|&quot;Using Defaults&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.fc.high_water
op_assign
id|DEFAULT_FCRTH
suffix:semicolon
id|adapter-&gt;hw.fc.low_water
op_assign
id|DEFAULT_FCRTL
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Receive Interrupt Delay */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Receive Interrupt Delay&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_RDTR
)paren
comma
dot
id|def
op_assign
id|DEFAULT_RDTR
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_RDTR
comma
dot
id|max
op_assign
id|MAX_RDTR
)brace
)brace
)brace
suffix:semicolon
id|adapter-&gt;rx_int_delay
op_assign
id|RxIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|adapter-&gt;rx_int_delay
comma
op_amp
id|opt
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Receive Interrupt Moderation */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|enable_option
comma
dot
id|name
op_assign
l_string|&quot;Advanced Receive Interrupt Moderation&quot;
comma
dot
id|err
op_assign
l_string|&quot;defaulting to Enabled&quot;
comma
dot
id|def
op_assign
id|OPTION_ENABLED
)brace
suffix:semicolon
r_int
id|raidc
op_assign
id|RAIDC
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|raidc
comma
op_amp
id|opt
)paren
suffix:semicolon
id|adapter-&gt;raidc
op_assign
id|raidc
suffix:semicolon
)brace
(brace
multiline_comment|/* Transmit Interrupt Delay */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|range_option
comma
dot
id|name
op_assign
l_string|&quot;Transmit Interrupt Delay&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_TIDV
)paren
comma
dot
id|def
op_assign
id|DEFAULT_TIDV
comma
dot
id|arg
op_assign
(brace
dot
id|r
op_assign
(brace
dot
id|min
op_assign
id|MIN_TIDV
comma
dot
id|max
op_assign
id|MAX_TIDV
)brace
)brace
)brace
suffix:semicolon
id|adapter-&gt;tx_int_delay
op_assign
id|TxIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|adapter-&gt;tx_int_delay
comma
op_amp
id|opt
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Transmit Interrupt Delay Enable */
r_struct
id|ixgb_option
id|opt
op_assign
(brace
dot
id|type
op_assign
id|enable_option
comma
dot
id|name
op_assign
l_string|&quot;Tx Interrupt Delay Enable&quot;
comma
dot
id|err
op_assign
l_string|&quot;defaulting to Enabled&quot;
comma
dot
id|def
op_assign
id|OPTION_ENABLED
)brace
suffix:semicolon
r_int
id|ide
op_assign
id|IntDelayEnable
(braket
id|bd
)braket
suffix:semicolon
id|ixgb_validate_option
c_func
(paren
op_amp
id|ide
comma
op_amp
id|opt
)paren
suffix:semicolon
id|adapter-&gt;tx_int_delay_enable
op_assign
id|ide
suffix:semicolon
)brace
)brace
eof
