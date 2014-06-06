#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	cam.setupPerspective(true);
    
    ofLoadImage(face, "linzer.png");
    int width = face.getWidth();
    int height = face.getHeight();
    
    shader.load("depthimage.vs", "depthimage.fs");

    fbo.allocate(face.getWidth(), face.getHeight(), GL_RGB32F);
    fbo.createAndAttachTexture(GL_RGB32F, 1);
    
    fbo.begin();
    
    int att[] = {0, 1};
    fbo.setActiveDrawBuffers(vector<int>(att, att + sizeof(att) / sizeof(int)));
    
    ofClear(0);
    
    shader.begin();
    shader.setUniform2f("size", face.getWidth(), face.getHeight());
    face.draw(0, 0);
    shader.end();
    
    fbo.end();
    
    vertices.allocate(fbo.getWidth()*fbo.getHeight(), 3, 1, GL_STATIC_COPY);
    vertices.readPixels(fbo, 1);
    
    texCoords.allocate(fbo.getWidth()*fbo.getHeight(), 2, 1, GL_STATIC_COPY);
    ofVec2f *tdata = texCoords.map();
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            tdata->x = x;
            tdata->y = y;
            tdata++;
        }
    }
    texCoords.unmap();
    
    int w = face.getWidth();
    int h = face.getHeight();
    float incx = (float)width / w;
    float incy = (float)height / h;
    
    indices.allocate(w * h * 6, GL_STATIC_COPY);
    
    GLuint *idata = indices.map();
    int ystride = width * roundf(incy);
    for (float fy=0; fy<height-1; fy+=incy) {
        int offset = width * (int)roundf(fy);
        for (float fx=0; fx<width-1; fx+=incx) {
            int x = offset + roundf(fx);
            int x2 = offset + roundf(fx+incx);
            idata[0] = x;
            idata[1] = x + ystride;
            idata[2] = x2 + ystride;
            idata[3] = x2 + ystride;
            idata[4] = x;
            idata[5] = x2;
            idata += 6;
        }
    }
    indices.unmap();

    ofBackground(40);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
    
    ofDisableAlphaBlending();
    ofEnableDepthTest();
    ofTranslate(-face.getWidth()/2, -face.getHeight()/2);
    
    ofScale(face.getWidth(), face.getHeight(), 600);
    ofTranslate(0, 0, -0.5);
    
    vertices.begin();
    texCoords.begin(face);
    indices.draw(GL_TRIANGLES);
    texCoords.end(face);
    vertices.end();
    
    cam.end();
}

