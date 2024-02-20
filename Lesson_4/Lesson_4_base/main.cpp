#include <iostream>

using namespace std;

class Parent {
public:
    int m_public;
private:
    int m_private;
protected:
    int m_protected;
};

class PublicTest: public Parent {
public:
    PublicTest() {
        m_public = 1;    // OK left public
        //m_private = 1; // NO left private, unable to edit in child class
        m_protected = 1; // OK left protected
    }
};

class PrivateTest: private Parent {
public:
    PrivateTest() {
        m_public = 1;    // OK become private
        //m_private = 1; // NO become private, unable to edit in child class
        m_protected = 1; // OK become private
    }
};

class ProtectedTest: protected Parent {
public:
    ProtectedTest() {
        m_public = 1;    // OK become protected
        //m_private = 1; // NO left private, unable to edit in child class
        m_protected = 1; // OK left protected
    }
};

int main()
{
    Parent parent;
    parent.m_public = 0;      // OK
    //parent.m_private = 0;   // NO
    //parent.m_protected = 0; // NO

    PublicTest publicTest;
    publicTest.m_public = 0;
    //publicTest.m_private = 0;
    //publicTest.m_protected = 0;

    PrivateTest privateTest;
    //privateTest.m_public = 0;
    //privateTest.m_private = 0;
    //privateTest.m_protected = 0;

    return 0;
}
