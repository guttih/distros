#include <iostream>

 #include <Json/Json.h>
#include <Json/JsonFile.h>
#include <Json/JsonFileCollection.h>
#include "Json/Version.h"
#include "Person.cpp"
#include "ConfigurationConfig.h"
// #include <Json/JsonGConfig.h>



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
    std::cout << jf.toJsonString().c_str() << "\n";
}

void getAndSetPersonCollection()
{
    std::cout << "------- getAndSetPersonCollection ------\n";
    Person person( "Gudjon", 51 );;
    JsonFileCollection< Person > coll( "coll-person.json" );
    coll.addItem( person );
}
int main()
{
    Version versionConfig( Configuration_VERSION_STRING );
    // Version versionJsonG( JsonG_VERSION_STRING );
    std::cout << "Configuration version : " << versionConfig.c_str() << "\n";
    // std::cout << "JsonG version         : " << versionJsonG.c_str() << "\n";
    getAndSetPersonCollection();
    std::cout << "Hello world from configurationx\n";
    JsonG::Json json( "{ \"One\": 1 }" );
    std::cout << json.toString().c_str() << "\n";
    getAndSetPerson();

    JsonData *jd = json.getRootObject();
    String now = jd->getChildAt( 0 )->getValue();
    std::string ss = now.c_str();
    std::cout << "aaaa" << ss << "\n";
    std::cout << "bbbb" << jd->toString().c_str() << "\n";


}
