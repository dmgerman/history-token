multiline_comment|/*&n; *  linux/drivers/sound/dmasound/dmasound_paula.c&n; *&n; *  Amiga `Paula&squot; DMA Sound Driver&n; *&n; *  See linux/drivers/sound/dmasound/dmasound_core.c for copyright and credits&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;dmasound.h&quot;
multiline_comment|/*&n;    *&t;The minimum period for audio depends on htotal (for OCS/ECS/AGA)&n;    *&t;(Imported from arch/m68k/amiga/amisound.c)&n;    */
r_extern
r_volatile
id|u_short
id|amiga_audio_min_period
suffix:semicolon
multiline_comment|/*&n;    *&t;amiga_mksound() should be able to restore the period after beeping&n;    *&t;(Imported from arch/m68k/amiga/amisound.c)&n;    */
r_extern
id|u_short
id|amiga_audio_period
suffix:semicolon
multiline_comment|/*&n;    *&t;Audio DMA masks&n;    */
DECL|macro|AMI_AUDIO_OFF
mdefine_line|#define AMI_AUDIO_OFF&t;(DMAF_AUD0 | DMAF_AUD1 | DMAF_AUD2 | DMAF_AUD3)
DECL|macro|AMI_AUDIO_8
mdefine_line|#define AMI_AUDIO_8&t;(DMAF_SETCLR | DMAF_MASTER | DMAF_AUD0 | DMAF_AUD1)
DECL|macro|AMI_AUDIO_14
mdefine_line|#define AMI_AUDIO_14&t;(AMI_AUDIO_8 | DMAF_AUD2 | DMAF_AUD3)
multiline_comment|/*&n;     *  Helper pointers for 16(14)-bit sound&n;     */
DECL|variable|write_sq_block_size_half
DECL|variable|write_sq_block_size_quarter
r_static
r_int
id|write_sq_block_size_half
comma
id|write_sq_block_size_quarter
suffix:semicolon
multiline_comment|/*** Low level stuff *********************************************************/
r_static
r_void
id|AmiOpen
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|AmiRelease
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
op_star
id|AmiAlloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_static
r_void
id|AmiFree
c_func
(paren
r_void
op_star
id|obj
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_static
r_int
id|AmiIrqInit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_static
r_void
id|AmiIrqCleanUp
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|AmiSilence
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|AmiInit
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|AmiSetFormat
c_func
(paren
r_int
id|format
)paren
suffix:semicolon
r_static
r_int
id|AmiSetVolume
c_func
(paren
r_int
id|volume
)paren
suffix:semicolon
r_static
r_int
id|AmiSetTreble
c_func
(paren
r_int
id|treble
)paren
suffix:semicolon
r_static
r_void
id|AmiPlayNextFrame
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_static
r_void
id|AmiPlay
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|AmiInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
multiline_comment|/*&n;     *  Heartbeat interferes with sound since the 7 kHz low-pass filter and the&n;     *  power LED are controlled by the same line.&n;     */
macro_line|#ifdef CONFIG_APUS
DECL|macro|mach_heartbeat
mdefine_line|#define mach_heartbeat&t;ppc_md.heartbeat
macro_line|#endif
DECL|variable|saved_heartbeat
r_static
r_void
(paren
op_star
id|saved_heartbeat
)paren
(paren
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|function|disable_heartbeat
r_static
r_inline
r_void
id|disable_heartbeat
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mach_heartbeat
)paren
(brace
id|saved_heartbeat
op_assign
id|mach_heartbeat
suffix:semicolon
id|mach_heartbeat
op_assign
l_int|NULL
suffix:semicolon
)brace
id|AmiSetTreble
c_func
(paren
id|dmasound.treble
)paren
suffix:semicolon
)brace
DECL|function|enable_heartbeat
r_static
r_inline
r_void
id|enable_heartbeat
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|saved_heartbeat
)paren
id|mach_heartbeat
op_assign
id|saved_heartbeat
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_HEARTBEAT */
DECL|macro|disable_heartbeat
mdefine_line|#define disable_heartbeat()&t;do { } while (0)
DECL|macro|enable_heartbeat
mdefine_line|#define enable_heartbeat()&t;do { } while (0)
macro_line|#endif /* !CONFIG_HEARTBEAT */
multiline_comment|/*** Mid level stuff *********************************************************/
r_static
r_void
id|AmiMixerInit
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|AmiMixerIoctl
c_func
(paren
id|u_int
id|cmd
comma
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_void
id|AmiWriteSqSetup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|AmiStateInfo
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
multiline_comment|/*** Translations ************************************************************/
multiline_comment|/* ++TeSche: radically changed for new expanding purposes...&n; *&n; * These two routines now deal with copying/expanding/translating the samples&n; * from user space into our buffer at the right frequency. They take care about&n; * how much data there&squot;s actually to read, how much buffer space there is and&n; * to convert samples into the right frequency/encoding. They will only work on&n; * complete samples so it may happen they leave some bytes in the input stream&n; * if the user didn&squot;t write a multiple of the current sample size. They both&n; * return the number of bytes they&squot;ve used from both streams so you may detect&n; * such a situation. Luckily all programs should be able to cope with that.&n; *&n; * I think I&squot;ve optimized anything as far as one can do in plain C, all&n; * variables should fit in registers and the loops are really short. There&squot;s&n; * one loop for every possible situation. Writing a more generalized and thus&n; * parameterized loop would only produce slower code. Feel free to optimize&n; * this in assembler if you like. :)&n; *&n; * I think these routines belong here because they&squot;re not yet really hardware&n; * independent, especially the fact that the Falcon can play 16bit samples&n; * only in stereo is hardcoded in both of them!&n; *&n; * ++geert: split in even more functions (one per format)&n; */
multiline_comment|/*&n;     *  Native format&n;     */
DECL|function|ami_ct_s8
r_static
id|ssize_t
id|ami_ct_s8
c_func
(paren
r_const
id|u_char
op_star
id|userPtr
comma
r_int
id|userCount
comma
id|u_char
id|frame
(braket
)braket
comma
id|ssize_t
op_star
id|frameUsed
comma
id|ssize_t
id|frameLeft
)paren
(brace
id|ssize_t
id|count
comma
id|used
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dmasound.soft.stereo
)paren
(brace
r_void
op_star
id|p
op_assign
op_amp
id|frame
(braket
op_star
id|frameUsed
)braket
suffix:semicolon
id|count
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|userCount
comma
id|frameLeft
)paren
op_amp
op_complement
l_int|1
suffix:semicolon
id|used
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|userPtr
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|u_char
op_star
id|left
op_assign
op_amp
id|frame
(braket
op_star
id|frameUsed
op_rshift
l_int|1
)braket
suffix:semicolon
id|u_char
op_star
id|right
op_assign
id|left
op_plus
id|write_sq_block_size_half
suffix:semicolon
id|count
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|userCount
comma
id|frameLeft
)paren
op_rshift
l_int|1
op_amp
op_complement
l_int|1
suffix:semicolon
id|used
op_assign
id|count
op_star
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
op_star
id|left
op_increment
comma
id|userPtr
op_increment
)paren
op_logical_or
id|get_user
c_func
(paren
op_star
id|right
op_increment
comma
id|userPtr
op_increment
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
)brace
op_star
id|frameUsed
op_add_assign
id|used
suffix:semicolon
r_return
id|used
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Copy and convert 8 bit data&n;     */
DECL|macro|GENERATE_AMI_CT8
mdefine_line|#define GENERATE_AMI_CT8(funcname, convsample)&t;&t;&t;&t;&bslash;&n;static ssize_t funcname(const u_char *userPtr, size_t userCount,&t;&bslash;&n;&t;&t;&t;u_char frame[], ssize_t *frameUsed,&t;&t;&bslash;&n;&t;&t;&t;ssize_t frameLeft)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssize_t count, used;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!dmasound.soft.stereo) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;u_char *p = &amp;frame[*frameUsed];&t;&t;&t;&t;&bslash;&n;&t;&t;count = min_t(size_t, userCount, frameLeft) &amp; ~1;&t;&bslash;&n;&t;&t;used = count;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (count &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;u_char data;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, userPtr++))&t;&t;&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*p++ = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;count--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;u_char *left = &amp;frame[*frameUsed&gt;&gt;1];&t;&t;&t;&bslash;&n;&t;&t;u_char *right = left+write_sq_block_size_half;&t;&t;&bslash;&n;&t;&t;count = min_t(size_t, userCount, frameLeft)&gt;&gt;1 &amp; ~1;&t;&bslash;&n;&t;&t;used = count*2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (count &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;u_char data;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, userPtr++))&t;&t;&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*left++ = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, userPtr++))&t;&t;&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*right++ = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;count--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*frameUsed += used;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return used;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|AMI_CT_ULAW
mdefine_line|#define AMI_CT_ULAW(x)&t;(dmasound_ulaw2dma8[(x)])
DECL|macro|AMI_CT_ALAW
mdefine_line|#define AMI_CT_ALAW(x)&t;(dmasound_alaw2dma8[(x)])
DECL|macro|AMI_CT_U8
mdefine_line|#define AMI_CT_U8(x)&t;((x) ^ 0x80)
id|GENERATE_AMI_CT8
c_func
(paren
id|ami_ct_ulaw
comma
id|AMI_CT_ULAW
)paren
id|GENERATE_AMI_CT8
c_func
(paren
id|ami_ct_alaw
comma
id|AMI_CT_ALAW
)paren
id|GENERATE_AMI_CT8
c_func
(paren
id|ami_ct_u8
comma
id|AMI_CT_U8
)paren
multiline_comment|/*&n;     *  Copy and convert 16 bit data&n;     */
DECL|macro|GENERATE_AMI_CT_16
mdefine_line|#define GENERATE_AMI_CT_16(funcname, convsample)&t;&t;&t;&bslash;&n;static ssize_t funcname(const u_char *userPtr, size_t userCount,&t;&bslash;&n;&t;&t;&t;u_char frame[], ssize_t *frameUsed,&t;&t;&bslash;&n;&t;&t;&t;ssize_t frameLeft)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssize_t count, used;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u_short data;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!dmasound.soft.stereo) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;u_char *high = &amp;frame[*frameUsed&gt;&gt;1];&t;&t;&t;&bslash;&n;&t;&t;u_char *low = high+write_sq_block_size_half;&t;&t;&bslash;&n;&t;&t;count = min_t(size_t, userCount, frameLeft)&gt;&gt;1 &amp; ~1;&t;&bslash;&n;&t;&t;used = count*2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (count &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, ((u_short *)userPtr)++))&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;data = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;*high++ = data&gt;&gt;8;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*low++ = (data&gt;&gt;2) &amp; 0x3f;&t;&t;&t;&bslash;&n;&t;&t;&t;count--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;u_char *lefth = &amp;frame[*frameUsed&gt;&gt;2];&t;&t;&t;&bslash;&n;&t;&t;u_char *leftl = lefth+write_sq_block_size_quarter;&t;&bslash;&n;&t;&t;u_char *righth = lefth+write_sq_block_size_half;&t;&bslash;&n;&t;&t;u_char *rightl = righth+write_sq_block_size_quarter;&t;&bslash;&n;&t;&t;count = min_t(size_t, userCount, frameLeft)&gt;&gt;2 &amp; ~1;&t;&bslash;&n;&t;&t;used = count*4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (count &gt; 0) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, ((u_short *)userPtr)++))&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;data = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;*lefth++ = data&gt;&gt;8;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*leftl++ = (data&gt;&gt;2) &amp; 0x3f;&t;&t;&t;&bslash;&n;&t;&t;&t;if (get_user(data, ((u_short *)userPtr)++))&t;&bslash;&n;&t;&t;&t;&t;return -EFAULT;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;data = convsample(data);&t;&t;&t;&bslash;&n;&t;&t;&t;*righth++ = data&gt;&gt;8;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*rightl++ = (data&gt;&gt;2) &amp; 0x3f;&t;&t;&t;&bslash;&n;&t;&t;&t;count--;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*frameUsed += used;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return used;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|AMI_CT_S16BE
mdefine_line|#define AMI_CT_S16BE(x)&t;(x)
DECL|macro|AMI_CT_U16BE
mdefine_line|#define AMI_CT_U16BE(x)&t;((x) ^ 0x8000)
DECL|macro|AMI_CT_S16LE
mdefine_line|#define AMI_CT_S16LE(x)&t;(le2be16((x)))
DECL|macro|AMI_CT_U16LE
mdefine_line|#define AMI_CT_U16LE(x)&t;(le2be16((x)) ^ 0x8000)
id|GENERATE_AMI_CT_16
c_func
(paren
id|ami_ct_s16be
comma
id|AMI_CT_S16BE
)paren
id|GENERATE_AMI_CT_16
c_func
(paren
id|ami_ct_u16be
comma
id|AMI_CT_U16BE
)paren
id|GENERATE_AMI_CT_16
c_func
(paren
id|ami_ct_s16le
comma
id|AMI_CT_S16LE
)paren
id|GENERATE_AMI_CT_16
c_func
(paren
id|ami_ct_u16le
comma
id|AMI_CT_U16LE
)paren
DECL|variable|transAmiga
r_static
id|TRANS
id|transAmiga
op_assign
(brace
id|ct_ulaw
suffix:colon
id|ami_ct_ulaw
comma
id|ct_alaw
suffix:colon
id|ami_ct_alaw
comma
id|ct_s8
suffix:colon
id|ami_ct_s8
comma
id|ct_u8
suffix:colon
id|ami_ct_u8
comma
id|ct_s16be
suffix:colon
id|ami_ct_s16be
comma
id|ct_u16be
suffix:colon
id|ami_ct_u16be
comma
id|ct_s16le
suffix:colon
id|ami_ct_s16le
comma
id|ct_u16le
suffix:colon
id|ami_ct_u16le
comma
)brace
suffix:semicolon
multiline_comment|/*** Low level stuff *********************************************************/
DECL|function|AmiOpen
r_static
r_void
id|AmiOpen
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|AmiRelease
r_static
r_void
id|AmiRelease
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|StopDMA
r_static
r_inline
r_void
id|StopDMA
c_func
(paren
r_void
)paren
(brace
id|custom.aud
(braket
l_int|0
)braket
dot
id|audvol
op_assign
id|custom.aud
(braket
l_int|1
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
id|custom.dmacon
op_assign
id|AMI_AUDIO_OFF
suffix:semicolon
id|enable_heartbeat
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|AmiAlloc
r_static
r_void
op_star
id|AmiAlloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|amiga_chip_alloc
c_func
(paren
(paren
r_int
)paren
id|size
comma
l_string|&quot;dmasound [Paula]&quot;
)paren
suffix:semicolon
)brace
DECL|function|AmiFree
r_static
r_void
id|AmiFree
c_func
(paren
r_void
op_star
id|obj
comma
r_int
r_int
id|size
)paren
(brace
id|amiga_chip_free
(paren
id|obj
)paren
suffix:semicolon
)brace
DECL|function|AmiIrqInit
r_static
r_int
id|__init
id|AmiIrqInit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* turn off DMA for audio channels */
id|StopDMA
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Register interrupt handler. */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_AUD0
comma
id|AmiInterrupt
comma
l_int|0
comma
l_string|&quot;DMA sound&quot;
comma
id|AmiInterrupt
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|AmiIrqCleanUp
r_static
r_void
id|AmiIrqCleanUp
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* turn off DMA for audio channels */
id|StopDMA
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release the interrupt */
id|free_irq
c_func
(paren
id|IRQ_AMIGA_AUD0
comma
id|AmiInterrupt
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
DECL|function|AmiSilence
r_static
r_void
id|AmiSilence
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* turn off DMA for audio channels */
id|StopDMA
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|AmiInit
r_static
r_void
id|AmiInit
c_func
(paren
r_void
)paren
(brace
r_int
id|period
comma
id|i
suffix:semicolon
id|AmiSilence
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.soft.speed
)paren
id|period
op_assign
id|amiga_colorclock
op_div
id|dmasound.soft.speed
op_minus
l_int|1
suffix:semicolon
r_else
id|period
op_assign
id|amiga_audio_min_period
suffix:semicolon
id|dmasound.hard
op_assign
id|dmasound.soft
suffix:semicolon
id|dmasound.trans_write
op_assign
op_amp
id|transAmiga
suffix:semicolon
r_if
c_cond
(paren
id|period
OL
id|amiga_audio_min_period
)paren
(brace
multiline_comment|/* we would need to squeeze the sound, but we won&squot;t do that */
id|period
op_assign
id|amiga_audio_min_period
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|period
OG
l_int|65535
)paren
(brace
id|period
op_assign
l_int|65535
suffix:semicolon
)brace
id|dmasound.hard.speed
op_assign
id|amiga_colorclock
op_div
(paren
id|period
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|custom.aud
(braket
id|i
)braket
dot
id|audper
op_assign
id|period
suffix:semicolon
id|amiga_audio_period
op_assign
id|period
suffix:semicolon
)brace
DECL|function|AmiSetFormat
r_static
r_int
id|AmiSetFormat
c_func
(paren
r_int
id|format
)paren
(brace
r_int
id|size
suffix:semicolon
multiline_comment|/* Amiga sound DMA supports 8bit and 16bit (pseudo 14 bit) modes */
r_switch
c_cond
(paren
id|format
)paren
(brace
r_case
id|AFMT_QUERY
suffix:colon
r_return
id|dmasound.soft.format
suffix:semicolon
r_case
id|AFMT_MU_LAW
suffix:colon
r_case
id|AFMT_A_LAW
suffix:colon
r_case
id|AFMT_U8
suffix:colon
r_case
id|AFMT_S8
suffix:colon
id|size
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFMT_S16_BE
suffix:colon
r_case
id|AFMT_U16_BE
suffix:colon
r_case
id|AFMT_S16_LE
suffix:colon
r_case
id|AFMT_U16_LE
suffix:colon
id|size
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* :-) */
id|size
op_assign
l_int|8
suffix:semicolon
id|format
op_assign
id|AFMT_S8
suffix:semicolon
)brace
id|dmasound.soft.format
op_assign
id|format
suffix:semicolon
id|dmasound.soft.size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.minDev
op_eq
id|SND_DEV_DSP
)paren
(brace
id|dmasound.dsp.format
op_assign
id|format
suffix:semicolon
id|dmasound.dsp.size
op_assign
id|dmasound.soft.size
suffix:semicolon
)brace
id|AmiInit
c_func
(paren
)paren
suffix:semicolon
r_return
id|format
suffix:semicolon
)brace
DECL|macro|VOLUME_VOXWARE_TO_AMI
mdefine_line|#define VOLUME_VOXWARE_TO_AMI(v) &bslash;&n;&t;(((v) &lt; 0) ? 0 : ((v) &gt; 100) ? 64 : ((v) * 64)/100)
DECL|macro|VOLUME_AMI_TO_VOXWARE
mdefine_line|#define VOLUME_AMI_TO_VOXWARE(v) ((v)*100/64)
DECL|function|AmiSetVolume
r_static
r_int
id|AmiSetVolume
c_func
(paren
r_int
id|volume
)paren
(brace
id|dmasound.volume_left
op_assign
id|VOLUME_VOXWARE_TO_AMI
c_func
(paren
id|volume
op_amp
l_int|0xff
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audvol
op_assign
id|dmasound.volume_left
suffix:semicolon
id|dmasound.volume_right
op_assign
id|VOLUME_VOXWARE_TO_AMI
c_func
(paren
(paren
id|volume
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audvol
op_assign
id|dmasound.volume_right
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.hard.size
op_eq
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|dmasound.volume_left
op_eq
l_int|64
op_logical_and
id|dmasound.volume_right
op_eq
l_int|64
)paren
(brace
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
id|VOLUME_AMI_TO_VOXWARE
c_func
(paren
id|dmasound.volume_left
)paren
op_or
(paren
id|VOLUME_AMI_TO_VOXWARE
c_func
(paren
id|dmasound.volume_right
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|AmiSetTreble
r_static
r_int
id|AmiSetTreble
c_func
(paren
r_int
id|treble
)paren
(brace
id|dmasound.treble
op_assign
id|treble
suffix:semicolon
r_if
c_cond
(paren
id|treble
OL
l_int|50
)paren
id|ciaa.pra
op_and_assign
op_complement
l_int|0x02
suffix:semicolon
r_else
id|ciaa.pra
op_or_assign
l_int|0x02
suffix:semicolon
r_return
id|treble
suffix:semicolon
)brace
DECL|macro|AMI_PLAY_LOADED
mdefine_line|#define AMI_PLAY_LOADED&t;&t;1
DECL|macro|AMI_PLAY_PLAYING
mdefine_line|#define AMI_PLAY_PLAYING&t;2
DECL|macro|AMI_PLAY_MASK
mdefine_line|#define AMI_PLAY_MASK&t;&t;3
DECL|function|AmiPlayNextFrame
r_static
r_void
id|AmiPlayNextFrame
c_func
(paren
r_int
id|index
)paren
(brace
id|u_char
op_star
id|start
comma
op_star
id|ch0
comma
op_star
id|ch1
comma
op_star
id|ch2
comma
op_star
id|ch3
suffix:semicolon
id|u_long
id|size
suffix:semicolon
multiline_comment|/* used by AmiPlay() if all doubts whether there really is something&n;&t; * to be played are already wiped out.&n;&t; */
id|start
op_assign
id|write_sq.buffers
(braket
id|write_sq.front
)braket
suffix:semicolon
id|size
op_assign
(paren
id|write_sq.count
op_eq
id|index
ques
c_cond
id|write_sq.rear_size
suffix:colon
id|write_sq.block_size
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.hard.stereo
)paren
(brace
id|ch0
op_assign
id|start
suffix:semicolon
id|ch1
op_assign
id|start
op_plus
id|write_sq_block_size_half
suffix:semicolon
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ch0
op_assign
id|start
suffix:semicolon
id|ch1
op_assign
id|start
suffix:semicolon
)brace
id|disable_heartbeat
c_func
(paren
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audvol
op_assign
id|dmasound.volume_left
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audvol
op_assign
id|dmasound.volume_right
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.hard.size
op_eq
l_int|8
)paren
(brace
id|custom.aud
(braket
l_int|0
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch0
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch1
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
id|custom.dmacon
op_assign
id|AMI_AUDIO_8
suffix:semicolon
)brace
r_else
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch0
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch1
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|1
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|dmasound.volume_left
op_eq
l_int|64
op_logical_and
id|dmasound.volume_right
op_eq
l_int|64
)paren
(brace
multiline_comment|/* We can play pseudo 14-bit only with the maximum volume */
id|ch3
op_assign
id|ch0
op_plus
id|write_sq_block_size_quarter
suffix:semicolon
id|ch2
op_assign
id|ch1
op_plus
id|write_sq_block_size_quarter
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we are being affected by the beeps */
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* restoring volume here helps a bit */
id|custom.aud
(braket
l_int|2
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch2
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audlc
op_assign
(paren
id|u_short
op_star
)paren
id|ZTWO_PADDR
c_func
(paren
id|ch3
)paren
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audlen
op_assign
id|size
suffix:semicolon
id|custom.dmacon
op_assign
id|AMI_AUDIO_14
suffix:semicolon
)brace
r_else
(brace
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|0
suffix:semicolon
id|custom.dmacon
op_assign
id|AMI_AUDIO_8
suffix:semicolon
)brace
)brace
id|write_sq.front
op_assign
(paren
id|write_sq.front
op_plus
l_int|1
)paren
op_mod
id|write_sq.max_count
suffix:semicolon
id|write_sq.active
op_or_assign
id|AMI_PLAY_LOADED
suffix:semicolon
)brace
DECL|function|AmiPlay
r_static
r_void
id|AmiPlay
c_func
(paren
r_void
)paren
(brace
r_int
id|minframes
op_assign
l_int|1
suffix:semicolon
id|custom.intena
op_assign
id|IF_AUD0
suffix:semicolon
r_if
c_cond
(paren
id|write_sq.active
op_amp
id|AMI_PLAY_LOADED
)paren
(brace
multiline_comment|/* There&squot;s already a frame loaded */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_AUD0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sq.active
op_amp
id|AMI_PLAY_PLAYING
)paren
multiline_comment|/* Increase threshold: frame 1 is already being played */
id|minframes
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|write_sq.count
OL
id|minframes
)paren
(brace
multiline_comment|/* Nothing to do */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_AUD0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sq.count
op_le
id|minframes
op_logical_and
id|write_sq.rear_size
OL
id|write_sq.block_size
op_logical_and
op_logical_neg
id|write_sq.syncing
)paren
(brace
multiline_comment|/* hmmm, the only existing frame is not&n;&t;&t; * yet filled and we&squot;re not syncing?&n;&t;&t; */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_AUD0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|AmiPlayNextFrame
c_func
(paren
id|minframes
)paren
suffix:semicolon
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_AUD0
suffix:semicolon
)brace
DECL|function|AmiInterrupt
r_static
r_void
id|AmiInterrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
id|minframes
op_assign
l_int|1
suffix:semicolon
id|custom.intena
op_assign
id|IF_AUD0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_sq.active
)paren
(brace
multiline_comment|/* Playing was interrupted and sq_reset() has already cleared&n;&t;&t; * the sq variables, so better don&squot;t do anything here.&n;&t;&t; */
id|WAKE_UP
c_func
(paren
id|write_sq.sync_queue
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sq.active
op_amp
id|AMI_PLAY_PLAYING
)paren
(brace
multiline_comment|/* We&squot;ve just finished a frame */
id|write_sq.count
op_decrement
suffix:semicolon
id|WAKE_UP
c_func
(paren
id|write_sq.action_queue
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write_sq.active
op_amp
id|AMI_PLAY_LOADED
)paren
multiline_comment|/* Increase threshold: frame 1 is already being played */
id|minframes
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Shift the flags */
id|write_sq.active
op_assign
(paren
id|write_sq.active
op_lshift
l_int|1
)paren
op_amp
id|AMI_PLAY_MASK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_sq.active
)paren
multiline_comment|/* No frame is playing, disable audio DMA */
id|StopDMA
c_func
(paren
)paren
suffix:semicolon
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_AUD0
suffix:semicolon
r_if
c_cond
(paren
id|write_sq.count
op_ge
id|minframes
)paren
multiline_comment|/* Try to play the next frame */
id|AmiPlay
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_sq.active
)paren
multiline_comment|/* Nothing to play anymore.&n;&t;&t;   Wake up a process waiting for audio output to drain. */
id|WAKE_UP
c_func
(paren
id|write_sq.sync_queue
)paren
suffix:semicolon
)brace
multiline_comment|/*** Mid level stuff *********************************************************/
multiline_comment|/*&n; * /dev/mixer abstraction&n; */
DECL|function|AmiMixerInit
r_static
r_void
id|__init
id|AmiMixerInit
c_func
(paren
r_void
)paren
(brace
id|dmasound.volume_left
op_assign
l_int|64
suffix:semicolon
id|dmasound.volume_right
op_assign
l_int|64
suffix:semicolon
id|custom.aud
(braket
l_int|0
)braket
dot
id|audvol
op_assign
id|dmasound.volume_left
suffix:semicolon
id|custom.aud
(braket
l_int|3
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* For pseudo 14bit */
id|custom.aud
(braket
l_int|1
)braket
dot
id|audvol
op_assign
id|dmasound.volume_right
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* For pseudo 14bit */
id|dmasound.treble
op_assign
l_int|50
suffix:semicolon
)brace
DECL|function|AmiMixerIoctl
r_static
r_int
id|AmiMixerIoctl
c_func
(paren
id|u_int
id|cmd
comma
id|u_long
id|arg
)paren
(brace
r_int
id|data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SOUND_MIXER_READ_DEVMASK
suffix:colon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_TREBLE
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_RECMASK
suffix:colon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_STEREODEVS
suffix:colon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|SOUND_MASK_VOLUME
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_VOLUME
suffix:colon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|VOLUME_AMI_TO_VOXWARE
c_func
(paren
id|dmasound.volume_left
)paren
op_or
id|VOLUME_AMI_TO_VOXWARE
c_func
(paren
id|dmasound.volume_right
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_VOLUME
suffix:colon
id|IOCTL_IN
c_func
(paren
id|arg
comma
id|data
)paren
suffix:semicolon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|dmasound_set_volume
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_TREBLE
suffix:colon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|dmasound.treble
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_TREBLE
suffix:colon
id|IOCTL_IN
c_func
(paren
id|arg
comma
id|data
)paren
suffix:semicolon
r_return
id|IOCTL_OUT
c_func
(paren
id|arg
comma
id|dmasound_set_treble
c_func
(paren
id|data
)paren
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|AmiWriteSqSetup
r_static
r_void
id|AmiWriteSqSetup
c_func
(paren
r_void
)paren
(brace
id|write_sq_block_size_half
op_assign
id|write_sq.block_size
op_rshift
l_int|1
suffix:semicolon
id|write_sq_block_size_quarter
op_assign
id|write_sq_block_size_half
op_rshift
l_int|1
suffix:semicolon
)brace
DECL|function|AmiStateInfo
r_static
r_int
id|AmiStateInfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;tsound.volume_left = %d [0...64]&bslash;n&quot;
comma
id|dmasound.volume_left
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;tsound.volume_right = %d [0...64]&bslash;n&quot;
comma
id|dmasound.volume_right
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*** Machine definitions *****************************************************/
DECL|variable|machAmiga
r_static
id|MACHINE
id|machAmiga
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Amiga&quot;
comma
id|name2
suffix:colon
l_string|&quot;AMIGA&quot;
comma
id|open
suffix:colon
id|AmiOpen
comma
id|release
suffix:colon
id|AmiRelease
comma
id|dma_alloc
suffix:colon
id|AmiAlloc
comma
id|dma_free
suffix:colon
id|AmiFree
comma
id|irqinit
suffix:colon
id|AmiIrqInit
comma
macro_line|#ifdef MODULE
id|irqcleanup
suffix:colon
id|AmiIrqCleanUp
comma
macro_line|#endif /* MODULE */
id|init
suffix:colon
id|AmiInit
comma
id|silence
suffix:colon
id|AmiSilence
comma
id|setFormat
suffix:colon
id|AmiSetFormat
comma
id|setVolume
suffix:colon
id|AmiSetVolume
comma
id|setTreble
suffix:colon
id|AmiSetTreble
comma
id|play
suffix:colon
id|AmiPlay
comma
id|mixer_init
suffix:colon
id|AmiMixerInit
comma
id|mixer_ioctl
suffix:colon
id|AmiMixerIoctl
comma
id|write_sq_setup
suffix:colon
id|AmiWriteSqSetup
comma
id|state_info
suffix:colon
id|AmiStateInfo
comma
id|min_dsp_speed
suffix:colon
l_int|8000
)brace
suffix:semicolon
multiline_comment|/*** Config &amp; Setup **********************************************************/
DECL|function|dmasound_paula_init
r_int
id|__init
id|dmasound_paula_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|AMI_AUDIO
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|0xa0
comma
l_int|0x40
comma
l_string|&quot;dmasound [Paula]&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|dmasound.mach
op_assign
id|machAmiga
suffix:semicolon
id|err
op_assign
id|dmasound_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|release_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|0xa0
comma
l_int|0x40
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|dmasound_paula_cleanup
r_static
r_void
id|__exit
id|dmasound_paula_cleanup
c_func
(paren
r_void
)paren
(brace
id|dmasound_deinit
c_func
(paren
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|0xa0
comma
l_int|0x40
)paren
suffix:semicolon
)brace
DECL|variable|dmasound_paula_init
id|module_init
c_func
(paren
id|dmasound_paula_init
)paren
suffix:semicolon
DECL|variable|dmasound_paula_cleanup
id|module_exit
c_func
(paren
id|dmasound_paula_cleanup
)paren
suffix:semicolon
eof
