multiline_comment|/*&n; *&t;Generic i2c interface for linux&n; *&n; *&t;(c) 1998 Gerd Knorr &lt;kraxel@cs.tu-berlin.de&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
DECL|macro|REGPRINT
mdefine_line|#define REGPRINT(x)   if (verbose)   (x)
DECL|macro|I2C_DEBUG
mdefine_line|#define I2C_DEBUG(x)  if (i2c_debug) (x)
DECL|variable|scan
r_static
r_int
id|scan
op_assign
l_int|0
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
DECL|variable|i2c_debug
r_static
r_int
id|i2c_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020117
id|MODULE_PARM
c_func
(paren
id|scan
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|verbose
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i2c_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|busses
r_static
r_struct
id|i2c_bus
op_star
id|busses
(braket
id|I2C_BUS_MAX
)braket
suffix:semicolon
DECL|variable|drivers
r_static
r_struct
id|i2c_driver
op_star
id|drivers
(braket
id|I2C_DRIVER_MAX
)braket
suffix:semicolon
DECL|variable|bus_count
DECL|variable|driver_count
r_static
r_int
id|bus_count
op_assign
l_int|0
comma
id|driver_count
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_VIDEO_BUZ
r_extern
r_int
id|saa7111_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|saa7185_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_LML33
r_extern
r_int
id|bt819_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|bt856_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|i2c_init
r_int
id|i2c_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c: initialized%s&bslash;n&quot;
comma
id|scan
ques
c_cond
l_string|&quot; (i2c bus scan enabled)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* anything to do here ? */
macro_line|#ifdef CONFIG_VIDEO_BUZ
id|saa7111_init
c_func
(paren
)paren
suffix:semicolon
id|saa7185_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_LML33
id|bt819_init
c_func
(paren
)paren
suffix:semicolon
id|bt856_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|i2c_attach_device
r_static
r_void
id|i2c_attach_device
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_struct
id|i2c_driver
op_star
id|driver
)paren
(brace
r_struct
id|i2c_device
op_star
id|device
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|ack
op_assign
l_int|1
suffix:semicolon
r_int
r_char
id|addr
suffix:semicolon
id|LOCK_FLAGS
suffix:semicolon
multiline_comment|/* probe for device */
id|LOCK_I2C_BUS
c_func
(paren
id|bus
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|driver-&gt;addr_l
suffix:semicolon
id|addr
op_le
id|driver-&gt;addr_h
suffix:semicolon
id|addr
op_add_assign
l_int|2
)paren
(brace
id|i2c_start
c_func
(paren
id|bus
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|addr
comma
l_int|0
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ack
)paren
r_break
suffix:semicolon
)brace
id|UNLOCK_I2C_BUS
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack
)paren
r_return
suffix:semicolon
multiline_comment|/* got answer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|driver-&gt;devices
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DEVICE_MAX
op_eq
id|i
)paren
r_return
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
id|I2C_DEVICE_MAX
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|bus-&gt;devices
(braket
id|j
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DEVICE_MAX
op_eq
id|j
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
(paren
id|device
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_device
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|device-&gt;bus
op_assign
id|bus
suffix:semicolon
id|device-&gt;driver
op_assign
id|driver
suffix:semicolon
id|device-&gt;addr
op_assign
id|addr
suffix:semicolon
multiline_comment|/* Attach */
r_if
c_cond
(paren
id|driver
op_member_access_from_pointer
id|attach
c_func
(paren
id|device
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|driver-&gt;devices
(braket
id|i
)braket
op_assign
id|device
suffix:semicolon
id|driver-&gt;devcount
op_increment
suffix:semicolon
id|bus-&gt;devices
(braket
id|j
)braket
op_assign
id|device
suffix:semicolon
id|bus-&gt;devcount
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;attach_inform
)paren
id|bus
op_member_access_from_pointer
id|attach_inform
c_func
(paren
id|bus
comma
id|driver-&gt;id
)paren
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: device attached: %s (addr=0x%02x, bus=%s, driver=%s)&bslash;n&quot;
comma
id|device-&gt;name
comma
id|addr
comma
id|bus-&gt;name
comma
id|driver-&gt;name
)paren
)paren
suffix:semicolon
)brace
DECL|function|i2c_detach_device
r_static
r_void
id|i2c_detach_device
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;bus-&gt;detach_inform
)paren
id|device-&gt;bus
op_member_access_from_pointer
id|detach_inform
c_func
(paren
id|device-&gt;bus
comma
id|device-&gt;driver-&gt;id
)paren
suffix:semicolon
id|device-&gt;driver
op_member_access_from_pointer
id|detach
c_func
(paren
id|device
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
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|device
op_eq
id|device-&gt;driver-&gt;devices
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DEVICE_MAX
op_eq
id|i
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c: detach_device #1: device not found: %s&bslash;n&quot;
comma
id|device-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|device-&gt;driver-&gt;devices
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|device-&gt;driver-&gt;devcount
op_decrement
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
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|device
op_eq
id|device-&gt;bus-&gt;devices
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DEVICE_MAX
op_eq
id|i
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c: detach_device #2: device not found: %s&bslash;n&quot;
comma
id|device-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|device-&gt;bus-&gt;devices
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|device-&gt;bus-&gt;devcount
op_decrement
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: device detached: %s (addr=0x%02x, bus=%s, driver=%s)&bslash;n&quot;
comma
id|device-&gt;name
comma
id|device-&gt;addr
comma
id|device-&gt;bus-&gt;name
comma
id|device-&gt;driver-&gt;name
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|i2c_register_bus
r_int
id|i2c_register_bus
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
r_int
id|i
comma
id|ack
suffix:semicolon
id|LOCK_FLAGS
suffix:semicolon
id|memset
c_func
(paren
id|bus-&gt;devices
comma
l_int|0
comma
r_sizeof
(paren
id|bus-&gt;devices
)paren
)paren
suffix:semicolon
id|bus-&gt;devcount
op_assign
l_int|0
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
id|I2C_BUS_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|busses
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_BUS_MAX
op_eq
id|i
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|busses
(braket
id|i
)braket
op_assign
id|bus
suffix:semicolon
id|bus_count
op_increment
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: bus registered: %s&bslash;n&quot;
comma
id|bus-&gt;name
)paren
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|scan
)paren
(brace
multiline_comment|/* scan whole i2c bus */
id|LOCK_I2C_BUS
c_func
(paren
id|bus
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
l_int|256
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|i2c_start
c_func
(paren
id|bus
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|i
comma
l_int|0
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ack
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c: scanning bus %s: found device at addr=0x%02x&bslash;n&quot;
comma
id|bus-&gt;name
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|UNLOCK_I2C_BUS
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
multiline_comment|/* probe available drivers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|I2C_DRIVER_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|drivers
(braket
id|i
)braket
)paren
id|i2c_attach_device
c_func
(paren
id|bus
comma
id|drivers
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_unregister_bus
r_int
id|i2c_unregister_bus
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* detach devices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bus-&gt;devices
(braket
id|i
)braket
)paren
id|i2c_detach_device
c_func
(paren
id|bus-&gt;devices
(braket
id|i
)braket
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
id|I2C_BUS_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bus
op_eq
id|busses
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_BUS_MAX
op_eq
id|i
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c: unregister_bus #1: bus not found: %s&bslash;n&quot;
comma
id|bus-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|busses
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|bus_count
op_decrement
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: bus unregistered: %s&bslash;n&quot;
comma
id|bus-&gt;name
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|i2c_register_driver
r_int
id|i2c_register_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
id|driver
)paren
(brace
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
id|driver-&gt;devices
comma
l_int|0
comma
r_sizeof
(paren
id|driver-&gt;devices
)paren
)paren
suffix:semicolon
id|driver-&gt;devcount
op_assign
l_int|0
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
id|I2C_DRIVER_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|drivers
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DRIVER_MAX
op_eq
id|i
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|drivers
(braket
id|i
)braket
op_assign
id|driver
suffix:semicolon
id|driver_count
op_increment
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: driver registered: %s&bslash;n&quot;
comma
id|driver-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* Probe available busses */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|I2C_BUS_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|busses
(braket
id|i
)braket
)paren
id|i2c_attach_device
c_func
(paren
id|busses
(braket
id|i
)braket
comma
id|driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_unregister_driver
r_int
id|i2c_unregister_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
id|driver
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* detach devices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|driver-&gt;devices
(braket
id|i
)braket
)paren
id|i2c_detach_device
c_func
(paren
id|driver-&gt;devices
(braket
id|i
)braket
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
id|I2C_DRIVER_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|driver
op_eq
id|drivers
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|I2C_DRIVER_MAX
op_eq
id|i
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c: unregister_driver: driver not found: %s&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|drivers
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|driver_count
op_decrement
suffix:semicolon
id|REGPRINT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c: driver unregistered: %s&bslash;n&quot;
comma
id|driver-&gt;name
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|i2c_control_device
r_int
id|i2c_control_device
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|id
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|i
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
id|I2C_DEVICE_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bus-&gt;devices
(braket
id|i
)braket
op_logical_and
id|bus-&gt;devices
(braket
id|i
)braket
op_member_access_from_pointer
id|driver-&gt;id
op_eq
id|id
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|I2C_DEVICE_MAX
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|bus-&gt;devices
(braket
id|i
)braket
op_member_access_from_pointer
id|driver-&gt;command
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|bus-&gt;devices
(braket
id|i
)braket
op_member_access_from_pointer
id|driver
op_member_access_from_pointer
id|command
c_func
(paren
id|bus-&gt;devices
(braket
id|i
)braket
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|macro|I2C_SET
mdefine_line|#define I2C_SET(bus,ctrl,data)  (bus-&gt;i2c_setlines(bus,ctrl,data))
DECL|macro|I2C_GET
mdefine_line|#define I2C_GET(bus)            (bus-&gt;i2c_getdataline(bus))
DECL|function|i2c_start
r_void
id|i2c_start
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|I2C_DEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s: &lt; &quot;
comma
id|bus-&gt;name
)paren
)paren
suffix:semicolon
)brace
DECL|function|i2c_stop
r_void
id|i2c_stop
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|I2C_DEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;&gt;&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|i2c_one
r_void
id|i2c_one
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|i2c_zero
r_void
id|i2c_zero
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|i2c_ack
r_int
id|i2c_ack
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
r_int
id|ack
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|ack
op_assign
id|I2C_GET
c_func
(paren
id|bus
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
DECL|function|i2c_sendbyte
r_int
id|i2c_sendbyte
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
r_char
id|data
comma
r_int
id|wait_for_ack
)paren
(brace
r_int
id|i
comma
id|ack
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(paren
id|data
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|i2c_one
c_func
(paren
id|bus
)paren
suffix:colon
id|i2c_zero
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_ack
)paren
id|udelay
c_func
(paren
id|wait_for_ack
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_ack
c_func
(paren
id|bus
)paren
suffix:semicolon
id|I2C_DEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%02x%c &quot;
comma
(paren
r_int
)paren
id|data
comma
id|ack
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
)paren
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
DECL|function|i2c_readbyte
r_int
r_char
id|i2c_readbyte
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|last
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|data
op_assign
l_int|0
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|I2C_GET
c_func
(paren
id|bus
)paren
)paren
id|data
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|I2C_SET
c_func
(paren
id|bus
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
id|last
ques
c_cond
id|i2c_one
c_func
(paren
id|bus
)paren
suffix:colon
id|i2c_zero
c_func
(paren
id|bus
)paren
suffix:semicolon
id|I2C_DEBUG
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;=%02x%c &quot;
comma
(paren
r_int
)paren
id|data
comma
id|last
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;+&squot;
)paren
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|i2c_read
r_int
id|i2c_read
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
r_char
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;i2c_read
)paren
r_return
id|bus
op_member_access_from_pointer
id|i2c_read
c_func
(paren
id|bus
comma
id|addr
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|addr
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|i2c_readbyte
c_func
(paren
id|bus
comma
l_int|1
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|i2c_write
r_int
id|i2c_write
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|data1
comma
r_int
r_char
id|data2
comma
r_int
id|both
)paren
(brace
r_int
id|ack
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;i2c_write
)paren
r_return
id|bus
op_member_access_from_pointer
id|i2c_write
c_func
(paren
id|bus
comma
id|addr
comma
id|data1
comma
id|data2
comma
id|both
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|addr
comma
l_int|0
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|data1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|both
)paren
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|bus
comma
id|data2
comma
l_int|0
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|ack
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
macro_line|#ifdef MODULE
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
DECL|variable|i2c_register_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_register_bus
)paren
suffix:semicolon
DECL|variable|i2c_unregister_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_unregister_bus
)paren
suffix:semicolon
DECL|variable|i2c_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_register_driver
)paren
suffix:semicolon
DECL|variable|i2c_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_unregister_driver
)paren
suffix:semicolon
DECL|variable|i2c_control_device
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_control_device
)paren
suffix:semicolon
DECL|variable|i2c_start
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_start
)paren
suffix:semicolon
DECL|variable|i2c_stop
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_stop
)paren
suffix:semicolon
DECL|variable|i2c_one
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_one
)paren
suffix:semicolon
DECL|variable|i2c_zero
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_zero
)paren
suffix:semicolon
DECL|variable|i2c_ack
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_ack
)paren
suffix:semicolon
DECL|variable|i2c_sendbyte
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_sendbyte
)paren
suffix:semicolon
DECL|variable|i2c_readbyte
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_readbyte
)paren
suffix:semicolon
DECL|variable|i2c_read
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_read
)paren
suffix:semicolon
DECL|variable|i2c_write
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_write
)paren
suffix:semicolon
macro_line|#endif
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
