multiline_comment|/* $Id: sun4paddr.h,v 1.3 1998/07/28 16:53:27 jj Exp $&n; * sun4paddr.h:  Various physical addresses on sun4 machines&n; *&n; * Copyright (C) 1997 Anton Blanchard (anton@progsoc.uts.edu.au)&n; * Copyright (C) 1998 Chris Davis (cdavis@cois.on.ca)&n; * &n; * Now supports more sun4&squot;s&n; */
macro_line|#ifndef _SPARC_SUN4PADDR_H
DECL|macro|_SPARC_SUN4PADDR_H
mdefine_line|#define _SPARC_SUN4PADDR_H
DECL|macro|SUN4_IE_PHYSADDR
mdefine_line|#define SUN4_IE_PHYSADDR&t;&t;0xf5000000
DECL|macro|SUN4_UNUSED_PHYSADDR
mdefine_line|#define SUN4_UNUSED_PHYSADDR&t;&t;0
multiline_comment|/* these work for me */
DECL|macro|SUN4_200_MEMREG_PHYSADDR
mdefine_line|#define SUN4_200_MEMREG_PHYSADDR&t;0xf4000000
DECL|macro|SUN4_200_CLOCK_PHYSADDR
mdefine_line|#define SUN4_200_CLOCK_PHYSADDR&t;&t;0xf3000000
DECL|macro|SUN4_200_BWTWO_PHYSADDR
mdefine_line|#define SUN4_200_BWTWO_PHYSADDR&t;&t;0xfd000000
DECL|macro|SUN4_200_ETH_PHYSADDR
mdefine_line|#define SUN4_200_ETH_PHYSADDR&t;&t;0xf6000000
DECL|macro|SUN4_200_SI_PHYSADDR
mdefine_line|#define SUN4_200_SI_PHYSADDR&t;&t;0xff200000
multiline_comment|/* these were here before */
DECL|macro|SUN4_300_MEMREG_PHYSADDR
mdefine_line|#define SUN4_300_MEMREG_PHYSADDR&t;0xf4000000
DECL|macro|SUN4_300_CLOCK_PHYSADDR
mdefine_line|#define SUN4_300_CLOCK_PHYSADDR&t;&t;0xf2000000
DECL|macro|SUN4_300_TIMER_PHYSADDR
mdefine_line|#define SUN4_300_TIMER_PHYSADDR&t;&t;0xef000000
DECL|macro|SUN4_300_ETH_PHYSADDR
mdefine_line|#define SUN4_300_ETH_PHYSADDR&t;&t;0xf9000000
DECL|macro|SUN4_300_BWTWO_PHYSADDR
mdefine_line|#define SUN4_300_BWTWO_PHYSADDR&t;&t;0xfb400000
DECL|macro|SUN4_300_DMA_PHYSADDR
mdefine_line|#define SUN4_300_DMA_PHYSADDR&t;&t;0xfa001000
DECL|macro|SUN4_300_ESP_PHYSADDR
mdefine_line|#define SUN4_300_ESP_PHYSADDR&t;&t;0xfa000000
multiline_comment|/* Are these right? */
DECL|macro|SUN4_400_MEMREG_PHYSADDR
mdefine_line|#define SUN4_400_MEMREG_PHYSADDR&t;0xf4000000
DECL|macro|SUN4_400_CLOCK_PHYSADDR
mdefine_line|#define SUN4_400_CLOCK_PHYSADDR&t;&t;0xf2000000
DECL|macro|SUN4_400_TIMER_PHYSADDR
mdefine_line|#define SUN4_400_TIMER_PHYSADDR&t;&t;0xef000000
DECL|macro|SUN4_400_ETH_PHYSADDR
mdefine_line|#define SUN4_400_ETH_PHYSADDR&t;&t;0xf9000000
DECL|macro|SUN4_400_BWTWO_PHYSADDR
mdefine_line|#define SUN4_400_BWTWO_PHYSADDR&t;&t;0xfb400000
DECL|macro|SUN4_400_DMA_PHYSADDR
mdefine_line|#define SUN4_400_DMA_PHYSADDR&t;&t;0xfa001000
DECL|macro|SUN4_400_ESP_PHYSADDR
mdefine_line|#define SUN4_400_ESP_PHYSADDR&t;&t;0xfa000000
multiline_comment|/* &n;&t;these are the actual values set and used in the code. Unused items set &n;&t;to SUN_UNUSED_PHYSADDR &n; */
r_extern
r_int
id|sun4_memreg_physaddr
suffix:semicolon
multiline_comment|/* memory register (ecc?) */
r_extern
r_int
id|sun4_clock_physaddr
suffix:semicolon
multiline_comment|/* system clock */
r_extern
r_int
id|sun4_timer_physaddr
suffix:semicolon
multiline_comment|/* timer, where applicable */
r_extern
r_int
id|sun4_eth_physaddr
suffix:semicolon
multiline_comment|/* onboard ethernet (ie/le) */
r_extern
r_int
id|sun4_si_physaddr
suffix:semicolon
multiline_comment|/* sun3 scsi adapter */
r_extern
r_int
id|sun4_bwtwo_physaddr
suffix:semicolon
multiline_comment|/* onboard bw2 */
r_extern
r_int
id|sun4_dma_physaddr
suffix:semicolon
multiline_comment|/* scsi dma */
r_extern
r_int
id|sun4_esp_physaddr
suffix:semicolon
multiline_comment|/* esp scsi */
r_extern
r_int
id|sun4_ie_physaddr
suffix:semicolon
multiline_comment|/* interrupt enable */
macro_line|#endif /* !(_SPARC_SUN4PADDR_H) */
eof
