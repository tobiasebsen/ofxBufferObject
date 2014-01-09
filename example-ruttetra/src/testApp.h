#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxVertexBuffer.h"
#include "ofxTexCoordBuffer.h"
#include "ofxIndexBuffer.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

private:
    
    // Slider callbacks
	void generateIndices(int & n);
	void generateTexCoords();

    ofxPanel panel;
	ofxFloatSlider extrude;
	ofxToggle points;
	ofxToggle smooth;
	ofxIntSlider lines;
	ofxIntSlider columns;
	ofxToggle blend;
	ofxFloatSlider lwidth;

    ofVideoGrabber grabber;
    ofEasyCam cam;
	ofShader shader;
	ofFbo fbo;

	ofxVertexBufferFloat vertices;
	ofxTexCoordBufferFloat texCoords;
	ofxIndexBuffer indices;
	int numIndices;
};
