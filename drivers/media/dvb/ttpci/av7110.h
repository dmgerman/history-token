macro_line|#ifndef _AV7110_H_
DECL|macro|_AV7110_H_
mdefine_line|#define _AV7110_H_
DECL|macro|DVB_FIRM_PATH
mdefine_line|#define DVB_FIRM_PATH &quot;/lib/DVB/&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#ifdef CONFIG_DEVFS_FS
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#endif
macro_line|#include &lt;media/saa7146_vv.h&gt;
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
DECL|macro|WAIT_QUEUE
mdefine_line|#define WAIT_QUEUE                 wait_queue_head_t
macro_line|#include &lt;linux/dvb/video.h&gt;
macro_line|#include &lt;linux/dvb/audio.h&gt;
macro_line|#include &lt;linux/dvb/dmx.h&gt;
macro_line|#include &lt;linux/dvb/ca.h&gt;
macro_line|#include &lt;linux/dvb/osd.h&gt;
macro_line|#include &lt;linux/dvb/net.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;demux.h&quot;
macro_line|#include &quot;dvb_demux.h&quot;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvb_filter.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;dvb_ringbuffer.h&quot;
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
DECL|enum|av7110_window_display_type
r_enum
id|av7110_window_display_type
(brace
DECL|enumerator|BITMAP1
id|BITMAP1
comma
multiline_comment|/* 1 bit bitmap */
DECL|enumerator|BITMAP2
id|BITMAP2
comma
multiline_comment|/* 2 bit bitmap */
DECL|enumerator|BITMAP4
id|BITMAP4
comma
multiline_comment|/* 4 bit bitmap */
DECL|enumerator|BITMAP8
id|BITMAP8
comma
multiline_comment|/* 8 bit bitmap */
DECL|enumerator|BITMAP1HR
id|BITMAP1HR
comma
multiline_comment|/* 1 Bit bitmap half resolution */
DECL|enumerator|BITMAP2HR
id|BITMAP2HR
comma
multiline_comment|/* 2 bit bitmap half resolution */
DECL|enumerator|BITMAP4HR
id|BITMAP4HR
comma
multiline_comment|/* 4 bit bitmap half resolution */
DECL|enumerator|BITMAP8HR
id|BITMAP8HR
comma
multiline_comment|/* 8 bit bitmap half resolution */
DECL|enumerator|YCRCB422
id|YCRCB422
comma
multiline_comment|/* 4:2:2 YCRCB Graphic Display */
DECL|enumerator|YCRCB444
id|YCRCB444
comma
multiline_comment|/* 4:4:4 YCRCB Graphic Display */
DECL|enumerator|YCRCB444HR
id|YCRCB444HR
comma
multiline_comment|/* 4:4:4 YCRCB graphic half resolution */
DECL|enumerator|VIDEOTSIZE
id|VIDEOTSIZE
comma
multiline_comment|/* True Size Normal MPEG Video Display */
DECL|enumerator|VIDEOHSIZE
id|VIDEOHSIZE
comma
multiline_comment|/* MPEG Video Display Half Resolution */
DECL|enumerator|VIDEOQSIZE
id|VIDEOQSIZE
comma
multiline_comment|/* MPEG Video Display Quarter Resolution */
DECL|enumerator|VIDEODSIZE
id|VIDEODSIZE
comma
multiline_comment|/* MPEG Video Display Double Resolution */
DECL|enumerator|VIDEOTHSIZE
id|VIDEOTHSIZE
comma
multiline_comment|/* True Size MPEG Video Display Half Resolution */
DECL|enumerator|VIDEOTQSIZE
id|VIDEOTQSIZE
comma
multiline_comment|/* True Size MPEG Video Display Quarter Resolution*/
DECL|enumerator|VIDEOTDSIZE
id|VIDEOTDSIZE
comma
multiline_comment|/* True Size MPEG Video Display Double Resolution */
DECL|enumerator|VIDEONSIZE
id|VIDEONSIZE
comma
multiline_comment|/* Full Size MPEG Video Display */
DECL|enumerator|CURSOR
id|CURSOR
multiline_comment|/* Cursor */
)brace
suffix:semicolon
multiline_comment|/* switch defines */
DECL|macro|SB_GPIO
mdefine_line|#define SB_GPIO 3
DECL|macro|SB_OFF
mdefine_line|#define SB_OFF&t;SAA7146_GPIO_OUTLO  
singleline_comment|//SlowBlank aus (TV-Mode)
DECL|macro|SB_ON
mdefine_line|#define SB_ON&t;SAA7146_GPIO_INPUT  
singleline_comment|//SlowBlank an  (AV-Mode)
DECL|macro|SB_WIDE
mdefine_line|#define SB_WIDE SAA7146_GPIO_OUTHI  
singleline_comment|//SlowBlank 6V  (16/9-Mode) nicht realisiert
DECL|macro|FB_GPIO
mdefine_line|#define FB_GPIO 1
DECL|macro|FB_OFF
mdefine_line|#define FB_OFF&t;SAA7146_GPIO_LO     
singleline_comment|//FastBlank aus (CVBS-Mode)
DECL|macro|FB_ON
mdefine_line|#define FB_ON   SAA7146_GPIO_OUTHI  
singleline_comment|//FastBlank an  (RGB-Mode)
DECL|macro|FB_LOOP
mdefine_line|#define FB_LOOP&t;SAA7146_GPIO_INPUT  
singleline_comment|//FastBlank der PC-Grafik durchschleifen
DECL|enum|av7110_video_output_mode
r_enum
id|av7110_video_output_mode
(brace
DECL|enumerator|NO_OUT
id|NO_OUT
op_assign
l_int|0
comma
singleline_comment|//disable analog Output
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
DECL|macro|GPMQFull
mdefine_line|#define GPMQFull        0x0001                  
singleline_comment|//Main Message Queue Full
DECL|macro|GPMQOver
mdefine_line|#define GPMQOver        0x0002                  
singleline_comment|//Main Message Queue Overflow
DECL|macro|HPQFull
mdefine_line|#define HPQFull         0x0004                  
singleline_comment|//High Priority Msg Queue Full
DECL|macro|HPQOver
mdefine_line|#define HPQOver         0x0008
DECL|macro|OSDQFull
mdefine_line|#define OSDQFull        0x0010                  
singleline_comment|//OSD Queue Full
DECL|macro|OSDQOver
mdefine_line|#define OSDQOver        0x0020
DECL|macro|SECTION_EIT
mdefine_line|#define&t;SECTION_EIT&t;        0x01
DECL|macro|SECTION_SINGLE
mdefine_line|#define&t;SECTION_SINGLE&t;        0x00
DECL|macro|SECTION_CYCLE
mdefine_line|#define&t;SECTION_CYCLE&t;&t;0x02
DECL|macro|SECTION_CONTINUOS
mdefine_line|#define&t;SECTION_CONTINUOS&t;0x04
DECL|macro|SECTION_MODE
mdefine_line|#define&t;SECTION_MODE&t;&t;0x06
DECL|macro|SECTION_IPMPE
mdefine_line|#define SECTION_IPMPE&t;&t;0x0C&t;
singleline_comment|// bis zu 4k gro&#xfffd;
DECL|macro|SECTION_HIGH_SPEED
mdefine_line|#define SECTION_HIGH_SPEED&t;0x1C&t;
singleline_comment|// vergr&#xfffd;&#xfffd;erter Puffer f&#xfffd;r High Speed Filter
DECL|macro|DATA_PIPING_FLAG
mdefine_line|#define DATA_PIPING_FLAG&t;0x20&t;
singleline_comment|// f&#xfffd;r Data Piping Filter
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
)brace
suffix:semicolon
DECL|macro|VID_NONE_PREF
mdefine_line|#define VID_NONE_PREF           0x00    /* No aspect ration processing preferred */
DECL|macro|VID_PAN_SCAN_PREF
mdefine_line|#define VID_PAN_SCAN_PREF       0x01    /* Pan and Scan Display preferred */
DECL|macro|VID_VERT_COMP_PREF
mdefine_line|#define VID_VERT_COMP_PREF      0x02    /* Vertical compression display preferred */
DECL|macro|VID_VC_AND_PS_PREF
mdefine_line|#define VID_VC_AND_PS_PREF      0x03    /* PanScan and vertical Compression if allowed */
DECL|macro|VID_CENTRE_CUT_PREF
mdefine_line|#define VID_CENTRE_CUT_PREF     0x05    /* PanScan with zero vector */
DECL|macro|DATA_NONE
mdefine_line|#define DATA_NONE                0x00
DECL|macro|DATA_FSECTION
mdefine_line|#define DATA_FSECTION            0x01
DECL|macro|DATA_IPMPE
mdefine_line|#define DATA_IPMPE               0x02
DECL|macro|DATA_MPEG_RECORD
mdefine_line|#define DATA_MPEG_RECORD         0x03
DECL|macro|DATA_DEBUG_MESSAGE
mdefine_line|#define DATA_DEBUG_MESSAGE       0x04
DECL|macro|DATA_COMMON_INTERFACE
mdefine_line|#define DATA_COMMON_INTERFACE    0x05
DECL|macro|DATA_MPEG_PLAY
mdefine_line|#define DATA_MPEG_PLAY           0x06
DECL|macro|DATA_BMP_LOAD
mdefine_line|#define DATA_BMP_LOAD            0x07
DECL|macro|DATA_IRCOMMAND
mdefine_line|#define DATA_IRCOMMAND           0x08
DECL|macro|DATA_PIPING
mdefine_line|#define DATA_PIPING              0x09
DECL|macro|DATA_STREAMING
mdefine_line|#define DATA_STREAMING           0x0a
DECL|macro|DATA_CI_GET
mdefine_line|#define DATA_CI_GET              0x0b
DECL|macro|DATA_CI_PUT
mdefine_line|#define DATA_CI_PUT              0x0c
DECL|macro|DATA_MPEG_VIDEO_EVENT
mdefine_line|#define DATA_MPEG_VIDEO_EVENT    0x0d
DECL|macro|DATA_PES_RECORD
mdefine_line|#define DATA_PES_RECORD          0x10
DECL|macro|DATA_PES_PLAY
mdefine_line|#define DATA_PES_PLAY            0x11
DECL|macro|DATA_TS_RECORD
mdefine_line|#define DATA_TS_RECORD           0x12
DECL|macro|DATA_TS_PLAY
mdefine_line|#define DATA_TS_PLAY             0x13
DECL|macro|CI_CMD_ERROR
mdefine_line|#define CI_CMD_ERROR             0x00
DECL|macro|CI_CMD_ACK
mdefine_line|#define CI_CMD_ACK               0x01
DECL|macro|CI_CMD_SYSTEM_READY
mdefine_line|#define CI_CMD_SYSTEM_READY      0x02
DECL|macro|CI_CMD_KEYPRESS
mdefine_line|#define CI_CMD_KEYPRESS          0x03
DECL|macro|CI_CMD_ON_TUNED
mdefine_line|#define CI_CMD_ON_TUNED          0x04
DECL|macro|CI_CMD_ON_SWITCH_PROGRAM
mdefine_line|#define CI_CMD_ON_SWITCH_PROGRAM 0x05
DECL|macro|CI_CMD_SECTION_ARRIVED
mdefine_line|#define CI_CMD_SECTION_ARRIVED   0x06
DECL|macro|CI_CMD_SECTION_TIMEOUT
mdefine_line|#define CI_CMD_SECTION_TIMEOUT   0x07
DECL|macro|CI_CMD_TIME
mdefine_line|#define CI_CMD_TIME              0x08
DECL|macro|CI_CMD_ENTER_MENU
mdefine_line|#define CI_CMD_ENTER_MENU        0x09
DECL|macro|CI_CMD_FAST_PSI
mdefine_line|#define CI_CMD_FAST_PSI          0x0a
DECL|macro|CI_CMD_GET_SLOT_INFO
mdefine_line|#define CI_CMD_GET_SLOT_INFO     0x0b
DECL|macro|CI_MSG_NONE
mdefine_line|#define CI_MSG_NONE              0x00
DECL|macro|CI_MSG_CI_INFO
mdefine_line|#define CI_MSG_CI_INFO           0x01
DECL|macro|CI_MSG_MENU
mdefine_line|#define CI_MSG_MENU              0x02
DECL|macro|CI_MSG_LIST
mdefine_line|#define CI_MSG_LIST              0x03
DECL|macro|CI_MSG_TEXT
mdefine_line|#define CI_MSG_TEXT              0x04
DECL|macro|CI_MSG_REQUEST_INPUT
mdefine_line|#define CI_MSG_REQUEST_INPUT     0x05
DECL|macro|CI_MSG_INPUT_COMPLETE
mdefine_line|#define CI_MSG_INPUT_COMPLETE    0x06
DECL|macro|CI_MSG_LIST_MORE
mdefine_line|#define CI_MSG_LIST_MORE         0x07
DECL|macro|CI_MSG_MENU_MORE
mdefine_line|#define CI_MSG_MENU_MORE         0x08
DECL|macro|CI_MSG_CLOSE_MMI_IMM
mdefine_line|#define CI_MSG_CLOSE_MMI_IMM     0x09
DECL|macro|CI_MSG_SECTION_REQUEST
mdefine_line|#define CI_MSG_SECTION_REQUEST   0x0a
DECL|macro|CI_MSG_CLOSE_FILTER
mdefine_line|#define CI_MSG_CLOSE_FILTER      0x0b
DECL|macro|CI_PSI_COMPLETE
mdefine_line|#define CI_PSI_COMPLETE          0x0c
DECL|macro|CI_MODULE_READY
mdefine_line|#define CI_MODULE_READY          0x0d
DECL|macro|CI_SWITCH_PRG_REPLY
mdefine_line|#define CI_SWITCH_PRG_REPLY      0x0e
DECL|macro|CI_MSG_TEXT_MORE
mdefine_line|#define CI_MSG_TEXT_MORE         0x0f
DECL|macro|CI_MSG_CA_PMT
mdefine_line|#define CI_MSG_CA_PMT            0xe0
DECL|macro|CI_MSG_ERROR
mdefine_line|#define CI_MSG_ERROR             0xf0
DECL|macro|PROG_STREAM_MAP
mdefine_line|#define PROG_STREAM_MAP  0xBC
DECL|macro|PRIVATE_STREAM1
mdefine_line|#define PRIVATE_STREAM1  0xBD
DECL|macro|PADDING_STREAM
mdefine_line|#define PADDING_STREAM   0xBE
DECL|macro|PRIVATE_STREAM2
mdefine_line|#define PRIVATE_STREAM2  0xBF
DECL|macro|AUDIO_STREAM_S
mdefine_line|#define AUDIO_STREAM_S   0xC0
DECL|macro|AUDIO_STREAM_E
mdefine_line|#define AUDIO_STREAM_E   0xDF
DECL|macro|VIDEO_STREAM_S
mdefine_line|#define VIDEO_STREAM_S   0xE0
DECL|macro|VIDEO_STREAM_E
mdefine_line|#define VIDEO_STREAM_E   0xEF
DECL|macro|ECM_STREAM
mdefine_line|#define ECM_STREAM       0xF0
DECL|macro|EMM_STREAM
mdefine_line|#define EMM_STREAM       0xF1
DECL|macro|DSM_CC_STREAM
mdefine_line|#define DSM_CC_STREAM    0xF2
DECL|macro|ISO13522_STREAM
mdefine_line|#define ISO13522_STREAM  0xF3
DECL|macro|PROG_STREAM_DIR
mdefine_line|#define PROG_STREAM_DIR  0xFF
DECL|macro|PTS_DTS_FLAGS
mdefine_line|#define PTS_DTS_FLAGS    0xC0
singleline_comment|//pts_dts flags
DECL|macro|PTS_ONLY
mdefine_line|#define PTS_ONLY         0x80
DECL|macro|PTS_DTS
mdefine_line|#define PTS_DTS          0xC0
DECL|macro|TS_SIZE
mdefine_line|#define TS_SIZE          188
DECL|macro|TRANS_ERROR
mdefine_line|#define TRANS_ERROR      0x80
DECL|macro|PAY_START
mdefine_line|#define PAY_START        0x40
DECL|macro|TRANS_PRIO
mdefine_line|#define TRANS_PRIO       0x20
DECL|macro|PID_MASK_HI
mdefine_line|#define PID_MASK_HI      0x1F
singleline_comment|//flags
DECL|macro|TRANS_SCRMBL1
mdefine_line|#define TRANS_SCRMBL1    0x80
DECL|macro|TRANS_SCRMBL2
mdefine_line|#define TRANS_SCRMBL2    0x40
DECL|macro|ADAPT_FIELD
mdefine_line|#define ADAPT_FIELD      0x20
DECL|macro|PAYLOAD
mdefine_line|#define PAYLOAD          0x10
DECL|macro|COUNT_MASK
mdefine_line|#define COUNT_MASK       0x0F
singleline_comment|// adaptation flags
DECL|macro|DISCON_IND
mdefine_line|#define DISCON_IND       0x80
DECL|macro|RAND_ACC_IND
mdefine_line|#define RAND_ACC_IND     0x40
DECL|macro|ES_PRI_IND
mdefine_line|#define ES_PRI_IND       0x20
DECL|macro|PCR_FLAG
mdefine_line|#define PCR_FLAG         0x10
DECL|macro|OPCR_FLAG
mdefine_line|#define OPCR_FLAG        0x08
DECL|macro|SPLICE_FLAG
mdefine_line|#define SPLICE_FLAG      0x04
DECL|macro|TRANS_PRIV
mdefine_line|#define TRANS_PRIV       0x02
DECL|macro|ADAP_EXT_FLAG
mdefine_line|#define ADAP_EXT_FLAG    0x01
singleline_comment|// adaptation extension flags
DECL|macro|LTW_FLAG
mdefine_line|#define LTW_FLAG         0x80
DECL|macro|PIECE_RATE
mdefine_line|#define PIECE_RATE       0x40
DECL|macro|SEAM_SPLICE
mdefine_line|#define SEAM_SPLICE      0x20
DECL|macro|MAX_PLENGTH
mdefine_line|#define MAX_PLENGTH      0xFFFF
DECL|macro|MAX_VID_PES
mdefine_line|#define MAX_VID_PES      0x1FFF
DECL|macro|MY_STATE_PES_START
mdefine_line|#define MY_STATE_PES_START     1
DECL|macro|MY_STATE_PES_STARTED
mdefine_line|#define MY_STATE_PES_STARTED   2
DECL|macro|MY_STATE_FULL
mdefine_line|#define MY_STATE_FULL          4
DECL|macro|MASKL
mdefine_line|#define MASKL   DMX_MAX_FILTER_SIZE
DECL|macro|MAXFILT
mdefine_line|#define MAXFILT 32
DECL|struct|dvb_filter
r_struct
id|dvb_filter
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|ts_state
id|u8
id|ts_state
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|value
id|u8
id|value
(braket
id|MASKL
)braket
suffix:semicolon
DECL|member|mask
id|u8
id|mask
(braket
id|MASKL
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enumerator|AV_PES_STREAM
DECL|enumerator|PS_STREAM
DECL|enumerator|TS_STREAM
DECL|enumerator|PES_STREAM
r_enum
(brace
id|AV_PES_STREAM
comma
id|PS_STREAM
comma
id|TS_STREAM
comma
id|PES_STREAM
)brace
suffix:semicolon
DECL|struct|av7110_p2t
r_struct
id|av7110_p2t
(brace
DECL|member|pes
id|u8
id|pes
(braket
id|TS_SIZE
)braket
suffix:semicolon
DECL|member|counter
id|u8
id|counter
suffix:semicolon
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
DECL|member|frags
r_int
id|frags
suffix:semicolon
DECL|member|feed
r_struct
id|dvb_demux_feed
op_star
id|feed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* video MPEG decoder events: */
multiline_comment|/* (code copied from dvb_frontend.c, should maybe be factored out...) */
DECL|macro|MAX_VIDEO_EVENT
mdefine_line|#define MAX_VIDEO_EVENT 8
DECL|struct|dvb_video_events
r_struct
id|dvb_video_events
(brace
DECL|member|events
r_struct
id|video_event
id|events
(braket
id|MAX_VIDEO_EVENT
)braket
suffix:semicolon
DECL|member|eventw
r_int
id|eventw
suffix:semicolon
DECL|member|eventr
r_int
id|eventr
suffix:semicolon
DECL|member|overflow
r_int
id|overflow
suffix:semicolon
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* place to store all the necessary device information */
DECL|struct|av7110
r_struct
id|av7110
(brace
multiline_comment|/* devices */
DECL|member|dvb_dev
r_struct
id|dvb_device
id|dvb_dev
suffix:semicolon
DECL|member|dvb_net
r_struct
id|dvb_net
id|dvb_net
suffix:semicolon
DECL|member|vd
r_struct
id|video_device
id|vd
suffix:semicolon
DECL|member|dev
r_struct
id|saa7146_dev
op_star
id|dev
suffix:semicolon
DECL|member|i2c_bus
r_struct
id|dvb_i2c_bus
op_star
id|i2c_bus
suffix:semicolon
DECL|member|card_name
r_char
op_star
id|card_name
suffix:semicolon
multiline_comment|/* support for analog module of dvb-c */
DECL|member|has_analog_tuner
r_int
id|has_analog_tuner
suffix:semicolon
DECL|member|current_input
r_int
id|current_input
suffix:semicolon
DECL|member|current_freq
id|u32
id|current_freq
suffix:semicolon
DECL|member|debi_tasklet
r_struct
id|tasklet_struct
id|debi_tasklet
suffix:semicolon
DECL|member|gpio_tasklet
r_struct
id|tasklet_struct
id|gpio_tasklet
suffix:semicolon
DECL|member|adac_type
r_int
id|adac_type
suffix:semicolon
multiline_comment|/* audio DAC type */
DECL|macro|DVB_ADAC_TI
mdefine_line|#define DVB_ADAC_TI       0
DECL|macro|DVB_ADAC_CRYSTAL
mdefine_line|#define DVB_ADAC_CRYSTAL  1
DECL|macro|DVB_ADAC_MSP
mdefine_line|#define DVB_ADAC_MSP      2
DECL|macro|DVB_ADAC_NONE
mdefine_line|#define DVB_ADAC_NONE    -1
multiline_comment|/* buffers */
DECL|member|iobuf
r_void
op_star
id|iobuf
suffix:semicolon
multiline_comment|/* memory for all buffers */
DECL|member|avout
r_struct
id|dvb_ringbuffer
id|avout
suffix:semicolon
multiline_comment|/* buffer for video or A/V mux */
DECL|macro|AVOUTLEN
mdefine_line|#define AVOUTLEN (128*1024)
DECL|member|aout
r_struct
id|dvb_ringbuffer
id|aout
suffix:semicolon
multiline_comment|/* buffer for audio */
DECL|macro|AOUTLEN
mdefine_line|#define AOUTLEN (64*1024)
DECL|member|bmpbuf
r_void
op_star
id|bmpbuf
suffix:semicolon
DECL|macro|BMPLEN
mdefine_line|#define BMPLEN (8*32768+1024)
multiline_comment|/* bitmap buffers and states */
DECL|member|bmpp
r_int
id|bmpp
suffix:semicolon
DECL|member|bmplen
r_int
id|bmplen
suffix:semicolon
DECL|member|bmp_win
r_int
id|bmp_win
suffix:semicolon
DECL|member|bmp_x
DECL|member|bmp_y
id|u16
id|bmp_x
comma
id|bmp_y
suffix:semicolon
DECL|member|bmp_trans
r_int
id|bmp_trans
suffix:semicolon
DECL|member|bmp_state
r_int
id|bmp_state
suffix:semicolon
DECL|macro|BMP_NONE
mdefine_line|#define BMP_NONE     0
DECL|macro|BMP_LOADING
mdefine_line|#define BMP_LOADING  1
DECL|macro|BMP_LOADINGS
mdefine_line|#define BMP_LOADINGS 2
DECL|macro|BMP_LOADED
mdefine_line|#define BMP_LOADED   3
DECL|member|bmpq
id|WAIT_QUEUE
id|bmpq
suffix:semicolon
multiline_comment|/* DEBI and polled command interface */
DECL|member|debilock
id|spinlock_t
id|debilock
suffix:semicolon
DECL|member|dcomlock
r_struct
id|semaphore
id|dcomlock
suffix:semicolon
DECL|member|debitype
r_int
id|debitype
suffix:semicolon
DECL|member|debilen
r_int
id|debilen
suffix:semicolon
DECL|member|debibuf
r_int
id|debibuf
suffix:semicolon
multiline_comment|/* Recording and playback flags */
DECL|member|rec_mode
r_int
id|rec_mode
suffix:semicolon
DECL|member|playing
r_int
id|playing
suffix:semicolon
DECL|macro|RP_NONE
mdefine_line|#define RP_NONE  0
DECL|macro|RP_VIDEO
mdefine_line|#define RP_VIDEO 1
DECL|macro|RP_AUDIO
mdefine_line|#define RP_AUDIO 2
DECL|macro|RP_AV
mdefine_line|#define RP_AV    3
multiline_comment|/* OSD */
DECL|member|osdwin
r_int
id|osdwin
suffix:semicolon
multiline_comment|/* currently active window */
DECL|member|osdbpp
id|u16
id|osdbpp
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* CA */
DECL|member|ci_slot
id|ca_slot_info_t
id|ci_slot
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vidmode
r_int
id|vidmode
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|hw_frontend
r_struct
id|dmx_frontend
id|hw_frontend
suffix:semicolon
DECL|member|mem_frontend
r_struct
id|dmx_frontend
id|mem_frontend
suffix:semicolon
DECL|member|fe_synced
r_int
id|fe_synced
suffix:semicolon
DECL|member|pid_mutex
r_struct
id|semaphore
id|pid_mutex
suffix:semicolon
DECL|member|video_blank
r_int
id|video_blank
suffix:semicolon
DECL|member|videostate
r_struct
id|video_status
id|videostate
suffix:semicolon
DECL|member|display_ar
r_int
id|display_ar
suffix:semicolon
DECL|member|trickmode
r_int
id|trickmode
suffix:semicolon
DECL|macro|TRICK_NONE
mdefine_line|#define TRICK_NONE   0
DECL|macro|TRICK_FAST
mdefine_line|#define TRICK_FAST   1
DECL|macro|TRICK_SLOW
mdefine_line|#define TRICK_SLOW   2
DECL|macro|TRICK_FREEZE
mdefine_line|#define TRICK_FREEZE 3
DECL|member|audiostate
r_struct
id|audio_status
id|audiostate
suffix:semicolon
DECL|member|handle2filter
r_struct
id|dvb_demux_filter
op_star
id|handle2filter
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|p2t_filter
r_struct
id|av7110_p2t
id|p2t_filter
(braket
id|MAXFILT
)braket
suffix:semicolon
DECL|member|p2t
r_struct
id|dvb_filter_pes2ts
id|p2t
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ipack
r_struct
id|ipack
id|ipack
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|kbuf
id|u8
op_star
id|kbuf
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sinfo
r_int
id|sinfo
suffix:semicolon
DECL|member|feeding
r_int
id|feeding
suffix:semicolon
DECL|member|arm_errors
r_int
id|arm_errors
suffix:semicolon
DECL|member|registered
r_int
id|registered
suffix:semicolon
multiline_comment|/* AV711X */
DECL|member|arm_fw
id|u32
id|arm_fw
suffix:semicolon
DECL|member|arm_rtsl
id|u32
id|arm_rtsl
suffix:semicolon
DECL|member|arm_vid
id|u32
id|arm_vid
suffix:semicolon
DECL|member|arm_app
id|u32
id|arm_app
suffix:semicolon
DECL|member|avtype
id|u32
id|avtype
suffix:semicolon
DECL|member|arm_ready
r_int
id|arm_ready
suffix:semicolon
DECL|member|arm_thread
r_struct
id|task_struct
op_star
id|arm_thread
suffix:semicolon
DECL|member|arm_wait
id|WAIT_QUEUE
id|arm_wait
suffix:semicolon
DECL|member|arm_loops
id|u16
id|arm_loops
suffix:semicolon
DECL|member|arm_rmmod
r_int
id|arm_rmmod
suffix:semicolon
DECL|member|debi_virt
r_void
op_star
id|debi_virt
suffix:semicolon
DECL|member|debi_bus
id|dma_addr_t
id|debi_bus
suffix:semicolon
DECL|member|pids
id|u16
id|pids
(braket
id|DMX_PES_OTHER
)braket
suffix:semicolon
DECL|member|ci_rbuffer
r_struct
id|dvb_ringbuffer
id|ci_rbuffer
suffix:semicolon
DECL|member|ci_wbuffer
r_struct
id|dvb_ringbuffer
id|ci_wbuffer
suffix:semicolon
DECL|member|dvb_adapter
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
suffix:semicolon
DECL|member|video_dev
r_struct
id|dvb_device
op_star
id|video_dev
suffix:semicolon
DECL|member|audio_dev
r_struct
id|dvb_device
op_star
id|audio_dev
suffix:semicolon
DECL|member|ca_dev
r_struct
id|dvb_device
op_star
id|ca_dev
suffix:semicolon
DECL|member|osd_dev
r_struct
id|dvb_device
op_star
id|osd_dev
suffix:semicolon
DECL|member|video_events
r_struct
id|dvb_video_events
id|video_events
suffix:semicolon
DECL|member|video_size
id|video_size_t
id|video_size
suffix:semicolon
DECL|member|dsp_dev
r_int
id|dsp_dev
suffix:semicolon
DECL|member|ir_config
id|u32
id|ir_config
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DPRAM_BASE
mdefine_line|#define&t;DPRAM_BASE 0x4000
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
DECL|macro|BUFF1_BASE
mdefine_line|#define BUFF1_BASE&t;(DPRAM_BASE + 0x120)
DECL|macro|BUFF1_SIZE
mdefine_line|#define BUFF1_SIZE&t;0xE0
DECL|macro|DATA_BUFF_BASE
mdefine_line|#define DATA_BUFF_BASE&t;(DPRAM_BASE + 0x200)
DECL|macro|DATA_BUFF_SIZE
mdefine_line|#define DATA_BUFF_SIZE&t;0x1C00
multiline_comment|/* new buffers */
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
DECL|macro|STATUS_BASE
mdefine_line|#define STATUS_BASE&t;(DPRAM_BASE + 0x1FC0)
DECL|macro|STATUS_SCR
mdefine_line|#define STATUS_SCR      (STATUS_BASE + 0x00)
DECL|macro|STATUS_MODES
mdefine_line|#define STATUS_MODES    (STATUS_BASE + 0x04)
DECL|macro|STATUS_LOOPS
mdefine_line|#define STATUS_LOOPS    (STATUS_BASE + 0x08)
DECL|macro|STATUS_MPEG_WIDTH
mdefine_line|#define STATUS_MPEG_WIDTH     (STATUS_BASE + 0x0C)
multiline_comment|/* ((aspect_ratio &amp; 0xf) &lt;&lt; 12) | (height &amp; 0xfff) */
DECL|macro|STATUS_MPEG_HEIGHT_AR
mdefine_line|#define STATUS_MPEG_HEIGHT_AR (STATUS_BASE + 0x0E)
DECL|macro|RX_TYPE
mdefine_line|#define RX_TYPE         (DPRAM_BASE + 0x1FE8)
DECL|macro|RX_LEN
mdefine_line|#define RX_LEN          (DPRAM_BASE + 0x1FEA)
DECL|macro|TX_TYPE
mdefine_line|#define TX_TYPE         (DPRAM_BASE + 0x1FEC)
DECL|macro|TX_LEN
mdefine_line|#define TX_LEN          (DPRAM_BASE + 0x1FEE)
DECL|macro|RX_BUFF
mdefine_line|#define RX_BUFF         (DPRAM_BASE + 0x1FF4)
DECL|macro|TX_BUFF
mdefine_line|#define TX_BUFF &t;(DPRAM_BASE + 0x1FF6)
DECL|macro|HANDSHAKE_REG
mdefine_line|#define HANDSHAKE_REG&t;(DPRAM_BASE + 0x1FF8)
DECL|macro|COM_IF_LOCK
mdefine_line|#define COM_IF_LOCK&t;(DPRAM_BASE + 0x1FFA)
DECL|macro|IRQ_RX
mdefine_line|#define IRQ_RX&t;&t;(DPRAM_BASE + 0x1FFC)
DECL|macro|IRQ_TX
mdefine_line|#define IRQ_TX&t;&t;(DPRAM_BASE + 0x1FFE)
DECL|macro|DRAM_START_CODE
mdefine_line|#define DRAM_START_CODE&t;&t;0x2e000404
DECL|macro|DRAM_MAX_CODE_SIZE
mdefine_line|#define DRAM_MAX_CODE_SIZE&t;0x00100000
DECL|macro|RESET_LINE
mdefine_line|#define RESET_LINE&t;&t;2
DECL|macro|DEBI_DONE_LINE
mdefine_line|#define DEBI_DONE_LINE&t;&t;1
DECL|macro|ARM_IRQ_LINE
mdefine_line|#define ARM_IRQ_LINE&t;&t;0
DECL|macro|DAC_CS
mdefine_line|#define DAC_CS&t;0x8000
DECL|macro|DAC_CDS
mdefine_line|#define DAC_CDS&t;0x0000
r_extern
r_int
r_char
op_star
id|av7110_dpram_addr
comma
op_star
id|av7110_root_addr
suffix:semicolon
r_extern
r_int
id|av7110_dpram_len
comma
id|av7110_root_len
suffix:semicolon
r_extern
r_void
id|av7110_register_irc_handler
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|u32
)paren
)paren
suffix:semicolon
r_extern
r_void
id|av7110_unregister_irc_handler
c_func
(paren
r_void
(paren
op_star
id|func
)paren
(paren
id|u32
)paren
)paren
suffix:semicolon
r_extern
r_void
id|av7110_setup_irc_config
(paren
r_struct
id|av7110
op_star
id|av7110
comma
id|u32
id|ir_config
)paren
suffix:semicolon
r_extern
r_int
id|av7110_ir_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|av7110_ir_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _AV7110_H_ */
eof
