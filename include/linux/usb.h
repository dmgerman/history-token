macro_line|#ifndef __LINUX_USB_H
DECL|macro|__LINUX_USB_H
mdefine_line|#define __LINUX_USB_H
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* USB constants */
multiline_comment|/*&n; * Device and/or Interface Class codes&n; */
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
mdefine_line|#define USB_CLASS_CSCID&t;&t;0x0b /* chip+ smart card */
DECL|macro|USB_CLASS_CONTENT_SEC
mdefine_line|#define USB_CLASS_CONTENT_SEC&t;&t;0x0d /* content security */
DECL|macro|USB_CLASS_APP_SPEC
mdefine_line|#define USB_CLASS_APP_SPEC&t;&t;0xfe
DECL|macro|USB_CLASS_VENDOR_SPEC
mdefine_line|#define USB_CLASS_VENDOR_SPEC&t;&t;0xff
multiline_comment|/*&n; * USB types&n; */
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
multiline_comment|/*&n; * USB recipients&n; */
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
multiline_comment|/*&n; * USB directions&n; */
DECL|macro|USB_DIR_OUT
mdefine_line|#define USB_DIR_OUT&t;&t;&t;0&t;&t;/* to device */
DECL|macro|USB_DIR_IN
mdefine_line|#define USB_DIR_IN&t;&t;&t;0x80&t;&t;/* to host */
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
multiline_comment|/*&n; * USB Packet IDs (PIDs)&n; */
DECL|macro|USB_PID_UNDEF_0
mdefine_line|#define USB_PID_UNDEF_0                        0xf0
DECL|macro|USB_PID_OUT
mdefine_line|#define USB_PID_OUT                            0xe1
DECL|macro|USB_PID_ACK
mdefine_line|#define USB_PID_ACK                            0xd2
DECL|macro|USB_PID_DATA0
mdefine_line|#define USB_PID_DATA0                          0xc3
DECL|macro|USB_PID_PING
mdefine_line|#define USB_PID_PING                           0xb4&t;/* USB 2.0 */
DECL|macro|USB_PID_SOF
mdefine_line|#define USB_PID_SOF                            0xa5
DECL|macro|USB_PID_NYET
mdefine_line|#define USB_PID_NYET                           0x96&t;/* USB 2.0 */
DECL|macro|USB_PID_DATA2
mdefine_line|#define USB_PID_DATA2                          0x87&t;/* USB 2.0 */
DECL|macro|USB_PID_SPLIT
mdefine_line|#define USB_PID_SPLIT                          0x78&t;/* USB 2.0 */
DECL|macro|USB_PID_IN
mdefine_line|#define USB_PID_IN                             0x69
DECL|macro|USB_PID_NAK
mdefine_line|#define USB_PID_NAK                            0x5a
DECL|macro|USB_PID_DATA1
mdefine_line|#define USB_PID_DATA1                          0x4b
DECL|macro|USB_PID_PREAMBLE
mdefine_line|#define USB_PID_PREAMBLE                       0x3c&t;/* Token mode */
DECL|macro|USB_PID_ERR
mdefine_line|#define USB_PID_ERR                            0x3c&t;/* USB 2.0: handshake mode */
DECL|macro|USB_PID_SETUP
mdefine_line|#define USB_PID_SETUP                          0x2d
DECL|macro|USB_PID_STALL
mdefine_line|#define USB_PID_STALL                          0x1e
DECL|macro|USB_PID_MDATA
mdefine_line|#define USB_PID_MDATA                          0x0f&t;/* USB 2.0 */
multiline_comment|/*&n; * Standard requests&n; */
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
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;&t;/* for in_interrupt() */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|USB_MAJOR
mdefine_line|#define USB_MAJOR 180
DECL|function|wait_ms
r_static
id|__inline__
r_void
id|wait_ms
c_func
(paren
r_int
r_int
id|ms
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
op_plus
id|ms
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
id|mdelay
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * struct usb_ctrlrequest - structure used to make USB device control requests easier to create and decode&n; * @bRequestType: matches the USB bmRequestType field&n; * @bRequest: matches the USB bRequest field&n; * @wValue: matches the USB wValue field&n; * @wIndex: matches the USB wIndex field&n; * @wLength: matches the USB wLength field&n; *&n; * This structure is used to send control requests to a USB device.  It matches&n; * the different fields of the USB 2.0 Spec section 9.3, table 9-2.  See the&n; * USB spec for a fuller description of the different fields, and what they are&n; * used for.&n; */
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
multiline_comment|/*&n; * USB device number allocation bitmap. There&squot;s one bitmap&n; * per USB tree.&n; */
DECL|struct|usb_devmap
r_struct
id|usb_devmap
(brace
DECL|member|devicemap
r_int
r_int
id|devicemap
(braket
l_int|128
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|usb_device
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Standard USB Descriptor support.&n; * Devices may also have class-specific or vendor-specific descriptors.&n; */
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
singleline_comment|// FIXME should be internal to hub driver
DECL|macro|USB_DT_HUB
mdefine_line|#define USB_DT_HUB&t;&t;&t;(USB_TYPE_CLASS | 0x09)
DECL|macro|USB_DT_HUB_NONVAR_SIZE
mdefine_line|#define USB_DT_HUB_NONVAR_SIZE&t;&t;7
multiline_comment|/*&n; * Descriptor sizes per descriptor type&n; */
DECL|macro|USB_DT_DEVICE_SIZE
mdefine_line|#define USB_DT_DEVICE_SIZE&t;&t;18
DECL|macro|USB_DT_CONFIG_SIZE
mdefine_line|#define USB_DT_CONFIG_SIZE&t;&t;9
DECL|macro|USB_DT_INTERFACE_SIZE
mdefine_line|#define USB_DT_INTERFACE_SIZE&t;&t;9
DECL|macro|USB_DT_ENDPOINT_SIZE
mdefine_line|#define USB_DT_ENDPOINT_SIZE&t;&t;7
DECL|macro|USB_DT_ENDPOINT_AUDIO_SIZE
mdefine_line|#define USB_DT_ENDPOINT_AUDIO_SIZE&t;9&t;/* Audio extension */
multiline_comment|/* most of these maximums are arbitrary */
DECL|macro|USB_MAXCONFIG
mdefine_line|#define USB_MAXCONFIG&t;&t;8
DECL|macro|USB_ALTSETTINGALLOC
mdefine_line|#define USB_ALTSETTINGALLOC     4
DECL|macro|USB_MAXALTSETTING
mdefine_line|#define USB_MAXALTSETTING&t;128  /* Hard limit */
DECL|macro|USB_MAXINTERFACES
mdefine_line|#define USB_MAXINTERFACES&t;32
DECL|macro|USB_MAXENDPOINTS
mdefine_line|#define USB_MAXENDPOINTS&t;32   /* Hard limit */
multiline_comment|/* All standard descriptors have these 2 fields in common */
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
multiline_comment|/* USB_DT_ENDPOINT: Endpoint descriptor */
DECL|struct|usb_endpoint_descriptor
r_struct
id|usb_endpoint_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bEndpointAddress
id|__u8
id|bEndpointAddress
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|wMaxPacketSize
id|__u16
id|wMaxPacketSize
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bInterval
id|__u8
id|bInterval
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bRefresh
id|__u8
id|bRefresh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bSynchAddress
id|__u8
id|bSynchAddress
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* the rest is internal to the Linux implementation */
DECL|member|extra
r_int
r_char
op_star
id|extra
suffix:semicolon
multiline_comment|/* Extra descriptors */
DECL|member|extralen
r_int
id|extralen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* USB_DT_INTERFACE: Interface descriptor */
DECL|struct|usb_interface_descriptor
r_struct
id|usb_interface_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bInterfaceNumber
id|__u8
id|bInterfaceNumber
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bAlternateSetting
id|__u8
id|bAlternateSetting
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bNumEndpoints
id|__u8
id|bNumEndpoints
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bInterfaceClass
id|__u8
id|bInterfaceClass
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bInterfaceSubClass
id|__u8
id|bInterfaceSubClass
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bInterfaceProtocol
id|__u8
id|bInterfaceProtocol
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|iInterface
id|__u8
id|iInterface
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* the rest is internal to the Linux implementation */
DECL|member|endpoint
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
DECL|member|extra
r_int
r_char
op_star
id|extra
suffix:semicolon
multiline_comment|/* Extra descriptors */
DECL|member|extralen
r_int
id|extralen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_interface
r_struct
id|usb_interface
(brace
DECL|member|altsetting
r_struct
id|usb_interface_descriptor
op_star
id|altsetting
suffix:semicolon
DECL|member|act_altsetting
r_int
id|act_altsetting
suffix:semicolon
multiline_comment|/* active alternate setting */
DECL|member|num_altsetting
r_int
id|num_altsetting
suffix:semicolon
multiline_comment|/* number of alternate settings */
DECL|member|max_altsetting
r_int
id|max_altsetting
suffix:semicolon
multiline_comment|/* total memory allocated */
DECL|member|driver
r_struct
id|usb_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* driver */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* interface specific device info */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* USB_DT_CONFIG: Configuration descriptor information.&n; *&n; * USB_DT_OTHER_SPEED_CONFIG is the same descriptor, except that the&n; * descriptor type is different.  Highspeed-capable devices can look&n; * different depending on what speed they&squot;re currently running.  Only&n; * devices with a USB_DT_DEVICE_QUALIFIER have an OTHER_SPEED_CONFIG.&n; */
DECL|struct|usb_config_descriptor
r_struct
id|usb_config_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|wTotalLength
id|__u16
id|wTotalLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bNumInterfaces
id|__u8
id|bNumInterfaces
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bConfigurationValue
id|__u8
id|bConfigurationValue
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|iConfiguration
id|__u8
id|iConfiguration
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bmAttributes
id|__u8
id|bmAttributes
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|MaxPower
id|__u8
id|MaxPower
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* the rest is internal to the Linux implementation */
DECL|member|interface
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
DECL|member|extra
r_int
r_char
op_star
id|extra
suffix:semicolon
multiline_comment|/* Extra descriptors */
DECL|member|extralen
r_int
id|extralen
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* helpers for driver access to descriptors */
r_extern
r_int
id|usb_ifnum_to_ifpos
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
)paren
suffix:semicolon
r_extern
r_struct
id|usb_interface
op_star
id|usb_ifnum_to_if
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
)paren
suffix:semicolon
r_extern
r_struct
id|usb_endpoint_descriptor
op_star
id|usb_epnum_to_ep_desc
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|epnum
)paren
suffix:semicolon
r_int
id|__usb_get_extra_descriptor
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|size
comma
r_int
r_char
id|type
comma
r_void
op_star
op_star
id|ptr
)paren
suffix:semicolon
DECL|macro|usb_get_extra_descriptor
mdefine_line|#define usb_get_extra_descriptor(ifpoint,type,ptr)&bslash;&n;&t;__usb_get_extra_descriptor((ifpoint)-&gt;extra,(ifpoint)-&gt;extralen,&bslash;&n;&t;&t;type,(void**)ptr)
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/* Host Controller Driver (HCD) support */
r_struct
id|usb_operations
suffix:semicolon
DECL|macro|DEVNUM_ROUND_ROBIN
mdefine_line|#define DEVNUM_ROUND_ROBIN&t;/***** OPTION *****/
multiline_comment|/*&n; * Allocated per bus we have&n; */
DECL|struct|usb_bus
r_struct
id|usb_bus
(brace
DECL|member|busnum
r_int
id|busnum
suffix:semicolon
multiline_comment|/* Bus number (in order of reg) */
DECL|member|bus_name
r_char
op_star
id|bus_name
suffix:semicolon
multiline_comment|/* stable id (PCI slot_name etc) */
macro_line|#ifdef DEVNUM_ROUND_ROBIN
DECL|member|devnum_next
r_int
id|devnum_next
suffix:semicolon
multiline_comment|/* Next open device number in round-robin allocation */
macro_line|#endif /* DEVNUM_ROUND_ROBIN */
DECL|member|devmap
r_struct
id|usb_devmap
id|devmap
suffix:semicolon
multiline_comment|/* device address allocation map */
DECL|member|op
r_struct
id|usb_operations
op_star
id|op
suffix:semicolon
multiline_comment|/* Operations (specific to the HC) */
DECL|member|root_hub
r_struct
id|usb_device
op_star
id|root_hub
suffix:semicolon
multiline_comment|/* Root hub */
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
multiline_comment|/* list of busses */
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
multiline_comment|/* Host Controller private data */
DECL|member|bandwidth_allocated
r_int
id|bandwidth_allocated
suffix:semicolon
multiline_comment|/* on this bus: how much of the time&n;&t;&t;&t;&t;&t; * reserved for periodic (intr/iso)&n;&t;&t;&t;&t;&t; * requests is used, on average?&n;&t;&t;&t;&t;&t; * Units: microseconds/frame.&n;&t;&t;&t;&t;&t; * Limits: Full/low speed reserve 90%,&n;&t;&t;&t;&t;&t; * while high speed reserves 80%.&n;&t;&t;&t;&t;&t; */
DECL|member|bandwidth_int_reqs
r_int
id|bandwidth_int_reqs
suffix:semicolon
multiline_comment|/* number of Interrupt requests */
DECL|member|bandwidth_isoc_reqs
r_int
id|bandwidth_isoc_reqs
suffix:semicolon
multiline_comment|/* number of Isoc. requests */
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
multiline_comment|/* usbfs dentry entry for the bus */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// FIXME:  root_hub_string vanishes when &quot;usb_hcd&quot; conversion is done,
singleline_comment|// along with pre-hcd versions of the OHCI and UHCI drivers.
r_extern
r_int
id|usb_root_hub_string
c_func
(paren
r_int
id|id
comma
r_int
id|serial
comma
r_char
op_star
id|type
comma
id|__u8
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/* This is arbitrary.&n; * From USB 2.0 spec Table 11-13, offset 7, a hub can&n; * have up to 255 ports. The most yet reported is 10.&n; */
DECL|macro|USB_MAXCHILDREN
mdefine_line|#define USB_MAXCHILDREN&t;&t;(16)
r_struct
id|usb_tt
suffix:semicolon
DECL|struct|usb_device
r_struct
id|usb_device
(brace
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
multiline_comment|/* Address on USB bus */
DECL|member|devpath
r_char
id|devpath
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Use in messages: /port/port/... */
r_enum
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
DECL|member|speed
)brace
id|speed
suffix:semicolon
DECL|member|tt
r_struct
id|usb_tt
op_star
id|tt
suffix:semicolon
multiline_comment|/* low/full speed dev, highspeed hub */
DECL|member|ttport
r_int
id|ttport
suffix:semicolon
multiline_comment|/* device port on that tt hub */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* Reference count */
DECL|member|serialize
r_struct
id|semaphore
id|serialize
suffix:semicolon
DECL|member|toggle
r_int
r_int
id|toggle
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* one bit for each endpoint ([0] = IN, [1] = OUT) */
DECL|member|halted
r_int
r_int
id|halted
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* endpoint halts; one bit per endpoint # &amp; direction; */
multiline_comment|/* [0] = IN, [1] = OUT */
DECL|member|epmaxpacketin
r_int
id|epmaxpacketin
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* INput endpoint specific maximums */
DECL|member|epmaxpacketout
r_int
id|epmaxpacketout
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OUTput endpoint specific maximums */
DECL|member|parent
r_struct
id|usb_device
op_star
id|parent
suffix:semicolon
multiline_comment|/* our hub, unless we&squot;re the root */
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* Bus we&squot;re part of */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* Generic device interface */
DECL|member|descriptor
r_struct
id|usb_device_descriptor
id|descriptor
suffix:semicolon
multiline_comment|/* Descriptor */
DECL|member|config
r_struct
id|usb_config_descriptor
op_star
id|config
suffix:semicolon
multiline_comment|/* All of the configs */
DECL|member|actconfig
r_struct
id|usb_config_descriptor
op_star
id|actconfig
suffix:semicolon
multiline_comment|/* the active configuration */
DECL|member|rawdescriptors
r_char
op_star
op_star
id|rawdescriptors
suffix:semicolon
multiline_comment|/* Raw descriptors for each config */
DECL|member|have_langid
r_int
id|have_langid
suffix:semicolon
multiline_comment|/* whether string_langid is valid yet */
DECL|member|string_langid
r_int
id|string_langid
suffix:semicolon
multiline_comment|/* language ID for strings */
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
multiline_comment|/* Host Controller private data */
DECL|member|filelist
r_struct
id|list_head
id|filelist
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
multiline_comment|/* usbfs dentry entry for the device */
multiline_comment|/*&n;&t; * Child devices - these can be either new devices&n;&t; * (if this is a hub device), or different instances&n;&t; * of this same device.&n;&t; *&n;&t; * Each instance needs its own set of data structures.&n;&t; */
DECL|member|maxchild
r_int
id|maxchild
suffix:semicolon
multiline_comment|/* Number of ports if hub */
DECL|member|children
r_struct
id|usb_device
op_star
id|children
(braket
id|USB_MAXCHILDREN
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|usb_device
op_star
id|usb_alloc_dev
c_func
(paren
r_struct
id|usb_device
op_star
id|parent
comma
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|usb_device
op_star
id|usb_get_dev
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_free_dev
c_func
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
DECL|macro|usb_put_dev
mdefine_line|#define usb_put_dev usb_free_dev
multiline_comment|/* for when layers above USB add new non-USB drivers */
r_extern
r_void
id|usb_scan_devices
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* mostly for devices emulating SCSI over USB */
r_extern
r_int
id|usb_reset_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* for drivers using iso endpoints */
r_extern
r_int
id|usb_get_current_frame_number
(paren
r_struct
id|usb_device
op_star
id|usb_dev
)paren
suffix:semicolon
multiline_comment|/* used these for multi-interface device registration */
r_extern
r_int
id|usb_find_interface_driver_for_ifnum
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
)paren
suffix:semicolon
r_extern
r_void
id|usb_driver_claim_interface
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_struct
id|usb_interface
op_star
id|iface
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|usb_interface_claimed
c_func
(paren
r_struct
id|usb_interface
op_star
id|iface
)paren
suffix:semicolon
r_extern
r_void
id|usb_driver_release_interface
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_struct
id|usb_interface
op_star
id|iface
)paren
suffix:semicolon
r_const
r_struct
id|usb_device_id
op_star
id|usb_match_id
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|usb_interface
op_star
id|interface
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
suffix:semicolon
multiline_comment|/**&n; * usb_make_path - returns stable device path in the usb tree&n; * @dev: the device whose path is being constructed&n; * @buf: where to put the string&n; * @size: how big is &quot;buf&quot;?&n; *&n; * Returns length of the string (&gt; 0) or negative if size was too small.&n; *&n; * This identifier is intended to be &quot;stable&quot;, reflecting physical paths in&n; * hardware such as physical bus addresses for host controllers or ports on&n; * USB hubs.  That makes it stay the same until systems are physically&n; * reconfigured, by re-cabling a tree of USB devices or by moving USB host&n; * controllers.  Adding and removing devices, including virtual root hubs&n; * in host controller driver modules, does not change these path identifers;&n; * neither does rebooting or re-enumerating.  These are more useful identifiers&n; * than changeable (&quot;unstable&quot;) ones like bus numbers or device addresses.&n; * &n; * With a partial exception for devices connected to USB 2.0 root hubs, these&n; * identifiers are also predictable:  so long as the device tree isn&squot;t changed,&n; * plugging any USB device into a given hub port always gives it the same path.&n; * Because of the use of &quot;companion&quot; controllers, devices connected to ports on&n; * USB 2.0 root hubs (EHCI host controllers) will get one path ID if they are&n; * high speed, and a different one if they are full or low speed.&n; */
DECL|function|usb_make_path
r_static
r_inline
r_int
id|usb_make_path
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_int
id|actual
suffix:semicolon
id|actual
op_assign
id|snprintf
(paren
id|buf
comma
id|size
comma
l_string|&quot;usb-%s-%s&quot;
comma
id|dev-&gt;bus-&gt;bus_name
comma
id|dev-&gt;devpath
)paren
suffix:semicolon
r_return
(paren
id|actual
op_ge
id|size
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
id|actual
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Device table entry for &quot;new style&quot; table-driven USB drivers.&n; * User mode code can read these tables to choose which modules to load.&n; * Declare the table as a MODULE_DEVICE_TABLE.&n; *&n; * The third probe() parameter will point to a matching entry from this&n; * table.  (Null value reserved.)  Use the driver_data field for each&n; * match to hold information tied to that match:  device quirks, etc.&n; * &n; * Terminate the driver&squot;s table with an all-zeroes entry.&n; * Use the flag values to control which fields are compared.&n; */
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
r_int
r_int
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
DECL|macro|USB_DEVICE_ID_MATCH_DEVICE
mdefine_line|#define USB_DEVICE_ID_MATCH_DEVICE&t;&t;(USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT)
DECL|macro|USB_DEVICE_ID_MATCH_DEV_RANGE
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_RANGE&t;&t;(USB_DEVICE_ID_MATCH_DEV_LO | USB_DEVICE_ID_MATCH_DEV_HI)
DECL|macro|USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION
mdefine_line|#define USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION&t;(USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_RANGE)
DECL|macro|USB_DEVICE_ID_MATCH_DEV_INFO
mdefine_line|#define USB_DEVICE_ID_MATCH_DEV_INFO &bslash;&n;&t;(USB_DEVICE_ID_MATCH_DEV_CLASS | USB_DEVICE_ID_MATCH_DEV_SUBCLASS | USB_DEVICE_ID_MATCH_DEV_PROTOCOL)
DECL|macro|USB_DEVICE_ID_MATCH_INT_INFO
mdefine_line|#define USB_DEVICE_ID_MATCH_INT_INFO &bslash;&n;&t;(USB_DEVICE_ID_MATCH_INT_CLASS | USB_DEVICE_ID_MATCH_INT_SUBCLASS | USB_DEVICE_ID_MATCH_INT_PROTOCOL)
multiline_comment|/**&n; * USB_DEVICE - macro used to describe a specific usb device&n; * @vend: the 16 bit USB Vendor ID&n; * @prod: the 16 bit USB Product ID&n; *&n; * This macro is used to create a struct usb_device_id that matches a&n; * specific device.&n; */
DECL|macro|USB_DEVICE
mdefine_line|#define USB_DEVICE(vend,prod) &bslash;&n;&t;match_flags: USB_DEVICE_ID_MATCH_DEVICE, idVendor: (vend), idProduct: (prod)
multiline_comment|/**&n; * USB_DEVICE_VER - macro used to describe a specific usb device with a version range&n; * @vend: the 16 bit USB Vendor ID&n; * @prod: the 16 bit USB Product ID&n; * @lo: the bcdDevice_lo value&n; * @hi: the bcdDevice_hi value&n; *&n; * This macro is used to create a struct usb_device_id that matches a&n; * specific device, with a version range.&n; */
DECL|macro|USB_DEVICE_VER
mdefine_line|#define USB_DEVICE_VER(vend,prod,lo,hi) &bslash;&n;&t;match_flags: USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION, idVendor: (vend), idProduct: (prod), bcdDevice_lo: (lo), bcdDevice_hi: (hi)
multiline_comment|/**&n; * USB_DEVICE_INFO - macro used to describe a class of usb devices&n; * @cl: bDeviceClass value&n; * @sc: bDeviceSubClass value&n; * @pr: bDeviceProtocol value&n; *&n; * This macro is used to create a struct usb_device_id that matches a&n; * specific class of devices.&n; */
DECL|macro|USB_DEVICE_INFO
mdefine_line|#define USB_DEVICE_INFO(cl,sc,pr) &bslash;&n;&t;match_flags: USB_DEVICE_ID_MATCH_DEV_INFO, bDeviceClass: (cl), bDeviceSubClass: (sc), bDeviceProtocol: (pr)
multiline_comment|/**&n; * USB_INTERFACE_INFO - macro used to describe a class of usb interfaces &n; * @cl: bInterfaceClass value&n; * @sc: bInterfaceSubClass value&n; * @pr: bInterfaceProtocol value&n; *&n; * This macro is used to create a struct usb_device_id that matches a&n; * specific class of interfaces.&n; */
DECL|macro|USB_INTERFACE_INFO
mdefine_line|#define USB_INTERFACE_INFO(cl,sc,pr) &bslash;&n;&t;match_flags: USB_DEVICE_ID_MATCH_INT_INFO, bInterfaceClass: (cl), bInterfaceSubClass: (sc), bInterfaceProtocol: (pr)
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/**&n; * struct usb_driver - identifies USB driver to usbcore&n; * @owner: Pointer to the module owner of this driver; initialize&n; *&t;it using THIS_MODULE.&n; * @name: The driver name should be unique among USB drivers,&n; *&t;and should normally be the same as the module name.&n; * @probe: Called to see if the driver is willing to manage a particular&n; *&t;interface on a device.  The probe routine returns a handle that &n; *&t;will later be provided to disconnect(), or a null pointer to&n; *&t;indicate that the driver will not handle the interface.&n; *&t;The handle is normally a pointer to driver-specific data.&n; *&t;If the probe() routine needs to access the interface&n; *&t;structure itself, use usb_ifnum_to_if() to make sure it&squot;s using&n; *&t;the right one.&n; * @disconnect: Called when the interface is no longer accessible, usually&n; *&t;because its device has been (or is being) disconnected.  The&n; *&t;handle passed is what was returned by probe(), or was provided&n; *&t;to usb_driver_claim_interface().&n; * @fops: USB drivers can reuse some character device framework in&n; *&t;the USB subsystem by providing a file operations vector and&n; *&t;a minor number.&n; * @minor: Used with fops to simplify creating USB character devices.&n; *&t;Such drivers have sixteen character devices, using the USB&n; *&t;major number and starting with this minor number.&n; * @num_minors: Used with minor to specify how many minors are used by&n; *&t;this driver.&n; * @ioctl: Used for drivers that want to talk to userspace through&n; *&t;the &quot;usbfs&quot; filesystem.  This lets devices provide ways to&n; *&t;expose information to user space regardless of where they&n; *&t;do (or don&squot;t) show up otherwise in the filesystem.&n; * @id_table: USB drivers use ID table to support hotplugging.&n; *&t;Export this with MODULE_DEVICE_TABLE(usb,...), or use NULL to&n; *&t;say that probe() should be called for any unclaimed interfce.&n; *&n; * USB drivers should provide a name, probe() and disconnect() methods,&n; * and an id_table.  Other driver fields are optional.&n; *&n; * The id_table is used in hotplugging.  It holds a set of descriptors,&n; * and specialized data may be associated with each entry.  That table&n; * is used by both user and kernel mode hotplugging support.&n; *&n; * The probe() and disconnect() methods are called in a context where&n; * they can sleep, but they should avoid abusing the privilege.  Most&n; * work to connect to a device should be done when the device is opened,&n; * and undone at the last close.  The disconnect code needs to address&n; * concurrency issues with respect to open() and close() methods, as&n; * well as forcing all pending I/O requests to complete (by unlinking&n; * them as necessary, and blocking until the unlinks complete).&n; */
DECL|struct|usb_driver
r_struct
id|usb_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe
r_void
op_star
(paren
op_star
id|probe
)paren
(paren
r_struct
id|usb_device
op_star
id|dev
comma
multiline_comment|/* the device */
r_int
id|intf
comma
multiline_comment|/* what interface */
r_const
r_struct
id|usb_device_id
op_star
id|id
multiline_comment|/* from id_table */
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|usb_device
op_star
id|dev
comma
multiline_comment|/* the device */
r_void
op_star
id|handle
multiline_comment|/* as returned by probe() */
)paren
suffix:semicolon
DECL|member|driver_list
r_struct
id|list_head
id|driver_list
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|num_minors
r_int
id|num_minors
suffix:semicolon
DECL|member|serialize
r_struct
id|semaphore
id|serialize
suffix:semicolon
multiline_comment|/* ioctl -- userspace apps can talk to drivers through usbfs */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|code
comma
r_void
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* support for &quot;new-style&quot; USB hotplugging */
DECL|member|id_table
r_const
r_struct
id|usb_device_id
op_star
id|id_table
suffix:semicolon
multiline_comment|/* suspend before the bus suspends;&n;&t; * disconnect or resume when the bus resumes */
multiline_comment|/* void (*suspend)(struct usb_device *dev); */
multiline_comment|/* void (*resume)(struct usb_device *dev); */
)brace
suffix:semicolon
multiline_comment|/*&n; * use these in module_init()/module_exit()&n; * and don&squot;t forget MODULE_DEVICE_TABLE(usb, ...)&n; */
r_extern
r_int
id|usb_register
c_func
(paren
r_struct
id|usb_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_deregister
c_func
(paren
r_struct
id|usb_driver
op_star
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_USB_DYNAMIC_MINORS
DECL|function|usb_register_dev
r_static
r_inline
r_int
id|usb_register_dev
c_func
(paren
r_struct
id|usb_driver
op_star
id|new_driver
comma
r_int
id|num_minors
comma
r_int
op_star
id|start_minor
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|usb_deregister_dev
r_static
r_inline
r_void
id|usb_deregister_dev
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_int
id|num_minors
comma
r_int
id|start_minor
)paren
(brace
)brace
macro_line|#else
r_extern
r_int
id|usb_register_dev
c_func
(paren
r_struct
id|usb_driver
op_star
id|new_driver
comma
r_int
id|num_minors
comma
r_int
op_star
id|start_minor
)paren
suffix:semicolon
r_extern
r_void
id|usb_deregister_dev
c_func
(paren
r_struct
id|usb_driver
op_star
id|driver
comma
r_int
id|num_minors
comma
r_int
id|start_minor
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/*&n; * URB support, for asynchronous request completions&n; */
multiline_comment|/*&n; * urb-&gt;transfer_flags:&n; *&n; * FIXME should be URB_* flags&n; */
DECL|macro|USB_DISABLE_SPD
mdefine_line|#define USB_DISABLE_SPD         0x0001
DECL|macro|USB_ISO_ASAP
mdefine_line|#define USB_ISO_ASAP            0x0002
DECL|macro|USB_ASYNC_UNLINK
mdefine_line|#define USB_ASYNC_UNLINK        0x0008
DECL|macro|USB_QUEUE_BULK
mdefine_line|#define USB_QUEUE_BULK          0x0010
DECL|macro|USB_NO_FSBR
mdefine_line|#define USB_NO_FSBR&t;&t;0x0020
DECL|macro|USB_ZERO_PACKET
mdefine_line|#define USB_ZERO_PACKET         0x0040  /* Finish bulk OUTs with short packet */
DECL|macro|URB_NO_INTERRUPT
mdefine_line|#define URB_NO_INTERRUPT&t;0x0080&t;/* HINT: no non-error interrupt needed */
multiline_comment|/* ... less overhead for QUEUE_BULK */
DECL|macro|USB_TIMEOUT_KILLED
mdefine_line|#define USB_TIMEOUT_KILLED&t;0x1000&t;/* only set by HCD! */
DECL|struct|usb_iso_packet_descriptor
r_struct
id|usb_iso_packet_descriptor
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* expected length */
DECL|member|actual_length
r_int
r_int
id|actual_length
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|urb
suffix:semicolon
DECL|typedef|usb_complete_t
r_typedef
r_void
(paren
op_star
id|usb_complete_t
)paren
(paren
r_struct
id|urb
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * struct urb - USB Request Block&n; * @urb_list: For use by current owner of the URB.&n; * @next: Used to link ISO requests into rings.&n; * @pipe: Holds endpoint number, direction, type, and max packet size.&n; *&t;Create these values with the eight macros available;&n; *&t;usb_{snd,rcv}TYPEpipe(dev,endpoint), where the type is &quot;ctrl&quot;&n; *&t;(control), &quot;bulk&quot;, &quot;int&quot; (interrupt), or &quot;iso&quot; (isochronous).&n; *&t;For example usb_sndbulkpipe() or usb_rcvintpipe().  Endpoint&n; *&t;numbers range from zero to fifteen.  Note that &quot;in&quot; endpoint two&n; *&t;is a different endpoint (and pipe) from &quot;out&quot; endpoint two.&n; *&t;The current configuration controls the existence, type, and&n; *&t;maximum packet size of any given endpoint.&n; * @dev: Identifies the USB device to perform the request.&n; * @status: This is read in non-iso completion functions to get the&n; *&t;status of the particular request.  ISO requests only use it&n; *&t;to tell whether the URB was unlinked; detailed status for&n; *&t;each frame is in the fields of the iso_frame-desc.&n; * @transfer_flags: A variety of flags may be used to affect how URB&n; *&t;submission, unlinking, or operation are handled.  Different&n; *&t;kinds of URB can use different flags.&n; * @transfer_buffer: For non-iso transfers, this identifies the buffer&n; *&t;to (or from) which the I/O request will be performed.  This&n; *&t;buffer must be suitable for DMA; allocate it with kmalloc()&n; *&t;or equivalent.  For transfers to &quot;in&quot; endpoints, contents of&n; *&t;this buffer will be modified.&n; * @transfer_buffer_length: How big is transfer_buffer.  The transfer may&n; *&t;be broken up into chunks according to the current maximum packet&n; *&t;size for the endpoint, which is a function of the configuration&n; *&t;and is encoded in the pipe.&n; * @actual_length: This is read in non-iso completion functions, and&n; *&t;it tells how many bytes (out of transfer_buffer_length) were&n; *&t;transferred.  It will normally be the same as requested, unless&n; *&t;either an error was reported or a short read was performed and&n; *&t;the USB_DISABLE_SPD transfer flag was used to say that such&n; *&t;short reads are not errors. &n; * @setup_packet: Only used for control transfers, this points to eight bytes&n; *&t;of setup data.  Control transfers always start by sending this data&n; *&t;to the device.  Then transfer_buffer is read or written, if needed.&n; * @start_frame: Returns the initial frame for interrupt or isochronous&n; *&t;transfers.&n; * @number_of_packets: Lists the number of ISO transfer buffers.&n; * @interval: Specifies the polling interval for interrupt or isochronous&n; *&t;transfers.  The units are frames (milliseconds) for for full and low&n; *&t;speed devices, and microframes (1/8 millisecond) for highspeed ones.&n; * @error_count: Returns the number of ISO transfers that reported errors.&n; * @context: For use in completion functions.  This normally points to&n; *&t;request-specific driver context.&n; * @complete: Completion handler. This URB is passed as the parameter to the&n; *&t;completion function.  Except for interrupt or isochronous transfers&n; *&t;that aren&squot;t being unlinked, the completion function may then do what&n; *&t;it likes with the URB, including resubmitting or freeing it.&n; * @iso_frame_desc: Used to provide arrays of ISO transfer buffers and to &n; *&t;collect the transfer status for each buffer.&n; *&n; * This structure identifies USB transfer requests.  URBs must be allocated by&n; * calling usb_alloc_urb() and freed with a call to usb_free_urb().&n; * Initialization may be done using various usb_fill_*_urb() functions.  URBs&n; * are submitted using usb_submit_urb(), and pending requests may be canceled&n; * using usb_unlink_urb().&n; *&n; * Initialization:&n; *&n; * All URBs submitted must initialize dev, pipe, next (may be null),&n; * transfer_flags (may be zero), complete, timeout (may be zero).&n; * The USB_ASYNC_UNLINK transfer flag affects later invocations of&n; * the usb_unlink_urb() routine.&n; *&n; * All non-isochronous URBs must also initialize &n; * transfer_buffer and transfer_buffer_length.  They may provide the&n; * USB_DISABLE_SPD transfer flag, indicating that short reads are&n; * not to be treated as errors.&n; *&n; * Bulk URBs may pass the USB_QUEUE_BULK transfer flag, telling the host&n; * controller driver never to report an error if several bulk requests get&n; * queued to the same endpoint.  Such queueing supports more efficient use&n; * of bus bandwidth, minimizing delays due to interrupts and scheduling,&n; * if the host controller hardware is smart enough.  Bulk URBs can also&n; * use the USB_ZERO_PACKET transfer flag, indicating that bulk OUT transfers&n; * should always terminate with a short packet, even if it means adding an&n; * extra zero length packet.&n; *&n; * Control URBs must provide a setup_packet.&n; *&n; * Interrupt UBS must provide an interval, saying how often (in milliseconds&n; * or, for highspeed devices, 125 microsecond units)&n; * to poll for transfers.  After the URB has been submitted, the interval&n; * and start_frame fields reflect how the transfer was actually scheduled.&n; * The polling interval may be more frequent than requested.&n; * For example, some controllers have a maximum interval of 32 microseconds,&n; * while others support intervals of up to 1024 microseconds.&n; * Isochronous URBs also have transfer intervals.  (Note that for isochronous&n; * endpoints, as well as high speed interrupt endpoints, the encoding of&n; * the transfer interval in the endpoint descriptor is logarithmic.)&n; *&n; * Isochronous URBs normally use the USB_ISO_ASAP transfer flag, telling&n; * the host controller to schedule the transfer as soon as bandwidth&n; * utilization allows, and then set start_frame to reflect the actual frame&n; * selected during submission.  Otherwise drivers must specify the start_frame&n; * and handle the case where the transfer can&squot;t begin then.  However, drivers&n; * won&squot;t know how bandwidth is currently allocated, and while they can&n; * find the current frame using usb_get_current_frame_number () they can&squot;t&n; * know the range for that frame number.  (Ranges for frame counter values&n; * are HC-specific, and can go from 256 to 65536 frames from &quot;now&quot;.)&n; *&n; * Isochronous URBs have a different data transfer model, in part because&n; * the quality of service is only &quot;best effort&quot;.  Callers provide specially&n; * allocated URBs, with number_of_packets worth of iso_frame_desc structures&n; * at the end.  Each such packet is an individual ISO transfer.  Isochronous&n; * URBs are normally submitted with urb-&gt;next fields set up as a ring, so&n; * that data (such as audio or video) streams at as constant a rate as the&n; * host controller scheduler can support.&n; *&n; * Completion Callbacks:&n; *&n; * The completion callback is made in_interrupt(), and one of the first&n; * things that a completion handler should do is check the status field.&n; * The status field is provided for all URBs.  It is used to report&n; * unlinked URBs, and status for all non-ISO transfers.  It should not&n; * be examined outside of the completion handler.&n; *&n; * The context field is normally used to link URBs back to the relevant&n; * driver or request state.&n; *&n; * When completion callback is invoked for non-isochronous URBs, the&n; * actual_length field tells how many bytes were transferred.&n; *&n; * For interrupt and isochronous URBs, the URB provided to the callback&n; * function is still &quot;owned&quot; by the USB core subsystem unless the status&n; * indicates that the URB has been unlinked.  Completion handlers should&n; * not modify such URBs until they have been unlinked.&n; *&n; * ISO transfer status is reported in the status and actual_length fields&n; * of the iso_frame_desc array, and the number of errors is reported in&n; * error_count.&n; */
DECL|struct|urb
r_struct
id|urb
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for the URB */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* reference count of the URB */
DECL|member|hcpriv
r_void
op_star
id|hcpriv
suffix:semicolon
multiline_comment|/* private data for host controller */
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
multiline_comment|/* list pointer to all active urbs */
DECL|member|next
r_struct
id|urb
op_star
id|next
suffix:semicolon
multiline_comment|/* (in) pointer to next URB */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* (in) pointer to associated device */
DECL|member|pipe
r_int
r_int
id|pipe
suffix:semicolon
multiline_comment|/* (in) pipe information */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* (return) non-ISO status */
DECL|member|transfer_flags
r_int
r_int
id|transfer_flags
suffix:semicolon
multiline_comment|/* (in) USB_DISABLE_SPD | ...*/
DECL|member|transfer_buffer
r_void
op_star
id|transfer_buffer
suffix:semicolon
multiline_comment|/* (in) associated data buffer */
DECL|member|transfer_buffer_length
r_int
id|transfer_buffer_length
suffix:semicolon
multiline_comment|/* (in) data buffer length */
DECL|member|actual_length
r_int
id|actual_length
suffix:semicolon
multiline_comment|/* (return) actual transfer length */
DECL|member|bandwidth
r_int
id|bandwidth
suffix:semicolon
multiline_comment|/* bandwidth for INT/ISO request */
DECL|member|setup_packet
r_int
r_char
op_star
id|setup_packet
suffix:semicolon
multiline_comment|/* (in) setup packet (control only) */
DECL|member|start_frame
r_int
id|start_frame
suffix:semicolon
multiline_comment|/* (modify) start frame (INT/ISO) */
DECL|member|number_of_packets
r_int
id|number_of_packets
suffix:semicolon
multiline_comment|/* (in) number of ISO packets */
DECL|member|interval
r_int
id|interval
suffix:semicolon
multiline_comment|/* (in) transfer interval (INT/ISO) */
DECL|member|error_count
r_int
id|error_count
suffix:semicolon
multiline_comment|/* (return) number of ISO errors */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* (in) timeout, in jiffies */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* (in) context for completion */
DECL|member|complete
id|usb_complete_t
id|complete
suffix:semicolon
multiline_comment|/* (in) completion routine */
DECL|member|iso_frame_desc
r_struct
id|usb_iso_packet_descriptor
id|iso_frame_desc
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* (in) ISO ONLY */
)brace
suffix:semicolon
multiline_comment|/**&n; * usb_fill_control_urb - initializes a control urb&n; * @urb: pointer to the urb to initialize.&n; * @dev: pointer to the struct usb_device for this urb.&n; * @pipe: the endpoint pipe&n; * @setup_packet: pointer to the setup_packet buffer&n; * @transfer_buffer: pointer to the transfer buffer&n; * @buffer_length: length of the transfer buffer&n; * @complete: pointer to the usb_complete_t function&n; * @context: what to set the urb context to.&n; *&n; * Initializes a control urb with the proper information needed to submit&n; * it to a device.&n; */
DECL|function|usb_fill_control_urb
r_static
r_inline
r_void
id|usb_fill_control_urb
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_int
r_char
op_star
id|setup_packet
comma
r_void
op_star
id|transfer_buffer
comma
r_int
id|buffer_length
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|urb-&gt;lock
)paren
suffix:semicolon
id|urb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|pipe
suffix:semicolon
id|urb-&gt;setup_packet
op_assign
id|setup_packet
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|transfer_buffer
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|buffer_length
suffix:semicolon
id|urb-&gt;complete
op_assign
id|complete
suffix:semicolon
id|urb-&gt;context
op_assign
id|context
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_fill_bulk_urb - macro to help initialize a bulk urb&n; * @urb: pointer to the urb to initialize.&n; * @dev: pointer to the struct usb_device for this urb.&n; * @pipe: the endpoint pipe&n; * @transfer_buffer: pointer to the transfer buffer&n; * @buffer_length: length of the transfer buffer&n; * @complete: pointer to the usb_complete_t function&n; * @context: what to set the urb context to.&n; *&n; * Initializes a bulk urb with the proper information needed to submit it&n; * to a device.&n; */
DECL|function|usb_fill_bulk_urb
r_static
r_inline
r_void
id|usb_fill_bulk_urb
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|transfer_buffer
comma
r_int
id|buffer_length
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|urb-&gt;lock
)paren
suffix:semicolon
id|urb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|pipe
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|transfer_buffer
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|buffer_length
suffix:semicolon
id|urb-&gt;complete
op_assign
id|complete
suffix:semicolon
id|urb-&gt;context
op_assign
id|context
suffix:semicolon
)brace
multiline_comment|/**&n; * usb_fill_int_urb - macro to help initialize a interrupt urb&n; * @urb: pointer to the urb to initialize.&n; * @dev: pointer to the struct usb_device for this urb.&n; * @pipe: the endpoint pipe&n; * @transfer_buffer: pointer to the transfer buffer&n; * @buffer_length: length of the transfer buffer&n; * @complete: pointer to the usb_complete_t function&n; * @context: what to set the urb context to.&n; * @interval: what to set the urb interval to, encoded like&n; *&t;the endpoint descriptor&squot;s bInterval value.&n; *&n; * Initializes a interrupt urb with the proper information needed to submit&n; * it to a device.&n; * Note that high speed interrupt endpoints use a logarithmic encoding of&n; * the endpoint interval, and express polling intervals in microframes&n; * (eight per millisecond) rather than in frames (one per millisecond).&n; */
DECL|function|usb_fill_int_urb
r_static
r_inline
r_void
id|usb_fill_int_urb
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|transfer_buffer
comma
r_int
id|buffer_length
comma
id|usb_complete_t
id|complete
comma
r_void
op_star
id|context
comma
r_int
id|interval
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|urb-&gt;lock
)paren
suffix:semicolon
id|urb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|pipe
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|transfer_buffer
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|buffer_length
suffix:semicolon
id|urb-&gt;complete
op_assign
id|complete
suffix:semicolon
id|urb-&gt;context
op_assign
id|context
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;speed
op_eq
id|USB_SPEED_HIGH
)paren
id|urb-&gt;interval
op_assign
l_int|1
op_lshift
(paren
id|interval
op_minus
l_int|1
)paren
suffix:semicolon
r_else
id|urb-&gt;interval
op_assign
id|interval
suffix:semicolon
id|urb-&gt;start_frame
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * old style macros to enable 2.4 and 2.2 drivers to build&n; * properly.  Please do not use these for new USB drivers.&n; */
DECL|macro|FILL_CONTROL_URB
mdefine_line|#define FILL_CONTROL_URB(URB,DEV,PIPE,SETUP_PACKET,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT) &bslash;&n;    usb_fill_control_urb(URB,DEV,PIPE,SETUP_PACKET,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT)
DECL|macro|FILL_BULK_URB
mdefine_line|#define FILL_BULK_URB(URB,DEV,PIPE,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT) &bslash;&n;    usb_fill_bulk_urb(URB,DEV,PIPE,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT)
DECL|macro|FILL_INT_URB
mdefine_line|#define FILL_INT_URB(URB,DEV,PIPE,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT,INTERVAL) &bslash;&n;    usb_fill_int_urb(URB,DEV,PIPE,TRANSFER_BUFFER,BUFFER_LENGTH,COMPLETE,CONTEXT,INTERVAL)
r_extern
r_struct
id|urb
op_star
id|usb_alloc_urb
c_func
(paren
r_int
id|iso_packets
comma
r_int
id|mem_flags
)paren
suffix:semicolon
r_extern
r_void
id|usb_free_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|macro|usb_put_urb
mdefine_line|#define usb_put_urb usb_free_urb
r_extern
r_struct
id|urb
op_star
id|usb_get_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_extern
r_int
id|usb_submit_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mem_flags
)paren
suffix:semicolon
r_extern
r_int
id|usb_unlink_urb
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------*&n; *                         SYNCHRONOUS CALL SUPPORT                  *&n; *-------------------------------------------------------------------*/
r_extern
r_int
id|usb_control_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|pipe
comma
id|__u8
id|request
comma
id|__u8
id|requesttype
comma
id|__u16
id|value
comma
id|__u16
id|index
comma
r_void
op_star
id|data
comma
id|__u16
id|size
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|usb_bulk_msg
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_int
op_star
id|actual_length
comma
r_int
id|timeout
)paren
suffix:semicolon
multiline_comment|/* wrappers around usb_control_msg() for the most common standard requests */
r_extern
r_int
id|usb_clear_halt
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|pipe
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_char
id|desctype
comma
r_int
r_char
id|descindex
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_device_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_status
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|type
comma
r_int
id|target
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|langid
comma
r_int
r_char
id|index
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|usb_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|index
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|usb_set_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|configuration
)paren
suffix:semicolon
r_extern
r_int
id|usb_set_interface
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|ifnum
comma
r_int
id|alternate
)paren
suffix:semicolon
multiline_comment|/*&n; * timeouts, in seconds, used for sending/receiving control messages&n; * they typically complete within a few frames (msec) after they&squot;re issued&n; */
macro_line|#ifdef CONFIG_USB_LONG_TIMEOUT
DECL|macro|USB_CTRL_GET_TIMEOUT
mdefine_line|#define USB_CTRL_GET_TIMEOUT 4
macro_line|#else
DECL|macro|USB_CTRL_GET_TIMEOUT
mdefine_line|#define USB_CTRL_GET_TIMEOUT 3
macro_line|#endif
DECL|macro|USB_CTRL_SET_TIMEOUT
mdefine_line|#define USB_CTRL_SET_TIMEOUT 3
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/*&n; * Calling this entity a &quot;pipe&quot; is glorifying it. A USB pipe&n; * is something embarrassingly simple: it basically consists&n; * of the following information:&n; *  - device number (7 bits)&n; *  - endpoint number (4 bits)&n; *  - current Data0/1 state (1 bit) [Historical; now gone]&n; *  - direction (1 bit)&n; *  - speed (1 bit) [Historical and specific to USB 1.1; now gone.]&n; *  - max packet size (2 bits: 8, 16, 32 or 64) [Historical; now gone.]&n; *  - pipe type (2 bits: control, interrupt, bulk, isochronous)&n; *&n; * That&squot;s 18 bits. Really. Nothing more. And the USB people have&n; * documented these eighteen bits as some kind of glorious&n; * virtual data structure.&n; *&n; * Let&squot;s not fall in that trap. We&squot;ll just encode it as a simple&n; * unsigned int. The encoding is:&n; *&n; *  - max size:&t;&t;bits 0-1&t;[Historical; now gone.]&n; *  - direction:&t;bit 7&t;&t;(0 = Host-to-Device [Out],&n; *&t;&t;&t;&t;&t; 1 = Device-to-Host [In])&n; *  - device:&t;&t;bits 8-14&n; *  - endpoint:&t;&t;bits 15-18&n; *  - Data0/1:&t;&t;bit 19&t;&t;[Historical; now gone. ]&n; *  - lowspeed:&t;&t;bit 26&t;&t;[Historical; now gone. ]&n; *  - pipe type:&t;bits 30-31&t;(00 = isochronous, 01 = interrupt,&n; *&t;&t;&t;&t;&t; 10 = control, 11 = bulk)&n; *&n; * Why? Because it&squot;s arbitrary, and whatever encoding we select is really&n; * up to us. This one happens to share a lot of bit positions with the UHCI&n; * specification, so that much of the uhci driver can just mask the bits&n; * appropriately.&n; */
multiline_comment|/* NOTE:  these are not the standard USB_ENDPOINT_XFER_* values!! */
DECL|macro|PIPE_ISOCHRONOUS
mdefine_line|#define PIPE_ISOCHRONOUS&t;&t;0
DECL|macro|PIPE_INTERRUPT
mdefine_line|#define PIPE_INTERRUPT&t;&t;&t;1
DECL|macro|PIPE_CONTROL
mdefine_line|#define PIPE_CONTROL&t;&t;&t;2
DECL|macro|PIPE_BULK
mdefine_line|#define PIPE_BULK&t;&t;&t;3
DECL|macro|usb_maxpacket
mdefine_line|#define usb_maxpacket(dev, pipe, out)&t;(out &bslash;&n;&t;&t;&t;&t;? (dev)-&gt;epmaxpacketout[usb_pipeendpoint(pipe)] &bslash;&n;&t;&t;&t;&t;: (dev)-&gt;epmaxpacketin [usb_pipeendpoint(pipe)] )
DECL|macro|usb_packetid
mdefine_line|#define usb_packetid(pipe)&t;(((pipe) &amp; USB_DIR_IN) ? USB_PID_IN : USB_PID_OUT)
DECL|macro|usb_pipeout
mdefine_line|#define usb_pipeout(pipe)&t;((((pipe) &gt;&gt; 7) &amp; 1) ^ 1)
DECL|macro|usb_pipein
mdefine_line|#define usb_pipein(pipe)&t;(((pipe) &gt;&gt; 7) &amp; 1)
DECL|macro|usb_pipedevice
mdefine_line|#define usb_pipedevice(pipe)&t;(((pipe) &gt;&gt; 8) &amp; 0x7f)
DECL|macro|usb_pipeendpoint
mdefine_line|#define usb_pipeendpoint(pipe)&t;(((pipe) &gt;&gt; 15) &amp; 0xf)
DECL|macro|usb_pipetype
mdefine_line|#define usb_pipetype(pipe)&t;(((pipe) &gt;&gt; 30) &amp; 3)
DECL|macro|usb_pipeisoc
mdefine_line|#define usb_pipeisoc(pipe)&t;(usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
DECL|macro|usb_pipeint
mdefine_line|#define usb_pipeint(pipe)&t;(usb_pipetype((pipe)) == PIPE_INTERRUPT)
DECL|macro|usb_pipecontrol
mdefine_line|#define usb_pipecontrol(pipe)&t;(usb_pipetype((pipe)) == PIPE_CONTROL)
DECL|macro|usb_pipebulk
mdefine_line|#define usb_pipebulk(pipe)&t;(usb_pipetype((pipe)) == PIPE_BULK)
DECL|macro|PIPE_DEVEP_MASK
mdefine_line|#define PIPE_DEVEP_MASK&t;&t;0x0007ff00
multiline_comment|/* The D0/D1 toggle bits */
DECL|macro|usb_gettoggle
mdefine_line|#define usb_gettoggle(dev, ep, out) (((dev)-&gt;toggle[out] &gt;&gt; (ep)) &amp; 1)
DECL|macro|usb_dotoggle
mdefine_line|#define&t;usb_dotoggle(dev, ep, out)  ((dev)-&gt;toggle[out] ^= (1 &lt;&lt; (ep)))
DECL|macro|usb_settoggle
mdefine_line|#define usb_settoggle(dev, ep, out, bit) ((dev)-&gt;toggle[out] = ((dev)-&gt;toggle[out] &amp; ~(1 &lt;&lt; (ep))) | ((bit) &lt;&lt; (ep)))
multiline_comment|/* Endpoint halt control/status */
DECL|macro|usb_endpoint_out
mdefine_line|#define usb_endpoint_out(ep_dir)&t;((((ep_dir) &gt;&gt; 7) &amp; 1) ^ 1)
DECL|macro|usb_endpoint_halt
mdefine_line|#define usb_endpoint_halt(dev, ep, out) ((dev)-&gt;halted[out] |= (1 &lt;&lt; (ep)))
DECL|macro|usb_endpoint_running
mdefine_line|#define usb_endpoint_running(dev, ep, out) ((dev)-&gt;halted[out] &amp;= ~(1 &lt;&lt; (ep)))
DECL|macro|usb_endpoint_halted
mdefine_line|#define usb_endpoint_halted(dev, ep, out) ((dev)-&gt;halted[out] &amp; (1 &lt;&lt; (ep)))
DECL|function|__create_pipe
r_static
r_inline
r_int
r_int
id|__create_pipe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|endpoint
)paren
(brace
r_return
(paren
id|dev-&gt;devnum
op_lshift
l_int|8
)paren
op_or
(paren
id|endpoint
op_lshift
l_int|15
)paren
suffix:semicolon
)brace
multiline_comment|/* Create various pipes... */
DECL|macro|usb_sndctrlpipe
mdefine_line|#define usb_sndctrlpipe(dev,endpoint)&t;((PIPE_CONTROL &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvctrlpipe
mdefine_line|#define usb_rcvctrlpipe(dev,endpoint)&t;((PIPE_CONTROL &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndisocpipe
mdefine_line|#define usb_sndisocpipe(dev,endpoint)&t;((PIPE_ISOCHRONOUS &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvisocpipe
mdefine_line|#define usb_rcvisocpipe(dev,endpoint)&t;((PIPE_ISOCHRONOUS &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndbulkpipe
mdefine_line|#define usb_sndbulkpipe(dev,endpoint)&t;((PIPE_BULK &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvbulkpipe
mdefine_line|#define usb_rcvbulkpipe(dev,endpoint)&t;((PIPE_BULK &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_sndintpipe
mdefine_line|#define usb_sndintpipe(dev,endpoint)&t;((PIPE_INTERRUPT &lt;&lt; 30) | __create_pipe(dev,endpoint))
DECL|macro|usb_rcvintpipe
mdefine_line|#define usb_rcvintpipe(dev,endpoint)&t;((PIPE_INTERRUPT &lt;&lt; 30) | __create_pipe(dev,endpoint) | USB_DIR_IN)
DECL|macro|usb_snddefctrl
mdefine_line|#define usb_snddefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30))
DECL|macro|usb_rcvdefctrl
mdefine_line|#define usb_rcvdefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30) | USB_DIR_IN)
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/*&n; * Debugging and troubleshooting/diagnostic helpers.&n; */
r_void
id|usb_show_device_descriptor
c_func
(paren
r_struct
id|usb_device_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_config_descriptor
c_func
(paren
r_struct
id|usb_config_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_interface_descriptor
c_func
(paren
r_struct
id|usb_interface_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_endpoint_descriptor
c_func
(paren
r_struct
id|usb_endpoint_descriptor
op_star
)paren
suffix:semicolon
r_void
id|usb_show_device
c_func
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
r_void
id|usb_show_string
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_char
op_star
id|id
comma
r_int
id|index
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
macro_line|#else
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do {} while (0)
macro_line|#endif
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/*&n; * driver list&n; * exported only for usbfs (not visible outside usbcore)&n; */
r_extern
r_struct
id|list_head
id|usb_driver_list
suffix:semicolon
multiline_comment|/*&n; * USB device fs stuff&n; */
macro_line|#ifdef CONFIG_USB_DEVICEFS
multiline_comment|/*&n; * these are expected to be called from the USB core/hub thread&n; * with the kernel lock held&n; */
r_extern
r_void
id|usbfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_update_special
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|usbfs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_USB_DEVICEFS */
DECL|function|usbfs_add_bus
r_static
r_inline
r_void
id|usbfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbfs_remove_bus
r_static
r_inline
r_void
id|usbfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbfs_add_device
r_static
r_inline
r_void
id|usbfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbfs_remove_device
r_static
r_inline
r_void
id|usbfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbfs_update_special
r_static
r_inline
r_void
id|usbfs_update_special
(paren
r_void
)paren
(brace
)brace
DECL|function|usbfs_init
r_static
r_inline
r_int
id|usbfs_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usbfs_cleanup
r_static
r_inline
r_void
id|usbfs_cleanup
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_USB_DEVICEFS */
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif
eof
