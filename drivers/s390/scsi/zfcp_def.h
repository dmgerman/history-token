multiline_comment|/* &n; * &n; * linux/drivers/s390/scsi/zfcp_def.h&n; * &n; * FCP adapter driver for IBM eServer zSeries &n; * &n; * Copyright 2002 IBM Corporation &n; * Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt; &n; *            Raimund Schroeder &lt;raimund.schroeder@de.ibm.com&gt; &n; *            Aron Zeh &lt;arzeh@de.ibm.com&gt; &n; *            Wolfgang Taphorn &lt;taphorn@de.ibm.com&gt; &n; *            Stefan Bader &lt;stefan.bader@de.ibm.com&gt; &n; *            Heiko Carstens &lt;heiko.carstens@de.ibm.com&gt; &n; * &n; * This program is free software; you can redistribute it and/or modify &n; * it under the terms of the GNU General Public License as published by &n; * the Free Software Foundation; either version 2, or (at your option) &n; * any later version. &n; * &n; * This program is distributed in the hope that it will be useful, &n; * but WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; * GNU General Public License for more details. &n; * &n; * You should have received a copy of the GNU General Public License &n; * along with this program; if not, write to the Free Software &n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; */
macro_line|#ifndef ZFCP_DEF_H
DECL|macro|ZFCP_DEF_H
mdefine_line|#define ZFCP_DEF_H
multiline_comment|/* this drivers version (do not edit !!! generated and updated by cvs) */
DECL|macro|ZFCP_DEF_REVISION
mdefine_line|#define ZFCP_DEF_REVISION &quot;$Revision: 1.48 $&quot;
multiline_comment|/*************************** INCLUDES *****************************************/
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;../../fc4/fc.h&quot;
macro_line|#include &quot;zfcp_fsf.h&quot;&t;&t;&t;/* FSF SW Interface */
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/qdio.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
multiline_comment|/************************ DEBUG FLAGS *****************************************/
DECL|macro|ZFCP_PRINT_FLAGS
mdefine_line|#define&t;ZFCP_PRINT_FLAGS
DECL|macro|ZFCP_DEBUG_REQUESTS
mdefine_line|#define&t;ZFCP_DEBUG_REQUESTS     /* fsf_req tracing */
DECL|macro|ZFCP_DEBUG_COMMANDS
mdefine_line|#define ZFCP_DEBUG_COMMANDS     /* host_byte tracing */
DECL|macro|ZFCP_DEBUG_ABORTS
mdefine_line|#define ZFCP_DEBUG_ABORTS       /* scsi_cmnd abort tracing */
DECL|macro|ZFCP_DEBUG_INCOMING_ELS
mdefine_line|#define ZFCP_DEBUG_INCOMING_ELS /* incoming ELS tracing */
DECL|macro|ZFCP_STAT_REQSIZES
mdefine_line|#define&t;ZFCP_STAT_REQSIZES
DECL|macro|ZFCP_STAT_QUEUES
mdefine_line|#define&t;ZFCP_STAT_QUEUES
multiline_comment|/********************* SCSI SPECIFIC DEFINES *********************************/
multiline_comment|/* 32 bit for SCSI ID and LUN as long as the SCSI stack uses this type */
DECL|typedef|scsi_id_t
r_typedef
id|u32
id|scsi_id_t
suffix:semicolon
DECL|typedef|scsi_lun_t
r_typedef
id|u32
id|scsi_lun_t
suffix:semicolon
DECL|macro|ZFCP_ERP_SCSI_LOW_MEM_TIMEOUT
mdefine_line|#define ZFCP_ERP_SCSI_LOW_MEM_TIMEOUT           (100*HZ)
DECL|macro|ZFCP_SCSI_ER_TIMEOUT
mdefine_line|#define ZFCP_SCSI_ER_TIMEOUT                    (100*HZ)
DECL|macro|ZFCP_SCSI_HOST_FLUSH_TIMEOUT
mdefine_line|#define ZFCP_SCSI_HOST_FLUSH_TIMEOUT            (1*HZ)
multiline_comment|/********************* CIO/QDIO SPECIFIC DEFINES *****************************/
multiline_comment|/* Adapter Identification Parameters */
DECL|macro|ZFCP_CONTROL_UNIT_TYPE
mdefine_line|#define ZFCP_CONTROL_UNIT_TYPE  0x1731
DECL|macro|ZFCP_CONTROL_UNIT_MODEL
mdefine_line|#define ZFCP_CONTROL_UNIT_MODEL 0x03
DECL|macro|ZFCP_DEVICE_TYPE
mdefine_line|#define ZFCP_DEVICE_TYPE        0x1732
DECL|macro|ZFCP_DEVICE_MODEL
mdefine_line|#define ZFCP_DEVICE_MODEL       0x03
multiline_comment|/* allow as many chained SBALs as are supported by hardware */
DECL|macro|ZFCP_MAX_SBALS_PER_REQ
mdefine_line|#define ZFCP_MAX_SBALS_PER_REQ&t;&t;FSF_MAX_SBALS_PER_REQ
multiline_comment|/* DMQ bug workaround: don&squot;t use last SBALE */
DECL|macro|ZFCP_MAX_SBALES_PER_SBAL
mdefine_line|#define ZFCP_MAX_SBALES_PER_SBAL&t;(QDIO_MAX_ELEMENTS_PER_BUFFER - 1)
multiline_comment|/* index of last SBALE (with respect to DMQ bug workaround) */
DECL|macro|ZFCP_LAST_SBALE_PER_SBAL
mdefine_line|#define ZFCP_LAST_SBALE_PER_SBAL&t;(ZFCP_MAX_SBALES_PER_SBAL - 1)
multiline_comment|/* max. number of (data buffer) SBALEs in largest SBAL chain */
DECL|macro|ZFCP_MAX_SBALES_PER_REQ
mdefine_line|#define ZFCP_MAX_SBALES_PER_REQ&t;&t;&bslash;&n;&t;(ZFCP_MAX_SBALS_PER_REQ * ZFCP_MAX_SBALES_PER_SBAL - 2)
multiline_comment|/* request ID + QTCB in SBALE 0 + 1 of first SBAL in chain */
multiline_comment|/* FIXME(tune): free space should be one max. SBAL chain plus what? */
DECL|macro|ZFCP_QDIO_PCI_INTERVAL
mdefine_line|#define ZFCP_QDIO_PCI_INTERVAL&t;&t;(QDIO_MAX_BUFFERS_PER_Q &bslash;&n;                                         - (ZFCP_MAX_SBALS_PER_REQ + 4))
DECL|macro|ZFCP_SBAL_TIMEOUT
mdefine_line|#define ZFCP_SBAL_TIMEOUT               (5*HZ)
DECL|macro|ZFCP_TYPE2_RECOVERY_TIME
mdefine_line|#define ZFCP_TYPE2_RECOVERY_TIME        (8*HZ)
multiline_comment|/* queue polling (values in microseconds) */
DECL|macro|ZFCP_MAX_INPUT_THRESHOLD
mdefine_line|#define ZFCP_MAX_INPUT_THRESHOLD &t;5000&t;/* FIXME: tune */
DECL|macro|ZFCP_MAX_OUTPUT_THRESHOLD
mdefine_line|#define ZFCP_MAX_OUTPUT_THRESHOLD &t;1000&t;/* FIXME: tune */
DECL|macro|ZFCP_MIN_INPUT_THRESHOLD
mdefine_line|#define ZFCP_MIN_INPUT_THRESHOLD &t;1&t;/* ignored by QDIO layer */
DECL|macro|ZFCP_MIN_OUTPUT_THRESHOLD
mdefine_line|#define ZFCP_MIN_OUTPUT_THRESHOLD &t;1&t;/* ignored by QDIO layer */
DECL|macro|QDIO_SCSI_QFMT
mdefine_line|#define QDIO_SCSI_QFMT&t;&t;&t;1&t;/* 1 for FSF */
multiline_comment|/********************* FSF SPECIFIC DEFINES *********************************/
DECL|macro|ZFCP_ULP_INFO_VERSION
mdefine_line|#define ZFCP_ULP_INFO_VERSION                   26
DECL|macro|ZFCP_QTCB_VERSION
mdefine_line|#define ZFCP_QTCB_VERSION&t;FSF_QTCB_CURRENT_VERSION
multiline_comment|/* ATTENTION: value must not be used by hardware */
DECL|macro|FSF_QTCB_UNSOLICITED_STATUS
mdefine_line|#define FSF_QTCB_UNSOLICITED_STATUS&t;&t;0x6305
DECL|macro|ZFCP_STATUS_READ_FAILED_THRESHOLD
mdefine_line|#define ZFCP_STATUS_READ_FAILED_THRESHOLD&t;3
DECL|macro|ZFCP_STATUS_READS_RECOM
mdefine_line|#define ZFCP_STATUS_READS_RECOM&t;&t;        FSF_STATUS_READS_RECOM
DECL|macro|ZFCP_EXCHANGE_CONFIG_DATA_RETRIES
mdefine_line|#define ZFCP_EXCHANGE_CONFIG_DATA_RETRIES&t;6
DECL|macro|ZFCP_EXCHANGE_CONFIG_DATA_SLEEP
mdefine_line|#define ZFCP_EXCHANGE_CONFIG_DATA_SLEEP&t;&t;50
DECL|macro|ZFCP_QTCB_SIZE
mdefine_line|#define ZFCP_QTCB_SIZE&t;&t;(sizeof(struct fsf_qtcb) + FSF_QTCB_LOG_SIZE)
DECL|macro|ZFCP_QTCB_AND_REQ_SIZE
mdefine_line|#define ZFCP_QTCB_AND_REQ_SIZE&t;(sizeof(struct zfcp_fsf_req) + ZFCP_QTCB_SIZE)
multiline_comment|/*************** FIBRE CHANNEL PROTOCOL SPECIFIC DEFINES ********************/
DECL|typedef|wwn_t
r_typedef
r_int
r_int
r_int
id|wwn_t
suffix:semicolon
DECL|typedef|fc_id_t
r_typedef
r_int
r_int
id|fc_id_t
suffix:semicolon
DECL|typedef|fcp_lun_t
r_typedef
r_int
r_int
r_int
id|fcp_lun_t
suffix:semicolon
multiline_comment|/* data length field may be at variable position in FCP-2 FCP_CMND IU */
DECL|typedef|fcp_dl_t
r_typedef
r_int
r_int
id|fcp_dl_t
suffix:semicolon
DECL|macro|ZFCP_FC_SERVICE_CLASS_DEFAULT
mdefine_line|#define ZFCP_FC_SERVICE_CLASS_DEFAULT&t;FSF_CLASS_3
multiline_comment|/* timeout for name-server lookup (in seconds) */
DECL|macro|ZFCP_NAMESERVER_TIMEOUT
mdefine_line|#define ZFCP_NAMESERVER_TIMEOUT&t;&t;10
multiline_comment|/* largest SCSI command we can process */
multiline_comment|/* FCP-2 (FCP_CMND IU) allows up to (255-3+16) */
DECL|macro|ZFCP_MAX_SCSI_CMND_LENGTH
mdefine_line|#define ZFCP_MAX_SCSI_CMND_LENGTH&t;255
multiline_comment|/* maximum number of commands in LUN queue (tagged queueing) */
DECL|macro|ZFCP_CMND_PER_LUN
mdefine_line|#define ZFCP_CMND_PER_LUN               32
multiline_comment|/* task attribute values in FCP-2 FCP_CMND IU */
DECL|macro|SIMPLE_Q
mdefine_line|#define SIMPLE_Q&t;0
DECL|macro|HEAD_OF_Q
mdefine_line|#define HEAD_OF_Q&t;1
DECL|macro|ORDERED_Q
mdefine_line|#define ORDERED_Q&t;2
DECL|macro|ACA_Q
mdefine_line|#define ACA_Q&t;&t;4
DECL|macro|UNTAGGED
mdefine_line|#define UNTAGGED&t;5
multiline_comment|/* task management flags in FCP-2 FCP_CMND IU */
DECL|macro|CLEAR_ACA
mdefine_line|#define CLEAR_ACA&t;&t;0x40
DECL|macro|TARGET_RESET
mdefine_line|#define TARGET_RESET&t;&t;0x20
DECL|macro|LOGICAL_UNIT_RESET
mdefine_line|#define LOGICAL_UNIT_RESET&t;0x10
DECL|macro|CLEAR_TASK_SET
mdefine_line|#define CLEAR_TASK_SET&t;&t;0x04
DECL|macro|ABORT_TASK_SET
mdefine_line|#define ABORT_TASK_SET&t;&t;0x02
DECL|macro|FCP_CDB_LENGTH
mdefine_line|#define FCP_CDB_LENGTH&t;&t;16
DECL|macro|ZFCP_DID_MASK
mdefine_line|#define ZFCP_DID_MASK           0x00FFFFFF
multiline_comment|/* FCP(-2) FCP_CMND IU */
DECL|struct|fcp_cmnd_iu
r_struct
id|fcp_cmnd_iu
(brace
DECL|member|fcp_lun
id|fcp_lun_t
id|fcp_lun
suffix:semicolon
multiline_comment|/* FCP logical unit number */
DECL|member|crn
id|u8
id|crn
suffix:semicolon
multiline_comment|/* command reference number */
DECL|member|reserved0
id|u8
id|reserved0
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|task_attribute
id|u8
id|task_attribute
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* task attribute */
DECL|member|task_management_flags
id|u8
id|task_management_flags
suffix:semicolon
multiline_comment|/* task management flags */
DECL|member|add_fcp_cdb_length
id|u8
id|add_fcp_cdb_length
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* additional FCP_CDB length */
DECL|member|rddata
id|u8
id|rddata
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* read data */
DECL|member|wddata
id|u8
id|wddata
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* write data */
DECL|member|fcp_cdb
id|u8
id|fcp_cdb
(braket
id|FCP_CDB_LENGTH
)braket
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
multiline_comment|/* FCP(-2) FCP_RSP IU */
DECL|struct|fcp_rsp_iu
r_struct
id|fcp_rsp_iu
(brace
DECL|member|reserved0
id|u8
id|reserved0
(braket
l_int|10
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|reserved1
id|u8
id|reserved1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|fcp_conf_req
id|u8
id|fcp_conf_req
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fcp_resid_under
id|u8
id|fcp_resid_under
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fcp_resid_over
id|u8
id|fcp_resid_over
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fcp_sns_len_valid
id|u8
id|fcp_sns_len_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fcp_rsp_len_valid
id|u8
id|fcp_rsp_len_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|value
id|u8
id|value
suffix:semicolon
DECL|member|validity
)brace
id|validity
suffix:semicolon
DECL|member|scsi_status
id|u8
id|scsi_status
suffix:semicolon
DECL|member|fcp_resid
id|u32
id|fcp_resid
suffix:semicolon
DECL|member|fcp_sns_len
id|u32
id|fcp_sns_len
suffix:semicolon
DECL|member|fcp_rsp_len
id|u32
id|fcp_rsp_len
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
DECL|macro|RSP_CODE_GOOD
mdefine_line|#define RSP_CODE_GOOD&t;&t; 0
DECL|macro|RSP_CODE_LENGTH_MISMATCH
mdefine_line|#define RSP_CODE_LENGTH_MISMATCH 1
DECL|macro|RSP_CODE_FIELD_INVALID
mdefine_line|#define RSP_CODE_FIELD_INVALID&t; 2
DECL|macro|RSP_CODE_RO_MISMATCH
mdefine_line|#define RSP_CODE_RO_MISMATCH&t; 3
DECL|macro|RSP_CODE_TASKMAN_UNSUPP
mdefine_line|#define RSP_CODE_TASKMAN_UNSUPP&t; 4
DECL|macro|RSP_CODE_TASKMAN_FAILED
mdefine_line|#define RSP_CODE_TASKMAN_FAILED&t; 5
multiline_comment|/* see fc-fs */
DECL|macro|LS_FAN
mdefine_line|#define LS_FAN 0x60000000
DECL|macro|LS_RSCN
mdefine_line|#define LS_RSCN 0x61040000
DECL|struct|fcp_rscn_head
r_struct
id|fcp_rscn_head
(brace
DECL|member|command
id|u8
id|command
suffix:semicolon
DECL|member|page_length
id|u8
id|page_length
suffix:semicolon
multiline_comment|/* always 0x04 */
DECL|member|payload_len
id|u16
id|payload_len
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
DECL|struct|fcp_rscn_element
r_struct
id|fcp_rscn_element
(brace
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|event_qual
id|u8
id|event_qual
suffix:colon
l_int|4
suffix:semicolon
DECL|member|addr_format
id|u8
id|addr_format
suffix:colon
l_int|2
suffix:semicolon
DECL|member|nport_did
id|u32
id|nport_did
suffix:colon
l_int|24
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
DECL|macro|ZFCP_PORT_ADDRESS
mdefine_line|#define ZFCP_PORT_ADDRESS   0x0
DECL|macro|ZFCP_AREA_ADDRESS
mdefine_line|#define ZFCP_AREA_ADDRESS   0x1
DECL|macro|ZFCP_DOMAIN_ADDRESS
mdefine_line|#define ZFCP_DOMAIN_ADDRESS 0x2
DECL|macro|ZFCP_FABRIC_ADDRESS
mdefine_line|#define ZFCP_FABRIC_ADDRESS 0x3
DECL|macro|ZFCP_PORTS_RANGE_PORT
mdefine_line|#define ZFCP_PORTS_RANGE_PORT   0xFFFFFF
DECL|macro|ZFCP_PORTS_RANGE_AREA
mdefine_line|#define ZFCP_PORTS_RANGE_AREA   0xFFFF00
DECL|macro|ZFCP_PORTS_RANGE_DOMAIN
mdefine_line|#define ZFCP_PORTS_RANGE_DOMAIN 0xFF0000
DECL|macro|ZFCP_PORTS_RANGE_FABRIC
mdefine_line|#define ZFCP_PORTS_RANGE_FABRIC 0x000000
DECL|macro|ZFCP_NO_PORTS_PER_AREA
mdefine_line|#define ZFCP_NO_PORTS_PER_AREA    0x100
DECL|macro|ZFCP_NO_PORTS_PER_DOMAIN
mdefine_line|#define ZFCP_NO_PORTS_PER_DOMAIN  0x10000
DECL|macro|ZFCP_NO_PORTS_PER_FABRIC
mdefine_line|#define ZFCP_NO_PORTS_PER_FABRIC  0x1000000
DECL|struct|fcp_fan
r_struct
id|fcp_fan
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|fport_did
id|u32
id|fport_did
suffix:semicolon
DECL|member|fport_wwpn
id|wwn_t
id|fport_wwpn
suffix:semicolon
DECL|member|fport_wwname
id|wwn_t
id|fport_wwname
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
multiline_comment|/* see fc-ph */
DECL|struct|fcp_logo
r_struct
id|fcp_logo
(brace
DECL|member|command
id|u32
id|command
suffix:semicolon
DECL|member|nport_did
id|u32
id|nport_did
suffix:semicolon
DECL|member|nport_wwpn
id|wwn_t
id|nport_wwpn
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
DECL|struct|fc_ct_iu
r_struct
id|fc_ct_iu
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* 0x01 */
DECL|member|in_id
id|u8
id|in_id
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|gs_type
id|u8
id|gs_type
suffix:semicolon
multiline_comment|/* 0xFC&t;Directory Service */
DECL|member|gs_subtype
id|u8
id|gs_subtype
suffix:semicolon
multiline_comment|/* 0x02&t;Name Server */
DECL|member|options
id|u8
id|options
suffix:semicolon
multiline_comment|/* 0x10 synchronous/single exchange */
DECL|member|reserved0
id|u8
id|reserved0
suffix:semicolon
DECL|member|cmd_rsp_code
id|u16
id|cmd_rsp_code
suffix:semicolon
multiline_comment|/* 0x0121 GID_PN */
DECL|member|max_res_size
id|u16
id|max_res_size
suffix:semicolon
multiline_comment|/* &lt;= (4096 - 16) / 4 */
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|reason_code
id|u8
id|reason_code
suffix:semicolon
DECL|member|reason_code_expl
id|u8
id|reason_code_expl
suffix:semicolon
DECL|member|vendor_unique
id|u8
id|vendor_unique
suffix:semicolon
r_union
(brace
DECL|member|wwpn
id|wwn_t
id|wwpn
suffix:semicolon
DECL|member|d_id
id|fc_id_t
id|d_id
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
DECL|macro|ZFCP_CT_REVISION
mdefine_line|#define ZFCP_CT_REVISION&t;&t;0x01
DECL|macro|ZFCP_CT_DIRECTORY_SERVICE
mdefine_line|#define ZFCP_CT_DIRECTORY_SERVICE&t;0xFC
DECL|macro|ZFCP_CT_NAME_SERVER
mdefine_line|#define ZFCP_CT_NAME_SERVER&t;&t;0x02
DECL|macro|ZFCP_CT_SYNCHRONOUS
mdefine_line|#define ZFCP_CT_SYNCHRONOUS&t;&t;0x00
DECL|macro|ZFCP_CT_GID_PN
mdefine_line|#define ZFCP_CT_GID_PN&t;&t;&t;0x0121
DECL|macro|ZFCP_CT_MAX_SIZE
mdefine_line|#define ZFCP_CT_MAX_SIZE&t;&t;0x1020
DECL|macro|ZFCP_CT_ACCEPT
mdefine_line|#define ZFCP_CT_ACCEPT&t;&t;&t;0x8002
multiline_comment|/***************** S390 DEBUG FEATURE SPECIFIC DEFINES ***********************/
multiline_comment|/* debug feature entries per adapter */
DECL|macro|ZFCP_ERP_DBF_INDEX
mdefine_line|#define ZFCP_ERP_DBF_INDEX     1 
DECL|macro|ZFCP_ERP_DBF_AREAS
mdefine_line|#define ZFCP_ERP_DBF_AREAS     2
DECL|macro|ZFCP_ERP_DBF_LENGTH
mdefine_line|#define ZFCP_ERP_DBF_LENGTH    16
DECL|macro|ZFCP_ERP_DBF_LEVEL
mdefine_line|#define ZFCP_ERP_DBF_LEVEL     3
DECL|macro|ZFCP_ERP_DBF_NAME
mdefine_line|#define ZFCP_ERP_DBF_NAME      &quot;zfcperp&quot;
DECL|macro|ZFCP_REQ_DBF_INDEX
mdefine_line|#define ZFCP_REQ_DBF_INDEX     1
DECL|macro|ZFCP_REQ_DBF_AREAS
mdefine_line|#define ZFCP_REQ_DBF_AREAS     1
DECL|macro|ZFCP_REQ_DBF_LENGTH
mdefine_line|#define ZFCP_REQ_DBF_LENGTH    8
DECL|macro|ZFCP_REQ_DBF_LEVEL
mdefine_line|#define ZFCP_REQ_DBF_LEVEL     1
DECL|macro|ZFCP_REQ_DBF_NAME
mdefine_line|#define ZFCP_REQ_DBF_NAME      &quot;zfcpreq&quot;
DECL|macro|ZFCP_CMD_DBF_INDEX
mdefine_line|#define ZFCP_CMD_DBF_INDEX     2
DECL|macro|ZFCP_CMD_DBF_AREAS
mdefine_line|#define ZFCP_CMD_DBF_AREAS     1
DECL|macro|ZFCP_CMD_DBF_LENGTH
mdefine_line|#define ZFCP_CMD_DBF_LENGTH    8
DECL|macro|ZFCP_CMD_DBF_LEVEL
mdefine_line|#define ZFCP_CMD_DBF_LEVEL     3
DECL|macro|ZFCP_CMD_DBF_NAME
mdefine_line|#define ZFCP_CMD_DBF_NAME      &quot;zfcpcmd&quot;
DECL|macro|ZFCP_ABORT_DBF_INDEX
mdefine_line|#define ZFCP_ABORT_DBF_INDEX   2
DECL|macro|ZFCP_ABORT_DBF_AREAS
mdefine_line|#define ZFCP_ABORT_DBF_AREAS   1
DECL|macro|ZFCP_ABORT_DBF_LENGTH
mdefine_line|#define ZFCP_ABORT_DBF_LENGTH  8
DECL|macro|ZFCP_ABORT_DBF_LEVEL
mdefine_line|#define ZFCP_ABORT_DBF_LEVEL   6
DECL|macro|ZFCP_ABORT_DBF_NAME
mdefine_line|#define ZFCP_ABORT_DBF_NAME    &quot;zfcpabt&quot;
DECL|macro|ZFCP_IN_ELS_DBF_INDEX
mdefine_line|#define ZFCP_IN_ELS_DBF_INDEX  2
DECL|macro|ZFCP_IN_ELS_DBF_AREAS
mdefine_line|#define ZFCP_IN_ELS_DBF_AREAS  1
DECL|macro|ZFCP_IN_ELS_DBF_LENGTH
mdefine_line|#define ZFCP_IN_ELS_DBF_LENGTH 8
DECL|macro|ZFCP_IN_ELS_DBF_LEVEL
mdefine_line|#define ZFCP_IN_ELS_DBF_LEVEL  6
DECL|macro|ZFCP_IN_ELS_DBF_NAME
mdefine_line|#define ZFCP_IN_ELS_DBF_NAME   &quot;zfcpels&quot;
DECL|macro|ZFCP_ADAPTER_REQ_DBF_INDEX
mdefine_line|#define ZFCP_ADAPTER_REQ_DBF_INDEX  4 
DECL|macro|ZFCP_ADAPTER_REQ_DBF_AREAS
mdefine_line|#define ZFCP_ADAPTER_REQ_DBF_AREAS  1
DECL|macro|ZFCP_ADAPTER_REQ_DBF_LENGTH
mdefine_line|#define ZFCP_ADAPTER_REQ_DBF_LENGTH 8
DECL|macro|ZFCP_ADAPTER_REQ_DBF_LEVEL
mdefine_line|#define ZFCP_ADAPTER_REQ_DBF_LEVEL  6
multiline_comment|/******************** LOGGING MACROS AND DEFINES *****************************/
multiline_comment|/*&n; * Logging may be applied on certain kinds of driver operations&n; * independently. Additionally, different log-levels are supported for&n; * each of these areas.&n; */
DECL|macro|ZFCP_NAME
mdefine_line|#define ZFCP_NAME               &quot;zfcp&quot;
multiline_comment|/* independent log areas */
DECL|macro|ZFCP_LOG_AREA_OTHER
mdefine_line|#define ZFCP_LOG_AREA_OTHER&t;0
DECL|macro|ZFCP_LOG_AREA_SCSI
mdefine_line|#define ZFCP_LOG_AREA_SCSI&t;1
DECL|macro|ZFCP_LOG_AREA_FSF
mdefine_line|#define ZFCP_LOG_AREA_FSF&t;2
DECL|macro|ZFCP_LOG_AREA_CONFIG
mdefine_line|#define ZFCP_LOG_AREA_CONFIG&t;3
DECL|macro|ZFCP_LOG_AREA_CIO
mdefine_line|#define ZFCP_LOG_AREA_CIO&t;4
DECL|macro|ZFCP_LOG_AREA_QDIO
mdefine_line|#define ZFCP_LOG_AREA_QDIO&t;5
DECL|macro|ZFCP_LOG_AREA_ERP
mdefine_line|#define ZFCP_LOG_AREA_ERP&t;6
DECL|macro|ZFCP_LOG_AREA_FC
mdefine_line|#define ZFCP_LOG_AREA_FC&t;7
multiline_comment|/* log level values*/
DECL|macro|ZFCP_LOG_LEVEL_NORMAL
mdefine_line|#define ZFCP_LOG_LEVEL_NORMAL&t;0
DECL|macro|ZFCP_LOG_LEVEL_INFO
mdefine_line|#define ZFCP_LOG_LEVEL_INFO&t;1
DECL|macro|ZFCP_LOG_LEVEL_DEBUG
mdefine_line|#define ZFCP_LOG_LEVEL_DEBUG&t;2
DECL|macro|ZFCP_LOG_LEVEL_TRACE
mdefine_line|#define ZFCP_LOG_LEVEL_TRACE&t;3
multiline_comment|/* default log levels for different log areas */
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_OTHER
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_OTHER&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_SCSI
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_SCSI&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_FSF
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_FSF&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_CONFIG
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_CONFIG&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_CIO
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_CIO&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_QDIO
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_QDIO&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_ERP
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_ERP&t;ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_LEVEL_DEFAULT_FC
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULT_FC&t;ZFCP_LOG_LEVEL_INFO
multiline_comment|/*&n; * this allows removal of logging code by the preprocessor&n; * (the most detailed log level still to be compiled in is specified, &n; * higher log levels are removed)&n; */
DECL|macro|ZFCP_LOG_LEVEL_LIMIT
mdefine_line|#define ZFCP_LOG_LEVEL_LIMIT&t;ZFCP_LOG_LEVEL_TRACE
multiline_comment|/* positional &quot;loglevel&quot; nibble assignment */
DECL|macro|ZFCP_LOG_VALUE
mdefine_line|#define ZFCP_LOG_VALUE(zfcp_lognibble) &bslash;&n;&t;       ((atomic_read(&amp;zfcp_data.loglevel) &gt;&gt; (zfcp_lognibble&lt;&lt;2)) &amp; 0xF)
DECL|macro|ZFCP_LOG_VALUE_OTHER
mdefine_line|#define ZFCP_LOG_VALUE_OTHER&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_OTHER)
DECL|macro|ZFCP_LOG_VALUE_SCSI
mdefine_line|#define ZFCP_LOG_VALUE_SCSI&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_SCSI)
DECL|macro|ZFCP_LOG_VALUE_FSF
mdefine_line|#define ZFCP_LOG_VALUE_FSF&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_FSF)
DECL|macro|ZFCP_LOG_VALUE_CONFIG
mdefine_line|#define ZFCP_LOG_VALUE_CONFIG&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_CONFIG)
DECL|macro|ZFCP_LOG_VALUE_CIO
mdefine_line|#define ZFCP_LOG_VALUE_CIO&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_CIO)
DECL|macro|ZFCP_LOG_VALUE_QDIO
mdefine_line|#define ZFCP_LOG_VALUE_QDIO&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_QDIO)
DECL|macro|ZFCP_LOG_VALUE_ERP
mdefine_line|#define ZFCP_LOG_VALUE_ERP&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_ERP)
DECL|macro|ZFCP_LOG_VALUE_FC
mdefine_line|#define ZFCP_LOG_VALUE_FC&t;ZFCP_LOG_VALUE(ZFCP_LOG_AREA_FC)
multiline_comment|/* all log-level defaults are combined to generate initial log-level */
DECL|macro|ZFCP_LOG_LEVEL_DEFAULTS
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULTS &bslash;&n;&t;((ZFCP_LOG_LEVEL_DEFAULT_OTHER&t;&lt;&lt; (ZFCP_LOG_AREA_OTHER&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_SCSI&t;&lt;&lt; (ZFCP_LOG_AREA_SCSI&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_FSF&t;&lt;&lt; (ZFCP_LOG_AREA_FSF&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_CONFIG&t;&lt;&lt; (ZFCP_LOG_AREA_CONFIG&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_CIO&t;&lt;&lt; (ZFCP_LOG_AREA_CIO&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_QDIO&t;&lt;&lt; (ZFCP_LOG_AREA_QDIO&lt;&lt;2))&t;| &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_ERP&t;&lt;&lt; (ZFCP_LOG_AREA_ERP&lt;&lt;2))      | &bslash;&n;&t; (ZFCP_LOG_LEVEL_DEFAULT_FC&t;&lt;&lt; (ZFCP_LOG_AREA_FC&lt;&lt;2)))
multiline_comment|/* the prefix placed at the beginning of each driver message */
DECL|macro|ZFCP_LOG_PREFIX
mdefine_line|#define ZFCP_LOG_PREFIX ZFCP_NAME&quot;: &quot;
multiline_comment|/* log area specific prefixes */
DECL|macro|ZFCP_LOG_AREA_PREFIX_OTHER
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_OTHER&t;&quot;&quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_SCSI
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_SCSI&t;&quot;SCSI: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_FSF
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_FSF&t;&quot;FSF: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_CONFIG
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_CONFIG&t;&quot;config: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_CIO
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_CIO&t;&quot;common I/O: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_QDIO
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_QDIO&t;&quot;QDIO: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_ERP
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_ERP&t;&quot;ERP: &quot;
DECL|macro|ZFCP_LOG_AREA_PREFIX_FC
mdefine_line|#define ZFCP_LOG_AREA_PREFIX_FC &t;&quot;FC: &quot;
multiline_comment|/* check whether we have the right level for logging */
DECL|macro|ZFCP_LOG_CHECK
mdefine_line|#define ZFCP_LOG_CHECK(ll)&t;(ZFCP_LOG_VALUE(ZFCP_LOG_AREA)) &gt;= ll
multiline_comment|/* As we have two printks it is possible for them to be seperated by another&n; * message. This holds true even for printks from within this module.&n; * In any case there should only be a small readability hit, however.&n; */
DECL|macro|_ZFCP_LOG
mdefine_line|#define _ZFCP_LOG(m...) &bslash;&n;&t;&t;{ &bslash;&n;&t;&t;&t;printk( &quot;%s%s: &quot;, &bslash;&n;&t;&t;&t;&t;ZFCP_LOG_PREFIX ZFCP_LOG_AREA_PREFIX, &bslash;&n;&t;&t;&t;&t;__FUNCTION__); &bslash;&n;&t;&t;&t;printk(m); &bslash;&n;&t;&t;}
DECL|macro|ZFCP_LOG
mdefine_line|#define ZFCP_LOG(ll, m...) &bslash;&n;&t;&t;if (ZFCP_LOG_CHECK(ll)) &bslash;&n;&t;&t;&t;_ZFCP_LOG(m)
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_NORMAL
DECL|macro|ZFCP_LOG_NORMAL
mdefine_line|#define ZFCP_LOG_NORMAL(m...)
macro_line|#else&t;/* ZFCP_LOG_LEVEL_LIMIT &gt;= ZFCP_LOG_LEVEL_NORMAL */
DECL|macro|ZFCP_LOG_NORMAL
mdefine_line|#define ZFCP_LOG_NORMAL(m...)&t;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_NORMAL, m)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_INFO
mdefine_line|#define ZFCP_LOG_INFO(m...)
macro_line|#else&t;/* ZFCP_LOG_LEVEL_LIMIT &gt;= ZFCP_LOG_LEVEL_INFO */
DECL|macro|ZFCP_LOG_INFO
mdefine_line|#define ZFCP_LOG_INFO(m...)&t;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_INFO, m)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_DEBUG
DECL|macro|ZFCP_LOG_DEBUG
mdefine_line|#define ZFCP_LOG_DEBUG(m...)
macro_line|#else&t;/* ZFCP_LOG_LEVEL_LIMIT &gt;= ZFCP_LOG_LEVEL_DEBUG */
DECL|macro|ZFCP_LOG_DEBUG
mdefine_line|#define ZFCP_LOG_DEBUG(m...)&t;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_DEBUG, m)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_TRACE
DECL|macro|ZFCP_LOG_TRACE
mdefine_line|#define ZFCP_LOG_TRACE(m...)
macro_line|#else&t;/* ZFCP_LOG_LEVEL_LIMIT &gt;= ZFCP_LOG_LEVEL_TRACE */
DECL|macro|ZFCP_LOG_TRACE
mdefine_line|#define ZFCP_LOG_TRACE(m...)&t;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_TRACE, m)
macro_line|#endif
macro_line|#ifdef ZFCP_PRINT_FLAGS
r_extern
id|u32
id|flags_dump
suffix:semicolon
DECL|macro|ZFCP_LOG_FLAGS
mdefine_line|#define ZFCP_LOG_FLAGS(ll, m...) &bslash;&n;&t;&t;if (ll&lt;=flags_dump) &bslash;&n;&t;&t;&t;_ZFCP_LOG(m)
macro_line|#else
DECL|macro|ZFCP_LOG_FLAGS
mdefine_line|#define ZFCP_LOG_FLAGS(ll, m...)
macro_line|#endif
multiline_comment|/*************** ADAPTER/PORT/UNIT AND FSF_REQ STATUS FLAGS ******************/
multiline_comment|/* &n; * Note, the leftmost status byte is common among adapter, port &n; * and unit&n; */
DECL|macro|ZFCP_COMMON_FLAGS
mdefine_line|#define ZFCP_COMMON_FLAGS                       0xff000000
DECL|macro|ZFCP_SPECIFIC_FLAGS
mdefine_line|#define ZFCP_SPECIFIC_FLAGS                     0x00ffffff
multiline_comment|/* common status bits */
DECL|macro|ZFCP_STATUS_COMMON_REMOVE
mdefine_line|#define ZFCP_STATUS_COMMON_REMOVE&t;&t;0x80000000
DECL|macro|ZFCP_STATUS_COMMON_RUNNING
mdefine_line|#define ZFCP_STATUS_COMMON_RUNNING&t;&t;0x40000000
DECL|macro|ZFCP_STATUS_COMMON_ERP_FAILED
mdefine_line|#define ZFCP_STATUS_COMMON_ERP_FAILED&t;&t;0x20000000
DECL|macro|ZFCP_STATUS_COMMON_UNBLOCKED
mdefine_line|#define ZFCP_STATUS_COMMON_UNBLOCKED&t;&t;0x10000000
DECL|macro|ZFCP_STATUS_COMMON_OPENING
mdefine_line|#define ZFCP_STATUS_COMMON_OPENING              0x08000000
DECL|macro|ZFCP_STATUS_COMMON_OPEN
mdefine_line|#define ZFCP_STATUS_COMMON_OPEN                 0x04000000
DECL|macro|ZFCP_STATUS_COMMON_CLOSING
mdefine_line|#define ZFCP_STATUS_COMMON_CLOSING              0x02000000
DECL|macro|ZFCP_STATUS_COMMON_ERP_INUSE
mdefine_line|#define ZFCP_STATUS_COMMON_ERP_INUSE&t;&t;0x01000000
multiline_comment|/* adapter status */
DECL|macro|ZFCP_STATUS_ADAPTER_QDIOUP
mdefine_line|#define ZFCP_STATUS_ADAPTER_QDIOUP&t;&t;0x00000002
DECL|macro|ZFCP_STATUS_ADAPTER_REGISTERED
mdefine_line|#define ZFCP_STATUS_ADAPTER_REGISTERED&t;&t;0x00000004
DECL|macro|ZFCP_STATUS_ADAPTER_XCONFIG_OK
mdefine_line|#define ZFCP_STATUS_ADAPTER_XCONFIG_OK&t;&t;0x00000008
DECL|macro|ZFCP_STATUS_ADAPTER_HOST_CON_INIT
mdefine_line|#define ZFCP_STATUS_ADAPTER_HOST_CON_INIT&t;0x00000010
DECL|macro|ZFCP_STATUS_ADAPTER_ERP_THREAD_UP
mdefine_line|#define ZFCP_STATUS_ADAPTER_ERP_THREAD_UP&t;0x00000020
DECL|macro|ZFCP_STATUS_ADAPTER_ERP_THREAD_KILL
mdefine_line|#define ZFCP_STATUS_ADAPTER_ERP_THREAD_KILL&t;0x00000080
DECL|macro|ZFCP_STATUS_ADAPTER_ERP_PENDING
mdefine_line|#define ZFCP_STATUS_ADAPTER_ERP_PENDING&t;&t;0x00000100
DECL|macro|ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED
mdefine_line|#define ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED&t;0x00000200
DECL|macro|ZFCP_STATUS_ADAPTER_SCSI_UP
mdefine_line|#define ZFCP_STATUS_ADAPTER_SCSI_UP&t;&t;&t;&bslash;&n;&t;&t;(ZFCP_STATUS_COMMON_UNBLOCKED |&t;&bslash;&n;&t;&t; ZFCP_STATUS_ADAPTER_REGISTERED)
DECL|macro|ZFCP_DID_NAMESERVER
mdefine_line|#define ZFCP_DID_NAMESERVER&t;&t;&t;0xFFFFFC
multiline_comment|/* remote port status */
DECL|macro|ZFCP_STATUS_PORT_PHYS_OPEN
mdefine_line|#define ZFCP_STATUS_PORT_PHYS_OPEN&t;&t;0x00000001
DECL|macro|ZFCP_STATUS_PORT_DID_DID
mdefine_line|#define ZFCP_STATUS_PORT_DID_DID&t;&t;0x00000002
DECL|macro|ZFCP_STATUS_PORT_PHYS_CLOSING
mdefine_line|#define ZFCP_STATUS_PORT_PHYS_CLOSING&t;&t;0x00000004
DECL|macro|ZFCP_STATUS_PORT_NO_WWPN
mdefine_line|#define ZFCP_STATUS_PORT_NO_WWPN&t;&t;0x00000008
DECL|macro|ZFCP_STATUS_PORT_NO_SCSI_ID
mdefine_line|#define ZFCP_STATUS_PORT_NO_SCSI_ID&t;&t;0x00000010
DECL|macro|ZFCP_STATUS_PORT_INVALID_WWPN
mdefine_line|#define ZFCP_STATUS_PORT_INVALID_WWPN&t;&t;0x00000020
DECL|macro|ZFCP_STATUS_PORT_NAMESERVER
mdefine_line|#define ZFCP_STATUS_PORT_NAMESERVER &bslash;&n;&t;&t;(ZFCP_STATUS_PORT_NO_WWPN | &bslash;&n;&t;&t; ZFCP_STATUS_PORT_NO_SCSI_ID)
multiline_comment|/* logical unit status */
DECL|macro|ZFCP_STATUS_UNIT_NOTSUPPUNITRESET
mdefine_line|#define ZFCP_STATUS_UNIT_NOTSUPPUNITRESET&t;0x00000001
multiline_comment|/* FSF request status (this does not have a common part) */
DECL|macro|ZFCP_STATUS_FSFREQ_NOT_INIT
mdefine_line|#define ZFCP_STATUS_FSFREQ_NOT_INIT&t;&t;0x00000000
DECL|macro|ZFCP_STATUS_FSFREQ_POOL
mdefine_line|#define ZFCP_STATUS_FSFREQ_POOL  &t;&t;0x00000001
DECL|macro|ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT
mdefine_line|#define ZFCP_STATUS_FSFREQ_TASK_MANAGEMENT&t;0x00000002
DECL|macro|ZFCP_STATUS_FSFREQ_COMPLETED
mdefine_line|#define ZFCP_STATUS_FSFREQ_COMPLETED&t;&t;0x00000004
DECL|macro|ZFCP_STATUS_FSFREQ_ERROR
mdefine_line|#define ZFCP_STATUS_FSFREQ_ERROR&t;&t;0x00000008
DECL|macro|ZFCP_STATUS_FSFREQ_CLEANUP
mdefine_line|#define ZFCP_STATUS_FSFREQ_CLEANUP&t;&t;0x00000010
DECL|macro|ZFCP_STATUS_FSFREQ_ABORTING
mdefine_line|#define ZFCP_STATUS_FSFREQ_ABORTING&t;&t;0x00000020
DECL|macro|ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED
mdefine_line|#define ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED&t;0x00000040
DECL|macro|ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED
mdefine_line|#define ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED       0x00000080
DECL|macro|ZFCP_STATUS_FSFREQ_ABORTED
mdefine_line|#define ZFCP_STATUS_FSFREQ_ABORTED              0x00000100
DECL|macro|ZFCP_STATUS_FSFREQ_TMFUNCFAILED
mdefine_line|#define ZFCP_STATUS_FSFREQ_TMFUNCFAILED         0x00000200
DECL|macro|ZFCP_STATUS_FSFREQ_TMFUNCNOTSUPP
mdefine_line|#define ZFCP_STATUS_FSFREQ_TMFUNCNOTSUPP        0x00000400
DECL|macro|ZFCP_STATUS_FSFREQ_RETRY
mdefine_line|#define ZFCP_STATUS_FSFREQ_RETRY                0x00000800
DECL|macro|ZFCP_STATUS_FSFREQ_DISMISSED
mdefine_line|#define ZFCP_STATUS_FSFREQ_DISMISSED            0x00001000
DECL|macro|ZFCP_STATUS_FSFREQ_POOLBUF
mdefine_line|#define ZFCP_STATUS_FSFREQ_POOLBUF              0x00002000
multiline_comment|/*********************** ERROR RECOVERY PROCEDURE DEFINES ********************/
DECL|macro|ZFCP_MAX_ERPS
mdefine_line|#define ZFCP_MAX_ERPS                   3
DECL|macro|ZFCP_ERP_FSFREQ_TIMEOUT
mdefine_line|#define ZFCP_ERP_FSFREQ_TIMEOUT&t;&t;(100 * HZ)
DECL|macro|ZFCP_ERP_MEMWAIT_TIMEOUT
mdefine_line|#define ZFCP_ERP_MEMWAIT_TIMEOUT&t;HZ
DECL|macro|ZFCP_STATUS_ERP_TIMEDOUT
mdefine_line|#define ZFCP_STATUS_ERP_TIMEDOUT&t;0x10000000
DECL|macro|ZFCP_STATUS_ERP_CLOSE_ONLY
mdefine_line|#define ZFCP_STATUS_ERP_CLOSE_ONLY&t;0x01000000
DECL|macro|ZFCP_STATUS_ERP_DISMISSING
mdefine_line|#define ZFCP_STATUS_ERP_DISMISSING&t;0x00100000
DECL|macro|ZFCP_STATUS_ERP_DISMISSED
mdefine_line|#define ZFCP_STATUS_ERP_DISMISSED&t;0x00200000
DECL|macro|ZFCP_ERP_STEP_UNINITIALIZED
mdefine_line|#define ZFCP_ERP_STEP_UNINITIALIZED&t;0x00000000
DECL|macro|ZFCP_ERP_STEP_FSF_XCONFIG
mdefine_line|#define ZFCP_ERP_STEP_FSF_XCONFIG&t;0x00000001
DECL|macro|ZFCP_ERP_STEP_PHYS_PORT_CLOSING
mdefine_line|#define ZFCP_ERP_STEP_PHYS_PORT_CLOSING&t;0x00000010
DECL|macro|ZFCP_ERP_STEP_PORT_CLOSING
mdefine_line|#define ZFCP_ERP_STEP_PORT_CLOSING&t;0x00000100
DECL|macro|ZFCP_ERP_STEP_NAMESERVER_OPEN
mdefine_line|#define ZFCP_ERP_STEP_NAMESERVER_OPEN&t;0x00000200
DECL|macro|ZFCP_ERP_STEP_NAMESERVER_LOOKUP
mdefine_line|#define ZFCP_ERP_STEP_NAMESERVER_LOOKUP&t;0x00000400
DECL|macro|ZFCP_ERP_STEP_PORT_OPENING
mdefine_line|#define ZFCP_ERP_STEP_PORT_OPENING&t;0x00000800
DECL|macro|ZFCP_ERP_STEP_UNIT_CLOSING
mdefine_line|#define ZFCP_ERP_STEP_UNIT_CLOSING&t;0x00001000
DECL|macro|ZFCP_ERP_STEP_UNIT_OPENING
mdefine_line|#define ZFCP_ERP_STEP_UNIT_OPENING&t;0x00002000
multiline_comment|/* Ordered by escalation level (necessary for proper erp-code operation) */
DECL|macro|ZFCP_ERP_ACTION_REOPEN_ADAPTER
mdefine_line|#define ZFCP_ERP_ACTION_REOPEN_ADAPTER&t;&t;0x4
DECL|macro|ZFCP_ERP_ACTION_REOPEN_PORT_FORCED
mdefine_line|#define ZFCP_ERP_ACTION_REOPEN_PORT_FORCED&t;0x3
DECL|macro|ZFCP_ERP_ACTION_REOPEN_PORT
mdefine_line|#define ZFCP_ERP_ACTION_REOPEN_PORT&t;&t;0x2
DECL|macro|ZFCP_ERP_ACTION_REOPEN_UNIT
mdefine_line|#define ZFCP_ERP_ACTION_REOPEN_UNIT&t;&t;0x1
DECL|macro|ZFCP_ERP_ACTION_RUNNING
mdefine_line|#define ZFCP_ERP_ACTION_RUNNING&t;&t;&t;0x1
DECL|macro|ZFCP_ERP_ACTION_READY
mdefine_line|#define ZFCP_ERP_ACTION_READY&t;&t;&t;0x2
DECL|macro|ZFCP_ERP_SUCCEEDED
mdefine_line|#define ZFCP_ERP_SUCCEEDED&t;0x0
DECL|macro|ZFCP_ERP_FAILED
mdefine_line|#define ZFCP_ERP_FAILED&t;&t;0x1
DECL|macro|ZFCP_ERP_CONTINUES
mdefine_line|#define ZFCP_ERP_CONTINUES&t;0x2
DECL|macro|ZFCP_ERP_EXIT
mdefine_line|#define ZFCP_ERP_EXIT&t;&t;0x3
DECL|macro|ZFCP_ERP_DISMISSED
mdefine_line|#define ZFCP_ERP_DISMISSED&t;0x4
DECL|macro|ZFCP_ERP_NOMEM
mdefine_line|#define ZFCP_ERP_NOMEM&t;&t;0x5
multiline_comment|/************************* STRUCTURE DEFINITIONS *****************************/
r_struct
id|zfcp_fsf_req
suffix:semicolon
DECL|typedef|zfcp_send_generic_handler_t
r_typedef
r_void
id|zfcp_send_generic_handler_t
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
DECL|struct|zfcp_adapter_mempool
r_struct
id|zfcp_adapter_mempool
(brace
DECL|member|status_read_fsf
id|mempool_t
op_star
id|status_read_fsf
suffix:semicolon
DECL|member|status_read_buf
id|mempool_t
op_star
id|status_read_buf
suffix:semicolon
DECL|member|nameserver
id|mempool_t
op_star
id|nameserver
suffix:semicolon
DECL|member|erp_fsf
id|mempool_t
op_star
id|erp_fsf
suffix:semicolon
DECL|member|fcp_command_fsf
id|mempool_t
op_star
id|fcp_command_fsf
suffix:semicolon
DECL|member|fcp_command_fsf_timer
r_struct
id|timer_list
id|fcp_command_fsf_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_exchange_config_data
r_struct
id|zfcp_exchange_config_data
(brace
)brace
suffix:semicolon
DECL|struct|zfcp_open_port
r_struct
id|zfcp_open_port
(brace
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_close_port
r_struct
id|zfcp_close_port
(brace
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_open_unit
r_struct
id|zfcp_open_unit
(brace
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_close_unit
r_struct
id|zfcp_close_unit
(brace
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_close_physical_port
r_struct
id|zfcp_close_physical_port
(brace
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_send_fcp_command_task
r_struct
id|zfcp_send_fcp_command_task
(brace
DECL|member|fsf_req
r_struct
id|zfcp_fsf_req
op_star
id|fsf_req
suffix:semicolon
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
DECL|member|scsi_cmnd
id|Scsi_Cmnd
op_star
id|scsi_cmnd
suffix:semicolon
DECL|member|start_jiffies
r_int
r_int
id|start_jiffies
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_send_fcp_command_task_management
r_struct
id|zfcp_send_fcp_command_task_management
(brace
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_abort_fcp_command
r_struct
id|zfcp_abort_fcp_command
(brace
DECL|member|fsf_req
r_struct
id|zfcp_fsf_req
op_star
id|fsf_req
suffix:semicolon
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_send_generic
r_struct
id|zfcp_send_generic
(brace
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
DECL|member|outbuf
r_char
op_star
id|outbuf
suffix:semicolon
DECL|member|inbuf
r_char
op_star
id|inbuf
suffix:semicolon
DECL|member|outbuf_length
r_int
id|outbuf_length
suffix:semicolon
DECL|member|inbuf_length
r_int
id|inbuf_length
suffix:semicolon
DECL|member|handler
id|zfcp_send_generic_handler_t
op_star
id|handler
suffix:semicolon
DECL|member|handler_data
r_int
r_int
id|handler_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_status_read
r_struct
id|zfcp_status_read
(brace
DECL|member|buffer
r_struct
id|fsf_status_read_buffer
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* request specific data */
DECL|union|zfcp_req_data
r_union
id|zfcp_req_data
(brace
DECL|member|exchange_config_data
r_struct
id|zfcp_exchange_config_data
id|exchange_config_data
suffix:semicolon
DECL|member|open_port
r_struct
id|zfcp_open_port
id|open_port
suffix:semicolon
DECL|member|close_port
r_struct
id|zfcp_close_port
id|close_port
suffix:semicolon
DECL|member|open_unit
r_struct
id|zfcp_open_unit
id|open_unit
suffix:semicolon
DECL|member|close_unit
r_struct
id|zfcp_close_unit
id|close_unit
suffix:semicolon
DECL|member|close_physical_port
r_struct
id|zfcp_close_physical_port
id|close_physical_port
suffix:semicolon
DECL|member|send_fcp_command_task
r_struct
id|zfcp_send_fcp_command_task
id|send_fcp_command_task
suffix:semicolon
r_struct
id|zfcp_send_fcp_command_task_management
DECL|member|send_fcp_command_task_management
id|send_fcp_command_task_management
suffix:semicolon
DECL|member|abort_fcp_command
r_struct
id|zfcp_abort_fcp_command
id|abort_fcp_command
suffix:semicolon
DECL|member|send_generic
r_struct
id|zfcp_send_generic
id|send_generic
suffix:semicolon
DECL|member|status_read
r_struct
id|zfcp_status_read
id|status_read
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_qdio_queue
r_struct
id|zfcp_qdio_queue
(brace
DECL|member|buffer
r_struct
id|qdio_buffer
op_star
id|buffer
(braket
id|QDIO_MAX_BUFFERS_PER_Q
)braket
suffix:semicolon
multiline_comment|/* SBALs */
DECL|member|free_index
id|u8
id|free_index
suffix:semicolon
multiline_comment|/* index of next free bfr&n;&t;&t;&t;&t;&t;&t; in queue (free_count&gt;0) */
DECL|member|free_count
id|atomic_t
id|free_count
suffix:semicolon
multiline_comment|/* number of free buffers&n;&t;&t;&t;&t;&t;&t; in queue */
DECL|member|queue_lock
id|rwlock_t
id|queue_lock
suffix:semicolon
multiline_comment|/* lock for operations on queue */
DECL|member|distance_from_int
r_int
id|distance_from_int
suffix:semicolon
multiline_comment|/* SBALs used since PCI indication&n;&t;&t;&t;&t;&t;&t; was last set */
)brace
suffix:semicolon
DECL|struct|zfcp_erp_action
r_struct
id|zfcp_erp_action
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|action
r_int
id|action
suffix:semicolon
multiline_comment|/* requested action code */
DECL|member|adapter
r_struct
id|zfcp_adapter
op_star
id|adapter
suffix:semicolon
multiline_comment|/* device which should be recovered */
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
DECL|member|unit
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
DECL|member|status
r_volatile
id|u32
id|status
suffix:semicolon
multiline_comment|/* recovery status */
DECL|member|step
id|u32
id|step
suffix:semicolon
multiline_comment|/* active step of this erp action */
DECL|member|fsf_req
r_struct
id|zfcp_fsf_req
op_star
id|fsf_req
suffix:semicolon
multiline_comment|/* fsf request currently pending&n;&t;&t;&t;&t;&t; for this action */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zfcp_adapter
r_struct
id|zfcp_adapter
(brace
DECL|member|common_magic
id|u32
id|common_magic
suffix:semicolon
multiline_comment|/* driver common magic */
DECL|member|specific_magic
id|u32
id|specific_magic
suffix:semicolon
multiline_comment|/* struct specific magic */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of adapters */
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|remove_wq
id|wait_queue_head_t
id|remove_wq
suffix:semicolon
multiline_comment|/* can be used to wait for&n;&t;&t;&t;&t;&t;&t;      refcount drop to zero */
DECL|member|wwnn
id|wwn_t
id|wwnn
suffix:semicolon
multiline_comment|/* WWNN */
DECL|member|wwpn
id|wwn_t
id|wwpn
suffix:semicolon
multiline_comment|/* WWPN */
DECL|member|s_id
id|fc_id_t
id|s_id
suffix:semicolon
multiline_comment|/* N_Port ID */
DECL|member|ccw_device
r_struct
id|ccw_device
op_star
id|ccw_device
suffix:semicolon
multiline_comment|/* S/390 ccw device */
DECL|member|fc_service_class
id|u8
id|fc_service_class
suffix:semicolon
DECL|member|fc_topology
id|u32
id|fc_topology
suffix:semicolon
multiline_comment|/* FC topology */
DECL|member|fc_link_speed
id|u32
id|fc_link_speed
suffix:semicolon
multiline_comment|/* FC interface speed */
DECL|member|hydra_version
id|u32
id|hydra_version
suffix:semicolon
multiline_comment|/* Hydra version */
DECL|member|fsf_lic_version
id|u32
id|fsf_lic_version
suffix:semicolon
DECL|member|scsi_host
r_struct
id|Scsi_Host
op_star
id|scsi_host
suffix:semicolon
multiline_comment|/* Pointer to mid-layer */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|port_list_head
r_struct
id|list_head
id|port_list_head
suffix:semicolon
multiline_comment|/* remote port list */
DECL|member|port_remove_lh
r_struct
id|list_head
id|port_remove_lh
suffix:semicolon
multiline_comment|/* head of ports to be&n;&t;&t;&t;&t;&t;&t;      removed */
DECL|member|ports
id|u32
id|ports
suffix:semicolon
multiline_comment|/* number of remote ports */
DECL|member|max_scsi_id
id|scsi_id_t
id|max_scsi_id
suffix:semicolon
multiline_comment|/* largest SCSI ID */
DECL|member|max_scsi_lun
id|scsi_lun_t
id|max_scsi_lun
suffix:semicolon
multiline_comment|/* largest SCSI LUN */
DECL|member|scsi_er_timer
r_struct
id|timer_list
id|scsi_er_timer
suffix:semicolon
multiline_comment|/* SCSI err recovery watch */
DECL|member|fsf_req_list_head
r_struct
id|list_head
id|fsf_req_list_head
suffix:semicolon
multiline_comment|/* head of FSF req list */
DECL|member|fsf_req_list_lock
id|rwlock_t
id|fsf_req_list_lock
suffix:semicolon
multiline_comment|/* lock for ops on list of&n;&t;&t;&t;&t;&t;&t;      FSF requests */
DECL|member|fsf_reqs_active
id|atomic_t
id|fsf_reqs_active
suffix:semicolon
multiline_comment|/* # active FSF reqs */
DECL|member|request_queue
r_struct
id|zfcp_qdio_queue
id|request_queue
suffix:semicolon
multiline_comment|/* request queue */
DECL|member|fsf_req_seq_no
id|u32
id|fsf_req_seq_no
suffix:semicolon
multiline_comment|/* FSF cmnd seq number */
DECL|member|request_wq
id|wait_queue_head_t
id|request_wq
suffix:semicolon
multiline_comment|/* can be used to wait for&n;&t;&t;&t;&t;&t;&t;      more avaliable SBALs */
DECL|member|response_queue
r_struct
id|zfcp_qdio_queue
id|response_queue
suffix:semicolon
multiline_comment|/* response queue */
DECL|member|abort_lock
id|rwlock_t
id|abort_lock
suffix:semicolon
multiline_comment|/* Protects against SCSI&n;&t;&t;&t;&t;&t;&t;      stack abort/command&n;&t;&t;&t;&t;&t;&t;      completion races */
DECL|member|status_read_failed
id|u16
id|status_read_failed
suffix:semicolon
multiline_comment|/* # failed status reads */
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
multiline_comment|/* status of this adapter */
DECL|member|erp_ready_head
r_struct
id|list_head
id|erp_ready_head
suffix:semicolon
multiline_comment|/* error recovery for this&n;&t;&t;&t;&t;&t;&t;      adapter/devices */
DECL|member|erp_running_head
r_struct
id|list_head
id|erp_running_head
suffix:semicolon
DECL|member|erp_lock
id|rwlock_t
id|erp_lock
suffix:semicolon
DECL|member|erp_ready_sem
r_struct
id|semaphore
id|erp_ready_sem
suffix:semicolon
DECL|member|erp_thread_wqh
id|wait_queue_head_t
id|erp_thread_wqh
suffix:semicolon
DECL|member|erp_done_wqh
id|wait_queue_head_t
id|erp_done_wqh
suffix:semicolon
DECL|member|erp_action
r_struct
id|zfcp_erp_action
id|erp_action
suffix:semicolon
multiline_comment|/* pending error recovery */
DECL|member|erp_counter
id|atomic_t
id|erp_counter
suffix:semicolon
DECL|member|nameserver_port
r_struct
id|zfcp_port
op_star
id|nameserver_port
suffix:semicolon
multiline_comment|/* adapter&squot;s nameserver */
DECL|member|erp_dbf
id|debug_info_t
op_star
id|erp_dbf
suffix:semicolon
multiline_comment|/* S/390 debug features */
DECL|member|abort_dbf
id|debug_info_t
op_star
id|abort_dbf
suffix:semicolon
DECL|member|req_dbf
id|debug_info_t
op_star
id|req_dbf
suffix:semicolon
DECL|member|in_els_dbf
id|debug_info_t
op_star
id|in_els_dbf
suffix:semicolon
DECL|member|cmd_dbf
id|debug_info_t
op_star
id|cmd_dbf
suffix:semicolon
DECL|member|cmd_dbf_lock
id|rwlock_t
id|cmd_dbf_lock
suffix:semicolon
DECL|member|pool
r_struct
id|zfcp_adapter_mempool
id|pool
suffix:semicolon
multiline_comment|/* Adapter memory pools */
DECL|member|qdio_init_data
r_struct
id|qdio_initialize
id|qdio_init_data
suffix:semicolon
multiline_comment|/* for qdio_establish */
)brace
suffix:semicolon
DECL|struct|zfcp_port
r_struct
id|zfcp_port
(brace
DECL|member|common_magic
id|u32
id|common_magic
suffix:semicolon
multiline_comment|/* driver wide common magic */
DECL|member|specific_magic
id|u32
id|specific_magic
suffix:semicolon
multiline_comment|/* structure specific magic */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of remote ports */
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|remove_wq
id|wait_queue_head_t
id|remove_wq
suffix:semicolon
multiline_comment|/* can be used to wait for&n;&t;&t;&t;&t;&t;&t;  refcount drop to zero */
DECL|member|adapter
r_struct
id|zfcp_adapter
op_star
id|adapter
suffix:semicolon
multiline_comment|/* adapter used to access port */
DECL|member|unit_list_head
r_struct
id|list_head
id|unit_list_head
suffix:semicolon
multiline_comment|/* head of logical unit list */
DECL|member|unit_remove_lh
r_struct
id|list_head
id|unit_remove_lh
suffix:semicolon
multiline_comment|/* head of luns to be removed&n;&t;&t;&t;&t;&t;&t;  list */
DECL|member|units
id|u32
id|units
suffix:semicolon
multiline_comment|/* # of logical units in list */
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
multiline_comment|/* status of this remote port */
DECL|member|scsi_id
id|scsi_id_t
id|scsi_id
suffix:semicolon
multiline_comment|/* own SCSI ID */
DECL|member|wwnn
id|wwn_t
id|wwnn
suffix:semicolon
multiline_comment|/* WWNN if known */
DECL|member|wwpn
id|wwn_t
id|wwpn
suffix:semicolon
multiline_comment|/* WWPN */
DECL|member|d_id
id|fc_id_t
id|d_id
suffix:semicolon
multiline_comment|/* D_ID */
DECL|member|max_scsi_lun
id|scsi_lun_t
id|max_scsi_lun
suffix:semicolon
multiline_comment|/* largest SCSI LUN */
DECL|member|handle
id|u32
id|handle
suffix:semicolon
multiline_comment|/* handle assigned by FSF */
DECL|member|erp_action
r_struct
id|zfcp_erp_action
id|erp_action
suffix:semicolon
multiline_comment|/* pending error recovery */
DECL|member|erp_counter
id|atomic_t
id|erp_counter
suffix:semicolon
DECL|member|sysfs_device
r_struct
id|device
id|sysfs_device
suffix:semicolon
multiline_comment|/* sysfs device */
)brace
suffix:semicolon
DECL|struct|zfcp_unit
r_struct
id|zfcp_unit
(brace
DECL|member|common_magic
id|u32
id|common_magic
suffix:semicolon
multiline_comment|/* driver wide common magic */
DECL|member|specific_magic
id|u32
id|specific_magic
suffix:semicolon
multiline_comment|/* structure specific magic */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of logical units */
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
multiline_comment|/* reference count */
DECL|member|remove_wq
id|wait_queue_head_t
id|remove_wq
suffix:semicolon
multiline_comment|/* can be used to wait for&n;&t;&t;&t;&t;&t;&t;  refcount drop to zero */
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
multiline_comment|/* remote port of unit */
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
multiline_comment|/* status of this logical unit */
DECL|member|scsi_lun
id|scsi_lun_t
id|scsi_lun
suffix:semicolon
multiline_comment|/* own SCSI LUN */
DECL|member|fcp_lun
id|fcp_lun_t
id|fcp_lun
suffix:semicolon
multiline_comment|/* own FCP_LUN */
DECL|member|handle
id|u32
id|handle
suffix:semicolon
multiline_comment|/* handle assigned by FSF */
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
multiline_comment|/* scsi device struct pointer */
DECL|member|erp_action
r_struct
id|zfcp_erp_action
id|erp_action
suffix:semicolon
multiline_comment|/* pending error recovery */
DECL|member|erp_counter
id|atomic_t
id|erp_counter
suffix:semicolon
DECL|member|sysfs_device
r_struct
id|device
id|sysfs_device
suffix:semicolon
multiline_comment|/* sysfs device */
DECL|member|scsi_add_work
id|atomic_t
id|scsi_add_work
suffix:semicolon
multiline_comment|/* used to synchronize */
DECL|member|scsi_add_wq
id|wait_queue_head_t
id|scsi_add_wq
suffix:semicolon
multiline_comment|/* wait for scsi_add_device */
)brace
suffix:semicolon
multiline_comment|/* FSF request */
DECL|struct|zfcp_fsf_req
r_struct
id|zfcp_fsf_req
(brace
DECL|member|common_magic
id|u32
id|common_magic
suffix:semicolon
multiline_comment|/* driver wide common magic */
DECL|member|specific_magic
id|u32
id|specific_magic
suffix:semicolon
multiline_comment|/* structure specific magic */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of FSF requests */
DECL|member|adapter
r_struct
id|zfcp_adapter
op_star
id|adapter
suffix:semicolon
multiline_comment|/* adapter request belongs to */
DECL|member|sbal_count
id|u8
id|sbal_count
suffix:semicolon
multiline_comment|/* # of SBALs in FSF request */
DECL|member|sbal_index
id|u8
id|sbal_index
suffix:semicolon
multiline_comment|/* position of 1st SBAL */
DECL|member|completion_wq
id|wait_queue_head_t
id|completion_wq
suffix:semicolon
multiline_comment|/* can be used by a routine&n;&t;&t;&t;&t;&t;&t;  to wait for completion */
DECL|member|status
r_volatile
id|u32
id|status
suffix:semicolon
multiline_comment|/* status of this request */
DECL|member|fsf_command
id|u32
id|fsf_command
suffix:semicolon
multiline_comment|/* FSF Command copy */
DECL|member|qtcb
r_struct
id|fsf_qtcb
op_star
id|qtcb
suffix:semicolon
multiline_comment|/* address of associated QTCB */
DECL|member|seq_no
id|u32
id|seq_no
suffix:semicolon
multiline_comment|/* Sequence number of request */
DECL|member|data
r_union
id|zfcp_req_data
id|data
suffix:semicolon
multiline_comment|/* Info fields of request */
DECL|member|erp_action
r_struct
id|zfcp_erp_action
op_star
id|erp_action
suffix:semicolon
multiline_comment|/* used if this request is&n;&t;&t;&t;&t;&t;&t;  issued on behalf of erp */
)brace
suffix:semicolon
DECL|typedef|zfcp_fsf_req_handler_t
r_typedef
r_void
id|zfcp_fsf_req_handler_t
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
multiline_comment|/* driver data */
DECL|struct|zfcp_data
r_struct
id|zfcp_data
(brace
DECL|member|scsi_host_template
id|Scsi_Host_Template
id|scsi_host_template
suffix:semicolon
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
multiline_comment|/* Module status flags */
DECL|member|adapter_list_head
r_struct
id|list_head
id|adapter_list_head
suffix:semicolon
multiline_comment|/* head of adapter list */
DECL|member|adapter_remove_lh
r_struct
id|list_head
id|adapter_remove_lh
suffix:semicolon
multiline_comment|/* head of adapters to be&n;&t;&t;&t;&t;&t;&t;       removed */
DECL|member|status_read_lock
id|rwlock_t
id|status_read_lock
suffix:semicolon
multiline_comment|/* for status read thread */
DECL|member|status_read_receive_head
r_struct
id|list_head
id|status_read_receive_head
suffix:semicolon
DECL|member|status_read_send_head
r_struct
id|list_head
id|status_read_send_head
suffix:semicolon
DECL|member|status_read_sema
r_struct
id|semaphore
id|status_read_sema
suffix:semicolon
DECL|member|status_read_thread_wqh
id|wait_queue_head_t
id|status_read_thread_wqh
suffix:semicolon
DECL|member|adapters
id|u16
id|adapters
suffix:semicolon
multiline_comment|/* # of adapters in list */
DECL|member|config_lock
id|rwlock_t
id|config_lock
suffix:semicolon
multiline_comment|/* serialises changes&n;&t;&t;&t;&t;&t;&t;       to adapter/port/unit&n;&t;&t;&t;&t;&t;&t;       lists */
DECL|member|config_sema
r_struct
id|semaphore
id|config_sema
suffix:semicolon
multiline_comment|/* serialises configuration&n;&t;&t;&t;&t;&t;&t;       changes */
DECL|member|reboot_notifier
r_struct
id|notifier_block
id|reboot_notifier
suffix:semicolon
multiline_comment|/* used to register cleanup&n;&t;&t;&t;&t;&t;&t;&t;functions */
DECL|member|loglevel
id|atomic_t
id|loglevel
suffix:semicolon
multiline_comment|/* current loglevel */
macro_line|#ifndef MODULE                                       /* initial parameters&n;&t;&t;&t;&t;&t;&t;&t;needed if ipl from a&n;&t;&t;&t;&t;&t;&t;&t;scsi device is wanted */
DECL|member|init_busid
r_char
id|init_busid
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
DECL|member|init_wwpn
id|wwn_t
id|init_wwpn
suffix:semicolon
DECL|member|init_fcp_lun
id|fcp_lun_t
id|init_fcp_lun
suffix:semicolon
DECL|member|init_is_valid
r_int
id|init_is_valid
suffix:semicolon
macro_line|#endif
macro_line|#ifdef ZFCP_STAT_REQSIZES                            /* Statistical accounting&n;&t;&t;&t;&t;&t;&t;&t;of processed data */
DECL|member|read_req_head
r_struct
id|list_head
id|read_req_head
suffix:semicolon
DECL|member|write_req_head
r_struct
id|list_head
id|write_req_head
suffix:semicolon
DECL|member|read_sg_head
r_struct
id|list_head
id|read_sg_head
suffix:semicolon
DECL|member|write_sg_head
r_struct
id|list_head
id|write_sg_head
suffix:semicolon
DECL|member|read_sguse_head
r_struct
id|list_head
id|read_sguse_head
suffix:semicolon
DECL|member|write_sguse_head
r_struct
id|list_head
id|write_sguse_head
suffix:semicolon
DECL|member|stat_errors
r_int
r_int
id|stat_errors
suffix:semicolon
DECL|member|stat_lock
id|rwlock_t
id|stat_lock
suffix:semicolon
macro_line|#endif
macro_line|#ifdef ZFCP_STAT_QUEUES
DECL|member|outbound_queue_full
id|atomic_t
id|outbound_queue_full
suffix:semicolon
DECL|member|outbound_total
id|atomic_t
id|outbound_total
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef ZFCP_STAT_REQSIZES
DECL|struct|zfcp_statistics
r_struct
id|zfcp_statistics
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|num
id|u32
id|num
suffix:semicolon
DECL|member|occurrence
id|u32
id|occurrence
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/********************** ZFCP SPECIFIC DEFINES ********************************/
DECL|macro|ZFCP_FSFREQ_CLEANUP_TIMEOUT
mdefine_line|#define ZFCP_FSFREQ_CLEANUP_TIMEOUT&t;HZ/10
DECL|macro|ZFCP_KNOWN
mdefine_line|#define ZFCP_KNOWN              0x00000001
DECL|macro|ZFCP_REQ_AUTO_CLEANUP
mdefine_line|#define ZFCP_REQ_AUTO_CLEANUP&t;0x00000002
DECL|macro|ZFCP_WAIT_FOR_SBAL
mdefine_line|#define ZFCP_WAIT_FOR_SBAL&t;0x00000004
DECL|macro|ZFCP_SET
mdefine_line|#define ZFCP_SET                0x00000100
DECL|macro|ZFCP_CLEAR
mdefine_line|#define ZFCP_CLEAR              0x00000200
DECL|macro|ZFCP_INTERRUPTIBLE
mdefine_line|#define ZFCP_INTERRUPTIBLE&t;1
DECL|macro|ZFCP_UNINTERRUPTIBLE
mdefine_line|#define ZFCP_UNINTERRUPTIBLE&t;0
multiline_comment|/* some magics which may be used to authenticate data structures */
DECL|macro|ZFCP_MAGIC
mdefine_line|#define ZFCP_MAGIC&t;&t;0xFCFCFCFC
DECL|macro|ZFCP_MAGIC_ADAPTER
mdefine_line|#define ZFCP_MAGIC_ADAPTER&t;0xAAAAAAAA
DECL|macro|ZFCP_MAGIC_PORT
mdefine_line|#define ZFCP_MAGIC_PORT&t;&t;0xBBBBBBBB
DECL|macro|ZFCP_MAGIC_UNIT
mdefine_line|#define ZFCP_MAGIC_UNIT&t;&t;0xCCCCCCCC
DECL|macro|ZFCP_MAGIC_FSFREQ
mdefine_line|#define ZFCP_MAGIC_FSFREQ&t;0xEEEEEEEE
macro_line|#ifndef atomic_test_mask
DECL|macro|atomic_test_mask
mdefine_line|#define atomic_test_mask(mask, target) &bslash;&n;           ((atomic_read(target) &amp; mask) == mask)
macro_line|#endif
r_extern
r_void
id|_zfcp_hex_dump
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|ZFCP_HEX_DUMP
mdefine_line|#define ZFCP_HEX_DUMP(level, addr, count) &bslash;&n;&t;&t;if (ZFCP_LOG_CHECK(level)) { &bslash;&n;&t;&t;&t;_zfcp_hex_dump(addr, count); &bslash;&n;&t;&t;}
multiline_comment|/*&n; * Not yet optimal but useful:&n; * Waits until the condition is met or the timeout occurs.&n; * The condition may be a function call. This allows to&n; * execute some additional instructions in addition&n; * to a simple condition check.&n; * The timeout is modified on exit and holds the remaining time.&n; * Thus it is zero if a timeout ocurred, i.e. the condition was &n; * not met in the specified interval.&n; */
DECL|macro|__ZFCP_WAIT_EVENT_TIMEOUT
mdefine_line|#define __ZFCP_WAIT_EVENT_TIMEOUT(timeout, condition) &bslash;&n;do { &bslash;&n;&t;set_current_state(TASK_UNINTERRUPTIBLE); &bslash;&n;&t;while (!(condition) &amp;&amp; timeout) &bslash;&n;&t;&t;timeout = schedule_timeout(timeout); &bslash;&n;&t;current-&gt;state = TASK_RUNNING; &bslash;&n;} while (0);
DECL|macro|ZFCP_WAIT_EVENT_TIMEOUT
mdefine_line|#define ZFCP_WAIT_EVENT_TIMEOUT(waitqueue, timeout, condition) &bslash;&n;do { &bslash;&n;&t;wait_queue_t entry; &bslash;&n;&t;init_waitqueue_entry(&amp;entry, current); &bslash;&n;&t;add_wait_queue(&amp;waitqueue, &amp;entry); &bslash;&n;&t;__ZFCP_WAIT_EVENT_TIMEOUT(timeout, condition) &bslash;&n;&t;remove_wait_queue(&amp;waitqueue, &amp;entry); &bslash;&n;} while (0);
DECL|macro|zfcp_get_busid_by_adapter
mdefine_line|#define zfcp_get_busid_by_adapter(adapter) (adapter-&gt;ccw_device-&gt;dev.bus_id)
DECL|macro|zfcp_get_busid_by_port
mdefine_line|#define zfcp_get_busid_by_port(port) (zfcp_get_busid_by_adapter(port-&gt;adapter))
DECL|macro|zfcp_get_busid_by_unit
mdefine_line|#define zfcp_get_busid_by_unit(unit) (zfcp_get_busid_by_port(unit-&gt;port))
multiline_comment|/*&n; *  functions needed for reference/usage counting&n; */
r_static
r_inline
r_void
DECL|function|zfcp_unit_get
id|zfcp_unit_get
c_func
(paren
r_struct
id|zfcp_unit
op_star
id|unit
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|unit-&gt;refcount
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_unit_put
id|zfcp_unit_put
c_func
(paren
r_struct
id|zfcp_unit
op_star
id|unit
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|unit-&gt;refcount
)paren
op_eq
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|unit-&gt;remove_wq
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_unit_wait
id|zfcp_unit_wait
c_func
(paren
r_struct
id|zfcp_unit
op_star
id|unit
)paren
(brace
id|wait_event
c_func
(paren
id|unit-&gt;remove_wq
comma
id|atomic_read
c_func
(paren
op_amp
id|unit-&gt;refcount
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_port_get
id|zfcp_port_get
c_func
(paren
r_struct
id|zfcp_port
op_star
id|port
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|port-&gt;refcount
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_port_put
id|zfcp_port_put
c_func
(paren
r_struct
id|zfcp_port
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|port-&gt;refcount
)paren
op_eq
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|port-&gt;remove_wq
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_port_wait
id|zfcp_port_wait
c_func
(paren
r_struct
id|zfcp_port
op_star
id|port
)paren
(brace
id|wait_event
c_func
(paren
id|port-&gt;remove_wq
comma
id|atomic_read
c_func
(paren
op_amp
id|port-&gt;refcount
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_adapter_get
id|zfcp_adapter_get
c_func
(paren
r_struct
id|zfcp_adapter
op_star
id|adapter
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|adapter-&gt;refcount
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_adapter_put
id|zfcp_adapter_put
c_func
(paren
r_struct
id|zfcp_adapter
op_star
id|adapter
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_return
c_func
(paren
op_amp
id|adapter-&gt;refcount
)paren
op_eq
l_int|0
)paren
id|wake_up
c_func
(paren
op_amp
id|adapter-&gt;remove_wq
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|zfcp_adapter_wait
id|zfcp_adapter_wait
c_func
(paren
r_struct
id|zfcp_adapter
op_star
id|adapter
)paren
(brace
id|wait_event
c_func
(paren
id|adapter-&gt;remove_wq
comma
id|atomic_read
c_func
(paren
op_amp
id|adapter-&gt;refcount
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif /* ZFCP_DEF_H */
eof
