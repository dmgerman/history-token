macro_line|#ifndef _INCLUDE_CERF_H_
DECL|macro|_INCLUDE_CERF_H_
mdefine_line|#define _INCLUDE_CERF_H_
multiline_comment|/* GPIOs for CF+ slot lines */
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ&t;&t;GPIO_GPIO (22)  /* 1111 MBGNT _OR_ CF IRQ   */
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD&t;&t;GPIO_GPIO (23)  /* 1111 MBREQ _OR_ CF CD    */
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2&t;&t;GPIO_GPIO (19)  /* Graphics IRQ _OR_ CF BVD */
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1&t;&t;GPIO_GPIO (20)  /* 1111 IRQ _OR_ CF BVD     */
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO23
DECL|macro|IRQ_GPIO_CF_BVD2
mdefine_line|#define IRQ_GPIO_CF_BVD2&t;IRQ_GPIO19
DECL|macro|IRQ_GPIO_CF_BVD1
mdefine_line|#define IRQ_GPIO_CF_BVD1&t;IRQ_GPIO20
DECL|macro|GPIO_UCB1200_IRQ
mdefine_line|#define GPIO_UCB1200_IRQ&t;GPIO_GPIO (18)
DECL|macro|IRQ_GPIO_UCB1200_IRQ
mdefine_line|#define IRQ_GPIO_UCB1200_IRQ&t;IRQ_GPIO18
macro_line|#endif
eof
