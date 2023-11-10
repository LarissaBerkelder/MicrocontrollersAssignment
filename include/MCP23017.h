#define MCP23017_ID    0x40
#define MCP23017_ADDR  0x00
#define IODIRA         0x00
#define GPIOA          0x12
#define GPPUA          0x0C
#define ACK 1
#define NACK 0

void Write_MCP23017(unsigned char reg_addr, unsigned char data);
unsigned char Read_MCP23017(unsigned char reg_addr);
void MCP23017_INIT();