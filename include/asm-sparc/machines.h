multiline_comment|/* $Id: machines.h,v 1.4 1995/11/25 02:31:58 davem Exp $&n; * machines.h:  Defines for taking apart the machine type value in the&n; *              idprom and determining the kind of machine we are on.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MACHINES_H
DECL|macro|_SPARC_MACHINES_H
mdefine_line|#define _SPARC_MACHINES_H
DECL|struct|Sun_Machine_Models
r_struct
id|Sun_Machine_Models
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_machtype
r_int
r_char
id|id_machtype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Current number of machines we know about that has an IDPROM&n; * machtype entry including one entry for the 0x80 OBP machines.&n; */
DECL|macro|NUM_SUN_MACHINES
mdefine_line|#define NUM_SUN_MACHINES   15
r_extern
r_struct
id|Sun_Machine_Models
id|Sun_Machines
(braket
id|NUM_SUN_MACHINES
)braket
suffix:semicolon
multiline_comment|/* The machine type in the idprom area looks like this:&n; *&n; * ---------------&n; * | ARCH | MACH |&n; * ---------------&n; *  7    4 3    0&n; *&n; * The ARCH field determines the architecture line (sun4, sun4c, etc).&n; * The MACH field determines the machine make within that architecture.&n; */
DECL|macro|SM_ARCH_MASK
mdefine_line|#define SM_ARCH_MASK  0xf0
DECL|macro|SM_SUN4
mdefine_line|#define SM_SUN4       0x20
DECL|macro|SM_SUN4C
mdefine_line|#define SM_SUN4C      0x50
DECL|macro|SM_SUN4M
mdefine_line|#define SM_SUN4M      0x70
DECL|macro|SM_SUN4M_OBP
mdefine_line|#define SM_SUN4M_OBP  0x80
DECL|macro|SM_TYP_MASK
mdefine_line|#define SM_TYP_MASK   0x0f
multiline_comment|/* Sun4 machines */
DECL|macro|SM_4_260
mdefine_line|#define SM_4_260      0x01    /* Sun 4/200 series */
DECL|macro|SM_4_110
mdefine_line|#define SM_4_110      0x02    /* Sun 4/100 series */
DECL|macro|SM_4_330
mdefine_line|#define SM_4_330      0x03    /* Sun 4/300 series */
DECL|macro|SM_4_470
mdefine_line|#define SM_4_470      0x04    /* Sun 4/400 series */
multiline_comment|/* Sun4c machines                Full Name              - PROM NAME */
DECL|macro|SM_4C_SS1
mdefine_line|#define SM_4C_SS1     0x01    /* Sun4c SparcStation 1   - Sun 4/60  */
DECL|macro|SM_4C_IPC
mdefine_line|#define SM_4C_IPC     0x02    /* Sun4c SparcStation IPC - Sun 4/40  */
DECL|macro|SM_4C_SS1PLUS
mdefine_line|#define SM_4C_SS1PLUS 0x03    /* Sun4c SparcStation 1+  - Sun 4/65  */
DECL|macro|SM_4C_SLC
mdefine_line|#define SM_4C_SLC     0x04    /* Sun4c SparcStation SLC - Sun 4/20  */
DECL|macro|SM_4C_SS2
mdefine_line|#define SM_4C_SS2     0x05    /* Sun4c SparcStation 2   - Sun 4/75  */
DECL|macro|SM_4C_ELC
mdefine_line|#define SM_4C_ELC     0x06    /* Sun4c SparcStation ELC - Sun 4/25  */
DECL|macro|SM_4C_IPX
mdefine_line|#define SM_4C_IPX     0x07    /* Sun4c SparcStation IPX - Sun 4/50  */
multiline_comment|/* Sun4m machines, these predate the OpenBoot.  These values only mean&n; * something if the value in the ARCH field is SM_SUN4M, if it is&n; * SM_SUN4M_OBP then you have the following situation:&n; * 1) You either have a sun4d, a sun4e, or a recently made sun4m.&n; * 2) You have to consult OpenBoot to determine which machine this is.&n; */
DECL|macro|SM_4M_SS60
mdefine_line|#define SM_4M_SS60    0x01    /* Sun4m SparcSystem 600                  */
DECL|macro|SM_4M_SS50
mdefine_line|#define SM_4M_SS50    0x02    /* Sun4m SparcStation 10                  */
DECL|macro|SM_4M_SS40
mdefine_line|#define SM_4M_SS40    0x03    /* Sun4m SparcStation 5                   */
multiline_comment|/* Sun4d machines -- N/A */
multiline_comment|/* Sun4e machines -- N/A */
multiline_comment|/* Sun4u machines -- N/A */
macro_line|#endif /* !(_SPARC_MACHINES_H) */
eof
