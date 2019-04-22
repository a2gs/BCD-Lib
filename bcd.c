/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * BCD encoder
 * Packed. Big endian. No sign bit (4 bits used to represent 0x00 - 0x0Fh)
 *
 * MIT License
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


/* *** INCLUDES ************************************************************************ */
#include <string.h>

int compactAsciiStringToBcdPacked(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen)
{
	unsigned int posIn = 0, posOut = 0;
	unsigned char nibbleFlag = 0;
	unsigned char c = 0;

	if(bufOutLen < ((dataInLen/2) + 1))
		return(1);

	memset(bufOut, 0, bufOutLen);

	for(posIn = 0, posOut = 0, nibbleFlag = 0; posIn < dataInLen; posIn++){

		c = dataIn[posIn];

		if((c >= '0') && (c <= '9')) c -= '0';
		else{
			if     ((c == 'A') || (c == 'a')) c = 0x0a;
			else if((c == 'B') || (c == 'b')) c = 0x0b;
			else if((c == 'C') || (c == 'c')) c = 0x0c;
			else if((c == 'D') || (c == 'd')) c = 0x0d;
			else if((c == 'E') || (c == 'e')) c = 0x0e;
			else if((c == 'F') || (c == 'f')) c = 0x0f;
			else                              return(1);
		}

		if(nibbleFlag == 0){
			c <<= 4;
			bufOut[posOut] |= c;
			nibbleFlag = 1;
		}else{
			bufOut[posOut] |= c;
			posOut++;
			nibbleFlag = 0;
		}
	}

	return(0);
}

/* unsigned char nibbleToHexChar(unsigned char nibble)
 *
 * Return a ASCII character for a given binary (in hex) character
 * 0x05 return '5'
 * 0x0c return 'C' ...
 *
 * INPUT:
 *  Binary character
 * OUTPUT:
 *  ASCII character
 *  A space ' ' indicating error (input is not in 0x00 - 0x0Fh range)
 */
unsigned char nibbleToHexChar(unsigned char nibble)
{
	if((nibble >= 0) && (nibble <= 9)) return(nibble + '0');
	else{
		if     (nibble == 0x0a) return('a');
		else if(nibble == 0x0b) return('b');
		else if(nibble == 0x0c) return('c');
		else if(nibble == 0x0d) return('d');
		else if(nibble == 0x0e) return('e');
		else if(nibble == 0x0f) return('f');
		else                    return(' ');
	}
}

int extractBcdPackedToAsciiString(unsigned char *dataIn, size_t dataInLen, unsigned char *bufOut, size_t bufOutLen)
{
	unsigned int posIn = 0, posOut = 0;

	if(bufOutLen < (dataInLen/2))
		return(1);

	memset(bufOut, 0, bufOutLen);

	for(posIn = 0, posOut = 0; posIn < dataInLen; posIn++){
		bufOut[posOut++] = nibbleToHexChar(dataIn[posIn] >> 4);
		bufOut[posOut++] = nibbleToHexChar(dataIn[posIn] & 0x0f);
	}

	return(0);
}
