multiline_comment|/* Hey EMACS -*- linux-c -*-&n; *&n; * tipar/tiser/tiusb - low level driver for handling link cables&n; * designed for Texas Instruments graphing calculators.&n; *&n; * Copyright (C) 2000-2002, Romain Lievin &lt;roms@lpg.ticalc.org&gt;&n; *&n; * Redistribution of this file is permitted under the terms of the GNU&n; * Public License (GPL)&n; */
macro_line|#ifndef _TICABLE_H 
DECL|macro|_TICABLE_H
mdefine_line|#define _TICABLE_H 1
multiline_comment|/* Internal default constants for the kernel module */
DECL|macro|TIMAXTIME
mdefine_line|#define TIMAXTIME 15      /* 1.5 seconds       */
DECL|macro|IO_DELAY
mdefine_line|#define IO_DELAY  10      /* 10 micro-seconds  */
multiline_comment|/* Major &amp; minor number for character devices */
DECL|macro|TIPAR_MAJOR
mdefine_line|#define TIPAR_MAJOR  115 /* 0 to 7 */
DECL|macro|TIPAR_MINOR
mdefine_line|#define TIPAR_MINOR    0
DECL|macro|TISER_MAJOR
mdefine_line|#define TISER_MAJOR  115 /* 8 to 15 */
DECL|macro|TISER_MINOR
mdefine_line|#define TISER_MINOR    8
DECL|macro|TIUSB_MAJOR
mdefine_line|#define TIUSB_MAJOR  115  /* 16 to 31 */
DECL|macro|TIUSB_MINOR
mdefine_line|#define TIUSB_MINOR   16
multiline_comment|/*&n; * Request values for the &squot;ioctl&squot; function.&n; */
DECL|macro|IOCTL_TIPAR_DELAY
mdefine_line|#define IOCTL_TIPAR_DELAY     _IOW(&squot;p&squot;, 0xa8, int) /* set delay   */
DECL|macro|IOCTL_TIPAR_TIMEOUT
mdefine_line|#define IOCTL_TIPAR_TIMEOUT   _IOW(&squot;p&squot;, 0xa9, int) /* set timeout */
DECL|macro|IOCTL_TISER_DELAY
mdefine_line|#define IOCTL_TISER_DELAY     _IOW(&squot;p&squot;, 0xa0, int) /* set delay   */
DECL|macro|IOCTL_TISER_TIMEOUT
mdefine_line|#define IOCTL_TISER_TIMEOUT   _IOW(&squot;p&squot;, 0xa1, int) /* set timeout */
DECL|macro|IOCTL_TIUSB_TIMEOUT
mdefine_line|#define IOCTL_TIUSB_TIMEOUT        _IOW(&squot;N&squot;, 0x20, int) /* set timeout */
DECL|macro|IOCTL_TIUSB_RESET_DEVICE
mdefine_line|#define IOCTL_TIUSB_RESET_DEVICE   _IOW(&squot;N&squot;, 0x21, int) /* reset device */
DECL|macro|IOCTL_TIUSB_RESET_PIPES
mdefine_line|#define IOCTL_TIUSB_RESET_PIPES    _IOW(&squot;N&squot;, 0x22, int) /* reset both pipes*/
macro_line|#endif /* TICABLE_H */
eof
