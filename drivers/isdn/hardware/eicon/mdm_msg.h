multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __EICON_MDM_MSG_H__
DECL|macro|__EICON_MDM_MSG_H__
mdefine_line|#define __EICON_MDM_MSG_H__
DECL|macro|DSP_UDATA_INDICATION_DCD_OFF
mdefine_line|#define DSP_UDATA_INDICATION_DCD_OFF  0x01
DECL|macro|DSP_UDATA_INDICATION_DCD_ON
mdefine_line|#define DSP_UDATA_INDICATION_DCD_ON  0x02
DECL|macro|DSP_UDATA_INDICATION_CTS_OFF
mdefine_line|#define DSP_UDATA_INDICATION_CTS_OFF  0x03
DECL|macro|DSP_UDATA_INDICATION_CTS_ON
mdefine_line|#define DSP_UDATA_INDICATION_CTS_ON  0x04
multiline_comment|/* =====================================================================&n;DCD_OFF Message:&n;  &lt;word&gt; time of DCD off (sampled from counter at 8kHz)&n;DCD_ON Message:&n;  &lt;word&gt; time of DCD on (sampled from counter at 8kHz)&n;  &lt;byte&gt; connected norm&n;  &lt;word&gt; connected options&n;  &lt;dword&gt; connected speed (bit/s, max of tx and rx speed)&n;  &lt;word&gt; roundtrip delay (ms)&n;  &lt;dword&gt; connected speed tx (bit/s)&n;  &lt;dword&gt; connected speed rx (bit/s)&n;  Size of this message == 19 bytes, but we will receive only 11&n;  ===================================================================== */
DECL|macro|DSP_CONNECTED_NORM_UNSPECIFIED
mdefine_line|#define DSP_CONNECTED_NORM_UNSPECIFIED      0
DECL|macro|DSP_CONNECTED_NORM_V21
mdefine_line|#define DSP_CONNECTED_NORM_V21              1
DECL|macro|DSP_CONNECTED_NORM_V23
mdefine_line|#define DSP_CONNECTED_NORM_V23              2
DECL|macro|DSP_CONNECTED_NORM_V22
mdefine_line|#define DSP_CONNECTED_NORM_V22              3
DECL|macro|DSP_CONNECTED_NORM_V22_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V22_BIS          4
DECL|macro|DSP_CONNECTED_NORM_V32_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V32_BIS          5
DECL|macro|DSP_CONNECTED_NORM_V34
mdefine_line|#define DSP_CONNECTED_NORM_V34              6
DECL|macro|DSP_CONNECTED_NORM_V8
mdefine_line|#define DSP_CONNECTED_NORM_V8               7
DECL|macro|DSP_CONNECTED_NORM_BELL_212A
mdefine_line|#define DSP_CONNECTED_NORM_BELL_212A        8
DECL|macro|DSP_CONNECTED_NORM_BELL_103
mdefine_line|#define DSP_CONNECTED_NORM_BELL_103         9
DECL|macro|DSP_CONNECTED_NORM_V29_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V29_LEASED_LINE  10
DECL|macro|DSP_CONNECTED_NORM_V33_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V33_LEASED_LINE  11
DECL|macro|DSP_CONNECTED_NORM_V90
mdefine_line|#define DSP_CONNECTED_NORM_V90              12
DECL|macro|DSP_CONNECTED_NORM_V21_CH2
mdefine_line|#define DSP_CONNECTED_NORM_V21_CH2          13
DECL|macro|DSP_CONNECTED_NORM_V27_TER
mdefine_line|#define DSP_CONNECTED_NORM_V27_TER          14
DECL|macro|DSP_CONNECTED_NORM_V29
mdefine_line|#define DSP_CONNECTED_NORM_V29              15
DECL|macro|DSP_CONNECTED_NORM_V33
mdefine_line|#define DSP_CONNECTED_NORM_V33              16
DECL|macro|DSP_CONNECTED_NORM_V17
mdefine_line|#define DSP_CONNECTED_NORM_V17              17
DECL|macro|DSP_CONNECTED_NORM_V32
mdefine_line|#define DSP_CONNECTED_NORM_V32              18
DECL|macro|DSP_CONNECTED_NORM_K56_FLEX
mdefine_line|#define DSP_CONNECTED_NORM_K56_FLEX         19
DECL|macro|DSP_CONNECTED_NORM_X2
mdefine_line|#define DSP_CONNECTED_NORM_X2               20
DECL|macro|DSP_CONNECTED_NORM_V18
mdefine_line|#define DSP_CONNECTED_NORM_V18              21
DECL|macro|DSP_CONNECTED_NORM_V18_LOW_HIGH
mdefine_line|#define DSP_CONNECTED_NORM_V18_LOW_HIGH     22
DECL|macro|DSP_CONNECTED_NORM_V18_HIGH_LOW
mdefine_line|#define DSP_CONNECTED_NORM_V18_HIGH_LOW     23
DECL|macro|DSP_CONNECTED_NORM_V21_LOW_HIGH
mdefine_line|#define DSP_CONNECTED_NORM_V21_LOW_HIGH     24
DECL|macro|DSP_CONNECTED_NORM_V21_HIGH_LOW
mdefine_line|#define DSP_CONNECTED_NORM_V21_HIGH_LOW     25
DECL|macro|DSP_CONNECTED_NORM_BELL103_LOW_HIGH
mdefine_line|#define DSP_CONNECTED_NORM_BELL103_LOW_HIGH 26
DECL|macro|DSP_CONNECTED_NORM_BELL103_HIGH_LOW
mdefine_line|#define DSP_CONNECTED_NORM_BELL103_HIGH_LOW 27
DECL|macro|DSP_CONNECTED_NORM_V23_75_1200
mdefine_line|#define DSP_CONNECTED_NORM_V23_75_1200      28
DECL|macro|DSP_CONNECTED_NORM_V23_1200_75
mdefine_line|#define DSP_CONNECTED_NORM_V23_1200_75      29
DECL|macro|DSP_CONNECTED_NORM_EDT_110
mdefine_line|#define DSP_CONNECTED_NORM_EDT_110          30
DECL|macro|DSP_CONNECTED_NORM_BAUDOT_45
mdefine_line|#define DSP_CONNECTED_NORM_BAUDOT_45        31
DECL|macro|DSP_CONNECTED_NORM_BAUDOT_47
mdefine_line|#define DSP_CONNECTED_NORM_BAUDOT_47        32
DECL|macro|DSP_CONNECTED_NORM_BAUDOT_50
mdefine_line|#define DSP_CONNECTED_NORM_BAUDOT_50        33
DECL|macro|DSP_CONNECTED_NORM_DTMF
mdefine_line|#define DSP_CONNECTED_NORM_DTMF             34
DECL|macro|DSP_CONNECTED_NORM_V18_RESERVED_13
mdefine_line|#define DSP_CONNECTED_NORM_V18_RESERVED_13  35
DECL|macro|DSP_CONNECTED_NORM_V18_RESERVED_14
mdefine_line|#define DSP_CONNECTED_NORM_V18_RESERVED_14  36
DECL|macro|DSP_CONNECTED_NORM_V18_RESERVED_15
mdefine_line|#define DSP_CONNECTED_NORM_V18_RESERVED_15  37
DECL|macro|DSP_CONNECTED_NORM_VOWN
mdefine_line|#define DSP_CONNECTED_NORM_VOWN             38
DECL|macro|DSP_CONNECTED_NORM_V23_OFF_HOOK
mdefine_line|#define DSP_CONNECTED_NORM_V23_OFF_HOOK     39
DECL|macro|DSP_CONNECTED_NORM_V23_ON_HOOK
mdefine_line|#define DSP_CONNECTED_NORM_V23_ON_HOOK      40
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_3
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_3  41
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_4
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_4  42
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_5
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_5  43
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_6
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_6  44
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_7
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_7  45
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_8
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_8  46
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_9
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_9  47
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_10
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_10 48
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_11
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_11 49
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_12
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_12 50
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_13
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_13 51
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_14
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_14 52
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_15
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_15 53
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_16
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_16 54
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_17
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_17 55
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_18
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_18 56
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_19
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_19 57
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_20
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_20 58
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_21
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_21 59
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_22
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_22 60
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_23
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_23 61
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_24
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_24 62
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_25
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_25 63
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_26
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_26 64
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_27
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_27 65
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_28
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_28 66
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_29
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_29 67
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_30
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_30 68
DECL|macro|DSP_CONNECTED_NORM_VOWN_RESERVED_31
mdefine_line|#define DSP_CONNECTED_NORM_VOWN_RESERVED_31 69
DECL|macro|DSP_CONNECTED_OPTION_TRELLIS
mdefine_line|#define DSP_CONNECTED_OPTION_TRELLIS             0x0001
DECL|macro|DSP_CONNECTED_OPTION_V42_TRANS
mdefine_line|#define DSP_CONNECTED_OPTION_V42_TRANS           0x0002
DECL|macro|DSP_CONNECTED_OPTION_V42_LAPM
mdefine_line|#define DSP_CONNECTED_OPTION_V42_LAPM            0x0004
DECL|macro|DSP_CONNECTED_OPTION_SHORT_TRAIN
mdefine_line|#define DSP_CONNECTED_OPTION_SHORT_TRAIN         0x0008
DECL|macro|DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT
mdefine_line|#define DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT 0x0010
DECL|macro|DSP_CONNECTED_OPTION_V42BIS
mdefine_line|#define DSP_CONNECTED_OPTION_V42BIS              0x0020
DECL|macro|DSP_CONNECTED_OPTION_MNP2
mdefine_line|#define DSP_CONNECTED_OPTION_MNP2                0x0040
DECL|macro|DSP_CONNECTED_OPTION_MNP3
mdefine_line|#define DSP_CONNECTED_OPTION_MNP3                0x0080
DECL|macro|DSP_CONNECTED_OPTION_MNP4
mdefine_line|#define DSP_CONNECTED_OPTION_MNP4                0x00c0
DECL|macro|DSP_CONNECTED_OPTION_MNP5
mdefine_line|#define DSP_CONNECTED_OPTION_MNP5                0x0100
DECL|macro|DSP_CONNECTED_OPTION_MNP10
mdefine_line|#define DSP_CONNECTED_OPTION_MNP10               0x0200
DECL|macro|DSP_CONNECTED_OPTION_MASK_V42
mdefine_line|#define DSP_CONNECTED_OPTION_MASK_V42            0x0024
DECL|macro|DSP_CONNECTED_OPTION_MASK_MNP
mdefine_line|#define DSP_CONNECTED_OPTION_MASK_MNP            0x03c0
DECL|macro|DSP_CONNECTED_OPTION_MASK_ERROR_CORRECT
mdefine_line|#define DSP_CONNECTED_OPTION_MASK_ERROR_CORRECT  0x03e4
DECL|macro|DSP_CONNECTED_OPTION_MASK_COMPRESSION
mdefine_line|#define DSP_CONNECTED_OPTION_MASK_COMPRESSION    0x0320
DECL|macro|DSP_UDATA_INDICATION_DISCONNECT
mdefine_line|#define DSP_UDATA_INDICATION_DISCONNECT         5
multiline_comment|/*&n;returns:&n;  &lt;byte&gt; cause&n;*/
multiline_comment|/* ==========================================================&n;    DLC: B2 modem configuration&n;   ========================================================== */
multiline_comment|/*&n;Fields in assign DLC information element for modem protocol V.42/MNP:&n;  &lt;byte&gt; length of information element&n;  &lt;word&gt; information field length&n;  &lt;byte&gt; address A       (not used, default 3)&n;  &lt;byte&gt; address B       (not used, default 1)&n;  &lt;byte&gt; modulo mode     (not used, default 7)&n;  &lt;byte&gt; window size     (not used, default 7)&n;  &lt;word&gt; XID length      (not used, default 0)&n;  ...    XID information (not used, default empty)&n;  &lt;byte&gt; modem protocol negotiation options&n;  &lt;byte&gt; modem protocol options&n;  &lt;byte&gt; modem protocol break configuration&n;  &lt;byte&gt; modem protocol application options&n;*/
DECL|macro|DLC_MODEMPROT_DISABLE_V42_V42BIS
mdefine_line|#define DLC_MODEMPROT_DISABLE_V42_V42BIS     0x01
DECL|macro|DLC_MODEMPROT_DISABLE_MNP_MNP5
mdefine_line|#define DLC_MODEMPROT_DISABLE_MNP_MNP5       0x02
DECL|macro|DLC_MODEMPROT_REQUIRE_PROTOCOL
mdefine_line|#define DLC_MODEMPROT_REQUIRE_PROTOCOL       0x04
DECL|macro|DLC_MODEMPROT_DISABLE_V42_DETECT
mdefine_line|#define DLC_MODEMPROT_DISABLE_V42_DETECT     0x08
DECL|macro|DLC_MODEMPROT_DISABLE_COMPRESSION
mdefine_line|#define DLC_MODEMPROT_DISABLE_COMPRESSION    0x10
DECL|macro|DLC_MODEMPROT_REQUIRE_PROTOCOL_V34UP
mdefine_line|#define DLC_MODEMPROT_REQUIRE_PROTOCOL_V34UP 0x20
DECL|macro|DLC_MODEMPROT_NO_PROTOCOL_IF_1200
mdefine_line|#define DLC_MODEMPROT_NO_PROTOCOL_IF_1200    0x01
DECL|macro|DLC_MODEMPROT_BUFFER_IN_V42_DETECT
mdefine_line|#define DLC_MODEMPROT_BUFFER_IN_V42_DETECT   0x02
DECL|macro|DLC_MODEMPROT_DISABLE_V42_SREJ
mdefine_line|#define DLC_MODEMPROT_DISABLE_V42_SREJ       0x04
DECL|macro|DLC_MODEMPROT_DISABLE_MNP3
mdefine_line|#define DLC_MODEMPROT_DISABLE_MNP3           0x08
DECL|macro|DLC_MODEMPROT_DISABLE_MNP4
mdefine_line|#define DLC_MODEMPROT_DISABLE_MNP4           0x10
DECL|macro|DLC_MODEMPROT_DISABLE_MNP10
mdefine_line|#define DLC_MODEMPROT_DISABLE_MNP10          0x20
DECL|macro|DLC_MODEMPROT_NO_PROTOCOL_IF_V22BIS
mdefine_line|#define DLC_MODEMPROT_NO_PROTOCOL_IF_V22BIS  0x40
DECL|macro|DLC_MODEMPROT_NO_PROTOCOL_IF_V32BIS
mdefine_line|#define DLC_MODEMPROT_NO_PROTOCOL_IF_V32BIS  0x80
DECL|macro|DLC_MODEMPROT_BREAK_DISABLED
mdefine_line|#define DLC_MODEMPROT_BREAK_DISABLED         0x00
DECL|macro|DLC_MODEMPROT_BREAK_NORMAL
mdefine_line|#define DLC_MODEMPROT_BREAK_NORMAL           0x01
DECL|macro|DLC_MODEMPROT_BREAK_EXPEDITED
mdefine_line|#define DLC_MODEMPROT_BREAK_EXPEDITED        0x02
DECL|macro|DLC_MODEMPROT_BREAK_DESTRUCTIVE
mdefine_line|#define DLC_MODEMPROT_BREAK_DESTRUCTIVE      0x03
DECL|macro|DLC_MODEMPROT_BREAK_CONFIG_MASK
mdefine_line|#define DLC_MODEMPROT_BREAK_CONFIG_MASK      0x03
DECL|macro|DLC_MODEMPROT_APPL_EARLY_CONNECT
mdefine_line|#define DLC_MODEMPROT_APPL_EARLY_CONNECT     0x01
DECL|macro|DLC_MODEMPROT_APPL_PASS_INDICATIONS
mdefine_line|#define DLC_MODEMPROT_APPL_PASS_INDICATIONS  0x02
multiline_comment|/* ==========================================================&n;    CAI parameters used for the modem L1 configuration&n;   ========================================================== */
multiline_comment|/*&n;Fields in assign CAI information element:&n;  &lt;byte&gt; length of information element&n;  &lt;byte&gt; info field and B-channel hardware&n;  &lt;byte&gt; rate adaptation bit rate&n;  &lt;byte&gt; async framing parameters&n;  &lt;byte&gt; reserved&n;  &lt;word&gt; packet length&n;  &lt;byte&gt; modem line taking options&n;  &lt;byte&gt; modem modulation negotiation parameters&n;  &lt;byte&gt; modem modulation options&n;  &lt;byte&gt; modem disabled modulations mask low&n;  &lt;byte&gt; modem disabled modulations mask high&n;  &lt;byte&gt; modem enabled modulations mask&n;  &lt;word&gt; modem min TX speed&n;  &lt;word&gt; modem max TX speed&n;  &lt;word&gt; modem min RX speed&n;  &lt;word&gt; modem max RX speed&n;  &lt;byte&gt; modem disabled symbol rates mask&n;  &lt;byte&gt; modem info options mask&n;  &lt;byte&gt; modem transmit level adjust&n;  &lt;byte&gt; modem speaker parameters&n;  &lt;word&gt; modem private debug config&n;  &lt;struct&gt; modem reserved&n;  &lt;struct&gt; v18 config parameters&n;  &lt;struct&gt; v18 probing sequence&n;  &lt;struct&gt; v18 probing message&n;*/
DECL|macro|DSP_CAI_HARDWARE_HDLC_64K
mdefine_line|#define DSP_CAI_HARDWARE_HDLC_64K          0x05
DECL|macro|DSP_CAI_HARDWARE_HDLC_56K
mdefine_line|#define DSP_CAI_HARDWARE_HDLC_56K          0x08
DECL|macro|DSP_CAI_HARDWARE_TRANSP
mdefine_line|#define DSP_CAI_HARDWARE_TRANSP            0x09
DECL|macro|DSP_CAI_HARDWARE_V110_SYNC
mdefine_line|#define DSP_CAI_HARDWARE_V110_SYNC         0x0c
DECL|macro|DSP_CAI_HARDWARE_V110_ASYNC
mdefine_line|#define DSP_CAI_HARDWARE_V110_ASYNC        0x0d
DECL|macro|DSP_CAI_HARDWARE_HDLC_128K
mdefine_line|#define DSP_CAI_HARDWARE_HDLC_128K         0x0f
DECL|macro|DSP_CAI_HARDWARE_FAX
mdefine_line|#define DSP_CAI_HARDWARE_FAX               0x10
DECL|macro|DSP_CAI_HARDWARE_MODEM_ASYNC
mdefine_line|#define DSP_CAI_HARDWARE_MODEM_ASYNC       0x11
DECL|macro|DSP_CAI_HARDWARE_MODEM_SYNC
mdefine_line|#define DSP_CAI_HARDWARE_MODEM_SYNC        0x12
DECL|macro|DSP_CAI_HARDWARE_V110_HDLCA
mdefine_line|#define DSP_CAI_HARDWARE_V110_HDLCA        0x13
DECL|macro|DSP_CAI_HARDWARE_ADVANCED_VOICE
mdefine_line|#define DSP_CAI_HARDWARE_ADVANCED_VOICE    0x14
DECL|macro|DSP_CAI_HARDWARE_TRANSP_DTMF
mdefine_line|#define DSP_CAI_HARDWARE_TRANSP_DTMF       0x16
DECL|macro|DSP_CAI_HARDWARE_DTMF_VOICE_ISDN
mdefine_line|#define DSP_CAI_HARDWARE_DTMF_VOICE_ISDN   0x17
DECL|macro|DSP_CAI_HARDWARE_DTMF_VOICE_LOCAL
mdefine_line|#define DSP_CAI_HARDWARE_DTMF_VOICE_LOCAL  0x18
DECL|macro|DSP_CAI_HARDWARE_MASK
mdefine_line|#define DSP_CAI_HARDWARE_MASK              0x3f
DECL|macro|DSP_CAI_ENABLE_INFO_INDICATIONS
mdefine_line|#define DSP_CAI_ENABLE_INFO_INDICATIONS    0x80
DECL|macro|DSP_CAI_RATE_ADAPTATION_300
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_300        0x00
DECL|macro|DSP_CAI_RATE_ADAPTATION_600
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_600        0x01
DECL|macro|DSP_CAI_RATE_ADAPTATION_1200
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_1200       0x02
DECL|macro|DSP_CAI_RATE_ADAPTATION_2400
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_2400       0x03
DECL|macro|DSP_CAI_RATE_ADAPTATION_4800
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_4800       0x04
DECL|macro|DSP_CAI_RATE_ADAPTATION_9600
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_9600       0x05
DECL|macro|DSP_CAI_RATE_ADAPTATION_19200
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_19200      0x06
DECL|macro|DSP_CAI_RATE_ADAPTATION_38400
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_38400      0x07
DECL|macro|DSP_CAI_RATE_ADAPTATION_48000
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_48000      0x08
DECL|macro|DSP_CAI_RATE_ADAPTATION_56000
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_56000      0x09
DECL|macro|DSP_CAI_RATE_ADAPTATION_7200
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_7200       0x0a
DECL|macro|DSP_CAI_RATE_ADAPTATION_14400
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_14400      0x0b
DECL|macro|DSP_CAI_RATE_ADAPTATION_28800
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_28800      0x0c
DECL|macro|DSP_CAI_RATE_ADAPTATION_12000
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_12000      0x0d
DECL|macro|DSP_CAI_RATE_ADAPTATION_1200_75
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_1200_75    0x0e
DECL|macro|DSP_CAI_RATE_ADAPTATION_75_1200
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_75_1200    0x0f
DECL|macro|DSP_CAI_RATE_ADAPTATION_MASK
mdefine_line|#define DSP_CAI_RATE_ADAPTATION_MASK       0x0f
DECL|macro|DSP_CAI_ASYNC_PARITY_ENABLE
mdefine_line|#define DSP_CAI_ASYNC_PARITY_ENABLE        0x01
DECL|macro|DSP_CAI_ASYNC_PARITY_SPACE
mdefine_line|#define DSP_CAI_ASYNC_PARITY_SPACE         0x00
DECL|macro|DSP_CAI_ASYNC_PARITY_ODD
mdefine_line|#define DSP_CAI_ASYNC_PARITY_ODD           0x02
DECL|macro|DSP_CAI_ASYNC_PARITY_EVEN
mdefine_line|#define DSP_CAI_ASYNC_PARITY_EVEN          0x04
DECL|macro|DSP_CAI_ASYNC_PARITY_MARK
mdefine_line|#define DSP_CAI_ASYNC_PARITY_MARK          0x06
DECL|macro|DSP_CAI_ASYNC_PARITY_MASK
mdefine_line|#define DSP_CAI_ASYNC_PARITY_MASK          0x06
DECL|macro|DSP_CAI_ASYNC_ONE_STOP_BIT
mdefine_line|#define DSP_CAI_ASYNC_ONE_STOP_BIT         0x00
DECL|macro|DSP_CAI_ASYNC_TWO_STOP_BITS
mdefine_line|#define DSP_CAI_ASYNC_TWO_STOP_BITS        0x20
DECL|macro|DSP_CAI_ASYNC_CHAR_LENGTH_8
mdefine_line|#define DSP_CAI_ASYNC_CHAR_LENGTH_8        0x00
DECL|macro|DSP_CAI_ASYNC_CHAR_LENGTH_7
mdefine_line|#define DSP_CAI_ASYNC_CHAR_LENGTH_7        0x40
DECL|macro|DSP_CAI_ASYNC_CHAR_LENGTH_6
mdefine_line|#define DSP_CAI_ASYNC_CHAR_LENGTH_6        0x80
DECL|macro|DSP_CAI_ASYNC_CHAR_LENGTH_5
mdefine_line|#define DSP_CAI_ASYNC_CHAR_LENGTH_5        0xc0
DECL|macro|DSP_CAI_ASYNC_CHAR_LENGTH_MASK
mdefine_line|#define DSP_CAI_ASYNC_CHAR_LENGTH_MASK     0xc0
DECL|macro|DSP_CAI_MODEM_LEASED_LINE_MODE
mdefine_line|#define DSP_CAI_MODEM_LEASED_LINE_MODE     0x01
DECL|macro|DSP_CAI_MODEM_4_WIRE_OPERATION
mdefine_line|#define DSP_CAI_MODEM_4_WIRE_OPERATION     0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_BUSY_DETECT
mdefine_line|#define DSP_CAI_MODEM_DISABLE_BUSY_DETECT  0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_CALLING_TONE
mdefine_line|#define DSP_CAI_MODEM_DISABLE_CALLING_TONE 0x08
DECL|macro|DSP_CAI_MODEM_DISABLE_ANSWER_TONE
mdefine_line|#define DSP_CAI_MODEM_DISABLE_ANSWER_TONE  0x10
DECL|macro|DSP_CAI_MODEM_ENABLE_DIAL_TONE_DET
mdefine_line|#define DSP_CAI_MODEM_ENABLE_DIAL_TONE_DET 0x20
DECL|macro|DSP_CAI_MODEM_USE_POTS_INTERFACE
mdefine_line|#define DSP_CAI_MODEM_USE_POTS_INTERFACE   0x40
DECL|macro|DSP_CAI_MODEM_FORCE_RAY_TAYLOR_FAX
mdefine_line|#define DSP_CAI_MODEM_FORCE_RAY_TAYLOR_FAX 0x80
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_HIGHEST
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_HIGHEST    0x00
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_DISABLED
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_DISABLED   0x01
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_IN_CLASS
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_IN_CLASS   0x02
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_V100
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_V100       0x03
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_V8
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_V8         0x04
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_V8BIS
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_V8BIS      0x05
DECL|macro|DSP_CAI_MODEM_NEGOTIATE_MASK
mdefine_line|#define DSP_CAI_MODEM_NEGOTIATE_MASK       0x07
DECL|macro|DSP_CAI_MODEM_GUARD_TONE_NONE
mdefine_line|#define DSP_CAI_MODEM_GUARD_TONE_NONE      0x00
DECL|macro|DSP_CAI_MODEM_GUARD_TONE_550HZ
mdefine_line|#define DSP_CAI_MODEM_GUARD_TONE_550HZ     0x40
DECL|macro|DSP_CAI_MODEM_GUARD_TONE_1800HZ
mdefine_line|#define DSP_CAI_MODEM_GUARD_TONE_1800HZ    0x80
DECL|macro|DSP_CAI_MODEM_GUARD_TONE_MASK
mdefine_line|#define DSP_CAI_MODEM_GUARD_TONE_MASK      0xc0
DECL|macro|DSP_CAI_MODEM_DISABLE_RETRAIN
mdefine_line|#define DSP_CAI_MODEM_DISABLE_RETRAIN      0x01
DECL|macro|DSP_CAI_MODEM_DISABLE_STEPUPDOWN
mdefine_line|#define DSP_CAI_MODEM_DISABLE_STEPUPDOWN   0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_SPLIT_SPEED
mdefine_line|#define DSP_CAI_MODEM_DISABLE_SPLIT_SPEED  0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_TRELLIS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_TRELLIS      0x08
DECL|macro|DSP_CAI_MODEM_ALLOW_RDL_TEST_LOOP
mdefine_line|#define DSP_CAI_MODEM_ALLOW_RDL_TEST_LOOP  0x10
DECL|macro|DSP_CAI_MODEM_DISABLE_FLUSH_TIMER
mdefine_line|#define DSP_CAI_MODEM_DISABLE_FLUSH_TIMER  0x40
DECL|macro|DSP_CAI_MODEM_REVERSE_DIRECTION
mdefine_line|#define DSP_CAI_MODEM_REVERSE_DIRECTION    0x80
DECL|macro|DSP_CAI_MODEM_DISABLE_V21
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V21          0x01
DECL|macro|DSP_CAI_MODEM_DISABLE_V23
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V23          0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_V22
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V22          0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_V22BIS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V22BIS       0x08
DECL|macro|DSP_CAI_MODEM_DISABLE_V32
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V32          0x10
DECL|macro|DSP_CAI_MODEM_DISABLE_V32BIS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V32BIS       0x20
DECL|macro|DSP_CAI_MODEM_DISABLE_V34
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V34          0x40
DECL|macro|DSP_CAI_MODEM_DISABLE_V90
mdefine_line|#define DSP_CAI_MODEM_DISABLE_V90          0x80
DECL|macro|DSP_CAI_MODEM_DISABLE_BELL103
mdefine_line|#define DSP_CAI_MODEM_DISABLE_BELL103      0x01
DECL|macro|DSP_CAI_MODEM_DISABLE_BELL212A
mdefine_line|#define DSP_CAI_MODEM_DISABLE_BELL212A     0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_VFC
mdefine_line|#define DSP_CAI_MODEM_DISABLE_VFC          0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_K56FLEX
mdefine_line|#define DSP_CAI_MODEM_DISABLE_K56FLEX      0x08
DECL|macro|DSP_CAI_MODEM_DISABLE_X2
mdefine_line|#define DSP_CAI_MODEM_DISABLE_X2           0x10
DECL|macro|DSP_CAI_MODEM_ENABLE_V29FDX
mdefine_line|#define DSP_CAI_MODEM_ENABLE_V29FDX        0x01
DECL|macro|DSP_CAI_MODEM_ENABLE_V33
mdefine_line|#define DSP_CAI_MODEM_ENABLE_V33           0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_2400_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_2400_SYMBOLS 0x01
DECL|macro|DSP_CAI_MODEM_DISABLE_2743_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_2743_SYMBOLS 0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_2800_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_2800_SYMBOLS 0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_3000_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_3000_SYMBOLS 0x08
DECL|macro|DSP_CAI_MODEM_DISABLE_3200_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_3200_SYMBOLS 0x10
DECL|macro|DSP_CAI_MODEM_DISABLE_3429_SYMBOLS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_3429_SYMBOLS 0x20
DECL|macro|DSP_CAI_MODEM_DISABLE_TX_REDUCTION
mdefine_line|#define DSP_CAI_MODEM_DISABLE_TX_REDUCTION 0x01
DECL|macro|DSP_CAI_MODEM_DISABLE_PRECODING
mdefine_line|#define DSP_CAI_MODEM_DISABLE_PRECODING    0x02
DECL|macro|DSP_CAI_MODEM_DISABLE_PREEMPHASIS
mdefine_line|#define DSP_CAI_MODEM_DISABLE_PREEMPHASIS  0x04
DECL|macro|DSP_CAI_MODEM_DISABLE_SHAPING
mdefine_line|#define DSP_CAI_MODEM_DISABLE_SHAPING      0x08
DECL|macro|DSP_CAI_MODEM_DISABLE_NONLINEAR_EN
mdefine_line|#define DSP_CAI_MODEM_DISABLE_NONLINEAR_EN 0x10
DECL|macro|DSP_CAI_MODEM_SPEAKER_OFF
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_OFF          0x00
DECL|macro|DSP_CAI_MODEM_SPEAKER_DURING_TRAIN
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_DURING_TRAIN 0x01
DECL|macro|DSP_CAI_MODEM_SPEAKER_TIL_CONNECT
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_TIL_CONNECT  0x02
DECL|macro|DSP_CAI_MODEM_SPEAKER_ALWAYS_ON
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_ALWAYS_ON    0x03
DECL|macro|DSP_CAI_MODEM_SPEAKER_CONTROL_MASK
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_CONTROL_MASK 0x03
DECL|macro|DSP_CAI_MODEM_SPEAKER_VOLUME_MIN
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_VOLUME_MIN   0x00
DECL|macro|DSP_CAI_MODEM_SPEAKER_VOLUME_LOW
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_VOLUME_LOW   0x04
DECL|macro|DSP_CAI_MODEM_SPEAKER_VOLUME_HIGH
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_VOLUME_HIGH  0x08
DECL|macro|DSP_CAI_MODEM_SPEAKER_VOLUME_MAX
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_VOLUME_MAX   0x0c
DECL|macro|DSP_CAI_MODEM_SPEAKER_VOLUME_MASK
mdefine_line|#define DSP_CAI_MODEM_SPEAKER_VOLUME_MASK  0x0c
multiline_comment|/* ==========================================================&n;    DCD/CTS State&n;   ========================================================== */
DECL|macro|MDM_WANT_CONNECT_B3_ACTIVE_I
mdefine_line|#define MDM_WANT_CONNECT_B3_ACTIVE_I  0x01
DECL|macro|MDM_NCPI_VALID
mdefine_line|#define MDM_NCPI_VALID                0x02
DECL|macro|MDM_NCPI_CTS_ON_RECEIVED
mdefine_line|#define MDM_NCPI_CTS_ON_RECEIVED      0x04
DECL|macro|MDM_NCPI_DCD_ON_RECEIVED
mdefine_line|#define MDM_NCPI_DCD_ON_RECEIVED      0x08
multiline_comment|/* ==========================================================&n;    CAPI NCPI Constants&n;   ========================================================== */
DECL|macro|MDM_NCPI_ECM_V42
mdefine_line|#define MDM_NCPI_ECM_V42              0x0001
DECL|macro|MDM_NCPI_ECM_MNP
mdefine_line|#define MDM_NCPI_ECM_MNP              0x0002
DECL|macro|MDM_NCPI_TRANSPARENT
mdefine_line|#define MDM_NCPI_TRANSPARENT          0x0004
DECL|macro|MDM_NCPI_COMPRESSED
mdefine_line|#define MDM_NCPI_COMPRESSED           0x0010
multiline_comment|/* ==========================================================&n;    CAPI B2 Config Constants&n;   ========================================================== */
DECL|macro|MDM_B2_DISABLE_V42bis
mdefine_line|#define MDM_B2_DISABLE_V42bis         0x0001
DECL|macro|MDM_B2_DISABLE_MNP
mdefine_line|#define MDM_B2_DISABLE_MNP            0x0002
DECL|macro|MDM_B2_DISABLE_TRANS
mdefine_line|#define MDM_B2_DISABLE_TRANS          0x0004
DECL|macro|MDM_B2_DISABLE_V42
mdefine_line|#define MDM_B2_DISABLE_V42            0x0008
DECL|macro|MDM_B2_DISABLE_COMP
mdefine_line|#define MDM_B2_DISABLE_COMP           0x0010
multiline_comment|/* ==========================================================&n;    CAPI B1 Config Constants&n;   ========================================================== */
DECL|macro|MDM_CAPI_DISABLE_RETRAIN
mdefine_line|#define MDM_CAPI_DISABLE_RETRAIN      0x0001
DECL|macro|MDM_CAPI_DISABLE_RING_TONE
mdefine_line|#define MDM_CAPI_DISABLE_RING_TONE    0x0002
DECL|macro|MDM_CAPI_GUARD_1800
mdefine_line|#define MDM_CAPI_GUARD_1800           0x0004
DECL|macro|MDM_CAPI_GUARD_550
mdefine_line|#define MDM_CAPI_GUARD_550            0x0008
DECL|macro|MDM_CAPI_NEG_V8
mdefine_line|#define MDM_CAPI_NEG_V8               0x0003
DECL|macro|MDM_CAPI_NEG_V100
mdefine_line|#define MDM_CAPI_NEG_V100             0x0002
DECL|macro|MDM_CAPI_NEG_MOD_CLASS
mdefine_line|#define MDM_CAPI_NEG_MOD_CLASS        0x0001
DECL|macro|MDM_CAPI_NEG_DISABLED
mdefine_line|#define MDM_CAPI_NEG_DISABLED         0x0000
macro_line|#endif
eof
