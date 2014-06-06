/*
 *  ofxIndexBuffer.h
 *
 *  Created by Tobias Ebsen on 5/23/13.
 *
 */

#pragma once
#include "ofxBufferObject.h"

class ofxIndexBuffer : public ofxBufferObjectUint {
public:
	
	void allocate(int count, int usage) {
        ofxBufferObject::allocate(GL_ELEMENT_ARRAY_BUFFER, count * getElementSize(), usage);
    }
	
	void draw(int mode, int count) {
        bind();
        glDrawElements(mode, count, getGlType(), NULL);
        unbind();
    }
    void draw(int mode) {
        draw(mode, getNumElements());
    }
};