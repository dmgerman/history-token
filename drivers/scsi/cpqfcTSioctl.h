singleline_comment|// for user apps, make sure data size types are defined
singleline_comment|// with 
DECL|macro|CCPQFCTS_IOC_MAGIC
mdefine_line|#define CCPQFCTS_IOC_MAGIC &squot;Z&squot;
r_typedef
r_struct
(brace
DECL|member|bus
id|__u8
id|bus
suffix:semicolon
DECL|member|dev_fn
id|__u8
id|dev_fn
suffix:semicolon
DECL|member|board_id
id|__u32
id|board_id
suffix:semicolon
DECL|typedef|cpqfc_pci_info_struct
)brace
id|cpqfc_pci_info_struct
suffix:semicolon
DECL|typedef|DriverVer_type
r_typedef
id|__u32
id|DriverVer_type
suffix:semicolon
multiline_comment|/*&n;typedef union&n;{&n;  struct  // Peripheral Unit Device&n;  { &n;    __u8 Bus:6;&n;    __u8 Mode:2;  // b00&n;    __u8 Dev;&n;  } PeripDev;&n;  struct  // Volume Set Address&n;  { &n;    __u8 DevMSB:6;&n;    __u8 Mode:2;  // b01&n;    __u8 DevLSB;&n;  } LogDev;&n;  struct  // Logical Unit Device (SCSI-3, SCC-2 defined)&n;  { &n;    __u8 Targ:6;&n;    __u8 Mode:2;  // b10&n;    __u8 Dev:5;&n;    __u8 Bus:3;&n;&n;  } LogUnit;&n;} SCSI3Addr_struct;&n;&n;&n;typedef struct&n;{&n;  SCSI3Addr_struct FCP_Nexus;&n;  __u8 cdb[16];&n;} PassThru_Command_struct;&n;*/
multiline_comment|/* this is nearly duplicated in idashare.h */
r_typedef
r_struct
(brace
DECL|member|lc
r_int
id|lc
suffix:semicolon
multiline_comment|/* Controller number */
DECL|member|node
r_int
id|node
suffix:semicolon
multiline_comment|/* Node (box) number */
DECL|member|ld
r_int
id|ld
suffix:semicolon
multiline_comment|/* Logical Drive on this box, if required */
DECL|member|nexus
id|__u32
id|nexus
suffix:semicolon
multiline_comment|/* SCSI Nexus */
DECL|member|argp
r_void
op_star
id|argp
suffix:semicolon
multiline_comment|/* Argument pointer */
DECL|typedef|VENDOR_IOCTL_REQ
)brace
id|VENDOR_IOCTL_REQ
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cdb
r_char
id|cdb
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* SCSI CDB for the pass-through */
DECL|member|bus
id|ushort
id|bus
suffix:semicolon
multiline_comment|/* Target bus on the box */
DECL|member|pdrive
id|ushort
id|pdrive
suffix:semicolon
multiline_comment|/* Physical drive on the box */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of the data area of the CDB */
DECL|member|sense_len
r_int
id|sense_len
suffix:semicolon
multiline_comment|/* Length of the sense data */
DECL|member|sense_data
r_char
id|sense_data
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Sense data */
DECL|member|bufp
r_void
op_star
id|bufp
suffix:semicolon
multiline_comment|/* Data area for the CDB */
DECL|member|rw_flag
r_char
id|rw_flag
suffix:semicolon
multiline_comment|/* Read CDB or Write CDB */
DECL|typedef|cpqfc_passthru_t
)brace
id|cpqfc_passthru_t
suffix:semicolon
multiline_comment|/*&n;** Defines for the IOCTLS.&n;*/
DECL|macro|VENDOR_READ_OPCODE
mdefine_line|#define VENDOR_READ_OPCODE&t;&t;&t;0x26
DECL|macro|VENDOR_WRITE_OPCODE
mdefine_line|#define VENDOR_WRITE_OPCODE&t;&t;&t;0x27
DECL|macro|CPQFCTS_GETPCIINFO
mdefine_line|#define CPQFCTS_GETPCIINFO _IOR( CCPQFCTS_IOC_MAGIC, 1, cpqfc_pci_info_struct)
DECL|macro|CPQFCTS_GETDRIVVER
mdefine_line|#define CPQFCTS_GETDRIVVER _IOR( CCPQFCTS_IOC_MAGIC, 9, DriverVer_type)
DECL|macro|CPQFCTS_SCSI_PASSTHRU
mdefine_line|#define CPQFCTS_SCSI_PASSTHRU _IOWR( CCPQFCTS_IOC_MAGIC,11, VENDOR_IOCTL_REQ)
multiline_comment|/* We would rather have equivalent generic, low-level driver agnostic &n;ioctls that do what CPQFC_IOCTL_FC_TARGET_ADDRESS and &n;CPQFC_IOCTL_FC_TDR 0x5388 do, but currently, we do not have them, &n;consequently applications would have to know they are talking to cpqfc. */
multiline_comment|/* Used to get Fibre Channel WWN and port_id from device */
singleline_comment|// #define CPQFC_IOCTL_FC_TARGET_ADDRESS 0x5387
DECL|macro|CPQFC_IOCTL_FC_TARGET_ADDRESS
mdefine_line|#define CPQFC_IOCTL_FC_TARGET_ADDRESS &bslash;&n;&t;_IOR( CCPQFCTS_IOC_MAGIC, 13, Scsi_FCTargAddress)
multiline_comment|/* Used to invoke Target Defice Reset for Fibre Channel */
singleline_comment|// #define CPQFC_IOCTL_FC_TDR 0x5388
DECL|macro|CPQFC_IOCTL_FC_TDR
mdefine_line|#define CPQFC_IOCTL_FC_TDR _IO( CCPQFCTS_IOC_MAGIC, 15)
eof
