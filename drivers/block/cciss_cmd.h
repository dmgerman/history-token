macro_line|#ifndef CCISS_CMD_H
DECL|macro|CCISS_CMD_H
mdefine_line|#define CCISS_CMD_H
singleline_comment|//###########################################################################
singleline_comment|//DEFINES
singleline_comment|//###########################################################################
DECL|macro|CISS_VERSION
mdefine_line|#define CISS_VERSION &quot;1.00&quot;
singleline_comment|//general boundary defintions
DECL|macro|SENSEINFOBYTES
mdefine_line|#define SENSEINFOBYTES          32
singleline_comment|//note that this value may vary between host implementations
DECL|macro|MAXSGENTRIES
mdefine_line|#define MAXSGENTRIES            31
DECL|macro|MAXREPLYQS
mdefine_line|#define MAXREPLYQS              256
singleline_comment|//Command Status value
DECL|macro|CMD_SUCCESS
mdefine_line|#define CMD_SUCCESS             0x0000
DECL|macro|CMD_TARGET_STATUS
mdefine_line|#define CMD_TARGET_STATUS       0x0001
DECL|macro|CMD_DATA_UNDERRUN
mdefine_line|#define CMD_DATA_UNDERRUN       0x0002
DECL|macro|CMD_DATA_OVERRUN
mdefine_line|#define CMD_DATA_OVERRUN        0x0003
DECL|macro|CMD_INVALID
mdefine_line|#define CMD_INVALID             0x0004
DECL|macro|CMD_PROTOCOL_ERR
mdefine_line|#define CMD_PROTOCOL_ERR        0x0005
DECL|macro|CMD_HARDWARE_ERR
mdefine_line|#define CMD_HARDWARE_ERR        0x0006
DECL|macro|CMD_CONNECTION_LOST
mdefine_line|#define CMD_CONNECTION_LOST     0x0007
DECL|macro|CMD_ABORTED
mdefine_line|#define CMD_ABORTED             0x0008
DECL|macro|CMD_ABORT_FAILED
mdefine_line|#define CMD_ABORT_FAILED        0x0009
DECL|macro|CMD_UNSOLICITED_ABORT
mdefine_line|#define CMD_UNSOLICITED_ABORT   0x000A
DECL|macro|CMD_TIMEOUT
mdefine_line|#define CMD_TIMEOUT             0x000B
DECL|macro|CMD_UNABORTABLE
mdefine_line|#define CMD_UNABORTABLE&t;&t;0x000C
singleline_comment|//transfer direction
DECL|macro|XFER_NONE
mdefine_line|#define XFER_NONE               0x00
DECL|macro|XFER_WRITE
mdefine_line|#define XFER_WRITE              0x01
DECL|macro|XFER_READ
mdefine_line|#define XFER_READ               0x02
DECL|macro|XFER_RSVD
mdefine_line|#define XFER_RSVD               0x03
singleline_comment|//task attribute
DECL|macro|ATTR_UNTAGGED
mdefine_line|#define ATTR_UNTAGGED           0x00
DECL|macro|ATTR_SIMPLE
mdefine_line|#define ATTR_SIMPLE             0x04
DECL|macro|ATTR_HEADOFQUEUE
mdefine_line|#define ATTR_HEADOFQUEUE        0x05
DECL|macro|ATTR_ORDERED
mdefine_line|#define ATTR_ORDERED            0x06
DECL|macro|ATTR_ACA
mdefine_line|#define ATTR_ACA                0x07
singleline_comment|//cdb type
DECL|macro|TYPE_CMD
mdefine_line|#define TYPE_CMD&t;&t;&t;&t;0x00
DECL|macro|TYPE_MSG
mdefine_line|#define TYPE_MSG&t;&t;&t;&t;0x01
singleline_comment|//config space register offsets
DECL|macro|CFG_VENDORID
mdefine_line|#define CFG_VENDORID            0x00
DECL|macro|CFG_DEVICEID
mdefine_line|#define CFG_DEVICEID            0x02
DECL|macro|CFG_I2OBAR
mdefine_line|#define CFG_I2OBAR              0x10
DECL|macro|CFG_MEM1BAR
mdefine_line|#define CFG_MEM1BAR             0x14
singleline_comment|//i2o space register offsets
DECL|macro|I2O_IBDB_SET
mdefine_line|#define I2O_IBDB_SET            0x20
DECL|macro|I2O_IBDB_CLEAR
mdefine_line|#define I2O_IBDB_CLEAR          0x70
DECL|macro|I2O_INT_STATUS
mdefine_line|#define I2O_INT_STATUS          0x30
DECL|macro|I2O_INT_MASK
mdefine_line|#define I2O_INT_MASK            0x34
DECL|macro|I2O_IBPOST_Q
mdefine_line|#define I2O_IBPOST_Q            0x40
DECL|macro|I2O_OBPOST_Q
mdefine_line|#define I2O_OBPOST_Q            0x44
singleline_comment|//Configuration Table
DECL|macro|CFGTBL_ChangeReq
mdefine_line|#define CFGTBL_ChangeReq        0x00000001l
DECL|macro|CFGTBL_AccCmds
mdefine_line|#define CFGTBL_AccCmds          0x00000001l
DECL|macro|CFGTBL_Trans_Simple
mdefine_line|#define CFGTBL_Trans_Simple     0x00000002l
DECL|macro|CFGTBL_BusType_Ultra2
mdefine_line|#define CFGTBL_BusType_Ultra2   0x00000001l
DECL|macro|CFGTBL_BusType_Ultra3
mdefine_line|#define CFGTBL_BusType_Ultra3   0x00000002l
DECL|macro|CFGTBL_BusType_Fibre1G
mdefine_line|#define CFGTBL_BusType_Fibre1G  0x00000100l
DECL|macro|CFGTBL_BusType_Fibre2G
mdefine_line|#define CFGTBL_BusType_Fibre2G  0x00000200l
DECL|struct|_vals32
r_typedef
r_struct
id|_vals32
(brace
DECL|member|lower
id|__u32
id|lower
suffix:semicolon
DECL|member|upper
id|__u32
id|upper
suffix:semicolon
DECL|typedef|vals32
)brace
id|vals32
suffix:semicolon
DECL|union|_u64bit
r_typedef
r_union
id|_u64bit
(brace
DECL|member|val32
id|vals32
id|val32
suffix:semicolon
DECL|member|val
id|__u64
id|val
suffix:semicolon
DECL|typedef|u64bit
)brace
id|u64bit
suffix:semicolon
singleline_comment|// Type defs used in the following structs
DECL|macro|BYTE
mdefine_line|#define BYTE __u8
DECL|macro|WORD
mdefine_line|#define WORD __u16
DECL|macro|HWORD
mdefine_line|#define HWORD __u16
DECL|macro|DWORD
mdefine_line|#define DWORD __u32
DECL|macro|QWORD
mdefine_line|#define QWORD vals32 
singleline_comment|//###########################################################################
singleline_comment|//STRUCTURES
singleline_comment|//###########################################################################
DECL|macro|CISS_MAX_LUN
mdefine_line|#define CISS_MAX_LUN&t;16&t;
singleline_comment|// SCSI-3 Cmmands 
macro_line|#pragma pack(1)&t;
DECL|macro|CISS_INQUIRY
mdefine_line|#define CISS_INQUIRY 0x12
singleline_comment|//Date returned
DECL|struct|_InquiryData_struct
r_typedef
r_struct
id|_InquiryData_struct
(brace
DECL|member|data_byte
id|BYTE
id|data_byte
(braket
l_int|36
)braket
suffix:semicolon
DECL|typedef|InquiryData_struct
)brace
id|InquiryData_struct
suffix:semicolon
DECL|macro|CISS_REPORT_LOG
mdefine_line|#define CISS_REPORT_LOG 0xc2    /* Report Logical LUNs */
singleline_comment|// Data returned
DECL|struct|_ReportLUNdata_struct
r_typedef
r_struct
id|_ReportLUNdata_struct
(brace
DECL|member|LUNListLength
id|BYTE
id|LUNListLength
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved
id|DWORD
id|reserved
suffix:semicolon
DECL|member|LUN
id|BYTE
id|LUN
(braket
id|CISS_MAX_LUN
)braket
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|ReportLunData_struct
)brace
id|ReportLunData_struct
suffix:semicolon
DECL|macro|CCISS_READ_CAPACITY
mdefine_line|#define CCISS_READ_CAPACITY 0x25 /* Read Capacity */ 
DECL|struct|_ReadCapdata_struct
r_typedef
r_struct
id|_ReadCapdata_struct
(brace
DECL|member|total_size
id|BYTE
id|total_size
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Total size in blocks
DECL|member|block_size
id|BYTE
id|block_size
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Size of blocks in bytes
DECL|typedef|ReadCapdata_struct
)brace
id|ReadCapdata_struct
suffix:semicolon
singleline_comment|// 12 byte commands not implemented in firmware yet. 
singleline_comment|// #define CCISS_READ &t;0xa8&t;// Read(12)
singleline_comment|// #define CCISS_WRITE&t;0xaa&t;// Write(12)
DECL|macro|CCISS_READ
mdefine_line|#define CCISS_READ   0x28    
singleline_comment|// Read(10)
DECL|macro|CCISS_WRITE
mdefine_line|#define CCISS_WRITE  0x2a    
singleline_comment|// Write(10)
singleline_comment|//Command List Structure
DECL|union|_SCSI3Addr_struct
r_typedef
r_union
id|_SCSI3Addr_struct
(brace
r_struct
(brace
DECL|member|Bus
id|BYTE
id|Bus
suffix:colon
l_int|6
suffix:semicolon
DECL|member|Mode
id|BYTE
id|Mode
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// b00
DECL|member|Dev
id|BYTE
id|Dev
suffix:semicolon
DECL|member|PeripDev
)brace
id|PeripDev
suffix:semicolon
r_struct
(brace
DECL|member|DevMSB
id|BYTE
id|DevMSB
suffix:colon
l_int|6
suffix:semicolon
DECL|member|Mode
id|BYTE
id|Mode
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// b01
DECL|member|DevLSB
id|BYTE
id|DevLSB
suffix:semicolon
DECL|member|LogDev
)brace
id|LogDev
suffix:semicolon
r_struct
(brace
DECL|member|Targ
id|BYTE
id|Targ
suffix:colon
l_int|6
suffix:semicolon
DECL|member|Mode
id|BYTE
id|Mode
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// b10
DECL|member|Dev
id|BYTE
id|Dev
suffix:colon
l_int|5
suffix:semicolon
DECL|member|Bus
id|BYTE
id|Bus
suffix:colon
l_int|3
suffix:semicolon
DECL|member|LogUnit
)brace
id|LogUnit
suffix:semicolon
DECL|typedef|SCSI3Addr_struct
)brace
id|SCSI3Addr_struct
suffix:semicolon
DECL|struct|_PhysDevAddr_struct
r_typedef
r_struct
id|_PhysDevAddr_struct
(brace
DECL|member|TargetId
id|DWORD
id|TargetId
suffix:colon
l_int|24
suffix:semicolon
DECL|member|Bus
id|DWORD
id|Bus
suffix:colon
l_int|6
suffix:semicolon
DECL|member|Mode
id|DWORD
id|Mode
suffix:colon
l_int|2
suffix:semicolon
DECL|member|Target
id|SCSI3Addr_struct
id|Target
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|//2 level target device addr
DECL|typedef|PhysDevAddr_struct
)brace
id|PhysDevAddr_struct
suffix:semicolon
DECL|struct|_LogDevAddr_struct
r_typedef
r_struct
id|_LogDevAddr_struct
(brace
DECL|member|VolId
id|DWORD
id|VolId
suffix:colon
l_int|30
suffix:semicolon
DECL|member|Mode
id|DWORD
id|Mode
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved
id|BYTE
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|LogDevAddr_struct
)brace
id|LogDevAddr_struct
suffix:semicolon
DECL|union|_LUNAddr_struct
r_typedef
r_union
id|_LUNAddr_struct
(brace
DECL|member|LunAddrBytes
id|BYTE
id|LunAddrBytes
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|SCSI3Lun
id|SCSI3Addr_struct
id|SCSI3Lun
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|PhysDev
id|PhysDevAddr_struct
id|PhysDev
suffix:semicolon
DECL|member|LogDev
id|LogDevAddr_struct
id|LogDev
suffix:semicolon
DECL|typedef|LUNAddr_struct
)brace
id|LUNAddr_struct
suffix:semicolon
DECL|struct|_CommandListHeader_struct
r_typedef
r_struct
id|_CommandListHeader_struct
(brace
DECL|member|ReplyQueue
id|BYTE
id|ReplyQueue
suffix:semicolon
DECL|member|SGList
id|BYTE
id|SGList
suffix:semicolon
DECL|member|SGTotal
id|HWORD
id|SGTotal
suffix:semicolon
DECL|member|Tag
id|QWORD
id|Tag
suffix:semicolon
DECL|member|LUN
id|LUNAddr_struct
id|LUN
suffix:semicolon
DECL|typedef|CommandListHeader_struct
)brace
id|CommandListHeader_struct
suffix:semicolon
DECL|struct|_RequestBlock_struct
r_typedef
r_struct
id|_RequestBlock_struct
(brace
DECL|member|CDBLen
id|BYTE
id|CDBLen
suffix:semicolon
r_struct
(brace
DECL|member|Type
id|BYTE
id|Type
suffix:colon
l_int|3
suffix:semicolon
DECL|member|Attribute
id|BYTE
id|Attribute
suffix:colon
l_int|3
suffix:semicolon
DECL|member|Direction
id|BYTE
id|Direction
suffix:colon
l_int|2
suffix:semicolon
DECL|member|Type
)brace
id|Type
suffix:semicolon
DECL|member|Timeout
id|HWORD
id|Timeout
suffix:semicolon
DECL|member|CDB
id|BYTE
id|CDB
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|RequestBlock_struct
)brace
id|RequestBlock_struct
suffix:semicolon
DECL|struct|_ErrDescriptor_struct
r_typedef
r_struct
id|_ErrDescriptor_struct
(brace
DECL|member|Addr
id|QWORD
id|Addr
suffix:semicolon
DECL|member|Len
id|DWORD
id|Len
suffix:semicolon
DECL|typedef|ErrDescriptor_struct
)brace
id|ErrDescriptor_struct
suffix:semicolon
DECL|struct|_SGDescriptor_struct
r_typedef
r_struct
id|_SGDescriptor_struct
(brace
DECL|member|Addr
id|QWORD
id|Addr
suffix:semicolon
DECL|member|Len
id|DWORD
id|Len
suffix:semicolon
DECL|member|Ext
id|DWORD
id|Ext
suffix:semicolon
DECL|typedef|SGDescriptor_struct
)brace
id|SGDescriptor_struct
suffix:semicolon
DECL|union|_MoreErrInfo_struct
r_typedef
r_union
id|_MoreErrInfo_struct
(brace
r_struct
(brace
DECL|member|Reserved
id|BYTE
id|Reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Type
id|BYTE
id|Type
suffix:semicolon
DECL|member|ErrorInfo
id|DWORD
id|ErrorInfo
suffix:semicolon
DECL|member|Common_Info
)brace
id|Common_Info
suffix:semicolon
(def_block
r_struct
(brace
DECL|member|Reserved
id|BYTE
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|offense_size
id|BYTE
id|offense_size
suffix:semicolon
singleline_comment|//size of offending entry
DECL|member|offense_num
id|BYTE
id|offense_num
suffix:semicolon
singleline_comment|//byte # of offense 0-base
DECL|member|offense_value
id|DWORD
id|offense_value
suffix:semicolon
DECL|member|Invalid_Cmd
)brace
)def_block
id|Invalid_Cmd
suffix:semicolon
DECL|typedef|MoreErrInfo_struct
)brace
id|MoreErrInfo_struct
suffix:semicolon
DECL|struct|_ErrorInfo_struct
r_typedef
r_struct
id|_ErrorInfo_struct
(brace
DECL|member|ScsiStatus
id|BYTE
id|ScsiStatus
suffix:semicolon
DECL|member|SenseLen
id|BYTE
id|SenseLen
suffix:semicolon
DECL|member|CommandStatus
id|HWORD
id|CommandStatus
suffix:semicolon
DECL|member|ResidualCnt
id|DWORD
id|ResidualCnt
suffix:semicolon
DECL|member|MoreErrInfo
id|MoreErrInfo_struct
id|MoreErrInfo
suffix:semicolon
DECL|member|SenseInfo
id|BYTE
id|SenseInfo
(braket
id|SENSEINFOBYTES
)braket
suffix:semicolon
DECL|typedef|ErrorInfo_struct
)brace
id|ErrorInfo_struct
suffix:semicolon
multiline_comment|/* Command types */
DECL|macro|CMD_RWREQ
mdefine_line|#define CMD_RWREQ       0x00
DECL|macro|CMD_IOCTL_PEND
mdefine_line|#define CMD_IOCTL_PEND  0x01
DECL|macro|CMD_IOCTL_DONE
mdefine_line|#define CMD_IOCTL_DONE  0x02
DECL|struct|_CommandList_struct
r_typedef
r_struct
id|_CommandList_struct
(brace
DECL|member|Header
id|CommandListHeader_struct
id|Header
suffix:semicolon
DECL|member|Request
id|RequestBlock_struct
id|Request
suffix:semicolon
DECL|member|ErrDesc
id|ErrDescriptor_struct
id|ErrDesc
suffix:semicolon
DECL|member|SG
id|SGDescriptor_struct
id|SG
(braket
id|MAXSGENTRIES
)braket
suffix:semicolon
multiline_comment|/* information associated with the command */
DECL|member|busaddr
id|__u32
id|busaddr
suffix:semicolon
multiline_comment|/* physical addres of this record */
DECL|member|err_info
id|ErrorInfo_struct
op_star
id|err_info
suffix:semicolon
multiline_comment|/* pointer to the allocated mem */
DECL|member|cmd_type
r_int
id|cmd_type
suffix:semicolon
DECL|member|prev
r_struct
id|_CommandList_struct
op_star
id|prev
suffix:semicolon
DECL|member|next
r_struct
id|_CommandList_struct
op_star
id|next
suffix:semicolon
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
DECL|typedef|CommandList_struct
)brace
id|CommandList_struct
suffix:semicolon
singleline_comment|//Configuration Table Structure
DECL|struct|_HostWrite_struct
r_typedef
r_struct
id|_HostWrite_struct
(brace
DECL|member|TransportRequest
id|DWORD
id|TransportRequest
suffix:semicolon
DECL|member|Reserved
id|DWORD
id|Reserved
suffix:semicolon
DECL|member|CoalIntDelay
id|DWORD
id|CoalIntDelay
suffix:semicolon
DECL|member|CoalIntCount
id|DWORD
id|CoalIntCount
suffix:semicolon
DECL|typedef|HostWrite_struct
)brace
id|HostWrite_struct
suffix:semicolon
DECL|struct|_CfgTable_struct
r_typedef
r_struct
id|_CfgTable_struct
(brace
DECL|member|Signature
id|BYTE
id|Signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|SpecValence
id|DWORD
id|SpecValence
suffix:semicolon
DECL|member|TransportSupport
id|DWORD
id|TransportSupport
suffix:semicolon
DECL|member|TransportActive
id|DWORD
id|TransportActive
suffix:semicolon
DECL|member|HostWrite
id|HostWrite_struct
id|HostWrite
suffix:semicolon
DECL|member|CmdsOutMax
id|DWORD
id|CmdsOutMax
suffix:semicolon
DECL|member|BusTypes
id|DWORD
id|BusTypes
suffix:semicolon
DECL|member|Reserved
id|DWORD
id|Reserved
suffix:semicolon
DECL|member|ServerName
id|BYTE
id|ServerName
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|HeartBeat
id|DWORD
id|HeartBeat
suffix:semicolon
DECL|typedef|CfgTable_struct
)brace
id|CfgTable_struct
suffix:semicolon
macro_line|#pragma pack()&t; 
macro_line|#endif 
singleline_comment|// CCISS_CMD_H
eof
