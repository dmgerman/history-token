macro_line|#ifndef _IEEE1394_HOTPLUG_H
DECL|macro|_IEEE1394_HOTPLUG_H
mdefine_line|#define _IEEE1394_HOTPLUG_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mod_devicetable.h&gt;
multiline_comment|/* Unit spec id and sw version entry for some protocols */
DECL|macro|AVC_UNIT_SPEC_ID_ENTRY
mdefine_line|#define AVC_UNIT_SPEC_ID_ENTRY&t;&t;0x0000A02D
DECL|macro|AVC_SW_VERSION_ENTRY
mdefine_line|#define AVC_SW_VERSION_ENTRY&t;&t;0x00010001
DECL|macro|CAMERA_UNIT_SPEC_ID_ENTRY
mdefine_line|#define CAMERA_UNIT_SPEC_ID_ENTRY&t;0x0000A02D
DECL|macro|CAMERA_SW_VERSION_ENTRY
mdefine_line|#define CAMERA_SW_VERSION_ENTRY&t;&t;0x00000100
multiline_comment|/* Check to make sure this all isn&squot;t already defined */
macro_line|#ifndef IEEE1394_MATCH_VENDOR_ID
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
macro_line|#endif
macro_line|#endif /* _IEEE1394_HOTPLUG_H */
eof
