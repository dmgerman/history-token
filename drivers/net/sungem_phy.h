macro_line|#ifndef __SUNGEM_PHY_H__
DECL|macro|__SUNGEM_PHY_H__
mdefine_line|#define __SUNGEM_PHY_H__
r_struct
id|mii_phy
suffix:semicolon
multiline_comment|/* Operations supported by any kind of PHY */
DECL|struct|mii_phy_ops
r_struct
id|mii_phy_ops
(brace
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|mii_phy
op_star
id|phy
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
id|mii_phy
op_star
id|phy
comma
r_int
id|wol_options
)paren
suffix:semicolon
DECL|member|setup_aneg
r_int
(paren
op_star
id|setup_aneg
)paren
(paren
r_struct
id|mii_phy
op_star
id|phy
comma
id|u32
id|advertise
)paren
suffix:semicolon
DECL|member|setup_forced
r_int
(paren
op_star
id|setup_forced
)paren
(paren
r_struct
id|mii_phy
op_star
id|phy
comma
r_int
id|speed
comma
r_int
id|fd
)paren
suffix:semicolon
DECL|member|poll_link
r_int
(paren
op_star
id|poll_link
)paren
(paren
r_struct
id|mii_phy
op_star
id|phy
)paren
suffix:semicolon
DECL|member|read_link
r_int
(paren
op_star
id|read_link
)paren
(paren
r_struct
id|mii_phy
op_star
id|phy
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure used to statically define an mii/gii based PHY */
DECL|struct|mii_phy_def
r_struct
id|mii_phy_def
(brace
DECL|member|phy_id
id|u32
id|phy_id
suffix:semicolon
multiline_comment|/* Concatenated ID1 &lt;&lt; 16 | ID2 */
DECL|member|phy_id_mask
id|u32
id|phy_id_mask
suffix:semicolon
multiline_comment|/* Significant bits */
DECL|member|features
id|u32
id|features
suffix:semicolon
multiline_comment|/* Ethtool SUPPORTED_* defines */
DECL|member|magic_aneg
r_int
id|magic_aneg
suffix:semicolon
multiline_comment|/* Autoneg does all speed test for us */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|ops
r_const
r_struct
id|mii_phy_ops
op_star
id|ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* An instance of a PHY, partially borrowed from mii_if_info */
DECL|struct|mii_phy
r_struct
id|mii_phy
(brace
DECL|member|def
r_struct
id|mii_phy_def
op_star
id|def
suffix:semicolon
DECL|member|advertising
r_int
id|advertising
suffix:semicolon
DECL|member|mii_id
r_int
id|mii_id
suffix:semicolon
multiline_comment|/* 1: autoneg enabled, 0: disabled */
DECL|member|autoneg
r_int
id|autoneg
suffix:semicolon
multiline_comment|/* forced speed &amp; duplex (no autoneg)&n;&t; * partner speed &amp; duplex &amp; pause (autoneg)&n;&t; */
DECL|member|speed
r_int
id|speed
suffix:semicolon
DECL|member|duplex
r_int
id|duplex
suffix:semicolon
DECL|member|pause
r_int
id|pause
suffix:semicolon
multiline_comment|/* Provided by host chip */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|mdio_read
r_int
(paren
op_star
id|mdio_read
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mii_id
comma
r_int
id|reg
)paren
suffix:semicolon
DECL|member|mdio_write
r_void
(paren
op_star
id|mdio_write
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mii_id
comma
r_int
id|reg
comma
r_int
id|val
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Pass in a struct mii_phy with dev, mdio_read and mdio_write&n; * filled, the remaining fields will be filled on return&n; */
r_extern
r_int
id|mii_phy_probe
c_func
(paren
r_struct
id|mii_phy
op_star
id|phy
comma
r_int
id|mii_id
)paren
suffix:semicolon
multiline_comment|/* MII definitions missing from mii.h */
DECL|macro|BMCR_SPD2
mdefine_line|#define BMCR_SPD2&t;0x0040&t;&t;/* Gigabit enable (bcm54xx)&t;*/
DECL|macro|LPA_PAUSE
mdefine_line|#define LPA_PAUSE&t;0x0400
multiline_comment|/* More PHY registers (model specific) */
multiline_comment|/* MII BCM5201 MULTIPHY interrupt register */
DECL|macro|MII_BCM5201_INTERRUPT
mdefine_line|#define MII_BCM5201_INTERRUPT&t;&t;&t;0x1A
DECL|macro|MII_BCM5201_INTERRUPT_INTENABLE
mdefine_line|#define MII_BCM5201_INTERRUPT_INTENABLE&t;&t;0x4000
DECL|macro|MII_BCM5201_AUXMODE2
mdefine_line|#define MII_BCM5201_AUXMODE2&t;&t;&t;0x1B
DECL|macro|MII_BCM5201_AUXMODE2_LOWPOWER
mdefine_line|#define MII_BCM5201_AUXMODE2_LOWPOWER&t;&t;0x0008
DECL|macro|MII_BCM5201_MULTIPHY
mdefine_line|#define MII_BCM5201_MULTIPHY                    0x1E
multiline_comment|/* MII BCM5201 MULTIPHY register bits */
DECL|macro|MII_BCM5201_MULTIPHY_SERIALMODE
mdefine_line|#define MII_BCM5201_MULTIPHY_SERIALMODE         0x0002
DECL|macro|MII_BCM5201_MULTIPHY_SUPERISOLATE
mdefine_line|#define MII_BCM5201_MULTIPHY_SUPERISOLATE       0x0008
multiline_comment|/* MII BCM5221 Additional registers */
DECL|macro|MII_BCM5221_TEST
mdefine_line|#define MII_BCM5221_TEST&t;&t;&t;0x1f
DECL|macro|MII_BCM5221_TEST_ENABLE_SHADOWS
mdefine_line|#define MII_BCM5221_TEST_ENABLE_SHADOWS&t;&t;0x0080
DECL|macro|MII_BCM5221_SHDOW_AUX_STAT2
mdefine_line|#define MII_BCM5221_SHDOW_AUX_STAT2&t;&t;0x1b
DECL|macro|MII_BCM5221_SHDOW_AUX_STAT2_APD
mdefine_line|#define MII_BCM5221_SHDOW_AUX_STAT2_APD&t;&t;0x0020
DECL|macro|MII_BCM5221_SHDOW_AUX_MODE4
mdefine_line|#define MII_BCM5221_SHDOW_AUX_MODE4&t;&t;0x1a
DECL|macro|MII_BCM5221_SHDOW_AUX_MODE4_CLKLOPWR
mdefine_line|#define MII_BCM5221_SHDOW_AUX_MODE4_CLKLOPWR&t;0x0004
multiline_comment|/* MII BCM5400 1000-BASET Control register */
DECL|macro|MII_BCM5400_GB_CONTROL
mdefine_line|#define MII_BCM5400_GB_CONTROL&t;&t;&t;0x09
DECL|macro|MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP
mdefine_line|#define MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP&t;0x0200
multiline_comment|/* MII BCM5400 AUXCONTROL register */
DECL|macro|MII_BCM5400_AUXCONTROL
mdefine_line|#define MII_BCM5400_AUXCONTROL                  0x18
DECL|macro|MII_BCM5400_AUXCONTROL_PWR10BASET
mdefine_line|#define MII_BCM5400_AUXCONTROL_PWR10BASET       0x0004
multiline_comment|/* MII BCM5400 AUXSTATUS register */
DECL|macro|MII_BCM5400_AUXSTATUS
mdefine_line|#define MII_BCM5400_AUXSTATUS                   0x19
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_MASK
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_MASK     0x0700
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT    8  
multiline_comment|/* 1000BT control (Marvell &amp; BCM54xx at least) */
DECL|macro|MII_1000BASETCONTROL
mdefine_line|#define MII_1000BASETCONTROL&t;&t;&t;0x09
DECL|macro|MII_1000BASETCONTROL_FULLDUPLEXCAP
mdefine_line|#define MII_1000BASETCONTROL_FULLDUPLEXCAP&t;0x0200
DECL|macro|MII_1000BASETCONTROL_HALFDUPLEXCAP
mdefine_line|#define MII_1000BASETCONTROL_HALFDUPLEXCAP&t;0x0100
multiline_comment|/* Marvell 88E1011 PHY control */
DECL|macro|MII_M1011_PHY_SPEC_CONTROL
mdefine_line|#define MII_M1011_PHY_SPEC_CONTROL&t;&t;0x10
DECL|macro|MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX
mdefine_line|#define MII_M1011_PHY_SPEC_CONTROL_MANUAL_MDIX&t;0x20
DECL|macro|MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX
mdefine_line|#define MII_M1011_PHY_SPEC_CONTROL_AUTO_MDIX&t;0x40
multiline_comment|/* Marvell 88E1011 PHY status */
DECL|macro|MII_M1011_PHY_SPEC_STATUS
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS&t;&t;0x11
DECL|macro|MII_M1011_PHY_SPEC_STATUS_1000
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_1000&t;&t;0x8000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_100
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_100&t;&t;0x4000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_SPD_MASK
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_SPD_MASK&t;0xc000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_FULLDUPLEX&t;0x2000
DECL|macro|MII_M1011_PHY_SPEC_STATUS_RESOLVED
mdefine_line|#define MII_M1011_PHY_SPEC_STATUS_RESOLVED&t;0x0800
macro_line|#endif /* __SUNGEM_PHY_H__ */
eof
