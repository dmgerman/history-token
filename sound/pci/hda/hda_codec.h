multiline_comment|/*&n; * Universal Interface for Intel High Definition Audio Codec&n; *&n; * Copyright (c) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the Free&n; *  Software Foundation; either version 2 of the License, or (at your option)&n; *  any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; *  more details.&n; *&n; *  You should have received a copy of the GNU General Public License along with&n; *  this program; if not, write to the Free Software Foundation, Inc., 59&n; *  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __SOUND_HDA_CODEC_H
DECL|macro|__SOUND_HDA_CODEC_H
mdefine_line|#define __SOUND_HDA_CODEC_H
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
multiline_comment|/*&n; * nodes&n; */
DECL|macro|AC_NODE_ROOT
mdefine_line|#define&t;AC_NODE_ROOT&t;&t;0x00
multiline_comment|/*&n; * function group types&n; */
r_enum
(brace
DECL|enumerator|AC_GRP_AUDIO_FUNCTION
id|AC_GRP_AUDIO_FUNCTION
op_assign
l_int|0x01
comma
DECL|enumerator|AC_GRP_MODEM_FUNCTION
id|AC_GRP_MODEM_FUNCTION
op_assign
l_int|0x02
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * widget types&n; */
r_enum
(brace
DECL|enumerator|AC_WID_AUD_OUT
id|AC_WID_AUD_OUT
comma
multiline_comment|/* Audio Out */
DECL|enumerator|AC_WID_AUD_IN
id|AC_WID_AUD_IN
comma
multiline_comment|/* Audio In */
DECL|enumerator|AC_WID_AUD_MIX
id|AC_WID_AUD_MIX
comma
multiline_comment|/* Audio Mixer */
DECL|enumerator|AC_WID_AUD_SEL
id|AC_WID_AUD_SEL
comma
multiline_comment|/* Audio Selector */
DECL|enumerator|AC_WID_PIN
id|AC_WID_PIN
comma
multiline_comment|/* Pin Complex */
DECL|enumerator|AC_WID_POWER
id|AC_WID_POWER
comma
multiline_comment|/* Power */
DECL|enumerator|AC_WID_VOL_KNB
id|AC_WID_VOL_KNB
comma
multiline_comment|/* Volume Knob */
DECL|enumerator|AC_WID_BEEP
id|AC_WID_BEEP
comma
multiline_comment|/* Beep Generator */
DECL|enumerator|AC_WID_VENDOR
id|AC_WID_VENDOR
op_assign
l_int|0x0f
multiline_comment|/* Vendor specific */
)brace
suffix:semicolon
multiline_comment|/*&n; * GET verbs&n; */
DECL|macro|AC_VERB_GET_STREAM_FORMAT
mdefine_line|#define AC_VERB_GET_STREAM_FORMAT&t;&t;0x0a00
DECL|macro|AC_VERB_GET_AMP_GAIN_MUTE
mdefine_line|#define AC_VERB_GET_AMP_GAIN_MUTE&t;&t;0x0b00
DECL|macro|AC_VERB_GET_PROC_COEF
mdefine_line|#define AC_VERB_GET_PROC_COEF&t;&t;&t;0x0c00
DECL|macro|AC_VERB_GET_COEF_INDEX
mdefine_line|#define AC_VERB_GET_COEF_INDEX&t;&t;&t;0x0d00
DECL|macro|AC_VERB_PARAMETERS
mdefine_line|#define AC_VERB_PARAMETERS&t;&t;&t;0x0f00
DECL|macro|AC_VERB_GET_CONNECT_SEL
mdefine_line|#define AC_VERB_GET_CONNECT_SEL&t;&t;&t;0x0f01
DECL|macro|AC_VERB_GET_CONNECT_LIST
mdefine_line|#define AC_VERB_GET_CONNECT_LIST&t;&t;0x0f02
DECL|macro|AC_VERB_GET_PROC_STATE
mdefine_line|#define AC_VERB_GET_PROC_STATE&t;&t;&t;0x0f03
DECL|macro|AC_VERB_GET_SDI_SELECT
mdefine_line|#define AC_VERB_GET_SDI_SELECT&t;&t;&t;0x0f04
DECL|macro|AC_VERB_GET_POWER_STATE
mdefine_line|#define AC_VERB_GET_POWER_STATE&t;&t;&t;0x0f05
DECL|macro|AC_VERB_GET_CONV
mdefine_line|#define AC_VERB_GET_CONV&t;&t;&t;0x0f06
DECL|macro|AC_VERB_GET_PIN_WIDGET_CONTROL
mdefine_line|#define AC_VERB_GET_PIN_WIDGET_CONTROL&t;&t;0x0f07
DECL|macro|AC_VERB_GET_UNSOLICITED_RESPONSE
mdefine_line|#define AC_VERB_GET_UNSOLICITED_RESPONSE&t;0x0f08
DECL|macro|AC_VERB_GET_PIN_SENSE
mdefine_line|#define AC_VERB_GET_PIN_SENSE&t;&t;&t;0x0f09
DECL|macro|AC_VERB_GET_BEEP_CONTROL
mdefine_line|#define AC_VERB_GET_BEEP_CONTROL&t;&t;0x0f0a
DECL|macro|AC_VERB_GET_EAPD_BTLENABLE
mdefine_line|#define AC_VERB_GET_EAPD_BTLENABLE&t;&t;0x0f0c
DECL|macro|AC_VERB_GET_DIGI_CONVERT
mdefine_line|#define AC_VERB_GET_DIGI_CONVERT&t;&t;0x0f0d
DECL|macro|AC_VERB_GET_VOLUME_KNOB_CONTROL
mdefine_line|#define AC_VERB_GET_VOLUME_KNOB_CONTROL&t;&t;0x0f0f
multiline_comment|/* f10-f1a: GPIO */
DECL|macro|AC_VERB_GET_CONFIG_DEFAULT
mdefine_line|#define AC_VERB_GET_CONFIG_DEFAULT&t;&t;0x0f1c
multiline_comment|/*&n; * SET verbs&n; */
DECL|macro|AC_VERB_SET_STREAM_FORMAT
mdefine_line|#define AC_VERB_SET_STREAM_FORMAT&t;&t;0x200
DECL|macro|AC_VERB_SET_AMP_GAIN_MUTE
mdefine_line|#define AC_VERB_SET_AMP_GAIN_MUTE&t;&t;0x300
DECL|macro|AC_VERB_SET_PROC_COEF
mdefine_line|#define AC_VERB_SET_PROC_COEF&t;&t;&t;0x400
DECL|macro|AC_VERB_SET_COEF_INDEX
mdefine_line|#define AC_VERB_SET_COEF_INDEX&t;&t;&t;0x500
DECL|macro|AC_VERB_SET_CONNECT_SEL
mdefine_line|#define AC_VERB_SET_CONNECT_SEL&t;&t;&t;0x701
DECL|macro|AC_VERB_SET_PROC_STATE
mdefine_line|#define AC_VERB_SET_PROC_STATE&t;&t;&t;0x703
DECL|macro|AC_VERB_SET_SDI_SELECT
mdefine_line|#define AC_VERB_SET_SDI_SELECT&t;&t;&t;0x704
DECL|macro|AC_VERB_SET_POWER_STATE
mdefine_line|#define AC_VERB_SET_POWER_STATE&t;&t;&t;0x705
DECL|macro|AC_VERB_SET_CHANNEL_STREAMID
mdefine_line|#define AC_VERB_SET_CHANNEL_STREAMID&t;&t;0x706
DECL|macro|AC_VERB_SET_PIN_WIDGET_CONTROL
mdefine_line|#define AC_VERB_SET_PIN_WIDGET_CONTROL&t;&t;0x707
DECL|macro|AC_VERB_SET_UNSOLICITED_ENABLE
mdefine_line|#define AC_VERB_SET_UNSOLICITED_ENABLE&t;&t;0x708
DECL|macro|AC_VERB_SET_PIN_SENSE
mdefine_line|#define AC_VERB_SET_PIN_SENSE&t;&t;&t;0x709
DECL|macro|AC_VERB_SET_BEEP_CONTROL
mdefine_line|#define AC_VERB_SET_BEEP_CONTROL&t;&t;0x70a
DECL|macro|AC_VERB_SET_EAPD_BTLENALBE
mdefine_line|#define AC_VERB_SET_EAPD_BTLENALBE&t;&t;0x70c
DECL|macro|AC_VERB_SET_DIGI_CONVERT_1
mdefine_line|#define AC_VERB_SET_DIGI_CONVERT_1&t;&t;0x70d
DECL|macro|AC_VERB_SET_DIGI_CONVERT_2
mdefine_line|#define AC_VERB_SET_DIGI_CONVERT_2&t;&t;0x70e
DECL|macro|AC_VERB_SET_VOLUME_KNOB_CONTROL
mdefine_line|#define AC_VERB_SET_VOLUME_KNOB_CONTROL&t;&t;0x70f
DECL|macro|AC_VERB_SET_CONFIG_DEFAULT_BYTES_0
mdefine_line|#define AC_VERB_SET_CONFIG_DEFAULT_BYTES_0&t;0x71c
DECL|macro|AC_VERB_SET_CONFIG_DEFAULT_BYTES_1
mdefine_line|#define AC_VERB_SET_CONFIG_DEFAULT_BYTES_1&t;0x71d
DECL|macro|AC_VERB_SET_CONFIG_DEFAULT_BYTES_2
mdefine_line|#define AC_VERB_SET_CONFIG_DEFAULT_BYTES_2&t;0x71e
DECL|macro|AC_VERB_SET_CONFIG_DEFAULT_BYTES_3
mdefine_line|#define AC_VERB_SET_CONFIG_DEFAULT_BYTES_3&t;0x71f
DECL|macro|AC_VERB_SET_CODEC_RESET
mdefine_line|#define AC_VERB_SET_CODEC_RESET&t;&t;&t;0x7ff
multiline_comment|/*&n; * Parameter IDs&n; */
DECL|macro|AC_PAR_VENDOR_ID
mdefine_line|#define AC_PAR_VENDOR_ID&t;&t;0x00
DECL|macro|AC_PAR_SUBSYSTEM_ID
mdefine_line|#define AC_PAR_SUBSYSTEM_ID&t;&t;0x01
DECL|macro|AC_PAR_REV_ID
mdefine_line|#define AC_PAR_REV_ID&t;&t;&t;0x02
DECL|macro|AC_PAR_NODE_COUNT
mdefine_line|#define AC_PAR_NODE_COUNT&t;&t;0x04
DECL|macro|AC_PAR_FUNCTION_TYPE
mdefine_line|#define AC_PAR_FUNCTION_TYPE&t;&t;0x05
DECL|macro|AC_PAR_AUDIO_FG_CAP
mdefine_line|#define AC_PAR_AUDIO_FG_CAP&t;&t;0x08
DECL|macro|AC_PAR_AUDIO_WIDGET_CAP
mdefine_line|#define AC_PAR_AUDIO_WIDGET_CAP&t;&t;0x09
DECL|macro|AC_PAR_PCM
mdefine_line|#define AC_PAR_PCM&t;&t;&t;0x0a
DECL|macro|AC_PAR_STREAM
mdefine_line|#define AC_PAR_STREAM&t;&t;&t;0x0b
DECL|macro|AC_PAR_PIN_CAP
mdefine_line|#define AC_PAR_PIN_CAP&t;&t;&t;0x0c
DECL|macro|AC_PAR_AMP_IN_CAP
mdefine_line|#define AC_PAR_AMP_IN_CAP&t;&t;0x0d
DECL|macro|AC_PAR_CONNLIST_LEN
mdefine_line|#define AC_PAR_CONNLIST_LEN&t;&t;0x0e
DECL|macro|AC_PAR_POWER_STATE
mdefine_line|#define AC_PAR_POWER_STATE&t;&t;0x0f
DECL|macro|AC_PAR_PROC_CAP
mdefine_line|#define AC_PAR_PROC_CAP&t;&t;&t;0x10
DECL|macro|AC_PAR_GPIO_CAP
mdefine_line|#define AC_PAR_GPIO_CAP&t;&t;&t;0x11
DECL|macro|AC_PAR_AMP_OUT_CAP
mdefine_line|#define AC_PAR_AMP_OUT_CAP&t;&t;0x12
multiline_comment|/*&n; * AC_VERB_PARAMETERS results (32bit)&n; */
multiline_comment|/* Function Group Type */
DECL|macro|AC_FGT_TYPE
mdefine_line|#define AC_FGT_TYPE&t;&t;&t;(0xff&lt;&lt;0)
DECL|macro|AC_FGT_TYPE_SHIFT
mdefine_line|#define AC_FGT_TYPE_SHIFT&t;&t;0
DECL|macro|AC_FGT_UNSOL_CAP
mdefine_line|#define AC_FGT_UNSOL_CAP&t;&t;(1&lt;&lt;8)
multiline_comment|/* Audio Function Group Capabilities */
DECL|macro|AC_AFG_OUT_DELAY
mdefine_line|#define AC_AFG_OUT_DELAY&t;&t;(0xf&lt;&lt;0)
DECL|macro|AC_AFG_IN_DELAY
mdefine_line|#define AC_AFG_IN_DELAY&t;&t;&t;(0xf&lt;&lt;8)
DECL|macro|AC_AFG_BEEP_GEN
mdefine_line|#define AC_AFG_BEEP_GEN&t;&t;&t;(1&lt;&lt;16)
multiline_comment|/* Audio Widget Capabilities */
DECL|macro|AC_WCAP_STEREO
mdefine_line|#define AC_WCAP_STEREO&t;&t;&t;(1&lt;&lt;0)&t;/* stereo I/O */
DECL|macro|AC_WCAP_IN_AMP
mdefine_line|#define AC_WCAP_IN_AMP&t;&t;&t;(1&lt;&lt;1)&t;/* AMP-in present */
DECL|macro|AC_WCAP_OUT_AMP
mdefine_line|#define AC_WCAP_OUT_AMP&t;&t;&t;(1&lt;&lt;2)&t;/* AMP-out present */
DECL|macro|AC_WCAP_AMP_OVRD
mdefine_line|#define AC_WCAP_AMP_OVRD&t;&t;(1&lt;&lt;3)&t;/* AMP-parameter override */
DECL|macro|AC_WCAP_FORMAT_OVRD
mdefine_line|#define AC_WCAP_FORMAT_OVRD&t;&t;(1&lt;&lt;4)&t;/* format override */
DECL|macro|AC_WCAP_STRIPE
mdefine_line|#define AC_WCAP_STRIPE&t;&t;&t;(1&lt;&lt;5)&t;/* stripe */
DECL|macro|AC_WCAP_PROC_WID
mdefine_line|#define AC_WCAP_PROC_WID&t;&t;(1&lt;&lt;6)&t;/* Proc Widget */
DECL|macro|AC_WCAP_UNSOL_CAP
mdefine_line|#define AC_WCAP_UNSOL_CAP&t;&t;(1&lt;&lt;7)&t;/* Unsol capable */
DECL|macro|AC_WCAP_CONN_LIST
mdefine_line|#define AC_WCAP_CONN_LIST&t;&t;(1&lt;&lt;8)&t;/* connection list */
DECL|macro|AC_WCAP_DIGITAL
mdefine_line|#define AC_WCAP_DIGITAL&t;&t;&t;(1&lt;&lt;9)&t;/* digital I/O */
DECL|macro|AC_WCAP_POWER
mdefine_line|#define AC_WCAP_POWER&t;&t;&t;(1&lt;&lt;10)&t;/* power control */
DECL|macro|AC_WCAP_LR_SWAP
mdefine_line|#define AC_WCAP_LR_SWAP&t;&t;&t;(1&lt;&lt;11)&t;/* L/R swap */
DECL|macro|AC_WCAP_DELAY
mdefine_line|#define AC_WCAP_DELAY&t;&t;&t;(0xf&lt;&lt;16)
DECL|macro|AC_WCAP_DELAY_SHIFT
mdefine_line|#define AC_WCAP_DELAY_SHIFT&t;&t;16
DECL|macro|AC_WCAP_TYPE
mdefine_line|#define AC_WCAP_TYPE&t;&t;&t;(0xf&lt;&lt;20)
DECL|macro|AC_WCAP_TYPE_SHIFT
mdefine_line|#define AC_WCAP_TYPE_SHIFT&t;&t;20
multiline_comment|/* supported PCM rates and bits */
DECL|macro|AC_SUPPCM_RATES
mdefine_line|#define AC_SUPPCM_RATES&t;&t;&t;(0xfff &lt;&lt; 0)
DECL|macro|AC_SUPPCM_BITS_8
mdefine_line|#define AC_SUPPCM_BITS_8&t;&t;(1&lt;&lt;16)
DECL|macro|AC_SUPPCM_BITS_16
mdefine_line|#define AC_SUPPCM_BITS_16&t;&t;(1&lt;&lt;17)
DECL|macro|AC_SUPPCM_BITS_20
mdefine_line|#define AC_SUPPCM_BITS_20&t;&t;(1&lt;&lt;18)
DECL|macro|AC_SUPPCM_BITS_24
mdefine_line|#define AC_SUPPCM_BITS_24&t;&t;(1&lt;&lt;19)
DECL|macro|AC_SUPPCM_BITS_32
mdefine_line|#define AC_SUPPCM_BITS_32&t;&t;(1&lt;&lt;20)
multiline_comment|/* supported PCM stream format */
DECL|macro|AC_SUPFMT_PCM
mdefine_line|#define AC_SUPFMT_PCM&t;&t;&t;(1&lt;&lt;0)
DECL|macro|AC_SUPFMT_FLOAT32
mdefine_line|#define AC_SUPFMT_FLOAT32&t;&t;(1&lt;&lt;1)
DECL|macro|AC_SUPFMT_AC3
mdefine_line|#define AC_SUPFMT_AC3&t;&t;&t;(1&lt;&lt;2)
multiline_comment|/* Pin widget capabilies */
DECL|macro|AC_PINCAP_IMP_SENSE
mdefine_line|#define AC_PINCAP_IMP_SENSE&t;&t;(1&lt;&lt;0)&t;/* impedance sense capable */
DECL|macro|AC_PINCAP_TRIG_REQ
mdefine_line|#define AC_PINCAP_TRIG_REQ&t;&t;(1&lt;&lt;1)&t;/* trigger required */
DECL|macro|AC_PINCAP_PRES_DETECT
mdefine_line|#define AC_PINCAP_PRES_DETECT&t;&t;(1&lt;&lt;2)&t;/* presence detect capable */
DECL|macro|AC_PINCAP_HP_DRV
mdefine_line|#define AC_PINCAP_HP_DRV&t;&t;(1&lt;&lt;3)&t;/* headphone drive capable */
DECL|macro|AC_PINCAP_OUT
mdefine_line|#define AC_PINCAP_OUT&t;&t;&t;(1&lt;&lt;4)&t;/* output capable */
DECL|macro|AC_PINCAP_IN
mdefine_line|#define AC_PINCAP_IN&t;&t;&t;(1&lt;&lt;5)&t;/* input capable */
DECL|macro|AC_PINCAP_BALANCE
mdefine_line|#define AC_PINCAP_BALANCE&t;&t;(1&lt;&lt;6)&t;/* balanced I/O capable */
DECL|macro|AC_PINCAP_VREF
mdefine_line|#define AC_PINCAP_VREF&t;&t;&t;(7&lt;&lt;8)
DECL|macro|AC_PINCAP_VREF_SHIFT
mdefine_line|#define AC_PINCAP_VREF_SHIFT&t;&t;8
DECL|macro|AC_PINCAP_EAPD
mdefine_line|#define AC_PINCAP_EAPD&t;&t;&t;(1&lt;&lt;16)&t;/* EAPD capable */
multiline_comment|/* Vref status (used in pin cap and pin ctl) */
DECL|macro|AC_PIN_VREF_HIZ
mdefine_line|#define AC_PIN_VREF_HIZ&t;&t;&t;(1&lt;&lt;0)&t;/* Hi-Z */
DECL|macro|AC_PIN_VREF_50
mdefine_line|#define AC_PIN_VREF_50&t;&t;&t;(1&lt;&lt;1)&t;/* 50% */
DECL|macro|AC_PIN_VREF_GRD
mdefine_line|#define AC_PIN_VREF_GRD&t;&t;&t;(1&lt;&lt;2)&t;/* ground */
DECL|macro|AC_PIN_VREF_80
mdefine_line|#define AC_PIN_VREF_80&t;&t;&t;(1&lt;&lt;4)&t;/* 80% */
DECL|macro|AC_PIN_VREF_100
mdefine_line|#define AC_PIN_VREF_100&t;&t;&t;(1&lt;&lt;5)&t;/* 100% */
multiline_comment|/* Amplifier capabilities */
DECL|macro|AC_AMPCAP_OFFSET
mdefine_line|#define AC_AMPCAP_OFFSET&t;&t;(0x7f&lt;&lt;0)  /* 0dB offset */
DECL|macro|AC_AMPCAP_OFFSET_SHIFT
mdefine_line|#define AC_AMPCAP_OFFSET_SHIFT&t;&t;0
DECL|macro|AC_AMPCAP_NUM_STEPS
mdefine_line|#define AC_AMPCAP_NUM_STEPS&t;&t;(0x7f&lt;&lt;8)  /* number of steps */
DECL|macro|AC_AMPCAP_NUM_STEPS_SHIFT
mdefine_line|#define AC_AMPCAP_NUM_STEPS_SHIFT&t;8
DECL|macro|AC_AMPCAP_STEP_SIZE
mdefine_line|#define AC_AMPCAP_STEP_SIZE&t;&t;(0x7f&lt;&lt;16) /* step size 0-32dB in 0.25dB */
DECL|macro|AC_AMPCAP_STEP_SIZE_SHIFT
mdefine_line|#define AC_AMPCAP_STEP_SIZE_SHIFT&t;16
DECL|macro|AC_AMPCAP_MUTE
mdefine_line|#define AC_AMPCAP_MUTE&t;&t;&t;(1&lt;&lt;31)    /* mute capable */
DECL|macro|AC_AMPCAP_MUTE_SHIFT
mdefine_line|#define AC_AMPCAP_MUTE_SHIFT&t;&t;31
multiline_comment|/* Connection list */
DECL|macro|AC_CLIST_LENGTH
mdefine_line|#define AC_CLIST_LENGTH&t;&t;&t;(0x7f&lt;&lt;0)
DECL|macro|AC_CLIST_LONG
mdefine_line|#define AC_CLIST_LONG&t;&t;&t;(1&lt;&lt;7)
multiline_comment|/* Supported power status */
DECL|macro|AC_PWRST_D0SUP
mdefine_line|#define AC_PWRST_D0SUP&t;&t;&t;(1&lt;&lt;0)
DECL|macro|AC_PWRST_D1SUP
mdefine_line|#define AC_PWRST_D1SUP&t;&t;&t;(1&lt;&lt;1)
DECL|macro|AC_PWRST_D2SUP
mdefine_line|#define AC_PWRST_D2SUP&t;&t;&t;(1&lt;&lt;2)
DECL|macro|AC_PWRST_D3SUP
mdefine_line|#define AC_PWRST_D3SUP&t;&t;&t;(1&lt;&lt;3)
multiline_comment|/* Processing capabilies */
DECL|macro|AC_PCAP_BENIGN
mdefine_line|#define AC_PCAP_BENIGN&t;&t;&t;(1&lt;&lt;0)
DECL|macro|AC_PCAP_NUM_COEF
mdefine_line|#define AC_PCAP_NUM_COEF&t;&t;(0xff&lt;&lt;8)
multiline_comment|/* Volume knobs capabilities */
DECL|macro|AC_KNBCAP_NUM_STEPS
mdefine_line|#define AC_KNBCAP_NUM_STEPS&t;&t;(0x7f&lt;&lt;0)
DECL|macro|AC_KNBCAP_DELTA
mdefine_line|#define AC_KNBCAP_DELTA&t;&t;&t;(1&lt;&lt;8)
multiline_comment|/*&n; * Control Parameters&n; */
multiline_comment|/* Amp gain/mute */
DECL|macro|AC_AMP_MUTE
mdefine_line|#define AC_AMP_MUTE&t;&t;&t;(1&lt;&lt;8)
DECL|macro|AC_AMP_GAIN
mdefine_line|#define AC_AMP_GAIN&t;&t;&t;(0x7f)
DECL|macro|AC_AMP_GET_INDEX
mdefine_line|#define AC_AMP_GET_INDEX&t;&t;(0xf&lt;&lt;0)
DECL|macro|AC_AMP_GET_LEFT
mdefine_line|#define AC_AMP_GET_LEFT&t;&t;&t;(1&lt;&lt;13)
DECL|macro|AC_AMP_GET_RIGHT
mdefine_line|#define AC_AMP_GET_RIGHT&t;&t;(0&lt;&lt;13)
DECL|macro|AC_AMP_GET_OUTPUT
mdefine_line|#define AC_AMP_GET_OUTPUT&t;&t;(1&lt;&lt;15)
DECL|macro|AC_AMP_GET_INPUT
mdefine_line|#define AC_AMP_GET_INPUT&t;&t;(0&lt;&lt;15)
DECL|macro|AC_AMP_SET_INDEX
mdefine_line|#define AC_AMP_SET_INDEX&t;&t;(0xf&lt;&lt;8)
DECL|macro|AC_AMP_SET_INDEX_SHIFT
mdefine_line|#define AC_AMP_SET_INDEX_SHIFT&t;&t;8
DECL|macro|AC_AMP_SET_RIGHT
mdefine_line|#define AC_AMP_SET_RIGHT&t;&t;(1&lt;&lt;12)
DECL|macro|AC_AMP_SET_LEFT
mdefine_line|#define AC_AMP_SET_LEFT&t;&t;&t;(1&lt;&lt;13)
DECL|macro|AC_AMP_SET_INPUT
mdefine_line|#define AC_AMP_SET_INPUT&t;&t;(1&lt;&lt;14)
DECL|macro|AC_AMP_SET_OUTPUT
mdefine_line|#define AC_AMP_SET_OUTPUT&t;&t;(1&lt;&lt;15)
multiline_comment|/* DIGITAL1 bits */
DECL|macro|AC_DIG1_ENABLE
mdefine_line|#define AC_DIG1_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|AC_DIG1_V
mdefine_line|#define AC_DIG1_V&t;&t;&t;(1&lt;&lt;1)
DECL|macro|AC_DIG1_VCFG
mdefine_line|#define AC_DIG1_VCFG&t;&t;&t;(1&lt;&lt;2)
DECL|macro|AC_DIG1_EMPHASIS
mdefine_line|#define AC_DIG1_EMPHASIS&t;&t;(1&lt;&lt;3)
DECL|macro|AC_DIG1_COPYRIGHT
mdefine_line|#define AC_DIG1_COPYRIGHT&t;&t;(1&lt;&lt;4)
DECL|macro|AC_DIG1_NONAUDIO
mdefine_line|#define AC_DIG1_NONAUDIO&t;&t;(1&lt;&lt;5)
DECL|macro|AC_DIG1_PROFESSIONAL
mdefine_line|#define AC_DIG1_PROFESSIONAL&t;&t;(1&lt;&lt;6)
DECL|macro|AC_DIG1_LEVEL
mdefine_line|#define AC_DIG1_LEVEL&t;&t;&t;(1&lt;&lt;7)
multiline_comment|/* Pin widget control - 8bit */
DECL|macro|AC_PINCTL_VREFEN
mdefine_line|#define AC_PINCTL_VREFEN&t;&t;(0x7&lt;&lt;0)
DECL|macro|AC_PINCTL_IN_EN
mdefine_line|#define AC_PINCTL_IN_EN&t;&t;&t;(1&lt;&lt;5)
DECL|macro|AC_PINCTL_OUT_EN
mdefine_line|#define AC_PINCTL_OUT_EN&t;&t;(1&lt;&lt;6)
DECL|macro|AC_PINCTL_HP_EN
mdefine_line|#define AC_PINCTL_HP_EN&t;&t;&t;(1&lt;&lt;7)
multiline_comment|/* configuration default - 32bit */
DECL|macro|AC_DEFCFG_SEQUENCE
mdefine_line|#define AC_DEFCFG_SEQUENCE&t;&t;(0xf&lt;&lt;0)
DECL|macro|AC_DEFCFG_DEF_ASSOC
mdefine_line|#define AC_DEFCFG_DEF_ASSOC&t;&t;(0xf&lt;&lt;4)
DECL|macro|AC_DEFCFG_MISC
mdefine_line|#define AC_DEFCFG_MISC&t;&t;&t;(0xf&lt;&lt;8)
DECL|macro|AC_DEFCFG_COLOR
mdefine_line|#define AC_DEFCFG_COLOR&t;&t;&t;(0xf&lt;&lt;12)
DECL|macro|AC_DEFCFG_COLOR_SHIFT
mdefine_line|#define AC_DEFCFG_COLOR_SHIFT&t;&t;12
DECL|macro|AC_DEFCFG_CONN_TYPE
mdefine_line|#define AC_DEFCFG_CONN_TYPE&t;&t;(0xf&lt;&lt;16)
DECL|macro|AC_DEFCFG_CONN_TYPE_SHIFT
mdefine_line|#define AC_DEFCFG_CONN_TYPE_SHIFT&t;16
DECL|macro|AC_DEFCFG_DEVICE
mdefine_line|#define AC_DEFCFG_DEVICE&t;&t;(0xf&lt;&lt;20)
DECL|macro|AC_DEFCFG_DEVICE_SHIFT
mdefine_line|#define AC_DEFCFG_DEVICE_SHIFT&t;&t;20
DECL|macro|AC_DEFCFG_LOCATION
mdefine_line|#define AC_DEFCFG_LOCATION&t;&t;(0x3f&lt;&lt;24)
DECL|macro|AC_DEFCFG_LOCATION_SHIFT
mdefine_line|#define AC_DEFCFG_LOCATION_SHIFT&t;24
DECL|macro|AC_DEFCFG_PORT_CONN
mdefine_line|#define AC_DEFCFG_PORT_CONN&t;&t;(0x3&lt;&lt;30)
DECL|macro|AC_DEFCFG_PORT_CONN_SHIFT
mdefine_line|#define AC_DEFCFG_PORT_CONN_SHIFT&t;30
multiline_comment|/* device device types (0x0-0xf) */
r_enum
(brace
DECL|enumerator|AC_JACK_LINE_OUT
id|AC_JACK_LINE_OUT
comma
DECL|enumerator|AC_JACK_SPEAKER
id|AC_JACK_SPEAKER
comma
DECL|enumerator|AC_JACK_HP_OUT
id|AC_JACK_HP_OUT
comma
DECL|enumerator|AC_JACK_CD
id|AC_JACK_CD
comma
DECL|enumerator|AC_JACK_SPDIF_OUT
id|AC_JACK_SPDIF_OUT
comma
DECL|enumerator|AC_JACK_DIG_OTHER_OUT
id|AC_JACK_DIG_OTHER_OUT
comma
DECL|enumerator|AC_JACK_MODEM_LINE_SIDE
id|AC_JACK_MODEM_LINE_SIDE
comma
DECL|enumerator|AC_JACK_MODEM_HAND_SIDE
id|AC_JACK_MODEM_HAND_SIDE
comma
DECL|enumerator|AC_JACK_LINE_IN
id|AC_JACK_LINE_IN
comma
DECL|enumerator|AC_JACK_AUX
id|AC_JACK_AUX
comma
DECL|enumerator|AC_JACK_MIC_IN
id|AC_JACK_MIC_IN
comma
DECL|enumerator|AC_JACK_TELEPHONY
id|AC_JACK_TELEPHONY
comma
DECL|enumerator|AC_JACK_SPDIF_IN
id|AC_JACK_SPDIF_IN
comma
DECL|enumerator|AC_JACK_DIG_OTHER_IN
id|AC_JACK_DIG_OTHER_IN
comma
DECL|enumerator|AC_JACK_OTHER
id|AC_JACK_OTHER
op_assign
l_int|0xf
comma
)brace
suffix:semicolon
multiline_comment|/* jack connection types (0x0-0xf) */
r_enum
(brace
DECL|enumerator|AC_JACK_CONN_UNKNOWN
id|AC_JACK_CONN_UNKNOWN
comma
DECL|enumerator|AC_JACK_CONN_1_8
id|AC_JACK_CONN_1_8
comma
DECL|enumerator|AC_JACK_CONN_1_4
id|AC_JACK_CONN_1_4
comma
DECL|enumerator|AC_JACK_CONN_ATAPI
id|AC_JACK_CONN_ATAPI
comma
DECL|enumerator|AC_JACK_CONN_RCA
id|AC_JACK_CONN_RCA
comma
DECL|enumerator|AC_JACK_CONN_OPTICAL
id|AC_JACK_CONN_OPTICAL
comma
DECL|enumerator|AC_JACK_CONN_OTHER_DIGITAL
id|AC_JACK_CONN_OTHER_DIGITAL
comma
DECL|enumerator|AC_JACK_CONN_OTHER_ANALOG
id|AC_JACK_CONN_OTHER_ANALOG
comma
DECL|enumerator|AC_JACK_CONN_DIN
id|AC_JACK_CONN_DIN
comma
DECL|enumerator|AC_JACK_CONN_XLR
id|AC_JACK_CONN_XLR
comma
DECL|enumerator|AC_JACK_CONN_RJ11
id|AC_JACK_CONN_RJ11
comma
DECL|enumerator|AC_JACK_CONN_COMB
id|AC_JACK_CONN_COMB
comma
DECL|enumerator|AC_JACK_CONN_OTHER
id|AC_JACK_CONN_OTHER
op_assign
l_int|0xf
comma
)brace
suffix:semicolon
multiline_comment|/* jack colors (0x0-0xf) */
r_enum
(brace
DECL|enumerator|AC_JACK_COLOR_UNKNOWN
id|AC_JACK_COLOR_UNKNOWN
comma
DECL|enumerator|AC_JACK_COLOR_BLACK
id|AC_JACK_COLOR_BLACK
comma
DECL|enumerator|AC_JACK_COLOR_GREY
id|AC_JACK_COLOR_GREY
comma
DECL|enumerator|AC_JACK_COLOR_BLUE
id|AC_JACK_COLOR_BLUE
comma
DECL|enumerator|AC_JACK_COLOR_GREEN
id|AC_JACK_COLOR_GREEN
comma
DECL|enumerator|AC_JACK_COLOR_RED
id|AC_JACK_COLOR_RED
comma
DECL|enumerator|AC_JACK_COLOR_ORANGE
id|AC_JACK_COLOR_ORANGE
comma
DECL|enumerator|AC_JACK_COLOR_YELLOW
id|AC_JACK_COLOR_YELLOW
comma
DECL|enumerator|AC_JACK_COLOR_PURPLE
id|AC_JACK_COLOR_PURPLE
comma
DECL|enumerator|AC_JACK_COLOR_PINK
id|AC_JACK_COLOR_PINK
comma
DECL|enumerator|AC_JACK_COLOR_WHITE
id|AC_JACK_COLOR_WHITE
op_assign
l_int|0xe
comma
DECL|enumerator|AC_JACK_COLOR_OTHER
id|AC_JACK_COLOR_OTHER
comma
)brace
suffix:semicolon
multiline_comment|/* Jack location (0x0-0x3f) */
multiline_comment|/* common case */
r_enum
(brace
DECL|enumerator|AC_JACK_LOC_NONE
id|AC_JACK_LOC_NONE
comma
DECL|enumerator|AC_JACK_LOC_REAR
id|AC_JACK_LOC_REAR
comma
DECL|enumerator|AC_JACK_LOC_FRONT
id|AC_JACK_LOC_FRONT
comma
DECL|enumerator|AC_JACK_LOC_LEFT
id|AC_JACK_LOC_LEFT
comma
DECL|enumerator|AC_JACK_LOC_RIGHT
id|AC_JACK_LOC_RIGHT
comma
DECL|enumerator|AC_JACK_LOC_TOP
id|AC_JACK_LOC_TOP
comma
DECL|enumerator|AC_JACK_LOC_BOTTOM
id|AC_JACK_LOC_BOTTOM
comma
)brace
suffix:semicolon
multiline_comment|/* bits 4-5 */
r_enum
(brace
DECL|enumerator|AC_JACK_LOC_EXTERNAL
id|AC_JACK_LOC_EXTERNAL
op_assign
l_int|0x00
comma
DECL|enumerator|AC_JACK_LOC_INTERNAL
id|AC_JACK_LOC_INTERNAL
op_assign
l_int|0x10
comma
DECL|enumerator|AC_JACK_LOC_SEPARATE
id|AC_JACK_LOC_SEPARATE
op_assign
l_int|0x20
comma
DECL|enumerator|AC_JACK_LOC_OTHER
id|AC_JACK_LOC_OTHER
op_assign
l_int|0x30
comma
)brace
suffix:semicolon
r_enum
(brace
multiline_comment|/* external on primary chasis */
DECL|enumerator|AC_JACK_LOC_REAR_PANEL
id|AC_JACK_LOC_REAR_PANEL
op_assign
l_int|0x07
comma
DECL|enumerator|AC_JACK_LOC_DRIVE_BAY
id|AC_JACK_LOC_DRIVE_BAY
comma
multiline_comment|/* internal */
DECL|enumerator|AC_JACK_LOC_RISER
id|AC_JACK_LOC_RISER
op_assign
l_int|0x17
comma
DECL|enumerator|AC_JACK_LOC_HDMI
id|AC_JACK_LOC_HDMI
comma
DECL|enumerator|AC_JACK_LOC_ATAPI
id|AC_JACK_LOC_ATAPI
comma
multiline_comment|/* others */
DECL|enumerator|AC_JACK_LOC_MOBILE_IN
id|AC_JACK_LOC_MOBILE_IN
op_assign
l_int|0x37
comma
DECL|enumerator|AC_JACK_LOC_MOBILE_OUT
id|AC_JACK_LOC_MOBILE_OUT
comma
)brace
suffix:semicolon
multiline_comment|/* Port connectivity (0-3) */
r_enum
(brace
DECL|enumerator|AC_JACK_PORT_COMPLEX
id|AC_JACK_PORT_COMPLEX
comma
DECL|enumerator|AC_JACK_PORT_NONE
id|AC_JACK_PORT_NONE
comma
DECL|enumerator|AC_JACK_PORT_FIXED
id|AC_JACK_PORT_FIXED
comma
DECL|enumerator|AC_JACK_PORT_BOTH
id|AC_JACK_PORT_BOTH
comma
)brace
suffix:semicolon
multiline_comment|/* max. connections to a widget */
DECL|macro|HDA_MAX_CONNECTIONS
mdefine_line|#define HDA_MAX_CONNECTIONS&t;16
multiline_comment|/* max. codec address */
DECL|macro|HDA_MAX_CODEC_ADDRESS
mdefine_line|#define HDA_MAX_CODEC_ADDRESS&t;0x0f
multiline_comment|/*&n; * Structures&n; */
r_struct
id|hda_bus
suffix:semicolon
r_struct
id|hda_codec
suffix:semicolon
r_struct
id|hda_pcm
suffix:semicolon
r_struct
id|hda_pcm_stream
suffix:semicolon
r_struct
id|hda_bus_unsolicited
suffix:semicolon
multiline_comment|/* NID type */
DECL|typedef|hda_nid_t
r_typedef
id|u16
id|hda_nid_t
suffix:semicolon
multiline_comment|/* bus operators */
DECL|struct|hda_bus_ops
r_struct
id|hda_bus_ops
(brace
multiline_comment|/* send a single command */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
r_int
id|direct
comma
r_int
r_int
id|verb
comma
r_int
r_int
id|parm
)paren
suffix:semicolon
multiline_comment|/* get a response from the last command */
DECL|member|get_response
r_int
r_int
(paren
op_star
id|get_response
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
multiline_comment|/* free the private data */
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
r_struct
id|hda_bus
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* template to pass to the bus constructor */
DECL|struct|hda_bus_template
r_struct
id|hda_bus_template
(brace
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|modelname
r_const
r_char
op_star
id|modelname
suffix:semicolon
DECL|member|ops
r_struct
id|hda_bus_ops
id|ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * codec bus&n; *&n; * each controller needs to creata a hda_bus to assign the accessor.&n; * A hda_bus contains several codecs in the list codec_list.&n; */
DECL|struct|hda_bus
r_struct
id|hda_bus
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* copied from template */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|modelname
r_const
r_char
op_star
id|modelname
suffix:semicolon
DECL|member|ops
r_struct
id|hda_bus_ops
id|ops
suffix:semicolon
multiline_comment|/* codec linked list */
DECL|member|codec_list
r_struct
id|list_head
id|codec_list
suffix:semicolon
DECL|member|caddr_tbl
r_struct
id|hda_codec
op_star
id|caddr_tbl
(braket
id|HDA_MAX_CODEC_ADDRESS
)braket
suffix:semicolon
multiline_comment|/* caddr -&gt; codec */
DECL|member|cmd_mutex
r_struct
id|semaphore
id|cmd_mutex
suffix:semicolon
multiline_comment|/* unsolicited event queue */
DECL|member|unsol
r_struct
id|hda_bus_unsolicited
op_star
id|unsol
suffix:semicolon
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * codec preset&n; *&n; * Known codecs have the patch to build and set up the controls/PCMs&n; * better than the generic parser.&n; */
DECL|struct|hda_codec_preset
r_struct
id|hda_codec_preset
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|subs
r_int
r_int
id|subs
suffix:semicolon
DECL|member|subs_mask
r_int
r_int
id|subs_mask
suffix:semicolon
DECL|member|rev
r_int
r_int
id|rev
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|patch
r_int
(paren
op_star
id|patch
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ops set by the preset patch */
DECL|struct|hda_codec_ops
r_struct
id|hda_codec_ops
(brace
DECL|member|build_controls
r_int
(paren
op_star
id|build_controls
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
DECL|member|build_pcms
r_int
(paren
op_star
id|build_pcms
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
DECL|member|unsol_event
r_void
(paren
op_star
id|unsol_event
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
r_int
r_int
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|pm_message_t
id|state
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* record for amp information cache */
DECL|struct|hda_amp_info
r_struct
id|hda_amp_info
(brace
DECL|member|key
id|u32
id|key
suffix:semicolon
multiline_comment|/* hash key */
DECL|member|amp_caps
id|u32
id|amp_caps
suffix:semicolon
multiline_comment|/* amp capabilities */
DECL|member|vol
id|u16
id|vol
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* current volume &amp; mute*/
DECL|member|status
id|u16
id|status
suffix:semicolon
multiline_comment|/* update flag */
DECL|member|next
id|u16
id|next
suffix:semicolon
multiline_comment|/* next link */
)brace
suffix:semicolon
multiline_comment|/* PCM callbacks */
DECL|struct|hda_pcm_ops
r_struct
id|hda_pcm_ops
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|hda_pcm_stream
op_star
id|info
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_struct
id|hda_pcm_stream
op_star
id|info
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|member|prepare
r_int
(paren
op_star
id|prepare
)paren
(paren
r_struct
id|hda_pcm_stream
op_star
id|info
comma
r_struct
id|hda_codec
op_star
id|codec
comma
r_int
r_int
id|stream_tag
comma
r_int
r_int
id|format
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
DECL|member|cleanup
r_int
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|hda_pcm_stream
op_star
id|info
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PCM information for each substream */
DECL|struct|hda_pcm_stream
r_struct
id|hda_pcm_stream
(brace
DECL|member|substreams
r_int
r_int
id|substreams
suffix:semicolon
multiline_comment|/* number of substreams, 0 = not exist */
DECL|member|channels_min
r_int
r_int
id|channels_min
suffix:semicolon
multiline_comment|/* min. number of channels */
DECL|member|channels_max
r_int
r_int
id|channels_max
suffix:semicolon
multiline_comment|/* max. number of channels */
DECL|member|nid
id|hda_nid_t
id|nid
suffix:semicolon
multiline_comment|/* default NID to query rates/formats/bps, or set up */
DECL|member|rates
id|u32
id|rates
suffix:semicolon
multiline_comment|/* supported rates */
DECL|member|formats
id|u64
id|formats
suffix:semicolon
multiline_comment|/* supported formats (SNDRV_PCM_FMTBIT_) */
DECL|member|maxbps
r_int
r_int
id|maxbps
suffix:semicolon
multiline_comment|/* supported max. bit per sample */
DECL|member|ops
r_struct
id|hda_pcm_ops
id|ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for PCM creation */
DECL|struct|hda_pcm
r_struct
id|hda_pcm
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|stream
r_struct
id|hda_pcm_stream
id|stream
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* codec information */
DECL|struct|hda_codec
r_struct
id|hda_codec
(brace
DECL|member|bus
r_struct
id|hda_bus
op_star
id|bus
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* codec addr*/
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list point */
DECL|member|afg
id|hda_nid_t
id|afg
suffix:semicolon
multiline_comment|/* AFG node id */
multiline_comment|/* ids */
DECL|member|vendor_id
id|u32
id|vendor_id
suffix:semicolon
DECL|member|subsystem_id
id|u32
id|subsystem_id
suffix:semicolon
DECL|member|revision_id
id|u32
id|revision_id
suffix:semicolon
multiline_comment|/* detected preset */
DECL|member|preset
r_const
r_struct
id|hda_codec_preset
op_star
id|preset
suffix:semicolon
multiline_comment|/* set by patch */
DECL|member|patch_ops
r_struct
id|hda_codec_ops
id|patch_ops
suffix:semicolon
multiline_comment|/* resume phase - all controls should update even if&n;&t; * the values are not changed&n;&t; */
DECL|member|in_resume
r_int
r_int
id|in_resume
suffix:semicolon
multiline_comment|/* PCM to create, set by patch_ops.build_pcms callback */
DECL|member|num_pcms
r_int
r_int
id|num_pcms
suffix:semicolon
DECL|member|pcm_info
r_struct
id|hda_pcm
op_star
id|pcm_info
suffix:semicolon
multiline_comment|/* codec specific info */
DECL|member|spec
r_void
op_star
id|spec
suffix:semicolon
multiline_comment|/* hash for amp access */
DECL|member|amp_hash
id|u16
id|amp_hash
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|num_amp_entries
r_int
id|num_amp_entries
suffix:semicolon
DECL|member|amp_info
r_struct
id|hda_amp_info
id|amp_info
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* big enough? */
DECL|member|spdif_mutex
r_struct
id|semaphore
id|spdif_mutex
suffix:semicolon
DECL|member|spdif_status
r_int
r_int
id|spdif_status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* direction */
r_enum
(brace
DECL|enumerator|HDA_INPUT
DECL|enumerator|HDA_OUTPUT
id|HDA_INPUT
comma
id|HDA_OUTPUT
)brace
suffix:semicolon
multiline_comment|/*&n; * constructors&n; */
r_int
id|snd_hda_bus_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_struct
id|hda_bus_template
op_star
id|temp
comma
r_struct
id|hda_bus
op_star
op_star
id|busp
)paren
suffix:semicolon
r_int
id|snd_hda_codec_new
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
comma
r_int
r_int
id|codec_addr
comma
r_struct
id|hda_codec
op_star
op_star
id|codecp
)paren
suffix:semicolon
multiline_comment|/*&n; * low level functions&n; */
r_int
r_int
id|snd_hda_codec_read
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
r_int
id|direct
comma
r_int
r_int
id|verb
comma
r_int
r_int
id|parm
)paren
suffix:semicolon
r_int
id|snd_hda_codec_write
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
r_int
id|direct
comma
r_int
r_int
id|verb
comma
r_int
r_int
id|parm
)paren
suffix:semicolon
DECL|macro|snd_hda_param_read
mdefine_line|#define snd_hda_param_read(codec, nid, param) snd_hda_codec_read(codec, nid, 0, AC_VERB_PARAMETERS, param)
r_int
id|snd_hda_get_sub_nodes
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
id|hda_nid_t
op_star
id|start_id
)paren
suffix:semicolon
r_int
id|snd_hda_get_connections
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
id|hda_nid_t
op_star
id|conn_list
comma
r_int
id|max_conns
)paren
suffix:semicolon
DECL|struct|hda_verb
r_struct
id|hda_verb
(brace
DECL|member|nid
id|hda_nid_t
id|nid
suffix:semicolon
DECL|member|verb
id|u32
id|verb
suffix:semicolon
DECL|member|param
id|u32
id|param
suffix:semicolon
)brace
suffix:semicolon
r_void
id|snd_hda_sequence_write
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
r_const
r_struct
id|hda_verb
op_star
id|seq
)paren
suffix:semicolon
multiline_comment|/* unsolicited event */
r_int
id|snd_hda_queue_unsol_event
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
comma
id|u32
id|res
comma
id|u32
id|res_ex
)paren
suffix:semicolon
multiline_comment|/*&n; * Mixer&n; */
r_int
id|snd_hda_build_controls
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/*&n; * PCM&n; */
r_int
id|snd_hda_build_pcms
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
)paren
suffix:semicolon
r_void
id|snd_hda_codec_setup_stream
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
id|u32
id|stream_tag
comma
r_int
id|channel_id
comma
r_int
id|format
)paren
suffix:semicolon
r_int
r_int
id|snd_hda_calc_stream_format
c_func
(paren
r_int
r_int
id|rate
comma
r_int
r_int
id|channels
comma
r_int
r_int
id|format
comma
r_int
r_int
id|maxbps
)paren
suffix:semicolon
r_int
id|snd_hda_query_supported_pcm
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
id|u32
op_star
id|ratesp
comma
id|u64
op_star
id|formatsp
comma
r_int
r_int
op_star
id|bpsp
)paren
suffix:semicolon
r_int
id|snd_hda_is_supported_format
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
id|hda_nid_t
id|nid
comma
r_int
r_int
id|format
)paren
suffix:semicolon
multiline_comment|/*&n; * Misc&n; */
r_void
id|snd_hda_get_codec_name
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
suffix:semicolon
multiline_comment|/*&n; * power management&n; */
macro_line|#ifdef CONFIG_PM
r_int
id|snd_hda_suspend
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
comma
id|pm_message_t
id|state
)paren
suffix:semicolon
r_int
id|snd_hda_resume
c_func
(paren
r_struct
id|hda_bus
op_star
id|bus
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_HDA_CODEC_H */
eof
