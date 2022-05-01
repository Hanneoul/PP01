//#pragma once
//#pragma once
//#define _CRTDBG_MAP_ALLOC
//
//#pragma comment (lib, "opengl32.lib")
//
//#include <GL/glew.h>		
//#include <GLFW/glfw3.h> 
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//
//#include <cmath>
//#include <ctime>
//#include <crtdbg.h>
//#include <queue>
//#include <mutex>
//
//using namespace std;
//
//#include "CommaxLidarHelper.hpp"
//#include "OpenGLHelper.hpp"
//
//
//#ifdef _DEBUG
//#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#endif //_DEBUG
//
//queue<glm::vec3> detectQueue;
//mutex mut;
//
//GLFWwindow* win;
//GLuint vertexShader;
//GLuint fragmentShader;
//GLuint shaderProgramID;
//GLuint MVPMatrixID;
//
////OpenGLCamera g_Cam;
//
//GLuint pointVAO, pointVBO, pointColorVBO, pointCount, pointOffset;
//GLuint gridLineVAO, gridLineVBO, gridLineColorVBO, gridLineCount;
//GLuint triangleVAO, triangleVBO, triangleColorVBO, triangleCount;
//
//double lastTime = glfwGetTime();
//int numOfFrames = 0;
//
////라이다 버퍼
//vector<float> pointVBuf(60000);
//vector<float> pointCBuf(60000);
//
//
//void keyCB(GLFWwindow* window, int key, int scancode, int action, int mods);
//void GLInitialize();
//void GLUpdate();
//void GLRelease();
//
//void CreateShader();
//void CreatePointBuffer();
//void CreateGridLineBuffer();
//bool UpdatePointBuffer();
//
//extern "C" __declspec(dllexport) void SetLiDARInitialTransform(float x, float y, float z, float height);
//extern "C" __declspec(dllexport) void SetLiDARInitialZone(int xcount, int ycount, int zcount);
//extern "C" __declspec(dllexport) void LiDARPreScan(float sec);
//extern "C" __declspec(dllexport) void LiDARScan(float sec, int filterLevel, int detectionLevel);
//extern "C" __declspec(dllexport) void OpenGLWindow();
//
//extern "C" __declspec(dllexport) int getDetection(float* input);
//extern "C" __declspec(dllexport) int getDetectionSize();
//extern "C" __declspec(dllexport) float getDetectionX();
//extern "C" __declspec(dllexport) float getDetectionY();
//extern "C" __declspec(dllexport) float getDetectionZ();
//extern "C" __declspec(dllexport) void getDetectionPop();
//
//
//void keyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
//		RotX -= 5.f;
//	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
//		RotX += 5.f;
//	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//		RotY += 5.f;
//	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
//		RotZ += 5.f;
//	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
//		RotZ -= 5.f;
//}
//void GLInitialize() {
//	win = InitGLWindow(800, 600, "Commax LiDAR Viewer", keyCB, framebufferSizeCallback, errorCallback, 1);
//
//	if (win == NULL) {
//		cerr << "Error: GLFW Window 생성 실패" << endl;
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	CreateShader();
//	CreatePointBuffer();
//	CreateGridLineBuffer();
//
//}
//void GLUpdate()
//{
//	double currentTime = glfwGetTime();
//	numOfFrames++;
//	if (currentTime - lastTime >= 1.0) {
//
//		//printf("%f ms/frame  %d fps \n", 1000.0 / double(numOfFrames), numOfFrames);
//		numOfFrames = 0;
//		lastTime = currentTime;
//	}
//
//	glClearColor((GLclampf)0.0, (GLclampf)0.0, (GLclampf)0.2, (GLclampf)1.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//
//
//	//카메라 부분
//	float FoV = 45.0f;
//
//	glm::mat4 projectionMatrix = glm::perspective(
//		glm::radians(FoV),  // 수직방향 시야각입니다 : "줌"의 크기. "카메라 렌즈" 를 생각해보세요. 이들은 보통 90도 (엑스트라 와이드) 에서 30도 (크게 확대한 경우) 사이에 있습니다
//		4.0f / 3.0f, // 화면 비 입니다. 이것은 당신의 윈도우 크기에 의존합니다. 4/3 == 800/600 == 1280/960 인데, 어디서 본것 같죠 ?
//		0.1f,        // Near clipping plane (근거리 잘라내기 평면). 최대한 크게 하세요. 아니면 정확도 문제가 생길 수 있습니다.
//		1000.0f       // Far clipping plane (원거리 잘라내기 평면). 최대한 작게 하세요.
//	);
//
//	// 카메라 매트릭스
//	glm::mat4 View = glm::lookAt(
//		glm::vec3(RotX, RotY, RotZ), // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
//		glm::vec3(0, 0, 0), // 그리고 카메라가 원점을 본다
//		glm::vec3(0, 1, 0)  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
//	);
//
//	glm::mat4 Model = glm::mat4(1.0f);
//	glm::mat4 mvp = projectionMatrix * View * Model;
//
//
//	glUseProgram(shaderProgramID);
//	glBindVertexArray(gridLineVAO);
//	glUniformMatrix4fv(MVPMatrixID, 1, GL_FALSE, &mvp[0][0]);
//	glDrawArrays(GL_LINES, 0, gridLineCount);
//
//	//if (buffer_x.size() != 0)
//	//{
//
//	//	if (!definePointVertexArrayObject(shaderProgramID)) {
//
//	//		cerr << "Error: Shader Program 생성 실패" << endl;
//
//	//		glfwTerminate();
//	//		std::exit(EXIT_FAILURE);
//	//	}
//
//	//	//glUseProgram(pointShaderProgramID);
//	//	glBindVertexArray(pointVertexArrayObject);
//	//	//glUniformMatrix4fv(PointMatrixID, 1, GL_FALSE, &mvp[0][0]);
//	//	glDrawArrays(GL_POINTS, 0, (GLsizei)vBuffer.size());
//	//}
//
//	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//	void* VBO = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//	if (!VBO) {
//		std::cout << "Error: cannot get VBO" << std::endl;
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		return;
//	}
//
//	UpdatePointBuffer();
//
//	// updating data
//	memcpy((char*)VBO, pointVBuf.data(), sizeof(float) * pointVBuf.size());
//	//데이터 변경 타이밍
//
//	glUnmapBuffer(GL_ARRAY_BUFFER);
//	////target + offset
//	////glDrawArrays(GL_POINTS, target, target + offset);
//
//	//glBindVertexArray(pointVAO);
//
//	//glDrawArrays(GL_POINTS, 0, pointCount);
//
//	glDeleteVertexArrays(1, &pointVAO);
//
//	if (!CreateVAO_vc(pointVAO, pointVBO, pointColorVBO, shaderProgramID))
//	{
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	glBindVertexArray(pointVAO);
//
//	glDrawArrays(GL_POINTS, 0, pointCount);
//
//	glfwSwapBuffers(win);
//	glfwPollEvents();
//
//}
//void GLRelease() {
//
//	glUseProgram(0);
//	glBindVertexArray(0);
//
//	glDeleteProgram(shaderProgramID);
//	glDeleteBuffers(1, &pointVBO);
//	glDeleteBuffers(1, &pointColorVBO);
//	glDeleteVertexArrays(1, &pointVAO);
//
//	glDeleteBuffers(1, &gridLineVBO);
//	glDeleteBuffers(1, &gridLineColorVBO);
//	glDeleteVertexArrays(1, &gridLineVAO);
//
//	glDeleteBuffers(1, &triangleVBO);
//	glDeleteBuffers(1, &triangleColorVBO);
//	glDeleteVertexArrays(1, &triangleVAO);
//
//	glfwTerminate();
//}
//
//void CreateShader() {
//	string vsSource = readShaderSource("vs.glsl");
//	string fsSource = readShaderSource("fs.glsl");
//
//	if (!initShader(vertexShader, vsSource.c_str(), GL_VERTEX_SHADER)) {
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//	if (!initShader(fragmentShader, fsSource.c_str(), GL_FRAGMENT_SHADER)) {
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	if (!initVFShaderProgram(shaderProgramID, vertexShader, fragmentShader)) {
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	MVPMatrixID = glGetUniformLocation(shaderProgramID, "MVP");
//}
//void CreatePointBuffer() {
//
//
//	pointOffset = 0;
//
//	glGenBuffers(1, &pointVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointVBuf.size(), pointVBuf.data(), GL_STREAM_DRAW);
//
//	//glVertexPointer(2, GL_FLOAT, sizeof(vertexStatic), (void*)offsetof(vertexStatic, position));
//
//	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
//
//
//	for (int i = 0; i < (pointCBuf.size() / 3); i++)
//	{
//
//		pointCBuf[3 * i] = 1.0f;
//		pointCBuf[3 * i + 1] = 1.0f;
//		pointCBuf[3 * i + 2] = 0.0f;
//	}
//
//
//	glGenBuffers(1, &pointColorVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, pointColorVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointCBuf.size(), pointCBuf.data(), GL_STATIC_DRAW);
//
//
//	/*if (!CreateVAO_vc(pointVAO, pointVBO, pointColorVBO, shaderProgramID))
//	{
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}*/
//	pointCount = (GLuint)pointVBuf.size();
//}
//void CreateGridLineBuffer() {
//	vector<float> gridLineVBuf(0);
//	vector<float> gridLineCBuf(0);
//
//	float max_CoordX = 30.0f;
//	float min_CoordX = -30.0f;
//	float max_CoordZ = 30.0f;
//	float min_CoordZ = -30.0f;
//	float intervalX = 0.5f;
//	float intervalZ = 0.5f;
//
//	float colorX = 0.3f;
//
//	for (float i = min_CoordX; i <= max_CoordX; i = i + intervalX)
//	{
//		gridLineVBuf.push_back(i);
//		gridLineVBuf.push_back(0.0f);
//		gridLineVBuf.push_back(min_CoordZ);
//
//		gridLineVBuf.push_back(i);
//		gridLineVBuf.push_back(0.0f);
//		gridLineVBuf.push_back(max_CoordZ);
//
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//
//	}
//	for (float i = min_CoordZ; i <= max_CoordZ; i = i + intervalZ)
//	{
//		gridLineVBuf.push_back(min_CoordX);
//		gridLineVBuf.push_back(0.0f);
//		gridLineVBuf.push_back(i);
//
//		gridLineVBuf.push_back(max_CoordX);
//		gridLineVBuf.push_back(0.0f);
//		gridLineVBuf.push_back(i);
//
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//		gridLineCBuf.push_back(colorX);
//	}
//
//	glGenBuffers(1, &gridLineVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, gridLineVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gridLineVBuf.size(), gridLineVBuf.data(), GL_STATIC_DRAW);
//
//	//glVertexPointer(2, GL_FLOAT, sizeof(vertexStatic), (void*)offsetof(vertexStatic, position));
//
//	glGenBuffers(1, &gridLineColorVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, gridLineColorVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gridLineCBuf.size(), gridLineCBuf.data(), GL_DYNAMIC_DRAW);
//
//	if (!CreateVAO_vc(gridLineVAO, gridLineVBO, gridLineColorVBO, shaderProgramID))
//	{
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	gridLineCount = (GLuint)gridLineVBuf.size();
//}
//bool UpdatePointBuffer() //크기
//{
//	//buffer_x, buffer_y, buffer_z
//
//
//	//pointVBuf.clear();
//	//pointCBuf.clear();
//	//cout <<"사이즈 : " << vBuffer.size() << "," << buffer_x.size() << endl;
//
//	for (size_t i = 0; i < buffer_x.size(); i++)
//	{
//		if (((pointOffset + i) * 3) < pointVBuf.size())
//		{
//
//			pointVBuf[3 * (pointOffset + i)] = buffer_y[i];
//			pointVBuf[3 * (pointOffset + i) + 1] = buffer_z[i];
//			pointVBuf[3 * (pointOffset + i) + 2] = buffer_x[i];
//
//		}
//		else
//		{
//			pointOffset = 0;
//		}
//	}
//
//	return true;
//}
//
//extern "C" __declspec(dllexport) int getDetectionSize() {
//	return (int)detectQueue.size();
//}
//extern "C" __declspec(dllexport) float getDetectionX() {
//	return (float)detectQueue.front().x;
//}
//extern "C" __declspec(dllexport)  float getDetectionY() {
//	return detectQueue.front().y;
//}
//extern "C" __declspec(dllexport)  float getDetectionZ() {
//	return detectQueue.front().z;
//}
//
//extern "C" __declspec(dllexport)  void getDetectionPop() {
//	mut.lock();
//	detectQueue.pop();
//	mut.unlock();
//}
//extern "C" __declspec(dllexport) int getDetection(float* input)
//{
//	cout << "detected" << endl;
//
//	if (!detectQueue.empty())
//	{
//		cout << "[Device] Copying Zone Coord :";
//
//		mut.lock();
//
//		glm::vec3 result = detectQueue.front();
//		detectQueue.pop();
//
//		mut.unlock();
//		if (input == nullptr)
//			input = new float[3];
//
//		input[0] = (float)result.x;
//		input[1] = (float)result.y;
//		input[2] = (float)result.z;
//
//		cout << result.x << " " << result.y << " " << result.z << endl;
//
//		return 0;
//	}
//	else
//		return 1;
//
//}
//
////Preprocessing 된 
//glm::mat4 lidar_transform = glm::mat4(1.);
//int zone_xnum, zone_ynum, zone_znum;
//int zoneSize;
//int* filtered_zone;
//int* zone;
//
////라이다 전용 Transform 함수
//extern "C" __declspec(dllexport) void SetLiDARInitialTransform(float x, float y, float z, float height)
//{
//	lidar_transform = glm::rotate(x, glm::vec3(1.0f, 0.0f, 0.0f)) *	//x축 회전
//		glm::rotate(x, glm::vec3(0.0f, 1.0f, 0.0f)) *	//y축 회전
//		glm::rotate(x, glm::vec3(0.0f, 0.0f, 1.0f)) *	//z축 회전
//		glm::translate(glm::vec3(0.0f, height, 0.0f));
//}
//
//extern "C" __declspec(dllexport) void SetLiDARInitialZone(int xcount, int ycount, int zcount)
//{
//	zone_xnum = xcount;
//	zone_ynum = ycount;
//	zone_znum = zcount;
//	zoneSize = xcount * ycount * zcount;
//
//	if (zone == nullptr)
//		zone = new int[zoneSize];
//	else
//	{
//		delete[] zone;
//		zone = new int[zoneSize];
//	}
//	for (int i = 0; i < zoneSize; i++)
//	{
//		zone[i] = 0;
//	}
//
//	if (filtered_zone == nullptr)
//		filtered_zone = new int[zoneSize];
//	else
//	{
//		delete[] filtered_zone;
//		filtered_zone = new int[zoneSize];
//	}
//	for (int i = 0; i < zoneSize; i++)
//	{
//		filtered_zone[i] = 0;
//	}
//}
//
//extern "C" __declspec(dllexport) void ReleaseLiDARZone()
//{
//	delete[] filtered_zone;
//	delete[] zone;
//}
//
//
//
////라이다 계산 함수
//extern "C" __declspec(dllexport) void LiDARPreScan(float sec)
//{
//	//라이다 Transform 정하기
//	//Zone 설정
//	//라이다 포인트 데이터 받기
//	//알고리즘 Run (포인트에 Transform 곱하기)
//	//1. 필터링
//	//2. 데이터 받기
//	//3. 감지 영역 
//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
//	double rotation_per_sec = 23.;
//
//	//DEBUG_getError();
//
//	//std::cout << "rotation_per_sec : " << rotation_per_sec << std::endl;
//
//
//	//sample = 1초동안 스캔할 데이터 량
//	for (int sample = 0; sample < (int)rotation_per_sec * sec; sample++)
//	{
//		clock_t start_time = clock();
//		instance->getRPS(rotation_per_sec);
//		instance->getCartesianOutputs(buffer_x, buffer_y, buffer_z);
//
//		int size_buffer(static_cast<int>(buffer_x.size()));
//		/*std::cout << size_buffer << std::endl;
//		for (int i(0); i < size_buffer; i++)
//		{
//			std::cout << "Coordinate(" << i << ") : (" << buffer_x.at(i) << "," << buffer_y.at(i) << "," << buffer_z.at(i) << ")" << std::endl;
//		}*/
//
//		for (int i = 0; i < buffer_x.size(); i++)
//		{
//			glm::vec4 detect_vertex = lidar_transform * glm::vec4(buffer_y[i], buffer_z[i], buffer_x[i], 1.0);
//
//			/*	int size_buffer(static_cast<int>(buffer_x.size()));
//				std::cout << size_buffer << std::endl;
//
//				std::cout << "Rotated Coordinate(" << i << ") : (" << detect_vertex.x << "," << detect_vertex.y << "," << detect_vertex.z << ")" << std::endl;
//			*/
//			int indexX = (int)lround((detect_vertex.x + 30.0) * ((float)zone_xnum / 60.0));
//			int indexY = (int)lround((detect_vertex.y + 30.0) * ((float)zone_ynum / 60.0));
//			int indexZ = (int)lround((detect_vertex.z + 30.0) * ((float)zone_znum / 60.0));
//
//			filtered_zone[indexX + (zone_xnum * indexY) + (zone_xnum * zone_ynum * indexZ)] += 1;
//		}
//		clock_t end_time = clock();
//		// 측정 시간 계산 (ms단위)
//		clock_t elapsed = end_time - start_time;
//
//		// Second로 변환
//		//double timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);
//
//		if (elapsed < 40)
//		{
//			std::this_thread::sleep_for(std::chrono::milliseconds(40 - elapsed));
//		}
//	}
//}
//
////filter level 최소 0
////detection level 최소 1
//extern "C" __declspec(dllexport) void LiDARScan(float sec, int filterLevel, int detectionLevel)
//{
//
//	double rotation_per_sec = 23.;
//
//	//sample = 1초동안 스캔할 데이터 량
//	while (true)
//	{
//		for (int sample = 0; sample < (int)rotation_per_sec * sec; sample++)
//		{
//			clock_t start_time = clock();
//
//			//DEBUG_getError();
//			instance->getRPS(rotation_per_sec);
//			instance->getCartesianOutputs(buffer_x, buffer_y, buffer_z);
//
//			for (int i = 0; i < buffer_x.size(); i++)
//			{
//				glm::vec4 detect_vertex = lidar_transform * glm::vec4(buffer_y[i], buffer_z[i], buffer_x[i], 1.0);
//
//				int indexX = (int)lround((detect_vertex.x + 30.0) * ((float)zone_xnum / 60.0));
//				int indexY = (int)lround((detect_vertex.y + 30.0) * ((float)zone_ynum / 60.0));
//				int indexZ = (int)lround((detect_vertex.z + 30.0) * ((float)zone_znum / 60.0));
//
//				if (filtered_zone[indexX + (zone_xnum * indexY) + (zone_xnum * zone_ynum * indexZ)] <= filterLevel)
//				{
//					if (zone[indexX + (zone_xnum * indexY) + (zone_xnum * zone_ynum * indexZ)] == 0)
//					{
//						zone[indexX + (zone_xnum * indexY) + (zone_xnum * zone_ynum * indexZ)] += 1;
//						mut.lock();
//						detectQueue.push(glm::vec3((float)indexX * (60.0f / (float)zone_xnum), (float)indexY * (60.0f / (float)zone_ynum), (float)indexZ * (60.0f / (float)zone_znum)));
//						mut.unlock();
//					}
//				}
//			}
//			clock_t end_time = clock();
//			// 측정 시간 계산 (ms단위)
//			clock_t elapsed = end_time - start_time;
//
//			// Second로 변환
//			//double timeInSecond = (double)(elapsed / CLOCKS_PER_SEC);
//
//			if (elapsed < 40)
//			{
//				std::this_thread::sleep_for(std::chrono::milliseconds(40 - elapsed));
//			}
//		}
//		for (int i = 0; i < zoneSize; i++)
//		{
//			zone[i] = 0;
//		}
//
//	}
//	ReleaseLiDARZone();
//	ReleaseLiDAR();
//}
//
//
//
//extern "C" __declspec(dllexport) void OpenGLWindow()
////void main()
//{
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	//_CrtSetBreakAlloc(155);
//
//	isEndLiDAREventRecieved = true;
//	isEndLiDAREventRecieved = false;
//
//
//	//	SetLiDAR((char*)"211.9.4.115", (char*)"lk.bin");
//
//	//	DEBUG_getStatus();
//
//
//	GLInitialize();
//
//
//
//	while (!glfwWindowShouldClose(win)) {
//
//
//		if (!isEndLiDAREventRecieved)
//		{
//			double rotation_per_sec;
//
//			//DEBUG_getError();
//			instance->getRPS(rotation_per_sec);
//			//std::cout << "rotation_per_sec : " << rotation_per_sec << std::endl;
//
//			//data
//			instance->getCartesianOutputs(buffer_x, buffer_y, buffer_z);
//			//getCartesianCoord();
//			//getIntensity();
//
//			//scan(3.0);
//			//scan2(3.0);
//
//		}
//
//		GLUpdate();
//
//	}
//
//	if (!isEndLiDAREventRecieved)
//	{
//		ReleaseLiDAR();
//	}
//	GLRelease();
//
//	_CrtDumpMemoryLeaks();
//	std::exit(EXIT_SUCCESS);
//	//return 0;
//}
//
//
//////////////////////////
//
//
//#pragma once
//
////Viewer
//int framebufferWidth, framebufferHeight;
////GLuint triangleVertexArrayObject;
////GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
////
////GLuint lineVertexArrayObject;
////GLuint linePositionVertexBufferObjectID, lineColorVertexBufferObjectID;
////
////GLuint pointVertexArrayObject;
////GLuint pointPositionVertexBufferObjectID, pointColorVertexBufferObjectID;
////GLuint pointPositionVertexBufferObjectIDY;
////GLuint pointPositionVertexBufferObjectIDZ;
//
//
//float RotX = 0.0f;
//float RotY = 10.0f;
//float RotZ = -50.0f;
//
//
////bool initShaderProgram();
////bool initZoneBoxShaderProgram();
////bool initPointShaderProgram();
////
////bool defineZoneBoxVertexArrayObject(
////	int x, int y, int z, //간격
////	float sizef_x, float sizef_y, float sizef_z); //크기
////
////bool definePointVertexArrayObject();
////
////bool defineVertexArrayObject();
//
//
//////안정화부분 /////////
//
//GLFWwindow* InitGLWindow(int width, int height, const char* title,
//	GLFWkeyfun keyCallback, GLFWframebuffersizefun framebufferSizeCallback, GLFWerrorfun errorCallback, int swapInterval);
//void framebufferSizeCallback(GLFWwindow* window, int width, int height);
//
//void framebufferSizeCallback(GLFWwindow* window, int width, int height);
//void errorCallback(int errorCode, const char* errorDescription);
//
//bool initShader(GLuint& shader, const GLchar* shaderSource, GLenum type);
//bool initVFShaderProgram(GLuint& VFShaderProgramID, GLuint& vertexShader, GLuint& fragmentShader);
//string readShaderSource(const char* filePath);
//bool CreateVAO_vc(GLuint& VAO, GLuint& vVBO, GLuint& cVBO, GLuint shaderProgramID);
//
//GLFWwindow* InitGLWindow(int width, int height, const char* title,
//	GLFWkeyfun keyCallback, GLFWframebuffersizefun framebufferSizeCallback, GLFWerrorfun errorCallback, int swapInterval)
//{
//	GLFWwindow* window;
//
//	glfwSetErrorCallback(errorCallback);
//	if (!glfwInit())
//	{
//		cerr << "Error: GLFW 초기화 실패" << endl;
//		std::exit(EXIT_FAILURE);
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	glfwWindowHint(GLFW_SAMPLES, 4);
//
//	window = glfwCreateWindow(width, height, title, NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window, keyCallback);
//	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
//
//	glfwSwapInterval(1);
//
//	glewExperimental = GL_TRUE;
//	GLenum errorCode = glewInit();
//	if (GLEW_OK != errorCode) {
//
//		cerr << "Error: GLEW 초기화 실패 - " << glewGetErrorString(errorCode) << endl;
//
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//
//	if (!GLEW_VERSION_3_3) {
//
//		cerr << "Error: OpenGL 3.3 API is not available." << endl;
//
//		glfwTerminate();
//		std::exit(EXIT_FAILURE);
//	}
//	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
//	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
//	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
//	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
//
//	return window;
//}
//
//void framebufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//	//처음 2개의 파라미터는 viewport rectangle의 왼쪽 아래 좌표
//	//다음 2개의 파라미터는 viewport의 너비와 높이이다.
//	//framebuffer의 width와 height를 가져와 glViewport에서 사용한다.
//	glViewport(0, 0, width, height);
//
//	framebufferWidth = width;
//	framebufferHeight = height;
//}
//
//void errorCallback(int errorCode, const char* errorDescription)
//{
//	cerr << "Error: " << errorDescription << endl;
//}
//
//
//
//bool initShader(GLuint& shader, const GLchar* shaderSource, GLenum type) {
//
//	shader = glCreateShader(type);
//	glShaderSource(shader, 1, &shaderSource, NULL);
//	glCompileShader(shader);
//
//	GLint result;
//	GLchar errorLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
//	if (!result)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, errorLog);
//		cerr << "ERROR: shader 컴파일 실패\n" << errorLog << endl;
//		glDeleteShader(shader);
//		return false;
//	}
//	return true;
//}
//
//bool initVFShaderProgram(GLuint& VFShaderProgramID, GLuint& vertexShader, GLuint& fragmentShader)
//{
//	//#5
//	VFShaderProgramID = glCreateProgram();
//
//	glAttachShader(VFShaderProgramID, vertexShader);
//	glAttachShader(VFShaderProgramID, fragmentShader);
//
//	glLinkProgram(VFShaderProgramID);
//
//	GLint result;
//	GLchar errorLog[512];
//	glGetProgramiv(VFShaderProgramID, GL_LINK_STATUS, &result);
//	if (!result) {
//		glGetProgramInfoLog(VFShaderProgramID, 512, NULL, errorLog);
//		cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
//		return false;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return true;
//}
//
//string readShaderSource(const char* filePath)
//{
//	string content = "";
//	ifstream fileStream(filePath, ios::in);
//	string line = "";
//	while (!fileStream.eof())
//	{
//		getline(fileStream, line);
//		content.append(line + "\n");
//	}
//	fileStream.close();
//	return content;
//}
//
//bool CreateVAO_vc(GLuint& VAO, GLuint& vVBO, GLuint& cVBO, GLuint shaderProgramID)
//{
//	//#6
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	GLint positionAttribute = glGetAttribLocation(shaderProgramID, "positionAttribute");
//	if (positionAttribute == -1) {
//		cerr << "position 속성 설정 실패triangle" << endl;
//		return false;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, vVBO);
//	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glEnableVertexAttribArray(positionAttribute);
//
//	GLint colorAttribute = glGetAttribLocation(shaderProgramID, "colorAttribute");
//	if (colorAttribute == -1) {
//		cerr << "color 속성 설정 실패" << endl;
//		return false;
//	}
//	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
//	glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(colorAttribute);
//
//	glBindVertexArray(0);
//
//	return true;
//}
//
//////////////
//
//
//
//
////class OpenGLCamera
////{
////public :
////	OpenGLCamera(){
////	
////		// 카메라 매트릭스
////		glm::mat4 View = glm::lookAt(vPos, vDir, vUp);
////
////		
////	}
////	
////	
////	~OpenGLCamera(){
////		
////	}
////
////	glm::mat4 Model;
////	glm::mat4 View;
////	glm::mat4 Proj;
////
////	
////	glm::vec3 vPos;
////	glm::vec3 vDir;
////	glm::vec3 vUp;
////	glm::vec3 vRight;
////
////	void Init()
////	{		
////		vPos = glm::vec3(0.0f, 0.0f, 0.0f);
////	}
////
////
////	void setPos(GLfloat, GLfloat, GLfloat){}
////
////	void setPerspectiveProjMatrix(GLfloat FoV, GLfloat near, GLfloat far)
////	{
////	glm::mat4 projectionMatrix = glm::perspective(
////			glm::radians(FoV),  // 수직방향 시야각입니다 : "줌"의 크기. "카메라 렌즈" 를 생각해보세요. 이들은 보통 90도 (엑스트라 와이드) 에서 30도 (크게 확대한 경우) 사이에 있습니다
////			4.0f / 3.0f, // 화면 비 입니다. 이것은 당신의 윈도우 크기에 의존합니다. 4/3 == 800/600 == 1280/960 인데, 어디서 본것 같죠 ?
////			near,        // Near clipping plane (근거리 잘라내기 평면). 최대한 크게 하세요. 아니면 정확도 문제가 생길 수 있습니다.
////			far       // Far clipping plane (원거리 잘라내기 평면). 최대한 작게 하세요.
////		);
////	}
////	void setViewMatrix()
////	{
////		// 카메라 매트릭스
////		glm::mat4 View = glm::lookAt(vPos, vDir, vUp);
////			
////	}
////
////	glm::mat4 getMVPMatrix(){
////		return View * Proj;
////	}
////
////};