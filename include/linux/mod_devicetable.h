multiline_comment|/*&n; * Device tables which are exported to userspace via&n; * scripts/table2alias.c.  You must keep that file in sync with this&n; * header.&n; */
macro_line|#ifndef LINUX_MOD_DEVICETABLE_H
DECL|macro|LINUX_MOD_DEVICETABLE_H
mdefine_line|#define LINUX_MOD_DEVICETABLE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|kernel_ulong_t
r_typedef
r_int
r_int
id|kernel_ulong_t
suffix:semicolon
macro_line|#endif
DECL|macro|PCI_ANY_ID
mdefine_line|#define PCI_ANY_ID (~0)
DECL|struct|pci_device_id
r_struct
id|pci_device_id
(brace
DECL|member|vendor
DECL|member|device
id|__u32
id|vendor
comma
id|device
suffix:semicolon
multiline_comment|/* Vendor and device ID or PCI_ANY_ID*/
DECL|member|subvendor
DECL|member|subdevice
id|__u32
id|subvendor
comma
id|subdevice
suffix:semicolon
multiline_comment|/* Subsystem ID&squot;s or PCI_ANY_ID */
DECL|member|class
DECL|member|class_mask
id|__u32
r_class
comma
id|class_mask
suffix:semicolon
multiline_comment|/* (class,subclass,prog-if) triplet */
DECL|member|driver_data
id|kernel_ulong_t
id|driver_data
suffix:semicolon
multiline_comment|/* Data private to the driver */
)brace
suffix:semicolon
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
id|__u32
id|match_flags
suffix:semicolon
DECL|member|vendor_id
id|__u32
id|vendor_id
suffix:semicolon
DECL|member|model_id
id|__u32
id|model_id
suffix:semicolon
DECL|member|specifier_id
id|__u32
id|specifier_id
suffix:semicolon
DECL|member|version
id|__u32
id|version
suffix:semicolon
DECL|member|driver_data
id|kernel_ulong_t
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Device table entry for &quot;new style&quot; table-driven USB drivers.&n; * User mode code can read these tables to choose which modules to load.&n; * Declare the table as a MODULE_DEVICE_TABLE.&n; *&n; * A probe() parameter will point to a matching entry from this table.&n; * Use the driver_info field for each match to hold information tied&n; * to that match:  device quirks, etc.&n; *&n; * Terminate the driver&squot;s table with an all-zeroes entry.&n; * Use the flag values to control which fields are compared.&n; */
multiline_comment|/**&n; * struct usb_device_id - identifies USB devices for probing and hotplugging&n; * @match_flags: Bit mask controlling of the other fields are used to match&n; *&t;against new devices.  Any field except for driver_info may be used,&n; *&t;although some only make sense in conjunction with other fields.&n; *&t;This is usually set by a USB_DEVICE_*() macro, which sets all&n; *&t;other fields in this structure except for driver_info.&n; * @idVendor: USB vendor ID for a device; numbers are assigned&n; *&t;by the USB forum to its members.&n; * @idProduct: Vendor-assigned product ID.&n; * @bcdDevice_lo: Low end of range of vendor-assigned product version numbers.&n; *&t;This is also used to identify individual product versions, for&n; *&t;a range consisting of a single device.&n; * @bcdDevice_hi: High end of version number range.  The range of product&n; *&t;versions is inclusive.&n; * @bDeviceClass: Class of device; numbers are assigned&n; *&t;by the USB forum.  Products may choose to implement classes,&n; *&t;or be vendor-specific.  Device classes specify behavior of all&n; *&t;the interfaces on a devices.&n; * @bDeviceSubClass: Subclass of device; associated with bDeviceClass.&n; * @bDeviceProtocol: Protocol of device; associated with bDeviceClass.&n; * @bInterfaceClass: Class of interface; numbers are assigned&n; *&t;by the USB forum.  Products may choose to implement classes,&n; *&t;or be vendor-specific.  Interface classes specify behavior only&n; *&t;of a given interface; other interfaces may support other classes.&n; * @bInterfaceSubClass: Subclass of interface; associated with bInterfaceClass.&n; * @bInterfaceProtocol: Protocol of interface; associated with bInterfaceClass.&n; * @driver_info: Holds information used by the driver.  Usually it holds&n; *&t;a pointer to a descriptor understood by the driver, or perhaps&n; *&t;device flags.&n; *&n; * In most cases, drivers will create a table of device IDs by using&n; * USB_DEVICE(), or similar macros designed for that purpose.&n; * They will then export it to userspace using MODULE_DEVICE_TABLE(),&n; * and provide it to the USB core through their usb_driver structure.&n; *&n; * See the usb_match_id() function for information about how matches are&n; * performed.  Briefly, you will normally use one of several macros to help&n; * construct these entries.  Each entry you provide will either identify&n; * one or more specific products, or will identify a class of products&n; * which have agreed to behave the same.  You should put the more specific&n; * matches towards the beginning of your table, so that driver_info can&n; * record quirks of specific products.&n; */
DECL|struct|usb_device_id
r_struct
id|usb_device_id
(brace
multiline_comment|/* which fields to match against? */
DECL|member|match_flags
id|__u16
id|match_flags
suffix:semicolon
multiline_comment|/* Used for product specific matches; range is inclusive */
DECL|member|idVendor
id|__u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__u16
id|idProduct
suffix:semicolon
DECL|member|bcdDevice_lo
id|__u16
id|bcdDevice_lo
suffix:semicolon
DECL|member|bcdDevice_hi
id|__u16
id|bcdDevice_hi
suffix:semicolon
multiline_comment|/* Used for device class matches */
DECL|member|bDeviceClass
id|__u8
id|bDeviceClass
suffix:semicolon
DECL|member|bDeviceSubClass
id|__u8
id|bDeviceSubClass
suffix:semicolon
DECL|member|bDeviceProtocol
id|__u8
id|bDeviceProtocol
suffix:semicolon
multiline_comment|/* Used for interface class matches */
DECL|member|bInterfaceClass
id|__u8
id|bInterfaceClass
suffix:semicolon
DECL|member|bInterfaceSubClass
id|__u8
id|bInterfaceSubClass
suffix:semicolon
DECL|member|bInterfaceProtocol
id|__u8
id|bInterfaceProtocol
suffix:semicolon
multiline_comment|/* not matched against */
DECL|member|driver_info
id|kernel_ulong_t
id|driver_info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Some useful macros to use to create struct usb_device_id */
DECL|macro|USB_DEVICE_ID_MATCH_VENDOR
mdefine_line|#define USB_DEVICE_ID_MATCH_VENDOR&t;&t;0x0001
DECL|macro|USB_DEVICE_ID_MATCH_PRODUCT
mdefine_line|#define USB_DEVICE_ID_MATCH_PRODUCT&t;&t;0x0002
DECL|macro|USB_DEVICE_ID_MATCH_DEV_LO
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_LO&t;&t;0x0004
DECL|macro|USB_DEVICE_ID_MATCH_DEV_HI
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_HI&t;&t;0x0008
DECL|macro|USB_DEVICE_ID_MATCH_DEV_CLASS
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_CLASS&t;&t;0x0010
DECL|macro|USB_DEVICE_ID_MATCH_DEV_SUBCLASS
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_SUBCLASS&t;0x0020
DECL|macro|USB_DEVICE_ID_MATCH_DEV_PROTOCOL
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_PROTOCOL&t;0x0040
DECL|macro|USB_DEVICE_ID_MATCH_INT_CLASS
mdefine_line|#define USB_DEVICE_ID_MATCH_INT_CLASS&t;&t;0x0080
DECL|macro|USB_DEVICE_ID_MATCH_INT_SUBCLASS
mdefine_line|#define USB_DEVICE_ID_MATCH_INT_SUBCLASS&t;0x0100
DECL|macro|USB_DEVICE_ID_MATCH_INT_PROTOCOL
mdefine_line|#define USB_DEVICE_ID_MATCH_INT_PROTOCOL&t;0x0200
multiline_comment|/* s390 CCW devices */
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
id|kernel_ulong_t
id|driver_info
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CCW_DEVICE_ID_MATCH_CU_TYPE
mdefine_line|#define CCW_DEVICE_ID_MATCH_CU_TYPE&t;&t;0x01
DECL|macro|CCW_DEVICE_ID_MATCH_CU_MODEL
mdefine_line|#define CCW_DEVICE_ID_MATCH_CU_MODEL&t;&t;0x02
DECL|macro|CCW_DEVICE_ID_MATCH_DEVICE_TYPE
mdefine_line|#define CCW_DEVICE_ID_MATCH_DEVICE_TYPE&t;&t;0x04
DECL|macro|CCW_DEVICE_ID_MATCH_DEVICE_MODEL
mdefine_line|#define CCW_DEVICE_ID_MATCH_DEVICE_MODEL&t;0x08
macro_line|#endif /* LINUX_MOD_DEVICETABLE_H */
eof
