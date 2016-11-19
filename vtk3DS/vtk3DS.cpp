#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtk3DSImporter.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main()
{
	vtkSmartPointer<vtk3DSImporter> importer = vtkSmartPointer<vtk3DSImporter>::New();
	importer->SetFileName("Tiger_I.3ds");
	importer->ComputeNormalsOn();
	importer->Read();

	vtkSmartPointer<vtkRenderer> render = importer->GetRenderer();

	vtkSmartPointer<vtkRenderWindow> window = importer->GetRenderWindow();
	window->SetSize(640, 480);
	window->SetPosition(50, 50);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();
}