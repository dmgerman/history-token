multiline_comment|/*&n; *&t;i810-tco 0.02:&t;TCO timer driver for i810 chipsets&n; *&n; *&t;(c) Copyright 2000 kernel concepts &lt;nils@kernelconcepts.de&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.kernelconcepts.de&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither kernel concepts nor Nils Faerber admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;(c) Copyright 2000&t;kernel concepts &lt;nils@kernelconcepts.de&gt;&n; *&t;&t;&t;&t;developed for&n; *                              Jentro AG, Haar/Munich (Germany)&n; *&n; *&t;TCO timer driver for i810 chipsets&n; *&t;based on softdog.c by Alan Cox &lt;alan@redhat.com&gt;&n; *&n; *      The TCO timer is implemented in the 82801AA (82801AB) chip,&n; *&t;see intel documentation from http://developer.intel.com,&n; *&t;order number 290655-003&n; *&n; *&t;For history see i810-tco.c&n; */
multiline_comment|/*&n; * Some address definitions for the i810 TCO&n; */
DECL|macro|TCOBASE
mdefine_line|#define&t;TCOBASE&t;&t;ACPIBASE + 0x60&t;/* TCO base address&t;&t;*/
DECL|macro|TCO1_RLD
mdefine_line|#define TCO1_RLD&t;TCOBASE + 0x00&t;/* TCO Timer Reload and Current Value */
DECL|macro|TCO1_TMR
mdefine_line|#define TCO1_TMR&t;TCOBASE + 0x01&t;/* TCO Timer Initial Value&t;*/
DECL|macro|TCO1_DAT_IN
mdefine_line|#define&t;TCO1_DAT_IN&t;TCOBASE + 0x02&t;/* TCO Data In Register&t;&t;*/
DECL|macro|TCO1_DAT_OUT
mdefine_line|#define&t;TCO1_DAT_OUT&t;TCOBASE + 0x03&t;/* TCO Data Out Register&t;*/
DECL|macro|TCO1_STS
mdefine_line|#define&t;TCO1_STS&t;TCOBASE + 0x04&t;/* TCO1 Status Register&t;&t;*/
DECL|macro|TCO2_STS
mdefine_line|#define&t;TCO2_STS&t;TCOBASE + 0x06&t;/* TCO2 Status Register&t;&t;*/
DECL|macro|TCO1_CNT
mdefine_line|#define TCO1_CNT&t;TCOBASE + 0x08&t;/* TCO1 Control Register&t;*/
DECL|macro|TCO2_CNT
mdefine_line|#define TCO2_CNT&t;TCOBASE + 0x0a&t;/* TCO2 Control Register&t;*/
DECL|macro|SMI_EN
mdefine_line|#define&t;SMI_EN&t;&t;ACPIBASE + 0x30&t;/* SMI Control and Enable Register */
eof
