macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|USB_MAXALTSETTING
mdefine_line|#define USB_MAXALTSETTING&t;&t;128&t;/* Hard limit */
DECL|macro|USB_MAXENDPOINTS
mdefine_line|#define USB_MAXENDPOINTS&t;&t;30&t;/* Hard limit */
DECL|macro|USB_MAXCONFIG
mdefine_line|#define USB_MAXCONFIG&t;&t;&t;8&t;/* Arbitrary limit */
DECL|function|plural
r_static
r_inline
r_const
r_char
op_star
id|plural
c_func
(paren
r_int
id|n
)paren
(brace
r_return
(paren
id|n
op_eq
l_int|1
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
)brace
DECL|function|find_next_descriptor
r_static
r_int
id|find_next_descriptor
c_func
(paren
r_int
r_char
op_star
id|buffer
comma
r_int
id|size
comma
r_int
id|dt1
comma
r_int
id|dt2
comma
r_int
op_star
id|num_skipped
)paren
(brace
r_struct
id|usb_descriptor_header
op_star
id|h
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|buffer0
op_assign
id|buffer
suffix:semicolon
multiline_comment|/* Find the next descriptor of type dt1 or dt2 */
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|h
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
id|h-&gt;bDescriptorType
op_eq
id|dt1
op_logical_or
id|h-&gt;bDescriptorType
op_eq
id|dt2
)paren
r_break
suffix:semicolon
id|buffer
op_add_assign
id|h-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|h-&gt;bLength
suffix:semicolon
op_increment
id|n
suffix:semicolon
)brace
multiline_comment|/* Store the number of descriptors skipped and return the&n;&t; * number of bytes skipped */
r_if
c_cond
(paren
id|num_skipped
)paren
op_star
id|num_skipped
op_assign
id|n
suffix:semicolon
r_return
id|buffer
op_minus
id|buffer0
suffix:semicolon
)brace
DECL|function|usb_parse_endpoint
r_static
r_int
id|usb_parse_endpoint
c_func
(paren
r_struct
id|device
op_star
id|ddev
comma
r_int
id|cfgno
comma
r_int
id|inum
comma
r_int
id|asnum
comma
r_struct
id|usb_host_interface
op_star
id|ifp
comma
r_int
id|num_ep
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
id|usb_endpoint_descriptor
op_star
id|d
suffix:semicolon
r_struct
id|usb_host_endpoint
op_star
id|endpoint
suffix:semicolon
r_int
id|n
comma
id|i
suffix:semicolon
id|d
op_assign
(paren
r_struct
id|usb_endpoint_descriptor
op_star
)paren
id|buffer
suffix:semicolon
id|buffer
op_add_assign
id|d-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|d-&gt;bLength
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bLength
op_ge
id|USB_DT_ENDPOINT_AUDIO_SIZE
)paren
id|n
op_assign
id|USB_DT_ENDPOINT_AUDIO_SIZE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|d-&gt;bLength
op_ge
id|USB_DT_ENDPOINT_SIZE
)paren
id|n
op_assign
id|USB_DT_ENDPOINT_SIZE
suffix:semicolon
r_else
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d interface %d altsetting %d has an &quot;
l_string|&quot;invalid endpoint descriptor of length %d, skipping&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|asnum
comma
id|d-&gt;bLength
)paren
suffix:semicolon
r_goto
id|skip_to_next_endpoint_or_interface_descriptor
suffix:semicolon
)brace
id|i
op_assign
id|d-&gt;bEndpointAddress
op_amp
op_complement
id|USB_ENDPOINT_DIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|16
op_logical_or
id|i
op_eq
l_int|0
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d interface %d altsetting %d has an &quot;
l_string|&quot;invalid endpoint with address 0x%X, skipping&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|asnum
comma
id|d-&gt;bEndpointAddress
)paren
suffix:semicolon
r_goto
id|skip_to_next_endpoint_or_interface_descriptor
suffix:semicolon
)brace
multiline_comment|/* Only store as many endpoints as we have room for */
r_if
c_cond
(paren
id|ifp-&gt;desc.bNumEndpoints
op_ge
id|num_ep
)paren
r_goto
id|skip_to_next_endpoint_or_interface_descriptor
suffix:semicolon
id|endpoint
op_assign
op_amp
id|ifp-&gt;endpoint
(braket
id|ifp-&gt;desc.bNumEndpoints
)braket
suffix:semicolon
op_increment
id|ifp-&gt;desc.bNumEndpoints
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|endpoint-&gt;desc
comma
id|d
comma
id|n
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|endpoint-&gt;urb_list
)paren
suffix:semicolon
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors;&n;&t; * find the next endpoint or interface descriptor */
id|endpoint-&gt;extra
op_assign
id|buffer
suffix:semicolon
id|i
op_assign
id|find_next_descriptor
c_func
(paren
id|buffer
comma
id|size
comma
id|USB_DT_ENDPOINT
comma
id|USB_DT_INTERFACE
comma
op_amp
id|n
)paren
suffix:semicolon
id|endpoint-&gt;extralen
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
id|dev_dbg
c_func
(paren
id|ddev
comma
l_string|&quot;skipped %d descriptor%s after %s&bslash;n&quot;
comma
id|n
comma
id|plural
c_func
(paren
id|n
)paren
comma
l_string|&quot;endpoint&quot;
)paren
suffix:semicolon
r_return
id|buffer
op_minus
id|buffer0
op_plus
id|i
suffix:semicolon
id|skip_to_next_endpoint_or_interface_descriptor
suffix:colon
id|i
op_assign
id|find_next_descriptor
c_func
(paren
id|buffer
comma
id|size
comma
id|USB_DT_ENDPOINT
comma
id|USB_DT_INTERFACE
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|buffer
op_minus
id|buffer0
op_plus
id|i
suffix:semicolon
)brace
DECL|function|usb_release_interface_cache
r_void
id|usb_release_interface_cache
c_func
(paren
r_struct
id|kref
op_star
id|ref
)paren
(brace
r_struct
id|usb_interface_cache
op_star
id|intfc
op_assign
id|ref_to_usb_interface_cache
c_func
(paren
id|ref
)paren
suffix:semicolon
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
id|intfc-&gt;num_altsetting
suffix:semicolon
id|j
op_increment
)paren
id|kfree
c_func
(paren
id|intfc-&gt;altsetting
(braket
id|j
)braket
dot
id|endpoint
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|intfc
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
id|device
op_star
id|ddev
comma
r_int
id|cfgno
comma
r_struct
id|usb_host_config
op_star
id|config
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|size
comma
id|u8
id|inums
(braket
)braket
comma
id|u8
id|nalts
(braket
)braket
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
id|usb_interface_descriptor
op_star
id|d
suffix:semicolon
r_int
id|inum
comma
id|asnum
suffix:semicolon
r_struct
id|usb_interface_cache
op_star
id|intfc
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|alt
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|len
comma
id|retval
suffix:semicolon
r_int
id|num_ep
comma
id|num_ep_orig
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
id|buffer
op_add_assign
id|d-&gt;bLength
suffix:semicolon
id|size
op_sub_assign
id|d-&gt;bLength
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bLength
OL
id|USB_DT_INTERFACE_SIZE
)paren
r_goto
id|skip_to_next_interface_descriptor
suffix:semicolon
multiline_comment|/* Which interface entry is this? */
id|intfc
op_assign
l_int|NULL
suffix:semicolon
id|inum
op_assign
id|d-&gt;bInterfaceNumber
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
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|inums
(braket
id|i
)braket
op_eq
id|inum
)paren
(brace
id|intfc
op_assign
id|config-&gt;intf_cache
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
id|intfc
op_logical_or
id|intfc-&gt;num_altsetting
op_ge
id|nalts
(braket
id|i
)braket
)paren
r_goto
id|skip_to_next_interface_descriptor
suffix:semicolon
multiline_comment|/* Check for duplicate altsetting entries */
id|asnum
op_assign
id|d-&gt;bAlternateSetting
suffix:semicolon
r_for
c_loop
(paren
(paren
id|i
op_assign
l_int|0
comma
id|alt
op_assign
op_amp
id|intfc-&gt;altsetting
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
OL
id|intfc-&gt;num_altsetting
suffix:semicolon
(paren
op_increment
id|i
comma
op_increment
id|alt
)paren
)paren
(brace
r_if
c_cond
(paren
id|alt-&gt;desc.bAlternateSetting
op_eq
id|asnum
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;Duplicate descriptor for config %d &quot;
l_string|&quot;interface %d altsetting %d, skipping&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|asnum
)paren
suffix:semicolon
r_goto
id|skip_to_next_interface_descriptor
suffix:semicolon
)brace
)brace
op_increment
id|intfc-&gt;num_altsetting
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|alt-&gt;desc
comma
id|d
comma
id|USB_DT_INTERFACE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors;&n;&t; * find the first endpoint or interface descriptor */
id|alt-&gt;extra
op_assign
id|buffer
suffix:semicolon
id|i
op_assign
id|find_next_descriptor
c_func
(paren
id|buffer
comma
id|size
comma
id|USB_DT_ENDPOINT
comma
id|USB_DT_INTERFACE
comma
op_amp
id|n
)paren
suffix:semicolon
id|alt-&gt;extralen
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
id|dev_dbg
c_func
(paren
id|ddev
comma
l_string|&quot;skipped %d descriptor%s after %s&bslash;n&quot;
comma
id|n
comma
id|plural
c_func
(paren
id|n
)paren
comma
l_string|&quot;interface&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|i
suffix:semicolon
multiline_comment|/* Allocate space for the right(?) number of endpoints */
id|num_ep
op_assign
id|num_ep_orig
op_assign
id|alt-&gt;desc.bNumEndpoints
suffix:semicolon
id|alt-&gt;desc.bNumEndpoints
op_assign
l_int|0
suffix:semicolon
singleline_comment|// Use as a counter
r_if
c_cond
(paren
id|num_ep
OG
id|USB_MAXENDPOINTS
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;too many endpoints for config %d interface %d &quot;
l_string|&quot;altsetting %d: %d, using maximum allowed: %d&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|asnum
comma
id|num_ep
comma
id|USB_MAXENDPOINTS
)paren
suffix:semicolon
id|num_ep
op_assign
id|USB_MAXENDPOINTS
suffix:semicolon
)brace
id|len
op_assign
r_sizeof
(paren
r_struct
id|usb_host_endpoint
)paren
op_star
id|num_ep
suffix:semicolon
id|alt-&gt;endpoint
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
id|alt-&gt;endpoint
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|alt-&gt;endpoint
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* Parse all the endpoint descriptors */
id|n
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
)paren
op_member_access_from_pointer
id|bDescriptorType
op_eq
id|USB_DT_INTERFACE
)paren
r_break
suffix:semicolon
id|retval
op_assign
id|usb_parse_endpoint
c_func
(paren
id|ddev
comma
id|cfgno
comma
id|inum
comma
id|asnum
comma
id|alt
comma
id|num_ep
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
op_increment
id|n
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
r_if
c_cond
(paren
id|n
op_ne
id|num_ep_orig
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d interface %d altsetting %d has %d &quot;
l_string|&quot;endpoint descriptor%s, different from the interface &quot;
l_string|&quot;descriptor&squot;s value: %d&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|asnum
comma
id|n
comma
id|plural
c_func
(paren
id|n
)paren
comma
id|num_ep_orig
)paren
suffix:semicolon
r_return
id|buffer
op_minus
id|buffer0
suffix:semicolon
id|skip_to_next_interface_descriptor
suffix:colon
id|i
op_assign
id|find_next_descriptor
c_func
(paren
id|buffer
comma
id|size
comma
id|USB_DT_INTERFACE
comma
id|USB_DT_INTERFACE
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|buffer
op_minus
id|buffer0
op_plus
id|i
suffix:semicolon
)brace
DECL|function|usb_parse_configuration
r_static
r_int
id|usb_parse_configuration
c_func
(paren
r_struct
id|device
op_star
id|ddev
comma
r_int
id|cfgidx
comma
r_struct
id|usb_host_config
op_star
id|config
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
id|cfgno
suffix:semicolon
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
id|n
suffix:semicolon
r_struct
id|usb_interface_cache
op_star
id|intfc
suffix:semicolon
r_int
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
id|len
comma
id|retval
suffix:semicolon
id|u8
id|inums
(braket
id|USB_MAXINTERFACES
)braket
comma
id|nalts
(braket
id|USB_MAXINTERFACES
)braket
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
r_if
c_cond
(paren
id|config-&gt;desc.bDescriptorType
op_ne
id|USB_DT_CONFIG
op_logical_or
id|config-&gt;desc.bLength
OL
id|USB_DT_CONFIG_SIZE
)paren
(brace
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;invalid descriptor for config index %d: &quot;
l_string|&quot;type = 0x%X, length = %d&bslash;n&quot;
comma
id|cfgidx
comma
id|config-&gt;desc.bDescriptorType
comma
id|config-&gt;desc.bLength
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cfgno
op_assign
id|config-&gt;desc.bConfigurationValue
suffix:semicolon
id|buffer
op_add_assign
id|config-&gt;desc.bLength
suffix:semicolon
id|size
op_sub_assign
id|config-&gt;desc.bLength
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
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has too many interfaces: %d, &quot;
l_string|&quot;using maximum allowed: %d&bslash;n&quot;
comma
id|cfgno
comma
id|nintf
comma
id|USB_MAXINTERFACES
)paren
suffix:semicolon
id|nintf
op_assign
id|USB_MAXINTERFACES
suffix:semicolon
)brace
multiline_comment|/* Go through the descriptors, checking their length and counting the&n;&t; * number of altsettings for each interface */
id|n
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
(paren
id|buffer2
op_assign
id|buffer
comma
id|size2
op_assign
id|size
)paren
suffix:semicolon
id|size2
OG
l_int|0
suffix:semicolon
(paren
id|buffer2
op_add_assign
id|header-&gt;bLength
comma
id|size2
op_sub_assign
id|header-&gt;bLength
)paren
)paren
(brace
r_if
c_cond
(paren
id|size2
OL
r_sizeof
(paren
r_struct
id|usb_descriptor_header
)paren
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d descriptor has %d excess &quot;
l_string|&quot;byte%s, ignoring&bslash;n&quot;
comma
id|cfgno
comma
id|size2
comma
id|plural
c_func
(paren
id|size2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has an invalid descriptor &quot;
l_string|&quot;of length %d, skipping remainder of the config&bslash;n&quot;
comma
id|cfgno
comma
id|header-&gt;bLength
)paren
suffix:semicolon
r_break
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
r_int
id|inum
suffix:semicolon
id|d
op_assign
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;bLength
OL
id|USB_DT_INTERFACE_SIZE
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has an invalid &quot;
l_string|&quot;interface descriptor of length %d, &quot;
l_string|&quot;skipping&bslash;n&quot;
comma
id|cfgno
comma
id|d-&gt;bLength
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|inum
op_assign
id|d-&gt;bInterfaceNumber
suffix:semicolon
r_if
c_cond
(paren
id|inum
op_ge
id|nintf_orig
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has an invalid &quot;
l_string|&quot;interface number: %d but max is %d&bslash;n&quot;
comma
id|cfgno
comma
id|inum
comma
id|nintf_orig
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Have we already encountered this interface?&n;&t;&t;&t; * Count its altsettings */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|inums
(braket
id|i
)braket
op_eq
id|inum
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|n
)paren
(brace
r_if
c_cond
(paren
id|nalts
(braket
id|i
)braket
OL
l_int|255
)paren
op_increment
id|nalts
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
OL
id|USB_MAXINTERFACES
)paren
(brace
id|inums
(braket
id|n
)braket
op_assign
id|inum
suffix:semicolon
id|nalts
(braket
id|n
)braket
op_assign
l_int|1
suffix:semicolon
op_increment
id|n
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_DEVICE
op_logical_or
id|header-&gt;bDescriptorType
op_eq
id|USB_DT_CONFIG
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d contains an unexpected &quot;
l_string|&quot;descriptor of type 0x%X, skipping&bslash;n&quot;
comma
id|cfgno
comma
id|header-&gt;bDescriptorType
)paren
suffix:semicolon
)brace
multiline_comment|/* for ((buffer2 = buffer, size2 = size); ...) */
id|size
op_assign
id|buffer2
op_minus
id|buffer
suffix:semicolon
id|config-&gt;desc.wTotalLength
op_assign
id|cpu_to_le16
c_func
(paren
id|buffer2
op_minus
id|buffer0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
id|nintf
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has %d interface%s, different from &quot;
l_string|&quot;the descriptor&squot;s value: %d&bslash;n&quot;
comma
id|cfgno
comma
id|n
comma
id|plural
c_func
(paren
id|n
)paren
comma
id|nintf_orig
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has no interfaces?&bslash;n&quot;
comma
id|cfgno
)paren
suffix:semicolon
id|config-&gt;desc.bNumInterfaces
op_assign
id|nintf
op_assign
id|n
suffix:semicolon
multiline_comment|/* Check for missing interface numbers */
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|nintf
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|inums
(braket
id|j
)braket
op_eq
id|i
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_ge
id|nintf
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d has no interface number &quot;
l_string|&quot;%d&bslash;n&quot;
comma
id|cfgno
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate the usb_interface_caches and altsetting arrays */
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
id|j
op_assign
id|nalts
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|j
OG
id|USB_MAXALTSETTING
)paren
(brace
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;too many alternate settings for &quot;
l_string|&quot;config %d interface %d: %d, &quot;
l_string|&quot;using maximum allowed: %d&bslash;n&quot;
comma
id|cfgno
comma
id|inums
(braket
id|i
)braket
comma
id|j
comma
id|USB_MAXALTSETTING
)paren
suffix:semicolon
id|nalts
(braket
id|i
)braket
op_assign
id|j
op_assign
id|USB_MAXALTSETTING
suffix:semicolon
)brace
id|len
op_assign
r_sizeof
(paren
op_star
id|intfc
)paren
op_plus
r_sizeof
(paren
r_struct
id|usb_host_interface
)paren
op_star
id|j
suffix:semicolon
id|config-&gt;intf_cache
(braket
id|i
)braket
op_assign
id|intfc
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
id|intfc
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|intfc
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|kref_init
c_func
(paren
op_amp
id|intfc-&gt;ref
)paren
suffix:semicolon
)brace
multiline_comment|/* Skip over any Class Specific or Vendor Specific descriptors;&n;&t; * find the first interface descriptor */
id|config-&gt;extra
op_assign
id|buffer
suffix:semicolon
id|i
op_assign
id|find_next_descriptor
c_func
(paren
id|buffer
comma
id|size
comma
id|USB_DT_INTERFACE
comma
id|USB_DT_INTERFACE
comma
op_amp
id|n
)paren
suffix:semicolon
id|config-&gt;extralen
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|0
)paren
id|dev_dbg
c_func
(paren
id|ddev
comma
l_string|&quot;skipped %d descriptor%s after %s&bslash;n&quot;
comma
id|n
comma
id|plural
c_func
(paren
id|n
)paren
comma
l_string|&quot;configuration&quot;
)paren
suffix:semicolon
id|buffer
op_add_assign
id|i
suffix:semicolon
id|size
op_sub_assign
id|i
suffix:semicolon
multiline_comment|/* Parse all the interface/altsetting descriptors */
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|retval
op_assign
id|usb_parse_interface
c_func
(paren
id|ddev
comma
id|cfgno
comma
id|config
comma
id|buffer
comma
id|size
comma
id|inums
comma
id|nalts
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
multiline_comment|/* Check for missing altsettings */
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
id|intfc
op_assign
id|config-&gt;intf_cache
(braket
id|i
)braket
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
id|intfc-&gt;num_altsetting
suffix:semicolon
op_increment
id|j
)paren
(brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|intfc-&gt;num_altsetting
suffix:semicolon
op_increment
id|n
)paren
(brace
r_if
c_cond
(paren
id|intfc-&gt;altsetting
(braket
id|n
)braket
dot
id|desc
dot
id|bAlternateSetting
op_eq
id|j
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_ge
id|intfc-&gt;num_altsetting
)paren
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config %d interface %d has no &quot;
l_string|&quot;altsetting %d&bslash;n&quot;
comma
id|cfgno
comma
id|inums
(braket
id|i
)braket
comma
id|j
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
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
id|dev-&gt;rawdescriptors
op_assign
l_int|NULL
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
id|kfree
c_func
(paren
id|cf-&gt;string
)paren
suffix:semicolon
id|cf-&gt;string
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
id|cf-&gt;desc.bNumInterfaces
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cf-&gt;intf_cache
(braket
id|i
)braket
)paren
id|kref_put
c_func
(paren
op_amp
id|cf-&gt;intf_cache
(braket
id|i
)braket
op_member_access_from_pointer
id|ref
comma
id|usb_release_interface_cache
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|dev-&gt;config
)paren
suffix:semicolon
id|dev-&gt;config
op_assign
l_int|NULL
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
r_struct
id|device
op_star
id|ddev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
r_int
id|ncfg
op_assign
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|ENOMEM
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
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;too many configurations: %d, &quot;
l_string|&quot;using maximum allowed: %d&bslash;n&quot;
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
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;no configurations&bslash;n&quot;
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
r_goto
id|err2
suffix:semicolon
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
r_goto
id|err2
suffix:semicolon
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
id|USB_DT_CONFIG_SIZE
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
r_goto
id|err2
suffix:semicolon
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
multiline_comment|/* We grab just the first descriptor so we know how long&n;&t;&t; * the whole configuration is */
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
id|USB_DT_CONFIG_SIZE
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
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;unable to read config index %d &quot;
l_string|&quot;descriptor/%s&bslash;n&quot;
comma
id|cfgno
comma
l_string|&quot;start&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OL
l_int|4
)paren
(brace
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;config index %d descriptor too short &quot;
l_string|&quot;(expected %i, got %i)&bslash;n&quot;
comma
id|cfgno
comma
id|USB_DT_CONFIG_SIZE
comma
id|result
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|length
op_assign
id|max
c_func
(paren
(paren
r_int
)paren
id|le16_to_cpu
c_func
(paren
id|desc-&gt;wTotalLength
)paren
comma
id|USB_DT_CONFIG_SIZE
)paren
suffix:semicolon
multiline_comment|/* Now that we know the length, get the whole thing */
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
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
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
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;unable to read config index %d &quot;
l_string|&quot;descriptor/%s&bslash;n&quot;
comma
id|cfgno
comma
l_string|&quot;all&quot;
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
id|dev_warn
c_func
(paren
id|ddev
comma
l_string|&quot;config index %d descriptor too short &quot;
l_string|&quot;(expected %i, got %i)&bslash;n&quot;
comma
id|cfgno
comma
id|length
comma
id|result
)paren
suffix:semicolon
id|length
op_assign
id|result
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
id|dev-&gt;dev
comma
id|cfgno
comma
op_amp
id|dev-&gt;config
(braket
id|cfgno
)braket
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
op_increment
id|cfgno
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
)brace
id|result
op_assign
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
id|err2
suffix:colon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOMEM
)paren
id|dev_err
c_func
(paren
id|ddev
comma
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
eof
