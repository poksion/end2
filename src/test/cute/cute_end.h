#ifndef __CUTE_END_H
#define __CUTE_END_H

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include <map>
#include <string>
#include <iterator>

//void thisIsATest() {
//	ASSERTM("start writing tests", false);
//}
//
//void runSuite(){
//	cute::suite s;
//	s.push_back(CUTE(thisIsATest));
//	cute::ide_listener lis;
//	cute::makeRunner(lis)(s, "The Suite");
//}

typedef int (*study_function)(void);

class CuteGraphicTest {
public:
    CuteGraphicTest(){}
    virtual ~CuteGraphicTest(){}

    virtual void onCreate() = 0;
    virtual void onRender() = 0;
    virtual void onDestroy() = 0;
};

class CuteGraphicTestSuite {
public:
    std::map<std::string, CuteGraphicTest*> s;
    CuteGraphicTestSuite(){}
    ~CuteGraphicTestSuite(){
        for(std::map<std::string, CuteGraphicTest*>::iterator itr = s.begin(); itr != s.end(); ++itr){
            delete itr->second;
        }
    }
};

class CuteSuite {
public:

	static cute::suite& get_suite(){
		static cute::suite s;
		return s;
	}

	static void add_test(cute::test& t){
		get_suite().push_back(t);
	}

	static bool run_suite(){
	    return run_suite(get_suite());
	}

	static bool run_suite(cute::suite& suite){
		if(suite.empty()){
			return false;
		}

		cute::ide_listener lis;
		cute::makeRunner(lis)(suite, "end2 suite");
		return true;
	}

	static std::map<std::string, CuteGraphicTest*>& get_graphic_suite(){
	    static CuteGraphicTestSuite s;
	    return s.s;
	}

	static void add_graphic_test(CuteGraphicTest* test, std::string& name){
	    get_graphic_suite()[name] = test;
	}
};

class CuteTestAdder {
public:
    CuteTestAdder(cute::test t){
		CuteSuite::add_test(t);
	}
};

#define CUTE_TEST(name) CuteTestAdder testAdder##name(cute::test((&name),(#name)))

class CuteGraphicTestAdder {
public:
    CuteGraphicTestAdder(CuteGraphicTest* t, std::string name){
		CuteSuite::add_graphic_test(t, name);
	}
};

#define CUTE_GRAPHIC_TEST(name) CuteGraphicTestAdder graphicTestAdder##name((new name()),(#name))

class CuteTracer {
public:
	int call_cnt;
	int depth_level;
	CuteTracer(){
		call_cnt = 0;
		depth_level = 0;
	}

	void add_depth(){
		++depth_level;
	}
	void remove_depth(){
		--depth_level;
	}

	std::ostream& print_on_call(){
		++call_cnt;
		std::string depth = "<";
		for(int i = 0; i < depth_level; ++i){
			depth = "    " + depth;
		}
		return std::cout << depth << depth_level << "> (call_cnt:" << call_cnt << ") - ";
	}
};

class CutePrinter {
public:
	template <typename T>
	static void printCollection(const T& in) {
		typename T::const_iterator itr;
		for(itr = in.begin(); itr != in.end(); ++itr){
			if(std::next(itr) == in.end()){
				std::cout << *itr << std::endl;
			} else {
				std::cout << *itr << ", ";
			}
		}
	}

	template <typename T>
	static void printMap(const T& in) {
		typename T::const_iterator itr;
		for(itr = in.begin(); itr != in.end(); ++itr){
			if(itr + 1 == in.end()){
				std::cout << itr->second << std::endl;
			} else {
				std::cout << itr->second << ", ";
			}
		}
	}
};

#endif
