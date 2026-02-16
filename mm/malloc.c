// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	if (size == 0) {
		return NULL;
	}

	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED) {
		return NULL;
	}

	if (mem_list_add(ptr, size) == -1) {
		munmap(ptr, size);
		return NULL;
	}

	return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	if (size == 0 || nmemb == 0) {
		return NULL;
	}

	size_t total_size = nmemb * size;
	void *ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (ptr == MAP_FAILED) {
		return NULL;
	}

	if (mem_list_add(ptr, total_size) == -1) {
		munmap(ptr, total_size);
		return NULL;
	}
	memset(ptr, 0, total_size);
	return ptr;
}

void free(void *ptr)
{
	if (ptr == NULL) {
		return;
	}

	struct mem_list *item = mem_list_find(ptr);
	if (item == NULL) {
		return;
	}

	munmap(ptr, item->len);
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	struct mem_list *item = mem_list_find(ptr);
	void *new_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_ptr == MAP_FAILED) {
		return NULL;
	}

	size_t copy_size;
	if (size < item->len) {
		copy_size = size;
	} else {
		copy_size = item->len;
	}

	memcpy(new_ptr, ptr, copy_size);
	free(ptr);

	if (mem_list_add(new_ptr, size) == -1) {
		munmap(new_ptr, size);
		return NULL;
	}

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return realloc(ptr, nmemb * size);
}
