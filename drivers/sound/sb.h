DECL|macro|DSP_RESET
mdefine_line|#define DSP_RESET&t;(devc-&gt;base + 0x6)
DECL|macro|DSP_READ
mdefine_line|#define DSP_READ&t;(devc-&gt;base + 0xA)
DECL|macro|DSP_WRITE
mdefine_line|#define DSP_WRITE&t;(devc-&gt;base + 0xC)
DECL|macro|DSP_COMMAND
mdefine_line|#define DSP_COMMAND&t;(devc-&gt;base + 0xC)
DECL|macro|DSP_STATUS
mdefine_line|#define DSP_STATUS&t;(devc-&gt;base + 0xC)
DECL|macro|DSP_DATA_AVAIL
mdefine_line|#define DSP_DATA_AVAIL&t;(devc-&gt;base + 0xE)
DECL|macro|DSP_DATA_AVL16
mdefine_line|#define DSP_DATA_AVL16&t;(devc-&gt;base + 0xF)
DECL|macro|MIXER_ADDR
mdefine_line|#define MIXER_ADDR&t;(devc-&gt;base + 0x4)
DECL|macro|MIXER_DATA
mdefine_line|#define MIXER_DATA&t;(devc-&gt;base + 0x5)
DECL|macro|OPL3_LEFT
mdefine_line|#define OPL3_LEFT&t;(devc-&gt;base + 0x0)
DECL|macro|OPL3_RIGHT
mdefine_line|#define OPL3_RIGHT&t;(devc-&gt;base + 0x2)
DECL|macro|OPL3_BOTH
mdefine_line|#define OPL3_BOTH&t;(devc-&gt;base + 0x8)
multiline_comment|/* DSP Commands */
DECL|macro|DSP_CMD_SPKON
mdefine_line|#define DSP_CMD_SPKON&t;&t;0xD1
DECL|macro|DSP_CMD_SPKOFF
mdefine_line|#define DSP_CMD_SPKOFF&t;&t;0xD3
DECL|macro|DSP_CMD_DMAON
mdefine_line|#define DSP_CMD_DMAON&t;&t;0xD0
DECL|macro|DSP_CMD_DMAOFF
mdefine_line|#define DSP_CMD_DMAOFF&t;&t;0xD4
DECL|macro|IMODE_NONE
mdefine_line|#define IMODE_NONE&t;&t;0
DECL|macro|IMODE_OUTPUT
mdefine_line|#define IMODE_OUTPUT&t;&t;PCM_ENABLE_OUTPUT
DECL|macro|IMODE_INPUT
mdefine_line|#define IMODE_INPUT&t;&t;PCM_ENABLE_INPUT
DECL|macro|IMODE_INIT
mdefine_line|#define IMODE_INIT&t;&t;3
DECL|macro|IMODE_MIDI
mdefine_line|#define IMODE_MIDI&t;&t;4
DECL|macro|NORMAL_MIDI
mdefine_line|#define NORMAL_MIDI&t;0
DECL|macro|UART_MIDI
mdefine_line|#define UART_MIDI&t;1
multiline_comment|/*&n; * Device models&n; */
DECL|macro|MDL_NONE
mdefine_line|#define MDL_NONE&t;0
DECL|macro|MDL_SB1
mdefine_line|#define MDL_SB1&t;&t;1&t;/* SB1.0 or 1.5 */
DECL|macro|MDL_SB2
mdefine_line|#define MDL_SB2&t;&t;2&t;/* SB2.0 */
DECL|macro|MDL_SB201
mdefine_line|#define MDL_SB201&t;3&t;/* SB2.01 */
DECL|macro|MDL_SBPRO
mdefine_line|#define MDL_SBPRO&t;4&t;/* SB Pro */
DECL|macro|MDL_SB16
mdefine_line|#define MDL_SB16&t;5&t;/* SB16/32/AWE */
DECL|macro|MDL_SBPNP
mdefine_line|#define MDL_SBPNP &t;6&t;/* SB16/32/AWE PnP */
DECL|macro|MDL_JAZZ
mdefine_line|#define MDL_JAZZ&t;10&t;/* Media Vision Jazz16 */
DECL|macro|MDL_SMW
mdefine_line|#define MDL_SMW&t;&t;11&t;/* Logitech SoundMan Wave (Jazz16) */
DECL|macro|MDL_ESS
mdefine_line|#define MDL_ESS&t;&t;12&t;/* ESS ES688 and ES1688 */
DECL|macro|MDL_AZTECH
mdefine_line|#define MDL_AZTECH&t;13&t;/* Aztech Sound Galaxy family */
DECL|macro|MDL_ES1868MIDI
mdefine_line|#define MDL_ES1868MIDI&t;14&t;/* MIDI port of ESS1868 */
DECL|macro|MDL_AEDSP
mdefine_line|#define MDL_AEDSP&t;15&t;/* Audio Excel DSP 16 */
DECL|macro|MDL_ESSPCI
mdefine_line|#define MDL_ESSPCI&t;16&t;/* ESS PCI card */
DECL|macro|MDL_YMPCI
mdefine_line|#define MDL_YMPCI&t;17&t;/* Yamaha PCI sb in emulation */
DECL|macro|SUBMDL_ALS007
mdefine_line|#define SUBMDL_ALS007&t;42&t;/* ALS-007 differs from SB16 only in mixer */
multiline_comment|/* register assignment */
DECL|macro|SUBMDL_ALS100
mdefine_line|#define SUBMDL_ALS100&t;43&t;/* ALS-100 allows sampling rates of up */
multiline_comment|/* to 48kHz */
multiline_comment|/*&n; * Config flags&n; */
DECL|macro|SB_NO_MIDI
mdefine_line|#define SB_NO_MIDI&t;0x00000001
DECL|macro|SB_NO_MIXER
mdefine_line|#define SB_NO_MIXER&t;0x00000002
DECL|macro|SB_NO_AUDIO
mdefine_line|#define SB_NO_AUDIO&t;0x00000004
DECL|macro|SB_NO_RECORDING
mdefine_line|#define SB_NO_RECORDING&t;0x00000008 /* No audio recording */
DECL|macro|SB_MIDI_ONLY
mdefine_line|#define SB_MIDI_ONLY&t;(SB_NO_AUDIO|SB_NO_MIXER)
DECL|macro|SB_PCI_IRQ
mdefine_line|#define SB_PCI_IRQ&t;0x00000010 /* PCI shared IRQ */
DECL|struct|mixer_def
r_struct
id|mixer_def
(brace
DECL|member|regno
r_int
r_int
id|regno
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bitoffs
r_int
r_int
id|bitoffs
suffix:colon
l_int|4
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:colon
l_int|4
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mixer_tab
r_typedef
r_struct
id|mixer_def
id|mixer_tab
(braket
l_int|32
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|mixer_ent
r_typedef
r_struct
id|mixer_def
id|mixer_ent
suffix:semicolon
DECL|struct|sb_module_options
r_struct
id|sb_module_options
(brace
DECL|member|esstype
r_int
id|esstype
suffix:semicolon
multiline_comment|/* ESS chip type */
DECL|member|acer
r_int
id|acer
suffix:semicolon
multiline_comment|/* Do acer notebook init? */
DECL|member|sm_games
r_int
id|sm_games
suffix:semicolon
multiline_comment|/* Logitech soundman games? */
)brace
suffix:semicolon
DECL|struct|sb_devc
r_typedef
r_struct
id|sb_devc
(brace
DECL|member|dev
r_int
id|dev
suffix:semicolon
multiline_comment|/* Hardware parameters */
DECL|member|osp
r_int
op_star
id|osp
suffix:semicolon
DECL|member|minor
DECL|member|major
r_int
id|minor
comma
id|major
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|model
DECL|member|submodel
r_int
id|model
comma
id|submodel
suffix:semicolon
DECL|member|caps
r_int
id|caps
suffix:semicolon
DECL|macro|SBCAP_STEREO
macro_line|#&t;define SBCAP_STEREO&t;0x00000001
DECL|macro|SBCAP_16BITS
macro_line|#&t;define SBCAP_16BITS&t;0x00000002
multiline_comment|/* Hardware resources */
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma8
DECL|member|dma16
r_int
id|dma8
comma
id|dma16
suffix:semicolon
DECL|member|pcibase
r_int
id|pcibase
suffix:semicolon
multiline_comment|/* For ESS Maestro etc */
multiline_comment|/* State variables */
DECL|member|opened
r_int
id|opened
suffix:semicolon
multiline_comment|/* new audio fields for full duplex support */
DECL|member|fullduplex
r_int
id|fullduplex
suffix:semicolon
DECL|member|duplex
r_int
id|duplex
suffix:semicolon
DECL|member|speed
DECL|member|bits
DECL|member|channels
r_int
id|speed
comma
id|bits
comma
id|channels
suffix:semicolon
DECL|member|irq_ok
r_volatile
r_int
id|irq_ok
suffix:semicolon
DECL|member|intr_active
DECL|member|irq_mode
r_volatile
r_int
id|intr_active
comma
id|irq_mode
suffix:semicolon
multiline_comment|/* duplicate audio fields for full duplex support */
DECL|member|intr_active_16
DECL|member|irq_mode_16
r_volatile
r_int
id|intr_active_16
comma
id|irq_mode_16
suffix:semicolon
multiline_comment|/* Mixer fields */
DECL|member|levels
r_int
op_star
id|levels
suffix:semicolon
DECL|member|iomap
id|mixer_tab
op_star
id|iomap
suffix:semicolon
DECL|member|mixer_caps
DECL|member|recmask
DECL|member|outmask
DECL|member|supported_devices
r_int
id|mixer_caps
comma
id|recmask
comma
id|outmask
comma
id|supported_devices
suffix:semicolon
DECL|member|supported_rec_devices
DECL|member|supported_out_devices
r_int
id|supported_rec_devices
comma
id|supported_out_devices
suffix:semicolon
DECL|member|my_mixerdev
r_int
id|my_mixerdev
suffix:semicolon
DECL|member|sbmixnum
r_int
id|sbmixnum
suffix:semicolon
multiline_comment|/* Audio fields */
DECL|member|trg_buf
r_int
r_int
id|trg_buf
suffix:semicolon
DECL|member|trigger_bits
r_int
id|trigger_bits
suffix:semicolon
DECL|member|trg_bytes
r_int
id|trg_bytes
suffix:semicolon
DECL|member|trg_intrflag
r_int
id|trg_intrflag
suffix:semicolon
DECL|member|trg_restart
r_int
id|trg_restart
suffix:semicolon
multiline_comment|/* duplicate audio fields for full duplex support */
DECL|member|trg_buf_16
r_int
r_int
id|trg_buf_16
suffix:semicolon
DECL|member|trigger_bits_16
r_int
id|trigger_bits_16
suffix:semicolon
DECL|member|trg_bytes_16
r_int
id|trg_bytes_16
suffix:semicolon
DECL|member|trg_intrflag_16
r_int
id|trg_intrflag_16
suffix:semicolon
DECL|member|trg_restart_16
r_int
id|trg_restart_16
suffix:semicolon
DECL|member|tconst
r_int
r_char
id|tconst
suffix:semicolon
multiline_comment|/* MIDI fields */
DECL|member|my_mididev
r_int
id|my_mididev
suffix:semicolon
DECL|member|input_opened
r_int
id|input_opened
suffix:semicolon
DECL|member|midi_broken
r_int
id|midi_broken
suffix:semicolon
DECL|member|midi_input_intr
r_void
(paren
op_star
id|midi_input_intr
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
suffix:semicolon
DECL|member|midi_irq_cookie
r_void
op_star
id|midi_irq_cookie
suffix:semicolon
multiline_comment|/* IRQ cookie for the midi */
DECL|member|sbmo
r_struct
id|sb_module_options
id|sbmo
suffix:semicolon
multiline_comment|/* Module options */
DECL|typedef|sb_devc
)brace
id|sb_devc
suffix:semicolon
multiline_comment|/*&n; *&t;PCI card types&n; */
DECL|macro|SB_PCI_ESSMAESTRO
mdefine_line|#define&t;SB_PCI_ESSMAESTRO&t;1&t;/* ESS Maestro Legacy */
DECL|macro|SB_PCI_YAMAHA
mdefine_line|#define&t;SB_PCI_YAMAHA&t;&t;2&t;/* Yamaha Legacy */
multiline_comment|/* &n; *&t;Functions&n; */
r_int
id|sb_dsp_command
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
id|sb_dsp_get_byte
c_func
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_int
id|sb_dsp_reset
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_void
id|sb_setmixer
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_int
id|port
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_int
r_int
id|sb_getmixer
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_int
id|sb_dsp_detect
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_int
id|pci
comma
r_int
id|pciio
comma
r_struct
id|sb_module_options
op_star
id|sbmo
)paren
suffix:semicolon
r_int
id|sb_dsp_init
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|sb_dsp_unload
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_int
id|sbmpu
)paren
suffix:semicolon
r_int
id|sb_mixer_init
c_func
(paren
id|sb_devc
op_star
id|devc
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|sb_mixer_unload
c_func
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_void
id|sb_mixer_set_stereo
(paren
id|sb_devc
op_star
id|devc
comma
r_int
id|mode
)paren
suffix:semicolon
r_void
id|smw_mixer_init
c_func
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_void
id|sb_dsp_midi_init
(paren
id|sb_devc
op_star
id|devc
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|sb_audio_init
(paren
id|sb_devc
op_star
id|devc
comma
r_char
op_star
id|name
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|sb_midi_interrupt
(paren
id|sb_devc
op_star
id|devc
)paren
suffix:semicolon
r_void
id|sb_chgmixer
(paren
id|sb_devc
op_star
id|devc
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_int
id|sb_common_mixer_set
c_func
(paren
id|sb_devc
op_star
id|devc
comma
r_int
id|dev
comma
r_int
id|left
comma
r_int
id|right
)paren
suffix:semicolon
r_int
id|sb_audio_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
suffix:semicolon
r_void
id|sb_audio_close
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_extern
id|sb_devc
op_star
id|last_sb
suffix:semicolon
multiline_comment|/*&t;From sb_common.c */
r_void
id|sb_dsp_disable_midi
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_void
id|sb_dsp_disable_recording
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_int
id|probe_sbmpu
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|module
op_star
id|owner
)paren
suffix:semicolon
r_void
id|unload_sbmpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|unload_sb16
c_func
(paren
r_struct
id|address_info
op_star
id|hw_info
)paren
suffix:semicolon
r_void
id|unload_sb16midi
c_func
(paren
r_struct
id|address_info
op_star
id|hw_info
)paren
suffix:semicolon
eof
