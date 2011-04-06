/** 
 * macro to wrap a malloc
 * 
 * @param size number of table elements to alloc
 * @param type type of an element
 * 
 * @return pointer to an allocated memory casted to an appropriate type
 */
#define ODE_MALLOC(size,type) (type *)malloc(size * sizeof(type))
#define ODE_FREE(ptr) {free(ptr); ptr=NULL;}
#define ODE_REALLOC(ptr,n,type) (type *)realloc((void * )ptr, (n) * sizeof(type))
#define MAX(a,b) (a<b?b:a)

