multiline_comment|/* $Id: termios.h,v 1.9 1999/12/02 09:57:53 davem Exp $ */
macro_line|#ifndef _SPARC64_TERMIOS_H
DECL|macro|_SPARC64_TERMIOS_H
mdefine_line|#define _SPARC64_TERMIOS_H
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/termbits.h&gt;
macro_line|#if defined(__KERNEL__) || defined(__DEFINE_BSD_TERMIOS)
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
macro_line|#endif /* __KERNEL__ */
DECL|struct|sunos_ttysize
r_struct
id|sunos_ttysize
(brace
DECL|member|st_lines
r_int
id|st_lines
suffix:semicolon
multiline_comment|/* Lines on the terminal */
DECL|member|st_columns
r_int
id|st_columns
suffix:semicolon
multiline_comment|/* Columns on the terminal */
)brace
suffix:semicolon
multiline_comment|/* Used for packet mode */
DECL|macro|TIOCPKT_DATA
mdefine_line|#define TIOCPKT_DATA&t;&t; 0
DECL|macro|TIOCPKT_FLUSHREAD
mdefine_line|#define TIOCPKT_FLUSHREAD&t; 1
DECL|macro|TIOCPKT_FLUSHWRITE
mdefine_line|#define TIOCPKT_FLUSHWRITE&t; 2
DECL|macro|TIOCPKT_STOP
mdefine_line|#define TIOCPKT_STOP&t;&t; 4
DECL|macro|TIOCPKT_START
mdefine_line|#define TIOCPKT_START&t;&t; 8
DECL|macro|TIOCPKT_NOSTOP
mdefine_line|#define TIOCPKT_NOSTOP&t;&t;16
DECL|macro|TIOCPKT_DOSTOP
mdefine_line|#define TIOCPKT_DOSTOP&t;&t;32
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
mdefine_line|#define N_X25&t;&t;6
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
mdefine_line|#define N_SYNC_PPP&t;14&t;/* synchronous PPP */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * c_cc characters in the termio structure.  Oh, how I love being&n; * backwardly compatible.  Notice that character 4 and 5 are&n; * interpreted differently depending on whether ICANON is set in&n; * c_lflag.  If it&squot;s set, they are used as _VEOF and _VEOL, otherwise&n; * as _VMIN and V_TIME.  This is for compatibility with OSF/1 (which&n; * is compatible with sysV)...&n; */
DECL|macro|_VMIN
mdefine_line|#define _VMIN&t;4
DECL|macro|_VTIME
mdefine_line|#define _VTIME&t;5
multiline_comment|/*&t;intr=^C&t;&t;quit=^&bslash;&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;eol=&bslash;0&t;&t;eol2=&bslash;0&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;dsusp=^Y&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;vmin=&bslash;1         vtime=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;000&bslash;000&bslash;000&bslash;021&bslash;023&bslash;032&bslash;031&bslash;022&bslash;025&bslash;027&bslash;026&bslash;001&bslash;000&quot;
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(termios, termio) &bslash;&n;({ &bslash;&n;&t;unsigned short tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;(termios)-&gt;c_iflag = (0xffff0000 &amp; ((termios)-&gt;c_iflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;(termios)-&gt;c_oflag = (0xffff0000 &amp; ((termios)-&gt;c_oflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;(termios)-&gt;c_cflag = (0xffff0000 &amp; ((termios)-&gt;c_cflag)) | tmp; &bslash;&n;&t;get_user(tmp, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;(termios)-&gt;c_lflag = (0xffff0000 &amp; ((termios)-&gt;c_lflag)) | tmp; &bslash;&n;&t;copy_from_user((termios)-&gt;c_cc, (termio)-&gt;c_cc, NCC); &bslash;&n;&t;0; &bslash;&n;})
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; *&n; * Note the &quot;fun&quot; _VMIN overloading.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(termio, termios) &bslash;&n;({ &bslash;&n;&t;put_user((termios)-&gt;c_iflag, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;put_user((termios)-&gt;c_oflag, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;put_user((termios)-&gt;c_cflag, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;put_user((termios)-&gt;c_lflag, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;put_user((termios)-&gt;c_line,  &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_to_user((termio)-&gt;c_cc, (termios)-&gt;c_cc, NCC); &bslash;&n;&t;if (!((termios)-&gt;c_lflag &amp; ICANON)) { &bslash;&n;&t;&t;put_user((termios)-&gt;c_cc[VMIN], &amp;(termio)-&gt;c_cc[_VMIN]); &bslash;&n;&t;&t;put_user((termios)-&gt;c_cc[VTIME], &amp;(termio)-&gt;c_cc[_VTIME]); &bslash;&n;&t;} &bslash;&n;&t;0; &bslash;&n;})
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) &bslash;&n;({ &bslash;&n;&t;get_user((k)-&gt;c_iflag, &amp;(u)-&gt;c_iflag); &bslash;&n;&t;get_user((k)-&gt;c_oflag, &amp;(u)-&gt;c_oflag); &bslash;&n;&t;get_user((k)-&gt;c_cflag, &amp;(u)-&gt;c_cflag); &bslash;&n;&t;get_user((k)-&gt;c_lflag, &amp;(u)-&gt;c_lflag); &bslash;&n;&t;get_user((k)-&gt;c_line,  &amp;(u)-&gt;c_line); &bslash;&n;&t;copy_from_user((k)-&gt;c_cc, (u)-&gt;c_cc, NCCS); &bslash;&n;&t;if((k)-&gt;c_lflag &amp; ICANON) { &bslash;&n;&t;&t;get_user((k)-&gt;c_cc[VEOF], &amp;(u)-&gt;c_cc[VEOF]); &bslash;&n;&t;&t;get_user((k)-&gt;c_cc[VEOL], &amp;(u)-&gt;c_cc[VEOL]); &bslash;&n;&t;} else { &bslash;&n;&t;&t;get_user((k)-&gt;c_cc[VMIN],  &amp;(u)-&gt;c_cc[_VMIN]); &bslash;&n;&t;&t;get_user((k)-&gt;c_cc[VTIME], &amp;(u)-&gt;c_cc[_VTIME]); &bslash;&n;&t;} &bslash;&n;&t;0; &bslash;&n;})
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) &bslash;&n;({ &bslash;&n;&t;put_user((k)-&gt;c_iflag, &amp;(u)-&gt;c_iflag); &bslash;&n;&t;put_user((k)-&gt;c_oflag, &amp;(u)-&gt;c_oflag); &bslash;&n;&t;put_user((k)-&gt;c_cflag, &amp;(u)-&gt;c_cflag); &bslash;&n;&t;put_user((k)-&gt;c_lflag, &amp;(u)-&gt;c_lflag); &bslash;&n;&t;put_user((k)-&gt;c_line, &amp;(u)-&gt;c_line); &bslash;&n;&t;copy_to_user((u)-&gt;c_cc, (k)-&gt;c_cc, NCCS); &bslash;&n;&t;if(!((k)-&gt;c_lflag &amp; ICANON)) { &bslash;&n;&t;&t;put_user((k)-&gt;c_cc[VMIN],  &amp;(u)-&gt;c_cc[_VMIN]); &bslash;&n;&t;&t;put_user((k)-&gt;c_cc[VTIME], &amp;(u)-&gt;c_cc[_VTIME]); &bslash;&n;&t;} else { &bslash;&n;&t;&t;put_user((k)-&gt;c_cc[VEOF], &amp;(u)-&gt;c_cc[VEOF]); &bslash;&n;&t;&t;put_user((k)-&gt;c_cc[VEOL], &amp;(u)-&gt;c_cc[VEOL]); &bslash;&n;&t;} &bslash;&n;&t;0; &bslash;&n;})
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* _SPARC64_TERMIOS_H */
eof
