multiline_comment|/*&n; * A driver for the Griffin Technology, Inc. &quot;PowerMate&quot; USB controller dial.&n; *&n; * v1.0, (c)2002 William R Sowerbutts &lt;will@sowerbutts.com&gt;&n; *&n; * This device is a stainless steel knob which connects over USB. It can measure&n; * clockwise and anticlockwise rotation. The dial also acts as a pushbutton with&n; * a spring for automatic release. The base contains a pair of LEDs which illuminate&n; * the translucent base. It rotates without limit and reports its relative rotation&n; * back to the host when polled by the USB controller.&n; *&n; * Testing with the knob I have has shown that it measures approximately 94 &quot;clicks&quot;&n; * for one full rotation. Testing with my High Speed Rotation Actuator (ok, it was &n; * a variable speed cordless electric drill) has shown that the device can measure&n; * speeds of up to 7 clicks either clockwise or anticlockwise between pollings from&n; * the host. If it counts more than 7 clicks before it is polled, it will wrap back&n; * to zero and start counting again. This was at quite high speed, however, almost&n; * certainly faster than the human hand could turn it.&n; *&n; * The device&squot;s microcontroller can be programmed to set the LED to either a constant&n; * intensity, or to a rhythmic pulsing. Several patterns and speeds are available.&n; *&n; * Griffin were very happy to provide documentation and free hardware for development.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|POWERMATE_VENDOR
mdefine_line|#define POWERMATE_VENDOR&t;0x077d&t;/* Griffin Technology, Inc. */
DECL|macro|POWERMATE_PRODUCT_NEW
mdefine_line|#define POWERMATE_PRODUCT_NEW&t;0x0410&t;/* Griffin PowerMate */
DECL|macro|POWERMATE_PRODUCT_OLD
mdefine_line|#define POWERMATE_PRODUCT_OLD&t;0x04AA&t;/* Griffin soundKnob */
DECL|macro|CONTOUR_VENDOR
mdefine_line|#define CONTOUR_VENDOR&t;&t;0x05f3&t;/* Contour Design, Inc. */
DECL|macro|CONTOUR_JOG
mdefine_line|#define CONTOUR_JOG&t;&t;0x0240&t;/* Jog and Shuttle */
multiline_comment|/* these are the command codes we send to the device */
DECL|macro|SET_STATIC_BRIGHTNESS
mdefine_line|#define SET_STATIC_BRIGHTNESS  0x01
DECL|macro|SET_PULSE_ASLEEP
mdefine_line|#define SET_PULSE_ASLEEP       0x02
DECL|macro|SET_PULSE_AWAKE
mdefine_line|#define SET_PULSE_AWAKE        0x03
DECL|macro|SET_PULSE_MODE
mdefine_line|#define SET_PULSE_MODE         0x04
multiline_comment|/* these refer to bits in the powermate_device&squot;s requires_update field. */
DECL|macro|UPDATE_STATIC_BRIGHTNESS
mdefine_line|#define UPDATE_STATIC_BRIGHTNESS (1&lt;&lt;0)
DECL|macro|UPDATE_PULSE_ASLEEP
mdefine_line|#define UPDATE_PULSE_ASLEEP      (1&lt;&lt;1)
DECL|macro|UPDATE_PULSE_AWAKE
mdefine_line|#define UPDATE_PULSE_AWAKE       (1&lt;&lt;2)
DECL|macro|UPDATE_PULSE_MODE
mdefine_line|#define UPDATE_PULSE_MODE        (1&lt;&lt;3)
DECL|macro|POWERMATE_PAYLOAD_SIZE
mdefine_line|#define POWERMATE_PAYLOAD_SIZE 3
DECL|struct|powermate_device
r_struct
id|powermate_device
(brace
DECL|member|data
r_int
r_char
id|data
(braket
id|POWERMATE_PAYLOAD_SIZE
)braket
suffix:semicolon
DECL|member|irq
DECL|member|config
r_struct
id|urb
id|irq
comma
id|config
suffix:semicolon
DECL|member|configcr
r_struct
id|usb_ctrlrequest
id|configcr
suffix:semicolon
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|input
r_struct
id|input_dev
id|input
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|static_brightness
r_int
id|static_brightness
suffix:semicolon
DECL|member|pulse_speed
r_int
id|pulse_speed
suffix:semicolon
DECL|member|pulse_table
r_int
id|pulse_table
suffix:semicolon
DECL|member|pulse_asleep
r_int
id|pulse_asleep
suffix:semicolon
DECL|member|pulse_awake
r_int
id|pulse_awake
suffix:semicolon
DECL|member|requires_update
r_int
id|requires_update
suffix:semicolon
singleline_comment|// physical settings which are out of sync
DECL|member|phys
r_char
id|phys
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|pm_name_powermate
r_static
r_char
id|pm_name_powermate
(braket
)braket
op_assign
l_string|&quot;Griffin PowerMate&quot;
suffix:semicolon
DECL|variable|pm_name_soundknob
r_static
r_char
id|pm_name_soundknob
(braket
)braket
op_assign
l_string|&quot;Griffin SoundKnob&quot;
suffix:semicolon
r_static
r_void
id|powermate_config_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* forward declararation of callback */
multiline_comment|/* Callback for data arriving from the PowerMate over the USB interrupt pipe */
DECL|function|powermate_irq
r_static
r_void
id|powermate_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|powermate_device
op_star
id|pm
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* handle updates to device state */
id|input_report_key
c_func
(paren
op_amp
id|pm-&gt;input
comma
id|BTN_0
comma
id|pm-&gt;data
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
op_amp
id|pm-&gt;input
comma
id|REL_DIAL
comma
id|pm-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Decide if we need to issue a control message and do so. Must be called with pm-&gt;lock down */
DECL|function|powermate_sync_state
r_static
r_void
id|powermate_sync_state
c_func
(paren
r_struct
id|powermate_device
op_star
id|pm
)paren
(brace
r_if
c_cond
(paren
id|pm-&gt;requires_update
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* no updates are required */
r_if
c_cond
(paren
id|pm-&gt;config.status
op_eq
op_minus
id|EINPROGRESS
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* an update is already in progress; it&squot;ll issue this update when it completes */
r_if
c_cond
(paren
id|pm-&gt;requires_update
op_amp
id|UPDATE_STATIC_BRIGHTNESS
)paren
(brace
id|pm-&gt;configcr.wValue
op_assign
id|cpu_to_le16
c_func
(paren
id|SET_STATIC_BRIGHTNESS
)paren
suffix:semicolon
id|pm-&gt;configcr.wIndex
op_assign
id|cpu_to_le16
c_func
(paren
id|pm-&gt;static_brightness
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_and_assign
op_complement
id|UPDATE_STATIC_BRIGHTNESS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pm-&gt;requires_update
op_amp
id|UPDATE_PULSE_ASLEEP
)paren
(brace
id|pm-&gt;configcr.wValue
op_assign
id|cpu_to_le16
c_func
(paren
id|SET_PULSE_ASLEEP
)paren
suffix:semicolon
id|pm-&gt;configcr.wIndex
op_assign
id|cpu_to_le16
c_func
(paren
id|pm-&gt;pulse_asleep
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_and_assign
op_complement
id|UPDATE_PULSE_ASLEEP
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pm-&gt;requires_update
op_amp
id|UPDATE_PULSE_AWAKE
)paren
(brace
id|pm-&gt;configcr.wValue
op_assign
id|cpu_to_le16
c_func
(paren
id|SET_PULSE_AWAKE
)paren
suffix:semicolon
id|pm-&gt;configcr.wIndex
op_assign
id|cpu_to_le16
c_func
(paren
id|pm-&gt;pulse_awake
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_and_assign
op_complement
id|UPDATE_PULSE_AWAKE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pm-&gt;requires_update
op_amp
id|UPDATE_PULSE_MODE
)paren
(brace
r_int
id|op
comma
id|arg
suffix:semicolon
multiline_comment|/* the powermate takes an operation and an argument for its pulse algorithm.&n;&t;&t;   the operation can be:&n;&t;&t;   0: divide the speed&n;&t;&t;   1: pulse at normal speed&n;&t;&t;   2: multiply the speed&n;&t;&t;   the argument only has an effect for operations 0 and 2, and ranges between&n;&t;&t;   1 (least effect) to 255 (maximum effect).&n;       &n;&t;&t;   thus, several states are equivalent and are coalesced into one state.&n;&n;&t;&t;   we map this onto a range from 0 to 510, with:&n;&t;&t;   0 -- 254    -- use divide (0 = slowest)&n;&t;&t;   255         -- use normal speed&n;&t;&t;   256 -- 510  -- use multiple (510 = fastest).&n;&n;&t;&t;   Only values of &squot;arg&squot; quite close to 255 are particularly useful/spectacular.&n;&t;&t;*/
r_if
c_cond
(paren
id|pm-&gt;pulse_speed
OL
l_int|255
)paren
(brace
id|op
op_assign
l_int|0
suffix:semicolon
singleline_comment|// divide
id|arg
op_assign
l_int|255
op_minus
id|pm-&gt;pulse_speed
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pm-&gt;pulse_speed
OG
l_int|255
)paren
(brace
id|op
op_assign
l_int|2
suffix:semicolon
singleline_comment|// multiply
id|arg
op_assign
id|pm-&gt;pulse_speed
op_minus
l_int|255
suffix:semicolon
)brace
r_else
(brace
id|op
op_assign
l_int|1
suffix:semicolon
singleline_comment|// normal speed
id|arg
op_assign
l_int|0
suffix:semicolon
singleline_comment|// can be any value
)brace
id|pm-&gt;configcr.wValue
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|pm-&gt;pulse_table
op_lshift
l_int|8
)paren
op_or
id|SET_PULSE_MODE
)paren
suffix:semicolon
id|pm-&gt;configcr.wIndex
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|arg
op_lshift
l_int|8
)paren
op_or
id|op
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_and_assign
op_complement
id|UPDATE_PULSE_MODE
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;powermate: unknown update required&quot;
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fudge the bug */
r_return
suffix:semicolon
)brace
multiline_comment|/*&t;printk(&quot;powermate: %04x %04x&bslash;n&quot;, pm-&gt;configcr.wValue, pm-&gt;configcr.wIndex); */
id|pm-&gt;config.dev
op_assign
id|pm-&gt;udev
suffix:semicolon
multiline_comment|/* is this necessary? */
id|pm-&gt;configcr.bRequestType
op_assign
l_int|0x41
suffix:semicolon
multiline_comment|/* vendor request */
id|pm-&gt;configcr.bRequest
op_assign
l_int|0x01
suffix:semicolon
id|pm-&gt;configcr.wLength
op_assign
l_int|0
suffix:semicolon
id|FILL_CONTROL_URB
c_func
(paren
op_amp
id|pm-&gt;config
comma
id|pm-&gt;udev
comma
id|usb_sndctrlpipe
c_func
(paren
id|pm-&gt;udev
comma
l_int|0
)paren
comma
(paren
r_void
op_star
)paren
op_amp
id|pm-&gt;configcr
comma
l_int|0
comma
l_int|0
comma
id|powermate_config_complete
comma
id|pm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|pm-&gt;config
comma
id|GFP_ATOMIC
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;powermate: usb_submit_urb(config) failed&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Called when our asynchronous control message completes. We may need to issue another immediately */
DECL|function|powermate_config_complete
r_static
r_void
id|powermate_config_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|powermate_device
op_star
id|pm
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;powermate: config urb returned %d&bslash;n&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
id|powermate_sync_state
c_func
(paren
id|pm
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the LED up as described and begin the sync with the hardware if required */
DECL|function|powermate_pulse_led
r_static
r_void
id|powermate_pulse_led
c_func
(paren
r_struct
id|powermate_device
op_star
id|pm
comma
r_int
id|static_brightness
comma
r_int
id|pulse_speed
comma
r_int
id|pulse_table
comma
r_int
id|pulse_asleep
comma
r_int
id|pulse_awake
)paren
(brace
r_if
c_cond
(paren
id|pulse_speed
OL
l_int|0
)paren
(brace
id|pulse_speed
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_table
OL
l_int|0
)paren
(brace
id|pulse_table
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_speed
OG
l_int|510
)paren
(brace
id|pulse_speed
op_assign
l_int|510
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_table
OG
l_int|2
)paren
(brace
id|pulse_table
op_assign
l_int|2
suffix:semicolon
)brace
id|pulse_asleep
op_assign
op_logical_neg
op_logical_neg
id|pulse_asleep
suffix:semicolon
id|pulse_awake
op_assign
op_logical_neg
op_logical_neg
id|pulse_awake
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* mark state updates which are required */
r_if
c_cond
(paren
id|static_brightness
op_ne
id|pm-&gt;static_brightness
)paren
(brace
id|pm-&gt;static_brightness
op_assign
id|static_brightness
suffix:semicolon
id|pm-&gt;requires_update
op_or_assign
id|UPDATE_STATIC_BRIGHTNESS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_asleep
op_ne
id|pm-&gt;pulse_asleep
)paren
(brace
id|pm-&gt;pulse_asleep
op_assign
id|pulse_asleep
suffix:semicolon
id|pm-&gt;requires_update
op_or_assign
id|UPDATE_PULSE_ASLEEP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_awake
op_ne
id|pm-&gt;pulse_awake
)paren
(brace
id|pm-&gt;pulse_awake
op_assign
id|pulse_awake
suffix:semicolon
id|pm-&gt;requires_update
op_or_assign
id|UPDATE_PULSE_AWAKE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pulse_speed
op_ne
id|pm-&gt;pulse_speed
op_logical_or
id|pulse_table
op_ne
id|pm-&gt;pulse_table
)paren
(brace
id|pm-&gt;pulse_speed
op_assign
id|pulse_speed
suffix:semicolon
id|pm-&gt;pulse_table
op_assign
id|pulse_table
suffix:semicolon
id|pm-&gt;requires_update
op_or_assign
id|UPDATE_PULSE_MODE
suffix:semicolon
)brace
id|powermate_sync_state
c_func
(paren
id|pm
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Callback from the Input layer when an event arrives from userspace to configure the LED */
DECL|function|powermate_input_event
r_static
r_int
id|powermate_input_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|_value
)paren
(brace
r_int
r_int
id|command
op_assign
(paren
r_int
r_int
)paren
id|_value
suffix:semicolon
r_struct
id|powermate_device
op_star
id|pm
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|EV_MSC
op_logical_and
id|code
op_eq
id|MSC_PULSELED
)paren
(brace
multiline_comment|/*  &n;&t;&t;    bits  0- 7: 8 bits: LED brightness&n;&t;&t;    bits  8-16: 9 bits: pulsing speed modifier (0 ... 510); 0-254 = slower, 255 = standard, 256-510 = faster.&n;&t;&t;    bits 17-18: 2 bits: pulse table (0, 1, 2 valid)&n;&t;&t;    bit     19: 1 bit : pulse whilst asleep?&n;&t;&t;    bit     20: 1 bit : pulse constantly?&n;&t;&t;*/
r_int
id|static_brightness
op_assign
id|command
op_amp
l_int|0xFF
suffix:semicolon
singleline_comment|// bits 0-7
r_int
id|pulse_speed
op_assign
(paren
id|command
op_rshift
l_int|8
)paren
op_amp
l_int|0x1FF
suffix:semicolon
singleline_comment|// bits 8-16
r_int
id|pulse_table
op_assign
(paren
id|command
op_rshift
l_int|17
)paren
op_amp
l_int|0x3
suffix:semicolon
singleline_comment|// bits 17-18
r_int
id|pulse_asleep
op_assign
(paren
id|command
op_rshift
l_int|19
)paren
op_amp
l_int|0x1
suffix:semicolon
singleline_comment|// bit 19
r_int
id|pulse_awake
op_assign
(paren
id|command
op_rshift
l_int|20
)paren
op_amp
l_int|0x1
suffix:semicolon
singleline_comment|// bit 20
id|powermate_pulse_led
c_func
(paren
id|pm
comma
id|static_brightness
comma
id|pulse_speed
comma
id|pulse_table
comma
id|pulse_asleep
comma
id|pulse_awake
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called whenever a USB device matching one in our supported devices table is connected */
DECL|function|powermate_probe
r_static
r_void
op_star
id|powermate_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_int
r_int
id|ifnum
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|powermate_device
op_star
id|pm
suffix:semicolon
r_int
id|pipe
comma
id|maxp
suffix:semicolon
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
id|interface
op_assign
id|udev-&gt;config
(braket
l_int|0
)braket
dot
id|interface
(braket
id|ifnum
)braket
dot
id|altsetting
op_plus
l_int|0
suffix:semicolon
id|endpoint
op_assign
id|interface-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
l_int|NULL
suffix:semicolon
id|usb_control_msg
c_func
(paren
id|udev
comma
id|usb_sndctrlpipe
c_func
(paren
id|udev
comma
l_int|0
)paren
comma
l_int|0x0a
comma
id|USB_TYPE_CLASS
op_or
id|USB_RECIP_INTERFACE
comma
l_int|0
comma
id|interface-&gt;bInterfaceNumber
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|pm
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|powermate_device
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|pm
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|powermate_device
)paren
)paren
suffix:semicolon
id|pm-&gt;udev
op_assign
id|udev
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* get a handle to the interrupt data pipe */
id|pipe
op_assign
id|usb_rcvintpipe
c_func
(paren
id|udev
comma
id|endpoint-&gt;bEndpointAddress
)paren
suffix:semicolon
id|maxp
op_assign
id|usb_maxpacket
c_func
(paren
id|udev
comma
id|pipe
comma
id|usb_pipeout
c_func
(paren
id|pipe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|maxp
op_ne
id|POWERMATE_PAYLOAD_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;powermate: Expected payload of %d bytes, found %d bytes!&bslash;n&quot;
comma
id|POWERMATE_PAYLOAD_SIZE
comma
id|maxp
)paren
suffix:semicolon
)brace
id|FILL_INT_URB
c_func
(paren
op_amp
id|pm-&gt;irq
comma
id|udev
comma
id|pipe
comma
id|pm-&gt;data
comma
id|POWERMATE_PAYLOAD_SIZE
comma
id|powermate_irq
comma
id|pm
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
multiline_comment|/* register our interrupt URB with the USB system */
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
op_amp
id|pm-&gt;irq
comma
id|GFP_KERNEL
)paren
)paren
(brace
id|kfree
c_func
(paren
id|pm
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* failure */
)brace
r_switch
c_cond
(paren
id|udev-&gt;descriptor.idProduct
)paren
(brace
r_case
id|POWERMATE_PRODUCT_NEW
suffix:colon
id|pm-&gt;input.name
op_assign
id|pm_name_powermate
suffix:semicolon
r_break
suffix:semicolon
r_case
id|POWERMATE_PRODUCT_OLD
suffix:colon
id|pm-&gt;input.name
op_assign
id|pm_name_soundknob
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pm-&gt;input.name
op_assign
id|pm_name_soundknob
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;powermate: unknown product id %04x&bslash;n&quot;
comma
id|udev-&gt;descriptor.idProduct
)paren
suffix:semicolon
)brace
id|pm-&gt;input
dot
r_private
op_assign
id|pm
suffix:semicolon
id|pm-&gt;input.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_REL
)paren
op_or
id|BIT
c_func
(paren
id|EV_MSC
)paren
suffix:semicolon
id|pm-&gt;input.keybit
(braket
id|LONG
c_func
(paren
id|BTN_0
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_0
)paren
suffix:semicolon
id|pm-&gt;input.relbit
(braket
id|LONG
c_func
(paren
id|REL_DIAL
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|REL_DIAL
)paren
suffix:semicolon
id|pm-&gt;input.mscbit
(braket
id|LONG
c_func
(paren
id|MSC_PULSELED
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|MSC_PULSELED
)paren
suffix:semicolon
id|pm-&gt;input.idbus
op_assign
id|BUS_USB
suffix:semicolon
id|pm-&gt;input.idvendor
op_assign
id|udev-&gt;descriptor.idVendor
suffix:semicolon
id|pm-&gt;input.idproduct
op_assign
id|udev-&gt;descriptor.idProduct
suffix:semicolon
id|pm-&gt;input.idversion
op_assign
id|udev-&gt;descriptor.bcdDevice
suffix:semicolon
id|pm-&gt;input.event
op_assign
id|powermate_input_event
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|pm-&gt;input
)paren
suffix:semicolon
id|usb_make_path
c_func
(paren
id|udev
comma
id|path
comma
l_int|64
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|pm-&gt;phys
comma
l_int|64
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|pm-&gt;input.name
comma
id|pm-&gt;input.phys
)paren
suffix:semicolon
multiline_comment|/* force an update of everything */
id|pm-&gt;requires_update
op_assign
id|UPDATE_PULSE_ASLEEP
op_or
id|UPDATE_PULSE_AWAKE
op_or
id|UPDATE_PULSE_MODE
op_or
id|UPDATE_STATIC_BRIGHTNESS
suffix:semicolon
id|powermate_pulse_led
c_func
(paren
id|pm
comma
l_int|0x80
comma
l_int|255
comma
l_int|0
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// set default pulse parameters
r_return
id|pm
suffix:semicolon
)brace
multiline_comment|/* Called when a USB device we&squot;ve accepted ownership of is removed */
DECL|function|powermate_disconnect
r_static
r_void
id|powermate_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|powermate_device
op_star
id|pm
op_assign
id|ptr
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pm-&gt;lock
)paren
suffix:semicolon
id|pm-&gt;requires_update
op_assign
l_int|0
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
op_amp
id|pm-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|pm-&gt;input
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pm
)paren
suffix:semicolon
)brace
DECL|variable|powermate_devices
r_static
r_struct
id|usb_device_id
id|powermate_devices
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|POWERMATE_VENDOR
comma
id|POWERMATE_PRODUCT_NEW
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|POWERMATE_VENDOR
comma
id|POWERMATE_PRODUCT_OLD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|CONTOUR_VENDOR
comma
id|CONTOUR_JOG
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|powermate_devices
)paren
suffix:semicolon
DECL|variable|powermate_driver
r_static
r_struct
id|usb_driver
id|powermate_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;powermate&quot;
comma
dot
id|probe
op_assign
id|powermate_probe
comma
dot
id|disconnect
op_assign
id|powermate_disconnect
comma
dot
id|id_table
op_assign
id|powermate_devices
comma
)brace
suffix:semicolon
DECL|function|powermate_init
r_int
id|powermate_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|powermate_driver
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|powermate_cleanup
r_void
id|powermate_cleanup
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|powermate_driver
)paren
suffix:semicolon
)brace
DECL|variable|powermate_init
id|module_init
c_func
(paren
id|powermate_init
)paren
suffix:semicolon
DECL|variable|powermate_cleanup
id|module_exit
c_func
(paren
id|powermate_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;William R Sowerbutts&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Griffin Technology, Inc PowerMate driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof