multiline_comment|/**********************************************************************&n; * Defines for the Tachyon Fibre Channel Controller and the Interphase&n; * (i)chip TPI. &n; *********************************************************************/
macro_line|#ifndef _TACH_H
DECL|macro|_TACH_H
mdefine_line|#define _TACH_H
DECL|macro|MY_PAGE_SIZE
mdefine_line|#define MY_PAGE_SIZE       4096
DECL|macro|REPLICATE
mdefine_line|#define REPLICATE          0xFF
DECL|macro|MAX_NODES
mdefine_line|#define MAX_NODES          127
DECL|macro|BROADCAST
mdefine_line|#define BROADCAST          0xFFFFFF
DECL|macro|BROADCAST_ADDR
mdefine_line|#define BROADCAST_ADDR     0xFFFFFFFFFFFF
DECL|macro|LOGIN_COMPLETED
mdefine_line|#define LOGIN_COMPLETED     2
DECL|macro|LOGIN_ATTEMPTED
mdefine_line|#define LOGIN_ATTEMPTED     1
DECL|macro|LOGIN_NOT_ATTEMPTED
mdefine_line|#define LOGIN_NOT_ATTEMPTED 0
DECL|macro|TRUE
mdefine_line|#define TRUE                1
DECL|macro|FALSE
mdefine_line|#define FALSE               0
DECL|macro|TACHYON_LIMIT
mdefine_line|#define TACHYON_LIMIT       0x01EF
DECL|macro|TACHYON_OFFSET
mdefine_line|#define TACHYON_OFFSET      0x200
multiline_comment|/* Offsets to the (i) chip */
DECL|macro|ICHIP_HW_CONTROL_REG_OFF
mdefine_line|#define ICHIP_HW_CONTROL_REG_OFF    (0x080 - TACHYON_OFFSET)
DECL|macro|ICHIP_HW_STATUS_REG_OFF
mdefine_line|#define ICHIP_HW_STATUS_REG_OFF     (0x084 - TACHYON_OFFSET)
DECL|macro|ICHIP_HW_ADDR_MASK_REG_OFF
mdefine_line|#define ICHIP_HW_ADDR_MASK_REG_OFF  (0x090 - TACHYON_OFFSET)
multiline_comment|/* (i)chip Hardware Control Register defines */
DECL|macro|ICHIP_HCR_RESET
mdefine_line|#define ICHIP_HCR_RESET         0x01
DECL|macro|ICHIP_HCR_DERESET
mdefine_line|#define ICHIP_HCR_DERESET       0x0
DECL|macro|ICHIP_HCR_ENABLE_INTA
mdefine_line|#define ICHIP_HCR_ENABLE_INTA   0x0000003E 
DECL|macro|ICHIP_HCR_ENABLE_INTB
mdefine_line|#define ICHIP_HCR_ENABLE_INTB   0x003E0000
DECL|macro|ICHIP_HCR_IWDATA_FIFO
mdefine_line|#define ICHIP_HCR_IWDATA_FIFO   0x800000
multiline_comment|/* (i)chip Hardware Status Register defines */
DECL|macro|ICHIP_HSR_INT_LATCH
mdefine_line|#define ICHIP_HSR_INT_LATCH     0x02
multiline_comment|/* (i)chip Hardware Address Mask Register defines */
DECL|macro|ICHIP_HAMR_BYTE_SWAP_ADDR_TR
mdefine_line|#define ICHIP_HAMR_BYTE_SWAP_ADDR_TR    0x08
DECL|macro|ICHIP_HAMR_BYTE_SWAP_NO_ADDR_TR
mdefine_line|#define ICHIP_HAMR_BYTE_SWAP_NO_ADDR_TR 0x04
multiline_comment|/* NOVRAM defines */
DECL|macro|IPH5526_NOVRAM_SIZE
mdefine_line|#define IPH5526_NOVRAM_SIZE 64
multiline_comment|/* Offsets for the registers that correspond to the &n; * Qs on the Tachyon (As defined in the Tachyon Manual).&n; */
multiline_comment|/* Outbound Command Queue (OCQ).&n; */
DECL|macro|OCQ_BASE_REGISTER_OFFSET
mdefine_line|#define OCQ_BASE_REGISTER_OFFSET&t;0x000  
DECL|macro|OCQ_LENGTH_REGISTER_OFFSET
mdefine_line|#define OCQ_LENGTH_REGISTER_OFFSET&t;0x004
DECL|macro|OCQ_PRODUCER_REGISTER_OFFSET
mdefine_line|#define OCQ_PRODUCER_REGISTER_OFFSET&t;0x008  
DECL|macro|OCQ_CONSUMER_REGISTER_OFFSET
mdefine_line|#define OCQ_CONSUMER_REGISTER_OFFSET&t;0x00C 
multiline_comment|/* Inbound Message Queue (IMQ).&n; */
DECL|macro|IMQ_BASE_REGISTER_OFFSET
mdefine_line|#define IMQ_BASE_REGISTER_OFFSET&t;0x080
DECL|macro|IMQ_LENGTH_REGISTER_OFFSET
mdefine_line|#define IMQ_LENGTH_REGISTER_OFFSET&t;0x084
DECL|macro|IMQ_CONSUMER_REGISTER_OFFSET
mdefine_line|#define IMQ_CONSUMER_REGISTER_OFFSET&t;0x088
DECL|macro|IMQ_PRODUCER_REGISTER_OFFSET
mdefine_line|#define IMQ_PRODUCER_REGISTER_OFFSET&t;0x08C
multiline_comment|/* Multiframe Sequence Buffer Queue (MFSBQ)&n; */
DECL|macro|MFSBQ_BASE_REGISTER_OFFSET
mdefine_line|#define MFSBQ_BASE_REGISTER_OFFSET&t;0x0C0
DECL|macro|MFSBQ_LENGTH_REGISTER_OFFSET
mdefine_line|#define MFSBQ_LENGTH_REGISTER_OFFSET&t;0x0C4
DECL|macro|MFSBQ_PRODUCER_REGISTER_OFFSET
mdefine_line|#define MFSBQ_PRODUCER_REGISTER_OFFSET&t;0x0C8
DECL|macro|MFSBQ_CONSUMER_REGISTER_OFFSET
mdefine_line|#define MFSBQ_CONSUMER_REGISTER_OFFSET&t;0x0CC  
DECL|macro|MFS_LENGTH_REGISTER_OFFSET
mdefine_line|#define MFS_LENGTH_REGISTER_OFFSET&t;0x0D0
multiline_comment|/* Single Frame Sequence Buffer Queue (SFSBQ)&n; */
DECL|macro|SFSBQ_BASE_REGISTER_OFFSET
mdefine_line|#define SFSBQ_BASE_REGISTER_OFFSET&t;0x100
DECL|macro|SFSBQ_LENGTH_REGISTER_OFFSET
mdefine_line|#define SFSBQ_LENGTH_REGISTER_OFFSET&t;0x104
DECL|macro|SFSBQ_PRODUCER_REGISTER_OFFSET
mdefine_line|#define SFSBQ_PRODUCER_REGISTER_OFFSET&t;0x108
DECL|macro|SFSBQ_CONSUMER_REGISTER_OFFSET
mdefine_line|#define SFSBQ_CONSUMER_REGISTER_OFFSET&t;0x10C  
DECL|macro|SFS_LENGTH_REGISTER_OFFSET
mdefine_line|#define SFS_LENGTH_REGISTER_OFFSET&t;0x110
multiline_comment|/* SCSI Exchange State Table (SEST)&n; */
DECL|macro|SEST_BASE_REGISTER_OFFSET
mdefine_line|#define SEST_BASE_REGISTER_OFFSET&t;0x140
DECL|macro|SEST_LENGTH_REGISTER_OFFSET
mdefine_line|#define SEST_LENGTH_REGISTER_OFFSET&t;0x144
DECL|macro|SCSI_LENGTH_REGISTER_OFFSET
mdefine_line|#define SCSI_LENGTH_REGISTER_OFFSET&t;0x148
multiline_comment|/*  Length of the various Qs &n; */
DECL|macro|NO_OF_ENTRIES
mdefine_line|#define NO_OF_ENTRIES&t;&t;8
DECL|macro|OCQ_LENGTH
mdefine_line|#define OCQ_LENGTH&t;&t;(MY_PAGE_SIZE/32)
DECL|macro|IMQ_LENGTH
mdefine_line|#define IMQ_LENGTH&t;&t;(MY_PAGE_SIZE/32)
DECL|macro|MFSBQ_LENGTH
mdefine_line|#define MFSBQ_LENGTH&t;&t;8
DECL|macro|SFSBQ_LENGTH
mdefine_line|#define SFSBQ_LENGTH&t;&t;8
DECL|macro|SEST_LENGTH
mdefine_line|#define SEST_LENGTH&t;&t;MY_PAGE_SIZE
multiline_comment|/* Size of the various buffers.&n; */
DECL|macro|TACH_FRAME_SIZE
mdefine_line|#define TACH_FRAME_SIZE         2048
DECL|macro|MFS_BUFFER_SIZE
mdefine_line|#define MFS_BUFFER_SIZE         TACH_FRAME_SIZE
DECL|macro|SFS_BUFFER_SIZE
mdefine_line|#define SFS_BUFFER_SIZE         (TACH_FRAME_SIZE + TACHYON_HEADER_LEN)
DECL|macro|SEST_BUFFER_SIZE
mdefine_line|#define SEST_BUFFER_SIZE        512
DECL|macro|TACH_HEADER_SIZE
mdefine_line|#define TACH_HEADER_SIZE        64
DECL|macro|NO_OF_TACH_HEADERS
mdefine_line|#define NO_OF_TACH_HEADERS      ((MY_PAGE_SIZE)/TACH_HEADER_SIZE)
DECL|macro|NO_OF_FCP_CMNDS
mdefine_line|#define NO_OF_FCP_CMNDS         (MY_PAGE_SIZE/32)
DECL|macro|SDB_SIZE
mdefine_line|#define SDB_SIZE                2048
DECL|macro|NO_OF_SDB_ENTRIES
mdefine_line|#define NO_OF_SDB_ENTRIES       ((32*MY_PAGE_SIZE)/SDB_SIZE)
multiline_comment|/* Offsets to the other Tachyon registers.&n; * (As defined in the Tachyon manual)&n; */
DECL|macro|TACHYON_CONFIG_REGISTER_OFFSET
mdefine_line|#define TACHYON_CONFIG_REGISTER_OFFSET          0x184
DECL|macro|TACHYON_CONTROL_REGISTER_OFFSET
mdefine_line|#define TACHYON_CONTROL_REGISTER_OFFSET         0x188
DECL|macro|TACHYON_STATUS_REGISTER_OFFSET
mdefine_line|#define TACHYON_STATUS_REGISTER_OFFSET          0x18C
DECL|macro|TACHYON_FLUSH_SEST_REGISTER_OFFSET
mdefine_line|#define TACHYON_FLUSH_SEST_REGISTER_OFFSET      0x190
multiline_comment|/* Defines for the Tachyon Configuration register.&n; */
DECL|macro|SCSI_ENABLE
mdefine_line|#define SCSI_ENABLE             0x40000000     
DECL|macro|WRITE_STREAM_SIZE
mdefine_line|#define WRITE_STREAM_SIZE       0x800&t;/* size = 16 */         
DECL|macro|READ_STREAM_SIZE
mdefine_line|#define READ_STREAM_SIZE        0x300&t;/* size = 64 */      
DECL|macro|PARITY_EVEN
mdefine_line|#define PARITY_EVEN             0x2         
DECL|macro|OOO_REASSEMBLY_DISABLE
mdefine_line|#define OOO_REASSEMBLY_DISABLE  0x40
multiline_comment|/* Defines for the Tachyon Control register.&n; */
DECL|macro|SOFTWARE_RESET
mdefine_line|#define SOFTWARE_RESET&t;0x80000000
DECL|macro|OCQ_RESET
mdefine_line|#define OCQ_RESET&t;0x4
DECL|macro|ERROR_RELEASE
mdefine_line|#define ERROR_RELEASE&t;0x2
multiline_comment|/* Defines for the Tachyon Status register.&n; */
DECL|macro|RECEIVE_FIFO_EMPTY
mdefine_line|#define RECEIVE_FIFO_EMPTY      0x10
DECL|macro|OSM_FROZEN
mdefine_line|#define OSM_FROZEN              0x1
DECL|macro|OCQ_RESET_STATUS
mdefine_line|#define OCQ_RESET_STATUS        0x20
DECL|macro|SCSI_FREEZE_STATUS
mdefine_line|#define SCSI_FREEZE_STATUS      0x40
multiline_comment|/* Offsets to the Frame Manager registers.&n; */
DECL|macro|FMGR_CONFIG_REGISTER_OFFSET
mdefine_line|#define FMGR_CONFIG_REGISTER_OFFSET 0x1C0
DECL|macro|FMGR_CONTROL_REGISTER_OFFSET
mdefine_line|#define FMGR_CONTROL_REGISTER_OFFSET 0x1C4
DECL|macro|FMGR_STATUS_REGISTER_OFFSET
mdefine_line|#define FMGR_STATUS_REGISTER_OFFSET 0x1C8
DECL|macro|FMGR_TIMER_REGISTER_OFFSET
mdefine_line|#define FMGR_TIMER_REGISTER_OFFSET 0x1CC
DECL|macro|FMGR_WWN_HI_REGISTER_OFFSET
mdefine_line|#define FMGR_WWN_HI_REGISTER_OFFSET 0x1E0
DECL|macro|FMGR_WWN_LO_REGISTER_OFFSET
mdefine_line|#define FMGR_WWN_LO_REGISTER_OFFSET 0x1E4
DECL|macro|FMGR_RCVD_ALPA_REGISTER_OFFSET
mdefine_line|#define FMGR_RCVD_ALPA_REGISTER_OFFSET 0x1E8
multiline_comment|/* Defines for the Frame Manager Configuration register.&n; */
DECL|macro|BB_CREDIT
mdefine_line|#define BB_CREDIT                    0x10000
DECL|macro|NPORT
mdefine_line|#define NPORT                        0x8000 
DECL|macro|LOOP_INIT_FABRIC_ADDRESS
mdefine_line|#define LOOP_INIT_FABRIC_ADDRESS     0x400  
DECL|macro|LOOP_INIT_PREVIOUS_ADDRESS
mdefine_line|#define LOOP_INIT_PREVIOUS_ADDRESS   0x200  
DECL|macro|LOOP_INIT_SOFT_ADDRESS
mdefine_line|#define LOOP_INIT_SOFT_ADDRESS       0x80  
multiline_comment|/* Defines for the Frame Manager Control register.&n; */
DECL|macro|HOST_CONTROL
mdefine_line|#define HOST_CONTROL                 0x02   
DECL|macro|EXIT_HOST_CONTROL
mdefine_line|#define EXIT_HOST_CONTROL            0x03  
DECL|macro|OFFLINE
mdefine_line|#define OFFLINE                      0x05 
DECL|macro|INITIALIZE
mdefine_line|#define INITIALIZE                   0x06 
DECL|macro|CLEAR_LF
mdefine_line|#define CLEAR_LF                     0x07
multiline_comment|/* Defines for the Frame Manager Status register.&n; */
DECL|macro|LOOP_UP
mdefine_line|#define LOOP_UP                 0x80000000
DECL|macro|TRANSMIT_PARITY_ERROR
mdefine_line|#define TRANSMIT_PARITY_ERROR   0x40000000
DECL|macro|NON_PARTICIPATING
mdefine_line|#define NON_PARTICIPATING       0x20000000
DECL|macro|OUT_OF_SYNC
mdefine_line|#define OUT_OF_SYNC             0x02000000
DECL|macro|LOSS_OF_SIGNAL
mdefine_line|#define LOSS_OF_SIGNAL          0x01000000
DECL|macro|NOS_OLS_RECEIVED
mdefine_line|#define NOS_OLS_RECEIVED        0x00080000
DECL|macro|LOOP_STATE_TIMEOUT
mdefine_line|#define LOOP_STATE_TIMEOUT      0x00040000
DECL|macro|LIPF_RECEIVED
mdefine_line|#define LIPF_RECEIVED           0x00020000
DECL|macro|BAD_ALPA
mdefine_line|#define BAD_ALPA                0x00010000
DECL|macro|LINK_FAILURE
mdefine_line|#define LINK_FAILURE            0x00001000
DECL|macro|ELASTIC_STORE_ERROR
mdefine_line|#define ELASTIC_STORE_ERROR     0x00000400
DECL|macro|LINK_UP
mdefine_line|#define LINK_UP                 0x00000200
DECL|macro|LINK_DOWN
mdefine_line|#define LINK_DOWN               0x00000100
DECL|macro|ARBITRATING
mdefine_line|#define ARBITRATING             0x00000010
DECL|macro|ARB_WON
mdefine_line|#define ARB_WON                 0x00000020
DECL|macro|OPEN
mdefine_line|#define OPEN                    0x00000030
DECL|macro|OPENED
mdefine_line|#define OPENED                  0x00000040
DECL|macro|TX_CLS
mdefine_line|#define TX_CLS                  0x00000050
DECL|macro|RX_CLS
mdefine_line|#define RX_CLS                  0x00000060
DECL|macro|TRANSFER
mdefine_line|#define TRANSFER                0x00000070
DECL|macro|INITIALIZING
mdefine_line|#define INITIALIZING            0x00000080
DECL|macro|LOOP_FAIL
mdefine_line|#define LOOP_FAIL               0x000000D0
DECL|macro|OLD_PORT
mdefine_line|#define OLD_PORT                0x000000F0
DECL|macro|PORT_STATE_ACTIVE
mdefine_line|#define PORT_STATE_ACTIVE       0x0000000F
DECL|macro|PORT_STATE_OFFLINE
mdefine_line|#define PORT_STATE_OFFLINE      0x00000000
DECL|macro|PORT_STATE_LF1
mdefine_line|#define PORT_STATE_LF1          0x00000009
DECL|macro|PORT_STATE_LF2
mdefine_line|#define PORT_STATE_LF2          0x0000000A
multiline_comment|/* Completion Message Types &n; * (defined in P.177 of the Tachyon manual)&n; */
DECL|macro|OUTBOUND_COMPLETION
mdefine_line|#define OUTBOUND_COMPLETION             0x000
DECL|macro|OUTBOUND_COMPLETION_I
mdefine_line|#define OUTBOUND_COMPLETION_I           0x100
DECL|macro|OUT_HI_PRI_COMPLETION
mdefine_line|#define OUT_HI_PRI_COMPLETION           0x001
DECL|macro|OUT_HI_PRI_COMPLETION_I
mdefine_line|#define OUT_HI_PRI_COMPLETION_I         0x101
DECL|macro|INBOUND_MFS_COMPLETION
mdefine_line|#define INBOUND_MFS_COMPLETION          0x102
DECL|macro|INBOUND_OOO_COMPLETION
mdefine_line|#define INBOUND_OOO_COMPLETION          0x003
DECL|macro|INBOUND_SFS_COMPLETION
mdefine_line|#define INBOUND_SFS_COMPLETION          0x104
DECL|macro|INBOUND_C1_TIMEOUT
mdefine_line|#define INBOUND_C1_TIMEOUT              0x105
DECL|macro|INBOUND_UNKNOWN_FRAME_I
mdefine_line|#define INBOUND_UNKNOWN_FRAME_I         0x106
DECL|macro|INBOUND_BUSIED_FRAME
mdefine_line|#define INBOUND_BUSIED_FRAME            0x006
DECL|macro|SFS_BUF_WARN
mdefine_line|#define SFS_BUF_WARN                    0x107
DECL|macro|MFS_BUF_WARN
mdefine_line|#define MFS_BUF_WARN                    0x108
DECL|macro|IMQ_BUF_WARN
mdefine_line|#define IMQ_BUF_WARN                    0x109
DECL|macro|FRAME_MGR_INTERRUPT
mdefine_line|#define FRAME_MGR_INTERRUPT             0x10A
DECL|macro|READ_STATUS
mdefine_line|#define READ_STATUS                     0x10B
DECL|macro|INBOUND_SCSI_DATA_COMPLETION
mdefine_line|#define INBOUND_SCSI_DATA_COMPLETION    0x10C
DECL|macro|INBOUND_SCSI_COMMAND
mdefine_line|#define INBOUND_SCSI_COMMAND            0x10D
DECL|macro|BAD_SCSI_FRAME
mdefine_line|#define BAD_SCSI_FRAME                  0x10E
DECL|macro|INB_SCSI_STATUS_COMPLETION
mdefine_line|#define INB_SCSI_STATUS_COMPLETION      0x10F
multiline_comment|/* One of the things that we care about when we receive an&n; * Outbound Completion Message (OCM).&n; */
DECL|macro|OCM_TIMEOUT_OR_BAD_ALPA
mdefine_line|#define OCM_TIMEOUT_OR_BAD_ALPA         0x0800
multiline_comment|/* Defines for the Tachyon Header structure.&n; */
DECL|macro|SOFI3
mdefine_line|#define SOFI3                0x70
DECL|macro|SOFN3
mdefine_line|#define SOFN3                0xB0
DECL|macro|EOFN
mdefine_line|#define EOFN                 0x5
multiline_comment|/* R_CTL */
DECL|macro|FC4_DEVICE_DATA
mdefine_line|#define FC4_DEVICE_DATA      0
DECL|macro|EXTENDED_LINK_DATA
mdefine_line|#define EXTENDED_LINK_DATA   0x20000000
DECL|macro|FC4_LINK_DATA
mdefine_line|#define FC4_LINK_DATA        0x30000000
DECL|macro|BASIC_LINK_DATA
mdefine_line|#define BASIC_LINK_DATA      0x80000000
DECL|macro|LINK_CONTROL
mdefine_line|#define LINK_CONTROL         0xC0000000
DECL|macro|SOLICITED_DATA
mdefine_line|#define SOLICITED_DATA       0x1000000
DECL|macro|UNSOLICITED_CONTROL
mdefine_line|#define UNSOLICITED_CONTROL  0x2000000
DECL|macro|SOLICITED_CONTROL
mdefine_line|#define SOLICITED_CONTROL    0x3000000
DECL|macro|UNSOLICITED_DATA
mdefine_line|#define UNSOLICITED_DATA     0x4000000
DECL|macro|DATA_DESCRIPTOR
mdefine_line|#define DATA_DESCRIPTOR      0x5000000
DECL|macro|UNSOLICITED_COMMAND
mdefine_line|#define UNSOLICITED_COMMAND  0x6000000
DECL|macro|RCTL_ELS_UCTL
mdefine_line|#define RCTL_ELS_UCTL          0x22000000
DECL|macro|RCTL_ELS_SCTL
mdefine_line|#define RCTL_ELS_SCTL          0x23000000
DECL|macro|RCTL_BASIC_ABTS
mdefine_line|#define RCTL_BASIC_ABTS        0x81000000
DECL|macro|RCTL_BASIC_ACC
mdefine_line|#define RCTL_BASIC_ACC         0x84000000
DECL|macro|RCTL_BASIC_RJT
mdefine_line|#define RCTL_BASIC_RJT         0x85000000
multiline_comment|/* TYPE */
DECL|macro|TYPE_BLS
mdefine_line|#define TYPE_BLS               0x00000000
DECL|macro|TYPE_ELS
mdefine_line|#define TYPE_ELS               0x01000000
DECL|macro|TYPE_FC_SERVICES
mdefine_line|#define TYPE_FC_SERVICES       0x20000000
DECL|macro|TYPE_LLC_SNAP
mdefine_line|#define TYPE_LLC_SNAP          0x05000000
DECL|macro|TYPE_FCP
mdefine_line|#define TYPE_FCP               0x08000000
multiline_comment|/* F_CTL */
DECL|macro|EXCHANGE_RESPONDER
mdefine_line|#define EXCHANGE_RESPONDER     0x800000
DECL|macro|SEQUENCE_RESPONDER
mdefine_line|#define SEQUENCE_RESPONDER     0x400000
DECL|macro|FIRST_SEQUENCE
mdefine_line|#define FIRST_SEQUENCE         0x200000
DECL|macro|LAST_SEQUENCE
mdefine_line|#define LAST_SEQUENCE          0x100000
DECL|macro|SEQUENCE_INITIATIVE
mdefine_line|#define SEQUENCE_INITIATIVE    0x10000
DECL|macro|RELATIVE_OFF_PRESENT
mdefine_line|#define RELATIVE_OFF_PRESENT   0x8
DECL|macro|END_SEQUENCE
mdefine_line|#define END_SEQUENCE           0x80000
DECL|macro|TACHYON_HEADER_LEN
mdefine_line|#define TACHYON_HEADER_LEN     32
DECL|macro|NW_HEADER_LEN
mdefine_line|#define NW_HEADER_LEN          16
multiline_comment|/* Defines for the Outbound Descriptor Block (ODB).&n; */
DECL|macro|ODB_CLASS_3
mdefine_line|#define ODB_CLASS_3          0xC000
DECL|macro|ODB_NO_COMP
mdefine_line|#define ODB_NO_COMP          0x400
DECL|macro|ODB_NO_INT
mdefine_line|#define ODB_NO_INT           0x200
DECL|macro|ODB_EE_CREDIT
mdefine_line|#define ODB_EE_CREDIT        0xF
multiline_comment|/* Defines for the Extended Descriptor Block (EDB).&n; */
DECL|macro|EDB_LEN
mdefine_line|#define EDB_LEN              ((32*MY_PAGE_SIZE)/8) 
DECL|macro|EDB_END
mdefine_line|#define EDB_END              0x8000
DECL|macro|EDB_FREE
mdefine_line|#define EDB_FREE             0
DECL|macro|EDB_BUSY
mdefine_line|#define EDB_BUSY             1
multiline_comment|/* Command Codes */
DECL|macro|ELS_LS_RJT
mdefine_line|#define ELS_LS_RJT          0x01000000
DECL|macro|ELS_ACC
mdefine_line|#define ELS_ACC             0x02000000
DECL|macro|ELS_PLOGI
mdefine_line|#define ELS_PLOGI           0x03000000
DECL|macro|ELS_FLOGI
mdefine_line|#define ELS_FLOGI           0x04000000
DECL|macro|ELS_LOGO
mdefine_line|#define ELS_LOGO            0x05000000
DECL|macro|ELS_TPRLO
mdefine_line|#define ELS_TPRLO           0x24000000
DECL|macro|ELS_ADISC
mdefine_line|#define ELS_ADISC           0x52000000
DECL|macro|ELS_PDISC
mdefine_line|#define ELS_PDISC           0x50000000
DECL|macro|ELS_PRLI
mdefine_line|#define ELS_PRLI            0x20000000 
DECL|macro|ELS_PRLO
mdefine_line|#define ELS_PRLO            0x21000000
DECL|macro|ELS_SCR
mdefine_line|#define ELS_SCR             0x62000000
DECL|macro|ELS_RSCN
mdefine_line|#define ELS_RSCN            0x61000000
DECL|macro|ELS_FARP_REQ
mdefine_line|#define ELS_FARP_REQ        0x54000000
DECL|macro|ELS_ABTX
mdefine_line|#define ELS_ABTX            0x06000000
DECL|macro|ELS_ADVC
mdefine_line|#define ELS_ADVC            0x0D000000
DECL|macro|ELS_ECHO
mdefine_line|#define ELS_ECHO            0x10000000
DECL|macro|ELS_ESTC
mdefine_line|#define ELS_ESTC            0x0C000000
DECL|macro|ELS_ESTS
mdefine_line|#define ELS_ESTS            0x0B000000
DECL|macro|ELS_RCS
mdefine_line|#define ELS_RCS             0x07000000
DECL|macro|ELS_RES
mdefine_line|#define ELS_RES             0x08000000
DECL|macro|ELS_RLS
mdefine_line|#define ELS_RLS             0x0F000000
DECL|macro|ELS_RRQ
mdefine_line|#define ELS_RRQ             0x12000000
DECL|macro|ELS_RSS
mdefine_line|#define ELS_RSS             0x09000000
DECL|macro|ELS_RTV
mdefine_line|#define ELS_RTV             0x0E000000
DECL|macro|ELS_RSI
mdefine_line|#define ELS_RSI             0x0A000000
DECL|macro|ELS_TEST
mdefine_line|#define ELS_TEST            0x11000000
DECL|macro|ELS_RNC
mdefine_line|#define ELS_RNC             0x53000000
DECL|macro|ELS_RVCS
mdefine_line|#define ELS_RVCS            0x41000000
DECL|macro|ELS_TPLS
mdefine_line|#define ELS_TPLS            0x23000000
DECL|macro|ELS_GAID
mdefine_line|#define ELS_GAID            0x30000000
DECL|macro|ELS_FACT
mdefine_line|#define ELS_FACT            0x31000000
DECL|macro|ELS_FAN
mdefine_line|#define ELS_FAN             0x60000000
DECL|macro|ELS_FDACT
mdefine_line|#define ELS_FDACT           0x32000000
DECL|macro|ELS_NACT
mdefine_line|#define ELS_NACT            0x33000000
DECL|macro|ELS_NDACT
mdefine_line|#define ELS_NDACT           0x34000000
DECL|macro|ELS_QoSR
mdefine_line|#define ELS_QoSR            0x40000000
DECL|macro|ELS_FDISC
mdefine_line|#define ELS_FDISC           0x51000000
DECL|macro|ELS_NS_PLOGI
mdefine_line|#define ELS_NS_PLOGI        0x03FFFFFC 
multiline_comment|/* LS_RJT reason codes.&n; */
DECL|macro|INV_LS_CMND_CODE
mdefine_line|#define INV_LS_CMND_CODE                0x0001
DECL|macro|LOGICAL_ERR
mdefine_line|#define LOGICAL_ERR                     0x0003
DECL|macro|LOGICAL_BUSY
mdefine_line|#define LOGICAL_BUSY                    0x0005
DECL|macro|PROTOCOL_ERR
mdefine_line|#define PROTOCOL_ERR                    0x0007
DECL|macro|UNABLE_TO_PERFORM
mdefine_line|#define UNABLE_TO_PERFORM               0x0009
DECL|macro|CMND_NOT_SUPP
mdefine_line|#define CMND_NOT_SUPP                   0x000B
multiline_comment|/* LS_RJT explanation codes.&n; */
DECL|macro|NO_EXPLN
mdefine_line|#define NO_EXPLN                        0x0000
DECL|macro|RECV_FIELD_SIZE
mdefine_line|#define RECV_FIELD_SIZE                 0x0700
DECL|macro|CONC_SEQ
mdefine_line|#define CONC_SEQ                        0x0900
DECL|macro|REQ_NOT_SUPPORTED
mdefine_line|#define REQ_NOT_SUPPORTED               0x2C00
DECL|macro|INV_PAYLOAD_LEN
mdefine_line|#define INV_PAYLOAD_LEN                 0x2D00
multiline_comment|/* Payload Length defines. &n; */
DECL|macro|PLOGI_LEN
mdefine_line|#define PLOGI_LEN&t;&t;&t;&t;116
DECL|macro|CONCURRENT_SEQUENCES
mdefine_line|#define CONCURRENT_SEQUENCES 0x01
DECL|macro|RO_INFO_CATEGORY
mdefine_line|#define RO_INFO_CATEGORY     0xFE
DECL|macro|E_D_TOV
mdefine_line|#define E_D_TOV              0x07D0 /* 2 Secs */
DECL|macro|AL_TIME
mdefine_line|#define AL_TIME&t;             0x0010 /* ~15 msec */
DECL|macro|TOV_VALUES
mdefine_line|#define TOV_VALUES           (AL_TIME &lt;&lt; 16) | E_D_TOV
DECL|macro|RT_TOV
mdefine_line|#define RT_TOV               0x64   /* 100 msec */
DECL|macro|PTP_TOV_VALUES
mdefine_line|#define PTP_TOV_VALUES       (RT_TOV &lt;&lt; 16) | E_D_TOV
DECL|macro|SERVICE_VALID
mdefine_line|#define SERVICE_VALID        0x8000
DECL|macro|SEQUENCE_DELIVERY
mdefine_line|#define SEQUENCE_DELIVERY&t; 0x0800
DECL|macro|CLASS3_CONCURRENT_SEQUENCE
mdefine_line|#define CLASS3_CONCURRENT_SEQUENCE    0x01
DECL|macro|CLASS3_OPEN_SEQUENCE
mdefine_line|#define CLASS3_OPEN_SEQUENCE          0x01
multiline_comment|/* These are retrieved from the NOVRAM.&n; */
DECL|macro|WORLD_WIDE_NAME_LOW
mdefine_line|#define WORLD_WIDE_NAME_LOW     fi-&gt;g.my_port_name_low
DECL|macro|WORLD_WIDE_NAME_HIGH
mdefine_line|#define WORLD_WIDE_NAME_HIGH    fi-&gt;g.my_port_name_high
DECL|macro|N_PORT_NAME_HIGH
mdefine_line|#define N_PORT_NAME_HIGH        fi-&gt;g.my_port_name_high
DECL|macro|N_PORT_NAME_LOW
mdefine_line|#define N_PORT_NAME_LOW         fi-&gt;g.my_port_name_low
DECL|macro|NODE_NAME_HIGH
mdefine_line|#define NODE_NAME_HIGH          fi-&gt;g.my_node_name_high
DECL|macro|NODE_NAME_LOW
mdefine_line|#define NODE_NAME_LOW           fi-&gt;g.my_node_name_low
DECL|macro|PORT_NAME_LEN
mdefine_line|#define PORT_NAME_LEN           8
DECL|macro|NODE_NAME_LEN
mdefine_line|#define NODE_NAME_LEN           8
DECL|macro|PH_VERSION
mdefine_line|#define PH_VERSION        0x0909
DECL|macro|LOOP_BB_CREDIT
mdefine_line|#define LOOP_BB_CREDIT  0x00
DECL|macro|PT2PT_BB_CREDIT
mdefine_line|#define PT2PT_BB_CREDIT 0x01
DECL|macro|FLOGI_C_F
mdefine_line|#define FLOGI_C_F       0x0800 /* Alternate BB_Credit Mgmnt */ 
DECL|macro|PLOGI_C_F
mdefine_line|#define PLOGI_C_F       0x8800 /* Continuously Increasing + Alternate BB_Credit Management */
multiline_comment|/* Fabric defines */
DECL|macro|DIRECTORY_SERVER
mdefine_line|#define DIRECTORY_SERVER        0xFFFFFC
DECL|macro|FABRIC_CONTROLLER
mdefine_line|#define FABRIC_CONTROLLER       0xFFFFFD
DECL|macro|F_PORT
mdefine_line|#define F_PORT                  0xFFFFFE
DECL|macro|FLOGI_DID
mdefine_line|#define FLOGI_DID&t;&t;&t;&t;0xFFFE
DECL|macro|NS_PLOGI_DID
mdefine_line|#define NS_PLOGI_DID&t;&t;&t;0xFFFC
multiline_comment|/* Fibre Channel Services defines */
DECL|macro|FCS_RFC_4
mdefine_line|#define FCS_RFC_4           0x02170000
DECL|macro|FCS_GP_ID4
mdefine_line|#define FCS_GP_ID4          0x01A10000
DECL|macro|FCS_ACC
mdefine_line|#define FCS_ACC             0x8002
DECL|macro|FCS_REJECT
mdefine_line|#define FCS_REJECT          0x8001
multiline_comment|/* CT Header defines */
DECL|macro|FC_CT_REV
mdefine_line|#define FC_CT_REV               0x01000000
DECL|macro|DIRECTORY_SERVER_APP
mdefine_line|#define DIRECTORY_SERVER_APP    0xFC
DECL|macro|NAME_SERVICE
mdefine_line|#define NAME_SERVICE            0x02
multiline_comment|/* Port Type defines */
DECL|macro|PORT_TYPE_IP
mdefine_line|#define PORT_TYPE_IP            0x05000000
DECL|macro|PORT_TYPE_NX_PORTS
mdefine_line|#define PORT_TYPE_NX_PORTS      0x7F000000
multiline_comment|/* SCR defines */
DECL|macro|FABRIC_DETECTED_REG
mdefine_line|#define FABRIC_DETECTED_REG&t;&t;0x00000001
DECL|macro|N_PORT_DETECTED_REG
mdefine_line|#define N_PORT_DETECTED_REG&t;&t;0x00000002
DECL|macro|FULL_REGISTRATION
mdefine_line|#define FULL_REGISTRATION&t;&t;0x00000003
DECL|macro|CLEAR_REGISTRATION
mdefine_line|#define CLEAR_REGISTRATION&t;&t;0x000000FF
multiline_comment|/* Command structure has only one byte to address targets &n; */
DECL|macro|MAX_SCSI_TARGETS
mdefine_line|#define MAX_SCSI_TARGETS&t;&t;0xFF 
DECL|macro|FC_SCSI_READ
mdefine_line|#define FC_SCSI_READ                    0x80
DECL|macro|FC_SCSI_WRITE
mdefine_line|#define FC_SCSI_WRITE                   0x81
DECL|macro|FC_ELS
mdefine_line|#define FC_ELS                          0x01
DECL|macro|FC_BLS
mdefine_line|#define FC_BLS                          0x00
DECL|macro|FC_IP
mdefine_line|#define FC_IP                           0x05
DECL|macro|FC_BROADCAST
mdefine_line|#define FC_BROADCAST                    0xFF
multiline_comment|/* SEST defines.&n; */
DECL|macro|SEST_V
mdefine_line|#define SEST_V                          0x80000000 /* V = 1 */
DECL|macro|INB_SEST_VED
mdefine_line|#define INB_SEST_VED                    0xA0000000 /* V = 1, D = 1 */
DECL|macro|SEST_INV
mdefine_line|#define SEST_INV                        0x7FFFFFFF 
DECL|macro|OUTB_SEST_VED
mdefine_line|#define OUTB_SEST_VED                   0x80000000 /* V = 1 */
DECL|macro|INV_SEQ_LEN
mdefine_line|#define INV_SEQ_LEN                     0xFFFFFFFF
DECL|macro|OUTB_SEST_LINK
mdefine_line|#define OUTB_SEST_LINK                  0xFFFF
multiline_comment|/* PRLI defines. &n; */
DECL|macro|PAGE_LEN
mdefine_line|#define PAGE_LEN                0x100000 /* 3rd byte - 0x10 */
DECL|macro|PRLI_LEN
mdefine_line|#define PRLI_LEN                0x0014 /* 20 bytes */
DECL|macro|FCP_TYPE_CODE
mdefine_line|#define FCP_TYPE_CODE           0x0800 /* FCP-SCSI */
DECL|macro|IMAGE_PAIR
mdefine_line|#define IMAGE_PAIR              0x2000 /* establish image pair */
DECL|macro|INITIATOR_FUNC
mdefine_line|#define INITIATOR_FUNC          0x00000020
DECL|macro|TARGET_FUNC
mdefine_line|#define TARGET_FUNC             0x00000010
DECL|macro|READ_XFER_RDY_DISABLED
mdefine_line|#define READ_XFER_RDY_DISABLED  0x00000002
DECL|macro|NODE_PROCESS_LOGGED_IN
mdefine_line|#define NODE_PROCESS_LOGGED_IN  0x3
DECL|macro|NODE_NOT_PRESENT
mdefine_line|#define NODE_NOT_PRESENT        0x2
DECL|macro|NODE_LOGGED_IN
mdefine_line|#define NODE_LOGGED_IN          0x1
DECL|macro|NODE_LOGGED_OUT
mdefine_line|#define NODE_LOGGED_OUT         0x0
multiline_comment|/* Defines to determine what should be returned when a SCSI frame&n; * times out.&n; */
DECL|macro|FC_SCSI_BAD_TARGET
mdefine_line|#define FC_SCSI_BAD_TARGET&t;&t;0xFFFE0000
multiline_comment|/* RSCN Address formats */
DECL|macro|PORT_ADDRESS_FORMAT
mdefine_line|#define PORT_ADDRESS_FORMAT             0x00
DECL|macro|AREA_ADDRESS_FORMAT
mdefine_line|#define AREA_ADDRESS_FORMAT             0x01
DECL|macro|DOMAIN_ADDRESS_FORMAT
mdefine_line|#define DOMAIN_ADDRESS_FORMAT           0x02
multiline_comment|/* Defines used to determine whether a frame transmission should&n; * be indicated by an interrupt or not.&n; */
DECL|macro|NO_COMP_AND_INT
mdefine_line|#define NO_COMP_AND_INT&t;&t;&t;0
DECL|macro|INT_AND_COMP_REQ
mdefine_line|#define INT_AND_COMP_REQ&t;&t;1
DECL|macro|NO_INT_COMP_REQ
mdefine_line|#define NO_INT_COMP_REQ&t;&t;&t;2
multiline_comment|/* Other junk...&n; */
DECL|macro|SDB_FREE
mdefine_line|#define SDB_FREE             0
DECL|macro|SDB_BUSY
mdefine_line|#define SDB_BUSY             1
DECL|macro|MAX_PENDING_FRAMES
mdefine_line|#define MAX_PENDING_FRAMES   15
DECL|macro|RX_ID_FIRST_SEQUENCE
mdefine_line|#define RX_ID_FIRST_SEQUENCE 0xFFFF
DECL|macro|OX_ID_FIRST_SEQUENCE
mdefine_line|#define OX_ID_FIRST_SEQUENCE 0xFFFF
DECL|macro|NOT_SCSI_XID
mdefine_line|#define NOT_SCSI_XID            0x8000
DECL|macro|MAX_SCSI_XID
mdefine_line|#define MAX_SCSI_XID            0x0FFF /* X_IDs are from 0-4095 */
DECL|macro|SCSI_READ_BIT
mdefine_line|#define SCSI_READ_BIT           0x4000 
DECL|macro|MAX_SCSI_OXID
mdefine_line|#define MAX_SCSI_OXID           0x4FFF
DECL|macro|OXID_AVAILABLE
mdefine_line|#define OXID_AVAILABLE          0
DECL|macro|OXID_INUSE
mdefine_line|#define OXID_INUSE              1
DECL|macro|MAX_SEQ_ID
mdefine_line|#define MAX_SEQ_ID              0xFF
DECL|macro|INITIATOR
mdefine_line|#define INITIATOR             2
DECL|macro|TARGET
mdefine_line|#define TARGET                1
DECL|macro|DELETE_ENTRY
mdefine_line|#define DELETE_ENTRY          1
DECL|macro|ADD_ENTRY
mdefine_line|#define ADD_ENTRY             2
macro_line|#endif /* _TACH_H */
eof
