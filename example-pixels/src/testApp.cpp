#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(25);
    
    bUsePBO = false;
    
    cpuMemory = (unsigned int*)malloc(2048 * 2048 * sizeof(unsigned int));

    GLenum error = 0;
    glGenTextures( 1, &tex);
    glActiveTexture(GL_TEXTURE0);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    glEnable(GL_TEXTURE_RECTANGLE);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    glBindTexture(GL_TEXTURE_RECTANGLE, tex);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_STORAGE_HINT_APPLE, GL_STORAGE_CACHED_APPLE);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    //glPixelStorei(GL_UNPACK_CLIENT_STORAGE_APPLE, GL_TRUE);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, 2048, 2048, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2048, 2048, GL_RGBA8, GL_UNSIGNED_BYTE, NULL);
    error = glGetError();
    if (error != GL_NO_ERROR) ofLogError("setup()", ofToString(gluErrorString(error)));
    glBindTexture(GL_TEXTURE_RECTANGLE, 0);
    glDisable(GL_TEXTURE_RECTANGLE);

    //texture.allocate(2048, 2048, GL_UNSIGNED_INT_8_8_8_8_REV);
    pbo.allocate(2048, 2048, GL_RGBA32I, GL_STREAM_DRAW);
    /*for (int i=0; i<2; i++) {
        ofxPixelBufferUintRev *buffer = new ofxPixelBufferUintRev();
        buffer->allocate(2048, 2048, GL_RGBA32I);
        pbo.addBuffer(buffer);
    }*/
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (bUsePBO) {
        //pbo.writeToTexture(texture);

        pbo.allocate(2048, 2048, GL_RGBA32I);
        //unsigned int* gpuMemory = (unsigned int*)glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, 2048*2048*4, GL_MAP_WRITE_BIT|GL_MAP_UNSYNCHRONIZED_BIT);
        unsigned int* gpuMemory = (unsigned int*)pbo.map(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
        if (gpuMemory) {
            updatePixels(gpuMemory);
            //glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
            pbo.unmap();
        }
        else {
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) ofLogError("update()", ofToString(gluErrorString(error)));
        }
        

        //glEnable(GL_TEXTURE_RECTANGLE);
        glBindTexture(GL_TEXTURE_RECTANGLE, tex);
        pbo.bind();
        glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_STORAGE_HINT_APPLE, GL_STORAGE_CACHED_APPLE);
        //glPixelStorei(GL_UNPACK_CLIENT_STORAGE_APPLE, GL_TRUE);
        unsigned long long start = ofGetElapsedTimeMicros();
        glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, 2048, 2048, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        time = (ofGetElapsedTimeMicros() - start) * 0.1 + time * 0.9;
        pbo.unbind();
        glBindTexture(GL_TEXTURE_RECTANGLE, 0);
        //glDisable(GL_TEXTURE_RECTANGLE);
        glFlush();

    }
    else {
        updatePixels(cpuMemory);
        
        unsigned long long start = ofGetElapsedTimeMicros();
        glEnable(GL_TEXTURE_RECTANGLE);
        glBindTexture(GL_TEXTURE_RECTANGLE, tex);
        glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, 2048, 2048, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, cpuMemory);
        //glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, 2048, 2048, 0, GL_RGBA, GL_UNSIGNED_BYTE, cpuMemory);
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) ofLogError("update()", ofToString(gluErrorString(error)));
        glBindTexture(GL_TEXTURE_RECTANGLE, 0);
        glDisable(GL_TEXTURE_RECTANGLE);
        //glDisable(GL_TEXTURE0);
        glFlush();
        
        time = (ofGetElapsedTimeMicros() - start) * 0.1 + time * 0.9;
    }
    
}
//--------------------------------------------------------------
void testApp::updatePixels(unsigned int *pixels) {
   
    int w = 2048;
    int h = 2048;
    
    unsigned int c = ofGetFrameNum() % 255;
    
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            pixels[0] = 0xFF000000 | c << 16;
            pixels ++;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    //glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_RECTANGLE);
    glBindTexture(GL_TEXTURE_RECTANGLE, tex);
    
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2i(0, 0);

    glTexCoord2f(2048, 0);
    glVertex2i(512, 0);
    
    glTexCoord2f(2048, 2048);
    glVertex2i(512, 512);

    glTexCoord2f(0, 2048);
    glVertex2i(0, 512);

    glEnd();
    
    glBindTexture(GL_TEXTURE_RECTANGLE, 0);
    glDisable(GL_TEXTURE_RECTANGLE);
    glEnable(GL_BLEND);
    
    ofDrawBitmapString("Use Pixel Buffer Object: " + ofToString(bUsePBO), 20, 20);
    ofDrawBitmapString("Pixel update time: " + ofToString(time) + " microseconds", 20, 35);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    bUsePBO = !bUsePBO;
}
