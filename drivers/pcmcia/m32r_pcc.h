multiline_comment|/*&n; * Copyright (C) 2001 by Hiroyuki Kondo&n; */
DECL|macro|M32R_MAX_PCC
mdefine_line|#define M32R_MAX_PCC&t;2
multiline_comment|/*&n; * M32R PC Card Controler&n; */
DECL|macro|M32R_PCC0_BASE
mdefine_line|#define M32R_PCC0_BASE        0x00ef7000
DECL|macro|M32R_PCC1_BASE
mdefine_line|#define M32R_PCC1_BASE        0x00ef7020
multiline_comment|/*&n; * Register offsets&n; */
DECL|macro|PCCR
mdefine_line|#define PCCR            0x00
DECL|macro|PCADR
mdefine_line|#define PCADR           0x04
DECL|macro|PCMOD
mdefine_line|#define PCMOD           0x08
DECL|macro|PCIRC
mdefine_line|#define PCIRC           0x0c
DECL|macro|PCCSIGCR
mdefine_line|#define PCCSIGCR        0x10
DECL|macro|PCATCR
mdefine_line|#define PCATCR          0x14
multiline_comment|/*&n; * PCCR&n; */
DECL|macro|PCCR_PCEN
mdefine_line|#define PCCR_PCEN       (1UL&lt;&lt;(31-31))
multiline_comment|/*&n; * PCIRC&n; */
DECL|macro|PCIRC_BWERR
mdefine_line|#define PCIRC_BWERR     (1UL&lt;&lt;(31-7))
DECL|macro|PCIRC_CDIN1
mdefine_line|#define PCIRC_CDIN1     (1UL&lt;&lt;(31-14))
DECL|macro|PCIRC_CDIN2
mdefine_line|#define PCIRC_CDIN2     (1UL&lt;&lt;(31-15))
DECL|macro|PCIRC_BEIEN
mdefine_line|#define PCIRC_BEIEN     (1UL&lt;&lt;(31-23))
DECL|macro|PCIRC_CIIEN
mdefine_line|#define PCIRC_CIIEN     (1UL&lt;&lt;(31-30))
DECL|macro|PCIRC_COIEN
mdefine_line|#define PCIRC_COIEN     (1UL&lt;&lt;(31-31))
multiline_comment|/*&n; * PCCSIGCR&n; */
DECL|macro|PCCSIGCR_SEN
mdefine_line|#define PCCSIGCR_SEN    (1UL&lt;&lt;(31-3))
DECL|macro|PCCSIGCR_VEN
mdefine_line|#define PCCSIGCR_VEN    (1UL&lt;&lt;(31-7))
DECL|macro|PCCSIGCR_CRST
mdefine_line|#define PCCSIGCR_CRST   (1UL&lt;&lt;(31-15))
DECL|macro|PCCSIGCR_COCR
mdefine_line|#define PCCSIGCR_COCR   (1UL&lt;&lt;(31-31))
multiline_comment|/*&n; *&n; */
DECL|macro|PCMOD_AS_ATTRIB
mdefine_line|#define PCMOD_AS_ATTRIB&t;(1UL&lt;&lt;(31-19))
DECL|macro|PCMOD_AS_IO
mdefine_line|#define PCMOD_AS_IO&t;(1UL&lt;&lt;(31-18))
DECL|macro|PCMOD_CBSZ
mdefine_line|#define PCMOD_CBSZ&t;(1UL&lt;&lt;(31-23)) /* set for 8bit */
DECL|macro|PCMOD_DBEX
mdefine_line|#define PCMOD_DBEX&t;(1UL&lt;&lt;(31-31)) /* set for excahnge */
multiline_comment|/*&n; * M32R PCC Map addr&n; */
DECL|macro|M32R_PCC0_MAPBASE
mdefine_line|#define M32R_PCC0_MAPBASE        0x14000000
DECL|macro|M32R_PCC1_MAPBASE
mdefine_line|#define M32R_PCC1_MAPBASE        0x16000000
DECL|macro|M32R_PCC_MAPMAX
mdefine_line|#define M32R_PCC_MAPMAX&t;&t; 0x02000000
DECL|macro|M32R_PCC_MAPSIZE
mdefine_line|#define M32R_PCC_MAPSIZE&t; 0x00001000 /* XXX */
DECL|macro|M32R_PCC_MAPMASK
mdefine_line|#define M32R_PCC_MAPMASK     &t;(~(M32R_PCC_MAPMAX-1))
eof
