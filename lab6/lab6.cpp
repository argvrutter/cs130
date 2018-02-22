/**
* Author: Aiden Rutter
* Lab 6: MyMap
*/
#include <stdio.h>
extern "C" //extern "C" is required here
{
    //These functions will be implemented in ASSEMBLY
    void asm_Construct(void *mymap_pointer);
    void asm_Set(void *mymap_pointer, char key, int value);
    int  asm_Get(const void *mymap_pointer, char key);
    void asm_Erase(void *mymap_pointer, char key);
    void asm_Print(const void *mymap_pointer);
}

//Write these in C++ to test your logic. These are analogous
//to their asm_* counterparts and perform the same operations.
struct KeyValue;
struct mymap;
/**
 * set all 20 elements to key '*', value -1
 */
void c_Construct(mymap *mymap_pointer);
/**
 * search for the key. if found, update value.
 * else, find an empty slot ('*') put value  & key there
 * if not empty, do nothing
 */
void c_Set(mymap *mymap_pointer, char key, int value);
/**
 * search for key, return value if found, else
 * return -1
 */
int  c_Get(const mymap *mymap_pointer, char key);
/**
 * search for key, if found, set key to *,
 * but does not change values
 */
void c_Erase(mymap *mymap_pointer, char key);
/**
 * prints all 20 key/value pairs, in this format
 * <key> = <value> \n
 */
void c_Print(const mymap *mymap_pointer);

//Copy this class into your code. Your member functions simply call
//your assembly functions prototyped above. To test your
//logic, change the asm_* functions to their c_* counterparts.
struct KeyValue
{
    char key;
    int value;
};

struct mymap
{
    KeyValue mKeyValues[20];
    //change asm to c_ temp here
    mymap () { asm_Construct(this); }
    void set(char key, int value) { asm_Set(this, key, value); }
    int get(char key) const { return asm_Get(this, key); }
    void erase(char key) { asm_Erase(this, key); }
    void print() const { asm_Print(this); }
};

void c_Construct(mymap *mymap_pointer)
{
    for(int i=0; i<20; i++)
    {
        mymap_pointer->mKeyValues[i].key = '*';
        mymap_pointer->mKeyValues[i].value = -1;
    }
}

void c_Set(mymap *mymap_pointer, char key, int value)
{
    int index = c_Get(mymap_pointer, key);
    if(index >= 0 && index < 20)
    {
        mymap_pointer->mKeyValues[index].value = value;
        return;
    }
    index = c_Get(mymap_pointer, '*');
    if(index >= 0 && index < 20)
    {
        mymap_pointer->mKeyValues[index].key = key;
        mymap_pointer->mKeyValues[index].value = value;
    }
}

int  c_Get(const mymap *mymap_pointer, char key)
{
    for(int i=0; i<20; i++)
    {
        if(mymap_pointer->mKeyValues[i].key == key)
        {
            return i;
        }
    }
    return -1;
}

void c_Erase(mymap *mymap_pointer, char key)
{
    int index = c_Get(mymap_pointer, key);
    if(index >=0 && index < 20)
    {
        mymap_pointer->mKeyValues[index].key = '*';
    }
}

void c_Print(const mymap *mymap_pointer)
{
    char key;
    int value;
    for(int i=0; i<20; i++)
    {
        key = mymap_pointer->mKeyValues[i].key;
        value = mymap_pointer->mKeyValues[i].value;
        printf("%c = %d \n", key, value);
    }
}

int main()
{
    mymap map;
    map.print();
    for(int i=0; i<20; i++)
    {
        map.set(97+i, i);
    }
    map.print();
    map.erase('g');
    map.erase('m');
    map.print();
    map.set('x', 255);
    map.set('z', 2048);
    map.set('g', 665);
    map.print();
}
