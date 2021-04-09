

// Returns the no. of characters in a string
uint32_t my_strlen(uint8_t *);

// Compares n bytes of 'src' and 'destination' string. Returns 0 if same, -1 if not
uint32_t my_strncmp(uint8_t *, uint8_t *, uint32_t );

// Concatenates 'n' bytes of 'src' string to destination string 
uint32_t my_strncat(uint8_t *, uint8_t *, uint32_t );

// Copies 'n' bytes from source to destination and returns 0 on success and -1 on failure
uint32_t my_strncpy(uint8_t *, uint8_t *, uint32_t);

// Returns a copy of malloc'ed string or NULL on failure
uint8_t *my_strdup(uint8_t *);



uint32_t my_strlen(uint8_t *str)
{
	uint8_t *ptr = str;
	uint32_t length = 0;

	while (*(ptr++) != '\x00')
	{
		++length;
	}	

	return length;
}


uint32_t my_strncmp(uint8_t *dest, uint8_t *src, uint32_t n)
{
	uint32_t i=0;

	for (i = 0; i < n; ++i)
	{
		// i has not parsed n chars yet either the 'src' or 'dest' string is ended with a NULL char
		if ( (i < n) && (*(src + i) == '\x00' || *(dest + i) == '\x00') )
		{
			fprintf(stderr, "Could match only %d characters\n", i);
			return -1;
		}

		// if not same characters at a position
		else if ( *(src + i) != *(dest + i) )
			return -1;	
	}

	// Means the loop parsed the string till n chars and all characters in 'src' string seems to match
	// characters in 'dest' string 
	if (i == n)
		return 0;
}


uint32_t my_strncat(uint8_t *src, uint8_t *dest, uint32_t dest_len)
{
	uint32_t src_len = my_strlen(src);
	uint32_t i;



	for (i = 0; i < dest_len; ++i)
	{
		*(src + src_len + i) = *(dest + i);
	}

	// NULL terminating the src string
	*(src + src_len + dest_len) = '\x00';
	//fprintf(stdout, "In my_strncat : src is '%s'\n", src);
	
	return 0;
}


uint32_t my_strncpy(uint8_t *src_buff, uint8_t *dest_buff, uint32_t n)
{
	uint32_t i;

	for (i = 0; i < n; ++i)
	{
		*(src_buff + i) = *(dest_buff + i);
	}
	
	*(src_buff + n) = '\x00';

	return 0;
}


uint8_t *my_strdup(uint8_t *string)
{
	uint32_t i, length = my_strlen(string);
	
	uint8_t *new_string = (uint8_t *)malloc(length);
	
	for ( i = 0; i < length ; ++i )
	{
		*(new_string + i) = *(string + i);
	}
	
	*(new_string + length) = '\x00';

	return new_string;
}

