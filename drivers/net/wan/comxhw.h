multiline_comment|/*&n; * Defines for comxhw.c&n; *&n; * Original authors:  Arpad Bakay &lt;bakay.arpad@synergon.hu&gt;,&n; *                    Peter Bajan &lt;bajan.peter@synergon.hu&gt;,&n; * Previous maintainer: Tivadar Szemethy &lt;tiv@itc.hu&gt;&n; * Current maintainer: Gergely Madarasz &lt;gorgo@itc.hu&gt;&n; *&n; * Copyright (C) 1995-1999 ITConsult-Pro Co. &lt;info@itc.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; */
DECL|macro|LOCOMX_IO_EXTENT
mdefine_line|#define&t;LOCOMX_IO_EXTENT&t;8
DECL|macro|COMX_IO_EXTENT
mdefine_line|#define COMX_IO_EXTENT&t;&t;4
DECL|macro|HICOMX_IO_EXTENT
mdefine_line|#define&t;HICOMX_IO_EXTENT&t;16
DECL|macro|COMX_MAX_TX_SIZE
mdefine_line|#define COMX_MAX_TX_SIZE&t;1600
DECL|macro|COMX_MAX_RX_SIZE
mdefine_line|#define COMX_MAX_RX_SIZE&t;2048
DECL|macro|COMX_JAIL_OFFSET
mdefine_line|#define COMX_JAIL_OFFSET&t;0xffff
DECL|macro|COMX_JAIL_VALUE
mdefine_line|#define COMX_JAIL_VALUE&t;&t;0xfe
DECL|macro|COMX_MEMORY_SIZE
mdefine_line|#define&t;COMX_MEMORY_SIZE&t;65536
DECL|macro|HICOMX_MEMORY_SIZE
mdefine_line|#define HICOMX_MEMORY_SIZE&t;16384
DECL|macro|COMX_MEM_MIN
mdefine_line|#define COMX_MEM_MIN&t;&t;0xa0000
DECL|macro|COMX_MEM_MAX
mdefine_line|#define COMX_MEM_MAX&t;&t;0xf0000
DECL|macro|COMX_DEFAULT_IO
mdefine_line|#define&t;COMX_DEFAULT_IO&t;&t;0x360
DECL|macro|COMX_DEFAULT_IRQ
mdefine_line|#define&t;COMX_DEFAULT_IRQ&t;10
DECL|macro|COMX_DEFAULT_MEMADDR
mdefine_line|#define&t;COMX_DEFAULT_MEMADDR&t;0xd0000
DECL|macro|HICOMX_DEFAULT_IO
mdefine_line|#define&t;HICOMX_DEFAULT_IO&t;0x320
DECL|macro|HICOMX_DEFAULT_IRQ
mdefine_line|#define&t;HICOMX_DEFAULT_IRQ&t;10
DECL|macro|HICOMX_DEFAULT_MEMADDR
mdefine_line|#define&t;HICOMX_DEFAULT_MEMADDR&t;0xd0000
DECL|macro|LOCOMX_DEFAULT_IO
mdefine_line|#define&t;LOCOMX_DEFAULT_IO&t;0x368
DECL|macro|LOCOMX_DEFAULT_IRQ
mdefine_line|#define&t;LOCOMX_DEFAULT_IRQ&t;7
DECL|macro|MAX_CHANNELNO
mdefine_line|#define MAX_CHANNELNO&t;&t;2
DECL|macro|COMX_CHANNEL_OFFSET
mdefine_line|#define&t;COMX_CHANNEL_OFFSET&t;0x2000
DECL|macro|COMX_ENABLE_BOARD_IT
mdefine_line|#define COMX_ENABLE_BOARD_IT    0x40
DECL|macro|COMX_BOARD_RESET
mdefine_line|#define COMX_BOARD_RESET       &t;0x20
DECL|macro|COMX_ENABLE_BOARD_MEM
mdefine_line|#define COMX_ENABLE_BOARD_MEM   0x10
DECL|macro|COMX_DISABLE_BOARD_MEM
mdefine_line|#define COMX_DISABLE_BOARD_MEM  0
DECL|macro|COMX_DISABLE_ALL
mdefine_line|#define COMX_DISABLE_ALL&t;0x00
DECL|macro|HICOMX_DISABLE_ALL
mdefine_line|#define HICOMX_DISABLE_ALL&t;0x00
DECL|macro|HICOMX_ENABLE_BOARD_MEM
mdefine_line|#define HICOMX_ENABLE_BOARD_MEM&t;0x02
DECL|macro|HICOMX_DISABLE_BOARD_MEM
mdefine_line|#define HICOMX_DISABLE_BOARD_MEM 0x0
DECL|macro|HICOMX_BOARD_RESET
mdefine_line|#define HICOMX_BOARD_RESET&t;0x01
DECL|macro|HICOMX_PRG_MEM
mdefine_line|#define HICOMX_PRG_MEM&t;&t;4
DECL|macro|HICOMX_DATA_MEM
mdefine_line|#define HICOMX_DATA_MEM&t;&t;0
DECL|macro|HICOMX_ID_BYTE
mdefine_line|#define HICOMX_ID_BYTE&t;&t;0x55
DECL|macro|CMX_ID_BYTE
mdefine_line|#define CMX_ID_BYTE&t;&t;0x31
DECL|macro|COMX_CLOCK_CONST
mdefine_line|#define COMX_CLOCK_CONST&t;8000
DECL|macro|LINKUP_READY
mdefine_line|#define&t;LINKUP_READY&t;&t;3
DECL|macro|OFF_FW_L1_ID
mdefine_line|#define&t;OFF_FW_L1_ID&t;0x01e&t; /* ID bytes */
DECL|macro|OFF_FW_L2_ID
mdefine_line|#define OFF_FW_L2_ID&t;0x1006
DECL|macro|FW_L1_ID_1
mdefine_line|#define&t;FW_L1_ID_1&t;0xab
DECL|macro|FW_L1_ID_2_COMX
mdefine_line|#define FW_L1_ID_2_COMX&t;&t;0xc0
DECL|macro|FW_L1_ID_2_HICOMX
mdefine_line|#define FW_L1_ID_2_HICOMX&t;0xc1
DECL|macro|FW_L2_ID_1
mdefine_line|#define&t;FW_L2_ID_1&t;0xab
DECL|macro|OFF_A_L2_CMD
mdefine_line|#define OFF_A_L2_CMD     0x130   /* command register for L2 */
DECL|macro|OFF_A_L2_CMDPAR
mdefine_line|#define OFF_A_L2_CMDPAR  0x131   /* command parameter byte */
DECL|macro|OFF_A_L1_STATB
mdefine_line|#define OFF_A_L1_STATB   0x122   /* stat. block for L1 */
DECL|macro|OFF_A_L1_ABOREC
mdefine_line|#define OFF_A_L1_ABOREC  0x122   /* receive ABORT counter */
DECL|macro|OFF_A_L1_OVERRUN
mdefine_line|#define OFF_A_L1_OVERRUN 0x123   /* receive overrun counter */
DECL|macro|OFF_A_L1_CRCREC
mdefine_line|#define OFF_A_L1_CRCREC  0x124   /* CRC error counter */
DECL|macro|OFF_A_L1_BUFFOVR
mdefine_line|#define OFF_A_L1_BUFFOVR 0x125   /* buffer overrun counter */
DECL|macro|OFF_A_L1_PBUFOVR
mdefine_line|#define OFF_A_L1_PBUFOVR 0x126   /* priority buffer overrun counter */
DECL|macro|OFF_A_L1_MODSTAT
mdefine_line|#define OFF_A_L1_MODSTAT 0x127   /* current state of modem ctrl lines */
DECL|macro|OFF_A_L1_STATE
mdefine_line|#define OFF_A_L1_STATE   0x127   /* end of stat. block for L1 */
DECL|macro|OFF_A_L1_TXPC
mdefine_line|#define OFF_A_L1_TXPC    0x128   /* Tx counter for the PC */
DECL|macro|OFF_A_L1_TXZ80
mdefine_line|#define OFF_A_L1_TXZ80   0x129   /* Tx counter for the Z80 */
DECL|macro|OFF_A_L1_RXPC
mdefine_line|#define OFF_A_L1_RXPC    0x12a   /* Rx counter for the PC */
DECL|macro|OFF_A_L1_RXZ80
mdefine_line|#define OFF_A_L1_RXZ80   0x12b   /* Rx counter for the Z80 */
DECL|macro|OFF_A_L1_REPENA
mdefine_line|#define OFF_A_L1_REPENA  0x12c   /* IT rep disable */
DECL|macro|OFF_A_L1_CHNR
mdefine_line|#define OFF_A_L1_CHNR    0x12d   /* L1 channel logical number */
DECL|macro|OFF_A_L1_CLKINI
mdefine_line|#define OFF_A_L1_CLKINI  0x12e   /* Timer Const */
DECL|macro|OFF_A_L2_LINKUP
mdefine_line|#define OFF_A_L2_LINKUP&t; 0x132&t; /* Linkup byte */
DECL|macro|OFF_A_L2_DAV
mdefine_line|#define OFF_A_L2_DAV&t; 0x134   /* Rx DAV */
DECL|macro|OFF_A_L2_RxBUFP
mdefine_line|#define OFF_A_L2_RxBUFP  0x136&t; /* Rx buff relative to membase */
DECL|macro|OFF_A_L2_TxEMPTY
mdefine_line|#define OFF_A_L2_TxEMPTY 0x138   /* Tx Empty */
DECL|macro|OFF_A_L2_TxBUFP
mdefine_line|#define OFF_A_L2_TxBUFP  0x13a   /* Tx Buf */
DECL|macro|OFF_A_L2_NBUFFS
mdefine_line|#define OFF_A_L2_NBUFFS&t; 0x144&t; /* Number of buffers to fetch */
DECL|macro|OFF_A_L2_SABMREC
mdefine_line|#define OFF_A_L2_SABMREC 0x164&t; /* LAPB no. of SABMs received */
DECL|macro|OFF_A_L2_SABMSENT
mdefine_line|#define OFF_A_L2_SABMSENT 0x165&t; /* LAPB no. of SABMs sent */
DECL|macro|OFF_A_L2_REJREC
mdefine_line|#define OFF_A_L2_REJREC  0x166&t; /* LAPB no. of REJs received */
DECL|macro|OFF_A_L2_REJSENT
mdefine_line|#define OFF_A_L2_REJSENT 0x167&t; /* LAPB no. of REJs sent */
DECL|macro|OFF_A_L2_FRMRREC
mdefine_line|#define OFF_A_L2_FRMRREC 0x168&t; /* LAPB no. of FRMRs received */
DECL|macro|OFF_A_L2_FRMRSENT
mdefine_line|#define OFF_A_L2_FRMRSENT 0x169&t; /* LAPB no. of FRMRs sent */
DECL|macro|OFF_A_L2_PROTERR
mdefine_line|#define OFF_A_L2_PROTERR 0x16A&t; /* LAPB no. of protocol errors rec&squot;d */
DECL|macro|OFF_A_L2_LONGREC
mdefine_line|#define OFF_A_L2_LONGREC 0x16B&t; /* LAPB no. of long frames */
DECL|macro|OFF_A_L2_INVNR
mdefine_line|#define OFF_A_L2_INVNR   0x16C&t; /* LAPB no. of invalid N(R)s rec&squot;d */
DECL|macro|OFF_A_L2_UNDEFFR
mdefine_line|#define OFF_A_L2_UNDEFFR 0x16D&t; /* LAPB no. of invalid frames */
DECL|macro|OFF_A_L2_T1
mdefine_line|#define&t;OFF_A_L2_T1&t;0x174&t; /* T1 timer */
DECL|macro|OFF_A_L2_ADDR
mdefine_line|#define&t;OFF_A_L2_ADDR&t;0x176&t; /* DCE = 1, DTE = 3 */
DECL|macro|COMX_CMD_INIT
mdefine_line|#define&t;COMX_CMD_INIT&t;1
DECL|macro|COMX_CMD_EXIT
mdefine_line|#define COMX_CMD_EXIT&t;2
DECL|macro|COMX_CMD_OPEN
mdefine_line|#define COMX_CMD_OPEN&t;16
DECL|macro|COMX_CMD_CLOSE
mdefine_line|#define COMX_CMD_CLOSE&t;17
eof
