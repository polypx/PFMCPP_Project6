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
    T(int v, const char* n) : value(v), name(n) {}    
    int value;                                        
    std::string name;                                 
};

struct FindSmaller                              
{
    T* compare(T& a, T& b)                      //5, pass references to two different T objects
    {                          
        if( a.value < b.value ) return &a;      // still need to RETURN a pointer
        if( a.value > b.value ) return &b;
        return nullptr;                         // return nullptr if a.value and b.value equal
    }    
};

struct U
{
    float uVariableA { 0 }, uVariableB { 0 };  
    float uMemberFunction(float& updatedValue)                              
    {
        std::cout << "U's uVariableA value: " << uVariableA << std::endl;  
        uVariableA = updatedValue;                                                  
        std::cout << "U's uVariableA updated value: " << uVariableA<< std::endl;
        while( std::abs(uVariableB - uVariableA) > 0.001f )
        {
            uVariableB += 0.1f;
        }
        std::cout << "U's uVariableB updated value: " << uVariableB << std::endl;
        return uVariableB * uVariableA;
    }    
};

struct DoingSomething
{
    static float updatingFunction(U& that, float& updatedValue)     //10  'that' reference to a U, reference to a float
    {   
        std::cout << "U's uVariableA value: " << that.uVariableA << std::endl; // now all uVariables are members of that
        that.uVariableA = updatedValue;                                     
        std::cout << "U's uVariableA updated value: " << that.uVariableA<< std::endl;
        while( std::abs(that.uVariableB - that.uVariableA) > 0.001f )   
        {
            /*
             write something that makes the distance between that->uVariableB and that->uVariableA get smaller
             */
            that.uVariableB += 0.1f;
        }
        std::cout << "U's uVariableB updated value: " << that.uVariableB << std::endl;
        return that.uVariableB * that.uVariableA;
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
    T tFirst(12, "tNameFirst");                                       
    T tSecond(11, "tNameSecond");                           
    
    FindSmaller f;                                        
    auto* smaller = f.compare(tFirst, tSecond); // smaller still must be pointer because we don't know result 
    if(smaller != nullptr)                  
    {    
        std::cout << "the smaller one is << " << smaller->name << std::endl;  
    }
    else
    {
        std::cout << "The two values must be equal."  << std::endl;  // only reason for smaller being nullptr   
    }    
    
    U uFirst;                                               
    float updatedValue = 5.f;                               
    std::cout << "[static func] uFirst's multiplied values: " << DoingSomething::updatingFunction(uFirst, updatedValue) << std::endl; 

    U uSecond;                                           
    std::cout << "[member func] uSecond's multiplied values: " << uSecond.uMemberFunction( updatedValue ) << std::endl;
}

