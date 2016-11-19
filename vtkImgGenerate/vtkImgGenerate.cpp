#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main()
{
	vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
	image->SetDimensions(100, 100, 1);
	image->AllocateScalars(VTK_DOUBLE, 3);

	int *dims = image->GetDimensions();
	for (int x = 0; x < dims[0]; x++)
	{
		for (int y = 0; y < dims[1]; y++)
		{
			for (int z = 0; z < dims[2]; z++)
			{
				double *pix = static_cast<double*>(image->GetScalarPointer(x, y, z));
				pix[0] = x;
				pix[1] = y;
				pix[2] = 100 * z;
			}
		}
	}

	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
	actor->SetInputData(image);

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(0.7, 0.7, 0.7);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render);
	window->SetSize(640, 480);
	window->SetPosition(50, 50);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();
}