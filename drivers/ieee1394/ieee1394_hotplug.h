macro_line|#ifndef _IEEE1394_HOTPLUG_H
DECL|macro|_IEEE1394_HOTPLUG_H
mdefine_line|#define _IEEE1394_HOTPLUG_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;nodemgr.h&quot;
DECL|macro|IEEE1394_MATCH_VENDOR_ID
mdefine_line|#define IEEE1394_MATCH_VENDOR_ID&t;0x0001
DECL|macro|IEEE1394_MATCH_MODEL_ID
mdefine_line|#define IEEE1394_MATCH_MODEL_ID&t;&t;0x0002
DECL|macro|IEEE1394_MATCH_SPECIFIER_ID
mdefine_line|#define IEEE1394_MATCH_SPECIFIER_ID&t;0x0004
DECL|macro|IEEE1394_MATCH_VERSION
mdefine_line|#define IEEE1394_MATCH_VERSION&t;&t;0x0008
DECL|struct|ieee1394_device_id
r_struct
id|ieee1394_device_id
(brace
DECL|member|match_flags
id|u32
id|match_flags
suffix:semicolon
DECL|member|vendor_id
id|u32
id|vendor_id
suffix:semicolon
DECL|member|model_id
id|u32
id|model_id
suffix:semicolon
DECL|member|specifier_id
id|u32
id|specifier_id
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hpsb_protocol_driver
r_struct
id|hpsb_protocol_driver
(brace
multiline_comment|/* The name of the driver, e.g. SBP2 or IP1394 */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* &n;&t; * The device id table describing the protocols and/or devices&n;&t; * supported by this driver.  This is used by the nodemgr to&n;&t; * decide if a driver could support a given node, but the&n;&t; * probe function below can implement further protocol&n;&t; * dependent or vendor dependent checking.&n;&t; */
DECL|member|id_table
r_struct
id|ieee1394_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* &n;&t; * The update function is called when the node has just&n;&t; * survived a bus reset, i.e. it is still present on the bus.&n;&t; * However, it may be necessary to reestablish the connection&n;&t; * or login into the node again, depending on the protocol.&n;&t; */
DECL|member|update
r_void
(paren
op_star
id|update
)paren
(paren
r_struct
id|unit_directory
op_star
id|ud
)paren
suffix:semicolon
multiline_comment|/* Our LDM structure */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
r_int
id|hpsb_register_protocol
c_func
(paren
r_struct
id|hpsb_protocol_driver
op_star
id|driver
)paren
suffix:semicolon
r_void
id|hpsb_unregister_protocol
c_func
(paren
r_struct
id|hpsb_protocol_driver
op_star
id|driver
)paren
suffix:semicolon
macro_line|#endif /* _IEEE1394_HOTPLUG_H */
eof
