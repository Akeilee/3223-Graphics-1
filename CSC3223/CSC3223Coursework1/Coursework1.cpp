//Name:Jane Lee 120236521
//Date:11/2019
//Purpose: CSC3223 Coursework 1
#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"
#include "../../Common/Camera.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"
#include "RasterisationMesh.h"
#include <algorithm>

using namespace NCL;
using namespace CSC3223;

void Background(Renderer& renderer) { //texture mapping of background and enabling of clamping
	OGLMesh* background = new OGLMesh();
	background->SetVertexPositions({ Vector3(0,0,-0.9), Vector3(800,0,-0.9), Vector3(0,600,-0.9),Vector3(800,600,-0.9) });

	background->SetVertexColours({ Vector4(0.1,0.1,0.1,1), Vector4(0.1,0.1,0.1,1), Vector4(0.1,0.1,0.1,1), Vector4(0.1,0.1,0.1,1), });
	background->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0),Vector2(0,1),Vector2(1,1) });
	background->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	background->UploadToGPU();

	Matrix4 translate = Matrix4::Translation(Vector3(0, 0, 0));
	RenderObject* render = new RenderObject(background, translate);
	TextureBase* bkgrndTex = OGLTexture::RGBATextureFromFilename("background.PNG");
	renderer.EnableTextureRepeating(*(OGLTexture*)bkgrndTex, true, true); //texture is able to be repeated 
	render->SetBaseTexture(bkgrndTex);
	renderer.AddRenderObject(render);
}

void Starfield(Renderer& renderer) { //making starfield
	OGLMesh* stars = new OGLMesh();

	stars->SetVertexPositions({ Vector3(50,50,0.8), Vector3(30,10,0.8), Vector3(75,75,0.8),Vector3(8,5,0.8),
								Vector3(15,70,0.8), Vector3(100,20,0.8), Vector3(55,30,0.8), Vector3(20,35,0.8) });
	stars->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),
								Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) });
	stars->SetPrimitiveType(GeometryPrimitive::Points);
	stars->UploadToGPU();

	for (int y = 0; y < 7; ++y) { //creating 7 along and 10 down 
		for (int x = 0; x < 10; ++x) {
			Matrix4 translate = Matrix4::Translation(Vector3(x * 90, y * 100, 0));
			renderer.AddRenderObject(new RenderObject(stars, translate));
		}
	}
}

void StarfieldPerspective(Renderer& renderer) { //making starfield to show using perspective matrix
	OGLMesh* stars = new OGLMesh();

	stars->SetVertexPositions({ Vector3(50,50,0.8), Vector3(30,10,0.8), Vector3(75,75,0.8),Vector3(8,5,0.8),
								Vector3(15,70,0.8), Vector3(100,20,0.8), Vector3(55,30,0.8), Vector3(20,35,0.8) });
	stars->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),
								Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) });
	stars->SetPrimitiveType(GeometryPrimitive::Points);
	stars->UploadToGPU();

	for (int y = 0; y < 7; ++y) { //creating 7 along and 10 down 
		for (int x = 0; x < 10; ++x) {
			for (int z = 0; z < 5; ++z) {
				Matrix4 translate = Matrix4::Translation(Vector3(x * 90, y * 100, z * 50)); //translating on z axis
				renderer.AddRenderObject(new RenderObject(stars, translate));
			}
		}
	}
}

void MoonFade(Renderer& renderer) { //for testing of alpha levels of the moon
	OGLMesh* moon = new OGLMesh();

	moon->SetVertexPositions(

		{ Vector3(400,300,0.7),
		Vector3(400,334,0.7),
		Vector3(405,334,0.7),
		Vector3(417,330,0.7),
		Vector3(427,320,0.7),
		Vector3(434,305,0.7),

		Vector3(434,300,0.7),
		Vector3(434,295,0.7),
		Vector3(427,280,0.7),
		Vector3(417,270,0.7),
		Vector3(405,264,0.7),

		Vector3(400,264,0.7),
		Vector3(395,264,0.7),
		Vector3(383,270,0.7),
		Vector3(373,280,0.7),
		Vector3(366,295,0.7),

		Vector3(366,300,0.7),
		Vector3(366,305,0.7),
		Vector3(373,320,0.7),
		Vector3(383,330,0.7),
		Vector3(395,334,0.7),
		Vector3(400,334,0.7)
		});

	moon->SetVertexColours({ Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), //alpha set to 0.9
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90), Vector4(1,0.7,0.05,0.90),
		Vector4(1,0.7,0.05,0.90), });

	moon->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	moon->UploadToGPU();

	Matrix4 translate = Matrix4::Translation(Vector3(200, -250, 10)); //translated on z axis
	renderer.AddRenderObject(new RenderObject(moon, translate));

	Matrix4 translate2 = Matrix4::Translation(Vector3(200, -250, 0));
	renderer.AddRenderObject(new RenderObject(moon, translate2));
}

