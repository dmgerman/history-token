multiline_comment|/*&n; * ibm_ocp.h&n; *&n; *      (c) Benjamin Herrenschmidt (benh@kernel.crashing.org)&n; *          Mipsys - France&n; *&n; *          Derived from work (c) Armin Kuster akuster@pacbell.net&n; *&n; *          Additional support and port to 2.6 LDM/sysfs by&n; *          Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *          Copyright 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __IBM_OCP_H__
DECL|macro|__IBM_OCP_H__
mdefine_line|#define __IBM_OCP_H__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * IBM 4xx OCP system information&n; */
DECL|struct|ocp_sys_info_data
r_struct
id|ocp_sys_info_data
(brace
DECL|member|opb_bus_freq
r_int
id|opb_bus_freq
suffix:semicolon
multiline_comment|/* OPB Bus Frequency (Hz) */
DECL|member|ebc_bus_freq
r_int
id|ebc_bus_freq
suffix:semicolon
multiline_comment|/* EBC Bus Frequency (Hz) */
)brace
suffix:semicolon
r_extern
r_struct
id|ocp_sys_info_data
id|ocp_sys_info
suffix:semicolon
multiline_comment|/*&n; * EMAC additional data and sysfs support&n; *&n; * Note about mdio_idx: When you have a zmii, it&squot;s usually&n; * not necessary, it covers the case of the 405EP which has&n; * the MDIO lines on EMAC0 only&n; *&n; * Note about phy_map: Per EMAC map of PHY ids which should&n; * be probed by emac_probe. Different EMACs can have&n; * overlapping maps.&n; *&n; * Note, this map uses inverse logic for bits:&n; *  0 - id should be probed&n; *  1 - id should be ignored&n; *&n; * Default value of 0x00000000 - will result in usual&n; * auto-detection logic.&n; *&n; */
DECL|struct|ocp_func_emac_data
r_struct
id|ocp_func_emac_data
(brace
DECL|member|rgmii_idx
r_int
id|rgmii_idx
suffix:semicolon
multiline_comment|/* RGMII device index or -1 */
DECL|member|rgmii_mux
r_int
id|rgmii_mux
suffix:semicolon
multiline_comment|/* RGMII input of this EMAC */
DECL|member|zmii_idx
r_int
id|zmii_idx
suffix:semicolon
multiline_comment|/* ZMII device index or -1 */
DECL|member|zmii_mux
r_int
id|zmii_mux
suffix:semicolon
multiline_comment|/* ZMII input of this EMAC */
DECL|member|mal_idx
r_int
id|mal_idx
suffix:semicolon
multiline_comment|/* MAL device index */
DECL|member|mal_rx_chan
r_int
id|mal_rx_chan
suffix:semicolon
multiline_comment|/* MAL rx channel number */
DECL|member|mal_tx_chan
r_int
id|mal_tx_chan
suffix:semicolon
multiline_comment|/* MAL tx channel number */
DECL|member|wol_irq
r_int
id|wol_irq
suffix:semicolon
multiline_comment|/* WOL interrupt */
DECL|member|mdio_idx
r_int
id|mdio_idx
suffix:semicolon
multiline_comment|/* EMAC idx of MDIO master or -1 */
DECL|member|tah_idx
r_int
id|tah_idx
suffix:semicolon
multiline_comment|/* TAH device index or -1 */
DECL|member|jumbo
r_int
id|jumbo
suffix:semicolon
multiline_comment|/* Jumbo frames capable flag */
DECL|member|phy_mode
r_int
id|phy_mode
suffix:semicolon
multiline_comment|/* PHY type or configurable mode */
DECL|member|mac_addr
id|u8
id|mac_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* EMAC mac address */
DECL|member|phy_map
id|u32
id|phy_map
suffix:semicolon
multiline_comment|/* EMAC phy map */
)brace
suffix:semicolon
multiline_comment|/* Sysfs support */
DECL|macro|OCP_SYSFS_EMAC_DATA
mdefine_line|#define OCP_SYSFS_EMAC_DATA()&t;&t;&t;&t;&t;&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, zmii_idx)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, zmii_mux)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, mal_idx)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, mal_rx_chan)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, mal_tx_chan)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, wol_irq)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_emac_data, &quot;%d&bslash;n&quot;, emac, mdio_idx)&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;void ocp_show_emac_data(struct device *dev)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_zmii_idx);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_zmii_mux);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_mal_idx);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_mal_rx_chan);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_mal_tx_chan);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_wol_irq);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_emac_mdio_idx);&t;&t;&bslash;&n;}
macro_line|#ifdef CONFIG_40x
multiline_comment|/*&n; * Helper function to copy MAC addresses from the bd_t to OCP EMAC&n; * additions.&n; *&n; * The range of EMAC indices (inclusive) to be copied are the arguments.&n; */
DECL|function|ibm_ocp_set_emac
r_static
r_inline
r_void
id|ibm_ocp_set_emac
c_func
(paren
r_int
id|start
comma
r_int
id|end
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ocp_def
op_star
id|def
suffix:semicolon
multiline_comment|/* Copy MAC addresses to EMAC additions */
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
op_le
id|end
suffix:semicolon
id|i
op_increment
)paren
(brace
id|def
op_assign
id|ocp_get_one_device
c_func
(paren
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_EMAC
comma
id|i
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
(paren
r_struct
id|ocp_func_emac_data
op_star
)paren
id|def-&gt;additions
)paren
op_member_access_from_pointer
id|mac_addr
comma
op_amp
id|__res.bi_enetaddr
(braket
id|i
)braket
comma
l_int|6
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * MAL additional data and sysfs support&n; */
DECL|struct|ocp_func_mal_data
r_struct
id|ocp_func_mal_data
(brace
DECL|member|num_tx_chans
r_int
id|num_tx_chans
suffix:semicolon
multiline_comment|/* Number of TX channels */
DECL|member|num_rx_chans
r_int
id|num_rx_chans
suffix:semicolon
multiline_comment|/* Number of RX channels */
DECL|member|txeob_irq
r_int
id|txeob_irq
suffix:semicolon
multiline_comment|/* TX End Of Buffer IRQ  */
DECL|member|rxeob_irq
r_int
id|rxeob_irq
suffix:semicolon
multiline_comment|/* RX End Of Buffer IRQ  */
DECL|member|txde_irq
r_int
id|txde_irq
suffix:semicolon
multiline_comment|/* TX Descriptor Error IRQ */
DECL|member|rxde_irq
r_int
id|rxde_irq
suffix:semicolon
multiline_comment|/* RX Descriptor Error IRQ */
DECL|member|serr_irq
r_int
id|serr_irq
suffix:semicolon
multiline_comment|/* MAL System Error IRQ    */
)brace
suffix:semicolon
DECL|macro|OCP_SYSFS_MAL_DATA
mdefine_line|#define OCP_SYSFS_MAL_DATA()&t;&t;&t;&t;&t;&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, num_tx_chans)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, num_rx_chans)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, txeob_irq)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, rxeob_irq)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, txde_irq)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, rxde_irq)&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_mal_data, &quot;%d&bslash;n&quot;, mal, serr_irq)&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;void ocp_show_mal_data(struct device *dev)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_num_tx_chans);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_num_rx_chans);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_txeob_irq);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_rxeob_irq);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_txde_irq);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_rxde_irq);&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_mal_serr_irq);&t;&t;&bslash;&n;}
multiline_comment|/*&n; * IIC additional data and sysfs support&n; */
DECL|struct|ocp_func_iic_data
r_struct
id|ocp_func_iic_data
(brace
DECL|member|fast_mode
r_int
id|fast_mode
suffix:semicolon
multiline_comment|/* IIC fast mode enabled */
)brace
suffix:semicolon
DECL|macro|OCP_SYSFS_IIC_DATA
mdefine_line|#define OCP_SYSFS_IIC_DATA()&t;&t;&t;&t;&t;&t;&bslash;&n;OCP_SYSFS_ADDTL(struct ocp_func_iic_data, &quot;%d&bslash;n&quot;, iic, fast_mode)&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;void ocp_show_iic_data(struct device *dev)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;device_create_file(dev, &amp;dev_attr_iic_fast_mode);&t;&t;&t;&bslash;&n;}
macro_line|#endif /* __IBM_OCP_H__ */
macro_line|#endif /* __KERNEL__ */
eof
