# <b>C++ Notes </b>

<b> 1. unique_ptr in cpp </b>

- lib:

```
#include <memory>
```

- allow use of pointer without need to worry about the mem leaks.

<br>

<i>
    example:
</i>

```
#include <memory>
#include <string>
#include <iostream>


class Student 
{
    public: 
        std::string name;
        int age;

        Student(const std::string &nm, int ag) 
            : name(nm), age(ag) {}
        ~Student() {std::cout << "auto desc student" << std::endl;}

};


int main() 
{
    std::unique_ptr<Student> student(new Student("kiran", 22));
    std::cout << student->name << std::endl;
    return 0;
}

/*
    output:

    -> kiran
    -> auto desc student

*/
```
