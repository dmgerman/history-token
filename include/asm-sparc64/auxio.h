multiline_comment|/* $Id: auxio.h,v 1.2 1999/09/21 14:39:25 davem Exp $&n; * auxio.h:  Definitions and code for the Auxiliary I/O register.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_AUXIO_H
DECL|macro|_SPARC64_AUXIO_H
mdefine_line|#define _SPARC64_AUXIO_H
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* FIXME: All of this should be checked for sun4u. It has /sbus/auxio, but&n;   I don&squot;t know whether it is the same and don&squot;t have a floppy */
r_extern
r_int
r_int
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
mdefine_line|#define AUXREG   (auxio_register)
multiline_comment|/* These are available on sun4c */
DECL|macro|TURN_ON_LED
mdefine_line|#define TURN_ON_LED   &bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb(sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;    (AUXIO_ORMEIN | AUXIO_LED), AUXREG); &bslash;&n;} while(0)
DECL|macro|TURN_OFF_LED
mdefine_line|#define TURN_OFF_LED  &bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb((sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;     AUXIO_ORMEIN) &amp; (~AUXIO_LED), &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
DECL|macro|FLIP_LED
mdefine_line|#define FLIP_LED&t;&bslash;&n;do {&t;if (AUXREG)  &bslash;&n;&t;&t;sbus_writeb((sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;     AUXIO_ORMEIN) ^ AUXIO_LEN, &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
DECL|macro|FLPY_MOTORON
mdefine_line|#define FLPY_MOTORON&t;&bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb(sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;    (AUXIO_ORMEIN | AUXIO_FLPY_DSEL), &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
DECL|macro|FLPY_MOTOROFF
mdefine_line|#define FLPY_MOTOROFF&t;&bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb((sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;     AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_DSEL), &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
DECL|macro|FLPY_TCNTON
mdefine_line|#define FLPY_TCNTON&t;&bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb((sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;     AUXIO_ORMEIN) | AUXIO_FLPY_TCNT, &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
DECL|macro|FLPY_TCNTOFF
mdefine_line|#define FLPY_TCNTOFF&t;&bslash;&n;do {&t;if (AUXREG) &bslash;&n;&t;&t;sbus_writeb((sbus_readb(AUXREG) | &bslash;&n;&t;&t;&t;     AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_TCNT), &bslash;&n;&t;&t;&t;    AUXREG); &bslash;&n;} while(0)
macro_line|#ifndef __ASSEMBLY__
DECL|function|set_auxio
r_extern
id|__inline__
r_void
id|set_auxio
c_func
(paren
r_int
r_char
id|bits_on
comma
r_int
r_char
id|bits_off
)paren
(brace
r_int
r_char
id|regval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|AUXREG
)paren
(brace
r_int
r_char
id|newval
suffix:semicolon
id|regval
op_assign
id|sbus_readb
c_func
(paren
id|AUXREG
)paren
suffix:semicolon
id|newval
op_assign
id|regval
op_or
id|bits_on
suffix:semicolon
id|newval
op_and_assign
op_complement
id|bits_off
suffix:semicolon
id|newval
op_or_assign
id|AUXIO_ORMEIN4M
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|newval
comma
id|AUXREG
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
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
