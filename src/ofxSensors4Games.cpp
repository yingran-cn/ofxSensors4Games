#include "ofxSensors4Games.h"

/*
    If you are struggling to get the device to connect ( especially Windows Users )
    please look at the ReadMe: in addons/ofxKinect/README.md
*/

//--------------------------------------------------------------
void ofxSensors4Games::setup(sensorType _myType, sensorMode _modeSensor, RecognitionMethod _myComputeBlobType) {
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//required calls
	SensorManager::getInstance()->setSensorType(_myType);
	SensorManager::getInstance()->setSensorMode(_modeSensor);
	
	//SensorManager::getInstance()->typeSensor = _myType;
	//SensorManager::getInstance()->modeSensor = _modeSensor;
	
	gui.setup();
	
	//setups managers with selected SensorType
	
	SensorManager::getInstance()->setup(_myType, _modeSensor);

	myControllerRecognition1.setup(
								SensorManager::getInstance()->getWidth(),
								SensorManager::getInstance()->getHeight(),
								_myComputeBlobType,
								SensorManager::getInstance()->computerVisionSensor1.contourFinder,
								1
								);

	myControllerRecognition2.setup(
								SensorManager::getInstance()->getWidth(),
								SensorManager::getInstance()->getHeight(),
								_myComputeBlobType,
								SensorManager::getInstance()->computerVisionSensor2.contourFinder,
								2
								);
	
	
}

//--------------------------------------------------------------
void ofxSensors4Games::update() {
	
	SensorManager::getInstance()->update();
	
	if (SensorManager::getInstance()->bArea1) {
		myControllerRecognition1.update(SensorManager::getInstance()->rectArea1);
	}
	if (SensorManager::getInstance()->bArea2) {
		myControllerRecognition2.update(SensorManager::getInstance()->rectArea2);
	}
}

//--------------------------------------------------------------
void ofxSensors4Games::draw() {
	
	///////////////////////////////////////////////////////////////
	//Gui Draw and controls
	
	//required to call this at beginning
	gui.begin();
	string frameRateAvailable = "Fps: " + ofToString(ofGetFrameRate(), 0);
	ImGui::Text("Sensors For Games!");
	
	ImGui::Text(frameRateAvailable.c_str());
	
	//TODO
	//Set here Sensor Selections
	//Set Here a button to Save all params in XML or Json
	//Activate and Address OSC data
	//Check here values to send and change tags if its necesary
	
	//General Draws with possibles Guis windows
	SensorManager::getInstance()->draw();
	
	if (SensorManager::getInstance()->bArea1)
	myControllerRecognition1.draw();
	
	if (SensorManager::getInstance()->bArea2)
	myControllerRecognition2.draw();
	
	//required to call this at end
	gui.end();
	
    
}


//--------------------------------------------------------------
void ofxSensors4Games::exit() {
	myControllerRecognition1.exit();
	myControllerRecognition2.exit();
	SensorManager::getInstance()->exit();
}

//-------------------------------------------------------------
bool ofxSensors4Games::loadAllParamters() {

	string filePath = "allMyParams.json";
	ofxJSONElement jPreset = loadJSON(filePath);

	/*
	ofxJSONElement jElement;
	for (int i = 0; i < thisPair.size(); i++) {
	}

	if (!checkIfSetExists(thisPair.first))
	{
		presetsBank.addSet(thisPair.first);
	}

	presetsBank.addPreset(thisPair.second, thisPair.first, jPreset);
	*/

	return true;
}


//-------------------------------------------------------------
ofxJSONElement ofxSensors4Games::loadJSON(string filePathName)
{
	ofxJSONElement jElement;
	bool parse = false;
	ofLogVerbose() << "Trying to load config at: " + filePathName;
	parse = jElement.open(filePathName);

	ofLogVerbose() << "ConfigLoaded";
	return jElement;
}

//------------------------------------------------------------
bool ofxSensors4Games::saveAllParams() {

	allParametersGui.clear();

	ofxJSONElement paramsRecognition1 = myControllerRecognition1.getParams();
	ofxJSONElement paramsRecognition2 = myControllerRecognition2.getParams();
	ofxJSONElement paramsSensor = SensorManager::getInstance()->getParams();

	allParametersGui.append(paramsRecognition1);
	allParametersGui.append(paramsRecognition2);
	allParametersGui.append(paramsSensor);
	/*
	int j = 0;
	for (auto it = paramsRecognition1.begin(); it != paramsRecognition1.end(); it++, j++){
		allParametersGui[it->first] = it->second;
	}

	ofxJSONElement paramsRecognition2 = myControllerRecognition1.getParams();
	j = 0;
	for (auto it = paramsRecognition2.begin(); it != paramsRecognition2.end(); it++, j++) {
		allParametersGui[it->first] = it->second;
	}

	ofxJSONElement paramsSensor = SensorManager::getInstance()->getParams();
	j = 0;
	for (auto it = paramsSensor.begin(); it != paramsSensor.end(); it++, j++) {
		allParametersGui[it->first] = it->second;
	}
	*/
	allParametersGui.save("allMyParams.json", true);

	return true;
}


/* Save some data example with Json ( need addon ofxJson)
//---------------------------------------------------------------------
void saveData() {
	
	//A fucntion to save all the array of pressets in a current Json
	ofxJSONElement saverySchedulerJS;

	saverySchedulerJS["Items"]["Description"] = myDynamicSchedulerPresetsVector[i].internalDescription;
	saverySchedulerJS["presetName"] = myDynamicSchedulerPresetsVector[i].typePresetName;
	saverySchedulerJS["Config"]["bSchedulerActive"] = bSchedulerActive;
	
	string name2Save = savefolder + fileName;
	saverySchedulerJS.save(name2Save, true);
}
 */
