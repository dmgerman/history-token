multiline_comment|/*&n; * linux/drivers/char/ppdev.h&n; *&n; * User-space parallel port device driver (header file).&n; *&n; * Copyright (C) 1998-9 Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Added PPGETTIME/PPSETTIME, Fred Barnes, 1999&n; */
DECL|macro|PP_MAJOR
mdefine_line|#define PP_MAJOR&t;99
DECL|macro|PP_IOCTL
mdefine_line|#define PP_IOCTL&t;&squot;p&squot;
multiline_comment|/* Set mode for read/write (e.g. IEEE1284_MODE_EPP) */
DECL|macro|PPSETMODE
mdefine_line|#define PPSETMODE&t;_IOW(PP_IOCTL, 0x80, int)
multiline_comment|/* Read status */
DECL|macro|PPRSTATUS
mdefine_line|#define PPRSTATUS&t;_IOR(PP_IOCTL, 0x81, unsigned char)
DECL|macro|PPWSTATUS
mdefine_line|#define PPWSTATUS&t;OBSOLETE__IOW(PP_IOCTL, 0x82, unsigned char)
multiline_comment|/* Read/write control */
DECL|macro|PPRCONTROL
mdefine_line|#define PPRCONTROL&t;_IOR(PP_IOCTL, 0x83, unsigned char)
DECL|macro|PPWCONTROL
mdefine_line|#define PPWCONTROL&t;_IOW(PP_IOCTL, 0x84, unsigned char)
DECL|struct|ppdev_frob_struct
r_struct
id|ppdev_frob_struct
(brace
DECL|member|mask
r_int
r_char
id|mask
suffix:semicolon
DECL|member|val
r_int
r_char
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PPFCONTROL
mdefine_line|#define PPFCONTROL      _IOW(PP_IOCTL, 0x8e, struct ppdev_frob_struct)
multiline_comment|/* Read/write data */
DECL|macro|PPRDATA
mdefine_line|#define PPRDATA&t;&t;_IOR(PP_IOCTL, 0x85, unsigned char)
DECL|macro|PPWDATA
mdefine_line|#define PPWDATA&t;&t;_IOW(PP_IOCTL, 0x86, unsigned char)
multiline_comment|/* Read/write econtrol (not used) */
DECL|macro|PPRECONTROL
mdefine_line|#define PPRECONTROL&t;OBSOLETE__IOR(PP_IOCTL, 0x87, unsigned char)
DECL|macro|PPWECONTROL
mdefine_line|#define PPWECONTROL&t;OBSOLETE__IOW(PP_IOCTL, 0x88, unsigned char)
multiline_comment|/* Read/write FIFO (not used) */
DECL|macro|PPRFIFO
mdefine_line|#define PPRFIFO&t;&t;OBSOLETE__IOR(PP_IOCTL, 0x89, unsigned char)
DECL|macro|PPWFIFO
mdefine_line|#define PPWFIFO&t;&t;OBSOLETE__IOW(PP_IOCTL, 0x8a, unsigned char)
multiline_comment|/* Claim the port to start using it */
DECL|macro|PPCLAIM
mdefine_line|#define PPCLAIM&t;&t;_IO(PP_IOCTL, 0x8b)
multiline_comment|/* Release the port when you aren&squot;t using it */
DECL|macro|PPRELEASE
mdefine_line|#define PPRELEASE&t;_IO(PP_IOCTL, 0x8c)
multiline_comment|/* Yield the port (release it if another driver is waiting,&n; * then reclaim) */
DECL|macro|PPYIELD
mdefine_line|#define PPYIELD&t;&t;_IO(PP_IOCTL, 0x8d)
multiline_comment|/* Register device exclusively (must be before PPCLAIM). */
DECL|macro|PPEXCL
mdefine_line|#define PPEXCL&t;&t;_IO(PP_IOCTL, 0x8f)
multiline_comment|/* Data line direction: non-zero for input mode. */
DECL|macro|PPDATADIR
mdefine_line|#define PPDATADIR&t;_IOW(PP_IOCTL, 0x90, int)
multiline_comment|/* Negotiate a particular IEEE 1284 mode. */
DECL|macro|PPNEGOT
mdefine_line|#define PPNEGOT&t;&t;_IOW(PP_IOCTL, 0x91, int)
multiline_comment|/* Set control lines when an interrupt occurs. */
DECL|macro|PPWCTLONIRQ
mdefine_line|#define PPWCTLONIRQ&t;_IOW(PP_IOCTL, 0x92, unsigned char)
multiline_comment|/* Clear (and return) interrupt count. */
DECL|macro|PPCLRIRQ
mdefine_line|#define PPCLRIRQ&t;_IOR(PP_IOCTL, 0x93, int)
multiline_comment|/* Set the IEEE 1284 phase that we&squot;re in (e.g. IEEE1284_PH_FWD_IDLE) */
DECL|macro|PPSETPHASE
mdefine_line|#define PPSETPHASE&t;_IOW(PP_IOCTL, 0x94, int)
multiline_comment|/* Set and get port timeout (struct timeval&squot;s) */
DECL|macro|PPGETTIME
mdefine_line|#define PPGETTIME&t;_IOR(PP_IOCTL, 0x95, struct timeval)
DECL|macro|PPSETTIME
mdefine_line|#define PPSETTIME&t;_IOW(PP_IOCTL, 0x96, struct timeval)
eof
