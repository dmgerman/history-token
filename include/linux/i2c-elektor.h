multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-elektor.c i2c-hw access for PCF8584 style isa bus adaptes             */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-97 Simon G. Vogl&n;                   1998-99 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-elektor.h,v 1.5 2001/06/05 01:46:33 mds Exp $ */
macro_line|#ifndef I2C_PCF_ELEKTOR_H
DECL|macro|I2C_PCF_ELEKTOR_H
mdefine_line|#define I2C_PCF_ELEKTOR_H 1
multiline_comment|/*&n; * This struct contains the hw-dependent functions of PCF8584 adapters to&n; * manipulate the registers, and to init any hw-specific features.&n; * vdovikin: removed: this module in real supports only one device,&n; * due to missing arguments in some functions, called from the algo-pcf module.&n; * Sometimes it&squot;s need to be rewriten -&n; * but for now just remove this for simpler reading */
multiline_comment|/*&n;struct i2c_pcf_isa {&n;&t;int pi_base;&n;&t;int pi_irq;&n;&t;int pi_clock;&n;&t;int pi_own;&n;};&n;*/
macro_line|#endif /* PCF_ELEKTOR_H */
eof
