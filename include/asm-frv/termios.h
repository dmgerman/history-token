macro_line|#ifndef _ASM_TERMIOS_H
DECL|macro|_ASM_TERMIOS_H
mdefine_line|#define _ASM_TERMIOS_H
macro_line|#include &lt;asm/termbits.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
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
macro_line|#ifdef __KERNEL__
multiline_comment|/*&t;intr=^C&t;&t;quit=^|&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;vtime=&bslash;0&t;vmin=&bslash;1&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;eol=&bslash;0&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;eol2=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;1&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;0&quot;
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
DECL|macro|TIOCM_MODEM_BITS
mdefine_line|#define TIOCM_MODEM_BITS       TIOCM_OUT2      /* IRDA support */
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
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
macro_line|#include &lt;asm-generic/termios.h&gt;
macro_line|#endif /* _ASM_TERMIOS_H */
eof
