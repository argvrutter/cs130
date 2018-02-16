/**
 * Author: Aiden Rutter
 * Lab 6: MyMap
 */

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
 void c_Construct(mymap *mymap_pointer);
 void c_Set(mymap *mymap_pointer, char key, int value);
 int  c_Get(const mymap *mymap_pointer, char key);
 void c_Erase(mymap *mymap_pointer, char key);
 void c_Print(const mymap *mymap_pointer);

 //Copy this class into your code. Your member functions simply call
 //your assembly functions prototyped above. To test your
 //logic, change the asm_* functions to their c_* counterparts.
 struct KeyValue
 {
    char key;
    int value;
 };

 struct mymap {
    KeyValue mKeyValues[20];

    mymap () { asm_Construct(this); }
    void set(char key, int value) { asm_Set(this, key, value); }
    int get(char key) const { return asm_Get(this, key); }
    void erase(char key) { asm_Erase(this, key); }
    void print() const { asm_Print(this); }
 };
