multiline_comment|/*&n; *  &n; *  This file contains the register definitions for the Excalibur&n; *  Timer TIMER00.&n; *&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __TIMER00_H
DECL|macro|__TIMER00_H
mdefine_line|#define __TIMER00_H
multiline_comment|/*&n; * Register definitions for the timers&n; */
DECL|macro|TIMER0_CR
mdefine_line|#define TIMER0_CR(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x00 ))
DECL|macro|TIMER0_CR_B_MSK
mdefine_line|#define TIMER0_CR_B_MSK (0x20)
DECL|macro|TIMER0_CR_B_OFST
mdefine_line|#define TIMER0_CR_B_OFST (0x5)
DECL|macro|TIMER0_CR_S_MSK
mdefine_line|#define TIMER0_CR_S_MSK  (0x10)
DECL|macro|TIMER0_CR_S_OFST
mdefine_line|#define TIMER0_CR_S_OFST (0x4)
DECL|macro|TIMER0_CR_CI_MSK
mdefine_line|#define TIMER0_CR_CI_MSK (0x08)
DECL|macro|TIMER0_CR_CI_OFST
mdefine_line|#define TIMER0_CR_CI_OFST (0x3)
DECL|macro|TIMER0_CR_IE_MSK
mdefine_line|#define TIMER0_CR_IE_MSK (0x04)
DECL|macro|TIMER0_CR_IE_OFST
mdefine_line|#define TIMER0_CR_IE_OFST (0x2)
DECL|macro|TIMER0_CR_MODE_MSK
mdefine_line|#define TIMER0_CR_MODE_MSK (0x3)
DECL|macro|TIMER0_CR_MODE_OFST
mdefine_line|#define TIMER0_CR_MODE_OFST (0)
DECL|macro|TIMER0_CR_MODE_FREE
mdefine_line|#define TIMER0_CR_MODE_FREE (0)
DECL|macro|TIMER0_CR_MODE_ONE
mdefine_line|#define TIMER0_CR_MODE_ONE  (1)
DECL|macro|TIMER0_CR_MODE_INTVL
mdefine_line|#define TIMER0_CR_MODE_INTVL (2)
DECL|macro|TIMER0_SR
mdefine_line|#define TIMER0_SR(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x00 ))
DECL|macro|TIMER0_SR_B_MSK
mdefine_line|#define TIMER0_SR_B_MSK (0x20)
DECL|macro|TIMER0_SR_B_OFST
mdefine_line|#define TIMER0_SR_B_OFST (0x5)
DECL|macro|TIMER0_SR_S_MSK
mdefine_line|#define TIMER0_SR_S_MSK  (0x10)
DECL|macro|TIMER0_SR_S_OFST
mdefine_line|#define TIMER0_SR_S_OFST (0x4)
DECL|macro|TIMER0_SR_CI_MSK
mdefine_line|#define TIMER0_SR_CI_MSK (0x08)
DECL|macro|TIMER0_SR_CI_OFST
mdefine_line|#define TIMER0_SR_CI_OFST (0x3)
DECL|macro|TIMER0_SR_IE_MSK
mdefine_line|#define TIMER0_SR_IE_MSK (0x04)
DECL|macro|TIMER0_SR_IE_OFST
mdefine_line|#define TIMER0_SR_IE_OFST (0x2)
DECL|macro|TIMER0_SR_MODE_MSK
mdefine_line|#define TIMER0_SR_MODE_MSK (0x3)
DECL|macro|TIMER0_SR_MODE_OFST
mdefine_line|#define TIMER0_SR_MODE_OFST (0)
DECL|macro|TIMER0_SR_MODE_FREE
mdefine_line|#define TIMER0_SR_MODE_FREE (0)
DECL|macro|TIMER0_SR_MODE_ONE
mdefine_line|#define TIMER0_SR_MODE_ONE  (1)
DECL|macro|TIMER0_SR_MODE_INTVL
mdefine_line|#define TIMER0_SR_MODE_INTVL (2)
DECL|macro|TIMER0_PRESCALE
mdefine_line|#define TIMER0_PRESCALE(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x010 ))
DECL|macro|TIMER0_LIMIT
mdefine_line|#define TIMER0_LIMIT(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x020 ))
DECL|macro|TIMER0_READ
mdefine_line|#define TIMER0_READ(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x030 ))
DECL|macro|TIMER1_CR
mdefine_line|#define TIMER1_CR(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x40 ))
DECL|macro|TIMER1_CR_B_MSK
mdefine_line|#define TIMER1_CR_B_MSK (0x20)
DECL|macro|TIMER1_CR_B_OFST
mdefine_line|#define TIMER1_CR_B_OFST (0x5)
DECL|macro|TIMER1_CR_S_MSK
mdefine_line|#define TIMER1_CR_S_MSK  (0x10)
DECL|macro|TIMER1_CR_S_OFST
mdefine_line|#define TIMER1_CR_S_OFST (0x4)
DECL|macro|TIMER1_CR_CI_MSK
mdefine_line|#define TIMER1_CR_CI_MSK (0x08)
DECL|macro|TIMER1_CR_CI_OFST
mdefine_line|#define TIMER1_CR_CI_OFST (0x3)
DECL|macro|TIMER1_CR_IE_MSK
mdefine_line|#define TIMER1_CR_IE_MSK (0x04)
DECL|macro|TIMER1_CR_IE_OFST
mdefine_line|#define TIMER1_CR_IE_OFST (0x2)
DECL|macro|TIMER1_CR_MODE_MSK
mdefine_line|#define TIMER1_CR_MODE_MSK (0x3)
DECL|macro|TIMER1_CR_MODE_OFST
mdefine_line|#define TIMER1_CR_MODE_OFST (0)
DECL|macro|TIMER1_CR_MODE_FREE
mdefine_line|#define TIMER1_CR_MODE_FREE (0)
DECL|macro|TIMER1_CR_MODE_ONE
mdefine_line|#define TIMER1_CR_MODE_ONE  (1)
DECL|macro|TIMER1_CR_MODE_INTVL
mdefine_line|#define TIMER1_CR_MODE_INTVL (2)
DECL|macro|TIMER1_SR
mdefine_line|#define TIMER1_SR(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x40 ))
DECL|macro|TIMER1_SR_B_MSK
mdefine_line|#define TIMER1_SR_B_MSK (0x20)
DECL|macro|TIMER1_SR_B_OFST
mdefine_line|#define TIMER1_SR_B_OFST (0x5)
DECL|macro|TIMER1_SR_S_MSK
mdefine_line|#define TIMER1_SR_S_MSK  (0x10)
DECL|macro|TIMER1_SR_S_OFST
mdefine_line|#define TIMER1_SR_S_OFST (0x4)
DECL|macro|TIMER1_SR_CI_MSK
mdefine_line|#define TIMER1_SR_CI_MSK (0x08)
DECL|macro|TIMER1_SR_CI_OFST
mdefine_line|#define TIMER1_SR_CI_OFST (0x3)
DECL|macro|TIMER1_SR_IE_MSK
mdefine_line|#define TIMER1_SR_IE_MSK (0x04)
DECL|macro|TIMER1_SR_IE_OFST
mdefine_line|#define TIMER1_SR_IE_OFST (0x2)
DECL|macro|TIMER1_SR_MODE_MSK
mdefine_line|#define TIMER1_SR_MODE_MSK (0x3)
DECL|macro|TIMER1_SR_MODE_OFST
mdefine_line|#define TIMER1_SR_MODE_OFST (0)
DECL|macro|TIMER1_SR_MODE_FREE
mdefine_line|#define TIMER1_SR_MODE_FREE (0)
DECL|macro|TIMER1_SR_MODE_ONE
mdefine_line|#define TIMER1_SR_MODE_ONE  (1)
DECL|macro|TIMER1_SR_MODE_INTVL
mdefine_line|#define TIMER1_SR_MODE_INTVL (2)
DECL|macro|TIMER1_PRESCALE
mdefine_line|#define TIMER1_PRESCALE(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x050 ))
DECL|macro|TIMER1_LIMIT
mdefine_line|#define TIMER1_LIMIT(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x060 ))
DECL|macro|TIMER1_READ
mdefine_line|#define TIMER1_READ(BASE_ADDR) (TIMER00_TYPE (BASE_ADDR  + 0x070 ))
macro_line|#endif /* __TIMER00_H */
eof
