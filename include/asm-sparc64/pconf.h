multiline_comment|/* $Id: pconf.h,v 1.1 1996/12/02 00:09:10 davem Exp $&n; * pconf.h: pathconf() and fpathconf() defines for SunOS&n; *          system call compatibility.&n; *&n; * Copyright (C) 1995, 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_PCONF_H
DECL|macro|_SPARC64_PCONF_H
mdefine_line|#define _SPARC64_PCONF_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
DECL|macro|_PCONF_LINK
mdefine_line|#define _PCONF_LINK       1 /* Max number of links to an object        */
DECL|macro|_PCONF_CANON
mdefine_line|#define _PCONF_CANON      2 /* TTY input buffer line size              */
DECL|macro|_PCONF_INPUT
mdefine_line|#define _PCONF_INPUT      3 /* Biggest packet a tty can imbibe at once */
DECL|macro|_PCONF_NAME
mdefine_line|#define _PCONF_NAME       4 /* Filename length max                     */
DECL|macro|_PCONF_PATH
mdefine_line|#define _PCONF_PATH       5 /* Max size of a pathname                  */
DECL|macro|_PCONF_PIPE
mdefine_line|#define _PCONF_PIPE       6 /* Buffer size for a pipe                  */
DECL|macro|_PCONF_CHRESTRICT
mdefine_line|#define _PCONF_CHRESTRICT 7 /* Can only root chown files?              */
DECL|macro|_PCONF_NOTRUNC
mdefine_line|#define _PCONF_NOTRUNC    8 /* Are pathnames truncated if too big?     */
DECL|macro|_PCONF_VDISABLE
mdefine_line|#define _PCONF_VDISABLE   9 /* Magic char to disable special tty chars */
DECL|macro|_PCONF_MAXPCONF
mdefine_line|#define _PCONF_MAXPCONF   9
macro_line|#endif /* !(_SPARC64_PCONF_H) */
eof
