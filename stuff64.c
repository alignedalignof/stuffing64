#include <stdint.h>

void cobs_encode(const uint8_t* input, int len, uint8_t* output)
{
	uint8_t* stuff = output++;
	uint8_t s = 1;
	while (len--)
	{
		if (*input)
		{
			s++;
			*output++ = *input;
		}
		if (!*input || s == 255)
		{
			*stuff = s;
			stuff = output++;
			s = 1;
		}
		input++;
	}
	*stuff = s;
	*output = 0;
}

void cobs_decode(const uint8_t* input, uint8_t* output)
{
	uint8_t stuff = *input++;
	while (stuff)
	{
		for (int i = 1; i < stuff; i++)
		{
			*output++ = *input++;
			if (!output[-1])
			{
				return;
			}
		}
		if (stuff < 255)
		{
			*output++ = 0;
		}
		stuff = *input++;
	}
}

void cobs64_encode(const uint64_t* input, int len, uint64_t* output)
{
	uint8_t* stuff = (uint8_t*)output++;
	uint8_t s = 1;
	while (len--)
	{
		uint8_t ones = (uint8_t)*input != 0;
		if (ones)
		{
			s++;
		}
		*output = *input;
		output += ones;
		if (!ones || s == 255)
		{
			*stuff = s;
			stuff = (uint8_t*)output++;
			s = 1;
		}
		input++;
	}
	*stuff = s;
	*output = 0;
}

void cobs64_decode(const uint64_t* input, uint64_t* output)
{
	uint8_t stuff =  (uint8_t)*input++;
	while (stuff)
	{
		for (int i = 1; i < stuff; i++)
		{
			*output++ = *input++;
			if (!output[-1])
			{
				return;
			}
		}
		if (stuff < 255)
		{
			*output++ = *input & ~0xffULL;
		}
		stuff = (uint8_t)*input++;
	}
}

void z2_encode(const uint64_t* input, int len, uint64_t* output)
{
	while (len)
	{
		if ((char)*input == 0 || (char)*input == 2)
		{
			uint64_t* stuff =  output++;
			uint64_t s = 0;
			int l = (len > 56) ? 56 : len;
			output += l;
			input += l;
			len -= l++;
			for (int i = 1; i < l; i++)
			{
				s = (s << 1) | !(input[-i] & 1);
				output[-i] = input[-i] ^ s;
			}
			*stuff = (s << 8) | 2;
		}
		else
		{
			*output++ = *input++;
			len--;
		}

	}
	*output = 0;
}

void z2_decode(const uint64_t* input, uint64_t* output)
{
	while (*input)
	{
		if ((char)*input == 2)
		{
			uint64_t stuff = *input++ >> 8;
			while (stuff && (*input))
			{
				*output++ = *input++ ^ stuff;
				stuff >>= 1;
			}
		}
		else
		{
			*output++ = *input++;
		}
	}
}

void evenify_encode(const uint64_t* input, int len, uint64_t* output)
{
	while (len)
	{
		uint64_t* stuff = output++;
		uint64_t s = 0;
		int l = (len > 63) ? 63 : len;
		output += l;
		input += l;
		len -= l++;
		for (int i = 1; i < l; i++)
		{
			s = (s << 1) | (input[-i] & 1);
			output[-i] = input[-i] & ~1;
		}
		s <<= 1;
		*stuff = s;
	}
	*output = ~0ULL;
}

void evenify_decode(const uint64_t* input, uint64_t* output)
{
	uint64_t stuff = 0;
	while (!(*input & 1))
	{
		stuff = *input++;
		stuff = (1ULL << 63) | (stuff >> 1);
		while (stuff > 1 && !(*input & 1))
		{
			*output++ = *input++ | (stuff & 1);
			stuff >>= 1;
		}
	}
}

void oddify_encode(const uint64_t* input, int len, uint64_t* output)
{
	while (len)
	{
		uint64_t* stuff = output++;
		uint64_t s = 0;
		int i = 63;
		for (; i && len; i--, len--)
		{
			s = (s << 1) | !(*input & 1);
			*output++ = *input++ ^ s;
		}
		s <<= i;
		*stuff = (s << 1) | 1;
	}
	*output = 0;
}

void oddify_decode(const uint64_t* input, uint64_t* output)
{
	uint64_t stuff = 0;
	while (*input & 1)
	{
		stuff = *input++;
		for (int i = 63; i && (*input & 1); i--)
		{
			*output++ = *input++ ^ (stuff >> i);
		}
	}
}
