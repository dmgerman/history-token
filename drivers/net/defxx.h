multiline_comment|/*&n; * File Name:&n; *   defxx.h&n; *&n; * Copyright Information:&n; *   Copyright Digital Equipment Corporation 1996.&n; *&n; *   This software may be used and distributed according to the terms of&n; *   the GNU Public License, incorporated herein by reference.&n; *&n; * Abstract:&n; *   Contains all definitions specified by port specification and required&n; *   by the defxx.c driver.&n; *&n; * Maintainers:&n; *   LVS&t;Lawrence V. Stefani&n; *&n; * Contact:&n; *&t; The author may be reached at:&n; *&n; *&t;&t;Inet: stefani@lkg.dec.com&n; *&t;&t;Mail: Digital Equipment Corporation&n; *&t;&t;&t;  550 King Street&n; *&t;&t;&t;  M/S: LKG1-3/M07&n; *&t;&t;&t;  Littleton, MA  01460&n; *&n; * Modification History:&n; *&t;&t;Date&t;&t;Name&t;Description&n; *&t;&t;16-Aug-96&t;LVS&t;&t;Created.&n; *&t;&t;09-Sep-96&t;LVS&t;&t;Added group_prom field.  Moved read/write I/O&n; *&t;&t;&t;&t;&t;&t;&t;macros to DEFXX.C.&n; *&t;&t;12-Sep-96&t;LVS&t;&t;Removed packet request header pointers.&n; */
macro_line|#ifndef _DEFXX_H_
DECL|macro|_DEFXX_H_
mdefine_line|#define _DEFXX_H_
multiline_comment|/* Define basic types for unsigned chars, shorts, longs */
DECL|typedef|PI_UINT8
r_typedef
id|u8
id|PI_UINT8
suffix:semicolon
DECL|typedef|PI_UINT16
r_typedef
id|u16
id|PI_UINT16
suffix:semicolon
DECL|typedef|PI_UINT32
r_typedef
id|u32
id|PI_UINT32
suffix:semicolon
multiline_comment|/* Define general structures */
r_typedef
r_struct
multiline_comment|/* 64-bit counter */
(brace
DECL|member|ms
id|PI_UINT32
id|ms
suffix:semicolon
DECL|member|ls
id|PI_UINT32
id|ls
suffix:semicolon
DECL|typedef|PI_CNTR
)brace
id|PI_CNTR
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* LAN address */
(brace
DECL|member|lwrd_0
id|PI_UINT32
id|lwrd_0
suffix:semicolon
DECL|member|lwrd_1
id|PI_UINT32
id|lwrd_1
suffix:semicolon
DECL|typedef|PI_LAN_ADDR
)brace
id|PI_LAN_ADDR
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* Station ID address */
(brace
DECL|member|octet_7_4
id|PI_UINT32
id|octet_7_4
suffix:semicolon
DECL|member|octet_3_0
id|PI_UINT32
id|octet_3_0
suffix:semicolon
DECL|typedef|PI_STATION_ID
)brace
id|PI_STATION_ID
suffix:semicolon
multiline_comment|/* Define general constants */
DECL|macro|PI_ALIGN_K_DESC_BLK
mdefine_line|#define PI_ALIGN_K_DESC_BLK&t;  &t;&t;&t;8192&t;/* Descriptor block boundary&t;&t;*/
DECL|macro|PI_ALIGN_K_CONS_BLK
mdefine_line|#define PI_ALIGN_K_CONS_BLK&t;  &t; &t;&t;64&t;&t;/* Consumer block boundary&t;&t;  &t;*/
DECL|macro|PI_ALIGN_K_CMD_REQ_BUFF
mdefine_line|#define PI_ALIGN_K_CMD_REQ_BUFF  &t;&t;128&t; &t;/* Xmt Command que buffer alignment */
DECL|macro|PI_ALIGN_K_CMD_RSP_BUFF
mdefine_line|#define PI_ALIGN_K_CMD_RSP_BUFF&t; &t;&t;128&t; &t;/* Rcv Command que buffer alignment */
DECL|macro|PI_ALIGN_K_UNSOL_BUFF
mdefine_line|#define PI_ALIGN_K_UNSOL_BUFF&t; &t;&t;128&t; &t;/* Unsol que buffer alignment&t;   &t;*/
DECL|macro|PI_ALIGN_K_XMT_DATA_BUFF
mdefine_line|#define PI_ALIGN_K_XMT_DATA_BUFF &t;&t;0&t;   &t;/* Xmt data que buffer alignment&t;*/
DECL|macro|PI_ALIGN_K_RCV_DATA_BUFF
mdefine_line|#define PI_ALIGN_K_RCV_DATA_BUFF &t;&t;128&t; &t;/* Rcv que buffer alignment&t;&t;&t;*/
multiline_comment|/* Define PHY index values */
DECL|macro|PI_PHY_K_S
mdefine_line|#define PI_PHY_K_S&t;&t;&t;&t;&t;&t;0&t;&t;/* Index to S phy */
DECL|macro|PI_PHY_K_A
mdefine_line|#define PI_PHY_K_A&t;&t;&t;&t;&t;&t;0&t;&t;/* Index to A phy */
DECL|macro|PI_PHY_K_B
mdefine_line|#define PI_PHY_K_B&t;&t;&t;&t;&t;&t;1&t;&t;/* Index to B phy */
DECL|macro|PI_PHY_K_MAX
mdefine_line|#define PI_PHY_K_MAX&t;&t;&t;&t;&t;2&t;&t;/* Max number of phys */
multiline_comment|/* Define FMC descriptor fields */
DECL|macro|PI_FMC_DESCR_V_SOP
mdefine_line|#define PI_FMC_DESCR_V_SOP&t;&t;&t;&t;31
DECL|macro|PI_FMC_DESCR_V_EOP
mdefine_line|#define PI_FMC_DESCR_V_EOP&t;&t;&t;&t;30
DECL|macro|PI_FMC_DESCR_V_FSC
mdefine_line|#define PI_FMC_DESCR_V_FSC&t;&t;&t;&t;27
DECL|macro|PI_FMC_DESCR_V_FSB_ERROR
mdefine_line|#define PI_FMC_DESCR_V_FSB_ERROR&t;&t;26
DECL|macro|PI_FMC_DESCR_V_FSB_ADDR_RECOG
mdefine_line|#define PI_FMC_DESCR_V_FSB_ADDR_RECOG&t;25
DECL|macro|PI_FMC_DESCR_V_FSB_ADDR_COPIED
mdefine_line|#define PI_FMC_DESCR_V_FSB_ADDR_COPIED&t;24
DECL|macro|PI_FMC_DESCR_V_FSB
mdefine_line|#define PI_FMC_DESCR_V_FSB&t;&t;&t;&t;22
DECL|macro|PI_FMC_DESCR_V_RCC_FLUSH
mdefine_line|#define PI_FMC_DESCR_V_RCC_FLUSH&t;&t;21
DECL|macro|PI_FMC_DESCR_V_RCC_CRC
mdefine_line|#define PI_FMC_DESCR_V_RCC_CRC&t;&t;&t;20
DECL|macro|PI_FMC_DESCR_V_RCC_RRR
mdefine_line|#define PI_FMC_DESCR_V_RCC_RRR&t;&t;&t;17
DECL|macro|PI_FMC_DESCR_V_RCC_DD
mdefine_line|#define PI_FMC_DESCR_V_RCC_DD&t;&t;&t;15
DECL|macro|PI_FMC_DESCR_V_RCC_SS
mdefine_line|#define PI_FMC_DESCR_V_RCC_SS&t;&t;&t;13
DECL|macro|PI_FMC_DESCR_V_RCC
mdefine_line|#define PI_FMC_DESCR_V_RCC&t;&t;&t;&t;13
DECL|macro|PI_FMC_DESCR_V_LEN
mdefine_line|#define PI_FMC_DESCR_V_LEN&t;&t;&t;&t;0
DECL|macro|PI_FMC_DESCR_M_SOP
mdefine_line|#define PI_FMC_DESCR_M_SOP&t;&t;&t;&t;0x80000000
DECL|macro|PI_FMC_DESCR_M_EOP
mdefine_line|#define PI_FMC_DESCR_M_EOP&t;&t;&t;&t;0x40000000
DECL|macro|PI_FMC_DESCR_M_FSC
mdefine_line|#define PI_FMC_DESCR_M_FSC&t;&t;&t;&t;0x38000000
DECL|macro|PI_FMC_DESCR_M_FSB_ERROR
mdefine_line|#define PI_FMC_DESCR_M_FSB_ERROR&t;&t;0x04000000
DECL|macro|PI_FMC_DESCR_M_FSB_ADDR_RECOG
mdefine_line|#define PI_FMC_DESCR_M_FSB_ADDR_RECOG&t;0x02000000
DECL|macro|PI_FMC_DESCR_M_FSB_ADDR_COPIED
mdefine_line|#define PI_FMC_DESCR_M_FSB_ADDR_COPIED&t;0x01000000
DECL|macro|PI_FMC_DESCR_M_FSB
mdefine_line|#define PI_FMC_DESCR_M_FSB&t;&t;&t;&t;0x07C00000
DECL|macro|PI_FMC_DESCR_M_RCC_FLUSH
mdefine_line|#define PI_FMC_DESCR_M_RCC_FLUSH&t;&t;0x00200000
DECL|macro|PI_FMC_DESCR_M_RCC_CRC
mdefine_line|#define PI_FMC_DESCR_M_RCC_CRC&t;&t;&t;0x00100000
DECL|macro|PI_FMC_DESCR_M_RCC_RRR
mdefine_line|#define PI_FMC_DESCR_M_RCC_RRR&t;&t;&t;0x000E0000
DECL|macro|PI_FMC_DESCR_M_RCC_DD
mdefine_line|#define PI_FMC_DESCR_M_RCC_DD&t;&t;&t;0x00018000
DECL|macro|PI_FMC_DESCR_M_RCC_SS
mdefine_line|#define PI_FMC_DESCR_M_RCC_SS&t;&t;&t;0x00006000
DECL|macro|PI_FMC_DESCR_M_RCC
mdefine_line|#define PI_FMC_DESCR_M_RCC&t;&t;&t;&t;0x003FE000
DECL|macro|PI_FMC_DESCR_M_LEN
mdefine_line|#define PI_FMC_DESCR_M_LEN&t;&t;&t;&t;0x00001FFF
DECL|macro|PI_FMC_DESCR_K_RCC_FMC_INT_ERR
mdefine_line|#define PI_FMC_DESCR_K_RCC_FMC_INT_ERR&t;0x01AA
DECL|macro|PI_FMC_DESCR_K_RRR_SUCCESS
mdefine_line|#define PI_FMC_DESCR_K_RRR_SUCCESS&t;&t;0x00
DECL|macro|PI_FMC_DESCR_K_RRR_SA_MATCH
mdefine_line|#define PI_FMC_DESCR_K_RRR_SA_MATCH&t;&t;0x01
DECL|macro|PI_FMC_DESCR_K_RRR_DA_MATCH
mdefine_line|#define PI_FMC_DESCR_K_RRR_DA_MATCH&t;&t;0x02
DECL|macro|PI_FMC_DESCR_K_RRR_FMC_ABORT
mdefine_line|#define PI_FMC_DESCR_K_RRR_FMC_ABORT&t;0x03
DECL|macro|PI_FMC_DESCR_K_RRR_LENGTH_BAD
mdefine_line|#define PI_FMC_DESCR_K_RRR_LENGTH_BAD&t;0x04
DECL|macro|PI_FMC_DESCR_K_RRR_FRAGMENT
mdefine_line|#define PI_FMC_DESCR_K_RRR_FRAGMENT&t;&t;0x05
DECL|macro|PI_FMC_DESCR_K_RRR_FORMAT_ERR
mdefine_line|#define PI_FMC_DESCR_K_RRR_FORMAT_ERR&t;0x06
DECL|macro|PI_FMC_DESCR_K_RRR_MAC_RESET
mdefine_line|#define PI_FMC_DESCR_K_RRR_MAC_RESET&t;0x07
DECL|macro|PI_FMC_DESCR_K_DD_NO_MATCH
mdefine_line|#define PI_FMC_DESCR_K_DD_NO_MATCH&t;&t;0x0
DECL|macro|PI_FMC_DESCR_K_DD_PROMISCUOUS
mdefine_line|#define PI_FMC_DESCR_K_DD_PROMISCUOUS&t;0x1
DECL|macro|PI_FMC_DESCR_K_DD_CAM_MATCH
mdefine_line|#define PI_FMC_DESCR_K_DD_CAM_MATCH&t;&t;0x2
DECL|macro|PI_FMC_DESCR_K_DD_LOCAL_MATCH
mdefine_line|#define PI_FMC_DESCR_K_DD_LOCAL_MATCH&t;0x3
DECL|macro|PI_FMC_DESCR_K_SS_NO_MATCH
mdefine_line|#define PI_FMC_DESCR_K_SS_NO_MATCH&t;&t;0x0
DECL|macro|PI_FMC_DESCR_K_SS_BRIDGE_MATCH
mdefine_line|#define PI_FMC_DESCR_K_SS_BRIDGE_MATCH&t;0x1
DECL|macro|PI_FMC_DESCR_K_SS_NOT_POSSIBLE
mdefine_line|#define PI_FMC_DESCR_K_SS_NOT_POSSIBLE&t;0x2
DECL|macro|PI_FMC_DESCR_K_SS_LOCAL_MATCH
mdefine_line|#define PI_FMC_DESCR_K_SS_LOCAL_MATCH&t;0x3
multiline_comment|/* Define some max buffer sizes */
DECL|macro|PI_CMD_REQ_K_SIZE_MAX
mdefine_line|#define PI_CMD_REQ_K_SIZE_MAX&t;&t;&t;512
DECL|macro|PI_CMD_RSP_K_SIZE_MAX
mdefine_line|#define PI_CMD_RSP_K_SIZE_MAX&t;&t;&t;512
DECL|macro|PI_UNSOL_K_SIZE_MAX
mdefine_line|#define PI_UNSOL_K_SIZE_MAX&t;&t;&t;&t;512
DECL|macro|PI_SMT_HOST_K_SIZE_MAX
mdefine_line|#define PI_SMT_HOST_K_SIZE_MAX&t;&t;&t;4608&t;&t;/* 4 1/2 K */
DECL|macro|PI_RCV_DATA_K_SIZE_MAX
mdefine_line|#define PI_RCV_DATA_K_SIZE_MAX&t;&t;&t;4608&t;&t;/* 4 1/2 K */
DECL|macro|PI_XMT_DATA_K_SIZE_MAX
mdefine_line|#define PI_XMT_DATA_K_SIZE_MAX&t;&t;&t;4608&t;&t;/* 4 1/2 K */
multiline_comment|/* Define adapter states */
DECL|macro|PI_STATE_K_RESET
mdefine_line|#define PI_STATE_K_RESET&t;&t;&t;&t;0
DECL|macro|PI_STATE_K_UPGRADE
mdefine_line|#define PI_STATE_K_UPGRADE&t;&t;  &t;&t;1
DECL|macro|PI_STATE_K_DMA_UNAVAIL
mdefine_line|#define PI_STATE_K_DMA_UNAVAIL&t;&t;&t;2
DECL|macro|PI_STATE_K_DMA_AVAIL
mdefine_line|#define PI_STATE_K_DMA_AVAIL&t;&t;&t;3
DECL|macro|PI_STATE_K_LINK_AVAIL
mdefine_line|#define PI_STATE_K_LINK_AVAIL&t;&t;&t;4
DECL|macro|PI_STATE_K_LINK_UNAVAIL
mdefine_line|#define PI_STATE_K_LINK_UNAVAIL&t; &t;&t;5
DECL|macro|PI_STATE_K_HALTED
mdefine_line|#define PI_STATE_K_HALTED&t;&t;   &t;&t;6
DECL|macro|PI_STATE_K_RING_MEMBER
mdefine_line|#define PI_STATE_K_RING_MEMBER&t;&t;&t;7
DECL|macro|PI_STATE_K_NUMBER
mdefine_line|#define PI_STATE_K_NUMBER&t;&t;&t;&t;8 
multiline_comment|/* Define codes for command type */
DECL|macro|PI_CMD_K_START
mdefine_line|#define PI_CMD_K_START&t;&t;&t;&t;&t;0x00
DECL|macro|PI_CMD_K_FILTERS_SET
mdefine_line|#define PI_CMD_K_FILTERS_SET&t;&t;&t;0x01
DECL|macro|PI_CMD_K_FILTERS_GET
mdefine_line|#define PI_CMD_K_FILTERS_GET&t;&t;&t;0x02
DECL|macro|PI_CMD_K_CHARS_SET
mdefine_line|#define PI_CMD_K_CHARS_SET&t;&t;&t;&t;0x03
DECL|macro|PI_CMD_K_STATUS_CHARS_GET
mdefine_line|#define PI_CMD_K_STATUS_CHARS_GET&t;&t;0x04
DECL|macro|PI_CMD_K_CNTRS_GET
mdefine_line|#define PI_CMD_K_CNTRS_GET&t;&t;&t;&t;0x05
DECL|macro|PI_CMD_K_CNTRS_SET
mdefine_line|#define PI_CMD_K_CNTRS_SET&t;&t;&t;&t;0x06
DECL|macro|PI_CMD_K_ADDR_FILTER_SET
mdefine_line|#define PI_CMD_K_ADDR_FILTER_SET&t;&t;0x07
DECL|macro|PI_CMD_K_ADDR_FILTER_GET
mdefine_line|#define PI_CMD_K_ADDR_FILTER_GET&t;&t;0x08
DECL|macro|PI_CMD_K_ERROR_LOG_CLEAR
mdefine_line|#define PI_CMD_K_ERROR_LOG_CLEAR&t;&t;0x09
DECL|macro|PI_CMD_K_ERROR_LOG_GET
mdefine_line|#define PI_CMD_K_ERROR_LOG_GET&t;&t;&t;0x0A
DECL|macro|PI_CMD_K_FDDI_MIB_GET
mdefine_line|#define PI_CMD_K_FDDI_MIB_GET&t;&t;&t;0x0B
DECL|macro|PI_CMD_K_DEC_EXT_MIB_GET
mdefine_line|#define PI_CMD_K_DEC_EXT_MIB_GET&t;&t;0x0C
DECL|macro|PI_CMD_K_DEVICE_SPECIFIC_GET
mdefine_line|#define PI_CMD_K_DEVICE_SPECIFIC_GET&t;0x0D
DECL|macro|PI_CMD_K_SNMP_SET
mdefine_line|#define PI_CMD_K_SNMP_SET&t;&t;&t;&t;0x0E
DECL|macro|PI_CMD_K_UNSOL_TEST
mdefine_line|#define PI_CMD_K_UNSOL_TEST&t;&t;&t;&t;0x0F
DECL|macro|PI_CMD_K_SMT_MIB_GET
mdefine_line|#define PI_CMD_K_SMT_MIB_GET&t;&t;&t;0x10
DECL|macro|PI_CMD_K_SMT_MIB_SET
mdefine_line|#define PI_CMD_K_SMT_MIB_SET&t;&t;&t;0x11
DECL|macro|PI_CMD_K_MAX
mdefine_line|#define PI_CMD_K_MAX&t;&t;&t;&t;&t;0x11&t;/* Must match last */
multiline_comment|/* Define item codes for Chars_Set and Filters_Set commands */
DECL|macro|PI_ITEM_K_EOL
mdefine_line|#define PI_ITEM_K_EOL&t;&t;&t;&t;&t;0x00 &t;/* End-of-Item list &t;&t;  */
DECL|macro|PI_ITEM_K_T_REQ
mdefine_line|#define PI_ITEM_K_T_REQ&t;&t;&t;&t;&t;0x01 &t;/* DECnet T_REQ &t;&t;&t;  */
DECL|macro|PI_ITEM_K_TVX
mdefine_line|#define PI_ITEM_K_TVX&t;&t;&t;&t;&t;0x02 &t;/* DECnet TVX &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_RESTRICTED_TOKEN
mdefine_line|#define PI_ITEM_K_RESTRICTED_TOKEN&t;&t;0x03 &t;/* DECnet Restricted Token &t;  */&t; 
DECL|macro|PI_ITEM_K_LEM_THRESHOLD
mdefine_line|#define PI_ITEM_K_LEM_THRESHOLD&t;&t;&t;0x04 &t;/* DECnet LEM Threshold &t;  */
DECL|macro|PI_ITEM_K_RING_PURGER
mdefine_line|#define PI_ITEM_K_RING_PURGER&t;&t;&t;0x05 &t;/* DECnet Ring Purger Enable  */&t;
DECL|macro|PI_ITEM_K_CNTR_INTERVAL
mdefine_line|#define PI_ITEM_K_CNTR_INTERVAL&t;&t;&t;0x06 &t;/* Chars_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_IND_GROUP_PROM
mdefine_line|#define PI_ITEM_K_IND_GROUP_PROM&t;&t;0x07 &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_GROUP_PROM
mdefine_line|#define PI_ITEM_K_GROUP_PROM&t;&t;&t;0x08 &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_BROADCAST
mdefine_line|#define PI_ITEM_K_BROADCAST&t;&t;&t;&t;0x09 &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_SMT_PROM
mdefine_line|#define PI_ITEM_K_SMT_PROM&t;&t;&t;&t;0x0A &t;/* Filters_Set&t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_SMT_USER
mdefine_line|#define PI_ITEM_K_SMT_USER&t;&t;&t;&t;0x0B &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_RESERVED
mdefine_line|#define PI_ITEM_K_RESERVED&t;&t;&t;&t;0x0C &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_IMPLEMENTOR
mdefine_line|#define PI_ITEM_K_IMPLEMENTOR&t;&t;&t;0x0D &t;/* Filters_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_LOOPBACK_MODE
mdefine_line|#define PI_ITEM_K_LOOPBACK_MODE&t;&t;&t;0x0E &t;/* Chars_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_CONFIG_POLICY
mdefine_line|#define PI_ITEM_K_CONFIG_POLICY&t;&t;&t;0x10 &t;/* SMTConfigPolicy &t;&t;&t;  */
DECL|macro|PI_ITEM_K_CON_POLICY
mdefine_line|#define PI_ITEM_K_CON_POLICY&t;&t;&t;0x11 &t;/* SMTConnectionPolicy &t;&t;  */
DECL|macro|PI_ITEM_K_T_NOTIFY
mdefine_line|#define PI_ITEM_K_T_NOTIFY&t;&t;&t;&t;0x12 &t;/* SMTTNotify &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_STATION_ACTION
mdefine_line|#define PI_ITEM_K_STATION_ACTION&t;&t;0x13 &t;/* SMTStationAction&t;&t;&t;  */
DECL|macro|PI_ITEM_K_MAC_PATHS_REQ
mdefine_line|#define PI_ITEM_K_MAC_PATHS_REQ&t;   &t;&t;0x15 &t;/* MACPathsRequested &t;&t;  */
DECL|macro|PI_ITEM_K_MAC_ACTION
mdefine_line|#define PI_ITEM_K_MAC_ACTION&t;&t;&t;0x17 &t;/* MACAction &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_CON_POLICIES
mdefine_line|#define PI_ITEM_K_CON_POLICIES&t;&t;&t;0x18 &t;/* PORTConnectionPolicies&t;  */
DECL|macro|PI_ITEM_K_PORT_PATHS_REQ
mdefine_line|#define PI_ITEM_K_PORT_PATHS_REQ&t;&t;0x19 &t;/* PORTPathsRequested &t;&t;  */
DECL|macro|PI_ITEM_K_MAC_LOOP_TIME
mdefine_line|#define PI_ITEM_K_MAC_LOOP_TIME&t;&t;&t;0x1A &t;/* PORTMACLoopTime &t;&t;&t;  */
DECL|macro|PI_ITEM_K_TB_MAX
mdefine_line|#define PI_ITEM_K_TB_MAX&t;&t;&t;&t;0x1B &t;/* PORTTBMax &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_LER_CUTOFF
mdefine_line|#define PI_ITEM_K_LER_CUTOFF&t;&t;&t;0x1C &t;/* PORTLerCutoff &t;&t;&t;  */
DECL|macro|PI_ITEM_K_LER_ALARM
mdefine_line|#define PI_ITEM_K_LER_ALARM&t;&t;&t;&t;0x1D &t;/* PORTLerAlarm &t;&t;&t;  */
DECL|macro|PI_ITEM_K_PORT_ACTION
mdefine_line|#define PI_ITEM_K_PORT_ACTION&t;&t;&t;0x1E &t;/* PORTAction &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_FLUSH_TIME
mdefine_line|#define PI_ITEM_K_FLUSH_TIME&t;&t;&t;0x20 &t;/* Chars_Set &t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_MAC_T_REQ
mdefine_line|#define PI_ITEM_K_MAC_T_REQ&t;&t;&t;&t;0x29 &t;/* MACTReq &t;&t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_EMAC_RING_PURGER
mdefine_line|#define PI_ITEM_K_EMAC_RING_PURGER&t;&t;0x2A &t;/* eMACRingPurgerEnable&t;&t;  */
DECL|macro|PI_ITEM_K_EMAC_RTOKEN_TIMEOUT
mdefine_line|#define PI_ITEM_K_EMAC_RTOKEN_TIMEOUT&t;0x2B &t;/* eMACRestrictedTokenTimeout */
DECL|macro|PI_ITEM_K_FDX_ENB_DIS
mdefine_line|#define PI_ITEM_K_FDX_ENB_DIS&t;&t;&t;0x2C &t;/* eFDXEnable&t;&t;&t;&t;  */
DECL|macro|PI_ITEM_K_MAX
mdefine_line|#define PI_ITEM_K_MAX&t;&t;&t;&t;&t;0x2C &t;/* Must equal high item&t;&t;  */
multiline_comment|/* Values for some of the items */
DECL|macro|PI_K_FALSE
mdefine_line|#define PI_K_FALSE&t;&t;&t;&t;&t;&t;0&t;   /* Generic false */
DECL|macro|PI_K_TRUE
mdefine_line|#define PI_K_TRUE&t;&t;&t;&t;&t;&t;1&t;   /* Generic true  */
DECL|macro|PI_SNMP_K_TRUE
mdefine_line|#define PI_SNMP_K_TRUE&t;&t;&t;&t;&t;1&t;   /* SNMP true/false values */
DECL|macro|PI_SNMP_K_FALSE
mdefine_line|#define PI_SNMP_K_FALSE&t;&t;&t;&t;&t;2
DECL|macro|PI_FSTATE_K_BLOCK
mdefine_line|#define PI_FSTATE_K_BLOCK&t;&t;&t;&t;0&t;   /* Filter State */
DECL|macro|PI_FSTATE_K_PASS
mdefine_line|#define PI_FSTATE_K_PASS&t;&t;&t;&t;1
multiline_comment|/* Define command return codes */
DECL|macro|PI_RSP_K_SUCCESS
mdefine_line|#define PI_RSP_K_SUCCESS&t;&t;&t;&t;0x00
DECL|macro|PI_RSP_K_FAILURE
mdefine_line|#define PI_RSP_K_FAILURE&t;&t;&t;&t;0x01
DECL|macro|PI_RSP_K_WARNING
mdefine_line|#define PI_RSP_K_WARNING&t;&t;&t;&t;0x02
DECL|macro|PI_RSP_K_LOOP_MODE_BAD
mdefine_line|#define PI_RSP_K_LOOP_MODE_BAD&t;&t;&t;0x03
DECL|macro|PI_RSP_K_ITEM_CODE_BAD
mdefine_line|#define PI_RSP_K_ITEM_CODE_BAD&t;&t;&t;0x04
DECL|macro|PI_RSP_K_TVX_BAD
mdefine_line|#define PI_RSP_K_TVX_BAD&t;&t;&t;&t;0x05
DECL|macro|PI_RSP_K_TREQ_BAD
mdefine_line|#define PI_RSP_K_TREQ_BAD&t;&t;&t;&t;0x06
DECL|macro|PI_RSP_K_TOKEN_BAD
mdefine_line|#define PI_RSP_K_TOKEN_BAD&t;&t;&t;&t;0x07
DECL|macro|PI_RSP_K_NO_EOL
mdefine_line|#define PI_RSP_K_NO_EOL&t;&t;&t;&t;&t;0x0C
DECL|macro|PI_RSP_K_FILTER_STATE_BAD
mdefine_line|#define PI_RSP_K_FILTER_STATE_BAD&t;&t;0x0D
DECL|macro|PI_RSP_K_CMD_TYPE_BAD
mdefine_line|#define PI_RSP_K_CMD_TYPE_BAD&t;&t;&t;0x0E
DECL|macro|PI_RSP_K_ADAPTER_STATE_BAD
mdefine_line|#define PI_RSP_K_ADAPTER_STATE_BAD&t;&t;0x0F
DECL|macro|PI_RSP_K_RING_PURGER_BAD
mdefine_line|#define PI_RSP_K_RING_PURGER_BAD&t;&t;0x10
DECL|macro|PI_RSP_K_LEM_THRESHOLD_BAD
mdefine_line|#define PI_RSP_K_LEM_THRESHOLD_BAD&t;&t;0x11
DECL|macro|PI_RSP_K_LOOP_NOT_SUPPORTED
mdefine_line|#define PI_RSP_K_LOOP_NOT_SUPPORTED&t;&t;0x12
DECL|macro|PI_RSP_K_FLUSH_TIME_BAD
mdefine_line|#define PI_RSP_K_FLUSH_TIME_BAD&t;&t;&t;0x13
DECL|macro|PI_RSP_K_NOT_IMPLEMENTED
mdefine_line|#define PI_RSP_K_NOT_IMPLEMENTED&t;&t;0x14
DECL|macro|PI_RSP_K_CONFIG_POLICY_BAD
mdefine_line|#define PI_RSP_K_CONFIG_POLICY_BAD&t;&t;0x15
DECL|macro|PI_RSP_K_STATION_ACTION_BAD
mdefine_line|#define PI_RSP_K_STATION_ACTION_BAD&t;&t;0x16
DECL|macro|PI_RSP_K_MAC_ACTION_BAD
mdefine_line|#define PI_RSP_K_MAC_ACTION_BAD&t;&t;&t;0x17
DECL|macro|PI_RSP_K_CON_POLICIES_BAD
mdefine_line|#define PI_RSP_K_CON_POLICIES_BAD&t;&t;0x18
DECL|macro|PI_RSP_K_MAC_LOOP_TIME_BAD
mdefine_line|#define PI_RSP_K_MAC_LOOP_TIME_BAD&t;&t;0x19
DECL|macro|PI_RSP_K_TB_MAX_BAD
mdefine_line|#define PI_RSP_K_TB_MAX_BAD&t;&t;&t;&t;0x1A
DECL|macro|PI_RSP_K_LER_CUTOFF_BAD
mdefine_line|#define PI_RSP_K_LER_CUTOFF_BAD&t;&t;&t;0x1B
DECL|macro|PI_RSP_K_LER_ALARM_BAD
mdefine_line|#define PI_RSP_K_LER_ALARM_BAD&t;&t;&t;0x1C
DECL|macro|PI_RSP_K_MAC_PATHS_REQ_BAD
mdefine_line|#define PI_RSP_K_MAC_PATHS_REQ_BAD&t;&t;0x1D
DECL|macro|PI_RSP_K_MAC_T_REQ_BAD
mdefine_line|#define PI_RSP_K_MAC_T_REQ_BAD&t;&t;&t;0x1E
DECL|macro|PI_RSP_K_EMAC_RING_PURGER_BAD
mdefine_line|#define PI_RSP_K_EMAC_RING_PURGER_BAD&t;0x1F
DECL|macro|PI_RSP_K_EMAC_RTOKEN_TIME_BAD
mdefine_line|#define PI_RSP_K_EMAC_RTOKEN_TIME_BAD&t;0x20
DECL|macro|PI_RSP_K_NO_SUCH_ENTRY
mdefine_line|#define PI_RSP_K_NO_SUCH_ENTRY&t;&t;&t;0x21
DECL|macro|PI_RSP_K_T_NOTIFY_BAD
mdefine_line|#define PI_RSP_K_T_NOTIFY_BAD&t;&t;&t;0x22
DECL|macro|PI_RSP_K_TR_MAX_EXP_BAD
mdefine_line|#define PI_RSP_K_TR_MAX_EXP_BAD&t;&t;&t;0x23
DECL|macro|PI_RSP_K_MAC_FRM_ERR_THR_BAD
mdefine_line|#define PI_RSP_K_MAC_FRM_ERR_THR_BAD&t;0x24
DECL|macro|PI_RSP_K_MAX_T_REQ_BAD
mdefine_line|#define PI_RSP_K_MAX_T_REQ_BAD&t;&t;&t;0x25
DECL|macro|PI_RSP_K_FDX_ENB_DIS_BAD
mdefine_line|#define PI_RSP_K_FDX_ENB_DIS_BAD&t;&t;0x26
DECL|macro|PI_RSP_K_ITEM_INDEX_BAD
mdefine_line|#define PI_RSP_K_ITEM_INDEX_BAD&t;&t;&t;0x27
DECL|macro|PI_RSP_K_PORT_ACTION_BAD
mdefine_line|#define PI_RSP_K_PORT_ACTION_BAD&t;&t;0x28
multiline_comment|/* Commonly used structures */
r_typedef
r_struct
multiline_comment|/* Item list */
(brace
DECL|member|item_code
id|PI_UINT32
id|item_code
suffix:semicolon
DECL|member|value
id|PI_UINT32
id|value
suffix:semicolon
DECL|typedef|PI_ITEM_LIST
)brace
id|PI_ITEM_LIST
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* Response header */
(brace
DECL|member|reserved
id|PI_UINT32
id|reserved
suffix:semicolon
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|status
id|PI_UINT32
id|status
suffix:semicolon
DECL|typedef|PI_RSP_HEADER
)brace
id|PI_RSP_HEADER
suffix:semicolon
multiline_comment|/* Start Command */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_START_REQ
)brace
id|PI_CMD_START_REQ
suffix:semicolon
multiline_comment|/* Start Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_START_RSP
)brace
id|PI_CMD_START_RSP
suffix:semicolon
multiline_comment|/* Filters_Set Request */
DECL|macro|PI_CMD_FILTERS_SET_K_ITEMS_MAX
mdefine_line|#define PI_CMD_FILTERS_SET_K_ITEMS_MAX  63&t;&t;/* Fits in a 512 byte buffer */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|item
id|PI_ITEM_LIST
id|item
(braket
id|PI_CMD_FILTERS_SET_K_ITEMS_MAX
)braket
suffix:semicolon
DECL|typedef|PI_CMD_FILTERS_SET_REQ
)brace
id|PI_CMD_FILTERS_SET_REQ
suffix:semicolon
multiline_comment|/* Filters_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_FILTERS_SET_RSP
)brace
id|PI_CMD_FILTERS_SET_RSP
suffix:semicolon
multiline_comment|/* Filters_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_FILTERS_GET_REQ
)brace
id|PI_CMD_FILTERS_GET_REQ
suffix:semicolon
multiline_comment|/* Filters_Get Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|ind_group_prom
id|PI_UINT32
id|ind_group_prom
suffix:semicolon
DECL|member|group_prom
id|PI_UINT32
id|group_prom
suffix:semicolon
DECL|member|broadcast_all
id|PI_UINT32
id|broadcast_all
suffix:semicolon
DECL|member|smt_all
id|PI_UINT32
id|smt_all
suffix:semicolon
DECL|member|smt_user
id|PI_UINT32
id|smt_user
suffix:semicolon
DECL|member|reserved_all
id|PI_UINT32
id|reserved_all
suffix:semicolon
DECL|member|implementor_all
id|PI_UINT32
id|implementor_all
suffix:semicolon
DECL|typedef|PI_CMD_FILTERS_GET_RSP
)brace
id|PI_CMD_FILTERS_GET_RSP
suffix:semicolon
multiline_comment|/* Chars_Set Request */
DECL|macro|PI_CMD_CHARS_SET_K_ITEMS_MAX
mdefine_line|#define PI_CMD_CHARS_SET_K_ITEMS_MAX 42&t;&t;/* Fits in a 512 byte buffer */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
r_struct
multiline_comment|/* Item list */
(brace
DECL|member|item_code
id|PI_UINT32
id|item_code
suffix:semicolon
DECL|member|value
id|PI_UINT32
id|value
suffix:semicolon
DECL|member|item_index
id|PI_UINT32
id|item_index
suffix:semicolon
DECL|member|item
)brace
id|item
(braket
id|PI_CMD_CHARS_SET_K_ITEMS_MAX
)braket
suffix:semicolon
DECL|typedef|PI_CMD_CHARS_SET_REQ
)brace
id|PI_CMD_CHARS_SET_REQ
suffix:semicolon
multiline_comment|/* Chars_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_CHARS_SET_RSP
)brace
id|PI_CMD_CHARS_SET_RSP
suffix:semicolon
multiline_comment|/* SNMP_Set Request */
DECL|macro|PI_CMD_SNMP_SET_K_ITEMS_MAX
mdefine_line|#define PI_CMD_SNMP_SET_K_ITEMS_MAX 42&t;   &t;/* Fits in a 512 byte buffer */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
r_struct
multiline_comment|/* Item list */
(brace
DECL|member|item_code
id|PI_UINT32
id|item_code
suffix:semicolon
DECL|member|value
id|PI_UINT32
id|value
suffix:semicolon
DECL|member|item_index
id|PI_UINT32
id|item_index
suffix:semicolon
DECL|member|item
)brace
id|item
(braket
id|PI_CMD_SNMP_SET_K_ITEMS_MAX
)braket
suffix:semicolon
DECL|typedef|PI_CMD_SNMP_SET_REQ
)brace
id|PI_CMD_SNMP_SET_REQ
suffix:semicolon
multiline_comment|/* SNMP_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_SNMP_SET_RSP
)brace
id|PI_CMD_SNMP_SET_RSP
suffix:semicolon
multiline_comment|/* SMT_MIB_Set Request */
DECL|macro|PI_CMD_SMT_MIB_SET_K_ITEMS_MAX
mdefine_line|#define PI_CMD_SMT_MIB_SET_K_ITEMS_MAX 42&t;/* Max number of items */ 
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
r_struct
(brace
DECL|member|item_code
id|PI_UINT32
id|item_code
suffix:semicolon
DECL|member|value
id|PI_UINT32
id|value
suffix:semicolon
DECL|member|item_index
id|PI_UINT32
id|item_index
suffix:semicolon
DECL|member|item
)brace
id|item
(braket
id|PI_CMD_SMT_MIB_SET_K_ITEMS_MAX
)braket
suffix:semicolon
DECL|typedef|PI_CMD_SMT_MIB_SET_REQ
)brace
id|PI_CMD_SMT_MIB_SET_REQ
suffix:semicolon
multiline_comment|/* SMT_MIB_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_SMT_MIB_SET_RSP
)brace
id|PI_CMD_SMT_MIB_SET_RSP
suffix:semicolon
multiline_comment|/* SMT_MIB_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_SMT_MIB_GET_REQ
)brace
id|PI_CMD_SMT_MIB_GET_REQ
suffix:semicolon
multiline_comment|/* SMT_MIB_Get Response */
r_typedef
r_struct
multiline_comment|/* Refer to ANSI FDDI SMT Rev. 7.3 */
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
multiline_comment|/* SMT GROUP */
DECL|member|smt_station_id
id|PI_STATION_ID
id|smt_station_id
suffix:semicolon
DECL|member|smt_op_version_id
id|PI_UINT32
id|smt_op_version_id
suffix:semicolon
DECL|member|smt_hi_version_id
id|PI_UINT32
id|smt_hi_version_id
suffix:semicolon
DECL|member|smt_lo_version_id
id|PI_UINT32
id|smt_lo_version_id
suffix:semicolon
DECL|member|smt_user_data
id|PI_UINT32
id|smt_user_data
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|smt_mib_version_id
id|PI_UINT32
id|smt_mib_version_id
suffix:semicolon
DECL|member|smt_mac_ct
id|PI_UINT32
id|smt_mac_ct
suffix:semicolon
DECL|member|smt_non_master_ct
id|PI_UINT32
id|smt_non_master_ct
suffix:semicolon
DECL|member|smt_master_ct
id|PI_UINT32
id|smt_master_ct
suffix:semicolon
DECL|member|smt_available_paths
id|PI_UINT32
id|smt_available_paths
suffix:semicolon
DECL|member|smt_config_capabilities
id|PI_UINT32
id|smt_config_capabilities
suffix:semicolon
DECL|member|smt_config_policy
id|PI_UINT32
id|smt_config_policy
suffix:semicolon
DECL|member|smt_connection_policy
id|PI_UINT32
id|smt_connection_policy
suffix:semicolon
DECL|member|smt_t_notify
id|PI_UINT32
id|smt_t_notify
suffix:semicolon
DECL|member|smt_stat_rpt_policy
id|PI_UINT32
id|smt_stat_rpt_policy
suffix:semicolon
DECL|member|smt_trace_max_expiration
id|PI_UINT32
id|smt_trace_max_expiration
suffix:semicolon
DECL|member|smt_bypass_present
id|PI_UINT32
id|smt_bypass_present
suffix:semicolon
DECL|member|smt_ecm_state
id|PI_UINT32
id|smt_ecm_state
suffix:semicolon
DECL|member|smt_cf_state
id|PI_UINT32
id|smt_cf_state
suffix:semicolon
DECL|member|smt_remote_disconnect_flag
id|PI_UINT32
id|smt_remote_disconnect_flag
suffix:semicolon
DECL|member|smt_station_status
id|PI_UINT32
id|smt_station_status
suffix:semicolon
DECL|member|smt_peer_wrap_flag
id|PI_UINT32
id|smt_peer_wrap_flag
suffix:semicolon
DECL|member|smt_msg_time_stamp
id|PI_CNTR
id|smt_msg_time_stamp
suffix:semicolon
DECL|member|smt_transition_time_stamp
id|PI_CNTR
id|smt_transition_time_stamp
suffix:semicolon
multiline_comment|/* MAC GROUP */
DECL|member|mac_frame_status_functions
id|PI_UINT32
id|mac_frame_status_functions
suffix:semicolon
DECL|member|mac_t_max_capability
id|PI_UINT32
id|mac_t_max_capability
suffix:semicolon
DECL|member|mac_tvx_capability
id|PI_UINT32
id|mac_tvx_capability
suffix:semicolon
DECL|member|mac_available_paths
id|PI_UINT32
id|mac_available_paths
suffix:semicolon
DECL|member|mac_current_path
id|PI_UINT32
id|mac_current_path
suffix:semicolon
DECL|member|mac_upstream_nbr
id|PI_LAN_ADDR
id|mac_upstream_nbr
suffix:semicolon
DECL|member|mac_downstream_nbr
id|PI_LAN_ADDR
id|mac_downstream_nbr
suffix:semicolon
DECL|member|mac_old_upstream_nbr
id|PI_LAN_ADDR
id|mac_old_upstream_nbr
suffix:semicolon
DECL|member|mac_old_downstream_nbr
id|PI_LAN_ADDR
id|mac_old_downstream_nbr
suffix:semicolon
DECL|member|mac_dup_address_test
id|PI_UINT32
id|mac_dup_address_test
suffix:semicolon
DECL|member|mac_requested_paths
id|PI_UINT32
id|mac_requested_paths
suffix:semicolon
DECL|member|mac_downstream_port_type
id|PI_UINT32
id|mac_downstream_port_type
suffix:semicolon
DECL|member|mac_smt_address
id|PI_LAN_ADDR
id|mac_smt_address
suffix:semicolon
DECL|member|mac_t_req
id|PI_UINT32
id|mac_t_req
suffix:semicolon
DECL|member|mac_t_neg
id|PI_UINT32
id|mac_t_neg
suffix:semicolon
DECL|member|mac_t_max
id|PI_UINT32
id|mac_t_max
suffix:semicolon
DECL|member|mac_tvx_value
id|PI_UINT32
id|mac_tvx_value
suffix:semicolon
DECL|member|mac_frame_error_threshold
id|PI_UINT32
id|mac_frame_error_threshold
suffix:semicolon
DECL|member|mac_frame_error_ratio
id|PI_UINT32
id|mac_frame_error_ratio
suffix:semicolon
DECL|member|mac_rmt_state
id|PI_UINT32
id|mac_rmt_state
suffix:semicolon
DECL|member|mac_da_flag
id|PI_UINT32
id|mac_da_flag
suffix:semicolon
DECL|member|mac_unda_flag
id|PI_UINT32
id|mac_unda_flag
suffix:semicolon
DECL|member|mac_frame_error_flag
id|PI_UINT32
id|mac_frame_error_flag
suffix:semicolon
DECL|member|mac_ma_unitdata_available
id|PI_UINT32
id|mac_ma_unitdata_available
suffix:semicolon
DECL|member|mac_hardware_present
id|PI_UINT32
id|mac_hardware_present
suffix:semicolon
DECL|member|mac_ma_unitdata_enable
id|PI_UINT32
id|mac_ma_unitdata_enable
suffix:semicolon
multiline_comment|/* PATH GROUP */
DECL|member|path_configuration
id|PI_UINT32
id|path_configuration
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|path_tvx_lower_bound
id|PI_UINT32
id|path_tvx_lower_bound
suffix:semicolon
DECL|member|path_t_max_lower_bound
id|PI_UINT32
id|path_t_max_lower_bound
suffix:semicolon
DECL|member|path_max_t_req
id|PI_UINT32
id|path_max_t_req
suffix:semicolon
multiline_comment|/* PORT GROUP */
DECL|member|port_my_type
id|PI_UINT32
id|port_my_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_neighbor_type
id|PI_UINT32
id|port_neighbor_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_connection_policies
id|PI_UINT32
id|port_connection_policies
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_mac_indicated
id|PI_UINT32
id|port_mac_indicated
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_current_path
id|PI_UINT32
id|port_current_path
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_requested_paths
id|PI_UINT32
id|port_requested_paths
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_mac_placement
id|PI_UINT32
id|port_mac_placement
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_available_paths
id|PI_UINT32
id|port_available_paths
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pmd_class
id|PI_UINT32
id|port_pmd_class
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_connection_capabilities
id|PI_UINT32
id|port_connection_capabilities
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_bs_flag
id|PI_UINT32
id|port_bs_flag
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_estimate
id|PI_UINT32
id|port_ler_estimate
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_cutoff
id|PI_UINT32
id|port_ler_cutoff
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_alarm
id|PI_UINT32
id|port_ler_alarm
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_connect_state
id|PI_UINT32
id|port_connect_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pcm_state
id|PI_UINT32
id|port_pcm_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pc_withhold
id|PI_UINT32
id|port_pc_withhold
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_flag
id|PI_UINT32
id|port_ler_flag
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_hardware_present
id|PI_UINT32
id|port_hardware_present
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/* GROUP for things that were added later, so must be at the end. */
DECL|member|path_ring_latency
id|PI_CNTR
id|path_ring_latency
suffix:semicolon
DECL|typedef|PI_CMD_SMT_MIB_GET_RSP
)brace
id|PI_CMD_SMT_MIB_GET_RSP
suffix:semicolon
multiline_comment|/*&n; *  Item and group code definitions for SMT 7.3 mandatory objects.  These&n; *  definitions are to be used as appropriate in SMT_MIB_SET commands and&n; *  certain host-sent SMT frames such as PMF Get and Set requests.  The&n; *  codes have been taken from the MIB summary section of ANSI SMT 7.3.&n; */
DECL|macro|PI_GRP_K_SMT_STATION_ID
mdefine_line|#define PI_GRP_K_SMT_STATION_ID&t;&t;&t;0x100A
DECL|macro|PI_ITEM_K_SMT_STATION_ID
mdefine_line|#define PI_ITEM_K_SMT_STATION_ID&t;&t;0x100B
DECL|macro|PI_ITEM_K_SMT_OP_VERS_ID
mdefine_line|#define PI_ITEM_K_SMT_OP_VERS_ID&t;&t;0x100D
DECL|macro|PI_ITEM_K_SMT_HI_VERS_ID
mdefine_line|#define PI_ITEM_K_SMT_HI_VERS_ID&t;&t;0x100E
DECL|macro|PI_ITEM_K_SMT_LO_VERS_ID
mdefine_line|#define PI_ITEM_K_SMT_LO_VERS_ID&t;&t;0x100F
DECL|macro|PI_ITEM_K_SMT_USER_DATA
mdefine_line|#define PI_ITEM_K_SMT_USER_DATA&t;&t;&t;0x1011
DECL|macro|PI_ITEM_K_SMT_MIB_VERS_ID
mdefine_line|#define PI_ITEM_K_SMT_MIB_VERS_ID&t;  &t;0x1012
DECL|macro|PI_GRP_K_SMT_STATION_CONFIG
mdefine_line|#define PI_GRP_K_SMT_STATION_CONFIG&t;&t;0x1014
DECL|macro|PI_ITEM_K_SMT_MAC_CT
mdefine_line|#define PI_ITEM_K_SMT_MAC_CT&t;&t;&t;0x1015
DECL|macro|PI_ITEM_K_SMT_NON_MASTER_CT
mdefine_line|#define PI_ITEM_K_SMT_NON_MASTER_CT&t;&t;0x1016
DECL|macro|PI_ITEM_K_SMT_MASTER_CT
mdefine_line|#define PI_ITEM_K_SMT_MASTER_CT&t;&t;&t;0x1017
DECL|macro|PI_ITEM_K_SMT_AVAIL_PATHS
mdefine_line|#define PI_ITEM_K_SMT_AVAIL_PATHS&t;&t;0x1018
DECL|macro|PI_ITEM_K_SMT_CONFIG_CAPS
mdefine_line|#define PI_ITEM_K_SMT_CONFIG_CAPS&t;&t;0x1019
DECL|macro|PI_ITEM_K_SMT_CONFIG_POL
mdefine_line|#define PI_ITEM_K_SMT_CONFIG_POL&t;&t;0x101A
DECL|macro|PI_ITEM_K_SMT_CONN_POL
mdefine_line|#define PI_ITEM_K_SMT_CONN_POL&t;&t;&t;0x101B
DECL|macro|PI_ITEM_K_SMT_T_NOTIFY
mdefine_line|#define PI_ITEM_K_SMT_T_NOTIFY&t;&t;&t;0x101D
DECL|macro|PI_ITEM_K_SMT_STAT_POL
mdefine_line|#define PI_ITEM_K_SMT_STAT_POL&t;&t;&t;0x101E
DECL|macro|PI_ITEM_K_SMT_TR_MAX_EXP
mdefine_line|#define PI_ITEM_K_SMT_TR_MAX_EXP&t;&t;0x101F
DECL|macro|PI_ITEM_K_SMT_PORT_INDEXES
mdefine_line|#define PI_ITEM_K_SMT_PORT_INDEXES&t;&t;0x1020
DECL|macro|PI_ITEM_K_SMT_MAC_INDEXES
mdefine_line|#define PI_ITEM_K_SMT_MAC_INDEXES&t;&t;0x1021
DECL|macro|PI_ITEM_K_SMT_BYPASS_PRESENT
mdefine_line|#define PI_ITEM_K_SMT_BYPASS_PRESENT&t;0x1022
DECL|macro|PI_GRP_K_SMT_STATUS
mdefine_line|#define PI_GRP_K_SMT_STATUS&t;&t;&t;&t;0x1028
DECL|macro|PI_ITEM_K_SMT_ECM_STATE
mdefine_line|#define PI_ITEM_K_SMT_ECM_STATE&t;&t;&t;0x1029
DECL|macro|PI_ITEM_K_SMT_CF_STATE
mdefine_line|#define PI_ITEM_K_SMT_CF_STATE&t;&t; &t;0x102A
DECL|macro|PI_ITEM_K_SMT_REM_DISC_FLAG
mdefine_line|#define PI_ITEM_K_SMT_REM_DISC_FLAG&t;&t;0x102C
DECL|macro|PI_ITEM_K_SMT_STATION_STATUS
mdefine_line|#define PI_ITEM_K_SMT_STATION_STATUS&t;0x102D
DECL|macro|PI_ITEM_K_SMT_PEER_WRAP_FLAG
mdefine_line|#define PI_ITEM_K_SMT_PEER_WRAP_FLAG&t;0x102E
DECL|macro|PI_GRP_K_SMT_MIB_OPERATION
mdefine_line|#define PI_GRP_K_SMT_MIB_OPERATION&t; &t;0x1032
DECL|macro|PI_ITEM_K_SMT_MSG_TIME_STAMP
mdefine_line|#define PI_ITEM_K_SMT_MSG_TIME_STAMP &t;0x1033
DECL|macro|PI_ITEM_K_SMT_TRN_TIME_STAMP
mdefine_line|#define PI_ITEM_K_SMT_TRN_TIME_STAMP &t;0x1034
DECL|macro|PI_ITEM_K_SMT_STATION_ACT
mdefine_line|#define PI_ITEM_K_SMT_STATION_ACT&t;&t;0x103C
DECL|macro|PI_GRP_K_MAC_CAPABILITIES
mdefine_line|#define PI_GRP_K_MAC_CAPABILITIES&t;  &t;0x200A
DECL|macro|PI_ITEM_K_MAC_FRM_STAT_FUNC
mdefine_line|#define PI_ITEM_K_MAC_FRM_STAT_FUNC&t;&t;0x200B
DECL|macro|PI_ITEM_K_MAC_T_MAX_CAP
mdefine_line|#define PI_ITEM_K_MAC_T_MAX_CAP&t;&t;&t;0x200D
DECL|macro|PI_ITEM_K_MAC_TVX_CAP
mdefine_line|#define PI_ITEM_K_MAC_TVX_CAP&t;&t;  &t;0x200E
DECL|macro|PI_GRP_K_MAC_CONFIG
mdefine_line|#define PI_GRP_K_MAC_CONFIG&t;&t;&t;&t;0x2014
DECL|macro|PI_ITEM_K_MAC_AVAIL_PATHS
mdefine_line|#define PI_ITEM_K_MAC_AVAIL_PATHS&t;  &t;0x2016
DECL|macro|PI_ITEM_K_MAC_CURRENT_PATH
mdefine_line|#define PI_ITEM_K_MAC_CURRENT_PATH&t; &t;0x2017
DECL|macro|PI_ITEM_K_MAC_UP_NBR
mdefine_line|#define PI_ITEM_K_MAC_UP_NBR&t;&t;&t;0x2018
DECL|macro|PI_ITEM_K_MAC_DOWN_NBR
mdefine_line|#define PI_ITEM_K_MAC_DOWN_NBR&t;&t;&t;0x2019
DECL|macro|PI_ITEM_K_MAC_OLD_UP_NBR
mdefine_line|#define PI_ITEM_K_MAC_OLD_UP_NBR&t; &t;0x201A
DECL|macro|PI_ITEM_K_MAC_OLD_DOWN_NBR
mdefine_line|#define PI_ITEM_K_MAC_OLD_DOWN_NBR&t; &t;0x201B
DECL|macro|PI_ITEM_K_MAC_DUP_ADDR_TEST
mdefine_line|#define PI_ITEM_K_MAC_DUP_ADDR_TEST&t;&t;0x201D
DECL|macro|PI_ITEM_K_MAC_REQ_PATHS
mdefine_line|#define PI_ITEM_K_MAC_REQ_PATHS&t;&t;&t;0x2020
DECL|macro|PI_ITEM_K_MAC_DOWN_PORT_TYPE
mdefine_line|#define PI_ITEM_K_MAC_DOWN_PORT_TYPE   &t;0x2021
DECL|macro|PI_ITEM_K_MAC_INDEX
mdefine_line|#define PI_ITEM_K_MAC_INDEX&t;&t;&t;&t;0x2022
DECL|macro|PI_GRP_K_MAC_ADDRESS
mdefine_line|#define PI_GRP_K_MAC_ADDRESS&t;&t;&t;0x2028
DECL|macro|PI_ITEM_K_MAC_SMT_ADDRESS
mdefine_line|#define PI_ITEM_K_MAC_SMT_ADDRESS&t;&t;0x2029
DECL|macro|PI_GRP_K_MAC_OPERATION
mdefine_line|#define PI_GRP_K_MAC_OPERATION&t;&t;&t;0x2032
DECL|macro|PI_ITEM_K_MAC_TREQ
mdefine_line|#define PI_ITEM_K_MAC_TREQ&t;&t;&t;&t;0x2033
DECL|macro|PI_ITEM_K_MAC_TNEG
mdefine_line|#define PI_ITEM_K_MAC_TNEG&t;&t;&t;&t;0x2034
DECL|macro|PI_ITEM_K_MAC_TMAX
mdefine_line|#define PI_ITEM_K_MAC_TMAX&t;&t;&t;&t;0x2035
DECL|macro|PI_ITEM_K_MAC_TVX_VALUE
mdefine_line|#define PI_ITEM_K_MAC_TVX_VALUE&t;&t;&t;0x2036
DECL|macro|PI_GRP_K_MAC_COUNTERS
mdefine_line|#define PI_GRP_K_MAC_COUNTERS&t;&t;&t;0x2046
DECL|macro|PI_ITEM_K_MAC_FRAME_CT
mdefine_line|#define PI_ITEM_K_MAC_FRAME_CT&t;&t;&t;0x2047
DECL|macro|PI_ITEM_K_MAC_COPIED_CT
mdefine_line|#define PI_ITEM_K_MAC_COPIED_CT&t;&t;&t;0x2048
DECL|macro|PI_ITEM_K_MAC_TRANSMIT_CT
mdefine_line|#define PI_ITEM_K_MAC_TRANSMIT_CT&t;&t;0x2049
DECL|macro|PI_ITEM_K_MAC_ERROR_CT
mdefine_line|#define PI_ITEM_K_MAC_ERROR_CT&t;&t;&t;0x2051
DECL|macro|PI_ITEM_K_MAC_LOST_CT
mdefine_line|#define PI_ITEM_K_MAC_LOST_CT&t;&t;&t;0x2052
DECL|macro|PI_GRP_K_MAC_FRM_ERR_COND
mdefine_line|#define PI_GRP_K_MAC_FRM_ERR_COND&t;&t;0x205A
DECL|macro|PI_ITEM_K_MAC_FRM_ERR_THR
mdefine_line|#define PI_ITEM_K_MAC_FRM_ERR_THR&t;&t;0x205F
DECL|macro|PI_ITEM_K_MAC_FRM_ERR_RAT
mdefine_line|#define PI_ITEM_K_MAC_FRM_ERR_RAT&t;&t;0x2060
DECL|macro|PI_GRP_K_MAC_STATUS
mdefine_line|#define PI_GRP_K_MAC_STATUS&t;&t;&t;&t;0x206E
DECL|macro|PI_ITEM_K_MAC_RMT_STATE
mdefine_line|#define PI_ITEM_K_MAC_RMT_STATE&t;&t;&t;0x206F
DECL|macro|PI_ITEM_K_MAC_DA_FLAG
mdefine_line|#define PI_ITEM_K_MAC_DA_FLAG&t;&t;&t;0x2070
DECL|macro|PI_ITEM_K_MAC_UNDA_FLAG
mdefine_line|#define PI_ITEM_K_MAC_UNDA_FLAG&t;&t;&t;0x2071
DECL|macro|PI_ITEM_K_MAC_FRM_ERR_FLAG
mdefine_line|#define PI_ITEM_K_MAC_FRM_ERR_FLAG&t;&t;0x2072
DECL|macro|PI_ITEM_K_MAC_MA_UNIT_AVAIL
mdefine_line|#define PI_ITEM_K_MAC_MA_UNIT_AVAIL&t;&t;0x2074
DECL|macro|PI_ITEM_K_MAC_HW_PRESENT
mdefine_line|#define PI_ITEM_K_MAC_HW_PRESENT&t;&t;0x2075
DECL|macro|PI_ITEM_K_MAC_MA_UNIT_ENAB
mdefine_line|#define PI_ITEM_K_MAC_MA_UNIT_ENAB&t;&t;0x2076
DECL|macro|PI_GRP_K_PATH_CONFIG
mdefine_line|#define PI_GRP_K_PATH_CONFIG&t;&t;&t;0x320A
DECL|macro|PI_ITEM_K_PATH_INDEX
mdefine_line|#define PI_ITEM_K_PATH_INDEX&t;&t;&t;0x320B
DECL|macro|PI_ITEM_K_PATH_CONFIGURATION
mdefine_line|#define PI_ITEM_K_PATH_CONFIGURATION &t;0x3212
DECL|macro|PI_ITEM_K_PATH_TVX_LB
mdefine_line|#define PI_ITEM_K_PATH_TVX_LB&t;&t;&t;0x3215
DECL|macro|PI_ITEM_K_PATH_T_MAX_LB
mdefine_line|#define PI_ITEM_K_PATH_T_MAX_LB&t;&t;&t;0x3216
DECL|macro|PI_ITEM_K_PATH_MAX_T_REQ
mdefine_line|#define PI_ITEM_K_PATH_MAX_T_REQ&t;&t;0x3217
DECL|macro|PI_GRP_K_PORT_CONFIG
mdefine_line|#define PI_GRP_K_PORT_CONFIG&t;&t;&t;0x400A
DECL|macro|PI_ITEM_K_PORT_MY_TYPE
mdefine_line|#define PI_ITEM_K_PORT_MY_TYPE&t;&t;&t;0x400C
DECL|macro|PI_ITEM_K_PORT_NBR_TYPE
mdefine_line|#define PI_ITEM_K_PORT_NBR_TYPE&t;&t;&t;0x400D
DECL|macro|PI_ITEM_K_PORT_CONN_POLS
mdefine_line|#define PI_ITEM_K_PORT_CONN_POLS&t;&t;0x400E
DECL|macro|PI_ITEM_K_PORT_MAC_INDICATED
mdefine_line|#define PI_ITEM_K_PORT_MAC_INDICATED  &t;0x400F
DECL|macro|PI_ITEM_K_PORT_CURRENT_PATH
mdefine_line|#define PI_ITEM_K_PORT_CURRENT_PATH&t;&t;0x4010
DECL|macro|PI_ITEM_K_PORT_REQ_PATHS
mdefine_line|#define PI_ITEM_K_PORT_REQ_PATHS&t;&t;0x4011
DECL|macro|PI_ITEM_K_PORT_MAC_PLACEMENT
mdefine_line|#define PI_ITEM_K_PORT_MAC_PLACEMENT &t;0x4012
DECL|macro|PI_ITEM_K_PORT_AVAIL_PATHS
mdefine_line|#define PI_ITEM_K_PORT_AVAIL_PATHS&t;&t;0x4013
DECL|macro|PI_ITEM_K_PORT_PMD_CLASS
mdefine_line|#define PI_ITEM_K_PORT_PMD_CLASS&t;&t;0x4016
DECL|macro|PI_ITEM_K_PORT_CONN_CAPS
mdefine_line|#define PI_ITEM_K_PORT_CONN_CAPS&t;&t;0x4017
DECL|macro|PI_ITEM_K_PORT_INDEX
mdefine_line|#define PI_ITEM_K_PORT_INDEX&t;&t;&t;0x401D
DECL|macro|PI_GRP_K_PORT_OPERATION
mdefine_line|#define PI_GRP_K_PORT_OPERATION&t;&t;&t;0x401E
DECL|macro|PI_ITEM_K_PORT_BS_FLAG
mdefine_line|#define PI_ITEM_K_PORT_BS_FLAG&t;&t; &t;0x4021
DECL|macro|PI_GRP_K_PORT_ERR_CNTRS
mdefine_line|#define PI_GRP_K_PORT_ERR_CNTRS&t;&t;&t;0x4028
DECL|macro|PI_ITEM_K_PORT_LCT_FAIL_CT
mdefine_line|#define PI_ITEM_K_PORT_LCT_FAIL_CT&t; &t;0x402A
DECL|macro|PI_GRP_K_PORT_LER
mdefine_line|#define PI_GRP_K_PORT_LER&t;&t;&t;  &t;0x4032
DECL|macro|PI_ITEM_K_PORT_LER_ESTIMATE
mdefine_line|#define PI_ITEM_K_PORT_LER_ESTIMATE&t;&t;0x4033
DECL|macro|PI_ITEM_K_PORT_LEM_REJ_CT
mdefine_line|#define PI_ITEM_K_PORT_LEM_REJ_CT&t;&t;0x4034
DECL|macro|PI_ITEM_K_PORT_LEM_CT
mdefine_line|#define PI_ITEM_K_PORT_LEM_CT&t;&t;&t;0x4035
DECL|macro|PI_ITEM_K_PORT_LER_CUTOFF
mdefine_line|#define PI_ITEM_K_PORT_LER_CUTOFF&t;&t;0x403A
DECL|macro|PI_ITEM_K_PORT_LER_ALARM
mdefine_line|#define PI_ITEM_K_PORT_LER_ALARM&t;&t;0x403B
DECL|macro|PI_GRP_K_PORT_STATUS
mdefine_line|#define PI_GRP_K_PORT_STATUS&t;&t;&t;0x403C
DECL|macro|PI_ITEM_K_PORT_CONNECT_STATE
mdefine_line|#define PI_ITEM_K_PORT_CONNECT_STATE&t;0x403D
DECL|macro|PI_ITEM_K_PORT_PCM_STATE
mdefine_line|#define PI_ITEM_K_PORT_PCM_STATE&t;&t;0x403E
DECL|macro|PI_ITEM_K_PORT_PC_WITHHOLD
mdefine_line|#define PI_ITEM_K_PORT_PC_WITHHOLD&t;&t;0x403F
DECL|macro|PI_ITEM_K_PORT_LER_FLAG
mdefine_line|#define PI_ITEM_K_PORT_LER_FLAG&t;&t;&t;0x4040
DECL|macro|PI_ITEM_K_PORT_HW_PRESENT
mdefine_line|#define PI_ITEM_K_PORT_HW_PRESENT&t;&t;0x4041
DECL|macro|PI_ITEM_K_PORT_ACT
mdefine_line|#define PI_ITEM_K_PORT_ACT&t;&t;&t;&t;0x4046
multiline_comment|/* Addr_Filter_Set Request */
DECL|macro|PI_CMD_ADDR_FILTER_K_SIZE
mdefine_line|#define PI_CMD_ADDR_FILTER_K_SIZE   62
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|entry
id|PI_LAN_ADDR
id|entry
(braket
id|PI_CMD_ADDR_FILTER_K_SIZE
)braket
suffix:semicolon
DECL|typedef|PI_CMD_ADDR_FILTER_SET_REQ
)brace
id|PI_CMD_ADDR_FILTER_SET_REQ
suffix:semicolon
multiline_comment|/* Addr_Filter_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_ADDR_FILTER_SET_RSP
)brace
id|PI_CMD_ADDR_FILTER_SET_RSP
suffix:semicolon
multiline_comment|/* Addr_Filter_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_ADDR_FILTER_GET_REQ
)brace
id|PI_CMD_ADDR_FILTER_GET_REQ
suffix:semicolon
multiline_comment|/* Addr_Filter_Get Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|entry
id|PI_LAN_ADDR
id|entry
(braket
id|PI_CMD_ADDR_FILTER_K_SIZE
)braket
suffix:semicolon
DECL|typedef|PI_CMD_ADDR_FILTER_GET_RSP
)brace
id|PI_CMD_ADDR_FILTER_GET_RSP
suffix:semicolon
multiline_comment|/* Status_Chars_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_STATUS_CHARS_GET_REQ
)brace
id|PI_CMD_STATUS_CHARS_GET_REQ
suffix:semicolon
multiline_comment|/* Status_Chars_Get Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|station_id
id|PI_STATION_ID
id|station_id
suffix:semicolon
multiline_comment|/* Station */
DECL|member|station_type
id|PI_UINT32
id|station_type
suffix:semicolon
DECL|member|smt_ver_id
id|PI_UINT32
id|smt_ver_id
suffix:semicolon
DECL|member|smt_ver_id_max
id|PI_UINT32
id|smt_ver_id_max
suffix:semicolon
DECL|member|smt_ver_id_min
id|PI_UINT32
id|smt_ver_id_min
suffix:semicolon
DECL|member|station_state
id|PI_UINT32
id|station_state
suffix:semicolon
DECL|member|link_addr
id|PI_LAN_ADDR
id|link_addr
suffix:semicolon
multiline_comment|/* Link */
DECL|member|t_req
id|PI_UINT32
id|t_req
suffix:semicolon
DECL|member|tvx
id|PI_UINT32
id|tvx
suffix:semicolon
DECL|member|token_timeout
id|PI_UINT32
id|token_timeout
suffix:semicolon
DECL|member|purger_enb
id|PI_UINT32
id|purger_enb
suffix:semicolon
DECL|member|link_state
id|PI_UINT32
id|link_state
suffix:semicolon
DECL|member|tneg
id|PI_UINT32
id|tneg
suffix:semicolon
DECL|member|dup_addr_flag
id|PI_UINT32
id|dup_addr_flag
suffix:semicolon
DECL|member|una
id|PI_LAN_ADDR
id|una
suffix:semicolon
DECL|member|una_old
id|PI_LAN_ADDR
id|una_old
suffix:semicolon
DECL|member|un_dup_addr_flag
id|PI_UINT32
id|un_dup_addr_flag
suffix:semicolon
DECL|member|dna
id|PI_LAN_ADDR
id|dna
suffix:semicolon
DECL|member|dna_old
id|PI_LAN_ADDR
id|dna_old
suffix:semicolon
DECL|member|purger_state
id|PI_UINT32
id|purger_state
suffix:semicolon
DECL|member|fci_mode
id|PI_UINT32
id|fci_mode
suffix:semicolon
DECL|member|error_reason
id|PI_UINT32
id|error_reason
suffix:semicolon
DECL|member|loopback
id|PI_UINT32
id|loopback
suffix:semicolon
DECL|member|ring_latency
id|PI_UINT32
id|ring_latency
suffix:semicolon
DECL|member|last_dir_beacon_sa
id|PI_LAN_ADDR
id|last_dir_beacon_sa
suffix:semicolon
DECL|member|last_dir_beacon_una
id|PI_LAN_ADDR
id|last_dir_beacon_una
suffix:semicolon
DECL|member|phy_type
id|PI_UINT32
id|phy_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/* Phy */
DECL|member|pmd_type
id|PI_UINT32
id|pmd_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|lem_threshold
id|PI_UINT32
id|lem_threshold
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|phy_state
id|PI_UINT32
id|phy_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|nbor_phy_type
id|PI_UINT32
id|nbor_phy_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|link_error_est
id|PI_UINT32
id|link_error_est
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|broken_reason
id|PI_UINT32
id|broken_reason
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|reject_reason
id|PI_UINT32
id|reject_reason
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|cntr_interval
id|PI_UINT32
id|cntr_interval
suffix:semicolon
multiline_comment|/* Miscellaneous */
DECL|member|module_rev
id|PI_UINT32
id|module_rev
suffix:semicolon
DECL|member|firmware_rev
id|PI_UINT32
id|firmware_rev
suffix:semicolon
DECL|member|mop_device_type
id|PI_UINT32
id|mop_device_type
suffix:semicolon
DECL|member|phy_led
id|PI_UINT32
id|phy_led
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|flush_time
id|PI_UINT32
id|flush_time
suffix:semicolon
DECL|typedef|PI_CMD_STATUS_CHARS_GET_RSP
)brace
id|PI_CMD_STATUS_CHARS_GET_RSP
suffix:semicolon
multiline_comment|/* FDDI_MIB_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_FDDI_MIB_GET_REQ
)brace
id|PI_CMD_FDDI_MIB_GET_REQ
suffix:semicolon
multiline_comment|/* FDDI_MIB_Get Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
multiline_comment|/* SMT GROUP */
DECL|member|smt_station_id
id|PI_STATION_ID
id|smt_station_id
suffix:semicolon
DECL|member|smt_op_version_id
id|PI_UINT32
id|smt_op_version_id
suffix:semicolon
DECL|member|smt_hi_version_id
id|PI_UINT32
id|smt_hi_version_id
suffix:semicolon
DECL|member|smt_lo_version_id
id|PI_UINT32
id|smt_lo_version_id
suffix:semicolon
DECL|member|smt_mac_ct
id|PI_UINT32
id|smt_mac_ct
suffix:semicolon
DECL|member|smt_non_master_ct
id|PI_UINT32
id|smt_non_master_ct
suffix:semicolon
DECL|member|smt_master_ct
id|PI_UINT32
id|smt_master_ct
suffix:semicolon
DECL|member|smt_paths_available
id|PI_UINT32
id|smt_paths_available
suffix:semicolon
DECL|member|smt_config_capabilities
id|PI_UINT32
id|smt_config_capabilities
suffix:semicolon
DECL|member|smt_config_policy
id|PI_UINT32
id|smt_config_policy
suffix:semicolon
DECL|member|smt_connection_policy
id|PI_UINT32
id|smt_connection_policy
suffix:semicolon
DECL|member|smt_t_notify
id|PI_UINT32
id|smt_t_notify
suffix:semicolon
DECL|member|smt_status_reporting
id|PI_UINT32
id|smt_status_reporting
suffix:semicolon
DECL|member|smt_ecm_state
id|PI_UINT32
id|smt_ecm_state
suffix:semicolon
DECL|member|smt_cf_state
id|PI_UINT32
id|smt_cf_state
suffix:semicolon
DECL|member|smt_hold_state
id|PI_UINT32
id|smt_hold_state
suffix:semicolon
DECL|member|smt_remote_disconnect_flag
id|PI_UINT32
id|smt_remote_disconnect_flag
suffix:semicolon
DECL|member|smt_station_action
id|PI_UINT32
id|smt_station_action
suffix:semicolon
multiline_comment|/* MAC GROUP */
DECL|member|mac_frame_status_capabilities
id|PI_UINT32
id|mac_frame_status_capabilities
suffix:semicolon
DECL|member|mac_t_max_greatest_lower_bound
id|PI_UINT32
id|mac_t_max_greatest_lower_bound
suffix:semicolon
DECL|member|mac_tvx_greatest_lower_bound
id|PI_UINT32
id|mac_tvx_greatest_lower_bound
suffix:semicolon
DECL|member|mac_paths_available
id|PI_UINT32
id|mac_paths_available
suffix:semicolon
DECL|member|mac_current_path
id|PI_UINT32
id|mac_current_path
suffix:semicolon
DECL|member|mac_upstream_nbr
id|PI_LAN_ADDR
id|mac_upstream_nbr
suffix:semicolon
DECL|member|mac_old_upstream_nbr
id|PI_LAN_ADDR
id|mac_old_upstream_nbr
suffix:semicolon
DECL|member|mac_dup_addr_test
id|PI_UINT32
id|mac_dup_addr_test
suffix:semicolon
DECL|member|mac_paths_requested
id|PI_UINT32
id|mac_paths_requested
suffix:semicolon
DECL|member|mac_downstream_port_type
id|PI_UINT32
id|mac_downstream_port_type
suffix:semicolon
DECL|member|mac_smt_address
id|PI_LAN_ADDR
id|mac_smt_address
suffix:semicolon
DECL|member|mac_t_req
id|PI_UINT32
id|mac_t_req
suffix:semicolon
DECL|member|mac_t_neg
id|PI_UINT32
id|mac_t_neg
suffix:semicolon
DECL|member|mac_t_max
id|PI_UINT32
id|mac_t_max
suffix:semicolon
DECL|member|mac_tvx_value
id|PI_UINT32
id|mac_tvx_value
suffix:semicolon
DECL|member|mac_t_min
id|PI_UINT32
id|mac_t_min
suffix:semicolon
DECL|member|mac_current_frame_status
id|PI_UINT32
id|mac_current_frame_status
suffix:semicolon
multiline_comment|/*&t;&t;&t;  &t;mac_frame_cts &t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;mac_error_cts &t;&t;&t;*/
multiline_comment|/* &t;&t;   &t;&t;mac_lost_cts &t;&t;&t;*/
DECL|member|mac_frame_error_threshold
id|PI_UINT32
id|mac_frame_error_threshold
suffix:semicolon
DECL|member|mac_frame_error_ratio
id|PI_UINT32
id|mac_frame_error_ratio
suffix:semicolon
DECL|member|mac_rmt_state
id|PI_UINT32
id|mac_rmt_state
suffix:semicolon
DECL|member|mac_da_flag
id|PI_UINT32
id|mac_da_flag
suffix:semicolon
DECL|member|mac_una_da_flag
id|PI_UINT32
id|mac_una_da_flag
suffix:semicolon
DECL|member|mac_frame_condition
id|PI_UINT32
id|mac_frame_condition
suffix:semicolon
DECL|member|mac_chip_set
id|PI_UINT32
id|mac_chip_set
suffix:semicolon
DECL|member|mac_action
id|PI_UINT32
id|mac_action
suffix:semicolon
multiline_comment|/* PATH GROUP =&gt; Does not need to be implemented */
multiline_comment|/* PORT GROUP */
DECL|member|port_pc_type
id|PI_UINT32
id|port_pc_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pc_neighbor
id|PI_UINT32
id|port_pc_neighbor
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_connection_policies
id|PI_UINT32
id|port_connection_policies
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_remote_mac_indicated
id|PI_UINT32
id|port_remote_mac_indicated
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ce_state
id|PI_UINT32
id|port_ce_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_paths_requested
id|PI_UINT32
id|port_paths_requested
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_mac_placement
id|PI_UINT32
id|port_mac_placement
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_available_paths
id|PI_UINT32
id|port_available_paths
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_mac_loop_time
id|PI_UINT32
id|port_mac_loop_time
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_tb_max
id|PI_UINT32
id|port_tb_max
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_bs_flag
id|PI_UINT32
id|port_bs_flag
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;port_lct_fail_cts[PI_PHY_K_MAX];&t;*/
DECL|member|port_ler_estimate
id|PI_UINT32
id|port_ler_estimate
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;port_lem_reject_cts[PI_PHY_K_MAX];&t;*/
multiline_comment|/*&t;&t;&t;&t;port_lem_cts[PI_PHY_K_MAX];&t;&t;*/
DECL|member|port_ler_cutoff
id|PI_UINT32
id|port_ler_cutoff
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_alarm
id|PI_UINT32
id|port_ler_alarm
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_connect_state
id|PI_UINT32
id|port_connect_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pcm_state
id|PI_UINT32
id|port_pcm_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_pc_withhold
id|PI_UINT32
id|port_pc_withhold
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_ler_condition
id|PI_UINT32
id|port_ler_condition
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_chip_set
id|PI_UINT32
id|port_chip_set
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|port_action
id|PI_UINT32
id|port_action
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/* ATTACHMENT GROUP */
DECL|member|attachment_class
id|PI_UINT32
id|attachment_class
suffix:semicolon
DECL|member|attachment_ob_present
id|PI_UINT32
id|attachment_ob_present
suffix:semicolon
DECL|member|attachment_imax_expiration
id|PI_UINT32
id|attachment_imax_expiration
suffix:semicolon
DECL|member|attachment_inserted_status
id|PI_UINT32
id|attachment_inserted_status
suffix:semicolon
DECL|member|attachment_insert_policy
id|PI_UINT32
id|attachment_insert_policy
suffix:semicolon
multiline_comment|/* CHIP SET GROUP =&gt; Does not need to be implemented */
DECL|typedef|PI_CMD_FDDI_MIB_GET_RSP
)brace
id|PI_CMD_FDDI_MIB_GET_RSP
suffix:semicolon
multiline_comment|/* DEC_Ext_MIB_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_DEC_EXT_MIB_GET_REQ
)brace
id|PI_CMD_DEC_EXT_MIB_GET_REQ
suffix:semicolon
multiline_comment|/* DEC_Ext_MIB_Get (efddi and efdx groups only) Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
multiline_comment|/* SMT GROUP */
DECL|member|esmt_station_type
id|PI_UINT32
id|esmt_station_type
suffix:semicolon
multiline_comment|/* MAC GROUP */
DECL|member|emac_link_state
id|PI_UINT32
id|emac_link_state
suffix:semicolon
DECL|member|emac_ring_purger_state
id|PI_UINT32
id|emac_ring_purger_state
suffix:semicolon
DECL|member|emac_ring_purger_enable
id|PI_UINT32
id|emac_ring_purger_enable
suffix:semicolon
DECL|member|emac_frame_strip_mode
id|PI_UINT32
id|emac_frame_strip_mode
suffix:semicolon
DECL|member|emac_ring_error_reason
id|PI_UINT32
id|emac_ring_error_reason
suffix:semicolon
DECL|member|emac_up_nbr_dup_addr_flag
id|PI_UINT32
id|emac_up_nbr_dup_addr_flag
suffix:semicolon
DECL|member|emac_restricted_token_timeout
id|PI_UINT32
id|emac_restricted_token_timeout
suffix:semicolon
multiline_comment|/* PORT GROUP */
DECL|member|eport_pmd_type
id|PI_UINT32
id|eport_pmd_type
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|eport_phy_state
id|PI_UINT32
id|eport_phy_state
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|eport_reject_reason
id|PI_UINT32
id|eport_reject_reason
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/* FDX (Full-Duplex) GROUP */
DECL|member|efdx_enable
id|PI_UINT32
id|efdx_enable
suffix:semicolon
multiline_comment|/* Valid only in SMT 7.3 */
DECL|member|efdx_op
id|PI_UINT32
id|efdx_op
suffix:semicolon
multiline_comment|/* Valid only in SMT 7.3 */
DECL|member|efdx_state
id|PI_UINT32
id|efdx_state
suffix:semicolon
multiline_comment|/* Valid only in SMT 7.3 */
DECL|typedef|PI_CMD_DEC_EXT_MIB_GET_RSP
)brace
id|PI_CMD_DEC_EXT_MIB_GET_RSP
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|traces_rcvd
id|PI_CNTR
id|traces_rcvd
suffix:semicolon
multiline_comment|/* Station */
DECL|member|frame_cnt
id|PI_CNTR
id|frame_cnt
suffix:semicolon
multiline_comment|/* Link */
DECL|member|error_cnt
id|PI_CNTR
id|error_cnt
suffix:semicolon
DECL|member|lost_cnt
id|PI_CNTR
id|lost_cnt
suffix:semicolon
DECL|member|octets_rcvd
id|PI_CNTR
id|octets_rcvd
suffix:semicolon
DECL|member|octets_sent
id|PI_CNTR
id|octets_sent
suffix:semicolon
DECL|member|pdus_rcvd
id|PI_CNTR
id|pdus_rcvd
suffix:semicolon
DECL|member|pdus_sent
id|PI_CNTR
id|pdus_sent
suffix:semicolon
DECL|member|mcast_octets_rcvd
id|PI_CNTR
id|mcast_octets_rcvd
suffix:semicolon
DECL|member|mcast_octets_sent
id|PI_CNTR
id|mcast_octets_sent
suffix:semicolon
DECL|member|mcast_pdus_rcvd
id|PI_CNTR
id|mcast_pdus_rcvd
suffix:semicolon
DECL|member|mcast_pdus_sent
id|PI_CNTR
id|mcast_pdus_sent
suffix:semicolon
DECL|member|xmt_underruns
id|PI_CNTR
id|xmt_underruns
suffix:semicolon
DECL|member|xmt_failures
id|PI_CNTR
id|xmt_failures
suffix:semicolon
DECL|member|block_check_errors
id|PI_CNTR
id|block_check_errors
suffix:semicolon
DECL|member|frame_status_errors
id|PI_CNTR
id|frame_status_errors
suffix:semicolon
DECL|member|pdu_length_errors
id|PI_CNTR
id|pdu_length_errors
suffix:semicolon
DECL|member|rcv_overruns
id|PI_CNTR
id|rcv_overruns
suffix:semicolon
DECL|member|user_buff_unavailable
id|PI_CNTR
id|user_buff_unavailable
suffix:semicolon
DECL|member|inits_initiated
id|PI_CNTR
id|inits_initiated
suffix:semicolon
DECL|member|inits_rcvd
id|PI_CNTR
id|inits_rcvd
suffix:semicolon
DECL|member|beacons_initiated
id|PI_CNTR
id|beacons_initiated
suffix:semicolon
DECL|member|dup_addrs
id|PI_CNTR
id|dup_addrs
suffix:semicolon
DECL|member|dup_tokens
id|PI_CNTR
id|dup_tokens
suffix:semicolon
DECL|member|purge_errors
id|PI_CNTR
id|purge_errors
suffix:semicolon
DECL|member|fci_strip_errors
id|PI_CNTR
id|fci_strip_errors
suffix:semicolon
DECL|member|traces_initiated
id|PI_CNTR
id|traces_initiated
suffix:semicolon
DECL|member|directed_beacons_rcvd
id|PI_CNTR
id|directed_beacons_rcvd
suffix:semicolon
DECL|member|emac_frame_alignment_errors
id|PI_CNTR
id|emac_frame_alignment_errors
suffix:semicolon
DECL|member|ebuff_errors
id|PI_CNTR
id|ebuff_errors
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
multiline_comment|/* Phy */
DECL|member|lct_rejects
id|PI_CNTR
id|lct_rejects
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|lem_rejects
id|PI_CNTR
id|lem_rejects
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|link_errors
id|PI_CNTR
id|link_errors
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|connections
id|PI_CNTR
id|connections
(braket
id|PI_PHY_K_MAX
)braket
suffix:semicolon
DECL|member|copied_cnt
id|PI_CNTR
id|copied_cnt
suffix:semicolon
multiline_comment|/* Valid only if using SMT 7.3 */
DECL|member|transmit_cnt
id|PI_CNTR
id|transmit_cnt
suffix:semicolon
multiline_comment|/* Valid only if using SMT 7.3 */
DECL|member|tokens
id|PI_CNTR
id|tokens
suffix:semicolon
DECL|typedef|PI_CNTR_BLK
)brace
id|PI_CNTR_BLK
suffix:semicolon
multiline_comment|/* Counters_Get Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_CNTRS_GET_REQ
)brace
id|PI_CMD_CNTRS_GET_REQ
suffix:semicolon
multiline_comment|/* Counters_Get Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|time_since_reset
id|PI_CNTR
id|time_since_reset
suffix:semicolon
DECL|member|cntrs
id|PI_CNTR_BLK
id|cntrs
suffix:semicolon
DECL|typedef|PI_CMD_CNTRS_GET_RSP
)brace
id|PI_CMD_CNTRS_GET_RSP
suffix:semicolon
multiline_comment|/* Counters_Set Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|cntrs
id|PI_CNTR_BLK
id|cntrs
suffix:semicolon
DECL|typedef|PI_CMD_CNTRS_SET_REQ
)brace
id|PI_CMD_CNTRS_SET_REQ
suffix:semicolon
multiline_comment|/* Counters_Set Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_CNTRS_SET_RSP
)brace
id|PI_CMD_CNTRS_SET_RSP
suffix:semicolon
multiline_comment|/* Error_Log_Clear Request */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|typedef|PI_CMD_ERROR_LOG_CLEAR_REQ
)brace
id|PI_CMD_ERROR_LOG_CLEAR_REQ
suffix:semicolon
multiline_comment|/* Error_Log_Clear Response */
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|typedef|PI_CMD_ERROR_LOG_CLEAR_RSP
)brace
id|PI_CMD_ERROR_LOG_CLEAR_RSP
suffix:semicolon
multiline_comment|/* Error_Log_Get Request */
DECL|macro|PI_LOG_ENTRY_K_INDEX_MIN
mdefine_line|#define PI_LOG_ENTRY_K_INDEX_MIN&t;0&t;&t;/* Minimum index for entry */
r_typedef
r_struct
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|entry_index
id|PI_UINT32
id|entry_index
suffix:semicolon
DECL|typedef|PI_CMD_ERROR_LOG_GET_REQ
)brace
id|PI_CMD_ERROR_LOG_GET_REQ
suffix:semicolon
multiline_comment|/* Error_Log_Get Response */
DECL|macro|PI_K_LOG_FW_SIZE
mdefine_line|#define PI_K_LOG_FW_SIZE&t;&t;&t;111&t;&t;/* Max number of fw longwords */
DECL|macro|PI_K_LOG_DIAG_SIZE
mdefine_line|#define PI_K_LOG_DIAG_SIZE&t; &t;&t;6&t;&t;/* Max number of diag longwords */
r_typedef
r_struct
(brace
r_struct
(brace
DECL|member|fru_imp_mask
id|PI_UINT32
id|fru_imp_mask
suffix:semicolon
DECL|member|test_id
id|PI_UINT32
id|test_id
suffix:semicolon
DECL|member|reserved
id|PI_UINT32
id|reserved
(braket
id|PI_K_LOG_DIAG_SIZE
)braket
suffix:semicolon
DECL|member|diag
)brace
id|diag
suffix:semicolon
DECL|member|fw
id|PI_UINT32
id|fw
(braket
id|PI_K_LOG_FW_SIZE
)braket
suffix:semicolon
DECL|typedef|PI_LOG_ENTRY
)brace
id|PI_LOG_ENTRY
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|event_status
id|PI_UINT32
id|event_status
suffix:semicolon
DECL|member|caller_id
id|PI_UINT32
id|caller_id
suffix:semicolon
DECL|member|timestamp_l
id|PI_UINT32
id|timestamp_l
suffix:semicolon
DECL|member|timestamp_h
id|PI_UINT32
id|timestamp_h
suffix:semicolon
DECL|member|write_count
id|PI_UINT32
id|write_count
suffix:semicolon
DECL|member|entry_info
id|PI_LOG_ENTRY
id|entry_info
suffix:semicolon
DECL|typedef|PI_CMD_ERROR_LOG_GET_RSP
)brace
id|PI_CMD_ERROR_LOG_GET_RSP
suffix:semicolon
multiline_comment|/* Define error log related constants and types.&t;&t;&t;&t;&t;*/
multiline_comment|/*   Not all of the caller id&squot;s can occur.  The only ones currently */
multiline_comment|/*   implemented are: none, selftest, mfg, fw, console&t;&t;&t;&t;*/
DECL|macro|PI_LOG_EVENT_STATUS_K_VALID
mdefine_line|#define PI_LOG_EVENT_STATUS_K_VALID&t;&t;0&t;/* Valid Event Status &t;&t;*/
DECL|macro|PI_LOG_EVENT_STATUS_K_INVALID
mdefine_line|#define PI_LOG_EVENT_STATUS_K_INVALID&t;1&t;/* Invalid Event Status &t;*/
DECL|macro|PI_LOG_CALLER_ID_K_NONE
mdefine_line|#define PI_LOG_CALLER_ID_K_NONE&t;&t; &t;0&t;/* No caller &t;&t;&t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_SELFTEST
mdefine_line|#define PI_LOG_CALLER_ID_K_SELFTEST&t; &t;1&t;/* Normal power-up selftest */&t;&t;&t;
DECL|macro|PI_LOG_CALLER_ID_K_MFG
mdefine_line|#define PI_LOG_CALLER_ID_K_MFG&t;&t; &t;2&t;/* Mfg power-up selftest &t;*/
DECL|macro|PI_LOG_CALLER_ID_K_ONLINE
mdefine_line|#define PI_LOG_CALLER_ID_K_ONLINE&t;&t;3&t;/* On-line diagnostics &t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_HW
mdefine_line|#define PI_LOG_CALLER_ID_K_HW&t;&t;&t;4&t;/* Hardware &t;&t;&t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_FW
mdefine_line|#define PI_LOG_CALLER_ID_K_FW&t;&t;&t;5&t;/* Firmware &t;&t;&t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_CNS_HW
mdefine_line|#define PI_LOG_CALLER_ID_K_CNS_HW&t;&t;6&t;/* CNS firmware &t;&t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_CNS_FW
mdefine_line|#define PI_LOG_CALLER_ID_K_CNS_FW&t;&t;7&t;/* CNS hardware &t;&t;&t;*/
DECL|macro|PI_LOG_CALLER_ID_K_CONSOLE
mdefine_line|#define PI_LOG_CALLER_ID_K_CONSOLE&t; &t;8   /* Console Caller Id &t;&t;*/
multiline_comment|/*&n; *  Place all DMA commands in the following request and response structures&n; *  to simplify code.&n; */
r_typedef
r_union
(brace
DECL|member|cmd_type
id|PI_UINT32
id|cmd_type
suffix:semicolon
DECL|member|start
id|PI_CMD_START_REQ
id|start
suffix:semicolon
DECL|member|filter_set
id|PI_CMD_FILTERS_SET_REQ
id|filter_set
suffix:semicolon
DECL|member|filter_get
id|PI_CMD_FILTERS_GET_REQ
id|filter_get
suffix:semicolon
DECL|member|char_set
id|PI_CMD_CHARS_SET_REQ
id|char_set
suffix:semicolon
DECL|member|addr_filter_set
id|PI_CMD_ADDR_FILTER_SET_REQ
id|addr_filter_set
suffix:semicolon
DECL|member|addr_filter_get
id|PI_CMD_ADDR_FILTER_GET_REQ
id|addr_filter_get
suffix:semicolon
DECL|member|stat_char_get
id|PI_CMD_STATUS_CHARS_GET_REQ
id|stat_char_get
suffix:semicolon
DECL|member|cntrs_get
id|PI_CMD_CNTRS_GET_REQ
id|cntrs_get
suffix:semicolon
DECL|member|cntrs_set
id|PI_CMD_CNTRS_SET_REQ
id|cntrs_set
suffix:semicolon
DECL|member|error_log_clear
id|PI_CMD_ERROR_LOG_CLEAR_REQ
id|error_log_clear
suffix:semicolon
DECL|member|error_log_read
id|PI_CMD_ERROR_LOG_GET_REQ
id|error_log_read
suffix:semicolon
DECL|member|snmp_set
id|PI_CMD_SNMP_SET_REQ
id|snmp_set
suffix:semicolon
DECL|member|fddi_mib_get
id|PI_CMD_FDDI_MIB_GET_REQ
id|fddi_mib_get
suffix:semicolon
DECL|member|dec_mib_get
id|PI_CMD_DEC_EXT_MIB_GET_REQ
id|dec_mib_get
suffix:semicolon
DECL|member|smt_mib_set
id|PI_CMD_SMT_MIB_SET_REQ
id|smt_mib_set
suffix:semicolon
DECL|member|smt_mib_get
id|PI_CMD_SMT_MIB_GET_REQ
id|smt_mib_get
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
id|PI_CMD_REQ_K_SIZE_MAX
)braket
suffix:semicolon
DECL|typedef|PI_DMA_CMD_REQ
)brace
id|PI_DMA_CMD_REQ
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|header
id|PI_RSP_HEADER
id|header
suffix:semicolon
DECL|member|start
id|PI_CMD_START_RSP
id|start
suffix:semicolon
DECL|member|filter_set
id|PI_CMD_FILTERS_SET_RSP
id|filter_set
suffix:semicolon
DECL|member|filter_get
id|PI_CMD_FILTERS_GET_RSP
id|filter_get
suffix:semicolon
DECL|member|char_set
id|PI_CMD_CHARS_SET_RSP
id|char_set
suffix:semicolon
DECL|member|addr_filter_set
id|PI_CMD_ADDR_FILTER_SET_RSP
id|addr_filter_set
suffix:semicolon
DECL|member|addr_filter_get
id|PI_CMD_ADDR_FILTER_GET_RSP
id|addr_filter_get
suffix:semicolon
DECL|member|stat_char_get
id|PI_CMD_STATUS_CHARS_GET_RSP
id|stat_char_get
suffix:semicolon
DECL|member|cntrs_get
id|PI_CMD_CNTRS_GET_RSP
id|cntrs_get
suffix:semicolon
DECL|member|cntrs_set
id|PI_CMD_CNTRS_SET_RSP
id|cntrs_set
suffix:semicolon
DECL|member|error_log_clear
id|PI_CMD_ERROR_LOG_CLEAR_RSP
id|error_log_clear
suffix:semicolon
DECL|member|error_log_get
id|PI_CMD_ERROR_LOG_GET_RSP
id|error_log_get
suffix:semicolon
DECL|member|snmp_set
id|PI_CMD_SNMP_SET_RSP
id|snmp_set
suffix:semicolon
DECL|member|fddi_mib_get
id|PI_CMD_FDDI_MIB_GET_RSP
id|fddi_mib_get
suffix:semicolon
DECL|member|dec_mib_get
id|PI_CMD_DEC_EXT_MIB_GET_RSP
id|dec_mib_get
suffix:semicolon
DECL|member|smt_mib_set
id|PI_CMD_SMT_MIB_SET_RSP
id|smt_mib_set
suffix:semicolon
DECL|member|smt_mib_get
id|PI_CMD_SMT_MIB_GET_RSP
id|smt_mib_get
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
id|PI_CMD_RSP_K_SIZE_MAX
)braket
suffix:semicolon
DECL|typedef|PI_DMA_CMD_RSP
)brace
id|PI_DMA_CMD_RSP
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|request
id|PI_DMA_CMD_REQ
id|request
suffix:semicolon
DECL|member|response
id|PI_DMA_CMD_RSP
id|response
suffix:semicolon
DECL|typedef|PI_DMA_CMD_BUFFER
)brace
id|PI_DMA_CMD_BUFFER
suffix:semicolon
multiline_comment|/* Define format of Consumer Block (resident in host memory) */
r_typedef
r_struct
(brace
DECL|member|xmt_rcv_data
r_volatile
id|PI_UINT32
id|xmt_rcv_data
suffix:semicolon
DECL|member|reserved_1
r_volatile
id|PI_UINT32
id|reserved_1
suffix:semicolon
DECL|member|smt_host
r_volatile
id|PI_UINT32
id|smt_host
suffix:semicolon
DECL|member|reserved_2
r_volatile
id|PI_UINT32
id|reserved_2
suffix:semicolon
DECL|member|unsol
r_volatile
id|PI_UINT32
id|unsol
suffix:semicolon
DECL|member|reserved_3
r_volatile
id|PI_UINT32
id|reserved_3
suffix:semicolon
DECL|member|cmd_rsp
r_volatile
id|PI_UINT32
id|cmd_rsp
suffix:semicolon
DECL|member|reserved_4
r_volatile
id|PI_UINT32
id|reserved_4
suffix:semicolon
DECL|member|cmd_req
r_volatile
id|PI_UINT32
id|cmd_req
suffix:semicolon
DECL|member|reserved_5
r_volatile
id|PI_UINT32
id|reserved_5
suffix:semicolon
DECL|typedef|PI_CONSUMER_BLOCK
)brace
id|PI_CONSUMER_BLOCK
suffix:semicolon
DECL|macro|PI_CONS_M_RCV_INDEX
mdefine_line|#define PI_CONS_M_RCV_INDEX&t;&t;&t;0x000000FF
DECL|macro|PI_CONS_M_XMT_INDEX
mdefine_line|#define PI_CONS_M_XMT_INDEX&t;&t;&t;0x00FF0000
DECL|macro|PI_CONS_V_RCV_INDEX
mdefine_line|#define PI_CONS_V_RCV_INDEX&t;&t;&t;0
DECL|macro|PI_CONS_V_XMT_INDEX
mdefine_line|#define PI_CONS_V_XMT_INDEX&t;&t;&t;16
multiline_comment|/* Offsets into consumer block */
DECL|macro|PI_CONS_BLK_K_XMT_RCV
mdefine_line|#define PI_CONS_BLK_K_XMT_RCV&t;&t;0x00
DECL|macro|PI_CONS_BLK_K_SMT_HOST
mdefine_line|#define PI_CONS_BLK_K_SMT_HOST&t;&t;0x08
DECL|macro|PI_CONS_BLK_K_UNSOL
mdefine_line|#define PI_CONS_BLK_K_UNSOL&t;&t;&t;0x10
DECL|macro|PI_CONS_BLK_K_CMD_RSP
mdefine_line|#define PI_CONS_BLK_K_CMD_RSP&t;&t;0x18
DECL|macro|PI_CONS_BLK_K_CMD_REQ
mdefine_line|#define PI_CONS_BLK_K_CMD_REQ&t;&t;0x20
multiline_comment|/* Offsets into descriptor block */
DECL|macro|PI_DESCR_BLK_K_RCV_DATA
mdefine_line|#define PI_DESCR_BLK_K_RCV_DATA&t;&t;0x0000
DECL|macro|PI_DESCR_BLK_K_XMT_DATA
mdefine_line|#define PI_DESCR_BLK_K_XMT_DATA&t;&t;0x0800
DECL|macro|PI_DESCR_BLK_K_SMT_HOST
mdefine_line|#define PI_DESCR_BLK_K_SMT_HOST &t;0x1000
DECL|macro|PI_DESCR_BLK_K_UNSOL
mdefine_line|#define PI_DESCR_BLK_K_UNSOL&t;&t;0x1200
DECL|macro|PI_DESCR_BLK_K_CMD_RSP
mdefine_line|#define PI_DESCR_BLK_K_CMD_RSP&t;&t;0x1280
DECL|macro|PI_DESCR_BLK_K_CMD_REQ
mdefine_line|#define PI_DESCR_BLK_K_CMD_REQ&t;&t;0x1300&t;
multiline_comment|/* Define format of a rcv descr (Rcv Data, Cmd Rsp, Unsolicited, SMT Host)   */
multiline_comment|/*   Note a field has been added for later versions of the PDQ to allow for  */
multiline_comment|/*   finer granularity of the rcv buffer alignment.  For backwards&t;&t; &t; */
multiline_comment|/*   compatibility, the two bits (which allow the rcv buffer to be longword  */
multiline_comment|/*   aligned) have been added at the MBZ bits.  To support previous drivers, */
multiline_comment|/*   the MBZ definition is left intact.&t;&t;&t;&t;&t;&t;&t;&t;&t;  &t; */
r_typedef
r_struct
(brace
DECL|member|long_0
id|PI_UINT32
id|long_0
suffix:semicolon
DECL|member|long_1
id|PI_UINT32
id|long_1
suffix:semicolon
DECL|typedef|PI_RCV_DESCR
)brace
id|PI_RCV_DESCR
suffix:semicolon
DECL|macro|PI_RCV_DESCR_M_SOP
mdefine_line|#define&t;PI_RCV_DESCR_M_SOP&t;  &t;&t;0x80000000
DECL|macro|PI_RCV_DESCR_M_SEG_LEN_LO
mdefine_line|#define PI_RCV_DESCR_M_SEG_LEN_LO &t;0x60000000 
DECL|macro|PI_RCV_DESCR_M_MBZ
mdefine_line|#define PI_RCV_DESCR_M_MBZ&t;  &t;&t;0x60000000 
DECL|macro|PI_RCV_DESCR_M_SEG_LEN
mdefine_line|#define PI_RCV_DESCR_M_SEG_LEN&t;&t;0x1F800000
DECL|macro|PI_RCV_DESCR_M_SEG_LEN_HI
mdefine_line|#define PI_RCV_DESCR_M_SEG_LEN_HI&t;0x1FF00000&t;  
DECL|macro|PI_RCV_DESCR_M_SEG_CNT
mdefine_line|#define PI_RCV_DESCR_M_SEG_CNT&t;  &t;0x000F0000
DECL|macro|PI_RCV_DESCR_M_BUFF_HI
mdefine_line|#define PI_RCV_DESCR_M_BUFF_HI&t;  &t;0x0000FFFF
DECL|macro|PI_RCV_DESCR_V_SOP
mdefine_line|#define&t;PI_RCV_DESCR_V_SOP&t;  &t;&t;31
DECL|macro|PI_RCV_DESCR_V_SEG_LEN_LO
mdefine_line|#define PI_RCV_DESCR_V_SEG_LEN_LO &t;29
DECL|macro|PI_RCV_DESCR_V_MBZ
mdefine_line|#define PI_RCV_DESCR_V_MBZ&t;  &t;&t;29
DECL|macro|PI_RCV_DESCR_V_SEG_LEN
mdefine_line|#define PI_RCV_DESCR_V_SEG_LEN&t;  &t;23
DECL|macro|PI_RCV_DESCR_V_SEG_LEN_HI
mdefine_line|#define PI_RCV_DESCR_V_SEG_LEN_HI &t;20&t;  
DECL|macro|PI_RCV_DESCR_V_SEG_CNT
mdefine_line|#define PI_RCV_DESCR_V_SEG_CNT&t;  &t;16
DECL|macro|PI_RCV_DESCR_V_BUFF_HI
mdefine_line|#define PI_RCV_DESCR_V_BUFF_HI&t; &t;0
multiline_comment|/* Define the format of a transmit descriptor (Xmt Data, Cmd Req) */
r_typedef
r_struct
(brace
DECL|member|long_0
id|PI_UINT32
id|long_0
suffix:semicolon
DECL|member|long_1
id|PI_UINT32
id|long_1
suffix:semicolon
DECL|typedef|PI_XMT_DESCR
)brace
id|PI_XMT_DESCR
suffix:semicolon
DECL|macro|PI_XMT_DESCR_M_SOP
mdefine_line|#define&t;PI_XMT_DESCR_M_SOP&t;&t;&t;0x80000000
DECL|macro|PI_XMT_DESCR_M_EOP
mdefine_line|#define PI_XMT_DESCR_M_EOP&t;&t;&t;0x40000000
DECL|macro|PI_XMT_DESCR_M_MBZ
mdefine_line|#define PI_XMT_DESCR_M_MBZ&t;&t;&t;0x20000000 
DECL|macro|PI_XMT_DESCR_M_SEG_LEN
mdefine_line|#define PI_XMT_DESCR_M_SEG_LEN&t;&t;0x1FFF0000
DECL|macro|PI_XMT_DESCR_M_BUFF_HI
mdefine_line|#define PI_XMT_DESCR_M_BUFF_HI&t;&t;0x0000FFFF
DECL|macro|PI_XMT_DESCR_V_SOP
mdefine_line|#define&t;PI_XMT_DESCR_V_SOP&t;&t;&t;31
DECL|macro|PI_XMT_DESCR_V_EOP
mdefine_line|#define&t;PI_XMT_DESCR_V_EOP&t;&t;&t;30
DECL|macro|PI_XMT_DESCR_V_MBZ
mdefine_line|#define PI_XMT_DESCR_V_MBZ&t;&t;&t;29
DECL|macro|PI_XMT_DESCR_V_SEG_LEN
mdefine_line|#define PI_XMT_DESCR_V_SEG_LEN&t;&t;16
DECL|macro|PI_XMT_DESCR_V_BUFF_HI
mdefine_line|#define PI_XMT_DESCR_V_BUFF_HI&t;&t;0
multiline_comment|/* Define format of the Descriptor Block (resident in host memory) */
DECL|macro|PI_RCV_DATA_K_NUM_ENTRIES
mdefine_line|#define PI_RCV_DATA_K_NUM_ENTRIES&t;&t;&t;256
DECL|macro|PI_XMT_DATA_K_NUM_ENTRIES
mdefine_line|#define PI_XMT_DATA_K_NUM_ENTRIES&t;&t;&t;256
DECL|macro|PI_SMT_HOST_K_NUM_ENTRIES
mdefine_line|#define PI_SMT_HOST_K_NUM_ENTRIES&t;&t;&t;64
DECL|macro|PI_UNSOL_K_NUM_ENTRIES
mdefine_line|#define PI_UNSOL_K_NUM_ENTRIES&t;&t;&t;&t;16
DECL|macro|PI_CMD_RSP_K_NUM_ENTRIES
mdefine_line|#define PI_CMD_RSP_K_NUM_ENTRIES&t;&t;&t;16
DECL|macro|PI_CMD_REQ_K_NUM_ENTRIES
mdefine_line|#define PI_CMD_REQ_K_NUM_ENTRIES&t;&t;&t;16
r_typedef
r_struct
(brace
DECL|member|rcv_data
id|PI_RCV_DESCR
id|rcv_data
(braket
id|PI_RCV_DATA_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|xmt_data
id|PI_XMT_DESCR
id|xmt_data
(braket
id|PI_XMT_DATA_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|smt_host
id|PI_RCV_DESCR
id|smt_host
(braket
id|PI_SMT_HOST_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|unsol
id|PI_RCV_DESCR
id|unsol
(braket
id|PI_UNSOL_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|cmd_rsp
id|PI_RCV_DESCR
id|cmd_rsp
(braket
id|PI_CMD_RSP_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|cmd_req
id|PI_XMT_DESCR
id|cmd_req
(braket
id|PI_CMD_REQ_K_NUM_ENTRIES
)braket
suffix:semicolon
DECL|typedef|PI_DESCR_BLOCK
)brace
id|PI_DESCR_BLOCK
suffix:semicolon
multiline_comment|/* Define Port Registers - offsets from PDQ Base address */
DECL|macro|PI_PDQ_K_REG_PORT_RESET
mdefine_line|#define PI_PDQ_K_REG_PORT_RESET&t;&t;&t;0x00000000
DECL|macro|PI_PDQ_K_REG_HOST_DATA
mdefine_line|#define PI_PDQ_K_REG_HOST_DATA&t;&t;&t;0x00000004
DECL|macro|PI_PDQ_K_REG_PORT_CTRL
mdefine_line|#define PI_PDQ_K_REG_PORT_CTRL&t;&t;&t;0x00000008
DECL|macro|PI_PDQ_K_REG_PORT_DATA_A
mdefine_line|#define PI_PDQ_K_REG_PORT_DATA_A&t;&t;0x0000000C
DECL|macro|PI_PDQ_K_REG_PORT_DATA_B
mdefine_line|#define PI_PDQ_K_REG_PORT_DATA_B&t;&t;0x00000010
DECL|macro|PI_PDQ_K_REG_PORT_STATUS
mdefine_line|#define PI_PDQ_K_REG_PORT_STATUS&t;&t;0x00000014
DECL|macro|PI_PDQ_K_REG_TYPE_0_STATUS
mdefine_line|#define PI_PDQ_K_REG_TYPE_0_STATUS &t;&t;0x00000018
DECL|macro|PI_PDQ_K_REG_HOST_INT_ENB
mdefine_line|#define PI_PDQ_K_REG_HOST_INT_ENB&t;  &t;0x0000001C
DECL|macro|PI_PDQ_K_REG_TYPE_2_PROD_NOINT
mdefine_line|#define PI_PDQ_K_REG_TYPE_2_PROD_NOINT &t;0x00000020
DECL|macro|PI_PDQ_K_REG_TYPE_2_PROD
mdefine_line|#define PI_PDQ_K_REG_TYPE_2_PROD&t;&t;0x00000024
DECL|macro|PI_PDQ_K_REG_CMD_RSP_PROD
mdefine_line|#define PI_PDQ_K_REG_CMD_RSP_PROD&t;&t;0x00000028
DECL|macro|PI_PDQ_K_REG_CMD_REQ_PROD
mdefine_line|#define PI_PDQ_K_REG_CMD_REQ_PROD&t;&t;0x0000002C
DECL|macro|PI_PDQ_K_REG_SMT_HOST_PROD
mdefine_line|#define PI_PDQ_K_REG_SMT_HOST_PROD   &t;0x00000030
DECL|macro|PI_PDQ_K_REG_UNSOL_PROD
mdefine_line|#define PI_PDQ_K_REG_UNSOL_PROD&t;&t;&t;0x00000034
multiline_comment|/* Port Control Register - Command codes for primary commands */
DECL|macro|PI_PCTRL_M_CMD_ERROR
mdefine_line|#define PI_PCTRL_M_CMD_ERROR&t;&t;&t;0x8000
DECL|macro|PI_PCTRL_M_BLAST_FLASH
mdefine_line|#define PI_PCTRL_M_BLAST_FLASH&t;&t;&t;0x4000
DECL|macro|PI_PCTRL_M_HALT
mdefine_line|#define PI_PCTRL_M_HALT&t;&t;&t;&t;&t;0x2000
DECL|macro|PI_PCTRL_M_COPY_DATA
mdefine_line|#define PI_PCTRL_M_COPY_DATA&t;&t;&t;0x1000
DECL|macro|PI_PCTRL_M_ERROR_LOG_START
mdefine_line|#define PI_PCTRL_M_ERROR_LOG_START&t;&t;0x0800
DECL|macro|PI_PCTRL_M_ERROR_LOG_READ
mdefine_line|#define PI_PCTRL_M_ERROR_LOG_READ&t;&t;0x0400
DECL|macro|PI_PCTRL_M_XMT_DATA_FLUSH_DONE
mdefine_line|#define PI_PCTRL_M_XMT_DATA_FLUSH_DONE&t;0x0200
DECL|macro|PI_PCTRL_M_INIT
mdefine_line|#define PI_PCTRL_M_INIT&t;&t;&t;&t;&t;0x0100
DECL|macro|PI_PCTRL_M_INIT_START
mdefine_line|#define PI_PCTRL_M_INIT_START&t;&t;    0x0080
DECL|macro|PI_PCTRL_M_CONS_BLOCK
mdefine_line|#define PI_PCTRL_M_CONS_BLOCK&t;&t;&t;0x0040
DECL|macro|PI_PCTRL_M_UNINIT
mdefine_line|#define PI_PCTRL_M_UNINIT&t;&t;&t;&t;0x0020
DECL|macro|PI_PCTRL_M_RING_MEMBER
mdefine_line|#define PI_PCTRL_M_RING_MEMBER&t;&t;&t;0x0010
DECL|macro|PI_PCTRL_M_MLA
mdefine_line|#define PI_PCTRL_M_MLA&t;&t;&t;&t;&t;0x0008&t;&t;
DECL|macro|PI_PCTRL_M_FW_REV_READ
mdefine_line|#define PI_PCTRL_M_FW_REV_READ&t;&t;&t;0x0004
DECL|macro|PI_PCTRL_M_DEV_SPECIFIC
mdefine_line|#define PI_PCTRL_M_DEV_SPECIFIC&t;&t;&t;0x0002
DECL|macro|PI_PCTRL_M_SUB_CMD
mdefine_line|#define PI_PCTRL_M_SUB_CMD&t;&t;&t;&t;0x0001
multiline_comment|/* Define sub-commands accessed via the PI_PCTRL_M_SUB_CMD command */
DECL|macro|PI_SUB_CMD_K_LINK_UNINIT
mdefine_line|#define PI_SUB_CMD_K_LINK_UNINIT&t;&t;0x0001
DECL|macro|PI_SUB_CMD_K_BURST_SIZE_SET
mdefine_line|#define PI_SUB_CMD_K_BURST_SIZE_SET&t;&t;0x0002
DECL|macro|PI_SUB_CMD_K_PDQ_REV_GET
mdefine_line|#define PI_SUB_CMD_K_PDQ_REV_GET&t;&t;0x0004
DECL|macro|PI_SUB_CMD_K_HW_REV_GET
mdefine_line|#define PI_SUB_CMD_K_HW_REV_GET&t;&t;&t;0x0008
multiline_comment|/* Define some Port Data B values */
DECL|macro|PI_PDATA_B_DMA_BURST_SIZE_4
mdefine_line|#define PI_PDATA_B_DMA_BURST_SIZE_4&t; &t;0&t;&t;/* valid values for command */
DECL|macro|PI_PDATA_B_DMA_BURST_SIZE_8
mdefine_line|#define PI_PDATA_B_DMA_BURST_SIZE_8&t; &t;1
DECL|macro|PI_PDATA_B_DMA_BURST_SIZE_16
mdefine_line|#define PI_PDATA_B_DMA_BURST_SIZE_16&t;2
DECL|macro|PI_PDATA_B_DMA_BURST_SIZE_32
mdefine_line|#define PI_PDATA_B_DMA_BURST_SIZE_32&t;3&t;&t;/* not supported on PCI */
DECL|macro|PI_PDATA_B_DMA_BURST_SIZE_DEF
mdefine_line|#define PI_PDATA_B_DMA_BURST_SIZE_DEF&t;PI_PDATA_B_DMA_BURST_SIZE_16
multiline_comment|/* Port Data A Reset state */
DECL|macro|PI_PDATA_A_RESET_M_UPGRADE
mdefine_line|#define PI_PDATA_A_RESET_M_UPGRADE&t;&t;0x00000001
DECL|macro|PI_PDATA_A_RESET_M_SOFT_RESET
mdefine_line|#define PI_PDATA_A_RESET_M_SOFT_RESET&t;0x00000002
DECL|macro|PI_PDATA_A_RESET_M_SKIP_ST
mdefine_line|#define PI_PDATA_A_RESET_M_SKIP_ST&t;&t;0x00000004
multiline_comment|/* Read adapter MLA address port control command constants */
DECL|macro|PI_PDATA_A_MLA_K_LO
mdefine_line|#define PI_PDATA_A_MLA_K_LO&t;&t;&t;&t;0
DECL|macro|PI_PDATA_A_MLA_K_HI
mdefine_line|#define PI_PDATA_A_MLA_K_HI&t;&t;&t;&t;1
multiline_comment|/* Byte Swap values for init command */
DECL|macro|PI_PDATA_A_INIT_M_DESC_BLK_ADDR
mdefine_line|#define PI_PDATA_A_INIT_M_DESC_BLK_ADDR&t;&t;&t;0x0FFFFE000
DECL|macro|PI_PDATA_A_INIT_M_RESERVED
mdefine_line|#define PI_PDATA_A_INIT_M_RESERVED&t;&t;&t;&t;0x000001FFC
DECL|macro|PI_PDATA_A_INIT_M_BSWAP_DATA
mdefine_line|#define PI_PDATA_A_INIT_M_BSWAP_DATA&t;&t;&t;0x000000002 
DECL|macro|PI_PDATA_A_INIT_M_BSWAP_LITERAL
mdefine_line|#define PI_PDATA_A_INIT_M_BSWAP_LITERAL&t;&t;&t;0x000000001
DECL|macro|PI_PDATA_A_INIT_V_DESC_BLK_ADDR
mdefine_line|#define PI_PDATA_A_INIT_V_DESC_BLK_ADDR&t;&t;&t;13
DECL|macro|PI_PDATA_A_INIT_V_RESERVED
mdefine_line|#define PI_PDATA_A_INIT_V_RESERVED&t;&t;&t;&t;3
DECL|macro|PI_PDATA_A_INIT_V_BSWAP_DATA
mdefine_line|#define PI_PDATA_A_INIT_V_BSWAP_DATA&t;&t;&t;1 
DECL|macro|PI_PDATA_A_INIT_V_BSWAP_LITERAL
mdefine_line|#define PI_PDATA_A_INIT_V_BSWAP_LITERAL&t;&t;&t;0
multiline_comment|/* Port Reset Register */
DECL|macro|PI_RESET_M_ASSERT_RESET
mdefine_line|#define PI_RESET_M_ASSERT_RESET&t;&t;&t;1
multiline_comment|/* Port Status register */
DECL|macro|PI_PSTATUS_V_RCV_DATA_PENDING
mdefine_line|#define PI_PSTATUS_V_RCV_DATA_PENDING&t;31
DECL|macro|PI_PSTATUS_V_XMT_DATA_PENDING
mdefine_line|#define PI_PSTATUS_V_XMT_DATA_PENDING&t;30
DECL|macro|PI_PSTATUS_V_SMT_HOST_PENDING
mdefine_line|#define PI_PSTATUS_V_SMT_HOST_PENDING&t;29
DECL|macro|PI_PSTATUS_V_UNSOL_PENDING
mdefine_line|#define PI_PSTATUS_V_UNSOL_PENDING&t;&t;28
DECL|macro|PI_PSTATUS_V_CMD_RSP_PENDING
mdefine_line|#define PI_PSTATUS_V_CMD_RSP_PENDING&t;27
DECL|macro|PI_PSTATUS_V_CMD_REQ_PENDING
mdefine_line|#define PI_PSTATUS_V_CMD_REQ_PENDING&t;26
DECL|macro|PI_PSTATUS_V_TYPE_0_PENDING
mdefine_line|#define PI_PSTATUS_V_TYPE_0_PENDING&t;&t;25
DECL|macro|PI_PSTATUS_V_RESERVED_1
mdefine_line|#define PI_PSTATUS_V_RESERVED_1&t;&t;&t;16
DECL|macro|PI_PSTATUS_V_RESERVED_2
mdefine_line|#define PI_PSTATUS_V_RESERVED_2&t;&t;&t;11
DECL|macro|PI_PSTATUS_V_STATE
mdefine_line|#define PI_PSTATUS_V_STATE&t;&t;&t;&t;8
DECL|macro|PI_PSTATUS_V_HALT_ID
mdefine_line|#define PI_PSTATUS_V_HALT_ID&t;&t;&t;0
DECL|macro|PI_PSTATUS_M_RCV_DATA_PENDING
mdefine_line|#define PI_PSTATUS_M_RCV_DATA_PENDING&t;0x80000000
DECL|macro|PI_PSTATUS_M_XMT_DATA_PENDING
mdefine_line|#define PI_PSTATUS_M_XMT_DATA_PENDING&t;0x40000000
DECL|macro|PI_PSTATUS_M_SMT_HOST_PENDING
mdefine_line|#define PI_PSTATUS_M_SMT_HOST_PENDING&t;0x20000000
DECL|macro|PI_PSTATUS_M_UNSOL_PENDING
mdefine_line|#define PI_PSTATUS_M_UNSOL_PENDING&t;&t;0x10000000
DECL|macro|PI_PSTATUS_M_CMD_RSP_PENDING
mdefine_line|#define PI_PSTATUS_M_CMD_RSP_PENDING&t;0x08000000
DECL|macro|PI_PSTATUS_M_CMD_REQ_PENDING
mdefine_line|#define PI_PSTATUS_M_CMD_REQ_PENDING&t;0x04000000
DECL|macro|PI_PSTATUS_M_TYPE_0_PENDING
mdefine_line|#define PI_PSTATUS_M_TYPE_0_PENDING&t;&t;0x02000000
DECL|macro|PI_PSTATUS_M_RESERVED_1
mdefine_line|#define PI_PSTATUS_M_RESERVED_1&t;&t;&t;0x01FF0000
DECL|macro|PI_PSTATUS_M_RESERVED_2
mdefine_line|#define PI_PSTATUS_M_RESERVED_2&t;&t;&t;0x0000F800
DECL|macro|PI_PSTATUS_M_STATE
mdefine_line|#define PI_PSTATUS_M_STATE&t;&t;&t;&t;0x00000700
DECL|macro|PI_PSTATUS_M_HALT_ID
mdefine_line|#define PI_PSTATUS_M_HALT_ID&t;&t;&t;0x000000FF
multiline_comment|/* Define Halt Id&squot;s&t;&t;&t; &t;&t;&t;&t;&t;*/
multiline_comment|/*   Do not insert into this list, only append. */
DECL|macro|PI_HALT_ID_K_SELFTEST_TIMEOUT
mdefine_line|#define PI_HALT_ID_K_SELFTEST_TIMEOUT&t;0
DECL|macro|PI_HALT_ID_K_PARITY_ERROR
mdefine_line|#define PI_HALT_ID_K_PARITY_ERROR&t;&t;1
DECL|macro|PI_HALT_ID_K_HOST_DIR_HALT
mdefine_line|#define PI_HALT_ID_K_HOST_DIR_HALT&t;&t;2
DECL|macro|PI_HALT_ID_K_SW_FAULT
mdefine_line|#define PI_HALT_ID_K_SW_FAULT&t;&t;&t;3
DECL|macro|PI_HALT_ID_K_HW_FAULT
mdefine_line|#define PI_HALT_ID_K_HW_FAULT&t;&t;&t;4
DECL|macro|PI_HALT_ID_K_PC_TRACE
mdefine_line|#define PI_HALT_ID_K_PC_TRACE&t;&t;&t;5
DECL|macro|PI_HALT_ID_K_DMA_ERROR
mdefine_line|#define PI_HALT_ID_K_DMA_ERROR&t;&t;&t;6&t;&t;&t;/* Host Data has error reg */
DECL|macro|PI_HALT_ID_K_IMAGE_CRC_ERROR
mdefine_line|#define PI_HALT_ID_K_IMAGE_CRC_ERROR&t;7   &t;&t;/* Image is bad, update it */
DECL|macro|PI_HALT_ID_K_BUS_EXCEPTION
mdefine_line|#define PI_HALT_ID_K_BUS_EXCEPTION&t; &t;8   &t;&t;/* 68K bus exception&t;   */
multiline_comment|/* Host Interrupt Enable Register as seen by host */
DECL|macro|PI_HOST_INT_M_XMT_DATA_ENB
mdefine_line|#define PI_HOST_INT_M_XMT_DATA_ENB&t;&t;0x80000000&t;/* Type 2 Enables */
DECL|macro|PI_HOST_INT_M_RCV_DATA_ENB
mdefine_line|#define PI_HOST_INT_M_RCV_DATA_ENB&t;&t;0x40000000  
DECL|macro|PI_HOST_INT_M_SMT_HOST_ENB
mdefine_line|#define PI_HOST_INT_M_SMT_HOST_ENB&t;&t;0x10000000&t;/* Type 1 Enables */ 
DECL|macro|PI_HOST_INT_M_UNSOL_ENB
mdefine_line|#define PI_HOST_INT_M_UNSOL_ENB&t;&t;&t;0x20000000
DECL|macro|PI_HOST_INT_M_CMD_RSP_ENB
mdefine_line|#define PI_HOST_INT_M_CMD_RSP_ENB&t;&t;0x08000000
DECL|macro|PI_HOST_INT_M_CMD_REQ_ENB
mdefine_line|#define PI_HOST_INT_M_CMD_REQ_ENB&t;&t;0x04000000
DECL|macro|PI_HOST_INT_M_TYPE_1_RESERVED
mdefine_line|#define&t;PI_HOST_INT_M_TYPE_1_RESERVED&t;0x00FF0000
DECL|macro|PI_HOST_INT_M_TYPE_0_RESERVED
mdefine_line|#define&t;PI_HOST_INT_M_TYPE_0_RESERVED&t;0x0000FF00&t;/* Type 0 Enables */
DECL|macro|PI_HOST_INT_M_1MS
mdefine_line|#define PI_HOST_INT_M_1MS&t;&t;&t;&t;0x00000080
DECL|macro|PI_HOST_INT_M_20MS
mdefine_line|#define PI_HOST_INT_M_20MS&t;&t;&t;&t;0x00000040
DECL|macro|PI_HOST_INT_M_CSR_CMD_DONE
mdefine_line|#define PI_HOST_INT_M_CSR_CMD_DONE&t;&t;0x00000020
DECL|macro|PI_HOST_INT_M_STATE_CHANGE
mdefine_line|#define PI_HOST_INT_M_STATE_CHANGE&t;&t;0x00000010
DECL|macro|PI_HOST_INT_M_XMT_FLUSH
mdefine_line|#define PI_HOST_INT_M_XMT_FLUSH&t;&t;&t;0x00000008
DECL|macro|PI_HOST_INT_M_NXM
mdefine_line|#define PI_HOST_INT_M_NXM&t;&t;&t;&t;0x00000004
DECL|macro|PI_HOST_INT_M_PM_PAR_ERR
mdefine_line|#define PI_HOST_INT_M_PM_PAR_ERR&t;&t;0x00000002
DECL|macro|PI_HOST_INT_M_BUS_PAR_ERR
mdefine_line|#define PI_HOST_INT_M_BUS_PAR_ERR&t;&t;0x00000001
DECL|macro|PI_HOST_INT_V_XMT_DATA_ENB
mdefine_line|#define PI_HOST_INT_V_XMT_DATA_ENB&t;&t;31&t;&t;&t;/* Type 2 Enables */
DECL|macro|PI_HOST_INT_V_RCV_DATA_ENB
mdefine_line|#define PI_HOST_INT_V_RCV_DATA_ENB&t;&t;30  
DECL|macro|PI_HOST_INT_V_SMT_HOST_ENB
mdefine_line|#define PI_HOST_INT_V_SMT_HOST_ENB&t;&t;29&t;&t;&t;/* Type 1 Enables */ 
DECL|macro|PI_HOST_INT_V_UNSOL_ENB
mdefine_line|#define PI_HOST_INT_V_UNSOL_ENB&t;&t;&t;28
DECL|macro|PI_HOST_INT_V_CMD_RSP_ENB
mdefine_line|#define PI_HOST_INT_V_CMD_RSP_ENB&t;&t;27
DECL|macro|PI_HOST_INT_V_CMD_REQ_ENB
mdefine_line|#define PI_HOST_INT_V_CMD_REQ_ENB&t;&t;26
DECL|macro|PI_HOST_INT_V_TYPE_1_RESERVED
mdefine_line|#define&t;PI_HOST_INT_V_TYPE_1_RESERVED&t;16
DECL|macro|PI_HOST_INT_V_TYPE_0_RESERVED
mdefine_line|#define&t;PI_HOST_INT_V_TYPE_0_RESERVED   8&t;&t;&t;/* Type 0 Enables */
DECL|macro|PI_HOST_INT_V_1MS_ENB
mdefine_line|#define PI_HOST_INT_V_1MS_ENB&t;&t;&t;7
DECL|macro|PI_HOST_INT_V_20MS_ENB
mdefine_line|#define PI_HOST_INT_V_20MS_ENB&t;&t;&t;6
DECL|macro|PI_HOST_INT_V_CSR_CMD_DONE_ENB
mdefine_line|#define PI_HOST_INT_V_CSR_CMD_DONE_ENB&t;5
DECL|macro|PI_HOST_INT_V_STATE_CHANGE_ENB
mdefine_line|#define PI_HOST_INT_V_STATE_CHANGE_ENB&t;4
DECL|macro|PI_HOST_INT_V_XMT_FLUSH_ENB
mdefine_line|#define PI_HOST_INT_V_XMT_FLUSH_ENB &t;3
DECL|macro|PI_HOST_INT_V_NXM_ENB
mdefine_line|#define PI_HOST_INT_V_NXM_ENB&t;&t;&t;2
DECL|macro|PI_HOST_INT_V_PM_PAR_ERR_ENB
mdefine_line|#define PI_HOST_INT_V_PM_PAR_ERR_ENB&t;1
DECL|macro|PI_HOST_INT_V_BUS_PAR_ERR_ENB
mdefine_line|#define PI_HOST_INT_V_BUS_PAR_ERR_ENB&t;0
DECL|macro|PI_HOST_INT_K_ACK_ALL_TYPE_0
mdefine_line|#define PI_HOST_INT_K_ACK_ALL_TYPE_0&t;0x000000FF
DECL|macro|PI_HOST_INT_K_DISABLE_ALL_INTS
mdefine_line|#define PI_HOST_INT_K_DISABLE_ALL_INTS&t;0x00000000
DECL|macro|PI_HOST_INT_K_ENABLE_ALL_INTS
mdefine_line|#define PI_HOST_INT_K_ENABLE_ALL_INTS&t;0xFFFFFFFF
DECL|macro|PI_HOST_INT_K_ENABLE_DEF_INTS
mdefine_line|#define PI_HOST_INT_K_ENABLE_DEF_INTS&t;0xC000001F
multiline_comment|/* Type 0 Interrupt Status Register */
DECL|macro|PI_TYPE_0_STAT_M_1MS
mdefine_line|#define PI_TYPE_0_STAT_M_1MS&t;&t;&t;0x00000080
DECL|macro|PI_TYPE_0_STAT_M_20MS
mdefine_line|#define PI_TYPE_0_STAT_M_20MS&t;&t;&t;0x00000040
DECL|macro|PI_TYPE_0_STAT_M_CSR_CMD_DONE
mdefine_line|#define PI_TYPE_0_STAT_M_CSR_CMD_DONE&t;0x00000020
DECL|macro|PI_TYPE_0_STAT_M_STATE_CHANGE
mdefine_line|#define PI_TYPE_0_STAT_M_STATE_CHANGE&t;0x00000010
DECL|macro|PI_TYPE_0_STAT_M_XMT_FLUSH
mdefine_line|#define PI_TYPE_0_STAT_M_XMT_FLUSH&t;&t;0x00000008
DECL|macro|PI_TYPE_0_STAT_M_NXM
mdefine_line|#define PI_TYPE_0_STAT_M_NXM&t;&t;&t;0x00000004
DECL|macro|PI_TYPE_0_STAT_M_PM_PAR_ERR
mdefine_line|#define PI_TYPE_0_STAT_M_PM_PAR_ERR&t;&t;0x00000002
DECL|macro|PI_TYPE_0_STAT_M_BUS_PAR_ERR
mdefine_line|#define PI_TYPE_0_STAT_M_BUS_PAR_ERR&t;0x00000001
DECL|macro|PI_TYPE_0_STAT_V_1MS
mdefine_line|#define PI_TYPE_0_STAT_V_1MS&t;&t;&t;7&t;&t;&t;
DECL|macro|PI_TYPE_0_STAT_V_20MS
mdefine_line|#define PI_TYPE_0_STAT_V_20MS&t;&t;&t;6&t;
DECL|macro|PI_TYPE_0_STAT_V_CSR_CMD_DONE
mdefine_line|#define PI_TYPE_0_STAT_V_CSR_CMD_DONE&t;5
DECL|macro|PI_TYPE_0_STAT_V_STATE_CHANGE
mdefine_line|#define PI_TYPE_0_STAT_V_STATE_CHANGE&t;4
DECL|macro|PI_TYPE_0_STAT_V_XMT_FLUSH
mdefine_line|#define PI_TYPE_0_STAT_V_XMT_FLUSH&t;&t;3
DECL|macro|PI_TYPE_0_STAT_V_NXM
mdefine_line|#define PI_TYPE_0_STAT_V_NXM&t;&t;&t;2
DECL|macro|PI_TYPE_0_STAT_V_PM_PAR_ERR
mdefine_line|#define PI_TYPE_0_STAT_V_PM_PAR_ERR&t;&t;1
DECL|macro|PI_TYPE_0_STAT_V_BUS_PAR_ERR
mdefine_line|#define PI_TYPE_0_STAT_V_BUS_PAR_ERR&t;0
multiline_comment|/* Register definition structures are defined for both big and little endian systems */
macro_line|#ifndef  BIG_ENDIAN
multiline_comment|/* Little endian format of Type 1 Producer register */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|prod
id|PI_UINT8
id|prod
suffix:semicolon
DECL|member|comp
id|PI_UINT8
id|comp
suffix:semicolon
DECL|member|mbz_1
id|PI_UINT8
id|mbz_1
suffix:semicolon
DECL|member|mbz_2
id|PI_UINT8
id|mbz_2
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_1_PROD_REG
)brace
id|PI_TYPE_1_PROD_REG
suffix:semicolon
multiline_comment|/* Little endian format of Type 2 Producer register */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|rcv_prod
id|PI_UINT8
id|rcv_prod
suffix:semicolon
DECL|member|xmt_prod
id|PI_UINT8
id|xmt_prod
suffix:semicolon
DECL|member|rcv_comp
id|PI_UINT8
id|rcv_comp
suffix:semicolon
DECL|member|xmt_comp
id|PI_UINT8
id|xmt_comp
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_2_PROD_REG
)brace
id|PI_TYPE_2_PROD_REG
suffix:semicolon
multiline_comment|/* Little endian format of Type 1 Consumer Block longword */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|cons
id|PI_UINT8
id|cons
suffix:semicolon
DECL|member|res0
id|PI_UINT8
id|res0
suffix:semicolon
DECL|member|res1
id|PI_UINT8
id|res1
suffix:semicolon
DECL|member|res2
id|PI_UINT8
id|res2
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_1_CONSUMER
)brace
id|PI_TYPE_1_CONSUMER
suffix:semicolon
multiline_comment|/* Little endian format of Type 2 Consumer Block longword */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|rcv_cons
id|PI_UINT8
id|rcv_cons
suffix:semicolon
DECL|member|res0
id|PI_UINT8
id|res0
suffix:semicolon
DECL|member|xmt_cons
id|PI_UINT8
id|xmt_cons
suffix:semicolon
DECL|member|res1
id|PI_UINT8
id|res1
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_2_CONSUMER
)brace
id|PI_TYPE_2_CONSUMER
suffix:semicolon
macro_line|#else
multiline_comment|/* Big endian format of Type 1 Producer register */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|mbz_2
id|PI_UINT8
id|mbz_2
suffix:semicolon
DECL|member|mbz_1
id|PI_UINT8
id|mbz_1
suffix:semicolon
DECL|member|comp
id|PI_UINT8
id|comp
suffix:semicolon
DECL|member|prod
id|PI_UINT8
id|prod
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_1_PROD_REG
)brace
id|PI_TYPE_1_PROD_REG
suffix:semicolon
multiline_comment|/* Big endian format of Type 2 Producer register */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|xmt_comp
id|PI_UINT8
id|xmt_comp
suffix:semicolon
DECL|member|rcv_comp
id|PI_UINT8
id|rcv_comp
suffix:semicolon
DECL|member|xmt_prod
id|PI_UINT8
id|xmt_prod
suffix:semicolon
DECL|member|rcv_prod
id|PI_UINT8
id|rcv_prod
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_2_PROD_REG
)brace
id|PI_TYPE_2_PROD_REG
suffix:semicolon
multiline_comment|/* Big endian format of Type 1 Consumer Block longword */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|res2
id|PI_UINT8
id|res2
suffix:semicolon
DECL|member|res1
id|PI_UINT8
id|res1
suffix:semicolon
DECL|member|res0
id|PI_UINT8
id|res0
suffix:semicolon
DECL|member|cons
id|PI_UINT8
id|cons
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_1_CONSUMER
)brace
id|PI_TYPE_1_CONSUMER
suffix:semicolon
multiline_comment|/* Big endian format of Type 2 Consumer Block longword */
r_typedef
r_union
(brace
DECL|member|lword
id|PI_UINT32
id|lword
suffix:semicolon
r_struct
(brace
DECL|member|res1
id|PI_UINT8
id|res1
suffix:semicolon
DECL|member|xmt_cons
id|PI_UINT8
id|xmt_cons
suffix:semicolon
DECL|member|res0
id|PI_UINT8
id|res0
suffix:semicolon
DECL|member|rcv_cons
id|PI_UINT8
id|rcv_cons
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
DECL|typedef|PI_TYPE_2_CONSUMER
)brace
id|PI_TYPE_2_CONSUMER
suffix:semicolon
macro_line|#endif&t;/* #ifndef BIG_ENDIAN */
multiline_comment|/* Define EISA controller register offsets */
DECL|macro|PI_ESIC_K_BURST_HOLDOFF
mdefine_line|#define PI_ESIC_K_BURST_HOLDOFF&t;&t;0x040
DECL|macro|PI_ESIC_K_SLOT_ID
mdefine_line|#define PI_ESIC_K_SLOT_ID            &t;0xC80
DECL|macro|PI_ESIC_K_SLOT_CNTRL
mdefine_line|#define PI_ESIC_K_SLOT_CNTRL&t;&t;0xC84
DECL|macro|PI_ESIC_K_MEM_ADD_CMP_0
mdefine_line|#define PI_ESIC_K_MEM_ADD_CMP_0     &t;0xC85
DECL|macro|PI_ESIC_K_MEM_ADD_CMP_1
mdefine_line|#define PI_ESIC_K_MEM_ADD_CMP_1     &t;0xC86
DECL|macro|PI_ESIC_K_MEM_ADD_CMP_2
mdefine_line|#define PI_ESIC_K_MEM_ADD_CMP_2     &t;0xC87
DECL|macro|PI_ESIC_K_MEM_ADD_HI_CMP_0
mdefine_line|#define PI_ESIC_K_MEM_ADD_HI_CMP_0  &t;0xC88
DECL|macro|PI_ESIC_K_MEM_ADD_HI_CMP_1
mdefine_line|#define PI_ESIC_K_MEM_ADD_HI_CMP_1  &t;0xC89
DECL|macro|PI_ESIC_K_MEM_ADD_HI_CMP_2
mdefine_line|#define PI_ESIC_K_MEM_ADD_HI_CMP_2  &t;0xC8A
DECL|macro|PI_ESIC_K_MEM_ADD_MASK_0
mdefine_line|#define PI_ESIC_K_MEM_ADD_MASK_0     &t;0xC8B
DECL|macro|PI_ESIC_K_MEM_ADD_MASK_1
mdefine_line|#define PI_ESIC_K_MEM_ADD_MASK_1     &t;0xC8C
DECL|macro|PI_ESIC_K_MEM_ADD_MASK_2
mdefine_line|#define PI_ESIC_K_MEM_ADD_MASK_2     &t;0xC8D
DECL|macro|PI_ESIC_K_MEM_ADD_LO_CMP_0
mdefine_line|#define PI_ESIC_K_MEM_ADD_LO_CMP_0  &t;0xC8E
DECL|macro|PI_ESIC_K_MEM_ADD_LO_CMP_1
mdefine_line|#define PI_ESIC_K_MEM_ADD_LO_CMP_1  &t;0xC8F
DECL|macro|PI_ESIC_K_MEM_ADD_LO_CMP_2
mdefine_line|#define PI_ESIC_K_MEM_ADD_LO_CMP_2  &t;0xC90
DECL|macro|PI_ESIC_K_IO_CMP_0_0
mdefine_line|#define PI_ESIC_K_IO_CMP_0_0&t;&t;0xC91
DECL|macro|PI_ESIC_K_IO_CMP_0_1
mdefine_line|#define PI_ESIC_K_IO_CMP_0_1&t;&t;0xC92
DECL|macro|PI_ESIC_K_IO_CMP_1_0
mdefine_line|#define PI_ESIC_K_IO_CMP_1_0&t;&t;0xC93
DECL|macro|PI_ESIC_K_IO_CMP_1_1
mdefine_line|#define PI_ESIC_K_IO_CMP_1_1&t;&t;0xC94
DECL|macro|PI_ESIC_K_IO_CMP_2_0
mdefine_line|#define PI_ESIC_K_IO_CMP_2_0&t;&t;0xC95
DECL|macro|PI_ESIC_K_IO_CMP_2_1
mdefine_line|#define PI_ESIC_K_IO_CMP_2_1&t;&t;0xC96
DECL|macro|PI_ESIC_K_IO_CMP_3_0
mdefine_line|#define PI_ESIC_K_IO_CMP_3_0&t;&t;0xC97
DECL|macro|PI_ESIC_K_IO_CMP_3_1
mdefine_line|#define PI_ESIC_K_IO_CMP_3_1&t;&t;0xC98
DECL|macro|PI_ESIC_K_IO_ADD_MASK_0_0
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_0_0    &t;0xC99
DECL|macro|PI_ESIC_K_IO_ADD_MASK_0_1
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_0_1    &t;0xC9A
DECL|macro|PI_ESIC_K_IO_ADD_MASK_1_0
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_1_0    &t;0xC9B
DECL|macro|PI_ESIC_K_IO_ADD_MASK_1_1
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_1_1    &t;0xC9C
DECL|macro|PI_ESIC_K_IO_ADD_MASK_2_0
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_2_0    &t;0xC9D
DECL|macro|PI_ESIC_K_IO_ADD_MASK_2_1
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_2_1    &t;0xC9E
DECL|macro|PI_ESIC_K_IO_ADD_MASK_3_0
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_3_0    &t;0xC9F
DECL|macro|PI_ESIC_K_IO_ADD_MASK_3_1
mdefine_line|#define PI_ESIC_K_IO_ADD_MASK_3_1    &t;0xCA0
DECL|macro|PI_ESIC_K_MOD_CONFIG_1
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_1&t;&t;0xCA1
DECL|macro|PI_ESIC_K_MOD_CONFIG_2
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_2&t;&t;0xCA2
DECL|macro|PI_ESIC_K_MOD_CONFIG_3
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_3&t;&t;0xCA3
DECL|macro|PI_ESIC_K_MOD_CONFIG_4
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_4&t;&t;0xCA4
DECL|macro|PI_ESIC_K_MOD_CONFIG_5
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_5    &t;0xCA5
DECL|macro|PI_ESIC_K_MOD_CONFIG_6
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_6&t;&t;0xCA6
DECL|macro|PI_ESIC_K_MOD_CONFIG_7
mdefine_line|#define PI_ESIC_K_MOD_CONFIG_7&t;&t;0xCA7
DECL|macro|PI_ESIC_K_DIP_SWITCH
mdefine_line|#define PI_ESIC_K_DIP_SWITCH         &t;0xCA8
DECL|macro|PI_ESIC_K_IO_CONFIG_STAT_0
mdefine_line|#define PI_ESIC_K_IO_CONFIG_STAT_0   &t;0xCA9
DECL|macro|PI_ESIC_K_IO_CONFIG_STAT_1
mdefine_line|#define PI_ESIC_K_IO_CONFIG_STAT_1   &t;0xCAA
DECL|macro|PI_ESIC_K_DMA_CONFIG
mdefine_line|#define PI_ESIC_K_DMA_CONFIG         &t;0xCAB
DECL|macro|PI_ESIC_K_INPUT_PORT
mdefine_line|#define PI_ESIC_K_INPUT_PORT         &t;0xCAC
DECL|macro|PI_ESIC_K_OUTPUT_PORT
mdefine_line|#define PI_ESIC_K_OUTPUT_PORT        &t;0xCAD
DECL|macro|PI_ESIC_K_FUNCTION_CNTRL
mdefine_line|#define PI_ESIC_K_FUNCTION_CNTRL&t;0xCAE
DECL|macro|PI_ESIC_K_CSR_IO_LEN
mdefine_line|#define PI_ESIC_K_CSR_IO_LEN&t;&t;PI_ESIC_K_FUNCTION_CNTRL+1&t;/* always last reg + 1 */
multiline_comment|/* Define the value all drivers must write to the function control register. */
DECL|macro|PI_ESIC_K_FUNCTION_CNTRL_IO_ENB
mdefine_line|#define PI_ESIC_K_FUNCTION_CNTRL_IO_ENB&t;0x03
multiline_comment|/* Define the bits in the slot control register. */
DECL|macro|PI_SLOT_CNTRL_M_RESET
mdefine_line|#define PI_SLOT_CNTRL_M_RESET&t;&t;0x04&t;/* Don&squot;t use.       */
DECL|macro|PI_SLOT_CNTRL_M_ERROR
mdefine_line|#define PI_SLOT_CNTRL_M_ERROR&t;&t;0x02&t;/* Not implemented. */
DECL|macro|PI_SLOT_CNTRL_M_ENB
mdefine_line|#define PI_SLOT_CNTRL_M_ENB&t;&t;0x01&t;/* Must be set.     */
multiline_comment|/* Define the bits in the burst holdoff register. */
DECL|macro|PI_BURST_HOLDOFF_M_HOLDOFF
mdefine_line|#define PI_BURST_HOLDOFF_M_HOLDOFF&t;0xFC
DECL|macro|PI_BURST_HOLDOFF_M_RESERVED
mdefine_line|#define PI_BURST_HOLDOFF_M_RESERVED&t;0x02
DECL|macro|PI_BURST_HOLDOFF_M_MEM_MAP
mdefine_line|#define PI_BURST_HOLDOFF_M_MEM_MAP&t;0x01
DECL|macro|PI_BURST_HOLDOFF_V_HOLDOFF
mdefine_line|#define PI_BURST_HOLDOFF_V_HOLDOFF&t;2
DECL|macro|PI_BURST_HOLDOFF_V_RESERVED
mdefine_line|#define PI_BURST_HOLDOFF_V_RESERVED&t;1
DECL|macro|PI_BURST_HOLDOFF_V_MEM_MAP
mdefine_line|#define PI_BURST_HOLDOFF_V_MEM_MAP&t;0
multiline_comment|/*&n; * Define the fields in the IO Compare registers.&n; * The driver must initialize the slot field with the slot ID shifted by the&n; * amount shown below.&n; */
DECL|macro|PI_IO_CMP_V_SLOT
mdefine_line|#define PI_IO_CMP_V_SLOT&t;&t;4
multiline_comment|/* Define the fields in the Interrupt Channel Configuration and Status reg */
DECL|macro|PI_CONFIG_STAT_0_M_PEND
mdefine_line|#define PI_CONFIG_STAT_0_M_PEND&t;&t;&t;0x80
DECL|macro|PI_CONFIG_STAT_0_M_RES_1
mdefine_line|#define PI_CONFIG_STAT_0_M_RES_1&t;&t;0x40
DECL|macro|PI_CONFIG_STAT_0_M_IREQ_OUT
mdefine_line|#define PI_CONFIG_STAT_0_M_IREQ_OUT&t;&t;0x20
DECL|macro|PI_CONFIG_STAT_0_M_IREQ_IN
mdefine_line|#define PI_CONFIG_STAT_0_M_IREQ_IN&t;&t;0x10
DECL|macro|PI_CONFIG_STAT_0_M_INT_ENB
mdefine_line|#define PI_CONFIG_STAT_0_M_INT_ENB&t;&t;0x08
DECL|macro|PI_CONFIG_STAT_0_M_RES_0
mdefine_line|#define PI_CONFIG_STAT_0_M_RES_0&t;&t;0x04
DECL|macro|PI_CONFIG_STAT_0_M_IRQ
mdefine_line|#define PI_CONFIG_STAT_0_M_IRQ&t;&t;&t;0x03
DECL|macro|PI_CONFIG_STAT_0_V_PEND
mdefine_line|#define PI_CONFIG_STAT_0_V_PEND&t;&t;&t;7
DECL|macro|PI_CONFIG_STAT_0_V_RES_1
mdefine_line|#define PI_CONFIG_STAT_0_V_RES_1&t;&t;6
DECL|macro|PI_CONFIG_STAT_0_V_IREQ_OUT
mdefine_line|#define PI_CONFIG_STAT_0_V_IREQ_OUT&t;&t;5
DECL|macro|PI_CONFIG_STAT_0_V_IREQ_IN
mdefine_line|#define PI_CONFIG_STAT_0_V_IREQ_IN&t;&t;4
DECL|macro|PI_CONFIG_STAT_0_V_INT_ENB
mdefine_line|#define PI_CONFIG_STAT_0_V_INT_ENB&t;&t;3
DECL|macro|PI_CONFIG_STAT_0_V_RES_0
mdefine_line|#define PI_CONFIG_STAT_0_V_RES_0&t;&t;2
DECL|macro|PI_CONFIG_STAT_0_V_IRQ
mdefine_line|#define PI_CONFIG_STAT_0_V_IRQ&t;&t;&t;0
DECL|macro|PI_CONFIG_STAT_0_IRQ_K_9
mdefine_line|#define PI_CONFIG_STAT_0_IRQ_K_9&t;&t;0
DECL|macro|PI_CONFIG_STAT_0_IRQ_K_10
mdefine_line|#define PI_CONFIG_STAT_0_IRQ_K_10&t;&t;1
DECL|macro|PI_CONFIG_STAT_0_IRQ_K_11
mdefine_line|#define PI_CONFIG_STAT_0_IRQ_K_11&t;&t;2
DECL|macro|PI_CONFIG_STAT_0_IRQ_K_15
mdefine_line|#define PI_CONFIG_STAT_0_IRQ_K_15&t;&t;3
multiline_comment|/* Define DEC FDDIcontroller/EISA (DEFEA) EISA hardware ID&squot;s */
DECL|macro|DEFEA_PRODUCT_ID
mdefine_line|#define DEFEA_PRODUCT_ID&t;0x0030A310&t;&t;/* DEC product 300 (no rev)&t;*/
DECL|macro|DEFEA_PROD_ID_1
mdefine_line|#define DEFEA_PROD_ID_1&t;&t;0x0130A310&t;&t;/* DEC product 300, rev 1&t;*/
DECL|macro|DEFEA_PROD_ID_2
mdefine_line|#define DEFEA_PROD_ID_2&t;&t;0x0230A310&t;&t;/* DEC product 300, rev 2&t;*/
DECL|macro|DEFEA_PROD_ID_3
mdefine_line|#define DEFEA_PROD_ID_3&t;&t;0x0330A310&t;&t;/* DEC product 300, rev 3&t;*/
multiline_comment|/**********************************************/
multiline_comment|/* Digital PFI Specification v1.0 Definitions */
multiline_comment|/**********************************************/
multiline_comment|/* PCI Configuration Space Constants */
DECL|macro|PFI_K_LAT_TIMER_DEF
mdefine_line|#define PFI_K_LAT_TIMER_DEF&t;&t;&t;0x88&t;/* def max master latency timer */
DECL|macro|PFI_K_LAT_TIMER_MIN
mdefine_line|#define PFI_K_LAT_TIMER_MIN&t;&t;&t;0x20&t;/* min max master latency timer */
DECL|macro|PFI_K_CSR_MEM_LEN
mdefine_line|#define PFI_K_CSR_MEM_LEN&t;&t;&t;0x80&t;/* 128 bytes */
DECL|macro|PFI_K_CSR_IO_LEN
mdefine_line|#define PFI_K_CSR_IO_LEN&t;&t;&t;0x80&t;/* 128 bytes */
DECL|macro|PFI_K_PKT_MEM_LEN
mdefine_line|#define PFI_K_PKT_MEM_LEN&t;&t;&t;0x10000&t;/* 64K bytes */
multiline_comment|/* PFI Register Offsets (starting at PDQ Register Base Address) */
DECL|macro|PFI_K_REG_RESERVED_0
mdefine_line|#define PFI_K_REG_RESERVED_0&t;&t; 0X00000038
DECL|macro|PFI_K_REG_RESERVED_1
mdefine_line|#define PFI_K_REG_RESERVED_1&t;&t; 0X0000003C
DECL|macro|PFI_K_REG_MODE_CTRL
mdefine_line|#define PFI_K_REG_MODE_CTRL&t;&t; 0X00000040
DECL|macro|PFI_K_REG_STATUS
mdefine_line|#define PFI_K_REG_STATUS&t;&t; 0X00000044
DECL|macro|PFI_K_REG_FIFO_WRITE
mdefine_line|#define PFI_K_REG_FIFO_WRITE&t;&t; 0X00000048
DECL|macro|PFI_K_REG_FIFO_READ
mdefine_line|#define PFI_K_REG_FIFO_READ&t;&t; 0X0000004C
multiline_comment|/* PFI Mode Control Register Constants */
DECL|macro|PFI_MODE_M_RESERVED
mdefine_line|#define PFI_MODE_M_RESERVED&t;&t; 0XFFFFFFF0
DECL|macro|PFI_MODE_M_TGT_ABORT_ENB
mdefine_line|#define PFI_MODE_M_TGT_ABORT_ENB&t; 0X00000008
DECL|macro|PFI_MODE_M_PDQ_INT_ENB
mdefine_line|#define PFI_MODE_M_PDQ_INT_ENB&t;&t; 0X00000004
DECL|macro|PFI_MODE_M_PFI_INT_ENB
mdefine_line|#define PFI_MODE_M_PFI_INT_ENB&t;&t; 0X00000002
DECL|macro|PFI_MODE_M_DMA_ENB
mdefine_line|#define PFI_MODE_M_DMA_ENB&t;&t; 0X00000001
DECL|macro|PFI_MODE_V_RESERVED
mdefine_line|#define PFI_MODE_V_RESERVED&t;&t; 4
DECL|macro|PFI_MODE_V_TGT_ABORT_ENB
mdefine_line|#define PFI_MODE_V_TGT_ABORT_ENB&t; 3
DECL|macro|PFI_MODE_V_PDQ_INT_ENB
mdefine_line|#define PFI_MODE_V_PDQ_INT_ENB&t;&t; 2
DECL|macro|PFI_MODE_V_PFI_INT_ENB
mdefine_line|#define PFI_MODE_V_PFI_INT_ENB&t;&t; 1
DECL|macro|PFI_MODE_V_DMA_ENB
mdefine_line|#define PFI_MODE_V_DMA_ENB&t;&t; 0
DECL|macro|PFI_MODE_K_ALL_DISABLE
mdefine_line|#define PFI_MODE_K_ALL_DISABLE&t;&t; 0X00000000
multiline_comment|/* PFI Status Register Constants */
DECL|macro|PFI_STATUS_M_RESERVED
mdefine_line|#define PFI_STATUS_M_RESERVED&t;&t; 0XFFFFFFC0
DECL|macro|PFI_STATUS_M_PFI_ERROR
mdefine_line|#define PFI_STATUS_M_PFI_ERROR&t;&t; 0X00000020&t;&t;/* only valid in rev 1 or later PFI */
DECL|macro|PFI_STATUS_M_PDQ_INT
mdefine_line|#define PFI_STATUS_M_PDQ_INT&t;&t; 0X00000010
DECL|macro|PFI_STATUS_M_PDQ_DMA_ABORT
mdefine_line|#define PFI_STATUS_M_PDQ_DMA_ABORT&t; 0X00000008
DECL|macro|PFI_STATUS_M_FIFO_FULL
mdefine_line|#define PFI_STATUS_M_FIFO_FULL&t;&t; 0X00000004
DECL|macro|PFI_STATUS_M_FIFO_EMPTY
mdefine_line|#define PFI_STATUS_M_FIFO_EMPTY&t;&t; 0X00000002
DECL|macro|PFI_STATUS_M_DMA_IN_PROGRESS
mdefine_line|#define PFI_STATUS_M_DMA_IN_PROGRESS&t; 0X00000001
DECL|macro|PFI_STATUS_V_RESERVED
mdefine_line|#define PFI_STATUS_V_RESERVED&t;&t; 6
DECL|macro|PFI_STATUS_V_PFI_ERROR
mdefine_line|#define PFI_STATUS_V_PFI_ERROR&t;&t; 5&t;&t;&t;/* only valid in rev 1 or later PFI */
DECL|macro|PFI_STATUS_V_PDQ_INT
mdefine_line|#define PFI_STATUS_V_PDQ_INT&t;&t; 4
DECL|macro|PFI_STATUS_V_PDQ_DMA_ABORT
mdefine_line|#define PFI_STATUS_V_PDQ_DMA_ABORT&t; 3
DECL|macro|PFI_STATUS_V_FIFO_FULL
mdefine_line|#define PFI_STATUS_V_FIFO_FULL&t;&t; 2
DECL|macro|PFI_STATUS_V_FIFO_EMPTY
mdefine_line|#define PFI_STATUS_V_FIFO_EMPTY&t;&t; 1
DECL|macro|PFI_STATUS_V_DMA_IN_PROGRESS
mdefine_line|#define PFI_STATUS_V_DMA_IN_PROGRESS 0
DECL|macro|DFX_MAX_EISA_SLOTS
mdefine_line|#define DFX_MAX_EISA_SLOTS&t;&t;16&t;&t;&t;/* maximum number of EISA slots to scan */
DECL|macro|DFX_MAX_NUM_BOARDS
mdefine_line|#define DFX_MAX_NUM_BOARDS&t;&t;8&t;&t;&t;/* maximum number of adapters supported */
DECL|macro|DFX_BUS_TYPE_PCI
mdefine_line|#define DFX_BUS_TYPE_PCI&t;&t;0&t;&t;&t;/* type code for DEC FDDIcontroller/PCI */
DECL|macro|DFX_BUS_TYPE_EISA
mdefine_line|#define DFX_BUS_TYPE_EISA&t;&t;1&t;&t;&t;/* type code for DEC FDDIcontroller/EISA */
DECL|macro|DFX_FC_PRH2_PRH1_PRH0
mdefine_line|#define DFX_FC_PRH2_PRH1_PRH0&t;&t;0x54003820&t;/* Packet Request Header bytes + FC */
DECL|macro|DFX_PRH0_BYTE
mdefine_line|#define DFX_PRH0_BYTE&t;&t;&t;0x20&t;&t;/* Packet Request Header byte 0 */
DECL|macro|DFX_PRH1_BYTE
mdefine_line|#define DFX_PRH1_BYTE&t;&t;&t;0x38&t;&t;/* Packet Request Header byte 1 */
DECL|macro|DFX_PRH2_BYTE
mdefine_line|#define DFX_PRH2_BYTE&t;&t;&t;0x00&t;&t;/* Packet Request Header byte 2 */
multiline_comment|/* Driver routine status (return) codes */
DECL|macro|DFX_K_SUCCESS
mdefine_line|#define DFX_K_SUCCESS&t;&t;&t;0&t;&t;&t;/* routine succeeded */
DECL|macro|DFX_K_FAILURE
mdefine_line|#define DFX_K_FAILURE&t;&t;&t;1&t;&t;&t;/* routine failed */
DECL|macro|DFX_K_OUTSTATE
mdefine_line|#define DFX_K_OUTSTATE&t;&t;&t;2&t;&t;&t;/* bad state for command */
DECL|macro|DFX_K_HW_TIMEOUT
mdefine_line|#define DFX_K_HW_TIMEOUT&t;&t;3&t;&t;&t;/* command timed out */
multiline_comment|/* Define LLC host receive buffer min/max/default values */
DECL|macro|RCV_BUFS_MIN
mdefine_line|#define RCV_BUFS_MIN&t;2&t;&t;&t;&t;&t;/* minimum pre-allocated receive buffers */
DECL|macro|RCV_BUFS_MAX
mdefine_line|#define RCV_BUFS_MAX&t;32&t;&t;&t;&t;&t;/* maximum pre-allocated receive buffers */
DECL|macro|RCV_BUFS_DEF
mdefine_line|#define RCV_BUFS_DEF&t;8&t;&t;&t;&t;&t;/* default pre-allocated receive buffers */
multiline_comment|/* Define offsets into FDDI LLC or SMT receive frame buffers - used when indicating frames */
DECL|macro|RCV_BUFF_K_DESCR
mdefine_line|#define RCV_BUFF_K_DESCR&t;0&t;&t;&t;&t;/* four byte FMC descriptor */
DECL|macro|RCV_BUFF_K_PADDING
mdefine_line|#define RCV_BUFF_K_PADDING&t;4&t;&t;&t;&t;/* three null bytes */
DECL|macro|RCV_BUFF_K_FC
mdefine_line|#define RCV_BUFF_K_FC&t;&t;7&t;&t;&t;&t;/* one byte frame control */
DECL|macro|RCV_BUFF_K_DA
mdefine_line|#define RCV_BUFF_K_DA&t;&t;8&t;&t;&t;&t;/* six byte destination address */
DECL|macro|RCV_BUFF_K_SA
mdefine_line|#define RCV_BUFF_K_SA&t;&t;14&t;&t;&t;&t;/* six byte source address */
DECL|macro|RCV_BUFF_K_DATA
mdefine_line|#define RCV_BUFF_K_DATA&t;&t;20&t;&t;&t;&t;/* offset to start of packet data */
multiline_comment|/* Define offsets into FDDI LLC transmit frame buffers - used when sending frames */
DECL|macro|XMT_BUFF_K_FC
mdefine_line|#define XMT_BUFF_K_FC&t;&t;0&t;&t;&t;&t;/* one byte frame control */
DECL|macro|XMT_BUFF_K_DA
mdefine_line|#define XMT_BUFF_K_DA&t;&t;1&t;&t;&t;&t;/* six byte destination address */
DECL|macro|XMT_BUFF_K_SA
mdefine_line|#define XMT_BUFF_K_SA&t;&t;7&t;&t;&t;&t;/* six byte source address */
DECL|macro|XMT_BUFF_K_DATA
mdefine_line|#define XMT_BUFF_K_DATA&t;&t;13&t;&t;&t;&t;/* offset to start of packet data */
multiline_comment|/*&n; * Macro evaluates to &quot;value&quot; aligned to &quot;size&quot; bytes.  Make sure that&n; * &quot;size&quot; is greater than 0 bytes.&n; */
DECL|macro|ALIGN
mdefine_line|#define ALIGN(value,size) ((value + (size - 1)) &amp; ~(size - 1))
multiline_comment|/* Macro for checking a &quot;value&quot; is within a specific range */
DECL|macro|IN_RANGE
mdefine_line|#define IN_RANGE(value,low,high) ((value &gt;= low) &amp;&amp; (value &lt;= high))
multiline_comment|/* Only execute special print call when debug driver was built */
macro_line|#ifdef DEFXX_DEBUG
DECL|macro|DBG_printk
mdefine_line|#define DBG_printk(args...) printk(## args)
macro_line|#else
DECL|macro|DBG_printk
mdefine_line|#define DBG_printk(args...)
macro_line|#endif
multiline_comment|/* Define constants for masking/unmasking interrupts */
DECL|macro|DFX_MASK_INTERRUPTS
mdefine_line|#define DFX_MASK_INTERRUPTS&t;&t;1
DECL|macro|DFX_UNMASK_INTERRUPTS
mdefine_line|#define DFX_UNMASK_INTERRUPTS&t;&t;0
multiline_comment|/* Define structure for driver transmit descriptor block */
r_typedef
r_struct
(brace
DECL|member|p_skb
r_struct
id|sk_buff
op_star
id|p_skb
suffix:semicolon
multiline_comment|/* ptr to skb */
DECL|typedef|XMT_DRIVER_DESCR
)brace
id|XMT_DRIVER_DESCR
suffix:semicolon
DECL|struct|DFX_board_tag
r_typedef
r_struct
id|DFX_board_tag
(brace
multiline_comment|/* Keep virtual and physical pointers to locked, physically contiguous memory */
DECL|member|kmalloced
r_char
op_star
id|kmalloced
suffix:semicolon
multiline_comment|/* kfree this on unload */
DECL|member|descr_block_virt
id|PI_DESCR_BLOCK
op_star
id|descr_block_virt
suffix:semicolon
multiline_comment|/* PDQ descriptor block virt address */
DECL|member|descr_block_phys
id|u32
id|descr_block_phys
suffix:semicolon
multiline_comment|/* PDQ descriptor block phys address */
DECL|member|cmd_req_virt
id|PI_DMA_CMD_REQ
op_star
id|cmd_req_virt
suffix:semicolon
multiline_comment|/* Command request buffer virt address */
DECL|member|cmd_req_phys
id|u32
id|cmd_req_phys
suffix:semicolon
multiline_comment|/* Command request buffer phys address */
DECL|member|cmd_rsp_virt
id|PI_DMA_CMD_RSP
op_star
id|cmd_rsp_virt
suffix:semicolon
multiline_comment|/* Command response buffer virt address */
DECL|member|cmd_rsp_phys
id|u32
id|cmd_rsp_phys
suffix:semicolon
multiline_comment|/* Command response buffer phys address */
DECL|member|rcv_block_virt
r_char
op_star
id|rcv_block_virt
suffix:semicolon
multiline_comment|/* LLC host receive queue buf blk virt */
DECL|member|rcv_block_phys
id|u32
id|rcv_block_phys
suffix:semicolon
multiline_comment|/* LLC host receive queue buf blk phys */
DECL|member|cons_block_virt
id|PI_CONSUMER_BLOCK
op_star
id|cons_block_virt
suffix:semicolon
multiline_comment|/* PDQ consumer block virt address */
DECL|member|cons_block_phys
id|u32
id|cons_block_phys
suffix:semicolon
multiline_comment|/* PDQ consumer block phys address */
multiline_comment|/* Keep local copies of Type 1 and Type 2 register data */
DECL|member|cmd_req_reg
id|PI_TYPE_1_PROD_REG
id|cmd_req_reg
suffix:semicolon
multiline_comment|/* Command Request register */
DECL|member|cmd_rsp_reg
id|PI_TYPE_1_PROD_REG
id|cmd_rsp_reg
suffix:semicolon
multiline_comment|/* Command Response register */
DECL|member|rcv_xmt_reg
id|PI_TYPE_2_PROD_REG
id|rcv_xmt_reg
suffix:semicolon
multiline_comment|/* Type 2 (RCV/XMT) register */
multiline_comment|/* Storage for unicast and multicast address entries in adapter CAM */
DECL|member|uc_table
id|u8
id|uc_table
(braket
l_int|1
op_star
id|FDDI_K_ALEN
)braket
suffix:semicolon
DECL|member|uc_count
id|u32
id|uc_count
suffix:semicolon
multiline_comment|/* number of unicast addresses */
DECL|member|mc_table
id|u8
id|mc_table
(braket
id|PI_CMD_ADDR_FILTER_K_SIZE
op_star
id|FDDI_K_ALEN
)braket
suffix:semicolon
DECL|member|mc_count
id|u32
id|mc_count
suffix:semicolon
multiline_comment|/* number of multicast addresses */
multiline_comment|/* Current packet filter settings */
DECL|member|ind_group_prom
id|u32
id|ind_group_prom
suffix:semicolon
multiline_comment|/* LLC individual &amp; group frame prom mode */
DECL|member|group_prom
id|u32
id|group_prom
suffix:semicolon
multiline_comment|/* LLC group (multicast) frame prom mode */
multiline_comment|/* Link available flag needed to determine whether to drop outgoing packet requests */
DECL|member|link_available
id|u32
id|link_available
suffix:semicolon
multiline_comment|/* is link available? */
multiline_comment|/* Resources to indicate reset type when resetting adapter */
DECL|member|reset_type
id|u32
id|reset_type
suffix:semicolon
multiline_comment|/* skip or rerun diagnostics */
multiline_comment|/* Store pointers to receive buffers for queue processing code */
DECL|member|p_rcv_buff_va
r_char
op_star
id|p_rcv_buff_va
(braket
id|PI_RCV_DATA_K_NUM_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* Store pointers to transmit buffers for transmit completion code */
DECL|member|xmt_drv_descr_blk
id|XMT_DRIVER_DESCR
id|xmt_drv_descr_blk
(braket
id|PI_XMT_DATA_K_NUM_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* Transmit spinlocks */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Store device, bus-specific, and parameter information for this adapter */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* pointer to device structure */
DECL|member|next
r_struct
id|net_device
op_star
id|next
suffix:semicolon
DECL|member|bus_type
id|u32
id|bus_type
suffix:semicolon
multiline_comment|/* bus type (0 == PCI, 1 == EISA) */
DECL|member|base_addr
id|u16
id|base_addr
suffix:semicolon
multiline_comment|/* base I/O address (same as dev-&gt;base_addr) */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|full_duplex_enb
id|u32
id|full_duplex_enb
suffix:semicolon
multiline_comment|/* FDDI Full Duplex enable (1 == on, 2 == off) */
DECL|member|req_ttrt
id|u32
id|req_ttrt
suffix:semicolon
multiline_comment|/* requested TTRT value (in 80ns units) */
DECL|member|burst_size
id|u32
id|burst_size
suffix:semicolon
multiline_comment|/* adapter burst size (enumerated) */
DECL|member|rcv_bufs_to_post
id|u32
id|rcv_bufs_to_post
suffix:semicolon
multiline_comment|/* receive buffers to post for LLC host queue */
DECL|member|factory_mac_addr
id|u8
id|factory_mac_addr
(braket
id|FDDI_K_ALEN
)braket
suffix:semicolon
multiline_comment|/* factory (on-board) MAC address */
multiline_comment|/* Common FDDI statistics structure and private counters */
DECL|member|stats
r_struct
id|fddi_statistics
id|stats
suffix:semicolon
DECL|member|rcv_discards
id|u32
id|rcv_discards
suffix:semicolon
DECL|member|rcv_crc_errors
id|u32
id|rcv_crc_errors
suffix:semicolon
DECL|member|rcv_frame_status_errors
id|u32
id|rcv_frame_status_errors
suffix:semicolon
DECL|member|rcv_length_errors
id|u32
id|rcv_length_errors
suffix:semicolon
DECL|member|rcv_total_frames
id|u32
id|rcv_total_frames
suffix:semicolon
DECL|member|rcv_multicast_frames
id|u32
id|rcv_multicast_frames
suffix:semicolon
DECL|member|rcv_total_bytes
id|u32
id|rcv_total_bytes
suffix:semicolon
DECL|member|xmt_discards
id|u32
id|xmt_discards
suffix:semicolon
DECL|member|xmt_length_errors
id|u32
id|xmt_length_errors
suffix:semicolon
DECL|member|xmt_total_frames
id|u32
id|xmt_total_frames
suffix:semicolon
DECL|member|xmt_total_bytes
id|u32
id|xmt_total_bytes
suffix:semicolon
DECL|typedef|DFX_board_t
)brace
id|DFX_board_t
suffix:semicolon
macro_line|#endif&t;/* #ifndef _DEFXX_H_ */
eof
