multiline_comment|/*&n; *  include/asm-s390/ccwdev.h&n; *  include/asm-s390x/ccwdev.h&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Arnd Bergmann &lt;arndb@de.ibm.com&gt;&n; *&n; *  Interface for CCW device drivers&n; */
macro_line|#ifndef _S390_CCWDEV_H_
DECL|macro|_S390_CCWDEV_H_
mdefine_line|#define _S390_CCWDEV_H_
macro_line|#include &lt;linux/device.h&gt;
multiline_comment|/* structs from asm/cio.h */
r_struct
id|irb
suffix:semicolon
r_struct
id|ccw1
suffix:semicolon
multiline_comment|/* the id is used to identify what hardware a device driver supports. It &n; * is used both by the ccw subsystem driver for probing and from&n; * user space for automatic module loading.&n; *&n; * References:&n; *   - struct usb_device_id (include/linux/usb.h)&n; *   - devreg_hc_t (include/linux/s390dyn.h)&n; *   - chandev_model_info (drivers/s390/misc/chandev.c)&n; */
DECL|struct|ccw_device_id
r_struct
id|ccw_device_id
(brace
DECL|member|match_flags
id|__u16
id|match_flags
suffix:semicolon
multiline_comment|/* which fields to match against */
DECL|member|cu_type
id|__u16
id|cu_type
suffix:semicolon
multiline_comment|/* control unit type     */
DECL|member|dev_type
id|__u16
id|dev_type
suffix:semicolon
multiline_comment|/* device type           */
DECL|member|cu_model
id|__u8
id|cu_model
suffix:semicolon
multiline_comment|/* control unit model    */
DECL|member|dev_model
id|__u8
id|dev_model
suffix:semicolon
multiline_comment|/* device model          */
DECL|member|driver_info
r_int
r_int
id|driver_info
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|match_flag
r_enum
id|match_flag
(brace
DECL|enumerator|CCW_DEVICE_ID_MATCH_CU_TYPE
id|CCW_DEVICE_ID_MATCH_CU_TYPE
op_assign
l_int|0x01
comma
DECL|enumerator|CCW_DEVICE_ID_MATCH_CU_MODEL
id|CCW_DEVICE_ID_MATCH_CU_MODEL
op_assign
l_int|0x02
comma
DECL|enumerator|CCW_DEVICE_ID_MATCH_DEVICE_TYPE
id|CCW_DEVICE_ID_MATCH_DEVICE_TYPE
op_assign
l_int|0x04
comma
DECL|enumerator|CCW_DEVICE_ID_MATCH_DEVICE_MODEL
id|CCW_DEVICE_ID_MATCH_DEVICE_MODEL
op_assign
l_int|0x08
comma
multiline_comment|/* CCW_DEVICE_ID_MATCH_ANY&t;     = 0x10, */
)brace
suffix:semicolon
multiline_comment|/* simplified initializers for struct ccw_device:&n; * CCW_DEVICE and CCW_DEVICE_DEVTYPE initialize one&n; * entry in your MODULE_DEVICE_TABLE and set the match_flag correctly */
DECL|macro|CCW_DEVICE
mdefine_line|#define CCW_DEVICE(cu, cum) &t;&t;&t;&t;&t;&t;&bslash;&n;&t;.cu_type=(cu), .cu_model=(cum),&t;&t;&t;&t;&t;&bslash;&n;&t;.match_flags=(CCW_DEVICE_ID_MATCH_CU_TYPE&t;&t;&t;&bslash;&n;&t;&t;   | (cum ? CCW_DEVICE_ID_MATCH_CU_MODEL : 0))
DECL|macro|CCW_DEVICE_DEVTYPE
mdefine_line|#define CCW_DEVICE_DEVTYPE(cu, cum, dev, devm)&t;&t;&t;&t;&bslash;&n;&t;.cu_type=(cu), .cu_model=(cum), .dev_type=(dev), .dev_model=(devm),&bslash;&n;&t;.match_flags=CCW_DEVICE_ID_MATCH_CU_TYPE&t;&t;&t;&bslash;&n;&t;&t;   | ((cum) ? CCW_DEVICE_ID_MATCH_CU_MODEL : 0) &t;&bslash;&n;&t;&t;   | CCW_DEVICE_ID_MATCH_DEVICE_TYPE&t;&t;&t;&bslash;&n;&t;&t;   | ((devm) ? CCW_DEVICE_ID_MATCH_DEVICE_MODEL : 0)
multiline_comment|/* scan through an array of device ids and return the first&n; * entry that matches the device.&n; *&n; * the array must end with an entry containing zero match_flags&n; */
r_static
r_inline
r_const
r_struct
id|ccw_device_id
op_star
DECL|function|ccw_device_id_match
id|ccw_device_id_match
c_func
(paren
r_const
r_struct
id|ccw_device_id
op_star
id|array
comma
r_const
r_struct
id|ccw_device_id
op_star
id|match
)paren
(brace
r_const
r_struct
id|ccw_device_id
op_star
id|id
op_assign
id|array
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
id|array
suffix:semicolon
id|id-&gt;match_flags
suffix:semicolon
id|id
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|id-&gt;match_flags
op_amp
id|CCW_DEVICE_ID_MATCH_CU_TYPE
)paren
op_logical_and
(paren
id|id-&gt;cu_type
op_ne
id|match-&gt;cu_type
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;match_flags
op_amp
id|CCW_DEVICE_ID_MATCH_CU_MODEL
)paren
op_logical_and
(paren
id|id-&gt;cu_model
op_ne
id|match-&gt;cu_model
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;match_flags
op_amp
id|CCW_DEVICE_ID_MATCH_DEVICE_TYPE
)paren
op_logical_and
(paren
id|id-&gt;dev_type
op_ne
id|match-&gt;dev_type
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;match_flags
op_amp
id|CCW_DEVICE_ID_MATCH_DEVICE_MODEL
)paren
op_logical_and
(paren
id|id-&gt;dev_model
op_ne
id|match-&gt;dev_model
)paren
)paren
r_continue
suffix:semicolon
r_return
id|id
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The struct ccw device is our replacement for the globally accessible&n; * ioinfo array. ioinfo will mutate into a subchannel device later.&n; *&n; * Reference: Documentation/driver-model.txt */
DECL|struct|ccw_device
r_struct
id|ccw_device
(brace
DECL|member|ccwlock
id|spinlock_t
op_star
id|ccwlock
suffix:semicolon
DECL|member|private
r_struct
id|ccw_device_private
op_star
r_private
suffix:semicolon
multiline_comment|/* cio private information */
DECL|member|id
r_struct
id|ccw_device_id
id|id
suffix:semicolon
multiline_comment|/* id of this device, driver_info is&n;&t;&t;&t;&t;&t;   set by ccw_find_driver */
DECL|member|drv
r_struct
id|ccw_driver
op_star
id|drv
suffix:semicolon
multiline_comment|/* */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* */
DECL|member|online
r_int
id|online
suffix:semicolon
multiline_comment|/* This is sick, but a driver can have different interrupt handlers &n;&t;   for different ccw_devices (multi-subchannel drivers)... */
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Each ccw driver registers with the ccw root bus */
DECL|struct|ccw_driver
r_struct
id|ccw_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* for automatic MOD_INC_USE_COUNT   */
DECL|member|ids
r_struct
id|ccw_device_id
op_star
id|ids
suffix:semicolon
multiline_comment|/* probe driver with these devs      */
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
multiline_comment|/* ask driver to probe dev &t;     */
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
multiline_comment|/* device is no longer available     */
DECL|member|set_online
r_int
(paren
op_star
id|set_online
)paren
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
DECL|member|set_offline
r_int
(paren
op_star
id|set_offline
)paren
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
multiline_comment|/* higher level structure, don&squot;t init&n;&t;&t;&t;&t;&t;   this from your driver&t;     */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ccw_device
op_star
id|get_ccwdev_by_busid
c_func
(paren
r_struct
id|ccw_driver
op_star
id|cdrv
comma
r_const
r_char
op_star
id|bus_id
)paren
suffix:semicolon
multiline_comment|/* devices drivers call these during module load and unload.&n; * When a driver is registered, its probe method is called&n; * when new devices for its type pop up */
r_extern
r_int
id|ccw_driver_register
(paren
r_struct
id|ccw_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_void
id|ccw_driver_unregister
(paren
r_struct
id|ccw_driver
op_star
id|driver
)paren
suffix:semicolon
r_struct
id|ccw1
suffix:semicolon
r_extern
r_int
id|ccw_device_set_options
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Allow for i/o completion notification after primary interrupt status. */
DECL|macro|CCWDEV_EARLY_NOTIFICATION
mdefine_line|#define CCWDEV_EARLY_NOTIFICATION&t;0x0001
multiline_comment|/* Report all interrupt conditions. */
DECL|macro|CCWDEV_REPORT_ALL
mdefine_line|#define CCWDEV_REPORT_ALL&t; &t;0x0002
multiline_comment|/*&n; * ccw_device_start()&n; *&n; *  Start a S/390 channel program. When the interrupt arrives, the&n; *  IRQ handler is called, either immediately, delayed (dev-end missing,&n; *  or sense required) or never (no IRQ handler registered).&n; *  Depending on the action taken, ccw_device_start() returns:  &n; *                           0&t;     - Success&n; *&t;&t;&t;     -EBUSY  - Device busy, or status pending&n; *&t;&t;&t;     -ENODEV - Device not operational&n; *                           -EINVAL - Device invalid for operation&n; */
r_extern
r_int
id|ccw_device_start
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_struct
id|ccw1
op_star
comma
r_int
r_int
comma
id|__u8
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ccw_device_resume
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ccw_device_halt
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ccw_device_clear
c_func
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|read_dev_chars
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_void
op_star
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|read_conf_data
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_void
op_star
op_star
id|buffer
comma
r_int
op_star
id|length
)paren
suffix:semicolon
r_extern
r_void
id|ccw_device_set_online
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
r_extern
r_void
id|ccw_device_set_offline
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
suffix:semicolon
r_extern
r_struct
id|ciw
op_star
id|ccw_device_get_ciw
c_func
(paren
r_struct
id|ccw_device
op_star
comma
id|__u32
id|cmd
)paren
suffix:semicolon
r_extern
id|__u8
id|ccw_device_get_path_mask
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
DECL|macro|get_ccwdev_lock
mdefine_line|#define get_ccwdev_lock(x) (x)-&gt;ccwlock
DECL|macro|to_ccwdev
mdefine_line|#define to_ccwdev(n) container_of(n, struct ccw_device, dev)
DECL|macro|to_ccwdrv
mdefine_line|#define to_ccwdrv(n) container_of(n, struct ccw_driver, driver)
r_extern
r_struct
id|ccw_device
op_star
id|ccw_device_probe_console
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|// FIXME: these have to go
r_extern
r_int
id|_ccw_device_get_device_number
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|_ccw_device_get_subchannel_number
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
macro_line|#endif /* _S390_CCWDEV_H_ */
eof
