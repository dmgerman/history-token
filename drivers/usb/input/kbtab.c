macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * Version Information&n; * v0.0.1 - Original, extremely basic version, 2.4.xx only&n; * v0.0.2 - Updated, works with 2.5.62 and 2.4.20;&n; *           - added pressure-threshold modules param code from&n; *              Alex Perry &lt;alex.perry@ieee.org&gt;&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.0.2&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Josh Myer &lt;josh@joshisanerd.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB KB Gear JamStudio Tablet driver&quot;
DECL|macro|DRIVER_LICENSE
mdefine_line|#define DRIVER_LICENSE &quot;GPL&quot;
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
DECL|variable|DRIVER_LICENSE
id|MODULE_LICENSE
c_func
(paren
id|DRIVER_LICENSE
)paren
suffix:semicolon
DECL|macro|USB_VENDOR_ID_KBGEAR
mdefine_line|#define USB_VENDOR_ID_KBGEAR&t;0x084e
DECL|variable|kb_pressure_click
r_static
r_int
id|kb_pressure_click
op_assign
l_int|0x10
suffix:semicolon
id|MODULE_PARM
(paren
id|kb_pressure_click
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|kb_pressure_click
comma
l_string|&quot;pressure threshold for clicks&quot;
)paren
suffix:semicolon
DECL|struct|kbtab
r_struct
id|kbtab
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|data_dma
id|dma_addr_t
id|data_dma
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|irq
r_struct
id|urb
op_star
id|irq
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|x
DECL|member|y
r_int
id|x
comma
id|y
suffix:semicolon
DECL|member|button
r_int
id|button
suffix:semicolon
DECL|member|pressure
r_int
id|pressure
suffix:semicolon
DECL|member|serial
id|__u32
id|serial
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|kbtab_irq
r_static
r_void
id|kbtab_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|kbtab
op_star
id|kbtab
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|kbtab-&gt;data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|kbtab-&gt;dev
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|urb-&gt;status
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* success */
r_break
suffix:semicolon
r_case
op_minus
id|ECONNRESET
suffix:colon
r_case
op_minus
id|ENOENT
suffix:colon
r_case
op_minus
id|ESHUTDOWN
suffix:colon
multiline_comment|/* this urb is terminated, clean up */
id|dbg
c_func
(paren
l_string|&quot;%s - urb shutting down with status: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - nonzero urb status received: %d&quot;
comma
id|__FUNCTION__
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|kbtab-&gt;x
op_assign
id|le16_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|data
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|kbtab-&gt;y
op_assign
id|le16_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|data
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|kbtab-&gt;pressure
op_assign
(paren
id|data
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_PEN
comma
l_int|1
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|kbtab-&gt;x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|kbtab-&gt;y
)paren
suffix:semicolon
multiline_comment|/*input_report_key(dev, BTN_TOUCH , data[0] &amp; 0x01);*/
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
id|kb_pressure_click
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|kbtab-&gt;pressure
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
(paren
id|kbtab-&gt;pressure
OG
id|kb_pressure_click
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
m_exit
suffix:colon
id|retval
op_assign
id|usb_submit_urb
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|err
(paren
l_string|&quot;%s - usb_submit_urb failed with result %d&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
)brace
DECL|variable|kbtab_ids
r_static
r_struct
id|usb_device_id
id|kbtab_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_KBGEAR
comma
l_int|0x1001
)paren
comma
dot
id|driver_info
op_assign
l_int|0
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|kbtab_ids
)paren
suffix:semicolon
DECL|function|kbtab_open
r_static
r_int
id|kbtab_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|kbtab
op_star
id|kbtab
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|kbtab-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|kbtab-&gt;irq-&gt;dev
op_assign
id|kbtab-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|kbtab-&gt;irq
comma
id|GFP_KERNEL
)paren
)paren
(brace
id|kbtab-&gt;open
op_decrement
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbtab_close
r_static
r_void
id|kbtab_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|kbtab
op_star
id|kbtab
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|kbtab-&gt;open
)paren
id|usb_unlink_urb
c_func
(paren
id|kbtab-&gt;irq
)paren
suffix:semicolon
)brace
DECL|function|kbtab_probe
r_static
r_int
id|kbtab_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|kbtab
op_star
id|kbtab
suffix:semicolon
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|kbtab
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|kbtab
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|kbtab
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|kbtab
)paren
)paren
suffix:semicolon
id|kbtab-&gt;data
op_assign
id|usb_buffer_alloc
c_func
(paren
id|dev
comma
l_int|8
comma
id|GFP_KERNEL
comma
op_amp
id|kbtab-&gt;data_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbtab-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|kbtab
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kbtab-&gt;irq
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
id|kbtab-&gt;irq
)paren
(brace
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|10
comma
id|kbtab-&gt;data
comma
id|kbtab-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbtab
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|kbtab-&gt;dev.evbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
op_or
id|BIT
c_func
(paren
id|EV_MSC
)paren
suffix:semicolon
id|kbtab-&gt;dev.absbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
op_or
id|BIT
c_func
(paren
id|ABS_PRESSURE
)paren
suffix:semicolon
id|kbtab-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
suffix:semicolon
id|kbtab-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_DIGI
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOOL_PEN
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
id|kbtab-&gt;dev.mscbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|MSC_SERIAL
)paren
suffix:semicolon
id|kbtab-&gt;dev.absmax
(braket
id|ABS_X
)braket
op_assign
l_int|0x2000
suffix:semicolon
id|kbtab-&gt;dev.absmax
(braket
id|ABS_Y
)braket
op_assign
l_int|0x1750
suffix:semicolon
id|kbtab-&gt;dev.absmax
(braket
id|ABS_PRESSURE
)braket
op_assign
l_int|0xff
suffix:semicolon
id|kbtab-&gt;dev.absfuzz
(braket
id|ABS_X
)braket
op_assign
l_int|4
suffix:semicolon
id|kbtab-&gt;dev.absfuzz
(braket
id|ABS_Y
)braket
op_assign
l_int|4
suffix:semicolon
id|kbtab-&gt;dev
dot
r_private
op_assign
id|kbtab
suffix:semicolon
id|kbtab-&gt;dev.open
op_assign
id|kbtab_open
suffix:semicolon
id|kbtab-&gt;dev.close
op_assign
id|kbtab_close
suffix:semicolon
id|usb_make_path
c_func
(paren
id|dev
comma
id|path
comma
l_int|64
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|kbtab-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|kbtab-&gt;dev.name
op_assign
l_string|&quot;KB Gear Tablet&quot;
suffix:semicolon
id|kbtab-&gt;dev.phys
op_assign
id|kbtab-&gt;phys
suffix:semicolon
id|kbtab-&gt;dev.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|kbtab-&gt;dev.id.vendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|kbtab-&gt;dev.id.product
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|kbtab-&gt;dev.id.version
op_assign
id|dev-&gt;descriptor.bcdDevice
suffix:semicolon
id|kbtab-&gt;dev.dev
op_assign
op_amp
id|intf-&gt;dev
suffix:semicolon
id|kbtab-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|endpoint
op_assign
op_amp
id|intf-&gt;cur_altsetting-&gt;endpoint
(braket
l_int|0
)braket
dot
id|desc
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|kbtab-&gt;irq
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
id|kbtab-&gt;data
comma
l_int|8
comma
id|kbtab_irq
comma
id|kbtab
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|kbtab-&gt;irq-&gt;transfer_dma
op_assign
id|kbtab-&gt;data_dma
suffix:semicolon
id|kbtab-&gt;irq-&gt;transfer_flags
op_or_assign
id|URB_NO_TRANSFER_DMA_MAP
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|kbtab-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: KB Gear Tablet on %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|kbtab
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|kbtab_disconnect
r_static
r_void
id|kbtab_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|kbtab
op_star
id|kbtab
op_assign
id|usb_get_intfdata
(paren
id|intf
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbtab
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|kbtab-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|kbtab-&gt;dev
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|kbtab-&gt;irq
)paren
suffix:semicolon
id|usb_buffer_free
c_func
(paren
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
comma
l_int|10
comma
id|kbtab-&gt;data
comma
id|kbtab-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbtab
)paren
suffix:semicolon
)brace
)brace
DECL|variable|kbtab_driver
r_static
r_struct
id|usb_driver
id|kbtab_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;kbtab&quot;
comma
dot
id|probe
op_assign
id|kbtab_probe
comma
dot
id|disconnect
op_assign
id|kbtab_disconnect
comma
dot
id|id_table
op_assign
id|kbtab_ids
comma
)brace
suffix:semicolon
DECL|function|kbtab_init
r_static
r_int
id|__init
id|kbtab_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|kbtab_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|kbtab_exit
r_static
r_void
id|__exit
id|kbtab_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|kbtab_driver
)paren
suffix:semicolon
)brace
DECL|variable|kbtab_init
id|module_init
c_func
(paren
id|kbtab_init
)paren
suffix:semicolon
DECL|variable|kbtab_exit
id|module_exit
c_func
(paren
id|kbtab_exit
)paren
suffix:semicolon
eof
