macro_line|#ifndef _PS2ESDI_H_
DECL|macro|_PS2ESDI_H_
mdefine_line|#define _PS2ESDI_H_
DECL|macro|NRML_ESDI_ID
mdefine_line|#define NRML_ESDI_ID 0xddff
DECL|macro|INTG_ESDI_ID
mdefine_line|#define INTG_ESDI_ID 0xdf9f
DECL|macro|PRIMARY_IO_BASE
mdefine_line|#define PRIMARY_IO_BASE 0x3510
DECL|macro|ALT_IO_BASE
mdefine_line|#define ALT_IO_BASE 0x3518
DECL|macro|ESDI_CMD_INT
mdefine_line|#define ESDI_CMD_INT (io_base+0)
DECL|macro|ESDI_STT_INT
mdefine_line|#define ESDI_STT_INT (io_base+0)
DECL|macro|ESDI_CONTROL
mdefine_line|#define ESDI_CONTROL (io_base+2)
DECL|macro|ESDI_STATUS
mdefine_line|#define ESDI_STATUS  (io_base+2)
DECL|macro|ESDI_ATTN
mdefine_line|#define ESDI_ATTN    (io_base+3)
DECL|macro|ESDI_INTRPT
mdefine_line|#define ESDI_INTRPT  (io_base+3)
DECL|macro|STATUS_ENABLED
mdefine_line|#define STATUS_ENABLED    0x01
DECL|macro|STATUS_ALTERNATE
mdefine_line|#define STATUS_ALTERNATE  0x02
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY       0x10
DECL|macro|STATUS_STAT_AVAIL
mdefine_line|#define STATUS_STAT_AVAIL 0x08
DECL|macro|STATUS_INTR
mdefine_line|#define STATUS_INTR       0x01
DECL|macro|STATUS_RESET_FAIL
mdefine_line|#define STATUS_RESET_FAIL 0xea
DECL|macro|STATUS_CMD_INF
mdefine_line|#define STATUS_CMD_INF&t;  0x04
DECL|macro|CTRL_SOFT_RESET
mdefine_line|#define CTRL_SOFT_RESET   0xe4
DECL|macro|CTRL_HARD_RESET
mdefine_line|#define CTRL_HARD_RESET   0x80
DECL|macro|CTRL_EOI
mdefine_line|#define CTRL_EOI          0xe2
DECL|macro|CTRL_ENABLE_DMA
mdefine_line|#define CTRL_ENABLE_DMA   0x02
DECL|macro|CTRL_ENABLE_INTR
mdefine_line|#define CTRL_ENABLE_INTR  0x01
DECL|macro|CTRL_DISABLE_INTR
mdefine_line|#define CTRL_DISABLE_INTR  0x00
DECL|macro|ATT_EOI
mdefine_line|#define ATT_EOI 0x02
multiline_comment|/* bits of word 0 of configuration status block. more info see p.38 of tech ref */
DECL|macro|CONFIG_IS
mdefine_line|#define CONFIG_IS 0x10 /* Invalid Secondary */
DECL|macro|CONFIG_ZD
mdefine_line|#define CONFIG_ZD 0x08 /* Zero Defect */
DECL|macro|CONFIG_SF
mdefine_line|#define CONFIG_SF 0x04 /* Skewed Format */
DECL|macro|CONFIG_FR
mdefine_line|#define CONFIG_FR 0x02 /* Removable */
DECL|macro|CONFIG_RT
mdefine_line|#define CONFIG_RT 0x01 /* Retries */
DECL|macro|PORT_SYS_A
mdefine_line|#define PORT_SYS_A   0x92
DECL|macro|PORT_DMA_FN
mdefine_line|#define PORT_DMA_FN  0x18
DECL|macro|PORT_DMA_EX
mdefine_line|#define PORT_DMA_EX  0x1a
DECL|macro|ON
mdefine_line|#define ON (unsigned char)0x40
DECL|macro|OFF
mdefine_line|#define OFF (unsigned char)~ON
DECL|macro|LITE_ON
mdefine_line|#define LITE_ON outb(inb(PORT_SYS_A) | ON,PORT_SYS_A)
DECL|macro|LITE_OFF
mdefine_line|#define LITE_OFF outb((inb(PORT_SYS_A) &amp; OFF),PORT_SYS_A)
DECL|macro|FAIL
mdefine_line|#define FAIL 0
DECL|macro|SUCCES
mdefine_line|#define SUCCES 1
DECL|macro|INT_CMD_COMPLETE
mdefine_line|#define INT_CMD_COMPLETE 0x01
DECL|macro|INT_CMD_ECC
mdefine_line|#define INT_CMD_ECC      0x03
DECL|macro|INT_CMD_RETRY
mdefine_line|#define INT_CMD_RETRY    0x05
DECL|macro|INT_CMD_FORMAT
mdefine_line|#define INT_CMD_FORMAT   0x06
DECL|macro|INT_CMD_ECC_RETRY
mdefine_line|#define INT_CMD_ECC_RETRY 0x07
DECL|macro|INT_CMD_WARNING
mdefine_line|#define INT_CMD_WARNING  0x08
DECL|macro|INT_CMD_ABORT
mdefine_line|#define INT_CMD_ABORT    0x09
DECL|macro|INT_RESET
mdefine_line|#define INT_RESET        0x0A
DECL|macro|INT_TRANSFER_REQ
mdefine_line|#define INT_TRANSFER_REQ 0x0B
DECL|macro|INT_CMD_FAILED
mdefine_line|#define INT_CMD_FAILED   0x0C
DECL|macro|INT_DMA_ERR
mdefine_line|#define INT_DMA_ERR      0x0D
DECL|macro|INT_CMD_BLK_ERR
mdefine_line|#define INT_CMD_BLK_ERR  0x0E
DECL|macro|INT_ATTN_ERROR
mdefine_line|#define INT_ATTN_ERROR   0x0F
DECL|macro|DMA_MASK_CHAN
mdefine_line|#define DMA_MASK_CHAN 0x90
DECL|macro|DMA_UNMASK_CHAN
mdefine_line|#define DMA_UNMASK_CHAN 0xA0
DECL|macro|DMA_WRITE_ADDR
mdefine_line|#define DMA_WRITE_ADDR 0x20
DECL|macro|DMA_WRITE_TC
mdefine_line|#define DMA_WRITE_TC 0x40
DECL|macro|DMA_WRITE_MODE
mdefine_line|#define DMA_WRITE_MODE 0x70
DECL|macro|CMD_GET_DEV_CONFIG
mdefine_line|#define CMD_GET_DEV_CONFIG 0x09
DECL|macro|CMD_READ
mdefine_line|#define CMD_READ 0x4601
DECL|macro|CMD_WRITE
mdefine_line|#define CMD_WRITE 0x4602
DECL|macro|DMA_READ_16
mdefine_line|#define DMA_READ_16 0x4C
DECL|macro|DMA_WRITE_16
mdefine_line|#define DMA_WRITE_16 0x44
DECL|macro|MB
mdefine_line|#define MB 1024*1024
DECL|macro|SECT_SIZE
mdefine_line|#define SECT_SIZE 512   
DECL|macro|ERROR
mdefine_line|#define ERROR 1
DECL|macro|OK
mdefine_line|#define OK 0
DECL|macro|HDIO_GETGEO
mdefine_line|#define HDIO_GETGEO 0x0301
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE !FALSE
DECL|struct|ps2esdi_geometry
r_struct
id|ps2esdi_geometry
(brace
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _PS2ESDI_H_ */
eof
