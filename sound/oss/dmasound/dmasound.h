macro_line|#ifndef _dmasound_h_
multiline_comment|/*&n; *  linux/drivers/sound/dmasound/dmasound.h&n; *&n; *&n; *  Minor numbers for the sound driver.&n; *&n; *  Unfortunately Creative called the codec chip of SB as a DSP. For this&n; *  reason the /dev/dsp is reserved for digitized audio use. There is a&n; *  device for true DSP processors but it will be called something else.&n; *  In v3.0 it&squot;s /dev/sndproc but this could be a temporary solution.&n; */
DECL|macro|_dmasound_h_
mdefine_line|#define _dmasound_h_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/* switch on various prinks */
DECL|macro|DEBUG_DMASOUND
mdefine_line|#define DEBUG_DMASOUND 1
DECL|macro|MAX_AUDIO_DEV
mdefine_line|#define MAX_AUDIO_DEV&t;5
DECL|macro|MAX_MIXER_DEV
mdefine_line|#define MAX_MIXER_DEV&t;4
DECL|macro|MAX_SYNTH_DEV
mdefine_line|#define MAX_SYNTH_DEV&t;3
DECL|macro|MAX_MIDI_DEV
mdefine_line|#define MAX_MIDI_DEV&t;6
DECL|macro|MAX_TIMER_DEV
mdefine_line|#define MAX_TIMER_DEV&t;3
DECL|macro|MAX_CATCH_RADIUS
mdefine_line|#define MAX_CATCH_RADIUS&t;10
DECL|macro|le2be16
mdefine_line|#define le2be16(x)&t;(((x)&lt;&lt;8 &amp; 0xff00) | ((x)&gt;&gt;8 &amp; 0x00ff))
DECL|macro|le2be16dbl
mdefine_line|#define le2be16dbl(x)&t;(((x)&lt;&lt;8 &amp; 0xff00ff00) | ((x)&gt;&gt;8 &amp; 0x00ff00ff))
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg, ret) &bslash;&n;&t;do { int error = get_user(ret, (int __user *)(arg)); &bslash;&n;&t;&t;if (error) return error; &bslash;&n;&t;} while (0)
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg, ret)&t;ioctl_return((int __user *)(arg), ret)
DECL|function|ioctl_return
r_static
r_inline
r_int
id|ioctl_return
c_func
(paren
r_int
id|__user
op_star
id|addr
comma
r_int
id|value
)paren
(brace
r_return
id|value
OL
l_int|0
ques
c_cond
id|value
suffix:colon
id|put_user
c_func
(paren
id|value
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Configuration&n;     */
DECL|macro|HAS_8BIT_TABLES
macro_line|#undef HAS_8BIT_TABLES
DECL|macro|HAS_RECORD
macro_line|#undef HAS_RECORD
macro_line|#if defined(CONFIG_DMASOUND_ATARI) || defined(CONFIG_DMASOUND_ATARI_MODULE) ||&bslash;&n;    defined(CONFIG_DMASOUND_PAULA) || defined(CONFIG_DMASOUND_PAULA_MODULE) ||&bslash;&n;    defined(CONFIG_DMASOUND_Q40) || defined(CONFIG_DMASOUND_Q40_MODULE)
DECL|macro|HAS_8BIT_TABLES
mdefine_line|#define HAS_8BIT_TABLES
DECL|macro|MIN_BUFFERS
mdefine_line|#define MIN_BUFFERS&t;4
DECL|macro|MIN_BUFSIZE
mdefine_line|#define MIN_BUFSIZE&t;(1&lt;&lt;12)&t;/* in bytes (- where does this come from ?) */
DECL|macro|MIN_FRAG_SIZE
mdefine_line|#define MIN_FRAG_SIZE&t;8&t;/* not 100% sure about this */
DECL|macro|MAX_BUFSIZE
mdefine_line|#define MAX_BUFSIZE&t;(1&lt;&lt;17)&t;/* Limit for Amiga is 128 kb */
DECL|macro|MAX_FRAG_SIZE
mdefine_line|#define MAX_FRAG_SIZE&t;15&t;/* allow *4 for mono-8 =&gt; stereo-16 (for multi) */
macro_line|#else /* is pmac and multi is off */
DECL|macro|MIN_BUFFERS
mdefine_line|#define MIN_BUFFERS&t;2
DECL|macro|MIN_BUFSIZE
mdefine_line|#define MIN_BUFSIZE&t;(1&lt;&lt;8)&t;/* in bytes */
DECL|macro|MIN_FRAG_SIZE
mdefine_line|#define MIN_FRAG_SIZE&t;8
DECL|macro|MAX_BUFSIZE
mdefine_line|#define MAX_BUFSIZE&t;(1&lt;&lt;18)&t;/* this is somewhat arbitrary for pmac */
DECL|macro|MAX_FRAG_SIZE
mdefine_line|#define MAX_FRAG_SIZE&t;16&t;/* need to allow *4 for mono-8 =&gt; stereo-16 */
macro_line|#endif
DECL|macro|DEFAULT_N_BUFFERS
mdefine_line|#define DEFAULT_N_BUFFERS 4
DECL|macro|DEFAULT_BUFF_SIZE
mdefine_line|#define DEFAULT_BUFF_SIZE (1&lt;&lt;15)
macro_line|#if defined(CONFIG_DMASOUND_PMAC) || defined(CONFIG_DMASOUND_PMAC_MODULE)
DECL|macro|HAS_RECORD
mdefine_line|#define HAS_RECORD
macro_line|#endif
multiline_comment|/*&n;     *  Initialization&n;     */
r_extern
r_int
id|dmasound_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_extern
r_void
id|dmasound_deinit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|dmasound_deinit
mdefine_line|#define dmasound_deinit()&t;do { } while (0)
macro_line|#endif
multiline_comment|/* description of the set-up applies to either hard or soft settings */
r_typedef
r_struct
(brace
DECL|member|format
r_int
id|format
suffix:semicolon
multiline_comment|/* AFMT_* */
DECL|member|stereo
r_int
id|stereo
suffix:semicolon
multiline_comment|/* 0 = mono, 1 = stereo */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* 8/16 bit*/
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* speed */
DECL|typedef|SETTINGS
)brace
id|SETTINGS
suffix:semicolon
multiline_comment|/*&n;     *  Machine definitions&n;     */
r_typedef
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|name2
r_const
r_char
op_star
id|name2
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|dma_alloc
r_void
op_star
(paren
op_star
id|dma_alloc
)paren
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_free
r_void
(paren
op_star
id|dma_free
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|irqinit
r_int
(paren
op_star
id|irqinit
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|member|irqcleanup
r_void
(paren
op_star
id|irqcleanup
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|silence
r_void
(paren
op_star
id|silence
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setFormat
r_int
(paren
op_star
id|setFormat
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|setVolume
r_int
(paren
op_star
id|setVolume
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|setBass
r_int
(paren
op_star
id|setBass
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|setTreble
r_int
(paren
op_star
id|setTreble
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|setGain
r_int
(paren
op_star
id|setGain
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|play
r_void
(paren
op_star
id|play
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|record
r_void
(paren
op_star
id|record
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|mixer_init
r_void
(paren
op_star
id|mixer_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|mixer_ioctl
r_int
(paren
op_star
id|mixer_ioctl
)paren
(paren
id|u_int
comma
id|u_long
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|write_sq_setup
r_int
(paren
op_star
id|write_sq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|read_sq_setup
r_int
(paren
op_star
id|read_sq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|sq_open
r_int
(paren
op_star
id|sq_open
)paren
(paren
id|mode_t
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|state_info
r_int
(paren
op_star
id|state_info
)paren
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|abort_read
r_void
(paren
op_star
id|abort_read
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|min_dsp_speed
r_int
id|min_dsp_speed
suffix:semicolon
DECL|member|max_dsp_speed
r_int
id|max_dsp_speed
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|hardware_afmts
r_int
id|hardware_afmts
suffix:semicolon
multiline_comment|/* OSS says we only return h&squot;ware info */
multiline_comment|/* when queried via SNDCTL_DSP_GETFMTS */
DECL|member|capabilities
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* low-level reply to SNDCTL_DSP_GETCAPS */
DECL|member|default_hard
id|SETTINGS
id|default_hard
suffix:semicolon
multiline_comment|/* open() or init() should set something valid */
DECL|member|default_soft
id|SETTINGS
id|default_soft
suffix:semicolon
multiline_comment|/* you can make it look like old OSS, if you want to */
DECL|typedef|MACHINE
)brace
id|MACHINE
suffix:semicolon
multiline_comment|/*&n;     *  Low level stuff&n;     */
r_typedef
r_struct
(brace
DECL|member|ct_ulaw
id|ssize_t
(paren
op_star
id|ct_ulaw
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_alaw
id|ssize_t
(paren
op_star
id|ct_alaw
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_s8
id|ssize_t
(paren
op_star
id|ct_s8
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_u8
id|ssize_t
(paren
op_star
id|ct_u8
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_s16be
id|ssize_t
(paren
op_star
id|ct_s16be
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_u16be
id|ssize_t
(paren
op_star
id|ct_u16be
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_s16le
id|ssize_t
(paren
op_star
id|ct_s16le
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|member|ct_u16le
id|ssize_t
(paren
op_star
id|ct_u16le
)paren
(paren
r_const
id|u_char
id|__user
op_star
comma
r_int
comma
id|u_char
op_star
comma
id|ssize_t
op_star
comma
id|ssize_t
)paren
suffix:semicolon
DECL|typedef|TRANS
)brace
id|TRANS
suffix:semicolon
DECL|struct|sound_settings
r_struct
id|sound_settings
(brace
DECL|member|mach
id|MACHINE
id|mach
suffix:semicolon
multiline_comment|/* machine dependent things */
DECL|member|hard
id|SETTINGS
id|hard
suffix:semicolon
multiline_comment|/* hardware settings */
DECL|member|soft
id|SETTINGS
id|soft
suffix:semicolon
multiline_comment|/* software settings */
DECL|member|dsp
id|SETTINGS
id|dsp
suffix:semicolon
multiline_comment|/* /dev/dsp default settings */
DECL|member|trans_write
id|TRANS
op_star
id|trans_write
suffix:semicolon
multiline_comment|/* supported translations */
macro_line|#ifdef HAS_RECORD
DECL|member|trans_read
id|TRANS
op_star
id|trans_read
suffix:semicolon
multiline_comment|/* supported translations */
macro_line|#endif
DECL|member|volume_left
r_int
id|volume_left
suffix:semicolon
multiline_comment|/* volume (range is machine dependent) */
DECL|member|volume_right
r_int
id|volume_right
suffix:semicolon
DECL|member|bass
r_int
id|bass
suffix:semicolon
multiline_comment|/* tone (range is machine dependent) */
DECL|member|treble
r_int
id|treble
suffix:semicolon
DECL|member|gain
r_int
id|gain
suffix:semicolon
DECL|member|minDev
r_int
id|minDev
suffix:semicolon
multiline_comment|/* minor device number currently open */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|sound_settings
id|dmasound
suffix:semicolon
macro_line|#ifdef HAS_8BIT_TABLES
r_extern
r_char
id|dmasound_ulaw2dma8
(braket
)braket
suffix:semicolon
r_extern
r_char
id|dmasound_alaw2dma8
(braket
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;     *  Mid level stuff&n;     */
DECL|function|dmasound_set_volume
r_static
r_inline
r_int
id|dmasound_set_volume
c_func
(paren
r_int
id|volume
)paren
(brace
r_return
id|dmasound.mach
dot
id|setVolume
c_func
(paren
id|volume
)paren
suffix:semicolon
)brace
DECL|function|dmasound_set_bass
r_static
r_inline
r_int
id|dmasound_set_bass
c_func
(paren
r_int
id|bass
)paren
(brace
r_return
id|dmasound.mach.setBass
ques
c_cond
id|dmasound.mach
dot
id|setBass
c_func
(paren
id|bass
)paren
suffix:colon
l_int|50
suffix:semicolon
)brace
DECL|function|dmasound_set_treble
r_static
r_inline
r_int
id|dmasound_set_treble
c_func
(paren
r_int
id|treble
)paren
(brace
r_return
id|dmasound.mach.setTreble
ques
c_cond
id|dmasound.mach
dot
id|setTreble
c_func
(paren
id|treble
)paren
suffix:colon
l_int|50
suffix:semicolon
)brace
DECL|function|dmasound_set_gain
r_static
r_inline
r_int
id|dmasound_set_gain
c_func
(paren
r_int
id|gain
)paren
(brace
r_return
id|dmasound.mach.setGain
ques
c_cond
id|dmasound.mach
dot
id|setGain
c_func
(paren
id|gain
)paren
suffix:colon
l_int|100
suffix:semicolon
)brace
multiline_comment|/*&n;     * Sound queue stuff, the heart of the driver&n;     */
DECL|struct|sound_queue
r_struct
id|sound_queue
(brace
multiline_comment|/* buffers allocated for this queue */
DECL|member|numBufs
r_int
id|numBufs
suffix:semicolon
multiline_comment|/* real limits on what the user can have */
DECL|member|bufSize
r_int
id|bufSize
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|buffers
r_char
op_star
op_star
id|buffers
suffix:semicolon
multiline_comment|/* current parameters */
DECL|member|locked
r_int
id|locked
suffix:semicolon
multiline_comment|/* params cannot be modified when != 0 */
DECL|member|user_frags
r_int
id|user_frags
suffix:semicolon
multiline_comment|/* user requests this many */
DECL|member|user_frag_size
r_int
id|user_frag_size
suffix:semicolon
multiline_comment|/* of this size */
DECL|member|max_count
r_int
id|max_count
suffix:semicolon
multiline_comment|/* actual # fragments &lt;= numBufs */
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
multiline_comment|/* internal block size in bytes */
DECL|member|max_active
r_int
id|max_active
suffix:semicolon
multiline_comment|/* in-use fragments &lt;= max_count */
multiline_comment|/* it shouldn&squot;t be necessary to declare any of these volatile */
DECL|member|front
DECL|member|rear
DECL|member|count
r_int
id|front
comma
id|rear
comma
id|count
suffix:semicolon
DECL|member|rear_size
r_int
id|rear_size
suffix:semicolon
multiline_comment|/*&n;     *&t;The use of the playing field depends on the hardware&n;     *&n;     *&t;Atari, PMac: The number of frames that are loaded/playing&n;     *&n;     *&t;Amiga: Bit 0 is set: a frame is loaded&n;     *&t;       Bit 1 is set: a frame is playing&n;     */
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|action_queue
DECL|member|open_queue
DECL|member|sync_queue
id|wait_queue_head_t
id|action_queue
comma
id|open_queue
comma
id|sync_queue
suffix:semicolon
DECL|member|open_mode
r_int
id|open_mode
suffix:semicolon
DECL|member|busy
DECL|member|syncing
DECL|member|xruns
DECL|member|died
r_int
id|busy
comma
id|syncing
comma
id|xruns
comma
id|died
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SLEEP
mdefine_line|#define SLEEP(queue)&t;&t;interruptible_sleep_on_timeout(&amp;queue, HZ)
DECL|macro|WAKE_UP
mdefine_line|#define WAKE_UP(queue)&t;&t;(wake_up_interruptible(&amp;queue))
r_extern
r_struct
id|sound_queue
id|dmasound_write_sq
suffix:semicolon
DECL|macro|write_sq
mdefine_line|#define write_sq&t;dmasound_write_sq
macro_line|#ifdef HAS_RECORD
r_extern
r_struct
id|sound_queue
id|dmasound_read_sq
suffix:semicolon
DECL|macro|read_sq
mdefine_line|#define read_sq&t;&t;dmasound_read_sq
macro_line|#endif
r_extern
r_int
id|dmasound_catchRadius
suffix:semicolon
DECL|macro|catchRadius
mdefine_line|#define catchRadius&t;dmasound_catchRadius
multiline_comment|/* define the value to be put in the byte-swap reg in mac-io&n;   when we want it to swap for us.&n;*/
DECL|macro|BS_VAL
mdefine_line|#define BS_VAL 1
DECL|macro|SW_INPUT_VOLUME_SCALE
mdefine_line|#define SW_INPUT_VOLUME_SCALE&t;4
DECL|macro|SW_INPUT_VOLUME_DEFAULT
mdefine_line|#define SW_INPUT_VOLUME_DEFAULT&t;(128 / SW_INPUT_VOLUME_SCALE)
r_extern
r_int
id|expand_bal
suffix:semicolon
multiline_comment|/* Balance factor for expanding (not volume!) */
r_extern
r_int
id|expand_read_bal
suffix:semicolon
multiline_comment|/* Balance factor for reading */
r_extern
id|uint
id|software_input_volume
suffix:semicolon
multiline_comment|/* software implemented recording volume! */
macro_line|#endif /* _dmasound_h_ */
eof
