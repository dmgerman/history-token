multiline_comment|/*&n; * Intel Multimedia Timer device interface&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; * This file should define an interface compatible with the IA-PC Multimedia&n; * Timers Draft Specification (rev. 0.97) from Intel.  Note that some&n; * hardware may not be able to safely export its registers to userspace,&n; * so the ioctl interface should support all necessary functionality.&n; *&n; * 11/01/01 - jbarnes - initial revision&n; * 9/10/04 - Christoph Lameter - remove interrupt support&n; */
macro_line|#ifndef _LINUX_MMTIMER_H
DECL|macro|_LINUX_MMTIMER_H
mdefine_line|#define _LINUX_MMTIMER_H
multiline_comment|/* name of the device, usually in /dev */
DECL|macro|MMTIMER_NAME
mdefine_line|#define MMTIMER_NAME &quot;mmtimer&quot;
DECL|macro|MMTIMER_FULLNAME
mdefine_line|#define MMTIMER_FULLNAME &quot;/dev/mmtimer&quot;
DECL|macro|MMTIMER_DESC
mdefine_line|#define MMTIMER_DESC &quot;IA-PC Multimedia Timer&quot;
DECL|macro|MMTIMER_VERSION
mdefine_line|#define MMTIMER_VERSION &quot;1.0&quot;
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
multiline_comment|/*&n; * An mmtimer verification program.  WARNINGs are ok, but ERRORs indicate&n; * that the device doesn&squot;t fully support the interface defined here.&n; */
macro_line|#ifdef _MMTIMER_TEST_PROGRAM
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &quot;mmtimer.h&quot;
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_int
id|result
comma
id|fd
suffix:semicolon
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|open
c_func
(paren
l_string|&quot;/dev/&quot;
id|MMTIMER_NAME
comma
id|O_RDONLY
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;failed to open /dev/%s&quot;
comma
id|MMTIMER_NAME
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;         * Can we mmap in the counter?&n;         */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_MMAPAVAIL
comma
l_int|0
)paren
)paren
op_eq
l_int|1
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;mmap available&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* ... so try getting the offset for each clock */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_GETOFFSET
comma
l_int|0
)paren
)paren
op_ne
op_minus
id|ENOSYS
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;offset: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;WARNING: offset unavailable for clock&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;WARNING: mmap unavailable&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the resolution in femtoseconds&n;&t; */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_GETRES
comma
op_amp
id|val
)paren
)paren
op_ne
op_minus
id|ENOSYS
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;resolution: %ld femtoseconds&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;ERROR: failed to get resolution&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the frequency in Hz&n;&t; */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_GETFREQ
comma
op_amp
id|val
)paren
)paren
op_ne
op_minus
id|ENOSYS
)paren
r_if
c_cond
(paren
id|val
OL
l_int|10000000
)paren
(brace
multiline_comment|/* less than 10 MHz? */
id|printf
c_func
(paren
l_string|&quot;ERROR: frequency only %ld MHz, should be &gt;= 10 MHz&bslash;n&quot;
comma
id|val
op_div
l_int|1000000
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;frequency: %ld MHz&bslash;n&quot;
comma
id|val
op_div
l_int|1000000
)paren
suffix:semicolon
r_else
id|printf
c_func
(paren
l_string|&quot;ERROR: failed to get frequency&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * How many bits in the counter?&n;&t; */
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_GETBITS
comma
l_int|0
)paren
)paren
op_ne
op_minus
id|ENOSYS
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;bits in counter: %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;ERROR: can&squot;t get number of bits in counter&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|ioctl
c_func
(paren
id|fd
comma
id|MMTIMER_GETCOUNTER
comma
op_amp
id|val
)paren
)paren
op_ne
op_minus
id|ENOSYS
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;counter value: %ld&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;ERROR: can&squot;t get counter value&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* _MMTIMER_TEST_PROGRM */
macro_line|#endif /* _LINUX_MMTIMER_H */
eof
