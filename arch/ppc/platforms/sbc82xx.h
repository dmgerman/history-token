multiline_comment|/* Board information for the SBCPowerQUICCII, which should be generic for&n; * all 8260 boards.  The IMMR is now given to us so the hard define&n; * will soon be removed.  All of the clock values are computed from&n; * the configuration SCMR and the Power-On-Reset word.&n; */
macro_line|#ifndef __PPC_SBC82xx_H__
DECL|macro|__PPC_SBC82xx_H__
mdefine_line|#define __PPC_SBC82xx_H__
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;&t;0xf0000000
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;&t;&t;0xf0000000
DECL|macro|SBC82xx_TODC_NVRAM_ADDR
mdefine_line|#define SBC82xx_TODC_NVRAM_ADDR&t;&t;0x80000000
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC1
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC1&t;0x220000c9&t;/* JP6B */
DECL|macro|SBC82xx_MACADDR_NVRAM_SCC1
mdefine_line|#define SBC82xx_MACADDR_NVRAM_SCC1&t;0x220000cf&t;/* JP6A */
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC2
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC2&t;0x220000d5&t;/* JP7A */
DECL|macro|SBC82xx_MACADDR_NVRAM_FCC3
mdefine_line|#define SBC82xx_MACADDR_NVRAM_FCC3&t;0x220000db&t;/* JP7B */
DECL|macro|BOOTROM_RESTART_ADDR
mdefine_line|#define BOOTROM_RESTART_ADDR      ((uint)0x40000104)
macro_line|#endif /* __PPC_SBC82xx_H__ */
eof
