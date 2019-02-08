#pragma once
#include <vector>

#include "LibApi.h"
class LIB_API List : public Object{
    public:
        void render(void * data = nullptr);

        void add(Object* obj);
        void remove(int n);
        void removeLight(int n);
        void removeAll();
		void setMirror(bool mirrorTrue);
		bool getMirror() const;
		int getNumberOfLights() const;
		int getNumberOfObjects() const;
        List();
        virtual ~List();
    private:
		bool mirrorTrue = true;
		void renderTransparentObjects(void * data);
		vector<Object*> transparentObjects;
        vector<Object*> list;
        vector<Light*> lights;

};

