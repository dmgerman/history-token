macro_line|#ifndef _LINUX_ISICOM_H
DECL|macro|_LINUX_ISICOM_H
mdefine_line|#define _LINUX_ISICOM_H
multiline_comment|/*#define&t;&t;ISICOM_DEBUG*/
multiline_comment|/*#define&t;&t;ISICOM_DEBUG_DTR_RTS*/
multiline_comment|/*&n; *&t;Firmware Loader definitions ...&n; */
DECL|macro|__MultiTech
mdefine_line|#define&t;&t;__MultiTech&t;&t;(&squot;M&squot;&lt;&lt;8)
DECL|macro|MIOCTL_LOAD_FIRMWARE
mdefine_line|#define&t;&t;MIOCTL_LOAD_FIRMWARE&t;(__MultiTech | 0x01)
DECL|macro|MIOCTL_READ_FIRMWARE
mdefine_line|#define         MIOCTL_READ_FIRMWARE    (__MultiTech | 0x02)
DECL|macro|MIOCTL_XFER_CTRL
mdefine_line|#define         MIOCTL_XFER_CTRL&t;(__MultiTech | 0x03)
DECL|macro|MIOCTL_RESET_CARD
mdefine_line|#define         MIOCTL_RESET_CARD&t;(__MultiTech | 0x04)
DECL|macro|DATA_SIZE
mdefine_line|#define&t;&t;DATA_SIZE&t;16
r_typedef
r_struct
(brace
DECL|member|exec_segment
r_int
r_int
id|exec_segment
suffix:semicolon
DECL|member|exec_addr
r_int
r_int
id|exec_addr
suffix:semicolon
DECL|typedef|exec_record
)brace
id|exec_record
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|board
r_int
id|board
suffix:semicolon
multiline_comment|/* Board to load */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|typedef|bin_header
)brace
id|bin_header
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|board
r_int
id|board
suffix:semicolon
multiline_comment|/* Board to load */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|segment
r_int
r_int
id|segment
suffix:semicolon
DECL|member|bin_data
r_int
r_char
id|bin_data
(braket
id|DATA_SIZE
)braket
suffix:semicolon
DECL|typedef|bin_frame
)brace
id|bin_frame
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|YES
mdefine_line|#define&t;&t;YES&t;1
DECL|macro|NO
mdefine_line|#define&t;&t;NO&t;0
DECL|macro|ISILOAD_MISC_MINOR
mdefine_line|#define&t;&t;ISILOAD_MISC_MINOR&t;155&t;/* /dev/isctl */
DECL|macro|ISILOAD_NAME
mdefine_line|#define&t;&t;ISILOAD_NAME&t;&t;&quot;ISILoad&quot;
multiline_comment|/*&t;&n; *  ISICOM Driver definitions ...&n; *&n; */
DECL|macro|ISICOM_NAME
mdefine_line|#define&t;&t;ISICOM_NAME&t;&quot;ISICom&quot;
multiline_comment|/*&n; *      PCI definitions&n; */
DECL|macro|DEVID_COUNT
mdefine_line|#define        DEVID_COUNT     9
DECL|macro|VENDOR_ID
mdefine_line|#define        VENDOR_ID       0x10b5
multiline_comment|/*&n; *&t;These are now officially allocated numbers&n; */
DECL|macro|ISICOM_NMAJOR
mdefine_line|#define&t;&t;ISICOM_NMAJOR&t;112&t;/* normal  */
DECL|macro|ISICOM_CMAJOR
mdefine_line|#define&t;&t;ISICOM_CMAJOR&t;113&t;/* callout */
DECL|macro|ISICOM_MAGIC
mdefine_line|#define&t;&t;ISICOM_MAGIC&t;((&squot;M&squot; &lt;&lt; 8) | &squot;T&squot;)
DECL|macro|WAKEUP_CHARS
mdefine_line|#define&t;&t;WAKEUP_CHARS&t;256&t;/* hard coded for now&t;*/ 
DECL|macro|TX_SIZE
mdefine_line|#define&t;&t;TX_SIZE&t;&t;254 
DECL|macro|BOARD_COUNT
mdefine_line|#define&t;&t;BOARD_COUNT&t;4
DECL|macro|PORT_COUNT
mdefine_line|#define&t;&t;PORT_COUNT&t;(BOARD_COUNT*16)
DECL|macro|SERIAL_TYPE_NORMAL
mdefine_line|#define&t;&t;SERIAL_TYPE_NORMAL&t;1
multiline_comment|/*   character sizes  */
DECL|macro|ISICOM_CS5
mdefine_line|#define&t;&t;ISICOM_CS5&t;&t;0x0000
DECL|macro|ISICOM_CS6
mdefine_line|#define&t;&t;ISICOM_CS6&t;&t;0x0001
DECL|macro|ISICOM_CS7
mdefine_line|#define&t;&t;ISICOM_CS7&t;&t;0x0002
DECL|macro|ISICOM_CS8
mdefine_line|#define&t;&t;ISICOM_CS8&t;&t;0x0003
multiline_comment|/* stop bits */
DECL|macro|ISICOM_1SB
mdefine_line|#define&t;&t;ISICOM_1SB&t;&t;0x0000
DECL|macro|ISICOM_2SB
mdefine_line|#define&t;&t;ISICOM_2SB&t;&t;0x0004
multiline_comment|/* parity */
DECL|macro|ISICOM_NOPAR
mdefine_line|#define&t;&t;ISICOM_NOPAR&t;&t;0x0000
DECL|macro|ISICOM_ODPAR
mdefine_line|#define&t;&t;ISICOM_ODPAR&t;&t;0x0008
DECL|macro|ISICOM_EVPAR
mdefine_line|#define&t;&t;ISICOM_EVPAR&t;&t;0x0018
multiline_comment|/* flow control */
DECL|macro|ISICOM_CTSRTS
mdefine_line|#define&t;&t;ISICOM_CTSRTS&t;&t;0x03
DECL|macro|ISICOM_INITIATE_XONXOFF
mdefine_line|#define&t;&t;ISICOM_INITIATE_XONXOFF&t;0x04
DECL|macro|ISICOM_RESPOND_XONXOFF
mdefine_line|#define&t;&t;ISICOM_RESPOND_XONXOFF&t;0x08
DECL|macro|InterruptTheCard
mdefine_line|#define InterruptTheCard(base) (outw(0,(base)+0xc)) 
DECL|macro|ClearInterrupt
mdefine_line|#define ClearInterrupt(base) (inw((base)+0x0a))&t;
DECL|macro|BOARD
mdefine_line|#define&t;BOARD(line)  (((line) &gt;&gt; 4) &amp; 0x3)
multiline_comment|/*&t;isi kill queue bitmap&t;*/
DECL|macro|ISICOM_KILLTX
mdefine_line|#define&t;&t;ISICOM_KILLTX&t;&t;0x01
DECL|macro|ISICOM_KILLRX
mdefine_line|#define&t;&t;ISICOM_KILLRX&t;&t;0x02
multiline_comment|/* isi_board status bitmap */
DECL|macro|FIRMWARE_LOADED
mdefine_line|#define&t;&t;FIRMWARE_LOADED&t;&t;0x0001
DECL|macro|BOARD_ACTIVE
mdefine_line|#define&t;&t;BOARD_ACTIVE&t;&t;0x0002
multiline_comment|/* isi_port status bitmap  */
DECL|macro|ISI_CTS
mdefine_line|#define&t;&t;ISI_CTS&t;&t;&t;0x1000
DECL|macro|ISI_DSR
mdefine_line|#define&t;&t;ISI_DSR&t;&t;&t;0x2000
DECL|macro|ISI_RI
mdefine_line|#define&t;&t;ISI_RI&t;&t;&t;0x4000
DECL|macro|ISI_DCD
mdefine_line|#define&t;&t;ISI_DCD&t;&t;&t;0x8000
DECL|macro|ISI_DTR
mdefine_line|#define&t;&t;ISI_DTR&t;&t;&t;0x0100
DECL|macro|ISI_RTS
mdefine_line|#define&t;&t;ISI_RTS&t;&t;&t;0x0200
DECL|macro|ISI_TXOK
mdefine_line|#define&t;&t;ISI_TXOK&t;&t;0x0001 
macro_line|#endif&t;/*&t;__KERNEL__&t;*/
macro_line|#endif&t;/*&t;ISICOM_H&t;*/
eof
