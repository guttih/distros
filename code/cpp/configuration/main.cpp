#include <iostream>

 #include <Json/Json.h>
#include <Json/JsonFile.h>
#include "Person.cpp"



void getAndSetPerson()
{
    std::cout << "------- getAndSetPerson ------\n";
    Person pr( "Me", 233 );
    std::cout << pr.toJsonString().c_str() << std::endl;
    JsonFile< Person > jf;
    jf.setFilename( "person.json" );
    String orgJsonStr="{\"name\":\"tveir\",\"age\":2}";
    jf.setFromJson( pr.toJsonString().c_str() );
    std::cout << "Filename:" << jf.getFilename().c_str() << std::endl;
    // QCOMPARE( jf.getFilename().c_str(), "person.json" );
    // QVERIFY( jf.setFromJson( orgJsonStr.c_str() ) );
    // QCOMPARE( jf.toJsonString().c_str(), orgJsonStr.c_str() );
    std::cout << jf.toJsonString().c_str() << "\n";
}
int main()
{
    std::cout << "Hello world from configurationx\n";
    std::cout << "Json version: " << JSON_VERSION << std::endl;
    JsonG::Json jd( "{\"hello\":\"world\"}" );
    std::cout << jd.toString().c_str() << "\n";
    getAndSetPerson();
}