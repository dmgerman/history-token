multiline_comment|/* $Id: termios.h,v 1.2 2000/01/27 23:45:30 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_TERMIOS_H
DECL|macro|_ASM_TERMIOS_H
mdefine_line|#define _ASM_TERMIOS_H
macro_line|#include &lt;asm/termbits.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
DECL|struct|sgttyb
r_struct
id|sgttyb
(brace
DECL|member|sg_ispeed
r_char
id|sg_ispeed
suffix:semicolon
DECL|member|sg_ospeed
r_char
id|sg_ospeed
suffix:semicolon
DECL|member|sg_erase
r_char
id|sg_erase
suffix:semicolon
DECL|member|sg_kill
r_char
id|sg_kill
suffix:semicolon
DECL|member|sg_flags
r_int
id|sg_flags
suffix:semicolon
multiline_comment|/* SGI special - int, not short */
)brace
suffix:semicolon
DECL|struct|tchars
r_struct
id|tchars
(brace
DECL|member|t_intrc
r_char
id|t_intrc
suffix:semicolon
DECL|member|t_quitc
r_char
id|t_quitc
suffix:semicolon
DECL|member|t_startc
r_char
id|t_startc
suffix:semicolon
DECL|member|t_stopc
r_char
id|t_stopc
suffix:semicolon
DECL|member|t_eofc
r_char
id|t_eofc
suffix:semicolon
DECL|member|t_brkc
r_char
id|t_brkc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ltchars
r_struct
id|ltchars
(brace
DECL|member|t_suspc
r_char
id|t_suspc
suffix:semicolon
multiline_comment|/* stop process signal */
DECL|member|t_dsuspc
r_char
id|t_dsuspc
suffix:semicolon
multiline_comment|/* delayed stop process signal */
DECL|member|t_rprntc
r_char
id|t_rprntc
suffix:semicolon
multiline_comment|/* reprint line */
DECL|member|t_flushc
r_char
id|t_flushc
suffix:semicolon
multiline_comment|/* flush output (toggles) */
DECL|member|t_werasc
r_char
id|t_werasc
suffix:semicolon
multiline_comment|/* word erase */
DECL|member|t_lnextc
r_char
id|t_lnextc
suffix:semicolon
multiline_comment|/* literal next character */
)brace
suffix:semicolon
multiline_comment|/* TIOCGSIZE, TIOCSSIZE not defined yet.  Only needed for SunOS source&n;   compatibility anyway ... */
DECL|struct|winsize
r_struct
id|winsize
(brace
DECL|member|ws_row
r_int
r_int
id|ws_row
suffix:semicolon
DECL|member|ws_col
r_int
r_int
id|ws_col
suffix:semicolon
DECL|member|ws_xpixel
r_int
r_int
id|ws_xpixel
suffix:semicolon
DECL|member|ws_ypixel
r_int
r_int
id|ws_ypixel
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCC
mdefine_line|#define NCC&t;8
DECL|struct|termio
r_struct
id|termio
(brace
DECL|member|c_iflag
r_int
r_int
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
r_int
r_int
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
r_int
r_int
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
r_int
r_int
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
DECL|member|c_line
r_char
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
r_int
r_char
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;intr=^C&t;&t;quit=^&bslash;&t;&t;erase=del&t;kill=^U&n; *&t;vmin=&bslash;1&t;&t;vtime=&bslash;0&t;eol2=&bslash;0&t;&t;swtc=&bslash;0&n; *&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;vdsusp=&n; *&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n; *&t;eof=^D&t;&t;eol=&bslash;0&n; */
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;1&bslash;0&bslash;0&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;004&bslash;0&quot;
macro_line|#endif
multiline_comment|/* modem lines */
DECL|macro|TIOCM_LE
mdefine_line|#define TIOCM_LE&t;0x001&t;&t;/* line enable */
DECL|macro|TIOCM_DTR
mdefine_line|#define TIOCM_DTR&t;0x002&t;&t;/* data terminal ready */
DECL|macro|TIOCM_RTS
mdefine_line|#define TIOCM_RTS&t;0x004&t;&t;/* request to send */
DECL|macro|TIOCM_ST
mdefine_line|#define TIOCM_ST&t;0x010&t;&t;/* secondary transmit */
DECL|macro|TIOCM_SR
mdefine_line|#define TIOCM_SR&t;0x020&t;&t;/* secondary receive */
DECL|macro|TIOCM_CTS
mdefine_line|#define TIOCM_CTS&t;0x040&t;&t;/* clear to send */
DECL|macro|TIOCM_CAR
mdefine_line|#define TIOCM_CAR&t;0x100&t;&t;/* carrier detect */
DECL|macro|TIOCM_CD
mdefine_line|#define TIOCM_CD&t;TIOCM_CAR
DECL|macro|TIOCM_RNG
mdefine_line|#define TIOCM_RNG&t;0x200&t;&t;/* ring */
DECL|macro|TIOCM_RI
mdefine_line|#define TIOCM_RI&t;TIOCM_RNG
DECL|macro|TIOCM_DSR
mdefine_line|#define TIOCM_DSR&t;0x400&t;&t;/* data set ready */
DECL|macro|TIOCM_OUT1
mdefine_line|#define TIOCM_OUT1&t;0x2000
DECL|macro|TIOCM_OUT2
mdefine_line|#define TIOCM_OUT2&t;0x4000
DECL|macro|TIOCM_LOOP
mdefine_line|#define TIOCM_LOOP&t;0x8000
multiline_comment|/* line disciplines */
DECL|macro|N_TTY
mdefine_line|#define N_TTY&t;&t;0
DECL|macro|N_SLIP
mdefine_line|#define N_SLIP&t;&t;1
DECL|macro|N_MOUSE
mdefine_line|#define N_MOUSE&t;&t;2
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;&t;3
DECL|macro|N_STRIP
mdefine_line|#define N_STRIP&t;&t;4
DECL|macro|N_AX25
mdefine_line|#define N_AX25&t;&t;5
DECL|macro|N_X25
mdefine_line|#define N_X25&t;&t;6&t;&t;/* X.25 async */
DECL|macro|N_6PACK
mdefine_line|#define N_6PACK&t;&t;7
DECL|macro|N_MASC
mdefine_line|#define N_MASC&t;&t;8&t;/* Reserved fo Mobitex module &lt;kaz@cafe.net&gt; */
DECL|macro|N_R3964
mdefine_line|#define N_R3964&t;&t;9&t;/* Reserved for Simatic R3964 module */
DECL|macro|N_PROFIBUS_FDL
mdefine_line|#define N_PROFIBUS_FDL&t;10&t;/* Reserved for Profibus &lt;Dave@mvhi.com&gt; */
DECL|macro|N_IRDA
mdefine_line|#define N_IRDA&t;&t;11&t;/* Linux IrDa - http://www.cs.uit.no/~dagb/irda/irda.html */
DECL|macro|N_SMSBLOCK
mdefine_line|#define N_SMSBLOCK&t;12&t;/* SMS block mode - for talking to GSM data cards about SMS messages */
DECL|macro|N_HDLC
mdefine_line|#define N_HDLC&t;&t;13&t;/* synchronous HDLC */
DECL|macro|N_SYNC_PPP
mdefine_line|#define N_SYNC_PPP&t;14&t;/* synchronous PPP */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(termios, termio) &bslash;&n;({ &bslash;&n;&t;unsigned short tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;(termios)-&gt;c_iflag = (0xffff0000 &amp; ((termios)-&gt;c_iflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;(termios)-&gt;c_oflag = (0xffff0000 &amp; ((termios)-&gt;c_oflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;(termios)-&gt;c_cflag = (0xffff0000 &amp; ((termios)-&gt;c_cflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;(termios)-&gt;c_lflag = (0xffff0000 &amp; ((termios)-&gt;c_lflag)) | tmp; &bslash;&n;&t;get_user((termios)-&gt;c_line, &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_from_user((termios)-&gt;c_cc, (termio)-&gt;c_cc, NCC); &bslash;&n;})
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(termio, termios) &bslash;&n;({ &bslash;&n;&t;put_user((termios)-&gt;c_iflag, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;put_user((termios)-&gt;c_oflag, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;put_user((termios)-&gt;c_cflag, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;put_user((termios)-&gt;c_lflag, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;put_user((termios)-&gt;c_line, &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_to_user((termio)-&gt;c_cc, (termios)-&gt;c_cc, NCC); &bslash;&n;})
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) copy_from_user(k, u, sizeof(struct termios))
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) copy_to_user(u, k, sizeof(struct termios))
macro_line|#endif /* defined(__KERNEL__) */
macro_line|#endif /* _ASM_TERMIOS_H */
eof
