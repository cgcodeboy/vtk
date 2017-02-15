#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkButterflySubdivisionFilter.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>

int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkPolyData> originalMesh;

    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();
    originalMesh = sphereSource->GetOutput();

    double numberOfViewports = 3;
    int numberOfSubdivisions = 2;

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(200* numberOfViewports,200);
    renderWindow->SetWindowName("Multiple ViewPorts");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    for(unsigned i = 0; i < numberOfViewports; i++)
    {
        vtkSmartPointer<vtkPolyDataAlgorithm> subdivisionFilter;
        switch(i)
        {
        case 0:
            subdivisionFilter = vtkSmartPointer<vtkLinearSubdivisionFilter>::New();
            dynamic_cast<vtkLinearSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        case 1:
            subdivisionFilter =  vtkSmartPointer<vtkLoopSubdivisionFilter>::New();
            dynamic_cast<vtkLoopSubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        case 2:
            subdivisionFilter = vtkSmartPointer<vtkButterflySubdivisionFilter>::New();
            dynamic_cast<vtkButterflySubdivisionFilter *> (subdivisionFilter.GetPointer())->SetNumberOfSubdivisions(numberOfSubdivisions);
            break;
        default:
            break;
        }

        subdivisionFilter->SetInputData(originalMesh);
        subdivisionFilter->Update();

        vtkSmartPointer<vtkRenderer> renderer =
            vtkSmartPointer<vtkRenderer>::New();

        renderWindow->AddRenderer(renderer);
        renderer->SetViewport(static_cast<double>(i)/numberOfViewports,0,static_cast<double>(i+1)/numberOfViewports,1);
        renderer->SetBackground(0.8, 0.7, 0.8);

        vtkSmartPointer<vtkPolyDataMapper> mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(subdivisionFilter->GetOutputPort());
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        renderer->AddActor(actor);
        renderer->ResetCamera();
    }

    renderWindow->SetSize(640, 320);
    renderWindow->Render();
    renderWindow->SetWindowName("PolyDataSubdivision");

    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
