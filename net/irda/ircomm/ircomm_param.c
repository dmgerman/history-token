multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_param.c&n; * Version:       1.0&n; * Description:   Parameter handling for the IrCOMM protocol&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Jun  7 10:25:11 1999&n; * Modified at:   Sun Jan 30 14:32:03 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/parameters.h&gt;
macro_line|#include &lt;net/irda/ircomm_core.h&gt;
macro_line|#include &lt;net/irda/ircomm_tty_attach.h&gt;
macro_line|#include &lt;net/irda/ircomm_tty.h&gt;
macro_line|#include &lt;net/irda/ircomm_param.h&gt;
r_static
r_int
id|ircomm_param_service_type
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_port_type
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_port_name
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_service_type
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_data_rate
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_data_format
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_flow_control
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_xon_xoff
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_enq_ack
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_line_status
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_dte
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_dce
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
r_static
r_int
id|ircomm_param_poll
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
suffix:semicolon
DECL|variable|pi_minor_call_table_common
r_static
id|pi_minor_info_t
id|pi_minor_call_table_common
(braket
)braket
op_assign
(brace
(brace
id|ircomm_param_service_type
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_port_type
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_port_name
comma
id|PV_STRING
)brace
)brace
suffix:semicolon
DECL|variable|pi_minor_call_table_non_raw
r_static
id|pi_minor_info_t
id|pi_minor_call_table_non_raw
(braket
)braket
op_assign
(brace
(brace
id|ircomm_param_data_rate
comma
id|PV_INT_32_BITS
op_or
id|PV_BIG_ENDIAN
)brace
comma
(brace
id|ircomm_param_data_format
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_flow_control
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_xon_xoff
comma
id|PV_INT_16_BITS
)brace
comma
(brace
id|ircomm_param_enq_ack
comma
id|PV_INT_16_BITS
)brace
comma
(brace
id|ircomm_param_line_status
comma
id|PV_INT_8_BITS
)brace
)brace
suffix:semicolon
DECL|variable|pi_minor_call_table_9_wire
r_static
id|pi_minor_info_t
id|pi_minor_call_table_9_wire
(braket
)braket
op_assign
(brace
(brace
id|ircomm_param_dte
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_dce
comma
id|PV_INT_8_BITS
)brace
comma
(brace
id|ircomm_param_poll
comma
id|PV_NO_VALUE
)brace
comma
)brace
suffix:semicolon
DECL|variable|pi_major_call_table
r_static
id|pi_major_info_t
id|pi_major_call_table
(braket
)braket
op_assign
(brace
(brace
id|pi_minor_call_table_common
comma
l_int|3
)brace
comma
(brace
id|pi_minor_call_table_non_raw
comma
l_int|6
)brace
comma
(brace
id|pi_minor_call_table_9_wire
comma
l_int|3
)brace
multiline_comment|/* &t;{ pi_minor_call_table_centronics }  */
)brace
suffix:semicolon
DECL|variable|ircomm_param_info
id|pi_param_info_t
id|ircomm_param_info
op_assign
(brace
id|pi_major_call_table
comma
l_int|3
comma
l_int|0x0f
comma
l_int|4
)brace
suffix:semicolon
multiline_comment|/*&n; * Function ircomm_param_flush (self)&n; *&n; *    Flush (send) out all queued parameters&n; *&n; */
DECL|function|ircomm_param_flush
r_int
id|ircomm_param_flush
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
)paren
(brace
r_if
c_cond
(paren
id|self-&gt;ctrl_skb
)paren
(brace
id|ircomm_control_request
c_func
(paren
id|self-&gt;ircomm
comma
id|self-&gt;ctrl_skb
)paren
suffix:semicolon
id|self-&gt;ctrl_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_request (self, pi, flush)&n; *&n; *    Queue a parameter for the control channel&n; *&n; */
DECL|function|ircomm_param_request
r_int
id|ircomm_param_request
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
comma
id|__u8
id|pi
comma
r_int
id|flush
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|count
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|tty
op_assign
id|self-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Make sure we don&squot;t send parameters for raw mode */
r_if
c_cond
(paren
id|self-&gt;service_type
op_eq
id|IRCOMM_3_WIRE_RAW
)paren
r_return
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|skb
op_assign
id|self-&gt;ctrl_skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|self-&gt;max_header_size
)paren
suffix:semicolon
id|self-&gt;ctrl_skb
op_assign
id|skb
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Inserting is a little bit tricky since we don&squot;t know how much&n;&t; * room we will need. But this should hopefully work OK &n;&t; */
id|count
op_assign
id|irda_param_insert
c_func
(paren
id|self
comma
id|pi
comma
id|skb-&gt;tail
comma
id|skb_tailroom
c_func
(paren
id|skb
)paren
comma
op_amp
id|ircomm_param_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
(brace
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), no room for parameter!&bslash;n&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), skb-&gt;len=%d&bslash;n&quot;
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flush
)paren
(brace
multiline_comment|/* ircomm_tty_do_softint will take care of the rest */
id|queue_task
c_func
(paren
op_amp
id|self-&gt;tqueue
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_service_type (self, buf, len)&n; *&n; *    Handle service type, this function will both be called after the LM-IAS&n; *    query and then the remote device sends its initial paramters&n; *&n; */
DECL|function|ircomm_param_service_type
r_static
r_int
id|ircomm_param_service_type
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|__u8
id|service_type
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.service_type
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Find all common service types */
id|service_type
op_and_assign
id|self-&gt;service_type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|service_type
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), No common service type to use!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), services in common=%02x&bslash;n&quot;
comma
id|service_type
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now choose a preferred service type of those available&n;&t; */
r_if
c_cond
(paren
id|service_type
op_amp
id|IRCOMM_CENTRONICS
)paren
id|self-&gt;settings.service_type
op_assign
id|IRCOMM_CENTRONICS
suffix:semicolon
r_else
r_if
c_cond
(paren
id|service_type
op_amp
id|IRCOMM_9_WIRE
)paren
id|self-&gt;settings.service_type
op_assign
id|IRCOMM_9_WIRE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|service_type
op_amp
id|IRCOMM_3_WIRE
)paren
id|self-&gt;settings.service_type
op_assign
id|IRCOMM_3_WIRE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|service_type
op_amp
id|IRCOMM_3_WIRE_RAW
)paren
id|self-&gt;settings.service_type
op_assign
id|IRCOMM_3_WIRE_RAW
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), resulting service type=0x%02x&bslash;n&quot;
comma
id|self-&gt;settings.service_type
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Now the line is ready for some communication. Check if we are a&n;         * server, and send over some initial parameters &n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;client
op_logical_and
(paren
id|self-&gt;settings.service_type
op_ne
id|IRCOMM_3_WIRE_RAW
)paren
)paren
(brace
multiline_comment|/* Init connection */
id|ircomm_tty_send_initial_parameters
c_func
(paren
id|self
)paren
suffix:semicolon
id|ircomm_tty_link_established
c_func
(paren
id|self
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_port_type (self, param)&n; *&n; *    The port type parameter tells if the devices are serial or parallel.&n; *    Since we only advertise serial service, this parameter should only&n; *    be equal to IRCOMM_SERIAL.&n; */
DECL|function|ircomm_param_port_type
r_static
r_int
id|ircomm_param_port_type
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.i
op_assign
id|IRCOMM_SERIAL
suffix:semicolon
r_else
(brace
id|self-&gt;settings.port_type
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), port type=%d&bslash;n&quot;
comma
id|self-&gt;settings.port_type
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_port_name (self, param)&n; *&n; *    Exchange port name&n; *&n; */
DECL|function|ircomm_param_port_name
r_static
r_int
id|ircomm_param_port_name
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), not imp!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), port-name=%s&bslash;n&quot;
comma
id|param-&gt;pv.c
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|self-&gt;settings.port_name
comma
id|param-&gt;pv.c
comma
l_int|32
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_data_rate (self, param)&n; *&n; *    Exchange data rate to be used in this settings&n; *&n; */
DECL|function|ircomm_param_data_rate
r_static
r_int
id|ircomm_param_data_rate
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.data_rate
suffix:semicolon
r_else
id|self-&gt;settings.data_rate
op_assign
id|param-&gt;pv.i
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), data rate = %d&bslash;n&quot;
comma
id|param-&gt;pv.i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_data_format (self, param)&n; *&n; *    Exchange data format to be used in this settings&n; *&n; */
DECL|function|ircomm_param_data_format
r_static
r_int
id|ircomm_param_data_format
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.data_format
suffix:semicolon
r_else
id|self-&gt;settings.data_format
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_flow_control (self, param)&n; *&n; *    Exchange flow control settings to be used in this settings&n; *&n; */
DECL|function|ircomm_param_flow_control
r_static
r_int
id|ircomm_param_flow_control
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.flow_control
suffix:semicolon
r_else
id|self-&gt;settings.flow_control
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
id|__FUNCTION__
l_string|&quot;(), flow control = 0x%02x&bslash;n&quot;
comma
(paren
id|__u8
)paren
id|param-&gt;pv.i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_xon_xoff (self, param)&n; *&n; *    Exchange XON/XOFF characters&n; *&n; */
DECL|function|ircomm_param_xon_xoff
r_static
r_int
id|ircomm_param_xon_xoff
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.xonxoff
(braket
l_int|0
)braket
suffix:semicolon
id|param-&gt;pv.i
op_or_assign
id|self-&gt;settings.xonxoff
(braket
l_int|1
)braket
op_lshift
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|self-&gt;settings.xonxoff
(braket
l_int|0
)braket
op_assign
(paren
id|__u16
)paren
id|param-&gt;pv.i
op_amp
l_int|0xff
suffix:semicolon
id|self-&gt;settings.xonxoff
(braket
l_int|1
)braket
op_assign
(paren
id|__u16
)paren
id|param-&gt;pv.i
op_rshift
l_int|8
suffix:semicolon
)brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), XON/XOFF = 0x%02x,0x%02x&bslash;n&quot;
comma
id|param-&gt;pv.i
op_amp
l_int|0xff
comma
id|param-&gt;pv.i
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_enq_ack (self, param)&n; *&n; *    Exchange ENQ/ACK characters&n; *&n; */
DECL|function|ircomm_param_enq_ack
r_static
r_int
id|ircomm_param_enq_ack
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
(brace
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.enqack
(braket
l_int|0
)braket
suffix:semicolon
id|param-&gt;pv.i
op_or_assign
id|self-&gt;settings.enqack
(braket
l_int|1
)braket
op_lshift
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|self-&gt;settings.enqack
(braket
l_int|0
)braket
op_assign
(paren
id|__u16
)paren
id|param-&gt;pv.i
op_amp
l_int|0xff
suffix:semicolon
id|self-&gt;settings.enqack
(braket
l_int|1
)braket
op_assign
(paren
id|__u16
)paren
id|param-&gt;pv.i
op_rshift
l_int|8
suffix:semicolon
)brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), ENQ/ACK = 0x%02x,0x%02x&bslash;n&quot;
comma
id|param-&gt;pv.i
op_amp
l_int|0xff
comma
id|param-&gt;pv.i
op_rshift
l_int|8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_line_status (self, param)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_param_line_status
r_static
r_int
id|ircomm_param_line_status
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), not impl.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_dte (instance, param)&n; *&n; *    If we get here, there must be some sort of null-modem connection, and&n; *    we are probably working in server mode as well.&n; */
DECL|function|ircomm_param_dte
r_static
r_int
id|ircomm_param_dte
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|__u8
id|dte
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get
)paren
id|param-&gt;pv.i
op_assign
id|self-&gt;settings.dte
suffix:semicolon
r_else
(brace
id|dte
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
r_if
c_cond
(paren
id|dte
op_amp
id|IRCOMM_DELTA_DTR
)paren
id|self-&gt;settings.dce
op_or_assign
(paren
id|IRCOMM_DELTA_DSR
op_or
id|IRCOMM_DELTA_RI
op_or
id|IRCOMM_DELTA_CD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dte
op_amp
id|IRCOMM_DTR
)paren
id|self-&gt;settings.dce
op_or_assign
(paren
id|IRCOMM_DSR
op_or
id|IRCOMM_RI
op_or
id|IRCOMM_CD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dte
op_amp
id|IRCOMM_DELTA_RTS
)paren
id|self-&gt;settings.dce
op_or_assign
id|IRCOMM_DELTA_CTS
suffix:semicolon
r_if
c_cond
(paren
id|dte
op_amp
id|IRCOMM_RTS
)paren
id|self-&gt;settings.dce
op_or_assign
id|IRCOMM_CTS
suffix:semicolon
multiline_comment|/* Take appropriate actions */
id|ircomm_tty_check_modem_status
c_func
(paren
id|self
)paren
suffix:semicolon
multiline_comment|/* Null modem cable emulator */
id|self-&gt;settings.null_modem
op_assign
id|TRUE
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_dce (instance, param)&n; *&n; *    &n; *&n; */
DECL|function|ircomm_param_dce
r_static
r_int
id|ircomm_param_dce
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|__u8
id|dce
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|1
comma
id|__FUNCTION__
l_string|&quot;(), dce = 0x%02x&bslash;n&quot;
comma
(paren
id|__u8
)paren
id|param-&gt;pv.i
)paren
suffix:semicolon
id|dce
op_assign
(paren
id|__u8
)paren
id|param-&gt;pv.i
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|self-&gt;settings.dce
op_assign
id|dce
suffix:semicolon
multiline_comment|/* Check if any of the settings have changed */
r_if
c_cond
(paren
id|dce
op_amp
l_int|0x0f
)paren
(brace
r_if
c_cond
(paren
id|dce
op_amp
id|IRCOMM_DELTA_CTS
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), CTS &bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|ircomm_tty_check_modem_status
c_func
(paren
id|self
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function ircomm_param_poll (instance, param)&n; *&n; *    Called when the peer device is polling for the line settings&n; *&n; */
DECL|function|ircomm_param_poll
r_static
r_int
id|ircomm_param_poll
c_func
(paren
r_void
op_star
id|instance
comma
id|irda_param_t
op_star
id|param
comma
r_int
id|get
)paren
(brace
r_struct
id|ircomm_tty_cb
op_star
id|self
op_assign
(paren
r_struct
id|ircomm_tty_cb
op_star
)paren
id|instance
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRCOMM_TTY_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Poll parameters are always of lenght 0 (just a signal) */
r_if
c_cond
(paren
op_logical_neg
id|get
)paren
(brace
multiline_comment|/* Respond with DTE line settings */
id|ircomm_param_request
c_func
(paren
id|self
comma
id|IRCOMM_DTE
comma
id|TRUE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
