multiline_comment|/*&n; *  Copyright (c) 1999,2000 Petko Manolov - Petkan (pmanolov@lnxw.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;PEGASUS_DEV
DECL|macro|PEGASUS_II
mdefine_line|#define&t;PEGASUS_II&t;&t;0x80000000
DECL|macro|HAS_HOME_PNA
mdefine_line|#define&t;HAS_HOME_PNA&t;&t;0x40000000
DECL|macro|PEGASUS_MTU
mdefine_line|#define&t;PEGASUS_MTU&t;&t;1500
DECL|macro|PEGASUS_MAX_MTU
mdefine_line|#define&t;PEGASUS_MAX_MTU&t;&t;1536
DECL|macro|EPROM_WRITE
mdefine_line|#define&t;EPROM_WRITE&t;&t;0x01
DECL|macro|EPROM_READ
mdefine_line|#define&t;EPROM_READ&t;&t;0x02
DECL|macro|EPROM_DONE
mdefine_line|#define&t;EPROM_DONE&t;&t;0x04
DECL|macro|EPROM_WR_ENABLE
mdefine_line|#define&t;EPROM_WR_ENABLE&t;&t;0x10
DECL|macro|EPROM_LOAD
mdefine_line|#define&t;EPROM_LOAD&t;&t;0x20
DECL|macro|MII_BMCR
mdefine_line|#define&t;MII_BMCR&t;&t;0x00
DECL|macro|MII_BMSR
mdefine_line|#define&t;MII_BMSR&t;&t;0x01
DECL|macro|BMSR_MEDIA
mdefine_line|#define&t;BMSR_MEDIA&t;&t;0x7808
DECL|macro|MII_ANLPA
mdefine_line|#define&t;MII_ANLPA&t;&t;0x05
DECL|macro|ANLPA_100TX_FD
mdefine_line|#define&t;ANLPA_100TX_FD&t;&t;0x0100
DECL|macro|ANLPA_100TX_HD
mdefine_line|#define&t;ANLPA_100TX_HD&t;&t;0x0080
DECL|macro|ANLPA_10T_FD
mdefine_line|#define&t;ANLPA_10T_FD&t;&t;0x0040
DECL|macro|ANLPA_10T_HD
mdefine_line|#define&t;ANLPA_10T_HD&t;&t;0x0020
DECL|macro|PHY_DONE
mdefine_line|#define&t;PHY_DONE&t;&t;0x80
DECL|macro|PHY_READ
mdefine_line|#define&t;PHY_READ&t;&t;0x40
DECL|macro|PHY_WRITE
mdefine_line|#define&t;PHY_WRITE&t;&t;0x20
DECL|macro|DEFAULT_GPIO_RESET
mdefine_line|#define&t;DEFAULT_GPIO_RESET&t;0x24
DECL|macro|LINKSYS_GPIO_RESET
mdefine_line|#define&t;LINKSYS_GPIO_RESET&t;0x24
DECL|macro|DEFAULT_GPIO_SET
mdefine_line|#define&t;DEFAULT_GPIO_SET&t;0x26
DECL|macro|PEGASUS_PRESENT
mdefine_line|#define&t;PEGASUS_PRESENT&t;&t;0x00000001
DECL|macro|PEGASUS_RUNNING
mdefine_line|#define&t;PEGASUS_RUNNING&t;&t;0x00000002
DECL|macro|PEGASUS_TX_BUSY
mdefine_line|#define&t;PEGASUS_TX_BUSY&t;&t;0x00000004
DECL|macro|PEGASUS_RX_BUSY
mdefine_line|#define&t;PEGASUS_RX_BUSY&t;&t;0x00000008
DECL|macro|CTRL_URB_RUNNING
mdefine_line|#define&t;CTRL_URB_RUNNING&t;0x00000010
DECL|macro|CTRL_URB_SLEEP
mdefine_line|#define&t;CTRL_URB_SLEEP&t;&t;0x00000020
DECL|macro|PEGASUS_UNPLUG
mdefine_line|#define&t;PEGASUS_UNPLUG&t;&t;0x00000040
DECL|macro|ETH_REGS_CHANGE
mdefine_line|#define&t;ETH_REGS_CHANGE&t;&t;0x40000000
DECL|macro|ETH_REGS_CHANGED
mdefine_line|#define&t;ETH_REGS_CHANGED&t;0x80000000
DECL|macro|RX_MULTICAST
mdefine_line|#define&t;RX_MULTICAST&t;&t;2
DECL|macro|RX_PROMISCUOUS
mdefine_line|#define&t;RX_PROMISCUOUS&t;&t;4
DECL|macro|REG_TIMEOUT
mdefine_line|#define&t;REG_TIMEOUT&t;&t;(HZ)
DECL|macro|PEGASUS_TX_TIMEOUT
mdefine_line|#define&t;PEGASUS_TX_TIMEOUT&t;(HZ*10)
DECL|macro|TX_UNDERRUN
mdefine_line|#define&t;TX_UNDERRUN&t;&t;0x80
DECL|macro|EXCESSIVE_COL
mdefine_line|#define&t;EXCESSIVE_COL&t;&t;0x40
DECL|macro|LATE_COL
mdefine_line|#define&t;LATE_COL&t;&t;0x20
DECL|macro|NO_CARRIER
mdefine_line|#define&t;NO_CARRIER&t;&t;0x10
DECL|macro|LOSS_CARRIER
mdefine_line|#define&t;LOSS_CARRIER&t;&t;0x08
DECL|macro|JABBER_TIMEOUT
mdefine_line|#define&t;JABBER_TIMEOUT&t;&t;0x04
DECL|macro|PEGASUS_REQT_READ
mdefine_line|#define&t;PEGASUS_REQT_READ&t;0xc0
DECL|macro|PEGASUS_REQT_WRITE
mdefine_line|#define&t;PEGASUS_REQT_WRITE&t;0x40
DECL|macro|PEGASUS_REQ_GET_REGS
mdefine_line|#define&t;PEGASUS_REQ_GET_REGS&t;0xf0
DECL|macro|PEGASUS_REQ_SET_REGS
mdefine_line|#define&t;PEGASUS_REQ_SET_REGS&t;0xf1
DECL|macro|PEGASUS_REQ_SET_REG
mdefine_line|#define&t;PEGASUS_REQ_SET_REG&t;PEGASUS_REQ_SET_REGS
DECL|macro|ALIGN
mdefine_line|#define&t;ALIGN(x)&t;&t;x __attribute__((aligned(L1_CACHE_BYTES)))
DECL|enum|pegasus_registers
r_enum
id|pegasus_registers
(brace
DECL|enumerator|EthCtrl0
id|EthCtrl0
op_assign
l_int|0
comma
DECL|enumerator|EthCtrl1
id|EthCtrl1
op_assign
l_int|1
comma
DECL|enumerator|EthCtrl2
id|EthCtrl2
op_assign
l_int|2
comma
DECL|enumerator|EthID
id|EthID
op_assign
l_int|0x10
comma
DECL|enumerator|Reg1d
id|Reg1d
op_assign
l_int|0x1d
comma
DECL|enumerator|EpromOffset
id|EpromOffset
op_assign
l_int|0x20
comma
DECL|enumerator|EpromData
id|EpromData
op_assign
l_int|0x21
comma
multiline_comment|/* 0x21 low, 0x22 high byte */
DECL|enumerator|EpromCtrl
id|EpromCtrl
op_assign
l_int|0x23
comma
DECL|enumerator|PhyAddr
id|PhyAddr
op_assign
l_int|0x25
comma
DECL|enumerator|PhyData
id|PhyData
op_assign
l_int|0x26
comma
multiline_comment|/* 0x26 low, 0x27 high byte */
DECL|enumerator|PhyCtrl
id|PhyCtrl
op_assign
l_int|0x28
comma
DECL|enumerator|UsbStst
id|UsbStst
op_assign
l_int|0x2a
comma
DECL|enumerator|EthTxStat0
id|EthTxStat0
op_assign
l_int|0x2b
comma
DECL|enumerator|EthTxStat1
id|EthTxStat1
op_assign
l_int|0x2c
comma
DECL|enumerator|EthRxStat
id|EthRxStat
op_assign
l_int|0x2d
comma
DECL|enumerator|Reg7b
id|Reg7b
op_assign
l_int|0x7b
comma
DECL|enumerator|Gpio0
id|Gpio0
op_assign
l_int|0x7e
comma
DECL|enumerator|Gpio1
id|Gpio1
op_assign
l_int|0x7f
comma
DECL|enumerator|Reg81
id|Reg81
op_assign
l_int|0x81
comma
)brace
suffix:semicolon
DECL|struct|pegasus
r_typedef
r_struct
id|pegasus
(brace
DECL|member|usb
r_struct
id|usb_device
op_star
id|usb
suffix:semicolon
DECL|member|net
r_struct
id|net_device
op_star
id|net
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|features
r_int
id|features
suffix:semicolon
DECL|member|dev_index
r_int
id|dev_index
suffix:semicolon
DECL|member|intr_interval
r_int
id|intr_interval
suffix:semicolon
DECL|member|ctrl_urb
DECL|member|rx_urb
DECL|member|tx_urb
DECL|member|intr_urb
r_struct
id|urb
op_star
id|ctrl_urb
comma
op_star
id|rx_urb
comma
op_star
id|tx_urb
comma
op_star
id|intr_urb
suffix:semicolon
DECL|member|dr
r_struct
id|usb_ctrlrequest
id|dr
suffix:semicolon
DECL|member|ctrl_wait
id|wait_queue_head_t
id|ctrl_wait
suffix:semicolon
DECL|member|ctrl_sem
r_struct
id|semaphore
id|ctrl_sem
suffix:semicolon
r_int
r_char
id|ALIGN
c_func
(paren
id|rx_buff
(braket
id|PEGASUS_MAX_MTU
)braket
)paren
suffix:semicolon
r_int
r_char
id|ALIGN
c_func
(paren
id|tx_buff
(braket
id|PEGASUS_MAX_MTU
)braket
)paren
suffix:semicolon
r_int
r_char
id|ALIGN
c_func
(paren
id|intr_buff
(braket
l_int|8
)braket
)paren
suffix:semicolon
DECL|member|eth_regs
id|__u8
id|eth_regs
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|phy
id|__u8
id|phy
suffix:semicolon
DECL|member|gpio_res
id|__u8
id|gpio_res
suffix:semicolon
DECL|typedef|pegasus_t
)brace
id|pegasus_t
suffix:semicolon
DECL|struct|usb_eth_dev
r_struct
id|usb_eth_dev
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|vendor
id|__u16
id|vendor
suffix:semicolon
DECL|member|device
id|__u16
id|device
suffix:semicolon
DECL|member|private
id|__u32
r_private
suffix:semicolon
multiline_comment|/* LSB is gpio reset value */
)brace
suffix:semicolon
DECL|macro|VENDOR_3COM
mdefine_line|#define&t;VENDOR_3COM&t;&t;0x0506
DECL|macro|VENDOR_ABOCOM
mdefine_line|#define&t;VENDOR_ABOCOM&t;&t;0x07b8
DECL|macro|VENDOR_ACCTON
mdefine_line|#define&t;VENDOR_ACCTON&t;&t;0x083a
DECL|macro|VENDOR_ADMTEK
mdefine_line|#define&t;VENDOR_ADMTEK&t;&t;0x07a6
DECL|macro|VENDOR_ALLIEDTEL
mdefine_line|#define&t;VENDOR_ALLIEDTEL&t;0x07c9
DECL|macro|VENDOR_BELKIN
mdefine_line|#define&t;VENDOR_BELKIN&t;&t;0x050d
DECL|macro|VENDOR_BILLIONTON
mdefine_line|#define&t;VENDOR_BILLIONTON&t;0x08dd
DECL|macro|VENDOR_COMPAQ
mdefine_line|#define&t;VENDOR_COMPAQ&t;&t;0x049f
DECL|macro|VENDOR_COREGA
mdefine_line|#define&t;VENDOR_COREGA&t;&t;0x07aa
DECL|macro|VENDOR_DLINK
mdefine_line|#define&t;VENDOR_DLINK&t;&t;0x2001
DECL|macro|VENDOR_ELSA
mdefine_line|#define&t;VENDOR_ELSA&t;&t;0x05cc
DECL|macro|VENDOR_HAWKING
mdefine_line|#define&t;VENDOR_HAWKING&t;&t;0x0e66
DECL|macro|VENDOR_IODATA
mdefine_line|#define&t;VENDOR_IODATA&t;&t;0x04bb
DECL|macro|VENDOR_KINGSTON
mdefine_line|#define&t;VENDOR_KINGSTON&t;&t;0x0951
DECL|macro|VENDOR_LANEED
mdefine_line|#define&t;VENDOR_LANEED&t;&t;0x056e
DECL|macro|VENDOR_LINKSYS
mdefine_line|#define&t;VENDOR_LINKSYS&t;&t;0x066b
DECL|macro|VENDOR_MELCO
mdefine_line|#define&t;VENDOR_MELCO&t;&t;0x0411
DECL|macro|VENDOR_SMARTBRIDGES
mdefine_line|#define&t;VENDOR_SMARTBRIDGES&t;0x08d1
DECL|macro|VENDOR_SMC
mdefine_line|#define&t;VENDOR_SMC&t;&t;0x0707
DECL|macro|VENDOR_SOHOWARE
mdefine_line|#define&t;VENDOR_SOHOWARE&t;&t;0x15e8
DECL|macro|VENDOR_SIEMENS
mdefine_line|#define&t;VENDOR_SIEMENS&t;&t;0x067c
macro_line|#else&t;/* PEGASUS_DEV */
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;3Com USB Ethernet 3C460B&quot;
comma
id|VENDOR_3COM
comma
l_int|0x4601
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB HPNA/Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x110c
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB HPNA/Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x4104
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB HPNA/Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x4004
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB HPNA/Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x4007
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x4102
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x4002
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x400b
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x400c
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0xabc1
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;USB 10/100 Fast Ethernet&quot;
comma
id|VENDOR_ABOCOM
comma
l_int|0x200c
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Accton USB 10/100 Ethernet Adapter&quot;
comma
id|VENDOR_ACCTON
comma
l_int|0x1046
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;SpeedStream USB 10/100 Ethernet&quot;
comma
id|VENDOR_ACCTON
comma
l_int|0x5046
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;ADMtek ADM8511 &bslash;&quot;Pegasus II&bslash;&quot; USB Ethernet&quot;
comma
id|VENDOR_ADMTEK
comma
l_int|0x8511
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;ADMtek AN986 &bslash;&quot;Pegasus&bslash;&quot; USB Ethernet (eval. board)&quot;
comma
id|VENDOR_ADMTEK
comma
l_int|0x0986
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Allied Telesyn Int. AT-USB100&quot;
comma
id|VENDOR_ALLIEDTEL
comma
l_int|0xb100
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Belkin F5D5050 USB Ethernet&quot;
comma
id|VENDOR_BELKIN
comma
l_int|0x0121
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Billionton USB-100&quot;
comma
id|VENDOR_BILLIONTON
comma
l_int|0x0986
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Billionton USBLP-100&quot;
comma
id|VENDOR_BILLIONTON
comma
l_int|0x0987
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;iPAQ Networking 10/100 USB&quot;
comma
id|VENDOR_COMPAQ
comma
l_int|0x8511
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Billionton USBEL-100&quot;
comma
id|VENDOR_BILLIONTON
comma
l_int|0x0988
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Billionton USBE-100&quot;
comma
id|VENDOR_BILLIONTON
comma
l_int|0x8511
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Corega FEter USB-TX&quot;
comma
id|VENDOR_COREGA
comma
l_int|0x0004
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x4001
comma
id|LINKSYS_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x4002
comma
id|LINKSYS_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x4102
comma
id|LINKSYS_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x400b
comma
id|LINKSYS_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x200c
comma
id|LINKSYS_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650TX(PNA)&quot;
comma
id|VENDOR_DLINK
comma
l_int|0x4003
comma
id|DEFAULT_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;D-Link DSB-650&quot;
comma
id|VENDOR_DLINK
comma
l_int|0xabc1
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Elsa Micolink USB2Ethernet&quot;
comma
id|VENDOR_ELSA
comma
l_int|0x3000
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Hawking UF100 10/100 Ethernet&quot;
comma
id|VENDOR_HAWKING
comma
l_int|0x400c
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;IO DATA USB ET/TX&quot;
comma
id|VENDOR_IODATA
comma
l_int|0x0904
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;IO DATA USB ET/TX-S&quot;
comma
id|VENDOR_IODATA
comma
l_int|0x0913
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Kingston KNU101TX Ethernet&quot;
comma
id|VENDOR_KINGSTON
comma
l_int|0x000a
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;LANEED USB Ethernet LD-USB/TX&quot;
comma
id|VENDOR_LANEED
comma
l_int|0x4002
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;LANEED USB Ethernet LD-USB/TX&quot;
comma
id|VENDOR_LANEED
comma
l_int|0x400b
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;LANEED USB Ethernet LD-USB/T&quot;
comma
id|VENDOR_LANEED
comma
l_int|0xabc1
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;LANEED USB Ethernet LD-USB/TX&quot;
comma
id|VENDOR_LANEED
comma
l_int|0x200c
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB10TX&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x2202
comma
id|LINKSYS_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB100TX&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x2203
comma
id|LINKSYS_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB100TX&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x2204
comma
id|LINKSYS_GPIO_RESET
op_or
id|HAS_HOME_PNA
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB Ethernet Adapter&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x2206
comma
id|LINKSYS_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB USB10TX&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x400b
comma
id|LINKSYS_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;Linksys USB10TX&quot;
comma
id|VENDOR_LINKSYS
comma
l_int|0x200c
comma
id|LINKSYS_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;MELCO/BUFFALO LUA-TX&quot;
comma
id|VENDOR_MELCO
comma
l_int|0x0001
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;MELCO/BUFFALO LUA-TX&quot;
comma
id|VENDOR_MELCO
comma
l_int|0x0005
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;MELCO/BUFFALO LUA2-TX&quot;
comma
id|VENDOR_MELCO
comma
l_int|0x0009
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;smartNIC 2 PnP Adapter&quot;
comma
id|VENDOR_SMARTBRIDGES
comma
l_int|0x0003
comma
id|DEFAULT_GPIO_RESET
op_or
id|PEGASUS_II
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;SMC 202 USB Ethernet&quot;
comma
id|VENDOR_SMC
comma
l_int|0x0200
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;SOHOware NUB100 Ethernet&quot;
comma
id|VENDOR_SOHOWARE
comma
l_int|0x9100
comma
id|DEFAULT_GPIO_RESET
)paren
id|PEGASUS_DEV
c_func
(paren
l_string|&quot;SpeedStream USB 10/100 Ethernet&quot;
comma
id|VENDOR_SIEMENS
comma
l_int|0x1001
comma
id|DEFAULT_GPIO_RESET
)paren
macro_line|#endif&t;/* PEGASUS_DEV */
eof
