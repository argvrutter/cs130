/*
 * Author: Aiden Rutter
 * Lab 4: Double vector
 */
#include <cmath>
#include <iostream>
class doublevector
{
   double *mValues;
   int mNumElements;
   //using new keyword, allocates space for an additional double. Deletes old allocation, replaces with a new one.
   //Uninitialized value at beginning by default.
   //If second parameter set to true, deallocates a double instead.
   //index parameter is the element where space will be allocated/deallocated

   void allocDouble(unsigned int index=0);

   void deAllocDouble(unsigned int index=0);
public:
   //Allocate an empty vector (mNumElements = 0)
   doublevector();
   //De-allocate any dynamic memory
   ~doublevector();

   //Push the given value to the bottom of the vector, you will need
   //to resize the heap memory.
   void push_back(double value_to_push);
   //Inserts value_to_insert at the element index_to_insert.
   //You will need to resize the heap memory and move all of the current
   //elements down.
   //If the index > mNumElements, insert at the bottom of the vector.
   void insert(double value_to_insert, int index_to_insert);
   //Erases the element at which_element_to_erase, resize the heap memory,
   //and move all of the following elements up.
   //If which_element_to_erase is invalid, do nothing.
   void erase(int which_element_to_erase);
   //Returns a pointer to the given element. If which_element does not exist,
   //return nullptr.
   double *at(int which_element);
   //Same as above, just for constant classes.
   const double *at(int which_element) const;

   //Returns the number of elements in this class instance.
   int size() const;
};

//Print out the vector from top to bottom, one value per line.
void PrintVector(const doublevector *v);
//Copy the source vector into the destination vector. The destination
//vector may not exist, in which you will need to create a new vector.
void CopyVector(doublevector **dst, const doublevector *src);
//Applies the given function to each element in the vector.
//For example, Map(myvector, sqrt) will take the square root
//of each element and store it back into that element's slot.
void Map(doublevector *v, double (*mapfunc)(double));

doublevector::doublevector()
{
    mNumElements = 0;
    mValues = new double[0];
}

doublevector::~doublevector()
{
    delete[] mValues;
}

void doublevector::push_back(double value_to_push)
{
	allocDouble(mNumElements);
	mValues[mNumElements-1] = value_to_push;
}

void doublevector::insert(double value_to_insert, int index_to_insert)
{
    allocDouble(index_to_insert);
    mValues[index_to_insert] = value_to_insert;
}

void doublevector::erase(int which_element_to_erase)
{
    deAllocDouble(which_element_to_erase);
}

double* doublevector::at(int which_element)
{
    if(!((which_element < 0 )||(which_element >= mNumElements)))
    {
        return &mValues[which_element];
    }
    else
    {
        return NULL;
    }
}
const double* doublevector::at(int which_element) const
{
    //if it doesn't exist return nullptr
    if(!((which_element < 0 )||(which_element >= mNumElements)))
    {
        return &mValues[which_element];
    }
    else
    {
        return NULL;
    }
}

void doublevector::deAllocDouble(unsigned int index)
{
    int j=0;
    int temp[mNumElements-1];

    if(index > mNumElements-1)
    {
        return;
    }

    for(int i=0; i<mNumElements; i++)
    {
        if(i == index)
        {
            i++;
        }
        temp[j] = mValues[i];
        j++;
    }

    delete[] mValues;

    mNumElements--;
    mValues = new double[mNumElements];
	//copy values
	for(int i=0; i<mNumElements; i++)
	{
		mValues[i] = temp[i];
	}
}

void doublevector::allocDouble(unsigned int index)
{
    int j=0;
    int temp[mNumElements+1];

    if(index > mNumElements)
    {
        return;
    }

	for(int i=0; i<mNumElements; i++)
    {
      //assignment skipped on index
      if(i == index)
      {
          j++;
      }
      temp[j] = mValues[i];
      j++;
    }

	delete[] mValues;

    mNumElements++;
    mValues = new double[mNumElements];
	//copy values
	for(int i=0; i<mNumElements; i++)
	{
		mValues[i] = temp[i];
	}
}

int doublevector::size() const
{
    return mNumElements;
}

void PrintVector(const doublevector *v)
{
    for(int i=0; i< v->size(); i++)
    {
        std::cout << std::endl << *(v->at(i));
    }
    std::cout << std::endl;
}

void CopyVector(doublevector **dst, const doublevector *src)
{
    *dst = new doublevector();
    for(int i=0; i<src->size(); i++)
    {
        (**dst).push_back(*(src->at(i)));
    }
}

void Map(doublevector *v, double (*mapfunc)(double))
{
    for(int i=0; i<v->size(); i++)
    {
        *(v->at(i)) = mapfunc(*(v->at(i)));
    }
}

int main()
{
    doublevector test;
    doublevector *test2;

    for(int i=0; i<10; i++)
    {
        test.push_back(static_cast<double>(i));
    }
    test.insert(static_cast<double>(81), 5);

    CopyVector(&test2, &test);
    PrintVector(&test);
    PrintVector(test2);

    Map(&test, std::sqrt);
    PrintVector(&test);
    delete test2;
}
