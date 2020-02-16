
#include "igl/opengl/glfw/renderer.h"
#include "tutorial/sandBox/inputManager.h"
#include <iostream>
#define width 1600
#define height 1000
#define arms 10
void init_scene();
Renderer renderer;
igl::opengl::glfw::Viewer viewer;
int main(int argc, char *argv[])
{
  Display *disp = new Display(width, height, "Wellcome");
  Init(*disp);

  renderer.init(&viewer);
  init_scene();
  viewer.init_snake(arms);
  disp->SetRenderer(&renderer);
  disp->launch_rendering(true);
  
  delete disp;
}
void init_scene()
{
	int i;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	 
	// Read the PNG
	viewer.readPNG("text/snake3.png", R, G, B, A);

	for (i = 0; i <= arms; i++) {
		viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/yCylinder.obj");
	}
	
	for (i = 0; i <= arms; i++) {
		viewer.selected_data_index = i;
		viewer.data().set_colors(Eigen::RowVector3d(0.64, 0.4941, 0.102));
		viewer.data().set_face_based(!viewer.data().face_based);
		renderer.core(0).toggle(viewer.data().show_lines);
		//renderer.core(1).toggle(viewer.data().show_lines);
		viewer.data().show_texture = true;
		// Use the image as a texture
		viewer.data().set_texture(R, G, B, A);

	}
	viewer.data().set_colors(Eigen::RowVector3d(0.84, 0.6941, 0.502));
	viewer.readPNG("text/snake_head.png", R, G, B, A);
	viewer.data().set_texture(R, G, B, A);
	for (i = 0; i < arms; i++) {
		viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/sphere.obj");
	}
	viewer.readPNG("text/sphere1.png", R, G, B, A);
	for (i = 1; i <= arms; i++) {
		viewer.selected_data_index = i + arms;
		viewer.data().set_colors(Eigen::RowVector3d(1, 1, 1));
		viewer.data().set_face_based(!viewer.data().face_based);
		renderer.core(0).toggle(viewer.data().show_lines);
		//renderer.core(1).toggle(viewer.data().show_lines);
		viewer.data().show_texture = true;
		viewer.data().set_texture(R, G, B, A);
		
		
	}
	viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/cube.obj");
	viewer.selected_data_index = 1 +(2*arms);
	viewer.data().set_colors(Eigen::RowVector3d(1,1,1));
	viewer.readPNG("text/cube2.png", R, G, B, A);
	viewer.data().show_texture = true;
	viewer.data().set_texture(R, G, B, A);
	viewer.data().invert_normals = true;
	//viewer.data().set_face_based(!viewer.data().face_based);
	renderer.core().toggle(viewer.data().show_lines);
	//renderer.core(1).toggle(viewer.data().show_lines);
	renderer.core().viewport = Eigen::Vector4f(0, 0, width / 2, height);
	int new_core = renderer.append_core(Eigen::Vector4f(width/2, 0, width/2, height));
	//std::cout << new_core << std::endl;
	renderer.selected_core_index = 0;
	renderer.core(1).is_animating = true;
	viewer.selected_data_index = 0;
	
}
