multiline_comment|/*******************************************************************************&n;*&n;*      &quot;cs46xxpm-24.h&quot; --  Cirrus Logic-Crystal CS46XX linux audio driver.&n;*&n;*      Copyright (C) 2000,2001  Cirrus Logic Corp.  &n;*            -- tom woller (twoller@crystal.cirrus.com) or&n;*               (pcaudio@crystal.cirrus.com).&n;*&n;*      This program is free software; you can redistribute it and/or modify&n;*      it under the terms of the GNU General Public License as published by&n;*      the Free Software Foundation; either version 2 of the License, or&n;*      (at your option) any later version.&n;*&n;*      This program is distributed in the hope that it will be useful,&n;*      but WITHOUT ANY WARRANTY; without even the implied warranty of&n;*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;*      GNU General Public License for more details.&n;*&n;*      You should have received a copy of the GNU General Public License&n;*      along with this program; if not, write to the Free Software&n;*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*&n;* 12/22/00 trw - new file. &n;*&n;*******************************************************************************/
macro_line|#ifndef __CS46XXPM24_H
DECL|macro|__CS46XXPM24_H
mdefine_line|#define __CS46XXPM24_H
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &quot;cs46xxpm.h&quot;
DECL|macro|CS46XX_ACPI_SUPPORT
mdefine_line|#define CS46XX_ACPI_SUPPORT 1
macro_line|#ifdef CS46XX_ACPI_SUPPORT
multiline_comment|/* &n;* for now (12/22/00) only enable the pm_register PM support.&n;* allow these table entries to be null.&n;*/
r_static
r_int
id|cs46xx_suspend_tbl
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
comma
id|u32
id|state
)paren
suffix:semicolon
r_static
r_int
id|cs46xx_resume_tbl
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
suffix:semicolon
DECL|macro|cs_pm_register
mdefine_line|#define cs_pm_register(a, b, c)  0
DECL|macro|cs_pm_unregister_all
mdefine_line|#define cs_pm_unregister_all(a) 
DECL|macro|CS46XX_SUSPEND_TBL
mdefine_line|#define CS46XX_SUSPEND_TBL cs46xx_suspend_tbl
DECL|macro|CS46XX_RESUME_TBL
mdefine_line|#define CS46XX_RESUME_TBL cs46xx_resume_tbl
macro_line|#else
DECL|macro|cs_pm_register
mdefine_line|#define cs_pm_register(a, b, c) pm_register((a), (b), (c));
DECL|macro|cs_pm_unregister_all
mdefine_line|#define cs_pm_unregister_all(a) pm_unregister_all((a));
DECL|macro|CS46XX_SUSPEND_TBL
mdefine_line|#define CS46XX_SUSPEND_TBL cs46xx_null
DECL|macro|CS46XX_RESUME_TBL
mdefine_line|#define CS46XX_RESUME_TBL cs46xx_null
macro_line|#endif
r_int
id|cs46xx_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
eof
