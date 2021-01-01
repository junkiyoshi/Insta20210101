#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofSetCircleResolution(60);
	ofEnableDepthTest();

	font.loadFont("fonts/Kazesawa-Bold.ttf", 230, true, true, true);
	/* https://github.com/kazesawa/kazesawa */
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int radius = 50;

	ofFill();
	ofSetColor(230, 0, 82);
	ofDrawCircle(glm::vec2(ofGetWidth() * -0.1, 0), radius);

	auto deg_span = 5;
	for (auto deg_start = ofGetFrameNum() * 0.125; deg_start <= ofGetFrameNum() * 0.5 + 360; deg_start += deg_span * 2) {

		vector<glm::vec2> vertices_1, vertices_2;
		for (auto deg = deg_start; deg <= deg_start + deg_span; deg++) {

			vertices_1.push_back(glm::vec2((radius + 10) * cos(deg * DEG_TO_RAD) - ofGetWidth() * 0.1, (radius + 10) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius * 15) * cos(deg * DEG_TO_RAD) - ofGetWidth() * 0.1, (radius * 15) * sin(deg * DEG_TO_RAD)));
		}

		reverse(vertices_2.begin(), vertices_2.end());

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);
	}

	auto word = "2  21";
	auto bound = this->font.getStringBoundingBox(word, 0, 0);
	auto path_list = font.getStringAsPoints(word, true, false);
	for (auto path : path_list) {

		auto outline = path.getOutline();

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(300);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - bound.width * 0.5, vertices[vertices_index].y + bound.height * 0.5, 1);
				ofVertex(location);
			}
		}
		ofEndShape();

		ofNoFill();
		ofSetColor(230, 0, 82);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			outline[outline_index] = outline[outline_index].getResampledByCount(300);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec3(vertices[vertices_index].x - bound.width * 0.5, vertices[vertices_index].y + bound.height * 0.5, 1);
				ofVertex(location);
			}
		}
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}