multiline_comment|/*&n; * Driver for ST5481 USB ISDN modem&n; *&n; * Author       Frode Isaksen&n; * Copyright    2001 by Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;st5481.h&quot;
multiline_comment|/* ======================================================================&n; * control pipe&n; */
multiline_comment|/*&n; * Send the next endpoint 0 request stored in the FIFO.&n; * Called either by the completion or by usb_ctrl_msg.&n; */
DECL|function|usb_next_ctrl_msg
r_static
r_void
id|usb_next_ctrl_msg
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|st5481_ctrl
op_star
id|ctrl
op_assign
op_amp
id|adapter-&gt;ctrl
suffix:semicolon
r_int
id|r_index
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|ctrl-&gt;busy
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|r_index
op_assign
id|fifo_remove
c_func
(paren
op_amp
id|ctrl-&gt;msg_fifo.f
)paren
)paren
OL
l_int|0
)paren
(brace
id|test_and_clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|ctrl-&gt;busy
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|urb-&gt;setup_packet
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|ctrl-&gt;msg_fifo.data
(braket
id|r_index
)braket
suffix:semicolon
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;request=0x%02x,value=0x%04x,index=%x&quot;
comma
(paren
(paren
r_struct
id|ctrl_msg
op_star
)paren
id|urb-&gt;setup_packet
)paren
op_member_access_from_pointer
id|dr.bRequest
comma
(paren
(paren
r_struct
id|ctrl_msg
op_star
)paren
id|urb-&gt;setup_packet
)paren
op_member_access_from_pointer
id|dr.wValue
comma
(paren
(paren
r_struct
id|ctrl_msg
op_star
)paren
id|urb-&gt;setup_packet
)paren
op_member_access_from_pointer
id|dr.wIndex
)paren
suffix:semicolon
singleline_comment|// Prepare the URB
id|urb-&gt;dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Asynchronous endpoint 0 request (async version of usb_control_msg).&n; * The request will be queued up in a FIFO if the endpoint is busy.&n; */
DECL|function|usb_ctrl_msg
r_void
id|usb_ctrl_msg
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u8
id|request
comma
id|u8
id|requesttype
comma
id|u16
id|value
comma
id|u16
id|index
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
r_struct
id|st5481_ctrl
op_star
id|ctrl
op_assign
op_amp
id|adapter-&gt;ctrl
suffix:semicolon
r_int
id|w_index
suffix:semicolon
r_struct
id|ctrl_msg
op_star
id|ctrl_msg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|w_index
op_assign
id|fifo_add
c_func
(paren
op_amp
id|ctrl-&gt;msg_fifo.f
)paren
)paren
OL
l_int|0
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;control msg FIFO full&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ctrl_msg
op_assign
op_amp
id|ctrl-&gt;msg_fifo.data
(braket
id|w_index
)braket
suffix:semicolon
id|ctrl_msg-&gt;dr.bRequestType
op_assign
id|requesttype
suffix:semicolon
id|ctrl_msg-&gt;dr.bRequest
op_assign
id|request
suffix:semicolon
id|ctrl_msg-&gt;dr.wValue
op_assign
id|cpu_to_le16p
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
id|ctrl_msg-&gt;dr.wIndex
op_assign
id|cpu_to_le16p
c_func
(paren
op_amp
id|index
)paren
suffix:semicolon
id|ctrl_msg-&gt;dr.wLength
op_assign
l_int|0
suffix:semicolon
id|ctrl_msg-&gt;complete
op_assign
id|complete
suffix:semicolon
id|ctrl_msg-&gt;context
op_assign
id|context
suffix:semicolon
id|usb_next_ctrl_msg
c_func
(paren
id|ctrl-&gt;urb
comma
id|adapter
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Asynchronous endpoint 0 device request.&n; */
DECL|function|st5481_usb_device_ctrl_msg
r_void
id|st5481_usb_device_ctrl_msg
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u8
id|request
comma
id|u16
id|value
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
id|usb_ctrl_msg
c_func
(paren
id|adapter
comma
id|request
comma
id|USB_DIR_OUT
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
comma
id|value
comma
l_int|0
comma
id|complete
comma
id|context
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Asynchronous pipe reset (async version of usb_clear_halt).&n; */
DECL|function|st5481_usb_pipe_reset
r_void
id|st5481_usb_pipe_reset
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
id|u_char
id|pipe
comma
id|ctrl_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;pipe=%02x&quot;
comma
id|pipe
)paren
suffix:semicolon
id|usb_ctrl_msg
c_func
(paren
id|adapter
comma
id|USB_REQ_CLEAR_FEATURE
comma
id|USB_DIR_OUT
op_or
id|USB_RECIP_ENDPOINT
comma
l_int|0
comma
id|pipe
comma
id|complete
comma
id|context
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  Physical level functions&n;*/
DECL|function|st5481_ph_command
r_void
id|st5481_ph_command
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
comma
r_int
r_int
id|command
)paren
(brace
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;command=%s&quot;
comma
id|ST5481_CMD_string
c_func
(paren
id|command
)paren
)paren
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|TXCI
comma
id|command
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The request on endpoint 0 has completed.&n; * Call the user provided completion routine and try&n; * to send the next request.&n; */
DECL|function|usb_ctrl_complete
r_static
r_void
id|usb_ctrl_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|urb-&gt;context
suffix:semicolon
r_struct
id|st5481_ctrl
op_star
id|ctrl
op_assign
op_amp
id|adapter-&gt;ctrl
suffix:semicolon
r_struct
id|ctrl_msg
op_star
id|ctrl_msg
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;status
op_ne
op_minus
id|ENOENT
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;urb status %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;urb killed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
singleline_comment|// Give up
)brace
)brace
id|ctrl_msg
op_assign
(paren
r_struct
id|ctrl_msg
op_star
)paren
id|urb-&gt;setup_packet
suffix:semicolon
r_if
c_cond
(paren
id|ctrl_msg-&gt;dr.bRequest
op_eq
id|USB_REQ_CLEAR_FEATURE
)paren
(brace
multiline_comment|/* Special case handling for pipe reset */
id|le16_to_cpus
c_func
(paren
op_amp
id|ctrl_msg-&gt;dr.wIndex
)paren
suffix:semicolon
id|usb_endpoint_running
c_func
(paren
id|adapter-&gt;usb_dev
comma
id|ctrl_msg-&gt;dr.wIndex
op_amp
op_complement
id|USB_DIR_IN
comma
(paren
id|ctrl_msg-&gt;dr.wIndex
op_amp
id|USB_DIR_IN
)paren
op_eq
l_int|0
)paren
suffix:semicolon
multiline_comment|/* toggle is reset on clear */
id|usb_settoggle
c_func
(paren
id|adapter-&gt;usb_dev
comma
id|ctrl_msg-&gt;dr.wIndex
op_amp
op_complement
id|USB_DIR_IN
comma
(paren
id|ctrl_msg-&gt;dr.wIndex
op_amp
id|USB_DIR_IN
)paren
op_eq
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_msg-&gt;complete
)paren
id|ctrl_msg
op_member_access_from_pointer
id|complete
c_func
(paren
id|ctrl_msg-&gt;context
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|ctrl-&gt;busy
)paren
suffix:semicolon
singleline_comment|// Try to send next control message
id|usb_next_ctrl_msg
c_func
(paren
id|urb
comma
id|adapter
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * interrupt pipe&n; */
multiline_comment|/*&n; * The interrupt endpoint will be called when any&n; * of the 6 registers changes state (depending on masks).&n; * Decode the register values and schedule a private event.&n; * Called at interrupt.&n; */
DECL|function|usb_int_complete
r_static
r_void
id|usb_int_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|u_char
op_star
id|data
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
id|u_char
id|irqbyte
suffix:semicolon
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;status
op_ne
op_minus
id|ENOENT
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;urb status %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;urb killed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
singleline_comment|// Give up
)brace
)brace
id|DBG_PACKET
c_func
(paren
l_int|1
comma
id|data
comma
id|INT_PKT_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;actual_length
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
id|irqbyte
op_assign
id|data
(braket
id|MPINT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irqbyte
op_amp
id|DEN_INT
)paren
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_DEN
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqbyte
op_amp
id|DCOLL_INT
)paren
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_COLL
comma
l_int|NULL
)paren
suffix:semicolon
id|irqbyte
op_assign
id|data
(braket
id|FFINT_D
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irqbyte
op_amp
id|OUT_UNDERRUN
)paren
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;d_out.fsm
comma
id|EV_DOUT_UNDERRUN
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqbyte
op_amp
id|OUT_DOWN
)paren
suffix:semicolon
singleline_comment|//&t;&t;printk(&quot;OUT_DOWN&bslash;n&quot;);
id|irqbyte
op_assign
id|data
(braket
id|MPINT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irqbyte
op_amp
id|RXCI_INT
)paren
id|FsmEvent
c_func
(paren
op_amp
id|adapter-&gt;l1m
comma
id|data
(braket
id|CCIST
)braket
op_amp
l_int|0x0f
comma
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
id|adapter-&gt;bcs
(braket
id|j
)braket
dot
id|b_out.flow_event
op_or_assign
id|data
(braket
id|FFINT_B1
op_plus
id|j
)braket
suffix:semicolon
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * initialization&n; */
DECL|function|st5481_setup_usb
r_int
id|__devinit
id|st5481_setup_usb
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
r_struct
id|st5481_ctrl
op_star
id|ctrl
op_assign
op_amp
id|adapter-&gt;ctrl
suffix:semicolon
r_struct
id|st5481_intr
op_star
id|intr
op_assign
op_amp
id|adapter-&gt;intr
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|altsetting
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_int
id|status
suffix:semicolon
id|urb_t
op_star
id|urb
suffix:semicolon
id|u_char
op_star
id|buf
suffix:semicolon
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|usb_set_configuration
(paren
id|dev
comma
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|bConfigurationValue
)paren
)paren
OL
l_int|0
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;set_configuration failed,status=%d&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
id|altsetting
op_assign
op_amp
(paren
id|dev-&gt;config-&gt;interface
(braket
l_int|0
)braket
dot
id|altsetting
(braket
l_int|3
)braket
)paren
suffix:semicolon
singleline_comment|// Check if the config is sane
r_if
c_cond
(paren
id|altsetting-&gt;bNumEndpoints
op_ne
l_int|7
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;expecting 7 got %d endpoints!&quot;
comma
id|altsetting-&gt;bNumEndpoints
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
singleline_comment|// The descriptor is wrong for some early samples of the ST5481 chip
id|altsetting-&gt;endpoint
(braket
l_int|3
)braket
dot
id|wMaxPacketSize
op_assign
l_int|32
suffix:semicolon
id|altsetting-&gt;endpoint
(braket
l_int|4
)braket
dot
id|wMaxPacketSize
op_assign
l_int|32
suffix:semicolon
singleline_comment|// Use alternative setting 3 on interface 0 to have 2B+D
r_if
c_cond
(paren
(paren
id|status
op_assign
id|usb_set_interface
(paren
id|dev
comma
l_int|0
comma
l_int|3
)paren
)paren
OL
l_int|0
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;usb_set_interface failed,status=%d&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
singleline_comment|// Allocate URB for control endpoint
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ctrl-&gt;urb
op_assign
id|urb
suffix:semicolon
singleline_comment|// Fill the control URB
id|FILL_CONTROL_URB
(paren
id|urb
comma
id|dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
id|usb_ctrl_complete
comma
id|adapter
)paren
suffix:semicolon
id|fifo_init
c_func
(paren
op_amp
id|ctrl-&gt;msg_fifo.f
comma
id|ARRAY_SIZE
c_func
(paren
id|ctrl-&gt;msg_fifo.data
)paren
)paren
suffix:semicolon
singleline_comment|// Allocate URBs and buffers for interrupt endpoint
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|intr-&gt;urb
op_assign
id|urb
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|INT_PKT_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|endpoint
op_assign
op_amp
id|altsetting-&gt;endpoint
(braket
id|EP_INT
op_minus
l_int|1
)braket
suffix:semicolon
singleline_comment|// Fill the interrupt URB
id|FILL_INT_URB
c_func
(paren
id|urb
comma
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|buf
comma
id|INT_PKT_SIZE
comma
id|usb_int_complete
comma
id|adapter
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Release buffers and URBs for the interrupt and control&n; * endpoint.&n; */
DECL|function|st5481_release_usb
r_void
id|st5481_release_usb
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|st5481_intr
op_star
id|intr
op_assign
op_amp
id|adapter-&gt;intr
suffix:semicolon
r_struct
id|st5481_ctrl
op_star
id|ctrl
op_assign
op_amp
id|adapter-&gt;ctrl
suffix:semicolon
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
singleline_comment|// Stop and free Control and Interrupt URBs
id|usb_unlink_urb
c_func
(paren
id|ctrl-&gt;urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctrl-&gt;urb-&gt;transfer_buffer
)paren
id|kfree
c_func
(paren
id|ctrl-&gt;urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|ctrl-&gt;urb
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|intr-&gt;urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr-&gt;urb-&gt;transfer_buffer
)paren
id|kfree
c_func
(paren
id|intr-&gt;urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|intr-&gt;urb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Initialize the adapter.&n; */
DECL|function|st5481_start
r_void
id|__devinit
id|st5481_start
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
r_static
r_const
id|u8
id|init_cmd_table
(braket
)braket
op_assign
initialization_block
suffix:semicolon
r_struct
id|st5481_intr
op_star
id|intr
op_assign
op_amp
id|adapter-&gt;intr
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|u8
id|request
comma
id|value
suffix:semicolon
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|adapter-&gt;leds
op_assign
id|RED_LED
suffix:semicolon
singleline_comment|// Start receiving on the interrupt endpoint
id|SUBMIT_URB
c_func
(paren
id|intr-&gt;urb
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|request
op_assign
id|init_cmd_table
(braket
id|i
op_increment
)braket
)paren
)paren
(brace
id|value
op_assign
id|init_cmd_table
(braket
id|i
op_increment
)braket
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|request
comma
id|value
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|st5481_ph_command
c_func
(paren
id|adapter
comma
id|ST5481_CMD_PUP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reset the adapter to default values.&n; */
DECL|function|st5481_stop
r_void
id|__devexit
id|st5481_stop
c_func
(paren
r_struct
id|st5481_adapter
op_star
id|adapter
)paren
(brace
id|DBG
c_func
(paren
l_int|8
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|adapter
comma
id|SET_DEFAULT
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* ======================================================================&n; * isochronous USB  helpers&n; */
r_static
r_void
id|__devinit
DECL|function|fill_isoc_urb
id|fill_isoc_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|buf
comma
r_int
id|num_packets
comma
r_int
id|packet_size
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
r_int
id|k
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|urb-&gt;lock
)paren
suffix:semicolon
id|urb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|pipe
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|buf
suffix:semicolon
id|urb-&gt;number_of_packets
op_assign
id|num_packets
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|num_packets
op_star
id|packet_size
suffix:semicolon
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
id|urb-&gt;complete
op_assign
id|complete
suffix:semicolon
id|urb-&gt;context
op_assign
id|context
suffix:semicolon
id|urb-&gt;transfer_flags
op_assign
id|USB_ISO_ASAP
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|num_packets
suffix:semicolon
id|k
op_increment
)paren
(brace
id|urb-&gt;iso_frame_desc
(braket
id|k
)braket
dot
id|offset
op_assign
id|packet_size
op_star
id|k
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|k
)braket
dot
id|length
op_assign
id|packet_size
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|k
)braket
dot
id|actual_length
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_int
id|__devinit
DECL|function|st5481_setup_isocpipes
id|st5481_setup_isocpipes
c_func
(paren
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_int
id|num_packets
comma
r_int
id|packet_size
comma
r_int
id|buf_size
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
r_int
id|j
comma
id|retval
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|urb
(braket
id|j
)braket
op_assign
id|usb_alloc_urb
c_func
(paren
id|num_packets
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
(braket
id|j
)braket
)paren
r_goto
id|err
suffix:semicolon
singleline_comment|// Allocate memory for 2000bytes/sec (16Kb/s)
id|buf
op_assign
id|kmalloc
c_func
(paren
id|buf_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_goto
id|err
suffix:semicolon
singleline_comment|// Fill the isochronous URB
id|fill_isoc_urb
c_func
(paren
id|urb
(braket
id|j
)braket
comma
id|dev
comma
id|pipe
comma
id|buf
comma
id|num_packets
comma
id|packet_size
comma
id|complete
comma
id|context
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|urb
(braket
id|j
)braket
)paren
(brace
r_if
c_cond
(paren
id|urb
(braket
id|j
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
id|kfree
c_func
(paren
id|urb
(braket
id|j
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|st5481_release_isocpipes
r_void
id|st5481_release_isocpipes
c_func
(paren
r_struct
id|urb
op_star
id|urb
(braket
l_int|2
)braket
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|urb
(braket
id|j
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb
(braket
id|j
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
id|kfree
c_func
(paren
id|urb
(braket
id|j
)braket
op_member_access_from_pointer
id|transfer_buffer
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Decode frames received on the B/D channel.&n; * Note that this function will be called continously&n; * with 64Kbit/s / 16Kbit/s of data and hence it will be &n; * called 50 times per second with 20 ISOC descriptors. &n; * Called at interrupt.&n; */
DECL|function|usb_in_complete
r_static
r_void
id|usb_in_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|st5481_in
op_star
id|in
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|len
comma
id|count
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;status
op_ne
op_minus
id|ENOENT
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;urb status %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;urb killed&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
singleline_comment|// Give up
)brace
)brace
id|DBG_ISO_PACKET
c_func
(paren
l_int|0x80
comma
id|urb
)paren
suffix:semicolon
id|len
op_assign
id|st5481_isoc_flatten
c_func
(paren
id|urb
)paren
suffix:semicolon
id|ptr
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|in-&gt;mode
op_eq
id|L1_MODE_TRANS
)paren
(brace
id|memcpy
c_func
(paren
id|in-&gt;rcvbuf
comma
id|ptr
comma
id|len
)paren
suffix:semicolon
id|status
op_assign
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|hdlc_decode
c_func
(paren
op_amp
id|in-&gt;hdlc_state
comma
id|ptr
comma
id|len
comma
op_amp
id|count
comma
id|in-&gt;rcvbuf
comma
id|in-&gt;bufsize
)paren
suffix:semicolon
id|ptr
op_add_assign
id|count
suffix:semicolon
id|len
op_sub_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
OG
l_int|0
)paren
(brace
singleline_comment|// Good frame received
id|DBG
c_func
(paren
l_int|4
comma
l_string|&quot;count=%d&quot;
comma
id|status
)paren
suffix:semicolon
id|DBG_PACKET
c_func
(paren
l_int|0x400
comma
id|in-&gt;rcvbuf
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|status
)paren
)paren
)paren
(brace
id|WARN
c_func
(paren
l_string|&quot;receive out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|status
)paren
comma
id|in-&gt;rcvbuf
comma
id|status
)paren
suffix:semicolon
id|in-&gt;hisax_if
op_member_access_from_pointer
id|l1l2
c_func
(paren
id|in-&gt;hisax_if
comma
id|PH_DATA
op_or
id|INDICATION
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|HDLC_CRC_ERROR
)paren
(brace
id|INFO
c_func
(paren
l_string|&quot;CRC error&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|HDLC_FRAMING_ERROR
)paren
(brace
id|INFO
c_func
(paren
l_string|&quot;framing error&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_eq
op_minus
id|HDLC_LENGTH_ERROR
)paren
(brace
id|INFO
c_func
(paren
l_string|&quot;length error&quot;
)paren
suffix:semicolon
)brace
)brace
singleline_comment|// Prepare URB for next transfer
id|urb-&gt;dev
op_assign
id|in-&gt;adapter-&gt;usb_dev
suffix:semicolon
id|urb-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|urb
)paren
suffix:semicolon
)brace
DECL|function|st5481_setup_in
r_int
id|__devinit
id|st5481_setup_in
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|in-&gt;adapter-&gt;usb_dev
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|DBG
c_func
(paren
l_int|4
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|in-&gt;rcvbuf
op_assign
id|kmalloc
c_func
(paren
id|in-&gt;bufsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in-&gt;rcvbuf
)paren
r_goto
id|err
suffix:semicolon
id|retval
op_assign
id|st5481_setup_isocpipes
c_func
(paren
id|in-&gt;urb
comma
id|dev
comma
id|usb_rcvisocpipe
c_func
(paren
id|dev
comma
id|in-&gt;ep
)paren
comma
id|in-&gt;num_packets
comma
id|in-&gt;packet_size
comma
id|in-&gt;num_packets
op_star
id|in-&gt;packet_size
comma
id|usb_in_complete
comma
id|in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|err_free
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_free
suffix:colon
id|kfree
c_func
(paren
id|in-&gt;rcvbuf
)paren
suffix:semicolon
id|err
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|st5481_release_in
r_void
id|st5481_release_in
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
)paren
(brace
id|DBG
c_func
(paren
l_int|2
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|st5481_release_isocpipes
c_func
(paren
id|in-&gt;urb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make the transfer_buffer contiguous by&n; * copying from the iso descriptors if necessary. &n; */
DECL|function|st5481_isoc_flatten
r_int
id|st5481_isoc_flatten
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|iso_packet_descriptor_t
op_star
id|pipd
comma
op_star
id|pend
suffix:semicolon
r_int
r_char
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
OL
l_int|0
)paren
(brace
r_return
id|urb-&gt;status
suffix:semicolon
)brace
r_for
c_loop
(paren
id|pipd
op_assign
op_amp
id|urb-&gt;iso_frame_desc
(braket
l_int|0
)braket
comma
id|pend
op_assign
op_amp
id|urb-&gt;iso_frame_desc
(braket
id|urb-&gt;number_of_packets
)braket
comma
id|dst
op_assign
id|urb-&gt;transfer_buffer
suffix:semicolon
id|pipd
OL
id|pend
suffix:semicolon
id|pipd
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pipd-&gt;status
OL
l_int|0
)paren
(brace
r_return
(paren
id|pipd-&gt;status
)paren
suffix:semicolon
)brace
id|len
op_assign
id|pipd-&gt;actual_length
suffix:semicolon
id|pipd-&gt;actual_length
op_assign
l_int|0
suffix:semicolon
id|src
op_assign
id|urb-&gt;transfer_buffer
op_plus
id|pipd-&gt;offset
suffix:semicolon
r_if
c_cond
(paren
id|src
op_ne
id|dst
)paren
(brace
singleline_comment|// Need to copy since isoc buffers not full
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
op_star
id|dst
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
singleline_comment|// No need to copy, just update destination buffer
id|dst
op_add_assign
id|len
suffix:semicolon
)brace
)brace
singleline_comment|// Return size of flattened buffer
r_return
(paren
id|dst
op_minus
(paren
r_int
r_char
op_star
)paren
id|urb-&gt;transfer_buffer
)paren
suffix:semicolon
)brace
DECL|function|st5481_start_rcv
r_static
r_void
id|st5481_start_rcv
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|st5481_in
op_star
id|in
op_assign
id|context
suffix:semicolon
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|in-&gt;adapter
suffix:semicolon
id|DBG
c_func
(paren
l_int|4
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|in-&gt;urb
(braket
l_int|0
)braket
op_member_access_from_pointer
id|dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|in-&gt;urb
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|in-&gt;urb
(braket
l_int|1
)braket
op_member_access_from_pointer
id|dev
op_assign
id|adapter-&gt;usb_dev
suffix:semicolon
id|SUBMIT_URB
c_func
(paren
id|in-&gt;urb
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|st5481_in_mode
r_void
id|st5481_in_mode
c_func
(paren
r_struct
id|st5481_in
op_star
id|in
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|in-&gt;mode
op_eq
id|mode
)paren
r_return
suffix:semicolon
id|in-&gt;mode
op_assign
id|mode
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|in-&gt;urb
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|in-&gt;urb
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in-&gt;mode
op_ne
id|L1_MODE_NULL
)paren
(brace
r_if
c_cond
(paren
id|in-&gt;mode
op_ne
id|L1_MODE_TRANS
)paren
id|hdlc_rcv_init
c_func
(paren
op_amp
id|in-&gt;hdlc_state
comma
id|in-&gt;mode
op_eq
id|L1_MODE_HDLC_56K
)paren
suffix:semicolon
id|st5481_usb_pipe_reset
c_func
(paren
id|in-&gt;adapter
comma
id|in-&gt;ep
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|in-&gt;adapter
comma
id|in-&gt;counter
comma
id|in-&gt;packet_size
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|st5481_start_rcv
c_func
(paren
id|in
)paren
suffix:semicolon
)brace
r_else
(brace
id|st5481_usb_device_ctrl_msg
c_func
(paren
id|in-&gt;adapter
comma
id|in-&gt;counter
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
eof
