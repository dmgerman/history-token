multiline_comment|/*&n; * linux/arch/m68k/amiga/amisound.c&n; *&n; * amiga sound driver for Linux/m68k&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
DECL|variable|snd_data
r_static
r_int
r_int
op_star
id|snd_data
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sine_data
r_static
r_const
r_int
r_char
id|sine_data
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|39
comma
l_int|75
comma
l_int|103
comma
l_int|121
comma
l_int|127
comma
l_int|121
comma
l_int|103
comma
l_int|75
comma
l_int|39
comma
l_int|0
comma
op_minus
l_int|39
comma
op_minus
l_int|75
comma
op_minus
l_int|103
comma
op_minus
l_int|121
comma
op_minus
l_int|127
comma
op_minus
l_int|121
comma
op_minus
l_int|103
comma
op_minus
l_int|75
comma
op_minus
l_int|39
)brace
suffix:semicolon
DECL|macro|DATA_SIZE
mdefine_line|#define DATA_SIZE&t;(sizeof(sine_data)/sizeof(sine_data[0]))
multiline_comment|/*&n;     * The minimum period for audio may be modified by the frame buffer&n;     * device since it depends on htotal (for OCS/ECS/AGA)&n;     */
DECL|variable|amiga_audio_min_period
r_volatile
r_int
r_int
id|amiga_audio_min_period
op_assign
l_int|124
suffix:semicolon
multiline_comment|/* Default for pre-OCS */
DECL|macro|MAX_PERIOD
mdefine_line|#define MAX_PERIOD&t;(65535)
multiline_comment|/*&n;     *&t;Current period (set by dmasound.c)&n;     */
DECL|variable|amiga_audio_period
r_int
r_int
id|amiga_audio_period
op_assign
id|MAX_PERIOD
suffix:semicolon
DECL|variable|clock_constant
r_static
r_int
r_int
id|clock_constant
suffix:semicolon
DECL|function|amiga_init_sound
r_void
id|__init
id|amiga_init_sound
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|resource
id|beep_res
op_assign
(brace
l_string|&quot;Beep&quot;
)brace
suffix:semicolon
id|snd_data
op_assign
id|amiga_chip_alloc_res
c_func
(paren
r_sizeof
(paren
id|sine_data
)paren
comma
op_amp
id|beep_res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_data
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;amiga init_sound: failed to allocate chipmem&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
(paren
id|snd_data
comma
id|sine_data
comma
r_sizeof
(paren
id|sine_data
)paren
)paren
suffix:semicolon
multiline_comment|/* setup divisor */
id|clock_constant
op_assign
(paren
id|amiga_colorclock
op_plus
id|DATA_SIZE
op_div
l_int|2
)paren
op_div
id|DATA_SIZE
suffix:semicolon
multiline_comment|/* without amifb, turn video off and enable high quality sound */
macro_line|#ifndef CONFIG_FB_AMIGA
id|amifb_video_off
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_void
id|nosound
c_func
(paren
r_int
r_int
id|ignored
)paren
suffix:semicolon
DECL|variable|sound_timer
r_static
r_struct
id|timer_list
id|sound_timer
op_assign
(brace
id|function
suffix:colon
id|nosound
)brace
suffix:semicolon
DECL|function|amiga_mksound
r_void
id|amiga_mksound
c_func
(paren
r_int
r_int
id|hz
comma
r_int
r_int
id|ticks
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_data
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|sound_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hz
OG
l_int|20
op_logical_and
id|hz
OL
l_int|32767
)paren
(brace
r_int
r_int
id|period
op_assign
(paren
id|clock_constant
op_div
id|hz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|period
OL
id|amiga_audio_min_period
)paren
id|period
op_assign
id|amiga_audio_min_period
suffix:semicolon
r_if
c_cond
(paren
id|period
OG
id|MAX_PERIOD
)paren
id|period
op_assign
id|MAX_PERIOD
suffix:semicolon
multiline_comment|/* setup pointer to data, period, length and volume */
id|custom.aud
(braket
l_int|2
)braket
dot
id|audlc
op_assign
id|snd_data
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audlen
op_assign
r_sizeof
(paren
id|sine_data
)paren
op_div
l_int|2
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audper
op_assign
(paren
r_int
r_int
)paren
id|period
suffix:semicolon
id|custom.aud
(braket
l_int|2
)braket
dot
id|audvol
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* 50% of maxvol */
r_if
c_cond
(paren
id|ticks
)paren
(brace
id|sound_timer.expires
op_assign
id|jiffies
op_plus
id|ticks
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|sound_timer
)paren
suffix:semicolon
)brace
multiline_comment|/* turn on DMA for audio channel 2 */
id|custom.dmacon
op_assign
id|DMAF_SETCLR
op_or
id|DMAF_AUD2
suffix:semicolon
)brace
r_else
id|nosound
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|nosound
r_static
r_void
id|nosound
c_func
(paren
r_int
r_int
id|ignored
)paren
(brace
multiline_comment|/* turn off DMA for audio channel 2 */
id|custom.dmacon
op_assign
id|DMAF_AUD2
suffix:semicolon
multiline_comment|/* restore period to previous value after beeping */
id|custom.aud
(braket
l_int|2
)braket
dot
id|audper
op_assign
id|amiga_audio_period
suffix:semicolon
)brace
eof
