multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *&t;SMT 7.2 frame definitions&n; */
macro_line|#ifndef&t;_SMT_
DECL|macro|_SMT_
mdefine_line|#define _SMT_
multiline_comment|/* #define SMT5_10 */
DECL|macro|SMT6_10
mdefine_line|#define SMT6_10
DECL|macro|SMT7_20
mdefine_line|#define SMT7_20
DECL|macro|OPT_PMF
mdefine_line|#define&t;OPT_PMF&t;&t;/* if parameter management is supported */
DECL|macro|OPT_SRF
mdefine_line|#define&t;OPT_SRF&t;&t;/* if status report is supported */
multiline_comment|/*&n; * SMT frame version 5.1&n; */
DECL|macro|SMT_VID
mdefine_line|#define SMT_VID&t;0x0001&t;&t;&t;/* V 5.1 .. 6.1 */
DECL|macro|SMT_VID_2
mdefine_line|#define SMT_VID_2 0x0002&t;&t;/* V 7.2 */
DECL|struct|smt_sid
r_struct
id|smt_sid
(brace
DECL|member|sid_oem
id|u_char
id|sid_oem
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* implementation spec. */
DECL|member|sid_node
r_struct
id|fddi_addr
id|sid_node
suffix:semicolon
multiline_comment|/* node address */
)brace
suffix:semicolon
DECL|typedef|t_station_id
r_typedef
id|u_char
id|t_station_id
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*&n; * note on alignment :&n; * sizeof(struct smt_header) = 32&n; * all parameters are long aligned&n; * if struct smt_header starts at offset 0, all longs are aligned correctly&n; * (FC starts at offset 3)&n; */
DECL|struct|smt_header
id|_packed
r_struct
id|smt_header
(brace
DECL|member|smt_dest
r_struct
id|fddi_addr
id|smt_dest
suffix:semicolon
multiline_comment|/* destination address */
DECL|member|smt_source
r_struct
id|fddi_addr
id|smt_source
suffix:semicolon
multiline_comment|/* source address */
DECL|member|smt_class
id|u_char
id|smt_class
suffix:semicolon
multiline_comment|/* NIF, SIF ... */
DECL|member|smt_type
id|u_char
id|smt_type
suffix:semicolon
multiline_comment|/* req., response .. */
DECL|member|smt_version
id|u_short
id|smt_version
suffix:semicolon
multiline_comment|/* version id */
DECL|member|smt_tid
id|u_int
id|smt_tid
suffix:semicolon
multiline_comment|/* transaction ID */
DECL|member|smt_sid
r_struct
id|smt_sid
id|smt_sid
suffix:semicolon
multiline_comment|/* station ID */
DECL|member|smt_pad
id|u_short
id|smt_pad
suffix:semicolon
multiline_comment|/* pad with 0 */
DECL|member|smt_len
id|u_short
id|smt_len
suffix:semicolon
multiline_comment|/* length of info field */
)brace
suffix:semicolon
DECL|macro|SWAP_SMTHEADER
mdefine_line|#define SWAP_SMTHEADER&t;&quot;662sl8ss&quot;
macro_line|#if&t;0
multiline_comment|/*&n; * MAC FC values&n; */
mdefine_line|#define FC_SMT_INFO&t;0x41&t;&t;/* SMT info */
mdefine_line|#define FC_SMT_NSA&t;0x4f&t;&t;/* SMT Next Station Addressing */
macro_line|#endif
multiline_comment|/*&n; * type codes&n; */
DECL|macro|SMT_ANNOUNCE
mdefine_line|#define SMT_ANNOUNCE&t;0x01&t;&t;/* announcement */
DECL|macro|SMT_REQUEST
mdefine_line|#define SMT_REQUEST&t;0x02&t;&t;/* request */
DECL|macro|SMT_REPLY
mdefine_line|#define SMT_REPLY&t;0x03&t;&t;/* reply */
multiline_comment|/*&n; * class codes&n; */
DECL|macro|SMT_NIF
mdefine_line|#define SMT_NIF&t;&t;0x01&t;&t;/* neighbor information frames */
DECL|macro|SMT_SIF_CONFIG
mdefine_line|#define SMT_SIF_CONFIG&t;0x02&t;&t;/* station information configuration */
DECL|macro|SMT_SIF_OPER
mdefine_line|#define SMT_SIF_OPER&t;0x03&t;&t;/* station information operation */
DECL|macro|SMT_ECF
mdefine_line|#define SMT_ECF&t;&t;0x04&t;&t;/* echo frames */
DECL|macro|SMT_RAF
mdefine_line|#define SMT_RAF&t;&t;0x05&t;&t;/* resource allocation */
DECL|macro|SMT_RDF
mdefine_line|#define SMT_RDF&t;&t;0x06&t;&t;/* request denied */
DECL|macro|SMT_SRF
mdefine_line|#define SMT_SRF&t;&t;0x07&t;&t;/* status report */
DECL|macro|SMT_PMF_GET
mdefine_line|#define SMT_PMF_GET&t;0x08&t;&t;/* parameter management get */
DECL|macro|SMT_PMF_SET
mdefine_line|#define SMT_PMF_SET&t;0x09&t;&t;/* parameter management set */
DECL|macro|SMT_ESF
mdefine_line|#define SMT_ESF&t;&t;0xff&t;&t;/* extended service */
DECL|macro|SMT_MAX_ECHO_LEN
mdefine_line|#define SMT_MAX_ECHO_LEN&t;4458&t;/* max length of SMT Echo */
macro_line|#if&t;defined(CONC) || defined(CONC_II)
DECL|macro|SMT_TEST_ECHO_LEN
mdefine_line|#define SMT_TEST_ECHO_LEN&t;50&t;/* test length of SMT Echo */
macro_line|#else
DECL|macro|SMT_TEST_ECHO_LEN
mdefine_line|#define SMT_TEST_ECHO_LEN&t;SMT_MAX_ECHO_LEN&t;/* test length */
macro_line|#endif
DECL|macro|SMT_MAX_INFO_LEN
mdefine_line|#define SMT_MAX_INFO_LEN&t;(4352-20)&t;/* max length for SMT info */
multiline_comment|/*&n; * parameter types&n; */
DECL|struct|smt_para
r_struct
id|smt_para
(brace
DECL|member|p_type
id|u_short
id|p_type
suffix:semicolon
multiline_comment|/* type */
DECL|member|p_len
id|u_short
id|p_len
suffix:semicolon
multiline_comment|/* length of parameter */
)brace
suffix:semicolon
DECL|macro|PARA_LEN
mdefine_line|#define PARA_LEN&t;(sizeof(struct smt_para))
DECL|macro|SMTSETPARA
mdefine_line|#define SMTSETPARA(p,t)&t;&t;(p)-&gt;para.p_type = (t),&bslash;&n;&t;&t;&t;&t;(p)-&gt;para.p_len = sizeof(*(p)) - PARA_LEN
multiline_comment|/*&n; * P01 : Upstream Neighbor Address, UNA&n; */
DECL|macro|SMT_P_UNA
mdefine_line|#define SMT_P_UNA&t;0x0001&t;&t;/* upstream neighbor address */
DECL|macro|SWAP_SMT_P_UNA
mdefine_line|#define SWAP_SMT_P_UNA&t;&quot;s6&quot;
DECL|struct|smt_p_una
r_struct
id|smt_p_una
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|una_pad
id|u_short
id|una_pad
suffix:semicolon
DECL|member|una_node
r_struct
id|fddi_addr
id|una_node
suffix:semicolon
multiline_comment|/* node address, zero if unknown */
)brace
suffix:semicolon
multiline_comment|/*&n; * P02 : Station Descriptor&n; */
DECL|macro|SMT_P_SDE
mdefine_line|#define SMT_P_SDE&t;0x0002&t;&t;/* station descriptor */
DECL|macro|SWAP_SMT_P_SDE
mdefine_line|#define SWAP_SMT_P_SDE&t;&quot;1111&quot;
DECL|macro|SMT_SDE_STATION
mdefine_line|#define SMT_SDE_STATION&t;&t;0&t;/* end node */
DECL|macro|SMT_SDE_CONCENTRATOR
mdefine_line|#define SMT_SDE_CONCENTRATOR&t;1&t;/* concentrator */
DECL|struct|smt_p_sde
r_struct
id|smt_p_sde
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|sde_type
id|u_char
id|sde_type
suffix:semicolon
multiline_comment|/* station type */
DECL|member|sde_mac_count
id|u_char
id|sde_mac_count
suffix:semicolon
multiline_comment|/* number of MACs */
DECL|member|sde_non_master
id|u_char
id|sde_non_master
suffix:semicolon
multiline_comment|/* number of A,B or S ports */
DECL|member|sde_master
id|u_char
id|sde_master
suffix:semicolon
multiline_comment|/* number of S ports on conc. */
)brace
suffix:semicolon
multiline_comment|/*&n; * P03 : Station State&n; */
DECL|macro|SMT_P_STATE
mdefine_line|#define SMT_P_STATE&t;0x0003&t;&t;/* station state */
DECL|macro|SWAP_SMT_P_STATE
mdefine_line|#define SWAP_SMT_P_STATE&t;&quot;scc&quot;
DECL|struct|smt_p_state
r_struct
id|smt_p_state
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|st_pad
id|u_short
id|st_pad
suffix:semicolon
DECL|member|st_topology
id|u_char
id|st_topology
suffix:semicolon
multiline_comment|/* topology */
DECL|member|st_dupl_addr
id|u_char
id|st_dupl_addr
suffix:semicolon
multiline_comment|/* duplicate address detected */
)brace
suffix:semicolon
DECL|macro|SMT_ST_WRAPPED
mdefine_line|#define SMT_ST_WRAPPED&t;&t;(1&lt;&lt;0)&t;/* station wrapped */
DECL|macro|SMT_ST_UNATTACHED
mdefine_line|#define SMT_ST_UNATTACHED&t;(1&lt;&lt;1)&t;/* unattached concentrator */
DECL|macro|SMT_ST_TWISTED_A
mdefine_line|#define SMT_ST_TWISTED_A&t;(1&lt;&lt;2)&t;/* A-A connection, twisted ring */
DECL|macro|SMT_ST_TWISTED_B
mdefine_line|#define SMT_ST_TWISTED_B&t;(1&lt;&lt;3)&t;/* B-B connection, twisted ring */
DECL|macro|SMT_ST_ROOTED_S
mdefine_line|#define SMT_ST_ROOTED_S&t;&t;(1&lt;&lt;4)&t;/* rooted station */
DECL|macro|SMT_ST_SRF
mdefine_line|#define SMT_ST_SRF&t;&t;(1&lt;&lt;5)&t;/* SRF protocol supported */
DECL|macro|SMT_ST_SYNC_SERVICE
mdefine_line|#define SMT_ST_SYNC_SERVICE&t;(1&lt;&lt;6)&t;/* use synchronous bandwidth */
DECL|macro|SMT_ST_MY_DUPA
mdefine_line|#define SMT_ST_MY_DUPA&t;&t;(1&lt;&lt;0)&t;/* my station detected dupl. */
DECL|macro|SMT_ST_UNA_DUPA
mdefine_line|#define SMT_ST_UNA_DUPA&t;&t;(1&lt;&lt;1)&t;/* my UNA detected duplicate */
multiline_comment|/*&n; * P04 : timestamp&n; */
DECL|macro|SMT_P_TIMESTAMP
mdefine_line|#define SMT_P_TIMESTAMP&t;0x0004&t;&t;/* time stamp */
DECL|macro|SWAP_SMT_P_TIMESTAMP
mdefine_line|#define SWAP_SMT_P_TIMESTAMP&t;&quot;8&quot;
DECL|struct|smt_p_timestamp
r_struct
id|smt_p_timestamp
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|ts_time
id|u_char
id|ts_time
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* time, resolution 80nS, unique */
)brace
suffix:semicolon
multiline_comment|/*&n; * P05 : station policies&n; */
DECL|macro|SMT_P_POLICY
mdefine_line|#define SMT_P_POLICY&t;0x0005&t;&t;/* station policies */
DECL|macro|SWAP_SMT_P_POLICY
mdefine_line|#define SWAP_SMT_P_POLICY&t;&quot;ss&quot;
DECL|struct|smt_p_policy
r_struct
id|smt_p_policy
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|pl_config
id|u_short
id|pl_config
suffix:semicolon
DECL|member|pl_connect
id|u_short
id|pl_connect
suffix:semicolon
multiline_comment|/* bit string POLICY_AA ... */
)brace
suffix:semicolon
DECL|macro|SMT_PL_HOLD
mdefine_line|#define SMT_PL_HOLD&t;&t;1&t;/* hold policy supported (Dual MAC) */
multiline_comment|/*&n; * P06 : latency equivalent&n; */
DECL|macro|SMT_P_LATENCY
mdefine_line|#define SMT_P_LATENCY&t;0x0006&t;&t;/* latency */
DECL|macro|SWAP_SMT_P_LATENCY
mdefine_line|#define SWAP_SMT_P_LATENCY&t;&quot;ssss&quot;
multiline_comment|/*&n; * note: latency has two phy entries by definition&n; * for a SAS, the 2nd one is null&n; */
DECL|struct|smt_p_latency
r_struct
id|smt_p_latency
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|lt_phyout_idx1
id|u_short
id|lt_phyout_idx1
suffix:semicolon
multiline_comment|/* index */
DECL|member|lt_latency1
id|u_short
id|lt_latency1
suffix:semicolon
multiline_comment|/* latency , unit : byte clock */
DECL|member|lt_phyout_idx2
id|u_short
id|lt_phyout_idx2
suffix:semicolon
multiline_comment|/* 0 if SAS */
DECL|member|lt_latency2
id|u_short
id|lt_latency2
suffix:semicolon
multiline_comment|/* 0 if SAS */
)brace
suffix:semicolon
multiline_comment|/*&n; * P07 : MAC neighbors&n; */
DECL|macro|SMT_P_NEIGHBORS
mdefine_line|#define SMT_P_NEIGHBORS&t;0x0007&t;&t;/* MAC neighbor description */
DECL|macro|SWAP_SMT_P_NEIGHBORS
mdefine_line|#define SWAP_SMT_P_NEIGHBORS&t;&quot;ss66&quot;
DECL|struct|smt_p_neighbor
r_struct
id|smt_p_neighbor
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|nb_mib_index
id|u_short
id|nb_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|nb_mac_index
id|u_short
id|nb_mac_index
suffix:semicolon
multiline_comment|/* n+1 .. n+m, m = #MACs, n = #PHYs */
DECL|member|nb_una
r_struct
id|fddi_addr
id|nb_una
suffix:semicolon
multiline_comment|/* UNA , 0 for unknown */
DECL|member|nb_dna
r_struct
id|fddi_addr
id|nb_dna
suffix:semicolon
multiline_comment|/* DNA , 0 for unknown */
)brace
suffix:semicolon
multiline_comment|/*&n; * PHY record&n; */
DECL|macro|SMT_PHY_A
mdefine_line|#define SMT_PHY_A&t;0&t;&t;/* A port */
DECL|macro|SMT_PHY_B
mdefine_line|#define SMT_PHY_B&t;1&t;&t;/* B port */
DECL|macro|SMT_PHY_S
mdefine_line|#define SMT_PHY_S&t;2&t;&t;/* slave port */
DECL|macro|SMT_PHY_M
mdefine_line|#define SMT_PHY_M&t;3&t;&t;/* master port */
DECL|macro|SMT_CS_DISABLED
mdefine_line|#define SMT_CS_DISABLED&t;0&t;&t;/* connect state : disabled */
DECL|macro|SMT_CS_CONNECTING
mdefine_line|#define SMT_CS_CONNECTING&t;1&t;/* connect state : connecting */
DECL|macro|SMT_CS_STANDBY
mdefine_line|#define SMT_CS_STANDBY&t;2&t;&t;/* connect state : stand by */
DECL|macro|SMT_CS_ACTIVE
mdefine_line|#define SMT_CS_ACTIVE&t;3&t;&t;/* connect state : active */
DECL|macro|SMT_RM_NONE
mdefine_line|#define SMT_RM_NONE&t;0
DECL|macro|SMT_RM_MAC
mdefine_line|#define SMT_RM_MAC&t;1
DECL|struct|smt_phy_rec
r_struct
id|smt_phy_rec
(brace
DECL|member|phy_mib_index
id|u_short
id|phy_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|phy_type
id|u_char
id|phy_type
suffix:semicolon
multiline_comment|/* A/B/S/M */
DECL|member|phy_connect_state
id|u_char
id|phy_connect_state
suffix:semicolon
multiline_comment|/* disabled/connecting/active */
DECL|member|phy_remote_type
id|u_char
id|phy_remote_type
suffix:semicolon
multiline_comment|/* A/B/S/M */
DECL|member|phy_remote_mac
id|u_char
id|phy_remote_mac
suffix:semicolon
multiline_comment|/* none/remote */
DECL|member|phy_resource_idx
id|u_short
id|phy_resource_idx
suffix:semicolon
multiline_comment|/* 1 .. n */
)brace
suffix:semicolon
multiline_comment|/*&n; * MAC record&n; */
DECL|struct|smt_mac_rec
r_struct
id|smt_mac_rec
(brace
DECL|member|mac_addr
r_struct
id|fddi_addr
id|mac_addr
suffix:semicolon
multiline_comment|/* MAC address */
DECL|member|mac_resource_idx
id|u_short
id|mac_resource_idx
suffix:semicolon
multiline_comment|/* n+1 .. n+m */
)brace
suffix:semicolon
multiline_comment|/*&n; * P08 : path descriptors&n; * should be really an array ; however our environment has a fixed number of&n; * PHYs and MACs&n; */
DECL|macro|SMT_P_PATH
mdefine_line|#define SMT_P_PATH&t;0x0008&t;&t;&t;/* path descriptor */
DECL|macro|SWAP_SMT_P_PATH
mdefine_line|#define SWAP_SMT_P_PATH&t;&quot;[6s]&quot;
DECL|struct|smt_p_path
r_struct
id|smt_p_path
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|pd_phy
r_struct
id|smt_phy_rec
id|pd_phy
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* PHY A */
DECL|member|pd_mac
r_struct
id|smt_mac_rec
id|pd_mac
suffix:semicolon
multiline_comment|/* MAC record */
)brace
suffix:semicolon
multiline_comment|/*&n; * P09 : MAC status&n; */
DECL|macro|SMT_P_MAC_STATUS
mdefine_line|#define SMT_P_MAC_STATUS&t;0x0009&t;&t;/* MAC status */
DECL|macro|SWAP_SMT_P_MAC_STATUS
mdefine_line|#define SWAP_SMT_P_MAC_STATUS&t;&quot;sslllllllll&quot;
DECL|struct|smt_p_mac_status
r_struct
id|smt_p_mac_status
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|st_mib_index
id|u_short
id|st_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|st_mac_index
id|u_short
id|st_mac_index
suffix:semicolon
multiline_comment|/* n+1 .. n+m */
DECL|member|st_t_req
id|u_int
id|st_t_req
suffix:semicolon
multiline_comment|/* T_Req */
DECL|member|st_t_neg
id|u_int
id|st_t_neg
suffix:semicolon
multiline_comment|/* T_Neg */
DECL|member|st_t_max
id|u_int
id|st_t_max
suffix:semicolon
multiline_comment|/* T_Max */
DECL|member|st_tvx_value
id|u_int
id|st_tvx_value
suffix:semicolon
multiline_comment|/* TVX_Value */
DECL|member|st_t_min
id|u_int
id|st_t_min
suffix:semicolon
multiline_comment|/* T_Min */
DECL|member|st_sba
id|u_int
id|st_sba
suffix:semicolon
multiline_comment|/* synchr. bandwidth alloc */
DECL|member|st_frame_ct
id|u_int
id|st_frame_ct
suffix:semicolon
multiline_comment|/* frame counter */
DECL|member|st_error_ct
id|u_int
id|st_error_ct
suffix:semicolon
multiline_comment|/* error counter */
DECL|member|st_lost_ct
id|u_int
id|st_lost_ct
suffix:semicolon
multiline_comment|/* lost frames counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0A : PHY link error rate monitoring&n; */
DECL|macro|SMT_P_LEM
mdefine_line|#define SMT_P_LEM&t;0x000a&t;&t;/* link error monitor */
DECL|macro|SWAP_SMT_P_LEM
mdefine_line|#define SWAP_SMT_P_LEM&t;&quot;ssccccll&quot;
multiline_comment|/*&n; * units of lem_cutoff,lem_alarm,lem_estimate : 10**-x&n; */
DECL|struct|smt_p_lem
r_struct
id|smt_p_lem
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|lem_mib_index
id|u_short
id|lem_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|lem_phy_index
id|u_short
id|lem_phy_index
suffix:semicolon
multiline_comment|/* 1 .. n */
DECL|member|lem_pad2
id|u_char
id|lem_pad2
suffix:semicolon
multiline_comment|/* be nice and make it even . */
DECL|member|lem_cutoff
id|u_char
id|lem_cutoff
suffix:semicolon
multiline_comment|/* 0x4 .. 0xf, default 0x7 */
DECL|member|lem_alarm
id|u_char
id|lem_alarm
suffix:semicolon
multiline_comment|/* 0x4 .. 0xf, default 0x8 */
DECL|member|lem_estimate
id|u_char
id|lem_estimate
suffix:semicolon
multiline_comment|/* 0x0 .. 0xff */
DECL|member|lem_reject_ct
id|u_int
id|lem_reject_ct
suffix:semicolon
multiline_comment|/* 0x00000000 .. 0xffffffff */
DECL|member|lem_ct
id|u_int
id|lem_ct
suffix:semicolon
multiline_comment|/* 0x00000000 .. 0xffffffff */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0B : MAC frame counters&n; */
DECL|macro|SMT_P_MAC_COUNTER
mdefine_line|#define SMT_P_MAC_COUNTER 0x000b&t;/* MAC frame counters */
DECL|macro|SWAP_SMT_P_MAC_COUNTER
mdefine_line|#define SWAP_SMT_P_MAC_COUNTER&t;&quot;ssll&quot;
DECL|struct|smt_p_mac_counter
r_struct
id|smt_p_mac_counter
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|mc_mib_index
id|u_short
id|mc_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|mc_index
id|u_short
id|mc_index
suffix:semicolon
multiline_comment|/* mac index */
DECL|member|mc_receive_ct
id|u_int
id|mc_receive_ct
suffix:semicolon
multiline_comment|/* receive counter */
DECL|member|mc_transmit_ct
id|u_int
id|mc_transmit_ct
suffix:semicolon
multiline_comment|/* transmit counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0C : MAC frame not copied counter&n; */
DECL|macro|SMT_P_MAC_FNC
mdefine_line|#define SMT_P_MAC_FNC&t;0x000c&t;&t;/* MAC frame not copied counter */
DECL|macro|SWAP_SMT_P_MAC_FNC
mdefine_line|#define SWAP_SMT_P_MAC_FNC&t;&quot;ssl&quot;
DECL|struct|smt_p_mac_fnc
r_struct
id|smt_p_mac_fnc
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|nc_mib_index
id|u_short
id|nc_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|nc_index
id|u_short
id|nc_index
suffix:semicolon
multiline_comment|/* mac index */
DECL|member|nc_counter
id|u_int
id|nc_counter
suffix:semicolon
multiline_comment|/* not copied counter */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0D : MAC priority values&n; */
DECL|macro|SMT_P_PRIORITY
mdefine_line|#define SMT_P_PRIORITY&t;0x000d&t;&t;/* MAC priority values */
DECL|macro|SWAP_SMT_P_PRIORITY
mdefine_line|#define SWAP_SMT_P_PRIORITY&t;&quot;ssl&quot;
DECL|struct|smt_p_priority
r_struct
id|smt_p_priority
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|pr_mib_index
id|u_short
id|pr_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|pr_index
id|u_short
id|pr_index
suffix:semicolon
multiline_comment|/* mac index */
DECL|member|pr_priority
id|u_int
id|pr_priority
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* priority values */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0E : PHY elasticity buffer status&n; */
DECL|macro|SMT_P_EB
mdefine_line|#define SMT_P_EB&t;0x000e&t;&t;/* PHY EB status */
DECL|macro|SWAP_SMT_P_EB
mdefine_line|#define SWAP_SMT_P_EB&t;&quot;ssl&quot;
DECL|struct|smt_p_eb
r_struct
id|smt_p_eb
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|eb_mib_index
id|u_short
id|eb_mib_index
suffix:semicolon
multiline_comment|/* MIB index */
DECL|member|eb_index
id|u_short
id|eb_index
suffix:semicolon
multiline_comment|/* phy index */
DECL|member|eb_error_ct
id|u_int
id|eb_error_ct
suffix:semicolon
multiline_comment|/* # of eb overflows */
)brace
suffix:semicolon
multiline_comment|/*&n; * P0F : manufacturer field&n; */
DECL|macro|SMT_P_MANUFACTURER
mdefine_line|#define SMT_P_MANUFACTURER&t;0x000f&t;/* manufacturer field */
DECL|macro|SWAP_SMT_P_MANUFACTURER
mdefine_line|#define SWAP_SMT_P_MANUFACTURER&t;&quot;&quot;
DECL|struct|smp_p_manufacturer
r_struct
id|smp_p_manufacturer
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|mf_data
id|u_char
id|mf_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* OUI + arbitrary data */
)brace
suffix:semicolon
multiline_comment|/*&n; * P10 : user field&n; */
DECL|macro|SMT_P_USER
mdefine_line|#define SMT_P_USER&t;&t;0x0010&t;/* manufacturer field */
DECL|macro|SWAP_SMT_P_USER
mdefine_line|#define SWAP_SMT_P_USER&t;&quot;&quot;
DECL|struct|smp_p_user
r_struct
id|smp_p_user
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|us_data
id|u_char
id|us_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* arbitrary data */
)brace
suffix:semicolon
multiline_comment|/*&n; * P11 : echo data&n; */
DECL|macro|SMT_P_ECHODATA
mdefine_line|#define SMT_P_ECHODATA&t;0x0011&t;&t;/* echo data */
DECL|macro|SWAP_SMT_P_ECHODATA
mdefine_line|#define SWAP_SMT_P_ECHODATA&t;&quot;&quot;
DECL|struct|smt_p_echo
r_struct
id|smt_p_echo
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|ec_data
id|u_char
id|ec_data
(braket
id|SMT_MAX_ECHO_LEN
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* echo data */
)brace
suffix:semicolon
multiline_comment|/*&n; * P12 : reason code&n; */
DECL|macro|SMT_P_REASON
mdefine_line|#define SMT_P_REASON&t;0x0012&t;&t;/* reason code */
DECL|macro|SWAP_SMT_P_REASON
mdefine_line|#define SWAP_SMT_P_REASON&t;&quot;l&quot;
DECL|struct|smt_p_reason
r_struct
id|smt_p_reason
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|rdf_reason
id|u_int
id|rdf_reason
suffix:semicolon
multiline_comment|/* CLASS/VERSION */
)brace
suffix:semicolon
DECL|macro|SMT_RDF_CLASS
mdefine_line|#define SMT_RDF_CLASS&t;0x00000001&t;/* class not supported */
DECL|macro|SMT_RDF_VERSION
mdefine_line|#define SMT_RDF_VERSION&t;0x00000002&t;/* version not supported */
DECL|macro|SMT_RDF_SUCCESS
mdefine_line|#define SMT_RDF_SUCCESS&t;0x00000003&t;/* success (PMF) */
DECL|macro|SMT_RDF_BADSET
mdefine_line|#define SMT_RDF_BADSET&t;0x00000004&t;/* bad set count (PMF) */
DECL|macro|SMT_RDF_ILLEGAL
mdefine_line|#define SMT_RDF_ILLEGAL 0x00000005&t;/* read only (PMF) */
DECL|macro|SMT_RDF_NOPARAM
mdefine_line|#define SMT_RDF_NOPARAM&t;0x6&t;&t;/* paramter not supported (PMF) */
DECL|macro|SMT_RDF_RANGE
mdefine_line|#define SMT_RDF_RANGE&t;0x8&t;&t;/* out of range */
DECL|macro|SMT_RDF_AUTHOR
mdefine_line|#define SMT_RDF_AUTHOR&t;0x9&t;&t;/* not autohorized */
DECL|macro|SMT_RDF_LENGTH
mdefine_line|#define SMT_RDF_LENGTH&t;0x0a&t;&t;/* length error */
DECL|macro|SMT_RDF_TOOLONG
mdefine_line|#define SMT_RDF_TOOLONG&t;0x0b&t;&t;/* length error */
DECL|macro|SMT_RDF_SBA
mdefine_line|#define SMT_RDF_SBA&t;0x0d&t;&t;/* SBA denied */
multiline_comment|/*&n; * P13 : refused frame beginning&n; */
DECL|macro|SMT_P_REFUSED
mdefine_line|#define SMT_P_REFUSED&t;0x0013&t;&t;/* refused frame beginning */
DECL|macro|SWAP_SMT_P_REFUSED
mdefine_line|#define SWAP_SMT_P_REFUSED&t;&quot;l&quot;
DECL|struct|smt_p_refused
r_struct
id|smt_p_refused
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|ref_fc
id|u_int
id|ref_fc
suffix:semicolon
multiline_comment|/* 3 bytes 0 + FC */
DECL|member|ref_header
r_struct
id|smt_header
id|ref_header
suffix:semicolon
multiline_comment|/* refused header */
)brace
suffix:semicolon
multiline_comment|/*&n; * P14 : supported SMT versions&n; */
DECL|macro|SMT_P_VERSION
mdefine_line|#define SMT_P_VERSION&t;0x0014&t;&t;/* SMT supported versions */
DECL|macro|SWAP_SMT_P_VERSION
mdefine_line|#define SWAP_SMT_P_VERSION&t;&quot;sccss&quot;
DECL|struct|smt_p_version
r_struct
id|smt_p_version
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|v_pad
id|u_short
id|v_pad
suffix:semicolon
DECL|member|v_n
id|u_char
id|v_n
suffix:semicolon
multiline_comment|/* 1 .. 0xff, #versions */
DECL|member|v_index
id|u_char
id|v_index
suffix:semicolon
multiline_comment|/* 1 .. 0xff, index of op. v. */
DECL|member|v_version
id|u_short
id|v_version
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* list of min. 1 version */
DECL|member|v_pad2
id|u_short
id|v_pad2
suffix:semicolon
multiline_comment|/* pad if necessary */
)brace
suffix:semicolon
multiline_comment|/*&n; * P15 : Resource Type&n; */
DECL|macro|SWAP_SMT_P0015
mdefine_line|#define&t;SWAP_SMT_P0015&t;&t;&quot;l&quot;
DECL|struct|smt_p_0015
r_struct
id|smt_p_0015
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|res_type
id|u_int
id|res_type
suffix:semicolon
multiline_comment|/* recsource type */
)brace
suffix:semicolon
DECL|macro|SYNC_BW
mdefine_line|#define&t;SYNC_BW&t;&t;0x00000001L&t;/* Synchronous Bandwidth */
multiline_comment|/*&n; * P16 : SBA Command&n; */
DECL|macro|SWAP_SMT_P0016
mdefine_line|#define&t;SWAP_SMT_P0016&t;&t;&quot;l&quot;
DECL|struct|smt_p_0016
r_struct
id|smt_p_0016
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|sba_cmd
id|u_int
id|sba_cmd
suffix:semicolon
multiline_comment|/* command for the SBA */
)brace
suffix:semicolon
DECL|macro|REQUEST_ALLOCATION
mdefine_line|#define&t;REQUEST_ALLOCATION&t;0x1&t;/* req allocation of sync bandwidth */
DECL|macro|REPORT_ALLOCATION
mdefine_line|#define&t;REPORT_ALLOCATION&t;0x2&t;/* rep of sync bandwidth allocation */
DECL|macro|CHANGE_ALLOCATION
mdefine_line|#define&t;CHANGE_ALLOCATION&t;0x3&t;/* forces a station using sync band-*/
multiline_comment|/* width to change its current allo-*/
multiline_comment|/* cation */
multiline_comment|/*&n; * P17 : SBA Payload Request&n; */
DECL|macro|SWAP_SMT_P0017
mdefine_line|#define&t;SWAP_SMT_P0017&t;&t;&quot;l&quot;
DECL|struct|smt_p_0017
r_struct
id|smt_p_0017
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|sba_pl_req
r_int
id|sba_pl_req
suffix:semicolon
multiline_comment|/* total sync bandwidth measured in */
)brace
suffix:semicolon
multiline_comment|/* bytes per 125 us */
multiline_comment|/*&n; * P18 : SBA Overhead Request&n; */
DECL|macro|SWAP_SMT_P0018
mdefine_line|#define&t;SWAP_SMT_P0018&t;&t;&quot;l&quot;
DECL|struct|smt_p_0018
r_struct
id|smt_p_0018
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|sba_ov_req
r_int
id|sba_ov_req
suffix:semicolon
multiline_comment|/* total sync bandwidth req for overhead*/
)brace
suffix:semicolon
multiline_comment|/* measuered in bytes per T_Neg */
multiline_comment|/*&n; * P19 : SBA Allocation Address&n; */
DECL|macro|SWAP_SMT_P0019
mdefine_line|#define&t;SWAP_SMT_P0019&t;&t;&quot;s6&quot;
DECL|struct|smt_p_0019
r_struct
id|smt_p_0019
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|sba_pad
id|u_short
id|sba_pad
suffix:semicolon
DECL|member|alloc_addr
r_struct
id|fddi_addr
id|alloc_addr
suffix:semicolon
multiline_comment|/* Allocation Address */
)brace
suffix:semicolon
multiline_comment|/*&n; * P1A : SBA Category&n; */
DECL|macro|SWAP_SMT_P001A
mdefine_line|#define&t;SWAP_SMT_P001A&t;&t;&quot;l&quot;
DECL|struct|smt_p_001a
r_struct
id|smt_p_001a
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|category
id|u_int
id|category
suffix:semicolon
multiline_comment|/* Allocator defined classification */
)brace
suffix:semicolon
multiline_comment|/*&n; * P1B : Maximum T_Neg&n; */
DECL|macro|SWAP_SMT_P001B
mdefine_line|#define&t;SWAP_SMT_P001B&t;&t;&quot;l&quot;
DECL|struct|smt_p_001b
r_struct
id|smt_p_001b
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|max_t_neg
id|u_int
id|max_t_neg
suffix:semicolon
multiline_comment|/* longest T_NEG for the sync service*/
)brace
suffix:semicolon
multiline_comment|/*&n; * P1C : Minimum SBA Segment Size&n; */
DECL|macro|SWAP_SMT_P001C
mdefine_line|#define&t;SWAP_SMT_P001C&t;&t;&quot;l&quot;
DECL|struct|smt_p_001c
r_struct
id|smt_p_001c
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|min_seg_siz
id|u_int
id|min_seg_siz
suffix:semicolon
multiline_comment|/* smallest number of bytes per frame*/
)brace
suffix:semicolon
multiline_comment|/*&n; * P1D : SBA Allocatable&n; */
DECL|macro|SWAP_SMT_P001D
mdefine_line|#define&t;SWAP_SMT_P001D&t;&t;&quot;l&quot;
DECL|struct|smt_p_001d
r_struct
id|smt_p_001d
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|allocatable
id|u_int
id|allocatable
suffix:semicolon
multiline_comment|/* total sync bw available for alloc */
)brace
suffix:semicolon
multiline_comment|/*&n; * P20 0B : frame status capabilities&n; * NOTE: not in swap table, is used by smt.c AND PMF table&n; */
DECL|macro|SMT_P_FSC
mdefine_line|#define SMT_P_FSC&t;0x200b
multiline_comment|/* #define SWAP_SMT_P_FSC&t;&quot;ssss&quot; */
DECL|struct|smt_p_fsc
r_struct
id|smt_p_fsc
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|fsc_pad0
id|u_short
id|fsc_pad0
suffix:semicolon
DECL|member|fsc_mac_index
id|u_short
id|fsc_mac_index
suffix:semicolon
multiline_comment|/* mac index 1 .. ff */
DECL|member|fsc_pad1
id|u_short
id|fsc_pad1
suffix:semicolon
DECL|member|fsc_value
id|u_short
id|fsc_value
suffix:semicolon
multiline_comment|/* FSC_TYPE[0-2] */
)brace
suffix:semicolon
DECL|macro|FSC_TYPE0
mdefine_line|#define FSC_TYPE0&t;0&t;&t;/* &quot;normal&quot; node (A/C handling) */
DECL|macro|FSC_TYPE1
mdefine_line|#define FSC_TYPE1&t;1&t;&t;/* Special A/C indicator forwarding */
DECL|macro|FSC_TYPE2
mdefine_line|#define FSC_TYPE2&t;2&t;&t;/* Special A/C indicator forwarding */
multiline_comment|/*&n; * P00 21 : user defined authoriziation (see pmf.c)&n; */
DECL|macro|SMT_P_AUTHOR
mdefine_line|#define SMT_P_AUTHOR&t;0x0021
multiline_comment|/*&n; * notification parameters&n; */
DECL|macro|SWAP_SMT_P1048
mdefine_line|#define SWAP_SMT_P1048&t;&quot;ll&quot;
DECL|struct|smt_p_1048
r_struct
id|smt_p_1048
(brace
DECL|member|p1048_flag
id|u_int
id|p1048_flag
suffix:semicolon
DECL|member|p1048_cf_state
id|u_int
id|p1048_cf_state
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * NOTE: all 2xxx 3xxx and 4xxx must include the INDEX in the swap string,&n; *&t;even so the INDEX is NOT part of the struct.&n; *&t;INDEX is already swapped in pmf.c, format in string is &squot;4&squot;&n; */
DECL|macro|SWAP_SMT_P208C
mdefine_line|#define SWAP_SMT_P208C&t;&quot;4lss66&quot;
DECL|struct|smt_p_208c
r_struct
id|smt_p_208c
(brace
DECL|member|p208c_flag
id|u_int
id|p208c_flag
suffix:semicolon
DECL|member|p208c_pad
id|u_short
id|p208c_pad
suffix:semicolon
DECL|member|p208c_dupcondition
id|u_short
id|p208c_dupcondition
suffix:semicolon
DECL|member|p208c_fddilong
r_struct
id|fddi_addr
id|p208c_fddilong
suffix:semicolon
DECL|member|p208c_fddiunalong
r_struct
id|fddi_addr
id|p208c_fddiunalong
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P208D
mdefine_line|#define SWAP_SMT_P208D&t;&quot;4lllll&quot;
DECL|struct|smt_p_208d
r_struct
id|smt_p_208d
(brace
DECL|member|p208d_flag
id|u_int
id|p208d_flag
suffix:semicolon
DECL|member|p208d_frame_ct
id|u_int
id|p208d_frame_ct
suffix:semicolon
DECL|member|p208d_error_ct
id|u_int
id|p208d_error_ct
suffix:semicolon
DECL|member|p208d_lost_ct
id|u_int
id|p208d_lost_ct
suffix:semicolon
DECL|member|p208d_ratio
id|u_int
id|p208d_ratio
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P208E
mdefine_line|#define SWAP_SMT_P208E&t;&quot;4llll&quot;
DECL|struct|smt_p_208e
r_struct
id|smt_p_208e
(brace
DECL|member|p208e_flag
id|u_int
id|p208e_flag
suffix:semicolon
DECL|member|p208e_not_copied
id|u_int
id|p208e_not_copied
suffix:semicolon
DECL|member|p208e_copied
id|u_int
id|p208e_copied
suffix:semicolon
DECL|member|p208e_not_copied_ratio
id|u_int
id|p208e_not_copied_ratio
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P208F
mdefine_line|#define SWAP_SMT_P208F&t;&quot;4ll6666s6&quot;
DECL|struct|smt_p_208f
r_struct
id|smt_p_208f
(brace
DECL|member|p208f_multiple
id|u_int
id|p208f_multiple
suffix:semicolon
DECL|member|p208f_nacondition
id|u_int
id|p208f_nacondition
suffix:semicolon
DECL|member|p208f_old_una
r_struct
id|fddi_addr
id|p208f_old_una
suffix:semicolon
DECL|member|p208f_new_una
r_struct
id|fddi_addr
id|p208f_new_una
suffix:semicolon
DECL|member|p208f_old_dna
r_struct
id|fddi_addr
id|p208f_old_dna
suffix:semicolon
DECL|member|p208f_new_dna
r_struct
id|fddi_addr
id|p208f_new_dna
suffix:semicolon
DECL|member|p208f_curren_path
id|u_short
id|p208f_curren_path
suffix:semicolon
DECL|member|p208f_smt_address
r_struct
id|fddi_addr
id|p208f_smt_address
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P2090
mdefine_line|#define SWAP_SMT_P2090&t;&quot;4lssl&quot;
DECL|struct|smt_p_2090
r_struct
id|smt_p_2090
(brace
DECL|member|p2090_multiple
id|u_int
id|p2090_multiple
suffix:semicolon
DECL|member|p2090_availablepaths
id|u_short
id|p2090_availablepaths
suffix:semicolon
DECL|member|p2090_currentpath
id|u_short
id|p2090_currentpath
suffix:semicolon
DECL|member|p2090_requestedpaths
id|u_int
id|p2090_requestedpaths
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * NOTE:&n; * special kludge for parameters 320b,320f,3210&n; * these parameters are part of RAF frames&n; * RAF frames are parsed in SBA.C and must be swapped&n; * PMF.C has special code to avoid double swapping&n; */
macro_line|#ifdef&t;LITTLE_ENDIAN
DECL|macro|SBAPATHINDEX
mdefine_line|#define SBAPATHINDEX&t;(0x01000000L)
macro_line|#else
DECL|macro|SBAPATHINDEX
mdefine_line|#define SBAPATHINDEX&t;(0x01L)
macro_line|#endif
DECL|macro|SWAP_SMT_P320B
mdefine_line|#define&t;SWAP_SMT_P320B&t;&quot;42s&quot;
DECL|struct|smt_p_320b
r_struct
id|smt_p_320b
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|mib_index
id|u_int
id|mib_index
suffix:semicolon
DECL|member|path_pad
id|u_short
id|path_pad
suffix:semicolon
DECL|member|path_index
id|u_short
id|path_index
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P320F
mdefine_line|#define&t;SWAP_SMT_P320F&t;&quot;4l&quot;
DECL|struct|smt_p_320f
r_struct
id|smt_p_320f
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|mib_index
id|u_int
id|mib_index
suffix:semicolon
DECL|member|mib_payload
id|u_int
id|mib_payload
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P3210
mdefine_line|#define&t;SWAP_SMT_P3210&t;&quot;4l&quot;
DECL|struct|smt_p_3210
r_struct
id|smt_p_3210
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|mib_index
id|u_int
id|mib_index
suffix:semicolon
DECL|member|mib_overhead
id|u_int
id|mib_overhead
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P4050
mdefine_line|#define SWAP_SMT_P4050&t;&quot;4l1111ll&quot;
DECL|struct|smt_p_4050
r_struct
id|smt_p_4050
(brace
DECL|member|p4050_flag
id|u_int
id|p4050_flag
suffix:semicolon
DECL|member|p4050_pad
id|u_char
id|p4050_pad
suffix:semicolon
DECL|member|p4050_cutoff
id|u_char
id|p4050_cutoff
suffix:semicolon
DECL|member|p4050_alarm
id|u_char
id|p4050_alarm
suffix:semicolon
DECL|member|p4050_estimate
id|u_char
id|p4050_estimate
suffix:semicolon
DECL|member|p4050_reject_ct
id|u_int
id|p4050_reject_ct
suffix:semicolon
DECL|member|p4050_ct
id|u_int
id|p4050_ct
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P4051
mdefine_line|#define SWAP_SMT_P4051&t;&quot;4lssss&quot;
DECL|struct|smt_p_4051
r_struct
id|smt_p_4051
(brace
DECL|member|p4051_multiple
id|u_int
id|p4051_multiple
suffix:semicolon
DECL|member|p4051_porttype
id|u_short
id|p4051_porttype
suffix:semicolon
DECL|member|p4051_connectstate
id|u_short
id|p4051_connectstate
suffix:semicolon
DECL|member|p4051_pc_neighbor
id|u_short
id|p4051_pc_neighbor
suffix:semicolon
DECL|member|p4051_pc_withhold
id|u_short
id|p4051_pc_withhold
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P4052
mdefine_line|#define SWAP_SMT_P4052&t;&quot;4ll&quot;
DECL|struct|smt_p_4052
r_struct
id|smt_p_4052
(brace
DECL|member|p4052_flag
id|u_int
id|p4052_flag
suffix:semicolon
DECL|member|p4052_eberrorcount
id|u_int
id|p4052_eberrorcount
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SWAP_SMT_P4053
mdefine_line|#define SWAP_SMT_P4053&t;&quot;4lsslss&quot;
DECL|struct|smt_p_4053
r_struct
id|smt_p_4053
(brace
DECL|member|p4053_multiple
id|u_int
id|p4053_multiple
suffix:semicolon
DECL|member|p4053_availablepaths
id|u_short
id|p4053_availablepaths
suffix:semicolon
DECL|member|p4053_currentpath
id|u_short
id|p4053_currentpath
suffix:semicolon
DECL|member|p4053_requestedpaths
id|u_int
id|p4053_requestedpaths
suffix:semicolon
DECL|member|p4053_mytype
id|u_short
id|p4053_mytype
suffix:semicolon
DECL|member|p4053_neighbortype
id|u_short
id|p4053_neighbortype
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SMT_P_SETCOUNT
mdefine_line|#define SMT_P_SETCOUNT&t;0x1035
DECL|macro|SWAP_SMT_P_SETCOUNT
mdefine_line|#define SWAP_SMT_P_SETCOUNT&t;&quot;l8&quot;
DECL|struct|smt_p_setcount
r_struct
id|smt_p_setcount
(brace
DECL|member|para
r_struct
id|smt_para
id|para
suffix:semicolon
multiline_comment|/* generic parameter header */
DECL|member|count
id|u_int
id|count
suffix:semicolon
DECL|member|timestamp
id|u_char
id|timestamp
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SMT FRAMES&n; */
multiline_comment|/*&n; * NIF : neighbor information frames&n; */
DECL|struct|smt_nif
r_struct
id|smt_nif
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|una
r_struct
id|smt_p_una
id|una
suffix:semicolon
multiline_comment|/* UNA */
DECL|member|sde
r_struct
id|smt_p_sde
id|sde
suffix:semicolon
multiline_comment|/* station descriptor */
DECL|member|state
r_struct
id|smt_p_state
id|state
suffix:semicolon
multiline_comment|/* station state */
macro_line|#ifdef&t;SMT6_10
DECL|member|fsc
r_struct
id|smt_p_fsc
id|fsc
suffix:semicolon
multiline_comment|/* frame status cap. */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * SIF : station information frames&n; */
DECL|struct|smt_sif_config
r_struct
id|smt_sif_config
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|ts
r_struct
id|smt_p_timestamp
id|ts
suffix:semicolon
multiline_comment|/* time stamp */
DECL|member|sde
r_struct
id|smt_p_sde
id|sde
suffix:semicolon
multiline_comment|/* station descriptor */
DECL|member|version
r_struct
id|smt_p_version
id|version
suffix:semicolon
multiline_comment|/* supported versions */
DECL|member|state
r_struct
id|smt_p_state
id|state
suffix:semicolon
multiline_comment|/* station state */
DECL|member|policy
r_struct
id|smt_p_policy
id|policy
suffix:semicolon
multiline_comment|/* station policy */
DECL|member|latency
r_struct
id|smt_p_latency
id|latency
suffix:semicolon
multiline_comment|/* path latency */
DECL|member|neighbor
r_struct
id|smt_p_neighbor
id|neighbor
suffix:semicolon
multiline_comment|/* neighbors, we have only one*/
macro_line|#ifdef&t;OPT_PMF
DECL|member|setcount
r_struct
id|smt_p_setcount
id|setcount
suffix:semicolon
multiline_comment|/* Set Count mandatory */
macro_line|#endif
multiline_comment|/* WARNING : path MUST BE LAST FIELD !!! (see smt.c:smt_fill_path) */
DECL|member|path
r_struct
id|smt_p_path
id|path
suffix:semicolon
multiline_comment|/* path descriptor */
)brace
suffix:semicolon
DECL|macro|SIZEOF_SMT_SIF_CONFIG
mdefine_line|#define SIZEOF_SMT_SIF_CONFIG&t;(sizeof(struct smt_sif_config)- &bslash;&n;&t;&t;&t;&t; sizeof(struct smt_p_path))
DECL|struct|smt_sif_operation
r_struct
id|smt_sif_operation
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|ts
r_struct
id|smt_p_timestamp
id|ts
suffix:semicolon
multiline_comment|/* time stamp */
DECL|member|status
r_struct
id|smt_p_mac_status
id|status
suffix:semicolon
multiline_comment|/* mac status */
DECL|member|mc
r_struct
id|smt_p_mac_counter
id|mc
suffix:semicolon
multiline_comment|/* MAC counter */
DECL|member|fnc
r_struct
id|smt_p_mac_fnc
id|fnc
suffix:semicolon
multiline_comment|/* MAC frame not copied */
DECL|member|man
r_struct
id|smp_p_manufacturer
id|man
suffix:semicolon
multiline_comment|/* manufacturer field */
DECL|member|user
r_struct
id|smp_p_user
id|user
suffix:semicolon
multiline_comment|/* user field */
macro_line|#ifdef&t;OPT_PMF
DECL|member|setcount
r_struct
id|smt_p_setcount
id|setcount
suffix:semicolon
multiline_comment|/* Set Count mandatory */
macro_line|#endif
multiline_comment|/* must be last */
DECL|member|lem
r_struct
id|smt_p_lem
id|lem
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* phy lem status */
)brace
suffix:semicolon
DECL|macro|SIZEOF_SMT_SIF_OPERATION
mdefine_line|#define SIZEOF_SMT_SIF_OPERATION&t;(sizeof(struct smt_sif_operation)- &bslash;&n;&t;&t;&t;&t;&t; sizeof(struct smt_p_lem))
multiline_comment|/*&n; * ECF : echo frame&n; */
DECL|struct|smt_ecf
r_struct
id|smt_ecf
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|ec_echo
r_struct
id|smt_p_echo
id|ec_echo
suffix:semicolon
multiline_comment|/* echo parameter */
)brace
suffix:semicolon
DECL|macro|SMT_ECF_LEN
mdefine_line|#define SMT_ECF_LEN&t;(sizeof(struct smt_header)+sizeof(struct smt_para))
multiline_comment|/*&n; * RDF : request denied frame&n; */
DECL|struct|smt_rdf
r_struct
id|smt_rdf
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|reason
r_struct
id|smt_p_reason
id|reason
suffix:semicolon
multiline_comment|/* reason code */
DECL|member|version
r_struct
id|smt_p_version
id|version
suffix:semicolon
multiline_comment|/* supported versions */
DECL|member|refused
r_struct
id|smt_p_refused
id|refused
suffix:semicolon
multiline_comment|/* refused frame fragment */
)brace
suffix:semicolon
multiline_comment|/*&n; * SBA Request Allocation Responce Frame&n; */
DECL|struct|smt_sba_alc_res
r_struct
id|smt_sba_alc_res
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|s_type
r_struct
id|smt_p_0015
id|s_type
suffix:semicolon
multiline_comment|/* resource type */
DECL|member|cmd
r_struct
id|smt_p_0016
id|cmd
suffix:semicolon
multiline_comment|/* SBA command */
DECL|member|reason
r_struct
id|smt_p_reason
id|reason
suffix:semicolon
multiline_comment|/* reason code */
DECL|member|path
r_struct
id|smt_p_320b
id|path
suffix:semicolon
multiline_comment|/* path type */
DECL|member|payload
r_struct
id|smt_p_320f
id|payload
suffix:semicolon
multiline_comment|/* current SBA payload */
DECL|member|overhead
r_struct
id|smt_p_3210
id|overhead
suffix:semicolon
multiline_comment|/* current SBA overhead */
DECL|member|a_addr
r_struct
id|smt_p_0019
id|a_addr
suffix:semicolon
multiline_comment|/* Allocation Address */
DECL|member|cat
r_struct
id|smt_p_001a
id|cat
suffix:semicolon
multiline_comment|/* Category - from the request */
DECL|member|alloc
r_struct
id|smt_p_001d
id|alloc
suffix:semicolon
multiline_comment|/* SBA Allocatable */
)brace
suffix:semicolon
multiline_comment|/*&n; * SBA Request Allocation Request Frame&n; */
DECL|struct|smt_sba_alc_req
r_struct
id|smt_sba_alc_req
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|s_type
r_struct
id|smt_p_0015
id|s_type
suffix:semicolon
multiline_comment|/* resource type */
DECL|member|cmd
r_struct
id|smt_p_0016
id|cmd
suffix:semicolon
multiline_comment|/* SBA command */
DECL|member|path
r_struct
id|smt_p_320b
id|path
suffix:semicolon
multiline_comment|/* path type */
DECL|member|pl_req
r_struct
id|smt_p_0017
id|pl_req
suffix:semicolon
multiline_comment|/* requested payload */
DECL|member|ov_req
r_struct
id|smt_p_0018
id|ov_req
suffix:semicolon
multiline_comment|/* requested SBA overhead */
DECL|member|payload
r_struct
id|smt_p_320f
id|payload
suffix:semicolon
multiline_comment|/* current SBA payload */
DECL|member|overhead
r_struct
id|smt_p_3210
id|overhead
suffix:semicolon
multiline_comment|/* current SBA overhead */
DECL|member|a_addr
r_struct
id|smt_p_0019
id|a_addr
suffix:semicolon
multiline_comment|/* Allocation Address */
DECL|member|cat
r_struct
id|smt_p_001a
id|cat
suffix:semicolon
multiline_comment|/* Category - from the request */
DECL|member|tneg
r_struct
id|smt_p_001b
id|tneg
suffix:semicolon
multiline_comment|/* max T-NEG */
DECL|member|segm
r_struct
id|smt_p_001c
id|segm
suffix:semicolon
multiline_comment|/* minimum segment size */
)brace
suffix:semicolon
multiline_comment|/*&n; * SBA Change Allocation Request Frame&n; */
DECL|struct|smt_sba_chg
r_struct
id|smt_sba_chg
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|s_type
r_struct
id|smt_p_0015
id|s_type
suffix:semicolon
multiline_comment|/* resource type */
DECL|member|cmd
r_struct
id|smt_p_0016
id|cmd
suffix:semicolon
multiline_comment|/* SBA command */
DECL|member|path
r_struct
id|smt_p_320b
id|path
suffix:semicolon
multiline_comment|/* path type */
DECL|member|payload
r_struct
id|smt_p_320f
id|payload
suffix:semicolon
multiline_comment|/* current SBA payload */
DECL|member|overhead
r_struct
id|smt_p_3210
id|overhead
suffix:semicolon
multiline_comment|/* current SBA overhead */
DECL|member|cat
r_struct
id|smt_p_001a
id|cat
suffix:semicolon
multiline_comment|/* Category - from the request */
)brace
suffix:semicolon
multiline_comment|/*&n; * SBA Report Allocation Request Frame&n; */
DECL|struct|smt_sba_rep_req
r_struct
id|smt_sba_rep_req
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|s_type
r_struct
id|smt_p_0015
id|s_type
suffix:semicolon
multiline_comment|/* resource type */
DECL|member|cmd
r_struct
id|smt_p_0016
id|cmd
suffix:semicolon
multiline_comment|/* SBA command */
)brace
suffix:semicolon
multiline_comment|/*&n; * SBA Report Allocation Response Frame&n; */
DECL|struct|smt_sba_rep_res
r_struct
id|smt_sba_rep_res
(brace
DECL|member|smt
r_struct
id|smt_header
id|smt
suffix:semicolon
multiline_comment|/* generic header */
DECL|member|s_type
r_struct
id|smt_p_0015
id|s_type
suffix:semicolon
multiline_comment|/* resource type */
DECL|member|cmd
r_struct
id|smt_p_0016
id|cmd
suffix:semicolon
multiline_comment|/* SBA command */
DECL|member|path
r_struct
id|smt_p_320b
id|path
suffix:semicolon
multiline_comment|/* path type */
DECL|member|payload
r_struct
id|smt_p_320f
id|payload
suffix:semicolon
multiline_comment|/* current SBA payload */
DECL|member|overhead
r_struct
id|smt_p_3210
id|overhead
suffix:semicolon
multiline_comment|/* current SBA overhead */
)brace
suffix:semicolon
multiline_comment|/*&n; * actions&n; */
DECL|macro|SMT_STATION_ACTION
mdefine_line|#define SMT_STATION_ACTION&t;1
DECL|macro|SMT_STATION_ACTION_CONNECT
mdefine_line|#define SMT_STATION_ACTION_CONNECT&t;0
DECL|macro|SMT_STATION_ACTION_DISCONNECT
mdefine_line|#define SMT_STATION_ACTION_DISCONNECT&t;1
DECL|macro|SMT_STATION_ACTION_PATHTEST
mdefine_line|#define SMT_STATION_ACTION_PATHTEST&t;2
DECL|macro|SMT_STATION_ACTION_SELFTEST
mdefine_line|#define SMT_STATION_ACTION_SELFTEST&t;3
DECL|macro|SMT_STATION_ACTION_DISABLE_A
mdefine_line|#define SMT_STATION_ACTION_DISABLE_A&t;4
DECL|macro|SMT_STATION_ACTION_DISABLE_B
mdefine_line|#define SMT_STATION_ACTION_DISABLE_B&t;5
DECL|macro|SMT_STATION_ACTION_DISABLE_M
mdefine_line|#define SMT_STATION_ACTION_DISABLE_M&t;6
DECL|macro|SMT_PORT_ACTION
mdefine_line|#define SMT_PORT_ACTION&t;&t;2
DECL|macro|SMT_PORT_ACTION_MAINT
mdefine_line|#define SMT_PORT_ACTION_MAINT&t;0
DECL|macro|SMT_PORT_ACTION_ENABLE
mdefine_line|#define SMT_PORT_ACTION_ENABLE&t;1
DECL|macro|SMT_PORT_ACTION_DISABLE
mdefine_line|#define SMT_PORT_ACTION_DISABLE&t;2
DECL|macro|SMT_PORT_ACTION_START
mdefine_line|#define SMT_PORT_ACTION_START&t;3
DECL|macro|SMT_PORT_ACTION_STOP
mdefine_line|#define SMT_PORT_ACTION_STOP&t;4
macro_line|#endif&t;/* _SMT_ */
eof
