multiline_comment|/*&n; * This file holds USB constants and structures that are needed for USB&n; * device APIs.  These are used by the USB device model, which is defined&n; * in chapter 9 of the USB 2.0 specification.  Linux has several APIs in C&n; * that need these:&n; *&n; * - the master/host side Linux-USB kernel driver API;&n; * - the &quot;usbfs&quot; user space API; and&n; * - (eventually) a Linux &quot;gadget&quot; slave/device side driver API.&n; *&n; * USB 2.0 adds an additional &quot;On The Go&quot; (OTG) mode, which lets systems&n; * act either as a USB master/host or as a USB slave/device.  That means&n; * the master and slave side APIs will benefit from working well together.&n; */
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
multiline_comment|/*&n; * USB feature flags are written using USB_REQ_{CLEAR,SET}_FEATURE, and&n; * are read as a bit array returned by USB_REQ_GET_STATUS.  (So there&n; * are at most sixteen features of each type.)&n; */
DECL|macro|USB_DEVICE_SELF_POWERED
mdefine_line|#define USB_DEVICE_SELF_POWERED&t;&t;0&t;/* (read only) */
DECL|macro|USB_DEVICE_REMOTE_WAKEUP
mdefine_line|#define USB_DEVICE_REMOTE_WAKEUP&t;1&t;/* dev may initiate wakeup */
DECL|macro|USB_DEVICE_TEST_MODE
mdefine_line|#define USB_DEVICE_TEST_MODE&t;&t;2&t;/* (high speed only) */
DECL|macro|USB_DEVICE_B_HNP_ENABLE
mdefine_line|#define USB_DEVICE_B_HNP_ENABLE&t;&t;3&t;/* dev may initiate HNP */
DECL|macro|USB_DEVICE_A_HNP_SUPPORT
mdefine_line|#define USB_DEVICE_A_HNP_SUPPORT&t;4&t;/* RH port supports HNP */
DECL|macro|USB_DEVICE_A_ALT_HNP_SUPPORT
mdefine_line|#define USB_DEVICE_A_ALT_HNP_SUPPORT&t;5&t;/* other RH port does */
DECL|macro|USB_ENDPOINT_HALT
mdefine_line|#define USB_ENDPOINT_HALT&t;&t;0&t;/* IN/OUT will STALL */
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
id|__le16
id|wValue
suffix:semicolon
DECL|member|wIndex
id|__le16
id|wIndex
suffix:semicolon
DECL|member|wLength
id|__le16
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
multiline_comment|/*&n; * STANDARD DESCRIPTORS ... as returned by GET_DESCRIPTOR, or&n; * (rarely) accepted by SET_DESCRIPTOR.&n; *&n; * Note that all multi-byte values here are encoded in little endian&n; * byte order &quot;on the wire&quot;.  But when exposed through Linux-USB APIs,&n; * they&squot;ve been converted to cpu byte order.&n; */
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
multiline_comment|/* these are from a minor usb 2.0 revision (ECN) */
DECL|macro|USB_DT_OTG
mdefine_line|#define USB_DT_OTG&t;&t;&t;0x09
DECL|macro|USB_DT_DEBUG
mdefine_line|#define USB_DT_DEBUG&t;&t;&t;0x0a
DECL|macro|USB_DT_INTERFACE_ASSOCIATION
mdefine_line|#define USB_DT_INTERFACE_ASSOCIATION&t;0x0b
multiline_comment|/* conventional codes for class-specific descriptors */
DECL|macro|USB_DT_CS_DEVICE
mdefine_line|#define USB_DT_CS_DEVICE&t;&t;0x21
DECL|macro|USB_DT_CS_CONFIG
mdefine_line|#define USB_DT_CS_CONFIG&t;&t;0x22
DECL|macro|USB_DT_CS_STRING
mdefine_line|#define USB_DT_CS_STRING&t;&t;0x23
DECL|macro|USB_DT_CS_INTERFACE
mdefine_line|#define USB_DT_CS_INTERFACE&t;&t;0x24
DECL|macro|USB_DT_CS_ENDPOINT
mdefine_line|#define USB_DT_CS_ENDPOINT&t;&t;0x25
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
multiline_comment|/*-------------------------------------------------------------------------*/
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
id|__le16
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
id|__le16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|__le16
id|idProduct
suffix:semicolon
DECL|member|bcdDevice
id|__le16
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
DECL|macro|USB_DT_DEVICE_SIZE
mdefine_line|#define USB_DT_DEVICE_SIZE&t;&t;18
multiline_comment|/*&n; * Device and/or Interface Class codes&n; * as found in bDeviceClass or bInterfaceClass&n; * and defined by www.usb.org documents&n; */
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
DECL|macro|USB_CLASS_VIDEO
mdefine_line|#define USB_CLASS_VIDEO&t;&t;&t;0x0e
DECL|macro|USB_CLASS_APP_SPEC
mdefine_line|#define USB_CLASS_APP_SPEC&t;&t;0xfe
DECL|macro|USB_CLASS_VENDOR_SPEC
mdefine_line|#define USB_CLASS_VENDOR_SPEC&t;&t;0xff
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* USB_DT_CONFIG: Configuration descriptor information.&n; *&n; * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the&n; * descriptor type is different.  Highspeed-capable devices can look&n; * different depending on what speed they&squot;re currently running.  Only&n; * devices with a USB_DT_DEVICE_QUALIFIER have any OTHER_SPEED_CONFIG&n; * descriptors.&n; */
DECL|struct|usb_config_descriptor
r_struct
id|usb_config_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|wTotalLength
id|__u16
id|wTotalLength
suffix:semicolon
DECL|member|bNumInterfaces
id|__u8
id|bNumInterfaces
suffix:semicolon
DECL|member|bConfigurationValue
id|__u8
id|bConfigurationValue
suffix:semicolon
DECL|member|iConfiguration
id|__u8
id|iConfiguration
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
suffix:semicolon
DECL|member|bMaxPower
id|__u8
id|bMaxPower
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|USB_DT_CONFIG_SIZE
mdefine_line|#define USB_DT_CONFIG_SIZE&t;&t;9
multiline_comment|/* from config descriptor bmAttributes */
DECL|macro|USB_CONFIG_ATT_ONE
mdefine_line|#define USB_CONFIG_ATT_ONE&t;&t;(1 &lt;&lt; 7)&t;/* must be set */
DECL|macro|USB_CONFIG_ATT_SELFPOWER
mdefine_line|#define USB_CONFIG_ATT_SELFPOWER&t;(1 &lt;&lt; 6)&t;/* self powered */
DECL|macro|USB_CONFIG_ATT_WAKEUP
mdefine_line|#define USB_CONFIG_ATT_WAKEUP&t;&t;(1 &lt;&lt; 5)&t;/* can wakeup */
multiline_comment|/*-------------------------------------------------------------------------*/
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
id|__le16
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
multiline_comment|/* note that &quot;string&quot; zero is special, it holds language codes that&n; * the device supports, not Unicode characters.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* USB_DT_INTERFACE: Interface descriptor */
DECL|struct|usb_interface_descriptor
r_struct
id|usb_interface_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bInterfaceNumber
id|__u8
id|bInterfaceNumber
suffix:semicolon
DECL|member|bAlternateSetting
id|__u8
id|bAlternateSetting
suffix:semicolon
DECL|member|bNumEndpoints
id|__u8
id|bNumEndpoints
suffix:semicolon
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
DECL|member|iInterface
id|__u8
id|iInterface
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|USB_DT_INTERFACE_SIZE
mdefine_line|#define USB_DT_INTERFACE_SIZE&t;&t;9
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* USB_DT_ENDPOINT: Endpoint descriptor */
DECL|struct|usb_endpoint_descriptor
r_struct
id|usb_endpoint_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bEndpointAddress
id|__u8
id|bEndpointAddress
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
suffix:semicolon
DECL|member|wMaxPacketSize
id|__u16
id|wMaxPacketSize
suffix:semicolon
DECL|member|bInterval
id|__u8
id|bInterval
suffix:semicolon
singleline_comment|// NOTE:  these two are _only_ in audio endpoints.
singleline_comment|// use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof.
DECL|member|bRefresh
id|__u8
id|bRefresh
suffix:semicolon
DECL|member|bSynchAddress
id|__u8
id|bSynchAddress
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|USB_DT_ENDPOINT_SIZE
mdefine_line|#define USB_DT_ENDPOINT_SIZE&t;&t;7
DECL|macro|USB_DT_ENDPOINT_AUDIO_SIZE
mdefine_line|#define USB_DT_ENDPOINT_AUDIO_SIZE&t;9&t;/* Audio extension */
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
multiline_comment|/*-------------------------------------------------------------------------*/
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
id|__le16
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
multiline_comment|/* USB_DT_OTG (from OTG 1.0a supplement) */
DECL|struct|usb_otg_descriptor
r_struct
id|usb_otg_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
suffix:semicolon
multiline_comment|/* support for HNP, SRP, etc */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* from usb_otg_descriptor.bmAttributes */
DECL|macro|USB_OTG_SRP
mdefine_line|#define USB_OTG_SRP&t;&t;(1 &lt;&lt; 0)
DECL|macro|USB_OTG_HNP
mdefine_line|#define USB_OTG_HNP&t;&t;(1 &lt;&lt; 1)&t;/* swap host/device roles */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* USB_DT_INTERFACE_ASSOCIATION: groups interfaces */
DECL|struct|usb_interface_assoc_descriptor
r_struct
id|usb_interface_assoc_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bFirstInterface
id|__u8
id|bFirstInterface
suffix:semicolon
DECL|member|bInterfaceCount
id|__u8
id|bInterfaceCount
suffix:semicolon
DECL|member|bFunctionClass
id|__u8
id|bFunctionClass
suffix:semicolon
DECL|member|bFunctionSubClass
id|__u8
id|bFunctionSubClass
suffix:semicolon
DECL|member|bFunctionProtocol
id|__u8
id|bFunctionProtocol
suffix:semicolon
DECL|member|iFunction
id|__u8
id|iFunction
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
DECL|enum|usb_device_state
r_enum
id|usb_device_state
(brace
multiline_comment|/* NOTATTACHED isn&squot;t in the USB spec, and this state acts&n;&t; * the same as ATTACHED ... but it&squot;s clearer this way.&n;&t; */
DECL|enumerator|USB_STATE_NOTATTACHED
id|USB_STATE_NOTATTACHED
op_assign
l_int|0
comma
multiline_comment|/* the chapter 9 device states */
DECL|enumerator|USB_STATE_ATTACHED
id|USB_STATE_ATTACHED
comma
DECL|enumerator|USB_STATE_POWERED
id|USB_STATE_POWERED
comma
DECL|enumerator|USB_STATE_DEFAULT
id|USB_STATE_DEFAULT
comma
multiline_comment|/* limited function */
DECL|enumerator|USB_STATE_ADDRESS
id|USB_STATE_ADDRESS
comma
DECL|enumerator|USB_STATE_CONFIGURED
id|USB_STATE_CONFIGURED
comma
multiline_comment|/* most functions */
DECL|enumerator|USB_STATE_SUSPENDED
id|USB_STATE_SUSPENDED
multiline_comment|/* NOTE:  there are actually four different SUSPENDED&n;&t; * states, returning to POWERED, DEFAULT, ADDRESS, or&n;&t; * CONFIGURED respectively when SOF tokens flow again.&n;&t; */
)brace
suffix:semicolon
macro_line|#endif&t;/* __LINUX_USB_CH9_H */
eof
