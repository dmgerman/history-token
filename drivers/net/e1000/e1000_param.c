multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
macro_line|#include &quot;e1000.h&quot;
multiline_comment|/* This is the only thing that needs to be changed to adjust the&n; * maximum number of ports that the driver can manage.&n; */
DECL|macro|E1000_MAX_NIC
mdefine_line|#define E1000_MAX_NIC 32
DECL|macro|OPTION_UNSET
mdefine_line|#define OPTION_UNSET   -1
DECL|macro|OPTION_DISABLED
mdefine_line|#define OPTION_DISABLED 0
DECL|macro|OPTION_ENABLED
mdefine_line|#define OPTION_ENABLED  1
multiline_comment|/* All parameters are treated the same, as an integer array of values.&n; * This macro just reduces the need to repeat the same declaration code&n; * over and over (plus this helps to avoid typo bugs).&n; */
DECL|macro|E1000_PARAM_INIT
mdefine_line|#define E1000_PARAM_INIT { [0 ... E1000_MAX_NIC] = OPTION_UNSET }
DECL|macro|E1000_PARAM
mdefine_line|#define E1000_PARAM(X, desc) &bslash;&n;&t;static int __devinitdata X[E1000_MAX_NIC+1] = E1000_PARAM_INIT; &bslash;&n;&t;static int num_##X = 0; &bslash;&n;&t;module_param_array(X, int, &amp;num_##X, 0); &bslash;&n;&t;MODULE_PARM_DESC(X, desc);
multiline_comment|/* Transmit Descriptor Count&n; *&n; * Valid Range: 80-256 for 82542 and 82543 gigabit ethernet controllers&n; * Valid Range: 80-4096 for 82544 and newer&n; *&n; * Default Value: 256&n; */
id|E1000_PARAM
c_func
(paren
id|TxDescriptors
comma
l_string|&quot;Number of transmit descriptors&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Descriptor Count&n; *&n; * Valid Range: 80-256 for 82542 and 82543 gigabit ethernet controllers&n; * Valid Range: 80-4096 for 82544 and newer&n; *&n; * Default Value: 256&n; */
id|E1000_PARAM
c_func
(paren
id|RxDescriptors
comma
l_string|&quot;Number of receive descriptors&quot;
)paren
suffix:semicolon
multiline_comment|/* User Specified Speed Override&n; *&n; * Valid Range: 0, 10, 100, 1000&n; *  - 0    - auto-negotiate at all supported speeds&n; *  - 10   - only link at 10 Mbps&n; *  - 100  - only link at 100 Mbps&n; *  - 1000 - only link at 1000 Mbps&n; *&n; * Default Value: 0&n; */
id|E1000_PARAM
c_func
(paren
id|Speed
comma
l_string|&quot;Speed setting&quot;
)paren
suffix:semicolon
multiline_comment|/* User Specified Duplex Override&n; *&n; * Valid Range: 0-2&n; *  - 0 - auto-negotiate for duplex&n; *  - 1 - only link at half duplex&n; *  - 2 - only link at full duplex&n; *&n; * Default Value: 0&n; */
id|E1000_PARAM
c_func
(paren
id|Duplex
comma
l_string|&quot;Duplex setting&quot;
)paren
suffix:semicolon
multiline_comment|/* Auto-negotiation Advertisement Override&n; *&n; * Valid Range: 0x01-0x0F, 0x20-0x2F (copper); 0x20 (fiber)&n; *&n; * The AutoNeg value is a bit mask describing which speed and duplex&n; * combinations should be advertised during auto-negotiation.&n; * The supported speed and duplex modes are listed below&n; *&n; * Bit           7     6     5      4      3     2     1      0&n; * Speed (Mbps)  N/A   N/A   1000   N/A    100   100   10     10&n; * Duplex                    Full          Full  Half  Full   Half&n; *&n; * Default Value: 0x2F (copper); 0x20 (fiber)&n; */
id|E1000_PARAM
c_func
(paren
id|AutoNeg
comma
l_string|&quot;Advertised auto-negotiation setting&quot;
)paren
suffix:semicolon
multiline_comment|/* User Specified Flow Control Override&n; *&n; * Valid Range: 0-3&n; *  - 0 - No Flow Control&n; *  - 1 - Rx only, respond to PAUSE frames but do not generate them&n; *  - 2 - Tx only, generate PAUSE frames but ignore them on receive&n; *  - 3 - Full Flow Control Support&n; *&n; * Default Value: Read flow control settings from the EEPROM&n; */
id|E1000_PARAM
c_func
(paren
id|FlowControl
comma
l_string|&quot;Flow Control setting&quot;
)paren
suffix:semicolon
multiline_comment|/* XsumRX - Receive Checksum Offload Enable/Disable&n; *&n; * Valid Range: 0, 1&n; *  - 0 - disables all checksum offload&n; *  - 1 - enables receive IP/TCP/UDP checksum offload&n; *        on 82543 and newer -based NICs&n; *&n; * Default Value: 1&n; */
id|E1000_PARAM
c_func
(paren
id|XsumRX
comma
l_string|&quot;Disable or enable Receive Checksum offload&quot;
)paren
suffix:semicolon
multiline_comment|/* Transmit Interrupt Delay in units of 1.024 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 64&n; */
id|E1000_PARAM
c_func
(paren
id|TxIntDelay
comma
l_string|&quot;Transmit Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Transmit Absolute Interrupt Delay in units of 1.024 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 0&n; */
id|E1000_PARAM
c_func
(paren
id|TxAbsIntDelay
comma
l_string|&quot;Transmit Absolute Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Interrupt Delay in units of 1.024 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 0&n; */
id|E1000_PARAM
c_func
(paren
id|RxIntDelay
comma
l_string|&quot;Receive Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Receive Absolute Interrupt Delay in units of 1.024 microseconds&n; *&n; * Valid Range: 0-65535&n; *&n; * Default Value: 128&n; */
id|E1000_PARAM
c_func
(paren
id|RxAbsIntDelay
comma
l_string|&quot;Receive Absolute Interrupt Delay&quot;
)paren
suffix:semicolon
multiline_comment|/* Interrupt Throttle Rate (interrupts/sec)&n; *&n; * Valid Range: 100-100000 (0=off, 1=dynamic)&n; *&n; * Default Value: 1&n; */
id|E1000_PARAM
c_func
(paren
id|InterruptThrottleRate
comma
l_string|&quot;Interrupt Throttling Rate&quot;
)paren
suffix:semicolon
DECL|macro|AUTONEG_ADV_DEFAULT
mdefine_line|#define AUTONEG_ADV_DEFAULT  0x2F
DECL|macro|AUTONEG_ADV_MASK
mdefine_line|#define AUTONEG_ADV_MASK     0x2F
DECL|macro|FLOW_CONTROL_DEFAULT
mdefine_line|#define FLOW_CONTROL_DEFAULT FLOW_CONTROL_FULL
DECL|macro|DEFAULT_RDTR
mdefine_line|#define DEFAULT_RDTR                   0
DECL|macro|MAX_RXDELAY
mdefine_line|#define MAX_RXDELAY               0xFFFF
DECL|macro|MIN_RXDELAY
mdefine_line|#define MIN_RXDELAY                    0
DECL|macro|DEFAULT_RADV
mdefine_line|#define DEFAULT_RADV                 128
DECL|macro|MAX_RXABSDELAY
mdefine_line|#define MAX_RXABSDELAY            0xFFFF
DECL|macro|MIN_RXABSDELAY
mdefine_line|#define MIN_RXABSDELAY                 0
DECL|macro|DEFAULT_TIDV
mdefine_line|#define DEFAULT_TIDV                  64
DECL|macro|MAX_TXDELAY
mdefine_line|#define MAX_TXDELAY               0xFFFF
DECL|macro|MIN_TXDELAY
mdefine_line|#define MIN_TXDELAY                    0
DECL|macro|DEFAULT_TADV
mdefine_line|#define DEFAULT_TADV                  64
DECL|macro|MAX_TXABSDELAY
mdefine_line|#define MAX_TXABSDELAY            0xFFFF
DECL|macro|MIN_TXABSDELAY
mdefine_line|#define MIN_TXABSDELAY                 0
DECL|macro|DEFAULT_ITR
mdefine_line|#define DEFAULT_ITR                 8000
DECL|macro|MAX_ITR
mdefine_line|#define MAX_ITR                   100000
DECL|macro|MIN_ITR
mdefine_line|#define MIN_ITR                      100
DECL|struct|e1000_option
r_struct
id|e1000_option
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
DECL|struct|e1000_opt_list
DECL|member|i
DECL|member|str
DECL|member|p
r_struct
id|e1000_opt_list
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
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
r_static
r_int
id|__devinit
DECL|function|e1000_validate_option
id|e1000_validate_option
c_func
(paren
r_int
op_star
id|value
comma
r_struct
id|e1000_option
op_star
id|opt
comma
r_struct
id|e1000_adapter
op_star
id|adapter
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
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
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
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
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
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
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
id|e1000_opt_list
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
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|ent-&gt;str
)paren
suffix:semicolon
)brace
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
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
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
r_static
r_void
id|e1000_check_fiber_options
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|e1000_check_copper_options
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
suffix:semicolon
multiline_comment|/**&n; * e1000_check_options - Range Checking for Command Line Parameters&n; * @adapter: board private structure&n; *&n; * This routine checks all command line parameters for valid user&n; * input.  If an invalid value is given, or if no user specified&n; * value exists, a default value is used.  The final value is stored&n; * in a variable in the adapter structure.&n; **/
r_void
id|__devinit
DECL|function|e1000_check_options
id|e1000_check_options
c_func
(paren
r_struct
id|e1000_adapter
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
id|E1000_MAX_NIC
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|NOTICE
comma
l_string|&quot;Warning: no configuration for board #%i&bslash;n&quot;
comma
id|bd
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|NOTICE
comma
l_string|&quot;Using defaults for all values&bslash;n&quot;
)paren
suffix:semicolon
)brace
(brace
multiline_comment|/* Transmit Descriptor Count */
r_struct
id|e1000_option
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
id|E1000_DEFAULT_TXD
)paren
comma
dot
id|def
op_assign
id|E1000_DEFAULT_TXD
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
id|E1000_MIN_TXD
)brace
)brace
)brace
suffix:semicolon
r_struct
id|e1000_desc_ring
op_star
id|tx_ring
op_assign
op_amp
id|adapter-&gt;tx_ring
suffix:semicolon
id|e1000_mac_type
id|mac_type
op_assign
id|adapter-&gt;hw.mac_type
suffix:semicolon
id|opt.arg.r.max
op_assign
id|mac_type
OL
id|e1000_82544
ques
c_cond
id|E1000_MAX_TXD
suffix:colon
id|E1000_MAX_82544_TXD
suffix:semicolon
r_if
c_cond
(paren
id|num_TxDescriptors
OG
id|bd
)paren
(brace
id|tx_ring-&gt;count
op_assign
id|TxDescriptors
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|tx_ring-&gt;count
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
id|E1000_ROUNDUP
c_func
(paren
id|tx_ring-&gt;count
comma
id|REQ_TX_DESCRIPTOR_MULTIPLE
)paren
suffix:semicolon
)brace
r_else
(brace
id|tx_ring-&gt;count
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Receive Descriptor Count */
r_struct
id|e1000_option
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
id|E1000_DEFAULT_RXD
)paren
comma
dot
id|def
op_assign
id|E1000_DEFAULT_RXD
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
id|E1000_MIN_RXD
)brace
)brace
)brace
suffix:semicolon
r_struct
id|e1000_desc_ring
op_star
id|rx_ring
op_assign
op_amp
id|adapter-&gt;rx_ring
suffix:semicolon
id|e1000_mac_type
id|mac_type
op_assign
id|adapter-&gt;hw.mac_type
suffix:semicolon
id|opt.arg.r.max
op_assign
id|mac_type
OL
id|e1000_82544
ques
c_cond
id|E1000_MAX_RXD
suffix:colon
id|E1000_MAX_82544_RXD
suffix:semicolon
r_if
c_cond
(paren
id|num_RxDescriptors
OG
id|bd
)paren
(brace
id|rx_ring-&gt;count
op_assign
id|RxDescriptors
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|rx_ring-&gt;count
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
id|E1000_ROUNDUP
c_func
(paren
id|rx_ring-&gt;count
comma
id|REQ_RX_DESCRIPTOR_MULTIPLE
)paren
suffix:semicolon
)brace
r_else
(brace
id|rx_ring-&gt;count
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Checksum Offload Enable/Disable */
r_struct
id|e1000_option
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
l_string|&quot;Checksum Offload&quot;
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
r_if
c_cond
(paren
id|num_XsumRX
OG
id|bd
)paren
(brace
r_int
id|rx_csum
op_assign
id|XsumRX
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|rx_csum
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
id|adapter-&gt;rx_csum
op_assign
id|rx_csum
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;rx_csum
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Flow Control */
r_struct
id|e1000_opt_list
id|fc_list
(braket
)braket
op_assign
(brace
(brace
id|e1000_fc_none
comma
l_string|&quot;Flow Control Disabled&quot;
)brace
comma
(brace
id|e1000_fc_rx_pause
comma
l_string|&quot;Flow Control Receive Only&quot;
)brace
comma
(brace
id|e1000_fc_tx_pause
comma
l_string|&quot;Flow Control Transmit Only&quot;
)brace
comma
(brace
id|e1000_fc_full
comma
l_string|&quot;Flow Control Enabled&quot;
)brace
comma
(brace
id|e1000_fc_default
comma
l_string|&quot;Flow Control Hardware Default&quot;
)brace
)brace
suffix:semicolon
r_struct
id|e1000_option
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
id|e1000_fc_default
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
id|ARRAY_SIZE
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
r_if
c_cond
(paren
id|num_FlowControl
OG
id|bd
)paren
(brace
r_int
id|fc
op_assign
id|FlowControl
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|fc
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
id|adapter-&gt;hw.fc
op_assign
id|adapter-&gt;hw.original_fc
op_assign
id|fc
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;hw.fc
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Transmit Interrupt Delay */
r_struct
id|e1000_option
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
id|MIN_TXDELAY
comma
dot
id|max
op_assign
id|MAX_TXDELAY
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_TxIntDelay
OG
id|bd
)paren
(brace
id|adapter-&gt;tx_int_delay
op_assign
id|TxIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|adapter-&gt;tx_int_delay
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;tx_int_delay
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Transmit Absolute Interrupt Delay */
r_struct
id|e1000_option
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
l_string|&quot;Transmit Absolute Interrupt Delay&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_TADV
)paren
comma
dot
id|def
op_assign
id|DEFAULT_TADV
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
id|MIN_TXABSDELAY
comma
dot
id|max
op_assign
id|MAX_TXABSDELAY
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_TxAbsIntDelay
OG
id|bd
)paren
(brace
id|adapter-&gt;tx_abs_int_delay
op_assign
id|TxAbsIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|adapter-&gt;tx_abs_int_delay
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;tx_abs_int_delay
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Receive Interrupt Delay */
r_struct
id|e1000_option
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
id|MIN_RXDELAY
comma
dot
id|max
op_assign
id|MAX_RXDELAY
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_RxIntDelay
OG
id|bd
)paren
(brace
id|adapter-&gt;rx_int_delay
op_assign
id|RxIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|adapter-&gt;rx_int_delay
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;rx_int_delay
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Receive Absolute Interrupt Delay */
r_struct
id|e1000_option
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
l_string|&quot;Receive Absolute Interrupt Delay&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_RADV
)paren
comma
dot
id|def
op_assign
id|DEFAULT_RADV
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
id|MIN_RXABSDELAY
comma
dot
id|max
op_assign
id|MAX_RXABSDELAY
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_RxAbsIntDelay
OG
id|bd
)paren
(brace
id|adapter-&gt;rx_abs_int_delay
op_assign
id|RxAbsIntDelay
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|adapter-&gt;rx_abs_int_delay
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|adapter-&gt;rx_abs_int_delay
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Interrupt Throttling Rate */
r_struct
id|e1000_option
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
l_string|&quot;Interrupt Throttling Rate (ints/sec)&quot;
comma
dot
id|err
op_assign
l_string|&quot;using default of &quot;
id|__MODULE_STRING
c_func
(paren
id|DEFAULT_ITR
)paren
comma
dot
id|def
op_assign
id|DEFAULT_ITR
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
id|MIN_ITR
comma
dot
id|max
op_assign
id|MAX_ITR
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_InterruptThrottleRate
OG
id|bd
)paren
(brace
id|adapter-&gt;itr
op_assign
id|InterruptThrottleRate
(braket
id|bd
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|adapter-&gt;itr
)paren
(brace
r_case
op_minus
l_int|1
suffix:colon
id|adapter-&gt;itr
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;%s turned off&bslash;n&quot;
comma
id|opt.name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;%s set to dynamic mode&bslash;n&quot;
comma
id|opt.name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|e1000_validate_option
c_func
(paren
op_amp
id|adapter-&gt;itr
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|adapter-&gt;itr
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|adapter-&gt;hw.media_type
)paren
(brace
r_case
id|e1000_media_type_fiber
suffix:colon
r_case
id|e1000_media_type_internal_serdes
suffix:colon
id|e1000_check_fiber_options
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|e1000_media_type_copper
suffix:colon
id|e1000_check_copper_options
c_func
(paren
id|adapter
)paren
suffix:semicolon
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
)brace
multiline_comment|/**&n; * e1000_check_fiber_options - Range Checking for Link Options, Fiber Version&n; * @adapter: board private structure&n; *&n; * Handles speed and duplex options on fiber adapters&n; **/
r_static
r_void
id|__devinit
DECL|function|e1000_check_fiber_options
id|e1000_check_fiber_options
c_func
(paren
r_struct
id|e1000_adapter
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
id|num_Speed
OG
id|bd
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Speed not valid for fiber adapters, &quot;
l_string|&quot;parameter ignored&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num_Duplex
OG
id|bd
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Duplex not valid for fiber adapters, &quot;
l_string|&quot;parameter ignored&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|num_AutoNeg
OG
id|bd
)paren
op_logical_and
(paren
id|AutoNeg
(braket
id|bd
)braket
op_ne
l_int|0x20
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;AutoNeg other than 1000/Full is &quot;
l_string|&quot;not valid for fiber adapters, &quot;
l_string|&quot;parameter ignored&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * e1000_check_copper_options - Range Checking for Link Options, Copper Version&n; * @adapter: board private structure&n; *&n; * Handles speed and duplex options on copper adapters&n; **/
r_static
r_void
id|__devinit
DECL|function|e1000_check_copper_options
id|e1000_check_copper_options
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
(brace
r_int
id|speed
comma
id|dplx
suffix:semicolon
r_int
id|bd
op_assign
id|adapter-&gt;bd_number
suffix:semicolon
(brace
multiline_comment|/* Speed */
r_struct
id|e1000_opt_list
id|speed_list
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|SPEED_10
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|SPEED_100
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|SPEED_1000
comma
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
r_struct
id|e1000_option
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
l_string|&quot;Speed&quot;
comma
dot
id|err
op_assign
l_string|&quot;parameter ignored&quot;
comma
dot
id|def
op_assign
l_int|0
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
id|ARRAY_SIZE
c_func
(paren
id|speed_list
)paren
comma
dot
id|p
op_assign
id|speed_list
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_Speed
OG
id|bd
)paren
(brace
id|speed
op_assign
id|Speed
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|speed
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|speed
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
(brace
multiline_comment|/* Duplex */
r_struct
id|e1000_opt_list
id|dplx_list
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|HALF_DUPLEX
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|FULL_DUPLEX
comma
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
r_struct
id|e1000_option
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
l_string|&quot;Duplex&quot;
comma
dot
id|err
op_assign
l_string|&quot;parameter ignored&quot;
comma
dot
id|def
op_assign
l_int|0
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
id|ARRAY_SIZE
c_func
(paren
id|dplx_list
)paren
comma
dot
id|p
op_assign
id|dplx_list
)brace
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|num_Duplex
OG
id|bd
)paren
(brace
id|dplx
op_assign
id|Duplex
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|dplx
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|dplx
op_assign
id|opt.def
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|num_AutoNeg
OG
id|bd
)paren
op_logical_and
(paren
id|speed
op_ne
l_int|0
op_logical_or
id|dplx
op_ne
l_int|0
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;AutoNeg specified along with Speed or Duplex, &quot;
l_string|&quot;parameter ignored&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|AUTONEG_ADV_DEFAULT
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Autoneg */
r_struct
id|e1000_opt_list
id|an_list
(braket
)braket
op_assign
DECL|macro|AA
mdefine_line|#define AA &quot;AutoNeg advertising &quot;
(brace
(brace
l_int|0x01
comma
id|AA
l_string|&quot;10/HD&quot;
)brace
comma
(brace
l_int|0x02
comma
id|AA
l_string|&quot;10/FD&quot;
)brace
comma
(brace
l_int|0x03
comma
id|AA
l_string|&quot;10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x04
comma
id|AA
l_string|&quot;100/HD&quot;
)brace
comma
(brace
l_int|0x05
comma
id|AA
l_string|&quot;100/HD, 10/HD&quot;
)brace
comma
(brace
l_int|0x06
comma
id|AA
l_string|&quot;100/HD, 10/FD&quot;
)brace
comma
(brace
l_int|0x07
comma
id|AA
l_string|&quot;100/HD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x08
comma
id|AA
l_string|&quot;100/FD&quot;
)brace
comma
(brace
l_int|0x09
comma
id|AA
l_string|&quot;100/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x0a
comma
id|AA
l_string|&quot;100/FD, 10/FD&quot;
)brace
comma
(brace
l_int|0x0b
comma
id|AA
l_string|&quot;100/FD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x0c
comma
id|AA
l_string|&quot;100/FD, 100/HD&quot;
)brace
comma
(brace
l_int|0x0d
comma
id|AA
l_string|&quot;100/FD, 100/HD, 10/HD&quot;
)brace
comma
(brace
l_int|0x0e
comma
id|AA
l_string|&quot;100/FD, 100/HD, 10/FD&quot;
)brace
comma
(brace
l_int|0x0f
comma
id|AA
l_string|&quot;100/FD, 100/HD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x20
comma
id|AA
l_string|&quot;1000/FD&quot;
)brace
comma
(brace
l_int|0x21
comma
id|AA
l_string|&quot;1000/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x22
comma
id|AA
l_string|&quot;1000/FD, 10/FD&quot;
)brace
comma
(brace
l_int|0x23
comma
id|AA
l_string|&quot;1000/FD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x24
comma
id|AA
l_string|&quot;1000/FD, 100/HD&quot;
)brace
comma
(brace
l_int|0x25
comma
id|AA
l_string|&quot;1000/FD, 100/HD, 10/HD&quot;
)brace
comma
(brace
l_int|0x26
comma
id|AA
l_string|&quot;1000/FD, 100/HD, 10/FD&quot;
)brace
comma
(brace
l_int|0x27
comma
id|AA
l_string|&quot;1000/FD, 100/HD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x28
comma
id|AA
l_string|&quot;1000/FD, 100/FD&quot;
)brace
comma
(brace
l_int|0x29
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x2a
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 10/FD&quot;
)brace
comma
(brace
l_int|0x2b
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 10/FD, 10/HD&quot;
)brace
comma
(brace
l_int|0x2c
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 100/HD&quot;
)brace
comma
(brace
l_int|0x2d
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 100/HD, 10/HD&quot;
)brace
comma
(brace
l_int|0x2e
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 100/HD, 10/FD&quot;
)brace
comma
(brace
l_int|0x2f
comma
id|AA
l_string|&quot;1000/FD, 100/FD, 100/HD, 10/FD, 10/HD&quot;
)brace
)brace
suffix:semicolon
r_struct
id|e1000_option
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
l_string|&quot;AutoNeg&quot;
comma
dot
id|err
op_assign
l_string|&quot;parameter ignored&quot;
comma
dot
id|def
op_assign
id|AUTONEG_ADV_DEFAULT
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
id|ARRAY_SIZE
c_func
(paren
id|an_list
)paren
comma
dot
id|p
op_assign
id|an_list
)brace
)brace
)brace
suffix:semicolon
r_int
id|an
op_assign
id|AutoNeg
(braket
id|bd
)braket
suffix:semicolon
id|e1000_validate_option
c_func
(paren
op_amp
id|an
comma
op_amp
id|opt
comma
id|adapter
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|an
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|speed
op_plus
id|dplx
)paren
(brace
r_case
l_int|0
suffix:colon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|num_Speed
OG
id|bd
)paren
op_logical_and
(paren
id|speed
op_ne
l_int|0
op_logical_or
id|dplx
op_ne
l_int|0
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Speed and duplex autonegotiation enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HALF_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Half Duplex specified without Speed&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at &quot;
l_string|&quot;Half Duplex only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_10_HALF
op_or
id|ADVERTISE_100_HALF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FULL_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Full Duplex specified without Speed&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at &quot;
l_string|&quot;Full Duplex only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_10_FULL
op_or
id|ADVERTISE_100_FULL
op_or
id|ADVERTISE_1000_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_10
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;10 Mbps Speed specified &quot;
l_string|&quot;without Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at 10 Mbps only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_10_HALF
op_or
id|ADVERTISE_10_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_10
op_plus
id|HALF_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Forcing to 10 Mbps Half Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|0
suffix:semicolon
id|adapter-&gt;hw.forced_speed_duplex
op_assign
id|e1000_10_half
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_10
op_plus
id|FULL_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Forcing to 10 Mbps Full Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|0
suffix:semicolon
id|adapter-&gt;hw.forced_speed_duplex
op_assign
id|e1000_10_full
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;100 Mbps Speed specified &quot;
l_string|&quot;without Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at &quot;
l_string|&quot;100 Mbps only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_100_HALF
op_or
id|ADVERTISE_100_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
op_plus
id|HALF_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Forcing to 100 Mbps Half Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|0
suffix:semicolon
id|adapter-&gt;hw.forced_speed_duplex
op_assign
id|e1000_100_half
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
op_plus
id|FULL_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Forcing to 100 Mbps Full Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|0
suffix:semicolon
id|adapter-&gt;hw.forced_speed_duplex
op_assign
id|e1000_100_full
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_1000
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;1000 Mbps Speed specified without &quot;
l_string|&quot;Duplex&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at 1000 Mbps &quot;
l_string|&quot;Full Duplex only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_1000_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_1000
op_plus
id|HALF_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Half Duplex is not supported at 1000 Mbps&bslash;n&quot;
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at 1000 Mbps &quot;
l_string|&quot;Full Duplex only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_1000_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_1000
op_plus
id|FULL_DUPLEX
suffix:colon
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Using Autonegotiation at 1000 Mbps Full Duplex only&bslash;n&quot;
)paren
suffix:semicolon
id|adapter-&gt;hw.autoneg
op_assign
id|adapter-&gt;fc_autoneg
op_assign
l_int|1
suffix:semicolon
id|adapter-&gt;hw.autoneg_advertised
op_assign
id|ADVERTISE_1000_FULL
suffix:semicolon
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
multiline_comment|/* Speed, AutoNeg and MDI/MDI-X must all play nice */
r_if
c_cond
(paren
id|e1000_validate_mdi_setting
c_func
(paren
op_amp
(paren
id|adapter-&gt;hw
)paren
)paren
OL
l_int|0
)paren
(brace
id|DPRINTK
c_func
(paren
id|PROBE
comma
id|INFO
comma
l_string|&quot;Speed, AutoNeg and MDI-X specifications are &quot;
l_string|&quot;incompatible. Setting MDI-X to a compatible value.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
