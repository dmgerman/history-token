multiline_comment|/*&n;   --------------------------------------------------------------------&n;   i2c-ite.h: Global defines for the I2C controller on board the    &n;                 ITE MIPS processor.                                &n;   --------------------------------------------------------------------&n;   Hai-Pao Fan, MontaVista Software, Inc.&n;   hpfan@mvista.com or source@mvista.com&n;&n;   Copyright 2001 MontaVista Software Inc.&n;&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; */
macro_line|#ifndef I2C_ITE_H
DECL|macro|I2C_ITE_H
mdefine_line|#define I2C_ITE_H 1
macro_line|#include &lt;asm/it8172/it8172.h&gt;
multiline_comment|/* I2C Registers */
DECL|macro|ITE_I2CHCR
mdefine_line|#define ITE_I2CHCR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x30
DECL|macro|ITE_I2CHSR
mdefine_line|#define ITE_I2CHSR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x34
DECL|macro|ITE_I2CSAR
mdefine_line|#define ITE_I2CSAR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x38
DECL|macro|ITE_I2CSSAR
mdefine_line|#define ITE_I2CSSAR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x3c
DECL|macro|ITE_I2CCKCNT
mdefine_line|#define ITE_I2CCKCNT&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x48
DECL|macro|ITE_I2CSHDR
mdefine_line|#define ITE_I2CSHDR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x4c
DECL|macro|ITE_I2CRSUR
mdefine_line|#define ITE_I2CRSUR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x50
DECL|macro|ITE_I2CPSUR
mdefine_line|#define ITE_I2CPSUR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x54
DECL|macro|ITE_I2CFDR
mdefine_line|#define ITE_I2CFDR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x70
DECL|macro|ITE_I2CFBCR
mdefine_line|#define ITE_I2CFBCR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x74
DECL|macro|ITE_I2CFCR
mdefine_line|#define ITE_I2CFCR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x78
DECL|macro|ITE_I2CFSR
mdefine_line|#define ITE_I2CFSR&t;IT8172_PCI_IO_BASE + IT_I2C_BASE + 0x7c
multiline_comment|/* Host Control Register ITE_I2CHCR */
DECL|macro|ITE_I2CHCR_HCE
mdefine_line|#define&t;ITE_I2CHCR_HCE&t;0x01&t;/* Enable I2C Host Controller */
DECL|macro|ITE_I2CHCR_IE
mdefine_line|#define&t;ITE_I2CHCR_IE&t;0x02&t;/* Enable the interrupt after completing&n;&t;&t;&t;&t;   the current transaction */
DECL|macro|ITE_I2CHCR_CP_W
mdefine_line|#define ITE_I2CHCR_CP_W&t;0x00&t;/* bit2-4 000 - Write */
DECL|macro|ITE_I2CHCR_CP_R
mdefine_line|#define&t;ITE_I2CHCR_CP_R&t;0x08&t;/*&t;  010 - Current address read */
DECL|macro|ITE_I2CHCR_CP_S
mdefine_line|#define&t;ITE_I2CHCR_CP_S&t;0x10&t;/*&t;  100 - Sequential read */
DECL|macro|ITE_I2CHCR_ST
mdefine_line|#define ITE_I2CHCR_ST&t;0x20&t;/* Initiates the I2C host controller to execute&n;&t;&t;&t;&t;   the command and send the data programmed in&n;&t;&t;&t;&t;   all required registers to I2C bus */
DECL|macro|ITE_CMD
mdefine_line|#define ITE_CMD&t;&t;ITE_I2CHCR_HCE | ITE_I2CHCR_IE | ITE_I2CHCR_ST
DECL|macro|ITE_WRITE
mdefine_line|#define ITE_WRITE&t;ITE_CMD | ITE_I2CHCR_CP_W
DECL|macro|ITE_READ
mdefine_line|#define ITE_READ&t;ITE_CMD | ITE_I2CHCR_CP_R
DECL|macro|ITE_SREAD
mdefine_line|#define ITE_SREAD&t;ITE_CMD | ITE_I2CHCR_CP_S
multiline_comment|/* Host Status Register ITE_I2CHSR */
DECL|macro|ITE_I2CHSR_DB
mdefine_line|#define&t;ITE_I2CHSR_DB&t;0x01&t;/* Device is busy, receives NACK response except&n;&t;&t;&t;&t;   in the first and last bytes */
DECL|macro|ITE_I2CHSR_DNE
mdefine_line|#define&t;ITE_I2CHSR_DNE&t;0x02&t;/* Target address on I2C bus does not exist */
DECL|macro|ITE_I2CHSR_TDI
mdefine_line|#define&t;ITE_I2CHSR_TDI&t;0x04&t;/* R/W Transaction on I2C bus was completed */
DECL|macro|ITE_I2CHSR_HB
mdefine_line|#define&t;ITE_I2CHSR_HB&t;0x08&t;/* Host controller is processing transactions */
DECL|macro|ITE_I2CHSR_FER
mdefine_line|#define&t;ITE_I2CHSR_FER&t;0x10&t;/* Error occurs in the FIFO */
multiline_comment|/* Slave Address Register ITE_I2CSAR */
DECL|macro|ITE_I2CSAR_SA_MASK
mdefine_line|#define&t;ITE_I2CSAR_SA_MASK&t;0xfe&t;/* Target I2C device address */
DECL|macro|ITE_I2CSAR_ASO
mdefine_line|#define&t;ITE_I2CSAR_ASO&t;&t;0x0100&t;/* Output 1/0 to I2CAS port when the&n;&t;&t;&t;&t;&t;   next slave address is addressed */
multiline_comment|/* Slave Sub-address Register ITE_I2CSSAR */
DECL|macro|ITE_I2CSSAR_SUBA_MASK
mdefine_line|#define&t;ITE_I2CSSAR_SUBA_MASK&t;0xff&t;/* Target I2C device sub-address */
multiline_comment|/* Clock Counter Register ITE_I2CCKCNT */
DECL|macro|ITE_I2CCKCNT_STOP
mdefine_line|#define&t;ITE_I2CCKCNT_STOP&t;0x00&t;/* stop I2C clock */
DECL|macro|ITE_I2CCKCNT_HPCC_MASK
mdefine_line|#define&t;ITE_I2CCKCNT_HPCC_MASK&t;0x7f&t;/* SCL high period counter */
DECL|macro|ITE_I2CCKCNT_LPCC_MASK
mdefine_line|#define&t;ITE_I2CCKCNT_LPCC_MASK&t;0x7f00&t;/* SCL low period counter */
multiline_comment|/* START Hold Time Register ITE_I2CSHDR */
multiline_comment|/* value is counted based on 16 MHz internal clock */
DECL|macro|ITE_I2CSHDR_FM
mdefine_line|#define ITE_I2CSHDR_FM&t;0x0a&t;/* START condition at fast mode */
DECL|macro|ITE_I2CSHDR_SM
mdefine_line|#define&t;ITE_I2CSHDR_SM&t;0x47&t;/* START contition at standard mode */
multiline_comment|/* (Repeated) START Setup Time Register ITE_I2CRSUR */
multiline_comment|/* value is counted based on 16 MHz internal clock */
DECL|macro|ITE_I2CRSUR_FM
mdefine_line|#define&t;ITE_I2CRSUR_FM&t;0x0a&t;/* repeated START condition at fast mode */
DECL|macro|ITE_I2CRSUR_SM
mdefine_line|#define&t;ITE_I2CRSUR_SM&t;0x50&t;/* repeated START condition at standard mode */
multiline_comment|/* STOP setup Time Register ITE_I2CPSUR */
multiline_comment|/* FIFO Data Register ITE_I2CFDR */
DECL|macro|ITE_I2CFDR_MASK
mdefine_line|#define&t;ITE_I2CFDR_MASK&t;&t;0xff
multiline_comment|/* FIFO Byte Count Register ITE_I2CFBCR */
DECL|macro|ITE_I2CFBCR_MASK
mdefine_line|#define ITE_I2CFBCR_MASK&t;0x3f
multiline_comment|/* FIFO Control Register ITE_I2CFCR */
DECL|macro|ITE_I2CFCR_FLUSH
mdefine_line|#define&t;ITE_I2CFCR_FLUSH&t;0x01&t;/* Flush FIFO and reset the FIFO point&n;&t;&t;&t;&t;&t;   and I2CFSR */
multiline_comment|/* FIFO Status Register ITE_I2CFSR */
DECL|macro|ITE_I2CFSR_FO
mdefine_line|#define&t;ITE_I2CFSR_FO&t;0x01&t;/* FIFO is overrun when write */
DECL|macro|ITE_I2CFSR_FU
mdefine_line|#define&t;ITE_I2CFSR_FU&t;0x02&t;/* FIFO is underrun when read */
DECL|macro|ITE_I2CFSR_FF
mdefine_line|#define&t;ITE_I2CFSR_FF&t;0x04&t;/* FIFO is full when write */
DECL|macro|ITE_I2CFSR_FE
mdefine_line|#define&t;ITE_I2CFSR_FE&t;0x08&t;/* FIFO is empty when read */
macro_line|#endif  /* I2C_ITE_H */
eof
