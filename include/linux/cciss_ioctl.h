macro_line|#ifndef CCISS_IOCTLH
DECL|macro|CCISS_IOCTLH
mdefine_line|#define CCISS_IOCTLH
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|CCISS_IOC_MAGIC
mdefine_line|#define CCISS_IOC_MAGIC &squot;B&squot;
DECL|struct|_cciss_pci_info_struct
r_typedef
r_struct
id|_cciss_pci_info_struct
(brace
DECL|member|bus
r_int
r_char
id|bus
suffix:semicolon
DECL|member|dev_fn
r_int
r_char
id|dev_fn
suffix:semicolon
DECL|member|board_id
id|__u32
id|board_id
suffix:semicolon
DECL|typedef|cciss_pci_info_struct
)brace
id|cciss_pci_info_struct
suffix:semicolon
DECL|struct|_cciss_coalint_struct
r_typedef
r_struct
id|_cciss_coalint_struct
(brace
DECL|member|delay
id|__u32
id|delay
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|typedef|cciss_coalint_struct
)brace
id|cciss_coalint_struct
suffix:semicolon
DECL|typedef|NodeName_type
r_typedef
r_char
id|NodeName_type
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|Heartbeat_type
r_typedef
id|__u32
id|Heartbeat_type
suffix:semicolon
DECL|macro|CISS_PARSCSIU2
mdefine_line|#define CISS_PARSCSIU2 &t;0x0001
DECL|macro|CISS_PARCSCIU3
mdefine_line|#define CISS_PARCSCIU3 &t;0x0002
DECL|macro|CISS_FIBRE1G
mdefine_line|#define CISS_FIBRE1G&t;0x0100
DECL|macro|CISS_FIBRE2G
mdefine_line|#define CISS_FIBRE2G&t;0x0200
DECL|typedef|BusTypes_type
r_typedef
id|__u32
id|BusTypes_type
suffix:semicolon
DECL|typedef|FirmwareVer_type
r_typedef
r_char
id|FirmwareVer_type
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|DriverVer_type
r_typedef
id|__u32
id|DriverVer_type
suffix:semicolon
macro_line|#ifndef CCISS_CMD_H
singleline_comment|// This defines are duplicated in cciss_cmd.h in the driver directory 
singleline_comment|//general boundary defintions
DECL|macro|SENSEINFOBYTES
mdefine_line|#define SENSEINFOBYTES          32
singleline_comment|//note that this value may vary between host implementations
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
singleline_comment|// Type defs used in the following structs
DECL|macro|BYTE
mdefine_line|#define BYTE __u8
DECL|macro|WORD
mdefine_line|#define WORD __u16
DECL|macro|HWORD
mdefine_line|#define HWORD __u16
DECL|macro|DWORD
mdefine_line|#define DWORD __u32
DECL|macro|CISS_MAX_LUN
mdefine_line|#define CISS_MAX_LUN&t;16&t;
DECL|macro|LEVEL2LUN
mdefine_line|#define LEVEL2LUN   1   
singleline_comment|// index into Target(x) structure, due to byte swapping
DECL|macro|LEVEL3LUN
mdefine_line|#define LEVEL3LUN   0
macro_line|#pragma pack(1)
singleline_comment|//Command List Structure
DECL|union|_SCSI3Addr_struct
r_typedef
r_union
id|_SCSI3Addr_struct
(brace
r_struct
(brace
DECL|member|Dev
id|BYTE
id|Dev
suffix:semicolon
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
DECL|member|PeripDev
)brace
id|PeripDev
suffix:semicolon
r_struct
(brace
DECL|member|DevLSB
id|BYTE
id|DevLSB
suffix:semicolon
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
DECL|member|LogDev
)brace
id|LogDev
suffix:semicolon
r_struct
(brace
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
macro_line|#pragma pack()
macro_line|#endif /* CCISS_CMD_H */ 
DECL|struct|_IOCTL_Command_struct
r_typedef
r_struct
id|_IOCTL_Command_struct
(brace
DECL|member|LUN_info
id|LUNAddr_struct
id|LUN_info
suffix:semicolon
DECL|member|Request
id|RequestBlock_struct
id|Request
suffix:semicolon
DECL|member|error_info
id|ErrorInfo_struct
id|error_info
suffix:semicolon
DECL|member|buf_size
id|WORD
id|buf_size
suffix:semicolon
multiline_comment|/* size in bytes of the buf */
DECL|member|buf
id|BYTE
op_star
id|buf
suffix:semicolon
DECL|typedef|IOCTL_Command_struct
)brace
id|IOCTL_Command_struct
suffix:semicolon
DECL|macro|CCISS_GETPCIINFO
mdefine_line|#define CCISS_GETPCIINFO _IOR(CCISS_IOC_MAGIC, 1, cciss_pci_info_struct)
DECL|macro|CCISS_GETINTINFO
mdefine_line|#define CCISS_GETINTINFO _IOR(CCISS_IOC_MAGIC, 2, cciss_coalint_struct)
DECL|macro|CCISS_SETINTINFO
mdefine_line|#define CCISS_SETINTINFO _IOW(CCISS_IOC_MAGIC, 3, cciss_coalint_struct)
DECL|macro|CCISS_GETNODENAME
mdefine_line|#define CCISS_GETNODENAME _IOR(CCISS_IOC_MAGIC, 4, NodeName_type)
DECL|macro|CCISS_SETNODENAME
mdefine_line|#define CCISS_SETNODENAME _IOW(CCISS_IOC_MAGIC, 5, NodeName_type)
DECL|macro|CCISS_GETHEARTBEAT
mdefine_line|#define CCISS_GETHEARTBEAT _IOR(CCISS_IOC_MAGIC, 6, Heartbeat_type)
DECL|macro|CCISS_GETBUSTYPES
mdefine_line|#define CCISS_GETBUSTYPES  _IOR(CCISS_IOC_MAGIC, 7, BusTypes_type)
DECL|macro|CCISS_GETFIRMVER
mdefine_line|#define CCISS_GETFIRMVER   _IOR(CCISS_IOC_MAGIC, 8, FirmwareVer_type)
DECL|macro|CCISS_GETDRIVVER
mdefine_line|#define CCISS_GETDRIVVER   _IOR(CCISS_IOC_MAGIC, 9, DriverVer_type)
DECL|macro|CCISS_REVALIDVOLS
mdefine_line|#define CCISS_REVALIDVOLS  _IO(CCISS_IOC_MAGIC, 10)
DECL|macro|CCISS_PASSTHRU
mdefine_line|#define CCISS_PASSTHRU&t;   _IOWR(CCISS_IOC_MAGIC, 11, IOCTL_Command_struct)
macro_line|#endif  
eof
