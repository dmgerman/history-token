macro_line|#ifndef _AV7110_HW_H_
DECL|macro|_AV7110_HW_H_
mdefine_line|#define _AV7110_HW_H_
macro_line|#include &quot;av7110.h&quot;
multiline_comment|/* DEBI transfer mode defs */
DECL|macro|DEBINOSWAP
mdefine_line|#define DEBINOSWAP 0x000e0000
DECL|macro|DEBISWAB
mdefine_line|#define DEBISWAB   0x001e0000
DECL|macro|DEBISWAP
mdefine_line|#define DEBISWAP   0x002e0000
DECL|macro|ARM_WAIT_FREE
mdefine_line|#define ARM_WAIT_FREE  (HZ)
DECL|macro|ARM_WAIT_SHAKE
mdefine_line|#define ARM_WAIT_SHAKE (HZ/5)
DECL|macro|ARM_WAIT_OSD
mdefine_line|#define ARM_WAIT_OSD (HZ)
DECL|enum|av7110_bootstate
r_enum
id|av7110_bootstate
(brace
DECL|enumerator|BOOTSTATE_BUFFER_EMPTY
id|BOOTSTATE_BUFFER_EMPTY
op_assign
l_int|0
comma
DECL|enumerator|BOOTSTATE_BUFFER_FULL
id|BOOTSTATE_BUFFER_FULL
op_assign
l_int|1
comma
DECL|enumerator|BOOTSTATE_BOOT_COMPLETE
id|BOOTSTATE_BOOT_COMPLETE
op_assign
l_int|2
)brace
suffix:semicolon
DECL|enum|av7110_type_rec_play_format
r_enum
id|av7110_type_rec_play_format
DECL|enumerator|RP_None
(brace
id|RP_None
comma
DECL|enumerator|AudioPES
id|AudioPES
comma
DECL|enumerator|AudioMp2
id|AudioMp2
comma
DECL|enumerator|AudioPCM
id|AudioPCM
comma
DECL|enumerator|VideoPES
id|VideoPES
comma
DECL|enumerator|AV_PES
id|AV_PES
)brace
suffix:semicolon
DECL|enum|av7110_osd_palette_type
r_enum
id|av7110_osd_palette_type
(brace
DECL|enumerator|NoPalet
id|NoPalet
op_assign
l_int|0
comma
multiline_comment|/* No palette */
DECL|enumerator|Pal1Bit
id|Pal1Bit
op_assign
l_int|2
comma
multiline_comment|/* 2 colors for 1 Bit Palette    */
DECL|enumerator|Pal2Bit
id|Pal2Bit
op_assign
l_int|4
comma
multiline_comment|/* 4 colors for 2 bit palette    */
DECL|enumerator|Pal4Bit
id|Pal4Bit
op_assign
l_int|16
comma
multiline_comment|/* 16 colors for 4 bit palette   */
DECL|enumerator|Pal8Bit
id|Pal8Bit
op_assign
l_int|256
multiline_comment|/* 256 colors for 16 bit palette */
)brace
suffix:semicolon
multiline_comment|/* switch defines */
DECL|macro|SB_GPIO
mdefine_line|#define SB_GPIO 3
DECL|macro|SB_OFF
mdefine_line|#define SB_OFF&t;SAA7146_GPIO_OUTLO  /* SlowBlank off (TV-Mode) */
DECL|macro|SB_ON
mdefine_line|#define SB_ON&t;SAA7146_GPIO_INPUT  /* SlowBlank on  (AV-Mode) */
DECL|macro|SB_WIDE
mdefine_line|#define SB_WIDE SAA7146_GPIO_OUTHI  /* SlowBlank 6V  (16/9-Mode) (not implemented) */
DECL|macro|FB_GPIO
mdefine_line|#define FB_GPIO 1
DECL|macro|FB_OFF
mdefine_line|#define FB_OFF&t;SAA7146_GPIO_LO     /* FastBlank off (CVBS-Mode) */
DECL|macro|FB_ON
mdefine_line|#define FB_ON&t;SAA7146_GPIO_OUTHI  /* FastBlank on  (RGB-Mode) */
DECL|macro|FB_LOOP
mdefine_line|#define FB_LOOP&t;SAA7146_GPIO_INPUT  /* FastBlank loop-through (PC graphics ???) */
DECL|enum|av7110_video_output_mode
r_enum
id|av7110_video_output_mode
(brace
DECL|enumerator|NO_OUT
id|NO_OUT
op_assign
l_int|0
comma
multiline_comment|/* disable analog output */
DECL|enumerator|CVBS_RGB_OUT
id|CVBS_RGB_OUT
op_assign
l_int|1
comma
DECL|enumerator|CVBS_YC_OUT
id|CVBS_YC_OUT
op_assign
l_int|2
comma
DECL|enumerator|YC_OUT
id|YC_OUT
op_assign
l_int|3
)brace
suffix:semicolon
multiline_comment|/* firmware internal msg q status: */
DECL|macro|GPMQFull
mdefine_line|#define GPMQFull&t;0x0001&t;&t;/* Main Message Queue Full */
DECL|macro|GPMQOver
mdefine_line|#define GPMQOver&t;0x0002&t;&t;/* Main Message Queue Overflow */
DECL|macro|HPQFull
mdefine_line|#define HPQFull&t;&t;0x0004&t;&t;/* High Priority Msg Queue Full */
DECL|macro|HPQOver
mdefine_line|#define HPQOver&t;&t;0x0008
DECL|macro|OSDQFull
mdefine_line|#define OSDQFull&t;0x0010&t;&t;/* OSD Queue Full */
DECL|macro|OSDQOver
mdefine_line|#define OSDQOver&t;0x0020
DECL|macro|GPMQBusy
mdefine_line|#define GPMQBusy&t;0x0040&t;&t;/* Queue not empty, FW &gt;= 261d */
DECL|macro|HPQBusy
mdefine_line|#define HPQBusy&t;&t;0x0080
DECL|macro|OSDQBusy
mdefine_line|#define OSDQBusy&t;0x0100
multiline_comment|/* hw section filter flags */
DECL|macro|SECTION_EIT
mdefine_line|#define&t;SECTION_EIT&t;&t;0x01
DECL|macro|SECTION_SINGLE
mdefine_line|#define&t;SECTION_SINGLE&t;&t;0x00
DECL|macro|SECTION_CYCLE
mdefine_line|#define&t;SECTION_CYCLE&t;&t;0x02
DECL|macro|SECTION_CONTINUOS
mdefine_line|#define&t;SECTION_CONTINUOS&t;0x04
DECL|macro|SECTION_MODE
mdefine_line|#define&t;SECTION_MODE&t;&t;0x06
DECL|macro|SECTION_IPMPE
mdefine_line|#define SECTION_IPMPE&t;&t;0x0C&t;/* size up to 4k */
DECL|macro|SECTION_HIGH_SPEED
mdefine_line|#define SECTION_HIGH_SPEED&t;0x1C&t;/* larger buffer */
DECL|macro|DATA_PIPING_FLAG
mdefine_line|#define DATA_PIPING_FLAG&t;0x20&t;/* for Data Piping Filter */
DECL|macro|PBUFSIZE_NONE
mdefine_line|#define&t;PBUFSIZE_NONE 0x0000
DECL|macro|PBUFSIZE_1P
mdefine_line|#define&t;PBUFSIZE_1P   0x0100
DECL|macro|PBUFSIZE_2P
mdefine_line|#define&t;PBUFSIZE_2P   0x0200
DECL|macro|PBUFSIZE_1K
mdefine_line|#define&t;PBUFSIZE_1K   0x0300
DECL|macro|PBUFSIZE_2K
mdefine_line|#define&t;PBUFSIZE_2K   0x0400
DECL|macro|PBUFSIZE_4K
mdefine_line|#define&t;PBUFSIZE_4K   0x0500
DECL|macro|PBUFSIZE_8K
mdefine_line|#define&t;PBUFSIZE_8K   0x0600
DECL|macro|PBUFSIZE_16K
mdefine_line|#define PBUFSIZE_16K  0x0700
DECL|macro|PBUFSIZE_32K
mdefine_line|#define PBUFSIZE_32K  0x0800
multiline_comment|/* firmware command codes */
DECL|enum|av7110_osd_command
r_enum
id|av7110_osd_command
(brace
DECL|enumerator|WCreate
id|WCreate
comma
DECL|enumerator|WDestroy
id|WDestroy
comma
DECL|enumerator|WMoveD
id|WMoveD
comma
DECL|enumerator|WMoveA
id|WMoveA
comma
DECL|enumerator|WHide
id|WHide
comma
DECL|enumerator|WTop
id|WTop
comma
DECL|enumerator|DBox
id|DBox
comma
DECL|enumerator|DLine
id|DLine
comma
DECL|enumerator|DText
id|DText
comma
DECL|enumerator|Set_Font
id|Set_Font
comma
DECL|enumerator|SetColor
id|SetColor
comma
DECL|enumerator|SetBlend
id|SetBlend
comma
DECL|enumerator|SetWBlend
id|SetWBlend
comma
DECL|enumerator|SetCBlend
id|SetCBlend
comma
DECL|enumerator|SetNonBlend
id|SetNonBlend
comma
DECL|enumerator|LoadBmp
id|LoadBmp
comma
DECL|enumerator|BlitBmp
id|BlitBmp
comma
DECL|enumerator|ReleaseBmp
id|ReleaseBmp
comma
DECL|enumerator|SetWTrans
id|SetWTrans
comma
DECL|enumerator|SetWNoTrans
id|SetWNoTrans
comma
DECL|enumerator|Set_Palette
id|Set_Palette
)brace
suffix:semicolon
DECL|enum|av7110_pid_command
r_enum
id|av7110_pid_command
(brace
DECL|enumerator|MultiPID
id|MultiPID
comma
DECL|enumerator|VideoPID
id|VideoPID
comma
DECL|enumerator|AudioPID
id|AudioPID
comma
DECL|enumerator|InitFilt
id|InitFilt
comma
DECL|enumerator|FiltError
id|FiltError
comma
DECL|enumerator|NewVersion
id|NewVersion
comma
DECL|enumerator|CacheError
id|CacheError
comma
DECL|enumerator|AddPIDFilter
id|AddPIDFilter
comma
DECL|enumerator|DelPIDFilter
id|DelPIDFilter
comma
DECL|enumerator|Scan
id|Scan
comma
DECL|enumerator|SetDescr
id|SetDescr
comma
DECL|enumerator|SetIR
id|SetIR
comma
DECL|enumerator|FlushTSQueue
id|FlushTSQueue
)brace
suffix:semicolon
DECL|enum|av7110_mpeg_command
r_enum
id|av7110_mpeg_command
(brace
DECL|enumerator|SelAudChannels
id|SelAudChannels
)brace
suffix:semicolon
DECL|enum|av7110_audio_command
r_enum
id|av7110_audio_command
(brace
DECL|enumerator|AudioDAC
id|AudioDAC
comma
DECL|enumerator|CabADAC
id|CabADAC
comma
DECL|enumerator|ON22K
id|ON22K
comma
DECL|enumerator|OFF22K
id|OFF22K
comma
DECL|enumerator|MainSwitch
id|MainSwitch
comma
DECL|enumerator|ADSwitch
id|ADSwitch
comma
DECL|enumerator|SendDiSEqC
id|SendDiSEqC
comma
DECL|enumerator|SetRegister
id|SetRegister
)brace
suffix:semicolon
DECL|enum|av7110_request_command
r_enum
id|av7110_request_command
(brace
DECL|enumerator|AudioState
id|AudioState
comma
DECL|enumerator|AudioBuffState
id|AudioBuffState
comma
DECL|enumerator|VideoState1
id|VideoState1
comma
DECL|enumerator|VideoState2
id|VideoState2
comma
DECL|enumerator|VideoState3
id|VideoState3
comma
DECL|enumerator|CrashCounter
id|CrashCounter
comma
DECL|enumerator|ReqVersion
id|ReqVersion
comma
DECL|enumerator|ReqVCXO
id|ReqVCXO
comma
DECL|enumerator|ReqRegister
id|ReqRegister
comma
DECL|enumerator|ReqSecFilterError
id|ReqSecFilterError
comma
DECL|enumerator|ReqSTC
id|ReqSTC
)brace
suffix:semicolon
DECL|enum|av7110_encoder_command
r_enum
id|av7110_encoder_command
(brace
DECL|enumerator|SetVidMode
id|SetVidMode
comma
DECL|enumerator|SetTestMode
id|SetTestMode
comma
DECL|enumerator|LoadVidCode
id|LoadVidCode
comma
DECL|enumerator|SetMonitorType
id|SetMonitorType
comma
DECL|enumerator|SetPanScanType
id|SetPanScanType
comma
DECL|enumerator|SetFreezeMode
id|SetFreezeMode
)brace
suffix:semicolon
DECL|enum|av7110_rec_play_state
r_enum
id|av7110_rec_play_state
(brace
DECL|enumerator|__Record
id|__Record
comma
DECL|enumerator|__Stop
id|__Stop
comma
DECL|enumerator|__Play
id|__Play
comma
DECL|enumerator|__Pause
id|__Pause
comma
DECL|enumerator|__Slow
id|__Slow
comma
DECL|enumerator|__FF_IP
id|__FF_IP
comma
DECL|enumerator|__Scan_I
id|__Scan_I
comma
DECL|enumerator|__Continue
id|__Continue
)brace
suffix:semicolon
DECL|enum|av7110_fw_cmd_misc
r_enum
id|av7110_fw_cmd_misc
(brace
DECL|enumerator|AV7110_FW_VIDEO_ZOOM
id|AV7110_FW_VIDEO_ZOOM
op_assign
l_int|1
comma
DECL|enumerator|AV7110_FW_VIDEO_COMMAND
id|AV7110_FW_VIDEO_COMMAND
comma
DECL|enumerator|AV7110_FW_AUDIO_COMMAND
id|AV7110_FW_AUDIO_COMMAND
)brace
suffix:semicolon
DECL|enum|av7110_command_type
r_enum
id|av7110_command_type
(brace
DECL|enumerator|COMTYPE_NOCOM
id|COMTYPE_NOCOM
comma
DECL|enumerator|COMTYPE_PIDFILTER
id|COMTYPE_PIDFILTER
comma
DECL|enumerator|COMTYPE_MPEGDECODER
id|COMTYPE_MPEGDECODER
comma
DECL|enumerator|COMTYPE_OSD
id|COMTYPE_OSD
comma
DECL|enumerator|COMTYPE_BMP
id|COMTYPE_BMP
comma
DECL|enumerator|COMTYPE_ENCODER
id|COMTYPE_ENCODER
comma
DECL|enumerator|COMTYPE_AUDIODAC
id|COMTYPE_AUDIODAC
comma
DECL|enumerator|COMTYPE_REQUEST
id|COMTYPE_REQUEST
comma
DECL|enumerator|COMTYPE_SYSTEM
id|COMTYPE_SYSTEM
comma
DECL|enumerator|COMTYPE_REC_PLAY
id|COMTYPE_REC_PLAY
comma
DECL|enumerator|COMTYPE_COMMON_IF
id|COMTYPE_COMMON_IF
comma
DECL|enumerator|COMTYPE_PID_FILTER
id|COMTYPE_PID_FILTER
comma
DECL|enumerator|COMTYPE_PES
id|COMTYPE_PES
comma
DECL|enumerator|COMTYPE_TS
id|COMTYPE_TS
comma
DECL|enumerator|COMTYPE_VIDEO
id|COMTYPE_VIDEO
comma
DECL|enumerator|COMTYPE_AUDIO
id|COMTYPE_AUDIO
comma
DECL|enumerator|COMTYPE_CI_LL
id|COMTYPE_CI_LL
comma
DECL|enumerator|COMTYPE_MISC
id|COMTYPE_MISC
op_assign
l_int|0x80
)brace
suffix:semicolon
DECL|macro|VID_NONE_PREF
mdefine_line|#define VID_NONE_PREF&t;&t;0x00&t;/* No aspect ration processing preferred */
DECL|macro|VID_PAN_SCAN_PREF
mdefine_line|#define VID_PAN_SCAN_PREF&t;0x01&t;/* Pan and Scan Display preferred */
DECL|macro|VID_VERT_COMP_PREF
mdefine_line|#define VID_VERT_COMP_PREF&t;0x02&t;/* Vertical compression display preferred */
DECL|macro|VID_VC_AND_PS_PREF
mdefine_line|#define VID_VC_AND_PS_PREF&t;0x03&t;/* PanScan and vertical Compression if allowed */
DECL|macro|VID_CENTRE_CUT_PREF
mdefine_line|#define VID_CENTRE_CUT_PREF&t;0x05&t;/* PanScan with zero vector */
multiline_comment|/* MPEG video decoder commands */
DECL|macro|VIDEO_CMD_STOP
mdefine_line|#define VIDEO_CMD_STOP&t;&t;0x000e
DECL|macro|VIDEO_CMD_PLAY
mdefine_line|#define VIDEO_CMD_PLAY&t;&t;0x000d
DECL|macro|VIDEO_CMD_FREEZE
mdefine_line|#define VIDEO_CMD_FREEZE&t;0x0102
DECL|macro|VIDEO_CMD_FFWD
mdefine_line|#define VIDEO_CMD_FFWD&t;&t;0x0016
DECL|macro|VIDEO_CMD_SLOW
mdefine_line|#define VIDEO_CMD_SLOW&t;&t;0x0022
multiline_comment|/* MPEG audio decoder commands */
DECL|macro|AUDIO_CMD_MUTE
mdefine_line|#define AUDIO_CMD_MUTE&t;&t;0x0001
DECL|macro|AUDIO_CMD_UNMUTE
mdefine_line|#define AUDIO_CMD_UNMUTE&t;0x0002
DECL|macro|AUDIO_CMD_PCM16
mdefine_line|#define AUDIO_CMD_PCM16&t;&t;0x0010
DECL|macro|AUDIO_CMD_STEREO
mdefine_line|#define AUDIO_CMD_STEREO&t;0x0080
DECL|macro|AUDIO_CMD_MONO_L
mdefine_line|#define AUDIO_CMD_MONO_L&t;0x0100
DECL|macro|AUDIO_CMD_MONO_R
mdefine_line|#define AUDIO_CMD_MONO_R&t;0x0200
DECL|macro|AUDIO_CMD_SYNC_OFF
mdefine_line|#define AUDIO_CMD_SYNC_OFF&t;0x000e
DECL|macro|AUDIO_CMD_SYNC_ON
mdefine_line|#define AUDIO_CMD_SYNC_ON&t;0x000f
multiline_comment|/* firmware data interface codes */
DECL|macro|DATA_NONE
mdefine_line|#define DATA_NONE&t;&t; 0x00
DECL|macro|DATA_FSECTION
mdefine_line|#define DATA_FSECTION&t;&t; 0x01
DECL|macro|DATA_IPMPE
mdefine_line|#define DATA_IPMPE&t;&t; 0x02
DECL|macro|DATA_MPEG_RECORD
mdefine_line|#define DATA_MPEG_RECORD&t; 0x03
DECL|macro|DATA_DEBUG_MESSAGE
mdefine_line|#define DATA_DEBUG_MESSAGE&t; 0x04
DECL|macro|DATA_COMMON_INTERFACE
mdefine_line|#define DATA_COMMON_INTERFACE&t; 0x05
DECL|macro|DATA_MPEG_PLAY
mdefine_line|#define DATA_MPEG_PLAY&t;&t; 0x06
DECL|macro|DATA_BMP_LOAD
mdefine_line|#define DATA_BMP_LOAD&t;&t; 0x07
DECL|macro|DATA_IRCOMMAND
mdefine_line|#define DATA_IRCOMMAND&t;&t; 0x08
DECL|macro|DATA_PIPING
mdefine_line|#define DATA_PIPING&t;&t; 0x09
DECL|macro|DATA_STREAMING
mdefine_line|#define DATA_STREAMING&t;&t; 0x0a
DECL|macro|DATA_CI_GET
mdefine_line|#define DATA_CI_GET&t;&t; 0x0b
DECL|macro|DATA_CI_PUT
mdefine_line|#define DATA_CI_PUT&t;&t; 0x0c
DECL|macro|DATA_MPEG_VIDEO_EVENT
mdefine_line|#define DATA_MPEG_VIDEO_EVENT&t; 0x0d
DECL|macro|DATA_PES_RECORD
mdefine_line|#define DATA_PES_RECORD&t;&t; 0x10
DECL|macro|DATA_PES_PLAY
mdefine_line|#define DATA_PES_PLAY&t;&t; 0x11
DECL|macro|DATA_TS_RECORD
mdefine_line|#define DATA_TS_RECORD&t;&t; 0x12
DECL|macro|DATA_TS_PLAY
mdefine_line|#define DATA_TS_PLAY&t;&t; 0x13
multiline_comment|/* ancient CI command codes, only two are actually still used&n; * by the link level CI firmware */
DECL|macro|CI_CMD_ERROR
mdefine_line|#define CI_CMD_ERROR&t;&t; 0x00
DECL|macro|CI_CMD_ACK
mdefine_line|#define CI_CMD_ACK&t;&t; 0x01
DECL|macro|CI_CMD_SYSTEM_READY
mdefine_line|#define CI_CMD_SYSTEM_READY&t; 0x02
DECL|macro|CI_CMD_KEYPRESS
mdefine_line|#define CI_CMD_KEYPRESS&t;&t; 0x03
DECL|macro|CI_CMD_ON_TUNED
mdefine_line|#define CI_CMD_ON_TUNED&t;&t; 0x04
DECL|macro|CI_CMD_ON_SWITCH_PROGRAM
mdefine_line|#define CI_CMD_ON_SWITCH_PROGRAM 0x05
DECL|macro|CI_CMD_SECTION_ARRIVED
mdefine_line|#define CI_CMD_SECTION_ARRIVED&t; 0x06
DECL|macro|CI_CMD_SECTION_TIMEOUT
mdefine_line|#define CI_CMD_SECTION_TIMEOUT&t; 0x07
DECL|macro|CI_CMD_TIME
mdefine_line|#define CI_CMD_TIME&t;&t; 0x08
DECL|macro|CI_CMD_ENTER_MENU
mdefine_line|#define CI_CMD_ENTER_MENU&t; 0x09
DECL|macro|CI_CMD_FAST_PSI
mdefine_line|#define CI_CMD_FAST_PSI&t;&t; 0x0a
DECL|macro|CI_CMD_GET_SLOT_INFO
mdefine_line|#define CI_CMD_GET_SLOT_INFO&t; 0x0b
DECL|macro|CI_MSG_NONE
mdefine_line|#define CI_MSG_NONE&t;&t; 0x00
DECL|macro|CI_MSG_CI_INFO
mdefine_line|#define CI_MSG_CI_INFO&t;&t; 0x01
DECL|macro|CI_MSG_MENU
mdefine_line|#define CI_MSG_MENU&t;&t; 0x02
DECL|macro|CI_MSG_LIST
mdefine_line|#define CI_MSG_LIST&t;&t; 0x03
DECL|macro|CI_MSG_TEXT
mdefine_line|#define CI_MSG_TEXT&t;&t; 0x04
DECL|macro|CI_MSG_REQUEST_INPUT
mdefine_line|#define CI_MSG_REQUEST_INPUT&t; 0x05
DECL|macro|CI_MSG_INPUT_COMPLETE
mdefine_line|#define CI_MSG_INPUT_COMPLETE&t; 0x06
DECL|macro|CI_MSG_LIST_MORE
mdefine_line|#define CI_MSG_LIST_MORE&t; 0x07
DECL|macro|CI_MSG_MENU_MORE
mdefine_line|#define CI_MSG_MENU_MORE&t; 0x08
DECL|macro|CI_MSG_CLOSE_MMI_IMM
mdefine_line|#define CI_MSG_CLOSE_MMI_IMM&t; 0x09
DECL|macro|CI_MSG_SECTION_REQUEST
mdefine_line|#define CI_MSG_SECTION_REQUEST&t; 0x0a
DECL|macro|CI_MSG_CLOSE_FILTER
mdefine_line|#define CI_MSG_CLOSE_FILTER&t; 0x0b
DECL|macro|CI_PSI_COMPLETE
mdefine_line|#define CI_PSI_COMPLETE&t;&t; 0x0c
DECL|macro|CI_MODULE_READY
mdefine_line|#define CI_MODULE_READY&t;&t; 0x0d
DECL|macro|CI_SWITCH_PRG_REPLY
mdefine_line|#define CI_SWITCH_PRG_REPLY&t; 0x0e
DECL|macro|CI_MSG_TEXT_MORE
mdefine_line|#define CI_MSG_TEXT_MORE&t; 0x0f
DECL|macro|CI_MSG_CA_PMT
mdefine_line|#define CI_MSG_CA_PMT&t;&t; 0xe0
DECL|macro|CI_MSG_ERROR
mdefine_line|#define CI_MSG_ERROR&t;&t; 0xf0
multiline_comment|/* base address of the dual ported RAM which serves as communication&n; * area between PCI bus and av7110,&n; * as seen by the DEBI bus of the saa7146 */
DECL|macro|DPRAM_BASE
mdefine_line|#define&t;DPRAM_BASE 0x4000
multiline_comment|/* boot protocol area */
DECL|macro|BOOT_STATE
mdefine_line|#define BOOT_STATE&t;(DPRAM_BASE + 0x3F8)
DECL|macro|BOOT_SIZE
mdefine_line|#define BOOT_SIZE&t;(DPRAM_BASE + 0x3FA)
DECL|macro|BOOT_BASE
mdefine_line|#define BOOT_BASE&t;(DPRAM_BASE + 0x3FC)
DECL|macro|BOOT_BLOCK
mdefine_line|#define BOOT_BLOCK&t;(DPRAM_BASE + 0x400)
DECL|macro|BOOT_MAX_SIZE
mdefine_line|#define BOOT_MAX_SIZE&t;0xc00
multiline_comment|/* firmware command protocol area */
DECL|macro|IRQ_STATE
mdefine_line|#define IRQ_STATE&t;(DPRAM_BASE + 0x0F4)
DECL|macro|IRQ_STATE_EXT
mdefine_line|#define IRQ_STATE_EXT&t;(DPRAM_BASE + 0x0F6)
DECL|macro|MSGSTATE
mdefine_line|#define MSGSTATE&t;(DPRAM_BASE + 0x0F8)
DECL|macro|FILT_STATE
mdefine_line|#define FILT_STATE&t;(DPRAM_BASE + 0x0FA)
DECL|macro|COMMAND
mdefine_line|#define COMMAND&t;&t;(DPRAM_BASE + 0x0FC)
DECL|macro|COM_BUFF
mdefine_line|#define COM_BUFF&t;(DPRAM_BASE + 0x100)
DECL|macro|COM_BUFF_SIZE
mdefine_line|#define COM_BUFF_SIZE&t;0x20
multiline_comment|/* various data buffers */
DECL|macro|BUFF1_BASE
mdefine_line|#define BUFF1_BASE&t;(DPRAM_BASE + 0x120)
DECL|macro|BUFF1_SIZE
mdefine_line|#define BUFF1_SIZE&t;0xE0
DECL|macro|DATA_BUFF0_BASE
mdefine_line|#define DATA_BUFF0_BASE&t;(DPRAM_BASE + 0x200)
DECL|macro|DATA_BUFF0_SIZE
mdefine_line|#define DATA_BUFF0_SIZE&t;0x0800
DECL|macro|DATA_BUFF1_BASE
mdefine_line|#define DATA_BUFF1_BASE&t;(DATA_BUFF0_BASE+DATA_BUFF0_SIZE)
DECL|macro|DATA_BUFF1_SIZE
mdefine_line|#define DATA_BUFF1_SIZE&t;0x0800
DECL|macro|DATA_BUFF2_BASE
mdefine_line|#define DATA_BUFF2_BASE&t;(DATA_BUFF1_BASE+DATA_BUFF1_SIZE)
DECL|macro|DATA_BUFF2_SIZE
mdefine_line|#define DATA_BUFF2_SIZE&t;0x0800
DECL|macro|DATA_BUFF3_BASE
mdefine_line|#define DATA_BUFF3_BASE (DATA_BUFF2_BASE+DATA_BUFF2_SIZE)
DECL|macro|DATA_BUFF3_SIZE
mdefine_line|#define DATA_BUFF3_SIZE 0x0400
DECL|macro|Reserved
mdefine_line|#define Reserved&t;(DPRAM_BASE + 0x1E00)
DECL|macro|Reserved_SIZE
mdefine_line|#define Reserved_SIZE&t;0x1C0
multiline_comment|/* firmware status area */
DECL|macro|STATUS_BASE
mdefine_line|#define STATUS_BASE&t;(DPRAM_BASE + 0x1FC0)
DECL|macro|STATUS_SCR
mdefine_line|#define STATUS_SCR&t;(STATUS_BASE + 0x00)
DECL|macro|STATUS_MODES
mdefine_line|#define STATUS_MODES&t;(STATUS_BASE + 0x04)
DECL|macro|STATUS_LOOPS
mdefine_line|#define STATUS_LOOPS&t;(STATUS_BASE + 0x08)
DECL|macro|STATUS_MPEG_WIDTH
mdefine_line|#define STATUS_MPEG_WIDTH     (STATUS_BASE + 0x0C)
multiline_comment|/* ((aspect_ratio &amp; 0xf) &lt;&lt; 12) | (height &amp; 0xfff) */
DECL|macro|STATUS_MPEG_HEIGHT_AR
mdefine_line|#define STATUS_MPEG_HEIGHT_AR (STATUS_BASE + 0x0E)
multiline_comment|/* firmware data protocol area */
DECL|macro|RX_TYPE
mdefine_line|#define RX_TYPE&t;&t;(DPRAM_BASE + 0x1FE8)
DECL|macro|RX_LEN
mdefine_line|#define RX_LEN&t;&t;(DPRAM_BASE + 0x1FEA)
DECL|macro|TX_TYPE
mdefine_line|#define TX_TYPE&t;&t;(DPRAM_BASE + 0x1FEC)
DECL|macro|TX_LEN
mdefine_line|#define TX_LEN&t;&t;(DPRAM_BASE + 0x1FEE)
DECL|macro|RX_BUFF
mdefine_line|#define RX_BUFF&t;&t;(DPRAM_BASE + 0x1FF4)
DECL|macro|TX_BUFF
mdefine_line|#define TX_BUFF&t;&t;(DPRAM_BASE + 0x1FF6)
DECL|macro|HANDSHAKE_REG
mdefine_line|#define HANDSHAKE_REG&t;(DPRAM_BASE + 0x1FF8)
DECL|macro|COM_IF_LOCK
mdefine_line|#define COM_IF_LOCK&t;(DPRAM_BASE + 0x1FFA)
DECL|macro|IRQ_RX
mdefine_line|#define IRQ_RX&t;&t;(DPRAM_BASE + 0x1FFC)
DECL|macro|IRQ_TX
mdefine_line|#define IRQ_TX&t;&t;(DPRAM_BASE + 0x1FFE)
multiline_comment|/* used by boot protocol to load firmware into av7110 DRAM */
DECL|macro|DRAM_START_CODE
mdefine_line|#define DRAM_START_CODE&t;&t;0x2e000404
DECL|macro|DRAM_MAX_CODE_SIZE
mdefine_line|#define DRAM_MAX_CODE_SIZE&t;0x00100000
multiline_comment|/* saa7146 gpio lines */
DECL|macro|RESET_LINE
mdefine_line|#define RESET_LINE&t;&t;2
DECL|macro|DEBI_DONE_LINE
mdefine_line|#define DEBI_DONE_LINE&t;&t;1
DECL|macro|ARM_IRQ_LINE
mdefine_line|#define ARM_IRQ_LINE&t;&t;0
r_extern
r_void
id|av7110_reset_arm
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_int
id|av7110_bootarm
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
r_extern
r_int
id|av7110_firmversion
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
suffix:semicolon
DECL|macro|FW_CI_LL_SUPPORT
mdefine_line|#define FW_CI_LL_SUPPORT(arm_app) ((arm_app) &amp; 0x80000000)
DECL|macro|FW_4M_SDRAM
mdefine_line|#define FW_4M_SDRAM(arm_app)      ((arm_app) &amp; 0x40000000)
DECL|macro|FW_VERSION
mdefine_line|#define FW_VERSION(arm_app)&t;  ((arm_app) &amp; 0x0000FFFF)
r_extern
r_int
id|av7110_wait_msgstate
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|av7110_fw_cmd
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
r_int
id|type
comma
r_int
id|com
comma
r_int
id|num
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|__av7110_send_fw_cmd
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
op_star
id|buf
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|av7110_send_fw_cmd
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
op_star
id|buf
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|av7110_send_ci_cmd
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|subcom
comma
id|u8
op_star
id|buf
comma
id|u8
id|len
)paren
suffix:semicolon
r_extern
r_int
id|av7110_fw_request
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
op_star
id|request_buf
comma
r_int
id|request_buf_len
comma
id|u16
op_star
id|reply_buf
comma
r_int
id|reply_buf_len
)paren
suffix:semicolon
r_extern
r_int
id|av7110_fw_query
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u16
id|tag
comma
id|u16
op_star
id|Buff
comma
id|s16
id|length
)paren
suffix:semicolon
multiline_comment|/* DEBI (saa7146 data extension bus interface) access */
r_extern
r_int
id|av7110_debiwrite
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
id|u32
id|av7110_debiread
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* DEBI during interrupt */
multiline_comment|/* single word writes */
DECL|function|iwdebi
r_static
r_inline
r_void
id|iwdebi
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
(brace
id|av7110_debiwrite
c_func
(paren
id|av7110
comma
id|config
comma
id|addr
comma
id|val
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* buffer writes */
DECL|function|mwdebi
r_static
r_inline
r_void
id|mwdebi
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
r_char
op_star
id|val
comma
r_int
id|count
)paren
(brace
id|memcpy
c_func
(paren
id|av7110-&gt;debi_virt
comma
id|val
comma
id|count
)paren
suffix:semicolon
id|av7110_debiwrite
c_func
(paren
id|av7110
comma
id|config
comma
id|addr
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|irdebi
r_static
r_inline
id|u32
id|irdebi
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
(brace
id|u32
id|res
suffix:semicolon
id|res
op_assign
id|av7110_debiread
c_func
(paren
id|av7110
comma
id|config
comma
id|addr
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|4
)paren
id|memcpy
c_func
(paren
id|av7110-&gt;debi_virt
comma
(paren
r_char
op_star
)paren
op_amp
id|res
comma
id|count
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* DEBI outside interrupts, only for count &lt;= 4! */
DECL|function|wdebi
r_static
r_inline
r_void
id|wdebi
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
id|av7110_debiwrite
c_func
(paren
id|av7110
comma
id|config
comma
id|addr
comma
id|val
comma
id|count
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|rdebi
r_static
r_inline
id|u32
id|rdebi
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|res
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
id|res
op_assign
id|av7110_debiread
c_func
(paren
id|av7110
comma
id|config
comma
id|addr
comma
id|count
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* handle mailbox registers of the dual ported RAM */
DECL|function|ARM_ResetMailBox
r_static
r_inline
r_void
id|ARM_ResetMailBox
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
id|av7110_debiread
c_func
(paren
id|av7110
comma
id|DEBINOSWAP
comma
id|IRQ_RX
comma
l_int|2
)paren
suffix:semicolon
id|av7110_debiwrite
c_func
(paren
id|av7110
comma
id|DEBINOSWAP
comma
id|IRQ_RX
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|av7110-&gt;debilock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ARM_ClearMailBox
r_static
r_inline
r_void
id|ARM_ClearMailBox
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
(brace
id|iwdebi
c_func
(paren
id|av7110
comma
id|DEBINOSWAP
comma
id|IRQ_RX
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|ARM_ClearIrq
r_static
r_inline
r_void
id|ARM_ClearIrq
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
)paren
(brace
id|irdebi
c_func
(paren
id|av7110
comma
id|DEBINOSWAP
comma
id|IRQ_RX
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; * Firmware commands&n; ****************************************************************************/
DECL|function|SendDAC
r_static
r_inline
r_int
id|SendDAC
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u8
id|addr
comma
id|u8
id|data
)paren
(brace
r_return
id|av7110_fw_cmd
c_func
(paren
id|av7110
comma
id|COMTYPE_AUDIODAC
comma
id|AudioDAC
comma
l_int|2
comma
id|addr
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|av7710_set_video_mode
r_static
r_inline
r_void
id|av7710_set_video_mode
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
r_int
id|mode
)paren
(brace
id|av7110_fw_cmd
c_func
(paren
id|av7110
comma
id|COMTYPE_ENCODER
comma
id|SetVidMode
comma
l_int|1
comma
id|mode
)paren
suffix:semicolon
)brace
DECL|function|vidcom
r_static
r_int
r_inline
id|vidcom
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|com
comma
id|u32
id|arg
)paren
(brace
r_return
id|av7110_fw_cmd
c_func
(paren
id|av7110
comma
id|COMTYPE_MISC
comma
id|AV7110_FW_VIDEO_COMMAND
comma
l_int|4
comma
(paren
id|com
op_rshift
l_int|16
)paren
comma
(paren
id|com
op_amp
l_int|0xffff
)paren
comma
(paren
id|arg
op_rshift
l_int|16
)paren
comma
(paren
id|arg
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
)brace
DECL|function|audcom
r_static
r_int
r_inline
id|audcom
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|com
)paren
(brace
r_return
id|av7110_fw_cmd
c_func
(paren
id|av7110
comma
id|COMTYPE_MISC
comma
id|AV7110_FW_AUDIO_COMMAND
comma
l_int|2
comma
(paren
id|com
op_rshift
l_int|16
)paren
comma
(paren
id|com
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
)brace
DECL|function|Set22K
r_static
r_inline
r_void
id|Set22K
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
r_int
id|state
)paren
(brace
id|av7110_fw_cmd
c_func
(paren
id|av7110
comma
id|COMTYPE_AUDIODAC
comma
(paren
id|state
ques
c_cond
id|ON22K
suffix:colon
id|OFF22K
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_int
id|av7110_diseqc_send
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
r_int
id|len
comma
id|u8
op_star
id|msg
comma
r_int
r_int
id|burst
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DVB_AV7110_OSD
r_extern
r_int
id|av7110_osd_cmd
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|osd_cmd_t
op_star
id|dc
)paren
suffix:semicolon
r_extern
r_int
id|av7110_osd_capability
c_func
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|osd_cap_t
op_star
id|cap
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_DVB_AV7110_OSD */
macro_line|#endif /* _AV7110_HW_H_ */
eof
