multiline_comment|/* linux/include/asm-arm/arch-s3c2410/otom-map.h&n; *&n; * (c) 2005 Guillaume GOURAT / NexVision&n; *          guillaume.gourat@nexvision.fr&n; *&n; * NexVision OTOM board memory map definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n;*/
multiline_comment|/* needs arch/map.h including with this */
multiline_comment|/* ok, we&squot;ve used up to 0x01300000, now we need to find space for the&n; * peripherals that live in the nGCS[x] areas, which are quite numerous&n; * in their space.&n; */
macro_line|#ifndef __ASM_ARCH_OTOMMAP_H
DECL|macro|__ASM_ARCH_OTOMMAP_H
mdefine_line|#define __ASM_ARCH_OTOMMAP_H
DECL|macro|OTOM_PA_CS8900A_BASE
mdefine_line|#define OTOM_PA_CS8900A_BASE       (S3C2410_CS3 + 0x01000000)&t;/* nGCS3 +0x01000000 */
DECL|macro|OTOM_VA_CS8900A_BASE
mdefine_line|#define OTOM_VA_CS8900A_BASE       S3C2410_ADDR(0x04000000)&t;&t;/* 0xF4000000 */
multiline_comment|/* physical offset addresses for the peripherals */
DECL|macro|OTOM_PA_FLASH0_BASE
mdefine_line|#define OTOM_PA_FLASH0_BASE        (S3C2410_CS0)&t;&t;&t;&t;/* Bank 0 */
macro_line|#endif /* __ASM_ARCH_OTOMMAP_H */
eof
