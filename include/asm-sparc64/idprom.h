multiline_comment|/* $Id: idprom.h,v 1.2 1997/04/04 00:50:16 davem Exp $&n; * idprom.h: Macros and defines for idprom routines&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_IDPROM_H
DECL|macro|_SPARC64_IDPROM_H
mdefine_line|#define _SPARC64_IDPROM_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Offset into the EEPROM where the id PROM is located on the 4c */
DECL|macro|IDPROM_OFFSET
mdefine_line|#define IDPROM_OFFSET  0x7d8
multiline_comment|/* On sun4m; physical. */
multiline_comment|/* MicroSPARC(-II) does not decode 31rd bit, but it works. */
DECL|macro|IDPROM_OFFSET_M
mdefine_line|#define IDPROM_OFFSET_M  0xfd8
DECL|struct|idprom
r_struct
id|idprom
(brace
DECL|member|id_format
id|u8
id|id_format
suffix:semicolon
multiline_comment|/* Format identifier (always 0x01) */
DECL|member|id_machtype
id|u8
id|id_machtype
suffix:semicolon
multiline_comment|/* Machine type */
DECL|member|id_ethaddr
id|u8
id|id_ethaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Hardware ethernet address */
DECL|member|id_date
id|s32
id|id_date
suffix:semicolon
multiline_comment|/* Date of manufacture */
DECL|member|id_sernum
id|u32
id|id_sernum
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Unique serial number */
DECL|member|id_cksum
id|u8
id|id_cksum
suffix:semicolon
multiline_comment|/* Checksum - xor of the data bytes */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|idprom
op_star
id|idprom
suffix:semicolon
r_extern
r_void
id|idprom_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|IDPROM_SIZE
mdefine_line|#define IDPROM_SIZE  (sizeof(struct idprom))
macro_line|#endif /* !(_SPARC_IDPROM_H) */
eof
