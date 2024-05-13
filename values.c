#include "values.h"
#include "memory.h"

void InitValue(ValueArray *array){
    array->values=NULL;
    array->count=0;
    array->capacity=0;
}

void WriteValue(ValueArray *array, Value value){
    if(array->capacity<array->count+1){
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void FreeValue(ValueArray *array){
    FREE_ARRAY(Value,array->values,array->capacity);
    InitValue(array);
}