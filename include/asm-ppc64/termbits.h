macro_line|#ifndef _PPC64_TERMBITS_H
DECL|macro|_PPC64_TERMBITS_H
mdefine_line|#define _PPC64_TERMBITS_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
multiline_comment|/*&n; * termios type and macro definitions.  Be careful about adding stuff&n; * to this file since it&squot;s used in GNU libc and there are strict rules&n; * concerning namespace pollution.&n; */
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
DECL|member|c_cc
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
DECL|member|c_line
id|cc_t
id|c_line
suffix:semicolon
multiline_comment|/* line discipline (== c_cc[19]) */
DECL|member|c_ispeed
id|speed_t
id|c_ispeed
suffix:semicolon
multiline_comment|/* input speed */
DECL|member|c_ospeed
id|speed_t
id|c_ospeed
suffix:semicolon
multiline_comment|/* output speed */
)brace
suffix:semicolon
multiline_comment|/* c_cc characters */
DECL|macro|VINTR
mdefine_line|#define VINTR &t;         0
DECL|macro|VQUIT
mdefine_line|#define VQUIT &t;         1
DECL|macro|VERASE
mdefine_line|#define VERASE &t;         2
DECL|macro|VKILL
mdefine_line|#define VKILL&t;         3
DECL|macro|VEOF
mdefine_line|#define VEOF&t;         4
DECL|macro|VMIN
mdefine_line|#define VMIN&t;         5
DECL|macro|VEOL
mdefine_line|#define VEOL&t;         6
DECL|macro|VTIME
mdefine_line|#define VTIME&t;         7
DECL|macro|VEOL2
mdefine_line|#define VEOL2&t;         8
DECL|macro|VSWTC
mdefine_line|#define VSWTC&t;         9
DECL|macro|VWERASE
mdefine_line|#define VWERASE &t;10
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT&t;11
DECL|macro|VSUSP
mdefine_line|#define VSUSP &t;&t;12
DECL|macro|VSTART
mdefine_line|#define VSTART&t;&t;13
DECL|macro|VSTOP
mdefine_line|#define VSTOP&t;&t;14
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT&t;&t;15
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD&t;16
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
DECL|macro|IXON
mdefine_line|#define IXON&t;0001000
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0002000
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0004000
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0010000
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0020000
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0000001
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0000002
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0000004
DECL|macro|OCRNL
mdefine_line|#define OCRNL&t;0000010
DECL|macro|ONOCR
mdefine_line|#define ONOCR&t;0000020
DECL|macro|ONLRET
mdefine_line|#define ONLRET&t;0000040
DECL|macro|OFILL
mdefine_line|#define OFILL&t;00000100
DECL|macro|OFDEL
mdefine_line|#define OFDEL&t;00000200
DECL|macro|NLDLY
mdefine_line|#define NLDLY&t;00001400
DECL|macro|NL0
mdefine_line|#define   NL0&t;00000000
DECL|macro|NL1
mdefine_line|#define   NL1&t;00000400
DECL|macro|NL2
mdefine_line|#define   NL2&t;00001000
DECL|macro|NL3
mdefine_line|#define   NL3&t;00001400
DECL|macro|TABDLY
mdefine_line|#define TABDLY&t;00006000
DECL|macro|TAB0
mdefine_line|#define   TAB0&t;00000000
DECL|macro|TAB1
mdefine_line|#define   TAB1&t;00002000
DECL|macro|TAB2
mdefine_line|#define   TAB2&t;00004000
DECL|macro|TAB3
mdefine_line|#define   TAB3&t;00006000
DECL|macro|CRDLY
mdefine_line|#define CRDLY&t;00030000
DECL|macro|CR0
mdefine_line|#define   CR0&t;00000000
DECL|macro|CR1
mdefine_line|#define   CR1&t;00010000
DECL|macro|CR2
mdefine_line|#define   CR2&t;00020000
DECL|macro|CR3
mdefine_line|#define   CR3&t;00030000
DECL|macro|FFDLY
mdefine_line|#define FFDLY&t;00040000
DECL|macro|FF0
mdefine_line|#define   FF0&t;00000000
DECL|macro|FF1
mdefine_line|#define   FF1&t;00040000
DECL|macro|BSDLY
mdefine_line|#define BSDLY&t;00100000
DECL|macro|BS0
mdefine_line|#define   BS0&t;00000000
DECL|macro|BS1
mdefine_line|#define   BS1&t;00100000
DECL|macro|VTDLY
mdefine_line|#define VTDLY&t;00200000
DECL|macro|VT0
mdefine_line|#define   VT0&t;00000000
DECL|macro|VT1
mdefine_line|#define   VT1&t;00200000
DECL|macro|XTABS
mdefine_line|#define XTABS&t;01000000 /* Hmm.. Linux/i386 considers this part of TABDLY.. */
multiline_comment|/* c_cflag bit meaning */
DECL|macro|CBAUD
mdefine_line|#define CBAUD&t;0000377
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
mdefine_line|#define  EXTA   B19200
DECL|macro|EXTB
mdefine_line|#define  EXTB   B38400
DECL|macro|CBAUDEX
mdefine_line|#define  CBAUDEX 0000000
DECL|macro|B57600
mdefine_line|#define  B57600   00020
DECL|macro|B115200
mdefine_line|#define  B115200  00021
DECL|macro|B230400
mdefine_line|#define  B230400  00022
DECL|macro|B460800
mdefine_line|#define  B460800  00023
DECL|macro|B500000
mdefine_line|#define  B500000  00024
DECL|macro|B576000
mdefine_line|#define  B576000  00025
DECL|macro|B921600
mdefine_line|#define  B921600  00026
DECL|macro|B1000000
mdefine_line|#define B1000000  00027
DECL|macro|B1152000
mdefine_line|#define B1152000  00030
DECL|macro|B1500000
mdefine_line|#define B1500000  00031
DECL|macro|B2000000
mdefine_line|#define B2000000  00032
DECL|macro|B2500000
mdefine_line|#define B2500000  00033
DECL|macro|B3000000
mdefine_line|#define B3000000  00034
DECL|macro|B3500000
mdefine_line|#define B3500000  00035
DECL|macro|B4000000
mdefine_line|#define B4000000  00036
DECL|macro|CSIZE
mdefine_line|#define CSIZE&t;00001400
DECL|macro|CS5
mdefine_line|#define   CS5&t;00000000
DECL|macro|CS6
mdefine_line|#define   CS6&t;00000400
DECL|macro|CS7
mdefine_line|#define   CS7&t;00001000
DECL|macro|CS8
mdefine_line|#define   CS8&t;00001400
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;00002000
DECL|macro|CREAD
mdefine_line|#define CREAD&t;00004000
DECL|macro|PARENB
mdefine_line|#define PARENB&t;00010000
DECL|macro|PARODD
mdefine_line|#define PARODD&t;00020000
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;00040000
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;00100000
DECL|macro|CRTSCTS
mdefine_line|#define CRTSCTS&t;  020000000000&t;&t;/* flow control */
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0x00000080
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0x00000100
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0x00004000
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0x00000008
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0x00000002
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0x00000004
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0x00000010
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0x80000000
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0x00400000
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0x00000040
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0x00000020
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0x00000001
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0x00800000
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0x20000000
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0x00000400
multiline_comment|/* Values for the ACTION argument to `tcflow&squot;.  */
DECL|macro|TCOOFF
mdefine_line|#define&t;TCOOFF&t;&t;0
DECL|macro|TCOON
mdefine_line|#define&t;TCOON&t;&t;1
DECL|macro|TCIOFF
mdefine_line|#define&t;TCIOFF&t;&t;2
DECL|macro|TCION
mdefine_line|#define&t;TCION&t;&t;3
multiline_comment|/* Values for the QUEUE_SELECTOR argument to `tcflush&squot;.  */
DECL|macro|TCIFLUSH
mdefine_line|#define&t;TCIFLUSH&t;0
DECL|macro|TCOFLUSH
mdefine_line|#define&t;TCOFLUSH&t;1
DECL|macro|TCIOFLUSH
mdefine_line|#define&t;TCIOFLUSH&t;2
multiline_comment|/* Values for the OPTIONAL_ACTIONS argument to `tcsetattr&squot;.  */
DECL|macro|TCSANOW
mdefine_line|#define&t;TCSANOW&t;&t;0
DECL|macro|TCSADRAIN
mdefine_line|#define&t;TCSADRAIN&t;1
DECL|macro|TCSAFLUSH
mdefine_line|#define&t;TCSAFLUSH&t;2
macro_line|#endif /* _PPC64_TERMBITS_H */
eof
