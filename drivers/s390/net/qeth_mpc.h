multiline_comment|/*&n; * linux/drivers/s390/net/qeth_mpc.h&n; *&n; * Linux on zSeries OSA Express and HiperSockets support&n; *&n; * Copyright 2000,2003 IBM Corporation&n; * Author(s): Utz Bacher &lt;utz.bacher@de.ibm.com&gt;&n; *&n; */
macro_line|#ifndef __QETH_MPC_H__
DECL|macro|__QETH_MPC_H__
mdefine_line|#define __QETH_MPC_H__
DECL|macro|VERSION_QETH_MPC_H
mdefine_line|#define VERSION_QETH_MPC_H &quot;$Revision: 1.16 $&quot;
DECL|macro|QETH_IPA_TIMEOUT
mdefine_line|#define QETH_IPA_TIMEOUT (card-&gt;ipa_timeout)
DECL|macro|QETH_MPC_TIMEOUT
mdefine_line|#define QETH_MPC_TIMEOUT 2000
DECL|macro|QETH_ADDR_TIMEOUT
mdefine_line|#define QETH_ADDR_TIMEOUT 1000
DECL|macro|QETH_SETIP_RETRIES
mdefine_line|#define QETH_SETIP_RETRIES 2
DECL|macro|IDX_ACTIVATE_SIZE
mdefine_line|#define IDX_ACTIVATE_SIZE 0x22
DECL|macro|CM_ENABLE_SIZE
mdefine_line|#define CM_ENABLE_SIZE 0x63
DECL|macro|CM_SETUP_SIZE
mdefine_line|#define CM_SETUP_SIZE 0x64
DECL|macro|ULP_ENABLE_SIZE
mdefine_line|#define ULP_ENABLE_SIZE 0x6b
DECL|macro|ULP_SETUP_SIZE
mdefine_line|#define ULP_SETUP_SIZE 0x6c
DECL|macro|DM_ACT_SIZE
mdefine_line|#define DM_ACT_SIZE 0x55
DECL|macro|QETH_MPC_TOKEN_LENGTH
mdefine_line|#define QETH_MPC_TOKEN_LENGTH 4
DECL|macro|QETH_SEQ_NO_LENGTH
mdefine_line|#define QETH_SEQ_NO_LENGTH 4
DECL|macro|QETH_IPA_SEQ_NO_LENGTH
mdefine_line|#define QETH_IPA_SEQ_NO_LENGTH 2
DECL|macro|QETH_TRANSPORT_HEADER_SEQ_NO
mdefine_line|#define QETH_TRANSPORT_HEADER_SEQ_NO(buffer) (buffer+4)
DECL|macro|QETH_PDU_HEADER_SEQ_NO
mdefine_line|#define QETH_PDU_HEADER_SEQ_NO(buffer) (buffer+0x1c)
DECL|macro|QETH_PDU_HEADER_ACK_SEQ_NO
mdefine_line|#define QETH_PDU_HEADER_ACK_SEQ_NO(buffer) (buffer+0x20)
r_extern
r_int
r_char
id|IDX_ACTIVATE_READ
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|IDX_ACTIVATE_WRITE
(braket
)braket
suffix:semicolon
DECL|macro|QETH_IDX_ACT_ISSUER_RM_TOKEN
mdefine_line|#define QETH_IDX_ACT_ISSUER_RM_TOKEN(buffer) (buffer+0x0c)
DECL|macro|QETH_IDX_NO_PORTNAME_REQUIRED
mdefine_line|#define QETH_IDX_NO_PORTNAME_REQUIRED(buffer) ((buffer)[0x0b]&amp;0x80)
DECL|macro|QETH_IDX_ACT_FUNC_LEVEL
mdefine_line|#define QETH_IDX_ACT_FUNC_LEVEL(buffer) (buffer+0x10)
DECL|macro|QETH_IDX_ACT_DATASET_NAME
mdefine_line|#define QETH_IDX_ACT_DATASET_NAME(buffer) (buffer+0x16)
DECL|macro|QETH_IDX_ACT_QDIO_DEV_CUA
mdefine_line|#define QETH_IDX_ACT_QDIO_DEV_CUA(buffer) (buffer+0x1e)
DECL|macro|QETH_IDX_ACT_QDIO_DEV_REALADDR
mdefine_line|#define QETH_IDX_ACT_QDIO_DEV_REALADDR(buffer) (buffer+0x20)
DECL|macro|QETH_IS_IDX_ACT_POS_REPLY
mdefine_line|#define QETH_IS_IDX_ACT_POS_REPLY(buffer) (((buffer)[0x08]&amp;3)==2)
DECL|macro|QETH_IDX_REPLY_LEVEL
mdefine_line|#define QETH_IDX_REPLY_LEVEL(buffer) (buffer+0x12)
DECL|macro|QETH_MCL_LENGTH
mdefine_line|#define QETH_MCL_LENGTH 4
r_extern
r_int
r_char
id|CM_ENABLE
(braket
)braket
suffix:semicolon
DECL|macro|QETH_CM_ENABLE_ISSUER_RM_TOKEN
mdefine_line|#define QETH_CM_ENABLE_ISSUER_RM_TOKEN(buffer) (buffer+0x2c)
DECL|macro|QETH_CM_ENABLE_FILTER_TOKEN
mdefine_line|#define QETH_CM_ENABLE_FILTER_TOKEN(buffer) (buffer+0x53)
DECL|macro|QETH_CM_ENABLE_USER_DATA
mdefine_line|#define QETH_CM_ENABLE_USER_DATA(buffer) (buffer+0x5b)
DECL|macro|QETH_CM_ENABLE_RESP_FILTER_TOKEN
mdefine_line|#define QETH_CM_ENABLE_RESP_FILTER_TOKEN(buffer) (PDU_ENCAPSULATION(buffer)+ &bslash;&n;&t;&t;&t;&t;&t;&t;  0x13)
r_extern
r_int
r_char
id|CM_SETUP
(braket
)braket
suffix:semicolon
DECL|macro|QETH_CM_SETUP_DEST_ADDR
mdefine_line|#define QETH_CM_SETUP_DEST_ADDR(buffer) (buffer+0x2c)
DECL|macro|QETH_CM_SETUP_CONNECTION_TOKEN
mdefine_line|#define QETH_CM_SETUP_CONNECTION_TOKEN(buffer) (buffer+0x51)
DECL|macro|QETH_CM_SETUP_FILTER_TOKEN
mdefine_line|#define QETH_CM_SETUP_FILTER_TOKEN(buffer) (buffer+0x5a)
DECL|macro|QETH_CM_SETUP_RESP_DEST_ADDR
mdefine_line|#define QETH_CM_SETUP_RESP_DEST_ADDR(buffer) (PDU_ENCAPSULATION(buffer)+ &bslash;&n;&t;&t;&t;&t;&t;      0x1a)
r_extern
r_int
r_char
id|ULP_ENABLE
(braket
)braket
suffix:semicolon
DECL|macro|QETH_ULP_ENABLE_LINKNUM
mdefine_line|#define QETH_ULP_ENABLE_LINKNUM(buffer) (buffer+0x61)
DECL|macro|QETH_ULP_ENABLE_DEST_ADDR
mdefine_line|#define QETH_ULP_ENABLE_DEST_ADDR(buffer) (buffer+0x2c)
DECL|macro|QETH_ULP_ENABLE_FILTER_TOKEN
mdefine_line|#define QETH_ULP_ENABLE_FILTER_TOKEN(buffer) (buffer+0x53)
DECL|macro|QETH_ULP_ENABLE_PORTNAME_AND_LL
mdefine_line|#define QETH_ULP_ENABLE_PORTNAME_AND_LL(buffer) (buffer+0x62)
DECL|macro|QETH_ULP_ENABLE_RESP_FILTER_TOKEN
mdefine_line|#define QETH_ULP_ENABLE_RESP_FILTER_TOKEN(buffer) (PDU_ENCAPSULATION(buffer)+ &bslash;&n;&t;&t;&t;&t;&t;&t;   0x13)
DECL|macro|QETH_ULP_ENABLE_RESP_MAX_MTU
mdefine_line|#define QETH_ULP_ENABLE_RESP_MAX_MTU(buffer) (PDU_ENCAPSULATION(buffer)+ 0x1f)
DECL|macro|QETH_ULP_ENABLE_RESP_DIFINFO_LEN
mdefine_line|#define QETH_ULP_ENABLE_RESP_DIFINFO_LEN(buffer) (PDU_ENCAPSULATION(buffer)+ &bslash;&n;&t;&t;&t;&t;&t;  &t;  0x17)
DECL|macro|QETH_ULP_ENABLE_RESP_LINK_TYPE
mdefine_line|#define QETH_ULP_ENABLE_RESP_LINK_TYPE(buffer) (PDU_ENCAPSULATION(buffer)+ &bslash;&n;&t;&t;&t;&t;&t;&t;0x2b)
r_extern
r_int
r_char
id|ULP_SETUP
(braket
)braket
suffix:semicolon
DECL|macro|QETH_ULP_SETUP_DEST_ADDR
mdefine_line|#define QETH_ULP_SETUP_DEST_ADDR(buffer) (buffer+0x2c)
DECL|macro|QETH_ULP_SETUP_CONNECTION_TOKEN
mdefine_line|#define QETH_ULP_SETUP_CONNECTION_TOKEN(buffer) (buffer+0x51)
DECL|macro|QETH_ULP_SETUP_FILTER_TOKEN
mdefine_line|#define QETH_ULP_SETUP_FILTER_TOKEN(buffer) (buffer+0x5a)
DECL|macro|QETH_ULP_SETUP_CUA
mdefine_line|#define QETH_ULP_SETUP_CUA(buffer) (buffer+0x68)
DECL|macro|QETH_ULP_SETUP_REAL_DEVADDR
mdefine_line|#define QETH_ULP_SETUP_REAL_DEVADDR(buffer) (buffer+0x6a)
DECL|macro|QETH_ULP_SETUP_RESP_CONNECTION_TOKEN
mdefine_line|#define QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(buffer) (PDU_ENCAPSULATION &bslash;&n;&t;&t;&t;&t;&t;&t;      (buffer)+0x1a)
r_extern
r_int
r_char
id|DM_ACT
(braket
)braket
suffix:semicolon
DECL|macro|QETH_DM_ACT_DEST_ADDR
mdefine_line|#define QETH_DM_ACT_DEST_ADDR(buffer) (buffer+0x2c)
DECL|macro|QETH_DM_ACT_CONNECTION_TOKEN
mdefine_line|#define QETH_DM_ACT_CONNECTION_TOKEN(buffer) (buffer+0x51)
DECL|macro|IPA_CMD_STARTLAN
mdefine_line|#define IPA_CMD_STARTLAN 0x01
DECL|macro|IPA_CMD_STOPLAN
mdefine_line|#define IPA_CMD_STOPLAN 0x02
DECL|macro|IPA_CMD_SETIP
mdefine_line|#define IPA_CMD_SETIP 0xb1
DECL|macro|IPA_CMD_DELIP
mdefine_line|#define IPA_CMD_DELIP 0xb7
DECL|macro|IPA_CMD_QIPASSIST
mdefine_line|#define IPA_CMD_QIPASSIST 0xb2
DECL|macro|IPA_CMD_SETASSPARMS
mdefine_line|#define IPA_CMD_SETASSPARMS 0xb3
DECL|macro|IPA_CMD_SETIPM
mdefine_line|#define IPA_CMD_SETIPM 0xb4
DECL|macro|IPA_CMD_DELIPM
mdefine_line|#define IPA_CMD_DELIPM 0xb5
DECL|macro|IPA_CMD_SETRTG
mdefine_line|#define IPA_CMD_SETRTG 0xb6
DECL|macro|IPA_CMD_SETADAPTERPARMS
mdefine_line|#define IPA_CMD_SETADAPTERPARMS 0xb8
DECL|macro|IPA_CMD_ADD_ADDR_ENTRY
mdefine_line|#define IPA_CMD_ADD_ADDR_ENTRY 0xc1
DECL|macro|IPA_CMD_DELETE_ADDR_ENTRY
mdefine_line|#define IPA_CMD_DELETE_ADDR_ENTRY 0xc2
DECL|macro|IPA_CMD_CREATE_ADDR
mdefine_line|#define IPA_CMD_CREATE_ADDR 0xc3
DECL|macro|IPA_CMD_DESTROY_ADDR
mdefine_line|#define IPA_CMD_DESTROY_ADDR 0xc4
DECL|macro|IPA_CMD_REGISTER_LOCAL_ADDR
mdefine_line|#define IPA_CMD_REGISTER_LOCAL_ADDR 0xd1
DECL|macro|IPA_CMD_UNREGISTER_LOCAL_ADDR
mdefine_line|#define IPA_CMD_UNREGISTER_LOCAL_ADDR 0xd2
DECL|macro|INITIATOR_HOST
mdefine_line|#define INITIATOR_HOST 0
DECL|macro|INITIATOR_HYDRA
mdefine_line|#define INITIATOR_HYDRA 1
DECL|macro|PRIM_VERSION_IPA
mdefine_line|#define PRIM_VERSION_IPA 1
DECL|macro|PROT_VERSION_SNA
mdefine_line|#define PROT_VERSION_SNA 1 /* hahaha */
DECL|macro|PROT_VERSION_IPv4
mdefine_line|#define PROT_VERSION_IPv4 4
DECL|macro|PROT_VERSION_IPv6
mdefine_line|#define PROT_VERSION_IPv6 6
DECL|macro|OSA_ADDR_LEN
mdefine_line|#define OSA_ADDR_LEN 6
DECL|macro|IPA_SETADAPTERPARMS_IP_VERSION
mdefine_line|#define IPA_SETADAPTERPARMS_IP_VERSION PROT_VERSION_IPv4
DECL|macro|SR_INFO_LEN
mdefine_line|#define SR_INFO_LEN 16
DECL|macro|IPA_ARP_PROCESSING
mdefine_line|#define IPA_ARP_PROCESSING 0x00000001L
DECL|macro|IPA_INBOUND_CHECKSUM
mdefine_line|#define IPA_INBOUND_CHECKSUM 0x00000002L
DECL|macro|IPA_OUTBOUND_CHECKSUM
mdefine_line|#define IPA_OUTBOUND_CHECKSUM 0x00000004L
DECL|macro|IPA_IP_FRAGMENTATION
mdefine_line|#define IPA_IP_FRAGMENTATION 0x00000008L
DECL|macro|IPA_FILTERING
mdefine_line|#define IPA_FILTERING 0x00000010L
DECL|macro|IPA_IPv6
mdefine_line|#define IPA_IPv6 0x00000020L
DECL|macro|IPA_MULTICASTING
mdefine_line|#define IPA_MULTICASTING 0x00000040L
DECL|macro|IPA_IP_REASSEMBLY
mdefine_line|#define IPA_IP_REASSEMBLY 0x00000080L
DECL|macro|IPA_QUERY_ARP_COUNTERS
mdefine_line|#define IPA_QUERY_ARP_COUNTERS 0x00000100L
DECL|macro|IPA_QUERY_ARP_ADDR_INFO
mdefine_line|#define IPA_QUERY_ARP_ADDR_INFO 0x00000200L
DECL|macro|IPA_SETADAPTERPARMS
mdefine_line|#define IPA_SETADAPTERPARMS 0x00000400L
DECL|macro|IPA_VLAN_PRIO
mdefine_line|#define IPA_VLAN_PRIO 0x00000800L
DECL|macro|IPA_PASSTHRU
mdefine_line|#define IPA_PASSTHRU 0x00001000L
DECL|macro|IPA_FULL_VLAN
mdefine_line|#define IPA_FULL_VLAN 0x00004000L
DECL|macro|IPA_SOURCE_MAC_AVAIL
mdefine_line|#define IPA_SOURCE_MAC_AVAIL 0x00010000L
DECL|macro|IPA_SETADP_QUERY_COMMANDS_SUPPORTED
mdefine_line|#define IPA_SETADP_QUERY_COMMANDS_SUPPORTED 0x01
DECL|macro|IPA_SETADP_ALTER_MAC_ADDRESS
mdefine_line|#define IPA_SETADP_ALTER_MAC_ADDRESS 0x02
DECL|macro|IPA_SETADP_ADD_DELETE_GROUP_ADDRESS
mdefine_line|#define IPA_SETADP_ADD_DELETE_GROUP_ADDRESS 0x04
DECL|macro|IPA_SETADP_ADD_DELETE_FUNCTIONAL_ADDR
mdefine_line|#define IPA_SETADP_ADD_DELETE_FUNCTIONAL_ADDR 0x08
DECL|macro|IPA_SETADP_SET_ADDRESSING_MODE
mdefine_line|#define IPA_SETADP_SET_ADDRESSING_MODE 0x10
DECL|macro|IPA_SETADP_SET_CONFIG_PARMS
mdefine_line|#define IPA_SETADP_SET_CONFIG_PARMS 0x20
DECL|macro|IPA_SETADP_SET_CONFIG_PARMS_EXTENDED
mdefine_line|#define IPA_SETADP_SET_CONFIG_PARMS_EXTENDED 0x40
DECL|macro|IPA_SETADP_SET_BROADCAST_MODE
mdefine_line|#define IPA_SETADP_SET_BROADCAST_MODE 0x80
DECL|macro|IPA_SETADP_SEND_OSA_MESSAGE
mdefine_line|#define IPA_SETADP_SEND_OSA_MESSAGE 0x0100
DECL|macro|IPA_SETADP_SET_SNMP_CONTROL
mdefine_line|#define IPA_SETADP_SET_SNMP_CONTROL 0x0200
DECL|macro|IPA_SETADP_READ_SNMP_PARMS
mdefine_line|#define IPA_SETADP_READ_SNMP_PARMS 0x0400
DECL|macro|IPA_SETADP_WRITE_SNMP_PARMS
mdefine_line|#define IPA_SETADP_WRITE_SNMP_PARMS 0x0800
DECL|macro|IPA_SETADP_QUERY_CARD_INFO
mdefine_line|#define IPA_SETADP_QUERY_CARD_INFO 0x1000
DECL|macro|CHANGE_ADDR_READ_MAC
mdefine_line|#define CHANGE_ADDR_READ_MAC 0
DECL|macro|CHANGE_ADDR_REPLACE_MAC
mdefine_line|#define CHANGE_ADDR_REPLACE_MAC 1
DECL|macro|CHANGE_ADDR_ADD_MAC
mdefine_line|#define CHANGE_ADDR_ADD_MAC 2
DECL|macro|CHANGE_ADDR_DEL_MAC
mdefine_line|#define CHANGE_ADDR_DEL_MAC 4
DECL|macro|CHANGE_ADDR_RESET_MAC
mdefine_line|#define CHANGE_ADDR_RESET_MAC 8
DECL|macro|CHANGE_ADDR_READ_ADDR
mdefine_line|#define CHANGE_ADDR_READ_ADDR 0
DECL|macro|CHANGE_ADDR_ADD_ADDR
mdefine_line|#define CHANGE_ADDR_ADD_ADDR 1
DECL|macro|CHANGE_ADDR_DEL_ADDR
mdefine_line|#define CHANGE_ADDR_DEL_ADDR 2
DECL|macro|CHANGE_ADDR_FLUSH_ADDR_TABLE
mdefine_line|#define CHANGE_ADDR_FLUSH_ADDR_TABLE 4
multiline_comment|/* we assumed, that the card is named card */
DECL|macro|qeth_is_supported
mdefine_line|#define qeth_is_supported(str) (card-&gt;ipa_supported&amp;str)
DECL|macro|qeth_is_supported6
mdefine_line|#define qeth_is_supported6(str) (card-&gt;ipa6_supported&amp;str)
DECL|macro|qeth_is_adp_supported
mdefine_line|#define qeth_is_adp_supported(str) (card-&gt;adp_supported&amp;str)
multiline_comment|/* the same for all assist parms: */
DECL|macro|IPA_CMD_ASS_START
mdefine_line|#define IPA_CMD_ASS_START 0x0001
DECL|macro|IPA_CMD_ASS_STOP
mdefine_line|#define IPA_CMD_ASS_STOP 0x0002
DECL|macro|IPA_CMD_ASS_CONFIGURE
mdefine_line|#define IPA_CMD_ASS_CONFIGURE 0x0003
DECL|macro|IPA_CMD_ASS_ENABLE
mdefine_line|#define IPA_CMD_ASS_ENABLE 0x0004
DECL|macro|IPA_CMD_ASS_ARP_SET_NO_ENTRIES
mdefine_line|#define IPA_CMD_ASS_ARP_SET_NO_ENTRIES 0x0003
DECL|macro|IPA_CMD_ASS_ARP_QUERY_CACHE
mdefine_line|#define IPA_CMD_ASS_ARP_QUERY_CACHE 0x0004
DECL|macro|IPA_CMD_ASS_ARP_ADD_ENTRY
mdefine_line|#define IPA_CMD_ASS_ARP_ADD_ENTRY 0x0005
DECL|macro|IPA_CMD_ASS_ARP_REMOVE_ENTRY
mdefine_line|#define IPA_CMD_ASS_ARP_REMOVE_ENTRY 0x0006
DECL|macro|IPA_CMD_ASS_ARP_FLUSH_CACHE
mdefine_line|#define IPA_CMD_ASS_ARP_FLUSH_CACHE 0x0007
DECL|macro|IPA_CMD_ASS_ARP_QUERY_INFO
mdefine_line|#define IPA_CMD_ASS_ARP_QUERY_INFO 0x0104
DECL|macro|IPA_CMD_ASS_ARP_QUERY_STATS
mdefine_line|#define IPA_CMD_ASS_ARP_QUERY_STATS 0x0204
DECL|macro|IPA_CHECKSUM_DEFAULT_ENABLE_MASK
mdefine_line|#define IPA_CHECKSUM_DEFAULT_ENABLE_MASK 0x001a
DECL|macro|IPA_CMD_ASS_FILTER_SET_TYPES
mdefine_line|#define IPA_CMD_ASS_FILTER_SET_TYPES 0x0003
DECL|macro|IPA_CMD_ASS_IPv6_SET_FUNCTIONS
mdefine_line|#define IPA_CMD_ASS_IPv6_SET_FUNCTIONS 0x0003
DECL|macro|IPA_REPLY_SUCCESS
mdefine_line|#define IPA_REPLY_SUCCESS 0
DECL|macro|IPA_REPLY_FAILED
mdefine_line|#define IPA_REPLY_FAILED 1
DECL|macro|IPA_REPLY_OPNOTSUPP
mdefine_line|#define IPA_REPLY_OPNOTSUPP 2
DECL|macro|IPA_REPLY_OPNOTSUPP2
mdefine_line|#define IPA_REPLY_OPNOTSUPP2 4
DECL|macro|IPA_REPLY_NOINFO
mdefine_line|#define IPA_REPLY_NOINFO 8
DECL|macro|IPA_SETIP_FLAGS
mdefine_line|#define IPA_SETIP_FLAGS 0
DECL|macro|IPA_SETIP_VIPA_FLAGS
mdefine_line|#define IPA_SETIP_VIPA_FLAGS 1
DECL|macro|IPA_SETIP_TAKEOVER_FLAGS
mdefine_line|#define IPA_SETIP_TAKEOVER_FLAGS 2
DECL|macro|VIPA_2_B_ADDED
mdefine_line|#define VIPA_2_B_ADDED 0
DECL|macro|VIPA_ESTABLISHED
mdefine_line|#define VIPA_ESTABLISHED 1
DECL|macro|VIPA_2_B_REMOVED
mdefine_line|#define VIPA_2_B_REMOVED 2
DECL|macro|IPA_DELIP_FLAGS
mdefine_line|#define IPA_DELIP_FLAGS 0
DECL|macro|IPA_SETADP_CMDSIZE
mdefine_line|#define IPA_SETADP_CMDSIZE 40
DECL|struct|ipa_setadp_cmd
r_struct
id|ipa_setadp_cmd
(brace
DECL|member|supp_hw_cmds
id|__u32
id|supp_hw_cmds
suffix:semicolon
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
DECL|member|cmdlength
id|__u16
id|cmdlength
suffix:semicolon
DECL|member|reserved2
id|__u16
id|reserved2
suffix:semicolon
DECL|member|command_code
id|__u32
id|command_code
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|frames_used_total
id|__u8
id|frames_used_total
suffix:semicolon
DECL|member|frame_seq_no
id|__u8
id|frame_seq_no
suffix:semicolon
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|no_lantypes_supp
id|__u32
id|no_lantypes_supp
suffix:semicolon
DECL|member|lan_type
id|__u8
id|lan_type
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|supported_cmds
id|__u32
id|supported_cmds
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|query_cmds_supp
)brace
id|query_cmds_supp
suffix:semicolon
r_struct
(brace
DECL|member|cmd
id|__u32
id|cmd
suffix:semicolon
DECL|member|addr_size
id|__u32
id|addr_size
suffix:semicolon
DECL|member|no_macs
id|__u32
id|no_macs
suffix:semicolon
DECL|member|addr
id|__u8
id|addr
(braket
id|OSA_ADDR_LEN
)braket
suffix:semicolon
DECL|member|change_addr
)brace
id|change_addr
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipa_cmd
r_struct
id|ipa_cmd
(brace
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|initiator
id|__u8
id|initiator
suffix:semicolon
DECL|member|seq_no
id|__u16
id|seq_no
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|adapter_type
id|__u8
id|adapter_type
suffix:semicolon
DECL|member|rel_adapter_no
id|__u8
id|rel_adapter_no
suffix:semicolon
DECL|member|prim_version_no
id|__u8
id|prim_version_no
suffix:semicolon
DECL|member|param_count
id|__u8
id|param_count
suffix:semicolon
DECL|member|prot_version
id|__u16
id|prot_version
suffix:semicolon
DECL|member|ipa_supported
id|__u32
id|ipa_supported
suffix:semicolon
DECL|member|ipa_enabled
id|__u32
id|ipa_enabled
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|ip
id|__u8
id|ip
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|netmask
id|__u8
id|netmask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|setdelip4
)brace
id|setdelip4
suffix:semicolon
r_struct
(brace
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|netmask
id|__u8
id|netmask
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|setdelip6
)brace
id|setdelip6
suffix:semicolon
r_struct
(brace
DECL|member|assist_no
id|__u32
id|assist_no
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|command_code
id|__u16
id|command_code
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|number_of_replies
id|__u8
id|number_of_replies
suffix:semicolon
DECL|member|seq_no
id|__u8
id|seq_no
suffix:semicolon
r_union
(brace
DECL|member|flags_32bit
id|__u32
id|flags_32bit
suffix:semicolon
r_struct
(brace
DECL|member|mac
id|__u8
id|mac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|add_arp_entry
)brace
id|add_arp_entry
suffix:semicolon
DECL|member|ip
id|__u8
id|ip
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|setassparms
)brace
id|setassparms
suffix:semicolon
r_struct
(brace
DECL|member|mac
id|__u8
id|mac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|padding
id|__u8
id|padding
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ip6
id|__u8
id|ip6
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ip4_6
id|__u8
id|ip4_6
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|setdelipm
)brace
id|setdelipm
suffix:semicolon
r_struct
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|setrtg
)brace
id|setrtg
suffix:semicolon
DECL|member|setadapterparms
r_struct
id|ipa_setadp_cmd
id|setadapterparms
suffix:semicolon
r_struct
(brace
DECL|member|command
id|__u32
id|command
suffix:semicolon
DECL|macro|ADDR_FRAME_TYPE_DIX
mdefine_line|#define ADDR_FRAME_TYPE_DIX 1
DECL|macro|ADDR_FRAME_TYPE_802_3
mdefine_line|#define ADDR_FRAME_TYPE_802_3 2
DECL|macro|ADDR_FRAME_TYPE_TR_WITHOUT_SR
mdefine_line|#define ADDR_FRAME_TYPE_TR_WITHOUT_SR 0x10
DECL|macro|ADDR_FRAME_TYPE_TR_WITH_SR
mdefine_line|#define ADDR_FRAME_TYPE_TR_WITH_SR 0x20
DECL|member|frame_type
id|__u32
id|frame_type
suffix:semicolon
DECL|member|cmd_flags
id|__u32
id|cmd_flags
suffix:semicolon
DECL|member|ip_addr
id|__u8
id|ip_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|tag_field
id|__u32
id|tag_field
suffix:semicolon
DECL|member|mac_addr
id|__u8
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|sr_len
id|__u32
id|sr_len
suffix:semicolon
DECL|member|sr_info
id|__u8
id|sr_info
(braket
id|SR_INFO_LEN
)braket
suffix:semicolon
DECL|member|add_addr_entry
)brace
id|add_addr_entry
suffix:semicolon
r_struct
(brace
DECL|member|command
id|__u32
id|command
suffix:semicolon
DECL|member|cmd_flags
id|__u32
id|cmd_flags
suffix:semicolon
DECL|member|ip_addr
id|__u8
id|ip_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|tag_field
id|__u32
id|tag_field
suffix:semicolon
DECL|member|delete_addr_entry
)brace
id|delete_addr_entry
suffix:semicolon
r_struct
(brace
DECL|member|unique_id
id|__u8
id|unique_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|create_destroy_addr
)brace
id|create_destroy_addr
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|QETH_IOC_MAGIC
mdefine_line|#define QETH_IOC_MAGIC 0x22
DECL|macro|QETH_IOCPROC_OSAEINTERFACES
mdefine_line|#define QETH_IOCPROC_OSAEINTERFACES _IOWR(QETH_IOC_MAGIC, 1, arg)
DECL|macro|QETH_IOCPROC_INTERFACECHANGES
mdefine_line|#define QETH_IOCPROC_INTERFACECHANGES _IOWR(QETH_IOC_MAGIC, 2, arg)
DECL|macro|SNMP_QUERY_CARD_INFO
mdefine_line|#define SNMP_QUERY_CARD_INFO 0x00000002L
DECL|macro|SNMP_REGISETER_MIB
mdefine_line|#define SNMP_REGISETER_MIB   0x00000004L
DECL|macro|SNMP_GET_OID
mdefine_line|#define SNMP_GET_OID         0x00000010L
DECL|macro|SNMP_SET_OID
mdefine_line|#define SNMP_SET_OID         0x00000011L
DECL|macro|SNMP_GET_NEXT_OID
mdefine_line|#define SNMP_GET_NEXT_OID    0x00000012L
DECL|macro|SNMP_QUERY_ALERTS
mdefine_line|#define SNMP_QUERY_ALERTS    0x00000020L
DECL|macro|SNMP_SET_TRAP
mdefine_line|#define SNMP_SET_TRAP        0x00000021L
DECL|macro|ARP_DATA_SIZE
mdefine_line|#define ARP_DATA_SIZE 3968
DECL|macro|ARP_FLUSH
mdefine_line|#define ARP_FLUSH -3
DECL|macro|ARP_RETURNCODE_NOARPDATA
mdefine_line|#define ARP_RETURNCODE_NOARPDATA -2
DECL|macro|ARP_RETURNCODE_ERROR
mdefine_line|#define ARP_RETURNCODE_ERROR -1
DECL|macro|ARP_RETURNCODE_SUCCESS
mdefine_line|#define ARP_RETURNCODE_SUCCESS 0
DECL|macro|ARP_RETURNCODE_LASTREPLY
mdefine_line|#define ARP_RETURNCODE_LASTREPLY 1
DECL|macro|SNMP_BASE_CMDLENGTH
mdefine_line|#define SNMP_BASE_CMDLENGTH 44
DECL|macro|SNMP_SETADP_CMDLENGTH
mdefine_line|#define SNMP_SETADP_CMDLENGTH 16
DECL|macro|SNMP_REQUEST_DATA_OFFSET
mdefine_line|#define SNMP_REQUEST_DATA_OFFSET 16
DECL|struct|snmp_ipa_setadp_cmd
r_struct
id|snmp_ipa_setadp_cmd
(brace
DECL|member|supp_hw_cmds
id|__u32
id|supp_hw_cmds
suffix:semicolon
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
DECL|member|cmdlength
id|__u16
id|cmdlength
suffix:semicolon
DECL|member|reserved2
id|__u16
id|reserved2
suffix:semicolon
DECL|member|command_code
id|__u32
id|command_code
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|frames_used_total
id|__u8
id|frames_used_total
suffix:semicolon
DECL|member|frame_seq_no
id|__u8
id|frame_seq_no
suffix:semicolon
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
DECL|member|snmp_token
id|__u8
id|snmp_token
(braket
l_int|16
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|snmp_request
id|__u32
id|snmp_request
suffix:semicolon
DECL|member|snmp_interface
id|__u32
id|snmp_interface
suffix:semicolon
DECL|member|snmp_returncode
id|__u32
id|snmp_returncode
suffix:semicolon
DECL|member|snmp_firmwarelevel
id|__u32
id|snmp_firmwarelevel
suffix:semicolon
DECL|member|snmp_seqno
id|__u32
id|snmp_seqno
suffix:semicolon
DECL|member|snmp_data
id|__u8
id|snmp_data
(braket
id|ARP_DATA_SIZE
)braket
suffix:semicolon
DECL|member|snmp_subcommand
)brace
id|snmp_subcommand
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|arp_cmd
r_struct
id|arp_cmd
(brace
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|initiator
id|__u8
id|initiator
suffix:semicolon
DECL|member|seq_no
id|__u16
id|seq_no
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|adapter_type
id|__u8
id|adapter_type
suffix:semicolon
DECL|member|rel_adapter_no
id|__u8
id|rel_adapter_no
suffix:semicolon
DECL|member|prim_version_no
id|__u8
id|prim_version_no
suffix:semicolon
DECL|member|param_count
id|__u8
id|param_count
suffix:semicolon
DECL|member|prot_version
id|__u16
id|prot_version
suffix:semicolon
DECL|member|ipa_supported
id|__u32
id|ipa_supported
suffix:semicolon
DECL|member|ipa_enabled
id|__u32
id|ipa_enabled
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|assist_no
id|__u32
id|assist_no
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|command_code
id|__u16
id|command_code
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
DECL|member|number_of_replies
id|__u8
id|number_of_replies
suffix:semicolon
DECL|member|seq_no
id|__u8
id|seq_no
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|tcpip_requestbitmask
id|__u16
id|tcpip_requestbitmask
suffix:semicolon
DECL|member|osa_setbitmask
id|__u16
id|osa_setbitmask
suffix:semicolon
DECL|member|number_of_entries
id|__u32
id|number_of_entries
suffix:semicolon
DECL|member|arp_data
id|__u8
id|arp_data
(braket
id|ARP_DATA_SIZE
)braket
suffix:semicolon
DECL|member|queryarp_data
)brace
id|queryarp_data
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|setassparms
)brace
id|setassparms
suffix:semicolon
DECL|member|setadapterparms
r_struct
id|snmp_ipa_setadp_cmd
id|setadapterparms
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IPA_PDU_HEADER_SIZE
mdefine_line|#define IPA_PDU_HEADER_SIZE 0x40
DECL|macro|QETH_IPA_PDU_LEN_TOTAL
mdefine_line|#define QETH_IPA_PDU_LEN_TOTAL(buffer) (buffer+0x0e)
DECL|macro|QETH_IPA_PDU_LEN_PDU1
mdefine_line|#define QETH_IPA_PDU_LEN_PDU1(buffer) (buffer+0x26)
DECL|macro|QETH_IPA_PDU_LEN_PDU2
mdefine_line|#define QETH_IPA_PDU_LEN_PDU2(buffer) (buffer+0x2a)
DECL|macro|QETH_IPA_PDU_LEN_PDU3
mdefine_line|#define QETH_IPA_PDU_LEN_PDU3(buffer) (buffer+0x3a)
r_extern
r_int
r_char
id|IPA_PDU_HEADER
(braket
)braket
suffix:semicolon
DECL|macro|QETH_IPA_CMD_DEST_ADDR
mdefine_line|#define QETH_IPA_CMD_DEST_ADDR(buffer) (buffer+0x2c)
DECL|macro|PDU_ENCAPSULATION
mdefine_line|#define PDU_ENCAPSULATION(buffer) &bslash;&n;&t;(buffer+ &bslash;&n;&t; *(buffer+ (*(buffer+0x0b))+ *(buffer+*(buffer+0x0b)+0x11) +0x07))
DECL|macro|IS_IPA
mdefine_line|#define IS_IPA(buffer) ((buffer) &amp;&amp; ( *(buffer+ ((*(buffer+0x0b))+4) )==0xc1) )
DECL|macro|IS_IPA_REPLY
mdefine_line|#define IS_IPA_REPLY(buffer) ( (buffer) &amp;&amp; ( (*(PDU_ENCAPSULATION(buffer)+1))==INITIATOR_HOST ) )
DECL|macro|CCW_NOP_CMD
mdefine_line|#define CCW_NOP_CMD 0x03
DECL|macro|CCW_NOP_COUNT
mdefine_line|#define CCW_NOP_COUNT 1
r_extern
r_int
r_char
id|WRITE_CCW
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|READ_CCW
(braket
)braket
suffix:semicolon
macro_line|#endif /* __QETH_MPC_H__ */
eof
