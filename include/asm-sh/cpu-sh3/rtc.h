macro_line|#ifndef __ASM_CPU_SH3_RTC_H
DECL|macro|__ASM_CPU_SH3_RTC_H
mdefine_line|#define __ASM_CPU_SH3_RTC_H
multiline_comment|/* SH-3 RTC */
DECL|macro|R64CNT
mdefine_line|#define R64CNT  &t;0xfffffec0
DECL|macro|RSECCNT
mdefine_line|#define RSECCNT &t;0xfffffec2
DECL|macro|RMINCNT
mdefine_line|#define RMINCNT &t;0xfffffec4
DECL|macro|RHRCNT
mdefine_line|#define RHRCNT  &t;0xfffffec6
DECL|macro|RWKCNT
mdefine_line|#define RWKCNT  &t;0xfffffec8
DECL|macro|RDAYCNT
mdefine_line|#define RDAYCNT &t;0xfffffeca
DECL|macro|RMONCNT
mdefine_line|#define RMONCNT &t;0xfffffecc
DECL|macro|RYRCNT
mdefine_line|#define RYRCNT  &t;0xfffffece
DECL|macro|RSECAR
mdefine_line|#define RSECAR  &t;0xfffffed0
DECL|macro|RMINAR
mdefine_line|#define RMINAR  &t;0xfffffed2
DECL|macro|RHRAR
mdefine_line|#define RHRAR   &t;0xfffffed4
DECL|macro|RWKAR
mdefine_line|#define RWKAR   &t;0xfffffed6
DECL|macro|RDAYAR
mdefine_line|#define RDAYAR  &t;0xfffffed8
DECL|macro|RMONAR
mdefine_line|#define RMONAR  &t;0xfffffeda
DECL|macro|RCR1
mdefine_line|#define RCR1    &t;0xfffffedc
DECL|macro|RCR2
mdefine_line|#define RCR2    &t;0xfffffede
DECL|macro|RTC_BIT_INVERTED
mdefine_line|#define RTC_BIT_INVERTED&t;0&t;/* No bug on SH7708, SH7709A */
macro_line|#endif /* __ASM_CPU_SH3_RTC_H */
eof
