multiline_comment|/*&n; * FILE NAME: ocp_ids.h&n; *&n; * BRIEF MODULE DESCRIPTION: &n; * OCP device ids based on the ideas from PCI&n; *&n; * Maintained by: Armin &lt;akuster@mvista.com&gt;&n; *&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Version 1.0 08/22/02 -Armin&n; *  &t;initial release&n; */
multiline_comment|/*&n; * Vender  device&n; * [xxxx]  [xxxx]&n; *&n; *  Keep in order, please&n; */
multiline_comment|/* Vendor IDs 0x0001 - 0xFFFF copied from pci_ids.h */
DECL|macro|OCP_VENDOR_INVALID
mdefine_line|#define&t;OCP_VENDOR_INVALID&t;0x0000
DECL|macro|OCP_VENDOR_ARM
mdefine_line|#define&t;OCP_VENDOR_ARM&t;&t;0x0004
DECL|macro|OCP_VENDOR_IBM
mdefine_line|#define OCP_VENDOR_IBM&t;&t;0x1014
DECL|macro|OCP_VENDOR_MOTOROLA
mdefine_line|#define OCP_VENDOR_MOTOROLA&t;0x1057
DECL|macro|OCP_VENDOR_XILINX
mdefine_line|#define&t;OCP_VENDOR_XILINX&t;0x10ee
DECL|macro|OCP_VENDOR_UNKNOWN
mdefine_line|#define&t;OCP_VENDOR_UNKNOWN&t;0xFFFF
multiline_comment|/* device identification */
multiline_comment|/* define type */
DECL|macro|OCP_FUNC_INVALID
mdefine_line|#define OCP_FUNC_INVALID&t;0x0000
multiline_comment|/* system 0x0001 - 0x001F */
DECL|macro|OCP_FUNC_UIC
mdefine_line|#define&t;OCP_FUNC_UIC&t;&t;0x0001
multiline_comment|/* Timers 0x0020 - 0x002F */
DECL|macro|OCP_FUNC_GPT
mdefine_line|#define OCP_FUNC_GPT&t;&t;0x0020 &t;/* General purpose timers */
DECL|macro|OCP_FUNC_RTC
mdefine_line|#define OCP_FUNC_RTC&t;&t;0x0021
multiline_comment|/* Serial 0x0030 - 0x006F*/
DECL|macro|OCP_FUNC_16550
mdefine_line|#define OCP_FUNC_16550&t;&t;0x0031 
DECL|macro|OCP_FUNC_SSP
mdefine_line|#define OCP_FUNC_SSP&t;&t;0x0032 /* sync serial port */
DECL|macro|OCP_FUNC_SCP
mdefine_line|#define OCP_FUNC_SCP&t;&t;0x0033 &t;/* serial controller port */
DECL|macro|OCP_FUNC_SCC
mdefine_line|#define OCP_FUNC_SCC&t;&t;0x0034 &t;/* serial contoller */
DECL|macro|OCP_FUNC_SCI
mdefine_line|#define OCP_FUNC_SCI&t;&t;0x0035 &t;/* Smart card */
DECL|macro|OCP_FUNC_IIC
mdefine_line|#define OCP_FUNC_IIC&t;&t;0x0040 
DECL|macro|OCP_FUNC_USB
mdefine_line|#define OCP_FUNC_USB&t;&t;0x0050 
DECL|macro|OCP_FUNC_IR
mdefine_line|#define OCP_FUNC_IR&t;&t;0x0060&t;&t;
multiline_comment|/* Memory devices 0x0090 - 0x009F */
DECL|macro|OCP_FUNC_SDRAM
mdefine_line|#define&t;OCP_FUNC_SDRAM&t;&t;0x0091
DECL|macro|OCP_FUNC_DMA
mdefine_line|#define OCP_FUNC_DMA&t;&t;0x0092
multiline_comment|/* Display 0x00A0 - 0x00AF */
DECL|macro|OCP_FUNC_VIDEO
mdefine_line|#define OCP_FUNC_VIDEO&t;&t;0x00A0 
DECL|macro|OCP_FUNC_LED
mdefine_line|#define OCP_FUNC_LED&t;&t;0x00A1
DECL|macro|OCP_FUNC_LCD
mdefine_line|#define&t;OCP_FUNC_LCD&t;&t;0x00A2
multiline_comment|/* Sound 0x00B0 - 0x00BF */
DECL|macro|OCP_FUNC_AUDIO
mdefine_line|#define OCP_FUNC_AUDIO&t;&t;0x00B0 
multiline_comment|/* Mass Storage 0x00C0 - 0xxCF */
DECL|macro|OCP_FUNC_IDE
mdefine_line|#define OCP_FUNC_IDE&t;&t;0x00C0 
multiline_comment|/* Misc 0x00D0 - 0x00DF*/
DECL|macro|OCP_FUNC_GPIO
mdefine_line|#define OCP_FUNC_GPIO&t;&t;0x00D0 
DECL|macro|OCP_FUNC_ZMII
mdefine_line|#define OCP_FUNC_ZMII&t;&t;0x00D1
multiline_comment|/* Network 0x0200 - 0x02FF */
DECL|macro|OCP_FUNC_EMAC
mdefine_line|#define OCP_FUNC_EMAC&t;&t;0x0200 
multiline_comment|/* Bridge devices 0xE00 - 0xEFF */
DECL|macro|OCP_FUNC_HOST
mdefine_line|#define OCP_FUNC_HOST&t;&t;0x0E00 
DECL|macro|OCP_FUNC_DCR
mdefine_line|#define OCP_FUNC_DCR&t;&t;0x0E01 
DECL|macro|OCP_FUNC_OPB
mdefine_line|#define OCP_FUNC_OPB&t;&t;0x0E02
DECL|macro|OCP_FUNC_PHY
mdefine_line|#define OCP_FUNC_PHY&t;&t;0x0E03
DECL|macro|OCP_FUNC_EXT
mdefine_line|#define OCP_FUNC_EXT&t;&t;0x0E04
DECL|macro|OCP_FUNC_PCI
mdefine_line|#define&t;OCP_FUNC_PCI&t;&t;0x0E05
DECL|macro|OCP_FUNC_PLB
mdefine_line|#define&t;OCP_FUNC_PLB&t;&t;0x0E06
DECL|macro|OCP_FUNC_UNKNOWN
mdefine_line|#define OCP_FUNC_UNKNOWN&t;0xFFFF
eof
