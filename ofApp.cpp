#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofRotate(270);

	ofColor color;
	for (int radius = 50; radius <= 320; radius += 10) {

		int deg_start = radius * 0.5 + ofGetFrameNum() * 2.16;
		for (int deg = deg_start; deg < deg_start + 360; deg += 60) {

			vector<glm::vec2> vertices;
			for (int tmp_deg = deg; tmp_deg <= deg + 90; tmp_deg += 1) {

				vertices.push_back(glm::vec2(this->make_point(radius, tmp_deg)));
			}

			color.setHsb(
				ofMap(deg, deg_start, deg_start + 360, 0, 255),
				130,
				ofMap(radius, 50, 320, 0, 255));

			ofFill();
			ofSetColor(color);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(ofMap(radius, 50, 320, 0, 255));
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int radius, int deg) {

	deg = deg % 360;

	int deg_a = (deg / 60) * 60;
	int deg_b = deg_a + 60;

	int remainder = deg % 60;
	int diff = deg - deg_a;

	auto point_a = glm::vec2(radius * cos(deg_a * DEG_TO_RAD), radius * sin(deg_a * DEG_TO_RAD));
	auto point_b = glm::vec2(radius * cos(deg_b * DEG_TO_RAD), radius * sin(deg_b * DEG_TO_RAD));
	auto distance = point_b - point_a;

	return point_a + (distance / 60) * diff;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}