macro_line|#ifndef __MV64340_ETH_H__
DECL|macro|__MV64340_ETH_H__
mdefine_line|#define __MV64340_ETH_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/mv643xx.h&gt;
DECL|macro|BIT0
mdefine_line|#define&t;BIT0&t;0x00000001
DECL|macro|BIT1
mdefine_line|#define&t;BIT1&t;0x00000002
DECL|macro|BIT2
mdefine_line|#define&t;BIT2&t;0x00000004
DECL|macro|BIT3
mdefine_line|#define&t;BIT3&t;0x00000008
DECL|macro|BIT4
mdefine_line|#define&t;BIT4&t;0x00000010
DECL|macro|BIT5
mdefine_line|#define&t;BIT5&t;0x00000020
DECL|macro|BIT6
mdefine_line|#define&t;BIT6&t;0x00000040
DECL|macro|BIT7
mdefine_line|#define&t;BIT7&t;0x00000080
DECL|macro|BIT8
mdefine_line|#define&t;BIT8&t;0x00000100
DECL|macro|BIT9
mdefine_line|#define&t;BIT9&t;0x00000200
DECL|macro|BIT10
mdefine_line|#define&t;BIT10&t;0x00000400
DECL|macro|BIT11
mdefine_line|#define&t;BIT11&t;0x00000800
DECL|macro|BIT12
mdefine_line|#define&t;BIT12&t;0x00001000
DECL|macro|BIT13
mdefine_line|#define&t;BIT13&t;0x00002000
DECL|macro|BIT14
mdefine_line|#define&t;BIT14&t;0x00004000
DECL|macro|BIT15
mdefine_line|#define&t;BIT15&t;0x00008000
DECL|macro|BIT16
mdefine_line|#define&t;BIT16&t;0x00010000
DECL|macro|BIT17
mdefine_line|#define&t;BIT17&t;0x00020000
DECL|macro|BIT18
mdefine_line|#define&t;BIT18&t;0x00040000
DECL|macro|BIT19
mdefine_line|#define&t;BIT19&t;0x00080000
DECL|macro|BIT20
mdefine_line|#define&t;BIT20&t;0x00100000
DECL|macro|BIT21
mdefine_line|#define&t;BIT21&t;0x00200000
DECL|macro|BIT22
mdefine_line|#define&t;BIT22&t;0x00400000
DECL|macro|BIT23
mdefine_line|#define&t;BIT23&t;0x00800000
DECL|macro|BIT24
mdefine_line|#define&t;BIT24&t;0x01000000
DECL|macro|BIT25
mdefine_line|#define&t;BIT25&t;0x02000000
DECL|macro|BIT26
mdefine_line|#define&t;BIT26&t;0x04000000
DECL|macro|BIT27
mdefine_line|#define&t;BIT27&t;0x08000000
DECL|macro|BIT28
mdefine_line|#define&t;BIT28&t;0x10000000
DECL|macro|BIT29
mdefine_line|#define&t;BIT29&t;0x20000000
DECL|macro|BIT30
mdefine_line|#define&t;BIT30&t;0x40000000
DECL|macro|BIT31
mdefine_line|#define&t;BIT31&t;0x80000000
multiline_comment|/*&n; *  The first part is the high level driver of the gigE ethernet ports.&n; */
DECL|macro|ETH_PORT0_IRQ_NUM
mdefine_line|#define ETH_PORT0_IRQ_NUM 48&t;&t;&t;/* main high register, bit0 */
DECL|macro|ETH_PORT1_IRQ_NUM
mdefine_line|#define ETH_PORT1_IRQ_NUM ETH_PORT0_IRQ_NUM+1&t;/* main high register, bit1 */
DECL|macro|ETH_PORT2_IRQ_NUM
mdefine_line|#define ETH_PORT2_IRQ_NUM ETH_PORT0_IRQ_NUM+2&t;/* main high register, bit1 */
multiline_comment|/* Checksum offload for Tx works */
DECL|macro|MV64340_CHECKSUM_OFFLOAD_TX
mdefine_line|#define  MV64340_CHECKSUM_OFFLOAD_TX
DECL|macro|MV64340_NAPI
mdefine_line|#define&t; MV64340_NAPI
DECL|macro|MV64340_TX_FAST_REFILL
mdefine_line|#define&t; MV64340_TX_FAST_REFILL
DECL|macro|MV64340_COAL
macro_line|#undef&t; MV64340_COAL
multiline_comment|/* &n; * Number of RX / TX descriptors on RX / TX rings.&n; * Note that allocating RX descriptors is done by allocating the RX&n; * ring AND a preallocated RX buffers (skb&squot;s) for each descriptor.&n; * The TX descriptors only allocates the TX descriptors ring,&n; * with no pre allocated TX buffers (skb&squot;s are allocated by higher layers.&n; */
multiline_comment|/* Default TX ring size is 1000 descriptors */
DECL|macro|MV64340_TX_QUEUE_SIZE
mdefine_line|#define MV64340_TX_QUEUE_SIZE 1000
multiline_comment|/* Default RX ring size is 400 descriptors */
DECL|macro|MV64340_RX_QUEUE_SIZE
mdefine_line|#define MV64340_RX_QUEUE_SIZE 400
DECL|macro|MV64340_TX_COAL
mdefine_line|#define MV64340_TX_COAL 100
macro_line|#ifdef MV64340_COAL
DECL|macro|MV64340_RX_COAL
mdefine_line|#define MV64340_RX_COAL 100
macro_line|#endif
multiline_comment|/*&n; * The second part is the low level driver of the gigE ethernet ports.   *&n; */
multiline_comment|/*&n; * Header File for : MV-643xx network interface header &n; *&n; * DESCRIPTION:&n; *       This header file contains macros typedefs and function declaration for&n; *       the Marvell Gig Bit Ethernet Controller. &n; *&n; * DEPENDENCIES:&n; *       None.&n; *&n; */
multiline_comment|/* Default port configuration value */
DECL|macro|PORT_CONFIG_VALUE
mdefine_line|#define PORT_CONFIG_VALUE                       &bslash;&n;             ETH_UNICAST_NORMAL_MODE&t;&t;|   &bslash;&n;             ETH_DEFAULT_RX_QUEUE_0&t;&t;|   &bslash;&n;             ETH_DEFAULT_RX_ARP_QUEUE_0&t;&t;|   &bslash;&n;             ETH_RECEIVE_BC_IF_NOT_IP_OR_ARP&t;|   &bslash;&n;             ETH_RECEIVE_BC_IF_IP&t;&t;|   &bslash;&n;             ETH_RECEIVE_BC_IF_ARP &t;&t;|   &bslash;&n;             ETH_CAPTURE_TCP_FRAMES_DIS&t;&t;|   &bslash;&n;             ETH_CAPTURE_UDP_FRAMES_DIS&t;&t;|   &bslash;&n;             ETH_DEFAULT_RX_TCP_QUEUE_0&t;&t;|   &bslash;&n;             ETH_DEFAULT_RX_UDP_QUEUE_0&t;&t;|   &bslash;&n;             ETH_DEFAULT_RX_BPDU_QUEUE_0
multiline_comment|/* Default port extend configuration value */
DECL|macro|PORT_CONFIG_EXTEND_VALUE
mdefine_line|#define PORT_CONFIG_EXTEND_VALUE&t;&t;&bslash;&n;             ETH_SPAN_BPDU_PACKETS_AS_NORMAL&t;|   &bslash;&n;             ETH_PARTITION_DISABLE
multiline_comment|/* Default sdma control value */
DECL|macro|PORT_SDMA_CONFIG_VALUE
mdefine_line|#define PORT_SDMA_CONFIG_VALUE&t;&t;&t;&bslash;&n;&t;&t;&t; ETH_RX_BURST_SIZE_16_64BIT &t;|&t;&bslash;&n;&t;&t;&t; GT_ETH_IPG_INT_RX(0) &t;&t;|&t;&bslash;&n;&t;&t;&t; ETH_TX_BURST_SIZE_16_64BIT;
DECL|macro|GT_ETH_IPG_INT_RX
mdefine_line|#define GT_ETH_IPG_INT_RX(value)                &bslash;&n;            ((value &amp; 0x3fff) &lt;&lt; 8)
multiline_comment|/* Default port serial control value */
DECL|macro|PORT_SERIAL_CONTROL_VALUE
mdefine_line|#define PORT_SERIAL_CONTROL_VALUE&t;&t;&bslash;&n;&t;&t;&t;ETH_FORCE_LINK_PASS &t;&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_ENABLE_AUTO_NEG_FOR_DUPLX&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_DISABLE_AUTO_NEG_FOR_FLOW_CTRL &t;|&t;&bslash;&n;&t;&t;&t;ETH_ADV_SYMMETRIC_FLOW_CTRL &t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_FORCE_FC_MODE_NO_PAUSE_DIS_TX &t;|&t;&bslash;&n;&t;&t;&t;ETH_FORCE_BP_MODE_NO_JAM &t;&t;|&t;&bslash;&n;&t;&t;&t;BIT9 &t;&t;&t;&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_DO_NOT_FORCE_LINK_FAIL &t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_RETRANSMIT_16_ATTEMPTS &t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_ENABLE_AUTO_NEG_SPEED_GMII&t; &t;|&t;&bslash;&n;&t;&t;&t;ETH_DTE_ADV_0 &t;&t;&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_DISABLE_AUTO_NEG_BYPASS&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_AUTO_NEG_NO_CHANGE &t;&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_MAX_RX_PACKET_9700BYTE &t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_CLR_EXT_LOOPBACK &t;&t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_SET_FULL_DUPLEX_MODE &t;&t;|&t;&bslash;&n;&t;&t;&t;ETH_ENABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX
DECL|macro|RX_BUFFER_MAX_SIZE
mdefine_line|#define RX_BUFFER_MAX_SIZE  0x4000000
DECL|macro|TX_BUFFER_MAX_SIZE
mdefine_line|#define TX_BUFFER_MAX_SIZE  0x4000000
multiline_comment|/* MAC accepet/reject macros */
DECL|macro|ACCEPT_MAC_ADDR
mdefine_line|#define ACCEPT_MAC_ADDR&t;    0
DECL|macro|REJECT_MAC_ADDR
mdefine_line|#define REJECT_MAC_ADDR&t;    1
multiline_comment|/* Buffer offset from buffer pointer */
DECL|macro|RX_BUF_OFFSET
mdefine_line|#define RX_BUF_OFFSET&t;&t;&t;&t;0x2
multiline_comment|/* Gigabit Ethernet Unit Global Registers */
multiline_comment|/* MIB Counters register definitions */
DECL|macro|ETH_MIB_GOOD_OCTETS_RECEIVED_LOW
mdefine_line|#define ETH_MIB_GOOD_OCTETS_RECEIVED_LOW   0x0
DECL|macro|ETH_MIB_GOOD_OCTETS_RECEIVED_HIGH
mdefine_line|#define ETH_MIB_GOOD_OCTETS_RECEIVED_HIGH  0x4
DECL|macro|ETH_MIB_BAD_OCTETS_RECEIVED
mdefine_line|#define ETH_MIB_BAD_OCTETS_RECEIVED        0x8
DECL|macro|ETH_MIB_INTERNAL_MAC_TRANSMIT_ERR
mdefine_line|#define ETH_MIB_INTERNAL_MAC_TRANSMIT_ERR  0xc
DECL|macro|ETH_MIB_GOOD_FRAMES_RECEIVED
mdefine_line|#define ETH_MIB_GOOD_FRAMES_RECEIVED       0x10
DECL|macro|ETH_MIB_BAD_FRAMES_RECEIVED
mdefine_line|#define ETH_MIB_BAD_FRAMES_RECEIVED        0x14
DECL|macro|ETH_MIB_BROADCAST_FRAMES_RECEIVED
mdefine_line|#define ETH_MIB_BROADCAST_FRAMES_RECEIVED  0x18
DECL|macro|ETH_MIB_MULTICAST_FRAMES_RECEIVED
mdefine_line|#define ETH_MIB_MULTICAST_FRAMES_RECEIVED  0x1c
DECL|macro|ETH_MIB_FRAMES_64_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_64_OCTETS           0x20
DECL|macro|ETH_MIB_FRAMES_65_TO_127_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_65_TO_127_OCTETS    0x24
DECL|macro|ETH_MIB_FRAMES_128_TO_255_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_128_TO_255_OCTETS   0x28
DECL|macro|ETH_MIB_FRAMES_256_TO_511_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_256_TO_511_OCTETS   0x2c
DECL|macro|ETH_MIB_FRAMES_512_TO_1023_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_512_TO_1023_OCTETS  0x30
DECL|macro|ETH_MIB_FRAMES_1024_TO_MAX_OCTETS
mdefine_line|#define ETH_MIB_FRAMES_1024_TO_MAX_OCTETS  0x34
DECL|macro|ETH_MIB_GOOD_OCTETS_SENT_LOW
mdefine_line|#define ETH_MIB_GOOD_OCTETS_SENT_LOW       0x38
DECL|macro|ETH_MIB_GOOD_OCTETS_SENT_HIGH
mdefine_line|#define ETH_MIB_GOOD_OCTETS_SENT_HIGH      0x3c
DECL|macro|ETH_MIB_GOOD_FRAMES_SENT
mdefine_line|#define ETH_MIB_GOOD_FRAMES_SENT           0x40
DECL|macro|ETH_MIB_EXCESSIVE_COLLISION
mdefine_line|#define ETH_MIB_EXCESSIVE_COLLISION        0x44
DECL|macro|ETH_MIB_MULTICAST_FRAMES_SENT
mdefine_line|#define ETH_MIB_MULTICAST_FRAMES_SENT      0x48
DECL|macro|ETH_MIB_BROADCAST_FRAMES_SENT
mdefine_line|#define ETH_MIB_BROADCAST_FRAMES_SENT      0x4c
DECL|macro|ETH_MIB_UNREC_MAC_CONTROL_RECEIVED
mdefine_line|#define ETH_MIB_UNREC_MAC_CONTROL_RECEIVED 0x50
DECL|macro|ETH_MIB_FC_SENT
mdefine_line|#define ETH_MIB_FC_SENT                    0x54
DECL|macro|ETH_MIB_GOOD_FC_RECEIVED
mdefine_line|#define ETH_MIB_GOOD_FC_RECEIVED           0x58
DECL|macro|ETH_MIB_BAD_FC_RECEIVED
mdefine_line|#define ETH_MIB_BAD_FC_RECEIVED            0x5c
DECL|macro|ETH_MIB_UNDERSIZE_RECEIVED
mdefine_line|#define ETH_MIB_UNDERSIZE_RECEIVED         0x60
DECL|macro|ETH_MIB_FRAGMENTS_RECEIVED
mdefine_line|#define ETH_MIB_FRAGMENTS_RECEIVED         0x64
DECL|macro|ETH_MIB_OVERSIZE_RECEIVED
mdefine_line|#define ETH_MIB_OVERSIZE_RECEIVED          0x68
DECL|macro|ETH_MIB_JABBER_RECEIVED
mdefine_line|#define ETH_MIB_JABBER_RECEIVED            0x6c
DECL|macro|ETH_MIB_MAC_RECEIVE_ERROR
mdefine_line|#define ETH_MIB_MAC_RECEIVE_ERROR          0x70
DECL|macro|ETH_MIB_BAD_CRC_EVENT
mdefine_line|#define ETH_MIB_BAD_CRC_EVENT              0x74
DECL|macro|ETH_MIB_COLLISION
mdefine_line|#define ETH_MIB_COLLISION                  0x78
DECL|macro|ETH_MIB_LATE_COLLISION
mdefine_line|#define ETH_MIB_LATE_COLLISION             0x7c
multiline_comment|/* Port serial status reg (PSR) */
DECL|macro|ETH_INTERFACE_GMII_MII
mdefine_line|#define ETH_INTERFACE_GMII_MII                          0
DECL|macro|ETH_INTERFACE_PCM
mdefine_line|#define ETH_INTERFACE_PCM                               BIT0
DECL|macro|ETH_LINK_IS_DOWN
mdefine_line|#define ETH_LINK_IS_DOWN                                0
DECL|macro|ETH_LINK_IS_UP
mdefine_line|#define ETH_LINK_IS_UP                                  BIT1
DECL|macro|ETH_PORT_AT_HALF_DUPLEX
mdefine_line|#define ETH_PORT_AT_HALF_DUPLEX                         0
DECL|macro|ETH_PORT_AT_FULL_DUPLEX
mdefine_line|#define ETH_PORT_AT_FULL_DUPLEX                         BIT2
DECL|macro|ETH_RX_FLOW_CTRL_DISABLED
mdefine_line|#define ETH_RX_FLOW_CTRL_DISABLED                       0
DECL|macro|ETH_RX_FLOW_CTRL_ENBALED
mdefine_line|#define ETH_RX_FLOW_CTRL_ENBALED                        BIT3
DECL|macro|ETH_GMII_SPEED_100_10
mdefine_line|#define ETH_GMII_SPEED_100_10                           0
DECL|macro|ETH_GMII_SPEED_1000
mdefine_line|#define ETH_GMII_SPEED_1000                             BIT4
DECL|macro|ETH_MII_SPEED_10
mdefine_line|#define ETH_MII_SPEED_10                                0
DECL|macro|ETH_MII_SPEED_100
mdefine_line|#define ETH_MII_SPEED_100                               BIT5
DECL|macro|ETH_NO_TX
mdefine_line|#define ETH_NO_TX                                       0
DECL|macro|ETH_TX_IN_PROGRESS
mdefine_line|#define ETH_TX_IN_PROGRESS                              BIT7
DECL|macro|ETH_BYPASS_NO_ACTIVE
mdefine_line|#define ETH_BYPASS_NO_ACTIVE                            0
DECL|macro|ETH_BYPASS_ACTIVE
mdefine_line|#define ETH_BYPASS_ACTIVE                               BIT8
DECL|macro|ETH_PORT_NOT_AT_PARTITION_STATE
mdefine_line|#define ETH_PORT_NOT_AT_PARTITION_STATE                 0
DECL|macro|ETH_PORT_AT_PARTITION_STATE
mdefine_line|#define ETH_PORT_AT_PARTITION_STATE                     BIT9
DECL|macro|ETH_PORT_TX_FIFO_NOT_EMPTY
mdefine_line|#define ETH_PORT_TX_FIFO_NOT_EMPTY                      0
DECL|macro|ETH_PORT_TX_FIFO_EMPTY
mdefine_line|#define ETH_PORT_TX_FIFO_EMPTY                          BIT10
multiline_comment|/* These macros describes the Port configuration reg (Px_cR) bits */
DECL|macro|ETH_UNICAST_NORMAL_MODE
mdefine_line|#define ETH_UNICAST_NORMAL_MODE                         0
DECL|macro|ETH_UNICAST_PROMISCUOUS_MODE
mdefine_line|#define ETH_UNICAST_PROMISCUOUS_MODE                    BIT0
DECL|macro|ETH_DEFAULT_RX_QUEUE_0
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_0                          0
DECL|macro|ETH_DEFAULT_RX_QUEUE_1
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_1                          BIT1
DECL|macro|ETH_DEFAULT_RX_QUEUE_2
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_2                          BIT2
DECL|macro|ETH_DEFAULT_RX_QUEUE_3
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_3                          (BIT2 | BIT1)
DECL|macro|ETH_DEFAULT_RX_QUEUE_4
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_4                          BIT3
DECL|macro|ETH_DEFAULT_RX_QUEUE_5
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_5                          (BIT3 | BIT1)
DECL|macro|ETH_DEFAULT_RX_QUEUE_6
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_6                          (BIT3 | BIT2)
DECL|macro|ETH_DEFAULT_RX_QUEUE_7
mdefine_line|#define ETH_DEFAULT_RX_QUEUE_7                          (BIT3 | BIT2 | BIT1)
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_0
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_0                      0
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_1
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_1                      BIT4
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_2
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_2                      BIT5
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_3
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_3                      (BIT5 | BIT4)
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_4
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_4                      BIT6
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_5
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_5                      (BIT6 | BIT4)
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_6
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_6                      (BIT6 | BIT5)
DECL|macro|ETH_DEFAULT_RX_ARP_QUEUE_7
mdefine_line|#define ETH_DEFAULT_RX_ARP_QUEUE_7                      (BIT6 | BIT5 | BIT4)
DECL|macro|ETH_RECEIVE_BC_IF_NOT_IP_OR_ARP
mdefine_line|#define ETH_RECEIVE_BC_IF_NOT_IP_OR_ARP                 0
DECL|macro|ETH_REJECT_BC_IF_NOT_IP_OR_ARP
mdefine_line|#define ETH_REJECT_BC_IF_NOT_IP_OR_ARP                  BIT7
DECL|macro|ETH_RECEIVE_BC_IF_IP
mdefine_line|#define ETH_RECEIVE_BC_IF_IP                            0
DECL|macro|ETH_REJECT_BC_IF_IP
mdefine_line|#define ETH_REJECT_BC_IF_IP                             BIT8
DECL|macro|ETH_RECEIVE_BC_IF_ARP
mdefine_line|#define ETH_RECEIVE_BC_IF_ARP                           0
DECL|macro|ETH_REJECT_BC_IF_ARP
mdefine_line|#define ETH_REJECT_BC_IF_ARP                            BIT9
DECL|macro|ETH_TX_AM_NO_UPDATE_ERROR_SUMMARY
mdefine_line|#define ETH_TX_AM_NO_UPDATE_ERROR_SUMMARY               BIT12
DECL|macro|ETH_CAPTURE_TCP_FRAMES_DIS
mdefine_line|#define ETH_CAPTURE_TCP_FRAMES_DIS                      0
DECL|macro|ETH_CAPTURE_TCP_FRAMES_EN
mdefine_line|#define ETH_CAPTURE_TCP_FRAMES_EN                       BIT14
DECL|macro|ETH_CAPTURE_UDP_FRAMES_DIS
mdefine_line|#define ETH_CAPTURE_UDP_FRAMES_DIS                      0
DECL|macro|ETH_CAPTURE_UDP_FRAMES_EN
mdefine_line|#define ETH_CAPTURE_UDP_FRAMES_EN                       BIT15
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_0
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_0                      0
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_1
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_1                      BIT16
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_2
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_2                      BIT17
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_3
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_3                      (BIT17 | BIT16)
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_4
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_4                      BIT18
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_5
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_5                      (BIT18 | BIT16)
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_6
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_6                      (BIT18 | BIT17)
DECL|macro|ETH_DEFAULT_RX_TCP_QUEUE_7
mdefine_line|#define ETH_DEFAULT_RX_TCP_QUEUE_7                      (BIT18 | BIT17 | BIT16)
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_0
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_0                      0
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_1
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_1                      BIT19
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_2
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_2                      BIT20
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_3
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_3                      (BIT20 | BIT19)
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_4
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_4                      (BIT21
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_5
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_5                      (BIT21 | BIT19)
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_6
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_6                      (BIT21 | BIT20)
DECL|macro|ETH_DEFAULT_RX_UDP_QUEUE_7
mdefine_line|#define ETH_DEFAULT_RX_UDP_QUEUE_7                      (BIT21 | BIT20 | BIT19)
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_0
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_0                      0
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_1
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_1                     BIT22
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_2
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_2                     BIT23
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_3
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_3                     (BIT23 | BIT22)
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_4
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_4                     BIT24
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_5
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_5                     (BIT24 | BIT22)
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_6
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_6                     (BIT24 | BIT23)
DECL|macro|ETH_DEFAULT_RX_BPDU_QUEUE_7
mdefine_line|#define ETH_DEFAULT_RX_BPDU_QUEUE_7                     (BIT24 | BIT23 | BIT22)
multiline_comment|/* These macros describes the Port configuration extend reg (Px_cXR) bits*/
DECL|macro|ETH_CLASSIFY_EN
mdefine_line|#define ETH_CLASSIFY_EN                                 BIT0
DECL|macro|ETH_SPAN_BPDU_PACKETS_AS_NORMAL
mdefine_line|#define ETH_SPAN_BPDU_PACKETS_AS_NORMAL                 0
DECL|macro|ETH_SPAN_BPDU_PACKETS_TO_RX_QUEUE_7
mdefine_line|#define ETH_SPAN_BPDU_PACKETS_TO_RX_QUEUE_7             BIT1
DECL|macro|ETH_PARTITION_DISABLE
mdefine_line|#define ETH_PARTITION_DISABLE                           0
DECL|macro|ETH_PARTITION_ENABLE
mdefine_line|#define ETH_PARTITION_ENABLE                            BIT2
multiline_comment|/* Tx/Rx queue command reg (RQCR/TQCR)*/
DECL|macro|ETH_QUEUE_0_ENABLE
mdefine_line|#define ETH_QUEUE_0_ENABLE                              BIT0
DECL|macro|ETH_QUEUE_1_ENABLE
mdefine_line|#define ETH_QUEUE_1_ENABLE                              BIT1
DECL|macro|ETH_QUEUE_2_ENABLE
mdefine_line|#define ETH_QUEUE_2_ENABLE                              BIT2
DECL|macro|ETH_QUEUE_3_ENABLE
mdefine_line|#define ETH_QUEUE_3_ENABLE                              BIT3
DECL|macro|ETH_QUEUE_4_ENABLE
mdefine_line|#define ETH_QUEUE_4_ENABLE                              BIT4
DECL|macro|ETH_QUEUE_5_ENABLE
mdefine_line|#define ETH_QUEUE_5_ENABLE                              BIT5
DECL|macro|ETH_QUEUE_6_ENABLE
mdefine_line|#define ETH_QUEUE_6_ENABLE                              BIT6
DECL|macro|ETH_QUEUE_7_ENABLE
mdefine_line|#define ETH_QUEUE_7_ENABLE                              BIT7
DECL|macro|ETH_QUEUE_0_DISABLE
mdefine_line|#define ETH_QUEUE_0_DISABLE                             BIT8
DECL|macro|ETH_QUEUE_1_DISABLE
mdefine_line|#define ETH_QUEUE_1_DISABLE                             BIT9
DECL|macro|ETH_QUEUE_2_DISABLE
mdefine_line|#define ETH_QUEUE_2_DISABLE                             BIT10
DECL|macro|ETH_QUEUE_3_DISABLE
mdefine_line|#define ETH_QUEUE_3_DISABLE                             BIT11
DECL|macro|ETH_QUEUE_4_DISABLE
mdefine_line|#define ETH_QUEUE_4_DISABLE                             BIT12
DECL|macro|ETH_QUEUE_5_DISABLE
mdefine_line|#define ETH_QUEUE_5_DISABLE                             BIT13
DECL|macro|ETH_QUEUE_6_DISABLE
mdefine_line|#define ETH_QUEUE_6_DISABLE                             BIT14
DECL|macro|ETH_QUEUE_7_DISABLE
mdefine_line|#define ETH_QUEUE_7_DISABLE                             BIT15
multiline_comment|/* These macros describes the Port Sdma configuration reg (SDCR) bits */
DECL|macro|ETH_RIFB
mdefine_line|#define ETH_RIFB                                        BIT0
DECL|macro|ETH_RX_BURST_SIZE_1_64BIT
mdefine_line|#define ETH_RX_BURST_SIZE_1_64BIT                       0
DECL|macro|ETH_RX_BURST_SIZE_2_64BIT
mdefine_line|#define ETH_RX_BURST_SIZE_2_64BIT                       BIT1
DECL|macro|ETH_RX_BURST_SIZE_4_64BIT
mdefine_line|#define ETH_RX_BURST_SIZE_4_64BIT                       BIT2
DECL|macro|ETH_RX_BURST_SIZE_8_64BIT
mdefine_line|#define ETH_RX_BURST_SIZE_8_64BIT                       (BIT2 | BIT1)
DECL|macro|ETH_RX_BURST_SIZE_16_64BIT
mdefine_line|#define ETH_RX_BURST_SIZE_16_64BIT                      BIT3
DECL|macro|ETH_BLM_RX_NO_SWAP
mdefine_line|#define ETH_BLM_RX_NO_SWAP                              BIT4
DECL|macro|ETH_BLM_RX_BYTE_SWAP
mdefine_line|#define ETH_BLM_RX_BYTE_SWAP                            0
DECL|macro|ETH_BLM_TX_NO_SWAP
mdefine_line|#define ETH_BLM_TX_NO_SWAP                              BIT5
DECL|macro|ETH_BLM_TX_BYTE_SWAP
mdefine_line|#define ETH_BLM_TX_BYTE_SWAP                            0
DECL|macro|ETH_DESCRIPTORS_BYTE_SWAP
mdefine_line|#define ETH_DESCRIPTORS_BYTE_SWAP                       BIT6
DECL|macro|ETH_DESCRIPTORS_NO_SWAP
mdefine_line|#define ETH_DESCRIPTORS_NO_SWAP                         0
DECL|macro|ETH_TX_BURST_SIZE_1_64BIT
mdefine_line|#define ETH_TX_BURST_SIZE_1_64BIT                       0
DECL|macro|ETH_TX_BURST_SIZE_2_64BIT
mdefine_line|#define ETH_TX_BURST_SIZE_2_64BIT                       BIT22
DECL|macro|ETH_TX_BURST_SIZE_4_64BIT
mdefine_line|#define ETH_TX_BURST_SIZE_4_64BIT                       BIT23
DECL|macro|ETH_TX_BURST_SIZE_8_64BIT
mdefine_line|#define ETH_TX_BURST_SIZE_8_64BIT                       (BIT23 | BIT22)
DECL|macro|ETH_TX_BURST_SIZE_16_64BIT
mdefine_line|#define ETH_TX_BURST_SIZE_16_64BIT                      BIT24
multiline_comment|/* These macros describes the Port serial control reg (PSCR) bits */
DECL|macro|ETH_SERIAL_PORT_DISABLE
mdefine_line|#define ETH_SERIAL_PORT_DISABLE                         0
DECL|macro|ETH_SERIAL_PORT_ENABLE
mdefine_line|#define ETH_SERIAL_PORT_ENABLE                          BIT0
DECL|macro|ETH_FORCE_LINK_PASS
mdefine_line|#define ETH_FORCE_LINK_PASS                             BIT1
DECL|macro|ETH_DO_NOT_FORCE_LINK_PASS
mdefine_line|#define ETH_DO_NOT_FORCE_LINK_PASS                      0
DECL|macro|ETH_ENABLE_AUTO_NEG_FOR_DUPLX
mdefine_line|#define ETH_ENABLE_AUTO_NEG_FOR_DUPLX                   0
DECL|macro|ETH_DISABLE_AUTO_NEG_FOR_DUPLX
mdefine_line|#define ETH_DISABLE_AUTO_NEG_FOR_DUPLX                  BIT2
DECL|macro|ETH_ENABLE_AUTO_NEG_FOR_FLOW_CTRL
mdefine_line|#define ETH_ENABLE_AUTO_NEG_FOR_FLOW_CTRL               0
DECL|macro|ETH_DISABLE_AUTO_NEG_FOR_FLOW_CTRL
mdefine_line|#define ETH_DISABLE_AUTO_NEG_FOR_FLOW_CTRL              BIT3
DECL|macro|ETH_ADV_NO_FLOW_CTRL
mdefine_line|#define ETH_ADV_NO_FLOW_CTRL                            0
DECL|macro|ETH_ADV_SYMMETRIC_FLOW_CTRL
mdefine_line|#define ETH_ADV_SYMMETRIC_FLOW_CTRL                     BIT4
DECL|macro|ETH_FORCE_FC_MODE_NO_PAUSE_DIS_TX
mdefine_line|#define ETH_FORCE_FC_MODE_NO_PAUSE_DIS_TX               0
DECL|macro|ETH_FORCE_FC_MODE_TX_PAUSE_DIS
mdefine_line|#define ETH_FORCE_FC_MODE_TX_PAUSE_DIS                  BIT5
DECL|macro|ETH_FORCE_BP_MODE_NO_JAM
mdefine_line|#define ETH_FORCE_BP_MODE_NO_JAM                        0
DECL|macro|ETH_FORCE_BP_MODE_JAM_TX
mdefine_line|#define ETH_FORCE_BP_MODE_JAM_TX                        BIT7
DECL|macro|ETH_FORCE_BP_MODE_JAM_TX_ON_RX_ERR
mdefine_line|#define ETH_FORCE_BP_MODE_JAM_TX_ON_RX_ERR              BIT8
DECL|macro|ETH_FORCE_LINK_FAIL
mdefine_line|#define ETH_FORCE_LINK_FAIL                             0
DECL|macro|ETH_DO_NOT_FORCE_LINK_FAIL
mdefine_line|#define ETH_DO_NOT_FORCE_LINK_FAIL                      BIT10
DECL|macro|ETH_RETRANSMIT_16_ATTEMPTS
mdefine_line|#define ETH_RETRANSMIT_16_ATTEMPTS                      0
DECL|macro|ETH_RETRANSMIT_FOREVER
mdefine_line|#define ETH_RETRANSMIT_FOREVER                          BIT11
DECL|macro|ETH_DISABLE_AUTO_NEG_SPEED_GMII
mdefine_line|#define ETH_DISABLE_AUTO_NEG_SPEED_GMII                 BIT13
DECL|macro|ETH_ENABLE_AUTO_NEG_SPEED_GMII
mdefine_line|#define ETH_ENABLE_AUTO_NEG_SPEED_GMII                  0
DECL|macro|ETH_DTE_ADV_0
mdefine_line|#define ETH_DTE_ADV_0                                   0
DECL|macro|ETH_DTE_ADV_1
mdefine_line|#define ETH_DTE_ADV_1                                   BIT14
DECL|macro|ETH_DISABLE_AUTO_NEG_BYPASS
mdefine_line|#define ETH_DISABLE_AUTO_NEG_BYPASS                     0
DECL|macro|ETH_ENABLE_AUTO_NEG_BYPASS
mdefine_line|#define ETH_ENABLE_AUTO_NEG_BYPASS                      BIT15
DECL|macro|ETH_AUTO_NEG_NO_CHANGE
mdefine_line|#define ETH_AUTO_NEG_NO_CHANGE                          0
DECL|macro|ETH_RESTART_AUTO_NEG
mdefine_line|#define ETH_RESTART_AUTO_NEG                            BIT16
DECL|macro|ETH_MAX_RX_PACKET_1518BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_1518BYTE                      0
DECL|macro|ETH_MAX_RX_PACKET_1522BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_1522BYTE                      BIT17
DECL|macro|ETH_MAX_RX_PACKET_1552BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_1552BYTE                      BIT18
DECL|macro|ETH_MAX_RX_PACKET_9022BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_9022BYTE                      (BIT18 | BIT17)
DECL|macro|ETH_MAX_RX_PACKET_9192BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_9192BYTE                      BIT19
DECL|macro|ETH_MAX_RX_PACKET_9700BYTE
mdefine_line|#define ETH_MAX_RX_PACKET_9700BYTE                      (BIT19 | BIT17)
DECL|macro|ETH_SET_EXT_LOOPBACK
mdefine_line|#define ETH_SET_EXT_LOOPBACK                            BIT20
DECL|macro|ETH_CLR_EXT_LOOPBACK
mdefine_line|#define ETH_CLR_EXT_LOOPBACK                            0
DECL|macro|ETH_SET_FULL_DUPLEX_MODE
mdefine_line|#define ETH_SET_FULL_DUPLEX_MODE                        BIT21
DECL|macro|ETH_SET_HALF_DUPLEX_MODE
mdefine_line|#define ETH_SET_HALF_DUPLEX_MODE                        0
DECL|macro|ETH_ENABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX
mdefine_line|#define ETH_ENABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX       BIT22
DECL|macro|ETH_DISABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX
mdefine_line|#define ETH_DISABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX      0
DECL|macro|ETH_SET_GMII_SPEED_TO_10_100
mdefine_line|#define ETH_SET_GMII_SPEED_TO_10_100                    0
DECL|macro|ETH_SET_GMII_SPEED_TO_1000
mdefine_line|#define ETH_SET_GMII_SPEED_TO_1000                      BIT23
DECL|macro|ETH_SET_MII_SPEED_TO_10
mdefine_line|#define ETH_SET_MII_SPEED_TO_10                         0
DECL|macro|ETH_SET_MII_SPEED_TO_100
mdefine_line|#define ETH_SET_MII_SPEED_TO_100                        BIT24
multiline_comment|/* SMI reg */
DECL|macro|ETH_SMI_BUSY
mdefine_line|#define ETH_SMI_BUSY        &t;BIT28&t;/* 0 - Write, 1 - Read          */
DECL|macro|ETH_SMI_READ_VALID
mdefine_line|#define ETH_SMI_READ_VALID  &t;BIT27&t;/* 0 - Write, 1 - Read          */
DECL|macro|ETH_SMI_OPCODE_WRITE
mdefine_line|#define ETH_SMI_OPCODE_WRITE&t;0&t;/* Completion of Read operation */
DECL|macro|ETH_SMI_OPCODE_READ
mdefine_line|#define ETH_SMI_OPCODE_READ &t;BIT26&t;/* Operation is in progress             */
multiline_comment|/* SDMA command status fields macros */
multiline_comment|/* Tx &amp; Rx descriptors status */
DECL|macro|ETH_ERROR_SUMMARY
mdefine_line|#define ETH_ERROR_SUMMARY                   (BIT0)
multiline_comment|/* Tx &amp; Rx descriptors command */
DECL|macro|ETH_BUFFER_OWNED_BY_DMA
mdefine_line|#define ETH_BUFFER_OWNED_BY_DMA             (BIT31)
multiline_comment|/* Tx descriptors status */
DECL|macro|ETH_LC_ERROR
mdefine_line|#define ETH_LC_ERROR                        (0&t;  )
DECL|macro|ETH_UR_ERROR
mdefine_line|#define ETH_UR_ERROR                        (BIT1 )
DECL|macro|ETH_RL_ERROR
mdefine_line|#define ETH_RL_ERROR                        (BIT2 )
DECL|macro|ETH_LLC_SNAP_FORMAT
mdefine_line|#define ETH_LLC_SNAP_FORMAT                 (BIT9 )
multiline_comment|/* Rx descriptors status */
DECL|macro|ETH_CRC_ERROR
mdefine_line|#define ETH_CRC_ERROR                       (0&t;  )
DECL|macro|ETH_OVERRUN_ERROR
mdefine_line|#define ETH_OVERRUN_ERROR                   (BIT1 )
DECL|macro|ETH_MAX_FRAME_LENGTH_ERROR
mdefine_line|#define ETH_MAX_FRAME_LENGTH_ERROR          (BIT2 )
DECL|macro|ETH_RESOURCE_ERROR
mdefine_line|#define ETH_RESOURCE_ERROR                  ((BIT2 | BIT1))
DECL|macro|ETH_VLAN_TAGGED
mdefine_line|#define ETH_VLAN_TAGGED                     (BIT19)
DECL|macro|ETH_BPDU_FRAME
mdefine_line|#define ETH_BPDU_FRAME                      (BIT20)
DECL|macro|ETH_TCP_FRAME_OVER_IP_V_4
mdefine_line|#define ETH_TCP_FRAME_OVER_IP_V_4           (0    )
DECL|macro|ETH_UDP_FRAME_OVER_IP_V_4
mdefine_line|#define ETH_UDP_FRAME_OVER_IP_V_4           (BIT21)
DECL|macro|ETH_OTHER_FRAME_TYPE
mdefine_line|#define ETH_OTHER_FRAME_TYPE                (BIT22)
DECL|macro|ETH_LAYER_2_IS_ETH_V_2
mdefine_line|#define ETH_LAYER_2_IS_ETH_V_2              (BIT23)
DECL|macro|ETH_FRAME_TYPE_IP_V_4
mdefine_line|#define ETH_FRAME_TYPE_IP_V_4               (BIT24)
DECL|macro|ETH_FRAME_HEADER_OK
mdefine_line|#define ETH_FRAME_HEADER_OK                 (BIT25)
DECL|macro|ETH_RX_LAST_DESC
mdefine_line|#define ETH_RX_LAST_DESC                    (BIT26)
DECL|macro|ETH_RX_FIRST_DESC
mdefine_line|#define ETH_RX_FIRST_DESC                   (BIT27)
DECL|macro|ETH_UNKNOWN_DESTINATION_ADDR
mdefine_line|#define ETH_UNKNOWN_DESTINATION_ADDR        (BIT28)
DECL|macro|ETH_RX_ENABLE_INTERRUPT
mdefine_line|#define ETH_RX_ENABLE_INTERRUPT             (BIT29)
DECL|macro|ETH_LAYER_4_CHECKSUM_OK
mdefine_line|#define ETH_LAYER_4_CHECKSUM_OK             (BIT30)
multiline_comment|/* Rx descriptors byte count */
DECL|macro|ETH_FRAME_FRAGMENTED
mdefine_line|#define ETH_FRAME_FRAGMENTED                (BIT2)
multiline_comment|/* Tx descriptors command */
DECL|macro|ETH_LAYER_4_CHECKSUM_FIRST_DESC
mdefine_line|#define ETH_LAYER_4_CHECKSUM_FIRST_DESC&t;&t;(BIT10)
DECL|macro|ETH_FRAME_SET_TO_VLAN
mdefine_line|#define ETH_FRAME_SET_TO_VLAN               (BIT15)
DECL|macro|ETH_TCP_FRAME
mdefine_line|#define ETH_TCP_FRAME                       (0&t;  )
DECL|macro|ETH_UDP_FRAME
mdefine_line|#define ETH_UDP_FRAME                       (BIT16)
DECL|macro|ETH_GEN_TCP_UDP_CHECKSUM
mdefine_line|#define ETH_GEN_TCP_UDP_CHECKSUM            (BIT17)
DECL|macro|ETH_GEN_IP_V_4_CHECKSUM
mdefine_line|#define ETH_GEN_IP_V_4_CHECKSUM             (BIT18)
DECL|macro|ETH_ZERO_PADDING
mdefine_line|#define ETH_ZERO_PADDING                    (BIT19)
DECL|macro|ETH_TX_LAST_DESC
mdefine_line|#define ETH_TX_LAST_DESC                    (BIT20)
DECL|macro|ETH_TX_FIRST_DESC
mdefine_line|#define ETH_TX_FIRST_DESC                   (BIT21)
DECL|macro|ETH_GEN_CRC
mdefine_line|#define ETH_GEN_CRC                         (BIT22)
DECL|macro|ETH_TX_ENABLE_INTERRUPT
mdefine_line|#define ETH_TX_ENABLE_INTERRUPT             (BIT23)
DECL|macro|ETH_AUTO_MODE
mdefine_line|#define ETH_AUTO_MODE                       (BIT30)
multiline_comment|/* typedefs */
DECL|enum|_eth_func_ret_status
r_typedef
r_enum
id|_eth_func_ret_status
(brace
DECL|enumerator|ETH_OK
id|ETH_OK
comma
multiline_comment|/* Returned as expected.                    */
DECL|enumerator|ETH_ERROR
id|ETH_ERROR
comma
multiline_comment|/* Fundamental error.                       */
DECL|enumerator|ETH_RETRY
id|ETH_RETRY
comma
multiline_comment|/* Could not process request. Try later.    */
DECL|enumerator|ETH_END_OF_JOB
id|ETH_END_OF_JOB
comma
multiline_comment|/* Ring has nothing to process.             */
DECL|enumerator|ETH_QUEUE_FULL
id|ETH_QUEUE_FULL
comma
multiline_comment|/* Ring resource error.                     */
DECL|enumerator|ETH_QUEUE_LAST_RESOURCE
id|ETH_QUEUE_LAST_RESOURCE
multiline_comment|/* Ring resources about to exhaust.         */
DECL|typedef|ETH_FUNC_RET_STATUS
)brace
id|ETH_FUNC_RET_STATUS
suffix:semicolon
DECL|enum|_eth_target
r_typedef
r_enum
id|_eth_target
(brace
DECL|enumerator|ETH_TARGET_DRAM
id|ETH_TARGET_DRAM
comma
DECL|enumerator|ETH_TARGET_DEVICE
id|ETH_TARGET_DEVICE
comma
DECL|enumerator|ETH_TARGET_CBS
id|ETH_TARGET_CBS
comma
DECL|enumerator|ETH_TARGET_PCI0
id|ETH_TARGET_PCI0
comma
DECL|enumerator|ETH_TARGET_PCI1
id|ETH_TARGET_PCI1
DECL|typedef|ETH_TARGET
)brace
id|ETH_TARGET
suffix:semicolon
multiline_comment|/* These are for big-endian machines.  Little endian needs different&n; * definitions.&n; */
macro_line|#if defined(__BIG_ENDIAN)
DECL|struct|eth_rx_desc
r_struct
id|eth_rx_desc
(brace
DECL|member|byte_cnt
id|u16
id|byte_cnt
suffix:semicolon
multiline_comment|/* Descriptor buffer byte count     */
DECL|member|buf_size
id|u16
id|buf_size
suffix:semicolon
multiline_comment|/* Buffer size                      */
DECL|member|cmd_sts
id|u32
id|cmd_sts
suffix:semicolon
multiline_comment|/* Descriptor command status        */
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
multiline_comment|/* Next descriptor pointer          */
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
multiline_comment|/* Descriptor buffer pointer        */
)brace
suffix:semicolon
DECL|struct|eth_tx_desc
r_struct
id|eth_tx_desc
(brace
DECL|member|byte_cnt
id|u16
id|byte_cnt
suffix:semicolon
multiline_comment|/* buffer byte count */
DECL|member|l4i_chk
id|u16
id|l4i_chk
suffix:semicolon
multiline_comment|/* CPU provided TCP checksum */
DECL|member|cmd_sts
id|u32
id|cmd_sts
suffix:semicolon
multiline_comment|/* Command/status field */
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
multiline_comment|/* Pointer to next descriptor */
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
multiline_comment|/* pointer to buffer for this descriptor */
)brace
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN)
DECL|struct|eth_rx_desc
r_struct
id|eth_rx_desc
(brace
DECL|member|cmd_sts
id|u32
id|cmd_sts
suffix:semicolon
multiline_comment|/* Descriptor command status        */
DECL|member|buf_size
id|u16
id|buf_size
suffix:semicolon
multiline_comment|/* Buffer size                      */
DECL|member|byte_cnt
id|u16
id|byte_cnt
suffix:semicolon
multiline_comment|/* Descriptor buffer byte count     */
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
multiline_comment|/* Descriptor buffer pointer        */
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
multiline_comment|/* Next descriptor pointer          */
)brace
suffix:semicolon
DECL|struct|eth_tx_desc
r_struct
id|eth_tx_desc
(brace
DECL|member|cmd_sts
id|u32
id|cmd_sts
suffix:semicolon
multiline_comment|/* Command/status field */
DECL|member|l4i_chk
id|u16
id|l4i_chk
suffix:semicolon
multiline_comment|/* CPU provided TCP checksum */
DECL|member|byte_cnt
id|u16
id|byte_cnt
suffix:semicolon
multiline_comment|/* buffer byte count */
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
multiline_comment|/* pointer to buffer for this descriptor */
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
multiline_comment|/* Pointer to next descriptor */
)brace
suffix:semicolon
macro_line|#else
macro_line|#error One of __BIG_ENDIAN or __LITTLE_ENDIAN must be defined
macro_line|#endif
multiline_comment|/* Unified struct for Rx and Tx operations. The user is not required to */
multiline_comment|/* be familier with neither Tx nor Rx descriptors.                       */
DECL|struct|pkt_info
r_struct
id|pkt_info
(brace
DECL|member|byte_cnt
r_int
r_int
id|byte_cnt
suffix:semicolon
multiline_comment|/* Descriptor buffer byte count     */
DECL|member|l4i_chk
r_int
r_int
id|l4i_chk
suffix:semicolon
multiline_comment|/* Tx CPU provided TCP Checksum     */
DECL|member|cmd_sts
r_int
r_int
id|cmd_sts
suffix:semicolon
multiline_comment|/* Descriptor command status        */
DECL|member|buf_ptr
id|dma_addr_t
id|buf_ptr
suffix:semicolon
multiline_comment|/* Descriptor buffer pointer        */
DECL|member|return_info
r_struct
id|sk_buff
op_star
id|return_info
suffix:semicolon
multiline_comment|/* User resource return information */
)brace
suffix:semicolon
multiline_comment|/* Ethernet port specific infomation */
DECL|struct|mv64340_private
r_struct
id|mv64340_private
(brace
DECL|member|port_num
r_int
id|port_num
suffix:semicolon
multiline_comment|/* User Ethernet port number */
DECL|member|port_mac_addr
id|u8
id|port_mac_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* User defined port MAC address. */
DECL|member|port_config
id|u32
id|port_config
suffix:semicolon
multiline_comment|/* User port configuration value */
DECL|member|port_config_extend
id|u32
id|port_config_extend
suffix:semicolon
multiline_comment|/* User port config extend value */
DECL|member|port_sdma_config
id|u32
id|port_sdma_config
suffix:semicolon
multiline_comment|/* User port SDMA config value */
DECL|member|port_serial_control
id|u32
id|port_serial_control
suffix:semicolon
multiline_comment|/* User port serial control value */
DECL|member|port_tx_queue_command
id|u32
id|port_tx_queue_command
suffix:semicolon
multiline_comment|/* Port active Tx queues summary */
DECL|member|port_rx_queue_command
id|u32
id|port_rx_queue_command
suffix:semicolon
multiline_comment|/* Port active Rx queues summary */
DECL|member|rx_resource_err
r_int
id|rx_resource_err
suffix:semicolon
multiline_comment|/* Rx ring resource error flag */
DECL|member|tx_resource_err
r_int
id|tx_resource_err
suffix:semicolon
multiline_comment|/* Tx ring resource error flag */
multiline_comment|/* Tx/Rx rings managment indexes fields. For driver use */
multiline_comment|/* Next available and first returning Rx resource */
DECL|member|rx_curr_desc_q
DECL|member|rx_used_desc_q
r_int
id|rx_curr_desc_q
comma
id|rx_used_desc_q
suffix:semicolon
multiline_comment|/* Next available and first returning Tx resource */
DECL|member|tx_curr_desc_q
DECL|member|tx_used_desc_q
r_int
id|tx_curr_desc_q
comma
id|tx_used_desc_q
suffix:semicolon
macro_line|#ifdef MV64340_CHECKSUM_OFFLOAD_TX
DECL|member|tx_first_desc_q
r_int
id|tx_first_desc_q
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MV64340_TX_FAST_REFILL
DECL|member|tx_clean_threshold
id|u32
id|tx_clean_threshold
suffix:semicolon
macro_line|#endif
DECL|member|p_rx_desc_area
r_volatile
r_struct
id|eth_rx_desc
op_star
id|p_rx_desc_area
suffix:semicolon
DECL|member|rx_desc_dma
id|dma_addr_t
id|rx_desc_dma
suffix:semicolon
DECL|member|rx_desc_area_size
r_int
r_int
id|rx_desc_area_size
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
(braket
id|MV64340_RX_QUEUE_SIZE
)braket
suffix:semicolon
DECL|member|p_tx_desc_area
r_volatile
r_struct
id|eth_tx_desc
op_star
id|p_tx_desc_area
suffix:semicolon
DECL|member|tx_desc_dma
id|dma_addr_t
id|tx_desc_dma
suffix:semicolon
DECL|member|tx_desc_area_size
r_int
r_int
id|tx_desc_area_size
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
(braket
id|MV64340_TX_QUEUE_SIZE
)braket
suffix:semicolon
DECL|member|tx_timeout_task
r_struct
id|work_struct
id|tx_timeout_task
suffix:semicolon
multiline_comment|/*&n;&t; * Former struct mv64340_eth_priv members start here&n;&t; */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Size of Tx Ring per queue */
DECL|member|tx_ring_size
r_int
r_int
id|tx_ring_size
suffix:semicolon
multiline_comment|/* Ammont of SKBs outstanding on Tx queue */
DECL|member|tx_ring_skbs
r_int
r_int
id|tx_ring_skbs
suffix:semicolon
multiline_comment|/* Size of Rx Ring per queue */
DECL|member|rx_ring_size
r_int
r_int
id|rx_ring_size
suffix:semicolon
multiline_comment|/* Ammount of SKBs allocated to Rx Ring per queue */
DECL|member|rx_ring_skbs
r_int
r_int
id|rx_ring_skbs
suffix:semicolon
multiline_comment|/*&n;&t; * rx_task used to fill RX ring out of bottom half context &n;&t; */
DECL|member|rx_task
r_struct
id|work_struct
id|rx_task
suffix:semicolon
multiline_comment|/* &n;&t; * Used in case RX Ring is empty, which can be caused when &n;&t; * system does not have resources (skb&squot;s) &n;&t; */
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|rx_task_busy
r_int
id|rx_task_busy
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|rx_timer_flag
r_int
id|rx_timer_flag
suffix:semicolon
DECL|member|rx_int_coal
id|u32
id|rx_int_coal
suffix:semicolon
DECL|member|tx_int_coal
id|u32
id|tx_int_coal
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ethernet.h API list */
multiline_comment|/* Port operation control routines */
r_static
r_void
id|eth_port_init
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
)paren
suffix:semicolon
r_static
r_void
id|eth_port_reset
c_func
(paren
r_int
r_int
id|eth_port_num
)paren
suffix:semicolon
r_static
r_int
id|eth_port_start
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
)paren
suffix:semicolon
r_static
r_void
id|ethernet_set_config_reg
c_func
(paren
r_int
r_int
id|eth_port_num
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_static
r_int
r_int
id|ethernet_get_config_reg
c_func
(paren
r_int
r_int
id|eth_port_num
)paren
suffix:semicolon
multiline_comment|/* Port MAC address routines */
r_static
r_void
id|eth_port_uc_addr_set
c_func
(paren
r_int
r_int
id|eth_port_num
comma
r_int
r_char
op_star
id|p_addr
)paren
suffix:semicolon
multiline_comment|/* PHY and MIB routines */
r_static
r_void
id|ethernet_phy_reset
c_func
(paren
r_int
r_int
id|eth_port_num
)paren
suffix:semicolon
r_static
r_void
id|eth_port_write_smi_reg
c_func
(paren
r_int
r_int
id|eth_port_num
comma
r_int
r_int
id|phy_reg
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_static
r_void
id|eth_port_read_smi_reg
c_func
(paren
r_int
r_int
id|eth_port_num
comma
r_int
r_int
id|phy_reg
comma
r_int
r_int
op_star
id|value
)paren
suffix:semicolon
r_static
r_void
id|eth_clear_mib_counters
c_func
(paren
r_int
r_int
id|eth_port_num
)paren
suffix:semicolon
multiline_comment|/* Port data flow control routines */
r_static
id|ETH_FUNC_RET_STATUS
id|eth_port_send
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
comma
r_struct
id|pkt_info
op_star
id|p_pkt_info
)paren
suffix:semicolon
r_static
id|ETH_FUNC_RET_STATUS
id|eth_tx_return_desc
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
comma
r_struct
id|pkt_info
op_star
id|p_pkt_info
)paren
suffix:semicolon
r_static
id|ETH_FUNC_RET_STATUS
id|eth_port_receive
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
comma
r_struct
id|pkt_info
op_star
id|p_pkt_info
)paren
suffix:semicolon
r_static
id|ETH_FUNC_RET_STATUS
id|eth_rx_return_buff
c_func
(paren
r_struct
id|mv64340_private
op_star
id|mp
comma
r_struct
id|pkt_info
op_star
id|p_pkt_info
)paren
suffix:semicolon
macro_line|#endif  /* __MV64340_ETH_H__ */
eof
