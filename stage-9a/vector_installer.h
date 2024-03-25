
#ifndef VECTOR_INSTALLER_H
#define VECTOR_INSTALLER_H
#include <osbind.h>
typedef void (*Vector)();

Vector install_vector(int num, Vector vector);



#endif
