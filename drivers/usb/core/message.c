multiline_comment|/*&n; * message.c - synchronous message handling&n; */
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|struct|usb_api_data
r_struct
id|usb_api_data
(brace
DECL|member|wqh
id|wait_queue_head_t
id|wqh
suffix:semicolon
DECL|member|done
r_int
id|done
suffix:semicolon
)brace
suffix:semicolon
DECL|function|usb_api_blocking_completion
r_static
r_void
id|usb_api_blocking_completion
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_api_data
op_star
id|awd
op_assign
(paren
r_struct
id|usb_api_data
op_star
)paren
id|urb-&gt;context
suffix:semicolon
id|awd-&gt;done
op_assign
l_int|1
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|awd-&gt;wqh
)paren
suffix:semicolon
)brace
singleline_comment|// Starts urb and waits for completion or timeout
DECL|function|usb_start_wait_urb
r_static
r_int
id|usb_start_wait_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_int
id|timeout
comma
r_int
op_star
id|actual_length
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|usb_api_data
id|awd
suffix:semicolon
r_int
id|status
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|awd.wqh
)paren
suffix:semicolon
id|awd.done
op_assign
l_int|0
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|awd.wqh
comma
op_amp
id|wait
)paren
suffix:semicolon
id|urb-&gt;context
op_assign
op_amp
id|awd
suffix:semicolon
id|status
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
singleline_comment|// something went wrong
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|awd.wqh
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_while
c_loop
(paren
id|timeout
op_logical_and
op_logical_neg
id|awd.done
)paren
(brace
id|timeout
op_assign
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|awd.wqh
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timeout
op_logical_and
op_logical_neg
id|awd.done
)paren
(brace
r_if
c_cond
(paren
id|urb-&gt;status
op_ne
op_minus
id|EINPROGRESS
)paren
(brace
multiline_comment|/* No callback?!! */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;usb: raced timeout, &quot;
l_string|&quot;pipe 0x%x status %d time left %d&bslash;n&quot;
comma
id|urb-&gt;pipe
comma
id|urb-&gt;status
comma
id|timeout
)paren
suffix:semicolon
id|status
op_assign
id|urb-&gt;status
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;usb_control/bulk_msg: timeout&bslash;n&quot;
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
singleline_comment|// remove urb safely
id|status
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
)brace
r_else
id|status
op_assign
id|urb-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|actual_length
)paren
op_star
id|actual_length
op_assign
id|urb-&gt;actual_length
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|urb
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------*/
singleline_comment|// returns status (negative) or length (positive)
DECL|function|usb_internal_control_msg
r_int
id|usb_internal_control_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
r_struct
id|usb_ctrlrequest
op_star
id|cmd
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_int
id|timeout
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_int
id|retv
suffix:semicolon
r_int
id|length
suffix:semicolon
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|FILL_CONTROL_URB
c_func
(paren
id|urb
comma
id|usb_dev
comma
id|pipe
comma
(paren
r_int
r_char
op_star
)paren
id|cmd
comma
id|data
comma
id|len
comma
id|usb_api_blocking_completion
comma
l_int|0
)paren
suffix:semicolon
id|retv
op_assign
id|usb_start_wait_urb
c_func
(paren
id|urb
comma
id|timeout
comma
op_amp
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retv
OL
l_int|0
)paren
r_return
id|retv
suffix:semicolon
r_else
r_return
id|length
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;usb_control_msg - Builds a control urb, sends it off and waits for completion&n; *&t;@dev: pointer to the usb device to send the message to&n; *&t;@pipe: endpoint &quot;pipe&quot; to send the message to&n; *&t;@request: USB message request value&n; *&t;@requesttype: USB message request type value&n; *&t;@value: USB message value&n; *&t;@index: USB message index value&n; *&t;@data: pointer to the data to send&n; *&t;@size: length in bytes of the data to send&n; *&t;@timeout: time in jiffies to wait for the message to complete before&n; *&t;&t;timing out (if 0 the wait is forever)&n; *&t;Context: !in_interrupt ()&n; *&n; *&t;This function sends a simple control message to a specified endpoint&n; *&t;and waits for the message to complete, or timeout.&n; *&t;&n; *&t;If successful, it returns the number of bytes transferred, otherwise a negative error number.&n; *&n; *&t;Don&squot;t use this function from within an interrupt context, like a&n; *&t;bottom half handler.  If you need an asynchronous message, or need to send&n; *&t;a message from within interrupt context, use usb_submit_urb()&n; */
DECL|function|usb_control_msg
r_int
id|usb_control_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
id|__u8
id|request
comma
id|__u8
id|requesttype
comma
id|__u16
id|value
comma
id|__u16
id|index
comma
r_void
op_star
id|data
comma
id|__u16
id|size
comma
r_int
id|timeout
)paren
(brace
r_struct
id|usb_ctrlrequest
op_star
id|dr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_ctrlrequest
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dr-&gt;bRequestType
op_assign
id|requesttype
suffix:semicolon
id|dr-&gt;bRequest
op_assign
id|request
suffix:semicolon
id|dr-&gt;wValue
op_assign
id|cpu_to_le16p
c_func
(paren
op_amp
id|value
)paren
suffix:semicolon
id|dr-&gt;wIndex
op_assign
id|cpu_to_le16p
c_func
(paren
op_amp
id|index
)paren
suffix:semicolon
id|dr-&gt;wLength
op_assign
id|cpu_to_le16p
c_func
(paren
op_amp
id|size
)paren
suffix:semicolon
singleline_comment|//dbg(&quot;usb_control_msg&quot;);&t;
id|ret
op_assign
id|usb_internal_control_msg
c_func
(paren
id|dev
comma
id|pipe
comma
id|dr
comma
id|data
comma
id|size
comma
id|timeout
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;usb_bulk_msg - Builds a bulk urb, sends it off and waits for completion&n; *&t;@usb_dev: pointer to the usb device to send the message to&n; *&t;@pipe: endpoint &quot;pipe&quot; to send the message to&n; *&t;@data: pointer to the data to send&n; *&t;@len: length in bytes of the data to send&n; *&t;@actual_length: pointer to a location to put the actual length transferred in bytes&n; *&t;@timeout: time in jiffies to wait for the message to complete before&n; *&t;&t;timing out (if 0 the wait is forever)&n; *&t;Context: !in_interrupt ()&n; *&n; *&t;This function sends a simple bulk message to a specified endpoint&n; *&t;and waits for the message to complete, or timeout.&n; *&t;&n; *&t;If successful, it returns 0, otherwise a negative error number.&n; *&t;The number of actual bytes transferred will be stored in the &n; *&t;actual_length paramater.&n; *&n; *&t;Don&squot;t use this function from within an interrupt context, like a&n; *&t;bottom half handler.  If you need an asynchronous message, or need to&n; *&t;send a message from within interrupt context, use usb_submit_urb()&n; */
DECL|function|usb_bulk_msg
r_int
id|usb_bulk_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_int
op_star
id|actual_length
comma
r_int
id|timeout
)paren
(brace
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|FILL_BULK_URB
c_func
(paren
id|urb
comma
id|usb_dev
comma
id|pipe
comma
id|data
comma
id|len
comma
id|usb_api_blocking_completion
comma
l_int|0
)paren
suffix:semicolon
r_return
id|usb_start_wait_urb
c_func
(paren
id|urb
comma
id|timeout
comma
id|actual_length
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_get_descriptor - issues a generic GET_DESCRIPTOR request&n; * @dev: the device whose descriptor is being retrieved&n; * @type: the descriptor type (USB_DT_*)&n; * @index: the number of the descriptor&n; * @buf: where to put the descriptor&n; * @size: how big is &quot;buf&quot;?&n; * Context: !in_interrupt ()&n; *&n; * Gets a USB descriptor.  Convenience functions exist to simplify&n; * getting some types of descriptors.  Use&n; * usb_get_device_descriptor() for USB_DT_DEVICE,&n; * and usb_get_string() or usb_string() for USB_DT_STRING.&n; * Configuration descriptors (USB_DT_CONFIG) are part of the device&n; * structure, at least for the current configuration.&n; * In addition to a number of USB-standard descriptors, some&n; * devices also use class-specific or vendor-specific descriptors.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns the number of bytes received on success, or else the status code&n; * returned by the underlying usb_control_msg() call.&n; */
DECL|function|usb_get_descriptor
r_int
id|usb_get_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_char
id|type
comma
r_int
r_char
id|index
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_int
id|i
op_assign
l_int|5
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
singleline_comment|// Make sure we parse really received data
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
multiline_comment|/* retries if the returned length was 0; flakey device */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_DESCRIPTOR
comma
id|USB_DIR_IN
comma
(paren
id|type
op_lshift
l_int|8
)paren
op_plus
id|index
comma
l_int|0
comma
id|buf
comma
id|size
comma
id|HZ
op_star
id|USB_CTRL_GET_TIMEOUT
)paren
)paren
OG
l_int|0
op_logical_or
id|result
op_eq
op_minus
id|EPIPE
)paren
r_break
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_get_string - gets a string descriptor&n; * @dev: the device whose string descriptor is being retrieved&n; * @langid: code for language chosen (from string descriptor zero)&n; * @index: the number of the descriptor&n; * @buf: where to put the string&n; * @size: how big is &quot;buf&quot;?&n; * Context: !in_interrupt ()&n; *&n; * Retrieves a string, encoded using UTF-16LE (Unicode, 16 bits per character,&n; * in little-endian byte order).&n; * The usb_string() function will often be a convenient way to turn&n; * these strings into kernel-printable form.&n; *&n; * Strings may be referenced in device, configuration, interface, or other&n; * descriptors, and could also be used in vendor-specific ways.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns the number of bytes received on success, or else the status code&n; * returned by the underlying usb_control_msg() call.&n; */
DECL|function|usb_get_string
r_int
id|usb_get_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|langid
comma
r_int
r_char
id|index
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_DESCRIPTOR
comma
id|USB_DIR_IN
comma
(paren
id|USB_DT_STRING
op_lshift
l_int|8
)paren
op_plus
id|index
comma
id|langid
comma
id|buf
comma
id|size
comma
id|HZ
op_star
id|USB_CTRL_GET_TIMEOUT
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_get_device_descriptor - (re)reads the device descriptor&n; * @dev: the device whose device descriptor is being updated&n; * Context: !in_interrupt ()&n; *&n; * Updates the copy of the device descriptor stored in the device structure,&n; * which dedicates space for this purpose.  Note that several fields are&n; * converted to the host CPU&squot;s byte order:  the USB version (bcdUSB), and&n; * vendors product and version fields (idVendor, idProduct, and bcdDevice).&n; * That lets device drivers compare against non-byteswapped constants.&n; *&n; * There&squot;s normally no need to use this call, although some devices&n; * will change their descriptors after events like updating firmware.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns the number of bytes received on success, or else the status code&n; * returned by the underlying usb_control_msg() call.&n; */
DECL|function|usb_get_device_descriptor
r_int
id|usb_get_device_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|ret
op_assign
id|usb_get_descriptor
c_func
(paren
id|dev
comma
id|USB_DT_DEVICE
comma
l_int|0
comma
op_amp
id|dev-&gt;descriptor
comma
r_sizeof
(paren
id|dev-&gt;descriptor
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
(brace
id|le16_to_cpus
c_func
(paren
op_amp
id|dev-&gt;descriptor.bcdUSB
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|dev-&gt;descriptor.idVendor
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|dev-&gt;descriptor.idProduct
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|dev-&gt;descriptor.bcdDevice
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_get_status - issues a GET_STATUS call&n; * @dev: the device whose status is being checked&n; * @type: USB_RECIP_*; for device, interface, or endpoint&n; * @target: zero (for device), else interface or endpoint number&n; * @data: pointer to two bytes of bitmap data&n; * Context: !in_interrupt ()&n; *&n; * Returns device, interface, or endpoint status.  Normally only of&n; * interest to see if the device is self powered, or has enabled the&n; * remote wakeup facility; or whether a bulk or interrupt endpoint&n; * is halted (&quot;stalled&quot;).&n; *&n; * Bits in these status bitmaps are set using the SET_FEATURE request,&n; * and cleared using the CLEAR_FEATURE request.  The usb_clear_halt()&n; * function should be used to clear halt (&quot;stall&quot;) status.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns the number of bytes received on success, or else the status code&n; * returned by the underlying usb_control_msg() call.&n; */
DECL|function|usb_get_status
r_int
id|usb_get_status
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|type
comma
r_int
id|target
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_STATUS
comma
id|USB_DIR_IN
op_or
id|type
comma
l_int|0
comma
id|target
comma
id|data
comma
l_int|2
comma
id|HZ
op_star
id|USB_CTRL_GET_TIMEOUT
)paren
suffix:semicolon
)brace
singleline_comment|// hub-only!! ... and only exported for reset/reinit path.
singleline_comment|// otherwise used internally, for config/altsetting reconfig.
DECL|function|usb_set_maxpacket
r_void
id|usb_set_maxpacket
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|i
comma
id|b
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
id|dev-&gt;actconfig-&gt;bNumInterfaces
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|usb_interface
op_star
id|ifp
op_assign
id|dev-&gt;actconfig-&gt;interface
op_plus
id|i
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|as
op_assign
id|ifp-&gt;altsetting
op_plus
id|ifp-&gt;act_altsetting
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|ep
op_assign
id|as-&gt;endpoint
suffix:semicolon
r_int
id|e
suffix:semicolon
r_for
c_loop
(paren
id|e
op_assign
l_int|0
suffix:semicolon
id|e
OL
id|as-&gt;bNumEndpoints
suffix:semicolon
id|e
op_increment
)paren
(brace
id|b
op_assign
id|ep
(braket
id|e
)braket
dot
id|bEndpointAddress
op_amp
id|USB_ENDPOINT_NUMBER_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ep
(braket
id|e
)braket
dot
id|bmAttributes
op_amp
id|USB_ENDPOINT_XFERTYPE_MASK
)paren
op_eq
id|USB_ENDPOINT_XFER_CONTROL
)paren
(brace
multiline_comment|/* Control =&gt; bidirectional */
id|dev-&gt;epmaxpacketout
(braket
id|b
)braket
op_assign
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
suffix:semicolon
id|dev-&gt;epmaxpacketin
(braket
id|b
)braket
op_assign
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|usb_endpoint_out
c_func
(paren
id|ep
(braket
id|e
)braket
dot
id|bEndpointAddress
)paren
)paren
(brace
r_if
c_cond
(paren
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
OG
id|dev-&gt;epmaxpacketout
(braket
id|b
)braket
)paren
id|dev-&gt;epmaxpacketout
(braket
id|b
)braket
op_assign
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
OG
id|dev-&gt;epmaxpacketin
(braket
id|b
)braket
)paren
id|dev-&gt;epmaxpacketin
(braket
id|b
)braket
op_assign
id|ep
(braket
id|e
)braket
dot
id|wMaxPacketSize
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/**&n; * usb_clear_halt - tells device to clear endpoint halt/stall condition&n; * @dev: device whose endpoint is halted&n; * @pipe: endpoint &quot;pipe&quot; being cleared&n; * Context: !in_interrupt ()&n; *&n; * This is used to clear halt conditions for bulk and interrupt endpoints,&n; * as reported by URB completion status.  Endpoints that are halted are&n; * sometimes referred to as being &quot;stalled&quot;.  Such endpoints are unable&n; * to transmit or receive data until the halt status is cleared.  Any URBs&n; * queued queued for such an endpoint should normally be unlinked before&n; * clearing the halt condition.&n; *&n; * Note that control and isochronous endpoints don&squot;t halt, although control&n; * endpoints report &quot;protocol stall&quot; (for unsupported requests) using the&n; * same status code used to report a true stall.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns zero on success, or else the status code returned by the&n; * underlying usb_control_msg() call.&n; */
DECL|function|usb_clear_halt
r_int
id|usb_clear_halt
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|pipe
)paren
(brace
r_int
id|result
suffix:semicolon
id|__u16
id|status
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|endp
op_assign
id|usb_pipeendpoint
c_func
(paren
id|pipe
)paren
op_or
(paren
id|usb_pipein
c_func
(paren
id|pipe
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/*&n;&t;if (!usb_endpoint_halted(dev, endp &amp; 0x0f, usb_endpoint_out(endp)))&n;&t;&t;return 0;&n;*/
id|result
op_assign
id|usb_control_msg
c_func
(paren
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
id|USB_REQ_CLEAR_FEATURE
comma
id|USB_RECIP_ENDPOINT
comma
l_int|0
comma
id|endp
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
suffix:semicolon
multiline_comment|/* don&squot;t clear if failed */
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|status
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|err
c_func
(paren
l_string|&quot;unable to allocate memory for configuration descriptors&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_STATUS
comma
id|USB_DIR_IN
op_or
id|USB_RECIP_ENDPOINT
comma
l_int|0
comma
id|endp
comma
singleline_comment|// FIXME USB_CTRL_GET_TIMEOUT, yes?  why not usb_get_status() ?
id|buffer
comma
r_sizeof
(paren
id|status
)paren
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|status
comma
id|buffer
comma
r_sizeof
(paren
id|status
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|status
)paren
op_amp
l_int|1
)paren
r_return
op_minus
id|EPIPE
suffix:semicolon
multiline_comment|/* still halted */
id|usb_endpoint_running
c_func
(paren
id|dev
comma
id|usb_pipeendpoint
c_func
(paren
id|pipe
)paren
comma
id|usb_pipeout
c_func
(paren
id|pipe
)paren
)paren
suffix:semicolon
multiline_comment|/* toggle is reset on clear */
id|usb_settoggle
c_func
(paren
id|dev
comma
id|usb_pipeendpoint
c_func
(paren
id|pipe
)paren
comma
id|usb_pipeout
c_func
(paren
id|pipe
)paren
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_set_interface - Makes a particular alternate setting be current&n; * @dev: the device whose interface is being updated&n; * @interface: the interface being updated&n; * @alternate: the setting being chosen.&n; * Context: !in_interrupt ()&n; *&n; * This is used to enable data transfers on interfaces that may not&n; * be enabled by default.  Not all devices support such configurability.&n; *&n; * Within any given configuration, each interface may have several&n; * alternative settings.  These are often used to control levels of&n; * bandwidth consumption.  For example, the default setting for a high&n; * speed interrupt endpoint may not send more than about 4KBytes per&n; * microframe, and isochronous endpoints may never be part of a an&n; * interface&squot;s default setting.  To access such bandwidth, alternate&n; * interface setting must be made current.&n; *&n; * Note that in the Linux USB subsystem, bandwidth associated with&n; * an endpoint in a given alternate setting is not reserved until an&n; * is submitted that needs that bandwidth.  Some other operating systems&n; * allocate bandwidth early, when a configuration is chosen.&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns zero on success, or else the status code returned by the&n; * underlying usb_control_msg() call.&n; */
DECL|function|usb_set_interface
r_int
id|usb_set_interface
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|interface
comma
r_int
id|alternate
)paren
(brace
r_struct
id|usb_interface
op_star
id|iface
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|iface_as
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
id|iface
op_assign
id|usb_ifnum_to_if
c_func
(paren
id|dev
comma
id|interface
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iface
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;selecting invalid interface %d&quot;
comma
id|interface
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* 9.4.10 says devices don&squot;t need this, if the interface&n;&t;   only has one alternate setting */
r_if
c_cond
(paren
id|iface-&gt;num_altsetting
op_eq
l_int|1
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;ignoring set_interface for dev %d, iface %d, alt %d&quot;
comma
id|dev-&gt;devnum
comma
id|interface
comma
id|alternate
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|usb_control_msg
c_func
(paren
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
id|USB_REQ_SET_INTERFACE
comma
id|USB_RECIP_INTERFACE
comma
id|alternate
comma
id|interface
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
l_int|5
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|iface-&gt;act_altsetting
op_assign
id|alternate
suffix:semicolon
multiline_comment|/* 9.1.1.5: reset toggles for all endpoints affected by this iface-as&n;&t; *&n;&t; * Note:&n;&t; * Despite EP0 is always present in all interfaces/AS, the list of&n;&t; * endpoints from the descriptor does not contain EP0. Due to its&n;&t; * omnipresence one might expect EP0 being considered &quot;affected&quot; by&n;&t; * any SetInterface request and hence assume toggles need to be reset.&n;&t; * However, EP0 toggles are re-synced for every individual transfer&n;&t; * during the SETUP stage - hence EP0 toggles are &quot;don&squot;t care&quot; here.&n;&t; */
id|iface_as
op_assign
op_amp
id|iface-&gt;altsetting
(braket
id|alternate
)braket
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
id|iface_as-&gt;bNumEndpoints
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u8
id|ep
op_assign
id|iface_as-&gt;endpoint
(braket
id|i
)braket
dot
id|bEndpointAddress
suffix:semicolon
id|usb_settoggle
c_func
(paren
id|dev
comma
id|ep
op_amp
id|USB_ENDPOINT_NUMBER_MASK
comma
id|usb_endpoint_out
c_func
(paren
id|ep
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* usb_set_maxpacket() sets the maxpacket size for all EP in all&n;&t; * interfaces but it shouldn&squot;t do any harm here: we have changed&n;&t; * the AS for the requested interface only, hence for unaffected&n;&t; * interfaces it&squot;s just re-application of still-valid values.&n;&t; */
id|usb_set_maxpacket
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_set_configuration - Makes a particular device setting be current&n; * @dev: the device whose configuration is being updated&n; * @configuration: the configuration being chosen.&n; * Context: !in_interrupt ()&n; *&n; * This is used to enable non-default device modes.  Not all devices&n; * support this kind of configurability.  By default, configuration&n; * zero is selected after enumeration; many devices only have a single&n; * configuration.&n; *&n; * USB devices may support one or more configurations, which affect&n; * power consumption and the functionality available.  For example,&n; * the default configuration is limited to using 100mA of bus power,&n; * so that when certain device functionality requires more power,&n; * and the device is bus powered, that functionality will be in some&n; * non-default device configuration.  Other device modes may also be&n; * reflected as configuration options, such as whether two ISDN&n; * channels are presented as independent 64Kb/s interfaces or as one&n; * bonded 128Kb/s interface.&n; *&n; * Note that USB has an additional level of device configurability,&n; * associated with interfaces.  That configurability is accessed using&n; * usb_set_interface().&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns zero on success, or else the status code returned by the&n; * underlying usb_control_msg() call.&n; */
DECL|function|usb_set_configuration
r_int
id|usb_set_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|configuration
)paren
(brace
r_int
id|i
comma
id|ret
suffix:semicolon
r_struct
id|usb_config_descriptor
op_star
id|cp
op_assign
l_int|NULL
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
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;config
(braket
id|i
)braket
dot
id|bConfigurationValue
op_eq
id|configuration
)paren
(brace
id|cp
op_assign
op_amp
id|dev-&gt;config
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|cp
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;selecting invalid configuration %d&quot;
comma
id|configuration
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|usb_control_msg
c_func
(paren
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
id|USB_REQ_SET_CONFIGURATION
comma
l_int|0
comma
id|configuration
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
op_star
id|USB_CTRL_SET_TIMEOUT
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|dev-&gt;actconfig
op_assign
id|cp
suffix:semicolon
id|dev-&gt;toggle
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;toggle
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|usb_set_maxpacket
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_string - returns ISO 8859-1 version of a string descriptor&n; * @dev: the device whose string descriptor is being retrieved&n; * @index: the number of the descriptor&n; * @buf: where to put the string&n; * @size: how big is &quot;buf&quot;?&n; * Context: !in_interrupt ()&n; * &n; * This converts the UTF-16LE encoded strings returned by devices, from&n; * usb_get_string_descriptor(), to null-terminated ISO-8859-1 encoded ones&n; * that are more usable in most kernel contexts.  Note that all characters&n; * in the chosen descriptor that can&squot;t be encoded using ISO-8859-1&n; * are converted to the question mark (&quot;?&quot;) character, and this function&n; * chooses strings in the first language supported by the device.&n; *&n; * The ASCII (or, redundantly, &quot;US-ASCII&quot;) character set is the seven-bit&n; * subset of ISO 8859-1. ISO-8859-1 is the eight-bit subset of Unicode,&n; * and is appropriate for use many uses of English and several other&n; * Western European languages.  (But it doesn&squot;t include the &quot;Euro&quot; symbol.)&n; *&n; * This call is synchronous, and may not be used in an interrupt context.&n; *&n; * Returns length of the string (&gt;= 0) or usb_control_msg status (&lt; 0).&n; */
DECL|function|usb_string
r_int
id|usb_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_int
r_char
op_star
id|tbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|u
comma
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
l_int|0
op_logical_or
op_logical_neg
id|buf
op_logical_or
op_logical_neg
id|index
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|tbuf
op_assign
id|kmalloc
c_func
(paren
l_int|256
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tbuf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* get langid for strings if it&squot;s not yet known */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;have_langid
)paren
(brace
id|err
op_assign
id|usb_get_string
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|0
comma
id|tbuf
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;error getting string descriptor 0 (error=%d)&quot;
comma
id|err
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tbuf
(braket
l_int|0
)braket
OL
l_int|4
)paren
(brace
id|err
c_func
(paren
l_string|&quot;string descriptor 0 too short&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;have_langid
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;string_langid
op_assign
id|tbuf
(braket
l_int|2
)braket
op_or
(paren
id|tbuf
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* always use the first langid listed */
id|dbg
c_func
(paren
l_string|&quot;USB device number %d default language ID 0x%x&quot;
comma
id|dev-&gt;devnum
comma
id|dev-&gt;string_langid
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Just ask for a maximum length string and then take the length&n;&t; * that was returned.&n;&t; */
id|err
op_assign
id|usb_get_string
c_func
(paren
id|dev
comma
id|dev-&gt;string_langid
comma
id|index
comma
id|tbuf
comma
l_int|255
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
id|size
op_decrement
suffix:semicolon
multiline_comment|/* leave room for trailing NULL char in output buffer */
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
comma
id|u
op_assign
l_int|2
suffix:semicolon
id|u
OL
id|err
suffix:semicolon
id|u
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|size
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tbuf
(braket
id|u
op_plus
l_int|1
)braket
)paren
multiline_comment|/* high byte */
id|buf
(braket
id|idx
op_increment
)braket
op_assign
l_char|&squot;?&squot;
suffix:semicolon
multiline_comment|/* non ISO-8859-1 character */
r_else
id|buf
(braket
id|idx
op_increment
)braket
op_assign
id|tbuf
(braket
id|u
)braket
suffix:semicolon
)brace
id|buf
(braket
id|idx
)braket
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|idx
suffix:semicolon
id|errout
suffix:colon
id|kfree
c_func
(paren
id|tbuf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
singleline_comment|// synchronous request completion model
DECL|variable|usb_control_msg
id|EXPORT_SYMBOL
c_func
(paren
id|usb_control_msg
)paren
suffix:semicolon
DECL|variable|usb_bulk_msg
id|EXPORT_SYMBOL
c_func
(paren
id|usb_bulk_msg
)paren
suffix:semicolon
singleline_comment|// synchronous control message convenience routines
DECL|variable|usb_get_descriptor
id|EXPORT_SYMBOL
c_func
(paren
id|usb_get_descriptor
)paren
suffix:semicolon
DECL|variable|usb_get_device_descriptor
id|EXPORT_SYMBOL
c_func
(paren
id|usb_get_device_descriptor
)paren
suffix:semicolon
DECL|variable|usb_get_status
id|EXPORT_SYMBOL
c_func
(paren
id|usb_get_status
)paren
suffix:semicolon
DECL|variable|usb_get_string
id|EXPORT_SYMBOL
c_func
(paren
id|usb_get_string
)paren
suffix:semicolon
DECL|variable|usb_string
id|EXPORT_SYMBOL
c_func
(paren
id|usb_string
)paren
suffix:semicolon
DECL|variable|usb_clear_halt
id|EXPORT_SYMBOL
c_func
(paren
id|usb_clear_halt
)paren
suffix:semicolon
DECL|variable|usb_set_configuration
id|EXPORT_SYMBOL
c_func
(paren
id|usb_set_configuration
)paren
suffix:semicolon
DECL|variable|usb_set_interface
id|EXPORT_SYMBOL
c_func
(paren
id|usb_set_interface
)paren
suffix:semicolon
eof
