/*
 *  ofxIndexBuffer.cpp
 *
 *  Created by Tobias Ebsen on 5/23/13.
 *
 */

#include "ofxIndexBuffer.h"

void ofxIndexBuffer::allocate(int count, int usage) {

	ofxBufferObject::allocate(GL_ELEMENT_ARRAY_BUFFER, count * getElementSize(), usage);
}

void ofxIndexBuffer::draw(int mode, int count) {
	bind();
	glDrawElements(mode, count, getGlType(), NULL);
	unbind();
}

void ofxIndexBuffer::draw(int mode) {
    draw(mode, getNumElements());
}