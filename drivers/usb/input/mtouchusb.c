multiline_comment|/******************************************************************************&n; * mtouchusb.c  --  Driver for Microtouch (Now 3M) USB Touchscreens&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Based upon original work by Radoslaw Garbacz (usb-support@ite.pl)&n; *  (http://freshmeat.net/projects/3mtouchscreendriver)&n; *&n; * History&n; *&n; *  0.3 &amp; 0.4  2002 (TEJ) tejohnson@yahoo.com&n; *    Updated to 2.4.18, then 2.4.19&n; *    Old version still relied on stealing a minor&n; *&n; *  0.5  02/26/2004 (TEJ) tejohnson@yahoo.com&n; *    Complete rewrite using Linux Input in 2.6.3&n; *    Unfortunately no calibration support at this time&n; *&n; *  1.4 04/25/2004 (TEJ) tejohnson@yahoo.com&n; *    Changed reset from standard USB dev reset to vendor reset&n; *    Changed data sent to host from compensated to raw coordinates&n; *    Eliminated vendor/product module params&n; *    Performed multiple successfull tests with an EXII-5010UC&n; *&n; *  1.5 02/27/2005 ddstreet@ieee.org&n; *    Added module parameter to select raw or hw-calibrated coordinate reporting&n; *&n; *****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|MTOUCHUSB_MIN_XC
mdefine_line|#define MTOUCHUSB_MIN_XC                0x0
DECL|macro|MTOUCHUSB_MAX_RAW_XC
mdefine_line|#define MTOUCHUSB_MAX_RAW_XC            0x4000
DECL|macro|MTOUCHUSB_MAX_CALIB_XC
mdefine_line|#define MTOUCHUSB_MAX_CALIB_XC          0xffff
DECL|macro|MTOUCHUSB_XC_FUZZ
mdefine_line|#define MTOUCHUSB_XC_FUZZ               0x0
DECL|macro|MTOUCHUSB_XC_FLAT
mdefine_line|#define MTOUCHUSB_XC_FLAT               0x0
DECL|macro|MTOUCHUSB_MIN_YC
mdefine_line|#define MTOUCHUSB_MIN_YC                0x0
DECL|macro|MTOUCHUSB_MAX_RAW_YC
mdefine_line|#define MTOUCHUSB_MAX_RAW_YC            0x4000
DECL|macro|MTOUCHUSB_MAX_CALIB_YC
mdefine_line|#define MTOUCHUSB_MAX_CALIB_YC          0xffff
DECL|macro|MTOUCHUSB_YC_FUZZ
mdefine_line|#define MTOUCHUSB_YC_FUZZ               0x0
DECL|macro|MTOUCHUSB_YC_FLAT
mdefine_line|#define MTOUCHUSB_YC_FLAT               0x0
DECL|macro|MTOUCHUSB_ASYNC_REPORT
mdefine_line|#define MTOUCHUSB_ASYNC_REPORT          1
DECL|macro|MTOUCHUSB_RESET
mdefine_line|#define MTOUCHUSB_RESET                 7
DECL|macro|MTOUCHUSB_REPORT_DATA_SIZE
mdefine_line|#define MTOUCHUSB_REPORT_DATA_SIZE      11
DECL|macro|MTOUCHUSB_REQ_CTRLLR_ID
mdefine_line|#define MTOUCHUSB_REQ_CTRLLR_ID         10
DECL|macro|MTOUCHUSB_GET_RAW_XC
mdefine_line|#define MTOUCHUSB_GET_RAW_XC(data)      (data[8]&lt;&lt;8 | data[7])
DECL|macro|MTOUCHUSB_GET_CALIB_XC
mdefine_line|#define MTOUCHUSB_GET_CALIB_XC(data)    (data[4]&lt;&lt;8 | data[3])
DECL|macro|MTOUCHUSB_GET_RAW_YC
mdefine_line|#define MTOUCHUSB_GET_RAW_YC(data)      (data[10]&lt;&lt;8 | data[9])
DECL|macro|MTOUCHUSB_GET_CALIB_YC
mdefine_line|#define MTOUCHUSB_GET_CALIB_YC(data)    (data[6]&lt;&lt;8 | data[5])
DECL|macro|MTOUCHUSB_GET_XC
mdefine_line|#define MTOUCHUSB_GET_XC(data)          (raw_coordinates ? &bslash;&n;                                         MTOUCHUSB_GET_RAW_XC(data) : &bslash;&n;                                         MTOUCHUSB_GET_CALIB_XC(data))
DECL|macro|MTOUCHUSB_GET_YC
mdefine_line|#define MTOUCHUSB_GET_YC(data)          (raw_coordinates ? &bslash;&n;                                         MTOUCHUSB_GET_RAW_YC(data) : &bslash;&n;                                         MTOUCHUSB_GET_CALIB_YC(data))
DECL|macro|MTOUCHUSB_GET_TOUCHED
mdefine_line|#define MTOUCHUSB_GET_TOUCHED(data)     ((data[2] &amp; 0x40) ? 1:0)
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v1.5&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Todd E. Johnson, tejohnson@yahoo.com&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;3M USB Touchscreen Driver&quot;
DECL|macro|DRIVER_LICENSE
mdefine_line|#define DRIVER_LICENSE &quot;GPL&quot;
DECL|variable|raw_coordinates
r_static
r_int
id|raw_coordinates
op_assign
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|raw_coordinates
comma
r_bool
comma
id|S_IRUGO
op_or
id|S_IWUSR
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|raw_coordinates
comma
l_string|&quot;report raw coordinate values (y, default) or hardware-calibrated coordinate values (n)&quot;
)paren
suffix:semicolon
DECL|struct|mtouch_usb
r_struct
id|mtouch_usb
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
DECL|member|irq
r_struct
id|urb
op_star
id|irq
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
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|mtouchusb_devices
r_static
r_struct
id|usb_device_id
id|mtouchusb_devices
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0596
comma
l_int|0x0001
)paren
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|function|mtouchusb_irq
r_static
r_void
id|mtouchusb_irq
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
id|mtouch_usb
op_star
id|mtouch
op_assign
id|urb-&gt;context
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
id|ETIMEDOUT
suffix:colon
multiline_comment|/* this urb is timing out */
id|dbg
c_func
(paren
l_string|&quot;%s - urb timed out - was the device unplugged?&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
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
id|input_regs
c_func
(paren
op_amp
id|mtouch-&gt;input
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|mtouch-&gt;input
comma
id|BTN_TOUCH
comma
id|MTOUCHUSB_GET_TOUCHED
c_func
(paren
id|mtouch-&gt;data
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|mtouch-&gt;input
comma
id|ABS_X
comma
id|MTOUCHUSB_GET_XC
c_func
(paren
id|mtouch-&gt;data
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
op_amp
id|mtouch-&gt;input
comma
id|ABS_Y
comma
(paren
id|raw_coordinates
ques
c_cond
id|MTOUCHUSB_MAX_RAW_YC
suffix:colon
id|MTOUCHUSB_MAX_CALIB_YC
)paren
op_minus
id|MTOUCHUSB_GET_YC
c_func
(paren
id|mtouch-&gt;data
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|mtouch-&gt;input
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
l_string|&quot;%s - usb_submit_urb failed with result: %d&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
)brace
DECL|function|mtouchusb_open
r_static
r_int
id|mtouchusb_open
(paren
r_struct
id|input_dev
op_star
id|input
)paren
(brace
r_struct
id|mtouch_usb
op_star
id|mtouch
op_assign
id|input
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|mtouch-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|mtouch-&gt;irq-&gt;dev
op_assign
id|mtouch-&gt;udev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
(paren
id|mtouch-&gt;irq
comma
id|GFP_ATOMIC
)paren
)paren
(brace
id|mtouch-&gt;open
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
DECL|function|mtouchusb_close
r_static
r_void
id|mtouchusb_close
(paren
r_struct
id|input_dev
op_star
id|input
)paren
(brace
r_struct
id|mtouch_usb
op_star
id|mtouch
op_assign
id|input
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|mtouch-&gt;open
)paren
id|usb_kill_urb
(paren
id|mtouch-&gt;irq
)paren
suffix:semicolon
)brace
DECL|function|mtouchusb_alloc_buffers
r_static
r_int
id|mtouchusb_alloc_buffers
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_struct
id|mtouch_usb
op_star
id|mtouch
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|mtouch-&gt;data
op_assign
id|usb_buffer_alloc
c_func
(paren
id|udev
comma
id|MTOUCHUSB_REPORT_DATA_SIZE
comma
id|SLAB_ATOMIC
comma
op_amp
id|mtouch-&gt;data_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtouch-&gt;data
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mtouchusb_free_buffers
r_static
r_void
id|mtouchusb_free_buffers
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_struct
id|mtouch_usb
op_star
id|mtouch
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtouch-&gt;data
)paren
id|usb_buffer_free
c_func
(paren
id|udev
comma
id|MTOUCHUSB_REPORT_DATA_SIZE
comma
id|mtouch-&gt;data
comma
id|mtouch-&gt;data_dma
)paren
suffix:semicolon
)brace
DECL|function|mtouchusb_probe
r_static
r_int
id|mtouchusb_probe
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
id|mtouch_usb
op_star
id|mtouch
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
(paren
id|intf
)paren
suffix:semicolon
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|nRet
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - setting interface&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|interface
op_assign
id|intf-&gt;cur_altsetting
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - setting endpoint&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
l_int|0
)braket
dot
id|desc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mtouch
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|mtouch_usb
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s - Out of memory.&quot;
comma
id|__FUNCTION__
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
id|mtouch
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mtouch_usb
)paren
)paren
suffix:semicolon
id|mtouch-&gt;udev
op_assign
id|udev
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - allocating buffers&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtouchusb_alloc_buffers
c_func
(paren
id|udev
comma
id|mtouch
)paren
)paren
(brace
id|mtouchusb_free_buffers
c_func
(paren
id|udev
comma
id|mtouch
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtouch
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|mtouch-&gt;input
dot
r_private
op_assign
id|mtouch
suffix:semicolon
id|mtouch-&gt;input.open
op_assign
id|mtouchusb_open
suffix:semicolon
id|mtouch-&gt;input.close
op_assign
id|mtouchusb_close
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
id|sprintf
c_func
(paren
id|mtouch-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|mtouch-&gt;input.name
op_assign
id|mtouch-&gt;name
suffix:semicolon
id|mtouch-&gt;input.phys
op_assign
id|mtouch-&gt;phys
suffix:semicolon
id|mtouch-&gt;input.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|mtouch-&gt;input.id.vendor
op_assign
id|le16_to_cpu
c_func
(paren
id|udev-&gt;descriptor.idVendor
)paren
suffix:semicolon
id|mtouch-&gt;input.id.product
op_assign
id|le16_to_cpu
c_func
(paren
id|udev-&gt;descriptor.idProduct
)paren
suffix:semicolon
id|mtouch-&gt;input.id.version
op_assign
id|le16_to_cpu
c_func
(paren
id|udev-&gt;descriptor.bcdDevice
)paren
suffix:semicolon
id|mtouch-&gt;input.dev
op_assign
op_amp
id|intf-&gt;dev
suffix:semicolon
id|mtouch-&gt;input.evbit
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
id|EV_ABS
)paren
suffix:semicolon
id|mtouch-&gt;input.absbit
(braket
l_int|0
)braket
op_assign
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
suffix:semicolon
id|mtouch-&gt;input.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
multiline_comment|/* Used to Scale Compensated Data and Flip Y */
id|mtouch-&gt;input.absmin
(braket
id|ABS_X
)braket
op_assign
id|MTOUCHUSB_MIN_XC
suffix:semicolon
id|mtouch-&gt;input.absmax
(braket
id|ABS_X
)braket
op_assign
id|raw_coordinates
ques
c_cond
"&bslash;"
id|MTOUCHUSB_MAX_RAW_XC
suffix:colon
id|MTOUCHUSB_MAX_CALIB_XC
suffix:semicolon
id|mtouch-&gt;input.absfuzz
(braket
id|ABS_X
)braket
op_assign
id|MTOUCHUSB_XC_FUZZ
suffix:semicolon
id|mtouch-&gt;input.absflat
(braket
id|ABS_X
)braket
op_assign
id|MTOUCHUSB_XC_FLAT
suffix:semicolon
id|mtouch-&gt;input.absmin
(braket
id|ABS_Y
)braket
op_assign
id|MTOUCHUSB_MIN_YC
suffix:semicolon
id|mtouch-&gt;input.absmax
(braket
id|ABS_Y
)braket
op_assign
id|raw_coordinates
ques
c_cond
"&bslash;"
id|MTOUCHUSB_MAX_RAW_YC
suffix:colon
id|MTOUCHUSB_MAX_CALIB_YC
suffix:semicolon
id|mtouch-&gt;input.absfuzz
(braket
id|ABS_Y
)braket
op_assign
id|MTOUCHUSB_YC_FUZZ
suffix:semicolon
id|mtouch-&gt;input.absflat
(braket
id|ABS_Y
)braket
op_assign
id|MTOUCHUSB_YC_FLAT
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;manufacturer
)paren
id|strcat
c_func
(paren
id|mtouch-&gt;name
comma
id|udev-&gt;manufacturer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udev-&gt;product
)paren
id|sprintf
c_func
(paren
id|mtouch-&gt;name
comma
l_string|&quot;%s %s&quot;
comma
id|mtouch-&gt;name
comma
id|udev-&gt;product
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strlen
c_func
(paren
id|mtouch-&gt;name
)paren
)paren
id|sprintf
c_func
(paren
id|mtouch-&gt;name
comma
l_string|&quot;USB Touchscreen %04x:%04x&quot;
comma
id|mtouch-&gt;input.id.vendor
comma
id|mtouch-&gt;input.id.product
)paren
suffix:semicolon
id|nRet
op_assign
id|usb_control_msg
c_func
(paren
id|mtouch-&gt;udev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|udev
comma
l_int|0
)paren
comma
id|MTOUCHUSB_RESET
comma
id|USB_DIR_OUT
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
comma
l_int|1
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|USB_CTRL_SET_TIMEOUT
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - usb_control_msg - MTOUCHUSB_RESET - bytes|err: %d&quot;
comma
id|__FUNCTION__
comma
id|nRet
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - usb_alloc_urb: mtouch-&gt;irq&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|mtouch-&gt;irq
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
id|mtouch-&gt;irq
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - usb_alloc_urb failed: mtouch-&gt;irq&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|mtouchusb_free_buffers
c_func
(paren
id|udev
comma
id|mtouch
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtouch
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s - usb_fill_int_urb&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|mtouch-&gt;irq
comma
id|mtouch-&gt;udev
comma
id|usb_rcvintpipe
c_func
(paren
id|mtouch-&gt;udev
comma
l_int|0x81
)paren
comma
id|mtouch-&gt;data
comma
id|MTOUCHUSB_REPORT_DATA_SIZE
comma
id|mtouchusb_irq
comma
id|mtouch
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - input_register_device&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|mtouch-&gt;input
)paren
suffix:semicolon
id|nRet
op_assign
id|usb_control_msg
c_func
(paren
id|mtouch-&gt;udev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|udev
comma
l_int|0
)paren
comma
id|MTOUCHUSB_ASYNC_REPORT
comma
id|USB_DIR_OUT
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_int|0
comma
id|USB_CTRL_SET_TIMEOUT
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - usb_control_msg - MTOUCHUSB_ASYNC_REPORT - bytes|err: %d&quot;
comma
id|__FUNCTION__
comma
id|nRet
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|mtouch-&gt;name
comma
id|path
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|mtouch
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mtouchusb_disconnect
r_static
r_void
id|mtouchusb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|mtouch_usb
op_star
id|mtouch
op_assign
id|usb_get_intfdata
(paren
id|intf
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
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
id|mtouch
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - mtouch is initialized, cleaning up&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|mtouch-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|mtouch-&gt;input
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|mtouch-&gt;irq
)paren
suffix:semicolon
id|mtouchusb_free_buffers
c_func
(paren
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
comma
id|mtouch
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mtouch
)paren
suffix:semicolon
)brace
)brace
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|mtouchusb_devices
)paren
suffix:semicolon
DECL|variable|mtouchusb_driver
r_static
r_struct
id|usb_driver
id|mtouchusb_driver
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
l_string|&quot;mtouchusb&quot;
comma
dot
id|probe
op_assign
id|mtouchusb_probe
comma
dot
id|disconnect
op_assign
id|mtouchusb_disconnect
comma
dot
id|id_table
op_assign
id|mtouchusb_devices
comma
)brace
suffix:semicolon
DECL|function|mtouchusb_init
r_static
r_int
id|__init
id|mtouchusb_init
c_func
(paren
r_void
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|usb_register
c_func
(paren
op_amp
id|mtouchusb_driver
)paren
suffix:semicolon
)brace
DECL|function|mtouchusb_cleanup
r_static
r_void
id|__exit
id|mtouchusb_cleanup
c_func
(paren
r_void
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - called&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|mtouchusb_driver
)paren
suffix:semicolon
)brace
DECL|variable|mtouchusb_init
id|module_init
c_func
(paren
id|mtouchusb_init
)paren
suffix:semicolon
DECL|variable|mtouchusb_cleanup
id|module_exit
c_func
(paren
id|mtouchusb_cleanup
)paren
suffix:semicolon
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
