macro_line|#ifndef RAYLINK_H
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
multiline_comment|/****** IEEE 802.11 constants ************************************************/
DECL|macro|ADDRLEN
mdefine_line|#define ADDRLEN           6
multiline_comment|/* Frame control 1 bit fields */
DECL|macro|PROTOCOL_VER
mdefine_line|#define PROTOCOL_VER      0x00
DECL|macro|DATA_TYPE
mdefine_line|#define DATA_TYPE         0x08
DECL|macro|ASSOC_REQ_TYPE
mdefine_line|#define ASSOC_REQ_TYPE    0x00
DECL|macro|ASSOC_RESP_TYPE
mdefine_line|#define ASSOC_RESP_TYPE   0x10
DECL|macro|REASSOC_REQ_TYPE
mdefine_line|#define REASSOC_REQ_TYPE  0x20
DECL|macro|REASSOC_RESP_TYPE
mdefine_line|#define REASSOC_RESP_TYPE 0x30
DECL|macro|NULL_MSG_TYPE
mdefine_line|#define NULL_MSG_TYPE     0x48
DECL|macro|BEACON_TYPE
mdefine_line|#define BEACON_TYPE       0x80
DECL|macro|DISASSOC_TYPE
mdefine_line|#define DISASSOC_TYPE     0xA0
DECL|macro|PSPOLL_TYPE
mdefine_line|#define PSPOLL_TYPE       0xA4
DECL|macro|AUTHENTIC_TYPE
mdefine_line|#define AUTHENTIC_TYPE    0xB0
DECL|macro|DEAUTHENTIC_TYPE
mdefine_line|#define DEAUTHENTIC_TYPE  0xC0
multiline_comment|/* Frame control 2 bit fields */
DECL|macro|FC2_TO_DS
mdefine_line|#define FC2_TO_DS         0x01
DECL|macro|FC2_FROM_DS
mdefine_line|#define FC2_FROM_DS       0x02
DECL|macro|FC2_MORE_FRAG
mdefine_line|#define FC2_MORE_FRAG     0x04
DECL|macro|FC2_RETRY
mdefine_line|#define FC2_RETRY         0x08
DECL|macro|FC2_PSM
mdefine_line|#define FC2_PSM           0x10
DECL|macro|FC2_MORE_DATA
mdefine_line|#define FC2_MORE_DATA     0x20
DECL|macro|FC2_WEP
mdefine_line|#define FC2_WEP           0x40
DECL|macro|FC2_ORDER
mdefine_line|#define FC2_ORDER         0x80
multiline_comment|/*****************************************************************************/
multiline_comment|/* 802.11 element ID&squot;s and lengths */
DECL|macro|C_BP_CAPABILITY_ESS
mdefine_line|#define C_BP_CAPABILITY_ESS             0x01
DECL|macro|C_BP_CAPABILITY_IBSS
mdefine_line|#define C_BP_CAPABILITY_IBSS            0x02
DECL|macro|C_BP_CAPABILITY_CF_POLLABLE
mdefine_line|#define C_BP_CAPABILITY_CF_POLLABLE     0x04
DECL|macro|C_BP_CAPABILITY_CF_POLL_REQUEST
mdefine_line|#define C_BP_CAPABILITY_CF_POLL_REQUEST 0x08
DECL|macro|C_BP_CAPABILITY_PRIVACY
mdefine_line|#define C_BP_CAPABILITY_PRIVACY         0x10
DECL|macro|C_ESSID_ELEMENT_ID
mdefine_line|#define C_ESSID_ELEMENT_ID               0
DECL|macro|C_ESSID_ELEMENT_MAX_LENGTH
mdefine_line|#define C_ESSID_ELEMENT_MAX_LENGTH       32
DECL|macro|C_SUPPORTED_RATES_ELEMENT_ID
mdefine_line|#define C_SUPPORTED_RATES_ELEMENT_ID     1
DECL|macro|C_SUPPORTED_RATES_ELEMENT_LENGTH
mdefine_line|#define C_SUPPORTED_RATES_ELEMENT_LENGTH 2
DECL|macro|C_FH_PARAM_SET_ELEMENT_ID
mdefine_line|#define C_FH_PARAM_SET_ELEMENT_ID        2
DECL|macro|C_FH_PARAM_SET_ELEMENT_LNGTH
mdefine_line|#define C_FH_PARAM_SET_ELEMENT_LNGTH     5
DECL|macro|C_CF_PARAM_SET_ELEMENT_ID
mdefine_line|#define C_CF_PARAM_SET_ELEMENT_ID        4
DECL|macro|C_CF_PARAM_SET_ELEMENT_LNGTH
mdefine_line|#define C_CF_PARAM_SET_ELEMENT_LNGTH     6
DECL|macro|C_TIM_ELEMENT_ID
mdefine_line|#define C_TIM_ELEMENT_ID                 5
DECL|macro|C_TIM_BITMAP_LENGTH
mdefine_line|#define C_TIM_BITMAP_LENGTH            251
DECL|macro|C_TIM_BMCAST_BIT
mdefine_line|#define C_TIM_BMCAST_BIT              0x01
DECL|macro|C_IBSS_ELEMENT_ID
mdefine_line|#define C_IBSS_ELEMENT_ID                6
DECL|macro|C_IBSS_ELEMENT_LENGTH
mdefine_line|#define C_IBSS_ELEMENT_LENGTH            2
DECL|macro|C_JAPAN_CALL_SIGN_ELEMENT_ID
mdefine_line|#define C_JAPAN_CALL_SIGN_ELEMENT_ID    51
DECL|macro|C_JAPAN_CALL_SIGN_ELEMENT_LNGTH
mdefine_line|#define C_JAPAN_CALL_SIGN_ELEMENT_LNGTH 12
DECL|macro|C_DISASSOC_REASON_CODE_LEN
mdefine_line|#define C_DISASSOC_REASON_CODE_LEN       2
DECL|macro|C_DISASSOC_REASON_CODE_DEFAULT
mdefine_line|#define C_DISASSOC_REASON_CODE_DEFAULT   8
DECL|macro|C_CRC_LEN
mdefine_line|#define C_CRC_LEN                        4
DECL|macro|C_NUM_SUPPORTED_RATES
mdefine_line|#define C_NUM_SUPPORTED_RATES            8 
multiline_comment|/****** IEEE 802.11 mac header for type data packets *************************/
DECL|struct|mac_header
r_struct
id|mac_header
(brace
DECL|member|frame_ctl_1
id|UCHAR
id|frame_ctl_1
suffix:semicolon
DECL|member|frame_ctl_2
id|UCHAR
id|frame_ctl_2
suffix:semicolon
DECL|member|duration_lsb
id|UCHAR
id|duration_lsb
suffix:semicolon
DECL|member|duration_msb
id|UCHAR
id|duration_msb
suffix:semicolon
DECL|member|addr_1
id|UCHAR
id|addr_1
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|addr_2
id|UCHAR
id|addr_2
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|addr_3
id|UCHAR
id|addr_3
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|seq_frag_num
id|UCHAR
id|seq_frag_num
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*  UCHAR addr_4[ADDRLEN]; */
multiline_comment|/* only present for AP to AP (TO DS and FROM DS */
)brace
suffix:semicolon
multiline_comment|/****** IEEE 802.11 frame element structures *********************************/
DECL|struct|essid_element
r_struct
id|essid_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|text
id|UCHAR
id|text
(braket
id|C_ESSID_ELEMENT_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rates_element
r_struct
id|rates_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|value
id|UCHAR
id|value
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|freq_hop_element
r_struct
id|freq_hop_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|dwell_time
id|UCHAR
id|dwell_time
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hop_set
id|UCHAR
id|hop_set
suffix:semicolon
DECL|member|hop_pattern
id|UCHAR
id|hop_pattern
suffix:semicolon
DECL|member|hop_index
id|UCHAR
id|hop_index
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tim_element
r_struct
id|tim_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|dtim_count
id|UCHAR
id|dtim_count
suffix:semicolon
DECL|member|dtim_period
id|UCHAR
id|dtim_period
suffix:semicolon
DECL|member|bitmap_control
id|UCHAR
id|bitmap_control
suffix:semicolon
DECL|member|tim
id|UCHAR
id|tim
(braket
id|C_TIM_BITMAP_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibss_element
r_struct
id|ibss_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|atim_window
id|UCHAR
id|atim_window
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|japan_call_sign_element
r_struct
id|japan_call_sign_element
(brace
DECL|member|id
id|UCHAR
id|id
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
DECL|member|call_sign
id|UCHAR
id|call_sign
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****** Beacon message structures ********************************************/
multiline_comment|/* .elements is a large lump of max size because elements are variable size  */
DECL|struct|infra_beacon
r_struct
id|infra_beacon
(brace
DECL|member|timestamp
id|UCHAR
id|timestamp
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|beacon_intvl
id|UCHAR
id|beacon_intvl
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|capability
id|UCHAR
id|capability
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|elements
id|UCHAR
id|elements
(braket
r_sizeof
(paren
r_struct
id|essid_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|rates_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|freq_hop_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|japan_call_sign_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|tim_element
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|adhoc_beacon
r_struct
id|adhoc_beacon
(brace
DECL|member|timestamp
id|UCHAR
id|timestamp
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|beacon_intvl
id|UCHAR
id|beacon_intvl
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|capability
id|UCHAR
id|capability
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|elements
id|UCHAR
id|elements
(braket
r_sizeof
(paren
r_struct
id|essid_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|rates_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|freq_hop_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|japan_call_sign_element
)paren
op_plus
r_sizeof
(paren
r_struct
id|ibss_element
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*****************************************************************************/
multiline_comment|/* #define C_MAC_HDR_2_WEP 0x40 */
multiline_comment|/* TX/RX CCS constants */
DECL|macro|TX_HEADER_LENGTH
mdefine_line|#define TX_HEADER_LENGTH 0x1C
DECL|macro|RX_MAC_HEADER_LENGTH
mdefine_line|#define RX_MAC_HEADER_LENGTH 0x18
DECL|macro|TX_AUTHENTICATE_LENGTH
mdefine_line|#define TX_AUTHENTICATE_LENGTH (TX_HEADER_LENGTH + 6)
DECL|macro|TX_AUTHENTICATE_LENGTH_MSB
mdefine_line|#define TX_AUTHENTICATE_LENGTH_MSB (TX_AUTHENTICATE_LENGTH &gt;&gt; 8)
DECL|macro|TX_AUTHENTICATE_LENGTH_LSB
mdefine_line|#define TX_AUTHENTICATE_LENGTH_LSB (TX_AUTHENTICATE_LENGTH &amp; 0xff)
DECL|macro|TX_DEAUTHENTICATE_LENGTH
mdefine_line|#define TX_DEAUTHENTICATE_LENGTH (TX_HEADER_LENGTH + 2)
DECL|macro|TX_DEAUTHENTICATE_LENGTH_MSB
mdefine_line|#define TX_DEAUTHENTICATE_LENGTH_MSB (TX_AUTHENTICATE_LENGTH &gt;&gt; 8)
DECL|macro|TX_DEAUTHENTICATE_LENGTH_LSB
mdefine_line|#define TX_DEAUTHENTICATE_LENGTH_LSB (TX_AUTHENTICATE_LENGTH &amp; 0xff)
DECL|macro|FCS_LEN
mdefine_line|#define FCS_LEN           4
DECL|macro|ADHOC
mdefine_line|#define ADHOC                 0
DECL|macro|INFRA
mdefine_line|#define INFRA                 1
DECL|macro|TYPE_STA
mdefine_line|#define TYPE_STA              0
DECL|macro|TYPE_AP
mdefine_line|#define TYPE_AP               1
DECL|macro|PASSIVE_SCAN
mdefine_line|#define PASSIVE_SCAN          1
DECL|macro|ACTIVE_SCAN
mdefine_line|#define ACTIVE_SCAN           1
DECL|macro|PSM_CAM
mdefine_line|#define PSM_CAM               0
multiline_comment|/* Country codes */
DECL|macro|USA
mdefine_line|#define USA                   1
DECL|macro|EUROPE
mdefine_line|#define EUROPE                2
DECL|macro|JAPAN
mdefine_line|#define JAPAN                 3
DECL|macro|KOREA
mdefine_line|#define KOREA                 4
DECL|macro|SPAIN
mdefine_line|#define SPAIN                 5
DECL|macro|FRANCE
mdefine_line|#define FRANCE                6
DECL|macro|ISRAEL
mdefine_line|#define ISRAEL                7
DECL|macro|AUSTRALIA
mdefine_line|#define AUSTRALIA             8
DECL|macro|JAPAN_TEST
mdefine_line|#define JAPAN_TEST            9
multiline_comment|/* Hop pattern lengths */
DECL|macro|USA_HOP_MOD
mdefine_line|#define USA_HOP_MOD          79 
DECL|macro|EUROPE_HOP_MOD
mdefine_line|#define EUROPE_HOP_MOD       79 
DECL|macro|JAPAN_HOP_MOD
mdefine_line|#define JAPAN_HOP_MOD        23
DECL|macro|KOREA_HOP_MOD
mdefine_line|#define KOREA_HOP_MOD        23
DECL|macro|SPAIN_HOP_MOD
mdefine_line|#define SPAIN_HOP_MOD        27
DECL|macro|FRANCE_HOP_MOD
mdefine_line|#define FRANCE_HOP_MOD       35
DECL|macro|ISRAEL_HOP_MOD
mdefine_line|#define ISRAEL_HOP_MOD       35
DECL|macro|AUSTRALIA_HOP_MOD
mdefine_line|#define AUSTRALIA_HOP_MOD    47
DECL|macro|JAPAN_TEST_HOP_MOD
mdefine_line|#define JAPAN_TEST_HOP_MOD   23
DECL|macro|ESSID_SIZE
mdefine_line|#define ESSID_SIZE           32
multiline_comment|/**********************************************************************/
multiline_comment|/* CIS Register Constants */
DECL|macro|CIS_OFFSET
mdefine_line|#define CIS_OFFSET             0x0f00
multiline_comment|/* Configuration Option Register (0x0F00) */
DECL|macro|COR_OFFSET
mdefine_line|#define COR_OFFSET             0x00
DECL|macro|COR_SOFT_RESET
mdefine_line|#define COR_SOFT_RESET         0x80
DECL|macro|COR_LEVEL_IRQ
mdefine_line|#define COR_LEVEL_IRQ          0x40
DECL|macro|COR_CONFIG_NUM
mdefine_line|#define COR_CONFIG_NUM         0x01
DECL|macro|COR_DEFAULT
mdefine_line|#define COR_DEFAULT            (COR_LEVEL_IRQ | COR_CONFIG_NUM)
multiline_comment|/* Card Configuration and Status Register (0x0F01) */
DECL|macro|CCSR_OFFSET
mdefine_line|#define CCSR_OFFSET            0x01
DECL|macro|CCSR_HOST_INTR_PENDING
mdefine_line|#define CCSR_HOST_INTR_PENDING 0x01
DECL|macro|CCSR_POWER_DOWN
mdefine_line|#define CCSR_POWER_DOWN        0x04
multiline_comment|/* HCS Interrupt Register (0x0F05) */
DECL|macro|HCS_INTR_OFFSET
mdefine_line|#define HCS_INTR_OFFSET        0x05
multiline_comment|/* #define HCS_INTR_OFFSET        0x0A */
DECL|macro|HCS_INTR_CLEAR
mdefine_line|#define HCS_INTR_CLEAR         0x00
multiline_comment|/* ECF Interrupt Register (0x0F06) */
DECL|macro|ECF_INTR_OFFSET
mdefine_line|#define ECF_INTR_OFFSET        0x06
multiline_comment|/* #define ECF_INTR_OFFSET        0x0C */
DECL|macro|ECF_INTR_SET
mdefine_line|#define ECF_INTR_SET           0x01
multiline_comment|/* Authorization Register 0 (0x0F08) */
DECL|macro|AUTH_0_ON
mdefine_line|#define AUTH_0_ON              0x57
multiline_comment|/* Authorization Register 1 (0x0F09) */
DECL|macro|AUTH_1_ON
mdefine_line|#define AUTH_1_ON              0x82
multiline_comment|/* Program Mode Register (0x0F0A) */
DECL|macro|PC2PM
mdefine_line|#define PC2PM                  0x02
DECL|macro|PC2CAL
mdefine_line|#define PC2CAL                 0x10
DECL|macro|PC2MLSE
mdefine_line|#define PC2MLSE                0x20
multiline_comment|/* PC Test Mode Register (0x0F0B) */
DECL|macro|PC_TEST_MODE
mdefine_line|#define PC_TEST_MODE           0x08
multiline_comment|/* Frequency Control Word (0x0F10) */
multiline_comment|/* Range 0x02 - 0xA6 */
multiline_comment|/* Test Mode Control 1-4 (0x0F14 - 0x0F17) */
multiline_comment|/**********************************************************************/
multiline_comment|/* Shared RAM Area */
DECL|macro|SCB_BASE
mdefine_line|#define SCB_BASE               0x0000
DECL|macro|STATUS_BASE
mdefine_line|#define STATUS_BASE            0x0100
DECL|macro|HOST_TO_ECF_BASE
mdefine_line|#define HOST_TO_ECF_BASE       0x0200
DECL|macro|ECF_TO_HOST_BASE
mdefine_line|#define ECF_TO_HOST_BASE       0x0300
DECL|macro|CCS_BASE
mdefine_line|#define CCS_BASE               0x0400
DECL|macro|RCS_BASE
mdefine_line|#define RCS_BASE               0x0800
DECL|macro|INFRA_TIM_BASE
mdefine_line|#define INFRA_TIM_BASE         0x0C00
DECL|macro|SSID_LIST_BASE
mdefine_line|#define SSID_LIST_BASE         0x0D00
DECL|macro|TX_BUF_BASE
mdefine_line|#define TX_BUF_BASE            0x1000
DECL|macro|RX_BUF_BASE
mdefine_line|#define RX_BUF_BASE            0x8000
DECL|macro|NUMBER_OF_CCS
mdefine_line|#define NUMBER_OF_CCS    64
DECL|macro|NUMBER_OF_RCS
mdefine_line|#define NUMBER_OF_RCS    64
multiline_comment|/*#define NUMBER_OF_TX_CCS 14 */
DECL|macro|NUMBER_OF_TX_CCS
mdefine_line|#define NUMBER_OF_TX_CCS 14
DECL|macro|TX_BUF_SIZE
mdefine_line|#define TX_BUF_SIZE      (2048 - sizeof(struct tx_msg))
DECL|macro|RX_BUFF_END
mdefine_line|#define RX_BUFF_END      0x3FFF
multiline_comment|/* Values for buffer_status */
DECL|macro|CCS_BUFFER_FREE
mdefine_line|#define CCS_BUFFER_FREE       0
DECL|macro|CCS_BUFFER_BUSY
mdefine_line|#define CCS_BUFFER_BUSY       1
DECL|macro|CCS_COMMAND_COMPLETE
mdefine_line|#define CCS_COMMAND_COMPLETE  2
DECL|macro|CCS_COMMAND_FAILED
mdefine_line|#define CCS_COMMAND_FAILED    3
multiline_comment|/* Values for cmd */
DECL|macro|CCS_DOWNLOAD_STARTUP_PARAMS
mdefine_line|#define CCS_DOWNLOAD_STARTUP_PARAMS    1
DECL|macro|CCS_UPDATE_PARAMS
mdefine_line|#define CCS_UPDATE_PARAMS              2
DECL|macro|CCS_REPORT_PARAMS
mdefine_line|#define CCS_REPORT_PARAMS              3
DECL|macro|CCS_UPDATE_MULTICAST_LIST
mdefine_line|#define CCS_UPDATE_MULTICAST_LIST      4
DECL|macro|CCS_UPDATE_POWER_SAVINGS_MODE
mdefine_line|#define CCS_UPDATE_POWER_SAVINGS_MODE  5
DECL|macro|CCS_START_NETWORK
mdefine_line|#define CCS_START_NETWORK              6
DECL|macro|CCS_JOIN_NETWORK
mdefine_line|#define CCS_JOIN_NETWORK               7
DECL|macro|CCS_START_ASSOCIATION
mdefine_line|#define CCS_START_ASSOCIATION          8
DECL|macro|CCS_TX_REQUEST
mdefine_line|#define CCS_TX_REQUEST                 9
DECL|macro|CCS_TEST_MEMORY
mdefine_line|#define CCS_TEST_MEMORY              0xa
DECL|macro|CCS_SHUTDOWN
mdefine_line|#define CCS_SHUTDOWN                 0xb
DECL|macro|CCS_DUMP_MEMORY
mdefine_line|#define CCS_DUMP_MEMORY              0xc
DECL|macro|CCS_START_TIMER
mdefine_line|#define CCS_START_TIMER              0xe
DECL|macro|CCS_LAST_CMD
mdefine_line|#define CCS_LAST_CMD                 CCS_START_TIMER
multiline_comment|/* Values for link field */
DECL|macro|CCS_END_LIST
mdefine_line|#define CCS_END_LIST                 0xff
multiline_comment|/* values for buffer_status field */
DECL|macro|RCS_BUFFER_FREE
mdefine_line|#define RCS_BUFFER_FREE       0
DECL|macro|RCS_BUFFER_BUSY
mdefine_line|#define RCS_BUFFER_BUSY       1
DECL|macro|RCS_COMPLETE
mdefine_line|#define RCS_COMPLETE          2
DECL|macro|RCS_FAILED
mdefine_line|#define RCS_FAILED            3
DECL|macro|RCS_BUFFER_RELEASE
mdefine_line|#define RCS_BUFFER_RELEASE    0xFF
multiline_comment|/* values for interrupt_id field */
DECL|macro|PROCESS_RX_PACKET
mdefine_line|#define PROCESS_RX_PACKET           0x80 /* */
DECL|macro|REJOIN_NET_COMPLETE
mdefine_line|#define REJOIN_NET_COMPLETE         0x81 /* RCS ID: Rejoin Net Complete */
DECL|macro|ROAMING_INITIATED
mdefine_line|#define ROAMING_INITIATED           0x82 /* RCS ID: Roaming Initiated   */
DECL|macro|JAPAN_CALL_SIGN_RXD
mdefine_line|#define JAPAN_CALL_SIGN_RXD         0x83 /* RCS ID: New Japan Call Sign */
multiline_comment|/*****************************************************************************/
multiline_comment|/* Memory types for dump memory command */
DECL|macro|C_MEM_PROG
mdefine_line|#define C_MEM_PROG  0
DECL|macro|C_MEM_XDATA
mdefine_line|#define C_MEM_XDATA 1
DECL|macro|C_MEM_SFR
mdefine_line|#define C_MEM_SFR   2
DECL|macro|C_MEM_IDATA
mdefine_line|#define C_MEM_IDATA 3
multiline_comment|/*** Return values for hw_xmit **********/
DECL|macro|XMIT_OK
mdefine_line|#define XMIT_OK        (0)
DECL|macro|XMIT_MSG_BAD
mdefine_line|#define XMIT_MSG_BAD   (-1)
DECL|macro|XMIT_NO_CCS
mdefine_line|#define XMIT_NO_CCS    (-2)
DECL|macro|XMIT_NO_INTR
mdefine_line|#define XMIT_NO_INTR   (-3)
DECL|macro|XMIT_NEED_AUTH
mdefine_line|#define XMIT_NEED_AUTH (-4)
multiline_comment|/*** Values for card status */
DECL|macro|CARD_INSERTED
mdefine_line|#define CARD_INSERTED       (0)
DECL|macro|CARD_AWAITING_PARAM
mdefine_line|#define CARD_AWAITING_PARAM (1)
DECL|macro|CARD_INIT_ERROR
mdefine_line|#define CARD_INIT_ERROR     (11)
DECL|macro|CARD_DL_PARAM
mdefine_line|#define CARD_DL_PARAM       (2)
DECL|macro|CARD_DL_PARAM_ERROR
mdefine_line|#define CARD_DL_PARAM_ERROR (12)
DECL|macro|CARD_DOING_ACQ
mdefine_line|#define CARD_DOING_ACQ      (3)
DECL|macro|CARD_ACQ_COMPLETE
mdefine_line|#define CARD_ACQ_COMPLETE   (4)
DECL|macro|CARD_ACQ_FAILED
mdefine_line|#define CARD_ACQ_FAILED     (14)
DECL|macro|CARD_AUTH_COMPLETE
mdefine_line|#define CARD_AUTH_COMPLETE  (5)
DECL|macro|CARD_AUTH_REFUSED
mdefine_line|#define CARD_AUTH_REFUSED   (15)
DECL|macro|CARD_ASSOC_COMPLETE
mdefine_line|#define CARD_ASSOC_COMPLETE (6)
DECL|macro|CARD_ASSOC_FAILED
mdefine_line|#define CARD_ASSOC_FAILED   (16)
multiline_comment|/*** Values for authentication_state ***********************************/
DECL|macro|UNAUTHENTICATED
mdefine_line|#define UNAUTHENTICATED     (0)
DECL|macro|AWAITING_RESPONSE
mdefine_line|#define AWAITING_RESPONSE   (1)
DECL|macro|AUTHENTICATED
mdefine_line|#define AUTHENTICATED       (2)
DECL|macro|NEED_TO_AUTH
mdefine_line|#define NEED_TO_AUTH        (3)
multiline_comment|/*** Values for authentication type ************************************/
DECL|macro|OPEN_AUTH_REQUEST
mdefine_line|#define OPEN_AUTH_REQUEST   (1)
DECL|macro|OPEN_AUTH_RESPONSE
mdefine_line|#define OPEN_AUTH_RESPONSE  (2)
DECL|macro|BROADCAST_DEAUTH
mdefine_line|#define BROADCAST_DEAUTH    (0xc0)
multiline_comment|/*** Values for timer functions ****************************************/
DECL|macro|TODO_NOTHING
mdefine_line|#define TODO_NOTHING              (0)
DECL|macro|TODO_VERIFY_DL_START
mdefine_line|#define TODO_VERIFY_DL_START      (-1)
DECL|macro|TODO_START_NET
mdefine_line|#define TODO_START_NET            (-2)
DECL|macro|TODO_JOIN_NET
mdefine_line|#define TODO_JOIN_NET             (-3)
DECL|macro|TODO_AUTHENTICATE_TIMEOUT
mdefine_line|#define TODO_AUTHENTICATE_TIMEOUT (-4)
DECL|macro|TODO_SEND_CCS
mdefine_line|#define TODO_SEND_CCS             (-5)
multiline_comment|/***********************************************************************/
multiline_comment|/* Parameter passing structure for update/report parameter CCS&squot;s */
DECL|struct|object_id
r_struct
id|object_id
(brace
DECL|member|object_addr
r_void
op_star
id|object_addr
suffix:semicolon
DECL|member|object_length
r_int
r_char
id|object_length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OBJID_network_type
mdefine_line|#define OBJID_network_type            0
DECL|macro|OBJID_acting_as_ap_status
mdefine_line|#define OBJID_acting_as_ap_status     1
DECL|macro|OBJID_current_ess_id
mdefine_line|#define OBJID_current_ess_id          2
DECL|macro|OBJID_scanning_mode
mdefine_line|#define OBJID_scanning_mode           3
DECL|macro|OBJID_power_mgt_state
mdefine_line|#define OBJID_power_mgt_state         4
DECL|macro|OBJID_mac_address
mdefine_line|#define OBJID_mac_address             5
DECL|macro|OBJID_frag_threshold
mdefine_line|#define OBJID_frag_threshold          6
DECL|macro|OBJID_hop_time
mdefine_line|#define OBJID_hop_time                7
DECL|macro|OBJID_beacon_period
mdefine_line|#define OBJID_beacon_period           8
DECL|macro|OBJID_dtim_period
mdefine_line|#define OBJID_dtim_period             9
DECL|macro|OBJID_retry_max
mdefine_line|#define OBJID_retry_max              10
DECL|macro|OBJID_ack_timeout
mdefine_line|#define OBJID_ack_timeout            11
DECL|macro|OBJID_sifs
mdefine_line|#define OBJID_sifs                   12
DECL|macro|OBJID_difs
mdefine_line|#define OBJID_difs                   13
DECL|macro|OBJID_pifs
mdefine_line|#define OBJID_pifs                   14
DECL|macro|OBJID_rts_threshold
mdefine_line|#define OBJID_rts_threshold          15
DECL|macro|OBJID_scan_dwell_time
mdefine_line|#define OBJID_scan_dwell_time        16
DECL|macro|OBJID_max_scan_dwell_time
mdefine_line|#define OBJID_max_scan_dwell_time    17
DECL|macro|OBJID_assoc_resp_timeout
mdefine_line|#define OBJID_assoc_resp_timeout     18
DECL|macro|OBJID_adhoc_scan_cycle_max
mdefine_line|#define OBJID_adhoc_scan_cycle_max   19
DECL|macro|OBJID_infra_scan_cycle_max
mdefine_line|#define OBJID_infra_scan_cycle_max   20
DECL|macro|OBJID_infra_super_cycle_max
mdefine_line|#define OBJID_infra_super_cycle_max  21
DECL|macro|OBJID_promiscuous_mode
mdefine_line|#define OBJID_promiscuous_mode       22
DECL|macro|OBJID_unique_word
mdefine_line|#define OBJID_unique_word            23
DECL|macro|OBJID_slot_time
mdefine_line|#define OBJID_slot_time              24
DECL|macro|OBJID_roaming_low_snr
mdefine_line|#define OBJID_roaming_low_snr        25
DECL|macro|OBJID_low_snr_count_thresh
mdefine_line|#define OBJID_low_snr_count_thresh   26
DECL|macro|OBJID_infra_missed_bcn
mdefine_line|#define OBJID_infra_missed_bcn       27
DECL|macro|OBJID_adhoc_missed_bcn
mdefine_line|#define OBJID_adhoc_missed_bcn       28
DECL|macro|OBJID_curr_country_code
mdefine_line|#define OBJID_curr_country_code      29
DECL|macro|OBJID_hop_pattern
mdefine_line|#define OBJID_hop_pattern            30
DECL|macro|OBJID_reserved
mdefine_line|#define OBJID_reserved               31
DECL|macro|OBJID_cw_max_msb
mdefine_line|#define OBJID_cw_max_msb             32
DECL|macro|OBJID_cw_min_msb
mdefine_line|#define OBJID_cw_min_msb             33
DECL|macro|OBJID_noise_filter_gain
mdefine_line|#define OBJID_noise_filter_gain      34
DECL|macro|OBJID_noise_limit_offset
mdefine_line|#define OBJID_noise_limit_offset     35
DECL|macro|OBJID_det_rssi_thresh_offset
mdefine_line|#define OBJID_det_rssi_thresh_offset 36
DECL|macro|OBJID_med_busy_thresh_offset
mdefine_line|#define OBJID_med_busy_thresh_offset 37
DECL|macro|OBJID_det_sync_thresh
mdefine_line|#define OBJID_det_sync_thresh        38
DECL|macro|OBJID_test_mode
mdefine_line|#define OBJID_test_mode              39
DECL|macro|OBJID_test_min_chan_num
mdefine_line|#define OBJID_test_min_chan_num      40
DECL|macro|OBJID_test_max_chan_num
mdefine_line|#define OBJID_test_max_chan_num      41
DECL|macro|OBJID_allow_bcast_ID_prbrsp
mdefine_line|#define OBJID_allow_bcast_ID_prbrsp  42
DECL|macro|OBJID_privacy_must_start
mdefine_line|#define OBJID_privacy_must_start     43
DECL|macro|OBJID_privacy_can_join
mdefine_line|#define OBJID_privacy_can_join       44
DECL|macro|OBJID_basic_rate_set
mdefine_line|#define OBJID_basic_rate_set         45
multiline_comment|/**** Configuration/Status/Control Area ***************************/
multiline_comment|/*    System Control Block (SCB) Area&n; *    Located at Shared RAM offset 0&n; */
DECL|struct|scb
r_struct
id|scb
(brace
DECL|member|ccs_index
id|UCHAR
id|ccs_index
suffix:semicolon
DECL|member|rcs_index
id|UCHAR
id|rcs_index
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****** Status area at Shared RAM offset 0x0100 ******************************/
DECL|struct|status
r_struct
id|status
(brace
DECL|member|mrx_overflow_for_host
id|UCHAR
id|mrx_overflow_for_host
suffix:semicolon
multiline_comment|/* 0=ECF may write, 1=host may write*/
DECL|member|mrx_checksum_error_for_host
id|UCHAR
id|mrx_checksum_error_for_host
suffix:semicolon
multiline_comment|/* 0=ECF may write, 1=host may write*/
DECL|member|rx_hec_error_for_host
id|UCHAR
id|rx_hec_error_for_host
suffix:semicolon
multiline_comment|/* 0=ECF may write, 1=host may write*/
DECL|member|reserved1
id|UCHAR
id|reserved1
suffix:semicolon
DECL|member|mrx_overflow
r_int
id|mrx_overflow
suffix:semicolon
multiline_comment|/* ECF increments on rx overflow    */
DECL|member|mrx_checksum_error
r_int
id|mrx_checksum_error
suffix:semicolon
multiline_comment|/* ECF increments on rx CRC error   */
DECL|member|rx_hec_error
r_int
id|rx_hec_error
suffix:semicolon
multiline_comment|/* ECF incs on mac header CRC error */
DECL|member|rxnoise
id|UCHAR
id|rxnoise
suffix:semicolon
multiline_comment|/* Average RSL measurement          */
)brace
suffix:semicolon
multiline_comment|/****** Host-to-ECF Data Area at Shared RAM offset 0x200 *********************/
DECL|struct|host_to_ecf_area
r_struct
id|host_to_ecf_area
(brace
)brace
suffix:semicolon
multiline_comment|/****** ECF-to-Host Data Area at Shared RAM offset 0x0300 ********************/
DECL|struct|startup_res_518
r_struct
id|startup_res_518
(brace
DECL|member|startup_word
id|UCHAR
id|startup_word
suffix:semicolon
DECL|member|station_addr
id|UCHAR
id|station_addr
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|calc_prog_chksum
id|UCHAR
id|calc_prog_chksum
suffix:semicolon
DECL|member|calc_cis_chksum
id|UCHAR
id|calc_cis_chksum
suffix:semicolon
DECL|member|ecf_spare
id|UCHAR
id|ecf_spare
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|japan_call_sign
id|UCHAR
id|japan_call_sign
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|startup_res_6
r_struct
id|startup_res_6
(brace
DECL|member|startup_word
id|UCHAR
id|startup_word
suffix:semicolon
DECL|member|station_addr
id|UCHAR
id|station_addr
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|member|supp_rates
id|UCHAR
id|supp_rates
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|japan_call_sign
id|UCHAR
id|japan_call_sign
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|calc_prog_chksum
id|UCHAR
id|calc_prog_chksum
suffix:semicolon
DECL|member|calc_cis_chksum
id|UCHAR
id|calc_cis_chksum
suffix:semicolon
DECL|member|firmware_version
id|UCHAR
id|firmware_version
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|asic_version
id|UCHAR
id|asic_version
suffix:semicolon
DECL|member|tib_length
id|UCHAR
id|tib_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|start_join_net_params
r_struct
id|start_join_net_params
(brace
DECL|member|net_type
id|UCHAR
id|net_type
suffix:semicolon
DECL|member|ssid
id|UCHAR
id|ssid
(braket
id|ESSID_SIZE
)braket
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|member|privacy_can_join
id|UCHAR
id|privacy_can_join
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****** Command Control Structure area at Shared ram offset 0x0400 ***********/
multiline_comment|/* Structures for command specific parameters (ccs.var) */
DECL|struct|update_param_cmd
r_struct
id|update_param_cmd
(brace
DECL|member|object_id
id|UCHAR
id|object_id
suffix:semicolon
DECL|member|number_objects
id|UCHAR
id|number_objects
suffix:semicolon
DECL|member|failure_cause
id|UCHAR
id|failure_cause
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|report_param_cmd
r_struct
id|report_param_cmd
(brace
DECL|member|object_id
id|UCHAR
id|object_id
suffix:semicolon
DECL|member|number_objects
id|UCHAR
id|number_objects
suffix:semicolon
DECL|member|failure_cause
id|UCHAR
id|failure_cause
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|start_network_cmd
r_struct
id|start_network_cmd
(brace
DECL|member|update_param
id|UCHAR
id|update_param
suffix:semicolon
DECL|member|bssid
id|UCHAR
id|bssid
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|net_initiated
id|UCHAR
id|net_initiated
suffix:semicolon
DECL|member|net_default_tx_rate
id|UCHAR
id|net_default_tx_rate
suffix:semicolon
DECL|member|encryption
id|UCHAR
id|encryption
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|join_network_cmd
r_struct
id|join_network_cmd
(brace
DECL|member|update_param
id|UCHAR
id|update_param
suffix:semicolon
DECL|member|bssid
id|UCHAR
id|bssid
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|net_initiated
id|UCHAR
id|net_initiated
suffix:semicolon
DECL|member|net_default_tx_rate
id|UCHAR
id|net_default_tx_rate
suffix:semicolon
DECL|member|encryption
id|UCHAR
id|encryption
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx_requested_cmd
r_struct
id|tx_requested_cmd
(brace
DECL|member|tx_data_ptr
id|UCHAR
id|tx_data_ptr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|tx_data_length
id|UCHAR
id|tx_data_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|host_reserved
id|UCHAR
id|host_reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tx_rate
id|UCHAR
id|tx_rate
suffix:semicolon
DECL|member|pow_sav_mode
id|UCHAR
id|pow_sav_mode
suffix:semicolon
DECL|member|retries
id|UCHAR
id|retries
suffix:semicolon
DECL|member|antenna
id|UCHAR
id|antenna
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx_requested_cmd_4
r_struct
id|tx_requested_cmd_4
(brace
DECL|member|tx_data_ptr
id|UCHAR
id|tx_data_ptr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|tx_data_length
id|UCHAR
id|tx_data_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dest_addr
id|UCHAR
id|dest_addr
(braket
id|ADDRLEN
)braket
suffix:semicolon
DECL|member|pow_sav_mode
id|UCHAR
id|pow_sav_mode
suffix:semicolon
DECL|member|retries
id|UCHAR
id|retries
suffix:semicolon
DECL|member|station_id
id|UCHAR
id|station_id
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|memory_dump_cmd
r_struct
id|memory_dump_cmd
(brace
DECL|member|memory_type
id|UCHAR
id|memory_type
suffix:semicolon
DECL|member|memory_ptr
id|UCHAR
id|memory_ptr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|length
id|UCHAR
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|update_association_cmd
r_struct
id|update_association_cmd
(brace
DECL|member|status
id|UCHAR
id|status
suffix:semicolon
DECL|member|aid
id|UCHAR
id|aid
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|start_timer_cmd
r_struct
id|start_timer_cmd
(brace
DECL|member|duration
id|UCHAR
id|duration
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ccs
r_struct
id|ccs
(brace
DECL|member|buffer_status
id|UCHAR
id|buffer_status
suffix:semicolon
multiline_comment|/* 0 = buffer free, 1 = buffer busy */
multiline_comment|/* 2 = command complete, 3 = failed */
DECL|member|cmd
id|UCHAR
id|cmd
suffix:semicolon
multiline_comment|/* command to ECF                   */
DECL|member|link
id|UCHAR
id|link
suffix:semicolon
multiline_comment|/* link to next CCS, FF=end of list */
multiline_comment|/* command specific parameters      */
r_union
(brace
DECL|member|reserved
r_char
id|reserved
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|update_param
r_struct
id|update_param_cmd
id|update_param
suffix:semicolon
DECL|member|report_param
r_struct
id|report_param_cmd
id|report_param
suffix:semicolon
DECL|member|nummulticast
id|UCHAR
id|nummulticast
suffix:semicolon
DECL|member|mode
id|UCHAR
id|mode
suffix:semicolon
DECL|member|start_network
r_struct
id|start_network_cmd
id|start_network
suffix:semicolon
DECL|member|join_network
r_struct
id|join_network_cmd
id|join_network
suffix:semicolon
DECL|member|tx_request
r_struct
id|tx_requested_cmd
id|tx_request
suffix:semicolon
DECL|member|memory_dump
r_struct
id|memory_dump_cmd
id|memory_dump
suffix:semicolon
DECL|member|update_assoc
r_struct
id|update_association_cmd
id|update_assoc
suffix:semicolon
DECL|member|start_timer
r_struct
id|start_timer_cmd
id|start_timer
suffix:semicolon
DECL|member|var
)brace
id|var
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/* Transmit buffer structures */
DECL|struct|tib_structure
r_struct
id|tib_structure
(brace
DECL|member|ccs_index
id|UCHAR
id|ccs_index
suffix:semicolon
DECL|member|psm
id|UCHAR
id|psm
suffix:semicolon
DECL|member|pass_fail
id|UCHAR
id|pass_fail
suffix:semicolon
DECL|member|retry_count
id|UCHAR
id|retry_count
suffix:semicolon
DECL|member|max_retries
id|UCHAR
id|max_retries
suffix:semicolon
DECL|member|frags_remaining
id|UCHAR
id|frags_remaining
suffix:semicolon
DECL|member|no_rb
id|UCHAR
id|no_rb
suffix:semicolon
DECL|member|rts_reqd
id|UCHAR
id|rts_reqd
suffix:semicolon
DECL|member|csma_tx_cntrl_2
id|UCHAR
id|csma_tx_cntrl_2
suffix:semicolon
DECL|member|sifs_tx_cntrl_2
id|UCHAR
id|sifs_tx_cntrl_2
suffix:semicolon
DECL|member|tx_dma_addr_1
id|UCHAR
id|tx_dma_addr_1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|tx_dma_addr_2
id|UCHAR
id|tx_dma_addr_2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|var_dur_2mhz
id|UCHAR
id|var_dur_2mhz
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|var_dur_1mhz
id|UCHAR
id|var_dur_1mhz
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|max_dur_2mhz
id|UCHAR
id|max_dur_2mhz
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|max_dur_1mhz
id|UCHAR
id|max_dur_1mhz
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hdr_len
id|UCHAR
id|hdr_len
suffix:semicolon
DECL|member|max_frag_len
id|UCHAR
id|max_frag_len
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|var_len
id|UCHAR
id|var_len
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|phy_hdr_4
id|UCHAR
id|phy_hdr_4
suffix:semicolon
DECL|member|mac_hdr_1
id|UCHAR
id|mac_hdr_1
suffix:semicolon
DECL|member|mac_hdr_2
id|UCHAR
id|mac_hdr_2
suffix:semicolon
DECL|member|sid
id|UCHAR
id|sid
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|phy_header
r_struct
id|phy_header
(brace
DECL|member|sfd
id|UCHAR
id|sfd
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hdr_3
id|UCHAR
id|hdr_3
suffix:semicolon
DECL|member|hdr_4
id|UCHAR
id|hdr_4
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rx_msg
r_struct
id|rx_msg
(brace
DECL|member|mac
r_struct
id|mac_header
id|mac
suffix:semicolon
DECL|member|var
id|UCHAR
id|var
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx_msg
r_struct
id|tx_msg
(brace
DECL|member|tib
r_struct
id|tib_structure
id|tib
suffix:semicolon
DECL|member|phy
r_struct
id|phy_header
id|phy
suffix:semicolon
DECL|member|mac
r_struct
id|mac_header
id|mac
suffix:semicolon
DECL|member|var
id|UCHAR
id|var
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****** ECF Receive Control Stucture (RCS) Area at Shared RAM offset 0x0800  */
multiline_comment|/* Structures for command specific parameters (rcs.var) */
DECL|struct|rx_packet_cmd
r_struct
id|rx_packet_cmd
(brace
DECL|member|rx_data_ptr
id|UCHAR
id|rx_data_ptr
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rx_data_length
id|UCHAR
id|rx_data_length
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rx_sig_lev
id|UCHAR
id|rx_sig_lev
suffix:semicolon
DECL|member|next_frag_rcs_index
id|UCHAR
id|next_frag_rcs_index
suffix:semicolon
DECL|member|totalpacketlength
id|UCHAR
id|totalpacketlength
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rejoin_net_cmplt_cmd
r_struct
id|rejoin_net_cmplt_cmd
(brace
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|member|bssid
id|UCHAR
id|bssid
(braket
id|ADDRLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|japan_call_sign_rxd
r_struct
id|japan_call_sign_rxd
(brace
DECL|member|rxd_call_sign
id|UCHAR
id|rxd_call_sign
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rcs
r_struct
id|rcs
(brace
DECL|member|buffer_status
id|UCHAR
id|buffer_status
suffix:semicolon
DECL|member|interrupt_id
id|UCHAR
id|interrupt_id
suffix:semicolon
DECL|member|link_field
id|UCHAR
id|link_field
suffix:semicolon
multiline_comment|/* command specific parameters      */
r_union
(brace
DECL|member|reserved
id|UCHAR
id|reserved
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|rx_packet
r_struct
id|rx_packet_cmd
id|rx_packet
suffix:semicolon
DECL|member|rejoin_net_complete
r_struct
id|rejoin_net_cmplt_cmd
id|rejoin_net_complete
suffix:semicolon
DECL|member|japan_call_sign
r_struct
id|japan_call_sign_rxd
id|japan_call_sign
suffix:semicolon
DECL|member|var
)brace
id|var
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****** Startup parameter structures for both versions of firmware ***********/
DECL|struct|b4_startup_params
r_struct
id|b4_startup_params
(brace
DECL|member|a_network_type
id|UCHAR
id|a_network_type
suffix:semicolon
multiline_comment|/* C_ADHOC, C_INFRA                 */
DECL|member|a_acting_as_ap_status
id|UCHAR
id|a_acting_as_ap_status
suffix:semicolon
multiline_comment|/* C_TYPE_STA, C_TYPE_AP            */
DECL|member|a_current_ess_id
id|UCHAR
id|a_current_ess_id
(braket
id|ESSID_SIZE
)braket
suffix:semicolon
multiline_comment|/* Null terminated unless 32 long   */
DECL|member|a_scanning_mode
id|UCHAR
id|a_scanning_mode
suffix:semicolon
multiline_comment|/* passive 0, active 1              */
DECL|member|a_power_mgt_state
id|UCHAR
id|a_power_mgt_state
suffix:semicolon
multiline_comment|/* CAM 0,                           */
DECL|member|a_mac_addr
id|UCHAR
id|a_mac_addr
(braket
id|ADDRLEN
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_frag_threshold
id|UCHAR
id|a_frag_threshold
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 512                              */
DECL|member|a_hop_time
id|UCHAR
id|a_hop_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 16k * 2**n, n=0-4 in Kus         */
DECL|member|a_beacon_period
id|UCHAR
id|a_beacon_period
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* n * a_hop_time  in Kus           */
DECL|member|a_dtim_period
id|UCHAR
id|a_dtim_period
suffix:semicolon
multiline_comment|/* in beacons                       */
DECL|member|a_retry_max
id|UCHAR
id|a_retry_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_ack_timeout
id|UCHAR
id|a_ack_timeout
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_sifs
id|UCHAR
id|a_sifs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_difs
id|UCHAR
id|a_difs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_pifs
id|UCHAR
id|a_pifs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_rts_threshold
id|UCHAR
id|a_rts_threshold
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_scan_dwell_time
id|UCHAR
id|a_scan_dwell_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_max_scan_dwell_time
id|UCHAR
id|a_max_scan_dwell_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_assoc_resp_timeout_thresh
id|UCHAR
id|a_assoc_resp_timeout_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_adhoc_scan_cycle_max
id|UCHAR
id|a_adhoc_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_scan_cycle_max
id|UCHAR
id|a_infra_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_super_scan_cycle_max
id|UCHAR
id|a_infra_super_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_promiscuous_mode
id|UCHAR
id|a_promiscuous_mode
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_unique_word
id|UCHAR
id|a_unique_word
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_slot_time
id|UCHAR
id|a_slot_time
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_roaming_low_snr_thresh
id|UCHAR
id|a_roaming_low_snr_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_low_snr_count_thresh
id|UCHAR
id|a_low_snr_count_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_missed_bcn_thresh
id|UCHAR
id|a_infra_missed_bcn_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_adhoc_missed_bcn_thresh
id|UCHAR
id|a_adhoc_missed_bcn_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_curr_country_code
id|UCHAR
id|a_curr_country_code
suffix:semicolon
multiline_comment|/* C_USA                            */
DECL|member|a_hop_pattern
id|UCHAR
id|a_hop_pattern
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_hop_pattern_length
id|UCHAR
id|a_hop_pattern_length
suffix:semicolon
multiline_comment|/*                                  */
multiline_comment|/* b4 - b5 differences start here */
DECL|member|a_cw_max
id|UCHAR
id|a_cw_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_cw_min
id|UCHAR
id|a_cw_min
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_noise_filter_gain
id|UCHAR
id|a_noise_filter_gain
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_noise_limit_offset
id|UCHAR
id|a_noise_limit_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_det_rssi_thresh_offset
id|UCHAR
id|a_det_rssi_thresh_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_med_busy_thresh_offset
id|UCHAR
id|a_med_busy_thresh_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_det_sync_thresh
id|UCHAR
id|a_det_sync_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_mode
id|UCHAR
id|a_test_mode
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_min_chan_num
id|UCHAR
id|a_test_min_chan_num
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_max_chan_num
id|UCHAR
id|a_test_max_chan_num
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_rx_tx_delay
id|UCHAR
id|a_rx_tx_delay
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_current_bss_id
id|UCHAR
id|a_current_bss_id
(braket
id|ADDRLEN
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_hop_set
id|UCHAR
id|a_hop_set
suffix:semicolon
multiline_comment|/*                                  */
)brace
suffix:semicolon
DECL|struct|b5_startup_params
r_struct
id|b5_startup_params
(brace
DECL|member|a_network_type
id|UCHAR
id|a_network_type
suffix:semicolon
multiline_comment|/* C_ADHOC, C_INFRA                 */
DECL|member|a_acting_as_ap_status
id|UCHAR
id|a_acting_as_ap_status
suffix:semicolon
multiline_comment|/* C_TYPE_STA, C_TYPE_AP            */
DECL|member|a_current_ess_id
id|UCHAR
id|a_current_ess_id
(braket
id|ESSID_SIZE
)braket
suffix:semicolon
multiline_comment|/* Null terminated unless 32 long   */
DECL|member|a_scanning_mode
id|UCHAR
id|a_scanning_mode
suffix:semicolon
multiline_comment|/* passive 0, active 1              */
DECL|member|a_power_mgt_state
id|UCHAR
id|a_power_mgt_state
suffix:semicolon
multiline_comment|/* CAM 0,                           */
DECL|member|a_mac_addr
id|UCHAR
id|a_mac_addr
(braket
id|ADDRLEN
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_frag_threshold
id|UCHAR
id|a_frag_threshold
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 512                              */
DECL|member|a_hop_time
id|UCHAR
id|a_hop_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 16k * 2**n, n=0-4 in Kus         */
DECL|member|a_beacon_period
id|UCHAR
id|a_beacon_period
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* n * a_hop_time  in Kus           */
DECL|member|a_dtim_period
id|UCHAR
id|a_dtim_period
suffix:semicolon
multiline_comment|/* in beacons                       */
DECL|member|a_retry_max
id|UCHAR
id|a_retry_max
suffix:semicolon
multiline_comment|/* 4                                */
DECL|member|a_ack_timeout
id|UCHAR
id|a_ack_timeout
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_sifs
id|UCHAR
id|a_sifs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_difs
id|UCHAR
id|a_difs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_pifs
id|UCHAR
id|a_pifs
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_rts_threshold
id|UCHAR
id|a_rts_threshold
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_scan_dwell_time
id|UCHAR
id|a_scan_dwell_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_max_scan_dwell_time
id|UCHAR
id|a_max_scan_dwell_time
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_assoc_resp_timeout_thresh
id|UCHAR
id|a_assoc_resp_timeout_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_adhoc_scan_cycle_max
id|UCHAR
id|a_adhoc_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_scan_cycle_max
id|UCHAR
id|a_infra_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_super_scan_cycle_max
id|UCHAR
id|a_infra_super_scan_cycle_max
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_promiscuous_mode
id|UCHAR
id|a_promiscuous_mode
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_unique_word
id|UCHAR
id|a_unique_word
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_slot_time
id|UCHAR
id|a_slot_time
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_roaming_low_snr_thresh
id|UCHAR
id|a_roaming_low_snr_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_low_snr_count_thresh
id|UCHAR
id|a_low_snr_count_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_infra_missed_bcn_thresh
id|UCHAR
id|a_infra_missed_bcn_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_adhoc_missed_bcn_thresh
id|UCHAR
id|a_adhoc_missed_bcn_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_curr_country_code
id|UCHAR
id|a_curr_country_code
suffix:semicolon
multiline_comment|/* C_USA                            */
DECL|member|a_hop_pattern
id|UCHAR
id|a_hop_pattern
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_hop_pattern_length
id|UCHAR
id|a_hop_pattern_length
suffix:semicolon
multiline_comment|/*                                  */
multiline_comment|/* b4 - b5 differences start here */
DECL|member|a_cw_max
id|UCHAR
id|a_cw_max
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_cw_min
id|UCHAR
id|a_cw_min
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_noise_filter_gain
id|UCHAR
id|a_noise_filter_gain
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_noise_limit_offset
id|UCHAR
id|a_noise_limit_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_det_rssi_thresh_offset
id|UCHAR
id|a_det_rssi_thresh_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_med_busy_thresh_offset
id|UCHAR
id|a_med_busy_thresh_offset
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_det_sync_thresh
id|UCHAR
id|a_det_sync_thresh
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_mode
id|UCHAR
id|a_test_mode
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_min_chan_num
id|UCHAR
id|a_test_min_chan_num
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_test_max_chan_num
id|UCHAR
id|a_test_max_chan_num
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|a_allow_bcast_SSID_probe_rsp
id|UCHAR
id|a_allow_bcast_SSID_probe_rsp
suffix:semicolon
DECL|member|a_privacy_must_start
id|UCHAR
id|a_privacy_must_start
suffix:semicolon
DECL|member|a_privacy_can_join
id|UCHAR
id|a_privacy_can_join
suffix:semicolon
DECL|member|a_basic_rate_set
id|UCHAR
id|a_basic_rate_set
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
DECL|macro|RAY_IOCG_PARMS
mdefine_line|#define RAY_IOCG_PARMS (SIOCDEVPRIVATE)
DECL|macro|RAY_IOCS_PARMS
mdefine_line|#define RAY_IOCS_PARMS (SIOCDEVPRIVATE + 1)
DECL|macro|RAY_DO_CMD
mdefine_line|#define RAY_DO_CMD     (SIOCDEVPRIVATE + 2)
multiline_comment|/****** ethernet &lt;-&gt; 802.11 translation **************************************/
DECL|struct|snaphdr_t
r_typedef
r_struct
id|snaphdr_t
(brace
DECL|member|dsap
id|UCHAR
id|dsap
suffix:semicolon
DECL|member|ssap
id|UCHAR
id|ssap
suffix:semicolon
DECL|member|ctrl
id|UCHAR
id|ctrl
suffix:semicolon
DECL|member|org
id|UCHAR
id|org
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ethertype
id|UCHAR
id|ethertype
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|snaphdr_t
)brace
id|snaphdr_t
suffix:semicolon
DECL|macro|BRIDGE_ENCAP
mdefine_line|#define BRIDGE_ENCAP  0xf80000
DECL|macro|RFC1042_ENCAP
mdefine_line|#define RFC1042_ENCAP 0
DECL|macro|SNAP_ID
mdefine_line|#define SNAP_ID       0x0003aaaa
DECL|macro|RAY_IPX_TYPE
mdefine_line|#define RAY_IPX_TYPE  0x8137
DECL|macro|APPLEARP_TYPE
mdefine_line|#define APPLEARP_TYPE 0x80f3
multiline_comment|/*****************************************************************************/
macro_line|#endif /* #ifndef RAYLINK_H */
eof
