multiline_comment|/* $Id: ioctls.h,v 1.5 1998/08/19 21:58:11 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_IOCTLS_H
DECL|macro|__ASM_MIPS_IOCTLS_H
mdefine_line|#define __ASM_MIPS_IOCTLS_H
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#if defined(__USE_MISC) || defined (__KERNEL__)
DECL|macro|tIOC
mdefine_line|#define tIOC&t;&t;(&squot;t&squot; &lt;&lt; 8)
macro_line|#endif
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;0x5401
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;0x5402
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;0x5403
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;0x5404
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;0x5405
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;0x5406
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;0x5407
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;0x540d
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;0x540e
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;0x540f
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;0x5410
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x740d&t;&t;/* set exclusive use of tty */
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x740e&t;&t;/* reset exclusive use of tty */
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ&t;0x7472&t;&t;/* output queue size */
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x5472&t;&t;/* simulate terminal input */
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;0x741d&t;&t;/* get all modem bits */
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;0x741b&t;&t;/* bis modem bits */
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;0x741c&t;&t;/* bic modem bits */
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;0x741a&t;&t;/* set all modem bits */
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;0x5470&t;&t;/* pty: set/clear packet mode */
DECL|macro|TIOCPKT_DATA
mdefine_line|#define&t;&t;TIOCPKT_DATA&t;&t;0x00&t;/* data packet */
DECL|macro|TIOCPKT_FLUSHREAD
mdefine_line|#define&t;&t;TIOCPKT_FLUSHREAD&t;0x01&t;/* flush packet */
DECL|macro|TIOCPKT_FLUSHWRITE
mdefine_line|#define&t;&t;TIOCPKT_FLUSHWRITE&t;0x02&t;/* flush packet */
DECL|macro|TIOCPKT_STOP
mdefine_line|#define&t;&t;TIOCPKT_STOP&t;&t;0x04&t;/* stop output */
DECL|macro|TIOCPKT_START
mdefine_line|#define&t;&t;TIOCPKT_START&t;&t;0x08&t;/* start output */
DECL|macro|TIOCPKT_NOSTOP
mdefine_line|#define&t;&t;TIOCPKT_NOSTOP&t;&t;0x10&t;/* no more ^S, ^Q */
DECL|macro|TIOCPKT_DOSTOP
mdefine_line|#define&t;&t;TIOCPKT_DOSTOP&t;&t;0x20&t;/* now do ^S ^Q */
macro_line|#if 0
mdefine_line|#define&t;&t;TIOCPKT_IOCTL&t;&t;0x40&t;/* state change of pty driver */
macro_line|#endif
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;_IOW(&squot;t&squot;, 103, struct winsize)&t;/* set window size */
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;_IOR(&squot;t&squot;, 104, struct winsize)&t;/* get window size */
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;0x5471&t;&t;/* void tty association */
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;(tIOC | 1)
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;(tIOC | 0)
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;0x6601
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;0x6602&t;&t;/* these numbers need to be adjusted. */
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;0x667d
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;0x667e
DECL|macro|FIOQSIZE
mdefine_line|#define FIOQSIZE&t;0x667f
macro_line|#if defined(__USE_MISC) || defined (__KERNEL__)
DECL|macro|TIOCGLTC
mdefine_line|#define TIOCGLTC&t;(tIOC | 116)&t;&t;/* get special local chars */
DECL|macro|TIOCSLTC
mdefine_line|#define TIOCSLTC&t;(tIOC | 117)&t;&t;/* set special local chars */
macro_line|#endif
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;_IOW(&squot;t&squot;, 118, int)&t;/* set pgrp of tty */
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;_IOR(&squot;t&squot;, 119, int)&t;/* get pgrp of tty */
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;_IOW(&squot;t&squot;, 120, int)&t;/* become virtual console */
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;0x467f
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
macro_line|#if defined(__USE_MISC) || defined (__KERNEL__)
DECL|macro|TIOCGETP
mdefine_line|#define TIOCGETP        (tIOC | 8)
DECL|macro|TIOCSETP
mdefine_line|#define TIOCSETP        (tIOC | 9)
DECL|macro|TIOCSETN
mdefine_line|#define TIOCSETN        (tIOC | 10)&t;&t;/* TIOCSETP wo flush */
macro_line|#endif
macro_line|#if 0
mdefine_line|#define&t;TIOCSETA&t;_IOW(&squot;t&squot;, 20, struct termios) /* set termios struct */
mdefine_line|#define&t;TIOCSETAW&t;_IOW(&squot;t&squot;, 21, struct termios) /* drain output, set */
mdefine_line|#define&t;TIOCSETAF&t;_IOW(&squot;t&squot;, 22, struct termios) /* drn out, fls in, set */
mdefine_line|#define&t;TIOCGETD&t;_IOR(&squot;t&squot;, 26, int)&t;/* get line discipline */
mdefine_line|#define&t;TIOCSETD&t;_IOW(&squot;t&squot;, 27, int)&t;/* set line discipline */
multiline_comment|/* 127-124 compat */
macro_line|#endif
multiline_comment|/* I hope the range from 0x5480 on is free ... */
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x5480&t;&t;/* become controlling tty */
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;0x5481
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;0x5482
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x5483
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x5484
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x5485
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x5486&t;/* Needed for POSIX tcsendbreak() */
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x5487  /* For debugging only */
DECL|macro|TIOCSBRK
mdefine_line|#define TIOCSBRK&t;0x5427  /* BSD compatibility */
DECL|macro|TIOCCBRK
mdefine_line|#define TIOCCBRK&t;0x5428  /* BSD compatibility */
DECL|macro|TIOCGSID
mdefine_line|#define TIOCGSID&t;0x7416  /* Return the session ID of FD */
DECL|macro|TIOCGPTN
mdefine_line|#define TIOCGPTN&t;_IOR(&squot;T&squot;,0x30, unsigned int) /* Get Pty Number (of pty-mux device) */
DECL|macro|TIOCSPTLCK
mdefine_line|#define TIOCSPTLCK&t;_IOW(&squot;T&squot;,0x31, int)  /* Lock/unlock Pty */
DECL|macro|TIOCSERCONFIG
mdefine_line|#define TIOCSERCONFIG&t;0x5488
DECL|macro|TIOCSERGWILD
mdefine_line|#define TIOCSERGWILD&t;0x5489
DECL|macro|TIOCSERSWILD
mdefine_line|#define TIOCSERSWILD&t;0x548a
DECL|macro|TIOCGLCKTRMIOS
mdefine_line|#define TIOCGLCKTRMIOS&t;0x548b
DECL|macro|TIOCSLCKTRMIOS
mdefine_line|#define TIOCSLCKTRMIOS&t;0x548c
DECL|macro|TIOCSERGSTRUCT
mdefine_line|#define TIOCSERGSTRUCT&t;0x548d /* For debugging only */
DECL|macro|TIOCSERGETLSR
mdefine_line|#define TIOCSERGETLSR   0x548e /* Get line status register */
DECL|macro|TIOCSERGETMULTI
mdefine_line|#define TIOCSERGETMULTI 0x548f /* Get multiport config  */
DECL|macro|TIOCSERSETMULTI
mdefine_line|#define TIOCSERSETMULTI 0x5490 /* Set multiport config */
DECL|macro|TIOCMIWAIT
mdefine_line|#define TIOCMIWAIT      0x5491 /* wait for a change on serial input line(s) */
DECL|macro|TIOCGICOUNT
mdefine_line|#define TIOCGICOUNT     0x5492 /* read serial port inline interrupt counts */
DECL|macro|TIOCGHAYESESP
mdefine_line|#define TIOCGHAYESESP&t;0x5493 /* Get Hayes ESP configuration */
DECL|macro|TIOCSHAYESESP
mdefine_line|#define TIOCSHAYESESP&t;0x5494 /* Set Hayes ESP configuration */
macro_line|#endif /* __ASM_MIPS_IOCTLS_H */
eof
