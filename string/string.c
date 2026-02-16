// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	*destination = 0;
	while (*source) {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = 0;
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	while (len && *source) {
		*destination = *source;
		destination++;
		source++;
		len--;
	}

	while (len) {
		*destination = 0;
		len--;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	while (*destination) {
		destination++;
	}

	while (*source) {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = 0;
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	while (*destination) {
		destination++;
	}

	while (*source && len) {
		*destination = *source;
		destination++;
		source++;
		len--;
	}

	*destination = 0;
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2) {
		if (*str1 != *str2) {
			return (char)*str1 - (char)*str2;
		}
		str1++;
		str2++;
	}

	return (char)*str1 - (char)*str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while (len && *str1 && *str2) {
		if (*str1 != *str2) {
			return (char)*str1 - (char)*str2;
		}
		str1++;
		str2++;
		len--;
	}

	if (len == 0) {
		return 0;
	}

	return (char)*str1 - (char)*str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	for (size_t i = 0; i < strlen(str); i++) {
		if (str[i] == (char)c) {
			return (char *)str + i;
		}
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	for (size_t i = strlen(str); i > 0; i--) {
		if (str[i - 1] == (char)c) {
			return (char *)str + (i - 1);
		}
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	for (size_t i = 0; i < strlen(haystack); i++) {
		size_t j = 0;
		while (haystack[i + j] == needle[j]) {
			j++;
			if (!needle[j]) {
				return (char *)haystack + i;
			}
		}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	for (size_t i = strlen(haystack); i > 0; i--) {
		size_t j = 0;
		while (haystack[(i - 1) + j] == needle[j]) {
			j++;
			if (!needle[j]) {
				return (char *)haystack + (i - 1);
			}
		}
	}
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *d = destination;
	char *s = (char *)source;

	for (size_t i = 0; i < num; i++) {
		d[i] = s[i];
	}

	return d;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *d = (char *)destination;
	char *s = (char *)source;

	if (d < s) {
		for (size_t i = 0; i < num; i++) {
			d[i] = s[i];
		}
	} else {
		for (size_t i = num; i > 0; i--) {
			d[i - 1] = s[i - 1];
		}
	}

	return d;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *p1 = (char *)ptr1;
	char *p2 = (char *)ptr2;

	while (num) {
		if (*p1 != *p2) {
			return *p1 - *p2;
		}
		p1++;
		p2++;
		num--;
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	char *s = (char *)source;
	for (size_t i = 0; i < num; i++) {
		s[i] = (char)value;
	}
	return s;
}
