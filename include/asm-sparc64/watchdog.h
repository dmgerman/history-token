multiline_comment|/* $Id: watchdog.h,v 1.1 2001/01/18 04:47:44 davem Exp $&n; *&n; * watchdog - Driver interface for the hardware watchdog timers&n; * present on Sun Microsystems boardsets&n; *&n; * Copyright (c) 2000 Eric Brower &lt;ebrower@usa.net&gt;&n; *&n; */
macro_line|#ifndef _SPARC64_WATCHDOG_H
DECL|macro|_SPARC64_WATCHDOG_H
mdefine_line|#define _SPARC64_WATCHDOG_H
macro_line|#include &lt;linux/watchdog.h&gt;
multiline_comment|/* Solaris compatibility ioctls--&n; * Ref. &lt;linux/watchdog.h&gt; for standard linux watchdog ioctls&n; */
DECL|macro|WIOCSTART
mdefine_line|#define WIOCSTART _IO (WATCHDOG_IOCTL_BASE, 10)&t;&t;/* Start Timer&t;&t;*/
DECL|macro|WIOCSTOP
mdefine_line|#define WIOCSTOP  _IO (WATCHDOG_IOCTL_BASE, 11)&t;&t;/* Stop Timer&t;&t;*/
DECL|macro|WIOCGSTAT
mdefine_line|#define WIOCGSTAT _IOR(WATCHDOG_IOCTL_BASE, 12, int)/* Get Timer Status&t;*/
multiline_comment|/* Status flags from WIOCGSTAT ioctl&n; */
DECL|macro|WD_FREERUN
mdefine_line|#define WD_FREERUN&t;0x01&t;/* timer is running, interrupts disabled&t;*/
DECL|macro|WD_EXPIRED
mdefine_line|#define WD_EXPIRED&t;0x02&t;/* timer has expired&t;&t;&t;&t;&t;&t;*/
DECL|macro|WD_RUNNING
mdefine_line|#define WD_RUNNING&t;0x04&t;/* timer is running, interrupts enabled&t;&t;*/
DECL|macro|WD_STOPPED
mdefine_line|#define WD_STOPPED&t;0x08&t;/* timer has not been started&t;&t;&t;&t;*/
DECL|macro|WD_SERVICED
mdefine_line|#define WD_SERVICED 0x10&t;/* timer interrupt was serviced&t;&t;&t;&t;*/
macro_line|#endif /* ifndef _SPARC64_WATCHDOG_H */
eof
