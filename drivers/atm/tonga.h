multiline_comment|/* drivers/atm/tonga.h - Efficient Networks Tonga (PCI bridge) declarations */
multiline_comment|/* Written 1995 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef DRIVER_ATM_TONGA_H
DECL|macro|DRIVER_ATM_TONGA_H
mdefine_line|#define DRIVER_ATM_TONGA_H
DECL|macro|PCI_TONGA_CTRL
mdefine_line|#define PCI_TONGA_CTRL&t;0x60&t;/* control register */
DECL|macro|END_SWAP_DMA
mdefine_line|#define END_SWAP_DMA&t;0x80&t;/* endian swap on DMA */
DECL|macro|END_SWAP_BYTE
mdefine_line|#define END_SWAP_BYTE&t;0x40&t;/* endian swap on slave byte accesses */
DECL|macro|END_SWAP_WORD
mdefine_line|#define END_SWAP_WORD&t;0x20&t;/* endian swap on slave word accesses */
DECL|macro|SEPROM_MAGIC
mdefine_line|#define SEPROM_MAGIC&t;0x0c&t;/* obscure required pattern (ASIC only) */
DECL|macro|SEPROM_DATA
mdefine_line|#define SEPROM_DATA&t;0x02&t;/* serial EEPROM data (ASIC only) */
DECL|macro|SEPROM_CLK
mdefine_line|#define SEPROM_CLK&t;0x01&t;/* serial EEPROM clock (ASIC only) */
DECL|macro|SEPROM_ESI_BASE
mdefine_line|#define SEPROM_ESI_BASE&t;64&t;/* start of ESI in serial EEPROM */
macro_line|#endif
eof
