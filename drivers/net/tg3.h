multiline_comment|/* $Id: tg3.h,v 1.37.2.32 2002/03/11 12:18:18 davem Exp $&n; * tg3.h: Definitions for Broadcom Tigon3 ethernet driver.&n; *&n; * Copyright (C) 2001, 2002 David S. Miller (davem@redhat.com)&n; * Copyright (C) 2001 Jeff Garzik (jgarzik@mandrakesoft.com)&n; */
macro_line|#ifndef _T3_H
DECL|macro|_T3_H
mdefine_line|#define _T3_H
DECL|macro|TG3_64BIT_REG_HIGH
mdefine_line|#define TG3_64BIT_REG_HIGH&t;&t;0x00UL
DECL|macro|TG3_64BIT_REG_LOW
mdefine_line|#define TG3_64BIT_REG_LOW&t;&t;0x04UL
multiline_comment|/* Descriptor block info. */
DECL|macro|TG3_BDINFO_HOST_ADDR
mdefine_line|#define TG3_BDINFO_HOST_ADDR&t;&t;0x0UL /* 64-bit */
DECL|macro|TG3_BDINFO_MAXLEN_FLAGS
mdefine_line|#define TG3_BDINFO_MAXLEN_FLAGS&t;&t;0x8UL /* 32-bit */
DECL|macro|BDINFO_FLAGS_USE_EXT_RECV
mdefine_line|#define  BDINFO_FLAGS_USE_EXT_RECV&t; 0x00000001 /* ext rx_buffer_desc */
DECL|macro|BDINFO_FLAGS_DISABLED
mdefine_line|#define  BDINFO_FLAGS_DISABLED&t;&t; 0x00000002
DECL|macro|BDINFO_FLAGS_MAXLEN_MASK
mdefine_line|#define  BDINFO_FLAGS_MAXLEN_MASK&t; 0xffff0000
DECL|macro|BDINFO_FLAGS_MAXLEN_SHIFT
mdefine_line|#define  BDINFO_FLAGS_MAXLEN_SHIFT&t; 16
DECL|macro|TG3_BDINFO_NIC_ADDR
mdefine_line|#define TG3_BDINFO_NIC_ADDR&t;&t;0xcUL /* 32-bit */
DECL|macro|TG3_BDINFO_SIZE
mdefine_line|#define TG3_BDINFO_SIZE&t;&t;&t;0x10UL
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  &t;&t;256
DECL|macro|RX_STD_MAX_SIZE
mdefine_line|#define RX_STD_MAX_SIZE&t;&t;&t;1536
DECL|macro|RX_JUMBO_MAX_SIZE
mdefine_line|#define RX_JUMBO_MAX_SIZE&t;&t;0xdeadbeef /* XXX */
macro_line|#if TG3_MINI_RING_WORKS
DECL|macro|RX_MINI_MAX_SIZE
mdefine_line|#define RX_MINI_MAX_SIZE&t;&t;256
macro_line|#endif
multiline_comment|/* First 256 bytes are a mirror of PCI config space. */
DECL|macro|TG3PCI_VENDOR
mdefine_line|#define TG3PCI_VENDOR&t;&t;&t;0x00000000
DECL|macro|TG3PCI_VENDOR_BROADCOM
mdefine_line|#define  TG3PCI_VENDOR_BROADCOM&t;&t; 0x14e4
DECL|macro|TG3PCI_DEVICE
mdefine_line|#define TG3PCI_DEVICE&t;&t;&t;0x00000002
DECL|macro|TG3PCI_DEVICE_TIGON3_1
mdefine_line|#define  TG3PCI_DEVICE_TIGON3_1&t;&t; 0x1644 /* BCM5700 */
DECL|macro|TG3PCI_DEVICE_TIGON3_2
mdefine_line|#define  TG3PCI_DEVICE_TIGON3_2&t;&t; 0x1645 /* BCM5701 */
DECL|macro|TG3PCI_DEVICE_TIGON3_3
mdefine_line|#define  TG3PCI_DEVICE_TIGON3_3&t;&t; 0x1646 /* BCM5702 */
DECL|macro|TG3PCI_DEVICE_TIGON3_4
mdefine_line|#define  TG3PCI_DEVICE_TIGON3_4&t;&t; 0x1647 /* BCM5703 */
DECL|macro|TG3PCI_COMMAND
mdefine_line|#define TG3PCI_COMMAND&t;&t;&t;0x00000004
DECL|macro|TG3PCI_STATUS
mdefine_line|#define TG3PCI_STATUS&t;&t;&t;0x00000006
DECL|macro|TG3PCI_CCREVID
mdefine_line|#define TG3PCI_CCREVID&t;&t;&t;0x00000008
DECL|macro|TG3PCI_CACHELINESZ
mdefine_line|#define TG3PCI_CACHELINESZ&t;&t;0x0000000c
DECL|macro|TG3PCI_LATTIMER
mdefine_line|#define TG3PCI_LATTIMER&t;&t;&t;0x0000000d
DECL|macro|TG3PCI_HEADERTYPE
mdefine_line|#define TG3PCI_HEADERTYPE&t;&t;0x0000000e
DECL|macro|TG3PCI_BIST
mdefine_line|#define TG3PCI_BIST&t;&t;&t;0x0000000f
DECL|macro|TG3PCI_BASE0_LOW
mdefine_line|#define TG3PCI_BASE0_LOW&t;&t;0x00000010
DECL|macro|TG3PCI_BASE0_HIGH
mdefine_line|#define TG3PCI_BASE0_HIGH&t;&t;0x00000014
multiline_comment|/* 0x18 --&gt; 0x2c unused */
DECL|macro|TG3PCI_SUBSYSVENID
mdefine_line|#define TG3PCI_SUBSYSVENID&t;&t;0x0000002c
DECL|macro|TG3PCI_SUBSYSID
mdefine_line|#define TG3PCI_SUBSYSID&t;&t;&t;0x0000002e
DECL|macro|TG3PCI_ROMADDR
mdefine_line|#define TG3PCI_ROMADDR&t;&t;&t;0x00000030
DECL|macro|TG3PCI_CAPLIST
mdefine_line|#define TG3PCI_CAPLIST&t;&t;&t;0x00000034
multiline_comment|/* 0x35 --&gt; 0x3c unused */
DECL|macro|TG3PCI_IRQ_LINE
mdefine_line|#define TG3PCI_IRQ_LINE&t;&t;&t;0x0000003c
DECL|macro|TG3PCI_IRQ_PIN
mdefine_line|#define TG3PCI_IRQ_PIN&t;&t;&t;0x0000003d
DECL|macro|TG3PCI_MIN_GNT
mdefine_line|#define TG3PCI_MIN_GNT&t;&t;&t;0x0000003e
DECL|macro|TG3PCI_MAX_LAT
mdefine_line|#define TG3PCI_MAX_LAT&t;&t;&t;0x0000003f
DECL|macro|TG3PCI_X_CAPS
mdefine_line|#define TG3PCI_X_CAPS&t;&t;&t;0x00000040
DECL|macro|PCIX_CAPS_RELAXED_ORDERING
mdefine_line|#define  PCIX_CAPS_RELAXED_ORDERING&t; 0x00020000
DECL|macro|TG3PCI_PM_CAP_PTR
mdefine_line|#define TG3PCI_PM_CAP_PTR&t;&t;0x00000041
DECL|macro|TG3PCI_X_COMMAND
mdefine_line|#define TG3PCI_X_COMMAND&t;&t;0x00000042
DECL|macro|TG3PCI_X_STATUS
mdefine_line|#define TG3PCI_X_STATUS&t;&t;&t;0x00000044
DECL|macro|TG3PCI_PM_CAP_ID
mdefine_line|#define TG3PCI_PM_CAP_ID&t;&t;0x00000048
DECL|macro|TG3PCI_VPD_CAP_PTR
mdefine_line|#define TG3PCI_VPD_CAP_PTR&t;&t;0x00000049
DECL|macro|TG3PCI_PM_CAPS
mdefine_line|#define TG3PCI_PM_CAPS&t;&t;&t;0x0000004a
DECL|macro|TG3PCI_PM_CTRL_STAT
mdefine_line|#define TG3PCI_PM_CTRL_STAT&t;&t;0x0000004c
DECL|macro|TG3PCI_BR_SUPP_EXT
mdefine_line|#define TG3PCI_BR_SUPP_EXT&t;&t;0x0000004e
DECL|macro|TG3PCI_PM_DATA
mdefine_line|#define TG3PCI_PM_DATA&t;&t;&t;0x0000004f
DECL|macro|TG3PCI_VPD_CAP_ID
mdefine_line|#define TG3PCI_VPD_CAP_ID&t;&t;0x00000050
DECL|macro|TG3PCI_MSI_CAP_PTR
mdefine_line|#define TG3PCI_MSI_CAP_PTR&t;&t;0x00000051
DECL|macro|TG3PCI_VPD_ADDR_FLAG
mdefine_line|#define TG3PCI_VPD_ADDR_FLAG&t;&t;0x00000052
DECL|macro|VPD_ADDR_FLAG_WRITE
mdefine_line|#define  VPD_ADDR_FLAG_WRITE&t;&t;0x00008000
DECL|macro|TG3PCI_VPD_DATA
mdefine_line|#define TG3PCI_VPD_DATA&t;&t;&t;0x00000054
DECL|macro|TG3PCI_MSI_CAP_ID
mdefine_line|#define TG3PCI_MSI_CAP_ID&t;&t;0x00000058
DECL|macro|TG3PCI_NXT_CAP_PTR
mdefine_line|#define TG3PCI_NXT_CAP_PTR&t;&t;0x00000059
DECL|macro|TG3PCI_MSI_CTRL
mdefine_line|#define TG3PCI_MSI_CTRL&t;&t;&t;0x0000005a
DECL|macro|TG3PCI_MSI_ADDR_LOW
mdefine_line|#define TG3PCI_MSI_ADDR_LOW&t;&t;0x0000005c
DECL|macro|TG3PCI_MSI_ADDR_HIGH
mdefine_line|#define TG3PCI_MSI_ADDR_HIGH&t;&t;0x00000060
DECL|macro|TG3PCI_MSI_DATA
mdefine_line|#define TG3PCI_MSI_DATA&t;&t;&t;0x00000064
multiline_comment|/* 0x66 --&gt; 0x68 unused */
DECL|macro|TG3PCI_MISC_HOST_CTRL
mdefine_line|#define TG3PCI_MISC_HOST_CTRL&t;&t;0x00000068
DECL|macro|MISC_HOST_CTRL_CLEAR_INT
mdefine_line|#define  MISC_HOST_CTRL_CLEAR_INT&t; 0x00000001
DECL|macro|MISC_HOST_CTRL_MASK_PCI_INT
mdefine_line|#define  MISC_HOST_CTRL_MASK_PCI_INT&t; 0x00000002
DECL|macro|MISC_HOST_CTRL_BYTE_SWAP
mdefine_line|#define  MISC_HOST_CTRL_BYTE_SWAP&t; 0x00000004
DECL|macro|MISC_HOST_CTRL_WORD_SWAP
mdefine_line|#define  MISC_HOST_CTRL_WORD_SWAP&t; 0x00000008
DECL|macro|MISC_HOST_CTRL_PCISTATE_RW
mdefine_line|#define  MISC_HOST_CTRL_PCISTATE_RW&t; 0x00000010
DECL|macro|MISC_HOST_CTRL_CLKREG_RW
mdefine_line|#define  MISC_HOST_CTRL_CLKREG_RW&t; 0x00000020
DECL|macro|MISC_HOST_CTRL_REGWORD_SWAP
mdefine_line|#define  MISC_HOST_CTRL_REGWORD_SWAP&t; 0x00000040
DECL|macro|MISC_HOST_CTRL_INDIR_ACCESS
mdefine_line|#define  MISC_HOST_CTRL_INDIR_ACCESS&t; 0x00000080
DECL|macro|MISC_HOST_CTRL_IRQ_MASK_MODE
mdefine_line|#define  MISC_HOST_CTRL_IRQ_MASK_MODE&t; 0x00000100
DECL|macro|MISC_HOST_CTRL_TAGGED_STATUS
mdefine_line|#define  MISC_HOST_CTRL_TAGGED_STATUS&t; 0x00000200
DECL|macro|MISC_HOST_CTRL_CHIPREV
mdefine_line|#define  MISC_HOST_CTRL_CHIPREV&t;&t; 0xffff0000
DECL|macro|MISC_HOST_CTRL_CHIPREV_SHIFT
mdefine_line|#define  MISC_HOST_CTRL_CHIPREV_SHIFT&t; 16
DECL|macro|GET_CHIP_REV_ID
mdefine_line|#define  GET_CHIP_REV_ID(MISC_HOST_CTRL) &bslash;&n;&t; (((MISC_HOST_CTRL) &amp; MISC_HOST_CTRL_CHIPREV) &gt;&gt; &bslash;&n;&t;  MISC_HOST_CTRL_CHIPREV_SHIFT)
DECL|macro|CHIPREV_ID_5700_A0
mdefine_line|#define  CHIPREV_ID_5700_A0&t;&t; 0x7000
DECL|macro|CHIPREV_ID_5700_A1
mdefine_line|#define  CHIPREV_ID_5700_A1&t;&t; 0x7001
DECL|macro|CHIPREV_ID_5700_B0
mdefine_line|#define  CHIPREV_ID_5700_B0&t;&t; 0x7100
DECL|macro|CHIPREV_ID_5700_B1
mdefine_line|#define  CHIPREV_ID_5700_B1&t;&t; 0x7101
DECL|macro|CHIPREV_ID_5700_B3
mdefine_line|#define  CHIPREV_ID_5700_B3&t;&t; 0x7102
DECL|macro|CHIPREV_ID_5700_ALTIMA
mdefine_line|#define  CHIPREV_ID_5700_ALTIMA&t;&t; 0x7104
DECL|macro|CHIPREV_ID_5700_C0
mdefine_line|#define  CHIPREV_ID_5700_C0&t;&t; 0x7200
DECL|macro|CHIPREV_ID_5701_A0
mdefine_line|#define  CHIPREV_ID_5701_A0&t;&t; 0x0000
DECL|macro|CHIPREV_ID_5701_B0
mdefine_line|#define  CHIPREV_ID_5701_B0&t;&t; 0x0100
DECL|macro|CHIPREV_ID_5701_B2
mdefine_line|#define  CHIPREV_ID_5701_B2&t;&t; 0x0102
DECL|macro|CHIPREV_ID_5701_B5
mdefine_line|#define  CHIPREV_ID_5701_B5&t;&t; 0x0105
DECL|macro|CHIPREV_ID_5703_A0
mdefine_line|#define  CHIPREV_ID_5703_A0&t;&t; 0x1000
DECL|macro|CHIPREV_ID_5703_A1
mdefine_line|#define  CHIPREV_ID_5703_A1&t;&t; 0x1001
DECL|macro|CHIPREV_ID_5703_A2
mdefine_line|#define  CHIPREV_ID_5703_A2&t;&t; 0x1002
DECL|macro|GET_ASIC_REV
mdefine_line|#define  GET_ASIC_REV(CHIP_REV_ID)&t;((CHIP_REV_ID) &gt;&gt; 12)
DECL|macro|ASIC_REV_5700
mdefine_line|#define   ASIC_REV_5700&t;&t;&t; 0x07
DECL|macro|ASIC_REV_5701
mdefine_line|#define   ASIC_REV_5701&t;&t;&t; 0x00
DECL|macro|ASIC_REV_5703
mdefine_line|#define   ASIC_REV_5703&t;&t;&t; 0x01
DECL|macro|GET_CHIP_REV
mdefine_line|#define  GET_CHIP_REV(CHIP_REV_ID)&t;((CHIP_REV_ID) &gt;&gt; 8)
DECL|macro|CHIPREV_5700_AX
mdefine_line|#define   CHIPREV_5700_AX&t;&t; 0x70
DECL|macro|CHIPREV_5700_BX
mdefine_line|#define   CHIPREV_5700_BX&t;&t; 0x71
DECL|macro|CHIPREV_5700_CX
mdefine_line|#define   CHIPREV_5700_CX&t;&t; 0x72
DECL|macro|CHIPREV_5701_AX
mdefine_line|#define   CHIPREV_5701_AX&t;&t; 0x00
DECL|macro|GET_METAL_REV
mdefine_line|#define  GET_METAL_REV(CHIP_REV_ID)&t;((CHIP_REV_ID) &amp; 0xff)
DECL|macro|METAL_REV_A0
mdefine_line|#define   METAL_REV_A0&t;&t;&t; 0x00
DECL|macro|METAL_REV_A1
mdefine_line|#define   METAL_REV_A1&t;&t;&t; 0x01
DECL|macro|METAL_REV_B0
mdefine_line|#define   METAL_REV_B0&t;&t;&t; 0x00
DECL|macro|METAL_REV_B1
mdefine_line|#define   METAL_REV_B1&t;&t;&t; 0x01
DECL|macro|METAL_REV_B2
mdefine_line|#define   METAL_REV_B2&t;&t;&t; 0x02
DECL|macro|TG3PCI_DMA_RW_CTRL
mdefine_line|#define TG3PCI_DMA_RW_CTRL&t;&t;0x0000006c
DECL|macro|DMA_RWCTRL_MIN_DMA
mdefine_line|#define  DMA_RWCTRL_MIN_DMA&t;&t; 0x000000ff
DECL|macro|DMA_RWCTRL_MIN_DMA_SHIFT
mdefine_line|#define  DMA_RWCTRL_MIN_DMA_SHIFT&t; 0
DECL|macro|DMA_RWCTRL_READ_BNDRY_MASK
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_MASK&t; 0x00000700
DECL|macro|DMA_RWCTRL_READ_BNDRY_DISAB
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_DISAB&t; 0x00000000
DECL|macro|DMA_RWCTRL_READ_BNDRY_16
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_16&t; 0x00000100
DECL|macro|DMA_RWCTRL_READ_BNDRY_32
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_32&t; 0x00000200
DECL|macro|DMA_RWCTRL_READ_BNDRY_64
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_64&t; 0x00000300
DECL|macro|DMA_RWCTRL_READ_BNDRY_128
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_128&t; 0x00000400
DECL|macro|DMA_RWCTRL_READ_BNDRY_256
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_256&t; 0x00000500
DECL|macro|DMA_RWCTRL_READ_BNDRY_512
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_512&t; 0x00000600
DECL|macro|DMA_RWCTRL_READ_BNDRY_1024
mdefine_line|#define  DMA_RWCTRL_READ_BNDRY_1024&t; 0x00000700
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_MASK
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_MASK&t; 0x00003800
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_DISAB
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_DISAB&t; 0x00000000
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_16
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_16&t; 0x00000800
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_32
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_32&t; 0x00001000
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_64
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_64&t; 0x00001800
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_128
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_128&t; 0x00002000
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_256
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_256&t; 0x00002800
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_512
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_512&t; 0x00003000
DECL|macro|DMA_RWCTRL_WRITE_BNDRY_1024
mdefine_line|#define  DMA_RWCTRL_WRITE_BNDRY_1024&t; 0x00003800
DECL|macro|DMA_RWCTRL_ONE_DMA
mdefine_line|#define  DMA_RWCTRL_ONE_DMA&t;&t; 0x00004000
DECL|macro|DMA_RWCTRL_READ_WATER
mdefine_line|#define  DMA_RWCTRL_READ_WATER&t;&t; 0x00070000
DECL|macro|DMA_RWCTRL_READ_WATER_SHIFT
mdefine_line|#define  DMA_RWCTRL_READ_WATER_SHIFT&t; 16
DECL|macro|DMA_RWCTRL_WRITE_WATER
mdefine_line|#define  DMA_RWCTRL_WRITE_WATER&t;&t; 0x00380000
DECL|macro|DMA_RWCTRL_WRITE_WATER_SHIFT
mdefine_line|#define  DMA_RWCTRL_WRITE_WATER_SHIFT&t; 19
DECL|macro|DMA_RWCTRL_USE_MEM_READ_MULT
mdefine_line|#define  DMA_RWCTRL_USE_MEM_READ_MULT&t; 0x00400000
DECL|macro|DMA_RWCTRL_ASSERT_ALL_BE
mdefine_line|#define  DMA_RWCTRL_ASSERT_ALL_BE&t; 0x00800000
DECL|macro|DMA_RWCTRL_PCI_READ_CMD
mdefine_line|#define  DMA_RWCTRL_PCI_READ_CMD&t; 0x0f000000
DECL|macro|DMA_RWCTRL_PCI_READ_CMD_SHIFT
mdefine_line|#define  DMA_RWCTRL_PCI_READ_CMD_SHIFT&t; 24
DECL|macro|DMA_RWCTRL_PCI_WRITE_CMD
mdefine_line|#define  DMA_RWCTRL_PCI_WRITE_CMD&t; 0xf0000000
DECL|macro|DMA_RWCTRL_PCI_WRITE_CMD_SHIFT
mdefine_line|#define  DMA_RWCTRL_PCI_WRITE_CMD_SHIFT&t; 28
DECL|macro|TG3PCI_PCISTATE
mdefine_line|#define TG3PCI_PCISTATE&t;&t;&t;0x00000070
DECL|macro|PCISTATE_FORCE_RESET
mdefine_line|#define  PCISTATE_FORCE_RESET&t;&t; 0x00000001
DECL|macro|PCISTATE_INT_NOT_ACTIVE
mdefine_line|#define  PCISTATE_INT_NOT_ACTIVE&t; 0x00000002
DECL|macro|PCISTATE_CONV_PCI_MODE
mdefine_line|#define  PCISTATE_CONV_PCI_MODE&t;&t; 0x00000004
DECL|macro|PCISTATE_BUS_SPEED_HIGH
mdefine_line|#define  PCISTATE_BUS_SPEED_HIGH&t; 0x00000008
DECL|macro|PCISTATE_BUS_32BIT
mdefine_line|#define  PCISTATE_BUS_32BIT&t;&t; 0x00000010
DECL|macro|PCISTATE_ROM_ENABLE
mdefine_line|#define  PCISTATE_ROM_ENABLE&t;&t; 0x00000020
DECL|macro|PCISTATE_ROM_RETRY_ENABLE
mdefine_line|#define  PCISTATE_ROM_RETRY_ENABLE&t; 0x00000040
DECL|macro|PCISTATE_FLAT_VIEW
mdefine_line|#define  PCISTATE_FLAT_VIEW&t;&t; 0x00000100
DECL|macro|TG3PCI_CLOCK_CTRL
mdefine_line|#define TG3PCI_CLOCK_CTRL&t;&t;0x00000074
DECL|macro|CLOCK_CTRL_CORECLK_DISABLE
mdefine_line|#define  CLOCK_CTRL_CORECLK_DISABLE&t; 0x00000200
DECL|macro|CLOCK_CTRL_RXCLK_DISABLE
mdefine_line|#define  CLOCK_CTRL_RXCLK_DISABLE&t; 0x00000400
DECL|macro|CLOCK_CTRL_TXCLK_DISABLE
mdefine_line|#define  CLOCK_CTRL_TXCLK_DISABLE&t; 0x00000800
DECL|macro|CLOCK_CTRL_ALTCLK
mdefine_line|#define  CLOCK_CTRL_ALTCLK&t;&t; 0x00001000
DECL|macro|CLOCK_CTRL_PWRDOWN_PLL133
mdefine_line|#define  CLOCK_CTRL_PWRDOWN_PLL133&t; 0x00008000
DECL|macro|CLOCK_CTRL_44MHZ_CORE
mdefine_line|#define  CLOCK_CTRL_44MHZ_CORE&t;&t; 0x00040000
DECL|macro|CLOCK_CTRL_DELAY_PCI_GRANT
mdefine_line|#define  CLOCK_CTRL_DELAY_PCI_GRANT&t; 0x80000000
DECL|macro|TG3PCI_REG_BASE_ADDR
mdefine_line|#define TG3PCI_REG_BASE_ADDR&t;&t;0x00000078
DECL|macro|TG3PCI_MEM_WIN_BASE_ADDR
mdefine_line|#define TG3PCI_MEM_WIN_BASE_ADDR&t;0x0000007c
DECL|macro|TG3PCI_REG_DATA
mdefine_line|#define TG3PCI_REG_DATA&t;&t;&t;0x00000080
DECL|macro|TG3PCI_MEM_WIN_DATA
mdefine_line|#define TG3PCI_MEM_WIN_DATA&t;&t;0x00000084
DECL|macro|TG3PCI_MODE_CTRL
mdefine_line|#define TG3PCI_MODE_CTRL&t;&t;0x00000088
DECL|macro|TG3PCI_MISC_CFG
mdefine_line|#define TG3PCI_MISC_CFG&t;&t;&t;0x0000008c
DECL|macro|TG3PCI_MISC_LOCAL_CTRL
mdefine_line|#define TG3PCI_MISC_LOCAL_CTRL&t;&t;0x00000090
multiline_comment|/* 0x94 --&gt; 0x98 unused */
DECL|macro|TG3PCI_STD_RING_PROD_IDX
mdefine_line|#define TG3PCI_STD_RING_PROD_IDX&t;0x00000098 /* 64-bit */
DECL|macro|TG3PCI_RCV_RET_RING_CON_IDX
mdefine_line|#define TG3PCI_RCV_RET_RING_CON_IDX&t;0x000000a0 /* 64-bit */
DECL|macro|TG3PCI_SND_PROD_IDX
mdefine_line|#define TG3PCI_SND_PROD_IDX&t;&t;0x000000a8 /* 64-bit */
multiline_comment|/* 0xb0 --&gt; 0x100 unused */
multiline_comment|/* 0x100 --&gt; 0x200 unused */
multiline_comment|/* Mailbox registers */
DECL|macro|MAILBOX_INTERRUPT_0
mdefine_line|#define MAILBOX_INTERRUPT_0&t;&t;0x00000200 /* 64-bit */
DECL|macro|MAILBOX_INTERRUPT_1
mdefine_line|#define MAILBOX_INTERRUPT_1&t;&t;0x00000208 /* 64-bit */
DECL|macro|MAILBOX_INTERRUPT_2
mdefine_line|#define MAILBOX_INTERRUPT_2&t;&t;0x00000210 /* 64-bit */
DECL|macro|MAILBOX_INTERRUPT_3
mdefine_line|#define MAILBOX_INTERRUPT_3&t;&t;0x00000218 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_0
mdefine_line|#define MAILBOX_GENERAL_0&t;&t;0x00000220 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_1
mdefine_line|#define MAILBOX_GENERAL_1&t;&t;0x00000228 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_2
mdefine_line|#define MAILBOX_GENERAL_2&t;&t;0x00000230 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_3
mdefine_line|#define MAILBOX_GENERAL_3&t;&t;0x00000238 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_4
mdefine_line|#define MAILBOX_GENERAL_4&t;&t;0x00000240 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_5
mdefine_line|#define MAILBOX_GENERAL_5&t;&t;0x00000248 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_6
mdefine_line|#define MAILBOX_GENERAL_6&t;&t;0x00000250 /* 64-bit */
DECL|macro|MAILBOX_GENERAL_7
mdefine_line|#define MAILBOX_GENERAL_7&t;&t;0x00000258 /* 64-bit */
DECL|macro|MAILBOX_RELOAD_STAT
mdefine_line|#define MAILBOX_RELOAD_STAT&t;&t;0x00000260 /* 64-bit */
DECL|macro|MAILBOX_RCV_STD_PROD_IDX
mdefine_line|#define MAILBOX_RCV_STD_PROD_IDX&t;0x00000268 /* 64-bit */
DECL|macro|MAILBOX_RCV_JUMBO_PROD_IDX
mdefine_line|#define MAILBOX_RCV_JUMBO_PROD_IDX&t;0x00000270 /* 64-bit */
DECL|macro|MAILBOX_RCV_MINI_PROD_IDX
mdefine_line|#define MAILBOX_RCV_MINI_PROD_IDX&t;0x00000278 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_0
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_0&t;0x00000280 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_1
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_1&t;0x00000288 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_2
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_2&t;0x00000290 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_3
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_3&t;0x00000298 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_4
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_4&t;0x000002a0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_5
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_5&t;0x000002a8 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_6
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_6&t;0x000002b0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_7
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_7&t;0x000002b8 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_8
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_8&t;0x000002c0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_9
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_9&t;0x000002c8 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_10
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_10&t;0x000002d0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_11
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_11&t;0x000002d8 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_12
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_12&t;0x000002e0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_13
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_13&t;0x000002e8 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_14
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_14&t;0x000002f0 /* 64-bit */
DECL|macro|MAILBOX_RCVRET_CON_IDX_15
mdefine_line|#define MAILBOX_RCVRET_CON_IDX_15&t;0x000002f8 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_0
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_0&t;0x00000300 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_1
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_1&t;0x00000308 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_2
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_2&t;0x00000310 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_3
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_3&t;0x00000318 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_4
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_4&t;0x00000320 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_5
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_5&t;0x00000328 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_6
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_6&t;0x00000330 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_7
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_7&t;0x00000338 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_8
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_8&t;0x00000340 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_9
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_9&t;0x00000348 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_10
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_10&t;0x00000350 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_11
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_11&t;0x00000358 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_12
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_12&t;0x00000360 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_13
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_13&t;0x00000368 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_14
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_14&t;0x00000370 /* 64-bit */
DECL|macro|MAILBOX_SNDHOST_PROD_IDX_15
mdefine_line|#define MAILBOX_SNDHOST_PROD_IDX_15&t;0x00000378 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_0
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_0&t;0x00000380 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_1
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_1&t;0x00000388 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_2
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_2&t;0x00000390 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_3
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_3&t;0x00000398 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_4
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_4&t;0x000003a0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_5
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_5&t;0x000003a8 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_6
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_6&t;0x000003b0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_7
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_7&t;0x000003b8 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_8
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_8&t;0x000003c0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_9
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_9&t;0x000003c8 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_10
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_10&t;0x000003d0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_11
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_11&t;0x000003d8 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_12
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_12&t;0x000003e0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_13
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_13&t;0x000003e8 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_14
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_14&t;0x000003f0 /* 64-bit */
DECL|macro|MAILBOX_SNDNIC_PROD_IDX_15
mdefine_line|#define MAILBOX_SNDNIC_PROD_IDX_15&t;0x000003f8 /* 64-bit */
multiline_comment|/* MAC control registers */
DECL|macro|MAC_MODE
mdefine_line|#define MAC_MODE&t;&t;&t;0x00000400
DECL|macro|MAC_MODE_RESET
mdefine_line|#define  MAC_MODE_RESET&t;&t;&t; 0x00000001
DECL|macro|MAC_MODE_HALF_DUPLEX
mdefine_line|#define  MAC_MODE_HALF_DUPLEX&t;&t; 0x00000002
DECL|macro|MAC_MODE_PORT_MODE_MASK
mdefine_line|#define  MAC_MODE_PORT_MODE_MASK&t; 0x0000000c
DECL|macro|MAC_MODE_PORT_MODE_TBI
mdefine_line|#define  MAC_MODE_PORT_MODE_TBI&t;&t; 0x0000000c
DECL|macro|MAC_MODE_PORT_MODE_GMII
mdefine_line|#define  MAC_MODE_PORT_MODE_GMII&t; 0x00000008
DECL|macro|MAC_MODE_PORT_MODE_MII
mdefine_line|#define  MAC_MODE_PORT_MODE_MII&t;&t; 0x00000004
DECL|macro|MAC_MODE_PORT_MODE_NONE
mdefine_line|#define  MAC_MODE_PORT_MODE_NONE&t; 0x00000000
DECL|macro|MAC_MODE_PORT_INT_LPBACK
mdefine_line|#define  MAC_MODE_PORT_INT_LPBACK&t; 0x00000010
DECL|macro|MAC_MODE_TAGGED_MAC_CTRL
mdefine_line|#define  MAC_MODE_TAGGED_MAC_CTRL&t; 0x00000080
DECL|macro|MAC_MODE_TX_BURSTING
mdefine_line|#define  MAC_MODE_TX_BURSTING&t;&t; 0x00000100
DECL|macro|MAC_MODE_MAX_DEFER
mdefine_line|#define  MAC_MODE_MAX_DEFER&t;&t; 0x00000200
DECL|macro|MAC_MODE_LINK_POLARITY
mdefine_line|#define  MAC_MODE_LINK_POLARITY&t;&t; 0x00000400
DECL|macro|MAC_MODE_RXSTAT_ENABLE
mdefine_line|#define  MAC_MODE_RXSTAT_ENABLE&t;&t; 0x00000800
DECL|macro|MAC_MODE_RXSTAT_CLEAR
mdefine_line|#define  MAC_MODE_RXSTAT_CLEAR&t;&t; 0x00001000
DECL|macro|MAC_MODE_RXSTAT_FLUSH
mdefine_line|#define  MAC_MODE_RXSTAT_FLUSH&t;&t; 0x00002000
DECL|macro|MAC_MODE_TXSTAT_ENABLE
mdefine_line|#define  MAC_MODE_TXSTAT_ENABLE&t;&t; 0x00004000
DECL|macro|MAC_MODE_TXSTAT_CLEAR
mdefine_line|#define  MAC_MODE_TXSTAT_CLEAR&t;&t; 0x00008000
DECL|macro|MAC_MODE_TXSTAT_FLUSH
mdefine_line|#define  MAC_MODE_TXSTAT_FLUSH&t;&t; 0x00010000
DECL|macro|MAC_MODE_SEND_CONFIGS
mdefine_line|#define  MAC_MODE_SEND_CONFIGS&t;&t; 0x00020000
DECL|macro|MAC_MODE_MAGIC_PKT_ENABLE
mdefine_line|#define  MAC_MODE_MAGIC_PKT_ENABLE&t; 0x00040000
DECL|macro|MAC_MODE_ACPI_ENABLE
mdefine_line|#define  MAC_MODE_ACPI_ENABLE&t;&t; 0x00080000
DECL|macro|MAC_MODE_MIP_ENABLE
mdefine_line|#define  MAC_MODE_MIP_ENABLE&t;&t; 0x00100000
DECL|macro|MAC_MODE_TDE_ENABLE
mdefine_line|#define  MAC_MODE_TDE_ENABLE&t;&t; 0x00200000
DECL|macro|MAC_MODE_RDE_ENABLE
mdefine_line|#define  MAC_MODE_RDE_ENABLE&t;&t; 0x00400000
DECL|macro|MAC_MODE_FHDE_ENABLE
mdefine_line|#define  MAC_MODE_FHDE_ENABLE&t;&t; 0x00800000
DECL|macro|MAC_STATUS
mdefine_line|#define MAC_STATUS&t;&t;&t;0x00000404
DECL|macro|MAC_STATUS_PCS_SYNCED
mdefine_line|#define  MAC_STATUS_PCS_SYNCED&t;&t; 0x00000001
DECL|macro|MAC_STATUS_SIGNAL_DET
mdefine_line|#define  MAC_STATUS_SIGNAL_DET&t;&t; 0x00000002
DECL|macro|MAC_STATUS_RCVD_CFG
mdefine_line|#define  MAC_STATUS_RCVD_CFG&t;&t; 0x00000004
DECL|macro|MAC_STATUS_CFG_CHANGED
mdefine_line|#define  MAC_STATUS_CFG_CHANGED&t;&t; 0x00000008
DECL|macro|MAC_STATUS_SYNC_CHANGED
mdefine_line|#define  MAC_STATUS_SYNC_CHANGED&t; 0x00000010
DECL|macro|MAC_STATUS_PORT_DEC_ERR
mdefine_line|#define  MAC_STATUS_PORT_DEC_ERR&t; 0x00000400
DECL|macro|MAC_STATUS_LNKSTATE_CHANGED
mdefine_line|#define  MAC_STATUS_LNKSTATE_CHANGED&t; 0x00001000
DECL|macro|MAC_STATUS_MI_COMPLETION
mdefine_line|#define  MAC_STATUS_MI_COMPLETION&t; 0x00400000
DECL|macro|MAC_STATUS_MI_INTERRUPT
mdefine_line|#define  MAC_STATUS_MI_INTERRUPT&t; 0x00800000
DECL|macro|MAC_STATUS_AP_ERROR
mdefine_line|#define  MAC_STATUS_AP_ERROR&t;&t; 0x01000000
DECL|macro|MAC_STATUS_ODI_ERROR
mdefine_line|#define  MAC_STATUS_ODI_ERROR&t;&t; 0x02000000
DECL|macro|MAC_STATUS_RXSTAT_OVERRUN
mdefine_line|#define  MAC_STATUS_RXSTAT_OVERRUN&t; 0x04000000
DECL|macro|MAC_STATUS_TXSTAT_OVERRUN
mdefine_line|#define  MAC_STATUS_TXSTAT_OVERRUN&t; 0x08000000
DECL|macro|MAC_EVENT
mdefine_line|#define MAC_EVENT&t;&t;&t;0x00000408
DECL|macro|MAC_EVENT_PORT_DECODE_ERR
mdefine_line|#define  MAC_EVENT_PORT_DECODE_ERR&t; 0x00000400
DECL|macro|MAC_EVENT_LNKSTATE_CHANGED
mdefine_line|#define  MAC_EVENT_LNKSTATE_CHANGED&t; 0x00001000
DECL|macro|MAC_EVENT_MI_COMPLETION
mdefine_line|#define  MAC_EVENT_MI_COMPLETION&t; 0x00400000
DECL|macro|MAC_EVENT_MI_INTERRUPT
mdefine_line|#define  MAC_EVENT_MI_INTERRUPT&t;&t; 0x00800000
DECL|macro|MAC_EVENT_AP_ERROR
mdefine_line|#define  MAC_EVENT_AP_ERROR&t;&t; 0x01000000
DECL|macro|MAC_EVENT_ODI_ERROR
mdefine_line|#define  MAC_EVENT_ODI_ERROR&t;&t; 0x02000000
DECL|macro|MAC_EVENT_RXSTAT_OVERRUN
mdefine_line|#define  MAC_EVENT_RXSTAT_OVERRUN&t; 0x04000000
DECL|macro|MAC_EVENT_TXSTAT_OVERRUN
mdefine_line|#define  MAC_EVENT_TXSTAT_OVERRUN&t; 0x08000000
DECL|macro|MAC_LED_CTRL
mdefine_line|#define MAC_LED_CTRL&t;&t;&t;0x0000040c
DECL|macro|LED_CTRL_LNKLED_OVERRIDE
mdefine_line|#define  LED_CTRL_LNKLED_OVERRIDE&t; 0x00000001
DECL|macro|LED_CTRL_1000MBPS_ON
mdefine_line|#define  LED_CTRL_1000MBPS_ON&t;&t; 0x00000002
DECL|macro|LED_CTRL_100MBPS_ON
mdefine_line|#define  LED_CTRL_100MBPS_ON&t;&t; 0x00000004
DECL|macro|LED_CTRL_10MBPS_ON
mdefine_line|#define  LED_CTRL_10MBPS_ON&t;&t; 0x00000008
DECL|macro|LED_CTRL_TRAFFIC_OVERRIDE
mdefine_line|#define  LED_CTRL_TRAFFIC_OVERRIDE&t; 0x00000010
DECL|macro|LED_CTRL_TRAFFIC_BLINK
mdefine_line|#define  LED_CTRL_TRAFFIC_BLINK&t;&t; 0x00000020
DECL|macro|LED_CTRL_TRAFFIC_LED
mdefine_line|#define  LED_CTRL_TRAFFIC_LED&t;&t; 0x00000040
DECL|macro|LED_CTRL_1000MBPS_STATUS
mdefine_line|#define  LED_CTRL_1000MBPS_STATUS&t; 0x00000080
DECL|macro|LED_CTRL_100MBPS_STATUS
mdefine_line|#define  LED_CTRL_100MBPS_STATUS&t; 0x00000100
DECL|macro|LED_CTRL_10MBPS_STATUS
mdefine_line|#define  LED_CTRL_10MBPS_STATUS&t;&t; 0x00000200
DECL|macro|LED_CTRL_TRAFFIC_STATUS
mdefine_line|#define  LED_CTRL_TRAFFIC_STATUS&t; 0x00000400
DECL|macro|LED_CTRL_MAC_MODE
mdefine_line|#define  LED_CTRL_MAC_MODE&t;&t; 0x00000000
DECL|macro|LED_CTRL_PHY_MODE_1
mdefine_line|#define  LED_CTRL_PHY_MODE_1&t;&t; 0x00000800
DECL|macro|LED_CTRL_PHY_MODE_2
mdefine_line|#define  LED_CTRL_PHY_MODE_2&t;&t; 0x00001000
DECL|macro|LED_CTRL_BLINK_RATE_MASK
mdefine_line|#define  LED_CTRL_BLINK_RATE_MASK&t; 0x7ff80000
DECL|macro|LED_CTRL_BLINK_RATE_SHIFT
mdefine_line|#define  LED_CTRL_BLINK_RATE_SHIFT&t; 19
DECL|macro|LED_CTRL_BLINK_PER_OVERRIDE
mdefine_line|#define  LED_CTRL_BLINK_PER_OVERRIDE&t; 0x00080000
DECL|macro|LED_CTRL_BLINK_RATE_OVERRIDE
mdefine_line|#define  LED_CTRL_BLINK_RATE_OVERRIDE&t; 0x80000000
DECL|macro|MAC_ADDR_0_HIGH
mdefine_line|#define MAC_ADDR_0_HIGH&t;&t;&t;0x00000410 /* upper 2 bytes */
DECL|macro|MAC_ADDR_0_LOW
mdefine_line|#define MAC_ADDR_0_LOW&t;&t;&t;0x00000414 /* lower 4 bytes */
DECL|macro|MAC_ADDR_1_HIGH
mdefine_line|#define MAC_ADDR_1_HIGH&t;&t;&t;0x00000418 /* upper 2 bytes */
DECL|macro|MAC_ADDR_1_LOW
mdefine_line|#define MAC_ADDR_1_LOW&t;&t;&t;0x0000041c /* lower 4 bytes */
DECL|macro|MAC_ADDR_2_HIGH
mdefine_line|#define MAC_ADDR_2_HIGH&t;&t;&t;0x00000420 /* upper 2 bytes */
DECL|macro|MAC_ADDR_2_LOW
mdefine_line|#define MAC_ADDR_2_LOW&t;&t;&t;0x00000424 /* lower 4 bytes */
DECL|macro|MAC_ADDR_3_HIGH
mdefine_line|#define MAC_ADDR_3_HIGH&t;&t;&t;0x00000428 /* upper 2 bytes */
DECL|macro|MAC_ADDR_3_LOW
mdefine_line|#define MAC_ADDR_3_LOW&t;&t;&t;0x0000042c /* lower 4 bytes */
DECL|macro|MAC_ACPI_MBUF_PTR
mdefine_line|#define MAC_ACPI_MBUF_PTR&t;&t;0x00000430
DECL|macro|MAC_ACPI_LEN_OFFSET
mdefine_line|#define MAC_ACPI_LEN_OFFSET&t;&t;0x00000434
DECL|macro|ACPI_LENOFF_LEN_MASK
mdefine_line|#define  ACPI_LENOFF_LEN_MASK&t;&t; 0x0000ffff
DECL|macro|ACPI_LENOFF_LEN_SHIFT
mdefine_line|#define  ACPI_LENOFF_LEN_SHIFT&t;&t; 0
DECL|macro|ACPI_LENOFF_OFF_MASK
mdefine_line|#define  ACPI_LENOFF_OFF_MASK&t;&t; 0x0fff0000
DECL|macro|ACPI_LENOFF_OFF_SHIFT
mdefine_line|#define  ACPI_LENOFF_OFF_SHIFT&t;&t; 16
DECL|macro|MAC_TX_BACKOFF_SEED
mdefine_line|#define MAC_TX_BACKOFF_SEED&t;&t;0x00000438
DECL|macro|TX_BACKOFF_SEED_MASK
mdefine_line|#define  TX_BACKOFF_SEED_MASK&t;&t; 0x000003ff
DECL|macro|MAC_RX_MTU_SIZE
mdefine_line|#define MAC_RX_MTU_SIZE&t;&t;&t;0x0000043c
DECL|macro|RX_MTU_SIZE_MASK
mdefine_line|#define  RX_MTU_SIZE_MASK&t;&t; 0x0000ffff
DECL|macro|MAC_PCS_TEST
mdefine_line|#define MAC_PCS_TEST&t;&t;&t;0x00000440
DECL|macro|PCS_TEST_PATTERN_MASK
mdefine_line|#define  PCS_TEST_PATTERN_MASK&t;&t; 0x000fffff
DECL|macro|PCS_TEST_PATTERN_SHIFT
mdefine_line|#define  PCS_TEST_PATTERN_SHIFT&t;&t; 0
DECL|macro|PCS_TEST_ENABLE
mdefine_line|#define  PCS_TEST_ENABLE&t;&t; 0x00100000
DECL|macro|MAC_TX_AUTO_NEG
mdefine_line|#define MAC_TX_AUTO_NEG&t;&t;&t;0x00000444
DECL|macro|TX_AUTO_NEG_MASK
mdefine_line|#define  TX_AUTO_NEG_MASK&t;&t; 0x0000ffff
DECL|macro|TX_AUTO_NEG_SHIFT
mdefine_line|#define  TX_AUTO_NEG_SHIFT&t;&t; 0
DECL|macro|MAC_RX_AUTO_NEG
mdefine_line|#define MAC_RX_AUTO_NEG&t;&t;&t;0x00000448
DECL|macro|RX_AUTO_NEG_MASK
mdefine_line|#define  RX_AUTO_NEG_MASK&t;&t; 0x0000ffff
DECL|macro|RX_AUTO_NEG_SHIFT
mdefine_line|#define  RX_AUTO_NEG_SHIFT&t;&t; 0
DECL|macro|MAC_MI_COM
mdefine_line|#define MAC_MI_COM&t;&t;&t;0x0000044c
DECL|macro|MI_COM_CMD_MASK
mdefine_line|#define  MI_COM_CMD_MASK&t;&t; 0x0c000000
DECL|macro|MI_COM_CMD_WRITE
mdefine_line|#define  MI_COM_CMD_WRITE&t;&t; 0x04000000
DECL|macro|MI_COM_CMD_READ
mdefine_line|#define  MI_COM_CMD_READ&t;&t; 0x08000000
DECL|macro|MI_COM_READ_FAILED
mdefine_line|#define  MI_COM_READ_FAILED&t;&t; 0x10000000
DECL|macro|MI_COM_START
mdefine_line|#define  MI_COM_START&t;&t;&t; 0x20000000
DECL|macro|MI_COM_BUSY
mdefine_line|#define  MI_COM_BUSY&t;&t;&t; 0x20000000
DECL|macro|MI_COM_PHY_ADDR_MASK
mdefine_line|#define  MI_COM_PHY_ADDR_MASK&t;&t; 0x03e00000
DECL|macro|MI_COM_PHY_ADDR_SHIFT
mdefine_line|#define  MI_COM_PHY_ADDR_SHIFT&t;&t; 21
DECL|macro|MI_COM_REG_ADDR_MASK
mdefine_line|#define  MI_COM_REG_ADDR_MASK&t;&t; 0x001f0000
DECL|macro|MI_COM_REG_ADDR_SHIFT
mdefine_line|#define  MI_COM_REG_ADDR_SHIFT&t;&t; 16
DECL|macro|MI_COM_DATA_MASK
mdefine_line|#define  MI_COM_DATA_MASK&t;&t; 0x0000ffff
DECL|macro|MAC_MI_STAT
mdefine_line|#define MAC_MI_STAT&t;&t;&t;0x00000450
DECL|macro|MAC_MI_STAT_LNKSTAT_ATTN_ENAB
mdefine_line|#define  MAC_MI_STAT_LNKSTAT_ATTN_ENAB&t; 0x00000001
DECL|macro|MAC_MI_MODE
mdefine_line|#define MAC_MI_MODE&t;&t;&t;0x00000454
DECL|macro|MAC_MI_MODE_CLK_10MHZ
mdefine_line|#define  MAC_MI_MODE_CLK_10MHZ&t;&t; 0x00000001
DECL|macro|MAC_MI_MODE_SHORT_PREAMBLE
mdefine_line|#define  MAC_MI_MODE_SHORT_PREAMBLE&t; 0x00000002
DECL|macro|MAC_MI_MODE_AUTO_POLL
mdefine_line|#define  MAC_MI_MODE_AUTO_POLL&t;&t; 0x00000010
DECL|macro|MAC_MI_MODE_CORE_CLK_62MHZ
mdefine_line|#define  MAC_MI_MODE_CORE_CLK_62MHZ&t; 0x00008000
DECL|macro|MAC_MI_MODE_BASE
mdefine_line|#define  MAC_MI_MODE_BASE&t;&t; 0x000c0000 /* XXX magic values XXX */
DECL|macro|MAC_AUTO_POLL_STATUS
mdefine_line|#define MAC_AUTO_POLL_STATUS&t;&t;0x00000458
DECL|macro|MAC_AUTO_POLL_ERROR
mdefine_line|#define  MAC_AUTO_POLL_ERROR&t;&t; 0x00000001
DECL|macro|MAC_TX_MODE
mdefine_line|#define MAC_TX_MODE&t;&t;&t;0x0000045c
DECL|macro|TX_MODE_RESET
mdefine_line|#define  TX_MODE_RESET&t;&t;&t; 0x00000001
DECL|macro|TX_MODE_ENABLE
mdefine_line|#define  TX_MODE_ENABLE&t;&t;&t; 0x00000002
DECL|macro|TX_MODE_FLOW_CTRL_ENABLE
mdefine_line|#define  TX_MODE_FLOW_CTRL_ENABLE&t; 0x00000010
DECL|macro|TX_MODE_BIG_BCKOFF_ENABLE
mdefine_line|#define  TX_MODE_BIG_BCKOFF_ENABLE&t; 0x00000020
DECL|macro|TX_MODE_LONG_PAUSE_ENABLE
mdefine_line|#define  TX_MODE_LONG_PAUSE_ENABLE&t; 0x00000040
DECL|macro|MAC_TX_STATUS
mdefine_line|#define MAC_TX_STATUS&t;&t;&t;0x00000460
DECL|macro|TX_STATUS_XOFFED
mdefine_line|#define  TX_STATUS_XOFFED&t;&t; 0x00000001
DECL|macro|TX_STATUS_SENT_XOFF
mdefine_line|#define  TX_STATUS_SENT_XOFF&t;&t; 0x00000002
DECL|macro|TX_STATUS_SENT_XON
mdefine_line|#define  TX_STATUS_SENT_XON&t;&t; 0x00000004
DECL|macro|TX_STATUS_LINK_UP
mdefine_line|#define  TX_STATUS_LINK_UP&t;&t; 0x00000008
DECL|macro|TX_STATUS_ODI_UNDERRUN
mdefine_line|#define  TX_STATUS_ODI_UNDERRUN&t;&t; 0x00000010
DECL|macro|TX_STATUS_ODI_OVERRUN
mdefine_line|#define  TX_STATUS_ODI_OVERRUN&t;&t; 0x00000020
DECL|macro|MAC_TX_LENGTHS
mdefine_line|#define MAC_TX_LENGTHS&t;&t;&t;0x00000464
DECL|macro|TX_LENGTHS_SLOT_TIME_MASK
mdefine_line|#define  TX_LENGTHS_SLOT_TIME_MASK&t; 0x000000ff
DECL|macro|TX_LENGTHS_SLOT_TIME_SHIFT
mdefine_line|#define  TX_LENGTHS_SLOT_TIME_SHIFT&t; 0
DECL|macro|TX_LENGTHS_IPG_MASK
mdefine_line|#define  TX_LENGTHS_IPG_MASK&t;&t; 0x00000f00
DECL|macro|TX_LENGTHS_IPG_SHIFT
mdefine_line|#define  TX_LENGTHS_IPG_SHIFT&t;&t; 8
DECL|macro|TX_LENGTHS_IPG_CRS_MASK
mdefine_line|#define  TX_LENGTHS_IPG_CRS_MASK&t; 0x00003000
DECL|macro|TX_LENGTHS_IPG_CRS_SHIFT
mdefine_line|#define  TX_LENGTHS_IPG_CRS_SHIFT&t; 12
DECL|macro|MAC_RX_MODE
mdefine_line|#define MAC_RX_MODE&t;&t;&t;0x00000468
DECL|macro|RX_MODE_RESET
mdefine_line|#define  RX_MODE_RESET&t;&t;&t; 0x00000001
DECL|macro|RX_MODE_ENABLE
mdefine_line|#define  RX_MODE_ENABLE&t;&t;&t; 0x00000002
DECL|macro|RX_MODE_FLOW_CTRL_ENABLE
mdefine_line|#define  RX_MODE_FLOW_CTRL_ENABLE&t; 0x00000004
DECL|macro|RX_MODE_KEEP_MAC_CTRL
mdefine_line|#define  RX_MODE_KEEP_MAC_CTRL&t;&t; 0x00000008
DECL|macro|RX_MODE_KEEP_PAUSE
mdefine_line|#define  RX_MODE_KEEP_PAUSE&t;&t; 0x00000010
DECL|macro|RX_MODE_ACCEPT_OVERSIZED
mdefine_line|#define  RX_MODE_ACCEPT_OVERSIZED&t; 0x00000020
DECL|macro|RX_MODE_ACCEPT_RUNTS
mdefine_line|#define  RX_MODE_ACCEPT_RUNTS&t;&t; 0x00000040
DECL|macro|RX_MODE_LEN_CHECK
mdefine_line|#define  RX_MODE_LEN_CHECK&t;&t; 0x00000080
DECL|macro|RX_MODE_PROMISC
mdefine_line|#define  RX_MODE_PROMISC&t;&t; 0x00000100
DECL|macro|RX_MODE_NO_CRC_CHECK
mdefine_line|#define  RX_MODE_NO_CRC_CHECK&t;&t; 0x00000200
DECL|macro|RX_MODE_KEEP_VLAN_TAG
mdefine_line|#define  RX_MODE_KEEP_VLAN_TAG&t;&t; 0x00000400
DECL|macro|MAC_RX_STATUS
mdefine_line|#define MAC_RX_STATUS&t;&t;&t;0x0000046c
DECL|macro|RX_STATUS_REMOTE_TX_XOFFED
mdefine_line|#define  RX_STATUS_REMOTE_TX_XOFFED&t; 0x00000001
DECL|macro|RX_STATUS_XOFF_RCVD
mdefine_line|#define  RX_STATUS_XOFF_RCVD&t;&t; 0x00000002
DECL|macro|RX_STATUS_XON_RCVD
mdefine_line|#define  RX_STATUS_XON_RCVD&t;&t; 0x00000004
DECL|macro|MAC_HASH_REG_0
mdefine_line|#define MAC_HASH_REG_0&t;&t;&t;0x00000470
DECL|macro|MAC_HASH_REG_1
mdefine_line|#define MAC_HASH_REG_1&t;&t;&t;0x00000474
DECL|macro|MAC_HASH_REG_2
mdefine_line|#define MAC_HASH_REG_2&t;&t;&t;0x00000478
DECL|macro|MAC_HASH_REG_3
mdefine_line|#define MAC_HASH_REG_3&t;&t;&t;0x0000047c
DECL|macro|MAC_RCV_RULE_0
mdefine_line|#define MAC_RCV_RULE_0&t;&t;&t;0x00000480
DECL|macro|MAC_RCV_VALUE_0
mdefine_line|#define MAC_RCV_VALUE_0&t;&t;&t;0x00000484
DECL|macro|MAC_RCV_RULE_1
mdefine_line|#define MAC_RCV_RULE_1&t;&t;&t;0x00000488
DECL|macro|MAC_RCV_VALUE_1
mdefine_line|#define MAC_RCV_VALUE_1&t;&t;&t;0x0000048c
DECL|macro|MAC_RCV_RULE_2
mdefine_line|#define MAC_RCV_RULE_2&t;&t;&t;0x00000490
DECL|macro|MAC_RCV_VALUE_2
mdefine_line|#define MAC_RCV_VALUE_2&t;&t;&t;0x00000494
DECL|macro|MAC_RCV_RULE_3
mdefine_line|#define MAC_RCV_RULE_3&t;&t;&t;0x00000498
DECL|macro|MAC_RCV_VALUE_3
mdefine_line|#define MAC_RCV_VALUE_3&t;&t;&t;0x0000049c
DECL|macro|MAC_RCV_RULE_4
mdefine_line|#define MAC_RCV_RULE_4&t;&t;&t;0x000004a0
DECL|macro|MAC_RCV_VALUE_4
mdefine_line|#define MAC_RCV_VALUE_4&t;&t;&t;0x000004a4
DECL|macro|MAC_RCV_RULE_5
mdefine_line|#define MAC_RCV_RULE_5&t;&t;&t;0x000004a8
DECL|macro|MAC_RCV_VALUE_5
mdefine_line|#define MAC_RCV_VALUE_5&t;&t;&t;0x000004ac
DECL|macro|MAC_RCV_RULE_6
mdefine_line|#define MAC_RCV_RULE_6&t;&t;&t;0x000004b0
DECL|macro|MAC_RCV_VALUE_6
mdefine_line|#define MAC_RCV_VALUE_6&t;&t;&t;0x000004b4
DECL|macro|MAC_RCV_RULE_7
mdefine_line|#define MAC_RCV_RULE_7&t;&t;&t;0x000004b8
DECL|macro|MAC_RCV_VALUE_7
mdefine_line|#define MAC_RCV_VALUE_7&t;&t;&t;0x000004bc
DECL|macro|MAC_RCV_RULE_8
mdefine_line|#define MAC_RCV_RULE_8&t;&t;&t;0x000004c0
DECL|macro|MAC_RCV_VALUE_8
mdefine_line|#define MAC_RCV_VALUE_8&t;&t;&t;0x000004c4
DECL|macro|MAC_RCV_RULE_9
mdefine_line|#define MAC_RCV_RULE_9&t;&t;&t;0x000004c8
DECL|macro|MAC_RCV_VALUE_9
mdefine_line|#define MAC_RCV_VALUE_9&t;&t;&t;0x000004cc
DECL|macro|MAC_RCV_RULE_10
mdefine_line|#define MAC_RCV_RULE_10&t;&t;&t;0x000004d0
DECL|macro|MAC_RCV_VALUE_10
mdefine_line|#define MAC_RCV_VALUE_10&t;&t;0x000004d4
DECL|macro|MAC_RCV_RULE_11
mdefine_line|#define MAC_RCV_RULE_11&t;&t;&t;0x000004d8
DECL|macro|MAC_RCV_VALUE_11
mdefine_line|#define MAC_RCV_VALUE_11&t;&t;0x000004dc
DECL|macro|MAC_RCV_RULE_12
mdefine_line|#define MAC_RCV_RULE_12&t;&t;&t;0x000004e0
DECL|macro|MAC_RCV_VALUE_12
mdefine_line|#define MAC_RCV_VALUE_12&t;&t;0x000004e4
DECL|macro|MAC_RCV_RULE_13
mdefine_line|#define MAC_RCV_RULE_13&t;&t;&t;0x000004e8
DECL|macro|MAC_RCV_VALUE_13
mdefine_line|#define MAC_RCV_VALUE_13&t;&t;0x000004ec
DECL|macro|MAC_RCV_RULE_14
mdefine_line|#define MAC_RCV_RULE_14&t;&t;&t;0x000004f0
DECL|macro|MAC_RCV_VALUE_14
mdefine_line|#define MAC_RCV_VALUE_14&t;&t;0x000004f4
DECL|macro|MAC_RCV_RULE_15
mdefine_line|#define MAC_RCV_RULE_15&t;&t;&t;0x000004f8
DECL|macro|MAC_RCV_VALUE_15
mdefine_line|#define MAC_RCV_VALUE_15&t;&t;0x000004fc
DECL|macro|RCV_RULE_DISABLE_MASK
mdefine_line|#define  RCV_RULE_DISABLE_MASK&t;&t; 0x7fffffff
DECL|macro|MAC_RCV_RULE_CFG
mdefine_line|#define MAC_RCV_RULE_CFG&t;&t;0x00000500
DECL|macro|RCV_RULE_CFG_DEFAULT_CLASS
mdefine_line|#define  RCV_RULE_CFG_DEFAULT_CLASS&t;0x00000008
multiline_comment|/* 0x504 --&gt; 0x590 unused */
DECL|macro|MAC_SERDES_CFG
mdefine_line|#define MAC_SERDES_CFG&t;&t;&t;0x00000590
DECL|macro|MAC_SERDES_STAT
mdefine_line|#define MAC_SERDES_STAT&t;&t;&t;0x00000594
multiline_comment|/* 0x598 --&gt; 0x600 unused */
DECL|macro|MAC_TX_MAC_STATE_BASE
mdefine_line|#define MAC_TX_MAC_STATE_BASE&t;&t;0x00000600 /* 16 bytes */
DECL|macro|MAC_RX_MAC_STATE_BASE
mdefine_line|#define MAC_RX_MAC_STATE_BASE&t;&t;0x00000610 /* 20 bytes */
multiline_comment|/* 0x624 --&gt; 0x800 unused */
DECL|macro|MAC_RX_STATS_BASE
mdefine_line|#define MAC_RX_STATS_BASE&t;&t;0x00000800 /* 26 32-bit words */
multiline_comment|/* 0x868 --&gt; 0x880 unused */
DECL|macro|MAC_TX_STATS_BASE
mdefine_line|#define MAC_TX_STATS_BASE&t;&t;0x00000880 /* 28 32-bit words */
multiline_comment|/* 0x8f0 --&gt; 0xc00 unused */
multiline_comment|/* Send data initiator control registers */
DECL|macro|SNDDATAI_MODE
mdefine_line|#define SNDDATAI_MODE&t;&t;&t;0x00000c00
DECL|macro|SNDDATAI_MODE_RESET
mdefine_line|#define  SNDDATAI_MODE_RESET&t;&t; 0x00000001
DECL|macro|SNDDATAI_MODE_ENABLE
mdefine_line|#define  SNDDATAI_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|SNDDATAI_MODE_STAT_OFLOW_ENAB
mdefine_line|#define  SNDDATAI_MODE_STAT_OFLOW_ENAB&t; 0x00000004
DECL|macro|SNDDATAI_STATUS
mdefine_line|#define SNDDATAI_STATUS&t;&t;&t;0x00000c04
DECL|macro|SNDDATAI_STATUS_STAT_OFLOW
mdefine_line|#define  SNDDATAI_STATUS_STAT_OFLOW&t; 0x00000004
DECL|macro|SNDDATAI_STATSCTRL
mdefine_line|#define SNDDATAI_STATSCTRL&t;&t;0x00000c08
DECL|macro|SNDDATAI_SCTRL_ENABLE
mdefine_line|#define  SNDDATAI_SCTRL_ENABLE&t;&t; 0x00000001
DECL|macro|SNDDATAI_SCTRL_FASTUPD
mdefine_line|#define  SNDDATAI_SCTRL_FASTUPD&t;&t; 0x00000002
DECL|macro|SNDDATAI_SCTRL_CLEAR
mdefine_line|#define  SNDDATAI_SCTRL_CLEAR&t;&t; 0x00000004
DECL|macro|SNDDATAI_SCTRL_FLUSH
mdefine_line|#define  SNDDATAI_SCTRL_FLUSH&t;&t; 0x00000008
DECL|macro|SNDDATAI_SCTRL_FORCE_ZERO
mdefine_line|#define  SNDDATAI_SCTRL_FORCE_ZERO&t; 0x00000010
DECL|macro|SNDDATAI_STATSENAB
mdefine_line|#define SNDDATAI_STATSENAB&t;&t;0x00000c0c
DECL|macro|SNDDATAI_STATSINCMASK
mdefine_line|#define SNDDATAI_STATSINCMASK&t;&t;0x00000c10
multiline_comment|/* 0xc14 --&gt; 0xc80 unused */
DECL|macro|SNDDATAI_COS_CNT_0
mdefine_line|#define SNDDATAI_COS_CNT_0&t;&t;0x00000c80
DECL|macro|SNDDATAI_COS_CNT_1
mdefine_line|#define SNDDATAI_COS_CNT_1&t;&t;0x00000c84
DECL|macro|SNDDATAI_COS_CNT_2
mdefine_line|#define SNDDATAI_COS_CNT_2&t;&t;0x00000c88
DECL|macro|SNDDATAI_COS_CNT_3
mdefine_line|#define SNDDATAI_COS_CNT_3&t;&t;0x00000c8c
DECL|macro|SNDDATAI_COS_CNT_4
mdefine_line|#define SNDDATAI_COS_CNT_4&t;&t;0x00000c90
DECL|macro|SNDDATAI_COS_CNT_5
mdefine_line|#define SNDDATAI_COS_CNT_5&t;&t;0x00000c94
DECL|macro|SNDDATAI_COS_CNT_6
mdefine_line|#define SNDDATAI_COS_CNT_6&t;&t;0x00000c98
DECL|macro|SNDDATAI_COS_CNT_7
mdefine_line|#define SNDDATAI_COS_CNT_7&t;&t;0x00000c9c
DECL|macro|SNDDATAI_COS_CNT_8
mdefine_line|#define SNDDATAI_COS_CNT_8&t;&t;0x00000ca0
DECL|macro|SNDDATAI_COS_CNT_9
mdefine_line|#define SNDDATAI_COS_CNT_9&t;&t;0x00000ca4
DECL|macro|SNDDATAI_COS_CNT_10
mdefine_line|#define SNDDATAI_COS_CNT_10&t;&t;0x00000ca8
DECL|macro|SNDDATAI_COS_CNT_11
mdefine_line|#define SNDDATAI_COS_CNT_11&t;&t;0x00000cac
DECL|macro|SNDDATAI_COS_CNT_12
mdefine_line|#define SNDDATAI_COS_CNT_12&t;&t;0x00000cb0
DECL|macro|SNDDATAI_COS_CNT_13
mdefine_line|#define SNDDATAI_COS_CNT_13&t;&t;0x00000cb4
DECL|macro|SNDDATAI_COS_CNT_14
mdefine_line|#define SNDDATAI_COS_CNT_14&t;&t;0x00000cb8
DECL|macro|SNDDATAI_COS_CNT_15
mdefine_line|#define SNDDATAI_COS_CNT_15&t;&t;0x00000cbc
DECL|macro|SNDDATAI_DMA_RDQ_FULL_CNT
mdefine_line|#define SNDDATAI_DMA_RDQ_FULL_CNT&t;0x00000cc0
DECL|macro|SNDDATAI_DMA_PRIO_RDQ_FULL_CNT
mdefine_line|#define SNDDATAI_DMA_PRIO_RDQ_FULL_CNT&t;0x00000cc4
DECL|macro|SNDDATAI_SDCQ_FULL_CNT
mdefine_line|#define SNDDATAI_SDCQ_FULL_CNT&t;&t;0x00000cc8
DECL|macro|SNDDATAI_NICRNG_SSND_PIDX_CNT
mdefine_line|#define SNDDATAI_NICRNG_SSND_PIDX_CNT&t;0x00000ccc
DECL|macro|SNDDATAI_STATS_UPDATED_CNT
mdefine_line|#define SNDDATAI_STATS_UPDATED_CNT&t;0x00000cd0
DECL|macro|SNDDATAI_INTERRUPTS_CNT
mdefine_line|#define SNDDATAI_INTERRUPTS_CNT&t;&t;0x00000cd4
DECL|macro|SNDDATAI_AVOID_INTERRUPTS_CNT
mdefine_line|#define SNDDATAI_AVOID_INTERRUPTS_CNT&t;0x00000cd8
DECL|macro|SNDDATAI_SND_THRESH_HIT_CNT
mdefine_line|#define SNDDATAI_SND_THRESH_HIT_CNT&t;0x00000cdc
multiline_comment|/* 0xce0 --&gt; 0x1000 unused */
multiline_comment|/* Send data completion control registers */
DECL|macro|SNDDATAC_MODE
mdefine_line|#define SNDDATAC_MODE&t;&t;&t;0x00001000
DECL|macro|SNDDATAC_MODE_RESET
mdefine_line|#define  SNDDATAC_MODE_RESET&t;&t; 0x00000001
DECL|macro|SNDDATAC_MODE_ENABLE
mdefine_line|#define  SNDDATAC_MODE_ENABLE&t;&t; 0x00000002
multiline_comment|/* 0x1004 --&gt; 0x1400 unused */
multiline_comment|/* Send BD ring selector */
DECL|macro|SNDBDS_MODE
mdefine_line|#define SNDBDS_MODE&t;&t;&t;0x00001400
DECL|macro|SNDBDS_MODE_RESET
mdefine_line|#define  SNDBDS_MODE_RESET&t;&t; 0x00000001
DECL|macro|SNDBDS_MODE_ENABLE
mdefine_line|#define  SNDBDS_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|SNDBDS_MODE_ATTN_ENABLE
mdefine_line|#define  SNDBDS_MODE_ATTN_ENABLE&t; 0x00000004
DECL|macro|SNDBDS_STATUS
mdefine_line|#define SNDBDS_STATUS&t;&t;&t;0x00001404
DECL|macro|SNDBDS_STATUS_ERROR_ATTN
mdefine_line|#define  SNDBDS_STATUS_ERROR_ATTN&t; 0x00000004
DECL|macro|SNDBDS_HWDIAG
mdefine_line|#define SNDBDS_HWDIAG&t;&t;&t;0x00001408
multiline_comment|/* 0x140c --&gt; 0x1440 */
DECL|macro|SNDBDS_SEL_CON_IDX_0
mdefine_line|#define SNDBDS_SEL_CON_IDX_0&t;&t;0x00001440
DECL|macro|SNDBDS_SEL_CON_IDX_1
mdefine_line|#define SNDBDS_SEL_CON_IDX_1&t;&t;0x00001444
DECL|macro|SNDBDS_SEL_CON_IDX_2
mdefine_line|#define SNDBDS_SEL_CON_IDX_2&t;&t;0x00001448
DECL|macro|SNDBDS_SEL_CON_IDX_3
mdefine_line|#define SNDBDS_SEL_CON_IDX_3&t;&t;0x0000144c
DECL|macro|SNDBDS_SEL_CON_IDX_4
mdefine_line|#define SNDBDS_SEL_CON_IDX_4&t;&t;0x00001450
DECL|macro|SNDBDS_SEL_CON_IDX_5
mdefine_line|#define SNDBDS_SEL_CON_IDX_5&t;&t;0x00001454
DECL|macro|SNDBDS_SEL_CON_IDX_6
mdefine_line|#define SNDBDS_SEL_CON_IDX_6&t;&t;0x00001458
DECL|macro|SNDBDS_SEL_CON_IDX_7
mdefine_line|#define SNDBDS_SEL_CON_IDX_7&t;&t;0x0000145c
DECL|macro|SNDBDS_SEL_CON_IDX_8
mdefine_line|#define SNDBDS_SEL_CON_IDX_8&t;&t;0x00001460
DECL|macro|SNDBDS_SEL_CON_IDX_9
mdefine_line|#define SNDBDS_SEL_CON_IDX_9&t;&t;0x00001464
DECL|macro|SNDBDS_SEL_CON_IDX_10
mdefine_line|#define SNDBDS_SEL_CON_IDX_10&t;&t;0x00001468
DECL|macro|SNDBDS_SEL_CON_IDX_11
mdefine_line|#define SNDBDS_SEL_CON_IDX_11&t;&t;0x0000146c
DECL|macro|SNDBDS_SEL_CON_IDX_12
mdefine_line|#define SNDBDS_SEL_CON_IDX_12&t;&t;0x00001470
DECL|macro|SNDBDS_SEL_CON_IDX_13
mdefine_line|#define SNDBDS_SEL_CON_IDX_13&t;&t;0x00001474
DECL|macro|SNDBDS_SEL_CON_IDX_14
mdefine_line|#define SNDBDS_SEL_CON_IDX_14&t;&t;0x00001478
DECL|macro|SNDBDS_SEL_CON_IDX_15
mdefine_line|#define SNDBDS_SEL_CON_IDX_15&t;&t;0x0000147c
multiline_comment|/* 0x1480 --&gt; 0x1800 unused */
multiline_comment|/* Send BD initiator control registers */
DECL|macro|SNDBDI_MODE
mdefine_line|#define SNDBDI_MODE&t;&t;&t;0x00001800
DECL|macro|SNDBDI_MODE_RESET
mdefine_line|#define  SNDBDI_MODE_RESET&t;&t; 0x00000001
DECL|macro|SNDBDI_MODE_ENABLE
mdefine_line|#define  SNDBDI_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|SNDBDI_MODE_ATTN_ENABLE
mdefine_line|#define  SNDBDI_MODE_ATTN_ENABLE&t; 0x00000004
DECL|macro|SNDBDI_STATUS
mdefine_line|#define SNDBDI_STATUS&t;&t;&t;0x00001804
DECL|macro|SNDBDI_STATUS_ERROR_ATTN
mdefine_line|#define  SNDBDI_STATUS_ERROR_ATTN&t; 0x00000004
DECL|macro|SNDBDI_IN_PROD_IDX_0
mdefine_line|#define SNDBDI_IN_PROD_IDX_0&t;&t;0x00001808
DECL|macro|SNDBDI_IN_PROD_IDX_1
mdefine_line|#define SNDBDI_IN_PROD_IDX_1&t;&t;0x0000180c
DECL|macro|SNDBDI_IN_PROD_IDX_2
mdefine_line|#define SNDBDI_IN_PROD_IDX_2&t;&t;0x00001810
DECL|macro|SNDBDI_IN_PROD_IDX_3
mdefine_line|#define SNDBDI_IN_PROD_IDX_3&t;&t;0x00001814
DECL|macro|SNDBDI_IN_PROD_IDX_4
mdefine_line|#define SNDBDI_IN_PROD_IDX_4&t;&t;0x00001818
DECL|macro|SNDBDI_IN_PROD_IDX_5
mdefine_line|#define SNDBDI_IN_PROD_IDX_5&t;&t;0x0000181c
DECL|macro|SNDBDI_IN_PROD_IDX_6
mdefine_line|#define SNDBDI_IN_PROD_IDX_6&t;&t;0x00001820
DECL|macro|SNDBDI_IN_PROD_IDX_7
mdefine_line|#define SNDBDI_IN_PROD_IDX_7&t;&t;0x00001824
DECL|macro|SNDBDI_IN_PROD_IDX_8
mdefine_line|#define SNDBDI_IN_PROD_IDX_8&t;&t;0x00001828
DECL|macro|SNDBDI_IN_PROD_IDX_9
mdefine_line|#define SNDBDI_IN_PROD_IDX_9&t;&t;0x0000182c
DECL|macro|SNDBDI_IN_PROD_IDX_10
mdefine_line|#define SNDBDI_IN_PROD_IDX_10&t;&t;0x00001830
DECL|macro|SNDBDI_IN_PROD_IDX_11
mdefine_line|#define SNDBDI_IN_PROD_IDX_11&t;&t;0x00001834
DECL|macro|SNDBDI_IN_PROD_IDX_12
mdefine_line|#define SNDBDI_IN_PROD_IDX_12&t;&t;0x00001838
DECL|macro|SNDBDI_IN_PROD_IDX_13
mdefine_line|#define SNDBDI_IN_PROD_IDX_13&t;&t;0x0000183c
DECL|macro|SNDBDI_IN_PROD_IDX_14
mdefine_line|#define SNDBDI_IN_PROD_IDX_14&t;&t;0x00001840
DECL|macro|SNDBDI_IN_PROD_IDX_15
mdefine_line|#define SNDBDI_IN_PROD_IDX_15&t;&t;0x00001844
multiline_comment|/* 0x1848 --&gt; 0x1c00 unused */
multiline_comment|/* Send BD completion control registers */
DECL|macro|SNDBDC_MODE
mdefine_line|#define SNDBDC_MODE&t;&t;&t;0x00001c00
DECL|macro|SNDBDC_MODE_RESET
mdefine_line|#define SNDBDC_MODE_RESET&t;&t; 0x00000001
DECL|macro|SNDBDC_MODE_ENABLE
mdefine_line|#define SNDBDC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|SNDBDC_MODE_ATTN_ENABLE
mdefine_line|#define SNDBDC_MODE_ATTN_ENABLE&t;&t; 0x00000004
multiline_comment|/* 0x1c04 --&gt; 0x2000 unused */
multiline_comment|/* Receive list placement control registers */
DECL|macro|RCVLPC_MODE
mdefine_line|#define RCVLPC_MODE&t;&t;&t;0x00002000
DECL|macro|RCVLPC_MODE_RESET
mdefine_line|#define  RCVLPC_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVLPC_MODE_ENABLE
mdefine_line|#define  RCVLPC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVLPC_MODE_CLASS0_ATTN_ENAB
mdefine_line|#define  RCVLPC_MODE_CLASS0_ATTN_ENAB&t; 0x00000004
DECL|macro|RCVLPC_MODE_MAPOOR_AATTN_ENAB
mdefine_line|#define  RCVLPC_MODE_MAPOOR_AATTN_ENAB&t; 0x00000008
DECL|macro|RCVLPC_MODE_STAT_OFLOW_ENAB
mdefine_line|#define  RCVLPC_MODE_STAT_OFLOW_ENAB&t; 0x00000010
DECL|macro|RCVLPC_STATUS
mdefine_line|#define RCVLPC_STATUS&t;&t;&t;0x00002004
DECL|macro|RCVLPC_STATUS_CLASS0
mdefine_line|#define  RCVLPC_STATUS_CLASS0&t;&t; 0x00000004
DECL|macro|RCVLPC_STATUS_MAPOOR
mdefine_line|#define  RCVLPC_STATUS_MAPOOR&t;&t; 0x00000008
DECL|macro|RCVLPC_STATUS_STAT_OFLOW
mdefine_line|#define  RCVLPC_STATUS_STAT_OFLOW&t; 0x00000010
DECL|macro|RCVLPC_LOCK
mdefine_line|#define RCVLPC_LOCK&t;&t;&t;0x00002008
DECL|macro|RCVLPC_LOCK_REQ_MASK
mdefine_line|#define  RCVLPC_LOCK_REQ_MASK&t;&t; 0x0000ffff
DECL|macro|RCVLPC_LOCK_REQ_SHIFT
mdefine_line|#define  RCVLPC_LOCK_REQ_SHIFT&t;&t; 0
DECL|macro|RCVLPC_LOCK_GRANT_MASK
mdefine_line|#define  RCVLPC_LOCK_GRANT_MASK&t;&t; 0xffff0000
DECL|macro|RCVLPC_LOCK_GRANT_SHIFT
mdefine_line|#define  RCVLPC_LOCK_GRANT_SHIFT&t; 16
DECL|macro|RCVLPC_NON_EMPTY_BITS
mdefine_line|#define RCVLPC_NON_EMPTY_BITS&t;&t;0x0000200c
DECL|macro|RCVLPC_NON_EMPTY_BITS_MASK
mdefine_line|#define  RCVLPC_NON_EMPTY_BITS_MASK&t; 0x0000ffff
DECL|macro|RCVLPC_CONFIG
mdefine_line|#define RCVLPC_CONFIG&t;&t;&t;0x00002010
DECL|macro|RCVLPC_STATSCTRL
mdefine_line|#define RCVLPC_STATSCTRL&t;&t;0x00002014
DECL|macro|RCVLPC_STATSCTRL_ENABLE
mdefine_line|#define  RCVLPC_STATSCTRL_ENABLE&t; 0x00000001
DECL|macro|RCVLPC_STATSCTRL_FASTUPD
mdefine_line|#define  RCVLPC_STATSCTRL_FASTUPD&t; 0x00000002
DECL|macro|RCVLPC_STATS_ENABLE
mdefine_line|#define RCVLPC_STATS_ENABLE&t;&t;0x00002018
DECL|macro|RCVLPC_STATS_INCMASK
mdefine_line|#define RCVLPC_STATS_INCMASK&t;&t;0x0000201c
multiline_comment|/* 0x2020 --&gt; 0x2100 unused */
DECL|macro|RCVLPC_SELLST_BASE
mdefine_line|#define RCVLPC_SELLST_BASE&t;&t;0x00002100 /* 16 16-byte entries */
DECL|macro|SELLST_TAIL
mdefine_line|#define  SELLST_TAIL&t;&t;&t;0x00000004
DECL|macro|SELLST_CONT
mdefine_line|#define  SELLST_CONT&t;&t;&t;0x00000008
DECL|macro|SELLST_UNUSED
mdefine_line|#define  SELLST_UNUSED&t;&t;&t;0x0000000c
DECL|macro|RCVLPC_COS_CNTL_BASE
mdefine_line|#define RCVLPC_COS_CNTL_BASE&t;&t;0x00002200 /* 16 4-byte entries */
DECL|macro|RCVLPC_DROP_FILTER_CNT
mdefine_line|#define RCVLPC_DROP_FILTER_CNT&t;&t;0x00002240
DECL|macro|RCVLPC_DMA_WQ_FULL_CNT
mdefine_line|#define RCVLPC_DMA_WQ_FULL_CNT&t;&t;0x00002244
DECL|macro|RCVLPC_DMA_HIPRIO_WQ_FULL_CNT
mdefine_line|#define RCVLPC_DMA_HIPRIO_WQ_FULL_CNT&t;0x00002248
DECL|macro|RCVLPC_NO_RCV_BD_CNT
mdefine_line|#define RCVLPC_NO_RCV_BD_CNT&t;&t;0x0000224c
DECL|macro|RCVLPC_IN_DISCARDS_CNT
mdefine_line|#define RCVLPC_IN_DISCARDS_CNT&t;&t;0x00002250
DECL|macro|RCVLPC_IN_ERRORS_CNT
mdefine_line|#define RCVLPC_IN_ERRORS_CNT&t;&t;0x00002254
DECL|macro|RCVLPC_RCV_THRESH_HIT_CNT
mdefine_line|#define RCVLPC_RCV_THRESH_HIT_CNT&t;0x00002258
multiline_comment|/* 0x225c --&gt; 0x2400 unused */
multiline_comment|/* Receive Data and Receive BD Initiator Control */
DECL|macro|RCVDBDI_MODE
mdefine_line|#define RCVDBDI_MODE&t;&t;&t;0x00002400
DECL|macro|RCVDBDI_MODE_RESET
mdefine_line|#define  RCVDBDI_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVDBDI_MODE_ENABLE
mdefine_line|#define  RCVDBDI_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVDBDI_MODE_JUMBOBD_NEEDED
mdefine_line|#define  RCVDBDI_MODE_JUMBOBD_NEEDED&t; 0x00000004
DECL|macro|RCVDBDI_MODE_FRM_TOO_BIG
mdefine_line|#define  RCVDBDI_MODE_FRM_TOO_BIG&t; 0x00000008
DECL|macro|RCVDBDI_MODE_INV_RING_SZ
mdefine_line|#define  RCVDBDI_MODE_INV_RING_SZ&t; 0x00000010
DECL|macro|RCVDBDI_STATUS
mdefine_line|#define RCVDBDI_STATUS&t;&t;&t;0x00002404
DECL|macro|RCVDBDI_STATUS_JUMBOBD_NEEDED
mdefine_line|#define  RCVDBDI_STATUS_JUMBOBD_NEEDED&t; 0x00000004
DECL|macro|RCVDBDI_STATUS_FRM_TOO_BIG
mdefine_line|#define  RCVDBDI_STATUS_FRM_TOO_BIG&t; 0x00000008
DECL|macro|RCVDBDI_STATUS_INV_RING_SZ
mdefine_line|#define  RCVDBDI_STATUS_INV_RING_SZ&t; 0x00000010
DECL|macro|RCVDBDI_SPLIT_FRAME_MINSZ
mdefine_line|#define RCVDBDI_SPLIT_FRAME_MINSZ&t;0x00002408
multiline_comment|/* 0x240c --&gt; 0x2440 unused */
DECL|macro|RCVDBDI_JUMBO_BD
mdefine_line|#define RCVDBDI_JUMBO_BD&t;&t;0x00002440 /* TG3_BDINFO_... */
DECL|macro|RCVDBDI_STD_BD
mdefine_line|#define RCVDBDI_STD_BD&t;&t;&t;0x00002450 /* TG3_BDINFO_... */
DECL|macro|RCVDBDI_MINI_BD
mdefine_line|#define RCVDBDI_MINI_BD&t;&t;&t;0x00002460 /* TG3_BDINFO_... */
DECL|macro|RCVDBDI_JUMBO_CON_IDX
mdefine_line|#define RCVDBDI_JUMBO_CON_IDX&t;&t;0x00002470
DECL|macro|RCVDBDI_STD_CON_IDX
mdefine_line|#define RCVDBDI_STD_CON_IDX&t;&t;0x00002474
DECL|macro|RCVDBDI_MINI_CON_IDX
mdefine_line|#define RCVDBDI_MINI_CON_IDX&t;&t;0x00002478
multiline_comment|/* 0x247c --&gt; 0x2480 unused */
DECL|macro|RCVDBDI_BD_PROD_IDX_0
mdefine_line|#define RCVDBDI_BD_PROD_IDX_0&t;&t;0x00002480
DECL|macro|RCVDBDI_BD_PROD_IDX_1
mdefine_line|#define RCVDBDI_BD_PROD_IDX_1&t;&t;0x00002484
DECL|macro|RCVDBDI_BD_PROD_IDX_2
mdefine_line|#define RCVDBDI_BD_PROD_IDX_2&t;&t;0x00002488
DECL|macro|RCVDBDI_BD_PROD_IDX_3
mdefine_line|#define RCVDBDI_BD_PROD_IDX_3&t;&t;0x0000248c
DECL|macro|RCVDBDI_BD_PROD_IDX_4
mdefine_line|#define RCVDBDI_BD_PROD_IDX_4&t;&t;0x00002490
DECL|macro|RCVDBDI_BD_PROD_IDX_5
mdefine_line|#define RCVDBDI_BD_PROD_IDX_5&t;&t;0x00002494
DECL|macro|RCVDBDI_BD_PROD_IDX_6
mdefine_line|#define RCVDBDI_BD_PROD_IDX_6&t;&t;0x00002498
DECL|macro|RCVDBDI_BD_PROD_IDX_7
mdefine_line|#define RCVDBDI_BD_PROD_IDX_7&t;&t;0x0000249c
DECL|macro|RCVDBDI_BD_PROD_IDX_8
mdefine_line|#define RCVDBDI_BD_PROD_IDX_8&t;&t;0x000024a0
DECL|macro|RCVDBDI_BD_PROD_IDX_9
mdefine_line|#define RCVDBDI_BD_PROD_IDX_9&t;&t;0x000024a4
DECL|macro|RCVDBDI_BD_PROD_IDX_10
mdefine_line|#define RCVDBDI_BD_PROD_IDX_10&t;&t;0x000024a8
DECL|macro|RCVDBDI_BD_PROD_IDX_11
mdefine_line|#define RCVDBDI_BD_PROD_IDX_11&t;&t;0x000024ac
DECL|macro|RCVDBDI_BD_PROD_IDX_12
mdefine_line|#define RCVDBDI_BD_PROD_IDX_12&t;&t;0x000024b0
DECL|macro|RCVDBDI_BD_PROD_IDX_13
mdefine_line|#define RCVDBDI_BD_PROD_IDX_13&t;&t;0x000024b4
DECL|macro|RCVDBDI_BD_PROD_IDX_14
mdefine_line|#define RCVDBDI_BD_PROD_IDX_14&t;&t;0x000024b8
DECL|macro|RCVDBDI_BD_PROD_IDX_15
mdefine_line|#define RCVDBDI_BD_PROD_IDX_15&t;&t;0x000024bc
DECL|macro|RCVDBDI_HWDIAG
mdefine_line|#define RCVDBDI_HWDIAG&t;&t;&t;0x000024c0
multiline_comment|/* 0x24c4 --&gt; 0x2800 unused */
multiline_comment|/* Receive Data Completion Control */
DECL|macro|RCVDCC_MODE
mdefine_line|#define RCVDCC_MODE&t;&t;&t;0x00002800
DECL|macro|RCVDCC_MODE_RESET
mdefine_line|#define  RCVDCC_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVDCC_MODE_ENABLE
mdefine_line|#define  RCVDCC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVDCC_MODE_ATTN_ENABLE
mdefine_line|#define  RCVDCC_MODE_ATTN_ENABLE&t; 0x00000004
multiline_comment|/* 0x2804 --&gt; 0x2c00 unused */
multiline_comment|/* Receive BD Initiator Control Registers */
DECL|macro|RCVBDI_MODE
mdefine_line|#define RCVBDI_MODE&t;&t;&t;0x00002c00
DECL|macro|RCVBDI_MODE_RESET
mdefine_line|#define  RCVBDI_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVBDI_MODE_ENABLE
mdefine_line|#define  RCVBDI_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVBDI_MODE_RCB_ATTN_ENAB
mdefine_line|#define  RCVBDI_MODE_RCB_ATTN_ENAB&t; 0x00000004
DECL|macro|RCVBDI_STATUS
mdefine_line|#define RCVBDI_STATUS&t;&t;&t;0x00002c04
DECL|macro|RCVBDI_STATUS_RCB_ATTN
mdefine_line|#define  RCVBDI_STATUS_RCB_ATTN&t;&t; 0x00000004
DECL|macro|RCVBDI_JUMBO_PROD_IDX
mdefine_line|#define RCVBDI_JUMBO_PROD_IDX&t;&t;0x00002c08
DECL|macro|RCVBDI_STD_PROD_IDX
mdefine_line|#define RCVBDI_STD_PROD_IDX&t;&t;0x00002c0c
DECL|macro|RCVBDI_MINI_PROD_IDX
mdefine_line|#define RCVBDI_MINI_PROD_IDX&t;&t;0x00002c10
DECL|macro|RCVBDI_MINI_THRESH
mdefine_line|#define RCVBDI_MINI_THRESH&t;&t;0x00002c14
DECL|macro|RCVBDI_STD_THRESH
mdefine_line|#define RCVBDI_STD_THRESH&t;&t;0x00002c18
DECL|macro|RCVBDI_JUMBO_THRESH
mdefine_line|#define RCVBDI_JUMBO_THRESH&t;&t;0x00002c1c
multiline_comment|/* 0x2c20 --&gt; 0x3000 unused */
multiline_comment|/* Receive BD Completion Control Registers */
DECL|macro|RCVCC_MODE
mdefine_line|#define RCVCC_MODE&t;&t;&t;0x00003000
DECL|macro|RCVCC_MODE_RESET
mdefine_line|#define  RCVCC_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVCC_MODE_ENABLE
mdefine_line|#define  RCVCC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVCC_MODE_ATTN_ENABLE
mdefine_line|#define  RCVCC_MODE_ATTN_ENABLE&t;&t; 0x00000004
DECL|macro|RCVCC_STATUS
mdefine_line|#define RCVCC_STATUS&t;&t;&t;0x00003004
DECL|macro|RCVCC_STATUS_ERROR_ATTN
mdefine_line|#define  RCVCC_STATUS_ERROR_ATTN&t; 0x00000004
DECL|macro|RCVCC_JUMP_PROD_IDX
mdefine_line|#define RCVCC_JUMP_PROD_IDX&t;&t;0x00003008
DECL|macro|RCVCC_STD_PROD_IDX
mdefine_line|#define RCVCC_STD_PROD_IDX&t;&t;0x0000300c
DECL|macro|RCVCC_MINI_PROD_IDX
mdefine_line|#define RCVCC_MINI_PROD_IDX&t;&t;0x00003010
multiline_comment|/* 0x3014 --&gt; 0x3400 unused */
multiline_comment|/* Receive list selector control registers */
DECL|macro|RCVLSC_MODE
mdefine_line|#define RCVLSC_MODE&t;&t;&t;0x00003400
DECL|macro|RCVLSC_MODE_RESET
mdefine_line|#define  RCVLSC_MODE_RESET&t;&t; 0x00000001
DECL|macro|RCVLSC_MODE_ENABLE
mdefine_line|#define  RCVLSC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RCVLSC_MODE_ATTN_ENABLE
mdefine_line|#define  RCVLSC_MODE_ATTN_ENABLE&t; 0x00000004
DECL|macro|RCVLSC_STATUS
mdefine_line|#define RCVLSC_STATUS&t;&t;&t;0x00003404
DECL|macro|RCVLSC_STATUS_ERROR_ATTN
mdefine_line|#define  RCVLSC_STATUS_ERROR_ATTN&t; 0x00000004
multiline_comment|/* 0x3408 --&gt; 0x3800 unused */
multiline_comment|/* Mbuf cluster free registers */
DECL|macro|MBFREE_MODE
mdefine_line|#define MBFREE_MODE&t;&t;&t;0x00003800
DECL|macro|MBFREE_MODE_RESET
mdefine_line|#define  MBFREE_MODE_RESET&t;&t; 0x00000001
DECL|macro|MBFREE_MODE_ENABLE
mdefine_line|#define  MBFREE_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|MBFREE_STATUS
mdefine_line|#define MBFREE_STATUS&t;&t;&t;0x00003804
multiline_comment|/* 0x3808 --&gt; 0x3c00 unused */
multiline_comment|/* Host coalescing control registers */
DECL|macro|HOSTCC_MODE
mdefine_line|#define HOSTCC_MODE&t;&t;&t;0x00003c00
DECL|macro|HOSTCC_MODE_RESET
mdefine_line|#define  HOSTCC_MODE_RESET&t;&t; 0x00000001
DECL|macro|HOSTCC_MODE_ENABLE
mdefine_line|#define  HOSTCC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|HOSTCC_MODE_ATTN
mdefine_line|#define  HOSTCC_MODE_ATTN&t;&t; 0x00000004
DECL|macro|HOSTCC_MODE_NOW
mdefine_line|#define  HOSTCC_MODE_NOW&t;&t; 0x00000008
DECL|macro|HOSTCC_MODE_FULL_STATUS
mdefine_line|#define  HOSTCC_MODE_FULL_STATUS&t; 0x00000000
DECL|macro|HOSTCC_MODE_64BYTE
mdefine_line|#define  HOSTCC_MODE_64BYTE&t;&t; 0x00000080
DECL|macro|HOSTCC_MODE_32BYTE
mdefine_line|#define  HOSTCC_MODE_32BYTE&t;&t; 0x00000100
DECL|macro|HOSTCC_MODE_CLRTICK_RXBD
mdefine_line|#define  HOSTCC_MODE_CLRTICK_RXBD&t; 0x00000200
DECL|macro|HOSTCC_MODE_CLRTICK_TXBD
mdefine_line|#define  HOSTCC_MODE_CLRTICK_TXBD&t; 0x00000400
DECL|macro|HOSTCC_MODE_NOINT_ON_NOW
mdefine_line|#define  HOSTCC_MODE_NOINT_ON_NOW&t; 0x00000800
DECL|macro|HOSTCC_MODE_NOINT_ON_FORCE
mdefine_line|#define  HOSTCC_MODE_NOINT_ON_FORCE&t; 0x00001000
DECL|macro|HOSTCC_STATUS
mdefine_line|#define HOSTCC_STATUS&t;&t;&t;0x00003c04
DECL|macro|HOSTCC_STATUS_ERROR_ATTN
mdefine_line|#define  HOSTCC_STATUS_ERROR_ATTN&t; 0x00000004
DECL|macro|HOSTCC_RXCOL_TICKS
mdefine_line|#define HOSTCC_RXCOL_TICKS&t;&t;0x00003c08
DECL|macro|LOW_RXCOL_TICKS
mdefine_line|#define  LOW_RXCOL_TICKS&t;&t; 0x00000032
DECL|macro|DEFAULT_RXCOL_TICKS
mdefine_line|#define  DEFAULT_RXCOL_TICKS&t;&t; 0x00000048
DECL|macro|HIGH_RXCOL_TICKS
mdefine_line|#define  HIGH_RXCOL_TICKS&t;&t; 0x00000096
DECL|macro|HOSTCC_TXCOL_TICKS
mdefine_line|#define HOSTCC_TXCOL_TICKS&t;&t;0x00003c0c
DECL|macro|LOW_TXCOL_TICKS
mdefine_line|#define  LOW_TXCOL_TICKS&t;&t; 0x00000096
DECL|macro|DEFAULT_TXCOL_TICKS
mdefine_line|#define  DEFAULT_TXCOL_TICKS&t;&t; 0x0000012c
DECL|macro|HIGH_TXCOL_TICKS
mdefine_line|#define  HIGH_TXCOL_TICKS&t;&t; 0x00000145
DECL|macro|HOSTCC_RXMAX_FRAMES
mdefine_line|#define HOSTCC_RXMAX_FRAMES&t;&t;0x00003c10
DECL|macro|LOW_RXMAX_FRAMES
mdefine_line|#define  LOW_RXMAX_FRAMES&t;&t; 0x00000005
DECL|macro|DEFAULT_RXMAX_FRAMES
mdefine_line|#define  DEFAULT_RXMAX_FRAMES&t;&t; 0x00000008
DECL|macro|HIGH_RXMAX_FRAMES
mdefine_line|#define  HIGH_RXMAX_FRAMES&t;&t; 0x00000012
DECL|macro|HOSTCC_TXMAX_FRAMES
mdefine_line|#define HOSTCC_TXMAX_FRAMES&t;&t;0x00003c14
DECL|macro|LOW_TXMAX_FRAMES
mdefine_line|#define  LOW_TXMAX_FRAMES&t;&t; 0x00000035
DECL|macro|DEFAULT_TXMAX_FRAMES
mdefine_line|#define  DEFAULT_TXMAX_FRAMES&t;&t; 0x0000004b
DECL|macro|HIGH_TXMAX_FRAMES
mdefine_line|#define  HIGH_TXMAX_FRAMES&t;&t; 0x00000052
DECL|macro|HOSTCC_RXCOAL_TICK_INT
mdefine_line|#define HOSTCC_RXCOAL_TICK_INT&t;&t;0x00003c18
DECL|macro|DEFAULT_RXCOAL_TICK_INT
mdefine_line|#define  DEFAULT_RXCOAL_TICK_INT&t; 0x00000019
DECL|macro|HOSTCC_TXCOAL_TICK_INT
mdefine_line|#define HOSTCC_TXCOAL_TICK_INT&t;&t;0x00003c1c
DECL|macro|DEFAULT_TXCOAL_TICK_INT
mdefine_line|#define  DEFAULT_TXCOAL_TICK_INT&t; 0x00000019
DECL|macro|HOSTCC_RXCOAL_MAXF_INT
mdefine_line|#define HOSTCC_RXCOAL_MAXF_INT&t;&t;0x00003c20
DECL|macro|DEFAULT_RXCOAL_MAXF_INT
mdefine_line|#define  DEFAULT_RXCOAL_MAXF_INT&t; 0x00000005
DECL|macro|HOSTCC_TXCOAL_MAXF_INT
mdefine_line|#define HOSTCC_TXCOAL_MAXF_INT&t;&t;0x00003c24
DECL|macro|DEFAULT_TXCOAL_MAXF_INT
mdefine_line|#define  DEFAULT_TXCOAL_MAXF_INT&t; 0x00000005
DECL|macro|HOSTCC_STAT_COAL_TICKS
mdefine_line|#define HOSTCC_STAT_COAL_TICKS&t;&t;0x00003c28
DECL|macro|DEFAULT_STAT_COAL_TICKS
mdefine_line|#define  DEFAULT_STAT_COAL_TICKS&t; 0x000f4240
multiline_comment|/* 0x3c2c --&gt; 0x3c30 unused */
DECL|macro|HOSTCC_STATS_BLK_HOST_ADDR
mdefine_line|#define HOSTCC_STATS_BLK_HOST_ADDR&t;0x00003c30 /* 64-bit */
DECL|macro|HOSTCC_STATUS_BLK_HOST_ADDR
mdefine_line|#define HOSTCC_STATUS_BLK_HOST_ADDR&t;0x00003c38 /* 64-bit */
DECL|macro|HOSTCC_STATS_BLK_NIC_ADDR
mdefine_line|#define HOSTCC_STATS_BLK_NIC_ADDR&t;0x00003c40
DECL|macro|HOSTCC_STATUS_BLK_NIC_ADDR
mdefine_line|#define HOSTCC_STATUS_BLK_NIC_ADDR&t;0x00003c44
DECL|macro|HOSTCC_FLOW_ATTN
mdefine_line|#define HOSTCC_FLOW_ATTN&t;&t;0x00003c48
multiline_comment|/* 0x3c4c --&gt; 0x3c50 unused */
DECL|macro|HOSTCC_JUMBO_CON_IDX
mdefine_line|#define HOSTCC_JUMBO_CON_IDX&t;&t;0x00003c50
DECL|macro|HOSTCC_STD_CON_IDX
mdefine_line|#define HOSTCC_STD_CON_IDX&t;&t;0x00003c54
DECL|macro|HOSTCC_MINI_CON_IDX
mdefine_line|#define HOSTCC_MINI_CON_IDX&t;&t;0x00003c58
multiline_comment|/* 0x3c5c --&gt; 0x3c80 unused */
DECL|macro|HOSTCC_RET_PROD_IDX_0
mdefine_line|#define HOSTCC_RET_PROD_IDX_0&t;&t;0x00003c80
DECL|macro|HOSTCC_RET_PROD_IDX_1
mdefine_line|#define HOSTCC_RET_PROD_IDX_1&t;&t;0x00003c84
DECL|macro|HOSTCC_RET_PROD_IDX_2
mdefine_line|#define HOSTCC_RET_PROD_IDX_2&t;&t;0x00003c88
DECL|macro|HOSTCC_RET_PROD_IDX_3
mdefine_line|#define HOSTCC_RET_PROD_IDX_3&t;&t;0x00003c8c
DECL|macro|HOSTCC_RET_PROD_IDX_4
mdefine_line|#define HOSTCC_RET_PROD_IDX_4&t;&t;0x00003c90
DECL|macro|HOSTCC_RET_PROD_IDX_5
mdefine_line|#define HOSTCC_RET_PROD_IDX_5&t;&t;0x00003c94
DECL|macro|HOSTCC_RET_PROD_IDX_6
mdefine_line|#define HOSTCC_RET_PROD_IDX_6&t;&t;0x00003c98
DECL|macro|HOSTCC_RET_PROD_IDX_7
mdefine_line|#define HOSTCC_RET_PROD_IDX_7&t;&t;0x00003c9c
DECL|macro|HOSTCC_RET_PROD_IDX_8
mdefine_line|#define HOSTCC_RET_PROD_IDX_8&t;&t;0x00003ca0
DECL|macro|HOSTCC_RET_PROD_IDX_9
mdefine_line|#define HOSTCC_RET_PROD_IDX_9&t;&t;0x00003ca4
DECL|macro|HOSTCC_RET_PROD_IDX_10
mdefine_line|#define HOSTCC_RET_PROD_IDX_10&t;&t;0x00003ca8
DECL|macro|HOSTCC_RET_PROD_IDX_11
mdefine_line|#define HOSTCC_RET_PROD_IDX_11&t;&t;0x00003cac
DECL|macro|HOSTCC_RET_PROD_IDX_12
mdefine_line|#define HOSTCC_RET_PROD_IDX_12&t;&t;0x00003cb0
DECL|macro|HOSTCC_RET_PROD_IDX_13
mdefine_line|#define HOSTCC_RET_PROD_IDX_13&t;&t;0x00003cb4
DECL|macro|HOSTCC_RET_PROD_IDX_14
mdefine_line|#define HOSTCC_RET_PROD_IDX_14&t;&t;0x00003cb8
DECL|macro|HOSTCC_RET_PROD_IDX_15
mdefine_line|#define HOSTCC_RET_PROD_IDX_15&t;&t;0x00003cbc
DECL|macro|HOSTCC_SND_CON_IDX_0
mdefine_line|#define HOSTCC_SND_CON_IDX_0&t;&t;0x00003cc0
DECL|macro|HOSTCC_SND_CON_IDX_1
mdefine_line|#define HOSTCC_SND_CON_IDX_1&t;&t;0x00003cc4
DECL|macro|HOSTCC_SND_CON_IDX_2
mdefine_line|#define HOSTCC_SND_CON_IDX_2&t;&t;0x00003cc8
DECL|macro|HOSTCC_SND_CON_IDX_3
mdefine_line|#define HOSTCC_SND_CON_IDX_3&t;&t;0x00003ccc
DECL|macro|HOSTCC_SND_CON_IDX_4
mdefine_line|#define HOSTCC_SND_CON_IDX_4&t;&t;0x00003cd0
DECL|macro|HOSTCC_SND_CON_IDX_5
mdefine_line|#define HOSTCC_SND_CON_IDX_5&t;&t;0x00003cd4
DECL|macro|HOSTCC_SND_CON_IDX_6
mdefine_line|#define HOSTCC_SND_CON_IDX_6&t;&t;0x00003cd8
DECL|macro|HOSTCC_SND_CON_IDX_7
mdefine_line|#define HOSTCC_SND_CON_IDX_7&t;&t;0x00003cdc
DECL|macro|HOSTCC_SND_CON_IDX_8
mdefine_line|#define HOSTCC_SND_CON_IDX_8&t;&t;0x00003ce0
DECL|macro|HOSTCC_SND_CON_IDX_9
mdefine_line|#define HOSTCC_SND_CON_IDX_9&t;&t;0x00003ce4
DECL|macro|HOSTCC_SND_CON_IDX_10
mdefine_line|#define HOSTCC_SND_CON_IDX_10&t;&t;0x00003ce8
DECL|macro|HOSTCC_SND_CON_IDX_11
mdefine_line|#define HOSTCC_SND_CON_IDX_11&t;&t;0x00003cec
DECL|macro|HOSTCC_SND_CON_IDX_12
mdefine_line|#define HOSTCC_SND_CON_IDX_12&t;&t;0x00003cf0
DECL|macro|HOSTCC_SND_CON_IDX_13
mdefine_line|#define HOSTCC_SND_CON_IDX_13&t;&t;0x00003cf4
DECL|macro|HOSTCC_SND_CON_IDX_14
mdefine_line|#define HOSTCC_SND_CON_IDX_14&t;&t;0x00003cf8
DECL|macro|HOSTCC_SND_CON_IDX_15
mdefine_line|#define HOSTCC_SND_CON_IDX_15&t;&t;0x00003cfc
multiline_comment|/* 0x3d00 --&gt; 0x4000 unused */
multiline_comment|/* Memory arbiter control registers */
DECL|macro|MEMARB_MODE
mdefine_line|#define MEMARB_MODE&t;&t;&t;0x00004000
DECL|macro|MEMARB_MODE_RESET
mdefine_line|#define  MEMARB_MODE_RESET&t;&t; 0x00000001
DECL|macro|MEMARB_MODE_ENABLE
mdefine_line|#define  MEMARB_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|MEMARB_STATUS
mdefine_line|#define MEMARB_STATUS&t;&t;&t;0x00004004
DECL|macro|MEMARB_TRAP_ADDR_LOW
mdefine_line|#define MEMARB_TRAP_ADDR_LOW&t;&t;0x00004008
DECL|macro|MEMARB_TRAP_ADDR_HIGH
mdefine_line|#define MEMARB_TRAP_ADDR_HIGH&t;&t;0x0000400c
multiline_comment|/* 0x4010 --&gt; 0x4400 unused */
multiline_comment|/* Buffer manager control registers */
DECL|macro|BUFMGR_MODE
mdefine_line|#define BUFMGR_MODE&t;&t;&t;0x00004400
DECL|macro|BUFMGR_MODE_RESET
mdefine_line|#define  BUFMGR_MODE_RESET&t;&t; 0x00000001
DECL|macro|BUFMGR_MODE_ENABLE
mdefine_line|#define  BUFMGR_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|BUFMGR_MODE_ATTN_ENABLE
mdefine_line|#define  BUFMGR_MODE_ATTN_ENABLE&t; 0x00000004
DECL|macro|BUFMGR_MODE_BM_TEST
mdefine_line|#define  BUFMGR_MODE_BM_TEST&t;&t; 0x00000008
DECL|macro|BUFMGR_MODE_MBLOW_ATTN_ENAB
mdefine_line|#define  BUFMGR_MODE_MBLOW_ATTN_ENAB&t; 0x00000010
DECL|macro|BUFMGR_STATUS
mdefine_line|#define BUFMGR_STATUS&t;&t;&t;0x00004404
DECL|macro|BUFMGR_STATUS_ERROR
mdefine_line|#define  BUFMGR_STATUS_ERROR&t;&t; 0x00000004
DECL|macro|BUFMGR_STATUS_MBLOW
mdefine_line|#define  BUFMGR_STATUS_MBLOW&t;&t; 0x00000010
DECL|macro|BUFMGR_MB_POOL_ADDR
mdefine_line|#define BUFMGR_MB_POOL_ADDR&t;&t;0x00004408
DECL|macro|BUFMGR_MB_POOL_SIZE
mdefine_line|#define BUFMGR_MB_POOL_SIZE&t;&t;0x0000440c
DECL|macro|BUFMGR_MB_RDMA_LOW_WATER
mdefine_line|#define BUFMGR_MB_RDMA_LOW_WATER&t;0x00004410
DECL|macro|DEFAULT_MB_RDMA_LOW_WATER
mdefine_line|#define  DEFAULT_MB_RDMA_LOW_WATER&t; 0x00000040
DECL|macro|DEFAULT_MB_RDMA_LOW_WATER_JUMBO
mdefine_line|#define  DEFAULT_MB_RDMA_LOW_WATER_JUMBO 0x00000130
DECL|macro|BUFMGR_MB_MACRX_LOW_WATER
mdefine_line|#define BUFMGR_MB_MACRX_LOW_WATER&t;0x00004414
DECL|macro|DEFAULT_MB_MACRX_LOW_WATER
mdefine_line|#define  DEFAULT_MB_MACRX_LOW_WATER&t;  0x00000020
DECL|macro|DEFAULT_MB_MACRX_LOW_WATER_JUMBO
mdefine_line|#define  DEFAULT_MB_MACRX_LOW_WATER_JUMBO 0x00000098
DECL|macro|BUFMGR_MB_HIGH_WATER
mdefine_line|#define BUFMGR_MB_HIGH_WATER&t;&t;0x00004418
DECL|macro|DEFAULT_MB_HIGH_WATER
mdefine_line|#define  DEFAULT_MB_HIGH_WATER&t;&t; 0x00000060
DECL|macro|DEFAULT_MB_HIGH_WATER_JUMBO
mdefine_line|#define  DEFAULT_MB_HIGH_WATER_JUMBO&t; 0x0000017c
DECL|macro|BUFMGR_RX_MB_ALLOC_REQ
mdefine_line|#define BUFMGR_RX_MB_ALLOC_REQ&t;&t;0x0000441c
DECL|macro|BUFMGR_MB_ALLOC_BIT
mdefine_line|#define  BUFMGR_MB_ALLOC_BIT&t;&t; 0x10000000
DECL|macro|BUFMGR_RX_MB_ALLOC_RESP
mdefine_line|#define BUFMGR_RX_MB_ALLOC_RESP&t;&t;0x00004420
DECL|macro|BUFMGR_TX_MB_ALLOC_REQ
mdefine_line|#define BUFMGR_TX_MB_ALLOC_REQ&t;&t;0x00004424
DECL|macro|BUFMGR_TX_MB_ALLOC_RESP
mdefine_line|#define BUFMGR_TX_MB_ALLOC_RESP&t;&t;0x00004428
DECL|macro|BUFMGR_DMA_DESC_POOL_ADDR
mdefine_line|#define BUFMGR_DMA_DESC_POOL_ADDR&t;0x0000442c
DECL|macro|BUFMGR_DMA_DESC_POOL_SIZE
mdefine_line|#define BUFMGR_DMA_DESC_POOL_SIZE&t;0x00004430
DECL|macro|BUFMGR_DMA_LOW_WATER
mdefine_line|#define BUFMGR_DMA_LOW_WATER&t;&t;0x00004434
DECL|macro|DEFAULT_DMA_LOW_WATER
mdefine_line|#define  DEFAULT_DMA_LOW_WATER&t;&t; 0x00000005
DECL|macro|BUFMGR_DMA_HIGH_WATER
mdefine_line|#define BUFMGR_DMA_HIGH_WATER&t;&t;0x00004438
DECL|macro|DEFAULT_DMA_HIGH_WATER
mdefine_line|#define  DEFAULT_DMA_HIGH_WATER&t;&t; 0x0000000a
DECL|macro|BUFMGR_RX_DMA_ALLOC_REQ
mdefine_line|#define BUFMGR_RX_DMA_ALLOC_REQ&t;&t;0x0000443c
DECL|macro|BUFMGR_RX_DMA_ALLOC_RESP
mdefine_line|#define BUFMGR_RX_DMA_ALLOC_RESP&t;0x00004440
DECL|macro|BUFMGR_TX_DMA_ALLOC_REQ
mdefine_line|#define BUFMGR_TX_DMA_ALLOC_REQ&t;&t;0x00004444
DECL|macro|BUFMGR_TX_DMA_ALLOC_RESP
mdefine_line|#define BUFMGR_TX_DMA_ALLOC_RESP&t;0x00004448
DECL|macro|BUFMGR_HWDIAG_0
mdefine_line|#define BUFMGR_HWDIAG_0&t;&t;&t;0x0000444c
DECL|macro|BUFMGR_HWDIAG_1
mdefine_line|#define BUFMGR_HWDIAG_1&t;&t;&t;0x00004450
DECL|macro|BUFMGR_HWDIAG_2
mdefine_line|#define BUFMGR_HWDIAG_2&t;&t;&t;0x00004454
multiline_comment|/* 0x4458 --&gt; 0x4800 unused */
multiline_comment|/* Read DMA control registers */
DECL|macro|RDMAC_MODE
mdefine_line|#define RDMAC_MODE&t;&t;&t;0x00004800
DECL|macro|RDMAC_MODE_RESET
mdefine_line|#define  RDMAC_MODE_RESET&t;&t; 0x00000001
DECL|macro|RDMAC_MODE_ENABLE
mdefine_line|#define  RDMAC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|RDMAC_MODE_TGTABORT_ENAB
mdefine_line|#define  RDMAC_MODE_TGTABORT_ENAB&t; 0x00000004
DECL|macro|RDMAC_MODE_MSTABORT_ENAB
mdefine_line|#define  RDMAC_MODE_MSTABORT_ENAB&t; 0x00000008
DECL|macro|RDMAC_MODE_PARITYERR_ENAB
mdefine_line|#define  RDMAC_MODE_PARITYERR_ENAB&t; 0x00000010
DECL|macro|RDMAC_MODE_ADDROFLOW_ENAB
mdefine_line|#define  RDMAC_MODE_ADDROFLOW_ENAB&t; 0x00000020
DECL|macro|RDMAC_MODE_FIFOOFLOW_ENAB
mdefine_line|#define  RDMAC_MODE_FIFOOFLOW_ENAB&t; 0x00000040
DECL|macro|RDMAC_MODE_FIFOURUN_ENAB
mdefine_line|#define  RDMAC_MODE_FIFOURUN_ENAB&t; 0x00000080
DECL|macro|RDMAC_MODE_FIFOOREAD_ENAB
mdefine_line|#define  RDMAC_MODE_FIFOOREAD_ENAB&t; 0x00000100
DECL|macro|RDMAC_MODE_LNGREAD_ENAB
mdefine_line|#define  RDMAC_MODE_LNGREAD_ENAB&t; 0x00000200
DECL|macro|RDMAC_STATUS
mdefine_line|#define RDMAC_STATUS&t;&t;&t;0x00004804
DECL|macro|RDMAC_STATUS_TGTABORT
mdefine_line|#define  RDMAC_STATUS_TGTABORT&t;&t; 0x00000004
DECL|macro|RDMAC_STATUS_MSTABORT
mdefine_line|#define  RDMAC_STATUS_MSTABORT&t;&t; 0x00000008
DECL|macro|RDMAC_STATUS_PARITYERR
mdefine_line|#define  RDMAC_STATUS_PARITYERR&t;&t; 0x00000010
DECL|macro|RDMAC_STATUS_ADDROFLOW
mdefine_line|#define  RDMAC_STATUS_ADDROFLOW&t;&t; 0x00000020
DECL|macro|RDMAC_STATUS_FIFOOFLOW
mdefine_line|#define  RDMAC_STATUS_FIFOOFLOW&t;&t; 0x00000040
DECL|macro|RDMAC_STATUS_FIFOURUN
mdefine_line|#define  RDMAC_STATUS_FIFOURUN&t;&t; 0x00000080
DECL|macro|RDMAC_STATUS_FIFOOREAD
mdefine_line|#define  RDMAC_STATUS_FIFOOREAD&t;&t; 0x00000100
DECL|macro|RDMAC_STATUS_LNGREAD
mdefine_line|#define  RDMAC_STATUS_LNGREAD&t;&t; 0x00000200
multiline_comment|/* 0x4808 --&gt; 0x4c00 unused */
multiline_comment|/* Write DMA control registers */
DECL|macro|WDMAC_MODE
mdefine_line|#define WDMAC_MODE&t;&t;&t;0x00004c00
DECL|macro|WDMAC_MODE_RESET
mdefine_line|#define  WDMAC_MODE_RESET&t;&t; 0x00000001
DECL|macro|WDMAC_MODE_ENABLE
mdefine_line|#define  WDMAC_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|WDMAC_MODE_TGTABORT_ENAB
mdefine_line|#define  WDMAC_MODE_TGTABORT_ENAB&t; 0x00000004
DECL|macro|WDMAC_MODE_MSTABORT_ENAB
mdefine_line|#define  WDMAC_MODE_MSTABORT_ENAB&t; 0x00000008
DECL|macro|WDMAC_MODE_PARITYERR_ENAB
mdefine_line|#define  WDMAC_MODE_PARITYERR_ENAB&t; 0x00000010
DECL|macro|WDMAC_MODE_ADDROFLOW_ENAB
mdefine_line|#define  WDMAC_MODE_ADDROFLOW_ENAB&t; 0x00000020
DECL|macro|WDMAC_MODE_FIFOOFLOW_ENAB
mdefine_line|#define  WDMAC_MODE_FIFOOFLOW_ENAB&t; 0x00000040
DECL|macro|WDMAC_MODE_FIFOURUN_ENAB
mdefine_line|#define  WDMAC_MODE_FIFOURUN_ENAB&t; 0x00000080
DECL|macro|WDMAC_MODE_FIFOOREAD_ENAB
mdefine_line|#define  WDMAC_MODE_FIFOOREAD_ENAB&t; 0x00000100
DECL|macro|WDMAC_MODE_LNGREAD_ENAB
mdefine_line|#define  WDMAC_MODE_LNGREAD_ENAB&t; 0x00000200
DECL|macro|WDMAC_STATUS
mdefine_line|#define WDMAC_STATUS&t;&t;&t;0x00004c04
DECL|macro|WDMAC_STATUS_TGTABORT
mdefine_line|#define  WDMAC_STATUS_TGTABORT&t;&t; 0x00000004
DECL|macro|WDMAC_STATUS_MSTABORT
mdefine_line|#define  WDMAC_STATUS_MSTABORT&t;&t; 0x00000008
DECL|macro|WDMAC_STATUS_PARITYERR
mdefine_line|#define  WDMAC_STATUS_PARITYERR&t;&t; 0x00000010
DECL|macro|WDMAC_STATUS_ADDROFLOW
mdefine_line|#define  WDMAC_STATUS_ADDROFLOW&t;&t; 0x00000020
DECL|macro|WDMAC_STATUS_FIFOOFLOW
mdefine_line|#define  WDMAC_STATUS_FIFOOFLOW&t;&t; 0x00000040
DECL|macro|WDMAC_STATUS_FIFOURUN
mdefine_line|#define  WDMAC_STATUS_FIFOURUN&t;&t; 0x00000080
DECL|macro|WDMAC_STATUS_FIFOOREAD
mdefine_line|#define  WDMAC_STATUS_FIFOOREAD&t;&t; 0x00000100
DECL|macro|WDMAC_STATUS_LNGREAD
mdefine_line|#define  WDMAC_STATUS_LNGREAD&t;&t; 0x00000200
multiline_comment|/* 0x4c08 --&gt; 0x5000 unused */
multiline_comment|/* Per-cpu register offsets (arm9) */
DECL|macro|CPU_MODE
mdefine_line|#define CPU_MODE&t;&t;&t;0x00000000
DECL|macro|CPU_MODE_RESET
mdefine_line|#define  CPU_MODE_RESET&t;&t;&t; 0x00000001
DECL|macro|CPU_MODE_HALT
mdefine_line|#define  CPU_MODE_HALT&t;&t;&t; 0x00000400
DECL|macro|CPU_STATE
mdefine_line|#define CPU_STATE&t;&t;&t;0x00000004
DECL|macro|CPU_EVTMASK
mdefine_line|#define CPU_EVTMASK&t;&t;&t;0x00000008
multiline_comment|/* 0xc --&gt; 0x1c reserved */
DECL|macro|CPU_PC
mdefine_line|#define CPU_PC&t;&t;&t;&t;0x0000001c
DECL|macro|CPU_INSN
mdefine_line|#define CPU_INSN&t;&t;&t;0x00000020
DECL|macro|CPU_SPAD_UFLOW
mdefine_line|#define CPU_SPAD_UFLOW&t;&t;&t;0x00000024
DECL|macro|CPU_WDOG_CLEAR
mdefine_line|#define CPU_WDOG_CLEAR&t;&t;&t;0x00000028
DECL|macro|CPU_WDOG_VECTOR
mdefine_line|#define CPU_WDOG_VECTOR&t;&t;&t;0x0000002c
DECL|macro|CPU_WDOG_PC
mdefine_line|#define CPU_WDOG_PC&t;&t;&t;0x00000030
DECL|macro|CPU_HW_BP
mdefine_line|#define CPU_HW_BP&t;&t;&t;0x00000034
multiline_comment|/* 0x38 --&gt; 0x44 unused */
DECL|macro|CPU_WDOG_SAVED_STATE
mdefine_line|#define CPU_WDOG_SAVED_STATE&t;&t;0x00000044
DECL|macro|CPU_LAST_BRANCH_ADDR
mdefine_line|#define CPU_LAST_BRANCH_ADDR&t;&t;0x00000048
DECL|macro|CPU_SPAD_UFLOW_SET
mdefine_line|#define CPU_SPAD_UFLOW_SET&t;&t;0x0000004c
multiline_comment|/* 0x50 --&gt; 0x200 unused */
DECL|macro|CPU_R0
mdefine_line|#define CPU_R0&t;&t;&t;&t;0x00000200
DECL|macro|CPU_R1
mdefine_line|#define CPU_R1&t;&t;&t;&t;0x00000204
DECL|macro|CPU_R2
mdefine_line|#define CPU_R2&t;&t;&t;&t;0x00000208
DECL|macro|CPU_R3
mdefine_line|#define CPU_R3&t;&t;&t;&t;0x0000020c
DECL|macro|CPU_R4
mdefine_line|#define CPU_R4&t;&t;&t;&t;0x00000210
DECL|macro|CPU_R5
mdefine_line|#define CPU_R5&t;&t;&t;&t;0x00000214
DECL|macro|CPU_R6
mdefine_line|#define CPU_R6&t;&t;&t;&t;0x00000218
DECL|macro|CPU_R7
mdefine_line|#define CPU_R7&t;&t;&t;&t;0x0000021c
DECL|macro|CPU_R8
mdefine_line|#define CPU_R8&t;&t;&t;&t;0x00000220
DECL|macro|CPU_R9
mdefine_line|#define CPU_R9&t;&t;&t;&t;0x00000224
DECL|macro|CPU_R10
mdefine_line|#define CPU_R10&t;&t;&t;&t;0x00000228
DECL|macro|CPU_R11
mdefine_line|#define CPU_R11&t;&t;&t;&t;0x0000022c
DECL|macro|CPU_R12
mdefine_line|#define CPU_R12&t;&t;&t;&t;0x00000230
DECL|macro|CPU_R13
mdefine_line|#define CPU_R13&t;&t;&t;&t;0x00000234
DECL|macro|CPU_R14
mdefine_line|#define CPU_R14&t;&t;&t;&t;0x00000238
DECL|macro|CPU_R15
mdefine_line|#define CPU_R15&t;&t;&t;&t;0x0000023c
DECL|macro|CPU_R16
mdefine_line|#define CPU_R16&t;&t;&t;&t;0x00000240
DECL|macro|CPU_R17
mdefine_line|#define CPU_R17&t;&t;&t;&t;0x00000244
DECL|macro|CPU_R18
mdefine_line|#define CPU_R18&t;&t;&t;&t;0x00000248
DECL|macro|CPU_R19
mdefine_line|#define CPU_R19&t;&t;&t;&t;0x0000024c
DECL|macro|CPU_R20
mdefine_line|#define CPU_R20&t;&t;&t;&t;0x00000250
DECL|macro|CPU_R21
mdefine_line|#define CPU_R21&t;&t;&t;&t;0x00000254
DECL|macro|CPU_R22
mdefine_line|#define CPU_R22&t;&t;&t;&t;0x00000258
DECL|macro|CPU_R23
mdefine_line|#define CPU_R23&t;&t;&t;&t;0x0000025c
DECL|macro|CPU_R24
mdefine_line|#define CPU_R24&t;&t;&t;&t;0x00000260
DECL|macro|CPU_R25
mdefine_line|#define CPU_R25&t;&t;&t;&t;0x00000264
DECL|macro|CPU_R26
mdefine_line|#define CPU_R26&t;&t;&t;&t;0x00000268
DECL|macro|CPU_R27
mdefine_line|#define CPU_R27&t;&t;&t;&t;0x0000026c
DECL|macro|CPU_R28
mdefine_line|#define CPU_R28&t;&t;&t;&t;0x00000270
DECL|macro|CPU_R29
mdefine_line|#define CPU_R29&t;&t;&t;&t;0x00000274
DECL|macro|CPU_R30
mdefine_line|#define CPU_R30&t;&t;&t;&t;0x00000278
DECL|macro|CPU_R31
mdefine_line|#define CPU_R31&t;&t;&t;&t;0x0000027c
multiline_comment|/* 0x280 --&gt; 0x400 unused */
DECL|macro|RX_CPU_BASE
mdefine_line|#define RX_CPU_BASE&t;&t;&t;0x00005000
DECL|macro|TX_CPU_BASE
mdefine_line|#define TX_CPU_BASE&t;&t;&t;0x00005400
multiline_comment|/* Mailboxes */
DECL|macro|GRCMBOX_INTERRUPT_0
mdefine_line|#define GRCMBOX_INTERRUPT_0&t;&t;0x00005800 /* 64-bit */
DECL|macro|GRCMBOX_INTERRUPT_1
mdefine_line|#define GRCMBOX_INTERRUPT_1&t;&t;0x00005808 /* 64-bit */
DECL|macro|GRCMBOX_INTERRUPT_2
mdefine_line|#define GRCMBOX_INTERRUPT_2&t;&t;0x00005810 /* 64-bit */
DECL|macro|GRCMBOX_INTERRUPT_3
mdefine_line|#define GRCMBOX_INTERRUPT_3&t;&t;0x00005818 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_0
mdefine_line|#define GRCMBOX_GENERAL_0&t;&t;0x00005820 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_1
mdefine_line|#define GRCMBOX_GENERAL_1&t;&t;0x00005828 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_2
mdefine_line|#define GRCMBOX_GENERAL_2&t;&t;0x00005830 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_3
mdefine_line|#define GRCMBOX_GENERAL_3&t;&t;0x00005838 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_4
mdefine_line|#define GRCMBOX_GENERAL_4&t;&t;0x00005840 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_5
mdefine_line|#define GRCMBOX_GENERAL_5&t;&t;0x00005848 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_6
mdefine_line|#define GRCMBOX_GENERAL_6&t;&t;0x00005850 /* 64-bit */
DECL|macro|GRCMBOX_GENERAL_7
mdefine_line|#define GRCMBOX_GENERAL_7&t;&t;0x00005858 /* 64-bit */
DECL|macro|GRCMBOX_RELOAD_STAT
mdefine_line|#define GRCMBOX_RELOAD_STAT&t;&t;0x00005860 /* 64-bit */
DECL|macro|GRCMBOX_RCVSTD_PROD_IDX
mdefine_line|#define GRCMBOX_RCVSTD_PROD_IDX&t;&t;0x00005868 /* 64-bit */
DECL|macro|GRCMBOX_RCVJUMBO_PROD_IDX
mdefine_line|#define GRCMBOX_RCVJUMBO_PROD_IDX&t;0x00005870 /* 64-bit */
DECL|macro|GRCMBOX_RCVMINI_PROD_IDX
mdefine_line|#define GRCMBOX_RCVMINI_PROD_IDX&t;0x00005878 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_0
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_0&t;0x00005880 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_1
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_1&t;0x00005888 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_2
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_2&t;0x00005890 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_3
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_3&t;0x00005898 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_4
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_4&t;0x000058a0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_5
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_5&t;0x000058a8 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_6
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_6&t;0x000058b0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_7
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_7&t;0x000058b8 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_8
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_8&t;0x000058c0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_9
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_9&t;0x000058c8 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_10
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_10&t;0x000058d0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_11
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_11&t;0x000058d8 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_12
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_12&t;0x000058e0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_13
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_13&t;0x000058e8 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_14
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_14&t;0x000058f0 /* 64-bit */
DECL|macro|GRCMBOX_RCVRET_CON_IDX_15
mdefine_line|#define GRCMBOX_RCVRET_CON_IDX_15&t;0x000058f8 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_0
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_0&t;0x00005900 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_1
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_1&t;0x00005908 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_2
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_2&t;0x00005910 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_3
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_3&t;0x00005918 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_4
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_4&t;0x00005920 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_5
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_5&t;0x00005928 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_6
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_6&t;0x00005930 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_7
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_7&t;0x00005938 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_8
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_8&t;0x00005940 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_9
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_9&t;0x00005948 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_10
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_10&t;0x00005950 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_11
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_11&t;0x00005958 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_12
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_12&t;0x00005960 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_13
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_13&t;0x00005968 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_14
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_14&t;0x00005970 /* 64-bit */
DECL|macro|GRCMBOX_SNDHOST_PROD_IDX_15
mdefine_line|#define GRCMBOX_SNDHOST_PROD_IDX_15&t;0x00005978 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_0
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_0&t;0x00005980 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_1
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_1&t;0x00005988 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_2
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_2&t;0x00005990 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_3
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_3&t;0x00005998 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_4
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_4&t;0x000059a0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_5
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_5&t;0x000059a8 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_6
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_6&t;0x000059b0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_7
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_7&t;0x000059b8 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_8
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_8&t;0x000059c0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_9
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_9&t;0x000059c8 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_10
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_10&t;0x000059d0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_11
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_11&t;0x000059d8 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_12
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_12&t;0x000059e0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_13
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_13&t;0x000059e8 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_14
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_14&t;0x000059f0 /* 64-bit */
DECL|macro|GRCMBOX_SNDNIC_PROD_IDX_15
mdefine_line|#define GRCMBOX_SNDNIC_PROD_IDX_15&t;0x000059f8 /* 64-bit */
DECL|macro|GRCMBOX_HIGH_PRIO_EV_VECTOR
mdefine_line|#define GRCMBOX_HIGH_PRIO_EV_VECTOR&t;0x00005a00
DECL|macro|GRCMBOX_HIGH_PRIO_EV_MASK
mdefine_line|#define GRCMBOX_HIGH_PRIO_EV_MASK&t;0x00005a04
DECL|macro|GRCMBOX_LOW_PRIO_EV_VEC
mdefine_line|#define GRCMBOX_LOW_PRIO_EV_VEC&t;&t;0x00005a08
DECL|macro|GRCMBOX_LOW_PRIO_EV_MASK
mdefine_line|#define GRCMBOX_LOW_PRIO_EV_MASK&t;0x00005a0c
multiline_comment|/* 0x5a10 --&gt; 0x5c00 */
multiline_comment|/* Flow Through queues */
DECL|macro|FTQ_RESET
mdefine_line|#define FTQ_RESET&t;&t;&t;0x00005c00
multiline_comment|/* 0x5c04 --&gt; 0x5c10 unused */
DECL|macro|FTQ_DMA_NORM_READ_CTL
mdefine_line|#define FTQ_DMA_NORM_READ_CTL&t;&t;0x00005c10
DECL|macro|FTQ_DMA_NORM_READ_FULL_CNT
mdefine_line|#define FTQ_DMA_NORM_READ_FULL_CNT&t;0x00005c14
DECL|macro|FTQ_DMA_NORM_READ_FIFO_ENQDEQ
mdefine_line|#define FTQ_DMA_NORM_READ_FIFO_ENQDEQ&t;0x00005c18
DECL|macro|FTQ_DMA_NORM_READ_WRITE_PEEK
mdefine_line|#define FTQ_DMA_NORM_READ_WRITE_PEEK&t;0x00005c1c
DECL|macro|FTQ_DMA_HIGH_READ_CTL
mdefine_line|#define FTQ_DMA_HIGH_READ_CTL&t;&t;0x00005c20
DECL|macro|FTQ_DMA_HIGH_READ_FULL_CNT
mdefine_line|#define FTQ_DMA_HIGH_READ_FULL_CNT&t;0x00005c24
DECL|macro|FTQ_DMA_HIGH_READ_FIFO_ENQDEQ
mdefine_line|#define FTQ_DMA_HIGH_READ_FIFO_ENQDEQ&t;0x00005c28
DECL|macro|FTQ_DMA_HIGH_READ_WRITE_PEEK
mdefine_line|#define FTQ_DMA_HIGH_READ_WRITE_PEEK&t;0x00005c2c
DECL|macro|FTQ_DMA_COMP_DISC_CTL
mdefine_line|#define FTQ_DMA_COMP_DISC_CTL&t;&t;0x00005c30
DECL|macro|FTQ_DMA_COMP_DISC_FULL_CNT
mdefine_line|#define FTQ_DMA_COMP_DISC_FULL_CNT&t;0x00005c34
DECL|macro|FTQ_DMA_COMP_DISC_FIFO_ENQDEQ
mdefine_line|#define FTQ_DMA_COMP_DISC_FIFO_ENQDEQ&t;0x00005c38
DECL|macro|FTQ_DMA_COMP_DISC_WRITE_PEEK
mdefine_line|#define FTQ_DMA_COMP_DISC_WRITE_PEEK&t;0x00005c3c
DECL|macro|FTQ_SEND_BD_COMP_CTL
mdefine_line|#define FTQ_SEND_BD_COMP_CTL&t;&t;0x00005c40
DECL|macro|FTQ_SEND_BD_COMP_FULL_CNT
mdefine_line|#define FTQ_SEND_BD_COMP_FULL_CNT&t;0x00005c44
DECL|macro|FTQ_SEND_BD_COMP_FIFO_ENQDEQ
mdefine_line|#define FTQ_SEND_BD_COMP_FIFO_ENQDEQ&t;0x00005c48
DECL|macro|FTQ_SEND_BD_COMP_WRITE_PEEK
mdefine_line|#define FTQ_SEND_BD_COMP_WRITE_PEEK&t;0x00005c4c
DECL|macro|FTQ_SEND_DATA_INIT_CTL
mdefine_line|#define FTQ_SEND_DATA_INIT_CTL&t;&t;0x00005c50
DECL|macro|FTQ_SEND_DATA_INIT_FULL_CNT
mdefine_line|#define FTQ_SEND_DATA_INIT_FULL_CNT&t;0x00005c54
DECL|macro|FTQ_SEND_DATA_INIT_FIFO_ENQDEQ
mdefine_line|#define FTQ_SEND_DATA_INIT_FIFO_ENQDEQ&t;0x00005c58
DECL|macro|FTQ_SEND_DATA_INIT_WRITE_PEEK
mdefine_line|#define FTQ_SEND_DATA_INIT_WRITE_PEEK&t;0x00005c5c
DECL|macro|FTQ_DMA_NORM_WRITE_CTL
mdefine_line|#define FTQ_DMA_NORM_WRITE_CTL&t;&t;0x00005c60
DECL|macro|FTQ_DMA_NORM_WRITE_FULL_CNT
mdefine_line|#define FTQ_DMA_NORM_WRITE_FULL_CNT&t;0x00005c64
DECL|macro|FTQ_DMA_NORM_WRITE_FIFO_ENQDEQ
mdefine_line|#define FTQ_DMA_NORM_WRITE_FIFO_ENQDEQ&t;0x00005c68
DECL|macro|FTQ_DMA_NORM_WRITE_WRITE_PEEK
mdefine_line|#define FTQ_DMA_NORM_WRITE_WRITE_PEEK&t;0x00005c6c
DECL|macro|FTQ_DMA_HIGH_WRITE_CTL
mdefine_line|#define FTQ_DMA_HIGH_WRITE_CTL&t;&t;0x00005c70
DECL|macro|FTQ_DMA_HIGH_WRITE_FULL_CNT
mdefine_line|#define FTQ_DMA_HIGH_WRITE_FULL_CNT&t;0x00005c74
DECL|macro|FTQ_DMA_HIGH_WRITE_FIFO_ENQDEQ
mdefine_line|#define FTQ_DMA_HIGH_WRITE_FIFO_ENQDEQ&t;0x00005c78
DECL|macro|FTQ_DMA_HIGH_WRITE_WRITE_PEEK
mdefine_line|#define FTQ_DMA_HIGH_WRITE_WRITE_PEEK&t;0x00005c7c
DECL|macro|FTQ_SWTYPE1_CTL
mdefine_line|#define FTQ_SWTYPE1_CTL&t;&t;&t;0x00005c80
DECL|macro|FTQ_SWTYPE1_FULL_CNT
mdefine_line|#define FTQ_SWTYPE1_FULL_CNT&t;&t;0x00005c84
DECL|macro|FTQ_SWTYPE1_FIFO_ENQDEQ
mdefine_line|#define FTQ_SWTYPE1_FIFO_ENQDEQ&t;&t;0x00005c88
DECL|macro|FTQ_SWTYPE1_WRITE_PEEK
mdefine_line|#define FTQ_SWTYPE1_WRITE_PEEK&t;&t;0x00005c8c
DECL|macro|FTQ_SEND_DATA_COMP_CTL
mdefine_line|#define FTQ_SEND_DATA_COMP_CTL&t;&t;0x00005c90
DECL|macro|FTQ_SEND_DATA_COMP_FULL_CNT
mdefine_line|#define FTQ_SEND_DATA_COMP_FULL_CNT&t;0x00005c94
DECL|macro|FTQ_SEND_DATA_COMP_FIFO_ENQDEQ
mdefine_line|#define FTQ_SEND_DATA_COMP_FIFO_ENQDEQ&t;0x00005c98
DECL|macro|FTQ_SEND_DATA_COMP_WRITE_PEEK
mdefine_line|#define FTQ_SEND_DATA_COMP_WRITE_PEEK&t;0x00005c9c
DECL|macro|FTQ_HOST_COAL_CTL
mdefine_line|#define FTQ_HOST_COAL_CTL&t;&t;0x00005ca0
DECL|macro|FTQ_HOST_COAL_FULL_CNT
mdefine_line|#define FTQ_HOST_COAL_FULL_CNT&t;&t;0x00005ca4
DECL|macro|FTQ_HOST_COAL_FIFO_ENQDEQ
mdefine_line|#define FTQ_HOST_COAL_FIFO_ENQDEQ&t;0x00005ca8
DECL|macro|FTQ_HOST_COAL_WRITE_PEEK
mdefine_line|#define FTQ_HOST_COAL_WRITE_PEEK&t;0x00005cac
DECL|macro|FTQ_MAC_TX_CTL
mdefine_line|#define FTQ_MAC_TX_CTL&t;&t;&t;0x00005cb0
DECL|macro|FTQ_MAC_TX_FULL_CNT
mdefine_line|#define FTQ_MAC_TX_FULL_CNT&t;&t;0x00005cb4
DECL|macro|FTQ_MAC_TX_FIFO_ENQDEQ
mdefine_line|#define FTQ_MAC_TX_FIFO_ENQDEQ&t;&t;0x00005cb8
DECL|macro|FTQ_MAC_TX_WRITE_PEEK
mdefine_line|#define FTQ_MAC_TX_WRITE_PEEK&t;&t;0x00005cbc
DECL|macro|FTQ_MB_FREE_CTL
mdefine_line|#define FTQ_MB_FREE_CTL&t;&t;&t;0x00005cc0
DECL|macro|FTQ_MB_FREE_FULL_CNT
mdefine_line|#define FTQ_MB_FREE_FULL_CNT&t;&t;0x00005cc4
DECL|macro|FTQ_MB_FREE_FIFO_ENQDEQ
mdefine_line|#define FTQ_MB_FREE_FIFO_ENQDEQ&t;&t;0x00005cc8
DECL|macro|FTQ_MB_FREE_WRITE_PEEK
mdefine_line|#define FTQ_MB_FREE_WRITE_PEEK&t;&t;0x00005ccc
DECL|macro|FTQ_RCVBD_COMP_CTL
mdefine_line|#define FTQ_RCVBD_COMP_CTL&t;&t;0x00005cd0
DECL|macro|FTQ_RCVBD_COMP_FULL_CNT
mdefine_line|#define FTQ_RCVBD_COMP_FULL_CNT&t;&t;0x00005cd4
DECL|macro|FTQ_RCVBD_COMP_FIFO_ENQDEQ
mdefine_line|#define FTQ_RCVBD_COMP_FIFO_ENQDEQ&t;0x00005cd8
DECL|macro|FTQ_RCVBD_COMP_WRITE_PEEK
mdefine_line|#define FTQ_RCVBD_COMP_WRITE_PEEK&t;0x00005cdc
DECL|macro|FTQ_RCVLST_PLMT_CTL
mdefine_line|#define FTQ_RCVLST_PLMT_CTL&t;&t;0x00005ce0
DECL|macro|FTQ_RCVLST_PLMT_FULL_CNT
mdefine_line|#define FTQ_RCVLST_PLMT_FULL_CNT&t;0x00005ce4
DECL|macro|FTQ_RCVLST_PLMT_FIFO_ENQDEQ
mdefine_line|#define FTQ_RCVLST_PLMT_FIFO_ENQDEQ&t;0x00005ce8
DECL|macro|FTQ_RCVLST_PLMT_WRITE_PEEK
mdefine_line|#define FTQ_RCVLST_PLMT_WRITE_PEEK&t;0x00005cec
DECL|macro|FTQ_RCVDATA_INI_CTL
mdefine_line|#define FTQ_RCVDATA_INI_CTL&t;&t;0x00005cf0
DECL|macro|FTQ_RCVDATA_INI_FULL_CNT
mdefine_line|#define FTQ_RCVDATA_INI_FULL_CNT&t;0x00005cf4
DECL|macro|FTQ_RCVDATA_INI_FIFO_ENQDEQ
mdefine_line|#define FTQ_RCVDATA_INI_FIFO_ENQDEQ&t;0x00005cf8
DECL|macro|FTQ_RCVDATA_INI_WRITE_PEEK
mdefine_line|#define FTQ_RCVDATA_INI_WRITE_PEEK&t;0x00005cfc
DECL|macro|FTQ_RCVDATA_COMP_CTL
mdefine_line|#define FTQ_RCVDATA_COMP_CTL&t;&t;0x00005d00
DECL|macro|FTQ_RCVDATA_COMP_FULL_CNT
mdefine_line|#define FTQ_RCVDATA_COMP_FULL_CNT&t;0x00005d04
DECL|macro|FTQ_RCVDATA_COMP_FIFO_ENQDEQ
mdefine_line|#define FTQ_RCVDATA_COMP_FIFO_ENQDEQ&t;0x00005d08
DECL|macro|FTQ_RCVDATA_COMP_WRITE_PEEK
mdefine_line|#define FTQ_RCVDATA_COMP_WRITE_PEEK&t;0x00005d0c
DECL|macro|FTQ_SWTYPE2_CTL
mdefine_line|#define FTQ_SWTYPE2_CTL&t;&t;&t;0x00005d10
DECL|macro|FTQ_SWTYPE2_FULL_CNT
mdefine_line|#define FTQ_SWTYPE2_FULL_CNT&t;&t;0x00005d14
DECL|macro|FTQ_SWTYPE2_FIFO_ENQDEQ
mdefine_line|#define FTQ_SWTYPE2_FIFO_ENQDEQ&t;&t;0x00005d18
DECL|macro|FTQ_SWTYPE2_WRITE_PEEK
mdefine_line|#define FTQ_SWTYPE2_WRITE_PEEK&t;&t;0x00005d1c
multiline_comment|/* 0x5d20 --&gt; 0x6000 unused */
multiline_comment|/* Message signaled interrupt registers */
DECL|macro|MSGINT_MODE
mdefine_line|#define MSGINT_MODE&t;&t;&t;0x00006000
DECL|macro|MSGINT_MODE_RESET
mdefine_line|#define  MSGINT_MODE_RESET&t;&t; 0x00000001
DECL|macro|MSGINT_MODE_ENABLE
mdefine_line|#define  MSGINT_MODE_ENABLE&t;&t; 0x00000002
DECL|macro|MSGINT_STATUS
mdefine_line|#define MSGINT_STATUS&t;&t;&t;0x00006004
DECL|macro|MSGINT_FIFO
mdefine_line|#define MSGINT_FIFO&t;&t;&t;0x00006008
multiline_comment|/* 0x600c --&gt; 0x6400 unused */
multiline_comment|/* DMA completion registers */
DECL|macro|DMAC_MODE
mdefine_line|#define DMAC_MODE&t;&t;&t;0x00006400
DECL|macro|DMAC_MODE_RESET
mdefine_line|#define  DMAC_MODE_RESET&t;&t; 0x00000001
DECL|macro|DMAC_MODE_ENABLE
mdefine_line|#define  DMAC_MODE_ENABLE&t;&t; 0x00000002
multiline_comment|/* 0x6404 --&gt; 0x6800 unused */
multiline_comment|/* GRC registers */
DECL|macro|GRC_MODE
mdefine_line|#define GRC_MODE&t;&t;&t;0x00006800
DECL|macro|GRC_MODE_UPD_ON_COAL
mdefine_line|#define  GRC_MODE_UPD_ON_COAL&t;&t;0x00000001
DECL|macro|GRC_MODE_BSWAP_NONFRM_DATA
mdefine_line|#define  GRC_MODE_BSWAP_NONFRM_DATA&t;0x00000002
DECL|macro|GRC_MODE_WSWAP_NONFRM_DATA
mdefine_line|#define  GRC_MODE_WSWAP_NONFRM_DATA&t;0x00000004
DECL|macro|GRC_MODE_BSWAP_DATA
mdefine_line|#define  GRC_MODE_BSWAP_DATA&t;&t;0x00000010
DECL|macro|GRC_MODE_WSWAP_DATA
mdefine_line|#define  GRC_MODE_WSWAP_DATA&t;&t;0x00000020
DECL|macro|GRC_MODE_SPLITHDR
mdefine_line|#define  GRC_MODE_SPLITHDR&t;&t;0x00000100
DECL|macro|GRC_MODE_NOFRM_CRACKING
mdefine_line|#define  GRC_MODE_NOFRM_CRACKING&t;0x00000200
DECL|macro|GRC_MODE_INCL_CRC
mdefine_line|#define  GRC_MODE_INCL_CRC&t;&t;0x00000400
DECL|macro|GRC_MODE_ALLOW_BAD_FRMS
mdefine_line|#define  GRC_MODE_ALLOW_BAD_FRMS&t;0x00000800
DECL|macro|GRC_MODE_NOIRQ_ON_SENDS
mdefine_line|#define  GRC_MODE_NOIRQ_ON_SENDS&t;0x00002000
DECL|macro|GRC_MODE_NOIRQ_ON_RCV
mdefine_line|#define  GRC_MODE_NOIRQ_ON_RCV&t;&t;0x00004000
DECL|macro|GRC_MODE_FORCE_PCI32BIT
mdefine_line|#define  GRC_MODE_FORCE_PCI32BIT&t;0x00008000
DECL|macro|GRC_MODE_HOST_STACKUP
mdefine_line|#define  GRC_MODE_HOST_STACKUP&t;&t;0x00010000
DECL|macro|GRC_MODE_HOST_SENDBDS
mdefine_line|#define  GRC_MODE_HOST_SENDBDS&t;&t;0x00020000
DECL|macro|GRC_MODE_NO_TX_PHDR_CSUM
mdefine_line|#define  GRC_MODE_NO_TX_PHDR_CSUM&t;0x00100000
DECL|macro|GRC_MODE_NO_RX_PHDR_CSUM
mdefine_line|#define  GRC_MODE_NO_RX_PHDR_CSUM&t;0x00800000
DECL|macro|GRC_MODE_IRQ_ON_TX_CPU_ATTN
mdefine_line|#define  GRC_MODE_IRQ_ON_TX_CPU_ATTN&t;0x01000000
DECL|macro|GRC_MODE_IRQ_ON_RX_CPU_ATTN
mdefine_line|#define  GRC_MODE_IRQ_ON_RX_CPU_ATTN&t;0x02000000
DECL|macro|GRC_MODE_IRQ_ON_MAC_ATTN
mdefine_line|#define  GRC_MODE_IRQ_ON_MAC_ATTN&t;0x04000000
DECL|macro|GRC_MODE_IRQ_ON_DMA_ATTN
mdefine_line|#define  GRC_MODE_IRQ_ON_DMA_ATTN&t;0x08000000
DECL|macro|GRC_MODE_IRQ_ON_FLOW_ATTN
mdefine_line|#define  GRC_MODE_IRQ_ON_FLOW_ATTN&t;0x10000000
DECL|macro|GRC_MODE_4X_NIC_SEND_RINGS
mdefine_line|#define  GRC_MODE_4X_NIC_SEND_RINGS&t;0x20000000
DECL|macro|GRC_MODE_MCAST_FRM_ENABLE
mdefine_line|#define  GRC_MODE_MCAST_FRM_ENABLE&t;0x40000000
DECL|macro|GRC_MISC_CFG
mdefine_line|#define GRC_MISC_CFG&t;&t;&t;0x00006804
DECL|macro|GRC_MISC_CFG_CORECLK_RESET
mdefine_line|#define  GRC_MISC_CFG_CORECLK_RESET&t;0x00000001
DECL|macro|GRC_MISC_CFG_PRESCALAR_MASK
mdefine_line|#define  GRC_MISC_CFG_PRESCALAR_MASK&t;0x000000fe
DECL|macro|GRC_MISC_CFG_PRESCALAR_SHIFT
mdefine_line|#define  GRC_MISC_CFG_PRESCALAR_SHIFT&t;1
DECL|macro|GRC_MISC_CFG_BOARD_ID_MASK
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_MASK&t;0x0001e000
DECL|macro|GRC_MISC_CFG_BOARD_ID_5700
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_5700&t;0x0001e000
DECL|macro|GRC_MISC_CFG_BOARD_ID_5701
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_5701&t;0x00000000
DECL|macro|GRC_MISC_CFG_BOARD_ID_5702FE
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_5702FE&t;0x00004000
DECL|macro|GRC_MISC_CFG_BOARD_ID_5703
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_5703&t;0x00000000
DECL|macro|GRC_MISC_CFG_BOARD_ID_5703S
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_5703S&t;0x00002000
DECL|macro|GRC_MISC_CFG_BOARD_ID_AC91002A1
mdefine_line|#define  GRC_MISC_CFG_BOARD_ID_AC91002A1 0x00018000
DECL|macro|GRC_LOCAL_CTRL
mdefine_line|#define GRC_LOCAL_CTRL&t;&t;&t;0x00006808
DECL|macro|GRC_LCLCTRL_INT_ACTIVE
mdefine_line|#define  GRC_LCLCTRL_INT_ACTIVE&t;&t;0x00000001
DECL|macro|GRC_LCLCTRL_CLEARINT
mdefine_line|#define  GRC_LCLCTRL_CLEARINT&t;&t;0x00000002
DECL|macro|GRC_LCLCTRL_SETINT
mdefine_line|#define  GRC_LCLCTRL_SETINT&t;&t;0x00000004
DECL|macro|GRC_LCLCTRL_INT_ON_ATTN
mdefine_line|#define  GRC_LCLCTRL_INT_ON_ATTN&t;0x00000008
DECL|macro|GRC_LCLCTRL_GPIO_INPUT0
mdefine_line|#define  GRC_LCLCTRL_GPIO_INPUT0&t;0x00000100
DECL|macro|GRC_LCLCTRL_GPIO_INPUT1
mdefine_line|#define  GRC_LCLCTRL_GPIO_INPUT1&t;0x00000200
DECL|macro|GRC_LCLCTRL_GPIO_INPUT2
mdefine_line|#define  GRC_LCLCTRL_GPIO_INPUT2&t;0x00000400
DECL|macro|GRC_LCLCTRL_GPIO_OE0
mdefine_line|#define  GRC_LCLCTRL_GPIO_OE0&t;&t;0x00000800
DECL|macro|GRC_LCLCTRL_GPIO_OE1
mdefine_line|#define  GRC_LCLCTRL_GPIO_OE1&t;&t;0x00001000
DECL|macro|GRC_LCLCTRL_GPIO_OE2
mdefine_line|#define  GRC_LCLCTRL_GPIO_OE2&t;&t;0x00002000
DECL|macro|GRC_LCLCTRL_GPIO_OUTPUT0
mdefine_line|#define  GRC_LCLCTRL_GPIO_OUTPUT0&t;0x00004000
DECL|macro|GRC_LCLCTRL_GPIO_OUTPUT1
mdefine_line|#define  GRC_LCLCTRL_GPIO_OUTPUT1&t;0x00008000
DECL|macro|GRC_LCLCTRL_GPIO_OUTPUT2
mdefine_line|#define  GRC_LCLCTRL_GPIO_OUTPUT2&t;0x00010000
DECL|macro|GRC_LCLCTRL_EXTMEM_ENABLE
mdefine_line|#define  GRC_LCLCTRL_EXTMEM_ENABLE&t;0x00020000
DECL|macro|GRC_LCLCTRL_MEMSZ_MASK
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_MASK&t;&t;0x001c0000
DECL|macro|GRC_LCLCTRL_MEMSZ_256K
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_256K&t;&t;0x00000000
DECL|macro|GRC_LCLCTRL_MEMSZ_512K
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_512K&t;&t;0x00040000
DECL|macro|GRC_LCLCTRL_MEMSZ_1M
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_1M&t;&t;0x00080000
DECL|macro|GRC_LCLCTRL_MEMSZ_2M
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_2M&t;&t;0x000c0000
DECL|macro|GRC_LCLCTRL_MEMSZ_4M
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_4M&t;&t;0x00100000
DECL|macro|GRC_LCLCTRL_MEMSZ_8M
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_8M&t;&t;0x00140000
DECL|macro|GRC_LCLCTRL_MEMSZ_16M
mdefine_line|#define  GRC_LCLCTRL_MEMSZ_16M&t;&t;0x00180000
DECL|macro|GRC_LCLCTRL_BANK_SELECT
mdefine_line|#define  GRC_LCLCTRL_BANK_SELECT&t;0x00200000
DECL|macro|GRC_LCLCTRL_SSRAM_TYPE
mdefine_line|#define  GRC_LCLCTRL_SSRAM_TYPE&t;&t;0x00400000
DECL|macro|GRC_LCLCTRL_AUTO_SEEPROM
mdefine_line|#define  GRC_LCLCTRL_AUTO_SEEPROM&t;0x01000000
DECL|macro|GRC_TIMER
mdefine_line|#define GRC_TIMER&t;&t;&t;0x0000680c
DECL|macro|GRC_RX_CPU_EVENT
mdefine_line|#define GRC_RX_CPU_EVENT&t;&t;0x00006810
DECL|macro|GRC_RX_TIMER_REF
mdefine_line|#define GRC_RX_TIMER_REF&t;&t;0x00006814
DECL|macro|GRC_RX_CPU_SEM
mdefine_line|#define GRC_RX_CPU_SEM&t;&t;&t;0x00006818
DECL|macro|GRC_REMOTE_RX_CPU_ATTN
mdefine_line|#define GRC_REMOTE_RX_CPU_ATTN&t;&t;0x0000681c
DECL|macro|GRC_TX_CPU_EVENT
mdefine_line|#define GRC_TX_CPU_EVENT&t;&t;0x00006820
DECL|macro|GRC_TX_TIMER_REF
mdefine_line|#define GRC_TX_TIMER_REF&t;&t;0x00006824
DECL|macro|GRC_TX_CPU_SEM
mdefine_line|#define GRC_TX_CPU_SEM&t;&t;&t;0x00006828
DECL|macro|GRC_REMOTE_TX_CPU_ATTN
mdefine_line|#define GRC_REMOTE_TX_CPU_ATTN&t;&t;0x0000682c
DECL|macro|GRC_MEM_POWER_UP
mdefine_line|#define GRC_MEM_POWER_UP&t;&t;0x00006830 /* 64-bit */
DECL|macro|GRC_EEPROM_ADDR
mdefine_line|#define GRC_EEPROM_ADDR&t;&t;&t;0x00006838
DECL|macro|EEPROM_ADDR_WRITE
mdefine_line|#define  EEPROM_ADDR_WRITE&t;&t;0x00000000
DECL|macro|EEPROM_ADDR_READ
mdefine_line|#define  EEPROM_ADDR_READ&t;&t;0x80000000
DECL|macro|EEPROM_ADDR_COMPLETE
mdefine_line|#define  EEPROM_ADDR_COMPLETE&t;&t;0x40000000
DECL|macro|EEPROM_ADDR_FSM_RESET
mdefine_line|#define  EEPROM_ADDR_FSM_RESET&t;&t;0x20000000
DECL|macro|EEPROM_ADDR_DEVID_MASK
mdefine_line|#define  EEPROM_ADDR_DEVID_MASK&t;&t;0x1c000000
DECL|macro|EEPROM_ADDR_DEVID_SHIFT
mdefine_line|#define  EEPROM_ADDR_DEVID_SHIFT&t;26
DECL|macro|EEPROM_ADDR_START
mdefine_line|#define  EEPROM_ADDR_START&t;&t;0x02000000
DECL|macro|EEPROM_ADDR_CLKPERD_SHIFT
mdefine_line|#define  EEPROM_ADDR_CLKPERD_SHIFT&t;16
DECL|macro|EEPROM_ADDR_ADDR_MASK
mdefine_line|#define  EEPROM_ADDR_ADDR_MASK&t;&t;0x0000ffff
DECL|macro|EEPROM_ADDR_ADDR_SHIFT
mdefine_line|#define  EEPROM_ADDR_ADDR_SHIFT&t;&t;0
DECL|macro|EEPROM_DEFAULT_CLOCK_PERIOD
mdefine_line|#define  EEPROM_DEFAULT_CLOCK_PERIOD&t;0x60
DECL|macro|EEPROM_CHIP_SIZE
mdefine_line|#define  EEPROM_CHIP_SIZE&t;&t;(64 * 1024)
DECL|macro|GRC_EEPROM_DATA
mdefine_line|#define GRC_EEPROM_DATA&t;&t;&t;0x0000683c
DECL|macro|GRC_EEPROM_CTRL
mdefine_line|#define GRC_EEPROM_CTRL&t;&t;&t;0x00006840
DECL|macro|GRC_MDI_CTRL
mdefine_line|#define GRC_MDI_CTRL&t;&t;&t;0x00006844
DECL|macro|GRC_SEEPROM_DELAY
mdefine_line|#define GRC_SEEPROM_DELAY&t;&t;0x00006848
multiline_comment|/* 0x684c --&gt; 0x6c00 unused */
multiline_comment|/* 0x6c00 --&gt; 0x7000 unused */
multiline_comment|/* NVRAM Control registers */
DECL|macro|NVRAM_CMD
mdefine_line|#define NVRAM_CMD&t;&t;&t;0x00007000
DECL|macro|NVRAM_CMD_RESET
mdefine_line|#define  NVRAM_CMD_RESET&t;&t; 0x00000001
DECL|macro|NVRAM_CMD_DONE
mdefine_line|#define  NVRAM_CMD_DONE&t;&t;&t; 0x00000008
DECL|macro|NVRAM_CMD_GO
mdefine_line|#define  NVRAM_CMD_GO&t;&t;&t; 0x00000010
DECL|macro|NVRAM_CMD_WR
mdefine_line|#define  NVRAM_CMD_WR&t;&t;&t; 0x00000020
DECL|macro|NVRAM_CMD_RD
mdefine_line|#define  NVRAM_CMD_RD&t;&t;&t; 0x00000000
DECL|macro|NVRAM_CMD_ERASE
mdefine_line|#define  NVRAM_CMD_ERASE&t;&t; 0x00000040
DECL|macro|NVRAM_CMD_FIRST
mdefine_line|#define  NVRAM_CMD_FIRST&t;&t; 0x00000080
DECL|macro|NVRAM_CMD_LAST
mdefine_line|#define  NVRAM_CMD_LAST&t;&t;&t; 0x00000100
DECL|macro|NVRAM_STAT
mdefine_line|#define NVRAM_STAT&t;&t;&t;0x00007004
DECL|macro|NVRAM_WRDATA
mdefine_line|#define NVRAM_WRDATA&t;&t;&t;0x00007008
DECL|macro|NVRAM_ADDR
mdefine_line|#define NVRAM_ADDR&t;&t;&t;0x0000700c
DECL|macro|NVRAM_ADDR_MSK
mdefine_line|#define  NVRAM_ADDR_MSK&t;&t;&t;0x00ffffff
DECL|macro|NVRAM_RDDATA
mdefine_line|#define NVRAM_RDDATA&t;&t;&t;0x00007010
DECL|macro|NVRAM_CFG1
mdefine_line|#define NVRAM_CFG1&t;&t;&t;0x00007014
DECL|macro|NVRAM_CFG1_FLASHIF_ENAB
mdefine_line|#define  NVRAM_CFG1_FLASHIF_ENAB&t; 0x00000001
DECL|macro|NVRAM_CFG1_BUFFERED_MODE
mdefine_line|#define  NVRAM_CFG1_BUFFERED_MODE&t; 0x00000002
DECL|macro|NVRAM_CFG1_PASS_THRU
mdefine_line|#define  NVRAM_CFG1_PASS_THRU&t;&t; 0x00000004
DECL|macro|NVRAM_CFG1_BIT_BANG
mdefine_line|#define  NVRAM_CFG1_BIT_BANG&t;&t; 0x00000008
DECL|macro|NVRAM_CFG1_COMPAT_BYPASS
mdefine_line|#define  NVRAM_CFG1_COMPAT_BYPASS&t; 0x80000000
DECL|macro|NVRAM_CFG2
mdefine_line|#define NVRAM_CFG2&t;&t;&t;0x00007018
DECL|macro|NVRAM_CFG3
mdefine_line|#define NVRAM_CFG3&t;&t;&t;0x0000701c
DECL|macro|NVRAM_SWARB
mdefine_line|#define NVRAM_SWARB&t;&t;&t;0x00007020
DECL|macro|SWARB_REQ_SET0
mdefine_line|#define  SWARB_REQ_SET0&t;&t;&t; 0x00000001
DECL|macro|SWARB_REQ_SET1
mdefine_line|#define  SWARB_REQ_SET1&t;&t;&t; 0x00000002
DECL|macro|SWARB_REQ_SET2
mdefine_line|#define  SWARB_REQ_SET2&t;&t;&t; 0x00000004
DECL|macro|SWARB_REQ_SET3
mdefine_line|#define  SWARB_REQ_SET3&t;&t;&t; 0x00000008
DECL|macro|SWARB_REQ_CLR0
mdefine_line|#define  SWARB_REQ_CLR0&t;&t;&t; 0x00000010
DECL|macro|SWARB_REQ_CLR1
mdefine_line|#define  SWARB_REQ_CLR1&t;&t;&t; 0x00000020
DECL|macro|SWARB_REQ_CLR2
mdefine_line|#define  SWARB_REQ_CLR2&t;&t;&t; 0x00000040
DECL|macro|SWARB_REQ_CLR3
mdefine_line|#define  SWARB_REQ_CLR3&t;&t;&t; 0x00000080
DECL|macro|SWARB_GNT0
mdefine_line|#define  SWARB_GNT0&t;&t;&t; 0x00000100
DECL|macro|SWARB_GNT1
mdefine_line|#define  SWARB_GNT1&t;&t;&t; 0x00000200
DECL|macro|SWARB_GNT2
mdefine_line|#define  SWARB_GNT2&t;&t;&t; 0x00000400
DECL|macro|SWARB_GNT3
mdefine_line|#define  SWARB_GNT3&t;&t;&t; 0x00000800
DECL|macro|SWARB_REQ0
mdefine_line|#define  SWARB_REQ0&t;&t;&t; 0x00001000
DECL|macro|SWARB_REQ1
mdefine_line|#define  SWARB_REQ1&t;&t;&t; 0x00002000
DECL|macro|SWARB_REQ2
mdefine_line|#define  SWARB_REQ2&t;&t;&t; 0x00004000
DECL|macro|SWARB_REQ3
mdefine_line|#define  SWARB_REQ3&t;&t;&t; 0x00008000
DECL|macro|NVRAM_BUFFERED_PAGE_SIZE
mdefine_line|#define    NVRAM_BUFFERED_PAGE_SIZE&t;   264
DECL|macro|NVRAM_BUFFERED_PAGE_POS
mdefine_line|#define    NVRAM_BUFFERED_PAGE_POS&t;   9
multiline_comment|/* 0x7024 --&gt; 0x7400 unused */
multiline_comment|/* 0x7400 --&gt; 0x8000 unused */
multiline_comment|/* 32K Window into NIC internal memory */
DECL|macro|NIC_SRAM_WIN_BASE
mdefine_line|#define NIC_SRAM_WIN_BASE&t;&t;0x00008000
multiline_comment|/* Offsets into first 32k of NIC internal memory. */
DECL|macro|NIC_SRAM_PAGE_ZERO
mdefine_line|#define NIC_SRAM_PAGE_ZERO&t;&t;0x00000000
DECL|macro|NIC_SRAM_SEND_RCB
mdefine_line|#define NIC_SRAM_SEND_RCB&t;&t;0x00000100 /* 16 * TG3_BDINFO_... */
DECL|macro|NIC_SRAM_RCV_RET_RCB
mdefine_line|#define NIC_SRAM_RCV_RET_RCB&t;&t;0x00000200 /* 16 * TG3_BDINFO_... */
DECL|macro|NIC_SRAM_STATS_BLK
mdefine_line|#define NIC_SRAM_STATS_BLK&t;&t;0x00000300
DECL|macro|NIC_SRAM_STATUS_BLK
mdefine_line|#define NIC_SRAM_STATUS_BLK&t;&t;0x00000b00
DECL|macro|NIC_SRAM_FIRMWARE_MBOX
mdefine_line|#define NIC_SRAM_FIRMWARE_MBOX&t;&t;0x00000b50
DECL|macro|NIC_SRAM_FIRMWARE_MBOX_MAGIC1
mdefine_line|#define  NIC_SRAM_FIRMWARE_MBOX_MAGIC1&t; 0x4B657654
DECL|macro|NIC_SRAM_FIRMWARE_MBOX_MAGIC2
mdefine_line|#define  NIC_SRAM_FIRMWARE_MBOX_MAGIC2&t; 0x4861764b /* !dma on linkchg */
DECL|macro|NIC_SRAM_DATA_SIG
mdefine_line|#define NIC_SRAM_DATA_SIG&t;&t;0x00000b54
DECL|macro|NIC_SRAM_DATA_SIG_MAGIC
mdefine_line|#define  NIC_SRAM_DATA_SIG_MAGIC&t; 0x4b657654 /* ascii for &squot;KevT&squot; */
DECL|macro|NIC_SRAM_DATA_CFG
mdefine_line|#define NIC_SRAM_DATA_CFG&t;&t;&t;0x00000b58
DECL|macro|NIC_SRAM_DATA_CFG_PHY_TYPE_MASK
mdefine_line|#define  NIC_SRAM_DATA_CFG_PHY_TYPE_MASK&t; 0x0000000c
DECL|macro|NIC_SRAM_DATA_CFG_PHY_TYPE_UNKNOWN
mdefine_line|#define  NIC_SRAM_DATA_CFG_PHY_TYPE_UNKNOWN&t; 0x00000000
DECL|macro|NIC_SRAM_DATA_CFG_PHY_TYPE_COPPER
mdefine_line|#define  NIC_SRAM_DATA_CFG_PHY_TYPE_COPPER&t; 0x00000004
DECL|macro|NIC_SRAM_DATA_CFG_PHY_TYPE_FIBER
mdefine_line|#define  NIC_SRAM_DATA_CFG_PHY_TYPE_FIBER&t; 0x00000008
DECL|macro|NIC_SRAM_DATA_CFG_LED_MODE_MASK
mdefine_line|#define  NIC_SRAM_DATA_CFG_LED_MODE_MASK&t; 0x00000030
DECL|macro|NIC_SRAM_DATA_CFG_LED_MODE_UNKNOWN
mdefine_line|#define  NIC_SRAM_DATA_CFG_LED_MODE_UNKNOWN&t; 0x00000000
DECL|macro|NIC_SRAM_DATA_CFG_LED_TRIPLE_SPD
mdefine_line|#define  NIC_SRAM_DATA_CFG_LED_TRIPLE_SPD&t; 0x00000010
DECL|macro|NIC_SRAM_DATA_CFG_LED_LINK_SPD
mdefine_line|#define  NIC_SRAM_DATA_CFG_LED_LINK_SPD&t;&t; 0x00000020
DECL|macro|NIC_SRAM_DATA_PHY_ID
mdefine_line|#define NIC_SRAM_DATA_PHY_ID&t;&t;0x00000b74
DECL|macro|NIC_SRAM_DATA_PHY_ID1_MASK
mdefine_line|#define  NIC_SRAM_DATA_PHY_ID1_MASK&t; 0xffff0000
DECL|macro|NIC_SRAM_DATA_PHY_ID2_MASK
mdefine_line|#define  NIC_SRAM_DATA_PHY_ID2_MASK&t; 0x0000ffff
DECL|macro|NIC_SRAM_FW_CMD_MBOX
mdefine_line|#define NIC_SRAM_FW_CMD_MBOX&t;&t;0x00000b78
DECL|macro|FWCMD_NICDRV_ALIVE
mdefine_line|#define  FWCMD_NICDRV_ALIVE&t;&t; 0x00000001
DECL|macro|FWCMD_NICDRV_PAUSE_FW
mdefine_line|#define  FWCMD_NICDRV_PAUSE_FW&t;&t; 0x00000002
DECL|macro|FWCMD_NICDRV_IPV4ADDR_CHG
mdefine_line|#define  FWCMD_NICDRV_IPV4ADDR_CHG&t; 0x00000003
DECL|macro|FWCMD_NICDRV_IPV6ADDR_CHG
mdefine_line|#define  FWCMD_NICDRV_IPV6ADDR_CHG&t; 0x00000004
DECL|macro|FWCMD_NICDRV_FIX_DMAR
mdefine_line|#define  FWCMD_NICDRV_FIX_DMAR&t;&t; 0x00000005
DECL|macro|FWCMD_NICDRV_FIX_DMAW
mdefine_line|#define  FWCMD_NICDRV_FIX_DMAW&t;&t; 0x00000006
DECL|macro|NIC_SRAM_FW_CMD_LEN_MBOX
mdefine_line|#define NIC_SRAM_FW_CMD_LEN_MBOX&t;0x00000b7c
DECL|macro|NIC_SRAM_FW_CMD_DATA_MBOX
mdefine_line|#define NIC_SRAM_FW_CMD_DATA_MBOX&t;0x00000b80
DECL|macro|NIC_SRAM_FW_ASF_STATUS_MBOX
mdefine_line|#define NIC_SRAM_FW_ASF_STATUS_MBOX&t;0x00000c00
DECL|macro|NIC_SRAM_FW_DRV_STATE_MBOX
mdefine_line|#define NIC_SRAM_FW_DRV_STATE_MBOX&t;0x00000c04
DECL|macro|DRV_STATE_START
mdefine_line|#define  DRV_STATE_START&t;&t; 0x00000001
DECL|macro|DRV_STATE_UNLOAD
mdefine_line|#define  DRV_STATE_UNLOAD&t;&t; 0x00000002
DECL|macro|DRV_STATE_WOL
mdefine_line|#define  DRV_STATE_WOL&t;&t;&t; 0x00000003
DECL|macro|DRV_STATE_SUSPEND
mdefine_line|#define  DRV_STATE_SUSPEND&t;&t; 0x00000004
DECL|macro|NIC_SRAM_FW_RESET_TYPE_MBOX
mdefine_line|#define NIC_SRAM_FW_RESET_TYPE_MBOX&t;0x00000c08
DECL|macro|NIC_SRAM_MAC_ADDR_HIGH_MBOX
mdefine_line|#define NIC_SRAM_MAC_ADDR_HIGH_MBOX&t;0x00000c14
DECL|macro|NIC_SRAM_MAC_ADDR_LOW_MBOX
mdefine_line|#define NIC_SRAM_MAC_ADDR_LOW_MBOX&t;0x00000c18
macro_line|#if TG3_MINI_RING_WORKS
DECL|macro|NIC_SRAM_RX_MINI_BUFFER_DESC
mdefine_line|#define NIC_SRAM_RX_MINI_BUFFER_DESC&t;0x00001000
macro_line|#endif
DECL|macro|NIC_SRAM_DMA_DESC_POOL_BASE
mdefine_line|#define NIC_SRAM_DMA_DESC_POOL_BASE&t;0x00002000
DECL|macro|NIC_SRAM_DMA_DESC_POOL_SIZE
mdefine_line|#define  NIC_SRAM_DMA_DESC_POOL_SIZE&t; 0x00002000
DECL|macro|NIC_SRAM_TX_BUFFER_DESC
mdefine_line|#define NIC_SRAM_TX_BUFFER_DESC&t;&t;0x00004000 /* 512 entries */
DECL|macro|NIC_SRAM_RX_BUFFER_DESC
mdefine_line|#define NIC_SRAM_RX_BUFFER_DESC&t;&t;0x00006000 /* 256 entries */
DECL|macro|NIC_SRAM_RX_JUMBO_BUFFER_DESC
mdefine_line|#define NIC_SRAM_RX_JUMBO_BUFFER_DESC&t;0x00007000 /* 256 entries */
DECL|macro|NIC_SRAM_MBUF_POOL_BASE
mdefine_line|#define NIC_SRAM_MBUF_POOL_BASE&t;&t;0x00008000
DECL|macro|NIC_SRAM_MBUF_POOL_SIZE
mdefine_line|#define  NIC_SRAM_MBUF_POOL_SIZE&t; 0x00018000
multiline_comment|/* Currently this is fixed. */
DECL|macro|PHY_ADDR
mdefine_line|#define PHY_ADDR&t;&t;0x01
multiline_comment|/* Tigon3 specific PHY MII registers. */
DECL|macro|TG3_BMCR_SPEED1000
mdefine_line|#define  TG3_BMCR_SPEED1000&t;&t;0x0040
DECL|macro|MII_TG3_CTRL
mdefine_line|#define MII_TG3_CTRL&t;&t;&t;0x09 /* 1000-baseT control register */
DECL|macro|MII_TG3_CTRL_ADV_1000_HALF
mdefine_line|#define  MII_TG3_CTRL_ADV_1000_HALF&t;0x0100
DECL|macro|MII_TG3_CTRL_ADV_1000_FULL
mdefine_line|#define  MII_TG3_CTRL_ADV_1000_FULL&t;0x0200
DECL|macro|MII_TG3_CTRL_AS_MASTER
mdefine_line|#define  MII_TG3_CTRL_AS_MASTER&t;&t;0x0800
DECL|macro|MII_TG3_CTRL_ENABLE_AS_MASTER
mdefine_line|#define  MII_TG3_CTRL_ENABLE_AS_MASTER&t;0x1000
DECL|macro|MII_TG3_EXT_CTRL
mdefine_line|#define MII_TG3_EXT_CTRL&t;&t;0x10 /* Extended control register */
DECL|macro|MII_TG3_EXT_CTRL_LNK3_LED_MODE
mdefine_line|#define  MII_TG3_EXT_CTRL_LNK3_LED_MODE&t;0x0002
DECL|macro|MII_TG3_EXT_CTRL_TBI
mdefine_line|#define  MII_TG3_EXT_CTRL_TBI&t;&t;0x8000
DECL|macro|MII_TG3_EXT_STAT
mdefine_line|#define MII_TG3_EXT_STAT&t;&t;0x11 /* Extended status register */
DECL|macro|MII_TG3_EXT_STAT_LPASS
mdefine_line|#define  MII_TG3_EXT_STAT_LPASS&t;&t;0x0100
DECL|macro|MII_TG3_DSP_RW_PORT
mdefine_line|#define MII_TG3_DSP_RW_PORT&t;&t;0x15 /* DSP coefficient read/write port */
DECL|macro|MII_TG3_DSP_ADDRESS
mdefine_line|#define MII_TG3_DSP_ADDRESS&t;&t;0x17 /* DSP address register */
DECL|macro|MII_TG3_AUX_CTRL
mdefine_line|#define MII_TG3_AUX_CTRL&t;&t;0x18 /* auxilliary control register */
DECL|macro|MII_TG3_AUX_STAT
mdefine_line|#define MII_TG3_AUX_STAT&t;&t;0x19 /* auxilliary status register */
DECL|macro|MII_TG3_AUX_STAT_LPASS
mdefine_line|#define MII_TG3_AUX_STAT_LPASS&t;&t;0x0004
DECL|macro|MII_TG3_AUX_STAT_SPDMASK
mdefine_line|#define MII_TG3_AUX_STAT_SPDMASK&t;0x0700
DECL|macro|MII_TG3_AUX_STAT_10HALF
mdefine_line|#define MII_TG3_AUX_STAT_10HALF&t;&t;0x0100
DECL|macro|MII_TG3_AUX_STAT_10FULL
mdefine_line|#define MII_TG3_AUX_STAT_10FULL&t;&t;0x0200
DECL|macro|MII_TG3_AUX_STAT_100HALF
mdefine_line|#define MII_TG3_AUX_STAT_100HALF&t;0x0300
DECL|macro|MII_TG3_AUX_STAT_100_4
mdefine_line|#define MII_TG3_AUX_STAT_100_4&t;&t;0x0400
DECL|macro|MII_TG3_AUX_STAT_100FULL
mdefine_line|#define MII_TG3_AUX_STAT_100FULL&t;0x0500
DECL|macro|MII_TG3_AUX_STAT_1000HALF
mdefine_line|#define MII_TG3_AUX_STAT_1000HALF&t;0x0600
DECL|macro|MII_TG3_AUX_STAT_1000FULL
mdefine_line|#define MII_TG3_AUX_STAT_1000FULL&t;0x0700
DECL|macro|MII_TG3_ISTAT
mdefine_line|#define MII_TG3_ISTAT&t;&t;&t;0x1a /* IRQ status register */
DECL|macro|MII_TG3_IMASK
mdefine_line|#define MII_TG3_IMASK&t;&t;&t;0x1b /* IRQ mask register */
multiline_comment|/* ISTAT/IMASK event bits */
DECL|macro|MII_TG3_INT_LINKCHG
mdefine_line|#define MII_TG3_INT_LINKCHG&t;&t;0x0002
DECL|macro|MII_TG3_INT_SPEEDCHG
mdefine_line|#define MII_TG3_INT_SPEEDCHG&t;&t;0x0004
DECL|macro|MII_TG3_INT_DUPLEXCHG
mdefine_line|#define MII_TG3_INT_DUPLEXCHG&t;&t;0x0008
DECL|macro|MII_TG3_INT_ANEG_PAGE_RX
mdefine_line|#define MII_TG3_INT_ANEG_PAGE_RX&t;0x0400
multiline_comment|/* XXX Add this to mii.h */
macro_line|#ifndef ADVERTISE_PAUSE
DECL|macro|ADVERTISE_PAUSE_CAP
mdefine_line|#define ADVERTISE_PAUSE_CAP&t;&t;0x0400
macro_line|#endif
macro_line|#ifndef ADVERTISE_PAUSE_ASYM
DECL|macro|ADVERTISE_PAUSE_ASYM
mdefine_line|#define ADVERTISE_PAUSE_ASYM&t;&t;0x0800
macro_line|#endif
macro_line|#ifndef LPA_PAUSE
DECL|macro|LPA_PAUSE_CAP
mdefine_line|#define LPA_PAUSE_CAP&t;&t;&t;0x0400
macro_line|#endif
macro_line|#ifndef LPA_PAUSE_ASYM
DECL|macro|LPA_PAUSE_ASYM
mdefine_line|#define LPA_PAUSE_ASYM&t;&t;&t;0x0800
macro_line|#endif
multiline_comment|/* There are two ways to manage the TX descriptors on the tigon3.&n; * Either the descriptors are in host DMA&squot;able memory, or they&n; * exist only in the cards on-chip SRAM.  All 16 send bds are under&n; * the same mode, they may not be configured individually.&n; *&n; * The mode we use is controlled by TG3_FLAG_HOST_TXDS in tp-&gt;tg3_flags.&n; *&n; * To use host memory TX descriptors:&n; *&t;1) Set GRC_MODE_HOST_SENDBDS in GRC_MODE register.&n; *&t;   Make sure GRC_MODE_4X_NIC_SEND_RINGS is clear.&n; *&t;2) Allocate DMA&squot;able memory.&n; *&t;3) In NIC_SRAM_SEND_RCB (of desired index) of on-chip SRAM:&n; *&t;   a) Set TG3_BDINFO_HOST_ADDR to DMA address of memory&n; *&t;      obtained in step 2&n; *&t;   b) Set TG3_BDINFO_NIC_ADDR to NIC_SRAM_TX_BUFFER_DESC.&n; *&t;   c) Set len field of TG3_BDINFO_MAXLEN_FLAGS to number&n; *            of TX descriptors.  Leave flags field clear.&n; *&t;4) Access TX descriptors via host memory.  The chip&n; *&t;   will refetch into local SRAM as needed when producer&n; *&t;   index mailboxes are updated.&n; *&n; * To use on-chip TX descriptors:&n; *&t;1) Set GRC_MODE_4X_NIC_SEND_RINGS in GRC_MODE register.&n; *&t;   Make sure GRC_MODE_HOST_SENDBDS is clear.&n; *&t;2) In NIC_SRAM_SEND_RCB (of desired index) of on-chip SRAM:&n; *&t;   a) Set TG3_BDINFO_HOST_ADDR to zero.&n; *&t;   b) Set TG3_BDINFO_NIC_ADDR to NIC_SRAM_TX_BUFFER_DESC&n; *&t;   c) TG3_BDINFO_MAXLEN_FLAGS is don&squot;t care.&n; *&t;3) Access TX descriptors directly in on-chip SRAM&n; *&t;   using normal {read,write}l().  (and not using&n; *         pointer dereferencing of ioremap()&squot;d memory like&n; *&t;   the broken Broadcom driver does)&n; *&n; * Note that BDINFO_FLAGS_DISABLED should be set in the flags field of&n; * TG3_BDINFO_MAXLEN_FLAGS of all unused SEND_RCB indices.&n; */
DECL|struct|tg3_tx_buffer_desc
r_struct
id|tg3_tx_buffer_desc
(brace
DECL|member|addr_hi
id|u32
id|addr_hi
suffix:semicolon
DECL|member|addr_lo
id|u32
id|addr_lo
suffix:semicolon
DECL|member|len_flags
id|u32
id|len_flags
suffix:semicolon
DECL|macro|TXD_FLAG_TCPUDP_CSUM
mdefine_line|#define TXD_FLAG_TCPUDP_CSUM&t;&t;0x0001
DECL|macro|TXD_FLAG_IP_CSUM
mdefine_line|#define TXD_FLAG_IP_CSUM&t;&t;0x0002
DECL|macro|TXD_FLAG_END
mdefine_line|#define TXD_FLAG_END&t;&t;&t;0x0004
DECL|macro|TXD_FLAG_IP_FRAG
mdefine_line|#define TXD_FLAG_IP_FRAG&t;&t;0x0008
DECL|macro|TXD_FLAG_IP_FRAG_END
mdefine_line|#define TXD_FLAG_IP_FRAG_END&t;&t;0x0010
DECL|macro|TXD_FLAG_VLAN
mdefine_line|#define TXD_FLAG_VLAN&t;&t;&t;0x0040
DECL|macro|TXD_FLAG_COAL_NOW
mdefine_line|#define TXD_FLAG_COAL_NOW&t;&t;0x0080
DECL|macro|TXD_FLAG_CPU_PRE_DMA
mdefine_line|#define TXD_FLAG_CPU_PRE_DMA&t;&t;0x0100
DECL|macro|TXD_FLAG_CPU_POST_DMA
mdefine_line|#define TXD_FLAG_CPU_POST_DMA&t;&t;0x0200
DECL|macro|TXD_FLAG_ADD_SRC_ADDR
mdefine_line|#define TXD_FLAG_ADD_SRC_ADDR&t;&t;0x1000
DECL|macro|TXD_FLAG_CHOOSE_SRC_ADDR
mdefine_line|#define TXD_FLAG_CHOOSE_SRC_ADDR&t;0x6000
DECL|macro|TXD_FLAG_NO_CRC
mdefine_line|#define TXD_FLAG_NO_CRC&t;&t;&t;0x8000
DECL|macro|TXD_LEN_SHIFT
mdefine_line|#define TXD_LEN_SHIFT&t;&t;&t;16
DECL|member|vlan_tag
id|u32
id|vlan_tag
suffix:semicolon
DECL|macro|TXD_VLAN_TAG_SHIFT
mdefine_line|#define TXD_VLAN_TAG_SHIFT&t;&t;0
)brace
suffix:semicolon
DECL|macro|TXD_ADDR
mdefine_line|#define TXD_ADDR&t;&t;&t;0x00UL /* 64-bit */
DECL|macro|TXD_LEN_FLAGS
mdefine_line|#define TXD_LEN_FLAGS&t;&t;&t;0x08UL /* 32-bit (upper 16-bits are len) */
DECL|macro|TXD_VLAN_TAG
mdefine_line|#define TXD_VLAN_TAG&t;&t;&t;0x0cUL /* 32-bit (upper 16-bits are tag) */
DECL|macro|TXD_SIZE
mdefine_line|#define TXD_SIZE&t;&t;&t;0x10UL
DECL|struct|tg3_rx_buffer_desc
r_struct
id|tg3_rx_buffer_desc
(brace
DECL|member|addr_hi
id|u32
id|addr_hi
suffix:semicolon
DECL|member|addr_lo
id|u32
id|addr_lo
suffix:semicolon
DECL|member|idx_len
id|u32
id|idx_len
suffix:semicolon
DECL|macro|RXD_IDX_MASK
mdefine_line|#define RXD_IDX_MASK&t;0xffff0000
DECL|macro|RXD_IDX_SHIFT
mdefine_line|#define RXD_IDX_SHIFT&t;16
DECL|macro|RXD_LEN_MASK
mdefine_line|#define RXD_LEN_MASK&t;0x0000ffff
DECL|macro|RXD_LEN_SHIFT
mdefine_line|#define RXD_LEN_SHIFT&t;0
DECL|member|type_flags
id|u32
id|type_flags
suffix:semicolon
DECL|macro|RXD_TYPE_SHIFT
mdefine_line|#define RXD_TYPE_SHIFT&t;16
DECL|macro|RXD_FLAGS_SHIFT
mdefine_line|#define RXD_FLAGS_SHIFT&t;0
DECL|macro|RXD_FLAG_END
mdefine_line|#define RXD_FLAG_END&t;&t;&t;0x0004
macro_line|#if TG3_MINI_RING_WORKS
DECL|macro|RXD_FLAG_MINI
mdefine_line|#define RXD_FLAG_MINI&t;&t;&t;0x0800
macro_line|#endif
DECL|macro|RXD_FLAG_JUMBO
mdefine_line|#define RXD_FLAG_JUMBO&t;&t;&t;0x0020
DECL|macro|RXD_FLAG_VLAN
mdefine_line|#define RXD_FLAG_VLAN&t;&t;&t;0x0040
DECL|macro|RXD_FLAG_ERROR
mdefine_line|#define RXD_FLAG_ERROR&t;&t;&t;0x0400
DECL|macro|RXD_FLAG_IP_CSUM
mdefine_line|#define RXD_FLAG_IP_CSUM&t;&t;0x1000
DECL|macro|RXD_FLAG_TCPUDP_CSUM
mdefine_line|#define RXD_FLAG_TCPUDP_CSUM&t;&t;0x2000
DECL|macro|RXD_FLAG_IS_TCP
mdefine_line|#define RXD_FLAG_IS_TCP&t;&t;&t;0x4000
DECL|member|ip_tcp_csum
id|u32
id|ip_tcp_csum
suffix:semicolon
DECL|macro|RXD_IPCSUM_MASK
mdefine_line|#define RXD_IPCSUM_MASK&t;&t;0xffff0000
DECL|macro|RXD_IPCSUM_SHIFT
mdefine_line|#define RXD_IPCSUM_SHIFT&t;16
DECL|macro|RXD_TCPCSUM_MASK
mdefine_line|#define RXD_TCPCSUM_MASK&t;0x0000ffff
DECL|macro|RXD_TCPCSUM_SHIFT
mdefine_line|#define RXD_TCPCSUM_SHIFT&t;0
DECL|member|err_vlan
id|u32
id|err_vlan
suffix:semicolon
DECL|macro|RXD_VLAN_MASK
mdefine_line|#define RXD_VLAN_MASK&t;&t;&t;0x0000ffff
DECL|macro|RXD_ERR_BAD_CRC
mdefine_line|#define RXD_ERR_BAD_CRC&t;&t;&t;0x00010000
DECL|macro|RXD_ERR_COLLISION
mdefine_line|#define RXD_ERR_COLLISION&t;&t;0x00020000
DECL|macro|RXD_ERR_LINK_LOST
mdefine_line|#define RXD_ERR_LINK_LOST&t;&t;0x00040000
DECL|macro|RXD_ERR_PHY_DECODE
mdefine_line|#define RXD_ERR_PHY_DECODE&t;&t;0x00080000
DECL|macro|RXD_ERR_ODD_NIBBLE_RCVD_MII
mdefine_line|#define RXD_ERR_ODD_NIBBLE_RCVD_MII&t;0x00100000
DECL|macro|RXD_ERR_MAC_ABRT
mdefine_line|#define RXD_ERR_MAC_ABRT&t;&t;0x00200000
DECL|macro|RXD_ERR_TOO_SMALL
mdefine_line|#define RXD_ERR_TOO_SMALL&t;&t;0x00400000
DECL|macro|RXD_ERR_NO_RESOURCES
mdefine_line|#define RXD_ERR_NO_RESOURCES&t;&t;0x00800000
DECL|macro|RXD_ERR_HUGE_FRAME
mdefine_line|#define RXD_ERR_HUGE_FRAME&t;&t;0x01000000
DECL|macro|RXD_ERR_MASK
mdefine_line|#define RXD_ERR_MASK&t;&t;&t;0xffff0000
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|opaque
id|u32
id|opaque
suffix:semicolon
DECL|macro|RXD_OPAQUE_INDEX_MASK
mdefine_line|#define RXD_OPAQUE_INDEX_MASK&t;&t;0x0000ffff
DECL|macro|RXD_OPAQUE_INDEX_SHIFT
mdefine_line|#define RXD_OPAQUE_INDEX_SHIFT&t;&t;0
DECL|macro|RXD_OPAQUE_RING_STD
mdefine_line|#define RXD_OPAQUE_RING_STD&t;&t;0x00010000
DECL|macro|RXD_OPAQUE_RING_JUMBO
mdefine_line|#define RXD_OPAQUE_RING_JUMBO&t;&t;0x00020000
macro_line|#if TG3_MINI_RING_WORKS
DECL|macro|RXD_OPAQUE_RING_MINI
mdefine_line|#define RXD_OPAQUE_RING_MINI&t;&t;0x00040000
macro_line|#endif
DECL|macro|RXD_OPAQUE_RING_MASK
mdefine_line|#define RXD_OPAQUE_RING_MASK&t;&t;0x00070000
)brace
suffix:semicolon
DECL|struct|tg3_ext_rx_buffer_desc
r_struct
id|tg3_ext_rx_buffer_desc
(brace
r_struct
(brace
DECL|member|addr_hi
id|u32
id|addr_hi
suffix:semicolon
DECL|member|addr_lo
id|u32
id|addr_lo
suffix:semicolon
DECL|member|addrlist
)brace
id|addrlist
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|len2_len1
id|u32
id|len2_len1
suffix:semicolon
DECL|member|resv_len3
id|u32
id|resv_len3
suffix:semicolon
DECL|member|std
r_struct
id|tg3_rx_buffer_desc
id|std
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We only use this when testing out the DMA engine&n; * at probe time.  This is the internal format of buffer&n; * descriptors used by the chip at NIC_SRAM_DMA_DESCS.&n; */
DECL|struct|tg3_internal_buffer_desc
r_struct
id|tg3_internal_buffer_desc
(brace
DECL|member|addr_hi
id|u32
id|addr_hi
suffix:semicolon
DECL|member|addr_lo
id|u32
id|addr_lo
suffix:semicolon
DECL|member|nic_mbuf
id|u32
id|nic_mbuf
suffix:semicolon
multiline_comment|/* XXX FIX THIS */
macro_line|#ifdef __BIG_ENDIAN
DECL|member|cqid_sqid
id|u16
id|cqid_sqid
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
macro_line|#else
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|member|cqid_sqid
id|u16
id|cqid_sqid
suffix:semicolon
macro_line|#endif
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|__cookie1
id|u32
id|__cookie1
suffix:semicolon
DECL|member|__cookie2
id|u32
id|__cookie2
suffix:semicolon
DECL|member|__cookie3
id|u32
id|__cookie3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TG3_HW_STATUS_SIZE
mdefine_line|#define TG3_HW_STATUS_SIZE&t;&t;0x80
DECL|struct|tg3_hw_status
r_struct
id|tg3_hw_status
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|macro|SD_STATUS_UPDATED
mdefine_line|#define SD_STATUS_UPDATED&t;&t;0x00000001
DECL|macro|SD_STATUS_LINK_CHG
mdefine_line|#define SD_STATUS_LINK_CHG&t;&t;0x00000002
DECL|macro|SD_STATUS_ERROR
mdefine_line|#define SD_STATUS_ERROR&t;&t;&t;0x00000004
DECL|member|status_tag
id|u32
id|status_tag
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|rx_consumer
id|u16
id|rx_consumer
suffix:semicolon
DECL|member|rx_jumbo_consumer
id|u16
id|rx_jumbo_consumer
suffix:semicolon
macro_line|#else
DECL|member|rx_jumbo_consumer
id|u16
id|rx_jumbo_consumer
suffix:semicolon
DECL|member|rx_consumer
id|u16
id|rx_consumer
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __BIG_ENDIAN
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|rx_mini_consumer
id|u16
id|rx_mini_consumer
suffix:semicolon
macro_line|#else
DECL|member|rx_mini_consumer
id|u16
id|rx_mini_consumer
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
macro_line|#endif
r_struct
(brace
macro_line|#ifdef __BIG_ENDIAN
DECL|member|tx_consumer
id|u16
id|tx_consumer
suffix:semicolon
DECL|member|rx_producer
id|u16
id|rx_producer
suffix:semicolon
macro_line|#else
id|u16
id|rx_producer
suffix:semicolon
id|u16
id|tx_consumer
suffix:semicolon
macro_line|#endif
DECL|member|idx
)brace
id|idx
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|high
DECL|member|low
id|u32
id|high
comma
id|low
suffix:semicolon
DECL|typedef|tg3_stat64_t
)brace
id|tg3_stat64_t
suffix:semicolon
DECL|struct|tg3_hw_stats
r_struct
id|tg3_hw_stats
(brace
DECL|member|__reserved0
id|u8
id|__reserved0
(braket
l_int|0x400
op_minus
l_int|0x300
)braket
suffix:semicolon
multiline_comment|/* Statistics maintained by Receive MAC. */
DECL|member|rx_octets
id|tg3_stat64_t
id|rx_octets
suffix:semicolon
DECL|member|__reserved1
id|u64
id|__reserved1
suffix:semicolon
DECL|member|rx_fragments
id|tg3_stat64_t
id|rx_fragments
suffix:semicolon
DECL|member|rx_ucast_packets
id|tg3_stat64_t
id|rx_ucast_packets
suffix:semicolon
DECL|member|rx_mcast_packets
id|tg3_stat64_t
id|rx_mcast_packets
suffix:semicolon
DECL|member|rx_bcast_packets
id|tg3_stat64_t
id|rx_bcast_packets
suffix:semicolon
DECL|member|rx_fcs_errors
id|tg3_stat64_t
id|rx_fcs_errors
suffix:semicolon
DECL|member|rx_align_errors
id|tg3_stat64_t
id|rx_align_errors
suffix:semicolon
DECL|member|rx_xon_pause_rcvd
id|tg3_stat64_t
id|rx_xon_pause_rcvd
suffix:semicolon
DECL|member|rx_xoff_pause_rcvd
id|tg3_stat64_t
id|rx_xoff_pause_rcvd
suffix:semicolon
DECL|member|rx_mac_ctrl_rcvd
id|tg3_stat64_t
id|rx_mac_ctrl_rcvd
suffix:semicolon
DECL|member|rx_xoff_entered
id|tg3_stat64_t
id|rx_xoff_entered
suffix:semicolon
DECL|member|rx_frame_too_long_errors
id|tg3_stat64_t
id|rx_frame_too_long_errors
suffix:semicolon
DECL|member|rx_jabbers
id|tg3_stat64_t
id|rx_jabbers
suffix:semicolon
DECL|member|rx_undersize_packets
id|tg3_stat64_t
id|rx_undersize_packets
suffix:semicolon
DECL|member|rx_in_length_errors
id|tg3_stat64_t
id|rx_in_length_errors
suffix:semicolon
DECL|member|rx_out_length_errors
id|tg3_stat64_t
id|rx_out_length_errors
suffix:semicolon
DECL|member|rx_64_or_less_octet_packets
id|tg3_stat64_t
id|rx_64_or_less_octet_packets
suffix:semicolon
DECL|member|rx_65_to_127_octet_packets
id|tg3_stat64_t
id|rx_65_to_127_octet_packets
suffix:semicolon
DECL|member|rx_128_to_255_octet_packets
id|tg3_stat64_t
id|rx_128_to_255_octet_packets
suffix:semicolon
DECL|member|rx_256_to_511_octet_packets
id|tg3_stat64_t
id|rx_256_to_511_octet_packets
suffix:semicolon
DECL|member|rx_512_to_1023_octet_packets
id|tg3_stat64_t
id|rx_512_to_1023_octet_packets
suffix:semicolon
DECL|member|rx_1024_to_1522_octet_packets
id|tg3_stat64_t
id|rx_1024_to_1522_octet_packets
suffix:semicolon
DECL|member|rx_1523_to_2047_octet_packets
id|tg3_stat64_t
id|rx_1523_to_2047_octet_packets
suffix:semicolon
DECL|member|rx_2048_to_4095_octet_packets
id|tg3_stat64_t
id|rx_2048_to_4095_octet_packets
suffix:semicolon
DECL|member|rx_4096_to_8191_octet_packets
id|tg3_stat64_t
id|rx_4096_to_8191_octet_packets
suffix:semicolon
DECL|member|rx_8192_to_9022_octet_packets
id|tg3_stat64_t
id|rx_8192_to_9022_octet_packets
suffix:semicolon
DECL|member|__unused0
id|u64
id|__unused0
(braket
l_int|37
)braket
suffix:semicolon
multiline_comment|/* Statistics maintained by Transmit MAC. */
DECL|member|tx_octets
id|tg3_stat64_t
id|tx_octets
suffix:semicolon
DECL|member|__reserved2
id|u64
id|__reserved2
suffix:semicolon
DECL|member|tx_collisions
id|tg3_stat64_t
id|tx_collisions
suffix:semicolon
DECL|member|tx_xon_sent
id|tg3_stat64_t
id|tx_xon_sent
suffix:semicolon
DECL|member|tx_xoff_sent
id|tg3_stat64_t
id|tx_xoff_sent
suffix:semicolon
DECL|member|tx_flow_control
id|tg3_stat64_t
id|tx_flow_control
suffix:semicolon
DECL|member|tx_mac_errors
id|tg3_stat64_t
id|tx_mac_errors
suffix:semicolon
DECL|member|tx_single_collisions
id|tg3_stat64_t
id|tx_single_collisions
suffix:semicolon
DECL|member|tx_mult_collisions
id|tg3_stat64_t
id|tx_mult_collisions
suffix:semicolon
DECL|member|tx_deferred
id|tg3_stat64_t
id|tx_deferred
suffix:semicolon
DECL|member|__reserved3
id|u64
id|__reserved3
suffix:semicolon
DECL|member|tx_excessive_collisions
id|tg3_stat64_t
id|tx_excessive_collisions
suffix:semicolon
DECL|member|tx_late_collisions
id|tg3_stat64_t
id|tx_late_collisions
suffix:semicolon
DECL|member|tx_collide_2times
id|tg3_stat64_t
id|tx_collide_2times
suffix:semicolon
DECL|member|tx_collide_3times
id|tg3_stat64_t
id|tx_collide_3times
suffix:semicolon
DECL|member|tx_collide_4times
id|tg3_stat64_t
id|tx_collide_4times
suffix:semicolon
DECL|member|tx_collide_5times
id|tg3_stat64_t
id|tx_collide_5times
suffix:semicolon
DECL|member|tx_collide_6times
id|tg3_stat64_t
id|tx_collide_6times
suffix:semicolon
DECL|member|tx_collide_7times
id|tg3_stat64_t
id|tx_collide_7times
suffix:semicolon
DECL|member|tx_collide_8times
id|tg3_stat64_t
id|tx_collide_8times
suffix:semicolon
DECL|member|tx_collide_9times
id|tg3_stat64_t
id|tx_collide_9times
suffix:semicolon
DECL|member|tx_collide_10times
id|tg3_stat64_t
id|tx_collide_10times
suffix:semicolon
DECL|member|tx_collide_11times
id|tg3_stat64_t
id|tx_collide_11times
suffix:semicolon
DECL|member|tx_collide_12times
id|tg3_stat64_t
id|tx_collide_12times
suffix:semicolon
DECL|member|tx_collide_13times
id|tg3_stat64_t
id|tx_collide_13times
suffix:semicolon
DECL|member|tx_collide_14times
id|tg3_stat64_t
id|tx_collide_14times
suffix:semicolon
DECL|member|tx_collide_15times
id|tg3_stat64_t
id|tx_collide_15times
suffix:semicolon
DECL|member|tx_ucast_packets
id|tg3_stat64_t
id|tx_ucast_packets
suffix:semicolon
DECL|member|tx_mcast_packets
id|tg3_stat64_t
id|tx_mcast_packets
suffix:semicolon
DECL|member|tx_bcast_packets
id|tg3_stat64_t
id|tx_bcast_packets
suffix:semicolon
DECL|member|tx_carrier_sense_errors
id|tg3_stat64_t
id|tx_carrier_sense_errors
suffix:semicolon
DECL|member|tx_discards
id|tg3_stat64_t
id|tx_discards
suffix:semicolon
DECL|member|tx_errors
id|tg3_stat64_t
id|tx_errors
suffix:semicolon
DECL|member|__unused1
id|u64
id|__unused1
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* Statistics maintained by Receive List Placement. */
DECL|member|COS_rx_packets
id|tg3_stat64_t
id|COS_rx_packets
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|COS_rx_filter_dropped
id|tg3_stat64_t
id|COS_rx_filter_dropped
suffix:semicolon
DECL|member|dma_writeq_full
id|tg3_stat64_t
id|dma_writeq_full
suffix:semicolon
DECL|member|dma_write_prioq_full
id|tg3_stat64_t
id|dma_write_prioq_full
suffix:semicolon
DECL|member|rxbds_empty
id|tg3_stat64_t
id|rxbds_empty
suffix:semicolon
DECL|member|rx_discards
id|tg3_stat64_t
id|rx_discards
suffix:semicolon
DECL|member|rx_errors
id|tg3_stat64_t
id|rx_errors
suffix:semicolon
DECL|member|rx_threshold_hit
id|tg3_stat64_t
id|rx_threshold_hit
suffix:semicolon
DECL|member|__unused2
id|u64
id|__unused2
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Statistics maintained by Send Data Initiator. */
DECL|member|COS_out_packets
id|tg3_stat64_t
id|COS_out_packets
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|dma_readq_full
id|tg3_stat64_t
id|dma_readq_full
suffix:semicolon
DECL|member|dma_read_prioq_full
id|tg3_stat64_t
id|dma_read_prioq_full
suffix:semicolon
DECL|member|tx_comp_queue_full
id|tg3_stat64_t
id|tx_comp_queue_full
suffix:semicolon
multiline_comment|/* Statistics maintained by Host Coalescing. */
DECL|member|ring_set_send_prod_index
id|tg3_stat64_t
id|ring_set_send_prod_index
suffix:semicolon
DECL|member|ring_status_update
id|tg3_stat64_t
id|ring_status_update
suffix:semicolon
DECL|member|nic_irqs
id|tg3_stat64_t
id|nic_irqs
suffix:semicolon
DECL|member|nic_avoided_irqs
id|tg3_stat64_t
id|nic_avoided_irqs
suffix:semicolon
DECL|member|nic_tx_threshold_hit
id|tg3_stat64_t
id|nic_tx_threshold_hit
suffix:semicolon
DECL|member|__reserved4
id|u8
id|__reserved4
(braket
l_int|0xb00
op_minus
l_int|0x9c0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|phy_led_mode
r_enum
id|phy_led_mode
(brace
DECL|enumerator|led_mode_auto
id|led_mode_auto
comma
DECL|enumerator|led_mode_three_link
id|led_mode_three_link
comma
DECL|enumerator|led_mode_link10
id|led_mode_link10
)brace
suffix:semicolon
multiline_comment|/* &squot;mapping&squot; is superfluous as the chip does not write into&n; * the tx/rx post rings so we could just fetch it from there.&n; * But the cache behavior is better how we are doing it now.&n; */
DECL|struct|ring_info
r_struct
id|ring_info
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|DECLARE_PCI_UNMAP_ADDR
c_func
(paren
id|mapping
)paren
)brace
suffix:semicolon
DECL|struct|tg3_config_info
r_struct
id|tg3_config_info
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tg3_link_config
r_struct
id|tg3_link_config
(brace
multiline_comment|/* Describes what we&squot;re trying to get. */
DECL|member|advertising
id|u32
id|advertising
suffix:semicolon
DECL|member|speed
id|u16
id|speed
suffix:semicolon
DECL|member|duplex
id|u8
id|duplex
suffix:semicolon
DECL|member|autoneg
id|u8
id|autoneg
suffix:semicolon
multiline_comment|/* Describes what we actually have. */
DECL|member|active_speed
id|u16
id|active_speed
suffix:semicolon
DECL|member|active_duplex
id|u8
id|active_duplex
suffix:semicolon
DECL|macro|SPEED_INVALID
mdefine_line|#define SPEED_INVALID&t;&t;0xffff
DECL|macro|DUPLEX_INVALID
mdefine_line|#define DUPLEX_INVALID&t;&t;0xff
DECL|macro|AUTONEG_INVALID
mdefine_line|#define AUTONEG_INVALID&t;&t;0xff
multiline_comment|/* When we go in and out of low power mode we need&n;&t; * to swap with this state.&n;&t; */
DECL|member|phy_is_low_power
r_int
id|phy_is_low_power
suffix:semicolon
DECL|member|orig_speed
id|u16
id|orig_speed
suffix:semicolon
DECL|member|orig_duplex
id|u8
id|orig_duplex
suffix:semicolon
DECL|member|orig_autoneg
id|u8
id|orig_autoneg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tg3_bufmgr_config
r_struct
id|tg3_bufmgr_config
(brace
DECL|member|mbuf_read_dma_low_water
id|u32
id|mbuf_read_dma_low_water
suffix:semicolon
DECL|member|mbuf_mac_rx_low_water
id|u32
id|mbuf_mac_rx_low_water
suffix:semicolon
DECL|member|mbuf_high_water
id|u32
id|mbuf_high_water
suffix:semicolon
DECL|member|mbuf_read_dma_low_water_jumbo
id|u32
id|mbuf_read_dma_low_water_jumbo
suffix:semicolon
DECL|member|mbuf_mac_rx_low_water_jumbo
id|u32
id|mbuf_mac_rx_low_water_jumbo
suffix:semicolon
DECL|member|mbuf_high_water_jumbo
id|u32
id|mbuf_high_water_jumbo
suffix:semicolon
DECL|member|dma_low_water
id|u32
id|dma_low_water
suffix:semicolon
DECL|member|dma_high_water
id|u32
id|dma_high_water
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tg3
r_struct
id|tg3
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|tx_prod
id|u32
id|tx_prod
suffix:semicolon
DECL|member|tx_cons
id|u32
id|tx_cons
suffix:semicolon
DECL|member|rx_rcb_ptr
id|u32
id|rx_rcb_ptr
suffix:semicolon
DECL|member|rx_std_ptr
id|u32
id|rx_std_ptr
suffix:semicolon
DECL|member|rx_jumbo_ptr
id|u32
id|rx_jumbo_ptr
suffix:semicolon
macro_line|#if TG3_MINI_RING_WORKS
DECL|member|rx_mini_ptr
id|u32
id|rx_mini_ptr
suffix:semicolon
macro_line|#endif
DECL|member|indirect_lock
id|spinlock_t
id|indirect_lock
suffix:semicolon
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
DECL|member|net_stats_prev
r_struct
id|net_device_stats
id|net_stats_prev
suffix:semicolon
DECL|member|phy_crc_errors
r_int
r_int
id|phy_crc_errors
suffix:semicolon
multiline_comment|/* Adaptive coalescing engine. */
DECL|member|last_rate_sample
r_int
r_int
id|last_rate_sample
suffix:semicolon
DECL|member|last_rx_count
id|u32
id|last_rx_count
suffix:semicolon
DECL|member|last_tx_count
id|u32
id|last_tx_count
suffix:semicolon
DECL|member|rx_offset
id|u32
id|rx_offset
suffix:semicolon
DECL|member|tg3_flags
id|u32
id|tg3_flags
suffix:semicolon
DECL|macro|TG3_FLAG_HOST_TXDS
mdefine_line|#define TG3_FLAG_HOST_TXDS&t;&t;0x00000001
DECL|macro|TG3_FLAG_TXD_MBOX_HWBUG
mdefine_line|#define TG3_FLAG_TXD_MBOX_HWBUG&t;&t;0x00000002
DECL|macro|TG3_FLAG_RX_CHECKSUMS
mdefine_line|#define TG3_FLAG_RX_CHECKSUMS&t;&t;0x00000004
DECL|macro|TG3_FLAG_USE_LINKCHG_REG
mdefine_line|#define TG3_FLAG_USE_LINKCHG_REG&t;0x00000008
DECL|macro|TG3_FLAG_USE_MI_INTERRUPT
mdefine_line|#define TG3_FLAG_USE_MI_INTERRUPT&t;0x00000010
DECL|macro|TG3_FLAG_ADAPTIVE_RX
mdefine_line|#define TG3_FLAG_ADAPTIVE_RX&t;&t;0x00000020
DECL|macro|TG3_FLAG_ADAPTIVE_TX
mdefine_line|#define TG3_FLAG_ADAPTIVE_TX&t;&t;0x00000040
DECL|macro|TG3_FLAG_POLL_SERDES
mdefine_line|#define TG3_FLAG_POLL_SERDES&t;&t;0x00000080
DECL|macro|TG3_FLAG_PHY_RESET_ON_INIT
mdefine_line|#define TG3_FLAG_PHY_RESET_ON_INIT&t;0x00000100
DECL|macro|TG3_FLAG_PCIX_TARGET_HWBUG
mdefine_line|#define TG3_FLAG_PCIX_TARGET_HWBUG&t;0x00000200
DECL|macro|TG3_FLAG_WOL_SPEED_100MB
mdefine_line|#define TG3_FLAG_WOL_SPEED_100MB&t;0x00000400
DECL|macro|TG3_FLAG_WOL_ENABLE
mdefine_line|#define TG3_FLAG_WOL_ENABLE&t;&t;0x00001000
DECL|macro|TG3_FLAG_NVRAM
mdefine_line|#define TG3_FLAG_NVRAM&t;&t;&t;0x00002000
DECL|macro|TG3_FLAG_NVRAM_BUFFERED
mdefine_line|#define TG3_FLAG_NVRAM_BUFFERED&t;&t;0x00004000
DECL|macro|TG3_FLAG_RX_PAUSE
mdefine_line|#define TG3_FLAG_RX_PAUSE&t;&t;0x00008000
DECL|macro|TG3_FLAG_TX_PAUSE
mdefine_line|#define TG3_FLAG_TX_PAUSE&t;&t;0x00010000
DECL|macro|TG3_FLAG_PCIX_MODE
mdefine_line|#define TG3_FLAG_PCIX_MODE&t;&t;0x00020000
DECL|macro|TG3_FLAG_PCI_HIGH_SPEED
mdefine_line|#define TG3_FLAG_PCI_HIGH_SPEED&t;&t;0x00040000
DECL|macro|TG3_FLAG_PCI_32BIT
mdefine_line|#define TG3_FLAG_PCI_32BIT&t;&t;0x00080000
DECL|macro|TG3_FLAG_NO_TX_PSEUDO_CSUM
mdefine_line|#define TG3_FLAG_NO_TX_PSEUDO_CSUM&t;0x00100000
DECL|macro|TG3_FLAG_NO_RX_PSEUDO_CSUM
mdefine_line|#define TG3_FLAG_NO_RX_PSEUDO_CSUM&t;0x00200000
DECL|macro|TG3_FLAG_AUTONEG_DISABLE
mdefine_line|#define TG3_FLAG_AUTONEG_DISABLE&t;0x00400000
DECL|macro|TG3_FLAG_JUMBO_ENABLE
mdefine_line|#define TG3_FLAG_JUMBO_ENABLE&t;&t;0x00800000
DECL|macro|TG3_FLAG_10_100_ONLY
mdefine_line|#define TG3_FLAG_10_100_ONLY&t;&t;0x01000000
DECL|macro|TG3_FLAG_PAUSE_AUTONEG
mdefine_line|#define TG3_FLAG_PAUSE_AUTONEG&t;&t;0x02000000
DECL|macro|TG3_FLAG_PAUSE_RX
mdefine_line|#define TG3_FLAG_PAUSE_RX&t;&t;0x04000000
DECL|macro|TG3_FLAG_PAUSE_TX
mdefine_line|#define TG3_FLAG_PAUSE_TX&t;&t;0x08000000
DECL|macro|TG3_FLAG_BROKEN_CHECKSUMS
mdefine_line|#define TG3_FLAG_BROKEN_CHECKSUMS&t;0x10000000
DECL|macro|TG3_FLAG_GOT_SERDES_FLOWCTL
mdefine_line|#define TG3_FLAG_GOT_SERDES_FLOWCTL&t;0x20000000
DECL|macro|TG3_FLAG_INIT_COMPLETE
mdefine_line|#define TG3_FLAG_INIT_COMPLETE&t;&t;0x80000000
DECL|member|msg_enable
id|u32
id|msg_enable
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|timer_counter
id|u16
id|timer_counter
suffix:semicolon
DECL|member|timer_multiplier
id|u16
id|timer_multiplier
suffix:semicolon
DECL|member|timer_offset
id|u32
id|timer_offset
suffix:semicolon
DECL|member|link_config
r_struct
id|tg3_link_config
id|link_config
suffix:semicolon
DECL|member|bufmgr_config
r_struct
id|tg3_bufmgr_config
id|bufmgr_config
suffix:semicolon
DECL|member|rx_pending
id|u32
id|rx_pending
suffix:semicolon
macro_line|#if TG3_MINI_RING_WORKS
DECL|member|rx_mini_pending
id|u32
id|rx_mini_pending
suffix:semicolon
macro_line|#endif
DECL|member|rx_jumbo_pending
id|u32
id|rx_jumbo_pending
suffix:semicolon
DECL|member|tx_pending
id|u32
id|tx_pending
suffix:semicolon
multiline_comment|/* cache h/w values, often passed straight to h/w */
DECL|member|rx_mode
id|u32
id|rx_mode
suffix:semicolon
DECL|member|tx_mode
id|u32
id|tx_mode
suffix:semicolon
DECL|member|mac_mode
id|u32
id|mac_mode
suffix:semicolon
DECL|member|mi_mode
id|u32
id|mi_mode
suffix:semicolon
DECL|member|misc_host_ctrl
id|u32
id|misc_host_ctrl
suffix:semicolon
DECL|member|grc_mode
id|u32
id|grc_mode
suffix:semicolon
DECL|member|grc_local_ctrl
id|u32
id|grc_local_ctrl
suffix:semicolon
DECL|member|dma_rwctrl
id|u32
id|dma_rwctrl
suffix:semicolon
DECL|member|coalesce_mode
id|u32
id|coalesce_mode
suffix:semicolon
multiline_comment|/* PCI block */
DECL|member|pci_chip_rev_id
id|u16
id|pci_chip_rev_id
suffix:semicolon
DECL|member|pci_cacheline_sz
id|u8
id|pci_cacheline_sz
suffix:semicolon
DECL|member|pci_lat_timer
id|u8
id|pci_lat_timer
suffix:semicolon
DECL|member|pci_hdr_type
id|u8
id|pci_hdr_type
suffix:semicolon
DECL|member|pci_bist
id|u8
id|pci_bist
suffix:semicolon
DECL|member|pci_cfg_state
id|u32
id|pci_cfg_state
(braket
l_int|64
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|pm_cap
r_int
id|pm_cap
suffix:semicolon
multiline_comment|/* PHY info */
DECL|member|phy_id
id|u32
id|phy_id
suffix:semicolon
DECL|macro|PHY_ID_MASK
mdefine_line|#define PHY_ID_MASK&t;&t;&t;0xfffffff0
DECL|macro|PHY_ID_BCM5400
mdefine_line|#define PHY_ID_BCM5400&t;&t;&t;0x60008040
DECL|macro|PHY_ID_BCM5401
mdefine_line|#define PHY_ID_BCM5401&t;&t;&t;0x60008050
DECL|macro|PHY_ID_BCM5411
mdefine_line|#define PHY_ID_BCM5411&t;&t;&t;0x60008070
DECL|macro|PHY_ID_BCM5701
mdefine_line|#define PHY_ID_BCM5701&t;&t;&t;0x60008110
DECL|macro|PHY_ID_BCM5703
mdefine_line|#define PHY_ID_BCM5703&t;&t;&t;0x60008160
DECL|macro|PHY_ID_BCM8002
mdefine_line|#define PHY_ID_BCM8002&t;&t;&t;0x60010140
DECL|macro|PHY_ID_SERDES
mdefine_line|#define PHY_ID_SERDES&t;&t;&t;0xfeedbee0
DECL|macro|PHY_ID_INVALID
mdefine_line|#define PHY_ID_INVALID&t;&t;&t;0xffffffff
DECL|macro|PHY_ID_REV_MASK
mdefine_line|#define PHY_ID_REV_MASK&t;&t;&t;0x0000000f
DECL|macro|PHY_REV_BCM5401_B0
mdefine_line|#define PHY_REV_BCM5401_B0&t;&t;0x1
DECL|macro|PHY_REV_BCM5401_B2
mdefine_line|#define PHY_REV_BCM5401_B2&t;&t;0x3
DECL|macro|PHY_REV_BCM5401_C0
mdefine_line|#define PHY_REV_BCM5401_C0&t;&t;0x6
DECL|macro|PHY_REV_BCM5411_X0
mdefine_line|#define PHY_REV_BCM5411_X0&t;&t;0x1 /* Found on Netgear GA302T */
DECL|member|led_mode
r_enum
id|phy_led_mode
id|led_mode
suffix:semicolon
DECL|member|board_part_number
r_char
id|board_part_number
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* This macro assumes the passed PHY ID is already masked&n;&t; * with PHY_ID_MASK.&n;&t; */
DECL|macro|KNOWN_PHY_ID
mdefine_line|#define KNOWN_PHY_ID(X)&t;&t;&bslash;&n;&t;((X) == PHY_ID_BCM5400 || (X) == PHY_ID_BCM5401 || &bslash;&n;&t; (X) == PHY_ID_BCM5411 || (X) == PHY_ID_BCM5701 || &bslash;&n;&t; (X) == PHY_ID_BCM5703 ||&t;&t;&t;   &bslash;&n;&t; (X) == PHY_ID_BCM8002 || (X) == PHY_ID_SERDES)
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
macro_line|#if TG3_VLAN_TAG_USED
DECL|member|vlgrp
r_struct
id|vlan_group
op_star
id|vlgrp
suffix:semicolon
macro_line|#endif
DECL|member|rx_std
r_struct
id|tg3_rx_buffer_desc
op_star
id|rx_std
suffix:semicolon
DECL|member|rx_std_buffers
r_struct
id|ring_info
op_star
id|rx_std_buffers
suffix:semicolon
DECL|member|rx_std_mapping
id|dma_addr_t
id|rx_std_mapping
suffix:semicolon
macro_line|#if TG3_MINI_RING_WORKS
DECL|member|rx_mini
r_struct
id|tg3_rx_buffer_desc
op_star
id|rx_mini
suffix:semicolon
DECL|member|rx_mini_buffers
r_struct
id|ring_info
op_star
id|rx_mini_buffers
suffix:semicolon
DECL|member|rx_mini_mapping
id|dma_addr_t
id|rx_mini_mapping
suffix:semicolon
macro_line|#endif
DECL|member|rx_jumbo
r_struct
id|tg3_rx_buffer_desc
op_star
id|rx_jumbo
suffix:semicolon
DECL|member|rx_jumbo_buffers
r_struct
id|ring_info
op_star
id|rx_jumbo_buffers
suffix:semicolon
DECL|member|rx_jumbo_mapping
id|dma_addr_t
id|rx_jumbo_mapping
suffix:semicolon
DECL|member|rx_rcb
r_struct
id|tg3_rx_buffer_desc
op_star
id|rx_rcb
suffix:semicolon
DECL|member|rx_rcb_mapping
id|dma_addr_t
id|rx_rcb_mapping
suffix:semicolon
multiline_comment|/* TX descs are only used if TG3_FLAG_HOST_TXDS is set. */
DECL|member|tx_ring
r_struct
id|tg3_tx_buffer_desc
op_star
id|tx_ring
suffix:semicolon
DECL|member|tx_buffers
r_struct
id|ring_info
op_star
id|tx_buffers
suffix:semicolon
DECL|member|tx_desc_mapping
id|dma_addr_t
id|tx_desc_mapping
suffix:semicolon
DECL|member|hw_status
r_struct
id|tg3_hw_status
op_star
id|hw_status
suffix:semicolon
DECL|member|status_mapping
id|dma_addr_t
id|status_mapping
suffix:semicolon
DECL|member|hw_stats
r_struct
id|tg3_hw_stats
op_star
id|hw_stats
suffix:semicolon
DECL|member|stats_mapping
id|dma_addr_t
id|stats_mapping
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(_T3_H) */
eof
