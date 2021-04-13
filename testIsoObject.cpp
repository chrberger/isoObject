
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "iso22133object.hpp"


class myDisarmed : public ISO22133::Disarmed {
public:
    /**
     * @brief Called once when entering state
     * 
     * @param obj 
     */
    void onEnter(ISO22133::TestObject& obj) override {
        std::cout << "Entering disarmed" << std::endl;
    }

    /**
     * @brief Called once when leaving state
     * 
     */
    void onExit(ISO22133::TestObject&) override{
        std::cout << "Leaving disarmed" << std::endl;
    }

    /**
     * @brief Overridden function handleHEAB() will be called every time a new
     * HEAB message is reveived
     * 
     */
    void handleHEAB(ISO22133::TestObject&,HeabMessageDataType&) override {
        //std::cout << "Got HEAB in overridden function" << std::endl;
    }
};

class myPreArming : public ISO22133::PreArming {
public:
    void onEnter(ISO22133::TestObject& obj) override{
        std::cout << "Entering Pre-Arming" << std::endl;
        try {
            this->handleEvent(obj, ISO22133::Events::N);
        }
        catch(const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
        }
    }
};



class myObject : public ISO22133::TestObject {

    /**
     * @brief User must override this function for handling internal
     * abort prerequisites of the test object
     * 
     */
	void handleAbort() { std::cout << "Bromsa!" << std::endl;}
    
    /**
     * @brief Create a myDisarmed object. 
     * This is an example of how to override the state creation 
     * functions to get the new state
     * 
     * @return ISO22133::Disarmed* 
     */
    ISO22133::Disarmed* createDisarmed() const override {
		return dynamic_cast<ISO22133::Disarmed*>(new myDisarmed);
	}

    ISO22133::PreArming* createPreArming() const override {
		return dynamic_cast<ISO22133::PreArming*>(new myPreArming);
	}

};




int main(int c, char** argv ) {

	myObject obj;
    while (true) {
        usleep(1000);

        while(obj.isUdpOk()){
            obj.sendMONR();
            usleep(1000);
        }
    }
    
    std::cout << "done\n";
}
