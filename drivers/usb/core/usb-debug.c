multiline_comment|/*&n; * debug.c - USB debug helper routines.&n; *&n; * I just want these out of the way where they aren&squot;t in your&n; * face, but so that you can still use them..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
DECL|function|usb_show_endpoint
r_static
r_void
id|usb_show_endpoint
c_func
(paren
r_struct
id|usb_host_endpoint
op_star
id|endpoint
)paren
(brace
id|usb_show_endpoint_descriptor
c_func
(paren
op_amp
id|endpoint-&gt;desc
)paren
suffix:semicolon
)brace
DECL|function|usb_show_interface
r_static
r_void
id|usb_show_interface
c_func
(paren
r_struct
id|usb_host_interface
op_star
id|altsetting
)paren
(brace
r_int
id|i
suffix:semicolon
id|usb_show_interface_descriptor
c_func
(paren
op_amp
id|altsetting-&gt;desc
)paren
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
id|altsetting-&gt;desc.bNumEndpoints
suffix:semicolon
id|i
op_increment
)paren
id|usb_show_endpoint
c_func
(paren
id|altsetting-&gt;endpoint
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|function|usb_show_config
r_static
r_void
id|usb_show_config
c_func
(paren
r_struct
id|usb_host_config
op_star
id|config
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|usb_interface
op_star
id|ifp
suffix:semicolon
id|usb_show_config_descriptor
c_func
(paren
op_amp
id|config-&gt;desc
)paren
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
id|config-&gt;desc.bNumInterfaces
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ifp
op_assign
id|config-&gt;interface
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ifp
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n  Interface: %d&bslash;n&quot;
comma
id|i
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
id|ifp-&gt;num_altsetting
suffix:semicolon
id|j
op_increment
)paren
id|usb_show_interface
c_func
(paren
id|ifp-&gt;altsetting
op_plus
id|j
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_show_device
r_void
id|usb_show_device
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
suffix:semicolon
id|usb_show_device_descriptor
c_func
(paren
op_amp
id|dev-&gt;descriptor
)paren
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
id|usb_show_config
c_func
(paren
id|dev-&gt;config
op_plus
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse and show the different USB descriptors.&n; */
DECL|function|usb_show_device_descriptor
r_void
id|usb_show_device_descriptor
c_func
(paren
r_struct
id|usb_device_descriptor
op_star
id|desc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|desc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid USB device descriptor (NULL POINTER)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;  Length              = %2d%s&bslash;n&quot;
comma
id|desc-&gt;bLength
comma
id|desc-&gt;bLength
op_eq
id|USB_DT_DEVICE_SIZE
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (!!!)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  DescriptorType      = %02x&bslash;n&quot;
comma
id|desc-&gt;bDescriptorType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  USB version         = %x.%02x&bslash;n&quot;
comma
id|desc-&gt;bcdUSB
op_rshift
l_int|8
comma
id|desc-&gt;bcdUSB
op_amp
l_int|0xff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Vendor:Product      = %04x:%04x&bslash;n&quot;
comma
id|desc-&gt;idVendor
comma
id|desc-&gt;idProduct
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  MaxPacketSize0      = %d&bslash;n&quot;
comma
id|desc-&gt;bMaxPacketSize0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  NumConfigurations   = %d&bslash;n&quot;
comma
id|desc-&gt;bNumConfigurations
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Device version      = %x.%02x&bslash;n&quot;
comma
id|desc-&gt;bcdDevice
op_rshift
l_int|8
comma
id|desc-&gt;bcdDevice
op_amp
l_int|0xff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Device Class:SubClass:Protocol = %02x:%02x:%02x&bslash;n&quot;
comma
id|desc-&gt;bDeviceClass
comma
id|desc-&gt;bDeviceSubClass
comma
id|desc-&gt;bDeviceProtocol
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|desc-&gt;bDeviceClass
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Per-interface classes&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_AUDIO
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Audio device class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_COMM
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Communications class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_HID
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Human Interface Devices class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_PRINTER
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Printer device class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_MASS_STORAGE
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Mass Storage device class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_HUB
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Hub device class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_CLASS_VENDOR_SPEC
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Vendor class&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    Unknown class&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_show_config_descriptor
r_void
id|usb_show_config_descriptor
c_func
(paren
r_struct
id|usb_config_descriptor
op_star
id|desc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Configuration:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bLength             = %4d%s&bslash;n&quot;
comma
id|desc-&gt;bLength
comma
id|desc-&gt;bLength
op_eq
id|USB_DT_CONFIG_SIZE
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (!!!)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bDescriptorType     =   %02x&bslash;n&quot;
comma
id|desc-&gt;bDescriptorType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  wTotalLength        = %04x&bslash;n&quot;
comma
id|desc-&gt;wTotalLength
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bNumInterfaces      =   %02x&bslash;n&quot;
comma
id|desc-&gt;bNumInterfaces
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bConfigurationValue =   %02x&bslash;n&quot;
comma
id|desc-&gt;bConfigurationValue
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  iConfiguration      =   %02x&bslash;n&quot;
comma
id|desc-&gt;iConfiguration
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bmAttributes        =   %02x&bslash;n&quot;
comma
id|desc-&gt;bmAttributes
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  bMaxPower            = %4dmA&bslash;n&quot;
comma
id|desc-&gt;bMaxPower
op_star
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|usb_show_interface_descriptor
r_void
id|usb_show_interface_descriptor
c_func
(paren
r_struct
id|usb_interface_descriptor
op_star
id|desc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  Alternate Setting: %2d&bslash;n&quot;
comma
id|desc-&gt;bAlternateSetting
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bLength             = %4d%s&bslash;n&quot;
comma
id|desc-&gt;bLength
comma
id|desc-&gt;bLength
op_eq
id|USB_DT_INTERFACE_SIZE
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (!!!)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bDescriptorType     =   %02x&bslash;n&quot;
comma
id|desc-&gt;bDescriptorType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bInterfaceNumber    =   %02x&bslash;n&quot;
comma
id|desc-&gt;bInterfaceNumber
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bAlternateSetting   =   %02x&bslash;n&quot;
comma
id|desc-&gt;bAlternateSetting
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bNumEndpoints       =   %02x&bslash;n&quot;
comma
id|desc-&gt;bNumEndpoints
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    bInterface Class:SubClass:Protocol =   %02x:%02x:%02x&bslash;n&quot;
comma
id|desc-&gt;bInterfaceClass
comma
id|desc-&gt;bInterfaceSubClass
comma
id|desc-&gt;bInterfaceProtocol
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    iInterface          =   %02x&bslash;n&quot;
comma
id|desc-&gt;iInterface
)paren
suffix:semicolon
)brace
DECL|function|usb_show_endpoint_descriptor
r_void
id|usb_show_endpoint_descriptor
c_func
(paren
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
)paren
(brace
r_char
op_star
id|LengthCommentString
op_assign
(paren
id|desc-&gt;bLength
op_eq
id|USB_DT_ENDPOINT_AUDIO_SIZE
)paren
ques
c_cond
l_string|&quot; (Audio)&quot;
suffix:colon
(paren
id|desc-&gt;bLength
op_eq
id|USB_DT_ENDPOINT_SIZE
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; (!!!)&quot;
suffix:semicolon
r_char
op_star
id|EndpointType
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;Control&quot;
comma
l_string|&quot;Isochronous&quot;
comma
l_string|&quot;Bulk&quot;
comma
l_string|&quot;Interrupt&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;    Endpoint:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bLength             = %4d%s&bslash;n&quot;
comma
id|desc-&gt;bLength
comma
id|LengthCommentString
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bDescriptorType     =   %02x&bslash;n&quot;
comma
id|desc-&gt;bDescriptorType
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bEndpointAddress    =   %02x (%s)&bslash;n&quot;
comma
id|desc-&gt;bEndpointAddress
comma
(paren
id|desc-&gt;bmAttributes
op_amp
id|USB_ENDPOINT_XFERTYPE_MASK
)paren
op_eq
id|USB_ENDPOINT_XFER_CONTROL
ques
c_cond
l_string|&quot;i/o&quot;
suffix:colon
(paren
id|desc-&gt;bEndpointAddress
op_amp
id|USB_ENDPOINT_DIR_MASK
)paren
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;out&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bmAttributes        =   %02x (%s)&bslash;n&quot;
comma
id|desc-&gt;bmAttributes
comma
id|EndpointType
(braket
id|USB_ENDPOINT_XFERTYPE_MASK
op_amp
id|desc-&gt;bmAttributes
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      wMaxPacketSize      = %04x&bslash;n&quot;
comma
id|desc-&gt;wMaxPacketSize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bInterval           =   %02x&bslash;n&quot;
comma
id|desc-&gt;bInterval
)paren
suffix:semicolon
multiline_comment|/* Audio extensions to the endpoint descriptor */
r_if
c_cond
(paren
id|desc-&gt;bLength
op_eq
id|USB_DT_ENDPOINT_AUDIO_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;      bRefresh            =   %02x&bslash;n&quot;
comma
id|desc-&gt;bRefresh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      bSynchAddress       =   %02x&bslash;n&quot;
comma
id|desc-&gt;bSynchAddress
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_show_string
r_void
id|usb_show_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_char
op_star
id|id
comma
r_int
id|index
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|index
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
op_assign
id|kmalloc
c_func
(paren
l_int|256
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|usb_string
c_func
(paren
id|dev
comma
id|index
comma
id|buf
comma
l_int|256
)paren
OG
l_int|0
)paren
id|dev_printk
c_func
(paren
id|KERN_INFO
comma
op_amp
id|dev-&gt;dev
comma
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|id
comma
id|buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|usb_dump_urb
r_void
id|usb_dump_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
id|printk
(paren
l_string|&quot;urb                   :%p&bslash;n&quot;
comma
id|urb
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;dev                   :%p&bslash;n&quot;
comma
id|urb-&gt;dev
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;pipe                  :%08X&bslash;n&quot;
comma
id|urb-&gt;pipe
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;status                :%d&bslash;n&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;transfer_flags        :%08X&bslash;n&quot;
comma
id|urb-&gt;transfer_flags
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;transfer_buffer       :%p&bslash;n&quot;
comma
id|urb-&gt;transfer_buffer
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;transfer_buffer_length:%d&bslash;n&quot;
comma
id|urb-&gt;transfer_buffer_length
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;actual_length         :%d&bslash;n&quot;
comma
id|urb-&gt;actual_length
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;setup_packet          :%p&bslash;n&quot;
comma
id|urb-&gt;setup_packet
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;start_frame           :%d&bslash;n&quot;
comma
id|urb-&gt;start_frame
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;number_of_packets     :%d&bslash;n&quot;
comma
id|urb-&gt;number_of_packets
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;interval              :%d&bslash;n&quot;
comma
id|urb-&gt;interval
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;error_count           :%d&bslash;n&quot;
comma
id|urb-&gt;error_count
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;context               :%p&bslash;n&quot;
comma
id|urb-&gt;context
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;complete              :%p&bslash;n&quot;
comma
id|urb-&gt;complete
)paren
suffix:semicolon
)brace
eof
