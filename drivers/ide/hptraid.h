DECL|struct|highpoint_raid_conf
r_struct
id|highpoint_raid_conf
(brace
DECL|member|filler1
r_int8
id|filler1
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|magic
id|u_int32_t
id|magic
suffix:semicolon
DECL|macro|HPT_MAGIC_OK
mdefine_line|#define HPT_MAGIC_OK   0x5a7816f0
DECL|macro|HPT_MAGIC_BAD
mdefine_line|#define HPT_MAGIC_BAD  0x5a7816fd  
DECL|member|magic_0
id|u_int32_t
id|magic_0
suffix:semicolon
DECL|member|magic_1
id|u_int32_t
id|magic_1
suffix:semicolon
DECL|member|order
id|u_int32_t
id|order
suffix:semicolon
DECL|macro|HPT_O_MIRROR
mdefine_line|#define HPT_O_MIRROR   0x01  
DECL|macro|HPT_O_STRIPE
mdefine_line|#define HPT_O_STRIPE   0x02
DECL|macro|HPT_O_OK
mdefine_line|#define HPT_O_OK       0x04
DECL|member|raid_disks
id|u_int8_t
id|raid_disks
suffix:semicolon
DECL|member|raid0_shift
id|u_int8_t
id|raid0_shift
suffix:semicolon
DECL|member|type
id|u_int8_t
id|type
suffix:semicolon
DECL|macro|HPT_T_RAID_0
mdefine_line|#define HPT_T_RAID_0   0x00 
DECL|macro|HPT_T_RAID_1
mdefine_line|#define HPT_T_RAID_1   0x01
DECL|macro|HPT_T_RAID_01_RAID_0
mdefine_line|#define HPT_T_RAID_01_RAID_0   0x02
DECL|macro|HPT_T_SPAN
mdefine_line|#define HPT_T_SPAN             0x03
DECL|macro|HPT_T_RAID_3
mdefine_line|#define HPT_T_RAID_3           0x04   
DECL|macro|HPT_T_RAID_5
mdefine_line|#define HPT_T_RAID_5           0x05
DECL|macro|HPT_T_SINGLEDISK
mdefine_line|#define HPT_T_SINGLEDISK       0x06
DECL|macro|HPT_T_RAID_01_RAID_1
mdefine_line|#define HPT_T_RAID_01_RAID_1   0x07
DECL|member|disk_number
id|u_int8_t
id|disk_number
suffix:semicolon
DECL|member|total_secs
id|u_int32_t
id|total_secs
suffix:semicolon
DECL|member|disk_mode
id|u_int32_t
id|disk_mode
suffix:semicolon
DECL|member|boot_mode
id|u_int32_t
id|boot_mode
suffix:semicolon
DECL|member|boot_disk
id|u_int8_t
id|boot_disk
suffix:semicolon
DECL|member|boot_protect
id|u_int8_t
id|boot_protect
suffix:semicolon
DECL|member|error_log_entries
id|u_int8_t
id|error_log_entries
suffix:semicolon
DECL|member|error_log_index
id|u_int8_t
id|error_log_index
suffix:semicolon
r_struct
(brace
DECL|member|timestamp
id|u_int32_t
id|timestamp
suffix:semicolon
DECL|member|reason
id|u_int8_t
id|reason
suffix:semicolon
DECL|macro|HPT_R_REMOVED
mdefine_line|#define HPT_R_REMOVED          0xfe      
DECL|macro|HPT_R_BROKEN
mdefine_line|#define HPT_R_BROKEN           0xff      
DECL|member|disk
id|u_int8_t
id|disk
suffix:semicolon
DECL|member|status
id|u_int8_t
id|status
suffix:semicolon
DECL|member|sectors
id|u_int8_t
id|sectors
suffix:semicolon
DECL|member|lba
id|u_int32_t
id|lba
suffix:semicolon
DECL|member|errorlog
)brace
id|errorlog
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|filler
id|u_int8_t
id|filler
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
