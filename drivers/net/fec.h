multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;fec.h  --  Fast Ethernet Controller for Motorola ColdFire 5270,&n;&t;&t;   5271, 5272, 5274, 5275, 5280 and 5282.&n; *&n; *&t;(C) Copyright 2000-2003, Greg Ungerer (gerg@snapgear.com)&n; *&t;(C) Copyright 2000-2001, Lineo (www.lineo.com)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef FEC_H
DECL|macro|FEC_H
mdefine_line|#define&t;FEC_H
multiline_comment|/****************************************************************************/
macro_line|#if defined(CONFIG_M527x) || defined(CONFIG_M528x)
multiline_comment|/*&n; *&t;Just figures, Motorola would have to change the offsets for&n; *&t;registers in the same peripheral device on different models&n; *&t;of the ColdFire!&n; */
DECL|struct|fec
r_typedef
r_struct
id|fec
(brace
DECL|member|fec_reserved0
r_int
r_int
id|fec_reserved0
suffix:semicolon
DECL|member|fec_ievent
r_int
r_int
id|fec_ievent
suffix:semicolon
multiline_comment|/* Interrupt event reg */
DECL|member|fec_imask
r_int
r_int
id|fec_imask
suffix:semicolon
multiline_comment|/* Interrupt mask reg */
DECL|member|fec_reserved1
r_int
r_int
id|fec_reserved1
suffix:semicolon
DECL|member|fec_r_des_active
r_int
r_int
id|fec_r_des_active
suffix:semicolon
multiline_comment|/* Receive descriptor reg */
DECL|member|fec_x_des_active
r_int
r_int
id|fec_x_des_active
suffix:semicolon
multiline_comment|/* Transmit descriptor reg */
DECL|member|fec_reserved2
r_int
r_int
id|fec_reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fec_ecntrl
r_int
r_int
id|fec_ecntrl
suffix:semicolon
multiline_comment|/* Ethernet control reg */
DECL|member|fec_reserved3
r_int
r_int
id|fec_reserved3
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fec_mii_data
r_int
r_int
id|fec_mii_data
suffix:semicolon
multiline_comment|/* MII manage frame reg */
DECL|member|fec_mii_speed
r_int
r_int
id|fec_mii_speed
suffix:semicolon
multiline_comment|/* MII speed control reg */
DECL|member|fec_reserved4
r_int
r_int
id|fec_reserved4
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|fec_mib_ctrlstat
r_int
r_int
id|fec_mib_ctrlstat
suffix:semicolon
multiline_comment|/* MIB control/status reg */
DECL|member|fec_reserved5
r_int
r_int
id|fec_reserved5
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|fec_r_cntrl
r_int
r_int
id|fec_r_cntrl
suffix:semicolon
multiline_comment|/* Receive control reg */
DECL|member|fec_reserved6
r_int
r_int
id|fec_reserved6
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|fec_x_cntrl
r_int
r_int
id|fec_x_cntrl
suffix:semicolon
multiline_comment|/* Transmit Control reg */
DECL|member|fec_reserved7
r_int
r_int
id|fec_reserved7
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|fec_addr_low
r_int
r_int
id|fec_addr_low
suffix:semicolon
multiline_comment|/* Low 32bits MAC address */
DECL|member|fec_addr_high
r_int
r_int
id|fec_addr_high
suffix:semicolon
multiline_comment|/* High 16bits MAC address */
DECL|member|fec_opd
r_int
r_int
id|fec_opd
suffix:semicolon
multiline_comment|/* Opcode + Pause duration */
DECL|member|fec_reserved8
r_int
r_int
id|fec_reserved8
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|fec_hash_table_high
r_int
r_int
id|fec_hash_table_high
suffix:semicolon
multiline_comment|/* High 32bits hash table */
DECL|member|fec_hash_table_low
r_int
r_int
id|fec_hash_table_low
suffix:semicolon
multiline_comment|/* Low 32bits hash table */
DECL|member|fec_grp_hash_table_high
r_int
r_int
id|fec_grp_hash_table_high
suffix:semicolon
multiline_comment|/* High 32bits hash table */
DECL|member|fec_grp_hash_table_low
r_int
r_int
id|fec_grp_hash_table_low
suffix:semicolon
multiline_comment|/* Low 32bits hash table */
DECL|member|fec_reserved9
r_int
r_int
id|fec_reserved9
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|fec_x_wmrk
r_int
r_int
id|fec_x_wmrk
suffix:semicolon
multiline_comment|/* FIFO transmit water mark */
DECL|member|fec_reserved10
r_int
r_int
id|fec_reserved10
suffix:semicolon
DECL|member|fec_r_bound
r_int
r_int
id|fec_r_bound
suffix:semicolon
multiline_comment|/* FIFO receive bound reg */
DECL|member|fec_r_fstart
r_int
r_int
id|fec_r_fstart
suffix:semicolon
multiline_comment|/* FIFO receive start reg */
DECL|member|fec_reserved11
r_int
r_int
id|fec_reserved11
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|fec_r_des_start
r_int
r_int
id|fec_r_des_start
suffix:semicolon
multiline_comment|/* Receive descriptor ring */
DECL|member|fec_x_des_start
r_int
r_int
id|fec_x_des_start
suffix:semicolon
multiline_comment|/* Transmit descriptor ring */
DECL|member|fec_r_buff_size
r_int
r_int
id|fec_r_buff_size
suffix:semicolon
multiline_comment|/* Maximum receive buff size */
DECL|typedef|fec_t
)brace
id|fec_t
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; *&t;Define device register set address map.&n; */
DECL|struct|fec
r_typedef
r_struct
id|fec
(brace
DECL|member|fec_ecntrl
r_int
r_int
id|fec_ecntrl
suffix:semicolon
multiline_comment|/* Ethernet control reg */
DECL|member|fec_ievent
r_int
r_int
id|fec_ievent
suffix:semicolon
multiline_comment|/* Interrupt even reg */
DECL|member|fec_imask
r_int
r_int
id|fec_imask
suffix:semicolon
multiline_comment|/* Interrupt mask reg */
DECL|member|fec_ivec
r_int
r_int
id|fec_ivec
suffix:semicolon
multiline_comment|/* Interrupt vec status reg */
DECL|member|fec_r_des_active
r_int
r_int
id|fec_r_des_active
suffix:semicolon
multiline_comment|/* Receive descriptor reg */
DECL|member|fec_x_des_active
r_int
r_int
id|fec_x_des_active
suffix:semicolon
multiline_comment|/* Transmit descriptor reg */
DECL|member|fec_reserved1
r_int
r_int
id|fec_reserved1
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|fec_mii_data
r_int
r_int
id|fec_mii_data
suffix:semicolon
multiline_comment|/* MII manage frame reg */
DECL|member|fec_mii_speed
r_int
r_int
id|fec_mii_speed
suffix:semicolon
multiline_comment|/* MII speed control reg */
DECL|member|fec_reserved2
r_int
r_int
id|fec_reserved2
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|fec_r_bound
r_int
r_int
id|fec_r_bound
suffix:semicolon
multiline_comment|/* FIFO receive bound reg */
DECL|member|fec_r_fstart
r_int
r_int
id|fec_r_fstart
suffix:semicolon
multiline_comment|/* FIFO receive start reg */
DECL|member|fec_reserved3
r_int
r_int
id|fec_reserved3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fec_x_wmrk
r_int
r_int
id|fec_x_wmrk
suffix:semicolon
multiline_comment|/* FIFO transmit water mark */
DECL|member|fec_reserved4
r_int
r_int
id|fec_reserved4
suffix:semicolon
DECL|member|fec_x_fstart
r_int
r_int
id|fec_x_fstart
suffix:semicolon
multiline_comment|/* FIFO transmit start reg */
DECL|member|fec_reserved5
r_int
r_int
id|fec_reserved5
(braket
l_int|21
)braket
suffix:semicolon
DECL|member|fec_r_cntrl
r_int
r_int
id|fec_r_cntrl
suffix:semicolon
multiline_comment|/* Receive control reg */
DECL|member|fec_max_frm_len
r_int
r_int
id|fec_max_frm_len
suffix:semicolon
multiline_comment|/* Maximum frame length reg */
DECL|member|fec_reserved6
r_int
r_int
id|fec_reserved6
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|fec_x_cntrl
r_int
r_int
id|fec_x_cntrl
suffix:semicolon
multiline_comment|/* Transmit Control reg */
DECL|member|fec_reserved7
r_int
r_int
id|fec_reserved7
(braket
l_int|158
)braket
suffix:semicolon
DECL|member|fec_addr_low
r_int
r_int
id|fec_addr_low
suffix:semicolon
multiline_comment|/* Low 32bits MAC address */
DECL|member|fec_addr_high
r_int
r_int
id|fec_addr_high
suffix:semicolon
multiline_comment|/* High 16bits MAC address */
DECL|member|fec_hash_table_high
r_int
r_int
id|fec_hash_table_high
suffix:semicolon
multiline_comment|/* High 32bits hash table */
DECL|member|fec_hash_table_low
r_int
r_int
id|fec_hash_table_low
suffix:semicolon
multiline_comment|/* Low 32bits hash table */
DECL|member|fec_r_des_start
r_int
r_int
id|fec_r_des_start
suffix:semicolon
multiline_comment|/* Receive descriptor ring */
DECL|member|fec_x_des_start
r_int
r_int
id|fec_x_des_start
suffix:semicolon
multiline_comment|/* Transmit descriptor ring */
DECL|member|fec_r_buff_size
r_int
r_int
id|fec_r_buff_size
suffix:semicolon
multiline_comment|/* Maximum receive buff size */
DECL|member|reserved8
r_int
r_int
id|reserved8
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|fec_fifo_ram
r_int
r_int
id|fec_fifo_ram
(braket
l_int|112
)braket
suffix:semicolon
multiline_comment|/* FIFO RAM buffer */
DECL|typedef|fec_t
)brace
id|fec_t
suffix:semicolon
macro_line|#endif /* CONFIG_M5272 */
multiline_comment|/*&n; *&t;Define the buffer descriptor structure.&n; */
DECL|struct|bufdesc
r_typedef
r_struct
id|bufdesc
(brace
DECL|member|cbd_sc
r_int
r_int
id|cbd_sc
suffix:semicolon
multiline_comment|/* Control and status info */
DECL|member|cbd_datlen
r_int
r_int
id|cbd_datlen
suffix:semicolon
multiline_comment|/* Data length */
DECL|member|cbd_bufaddr
r_int
r_int
id|cbd_bufaddr
suffix:semicolon
multiline_comment|/* Buffer address */
DECL|typedef|cbd_t
)brace
id|cbd_t
suffix:semicolon
multiline_comment|/*&n; *&t;The following definitions courtesy of commproc.h, which where&n; *&t;Copyright (c) 1997 Dan Malek (dmalek@jlc.net).&n; */
DECL|macro|BD_SC_EMPTY
mdefine_line|#define BD_SC_EMPTY     ((ushort)0x8000)        /* Recieve is empty */
DECL|macro|BD_SC_READY
mdefine_line|#define BD_SC_READY     ((ushort)0x8000)        /* Transmit is ready */
DECL|macro|BD_SC_WRAP
mdefine_line|#define BD_SC_WRAP      ((ushort)0x2000)        /* Last buffer descriptor */
DECL|macro|BD_SC_INTRPT
mdefine_line|#define BD_SC_INTRPT    ((ushort)0x1000)        /* Interrupt on change */
DECL|macro|BD_SC_CM
mdefine_line|#define BD_SC_CM        ((ushort)0x0200)        /* Continous mode */
DECL|macro|BD_SC_ID
mdefine_line|#define BD_SC_ID        ((ushort)0x0100)        /* Rec&squot;d too many idles */
DECL|macro|BD_SC_P
mdefine_line|#define BD_SC_P         ((ushort)0x0100)        /* xmt preamble */
DECL|macro|BD_SC_BR
mdefine_line|#define BD_SC_BR        ((ushort)0x0020)        /* Break received */
DECL|macro|BD_SC_FR
mdefine_line|#define BD_SC_FR        ((ushort)0x0010)        /* Framing error */
DECL|macro|BD_SC_PR
mdefine_line|#define BD_SC_PR        ((ushort)0x0008)        /* Parity error */
DECL|macro|BD_SC_OV
mdefine_line|#define BD_SC_OV        ((ushort)0x0002)        /* Overrun */
DECL|macro|BD_SC_CD
mdefine_line|#define BD_SC_CD        ((ushort)0x0001)        /* ?? */
multiline_comment|/* Buffer descriptor control/status used by Ethernet receive.&n;*/
DECL|macro|BD_ENET_RX_EMPTY
mdefine_line|#define BD_ENET_RX_EMPTY        ((ushort)0x8000)
DECL|macro|BD_ENET_RX_WRAP
mdefine_line|#define BD_ENET_RX_WRAP         ((ushort)0x2000)
DECL|macro|BD_ENET_RX_INTR
mdefine_line|#define BD_ENET_RX_INTR         ((ushort)0x1000)
DECL|macro|BD_ENET_RX_LAST
mdefine_line|#define BD_ENET_RX_LAST         ((ushort)0x0800)
DECL|macro|BD_ENET_RX_FIRST
mdefine_line|#define BD_ENET_RX_FIRST        ((ushort)0x0400)
DECL|macro|BD_ENET_RX_MISS
mdefine_line|#define BD_ENET_RX_MISS         ((ushort)0x0100)
DECL|macro|BD_ENET_RX_LG
mdefine_line|#define BD_ENET_RX_LG           ((ushort)0x0020)
DECL|macro|BD_ENET_RX_NO
mdefine_line|#define BD_ENET_RX_NO           ((ushort)0x0010)
DECL|macro|BD_ENET_RX_SH
mdefine_line|#define BD_ENET_RX_SH           ((ushort)0x0008)
DECL|macro|BD_ENET_RX_CR
mdefine_line|#define BD_ENET_RX_CR           ((ushort)0x0004)
DECL|macro|BD_ENET_RX_OV
mdefine_line|#define BD_ENET_RX_OV           ((ushort)0x0002)
DECL|macro|BD_ENET_RX_CL
mdefine_line|#define BD_ENET_RX_CL           ((ushort)0x0001)
DECL|macro|BD_ENET_RX_STATS
mdefine_line|#define BD_ENET_RX_STATS        ((ushort)0x013f)        /* All status bits */
multiline_comment|/* Buffer descriptor control/status used by Ethernet transmit.&n;*/
DECL|macro|BD_ENET_TX_READY
mdefine_line|#define BD_ENET_TX_READY        ((ushort)0x8000)
DECL|macro|BD_ENET_TX_PAD
mdefine_line|#define BD_ENET_TX_PAD          ((ushort)0x4000)
DECL|macro|BD_ENET_TX_WRAP
mdefine_line|#define BD_ENET_TX_WRAP         ((ushort)0x2000)
DECL|macro|BD_ENET_TX_INTR
mdefine_line|#define BD_ENET_TX_INTR         ((ushort)0x1000)
DECL|macro|BD_ENET_TX_LAST
mdefine_line|#define BD_ENET_TX_LAST         ((ushort)0x0800)
DECL|macro|BD_ENET_TX_TC
mdefine_line|#define BD_ENET_TX_TC           ((ushort)0x0400)
DECL|macro|BD_ENET_TX_DEF
mdefine_line|#define BD_ENET_TX_DEF          ((ushort)0x0200)
DECL|macro|BD_ENET_TX_HB
mdefine_line|#define BD_ENET_TX_HB           ((ushort)0x0100)
DECL|macro|BD_ENET_TX_LC
mdefine_line|#define BD_ENET_TX_LC           ((ushort)0x0080)
DECL|macro|BD_ENET_TX_RL
mdefine_line|#define BD_ENET_TX_RL           ((ushort)0x0040)
DECL|macro|BD_ENET_TX_RCMASK
mdefine_line|#define BD_ENET_TX_RCMASK       ((ushort)0x003c)
DECL|macro|BD_ENET_TX_UN
mdefine_line|#define BD_ENET_TX_UN           ((ushort)0x0002)
DECL|macro|BD_ENET_TX_CSL
mdefine_line|#define BD_ENET_TX_CSL          ((ushort)0x0001)
DECL|macro|BD_ENET_TX_STATS
mdefine_line|#define BD_ENET_TX_STATS        ((ushort)0x03ff)        /* All status bits */
multiline_comment|/****************************************************************************/
macro_line|#endif /* FEC_H */
eof