void LargeStars(Renderer& renderer) { //adding random big stars
	OGLMesh* first = new OGLMesh();
	OGLMesh* second = new OGLMesh();
	OGLMesh* third = new OGLMesh();

	first->SetVertexPositions({ Vector3(20,20,0.75),Vector3(20,17,0.75), Vector3(23,20,0.75), Vector3(20,23,0.75), Vector3(17,20,0.75), Vector3(20,17,0.75) });
	first->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) ,Vector4(1,1,1,1) });
	first->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	first->UploadToGPU();

	second->SetVertexPositions({ Vector3(20,20,0.75),Vector3(20,17,0.75), Vector3(23,20,0.75), Vector3(20,23,0.75), Vector3(17,20,0.75), Vector3(20,17,0.75) });
	second->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) ,Vector4(1,1,1,1) });
	second->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	second->UploadToGPU();

	third->SetVertexPositions({ Vector3(20,20,0.75),Vector3(20,17,0.75), Vector3(23,20,0.75), Vector3(20,23,0.75), Vector3(17,20,0.75), Vector3(20,17,0.75) });
	third->SetVertexColours({ Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1),Vector4(1,1,1,1) ,Vector4(1,1,1,1) });
	third->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	third->UploadToGPU();

	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 1; ++x) {
			Matrix4 translate = Matrix4::Translation(Vector3(x * 100, y * 100, 0));
			renderer.AddRenderObject(new RenderObject(first, translate));

		}
	}

	Matrix4 translate = Matrix4::Translation(Vector3(100, 125, 0));
	renderer.AddRenderObject(new RenderObject(second, translate));

	Matrix4 translate2 = Matrix4::Translation(Vector3(70, 150, 0));
	renderer.AddRenderObject(new RenderObject(third, translate2));

}

void Asteroid(Renderer& renderer) { //making asteroid using triangle strip and texturing. also has perspective asteroids made
	OGLMesh* asteroid = new OGLMesh();
	asteroid->SetVertexPositions({ Vector3(30,45,0), Vector3(40,55,0), Vector3(35,32,0), Vector3(45,58,0) ,
		Vector3(55,15,0), Vector3(60,40,0), Vector3(65,20,0) });
	asteroid->SetVertexColours({ Vector4(0.1,0.11,0.16,1),Vector4(0.1,0.11,0.16,1),Vector4(0.36,0.41,0.43,1),Vector4(0.13,0.12,0.21,1),
		Vector4(0.65,0.61,0.69,1), Vector4(0.59,0.62,0.64,1), Vector4(0.70,0.74,0.73,1) });
	asteroid->SetVertexTextureCoords({ Vector2(0.9,0.6),Vector2(0.8,0.5),Vector2(1,0),Vector2(0.3,0.2),Vector2(0.6,0.5),Vector2(0.5,0.9),Vector2(0.4,0.8) });

	asteroid->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	asteroid->UploadToGPU();

	Matrix4 scale = Matrix4::Scale(Vector3(5, 5, 5));
	Matrix4 scale2 = Matrix4::Scale(Vector3(3, 3, 3));

	Matrix4 translate = Matrix4::Translation(Vector3(-80, 220, 0.4)); //big asteroid
	Matrix4 translateP = Matrix4::Translation(Vector3(-80, 220, 60)); //big asteroid for perspective

	Matrix4 translate2 = Matrix4::Translation(Vector3(250, 200, 0.45)); //small asteroid
	Matrix4 translate2P = Matrix4::Translation(Vector3(250, 200, 40)); //small asteroid for perspective

	Matrix4 rotate = Matrix4::Rotation(-180, Vector3(0, 1, 0)); //rotation on y axis

	RenderObject* render = new RenderObject(asteroid, translate * scale);
	RenderObject* renderP = new RenderObject(asteroid, translateP * scale);

	RenderObject* render2 = new RenderObject(asteroid, translate2 * rotate * scale2);
	RenderObject* render2P = new RenderObject(asteroid, translate2P * rotate * scale2);

	TextureBase* asteroidTex = OGLTexture::RGBATextureFromFilename("asteroid.PNG");
	render->SetBaseTexture(asteroidTex);
	renderP->SetBaseTexture(asteroidTex);

	render2->SetBaseTexture(asteroidTex);
	render2P->SetBaseTexture(asteroidTex);
	renderer.EnableBilinearFiltering(*(OGLTexture*)asteroidTex); //creates a smoother looking image using bilinear
	renderer.AddRenderObject(render2);
	renderer.AddRenderObject(render);

	renderer.AddRenderObject(render2P);
	renderer.AddRenderObject(renderP);

}

void BackgroundAsteroid(Renderer& renderer) { //rotation, translation and scaling of asteroid objects
	OGLMesh* asteroid = new OGLMesh();
	asteroid->SetVertexPositions({ Vector3(30,45,0), Vector3(40,55,0), Vector3(35,32,0), Vector3(45,58,0) ,
		Vector3(55,15,0), Vector3(60,40,0), Vector3(65,20,0) });
	asteroid->SetVertexColours({ Vector4(0,0,0,1),Vector4(0,0,0,1),Vector4(0.13,0.12,0.21,1),Vector4(0.13,0.12,0.21,1),
		Vector4(0.13,0.12,0.21,1), Vector4(0.59,0.62,0.64,1), Vector4(0.70,0.74,0.73,1) });

	asteroid->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	asteroid->UploadToGPU();

	Matrix4 scale = Matrix4::Scale(Vector3(0.5, 0.5, 0.5));
	Matrix4 scale2 = Matrix4::Scale(Vector3(0.8, 0.8, 0.8));

	Matrix4 translate = Matrix4::Translation(Vector3(400, 170, 0.71));
	Matrix4 translate2 = Matrix4::Translation(Vector3(500, 150, 0.71));
	Matrix4 translate3 = Matrix4::Translation(Vector3(500, 150, 0.7));

	Matrix4 rotate = Matrix4::Rotation(-180, Vector3(0, 1, 0)); //rotation on y axis
	Matrix4 rotate2 = Matrix4::Rotation(80, Vector3(0, 0, 1)); //rotation on z axis

	RenderObject* render = new RenderObject(asteroid, translate * scale);
	RenderObject* render2 = new RenderObject(asteroid, translate2 * rotate * scale2);
	RenderObject* render3 = new RenderObject(asteroid, translate3 * rotate2);

	renderer.AddRenderObject(render2);
	renderer.AddRenderObject(render3);
	renderer.AddRenderObject(render);
}

