multiline_comment|/* &n; * &n; * linux/drivers/s390/scsi/zfcp_def.h&n; * &n; * FCP adapter driver for IBM eServer zSeries &n; * &n; * (C) Copyright IBM Corp. 2002, 2004&n; *&n; * Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt; &n; *            Raimund Schroeder &lt;raimund.schroeder@de.ibm.com&gt; &n; *            Aron Zeh&n; *            Wolfgang Taphorn&n; *            Stefan Bader &lt;stefan.bader@de.ibm.com&gt; &n; *            Heiko Carstens &lt;heiko.carstens@de.ibm.com&gt; &n; *            Andreas Herrmann &lt;aherrman@de.ibm.com&gt;&n; *            Volker Sameske &lt;sameske@de.ibm.com&gt;&n; * &n; * This program is free software; you can redistribute it and/or modify &n; * it under the terms of the GNU General Public License as published by &n; * the Free Software Foundation; either version 2, or (at your option) &n; * any later version. &n; * &n; * This program is distributed in the hope that it will be useful, &n; * but WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; * GNU General Public License for more details. &n; * &n; * You should have received a copy of the GNU General Public License &n; * along with this program; if not, write to the Free Software &n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; */
macro_line|#ifndef ZFCP_DEF_H
DECL|macro|ZFCP_DEF_H
mdefine_line|#define ZFCP_DEF_H
multiline_comment|/* this drivers version (do not edit !!! generated and updated by cvs) */
DECL|macro|ZFCP_DEF_REVISION
mdefine_line|#define ZFCP_DEF_REVISION &quot;$Revision: 1.107 $&quot;
multiline_comment|/*************************** INCLUDES *****************************************/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_tcq.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &lt;scsi/scsi_transport_fc.h&gt;
macro_line|#include &quot;../../fc4/fc.h&quot;
macro_line|#include &quot;zfcp_fsf.h&quot;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/qdio.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
multiline_comment|/************************ DEBUG FLAGS *****************************************/
DECL|macro|ZFCP_PRINT_FLAGS
mdefine_line|#define&t;ZFCP_PRINT_FLAGS
multiline_comment|/********************* GENERAL DEFINES *********************************/
DECL|macro|ZFCP_VERSION
mdefine_line|#define ZFCP_VERSION&t;&t;&quot;4.2.0&quot;
multiline_comment|/**&n; * zfcp_sg_to_address - determine kernel address from struct scatterlist&n; * @list: struct scatterlist&n; * Return: kernel address&n; */
r_static
r_inline
r_void
op_star
DECL|function|zfcp_sg_to_address
id|zfcp_sg_to_address
c_func
(paren
r_struct
id|scatterlist
op_star
id|list
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|page_address
c_func
(paren
id|list-&gt;page
)paren
op_plus
id|list-&gt;offset
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * zfcp_address_to_sg - set up struct scatterlist from kernel address&n; * @address: kernel address&n; * @list: struct scatterlist&n; */
r_static
r_inline
r_void
DECL|function|zfcp_address_to_sg
id|zfcp_address_to_sg
c_func
(paren
r_void
op_star
id|address
comma
r_struct
id|scatterlist
op_star
id|list
)paren
(brace
id|list-&gt;page
op_assign
id|virt_to_page
c_func
(paren
id|address
)paren
suffix:semicolon
id|list-&gt;offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|address
)paren
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
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
DECL|macro|ZFCP_DEVICE_MODEL_PRIV
mdefine_line|#define ZFCP_DEVICE_MODEL_PRIV&t;0x04
multiline_comment|/* allow as many chained SBALs as are supported by hardware */
DECL|macro|ZFCP_MAX_SBALS_PER_REQ
mdefine_line|#define ZFCP_MAX_SBALS_PER_REQ&t;&t;FSF_MAX_SBALS_PER_REQ
DECL|macro|ZFCP_MAX_SBALS_PER_CT_REQ
mdefine_line|#define ZFCP_MAX_SBALS_PER_CT_REQ&t;FSF_MAX_SBALS_PER_REQ
DECL|macro|ZFCP_MAX_SBALS_PER_ELS_REQ
mdefine_line|#define ZFCP_MAX_SBALS_PER_ELS_REQ&t;FSF_MAX_SBALS_PER_ELS_REQ
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
multiline_comment|/* timeout value for &quot;default timer&quot; for fsf requests */
DECL|macro|ZFCP_FSF_REQUEST_TIMEOUT
mdefine_line|#define ZFCP_FSF_REQUEST_TIMEOUT (60*HZ);
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
DECL|macro|ZFCP_NS_GID_PN_TIMEOUT
mdefine_line|#define ZFCP_NS_GID_PN_TIMEOUT&t;&t;10
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
DECL|macro|FCP_CLEAR_ACA
mdefine_line|#define FCP_CLEAR_ACA&t;&t;0x40
DECL|macro|FCP_TARGET_RESET
mdefine_line|#define FCP_TARGET_RESET&t;0x20
DECL|macro|FCP_LOGICAL_UNIT_RESET
mdefine_line|#define FCP_LOGICAL_UNIT_RESET&t;0x10
DECL|macro|FCP_CLEAR_TASK_SET
mdefine_line|#define FCP_CLEAR_TASK_SET&t;0x04
DECL|macro|FCP_ABORT_TASK_SET
mdefine_line|#define FCP_ABORT_TASK_SET&t;0x02
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
multiline_comment|/*&n; * FC-FS stuff&n; */
DECL|macro|R_A_TOV
mdefine_line|#define R_A_TOV&t;&t;&t;&t;10 /* seconds */
DECL|macro|ZFCP_ELS_TIMEOUT
mdefine_line|#define ZFCP_ELS_TIMEOUT&t;&t;(2 * R_A_TOV)
DECL|macro|ZFCP_LS_RLS
mdefine_line|#define ZFCP_LS_RLS&t;&t;&t;0x0f
DECL|macro|ZFCP_LS_ADISC
mdefine_line|#define ZFCP_LS_ADISC&t;&t;&t;0x52
DECL|macro|ZFCP_LS_RPS
mdefine_line|#define ZFCP_LS_RPS&t;&t;&t;0x56
DECL|macro|ZFCP_LS_RSCN
mdefine_line|#define ZFCP_LS_RSCN&t;&t;&t;0x61
DECL|macro|ZFCP_LS_RNID
mdefine_line|#define ZFCP_LS_RNID&t;&t;&t;0x78
DECL|struct|zfcp_ls_rjt_par
r_struct
id|zfcp_ls_rjt_par
(brace
DECL|member|action
id|u8
id|action
suffix:semicolon
DECL|member|reason_code
id|u8
id|reason_code
suffix:semicolon
DECL|member|reason_expl
id|u8
id|reason_expl
suffix:semicolon
DECL|member|vendor_unique
id|u8
id|vendor_unique
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|zfcp_ls_adisc
r_struct
id|zfcp_ls_adisc
(brace
DECL|member|code
id|u8
id|code
suffix:semicolon
DECL|member|field
id|u8
id|field
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|hard_nport_id
id|u32
id|hard_nport_id
suffix:semicolon
DECL|member|wwpn
id|u64
id|wwpn
suffix:semicolon
DECL|member|wwnn
id|u64
id|wwnn
suffix:semicolon
DECL|member|nport_id
id|u32
id|nport_id
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|zfcp_ls_adisc_acc
r_struct
id|zfcp_ls_adisc_acc
(brace
DECL|member|code
id|u8
id|code
suffix:semicolon
DECL|member|field
id|u8
id|field
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|hard_nport_id
id|u32
id|hard_nport_id
suffix:semicolon
DECL|member|wwpn
id|u64
id|wwpn
suffix:semicolon
DECL|member|wwnn
id|u64
id|wwnn
suffix:semicolon
DECL|member|nport_id
id|u32
id|nport_id
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|zfcp_rc_entry
r_struct
id|zfcp_rc_entry
(brace
DECL|member|code
id|u8
id|code
suffix:semicolon
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * FC-GS-2 stuff&n; */
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
DECL|macro|ZFCP_CT_REJECT
mdefine_line|#define ZFCP_CT_REJECT&t;&t;&t;0x8001
multiline_comment|/*&n; * FC-GS-4 stuff&n; */
DECL|macro|ZFCP_CT_TIMEOUT
mdefine_line|#define ZFCP_CT_TIMEOUT&t;&t;&t;(3 * R_A_TOV)
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
multiline_comment|/******************** LOGGING MACROS AND DEFINES *****************************/
multiline_comment|/*&n; * Logging may be applied on certain kinds of driver operations&n; * independently. Additionally, different log-levels are supported for&n; * each of these areas.&n; */
DECL|macro|ZFCP_NAME
mdefine_line|#define ZFCP_NAME               &quot;zfcp&quot;
multiline_comment|/* read-only LUN sharing switch initial value */
DECL|macro|ZFCP_RO_LUN_SHARING_DEFAULTS
mdefine_line|#define ZFCP_RO_LUN_SHARING_DEFAULTS 0
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
multiline_comment|/*&n; * this allows removal of logging code by the preprocessor&n; * (the most detailed log level still to be compiled in is specified, &n; * higher log levels are removed)&n; */
DECL|macro|ZFCP_LOG_LEVEL_LIMIT
mdefine_line|#define ZFCP_LOG_LEVEL_LIMIT&t;ZFCP_LOG_LEVEL_TRACE
multiline_comment|/* get &quot;loglevel&quot; nibble assignment */
DECL|macro|ZFCP_GET_LOG_VALUE
mdefine_line|#define ZFCP_GET_LOG_VALUE(zfcp_lognibble) &bslash;&n;&t;       ((atomic_read(&amp;zfcp_data.loglevel) &gt;&gt; (zfcp_lognibble&lt;&lt;2)) &amp; 0xF)
multiline_comment|/* set &quot;loglevel&quot; nibble */
DECL|macro|ZFCP_SET_LOG_NIBBLE
mdefine_line|#define ZFCP_SET_LOG_NIBBLE(value, zfcp_lognibble) &bslash;&n;&t;       (value &lt;&lt; (zfcp_lognibble &lt;&lt; 2))
multiline_comment|/* all log-level defaults are combined to generate initial log-level */
DECL|macro|ZFCP_LOG_LEVEL_DEFAULTS
mdefine_line|#define ZFCP_LOG_LEVEL_DEFAULTS &bslash;&n;&t;(ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_OTHER) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_SCSI) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_FSF) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_CONFIG) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_CIO) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_QDIO) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_ERP) | &bslash;&n;&t; ZFCP_SET_LOG_NIBBLE(ZFCP_LOG_LEVEL_NORMAL, ZFCP_LOG_AREA_FC))
multiline_comment|/* check whether we have the right level for logging */
DECL|macro|ZFCP_LOG_CHECK
mdefine_line|#define ZFCP_LOG_CHECK(level) &bslash;&n;&t;((ZFCP_GET_LOG_VALUE(ZFCP_LOG_AREA)) &gt;= level)
multiline_comment|/* logging routine for zfcp */
DECL|macro|_ZFCP_LOG
mdefine_line|#define _ZFCP_LOG(fmt, args...) &bslash;&n;&t;printk(KERN_ERR ZFCP_NAME&quot;: %s(%d): &quot; fmt, __FUNCTION__, &bslash;&n;&t;       __LINE__ , ##args)
DECL|macro|ZFCP_LOG
mdefine_line|#define ZFCP_LOG(level, fmt, args...) &bslash;&n;do { &bslash;&n;&t;if (ZFCP_LOG_CHECK(level)) &bslash;&n;&t;&t;_ZFCP_LOG(fmt, ##args); &bslash;&n;} while (0)
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_NORMAL
DECL|macro|ZFCP_LOG_NORMAL
macro_line|# define ZFCP_LOG_NORMAL(fmt, args...)
macro_line|#else
DECL|macro|ZFCP_LOG_NORMAL
macro_line|# define ZFCP_LOG_NORMAL(fmt, args...) &bslash;&n;do { &bslash;&n;&t;if (ZFCP_LOG_CHECK(ZFCP_LOG_LEVEL_NORMAL)) &bslash;&n;&t;&t;printk(KERN_ERR ZFCP_NAME&quot;: &quot; fmt, ##args); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_INFO
DECL|macro|ZFCP_LOG_INFO
macro_line|# define ZFCP_LOG_INFO(fmt, args...)
macro_line|#else
DECL|macro|ZFCP_LOG_INFO
macro_line|# define ZFCP_LOG_INFO(fmt, args...) &bslash;&n;do { &bslash;&n;&t;if (ZFCP_LOG_CHECK(ZFCP_LOG_LEVEL_INFO)) &bslash;&n;&t;&t;printk(KERN_ERR ZFCP_NAME&quot;: &quot; fmt, ##args); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_DEBUG
DECL|macro|ZFCP_LOG_DEBUG
macro_line|# define ZFCP_LOG_DEBUG(fmt, args...)
macro_line|#else
DECL|macro|ZFCP_LOG_DEBUG
macro_line|# define ZFCP_LOG_DEBUG(fmt, args...) &bslash;&n;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_DEBUG, fmt , ##args)
macro_line|#endif
macro_line|#if ZFCP_LOG_LEVEL_LIMIT &lt; ZFCP_LOG_LEVEL_TRACE
DECL|macro|ZFCP_LOG_TRACE
macro_line|# define ZFCP_LOG_TRACE(fmt, args...)
macro_line|#else
DECL|macro|ZFCP_LOG_TRACE
macro_line|# define ZFCP_LOG_TRACE(fmt, args...) &bslash;&n;&t;ZFCP_LOG(ZFCP_LOG_LEVEL_TRACE, fmt , ##args)
macro_line|#endif
macro_line|#ifndef ZFCP_PRINT_FLAGS
DECL|macro|ZFCP_LOG_FLAGS
macro_line|# define ZFCP_LOG_FLAGS(level, fmt, args...)
macro_line|#else
r_extern
id|u32
id|flags_dump
suffix:semicolon
DECL|macro|ZFCP_LOG_FLAGS
macro_line|# define ZFCP_LOG_FLAGS(level, fmt, args...) &bslash;&n;do { &bslash;&n;&t;if (level &lt;= flags_dump) &bslash;&n;&t;&t;_ZFCP_LOG(fmt, ##args); &bslash;&n;} while (0)
macro_line|#endif
multiline_comment|/*************** ADAPTER/PORT/UNIT AND FSF_REQ STATUS FLAGS ******************/
multiline_comment|/* &n; * Note, the leftmost status byte is common among adapter, port &n; * and unit&n; */
DECL|macro|ZFCP_COMMON_FLAGS
mdefine_line|#define ZFCP_COMMON_FLAGS&t;&t;&t;0xfff00000
DECL|macro|ZFCP_SPECIFIC_FLAGS
mdefine_line|#define ZFCP_SPECIFIC_FLAGS&t;&t;&t;0x000fffff
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
DECL|macro|ZFCP_STATUS_COMMON_ACCESS_DENIED
mdefine_line|#define ZFCP_STATUS_COMMON_ACCESS_DENIED&t;0x00800000
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
multiline_comment|/* FC-PH/FC-GS well-known address identifiers for generic services */
DECL|macro|ZFCP_DID_MANAGEMENT_SERVICE
mdefine_line|#define ZFCP_DID_MANAGEMENT_SERVICE&t;&t;0xFFFFFA
DECL|macro|ZFCP_DID_TIME_SERVICE
mdefine_line|#define ZFCP_DID_TIME_SERVICE&t;&t;&t;0xFFFFFB
DECL|macro|ZFCP_DID_DIRECTORY_SERVICE
mdefine_line|#define ZFCP_DID_DIRECTORY_SERVICE&t;&t;0xFFFFFC
DECL|macro|ZFCP_DID_ALIAS_SERVICE
mdefine_line|#define ZFCP_DID_ALIAS_SERVICE&t;&t;&t;0xFFFFF8
DECL|macro|ZFCP_DID_KEY_DISTRIBUTION_SERVICE
mdefine_line|#define ZFCP_DID_KEY_DISTRIBUTION_SERVICE&t;0xFFFFF7
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
DECL|macro|ZFCP_STATUS_PORT_ACCESS_DENIED
mdefine_line|#define ZFCP_STATUS_PORT_ACCESS_DENIED&t;&t;0x00000040
multiline_comment|/* for ports with well known addresses */
DECL|macro|ZFCP_STATUS_PORT_WKA
mdefine_line|#define ZFCP_STATUS_PORT_WKA &bslash;&n;&t;&t;(ZFCP_STATUS_PORT_NO_WWPN | &bslash;&n;&t;&t; ZFCP_STATUS_PORT_NO_SCSI_ID)
multiline_comment|/* logical unit status */
DECL|macro|ZFCP_STATUS_UNIT_NOTSUPPUNITRESET
mdefine_line|#define ZFCP_STATUS_UNIT_NOTSUPPUNITRESET&t;0x00000001
DECL|macro|ZFCP_STATUS_UNIT_TEMPORARY
mdefine_line|#define ZFCP_STATUS_UNIT_TEMPORARY&t;&t;0x00000002
DECL|macro|ZFCP_STATUS_UNIT_SHARED
mdefine_line|#define ZFCP_STATUS_UNIT_SHARED&t;&t;&t;0x00000004
DECL|macro|ZFCP_STATUS_UNIT_READONLY
mdefine_line|#define ZFCP_STATUS_UNIT_READONLY&t;&t;0x00000008
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
multiline_comment|/*********************** ERROR RECOVERY PROCEDURE DEFINES ********************/
DECL|macro|ZFCP_MAX_ERPS
mdefine_line|#define ZFCP_MAX_ERPS                   3
DECL|macro|ZFCP_ERP_FSFREQ_TIMEOUT
mdefine_line|#define ZFCP_ERP_FSFREQ_TIMEOUT&t;&t;(30 * HZ)
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
DECL|macro|ZFCP_STATUS_ERP_LOWMEM
mdefine_line|#define ZFCP_STATUS_ERP_LOWMEM&t;&t;0x00400000
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
multiline_comment|/******************** CFDC SPECIFIC STUFF *****************************/
multiline_comment|/* Firewall data channel sense data record */
DECL|struct|zfcp_cfdc_sense_data
r_struct
id|zfcp_cfdc_sense_data
(brace
DECL|member|signature
id|u32
id|signature
suffix:semicolon
multiline_comment|/* Request signature */
DECL|member|devno
id|u32
id|devno
suffix:semicolon
multiline_comment|/* FCP adapter device number */
DECL|member|command
id|u32
id|command
suffix:semicolon
multiline_comment|/* Command code */
DECL|member|fsf_status
id|u32
id|fsf_status
suffix:semicolon
multiline_comment|/* FSF request status and status qualifier */
DECL|member|fsf_status_qual
id|u8
id|fsf_status_qual
(braket
id|FSF_STATUS_QUALIFIER_SIZE
)braket
suffix:semicolon
DECL|member|payloads
id|u8
id|payloads
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Access conflicts list */
DECL|member|control_file
id|u8
id|control_file
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Access control table */
)brace
suffix:semicolon
DECL|macro|ZFCP_CFDC_SIGNATURE
mdefine_line|#define ZFCP_CFDC_SIGNATURE&t;&t;&t;0xCFDCACDF
DECL|macro|ZFCP_CFDC_CMND_DOWNLOAD_NORMAL
mdefine_line|#define ZFCP_CFDC_CMND_DOWNLOAD_NORMAL&t;&t;0x00010001
DECL|macro|ZFCP_CFDC_CMND_DOWNLOAD_FORCE
mdefine_line|#define ZFCP_CFDC_CMND_DOWNLOAD_FORCE&t;&t;0x00010101
DECL|macro|ZFCP_CFDC_CMND_FULL_ACCESS
mdefine_line|#define ZFCP_CFDC_CMND_FULL_ACCESS&t;&t;0x00000201
DECL|macro|ZFCP_CFDC_CMND_RESTRICTED_ACCESS
mdefine_line|#define ZFCP_CFDC_CMND_RESTRICTED_ACCESS&t;0x00000401
DECL|macro|ZFCP_CFDC_CMND_UPLOAD
mdefine_line|#define ZFCP_CFDC_CMND_UPLOAD&t;&t;&t;0x00010002
DECL|macro|ZFCP_CFDC_DOWNLOAD
mdefine_line|#define ZFCP_CFDC_DOWNLOAD&t;&t;&t;0x00000001
DECL|macro|ZFCP_CFDC_UPLOAD
mdefine_line|#define ZFCP_CFDC_UPLOAD&t;&t;&t;0x00000002
DECL|macro|ZFCP_CFDC_WITH_CONTROL_FILE
mdefine_line|#define ZFCP_CFDC_WITH_CONTROL_FILE&t;&t;0x00010000
DECL|macro|ZFCP_CFDC_DEV_NAME
mdefine_line|#define ZFCP_CFDC_DEV_NAME&t;&t;&t;&quot;zfcp_cfdc&quot;
DECL|macro|ZFCP_CFDC_DEV_MAJOR
mdefine_line|#define ZFCP_CFDC_DEV_MAJOR&t;&t;&t;MISC_MAJOR
DECL|macro|ZFCP_CFDC_DEV_MINOR
mdefine_line|#define ZFCP_CFDC_DEV_MINOR&t;&t;&t;MISC_DYNAMIC_MINOR
DECL|macro|ZFCP_CFDC_MAX_CONTROL_FILE_SIZE
mdefine_line|#define ZFCP_CFDC_MAX_CONTROL_FILE_SIZE&t;&t;127 * 1024
multiline_comment|/************************* STRUCTURE DEFINITIONS *****************************/
r_struct
id|zfcp_fsf_req
suffix:semicolon
multiline_comment|/* holds various memory pools of an adapter */
DECL|struct|zfcp_adapter_mempool
r_struct
id|zfcp_adapter_mempool
(brace
DECL|member|fsf_req_erp
id|mempool_t
op_star
id|fsf_req_erp
suffix:semicolon
DECL|member|fsf_req_scsi
id|mempool_t
op_star
id|fsf_req_scsi
suffix:semicolon
DECL|member|fsf_req_abort
id|mempool_t
op_star
id|fsf_req_abort
suffix:semicolon
DECL|member|fsf_req_status_read
id|mempool_t
op_star
id|fsf_req_status_read
suffix:semicolon
DECL|member|data_status_read
id|mempool_t
op_star
id|data_status_read
suffix:semicolon
DECL|member|data_gid_pn
id|mempool_t
op_star
id|data_gid_pn
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
r_struct
id|scsi_cmnd
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
multiline_comment|/*&n; * header for CT_IU&n; */
DECL|struct|ct_hdr
r_struct
id|ct_hdr
(brace
DECL|member|revision
id|u8
id|revision
suffix:semicolon
singleline_comment|// 0x01
DECL|member|in_id
id|u8
id|in_id
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0x00
DECL|member|gs_type
id|u8
id|gs_type
suffix:semicolon
singleline_comment|// 0xFC&t;Directory Service
DECL|member|gs_subtype
id|u8
id|gs_subtype
suffix:semicolon
singleline_comment|// 0x02&t;Name Server
DECL|member|options
id|u8
id|options
suffix:semicolon
singleline_comment|// 0x00 single bidirectional exchange
DECL|member|reserved0
id|u8
id|reserved0
suffix:semicolon
DECL|member|cmd_rsp_code
id|u16
id|cmd_rsp_code
suffix:semicolon
singleline_comment|// 0x0121 GID_PN, or 0x0100 GA_NXT
DECL|member|max_res_size
id|u16
id|max_res_size
suffix:semicolon
singleline_comment|// &lt;= (4096 - 16) / 4
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
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* nameserver request CT_IU -- for requests where&n; * a port name is required */
DECL|struct|ct_iu_gid_pn_req
r_struct
id|ct_iu_gid_pn_req
(brace
DECL|member|header
r_struct
id|ct_hdr
id|header
suffix:semicolon
DECL|member|wwpn
id|wwn_t
id|wwpn
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* FS_ACC IU and data unit for GID_PN nameserver request */
DECL|struct|ct_iu_gid_pn_resp
r_struct
id|ct_iu_gid_pn_resp
(brace
DECL|member|header
r_struct
id|ct_hdr
id|header
suffix:semicolon
DECL|member|d_id
id|fc_id_t
id|d_id
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|zfcp_send_ct_handler_t
r_typedef
r_void
(paren
op_star
id|zfcp_send_ct_handler_t
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/**&n; * struct zfcp_send_ct - used to pass parameters to function zfcp_fsf_send_ct&n; * @port: port where the request is sent to&n; * @req: scatter-gather list for request&n; * @resp: scatter-gather list for response&n; * @req_count: number of elements in request scatter-gather list&n; * @resp_count: number of elements in response scatter-gather list&n; * @handler: handler function (called for response to the request)&n; * @handler_data: data passed to handler function&n; * @pool: pointer to memory pool for ct request structure&n; * @timeout: FSF timeout for this request&n; * @timer: timer (e.g. for request initiated by erp)&n; * @completion: completion for synchronization purposes&n; * @status: used to pass error status to calling function&n; */
DECL|struct|zfcp_send_ct
r_struct
id|zfcp_send_ct
(brace
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
DECL|member|req
r_struct
id|scatterlist
op_star
id|req
suffix:semicolon
DECL|member|resp
r_struct
id|scatterlist
op_star
id|resp
suffix:semicolon
DECL|member|req_count
r_int
r_int
id|req_count
suffix:semicolon
DECL|member|resp_count
r_int
r_int
id|resp_count
suffix:semicolon
DECL|member|handler
id|zfcp_send_ct_handler_t
id|handler
suffix:semicolon
DECL|member|handler_data
r_int
r_int
id|handler_data
suffix:semicolon
DECL|member|pool
id|mempool_t
op_star
id|pool
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
DECL|member|completion
r_struct
id|completion
op_star
id|completion
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used for name server requests in error recovery */
DECL|struct|zfcp_gid_pn_data
r_struct
id|zfcp_gid_pn_data
(brace
DECL|member|ct
r_struct
id|zfcp_send_ct
id|ct
suffix:semicolon
DECL|member|req
r_struct
id|scatterlist
id|req
suffix:semicolon
DECL|member|resp
r_struct
id|scatterlist
id|resp
suffix:semicolon
DECL|member|ct_iu_req
r_struct
id|ct_iu_gid_pn_req
id|ct_iu_req
suffix:semicolon
DECL|member|ct_iu_resp
r_struct
id|ct_iu_gid_pn_resp
id|ct_iu_resp
suffix:semicolon
DECL|member|port
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|zfcp_send_els_handler_t
r_typedef
r_void
(paren
op_star
id|zfcp_send_els_handler_t
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/**&n; * struct zfcp_send_els - used to pass parameters to function zfcp_fsf_send_els&n; * @adapter: adapter where request is sent from&n; * @d_id: destiniation id of port where request is sent to&n; * @req: scatter-gather list for request&n; * @resp: scatter-gather list for response&n; * @req_count: number of elements in request scatter-gather list&n; * @resp_count: number of elements in response scatter-gather list&n; * @handler: handler function (called for response to the request)&n; * @handler_data: data passed to handler function&n; * @timer: timer (e.g. for request initiated by erp)&n; * @completion: completion for synchronization purposes&n; * @ls_code: hex code of ELS command&n; * @status: used to pass error status to calling function&n; */
DECL|struct|zfcp_send_els
r_struct
id|zfcp_send_els
(brace
DECL|member|adapter
r_struct
id|zfcp_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|d_id
id|fc_id_t
id|d_id
suffix:semicolon
DECL|member|req
r_struct
id|scatterlist
op_star
id|req
suffix:semicolon
DECL|member|resp
r_struct
id|scatterlist
op_star
id|resp
suffix:semicolon
DECL|member|req_count
r_int
r_int
id|req_count
suffix:semicolon
DECL|member|resp_count
r_int
r_int
id|resp_count
suffix:semicolon
DECL|member|handler
id|zfcp_send_els_handler_t
id|handler
suffix:semicolon
DECL|member|handler_data
r_int
r_int
id|handler_data
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
op_star
id|timer
suffix:semicolon
DECL|member|completion
r_struct
id|completion
op_star
id|completion
suffix:semicolon
DECL|member|ls_code
r_int
id|ls_code
suffix:semicolon
DECL|member|status
r_int
id|status
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
DECL|struct|zfcp_fsf_done
r_struct
id|zfcp_fsf_done
(brace
DECL|member|complete
r_struct
id|completion
op_star
id|complete
suffix:semicolon
DECL|member|status
r_int
id|status
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
DECL|member|send_ct
r_struct
id|zfcp_send_ct
op_star
id|send_ct
suffix:semicolon
DECL|member|send_els
r_struct
id|zfcp_send_els
op_star
id|send_els
suffix:semicolon
DECL|member|status_read
r_struct
id|zfcp_status_read
id|status_read
suffix:semicolon
DECL|member|port_data
r_struct
id|fsf_qtcb_bottom_port
op_star
id|port_data
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
DECL|member|supported_features
id|u32
id|supported_features
suffix:semicolon
multiline_comment|/* of FCP channel */
DECL|member|hardware_version
id|u32
id|hardware_version
suffix:semicolon
multiline_comment|/* of FCP channel */
DECL|member|serial_number
id|u8
id|serial_number
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* of hardware */
DECL|member|scsi_host
r_struct
id|Scsi_Host
op_star
id|scsi_host
suffix:semicolon
multiline_comment|/* Pointer to mid-layer */
DECL|member|scsi_host_no
r_int
r_int
id|scsi_host_no
suffix:semicolon
multiline_comment|/* Assigned host number */
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
DECL|member|erp_total_count
id|u32
id|erp_total_count
suffix:semicolon
multiline_comment|/* total nr of enqueued erp&n;&t;&t;&t;&t;&t;&t;      actions */
DECL|member|erp_low_mem_count
id|u32
id|erp_low_mem_count
suffix:semicolon
multiline_comment|/* nr of erp actions waiting&n;&t;&t;&t;&t;&t;&t;      for memory */
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
DECL|member|dbf_lock
id|spinlock_t
id|dbf_lock
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
DECL|member|generic_services
r_struct
id|device
id|generic_services
suffix:semicolon
multiline_comment|/* directory for WKA ports */
)brace
suffix:semicolon
multiline_comment|/*&n; * the struct device sysfs_device must be at the beginning of this structure.&n; * pointer to struct device is used to free port structure in release function&n; * of the device. don&squot;t change!&n; */
DECL|struct|zfcp_port
r_struct
id|zfcp_port
(brace
DECL|member|sysfs_device
r_struct
id|device
id|sysfs_device
suffix:semicolon
multiline_comment|/* sysfs device */
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
)brace
suffix:semicolon
multiline_comment|/* the struct device sysfs_device must be at the beginning of this structure.&n; * pointer to struct device is used to free unit structure in release function&n; * of the device. don&squot;t change!&n; */
DECL|struct|zfcp_unit
r_struct
id|zfcp_unit
(brace
DECL|member|sysfs_device
r_struct
id|device
id|sysfs_device
suffix:semicolon
multiline_comment|/* sysfs device */
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
r_struct
id|scsi_device
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
)brace
suffix:semicolon
multiline_comment|/* FSF request */
DECL|struct|zfcp_fsf_req
r_struct
id|zfcp_fsf_req
(brace
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
DECL|member|sbal_number
id|u8
id|sbal_number
suffix:semicolon
multiline_comment|/* nr of SBALs free for use */
DECL|member|sbal_first
id|u8
id|sbal_first
suffix:semicolon
multiline_comment|/* first SBAL for this request */
DECL|member|sbal_last
id|u8
id|sbal_last
suffix:semicolon
multiline_comment|/* last possible SBAL for&n;&t;&t;&t;&t;&t;&t;  this reuest */
DECL|member|sbal_curr
id|u8
id|sbal_curr
suffix:semicolon
multiline_comment|/* current SBAL during creation&n;&t;&t;&t;&t;&t;&t;  of request */
DECL|member|sbale_curr
id|u8
id|sbale_curr
suffix:semicolon
multiline_comment|/* current SBALE during creation&n;&t;&t;&t;&t;&t;&t;  of request */
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
DECL|member|pool
id|mempool_t
op_star
id|pool
suffix:semicolon
multiline_comment|/* used if request was alloacted&n;&t;&t;&t;&t;&t;&t;  from emergency pool */
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
r_struct
id|scsi_host_template
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
id|u32
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
DECL|member|loglevel
id|atomic_t
id|loglevel
suffix:semicolon
multiline_comment|/* current loglevel */
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
DECL|member|driver_version
r_char
op_star
id|driver_version
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct zfcp_sg_list - struct describing a scatter-gather list&n; * @sg: pointer to array of (struct scatterlist)&n; * @count: number of elements in scatter-gather list&n; */
DECL|struct|zfcp_sg_list
r_struct
id|zfcp_sg_list
(brace
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* number of elements for various memory pools */
DECL|macro|ZFCP_POOL_FSF_REQ_ERP_NR
mdefine_line|#define ZFCP_POOL_FSF_REQ_ERP_NR&t;1
DECL|macro|ZFCP_POOL_FSF_REQ_SCSI_NR
mdefine_line|#define ZFCP_POOL_FSF_REQ_SCSI_NR&t;1
DECL|macro|ZFCP_POOL_FSF_REQ_ABORT_NR
mdefine_line|#define ZFCP_POOL_FSF_REQ_ABORT_NR&t;1
DECL|macro|ZFCP_POOL_STATUS_READ_NR
mdefine_line|#define ZFCP_POOL_STATUS_READ_NR&t;ZFCP_STATUS_READS_RECOM
DECL|macro|ZFCP_POOL_DATA_GID_PN_NR
mdefine_line|#define ZFCP_POOL_DATA_GID_PN_NR&t;1
multiline_comment|/* struct used by memory pools for fsf_requests */
DECL|struct|zfcp_fsf_req_pool_element
r_struct
id|zfcp_fsf_req_pool_element
(brace
DECL|member|fsf_req
r_struct
id|zfcp_fsf_req
id|fsf_req
suffix:semicolon
DECL|member|qtcb
r_struct
id|fsf_qtcb
id|qtcb
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/********************** ZFCP SPECIFIC DEFINES ********************************/
DECL|macro|ZFCP_FSFREQ_CLEANUP_TIMEOUT
mdefine_line|#define ZFCP_FSFREQ_CLEANUP_TIMEOUT&t;HZ/10
DECL|macro|ZFCP_KNOWN
mdefine_line|#define ZFCP_KNOWN              0x00000001
DECL|macro|ZFCP_REQ_AUTO_CLEANUP
mdefine_line|#define ZFCP_REQ_AUTO_CLEANUP&t;0x00000002
DECL|macro|ZFCP_WAIT_FOR_SBAL
mdefine_line|#define ZFCP_WAIT_FOR_SBAL&t;0x00000004
DECL|macro|ZFCP_REQ_NO_QTCB
mdefine_line|#define ZFCP_REQ_NO_QTCB&t;0x00000008
DECL|macro|ZFCP_SET
mdefine_line|#define ZFCP_SET                0x00000100
DECL|macro|ZFCP_CLEAR
mdefine_line|#define ZFCP_CLEAR              0x00000200
DECL|macro|ZFCP_INTERRUPTIBLE
mdefine_line|#define ZFCP_INTERRUPTIBLE&t;1
DECL|macro|ZFCP_UNINTERRUPTIBLE
mdefine_line|#define ZFCP_UNINTERRUPTIBLE&t;0
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
multiline_comment|/*&n; *  stuff needed for callback handling&n; */
DECL|typedef|zfcp_cb_incoming_els_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_incoming_els_t
)paren
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|typedef|zfcp_cb_link_down_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_link_down_t
)paren
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
DECL|typedef|zfcp_cb_link_up_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_link_up_t
)paren
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
DECL|typedef|zfcp_cb_adapter_add_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_adapter_add_t
)paren
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
DECL|typedef|zfcp_cb_port_add_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_port_add_t
)paren
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
DECL|typedef|zfcp_cb_unit_add_t
r_typedef
r_void
(paren
op_star
id|zfcp_cb_unit_add_t
)paren
(paren
r_struct
id|zfcp_unit
op_star
)paren
suffix:semicolon
DECL|struct|zfcp_callbacks
r_struct
id|zfcp_callbacks
(brace
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|incoming_els
id|zfcp_cb_incoming_els_t
id|incoming_els
suffix:semicolon
DECL|member|link_down
id|zfcp_cb_link_down_t
id|link_down
suffix:semicolon
DECL|member|link_up
id|zfcp_cb_link_up_t
id|link_up
suffix:semicolon
DECL|member|adapter_add
id|zfcp_cb_adapter_add_t
id|adapter_add
suffix:semicolon
DECL|member|port_add
id|zfcp_cb_port_add_t
id|port_add
suffix:semicolon
DECL|member|unit_add
id|zfcp_cb_unit_add_t
id|unit_add
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|zfcp_callbacks
id|zfcp_callbacks
suffix:semicolon
macro_line|#endif /* ZFCP_DEF_H */
eof
