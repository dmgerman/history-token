multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: mthca_config_reg.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef MTHCA_CONFIG_REG_H
DECL|macro|MTHCA_CONFIG_REG_H
mdefine_line|#define MTHCA_CONFIG_REG_H
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|MTHCA_HCR_BASE
mdefine_line|#define MTHCA_HCR_BASE         0x80680
DECL|macro|MTHCA_HCR_SIZE
mdefine_line|#define MTHCA_HCR_SIZE         0x0001c
DECL|macro|MTHCA_ECR_BASE
mdefine_line|#define MTHCA_ECR_BASE         0x80700
DECL|macro|MTHCA_ECR_SIZE
mdefine_line|#define MTHCA_ECR_SIZE         0x00008
DECL|macro|MTHCA_ECR_CLR_BASE
mdefine_line|#define MTHCA_ECR_CLR_BASE     0x80708
DECL|macro|MTHCA_ECR_CLR_SIZE
mdefine_line|#define MTHCA_ECR_CLR_SIZE     0x00008
DECL|macro|MTHCA_MAP_ECR_SIZE
mdefine_line|#define MTHCA_MAP_ECR_SIZE     (MTHCA_ECR_SIZE + MTHCA_ECR_CLR_SIZE)
DECL|macro|MTHCA_CLR_INT_BASE
mdefine_line|#define MTHCA_CLR_INT_BASE     0xf00d8
DECL|macro|MTHCA_CLR_INT_SIZE
mdefine_line|#define MTHCA_CLR_INT_SIZE     0x00008
macro_line|#endif /* MTHCA_CONFIG_REG_H */
eof
