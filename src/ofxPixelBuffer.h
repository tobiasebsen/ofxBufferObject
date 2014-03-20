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
        
        this->unbind();
        tex.unbind();
    }
};

typedef ofxPixelBuffer<unsigned char,GL_UNSIGNED_BYTE> ofxPixelBufferUbyte;