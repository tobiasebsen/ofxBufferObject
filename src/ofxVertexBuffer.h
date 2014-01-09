/*
 *  ofxVertexBuffer.h
 *
 *  Created by Tobias Ebsen on 5/23/13.
 *
 */

#pragma once
#include "ofxBufferObject.h"

template<typename BufferType, GLenum glType>
class ofxVertexBuffer : public ofxBufferObject_<BufferType,glType> {
public:
	
	virtual void allocate(int count, int ncoords, int stride, int usage);
	
	virtual void begin();
	virtual void end();
	
	void draw(int mode, int first, int count);
	void draw(int mode) { draw(mode, 0, count); }
	
	int getCount() { return count; }
	int getNumCoords() { return ncoords; }
	int getStride() { return stride; }

private:
	int count;
	int ncoords;
	int stride;
};

typedef ofxVertexBuffer<GLfloat, GL_FLOAT> ofxVertexBufferFloat;
typedef ofxVertexBuffer<GLint, GL_INT> ofxVertexBufferInt;

template<typename BufferType, GLenum glType>
void ofxVertexBuffer<BufferType,glType>::allocate(int count, int ncoords, int stride, int usage) {
	
	this->count = count;
	this->ncoords = ncoords;
	this->stride = stride == 0 ? ncoords : stride;
	
	ofxBufferObject::allocate(GL_ARRAY_BUFFER, count * stride * sizeof(BufferType), usage);
}

template<typename BufferType, GLenum glType>
void ofxVertexBuffer<BufferType,glType>::begin() {
	
	this->bind(GL_ARRAY_BUFFER);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(ncoords, glType, stride * sizeof(BufferType), NULL);
}

template<typename BufferType, GLenum glType>
void ofxVertexBuffer<BufferType,glType>::end() {
	
	glDisableClientState(GL_VERTEX_ARRAY);
	this->unbind();
}

template<typename BufferType, GLenum glType>
void ofxVertexBuffer<BufferType,glType>::draw(int mode, int first, int count) {
	
	ofxVertexBuffer::begin();
	glDrawArrays(mode, first, count);
	ofxVertexBuffer::end();
}
