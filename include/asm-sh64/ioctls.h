macro_line|#ifndef __ASM_SH64_IOCTLS_H
DECL|macro|__ASM_SH64_IOCTLS_H
mdefine_line|#define __ASM_SH64_IOCTLS_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/ioctls.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2004  Richard Curnow&n; *&n; */
macro_line|#include &lt;asm/ioctl.h&gt;
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;0x6601&t;&t;/* _IO(&squot;f&squot;, 1) */
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;0x6602&t;&t;/* _IO(&squot;f&squot;, 2) */
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;0x4004667d&t;/* _IOW(&squot;f&squot;, 125, int) */
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;0x4004667e&t;/* _IOW(&squot;f&squot;, 126, int) */
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;0x8004667f&t;/* _IOW(&squot;f&squot;, 127, int) */
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
DECL|macro|FIOQSIZE
mdefine_line|#define FIOQSIZE&t;0x80086680&t;/* _IOR(&squot;f&squot;, 128, loff_t) */
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;0x5401
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;0x5402
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;0x5403
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;0x5404
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;0x80127417&t;/* _IOR(&squot;t&squot;, 23, struct termio) */
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;0x40127418&t;/* _IOW(&squot;t&squot;, 24, struct termio) */
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;0x40127419&t;/* _IOW(&squot;t&squot;, 25, struct termio) */
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;0x4012741c&t;/* _IOW(&squot;t&squot;, 28, struct termio) */
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;0x741d&t;&t;/* _IO(&squot;t&squot;, 29) */
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;0x741e&t;&t;/* _IO(&squot;t&squot;, 30) */
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;0x741f&t;&t;/* _IO(&squot;t&squot;, 31) */
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;0x40087467&t;/* _IOW(&squot;t&squot;, 103, struct winsize) */
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;0x80087468&t;/* _IOR(&squot;t&squot;, 104, struct winsize) */
DECL|macro|TIOCSTART
mdefine_line|#define&t;TIOCSTART&t;0x746e&t;&t;/* _IO(&squot;t&squot;, 110)  start output, like ^Q */
DECL|macro|TIOCSTOP
mdefine_line|#define&t;TIOCSTOP&t;0x746f&t;&t;/* _IO(&squot;t&squot;, 111)  stop output, like ^S */
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ        0x80047473&t;/* _IOR(&squot;t&squot;, 115, int) output queue size */
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;0x40047476&t;/* _IOW(&squot;t&squot;, 118, int) */
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;0x80047477&t;/* _IOR(&squot;t&squot;, 119, int) */
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x540c&t;&t;/* _IO(&squot;T&squot;, 12) */
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x540d&t;&t;/* _IO(&squot;T&squot;, 13) */
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x540e&t;&t;/* _IO(&squot;T&squot;, 14) */
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x40015412&t;/* _IOW(&squot;T&squot;, 18, char) 0x5412 */
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;0x80045415&t;/* _IOR(&squot;T&squot;, 21, unsigned int) 0x5415 */
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;0x40045416&t;/* _IOW(&squot;T&squot;, 22, unsigned int) 0x5416 */
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;0x40045417&t;/* _IOW(&squot;T&squot;, 23, unsigned int) 0x5417 */
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;0x40045418&t;/* _IOW(&squot;T&squot;, 24, unsigned int) 0x5418 */
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
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;0x80045419&t;/* _IOR(&squot;T&squot;, 25, unsigned int) 0x5419 */
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;0x4004541a&t;/* _IOW(&squot;T&squot;, 26, unsigned int) 0x541A */
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x4004541c&t;/* _IOW(&squot;T&squot;, 28, char) 0x541C */
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;0x541d&t;&t;/* _IO(&squot;T&squot;, 29) */
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x803c541e&t;/* _IOR(&squot;T&squot;, 30, struct serial_struct) 0x541E */
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x403c541f&t;/* _IOW(&squot;T&squot;, 31, struct serial_struct) 0x541F */
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;0x40045420&t;/* _IOW(&squot;T&squot;, 32, int) 0x5420 */
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
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;0x5422&t;&t;/* _IO(&squot;T&squot;, 34) */
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;0x40045423&t;/* _IOW(&squot;T&squot;, 35, int) 0x5423 */
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;0x80045424&t;/* _IOR(&squot;T&squot;, 36, int) 0x5424 */
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x40045424&t;/* _IOW(&squot;T&squot;, 37, int) 0x5425 */&t;/* Needed for POSIX tcsendbreak() */
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x8c105426&t;/* _IOR(&squot;T&squot;, 38, struct tty_struct) 0x5426 */ /* For debugging only */
DECL|macro|TIOCSBRK
mdefine_line|#define TIOCSBRK&t;0x5427&t;&t;/* _IO(&squot;T&squot;, 39) */ /* BSD compatibility */
DECL|macro|TIOCCBRK
mdefine_line|#define TIOCCBRK&t;0x5428&t;&t;/* _IO(&squot;T&squot;, 40) */ /* BSD compatibility */
DECL|macro|TIOCGSID
mdefine_line|#define TIOCGSID&t;0x80045429&t;/* _IOR(&squot;T&squot;, 41, pid_t) 0x5429 */ /* Return the session ID of FD */
DECL|macro|TIOCGPTN
mdefine_line|#define TIOCGPTN&t;0x80045430&t;/* _IOR(&squot;T&squot;,0x30, unsigned int) 0x5430 Get Pty Number (of pty-mux device) */
DECL|macro|TIOCSPTLCK
mdefine_line|#define TIOCSPTLCK&t;0x40045431&t;/* _IOW(&squot;T&squot;,0x31, int) Lock/unlock Pty */
DECL|macro|TIOCSERCONFIG
mdefine_line|#define TIOCSERCONFIG&t;0x5453&t;&t;/* _IO(&squot;T&squot;, 83) */
DECL|macro|TIOCSERGWILD
mdefine_line|#define TIOCSERGWILD&t;0x80045454&t;/* _IOR(&squot;T&squot;, 84,  int) 0x5454 */
DECL|macro|TIOCSERSWILD
mdefine_line|#define TIOCSERSWILD&t;0x40045455&t;/* _IOW(&squot;T&squot;, 85,  int) 0x5455 */
DECL|macro|TIOCGLCKTRMIOS
mdefine_line|#define TIOCGLCKTRMIOS&t;0x5456
DECL|macro|TIOCSLCKTRMIOS
mdefine_line|#define TIOCSLCKTRMIOS&t;0x5457
DECL|macro|TIOCSERGSTRUCT
mdefine_line|#define TIOCSERGSTRUCT&t;0x80d85458&t;/* _IOR(&squot;T&squot;, 88, struct async_struct) 0x5458 */ /* For debugging only */
DECL|macro|TIOCSERGETLSR
mdefine_line|#define TIOCSERGETLSR   0x80045459&t;/* _IOR(&squot;T&squot;, 89, unsigned int) 0x5459 */ /* Get line status register */
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
DECL|macro|TIOCSERGETMULTI
mdefine_line|#define TIOCSERGETMULTI 0x80a8545a&t;/* _IOR(&squot;T&squot;, 90, struct serial_multiport_struct) 0x545A */ /* Get multiport config  */
DECL|macro|TIOCSERSETMULTI
mdefine_line|#define TIOCSERSETMULTI 0x40a8545b&t;/* _IOW(&squot;T&squot;, 91, struct serial_multiport_struct) 0x545B */ /* Set multiport config */
DECL|macro|TIOCMIWAIT
mdefine_line|#define TIOCMIWAIT&t;0x545c&t;&t;/* _IO(&squot;T&squot;, 92) wait for a change on serial input line(s) */
DECL|macro|TIOCGICOUNT
mdefine_line|#define TIOCGICOUNT&t;0x802c545d&t;/* _IOR(&squot;T&squot;, 93, struct async_icount) 0x545D */&t;/* read serial port inline interrupt counts */
macro_line|#endif /* __ASM_SH64_IOCTLS_H */
eof
