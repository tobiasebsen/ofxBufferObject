#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    bUsePBO = false;
    
    grabber.initGrabber(640, 480, false);
    
    ofPixelFormat format = grabber.getPixelFormat();
    int glInternalFormat = ofGetGLInternalFormatFromPixelFormat(format);
    texture.allocate(grabber.getWidth(), grabber.getHeight(), glInternalFormat);

    int glFormat = ofGetGLFormatFromInternal(glInternalFormat);
    //pbo.allocate(grabber.getWidth(), grabber.getHeight(), glFormat);
    for (int i=0; i<4; i++) {
        ofxPixelBufferUbyte *buffer = new ofxPixelBufferUbyte();
        buffer->allocate(grabber.getWidth(), grabber.getHeight(), glFormat);
        pbo.addBuffer(buffer);
    }
}

//--------------------------------------------------------------
void testApp::update(){

    grabber.update();
    
    if (grabber.isFrameNew()) {
        
        unsigned long long before = ofGetElapsedTimeMicros();
        
        if (bUsePBO) {
            pbo.loadData(grabber.getPixelsRef());
            pbo.writeToTexture(texture);
        }
        else {
            texture.loadData(grabber.getPixelsRef());
        }
        
        int measured = ofGetElapsedTimeMicros() - before;
        time = measured * 0.05 + time * 0.95;
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    texture.draw(0, 0);
    
    ofDrawBitmapString("Using Pixel Buffer (PBO): " + ofToString(bUsePBO), 20, 20);
    ofDrawBitmapString("Time (micoseconds): " + ofToString(time), 20, 35);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    bUsePBO = !bUsePBO;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

