macro_line|#ifndef SUN3X_H
DECL|macro|SUN3X_H
mdefine_line|#define SUN3X_H
multiline_comment|/* hardware addresses */
DECL|macro|SUN3X_IOMMU
mdefine_line|#define SUN3X_IOMMU       0x60000000
DECL|macro|SUN3X_ENAREG
mdefine_line|#define SUN3X_ENAREG      0x61000000
DECL|macro|SUN3X_INTREG
mdefine_line|#define SUN3X_INTREG      0x61001400
DECL|macro|SUN3X_DIAGREG
mdefine_line|#define SUN3X_DIAGREG     0x61001800
DECL|macro|SUN3X_ZS1
mdefine_line|#define SUN3X_ZS1         0x62000000
DECL|macro|SUN3X_ZS2
mdefine_line|#define SUN3X_ZS2         0x62002000
DECL|macro|SUN3X_LANCE
mdefine_line|#define SUN3X_LANCE       0x65002000
DECL|macro|SUN3X_EEPROM
mdefine_line|#define SUN3X_EEPROM      0x64000000
DECL|macro|SUN3X_IDPROM
mdefine_line|#define SUN3X_IDPROM      0x640007d8
DECL|macro|SUN3X_VIDEO_BASE
mdefine_line|#define SUN3X_VIDEO_BASE  0x50000000
DECL|macro|SUN3X_VIDEO_P4ID
mdefine_line|#define SUN3X_VIDEO_P4ID  0x50300000
DECL|macro|SUN3X_ESP_BASE
mdefine_line|#define SUN3X_ESP_BASE&t;  0x66000000
DECL|macro|SUN3X_ESP_DMA
mdefine_line|#define SUN3X_ESP_DMA&t;  0x66001000
DECL|macro|SUN3X_FDC
mdefine_line|#define SUN3X_FDC         0x6e000000
DECL|macro|SUN3X_FDC_FCR
mdefine_line|#define SUN3X_FDC_FCR     0x6e000400
DECL|macro|SUN3X_FDC_FVR
mdefine_line|#define SUN3X_FDC_FVR     0x6e000800
multiline_comment|/* some NVRAM addresses */
DECL|macro|SUN3X_EEPROM_CONS
mdefine_line|#define SUN3X_EEPROM_CONS &t;(SUN3X_EEPROM + 0x1f)
DECL|macro|SUN3X_EEPROM_PORTA
mdefine_line|#define SUN3X_EEPROM_PORTA&t;(SUN3X_EEPROM + 0x58)
DECL|macro|SUN3X_EEPROM_PORTB
mdefine_line|#define SUN3X_EEPROM_PORTB&t;(SUN3X_EEPROM + 0x60)
macro_line|#endif
eof