void BackgroundAsteroidMipMap(Renderer& renderer) { //texuring of asteroids using mipmap enabled
	OGLMesh* asteroid = new OGLMesh();
	asteroid->SetVertexPositions({ Vector3(30,45,0), Vector3(40,55,0), Vector3(35,32,0), Vector3(45,58,0) ,
		Vector3(55,15,0), Vector3(60,40,0), Vector3(65,20,0) });
	asteroid->SetVertexColours({ Vector4(0.1,0.11,0.16,1),Vector4(0.1,0.11,0.16,1),Vector4(0.36,0.41,0.43,1),Vector4(0.13,0.12,0.21,1),
		Vector4(0.65,0.61,0.69,1), Vector4(0.59,0.62,0.64,1), Vector4(0.70,0.74,0.73,1) });
	asteroid->SetVertexTextureCoords({ Vector2(0.9,0.6),Vector2(0.8,0.5),Vector2(1,0),Vector2(0.3,0.2),Vector2(0.6,0.5),Vector2(0.5,0.9),Vector2(0.4,0.8) });

	asteroid->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	asteroid->UploadToGPU();

	Matrix4 scale = Matrix4::Scale(Vector3(1, 1, 1));
	Matrix4 scale2 = Matrix4::Scale(Vector3(0.5, 0.5, 0.5));
	Matrix4 scale3 = Matrix4::Scale(Vector3(0.7, 0.7, 0.7));
	Matrix4 scale4 = Matrix4::Scale(Vector3(0.5, 0.5, 0.5));

	Matrix4 translate = Matrix4::Translation(Vector3(250, 120, 0.6)); //big asteroid
	Matrix4 translate2 = Matrix4::Translation(Vector3(250, 70, 0.6)); //small asteroid
	Matrix4 translate3 = Matrix4::Translation(Vector3(680, 150, 0.6)); //rhs asteroid
	Matrix4 translate4 = Matrix4::Translation(Vector3(120, 10, 0.6)); //lhs asteroid

	Matrix4 rotate = Matrix4::Rotation(50, Vector3(0, 0, 1));
	Matrix4 rotate2 = Matrix4::Rotation(270, Vector3(0, 0, 1));
	Matrix4 rotate3 = Matrix4::Rotation(300, Vector3(0, 0, 1));
	Matrix4 rotate4 = Matrix4::Rotation(90, Vector3(0, 0, 1));

	RenderObject* render = new RenderObject(asteroid, translate * rotate2 * scale);
	RenderObject* render2 = new RenderObject(asteroid, translate2 * rotate * scale2);
	RenderObject* render3 = new RenderObject(asteroid, translate3 * rotate3 * scale3);
	RenderObject* render4 = new RenderObject(asteroid, translate4 * rotate4 * scale4);

	TextureBase* asteroidTex = OGLTexture::RGBATextureFromFilename("asteroid.PNG");
	render->SetBaseTexture(asteroidTex);
	render2->SetBaseTexture(asteroidTex);
	render3->SetBaseTexture(asteroidTex);
	render4->SetBaseTexture(asteroidTex);
	renderer.EnableMipMapFiltering(*(OGLTexture*)asteroidTex); //using mipmap to allow correct texture to show when made smaller
	renderer.AddRenderObject(render2);
	renderer.AddRenderObject(render3);
	renderer.AddRenderObject(render4);
	renderer.AddRenderObject(render);

}

