multiline_comment|/* drivers/atm/zeprom.h - ZeitNet ZN122x EEPROM (NM93C46) declarations */
multiline_comment|/* Written 1995,1996 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef DRIVER_ATM_ZEPROM_H
DECL|macro|DRIVER_ATM_ZEPROM_H
mdefine_line|#define DRIVER_ATM_ZEPROM_H
multiline_comment|/* Different versions use different control registers */
DECL|macro|ZEPROM_V1_REG
mdefine_line|#define ZEPROM_V1_REG&t;PCI_VENDOR_ID&t;/* PCI register */
DECL|macro|ZEPROM_V2_REG
mdefine_line|#define ZEPROM_V2_REG&t;0x40
multiline_comment|/* Bits in contol register */
DECL|macro|ZEPROM_SK
mdefine_line|#define ZEPROM_SK&t;0x80000000&t;/* strobe (probably on raising edge) */
DECL|macro|ZEPROM_CS
mdefine_line|#define ZEPROM_CS&t;0x40000000&t;/* Chip Select */
DECL|macro|ZEPROM_DI
mdefine_line|#define ZEPROM_DI&t;0x20000000&t;/* Data Input */
DECL|macro|ZEPROM_DO
mdefine_line|#define ZEPROM_DO&t;0x10000000&t;/* Data Output */
DECL|macro|ZEPROM_SIZE
mdefine_line|#define ZEPROM_SIZE&t;32&t;&t;/* 32 bytes */
DECL|macro|ZEPROM_V1_ESI_OFF
mdefine_line|#define ZEPROM_V1_ESI_OFF 24&t;&t;/* ESI offset in EEPROM (V1) */
DECL|macro|ZEPROM_V2_ESI_OFF
mdefine_line|#define ZEPROM_V2_ESI_OFF 4&t;&t;/* ESI offset in EEPROM (V2) */
DECL|macro|ZEPROM_CMD_LEN
mdefine_line|#define ZEPROM_CMD_LEN&t;3&t;&t;/* commands are three bits */
DECL|macro|ZEPROM_ADDR_LEN
mdefine_line|#define ZEPROM_ADDR_LEN&t;6&t;&t;/* addresses are six bits */
multiline_comment|/* Commands (3 bits) */
DECL|macro|ZEPROM_CMD_READ
mdefine_line|#define ZEPROM_CMD_READ&t;6
multiline_comment|/* No other commands are needed. */
macro_line|#endif
eof
