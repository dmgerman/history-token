macro_line|#ifndef __ARCH_I386_TERMBITS_H__
DECL|macro|__ARCH_I386_TERMBITS_H__
mdefine_line|#define __ARCH_I386_TERMBITS_H__
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
DECL|typedef|tcflag_t
r_typedef
r_int
r_int
id|tcflag_t
suffix:semicolon
DECL|macro|NCCS
mdefine_line|#define NCCS 19
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
)brace
suffix:semicolon
multiline_comment|/* c_cc characters */
DECL|macro|VINTR
mdefine_line|#define VINTR 0
DECL|macro|VQUIT
mdefine_line|#define VQUIT 1
DECL|macro|VERASE
mdefine_line|#define VERASE 2
DECL|macro|VKILL
mdefine_line|#define VKILL 3
DECL|macro|VEOF
mdefine_line|#define VEOF 4
DECL|macro|VTIME
mdefine_line|#define VTIME 5
DECL|macro|VMIN
mdefine_line|#define VMIN 6
DECL|macro|VSWTC
mdefine_line|#define VSWTC 7
DECL|macro|VSTART
mdefine_line|#define VSTART 8
DECL|macro|VSTOP
mdefine_line|#define VSTOP 9
DECL|macro|VSUSP
mdefine_line|#define VSUSP 10
DECL|macro|VEOL
mdefine_line|#define VEOL 11
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT 12
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD 13
DECL|macro|VWERASE
mdefine_line|#define VWERASE 14
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT 15
DECL|macro|VEOL2
mdefine_line|#define VEOL2 16
multiline_comment|/* c_iflag bits */
DECL|macro|IGNBRK
mdefine_line|#define IGNBRK&t;0000001
DECL|macro|BRKINT
mdefine_line|#define BRKINT&t;0000002
DECL|macro|IGNPAR
mdefine_line|#define IGNPAR&t;0000004
DECL|macro|PARMRK
mdefine_line|#define PARMRK&t;0000010
DECL|macro|INPCK
mdefine_line|#define INPCK&t;0000020
DECL|macro|ISTRIP
mdefine_line|#define ISTRIP&t;0000040
DECL|macro|INLCR
mdefine_line|#define INLCR&t;0000100
DECL|macro|IGNCR
mdefine_line|#define IGNCR&t;0000200
DECL|macro|ICRNL
mdefine_line|#define ICRNL&t;0000400
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0001000
DECL|macro|IXON
mdefine_line|#define IXON&t;0002000
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0004000
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0010000
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0020000
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0000001
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0000002
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0000004
DECL|macro|OCRNL
mdefine_line|#define OCRNL&t;0000010
DECL|macro|ONOCR
mdefine_line|#define ONOCR&t;0000020
DECL|macro|ONLRET
mdefine_line|#define ONLRET&t;0000040
DECL|macro|OFILL
mdefine_line|#define OFILL&t;0000100
DECL|macro|OFDEL
mdefine_line|#define OFDEL&t;0000200
DECL|macro|NLDLY
mdefine_line|#define NLDLY&t;0000400
DECL|macro|NL0
mdefine_line|#define   NL0&t;0000000
DECL|macro|NL1
mdefine_line|#define   NL1&t;0000400
DECL|macro|CRDLY
mdefine_line|#define CRDLY&t;0003000
DECL|macro|CR0
mdefine_line|#define   CR0&t;0000000
DECL|macro|CR1
mdefine_line|#define   CR1&t;0001000
DECL|macro|CR2
mdefine_line|#define   CR2&t;0002000
DECL|macro|CR3
mdefine_line|#define   CR3&t;0003000
DECL|macro|TABDLY
mdefine_line|#define TABDLY&t;0014000
DECL|macro|TAB0
mdefine_line|#define   TAB0&t;0000000
DECL|macro|TAB1
mdefine_line|#define   TAB1&t;0004000
DECL|macro|TAB2
mdefine_line|#define   TAB2&t;0010000
DECL|macro|TAB3
mdefine_line|#define   TAB3&t;0014000
DECL|macro|XTABS
mdefine_line|#define   XTABS&t;0014000
DECL|macro|BSDLY
mdefine_line|#define BSDLY&t;0020000
DECL|macro|BS0
mdefine_line|#define   BS0&t;0000000
DECL|macro|BS1
mdefine_line|#define   BS1&t;0020000
DECL|macro|VTDLY
mdefine_line|#define VTDLY&t;0040000
DECL|macro|VT0
mdefine_line|#define   VT0&t;0000000
DECL|macro|VT1
mdefine_line|#define   VT1&t;0040000
DECL|macro|FFDLY
mdefine_line|#define FFDLY&t;0100000
DECL|macro|FF0
mdefine_line|#define   FF0&t;0000000
DECL|macro|FF1
mdefine_line|#define   FF1&t;0100000
multiline_comment|/* c_cflag bit meaning */
DECL|macro|CBAUD
mdefine_line|#define CBAUD&t;0010017
DECL|macro|B0
mdefine_line|#define  B0&t;0000000&t;&t;/* hang up */
DECL|macro|B50
mdefine_line|#define  B50&t;0000001
DECL|macro|B75
mdefine_line|#define  B75&t;0000002
DECL|macro|B110
mdefine_line|#define  B110&t;0000003
DECL|macro|B134
mdefine_line|#define  B134&t;0000004
DECL|macro|B150
mdefine_line|#define  B150&t;0000005
DECL|macro|B200
mdefine_line|#define  B200&t;0000006
DECL|macro|B300
mdefine_line|#define  B300&t;0000007
DECL|macro|B600
mdefine_line|#define  B600&t;0000010
DECL|macro|B1200
mdefine_line|#define  B1200&t;0000011
DECL|macro|B1800
mdefine_line|#define  B1800&t;0000012
DECL|macro|B2400
mdefine_line|#define  B2400&t;0000013
DECL|macro|B4800
mdefine_line|#define  B4800&t;0000014
DECL|macro|B9600
mdefine_line|#define  B9600&t;0000015
DECL|macro|B19200
mdefine_line|#define  B19200&t;0000016
DECL|macro|B38400
mdefine_line|#define  B38400&t;0000017
DECL|macro|EXTA
mdefine_line|#define EXTA B19200
DECL|macro|EXTB
mdefine_line|#define EXTB B38400
DECL|macro|CSIZE
mdefine_line|#define CSIZE&t;0000060
DECL|macro|CS5
mdefine_line|#define   CS5&t;0000000
DECL|macro|CS6
mdefine_line|#define   CS6&t;0000020
DECL|macro|CS7
mdefine_line|#define   CS7&t;0000040
DECL|macro|CS8
mdefine_line|#define   CS8&t;0000060
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;0000100
DECL|macro|CREAD
mdefine_line|#define CREAD&t;0000200
DECL|macro|PARENB
mdefine_line|#define PARENB&t;0000400
DECL|macro|PARODD
mdefine_line|#define PARODD&t;0001000
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;0002000
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;0004000
DECL|macro|CBAUDEX
mdefine_line|#define CBAUDEX 0010000
DECL|macro|B57600
mdefine_line|#define    B57600 0010001
DECL|macro|B115200
mdefine_line|#define   B115200 0010002
DECL|macro|B230400
mdefine_line|#define   B230400 0010003
DECL|macro|B460800
mdefine_line|#define   B460800 0010004
DECL|macro|B500000
mdefine_line|#define   B500000 0010005
DECL|macro|B576000
mdefine_line|#define   B576000 0010006
DECL|macro|B921600
mdefine_line|#define   B921600 0010007
DECL|macro|B1000000
mdefine_line|#define  B1000000 0010010
DECL|macro|B1152000
mdefine_line|#define  B1152000 0010011
DECL|macro|B1500000
mdefine_line|#define  B1500000 0010012
DECL|macro|B2000000
mdefine_line|#define  B2000000 0010013
DECL|macro|B2500000
mdefine_line|#define  B2500000 0010014
DECL|macro|B3000000
mdefine_line|#define  B3000000 0010015
DECL|macro|B3500000
mdefine_line|#define  B3500000 0010016
DECL|macro|B4000000
mdefine_line|#define  B4000000 0010017
DECL|macro|CIBAUD
mdefine_line|#define CIBAUD&t;  002003600000&t;/* input baud rate (not used) */
DECL|macro|CMSPAR
mdefine_line|#define CMSPAR&t;  010000000000&t;&t;/* mark or space (stick) parity */
DECL|macro|CRTSCTS
mdefine_line|#define CRTSCTS&t;  020000000000&t;&t;/* flow control */
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0000001
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0000002
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0000004
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0000010
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0000020
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0000040
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0000100
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0000200
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0000400
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0001000
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0002000
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0004000
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0010000
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0040000
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0100000
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
macro_line|#endif
eof