RenderObject* Spaceship(Renderer& renderer) { //ship made out of triangles and lines (also made ship for perspective mode)
	OGLMesh* ship = new OGLMesh();
	OGLMesh* shipLines = new OGLMesh();

	ship->SetVertexPositions({
		Vector3(0,30,0),Vector3(0,26,0),Vector3(12,26,0), //1
		Vector3(0,30,0),Vector3(12,30,0),Vector3(12,26,0), //2
		Vector3(6,16,0),Vector3(12,16,0),Vector3(12,10,0), //3
		Vector3(12,32,0),Vector3(12,10,0),Vector3(22,10,0), //4
		Vector3(12,32,0),Vector3(22,32,0),Vector3(22,10,0), //5
		Vector3(22,22,0),Vector3(22,20,0),Vector3(30,20,0), //6
		Vector3(22,32,0),Vector3(22,22,0),Vector3(30,20,0), //7
		Vector3(22,32,0),Vector3(30,30,0),Vector3(30,20,0), //8
		Vector3(30,20,0),Vector3(40,20,0),Vector3(35,14,0), //9
		Vector3(30,30,0),Vector3(30,20,0),Vector3(35,25,0), //10.1
		Vector3(30,20,0),Vector3(40,20,0),Vector3(35,25,0), //10.2
		Vector3(30,30,0),Vector3(40,30,0),Vector3(35,25,0), //11.1
		Vector3(40,20,0),Vector3(40,30,0),Vector3(35,25,0), //11.2
		Vector3(40,30,0),Vector3(40,20,0),Vector3(48,32,0), //12
		Vector3(40,20,0),Vector3(48,22,0),Vector3(48,32,0), //13
		Vector3(40,20,0),Vector3(48,20,0),Vector3(48,22,0), //14
		Vector3(48,32,0),Vector3(48,10,0),Vector3(58,32,0), //15
		Vector3(58,32,0),Vector3(58,10,0),Vector3(48,10,0), //16
		Vector3(58,16,0),Vector3(64,16,0),Vector3(58,10,0), //17
		Vector3(58,30,0),Vector3(58,26,0),Vector3(70,30,0), //18
		Vector3(58,26,0),Vector3(70,26,0),Vector3(70,30,0), //19

		});

	ship->SetVertexColours({
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), //1
		Vector4(0.65,0.65,0.65,1), Vector4(0.65,0.65,0.65,1), Vector4(0.65,0.65,0.65,1), //2
		Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), //3
		Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), //4
		Vector4(0.93,0.34,0.06,1), Vector4(1,0.5,0.5,1), Vector4(0.93,0.34,0.06,1), //5
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), //6
		Vector4(0.82,0.25,0.09,1), Vector4(0.82,0.25,0.09,1), Vector4(0.47,0.23,0.17,1), //7
		Vector4(0.82,0.25,0.09,1), Vector4(0.47,0.23,0.17,1), Vector4(0.47,0.23,0.17,1), //8
		Vector4(0.65,0.65,0.65,1), Vector4(0.65,0.65,0.65,1), Vector4(0.95,0.95,0.95,1), //9
		Vector4(0,0,0,1), Vector4(0,0,0,1), Vector4(1,0.86,0.08,1), //10.1
		Vector4(0,0,0,1), Vector4(0,0,0,1), Vector4(1,0.86,0.08,1), //10.2
		Vector4(0,0,0,1), Vector4(0,0,0,1), Vector4(1,0.86,0.08,1), //11.1
		Vector4(0,0,0,1), Vector4(0,0,0,1), Vector4(1,0.86,0.08,1), //11.2
		Vector4(0.47,0.23,0.17,1), Vector4(0.47,0.23,0.17,1), Vector4(0.82,0.25,0.09,1), //12
		Vector4(0.47,0.23,0.17,1), Vector4(0.82,0.25,0.09,1), Vector4(0.82,0.25,0.09,1), //13
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), //14
		Vector4(1,0.5,0.5,1), Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), //15
		Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), //16
		Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), Vector4(0.93,0.34,0.06,1), //17
		Vector4(0.65,0.65,0.65,1), Vector4(0.65,0.65,0.65,1), Vector4(0.65,0.65,0.65,1), //18
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1), //19
		});

	shipLines->SetVertexPositions({
		Vector3(16,38,0), Vector3(16,32,0),
		Vector3(26,38,0), Vector3(26,31,0),
		Vector3(44,38,0), Vector3(44,31,0),
		Vector3(54,38,0), Vector3(54,32,0),
		});

	shipLines->SetVertexColours({
		Vector4(0.95,0.95,0.95,1),Vector4(0.95,0.95,0.95,1),
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1),
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1),
		Vector4(0.95,0.95,0.95,1), Vector4(0.95,0.95,0.95,1),
		});

	ship->SetPrimitiveType(GeometryPrimitive::Triangles);
	ship->UploadToGPU();

	shipLines->SetPrimitiveType(GeometryPrimitive::Lines);
	shipLines->UploadToGPU();

	Matrix4 translate = Matrix4::Translation(Vector3(320, 200, 0.1));
	Matrix4 rotate = Matrix4::Rotation(30, Vector3(0, 0, 1));
	Matrix4 scale = Matrix4::Scale(Vector3(3, 3, 3));

	for (int z = 1; z < 50; ++z) { //creating multiple ships that translate across the z axis (used for perspective testing)
		Matrix4 translate2 = Matrix4::Translation(Vector3(320, 200, 10 * z));
		RenderObject* render = new RenderObject(ship, translate2 * rotate * scale);
		RenderObject* renderLine = new RenderObject(shipLines, translate2 * rotate * scale);

		renderer.AddRenderObject(render);
		renderer.AddRenderObject(renderLine);
	}

	RenderObject* render = new RenderObject(ship);
	renderer.AddRenderObject(render);
	return render;

}

