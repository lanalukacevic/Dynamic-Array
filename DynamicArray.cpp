#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
    private:
        T* array;
        int size;
    public:
        
        DynamicArray()
        {
            array = NULL;
            size = 0;
        }

        // add new element to end of array, resize array to accomadate
        void add(const T& elem)
        {
            T* temp = new T[size + 1];

            for (int i = 0; i < size; i++)
            {
                temp[i] = array[i];
            }

            temp[size] = elem;
            size++;

            if (array != NULL)
                delete [] array;
            
            array = temp;
        }
        
        // return the size of the array
        int length() const
        {
            return size;
        }

        // remove item by value - search - bool
        bool removeValue(const T& value)
        {
            bool exist = false;
            int index;
            for (int i = 0; i < size; i++)
            {
                if (value == array[i])
                {
                    index = i;
                    exist = true;
                    break;
                }
            }
            if (exist)
            {
                T * tmp = new T[--size];
                // copy up to the index which should be dropped
                for (int i = 0; i < index; i++)
                {
                    tmp[i] = array[i];
                }
                // copy over the rest of the array after the value at the index needed to be dropped
                for (int i = index; i < size; i++)
                {
                    tmp[i] = array[i + 1];
                }

                delete [] array;
                array = tmp;
                
                return true;

            }
            cerr << "Value "<< value << ": does not exist in array" << endl;
            return false;

        }


        // remove item by index - check to see if index in range
        bool removeIndex(const int& index)
        {
            if (index < size)
            {
                T * tmp = new T[--size];
                // copy up to the index which should be dropped
                for (int i = 0; i < index; i++)
                {
                    tmp[i] = array[i];
                }
                // copy over the rest of the array after the value at the index needed to be dropped
                for (int i = index; i < size; i++)
                {
                    tmp[i] = array[i + 1];
                }

                delete [] array;
                array = tmp;
                
                return true;
            }
            cerr << "Index " << index << ": out of bounds" << endl;
            return false;
        }

        T& operator [] (const int& index) const
        {
            if ( index >= size)
            {
                cerr << "Index: " << index << ": out of bounds" << endl;
                exit(1);
            }
            return array[index];
        }  


        // the big three - need to explicitly be defined when explicit handling of memory occurs in cpp, to avoid catastropic memory disasters
        // overwrite COPY CONSTRUCTOR - deep copy
        DynamicArray(const DynamicArray<T>& other): size(other.size)
        {
            if (size > 0)
            {
                array = new T[size];
                for (int i = 0; i < size; i++)
                {
                    array[i] = other.array[i];
                }
            }
        }

        /*
        -Deep copy the RHS argument to the LHS side, both of which are already existing objects of the class
        values before assignment: [1,2,3]  [2,5,8,10]
        array1 = array2 // array1 calls = operator array2 is the argument passed
        values after assignment: [2,5,8,10] [2,5,8,10]
        array1.add(5)
        values after add: [2,5,8,10,5] [2,5,8,10]
        */

       // array1 = (array2 = array3)
       // array = array2


        // overwrite assignment operator - you assign to an existing object
        DynamicArray<T> operator = (const DynamicArray<T>& other)
        {
            if (this != &other) // prevents data loss when both LHS and RHS of assignment
            {
                if (array != NULL) // only free memory if pointer is referencing an array prevents memory leak
                {
                    delete [] array;
                }

                size = other.size;
                if (size > 0) // only allocate memory if right hand side of assignment size > 0
                {
                    array = new T[size];   
                }

                for (int i = 0; i < size; i++)
                {
                    array[i] = other.array[i];
                }
            }
            return *this; // returns lhs object in the case there is another assignment                 
        }
        

        // overwrite destructor
        ~DynamicArray()
        {
            if (array != NULL)
            {
                // prevents memory leaks
                delete [] array;
                // this removes hanging reference
                array = NULL;
            }
        }




        template <class t> // need to declare a different template for the friend
        friend ostream& operator << (ostream& out, const DynamicArray<t>& da);

};

template <class t>
ostream& operator << (ostream& out, const DynamicArray<t>& da)
{
    for (int i = 0; i < da.size; i++)
    {
        out << da.array[i] << "\t";
    }

    return out;
}