multiline_comment|/*&n; *  linux/include/linux/mmc/card.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Card driver specific definitions.&n; */
macro_line|#ifndef LINUX_MMC_CARD_H
DECL|macro|LINUX_MMC_CARD_H
mdefine_line|#define LINUX_MMC_CARD_H
macro_line|#include &lt;linux/mmc/mmc.h&gt;
DECL|struct|mmc_cid
r_struct
id|mmc_cid
(brace
DECL|member|manfid
r_int
r_int
id|manfid
suffix:semicolon
DECL|member|prod_name
r_char
id|prod_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
DECL|member|oemid
r_int
r_int
id|oemid
suffix:semicolon
DECL|member|year
r_int
r_int
id|year
suffix:semicolon
DECL|member|hwrev
r_int
r_char
id|hwrev
suffix:semicolon
DECL|member|fwrev
r_int
r_char
id|fwrev
suffix:semicolon
DECL|member|month
r_int
r_char
id|month
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mmc_csd
r_struct
id|mmc_csd
(brace
DECL|member|mmca_vsn
r_int
r_char
id|mmca_vsn
suffix:semicolon
DECL|member|cmdclass
r_int
r_int
id|cmdclass
suffix:semicolon
DECL|member|tacc_clks
r_int
r_int
id|tacc_clks
suffix:semicolon
DECL|member|tacc_ns
r_int
r_int
id|tacc_ns
suffix:semicolon
DECL|member|max_dtr
r_int
r_int
id|max_dtr
suffix:semicolon
DECL|member|read_blkbits
r_int
r_int
id|read_blkbits
suffix:semicolon
DECL|member|capacity
r_int
r_int
id|capacity
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|mmc_host
suffix:semicolon
multiline_comment|/*&n; * MMC device&n; */
DECL|struct|mmc_card
r_struct
id|mmc_card
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in hosts devices list */
DECL|member|host
r_struct
id|mmc_host
op_star
id|host
suffix:semicolon
multiline_comment|/* the host this device belongs to */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* the device */
DECL|member|rca
r_int
r_int
id|rca
suffix:semicolon
multiline_comment|/* relative card address of device */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* (our) card state */
DECL|macro|MMC_STATE_PRESENT
mdefine_line|#define MMC_STATE_PRESENT&t;(1&lt;&lt;0)&t;&t;/* present in sysfs */
DECL|macro|MMC_STATE_DEAD
mdefine_line|#define MMC_STATE_DEAD&t;&t;(1&lt;&lt;1)&t;&t;/* device no longer in stack */
DECL|macro|MMC_STATE_BAD
mdefine_line|#define MMC_STATE_BAD&t;&t;(1&lt;&lt;2)&t;&t;/* unrecognised device */
DECL|member|raw_cid
id|u32
id|raw_cid
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* raw card CID */
DECL|member|raw_csd
id|u32
id|raw_csd
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* raw card CSD */
DECL|member|cid
r_struct
id|mmc_cid
id|cid
suffix:semicolon
multiline_comment|/* card identification */
DECL|member|csd
r_struct
id|mmc_csd
id|csd
suffix:semicolon
multiline_comment|/* card specific */
)brace
suffix:semicolon
DECL|macro|mmc_card_present
mdefine_line|#define mmc_card_present(c)&t;((c)-&gt;state &amp; MMC_STATE_PRESENT)
DECL|macro|mmc_card_dead
mdefine_line|#define mmc_card_dead(c)&t;((c)-&gt;state &amp; MMC_STATE_DEAD)
DECL|macro|mmc_card_bad
mdefine_line|#define mmc_card_bad(c)&t;&t;((c)-&gt;state &amp; MMC_STATE_BAD)
DECL|macro|mmc_card_set_present
mdefine_line|#define mmc_card_set_present(c)&t;((c)-&gt;state |= MMC_STATE_PRESENT)
DECL|macro|mmc_card_set_dead
mdefine_line|#define mmc_card_set_dead(c)&t;((c)-&gt;state |= MMC_STATE_DEAD)
DECL|macro|mmc_card_set_bad
mdefine_line|#define mmc_card_set_bad(c)&t;((c)-&gt;state |= MMC_STATE_BAD)
DECL|macro|mmc_card_name
mdefine_line|#define mmc_card_name(c)&t;((c)-&gt;cid.prod_name)
DECL|macro|mmc_card_id
mdefine_line|#define mmc_card_id(c)&t;&t;((c)-&gt;dev.bus_id)
DECL|macro|mmc_list_to_card
mdefine_line|#define mmc_list_to_card(l)&t;container_of(l, struct mmc_card, node)
DECL|macro|mmc_get_drvdata
mdefine_line|#define mmc_get_drvdata(c)&t;dev_get_drvdata(&amp;(c)-&gt;dev)
DECL|macro|mmc_set_drvdata
mdefine_line|#define mmc_set_drvdata(c,d)&t;dev_set_drvdata(&amp;(c)-&gt;dev, d)
multiline_comment|/*&n; * MMC device driver (e.g., Flash card, I/O card...)&n; */
DECL|struct|mmc_driver
r_struct
id|mmc_driver
(brace
DECL|member|drv
r_struct
id|device_driver
id|drv
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|mmc_card
op_star
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|mmc_card
op_star
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|mmc_card
op_star
comma
id|pm_message_t
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|mmc_card
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|mmc_register_driver
c_func
(paren
r_struct
id|mmc_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mmc_unregister_driver
c_func
(paren
r_struct
id|mmc_driver
op_star
)paren
suffix:semicolon
DECL|function|mmc_card_claim_host
r_static
r_inline
r_int
id|mmc_card_claim_host
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
(brace
r_return
id|__mmc_claim_host
c_func
(paren
id|card-&gt;host
comma
id|card
)paren
suffix:semicolon
)brace
DECL|macro|mmc_card_release_host
mdefine_line|#define mmc_card_release_host(c)&t;mmc_release_host((c)-&gt;host)
macro_line|#endif
eof
