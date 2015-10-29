#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <iostream>


//define app class
class hello : public cppcms::application {
public:
    hello(cppcms::service &serv): cppcms::application(serv)
    {}
    virtual void main(std::string url);
};


void hello::main(std::string /*url*/){
    response().out() << "<html><body><h1>Hello CppCMS</h1></body></html>\n";
}

int main(int argc, char** argv){
    try {
        cppcms::service serv(argc, argv);
        serv.applications_pool().mount(cppcms::applications_factory<hello>());
        serv.run();
    }
    catch (std::exception const &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
