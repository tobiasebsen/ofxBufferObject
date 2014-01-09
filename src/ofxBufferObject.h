/*
 *  ofxBufferObject.h
 *
 *  Created by Tobias Ebsen on 3/11/13.
 *
 */

#pragma once
#include "ofMain.h"

class ofxBufferObject {
public:
	ofxBufferObject();
	virtual ~ofxBufferObject();

	// Setup buffer without allocating data
	// target - Usually GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, etc.
	void setup(int target);

	// Allocate the buffer
	// target - Usually GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, etc.
	// size   - Size in bytes
	// usage  - GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
	void allocate(int target, int size, int usage);
	void allocate(int size, int usage);
	
	// Load specific data
	void loadData(void* data, int size, int usage);
	
    // Bind buffer
	void bind(int target);
	void bind();
	void unbind(int target);
	void unbind();
	
    // Map to pointer
	// access - GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE.
	void* map(int target, int access);
	void* map(int target);
	void* map();
	void unmap(int target);
	void unmap();
	
	// Read pixels from currently bound frame buffer
	void readPixels(int x, int y, int width, int height, int format, int type, int offset = 0);
	// Read pixels from specific frame buffer
	void readPixels(ofFbo & fbo, int x, int y, int width, int height);
	void readPixels(ofFbo & fbo);
	
	// Get size of buffer in bytes
	int getSize();

protected:
	void destroy();
	
private:
	GLuint		buffer;
	GLsizei		size;
	GLenum		target;
	GLenum		usage;
	
	bool		bSetup;
	bool		bAllocated;
	int			isBound;
};

template<typename BufferType, GLenum glType>
class ofxBufferObject_ : public ofxBufferObject {
public:
	
	void loadData(BufferType* data, int size) { ofxBufferObject::loadData(data, size); }
	
	BufferType* map(int access, int target) { return (BufferType*)ofxBufferObject::map(access, target); }
	BufferType* map(int access) { return (BufferType*)ofxBufferObject::map(access); }
	BufferType* map() { return (BufferType*)ofxBufferObject::map(); }
	
	GLenum getGlType() { return glType; }
	int getElementSize() { return sizeof(BufferType); }
	int getNumElements() { return getSize() / sizeof(BufferType); }
};

typedef ofxBufferObject_<GLfloat, GL_FLOAT> ofxBufferObjectFloat;
typedef ofxBufferObject_<GLint, GL_INT> ofxBufferObjectInt;
typedef ofxBufferObject_<GLuint, GL_UNSIGNED_INT> ofxBufferObjectUint;
typedef ofxBufferObject_<GLbyte, GL_BYTE> ofxBufferObjectByte;
typedef ofxBufferObject_<GLubyte, GL_UNSIGNED_BYTE> ofxBufferObjectUbyte;

