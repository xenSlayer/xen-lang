# <b>C++ Notes </b>

<b> 1. unique_ptr </b>

Use only when there is a single reference to the pointer. If a unique pointer is shared then it will cause issue once the first reference to the pointer is complete. Since the mem will be freed, the other reference to the pointer will be pointing to a mem location where the mem is cleared or stuffed with other data.

<br>

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
    std::unique_ptr<Student> student = std::make_unique<Student>();
    std::cout << student->name << std::endl;
    return 0;
}

/*
    output:

    -> kiran
    -> auto desc student

*/
```

<br>

<b> 2. shared_ptr</b>

- lib:

```
#include <memory>
```

- allow use of shared pointer without need to worry about the mem leaks.

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
