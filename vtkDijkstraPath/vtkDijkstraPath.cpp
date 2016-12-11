#include <vtkDijkstraGraphGeodesicPath.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataReader.h>
#include <vtkProperty.h>

int main()
{
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(2);
//    sphere->SetThetaResolution(20);
//    sphere->SetPhiResolution(20);
    sphere->Update();

    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName("fran_cut.vtk");
    reader->Update();

    vtkSmartPointer<vtkDijkstraGraphGeodesicPath> dijkstraPath = vtkSmartPointer<vtkDijkstraGraphGeodesicPath>::New();
    dijkstraPath->SetInputData(reader->GetOutput());
    dijkstraPath->SetStartVertex(0);
    dijkstraPath->SetEndVertex(1500);
    dijkstraPath->Update();

    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkPolyDataMapper> dijkstraMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    dijkstraMapper->SetInputData(dijkstraPath->GetOutput());

    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(originMapper);
    originActor->GetProperty()->SetColor(0.6,0.8,0.8);

    vtkSmartPointer<vtkActor> dijkstraActor = vtkSmartPointer<vtkActor>::New();
    dijkstraActor->SetMapper(dijkstraMapper);
    dijkstraActor->GetProperty()->SetColor(0.8,0.5,0.5);
    dijkstraActor->GetProperty()->SetLineWidth(2);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(originActor);
    render->AddActor(dijkstraActor);
    render->SetBackground(0.7,0.7,0.7);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(600,480);
    window->AddRenderer(render);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;

}
