#pragma once

#include "ofMain.h"
#include "ofxVertexBuffer.h"
#include "ofxTexCoordBuffer.h"
#include "ofxIndexBuffer.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

private:
    
    ofTexture face;
    
    ofEasyCam cam;
	ofShader shader;
	ofFbo fbo;

	ofxVertexBufferVec3f vertices;
	ofxTexCoordBufferVec2f texCoords;
	ofxIndexBuffer indices;
};
