/*
 *  ofxColorBuffer.h
 *
 *  Created by Tobias Ebsen on 6/9/13.
 *
 */

#pragma once
#include "ofxVertexBuffer.h"

template<typename BufferType, GLenum glType>
class ofxColorBuffer : public ofxVertexBuffer<BufferType,glType> {
public:

	void begin();
	void end();
};

typedef ofxColorBuffer<GLubyte, GL_UNSIGNED_BYTE> ofxColorBufferUbyte;

template<typename BufferType, GLenum glType>
void ofxColorBuffer<BufferType,glType>::begin() {
	this->bind();
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(this->getNumCoords(), glType, this->getStride() * sizeof(BufferType), NULL);
    
}

template<typename BufferType, GLenum glType>
void ofxColorBuffer<BufferType,glType>::end() {
	glDisableClientState(GL_COLOR_ARRAY);
	this->unbind();
}