#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMetaImageReader.h>

int main()
{
	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("brain.mhd");
	reader->Update();

	vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
	viewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderer> render = viewer->GetRenderer();
	render->SetBackground(0.5, 0.6, 0.7);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->SetSize(600, 480);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	interactor->Start();
	
	viewer->SetColorLevel(500);
	viewer->SetColorWindow(2000);
	viewer->SetSlice(40);
	viewer->SetSliceOrientationToXY();
	viewer->Render();

	return EXIT_SUCCESS;
}