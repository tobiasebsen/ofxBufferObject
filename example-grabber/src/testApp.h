#pragma once

#include "ofMain.h"
#include "ofxPixelBuffer.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

    ofVideoGrabber grabber;
    ofTexture texture;
    ofxPixelBufferMulti<unsigned char,GL_UNSIGNED_BYTE> pbo;
    
    bool bUsePBO;
    int time;
};
