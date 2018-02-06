/*
 * Author: Aiden Rutter
 * Lab 4: Double vector
 * Personal goal: memory is stored contiguously and efficiently
 * Strategy: Stack-like method of retrieval and storage.
 */


using namespace std;
class doublevector
{
   double *mValues;
   int mNumElements;
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
  /*
    double temp[mNumElements +1];
    for(int i=0; i<mNumElements; i++)
    {
      temp[i]= mValues[i];
    }
    temp[mNumElements] = value_to_push;
    delete[] mValues;
    mNumElements++;
    mValues = new double[mNumElements];
    mValues = temp;
    */
}

void doublevector::insert(double value_to_insert, int index_to_insert)
{
    delete[] mValues;

}

void doublevector::erase(int which_element_to_erase)
{

}

double* doublevector::at(int which_element)
{

}
const double* doublevector::at(int which_element) const
{

}

int doublevector::size() const
{
    return mNumElements;
}

void PrintVector(const doublevector *v)
{
    for(int i=0; i< v->size(); i++)
    {
        cout << endl << *(v->at(i));
    }
    cout << endl;
}

void CopyVector(doublevector **dst, const doublevector *src)
{

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
    //Just for testing and so it compiles
}
