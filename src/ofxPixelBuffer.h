//
//  ofxPixelBuffer.h
//
//  Created by Tobias Ebsen on 16/03/14.
//
//

#pragma once

#include "ofxBufferObject.h"

template<typename BufferType, GLenum glType>
class ofxPixelBuffer : public ofxBufferObject_<BufferType,glType> {
public:

    void allocate(int width, int height, int glFormat = GL_RGBA, int usage = GL_STREAM_DRAW) {
        ofxBufferObject::allocate(GL_PIXEL_UNPACK_BUFFER, width * height * ofGetNumChannelsFromGLFormat(glFormat) * this->getElementSize(), usage);
    }
    
    void writeToTexture(ofTexture & tex) {
        tex.bind();
        this->bind();
        ofTextureData & data = tex.getTextureData();
        int format = ofGetGLFormatFromInternal(data.glTypeInternal);
        int type = ofGetGlTypeFromInternal(data.glTypeInternal);
        
        glTexSubImage2D(data.textureTarget, 0, 0, 0, data.tex_w, data.tex_h, format, type, NULL);
        //glTexImage2D(data.textureTarget, 0, data.glTypeInternal, data.tex_w, data.tex_h, 0, format, type, NULL);
        
        int err = glGetError();
        if (err != GL_NO_ERROR) {
            ofLogError("ofxPixelBuffer", ofToString(gluErrorString(err)));
        }

        this->unbind();
        tex.unbind();
    }
};

typedef ofxPixelBuffer<unsigned char,GL_UNSIGNED_BYTE> ofxPixelBufferUbyte;
typedef ofxPixelBuffer<unsigned short,GL_UNSIGNED_BYTE> ofxPixelBufferUshort;
typedef ofxPixelBuffer<unsigned int,GL_UNSIGNED_INT_8_8_8_8> ofxPixelBufferUint;
typedef ofxPixelBuffer<unsigned int,GL_UNSIGNED_INT_8_8_8_8_REV> ofxPixelBufferUintRev;
typedef ofxPixelBuffer<float,GL_FLOAT> ofxPixelBufferFloat;

template<typename BufferType, GLenum glType>
class ofxPixelBufferMulti {
public:
    ofxPixelBufferMulti() : index(0) {}

    void addBuffer(ofxPixelBuffer<BufferType,glType>* buf) {
        buffers.push_back(buf);
    }
    BufferType* map() {
        return buffers[nextindex]->map(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    }
    void unmap() {
        buffers[nextindex]->unmap();
    }
    void writeToTexture(ofTexture & tex) {
        index = (index+1) % buffers.size();
        nextindex = (index+1) % buffers.size();
        buffers[index]->writeToTexture(tex);
    }
    
private:
    vector<ofxPixelBuffer<BufferType,glType>*> buffers;
    int index,nextindex;
};

typedef ofxPixelBufferMulti<unsigned char,GL_UNSIGNED_BYTE> ofxPixelBufferMultiUbyte;
typedef ofxPixelBufferMulti<unsigned int,GL_UNSIGNED_INT_8_8_8_8> ofxPixelBufferMultiUint;
typedef ofxPixelBufferMulti<unsigned int,GL_UNSIGNED_INT_8_8_8_8_REV> ofxPixelBufferMultiUintRev;
