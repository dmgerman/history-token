multiline_comment|/* $Id: ultra.h,v 1.2 1995/11/25 02:33:10 davem Exp $&n; * ultra.h: Definitions and defines for the TI V9 UltraSparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ULTRA_H
DECL|macro|_SPARC_ULTRA_H
mdefine_line|#define _SPARC_ULTRA_H
multiline_comment|/* Spitfire MMU control register:&n; *&n; * ----------------------------------------------------------&n; * |        | IMPL  | VERS  |     |  MID  |                 |&n; * ----------------------------------------------------------&n; *  64        31-28   27-24  23-22  21-17   16             0&n; *&n; * IMPL: Implementation of this Spitfire.&n; * VERS: Version of this Spitfire.&n; * MID: Module ID of this processor.&n; */
DECL|macro|SPITFIRE_MIDMASK
mdefine_line|#define SPITFIRE_MIDMASK     0x00000000003e0000
multiline_comment|/* Spitfire Load Store Unit control register:&n; *&n; * ---------------------------------------------------------------------&n; * | RSV | PWR | PWW | VWR | VWW | RSV | PMASK | DME | IME | DCE | ICE |&n; * ---------------------------------------------------------------------&n; *  63-25  24    23     22    21    20   19-4      3     2     1     0&n; *&n; * PWR: Physical Watchpoint Read enable: 0=off 1=on&n; * PWW: Physical Watchpoint Write enable: 0=off 1=on&n; * VWR: Virtual Watchpoint Read enable: 0=off 1=on&n; * VWW: Virtual Watchpoint Write enable: 0=off 1=on&n; * PMASK: Parity MASK  ???&n; * DME: Data MMU Enable: 0=off 1=on&n; * IME: Instruction MMU Enable: 0=off 1=on&n; * DCE: Data Cache Enable: 0=off 1=on&n; * ICE: Instruction Cache Enable: 0=off 1=on&n; */
DECL|macro|SPITFIRE_LSU_PWR
mdefine_line|#define SPITFIRE_LSU_PWR      0x01000000
DECL|macro|SPITFIRE_LSU_PWW
mdefine_line|#define SPITFIRE_LSU_PWW      0x00800000
DECL|macro|SPITFIRE_LSU_VWR
mdefine_line|#define SPITFIRE_LSU_VWR      0x00400000
DECL|macro|SPITFIRE_LSU_VWW
mdefine_line|#define SPITFIRE_LSU_VWW      0x00200000
DECL|macro|SPITFIRE_LSU_PMASK
mdefine_line|#define SPITFIRE_LSU_PMASK    0x000ffff0
DECL|macro|SPITFIRE_LSU_DME
mdefine_line|#define SPITFIRE_LSU_DME      0x00000008
DECL|macro|SPITFIRE_LSU_IME
mdefine_line|#define SPITFIRE_LSU_IME      0x00000004
DECL|macro|SPITFIRE_LSU_DCE
mdefine_line|#define SPITFIRE_LSU_DCE      0x00000002
DECL|macro|SPITFIRE_LSU_ICE
mdefine_line|#define SPITFIRE_LSU_ICE      0x00000001
macro_line|#endif /* !(_SPARC_ULTRA_H) */
eof
