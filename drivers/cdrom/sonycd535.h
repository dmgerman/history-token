macro_line|#ifndef SONYCD535_H
DECL|macro|SONYCD535_H
mdefine_line|#define SONYCD535_H
multiline_comment|/*&n; * define all the commands recognized by the CDU-531/5&n; */
DECL|macro|SONY535_REQUEST_DRIVE_STATUS_1
mdefine_line|#define SONY535_REQUEST_DRIVE_STATUS_1&t;&t;(0x80)
DECL|macro|SONY535_REQUEST_SENSE
mdefine_line|#define SONY535_REQUEST_SENSE&t;&t;&t;(0x82)
DECL|macro|SONY535_REQUEST_DRIVE_STATUS_2
mdefine_line|#define SONY535_REQUEST_DRIVE_STATUS_2&t;&t;(0x84)
DECL|macro|SONY535_REQUEST_ERROR_STATUS
mdefine_line|#define SONY535_REQUEST_ERROR_STATUS&t;&t;(0x86)
DECL|macro|SONY535_REQUEST_AUDIO_STATUS
mdefine_line|#define SONY535_REQUEST_AUDIO_STATUS&t;&t;(0x88)
DECL|macro|SONY535_INQUIRY
mdefine_line|#define SONY535_INQUIRY&t;&t;&t;&t;(0x8a)
DECL|macro|SONY535_SET_INACTIVITY_TIME
mdefine_line|#define SONY535_SET_INACTIVITY_TIME&t;&t;(0x90)
DECL|macro|SONY535_SEEK_AND_READ_N_BLOCKS_1
mdefine_line|#define SONY535_SEEK_AND_READ_N_BLOCKS_1&t;(0xa0)
DECL|macro|SONY535_SEEK_AND_READ_N_BLOCKS_2
mdefine_line|#define SONY535_SEEK_AND_READ_N_BLOCKS_2&t;(0xa4)
DECL|macro|SONY535_PLAY_AUDIO
mdefine_line|#define SONY535_PLAY_AUDIO&t;&t;&t;(0xa6)
DECL|macro|SONY535_REQUEST_DISC_CAPACITY
mdefine_line|#define SONY535_REQUEST_DISC_CAPACITY&t;&t;(0xb0)
DECL|macro|SONY535_REQUEST_TOC_DATA
mdefine_line|#define SONY535_REQUEST_TOC_DATA&t;&t;(0xb2)
DECL|macro|SONY535_REQUEST_SUB_Q_DATA
mdefine_line|#define SONY535_REQUEST_SUB_Q_DATA&t;&t;(0xb4)
DECL|macro|SONY535_REQUEST_ISRC
mdefine_line|#define SONY535_REQUEST_ISRC&t;&t;&t;(0xb6)
DECL|macro|SONY535_REQUEST_UPC_EAN
mdefine_line|#define SONY535_REQUEST_UPC_EAN&t;&t;&t;(0xb8)
DECL|macro|SONY535_SET_DRIVE_MODE
mdefine_line|#define SONY535_SET_DRIVE_MODE&t;&t;&t;(0xc0)
DECL|macro|SONY535_REQUEST_DRIVE_MODE
mdefine_line|#define SONY535_REQUEST_DRIVE_MODE&t;&t;(0xc2)
DECL|macro|SONY535_SET_RETRY_COUNT
mdefine_line|#define SONY535_SET_RETRY_COUNT&t;&t;&t;(0xc4)
DECL|macro|SONY535_DIAGNOSTIC_1
mdefine_line|#define SONY535_DIAGNOSTIC_1&t;&t;&t;(0xc6)
DECL|macro|SONY535_DIAGNOSTIC_4
mdefine_line|#define SONY535_DIAGNOSTIC_4&t;&t;&t;(0xcc)
DECL|macro|SONY535_DIAGNOSTIC_5
mdefine_line|#define SONY535_DIAGNOSTIC_5&t;&t;&t;(0xce)
DECL|macro|SONY535_EJECT_CADDY
mdefine_line|#define SONY535_EJECT_CADDY&t;&t;&t;(0xd0)
DECL|macro|SONY535_DISABLE_EJECT_BUTTON
mdefine_line|#define SONY535_DISABLE_EJECT_BUTTON&t;&t;(0xd2)
DECL|macro|SONY535_ENABLE_EJECT_BUTTON
mdefine_line|#define SONY535_ENABLE_EJECT_BUTTON&t;&t;(0xd4)
DECL|macro|SONY535_HOLD
mdefine_line|#define SONY535_HOLD&t;&t;&t;&t;(0xe0)
DECL|macro|SONY535_AUDIO_PAUSE_ON_OFF
mdefine_line|#define SONY535_AUDIO_PAUSE_ON_OFF&t;&t;(0xe2)
DECL|macro|SONY535_SET_VOLUME
mdefine_line|#define SONY535_SET_VOLUME&t;&t;&t;(0xe8)
DECL|macro|SONY535_STOP
mdefine_line|#define SONY535_STOP&t;&t;&t;&t;(0xf0)
DECL|macro|SONY535_SPIN_UP
mdefine_line|#define SONY535_SPIN_UP&t;&t;&t;&t;(0xf2)
DECL|macro|SONY535_SPIN_DOWN
mdefine_line|#define SONY535_SPIN_DOWN&t;&t;&t;(0xf4)
DECL|macro|SONY535_CLEAR_PARAMETERS
mdefine_line|#define SONY535_CLEAR_PARAMETERS&t;&t;(0xf6)
DECL|macro|SONY535_CLEAR_ENDING_ADDRESS
mdefine_line|#define SONY535_CLEAR_ENDING_ADDRESS&t;&t;(0xf8)
multiline_comment|/*&n; * define some masks&n; */
DECL|macro|SONY535_DATA_NOT_READY_BIT
mdefine_line|#define SONY535_DATA_NOT_READY_BIT&t;&t;(0x1)
DECL|macro|SONY535_RESULT_NOT_READY_BIT
mdefine_line|#define SONY535_RESULT_NOT_READY_BIT&t;&t;(0x2)
multiline_comment|/*&n; *  drive status 1&n; */
DECL|macro|SONY535_STATUS1_COMMAND_ERROR
mdefine_line|#define SONY535_STATUS1_COMMAND_ERROR&t;&t;(0x1)
DECL|macro|SONY535_STATUS1_DATA_ERROR
mdefine_line|#define SONY535_STATUS1_DATA_ERROR&t;&t;(0x2)
DECL|macro|SONY535_STATUS1_SEEK_ERROR
mdefine_line|#define SONY535_STATUS1_SEEK_ERROR&t;&t;(0x4)
DECL|macro|SONY535_STATUS1_DISC_TYPE_ERROR
mdefine_line|#define SONY535_STATUS1_DISC_TYPE_ERROR&t;&t;(0x8)
DECL|macro|SONY535_STATUS1_NOT_SPINNING
mdefine_line|#define SONY535_STATUS1_NOT_SPINNING&t;&t;(0x10)
DECL|macro|SONY535_STATUS1_EJECT_BUTTON_PRESSED
mdefine_line|#define SONY535_STATUS1_EJECT_BUTTON_PRESSED&t;(0x20)
DECL|macro|SONY535_STATUS1_CADDY_NOT_INSERTED
mdefine_line|#define SONY535_STATUS1_CADDY_NOT_INSERTED&t;(0x40)
DECL|macro|SONY535_STATUS1_BYTE_TWO_FOLLOWS
mdefine_line|#define SONY535_STATUS1_BYTE_TWO_FOLLOWS&t;(0x80)
multiline_comment|/*&n; * drive status 2&n; */
DECL|macro|SONY535_CDD_LOADING_ERROR
mdefine_line|#define SONY535_CDD_LOADING_ERROR&t;&t;(0x7)
DECL|macro|SONY535_CDD_NO_DISC
mdefine_line|#define SONY535_CDD_NO_DISC&t;&t;&t;(0x8)
DECL|macro|SONY535_CDD_UNLOADING_ERROR
mdefine_line|#define SONY535_CDD_UNLOADING_ERROR&t;&t;(0x9)
DECL|macro|SONY535_CDD_CADDY_NOT_INSERTED
mdefine_line|#define SONY535_CDD_CADDY_NOT_INSERTED&t;&t;(0xd)
DECL|macro|SONY535_ATN_RESET_OCCURRED
mdefine_line|#define SONY535_ATN_RESET_OCCURRED&t;&t;(0x2)
DECL|macro|SONY535_ATN_DISC_CHANGED
mdefine_line|#define SONY535_ATN_DISC_CHANGED&t;&t;(0x4)
DECL|macro|SONY535_ATN_RESET_AND_DISC_CHANGED
mdefine_line|#define SONY535_ATN_RESET_AND_DISC_CHANGED&t;(0x6)
DECL|macro|SONY535_ATN_EJECT_IN_PROGRESS
mdefine_line|#define SONY535_ATN_EJECT_IN_PROGRESS&t;&t;(0xe)
DECL|macro|SONY535_ATN_BUSY
mdefine_line|#define SONY535_ATN_BUSY&t;&t;&t;(0xf)
multiline_comment|/*&n; * define some parameters&n; */
DECL|macro|SONY535_AUDIO_DRIVE_MODE
mdefine_line|#define SONY535_AUDIO_DRIVE_MODE&t;&t;(0)
DECL|macro|SONY535_CDROM_DRIVE_MODE
mdefine_line|#define SONY535_CDROM_DRIVE_MODE&t;&t;(0xe0)
DECL|macro|SONY535_PLAY_OP_PLAYBACK
mdefine_line|#define SONY535_PLAY_OP_PLAYBACK&t;&t;(0)
DECL|macro|SONY535_PLAY_OP_ENTER_HOLD
mdefine_line|#define SONY535_PLAY_OP_ENTER_HOLD&t;&t;(1)
DECL|macro|SONY535_PLAY_OP_SET_AUDIO_ENDING_ADDR
mdefine_line|#define SONY535_PLAY_OP_SET_AUDIO_ENDING_ADDR&t;(2)
DECL|macro|SONY535_PLAY_OP_SCAN_FORWARD
mdefine_line|#define SONY535_PLAY_OP_SCAN_FORWARD&t;&t;(3)
DECL|macro|SONY535_PLAY_OP_SCAN_BACKWARD
mdefine_line|#define SONY535_PLAY_OP_SCAN_BACKWARD&t;&t;(4)
multiline_comment|/*&n; *  convert from msf format to block number &n; */
DECL|macro|SONY_BLOCK_NUMBER
mdefine_line|#define SONY_BLOCK_NUMBER(m,s,f) (((m)*60L+(s))*75L+(f))
DECL|macro|SONY_BLOCK_NUMBER_MSF
mdefine_line|#define SONY_BLOCK_NUMBER_MSF(x) (((x)[0]*60L+(x)[1])*75L+(x)[2])
multiline_comment|/*&n; *  error return values from the doSonyCmd() routines&n; */
DECL|macro|TIME_OUT
mdefine_line|#define TIME_OUT&t;&t;&t;(-1)
DECL|macro|NO_CDROM
mdefine_line|#define NO_CDROM&t;&t;&t;(-2)
DECL|macro|BAD_STATUS
mdefine_line|#define BAD_STATUS&t;&t;&t;(-3)
DECL|macro|CD_BUSY
mdefine_line|#define CD_BUSY&t;&t;&t;&t;(-4)
DECL|macro|NOT_DATA_CD
mdefine_line|#define NOT_DATA_CD&t;&t;&t;(-5)
DECL|macro|NO_ROOM
mdefine_line|#define NO_ROOM&t;&t;&t;&t;(-6)
DECL|macro|LOG_START_OFFSET
mdefine_line|#define LOG_START_OFFSET        150     /* Offset of first logical sector */
DECL|macro|SONY_JIFFIES_TIMEOUT
mdefine_line|#define SONY_JIFFIES_TIMEOUT&t;(5*HZ)&t;/* Maximum time&n;&t;&t;&t;&t;&t;   the drive will wait/try for an&n;&t;&t;&t;&t;&t;   operation */
DECL|macro|SONY_READY_RETRIES
mdefine_line|#define SONY_READY_RETRIES      (50000)  /* How many times to retry a&n;                                                  spin waiting for a register&n;                                                  to come ready */
DECL|macro|SONY535_FAST_POLLS
mdefine_line|#define SONY535_FAST_POLLS&t;(10000)   /* how many times recheck &n;                                                  status waiting for a data&n;                                                  to become ready */
DECL|typedef|Byte
r_typedef
r_int
r_char
id|Byte
suffix:semicolon
multiline_comment|/*&n; * This is the complete status returned from the drive configuration request&n; * command.&n; */
DECL|struct|s535_sony_drive_config
r_struct
id|s535_sony_drive_config
(brace
DECL|member|vendor_id
r_char
id|vendor_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|product_id
r_char
id|product_id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|product_rev_level
r_char
id|product_rev_level
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The following is returned from the request sub-q data command */
DECL|struct|s535_sony_subcode
r_struct
id|s535_sony_subcode
(brace
DECL|member|address
r_int
r_char
id|address
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control
r_int
r_char
id|control
suffix:colon
l_int|4
suffix:semicolon
DECL|member|track_num
r_int
r_char
id|track_num
suffix:semicolon
DECL|member|index_num
r_int
r_char
id|index_num
suffix:semicolon
DECL|member|rel_msf
r_int
r_char
id|rel_msf
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|abs_msf
r_int
r_char
id|abs_msf
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s535_sony_disc_capacity
r_struct
id|s535_sony_disc_capacity
(brace
DECL|member|mFirstTrack
DECL|member|sFirstTrack
DECL|member|fFirstTrack
id|Byte
id|mFirstTrack
comma
id|sFirstTrack
comma
id|fFirstTrack
suffix:semicolon
DECL|member|mLeadOut
DECL|member|sLeadOut
DECL|member|fLeadOut
id|Byte
id|mLeadOut
comma
id|sLeadOut
comma
id|fLeadOut
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following is returned from the request TOC (Table Of Contents) command.&n; * (last_track_num-first_track_num+1) values are valid in tracks.&n; */
DECL|struct|s535_sony_toc
r_struct
id|s535_sony_toc
(brace
DECL|member|reserved0
r_int
r_char
id|reserved0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control0
r_int
r_char
id|control0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|point0
r_int
r_char
id|point0
suffix:semicolon
DECL|member|first_track_num
r_int
r_char
id|first_track_num
suffix:semicolon
DECL|member|reserved0a
r_int
r_char
id|reserved0a
suffix:semicolon
DECL|member|reserved0b
r_int
r_char
id|reserved0b
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control1
r_int
r_char
id|control1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|point1
r_int
r_char
id|point1
suffix:semicolon
DECL|member|last_track_num
r_int
r_char
id|last_track_num
suffix:semicolon
DECL|member|dummy1
r_int
r_char
id|dummy1
suffix:semicolon
DECL|member|dummy2
r_int
r_char
id|dummy2
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control2
r_int
r_char
id|control2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|point2
r_int
r_char
id|point2
suffix:semicolon
DECL|member|lead_out_start_msf
r_int
r_char
id|lead_out_start_msf
(braket
l_int|3
)braket
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control
r_int
r_char
id|control
suffix:colon
l_int|4
suffix:semicolon
DECL|member|track
r_int
r_char
id|track
suffix:semicolon
DECL|member|track_start_msf
r_int
r_char
id|track_start_msf
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|tracks
)brace
id|tracks
(braket
l_int|100
)braket
suffix:semicolon
DECL|member|lead_out_start_lba
r_int
r_int
id|lead_out_start_lba
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* SONYCD535_H */
eof
