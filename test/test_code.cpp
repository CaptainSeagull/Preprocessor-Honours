#include <iostream>
#include "pp_generated/test_code_generated.h"
#include <string>

class Person

{
public:
    std::string name = "";
    int age = 0;
    std::string city = "";
    char gender = ' ';

    void setName(std::string nameIn) { name = nameIn; }
    void setAge(int ageIn) { age = ageIn; }
    void setCity(std::string cityIn) { name = cityIn; }
    void setGender(char genderIn) { gender = genderIn; }
};

class Student :public Person {
public:
    std::string major = "";
    std::string minor = "";

    void setMajor(std::string majorIn) { major = majorIn; }
    void setMinor(std::string minorIn) { minor = minorIn; }


};



int main(void) {
    Student student1;
    student1.setName("John Smith");
    student1.setAge(24);
    student1.setCity("Glasgow City");
    student1.setGender('M');
    student1.setMajor("Mathematics");
    student1.setMinor("Philosphy");

    Student student2;
    student2.setName("Jane Doe");
    student2.setAge(35);
    student2.setCity("Edinburgh");
    student2.setGender('F');
    student2.setMajor("Computing");
    student2.setMinor("Chemistry");

    Student student3;
    student3.setName("Steven Stevenson");
    student3.setAge(40);
    student3.setCity("Manchester");
    student3.setGender('M');
    student3.setMajor("Mathematics");
    student3.setMinor("English");

    Student student4;
    student4.setName("Mary Sue");
    student4.setAge(19);
    student4.setCity("London");
    student4.setGender('F');
    student4.setMajor("Computing");
    student4.setMinor("French");

    Student student5;
    student5.setName("Bob McMullen");
    student5.setAge(20);
    student5.setCity("Liverpool");
    student5.setGender('M');
    student5.setMajor("Mathematics");
    student5.setMinor("Art");

    Student student6;
    student6.setName("Joe Doe");
    student6.setAge(56);
    student6.setCity("Dundee");
    student6.setGender('M');
    student6.setMajor("Computing");
    student6.setMinor("French");

    Student student7;
    student7.setName("Sally Suesanson");
    student7.setAge(60);
    student7.setCity("Aberdeen");
    student7.setGender('F');
    student7.setMajor("Mathematics");
    student7.setMinor("Computing");

    Student student8;
    student8.setName("David Brown");
    student8.setAge(28);
    student8.setCity("York");
    student8.setGender('M');
    student8.setMajor("Computing");
    student8.setMinor("Spanish");

    Student student9;
    student9.setName("Moira Wright");
    student9.setAge(67);
    student9.setCity("Birmingham");
    student9.setGender('F');
    student9.setMajor("Mathematics");
    student9.setMinor("Art");

    Student student10;
    student10.setName("Mark McBride");
    student10.setAge(45);
    student10.setCity("Dublin");
    student10.setGender('M');
    student10.setMajor("Computing");
    student10.setMinor("History");

    pp::print(student1);
    pp::print(student2);
    pp::print(student3);
    pp::print(student4);
    pp::print(student5);
    pp::print(student6);
    pp::print(student7);
    pp::print(student8);
    pp::print(student9);
    pp::print(student10);

    return 0;
}