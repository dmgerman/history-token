multiline_comment|/*&n; * MyCable XXS1500 Referrence Board&n; *&n; * Copyright 2003 MontaVista Software Inc.&n; * Author: Pete Popov, MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * &n; */
macro_line|#ifndef __ASM_XXS1500_H
DECL|macro|__ASM_XXS1500_H
mdefine_line|#define __ASM_XXS1500_H
multiline_comment|/* PCMCIA XXS1500 specific defines */
DECL|macro|PCMCIA_MAX_SOCK
mdefine_line|#define PCMCIA_MAX_SOCK 0
DECL|macro|PCMCIA_NUM_SOCKS
mdefine_line|#define PCMCIA_NUM_SOCKS (PCMCIA_MAX_SOCK+1)
DECL|macro|PCMCIA_IRQ
mdefine_line|#define PCMCIA_IRQ AU1000_GPIO_4
macro_line|#endif /* __ASM_XXS1500_ */
eof
