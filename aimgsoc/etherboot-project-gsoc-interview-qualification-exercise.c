/*
Question:

Implement a bit input stream API that callers use to read one or more bits from
an input file.  Normally file I/O is in units of bytes but some applications
such as decoders require bit-level I/O.

Example:
struct bit_input_stream bis;
bis_init ( &bis, stdin );
printf ( "0x%x\n", bis_get_bits ( &bis, 3 ) );
printf ( "%d\n", bis_is_eof ( &bis ) );
bis_get_bits ( &bis, 5 );
printf ( "%d\n", bis_is_eof ( &bis ) );

$ echo -ne '\x80' | ./bis
0x4
0
1

The first 3 bits of 0x80 are 100 in binary, which is 0x4 in hex.

The first eof output is 0 because we still have 5 bits left in the input
stream.  The second eof output is 1 because there are no bits remaining.

Your solution must provide the following API for reading 1 to 8 bits at a time:
*/

#include <stdint.h> /* for uint8_t */
#include <stdio.h>

/**
 * An input stream in units of bits
 */
struct bit_input_stream {
	/* The byte offset of byte in buffer */
	uint32_t byte;
	/* The bit offset of where next read is serviced from */
	uint8_t bit;
	/* The file */
	FILE *f;
	/* current and next bytes */
	char current;
	/* EOF indicator */
	int eof;
};

/**
 * Initialize the bit input stream given a file
 *
 * @v bis		Bit input stream
 * @v fp		Input file pointer
 */
static void bis_init ( struct bit_input_stream *bis, FILE *fp ) {
	bis->f = fp;
	bis->byte = 0;
	bis->bit = 0; 
	fread(&(bis->current), sizeof(bis->current), 1, bis->f);
	bis->eof = feof(bis->f);
}

/**
 * Check whether end-of-file has been reached
 *
 * @v bis		Bit input stream
 * @ret eof		1 on end-of-file, 0 otherwise
 */
static int bis_is_eof ( struct bit_input_stream *bis ) {
	return bis->eof;
}

/**
 * Fetch a number of bits from the input stream
 *
 * Limitations:- 
	1) Cannot read across a byte boundary.
 * @v bis		Bit input stream
 * @v n			Number of bits
 * @ret bits		Requested bits, filled from the right
 */
static uint8_t bis_get_bits ( struct bit_input_stream *bis, unsigned int n ) {
	/* mask = the lower n bits are 1, all others 0. i.e. 2^n - 1 */
	uint8_t mask = (1 << n) - 1;
	uint8_t data;


	/* Get the required n bits into lower n bits */
	data = bis->current >> ((7 - bis->bit) - (n - 1));
	
	/* Clear all higher bits */
	data &= mask;

	/* Increment bit offset */
	bis->bit = (bis->bit + n) % 8;

	if(bis->bit == 0) { /* Move to next byte */
		bis->byte++;
		fread(&(bis->current), sizeof(bis->current), 1, bis->f);
		bis->eof = feof(bis->f);
	}

	return data;
}


int main(void)
{
	FILE *fp = stdin;
	struct bit_input_stream bis;

	bis_init(&bis, fp);

	while(!bis_is_eof(&bis)) {
		printf ( "0x%x\n", bis_get_bits ( &bis, 3 ) );
		printf ( "%d\n", bis_is_eof ( &bis ) );
		printf ( "0x%x\n", bis_get_bits ( &bis, 5 ));
		printf ( "%d\n", bis_is_eof ( &bis ) );
	}

	return 0;
}

