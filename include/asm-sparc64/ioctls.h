multiline_comment|/* $Id: ioctls.h,v 1.7 1998/02/23 02:49:41 davem Exp $ */
macro_line|#ifndef _ASM_SPARC64_IOCTLS_H
DECL|macro|_ASM_SPARC64_IOCTLS_H
mdefine_line|#define _ASM_SPARC64_IOCTLS_H
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/* Big T */
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;_IOR(&squot;T&squot;, 1, struct termio)
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;_IOW(&squot;T&squot;, 2, struct termio)
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;_IOW(&squot;T&squot;, 3, struct termio)
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;_IOW(&squot;T&squot;, 4, struct termio)
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;_IO(&squot;T&squot;, 5)
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;_IO(&squot;T&squot;, 6)
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;_IO(&squot;T&squot;, 7)
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;_IOR(&squot;T&squot;, 8, struct termios)
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;_IOW(&squot;T&squot;, 9, struct termios)
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;_IOW(&squot;T&squot;, 10, struct termios)
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;_IOW(&squot;T&squot;, 11, struct termios)
multiline_comment|/* Note that all the ioctls that are not available in Linux have a &n; * double underscore on the front to: a) avoid some programs to&n; * think we support some ioctls under Linux (autoconfiguration stuff)&n; */
multiline_comment|/* Little t */
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;_IOR(&squot;t&squot;, 0, int)
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;_IOW(&squot;t&squot;, 1, int)
DECL|macro|__TIOCHPCL
mdefine_line|#define __TIOCHPCL        _IO(&squot;t&squot;, 2) /* SunOS Specific */
DECL|macro|__TIOCMODG
mdefine_line|#define __TIOCMODG        _IOR(&squot;t&squot;, 3, int) /* SunOS Specific */
DECL|macro|__TIOCMODS
mdefine_line|#define __TIOCMODS        _IOW(&squot;t&squot;, 4, int) /* SunOS Specific */
DECL|macro|__TIOCGETP
mdefine_line|#define __TIOCGETP        _IOR(&squot;t&squot;, 8, struct sgttyb) /* SunOS Specific */
DECL|macro|__TIOCSETP
mdefine_line|#define __TIOCSETP        _IOW(&squot;t&squot;, 9, struct sgttyb) /* SunOS Specific */
DECL|macro|__TIOCSETN
mdefine_line|#define __TIOCSETN        _IOW(&squot;t&squot;, 10, struct sgttyb) /* SunOS Specific */
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;_IO(&squot;t&squot;, 13)
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;_IO(&squot;t&squot;, 14)
DECL|macro|__TIOCFLUSH
mdefine_line|#define __TIOCFLUSH       _IOW(&squot;t&squot;, 16, int) /* SunOS Specific */
DECL|macro|__TIOCSETC
mdefine_line|#define __TIOCSETC        _IOW(&squot;t&squot;, 17, struct tchars) /* SunOS Specific */
DECL|macro|__TIOCGETC
mdefine_line|#define __TIOCGETC        _IOR(&squot;t&squot;, 18, struct tchars) /* SunOS Specific */
DECL|macro|__TIOCTCNTL
mdefine_line|#define __TIOCTCNTL       _IOW(&squot;t&squot;, 32, int) /* SunOS Specific */
DECL|macro|__TIOCSIGNAL
mdefine_line|#define __TIOCSIGNAL      _IOW(&squot;t&squot;, 33, int) /* SunOS Specific */
DECL|macro|__TIOCSETX
mdefine_line|#define __TIOCSETX        _IOW(&squot;t&squot;, 34, int) /* SunOS Specific */
DECL|macro|__TIOCGETX
mdefine_line|#define __TIOCGETX        _IOR(&squot;t&squot;, 35, int) /* SunOS Specific */
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;_IO(&squot;t&squot;, 36)
DECL|macro|__TIOCSSIZE
mdefine_line|#define __TIOCSSIZE     _IOW(&squot;t&squot;, 37, struct sunos_ttysize) /* SunOS Specific */
DECL|macro|__TIOCGSIZE
mdefine_line|#define __TIOCGSIZE     _IOR(&squot;t&squot;, 38, struct sunos_ttysize) /* SunOS Specific */
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;_IOR(&squot;t&squot;, 100, int)
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;_IOW(&squot;t&squot;, 101, int)
DECL|macro|__TIOCUCNTL
mdefine_line|#define __TIOCUCNTL       _IOW(&squot;t&squot;, 102, int) /* SunOS Specific */
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;_IOW(&squot;t&squot;, 103, struct winsize)
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;_IOR(&squot;t&squot;, 104, struct winsize)
DECL|macro|__TIOCREMOTE
mdefine_line|#define __TIOCREMOTE      _IOW(&squot;t&squot;, 105, int) /* SunOS Specific */
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;_IOR(&squot;t&squot;, 106, int)
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;_IOW(&squot;t&squot;, 107, int)
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;_IOW(&squot;t&squot;, 108, int)
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;_IOW(&squot;t&squot;, 109, int)
DECL|macro|TIOCSTART
mdefine_line|#define TIOCSTART       _IO(&squot;t&squot;, 110)
DECL|macro|TIOCSTOP
mdefine_line|#define TIOCSTOP        _IO(&squot;t&squot;, 111)
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;_IOW(&squot;t&squot;, 112, int)
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;_IO(&squot;t&squot;, 113)
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;_IOW(&squot;t&squot;, 114, char)
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ&t;_IOR(&squot;t&squot;, 115, int)
DECL|macro|__TIOCGLTC
mdefine_line|#define __TIOCGLTC        _IOR(&squot;t&squot;, 116, struct ltchars) /* SunOS Specific */
DECL|macro|__TIOCSLTC
mdefine_line|#define __TIOCSLTC        _IOW(&squot;t&squot;, 117, struct ltchars) /* SunOS Specific */
multiline_comment|/* 118 is the non-posix setpgrp tty ioctl */
multiline_comment|/* 119 is the non-posix getpgrp tty ioctl */
DECL|macro|__TIOCCDTR
mdefine_line|#define __TIOCCDTR        _IO(&squot;t&squot;, 120) /* SunOS Specific */
DECL|macro|__TIOCSDTR
mdefine_line|#define __TIOCSDTR        _IO(&squot;t&squot;, 121) /* SunOS Specific */
DECL|macro|TIOCCBRK
mdefine_line|#define TIOCCBRK        _IO(&squot;t&squot;, 122)
DECL|macro|TIOCSBRK
mdefine_line|#define TIOCSBRK        _IO(&squot;t&squot;, 123)
DECL|macro|__TIOCLGET
mdefine_line|#define __TIOCLGET        _IOW(&squot;t&squot;, 124, int) /* SunOS Specific */
DECL|macro|__TIOCLSET
mdefine_line|#define __TIOCLSET        _IOW(&squot;t&squot;, 125, int) /* SunOS Specific */
DECL|macro|__TIOCLBIC
mdefine_line|#define __TIOCLBIC        _IOW(&squot;t&squot;, 126, int) /* SunOS Specific */
DECL|macro|__TIOCLBIS
mdefine_line|#define __TIOCLBIS        _IOW(&squot;t&squot;, 127, int) /* SunOS Specific */
DECL|macro|__TIOCISPACE
mdefine_line|#define __TIOCISPACE      _IOR(&squot;t&squot;, 128, int) /* SunOS Specific */
DECL|macro|__TIOCISIZE
mdefine_line|#define __TIOCISIZE       _IOR(&squot;t&squot;, 129, int) /* SunOS Specific */
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;_IOW(&squot;t&squot;, 130, int)
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;_IOR(&squot;t&squot;, 131, int)
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;_IO(&squot;t&squot;, 132)
DECL|macro|TIOCGSID
mdefine_line|#define TIOCGSID&t;_IOR(&squot;t&squot;, 133, int)
multiline_comment|/* Get minor device of a pty master&squot;s FD -- Solaris equiv is ISPTM */
DECL|macro|TIOCGPTN
mdefine_line|#define TIOCGPTN&t;_IOR(&squot;t&squot;, 134, unsigned int) /* Get Pty Number */
DECL|macro|TIOCSPTLCK
mdefine_line|#define TIOCSPTLCK&t;_IOW(&squot;t&squot;, 135, int) /* Lock/unlock PTY */
multiline_comment|/* Little f */
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
multiline_comment|/* SCARY Rutgers local SunOS kernel hackery, perhaps I will support it&n; * someday.  This is completely bogus, I know...&n; */
DECL|macro|__TCGETSTAT
mdefine_line|#define __TCGETSTAT       _IO(&squot;T&squot;, 200) /* Rutgers specific */
DECL|macro|__TCSETSTAT
mdefine_line|#define __TCSETSTAT       _IO(&squot;T&squot;, 201) /* Rutgers specific */
multiline_comment|/* Linux specific, no SunOS equivalent. */
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x541C
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x541E
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x541F
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x5425
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x5426
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
mdefine_line|#define TIOCMIWAIT&t;0x545C /* Wait for change on serial input line(s) */
DECL|macro|TIOCGICOUNT
mdefine_line|#define TIOCGICOUNT&t;0x545D /* Read serial port inline interrupt counts */
multiline_comment|/* Kernel definitions */
macro_line|#ifdef __KERNEL__
DECL|macro|TIOCGETC
mdefine_line|#define TIOCGETC __TIOCGETC
DECL|macro|TIOCGETP
mdefine_line|#define TIOCGETP __TIOCGETP
DECL|macro|TIOCGLTC
mdefine_line|#define TIOCGLTC __TIOCGLTC
DECL|macro|TIOCSLTC
mdefine_line|#define TIOCSLTC __TIOCSLTC
DECL|macro|TIOCSETP
mdefine_line|#define TIOCSETP __TIOCSETP
DECL|macro|TIOCSETN
mdefine_line|#define TIOCSETN __TIOCSETN
DECL|macro|TIOCSETC
mdefine_line|#define TIOCSETC __TIOCSETC
macro_line|#endif
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
macro_line|#endif /* !(_ASM_SPARC64_IOCTLS_H) */
eof
