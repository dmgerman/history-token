DECL|macro|MMC_STRPCL
macro_line|#undef MMC_STRPCL
DECL|macro|MMC_STAT
macro_line|#undef MMC_STAT
DECL|macro|MMC_CLKRT
macro_line|#undef MMC_CLKRT
DECL|macro|MMC_SPI
macro_line|#undef MMC_SPI
DECL|macro|MMC_CMDAT
macro_line|#undef MMC_CMDAT
DECL|macro|MMC_RESTO
macro_line|#undef MMC_RESTO
DECL|macro|MMC_RDTO
macro_line|#undef MMC_RDTO
DECL|macro|MMC_BLKLEN
macro_line|#undef MMC_BLKLEN
DECL|macro|MMC_NOB
macro_line|#undef MMC_NOB
DECL|macro|MMC_PRTBUF
macro_line|#undef MMC_PRTBUF
DECL|macro|MMC_I_MASK
macro_line|#undef MMC_I_MASK
DECL|macro|END_CMD_RES
macro_line|#undef END_CMD_RES
DECL|macro|PRG_DONE
macro_line|#undef PRG_DONE
DECL|macro|DATA_TRAN_DONE
macro_line|#undef DATA_TRAN_DONE
DECL|macro|MMC_I_REG
macro_line|#undef MMC_I_REG
DECL|macro|MMC_CMD
macro_line|#undef MMC_CMD
DECL|macro|MMC_ARGH
macro_line|#undef MMC_ARGH
DECL|macro|MMC_ARGL
macro_line|#undef MMC_ARGL
DECL|macro|MMC_RES
macro_line|#undef MMC_RES
DECL|macro|MMC_RXFIFO
macro_line|#undef MMC_RXFIFO
DECL|macro|MMC_TXFIFO
macro_line|#undef MMC_TXFIFO
DECL|macro|MMC_STRPCL
mdefine_line|#define MMC_STRPCL&t;0x0000
DECL|macro|STOP_CLOCK
mdefine_line|#define STOP_CLOCK&t;&t;(1 &lt;&lt; 0)
DECL|macro|START_CLOCK
mdefine_line|#define START_CLOCK&t;&t;(2 &lt;&lt; 0)
DECL|macro|MMC_STAT
mdefine_line|#define MMC_STAT&t;0x0004
DECL|macro|STAT_END_CMD_RES
mdefine_line|#define STAT_END_CMD_RES&t;&t;(1 &lt;&lt; 13)
DECL|macro|STAT_PRG_DONE
mdefine_line|#define STAT_PRG_DONE&t;&t;&t;(1 &lt;&lt; 12)
DECL|macro|STAT_DATA_TRAN_DONE
mdefine_line|#define STAT_DATA_TRAN_DONE&t;&t;(1 &lt;&lt; 11)
DECL|macro|STAT_CLK_EN
mdefine_line|#define STAT_CLK_EN&t;&t;&t;(1 &lt;&lt; 8)
DECL|macro|STAT_RECV_FIFO_FULL
mdefine_line|#define STAT_RECV_FIFO_FULL&t;&t;(1 &lt;&lt; 7)
DECL|macro|STAT_XMIT_FIFO_EMPTY
mdefine_line|#define STAT_XMIT_FIFO_EMPTY&t;&t;(1 &lt;&lt; 6)
DECL|macro|STAT_RES_CRC_ERR
mdefine_line|#define STAT_RES_CRC_ERR&t;&t;(1 &lt;&lt; 5)
DECL|macro|STAT_SPI_READ_ERROR_TOKEN
mdefine_line|#define STAT_SPI_READ_ERROR_TOKEN&t;(1 &lt;&lt; 4)
DECL|macro|STAT_CRC_READ_ERROR
mdefine_line|#define STAT_CRC_READ_ERROR&t;&t;(1 &lt;&lt; 3)
DECL|macro|STAT_CRC_WRITE_ERROR
mdefine_line|#define STAT_CRC_WRITE_ERROR&t;&t;(1 &lt;&lt; 2)
DECL|macro|STAT_TIME_OUT_RESPONSE
mdefine_line|#define STAT_TIME_OUT_RESPONSE&t;&t;(1 &lt;&lt; 1)
DECL|macro|STAT_READ_TIME_OUT
mdefine_line|#define STAT_READ_TIME_OUT&t;&t;(1 &lt;&lt; 0)
DECL|macro|MMC_CLKRT
mdefine_line|#define MMC_CLKRT&t;0x0008&t;&t;/* 3 bit */
DECL|macro|MMC_SPI
mdefine_line|#define MMC_SPI&t;&t;0x000c
DECL|macro|SPI_CS_ADDRESS
mdefine_line|#define SPI_CS_ADDRESS&t;&t;(1 &lt;&lt; 3)
DECL|macro|SPI_CS_EN
mdefine_line|#define SPI_CS_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|CRC_ON
mdefine_line|#define CRC_ON&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|SPI_EN
mdefine_line|#define SPI_EN&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|MMC_CMDAT
mdefine_line|#define MMC_CMDAT&t;0x0010
DECL|macro|CMDAT_DMAEN
mdefine_line|#define CMDAT_DMAEN&t;&t;(1 &lt;&lt; 7)
DECL|macro|CMDAT_INIT
mdefine_line|#define CMDAT_INIT&t;&t;(1 &lt;&lt; 6)
DECL|macro|CMDAT_BUSY
mdefine_line|#define CMDAT_BUSY&t;&t;(1 &lt;&lt; 5)
DECL|macro|CMDAT_STREAM
mdefine_line|#define CMDAT_STREAM&t;&t;(1 &lt;&lt; 4)&t;/* 1 = stream */
DECL|macro|CMDAT_WRITE
mdefine_line|#define CMDAT_WRITE&t;&t;(1 &lt;&lt; 3)&t;/* 1 = write */
DECL|macro|CMDAT_DATAEN
mdefine_line|#define CMDAT_DATAEN&t;&t;(1 &lt;&lt; 2)
DECL|macro|CMDAT_RESP_NONE
mdefine_line|#define CMDAT_RESP_NONE&t;&t;(0 &lt;&lt; 0)
DECL|macro|CMDAT_RESP_SHORT
mdefine_line|#define CMDAT_RESP_SHORT&t;(1 &lt;&lt; 0)
DECL|macro|CMDAT_RESP_R2
mdefine_line|#define CMDAT_RESP_R2&t;&t;(2 &lt;&lt; 0)
DECL|macro|CMDAT_RESP_R3
mdefine_line|#define CMDAT_RESP_R3&t;&t;(3 &lt;&lt; 0)
DECL|macro|MMC_RESTO
mdefine_line|#define MMC_RESTO&t;0x0014&t;/* 7 bit */
DECL|macro|MMC_RDTO
mdefine_line|#define MMC_RDTO&t;0x0018&t;/* 16 bit */
DECL|macro|MMC_BLKLEN
mdefine_line|#define MMC_BLKLEN&t;0x001c&t;/* 10 bit */
DECL|macro|MMC_NOB
mdefine_line|#define MMC_NOB&t;&t;0x0020&t;/* 16 bit */
DECL|macro|MMC_PRTBUF
mdefine_line|#define MMC_PRTBUF&t;0x0024
DECL|macro|BUF_PART_FULL
mdefine_line|#define BUF_PART_FULL&t;&t;(1 &lt;&lt; 0)
DECL|macro|MMC_I_MASK
mdefine_line|#define MMC_I_MASK&t;0x0028
multiline_comment|/*PXA27x MMC interrupts*/
DECL|macro|SDIO_SUSPEND_ACK
mdefine_line|#define SDIO_SUSPEND_ACK  &t;(1 &lt;&lt; 12)
DECL|macro|SDIO_INT
mdefine_line|#define SDIO_INT          &t;(1 &lt;&lt; 11)
DECL|macro|RD_STALLED
mdefine_line|#define RD_STALLED        &t;(1 &lt;&lt; 10)
DECL|macro|RES_ERR
mdefine_line|#define RES_ERR           &t;(1 &lt;&lt; 9)
DECL|macro|DAT_ERR
mdefine_line|#define DAT_ERR           &t;(1 &lt;&lt; 8)
DECL|macro|TINT
mdefine_line|#define TINT              &t;(1 &lt;&lt; 7)
multiline_comment|/*PXA2xx MMC interrupts*/
DECL|macro|TXFIFO_WR_REQ
mdefine_line|#define TXFIFO_WR_REQ&t;&t;(1 &lt;&lt; 6)
DECL|macro|RXFIFO_RD_REQ
mdefine_line|#define RXFIFO_RD_REQ&t;&t;(1 &lt;&lt; 5)
DECL|macro|CLK_IS_OFF
mdefine_line|#define CLK_IS_OFF&t;&t;(1 &lt;&lt; 4)
DECL|macro|STOP_CMD
mdefine_line|#define STOP_CMD&t;&t;(1 &lt;&lt; 3)
DECL|macro|END_CMD_RES
mdefine_line|#define END_CMD_RES&t;&t;(1 &lt;&lt; 2)
DECL|macro|PRG_DONE
mdefine_line|#define PRG_DONE&t;&t;(1 &lt;&lt; 1)
DECL|macro|DATA_TRAN_DONE
mdefine_line|#define DATA_TRAN_DONE&t;&t;(1 &lt;&lt; 0)
macro_line|#ifdef CONFIG_PXA27x
DECL|macro|MMC_I_MASK_ALL
mdefine_line|#define MMC_I_MASK_ALL          0x00001fff
macro_line|#else
DECL|macro|MMC_I_MASK_ALL
mdefine_line|#define MMC_I_MASK_ALL          0x0000007f
macro_line|#endif
DECL|macro|MMC_I_REG
mdefine_line|#define MMC_I_REG&t;0x002c
multiline_comment|/* same as MMC_I_MASK */
DECL|macro|MMC_CMD
mdefine_line|#define MMC_CMD&t;&t;0x0030
DECL|macro|MMC_ARGH
mdefine_line|#define MMC_ARGH&t;0x0034&t;/* 16 bit */
DECL|macro|MMC_ARGL
mdefine_line|#define MMC_ARGL&t;0x0038&t;/* 16 bit */
DECL|macro|MMC_RES
mdefine_line|#define MMC_RES&t;&t;0x003c&t;/* 16 bit */
DECL|macro|MMC_RXFIFO
mdefine_line|#define MMC_RXFIFO&t;0x0040&t;/* 8 bit */
DECL|macro|MMC_TXFIFO
mdefine_line|#define MMC_TXFIFO&t;0x0044&t;/* 8 bit */
multiline_comment|/*&n; * The base MMC clock rate&n; */
macro_line|#ifdef CONFIG_PXA27x
DECL|macro|CLOCKRATE_MIN
mdefine_line|#define CLOCKRATE_MIN&t;304688
DECL|macro|CLOCKRATE_MAX
mdefine_line|#define CLOCKRATE_MAX&t;19500000
macro_line|#else
DECL|macro|CLOCKRATE_MIN
mdefine_line|#define CLOCKRATE_MIN&t;312500
DECL|macro|CLOCKRATE_MAX
mdefine_line|#define CLOCKRATE_MAX&t;20000000
macro_line|#endif
DECL|macro|CLOCKRATE
mdefine_line|#define CLOCKRATE&t;CLOCKRATE_MAX
eof
