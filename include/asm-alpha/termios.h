macro_line|#ifndef _ALPHA_TERMIOS_H
DECL|macro|_ALPHA_TERMIOS_H
mdefine_line|#define _ALPHA_TERMIOS_H
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/termbits.h&gt;
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
DECL|member|t_dsuspc
r_char
id|t_dsuspc
suffix:semicolon
DECL|member|t_rprntc
r_char
id|t_rprntc
suffix:semicolon
DECL|member|t_flushc
r_char
id|t_flushc
suffix:semicolon
DECL|member|t_werasc
r_char
id|t_werasc
suffix:semicolon
DECL|member|t_lnextc
r_char
id|t_lnextc
suffix:semicolon
)brace
suffix:semicolon
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
mdefine_line|#define NCC 8
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
r_int
r_char
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
r_int
r_char
id|c_cc
(braket
id|NCC
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
multiline_comment|/*&n; * c_cc characters in the termio structure.  Oh, how I love being&n; * backwardly compatible.  Notice that character 4 and 5 are&n; * interpreted differently depending on whether ICANON is set in&n; * c_lflag.  If it&squot;s set, they are used as _VEOF and _VEOL, otherwise&n; * as _VMIN and V_TIME.  This is for compatibility with OSF/1 (which&n; * is compatible with sysV)...&n; */
DECL|macro|_VINTR
mdefine_line|#define _VINTR&t;0
DECL|macro|_VQUIT
mdefine_line|#define _VQUIT&t;1
DECL|macro|_VERASE
mdefine_line|#define _VERASE&t;2
DECL|macro|_VKILL
mdefine_line|#define _VKILL&t;3
DECL|macro|_VEOF
mdefine_line|#define _VEOF&t;4
DECL|macro|_VMIN
mdefine_line|#define _VMIN&t;4
DECL|macro|_VEOL
mdefine_line|#define _VEOL&t;5
DECL|macro|_VTIME
mdefine_line|#define _VTIME&t;5
DECL|macro|_VEOL2
mdefine_line|#define _VEOL2&t;6
DECL|macro|_VSWTC
mdefine_line|#define _VSWTC&t;7
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
mdefine_line|#define N_X25&t;&t;6&t;/* X.25 async */
DECL|macro|N_6PACK
mdefine_line|#define N_6PACK&t;&t;7
DECL|macro|N_MASC
mdefine_line|#define N_MASC&t;&t;8&t;/* Reserved for Mobitex module &lt;kaz@cafe.net&gt; */
DECL|macro|N_R3964
mdefine_line|#define N_R3964&t;&t;9&t;/* Reserved for Simatic R3964 module */
DECL|macro|N_PROFIBUS_FDL
mdefine_line|#define N_PROFIBUS_FDL&t;10&t;/* Reserved for Profibus &lt;Dave@mvhi.com&gt; */
DECL|macro|N_IRDA
mdefine_line|#define N_IRDA&t;&t;11&t;/* Linux IrDa - http://irda.sourceforge.net/ */
DECL|macro|N_SMSBLOCK
mdefine_line|#define N_SMSBLOCK&t;12&t;/* SMS block mode - for talking to GSM data cards about SMS messages */
DECL|macro|N_HDLC
mdefine_line|#define N_HDLC&t;&t;13&t;/* synchronous HDLC */
DECL|macro|N_SYNC_PPP
mdefine_line|#define N_SYNC_PPP&t;14
DECL|macro|N_HCI
mdefine_line|#define N_HCI&t;&t;15  /* Bluetooth HCI UART */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&t;eof=^D&t;&t;eol=&bslash;0&t;&t;eol2=&bslash;0&t;&t;erase=del&n;&t;werase=^W&t;kill=^U&t;&t;reprint=^R&t;sxtc=&bslash;0&n;&t;intr=^C&t;&t;quit=^&bslash;&t;&t;susp=^Z&t;&t;&lt;OSF/1 VDSUSP&gt;&n;&t;start=^Q&t;stop=^S&t;&t;lnext=^V&t;discard=^U&n;&t;vmin=&bslash;1&t;&t;vtime=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;004&bslash;000&bslash;000&bslash;177&bslash;027&bslash;025&bslash;022&bslash;000&bslash;003&bslash;034&bslash;032&bslash;000&bslash;021&bslash;023&bslash;026&bslash;025&bslash;001&bslash;000&quot;
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(a_termios, u_termio)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct termios *k_termios = (a_termios);&t;&t;&t;&t;&bslash;&n;&t;struct termio k_termio;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int canon, ret;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ret = copy_from_user(&amp;k_termio, u_termio, sizeof(k_termio));&t;&t;&bslash;&n;&t;if (!ret) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* Overwrite only the low bits.  */&t;&t;&t;&t;&bslash;&n;&t;&t;*(unsigned short *)&amp;k_termios-&gt;c_iflag = k_termio.c_iflag;&t;&bslash;&n;&t;&t;*(unsigned short *)&amp;k_termios-&gt;c_oflag = k_termio.c_oflag;&t;&bslash;&n;&t;&t;*(unsigned short *)&amp;k_termios-&gt;c_cflag = k_termio.c_cflag;&t;&bslash;&n;&t;&t;*(unsigned short *)&amp;k_termios-&gt;c_lflag = k_termio.c_lflag;&t;&bslash;&n;&t;&t;canon = k_termio.c_lflag &amp; ICANON;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VINTR]  = k_termio.c_cc[_VINTR];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VQUIT]  = k_termio.c_cc[_VQUIT];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VERASE] = k_termio.c_cc[_VERASE];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VKILL]  = k_termio.c_cc[_VKILL];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VEOL2]  = k_termio.c_cc[_VEOL2];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[VSWTC]  = k_termio.c_cc[_VSWTC];&t;&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[canon ? VEOF : VMIN]  = k_termio.c_cc[_VEOF];&t;&bslash;&n;&t;&t;k_termios-&gt;c_cc[canon ? VEOL : VTIME] = k_termio.c_cc[_VEOL];&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ret;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; *&n; * Note the &quot;fun&quot; _VMIN overloading.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(u_termio, a_termios)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct termios *k_termios = (a_termios);&t;&t;&t;&bslash;&n;&t;struct termio k_termio;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int canon;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;k_termio.c_iflag = k_termios-&gt;c_iflag;&t;&t;&t;&t;&bslash;&n;&t;k_termio.c_oflag = k_termios-&gt;c_oflag;&t;&t;&t;&t;&bslash;&n;&t;k_termio.c_cflag = k_termios-&gt;c_cflag;&t;&t;&t;&t;&bslash;&n;&t;canon = (k_termio.c_lflag = k_termios-&gt;c_lflag) &amp; ICANON;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;k_termio.c_line = k_termios-&gt;c_line;&t;&t;&t;&t;&bslash;&n;&t;k_termio.c_cc[_VINTR]  = k_termios-&gt;c_cc[VINTR];&t;&t;&bslash;&n;&t;k_termio.c_cc[_VQUIT]  = k_termios-&gt;c_cc[VQUIT];&t;&t;&bslash;&n;&t;k_termio.c_cc[_VERASE] = k_termios-&gt;c_cc[VERASE];&t;&t;&bslash;&n;&t;k_termio.c_cc[_VKILL]  = k_termios-&gt;c_cc[VKILL];&t;&t;&bslash;&n;&t;k_termio.c_cc[_VEOF]   = k_termios-&gt;c_cc[canon ? VEOF : VMIN];&t;&bslash;&n;&t;k_termio.c_cc[_VEOL]   = k_termios-&gt;c_cc[canon ? VEOL : VTIME];&t;&bslash;&n;&t;k_termio.c_cc[_VEOL2]  = k_termios-&gt;c_cc[VEOL2];&t;&t;&bslash;&n;&t;k_termio.c_cc[_VSWTC]  = k_termios-&gt;c_cc[VSWTC];&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;copy_to_user(u_termio, &amp;k_termio, sizeof(k_termio));&t;&t;&bslash;&n;})
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) &bslash;&n;&t;copy_from_user(k, u, sizeof(struct termios))
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) &bslash;&n;&t;copy_to_user(u, k, sizeof(struct termios))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _ALPHA_TERMIOS_H */
eof
