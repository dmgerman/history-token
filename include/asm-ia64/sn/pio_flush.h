multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _ASM_IA64_PIO_FLUSH_H
DECL|macro|_ASM_IA64_PIO_FLUSH_H
mdefine_line|#define _ASM_IA64_PIO_FLUSH_H
multiline_comment|/*&n; * This macro flushes all outstanding PIOs performed by this cpu to the &n; * intended destination SHUB.  This in essence ensures that all PIO&squot;s&n; * issues by this cpu has landed at it&squot;s destination.&n; *&n; * This macro expects the caller:&n; *&t;1.  The thread is locked.&n; *&t;2.  All prior PIO operations has been fenced.&n; *&n; */
macro_line|#if defined (CONFIG_IA64_SGI_SN)
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#if defined (CONFIG_IA64_SGI_SN2)
DECL|macro|PIO_FLUSH
mdefine_line|#define PIO_FLUSH() &bslash;&n;&t;{ &bslash;&n;&t;while ( !((volatile unsigned long) (*pda.pio_write_status_addr)) &amp; 0x8000000000000000) { &bslash;&n;&t;&t;&t;udelay(5); &bslash;&n;&t;} &bslash;&n;&t;__ia64_mf_a(); &bslash;&n;&t;}
macro_line|#elif defined (CONFIG_IA64_SGI_SN1)
multiline_comment|/*&n; * For SN1 we need to first read any local Bedrock&squot;s MMR and then poll on the &n; * Synergy MMR.&n; */
DECL|macro|PIO_FLUSH
mdefine_line|#define PIO_FLUSH() &bslash;&n;&t;{ &bslash;&n;&t;(volatile unsigned long) (*pda.bedrock_rev_id); &bslash;&n;&t;while (!(volatile unsigned long) (*pda.pio_write_status_addr)) { &bslash;&n;&t;&t;udelay(5); &bslash;&n;&t;} &bslash;&n;&t;__ia64_mf_a(); &bslash;&n;&t;} 
macro_line|#endif
macro_line|#else
multiline_comment|/*&n; * For all ARCHITECTURE type, this is a NOOP.&n; */
DECL|macro|PIO_FLUSH
mdefine_line|#define PIO_FLUSH()
macro_line|#endif
macro_line|#endif /* _ASM_IA64_PIO_FLUSH_H */
eof
