/*
 Project 6: Part 1 / 2
 Video: Chapter 3 Part 2

Create a branch named Part1

Purpose:  This project will show you the difference between member functions and static class functions, as well as the difference between pointers and references and the code semantics that accompany pointers and references.

 Pointers

 Please look at the screenshot in the files to see what happens if you paste this assignment into an existing cpp file in an xcode project
 
 Task: replace all of the <#place holder#> placeholders with proper names and types that will make this program compile and run.
 
 press the Compile, link and run... button and work your way through all of the error messages.
 

 steps:
 
 1) finish implementing the constructor for T. the constructor parameters need to initialize 2) and 3)
 
 2) provide a member variable in T of a type of your choosing that works with the compare function below T
         note the name of the variable used in the compare function
 
 3) provide a member variable of type std::string in T that works with the *first* cout statement in main().
         note the name of the variable used in the *first* cout statement in main()
 
 4) finish defining the struct with the compare function
 5) provide proper types for the arguments to compare, and a proper return value
         be sure to make it work with the pointer semantics being used in the if statements.
         see 8) for a hint about what type to use.
 
 6) finish instantiating the two T instances being declared in main(), based on the constructor you finished implementing in T
     Their names (line 105,106) are different than the member variables names (line 77), even tho the placeholders share the same name.
     Don't let this confuse you.
 
 7) Declare 'f' with the proper type so the call to f.compare works
 
 8) call f.compare() with the correct arguments, based on 2) and 5)
 
 9) correct the cout that uses smaller's member variable with some safe pointer usage.
    the possible return values of the compare() function should give you a hint.
    Also: if smaller == nullptr, make the cout statement explain the reasons that `f.compare()` might return nullptr.  
    hint: There are multiple reasons
 
 10) complete the implementation for the static function in <structName2>
 
 11) call the <structName2> static function correctly in main()
 
 12) replicate the functionality of <structName2>'s static function by implementing a member function in U that does the same thing.
 
 13) remember the rules for using pointers!  What is the one thing we always do before we use a pointer?
 
 After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

#include <iostream>
#include <string>
struct T
{
    T(int v, const char* n) : value(v), name(n) {}    //1  object T has an integer and a name
    int value;                                        //2  'value' given us by compare function
    std::string name;                                 //3  'name' from main
};

struct FindSmaller                               //4
{
    T* compare(T* a, T* b)      //5, compare the integer members of two different Ts, using pointers to them, a and b point to two Ts
    {                          
        if(a != nullptr && b != nullptr) // WE'RE GOING TO HAVE TO CHECK FOR NULL POINTERS HERE TOO IF WE'RE CREATING SOME POINTERS 
        {
            if( a->value < b->value ) return a;   // ->"value" of the T pointed at by "a" < "value" of the T pointed at by "b", jeez
            if( a->value > b->value ) return b;
        }
        return nullptr;                           // return nullptr if either a or b is null, or if a and b point to the same value
    }    
};

struct U
{
    float uVariableA { 0 }, uVariableB { 0 };  
    float uMemberFunction(float* updatedValue)                              //    all that's become this's, nice
    {
        std::cout << "U's uVariableA value: " << this->uVariableA << std::endl;
        this->uVariableA = *updatedValue;                                                  
        std::cout << "U's uVariableA updated value: " << this->uVariableA<< std::endl;
        while( std::abs(this->uVariableB - this->uVariableA) > 0.001f )
        {
            this->uVariableB += 0.1f;
        }
        std::cout << "U's uVariableB updated value: " << this->uVariableB << std::endl;
        return this->uVariableB * this->uVariableA;
    }
};

struct DoingSomething
{
    static float updatingFunction(U* that, float* updatedValue )        //10  'that' pointer to a U, pointer to a float
    {
        std::cout << "U's uVariableA value: " << that->uVariableA << std::endl;
        that->uVariableA = *updatedValue;                            //  copy the actual value float, "dereference", into 'that' actual U object                   
        std::cout << "U's uVariableA updated value: " << that->uVariableA<< std::endl;
        while( std::abs(that->uVariableB - that->uVariableA) > 0.001f )   
        {
            /*
             write something that makes the distance between that->uVariableB and that->uVariableA get smaller
             */
            that->uVariableB += 0.1f;
        }
        std::cout << "U's uVariableB updated value: " << that->uVariableB << std::endl;
        return that->uVariableB * that->uVariableA;
    }
};
        
/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    T tFirst(12, "tNameFirst");                                           //6  create a couple Ts, with some values
    T tSecond(13, "tNameSecond");                                         //6
    
    FindSmaller f;                                                        //7   create a FindSmaller object to compare Ts with 
    auto* smaller = f.compare(&tFirst, &tSecond);                         //8   pass the ADDRESS of each T, not the whole shebang
    if(smaller != nullptr)                                                //    check smaller (return from f.compare) is actually not nullptr 
    {    
    std::cout << "the smaller one is << " << smaller->name << std::endl;  //9   print the name of the T instance pointed at by smaller  
    }
    else
    {
    std::cout << "Either the two values are equal or at least one of them is nullptr"  << std::endl;  //9   reason for nullptr     
    }    
    
    U uFirst;                                                             //  create a U 
    float updatedValue = 5.f;
    std::cout << "[static func] uFirsts multiplied values: "  << DoingSomething::updatingFunction(&uFirst , &updatedValue) << std::endl;   //11

    U uSecond;                                                            //  create another U 
    std::cout << "[member func] uSeconds multiplied values: " << uSecond.uMemberFunction( &updatedValue ) << std::endl;
}
