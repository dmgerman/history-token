multiline_comment|/*&n; * This file holds USB constants and structures that are needed for USB&n; * device APIs.  These are used by the USB device model, which is defined&n; * in chapter 9 of the USB 2.0 specification.  Linux has several APIs in C&n; * that need these:&n; *&n; * - the master/host side Linux-USB kernel driver API;&n; * - the &quot;usbfs&quot; user space API; and&n; * - (eventually) a Linux slave/device side driver API.&n; *&n; * USB 2.0 adds an additional &quot;On The Go&quot; (OTG) mode, which lets systems&n; * act either as a USB master/host or as a USB slave/device.  That means&n; * the master and slave side APIs will benefit from working well together.&n; */
macro_line|#ifndef __LINUX_USB_CH9_H
DECL|macro|__LINUX_USB_CH9_H
mdefine_line|#define __LINUX_USB_CH9_H
macro_line|#include &lt;asm/types.h&gt;&t;&t;/* __u8 etc */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* CONTROL REQUEST SUPPORT */
multiline_comment|/*&n; * USB directions&n; *&n; * This bit flag is used in endpoint descriptors&squot; bEndpointAddress field.&n; * It&squot;s also one of three fields in control requests bRequestType.&n; */
DECL|macro|USB_DIR_OUT
mdefine_line|#define USB_DIR_OUT&t;&t;&t;0&t;&t;/* to device */
DECL|macro|USB_DIR_IN
mdefine_line|#define USB_DIR_IN&t;&t;&t;0x80&t;&t;/* to host */
multiline_comment|/*&n; * USB types, the second of three bRequestType fields&n; */
DECL|macro|USB_TYPE_MASK
mdefine_line|#define USB_TYPE_MASK&t;&t;&t;(0x03 &lt;&lt; 5)
DECL|macro|USB_TYPE_STANDARD
mdefine_line|#define USB_TYPE_STANDARD&t;&t;(0x00 &lt;&lt; 5)
DECL|macro|USB_TYPE_CLASS
mdefine_line|#define USB_TYPE_CLASS&t;&t;&t;(0x01 &lt;&lt; 5)
DECL|macro|USB_TYPE_VENDOR
mdefine_line|#define USB_TYPE_VENDOR&t;&t;&t;(0x02 &lt;&lt; 5)
DECL|macro|USB_TYPE_RESERVED
mdefine_line|#define USB_TYPE_RESERVED&t;&t;(0x03 &lt;&lt; 5)
multiline_comment|/*&n; * USB recipients, the third of three bRequestType fields&n; */
DECL|macro|USB_RECIP_MASK
mdefine_line|#define USB_RECIP_MASK&t;&t;&t;0x1f
DECL|macro|USB_RECIP_DEVICE
mdefine_line|#define USB_RECIP_DEVICE&t;&t;0x00
DECL|macro|USB_RECIP_INTERFACE
mdefine_line|#define USB_RECIP_INTERFACE&t;&t;0x01
DECL|macro|USB_RECIP_ENDPOINT
mdefine_line|#define USB_RECIP_ENDPOINT&t;&t;0x02
DECL|macro|USB_RECIP_OTHER
mdefine_line|#define USB_RECIP_OTHER&t;&t;&t;0x03
multiline_comment|/*&n; * Standard requests, for the bRequest field of a SETUP packet.&n; *&n; * These are qualified by the bRequestType field, so that for example&n; * TYPE_CLASS or TYPE_VENDOR specific feature flags could be retrieved&n; * by a GET_STATUS request.&n; */
DECL|macro|USB_REQ_GET_STATUS
mdefine_line|#define USB_REQ_GET_STATUS&t;&t;0x00
DECL|macro|USB_REQ_CLEAR_FEATURE
mdefine_line|#define USB_REQ_CLEAR_FEATURE&t;&t;0x01
DECL|macro|USB_REQ_SET_FEATURE
mdefine_line|#define USB_REQ_SET_FEATURE&t;&t;0x03
DECL|macro|USB_REQ_SET_ADDRESS
mdefine_line|#define USB_REQ_SET_ADDRESS&t;&t;0x05
DECL|macro|USB_REQ_GET_DESCRIPTOR
mdefine_line|#define USB_REQ_GET_DESCRIPTOR&t;&t;0x06
DECL|macro|USB_REQ_SET_DESCRIPTOR
mdefine_line|#define USB_REQ_SET_DESCRIPTOR&t;&t;0x07
DECL|macro|USB_REQ_GET_CONFIGURATION
mdefine_line|#define USB_REQ_GET_CONFIGURATION&t;0x08
DECL|macro|USB_REQ_SET_CONFIGURATION
mdefine_line|#define USB_REQ_SET_CONFIGURATION&t;0x09
DECL|macro|USB_REQ_GET_INTERFACE
mdefine_line|#define USB_REQ_GET_INTERFACE&t;&t;0x0A
DECL|macro|USB_REQ_SET_INTERFACE
mdefine_line|#define USB_REQ_SET_INTERFACE&t;&t;0x0B
DECL|macro|USB_REQ_SYNCH_FRAME
mdefine_line|#define USB_REQ_SYNCH_FRAME&t;&t;0x0C
multiline_comment|/**&n; * struct usb_ctrlrequest - SETUP data for a USB device control request&n; * @bRequestType: matches the USB bmRequestType field&n; * @bRequest: matches the USB bRequest field&n; * @wValue: matches the USB wValue field (le16 byte order)&n; * @wIndex: matches the USB wIndex field (le16 byte order)&n; * @wLength: matches the USB wLength field (le16 byte order)&n; *&n; * This structure is used to send control requests to a USB device.  It matches&n; * the different fields of the USB 2.0 Spec section 9.3, table 9-2.  See the&n; * USB spec for a fuller description of the different fields, and what they are&n; * used for.&n; *&n; * Note that the driver for any interface can issue control requests.&n; * For most devices, interfaces don&squot;t coordinate with each other, so&n; * such requests may be made at any time.&n; */
DECL|struct|usb_ctrlrequest
r_struct
id|usb_ctrlrequest
(brace
DECL|member|bRequestType
id|__u8
id|bRequestType
suffix:semicolon
DECL|member|bRequest
id|__u8
id|bRequest
suffix:semicolon
DECL|member|wValue
id|__u16
id|wValue
suffix:semicolon
DECL|member|wIndex
id|__u16
id|wIndex
suffix:semicolon
DECL|member|wLength
id|__u16
id|wLength
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * STANDARD DESCRIPTORS ... as returned by GET_DESCRIPTOR, or&n; * (rarely) accepted by SET_DESCRIPTOR.&n; *&n; * Note that all multi-byte values here are encoded in little endian&n; * byte order.&n; */
multiline_comment|/*&n; * Descriptor types ... USB 2.0 spec table 9.5&n; */
DECL|macro|USB_DT_DEVICE
mdefine_line|#define USB_DT_DEVICE&t;&t;&t;0x01
DECL|macro|USB_DT_CONFIG
mdefine_line|#define USB_DT_CONFIG&t;&t;&t;0x02
DECL|macro|USB_DT_STRING
mdefine_line|#define USB_DT_STRING&t;&t;&t;0x03
DECL|macro|USB_DT_INTERFACE
mdefine_line|#define USB_DT_INTERFACE&t;&t;0x04
DECL|macro|USB_DT_ENDPOINT
mdefine_line|#define USB_DT_ENDPOINT&t;&t;&t;0x05
DECL|macro|USB_DT_DEVICE_QUALIFIER
mdefine_line|#define USB_DT_DEVICE_QUALIFIER&t;&t;0x06
DECL|macro|USB_DT_OTHER_SPEED_CONFIG
mdefine_line|#define USB_DT_OTHER_SPEED_CONFIG&t;0x07
DECL|macro|USB_DT_INTERFACE_POWER
mdefine_line|#define USB_DT_INTERFACE_POWER&t;&t;0x08
multiline_comment|/* All standard descriptors have these 2 fields at the beginning */
DECL|struct|usb_descriptor_header
r_struct
id|usb_descriptor_header
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* USB_DT_DEVICE: Device descriptor */
DECL|struct|usb_device_descriptor
r_struct
id|usb_device_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdUSB
id|__u16
id|bcdUSB
suffix:semicolon
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
DECL|member|bMaxPacketSize0
id|__u8
id|bMaxPacketSize0
suffix:semicolon
DECL|member|idVendor
id|__u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__u16
id|idProduct
suffix:semicolon
DECL|member|bcdDevice
id|__u16
id|bcdDevice
suffix:semicolon
DECL|member|iManufacturer
id|__u8
id|iManufacturer
suffix:semicolon
DECL|member|iProduct
id|__u8
id|iProduct
suffix:semicolon
DECL|member|iSerialNumber
id|__u8
id|iSerialNumber
suffix:semicolon
DECL|member|bNumConfigurations
id|__u8
id|bNumConfigurations
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Device and/or Interface Class codes&n; * as found in device and interface descriptors&n; * and defined by www.usb.org documents&n; */
DECL|macro|USB_CLASS_PER_INTERFACE
mdefine_line|#define USB_CLASS_PER_INTERFACE&t;&t;0&t;/* for DeviceClass */
DECL|macro|USB_CLASS_AUDIO
mdefine_line|#define USB_CLASS_AUDIO&t;&t;&t;1
DECL|macro|USB_CLASS_COMM
mdefine_line|#define USB_CLASS_COMM&t;&t;&t;2
DECL|macro|USB_CLASS_HID
mdefine_line|#define USB_CLASS_HID&t;&t;&t;3
DECL|macro|USB_CLASS_PHYSICAL
mdefine_line|#define USB_CLASS_PHYSICAL&t;&t;5
DECL|macro|USB_CLASS_STILL_IMAGE
mdefine_line|#define USB_CLASS_STILL_IMAGE&t;&t;6
DECL|macro|USB_CLASS_PRINTER
mdefine_line|#define USB_CLASS_PRINTER&t;&t;7
DECL|macro|USB_CLASS_MASS_STORAGE
mdefine_line|#define USB_CLASS_MASS_STORAGE&t;&t;8
DECL|macro|USB_CLASS_HUB
mdefine_line|#define USB_CLASS_HUB&t;&t;&t;9
DECL|macro|USB_CLASS_CDC_DATA
mdefine_line|#define USB_CLASS_CDC_DATA&t;&t;0x0a
DECL|macro|USB_CLASS_CSCID
mdefine_line|#define USB_CLASS_CSCID&t;&t;&t;0x0b&t;/* chip+ smart card */
DECL|macro|USB_CLASS_CONTENT_SEC
mdefine_line|#define USB_CLASS_CONTENT_SEC&t;&t;0x0d&t;/* content security */
DECL|macro|USB_CLASS_APP_SPEC
mdefine_line|#define USB_CLASS_APP_SPEC&t;&t;0xfe
DECL|macro|USB_CLASS_VENDOR_SPEC
mdefine_line|#define USB_CLASS_VENDOR_SPEC&t;&t;0xff
singleline_comment|// FIXME include struct usb_config_descriptor
multiline_comment|/* USB_DT_STRING: String descriptor */
DECL|struct|usb_string_descriptor
r_struct
id|usb_string_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|wData
id|__u16
id|wData
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* UTF-16LE encoded */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
singleline_comment|// FIXME include struct usb_interface_descriptor
singleline_comment|// FIXME include struct usb_endpoint_descriptor
multiline_comment|/*&n; * Endpoints&n; */
DECL|macro|USB_ENDPOINT_NUMBER_MASK
mdefine_line|#define USB_ENDPOINT_NUMBER_MASK&t;0x0f&t;/* in bEndpointAddress */
DECL|macro|USB_ENDPOINT_DIR_MASK
mdefine_line|#define USB_ENDPOINT_DIR_MASK&t;&t;0x80
DECL|macro|USB_ENDPOINT_XFERTYPE_MASK
mdefine_line|#define USB_ENDPOINT_XFERTYPE_MASK&t;0x03&t;/* in bmAttributes */
DECL|macro|USB_ENDPOINT_XFER_CONTROL
mdefine_line|#define USB_ENDPOINT_XFER_CONTROL&t;0
DECL|macro|USB_ENDPOINT_XFER_ISOC
mdefine_line|#define USB_ENDPOINT_XFER_ISOC&t;&t;1
DECL|macro|USB_ENDPOINT_XFER_BULK
mdefine_line|#define USB_ENDPOINT_XFER_BULK&t;&t;2
DECL|macro|USB_ENDPOINT_XFER_INT
mdefine_line|#define USB_ENDPOINT_XFER_INT&t;&t;3
multiline_comment|/* USB_DT_DEVICE_QUALIFIER: Device Qualifier descriptor */
DECL|struct|usb_qualifier_descriptor
r_struct
id|usb_qualifier_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdUSB
id|__u16
id|bcdUSB
suffix:semicolon
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
DECL|member|bMaxPacketSize0
id|__u8
id|bMaxPacketSize0
suffix:semicolon
DECL|member|bNumConfigurations
id|__u8
id|bNumConfigurations
suffix:semicolon
DECL|member|bRESERVED
id|__u8
id|bRESERVED
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* USB 2.0 defines three speeds, here&squot;s how Linux identifies them */
DECL|enum|usb_device_speed
r_enum
id|usb_device_speed
(brace
DECL|enumerator|USB_SPEED_UNKNOWN
id|USB_SPEED_UNKNOWN
op_assign
l_int|0
comma
multiline_comment|/* enumerating */
DECL|enumerator|USB_SPEED_LOW
DECL|enumerator|USB_SPEED_FULL
id|USB_SPEED_LOW
comma
id|USB_SPEED_FULL
comma
multiline_comment|/* usb 1.1 */
DECL|enumerator|USB_SPEED_HIGH
id|USB_SPEED_HIGH
multiline_comment|/* usb 2.0 */
)brace
suffix:semicolon
macro_line|#endif&t;/* __LINUX_USB_CH9_H */
eof
