multiline_comment|/* Useful PROM locations */
macro_line|#ifndef SUN3X_PROM_H
DECL|macro|SUN3X_PROM_H
mdefine_line|#define SUN3X_PROM_H
r_extern
r_void
(paren
op_star
id|sun3x_putchar
)paren
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|sun3x_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|sun3x_mayget
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|sun3x_mayput
)paren
(paren
r_int
)paren
suffix:semicolon
r_void
id|sun3x_reboot
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sun3x_abort
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sun3x_prom_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|sun3x_prom_ptov
c_func
(paren
r_int
r_int
id|pa
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* interesting hardware locations */
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
mdefine_line|#define SUN3X_VIDEO_BASE  0x50400000
DECL|macro|SUN3X_VIDEO_REGS
mdefine_line|#define SUN3X_VIDEO_REGS  0x50300000
multiline_comment|/* vector table */
DECL|macro|SUN3X_PROM_BASE
mdefine_line|#define SUN3X_PROM_BASE   0xfefe0000
DECL|macro|SUN3X_P_GETCHAR
mdefine_line|#define SUN3X_P_GETCHAR   (SUN3X_PROM_BASE + 20)
DECL|macro|SUN3X_P_PUTCHAR
mdefine_line|#define SUN3X_P_PUTCHAR   (SUN3X_PROM_BASE + 24)
DECL|macro|SUN3X_P_MAYGET
mdefine_line|#define SUN3X_P_MAYGET    (SUN3X_PROM_BASE + 28)
DECL|macro|SUN3X_P_MAYPUT
mdefine_line|#define SUN3X_P_MAYPUT    (SUN3X_PROM_BASE + 32)
DECL|macro|SUN3X_P_REBOOT
mdefine_line|#define SUN3X_P_REBOOT    (SUN3X_PROM_BASE + 96)
DECL|macro|SUN3X_P_SETLEDS
mdefine_line|#define SUN3X_P_SETLEDS   (SUN3X_PROM_BASE + 144)
DECL|macro|SUN3X_P_ABORT
mdefine_line|#define SUN3X_P_ABORT     (SUN3X_PROM_BASE + 152)
multiline_comment|/* mapped area */
DECL|macro|SUN3X_MAP_START
mdefine_line|#define SUN3X_MAP_START   0xfee00000
DECL|macro|SUN3X_MAP_END
mdefine_line|#define SUN3X_MAP_END     0xff000000
macro_line|#endif
eof
