macro_line|#ifndef _AC97_CODEC_H_
DECL|macro|_AC97_CODEC_H_
mdefine_line|#define _AC97_CODEC_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
multiline_comment|/* AC97 1.0 */
DECL|macro|AC97_RESET
mdefine_line|#define  AC97_RESET               0x0000      
singleline_comment|//
DECL|macro|AC97_MASTER_VOL_STEREO
mdefine_line|#define  AC97_MASTER_VOL_STEREO   0x0002      
singleline_comment|// Line Out
DECL|macro|AC97_HEADPHONE_VOL
mdefine_line|#define  AC97_HEADPHONE_VOL       0x0004      
singleline_comment|// 
DECL|macro|AC97_MASTER_VOL_MONO
mdefine_line|#define  AC97_MASTER_VOL_MONO     0x0006      
singleline_comment|// TAD Output
DECL|macro|AC97_MASTER_TONE
mdefine_line|#define  AC97_MASTER_TONE         0x0008      
singleline_comment|//
DECL|macro|AC97_PCBEEP_VOL
mdefine_line|#define  AC97_PCBEEP_VOL          0x000a      
singleline_comment|// none
DECL|macro|AC97_PHONE_VOL
mdefine_line|#define  AC97_PHONE_VOL           0x000c      
singleline_comment|// TAD Input (mono)
DECL|macro|AC97_MIC_VOL
mdefine_line|#define  AC97_MIC_VOL             0x000e      
singleline_comment|// MIC Input (mono)
DECL|macro|AC97_LINEIN_VOL
mdefine_line|#define  AC97_LINEIN_VOL          0x0010      
singleline_comment|// Line Input (stereo)
DECL|macro|AC97_CD_VOL
mdefine_line|#define  AC97_CD_VOL              0x0012      
singleline_comment|// CD Input (stereo)
DECL|macro|AC97_VIDEO_VOL
mdefine_line|#define  AC97_VIDEO_VOL           0x0014      
singleline_comment|// none
DECL|macro|AC97_AUX_VOL
mdefine_line|#define  AC97_AUX_VOL             0x0016      
singleline_comment|// Aux Input (stereo)
DECL|macro|AC97_PCMOUT_VOL
mdefine_line|#define  AC97_PCMOUT_VOL          0x0018      
singleline_comment|// Wave Output (stereo)
DECL|macro|AC97_RECORD_SELECT
mdefine_line|#define  AC97_RECORD_SELECT       0x001a      
singleline_comment|//
DECL|macro|AC97_RECORD_GAIN
mdefine_line|#define  AC97_RECORD_GAIN         0x001c
DECL|macro|AC97_RECORD_GAIN_MIC
mdefine_line|#define  AC97_RECORD_GAIN_MIC     0x001e
DECL|macro|AC97_GENERAL_PURPOSE
mdefine_line|#define  AC97_GENERAL_PURPOSE     0x0020
DECL|macro|AC97_3D_CONTROL
mdefine_line|#define  AC97_3D_CONTROL          0x0022
DECL|macro|AC97_MODEM_RATE
mdefine_line|#define  AC97_MODEM_RATE          0x0024
DECL|macro|AC97_POWER_CONTROL
mdefine_line|#define  AC97_POWER_CONTROL       0x0026
multiline_comment|/* AC&squot;97 2.0 */
DECL|macro|AC97_EXTENDED_ID
mdefine_line|#define AC97_EXTENDED_ID          0x0028       /* Extended Audio ID */
DECL|macro|AC97_EXTENDED_STATUS
mdefine_line|#define AC97_EXTENDED_STATUS      0x002A       /* Extended Audio Status */
DECL|macro|AC97_PCM_FRONT_DAC_RATE
mdefine_line|#define AC97_PCM_FRONT_DAC_RATE   0x002C       /* PCM Front DAC Rate */
DECL|macro|AC97_PCM_SURR_DAC_RATE
mdefine_line|#define AC97_PCM_SURR_DAC_RATE    0x002E       /* PCM Surround DAC Rate */
DECL|macro|AC97_PCM_LFE_DAC_RATE
mdefine_line|#define AC97_PCM_LFE_DAC_RATE     0x0030       /* PCM LFE DAC Rate */
DECL|macro|AC97_PCM_LR_DAC_RATE
mdefine_line|#define AC97_PCM_LR_DAC_RATE      0x0032       /* PCM LR DAC Rate */
DECL|macro|AC97_PCM_MIC_ADC_RATE
mdefine_line|#define AC97_PCM_MIC_ADC_RATE     0x0034       /* PCM MIC ADC Rate */
DECL|macro|AC97_CENTER_LFE_MASTER
mdefine_line|#define AC97_CENTER_LFE_MASTER    0x0036       /* Center + LFE Master Volume */
DECL|macro|AC97_SURROUND_MASTER
mdefine_line|#define AC97_SURROUND_MASTER      0x0038       /* Surround (Rear) Master Volume */
DECL|macro|AC97_RESERVED_3A
mdefine_line|#define AC97_RESERVED_3A          0x003A       /* Reserved */
multiline_comment|/* range 0x3c-0x58 - MODEM */
DECL|macro|AC97_EXTENDED_MODEM_ID
mdefine_line|#define AC97_EXTENDED_MODEM_ID    0x003C
DECL|macro|AC97_EXTEND_MODEM_STAT
mdefine_line|#define AC97_EXTEND_MODEM_STAT    0x003E
DECL|macro|AC97_LINE1_RATE
mdefine_line|#define AC97_LINE1_RATE           0x0040
DECL|macro|AC97_LINE2_RATE
mdefine_line|#define AC97_LINE2_RATE           0x0042
DECL|macro|AC97_HANDSET_RATE
mdefine_line|#define AC97_HANDSET_RATE         0x0044
DECL|macro|AC97_LINE1_LEVEL
mdefine_line|#define AC97_LINE1_LEVEL          0x0046
DECL|macro|AC97_LINE2_LEVEL
mdefine_line|#define AC97_LINE2_LEVEL          0x0048
DECL|macro|AC97_HANDSET_LEVEL
mdefine_line|#define AC97_HANDSET_LEVEL        0x004A
DECL|macro|AC97_GPIO_CONFIG
mdefine_line|#define AC97_GPIO_CONFIG          0x004C
DECL|macro|AC97_GPIO_POLARITY
mdefine_line|#define AC97_GPIO_POLARITY        0x004E
DECL|macro|AC97_GPIO_STICKY
mdefine_line|#define AC97_GPIO_STICKY          0x0050
DECL|macro|AC97_GPIO_WAKE_UP
mdefine_line|#define AC97_GPIO_WAKE_UP         0x0052
DECL|macro|AC97_GPIO_STATUS
mdefine_line|#define AC97_GPIO_STATUS          0x0054
DECL|macro|AC97_MISC_MODEM_STAT
mdefine_line|#define AC97_MISC_MODEM_STAT      0x0056
DECL|macro|AC97_RESERVED_58
mdefine_line|#define AC97_RESERVED_58          0x0058
multiline_comment|/* registers 0x005a - 0x007a are vendor reserved */
DECL|macro|AC97_VENDOR_ID1
mdefine_line|#define AC97_VENDOR_ID1           0x007c
DECL|macro|AC97_VENDOR_ID2
mdefine_line|#define AC97_VENDOR_ID2           0x007e
multiline_comment|/* volume control bit defines */
DECL|macro|AC97_MUTE
mdefine_line|#define AC97_MUTE                 0x8000
DECL|macro|AC97_MICBOOST
mdefine_line|#define AC97_MICBOOST             0x0040
DECL|macro|AC97_LEFTVOL
mdefine_line|#define AC97_LEFTVOL              0x3f00
DECL|macro|AC97_RIGHTVOL
mdefine_line|#define AC97_RIGHTVOL             0x003f
multiline_comment|/* record mux defines */
DECL|macro|AC97_RECMUX_MIC
mdefine_line|#define AC97_RECMUX_MIC           0x0000
DECL|macro|AC97_RECMUX_CD
mdefine_line|#define AC97_RECMUX_CD            0x0101
DECL|macro|AC97_RECMUX_VIDEO
mdefine_line|#define AC97_RECMUX_VIDEO         0x0202
DECL|macro|AC97_RECMUX_AUX
mdefine_line|#define AC97_RECMUX_AUX           0x0303
DECL|macro|AC97_RECMUX_LINE
mdefine_line|#define AC97_RECMUX_LINE          0x0404
DECL|macro|AC97_RECMUX_STEREO_MIX
mdefine_line|#define AC97_RECMUX_STEREO_MIX    0x0505
DECL|macro|AC97_RECMUX_MONO_MIX
mdefine_line|#define AC97_RECMUX_MONO_MIX      0x0606
DECL|macro|AC97_RECMUX_PHONE
mdefine_line|#define AC97_RECMUX_PHONE         0x0707
multiline_comment|/* general purpose register bit defines */
DECL|macro|AC97_GP_LPBK
mdefine_line|#define AC97_GP_LPBK              0x0080       /* Loopback mode */
DECL|macro|AC97_GP_MS
mdefine_line|#define AC97_GP_MS                0x0100       /* Mic Select 0=Mic1, 1=Mic2 */
DECL|macro|AC97_GP_MIX
mdefine_line|#define AC97_GP_MIX               0x0200       /* Mono output select 0=Mix, 1=Mic */
DECL|macro|AC97_GP_RLBK
mdefine_line|#define AC97_GP_RLBK              0x0400       /* Remote Loopback - Modem line codec */
DECL|macro|AC97_GP_LLBK
mdefine_line|#define AC97_GP_LLBK              0x0800       /* Local Loopback - Modem Line codec */
DECL|macro|AC97_GP_LD
mdefine_line|#define AC97_GP_LD                0x1000       /* Loudness 1=on */
DECL|macro|AC97_GP_3D
mdefine_line|#define AC97_GP_3D                0x2000       /* 3D Enhancement 1=on */
DECL|macro|AC97_GP_ST
mdefine_line|#define AC97_GP_ST                0x4000       /* Stereo Enhancement 1=on */
DECL|macro|AC97_GP_POP
mdefine_line|#define AC97_GP_POP               0x8000       /* Pcm Out Path, 0=pre 3D, 1=post 3D */
multiline_comment|/* powerdown control and status bit defines */
multiline_comment|/* status */
DECL|macro|AC97_PWR_MDM
mdefine_line|#define AC97_PWR_MDM              0x0010       /* Modem section ready */
DECL|macro|AC97_PWR_REF
mdefine_line|#define AC97_PWR_REF              0x0008       /* Vref nominal */
DECL|macro|AC97_PWR_ANL
mdefine_line|#define AC97_PWR_ANL              0x0004       /* Analog section ready */
DECL|macro|AC97_PWR_DAC
mdefine_line|#define AC97_PWR_DAC              0x0002       /* DAC section ready */
DECL|macro|AC97_PWR_ADC
mdefine_line|#define AC97_PWR_ADC              0x0001       /* ADC section ready */
multiline_comment|/* control */
DECL|macro|AC97_PWR_PR0
mdefine_line|#define AC97_PWR_PR0              0x0100       /* ADC and Mux powerdown */
DECL|macro|AC97_PWR_PR1
mdefine_line|#define AC97_PWR_PR1              0x0200       /* DAC powerdown */
DECL|macro|AC97_PWR_PR2
mdefine_line|#define AC97_PWR_PR2              0x0400       /* Output mixer powerdown (Vref on) */
DECL|macro|AC97_PWR_PR3
mdefine_line|#define AC97_PWR_PR3              0x0800       /* Output mixer powerdown (Vref off) */
DECL|macro|AC97_PWR_PR4
mdefine_line|#define AC97_PWR_PR4              0x1000       /* AC-link powerdown */
DECL|macro|AC97_PWR_PR5
mdefine_line|#define AC97_PWR_PR5              0x2000       /* Internal Clk disable */
DECL|macro|AC97_PWR_PR6
mdefine_line|#define AC97_PWR_PR6              0x4000       /* HP amp powerdown */
DECL|macro|AC97_PWR_PR7
mdefine_line|#define AC97_PWR_PR7              0x8000       /* Modem off - if supported */
multiline_comment|/* useful power states */
DECL|macro|AC97_PWR_D0
mdefine_line|#define AC97_PWR_D0               0x0000      /* everything on */
DECL|macro|AC97_PWR_D1
mdefine_line|#define AC97_PWR_D1              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR4
DECL|macro|AC97_PWR_D2
mdefine_line|#define AC97_PWR_D2              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR2|AC97_PWR_PR3|AC97_PWR_PR4
DECL|macro|AC97_PWR_D3
mdefine_line|#define AC97_PWR_D3              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR2|AC97_PWR_PR3|AC97_PWR_PR4
DECL|macro|AC97_PWR_ANLOFF
mdefine_line|#define AC97_PWR_ANLOFF          AC97_PWR_PR2|AC97_PWR_PR3  /* analog section off */
multiline_comment|/* Total number of defined registers.  */
DECL|macro|AC97_REG_CNT
mdefine_line|#define AC97_REG_CNT 64
multiline_comment|/* OSS interface to the ac97s.. */
DECL|macro|AC97_STEREO_MASK
mdefine_line|#define AC97_STEREO_MASK (SOUND_MASK_VOLUME|SOUND_MASK_PCM|&bslash;&n;&t;SOUND_MASK_LINE|SOUND_MASK_CD|&bslash;&n;&t;SOUND_MASK_ALTPCM|SOUND_MASK_IGAIN|&bslash;&n;&t;SOUND_MASK_LINE1|SOUND_MASK_VIDEO)
DECL|macro|AC97_SUPPORTED_MASK
mdefine_line|#define AC97_SUPPORTED_MASK (AC97_STEREO_MASK | &bslash;&n;&t;SOUND_MASK_BASS|SOUND_MASK_TREBLE|&bslash;&n;&t;SOUND_MASK_SPEAKER|SOUND_MASK_MIC|&bslash;&n;&t;SOUND_MASK_PHONEIN|SOUND_MASK_PHONEOUT)
DECL|macro|AC97_RECORD_MASK
mdefine_line|#define AC97_RECORD_MASK (SOUND_MASK_MIC|&bslash;&n;&t;SOUND_MASK_CD|SOUND_MASK_IGAIN|SOUND_MASK_VIDEO|&bslash;&n;&t;SOUND_MASK_LINE1| SOUND_MASK_LINE|&bslash;&n;&t;SOUND_MASK_PHONEIN)
DECL|macro|supported_mixer
mdefine_line|#define supported_mixer(CODEC,FOO) ((CODEC)-&gt;supported_mixers &amp; (1&lt;&lt;FOO) )
DECL|struct|ac97_codec
r_struct
id|ac97_codec
(brace
multiline_comment|/* AC97 controller connected with */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|dev_mixer
r_int
id|dev_mixer
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* codec specific init/reset routines, used mainly for 4 or 6 channel support */
DECL|member|codec_init
r_int
(paren
op_star
id|codec_init
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
)paren
suffix:semicolon
multiline_comment|/* controller specific lower leverl ac97 accessing routines */
DECL|member|codec_read
id|u16
(paren
op_star
id|codec_read
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
id|u8
id|reg
)paren
suffix:semicolon
DECL|member|codec_write
r_void
(paren
op_star
id|codec_write
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
id|u8
id|reg
comma
id|u16
id|val
)paren
suffix:semicolon
multiline_comment|/* Wait for codec-ready.  Ok to sleep here.  */
DECL|member|codec_wait
r_void
(paren
op_star
id|codec_wait
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
)paren
suffix:semicolon
multiline_comment|/* OSS mixer masks */
DECL|member|modcnt
r_int
id|modcnt
suffix:semicolon
DECL|member|supported_mixers
r_int
id|supported_mixers
suffix:semicolon
DECL|member|stereo_mixers
r_int
id|stereo_mixers
suffix:semicolon
DECL|member|record_sources
r_int
id|record_sources
suffix:semicolon
DECL|member|bit_resolution
r_int
id|bit_resolution
suffix:semicolon
multiline_comment|/* OSS mixer interface */
DECL|member|read_mixer
r_int
(paren
op_star
id|read_mixer
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_int
id|oss_channel
)paren
suffix:semicolon
DECL|member|write_mixer
r_void
(paren
op_star
id|write_mixer
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_int
id|oss_channel
comma
r_int
r_int
id|left
comma
r_int
r_int
id|right
)paren
suffix:semicolon
DECL|member|recmask_io
r_int
(paren
op_star
id|recmask_io
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_int
id|rw
comma
r_int
id|mask
)paren
suffix:semicolon
DECL|member|mixer_ioctl
r_int
(paren
op_star
id|mixer_ioctl
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* saved OSS mixer states */
DECL|member|mixer_state
r_int
r_int
id|mixer_state
(braket
id|SOUND_MIXER_NRDEVICES
)braket
suffix:semicolon
multiline_comment|/* Software Modem interface */
DECL|member|modem_ioctl
r_int
(paren
op_star
id|modem_ioctl
)paren
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|ac97_read_proc
(paren
r_char
op_star
id|page_out
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|ac97_probe_codec
c_func
(paren
r_struct
id|ac97_codec
op_star
)paren
suffix:semicolon
macro_line|#endif /* _AC97_CODEC_H_ */
eof
