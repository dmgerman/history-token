macro_line|#ifndef __WL3501_H__
DECL|macro|__WL3501_H__
mdefine_line|#define __WL3501_H__
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/* define for WLA 2.0 */
DECL|macro|WL3501_BLKSZ
mdefine_line|#define WL3501_BLKSZ 256
multiline_comment|/*&n; * ID for input Signals of DRIVER block&n; * bit[7-5] is block ID: 000&n; * bit[4-0] is signal ID&n;*/
DECL|enum|wl3501_signals
r_enum
id|wl3501_signals
(brace
DECL|enumerator|WL3501_SIG_ALARM
id|WL3501_SIG_ALARM
comma
DECL|enumerator|WL3501_SIG_MD_CONFIRM
id|WL3501_SIG_MD_CONFIRM
comma
DECL|enumerator|WL3501_SIG_MD_IND
id|WL3501_SIG_MD_IND
comma
DECL|enumerator|WL3501_SIG_ASSOC_CONFIRM
id|WL3501_SIG_ASSOC_CONFIRM
comma
DECL|enumerator|WL3501_SIG_ASSOC_IND
id|WL3501_SIG_ASSOC_IND
comma
DECL|enumerator|WL3501_SIG_AUTH_CONFIRM
id|WL3501_SIG_AUTH_CONFIRM
comma
DECL|enumerator|WL3501_SIG_AUTH_IND
id|WL3501_SIG_AUTH_IND
comma
DECL|enumerator|WL3501_SIG_DEAUTH_CONFIRM
id|WL3501_SIG_DEAUTH_CONFIRM
comma
DECL|enumerator|WL3501_SIG_DEAUTH_IND
id|WL3501_SIG_DEAUTH_IND
comma
DECL|enumerator|WL3501_SIG_DISASSOC_CONFIRM
id|WL3501_SIG_DISASSOC_CONFIRM
comma
DECL|enumerator|WL3501_SIG_DISASSOC_IND
id|WL3501_SIG_DISASSOC_IND
comma
DECL|enumerator|WL3501_SIG_GET_CONFIRM
id|WL3501_SIG_GET_CONFIRM
comma
DECL|enumerator|WL3501_SIG_JOIN_CONFIRM
id|WL3501_SIG_JOIN_CONFIRM
comma
DECL|enumerator|WL3501_SIG_PWR_MGMT_CONFIRM
id|WL3501_SIG_PWR_MGMT_CONFIRM
comma
DECL|enumerator|WL3501_SIG_REASSOC_CONFIRM
id|WL3501_SIG_REASSOC_CONFIRM
comma
DECL|enumerator|WL3501_SIG_REASSOC_IND
id|WL3501_SIG_REASSOC_IND
comma
DECL|enumerator|WL3501_SIG_SCAN_CONFIRM
id|WL3501_SIG_SCAN_CONFIRM
comma
DECL|enumerator|WL3501_SIG_SET_CONFIRM
id|WL3501_SIG_SET_CONFIRM
comma
DECL|enumerator|WL3501_SIG_START_CONFIRM
id|WL3501_SIG_START_CONFIRM
comma
DECL|enumerator|WL3501_SIG_RESYNC_CONFIRM
id|WL3501_SIG_RESYNC_CONFIRM
comma
DECL|enumerator|WL3501_SIG_SITE_CONFIRM
id|WL3501_SIG_SITE_CONFIRM
comma
DECL|enumerator|WL3501_SIG_SAVE_CONFIRM
id|WL3501_SIG_SAVE_CONFIRM
comma
DECL|enumerator|WL3501_SIG_RFTEST_CONFIRM
id|WL3501_SIG_RFTEST_CONFIRM
comma
multiline_comment|/*&n; * ID for input Signals of MLME block&n; * bit[7-5] is block ID: 010&n; * bit[4-0] is signal ID&n; */
DECL|enumerator|WL3501_SIG_ASSOC_REQ
id|WL3501_SIG_ASSOC_REQ
op_assign
l_int|0x20
comma
DECL|enumerator|WL3501_SIG_AUTH_REQ
id|WL3501_SIG_AUTH_REQ
comma
DECL|enumerator|WL3501_SIG_DEAUTH_REQ
id|WL3501_SIG_DEAUTH_REQ
comma
DECL|enumerator|WL3501_SIG_DISASSOC_REQ
id|WL3501_SIG_DISASSOC_REQ
comma
DECL|enumerator|WL3501_SIG_GET_REQ
id|WL3501_SIG_GET_REQ
comma
DECL|enumerator|WL3501_SIG_JOIN_REQ
id|WL3501_SIG_JOIN_REQ
comma
DECL|enumerator|WL3501_SIG_POWERMGT_REQ
id|WL3501_SIG_POWERMGT_REQ
comma
DECL|enumerator|WL3501_SIG_REASSOC_REQ
id|WL3501_SIG_REASSOC_REQ
comma
DECL|enumerator|WL3501_SIG_SCAN_REQ
id|WL3501_SIG_SCAN_REQ
comma
DECL|enumerator|WL3501_SIG_SET_REQ
id|WL3501_SIG_SET_REQ
comma
DECL|enumerator|WL3501_SIG_START_REQ
id|WL3501_SIG_START_REQ
comma
DECL|enumerator|WL3501_SIG_MD_REQ
id|WL3501_SIG_MD_REQ
comma
DECL|enumerator|WL3501_SIG_RESYNC_REQ
id|WL3501_SIG_RESYNC_REQ
comma
DECL|enumerator|WL3501_SIG_SITE_REQ
id|WL3501_SIG_SITE_REQ
comma
DECL|enumerator|WL3501_SIG_SAVE_REQ
id|WL3501_SIG_SAVE_REQ
comma
DECL|enumerator|WL3501_SIG_RF_TEST_REQ
id|WL3501_SIG_RF_TEST_REQ
comma
DECL|enumerator|WL3501_SIG_MM_CONFIRM
id|WL3501_SIG_MM_CONFIRM
op_assign
l_int|0x60
comma
DECL|enumerator|WL3501_SIG_MM_IND
id|WL3501_SIG_MM_IND
comma
)brace
suffix:semicolon
DECL|enum|wl3501_mib_attribs
r_enum
id|wl3501_mib_attribs
(brace
DECL|enumerator|WL3501_MIB_ATTR_STATION_ID
id|WL3501_MIB_ATTR_STATION_ID
comma
DECL|enumerator|WL3501_MIB_ATTR_AUTH_ALGORITHMS
id|WL3501_MIB_ATTR_AUTH_ALGORITHMS
comma
DECL|enumerator|WL3501_MIB_ATTR_AUTH_TYPE
id|WL3501_MIB_ATTR_AUTH_TYPE
comma
DECL|enumerator|WL3501_MIB_ATTR_MEDIUM_OCCUPANCY_LIMIT
id|WL3501_MIB_ATTR_MEDIUM_OCCUPANCY_LIMIT
comma
DECL|enumerator|WL3501_MIB_ATTR_CF_POLLABLE
id|WL3501_MIB_ATTR_CF_POLLABLE
comma
DECL|enumerator|WL3501_MIB_ATTR_CFP_PERIOD
id|WL3501_MIB_ATTR_CFP_PERIOD
comma
DECL|enumerator|WL3501_MIB_ATTR_CFPMAX_DURATION
id|WL3501_MIB_ATTR_CFPMAX_DURATION
comma
DECL|enumerator|WL3501_MIB_ATTR_AUTH_RESP_TMOUT
id|WL3501_MIB_ATTR_AUTH_RESP_TMOUT
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_DTIMS
id|WL3501_MIB_ATTR_RX_DTIMS
comma
DECL|enumerator|WL3501_MIB_ATTR_PRIV_OPT_IMPLEMENTED
id|WL3501_MIB_ATTR_PRIV_OPT_IMPLEMENTED
comma
DECL|enumerator|WL3501_MIB_ATTR_PRIV_INVOKED
id|WL3501_MIB_ATTR_PRIV_INVOKED
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_DEFAULT_KEYS
id|WL3501_MIB_ATTR_WEP_DEFAULT_KEYS
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_DEFAULT_KEY_ID
id|WL3501_MIB_ATTR_WEP_DEFAULT_KEY_ID
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_KEY_MAPPINGS
id|WL3501_MIB_ATTR_WEP_KEY_MAPPINGS
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_KEY_MAPPINGS_LEN
id|WL3501_MIB_ATTR_WEP_KEY_MAPPINGS_LEN
comma
DECL|enumerator|WL3501_MIB_ATTR_EXCLUDE_UNENCRYPTED
id|WL3501_MIB_ATTR_EXCLUDE_UNENCRYPTED
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT
id|WL3501_MIB_ATTR_WEP_ICV_ERROR_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT
id|WL3501_MIB_ATTR_WEP_UNDECRYPTABLE_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT
id|WL3501_MIB_ATTR_WEP_EXCLUDED_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_MAC_ADDR
id|WL3501_MIB_ATTR_MAC_ADDR
comma
DECL|enumerator|WL3501_MIB_ATTR_GROUP_ADDRS
id|WL3501_MIB_ATTR_GROUP_ADDRS
comma
DECL|enumerator|WL3501_MIB_ATTR_RTS_THRESHOLD
id|WL3501_MIB_ATTR_RTS_THRESHOLD
comma
DECL|enumerator|WL3501_MIB_ATTR_SHORT_RETRY_LIMIT
id|WL3501_MIB_ATTR_SHORT_RETRY_LIMIT
comma
DECL|enumerator|WL3501_MIB_ATTR_LONG_RETRY_LIMIT
id|WL3501_MIB_ATTR_LONG_RETRY_LIMIT
comma
DECL|enumerator|WL3501_MIB_ATTR_FRAG_THRESHOLD
id|WL3501_MIB_ATTR_FRAG_THRESHOLD
comma
DECL|enumerator|WL3501_MIB_ATTR_MAX_TX_MSDU_LIFETIME
id|WL3501_MIB_ATTR_MAX_TX_MSDU_LIFETIME
comma
DECL|enumerator|WL3501_MIB_ATTR_MAX_RX_LIFETIME
id|WL3501_MIB_ATTR_MAX_RX_LIFETIME
comma
DECL|enumerator|WL3501_MIB_ATTR_MANUFACTURER_ID
id|WL3501_MIB_ATTR_MANUFACTURER_ID
comma
DECL|enumerator|WL3501_MIB_ATTR_PRODUCT_ID
id|WL3501_MIB_ATTR_PRODUCT_ID
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_FRAG_COUNT
id|WL3501_MIB_ATTR_TX_FRAG_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_MULTICAST_TX_FRAME_COUNT
id|WL3501_MIB_ATTR_MULTICAST_TX_FRAME_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_FAILED_COUNT
id|WL3501_MIB_ATTR_FAILED_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_FRAG_COUNT
id|WL3501_MIB_ATTR_RX_FRAG_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_MULTICAST_RX_COUNT
id|WL3501_MIB_ATTR_MULTICAST_RX_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_FCS_ERROR_COUNT
id|WL3501_MIB_ATTR_FCS_ERROR_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_RETRY_COUNT
id|WL3501_MIB_ATTR_RETRY_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_MULTIPLE_RETRY_COUNT
id|WL3501_MIB_ATTR_MULTIPLE_RETRY_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_RTS_SUCCESS_COUNT
id|WL3501_MIB_ATTR_RTS_SUCCESS_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_RTS_FAILURE_COUNT
id|WL3501_MIB_ATTR_RTS_FAILURE_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_ACK_FAILURE_COUNT
id|WL3501_MIB_ATTR_ACK_FAILURE_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT
id|WL3501_MIB_ATTR_FRAME_DUPLICATE_COUNT
comma
DECL|enumerator|WL3501_MIB_ATTR_PHY_TYPE
id|WL3501_MIB_ATTR_PHY_TYPE
comma
DECL|enumerator|WL3501_MIB_ATTR_REG_DOMAINS_SUPPORT
id|WL3501_MIB_ATTR_REG_DOMAINS_SUPPORT
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_REG_DOMAIN
id|WL3501_MIB_ATTR_CURRENT_REG_DOMAIN
comma
DECL|enumerator|WL3501_MIB_ATTR_SLOT_TIME
id|WL3501_MIB_ATTR_SLOT_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_CCA_TIME
id|WL3501_MIB_ATTR_CCA_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_TX_TURNAROUND_TIME
id|WL3501_MIB_ATTR_RX_TX_TURNAROUND_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PLCP_DELAY
id|WL3501_MIB_ATTR_TX_PLCP_DELAY
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_TX_SWITCH_TIME
id|WL3501_MIB_ATTR_RX_TX_SWITCH_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_RAMP_ON_TIME
id|WL3501_MIB_ATTR_TX_RAMP_ON_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_RF_DELAY
id|WL3501_MIB_ATTR_TX_RF_DELAY
comma
DECL|enumerator|WL3501_MIB_ATTR_SIFS_TIME
id|WL3501_MIB_ATTR_SIFS_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_RF_DELAY
id|WL3501_MIB_ATTR_RX_RF_DELAY
comma
DECL|enumerator|WL3501_MIB_ATTR_RX_PLCP_DELAY
id|WL3501_MIB_ATTR_RX_PLCP_DELAY
comma
DECL|enumerator|WL3501_MIB_ATTR_MAC_PROCESSING_DELAY
id|WL3501_MIB_ATTR_MAC_PROCESSING_DELAY
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_RAMP_OFF_TIME
id|WL3501_MIB_ATTR_TX_RAMP_OFF_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_PREAMBLE_LEN
id|WL3501_MIB_ATTR_PREAMBLE_LEN
comma
DECL|enumerator|WL3501_MIB_ATTR_PLCP_HEADER_LEN
id|WL3501_MIB_ATTR_PLCP_HEADER_LEN
comma
DECL|enumerator|WL3501_MIB_ATTR_MPDU_DURATION_FACTOR
id|WL3501_MIB_ATTR_MPDU_DURATION_FACTOR
comma
DECL|enumerator|WL3501_MIB_ATTR_AIR_PROPAGATION_TIME
id|WL3501_MIB_ATTR_AIR_PROPAGATION_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_TEMP_TYPE
id|WL3501_MIB_ATTR_TEMP_TYPE
comma
DECL|enumerator|WL3501_MIB_ATTR_CW_MIN
id|WL3501_MIB_ATTR_CW_MIN
comma
DECL|enumerator|WL3501_MIB_ATTR_CW_MAX
id|WL3501_MIB_ATTR_CW_MAX
comma
DECL|enumerator|WL3501_MIB_ATTR_SUPPORT_DATA_RATES_TX
id|WL3501_MIB_ATTR_SUPPORT_DATA_RATES_TX
comma
DECL|enumerator|WL3501_MIB_ATTR_SUPPORT_DATA_RATES_RX
id|WL3501_MIB_ATTR_SUPPORT_DATA_RATES_RX
comma
DECL|enumerator|WL3501_MIB_ATTR_MPDU_MAX_LEN
id|WL3501_MIB_ATTR_MPDU_MAX_LEN
comma
DECL|enumerator|WL3501_MIB_ATTR_SUPPORT_TX_ANTENNAS
id|WL3501_MIB_ATTR_SUPPORT_TX_ANTENNAS
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_TX_ANTENNA
id|WL3501_MIB_ATTR_CURRENT_TX_ANTENNA
comma
DECL|enumerator|WL3501_MIB_ATTR_SUPPORT_RX_ANTENNAS
id|WL3501_MIB_ATTR_SUPPORT_RX_ANTENNAS
comma
DECL|enumerator|WL3501_MIB_ATTR_DIVERSITY_SUPPORT
id|WL3501_MIB_ATTR_DIVERSITY_SUPPORT
comma
DECL|enumerator|WL3501_MIB_ATTR_DIVERSITY_SELECTION_RS
id|WL3501_MIB_ATTR_DIVERSITY_SELECTION_RS
comma
DECL|enumerator|WL3501_MIB_ATTR_NR_SUPPORTED_PWR_LEVELS
id|WL3501_MIB_ATTR_NR_SUPPORTED_PWR_LEVELS
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL1
id|WL3501_MIB_ATTR_TX_PWR_LEVEL1
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL2
id|WL3501_MIB_ATTR_TX_PWR_LEVEL2
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL3
id|WL3501_MIB_ATTR_TX_PWR_LEVEL3
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL4
id|WL3501_MIB_ATTR_TX_PWR_LEVEL4
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL5
id|WL3501_MIB_ATTR_TX_PWR_LEVEL5
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL6
id|WL3501_MIB_ATTR_TX_PWR_LEVEL6
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL7
id|WL3501_MIB_ATTR_TX_PWR_LEVEL7
comma
DECL|enumerator|WL3501_MIB_ATTR_TX_PWR_LEVEL8
id|WL3501_MIB_ATTR_TX_PWR_LEVEL8
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL
id|WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_CHAN
id|WL3501_MIB_ATTR_CURRENT_CHAN
comma
DECL|enumerator|WL3501_MIB_ATTR_CCA_MODE_SUPPORTED
id|WL3501_MIB_ATTR_CCA_MODE_SUPPORTED
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_CCA_MODE
id|WL3501_MIB_ATTR_CURRENT_CCA_MODE
comma
DECL|enumerator|WL3501_MIB_ATTR_ED_THRESHOLD
id|WL3501_MIB_ATTR_ED_THRESHOLD
comma
DECL|enumerator|WL3501_MIB_ATTR_SINTHESIZER_LOCKED
id|WL3501_MIB_ATTR_SINTHESIZER_LOCKED
comma
DECL|enumerator|WL3501_MIB_ATTR_CURRENT_PWR_STATE
id|WL3501_MIB_ATTR_CURRENT_PWR_STATE
comma
DECL|enumerator|WL3501_MIB_ATTR_DOZE_TURNON_TIME
id|WL3501_MIB_ATTR_DOZE_TURNON_TIME
comma
DECL|enumerator|WL3501_MIB_ATTR_RCR33
id|WL3501_MIB_ATTR_RCR33
comma
DECL|enumerator|WL3501_MIB_ATTR_DEFAULT_CHAN
id|WL3501_MIB_ATTR_DEFAULT_CHAN
comma
DECL|enumerator|WL3501_MIB_ATTR_SSID
id|WL3501_MIB_ATTR_SSID
comma
DECL|enumerator|WL3501_MIB_ATTR_PWR_MGMT_ENABLE
id|WL3501_MIB_ATTR_PWR_MGMT_ENABLE
comma
DECL|enumerator|WL3501_MIB_ATTR_NET_CAPABILITY
id|WL3501_MIB_ATTR_NET_CAPABILITY
comma
DECL|enumerator|WL3501_MIB_ATTR_ROUTING
id|WL3501_MIB_ATTR_ROUTING
comma
)brace
suffix:semicolon
DECL|enum|wl3501_net_type
r_enum
id|wl3501_net_type
(brace
DECL|enumerator|WL3501_NET_TYPE_INFRA
id|WL3501_NET_TYPE_INFRA
comma
DECL|enumerator|WL3501_NET_TYPE_ADHOC
id|WL3501_NET_TYPE_ADHOC
comma
DECL|enumerator|WL3501_NET_TYPE_ANY_BSS
id|WL3501_NET_TYPE_ANY_BSS
comma
)brace
suffix:semicolon
DECL|enum|wl3501_scan_type
r_enum
id|wl3501_scan_type
(brace
DECL|enumerator|WL3501_SCAN_TYPE_ACTIVE
id|WL3501_SCAN_TYPE_ACTIVE
comma
DECL|enumerator|WL3501_SCAN_TYPE_PASSIVE
id|WL3501_SCAN_TYPE_PASSIVE
comma
)brace
suffix:semicolon
DECL|enum|wl3501_tx_result
r_enum
id|wl3501_tx_result
(brace
DECL|enumerator|WL3501_TX_RESULT_SUCCESS
id|WL3501_TX_RESULT_SUCCESS
comma
DECL|enumerator|WL3501_TX_RESULT_NO_BSS
id|WL3501_TX_RESULT_NO_BSS
comma
DECL|enumerator|WL3501_TX_RESULT_RETRY_LIMIT
id|WL3501_TX_RESULT_RETRY_LIMIT
comma
)brace
suffix:semicolon
DECL|enum|wl3501_sys_type
r_enum
id|wl3501_sys_type
(brace
DECL|enumerator|WL3501_SYS_TYPE_OPEN
id|WL3501_SYS_TYPE_OPEN
comma
DECL|enumerator|WL3501_SYS_TYPE_SHARE_KEY
id|WL3501_SYS_TYPE_SHARE_KEY
comma
)brace
suffix:semicolon
DECL|enum|wl3501_status
r_enum
id|wl3501_status
(brace
DECL|enumerator|WL3501_STATUS_SUCCESS
id|WL3501_STATUS_SUCCESS
comma
DECL|enumerator|WL3501_STATUS_INVALID
id|WL3501_STATUS_INVALID
comma
DECL|enumerator|WL3501_STATUS_TIMEOUT
id|WL3501_STATUS_TIMEOUT
comma
DECL|enumerator|WL3501_STATUS_REFUSED
id|WL3501_STATUS_REFUSED
comma
DECL|enumerator|WL3501_STATUS_MANY_REQ
id|WL3501_STATUS_MANY_REQ
comma
DECL|enumerator|WL3501_STATUS_ALREADY_BSS
id|WL3501_STATUS_ALREADY_BSS
comma
)brace
suffix:semicolon
DECL|macro|WL3501_MGMT_CAPABILITY_ESS
mdefine_line|#define WL3501_MGMT_CAPABILITY_ESS&t;&t;0x0001  /* see 802.11 p.58 */
DECL|macro|WL3501_MGMT_CAPABILITY_IBSS
mdefine_line|#define WL3501_MGMT_CAPABILITY_IBSS&t;&t;0x0002  /*      - &quot; -&t;   */
DECL|macro|WL3501_MGMT_CAPABILITY_CF_POLLABLE
mdefine_line|#define WL3501_MGMT_CAPABILITY_CF_POLLABLE&t;0x0004  /*      - &quot; -&t;   */
DECL|macro|WL3501_MGMT_CAPABILITY_CF_POLL_REQUEST
mdefine_line|#define WL3501_MGMT_CAPABILITY_CF_POLL_REQUEST&t;0x0008  /*      - &quot; -&t;   */
DECL|macro|WL3501_MGMT_CAPABILITY_PRIVACY
mdefine_line|#define WL3501_MGMT_CAPABILITY_PRIVACY&t;&t;0x0010  /*      - &quot; -&t;   */
DECL|macro|WL3501_FREQ_DOMAIN_FCC
mdefine_line|#define WL3501_FREQ_DOMAIN_FCC    0x10&t;/* Channel 1 to 11 */
DECL|macro|WL3501_FREQ_DOMAIN_IC
mdefine_line|#define WL3501_FREQ_DOMAIN_IC     0x20&t;/* Channel 1 to 11 */
DECL|macro|WL3501_FREQ_DOMAIN_ETSI
mdefine_line|#define WL3501_FREQ_DOMAIN_ETSI   0x30&t;/* Channel 1 to 13 */
DECL|macro|WL3501_FREQ_DOMAIN_SPAIN
mdefine_line|#define WL3501_FREQ_DOMAIN_SPAIN  0x31&t;/* Channel 10 to 11 */
DECL|macro|WL3501_FREQ_DOMAIN_FRANCE
mdefine_line|#define WL3501_FREQ_DOMAIN_FRANCE 0x32&t;/* Channel 10 to 13 */
DECL|macro|WL3501_FREQ_DOMAIN_MKK
mdefine_line|#define WL3501_FREQ_DOMAIN_MKK    0x40&t;/* Channel 14 */
DECL|macro|WL3501_ESSID_MAX_LEN
mdefine_line|#define WL3501_ESSID_MAX_LEN (IW_ESSID_MAX_SIZE + 2)
DECL|struct|wl3501_tx_hdr
r_struct
id|wl3501_tx_hdr
(brace
DECL|member|tx_cnt
id|u16
id|tx_cnt
suffix:semicolon
DECL|member|sync
r_int
r_char
id|sync
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sfd
id|u16
id|sfd
suffix:semicolon
DECL|member|signal
r_int
r_char
id|signal
suffix:semicolon
DECL|member|service
r_int
r_char
id|service
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|crc16
id|u16
id|crc16
suffix:semicolon
DECL|member|frame_ctrl
id|u16
id|frame_ctrl
suffix:semicolon
DECL|member|duration_id
id|u16
id|duration_id
suffix:semicolon
DECL|member|addr1
r_int
r_char
id|addr1
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr2
r_int
r_char
id|addr2
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr3
r_int
r_char
id|addr3
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|seq_ctrl
id|u16
id|seq_ctrl
suffix:semicolon
DECL|member|addr4
r_int
r_char
id|addr4
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_rx_hdr
r_struct
id|wl3501_rx_hdr
(brace
DECL|member|rx_next_blk
id|u16
id|rx_next_blk
suffix:semicolon
DECL|member|rc_next_frame_blk
id|u16
id|rc_next_frame_blk
suffix:semicolon
DECL|member|rx_blk_ctrl
r_int
r_char
id|rx_blk_ctrl
suffix:semicolon
DECL|member|rx_next_frame
r_int
r_char
id|rx_next_frame
suffix:semicolon
DECL|member|rx_next_frame1
r_int
r_char
id|rx_next_frame1
suffix:semicolon
DECL|member|rssi
r_int
r_char
id|rssi
suffix:semicolon
DECL|member|time
r_int
r_char
id|time
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|signal
r_int
r_char
id|signal
suffix:semicolon
DECL|member|service
r_int
r_char
id|service
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|crc16
id|u16
id|crc16
suffix:semicolon
DECL|member|frame_ctrl
id|u16
id|frame_ctrl
suffix:semicolon
DECL|member|duration
id|u16
id|duration
suffix:semicolon
DECL|member|addr1
r_int
r_char
id|addr1
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr2
r_int
r_char
id|addr2
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr3
r_int
r_char
id|addr3
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|seq
id|u16
id|seq
suffix:semicolon
DECL|member|addr4
r_int
r_char
id|addr4
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_start_req
r_struct
id|wl3501_start_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|bss_type
r_int
r_char
id|bss_type
suffix:semicolon
DECL|member|beacon_period
id|u16
id|beacon_period
suffix:semicolon
DECL|member|dtim_period
id|u16
id|dtim_period
suffix:semicolon
DECL|member|probe_delay
id|u16
id|probe_delay
suffix:semicolon
DECL|member|cap_info
id|u16
id|cap_info
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|bss_basic_rate_set
r_int
r_char
id|bss_basic_rate_set
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|operational_rate_set
r_int
r_char
id|operational_rate_set
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|cf_pset
r_int
r_char
id|cf_pset
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|phy_pset
r_int
r_char
id|phy_pset
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ibss_pset
r_int
r_char
id|ibss_pset
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_assoc_req
r_struct
id|wl3501_assoc_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|timeout
id|u16
id|timeout
suffix:semicolon
DECL|member|cap_info
id|u16
id|cap_info
suffix:semicolon
DECL|member|listen_interval
id|u16
id|listen_interval
suffix:semicolon
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_assoc_confirm
r_struct
id|wl3501_assoc_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_assoc_ind
r_struct
id|wl3501_assoc_ind
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_auth_req
r_struct
id|wl3501_auth_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|timeout
id|u16
id|timeout
suffix:semicolon
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_auth_confirm
r_struct
id|wl3501_auth_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_get_req
r_struct
id|wl3501_get_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|mib_attrib
id|u16
id|mib_attrib
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_get_confirm
r_struct
id|wl3501_get_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|mib_status
id|u16
id|mib_status
suffix:semicolon
DECL|member|mib_attrib
id|u16
id|mib_attrib
suffix:semicolon
DECL|member|mib_value
r_int
r_char
id|mib_value
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_join_req
r_struct
id|wl3501_join_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|operational_rate_set
r_int
r_char
id|operational_rate_set
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|timeout
id|u16
id|timeout
suffix:semicolon
DECL|member|probe_delay
id|u16
id|probe_delay
suffix:semicolon
DECL|member|timestamp
r_int
r_char
id|timestamp
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|local_time
r_int
r_char
id|local_time
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|beacon_period
id|u16
id|beacon_period
suffix:semicolon
DECL|member|dtim_period
id|u16
id|dtim_period
suffix:semicolon
DECL|member|cap_info
id|u16
id|cap_info
suffix:semicolon
DECL|member|bss_type
r_int
r_char
id|bss_type
suffix:semicolon
DECL|member|bssid
r_int
r_char
id|bssid
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|phy_pset
r_int
r_char
id|phy_pset
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cf_pset
r_int
r_char
id|cf_pset
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ibss_pset
r_int
r_char
id|ibss_pset
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bss_basic_rate_set
r_int
r_char
id|bss_basic_rate_set
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_join_confirm
r_struct
id|wl3501_join_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_scan_req
r_struct
id|wl3501_scan_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|bss_type
r_int
r_char
id|bss_type
suffix:semicolon
DECL|member|probe_delay
id|u16
id|probe_delay
suffix:semicolon
DECL|member|min_chan_time
id|u16
id|min_chan_time
suffix:semicolon
DECL|member|max_chan_time
id|u16
id|max_chan_time
suffix:semicolon
DECL|member|chan_list
r_int
r_char
id|chan_list
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|bssid
r_int
r_char
id|bssid
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|scan_type
r_enum
id|wl3501_scan_type
id|scan_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_scan_confirm
r_struct
id|wl3501_scan_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|timestamp
r_int
r_char
id|timestamp
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|localtime
r_int
r_char
id|localtime
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|beacon_period
id|u16
id|beacon_period
suffix:semicolon
DECL|member|dtim_period
id|u16
id|dtim_period
suffix:semicolon
DECL|member|cap_info
id|u16
id|cap_info
suffix:semicolon
DECL|member|bss_type
r_int
r_char
id|bss_type
suffix:semicolon
DECL|member|bssid
r_int
r_char
id|bssid
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|phy_pset
r_int
r_char
id|phy_pset
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cf_pset
r_int
r_char
id|cf_pset
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ibss_pset
r_int
r_char
id|ibss_pset
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bss_basic_rate_set
r_int
r_char
id|bss_basic_rate_set
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|rssi
r_int
r_char
id|rssi
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_start_confirm
r_struct
id|wl3501_start_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_md_req
r_struct
id|wl3501_md_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|routing
r_int
r_char
id|routing
suffix:semicolon
DECL|member|data
id|u16
id|data
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|pri
r_int
r_char
id|pri
suffix:semicolon
DECL|member|service_class
r_int
r_char
id|service_class
suffix:semicolon
DECL|member|daddr
r_int
r_char
id|daddr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|saddr
r_int
r_char
id|saddr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_md_ind
r_struct
id|wl3501_md_ind
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|routing
r_int
r_char
id|routing
suffix:semicolon
DECL|member|data
id|u16
id|data
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|reception
r_int
r_char
id|reception
suffix:semicolon
DECL|member|pri
r_int
r_char
id|pri
suffix:semicolon
DECL|member|service_class
r_int
r_char
id|service_class
suffix:semicolon
DECL|member|daddr
r_int
r_char
id|daddr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|saddr
r_int
r_char
id|saddr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_md_confirm
r_struct
id|wl3501_md_confirm
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|data
id|u16
id|data
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|pri
r_int
r_char
id|pri
suffix:semicolon
DECL|member|service_class
r_int
r_char
id|service_class
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_resync_req
r_struct
id|wl3501_resync_req
(brace
DECL|member|next_blk
id|u16
id|next_blk
suffix:semicolon
DECL|member|sig_id
r_int
r_char
id|sig_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For rough constant delay */
DECL|macro|WL3501_NOPLOOP
mdefine_line|#define WL3501_NOPLOOP(n) { int x = 0; while (x++ &lt; n) slow_down_io(); }
multiline_comment|/* Ethernet MAC addr, BSS_ID, or ESS_ID */
multiline_comment|/* With this, we may simply write &quot;x=y;&quot; instead of &quot;memcpy(x, y, 6);&quot; */
multiline_comment|/* It&squot;s more efficiency with compiler&squot;s optimization and more clearly  */
DECL|struct|wl3501_mac_addr
r_struct
id|wl3501_mac_addr
(brace
DECL|member|b0
DECL|member|b1
DECL|member|b2
DECL|member|b3
DECL|member|b4
DECL|member|b5
id|u8
id|b0
comma
id|b1
comma
id|b2
comma
id|b3
comma
id|b4
comma
id|b5
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Definitions for supporting clone adapters. */
multiline_comment|/* System Interface Registers (SIR space) */
DECL|macro|WL3501_NIC_GCR
mdefine_line|#define WL3501_NIC_GCR ((u8)0x00)&t;/* SIR0 - General Conf Register */
DECL|macro|WL3501_NIC_BSS
mdefine_line|#define WL3501_NIC_BSS ((u8)0x01)&t;/* SIR1 - Bank Switching Select Reg */
DECL|macro|WL3501_NIC_LMAL
mdefine_line|#define WL3501_NIC_LMAL ((u8)0x02)&t;/* SIR2 - Local Mem addr Reg [7:0] */
DECL|macro|WL3501_NIC_LMAH
mdefine_line|#define WL3501_NIC_LMAH ((u8)0x03)&t;/* SIR3 - Local Mem addr Reg [14:8] */
DECL|macro|WL3501_NIC_IODPA
mdefine_line|#define WL3501_NIC_IODPA ((u8)0x04)&t;/* SIR4 - I/O Data Port A */
DECL|macro|WL3501_NIC_IODPB
mdefine_line|#define WL3501_NIC_IODPB ((u8)0x05)&t;/* SIR5 - I/O Data Port B */
DECL|macro|WL3501_NIC_IODPC
mdefine_line|#define WL3501_NIC_IODPC ((u8)0x06)&t;/* SIR6 - I/O Data Port C */
DECL|macro|WL3501_NIC_IODPD
mdefine_line|#define WL3501_NIC_IODPD ((u8)0x07)&t;/* SIR7 - I/O Data Port D */
multiline_comment|/* Bits in GCR */
DECL|macro|WL3501_GCR_SWRESET
mdefine_line|#define WL3501_GCR_SWRESET ((u8)0x80)
DECL|macro|WL3501_GCR_CORESET
mdefine_line|#define WL3501_GCR_CORESET ((u8)0x40)
DECL|macro|WL3501_GCR_DISPWDN
mdefine_line|#define WL3501_GCR_DISPWDN ((u8)0x20)
DECL|macro|WL3501_GCR_ECWAIT
mdefine_line|#define WL3501_GCR_ECWAIT  ((u8)0x10)
DECL|macro|WL3501_GCR_ECINT
mdefine_line|#define WL3501_GCR_ECINT   ((u8)0x08)
DECL|macro|WL3501_GCR_INT2EC
mdefine_line|#define WL3501_GCR_INT2EC  ((u8)0x04)
DECL|macro|WL3501_GCR_ENECINT
mdefine_line|#define WL3501_GCR_ENECINT ((u8)0x02)
DECL|macro|WL3501_GCR_DAM
mdefine_line|#define WL3501_GCR_DAM     ((u8)0x01)
multiline_comment|/* Bits in BSS (Bank Switching Select Register) */
DECL|macro|WL3501_BSS_FPAGE0
mdefine_line|#define WL3501_BSS_FPAGE0 ((u8)0x20)&t;/* Flash memory page0 */
DECL|macro|WL3501_BSS_FPAGE1
mdefine_line|#define WL3501_BSS_FPAGE1 ((u8)0x28)
DECL|macro|WL3501_BSS_FPAGE2
mdefine_line|#define WL3501_BSS_FPAGE2 ((u8)0x30)
DECL|macro|WL3501_BSS_FPAGE3
mdefine_line|#define WL3501_BSS_FPAGE3 ((u8)0x38)
DECL|macro|WL3501_BSS_SPAGE0
mdefine_line|#define WL3501_BSS_SPAGE0 ((u8)0x00)&t;/* SRAM page0 */
DECL|macro|WL3501_BSS_SPAGE1
mdefine_line|#define WL3501_BSS_SPAGE1 ((u8)0x08)
DECL|macro|WL3501_BSS_SPAGE2
mdefine_line|#define WL3501_BSS_SPAGE2 ((u8)0x10)
DECL|macro|WL3501_BSS_SPAGE3
mdefine_line|#define WL3501_BSS_SPAGE3 ((u8)0x18)
multiline_comment|/* Define Driver Interface */
multiline_comment|/* Refer IEEE 802.11 */
multiline_comment|/* Tx packet header, include PLCP and MPDU */
multiline_comment|/* Tx PLCP Header */
DECL|struct|wl3501_80211_tx_plcp_hdr
r_struct
id|wl3501_80211_tx_plcp_hdr
(brace
DECL|member|sync
id|u8
id|sync
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sfd
id|u16
id|sfd
suffix:semicolon
DECL|member|signal
id|u8
id|signal
suffix:semicolon
DECL|member|service
id|u8
id|service
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|crc16
id|u16
id|crc16
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Data Frame MAC Header (IEEE 802.11)&n; */
DECL|struct|wl3501_80211_data_mac_hdr
r_struct
id|wl3501_80211_data_mac_hdr
(brace
DECL|member|frame_ctrl
id|u16
id|frame_ctrl
suffix:semicolon
DECL|member|duration_id
id|u16
id|duration_id
suffix:semicolon
DECL|member|addr1
r_struct
id|wl3501_mac_addr
id|addr1
suffix:semicolon
DECL|member|addr2
r_struct
id|wl3501_mac_addr
id|addr2
suffix:semicolon
DECL|member|addr3
r_struct
id|wl3501_mac_addr
id|addr3
suffix:semicolon
DECL|member|seq_ctrl
id|u16
id|seq_ctrl
suffix:semicolon
DECL|member|addr4
r_struct
id|wl3501_mac_addr
id|addr4
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|wl3501_80211_tx_hdr
r_struct
id|wl3501_80211_tx_hdr
(brace
DECL|member|pclp_hdr
r_struct
id|wl3501_80211_tx_plcp_hdr
id|pclp_hdr
suffix:semicolon
DECL|member|mac_hdr
r_struct
id|wl3501_80211_data_mac_hdr
id|mac_hdr
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;   Reserve the beginning Tx space for descriptor use.&n;&n;   TxBlockOffset --&gt;&t;*----*----*----*----* &bslash;&n;&t;(TxFreeDesc)&t;|  0 |  1 |  2 |  3 |  &bslash;&n;&t;&t;&t;|  4 |  5 |  6 |  7 |   |&n;&t;&t;&t;|  8 |  9 | 10 | 11 |   TX_DESC * 20&n;&t;&t;&t;| 12 | 13 | 14 | 15 |   |&n;&t;&t;&t;| 16 | 17 | 18 | 19 |  /&n;   TxBufferBegin --&gt;&t;*----*----*----*----* /&n;   (TxBufferHead)&t;| &t;&t;    |&n;   (TxBufferTail)&t;| &t;&t;    |&n;&t;&t;&t;|    Send Buffer    |&n;&t;&t;&t;| &t;&t;    |&n;&t;&t;&t;|&t;&t;    |&n;&t;&t;&t;*-------------------*&n;   TxBufferEnd    -------------------------/&n;&n;*/
DECL|struct|wl3501_card
r_struct
id|wl3501_card
(brace
DECL|member|base_addr
r_int
id|base_addr
suffix:semicolon
DECL|member|mac_addr
r_struct
id|wl3501_mac_addr
id|mac_addr
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|sig_get_confirm
r_struct
id|wl3501_get_confirm
id|sig_get_confirm
suffix:semicolon
DECL|member|tx_buffer_size
id|u16
id|tx_buffer_size
suffix:semicolon
DECL|member|tx_buffer_head
id|u16
id|tx_buffer_head
suffix:semicolon
DECL|member|tx_buffer_tail
id|u16
id|tx_buffer_tail
suffix:semicolon
DECL|member|tx_buffer_cnt
id|u16
id|tx_buffer_cnt
suffix:semicolon
DECL|member|esbq_req_start
id|u16
id|esbq_req_start
suffix:semicolon
DECL|member|esbq_req_end
id|u16
id|esbq_req_end
suffix:semicolon
DECL|member|esbq_req_head
id|u16
id|esbq_req_head
suffix:semicolon
DECL|member|esbq_req_tail
id|u16
id|esbq_req_tail
suffix:semicolon
DECL|member|esbq_confirm_start
id|u16
id|esbq_confirm_start
suffix:semicolon
DECL|member|esbq_confirm_end
id|u16
id|esbq_confirm_end
suffix:semicolon
DECL|member|esbq_confirm
id|u16
id|esbq_confirm
suffix:semicolon
DECL|member|llc_type
id|u8
id|llc_type
suffix:semicolon
DECL|member|essid
id|u8
id|essid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|bssid
r_struct
id|wl3501_mac_addr
id|bssid
suffix:semicolon
DECL|member|ether_type
r_int
id|ether_type
suffix:semicolon
DECL|member|net_type
r_int
id|net_type
suffix:semicolon
DECL|member|keep_essid
id|u8
id|keep_essid
(braket
id|WL3501_ESSID_MAX_LEN
)braket
suffix:semicolon
DECL|member|nick
r_int
r_char
id|nick
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|card_name
r_int
r_char
id|card_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|firmware_date
r_int
r_char
id|firmware_date
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|chan
id|u8
id|chan
suffix:semicolon
DECL|member|def_chan
id|u8
id|def_chan
suffix:semicolon
DECL|member|cap_info
id|u8
id|cap_info
suffix:semicolon
DECL|member|start_seg
id|u16
id|start_seg
suffix:semicolon
DECL|member|bss_cnt
id|u16
id|bss_cnt
suffix:semicolon
DECL|member|join_sta_bss
id|u16
id|join_sta_bss
suffix:semicolon
DECL|member|rssi
r_int
r_char
id|rssi
suffix:semicolon
DECL|member|adhoc_times
id|u8
id|adhoc_times
suffix:semicolon
DECL|member|freq_domain
id|u8
id|freq_domain
suffix:semicolon
DECL|member|version
id|u8
id|version
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bss_set
r_struct
id|wl3501_scan_confirm
id|bss_set
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|wstats
r_struct
id|iw_statistics
id|wstats
suffix:semicolon
DECL|member|spy_data
r_struct
id|iw_spy_data
id|spy_data
suffix:semicolon
DECL|member|node
r_struct
id|dev_node_t
id|node
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
