macro_line|#ifndef __SOUND_SND_WAVEFRONT_H__
DECL|macro|__SOUND_SND_WAVEFRONT_H__
mdefine_line|#define __SOUND_SND_WAVEFRONT_H__
macro_line|#include &quot;cs4231.h&quot;
macro_line|#include &quot;mpu401.h&quot;
macro_line|#include &quot;hwdep.h&quot;
macro_line|#include &quot;rawmidi.h&quot;
macro_line|#include &quot;wavefront.h&quot;  /* generic OSS/ALSA/user-level wavefront header */
multiline_comment|/* MIDI interface */
r_struct
id|_snd_wavefront_midi
suffix:semicolon
r_struct
id|_snd_wavefront_card
suffix:semicolon
r_struct
id|_snd_wavefront
suffix:semicolon
DECL|typedef|snd_wavefront_midi_t
r_typedef
r_struct
id|_snd_wavefront_midi
id|snd_wavefront_midi_t
suffix:semicolon
DECL|typedef|snd_wavefront_card_t
r_typedef
r_struct
id|_snd_wavefront_card
id|snd_wavefront_card_t
suffix:semicolon
DECL|typedef|snd_wavefront_t
r_typedef
r_struct
id|_snd_wavefront
id|snd_wavefront_t
suffix:semicolon
DECL|enumerator|internal_mpu
DECL|enumerator|external_mpu
DECL|typedef|snd_wavefront_mpu_id
r_typedef
r_enum
(brace
id|internal_mpu
op_assign
l_int|0
comma
id|external_mpu
op_assign
l_int|1
)brace
id|snd_wavefront_mpu_id
suffix:semicolon
DECL|struct|_snd_wavefront_midi
r_struct
id|_snd_wavefront_midi
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* I/O port address */
DECL|member|isvirtual
r_char
id|isvirtual
suffix:semicolon
multiline_comment|/* doing virtual MIDI stuff ? */
DECL|member|istimer
r_char
id|istimer
suffix:semicolon
multiline_comment|/* timer is used */
DECL|member|output_mpu
id|snd_wavefront_mpu_id
id|output_mpu
suffix:semicolon
multiline_comment|/* most-recently-used */
DECL|member|input_mpu
id|snd_wavefront_mpu_id
id|input_mpu
suffix:semicolon
multiline_comment|/* most-recently-used */
DECL|member|mode
r_int
r_int
id|mode
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* MPU401_MODE_XXX */
DECL|member|substream_output
id|snd_rawmidi_substream_t
op_star
id|substream_output
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|substream_input
id|snd_rawmidi_substream_t
op_star
id|substream_input
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|open
id|spinlock_t
id|open
suffix:semicolon
DECL|member|virtual
id|spinlock_t
r_virtual
suffix:semicolon
multiline_comment|/* protects isvirtual */
)brace
suffix:semicolon
DECL|macro|OUTPUT_READY
mdefine_line|#define&t;OUTPUT_READY&t;0x40
DECL|macro|INPUT_AVAIL
mdefine_line|#define&t;INPUT_AVAIL&t;0x80
DECL|macro|MPU_ACK
mdefine_line|#define&t;MPU_ACK&t;&t;0xFE
DECL|macro|UART_MODE_ON
mdefine_line|#define&t;UART_MODE_ON&t;0x3F
r_extern
id|snd_rawmidi_ops_t
id|snd_wavefront_midi_output
suffix:semicolon
r_extern
id|snd_rawmidi_ops_t
id|snd_wavefront_midi_input
suffix:semicolon
r_extern
r_void
id|snd_wavefront_midi_enable_virtual
(paren
id|snd_wavefront_card_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|snd_wavefront_midi_disable_virtual
(paren
id|snd_wavefront_card_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|snd_wavefront_midi_interrupt
(paren
id|snd_wavefront_card_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_midi_start
(paren
id|snd_wavefront_card_t
op_star
)paren
suffix:semicolon
DECL|struct|_snd_wavefront
r_struct
id|_snd_wavefront
(brace
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* &quot;you were one, one of the few ...&quot; */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* low i/o port address */
DECL|member|res_base
r_struct
id|resource
op_star
id|res_base
suffix:semicolon
multiline_comment|/* i/o port resource allocation */
DECL|macro|mpu_data_port
mdefine_line|#define mpu_data_port    base 
DECL|macro|mpu_command_port
mdefine_line|#define mpu_command_port base + 1 /* write semantics */
DECL|macro|mpu_status_port
mdefine_line|#define mpu_status_port  base + 1 /* read semantics */
DECL|macro|data_port
mdefine_line|#define data_port        base + 2 
DECL|macro|status_port
mdefine_line|#define status_port      base + 3 /* read semantics */
DECL|macro|control_port
mdefine_line|#define control_port     base + 3 /* write semantics  */
DECL|macro|block_port
mdefine_line|#define block_port       base + 4 /* 16 bit, writeonly */
DECL|macro|last_block_port
mdefine_line|#define last_block_port  base + 6 /* 16 bit, writeonly */
multiline_comment|/* FX ports. These are mapped through the ICS2115 to the YS225.&n;&t;   The ICS2115 takes care of flipping the relevant pins on the&n;&t;   YS225 so that access to each of these ports does the right&n;&t;   thing. Note: these are NOT documented by Turtle Beach.&n;&t;*/
DECL|macro|fx_status
mdefine_line|#define fx_status       base + 8 
DECL|macro|fx_op
mdefine_line|#define fx_op           base + 8 
DECL|macro|fx_lcr
mdefine_line|#define fx_lcr          base + 9 
DECL|macro|fx_dsp_addr
mdefine_line|#define fx_dsp_addr     base + 0xa
DECL|macro|fx_dsp_page
mdefine_line|#define fx_dsp_page     base + 0xb 
DECL|macro|fx_dsp_lsb
mdefine_line|#define fx_dsp_lsb      base + 0xc 
DECL|macro|fx_dsp_msb
mdefine_line|#define fx_dsp_msb      base + 0xd 
DECL|macro|fx_mod_addr
mdefine_line|#define fx_mod_addr     base + 0xe
DECL|macro|fx_mod_data
mdefine_line|#define fx_mod_data     base + 0xf 
DECL|member|irq_ok
r_volatile
r_int
id|irq_ok
suffix:semicolon
multiline_comment|/* set by interrupt handler */
DECL|member|irq_cnt
r_volatile
r_int
id|irq_cnt
suffix:semicolon
multiline_comment|/* ditto */
DECL|member|debug
r_char
id|debug
suffix:semicolon
multiline_comment|/* debugging flags */
DECL|member|freemem
r_int
id|freemem
suffix:semicolon
multiline_comment|/* installed RAM, in bytes */
DECL|member|fw_version
r_char
id|fw_version
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* major = [0], minor = [1] */
DECL|member|hw_version
r_char
id|hw_version
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* major = [0], minor = [1] */
DECL|member|israw
r_char
id|israw
suffix:semicolon
multiline_comment|/* needs Motorola microcode */
DECL|member|has_fx
r_char
id|has_fx
suffix:semicolon
multiline_comment|/* has FX processor (Tropez+) */
DECL|member|prog_status
r_char
id|prog_status
(braket
id|WF_MAX_PROGRAM
)braket
suffix:semicolon
multiline_comment|/* WF_SLOT_* */
DECL|member|patch_status
r_char
id|patch_status
(braket
id|WF_MAX_PATCH
)braket
suffix:semicolon
multiline_comment|/* WF_SLOT_* */
DECL|member|sample_status
r_char
id|sample_status
(braket
id|WF_MAX_SAMPLE
)braket
suffix:semicolon
multiline_comment|/* WF_ST_* | WF_SLOT_* */
DECL|member|samples_used
r_int
id|samples_used
suffix:semicolon
multiline_comment|/* how many */
DECL|member|interrupts_are_midi
r_char
id|interrupts_are_midi
suffix:semicolon
multiline_comment|/* h/w MPU interrupts enabled ? */
DECL|member|rom_samples_rdonly
r_char
id|rom_samples_rdonly
suffix:semicolon
multiline_comment|/* can we write on ROM samples */
DECL|member|interrupt_sleeper
id|wait_queue_head_t
id|interrupt_sleeper
suffix:semicolon
DECL|member|midi
id|snd_wavefront_midi_t
id|midi
suffix:semicolon
multiline_comment|/* ICS2115 MIDI interface */
)brace
suffix:semicolon
DECL|struct|_snd_wavefront_card
r_struct
id|_snd_wavefront_card
(brace
DECL|member|wavefront
id|snd_wavefront_t
id|wavefront
suffix:semicolon
macro_line|#ifdef __ISAPNP__
DECL|member|wss
r_struct
id|isapnp_dev
op_star
id|wss
suffix:semicolon
DECL|member|ctrl
r_struct
id|isapnp_dev
op_star
id|ctrl
suffix:semicolon
DECL|member|mpu
r_struct
id|isapnp_dev
op_star
id|mpu
suffix:semicolon
DECL|member|synth
r_struct
id|isapnp_dev
op_star
id|synth
suffix:semicolon
macro_line|#endif /* CONFIG_ISAPNP */
)brace
suffix:semicolon
r_extern
r_void
id|snd_wavefront_internal_interrupt
(paren
id|snd_wavefront_card_t
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_interrupt_bits
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_detect_irq
(paren
id|snd_wavefront_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_check_irq
(paren
id|snd_wavefront_t
op_star
id|dev
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_restart
(paren
id|snd_wavefront_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_start
(paren
id|snd_wavefront_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_detect
(paren
id|snd_wavefront_card_t
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_config_midi
(paren
id|snd_wavefront_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_cmd
(paren
id|snd_wavefront_t
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_synth_ioctl
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
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
r_extern
r_int
id|snd_wavefront_synth_open
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_synth_release
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/* FX processor - see also yss225.[ch] */
r_extern
r_int
id|snd_wavefront_fx_start
(paren
id|snd_wavefront_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_fx_detect
(paren
id|snd_wavefront_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_fx_ioctl
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
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
r_extern
r_int
id|snd_wavefront_fx_open
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|snd_wavefront_fx_release
(paren
id|snd_hwdep_t
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/* prefix in all snd_printk() delivered messages */
DECL|macro|LOGNAME
mdefine_line|#define LOGNAME &quot;WaveFront: &quot;
macro_line|#endif  /* __SOUND_SND_WAVEFRONT_H__ */
eof
