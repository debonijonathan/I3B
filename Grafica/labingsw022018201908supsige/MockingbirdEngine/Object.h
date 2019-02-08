#pragma once
#include <string>

using namespace std;

#include "LibApi.h"
class LIB_API Object {
    public:
        int getId();

        string getName();
		string getType();
        void setName(string name);
		void setType(string type);
        virtual void render(void * data = nullptr);
        Object();
        Object(string name);
        virtual ~Object();

	private:
		int id;
		void setId();
		static int autoId;
        string name;
		string type;
};

