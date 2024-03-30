#ifndef vct_inst
#define vct_inst
#include <osbind.h>
typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

#endif