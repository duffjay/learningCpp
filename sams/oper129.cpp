#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class MyString
{
    private:
        char* buffer;

        // private constructor
        MyString() {}

    public:
        // constructor
        MyString(const char* initialInput)    // const = can't alter the input
        {
            buffer = NULL;
            cout << "Default constructor: creating new MyString" << endl;
            if(initialInput != NULL)
            {
                buffer = new char [strlen(initialInput) + 1];   // get a new mem alloc for a buffer  +1 for \0
                strcpy(buffer, initialInput);                   // strcpy uses char*
                
                cout << "new MyString object.buffer points to: " << hex;
                cout << (unsigned int*)buffer << endl;
            }
            else
                buffer = NULL;
        }

        // Copy constructor - from 9.9
        MyString(const MyString& copySource)
        {
            buffer = NULL;
            cout << "Copy constructor: copying from MyString" << endl;
            if(copySource.buffer != NULL)
            {
                // allocate own buffer, buffer is a char[]
                buffer = new char [strlen(copySource.buffer) + 1];

                // deep copy from the source into local buffer
                strcpy(buffer, copySource.buffer);
                // show the pointer to the char[] = buffer; so the pointer is *buffer
                cout << "Copy Constructor - buffer points to: " << hex;
                cout << (unsigned int*)buffer << endl;
            }
        }

        // Copy assignment operator =  taken from 12.8
           // Copy assignment operator
        MyString& operator= (const MyString& CopySource)
        {
            cout << "using operator = " << endl;
            // can't copy to self and buffer of the copy source can't be NULL
            if ((this != &CopySource) && (CopySource.buffer != NULL))
            {
                if (buffer != NULL)     // don't reuse an existing buffer?
                    delete[] buffer;

                // ensure deep copy by first allocating own buffer 
                buffer = new char [strlen(CopySource.buffer) + 1];

                // copy from the source into local buffer
                strcpy(buffer, CopySource.buffer);

                // show the pointer to the char[] = buffer; so the pointer is *buffer
                cout << "operator = buffer points to: " << hex;
                cout << (unsigned int*)buffer << endl;
            }
            else
                cout << "operator =  did nothing" << endl;

            return *this;
        }

        const char& operator[] (int index) const
        {
            if (index < GetLength())
                return buffer[index];
        }

        // Destructor
        ~MyString()
        {
            cout << "destructor called" << endl;
            if (buffer != NULL)
                delete [] buffer;
        }

        int GetLength() const
        {
            return strlen(buffer);
        }

        operator const char*()
        {
            return buffer;
        }
   };

int main()
{
    cout << "Type a statement: ";
    string strInput;
    getline(cin, strInput);

    //this is constructing a MyString = to what you entered
    MyString youSaid(strInput.c_str());

    cout << "Using operator[] for displaying your input: " << endl;
    for (int index = 0; index < youSaid.GetLength(); ++index)
        cout << youSaid[index] << " ";
    cout << endl;

    // show index range - prompt to enter valid index
    cout << "Enter index 0 - " << youSaid.GetLength() - 1 << ": ";
    int index = 0;
    cin >> index;
    cout << "Input character at zero-based position: " << index;
    cout << " is: " << youSaid[index] << endl;

    // demonstrate the copy constructor
    MyString copy2YouSaid("initialized copy2");
    cout << "copied w/ copy contructor - string: " << MyString(copy2YouSaid) << endl;

    // demonstrate = operator
    MyString copy3YouSaid("initialized copy3");
    copy3YouSaid = youSaid;
    cout << "copied w/ = string: " << copy3YouSaid << endl;

    return 0;

}
