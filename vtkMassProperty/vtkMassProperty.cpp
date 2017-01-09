#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMassProperties.h>
#include <vtkCubeSource.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <iostream>

using namespace std;

int main()
{
    vtkSmartPointer<vtkCubeSource> source = vtkSmartPointer<vtkCubeSource>::New();
    source->SetXLength(2);
    source->SetYLength(3);
    source->SetZLength(4);
    source->Update();

    vtkSmartPointer<vtkTriangleFilter> filter = vtkSmartPointer<vtkTriangleFilter>::New();
    filter->SetInputData(source->GetOutput());
    filter->Update();

    vtkSmartPointer<vtkMassProperties> massproperty = vtkSmartPointer<vtkMassProperties>::New();
    massproperty->SetInputConnection(filter->GetOutputPort());

    cout<<"Volume      :"<<massproperty->GetVolume()<<endl;
    cout<<"Surface Area:"<<massproperty->GetSurfaceArea()<<endl;
    cout<<"Max Area    :"<<massproperty->GetMaxCellArea()<<endl;
    cout<<"Min Area    :"<<massproperty->GetMinCellArea()<<endl;

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(filter->GetOutputPort());
    mapper->Update();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0,1,0);
    actor->GetProperty()->SetEdgeColor(1,0,0);
    actor->GetProperty()->SetEdgeVisibility(1);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
    render->SetBackground(0.7,0.7,0.7);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(render);
    window->SetSize(600,480);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;

}
