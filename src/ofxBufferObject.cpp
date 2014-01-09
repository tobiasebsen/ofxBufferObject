/*
 *  ofxBufferObject.cpp
 *
 *  Created by Tobias Ebsen on 3/11/13.
 *
 */

#include "ofxBufferObject.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

ofxBufferObject::ofxBufferObject() {
	buffer = 0;
	size = 0;
	target = GL_ARRAY_BUFFER;
	usage = GL_STATIC_DRAW;
	bSetup = false;
	bAllocated = false;
	isBound = 0;
}

ofxBufferObject::~ofxBufferObject() {
	destroy();
}

void ofxBufferObject::setup(int target) {
	
	this->target = target;

	glGenBuffers(1, &buffer);
	
	bSetup = true;
}

void ofxBufferObject::allocate(int target, int size, int usage) {
	
	if (!bSetup)
		setup(target);
	
	this->size = size;
	this->usage = usage;
	
	glBindBuffer(target, buffer);
	glBufferData(target, size, NULL, usage);
	glBindBuffer(target, 0);
	
	bAllocated = true;
}

void ofxBufferObject::allocate(int size, int usage) {
	allocate(target, size, usage);
}

void ofxBufferObject::loadData(void* data, int size, int usage) {

	if (!bSetup)
		setup(target);
	
	this->size = size;
	this->usage = usage;
	
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);
	glBindBuffer(target, 0);
	
	bAllocated = true;
}

void ofxBufferObject::destroy() {
	if (bSetup) {
		glDeleteBuffers(1, &buffer);
		buffer = 0;
	}
	bSetup = false;
}

void ofxBufferObject::bind(int target) {
	if (!isBound)
		glBindBuffer(target, buffer);
	isBound++;
}

void ofxBufferObject::bind() {
	if (!isBound)
		glBindBuffer(target, buffer);
	isBound++;
}

void ofxBufferObject::unbind(int target) {
	if (isBound)
		isBound--;
	if (!isBound)
		glBindBuffer(target, 0);
}

void ofxBufferObject::unbind() {
	if (isBound)
		isBound--;
	if (!isBound)
		glBindBuffer(target, 0);
}

void* ofxBufferObject::map(int target, int access) {
	
	bind(target);
	
	void* data = glMapBuffer(target, access);
	if (data == NULL) {
		unbind(target);
		GLenum error = glGetError();
		string s((char*)gluErrorString(error));
		ofLog(OF_LOG_ERROR, s);
	}
	return data;
}

void* ofxBufferObject::map(int target) {
	return map(target, GL_READ_WRITE);
}

void* ofxBufferObject::map() {
	return map(target);
}

void ofxBufferObject::unmap(int target) {
	glUnmapBuffer(target);
	unbind(target);
}

void ofxBufferObject::unmap() {
	glUnmapBuffer(target);
	unbind(target);
}

void ofxBufferObject::readPixels(int x, int y, int width, int height, int format, int type, int offset) {

	bind(GL_PIXEL_PACK_BUFFER);
	
	glReadPixels(x, y, width, height, format, type, BUFFER_OFFSET(offset));
	
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		string s((char*)gluErrorString(error));
		ofLog(OF_LOG_ERROR, s);
	}
	
	unbind(GL_PIXEL_PACK_BUFFER);
}

void ofxBufferObject::readPixels(ofFbo & fbo, int x, int y, int width, int height) {

	ofTextureData texData = fbo.getTextureReference().getTextureData();
	
	GLint temp;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &temp);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo.getFbo());
	
    GLint format = ofGetGLFormatFromInternal(texData.glTypeInternal);
    GLint type = ofGetGlTypeFromInternal(texData.glTypeInternal);
	readPixels(x, y, width, height, format, type, 0);
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, temp);
}

void ofxBufferObject::readPixels(ofFbo & fbo) {
	readPixels(fbo, 0, 0, fbo.getWidth(), fbo.getHeight());
}

int ofxBufferObject::getSize() {
	return size;
}
