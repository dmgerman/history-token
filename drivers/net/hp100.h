multiline_comment|/*&n; * hp100.h: Hewlett Packard HP10/100VG ANY LAN ethernet driver for Linux.&n; *&n; * $Id: hp100.h,v 1.51 1997/04/08 14:26:42 floeff Exp floeff $&n; *&n; * Authors:  Jaroslav Kysela, &lt;perex@pf.jcu.cz&gt;&n; *           Siegfried Loeffler &lt;floeff@tunix.mathematik.uni-stuttgart.de&gt;&n; *&n; * This driver is based on the &squot;hpfepkt&squot; crynwr packet driver.&n; *&n; * This source/code is public free; you can distribute it and/or modify &n; * it under terms of the GNU General Public License (published by the&n; * Free Software Foundation) either version two of this License, or any &n; * later version.&n; */
multiline_comment|/****************************************************************************&n; *  Hardware Constants&n; ****************************************************************************/
multiline_comment|/* &n; * Page Identifiers&n; * (Swap Paging Register, PAGING, bits 3:0, Offset 0x02)&n; */
DECL|macro|HP100_PAGE_PERFORMANCE
mdefine_line|#define HP100_PAGE_PERFORMANCE&t;0x0&t;/* Page 0 */
DECL|macro|HP100_PAGE_MAC_ADDRESS
mdefine_line|#define HP100_PAGE_MAC_ADDRESS&t;0x1&t;/* Page 1 */
DECL|macro|HP100_PAGE_HW_MAP
mdefine_line|#define HP100_PAGE_HW_MAP&t;0x2&t;/* Page 2 */
DECL|macro|HP100_PAGE_EEPROM_CTRL
mdefine_line|#define HP100_PAGE_EEPROM_CTRL&t;0x3&t;/* Page 3 */
DECL|macro|HP100_PAGE_MAC_CTRL
mdefine_line|#define HP100_PAGE_MAC_CTRL&t;0x4&t;/* Page 4 */
DECL|macro|HP100_PAGE_MMU_CFG
mdefine_line|#define HP100_PAGE_MMU_CFG&t;0x5&t;/* Page 5 */
DECL|macro|HP100_PAGE_ID_MAC_ADDR
mdefine_line|#define HP100_PAGE_ID_MAC_ADDR&t;0x6&t;/* Page 6 */
DECL|macro|HP100_PAGE_MMU_POINTER
mdefine_line|#define HP100_PAGE_MMU_POINTER&t;0x7&t;/* Page 7 */
multiline_comment|/* Registers that are present on all pages  */
DECL|macro|HP100_REG_HW_ID
mdefine_line|#define HP100_REG_HW_ID&t;&t;0x00&t;/* R:  (16) Unique card ID           */
DECL|macro|HP100_REG_TRACE
mdefine_line|#define HP100_REG_TRACE&t;&t;0x00&t;/* W:  (16) Used for debug output    */
DECL|macro|HP100_REG_PAGING
mdefine_line|#define HP100_REG_PAGING&t;0x02&t;/* R:  (16),15:4 Card ID             */
multiline_comment|/* W:  (16),3:0 Switch pages         */
DECL|macro|HP100_REG_OPTION_LSW
mdefine_line|#define HP100_REG_OPTION_LSW&t;0x04&t;/* RW: (16) Select card functions    */
DECL|macro|HP100_REG_OPTION_MSW
mdefine_line|#define HP100_REG_OPTION_MSW&t;0x06&t;/* RW: (16) Select card functions    */
multiline_comment|/*  Page 0 - Performance  */
DECL|macro|HP100_REG_IRQ_STATUS
mdefine_line|#define HP100_REG_IRQ_STATUS&t;0x08&t;/* RW: (16) Which ints are pending   */
DECL|macro|HP100_REG_IRQ_MASK
mdefine_line|#define HP100_REG_IRQ_MASK&t;0x0a&t;/* RW: (16) Select ints to allow     */
DECL|macro|HP100_REG_FRAGMENT_LEN
mdefine_line|#define HP100_REG_FRAGMENT_LEN&t;0x0c&t;/* W: (16)12:0 Current fragment len */
multiline_comment|/* Note: For 32 bit systems, fragment len and offset registers are available */
multiline_comment|/*       at offset 0x28 and 0x2c, where they can be written as 32bit values. */
DECL|macro|HP100_REG_OFFSET
mdefine_line|#define HP100_REG_OFFSET&t;0x0e&t;/* RW: (16)12:0 Offset to start read */
DECL|macro|HP100_REG_DATA32
mdefine_line|#define HP100_REG_DATA32&t;0x10&t;/* RW: (32) I/O mode data port       */
DECL|macro|HP100_REG_DATA16
mdefine_line|#define HP100_REG_DATA16&t;0x12&t;/* RW: WORDs must be read from here  */
DECL|macro|HP100_REG_TX_MEM_FREE
mdefine_line|#define HP100_REG_TX_MEM_FREE&t;0x14&t;/* RD: (32) Amount of free Tx mem    */
DECL|macro|HP100_REG_TX_PDA_L
mdefine_line|#define HP100_REG_TX_PDA_L      0x14    /* W: (32) BM: Ptr to PDL, Low Pri  */
DECL|macro|HP100_REG_TX_PDA_H
mdefine_line|#define HP100_REG_TX_PDA_H      0x1c    /* W: (32) BM: Ptr to PDL, High Pri */
DECL|macro|HP100_REG_RX_PKT_CNT
mdefine_line|#define HP100_REG_RX_PKT_CNT&t;0x18&t;/* RD: (8) Rx count of pkts on card  */
DECL|macro|HP100_REG_TX_PKT_CNT
mdefine_line|#define HP100_REG_TX_PKT_CNT&t;0x19&t;/* RD: (8) Tx count of pkts on card  */
DECL|macro|HP100_REG_RX_PDL
mdefine_line|#define HP100_REG_RX_PDL        0x1a    /* R: (8) BM: # rx pdl not executed */
DECL|macro|HP100_REG_TX_PDL
mdefine_line|#define HP100_REG_TX_PDL        0x1b    /* R: (8) BM: # tx pdl not executed */
DECL|macro|HP100_REG_RX_PDA
mdefine_line|#define HP100_REG_RX_PDA        0x18    /* W: (32) BM: Up to 31 addresses */
multiline_comment|/*             which point to a PDL */
DECL|macro|HP100_REG_SL_EARLY
mdefine_line|#define HP100_REG_SL_EARLY      0x1c    /*    (32) Enhanced Slave Early Rx */
DECL|macro|HP100_REG_STAT_DROPPED
mdefine_line|#define HP100_REG_STAT_DROPPED  0x20    /* R (12) Dropped Packet Counter */
DECL|macro|HP100_REG_STAT_ERRORED
mdefine_line|#define HP100_REG_STAT_ERRORED  0x22    /* R (8) Errored Packet Counter */
DECL|macro|HP100_REG_STAT_ABORT
mdefine_line|#define HP100_REG_STAT_ABORT    0x23    /* R (8) Abort Counter/OW Coll. Flag */
DECL|macro|HP100_REG_RX_RING
mdefine_line|#define HP100_REG_RX_RING       0x24    /* W (32) Slave: RX Ring Pointers */
DECL|macro|HP100_REG_32_FRAGMENT_LEN
mdefine_line|#define HP100_REG_32_FRAGMENT_LEN 0x28  /* W (13) Slave: Fragment Length Reg */
DECL|macro|HP100_REG_32_OFFSET
mdefine_line|#define HP100_REG_32_OFFSET     0x2c    /* W (16) Slave: Offset Register */
multiline_comment|/*  Page 1 - MAC Address/Hash Table  */
DECL|macro|HP100_REG_MAC_ADDR
mdefine_line|#define HP100_REG_MAC_ADDR&t;0x08&t;/* RW: (8) Cards MAC address&t;     */
DECL|macro|HP100_REG_HASH_BYTE0
mdefine_line|#define HP100_REG_HASH_BYTE0&t;0x10&t;/* RW: (8) Cards multicast filter    */
multiline_comment|/*  Page 2 - Hardware Mapping  */
DECL|macro|HP100_REG_MEM_MAP_LSW
mdefine_line|#define HP100_REG_MEM_MAP_LSW&t;0x08&t;/* RW: (16) LSW of cards mem addr    */
DECL|macro|HP100_REG_MEM_MAP_MSW
mdefine_line|#define HP100_REG_MEM_MAP_MSW&t;0x0a&t;/* RW: (16) MSW of cards mem addr    */
DECL|macro|HP100_REG_IO_MAP
mdefine_line|#define HP100_REG_IO_MAP&t;0x0c&t;/* RW: (8) Cards I/O address         */
DECL|macro|HP100_REG_IRQ_CHANNEL
mdefine_line|#define HP100_REG_IRQ_CHANNEL&t;0x0d&t;/* RW: (8) IRQ and edge/level int    */
DECL|macro|HP100_REG_SRAM
mdefine_line|#define HP100_REG_SRAM&t;&t;0x0e&t;/* RW: (8) How much RAM on card      */
DECL|macro|HP100_REG_BM
mdefine_line|#define HP100_REG_BM&t;&t;0x0f&t;/* RW: (8) Controls BM functions     */
multiline_comment|/* New on Page 2 for ETR chips: */
DECL|macro|HP100_REG_MODECTRL1
mdefine_line|#define HP100_REG_MODECTRL1     0x10    /* RW: (8) Mode Control 1 */
DECL|macro|HP100_REG_MODECTRL2
mdefine_line|#define HP100_REG_MODECTRL2     0x11    /* RW: (8) Mode Control 2 */
DECL|macro|HP100_REG_PCICTRL1
mdefine_line|#define HP100_REG_PCICTRL1      0x12    /* RW: (8) PCI Cfg 1 */
DECL|macro|HP100_REG_PCICTRL2
mdefine_line|#define HP100_REG_PCICTRL2      0x13    /* RW: (8) PCI Cfg 2 */
DECL|macro|HP100_REG_PCIBUSMLAT
mdefine_line|#define HP100_REG_PCIBUSMLAT    0x15    /* RW: (8) PCI Bus Master Latency */
DECL|macro|HP100_REG_EARLYTXCFG
mdefine_line|#define HP100_REG_EARLYTXCFG    0x16    /* RW: (16) Early TX Cfg/Cntrl Reg */
DECL|macro|HP100_REG_EARLYRXCFG
mdefine_line|#define HP100_REG_EARLYRXCFG    0x18    /* RW: (8) Early RX Cfg/Cntrl Reg */
DECL|macro|HP100_REG_ISAPNPCFG1
mdefine_line|#define HP100_REG_ISAPNPCFG1    0x1a    /* RW: (8) ISA PnP Cfg/Cntrl Reg 1 */
DECL|macro|HP100_REG_ISAPNPCFG2
mdefine_line|#define HP100_REG_ISAPNPCFG2    0x1b    /* RW: (8) ISA PnP Cfg/Cntrl Reg 2 */
multiline_comment|/*  Page 3 - EEPROM/Boot ROM  */
DECL|macro|HP100_REG_EEPROM_CTRL
mdefine_line|#define HP100_REG_EEPROM_CTRL&t;0x08&t;/* RW: (16) Used to load EEPROM      */
DECL|macro|HP100_REG_BOOTROM_CTRL
mdefine_line|#define HP100_REG_BOOTROM_CTRL  0x0a
multiline_comment|/*  Page 4 - LAN Configuration  (MAC_CTRL) */
DECL|macro|HP100_REG_10_LAN_CFG_1
mdefine_line|#define HP100_REG_10_LAN_CFG_1&t;0x08&t;/* RW: (8) Set 10M XCVR functions   */
DECL|macro|HP100_REG_10_LAN_CFG_2
mdefine_line|#define HP100_REG_10_LAN_CFG_2  0x09    /* RW: (8)     10M XCVR functions   */
DECL|macro|HP100_REG_VG_LAN_CFG_1
mdefine_line|#define HP100_REG_VG_LAN_CFG_1&t;0x0a&t;/* RW: (8) Set 100M XCVR functions  */
DECL|macro|HP100_REG_VG_LAN_CFG_2
mdefine_line|#define HP100_REG_VG_LAN_CFG_2  0x0b    /* RW: (8) 100M LAN Training cfgregs */
DECL|macro|HP100_REG_MAC_CFG_1
mdefine_line|#define HP100_REG_MAC_CFG_1&t;0x0c&t;/* RW: (8) Types of pkts to accept   */
DECL|macro|HP100_REG_MAC_CFG_2
mdefine_line|#define HP100_REG_MAC_CFG_2&t;0x0d&t;/* RW: (8) Misc MAC functions        */
DECL|macro|HP100_REG_MAC_CFG_3
mdefine_line|#define HP100_REG_MAC_CFG_3     0x0e    /* RW: (8) Misc MAC functions */
DECL|macro|HP100_REG_MAC_CFG_4
mdefine_line|#define HP100_REG_MAC_CFG_4     0x0f    /* R:  (8) Misc MAC states */
DECL|macro|HP100_REG_DROPPED
mdefine_line|#define HP100_REG_DROPPED&t;0x10&t;/* R:  (16),11:0 Pkts cant fit in mem*/
DECL|macro|HP100_REG_CRC
mdefine_line|#define HP100_REG_CRC&t;&t;0x12&t;/* R:  (8) Pkts with CRC             */
DECL|macro|HP100_REG_ABORT
mdefine_line|#define HP100_REG_ABORT&t;&t;0x13&t;/* R:  (8) Aborted Tx pkts           */
DECL|macro|HP100_REG_TRAIN_REQUEST
mdefine_line|#define HP100_REG_TRAIN_REQUEST 0x14    /* RW: (16) Endnode MAC register.*/
DECL|macro|HP100_REG_TRAIN_ALLOW
mdefine_line|#define HP100_REG_TRAIN_ALLOW   0x16    /* R:  (16) Hub allowed register */
multiline_comment|/*  Page 5 - MMU  */
DECL|macro|HP100_REG_RX_MEM_STOP
mdefine_line|#define HP100_REG_RX_MEM_STOP&t;0x0c&t;/* RW: (16) End of Rx ring addr      */
DECL|macro|HP100_REG_TX_MEM_STOP
mdefine_line|#define HP100_REG_TX_MEM_STOP&t;0x0e&t;/* RW: (16) End of Tx ring addr      */
DECL|macro|HP100_REG_PDL_MEM_STOP
mdefine_line|#define HP100_REG_PDL_MEM_STOP  0x10    /* Not used by 802.12 devices */
DECL|macro|HP100_REG_ECB_MEM_STOP
mdefine_line|#define HP100_REG_ECB_MEM_STOP  0x14    /* I&squot;ve no idea what this is */
multiline_comment|/*  Page 6 - Card ID/Physical LAN Address  */
DECL|macro|HP100_REG_BOARD_ID
mdefine_line|#define HP100_REG_BOARD_ID&t;0x08&t;/* R:  (8) EISA/ISA card ID          */
DECL|macro|HP100_REG_BOARD_IO_CHCK
mdefine_line|#define HP100_REG_BOARD_IO_CHCK 0x0c&t;/* R:  (8) Added to ID to get FFh    */
DECL|macro|HP100_REG_SOFT_MODEL
mdefine_line|#define HP100_REG_SOFT_MODEL&t;0x0d&t;/* R:  (8) Config program defined    */
DECL|macro|HP100_REG_LAN_ADDR
mdefine_line|#define HP100_REG_LAN_ADDR&t;0x10&t;/* R:  (8) MAC addr of card          */
DECL|macro|HP100_REG_LAN_ADDR_CHCK
mdefine_line|#define HP100_REG_LAN_ADDR_CHCK 0x16&t;/* R:  (8) Added to addr to get FFh  */
multiline_comment|/*  Page 7 - MMU Current Pointers  */
DECL|macro|HP100_REG_PTR_RXSTART
mdefine_line|#define HP100_REG_PTR_RXSTART&t;0x08&t;/* R:  (16) Current begin of Rx ring */
DECL|macro|HP100_REG_PTR_RXEND
mdefine_line|#define HP100_REG_PTR_RXEND&t;0x0a&t;/* R:  (16) Current end of Rx ring   */
DECL|macro|HP100_REG_PTR_TXSTART
mdefine_line|#define HP100_REG_PTR_TXSTART&t;0x0c&t;/* R:  (16) Current begin of Tx ring */
DECL|macro|HP100_REG_PTR_TXEND
mdefine_line|#define HP100_REG_PTR_TXEND&t;0x0e&t;/* R:  (16) Current end of Rx ring   */
DECL|macro|HP100_REG_PTR_RPDLSTART
mdefine_line|#define HP100_REG_PTR_RPDLSTART 0x10
DECL|macro|HP100_REG_PTR_RPDLEND
mdefine_line|#define HP100_REG_PTR_RPDLEND   0x12
DECL|macro|HP100_REG_PTR_RINGPTRS
mdefine_line|#define HP100_REG_PTR_RINGPTRS  0x14
DECL|macro|HP100_REG_PTR_MEMDEBUG
mdefine_line|#define HP100_REG_PTR_MEMDEBUG  0x1a
multiline_comment|/* ------------------------------------------------------------------------ */
multiline_comment|/* &n; * Hardware ID Register I (Always available, HW_ID, Offset 0x00)&n; */
DECL|macro|HP100_HW_ID_CASCADE
mdefine_line|#define HP100_HW_ID_CASCADE     0x4850  /* Identifies Cascade Chip */
multiline_comment|/* &n; * Hardware ID Register 2 &amp; Paging Register&n; * (Always available, PAGING, Offset 0x02)&n; * Bits 15:4 are for the Chip ID &n; */
DECL|macro|HP100_CHIPID_MASK
mdefine_line|#define HP100_CHIPID_MASK        0xFFF0
DECL|macro|HP100_CHIPID_SHASTA
mdefine_line|#define HP100_CHIPID_SHASTA      0x5350  /* Not 802.12 compliant */
multiline_comment|/* EISA BM/SL, MCA16/32 SL, ISA SL */
DECL|macro|HP100_CHIPID_RAINIER
mdefine_line|#define HP100_CHIPID_RAINIER     0x5360  /* Not 802.12 compliant EISA BM,*/
multiline_comment|/* PCI SL, MCA16/32 SL, ISA SL */
DECL|macro|HP100_CHIPID_LASSEN
mdefine_line|#define HP100_CHIPID_LASSEN      0x5370  /* 802.12 compliant PCI BM, PCI SL */
multiline_comment|/* LRF supported */
multiline_comment|/*&n; *  Option Registers I and II &n; * (Always available, OPTION_LSW, Offset 0x04-0x05)&n; */
DECL|macro|HP100_DEBUG_EN
mdefine_line|#define HP100_DEBUG_EN&t;&t;0x8000&t;/* 0:Dis., 1:Enable Debug Dump Ptr. */
DECL|macro|HP100_RX_HDR
mdefine_line|#define HP100_RX_HDR&t;&t;0x4000&t;/* 0:Dis., 1:Enable putting pkt into */
multiline_comment|/*   system mem. before Rx interrupt */
DECL|macro|HP100_MMAP_DIS
mdefine_line|#define HP100_MMAP_DIS&t;&t;0x2000&t;/* 0:Enable, 1:Disable mem.mapping. */
multiline_comment|/*   MMAP_DIS must be 0 and MEM_EN */
multiline_comment|/*   must be 1 for memory-mapped */
multiline_comment|/*   mode to be enabled */
DECL|macro|HP100_EE_EN
mdefine_line|#define HP100_EE_EN&t;&t;0x1000&t;/* 0:Disable,1:Enable EEPROM writing */
DECL|macro|HP100_BM_WRITE
mdefine_line|#define HP100_BM_WRITE&t;&t;0x0800&t;/* 0:Slave, 1:Bus Master for Tx data */
DECL|macro|HP100_BM_READ
mdefine_line|#define HP100_BM_READ&t;&t;0x0400&t;/* 0:Slave, 1:Bus Master for Rx data */
DECL|macro|HP100_TRI_INT
mdefine_line|#define HP100_TRI_INT&t;&t;0x0200&t;/* 0:Don&squot;t, 1:Do tri-state the int */
DECL|macro|HP100_MEM_EN
mdefine_line|#define HP100_MEM_EN&t;&t;0x0040&t;/* Config program set this to */
multiline_comment|/*   0:Disable, 1:Enable mem map. */
multiline_comment|/*   See MMAP_DIS. */
DECL|macro|HP100_IO_EN
mdefine_line|#define HP100_IO_EN&t;&t;0x0020&t;/* 1:Enable I/O transfers */
DECL|macro|HP100_BOOT_EN
mdefine_line|#define HP100_BOOT_EN&t;&t;0x0010&t;/* 1:Enable boot ROM access */
DECL|macro|HP100_FAKE_INT
mdefine_line|#define HP100_FAKE_INT&t;&t;0x0008&t;/* 1:int */
DECL|macro|HP100_INT_EN
mdefine_line|#define HP100_INT_EN&t;&t;0x0004&t;/* 1:Enable ints from card */
DECL|macro|HP100_HW_RST
mdefine_line|#define HP100_HW_RST&t;&t;0x0002&t;/* 0:Reset, 1:Out of reset */
multiline_comment|/* NIC reset on 0 to 1 transition */
multiline_comment|/*&n; *  Option Register III &n; * (Always available, OPTION_MSW, Offset 0x06)&n; */
DECL|macro|HP100_PRIORITY_TX
mdefine_line|#define HP100_PRIORITY_TX&t;0x0080&t;/* 1:Do all Tx pkts as priority */
DECL|macro|HP100_EE_LOAD
mdefine_line|#define HP100_EE_LOAD&t;&t;0x0040&t;/* 1:EEPROM loading, 0 when done */
DECL|macro|HP100_ADV_NXT_PKT
mdefine_line|#define HP100_ADV_NXT_PKT&t;0x0004&t;/* 1:Advance to next pkt in Rx queue */
multiline_comment|/*   h/w will set to 0 when done */
DECL|macro|HP100_TX_CMD
mdefine_line|#define HP100_TX_CMD&t;&t;0x0002&t;/* 1:Tell h/w download done, h/w */
multiline_comment|/*   will set to 0 when done */
multiline_comment|/*&n; * Interrupt Status Registers I and II&n; * (Page PERFORMANCE, IRQ_STATUS, Offset 0x08-0x09)&n; * Note: With old chips, these Registers will clear when 1 is written to them&n; *       with new chips this depends on setting of CLR_ISMODE&n; */
DECL|macro|HP100_RX_EARLY_INT
mdefine_line|#define HP100_RX_EARLY_INT      0x2000
DECL|macro|HP100_RX_PDA_ZERO
mdefine_line|#define HP100_RX_PDA_ZERO       0x1000
DECL|macro|HP100_RX_PDL_FILL_COMPL
mdefine_line|#define HP100_RX_PDL_FILL_COMPL 0x0800
DECL|macro|HP100_RX_PACKET
mdefine_line|#define HP100_RX_PACKET&t;&t;0x0400&t;/* 0:No, 1:Yes pkt has been Rx */
DECL|macro|HP100_RX_ERROR
mdefine_line|#define HP100_RX_ERROR&t;&t;0x0200&t;/* 0:No, 1:Yes Rx pkt had error */
DECL|macro|HP100_TX_PDA_ZERO
mdefine_line|#define HP100_TX_PDA_ZERO       0x0020  /* 1 when PDA count goes to zero */
DECL|macro|HP100_TX_SPACE_AVAIL
mdefine_line|#define HP100_TX_SPACE_AVAIL&t;0x0010&t;/* 0:&lt;8192, 1:&gt;=8192 Tx free bytes */
DECL|macro|HP100_TX_COMPLETE
mdefine_line|#define HP100_TX_COMPLETE&t;0x0008&t;/* 0:No, 1:Yes a Tx has completed */
DECL|macro|HP100_MISC_ERROR
mdefine_line|#define HP100_MISC_ERROR        0x0004  /* 0:No, 1:Lan Link down or bus error*/
DECL|macro|HP100_TX_ERROR
mdefine_line|#define HP100_TX_ERROR&t;&t;0x0002&t;/* 0:No, 1:Yes Tx pkt had error */
multiline_comment|/*&n; * Xmit Memory Free Count&n; * (Page PERFORMANCE, TX_MEM_FREE, Offset 0x14) (Read only, 32bit)&n; */
DECL|macro|HP100_AUTO_COMPARE
mdefine_line|#define HP100_AUTO_COMPARE&t;0x80000000&t;/* Tx Space avail &amp; pkts&lt;255 */
DECL|macro|HP100_FREE_SPACE
mdefine_line|#define HP100_FREE_SPACE&t;0x7fffffe0&t;/* Tx free memory */
multiline_comment|/*&n; *  IRQ Channel&n; * (Page HW_MAP, IRQ_CHANNEL, Offset 0x0d)&n; */
DECL|macro|HP100_ZERO_WAIT_EN
mdefine_line|#define HP100_ZERO_WAIT_EN&t;0x80&t;/* 0:No, 1:Yes asserts NOWS signal */
DECL|macro|HP100_IRQ_SCRAMBLE
mdefine_line|#define HP100_IRQ_SCRAMBLE      0x40
DECL|macro|HP100_BOND_HP
mdefine_line|#define HP100_BOND_HP           0x20
DECL|macro|HP100_LEVEL_IRQ
mdefine_line|#define HP100_LEVEL_IRQ&t;&t;0x10&t;/* 0:Edge, 1:Level type interrupts. */
multiline_comment|/* (Only valid on EISA cards) */
DECL|macro|HP100_IRQMASK
mdefine_line|#define HP100_IRQMASK&t;&t;0x0F&t;/* Isolate the IRQ bits */
multiline_comment|/*&n; * SRAM Parameters&n; * (Page HW_MAP, SRAM, Offset 0x0e)&n; */
DECL|macro|HP100_RAM_SIZE_MASK
mdefine_line|#define HP100_RAM_SIZE_MASK&t;0xe0&t;/* AND to get SRAM size index */
DECL|macro|HP100_RAM_SIZE_SHIFT
mdefine_line|#define HP100_RAM_SIZE_SHIFT&t;0x05&t;/* Shift count(put index in lwr bits)*/
multiline_comment|/*&n; * Bus Master Register&n; * (Page HW_MAP, BM, Offset 0x0f)&n; */
DECL|macro|HP100_BM_BURST_RD
mdefine_line|#define HP100_BM_BURST_RD       0x01    /* EISA only: 1=Use burst trans. fm system */
multiline_comment|/* memory to chip (tx) */
DECL|macro|HP100_BM_BURST_WR
mdefine_line|#define HP100_BM_BURST_WR       0x02    /* EISA only: 1=Use burst trans. fm system */
multiline_comment|/* memory to chip (rx) */
DECL|macro|HP100_BM_MASTER
mdefine_line|#define HP100_BM_MASTER&t;&t;0x04&t;/* 0:Slave, 1:BM mode */
DECL|macro|HP100_BM_PAGE_CK
mdefine_line|#define HP100_BM_PAGE_CK        0x08    /* This bit should be set whenever in*/
multiline_comment|/* an EISA system */
DECL|macro|HP100_BM_PCI_8CLK
mdefine_line|#define HP100_BM_PCI_8CLK       0x40    /* ... cycles 8 clocks apart */
multiline_comment|/* &n; * Mode Control Register I&n; * (Page HW_MAP, MODECTRL1, Offset0x10)&n; */
DECL|macro|HP100_TX_DUALQ
mdefine_line|#define HP100_TX_DUALQ          0x10
multiline_comment|/* If set and BM -&gt; dual tx pda queues*/
DECL|macro|HP100_ISR_CLRMODE
mdefine_line|#define HP100_ISR_CLRMODE       0x02   /* If set ISR will clear all pending */
multiline_comment|/* interrupts on read (etr only?) */
DECL|macro|HP100_EE_NOLOAD
mdefine_line|#define HP100_EE_NOLOAD         0x04   /* Status whether res will be loaded */
multiline_comment|/* from the eeprom */
DECL|macro|HP100_TX_CNT_FLG
mdefine_line|#define HP100_TX_CNT_FLG        0x08   /* Controls Early TX Reg Cnt Field */
DECL|macro|HP100_PDL_USE3
mdefine_line|#define HP100_PDL_USE3          0x10   /* If set BM engine will read only */
multiline_comment|/* first three data elements of a PDL */
multiline_comment|/* on the first access. */
DECL|macro|HP100_BUSTYPE_MASK
mdefine_line|#define HP100_BUSTYPE_MASK      0xe0   /* Three bit bus type info */
multiline_comment|/*&n; * Mode Control Register II&n; * (Page HW_MAP, MODECTRL2, Offset0x11)&n; */
DECL|macro|HP100_EE_MASK
mdefine_line|#define HP100_EE_MASK           0x0f   /* Tell EEPROM circuit not to load */ 
multiline_comment|/* certain resources */
DECL|macro|HP100_DIS_CANCEL
mdefine_line|#define HP100_DIS_CANCEL        0x20   /* For tx dualq mode operation */
DECL|macro|HP100_EN_PDL_WB
mdefine_line|#define HP100_EN_PDL_WB         0x40   /* 1: Status of PDL completion may be */
multiline_comment|/* written back to system mem */
DECL|macro|HP100_EN_BUS_FAIL
mdefine_line|#define HP100_EN_BUS_FAIL       0x80   /* Enables bus-fail portion of misc */
multiline_comment|/* interrupt */
multiline_comment|/* &n; * PCI Configuration and Control Register I&n; * (Page HW_MAP, PCICTRL1, Offset 0x12)&n; */
DECL|macro|HP100_LO_MEM
mdefine_line|#define HP100_LO_MEM            0x01   /* 1: Mapped Mem requested below 1MB */
DECL|macro|HP100_NO_MEM
mdefine_line|#define HP100_NO_MEM            0x02   /* 1: Disables Req for sysmem to PCI */ 
multiline_comment|/* bios */
DECL|macro|HP100_USE_ISA
mdefine_line|#define HP100_USE_ISA           0x04   /* 1: isa type decodes will occur */
multiline_comment|/* simultaneously with PCI decodes */
DECL|macro|HP100_IRQ_HI_MASK
mdefine_line|#define HP100_IRQ_HI_MASK       0xf0   /* pgmed by pci bios */
DECL|macro|HP100_PCI_IRQ_HI_MASK
mdefine_line|#define HP100_PCI_IRQ_HI_MASK   0x78    /* Isolate 4 bits for PCI IRQ  */
multiline_comment|/*&n; * PCI Configuration and Control Register II&n; * (Page HW_MAP, PCICTRL2, Offset 0x13)&n; */
DECL|macro|HP100_RD_LINE_PDL
mdefine_line|#define HP100_RD_LINE_PDL       0x01   /* 1: PCI command Memory Read Line en */
DECL|macro|HP100_RD_TX_DATA_MASK
mdefine_line|#define HP100_RD_TX_DATA_MASK   0x06   /* choose PCI memread cmds for TX */ 
DECL|macro|HP100_MWI
mdefine_line|#define HP100_MWI               0x08   /* 1: en. PCI memory write invalidate */
DECL|macro|HP100_ARB_MODE
mdefine_line|#define HP100_ARB_MODE          0x10   /* Select PCI arbitor type */
DECL|macro|HP100_STOP_EN
mdefine_line|#define HP100_STOP_EN           0x20   /* Enables PCI state machine to issue */
multiline_comment|/* pci stop if cascade not ready */
DECL|macro|HP100_IGNORE_PAR
mdefine_line|#define HP100_IGNORE_PAR        0x40   /* 1: PCI state machine ignores parity*/
DECL|macro|HP100_PCI_RESET
mdefine_line|#define HP100_PCI_RESET         0x80   /* 0-&gt;1: Reset PCI block */
multiline_comment|/*&n; * Early TX Configuration and Control Register&n; * (Page HW_MAP, EARLYTXCFG, Offset 0x16)&n; */
DECL|macro|HP100_EN_EARLY_TX
mdefine_line|#define HP100_EN_EARLY_TX       0x8000  /* 1=Enable Early TX */
DECL|macro|HP100_EN_ADAPTIVE
mdefine_line|#define HP100_EN_ADAPTIVE       0x4000  /* 1=Enable adaptive mode */
DECL|macro|HP100_EN_TX_UR_IRQ
mdefine_line|#define HP100_EN_TX_UR_IRQ      0x2000  /* reserved, must be 0 */
DECL|macro|HP100_EN_LOW_TX
mdefine_line|#define HP100_EN_LOW_TX         0x1000  /* reserved, must be 0 */
DECL|macro|HP100_ET_CNT_MASK
mdefine_line|#define HP100_ET_CNT_MASK       0x0fff  /* bits 11..0: ET counters */
multiline_comment|/*&n; * Early RX Configuration and Control Register&n; * (Page HW_MAP, EARLYRXCFG, Offset 0x18)&n; */
DECL|macro|HP100_EN_EARLY_RX
mdefine_line|#define HP100_EN_EARLY_RX       0x80     /* 1=Enable Early RX */
DECL|macro|HP100_EN_LOW_RX
mdefine_line|#define HP100_EN_LOW_RX         0x40     /* reserved, must be 0 */
DECL|macro|HP100_RX_TRIP_MASK
mdefine_line|#define HP100_RX_TRIP_MASK      0x1f     /* bits 4..0: threshold at which the&n;&t;&t;&t;&t;&t;  * early rx circuit will start the&n;&t;&t;&t;&t;&t;  * dma of received packet into system&n;&t;&t;&t;&t;&t;  * memory for BM */
multiline_comment|/*&n; *  Serial Devices Control Register&n; * (Page EEPROM_CTRL, EEPROM_CTRL, Offset 0x08)&n; */
DECL|macro|HP100_EEPROM_LOAD
mdefine_line|#define HP100_EEPROM_LOAD&t;0x0001&t;/* 0-&gt;1 loads EEPROM into registers. */
multiline_comment|/* When it goes back to 0, load is   */
multiline_comment|/* complete. This should take ~600us.*/
multiline_comment|/*&n; * 10MB LAN Control and Configuration Register I&n; * (Page MAC_CTRL, 10_LAN_CFG_1, Offset 0x08)&n; */
DECL|macro|HP100_MAC10_SEL
mdefine_line|#define HP100_MAC10_SEL&t;&t;0xc0&t;/* Get bits to indicate MAC */
DECL|macro|HP100_AUI_SEL
mdefine_line|#define HP100_AUI_SEL&t;&t;0x20&t;/* Status of AUI selection */
DECL|macro|HP100_LOW_TH
mdefine_line|#define HP100_LOW_TH&t;&t;0x10&t;/* 0:No, 1:Yes allow better cabling */
DECL|macro|HP100_LINK_BEAT_DIS
mdefine_line|#define HP100_LINK_BEAT_DIS&t;0x08&t;/* 0:Enable, 1:Disable link beat */
DECL|macro|HP100_LINK_BEAT_ST
mdefine_line|#define HP100_LINK_BEAT_ST&t;0x04&t;/* 0:No, 1:Yes link beat being Rx */
DECL|macro|HP100_R_ROL_ST
mdefine_line|#define HP100_R_ROL_ST&t;&t;0x02&t;/* 0:No, 1:Yes Rx twisted pair has */
multiline_comment|/*             been reversed */
DECL|macro|HP100_AUI_ST
mdefine_line|#define HP100_AUI_ST&t;&t;0x01&t;/* 0:No, 1:Yes use AUI on TP card */
multiline_comment|/*&n; * 10 MB LAN Control and Configuration Register II&n; * (Page MAC_CTRL, 10_LAN_CFG_2, Offset 0x09)&n; */
DECL|macro|HP100_SQU_ST
mdefine_line|#define HP100_SQU_ST&t;&t;0x01&t;/* 0:No, 1:Yes collision signal sent */
multiline_comment|/*       after Tx.Only used for AUI. */
DECL|macro|HP100_FULLDUP
mdefine_line|#define HP100_FULLDUP           0x02    /* 1: LXT901 XCVR fullduplx enabled */
DECL|macro|HP100_DOT3_MAC
mdefine_line|#define HP100_DOT3_MAC          0x04    /* 1: DOT 3 Mac sel. unless Autosel */
multiline_comment|/*&n; * MAC Selection, use with MAC10_SEL bits&n; */
DECL|macro|HP100_AUTO_SEL_10
mdefine_line|#define HP100_AUTO_SEL_10&t;0x0&t;/* Auto select */
DECL|macro|HP100_XCVR_LXT901_10
mdefine_line|#define HP100_XCVR_LXT901_10&t;0x1&t;/* LXT901 10BaseT transceiver */
DECL|macro|HP100_XCVR_7213
mdefine_line|#define HP100_XCVR_7213&t;&t;0x2&t;/* 7213 transceiver */
DECL|macro|HP100_XCVR_82503
mdefine_line|#define HP100_XCVR_82503&t;0x3&t;/* 82503 transceiver */
multiline_comment|/*&n; *  100MB LAN Training Register&n; * (Page MAC_CTRL, VG_LAN_CFG_2, Offset 0x0b) (old, pre 802.12)&n; */
DECL|macro|HP100_FRAME_FORMAT
mdefine_line|#define HP100_FRAME_FORMAT&t;0x08&t;/* 0:802.3, 1:802.5 frames */
DECL|macro|HP100_BRIDGE
mdefine_line|#define HP100_BRIDGE&t;&t;0x04&t;/* 0:No, 1:Yes tell hub i am a bridge */
DECL|macro|HP100_PROM_MODE
mdefine_line|#define HP100_PROM_MODE&t;&t;0x02&t;/* 0:No, 1:Yes tell hub card is */
multiline_comment|/*         promiscuous */
DECL|macro|HP100_REPEATER
mdefine_line|#define HP100_REPEATER&t;&t;0x01&t;/* 0:No, 1:Yes tell hub MAC wants to */
multiline_comment|/*         be a cascaded repeater */
multiline_comment|/*&n; * 100MB LAN Control and Configuration Register&n; * (Page MAC_CTRL, VG_LAN_CFG_1, Offset 0x0a) &n; */
DECL|macro|HP100_VG_SEL
mdefine_line|#define HP100_VG_SEL&t;        0x80&t;/* 0:No, 1:Yes use 100 Mbit MAC */
DECL|macro|HP100_LINK_UP_ST
mdefine_line|#define HP100_LINK_UP_ST&t;0x40&t;/* 0:No, 1:Yes endnode logged in */
DECL|macro|HP100_LINK_CABLE_ST
mdefine_line|#define HP100_LINK_CABLE_ST&t;0x20&t;/* 0:No, 1:Yes cable can hear tones */
multiline_comment|/*         from  hub */
DECL|macro|HP100_LOAD_ADDR
mdefine_line|#define HP100_LOAD_ADDR&t;&t;0x10&t;/* 0-&gt;1 card addr will be sent  */
multiline_comment|/* 100ms later the link status  */
multiline_comment|/* bits are valid */
DECL|macro|HP100_LINK_CMD
mdefine_line|#define HP100_LINK_CMD&t;&t;0x08&t;/* 0-&gt;1 link will attempt to log in. */
multiline_comment|/* 100ms later the link status */
multiline_comment|/* bits are valid */
DECL|macro|HP100_TRN_DONE
mdefine_line|#define HP100_TRN_DONE          0x04    /* NEW ETR-Chips only: Will be reset */
multiline_comment|/* after LinkUp Cmd is given and set */
multiline_comment|/* when training has completed. */
DECL|macro|HP100_LINK_GOOD_ST
mdefine_line|#define HP100_LINK_GOOD_ST&t;0x02&t;/* 0:No, 1:Yes cable passed training */
DECL|macro|HP100_VG_RESET
mdefine_line|#define HP100_VG_RESET&t;&t;0x01&t;/* 0:Yes, 1:No reset the 100VG MAC */
multiline_comment|/*&n; *  MAC Configuration Register I&n; * (Page MAC_CTRL, MAC_CFG_1, Offset 0x0c)&n; */
DECL|macro|HP100_RX_IDLE
mdefine_line|#define HP100_RX_IDLE&t;&t;0x80&t;/* 0:Yes, 1:No currently receiving pkts */
DECL|macro|HP100_TX_IDLE
mdefine_line|#define HP100_TX_IDLE&t;&t;0x40&t;/* 0:Yes, 1:No currently Txing pkts */
DECL|macro|HP100_RX_EN
mdefine_line|#define HP100_RX_EN&t;&t;0x20&t;/* 1: allow receiving of pkts */
DECL|macro|HP100_TX_EN
mdefine_line|#define HP100_TX_EN&t;&t;0x10&t;/* 1: allow transmitting of pkts */
DECL|macro|HP100_ACC_ERRORED
mdefine_line|#define HP100_ACC_ERRORED&t;0x08&t;/* 0:No, 1:Yes allow Rx of errored pkts */
DECL|macro|HP100_ACC_MC
mdefine_line|#define HP100_ACC_MC&t;&t;0x04&t;/* 0:No, 1:Yes allow Rx of multicast pkts */
DECL|macro|HP100_ACC_BC
mdefine_line|#define HP100_ACC_BC&t;&t;0x02&t;/* 0:No, 1:Yes allow Rx of broadcast pkts */
DECL|macro|HP100_ACC_PHY
mdefine_line|#define HP100_ACC_PHY&t;&t;0x01&t;/* 0:No, 1:Yes allow Rx of ALL phys. pkts */
DECL|macro|HP100_MAC1MODEMASK
mdefine_line|#define HP100_MAC1MODEMASK&t;0xf0&t;/* Hide ACC bits */
DECL|macro|HP100_MAC1MODE1
mdefine_line|#define HP100_MAC1MODE1&t;&t;0x00&t;/* Receive nothing, must also disable RX */
DECL|macro|HP100_MAC1MODE2
mdefine_line|#define HP100_MAC1MODE2&t;&t;0x00
DECL|macro|HP100_MAC1MODE3
mdefine_line|#define HP100_MAC1MODE3&t;&t;HP100_MAC1MODE2 | HP100_ACC_BC
DECL|macro|HP100_MAC1MODE4
mdefine_line|#define HP100_MAC1MODE4&t;&t;HP100_MAC1MODE3 | HP100_ACC_MC
DECL|macro|HP100_MAC1MODE5
mdefine_line|#define HP100_MAC1MODE5&t;&t;HP100_MAC1MODE4 /* set mc hash to all ones also */
DECL|macro|HP100_MAC1MODE6
mdefine_line|#define HP100_MAC1MODE6&t;&t;HP100_MAC1MODE5 | HP100_ACC_PHY&t;/* Promiscuous */
multiline_comment|/* Note MODE6 will receive all GOOD packets on the LAN. This really needs&n;   a mode 7 defined to be LAN Analyzer mode, which will receive errored and&n;   runt packets, and keep the CRC bytes. */
DECL|macro|HP100_MAC1MODE7
mdefine_line|#define HP100_MAC1MODE7&t;&t;HP100_MAC1MODE6 | HP100_ACC_ERRORED
multiline_comment|/*&n; *  MAC Configuration Register II &n; * (Page MAC_CTRL, MAC_CFG_2, Offset 0x0d)&n; */
DECL|macro|HP100_TR_MODE
mdefine_line|#define HP100_TR_MODE&t;&t;0x80&t;/* 0:No, 1:Yes support Token Ring formats */
DECL|macro|HP100_TX_SAME
mdefine_line|#define HP100_TX_SAME&t;&t;0x40&t;/* 0:No, 1:Yes Tx same packet continuous */
DECL|macro|HP100_LBK_XCVR
mdefine_line|#define HP100_LBK_XCVR&t;&t;0x20&t;/* 0:No, 1:Yes loopback through MAC &amp; */
multiline_comment|/*   transceiver */
DECL|macro|HP100_LBK_MAC
mdefine_line|#define HP100_LBK_MAC&t;&t;0x10&t;/* 0:No, 1:Yes loopback through MAC */
DECL|macro|HP100_CRC_I
mdefine_line|#define HP100_CRC_I&t;&t;0x08&t;/* 0:No, 1:Yes inhibit CRC on Tx packets */
DECL|macro|HP100_ACCNA
mdefine_line|#define HP100_ACCNA             0x04    /* 1: For 802.5: Accept only token ring&n;&t;&t;&t;&t;&t; * group addr that maches NA mask */
DECL|macro|HP100_KEEP_CRC
mdefine_line|#define HP100_KEEP_CRC&t;&t;0x02&t;/* 0:No, 1:Yes keep CRC on Rx packets. */
multiline_comment|/*   The length will reflect this. */
DECL|macro|HP100_ACCFA
mdefine_line|#define HP100_ACCFA             0x01    /* 1: For 802.5: Accept only functional&n;&t;&t;&t;&t;&t; * addrs that match FA mask (page1) */
DECL|macro|HP100_MAC2MODEMASK
mdefine_line|#define HP100_MAC2MODEMASK&t;0x02
DECL|macro|HP100_MAC2MODE1
mdefine_line|#define HP100_MAC2MODE1&t;&t;0x00
DECL|macro|HP100_MAC2MODE2
mdefine_line|#define HP100_MAC2MODE2&t;&t;0x00
DECL|macro|HP100_MAC2MODE3
mdefine_line|#define HP100_MAC2MODE3&t;&t;0x00
DECL|macro|HP100_MAC2MODE4
mdefine_line|#define HP100_MAC2MODE4&t;&t;0x00
DECL|macro|HP100_MAC2MODE5
mdefine_line|#define HP100_MAC2MODE5&t;&t;0x00
DECL|macro|HP100_MAC2MODE6
mdefine_line|#define HP100_MAC2MODE6&t;&t;0x00
DECL|macro|HP100_MAC2MODE7
mdefine_line|#define HP100_MAC2MODE7&t;&t;KEEP_CRC
multiline_comment|/*&n; * MAC Configuration Register III &n; * (Page MAC_CTRL, MAC_CFG_3, Offset 0x0e) &n; */
DECL|macro|HP100_PACKET_PACE
mdefine_line|#define HP100_PACKET_PACE       0x03     /* Packet Pacing:&n;&t;&t;&t;&t;&t;  * 00: No packet pacing&n;                                          * 01: 8 to 16 uS delay&n;                                          * 10: 16 to 32 uS delay&n;                                          * 11: 32 to 64 uS delay&n;&t;&t;&t;&t;&t;  */
DECL|macro|HP100_LRF_EN
mdefine_line|#define HP100_LRF_EN            0x04     /* 1: External LAN Rcv Filter and&n;&t;&t;&t;&t;&t;  * TCP/IP Checksumming enabled. */
DECL|macro|HP100_AUTO_MODE
mdefine_line|#define HP100_AUTO_MODE         0x10     /* 1: AutoSelect between 10/100 */
multiline_comment|/*&n; * MAC Configuration Register IV &n; * (Page MAC_CTRL, MAC_CFG_4, Offset 0x0f)&n; */
DECL|macro|HP100_MAC_SEL_ST
mdefine_line|#define HP100_MAC_SEL_ST        0x01      /* (R): Status of external VGSEL&n;&t;&t;&t;&t;&t;   * Signal, 1=100VG, 0=10Mbit sel. */
DECL|macro|HP100_LINK_FAIL_ST
mdefine_line|#define HP100_LINK_FAIL_ST      0x02      /* (R): Status of Link Fail portion&n;                                           * of the Misc. Interrupt */
multiline_comment|/* &n; *  100 MB LAN Training Request/Allowed Registers &n; * (Page MAC_CTRL, TRAIN_REQUEST and TRAIN_ALLOW, Offset 0x14-0x16)(ETR parts only)&n; */
DECL|macro|HP100_MACRQ_REPEATER
mdefine_line|#define HP100_MACRQ_REPEATER         0x0001  /* 1: MAC tells HUB it wants to be &n;&t;&t;&t;&t;              *    a cascaded repeater&n;&t;&t;&t;&t;&t;      * 0: ... wants to be a DTE */
DECL|macro|HP100_MACRQ_PROMSC
mdefine_line|#define HP100_MACRQ_PROMSC           0x0006  /* 2 bits: Promiscious mode&n;&t;&t;&t;&t;&t;      * 00: Rcv only unicast packets&n;&t;&t;&t;&t;&t;      *     specifically addr to this&n;&t;&t;&t;&t;&t;      *     endnode&n;&t;&t;&t;&t;&t;      * 10: Rcv all pckts fwded by &n;&t;&t;&t;&t;&t;      *     the local repeater */
DECL|macro|HP100_MACRQ_FRAMEFMT_EITHER
mdefine_line|#define HP100_MACRQ_FRAMEFMT_EITHER  0x0018  /* 11: either format allowed */
DECL|macro|HP100_MACRQ_FRAMEFMT_802_3
mdefine_line|#define HP100_MACRQ_FRAMEFMT_802_3   0x0000  /* 00: 802.3 is requested */
DECL|macro|HP100_MACRQ_FRAMEFMT_802_5
mdefine_line|#define HP100_MACRQ_FRAMEFMT_802_5   0x0010  /* 10: 802.5 format is requested */
DECL|macro|HP100_CARD_MACVER
mdefine_line|#define HP100_CARD_MACVER            0xe000  /* R: 3 bit Cards 100VG MAC version */
DECL|macro|HP100_MALLOW_REPEATER
mdefine_line|#define HP100_MALLOW_REPEATER        0x0001  /* If reset, requested access as an&n;&t;&t;&t;&t;&t;      * end node is allowed */
DECL|macro|HP100_MALLOW_PROMSC
mdefine_line|#define HP100_MALLOW_PROMSC          0x0004  /* 2 bits: Promiscious mode&n;&t;&t;&t;&t;&t;      * 00: Rcv only unicast packets&n;&t;&t;&t;&t;&t;      *     specifically addr to this&n;&t;&t;&t;&t;&t;      *     endnode&n;&t;&t;&t;&t;&t;      * 10: Rcv all pckts fwded by &n;&t;&t;&t;&t;&t;      *     the local repeater */
DECL|macro|HP100_MALLOW_FRAMEFMT
mdefine_line|#define HP100_MALLOW_FRAMEFMT        0x00e0  /* 2 bits: Frame Format&n;&t;&t;&t;&t;&t;      * 00: 802.3 format will be used&n;&t;&t;&t;&t;&t;      * 10: 802.5 format will be used */
DECL|macro|HP100_MALLOW_ACCDENIED
mdefine_line|#define HP100_MALLOW_ACCDENIED       0x0400  /* N bit */
DECL|macro|HP100_MALLOW_CONFIGURE
mdefine_line|#define HP100_MALLOW_CONFIGURE       0x0f00  /* C bit */
DECL|macro|HP100_MALLOW_DUPADDR
mdefine_line|#define HP100_MALLOW_DUPADDR         0x1000  /* D bit */
DECL|macro|HP100_HUB_MACVER
mdefine_line|#define HP100_HUB_MACVER             0xe000  /* R: 3 bit 802.12 MAC/RMAC training */
multiline_comment|/*    protocol of repeater */
multiline_comment|/* ****************************************************************************** */
multiline_comment|/*&n; *  Set/Reset bits&n; */
DECL|macro|HP100_SET_HB
mdefine_line|#define HP100_SET_HB&t;&t;0x0100&t;/* 0:Set fields to 0 whose mask is 1 */
DECL|macro|HP100_SET_LB
mdefine_line|#define HP100_SET_LB&t;&t;0x0001&t;/* HB sets upper byte, LB sets lower byte */
DECL|macro|HP100_RESET_HB
mdefine_line|#define HP100_RESET_HB&t;&t;0x0000&t;/* For readability when resetting bits */
DECL|macro|HP100_RESET_LB
mdefine_line|#define HP100_RESET_LB&t;&t;0x0000&t;/* For readability when resetting bits */
multiline_comment|/*&n; *  Misc. Constants&n; */
DECL|macro|HP100_LAN_100
mdefine_line|#define HP100_LAN_100&t;&t;100     /* lan_type value for VG */
DECL|macro|HP100_LAN_10
mdefine_line|#define HP100_LAN_10&t;&t;10&t;/* lan_type value for 10BaseT */
DECL|macro|HP100_LAN_ERR
mdefine_line|#define HP100_LAN_ERR&t;&t;(-1)&t;/* lan_type value for link down */
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
multiline_comment|/* &n; * Bus Master Data Structures  ----------------------------------------------&n; */
DECL|macro|MAX_RX_PDL
mdefine_line|#define MAX_RX_PDL              30   /* Card limit = 31 */
DECL|macro|MAX_RX_FRAG
mdefine_line|#define MAX_RX_FRAG             2    /* Don&squot;t need more... */
DECL|macro|MAX_TX_PDL
mdefine_line|#define MAX_TX_PDL              29
DECL|macro|MAX_TX_FRAG
mdefine_line|#define MAX_TX_FRAG             2   /* Limit = 31 */
multiline_comment|/* Define total PDL area size in bytes (should be 4096) */
multiline_comment|/* This is the size of kernel (dma) memory that will be allocated. */
DECL|macro|MAX_RINGSIZE
mdefine_line|#define MAX_RINGSIZE ((MAX_RX_FRAG*8+4+4)*MAX_RX_PDL+(MAX_TX_FRAG*8+4+4)*MAX_TX_PDL)+16
multiline_comment|/* Ethernet Packet Sizes */
DECL|macro|MIN_ETHER_SIZE
mdefine_line|#define MIN_ETHER_SIZE          60
DECL|macro|MAX_ETHER_SIZE
mdefine_line|#define MAX_ETHER_SIZE          1514    /* Needed for preallocation of */
multiline_comment|/* skb buffer when busmastering */
multiline_comment|/* Tx or Rx Ring Entry */
DECL|struct|hp100_ring
r_typedef
r_struct
id|hp100_ring
(brace
DECL|member|pdl
id|u_int
op_star
id|pdl
suffix:semicolon
multiline_comment|/* Address of PDLs PDH, dword before&n;&t;&t;&t;&t;&t; * this address is used for rx hdr */
DECL|member|pdl_paddr
id|u_int
id|pdl_paddr
suffix:semicolon
multiline_comment|/* Physical address of PDL */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|next
r_struct
id|hp100_ring
op_star
id|next
suffix:semicolon
DECL|typedef|hp100_ring_t
)brace
id|hp100_ring_t
suffix:semicolon
multiline_comment|/* Mask for Header Descriptor */
DECL|macro|HP100_PKT_LEN_MASK
mdefine_line|#define HP100_PKT_LEN_MASK&t;0x1FFF&t;/* AND with RxLength to get length */
multiline_comment|/* Receive Packet Status.  Note, the error bits are only valid if ACC_ERRORED &n;   bit in the MAC Configuration Register 1 is set. */
DECL|macro|HP100_RX_PRI
mdefine_line|#define HP100_RX_PRI&t;&t;0x8000&t;/* 0:No, 1:Yes packet is priority */
DECL|macro|HP100_SDF_ERR
mdefine_line|#define HP100_SDF_ERR&t;&t;0x4000&t;/* 0:No, 1:Yes start of frame error */
DECL|macro|HP100_SKEW_ERR
mdefine_line|#define HP100_SKEW_ERR&t;&t;0x2000&t;/* 0:No, 1:Yes skew out of range */
DECL|macro|HP100_BAD_SYMBOL_ERR
mdefine_line|#define HP100_BAD_SYMBOL_ERR&t;0x1000&t;/* 0:No, 1:Yes invalid symbol received */
DECL|macro|HP100_RCV_IPM_ERR
mdefine_line|#define HP100_RCV_IPM_ERR&t;0x0800&t;/* 0:No, 1:Yes pkt had an invalid packet */
multiline_comment|/*   marker */
DECL|macro|HP100_SYMBOL_BAL_ERR
mdefine_line|#define HP100_SYMBOL_BAL_ERR&t;0x0400&t;/* 0:No, 1:Yes symbol balance error */
DECL|macro|HP100_VG_ALN_ERR
mdefine_line|#define HP100_VG_ALN_ERR&t;0x0200&t;/* 0:No, 1:Yes non-octet received */
DECL|macro|HP100_TRUNC_ERR
mdefine_line|#define HP100_TRUNC_ERR&t;&t;0x0100&t;/* 0:No, 1:Yes the packet was truncated */
DECL|macro|HP100_RUNT_ERR
mdefine_line|#define HP100_RUNT_ERR&t;&t;0x0040&t;/* 0:No, 1:Yes pkt length &lt; Min Pkt */
multiline_comment|/*   Length Reg. */
DECL|macro|HP100_ALN_ERR
mdefine_line|#define HP100_ALN_ERR&t;&t;0x0010&t;/* 0:No, 1:Yes align error. */
DECL|macro|HP100_CRC_ERR
mdefine_line|#define HP100_CRC_ERR&t;&t;0x0008&t;/* 0:No, 1:Yes CRC occurred. */
multiline_comment|/* The last three bits indicate the type of destination address */
DECL|macro|HP100_MULTI_ADDR_HASH
mdefine_line|#define HP100_MULTI_ADDR_HASH&t;0x0006&t;/* 110: Addr multicast, matched hash */
DECL|macro|HP100_BROADCAST_ADDR
mdefine_line|#define HP100_BROADCAST_ADDR&t;0x0003&t;/* x11: Addr broadcast */
DECL|macro|HP100_MULTI_ADDR_NO_HASH
mdefine_line|#define HP100_MULTI_ADDR_NO_HASH 0x0002&t;/* 010: Addr multicast, didn&squot;t match hash */
DECL|macro|HP100_PHYS_ADDR_MATCH
mdefine_line|#define HP100_PHYS_ADDR_MATCH&t;0x0001&t;/* x01: Addr was physical and mine */
DECL|macro|HP100_PHYS_ADDR_NO_MATCH
mdefine_line|#define HP100_PHYS_ADDR_NO_MATCH 0x0000&t;/* x00: Addr was physical but not mine */
multiline_comment|/*&n; *  macros&n; */
DECL|macro|hp100_inb
mdefine_line|#define hp100_inb( reg ) &bslash;&n;        inb( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_inw
mdefine_line|#define hp100_inw( reg ) &bslash;&n;&t;inw( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_inl
mdefine_line|#define hp100_inl( reg ) &bslash;&n;&t;inl( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outb
mdefine_line|#define hp100_outb( data, reg ) &bslash;&n;&t;outb( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outw
mdefine_line|#define hp100_outw( data, reg ) &bslash;&n;&t;outw( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outl
mdefine_line|#define hp100_outl( data, reg ) &bslash;&n;&t;outl( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_orb
mdefine_line|#define hp100_orb( data, reg ) &bslash;&n;&t;outb( inb( ioaddr + HP100_REG_##reg ) | (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_orw
mdefine_line|#define hp100_orw( data, reg ) &bslash;&n;&t;outw( inw( ioaddr + HP100_REG_##reg ) | (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_andb
mdefine_line|#define hp100_andb( data, reg ) &bslash;&n;&t;outb( inb( ioaddr + HP100_REG_##reg ) &amp; (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_andw
mdefine_line|#define hp100_andw( data, reg ) &bslash;&n;&t;outw( inw( ioaddr + HP100_REG_##reg ) &amp; (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_page
mdefine_line|#define hp100_page( page ) &bslash;&n;&t;outw( HP100_PAGE_##page, ioaddr + HP100_REG_PAGING )
DECL|macro|hp100_ints_off
mdefine_line|#define hp100_ints_off() &bslash;&n;&t;outw( HP100_INT_EN | HP100_RESET_LB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_ints_on
mdefine_line|#define hp100_ints_on() &bslash;&n;&t;outw( HP100_INT_EN | HP100_SET_LB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_mem_map_enable
mdefine_line|#define hp100_mem_map_enable() &bslash;&n;&t;outw( HP100_MMAP_DIS | HP100_RESET_HB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_mem_map_disable
mdefine_line|#define hp100_mem_map_disable() &bslash;&n;&t;outw( HP100_MMAP_DIS | HP100_SET_HB, ioaddr + HP100_REG_OPTION_LSW )
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 2&n; *  tab-width: 8&n; * End:&n;*/
eof
