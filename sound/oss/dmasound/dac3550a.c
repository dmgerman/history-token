multiline_comment|/*&n; * Driver for the i2c/i2s based DAC3550a sound chip used&n; * on some Apple iBooks. Also known as &quot;DACA&quot;.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;dmasound.h&quot;
multiline_comment|/* FYI: This code was derived from the tas3001c.c Texas/Tumbler mixer&n; * control code, as well as info derived from the AppleDACAAudio driver&n; * from Darwin CVS (main thing I derived being register numbers and &n; * values, as well as when to make the calls). */
DECL|macro|I2C_DRIVERID_DACA
mdefine_line|#define I2C_DRIVERID_DACA (0xFDCB)
DECL|macro|DACA_VERSION
mdefine_line|#define DACA_VERSION&t;&quot;0.1&quot;
DECL|macro|DACA_DATE
mdefine_line|#define DACA_DATE &quot;20010930&quot;
DECL|variable|cur_left_vol
r_static
r_int
id|cur_left_vol
suffix:semicolon
DECL|variable|cur_right_vol
r_static
r_int
id|cur_right_vol
suffix:semicolon
DECL|variable|daca_client
r_static
r_struct
id|i2c_client
op_star
id|daca_client
suffix:semicolon
r_static
r_int
id|daca_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_int
id|daca_detect_client
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|address
)paren
suffix:semicolon
r_static
r_int
id|daca_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/* Unique ID allocation */
DECL|variable|daca_id
r_static
r_int
id|daca_id
suffix:semicolon
DECL|struct|daca_data
r_struct
id|daca_data
(brace
DECL|member|arf
r_int
id|arf
suffix:semicolon
multiline_comment|/* place holder for furture use */
)brace
suffix:semicolon
DECL|variable|daca_driver
r_struct
id|i2c_driver
id|daca_driver
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
l_string|&quot;DAC3550A driver  V &quot;
id|DACA_VERSION
comma
dot
id|id
op_assign
id|I2C_DRIVERID_DACA
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|daca_attach_adapter
comma
dot
id|detach_client
op_assign
id|daca_detach_client
comma
)brace
suffix:semicolon
DECL|macro|VOL_MAX
mdefine_line|#define VOL_MAX ((1&lt;&lt;20) - 1)
DECL|function|daca_get_volume
r_void
id|daca_get_volume
c_func
(paren
id|uint
op_star
id|left_vol
comma
id|uint
op_star
id|right_vol
)paren
(brace
op_star
id|left_vol
op_assign
id|cur_left_vol
op_rshift
l_int|5
suffix:semicolon
op_star
id|right_vol
op_assign
id|cur_right_vol
op_rshift
l_int|5
suffix:semicolon
)brace
DECL|function|daca_set_volume
r_int
id|daca_set_volume
c_func
(paren
id|uint
id|left_vol
comma
id|uint
id|right_vol
)paren
(brace
r_int
r_int
id|voldata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|daca_client
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Derived from experience, not from any specific values */
id|left_vol
op_lshift_assign
l_int|5
suffix:semicolon
id|right_vol
op_lshift_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|left_vol
OG
id|VOL_MAX
)paren
id|left_vol
op_assign
id|VOL_MAX
suffix:semicolon
r_if
c_cond
(paren
id|right_vol
OG
id|VOL_MAX
)paren
id|right_vol
op_assign
id|VOL_MAX
suffix:semicolon
id|voldata
op_assign
(paren
(paren
id|left_vol
op_rshift
l_int|14
)paren
op_amp
l_int|0x3f
)paren
op_lshift
l_int|8
suffix:semicolon
id|voldata
op_or_assign
(paren
id|right_vol
op_rshift
l_int|14
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_write_word_data
c_func
(paren
id|daca_client
comma
l_int|2
comma
id|voldata
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;daca: failed to set volume &bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|cur_left_vol
op_assign
id|left_vol
suffix:semicolon
id|cur_right_vol
op_assign
id|right_vol
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_leave_sleep
r_int
id|daca_leave_sleep
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|daca_client
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Do a short sleep, just to make sure I2C bus is awake and paying&n;&t; * attention to us&n;&t; */
id|wait_ms
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Write the sample rate reg the value it needs */
id|i2c_smbus_write_byte_data
c_func
(paren
id|daca_client
comma
l_int|1
comma
l_int|8
)paren
suffix:semicolon
id|daca_set_volume
c_func
(paren
id|cur_left_vol
op_rshift
l_int|5
comma
id|cur_right_vol
op_rshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Another short delay, just to make sure the other I2C bus writes&n;&t; * have taken...&n;&t; */
id|wait_ms
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Write the global config reg - invert right power amp,&n;&t; * DAC on, use 5-volt mode */
id|i2c_smbus_write_byte_data
c_func
(paren
id|daca_client
comma
l_int|3
comma
l_int|0x45
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_enter_sleep
r_int
id|daca_enter_sleep
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|daca_client
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|daca_client
comma
l_int|1
comma
l_int|8
)paren
suffix:semicolon
id|daca_set_volume
c_func
(paren
id|cur_left_vol
op_rshift
l_int|5
comma
id|cur_right_vol
op_rshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Write the global config reg - invert right power amp,&n;&t; * DAC on, enter low-power mode, use 5-volt mode&n;&t; */
id|i2c_smbus_write_byte_data
c_func
(paren
id|daca_client
comma
l_int|3
comma
l_int|0x65
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_attach_adapter
r_static
r_int
id|daca_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|adapter-&gt;name
comma
l_string|&quot;mac-io&quot;
comma
l_int|6
)paren
)paren
id|daca_detect_client
c_func
(paren
id|adapter
comma
l_int|0x4d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_init_client
r_static
r_int
id|daca_init_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|new_client
)paren
(brace
multiline_comment|/* &n;&t; * Probe is not working with the current i2c-keywest&n;&t; * driver. We try to use addr 0x4d on each adapters&n;&t; * instead, by setting the format register.&n;&t; * &n;&t; * FIXME: I&squot;m sure that can be obtained from the&n;&t; * device-tree. --BenH.&n;&t; */
multiline_comment|/* Write the global config reg - invert right power amp,&n;&t; * DAC on, use 5-volt mode&n;&t; */
r_if
c_cond
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|new_client
comma
l_int|3
comma
l_int|0x45
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|new_client
comma
l_int|1
comma
l_int|8
)paren
suffix:semicolon
id|daca_client
op_assign
id|new_client
suffix:semicolon
id|daca_set_volume
c_func
(paren
l_int|15000
comma
l_int|15000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_detect_client
r_static
r_int
id|daca_detect_client
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|address
)paren
(brace
r_const
r_char
op_star
id|client_name
op_assign
l_string|&quot;DAC 3550A Digital Equalizer&quot;
suffix:semicolon
r_struct
id|i2c_client
op_star
id|new_client
suffix:semicolon
r_struct
id|daca_data
op_star
id|data
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|new_client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|new_client
)paren
op_plus
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_client
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|new_client-&gt;addr
op_assign
id|address
suffix:semicolon
id|new_client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|new_client-&gt;driver
op_assign
op_amp
id|daca_driver
suffix:semicolon
id|new_client-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|new_client-&gt;name
comma
id|client_name
)paren
suffix:semicolon
id|new_client-&gt;id
op_assign
id|daca_id
op_increment
suffix:semicolon
multiline_comment|/* racy... */
id|data
op_assign
(paren
r_struct
id|daca_data
op_star
)paren
(paren
id|new_client
op_plus
l_int|1
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|new_client-&gt;dev
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|daca_init_client
c_func
(paren
id|new_client
)paren
)paren
r_goto
id|bail
suffix:semicolon
multiline_comment|/* Tell the i2c layer a new client has arrived */
r_if
c_cond
(paren
id|i2c_attach_client
c_func
(paren
id|new_client
)paren
)paren
r_goto
id|bail
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bail
suffix:colon
id|kfree
c_func
(paren
id|new_client
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|daca_detach_client
r_static
r_int
id|daca_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_if
c_cond
(paren
id|client
op_eq
id|daca_client
)paren
id|daca_client
op_assign
l_int|NULL
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_cleanup
r_void
id|daca_cleanup
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|daca_driver
)paren
suffix:semicolon
)brace
DECL|function|daca_init
r_int
id|daca_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dac3550a driver version %s (%s)&bslash;n&quot;
comma
id|DACA_VERSION
comma
id|DACA_DATE
)paren
suffix:semicolon
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|daca_driver
)paren
suffix:semicolon
)brace
eof