void Planet(Renderer& renderer) { //large planet using triangle fans and colour interpolated across it
	OGLMesh* planet = new OGLMesh();

	planet->SetVertexPositions(
		{ Vector3(800,800,0),
		Vector3(800,300,0),
		Vector3(860,310,0),
		Vector3(920,330,0),
		Vector3(960,350,0),
		Vector3(1020,390,0),
		Vector3(1050,430,0),
		Vector3(1080,490,0),
		Vector3(1090,540,0),

		Vector3(1100,600,0),
		Vector3(1090,660,0),
		Vector3(1080,710,0),
		Vector3(1050,770,0),
		Vector3(1020,810,0),
		Vector3(960,850,0),
		Vector3(920,870,0),
		Vector3(860,890,0),

		Vector3(800,900,0),
		Vector3(740,890,0),
		Vector3(680,870,0),
		Vector3(640,850,0),
		Vector3(580,810,0),
		Vector3(550,770,0),
		Vector3(520,710,0),
		Vector3(510,660,0),

		Vector3(500,600,0),
		Vector3(510,540,0),
		Vector3(520,490,0),
		Vector3(550,430,0),
		Vector3(580,390,0),
		Vector3(640,350,0),
		Vector3(680,330,0),
		Vector3(740,310,0),

		Vector3(800,300,0),
		});

	planet->SetVertexColours({
		/*Vector4(0.36,0.31,0.13,0.75),

		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),

		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),

		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),

		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),*/

		Vector4(1,1,0.61,0.75),

		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),

		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),

		Vector4(1,1,0.61,0.75),
		Vector4(1,1,0.61,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),
		Vector4(0.64,0.54,0.13,0.75),

		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.36,0.31,0.13,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),
		Vector4(0.2,0.18,0.08,0.75),

		});

	planet->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	planet->UploadToGPU();
	Matrix4 translate = Matrix4::Translation(Vector3(1500, 1100, 0.3));
	Matrix4 scale = Matrix4::Scale(Vector3(1, 1, 1));
	Matrix4 rotate = Matrix4::Rotation(180, Vector3(0, 0, 1));
	Matrix4 finalMat = translate * rotate * scale;
	renderer.AddRenderObject(new RenderObject(planet, finalMat));

}

RenderObject* SmallMoon(Renderer& renderer) { //making a small moon using triange fan and also made into 3D shape
	OGLMesh* moon2 = new OGLMesh();

	moon2->SetVertexPositions(
		{ Vector3(400, 300, 0),
				Vector3(400, 347, 0.65),
				Vector3(415, 345, 0.65),
				Vector3(427, 340, 0.65),
				Vector3(437, 330, 0.65),
				Vector3(445, 315, 0.65),

				Vector3(447, 300, 0.65),
				Vector3(445, 285, 0.65),
				Vector3(437, 270, 0.65),
				Vector3(427, 260, 0.65),
				Vector3(415, 255, 0.65),

				Vector3(400, 253, 0.65),
				Vector3(385, 255, 0.65),
				Vector3(373, 260, 0.65),
				Vector3(363, 270, 0.65),
				Vector3(355, 285, 0.65),

				Vector3(353, 300, 0.65),
				Vector3(355, 315, 0.65),
				Vector3(363, 330, 0.65),
				Vector3(373, 340, 0.65),
				Vector3(385, 345, 0.65),
				Vector3(400, 347, 0.65) });

	moon2->SetVertexColours({ Vector4(1,1,1,0.5),Vector4(1,1,1,0.5),Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5), Vector4(1,1,1,0.5), Vector4(1,1,1,0.5),
		Vector4(1,1,1,0.5) });

	moon2->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	moon2->UploadToGPU();
	Matrix4 translate = Matrix4::Translation(Vector3(360, -130, 0));
	Matrix4 scale = Matrix4::Scale(Vector3(0.6, 0.6, 0.6));
	Matrix4 finalMat = translate * scale;
	RenderObject* drawnMoon = new RenderObject(moon2, finalMat);
	renderer.AddRenderObject(drawnMoon);

	return drawnMoon;
}

void HiddenAsteroid(Renderer& renderer) { //asteroid behind planet to use in alpha blending testing
	OGLMesh* asteroid = new OGLMesh();
	asteroid->SetVertexPositions({ Vector3(30,45,0), Vector3(40,55,0), Vector3(35,32,0), Vector3(45,58,0) ,
		Vector3(55,15,0), Vector3(60,40,0), Vector3(65,20,0) });
	asteroid->SetVertexColours({ Vector4(0.1,0.11,0.16,1),Vector4(0.1,0.11,0.16,1),Vector4(0.36,0.41,0.43,1),Vector4(0.13,0.12,0.21,1),
		Vector4(0.65,0.61,0.69,1), Vector4(0.59,0.62,0.64,1), Vector4(0.70,0.74,0.73,1) });
	asteroid->SetVertexTextureCoords({ Vector2(0.9,0.6),Vector2(0.8,0.5),Vector2(1,0),Vector2(0.3,0.2),Vector2(0.6,0.5),Vector2(0.5,0.9),Vector2(0.4,0.8) });

	asteroid->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	asteroid->UploadToGPU();

	Matrix4 scale = Matrix4::Scale(Vector3(6, 6, 6));
	Matrix4 translate = Matrix4::Translation(Vector3(600, 850, 0.4));
	Matrix4 rotate = Matrix4::Rotation(200, Vector3(0, 0, 1));
	RenderObject* render = new RenderObject(asteroid, translate * rotate * scale);

	TextureBase* asteroidTex = OGLTexture::RGBATextureFromFilename("asteroid.PNG");
	render->SetBaseTexture(asteroidTex);
	renderer.EnableTextureRepeating(*(OGLTexture*)asteroidTex, true, true); //enable texture repeating
	renderer.AddRenderObject(render);

}

