multiline_comment|/* &n; * &n; * linux/drivers/s390/scsi/zfcp_fsf.h&n; * &n; * FCP adapter driver for IBM eServer zSeries &n; * &n; * (C) Copyright IBM Corp. 2002, 2004&n; *&n; * Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt; &n; *            Raimund Schroeder &lt;raimund.schroeder@de.ibm.com&gt; &n; *            Aron Zeh&n; *            Wolfgang Taphorn&n; *            Stefan Bader &lt;stefan.bader@de.ibm.com&gt; &n; *            Heiko Carstens &lt;heiko.carstens@de.ibm.com&gt;&n; *            Andreas Herrmann &lt;aherrman@de.ibm.com&gt;&n; *            Volker Sameske &lt;sameske@de.ibm.com&gt;&n; * &n; * This program is free software; you can redistribute it and/or modify &n; * it under the terms of the GNU General Public License as published by &n; * the Free Software Foundation; either version 2, or (at your option) &n; * any later version. &n; * &n; * This program is distributed in the hope that it will be useful, &n; * but WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; * GNU General Public License for more details. &n; * &n; * You should have received a copy of the GNU General Public License &n; * along with this program; if not, write to the Free Software &n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; */
macro_line|#ifndef FSF_H
DECL|macro|FSF_H
mdefine_line|#define FSF_H
DECL|macro|FSF_QTCB_VERSION1
mdefine_line|#define FSF_QTCB_VERSION1&t;&t;&t;0x00000001
DECL|macro|FSF_QTCB_CURRENT_VERSION
mdefine_line|#define FSF_QTCB_CURRENT_VERSION&t;&t;FSF_QTCB_VERSION1
multiline_comment|/* FSF commands */
DECL|macro|FSF_QTCB_FCP_CMND
mdefine_line|#define&t;FSF_QTCB_FCP_CMND&t;&t;&t;0x00000001
DECL|macro|FSF_QTCB_ABORT_FCP_CMND
mdefine_line|#define&t;FSF_QTCB_ABORT_FCP_CMND&t;&t;&t;0x00000002
DECL|macro|FSF_QTCB_OPEN_PORT_WITH_DID
mdefine_line|#define&t;FSF_QTCB_OPEN_PORT_WITH_DID&t;&t;0x00000005
DECL|macro|FSF_QTCB_OPEN_LUN
mdefine_line|#define&t;FSF_QTCB_OPEN_LUN&t;&t;&t;0x00000006
DECL|macro|FSF_QTCB_CLOSE_LUN
mdefine_line|#define&t;FSF_QTCB_CLOSE_LUN&t;&t;&t;0x00000007
DECL|macro|FSF_QTCB_CLOSE_PORT
mdefine_line|#define&t;FSF_QTCB_CLOSE_PORT&t;&t;&t;0x00000008
DECL|macro|FSF_QTCB_CLOSE_PHYSICAL_PORT
mdefine_line|#define&t;FSF_QTCB_CLOSE_PHYSICAL_PORT&t;&t;0x00000009
DECL|macro|FSF_QTCB_SEND_ELS
mdefine_line|#define&t;FSF_QTCB_SEND_ELS&t;&t;&t;0x0000000B
DECL|macro|FSF_QTCB_SEND_GENERIC
mdefine_line|#define&t;FSF_QTCB_SEND_GENERIC&t;&t;&t;0x0000000C
DECL|macro|FSF_QTCB_EXCHANGE_CONFIG_DATA
mdefine_line|#define&t;FSF_QTCB_EXCHANGE_CONFIG_DATA&t;&t;0x0000000D
DECL|macro|FSF_QTCB_EXCHANGE_PORT_DATA
mdefine_line|#define&t;FSF_QTCB_EXCHANGE_PORT_DATA&t;&t;0x0000000E
DECL|macro|FSF_QTCB_DOWNLOAD_CONTROL_FILE
mdefine_line|#define FSF_QTCB_DOWNLOAD_CONTROL_FILE&t;&t;0x00000012
DECL|macro|FSF_QTCB_UPLOAD_CONTROL_FILE
mdefine_line|#define FSF_QTCB_UPLOAD_CONTROL_FILE&t;&t;0x00000013
multiline_comment|/* FSF QTCB types */
DECL|macro|FSF_IO_COMMAND
mdefine_line|#define FSF_IO_COMMAND&t;&t;&t;&t;0x00000001
DECL|macro|FSF_SUPPORT_COMMAND
mdefine_line|#define FSF_SUPPORT_COMMAND&t;&t;&t;0x00000002
DECL|macro|FSF_CONFIG_COMMAND
mdefine_line|#define FSF_CONFIG_COMMAND&t;&t;&t;0x00000003
DECL|macro|FSF_PORT_COMMAND
mdefine_line|#define FSF_PORT_COMMAND&t;&t;&t;0x00000004
multiline_comment|/* FSF control file upload/download operations&squot; subtype and options */
DECL|macro|FSF_CFDC_OPERATION_SUBTYPE
mdefine_line|#define FSF_CFDC_OPERATION_SUBTYPE&t;&t;0x00020001
DECL|macro|FSF_CFDC_OPTION_NORMAL_MODE
mdefine_line|#define FSF_CFDC_OPTION_NORMAL_MODE&t;&t;0x00000000
DECL|macro|FSF_CFDC_OPTION_FORCE
mdefine_line|#define FSF_CFDC_OPTION_FORCE&t;&t;&t;0x00000001
DECL|macro|FSF_CFDC_OPTION_FULL_ACCESS
mdefine_line|#define FSF_CFDC_OPTION_FULL_ACCESS&t;&t;0x00000002
DECL|macro|FSF_CFDC_OPTION_RESTRICTED_ACCESS
mdefine_line|#define FSF_CFDC_OPTION_RESTRICTED_ACCESS&t;0x00000004
multiline_comment|/* FSF protocol stati */
DECL|macro|FSF_PROT_GOOD
mdefine_line|#define FSF_PROT_GOOD&t;&t;&t;&t;0x00000001
DECL|macro|FSF_PROT_QTCB_VERSION_ERROR
mdefine_line|#define FSF_PROT_QTCB_VERSION_ERROR&t;&t;0x00000010
DECL|macro|FSF_PROT_SEQ_NUMB_ERROR
mdefine_line|#define FSF_PROT_SEQ_NUMB_ERROR&t;&t;&t;0x00000020
DECL|macro|FSF_PROT_UNSUPP_QTCB_TYPE
mdefine_line|#define FSF_PROT_UNSUPP_QTCB_TYPE&t;&t;0x00000040
DECL|macro|FSF_PROT_HOST_CONNECTION_INITIALIZING
mdefine_line|#define FSF_PROT_HOST_CONNECTION_INITIALIZING&t;0x00000080
DECL|macro|FSF_PROT_FSF_STATUS_PRESENTED
mdefine_line|#define FSF_PROT_FSF_STATUS_PRESENTED&t;&t;0x00000100
DECL|macro|FSF_PROT_DUPLICATE_REQUEST_ID
mdefine_line|#define FSF_PROT_DUPLICATE_REQUEST_ID&t;&t;0x00000200
DECL|macro|FSF_PROT_LINK_DOWN
mdefine_line|#define FSF_PROT_LINK_DOWN                      0x00000400
DECL|macro|FSF_PROT_REEST_QUEUE
mdefine_line|#define FSF_PROT_REEST_QUEUE                    0x00000800
DECL|macro|FSF_PROT_ERROR_STATE
mdefine_line|#define FSF_PROT_ERROR_STATE&t;&t;&t;0x01000000
multiline_comment|/* FSF stati */
DECL|macro|FSF_GOOD
mdefine_line|#define FSF_GOOD&t;&t;&t;&t;0x00000000
DECL|macro|FSF_PORT_ALREADY_OPEN
mdefine_line|#define FSF_PORT_ALREADY_OPEN&t;&t;&t;0x00000001
DECL|macro|FSF_LUN_ALREADY_OPEN
mdefine_line|#define FSF_LUN_ALREADY_OPEN&t;&t;&t;0x00000002
DECL|macro|FSF_PORT_HANDLE_NOT_VALID
mdefine_line|#define FSF_PORT_HANDLE_NOT_VALID&t;&t;0x00000003
DECL|macro|FSF_LUN_HANDLE_NOT_VALID
mdefine_line|#define FSF_LUN_HANDLE_NOT_VALID&t;&t;0x00000004
DECL|macro|FSF_HANDLE_MISMATCH
mdefine_line|#define FSF_HANDLE_MISMATCH&t;&t;&t;0x00000005
DECL|macro|FSF_SERVICE_CLASS_NOT_SUPPORTED
mdefine_line|#define FSF_SERVICE_CLASS_NOT_SUPPORTED&t;&t;0x00000006
DECL|macro|FSF_FCPLUN_NOT_VALID
mdefine_line|#define FSF_FCPLUN_NOT_VALID&t;&t;&t;0x00000009
DECL|macro|FSF_ACCESS_DENIED
mdefine_line|#define FSF_ACCESS_DENIED&t;&t;&t;0x00000010
DECL|macro|FSF_LUN_SHARING_VIOLATION
mdefine_line|#define FSF_LUN_SHARING_VIOLATION               0x00000012
DECL|macro|FSF_FCP_COMMAND_DOES_NOT_EXIST
mdefine_line|#define FSF_FCP_COMMAND_DOES_NOT_EXIST&t;&t;0x00000022
DECL|macro|FSF_DIRECTION_INDICATOR_NOT_VALID
mdefine_line|#define FSF_DIRECTION_INDICATOR_NOT_VALID&t;0x00000030
DECL|macro|FSF_CMND_LENGTH_NOT_VALID
mdefine_line|#define FSF_CMND_LENGTH_NOT_VALID&t;&t;0x00000033
DECL|macro|FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED
mdefine_line|#define FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED&t;0x00000040
DECL|macro|FSF_MAXIMUM_NUMBER_OF_LUNS_EXCEEDED
mdefine_line|#define FSF_MAXIMUM_NUMBER_OF_LUNS_EXCEEDED&t;0x00000041
DECL|macro|FSF_ELS_COMMAND_REJECTED
mdefine_line|#define FSF_ELS_COMMAND_REJECTED&t;&t;0x00000050
DECL|macro|FSF_GENERIC_COMMAND_REJECTED
mdefine_line|#define FSF_GENERIC_COMMAND_REJECTED&t;&t;0x00000051
DECL|macro|FSF_OPERATION_PARTIALLY_SUCCESSFUL
mdefine_line|#define FSF_OPERATION_PARTIALLY_SUCCESSFUL&t;0x00000052
DECL|macro|FSF_AUTHORIZATION_FAILURE
mdefine_line|#define FSF_AUTHORIZATION_FAILURE&t;&t;0x00000053
DECL|macro|FSF_CFDC_ERROR_DETECTED
mdefine_line|#define FSF_CFDC_ERROR_DETECTED&t;&t;&t;0x00000054
DECL|macro|FSF_CONTROL_FILE_UPDATE_ERROR
mdefine_line|#define FSF_CONTROL_FILE_UPDATE_ERROR&t;&t;0x00000055
DECL|macro|FSF_CONTROL_FILE_TOO_LARGE
mdefine_line|#define FSF_CONTROL_FILE_TOO_LARGE&t;&t;0x00000056
DECL|macro|FSF_ACCESS_CONFLICT_DETECTED
mdefine_line|#define FSF_ACCESS_CONFLICT_DETECTED&t;&t;0x00000057
DECL|macro|FSF_CONFLICTS_OVERRULED
mdefine_line|#define FSF_CONFLICTS_OVERRULED&t;&t;&t;0x00000058
DECL|macro|FSF_PORT_BOXED
mdefine_line|#define FSF_PORT_BOXED&t;&t;&t;&t;0x00000059
DECL|macro|FSF_LUN_BOXED
mdefine_line|#define FSF_LUN_BOXED&t;&t;&t;&t;0x0000005A
DECL|macro|FSF_EXCHANGE_CONFIG_DATA_INCOMPLETE
mdefine_line|#define FSF_EXCHANGE_CONFIG_DATA_INCOMPLETE&t;0x0000005B
DECL|macro|FSF_PAYLOAD_SIZE_MISMATCH
mdefine_line|#define FSF_PAYLOAD_SIZE_MISMATCH&t;&t;0x00000060
DECL|macro|FSF_REQUEST_SIZE_TOO_LARGE
mdefine_line|#define FSF_REQUEST_SIZE_TOO_LARGE&t;&t;0x00000061
DECL|macro|FSF_RESPONSE_SIZE_TOO_LARGE
mdefine_line|#define FSF_RESPONSE_SIZE_TOO_LARGE&t;&t;0x00000062
DECL|macro|FSF_SBAL_MISMATCH
mdefine_line|#define FSF_SBAL_MISMATCH&t;&t;&t;0x00000063
DECL|macro|FSF_OPEN_PORT_WITHOUT_PRLI
mdefine_line|#define FSF_OPEN_PORT_WITHOUT_PRLI&t;&t;0x00000064
DECL|macro|FSF_ADAPTER_STATUS_AVAILABLE
mdefine_line|#define FSF_ADAPTER_STATUS_AVAILABLE&t;&t;0x000000AD
DECL|macro|FSF_FCP_RSP_AVAILABLE
mdefine_line|#define FSF_FCP_RSP_AVAILABLE&t;&t;&t;0x000000AF
DECL|macro|FSF_UNKNOWN_COMMAND
mdefine_line|#define FSF_UNKNOWN_COMMAND&t;&t;&t;0x000000E2
DECL|macro|FSF_UNKNOWN_OP_SUBTYPE
mdefine_line|#define FSF_UNKNOWN_OP_SUBTYPE                  0x000000E3
DECL|macro|FSF_INVALID_COMMAND_OPTION
mdefine_line|#define FSF_INVALID_COMMAND_OPTION              0x000000E5
multiline_comment|/* #define FSF_ERROR                             0x000000FF  */
DECL|macro|FSF_STATUS_QUALIFIER_SIZE
mdefine_line|#define FSF_STATUS_QUALIFIER_SIZE&t;&t;16
multiline_comment|/* FSF status qualifier, recommendations */
DECL|macro|FSF_SQ_NO_RECOM
mdefine_line|#define FSF_SQ_NO_RECOM&t;&t;&t;&t;0x00
DECL|macro|FSF_SQ_FCP_RSP_AVAILABLE
mdefine_line|#define FSF_SQ_FCP_RSP_AVAILABLE&t;&t;0x01
DECL|macro|FSF_SQ_RETRY_IF_POSSIBLE
mdefine_line|#define FSF_SQ_RETRY_IF_POSSIBLE&t;&t;0x02
DECL|macro|FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED
mdefine_line|#define FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED&t;0x03
DECL|macro|FSF_SQ_INVOKE_LINK_TEST_PROCEDURE
mdefine_line|#define FSF_SQ_INVOKE_LINK_TEST_PROCEDURE&t;0x04
DECL|macro|FSF_SQ_ULP_PROGRAMMING_ERROR
mdefine_line|#define FSF_SQ_ULP_PROGRAMMING_ERROR&t;&t;0x05
DECL|macro|FSF_SQ_COMMAND_ABORTED
mdefine_line|#define FSF_SQ_COMMAND_ABORTED&t;&t;&t;0x06
DECL|macro|FSF_SQ_NO_RETRY_POSSIBLE
mdefine_line|#define FSF_SQ_NO_RETRY_POSSIBLE&t;&t;0x07
multiline_comment|/* FSF status qualifier for CFDC commands */
DECL|macro|FSF_SQ_CFDC_COULD_NOT_HARDEN_ON_SE
mdefine_line|#define FSF_SQ_CFDC_COULD_NOT_HARDEN_ON_SE&t;0x00000001
DECL|macro|FSF_SQ_CFDC_COULD_NOT_HARDEN_ON_SE2
mdefine_line|#define FSF_SQ_CFDC_COULD_NOT_HARDEN_ON_SE2&t;0x00000002
multiline_comment|/* CFDC subtable codes */
DECL|macro|FSF_SQ_CFDC_SUBTABLE_OS
mdefine_line|#define FSF_SQ_CFDC_SUBTABLE_OS&t;&t;&t;0x0001
DECL|macro|FSF_SQ_CFDC_SUBTABLE_PORT_WWPN
mdefine_line|#define FSF_SQ_CFDC_SUBTABLE_PORT_WWPN&t;&t;0x0002
DECL|macro|FSF_SQ_CFDC_SUBTABLE_PORT_DID
mdefine_line|#define FSF_SQ_CFDC_SUBTABLE_PORT_DID&t;&t;0x0003
DECL|macro|FSF_SQ_CFDC_SUBTABLE_LUN
mdefine_line|#define FSF_SQ_CFDC_SUBTABLE_LUN&t;&t;0x0004
multiline_comment|/* FSF status qualifier (most significant 4 bytes), local link down */
DECL|macro|FSF_PSQ_LINK_NOLIGHT
mdefine_line|#define FSF_PSQ_LINK_NOLIGHT&t;&t;&t;0x00000004
DECL|macro|FSF_PSQ_LINK_WRAPPLUG
mdefine_line|#define FSF_PSQ_LINK_WRAPPLUG&t;&t;&t;0x00000008
DECL|macro|FSF_PSQ_LINK_NOFCP
mdefine_line|#define FSF_PSQ_LINK_NOFCP&t;&t;&t;0x00000010
multiline_comment|/* payload size in status read buffer */
DECL|macro|FSF_STATUS_READ_PAYLOAD_SIZE
mdefine_line|#define FSF_STATUS_READ_PAYLOAD_SIZE&t;&t;4032
multiline_comment|/* number of status read buffers that should be sent by ULP */
DECL|macro|FSF_STATUS_READS_RECOM
mdefine_line|#define FSF_STATUS_READS_RECOM&t;&t;&t;16
multiline_comment|/* status types in status read buffer */
DECL|macro|FSF_STATUS_READ_PORT_CLOSED
mdefine_line|#define FSF_STATUS_READ_PORT_CLOSED&t;&t;0x00000001
DECL|macro|FSF_STATUS_READ_INCOMING_ELS
mdefine_line|#define FSF_STATUS_READ_INCOMING_ELS&t;&t;0x00000002
DECL|macro|FSF_STATUS_READ_SENSE_DATA_AVAIL
mdefine_line|#define FSF_STATUS_READ_SENSE_DATA_AVAIL        0x00000003
DECL|macro|FSF_STATUS_READ_BIT_ERROR_THRESHOLD
mdefine_line|#define FSF_STATUS_READ_BIT_ERROR_THRESHOLD&t;0x00000004
DECL|macro|FSF_STATUS_READ_LINK_DOWN
mdefine_line|#define FSF_STATUS_READ_LINK_DOWN&t;&t;0x00000005 /* FIXME: really? */
DECL|macro|FSF_STATUS_READ_LINK_UP
mdefine_line|#define FSF_STATUS_READ_LINK_UP          &t;0x00000006
DECL|macro|FSF_STATUS_READ_CFDC_UPDATED
mdefine_line|#define FSF_STATUS_READ_CFDC_UPDATED&t;&t;0x0000000A
DECL|macro|FSF_STATUS_READ_CFDC_HARDENED
mdefine_line|#define FSF_STATUS_READ_CFDC_HARDENED&t;&t;0x0000000B
multiline_comment|/* status subtypes in status read buffer */
DECL|macro|FSF_STATUS_READ_SUB_CLOSE_PHYS_PORT
mdefine_line|#define FSF_STATUS_READ_SUB_CLOSE_PHYS_PORT&t;0x00000001
DECL|macro|FSF_STATUS_READ_SUB_ERROR_PORT
mdefine_line|#define FSF_STATUS_READ_SUB_ERROR_PORT&t;&t;0x00000002
multiline_comment|/* status subtypes for CFDC */
DECL|macro|FSF_STATUS_READ_SUB_CFDC_HARDENED_ON_SE
mdefine_line|#define FSF_STATUS_READ_SUB_CFDC_HARDENED_ON_SE&t;0x00000002
DECL|macro|FSF_STATUS_READ_SUB_CFDC_HARDENED_ON_SE2
mdefine_line|#define FSF_STATUS_READ_SUB_CFDC_HARDENED_ON_SE2 0x0000000F
multiline_comment|/* topologie that is detected by the adapter */
DECL|macro|FSF_TOPO_ERROR
mdefine_line|#define FSF_TOPO_ERROR&t;&t;&t;&t;0x00000000
DECL|macro|FSF_TOPO_P2P
mdefine_line|#define FSF_TOPO_P2P&t;&t;&t;&t;0x00000001
DECL|macro|FSF_TOPO_FABRIC
mdefine_line|#define FSF_TOPO_FABRIC&t;&t;&t;&t;0x00000002
DECL|macro|FSF_TOPO_AL
mdefine_line|#define FSF_TOPO_AL&t;&t;&t;&t;0x00000003
DECL|macro|FSF_TOPO_FABRIC_VIRT
mdefine_line|#define FSF_TOPO_FABRIC_VIRT&t;&t;&t;0x00000004
multiline_comment|/* data direction for FCP commands */
DECL|macro|FSF_DATADIR_WRITE
mdefine_line|#define FSF_DATADIR_WRITE&t;&t;&t;0x00000001
DECL|macro|FSF_DATADIR_READ
mdefine_line|#define FSF_DATADIR_READ&t;&t;&t;0x00000002
DECL|macro|FSF_DATADIR_READ_WRITE
mdefine_line|#define FSF_DATADIR_READ_WRITE&t;&t;&t;0x00000003
DECL|macro|FSF_DATADIR_CMND
mdefine_line|#define FSF_DATADIR_CMND&t;&t;&t;0x00000004
multiline_comment|/* fc service class */
DECL|macro|FSF_CLASS_1
mdefine_line|#define FSF_CLASS_1&t;&t;&t;&t;0x00000001
DECL|macro|FSF_CLASS_2
mdefine_line|#define FSF_CLASS_2&t;&t;&t;&t;0x00000002
DECL|macro|FSF_CLASS_3
mdefine_line|#define FSF_CLASS_3&t;&t;&t;&t;0x00000003
multiline_comment|/* SBAL chaining */
DECL|macro|FSF_MAX_SBALS_PER_REQ
mdefine_line|#define FSF_MAX_SBALS_PER_REQ&t;&t;&t;36
DECL|macro|FSF_MAX_SBALS_PER_ELS_REQ
mdefine_line|#define FSF_MAX_SBALS_PER_ELS_REQ&t;&t;2
multiline_comment|/* logging space behind QTCB */
DECL|macro|FSF_QTCB_LOG_SIZE
mdefine_line|#define FSF_QTCB_LOG_SIZE&t;&t;&t;1024
multiline_comment|/* channel features */
DECL|macro|FSF_FEATURE_QTCB_SUPPRESSION
mdefine_line|#define FSF_FEATURE_QTCB_SUPPRESSION            0x00000001
DECL|macro|FSF_FEATURE_CFDC
mdefine_line|#define FSF_FEATURE_CFDC&t;&t;&t;0x00000002
DECL|macro|FSF_FEATURE_LUN_SHARING
mdefine_line|#define FSF_FEATURE_LUN_SHARING&t;&t;&t;0x00000004
DECL|macro|FSF_FEATURE_HBAAPI_MANAGEMENT
mdefine_line|#define FSF_FEATURE_HBAAPI_MANAGEMENT           0x00000010
DECL|macro|FSF_FEATURE_ELS_CT_CHAINED_SBALS
mdefine_line|#define FSF_FEATURE_ELS_CT_CHAINED_SBALS        0x00000020
multiline_comment|/* option */
DECL|macro|FSF_OPEN_LUN_SUPPRESS_BOXING
mdefine_line|#define FSF_OPEN_LUN_SUPPRESS_BOXING&t;&t;0x00000001
DECL|macro|FSF_OPEN_LUN_REPLICATE_SENSE
mdefine_line|#define FSF_OPEN_LUN_REPLICATE_SENSE&t;&t;0x00000002
multiline_comment|/* adapter types */
DECL|macro|FSF_ADAPTER_TYPE_FICON
mdefine_line|#define FSF_ADAPTER_TYPE_FICON                  0x00000001
DECL|macro|FSF_ADAPTER_TYPE_FICON_EXPRESS
mdefine_line|#define FSF_ADAPTER_TYPE_FICON_EXPRESS          0x00000002
multiline_comment|/* port types */
DECL|macro|FSF_HBA_PORTTYPE_UNKNOWN
mdefine_line|#define FSF_HBA_PORTTYPE_UNKNOWN&t;&t;0x00000001
DECL|macro|FSF_HBA_PORTTYPE_NOTPRESENT
mdefine_line|#define FSF_HBA_PORTTYPE_NOTPRESENT&t;&t;0x00000003
DECL|macro|FSF_HBA_PORTTYPE_NPORT
mdefine_line|#define FSF_HBA_PORTTYPE_NPORT&t;&t;&t;0x00000005
DECL|macro|FSF_HBA_PORTTYPE_PTP
mdefine_line|#define FSF_HBA_PORTTYPE_PTP&t;&t;&t;0x00000021
multiline_comment|/* following are not defined and used by FSF Spec&n;   but are additionally defined by FC-HBA */
DECL|macro|FSF_HBA_PORTTYPE_OTHER
mdefine_line|#define FSF_HBA_PORTTYPE_OTHER&t;&t;&t;0x00000002
DECL|macro|FSF_HBA_PORTTYPE_NOTPRESENT
mdefine_line|#define FSF_HBA_PORTTYPE_NOTPRESENT&t;&t;0x00000003
DECL|macro|FSF_HBA_PORTTYPE_NLPORT
mdefine_line|#define FSF_HBA_PORTTYPE_NLPORT&t;&t;&t;0x00000006
DECL|macro|FSF_HBA_PORTTYPE_FLPORT
mdefine_line|#define FSF_HBA_PORTTYPE_FLPORT&t;&t;&t;0x00000007
DECL|macro|FSF_HBA_PORTTYPE_FPORT
mdefine_line|#define FSF_HBA_PORTTYPE_FPORT&t;&t;&t;0x00000008
DECL|macro|FSF_HBA_PORTTYPE_LPORT
mdefine_line|#define FSF_HBA_PORTTYPE_LPORT&t;&t;&t;0x00000020
multiline_comment|/* port states */
DECL|macro|FSF_HBA_PORTSTATE_UNKNOWN
mdefine_line|#define FSF_HBA_PORTSTATE_UNKNOWN&t;&t;0x00000001
DECL|macro|FSF_HBA_PORTSTATE_ONLINE
mdefine_line|#define FSF_HBA_PORTSTATE_ONLINE&t;&t;0x00000002
DECL|macro|FSF_HBA_PORTSTATE_OFFLINE
mdefine_line|#define FSF_HBA_PORTSTATE_OFFLINE&t;&t;0x00000003
DECL|macro|FSF_HBA_PORTSTATE_LINKDOWN
mdefine_line|#define FSF_HBA_PORTSTATE_LINKDOWN&t;&t;0x00000006
DECL|macro|FSF_HBA_PORTSTATE_ERROR
mdefine_line|#define FSF_HBA_PORTSTATE_ERROR&t;&t;&t;0x00000007
multiline_comment|/* IO states of adapter */
DECL|macro|FSF_IOSTAT_NPORT_RJT
mdefine_line|#define FSF_IOSTAT_NPORT_RJT&t;&t;&t;0x00000004
DECL|macro|FSF_IOSTAT_FABRIC_RJT
mdefine_line|#define FSF_IOSTAT_FABRIC_RJT&t;&t;&t;0x00000005
DECL|macro|FSF_IOSTAT_LS_RJT
mdefine_line|#define FSF_IOSTAT_LS_RJT&t;&t;&t;0x00000009
multiline_comment|/* open LUN access flags*/
DECL|macro|FSF_UNIT_ACCESS_OPEN_LUN_ALLOWED
mdefine_line|#define FSF_UNIT_ACCESS_OPEN_LUN_ALLOWED&t;0x01000000
DECL|macro|FSF_UNIT_ACCESS_EXCLUSIVE
mdefine_line|#define FSF_UNIT_ACCESS_EXCLUSIVE&t;&t;0x02000000
DECL|macro|FSF_UNIT_ACCESS_OUTBOUND_TRANSFER
mdefine_line|#define FSF_UNIT_ACCESS_OUTBOUND_TRANSFER&t;0x10000000
r_struct
id|fsf_queue_designator
suffix:semicolon
r_struct
id|fsf_status_read_buffer
suffix:semicolon
r_struct
id|fsf_port_closed_payload
suffix:semicolon
r_struct
id|fsf_bit_error_payload
suffix:semicolon
r_union
id|fsf_prot_status_qual
suffix:semicolon
r_struct
id|fsf_qual_version_error
suffix:semicolon
r_struct
id|fsf_qual_sequence_error
suffix:semicolon
r_struct
id|fsf_qtcb_prefix
suffix:semicolon
r_struct
id|fsf_qtcb_header
suffix:semicolon
r_struct
id|fsf_qtcb_bottom_config
suffix:semicolon
r_struct
id|fsf_qtcb_bottom_support
suffix:semicolon
r_struct
id|fsf_qtcb_bottom_io
suffix:semicolon
r_union
id|fsf_qtcb_bottom
suffix:semicolon
DECL|struct|fsf_queue_designator
r_struct
id|fsf_queue_designator
(brace
DECL|member|cssid
id|u8
id|cssid
suffix:semicolon
DECL|member|chpid
id|u8
id|chpid
suffix:semicolon
DECL|member|hla
id|u8
id|hla
suffix:semicolon
DECL|member|ua
id|u8
id|ua
suffix:semicolon
DECL|member|res1
id|u32
id|res1
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_port_closed_payload
r_struct
id|fsf_port_closed_payload
(brace
DECL|member|queue_designator
r_struct
id|fsf_queue_designator
id|queue_designator
suffix:semicolon
DECL|member|port_handle
id|u32
id|port_handle
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_bit_error_payload
r_struct
id|fsf_bit_error_payload
(brace
DECL|member|res1
id|u32
id|res1
suffix:semicolon
DECL|member|link_failure_error_count
id|u32
id|link_failure_error_count
suffix:semicolon
DECL|member|loss_of_sync_error_count
id|u32
id|loss_of_sync_error_count
suffix:semicolon
DECL|member|loss_of_signal_error_count
id|u32
id|loss_of_signal_error_count
suffix:semicolon
DECL|member|primitive_sequence_error_count
id|u32
id|primitive_sequence_error_count
suffix:semicolon
DECL|member|invalid_transmission_word_error_count
id|u32
id|invalid_transmission_word_error_count
suffix:semicolon
DECL|member|crc_error_count
id|u32
id|crc_error_count
suffix:semicolon
DECL|member|primitive_sequence_event_timeout_count
id|u32
id|primitive_sequence_event_timeout_count
suffix:semicolon
DECL|member|elastic_buffer_overrun_error_count
id|u32
id|elastic_buffer_overrun_error_count
suffix:semicolon
DECL|member|fcal_arbitration_timeout_count
id|u32
id|fcal_arbitration_timeout_count
suffix:semicolon
DECL|member|advertised_receive_b2b_credit
id|u32
id|advertised_receive_b2b_credit
suffix:semicolon
DECL|member|current_receive_b2b_credit
id|u32
id|current_receive_b2b_credit
suffix:semicolon
DECL|member|advertised_transmit_b2b_credit
id|u32
id|advertised_transmit_b2b_credit
suffix:semicolon
DECL|member|current_transmit_b2b_credit
id|u32
id|current_transmit_b2b_credit
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_status_read_buffer
r_struct
id|fsf_status_read_buffer
(brace
DECL|member|status_type
id|u32
id|status_type
suffix:semicolon
DECL|member|status_subtype
id|u32
id|status_subtype
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|res1
id|u32
id|res1
suffix:semicolon
DECL|member|queue_designator
r_struct
id|fsf_queue_designator
id|queue_designator
suffix:semicolon
DECL|member|d_id
id|u32
id|d_id
suffix:semicolon
DECL|member|class
id|u32
r_class
suffix:semicolon
DECL|member|fcp_lun
id|u64
id|fcp_lun
suffix:semicolon
DECL|member|res3
id|u8
id|res3
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|payload
id|u8
id|payload
(braket
id|FSF_STATUS_READ_PAYLOAD_SIZE
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qual_version_error
r_struct
id|fsf_qual_version_error
(brace
DECL|member|fsf_version
id|u32
id|fsf_version
suffix:semicolon
DECL|member|res1
id|u32
id|res1
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qual_sequence_error
r_struct
id|fsf_qual_sequence_error
(brace
DECL|member|exp_req_seq_no
id|u32
id|exp_req_seq_no
suffix:semicolon
DECL|member|res1
id|u32
id|res1
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qual_locallink_error
r_struct
id|fsf_qual_locallink_error
(brace
DECL|member|code
id|u32
id|code
suffix:semicolon
DECL|member|res1
id|u32
id|res1
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|fsf_prot_status_qual
r_union
id|fsf_prot_status_qual
(brace
DECL|member|version_error
r_struct
id|fsf_qual_version_error
id|version_error
suffix:semicolon
DECL|member|sequence_error
r_struct
id|fsf_qual_sequence_error
id|sequence_error
suffix:semicolon
DECL|member|locallink_error
r_struct
id|fsf_qual_locallink_error
id|locallink_error
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qtcb_prefix
r_struct
id|fsf_qtcb_prefix
(brace
DECL|member|req_id
id|u64
id|req_id
suffix:semicolon
DECL|member|qtcb_version
id|u32
id|qtcb_version
suffix:semicolon
DECL|member|ulp_info
id|u32
id|ulp_info
suffix:semicolon
DECL|member|qtcb_type
id|u32
id|qtcb_type
suffix:semicolon
DECL|member|req_seq_no
id|u32
id|req_seq_no
suffix:semicolon
DECL|member|prot_status
id|u32
id|prot_status
suffix:semicolon
DECL|member|prot_status_qual
r_union
id|fsf_prot_status_qual
id|prot_status_qual
suffix:semicolon
DECL|member|res1
id|u8
id|res1
(braket
l_int|20
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|fsf_status_qual
r_union
id|fsf_status_qual
(brace
DECL|member|byte
id|u8
id|byte
(braket
id|FSF_STATUS_QUALIFIER_SIZE
)braket
suffix:semicolon
DECL|member|halfword
id|u16
id|halfword
(braket
id|FSF_STATUS_QUALIFIER_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
)braket
suffix:semicolon
DECL|member|word
id|u32
id|word
(braket
id|FSF_STATUS_QUALIFIER_SIZE
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|fsf_queue_designator
r_struct
id|fsf_queue_designator
id|fsf_queue_designator
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qtcb_header
r_struct
id|fsf_qtcb_header
(brace
DECL|member|req_handle
id|u64
id|req_handle
suffix:semicolon
DECL|member|fsf_command
id|u32
id|fsf_command
suffix:semicolon
DECL|member|res1
id|u32
id|res1
suffix:semicolon
DECL|member|port_handle
id|u32
id|port_handle
suffix:semicolon
DECL|member|lun_handle
id|u32
id|lun_handle
suffix:semicolon
DECL|member|res2
id|u32
id|res2
suffix:semicolon
DECL|member|fsf_status
id|u32
id|fsf_status
suffix:semicolon
DECL|member|fsf_status_qual
r_union
id|fsf_status_qual
id|fsf_status_qual
suffix:semicolon
DECL|member|res3
id|u8
id|res3
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|log_start
id|u16
id|log_start
suffix:semicolon
DECL|member|log_length
id|u16
id|log_length
suffix:semicolon
DECL|member|res4
id|u8
id|res4
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_nport_serv_param
r_struct
id|fsf_nport_serv_param
(brace
DECL|member|common_serv_param
id|u8
id|common_serv_param
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|wwpn
id|u64
id|wwpn
suffix:semicolon
DECL|member|wwnn
id|u64
id|wwnn
suffix:semicolon
DECL|member|class1_serv_param
id|u8
id|class1_serv_param
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|class2_serv_param
id|u8
id|class2_serv_param
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|class3_serv_param
id|u8
id|class3_serv_param
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|class4_serv_param
id|u8
id|class4_serv_param
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|vendor_version_level
id|u8
id|vendor_version_level
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|res1
id|u8
id|res1
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_plogi
r_struct
id|fsf_plogi
(brace
DECL|member|code
id|u32
id|code
suffix:semicolon
DECL|member|serv_param
r_struct
id|fsf_nport_serv_param
id|serv_param
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|FSF_FCP_CMND_SIZE
mdefine_line|#define FSF_FCP_CMND_SIZE&t;288
DECL|macro|FSF_FCP_RSP_SIZE
mdefine_line|#define FSF_FCP_RSP_SIZE&t;128
DECL|struct|fsf_qtcb_bottom_io
r_struct
id|fsf_qtcb_bottom_io
(brace
DECL|member|data_direction
id|u32
id|data_direction
suffix:semicolon
DECL|member|service_class
id|u32
id|service_class
suffix:semicolon
DECL|member|res1
id|u8
id|res1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fcp_cmnd_length
id|u32
id|fcp_cmnd_length
suffix:semicolon
DECL|member|res2
id|u8
id|res2
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|fcp_cmnd
id|u8
id|fcp_cmnd
(braket
id|FSF_FCP_CMND_SIZE
)braket
suffix:semicolon
DECL|member|fcp_rsp
id|u8
id|fcp_rsp
(braket
id|FSF_FCP_RSP_SIZE
)braket
suffix:semicolon
DECL|member|res3
id|u8
id|res3
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qtcb_bottom_support
r_struct
id|fsf_qtcb_bottom_support
(brace
DECL|member|operation_subtype
id|u32
id|operation_subtype
suffix:semicolon
DECL|member|res1
id|u8
id|res1
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|d_id
id|u32
id|d_id
suffix:semicolon
DECL|member|option
id|u32
id|option
suffix:semicolon
DECL|member|fcp_lun
id|u64
id|fcp_lun
suffix:semicolon
DECL|member|res2
id|u64
id|res2
suffix:semicolon
DECL|member|req_handle
id|u64
id|req_handle
suffix:semicolon
DECL|member|service_class
id|u32
id|service_class
suffix:semicolon
DECL|member|res3
id|u8
id|res3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|timeout
id|u8
id|timeout
suffix:semicolon
DECL|member|lun_access_info
id|u32
id|lun_access_info
suffix:semicolon
DECL|member|res4
id|u8
id|res4
(braket
l_int|180
)braket
suffix:semicolon
DECL|member|els1_length
id|u32
id|els1_length
suffix:semicolon
DECL|member|els2_length
id|u32
id|els2_length
suffix:semicolon
DECL|member|req_buf_length
id|u32
id|req_buf_length
suffix:semicolon
DECL|member|resp_buf_length
id|u32
id|resp_buf_length
suffix:semicolon
DECL|member|els
id|u8
id|els
(braket
l_int|256
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qtcb_bottom_config
r_struct
id|fsf_qtcb_bottom_config
(brace
DECL|member|lic_version
id|u32
id|lic_version
suffix:semicolon
DECL|member|feature_selection
id|u32
id|feature_selection
suffix:semicolon
DECL|member|high_qtcb_version
id|u32
id|high_qtcb_version
suffix:semicolon
DECL|member|low_qtcb_version
id|u32
id|low_qtcb_version
suffix:semicolon
DECL|member|max_qtcb_size
id|u32
id|max_qtcb_size
suffix:semicolon
DECL|member|max_data_transfer_size
id|u32
id|max_data_transfer_size
suffix:semicolon
DECL|member|supported_features
id|u32
id|supported_features
suffix:semicolon
DECL|member|res1
id|u8
id|res1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fc_topology
id|u32
id|fc_topology
suffix:semicolon
DECL|member|fc_link_speed
id|u32
id|fc_link_speed
suffix:semicolon
DECL|member|adapter_type
id|u32
id|adapter_type
suffix:semicolon
DECL|member|peer_d_id
id|u32
id|peer_d_id
suffix:semicolon
DECL|member|res2
id|u8
id|res2
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|s_id
id|u32
id|s_id
suffix:semicolon
DECL|member|nport_serv_param
r_struct
id|fsf_nport_serv_param
id|nport_serv_param
suffix:semicolon
DECL|member|res3
id|u8
id|res3
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|adapter_ports
id|u32
id|adapter_ports
suffix:semicolon
DECL|member|hardware_version
id|u32
id|hardware_version
suffix:semicolon
DECL|member|serial_number
id|u8
id|serial_number
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|res4
id|u8
id|res4
(braket
l_int|272
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|fsf_qtcb_bottom_port
r_struct
id|fsf_qtcb_bottom_port
(brace
DECL|member|res1
id|u8
id|res1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fc_port_id
id|u32
id|fc_port_id
suffix:semicolon
DECL|member|port_type
id|u32
id|port_type
suffix:semicolon
DECL|member|port_state
id|u32
id|port_state
suffix:semicolon
DECL|member|class_of_service
id|u32
id|class_of_service
suffix:semicolon
multiline_comment|/* should be 0x00000006 for class 2 and 3 */
DECL|member|supported_fc4_types
id|u8
id|supported_fc4_types
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* should be 0x00000100 for scsi fcp */
DECL|member|active_fc4_types
id|u8
id|active_fc4_types
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|supported_speed
id|u32
id|supported_speed
suffix:semicolon
multiline_comment|/* 0x0001 for 1 GBit/s or 0x0002 for 2 GBit/s */
DECL|member|maximum_frame_size
id|u32
id|maximum_frame_size
suffix:semicolon
multiline_comment|/* fixed value of 2112 */
DECL|member|seconds_since_last_reset
id|u64
id|seconds_since_last_reset
suffix:semicolon
DECL|member|tx_frames
id|u64
id|tx_frames
suffix:semicolon
DECL|member|tx_words
id|u64
id|tx_words
suffix:semicolon
DECL|member|rx_frames
id|u64
id|rx_frames
suffix:semicolon
DECL|member|rx_words
id|u64
id|rx_words
suffix:semicolon
DECL|member|lip
id|u64
id|lip
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|nos
id|u64
id|nos
suffix:semicolon
multiline_comment|/* currently 0 */
DECL|member|error_frames
id|u64
id|error_frames
suffix:semicolon
multiline_comment|/* currently 0 */
DECL|member|dumped_frames
id|u64
id|dumped_frames
suffix:semicolon
multiline_comment|/* currently 0 */
DECL|member|link_failure
id|u64
id|link_failure
suffix:semicolon
DECL|member|loss_of_sync
id|u64
id|loss_of_sync
suffix:semicolon
DECL|member|loss_of_signal
id|u64
id|loss_of_signal
suffix:semicolon
DECL|member|psp_error_counts
id|u64
id|psp_error_counts
suffix:semicolon
DECL|member|invalid_tx_words
id|u64
id|invalid_tx_words
suffix:semicolon
DECL|member|invalid_crcs
id|u64
id|invalid_crcs
suffix:semicolon
DECL|member|input_requests
id|u64
id|input_requests
suffix:semicolon
DECL|member|output_requests
id|u64
id|output_requests
suffix:semicolon
DECL|member|control_requests
id|u64
id|control_requests
suffix:semicolon
DECL|member|input_mb
id|u64
id|input_mb
suffix:semicolon
multiline_comment|/* where 1 MByte == 1.000.000 Bytes */
DECL|member|output_mb
id|u64
id|output_mb
suffix:semicolon
multiline_comment|/* where 1 MByte == 1.000.000 Bytes */
DECL|member|res2
id|u8
id|res2
(braket
l_int|256
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|fsf_qtcb_bottom
r_union
id|fsf_qtcb_bottom
(brace
DECL|member|io
r_struct
id|fsf_qtcb_bottom_io
id|io
suffix:semicolon
DECL|member|support
r_struct
id|fsf_qtcb_bottom_support
id|support
suffix:semicolon
DECL|member|config
r_struct
id|fsf_qtcb_bottom_config
id|config
suffix:semicolon
DECL|member|port
r_struct
id|fsf_qtcb_bottom_port
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fsf_qtcb
r_struct
id|fsf_qtcb
(brace
DECL|member|prefix
r_struct
id|fsf_qtcb_prefix
id|prefix
suffix:semicolon
DECL|member|header
r_struct
id|fsf_qtcb_header
id|header
suffix:semicolon
DECL|member|bottom
r_union
id|fsf_qtcb_bottom
id|bottom
suffix:semicolon
DECL|member|log
id|u8
id|log
(braket
id|FSF_QTCB_LOG_SIZE
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* FSF_H */
eof
