multiline_comment|/*&n; * sbp2.h - Defines and prototypes for sbp2.c&n; *&n; * Copyright (C) 2000 James Goodwin, Filanet Corporation (www.filanet.com)&n; * jamesg@filanet.com&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef SBP2_H
DECL|macro|SBP2_H
mdefine_line|#define SBP2_H
DECL|macro|SBP2_DEVICE_NAME
mdefine_line|#define SBP2_DEVICE_NAME&t;&t;&quot;sbp2&quot;
multiline_comment|/*&n; * SBP2 specific structures and defines&n; */
DECL|macro|ORB_DIRECTION_WRITE_TO_MEDIA
mdefine_line|#define ORB_DIRECTION_WRITE_TO_MEDIA    0x0
DECL|macro|ORB_DIRECTION_READ_FROM_MEDIA
mdefine_line|#define ORB_DIRECTION_READ_FROM_MEDIA   0x1
DECL|macro|ORB_DIRECTION_NO_DATA_TRANSFER
mdefine_line|#define ORB_DIRECTION_NO_DATA_TRANSFER  0x2
DECL|macro|ORB_SET_NULL_PTR
mdefine_line|#define ORB_SET_NULL_PTR(value)&t;&t;&t;((value &amp; 0x1) &lt;&lt; 31)
DECL|macro|ORB_SET_NOTIFY
mdefine_line|#define ORB_SET_NOTIFY(value)                   ((value &amp; 0x1) &lt;&lt; 31)
DECL|macro|ORB_SET_RQ_FMT
mdefine_line|#define ORB_SET_RQ_FMT(value)                   ((value &amp; 0x3) &lt;&lt; 29)&t;/* unused ? */
DECL|macro|ORB_SET_NODE_ID
mdefine_line|#define ORB_SET_NODE_ID(value)&t;&t;&t;((value &amp; 0xffff) &lt;&lt; 16)
DECL|macro|ORB_SET_DATA_SIZE
mdefine_line|#define ORB_SET_DATA_SIZE(value)                (value &amp; 0xffff)
DECL|macro|ORB_SET_PAGE_SIZE
mdefine_line|#define ORB_SET_PAGE_SIZE(value)                ((value &amp; 0x7) &lt;&lt; 16)
DECL|macro|ORB_SET_PAGE_TABLE_PRESENT
mdefine_line|#define ORB_SET_PAGE_TABLE_PRESENT(value)       ((value &amp; 0x1) &lt;&lt; 19)
DECL|macro|ORB_SET_MAX_PAYLOAD
mdefine_line|#define ORB_SET_MAX_PAYLOAD(value)              ((value &amp; 0xf) &lt;&lt; 20)
DECL|macro|ORB_SET_SPEED
mdefine_line|#define ORB_SET_SPEED(value)                    ((value &amp; 0x7) &lt;&lt; 24)
DECL|macro|ORB_SET_DIRECTION
mdefine_line|#define ORB_SET_DIRECTION(value)                ((value &amp; 0x1) &lt;&lt; 27)
DECL|struct|sbp2_command_orb
r_struct
id|sbp2_command_orb
(brace
DECL|member|next_ORB_hi
r_volatile
id|u32
id|next_ORB_hi
suffix:semicolon
DECL|member|next_ORB_lo
r_volatile
id|u32
id|next_ORB_lo
suffix:semicolon
DECL|member|data_descriptor_hi
id|u32
id|data_descriptor_hi
suffix:semicolon
DECL|member|data_descriptor_lo
id|u32
id|data_descriptor_lo
suffix:semicolon
DECL|member|misc
id|u32
id|misc
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LOGIN_REQUEST
mdefine_line|#define LOGIN_REQUEST&t;&t;&t;0x0
DECL|macro|QUERY_LOGINS_REQUEST
mdefine_line|#define QUERY_LOGINS_REQUEST&t;&t;0x1
DECL|macro|RECONNECT_REQUEST
mdefine_line|#define RECONNECT_REQUEST&t;&t;0x3
DECL|macro|SET_PASSWORD_REQUEST
mdefine_line|#define SET_PASSWORD_REQUEST&t;&t;0x4
DECL|macro|LOGOUT_REQUEST
mdefine_line|#define LOGOUT_REQUEST&t;&t;&t;0x7
DECL|macro|ABORT_TASK_REQUEST
mdefine_line|#define ABORT_TASK_REQUEST&t;&t;0xb
DECL|macro|ABORT_TASK_SET
mdefine_line|#define ABORT_TASK_SET&t;&t;&t;0xc
DECL|macro|LOGICAL_UNIT_RESET
mdefine_line|#define LOGICAL_UNIT_RESET&t;&t;0xe
DECL|macro|TARGET_RESET_REQUEST
mdefine_line|#define TARGET_RESET_REQUEST&t;&t;0xf
DECL|macro|ORB_SET_LUN
mdefine_line|#define ORB_SET_LUN(value)                      (value &amp; 0xffff)
DECL|macro|ORB_SET_FUNCTION
mdefine_line|#define ORB_SET_FUNCTION(value)                 ((value &amp; 0xf) &lt;&lt; 16)
DECL|macro|ORB_SET_RECONNECT
mdefine_line|#define ORB_SET_RECONNECT(value)                ((value &amp; 0xf) &lt;&lt; 20)
DECL|macro|ORB_SET_EXCLUSIVE
mdefine_line|#define ORB_SET_EXCLUSIVE(value)                ((value &amp; 0x1) &lt;&lt; 28)
DECL|macro|ORB_SET_LOGIN_RESP_LENGTH
mdefine_line|#define ORB_SET_LOGIN_RESP_LENGTH(value)        (value &amp; 0xffff)
DECL|macro|ORB_SET_PASSWD_LENGTH
mdefine_line|#define ORB_SET_PASSWD_LENGTH(value)            ((value &amp; 0xffff) &lt;&lt; 16)
DECL|struct|sbp2_login_orb
r_struct
id|sbp2_login_orb
(brace
DECL|member|password_hi
id|u32
id|password_hi
suffix:semicolon
DECL|member|password_lo
id|u32
id|password_lo
suffix:semicolon
DECL|member|login_response_hi
id|u32
id|login_response_hi
suffix:semicolon
DECL|member|login_response_lo
id|u32
id|login_response_lo
suffix:semicolon
DECL|member|lun_misc
id|u32
id|lun_misc
suffix:semicolon
DECL|member|passwd_resp_lengths
id|u32
id|passwd_resp_lengths
suffix:semicolon
DECL|member|status_FIFO_hi
id|u32
id|status_FIFO_hi
suffix:semicolon
DECL|member|status_FIFO_lo
id|u32
id|status_FIFO_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RESPONSE_GET_LOGIN_ID
mdefine_line|#define RESPONSE_GET_LOGIN_ID(value)            (value &amp; 0xffff)
DECL|macro|RESPONSE_GET_LENGTH
mdefine_line|#define RESPONSE_GET_LENGTH(value)              ((value &gt;&gt; 16) &amp; 0xffff)
DECL|macro|RESPONSE_GET_RECONNECT_HOLD
mdefine_line|#define RESPONSE_GET_RECONNECT_HOLD(value)      (value &amp; 0xffff)
DECL|struct|sbp2_login_response
r_struct
id|sbp2_login_response
(brace
DECL|member|length_login_ID
id|u32
id|length_login_ID
suffix:semicolon
DECL|member|command_block_agent_hi
id|u32
id|command_block_agent_hi
suffix:semicolon
DECL|member|command_block_agent_lo
id|u32
id|command_block_agent_lo
suffix:semicolon
DECL|member|reconnect_hold
id|u32
id|reconnect_hold
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ORB_SET_LOGIN_ID
mdefine_line|#define ORB_SET_LOGIN_ID(value)                 (value &amp; 0xffff)
DECL|macro|ORB_SET_QUERY_LOGINS_RESP_LENGTH
mdefine_line|#define ORB_SET_QUERY_LOGINS_RESP_LENGTH(value) (value &amp; 0xffff)
DECL|struct|sbp2_query_logins_orb
r_struct
id|sbp2_query_logins_orb
(brace
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|query_response_hi
id|u32
id|query_response_hi
suffix:semicolon
DECL|member|query_response_lo
id|u32
id|query_response_lo
suffix:semicolon
DECL|member|lun_misc
id|u32
id|lun_misc
suffix:semicolon
DECL|member|reserved_resp_length
id|u32
id|reserved_resp_length
suffix:semicolon
DECL|member|status_FIFO_hi
id|u32
id|status_FIFO_hi
suffix:semicolon
DECL|member|status_FIFO_lo
id|u32
id|status_FIFO_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RESPONSE_GET_MAX_LOGINS
mdefine_line|#define RESPONSE_GET_MAX_LOGINS(value)          (value &amp; 0xffff)
DECL|macro|RESPONSE_GET_ACTIVE_LOGINS
mdefine_line|#define RESPONSE_GET_ACTIVE_LOGINS(value)       ((RESPONSE_GET_LENGTH(value) - 4) / 12)
DECL|struct|sbp2_query_logins_response
r_struct
id|sbp2_query_logins_response
(brace
DECL|member|length_max_logins
id|u32
id|length_max_logins
suffix:semicolon
DECL|member|misc_IDs
id|u32
id|misc_IDs
suffix:semicolon
DECL|member|initiator_misc_hi
id|u32
id|initiator_misc_hi
suffix:semicolon
DECL|member|initiator_misc_lo
id|u32
id|initiator_misc_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sbp2_reconnect_orb
r_struct
id|sbp2_reconnect_orb
(brace
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|member|login_ID_misc
id|u32
id|login_ID_misc
suffix:semicolon
DECL|member|reserved5
id|u32
id|reserved5
suffix:semicolon
DECL|member|status_FIFO_hi
id|u32
id|status_FIFO_hi
suffix:semicolon
DECL|member|status_FIFO_lo
id|u32
id|status_FIFO_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sbp2_logout_orb
r_struct
id|sbp2_logout_orb
(brace
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|member|login_ID_misc
id|u32
id|login_ID_misc
suffix:semicolon
DECL|member|reserved5
id|u32
id|reserved5
suffix:semicolon
DECL|member|status_FIFO_hi
id|u32
id|status_FIFO_hi
suffix:semicolon
DECL|member|status_FIFO_lo
id|u32
id|status_FIFO_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PAGE_TABLE_SET_SEGMENT_BASE_HI
mdefine_line|#define PAGE_TABLE_SET_SEGMENT_BASE_HI(value)   (value &amp; 0xffff)
DECL|macro|PAGE_TABLE_SET_SEGMENT_LENGTH
mdefine_line|#define PAGE_TABLE_SET_SEGMENT_LENGTH(value)    ((value &amp; 0xffff) &lt;&lt; 16)
DECL|struct|sbp2_unrestricted_page_table
r_struct
id|sbp2_unrestricted_page_table
(brace
DECL|member|length_segment_base_hi
id|u32
id|length_segment_base_hi
suffix:semicolon
DECL|member|segment_base_lo
id|u32
id|segment_base_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RESP_STATUS_REQUEST_COMPLETE
mdefine_line|#define RESP_STATUS_REQUEST_COMPLETE&t;&t;0x0
DECL|macro|RESP_STATUS_TRANSPORT_FAILURE
mdefine_line|#define RESP_STATUS_TRANSPORT_FAILURE&t;&t;0x1
DECL|macro|RESP_STATUS_ILLEGAL_REQUEST
mdefine_line|#define RESP_STATUS_ILLEGAL_REQUEST&t;&t;0x2
DECL|macro|RESP_STATUS_VENDOR_DEPENDENT
mdefine_line|#define RESP_STATUS_VENDOR_DEPENDENT&t;&t;0x3
DECL|macro|SBP2_STATUS_NO_ADDITIONAL_INFO
mdefine_line|#define SBP2_STATUS_NO_ADDITIONAL_INFO&t;&t;0x0
DECL|macro|SBP2_STATUS_REQ_TYPE_NOT_SUPPORTED
mdefine_line|#define SBP2_STATUS_REQ_TYPE_NOT_SUPPORTED&t;0x1
DECL|macro|SBP2_STATUS_SPEED_NOT_SUPPORTED
mdefine_line|#define SBP2_STATUS_SPEED_NOT_SUPPORTED&t;&t;0x2
DECL|macro|SBP2_STATUS_PAGE_SIZE_NOT_SUPPORTED
mdefine_line|#define SBP2_STATUS_PAGE_SIZE_NOT_SUPPORTED&t;0x3
DECL|macro|SBP2_STATUS_ACCESS_DENIED
mdefine_line|#define SBP2_STATUS_ACCESS_DENIED&t;&t;0x4
DECL|macro|SBP2_STATUS_LU_NOT_SUPPORTED
mdefine_line|#define SBP2_STATUS_LU_NOT_SUPPORTED&t;&t;0x5
DECL|macro|SBP2_STATUS_MAX_PAYLOAD_TOO_SMALL
mdefine_line|#define SBP2_STATUS_MAX_PAYLOAD_TOO_SMALL&t;0x6
DECL|macro|SBP2_STATUS_RESOURCES_UNAVAILABLE
mdefine_line|#define SBP2_STATUS_RESOURCES_UNAVAILABLE&t;0x8
DECL|macro|SBP2_STATUS_FUNCTION_REJECTED
mdefine_line|#define SBP2_STATUS_FUNCTION_REJECTED&t;&t;0x9
DECL|macro|SBP2_STATUS_LOGIN_ID_NOT_RECOGNIZED
mdefine_line|#define SBP2_STATUS_LOGIN_ID_NOT_RECOGNIZED&t;0xa
DECL|macro|SBP2_STATUS_DUMMY_ORB_COMPLETED
mdefine_line|#define SBP2_STATUS_DUMMY_ORB_COMPLETED&t;&t;0xb
DECL|macro|SBP2_STATUS_REQUEST_ABORTED
mdefine_line|#define SBP2_STATUS_REQUEST_ABORTED&t;&t;0xc
DECL|macro|SBP2_STATUS_UNSPECIFIED_ERROR
mdefine_line|#define SBP2_STATUS_UNSPECIFIED_ERROR&t;&t;0xff
DECL|macro|SFMT_CURRENT_ERROR
mdefine_line|#define SFMT_CURRENT_ERROR&t;&t;&t;0x0
DECL|macro|SFMT_DEFERRED_ERROR
mdefine_line|#define SFMT_DEFERRED_ERROR&t;&t;&t;0x1
DECL|macro|SFMT_VENDOR_DEPENDENT_STATUS
mdefine_line|#define SFMT_VENDOR_DEPENDENT_STATUS&t;&t;0x3
DECL|macro|SBP2_SCSI_STATUS_GOOD
mdefine_line|#define SBP2_SCSI_STATUS_GOOD&t;&t;&t;0x0
DECL|macro|SBP2_SCSI_STATUS_CHECK_CONDITION
mdefine_line|#define SBP2_SCSI_STATUS_CHECK_CONDITION&t;0x2
DECL|macro|SBP2_SCSI_STATUS_CONDITION_MET
mdefine_line|#define SBP2_SCSI_STATUS_CONDITION_MET&t;&t;0x4
DECL|macro|SBP2_SCSI_STATUS_BUSY
mdefine_line|#define SBP2_SCSI_STATUS_BUSY&t;&t;&t;0x8
DECL|macro|SBP2_SCSI_STATUS_RESERVATION_CONFLICT
mdefine_line|#define SBP2_SCSI_STATUS_RESERVATION_CONFLICT&t;0x18
DECL|macro|SBP2_SCSI_STATUS_COMMAND_TERMINATED
mdefine_line|#define SBP2_SCSI_STATUS_COMMAND_TERMINATED&t;0x22
DECL|macro|SBP2_SCSI_STATUS_SELECTION_TIMEOUT
mdefine_line|#define SBP2_SCSI_STATUS_SELECTION_TIMEOUT&t;0xff
DECL|macro|STATUS_GET_ORB_OFFSET_HI
mdefine_line|#define STATUS_GET_ORB_OFFSET_HI(value)         (value &amp; 0xffff)
DECL|macro|STATUS_GET_SBP_STATUS
mdefine_line|#define STATUS_GET_SBP_STATUS(value)            ((value &gt;&gt; 16) &amp; 0xff)
DECL|macro|STATUS_GET_LENGTH
mdefine_line|#define STATUS_GET_LENGTH(value)                ((value &gt;&gt; 24) &amp; 0x7)
DECL|macro|STATUS_GET_DEAD_BIT
mdefine_line|#define STATUS_GET_DEAD_BIT(value)              ((value &gt;&gt; 27) &amp; 0x1)
DECL|macro|STATUS_GET_RESP
mdefine_line|#define STATUS_GET_RESP(value)                  ((value &gt;&gt; 28) &amp; 0x3)
DECL|macro|STATUS_GET_SRC
mdefine_line|#define STATUS_GET_SRC(value)                   ((value &gt;&gt; 30) &amp; 0x3)
DECL|struct|sbp2_status_block
r_struct
id|sbp2_status_block
(brace
DECL|member|ORB_offset_hi_misc
id|u32
id|ORB_offset_hi_misc
suffix:semicolon
DECL|member|ORB_offset_lo
id|u32
id|ORB_offset_lo
suffix:semicolon
DECL|member|command_set_dependent
id|u8
id|command_set_dependent
(braket
l_int|24
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Miscellaneous SBP2 related config rom defines&n; */
multiline_comment|/* &n; * The status fifo address definition below is used as a status base, with a chunk&n; * separately assigned for each sbp2 device detected. For example, 0xfffe00000000ULL &n; * is used for the first sbp2 device detected, 0xfffe00000020ULL for the next sbp2 &n; * device, and so on.&n; *&n; * Note: We could use a single status fifo address for all sbp2 devices, and figure &n; * out which sbp2 device the status belongs to by looking at the source node id of&n; * the status write... but, using separate addresses for each sbp2 device allows for&n; * better code and the ability to support multiple luns within a single 1394 node.&n; *&n; * Also note that we choose the address range below as it is a region specified for&n; * write posting, where the ohci controller will automatically send an ack_complete&n; * when the status is written by the sbp2 device... saving a split transaction.   =)&n; */
DECL|macro|SBP2_STATUS_FIFO_ADDRESS
mdefine_line|#define SBP2_STATUS_FIFO_ADDRESS&t;&t;&t;&t;0xfffe00000000ULL
DECL|macro|SBP2_STATUS_FIFO_ADDRESS_HI
mdefine_line|#define SBP2_STATUS_FIFO_ADDRESS_HI                             0xfffe
DECL|macro|SBP2_STATUS_FIFO_ADDRESS_LO
mdefine_line|#define SBP2_STATUS_FIFO_ADDRESS_LO                             0x0
DECL|macro|SBP2_STATUS_FIFO_ENTRY_TO_OFFSET
mdefine_line|#define SBP2_STATUS_FIFO_ENTRY_TO_OFFSET(entry)&t;&t;&t;((entry) &lt;&lt; 5)
DECL|macro|SBP2_STATUS_FIFO_OFFSET_TO_ENTRY
mdefine_line|#define SBP2_STATUS_FIFO_OFFSET_TO_ENTRY(offset)&t;&t;((offset) &gt;&gt; 5)
DECL|macro|SBP2_UNIT_DIRECTORY_OFFSET_KEY
mdefine_line|#define SBP2_UNIT_DIRECTORY_OFFSET_KEY&t;&t;&t;&t;0xd1
DECL|macro|SBP2_CSR_OFFSET_KEY
mdefine_line|#define SBP2_CSR_OFFSET_KEY&t;&t;&t;&t;&t;0x54
DECL|macro|SBP2_UNIT_SPEC_ID_KEY
mdefine_line|#define SBP2_UNIT_SPEC_ID_KEY&t;&t;&t;&t;&t;0x12
DECL|macro|SBP2_UNIT_SW_VERSION_KEY
mdefine_line|#define SBP2_UNIT_SW_VERSION_KEY&t;&t;&t;&t;0x13
DECL|macro|SBP2_COMMAND_SET_SPEC_ID_KEY
mdefine_line|#define SBP2_COMMAND_SET_SPEC_ID_KEY&t;&t;&t;&t;0x38
DECL|macro|SBP2_COMMAND_SET_KEY
mdefine_line|#define SBP2_COMMAND_SET_KEY&t;&t;&t;&t;&t;0x39
DECL|macro|SBP2_UNIT_CHARACTERISTICS_KEY
mdefine_line|#define SBP2_UNIT_CHARACTERISTICS_KEY&t;&t;&t;&t;0x3a
DECL|macro|SBP2_DEVICE_TYPE_AND_LUN_KEY
mdefine_line|#define SBP2_DEVICE_TYPE_AND_LUN_KEY&t;&t;&t;&t;0x14
DECL|macro|SBP2_FIRMWARE_REVISION_KEY
mdefine_line|#define SBP2_FIRMWARE_REVISION_KEY&t;&t;&t;&t;0x3c
DECL|macro|SBP2_DEVICE_TYPE
mdefine_line|#define SBP2_DEVICE_TYPE(q)&t;&t;&t;&t;&t;(((q) &gt;&gt; 16) &amp; 0x1f)
DECL|macro|SBP2_DEVICE_LUN
mdefine_line|#define SBP2_DEVICE_LUN(q)&t;&t;&t;&t;&t;((q) &amp; 0xffff)
DECL|macro|SBP2_AGENT_STATE_OFFSET
mdefine_line|#define SBP2_AGENT_STATE_OFFSET&t;&t;&t;&t;&t;0x00ULL
DECL|macro|SBP2_AGENT_RESET_OFFSET
mdefine_line|#define SBP2_AGENT_RESET_OFFSET&t;&t;&t;&t;&t;0x04ULL
DECL|macro|SBP2_ORB_POINTER_OFFSET
mdefine_line|#define SBP2_ORB_POINTER_OFFSET&t;&t;&t;&t;&t;0x08ULL
DECL|macro|SBP2_DOORBELL_OFFSET
mdefine_line|#define SBP2_DOORBELL_OFFSET&t;&t;&t;&t;&t;0x10ULL
DECL|macro|SBP2_UNSOLICITED_STATUS_ENABLE_OFFSET
mdefine_line|#define SBP2_UNSOLICITED_STATUS_ENABLE_OFFSET&t;&t;&t;0x14ULL
DECL|macro|SBP2_UNSOLICITED_STATUS_VALUE
mdefine_line|#define SBP2_UNSOLICITED_STATUS_VALUE&t;&t;&t;&t;0xf
DECL|macro|SBP2_BUSY_TIMEOUT_ADDRESS
mdefine_line|#define SBP2_BUSY_TIMEOUT_ADDRESS&t;&t;&t;&t;0xfffff0000210ULL
DECL|macro|SBP2_BUSY_TIMEOUT_VALUE
mdefine_line|#define SBP2_BUSY_TIMEOUT_VALUE&t;&t;&t;&t;&t;0xf
DECL|macro|SBP2_AGENT_RESET_DATA
mdefine_line|#define SBP2_AGENT_RESET_DATA&t;&t;&t;&t;&t;0xf
multiline_comment|/*&n; * Unit spec id and sw version entry for SBP-2 devices&n; */
DECL|macro|SBP2_UNIT_SPEC_ID_ENTRY
mdefine_line|#define SBP2_UNIT_SPEC_ID_ENTRY&t;&t;&t;&t;&t;0x0000609e
DECL|macro|SBP2_SW_VERSION_ENTRY
mdefine_line|#define SBP2_SW_VERSION_ENTRY&t;&t;&t;&t;&t;0x00010483
multiline_comment|/*&n; * Other misc defines&n; */
DECL|macro|SBP2_128KB_BROKEN_FIRMWARE
mdefine_line|#define SBP2_128KB_BROKEN_FIRMWARE&t;&t;&t;&t;0xa0b800
DECL|macro|SBP2_DEVICE_TYPE_LUN_UNINITIALIZED
mdefine_line|#define SBP2_DEVICE_TYPE_LUN_UNINITIALIZED&t;&t;&t;0xffffffff
multiline_comment|/*&n; * SCSI specific stuff&n; */
DECL|macro|SBP2_MAX_SG_ELEMENT_LENGTH
mdefine_line|#define SBP2_MAX_SG_ELEMENT_LENGTH&t;0xf000
DECL|macro|SBP2SCSI_MAX_SCSI_IDS
mdefine_line|#define SBP2SCSI_MAX_SCSI_IDS&t;&t;32&t;/* Max sbp2 device instances supported */
DECL|macro|SBP2_MAX_SECTORS
mdefine_line|#define SBP2_MAX_SECTORS&t;&t;255&t;/* Max sectors supported */
macro_line|#ifndef TYPE_SDAD
DECL|macro|TYPE_SDAD
mdefine_line|#define TYPE_SDAD&t;&t;&t;0x0e&t;/* simplified direct access device */
macro_line|#endif
multiline_comment|/*&n; * SCSI direction table... &n; * (now used as a back-up in case the direction passed down from above is &quot;unknown&quot;)&n; *&n; * DIN = IN data direction&n; * DOU = OUT data direction&n; * DNO = No data transfer&n; * DUN = Unknown data direction&n; *&n; * Opcode 0xec (Teac specific &quot;opc execute&quot;) possibly should be DNO,&n; * but we&squot;ll change it when somebody reports a problem with this.&n; */
DECL|macro|DIN
mdefine_line|#define DIN&t;&t;&t;&t;ORB_DIRECTION_READ_FROM_MEDIA
DECL|macro|DOU
mdefine_line|#define DOU&t;&t;&t;&t;ORB_DIRECTION_WRITE_TO_MEDIA
DECL|macro|DNO
mdefine_line|#define DNO&t;&t;&t;&t;ORB_DIRECTION_NO_DATA_TRANSFER
DECL|macro|DUN
mdefine_line|#define DUN&t;&t;&t;&t;DIN 
DECL|variable|sbp2scsi_direction_table
r_static
id|unchar
id|sbp2scsi_direction_table
(braket
l_int|0x100
)braket
op_assign
(brace
id|DNO
comma
id|DNO
comma
id|DIN
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DUN
comma
id|DOU
comma
id|DOU
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DIN
comma
id|DNO
comma
id|DIN
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DOU
comma
id|DNO
comma
id|DNO
comma
id|DOU
comma
id|DNO
comma
id|DIN
comma
id|DNO
comma
id|DIN
comma
id|DOU
comma
id|DNO
comma
id|DUN
comma
id|DIN
comma
id|DUN
comma
id|DIN
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DUN
comma
id|DUN
comma
id|DIN
comma
id|DIN
comma
id|DOU
comma
id|DNO
comma
id|DUN
comma
id|DIN
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DNO
comma
id|DIN
comma
id|DNO
comma
id|DNO
comma
id|DIN
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DIN
comma
id|DIN
comma
id|DIN
comma
id|DNO
comma
id|DIN
comma
id|DNO
comma
id|DNO
comma
id|DNO
comma
id|DUN
comma
id|DNO
comma
id|DOU
comma
id|DIN
comma
id|DNO
comma
id|DUN
comma
id|DUN
comma
id|DIN
comma
id|DIN
comma
id|DNO
comma
id|DNO
comma
id|DOU
comma
id|DUN
comma
id|DUN
comma
id|DNO
comma
id|DIN
comma
id|DIN
comma
id|DNO
comma
id|DIN
comma
id|DOU
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DNO
comma
id|DOU
comma
id|DOU
comma
id|DIN
comma
id|DNO
comma
id|DNO
comma
id|DNO
comma
id|DIN
comma
id|DNO
comma
id|DOU
comma
id|DUN
comma
id|DNO
comma
id|DIN
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DOU
comma
id|DNO
comma
id|DUN
comma
id|DIN
comma
id|DOU
comma
id|DIN
comma
id|DIN
comma
id|DIN
comma
id|DNO
comma
id|DNO
comma
id|DNO
comma
id|DIN
comma
id|DIN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DOU
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
comma
id|DUN
)brace
suffix:semicolon
multiline_comment|/* This should be safe. If there&squot;s more than one LUN per node, we could&n; * saturate the tlabel&squot;s though.  */
DECL|macro|SBP2_MAX_CMDS_PER_LUN
mdefine_line|#define SBP2_MAX_CMDS_PER_LUN   8
DECL|macro|SBP2_MAX_SCSI_QUEUE
mdefine_line|#define SBP2_MAX_SCSI_QUEUE&t;(SBP2_MAX_CMDS_PER_LUN * SBP2SCSI_MAX_SCSI_IDS)
DECL|macro|SBP2_MAX_COMMAND_ORBS
mdefine_line|#define SBP2_MAX_COMMAND_ORBS&t;SBP2_MAX_SCSI_QUEUE
multiline_comment|/* This is the two dma types we use for cmd_dma below */
DECL|enum|cmd_dma_types
r_enum
id|cmd_dma_types
(brace
DECL|enumerator|CMD_DMA_NONE
id|CMD_DMA_NONE
comma
DECL|enumerator|CMD_DMA_PAGE
id|CMD_DMA_PAGE
comma
DECL|enumerator|CMD_DMA_SINGLE
id|CMD_DMA_SINGLE
)brace
suffix:semicolon
multiline_comment|/* &n; * Encapsulates all the info necessary for an outstanding command. &n; */
DECL|struct|sbp2_command_info
r_struct
id|sbp2_command_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|____cacheline_aligned
r_struct
id|sbp2_command_orb
id|command_orb
id|____cacheline_aligned
suffix:semicolon
DECL|member|____cacheline_aligned
id|dma_addr_t
id|command_orb_dma
id|____cacheline_aligned
suffix:semicolon
DECL|member|Current_SCpnt
id|Scsi_Cmnd
op_star
id|Current_SCpnt
suffix:semicolon
DECL|member|Current_done
r_void
(paren
op_star
id|Current_done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Also need s/g structure for each sbp2 command */
DECL|member|____cacheline_aligned
r_struct
id|sbp2_unrestricted_page_table
id|scatter_gather_element
(braket
id|SG_ALL
)braket
id|____cacheline_aligned
suffix:semicolon
DECL|member|____cacheline_aligned
id|dma_addr_t
id|sge_dma
id|____cacheline_aligned
suffix:semicolon
DECL|member|sge_buffer
r_void
op_star
id|sge_buffer
suffix:semicolon
DECL|member|cmd_dma
id|dma_addr_t
id|cmd_dma
suffix:semicolon
DECL|member|dma_type
r_enum
id|cmd_dma_types
id|dma_type
suffix:semicolon
DECL|member|dma_size
r_int
r_int
id|dma_size
suffix:semicolon
DECL|member|dma_dir
r_int
id|dma_dir
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A list of flags for detected oddities and brokeness. */
DECL|macro|SBP2_BREAKAGE_128K_MAX_TRANSFER
mdefine_line|#define SBP2_BREAKAGE_128K_MAX_TRANSFER&t;&t;0x1
DECL|macro|SBP2_BREAKAGE_INQUIRY_HACK
mdefine_line|#define SBP2_BREAKAGE_INQUIRY_HACK&t;&t;0x2
r_struct
id|sbp2scsi_host_info
suffix:semicolon
multiline_comment|/*&n; * Information needed on a per scsi id basis (one for each sbp2 device)&n; */
DECL|struct|scsi_id_instance_data
r_struct
id|scsi_id_instance_data
(brace
multiline_comment|/* SCSI ID */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/*&n;&t; * Various sbp2 specific structures&n;&t; */
DECL|member|last_orb
r_struct
id|sbp2_command_orb
op_star
id|last_orb
suffix:semicolon
DECL|member|last_orb_dma
id|dma_addr_t
id|last_orb_dma
suffix:semicolon
DECL|member|login_orb
r_struct
id|sbp2_login_orb
op_star
id|login_orb
suffix:semicolon
DECL|member|login_orb_dma
id|dma_addr_t
id|login_orb_dma
suffix:semicolon
DECL|member|login_response
r_struct
id|sbp2_login_response
op_star
id|login_response
suffix:semicolon
DECL|member|login_response_dma
id|dma_addr_t
id|login_response_dma
suffix:semicolon
DECL|member|query_logins_orb
r_struct
id|sbp2_query_logins_orb
op_star
id|query_logins_orb
suffix:semicolon
DECL|member|query_logins_orb_dma
id|dma_addr_t
id|query_logins_orb_dma
suffix:semicolon
DECL|member|query_logins_response
r_struct
id|sbp2_query_logins_response
op_star
id|query_logins_response
suffix:semicolon
DECL|member|query_logins_response_dma
id|dma_addr_t
id|query_logins_response_dma
suffix:semicolon
DECL|member|reconnect_orb
r_struct
id|sbp2_reconnect_orb
op_star
id|reconnect_orb
suffix:semicolon
DECL|member|reconnect_orb_dma
id|dma_addr_t
id|reconnect_orb_dma
suffix:semicolon
DECL|member|logout_orb
r_struct
id|sbp2_logout_orb
op_star
id|logout_orb
suffix:semicolon
DECL|member|logout_orb_dma
id|dma_addr_t
id|logout_orb_dma
suffix:semicolon
DECL|member|status_block
r_struct
id|sbp2_status_block
id|status_block
suffix:semicolon
multiline_comment|/*&n;&t; * Stuff we need to know about the sbp2 device itself&n;&t; */
DECL|member|sbp2_management_agent_addr
id|u64
id|sbp2_management_agent_addr
suffix:semicolon
DECL|member|sbp2_command_block_agent_addr
id|u64
id|sbp2_command_block_agent_addr
suffix:semicolon
DECL|member|speed_code
id|u32
id|speed_code
suffix:semicolon
DECL|member|max_payload_size
id|u32
id|max_payload_size
suffix:semicolon
multiline_comment|/*&n;&t; * Values pulled from the device&squot;s unit directory&n;&t; */
DECL|member|ud
r_struct
id|unit_directory
op_star
id|ud
suffix:semicolon
DECL|member|sbp2_command_set_spec_id
id|u32
id|sbp2_command_set_spec_id
suffix:semicolon
DECL|member|sbp2_command_set
id|u32
id|sbp2_command_set
suffix:semicolon
DECL|member|sbp2_unit_characteristics
id|u32
id|sbp2_unit_characteristics
suffix:semicolon
DECL|member|sbp2_device_type_and_lun
id|u32
id|sbp2_device_type_and_lun
suffix:semicolon
DECL|member|sbp2_firmware_revision
id|u32
id|sbp2_firmware_revision
suffix:semicolon
multiline_comment|/* &n;&t; * Variable used for logins, reconnects, logouts, query logins&n;&t; */
DECL|member|sbp2_login_complete
id|atomic_t
id|sbp2_login_complete
suffix:semicolon
multiline_comment|/* &n;&t; * Pool of command orbs, so we can have more than overlapped command per id&n;&t; */
DECL|member|sbp2_command_orb_lock
id|spinlock_t
id|sbp2_command_orb_lock
suffix:semicolon
DECL|member|sbp2_command_orb_inuse
r_struct
id|list_head
id|sbp2_command_orb_inuse
suffix:semicolon
DECL|member|sbp2_command_orb_completed
r_struct
id|list_head
id|sbp2_command_orb_completed
suffix:semicolon
multiline_comment|/* Node entry, as retrieved from NodeMgr entries */
DECL|member|ne
r_struct
id|node_entry
op_star
id|ne
suffix:semicolon
multiline_comment|/* A backlink to our host_info */
DECL|member|hi
r_struct
id|sbp2scsi_host_info
op_star
id|hi
suffix:semicolon
multiline_comment|/* Device specific workarounds/brokeness */
DECL|member|workarounds
id|u32
id|workarounds
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Sbp2 host data structure (one per sbp2 host)&n; */
DECL|struct|sbp2scsi_host_info
r_struct
id|sbp2scsi_host_info
(brace
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
multiline_comment|/*&n;&t; * Spin locks for command processing&n;&t; */
DECL|member|sbp2_command_lock
id|spinlock_t
id|sbp2_command_lock
suffix:semicolon
multiline_comment|/*&n;&t; * This is the scsi host we register with the scsi mid level.&n;&t; * We keep a reference to it here, so we can unregister it&n;&t; * when the hpsb_host is removed.&n;&t; */
DECL|member|scsi_host
r_struct
id|Scsi_Host
op_star
id|scsi_host
suffix:semicolon
multiline_comment|/*&n;&t; * SCSI ID instance data (one for each sbp2 device instance possible)&n;&t; */
DECL|member|scsi_id
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
(braket
id|SBP2SCSI_MAX_SCSI_IDS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/*&n; * Various utility prototypes&n; */
r_static
r_int
id|sbp2util_create_command_orb_pool
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_void
id|sbp2util_remove_command_orb_pool
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_struct
id|sbp2_command_info
op_star
id|sbp2util_find_command_for_orb
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
id|dma_addr_t
id|orb
)paren
suffix:semicolon
r_static
r_struct
id|sbp2_command_info
op_star
id|sbp2util_find_command_for_SCpnt
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
r_void
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_struct
id|sbp2_command_info
op_star
id|sbp2util_allocate_command_orb
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
id|Scsi_Cmnd
op_star
id|Current_SCpnt
comma
r_void
(paren
op_star
id|Current_done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_void
id|sbp2util_mark_command_completed
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
r_struct
id|sbp2_command_info
op_star
id|command
)paren
suffix:semicolon
multiline_comment|/*&n; * IEEE-1394 core driver related prototypes&n; */
r_static
r_struct
id|sbp2scsi_host_info
op_star
id|sbp2_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_static
r_void
id|sbp2_remove_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
suffix:semicolon
r_static
r_int
id|sbp2_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|sbp2_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|sbp2_update
c_func
(paren
r_struct
id|unit_directory
op_star
id|ud
)paren
suffix:semicolon
r_static
r_int
id|sbp2_start_device
c_func
(paren
r_struct
id|sbp2scsi_host_info
op_star
id|hi
comma
r_struct
id|unit_directory
op_star
id|ud
)paren
suffix:semicolon
r_static
r_void
id|sbp2_remove_device
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_SBP2_PHYS_DMA
r_static
r_int
id|sbp2_handle_physdma_write
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|destid
comma
id|quadlet_t
op_star
id|data
comma
id|u64
id|addr
comma
r_int
r_int
id|length
comma
id|u16
id|flags
)paren
suffix:semicolon
r_static
r_int
id|sbp2_handle_physdma_read
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|data
comma
id|u64
id|addr
comma
r_int
r_int
id|length
comma
id|u16
id|flags
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * SBP-2 protocol related prototypes&n; */
r_static
r_int
id|sbp2_query_logins
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_login_device
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_reconnect_device
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_logout_device
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_handle_status_write
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|destid
comma
id|quadlet_t
op_star
id|data
comma
id|u64
id|addr
comma
r_int
r_int
id|length
comma
id|u16
id|flags
)paren
suffix:semicolon
r_static
r_int
id|sbp2_agent_reset
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
r_int
id|wait
)paren
suffix:semicolon
r_static
r_int
id|sbp2_create_command_orb
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
r_struct
id|sbp2_command_info
op_star
id|command
comma
id|unchar
op_star
id|scsi_cmd
comma
r_int
r_int
id|scsi_use_sg
comma
r_int
r_int
id|scsi_request_bufflen
comma
r_void
op_star
id|scsi_request_buffer
comma
r_int
r_char
id|scsi_dir
)paren
suffix:semicolon
r_static
r_int
id|sbp2_link_orb_command
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
r_struct
id|sbp2_command_info
op_star
id|command
)paren
suffix:semicolon
r_static
r_int
id|sbp2_send_command
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_int
r_int
id|sbp2_status_to_sense_data
c_func
(paren
id|unchar
op_star
id|sbp2_status
comma
id|unchar
op_star
id|sense_data
)paren
suffix:semicolon
r_static
r_void
id|sbp2_check_sbp2_command
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
id|unchar
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_void
id|sbp2_check_sbp2_response
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|sbp2_parse_unit_directory
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_set_busy_timeout
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
r_static
r_int
id|sbp2_max_speed_and_size
c_func
(paren
r_struct
id|scsi_id_instance_data
op_star
id|scsi_id
)paren
suffix:semicolon
macro_line|#endif /* SBP2_H */
eof