void NameCreation(Renderer& renderer) { //making name appear on screen

	Matrix4 translate = Matrix4::Translation(Vector3(-70, 0, 0));
	Matrix4 translate2 = Matrix4::Translation(Vector3(-50, -70, 0));

	OGLMesh* firstName = //triangles using line equation
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({

		//J
		Vector3(110,50,0), Vector3(110,80,0), Vector3(260,80,0),
		Vector3(260,50,0), Vector3(110,50,0),Vector3(260,80,0),
		Vector3(170,200,0), Vector3(200,200,0),Vector3(170,80,0),
		Vector3(200,80,0), Vector3(170,80,0), Vector3(200,200,0),
		Vector3(200,210,0),Vector3(180,210,0),Vector3(180,230,0),
		Vector3(180,210,0),Vector3(130,210,0),Vector3(180,230,0),
		Vector3(130,210,0),Vector3(110,210,0),Vector3(130,230,0),
		Vector3(110,200,0),Vector3(110,210,0),Vector3(200,210,0),
		Vector3(110,200,0),Vector3(140,200,0),Vector3(110,180,0),
		Vector3(110,180,0),Vector3(140,200,0),Vector3(140,180,0),
		Vector3(110,200,0),Vector3(200,210,0),Vector3(200,200,0),
		Vector3(130,230,0),Vector3(180,230,0),Vector3(130,210,0),

		//N
		Vector3(470,230,0),Vector3(500,230,0),Vector3(470,80,0),
		Vector3(500,230,0),Vector3(500,80,0),Vector3(470,80,0),
		Vector3(470,50,0),Vector3(470,80,0),Vector3(520,80,0),
		Vector3(520,80,0),Vector3(520,50,0),Vector3(470,50,0),
		Vector3(520,50,0),Vector3(520,80,0),Vector3(530,80,0),
		Vector3(500,80,0),Vector3(550,200,0),Vector3(590,200,0),
		Vector3(500,80,0),Vector3(590,200,0),Vector3(530,80,0),
		Vector3(570,200,0),Vector3(550,200,0),Vector3(570,230,0),
		Vector3(570,200,0),Vector3(570,230,0),Vector3(620,230,0),
		Vector3(620,230,0),Vector3(620,200,0),Vector3(570,200,0),
		Vector3(590,200,0),Vector3(620,200,0),Vector3(590,50,0),
		Vector3(620,230,0),Vector3(620,50,0),Vector3(590,50,0),
			},

			{
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),

			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			Vector4(0.51,0,1,1), Vector4(0.51,0,1,1), Vector4(0.51,0,1,1),
			});

	OGLMesh* firstName2 = //triangles using triangle span
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints({
		//A
		Vector3(270,230,1),Vector3(300,230,1),Vector3(290,170,1),
		Vector3(290,170,1),Vector3(300,230,1),Vector3(320,170,1),
		Vector3(390,170,1),Vector3(410,230,1),Vector3(420,170,1),
		Vector3(410,230,1),Vector3(440,230,1),Vector3(420,170,1),
		Vector3(290,170,1),Vector3(420,170,1),Vector3(300,140,1),
		Vector3(300,140,1),Vector3(420,170,1),Vector3(410,140,1),
		Vector3(300,140,1),Vector3(330,140,1),Vector3(320,80,1),
		Vector3(330,140,1),Vector3(350,80,1),Vector3(320,80,1),
		Vector3(380,140,1),Vector3(410,140,1),Vector3(360,80,1),
		Vector3(360,80,1),Vector3(410,140,1),Vector3(390,80,1),
		Vector3(320,80,1),Vector3(390,80,1),Vector3(330,50,1),
		Vector3(330,50,1),Vector3(390,80,1),Vector3(380,50,1),

		//E
		Vector3(650,85,1),Vector3(800,50,1),Vector3(650,50,1),
		Vector3(650,85,1),Vector3(800,85,1),Vector3(800,50,1),
		Vector3(650,85,1),Vector3(650,125,1),Vector3(680,85,1),
		Vector3(650,125,1),Vector3(680,125,1),Vector3(680,85,1),
		Vector3(650,125,1),Vector3(650,155,1),Vector3(800,125,1),
		Vector3(650,155,1),Vector3(800,155,1),Vector3(800,125,1),
		Vector3(650,155,1),Vector3(650,195,1),Vector3(680,155,1),
		Vector3(650,195,1),Vector3(680,195,1),Vector3(680,155,1),
		Vector3(650,195,1),Vector3(650,230,1),Vector3(800,195,1),
		Vector3(650,230,1),Vector3(800,230,1),Vector3(800,195,1),

			},

			{
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),

			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),Vector4(0.51,0,0.51,1),
			});

	OGLMesh* surname = //line not using bresenham 
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints({
		//L
		Vector3(180,370,0),Vector3(180,550,0),
		Vector3(180,370,0), Vector3(215,370,0),
		Vector3(215,370,0), Vector3(215,515,0),
		Vector3(215,515,0), Vector3(330,515,0),
		Vector3(330,515,0), Vector3(330,550,0),
		Vector3(330,550,0), Vector3(180,550,0),

		//E2
		Vector3(540,550,0),Vector3(540,370,0),
		Vector3(540,370,0),Vector3(690,370,0),
		Vector3(690,370,0),Vector3(690,405,0),
		Vector3(570,405,0),Vector3(690,405,0),
		Vector3(570,405,0),Vector3(570,445,0),
		Vector3(570,445,0),Vector3(690,445,0),
		Vector3(690,445,0),Vector3(690,475,0),
		Vector3(570,475,0),Vector3(690,475,0),
		Vector3(570,475,0),Vector3(570,515,0),
		Vector3(570,515,0),Vector3(690,515,0),
		Vector3(690,515,0),Vector3(690,550,0),
		Vector3(540,550,0),Vector3(690,550,0),
			},

			{ Vector4(1,0,0.51,1),Vector4(1,0,0.51,1),Vector4(1,0,0.51,1),Vector4(1,0,0.51,1),Vector4(1,0,0.51,1),Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1),
			Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), Vector4(1,0,0.51,1), }, false);

	OGLMesh* surname2 = //line using bresenham's line algorithm
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints({

		//E1
		Vector3(360, 550, 0), Vector3(360, 370, 0),
		Vector3(360, 370, 0), Vector3(510, 370, 0),
		Vector3(510, 370, 0), Vector3(510, 405, 0),
		Vector3(390, 405, 0), Vector3(510, 405, 0),
		Vector3(390, 405, 0), Vector3(390, 445, 0),
		Vector3(390, 445, 0), Vector3(510, 445, 0),
		Vector3(510, 445, 0), Vector3(510, 475, 0),
		Vector3(390, 475, 0), Vector3(510, 475, 0),
		Vector3(390, 475, 0), Vector3(390, 515, 0),
		Vector3(390, 515, 0), Vector3(510, 515, 0),
		Vector3(510, 515, 0), Vector3(510, 550, 0),
		Vector3(360, 550, 0), Vector3(510, 550, 0) },

			{ Vector4(0,0.51,1,1),Vector4(0,0.51,1,1),Vector4(0,0.51,1,1),Vector4(0,0.51,1,1),Vector4(0,0.51,1,1),Vector4(0,0.51,1,1),
			Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1),
			Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1),
			Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), Vector4(0,0.51,1,1), }, true);


	RenderObject* renderFirst = new RenderObject(firstName, translate);
	RenderObject* renderFirst2 = new RenderObject(firstName2, translate);
	RenderObject* renderLast = new RenderObject(surname, translate2);
	RenderObject* renderLast2 = new RenderObject(surname2, translate2);

	renderer.AddRenderObject(renderFirst);
	renderer.AddRenderObject(renderFirst2);
	renderer.AddRenderObject(renderLast);
	renderer.AddRenderObject(renderLast2);

}



