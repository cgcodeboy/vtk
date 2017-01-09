#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataWriter.h>
#include "../MyVtkWindow.h"

int main()
{
    MyVtkWindow *window = new MyVtkWindow;

    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(5);
    sphere->SetPhiResolution(10);
    sphere->SetThetaResolution(10);
    sphere->Update();

    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    cone->SetRadius(15);
    cone->SetHeight(20);
    cone->SetCenter(10,0,0);
    cone->Update();

    vtkSmartPointer<vtkAppendPolyData> append = vtkSmartPointer<vtkAppendPolyData>::New();
    append->AddInputData(sphere->GetOutput());
    append->AddInputData(cone->GetOutput());
    append->Update();

    vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivity = vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
    connectivity->SetInputData(append->GetOutput());
    connectivity->SetExtractionModeToAllRegions();
    connectivity->Update();

    int regionNum = connectivity->GetNumberOfExtractedRegions();
    for (int i=0; i<regionNum; i++)
    {
        vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter2 =
            vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
        connectivityFilter2->SetInputData(append->GetOutput());
        connectivityFilter2->InitializeSpecifiedRegionList();
        connectivityFilter2->SetExtractionModeToSpecifiedRegions();
        connectivityFilter2->AddSpecifiedRegion(i);
        connectivityFilter2->Update();

        vtkSmartPointer<vtkPolyDataMapper> tempmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        tempmapper->SetInputData(connectivityFilter2->GetOutput());

        vtkSmartPointer<vtkActor> tempactor = vtkSmartPointer<vtkActor>::New();
        tempactor->SetMapper(tempmapper);

        vtkSmartPointer<vtkRenderer> temprender = vtkSmartPointer<vtkRenderer>::New();
        temprender->AddActor(tempactor);
        temprender->SetBackground(0.8,0.6,0.7);

        window->addRenderer(temprender);
    }

    vtkSmartPointer<vtkPolyDataMapper> appendmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    appendmapper->SetInputData(append->GetOutput());

    vtkSmartPointer<vtkActor> appendactor = vtkSmartPointer<vtkActor>::New();
    appendactor->SetMapper(appendmapper);

    vtkSmartPointer<vtkRenderer> appendrender = vtkSmartPointer<vtkRenderer>::New();
    appendrender->AddActor(appendactor);
    appendrender->SetBackground(0.6,0.8,0.7);

    vtkSmartPointer<vtkPolyDataMapper> connectmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    connectmapper->SetInputData(connectivity->GetOutput());

    vtkSmartPointer<vtkActor> connectactor = vtkSmartPointer<vtkActor>::New();
    connectactor->SetMapper(connectmapper);

    vtkSmartPointer<vtkRenderer> connectrender = vtkSmartPointer<vtkRenderer>::New();
    connectrender->AddActor(connectactor);
    connectrender->SetBackground(0.8,0.6,0.7);

    window->addRenderer(appendrender);
    window->addRenderer(connectrender);
    window->startRenderWindow();

    return EXIT_SUCCESS;
}
