multiline_comment|/*&n; * Generic IEEE 1394 definitions&n; */
macro_line|#ifndef _IEEE1394_IEEE1394_H
DECL|macro|_IEEE1394_IEEE1394_H
mdefine_line|#define _IEEE1394_IEEE1394_H
DECL|macro|TCODE_WRITEQ
mdefine_line|#define TCODE_WRITEQ             0x0
DECL|macro|TCODE_WRITEB
mdefine_line|#define TCODE_WRITEB             0x1
DECL|macro|TCODE_WRITE_RESPONSE
mdefine_line|#define TCODE_WRITE_RESPONSE     0x2
DECL|macro|TCODE_READQ
mdefine_line|#define TCODE_READQ              0x4
DECL|macro|TCODE_READB
mdefine_line|#define TCODE_READB              0x5
DECL|macro|TCODE_READQ_RESPONSE
mdefine_line|#define TCODE_READQ_RESPONSE     0x6
DECL|macro|TCODE_READB_RESPONSE
mdefine_line|#define TCODE_READB_RESPONSE     0x7
DECL|macro|TCODE_CYCLE_START
mdefine_line|#define TCODE_CYCLE_START        0x8
DECL|macro|TCODE_LOCK_REQUEST
mdefine_line|#define TCODE_LOCK_REQUEST       0x9
DECL|macro|TCODE_ISO_DATA
mdefine_line|#define TCODE_ISO_DATA           0xa
DECL|macro|TCODE_LOCK_RESPONSE
mdefine_line|#define TCODE_LOCK_RESPONSE      0xb
DECL|macro|RCODE_COMPLETE
mdefine_line|#define RCODE_COMPLETE           0x0
DECL|macro|RCODE_CONFLICT_ERROR
mdefine_line|#define RCODE_CONFLICT_ERROR     0x4
DECL|macro|RCODE_DATA_ERROR
mdefine_line|#define RCODE_DATA_ERROR         0x5
DECL|macro|RCODE_TYPE_ERROR
mdefine_line|#define RCODE_TYPE_ERROR         0x6
DECL|macro|RCODE_ADDRESS_ERROR
mdefine_line|#define RCODE_ADDRESS_ERROR      0x7
DECL|macro|EXTCODE_MASK_SWAP
mdefine_line|#define EXTCODE_MASK_SWAP        0x1
DECL|macro|EXTCODE_COMPARE_SWAP
mdefine_line|#define EXTCODE_COMPARE_SWAP     0x2
DECL|macro|EXTCODE_FETCH_ADD
mdefine_line|#define EXTCODE_FETCH_ADD        0x3
DECL|macro|EXTCODE_LITTLE_ADD
mdefine_line|#define EXTCODE_LITTLE_ADD       0x4
DECL|macro|EXTCODE_BOUNDED_ADD
mdefine_line|#define EXTCODE_BOUNDED_ADD      0x5
DECL|macro|EXTCODE_WRAP_ADD
mdefine_line|#define EXTCODE_WRAP_ADD         0x6
DECL|macro|ACK_COMPLETE
mdefine_line|#define ACK_COMPLETE             0x1
DECL|macro|ACK_PENDING
mdefine_line|#define ACK_PENDING              0x2
DECL|macro|ACK_BUSY_X
mdefine_line|#define ACK_BUSY_X               0x4
DECL|macro|ACK_BUSY_A
mdefine_line|#define ACK_BUSY_A               0x5
DECL|macro|ACK_BUSY_B
mdefine_line|#define ACK_BUSY_B               0x6
DECL|macro|ACK_DATA_ERROR
mdefine_line|#define ACK_DATA_ERROR           0xd
DECL|macro|ACK_TYPE_ERROR
mdefine_line|#define ACK_TYPE_ERROR           0xe 
multiline_comment|/* Non-standard &quot;ACK codes&quot; for internal use */
DECL|macro|ACKX_NONE
mdefine_line|#define ACKX_NONE                -1
DECL|macro|ACKX_SEND_ERROR
mdefine_line|#define ACKX_SEND_ERROR          -2
DECL|macro|ACKX_ABORTED
mdefine_line|#define ACKX_ABORTED             -3
DECL|macro|ACKX_TIMEOUT
mdefine_line|#define ACKX_TIMEOUT             -4
DECL|macro|SPEED_100
mdefine_line|#define SPEED_100                0x0
DECL|macro|SPEED_200
mdefine_line|#define SPEED_200                0x1
DECL|macro|SPEED_400
mdefine_line|#define SPEED_400                0x2 
DECL|macro|SELFID_PWRCL_NO_POWER
mdefine_line|#define SELFID_PWRCL_NO_POWER    0x0
DECL|macro|SELFID_PWRCL_PROVIDE_15W
mdefine_line|#define SELFID_PWRCL_PROVIDE_15W 0x1
DECL|macro|SELFID_PWRCL_PROVIDE_30W
mdefine_line|#define SELFID_PWRCL_PROVIDE_30W 0x2
DECL|macro|SELFID_PWRCL_PROVIDE_45W
mdefine_line|#define SELFID_PWRCL_PROVIDE_45W 0x3
DECL|macro|SELFID_PWRCL_USE_1W
mdefine_line|#define SELFID_PWRCL_USE_1W      0x4
DECL|macro|SELFID_PWRCL_USE_3W
mdefine_line|#define SELFID_PWRCL_USE_3W      0x5
DECL|macro|SELFID_PWRCL_USE_6W
mdefine_line|#define SELFID_PWRCL_USE_6W      0x6
DECL|macro|SELFID_PWRCL_USE_10W
mdefine_line|#define SELFID_PWRCL_USE_10W     0x7
DECL|macro|SELFID_PORT_CHILD
mdefine_line|#define SELFID_PORT_CHILD        0x3
DECL|macro|SELFID_PORT_PARENT
mdefine_line|#define SELFID_PORT_PARENT       0x2
DECL|macro|SELFID_PORT_NCONN
mdefine_line|#define SELFID_PORT_NCONN        0x1
DECL|macro|SELFID_PORT_NONE
mdefine_line|#define SELFID_PORT_NONE         0x0   
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef __BIG_ENDIAN_BITFIELD
DECL|struct|selfid
r_struct
id|selfid
(brace
DECL|member|packet_identifier
id|u32
id|packet_identifier
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* always binary 10 */
DECL|member|phy_id
id|u32
id|phy_id
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* byte */
DECL|member|extended
id|u32
id|extended
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if true is struct ext_selfid */
DECL|member|link_active
id|u32
id|link_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|gap_count
id|u32
id|gap_count
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* byte */
DECL|member|speed
id|u32
id|speed
suffix:colon
l_int|2
suffix:semicolon
DECL|member|phy_delay
id|u32
id|phy_delay
suffix:colon
l_int|2
suffix:semicolon
DECL|member|contender
id|u32
id|contender
suffix:colon
l_int|1
suffix:semicolon
DECL|member|power_class
id|u32
id|power_class
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* byte */
DECL|member|port0
id|u32
id|port0
suffix:colon
l_int|2
suffix:semicolon
DECL|member|port1
id|u32
id|port1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|port2
id|u32
id|port2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|initiated_reset
id|u32
id|initiated_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|more_packets
id|u32
id|more_packets
suffix:colon
l_int|1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ext_selfid
r_struct
id|ext_selfid
(brace
DECL|member|packet_identifier
id|u32
id|packet_identifier
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* always binary 10 */
DECL|member|phy_id
id|u32
id|phy_id
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* byte */
DECL|member|extended
id|u32
id|extended
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if false is struct selfid */
DECL|member|seq_nr
id|u32
id|seq_nr
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|porta
id|u32
id|porta
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte */
DECL|member|portb
id|u32
id|portb
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portc
id|u32
id|portc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portd
id|u32
id|portd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|porte
id|u32
id|porte
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte */
DECL|member|portf
id|u32
id|portf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portg
id|u32
id|portg
suffix:colon
l_int|2
suffix:semicolon
DECL|member|porth
id|u32
id|porth
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|more_packets
id|u32
id|more_packets
suffix:colon
l_int|1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#elif defined __LITTLE_ENDIAN_BITFIELD /* __BIG_ENDIAN_BITFIELD */
multiline_comment|/*&n; * Note: these mean to be bit fields of a big endian SelfID as seen on a little&n; * endian machine.&n; */
DECL|struct|selfid
r_struct
id|selfid
(brace
DECL|member|phy_id
id|u32
id|phy_id
suffix:colon
l_int|6
suffix:semicolon
DECL|member|packet_identifier
id|u32
id|packet_identifier
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* always binary 10 */
multiline_comment|/* byte */
DECL|member|gap_count
id|u32
id|gap_count
suffix:colon
l_int|6
suffix:semicolon
DECL|member|link_active
id|u32
id|link_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|extended
id|u32
id|extended
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if true is struct ext_selfid */
multiline_comment|/* byte */
DECL|member|power_class
id|u32
id|power_class
suffix:colon
l_int|3
suffix:semicolon
DECL|member|contender
id|u32
id|contender
suffix:colon
l_int|1
suffix:semicolon
DECL|member|phy_delay
id|u32
id|phy_delay
suffix:colon
l_int|2
suffix:semicolon
DECL|member|speed
id|u32
id|speed
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte */
DECL|member|more_packets
id|u32
id|more_packets
suffix:colon
l_int|1
suffix:semicolon
DECL|member|initiated_reset
id|u32
id|initiated_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|port2
id|u32
id|port2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|port1
id|u32
id|port1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|port0
id|u32
id|port0
suffix:colon
l_int|2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ext_selfid
r_struct
id|ext_selfid
(brace
DECL|member|phy_id
id|u32
id|phy_id
suffix:colon
l_int|6
suffix:semicolon
DECL|member|packet_identifier
id|u32
id|packet_identifier
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* always binary 10 */
multiline_comment|/* byte */
DECL|member|porta
id|u32
id|porta
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|seq_nr
id|u32
id|seq_nr
suffix:colon
l_int|3
suffix:semicolon
DECL|member|extended
id|u32
id|extended
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if false is struct selfid */
multiline_comment|/* byte */
DECL|member|porte
id|u32
id|porte
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portd
id|u32
id|portd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portc
id|u32
id|portc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portb
id|u32
id|portb
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte */
DECL|member|more_packets
id|u32
id|more_packets
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|porth
id|u32
id|porth
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portg
id|u32
id|portg
suffix:colon
l_int|2
suffix:semicolon
DECL|member|portf
id|u32
id|portf
suffix:colon
l_int|2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#error What? PDP endian?
macro_line|#endif /* __BIG_ENDIAN_BITFIELD */
macro_line|#endif /* _IEEE1394_IEEE1394_H */
eof
