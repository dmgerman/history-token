multiline_comment|/*&n; * Minor numbers for the sound driver.&n; *&n; * Unfortunately Creative called the codec chip of SB as a DSP. For this&n; * reason the /dev/dsp is reserved for digitized audio use. There is a&n; * device for true DSP processors but it will be called something else.&n; * In v3.0 it&squot;s /dev/sndproc but this could be a temporary solution.&n; */
DECL|macro|SND_NDEVS
mdefine_line|#define SND_NDEVS&t;256&t;/* Number of supported devices */
DECL|macro|SND_DEV_CTL
mdefine_line|#define SND_DEV_CTL&t;0&t;/* Control port /dev/mixer */
DECL|macro|SND_DEV_SEQ
mdefine_line|#define SND_DEV_SEQ&t;1&t;/* Sequencer output /dev/sequencer (FM&n;&t;&t;&t;&t;   synthesizer and MIDI output) */
DECL|macro|SND_DEV_MIDIN
mdefine_line|#define SND_DEV_MIDIN&t;2&t;/* Raw midi access */
DECL|macro|SND_DEV_DSP
mdefine_line|#define SND_DEV_DSP&t;3&t;/* Digitized voice /dev/dsp */
DECL|macro|SND_DEV_AUDIO
mdefine_line|#define SND_DEV_AUDIO&t;4&t;/* Sparc compatible /dev/audio */
DECL|macro|SND_DEV_DSP16
mdefine_line|#define SND_DEV_DSP16&t;5&t;/* Like /dev/dsp but 16 bits/sample */
DECL|macro|SND_DEV_STATUS
mdefine_line|#define SND_DEV_STATUS&t;6&t;/* /dev/sndstat */
multiline_comment|/* #7 not in use now. Was in 2.4. Free for use after v3.0. */
DECL|macro|SND_DEV_SEQ2
mdefine_line|#define SND_DEV_SEQ2&t;8&t;/* /dev/sequencer, level 2 interface */
DECL|macro|SND_DEV_SNDPROC
mdefine_line|#define SND_DEV_SNDPROC 9&t;/* /dev/sndproc for programmable devices */
DECL|macro|SND_DEV_PSS
mdefine_line|#define SND_DEV_PSS&t;SND_DEV_SNDPROC
DECL|macro|DSP_DEFAULT_SPEED
mdefine_line|#define DSP_DEFAULT_SPEED&t;8000
DECL|macro|ON
mdefine_line|#define ON&t;&t;1
DECL|macro|OFF
mdefine_line|#define OFF&t;&t;0
DECL|macro|MAX_AUDIO_DEV
mdefine_line|#define MAX_AUDIO_DEV&t;5
DECL|macro|MAX_MIXER_DEV
mdefine_line|#define MAX_MIXER_DEV&t;2
DECL|macro|MAX_SYNTH_DEV
mdefine_line|#define MAX_SYNTH_DEV&t;3
DECL|macro|MAX_MIDI_DEV
mdefine_line|#define MAX_MIDI_DEV&t;6
DECL|macro|MAX_TIMER_DEV
mdefine_line|#define MAX_TIMER_DEV&t;3
eof
