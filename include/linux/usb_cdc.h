multiline_comment|/*&n; * USB Communications Device Class (CDC) definitions&n; *&n; * CDC says how to talk to lots of different types of network adapters,&n; * notably ethernet adapters and various modems.  It&squot;s used mostly with&n; * firmware based USB peripherals.&n; */
DECL|macro|USB_CDC_SUBCLASS_ACM
mdefine_line|#define USB_CDC_SUBCLASS_ACM&t;&t;&t;2
DECL|macro|USB_CDC_SUBCLASS_ETHERNET
mdefine_line|#define USB_CDC_SUBCLASS_ETHERNET&t;&t;6
DECL|macro|USB_CDC_PROTO_NONE
mdefine_line|#define USB_CDC_PROTO_NONE&t;&t;&t;0
DECL|macro|USB_CDC_ACM_PROTO_AT_V25TER
mdefine_line|#define USB_CDC_ACM_PROTO_AT_V25TER&t;&t;1
DECL|macro|USB_CDC_ACM_PROTO_AT_PCCA101
mdefine_line|#define USB_CDC_ACM_PROTO_AT_PCCA101&t;&t;2
DECL|macro|USB_CDC_ACM_PROTO_AT_PCCA101_WAKE
mdefine_line|#define USB_CDC_ACM_PROTO_AT_PCCA101_WAKE&t;3
DECL|macro|USB_CDC_ACM_PROTO_AT_GSM
mdefine_line|#define USB_CDC_ACM_PROTO_AT_GSM&t;&t;4
DECL|macro|USB_CDC_ACM_PROTO_AT_3G
mdefine_line|#define USB_CDC_ACM_PROTO_AT_3G&t;&t;&t;5
DECL|macro|USB_CDC_ACM_PROTO_AT_CDMA
mdefine_line|#define USB_CDC_ACM_PROTO_AT_CDMA&t;&t;6
DECL|macro|USB_CDC_ACM_PROTO_VENDOR
mdefine_line|#define USB_CDC_ACM_PROTO_VENDOR&t;&t;0xff
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Class-Specific descriptors ... there are a couple dozen of them&n; */
DECL|macro|USB_CDC_HEADER_TYPE
mdefine_line|#define USB_CDC_HEADER_TYPE&t;&t;0x00&t;&t;/* header_desc */
DECL|macro|USB_CDC_CALL_MANAGEMENT_TYPE
mdefine_line|#define USB_CDC_CALL_MANAGEMENT_TYPE&t;0x01&t;&t;/* call_mgmt_descriptor */
DECL|macro|USB_CDC_ACM_TYPE
mdefine_line|#define USB_CDC_ACM_TYPE&t;&t;0x02&t;&t;/* acm_descriptor */
DECL|macro|USB_CDC_UNION_TYPE
mdefine_line|#define USB_CDC_UNION_TYPE&t;&t;0x06&t;&t;/* union_desc */
DECL|macro|USB_CDC_COUNTRY_TYPE
mdefine_line|#define USB_CDC_COUNTRY_TYPE&t;&t;0x07
DECL|macro|USB_CDC_ETHERNET_TYPE
mdefine_line|#define USB_CDC_ETHERNET_TYPE&t;&t;0x0f&t;&t;/* ether_desc */
multiline_comment|/* &quot;Header Functional Descriptor&quot; from CDC spec  5.2.3.1 */
DECL|struct|usb_cdc_header_desc
r_struct
id|usb_cdc_header_desc
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|__u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|bcdCDC
id|__le16
id|bcdCDC
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* &quot;Call Management Descriptor&quot; from CDC spec  5.2.3.2 */
DECL|struct|usb_cdc_call_mgmt_descriptor
r_struct
id|usb_cdc_call_mgmt_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|__u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|bmCapabilities
id|__u8
id|bmCapabilities
suffix:semicolon
DECL|macro|USB_CDC_CALL_MGMT_CAP_CALL_MGMT
mdefine_line|#define USB_CDC_CALL_MGMT_CAP_CALL_MGMT&t;&t;0x01
DECL|macro|USB_CDC_CALL_MGMT_CAP_DATA_INTF
mdefine_line|#define USB_CDC_CALL_MGMT_CAP_DATA_INTF&t;&t;0x02
DECL|member|bDataInterface
id|__u8
id|bDataInterface
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* &quot;Abstract Control Management Descriptor&quot; from CDC spec  5.2.3.3 */
DECL|struct|usb_cdc_acm_descriptor
r_struct
id|usb_cdc_acm_descriptor
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|__u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|bmCapabilities
id|__u8
id|bmCapabilities
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* &quot;Union Functional Descriptor&quot; from CDC spec 5.2.3.8 */
DECL|struct|usb_cdc_union_desc
r_struct
id|usb_cdc_union_desc
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|__u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|bMasterInterface0
id|__u8
id|bMasterInterface0
suffix:semicolon
DECL|member|bSlaveInterface0
id|__u8
id|bSlaveInterface0
suffix:semicolon
multiline_comment|/* ... and there could be other slave interfaces */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* &quot;Ethernet Networking Functional Descriptor&quot; from CDC spec 5.2.3.16 */
DECL|struct|usb_cdc_ether_desc
r_struct
id|usb_cdc_ether_desc
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|__u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|iMACAddress
id|__u8
id|iMACAddress
suffix:semicolon
DECL|member|bmEthernetStatistics
id|__le32
id|bmEthernetStatistics
suffix:semicolon
DECL|member|wMaxSegmentSize
id|__le16
id|wMaxSegmentSize
suffix:semicolon
DECL|member|wNumberMCFilters
id|__le16
id|wNumberMCFilters
suffix:semicolon
DECL|member|bNumberPowerFilters
id|__u8
id|bNumberPowerFilters
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
multiline_comment|/*&n; * Class-Specific Control Requests (6.2)&n; *&n; * section 3.6.2.1 table 4 has the ACM profile, for modems.&n; * section 3.8.2 table 10 has the ethernet profile.&n; *&n; * Microsoft&squot;s RNDIS stack for Ethernet is a vendor-specific CDC ACM variant,&n; * heavily dependent on the encapsulated (proprietary) command mechanism.&n; */
DECL|macro|USB_CDC_SEND_ENCAPSULATED_COMMAND
mdefine_line|#define USB_CDC_SEND_ENCAPSULATED_COMMAND&t;0x00
DECL|macro|USB_CDC_GET_ENCAPSULATED_RESPONSE
mdefine_line|#define USB_CDC_GET_ENCAPSULATED_RESPONSE&t;0x01
DECL|macro|USB_CDC_REQ_SET_LINE_CODING
mdefine_line|#define USB_CDC_REQ_SET_LINE_CODING&t;&t;0x20
DECL|macro|USB_CDC_REQ_GET_LINE_CODING
mdefine_line|#define USB_CDC_REQ_GET_LINE_CODING&t;&t;0x21
DECL|macro|USB_CDC_REQ_SET_CONTROL_LINE_STATE
mdefine_line|#define USB_CDC_REQ_SET_CONTROL_LINE_STATE&t;0x22
DECL|macro|USB_CDC_REQ_SEND_BREAK
mdefine_line|#define USB_CDC_REQ_SEND_BREAK&t;&t;&t;0x23
DECL|macro|USB_CDC_SET_ETHERNET_MULTICAST_FILTERS
mdefine_line|#define USB_CDC_SET_ETHERNET_MULTICAST_FILTERS&t;0x40
DECL|macro|USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER
mdefine_line|#define USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER&t;0x41
DECL|macro|USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER
mdefine_line|#define USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER&t;0x42
DECL|macro|USB_CDC_SET_ETHERNET_PACKET_FILTER
mdefine_line|#define USB_CDC_SET_ETHERNET_PACKET_FILTER&t;0x43
DECL|macro|USB_CDC_GET_ETHERNET_STATISTIC
mdefine_line|#define USB_CDC_GET_ETHERNET_STATISTIC&t;&t;0x44
multiline_comment|/* Line Coding Structure from CDC spec 6.2.13 */
DECL|struct|usb_cdc_line_coding
r_struct
id|usb_cdc_line_coding
(brace
DECL|member|dwDTERate
id|__le32
id|dwDTERate
suffix:semicolon
DECL|member|bCharFormat
id|__u8
id|bCharFormat
suffix:semicolon
DECL|macro|USB_CDC_1_STOP_BITS
mdefine_line|#define USB_CDC_1_STOP_BITS&t;&t;&t;0
DECL|macro|USB_CDC_1_5_STOP_BITS
mdefine_line|#define USB_CDC_1_5_STOP_BITS&t;&t;&t;1
DECL|macro|USB_CDC_2_STOP_BITS
mdefine_line|#define USB_CDC_2_STOP_BITS&t;&t;&t;2
DECL|member|bParityType
id|__u8
id|bParityType
suffix:semicolon
DECL|macro|USB_CDC_NO_PARITY
mdefine_line|#define USB_CDC_NO_PARITY&t;&t;&t;0
DECL|macro|USB_CDC_ODD_PARITY
mdefine_line|#define USB_CDC_ODD_PARITY&t;&t;&t;1
DECL|macro|USB_CDC_EVEN_PARITY
mdefine_line|#define USB_CDC_EVEN_PARITY&t;&t;&t;2
DECL|macro|USB_CDC_MARK_PARITY
mdefine_line|#define USB_CDC_MARK_PARITY&t;&t;&t;3
DECL|macro|USB_CDC_SPACE_PARITY
mdefine_line|#define USB_CDC_SPACE_PARITY&t;&t;&t;4
DECL|member|bDataBits
id|__u8
id|bDataBits
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* table 62; bits in multicast filter */
DECL|macro|USB_CDC_PACKET_TYPE_PROMISCUOUS
mdefine_line|#define&t;USB_CDC_PACKET_TYPE_PROMISCUOUS&t;&t;(1 &lt;&lt; 0)
DECL|macro|USB_CDC_PACKET_TYPE_ALL_MULTICAST
mdefine_line|#define&t;USB_CDC_PACKET_TYPE_ALL_MULTICAST&t;(1 &lt;&lt; 1) /* no filter */
DECL|macro|USB_CDC_PACKET_TYPE_DIRECTED
mdefine_line|#define&t;USB_CDC_PACKET_TYPE_DIRECTED&t;&t;(1 &lt;&lt; 2)
DECL|macro|USB_CDC_PACKET_TYPE_BROADCAST
mdefine_line|#define&t;USB_CDC_PACKET_TYPE_BROADCAST&t;&t;(1 &lt;&lt; 3)
DECL|macro|USB_CDC_PACKET_TYPE_MULTICAST
mdefine_line|#define&t;USB_CDC_PACKET_TYPE_MULTICAST&t;&t;(1 &lt;&lt; 4) /* filtered */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Class-Specific Notifications (6.3) sent by interrupt transfers&n; *&n; * section 3.8.2 table 11 of the CDC spec lists Ethernet notifications&n; * section 3.6.2.1 table 5 specifies ACM notifications, accepted by RNDIS&n; * RNDIS also defines its own bit-incompatible notifications&n; */
DECL|macro|USB_CDC_NOTIFY_NETWORK_CONNECTION
mdefine_line|#define USB_CDC_NOTIFY_NETWORK_CONNECTION&t;0x00
DECL|macro|USB_CDC_NOTIFY_RESPONSE_AVAILABLE
mdefine_line|#define USB_CDC_NOTIFY_RESPONSE_AVAILABLE&t;0x01
DECL|macro|USB_CDC_NOTIFY_SERIAL_STATE
mdefine_line|#define USB_CDC_NOTIFY_SERIAL_STATE&t;&t;0x20
DECL|macro|USB_CDC_NOTIFY_SPEED_CHANGE
mdefine_line|#define USB_CDC_NOTIFY_SPEED_CHANGE&t;&t;0x2a
DECL|struct|usb_cdc_notification
r_struct
id|usb_cdc_notification
(brace
DECL|member|bmRequestType
id|__u8
id|bmRequestType
suffix:semicolon
DECL|member|bNotificationType
id|__u8
id|bNotificationType
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
eof
