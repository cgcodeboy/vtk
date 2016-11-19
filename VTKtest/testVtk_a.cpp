#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCylinderSource.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPNGReader.h>
#include <vtkTexture.h>
#include <vtkTransform.h>

int main()
{
	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->SetGradientBackground(true);
	render->SetBackground(0.2, 0.4, 0.6);
	render->SetBackground2(0.6, 0.4, 0.2);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(render);
	renWin->SetSize(600, 480);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renWin);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	vtkSmartPointer<vtkCylinderSource> cylinderSource = vtkSmartPointer<vtkCylinderSource>::New();
	cylinderSource->SetHeight(10);
	cylinderSource->SetRadius(1);
	cylinderSource->SetResolution(20);

	vtkSmartPointer<vtkPNGReader> pngreader = vtkSmartPointer<vtkPNGReader>::New();
	pngreader->SetFileName("001.png");

	vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
	texture->SetInputConnection(pngreader->GetOutputPort());
	texture->SetRepeat(1);
	texture->InterpolateOn();
	texture->SetEdgeClamp(0);

	vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
	trans->PostMultiply();
	trans->RotateZ(30);

	vtkSmartPointer<vtkPolyDataMapper> dataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	dataMapper->SetInputConnection(cylinderSource->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(dataMapper);
	actor->SetTexture(texture);
	actor->SetUserTransform(trans);
	render->AddActor(actor); 

	vtkSmartPointer<vtkLight> light1 = vtkSmartPointer<vtkLight>::New();
	light1->SetColor(0.5, 0.2, 0.2);
	light1->SetPosition(0, 0, 10);
	light1->SetFocalPoint(render->GetActiveCamera()->GetFocalPoint());
	render->AddLight(light1);

	vtkSmartPointer<vtkLight> light2 = vtkSmartPointer<vtkLight>::New();
	light2->SetColor(0.2, 0.5, 0.2);
	light2->SetPosition(0, 0, -10);
	light2->SetFocalPoint(render->GetActiveCamera()->GetFocalPoint());
	render->AddLight(light2);

	
	render->GetActiveCamera()->SetPosition(0, 0, 20);
	render->GetActiveCamera()->SetViewUp(0, 1, 0);
	render->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	
	interactor->Initialize();
	interactor->Start();
	/*cylinderSource->Delete();
	dataMapper->Delete();
	actor->Delete();
	render->Delete();
	renWin->Delete();
	interactor->Delete();
	style->Delete();
	*/
    return 0;
}
