multiline_comment|/*&n; *  Code extracted from&n; *  linux/kernel/hd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *&n; *  devfs support - jj, rgooch, 980122&n; *&n; *  Moved partition checking code to fs/partitions* - Russell King&n; *  (linux@arm.uk.linux.org)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_DAC960
r_extern
r_void
id|DAC960_Initialize
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FUSION_BOOT
r_extern
r_int
id|fusion_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|net_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_map_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|soc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atmdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|i2o_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpqarray_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|device_init
r_int
id|__init
id|device_init
c_func
(paren
r_void
)paren
(brace
id|blk_dev_init
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_I2O
id|i2o_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_DAC960
id|DAC960_Initialize
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FUSION_BOOT
id|fusion_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FC4_SOC
multiline_comment|/* This has to be done before scsi_dev_init */
id|soc_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_CPQ_DA
id|cpqarray_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET
id|net_dev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM
(paren
r_void
)paren
id|atmdev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
id|console_map_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|device_init
id|__initcall
c_func
(paren
id|device_init
)paren
suffix:semicolon
eof
