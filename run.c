#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <assert.h>

void cobs_encode(const uint8_t* input, int len, uint8_t* output);
void cobs_decode(const uint8_t* input, uint8_t* output);
void cobs64_encode(const uint64_t* input, int len, uint64_t* output);
void cobs64_decode(const uint64_t* input, uint64_t* output);
void z2_encode(const uint64_t* input, int len, uint64_t* output);
void z2_decode(const uint64_t* input, uint64_t* output);
void evenify_encode(const uint64_t* input, int len, uint64_t* output);
void evenify_decode(const uint64_t* input, uint64_t* output);
void oddify_encode(const uint64_t* input, int len, uint64_t* output);
void oddify_decode(const uint64_t* input, uint64_t* output);

static void _cobs8_encode(const uint64_t* input, int len, uint64_t* output)
{
	cobs_encode((uint8_t*)input, 8*len, (uint8_t*)output);
}

static void _cobs8_decode(const uint64_t* input, uint64_t* output)
{
	cobs_decode((uint8_t*)input, (uint8_t*)output);
}

static void _memcpy_encode(const uint64_t* input, int len, uint64_t* output)
{
	*output++ = 8*len;
	memcpy(output, input, output[-1]);
}

static void _memcpy_decode(const uint64_t* input, uint64_t* output)
{
	int len = *input++;
	memcpy(output, input, len);
}

static uint64_t _get_us(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000 + tv.tv_usec;
}

static void _test(const char* name, const uint64_t* data, int len, uint64_t* encoded, uint64_t* decoded,
		void (*encode)(const uint64_t* input, int len, uint64_t* output),
		void (*decode)(const uint64_t* input, uint64_t* output))
{
	memset(encoded, 0, len);
	memset(decoded, 0, len);

	uint64_t encode_us = _get_us();
	encode(data, len, encoded);
	encode_us = _get_us() - encode_us;

	uint64_t decode_us = _get_us();
	decode(encoded, decoded);
	decode_us = _get_us() - decode_us;

	bool success = true;
	for (int i = 0; i < len && success; i++)
	{
		success = data[i] == decoded[i];
		if (!success)
		{
			printf("ERR %i %016lx != %016lx\n", i, data[i], decoded[i]);
		}
	}

	uint64_t total_us = encode_us + decode_us;
	float gibs = len*0.008f/total_us;
	printf("[%4s]%-10s %5i MiB, enc %10.3lf, dec %10.3lf, total %10.3lf [ms] %3.3lf GiB/s\n", success ? "OK" : "FAIL", name, len>>17, encode_us/1000.0f, decode_us/1000.0f, total_us/1000.0f, gibs);
}

int main(int argn, char* argv[])
{
	const int LEN = 1024*1024*1024;
	uint64_t* data = malloc(LEN);
	uint64_t* encoded = malloc(LEN + LEN/10);
	uint64_t* decoded = malloc(LEN);

	printf("dry run\n");
	_test("memcpy", data, LEN/8, encoded, decoded, _memcpy_encode, _memcpy_decode);
	_test("COBS", data, LEN/8, encoded, decoded, _cobs8_encode, _cobs8_decode);
	_test("COBS64", data, LEN/8, encoded, decoded, cobs64_encode, cobs64_decode);
	_test("z2", data, LEN/8, encoded, decoded, z2_encode, z2_decode);
	_test("evenify", data, LEN/8, encoded, decoded, evenify_encode, evenify_decode);
	_test("oddify", data, LEN/8, encoded, decoded, oddify_encode, oddify_decode);

	for (int i = 0; i < LEN; i++)
	{
		((uint8_t*)data)[i] = 0;
	}
	printf("zero data\n");
	_test("memcpy", data, LEN/8, encoded, decoded, _memcpy_encode, _memcpy_decode);
	_test("COBS", data, LEN/8, encoded, decoded, _cobs8_encode, _cobs8_decode);
	_test("COBS64", data, LEN/8, encoded, decoded, cobs64_encode, cobs64_decode);
	_test("z2", data, LEN/8, encoded, decoded, z2_encode, z2_decode);
	_test("evenify", data, LEN/8, encoded, decoded, evenify_encode, evenify_decode);
	_test("oddify", data, LEN/8, encoded, decoded, oddify_encode, oddify_decode);

	for (int i = 0; i < LEN; i++)
	{
		((uint8_t*)data)[i] = 0xff;
	}
	printf("0xff data\n");
	_test("memcpy", data, LEN/8, encoded, decoded, _memcpy_encode, _memcpy_decode);
	_test("COBS", data, LEN/8, encoded, decoded, _cobs8_encode, _cobs8_decode);
	_test("COBS64", data, LEN/8, encoded, decoded, cobs64_encode, cobs64_decode);
	_test("z2", data, LEN/8, encoded, decoded, z2_encode, z2_decode);
	_test("evenify", data, LEN/8, encoded, decoded, evenify_encode, evenify_decode);
	_test("oddify", data, LEN/8, encoded, decoded, oddify_encode, oddify_decode);

	for (int i = 0; i < LEN; i++)
	{
		((uint8_t*)data)[i] = rand();
	}
	printf("pseudo data\n");
	_test("memcpy", data, LEN/8, encoded, decoded, _memcpy_encode, _memcpy_decode);
	_test("COBS", data, LEN/8, encoded, decoded, _cobs8_encode, _cobs8_decode);
	_test("COBS64", data, LEN/8, encoded, decoded, cobs64_encode, cobs64_decode);
	_test("z2", data, LEN/8, encoded, decoded, z2_encode, z2_decode);
	_test("evenify", data, LEN/8, encoded, decoded, evenify_encode, evenify_decode);
	_test("oddify", data, LEN/8, encoded, decoded, oddify_encode, oddify_decode);
}
