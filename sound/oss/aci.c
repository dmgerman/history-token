multiline_comment|/*&n; * Audio Command Interface (ACI) driver (sound/aci.c)&n; *&n; * ACI is a protocol used to communicate with the microcontroller on&n; * some sound cards produced by miro, e.g. the miroSOUND PCM12 and&n; * PCM20. The ACI has been developed for miro by Norberto Pellicci&n; * &lt;pellicci@home.com&gt;. Special thanks to both him and miro for&n; * providing the ACI specification.&n; *&n; * The main function of the ACI is to control the mixer and to get a&n; * product identification. On the PCM20, ACI also controls the radio&n; * tuner on this card, this is supported in the Video for Linux &n; * miropcm20 driver.&n; * -&n; * This is a fullfeatured implementation. Unsupported features&n; * are bugs... (:&n; *&n; * It is not longer necessary to load the mad16 module first. The&n; * user is currently responsible to set the mad16 mixer correctly.&n; *&n; * To toggle the solo mode for full duplex operation just use the OSS&n; * record switch for the pcm (&squot;wave&squot;) controller.           Robert&n; * -&n; *&n; * Revision history:&n; *&n; *   1995-11-10  Markus Kuhn &lt;mskuhn@cip.informatik.uni-erlangen.de&gt;&n; *        First version written.&n; *   1995-12-31  Markus Kuhn&n; *        Second revision, general code cleanup.&n; *   1996-05-16&t; Hannu Savolainen&n; *&t;  Integrated with other parts of the driver.&n; *   1996-05-28  Markus Kuhn&n; *        Initialize CS4231A mixer, make ACI first mixer,&n; *        use new private mixer API for solo mode.&n; *   1998-08-18  Ruurd Reitsma &lt;R.A.Reitsma@wbmt.tudelft.nl&gt;&n; *&t;  Small modification to export ACI functions and &n; *&t;  complete modularisation.&n; *   2000-06-20  Robert Siemer &lt;Robert.Siemer@gmx.de&gt;&n; *        Don&squot;t initialize the CS4231A mixer anymore, so the code is&n; *        working again, and other small changes to fit in todays&n; *        kernels.&n; *   2000-08-26  Robert Siemer&n; *        Clean up and rewrite for 2.4.x. Maybe it&squot;s SMP safe now... (:&n; *        ioctl bugfix, and integration of solo-mode into OSS-API,&n; *        added (OSS-limited) equalizer support, return value bugfix,&n; *        changed param aci_reset to reset, new params: ide, wss.&n; *   2001-04-20  Robert Siemer&n; *        even more cleanups...&n; *   2001-10-08  Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *   &t;  Get rid of check_region, .bss optimizations, use set_current_state&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;sound_config.h&quot;
DECL|variable|aci_port
r_int
id|aci_port
suffix:semicolon
multiline_comment|/* as determined by bit 4 in the OPTi 929 MC4 register */
DECL|variable|aci_idcode
r_static
r_int
id|aci_idcode
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* manufacturer and product ID */
DECL|variable|aci_version
r_int
id|aci_version
suffix:semicolon
multiline_comment|/* ACI firmware version&t;*/
DECL|variable|aci_port
id|EXPORT_SYMBOL
c_func
(paren
id|aci_port
)paren
suffix:semicolon
DECL|variable|aci_version
id|EXPORT_SYMBOL
c_func
(paren
id|aci_version
)paren
suffix:semicolon
macro_line|#include &quot;aci.h&quot;
DECL|variable|aci_solo
r_static
r_int
id|aci_solo
suffix:semicolon
multiline_comment|/* status bit of the card that can&squot;t be&t;&t;*&n;&t;&t;&t; * checked with ACI versions prior to 0xb0&t;*/
DECL|variable|aci_amp
r_static
r_int
id|aci_amp
suffix:semicolon
multiline_comment|/* status bit for power-amp/line-out level&n;&t;&t;&t;   but I have no docs about what is what... */
DECL|variable|aci_micpreamp
r_static
r_int
id|aci_micpreamp
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* microphone preamp-level that can&squot;t be    *&n;&t;&t;&t; * checked with ACI versions prior to 0xb0&t;*/
DECL|variable|mixer_device
r_static
r_int
id|mixer_device
suffix:semicolon
DECL|variable|aci_sem
r_static
r_struct
id|semaphore
id|aci_sem
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|reset
r_static
r_int
id|reset
suffix:semicolon
id|module_param
c_func
(paren
id|reset
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|reset
comma
l_string|&quot;When set to 1, reset aci mixer.&quot;
)paren
suffix:semicolon
macro_line|#else
DECL|variable|reset
r_static
r_int
id|reset
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
DECL|variable|ide
r_static
r_int
id|ide
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|ide
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ide
comma
l_string|&quot;1 enable, 0 disable ide-port - untested&quot;
l_string|&quot; default: do nothing&quot;
)paren
suffix:semicolon
DECL|variable|wss
r_static
r_int
id|wss
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|wss
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|wss
comma
l_string|&quot;change between ACI/WSS-mixer; use 0 and 1 - untested&quot;
l_string|&quot; default: do nothing; for PCM1-pro only&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|function|print_bits
r_static
r_void
id|print_bits
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_int
id|j
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;aci: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|7
suffix:semicolon
id|j
op_ge
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%d&quot;
comma
(paren
id|c
op_rshift
id|j
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * This busy wait code normally requires less than 15 loops and&n; * practically always less than 100 loops on my i486/DX2 66 MHz.&n; *&n; * Warning: Waiting on the general status flag after reseting the MUTE&n; * function can take a VERY long time, because the PCM12 does some kind&n; * of fade-in effect. For this reason, access to the MUTE function has&n; * not been implemented at all.&n; *&n; * - The OSS interface has no mute option. It takes about 3 seconds to&n; * fade-in on my PCM20. busy_wait() handles it great now...     Robert&n; */
DECL|function|busy_wait
r_static
r_int
id|busy_wait
c_func
(paren
r_void
)paren
(brace
DECL|macro|MINTIME
mdefine_line|#define MINTIME 500
r_int
id|timeout
suffix:semicolon
r_int
r_char
id|byte
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|1
suffix:semicolon
id|timeout
op_le
id|MINTIME
op_plus
l_int|30
suffix:semicolon
id|timeout
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|byte
op_assign
id|inb
c_func
(paren
id|BUSY_REGISTER
)paren
)paren
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|timeout
op_ge
id|MINTIME
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;aci: Got READYFLAG in round %ld.&bslash;n&quot;
comma
id|timeout
op_minus
id|MINTIME
)paren
suffix:semicolon
r_return
id|byte
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timeout
op_ge
id|MINTIME
)paren
(brace
r_int
id|out
op_assign
l_int|10
op_star
id|HZ
suffix:semicolon
r_switch
c_cond
(paren
id|timeout
op_minus
id|MINTIME
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|9
suffix:colon
id|out
op_div_assign
l_int|10
suffix:semicolon
r_case
l_int|10
dot
dot
dot
l_int|19
suffix:colon
id|out
op_div_assign
l_int|10
suffix:semicolon
r_case
l_int|20
dot
dot
dot
l_int|30
suffix:colon
id|out
op_div_assign
l_int|10
suffix:semicolon
r_default
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|out
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;aci: busy_wait() time out.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* The four ACI command types are fucked up. [-:&n; * implied is: 1w      - special case for INIT&n; * write   is: 2w1r&n; * read    is: x(1w1r) where x is 1 or 2 (1 CHECK_SIG, 1 CHECK_STER,&n; *                                        1 VERSION, 2 IDCODE)&n; *  the command is only in the first write, rest is protocol overhead&n; *&n; * indexed is technically a write and used for STATUS&n; * and the special case for TUNE is: 3w1r&n; * &n; * Here the new general sheme: TUNE --&gt; aci_rw_cmd(x,  y,  z)&n; *                indexed and write --&gt; aci_rw_cmd(x,  y, -1)&n; *           implied and read (x=1) --&gt; aci_rw_cmd(x, -1, -1)&n; *&n; * Read (x&gt;=2) is not implemented (only used during initialization).&n; * Use aci_idcode[2] and aci_version...                    Robert&n; */
multiline_comment|/* Some notes for error detection: theoretically it is possible.&n; * But it doubles the I/O-traffic from ww(r) to wwwrw(r) in the normal &n; * case and doesn&squot;t seem to be designed for that...        Robert&n; */
DECL|function|aci_rawwrite
r_static
r_inline
r_int
id|aci_rawwrite
c_func
(paren
r_int
r_char
id|byte
)paren
(brace
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
op_ge
l_int|0
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;aci_rawwrite(%d)&bslash;n&quot;
comma
id|byte
)paren
suffix:semicolon
macro_line|#endif
id|outb
c_func
(paren
id|byte
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|aci_rawread
r_static
r_inline
r_int
id|aci_rawread
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|byte
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
op_ge
l_int|0
)paren
(brace
id|byte
op_assign
id|inb
c_func
(paren
id|STATUS_REGISTER
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%d = aci_rawread()&bslash;n&quot;
comma
id|byte
)paren
suffix:semicolon
macro_line|#endif
r_return
id|byte
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|aci_rw_cmd
r_int
id|aci_rw_cmd
c_func
(paren
r_int
id|write1
comma
r_int
id|write2
comma
r_int
id|write3
)paren
(brace
r_int
id|write
(braket
)braket
op_assign
(brace
id|write1
comma
id|write2
comma
id|write3
)brace
suffix:semicolon
r_int
id|read
op_assign
op_minus
id|EINTR
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|aci_sem
)paren
)paren
r_goto
id|out
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|write
(braket
id|i
)braket
template_param
l_int|255
)paren
r_break
suffix:semicolon
r_else
(brace
id|read
op_assign
id|aci_rawwrite
c_func
(paren
id|write
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
OL
l_int|0
)paren
r_goto
id|out_up
suffix:semicolon
)brace
)brace
id|read
op_assign
id|aci_rawread
c_func
(paren
)paren
suffix:semicolon
id|out_up
suffix:colon
id|up
c_func
(paren
op_amp
id|aci_sem
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|read
suffix:semicolon
)brace
DECL|variable|aci_rw_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|aci_rw_cmd
)paren
suffix:semicolon
DECL|function|setvolume
r_static
r_int
id|setvolume
c_func
(paren
r_int
id|__user
op_star
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|vol
comma
id|ret
comma
id|uservol
comma
id|buf
suffix:semicolon
id|__get_user
c_func
(paren
id|uservol
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* left channel */
id|vol
op_assign
id|uservol
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|0x20
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|left_index
comma
l_int|0x20
op_minus
id|vol
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|ret
op_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|vol
)paren
suffix:semicolon
multiline_comment|/* right channel */
id|vol
op_assign
(paren
id|uservol
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|0x20
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|right_index
comma
l_int|0x20
op_minus
id|vol
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|ret
op_or_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|vol
)paren
op_lshift
l_int|8
suffix:semicolon
id|__put_user
c_func
(paren
id|ret
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getvolume
r_static
r_int
id|getvolume
c_func
(paren
r_int
id|__user
op_star
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|vol
suffix:semicolon
r_int
id|buf
suffix:semicolon
multiline_comment|/* left channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_indexed_cmd
c_func
(paren
id|ACI_STATUS
comma
id|left_index
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|buf
OL
l_int|0x20
ques
c_cond
l_int|0x20
op_minus
id|buf
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* right channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_indexed_cmd
c_func
(paren
id|ACI_STATUS
comma
id|right_index
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|vol
op_or_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|buf
OL
l_int|0x20
ques
c_cond
l_int|0x20
op_minus
id|buf
suffix:colon
l_int|0
)paren
op_lshift
l_int|8
suffix:semicolon
id|__put_user
c_func
(paren
id|vol
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The equalizer is somewhat strange on the ACI. From -12dB to +12dB&n; * write:  0xff..down.to..0x80==0x00..up.to..0x7f&n; */
DECL|function|eq_oss2aci
r_static
r_inline
r_int
r_int
id|eq_oss2aci
c_func
(paren
r_int
r_int
id|vol
)paren
(brace
r_int
id|boost
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|50
)paren
(brace
id|vol
op_sub_assign
l_int|51
suffix:semicolon
id|boost
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|boost
)paren
id|ret
op_assign
id|SCALE
c_func
(paren
l_int|49
comma
l_int|0x7e
comma
id|vol
)paren
op_plus
l_int|1
suffix:semicolon
r_else
id|ret
op_assign
l_int|0xff
op_minus
id|SCALE
c_func
(paren
l_int|50
comma
l_int|0x7f
comma
id|vol
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|eq_aci2oss
r_static
r_inline
r_int
r_int
id|eq_aci2oss
c_func
(paren
r_int
r_int
id|vol
)paren
(brace
r_if
c_cond
(paren
id|vol
OL
l_int|0x80
)paren
r_return
id|SCALE
c_func
(paren
l_int|0x7f
comma
l_int|50
comma
id|vol
)paren
op_plus
l_int|50
suffix:semicolon
r_else
r_return
id|SCALE
c_func
(paren
l_int|0x7f
comma
l_int|50
comma
l_int|0xff
op_minus
id|vol
)paren
suffix:semicolon
)brace
DECL|function|setequalizer
r_static
r_int
id|setequalizer
c_func
(paren
r_int
id|__user
op_star
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|buf
suffix:semicolon
r_int
r_int
id|vol
suffix:semicolon
id|__get_user
c_func
(paren
id|vol
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* left channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|left_index
comma
id|eq_oss2aci
c_func
(paren
id|vol
op_amp
l_int|0xff
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
multiline_comment|/* right channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|right_index
comma
id|eq_oss2aci
c_func
(paren
(paren
id|vol
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
multiline_comment|/* the ACI equalizer is more precise */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|getequalizer
r_static
r_int
id|getequalizer
c_func
(paren
r_int
id|__user
op_star
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|buf
suffix:semicolon
r_int
r_int
id|vol
suffix:semicolon
multiline_comment|/* left channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_indexed_cmd
c_func
(paren
id|ACI_STATUS
comma
id|left_index
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|vol
op_assign
id|eq_aci2oss
c_func
(paren
id|buf
)paren
suffix:semicolon
multiline_comment|/* right channel */
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_indexed_cmd
c_func
(paren
id|ACI_STATUS
comma
id|right_index
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|vol
op_or_assign
id|eq_aci2oss
c_func
(paren
id|buf
)paren
op_lshift
l_int|8
suffix:semicolon
id|__put_user
c_func
(paren
id|vol
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aci_mixer_ioctl
r_static
r_int
id|aci_mixer_ioctl
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
id|arg
)paren
(brace
r_int
id|vol
comma
id|buf
suffix:semicolon
r_int
id|__user
op_star
id|p
op_assign
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SOUND_MIXER_WRITE_VOLUME
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_CD
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x3c
comma
l_int|0x34
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_MIC
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x38
comma
l_int|0x30
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_LINE
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x39
comma
l_int|0x31
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_SYNTH
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x3b
comma
l_int|0x33
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_PCM
suffix:colon
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x3a
comma
l_int|0x32
)paren
suffix:semicolon
r_case
id|MIXER_WRITE
c_func
(paren
id|SOUND_MIXER_RADIO
)paren
suffix:colon
multiline_comment|/* fall through */
r_case
id|SOUND_MIXER_WRITE_LINE1
suffix:colon
multiline_comment|/* AUX1 or radio */
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x3d
comma
l_int|0x35
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_LINE2
suffix:colon
multiline_comment|/* AUX2 */
r_return
id|setvolume
c_func
(paren
id|p
comma
l_int|0x3e
comma
l_int|0x36
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_BASS
suffix:colon
multiline_comment|/* set band one and two */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|setequalizer
c_func
(paren
id|p
comma
l_int|0x48
comma
l_int|0x40
)paren
)paren
op_logical_or
(paren
id|buf
op_assign
id|setequalizer
c_func
(paren
id|p
comma
l_int|0x49
comma
l_int|0x41
)paren
)paren
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_TREBLE
suffix:colon
multiline_comment|/* set band six and seven */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|setequalizer
c_func
(paren
id|p
comma
l_int|0x4d
comma
l_int|0x45
)paren
)paren
op_logical_or
(paren
id|buf
op_assign
id|setequalizer
c_func
(paren
id|p
comma
l_int|0x4e
comma
l_int|0x46
)paren
)paren
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_IGAIN
suffix:colon
multiline_comment|/* MIC pre-amp */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;B&squot;
op_logical_or
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
id|__get_user
c_func
(paren
id|vol
comma
id|p
)paren
suffix:semicolon
id|vol
op_assign
id|vol
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|3
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|ACI_WRITE_IGAIN
comma
id|vol
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|aci_micpreamp
op_assign
id|vol
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|3
comma
l_int|100
comma
id|vol
)paren
suffix:semicolon
id|vol
op_or_assign
(paren
id|vol
op_lshift
l_int|8
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|vol
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_OGAIN
suffix:colon
multiline_comment|/* Power-amp/line-out level */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;A&squot;
op_logical_or
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;B&squot;
)paren
(brace
id|__get_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
id|buf
op_assign
id|buf
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|buf
OG
l_int|50
)paren
id|vol
op_assign
l_int|1
suffix:semicolon
r_else
id|vol
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|ACI_SET_POWERAMP
comma
id|vol
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|aci_amp
op_assign
id|vol
suffix:semicolon
r_if
c_cond
(paren
id|aci_amp
)paren
id|buf
op_assign
(paren
l_int|100
op_logical_or
l_int|100
op_lshift
l_int|8
)paren
suffix:semicolon
r_else
id|buf
op_assign
l_int|0
suffix:semicolon
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_WRITE_RECSRC
suffix:colon
multiline_comment|/* handle solo mode control */
id|__get_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* unset solo when RECSRC for PCM is requested */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;B&squot;
op_logical_or
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
id|vol
op_assign
op_logical_neg
(paren
id|buf
op_amp
id|SOUND_MASK_PCM
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_write_cmd
c_func
(paren
id|ACI_SET_SOLOMODE
comma
id|vol
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
id|aci_solo
op_assign
id|vol
suffix:semicolon
)brace
id|buf
op_assign
(paren
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
multiline_comment|/* PCM20 radio */
id|buf
op_or_assign
id|SOUND_MASK_RADIO
suffix:semicolon
r_else
id|buf
op_or_assign
id|SOUND_MASK_LINE1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aci_solo
)paren
id|buf
op_or_assign
id|SOUND_MASK_PCM
suffix:semicolon
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_DEVMASK
suffix:colon
id|buf
op_assign
(paren
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_PCM
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
multiline_comment|/* PCM20 radio */
id|buf
op_or_assign
(paren
id|SOUND_MASK_RADIO
op_or
id|SOUND_MASK_IGAIN
op_or
id|SOUND_MASK_BASS
op_or
id|SOUND_MASK_TREBLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
multiline_comment|/* PCM12 */
id|buf
op_or_assign
(paren
id|SOUND_MASK_LINE1
op_or
id|SOUND_MASK_IGAIN
op_or
id|SOUND_MASK_OGAIN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;A&squot;
suffix:colon
multiline_comment|/* PCM1-pro */
id|buf
op_or_assign
(paren
id|SOUND_MASK_LINE1
op_or
id|SOUND_MASK_OGAIN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|buf
op_or_assign
id|SOUND_MASK_LINE1
suffix:semicolon
)brace
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_STEREODEVS
suffix:colon
id|buf
op_assign
(paren
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_PCM
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
multiline_comment|/* PCM20 radio */
id|buf
op_or_assign
(paren
id|SOUND_MASK_RADIO
op_or
id|SOUND_MASK_BASS
op_or
id|SOUND_MASK_TREBLE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|buf
op_or_assign
id|SOUND_MASK_LINE1
suffix:semicolon
)brace
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_RECMASK
suffix:colon
id|buf
op_assign
(paren
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_LINE2
op_or
id|SOUND_MASK_PCM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
multiline_comment|/* PCM20 radio */
id|buf
op_or_assign
id|SOUND_MASK_RADIO
suffix:semicolon
r_else
id|buf
op_or_assign
id|SOUND_MASK_LINE1
suffix:semicolon
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_RECSRC
suffix:colon
id|buf
op_assign
(paren
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
multiline_comment|/* do we need aci_solo or can I get it from the ACI? */
r_switch
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;B&squot;
suffix:colon
multiline_comment|/* PCM12 */
r_case
l_char|&squot;C&squot;
suffix:colon
multiline_comment|/* PCM20 radio */
r_if
c_cond
(paren
id|aci_version
op_ge
l_int|0xb0
)paren
(brace
r_if
c_cond
(paren
(paren
id|vol
op_assign
id|aci_rw_cmd
c_func
(paren
id|ACI_STATUS
comma
id|ACI_S_GENERAL
comma
op_minus
l_int|1
)paren
)paren
OL
l_int|0
)paren
r_return
id|vol
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_amp
l_int|0x20
)paren
id|buf
op_or_assign
id|SOUND_MASK_PCM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|aci_solo
)paren
id|buf
op_or_assign
id|SOUND_MASK_PCM
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|buf
op_or_assign
id|SOUND_MASK_PCM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
multiline_comment|/* PCM20 radio */
id|buf
op_or_assign
id|SOUND_MASK_RADIO
suffix:semicolon
r_else
id|buf
op_or_assign
id|SOUND_MASK_LINE1
suffix:semicolon
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_CAPS
suffix:colon
id|__put_user
c_func
(paren
l_int|0
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SOUND_MIXER_READ_VOLUME
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x04
comma
l_int|0x03
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_CD
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x0a
comma
l_int|0x09
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_MIC
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x06
comma
l_int|0x05
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_LINE
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x08
comma
l_int|0x07
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_SYNTH
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x0c
comma
l_int|0x0b
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_PCM
suffix:colon
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x0e
comma
l_int|0x0d
)paren
suffix:semicolon
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_RADIO
)paren
suffix:colon
multiline_comment|/* fall through */
r_case
id|SOUND_MIXER_READ_LINE1
suffix:colon
multiline_comment|/* AUX1 */
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x11
comma
l_int|0x10
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_LINE2
suffix:colon
multiline_comment|/* AUX2 */
r_return
id|getvolume
c_func
(paren
id|p
comma
l_int|0x13
comma
l_int|0x12
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_READ_BASS
suffix:colon
multiline_comment|/* get band one */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
r_return
id|getequalizer
c_func
(paren
id|p
comma
l_int|0x23
comma
l_int|0x22
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_TREBLE
suffix:colon
multiline_comment|/* get band seven */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
r_return
id|getequalizer
c_func
(paren
id|p
comma
l_int|0x2f
comma
l_int|0x2e
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_IGAIN
suffix:colon
multiline_comment|/* MIC pre-amp */
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;B&squot;
op_logical_or
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;C&squot;
)paren
(brace
multiline_comment|/* aci_micpreamp or ACI? */
r_if
c_cond
(paren
id|aci_version
op_ge
l_int|0xb0
)paren
(brace
r_if
c_cond
(paren
(paren
id|buf
op_assign
id|aci_indexed_cmd
c_func
(paren
id|ACI_STATUS
comma
id|ACI_S_READ_IGAIN
)paren
)paren
OL
l_int|0
)paren
r_return
id|buf
suffix:semicolon
)brace
r_else
id|buf
op_assign
id|aci_micpreamp
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|3
comma
l_int|100
comma
id|buf
op_le
l_int|3
ques
c_cond
id|buf
suffix:colon
l_int|3
)paren
suffix:semicolon
id|vol
op_or_assign
id|vol
op_lshift
l_int|8
suffix:semicolon
id|__put_user
c_func
(paren
id|vol
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_READ_OGAIN
suffix:colon
r_if
c_cond
(paren
id|aci_amp
)paren
id|buf
op_assign
(paren
l_int|100
op_logical_or
l_int|100
op_lshift
l_int|8
)paren
suffix:semicolon
r_else
id|buf
op_assign
l_int|0
suffix:semicolon
id|__put_user
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|aci_mixer_operations
r_static
r_struct
id|mixer_operations
id|aci_mixer_operations
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
l_string|&quot;ACI&quot;
comma
dot
id|ioctl
op_assign
id|aci_mixer_ioctl
)brace
suffix:semicolon
multiline_comment|/*&n; * There is also an internal mixer in the codec (CS4231A or AD1845),&n; * that deserves no purpose in an ACI based system which uses an&n; * external ACI controlled stereo mixer. Make sure that this codec&n; * mixer has the AUX1 input selected as the recording source, that the&n; * input gain is set near maximum and that the other channels going&n; * from the inputs to the codec output are muted.&n; */
DECL|function|attach_aci
r_static
r_int
id|__init
id|attach_aci
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|boardname
suffix:semicolon
r_int
id|i
comma
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|aci_sem
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE3
comma
l_int|0xf8f
)paren
suffix:semicolon
multiline_comment|/* Write MAD16 password */
id|aci_port
op_assign
(paren
id|inb
c_func
(paren
l_int|0xf90
)paren
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|0x344
suffix:colon
l_int|0x354
suffix:semicolon
multiline_comment|/* Get aci_port from MC4_PORT */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|aci_port
comma
l_int|3
comma
l_string|&quot;sound mixer (ACI)&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;aci: I/O area 0x%03x-0x%03x already used.&bslash;n&quot;
comma
id|aci_port
comma
id|aci_port
op_plus
l_int|2
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* force ACI into a known state */
id|rc
op_assign
op_minus
id|EFAULT
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|aci_rw_cmd
c_func
(paren
id|ACI_ERROR_OP
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
OL
l_int|0
)paren
r_goto
id|out_release_region
suffix:semicolon
multiline_comment|/* official this is one aci read call: */
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|aci_idcode
(braket
l_int|0
)braket
op_assign
id|aci_rw_cmd
c_func
(paren
id|ACI_READ_IDCODE
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
)paren
OL
l_int|0
op_logical_or
(paren
id|aci_idcode
(braket
l_int|1
)braket
op_assign
id|aci_rw_cmd
c_func
(paren
id|ACI_READ_IDCODE
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aci: Failed to read idcode on 0x%03x.&bslash;n&quot;
comma
id|aci_port
)paren
suffix:semicolon
r_goto
id|out_release_region
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|aci_version
op_assign
id|aci_rw_cmd
c_func
(paren
id|ACI_READ_VERSION
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aci: Failed to read version on 0x%03x.&bslash;n&quot;
comma
id|aci_port
)paren
suffix:semicolon
r_goto
id|out_release_region
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|0
)braket
op_eq
l_char|&squot;m&squot;
)paren
(brace
multiline_comment|/* It looks like a miro sound card. */
r_switch
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;A&squot;
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM1 pro / early PCM12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;B&squot;
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;C&squot;
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM20 radio&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|boardname
op_assign
l_string|&quot;unknown miro&quot;
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;aci: Warning: unsupported card! - &quot;
l_string|&quot;no hardware, no specs...&bslash;n&quot;
)paren
suffix:semicolon
id|boardname
op_assign
l_string|&quot;unknown Cardinal Technologies&quot;
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&lt;ACI 0x%02x, id %02x/%02x &bslash;&quot;%c/%c&bslash;&quot;, (%s)&gt; at 0x%03x&bslash;n&quot;
comma
id|aci_version
comma
id|aci_idcode
(braket
l_int|0
)braket
comma
id|aci_idcode
(braket
l_int|1
)braket
comma
id|aci_idcode
(braket
l_int|0
)braket
comma
id|aci_idcode
(braket
l_int|1
)braket
comma
id|boardname
comma
id|aci_port
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
(brace
multiline_comment|/* first write()s after reset fail with my PCM20 */
r_if
c_cond
(paren
id|aci_rw_cmd
c_func
(paren
id|ACI_INIT
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)paren
OL
l_int|0
op_logical_or
id|aci_rw_cmd
c_func
(paren
id|ACI_ERROR_OP
comma
id|ACI_ERROR_OP
comma
id|ACI_ERROR_OP
)paren
OL
l_int|0
op_logical_or
id|aci_rw_cmd
c_func
(paren
id|ACI_ERROR_OP
comma
id|ACI_ERROR_OP
comma
id|ACI_ERROR_OP
)paren
OL
l_int|0
)paren
r_goto
id|out_release_region
suffix:semicolon
)brace
multiline_comment|/* the PCM20 is muted after reset (and reboot) */
r_if
c_cond
(paren
id|aci_rw_cmd
c_func
(paren
id|ACI_SET_MUTE
comma
l_int|0x00
comma
op_minus
l_int|1
)paren
OL
l_int|0
)paren
r_goto
id|out_release_region
suffix:semicolon
r_if
c_cond
(paren
id|ide
op_ge
l_int|0
)paren
r_if
c_cond
(paren
id|aci_rw_cmd
c_func
(paren
id|ACI_SET_IDE
comma
op_logical_neg
id|ide
comma
op_minus
l_int|1
)paren
OL
l_int|0
)paren
r_goto
id|out_release_region
suffix:semicolon
r_if
c_cond
(paren
id|wss
op_ge
l_int|0
op_logical_and
id|aci_idcode
(braket
l_int|1
)braket
op_eq
l_char|&squot;A&squot;
)paren
r_if
c_cond
(paren
id|aci_rw_cmd
c_func
(paren
id|ACI_SET_WSS
comma
op_logical_neg
op_logical_neg
id|wss
comma
op_minus
l_int|1
)paren
OL
l_int|0
)paren
r_goto
id|out_release_region
suffix:semicolon
id|mixer_device
op_assign
id|sound_install_mixer
c_func
(paren
id|MIXER_DRIVER_VERSION
comma
id|boardname
comma
op_amp
id|aci_mixer_operations
comma
r_sizeof
(paren
id|aci_mixer_operations
)paren
comma
l_int|NULL
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mixer_device
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aci: Failed to install mixer.&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|mixer_device
suffix:semicolon
r_goto
id|out_release_region
suffix:semicolon
)brace
multiline_comment|/* else Maybe initialize the CS4231A mixer here... */
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_release_region
suffix:colon
id|release_region
c_func
(paren
id|aci_port
comma
l_int|3
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|unload_aci
r_static
r_void
id|__exit
id|unload_aci
c_func
(paren
r_void
)paren
(brace
id|sound_unload_mixerdev
c_func
(paren
id|mixer_device
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|aci_port
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|variable|attach_aci
id|module_init
c_func
(paren
id|attach_aci
)paren
suffix:semicolon
DECL|variable|unload_aci
id|module_exit
c_func
(paren
id|unload_aci
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
