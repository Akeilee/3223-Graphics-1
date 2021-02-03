//Name:Jane Lee 120236521
//Date:11/2019
//Purpose: CSC3223 Coursework 1
#pragma once
#include "../../Plugins/OpenGLRendering//OGLMesh.h"


namespace NCL {
	namespace CSC3223 {

		class RasterisationMesh : public Rendering::OGLMesh
		{
		public:

			//tut 3
			static RasterisationMesh* CreateTriangleFromPoints(const std::vector <Vector3>& vertices, const std::vector<Vector4>& colours, int type = 0);
			static RasterisationMesh* CreateLineFromPoints(const std::vector <Vector3>& vertices, const std::vector<Vector4>& colours, bool bresenham = false);

		protected:

			//tut 3
			void RasterBasicLine(const Vector3& p0, const Vector3& p1, const Vector4& c0, const Vector4& c1);
			void RasterBresenhamLine(const Vector3& p0, const Vector3& p1, const Vector4& c0, const Vector4& c1);
			void RasterLineEquationTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector4& c0, const Vector4& c1, const Vector4& c2);
			void RasterSpanTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector4& c0, const Vector4& c1, const Vector4& c2);
			void RasterBarycentricTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector4& c0, const Vector4& c1, const Vector4& c2);
		};
	}
}

