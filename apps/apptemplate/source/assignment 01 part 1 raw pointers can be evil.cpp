//
// File:   assignment1.cpp
// Author: <Arielle Robinson>
// Purpose:
// Illustrate some of the bad things that can happen with
// pointers
//
#include <iostream>

#include <vector>

#include <string>



using namespace std;



class Move {

private:



    int* data;



public:



    Move(int d) {

        data = new int;

        *data = d;

        cout << "Constructor is called for " << d << endl;

    }





    Move(const Move& source) : Move{ *source.data } {



        cout << "Copy Constructor is called - Deep copy for " << *source.data << endl;

    }



    Move(Move&& source)

        : data{ source.data } {

        cout << "Move Constructor is called for " << *source.data << endl;

        source.data = nullptr;

    }





    Move& operator=(const Move& source) {

        if (this == &source)

            return *this;



        delete data;



        data = new int{ *source.data };

        cout << "Copy Assignment is called - Deep copy for " << *source.data << endl;



        return *this;

    }





    Move& operator=(Move&& source) noexcept {

        if (this == &source)

            return *this;



        delete data;



        data = source.data;

        source.data = nullptr;



        cout << "Move Assignment is called for " << *data << endl;



        return *this;

    }





    ~Move() {

        if (data != nullptr)



            cout << "Destructor is called for " << *data << endl;

        else



            cout << "Destructor is called for nullptr" << endl;





        delete data;

    }

};



void allocateAndManipulateArray() {



    int* firstPtr = new int[100000];



    for (int i = 0; i < 100000; ++i) {

        firstPtr[i] = i;

    }



    int* secondPtr = firstPtr;



    delete[] firstPtr;



    for (int i = 0; i < 10; ++i) {

        cout << secondPtr[i] << " ";

    }

    cout << endl;

}



void allocateAndInspectPointer() {



    int* firstPtr = new int[100000];



    for (int i = 0; i < 100000; ++i) {

        firstPtr[i] = i;

    }



    int* secondPtr = firstPtr;



    delete firstPtr;



    cout << "Second pointer address: " << secondPtr << endl;

    for (int i = 0; i < 10; ++i) {

        cout << secondPtr[i] << " ";

    }

    cout << endl;

}



string* createStringOnHeap() {

    string* strPtr = new string("abcdefghijkl");

    return strPtr;

}



void allocateAndPrintString() {

    string* str = createStringOnHeap();

    cout << *str << endl;

    delete str;

}



int main() {

    allocateAndManipulateArray();

    allocateAndInspectPointer();

    allocateAndPrintString();





    vector<Move> vec;



    vec.push_back(Move{ 10 });

    vec.push_back(Move{ 20 });



    return 0;

}

