multiline_comment|/* $Id: mpmbox.h,v 1.4 1996/04/25 06:13:19 davem Exp $&n; * mpmbox.h:  Interface and defines for the OpenProm mailbox&n; *               facilities for MP machines under Linux.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MPMBOX_H
DECL|macro|_SPARC_MPMBOX_H
mdefine_line|#define _SPARC_MPMBOX_H
multiline_comment|/* The prom allocates, for each CPU on the machine an unsigned&n; * byte in physical ram.  You probe the device tree prom nodes&n; * for these values.  The purpose of this byte is to be able to&n; * pass messages from one cpu to another.&n; */
multiline_comment|/* These are the main message types we have to look for in our&n; * Cpu mailboxes, based upon these values we decide what course&n; * of action to take.&n; */
multiline_comment|/* The CPU is executing code in the kernel. */
DECL|macro|MAILBOX_ISRUNNING
mdefine_line|#define MAILBOX_ISRUNNING     0xf0
multiline_comment|/* Another CPU called romvec-&gt;pv_exit(), you should call&n; * prom_stopcpu() when you see this in your mailbox.&n; */
DECL|macro|MAILBOX_EXIT
mdefine_line|#define MAILBOX_EXIT          0xfb
multiline_comment|/* Another CPU called romvec-&gt;pv_enter(), you should call&n; * prom_cpuidle() when this is seen.&n; */
DECL|macro|MAILBOX_GOSPIN
mdefine_line|#define MAILBOX_GOSPIN        0xfc
multiline_comment|/* Another CPU has hit a breakpoint either into kadb or the prom&n; * itself.  Just like MAILBOX_GOSPIN, you should call prom_cpuidle()&n; * at this point.&n; */
DECL|macro|MAILBOX_BPT_SPIN
mdefine_line|#define MAILBOX_BPT_SPIN      0xfd
multiline_comment|/* Oh geese, some other nitwit got a damn watchdog reset.  The party&squot;s&n; * over so go call prom_stopcpu().&n; */
DECL|macro|MAILBOX_WDOG_STOP
mdefine_line|#define MAILBOX_WDOG_STOP     0xfe
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Handy macro&squot;s to determine a cpu&squot;s state. */
multiline_comment|/* Is the cpu still in Power On Self Test? */
DECL|macro|MBOX_POST_P
mdefine_line|#define MBOX_POST_P(letter)  ((letter) &gt;= 0x00 &amp;&amp; (letter) &lt;= 0x7f)
multiline_comment|/* Is the cpu at the &squot;ok&squot; prompt of the PROM? */
DECL|macro|MBOX_PROMPROMPT_P
mdefine_line|#define MBOX_PROMPROMPT_P(letter) ((letter) &gt;= 0x80 &amp;&amp; (letter) &lt;= 0x8f)
multiline_comment|/* Is the cpu spinning in the PROM? */
DECL|macro|MBOX_PROMSPIN_P
mdefine_line|#define MBOX_PROMSPIN_P(letter) ((letter) &gt;= 0x90 &amp;&amp; (letter) &lt;= 0xef)
multiline_comment|/* Sanity check... This is junk mail, throw it out. */
DECL|macro|MBOX_BOGON_P
mdefine_line|#define MBOX_BOGON_P(letter) ((letter) &gt;= 0xf1 &amp;&amp; (letter) &lt;= 0xfa)
multiline_comment|/* Is the cpu actively running an application/kernel-code? */
DECL|macro|MBOX_RUNNING_P
mdefine_line|#define MBOX_RUNNING_P(letter) ((letter) == MAILBOX_ISRUNNING)
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_SPARC_MPMBOX_H) */
eof
