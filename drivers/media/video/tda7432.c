multiline_comment|/*&n; * For the STS-Thompson TDA7432 audio processor chip&n; * &n; * Handles audio functions: volume, balance, tone, loudness&n; * This driver will not complain if used with any &n; * other i2c device with the same address.&n; *&n; * Muting and tone control by Jonathan Isom &lt;jisom@ematic.com&gt;&n; *&n; * Copyright (c) 2000 Eric Sandeen &lt;eric_sandeen@bigfoot.com&gt;&n; * This code is placed under the terms of the GNU General Public License&n; * Based on tda9855.c by Steve VanDeBogart (vandebo@uclink.berkeley.edu)&n; * Which was based on tda8425.c by Greg Alexander (c) 1998&n; *&n; * OPTIONS:&n; * debug    - set to 1 if you&squot;d like to see debug messages&n; *            set to 2 if you&squot;d like to be inundated with debug messages&n; *&n; * loudness - set between 0 and 15 for varying degrees of loudness effect&n; *&n; * maxvol   - set maximium volume to +20db (1), default is 0db(0)&n; *&n; *&n; *  Revision: 0.7 - maxvol module parm to set maximium volume 0db or +20db&n; *  &t;&t;&t;&t;store if muted so we can return it&n; *  &t;&t;&t;&t;change balance only if flaged to&n; *  Revision: 0.6 - added tone controls&n; *  Revision: 0.5 - Fixed odd balance problem&n; *  Revision: 0.4 - added muting&n; *  Revision: 0.3 - Fixed silly reversed volume controls.  :)&n; *  Revision: 0.2 - Cleaned up #defines&n; *&t;&t;&t;fixed volume control&n; *          Added I2C_DRIVERID_TDA7432&n; *&t;&t;&t;added loudness insmod control&n; *  Revision: 0.1 - initial version&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;bttv.h&quot;
macro_line|#include &lt;media/audiochip.h&gt;
macro_line|#include &lt;media/id.h&gt;
macro_line|#ifndef VIDEO_AUDIO_BALANCE
DECL|macro|VIDEO_AUDIO_BALANCE
macro_line|# define VIDEO_AUDIO_BALANCE 32
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Sandeen &lt;eric_sandeen@bigfoot.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;bttv driver for the tda7432 audio processor chip&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|loudness
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|maxvol
comma
l_string|&quot;Set maximium volume to +20db (0), default is 0db(1)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|maxvol
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|maxvol
r_static
r_int
id|maxvol
op_assign
l_int|0
suffix:semicolon
DECL|variable|loudness
r_static
r_int
id|loudness
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable loudness by default */
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* insmod parameter */
multiline_comment|/* Address to scan (I2C address of this chip) */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|I2C_TDA7432
op_rshift
l_int|1
comma
id|I2C_CLIENT_END
comma
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
id|I2C_CLIENT_INSMOD
suffix:semicolon
multiline_comment|/* Structure of address and subaddresses for the tda7432 */
DECL|struct|tda7432
r_struct
id|tda7432
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|input
r_int
id|input
suffix:semicolon
DECL|member|volume
r_int
id|volume
suffix:semicolon
DECL|member|muted
r_int
id|muted
suffix:semicolon
DECL|member|bass
DECL|member|treble
r_int
id|bass
comma
id|treble
suffix:semicolon
DECL|member|lf
DECL|member|lr
DECL|member|rf
DECL|member|rr
r_int
id|lf
comma
id|lr
comma
id|rf
comma
id|rr
suffix:semicolon
DECL|member|loud
r_int
id|loud
suffix:semicolon
DECL|member|c
r_struct
id|i2c_client
id|c
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk  if (debug) printk
DECL|macro|d2printk
mdefine_line|#define d2printk if (debug &gt; 1) printk
multiline_comment|/* The TDA7432 is made by STS-Thompson&n; * http://www.st.com&n; * http://us.st.com/stonline/books/pdf/docs/4056.pdf&n; *&n; * TDA7432: I2C-bus controlled basic audio processor&n; *&n; * The TDA7432 controls basic audio functions like volume, balance,&n; * and tone control (including loudness).  It also has four channel&n; * output (for front and rear).  Since most vidcap cards probably&n; * don&squot;t have 4 channel output, this driver will set front &amp; rear&n; * together (no independent control).&n; */
multiline_comment|/* Subaddresses for TDA7432 */
DECL|macro|TDA7432_IN
mdefine_line|#define TDA7432_IN&t;0x00 /* Input select                 */
DECL|macro|TDA7432_VL
mdefine_line|#define TDA7432_VL&t;0x01 /* Volume                       */
DECL|macro|TDA7432_TN
mdefine_line|#define TDA7432_TN&t;0x02 /* Bass, Treble (Tone)          */
DECL|macro|TDA7432_LF
mdefine_line|#define TDA7432_LF&t;0x03 /* Attenuation LF (Left Front)  */
DECL|macro|TDA7432_LR
mdefine_line|#define TDA7432_LR&t;0x04 /* Attenuation LR (Left Rear)   */
DECL|macro|TDA7432_RF
mdefine_line|#define TDA7432_RF&t;0x05 /* Attenuation RF (Right Front) */
DECL|macro|TDA7432_RR
mdefine_line|#define TDA7432_RR&t;0x06 /* Attenuation RR (Right Rear)  */
DECL|macro|TDA7432_LD
mdefine_line|#define TDA7432_LD&t;0x07 /* Loudness                     */
multiline_comment|/* Masks for bits in TDA7432 subaddresses */
multiline_comment|/* Many of these not used - just for documentation */
multiline_comment|/* Subaddress 0x00 - Input selection and bass control */
multiline_comment|/* Bits 0,1,2 control input:&n; * 0x00 - Stereo input&n; * 0x02 - Mono input&n; * 0x03 - Mute  (Using Attenuators Plays better with modules)&n; * Mono probably isn&squot;t used - I&squot;m guessing only the stereo&n; * input is connected on most cards, so we&squot;ll set it to stereo.&n; * &n; * Bit 3 controls bass cut: 0/1 is non-symmetric/symmetric bass cut&n; * Bit 4 controls bass range: 0/1 is extended/standard bass range&n; * &n; * Highest 3 bits not used&n; */
DECL|macro|TDA7432_STEREO_IN
mdefine_line|#define TDA7432_STEREO_IN&t;0
DECL|macro|TDA7432_MONO_IN
mdefine_line|#define TDA7432_MONO_IN&t;&t;2&t;/* Probably won&squot;t be used */
DECL|macro|TDA7432_BASS_SYM
mdefine_line|#define TDA7432_BASS_SYM&t;1 &lt;&lt; 3
DECL|macro|TDA7432_BASS_NORM
mdefine_line|#define TDA7432_BASS_NORM&t;1 &lt;&lt; 4
multiline_comment|/* Subaddress 0x01 - Volume */
multiline_comment|/* Lower 7 bits control volume from -79dB to +32dB in 1dB steps&n; * Recommended maximum is +20 dB&n; *&n; * +32dB: 0x00&n; * +20dB: 0x0c&n; *   0dB: 0x20&n; * -79dB: 0x6f&n; *&n; * MSB (bit 7) controls loudness: 1/0 is loudness on/off&n; */
DECL|macro|TDA7432_VOL_0DB
mdefine_line|#define&t;TDA7432_VOL_0DB&t;&t;0x20
DECL|macro|TDA7432_LD_ON
mdefine_line|#define TDA7432_LD_ON&t;&t;1 &lt;&lt; 7
multiline_comment|/* Subaddress 0x02 - Tone control */
multiline_comment|/* Bits 0,1,2 control absolute treble gain from 0dB to 14dB&n; * 0x0 is 14dB, 0x7 is 0dB&n; *&n; * Bit 3 controls treble attenuation/gain (sign)&n; * 1 = gain (+)&n; * 0 = attenuation (-)&n; *&n; * Bits 4,5,6 control absolute bass gain from 0dB to 14dB&n; * (This is only true for normal base range, set in 0x00)&n; * 0x0 &lt;&lt; 4 is 14dB, 0x7 is 0dB&n; * &n; * Bit 7 controls bass attenuation/gain (sign)&n; * 1 &lt;&lt; 7 = gain (+)&n; * 0 &lt;&lt; 7 = attenuation (-) &n; *&n; * Example:&n; * 1 1 0 1 0 1 0 1 is +4dB bass, -4dB treble&n; */
DECL|macro|TDA7432_TREBLE_0DB
mdefine_line|#define TDA7432_TREBLE_0DB&t;&t;0xf 
DECL|macro|TDA7432_TREBLE
mdefine_line|#define TDA7432_TREBLE&t;&t;&t;7
DECL|macro|TDA7432_TREBLE_GAIN
mdefine_line|#define TDA7432_TREBLE_GAIN&t;&t;1 &lt;&lt; 3
DECL|macro|TDA7432_BASS_0DB
mdefine_line|#define TDA7432_BASS_0DB&t;&t;0xf
DECL|macro|TDA7432_BASS
mdefine_line|#define TDA7432_BASS&t;&t;&t;7 &lt;&lt; 4
DECL|macro|TDA7432_BASS_GAIN
mdefine_line|#define TDA7432_BASS_GAIN&t;&t;1 &lt;&lt; 7
multiline_comment|/* Subaddress 0x03 - Left  Front attenuation */
multiline_comment|/* Subaddress 0x04 - Left  Rear  attenuation */
multiline_comment|/* Subaddress 0x05 - Right Front attenuation */
multiline_comment|/* Subaddress 0x06 - Right Rear  attenuation */
multiline_comment|/* Bits 0,1,2,3,4 control attenuation from 0dB to -37.5dB&n; * in 1.5dB steps.&n; *&n; * 0x00 is     0dB&n; * 0x1f is -37.5dB&n; *&n; * Bit 5 mutes that channel when set (1 = mute, 0 = unmute)&n; * We&squot;ll use the mute on the input, though (above) &n; * Bits 6,7 unused&n; */
DECL|macro|TDA7432_ATTEN_0DB
mdefine_line|#define TDA7432_ATTEN_0DB&t;0x00
DECL|macro|TDA7432_MUTE
mdefine_line|#define TDA7432_MUTE        0x1 &lt;&lt; 5
multiline_comment|/* Subaddress 0x07 - Loudness Control */
multiline_comment|/* Bits 0,1,2,3 control loudness from 0dB to -15dB in 1dB steps&n; * when bit 4 is NOT set&n; *&n; * 0x0 is   0dB&n; * 0xf is -15dB&n; *&n; * If bit 4 is set, then there is a flat attenuation according to&n; * the lower 4 bits, as above.&n; *&n; * Bits 5,6,7 unused&n; */
multiline_comment|/* Begin code */
DECL|function|tda7432_write
r_static
r_int
id|tda7432_write
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|subaddr
comma
r_int
id|val
)paren
(brace
r_int
r_char
id|buffer
(braket
l_int|2
)braket
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_write&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tda7432: Writing %d 0x%x&bslash;n&quot;
comma
id|subaddr
comma
id|val
)paren
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
id|subaddr
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_ne
id|i2c_master_send
c_func
(paren
id|client
comma
id|buffer
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda7432: I/O error, trying (write %d 0x%x)&bslash;n&quot;
comma
id|subaddr
comma
id|val
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* I don&squot;t think we ever actually _read_ the chip... */
macro_line|#if 0
r_static
r_int
id|tda7432_read
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
r_char
id|buffer
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_read&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
id|i2c_master_recv
c_func
(paren
id|client
comma
op_amp
id|buffer
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda7432: I/O error, trying (read)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;tda7432: Read 0x%02x&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
macro_line|#endif
DECL|function|tda7432_set
r_static
r_int
id|tda7432_set
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda7432
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_set&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda7432: 7432_set(0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x)&bslash;n&quot;
comma
id|t-&gt;input
comma
id|t-&gt;volume
comma
id|t-&gt;bass
comma
id|t-&gt;treble
comma
id|t-&gt;lf
comma
id|t-&gt;lr
comma
id|t-&gt;rf
comma
id|t-&gt;rr
comma
id|t-&gt;loud
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|TDA7432_IN
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|t-&gt;input
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|t-&gt;volume
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|t-&gt;bass
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|t-&gt;treble
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
id|t-&gt;lf
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_assign
id|t-&gt;lr
suffix:semicolon
id|buf
(braket
l_int|7
)braket
op_assign
id|t-&gt;rf
suffix:semicolon
id|buf
(braket
l_int|8
)braket
op_assign
id|t-&gt;rr
suffix:semicolon
id|buf
(braket
l_int|9
)braket
op_assign
id|t-&gt;loud
suffix:semicolon
r_if
c_cond
(paren
l_int|10
op_ne
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|10
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda7432: I/O error, trying tda7432_set&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_tda7432_init
r_static
r_void
id|do_tda7432_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda7432
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_init&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;input
op_assign
id|TDA7432_STEREO_IN
op_or
multiline_comment|/* Main (stereo) input   */
id|TDA7432_BASS_SYM
op_or
multiline_comment|/* Symmetric bass cut    */
id|TDA7432_BASS_NORM
suffix:semicolon
multiline_comment|/* Normal bass range     */
id|t-&gt;volume
op_assign
l_int|0x3b
suffix:semicolon
multiline_comment|/* -27dB Volume            */
r_if
c_cond
(paren
id|loudness
)paren
multiline_comment|/* Turn loudness on?     */
id|t-&gt;volume
op_or_assign
id|TDA7432_LD_ON
suffix:semicolon
id|t-&gt;muted
op_assign
id|VIDEO_AUDIO_MUTE
suffix:semicolon
id|t-&gt;treble
op_assign
id|TDA7432_TREBLE_0DB
suffix:semicolon
multiline_comment|/* 0dB Treble            */
id|t-&gt;bass
op_assign
id|TDA7432_BASS_0DB
suffix:semicolon
multiline_comment|/* 0dB Bass              */
id|t-&gt;lf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
multiline_comment|/* 0dB attenuation       */
id|t-&gt;lr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
multiline_comment|/* 0dB attenuation       */
id|t-&gt;rf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
multiline_comment|/* 0dB attenuation       */
id|t-&gt;rr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
multiline_comment|/* 0dB attenuation       */
id|t-&gt;loud
op_assign
id|loudness
suffix:semicolon
multiline_comment|/* insmod parameter      */
id|tda7432_set
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
multiline_comment|/* *********************** *&n; * i2c interface functions *&n; * *********************** */
DECL|function|tda7432_attach
r_static
r_int
id|tda7432_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|addr
comma
r_int
id|kind
)paren
(brace
r_struct
id|tda7432
op_star
id|t
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_attach&bslash;n&quot;
)paren
suffix:semicolon
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|t
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
op_star
id|t
)paren
suffix:semicolon
id|client
op_assign
op_amp
id|t-&gt;c
suffix:semicolon
id|memcpy
c_func
(paren
id|client
comma
op_amp
id|client_template
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|client-&gt;addr
op_assign
id|addr
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|t
)paren
suffix:semicolon
id|do_tda7432_init
c_func
(paren
id|client
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda7432: init&bslash;n&quot;
)paren
suffix:semicolon
id|i2c_attach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda7432_probe
r_static
r_int
id|tda7432_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef I2C_CLASS_TV_ANALOG
r_if
c_cond
(paren
id|adap
op_member_access_from_pointer
r_class
op_amp
id|I2C_CLASS_TV_ANALOG
)paren
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|tda7432_attach
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|adap-&gt;id
op_eq
(paren
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
)paren
)paren
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|tda7432_attach
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda7432_detach
r_static
r_int
id|tda7432_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda7432
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|do_tda7432_init
c_func
(paren
id|client
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda7432_command
r_static
r_int
id|tda7432_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|tda7432
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|d2printk
c_func
(paren
l_string|&quot;tda7432: In tda7432_command&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* --- v4l ioctls --- */
multiline_comment|/* take care: bttv does userspace copying, we&squot;ll get a&n;&t;   kernel pointer here... */
multiline_comment|/* Query card - scale from TDA7432 settings to V4L settings */
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|va
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tda7432: VIDIOCGAUDIO&bslash;n&quot;
)paren
suffix:semicolon
id|va-&gt;flags
op_or_assign
id|VIDEO_AUDIO_VOLUME
op_or
id|VIDEO_AUDIO_BASS
op_or
id|VIDEO_AUDIO_TREBLE
op_or
id|VIDEO_AUDIO_MUTABLE
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;muted
)paren
id|va-&gt;flags
op_or_assign
id|VIDEO_AUDIO_MUTE
suffix:semicolon
id|va-&gt;mode
op_or_assign
id|VIDEO_SOUND_STEREO
suffix:semicolon
multiline_comment|/* Master volume control&n;&t;&t; * V4L volume is min 0, max 65535&n;&t;&t; * TDA7432 Volume: &n;&t;&t; * Min (-79dB) is 0x6f&n;&t;&t; * Max (+20dB) is 0x07 (630)&n;&t;&t; * Max (0dB) is 0x20 (829)&n;&t;&t; * (Mask out bit 7 of vol - it&squot;s for the loudness setting)&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|maxvol
)paren
(brace
multiline_comment|/* max +20db */
id|va-&gt;volume
op_assign
(paren
l_int|0x6f
op_minus
(paren
id|t-&gt;volume
op_amp
l_int|0x7F
)paren
)paren
op_star
l_int|630
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* max 0db   */
id|va-&gt;volume
op_assign
(paren
l_int|0x6f
op_minus
(paren
id|t-&gt;volume
op_amp
l_int|0x7F
)paren
)paren
op_star
l_int|829
suffix:semicolon
)brace
multiline_comment|/* Balance depends on L,R attenuation&n;&t;&t; * V4L balance is 0 to 65535, middle is 32768&n;&t;&t; * TDA7432 attenuation: min (0dB) is 0, max (-37.5dB) is 0x1f&n;&t;&t; * to scale up to V4L numbers, mult by 1057&n;&t;&t; * attenuation exists for lf, lr, rf, rr&n;&t;&t; * we use only lf and rf (front channels)&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|t-&gt;lf
)paren
OL
(paren
id|t-&gt;rf
)paren
)paren
multiline_comment|/* right is attenuated, balance shifted left */
id|va-&gt;balance
op_assign
(paren
l_int|32768
op_minus
l_int|1057
op_star
(paren
id|t-&gt;rf
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* left is attenuated, balance shifted right */
id|va-&gt;balance
op_assign
(paren
l_int|32768
op_plus
l_int|1057
op_star
(paren
id|t-&gt;lf
)paren
)paren
suffix:semicolon
multiline_comment|/* Bass/treble 4 bits each */
id|va-&gt;bass
op_assign
id|t-&gt;bass
suffix:semicolon
r_if
c_cond
(paren
id|va-&gt;bass
op_ge
l_int|0x8
)paren
(brace
id|va-&gt;bass
op_assign
op_complement
(paren
id|va-&gt;bass
op_minus
l_int|0x8
)paren
op_amp
l_int|0xf
suffix:semicolon
)brace
id|va-&gt;bass
op_assign
(paren
id|va-&gt;bass
op_lshift
l_int|12
)paren
op_plus
(paren
id|va-&gt;bass
op_lshift
l_int|8
)paren
op_plus
(paren
id|va-&gt;bass
op_lshift
l_int|4
)paren
op_plus
(paren
id|va-&gt;bass
)paren
suffix:semicolon
id|va-&gt;treble
op_assign
id|t-&gt;treble
suffix:semicolon
r_if
c_cond
(paren
id|va-&gt;treble
op_ge
l_int|0x8
)paren
(brace
id|va-&gt;treble
op_assign
op_complement
(paren
id|va-&gt;treble
op_minus
l_int|0x8
)paren
op_amp
l_int|0xf
suffix:semicolon
)brace
id|va-&gt;treble
op_assign
(paren
id|va-&gt;treble
op_lshift
l_int|12
)paren
op_plus
(paren
id|va-&gt;treble
op_lshift
l_int|8
)paren
op_plus
(paren
id|va-&gt;treble
op_lshift
l_int|4
)paren
op_plus
(paren
id|va-&gt;treble
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* VIDIOCGAUDIO case */
)brace
multiline_comment|/* Set card - scale from V4L settings to TDA7432 settings */
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|va
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tda7432: VIDEOCSAUDIO&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|va-&gt;flags
op_amp
id|VIDEO_AUDIO_VOLUME
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|maxvol
)paren
(brace
multiline_comment|/* max +20db */
id|t-&gt;volume
op_assign
l_int|0x6f
op_minus
(paren
(paren
id|va-&gt;volume
)paren
op_div
l_int|630
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* max 0db   */
id|t-&gt;volume
op_assign
l_int|0x6f
op_minus
(paren
(paren
id|va-&gt;volume
)paren
op_div
l_int|829
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loudness
)paren
multiline_comment|/* Turn on the loudness bit */
id|t-&gt;volume
op_or_assign
id|TDA7432_LD_ON
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_VL
comma
id|t-&gt;volume
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|va-&gt;flags
op_amp
id|VIDEO_AUDIO_BASS
)paren
(brace
id|t-&gt;bass
op_assign
id|va-&gt;bass
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;bass
op_ge
l_int|0x8
)paren
(brace
id|t-&gt;bass
op_assign
(paren
op_complement
id|t-&gt;bass
op_amp
l_int|0xf
)paren
op_plus
l_int|0x8
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|va-&gt;flags
op_amp
id|VIDEO_AUDIO_TREBLE
)paren
(brace
id|t-&gt;treble
op_assign
id|va-&gt;treble
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;treble
op_ge
l_int|0x8
)paren
(brace
id|t-&gt;treble
op_assign
(paren
op_complement
id|t-&gt;treble
op_amp
l_int|0xf
)paren
op_plus
l_int|0x8
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|va-&gt;flags
op_amp
(paren
id|VIDEO_AUDIO_TREBLE
op_or
id|VIDEO_AUDIO_BASS
)paren
)paren
(brace
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_TN
comma
l_int|0x10
op_or
(paren
id|t-&gt;bass
op_lshift
l_int|4
)paren
op_or
id|t-&gt;treble
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|va-&gt;flags
op_amp
id|VIDEO_AUDIO_BALANCE
)paren
(brace
r_if
c_cond
(paren
id|va-&gt;balance
OL
l_int|32768
)paren
(brace
multiline_comment|/* shifted to left, attenuate right */
id|t-&gt;rr
op_assign
(paren
l_int|32768
op_minus
id|va-&gt;balance
)paren
op_div
l_int|1057
suffix:semicolon
id|t-&gt;rf
op_assign
id|t-&gt;rr
suffix:semicolon
id|t-&gt;lr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
id|t-&gt;lf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|va-&gt;balance
OG
l_int|32769
)paren
(brace
multiline_comment|/* shifted to right, attenuate left */
id|t-&gt;lf
op_assign
(paren
id|va-&gt;balance
op_minus
l_int|32768
)paren
op_div
l_int|1057
suffix:semicolon
id|t-&gt;lr
op_assign
id|t-&gt;lf
suffix:semicolon
id|t-&gt;rr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
id|t-&gt;rf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* centered */
id|t-&gt;rr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
id|t-&gt;rf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
id|t-&gt;lf
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
id|t-&gt;lr
op_assign
id|TDA7432_ATTEN_0DB
suffix:semicolon
)brace
)brace
id|t-&gt;muted
op_assign
(paren
id|va-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;muted
)paren
(brace
multiline_comment|/* Mute &amp; update balance*/
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_LF
comma
id|t-&gt;lf
op_or
id|TDA7432_MUTE
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_LR
comma
id|t-&gt;lr
op_or
id|TDA7432_MUTE
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_RF
comma
id|t-&gt;rf
op_or
id|TDA7432_MUTE
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_RR
comma
id|t-&gt;rr
op_or
id|TDA7432_MUTE
)paren
suffix:semicolon
)brace
r_else
(brace
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_LF
comma
id|t-&gt;lf
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_LR
comma
id|t-&gt;lr
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_RF
comma
id|t-&gt;rf
)paren
suffix:semicolon
id|tda7432_write
c_func
(paren
id|client
comma
id|TDA7432_RR
comma
id|t-&gt;rr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* end of VIDEOCSAUDIO case */
r_default
suffix:colon
multiline_comment|/* Not VIDEOCGAUDIO or VIDEOCSAUDIO */
multiline_comment|/* nothing */
id|d2printk
c_func
(paren
l_string|&quot;tda7432: Default&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end of (cmd) switch */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;i2c tda7432 driver&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_TDA7432
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|tda7432_probe
comma
dot
id|detach_client
op_assign
id|tda7432_detach
comma
dot
id|command
op_assign
id|tda7432_command
comma
)brace
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
op_assign
(brace
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;tda7432&quot;
)paren
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|driver
op_assign
op_amp
id|driver
comma
)brace
suffix:semicolon
DECL|function|tda7432_init
r_static
r_int
id|__init
id|tda7432_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|loudness
OL
l_int|0
)paren
op_logical_or
(paren
id|loudness
OG
l_int|15
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tda7432: loudness parameter must be between 0 and 15&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|tda7432_fini
r_static
r_void
id|__exit
id|tda7432_fini
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|tda7432_init
id|module_init
c_func
(paren
id|tda7432_init
)paren
suffix:semicolon
DECL|variable|tda7432_fini
id|module_exit
c_func
(paren
id|tda7432_fini
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
