macro_line|#ifndef __WL3501_H__
DECL|macro|__WL3501_H__
mdefine_line|#define __WL3501_H__
DECL|macro|WL3501_SLOW_DOWN_IO
mdefine_line|#define WL3501_SLOW_DOWN_IO __asm__ __volatile__(&quot;outb %al,$0x80&quot;)
multiline_comment|/* define for WLA 2.0 */
DECL|macro|WL3501_BLKSZ
mdefine_line|#define WL3501_BLKSZ 256
multiline_comment|/*&n; * ID for input Signals of DRIVER block&n; * bit[7-5] is block ID: 000&n; * bit[4-0] is signal ID&n;*/
DECL|macro|WL3501_Alarm
mdefine_line|#define WL3501_Alarm&t;&t;0x00
DECL|macro|WL3501_MdConfirm
mdefine_line|#define WL3501_MdConfirm&t;0x01
DECL|macro|WL3501_MdIndicate
mdefine_line|#define WL3501_MdIndicate&t;0x02
DECL|macro|WL3501_AssocConfirm
mdefine_line|#define WL3501_AssocConfirm&t;0x03
DECL|macro|WL3501_AssocIndicate
mdefine_line|#define WL3501_AssocIndicate&t;0x04
DECL|macro|WL3501_AutheConfirm
mdefine_line|#define WL3501_AutheConfirm&t;0x05
DECL|macro|WL3501_AutheIndicate
mdefine_line|#define WL3501_AutheIndicate&t;0x06
DECL|macro|WL3501_DeautheConfirm
mdefine_line|#define WL3501_DeautheConfirm&t;0x07
DECL|macro|WL3501_DeautheIndicate
mdefine_line|#define WL3501_DeautheIndicate &t;0x08
DECL|macro|WL3501_DisassocConfirm
mdefine_line|#define WL3501_DisassocConfirm &t;0x09
DECL|macro|WL3501_DisassocIndicate
mdefine_line|#define WL3501_DisassocIndicate&t;0x0A
DECL|macro|WL3501_GetConfirm
mdefine_line|#define WL3501_GetConfirm&t;0x0B
DECL|macro|WL3501_JoinConfirm
mdefine_line|#define WL3501_JoinConfirm &t;0x0C
DECL|macro|WL3501_PowermgtConfirm
mdefine_line|#define WL3501_PowermgtConfirm &t;0x0D
DECL|macro|WL3501_ReassocConfirm
mdefine_line|#define WL3501_ReassocConfirm&t;0x0E
DECL|macro|WL3501_ReassocIndicate
mdefine_line|#define WL3501_ReassocIndicate &t;0x0F
DECL|macro|WL3501_ScanConfirm
mdefine_line|#define WL3501_ScanConfirm &t;0x10
DECL|macro|WL3501_SetConfirm
mdefine_line|#define WL3501_SetConfirm&t;0x11
DECL|macro|WL3501_StartConfirm
mdefine_line|#define WL3501_StartConfirm&t;0x12
DECL|macro|WL3501_ResyncConfirm
mdefine_line|#define WL3501_ResyncConfirm&t;0x13
DECL|macro|WL3501_SiteConfirm
mdefine_line|#define WL3501_SiteConfirm &t;0x14
DECL|macro|WL3501_SaveConfirm
mdefine_line|#define WL3501_SaveConfirm &t;0x15
DECL|macro|WL3501_RFtestConfirm
mdefine_line|#define WL3501_RFtestConfirm&t;0x16
multiline_comment|/*&n; * ID for input Signals of MLME block&n; * bit[7-5] is block ID: 010&n; * bit[4-0] is signal ID&n; */
DECL|macro|WL3501_AssocRequest
mdefine_line|#define WL3501_AssocRequest&t;0x20
DECL|macro|WL3501_AutheRequest
mdefine_line|#define WL3501_AutheRequest&t;0x21
DECL|macro|WL3501_DeautheRequest
mdefine_line|#define WL3501_DeautheRequest&t;0x22
DECL|macro|WL3501_DisassocRequest
mdefine_line|#define WL3501_DisassocRequest&t;0x23
DECL|macro|WL3501_GetRequest
mdefine_line|#define WL3501_GetRequest&t;0x24
DECL|macro|WL3501_JoinRequest
mdefine_line|#define WL3501_JoinRequest&t;0x25
DECL|macro|WL3501_PowermgtRequest
mdefine_line|#define WL3501_PowermgtRequest&t;0x26
DECL|macro|WL3501_ReassocRequest
mdefine_line|#define WL3501_ReassocRequest&t;0x27
DECL|macro|WL3501_ScanRequest
mdefine_line|#define WL3501_ScanRequest&t;0x28
DECL|macro|WL3501_SetRequest
mdefine_line|#define WL3501_SetRequest&t;0x29
DECL|macro|WL3501_StartRequest
mdefine_line|#define WL3501_StartRequest&t;0x2A
DECL|macro|WL3501_MdRequest
mdefine_line|#define WL3501_MdRequest&t;0x2B
DECL|macro|WL3501_ResyncRequest
mdefine_line|#define WL3501_ResyncRequest&t;0x2C
DECL|macro|WL3501_SiteRequest
mdefine_line|#define WL3501_SiteRequest&t;0x2D
DECL|macro|WL3501_SaveRequest
mdefine_line|#define WL3501_SaveRequest&t;0x2E
DECL|macro|WL3501_RFtestRequest
mdefine_line|#define WL3501_RFtestRequest&t;0x2F
DECL|macro|WL3501_MmConfirm
mdefine_line|#define WL3501_MmConfirm&t;0x60
DECL|macro|WL3501_MmIndicate
mdefine_line|#define WL3501_MmIndicate&t;0x61
DECL|macro|WL3501_Infrastructure
mdefine_line|#define WL3501_Infrastructure&t;&t;0
DECL|macro|WL3501_Independent
mdefine_line|#define WL3501_Independent&t;&t;1
DECL|macro|WL3501_Any_bss
mdefine_line|#define WL3501_Any_bss&t;&t;&t;2
DECL|macro|WL3501_ActiveScan
mdefine_line|#define WL3501_ActiveScan&t;&t;0
DECL|macro|WL3501_PassiveScan
mdefine_line|#define WL3501_PassiveScan&t;&t;1
DECL|macro|WL3501_TxResult_Success
mdefine_line|#define WL3501_TxResult_Success&t;&t;0
DECL|macro|WL3501_TxResult_NoBss
mdefine_line|#define WL3501_TxResult_NoBss&t;&t;1
DECL|macro|WL3501_TxResult_retryLimit
mdefine_line|#define WL3501_TxResult_retryLimit&t;2
DECL|macro|WL3501_Open_System
mdefine_line|#define WL3501_Open_System&t;0
DECL|macro|WL3501_Share_Key
mdefine_line|#define WL3501_Share_Key&t;1
DECL|macro|EtherII
mdefine_line|#define EtherII     0
DECL|macro|Ether802_3e
mdefine_line|#define Ether802_3e 1
DECL|macro|Ether802_3f
mdefine_line|#define Ether802_3f 2
DECL|macro|WL3501_STATUS_SUCCESS
mdefine_line|#define WL3501_STATUS_SUCCESS    0
DECL|macro|WL3501_STATUS_INVALID
mdefine_line|#define WL3501_STATUS_INVALID    1
DECL|macro|WL3501_STATUS_TIMEOUT
mdefine_line|#define WL3501_STATUS_TIMEOUT    2
DECL|macro|WL3501_STATUS_REFUSED
mdefine_line|#define WL3501_STATUS_REFUSED    3
DECL|macro|WL3501_STATUS_MANYREQ
mdefine_line|#define WL3501_STATUS_MANYREQ    4
DECL|macro|WL3501_STATUS_ALREADYBSS
mdefine_line|#define WL3501_STATUS_ALREADYBSS 5
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
l_int|6
)braket
suffix:semicolon
DECL|member|addr2
r_int
r_char
id|addr2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|addr3
r_int
r_char
id|addr3
(braket
l_int|6
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
l_int|6
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
l_int|6
)braket
suffix:semicolon
DECL|member|addr2
r_int
r_char
id|addr2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|addr3
r_int
r_char
id|addr3
(braket
l_int|6
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
l_int|6
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
l_int|34
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
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_assoc_conf
r_struct
id|wl3501_assoc_conf
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
l_int|6
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
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_auth_conf
r_struct
id|wl3501_auth_conf
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
DECL|member|Type
id|u16
id|Type
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
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_get_conf
r_struct
id|wl3501_get_conf
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
l_int|6
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
l_int|34
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
DECL|struct|wl3501_join_conf
r_struct
id|wl3501_join_conf
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
l_int|6
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
l_int|34
)braket
suffix:semicolon
DECL|member|scan_type
r_int
r_char
id|scan_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_scan_conf
r_struct
id|wl3501_scan_conf
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
l_int|6
)braket
suffix:semicolon
DECL|member|ssid
r_int
r_char
id|ssid
(braket
l_int|34
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
DECL|struct|wl3501_start_conf
r_struct
id|wl3501_start_conf
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
l_int|6
)braket
suffix:semicolon
DECL|member|saddr
r_int
r_char
id|saddr
(braket
l_int|6
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
l_int|6
)braket
suffix:semicolon
DECL|member|saddr
r_int
r_char
id|saddr
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|wl3501_md_conf
r_struct
id|wl3501_md_conf
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
mdefine_line|#define WL3501_NOPLOOP(n) { int x = 0; while (x++ &lt; n) WL3501_SLOW_DOWN_IO; }
multiline_comment|/* Ethernet MAC addr, BSS_ID, or ESS_ID */
multiline_comment|/* With this, we may simply write &quot;x=y;&quot; instead of &quot;memcpy(x, y, 6);&quot; */
multiline_comment|/* It&squot;s more efficiency with compiler&squot;s optimization and more clearly  */
DECL|struct|wl3501_mac_addr
r_struct
id|wl3501_mac_addr
(brace
DECL|member|b0
id|u8
id|b0
suffix:semicolon
DECL|member|b1
id|u8
id|b1
suffix:semicolon
DECL|member|b2
id|u8
id|b2
suffix:semicolon
DECL|member|b3
id|u8
id|b3
suffix:semicolon
DECL|member|b4
id|u8
id|b4
suffix:semicolon
DECL|member|b5
id|u8
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
multiline_comment|/*&n; * Data Frame MAC Header (IEEE 802.11)&n; * FIXME: try to use ieee_802_11_header (see linux/802_11.h)&n; */
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
DECL|member|bssid
r_struct
id|wl3501_mac_addr
id|bssid
suffix:semicolon
DECL|member|llc_type
id|u8
id|llc_type
suffix:semicolon
DECL|member|net_type
id|u8
id|net_type
suffix:semicolon
DECL|member|essid
id|u8
id|essid
(braket
l_int|34
)braket
suffix:semicolon
DECL|member|keep_essid
id|u8
id|keep_essid
(braket
l_int|34
)braket
suffix:semicolon
DECL|member|ether_type
id|u8
id|ether_type
suffix:semicolon
DECL|member|chan
id|u8
id|chan
suffix:semicolon
DECL|member|def_chan
id|u8
id|def_chan
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
DECL|member|cap_info
id|u8
id|cap_info
suffix:semicolon
DECL|member|adhoc_times
id|u8
id|adhoc_times
suffix:semicolon
DECL|member|card_start
r_int
id|card_start
suffix:semicolon
DECL|member|bss_set
r_struct
id|wl3501_scan_conf
id|bss_set
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|driver_state
id|u8
id|driver_state
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
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * wl3501_ioctl_blk is put into ifreq.ifr_data which is a union (16 bytes)&n; * sizeof(wl3501_ioctl_blk) must be less than 16 bytes.&n; */
DECL|struct|wl3501_ioctl_blk
r_struct
id|wl3501_ioctl_blk
(brace
DECL|member|cmd
id|u16
id|cmd
suffix:semicolon
multiline_comment|/* Command to run */
DECL|member|len
id|u16
id|len
suffix:semicolon
multiline_comment|/* Length of the data buffer */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to the data buffer */
)brace
suffix:semicolon
DECL|struct|wl3501_ioctl_parm
r_struct
id|wl3501_ioctl_parm
(brace
DECL|member|def_chan
id|u8
id|def_chan
suffix:semicolon
DECL|member|chan
id|u8
id|chan
suffix:semicolon
DECL|member|net_type
id|u8
id|net_type
suffix:semicolon
DECL|member|essid
id|u8
id|essid
(braket
l_int|34
)braket
suffix:semicolon
DECL|member|keep_essid
id|u8
id|keep_essid
(braket
l_int|34
)braket
suffix:semicolon
DECL|member|version
id|u8
id|version
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|freq_domain
id|u8
id|freq_domain
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|WL3501_IOCTL_GET_PARAMETER
mdefine_line|#define WL3501_IOCTL_GET_PARAMETER   0&t;/* Get parameter */
DECL|macro|WL3501_IOCTL_SET_PARAMETER
mdefine_line|#define WL3501_IOCTL_SET_PARAMETER   1&t;/* Get parameter */
DECL|macro|WL3501_IOCTL_WRITE_FLASH
mdefine_line|#define WL3501_IOCTL_WRITE_FLASH     2&t;/* Write firmware into Flash ROM */
DECL|macro|WL3501_IOCTL_SET_RESET
mdefine_line|#define WL3501_IOCTL_SET_RESET       3&t;/* Reset the firmware */
macro_line|#endif&t;&t;&t;&t;/* __WL3501_H__ */
eof
