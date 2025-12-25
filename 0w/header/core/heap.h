#if (!defined Value_Heap_FUNCTION && defined Value_DEFINE)

#define Value_Heap_FUNCTION

typedef void *ptr_t, *heap_t, *pHeap_t;

int value_heap_calloc(pHeap_t ptrOfTheObjectPtr, unsigned int sizeOfElementType, unsigned int elementCount);

int value_heap_redirect(pHeap_t ptrOfTheObjectPtr, ptr_t redirectTo);

int value_heap_release(heap_t restrict ptrOfTheObjectPtr);

#endif
