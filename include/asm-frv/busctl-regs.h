multiline_comment|/* busctl-regs.h: FR400-series CPU bus controller registers&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_BUSCTL_REGS_H
DECL|macro|_ASM_BUSCTL_REGS_H
mdefine_line|#define _ASM_BUSCTL_REGS_H
multiline_comment|/* bus controller registers */
DECL|macro|__get_LGCR
mdefine_line|#define __get_LGCR()&t;({ *(volatile unsigned long *)(0xfe000010); })
DECL|macro|__get_LMAICR
mdefine_line|#define __get_LMAICR()&t;({ *(volatile unsigned long *)(0xfe000030); })
DECL|macro|__get_LEMBR
mdefine_line|#define __get_LEMBR()&t;({ *(volatile unsigned long *)(0xfe000040); })
DECL|macro|__get_LEMAM
mdefine_line|#define __get_LEMAM()&t;({ *(volatile unsigned long *)(0xfe000048); })
DECL|macro|__get_LCR
mdefine_line|#define __get_LCR(R)&t;({ *(volatile unsigned long *)(0xfe000100 + 8*(R)); })
DECL|macro|__get_LSBR
mdefine_line|#define __get_LSBR(R)&t;({ *(volatile unsigned long *)(0xfe000c00 + 8*(R)); })
DECL|macro|__get_LSAM
mdefine_line|#define __get_LSAM(R)&t;({ *(volatile unsigned long *)(0xfe000d00 + 8*(R)); })
DECL|macro|__set_LGCR
mdefine_line|#define __set_LGCR(V)&t;do { *(volatile unsigned long *)(0xfe000010) = (V); } while(0)
DECL|macro|__set_LMAICR
mdefine_line|#define __set_LMAICR(V)&t;do { *(volatile unsigned long *)(0xfe000030) = (V); } while(0)
DECL|macro|__set_LEMBR
mdefine_line|#define __set_LEMBR(V)&t;do { *(volatile unsigned long *)(0xfe000040) = (V); } while(0)
DECL|macro|__set_LEMAM
mdefine_line|#define __set_LEMAM(V)&t;do { *(volatile unsigned long *)(0xfe000048) = (V); } while(0)
DECL|macro|__set_LCR
mdefine_line|#define __set_LCR(R,V)&t;do { *(volatile unsigned long *)(0xfe000100 + 8*(R)) = (V); } while(0)
DECL|macro|__set_LSBR
mdefine_line|#define __set_LSBR(R,V)&t;do { *(volatile unsigned long *)(0xfe000c00 + 8*(R)) = (V); } while(0)
DECL|macro|__set_LSAM
mdefine_line|#define __set_LSAM(R,V)&t;do { *(volatile unsigned long *)(0xfe000d00 + 8*(R)) = (V); } while(0)
multiline_comment|/* FR401 SDRAM controller registers */
DECL|macro|__get_DBR
mdefine_line|#define __get_DBR(R)&t;({ *(volatile unsigned long *)(0xfe000e00 + 8*(R)); })
DECL|macro|__get_DAM
mdefine_line|#define __get_DAM(R)&t;({ *(volatile unsigned long *)(0xfe000f00 + 8*(R)); })
multiline_comment|/* FR551 SDRAM controller registers */
DECL|macro|__get_DARS
mdefine_line|#define __get_DARS(R)&t;({ *(volatile unsigned long *)(0xfeff0100 + 8*(R)); })
DECL|macro|__get_DAMK
mdefine_line|#define __get_DAMK(R)&t;({ *(volatile unsigned long *)(0xfeff0110 + 8*(R)); })
macro_line|#endif /* _ASM_BUSCTL_REGS_H */
eof
