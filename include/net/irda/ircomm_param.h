multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_param.h&n; * Version:       1.0&n; * Description:   Parameter handling for the IrCOMM protocol&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Jun  7 08:47:28 1999&n; * Modified at:   Wed Aug 25 13:46:33 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef IRCOMM_PARAMS_H
DECL|macro|IRCOMM_PARAMS_H
mdefine_line|#define IRCOMM_PARAMS_H
macro_line|#include &lt;net/irda/parameters.h&gt;
multiline_comment|/* Parameters common to all service types */
DECL|macro|IRCOMM_SERVICE_TYPE
mdefine_line|#define IRCOMM_SERVICE_TYPE     0x00
DECL|macro|IRCOMM_PORT_TYPE
mdefine_line|#define IRCOMM_PORT_TYPE        0x01 /* Only used in LM-IAS */
DECL|macro|IRCOMM_PORT_NAME
mdefine_line|#define IRCOMM_PORT_NAME        0x02 /* Only used in LM-IAS */
multiline_comment|/* Parameters for both 3 wire and 9 wire */
DECL|macro|IRCOMM_DATA_RATE
mdefine_line|#define IRCOMM_DATA_RATE        0x10
DECL|macro|IRCOMM_DATA_FORMAT
mdefine_line|#define IRCOMM_DATA_FORMAT      0x11
DECL|macro|IRCOMM_FLOW_CONTROL
mdefine_line|#define IRCOMM_FLOW_CONTROL     0x12
DECL|macro|IRCOMM_XON_XOFF
mdefine_line|#define IRCOMM_XON_XOFF         0x13
DECL|macro|IRCOMM_ENQ_ACK
mdefine_line|#define IRCOMM_ENQ_ACK          0x14
DECL|macro|IRCOMM_LINE_STATUS
mdefine_line|#define IRCOMM_LINE_STATUS      0x15
DECL|macro|IRCOMM_BREAK
mdefine_line|#define IRCOMM_BREAK            0x16
multiline_comment|/* Parameters for 9 wire */
DECL|macro|IRCOMM_DTE
mdefine_line|#define IRCOMM_DTE              0x20
DECL|macro|IRCOMM_DCE
mdefine_line|#define IRCOMM_DCE              0x21
DECL|macro|IRCOMM_POLL
mdefine_line|#define IRCOMM_POLL             0x22
multiline_comment|/* Service type (details) */
DECL|macro|IRCOMM_3_WIRE_RAW
mdefine_line|#define IRCOMM_3_WIRE_RAW       0x01
DECL|macro|IRCOMM_3_WIRE
mdefine_line|#define IRCOMM_3_WIRE           0x02
DECL|macro|IRCOMM_9_WIRE
mdefine_line|#define IRCOMM_9_WIRE           0x04
DECL|macro|IRCOMM_CENTRONICS
mdefine_line|#define IRCOMM_CENTRONICS       0x08
multiline_comment|/* Port type (details) */
DECL|macro|IRCOMM_SERIAL
mdefine_line|#define IRCOMM_SERIAL           0x00
DECL|macro|IRCOMM_PARALLEL
mdefine_line|#define IRCOMM_PARALLEL         0x01
multiline_comment|/* Data format (details) */
DECL|macro|IRCOMM_WSIZE_5
mdefine_line|#define IRCOMM_WSIZE_5          0x00
DECL|macro|IRCOMM_WSIZE_6
mdefine_line|#define IRCOMM_WSIZE_6          0x01
DECL|macro|IRCOMM_WSIZE_7
mdefine_line|#define IRCOMM_WSIZE_7          0x02
DECL|macro|IRCOMM_WSIZE_8
mdefine_line|#define IRCOMM_WSIZE_8          0x03
DECL|macro|IRCOMM_1_STOP_BIT
mdefine_line|#define IRCOMM_1_STOP_BIT       0x00
DECL|macro|IRCOMM_2_STOP_BIT
mdefine_line|#define IRCOMM_2_STOP_BIT       0x04 /* 1.5 if char len 5 */
DECL|macro|IRCOMM_PARITY_DISABLE
mdefine_line|#define IRCOMM_PARITY_DISABLE   0x00
DECL|macro|IRCOMM_PARITY_ENABLE
mdefine_line|#define IRCOMM_PARITY_ENABLE    0x08
DECL|macro|IRCOMM_PARITY_ODD
mdefine_line|#define IRCOMM_PARITY_ODD       0x00
DECL|macro|IRCOMM_PARITY_EVEN
mdefine_line|#define IRCOMM_PARITY_EVEN      0x10
DECL|macro|IRCOMM_PARITY_MARK
mdefine_line|#define IRCOMM_PARITY_MARK      0x20
DECL|macro|IRCOMM_PARITY_SPACE
mdefine_line|#define IRCOMM_PARITY_SPACE     0x30
multiline_comment|/* Flow control */
DECL|macro|IRCOMM_XON_XOFF_IN
mdefine_line|#define IRCOMM_XON_XOFF_IN      0x01
DECL|macro|IRCOMM_XON_XOFF_OUT
mdefine_line|#define IRCOMM_XON_XOFF_OUT     0x02
DECL|macro|IRCOMM_RTS_CTS_IN
mdefine_line|#define IRCOMM_RTS_CTS_IN       0x04
DECL|macro|IRCOMM_RTS_CTS_OUT
mdefine_line|#define IRCOMM_RTS_CTS_OUT      0x08
DECL|macro|IRCOMM_DSR_DTR_IN
mdefine_line|#define IRCOMM_DSR_DTR_IN       0x10
DECL|macro|IRCOMM_DSR_DTR_OUT
mdefine_line|#define IRCOMM_DSR_DTR_OUT      0x20
DECL|macro|IRCOMM_ENQ_ACK_IN
mdefine_line|#define IRCOMM_ENQ_ACK_IN       0x40
DECL|macro|IRCOMM_ENQ_ACK_OUT
mdefine_line|#define IRCOMM_ENQ_ACK_OUT      0x80
multiline_comment|/* Line status */
DECL|macro|IRCOMM_OVERRUN_ERROR
mdefine_line|#define IRCOMM_OVERRUN_ERROR    0x02
DECL|macro|IRCOMM_PARITY_ERROR
mdefine_line|#define IRCOMM_PARITY_ERROR     0x04
DECL|macro|IRCOMM_FRAMING_ERROR
mdefine_line|#define IRCOMM_FRAMING_ERROR    0x08
multiline_comment|/* DTE (Data terminal equipment) line settings */
DECL|macro|IRCOMM_DELTA_DTR
mdefine_line|#define IRCOMM_DELTA_DTR        0x01
DECL|macro|IRCOMM_DELTA_RTS
mdefine_line|#define IRCOMM_DELTA_RTS        0x02
DECL|macro|IRCOMM_DTR
mdefine_line|#define IRCOMM_DTR              0x04
DECL|macro|IRCOMM_RTS
mdefine_line|#define IRCOMM_RTS              0x08
multiline_comment|/* DCE (Data communications equipment) line settings */
DECL|macro|IRCOMM_DELTA_CTS
mdefine_line|#define IRCOMM_DELTA_CTS        0x01  /* Clear to send has changed */
DECL|macro|IRCOMM_DELTA_DSR
mdefine_line|#define IRCOMM_DELTA_DSR        0x02  /* Data set ready has changed */
DECL|macro|IRCOMM_DELTA_RI
mdefine_line|#define IRCOMM_DELTA_RI         0x04  /* Ring indicator has changed */
DECL|macro|IRCOMM_DELTA_CD
mdefine_line|#define IRCOMM_DELTA_CD         0x08  /* Carrier detect has changed */
DECL|macro|IRCOMM_CTS
mdefine_line|#define IRCOMM_CTS              0x10  /* Clear to send is high */
DECL|macro|IRCOMM_DSR
mdefine_line|#define IRCOMM_DSR              0x20  /* Data set ready is high */
DECL|macro|IRCOMM_RI
mdefine_line|#define IRCOMM_RI               0x40  /* Ring indicator is high */
DECL|macro|IRCOMM_CD
mdefine_line|#define IRCOMM_CD               0x80  /* Carrier detect is high */
DECL|macro|IRCOMM_DCE_DELTA_ANY
mdefine_line|#define IRCOMM_DCE_DELTA_ANY    0x0f
multiline_comment|/*&n; * Parameter state&n; */
DECL|struct|ircomm_params
r_struct
id|ircomm_params
(brace
multiline_comment|/* General control params */
DECL|member|service_type
id|__u8
id|service_type
suffix:semicolon
DECL|member|port_type
id|__u8
id|port_type
suffix:semicolon
DECL|member|port_name
r_char
id|port_name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Control params for 3- and 9-wire service type */
DECL|member|data_rate
id|__u32
id|data_rate
suffix:semicolon
multiline_comment|/* Data rate in bps */
DECL|member|data_format
id|__u8
id|data_format
suffix:semicolon
DECL|member|flow_control
id|__u8
id|flow_control
suffix:semicolon
DECL|member|xonxoff
r_char
id|xonxoff
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|enqack
r_char
id|enqack
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|line_status
id|__u8
id|line_status
suffix:semicolon
DECL|member|_break
id|__u8
id|_break
suffix:semicolon
DECL|member|null_modem
id|__u8
id|null_modem
suffix:semicolon
multiline_comment|/* Control params for 9-wire service type */
DECL|member|dte
id|__u8
id|dte
suffix:semicolon
DECL|member|dce
id|__u8
id|dce
suffix:semicolon
DECL|member|poll
id|__u8
id|poll
suffix:semicolon
multiline_comment|/* Control params for Centronics service type */
)brace
suffix:semicolon
r_struct
id|ircomm_tty_cb
suffix:semicolon
multiline_comment|/* Forward decl. */
r_int
id|ircomm_param_flush
c_func
(paren
r_struct
id|ircomm_tty_cb
op_star
id|self
)paren
suffix:semicolon
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
suffix:semicolon
r_extern
id|pi_param_info_t
id|ircomm_param_info
suffix:semicolon
macro_line|#endif /* IRCOMM_PARAMS_H */
eof
