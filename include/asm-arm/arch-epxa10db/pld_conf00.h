macro_line|#ifndef __PLD_CONF00_H
DECL|macro|__PLD_CONF00_H
mdefine_line|#define __PLD_CONF00_H
multiline_comment|/*&n; * Register definitions for the PLD Configuration Logic&n; */
multiline_comment|/*&n; *  &n; *  This file contains the register definitions for the Excalibur&n; *  Interrupnt controller INT_CTRL00.&n; *&n; *  Copyright (C) 2001 Altera Corporation&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
DECL|macro|CONFIG_CONTROL
mdefine_line|#define CONFIG_CONTROL(BASE_ADDR) (PLD_CONF00_TYPE (BASE_ADDR))  
DECL|macro|CONFIG_CONTROL_LK_MSK
mdefine_line|#define CONFIG_CONTROL_LK_MSK (0x1)
DECL|macro|CONFIG_CONTROL_LK_OFST
mdefine_line|#define CONFIG_CONTROL_LK_OFST (0)
DECL|macro|CONFIG_CONTROL_CO_MSK
mdefine_line|#define CONFIG_CONTROL_CO_MSK (0x2)
DECL|macro|CONFIG_CONTROL_CO_OFST
mdefine_line|#define CONFIG_CONTROL_CO_OFST (1)
DECL|macro|CONFIG_CONTROL_B_MSK
mdefine_line|#define CONFIG_CONTROL_B_MSK  (0x4)
DECL|macro|CONFIG_CONTROL_B_OFST
mdefine_line|#define CONFIG_CONTROL_B_OFST (2)
DECL|macro|CONFIG_CONTROL_PC_MSK
mdefine_line|#define CONFIG_CONTROL_PC_MSK (0x8)
DECL|macro|CONFIG_CONTROL_PC_OFST
mdefine_line|#define CONFIG_CONTROL_PC_OFST (3)
DECL|macro|CONFIG_CONTROL_E_MSK
mdefine_line|#define CONFIG_CONTROL_E_MSK (0x10)
DECL|macro|CONFIG_CONTROL_E_OFST
mdefine_line|#define CONFIG_CONTROL_E_OFST (4)
DECL|macro|CONFIG_CONTROL_ES_MSK
mdefine_line|#define CONFIG_CONTROL_ES_MSK (0xE0)
DECL|macro|CONFIG_CONTROL_ES_OFST
mdefine_line|#define CONFIG_CONTROL_ES_OFST (5)
DECL|macro|CONFIG_CONTROL_ES_0_MSK
mdefine_line|#define CONFIG_CONTROL_ES_0_MSK (0x20)
DECL|macro|CONFIG_CONTROL_ES_1_MSK
mdefine_line|#define CONFIG_CONTROL_ES_1_MSK (0x40)
DECL|macro|CONFIG_CONTROL_ES_2_MSK
mdefine_line|#define CONFIG_CONTROL_ES_2_MSK (0x80)
DECL|macro|CONFIG_CONTROL_CLOCK
mdefine_line|#define CONFIG_CONTROL_CLOCK(BASE_ADDR) (PLD_CONF00_TYPE (BASE_ADDR  + 0x4 ))
DECL|macro|CONFIG_CONTROL_CLOCK_RATIO_MSK
mdefine_line|#define CONFIG_CONTROL_CLOCK_RATIO_MSK (0xFFFF)
DECL|macro|CONFIG_CONTROL_CLOCK_RATIO_OFST
mdefine_line|#define CONFIG_CONTROL_CLOCK_RATIO_OFST (0)
DECL|macro|CONFIG_CONTROL_DATA
mdefine_line|#define CONFIG_CONTROL_DATA(BASE_ADDR) (PLD_CONF00_TYPE (BASE_ADDR  + 0x8 ))
DECL|macro|CONFIG_CONTROL_DATA_MSK
mdefine_line|#define CONFIG_CONTROL_DATA_MSK (0xFFFFFFFF)
DECL|macro|CONFIG_CONTROL_DATA_OFST
mdefine_line|#define CONFIG_CONTROL_DATA_OFST (0)
DECL|macro|CONFIG_UNLOCK
mdefine_line|#define CONFIG_UNLOCK(BASE_ADDR) (PLD_CONF00_TYPE (BASE_ADDR  + 0xC )) 
DECL|macro|CONFIG_UNLOCK_MSK
mdefine_line|#define CONFIG_UNLOCK_MSK (0xFFFFFFFF)
DECL|macro|CONFIG_UNLOCK_OFST
mdefine_line|#define CONFIG_UNLOCK_OFST (0)
DECL|macro|CONFIG_UNLOCK_MAGIC
mdefine_line|#define CONFIG_UNLOCK_MAGIC (0x554E4C4B)
macro_line|#endif /* __PLD_CONF00_H */
eof
