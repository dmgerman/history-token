multiline_comment|/* typhoon.h:&t;chip info for the 3Com 3CR990 family of controllers */
multiline_comment|/*&n;&t;Written 2002-2003 by David Dillow &lt;dave@thedillows.org&gt;&n;&n;&t;This software may be used and distributed according to the terms of&n;&t;the GNU General Public License (GPL), incorporated herein by reference.&n;&t;Drivers based on or derived from this code fall under the GPL and must&n;&t;retain the authorship, copyright and license notice.  This file is not&n;&t;a complete program and may only be used when the entire operating&n;&t;system is licensed under the GPL.&n;&n;&t;This software is available on a public web site. It may enable&n;&t;cryptographic capabilities of the 3Com hardware, and may be&n;&t;exported from the United States under License Exception &quot;TSU&quot;&n;&t;pursuant to 15 C.F.R. Section 740.13(e).&n;&n;&t;This work was funded by the National Library of Medicine under&n;&t;the Department of Energy project number 0274DD06D1 and NLM project&n;&t;number Y1-LM-2015-01.&n;*/
multiline_comment|/* All Typhoon ring positions are specificed in bytes, and point to the&n; * first &quot;clean&quot; entry in the ring -- ie the next entry we use for whatever&n; * purpose.&n; */
multiline_comment|/* The Typhoon basic ring&n; * ringBase:  where this ring lives (our virtual address)&n; * lastWrite: the next entry we&squot;ll use&n; */
DECL|struct|basic_ring
r_struct
id|basic_ring
(brace
DECL|member|ringBase
id|u8
op_star
id|ringBase
suffix:semicolon
DECL|member|lastWrite
id|u32
id|lastWrite
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The Typoon transmit ring -- same as a basic ring, plus:&n; * lastRead:      where we&squot;re at in regard to cleaning up the ring&n; * writeRegister: register to use for writing (different for Hi &amp; Lo rings)&n; */
DECL|struct|transmit_ring
r_struct
id|transmit_ring
(brace
DECL|member|ringBase
id|u8
op_star
id|ringBase
suffix:semicolon
DECL|member|lastWrite
id|u32
id|lastWrite
suffix:semicolon
DECL|member|lastRead
id|u32
id|lastRead
suffix:semicolon
DECL|member|writeRegister
r_int
id|writeRegister
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The host&lt;-&gt;Typhoon ring index structure&n; * This indicates the current positions in the rings&n; * &n; * All values must be in little endian format for the 3XP&n; *&n; * rxHiCleared:   entry we&squot;ve cleared to in the Hi receive ring&n; * rxLoCleared:   entry we&squot;ve cleared to in the Lo receive ring&n; * rxBuffReady:   next entry we&squot;ll put a free buffer in&n; * respCleared:   entry we&squot;ve cleared to in the response ring&n; *&n; * txLoCleared:   entry the NIC has cleared to in the Lo transmit ring&n; * txHiCleared:   entry the NIC has cleared to in the Hi transmit ring&n; * rxLoReady:     entry the NIC has filled to in the Lo receive ring&n; * rxBuffCleared: entry the NIC has cleared in the free buffer ring&n; * cmdCleared:    entry the NIC has cleared in the command ring&n; * respReady:     entry the NIC has filled to in the response ring&n; * rxHiReady:     entry the NIC has filled to in the Hi receive ring&n; */
DECL|struct|typhoon_indexes
r_struct
id|typhoon_indexes
(brace
multiline_comment|/* The first four are written by the host, and read by the NIC */
DECL|member|rxHiCleared
r_volatile
id|u32
id|rxHiCleared
suffix:semicolon
DECL|member|rxLoCleared
r_volatile
id|u32
id|rxLoCleared
suffix:semicolon
DECL|member|rxBuffReady
r_volatile
id|u32
id|rxBuffReady
suffix:semicolon
DECL|member|respCleared
r_volatile
id|u32
id|respCleared
suffix:semicolon
multiline_comment|/* The remaining are written by the NIC, and read by the host */
DECL|member|txLoCleared
r_volatile
id|u32
id|txLoCleared
suffix:semicolon
DECL|member|txHiCleared
r_volatile
id|u32
id|txHiCleared
suffix:semicolon
DECL|member|rxLoReady
r_volatile
id|u32
id|rxLoReady
suffix:semicolon
DECL|member|rxBuffCleared
r_volatile
id|u32
id|rxBuffCleared
suffix:semicolon
DECL|member|cmdCleared
r_volatile
id|u32
id|cmdCleared
suffix:semicolon
DECL|member|respReady
r_volatile
id|u32
id|respReady
suffix:semicolon
DECL|member|rxHiReady
r_volatile
id|u32
id|rxHiReady
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The host&lt;-&gt;Typhoon interface&n; * Our means of communicating where things are&n; *&n; * All values must be in little endian format for the 3XP&n; *&n; * ringIndex:   64 bit bus address of the index structure&n; * txLoAddr:    64 bit bus address of the Lo transmit ring&n; * txLoSize:    size (in bytes) of the Lo transmit ring&n; * txHi*:       as above for the Hi priority transmit ring&n; * rxLo*:       as above for the Lo priority receive ring&n; * rxBuff*:     as above for the free buffer ring&n; * cmd*:        as above for the command ring&n; * resp*:       as above for the response ring&n; * zeroAddr:    64 bit bus address of a zero word (for DMA)&n; * rxHi*:       as above for the Hi Priority receive ring&n; *&n; * While there is room for 64 bit addresses, current versions of the 3XP&n; * only do 32 bit addresses, so the *Hi for each of the above will always&n; * be zero.&n; */
DECL|struct|typhoon_interface
r_struct
id|typhoon_interface
(brace
DECL|member|ringIndex
id|u32
id|ringIndex
suffix:semicolon
DECL|member|ringIndexHi
id|u32
id|ringIndexHi
suffix:semicolon
DECL|member|txLoAddr
id|u32
id|txLoAddr
suffix:semicolon
DECL|member|txLoAddrHi
id|u32
id|txLoAddrHi
suffix:semicolon
DECL|member|txLoSize
id|u32
id|txLoSize
suffix:semicolon
DECL|member|txHiAddr
id|u32
id|txHiAddr
suffix:semicolon
DECL|member|txHiAddrHi
id|u32
id|txHiAddrHi
suffix:semicolon
DECL|member|txHiSize
id|u32
id|txHiSize
suffix:semicolon
DECL|member|rxLoAddr
id|u32
id|rxLoAddr
suffix:semicolon
DECL|member|rxLoAddrHi
id|u32
id|rxLoAddrHi
suffix:semicolon
DECL|member|rxLoSize
id|u32
id|rxLoSize
suffix:semicolon
DECL|member|rxBuffAddr
id|u32
id|rxBuffAddr
suffix:semicolon
DECL|member|rxBuffAddrHi
id|u32
id|rxBuffAddrHi
suffix:semicolon
DECL|member|rxBuffSize
id|u32
id|rxBuffSize
suffix:semicolon
DECL|member|cmdAddr
id|u32
id|cmdAddr
suffix:semicolon
DECL|member|cmdAddrHi
id|u32
id|cmdAddrHi
suffix:semicolon
DECL|member|cmdSize
id|u32
id|cmdSize
suffix:semicolon
DECL|member|respAddr
id|u32
id|respAddr
suffix:semicolon
DECL|member|respAddrHi
id|u32
id|respAddrHi
suffix:semicolon
DECL|member|respSize
id|u32
id|respSize
suffix:semicolon
DECL|member|zeroAddr
id|u32
id|zeroAddr
suffix:semicolon
DECL|member|zeroAddrHi
id|u32
id|zeroAddrHi
suffix:semicolon
DECL|member|rxHiAddr
id|u32
id|rxHiAddr
suffix:semicolon
DECL|member|rxHiAddrHi
id|u32
id|rxHiAddrHi
suffix:semicolon
DECL|member|rxHiSize
id|u32
id|rxHiSize
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon transmit/fragment descriptor&n; *&n; * A packet is described by a packet descriptor, followed by option descriptors,&n; * if any, then one or more fragment descriptors.&n; * &n; * Packet descriptor:&n; * flags:&t;Descriptor type&n; * len:i&t;zero, or length of this packet&n; * addr*:&t;8 bytes of opaque data to the firmware -- for skb pointer&n; * processFlags: Determine offload tasks to perform on this packet.&n; *&n; * Fragment descriptor:&n; * flags:&t;Descriptor type&n; * len:i&t;length of this fragment&n; * addr:&t;low bytes of DMA address for this part of the packet&n; * addrHi:&t;hi bytes of DMA address for this part of the packet&n; * processFlags: must be zero&n; *&n; * TYPHOON_DESC_VALID is not mentioned in their docs, but their Linux&n; * driver uses it.&n; */
DECL|struct|tx_desc
r_struct
id|tx_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|macro|TYPHOON_TYPE_MASK
mdefine_line|#define TYPHOON_TYPE_MASK&t;0x07
DECL|macro|TYPHOON_FRAG_DESC
mdefine_line|#define &t;TYPHOON_FRAG_DESC&t;0x00
DECL|macro|TYPHOON_TX_DESC
mdefine_line|#define &t;TYPHOON_TX_DESC&t;&t;0x01
DECL|macro|TYPHOON_CMD_DESC
mdefine_line|#define &t;TYPHOON_CMD_DESC&t;0x02
DECL|macro|TYPHOON_OPT_DESC
mdefine_line|#define &t;TYPHOON_OPT_DESC&t;0x03
DECL|macro|TYPHOON_RX_DESC
mdefine_line|#define &t;TYPHOON_RX_DESC&t;&t;0x04
DECL|macro|TYPHOON_RESP_DESC
mdefine_line|#define &t;TYPHOON_RESP_DESC&t;0x05
DECL|macro|TYPHOON_OPT_TYPE_MASK
mdefine_line|#define TYPHOON_OPT_TYPE_MASK&t;0xf0
DECL|macro|TYPHOON_OPT_IPSEC
mdefine_line|#define &t;TYPHOON_OPT_IPSEC&t;0x00
DECL|macro|TYPHOON_OPT_TCP_SEG
mdefine_line|#define &t;TYPHOON_OPT_TCP_SEG&t;0x10
DECL|macro|TYPHOON_CMD_RESPOND
mdefine_line|#define TYPHOON_CMD_RESPOND&t;0x40
DECL|macro|TYPHOON_RESP_ERROR
mdefine_line|#define TYPHOON_RESP_ERROR&t;0x40
DECL|macro|TYPHOON_RX_ERROR
mdefine_line|#define TYPHOON_RX_ERROR&t;0x40
DECL|macro|TYPHOON_DESC_VALID
mdefine_line|#define TYPHOON_DESC_VALID&t;0x80
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|addrHi
id|u32
id|addrHi
suffix:semicolon
DECL|member|processFlags
id|u32
id|processFlags
suffix:semicolon
DECL|macro|TYPHOON_TX_PF_NO_CRC
mdefine_line|#define TYPHOON_TX_PF_NO_CRC&t;&t;__constant_cpu_to_le32(0x00000001)
DECL|macro|TYPHOON_TX_PF_IP_CHKSUM
mdefine_line|#define TYPHOON_TX_PF_IP_CHKSUM&t;&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_TX_PF_TCP_CHKSUM
mdefine_line|#define TYPHOON_TX_PF_TCP_CHKSUM&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_TX_PF_TCP_SEGMENT
mdefine_line|#define TYPHOON_TX_PF_TCP_SEGMENT&t;__constant_cpu_to_le32(0x00000008)
DECL|macro|TYPHOON_TX_PF_INSERT_VLAN
mdefine_line|#define TYPHOON_TX_PF_INSERT_VLAN&t;__constant_cpu_to_le32(0x00000010)
DECL|macro|TYPHOON_TX_PF_IPSEC
mdefine_line|#define TYPHOON_TX_PF_IPSEC&t;&t;__constant_cpu_to_le32(0x00000020)
DECL|macro|TYPHOON_TX_PF_VLAN_PRIORITY
mdefine_line|#define TYPHOON_TX_PF_VLAN_PRIORITY&t;__constant_cpu_to_le32(0x00000040)
DECL|macro|TYPHOON_TX_PF_UDP_CHKSUM
mdefine_line|#define TYPHOON_TX_PF_UDP_CHKSUM&t;__constant_cpu_to_le32(0x00000080)
DECL|macro|TYPHOON_TX_PF_PAD_FRAME
mdefine_line|#define TYPHOON_TX_PF_PAD_FRAME&t;&t;__constant_cpu_to_le32(0x00000100)
DECL|macro|TYPHOON_TX_PF_RESERVED
mdefine_line|#define TYPHOON_TX_PF_RESERVED&t;&t;__constant_cpu_to_le32(0x00000e00)
DECL|macro|TYPHOON_TX_PF_VLAN_MASK
mdefine_line|#define TYPHOON_TX_PF_VLAN_MASK&t;&t;__constant_cpu_to_le32(0x0ffff000)
DECL|macro|TYPHOON_TX_PF_INTERNAL
mdefine_line|#define TYPHOON_TX_PF_INTERNAL&t;&t;__constant_cpu_to_le32(0xf0000000)
DECL|macro|TYPHOON_TX_PF_VLAN_TAG_SHIFT
mdefine_line|#define TYPHOON_TX_PF_VLAN_TAG_SHIFT&t;12
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The TCP Segmentation offload option descriptor&n; *&n; * flags:&t;descriptor type&n; * numDesc:&t;must be 1&n; * mss_flags:&t;bits 0-11 (little endian) are MSS, 12 is first TSO descriptor&n; *&t;&t;&t;13 is list TSO descriptor, set both if only one TSO&n; * respAddrLo:&t;low bytes of address of the bytesTx field of this descriptor&n; * bytesTx:&t;total number of bytes in this TSO request&n; * status:&t;0 on completion&n; */
DECL|struct|tcpopt_desc
r_struct
id|tcpopt_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|mss_flags
id|u16
id|mss_flags
suffix:semicolon
DECL|macro|TYPHOON_TSO_FIRST
mdefine_line|#define TYPHOON_TSO_FIRST&t;&t;__constant_cpu_to_le16(0x1000)
DECL|macro|TYPHOON_TSO_LAST
mdefine_line|#define TYPHOON_TSO_LAST&t;&t;__constant_cpu_to_le16(0x2000)
DECL|member|respAddrLo
id|u32
id|respAddrLo
suffix:semicolon
DECL|member|bytesTx
id|u32
id|bytesTx
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The IPSEC Offload descriptor&n; *&n; * flags:&t;descriptor type&n; * numDesc:&t;must be 1&n; * ipsecFlags:&t;bit 0: 0 -- generate IV, 1 -- use supplied IV&n; * sa1, sa2:&t;Security Association IDs for this packet&n; * reserved:&t;set to 0&n; */
DECL|struct|ipsec_desc
r_struct
id|ipsec_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|ipsecFlags
id|u16
id|ipsecFlags
suffix:semicolon
DECL|macro|TYPHOON_IPSEC_GEN_IV
mdefine_line|#define TYPHOON_IPSEC_GEN_IV&t;__constant_cpu_to_le16(0x0000)
DECL|macro|TYPHOON_IPSEC_USE_IV
mdefine_line|#define TYPHOON_IPSEC_USE_IV&t;__constant_cpu_to_le16(0x0001)
DECL|member|sa1
id|u32
id|sa1
suffix:semicolon
DECL|member|sa2
id|u32
id|sa2
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon receive descriptor (Updated by NIC)&n; *&n; * flags:         Descriptor type, error indication&n; * numDesc:       Always zero&n; * frameLen:      the size of the packet received&n; * addr:          low 32 bytes of the virtual addr passed in for this buffer&n; * addrHi:        high 32 bytes of the virtual addr passed in for this buffer&n; * rxStatus:      Error if set in flags, otherwise result of offload processing&n; * filterResults: results of filtering on packet, not used&n; * ipsecResults:  Results of IPSEC processing&n; * vlanTag:       the 801.2q TCI from the packet&n; */
DECL|struct|rx_desc
r_struct
id|rx_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|frameLen
id|u16
id|frameLen
suffix:semicolon
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|addrHi
id|u32
id|addrHi
suffix:semicolon
DECL|member|rxStatus
id|u32
id|rxStatus
suffix:semicolon
DECL|macro|TYPHOON_RX_ERR_INTERNAL
mdefine_line|#define TYPHOON_RX_ERR_INTERNAL&t;&t;__constant_cpu_to_le32(0x00000000)
DECL|macro|TYPHOON_RX_ERR_FIFO_UNDERRUN
mdefine_line|#define TYPHOON_RX_ERR_FIFO_UNDERRUN&t;__constant_cpu_to_le32(0x00000001)
DECL|macro|TYPHOON_RX_ERR_BAD_SSD
mdefine_line|#define TYPHOON_RX_ERR_BAD_SSD&t;&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_RX_ERR_RUNT
mdefine_line|#define TYPHOON_RX_ERR_RUNT&t;&t;__constant_cpu_to_le32(0x00000003)
DECL|macro|TYPHOON_RX_ERR_CRC
mdefine_line|#define TYPHOON_RX_ERR_CRC&t;&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_RX_ERR_OVERSIZE
mdefine_line|#define TYPHOON_RX_ERR_OVERSIZE&t;&t;__constant_cpu_to_le32(0x00000005)
DECL|macro|TYPHOON_RX_ERR_ALIGN
mdefine_line|#define TYPHOON_RX_ERR_ALIGN&t;&t;__constant_cpu_to_le32(0x00000006)
DECL|macro|TYPHOON_RX_ERR_DRIBBLE
mdefine_line|#define TYPHOON_RX_ERR_DRIBBLE&t;&t;__constant_cpu_to_le32(0x00000007)
DECL|macro|TYPHOON_RX_PROTO_MASK
mdefine_line|#define TYPHOON_RX_PROTO_MASK&t;&t;__constant_cpu_to_le32(0x00000003)
DECL|macro|TYPHOON_RX_PROTO_UNKNOWN
mdefine_line|#define TYPHOON_RX_PROTO_UNKNOWN&t;__constant_cpu_to_le32(0x00000000)
DECL|macro|TYPHOON_RX_PROTO_IP
mdefine_line|#define TYPHOON_RX_PROTO_IP&t;&t;__constant_cpu_to_le32(0x00000001)
DECL|macro|TYPHOON_RX_PROTO_IPX
mdefine_line|#define TYPHOON_RX_PROTO_IPX&t;&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_RX_VLAN
mdefine_line|#define TYPHOON_RX_VLAN&t;&t;&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_RX_IP_FRAG
mdefine_line|#define TYPHOON_RX_IP_FRAG&t;&t;__constant_cpu_to_le32(0x00000008)
DECL|macro|TYPHOON_RX_IPSEC
mdefine_line|#define TYPHOON_RX_IPSEC&t;&t;__constant_cpu_to_le32(0x00000010)
DECL|macro|TYPHOON_RX_IP_CHK_FAIL
mdefine_line|#define TYPHOON_RX_IP_CHK_FAIL&t;&t;__constant_cpu_to_le32(0x00000020)
DECL|macro|TYPHOON_RX_TCP_CHK_FAIL
mdefine_line|#define TYPHOON_RX_TCP_CHK_FAIL&t;&t;__constant_cpu_to_le32(0x00000040)
DECL|macro|TYPHOON_RX_UDP_CHK_FAIL
mdefine_line|#define TYPHOON_RX_UDP_CHK_FAIL&t;&t;__constant_cpu_to_le32(0x00000080)
DECL|macro|TYPHOON_RX_IP_CHK_GOOD
mdefine_line|#define TYPHOON_RX_IP_CHK_GOOD&t;&t;__constant_cpu_to_le32(0x00000100)
DECL|macro|TYPHOON_RX_TCP_CHK_GOOD
mdefine_line|#define TYPHOON_RX_TCP_CHK_GOOD&t;&t;__constant_cpu_to_le32(0x00000200)
DECL|macro|TYPHOON_RX_UDP_CHK_GOOD
mdefine_line|#define TYPHOON_RX_UDP_CHK_GOOD&t;&t;__constant_cpu_to_le32(0x00000400)
DECL|member|filterResults
id|u16
id|filterResults
suffix:semicolon
DECL|macro|TYPHOON_RX_FILTER_MASK
mdefine_line|#define TYPHOON_RX_FILTER_MASK&t;&t;__constant_cpu_to_le16(0x7fff)
DECL|macro|TYPHOON_RX_FILTERED
mdefine_line|#define TYPHOON_RX_FILTERED&t;&t;__constant_cpu_to_le16(0x8000)
DECL|member|ipsecResults
id|u16
id|ipsecResults
suffix:semicolon
DECL|macro|TYPHOON_RX_OUTER_AH_GOOD
mdefine_line|#define TYPHOON_RX_OUTER_AH_GOOD&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_RX_OUTER_ESP_GOOD
mdefine_line|#define TYPHOON_RX_OUTER_ESP_GOOD&t;__constant_cpu_to_le16(0x0002)
DECL|macro|TYPHOON_RX_INNER_AH_GOOD
mdefine_line|#define TYPHOON_RX_INNER_AH_GOOD&t;__constant_cpu_to_le16(0x0004)
DECL|macro|TYPHOON_RX_INNER_ESP_GOOD
mdefine_line|#define TYPHOON_RX_INNER_ESP_GOOD&t;__constant_cpu_to_le16(0x0008)
DECL|macro|TYPHOON_RX_OUTER_AH_FAIL
mdefine_line|#define TYPHOON_RX_OUTER_AH_FAIL&t;__constant_cpu_to_le16(0x0010)
DECL|macro|TYPHOON_RX_OUTER_ESP_FAIL
mdefine_line|#define TYPHOON_RX_OUTER_ESP_FAIL&t;__constant_cpu_to_le16(0x0020)
DECL|macro|TYPHOON_RX_INNER_AH_FAIL
mdefine_line|#define TYPHOON_RX_INNER_AH_FAIL&t;__constant_cpu_to_le16(0x0040)
DECL|macro|TYPHOON_RX_INNER_ESP_FAIL
mdefine_line|#define TYPHOON_RX_INNER_ESP_FAIL&t;__constant_cpu_to_le16(0x0080)
DECL|macro|TYPHOON_RX_UNKNOWN_SA
mdefine_line|#define TYPHOON_RX_UNKNOWN_SA&t;&t;__constant_cpu_to_le16(0x0100)
DECL|macro|TYPHOON_RX_ESP_FORMAT_ERR
mdefine_line|#define TYPHOON_RX_ESP_FORMAT_ERR&t;__constant_cpu_to_le16(0x0200)
DECL|member|vlanTag
id|u32
id|vlanTag
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon free buffer descriptor, used to give a buffer to the NIC&n; *&n; * physAddr:    low 32 bits of the bus address of the buffer&n; * physAddrHi:  high 32 bits of the bus address of the buffer, always zero&n; * virtAddr:    low 32 bits of the skb address&n; * virtAddrHi:  high 32 bits of the skb address, always zero&n; *&n; * the virt* address is basically two 32 bit cookies, just passed back&n; * from the NIC&n; */
DECL|struct|rx_free
r_struct
id|rx_free
(brace
DECL|member|physAddr
id|u32
id|physAddr
suffix:semicolon
DECL|member|physAddrHi
id|u32
id|physAddrHi
suffix:semicolon
DECL|member|virtAddr
id|u32
id|virtAddr
suffix:semicolon
DECL|member|virtAddrHi
id|u32
id|virtAddrHi
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon command descriptor, used for commands and responses&n; *&n; * flags:   descriptor type&n; * numDesc: number of descriptors following in this command/response,&n; *&t;&t;&t;&t;ie, zero for a one descriptor command&n; * cmd:     the command&n; * seqNo:   sequence number (unused)&n; * parm1:   use varies by command&n; * parm2:   use varies by command&n; * parm3:   use varies by command&n; */
DECL|struct|cmd_desc
r_struct
id|cmd_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|cmd
id|u16
id|cmd
suffix:semicolon
DECL|macro|TYPHOON_CMD_TX_ENABLE
mdefine_line|#define TYPHOON_CMD_TX_ENABLE&t;&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_CMD_TX_DISABLE
mdefine_line|#define TYPHOON_CMD_TX_DISABLE&t;&t;__constant_cpu_to_le16(0x0002)
DECL|macro|TYPHOON_CMD_RX_ENABLE
mdefine_line|#define TYPHOON_CMD_RX_ENABLE&t;&t;__constant_cpu_to_le16(0x0003)
DECL|macro|TYPHOON_CMD_RX_DISABLE
mdefine_line|#define TYPHOON_CMD_RX_DISABLE&t;&t;__constant_cpu_to_le16(0x0004)
DECL|macro|TYPHOON_CMD_SET_RX_FILTER
mdefine_line|#define TYPHOON_CMD_SET_RX_FILTER&t;__constant_cpu_to_le16(0x0005)
DECL|macro|TYPHOON_CMD_READ_STATS
mdefine_line|#define TYPHOON_CMD_READ_STATS&t;&t;__constant_cpu_to_le16(0x0007)
DECL|macro|TYPHOON_CMD_XCVR_SELECT
mdefine_line|#define TYPHOON_CMD_XCVR_SELECT&t;&t;__constant_cpu_to_le16(0x0013)
DECL|macro|TYPHOON_CMD_SET_MAX_PKT_SIZE
mdefine_line|#define TYPHOON_CMD_SET_MAX_PKT_SIZE&t;__constant_cpu_to_le16(0x001a)
DECL|macro|TYPHOON_CMD_READ_MEDIA_STATUS
mdefine_line|#define TYPHOON_CMD_READ_MEDIA_STATUS&t;__constant_cpu_to_le16(0x001b)
DECL|macro|TYPHOON_CMD_GOTO_SLEEP
mdefine_line|#define TYPHOON_CMD_GOTO_SLEEP&t;&t;__constant_cpu_to_le16(0x0023)
DECL|macro|TYPHOON_CMD_SET_MULTICAST_HASH
mdefine_line|#define TYPHOON_CMD_SET_MULTICAST_HASH&t;__constant_cpu_to_le16(0x0025)
DECL|macro|TYPHOON_CMD_SET_MAC_ADDRESS
mdefine_line|#define TYPHOON_CMD_SET_MAC_ADDRESS&t;__constant_cpu_to_le16(0x0026)
DECL|macro|TYPHOON_CMD_READ_MAC_ADDRESS
mdefine_line|#define TYPHOON_CMD_READ_MAC_ADDRESS&t;__constant_cpu_to_le16(0x0027)
DECL|macro|TYPHOON_CMD_VLAN_TYPE_WRITE
mdefine_line|#define TYPHOON_CMD_VLAN_TYPE_WRITE&t;__constant_cpu_to_le16(0x002b)
DECL|macro|TYPHOON_CMD_CREATE_SA
mdefine_line|#define TYPHOON_CMD_CREATE_SA&t;&t;__constant_cpu_to_le16(0x0034)
DECL|macro|TYPHOON_CMD_DELETE_SA
mdefine_line|#define TYPHOON_CMD_DELETE_SA&t;&t;__constant_cpu_to_le16(0x0035)
DECL|macro|TYPHOON_CMD_READ_VERSIONS
mdefine_line|#define TYPHOON_CMD_READ_VERSIONS&t;__constant_cpu_to_le16(0x0043)
DECL|macro|TYPHOON_CMD_IRQ_COALESCE_CTRL
mdefine_line|#define TYPHOON_CMD_IRQ_COALESCE_CTRL&t;__constant_cpu_to_le16(0x0045)
DECL|macro|TYPHOON_CMD_ENABLE_WAKE_EVENTS
mdefine_line|#define TYPHOON_CMD_ENABLE_WAKE_EVENTS&t;__constant_cpu_to_le16(0x0049)
DECL|macro|TYPHOON_CMD_SET_OFFLOAD_TASKS
mdefine_line|#define TYPHOON_CMD_SET_OFFLOAD_TASKS&t;__constant_cpu_to_le16(0x004f)
DECL|macro|TYPHOON_CMD_HELLO_RESP
mdefine_line|#define TYPHOON_CMD_HELLO_RESP&t;&t;__constant_cpu_to_le16(0x0057)
DECL|macro|TYPHOON_CMD_HALT
mdefine_line|#define TYPHOON_CMD_HALT&t;&t;__constant_cpu_to_le16(0x005d)
DECL|macro|TYPHOON_CMD_READ_IPSEC_INFO
mdefine_line|#define TYPHOON_CMD_READ_IPSEC_INFO&t;__constant_cpu_to_le16(0x005e)
DECL|macro|TYPHOON_CMD_GET_IPSEC_ENABLE
mdefine_line|#define TYPHOON_CMD_GET_IPSEC_ENABLE&t;__constant_cpu_to_le16(0x0067)
DECL|macro|TYPHOON_CMD_GET_CMD_LVL
mdefine_line|#define TYPHOON_CMD_GET_CMD_LVL&t;&t;__constant_cpu_to_le16(0x0069)
DECL|member|seqNo
id|u16
id|seqNo
suffix:semicolon
DECL|member|parm1
id|u16
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon response descriptor, see command descriptor for details&n; */
DECL|struct|resp_desc
r_struct
id|resp_desc
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|cmd
id|u16
id|cmd
suffix:semicolon
DECL|member|seqNo
id|u16
id|seqNo
suffix:semicolon
DECL|member|parm1
id|u16
id|parm1
suffix:semicolon
DECL|member|parm2
id|u32
id|parm2
suffix:semicolon
DECL|member|parm3
id|u32
id|parm3
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|INIT_COMMAND_NO_RESPONSE
mdefine_line|#define INIT_COMMAND_NO_RESPONSE(x, command)&t;&t;&t;&t;&bslash;&n;&t;do { struct cmd_desc *_ptr = (x);&t;&t;&t;&t;&bslash;&n;&t;&t;memset(_ptr, 0, sizeof(struct cmd_desc));&t;&t;&bslash;&n;&t;&t;_ptr-&gt;flags = TYPHOON_CMD_DESC | TYPHOON_DESC_VALID;&t;&bslash;&n;&t;&t;_ptr-&gt;cmd = command;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/* We set seqNo to 1 if we&squot;re expecting a response from this command */
DECL|macro|INIT_COMMAND_WITH_RESPONSE
mdefine_line|#define INIT_COMMAND_WITH_RESPONSE(x, command)&t;&t;&t;&t;&bslash;&n;&t;do { struct cmd_desc *_ptr = (x);&t;&t;&t;&t;&bslash;&n;&t;&t;memset(_ptr, 0, sizeof(struct cmd_desc));&t;&t;&bslash;&n;&t;&t;_ptr-&gt;flags = TYPHOON_CMD_RESPOND | TYPHOON_CMD_DESC;&t;&bslash;&n;&t;&t;_ptr-&gt;flags |= TYPHOON_DESC_VALID; &t;&t;&t;&bslash;&n;&t;&t;_ptr-&gt;cmd = command;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_ptr-&gt;seqNo = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/* TYPHOON_CMD_SET_RX_FILTER filter bits (cmd.parm1)&n; */
DECL|macro|TYPHOON_RX_FILTER_DIRECTED
mdefine_line|#define TYPHOON_RX_FILTER_DIRECTED&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_RX_FILTER_ALL_MCAST
mdefine_line|#define TYPHOON_RX_FILTER_ALL_MCAST&t;__constant_cpu_to_le16(0x0002)
DECL|macro|TYPHOON_RX_FILTER_BROADCAST
mdefine_line|#define TYPHOON_RX_FILTER_BROADCAST&t;__constant_cpu_to_le16(0x0004)
DECL|macro|TYPHOON_RX_FILTER_PROMISCOUS
mdefine_line|#define TYPHOON_RX_FILTER_PROMISCOUS&t;__constant_cpu_to_le16(0x0008)
DECL|macro|TYPHOON_RX_FILTER_MCAST_HASH
mdefine_line|#define TYPHOON_RX_FILTER_MCAST_HASH&t;__constant_cpu_to_le16(0x0010)
multiline_comment|/* TYPHOON_CMD_READ_STATS response format&n; */
DECL|struct|stats_resp
r_struct
id|stats_resp
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|cmd
id|u16
id|cmd
suffix:semicolon
DECL|member|seqNo
id|u16
id|seqNo
suffix:semicolon
DECL|member|unused
id|u16
id|unused
suffix:semicolon
DECL|member|txPackets
id|u32
id|txPackets
suffix:semicolon
DECL|member|txBytes
id|u64
id|txBytes
suffix:semicolon
DECL|member|txDeferred
id|u32
id|txDeferred
suffix:semicolon
DECL|member|txLateCollisions
id|u32
id|txLateCollisions
suffix:semicolon
DECL|member|txCollisions
id|u32
id|txCollisions
suffix:semicolon
DECL|member|txCarrierLost
id|u32
id|txCarrierLost
suffix:semicolon
DECL|member|txMultipleCollisions
id|u32
id|txMultipleCollisions
suffix:semicolon
DECL|member|txExcessiveCollisions
id|u32
id|txExcessiveCollisions
suffix:semicolon
DECL|member|txFifoUnderruns
id|u32
id|txFifoUnderruns
suffix:semicolon
DECL|member|txMulticastTxOverflows
id|u32
id|txMulticastTxOverflows
suffix:semicolon
DECL|member|txFiltered
id|u32
id|txFiltered
suffix:semicolon
DECL|member|rxPacketsGood
id|u32
id|rxPacketsGood
suffix:semicolon
DECL|member|rxBytesGood
id|u64
id|rxBytesGood
suffix:semicolon
DECL|member|rxFifoOverruns
id|u32
id|rxFifoOverruns
suffix:semicolon
DECL|member|BadSSD
id|u32
id|BadSSD
suffix:semicolon
DECL|member|rxCrcErrors
id|u32
id|rxCrcErrors
suffix:semicolon
DECL|member|rxOversized
id|u32
id|rxOversized
suffix:semicolon
DECL|member|rxBroadcast
id|u32
id|rxBroadcast
suffix:semicolon
DECL|member|rxMulticast
id|u32
id|rxMulticast
suffix:semicolon
DECL|member|rxOverflow
id|u32
id|rxOverflow
suffix:semicolon
DECL|member|rxFiltered
id|u32
id|rxFiltered
suffix:semicolon
DECL|member|linkStatus
id|u32
id|linkStatus
suffix:semicolon
DECL|macro|TYPHOON_LINK_STAT_MASK
mdefine_line|#define TYPHOON_LINK_STAT_MASK&t;&t;__constant_cpu_to_le32(0x00000001)
DECL|macro|TYPHOON_LINK_GOOD
mdefine_line|#define TYPHOON_LINK_GOOD&t;&t;__constant_cpu_to_le32(0x00000001)
DECL|macro|TYPHOON_LINK_BAD
mdefine_line|#define TYPHOON_LINK_BAD&t;&t;__constant_cpu_to_le32(0x00000000)
DECL|macro|TYPHOON_LINK_SPEED_MASK
mdefine_line|#define TYPHOON_LINK_SPEED_MASK&t;&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_LINK_100MBPS
mdefine_line|#define TYPHOON_LINK_100MBPS&t;&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_LINK_10MBPS
mdefine_line|#define TYPHOON_LINK_10MBPS&t;&t;__constant_cpu_to_le32(0x00000000)
DECL|macro|TYPHOON_LINK_DUPLEX_MASK
mdefine_line|#define TYPHOON_LINK_DUPLEX_MASK&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_LINK_FULL_DUPLEX
mdefine_line|#define TYPHOON_LINK_FULL_DUPLEX&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_LINK_HALF_DUPLEX
mdefine_line|#define TYPHOON_LINK_HALF_DUPLEX&t;__constant_cpu_to_le32(0x00000000)
DECL|member|unused2
id|u32
id|unused2
suffix:semicolon
DECL|member|unused3
id|u32
id|unused3
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* TYPHOON_CMD_XCVR_SELECT xcvr values (resp.parm1)&n; */
DECL|macro|TYPHOON_XCVR_10HALF
mdefine_line|#define TYPHOON_XCVR_10HALF&t;__constant_cpu_to_le16(0x0000)
DECL|macro|TYPHOON_XCVR_10FULL
mdefine_line|#define TYPHOON_XCVR_10FULL&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_XCVR_100HALF
mdefine_line|#define TYPHOON_XCVR_100HALF&t;__constant_cpu_to_le16(0x0002)
DECL|macro|TYPHOON_XCVR_100FULL
mdefine_line|#define TYPHOON_XCVR_100FULL&t;__constant_cpu_to_le16(0x0003)
DECL|macro|TYPHOON_XCVR_AUTONEG
mdefine_line|#define TYPHOON_XCVR_AUTONEG&t;__constant_cpu_to_le16(0x0004)
multiline_comment|/* TYPHOON_CMD_READ_MEDIA_STATUS (resp.parm1)&n; */
DECL|macro|TYPHOON_MEDIA_STAT_CRC_STRIP_DISABLE
mdefine_line|#define TYPHOON_MEDIA_STAT_CRC_STRIP_DISABLE&t;__constant_cpu_to_le16(0x0004)
DECL|macro|TYPHOON_MEDIA_STAT_COLLISION_DETECT
mdefine_line|#define TYPHOON_MEDIA_STAT_COLLISION_DETECT&t;__constant_cpu_to_le16(0x0010)
DECL|macro|TYPHOON_MEDIA_STAT_CARRIER_SENSE
mdefine_line|#define TYPHOON_MEDIA_STAT_CARRIER_SENSE&t;__constant_cpu_to_le16(0x0020)
DECL|macro|TYPHOON_MEDIA_STAT_POLARITY_REV
mdefine_line|#define TYPHOON_MEDIA_STAT_POLARITY_REV&t;&t;__constant_cpu_to_le16(0x0400)
DECL|macro|TYPHOON_MEDIA_STAT_NO_LINK
mdefine_line|#define TYPHOON_MEDIA_STAT_NO_LINK&t;&t;__constant_cpu_to_le16(0x0800)
multiline_comment|/* TYPHOON_CMD_SET_MULTICAST_HASH enable values (cmd.parm1)&n; */
DECL|macro|TYPHOON_MCAST_HASH_DISABLE
mdefine_line|#define TYPHOON_MCAST_HASH_DISABLE&t;__constant_cpu_to_le16(0x0000)
DECL|macro|TYPHOON_MCAST_HASH_ENABLE
mdefine_line|#define TYPHOON_MCAST_HASH_ENABLE&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_MCAST_HASH_SET
mdefine_line|#define TYPHOON_MCAST_HASH_SET&t;&t;__constant_cpu_to_le16(0x0002)
multiline_comment|/* TYPHOON_CMD_CREATE_SA descriptor and settings&n; */
DECL|struct|sa_descriptor
r_struct
id|sa_descriptor
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|numDesc
id|u8
id|numDesc
suffix:semicolon
DECL|member|cmd
id|u16
id|cmd
suffix:semicolon
DECL|member|seqNo
id|u16
id|seqNo
suffix:semicolon
DECL|member|mode
id|u16
id|mode
suffix:semicolon
DECL|macro|TYPHOON_SA_MODE_NULL
mdefine_line|#define TYPHOON_SA_MODE_NULL&t;&t;__constant_cpu_to_le16(0x0000)
DECL|macro|TYPHOON_SA_MODE_AH
mdefine_line|#define TYPHOON_SA_MODE_AH&t;&t;__constant_cpu_to_le16(0x0001)
DECL|macro|TYPHOON_SA_MODE_ESP
mdefine_line|#define TYPHOON_SA_MODE_ESP&t;&t;__constant_cpu_to_le16(0x0002)
DECL|member|hashFlags
id|u8
id|hashFlags
suffix:semicolon
DECL|macro|TYPHOON_SA_HASH_ENABLE
mdefine_line|#define TYPHOON_SA_HASH_ENABLE&t;&t;0x01
DECL|macro|TYPHOON_SA_HASH_SHA1
mdefine_line|#define TYPHOON_SA_HASH_SHA1&t;&t;0x02
DECL|macro|TYPHOON_SA_HASH_MD5
mdefine_line|#define TYPHOON_SA_HASH_MD5&t;&t;0x04
DECL|member|direction
id|u8
id|direction
suffix:semicolon
DECL|macro|TYPHOON_SA_DIR_RX
mdefine_line|#define TYPHOON_SA_DIR_RX&t;&t;0x00
DECL|macro|TYPHOON_SA_DIR_TX
mdefine_line|#define TYPHOON_SA_DIR_TX&t;&t;0x01
DECL|member|encryptionFlags
id|u8
id|encryptionFlags
suffix:semicolon
DECL|macro|TYPHOON_SA_ENCRYPT_ENABLE
mdefine_line|#define TYPHOON_SA_ENCRYPT_ENABLE&t;0x01
DECL|macro|TYPHOON_SA_ENCRYPT_DES
mdefine_line|#define TYPHOON_SA_ENCRYPT_DES&t;&t;0x02
DECL|macro|TYPHOON_SA_ENCRYPT_3DES
mdefine_line|#define TYPHOON_SA_ENCRYPT_3DES&t;&t;0x00
DECL|macro|TYPHOON_SA_ENCRYPT_3DES_2KEY
mdefine_line|#define TYPHOON_SA_ENCRYPT_3DES_2KEY&t;0x00
DECL|macro|TYPHOON_SA_ENCRYPT_3DES_3KEY
mdefine_line|#define TYPHOON_SA_ENCRYPT_3DES_3KEY&t;0x04
DECL|macro|TYPHOON_SA_ENCRYPT_CBC
mdefine_line|#define TYPHOON_SA_ENCRYPT_CBC&t;&t;0x08
DECL|macro|TYPHOON_SA_ENCRYPT_ECB
mdefine_line|#define TYPHOON_SA_ENCRYPT_ECB&t;&t;0x00
DECL|member|specifyIndex
id|u8
id|specifyIndex
suffix:semicolon
DECL|macro|TYPHOON_SA_SPECIFY_INDEX
mdefine_line|#define TYPHOON_SA_SPECIFY_INDEX&t;0x01
DECL|macro|TYPHOON_SA_GENERATE_INDEX
mdefine_line|#define TYPHOON_SA_GENERATE_INDEX&t;0x00
DECL|member|SPI
id|u32
id|SPI
suffix:semicolon
DECL|member|destAddr
id|u32
id|destAddr
suffix:semicolon
DECL|member|destMask
id|u32
id|destMask
suffix:semicolon
DECL|member|integKey
id|u8
id|integKey
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|confKey
id|u8
id|confKey
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|unused
id|u32
id|unused
suffix:semicolon
DECL|member|unused2
id|u32
id|unused2
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* TYPHOON_CMD_SET_OFFLOAD_TASKS bits (cmd.parm2 (Tx) &amp; cmd.parm3 (Rx))&n; * This is all for IPv4.&n; */
DECL|macro|TYPHOON_OFFLOAD_TCP_CHKSUM
mdefine_line|#define TYPHOON_OFFLOAD_TCP_CHKSUM&t;__constant_cpu_to_le32(0x00000002)
DECL|macro|TYPHOON_OFFLOAD_UDP_CHKSUM
mdefine_line|#define TYPHOON_OFFLOAD_UDP_CHKSUM&t;__constant_cpu_to_le32(0x00000004)
DECL|macro|TYPHOON_OFFLOAD_IP_CHKSUM
mdefine_line|#define TYPHOON_OFFLOAD_IP_CHKSUM&t;__constant_cpu_to_le32(0x00000008)
DECL|macro|TYPHOON_OFFLOAD_IPSEC
mdefine_line|#define TYPHOON_OFFLOAD_IPSEC&t;&t;__constant_cpu_to_le32(0x00000010)
DECL|macro|TYPHOON_OFFLOAD_BCAST_THROTTLE
mdefine_line|#define TYPHOON_OFFLOAD_BCAST_THROTTLE&t;__constant_cpu_to_le32(0x00000020)
DECL|macro|TYPHOON_OFFLOAD_DHCP_PREVENT
mdefine_line|#define TYPHOON_OFFLOAD_DHCP_PREVENT&t;__constant_cpu_to_le32(0x00000040)
DECL|macro|TYPHOON_OFFLOAD_VLAN
mdefine_line|#define TYPHOON_OFFLOAD_VLAN&t;&t;__constant_cpu_to_le32(0x00000080)
DECL|macro|TYPHOON_OFFLOAD_FILTERING
mdefine_line|#define TYPHOON_OFFLOAD_FILTERING&t;__constant_cpu_to_le32(0x00000100)
DECL|macro|TYPHOON_OFFLOAD_TCP_SEGMENT
mdefine_line|#define TYPHOON_OFFLOAD_TCP_SEGMENT&t;__constant_cpu_to_le32(0x00000200)
multiline_comment|/* TYPHOON_CMD_ENABLE_WAKE_EVENTS bits (cmd.parm1)&n; */
DECL|macro|TYPHOON_WAKE_MAGIC_PKT
mdefine_line|#define TYPHOON_WAKE_MAGIC_PKT&t;&t;__constant_cpu_to_le16(0x01)
DECL|macro|TYPHOON_WAKE_LINK_EVENT
mdefine_line|#define TYPHOON_WAKE_LINK_EVENT&t;&t;__constant_cpu_to_le16(0x02)
DECL|macro|TYPHOON_WAKE_ICMP_ECHO
mdefine_line|#define TYPHOON_WAKE_ICMP_ECHO&t;&t;__constant_cpu_to_le16(0x04)
DECL|macro|TYPHOON_WAKE_ARP
mdefine_line|#define TYPHOON_WAKE_ARP&t;&t;__constant_cpu_to_le16(0x08)
multiline_comment|/* These are used to load the firmware image on the NIC&n; */
DECL|struct|typhoon_file_header
r_struct
id|typhoon_file_header
(brace
DECL|member|tag
id|u8
id|tag
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|numSections
id|u32
id|numSections
suffix:semicolon
DECL|member|startAddr
id|u32
id|startAddr
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|typhoon_section_header
r_struct
id|typhoon_section_header
(brace
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|checksum
id|u16
id|checksum
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|startAddr
id|u32
id|startAddr
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The Typhoon Register offsets&n; */
DECL|macro|TYPHOON_REG_SOFT_RESET
mdefine_line|#define TYPHOON_REG_SOFT_RESET&t;&t;&t;0x00
DECL|macro|TYPHOON_REG_INTR_STATUS
mdefine_line|#define TYPHOON_REG_INTR_STATUS&t;&t;&t;0x04
DECL|macro|TYPHOON_REG_INTR_ENABLE
mdefine_line|#define TYPHOON_REG_INTR_ENABLE&t;&t;&t;0x08
DECL|macro|TYPHOON_REG_INTR_MASK
mdefine_line|#define TYPHOON_REG_INTR_MASK&t;&t;&t;0x0c
DECL|macro|TYPHOON_REG_SELF_INTERRUPT
mdefine_line|#define TYPHOON_REG_SELF_INTERRUPT&t;&t;0x10
DECL|macro|TYPHOON_REG_HOST2ARM7
mdefine_line|#define TYPHOON_REG_HOST2ARM7&t;&t;&t;0x14
DECL|macro|TYPHOON_REG_HOST2ARM6
mdefine_line|#define TYPHOON_REG_HOST2ARM6&t;&t;&t;0x18
DECL|macro|TYPHOON_REG_HOST2ARM5
mdefine_line|#define TYPHOON_REG_HOST2ARM5&t;&t;&t;0x1c
DECL|macro|TYPHOON_REG_HOST2ARM4
mdefine_line|#define TYPHOON_REG_HOST2ARM4&t;&t;&t;0x20
DECL|macro|TYPHOON_REG_HOST2ARM3
mdefine_line|#define TYPHOON_REG_HOST2ARM3&t;&t;&t;0x24
DECL|macro|TYPHOON_REG_HOST2ARM2
mdefine_line|#define TYPHOON_REG_HOST2ARM2&t;&t;&t;0x28
DECL|macro|TYPHOON_REG_HOST2ARM1
mdefine_line|#define TYPHOON_REG_HOST2ARM1&t;&t;&t;0x2c
DECL|macro|TYPHOON_REG_HOST2ARM0
mdefine_line|#define TYPHOON_REG_HOST2ARM0&t;&t;&t;0x30
DECL|macro|TYPHOON_REG_ARM2HOST3
mdefine_line|#define TYPHOON_REG_ARM2HOST3&t;&t;&t;0x34
DECL|macro|TYPHOON_REG_ARM2HOST2
mdefine_line|#define TYPHOON_REG_ARM2HOST2&t;&t;&t;0x38
DECL|macro|TYPHOON_REG_ARM2HOST1
mdefine_line|#define TYPHOON_REG_ARM2HOST1&t;&t;&t;0x3c
DECL|macro|TYPHOON_REG_ARM2HOST0
mdefine_line|#define TYPHOON_REG_ARM2HOST0&t;&t;&t;0x40
DECL|macro|TYPHOON_REG_BOOT_DATA_LO
mdefine_line|#define TYPHOON_REG_BOOT_DATA_LO&t;&t;TYPHOON_REG_HOST2ARM5
DECL|macro|TYPHOON_REG_BOOT_DATA_HI
mdefine_line|#define TYPHOON_REG_BOOT_DATA_HI&t;&t;TYPHOON_REG_HOST2ARM4
DECL|macro|TYPHOON_REG_BOOT_DEST_ADDR
mdefine_line|#define TYPHOON_REG_BOOT_DEST_ADDR&t;&t;TYPHOON_REG_HOST2ARM3
DECL|macro|TYPHOON_REG_BOOT_CHECKSUM
mdefine_line|#define TYPHOON_REG_BOOT_CHECKSUM&t;&t;TYPHOON_REG_HOST2ARM2
DECL|macro|TYPHOON_REG_BOOT_LENGTH
mdefine_line|#define TYPHOON_REG_BOOT_LENGTH&t;&t;&t;TYPHOON_REG_HOST2ARM1
DECL|macro|TYPHOON_REG_DOWNLOAD_BOOT_ADDR
mdefine_line|#define TYPHOON_REG_DOWNLOAD_BOOT_ADDR&t;&t;TYPHOON_REG_HOST2ARM1
DECL|macro|TYPHOON_REG_BOOT_RECORD_ADDR_HI
mdefine_line|#define TYPHOON_REG_BOOT_RECORD_ADDR_HI&t;&t;TYPHOON_REG_HOST2ARM2
DECL|macro|TYPHOON_REG_BOOT_RECORD_ADDR_LO
mdefine_line|#define TYPHOON_REG_BOOT_RECORD_ADDR_LO&t;&t;TYPHOON_REG_HOST2ARM1
DECL|macro|TYPHOON_REG_TX_LO_READY
mdefine_line|#define TYPHOON_REG_TX_LO_READY&t;&t;&t;TYPHOON_REG_HOST2ARM3
DECL|macro|TYPHOON_REG_CMD_READY
mdefine_line|#define TYPHOON_REG_CMD_READY&t;&t;&t;TYPHOON_REG_HOST2ARM2
DECL|macro|TYPHOON_REG_TX_HI_READY
mdefine_line|#define TYPHOON_REG_TX_HI_READY&t;&t;&t;TYPHOON_REG_HOST2ARM1
DECL|macro|TYPHOON_REG_COMMAND
mdefine_line|#define TYPHOON_REG_COMMAND&t;&t;&t;TYPHOON_REG_HOST2ARM0
DECL|macro|TYPHOON_REG_HEARTBEAT
mdefine_line|#define TYPHOON_REG_HEARTBEAT&t;&t;&t;TYPHOON_REG_ARM2HOST3
DECL|macro|TYPHOON_REG_STATUS
mdefine_line|#define TYPHOON_REG_STATUS&t;&t;&t;TYPHOON_REG_ARM2HOST0
multiline_comment|/* 3XP Reset values (TYPHOON_REG_SOFT_RESET)&n; */
DECL|macro|TYPHOON_RESET_ALL
mdefine_line|#define TYPHOON_RESET_ALL&t;0x7f
DECL|macro|TYPHOON_RESET_NONE
mdefine_line|#define TYPHOON_RESET_NONE&t;0x00
multiline_comment|/* 3XP irq bits (TYPHOON_REG_INTR{STATUS,ENABLE,MASK})&n; *&n; * Some of these came from OpenBSD, as the 3Com docs have it wrong&n; * (INTR_SELF) or don&squot;t list it at all (INTR_*_ABORT)&n; *&n; * Enabling irqs on the Heartbeat reg (ArmToHost3) gets you an irq&n; * about every 8ms, so don&squot;t do it.&n; */
DECL|macro|TYPHOON_INTR_HOST_INT
mdefine_line|#define TYPHOON_INTR_HOST_INT&t;&t;0x00000001
DECL|macro|TYPHOON_INTR_ARM2HOST0
mdefine_line|#define TYPHOON_INTR_ARM2HOST0&t;&t;0x00000002
DECL|macro|TYPHOON_INTR_ARM2HOST1
mdefine_line|#define TYPHOON_INTR_ARM2HOST1&t;&t;0x00000004
DECL|macro|TYPHOON_INTR_ARM2HOST2
mdefine_line|#define TYPHOON_INTR_ARM2HOST2&t;&t;0x00000008
DECL|macro|TYPHOON_INTR_ARM2HOST3
mdefine_line|#define TYPHOON_INTR_ARM2HOST3&t;&t;0x00000010
DECL|macro|TYPHOON_INTR_DMA0
mdefine_line|#define TYPHOON_INTR_DMA0&t;&t;0x00000020
DECL|macro|TYPHOON_INTR_DMA1
mdefine_line|#define TYPHOON_INTR_DMA1&t;&t;0x00000040
DECL|macro|TYPHOON_INTR_DMA2
mdefine_line|#define TYPHOON_INTR_DMA2&t;&t;0x00000080
DECL|macro|TYPHOON_INTR_DMA3
mdefine_line|#define TYPHOON_INTR_DMA3&t;&t;0x00000100
DECL|macro|TYPHOON_INTR_MASTER_ABORT
mdefine_line|#define TYPHOON_INTR_MASTER_ABORT&t;0x00000200
DECL|macro|TYPHOON_INTR_TARGET_ABORT
mdefine_line|#define TYPHOON_INTR_TARGET_ABORT&t;0x00000400
DECL|macro|TYPHOON_INTR_SELF
mdefine_line|#define TYPHOON_INTR_SELF&t;&t;0x00000800
DECL|macro|TYPHOON_INTR_RESERVED
mdefine_line|#define TYPHOON_INTR_RESERVED&t;&t;0xfffff000
DECL|macro|TYPHOON_INTR_BOOTCMD
mdefine_line|#define TYPHOON_INTR_BOOTCMD&t;&t;TYPHOON_INTR_ARM2HOST0
DECL|macro|TYPHOON_INTR_ENABLE_ALL
mdefine_line|#define TYPHOON_INTR_ENABLE_ALL&t;&t;0xffffffef
DECL|macro|TYPHOON_INTR_ALL
mdefine_line|#define TYPHOON_INTR_ALL&t;&t;0xffffffff
DECL|macro|TYPHOON_INTR_NONE
mdefine_line|#define TYPHOON_INTR_NONE&t;&t;0x00000000
multiline_comment|/* The commands for the 3XP chip (TYPHOON_REG_COMMAND)&n; */
DECL|macro|TYPHOON_BOOTCMD_BOOT
mdefine_line|#define TYPHOON_BOOTCMD_BOOT&t;&t;&t;0x00
DECL|macro|TYPHOON_BOOTCMD_WAKEUP
mdefine_line|#define TYPHOON_BOOTCMD_WAKEUP&t;&t;&t;0xfa
DECL|macro|TYPHOON_BOOTCMD_DNLD_COMPLETE
mdefine_line|#define TYPHOON_BOOTCMD_DNLD_COMPLETE&t;&t;0xfb
DECL|macro|TYPHOON_BOOTCMD_SEG_AVAILABLE
mdefine_line|#define TYPHOON_BOOTCMD_SEG_AVAILABLE&t;&t;0xfc
DECL|macro|TYPHOON_BOOTCMD_RUNTIME_IMAGE
mdefine_line|#define TYPHOON_BOOTCMD_RUNTIME_IMAGE&t;&t;0xfd
DECL|macro|TYPHOON_BOOTCMD_REG_BOOT_RECORD
mdefine_line|#define TYPHOON_BOOTCMD_REG_BOOT_RECORD&t;&t;0xff
multiline_comment|/* 3XP Status values (TYPHOON_REG_STATUS)&n; */
DECL|macro|TYPHOON_STATUS_WAITING_FOR_BOOT
mdefine_line|#define TYPHOON_STATUS_WAITING_FOR_BOOT&t;&t;0x07
DECL|macro|TYPHOON_STATUS_SECOND_INIT
mdefine_line|#define TYPHOON_STATUS_SECOND_INIT&t;&t;0x08
DECL|macro|TYPHOON_STATUS_RUNNING
mdefine_line|#define TYPHOON_STATUS_RUNNING&t;&t;&t;0x09
DECL|macro|TYPHOON_STATUS_WAITING_FOR_HOST
mdefine_line|#define TYPHOON_STATUS_WAITING_FOR_HOST&t;&t;0x0d
DECL|macro|TYPHOON_STATUS_WAITING_FOR_SEGMENT
mdefine_line|#define TYPHOON_STATUS_WAITING_FOR_SEGMENT&t;0x10
DECL|macro|TYPHOON_STATUS_SLEEPING
mdefine_line|#define TYPHOON_STATUS_SLEEPING&t;&t;&t;0x11
DECL|macro|TYPHOON_STATUS_HALTED
mdefine_line|#define TYPHOON_STATUS_HALTED&t;&t;&t;0x14
eof
