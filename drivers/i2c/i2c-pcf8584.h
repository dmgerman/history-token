multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/* i2c-pcf8584.h: PCF 8584 global defines&t;&t;&t;&t;*/
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1996 Simon G. Vogl&n;                   1999 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;*/
multiline_comment|/* --------------------------------------------------------------------&t;*/
multiline_comment|/* With some changes from Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-pcf8584.h,v 1.3 2000/01/18 23:54:07 frodo Exp $ */
macro_line|#ifndef I2C_PCF8584_H
DECL|macro|I2C_PCF8584_H
mdefine_line|#define I2C_PCF8584_H 1
multiline_comment|/* ----- Control register bits ----------------------------------------&t;*/
DECL|macro|I2C_PCF_PIN
mdefine_line|#define I2C_PCF_PIN&t;0x80
DECL|macro|I2C_PCF_ESO
mdefine_line|#define I2C_PCF_ESO&t;0x40
DECL|macro|I2C_PCF_ES1
mdefine_line|#define I2C_PCF_ES1&t;0x20
DECL|macro|I2C_PCF_ES2
mdefine_line|#define I2C_PCF_ES2&t;0x10
DECL|macro|I2C_PCF_ENI
mdefine_line|#define I2C_PCF_ENI&t;0x08
DECL|macro|I2C_PCF_STA
mdefine_line|#define I2C_PCF_STA&t;0x04
DECL|macro|I2C_PCF_STO
mdefine_line|#define I2C_PCF_STO&t;0x02
DECL|macro|I2C_PCF_ACK
mdefine_line|#define I2C_PCF_ACK&t;0x01
DECL|macro|I2C_PCF_START
mdefine_line|#define I2C_PCF_START    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
DECL|macro|I2C_PCF_STOP
mdefine_line|#define I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
DECL|macro|I2C_PCF_REPSTART
mdefine_line|#define I2C_PCF_REPSTART (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
DECL|macro|I2C_PCF_IDLE
mdefine_line|#define I2C_PCF_IDLE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)
multiline_comment|/* ----- Status register bits -----------------------------------------&t;*/
multiline_comment|/*#define I2C_PCF_PIN  0x80    as above*/
DECL|macro|I2C_PCF_INI
mdefine_line|#define I2C_PCF_INI 0x40   /* 1 if not initialized */
DECL|macro|I2C_PCF_STS
mdefine_line|#define I2C_PCF_STS 0x20
DECL|macro|I2C_PCF_BER
mdefine_line|#define I2C_PCF_BER 0x10
DECL|macro|I2C_PCF_AD0
mdefine_line|#define I2C_PCF_AD0 0x08
DECL|macro|I2C_PCF_LRB
mdefine_line|#define I2C_PCF_LRB 0x08
DECL|macro|I2C_PCF_AAS
mdefine_line|#define I2C_PCF_AAS 0x04
DECL|macro|I2C_PCF_LAB
mdefine_line|#define I2C_PCF_LAB 0x02
DECL|macro|I2C_PCF_BB
mdefine_line|#define I2C_PCF_BB  0x01
multiline_comment|/* ----- Chip clock frequencies ---------------------------------------&t;*/
DECL|macro|I2C_PCF_CLK3
mdefine_line|#define I2C_PCF_CLK3&t;0x00
DECL|macro|I2C_PCF_CLK443
mdefine_line|#define I2C_PCF_CLK443&t;0x10
DECL|macro|I2C_PCF_CLK6
mdefine_line|#define I2C_PCF_CLK6&t;0x14
DECL|macro|I2C_PCF_CLK
mdefine_line|#define I2C_PCF_CLK&t;0x18
DECL|macro|I2C_PCF_CLK12
mdefine_line|#define I2C_PCF_CLK12&t;0x1c
multiline_comment|/* ----- transmission frequencies -------------------------------------&t;*/
DECL|macro|I2C_PCF_TRNS90
mdefine_line|#define I2C_PCF_TRNS90 0x00&t;/*  90 kHz */
DECL|macro|I2C_PCF_TRNS45
mdefine_line|#define I2C_PCF_TRNS45 0x01&t;/*  45 kHz */
DECL|macro|I2C_PCF_TRNS11
mdefine_line|#define I2C_PCF_TRNS11 0x02&t;/*  11 kHz */
DECL|macro|I2C_PCF_TRNS15
mdefine_line|#define I2C_PCF_TRNS15 0x03&t;/* 1.5 kHz */
multiline_comment|/* ----- Access to internal registers according to ES1,ES2 ------------&t;*/
multiline_comment|/* they are mapped to the data port ( a0 = 0 ) &t;&t;&t;&t;*/
multiline_comment|/* available when ESO == 0 :&t;&t;&t;&t;&t;&t;*/
DECL|macro|I2C_PCF_OWNADR
mdefine_line|#define I2C_PCF_OWNADR&t;0
DECL|macro|I2C_PCF_INTREG
mdefine_line|#define I2C_PCF_INTREG&t;I2C_PCF_ES2
DECL|macro|I2C_PCF_CLKREG
mdefine_line|#define I2C_PCF_CLKREG&t;I2C_PCF_ES1
macro_line|#endif I2C_PCF8584_H
eof
