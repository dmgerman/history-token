macro_line|#ifndef __ARCH_X8664_IOCTLS_H__
DECL|macro|__ARCH_X8664_IOCTLS_H__
mdefine_line|#define __ARCH_X8664_IOCTLS_H__
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/* 0x54 is just a magic number to make these relatively unique (&squot;T&squot;) */
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;0x5401
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;0x5402
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;0x5403
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;0x5404
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;0x5405
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;0x5406
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;0x5407
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;0x5408
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;0x5409
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;0x540A
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;0x540B
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x540C
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x540D
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x540E
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;0x540F
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;0x5410
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ&t;0x5411
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x5412
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;0x5413
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;0x5414
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
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;0x541B
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
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
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;0x5421
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
DECL|macro|TIOCSBRK
mdefine_line|#define TIOCSBRK&t;0x5427  /* BSD compatibility */
DECL|macro|TIOCCBRK
mdefine_line|#define TIOCCBRK&t;0x5428  /* BSD compatibility */
DECL|macro|TIOCGSID
mdefine_line|#define TIOCGSID&t;0x5429  /* Return the session ID of FD */
DECL|macro|TIOCGPTN
mdefine_line|#define TIOCGPTN&t;_IOR(&squot;T&squot;,0x30, unsigned int) /* Get Pty Number (of pty-mux device) */
DECL|macro|TIOCSPTLCK
mdefine_line|#define TIOCSPTLCK&t;_IOW(&squot;T&squot;,0x31, int)  /* Lock/unlock Pty */
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;0x5450  /* these numbers need to be adjusted. */
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;0x5451
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;0x5452
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
DECL|macro|TIOCGHAYESESP
mdefine_line|#define TIOCGHAYESESP   0x545E  /* Get Hayes ESP configuration */
DECL|macro|TIOCSHAYESESP
mdefine_line|#define TIOCSHAYESESP   0x545F  /* Set Hayes ESP configuration */
DECL|macro|FIOQSIZE
mdefine_line|#define FIOQSIZE       0x5460
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
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
macro_line|#endif
eof
