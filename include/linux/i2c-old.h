macro_line|#ifndef I2C_H
DECL|macro|I2C_H
mdefine_line|#define I2C_H
multiline_comment|/*&n; * linux i2c interface.  Works a little bit like the scsi subsystem.&n; * There are:&n; *&n; *     i2c          the basic control module        (like scsi_mod)&n; *     bus driver   a driver with a i2c bus         (hostadapter driver)&n; *     chip driver  a driver for a chip connected&n; *                  to a i2c bus                    (cdrom/hd driver)&n; *&n; * A device will be attached to one bus and one chip driver.  Every chip&n; * driver gets a unique ID.&n; *&n; * A chip driver can provide a ioctl-like callback for the&n; * communication with other parts of the kernel (not every i2c chip is&n; * useful without other devices, a TV card tuner for example). &n; *&n; * &quot;i2c internal&quot; parts of the structs: only the i2c module is allowed to&n; * write to them, for others they are read-only.&n; *&n; */
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|I2C_BUS_MAX
mdefine_line|#define I2C_BUS_MAX       4    /* max # of bus drivers  */
DECL|macro|I2C_DRIVER_MAX
mdefine_line|#define I2C_DRIVER_MAX    8    /* max # of chip drivers */
DECL|macro|I2C_DEVICE_MAX
mdefine_line|#define I2C_DEVICE_MAX    8    /* max # if devices per bus/driver */
r_struct
id|i2c_bus
suffix:semicolon
r_struct
id|i2c_driver
suffix:semicolon
r_struct
id|i2c_device
suffix:semicolon
DECL|macro|I2C_DRIVERID_MSP3400
mdefine_line|#define I2C_DRIVERID_MSP3400    &t; 1
DECL|macro|I2C_DRIVERID_TUNER
mdefine_line|#define I2C_DRIVERID_TUNER      &t; 2
DECL|macro|I2C_DRIVERID_VIDEOTEXT
mdefine_line|#define I2C_DRIVERID_VIDEOTEXT&t;&t; 3
DECL|macro|I2C_DRIVERID_VIDEODECODER
mdefine_line|#define I2C_DRIVERID_VIDEODECODER&t; 4
DECL|macro|I2C_DRIVERID_VIDEOENCODER
mdefine_line|#define I2C_DRIVERID_VIDEOENCODER&t; 5
DECL|macro|I2C_BUSID_BT848
mdefine_line|#define I2C_BUSID_BT848&t;&t;1&t;/* I2C bus on a BT848 */
DECL|macro|I2C_BUSID_PARPORT
mdefine_line|#define I2C_BUSID_PARPORT&t;2&t;/* Bit banging on a parallel port */
DECL|macro|I2C_BUSID_BUZ
mdefine_line|#define I2C_BUSID_BUZ&t;&t;3
DECL|macro|I2C_BUSID_ZORAN
mdefine_line|#define I2C_BUSID_ZORAN&t;&t;4
DECL|macro|I2C_BUSID_CYBER2000
mdefine_line|#define I2C_BUSID_CYBER2000&t;5
multiline_comment|/*&n; * struct for a driver for a i2c chip (tuner, soundprocessor,&n; * videotext, ... ).&n; *&n; * a driver will register within the i2c module.  The i2c module will&n; * callback the driver (i2c_attach) for every device it finds on a i2c&n; * bus at the specified address.  If the driver decides to &quot;accept&quot;&n; * the, device, it must return a struct i2c_device, and NULL&n; * otherwise.&n; *&n; * i2c_detach = i2c_attach ** -1&n; * &n; * i2c_command will be used to pass commands to the driver in a&n; * ioctl-line manner.&n; *&n; */
DECL|struct|i2c_driver
r_struct
id|i2c_driver
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful label         */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* device type ID            */
DECL|member|addr_l
DECL|member|addr_h
r_int
r_char
id|addr_l
comma
id|addr_h
suffix:semicolon
multiline_comment|/* address range of the chip */
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
suffix:semicolon
DECL|member|detach
r_int
(paren
op_star
id|detach
)paren
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
suffix:semicolon
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_struct
id|i2c_device
op_star
id|device
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* i2c internal */
DECL|member|devices
r_struct
id|i2c_device
op_star
id|devices
(braket
id|I2C_DEVICE_MAX
)braket
suffix:semicolon
DECL|member|devcount
r_int
id|devcount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * this holds the informations about a i2c bus available in the system.&n; * &n; * a chip with a i2c bus interface (like bt848) registers the bus within&n; * the i2c module. This struct provides functions to access the i2c bus.&n; * &n; * One must hold the spinlock to access the i2c bus (XXX: is the irqsave&n; * required? Maybe better use a semaphore?). &n; * [-AC-] having a spinlock_irqsave is only needed if we have drivers wishing&n; *&t;  to bang their i2c bus from an interrupt.&n; * &n; * attach/detach_inform is a callback to inform the bus driver about&n; * attached chip drivers.&n; *&n; */
multiline_comment|/* needed: unsigned long flags */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
macro_line|# if 0
macro_line|#  define LOCK_FLAGS unsigned long flags;
macro_line|#  define LOCK_I2C_BUS(bus)    spin_lock_irqsave(&amp;(bus-&gt;bus_lock),flags);
macro_line|#  define UNLOCK_I2C_BUS(bus)  spin_unlock_irqrestore(&amp;(bus-&gt;bus_lock),flags);
macro_line|# else
DECL|macro|LOCK_FLAGS
macro_line|#  define LOCK_FLAGS
DECL|macro|LOCK_I2C_BUS
macro_line|#  define LOCK_I2C_BUS(bus)    spin_lock(&amp;(bus-&gt;bus_lock));
DECL|macro|UNLOCK_I2C_BUS
macro_line|#  define UNLOCK_I2C_BUS(bus)  spin_unlock(&amp;(bus-&gt;bus_lock));
macro_line|# endif
macro_line|#else
DECL|macro|LOCK_FLAGS
macro_line|# define LOCK_FLAGS unsigned long flags;
DECL|macro|LOCK_I2C_BUS
macro_line|# define LOCK_I2C_BUS(bus)    { save_flags(flags); cli(); }
DECL|macro|UNLOCK_I2C_BUS
macro_line|# define UNLOCK_I2C_BUS(bus)  { restore_flags(flags);     }
macro_line|#endif
DECL|struct|i2c_bus
r_struct
id|i2c_bus
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful label */
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* free for use by the bus driver */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
DECL|member|bus_lock
id|spinlock_t
id|bus_lock
suffix:semicolon
macro_line|#endif
multiline_comment|/* attach/detach inform callbacks */
DECL|member|attach_inform
r_void
(paren
op_star
id|attach_inform
)paren
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|id
)paren
suffix:semicolon
DECL|member|detach_inform
r_void
(paren
op_star
id|detach_inform
)paren
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/* Software I2C */
DECL|member|i2c_setlines
r_void
(paren
op_star
id|i2c_setlines
)paren
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|ctrl
comma
r_int
id|data
)paren
suffix:semicolon
DECL|member|i2c_getdataline
r_int
(paren
op_star
id|i2c_getdataline
)paren
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* Hardware I2C */
DECL|member|i2c_read
r_int
(paren
op_star
id|i2c_read
)paren
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
suffix:semicolon
DECL|member|i2c_write
r_int
(paren
op_star
id|i2c_write
)paren
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
id|b1
comma
r_int
r_char
id|b2
comma
r_int
id|both
)paren
suffix:semicolon
multiline_comment|/* internal data for i2c module */
DECL|member|devices
r_struct
id|i2c_device
op_star
id|devices
(braket
id|I2C_DEVICE_MAX
)braket
suffix:semicolon
DECL|member|devcount
r_int
id|devcount
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;This holds per-device data for a i2c device&n; */
DECL|struct|i2c_device
r_struct
id|i2c_device
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful label */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* free for use by the chip driver */
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
multiline_comment|/* chip addr */
multiline_comment|/* i2c internal */
DECL|member|bus
r_struct
id|i2c_bus
op_star
id|bus
suffix:semicolon
DECL|member|driver
r_struct
id|i2c_driver
op_star
id|driver
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------- */
multiline_comment|/* i2c module functions                                                */
multiline_comment|/* register/unregister a i2c bus */
r_int
id|i2c_register_bus
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
r_int
id|i2c_unregister_bus
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* register/unregister a chip driver */
r_int
id|i2c_register_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
id|driver
)paren
suffix:semicolon
r_int
id|i2c_unregister_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/* send a command to a chip using the ioctl-like callback interface */
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
suffix:semicolon
multiline_comment|/* i2c bus access functions */
r_void
id|i2c_start
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|i2c_stop
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|i2c_one
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|i2c_zero
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
r_int
id|i2c_ack
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
multiline_comment|/* i2c (maybe) hardware functions */
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
suffix:semicolon
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
id|b1
comma
r_int
r_char
id|b2
comma
r_int
id|both
)paren
suffix:semicolon
r_int
id|i2c_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* I2C_H */
eof
