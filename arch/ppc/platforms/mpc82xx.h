multiline_comment|/*&n; * arch/ppc/platforms/mpc82xx.h&n; *&n; * Board specific support for various 82xx platforms.&n; *&n; * Author: Allen Curtis &lt;acurtis@onz.com&gt;&n; *&n; * Copyright 2002 Ones and Zeros, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __CONFIG_82XX_PLATFORMS
DECL|macro|__CONFIG_82XX_PLATFORMS
mdefine_line|#define __CONFIG_82XX_PLATFORMS
macro_line|#ifdef CONFIG_8260
macro_line|#ifdef CONFIG_EST8260
macro_line|#include &lt;platforms/est8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SBS8260
macro_line|#include &lt;platforms/sbs8260.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RPX6
macro_line|#include &lt;platforms/rpxsuper.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_WILLOW
macro_line|#include &lt;platforms/willow.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_TQM8260
macro_line|#include &lt;platforms/tqm8260.h&gt;
macro_line|#endif
macro_line|#endif&t;/* CONFIG_8260 */
macro_line|#endif
eof
