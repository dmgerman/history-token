macro_line|#ifndef _SPARC64_TERMBITS_H
DECL|macro|_SPARC64_TERMBITS_H
mdefine_line|#define _SPARC64_TERMBITS_H
macro_line|#include &lt;linux/posix_types.h&gt;
DECL|typedef|cc_t
r_typedef
r_int
r_char
id|cc_t
suffix:semicolon
DECL|typedef|speed_t
r_typedef
r_int
r_int
id|speed_t
suffix:semicolon
multiline_comment|/* XXX is this right for sparc64?  it was an unsigned long... XXX */
DECL|typedef|tcflag_t
r_typedef
r_int
r_int
id|tcflag_t
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
DECL|macro|NCCS
mdefine_line|#define NCCS 17
DECL|struct|termios
r_struct
id|termios
(brace
DECL|member|c_iflag
id|tcflag_t
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
id|tcflag_t
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
id|tcflag_t
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
id|tcflag_t
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
DECL|member|c_line
id|cc_t
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
macro_line|#ifdef __KERNEL__
DECL|macro|SIZEOF_USER_TERMIOS
mdefine_line|#define SIZEOF_USER_TERMIOS sizeof (struct termios) - (2*sizeof (cc_t))
DECL|member|_x_cc
id|cc_t
id|_x_cc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* We need them to hold vmin/vtime */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* c_cc characters */
DECL|macro|VINTR
mdefine_line|#define VINTR    0
DECL|macro|VQUIT
mdefine_line|#define VQUIT    1
DECL|macro|VERASE
mdefine_line|#define VERASE   2
DECL|macro|VKILL
mdefine_line|#define VKILL    3
DECL|macro|VEOF
mdefine_line|#define VEOF     4
DECL|macro|VEOL
mdefine_line|#define VEOL     5
DECL|macro|VEOL2
mdefine_line|#define VEOL2    6
DECL|macro|VSWTC
mdefine_line|#define VSWTC    7
DECL|macro|VSTART
mdefine_line|#define VSTART   8
DECL|macro|VSTOP
mdefine_line|#define VSTOP    9
DECL|macro|VSUSP
mdefine_line|#define VSUSP    10
DECL|macro|VDSUSP
mdefine_line|#define VDSUSP   11  /* SunOS POSIX nicety I do believe... */
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT 12
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD 13
DECL|macro|VWERASE
mdefine_line|#define VWERASE  14
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT   15
multiline_comment|/* Kernel keeps vmin/vtime separated, user apps assume vmin/vtime is&n; * shared with eof/eol&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|VMIN
mdefine_line|#define VMIN     16
DECL|macro|VTIME
mdefine_line|#define VTIME    17
macro_line|#else
DECL|macro|VMIN
mdefine_line|#define VMIN     VEOF
DECL|macro|VTIME
mdefine_line|#define VTIME    VEOL
macro_line|#endif
multiline_comment|/* c_iflag bits */
DECL|macro|IGNBRK
mdefine_line|#define IGNBRK&t;0x00000001
DECL|macro|BRKINT
mdefine_line|#define BRKINT&t;0x00000002
DECL|macro|IGNPAR
mdefine_line|#define IGNPAR&t;0x00000004
DECL|macro|PARMRK
mdefine_line|#define PARMRK&t;0x00000008
DECL|macro|INPCK
mdefine_line|#define INPCK&t;0x00000010
DECL|macro|ISTRIP
mdefine_line|#define ISTRIP&t;0x00000020
DECL|macro|INLCR
mdefine_line|#define INLCR&t;0x00000040
DECL|macro|IGNCR
mdefine_line|#define IGNCR&t;0x00000080
DECL|macro|ICRNL
mdefine_line|#define ICRNL&t;0x00000100
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0x00000200
DECL|macro|IXON
mdefine_line|#define IXON&t;0x00000400
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0x00000800
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0x00001000
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0x00002000
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0x00000001
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0x00000002
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0x00000004
DECL|macro|OCRNL
mdefine_line|#define OCRNL&t;0x00000008
DECL|macro|ONOCR
mdefine_line|#define ONOCR&t;0x00000010
DECL|macro|ONLRET
mdefine_line|#define ONLRET&t;0x00000020
DECL|macro|OFILL
mdefine_line|#define OFILL&t;0x00000040
DECL|macro|OFDEL
mdefine_line|#define OFDEL&t;0x00000080
DECL|macro|NLDLY
mdefine_line|#define NLDLY&t;0x00000100
DECL|macro|NL0
mdefine_line|#define   NL0&t;0x00000000
DECL|macro|NL1
mdefine_line|#define   NL1&t;0x00000100
DECL|macro|CRDLY
mdefine_line|#define CRDLY&t;0x00000600
DECL|macro|CR0
mdefine_line|#define   CR0&t;0x00000000
DECL|macro|CR1
mdefine_line|#define   CR1&t;0x00000200
DECL|macro|CR2
mdefine_line|#define   CR2&t;0x00000400
DECL|macro|CR3
mdefine_line|#define   CR3&t;0x00000600
DECL|macro|TABDLY
mdefine_line|#define TABDLY&t;0x00001800
DECL|macro|TAB0
mdefine_line|#define   TAB0&t;0x00000000
DECL|macro|TAB1
mdefine_line|#define   TAB1&t;0x00000800
DECL|macro|TAB2
mdefine_line|#define   TAB2&t;0x00001000
DECL|macro|TAB3
mdefine_line|#define   TAB3&t;0x00001800
DECL|macro|XTABS
mdefine_line|#define   XTABS&t;0x00001800
DECL|macro|BSDLY
mdefine_line|#define BSDLY&t;0x00002000
DECL|macro|BS0
mdefine_line|#define   BS0&t;0x00000000
DECL|macro|BS1
mdefine_line|#define   BS1&t;0x00002000
DECL|macro|VTDLY
mdefine_line|#define VTDLY&t;0x00004000
DECL|macro|VT0
mdefine_line|#define   VT0&t;0x00000000
DECL|macro|VT1
mdefine_line|#define   VT1&t;0x00004000
DECL|macro|FFDLY
mdefine_line|#define FFDLY&t;0x00008000
DECL|macro|FF0
mdefine_line|#define   FF0&t;0x00000000
DECL|macro|FF1
mdefine_line|#define   FF1&t;0x00008000
DECL|macro|PAGEOUT
mdefine_line|#define PAGEOUT 0x00010000  /* SUNOS specific */
DECL|macro|WRAP
mdefine_line|#define WRAP    0x00020000  /* SUNOS specific */
multiline_comment|/* c_cflag bit meaning */
DECL|macro|CBAUD
mdefine_line|#define CBAUD&t;  0x0000100f
DECL|macro|B0
mdefine_line|#define  B0&t;  0x00000000   /* hang up */
DECL|macro|B50
mdefine_line|#define  B50&t;  0x00000001
DECL|macro|B75
mdefine_line|#define  B75&t;  0x00000002
DECL|macro|B110
mdefine_line|#define  B110&t;  0x00000003
DECL|macro|B134
mdefine_line|#define  B134&t;  0x00000004
DECL|macro|B150
mdefine_line|#define  B150&t;  0x00000005
DECL|macro|B200
mdefine_line|#define  B200&t;  0x00000006
DECL|macro|B300
mdefine_line|#define  B300&t;  0x00000007
DECL|macro|B600
mdefine_line|#define  B600&t;  0x00000008
DECL|macro|B1200
mdefine_line|#define  B1200&t;  0x00000009
DECL|macro|B1800
mdefine_line|#define  B1800&t;  0x0000000a
DECL|macro|B2400
mdefine_line|#define  B2400&t;  0x0000000b
DECL|macro|B4800
mdefine_line|#define  B4800&t;  0x0000000c
DECL|macro|B9600
mdefine_line|#define  B9600&t;  0x0000000d
DECL|macro|B19200
mdefine_line|#define  B19200&t;  0x0000000e
DECL|macro|B38400
mdefine_line|#define  B38400&t;  0x0000000f
DECL|macro|EXTA
mdefine_line|#define EXTA      B19200
DECL|macro|EXTB
mdefine_line|#define EXTB      B38400
DECL|macro|CSIZE
mdefine_line|#define  CSIZE    0x00000030
DECL|macro|CS5
mdefine_line|#define   CS5&t;  0x00000000
DECL|macro|CS6
mdefine_line|#define   CS6&t;  0x00000010
DECL|macro|CS7
mdefine_line|#define   CS7&t;  0x00000020
DECL|macro|CS8
mdefine_line|#define   CS8&t;  0x00000030
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;  0x00000040
DECL|macro|CREAD
mdefine_line|#define CREAD&t;  0x00000080
DECL|macro|PARENB
mdefine_line|#define PARENB&t;  0x00000100
DECL|macro|PARODD
mdefine_line|#define PARODD&t;  0x00000200
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;  0x00000400
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;  0x00000800
DECL|macro|CBAUDEX
mdefine_line|#define CBAUDEX   0x00001000
DECL|macro|B57600
mdefine_line|#define  B57600   0x00001001
DECL|macro|B115200
mdefine_line|#define  B115200  0x00001002
DECL|macro|B230400
mdefine_line|#define  B230400  0x00001003
DECL|macro|B460800
mdefine_line|#define  B460800  0x00001004
multiline_comment|/* This is what we can do with the Zilogs. */
DECL|macro|B76800
mdefine_line|#define  B76800   0x00001005
multiline_comment|/* This is what we can do with the SAB82532. */
DECL|macro|B153600
mdefine_line|#define  B153600  0x00001006
DECL|macro|B307200
mdefine_line|#define  B307200  0x00001007
DECL|macro|B614400
mdefine_line|#define  B614400  0x00001008
DECL|macro|B921600
mdefine_line|#define  B921600  0x00001009
multiline_comment|/* And these are the rest... */
DECL|macro|B500000
mdefine_line|#define  B500000  0x0000100a
DECL|macro|B576000
mdefine_line|#define  B576000  0x0000100b
DECL|macro|B1000000
mdefine_line|#define B1000000  0x0000100c
DECL|macro|B1152000
mdefine_line|#define B1152000  0x0000100d
DECL|macro|B1500000
mdefine_line|#define B1500000  0x0000100e
DECL|macro|B2000000
mdefine_line|#define B2000000  0x0000100f
multiline_comment|/* These have totally bogus values and nobody uses them&n;   so far. Later on we&squot;d have to use say 0x10000x and&n;   adjust CBAUD constant and drivers accordingly.&n;#define B2500000  0x00001010&n;#define B3000000  0x00001011&n;#define B3500000  0x00001012&n;#define B4000000  0x00001013  */
DECL|macro|CIBAUD
mdefine_line|#define CIBAUD&t;  0x100f0000  /* input baud rate (not used) */
DECL|macro|CMSPAR
mdefine_line|#define CMSPAR    0x40000000  /* mark or space (stick) parity */
DECL|macro|CRTSCTS
mdefine_line|#define CRTSCTS&t;  0x80000000  /* flow control */
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0x00000001
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0x00000002
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0x00000004
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0x00000008
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0x00000010
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0x00000020
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0x00000040
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0x00000080
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0x00000100
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0x00000200
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0x00000400
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0x00000800
DECL|macro|DEFECHO
mdefine_line|#define DEFECHO 0x00001000  /* SUNOS thing, what is it? */
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0x00002000
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0x00004000
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0x00008000
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
multiline_comment|/* tcflow() and TCXONC use these */
DECL|macro|TCOOFF
mdefine_line|#define&t;TCOOFF&t;&t;0
DECL|macro|TCOON
mdefine_line|#define&t;TCOON&t;&t;1
DECL|macro|TCIOFF
mdefine_line|#define&t;TCIOFF&t;&t;2
DECL|macro|TCION
mdefine_line|#define&t;TCION&t;&t;3
multiline_comment|/* tcflush() and TCFLSH use these */
DECL|macro|TCIFLUSH
mdefine_line|#define&t;TCIFLUSH&t;0
DECL|macro|TCOFLUSH
mdefine_line|#define&t;TCOFLUSH&t;1
DECL|macro|TCIOFLUSH
mdefine_line|#define&t;TCIOFLUSH&t;2
multiline_comment|/* tcsetattr uses these */
DECL|macro|TCSANOW
mdefine_line|#define&t;TCSANOW&t;&t;0
DECL|macro|TCSADRAIN
mdefine_line|#define&t;TCSADRAIN&t;1
DECL|macro|TCSAFLUSH
mdefine_line|#define&t;TCSAFLUSH&t;2
macro_line|#endif /* !(_SPARC64_TERMBITS_H) */
eof
