multiline_comment|/* $Id: auxio.h,v 1.18 1997/11/07 15:01:45 jj Exp $&n; * auxio.h:  Definitions and code for the Auxiliary I/O register.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_AUXIO_H
DECL|macro|_SPARC_AUXIO_H
mdefine_line|#define _SPARC_AUXIO_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
r_extern
r_int
r_char
op_star
id|auxio_register
suffix:semicolon
multiline_comment|/* This register is an unsigned char in IO space.  It does two things.&n; * First, it is used to control the front panel LED light on machines&n; * that have it (good for testing entry points to trap handlers and irq&squot;s)&n; * Secondly, it controls various floppy drive parameters.&n; */
DECL|macro|AUXIO_ORMEIN
mdefine_line|#define AUXIO_ORMEIN      0xf0    /* All writes must set these bits. */
DECL|macro|AUXIO_ORMEIN4M
mdefine_line|#define AUXIO_ORMEIN4M    0xc0    /* sun4m - All writes must set these bits. */
DECL|macro|AUXIO_FLPY_DENS
mdefine_line|#define AUXIO_FLPY_DENS   0x20    /* Floppy density, high if set. Read only. */
DECL|macro|AUXIO_FLPY_DCHG
mdefine_line|#define AUXIO_FLPY_DCHG   0x10    /* A disk change occurred.  Read only. */
DECL|macro|AUXIO_EDGE_ON
mdefine_line|#define AUXIO_EDGE_ON     0x10    /* sun4m - On means Jumper block is in. */
DECL|macro|AUXIO_FLPY_DSEL
mdefine_line|#define AUXIO_FLPY_DSEL   0x08    /* Drive select/start-motor. Write only. */
DECL|macro|AUXIO_LINK_TEST
mdefine_line|#define AUXIO_LINK_TEST   0x08    /* sun4m - On means TPE Carrier detect. */
multiline_comment|/* Set the following to one, then zero, after doing a pseudo DMA transfer. */
DECL|macro|AUXIO_FLPY_TCNT
mdefine_line|#define AUXIO_FLPY_TCNT   0x04    /* Floppy terminal count. Write only. */
multiline_comment|/* Set the following to zero to eject the floppy. */
DECL|macro|AUXIO_FLPY_EJCT
mdefine_line|#define AUXIO_FLPY_EJCT   0x02    /* Eject floppy disk.  Write only. */
DECL|macro|AUXIO_LED
mdefine_line|#define AUXIO_LED         0x01    /* On if set, off if unset. Read/Write */
DECL|macro|AUXREG
mdefine_line|#define AUXREG   ((volatile unsigned char *)(auxio_register))
multiline_comment|/* These are available on sun4c */
DECL|macro|TURN_ON_LED
mdefine_line|#define TURN_ON_LED   if (AUXREG) *AUXREG = (*AUXREG | AUXIO_ORMEIN | AUXIO_LED)
DECL|macro|TURN_OFF_LED
mdefine_line|#define TURN_OFF_LED  if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_LED))
DECL|macro|FLIP_LED
mdefine_line|#define FLIP_LED      if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) ^ AUXIO_LED)
DECL|macro|FLPY_MOTORON
mdefine_line|#define FLPY_MOTORON  if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) | AUXIO_FLPY_DSEL)
DECL|macro|FLPY_MOTOROFF
mdefine_line|#define FLPY_MOTOROFF if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_DSEL))
DECL|macro|FLPY_TCNTON
mdefine_line|#define FLPY_TCNTON   if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) | AUXIO_FLPY_TCNT)
DECL|macro|FLPY_TCNTOFF
mdefine_line|#define FLPY_TCNTOFF  if (AUXREG) *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_TCNT))
macro_line|#ifndef __ASSEMBLY__
DECL|macro|set_auxio
mdefine_line|#define set_auxio(bits_on, bits_off) &bslash;&n;do { &bslash;&n;&t;unsigned char regval; &bslash;&n;&t;unsigned long flags; &bslash;&n;&t;save_flags(flags); cli(); &bslash;&n;&t;switch(sparc_cpu_model) { &bslash;&n;&t;case sun4c: &bslash;&n;&t;&t;regval = *AUXREG; &bslash;&n;&t;&t;*AUXREG = ((regval | bits_on) &amp; ~bits_off) | AUXIO_ORMEIN; &bslash;&n;&t;&t;break; &bslash;&n;&t;case sun4m: &bslash;&n;&t;&t;if(!AUXREG) &bslash;&n;&t;&t;&t;break;     /* VME chassic sun4m, no auxio. */ &bslash;&n;&t;&t;regval = *AUXREG; &bslash;&n;&t;&t;*AUXREG = ((regval | bits_on) &amp; ~bits_off) | AUXIO_ORMEIN4M; &bslash;&n;&t;&t;break; &bslash;&n;&t;case sun4d: &bslash;&n;&t;&t;break; &bslash;&n;&t;default: &bslash;&n;&t;&t;panic(&quot;Can&squot;t set AUXIO register on this machine.&quot;); &bslash;&n;&t;}; &bslash;&n;&t;restore_flags(flags); &bslash;&n;} while(0)
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* AUXIO2 (Power Off Control) */
r_extern
id|__volatile__
r_int
r_char
op_star
id|auxio_power_register
suffix:semicolon
DECL|macro|AUXIO_POWER_DETECT_FAILURE
mdefine_line|#define&t;AUXIO_POWER_DETECT_FAILURE&t;32
DECL|macro|AUXIO_POWER_CLEAR_FAILURE
mdefine_line|#define&t;AUXIO_POWER_CLEAR_FAILURE&t;2
DECL|macro|AUXIO_POWER_OFF
mdefine_line|#define&t;AUXIO_POWER_OFF&t;&t;&t;1
macro_line|#endif /* !(_SPARC_AUXIO_H) */
eof
