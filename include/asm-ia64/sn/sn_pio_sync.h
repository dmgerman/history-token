multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN_PIO_WRITE_SYNC_H
DECL|macro|_ASM_IA64_SN_SN_PIO_WRITE_SYNC_H
mdefine_line|#define _ASM_IA64_SN_SN_PIO_WRITE_SYNC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN2
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/sn2/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr_t.h&gt;
multiline_comment|/*&n; * This macro flushes all outstanding PIOs performed by this cpu to the &n; * intended destination SHUB.  This in essence ensures that all PIO&squot;s&n; * issues by this cpu has landed at it&squot;s destination.&n; *&n; * This macro expects the caller:&n; *&t;1.  The thread is locked.&n; *&t;2.  All prior PIO operations has been fenced with __ia64_mf_a().&n; *&n; * The expectation is that get_slice() will return either 0 or 2.&n; * When we have multi-core cpu&squot;s, the expectation is get_slice() will &n; * return either 0,1 or 2,3.&n; */
DECL|macro|SN_PIO_WRITE_SYNC
mdefine_line|#define SN_PIO_WRITE_SYNC &bslash;&n;&t;{ &bslash;&n;&t;&t;volatile unsigned long sn_pio_writes_done; &bslash;&n;&t;do { &bslash;&n;&t;&t;sn_pio_writes_done = (volatile unsigned long) (SH_PIO_WRITE_STATUS_0_WRITES_OK_MASK &amp; HUB_L( (unsigned long *)GLOBAL_MMR_ADDR(get_nasid(), (get_slice() &lt; 2) ? SH_PIO_WRITE_STATUS_0 : SH_PIO_WRITE_STATUS_1 ))); &bslash;&n;&t;} while (!sn_pio_writes_done); &bslash;&n;&t;__ia64_mf_a(); &bslash;&n;&t;}
macro_line|#else
multiline_comment|/*&n; * For all ARCHITECTURE type, this is a NOOP.&n; */
DECL|macro|SN_PIO_WRITE_SYNC
mdefine_line|#define SN_PIO_WRITE_SYNC
macro_line|#endif
macro_line|#endif /* _ASM_IA64_SN_SN_PIO_WRITE_SYNC_H */
eof
