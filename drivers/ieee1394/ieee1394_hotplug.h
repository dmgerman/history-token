macro_line|#ifndef _IEEE1394_HOTPLUG_H
DECL|macro|_IEEE1394_HOTPLUG_H
mdefine_line|#define _IEEE1394_HOTPLUG_H
macro_line|#include &quot;ieee1394_core.h&quot;
DECL|macro|IEEE1394_DEVICE_ID_MATCH_VENDOR_ID
mdefine_line|#define IEEE1394_DEVICE_ID_MATCH_VENDOR_ID&t;&t;0x0001
DECL|macro|IEEE1394_DEVICE_ID_MATCH_MODEL_ID
mdefine_line|#define IEEE1394_DEVICE_ID_MATCH_MODEL_ID&t;&t;0x0002
DECL|macro|IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_ID
mdefine_line|#define IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_ID&t;0x0004
DECL|macro|IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_VERSION
mdefine_line|#define IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_VERSION&t;0x0008
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
DECL|member|sw_specifier_id
id|u32
id|sw_specifier_id
suffix:semicolon
DECL|member|sw_specifier_version
id|u32
id|sw_specifier_version
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IEEE1394_PROTOCOL
mdefine_line|#define IEEE1394_PROTOCOL(id, version) {&t;&t;&t;&t;       &bslash;&n;&t;match_flags:&t;&t;IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_ID |     &bslash;&n;&t;&t;&t;&t;IEEE1394_DEVICE_ID_MATCH_SW_SPECIFIER_VERSION, &bslash;&n;&t;sw_specifier_id:&t;id,&t;&t;&t;&t;&t;       &bslash;&n;&t;sw_specifier_version:&t;version&t;&t;&t;&t;&t;       &bslash;&n;}
DECL|macro|IEEE1394_DEVICE
mdefine_line|#define IEEE1394_DEVICE(vendor_id, model_id) {&t;&t;&t;&bslash;&n;&t;match_flags: &t;IEEE1394_DEVICE_ID_MATCH_VENDOR_ID |&t;&bslash;&n;&t;&t;&t;IEEE1394_DEVICE_ID_MATCH_MODEL_ID,&t;&bslash;&n;&t;vendor_id:&t;vendor_id,&t;&t;&t;&t;&bslash;&n;&t;model_id:&t;vendor_id,&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* _IEEE1394_HOTPLUG_H */
eof
