multiline_comment|/*&n; * File...........: linux/include/asm/todclk.h&n; * Author(s)......: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Bugreports.to..: &lt;Linux390@de.ibm.com&gt;&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n; *&n; * History of changes (starts July 2000)&n; */
macro_line|#ifndef __ASM_TODCLK_H
DECL|macro|__ASM_TODCLK_H
mdefine_line|#define __ASM_TODCLK_H
DECL|macro|TOD_uSEC
mdefine_line|#define TOD_uSEC (0x1000ULL)
DECL|macro|TOD_mSEC
mdefine_line|#define TOD_mSEC (1000 * TOD_uSEC)
DECL|macro|TOD_SEC
mdefine_line|#define TOD_SEC (1000 * TOD_mSEC)
DECL|macro|TOD_MIN
mdefine_line|#define TOD_MIN (60 * TOD_SEC)
DECL|macro|TOD_HOUR
mdefine_line|#define TOD_HOUR (60 * TOD_MIN)
macro_line|#endif
eof
