macro_line|#ifndef _PPC_TERMIOS_H
DECL|macro|_PPC_TERMIOS_H
mdefine_line|#define _PPC_TERMIOS_H
multiline_comment|/*&n; * Liberally adapted from alpha/termios.h.  In particular, the c_cc[]&n; * fields have been reordered so that termio &amp; termios share the&n; * common subset in the same order (for brain dead programs that don&squot;t&n; * know or care about the differences).&n; */
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
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;_IO(&squot;f&squot;, 1)
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;_IO(&squot;f&squot;, 2)
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;_IOW(&squot;f&squot;, 125, int)
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;_IOW(&squot;f&squot;, 126, int)
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;_IOR(&squot;f&squot;, 127, int)
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
DECL|macro|FIOQSIZE
mdefine_line|#define FIOQSIZE&t;_IOR(&squot;f&squot;, 128, loff_t)
DECL|macro|TIOCGETP
mdefine_line|#define TIOCGETP&t;_IOR(&squot;t&squot;, 8, struct sgttyb)
DECL|macro|TIOCSETP
mdefine_line|#define TIOCSETP&t;_IOW(&squot;t&squot;, 9, struct sgttyb)
DECL|macro|TIOCSETN
mdefine_line|#define TIOCSETN&t;_IOW(&squot;t&squot;, 10, struct sgttyb)&t;/* TIOCSETP wo flush */
DECL|macro|TIOCSETC
mdefine_line|#define TIOCSETC&t;_IOW(&squot;t&squot;, 17, struct tchars)
DECL|macro|TIOCGETC
mdefine_line|#define TIOCGETC&t;_IOR(&squot;t&squot;, 18, struct tchars)
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;_IOR(&squot;t&squot;, 19, struct termios)
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;_IOW(&squot;t&squot;, 20, struct termios)
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;_IOW(&squot;t&squot;, 21, struct termios)
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;_IOW(&squot;t&squot;, 22, struct termios)
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;_IOR(&squot;t&squot;, 23, struct termio)
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;_IOW(&squot;t&squot;, 24, struct termio)
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;_IOW(&squot;t&squot;, 25, struct termio)
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;_IOW(&squot;t&squot;, 28, struct termio)
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;_IO(&squot;t&squot;, 29)
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;_IO(&squot;t&squot;, 30)
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;_IO(&squot;t&squot;, 31)
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;_IOW(&squot;t&squot;, 103, struct winsize)
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;_IOR(&squot;t&squot;, 104, struct winsize)
DECL|macro|TIOCSTART
mdefine_line|#define&t;TIOCSTART&t;_IO(&squot;t&squot;, 110)&t;&t;/* start output, like ^Q */
DECL|macro|TIOCSTOP
mdefine_line|#define&t;TIOCSTOP&t;_IO(&squot;t&squot;, 111)&t;&t;/* stop output, like ^S */
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ        _IOR(&squot;t&squot;, 115, int)     /* output queue size */
DECL|macro|TIOCGLTC
mdefine_line|#define TIOCGLTC&t;_IOR(&squot;t&squot;, 116, struct ltchars)
DECL|macro|TIOCSLTC
mdefine_line|#define TIOCSLTC&t;_IOW(&squot;t&squot;, 117, struct ltchars)
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;_IOW(&squot;t&squot;, 118, int)
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;_IOR(&squot;t&squot;, 119, int)
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x540C
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x540D
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x540E
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x5412
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;0x5415
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;0x5416
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;0x5417
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;0x5418
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;0x5419
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;0x541A
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x541C
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;0x541D
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x541E
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x541F
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;0x5420
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;0x5422
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;0x5423
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;0x5424
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x5425&t;/* Needed for POSIX tcsendbreak() */
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x5426  /* For debugging only */
DECL|macro|TIOCSERCONFIG
mdefine_line|#define TIOCSERCONFIG&t;0x5453
DECL|macro|TIOCSERGWILD
mdefine_line|#define TIOCSERGWILD&t;0x5454
DECL|macro|TIOCSERSWILD
mdefine_line|#define TIOCSERSWILD&t;0x5455
DECL|macro|TIOCGLCKTRMIOS
mdefine_line|#define TIOCGLCKTRMIOS&t;0x5456
DECL|macro|TIOCSLCKTRMIOS
mdefine_line|#define TIOCSLCKTRMIOS&t;0x5457
DECL|macro|TIOCSERGSTRUCT
mdefine_line|#define TIOCSERGSTRUCT&t;0x5458 /* For debugging only */
DECL|macro|TIOCSERGETLSR
mdefine_line|#define TIOCSERGETLSR   0x5459 /* Get line status register */
DECL|macro|TIOCSERGETMULTI
mdefine_line|#define TIOCSERGETMULTI 0x545A /* Get multiport config  */
DECL|macro|TIOCSERSETMULTI
mdefine_line|#define TIOCSERSETMULTI 0x545B /* Set multiport config */
DECL|macro|TIOCMIWAIT
mdefine_line|#define TIOCMIWAIT&t;0x545C&t;/* wait for a change on serial input line(s) */
DECL|macro|TIOCGICOUNT
mdefine_line|#define TIOCGICOUNT&t;0x545D&t;/* read serial port inline interrupt counts */
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
DECL|macro|NCC
mdefine_line|#define NCC 10
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
multiline_comment|/* c_cc characters */
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
mdefine_line|#define _VMIN&t;5
DECL|macro|_VEOL
mdefine_line|#define _VEOL&t;6
DECL|macro|_VTIME
mdefine_line|#define _VTIME&t;7
DECL|macro|_VEOL2
mdefine_line|#define _VEOL2&t;8
DECL|macro|_VSWTC
mdefine_line|#define _VSWTC&t;9
macro_line|#ifdef __KERNEL__
multiline_comment|/*                   ^C  ^&bslash; del  ^U  ^D   1   0   0   0   0  ^W  ^R  ^Z  ^Q  ^S  ^V  ^U  */
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;001&bslash;000&bslash;000&bslash;000&bslash;000&bslash;027&bslash;022&bslash;032&bslash;021&bslash;023&bslash;026&bslash;025&quot; 
macro_line|#endif
multiline_comment|/* modem lines */
DECL|macro|TIOCM_LE
mdefine_line|#define TIOCM_LE&t;0x001
DECL|macro|TIOCM_DTR
mdefine_line|#define TIOCM_DTR&t;0x002
DECL|macro|TIOCM_RTS
mdefine_line|#define TIOCM_RTS&t;0x004
DECL|macro|TIOCM_ST
mdefine_line|#define TIOCM_ST&t;0x008
DECL|macro|TIOCM_SR
mdefine_line|#define TIOCM_SR&t;0x010
DECL|macro|TIOCM_CTS
mdefine_line|#define TIOCM_CTS&t;0x020
DECL|macro|TIOCM_CAR
mdefine_line|#define TIOCM_CAR&t;0x040
DECL|macro|TIOCM_RNG
mdefine_line|#define TIOCM_RNG&t;0x080
DECL|macro|TIOCM_DSR
mdefine_line|#define TIOCM_DSR&t;0x100
DECL|macro|TIOCM_CD
mdefine_line|#define TIOCM_CD&t;TIOCM_CAR
DECL|macro|TIOCM_RI
mdefine_line|#define TIOCM_RI&t;TIOCM_RNG
DECL|macro|TIOCM_OUT1
mdefine_line|#define TIOCM_OUT1&t;0x2000
DECL|macro|TIOCM_OUT2
mdefine_line|#define TIOCM_OUT2&t;0x4000
DECL|macro|TIOCM_LOOP
mdefine_line|#define TIOCM_LOOP&t;0x8000
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
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
mdefine_line|#define N_IRDA&t;&t;11&t;/* Linux IrDa - http://www.cs.uit.no/~dagb/irda/irda.html */
DECL|macro|N_SMSBLOCK
mdefine_line|#define N_SMSBLOCK&t;12&t;/* SMS block mode - for talking to GSM data cards about SMS messages */
DECL|macro|N_HDLC
mdefine_line|#define N_HDLC&t;&t;13&t;/* synchronous HDLC */
DECL|macro|N_SYNC_PPP
mdefine_line|#define N_SYNC_PPP&t;14
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|macro|SET_LOW_TERMIOS_BITS
mdefine_line|#define SET_LOW_TERMIOS_BITS(termios, termio, x) { &bslash;&n;&t;unsigned short __tmp; &bslash;&n;&t;get_user(__tmp,&amp;(termio)-&gt;x); &bslash;&n;&t;(termios)-&gt;x = (0xffff0000 &amp; (termios)-&gt;x) | __tmp; &bslash;&n;}
DECL|macro|user_termio_to_kernel_termios
mdefine_line|#define user_termio_to_kernel_termios(termios, termio) &bslash;&n;({ &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_iflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_oflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_cflag); &bslash;&n;&t;SET_LOW_TERMIOS_BITS(termios, termio, c_lflag); &bslash;&n;&t;copy_from_user((termios)-&gt;c_cc, (termio)-&gt;c_cc, NCC); &bslash;&n;})
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; */
DECL|macro|kernel_termios_to_user_termio
mdefine_line|#define kernel_termios_to_user_termio(termio, termios) &bslash;&n;({ &bslash;&n;&t;put_user((termios)-&gt;c_iflag, &amp;(termio)-&gt;c_iflag); &bslash;&n;&t;put_user((termios)-&gt;c_oflag, &amp;(termio)-&gt;c_oflag); &bslash;&n;&t;put_user((termios)-&gt;c_cflag, &amp;(termio)-&gt;c_cflag); &bslash;&n;&t;put_user((termios)-&gt;c_lflag, &amp;(termio)-&gt;c_lflag); &bslash;&n;&t;put_user((termios)-&gt;c_line,  &amp;(termio)-&gt;c_line); &bslash;&n;&t;copy_to_user((termio)-&gt;c_cc, (termios)-&gt;c_cc, NCC); &bslash;&n;})
DECL|macro|user_termios_to_kernel_termios
mdefine_line|#define user_termios_to_kernel_termios(k, u) copy_from_user(k, u, sizeof(struct termios))
DECL|macro|kernel_termios_to_user_termios
mdefine_line|#define kernel_termios_to_user_termios(u, k) copy_to_user(u, k, sizeof(struct termios))
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _PPC_TERMIOS_H */
eof
