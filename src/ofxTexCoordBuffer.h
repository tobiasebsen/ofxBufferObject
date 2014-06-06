/*
 *  ofxTexCoordBuffer.h
 *
 *  Created by Tobias Ebsen on 5/23/13.
 *
 */

#pragma once
#include "ofxVertexBuffer.h"

template<typename BufferType, GLenum glType>
class ofxTexCoordBuffer : public ofxVertexBuffer<BufferType,glType> {
public:
	
	void begin();
    void begin(ofTexture & tex);
    void begin(ofBaseHasTexture & base);

	void end();
    void end(ofTexture & tex);
    void end(ofBaseHasTexture & base);
};

typedef ofxTexCoordBuffer<GLfloat,GL_FLOAT> ofxTexCoordBufferFloat;
typedef ofxTexCoordBuffer<ofVec2f,GL_FLOAT> ofxTexCoordBufferVec2f;

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::begin() {
	this->bind(GL_ARRAY_BUFFER);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(this->getNumCoords(), glType, this->getStride() * sizeof(BufferType), NULL);
}

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::begin(ofTexture & tex) {
    tex.bind();
    this->begin();
}

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::begin(ofBaseHasTexture & base) {
    this->begin(base.getTextureReference());
}

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::end() {
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	this->unbind(GL_ARRAY_BUFFER);
}

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::end(ofTexture & tex) {
    this->end();
    tex.unbind();
}

template<typename BufferType, GLenum glType>
void ofxTexCoordBuffer<BufferType,glType>::end(ofBaseHasTexture & base) {
    this->end(base.getTextureReference());
}
