multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*-------------------------------------------------------------------------*&n; * SL811HS virtual root hub&n; *  &n; * based on usb-ohci.c by R. Weissgaerber et al.&n; *-------------------------------------------------------------------------*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; *-------------------------------------------------------------------------*/
multiline_comment|/* FIXME:  reuse the root hub framework in usbcore, shrinking this code.  */
macro_line|#ifdef DEBUG
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
r_static
id|__u32
id|getPortStatusAndChange
(paren
id|hci_t
op_star
id|hci
)paren
suffix:semicolon
r_static
r_void
id|setPortStatus
(paren
id|hci_t
op_star
id|hci
comma
id|__u16
id|bitPos
)paren
suffix:semicolon
r_static
r_void
id|setPortChange
(paren
id|hci_t
op_star
id|hci
comma
id|__u16
id|bitPos
)paren
suffix:semicolon
r_static
r_void
id|clrPortStatus
(paren
id|hci_t
op_star
id|hci
comma
id|__u16
id|bitPos
)paren
suffix:semicolon
r_static
r_void
id|clrPortChange
(paren
id|hci_t
op_star
id|hci
comma
id|__u16
id|bitPos
)paren
suffix:semicolon
r_static
r_int
id|USBReset
(paren
id|hci_t
op_star
id|hci
)paren
suffix:semicolon
r_static
r_int
id|cc_to_error
(paren
r_int
id|cc
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*&n; * Virtual Root Hub &n; *-------------------------------------------------------------------------*/
multiline_comment|/* Device descriptor */
DECL|variable|root_hub_dev_des
r_static
id|__u8
id|root_hub_dev_des
(braket
)braket
op_assign
(brace
l_int|0x12
comma
multiline_comment|/*  __u8  bLength; */
l_int|0x01
comma
multiline_comment|/*  __u8  bDescriptorType; Device */
l_int|0x10
comma
multiline_comment|/*  __u16 bcdUSB; v1.1 */
l_int|0x01
comma
l_int|0x09
comma
multiline_comment|/*  __u8  bDeviceClass; HUB_CLASSCODE */
l_int|0x00
comma
multiline_comment|/*  __u8  bDeviceSubClass; */
l_int|0x00
comma
multiline_comment|/*  __u8  bDeviceProtocol; */
l_int|0x08
comma
multiline_comment|/*  __u8  bMaxPacketSize0; 8 Bytes */
l_int|0x00
comma
multiline_comment|/*  __u16 idVendor; */
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/*  __u16 idProduct; */
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/*  __u16 bcdDevice; */
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/*  __u8  iManufacturer; */
l_int|0x02
comma
multiline_comment|/*  __u8  iProduct; */
l_int|0x01
comma
multiline_comment|/*  __u8  iSerialNumber; */
l_int|0x01
multiline_comment|/*  __u8  bNumConfigurations; */
)brace
suffix:semicolon
multiline_comment|/* Configuration descriptor */
DECL|variable|root_hub_config_des
r_static
id|__u8
id|root_hub_config_des
(braket
)braket
op_assign
(brace
l_int|0x09
comma
multiline_comment|/*  __u8  bLength; */
l_int|0x02
comma
multiline_comment|/*  __u8  bDescriptorType; Configuration */
l_int|0x19
comma
multiline_comment|/*  __u16 wTotalLength; */
l_int|0x00
comma
l_int|0x01
comma
multiline_comment|/*  __u8  bNumInterfaces; */
l_int|0x01
comma
multiline_comment|/*  __u8  bConfigurationValue; */
l_int|0x00
comma
multiline_comment|/*  __u8  iConfiguration; */
l_int|0x40
comma
multiline_comment|/*  __u8  bmAttributes; &n;&t;&t;&t;&t;   Bit 7: Bus-powered, 6: Self-powered, 5 Remote-wakwup, &n;&t;&t;&t;&t;   4..0: resvd */
l_int|0x00
comma
multiline_comment|/*  __u8  MaxPower; */
multiline_comment|/* interface */
l_int|0x09
comma
multiline_comment|/*  __u8  if_bLength; */
l_int|0x04
comma
multiline_comment|/*  __u8  if_bDescriptorType; Interface */
l_int|0x00
comma
multiline_comment|/*  __u8  if_bInterfaceNumber; */
l_int|0x00
comma
multiline_comment|/*  __u8  if_bAlternateSetting; */
l_int|0x01
comma
multiline_comment|/*  __u8  if_bNumEndpoints; */
l_int|0x09
comma
multiline_comment|/*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
l_int|0x00
comma
multiline_comment|/*  __u8  if_bInterfaceSubClass; */
l_int|0x00
comma
multiline_comment|/*  __u8  if_bInterfaceProtocol; */
l_int|0x00
comma
multiline_comment|/*  __u8  if_iInterface; */
multiline_comment|/* endpoint */
l_int|0x07
comma
multiline_comment|/*  __u8  ep_bLength; */
l_int|0x05
comma
multiline_comment|/*  __u8  ep_bDescriptorType; Endpoint */
l_int|0x81
comma
multiline_comment|/*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
l_int|0x03
comma
multiline_comment|/*  __u8  ep_bmAttributes; Interrupt */
l_int|0x02
comma
multiline_comment|/*  __u16 ep_wMaxPacketSize; ((MAX_ROOT_PORTS + 1) / 8 */
l_int|0x00
comma
l_int|0xff
multiline_comment|/*  __u8  ep_bInterval; 255 ms */
)brace
suffix:semicolon
multiline_comment|/* Hub class-specific descriptor is constructed dynamically */
multiline_comment|/***************************************************************************&n; * Function Name : rh_send_irq&n; * &n; * This function examine the port change in the virtual root hub.&n; * &n; * Note: This function assumes only one port exist in the root hub.&n; *&n; * Input:  hci = data structure for the host controller&n; *         rh_data = The pointer to port change data&n; *         rh_len = length of the data in bytes&n; *&n; * Return: length of data  &n; **************************************************************************/
DECL|function|rh_send_irq
r_static
r_int
id|rh_send_irq
(paren
id|hci_t
op_star
id|hci
comma
r_void
op_star
id|rh_data
comma
r_int
id|rh_len
)paren
(brace
r_int
id|num_ports
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|len
suffix:semicolon
id|__u8
id|data
(braket
l_int|8
)braket
suffix:semicolon
id|DBGFUNC
(paren
l_string|&quot;enter rh_send_irq: &bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Assuming the root hub has one port.  This value need to change if&n;&t; * there are more than one port for the root hub&n;&t; */
id|num_ports
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* The root hub status is not implemented, it basically has two fields:&n;&t; *     -- Local Power Status&n;&t; *     -- Over Current Indicator&n;&t; *     -- Local Power Change&n;&t; *     -- Over Current Indicator&n;&t; *&n;&t; * Right now, It is assume the power is good and no changes &n;&t; */
op_star
(paren
id|__u8
op_star
)paren
id|data
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_star
(paren
id|__u8
op_star
)paren
id|data
suffix:semicolon
multiline_comment|/* Has the port status change within the root hub: It checks for&n;&t; *      -- Port Connect Status change&n;&t; *      -- Port Enable Change&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_ports
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
(paren
id|__u8
op_star
)paren
(paren
id|data
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_div
l_int|8
)paren
op_or_assign
(paren
(paren
(paren
id|getPortStatusAndChange
(paren
id|hci
)paren
op_rshift
l_int|16
)paren
op_amp
(paren
id|PORT_CONNECT_STAT
op_or
id|PORT_ENABLE_STAT
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_lshift
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_mod
l_int|8
)paren
suffix:semicolon
id|ret
op_add_assign
op_star
(paren
id|__u8
op_star
)paren
(paren
id|data
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_div
l_int|8
)paren
suffix:semicolon
multiline_comment|/* After the port change is read, it should be reset so the next time &n;&t;&t; * is it doesn&squot;t trigger a change again */
)brace
id|len
op_assign
id|i
op_div
l_int|8
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|memcpy
(paren
id|rh_data
comma
id|data
comma
id|min
(paren
id|len
comma
id|min
(paren
id|rh_len
comma
(paren
r_int
)paren
r_sizeof
(paren
id|data
)paren
)paren
)paren
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***************************************************************************&n; * Function Name : rh_int_timer_do&n; * &n; * This function is called when the timer expires.  It gets the the port &n; * change data and pass along to the upper protocol.&n; * &n; * Note:  The virtual root hub interrupt pipe are polled by the timer&n; *        every &quot;interval&quot; ms&n; *&n; * Input:  ptr = ptr to the urb&n; *&n; * Return: none  &n; **************************************************************************/
DECL|function|rh_int_timer_do
r_static
r_void
id|rh_int_timer_do
(paren
r_int
r_int
id|ptr
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|urb
op_star
id|urb
op_assign
(paren
r_struct
id|urb
op_star
)paren
id|ptr
suffix:semicolon
id|hci_t
op_star
id|hci
op_assign
id|urb-&gt;dev-&gt;bus-&gt;hcpriv
suffix:semicolon
id|DBGFUNC
(paren
l_string|&quot;enter rh_int_timer_do&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci-&gt;rh.send
)paren
(brace
id|len
op_assign
id|rh_send_irq
(paren
id|hci
comma
id|urb-&gt;transfer_buffer
comma
id|urb-&gt;transfer_buffer_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|urb-&gt;actual_length
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|urb_debug
op_eq
l_int|2
)paren
id|urb_print
(paren
id|urb
comma
l_string|&quot;RET-t(rh)&quot;
comma
id|usb_pipeout
(paren
id|urb-&gt;pipe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;complete
)paren
(brace
id|urb-&gt;complete
(paren
id|urb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* re-activate the timer */
id|rh_init_int_timer
(paren
id|urb
)paren
suffix:semicolon
)brace
multiline_comment|/***************************************************************************&n; * Function Name : rh_init_int_timer&n; * &n; * This function creates a timer that act as interrupt pipe in the&n; * virtual hub.   &n; * &n; * Note:  The virtual root hub&squot;s interrupt pipe are polled by the timer&n; *        every &quot;interval&quot; ms&n; *&n; * Input: urb = USB request block &n; *&n; * Return: 0  &n; **************************************************************************/
DECL|function|rh_init_int_timer
r_static
r_int
id|rh_init_int_timer
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|hci_t
op_star
id|hci
op_assign
id|urb-&gt;dev-&gt;bus-&gt;hcpriv
suffix:semicolon
id|hci-&gt;rh.interval
op_assign
id|urb-&gt;interval
suffix:semicolon
id|init_timer
(paren
op_amp
id|hci-&gt;rh.rh_int_timer
)paren
suffix:semicolon
id|hci-&gt;rh.rh_int_timer.function
op_assign
id|rh_int_timer_do
suffix:semicolon
id|hci-&gt;rh.rh_int_timer.data
op_assign
(paren
r_int
r_int
)paren
id|urb
suffix:semicolon
id|hci-&gt;rh.rh_int_timer.expires
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_star
(paren
id|urb-&gt;interval
OL
l_int|30
ques
c_cond
l_int|30
suffix:colon
id|urb-&gt;interval
)paren
)paren
op_div
l_int|1000
suffix:semicolon
id|add_timer
(paren
op_amp
id|hci-&gt;rh.rh_int_timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* for returning string descriptors in UTF-16LE */
DECL|function|ascii2utf
r_static
r_int
id|ascii2utf
(paren
r_char
op_star
id|ascii
comma
id|__u8
op_star
id|utf
comma
r_int
id|utfmax
)paren
(brace
r_int
id|retval
suffix:semicolon
r_for
c_loop
(paren
id|retval
op_assign
l_int|0
suffix:semicolon
op_star
id|ascii
op_logical_and
id|utfmax
OG
l_int|1
suffix:semicolon
id|utfmax
op_sub_assign
l_int|2
comma
id|retval
op_add_assign
l_int|2
)paren
(brace
op_star
id|utf
op_increment
op_assign
op_star
id|ascii
op_increment
op_amp
l_int|0x7f
suffix:semicolon
op_star
id|utf
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|root_hub_string
r_static
r_int
id|root_hub_string
(paren
r_int
id|id
comma
r_int
id|serial
comma
r_char
op_star
id|type
comma
id|__u8
op_star
id|data
comma
r_int
id|len
)paren
(brace
r_char
id|buf
(braket
l_int|30
)braket
suffix:semicolon
singleline_comment|// assert (len &gt; (2 * (sizeof (buf) + 1)));
singleline_comment|// assert (strlen (type) &lt;= 8);
singleline_comment|// language ids
r_if
c_cond
(paren
id|id
op_eq
l_int|0
)paren
(brace
op_star
id|data
op_increment
op_assign
l_int|4
suffix:semicolon
op_star
id|data
op_increment
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* 4 bytes data */
op_star
id|data
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|data
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* some language id */
r_return
l_int|4
suffix:semicolon
singleline_comment|// serial number
)brace
r_else
r_if
c_cond
(paren
id|id
op_eq
l_int|1
)paren
(brace
id|sprintf
(paren
id|buf
comma
l_string|&quot;%x&quot;
comma
id|serial
)paren
suffix:semicolon
singleline_comment|// product description
)brace
r_else
r_if
c_cond
(paren
id|id
op_eq
l_int|2
)paren
(brace
id|sprintf
(paren
id|buf
comma
l_string|&quot;USB %s Root Hub&quot;
comma
id|type
)paren
suffix:semicolon
singleline_comment|// id 3 == vendor description
singleline_comment|// unsupported IDs --&gt; &quot;stall&quot;
)brace
r_else
r_return
l_int|0
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
l_int|2
op_plus
id|ascii2utf
(paren
id|buf
comma
id|data
op_plus
l_int|2
comma
id|len
op_minus
l_int|2
)paren
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
l_int|3
suffix:semicolon
r_return
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* helper macro */
DECL|macro|OK
mdefine_line|#define OK(x) &t;&t;&t;len = (x); break
multiline_comment|/***************************************************************************&n; * Function Name : rh_submit_urb&n; * &n; * This function handles all USB request to the the virtual root hub&n; * &n; * Input: urb = USB request block &n; *&n; * Return: 0  &n; **************************************************************************/
DECL|function|rh_submit_urb
r_static
r_int
id|rh_submit_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_device
op_star
id|usb_dev
op_assign
id|urb-&gt;dev
suffix:semicolon
id|hci_t
op_star
id|hci
op_assign
id|usb_dev-&gt;bus-&gt;hcpriv
suffix:semicolon
r_int
r_int
id|pipe
op_assign
id|urb-&gt;pipe
suffix:semicolon
r_struct
id|usb_ctrlrequest
op_star
id|cmd
op_assign
(paren
r_struct
id|usb_ctrlrequest
op_star
)paren
id|urb-&gt;setup_packet
suffix:semicolon
r_void
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_int
id|leni
op_assign
id|urb-&gt;transfer_buffer_length
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|status
op_assign
id|TD_CC_NOERROR
suffix:semicolon
id|__u32
id|datab
(braket
l_int|4
)braket
suffix:semicolon
id|__u8
op_star
id|data_buf
op_assign
(paren
id|__u8
op_star
)paren
id|datab
suffix:semicolon
id|__u16
id|bmRType_bReq
suffix:semicolon
id|__u16
id|wValue
suffix:semicolon
id|__u16
id|wIndex
suffix:semicolon
id|__u16
id|wLength
suffix:semicolon
id|DBGFUNC
(paren
l_string|&quot;enter rh_submit_urb&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_pipeint
(paren
id|pipe
)paren
)paren
(brace
id|hci-&gt;rh.urb
op_assign
id|urb
suffix:semicolon
id|hci-&gt;rh.send
op_assign
l_int|1
suffix:semicolon
id|hci-&gt;rh.interval
op_assign
id|urb-&gt;interval
suffix:semicolon
id|rh_init_int_timer
(paren
id|urb
)paren
suffix:semicolon
id|urb-&gt;status
op_assign
id|cc_to_error
(paren
id|TD_CC_NOERROR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|bmRType_bReq
op_assign
id|cmd-&gt;bRequestType
op_or
(paren
id|cmd-&gt;bRequest
op_lshift
l_int|8
)paren
suffix:semicolon
id|wValue
op_assign
id|le16_to_cpu
(paren
id|cmd-&gt;wValue
)paren
suffix:semicolon
id|wIndex
op_assign
id|le16_to_cpu
(paren
id|cmd-&gt;wIndex
)paren
suffix:semicolon
id|wLength
op_assign
id|le16_to_cpu
(paren
id|cmd-&gt;wLength
)paren
suffix:semicolon
id|DBG
(paren
l_string|&quot;rh_submit_urb, req = %d(%x) len=%d&quot;
comma
id|bmRType_bReq
comma
id|bmRType_bReq
comma
id|wLength
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bmRType_bReq
)paren
(brace
multiline_comment|/* Request Destination:&n;&t;&t;   without flags: Device, &n;&t;&t;   RH_INTERFACE: interface, &n;&t;&t;   RH_ENDPOINT: endpoint,&n;&t;&t;   RH_CLASS means HUB here, &n;&t;&t;   RH_OTHER | RH_CLASS  almost ever means HUB_PORT here &n;&t;&t; */
r_case
id|RH_GET_STATUS
suffix:colon
op_star
(paren
id|__u16
op_star
)paren
id|data_buf
op_assign
id|cpu_to_le16
(paren
l_int|1
)paren
suffix:semicolon
id|OK
(paren
l_int|2
)paren
suffix:semicolon
r_case
id|RH_GET_STATUS
op_or
id|RH_INTERFACE
suffix:colon
op_star
(paren
id|__u16
op_star
)paren
id|data_buf
op_assign
id|cpu_to_le16
(paren
l_int|0
)paren
suffix:semicolon
id|OK
(paren
l_int|2
)paren
suffix:semicolon
r_case
id|RH_GET_STATUS
op_or
id|RH_ENDPOINT
suffix:colon
op_star
(paren
id|__u16
op_star
)paren
id|data_buf
op_assign
id|cpu_to_le16
(paren
l_int|0
)paren
suffix:semicolon
id|OK
(paren
l_int|2
)paren
suffix:semicolon
r_case
id|RH_GET_STATUS
op_or
id|RH_CLASS
suffix:colon
op_star
(paren
id|__u32
op_star
)paren
id|data_buf
op_assign
id|cpu_to_le32
(paren
l_int|0
)paren
suffix:semicolon
id|OK
(paren
l_int|4
)paren
suffix:semicolon
r_case
id|RH_GET_STATUS
op_or
id|RH_OTHER
op_or
id|RH_CLASS
suffix:colon
op_star
(paren
id|__u32
op_star
)paren
id|data_buf
op_assign
id|cpu_to_le32
(paren
id|getPortStatusAndChange
(paren
id|hci
)paren
)paren
suffix:semicolon
id|OK
(paren
l_int|4
)paren
suffix:semicolon
r_case
id|RH_CLEAR_FEATURE
op_or
id|RH_ENDPOINT
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
(paren
id|RH_ENDPOINT_STALL
)paren
suffix:colon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RH_CLEAR_FEATURE
op_or
id|RH_CLASS
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
id|RH_C_HUB_LOCAL_POWER
suffix:colon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_HUB_OVER_CURRENT
)paren
suffix:colon
multiline_comment|/* Over Current Not Implemented */
id|OK
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RH_CLEAR_FEATURE
op_or
id|RH_OTHER
op_or
id|RH_CLASS
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
(paren
id|RH_PORT_ENABLE
)paren
suffix:colon
id|clrPortStatus
(paren
id|hci
comma
id|PORT_ENABLE_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_PORT_SUSPEND
)paren
suffix:colon
id|clrPortStatus
(paren
id|hci
comma
id|PORT_SUSPEND_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_PORT_POWER
)paren
suffix:colon
id|clrPortStatus
(paren
id|hci
comma
id|PORT_POWER_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_PORT_CONNECTION
)paren
suffix:colon
id|clrPortChange
(paren
id|hci
comma
id|PORT_CONNECT_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_PORT_ENABLE
)paren
suffix:colon
id|clrPortChange
(paren
id|hci
comma
id|PORT_ENABLE_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_PORT_SUSPEND
)paren
suffix:colon
id|clrPortChange
(paren
id|hci
comma
id|PORT_SUSPEND_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_PORT_OVER_CURRENT
)paren
suffix:colon
id|clrPortChange
(paren
id|hci
comma
id|PORT_OVER_CURRENT_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_C_PORT_RESET
)paren
suffix:colon
id|clrPortChange
(paren
id|hci
comma
id|PORT_RESET_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RH_SET_FEATURE
op_or
id|RH_OTHER
op_or
id|RH_CLASS
suffix:colon
r_switch
c_cond
(paren
id|wValue
)paren
(brace
r_case
(paren
id|RH_PORT_SUSPEND
)paren
suffix:colon
id|setPortStatus
(paren
id|hci
comma
id|PORT_SUSPEND_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_PORT_RESET
)paren
suffix:colon
id|setPortStatus
(paren
id|hci
comma
id|PORT_RESET_STAT
)paren
suffix:semicolon
singleline_comment|// USBReset(hci);
id|clrPortChange
(paren
id|hci
comma
id|PORT_CONNECT_CHANGE
op_or
id|PORT_ENABLE_CHANGE
op_or
id|PORT_SUSPEND_CHANGE
op_or
id|PORT_OVER_CURRENT_CHANGE
)paren
suffix:semicolon
id|setPortChange
(paren
id|hci
comma
id|PORT_RESET_CHANGE
)paren
suffix:semicolon
id|clrPortStatus
(paren
id|hci
comma
id|PORT_RESET_STAT
)paren
suffix:semicolon
id|setPortStatus
(paren
id|hci
comma
id|PORT_ENABLE_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_PORT_POWER
)paren
suffix:colon
id|setPortStatus
(paren
id|hci
comma
id|PORT_POWER_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
(paren
id|RH_PORT_ENABLE
)paren
suffix:colon
id|setPortStatus
(paren
id|hci
comma
id|PORT_ENABLE_STAT
)paren
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RH_SET_ADDRESS
suffix:colon
id|hci-&gt;rh.devnum
op_assign
id|wValue
suffix:semicolon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|RH_GET_DESCRIPTOR
suffix:colon
id|DBGVERBOSE
(paren
l_string|&quot;rh_submit_urb: RH_GET_DESCRIPTOR, wValue = 0x%x&bslash;n&quot;
comma
id|wValue
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|wValue
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
(brace
r_case
(paren
l_int|0x01
)paren
suffix:colon
multiline_comment|/* device descriptor */
id|len
op_assign
id|min
(paren
id|leni
comma
id|min
(paren
(paren
id|__u16
)paren
r_sizeof
(paren
id|root_hub_dev_des
)paren
comma
id|wLength
)paren
)paren
suffix:semicolon
id|data_buf
op_assign
id|root_hub_dev_des
suffix:semicolon
id|OK
(paren
id|len
)paren
suffix:semicolon
r_case
(paren
l_int|0x02
)paren
suffix:colon
multiline_comment|/* configuration descriptor */
id|len
op_assign
id|min
(paren
id|leni
comma
id|min
(paren
(paren
id|__u16
)paren
r_sizeof
(paren
id|root_hub_config_des
)paren
comma
id|wLength
)paren
)paren
suffix:semicolon
id|data_buf
op_assign
id|root_hub_config_des
suffix:semicolon
id|OK
(paren
id|len
)paren
suffix:semicolon
r_case
(paren
l_int|0x03
)paren
suffix:colon
multiline_comment|/* string descriptors */
id|len
op_assign
id|root_hub_string
(paren
id|wValue
op_amp
l_int|0xff
comma
(paren
r_int
)paren
(paren
r_int
)paren
l_int|0
comma
l_string|&quot;SL811HS&quot;
comma
id|data
comma
id|wLength
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|data_buf
op_assign
id|data
suffix:semicolon
id|OK
(paren
id|min
(paren
id|leni
comma
id|len
)paren
)paren
suffix:semicolon
)brace
r_default
suffix:colon
id|status
op_assign
id|SL11H_STATMASK_STALL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|RH_GET_DESCRIPTOR
op_or
id|RH_CLASS
suffix:colon
id|data_buf
(braket
l_int|0
)braket
op_assign
l_int|9
suffix:semicolon
singleline_comment|// min length;
id|data_buf
(braket
l_int|1
)braket
op_assign
l_int|0x29
suffix:semicolon
id|data_buf
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
singleline_comment|// # of downstream port
id|data_buf
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|datab
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|data_buf
(braket
l_int|5
)braket
op_assign
l_int|50
suffix:semicolon
singleline_comment|// 100 ms for port reset
id|data_buf
(braket
l_int|7
)braket
op_assign
l_int|0xfc
suffix:semicolon
singleline_comment|// which port is attachable
r_if
c_cond
(paren
id|data_buf
(braket
l_int|2
)braket
OL
l_int|7
)paren
(brace
id|data_buf
(braket
l_int|8
)braket
op_assign
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
)brace
id|len
op_assign
id|min
(paren
id|leni
comma
id|min
(paren
(paren
id|__u16
)paren
id|data_buf
(braket
l_int|0
)braket
comma
id|wLength
)paren
)paren
suffix:semicolon
id|OK
(paren
id|len
)paren
suffix:semicolon
r_case
id|RH_GET_CONFIGURATION
suffix:colon
op_star
(paren
id|__u8
op_star
)paren
id|data_buf
op_assign
l_int|0x01
suffix:semicolon
id|OK
(paren
l_int|1
)paren
suffix:semicolon
r_case
id|RH_SET_CONFIGURATION
suffix:colon
id|OK
(paren
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
id|DBGERR
(paren
l_string|&quot;unsupported root hub command&quot;
)paren
suffix:semicolon
id|status
op_assign
id|SL11H_STATMASK_STALL
suffix:semicolon
)brace
id|len
op_assign
id|min
(paren
id|len
comma
id|leni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_ne
id|data_buf
)paren
id|memcpy
(paren
id|data
comma
id|data_buf
comma
id|len
)paren
suffix:semicolon
id|urb-&gt;actual_length
op_assign
id|len
suffix:semicolon
id|urb-&gt;status
op_assign
id|cc_to_error
(paren
id|status
)paren
suffix:semicolon
id|urb-&gt;hcpriv
op_assign
l_int|NULL
suffix:semicolon
id|urb-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;complete
)paren
(brace
id|urb-&gt;complete
(paren
id|urb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***************************************************************************&n; * Function Name : rh_unlink_urb&n; * &n; * This function unlinks the URB &n; * &n; * Input: urb = USB request block &n; *&n; * Return: 0  &n; **************************************************************************/
DECL|function|rh_unlink_urb
r_static
r_int
id|rh_unlink_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|hci_t
op_star
id|hci
op_assign
id|urb-&gt;dev-&gt;bus-&gt;hcpriv
suffix:semicolon
id|DBGFUNC
(paren
l_string|&quot;enter rh_unlink_urb&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci-&gt;rh.urb
op_eq
id|urb
)paren
(brace
id|hci-&gt;rh.send
op_assign
l_int|0
suffix:semicolon
id|del_timer
(paren
op_amp
id|hci-&gt;rh.rh_int_timer
)paren
suffix:semicolon
id|hci-&gt;rh.urb
op_assign
l_int|NULL
suffix:semicolon
id|urb-&gt;hcpriv
op_assign
l_int|NULL
suffix:semicolon
id|usb_put_dev
(paren
id|urb-&gt;dev
)paren
suffix:semicolon
id|urb-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;transfer_flags
op_amp
id|URB_ASYNC_UNLINK
)paren
(brace
id|urb-&gt;status
op_assign
op_minus
id|ECONNRESET
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;complete
)paren
(brace
id|urb-&gt;complete
(paren
id|urb
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_else
id|urb-&gt;status
op_assign
op_minus
id|ENOENT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/***************************************************************************&n; * Function Name : rh_connect_rh&n; * &n; * This function connect the virtual root hub to the USB stack &n; * &n; * Input: urb = USB request block &n; *&n; * Return: 0  &n; **************************************************************************/
DECL|function|rh_connect_rh
r_static
r_int
id|rh_connect_rh
(paren
id|hci_t
op_star
id|hci
)paren
(brace
r_struct
id|usb_device
op_star
id|usb_dev
suffix:semicolon
id|hci-&gt;rh.devnum
op_assign
l_int|0
suffix:semicolon
id|usb_dev
op_assign
id|usb_alloc_dev
(paren
l_int|NULL
comma
id|hci-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usb_dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|hci-&gt;bus-&gt;root_hub
op_assign
id|usb_dev
suffix:semicolon
id|usb_connect
(paren
id|usb_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_new_device
(paren
id|usb_dev
)paren
op_ne
l_int|0
)paren
(brace
id|usb_put_dev
(paren
id|usb_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
