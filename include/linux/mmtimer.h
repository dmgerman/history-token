multiline_comment|/*&n; * Intel Multimedia Timer device interface&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; *&n; * This file should define an interface compatible with the IA-PC Multimedia&n; * Timers Draft Specification (rev. 0.97) from Intel.  Note that some&n; * hardware may not be able to safely export its registers to userspace,&n; * so the ioctl interface should support all necessary functionality.&n; *&n; * 11/01/01 - jbarnes - initial revision&n; * 9/10/04 - Christoph Lameter - remove interrupt support&n; * 9/17/04 - jbarnes - remove test program, move some #defines to the driver&n; */
macro_line|#ifndef _LINUX_MMTIMER_H
DECL|macro|_LINUX_MMTIMER_H
mdefine_line|#define _LINUX_MMTIMER_H
multiline_comment|/*&n; * Breakdown of the ioctl&squot;s available.  An &squot;optional&squot; next to the command&n; * indicates that supporting this command is optional, while &squot;required&squot;&n; * commands must be implemented if conformance is desired.&n; *&n; * MMTIMER_GETOFFSET - optional&n; *   Should return the offset (relative to the start of the page where the&n; *   registers are mapped) for the counter in question.&n; *&n; * MMTIMER_GETRES - required&n; *   The resolution of the clock in femto (10^-15) seconds&n; *&n; * MMTIMER_GETFREQ - required&n; *   Frequency of the clock in Hz&n; *&n; * MMTIMER_GETBITS - required&n; *   Number of bits in the clock&squot;s counter&n; *&n; * MMTIMER_MMAPAVAIL - required&n; *   Returns nonzero if the registers can be mmap&squot;d into userspace, 0 otherwise&n; *&n; * MMTIMER_GETCOUNTER - required&n; *   Gets the current value in the counter&n; */
DECL|macro|MMTIMER_IOCTL_BASE
mdefine_line|#define MMTIMER_IOCTL_BASE &squot;m&squot;
DECL|macro|MMTIMER_GETOFFSET
mdefine_line|#define MMTIMER_GETOFFSET _IO(MMTIMER_IOCTL_BASE, 0)
DECL|macro|MMTIMER_GETRES
mdefine_line|#define MMTIMER_GETRES _IOR(MMTIMER_IOCTL_BASE, 1, unsigned long)
DECL|macro|MMTIMER_GETFREQ
mdefine_line|#define MMTIMER_GETFREQ _IOR(MMTIMER_IOCTL_BASE, 2, unsigned long)
DECL|macro|MMTIMER_GETBITS
mdefine_line|#define MMTIMER_GETBITS _IO(MMTIMER_IOCTL_BASE, 4)
DECL|macro|MMTIMER_MMAPAVAIL
mdefine_line|#define MMTIMER_MMAPAVAIL _IO(MMTIMER_IOCTL_BASE, 6)
DECL|macro|MMTIMER_GETCOUNTER
mdefine_line|#define MMTIMER_GETCOUNTER _IOR(MMTIMER_IOCTL_BASE, 9, unsigned long)
macro_line|#endif /* _LINUX_MMTIMER_H */
eof
