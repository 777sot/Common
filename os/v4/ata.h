#ifndef _ATA_H
#define _ATA_H

#define ATA_PRIMARY_MASTER		0x0
#define ATA_PRIMARY_SLAVE		0x1
#define ATA_SECONDARY_MASTER	0x2
#define ATA_SECONDARY_SLAVE		0x3

#define PRIMARY_MASTER_DRIVE	ATA_PRIMARY_MASTER
#define PRIMARY_SLAVE_DRIVE		ATA_PRIMARY_SLAVE
#define SECONDARY_MASTER_DRIVE	ATA_SECONDARY_MASTER
#define SECONDARY_SLAVE_DRIVE	ATA_SECONDARY_SLAVE

#define ATA_COMMAND_READ_DMA 0xc8

#define ATA_SLAVE	0xf0
#define ATA_MASTER	0xe0

#define ATA_PRIMARY_DATA_PORT		0x1f0
#define ATA_PRIMARY_ERROR_PORT		0x1f1
#define ATA_PRIMARY_FEATURE_PORT	0x1f1
#define ATA_PRIMARY_COUNTER_PORT	0x1f2
#define ATA_PRIMARY_LBA0_PORT		0x1f3
#define ATA_PRIMARY_LBA1_PORT		0x1f4
#define ATA_PRIMARY_LBA2_PORT		0x1f5
#define ATA_PRIMARY_LBA3_PORT		0x1f6
#define ATA_PRIMARY_STATE_PORT		0x1f7
#define ATA_PRIMARY_COMMAND_PORT	0x1f7
#define ATA_PRIMARY_STATE_ALT_PORT	0x3f6
#define ATA_PRIMARY_CONTROL_PORT	0x3f6

#define ATA_PRIMARY_WAIT_WHILE_BUSY() while(inb(ATA_PRIMARY_STATE_ALT_PORT) & 0x80)
#define ATA_PRIMARY_CLI() outb(ATA_PRIMARY_CONTROL_PORT, 0x2)
#define ATA_PRIMARY_STI() outb(ATA_PRIMARY_CONTROL_PORT, 0x0)
#define ATA_PRIMARY_SET_LBA(LBA, COUNTER, MASTER_OR_SLAVE) \
	outb(ATA_PRIMARY_LBA3_PORT, (byte)((LBA) >> 24) | (MASTER_OR_SLAVE)); \
	while((inb(ATA_PRIMARY_STATE_ALT_PORT) & 0xc0) != 0x40); \
	outb(ATA_PRIMARY_COUNTER_PORT, (COUNTER)); \
	outb(ATA_PRIMARY_LBA0_PORT, (byte)(LBA)); \
	outb(ATA_PRIMARY_LBA1_PORT, (byte)((LBA) >> 8)); \
	outb(ATA_PRIMARY_LBA2_PORT, (byte)((LBA) >> 16))
#define ATA_PRIMARY_SEND_COMMAND(COMMAND) \
	outb(ATA_PRIMARY_COMMAND_PORT, (COMMAND)); \
	while((inb(ATA_PRIMARY_STATE_PORT) & 0x88) != 0x8)
#define ATA_DMA_LOAD_PRDT(PORT, PRDT) outdw((PORT) + 0x4, (PRDT))
#define ATA_DMA_SET_DIRECTION_TO_MEMOMY(PORT) outb((PORT) + 0x8, 0x8)
#define ATA_DMA_ENABLE_BUS_MASTER(PORT) outb((PORT), 0x9)
#define ATA_DMA_DISABLE_BUS_MASTER(PORT) outb((PORT), 0x0)
#define ATA_DMA_WAIT_WHILE_AC(PORT) while(inb((PORT) + 0x2) & 0x1)

#endif
