multiline_comment|/*&n; * Minor numbers for the sound driver.&n; */
macro_line|#include &lt;linux/fs.h&gt;
DECL|macro|SND_DEV_CTL
mdefine_line|#define SND_DEV_CTL&t;&t;0&t;/* Control port /dev/mixer */
DECL|macro|SND_DEV_SEQ
mdefine_line|#define SND_DEV_SEQ&t;&t;1&t;/* Sequencer output /dev/sequencer (FM&n;&t;&t;&t;&t;&t;&t;synthesizer and MIDI output) */
DECL|macro|SND_DEV_MIDIN
mdefine_line|#define SND_DEV_MIDIN&t;&t;2&t;/* Raw midi access */
DECL|macro|SND_DEV_DSP
mdefine_line|#define SND_DEV_DSP&t;&t;3&t;/* Digitized voice /dev/dsp */
DECL|macro|SND_DEV_AUDIO
mdefine_line|#define SND_DEV_AUDIO&t;&t;4&t;/* Sparc compatible /dev/audio */
DECL|macro|SND_DEV_DSP16
mdefine_line|#define SND_DEV_DSP16&t;&t;5&t;/* Like /dev/dsp but 16 bits/sample */
multiline_comment|/* #define SND_DEV_STATUS&t;6 */
multiline_comment|/* /dev/sndstat (obsolete) */
DECL|macro|SND_DEV_UNUSED
mdefine_line|#define SND_DEV_UNUSED&t;&t;6
DECL|macro|SND_DEV_AWFM
mdefine_line|#define SND_DEV_AWFM&t;&t;7&t;/* Reserved */
DECL|macro|SND_DEV_SEQ2
mdefine_line|#define SND_DEV_SEQ2&t;&t;8&t;/* /dev/sequencer, level 2 interface */
multiline_comment|/* #define SND_DEV_SNDPROC&t;9 */
multiline_comment|/* /dev/sndproc for programmable devices (not used) */
multiline_comment|/* #define SND_DEV_DMMIDI&t;9 */
DECL|macro|SND_DEV_SYNTH
mdefine_line|#define SND_DEV_SYNTH&t;&t;9&t;/* Raw synth access /dev/synth (same as /dev/dmfm) */
DECL|macro|SND_DEV_DMFM
mdefine_line|#define SND_DEV_DMFM&t;&t;10&t;/* Raw synth access /dev/dmfm */
DECL|macro|SND_DEV_UNKNOWN11
mdefine_line|#define SND_DEV_UNKNOWN11&t;11
DECL|macro|SND_DEV_ADSP
mdefine_line|#define SND_DEV_ADSP&t;&t;12&t;/* Like /dev/dsp (obsolete) */
DECL|macro|SND_DEV_AMIDI
mdefine_line|#define SND_DEV_AMIDI&t;&t;13&t;/* Like /dev/midi (obsolete) */
DECL|macro|SND_DEV_ADMMIDI
mdefine_line|#define SND_DEV_ADMMIDI&t;&t;14&t;/* Like /dev/dmmidi (onsolete) */
multiline_comment|/*&n; *&t;Sound core interface functions&n; */
r_extern
r_int
id|register_sound_special
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_int
id|register_sound_mixer
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_sound_midi
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_sound_dsp
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_sound_synth
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|unregister_sound_special
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_void
id|unregister_sound_mixer
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_void
id|unregister_sound_midi
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_void
id|unregister_sound_dsp
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_void
id|unregister_sound_synth
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
eof
