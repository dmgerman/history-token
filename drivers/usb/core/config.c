macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|USB_MAXALTSETTING
mdefine_line|#define USB_MAXALTSETTING&t;&t;128&t;/* Hard limit */
DECL|macro|USB_MAXENDPOINTS
mdefine_line|#define USB_MAXENDPOINTS&t;&t;30&t;/* Hard limit */
multiline_comment|/* these maximums are arbitrary */
DECL|macro|USB_MAXCONFIG
mdefine_line|#define USB_MAXCONFIG&t;&t;&t;8
DECL|macro|USB_MAXINTERFACES
mdefine_line|#define USB_MAXINTERFACES&t;&t;32
DECL|function|usb_parse_endpoint
r_static
r_int
id|usb_parse_endpoint
c_func
(paren
r_struct
id|usb_host_endpoint
op_star
id|endpoint
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_int
r_char
op_star
id|buffer0
op_assign
id|buffer
suffix:semicolon
r_struct
id|usb_descriptor_header
op_star
id|header
suffix:semicolon
r_int
r_char
op_star
id|begin
suffix:semicolon
r_int
id|len
comma
id|numskipped
suffix:semicolon
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;bDescriptorType
op_ne
id|USB_DT_ENDPOINT
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;unexpected descriptor 0x%X, expecting endpoint, 0x%X&quot;
comma
id|header-&gt;bDescriptorType
comma
id|USB_DT_ENDPOINT
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
id|header-&gt;bLength
op_eq
id|USB_DT_ENDPOINT_AUDIO_SIZE
)paren
id|memcpy
c_func
(paren
op_amp
id|endpoint-&gt;desc
comma
id|buffer
comma
id|USB_DT_ENDPOINT_AUDIO_SIZE
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
op_amp
id|endpoint-&gt;desc
comma
id|buffer
comma
id|USB_DT_ENDPOINT_SIZE
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|endpoint-&gt;desc.wMaxPacketSize
)paren
suffix:semicolon
id|buffer
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors */
id|begin
op_assign
id|buffer
suffix:semicolon
id|numskipped
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/* If we find another &quot;proper&quot; descriptor then we&squot;re done  */
r_if
c_cond
(paren
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_ENDPOINT
)paren
op_logical_or
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
)paren
r_break
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;skipping descriptor 0x%X&quot;
comma
id|header-&gt;bDescriptorType
)paren
suffix:semicolon
id|numskipped
op_increment
suffix:semicolon
id|buffer
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numskipped
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;skipped %d class/vendor specific endpoint descriptors&quot;
comma
id|numskipped
)paren
suffix:semicolon
multiline_comment|/* Copy any unknown descriptors into a storage area for drivers */
multiline_comment|/*  to later parse */
id|len
op_assign
id|buffer
op_minus
id|begin
suffix:semicolon
id|endpoint-&gt;extra
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|endpoint-&gt;extra
)paren
(brace
id|err
c_func
(paren
l_string|&quot;couldn&squot;t allocate memory for endpoint extra descriptors&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|endpoint-&gt;extra
comma
id|begin
comma
id|len
)paren
suffix:semicolon
id|endpoint-&gt;extralen
op_assign
id|len
suffix:semicolon
)brace
r_return
id|buffer
op_minus
id|buffer0
suffix:semicolon
)brace
DECL|function|usb_release_intf
r_static
r_void
id|usb_release_intf
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|usb_interface
op_star
id|intf
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|k
suffix:semicolon
id|intf
op_assign
id|to_usb_interface
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intf-&gt;altsetting
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|intf-&gt;num_altsetting
suffix:semicolon
id|j
op_increment
)paren
(brace
r_struct
id|usb_host_interface
op_star
id|as
op_assign
op_amp
id|intf-&gt;altsetting
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;extra
)paren
id|kfree
c_func
(paren
id|as-&gt;extra
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;endpoint
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|as-&gt;desc.bNumEndpoints
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|as-&gt;endpoint
(braket
id|k
)braket
dot
id|extra
)paren
id|kfree
c_func
(paren
id|as-&gt;endpoint
(braket
id|k
)braket
dot
id|extra
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as-&gt;endpoint
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|intf-&gt;altsetting
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|intf
)paren
suffix:semicolon
)brace
DECL|function|usb_parse_interface
r_static
r_int
id|usb_parse_interface
c_func
(paren
r_struct
id|usb_interface
op_star
id|interface
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|size
)paren
(brace
r_int
r_char
op_star
id|buffer0
op_assign
id|buffer
suffix:semicolon
r_int
id|i
comma
id|len
comma
id|numskipped
comma
id|retval
suffix:semicolon
r_struct
id|usb_descriptor_header
op_star
id|header
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|ifp
suffix:semicolon
r_int
r_char
op_star
id|begin
suffix:semicolon
id|ifp
op_assign
id|interface-&gt;altsetting
suffix:semicolon
r_while
c_loop
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|d
suffix:semicolon
id|d
op_assign
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bAlternateSetting
op_ge
id|interface-&gt;num_altsetting
)paren
(brace
multiline_comment|/* Skip to the next interface descriptor */
id|buffer
op_add_assign
id|d-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|d-&gt;bLength
suffix:semicolon
r_while
c_loop
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
r_break
suffix:semicolon
id|buffer
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|ifp-&gt;desc
comma
id|buffer
comma
id|USB_DT_INTERFACE_SIZE
)paren
suffix:semicolon
id|buffer
op_add_assign
id|ifp-&gt;desc.bLength
suffix:semicolon
id|size
op_sub_assign
id|ifp-&gt;desc.bLength
suffix:semicolon
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors */
id|begin
op_assign
id|buffer
suffix:semicolon
id|numskipped
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/* If we find another &quot;proper&quot; descriptor then we&squot;re done  */
r_if
c_cond
(paren
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
op_logical_or
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_ENDPOINT
)paren
)paren
r_break
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;skipping descriptor 0x%X&quot;
comma
id|header-&gt;bDescriptorType
)paren
suffix:semicolon
id|numskipped
op_increment
suffix:semicolon
id|buffer
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numskipped
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;skipped %d class/vendor specific interface descriptors&quot;
comma
id|numskipped
)paren
suffix:semicolon
multiline_comment|/* Copy any unknown descriptors into a storage area for */
multiline_comment|/*  drivers to later parse */
id|len
op_assign
id|buffer
op_minus
id|begin
suffix:semicolon
id|ifp-&gt;extra
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ifp-&gt;extra
)paren
(brace
id|err
c_func
(paren
l_string|&quot;couldn&squot;t allocate memory for interface extra descriptors&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|ifp-&gt;extra
comma
id|begin
comma
id|len
)paren
suffix:semicolon
id|ifp-&gt;extralen
op_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ifp-&gt;desc.bNumEndpoints
OG
id|USB_MAXENDPOINTS
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;too many endpoints&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|len
op_assign
id|ifp-&gt;desc.bNumEndpoints
op_star
r_sizeof
(paren
r_struct
id|usb_host_endpoint
)paren
suffix:semicolon
id|ifp-&gt;endpoint
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ifp-&gt;endpoint
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ifp-&gt;endpoint
comma
l_int|0
comma
id|len
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
id|ifp-&gt;desc.bNumEndpoints
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|size
OL
id|USB_DT_ENDPOINT_SIZE
)paren
(brace
id|err
c_func
(paren
l_string|&quot;ran out of descriptors parsing&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|retval
op_assign
id|usb_parse_endpoint
c_func
(paren
id|ifp-&gt;endpoint
op_plus
id|i
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|buffer
op_add_assign
id|retval
suffix:semicolon
id|size
op_sub_assign
id|retval
suffix:semicolon
)brace
multiline_comment|/* We check to see if it&squot;s an alternate to this one */
id|d
op_assign
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|USB_DT_INTERFACE_SIZE
op_logical_or
id|d-&gt;bDescriptorType
op_ne
id|USB_DT_INTERFACE
op_logical_or
op_logical_neg
id|d-&gt;bAlternateSetting
)paren
r_break
suffix:semicolon
op_increment
id|ifp
suffix:semicolon
)brace
r_return
id|buffer
op_minus
id|buffer0
suffix:semicolon
)brace
DECL|function|usb_parse_configuration
r_int
id|usb_parse_configuration
c_func
(paren
r_struct
id|usb_host_config
op_star
id|config
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|nintf
comma
id|nintf_orig
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|size
suffix:semicolon
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
r_char
op_star
id|buffer2
suffix:semicolon
r_int
id|size2
suffix:semicolon
r_struct
id|usb_descriptor_header
op_star
id|header
suffix:semicolon
r_int
id|numskipped
comma
id|len
suffix:semicolon
r_char
op_star
id|begin
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|config-&gt;desc
comma
id|buffer
comma
id|USB_DT_CONFIG_SIZE
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|config-&gt;desc.wTotalLength
)paren
suffix:semicolon
id|size
op_assign
id|config-&gt;desc.wTotalLength
suffix:semicolon
id|nintf
op_assign
id|nintf_orig
op_assign
id|config-&gt;desc.bNumInterfaces
suffix:semicolon
r_if
c_cond
(paren
id|nintf
OG
id|USB_MAXINTERFACES
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;too many interfaces (%d max %d)&quot;
comma
id|nintf
comma
id|USB_MAXINTERFACES
)paren
suffix:semicolon
id|config-&gt;desc.bNumInterfaces
op_assign
id|nintf
op_assign
id|USB_MAXINTERFACES
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nintf
suffix:semicolon
op_increment
id|i
)paren
(brace
id|interface
op_assign
id|config-&gt;interface
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_interface
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;kmalloc IF %p, numif %i&quot;
comma
id|interface
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interface
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|interface
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usb_interface
)paren
)paren
suffix:semicolon
id|interface-&gt;dev.release
op_assign
id|usb_release_intf
suffix:semicolon
id|device_initialize
c_func
(paren
op_amp
id|interface-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* put happens in usb_destroy_configuration */
id|get_device
c_func
(paren
op_amp
id|interface-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Go through the descriptors, checking their length and counting the&n;&t; * number of altsettings for each interface */
id|buffer2
op_assign
id|buffer
suffix:semicolon
id|size2
op_assign
id|size
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size2
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|header-&gt;bLength
OG
id|size2
)paren
op_logical_or
(paren
id|header-&gt;bLength
OL
l_int|2
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;invalid descriptor of length %d&quot;
comma
id|header-&gt;bLength
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
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|d
suffix:semicolon
r_if
c_cond
(paren
id|header-&gt;bLength
OL
id|USB_DT_INTERFACE_SIZE
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;invalid interface descriptor&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|d
op_assign
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
id|header
suffix:semicolon
id|i
op_assign
id|d-&gt;bInterfaceNumber
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|nintf_orig
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;invalid interface number (%d/%d)&quot;
comma
id|i
comma
id|nintf_orig
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
id|i
OL
id|nintf
)paren
op_increment
id|config-&gt;interface
(braket
id|i
)braket
op_member_access_from_pointer
id|num_altsetting
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_DEVICE
op_logical_or
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_CONFIG
)paren
op_logical_and
id|j
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;unexpected descriptor type 0x%X&quot;
comma
id|header-&gt;bDescriptorType
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|j
op_assign
l_int|1
suffix:semicolon
id|buffer2
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size2
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
)brace
multiline_comment|/* Allocate the altsetting arrays */
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
op_increment
id|i
)paren
(brace
id|interface
op_assign
id|config-&gt;interface
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|interface-&gt;num_altsetting
OG
id|USB_MAXALTSETTING
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;too many alternate settings for interface %d (%d max %d)&bslash;n&quot;
comma
id|i
comma
id|interface-&gt;num_altsetting
comma
id|USB_MAXALTSETTING
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
id|interface-&gt;num_altsetting
op_eq
l_int|0
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;no alternate settings for interface %d&quot;
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|len
op_assign
r_sizeof
(paren
op_star
id|interface-&gt;altsetting
)paren
op_star
id|interface-&gt;num_altsetting
suffix:semicolon
id|interface-&gt;altsetting
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interface-&gt;altsetting
)paren
(brace
id|err
c_func
(paren
l_string|&quot;couldn&squot;t kmalloc interface-&gt;altsetting&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|interface-&gt;altsetting
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
)brace
id|buffer
op_add_assign
id|config-&gt;desc.bLength
suffix:semicolon
id|size
op_sub_assign
id|config-&gt;desc.bLength
suffix:semicolon
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors */
id|begin
op_assign
id|buffer
suffix:semicolon
id|numskipped
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
op_ge
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/* If we find another &quot;proper&quot; descriptor then we&squot;re done  */
r_if
c_cond
(paren
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_ENDPOINT
)paren
op_logical_or
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
)paren
r_break
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;skipping descriptor 0x%X&quot;
comma
id|header-&gt;bDescriptorType
)paren
suffix:semicolon
id|numskipped
op_increment
suffix:semicolon
id|buffer
op_add_assign
id|header-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|header-&gt;bLength
suffix:semicolon
)brace
r_if
c_cond
(paren
id|numskipped
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;skipped %d class/vendor specific configuration descriptors&quot;
comma
id|numskipped
)paren
suffix:semicolon
multiline_comment|/* Copy any unknown descriptors into a storage area for */
multiline_comment|/*  drivers to later parse */
id|len
op_assign
id|buffer
op_minus
id|begin
suffix:semicolon
id|config-&gt;extra
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|config-&gt;extra
)paren
(brace
id|err
c_func
(paren
l_string|&quot;couldn&squot;t allocate memory for config extra descriptors&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|config-&gt;extra
comma
id|begin
comma
id|len
)paren
suffix:semicolon
id|config-&gt;extralen
op_assign
id|len
suffix:semicolon
)brace
multiline_comment|/* Parse all the interface/altsetting descriptors */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nintf_orig
suffix:semicolon
id|i
op_increment
)paren
(brace
id|retval
op_assign
id|usb_parse_interface
c_func
(paren
id|config-&gt;interface
(braket
id|i
)braket
comma
id|buffer
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|buffer
op_add_assign
id|retval
suffix:semicolon
id|size
op_sub_assign
id|retval
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
singleline_comment|// hub-only!! ... and only exported for reset/reinit path.
singleline_comment|// otherwise used internally on disconnect/destroy path
DECL|function|usb_destroy_configuration
r_void
id|usb_destroy_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|c
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;config
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;rawdescriptors
)paren
(brace
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
id|kfree
c_func
(paren
id|dev-&gt;rawdescriptors
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;rawdescriptors
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
id|c
op_increment
)paren
(brace
r_struct
id|usb_host_config
op_star
id|cf
op_assign
op_amp
id|dev-&gt;config
(braket
id|c
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
id|cf-&gt;desc.bNumInterfaces
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
id|cf-&gt;interface
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ifp
)paren
id|put_device
c_func
(paren
op_amp
id|ifp-&gt;dev
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|cf-&gt;extra
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|dev-&gt;config
)paren
suffix:semicolon
)brace
singleline_comment|// hub-only!! ... and only in reset path, or usb_new_device()
singleline_comment|// (used by real hubs and virtual root hubs)
DECL|function|usb_get_configuration
r_int
id|usb_get_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|ncfg
op_assign
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
r_int
id|cfgno
comma
id|length
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_char
op_star
id|bigbuffer
suffix:semicolon
r_struct
id|usb_config_descriptor
op_star
id|desc
suffix:semicolon
r_if
c_cond
(paren
id|ncfg
OG
id|USB_MAXCONFIG
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;too many configurations (%d max %d)&quot;
comma
id|ncfg
comma
id|USB_MAXCONFIG
)paren
suffix:semicolon
id|dev-&gt;descriptor.bNumConfigurations
op_assign
id|ncfg
op_assign
id|USB_MAXCONFIG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncfg
OL
l_int|1
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;no configurations&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|length
op_assign
id|ncfg
op_star
r_sizeof
(paren
r_struct
id|usb_host_config
)paren
suffix:semicolon
id|dev-&gt;config
op_assign
id|kmalloc
c_func
(paren
id|length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;config
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev-&gt;config
comma
l_int|0
comma
id|length
)paren
suffix:semicolon
id|length
op_assign
id|ncfg
op_star
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|dev-&gt;rawdescriptors
op_assign
id|kmalloc
c_func
(paren
id|length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;rawdescriptors
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev-&gt;rawdescriptors
comma
l_int|0
comma
id|length
)paren
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
l_int|8
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
id|desc
op_assign
(paren
r_struct
id|usb_config_descriptor
op_star
)paren
id|buffer
suffix:semicolon
r_for
c_loop
(paren
id|cfgno
op_assign
l_int|0
suffix:semicolon
id|cfgno
OL
id|ncfg
suffix:semicolon
id|cfgno
op_increment
)paren
(brace
multiline_comment|/* We grab the first 8 bytes so we know how long the whole */
multiline_comment|/*  configuration is */
id|result
op_assign
id|usb_get_descriptor
c_func
(paren
id|dev
comma
id|USB_DT_CONFIG
comma
id|cfgno
comma
id|buffer
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;unable to get descriptor&quot;
)paren
suffix:semicolon
r_else
(brace
id|err
c_func
(paren
l_string|&quot;config descriptor too short (expected %i, got %i)&quot;
comma
l_int|8
comma
id|result
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/* Get the full buffer */
id|length
op_assign
id|le16_to_cpu
c_func
(paren
id|desc-&gt;wTotalLength
)paren
suffix:semicolon
id|bigbuffer
op_assign
id|kmalloc
c_func
(paren
id|length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bigbuffer
)paren
(brace
id|err
c_func
(paren
l_string|&quot;unable to allocate memory for configuration descriptors&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/* Now that we know the length, get the whole thing */
id|result
op_assign
id|usb_get_descriptor
c_func
(paren
id|dev
comma
id|USB_DT_CONFIG
comma
id|cfgno
comma
id|bigbuffer
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|err
c_func
(paren
l_string|&quot;couldn&squot;t get all of config descriptors&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bigbuffer
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
id|length
)paren
(brace
id|err
c_func
(paren
l_string|&quot;config descriptor too short (expected %i, got %i)&quot;
comma
id|length
comma
id|result
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|bigbuffer
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|dev-&gt;rawdescriptors
(braket
id|cfgno
)braket
op_assign
id|bigbuffer
suffix:semicolon
id|result
op_assign
id|usb_parse_configuration
c_func
(paren
op_amp
id|dev-&gt;config
(braket
id|cfgno
)braket
comma
id|bigbuffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OG
l_int|0
)paren
id|dbg
c_func
(paren
l_string|&quot;descriptor data left&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
op_increment
id|cfgno
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|dev-&gt;descriptor.bNumConfigurations
op_assign
id|cfgno
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
