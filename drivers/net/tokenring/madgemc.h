multiline_comment|/* &n; * madgemc.h: Header for the madgemc tms380tr module&n; *&n; * Authors:&n; * - Adam Fritzler &lt;mid@auk.cx&gt;&n; */
macro_line|#ifndef __LINUX_MADGEMC_H
DECL|macro|__LINUX_MADGEMC_H
mdefine_line|#define __LINUX_MADGEMC_H
macro_line|#ifdef __KERNEL__
DECL|macro|MADGEMC16_CARDNAME
mdefine_line|#define MADGEMC16_CARDNAME &quot;Madge Smart 16/4 MC16 Ringnode&quot;
DECL|macro|MADGEMC32_CARDNAME
mdefine_line|#define MADGEMC32_CARDNAME &quot;Madge Smart 16/4 MC32 Ringnode&quot;
multiline_comment|/* &n; * Bit definitions for the POS config registers&n; */
DECL|macro|MC16_POS0_ADDR1
mdefine_line|#define MC16_POS0_ADDR1 0x20
DECL|macro|MC16_POS2_ADDR2
mdefine_line|#define MC16_POS2_ADDR2 0x04
DECL|macro|MC16_POS3_ADDR3
mdefine_line|#define MC16_POS3_ADDR3 0x20
DECL|macro|MC_CONTROL_REG0
mdefine_line|#define MC_CONTROL_REG0&t;&t;((long)-8) /* 0x00 */
DECL|macro|MC_CONTROL_REG1
mdefine_line|#define MC_CONTROL_REG1&t;&t;((long)-7) /* 0x01 */
DECL|macro|MC_ADAPTER_POS_REG0
mdefine_line|#define MC_ADAPTER_POS_REG0&t;((long)-6) /* 0x02 */
DECL|macro|MC_ADAPTER_POS_REG1
mdefine_line|#define MC_ADAPTER_POS_REG1&t;((long)-5) /* 0x03 */
DECL|macro|MC_ADAPTER_POS_REG2
mdefine_line|#define MC_ADAPTER_POS_REG2&t;((long)-4) /* 0x04 */
DECL|macro|MC_ADAPTER_REG5_UNUSED
mdefine_line|#define MC_ADAPTER_REG5_UNUSED&t;((long)-3) /* 0x05 */
DECL|macro|MC_ADAPTER_REG6_UNUSED
mdefine_line|#define MC_ADAPTER_REG6_UNUSED&t;((long)-2) /* 0x06 */
DECL|macro|MC_CONTROL_REG7
mdefine_line|#define MC_CONTROL_REG7&t;&t;((long)-1) /* 0x07 */
DECL|macro|MC_CONTROL_REG0_UNKNOWN1
mdefine_line|#define MC_CONTROL_REG0_UNKNOWN1&t;0x01
DECL|macro|MC_CONTROL_REG0_UNKNOWN2
mdefine_line|#define MC_CONTROL_REG0_UNKNOWN2&t;0x02
DECL|macro|MC_CONTROL_REG0_SIFSEL
mdefine_line|#define MC_CONTROL_REG0_SIFSEL&t;&t;0x04
DECL|macro|MC_CONTROL_REG0_PAGE
mdefine_line|#define MC_CONTROL_REG0_PAGE&t;&t;0x08
DECL|macro|MC_CONTROL_REG0_TESTINTERRUPT
mdefine_line|#define MC_CONTROL_REG0_TESTINTERRUPT&t;0x10
DECL|macro|MC_CONTROL_REG0_UNKNOWN20
mdefine_line|#define MC_CONTROL_REG0_UNKNOWN20&t;0x20
DECL|macro|MC_CONTROL_REG0_SINTR
mdefine_line|#define MC_CONTROL_REG0_SINTR&t;&t;0x40
DECL|macro|MC_CONTROL_REG0_UNKNOWN80
mdefine_line|#define MC_CONTROL_REG0_UNKNOWN80&t;0x80
DECL|macro|MC_CONTROL_REG1_SINTEN
mdefine_line|#define MC_CONTROL_REG1_SINTEN&t;&t;0x01
DECL|macro|MC_CONTROL_REG1_BITOFDEATH
mdefine_line|#define MC_CONTROL_REG1_BITOFDEATH&t;0x02
DECL|macro|MC_CONTROL_REG1_NSRESET
mdefine_line|#define MC_CONTROL_REG1_NSRESET&t;&t;0x04
DECL|macro|MC_CONTROL_REG1_UNKNOWN8
mdefine_line|#define MC_CONTROL_REG1_UNKNOWN8&t;0x08
DECL|macro|MC_CONTROL_REG1_UNKNOWN10
mdefine_line|#define MC_CONTROL_REG1_UNKNOWN10&t;0x10
DECL|macro|MC_CONTROL_REG1_UNKNOWN20
mdefine_line|#define MC_CONTROL_REG1_UNKNOWN20&t;0x20
DECL|macro|MC_CONTROL_REG1_SRSX
mdefine_line|#define MC_CONTROL_REG1_SRSX&t;&t;0x40
DECL|macro|MC_CONTROL_REG1_SPEED_SEL
mdefine_line|#define MC_CONTROL_REG1_SPEED_SEL&t;0x80
DECL|macro|MC_CONTROL_REG7_CABLESTP
mdefine_line|#define MC_CONTROL_REG7_CABLESTP&t;0x00
DECL|macro|MC_CONTROL_REG7_CABLEUTP
mdefine_line|#define MC_CONTROL_REG7_CABLEUTP&t;0x01
multiline_comment|/*&n; * ROM Page Zero&n; */
DECL|macro|MC_ROM_MANUFACTURERID
mdefine_line|#define MC_ROM_MANUFACTURERID&t;&t;0x00
DECL|macro|MC_ROM_ADAPTERID
mdefine_line|#define MC_ROM_ADAPTERID&t;&t;0x01
DECL|macro|MC_ROM_REVISION
mdefine_line|#define MC_ROM_REVISION&t;&t;&t;0x02
DECL|macro|MC_ROM_CONFIG0
mdefine_line|#define MC_ROM_CONFIG0&t;&t;&t;0x03
DECL|macro|MC_ROM_CONFIG1
mdefine_line|#define MC_ROM_CONFIG1&t;&t;&t;0x04
DECL|macro|MC_ROM_CONFIG2
mdefine_line|#define MC_ROM_CONFIG2&t;&t;&t;0x05
multiline_comment|/*&n; * ROM Page One&n; */
DECL|macro|MC_ROM_UNUSED_BYTE
mdefine_line|#define MC_ROM_UNUSED_BYTE&t;&t;0x00
DECL|macro|MC_ROM_BIA_START
mdefine_line|#define MC_ROM_BIA_START&t;&t;0x01
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_MADGEMC_H */
eof
