multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1999, 2001 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_TERMBITS_H
DECL|macro|_ASM_TERMBITS_H
mdefine_line|#define _ASM_TERMBITS_H
macro_line|#include &lt;linux/posix_types.h&gt;
DECL|typedef|cc_t
r_typedef
r_int
r_char
id|cc_t
suffix:semicolon
macro_line|#if (_MIPS_SZLONG == 32)
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
macro_line|#endif
macro_line|#if (_MIPS_SZLONG == 64)
DECL|typedef|speed_t
r_typedef
id|__u32
id|speed_t
suffix:semicolon
DECL|typedef|tcflag_t
r_typedef
id|__u32
id|tcflag_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The ABI says nothing about NCC but seems to use NCCS as&n; * replacement for it in struct termio&n; */
DECL|macro|NCCS
mdefine_line|#define NCCS&t;23
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
mdefine_line|#define VINTR&t;&t; 0&t;&t;/* Interrupt character [ISIG].  */
DECL|macro|VQUIT
mdefine_line|#define VQUIT&t;&t; 1&t;&t;/* Quit character [ISIG].  */
DECL|macro|VERASE
mdefine_line|#define VERASE&t;&t; 2&t;&t;/* Erase character [ICANON].  */
DECL|macro|VKILL
mdefine_line|#define VKILL&t;&t; 3&t;&t;/* Kill-line character [ICANON].  */
DECL|macro|VMIN
mdefine_line|#define VMIN&t;&t; 4&t;&t;/* Minimum number of bytes read at once [!ICANON].  */
DECL|macro|VTIME
mdefine_line|#define VTIME&t;&t; 5&t;&t;/* Time-out value (tenths of a second) [!ICANON].  */
DECL|macro|VEOL2
mdefine_line|#define VEOL2&t;&t; 6&t;&t;/* Second EOL character [ICANON].  */
DECL|macro|VSWTC
mdefine_line|#define VSWTC&t;&t; 7&t;&t;/* ??? */
DECL|macro|VSWTCH
mdefine_line|#define VSWTCH&t;&t;VSWTC
DECL|macro|VSTART
mdefine_line|#define VSTART&t;&t; 8&t;&t;/* Start (X-ON) character [IXON, IXOFF].  */
DECL|macro|VSTOP
mdefine_line|#define VSTOP&t;&t; 9&t;&t;/* Stop (X-OFF) character [IXON, IXOFF].  */
DECL|macro|VSUSP
mdefine_line|#define VSUSP&t;&t;10&t;&t;/* Suspend character [ISIG].  */
macro_line|#if 0
multiline_comment|/*&n; * VDSUSP is not supported&n; */
mdefine_line|#define VDSUSP&t;&t;11&t;&t;/* Delayed suspend character [ISIG].  */
macro_line|#endif
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT&t;12&t;&t;/* Reprint-line character [ICANON].  */
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD&t;13&t;&t;/* Discard character [IEXTEN].  */
DECL|macro|VWERASE
mdefine_line|#define VWERASE&t;&t;14&t;&t;/* Word-erase character [ICANON].  */
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT&t;&t;15&t;&t;/* Literal-next character [IEXTEN].  */
DECL|macro|VEOF
mdefine_line|#define VEOF&t;&t;16&t;&t;/* End-of-file character [ICANON].  */
DECL|macro|VEOL
mdefine_line|#define VEOL&t;&t;17&t;&t;/* End-of-line character [ICANON].  */
multiline_comment|/* c_iflag bits */
DECL|macro|IGNBRK
mdefine_line|#define IGNBRK&t;0000001&t;&t;/* Ignore break condition.  */
DECL|macro|BRKINT
mdefine_line|#define BRKINT&t;0000002&t;&t;/* Signal interrupt on break.  */
DECL|macro|IGNPAR
mdefine_line|#define IGNPAR&t;0000004&t;&t;/* Ignore characters with parity errors.  */
DECL|macro|PARMRK
mdefine_line|#define PARMRK&t;0000010&t;&t;/* Mark parity and framing errors.  */
DECL|macro|INPCK
mdefine_line|#define INPCK&t;0000020&t;&t;/* Enable input parity check.  */
DECL|macro|ISTRIP
mdefine_line|#define ISTRIP&t;0000040&t;&t;/* Strip 8th bit off characters.  */
DECL|macro|INLCR
mdefine_line|#define INLCR&t;0000100&t;&t;/* Map NL to CR on input.  */
DECL|macro|IGNCR
mdefine_line|#define IGNCR&t;0000200&t;&t;/* Ignore CR.  */
DECL|macro|ICRNL
mdefine_line|#define ICRNL&t;0000400&t;&t;/* Map CR to NL on input.  */
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0001000&t;&t;/* Map upper case to lower case on input.  */
DECL|macro|IXON
mdefine_line|#define IXON&t;0002000&t;&t;/* Enable start/stop output control.  */
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0004000&t;&t;/* Any character will restart after stop.  */
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0010000&t;&t;/* Enable start/stop input control.  */
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0020000&t;&t;/* Ring bell when input queue is full.  */
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0000001&t;&t;/* Perform output processing.  */
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0000002&t;&t;/* Map lower case to upper case on output.  */
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0000004&t;&t;/* Map NL to CR-NL on output.  */
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
multiline_comment|/*&n;#define PAGEOUT ???&n;#define WRAP    ???&n; */
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
mdefine_line|#define CSIZE&t;0000060&t;&t;/* Number of bits per byte (mask).  */
DECL|macro|CS5
mdefine_line|#define   CS5&t;0000000&t;&t;/* 5 bits per byte.  */
DECL|macro|CS6
mdefine_line|#define   CS6&t;0000020&t;&t;/* 6 bits per byte.  */
DECL|macro|CS7
mdefine_line|#define   CS7&t;0000040&t;&t;/* 7 bits per byte.  */
DECL|macro|CS8
mdefine_line|#define   CS8&t;0000060&t;&t;/* 8 bits per byte.  */
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;0000100&t;&t;/* Two stop bits instead of one.  */
DECL|macro|CREAD
mdefine_line|#define CREAD&t;0000200&t;&t;/* Enable receiver.  */
DECL|macro|PARENB
mdefine_line|#define PARENB&t;0000400&t;&t;/* Parity enable.  */
DECL|macro|PARODD
mdefine_line|#define PARODD&t;0001000&t;&t;/* Odd parity instead of even.  */
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;0002000&t;&t;/* Hang up on last close.  */
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;0004000&t;&t;/* Ignore modem status lines.  */
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
mdefine_line|#define CMSPAR    010000000000&t;/* mark or space (stick) parity */
DECL|macro|CRTSCTS
mdefine_line|#define CRTSCTS&t;  020000000000&t;&t;/* flow control */
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0000001&t;&t;/* Enable signals.  */
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0000002&t;&t;/* Do erase and kill processing.  */
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0000004
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0000010&t;&t;/* Enable echo.  */
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0000020&t;&t;/* Visual erase for ERASE.  */
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0000040&t;&t;/* Echo NL after KILL.  */
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0000100&t;&t;/* Echo NL even if ECHO is off.  */
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0000200&t;&t;/* Disable flush after interrupt.  */
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0000400&t;&t;/* Enable DISCARD and LNEXT.  */
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0001000&t;&t;/* Echo control characters as ^X.  */
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0002000&t;&t;/* Hardcopy visual erase.  */
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0004000&t;&t;/* Visual erase for KILL.  */
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0020000
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0040000&t;&t;/* Retype pending input (state).  */
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0100000&t;&t;/* Send SIGTTOU for background output.  */
DECL|macro|ITOSTOP
mdefine_line|#define ITOSTOP&t;TOSTOP
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
multiline_comment|/* tcflow() and TCXONC use these */
DECL|macro|TCOOFF
mdefine_line|#define&t;TCOOFF&t;&t;0&t;/* Suspend output.  */
DECL|macro|TCOON
mdefine_line|#define&t;TCOON&t;&t;1&t;/* Restart suspended output.  */
DECL|macro|TCIOFF
mdefine_line|#define&t;TCIOFF&t;&t;2&t;/* Send a STOP character.  */
DECL|macro|TCION
mdefine_line|#define&t;TCION&t;&t;3&t;/* Send a START character.  */
multiline_comment|/* tcflush() and TCFLSH use these */
DECL|macro|TCIFLUSH
mdefine_line|#define&t;TCIFLUSH&t;0&t;/* Discard data received but not yet read.  */
DECL|macro|TCOFLUSH
mdefine_line|#define&t;TCOFLUSH&t;1&t;/* Discard data written but not yet sent.  */
DECL|macro|TCIOFLUSH
mdefine_line|#define&t;TCIOFLUSH&t;2&t;/* Discard all pending data.  */
multiline_comment|/* tcsetattr uses these */
DECL|macro|TCSANOW
mdefine_line|#define&t;TCSANOW&t;&t;TCSETS&t;/* Change immediately.  */
DECL|macro|TCSADRAIN
mdefine_line|#define&t;TCSADRAIN&t;TCSETSW&t;/* Change when pending output is written.  */
DECL|macro|TCSAFLUSH
mdefine_line|#define&t;TCSAFLUSH&t;TCSETSF&t;/* Flush pending input before changing.  */
macro_line|#endif /* _ASM_TERMBITS_H */
eof
