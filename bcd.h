/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * BCD encoder
 * Packed. Big endian. No sign bit (4 bits used to represent 0x00 - 0x0Fh)
 *
 * Public Domain
 *
 */

/* bcd.c
 * BCD encoder/decoder
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 28/01/2019 | Creation
 *          |            |
 */


#ifndef __BCD_H__
#define __BCD_H__

/* *** INTERFACES / PROTOTYPES *************************************** */
/* int compactAsciiStringToBcdPacked(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen)
 *
 * Transforms a ASCII string expressed Hex values to a BCD buffer (1 bcd byte for 2 hex numbers 0x00 - 0x0Fh)
 *
 * INPUT:
 *  dataIn - Hex values expressed in ASCII
 *  dataInLen - dataIn size
 *  bufOutLen - bufOut (it MUST BE greatest than ((dataInLen/2)+1) or more)
 * OUTPUT:
 *  bufOut - Preallocad buffer to receives BCD data
 * RETURN:
 *  0 - Ok
 *  1 - NOK (maybe bufOutLen is smaller than necessary)
 */
int compactAsciiStringToBcdPacked(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen);

/* int extractBcdPackedToAsciiString(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen)
 *
 * Transforms a BCD buffer (binary data) to a ASCII represetantion (in hex)
 *
 * INPUT:
 *  dataIn - Binary (hex) values
 *  dataInLen - dataIn size
 *  bufOutLen - bufOut (it MUST BE greatest than (dataInLen*2) or more)
 * OUTPUT:
 *  bufOut - Preallocad buffer to receives ASCII data (expressed in hex values)
 * RETURN:
 *  0 - Ok
 *  1 - NOK (maybe bufOutLen is smaller than necessary)
 */
int extractBcdPackedToAsciiString(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen);

/* *** EXAMPLE ******************************************************* */
#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	unsigned char dataAscii[]="25fbde9a9";
	unsigned char *bufOutToBCDFixed = NULL;
	size_t bufOutToBCDFixedSz = 0;
	unsigned char *bufOutFromBCDFixed = NULL;
	size_t bufOutFromBCDFixedSz = 0;
	int i = 0;
	int ret = 0;

	printf("Dados nao BCD: [%s]\n\n", dataAscii);

	bufOutToBCDFixedSz = (strlen((const char *) dataAscii)/2) + 1;
	bufOutToBCDFixed = malloc(bufOutToBCDFixedSz);
	if(bufOutToBCDFixed == NULL){
		printf("Erro malloc() 1.\n");
		return(1);
	}

	ret = compactAsciiStringToBcdPacked(dataAscii, strlen((const char *) dataAscii), bufOutToBCDFixed, bufOutToBCDFixedSz);
	if(ret != 0){
		printf("Erro compactAsciiStringToBcdPacked().\n");
		return(1);
	}

	printf("Dump to BCD (%ld bytes): ", bufOutToBCDFixedSz);

	for(i = 0; i < bufOutToBCDFixedSz; i++)
		printf("0x%02X ", bufOutToBCDFixed[i]);

	printf("\n\n");

	/* --- */

	bufOutFromBCDFixedSz = (bufOutToBCDFixedSz * 2);
	bufOutFromBCDFixed = malloc(bufOutFromBCDFixedSz);
	if(bufOutFromBCDFixed == NULL){
		printf("Erro malloc() 2.\n");
		return(1);
	}

	ret = extractBcdPackedToAsciiString(bufOutToBCDFixed, bufOutToBCDFixedSz, bufOutFromBCDFixed, bufOutFromBCDFixedSz);
	if(ret != 0){
		printf("Erro extractBcdPackedToAsciiString().\n");
		return(1);
	}

	printf("Dump from BCD (%ld bytes): \"", bufOutFromBCDFixedSz);

	for(i = 0; i < bufOutFromBCDFixedSz; i++)
		printf("%c", bufOutFromBCDFixed[i]);

	printf("\"\n");

	/* --- */

	free(bufOutToBCDFixed);
	free(bufOutFromBCDFixed);

	return(0);
}
#endif

#endif
