multiline_comment|/*&n; * ac97.h &n; * &n; * definitions for the AC97, Intel&squot;s Audio Codec 97 Spec&n; * also includes support for a generic AC97 interface&n; */
macro_line|#ifndef _AC97_H_
DECL|macro|_AC97_H_
mdefine_line|#define _AC97_H_
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;sound_calls.h&quot;
DECL|macro|AC97_RESET
mdefine_line|#define  AC97_RESET              0x0000      
singleline_comment|//
DECL|macro|AC97_MASTER_VOL_STEREO
mdefine_line|#define  AC97_MASTER_VOL_STEREO  0x0002      
singleline_comment|// Line Out
DECL|macro|AC97_HEADPHONE_VOL
mdefine_line|#define  AC97_HEADPHONE_VOL      0x0004      
singleline_comment|// 
DECL|macro|AC97_MASTER_VOL_MONO
mdefine_line|#define  AC97_MASTER_VOL_MONO    0x0006      
singleline_comment|// TAD Output
DECL|macro|AC97_MASTER_TONE
mdefine_line|#define  AC97_MASTER_TONE        0x0008      
singleline_comment|//
DECL|macro|AC97_PCBEEP_VOL
mdefine_line|#define  AC97_PCBEEP_VOL         0x000a      
singleline_comment|// none
DECL|macro|AC97_PHONE_VOL
mdefine_line|#define  AC97_PHONE_VOL          0x000c      
singleline_comment|// TAD Input (mono)
DECL|macro|AC97_MIC_VOL
mdefine_line|#define  AC97_MIC_VOL            0x000e      
singleline_comment|// MIC Input (mono)
DECL|macro|AC97_LINEIN_VOL
mdefine_line|#define  AC97_LINEIN_VOL         0x0010      
singleline_comment|// Line Input (stereo)
DECL|macro|AC97_CD_VOL
mdefine_line|#define  AC97_CD_VOL             0x0012      
singleline_comment|// CD Input (stereo)
DECL|macro|AC97_VIDEO_VOL
mdefine_line|#define  AC97_VIDEO_VOL          0x0014      
singleline_comment|// none
DECL|macro|AC97_AUX_VOL
mdefine_line|#define  AC97_AUX_VOL            0x0016      
singleline_comment|// Aux Input (stereo)
DECL|macro|AC97_PCMOUT_VOL
mdefine_line|#define  AC97_PCMOUT_VOL         0x0018      
singleline_comment|// Wave Output (stereo)
DECL|macro|AC97_RECORD_SELECT
mdefine_line|#define  AC97_RECORD_SELECT      0x001a      
singleline_comment|//
DECL|macro|AC97_RECORD_GAIN
mdefine_line|#define  AC97_RECORD_GAIN        0x001c
DECL|macro|AC97_RECORD_GAIN_MIC
mdefine_line|#define  AC97_RECORD_GAIN_MIC    0x001e
DECL|macro|AC97_GENERAL_PURPOSE
mdefine_line|#define  AC97_GENERAL_PURPOSE    0x0020
DECL|macro|AC97_3D_CONTROL
mdefine_line|#define  AC97_3D_CONTROL         0x0022
DECL|macro|AC97_MODEM_RATE
mdefine_line|#define  AC97_MODEM_RATE         0x0024
DECL|macro|AC97_POWER_CONTROL
mdefine_line|#define  AC97_POWER_CONTROL      0x0026
multiline_comment|/* registers 0x0028 - 0x0058 are reserved */
multiline_comment|/* AC&squot;97 2.0 */
DECL|macro|AC97_EXTENDED_ID
mdefine_line|#define AC97_EXTENDED_ID&t;0x0028&t;/* Extended Audio ID */
DECL|macro|AC97_EXTENDED_STATUS
mdefine_line|#define AC97_EXTENDED_STATUS&t;0x002A&t;/* Extended Audio Status */
DECL|macro|AC97_PCM_FRONT_DAC_RATE
mdefine_line|#define AC97_PCM_FRONT_DAC_RATE 0x002C  /* PCM Front DAC Rate */
DECL|macro|AC97_PCM_SURR_DAC_RATE
mdefine_line|#define AC97_PCM_SURR_DAC_RATE  0x002E  /* PCM Surround DAC Rate */
DECL|macro|AC97_PCM_LFE_DAC_RATE
mdefine_line|#define AC97_PCM_LFE_DAC_RATE   0x0030  /* PCM LFE DAC Rate */
DECL|macro|AC97_PCM_LR_ADC_RATE
mdefine_line|#define AC97_PCM_LR_ADC_RATE&t;0x0032&t;/* PCM LR DAC Rate */
DECL|macro|AC97_PCM_MIC_ADC_RATE
mdefine_line|#define AC97_PCM_MIC_ADC_RATE   0x0034  /* PCM MIC ADC Rate */
DECL|macro|AC97_CENTER_LFE_MASTER
mdefine_line|#define AC97_CENTER_LFE_MASTER  0x0036  /* Center + LFE Master Volume */
DECL|macro|AC97_SURROUND_MASTER
mdefine_line|#define AC97_SURROUND_MASTER    0x0038  /* Surround (Rear) Master Volume */
DECL|macro|AC97_RESERVED_3A
mdefine_line|#define AC97_RESERVED_3A&t;0x003A&t;/* Reserved */
multiline_comment|/* range 0x3c-0x58 - MODEM */
multiline_comment|/* registers 0x005a - 0x007a are vendor reserved */
DECL|macro|AC97_VENDOR_ID1
mdefine_line|#define  AC97_VENDOR_ID1         0x007c
DECL|macro|AC97_VENDOR_ID2
mdefine_line|#define  AC97_VENDOR_ID2         0x007e
multiline_comment|/* volume control bit defines */
DECL|macro|AC97_MUTE
mdefine_line|#define AC97_MUTE                0x8000
DECL|macro|AC97_MICBOOST
mdefine_line|#define AC97_MICBOOST            0x0040
DECL|macro|AC97_LEFTVOL
mdefine_line|#define AC97_LEFTVOL             0x3f00
DECL|macro|AC97_RIGHTVOL
mdefine_line|#define AC97_RIGHTVOL            0x003f
multiline_comment|/* record mux defines */
DECL|macro|AC97_RECMUX_MIC
mdefine_line|#define AC97_RECMUX_MIC          0x0000
DECL|macro|AC97_RECMUX_CD
mdefine_line|#define AC97_RECMUX_CD           0x0101
DECL|macro|AC97_RECMUX_VIDEO
mdefine_line|#define AC97_RECMUX_VIDEO        0x0202      /* not used */
DECL|macro|AC97_RECMUX_AUX
mdefine_line|#define AC97_RECMUX_AUX          0x0303      
DECL|macro|AC97_RECMUX_LINE
mdefine_line|#define AC97_RECMUX_LINE         0x0404      
DECL|macro|AC97_RECMUX_STEREO_MIX
mdefine_line|#define AC97_RECMUX_STEREO_MIX   0x0505
DECL|macro|AC97_RECMUX_MONO_MIX
mdefine_line|#define AC97_RECMUX_MONO_MIX     0x0606
DECL|macro|AC97_RECMUX_PHONE
mdefine_line|#define AC97_RECMUX_PHONE        0x0707
multiline_comment|/* general purpose register bit defines */
DECL|macro|AC97_GP_LPBK
mdefine_line|#define AC97_GP_LPBK             0x0080      /* Loopback mode */
DECL|macro|AC97_GP_MS
mdefine_line|#define AC97_GP_MS               0x0100      /* Mic Select 0=Mic1, 1=Mic2 */
DECL|macro|AC97_GP_MIX
mdefine_line|#define AC97_GP_MIX              0x0200      /* Mono output select 0=Mix, 1=Mic */
DECL|macro|AC97_GP_RLBK
mdefine_line|#define AC97_GP_RLBK             0x0400      /* Remote Loopback - Modem line codec */
DECL|macro|AC97_GP_LLBK
mdefine_line|#define AC97_GP_LLBK             0x0800      /* Local Loopback - Modem Line codec */
DECL|macro|AC97_GP_LD
mdefine_line|#define AC97_GP_LD               0x1000      /* Loudness 1=on */
DECL|macro|AC97_GP_3D
mdefine_line|#define AC97_GP_3D               0x2000      /* 3D Enhancement 1=on */
DECL|macro|AC97_GP_ST
mdefine_line|#define AC97_GP_ST               0x4000      /* Stereo Enhancement 1=on */
DECL|macro|AC97_GP_POP
mdefine_line|#define AC97_GP_POP              0x8000      /* Pcm Out Path, 0=pre 3D, 1=post 3D */
multiline_comment|/* powerdown control and status bit defines */
multiline_comment|/* status */
DECL|macro|AC97_PWR_MDM
mdefine_line|#define AC97_PWR_MDM             0x0010      /* Modem section ready */
DECL|macro|AC97_PWR_REF
mdefine_line|#define AC97_PWR_REF             0x0008      /* Vref nominal */
DECL|macro|AC97_PWR_ANL
mdefine_line|#define AC97_PWR_ANL             0x0004      /* Analog section ready */
DECL|macro|AC97_PWR_DAC
mdefine_line|#define AC97_PWR_DAC             0x0002      /* DAC section ready */
DECL|macro|AC97_PWR_ADC
mdefine_line|#define AC97_PWR_ADC             0x0001      /* ADC section ready */
multiline_comment|/* control */
DECL|macro|AC97_PWR_PR0
mdefine_line|#define AC97_PWR_PR0             0x0100      /* ADC and Mux powerdown */
DECL|macro|AC97_PWR_PR1
mdefine_line|#define AC97_PWR_PR1             0x0200      /* DAC powerdown */
DECL|macro|AC97_PWR_PR2
mdefine_line|#define AC97_PWR_PR2             0x0400      /* Output mixer powerdown (Vref on) */
DECL|macro|AC97_PWR_PR3
mdefine_line|#define AC97_PWR_PR3             0x0800      /* Output mixer powerdown (Vref off) */
DECL|macro|AC97_PWR_PR4
mdefine_line|#define AC97_PWR_PR4             0x1000      /* AC-link powerdown */
DECL|macro|AC97_PWR_PR5
mdefine_line|#define AC97_PWR_PR5             0x2000      /* Internal Clk disable */
DECL|macro|AC97_PWR_PR6
mdefine_line|#define AC97_PWR_PR6             0x4000      /* HP amp powerdown */
DECL|macro|AC97_PWR_PR7
mdefine_line|#define AC97_PWR_PR7             0x8000      /* Modem off - if supported */
multiline_comment|/* useful power states */
DECL|macro|AC97_PWR_D0
mdefine_line|#define AC97_PWR_D0              0x0000      /* everything on */
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
multiline_comment|/* Generic AC97 mixer interface. */
multiline_comment|/* Structure describing access to the hardware. */
DECL|struct|ac97_hwint
r_struct
id|ac97_hwint
(brace
multiline_comment|/* Perform any hardware-specific reset and initialization.  Returns&n;     0 on success, or a negative error code.  */
DECL|member|reset_device
r_int
(paren
op_star
id|reset_device
)paren
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Returns the contents of the specified register REG.  The caller&n;       should check to see if the desired contents are available in&n;       the cache first, if applicable. Returns a positive unsigned value&n;       representing the contents of the register, or a negative error&n;       code.  */
DECL|member|read_reg
r_int
(paren
op_star
id|read_reg
)paren
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
)paren
suffix:semicolon
multiline_comment|/* Writes VALUE to register REG.  Returns 0 on success, or a&n;       negative error code.  */
DECL|member|write_reg
r_int
(paren
op_star
id|write_reg
)paren
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
suffix:semicolon
multiline_comment|/* Hardware-specific information. */
DECL|member|driver_private
r_void
op_star
id|driver_private
suffix:semicolon
multiline_comment|/* Three OSS masks. */
DECL|member|mixer_devmask
r_int
id|mixer_devmask
suffix:semicolon
DECL|member|mixer_stereomask
r_int
id|mixer_stereomask
suffix:semicolon
DECL|member|mixer_recmask
r_int
id|mixer_recmask
suffix:semicolon
multiline_comment|/* The mixer cache. The indices correspond to the AC97 hardware register&n;       number / 2, since the register numbers are always an even number.&n;&n;       Unknown values are set to -1; unsupported registers contain a&n;       -2.  */
DECL|member|last_written_mixer_values
r_int
id|last_written_mixer_values
(braket
id|AC97_REG_CNT
)braket
suffix:semicolon
multiline_comment|/* A cache of values written via OSS; we need these so we can return&n;       the values originally written by the user.&n;&n;       Why the original user values?  Because the real-world hardware&n;       has less precision, and some existing applications assume that&n;       they will get back the exact value that they wrote (aumix).&n;&n;       A -1 value indicates that no value has been written to this mixer&n;       channel via OSS.  */
DECL|member|last_written_OSS_values
r_int
id|last_written_OSS_values
(braket
id|SOUND_MIXER_NRDEVICES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Values stored in the register cache.  */
DECL|macro|AC97_REGVAL_UNKNOWN
mdefine_line|#define AC97_REGVAL_UNKNOWN -1
DECL|macro|AC97_REG_UNSUPPORTED
mdefine_line|#define AC97_REG_UNSUPPORTED -2
DECL|struct|ac97_mixer_value_list
r_struct
id|ac97_mixer_value_list
(brace
multiline_comment|/* Mixer channel to set.  List is terminated by a value of -1.  */
DECL|member|oss_channel
r_int
id|oss_channel
suffix:semicolon
multiline_comment|/* The scaled value to set it to; values generally range from 0-100. */
r_union
(brace
r_struct
(brace
DECL|member|left
DECL|member|right
id|u8
id|left
comma
id|right
suffix:semicolon
DECL|member|stereo
)brace
id|stereo
suffix:semicolon
DECL|member|mono
id|u8
id|mono
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Initialize the ac97 mixer by resetting it.  */
r_extern
r_int
id|ac97_init
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Sets the mixer DEV to the values in VALUE_LIST.  Returns 0 on success,&n;   or a negative error code.  */
r_extern
r_int
id|ac97_set_values
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_struct
id|ac97_mixer_value_list
op_star
id|value_list
)paren
suffix:semicolon
multiline_comment|/* Sets one mixer channel OSS_CHANNEL to the scaled value OSS_VALUE.&n;   Returns the resulting (rescaled) value, or a negative value&n;   representing an error code.&n;&n;   Stereo channels have two values in OSS_VALUE (the left value is in the&n;   lower 8 bits, the right value is in the upper 8 bits). */
r_extern
r_int
id|ac97_set_mixer
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_channel
comma
id|u16
id|oss_value
)paren
suffix:semicolon
multiline_comment|/* Return the contents of the specified AC97 register REG; it uses the&n;   last-written value if it is available.  */
r_extern
r_int
id|ac97_get_register
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
)paren
suffix:semicolon
multiline_comment|/* Writes the specified VALUE to the AC97 register REG in the mixer.&n;   Takes care of setting the last-written cache as well.  */
r_extern
r_int
id|ac97_put_register
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
suffix:semicolon
multiline_comment|/* Returns the last OSS value written to the OSS_CHANNEL mixer channel.  */
r_extern
r_int
id|ac97_get_mixer_scaled
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
id|oss_channel
)paren
suffix:semicolon
multiline_comment|/* Default ioctl. */
r_extern
r_int
id|ac97_mixer_ioctl
(paren
r_struct
id|ac97_hwint
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
suffix:semicolon
multiline_comment|/* Do a complete reset on the AC97 mixer, restoring all mixer registers to&n;   the current values.  Normally used after an APM resume event.  */
r_extern
r_int
id|ac97_reset
(paren
r_struct
id|ac97_hwint
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  c-basic-offset: 4&n; * End:&n; */
eof
