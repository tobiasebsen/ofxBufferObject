#pragma once

#include "ofMain.h"
#include "ofxPixelBuffer.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void updatePixels(unsigned int* pixels);
		void draw();

		void keyPressed(int key);

    GLuint tex;
    ofTexture texture;
    ofxPixelBufferUintRev pbo;
    unsigned int* cpuMemory;
    
    bool bUsePBO;
    int time;
};
