/*
 Project 6: Part 2 / 2
 Video: Chapter 3 Part 3

Create a branch named Part2

 References
 
 
 1) convert the pointer usage (except for 'const char*') to reference types or 
    const reference types **>>> WHERE POSSIBLE <<<**
    Not every pointer can be converted.
        hint: There is no reference equivalent to nullptr.  
        if a pointer (including nullptr) is being returned anywhere, don't try to convert it to a reference.

    You have to ask yourself if each pointer can be converted to a (const) reference.
    Think carefully when making your changes.

 2) revise the 'else' statement in main() that handles when `smaller` is a nullptr. 
 there is only one reason for `compare` to return nullptr. 
 Update this std::cout expression to specify why nullptr was returned.
 
 3) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
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
    float uMemberFunction(float* updatedValue)                              
    {
        if (updatedValue != nullptr)                                        // new pointers! check not null
        {
            std::cout << "U's uVariableA value: " << this->uVariableA << std::endl;    // all that's become this's
            this->uVariableA = *updatedValue;                                                  
            std::cout << "U's uVariableA updated value: " << this->uVariableA<< std::endl;
            while( std::abs(this->uVariableB - this->uVariableA) > 0.001f )
            {
                this->uVariableB += 0.1f;
            }
            std::cout << "U's uVariableB updated value: " << this->uVariableB << std::endl;
            return this->uVariableB * this->uVariableA;
        }
        return 0;  // just to return something in case nullptr
    }    
};

struct DoingSomething
{
    static float updatingFunction(U* that, float* updatedValue)     //10  'that' pointer to a U, pointer to a float
    {                                                               // here again some new pointers!!!! check not null
        if( that != nullptr && updatedValue != nullptr )
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
        return 0;  // just to return something in case nullptr
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
    T tSecond(11, "tNameSecond");                                         //6
    
    FindSmaller f;                                                        //7   create a FindSmaller object to compare Ts with 
    auto* smaller = f.compare(&tFirst, &tSecond);                         //8   pass the ADDRESS of each T, not the whole shebang
    if(smaller != nullptr)                                                //    check smaller pointer is not nullptr 
    {    
        std::cout << "the smaller one is << " << smaller->name << std::endl;  //9   print the name of the T instance pointed at by smaller  
    }
    else
    {
        std::cout << "Either the two values are equal or one is nullptr"  << std::endl;  //   reasons for smaller being nullptr     
    }    
    
    U uFirst;                                                   //  create a U 
    float updatedValue = 5.f;                                   //  create a float value
    
    std::cout << "[static func] uFirst's multiplied values: "  << DoingSomething::updatingFunction(&uFirst, &updatedValue) << std::endl; 
                                                                // we access updatingFunction by class name::method
                                                                // it exists even though there is no object of type 'DoingSomething'
                                                                // ie. the static function exists all the time, static variables too

    U uSecond;                                                  //  create another U 
    std::cout << "[member func] uSecond's multiplied values: " << uSecond.uMemberFunction( &updatedValue ) << std::endl;
                                                                // we access this version of the function by class.member method
}

