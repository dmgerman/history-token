multiline_comment|/*&n; * Driver for ST5481 USB ISDN modem&n; *&n; * Author       Frode Isaksen&n; * Copyright    2001 by Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/* &n; * TODO:&n; *&n; * b layer1 delay?&n; * hdlc as module&n; * hotplug / unregister issues&n; * mod_inc/dec_use_count&n; * unify parts of d/b channel usb handling&n; * file header&n; * avoid copy to isoc buffer?&n; * improve usb delay?&n; * merge l1 state machines?&n; * clean up debug&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;st5481.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISDN4Linux: driver for ST5481 USB ISDN adapter&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frode Isaksen&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|protocol
r_static
r_int
id|protocol
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* EURO-ISDN Default */
id|MODULE_PARM
c_func
(paren
id|protocol
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|number_of_leds
r_static
r_int
id|number_of_leds
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* 2 LEDs on the adpater default */
id|MODULE_PARM
c_func
(paren
id|number_of_leds
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HISAX_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0x1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|st5481_debug
r_int
id|st5481_debug
suffix:semicolon
macro_line|#endif
r_static
id|LIST_HEAD
c_func
(paren
id|adapter_list
)paren
suffix:semicolon
multiline_comment|/* ======================================================================&n; * registration/deregistration with the USB layer&n; */
multiline_comment|/*&n; * This function will be called when the adapter is plugged&n; * into the USB bus.&n; */
DECL|function|probe_st5481
r_static
r_void
op_star
id|__devinit
id|probe_st5481
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
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
id|st5481_adapter
op_star
id|adapter
suffix:semicolon
r_struct
id|hisax_b_if
op_star
id|b_if
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|retval
comma
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;st541: found adapter VendorId %04x, ProductId %04x, LEDs %d&bslash;n&quot;
comma
id|dev-&gt;descriptor.idVendor
comma
id|dev-&gt;descriptor.idProduct
comma
id|number_of_leds
)paren
suffix:semicolon
id|adapter
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|st5481_adapter
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|adapter
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|st5481_adapter
)paren
)paren
suffix:semicolon
id|adapter-&gt;number_of_leds
op_assign
id|number_of_leds
suffix:semicolon
id|adapter-&gt;usb_dev
op_assign
id|dev
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
op_amp
id|adapter-&gt;hisax_d_if
)paren
suffix:semicolon
id|adapter-&gt;hisax_d_if.ifc.priv
op_assign
id|adapter
suffix:semicolon
id|adapter-&gt;hisax_d_if.ifc.l2l1
op_assign
id|st5481_d_l2l1
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|adapter-&gt;bcs
(braket
id|i
)braket
dot
id|adapter
op_assign
id|adapter
suffix:semicolon
id|adapter-&gt;bcs
(braket
id|i
)braket
dot
id|channel
op_assign
id|i
suffix:semicolon
id|adapter-&gt;bcs
(braket
id|i
)braket
dot
id|b_if.ifc.priv
op_assign
op_amp
id|adapter-&gt;bcs
(braket
id|i
)braket
suffix:semicolon
id|adapter-&gt;bcs
(braket
id|i
)braket
dot
id|b_if.ifc.l2l1
op_assign
id|st5481_b_l2l1
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
id|adapter-&gt;list
comma
op_amp
id|adapter_list
)paren
suffix:semicolon
id|retval
op_assign
id|st5481_setup_usb
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
id|retval
op_assign
id|st5481_setup_d
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err_usb
suffix:semicolon
id|retval
op_assign
id|st5481_setup_b
c_func
(paren
op_amp
id|adapter-&gt;bcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err_d
suffix:semicolon
id|retval
op_assign
id|st5481_setup_b
c_func
(paren
op_amp
id|adapter-&gt;bcs
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err_b
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|b_if
(braket
id|i
)braket
op_assign
op_amp
id|adapter-&gt;bcs
(braket
id|i
)braket
dot
id|b_if
suffix:semicolon
id|hisax_register
c_func
(paren
op_amp
id|adapter-&gt;hisax_d_if
comma
id|b_if
comma
l_string|&quot;st5481_usb&quot;
comma
id|protocol
)paren
suffix:semicolon
id|st5481_start
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
id|adapter
suffix:semicolon
id|err_b
suffix:colon
id|st5481_release_b
c_func
(paren
op_amp
id|adapter-&gt;bcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|err_d
suffix:colon
id|st5481_release_d
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|err_usb
suffix:colon
id|st5481_release_usb
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|err
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * This function will be called when the adapter is removed&n; * from the USB bus.&n; */
DECL|function|disconnect_st5481
r_static
r_void
id|__devexit
id|disconnect_st5481
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|st5481_adapter
op_star
id|adapter
op_assign
id|arg
suffix:semicolon
id|DBG
c_func
(paren
l_int|1
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|adapter-&gt;list
)paren
suffix:semicolon
id|st5481_stop
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|st5481_release_b
c_func
(paren
op_amp
id|adapter-&gt;bcs
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|st5481_release_b
c_func
(paren
op_amp
id|adapter-&gt;bcs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|st5481_release_d
c_func
(paren
id|adapter
)paren
suffix:semicolon
singleline_comment|// we would actually better wait for completion of outstanding urbs
id|mdelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|st5481_release_usb
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|hisax_unregister
c_func
(paren
op_amp
id|adapter-&gt;hisax_d_if
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The last 4 bits in the Product Id is set with 4 pins on the chip.&n; */
DECL|variable|st5481_ids
r_static
r_struct
id|usb_device_id
id|st5481_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x0
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x1
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x2
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x3
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x4
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x5
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x6
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x7
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x8
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0x9
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xA
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xB
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xC
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xD
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xE
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|ST_VENDOR_ID
comma
id|ST5481_PRODUCT_ID
op_plus
l_int|0xF
)paren
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|st5481_ids
)paren
suffix:semicolon
DECL|variable|st5481_usb_driver
r_static
r_struct
id|usb_driver
id|st5481_usb_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;st5481_usb&quot;
comma
dot
id|probe
op_assign
id|probe_st5481
comma
dot
id|disconnect
op_assign
id|__devexit_p
c_func
(paren
id|disconnect_st5481
)paren
comma
dot
id|id_table
op_assign
id|st5481_ids
comma
)brace
suffix:semicolon
DECL|function|st5481_usb_init
r_static
r_int
id|__init
id|st5481_usb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
macro_line|#ifdef CONFIG_HISAX_DEBUG
id|st5481_debug
op_assign
id|debug
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hiax_st5481: ST5481 USB ISDN driver v0.1.0&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|st5481_d_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|st5481_usb_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|out_d_exit
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_d_exit
suffix:colon
id|st5481_d_exit
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|st5481_usb_exit
r_static
r_void
id|__exit
id|st5481_usb_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|st5481_usb_driver
)paren
suffix:semicolon
)brace
DECL|variable|st5481_usb_init
id|module_init
c_func
(paren
id|st5481_usb_init
)paren
suffix:semicolon
DECL|variable|st5481_usb_exit
id|module_exit
c_func
(paren
id|st5481_usb_exit
)paren
suffix:semicolon
eof
