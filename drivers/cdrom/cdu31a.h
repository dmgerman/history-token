multiline_comment|/*&n; * Definitions for a Sony interface CDROM drive.&n; *&n; * Corey Minyard (minyard@wf-rch.cirr.com)&n; *&n; *  Copyright (C) 1993  Corey Minyard&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*&n; * General defines.&n; */
DECL|macro|SONY_XA_DISK_TYPE
mdefine_line|#define SONY_XA_DISK_TYPE 0x20
multiline_comment|/*&n; * Offsets (from the base address) and bits for the various write registers&n; * of the drive.&n; */
DECL|macro|SONY_CMD_REG_OFFSET
mdefine_line|#define SONY_CMD_REG_OFFSET     0
DECL|macro|SONY_PARAM_REG_OFFSET
mdefine_line|#define SONY_PARAM_REG_OFFSET   1
DECL|macro|SONY_WRITE_REG_OFFSET
mdefine_line|#define SONY_WRITE_REG_OFFSET   2
DECL|macro|SONY_CONTROL_REG_OFFSET
mdefine_line|#define SONY_CONTROL_REG_OFFSET 3
DECL|macro|SONY_ATTN_CLR_BIT
macro_line|#       define SONY_ATTN_CLR_BIT        0x01
DECL|macro|SONY_RES_RDY_CLR_BIT
macro_line|#       define SONY_RES_RDY_CLR_BIT     0x02
DECL|macro|SONY_DATA_RDY_CLR_BIT
macro_line|#       define SONY_DATA_RDY_CLR_BIT    0x04
DECL|macro|SONY_ATTN_INT_EN_BIT
macro_line|#       define SONY_ATTN_INT_EN_BIT     0x08
DECL|macro|SONY_RES_RDY_INT_EN_BIT
macro_line|#       define SONY_RES_RDY_INT_EN_BIT  0x10
DECL|macro|SONY_DATA_RDY_INT_EN_BIT
macro_line|#       define SONY_DATA_RDY_INT_EN_BIT 0x20
DECL|macro|SONY_PARAM_CLR_BIT
macro_line|#       define SONY_PARAM_CLR_BIT       0x40
DECL|macro|SONY_DRIVE_RESET_BIT
macro_line|#       define SONY_DRIVE_RESET_BIT     0x80
multiline_comment|/*&n; * Offsets (from the base address) and bits for the various read registers&n; * of the drive.&n; */
DECL|macro|SONY_STATUS_REG_OFFSET
mdefine_line|#define SONY_STATUS_REG_OFFSET  0
DECL|macro|SONY_ATTN_BIT
macro_line|#       define SONY_ATTN_BIT            0x01
DECL|macro|SONY_RES_RDY_BIT
macro_line|#       define SONY_RES_RDY_BIT         0x02
DECL|macro|SONY_DATA_RDY_BIT
macro_line|#       define SONY_DATA_RDY_BIT        0x04
DECL|macro|SONY_ATTN_INT_ST_BIT
macro_line|#       define SONY_ATTN_INT_ST_BIT     0x08
DECL|macro|SONY_RES_RDY_INT_ST_BIT
macro_line|#       define SONY_RES_RDY_INT_ST_BIT  0x10
DECL|macro|SONY_DATA_RDY_INT_ST_BIT
macro_line|#       define SONY_DATA_RDY_INT_ST_BIT 0x20
DECL|macro|SONY_DATA_REQUEST_BIT
macro_line|#       define SONY_DATA_REQUEST_BIT    0x40
DECL|macro|SONY_BUSY_BIT
macro_line|#       define SONY_BUSY_BIT            0x80
DECL|macro|SONY_RESULT_REG_OFFSET
mdefine_line|#define SONY_RESULT_REG_OFFSET  1
DECL|macro|SONY_READ_REG_OFFSET
mdefine_line|#define SONY_READ_REG_OFFSET    2
DECL|macro|SONY_FIFOST_REG_OFFSET
mdefine_line|#define SONY_FIFOST_REG_OFFSET  3
DECL|macro|SONY_PARAM_WRITE_RDY_BIT
macro_line|#       define SONY_PARAM_WRITE_RDY_BIT 0x01
DECL|macro|SONY_PARAM_REG_EMPTY_BIT
macro_line|#       define SONY_PARAM_REG_EMPTY_BIT 0x02
DECL|macro|SONY_RES_REG_NOT_EMP_BIT
macro_line|#       define SONY_RES_REG_NOT_EMP_BIT 0x04
DECL|macro|SONY_RES_REG_FULL_BIT
macro_line|#       define SONY_RES_REG_FULL_BIT    0x08
DECL|macro|LOG_START_OFFSET
mdefine_line|#define LOG_START_OFFSET        150     /* Offset of first logical sector */
DECL|macro|SONY_DETECT_TIMEOUT
mdefine_line|#define SONY_DETECT_TIMEOUT&t;(8*HZ/10) /* Maximum amount of time&n;                                           that drive detection code&n;                                           will wait for response&n;                                           from drive (in 1/100th&squot;s&n;                                           of seconds). */
DECL|macro|SONY_JIFFIES_TIMEOUT
mdefine_line|#define SONY_JIFFIES_TIMEOUT    1000&t;/* Maximum number of times the&n;                                           drive will wait/try for an&n;                                           operation */
DECL|macro|SONY_RESET_TIMEOUT
mdefine_line|#define SONY_RESET_TIMEOUT      100&t;/* Maximum number of times the&n;                                           drive will wait/try a reset&n;                                           operation */
DECL|macro|SONY_READY_RETRIES
mdefine_line|#define SONY_READY_RETRIES      20000   /* How many times to retry a&n;                                           spin waiting for a register&n;                                           to come ready */
DECL|macro|MAX_CDU31A_RETRIES
mdefine_line|#define MAX_CDU31A_RETRIES      3       /* How many times to retry an&n;                                           operation */
multiline_comment|/* Commands to request or set drive control parameters and disc information */
DECL|macro|SONY_REQ_DRIVE_CONFIG_CMD
mdefine_line|#define SONY_REQ_DRIVE_CONFIG_CMD       0x00    /* Returns s_sony_drive_config */
DECL|macro|SONY_REQ_DRIVE_MODE_CMD
mdefine_line|#define SONY_REQ_DRIVE_MODE_CMD         0x01
DECL|macro|SONY_REQ_DRIVE_PARAM_CMD
mdefine_line|#define SONY_REQ_DRIVE_PARAM_CMD        0x02
DECL|macro|SONY_REQ_MECH_STATUS_CMD
mdefine_line|#define SONY_REQ_MECH_STATUS_CMD        0x03
DECL|macro|SONY_REQ_AUDIO_STATUS_CMD
mdefine_line|#define SONY_REQ_AUDIO_STATUS_CMD       0x04
DECL|macro|SONY_SET_DRIVE_PARAM_CMD
mdefine_line|#define SONY_SET_DRIVE_PARAM_CMD        0x10
DECL|macro|SONY_REQ_TOC_DATA_CMD
mdefine_line|#define SONY_REQ_TOC_DATA_CMD           0x20    /* Returns s_sony_toc */
DECL|macro|SONY_REQ_SUBCODE_ADDRESS_CMD
mdefine_line|#define SONY_REQ_SUBCODE_ADDRESS_CMD    0x21    /* Returns s_sony_subcode */
DECL|macro|SONY_REQ_UPC_EAN_CMD
mdefine_line|#define SONY_REQ_UPC_EAN_CMD            0x22
DECL|macro|SONY_REQ_ISRC_CMD
mdefine_line|#define SONY_REQ_ISRC_CMD               0x23
DECL|macro|SONY_REQ_TOC_DATA_SPEC_CMD
mdefine_line|#define SONY_REQ_TOC_DATA_SPEC_CMD      0x24    /* Returns s_sony_session_toc */
multiline_comment|/* Commands to request information from the drive */
DECL|macro|SONY_READ_TOC_CMD
mdefine_line|#define SONY_READ_TOC_CMD               0x30    /* let the drive firmware grab the TOC */
DECL|macro|SONY_SEEK_CMD
mdefine_line|#define SONY_SEEK_CMD                   0x31
DECL|macro|SONY_READ_CMD
mdefine_line|#define SONY_READ_CMD                   0x32
DECL|macro|SONY_READ_BLKERR_STAT_CMD
mdefine_line|#define SONY_READ_BLKERR_STAT_CMD       0x34
DECL|macro|SONY_ABORT_CMD
mdefine_line|#define SONY_ABORT_CMD                  0x35
DECL|macro|SONY_READ_TOC_SPEC_CMD
mdefine_line|#define SONY_READ_TOC_SPEC_CMD          0x36
multiline_comment|/* Commands to control audio */
DECL|macro|SONY_AUDIO_PLAYBACK_CMD
mdefine_line|#define SONY_AUDIO_PLAYBACK_CMD         0x40
DECL|macro|SONY_AUDIO_STOP_CMD
mdefine_line|#define SONY_AUDIO_STOP_CMD             0x41
DECL|macro|SONY_AUDIO_SCAN_CMD
mdefine_line|#define SONY_AUDIO_SCAN_CMD             0x42
multiline_comment|/* Miscellaneous control commands */
DECL|macro|SONY_EJECT_CMD
mdefine_line|#define SONY_EJECT_CMD                  0x50
DECL|macro|SONY_SPIN_UP_CMD
mdefine_line|#define SONY_SPIN_UP_CMD                0x51
DECL|macro|SONY_SPIN_DOWN_CMD
mdefine_line|#define SONY_SPIN_DOWN_CMD              0x52
multiline_comment|/* Diagnostic commands */
DECL|macro|SONY_WRITE_BUFFER_CMD
mdefine_line|#define SONY_WRITE_BUFFER_CMD           0x60
DECL|macro|SONY_READ_BUFFER_CMD
mdefine_line|#define SONY_READ_BUFFER_CMD            0x61
DECL|macro|SONY_DIAGNOSTICS_CMD
mdefine_line|#define SONY_DIAGNOSTICS_CMD            0x62
multiline_comment|/*&n; * The following are command parameters for the set drive parameter command&n; */
DECL|macro|SONY_SD_DECODE_PARAM
mdefine_line|#define SONY_SD_DECODE_PARAM            0x00
DECL|macro|SONY_SD_INTERFACE_PARAM
mdefine_line|#define SONY_SD_INTERFACE_PARAM         0x01
DECL|macro|SONY_SD_BUFFERING_PARAM
mdefine_line|#define SONY_SD_BUFFERING_PARAM         0x02
DECL|macro|SONY_SD_AUDIO_PARAM
mdefine_line|#define SONY_SD_AUDIO_PARAM             0x03
DECL|macro|SONY_SD_AUDIO_VOLUME
mdefine_line|#define SONY_SD_AUDIO_VOLUME            0x04
DECL|macro|SONY_SD_MECH_CONTROL
mdefine_line|#define SONY_SD_MECH_CONTROL            0x05
DECL|macro|SONY_SD_AUTO_SPIN_DOWN_TIME
mdefine_line|#define SONY_SD_AUTO_SPIN_DOWN_TIME     0x06
multiline_comment|/*&n; * The following are parameter bits for the mechanical control command&n; */
DECL|macro|SONY_AUTO_SPIN_UP_BIT
mdefine_line|#define SONY_AUTO_SPIN_UP_BIT           0x01
DECL|macro|SONY_AUTO_EJECT_BIT
mdefine_line|#define SONY_AUTO_EJECT_BIT             0x02
DECL|macro|SONY_DOUBLE_SPEED_BIT
mdefine_line|#define SONY_DOUBLE_SPEED_BIT           0x04
multiline_comment|/*&n; * The following extract information from the drive configuration about&n; * the drive itself.&n; */
DECL|macro|SONY_HWC_GET_LOAD_MECH
mdefine_line|#define SONY_HWC_GET_LOAD_MECH(c)       (c.hw_config[0] &amp; 0x03)
DECL|macro|SONY_HWC_EJECT
mdefine_line|#define SONY_HWC_EJECT(c)               (c.hw_config[0] &amp; 0x04)
DECL|macro|SONY_HWC_LED_SUPPORT
mdefine_line|#define SONY_HWC_LED_SUPPORT(c)         (c.hw_config[0] &amp; 0x08)
DECL|macro|SONY_HWC_DOUBLE_SPEED
mdefine_line|#define SONY_HWC_DOUBLE_SPEED(c)        (c.hw_config[0] &amp; 0x10)
DECL|macro|SONY_HWC_GET_BUF_MEM_SIZE
mdefine_line|#define SONY_HWC_GET_BUF_MEM_SIZE(c)    ((c.hw_config[0] &amp; 0xc0) &gt;&gt; 6)
DECL|macro|SONY_HWC_AUDIO_PLAYBACK
mdefine_line|#define SONY_HWC_AUDIO_PLAYBACK(c)      (c.hw_config[1] &amp; 0x01)
DECL|macro|SONY_HWC_ELECTRIC_VOLUME
mdefine_line|#define SONY_HWC_ELECTRIC_VOLUME(c)     (c.hw_config[1] &amp; 0x02)
DECL|macro|SONY_HWC_ELECTRIC_VOLUME_CTL
mdefine_line|#define SONY_HWC_ELECTRIC_VOLUME_CTL(c) (c.hw_config[1] &amp; 0x04)
DECL|macro|SONY_HWC_CADDY_LOAD_MECH
mdefine_line|#define SONY_HWC_CADDY_LOAD_MECH        0x00
DECL|macro|SONY_HWC_TRAY_LOAD_MECH
mdefine_line|#define SONY_HWC_TRAY_LOAD_MECH         0x01
DECL|macro|SONY_HWC_POPUP_LOAD_MECH
mdefine_line|#define SONY_HWC_POPUP_LOAD_MECH        0x02
DECL|macro|SONY_HWC_UNKWN_LOAD_MECH
mdefine_line|#define SONY_HWC_UNKWN_LOAD_MECH        0x03
DECL|macro|SONY_HWC_8KB_BUFFER
mdefine_line|#define SONY_HWC_8KB_BUFFER             0x00
DECL|macro|SONY_HWC_32KB_BUFFER
mdefine_line|#define SONY_HWC_32KB_BUFFER            0x01
DECL|macro|SONY_HWC_64KB_BUFFER
mdefine_line|#define SONY_HWC_64KB_BUFFER            0x02
DECL|macro|SONY_HWC_UNKWN_BUFFER
mdefine_line|#define SONY_HWC_UNKWN_BUFFER           0x03
multiline_comment|/*&n; * This is the complete status returned from the drive configuration request&n; * command.&n; */
DECL|struct|s_sony_drive_config
r_struct
id|s_sony_drive_config
(brace
DECL|member|exec_status
r_int
r_char
id|exec_status
(braket
l_int|2
)braket
suffix:semicolon
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
l_int|8
)braket
suffix:semicolon
DECL|member|hw_config
r_int
r_char
id|hw_config
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The following is returned from the request subcode address command */
DECL|struct|s_sony_subcode
r_struct
id|s_sony_subcode
(brace
DECL|member|exec_status
r_int
r_char
id|exec_status
(braket
l_int|2
)braket
suffix:semicolon
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
DECL|member|reserved1
r_int
r_char
id|reserved1
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
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS 100&t;/* The maximum tracks a disk may have. */
multiline_comment|/*&n; * The following is returned from the request TOC (Table Of Contents) command.&n; * (last_track_num-first_track_num+1) values are valid in tracks.&n; */
DECL|struct|s_sony_toc
r_struct
id|s_sony_toc
(brace
DECL|member|exec_status
r_int
r_char
id|exec_status
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|address0
r_int
r_char
id|address0
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
DECL|member|disk_type
r_int
r_char
id|disk_type
suffix:semicolon
DECL|member|dummy0
r_int
r_char
id|dummy0
suffix:semicolon
DECL|member|address1
r_int
r_char
id|address1
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
DECL|member|address2
r_int
r_char
id|address2
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
id|MAX_TRACKS
)braket
suffix:semicolon
DECL|member|lead_out_start_lba
r_int
r_int
id|lead_out_start_lba
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s_sony_session_toc
r_struct
id|s_sony_session_toc
(brace
DECL|member|exec_status
r_int
r_char
id|exec_status
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|session_number
r_int
r_char
id|session_number
suffix:semicolon
DECL|member|address0
r_int
r_char
id|address0
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
DECL|member|disk_type
r_int
r_char
id|disk_type
suffix:semicolon
DECL|member|dummy0
r_int
r_char
id|dummy0
suffix:semicolon
DECL|member|address1
r_int
r_char
id|address1
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
DECL|member|address2
r_int
r_char
id|address2
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
DECL|member|addressb0
r_int
r_char
id|addressb0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlb0
r_int
r_char
id|controlb0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointb0
r_int
r_char
id|pointb0
suffix:semicolon
DECL|member|next_poss_prog_area_msf
r_int
r_char
id|next_poss_prog_area_msf
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|num_mode_5_pointers
r_int
r_char
id|num_mode_5_pointers
suffix:semicolon
DECL|member|max_start_outer_leadout_msf
r_int
r_char
id|max_start_outer_leadout_msf
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|addressb1
r_int
r_char
id|addressb1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlb1
r_int
r_char
id|controlb1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointb1
r_int
r_char
id|pointb1
suffix:semicolon
DECL|member|dummyb0_1
r_int
r_char
id|dummyb0_1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|num_skip_interval_pointers
r_int
r_char
id|num_skip_interval_pointers
suffix:semicolon
DECL|member|num_skip_track_assignments
r_int
r_char
id|num_skip_track_assignments
suffix:semicolon
DECL|member|dummyb0_2
r_int
r_char
id|dummyb0_2
suffix:semicolon
DECL|member|addressb2
r_int
r_char
id|addressb2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlb2
r_int
r_char
id|controlb2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointb2
r_int
r_char
id|pointb2
suffix:semicolon
DECL|member|tracksb2
r_int
r_char
id|tracksb2
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|addressb3
r_int
r_char
id|addressb3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlb3
r_int
r_char
id|controlb3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointb3
r_int
r_char
id|pointb3
suffix:semicolon
DECL|member|tracksb3
r_int
r_char
id|tracksb3
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|addressb4
r_int
r_char
id|addressb4
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlb4
r_int
r_char
id|controlb4
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointb4
r_int
r_char
id|pointb4
suffix:semicolon
DECL|member|tracksb4
r_int
r_char
id|tracksb4
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|addressc0
r_int
r_char
id|addressc0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|controlc0
r_int
r_char
id|controlc0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pointc0
r_int
r_char
id|pointc0
suffix:semicolon
DECL|member|dummyc0
r_int
r_char
id|dummyc0
(braket
l_int|7
)braket
suffix:semicolon
r_struct
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
id|MAX_TRACKS
)braket
suffix:semicolon
DECL|member|start_track_lba
r_int
r_int
id|start_track_lba
suffix:semicolon
DECL|member|lead_out_start_lba
r_int
r_int
id|lead_out_start_lba
suffix:semicolon
DECL|member|mint
r_int
r_int
id|mint
suffix:semicolon
DECL|member|maxt
r_int
r_int
id|maxt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s_all_sessions_toc
r_struct
id|s_all_sessions_toc
(brace
DECL|member|sessions
r_int
r_char
id|sessions
suffix:semicolon
DECL|member|track_entries
r_int
r_int
id|track_entries
suffix:semicolon
DECL|member|first_track_num
r_int
r_char
id|first_track_num
suffix:semicolon
DECL|member|last_track_num
r_int
r_char
id|last_track_num
suffix:semicolon
DECL|member|disk_type
r_int
r_char
id|disk_type
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
id|MAX_TRACKS
)braket
suffix:semicolon
DECL|member|start_track_lba
r_int
r_int
id|start_track_lba
suffix:semicolon
DECL|member|lead_out_start_lba
r_int
r_int
id|lead_out_start_lba
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following are errors returned from the drive.&n; */
multiline_comment|/* Command error group */
DECL|macro|SONY_ILL_CMD_ERR
mdefine_line|#define SONY_ILL_CMD_ERR                0x10
DECL|macro|SONY_ILL_PARAM_ERR
mdefine_line|#define SONY_ILL_PARAM_ERR              0x11
multiline_comment|/* Mechanism group */
DECL|macro|SONY_NOT_LOAD_ERR
mdefine_line|#define SONY_NOT_LOAD_ERR               0x20
DECL|macro|SONY_NO_DISK_ERR
mdefine_line|#define SONY_NO_DISK_ERR                0x21
DECL|macro|SONY_NOT_SPIN_ERR
mdefine_line|#define SONY_NOT_SPIN_ERR               0x22
DECL|macro|SONY_SPIN_ERR
mdefine_line|#define SONY_SPIN_ERR                   0x23
DECL|macro|SONY_SPINDLE_SERVO_ERR
mdefine_line|#define SONY_SPINDLE_SERVO_ERR          0x25
DECL|macro|SONY_FOCUS_SERVO_ERR
mdefine_line|#define SONY_FOCUS_SERVO_ERR            0x26
DECL|macro|SONY_EJECT_MECH_ERR
mdefine_line|#define SONY_EJECT_MECH_ERR             0x29
DECL|macro|SONY_AUDIO_PLAYING_ERR
mdefine_line|#define SONY_AUDIO_PLAYING_ERR          0x2a
DECL|macro|SONY_EMERGENCY_EJECT_ERR
mdefine_line|#define SONY_EMERGENCY_EJECT_ERR        0x2c
multiline_comment|/* Seek error group */
DECL|macro|SONY_FOCUS_ERR
mdefine_line|#define SONY_FOCUS_ERR                  0x30
DECL|macro|SONY_FRAME_SYNC_ERR
mdefine_line|#define SONY_FRAME_SYNC_ERR             0x31
DECL|macro|SONY_SUBCODE_ADDR_ERR
mdefine_line|#define SONY_SUBCODE_ADDR_ERR           0x32
DECL|macro|SONY_BLOCK_SYNC_ERR
mdefine_line|#define SONY_BLOCK_SYNC_ERR             0x33
DECL|macro|SONY_HEADER_ADDR_ERR
mdefine_line|#define SONY_HEADER_ADDR_ERR            0x34
multiline_comment|/* Read error group */
DECL|macro|SONY_ILL_TRACK_R_ERR
mdefine_line|#define SONY_ILL_TRACK_R_ERR            0x40
DECL|macro|SONY_MODE_0_R_ERR
mdefine_line|#define SONY_MODE_0_R_ERR               0x41
DECL|macro|SONY_ILL_MODE_R_ERR
mdefine_line|#define SONY_ILL_MODE_R_ERR             0x42
DECL|macro|SONY_ILL_BLOCK_SIZE_R_ERR
mdefine_line|#define SONY_ILL_BLOCK_SIZE_R_ERR       0x43
DECL|macro|SONY_MODE_R_ERR
mdefine_line|#define SONY_MODE_R_ERR                 0x44
DECL|macro|SONY_FORM_R_ERR
mdefine_line|#define SONY_FORM_R_ERR                 0x45
DECL|macro|SONY_LEAD_OUT_R_ERR
mdefine_line|#define SONY_LEAD_OUT_R_ERR             0x46
DECL|macro|SONY_BUFFER_OVERRUN_R_ERR
mdefine_line|#define SONY_BUFFER_OVERRUN_R_ERR       0x47
multiline_comment|/* Data error group */
DECL|macro|SONY_UNREC_CIRC_ERR
mdefine_line|#define SONY_UNREC_CIRC_ERR             0x53
DECL|macro|SONY_UNREC_LECC_ERR
mdefine_line|#define SONY_UNREC_LECC_ERR             0x57
multiline_comment|/* Subcode error group */
DECL|macro|SONY_NO_TOC_ERR
mdefine_line|#define SONY_NO_TOC_ERR                 0x60
DECL|macro|SONY_SUBCODE_DATA_NVAL_ERR
mdefine_line|#define SONY_SUBCODE_DATA_NVAL_ERR      0x61
DECL|macro|SONY_FOCUS_ON_TOC_READ_ERR
mdefine_line|#define SONY_FOCUS_ON_TOC_READ_ERR      0x63
DECL|macro|SONY_FRAME_SYNC_ON_TOC_READ_ERR
mdefine_line|#define SONY_FRAME_SYNC_ON_TOC_READ_ERR 0x64
DECL|macro|SONY_TOC_DATA_ERR
mdefine_line|#define SONY_TOC_DATA_ERR               0x65
multiline_comment|/* Hardware failure group */
DECL|macro|SONY_HW_FAILURE_ERR
mdefine_line|#define SONY_HW_FAILURE_ERR             0x70
DECL|macro|SONY_LEAD_IN_A_ERR
mdefine_line|#define SONY_LEAD_IN_A_ERR              0x91
DECL|macro|SONY_LEAD_OUT_A_ERR
mdefine_line|#define SONY_LEAD_OUT_A_ERR             0x92
DECL|macro|SONY_DATA_TRACK_A_ERR
mdefine_line|#define SONY_DATA_TRACK_A_ERR           0x93
multiline_comment|/*&n; * The following are returned from the Read With Block Error Status command.&n; * They are not errors but information (Errors from the 0x5x group above may&n; * also be returned&n; */
DECL|macro|SONY_NO_CIRC_ERR_BLK_STAT
mdefine_line|#define SONY_NO_CIRC_ERR_BLK_STAT       0x50
DECL|macro|SONY_NO_LECC_ERR_BLK_STAT
mdefine_line|#define SONY_NO_LECC_ERR_BLK_STAT       0x54
DECL|macro|SONY_RECOV_LECC_ERR_BLK_STAT
mdefine_line|#define SONY_RECOV_LECC_ERR_BLK_STAT    0x55
DECL|macro|SONY_NO_ERR_DETECTION_STAT
mdefine_line|#define SONY_NO_ERR_DETECTION_STAT      0x59
multiline_comment|/* &n; * The following is not an error returned by the drive, but by the code&n; * that talks to the drive.  It is returned because of a timeout.&n; */
DECL|macro|SONY_TIMEOUT_OP_ERR
mdefine_line|#define SONY_TIMEOUT_OP_ERR             0x01
DECL|macro|SONY_SIGNAL_OP_ERR
mdefine_line|#define SONY_SIGNAL_OP_ERR              0x02
DECL|macro|SONY_BAD_DATA_ERR
mdefine_line|#define SONY_BAD_DATA_ERR               0x03
multiline_comment|/*&n; * The following are attention code for asynchronous events from the drive.&n; */
multiline_comment|/* Standard attention group */
DECL|macro|SONY_EMER_EJECT_ATTN
mdefine_line|#define SONY_EMER_EJECT_ATTN            0x2c
DECL|macro|SONY_HW_FAILURE_ATTN
mdefine_line|#define SONY_HW_FAILURE_ATTN            0x70
DECL|macro|SONY_MECH_LOADED_ATTN
mdefine_line|#define SONY_MECH_LOADED_ATTN           0x80
DECL|macro|SONY_EJECT_PUSHED_ATTN
mdefine_line|#define SONY_EJECT_PUSHED_ATTN          0x81
multiline_comment|/* Audio attention group */
DECL|macro|SONY_AUDIO_PLAY_DONE_ATTN
mdefine_line|#define SONY_AUDIO_PLAY_DONE_ATTN       0x90
DECL|macro|SONY_LEAD_IN_ERR_ATTN
mdefine_line|#define SONY_LEAD_IN_ERR_ATTN           0x91
DECL|macro|SONY_LEAD_OUT_ERR_ATTN
mdefine_line|#define SONY_LEAD_OUT_ERR_ATTN          0x92
DECL|macro|SONY_DATA_TRACK_ERR_ATTN
mdefine_line|#define SONY_DATA_TRACK_ERR_ATTN        0x93
DECL|macro|SONY_AUDIO_PLAYBACK_ERR_ATTN
mdefine_line|#define SONY_AUDIO_PLAYBACK_ERR_ATTN    0x94
multiline_comment|/* Auto spin up group */
DECL|macro|SONY_SPIN_UP_COMPLETE_ATTN
mdefine_line|#define SONY_SPIN_UP_COMPLETE_ATTN      0x24
DECL|macro|SONY_SPINDLE_SERVO_ERR_ATTN
mdefine_line|#define SONY_SPINDLE_SERVO_ERR_ATTN     0x25
DECL|macro|SONY_FOCUS_SERVO_ERR_ATTN
mdefine_line|#define SONY_FOCUS_SERVO_ERR_ATTN       0x26
DECL|macro|SONY_TOC_READ_DONE_ATTN
mdefine_line|#define SONY_TOC_READ_DONE_ATTN         0x62
DECL|macro|SONY_FOCUS_ON_TOC_READ_ERR_ATTN
mdefine_line|#define SONY_FOCUS_ON_TOC_READ_ERR_ATTN 0x63
DECL|macro|SONY_SYNC_ON_TOC_READ_ERR_ATTN
mdefine_line|#define SONY_SYNC_ON_TOC_READ_ERR_ATTN  0x65
multiline_comment|/* Auto eject group */
DECL|macro|SONY_SPIN_DOWN_COMPLETE_ATTN
mdefine_line|#define SONY_SPIN_DOWN_COMPLETE_ATTN    0x27
DECL|macro|SONY_EJECT_COMPLETE_ATTN
mdefine_line|#define SONY_EJECT_COMPLETE_ATTN        0x28
DECL|macro|SONY_EJECT_MECH_ERR_ATTN
mdefine_line|#define SONY_EJECT_MECH_ERR_ATTN        0x29
eof
