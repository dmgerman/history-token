macro_line|#ifndef IEEE_802_11
DECL|macro|IEEE_802_11
mdefine_line|#define IEEE_802_11  
macro_line|#include &lt;linux/types.h&gt;
DECL|enum|ieee_802_11_link_status_failure_reason
r_enum
id|ieee_802_11_link_status_failure_reason
(brace
DECL|enumerator|reserved0
DECL|enumerator|Unspecified
DECL|enumerator|Previous_not_valid
id|reserved0
comma
id|Unspecified
op_assign
l_int|1
comma
id|Previous_not_valid
comma
DECL|enumerator|Sender_Quits_ESS_or_IBSS
id|Sender_Quits_ESS_or_IBSS
comma
DECL|enumerator|Due_Inactivity
DECL|enumerator|AP_Overload
id|Due_Inactivity
comma
id|AP_Overload
comma
DECL|enumerator|Class_2_from_NonAuth
id|Class_2_from_NonAuth
comma
DECL|enumerator|Class_3_from_NonAuth
id|Class_3_from_NonAuth
comma
DECL|enumerator|Sender_Quits_BSS
id|Sender_Quits_BSS
comma
DECL|enumerator|Association_requester_not_authenticated
id|Association_requester_not_authenticated
comma
DECL|enumerator|Reserved10
id|Reserved10
)brace
suffix:semicolon
DECL|macro|IEEE_802_11_LINK_STATUS_FAILURE_REASON_STRINGS
mdefine_line|#define IEEE_802_11_LINK_STATUS_FAILURE_REASON_STRINGS &bslash;&n;{&t;&bslash;&n;        {reserved0,&t;&t;0xff,&quot; Reserved reason &quot;},&bslash;&n;        {Unspecified,&t;&t;0xff,&quot; Unspecified Reason &quot;},&bslash;&n;        {Previous_not_valid,&t;0xff,&quot; Previous Authentication no longer valid &quot;},&bslash;&n;        {Sender_Quits_ESS_or_IBSS,0xff,&quot; Deauthenticated because sending station is leaving (has left) IBSS or ESS &quot;},&bslash;&n;        {Due_Inactivity,&t;0xff,&quot; Disassociated due to inactivity &quot;},&bslash;&n;        {AP_Overload,&t;&t;0xff,&quot; Disassociated because AP is unable to handle all currently associated stations &quot;},&bslash;&n;        {Class_2_from_NonAuth,&t;0xff,&quot; Class 2 frame received from non-Authenticated station&quot;},&bslash;&n;        {Class_3_from_NonAuth,&t;0xff,&quot; Class 3 frame received from non&#xfffd;Associated station&quot;},&bslash;&n;        {Sender_Quits_BSS,&t;0xff,&quot; Disassociated because sending station is leaving (has left) BSS&quot;},&bslash;&n;        {Association_requester_not_authenticated,0xff,&quot; Station requesting (Re)Association is not Authenticated with responding station&quot;},&bslash;&n;        {Reserved10,&t;&t;0xff,&quot; Reserved&quot;},&bslash;&n;&t;{0,0,NULL}&bslash;&n;};
DECL|struct|ieee_802_11_header
r_struct
id|ieee_802_11_header
(brace
DECL|member|frame_control
id|u16
id|frame_control
suffix:semicolon
singleline_comment|// needs to be subtyped
DECL|member|duration
id|u16
id|duration
suffix:semicolon
DECL|member|mac1
id|u8
id|mac1
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|mac2
id|u8
id|mac2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|mac3
id|u8
id|mac3
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|SeqCtl
id|u16
id|SeqCtl
suffix:semicolon
DECL|member|mac4
id|u8
id|mac4
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|gapLen
id|u16
id|gapLen
suffix:semicolon
DECL|member|gap
id|u8
id|gap
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ieee_802_3_header
r_struct
id|ieee_802_3_header
(brace
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|payload_length
id|u16
id|payload_length
suffix:semicolon
DECL|member|dst_mac
id|u8
id|dst_mac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|src_mac
id|u8
id|src_mac
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|P80211_OUI_LEN
mdefine_line|#define P80211_OUI_LEN 3
DECL|struct|ieee_802_11_snap_header
r_struct
id|ieee_802_11_snap_header
(brace
DECL|member|dsap
id|u8
id|dsap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ssap
id|u8
id|ssap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ctrl
id|u8
id|ctrl
suffix:semicolon
multiline_comment|/* always 0x03 */
DECL|member|oui
id|u8
id|oui
(braket
id|P80211_OUI_LEN
)braket
suffix:semicolon
multiline_comment|/* organizational universal id */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|P80211_LLC_OUI_LEN
mdefine_line|#define P80211_LLC_OUI_LEN 3
DECL|struct|ieee_802_11_802_1H_header
r_struct
id|ieee_802_11_802_1H_header
(brace
DECL|member|dsap
id|u8
id|dsap
suffix:semicolon
DECL|member|ssap
id|u8
id|ssap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ctrl
id|u8
id|ctrl
suffix:semicolon
multiline_comment|/* always 0x03 */
DECL|member|oui
id|u8
id|oui
(braket
id|P80211_OUI_LEN
)braket
suffix:semicolon
multiline_comment|/* organizational universal id */
DECL|member|unknown1
id|u16
id|unknown1
suffix:semicolon
multiline_comment|/* packet type ID fields */
DECL|member|unknown2
id|u16
id|unknown2
suffix:semicolon
multiline_comment|/* here is something like length in some cases */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ieee_802_11_802_2_header
r_struct
id|ieee_802_11_802_2_header
(brace
DECL|member|dsap
id|u8
id|dsap
suffix:semicolon
DECL|member|ssap
id|u8
id|ssap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ctrl
id|u8
id|ctrl
suffix:semicolon
multiline_comment|/* always 0x03 */
DECL|member|oui
id|u8
id|oui
(braket
id|P80211_OUI_LEN
)braket
suffix:semicolon
multiline_comment|/* organizational universal id */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* packet type ID field. i guess,  */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
singleline_comment|// following is incoplete and may be incorrect and need reorganization
DECL|macro|ieee_802_11_frame_type_Management
mdefine_line|#define ieee_802_11_frame_type_Management&t;0x00
DECL|macro|ieee_802_11_frame_type_Control
mdefine_line|#define ieee_802_11_frame_type_Control&t;&t;0x01
DECL|macro|ieee_802_11_frame_type_Data
mdefine_line|#define ieee_802_11_frame_type_Data&t;&t;0x10
DECL|macro|ieee_802_11_frame_type_Reserved
mdefine_line|#define ieee_802_11_frame_type_Reserved&t;&t;0x11
DECL|macro|ieee_802_11_frame_subtype_Association_Req
mdefine_line|#define ieee_802_11_frame_subtype_Association_Req&t;0x0 
singleline_comment|// Association Request
DECL|macro|ieee_802_11_frame_subtype_Association_Resp
mdefine_line|#define ieee_802_11_frame_subtype_Association_Resp&t;0x1 
singleline_comment|// Association Response
DECL|macro|ieee_802_11_frame_subtype_Reassociation_Req
mdefine_line|#define ieee_802_11_frame_subtype_Reassociation_Req&t;0x2 
singleline_comment|// Reassociation Request
DECL|macro|ieee_802_11_frame_subtype_Reassociation_Resp
mdefine_line|#define ieee_802_11_frame_subtype_Reassociation_Resp&t;0x3 
singleline_comment|// Reassociation Response
DECL|macro|ieee_802_11_frame_subtype_Probe_Req
mdefine_line|#define ieee_802_11_frame_subtype_Probe_Req&t;&t;0x4 
singleline_comment|// Probe Request
DECL|macro|ieee_802_11_frame_subtype_Probe_Resp
mdefine_line|#define ieee_802_11_frame_subtype_Probe_Resp&t;&t;0x5 
singleline_comment|// Probe Response
DECL|macro|ieee_802_11_frame_subtype_Beacon
mdefine_line|#define ieee_802_11_frame_subtype_Beacon &t;&t;0x8 
singleline_comment|// Beacon
DECL|macro|ieee_802_11_frame_subtype_ATIM
mdefine_line|#define ieee_802_11_frame_subtype_ATIM &t;&t;&t;0x9 
singleline_comment|// ATIM
DECL|macro|ieee_802_11_frame_subtype_Disassociation
mdefine_line|#define ieee_802_11_frame_subtype_Disassociation &t;0xA 
singleline_comment|// Disassociation
DECL|macro|ieee_802_11_frame_subtype_Authentication
mdefine_line|#define ieee_802_11_frame_subtype_Authentication &t;0xB 
singleline_comment|// Authentication
DECL|macro|ieee_802_11_frame_subtype_Deauthentication
mdefine_line|#define ieee_802_11_frame_subtype_Deauthentication &t;0xC 
singleline_comment|// Deauthentication
DECL|macro|ieee_802_11_frame_subtype_PS_Poll
mdefine_line|#define ieee_802_11_frame_subtype_PS_Poll &t;&t;0xA 
singleline_comment|// PS-Poll
DECL|macro|ieee_802_11_frame_subtype_RTS
mdefine_line|#define ieee_802_11_frame_subtype_RTS &t;&t;&t;0xB 
singleline_comment|// RTS
DECL|macro|ieee_802_11_frame_subtype_CTS
mdefine_line|#define ieee_802_11_frame_subtype_CTS &t;&t;&t;0xC 
singleline_comment|// CTS
DECL|macro|ieee_802_11_frame_subtype_ACK
mdefine_line|#define ieee_802_11_frame_subtype_ACK &t;&t;&t;0xD 
singleline_comment|// ACK
DECL|macro|ieee_802_11_frame_subtype_CFEnd
mdefine_line|#define ieee_802_11_frame_subtype_CFEnd &t;&t;0xE 
singleline_comment|// CF-End
DECL|macro|ieee_802_11_frame_subtype_CFEnd_CFAck
mdefine_line|#define ieee_802_11_frame_subtype_CFEnd_CFAck &t;&t;0xF 
singleline_comment|// CF-End + CF-Ack
DECL|macro|ieee_802_11_frame_subtype_Data
mdefine_line|#define ieee_802_11_frame_subtype_Data &t;&t;&t;0x0 
singleline_comment|// Data
DECL|macro|ieee_802_11_frame_subtype_Data_CFAck
mdefine_line|#define ieee_802_11_frame_subtype_Data_CFAck &t;&t;0x1 
singleline_comment|// Data + CF-Ack
DECL|macro|ieee_802_11_frame_subtype_Data_CF_Poll
mdefine_line|#define ieee_802_11_frame_subtype_Data_CF_Poll &t;&t;0x2 
singleline_comment|// Data + CF-Poll
DECL|macro|ieee_802_11_frame_subtype_Data_CF_AckCF_Poll
mdefine_line|#define ieee_802_11_frame_subtype_Data_CF_AckCF_Poll &t;0x3 
singleline_comment|// Data + CF-Ack + CF-Poll
DECL|macro|ieee_802_11_frame_subtype_NullFunction
mdefine_line|#define ieee_802_11_frame_subtype_NullFunction &t;&t;0x4 
singleline_comment|// Null Function (no data)
DECL|macro|ieee_802_11_frame_subtype_CF_Ack
mdefine_line|#define ieee_802_11_frame_subtype_CF_Ack &t;&t;0x5 
singleline_comment|// CF-Ack (no data)
DECL|macro|ieee_802_11_frame_subtype_CF_Poll
mdefine_line|#define ieee_802_11_frame_subtype_CF_Poll &t;&t;0x6 
singleline_comment|// CF-Poll (no data)
DECL|macro|ieee_802_11_frame_subtype_CF_AckCF_Poll
mdefine_line|#define ieee_802_11_frame_subtype_CF_AckCF_Poll &t;0x7 
singleline_comment|// CF-Ack + CF-Poll (no data)
DECL|macro|ieee_802_11_frame_subtype_strings
mdefine_line|#define ieee_802_11_frame_subtype_strings {&bslash;&n;&t;{ ieee_802_11_frame_subtype_Association_Req,&t;0xF,&quot;f  Association Request&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Association_Resp,&t;0xF,&quot;1  Association Response&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Reassociation_Req,&t;0xF,&quot;2  Reassociation Request&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Reassociation_Resp,&t;0xF,&quot;3  Reassociation Response&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Probe_Req&t;,&t;0xF,&quot;4  Probe Request&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Probe_Resp&t;,&t;0xF,&quot;5  Probe Response&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Beacon &t;,&t;0xF,&quot;8  Beacon&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_ATIM &t;,&t;0xF,&quot;9  ATIM&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Disassociation,&t;0xF,&quot;A  Disassociation&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Authentication,&t;0xF,&quot;B  Authentication&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Deauthentication,&t;0xF,&quot;C  Deauthentication&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_PS_Poll &t;,&t;0xF,&quot;A  PS-Poll&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_RTS &t;,&t;0xF,&quot;B  RTS&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CTS &t;,&t;0xF,&quot;C  CTS&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_ACK &t;,&t;0xF,&quot;D  ACK&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFEnd&t;,&t;0xF,&quot;E  CF-End&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFEnd_CFAck ,&t;0xF,&quot;F  CF-End + CF-Ack&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data &t;,&t;0xF,&quot;0  Data&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CFAck &t;,&t;0xF,&quot;1  Data + CF-Ack&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CFPoll ,&t;0xF,&quot;2  Data + CF-Poll&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CFAck_CFPoll,&t;0xF,&quot;3  Data + CF-Ack + CF-Poll&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Null_Function ,&t;0xF,&quot;4  Null Function (no data)&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFAck ,&t;&t;0xF,&quot;5  CF-Ack (no data)&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFPoll ,&t;&t;0xF,&quot;6  CF-Poll (no data)&quot;},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFAck_CFPoll,&t;0xF,&quot;y7  CF-Ack + CF-Poll (no data)&quot;},&bslash;&n;&t;{ 0,0,NULL}&bslash;&n;}
DECL|struct|ieee_802_11_frame_subtype_class
r_struct
id|ieee_802_11_frame_subtype_class
(brace
DECL|member|subtype
id|u8
id|subtype
suffix:semicolon
DECL|member|mask
id|u8
id|mask
suffix:semicolon
DECL|member|class
id|u8
r_class
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ieee_802_11_frame_subtype_classes
mdefine_line|#define ieee_802_11_frame_subtype_classes {&bslash;&n;&t;{ ieee_802_11_frame_subtype_Association_Req,&t;0xF,2,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Association_Resp,&t;0xF,2,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Reassociation_Req,&t;0xF,2,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Reassociation_Resp,&t;0xF,2,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Probe_Req&t;,&t;0xF,1,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Probe_Resp&t;,&t;0xF,1,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Beacon &t;,&t;0xF,1,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_ATIM &t;,&t;0xF,1,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Disassociation,&t;0xF,2,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Authentication,&t;0xF,1,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Deauthentication,&t;0xF,3,ieee_802_11_frame_type_Management},&bslash;&n;&t;{ ieee_802_11_frame_subtype_PS-Poll &t;,&t;0xF,3,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_RTS &t;,&t;0xF,1,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CTS &t;,&t;0xF,1,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_ACK &t;,&t;0xF,1,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFEnd&t;,&t;0xF,1,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CFEnd_CFAck ,&t;0xF,1,ieee_802_11_frame_type_Control},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data &t;,&t;0xF,3,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CFAck &t;,&t;0xF,3,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CF_Poll &t;0xF,3,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_Data_CF_AckCF_Poll,&t;0xF,3,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_NullFunction &t;0xF,1,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CF_Ack ,&t;&t;0xF,1,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CF_Poll ,&t;&t;0xF,1,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ ieee_802_11_frame_subtype_CF_AckCF_Poll,&t;0xF,1,ieee_802_11_frame_type_Data},&bslash;&n;&t;{ 0,0,NULL}&bslash;&n;}
macro_line|#endif
eof
