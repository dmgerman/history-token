multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001 Silicon Graphics, Inc. All rights reserved.&n; *&n; * SGI Hi Resolution Clock&n; *&n; * SGI SN platforms provide a high resolution clock that is&n; * synchronized across all nodes. The clock can be memory mapped&n; * and directly read from user space.&n; *&n; * Access to the clock is thru the following:&n; *       (error checking not shown)&n; *&n; * (Note: should library routines be provided to encapsulate this??)&n; *&n; *&t;int&t;&t;fd:&n; *&t;volatile long&t;*clk;&n; *&n; *&t;fd = open (HIRES_FULLNAME, O_RDONLY);&n; *&t;clk = mmap(0, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);&n; *&t;clk += ioctl(fd, HIRES_IOCQGETOFFSET, 0);&n; *&n; * At this point, clk is a pointer to the high resolution clock.&n; *&n; * The clock period can be obtained via:&n; *&n; *&t;long&t;picosec_per_tick;&n; *&t;picosec_per_tick = ioctl(fd, HIRES_IOCQGETPICOSEC, 0);&n; */
macro_line|#ifndef _ASM_IA64_SN_HIRES_CLOCK_H
DECL|macro|_ASM_IA64_SN_HIRES_CLOCK_H
mdefine_line|#define _ASM_IA64_SN_HIRES_CLOCK_H
DECL|macro|HIRES_BASENAME
mdefine_line|#define HIRES_BASENAME&t;&quot;sgi_hires_clock&quot;
DECL|macro|HIRES_FULLNAME
mdefine_line|#define HIRES_FULLNAME  &quot;/dev/sgi_hires_clock&quot;
DECL|macro|HIRES_IOC_BASE
mdefine_line|#define HIRES_IOC_BASE&t;&squot;s&squot;
multiline_comment|/* Get page offset of hires timer */
DECL|macro|HIRES_IOCQGETOFFSET
mdefine_line|#define HIRES_IOCQGETOFFSET&t;_IO( HIRES_IOC_BASE, 0 )
multiline_comment|/* get clock period in picoseconds per tick */
DECL|macro|HIRES_IOCQGETPICOSEC
mdefine_line|#define HIRES_IOCQGETPICOSEC&t;_IO( HIRES_IOC_BASE, 1 )
multiline_comment|/* get number of significant bits in clock counter */
DECL|macro|HIRES_IOCQGETCLOCKBITS
mdefine_line|#define HIRES_IOCQGETCLOCKBITS&t;_IO( HIRES_IOC_BASE, 2 )
macro_line|#endif /* _ASM_IA64_SN_HIRES_CLOCK_H */
eof
