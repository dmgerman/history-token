multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * SAA9730 ethernet driver description.&n; *&n; */
macro_line|#ifndef _SAA9730_H
DECL|macro|_SAA9730_H
mdefine_line|#define _SAA9730_H
multiline_comment|/* Number of 6-byte entries in the CAM. */
DECL|macro|LAN_SAA9730_CAM_ENTRIES
mdefine_line|#define LAN_SAA9730_CAM_ENTRIES              10
DECL|macro|LAN_SAA9730_CAM_DWORDS
mdefine_line|#define&t;LAN_SAA9730_CAM_DWORDS               ((LAN_SAA9730_CAM_ENTRIES*6)/4)
multiline_comment|/* TX and RX packet size: fixed to 2048 bytes, according to HW requirements. */
DECL|macro|LAN_SAA9730_PACKET_SIZE
mdefine_line|#define LAN_SAA9730_PACKET_SIZE                       2048
multiline_comment|/* &n; * Number of TX buffers = number of RX buffers = 2, which is fixed according &n; * to HW requirements. &n; */
DECL|macro|LAN_SAA9730_BUFFERS
mdefine_line|#define LAN_SAA9730_BUFFERS                           2
multiline_comment|/* Number of RX packets per RX buffer. */
DECL|macro|LAN_SAA9730_RCV_Q_SIZE
mdefine_line|#define LAN_SAA9730_RCV_Q_SIZE                        15
multiline_comment|/* Number of TX packets per TX buffer. */
DECL|macro|LAN_SAA9730_TXM_Q_SIZE
mdefine_line|#define LAN_SAA9730_TXM_Q_SIZE                        15
multiline_comment|/*&n; * We get an interrupt for each LAN_SAA9730_DEFAULT_RCV_Q_INT_THRESHOLD &n; * packets received. &n; * If however we receive less than  LAN_SAA9730_DEFAULT_RCV_Q_INT_THRESHOLD&n; * packets, the hardware can timeout after a certain time and still tell &n; * us packets have arrived.&n; * The timeout value in unit of 32 PCI clocks (33Mhz).&n; * The value 200 approximates 0.0002 seconds.&n; */
DECL|macro|LAN_SAA9730_RCV_Q_INT_THRESHOLD
mdefine_line|#define LAN_SAA9730_RCV_Q_INT_THRESHOLD               1
DECL|macro|LAN_SAA9730_DEFAULT_TIME_OUT_CNT
mdefine_line|#define LAN_SAA9730_DEFAULT_TIME_OUT_CNT              10
DECL|macro|RXSF_NDIS
mdefine_line|#define RXSF_NDIS                       0
DECL|macro|RXSF_READY
mdefine_line|#define RXSF_READY                      2
DECL|macro|RXSF_HWDONE
mdefine_line|#define RXSF_HWDONE                     3
DECL|macro|TXSF_EMPTY
mdefine_line|#define TXSF_EMPTY                      0
DECL|macro|TXSF_READY
mdefine_line|#define TXSF_READY                      2
DECL|macro|TXSF_HWDONE
mdefine_line|#define TXSF_HWDONE                     3
DECL|macro|LANEND_LITTLE
mdefine_line|#define LANEND_LITTLE                   0
DECL|macro|LANEND_BIG_2143
mdefine_line|#define LANEND_BIG_2143                 1
DECL|macro|LANEND_BIG_4321
mdefine_line|#define LANEND_BIG_4321                 2
DECL|macro|LANMB_ANY
mdefine_line|#define LANMB_ANY                       0
DECL|macro|LANMB_8
mdefine_line|#define LANMB_8                         1
DECL|macro|LANMB_32
mdefine_line|#define LANMB_32                        2
DECL|macro|LANMB_64
mdefine_line|#define LANMB_64                        3
DECL|macro|MACCM_AUTOMATIC
mdefine_line|#define MACCM_AUTOMATIC                 0
DECL|macro|MACCM_10MB
mdefine_line|#define MACCM_10MB                      1
DECL|macro|MACCM_MII
mdefine_line|#define MACCM_MII                       2
multiline_comment|/* &n; * PHY definitions for Basic registers of QS6612 (used on MIPS ATLAS board) &n; */
DECL|macro|PHY_CONTROL
mdefine_line|#define PHY_CONTROL                     0x0
DECL|macro|PHY_STATUS
mdefine_line|#define PHY_STATUS                      0x1
DECL|macro|PHY_STATUS_LINK_UP
mdefine_line|#define PHY_STATUS_LINK_UP              0x4
DECL|macro|PHY_CONTROL_RESET
mdefine_line|#define PHY_CONTROL_RESET               0x8000
DECL|macro|PHY_CONTROL_AUTO_NEG
mdefine_line|#define PHY_CONTROL_AUTO_NEG            0x1000
DECL|macro|PHY_CONTROL_RESTART_AUTO_NEG
mdefine_line|#define PHY_CONTROL_RESTART_AUTO_NEG    0x0200
DECL|macro|PHY_ADDRESS
mdefine_line|#define PHY_ADDRESS                     0x0
multiline_comment|/* PK_COUNT register. */
DECL|macro|PK_COUNT_TX_A_SHF
mdefine_line|#define PK_COUNT_TX_A_SHF               24
DECL|macro|PK_COUNT_TX_A_MSK
mdefine_line|#define PK_COUNT_TX_A_MSK               (0xff &lt;&lt; PK_COUNT_TX_A_SHF)
DECL|macro|PK_COUNT_TX_B_SHF
mdefine_line|#define PK_COUNT_TX_B_SHF               16
DECL|macro|PK_COUNT_TX_B_MSK
mdefine_line|#define PK_COUNT_TX_B_MSK               (0xff &lt;&lt; PK_COUNT_TX_B_SHF)
DECL|macro|PK_COUNT_RX_A_SHF
mdefine_line|#define PK_COUNT_RX_A_SHF               8
DECL|macro|PK_COUNT_RX_A_MSK
mdefine_line|#define PK_COUNT_RX_A_MSK               (0xff &lt;&lt; PK_COUNT_RX_A_SHF)
DECL|macro|PK_COUNT_RX_B_SHF
mdefine_line|#define PK_COUNT_RX_B_SHF               0
DECL|macro|PK_COUNT_RX_B_MSK
mdefine_line|#define PK_COUNT_RX_B_MSK               (0xff &lt;&lt; PK_COUNT_RX_B_SHF)
multiline_comment|/* OK2USE register. */
DECL|macro|OK2USE_TX_A
mdefine_line|#define OK2USE_TX_A                     0x8
DECL|macro|OK2USE_TX_B
mdefine_line|#define OK2USE_TX_B                     0x4
DECL|macro|OK2USE_RX_A
mdefine_line|#define OK2USE_RX_A                     0x2
DECL|macro|OK2USE_RX_B
mdefine_line|#define OK2USE_RX_B                     0x1
multiline_comment|/* LAN DMA CONTROL register. */
DECL|macro|DMA_CTL_BLK_INT
mdefine_line|#define DMA_CTL_BLK_INT                 0x80000000
DECL|macro|DMA_CTL_MAX_XFER_SHF
mdefine_line|#define DMA_CTL_MAX_XFER_SHF            18
DECL|macro|DMA_CTL_MAX_XFER_MSK
mdefine_line|#define DMA_CTL_MAX_XFER_MSK            (0x3 &lt;&lt; LAN_DMA_CTL_MAX_XFER_SHF)
DECL|macro|DMA_CTL_ENDIAN_SHF
mdefine_line|#define DMA_CTL_ENDIAN_SHF              16
DECL|macro|DMA_CTL_ENDIAN_MSK
mdefine_line|#define DMA_CTL_ENDIAN_MSK              (0x3 &lt;&lt; LAN_DMA_CTL_ENDIAN_SHF)
DECL|macro|DMA_CTL_RX_INT_COUNT_SHF
mdefine_line|#define DMA_CTL_RX_INT_COUNT_SHF        8
DECL|macro|DMA_CTL_RX_INT_COUNT_MSK
mdefine_line|#define DMA_CTL_RX_INT_COUNT_MSK        (0xff &lt;&lt; LAN_DMA_CTL_RX_INT_COUNT_SHF)
DECL|macro|DMA_CTL_EN_TX_DMA
mdefine_line|#define DMA_CTL_EN_TX_DMA               0x00000080
DECL|macro|DMA_CTL_EN_RX_DMA
mdefine_line|#define DMA_CTL_EN_RX_DMA               0x00000040
DECL|macro|DMA_CTL_RX_INT_BUFFUL_EN
mdefine_line|#define DMA_CTL_RX_INT_BUFFUL_EN        0x00000020
DECL|macro|DMA_CTL_RX_INT_TO_EN
mdefine_line|#define DMA_CTL_RX_INT_TO_EN            0x00000010
DECL|macro|DMA_CTL_RX_INT_EN
mdefine_line|#define DMA_CTL_RX_INT_EN               0x00000008
DECL|macro|DMA_CTL_TX_INT_EN
mdefine_line|#define DMA_CTL_TX_INT_EN               0x00000004
DECL|macro|DMA_CTL_MAC_TX_INT_EN
mdefine_line|#define DMA_CTL_MAC_TX_INT_EN           0x00000002
DECL|macro|DMA_CTL_MAC_RX_INT_EN
mdefine_line|#define DMA_CTL_MAC_RX_INT_EN           0x00000001
multiline_comment|/* DMA STATUS register. */
DECL|macro|DMA_STATUS_BAD_ADDR_SHF
mdefine_line|#define DMA_STATUS_BAD_ADDR_SHF         16
DECL|macro|DMA_STATUS_BAD_ADDR_MSK
mdefine_line|#define DMA_STATUS_BAD_ADDR_MSK         (0xf &lt;&lt; DMA_STATUS_BAD_ADDR_SHF)
DECL|macro|DMA_STATUS_RX_PKTS_RECEIVED_SHF
mdefine_line|#define DMA_STATUS_RX_PKTS_RECEIVED_SHF 8
DECL|macro|DMA_STATUS_RX_PKTS_RECEIVED_MSK
mdefine_line|#define DMA_STATUS_RX_PKTS_RECEIVED_MSK (0xff &lt;&lt; DMA_STATUS_RX_PKTS_RECEIVED_SHF)
DECL|macro|DMA_STATUS_TX_EN_SYNC
mdefine_line|#define DMA_STATUS_TX_EN_SYNC           0x00000080
DECL|macro|DMA_STATUS_RX_BUF_A_FUL
mdefine_line|#define DMA_STATUS_RX_BUF_A_FUL         0x00000040
DECL|macro|DMA_STATUS_RX_BUF_B_FUL
mdefine_line|#define DMA_STATUS_RX_BUF_B_FUL         0x00000020
DECL|macro|DMA_STATUS_RX_TO_INT
mdefine_line|#define DMA_STATUS_RX_TO_INT            0x00000010
DECL|macro|DMA_STATUS_RX_INT
mdefine_line|#define DMA_STATUS_RX_INT               0x00000008
DECL|macro|DMA_STATUS_TX_INT
mdefine_line|#define DMA_STATUS_TX_INT               0x00000004
DECL|macro|DMA_STATUS_MAC_TX_INT
mdefine_line|#define DMA_STATUS_MAC_TX_INT           0x00000002
DECL|macro|DMA_STATUS_MAC_RX_INT
mdefine_line|#define DMA_STATUS_MAC_RX_INT           0x00000001
multiline_comment|/* DMA TEST/PANIC SWITHES register. */
DECL|macro|DMA_TEST_LOOPBACK
mdefine_line|#define DMA_TEST_LOOPBACK               0x01000000
DECL|macro|DMA_TEST_SW_RESET
mdefine_line|#define DMA_TEST_SW_RESET               0x00000001
multiline_comment|/* MAC CONTROL register. */
DECL|macro|MAC_CONTROL_EN_MISS_ROLL
mdefine_line|#define MAC_CONTROL_EN_MISS_ROLL        0x00002000
DECL|macro|MAC_CONTROL_MISS_ROLL
mdefine_line|#define MAC_CONTROL_MISS_ROLL           0x00000400
DECL|macro|MAC_CONTROL_LOOP10
mdefine_line|#define MAC_CONTROL_LOOP10              0x00000080
DECL|macro|MAC_CONTROL_CONN_SHF
mdefine_line|#define MAC_CONTROL_CONN_SHF            5
DECL|macro|MAC_CONTROL_CONN_MSK
mdefine_line|#define MAC_CONTROL_CONN_MSK            (0x3 &lt;&lt; MAC_CONTROL_CONN_SHF)
DECL|macro|MAC_CONTROL_MAC_LOOP
mdefine_line|#define MAC_CONTROL_MAC_LOOP            0x00000010
DECL|macro|MAC_CONTROL_FULL_DUP
mdefine_line|#define MAC_CONTROL_FULL_DUP            0x00000008
DECL|macro|MAC_CONTROL_RESET
mdefine_line|#define MAC_CONTROL_RESET               0x00000004
DECL|macro|MAC_CONTROL_HALT_IMM
mdefine_line|#define MAC_CONTROL_HALT_IMM            0x00000002
DECL|macro|MAC_CONTROL_HALT_REQ
mdefine_line|#define MAC_CONTROL_HALT_REQ            0x00000001
multiline_comment|/* CAM CONTROL register. */
DECL|macro|CAM_CONTROL_COMP_EN
mdefine_line|#define CAM_CONTROL_COMP_EN             0x00000010
DECL|macro|CAM_CONTROL_NEG_CAM
mdefine_line|#define CAM_CONTROL_NEG_CAM             0x00000008
DECL|macro|CAM_CONTROL_BROAD_ACC
mdefine_line|#define CAM_CONTROL_BROAD_ACC           0x00000004
DECL|macro|CAM_CONTROL_GROUP_ACC
mdefine_line|#define CAM_CONTROL_GROUP_ACC           0x00000002
DECL|macro|CAM_CONTROL_STATION_ACC
mdefine_line|#define CAM_CONTROL_STATION_ACC         0x00000001
multiline_comment|/* TRANSMIT CONTROL register. */
DECL|macro|TX_CTL_EN_COMP
mdefine_line|#define TX_CTL_EN_COMP                  0x00004000
DECL|macro|TX_CTL_EN_TX_PAR
mdefine_line|#define TX_CTL_EN_TX_PAR                0x00002000
DECL|macro|TX_CTL_EN_LATE_COLL
mdefine_line|#define TX_CTL_EN_LATE_COLL             0x00001000
DECL|macro|TX_CTL_EN_EX_COLL
mdefine_line|#define TX_CTL_EN_EX_COLL               0x00000800
DECL|macro|TX_CTL_EN_L_CARR
mdefine_line|#define TX_CTL_EN_L_CARR                0x00000400
DECL|macro|TX_CTL_EN_EX_DEFER
mdefine_line|#define TX_CTL_EN_EX_DEFER              0x00000200
DECL|macro|TX_CTL_EN_UNDER
mdefine_line|#define TX_CTL_EN_UNDER                 0x00000100
DECL|macro|TX_CTL_MII10
mdefine_line|#define TX_CTL_MII10                    0x00000080
DECL|macro|TX_CTL_SD_PAUSE
mdefine_line|#define TX_CTL_SD_PAUSE                 0x00000040
DECL|macro|TX_CTL_NO_EX_DEF0
mdefine_line|#define TX_CTL_NO_EX_DEF0               0x00000020
DECL|macro|TX_CTL_F_BACK
mdefine_line|#define TX_CTL_F_BACK                   0x00000010
DECL|macro|TX_CTL_NO_CRC
mdefine_line|#define TX_CTL_NO_CRC                   0x00000008
DECL|macro|TX_CTL_NO_PAD
mdefine_line|#define TX_CTL_NO_PAD                   0x00000004
DECL|macro|TX_CTL_TX_HALT
mdefine_line|#define TX_CTL_TX_HALT                  0x00000002
DECL|macro|TX_CTL_TX_EN
mdefine_line|#define TX_CTL_TX_EN                    0x00000001
multiline_comment|/* TRANSMIT STATUS register. */
DECL|macro|TX_STATUS_SQ_ERR
mdefine_line|#define TX_STATUS_SQ_ERR                0x00010000
DECL|macro|TX_STATUS_TX_HALTED
mdefine_line|#define TX_STATUS_TX_HALTED             0x00008000
DECL|macro|TX_STATUS_COMP
mdefine_line|#define TX_STATUS_COMP                  0x00004000
DECL|macro|TX_STATUS_TX_PAR
mdefine_line|#define TX_STATUS_TX_PAR                0x00002000
DECL|macro|TX_STATUS_LATE_COLL
mdefine_line|#define TX_STATUS_LATE_COLL             0x00001000
DECL|macro|TX_STATUS_TX10_STAT
mdefine_line|#define TX_STATUS_TX10_STAT             0x00000800
DECL|macro|TX_STATUS_L_CARR
mdefine_line|#define TX_STATUS_L_CARR                0x00000400
DECL|macro|TX_STATUS_EX_DEFER
mdefine_line|#define TX_STATUS_EX_DEFER              0x00000200
DECL|macro|TX_STATUS_UNDER
mdefine_line|#define TX_STATUS_UNDER                 0x00000100
DECL|macro|TX_STATUS_IN_TX
mdefine_line|#define TX_STATUS_IN_TX                 0x00000080
DECL|macro|TX_STATUS_PAUSED
mdefine_line|#define TX_STATUS_PAUSED                0x00000040
DECL|macro|TX_STATUS_TX_DEFERRED
mdefine_line|#define TX_STATUS_TX_DEFERRED           0x00000020
DECL|macro|TX_STATUS_EX_COLL
mdefine_line|#define TX_STATUS_EX_COLL               0x00000010
DECL|macro|TX_STATUS_TX_COLL_SHF
mdefine_line|#define TX_STATUS_TX_COLL_SHF           0
DECL|macro|TX_STATUS_TX_COLL_MSK
mdefine_line|#define TX_STATUS_TX_COLL_MSK           (0xf &lt;&lt; TX_STATUS_TX_COLL_SHF)
multiline_comment|/* RECEIVE CONTROL register. */
DECL|macro|RX_CTL_EN_GOOD
mdefine_line|#define RX_CTL_EN_GOOD                  0x00004000
DECL|macro|RX_CTL_EN_RX_PAR
mdefine_line|#define RX_CTL_EN_RX_PAR                0x00002000
DECL|macro|RX_CTL_EN_LONG_ERR
mdefine_line|#define RX_CTL_EN_LONG_ERR              0x00000800
DECL|macro|RX_CTL_EN_OVER
mdefine_line|#define RX_CTL_EN_OVER                  0x00000400
DECL|macro|RX_CTL_EN_CRC_ERR
mdefine_line|#define RX_CTL_EN_CRC_ERR               0x00000200
DECL|macro|RX_CTL_EN_ALIGN
mdefine_line|#define RX_CTL_EN_ALIGN                 0x00000100
DECL|macro|RX_CTL_IGNORE_CRC
mdefine_line|#define RX_CTL_IGNORE_CRC               0x00000040
DECL|macro|RX_CTL_PASS_CTL
mdefine_line|#define RX_CTL_PASS_CTL                 0x00000020
DECL|macro|RX_CTL_STRIP_CRC
mdefine_line|#define RX_CTL_STRIP_CRC                0x00000010
DECL|macro|RX_CTL_SHORT_EN
mdefine_line|#define RX_CTL_SHORT_EN                 0x00000008
DECL|macro|RX_CTL_LONG_EN
mdefine_line|#define RX_CTL_LONG_EN                  0x00000004
DECL|macro|RX_CTL_RX_HALT
mdefine_line|#define RX_CTL_RX_HALT                  0x00000002
DECL|macro|RX_CTL_RX_EN
mdefine_line|#define RX_CTL_RX_EN                    0x00000001
multiline_comment|/* RECEIVE STATUS register. */
DECL|macro|RX_STATUS_RX_HALTED
mdefine_line|#define RX_STATUS_RX_HALTED             0x00008000
DECL|macro|RX_STATUS_GOOD
mdefine_line|#define RX_STATUS_GOOD                  0x00004000
DECL|macro|RX_STATUS_RX_PAR
mdefine_line|#define RX_STATUS_RX_PAR                0x00002000
DECL|macro|RX_STATUS_LONG_ERR
mdefine_line|#define RX_STATUS_LONG_ERR              0x00000800
DECL|macro|RX_STATUS_OVERFLOW
mdefine_line|#define RX_STATUS_OVERFLOW              0x00000400
DECL|macro|RX_STATUS_CRC_ERR
mdefine_line|#define RX_STATUS_CRC_ERR               0x00000200
DECL|macro|RX_STATUS_ALIGN_ERR
mdefine_line|#define RX_STATUS_ALIGN_ERR             0x00000100
DECL|macro|RX_STATUS_RX10_STAT
mdefine_line|#define RX_STATUS_RX10_STAT             0x00000080
DECL|macro|RX_STATUS_INT_RX
mdefine_line|#define RX_STATUS_INT_RX                0x00000040
DECL|macro|RX_STATUS_CTL_RECD
mdefine_line|#define RX_STATUS_CTL_RECD              0x00000020
multiline_comment|/* MD_CA register. */
DECL|macro|MD_CA_PRE_SUP
mdefine_line|#define MD_CA_PRE_SUP                   0x00001000
DECL|macro|MD_CA_BUSY
mdefine_line|#define MD_CA_BUSY                      0x00000800
DECL|macro|MD_CA_WR
mdefine_line|#define MD_CA_WR                        0x00000400
DECL|macro|MD_CA_PHY_SHF
mdefine_line|#define MD_CA_PHY_SHF                   5
DECL|macro|MD_CA_PHY_MSK
mdefine_line|#define MD_CA_PHY_MSK                   (0x1f &lt;&lt; MD_CA_PHY_SHF)
DECL|macro|MD_CA_ADDR_SHF
mdefine_line|#define MD_CA_ADDR_SHF                  0
DECL|macro|MD_CA_ADDR_MSK
mdefine_line|#define MD_CA_ADDR_MSK                  (0x1f &lt;&lt; MD_CA_ADDR_SHF)
multiline_comment|/* Tx Status/Control. */
DECL|macro|TX_STAT_CTL_OWNER_SHF
mdefine_line|#define TX_STAT_CTL_OWNER_SHF           30
DECL|macro|TX_STAT_CTL_OWNER_MSK
mdefine_line|#define TX_STAT_CTL_OWNER_MSK           (0x3 &lt;&lt; TX_STAT_CTL_OWNER_SHF)
DECL|macro|TX_STAT_CTL_FRAME_SHF
mdefine_line|#define TX_STAT_CTL_FRAME_SHF           27
DECL|macro|TX_STAT_CTL_FRAME_MSK
mdefine_line|#define TX_STAT_CTL_FRAME_MSK           (0x7 &lt;&lt; TX_STAT_CTL_FRAME_SHF)
DECL|macro|TX_STAT_CTL_STATUS_SHF
mdefine_line|#define TX_STAT_CTL_STATUS_SHF          11
DECL|macro|TX_STAT_CTL_STATUS_MSK
mdefine_line|#define TX_STAT_CTL_STATUS_MSK          (0x1ffff &lt;&lt; TX_STAT_CTL_STATUS_SHF)
DECL|macro|TX_STAT_CTL_LENGTH_SHF
mdefine_line|#define TX_STAT_CTL_LENGTH_SHF          0
DECL|macro|TX_STAT_CTL_LENGTH_MSK
mdefine_line|#define TX_STAT_CTL_LENGTH_MSK          (0x7ff &lt;&lt; TX_STAT_CTL_LENGTH_SHF)
DECL|macro|TX_STAT_CTL_ERROR_MSK
mdefine_line|#define TX_STAT_CTL_ERROR_MSK           ((TX_STATUS_SQ_ERR      |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_TX_HALTED   |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_TX_PAR      |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_LATE_COLL   |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_L_CARR      |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_EX_DEFER    |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_UNDER       |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_PAUSED      |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_TX_DEFERRED |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_EX_COLL     |     &bslash;&n;&t;&t;&t;&t;&t;  TX_STATUS_TX_COLL_MSK)      &bslash;&n;                                                    &lt;&lt; TX_STAT_CTL_STATUS_SHF)
DECL|macro|TX_STAT_CTL_INT_AFTER_TX
mdefine_line|#define TX_STAT_CTL_INT_AFTER_TX        0x4
multiline_comment|/* Rx Status/Control. */
DECL|macro|RX_STAT_CTL_OWNER_SHF
mdefine_line|#define RX_STAT_CTL_OWNER_SHF           30
DECL|macro|RX_STAT_CTL_OWNER_MSK
mdefine_line|#define RX_STAT_CTL_OWNER_MSK           (0x3 &lt;&lt; RX_STAT_CTL_OWNER_SHF)
DECL|macro|RX_STAT_CTL_STATUS_SHF
mdefine_line|#define RX_STAT_CTL_STATUS_SHF          11
DECL|macro|RX_STAT_CTL_STATUS_MSK
mdefine_line|#define RX_STAT_CTL_STATUS_MSK          (0xffff &lt;&lt; RX_STAT_CTL_STATUS_SHF)
DECL|macro|RX_STAT_CTL_LENGTH_SHF
mdefine_line|#define RX_STAT_CTL_LENGTH_SHF          0
DECL|macro|RX_STAT_CTL_LENGTH_MSK
mdefine_line|#define RX_STAT_CTL_LENGTH_MSK          (0x7ff &lt;&lt; RX_STAT_CTL_LENGTH_SHF)
multiline_comment|/* The SAA9730 (LAN) controller register map, as seen via the PCI-bus. */
DECL|macro|SAA9730_LAN_REGS_ADDR
mdefine_line|#define SAA9730_LAN_REGS_ADDR   0x20400
DECL|struct|lan_saa9730_regmap
r_struct
id|lan_saa9730_regmap
(brace
DECL|member|TxBuffA
r_volatile
r_int
r_int
id|TxBuffA
suffix:semicolon
multiline_comment|/* 0x20400 */
DECL|member|TxBuffB
r_volatile
r_int
r_int
id|TxBuffB
suffix:semicolon
multiline_comment|/* 0x20404 */
DECL|member|RxBuffA
r_volatile
r_int
r_int
id|RxBuffA
suffix:semicolon
multiline_comment|/* 0x20408 */
DECL|member|RxBuffB
r_volatile
r_int
r_int
id|RxBuffB
suffix:semicolon
multiline_comment|/* 0x2040c */
DECL|member|PacketCount
r_volatile
r_int
r_int
id|PacketCount
suffix:semicolon
multiline_comment|/* 0x20410 */
DECL|member|Ok2Use
r_volatile
r_int
r_int
id|Ok2Use
suffix:semicolon
multiline_comment|/* 0x20414 */
DECL|member|LanDmaCtl
r_volatile
r_int
r_int
id|LanDmaCtl
suffix:semicolon
multiline_comment|/* 0x20418 */
DECL|member|Timeout
r_volatile
r_int
r_int
id|Timeout
suffix:semicolon
multiline_comment|/* 0x2041c */
DECL|member|DmaStatus
r_volatile
r_int
r_int
id|DmaStatus
suffix:semicolon
multiline_comment|/* 0x20420 */
DECL|member|DmaTest
r_volatile
r_int
r_int
id|DmaTest
suffix:semicolon
multiline_comment|/* 0x20424 */
DECL|member|filler20428
r_volatile
r_int
r_char
id|filler20428
(braket
l_int|0x20430
op_minus
l_int|0x20428
)braket
suffix:semicolon
DECL|member|PauseCount
r_volatile
r_int
r_int
id|PauseCount
suffix:semicolon
multiline_comment|/* 0x20430 */
DECL|member|RemotePauseCount
r_volatile
r_int
r_int
id|RemotePauseCount
suffix:semicolon
multiline_comment|/* 0x20434 */
DECL|member|filler20438
r_volatile
r_int
r_char
id|filler20438
(braket
l_int|0x20440
op_minus
l_int|0x20438
)braket
suffix:semicolon
DECL|member|MacCtl
r_volatile
r_int
r_int
id|MacCtl
suffix:semicolon
multiline_comment|/* 0x20440 */
DECL|member|CamCtl
r_volatile
r_int
r_int
id|CamCtl
suffix:semicolon
multiline_comment|/* 0x20444 */
DECL|member|TxCtl
r_volatile
r_int
r_int
id|TxCtl
suffix:semicolon
multiline_comment|/* 0x20448 */
DECL|member|TxStatus
r_volatile
r_int
r_int
id|TxStatus
suffix:semicolon
multiline_comment|/* 0x2044c */
DECL|member|RxCtl
r_volatile
r_int
r_int
id|RxCtl
suffix:semicolon
multiline_comment|/* 0x20450 */
DECL|member|RxStatus
r_volatile
r_int
r_int
id|RxStatus
suffix:semicolon
multiline_comment|/* 0x20454 */
DECL|member|StationMgmtData
r_volatile
r_int
r_int
id|StationMgmtData
suffix:semicolon
multiline_comment|/* 0x20458 */
DECL|member|StationMgmtCtl
r_volatile
r_int
r_int
id|StationMgmtCtl
suffix:semicolon
multiline_comment|/* 0x2045c */
DECL|member|CamAddress
r_volatile
r_int
r_int
id|CamAddress
suffix:semicolon
multiline_comment|/* 0x20460 */
DECL|member|CamData
r_volatile
r_int
r_int
id|CamData
suffix:semicolon
multiline_comment|/* 0x20464 */
DECL|member|CamEnable
r_volatile
r_int
r_int
id|CamEnable
suffix:semicolon
multiline_comment|/* 0x20468 */
DECL|member|filler2046c
r_volatile
r_int
r_char
id|filler2046c
(braket
l_int|0x20500
op_minus
l_int|0x2046c
)braket
suffix:semicolon
DECL|member|DebugPCIMasterAddr
r_volatile
r_int
r_int
id|DebugPCIMasterAddr
suffix:semicolon
multiline_comment|/* 0x20500 */
DECL|member|DebugLanTxStateMachine
r_volatile
r_int
r_int
id|DebugLanTxStateMachine
suffix:semicolon
multiline_comment|/* 0x20504 */
DECL|member|DebugLanRxStateMachine
r_volatile
r_int
r_int
id|DebugLanRxStateMachine
suffix:semicolon
multiline_comment|/* 0x20508 */
DECL|member|DebugLanTxFifoPointers
r_volatile
r_int
r_int
id|DebugLanTxFifoPointers
suffix:semicolon
multiline_comment|/* 0x2050c */
DECL|member|DebugLanRxFifoPointers
r_volatile
r_int
r_int
id|DebugLanRxFifoPointers
suffix:semicolon
multiline_comment|/* 0x20510 */
DECL|member|DebugLanCtlStateMachine
r_volatile
r_int
r_int
id|DebugLanCtlStateMachine
suffix:semicolon
multiline_comment|/* 0x20514 */
)brace
suffix:semicolon
DECL|typedef|t_lan_saa9730_regmap
r_typedef
r_volatile
r_struct
id|lan_saa9730_regmap
id|t_lan_saa9730_regmap
suffix:semicolon
multiline_comment|/* EVM interrupt control registers. */
DECL|macro|EVM_LAN_INT
mdefine_line|#define EVM_LAN_INT                     0x00010000
DECL|macro|EVM_MASTER_EN
mdefine_line|#define EVM_MASTER_EN                   0x00000001
multiline_comment|/* The SAA9730 (EVM) controller register map, as seen via the PCI-bus. */
DECL|macro|SAA9730_EVM_REGS_ADDR
mdefine_line|#define SAA9730_EVM_REGS_ADDR   0x02000
DECL|struct|evm_saa9730_regmap
r_struct
id|evm_saa9730_regmap
(brace
DECL|member|InterruptStatus1
r_volatile
r_int
r_int
id|InterruptStatus1
suffix:semicolon
multiline_comment|/* 0x2000 */
DECL|member|InterruptEnable1
r_volatile
r_int
r_int
id|InterruptEnable1
suffix:semicolon
multiline_comment|/* 0x2004 */
DECL|member|InterruptMonitor1
r_volatile
r_int
r_int
id|InterruptMonitor1
suffix:semicolon
multiline_comment|/* 0x2008 */
DECL|member|Counter
r_volatile
r_int
r_int
id|Counter
suffix:semicolon
multiline_comment|/* 0x200c */
DECL|member|CounterThreshold
r_volatile
r_int
r_int
id|CounterThreshold
suffix:semicolon
multiline_comment|/* 0x2010 */
DECL|member|CounterControl
r_volatile
r_int
r_int
id|CounterControl
suffix:semicolon
multiline_comment|/* 0x2014 */
DECL|member|GpioControl1
r_volatile
r_int
r_int
id|GpioControl1
suffix:semicolon
multiline_comment|/* 0x2018 */
DECL|member|InterruptStatus2
r_volatile
r_int
r_int
id|InterruptStatus2
suffix:semicolon
multiline_comment|/* 0x201c */
DECL|member|InterruptEnable2
r_volatile
r_int
r_int
id|InterruptEnable2
suffix:semicolon
multiline_comment|/* 0x2020 */
DECL|member|InterruptMonitor2
r_volatile
r_int
r_int
id|InterruptMonitor2
suffix:semicolon
multiline_comment|/* 0x2024 */
DECL|member|GpioControl2
r_volatile
r_int
r_int
id|GpioControl2
suffix:semicolon
multiline_comment|/* 0x2028 */
DECL|member|InterruptBlock1
r_volatile
r_int
r_int
id|InterruptBlock1
suffix:semicolon
multiline_comment|/* 0x202c */
DECL|member|InterruptBlock2
r_volatile
r_int
r_int
id|InterruptBlock2
suffix:semicolon
multiline_comment|/* 0x2030 */
)brace
suffix:semicolon
DECL|typedef|t_evm_saa9730_regmap
r_typedef
r_volatile
r_struct
id|evm_saa9730_regmap
id|t_evm_saa9730_regmap
suffix:semicolon
DECL|struct|lan_saa9730_private
r_struct
id|lan_saa9730_private
(brace
multiline_comment|/* Pointer for the SAA9730 LAN controller register set. */
DECL|member|lan_saa9730_regs
id|t_lan_saa9730_regmap
op_star
id|lan_saa9730_regs
suffix:semicolon
multiline_comment|/* Pointer to the SAA9730 EVM register. */
DECL|member|evm_saa9730_regs
id|t_evm_saa9730_regmap
op_star
id|evm_saa9730_regs
suffix:semicolon
multiline_comment|/* TRUE if the next buffer to write is RxBuffA,  FALSE if RxBuffB. */
DECL|member|NextRcvToUseIsA
r_int
r_char
id|NextRcvToUseIsA
suffix:semicolon
multiline_comment|/* Rcv buffer Index. */
DECL|member|NextRcvPacketIndex
r_int
r_char
id|NextRcvPacketIndex
suffix:semicolon
multiline_comment|/* Index of next packet to use in that buffer. */
DECL|member|NextTxmPacketIndex
r_int
r_char
id|NextTxmPacketIndex
suffix:semicolon
multiline_comment|/* Next buffer index. */
DECL|member|NextTxmBufferIndex
r_int
r_char
id|NextTxmBufferIndex
suffix:semicolon
multiline_comment|/* Index of first pending packet ready to send. */
DECL|member|PendingTxmPacketIndex
r_int
r_char
id|PendingTxmPacketIndex
suffix:semicolon
multiline_comment|/* Pending buffer index. */
DECL|member|PendingTxmBufferIndex
r_int
r_char
id|PendingTxmBufferIndex
suffix:semicolon
DECL|member|DmaRcvPackets
r_int
r_char
id|DmaRcvPackets
suffix:semicolon
DECL|member|DmaTxmPackets
r_int
r_char
id|DmaTxmPackets
suffix:semicolon
DECL|member|RcvAIndex
r_int
r_char
id|RcvAIndex
suffix:semicolon
multiline_comment|/* index into RcvBufferSpace[] for Blk A */
DECL|member|RcvBIndex
r_int
r_char
id|RcvBIndex
suffix:semicolon
multiline_comment|/* index into RcvBufferSpace[] for Blk B */
r_int
r_int
DECL|member|TxmBuffer
id|TxmBuffer
(braket
id|LAN_SAA9730_BUFFERS
)braket
(braket
id|LAN_SAA9730_TXM_Q_SIZE
)braket
suffix:semicolon
r_int
r_int
DECL|member|RcvBuffer
id|RcvBuffer
(braket
id|LAN_SAA9730_BUFFERS
)braket
(braket
id|LAN_SAA9730_RCV_Q_SIZE
)braket
suffix:semicolon
DECL|member|TxBufferFree
r_int
r_int
id|TxBufferFree
(braket
id|LAN_SAA9730_BUFFERS
)braket
suffix:semicolon
DECL|member|PhysicalAddress
r_int
r_char
id|PhysicalAddress
(braket
id|LAN_SAA9730_CAM_ENTRIES
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _SAA9730_H */
eof