int main() {

	Window* w = Window::CreateGameWindow("CSC3223 Coursework 1!");
	if (!w->HasInitialised()) {
		return -1;
	}
	Renderer* renderer = new Renderer(*w);

	glClearColor(0, 0, 0, 1); //changes background to black
	Vector3 viewPosition(0, 0, 0); //camera view
	Vector3 moveShip(320, 200, 0.1); //setting position
	Vector3 moveMoon(360, -130, 0); //setting position
	Vector3 rotateAxis(0, 0, 0);
	float rotateAngle = 0.0f;
	float rotateAngleMoon = 0.0f;

	renderer->SetBlendToLinear(); //initialising blending
	//for othographic view
	float currentWidth = Window::GetWindow()->GetScreenSize().x;
	float currentHeight = Window::GetWindow()->GetScreenSize().y;
	Matrix4 ortho = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
	Matrix4 scale = Matrix4::Scale(Vector3(0.9, -0.9, 0.9));
	float degree = 0;

	//for toggling F1 and F5 and F10 keys
	static bool alphaIsOn = true;
	static bool depthIsOn = true;
	static bool polygonOn = true;

	//calling functions
	Background(*renderer);
	Starfield(*renderer);
	StarfieldPerspective(*renderer);
	LargeStars(*renderer);
	MoonFade(*renderer);
	RenderObject* finishedMoon = SmallMoon(*renderer);
	BackgroundAsteroid(*renderer);
	BackgroundAsteroidMipMap(*renderer);
	HiddenAsteroid(*renderer);
	Planet(*renderer);
	Asteroid(*renderer);
	RenderObject* finishedShip = Spaceship(*renderer);



	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();
		renderer->Update(time);
		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		//toggle alpha blending
		if (alphaIsOn == false && Window::GetKeyboard()->KeyPressed(KEYBOARD_F5))
		{
			renderer->EnableAlphaBlending(true);
		}
		else if (alphaIsOn == true && Window::GetKeyboard()->KeyPressed(KEYBOARD_F5))
		{
			renderer->EnableAlphaBlending(false);
		}
		alphaIsOn = !alphaIsOn;

		//toggle depth buffer
		if (depthIsOn == false && Window::GetKeyboard()->KeyPressed(KEYBOARD_F1))
		{
			renderer->EnableDepthBuffer(true);
		}
		else if (depthIsOn == true && Window::GetKeyboard()->KeyPressed(KEYBOARD_F1))
		{
			renderer->EnableDepthBuffer(false);
		}
		depthIsOn = !depthIsOn;

		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}


		if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) { //left
			viewPosition.x += 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) { //right
			viewPosition.x -= 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) { //up
			viewPosition.y += 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) { //down
			viewPosition.y -= 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Z)) { //near plane
			viewPosition.z += 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_X)) { //far plane
			viewPosition.z -= 2.0f;
		}

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition)); //allowing tranlation of the camera view

		//rotating camera by x, y and z axis
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_7)) {
			degree += 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(0, 0, 1));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_8)) {
			degree -= 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(0, 0, 1));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_9)) {
			degree += 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(1, 0, 0));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_0)) {
			degree -= 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(1, 0, 0));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_PLUS)) {
			degree += 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(0, 1, 0));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_MINUS)) {
			degree -= 1;
			Matrix4 rotate = Matrix4::Rotation(degree, Vector3(0, 1, 0));
			Matrix4 final = rotate * scale * ortho;
			renderer->SetProjectionMatrix(final);
		}

		// --- NOTE: DEPTH AND ALPHA BLENDING KEY PRESSES SOMETIMES NEED TO BE PRESSED A FEW TIMES BEFORE THEY WORK ---
		//depth buffer
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F2)) { //passes if fragment depth value is greater than stored depth value
			glDepthFunc(GL_GREATER);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F3)) { //depth test always passes
			glDepthFunc(GL_ALWAYS);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F4)) { //passes if fragment depth value is less than stored depth value
			glDepthFunc(GL_LESS);
		}

		//alpha blending
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) { //additive blending
			renderer->SetBlendToAdditive();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) { //linear blending
			renderer->SetBlendToLinear();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F8)) { //invert blending
			renderer->SetBlendToInvert();
		}

		//orthographic view
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NUMPAD1)) {
			viewPosition.x = -400; //reset camera
			viewPosition.y = -275;
			viewPosition.z = 0;
			Matrix4 ortho = Matrix4::Orthographic(1, 10.0f, currentWidth * 0.5f, -currentWidth * 0.5f, -currentHeight * 0.5f, currentHeight * 0.5f); //set near plane to 1 and far to 10
			renderer->SetProjectionMatrix(ortho);
		}
		//perspective view
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NUMPAD2)) {
			viewPosition.x = -400; //reset camera
			viewPosition.y = -275;
			viewPosition.z = 0;
			float aspect = w->GetScreenAspect();
			Matrix4 persp = Matrix4::Perspective(1.0f, 100.0f, aspect, 45.0f); //near plane =1, far plane = 100, FOV = 45
			Matrix4 scale = (Matrix4::Scale(Vector3(0.9, -0.9, 0.9))); //scaling image down and flipping it right way up
			Matrix4 fin = scale * persp;
			renderer->SetProjectionMatrix(fin);
		}
		//reset view
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_N)) {
			Matrix4 ortho = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
			viewPosition.x = 0;
			viewPosition.y = 0;
			viewPosition.z = 0;
			renderer->SetProjectionMatrix(ortho);
		}

		//showing polygon lines or showing filled shape
		if (polygonOn == false && Window::GetKeyboard()->KeyPressed(KEYBOARD_F10))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //show lines
		}
		else if (polygonOn == true && Window::GetKeyboard()->KeyPressed(KEYBOARD_F10))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //fill shape
		}
		polygonOn = !polygonOn;

		//moving spaceship
		Matrix4 shipTranslate = Matrix4::Translation(moveShip);
		Matrix4 shipRotate = Matrix4::Rotation(30 + rotateAngle, Vector3(0, 0, 1));
		Matrix4 shipScale = Matrix4::Scale(Vector3(3, 3, 3));
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) { //move right
			moveShip.x += 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) { //move left
			moveShip.x -= 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) { //move up
			moveShip.y += 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) { //move down
			moveShip.y -= 2.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) { //rotate
			rotateAngle += 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) { //rotate
			rotateAngle -= 1.0f;
		}

		//rotating moon (works better in perspective mode)
		Matrix4 moonTranslate = Matrix4::Translation(moveMoon);
		Matrix4 moonRotate = Matrix4::Rotation(rotateAngleMoon, rotateAxis);
		Matrix4 moonScale = Matrix4::Scale(Vector3(0.6, 0.6, 0.6));
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J)) { //move x axis
			rotateAngleMoon += 1.0f;
			rotateAxis.x = 1;
			rotateAxis.y = 0;
			rotateAxis.z = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_L)) { //move x axis
			rotateAngleMoon -= 0.5f;
			rotateAxis.x = 1;
			rotateAxis.y = 0;
			rotateAxis.z = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_I)) { //move y axis
			rotateAngleMoon += 0.5f;
			rotateAxis.y = 1;
			rotateAxis.x = 0;
			rotateAxis.z = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_K)) { //move y axis
			rotateAngleMoon -= 0.5f;
			rotateAxis.y = 1;
			rotateAxis.x = 0;
			rotateAxis.z = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_U)) { //move z axis
			rotateAngleMoon += 0.5f;
			rotateAxis.z = 1;
			rotateAxis.y = 0;
			rotateAxis.x = 0;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_O)) { //move z axis
			rotateAngleMoon -= 0.5f;
			rotateAxis.z = 1;
			rotateAxis.y = 0;
			rotateAxis.x = 0;
		}

		finishedShip->SetTransform(shipTranslate * shipRotate * shipScale);
		finishedMoon->SetTransform(moonTranslate * moonRotate * moonScale);

		//clear screen and show name
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
			renderer->DeleteAllRenderObjects(); //delete old renders
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //setting canvas to black
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //making sure everything is deleted
			NameCreation(*renderer);
		}

		w->SetTitle(std::to_string(time) + std::string(" Jane Lee CW1 CSC3223"));
	}

	delete renderer;

	Window::DestroyGameWindow();
}