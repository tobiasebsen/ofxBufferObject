#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	panel.setup("Settings");
	panel.add(extrude.setup("Extrude", 200, 0, 1000));
	panel.add(points.setup("Points", false));
	panel.add(smooth.setup("Smooth", true));
	panel.add(lines.setup("Lines", 120, 1, 480));
	panel.add(columns.setup("Columns", 120, 1, 640));
	panel.add(blend.setup("Blend", true));
	panel.add(lwidth.setup("Width", 1, 0.1, 5));
	
	lines.addListener(this, &testApp::generateIndices);
	columns.addListener(this, &testApp::generateIndices);
    
	cam.setupPerspective(true);
	
	grabber.initGrabber(640, 480);
    
	fbo.allocate(grabber.getWidth(), grabber.getHeight(), GL_RGB32F);
    
	shader.load("ruttetra.vs", "ruttetra.fs");
	shader.begin();
	shader.setUniform2f("size", fbo.getWidth(), fbo.getHeight());
	shader.end();

	int width = fbo.getWidth();
	int height = fbo.getHeight();
	vertices.allocate(width * height, 3, 1, GL_DYNAMIC_COPY);
	texCoords.allocate(width * height, 2, 1, GL_STATIC_COPY);
	indices.allocate((width-1)*(height-1)*2, GL_STATIC_COPY);
    
    int n = lines;
	generateIndices(n);
	generateTexCoords();

    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::generateIndices(int & n) {
    
	int width = fbo.getWidth();
	int height = fbo.getHeight();
	float incy = (float)height / lines;
	float incx = (float)width / columns;
    
	GLuint *idata = indices.map();
	int last = 0;
	
    for (float fy = 0; fy < height - 1 ; fy+=incy) {
		int offset = last = round(fy) * width;
		for (float fx = 0; fx < width - 1 ; fx+=incx) {
			idata[0] = last;
			idata[1] = last = offset + round(fx);
            idata+=2;
		}
	}
	indices.unmap();
	numIndices = (lines-1) * (columns-1) * 2;
}

//--------------------------------------------------------------
void testApp::generateTexCoords() {
    
	int width = fbo.getWidth();
	int height = fbo.getHeight();
	
    ofVec2f *tdata = texCoords.map();
    
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			tdata->x = x;
			tdata->y = y;
            tdata++;
		}
	}
	texCoords.unmap();
}

//--------------------------------------------------------------
void testApp::update(){

    grabber.update();
	if (grabber.isFrameNew()) {

        glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);

		fbo.begin();
		
		shader.begin();
		grabber.draw(0, 0);
		shader.end();
		
		vertices.readPixels(fbo);
		
		fbo.end();

        glPopAttrib();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
    //ofPushView();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
	ofTranslate(-grabber.getWidth()/2, -grabber.getHeight()/2, 0);
	ofScale(grabber.getWidth(), grabber.getHeight(), extrude);
    
    if (blend) ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    else ofDisableBlendMode();
    
	if (smooth) {
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POINT_SMOOTH);
	}

	glLineWidth(lwidth);
	glPointSize(lwidth);
    
    
	vertices.begin();
	texCoords.begin(grabber);
	indices.draw(points ? GL_POINTS : GL_LINES, numIndices);
	texCoords.end(grabber);
	vertices.end();
    
    glPopAttrib();
    //ofPopView();
    cam.end();

    panel.draw();
}

