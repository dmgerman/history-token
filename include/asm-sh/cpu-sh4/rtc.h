macro_line|#ifndef __ASM_CPU_SH4_RTC_H
DECL|macro|__ASM_CPU_SH4_RTC_H
mdefine_line|#define __ASM_CPU_SH4_RTC_H
multiline_comment|/* SH-4 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xffc80000
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xffc80004
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xffc80008
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xffc8000c
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xffc80010
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xffc80014
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xffc80018
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xffc8001c  /* 16bit */
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xffc80020
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xffc80024
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xffc80028
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xffc8002c
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xffc80030
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xffc80034
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xffc80038
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xffc8003c
DECL|macro|RTC_BIT_INVERTED
mdefine_line|#define RTC_BIT_INVERTED&t;0x40&t;/* bug on SH7750, SH7750S */
macro_line|#endif /* __ASM_CPU_SH4_RTC_H */
eof
